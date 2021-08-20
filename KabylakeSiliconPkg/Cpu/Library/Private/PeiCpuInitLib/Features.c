/** @file
  CPU feature control module

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification
**/
#include <Library/ReportStatusCodeLib.h>

#include "Features.h"
#include "MachineCheck.h"
#include <Library/BaseLib.h>
#include <Library/PciLib.h>
#include <Library/IoLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/TimerLib.h>
#include <PchAccess.h>
#include <Private/Library/SoftwareGuardLib.h>
#include <Private/Library/CpuCommonLib.h>
#include <Private/Library/BiosGuardInit.h>
#include <Private/CpuInitDataHob.h>
#include <Private/Library/PchRcLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PostCodeLib.h>
#include <Library/CpuMailboxLib.h>

//
// Global variables
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_MP_SERVICES_PPI      *gMpServicesPpi             = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED MP_SYSTEM_DATA               *mMpSystemData              = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED SI_POLICY_PPI                *mSiPolicyPpi               = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_TEST_CONFIG              *mCpuTestConfig             = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_CONFIG                   *mCpuConfig                 = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_POWER_MGMT_BASIC_CONFIG  *mCpuPowerMgmtBasicConfig   = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_POWER_MGMT_CUSTOM_CONFIG *mCpuPowerMgmtCustomConfig  = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_CONFIG_LIB_PREMEM_CONFIG *mCpuConfigLibPreMemConfig  = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                      mC6DramStatus               = FALSE;

#ifndef MINTREE_FLAG
///
/// Values for Trace Hub Acpi Base Address
///
UINT64   mTraceHubAcpiBaseAddress = 0;
BOOLEAN  mTraceHubFeatureEnable   = FALSE;
#endif

//
// Setting for AP init.
//
BOOLEAN  mPmTimerEmulationEnable  = FALSE;

/**
  Perform BIOS uCode PM_TMR Emulation Configuration by configuring MSR 121h and setting
  the ACPI Timer Disable Bit

  The uCode emulation of the ACPI Timer allows disabling of the ACPI Timer to have no
  impact on the system, with the exception that TMR_STS will not be set.  All aligned
  32-bit reads   to the ACPI Timer port are valid and will behave as if the ACPI timer
  remains enabled.
**/
VOID
BiosUcodePmTmrEmulationMsrCfg (
  VOID
  )
{
  UINT64 Data64;
  UINT16 ABase;

  PchAcpiBaseGet (&ABase);

  Data64 = ((LShiftU64 (V_BIOS_UCODE_PM_TMR_EMULATION_CFG_CORRECTION_FACTOR,
                        N_BIOS_UCODE_PM_TMR_EMULATION_CFG_CORRECTION_FACTOR_OFFSET)) |
            (LShiftU64 (V_BIOS_UCODE_PM_TMR_EMULATION_CFG_DELAY_VALUE,
                        N_BIOS_UCODE_PM_TMR_EMULATION_CFG_DELAY_VALUE_OFFSET
                        )) |
           ((B_BIOS_UCODE_PM_TMR_EMULATION_CFG_VALID |
            (ABase + R_PCH_ACPI_PM1_TMR))));
  if (IsBsp ()) {
    DEBUG ((DEBUG_INFO, "ACPI Timer Emulation Config, writing 0x%lx to MSR 121h.\n", Data64));
  }
  AsmWriteMsr64 (MSR_BIOS_UCODE_PM_TMR_EMULATION_CFG, Data64);
}

/**
  Provide access to the CPU misc enables MSR

  @param[in] Enable  - Enable or Disable Misc Features
  @param[in] BitMask - The register bit offset of MSR MSR_IA32_MISC_ENABLE
**/
VOID
CpuMiscEnable (
  BOOLEAN Enable,
  UINT64  BitMask
  )
{
  UINT64 MsrValue;

  MsrValue = AsmReadMsr64 (MSR_IA32_MISC_ENABLE);
  if (Enable) {
    MsrValue |= BitMask;
  } else {
    MsrValue &= ~BitMask;
  }

  AsmWriteMsr64 (MSR_IA32_MISC_ENABLE, MsrValue);
}

///
/// DCA contains processor code and chipset code
/// CPU driver has the following assumption on the initialization flow
/// 1. Chipset pre-initialization should detect DCA support per chipset capability after SiCpuPolicy
/// 2. If not support, it should update SiCpuPolicy DCA to disable state
/// 3. If support, it should enable the DCA related registers
/// 4. CPU initialization for DCA (CPU may change SiCpuPolicy DCA states per CPU capability)
/// 5. Normal chipset driver (IOH) should look at SiCpuPolicy DCA policy again in PCI enumeration
/// 6. Chipset enable or disable DCA according to SiCpuPolicy DCA state
///
/**
  Detect DCA supported or not

  @retval DCA_SUPPORT if supported or 0 if not supported
**/
UINTN
IsDcaSupported (
  VOID
  )
{
  CPUID_VERSION_INFO_ECX Ecx;
  UINTN                  Support;

  Support = 0;
  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &Ecx.Uint32, NULL);
  if (Ecx.Bits.DCA == 1) {
    Support = DCA_SUPPORT;
  }
  return Support;
}

/**
  Detect HT supported or not

  @retval HT_SUPPORT if supported or 0 if not supported
**/
UINTN
IsHTSupported (
  VOID
  )
{
  EFI_CPUID_REGISTER CpuidRegisters;
  UINTN              Support;

  Support = 0;

  AsmCpuidEx (
    CPUID_EXTENDED_TOPOLOGY,
    0,
    &CpuidRegisters.RegEax,
    &CpuidRegisters.RegEbx,
    &CpuidRegisters.RegEcx,
    &CpuidRegisters.RegEdx
    );
  if ((CpuidRegisters.RegEbx & 0x00FF) > 1) {
    Support = HT_SUPPORT;
  }
  return Support;

}

/**
  Detect if AES supported or not

  @retval AES_SUPPORT if supported or 0 if not supported
**/
UINTN
IsAesSupported (
  VOID
  )
{
  CPUID_VERSION_INFO_ECX Ecx;
  UINTN                  Support;

  Support = 0;
  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &Ecx.Uint32, NULL);
  if (Ecx.Bits.AESNI == 1) {
    Support = AES_SUPPORT;
  }
  return Support;
}

/**
  Detect if XD supported or not

  @retval XD_SUPPORT if supported or 0 if not supported
**/
UINTN
IsXdSupported (
  VOID
  )
{
  UINT32                     RegEax;
  CPUID_EXTENDED_CPU_SIG_EDX Edx;
  UINTN                      Support;

  Support = 0;
  AsmCpuid (CPUID_EXTENDED_FUNCTION, &RegEax, NULL, NULL, NULL);
  if (RegEax >= CPUID_EXTENDED_CPU_SIG) {
    AsmCpuid (CPUID_EXTENDED_CPU_SIG, NULL, NULL, NULL, &Edx.Uint32);
    if (Edx.Bits.NX == 1) {
      ///
      /// Execute Disable Bit feature is supported on this processor.
      ///
      Support = XD_SUPPORT;
    }
  }
  return Support;
}

/**
  Program XD if supported or disable it if not supported

  @param[in] Support  - bitmap that indicate XD supported or not
**/
VOID
ProgramXd (
  IN UINTN Support
  )
{
  BOOLEAN XdSupport;

  XdSupport = (BOOLEAN) ((Support & XD_SUPPORT) == XD_SUPPORT);
  ///
  /// MSR MISC_ENABLE[34] has negative logic: 0 - XD Enabled, 1 - XD Disabled
  ///
  CpuMiscEnable (!XdSupport, B_MSR_IA32_MISC_ENABLE_XD);
}

/**
  Check on the processor if VMX/TXT is supported.

  @retval VMX_SUPPORT and/or TXT_SUPPORT if supported or 0 if neither supported
**/
UINTN
IsVmxSupported (
  VOID
  )
{
  CPUID_VERSION_INFO_ECX Ecx;
  UINTN                  Support;

  Support = 0;

  ///
  /// Get CPUID to check if the processor supports Vanderpool Technology.
  ///
  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &Ecx.Uint32, NULL);
  if (Ecx.Bits.VMX == 1) {
    ///
    /// VT is supported.
    ///
    Support |= VMX_SUPPORT;
  }
  if (Ecx.Bits.SMX == 1) {
    ///
    /// TXT is supported.
    ///
    Support |= TXT_SUPPORT;
  }
  return Support;
}

/**
  Enable VMX/TXT on the processor.

  @param[in] Support  - To enable or disable VMX/TXT feature.
**/
VOID
EnableDisableVmx (
  IN UINTN Support
  )
{
  MSR_IA32_FEATURE_CONTROL_REGISTER Msr;

  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_FEATURE_CONTROL);
  Msr.Uint64 &= ~((UINT64) OPTION_FEATURE_RESERVED_MASK); ///< @todo Remove if possible, otherwise document the requirement.

  if (mMpSystemData->CommonFeatures & VMX_SUPPORT) {
    if (Support & VMX_SUPPORT) {
      Msr.Bits.EnableVmxOutsideSmx = 1;
    } else {
      Msr.Bits.EnableVmxOutsideSmx = 0;
    }
  }
  if (mMpSystemData->CommonFeatures & TXT_SUPPORT) {
    if (Support & TXT_SUPPORT) {
      ///
      /// MSR Lock will be done later.
      /// Set all 7 bits for SenterLocalFunctionEnables.
      ///
      Msr.Bits.SenterLocalFunctionEnables = 0x7F;
      Msr.Bits.SenterGlobalEnable = 1;
      if (mMpSystemData->CommonFeatures & VMX_SUPPORT) {
        ///
        /// Bit [1] can only be set if CPU is both VMX and TXT capable
        ///
        Msr.Bits.EnableVmxInsideSmx = 1;
      }
    } else {
      Msr.Bits.EnableVmxInsideSmx = 0;
      Msr.Bits.SenterLocalFunctionEnables = 0;
      Msr.Bits.SenterGlobalEnable = 0;
    }
  }

  ///
  /// Check the Feature Lock Bit.
  /// If it is already set, which indicates we are executing POST
  /// due to a warm RESET (i.e., PWRGOOD was not de-asserted).
  ///
  if (Msr.Bits.Lock == 0) {
    AsmWriteMsr64 (MSR_IA32_FEATURE_CONTROL, Msr.Uint64);
  }
}

/**
  Enable / Disable AES on the processor.

  @param[in] Support  - To enable or disable AES feature.
**/
VOID
EnableDisableAes (
  IN UINTN Support
  )
{
  UINT64 MsrValue;

  if (!(mMpSystemData->CommonFeatures & AES_SUPPORT) || (IsSecondaryThread ())) {
    return;
  }

  ///
  /// The processor was manufactured with AES-NI feature
  ///
  MsrValue = AsmReadMsr64 (MSR_IA32_FEATURE_CONFIG);

  ///
  /// Check the Feature Lock Bit.
  /// If it is already set, which indicates we are executing POST
  /// due to a warm RESET (i.e., PWRGOOD was not de-asserted).
  ///
  if ((MsrValue & B_IA32_FEATURE_CONFIG_LOCK) == 0) {
    if (Support & AES_SUPPORT) {
      ///
      /// Enabled AES, writes of 00b, 01b pr 10b to the MSR will result in AES enable.
      /// Should lock this MSR always, so write 01b to the MSR.
      ///
      MsrValue &= (UINT64) ~B_IA32_FEATURE_CONFIG_AES_DIS;
      MsrValue |= B_IA32_FEATURE_CONFIG_LOCK;
    } else {
      ///
      /// To disable AES, system BIOS must write 11b to this MSR.
      ///
      MsrValue |= (UINT64) (B_IA32_FEATURE_CONFIG_AES_DIS + B_IA32_FEATURE_CONFIG_LOCK);
    }
    AsmWriteMsr64 (MSR_IA32_FEATURE_CONFIG, MsrValue);
  }
  return;
}

/**
  Check on the processor if Debug Interface is supported

  @retval Value of DEBUG_SUPPORT and DEBUG_LOCK_SUPPORT
**/
UINTN
IsDebugInterfaceSupported (
  VOID
  )
{
  UINTN              Support;
  EFI_CPUID_REGISTER CpuIdRegister;

  Support = 0;

  ///
  /// Debug interface is supported if CPUID (EAX=1): ECX[11] = 1,
  ///
  AsmCpuid (
    CPUID_VERSION_INFO,
    &CpuIdRegister.RegEax,
    &CpuIdRegister.RegEbx,
    &CpuIdRegister.RegEcx,
    &CpuIdRegister.RegEdx
    );

  if (CpuIdRegister.RegEcx & BIT11) {
    Support |= DEBUG_SUPPORT;
    Support |= DEBUG_LOCK_SUPPORT;
  }

  return Support;
}

/**
  Enable/Disable Debug Interfaces in the processor.

  @param[in] Support  - To enable or disable Debug Interface feature.
**/
VOID
EnableDisableDebugInterface (
  IN UINTN Support
  )
{
  UINT64  Ia32DebugInterface;

  ///
  /// IA32_DEBUG_INTERFACE_MSR scope is "Package", program on BSP only
  ///
  if (!(mMpSystemData->CommonFeatures & DEBUG_SUPPORT) || (IsBsp () == FALSE)) {
    return;
  }

  ///
  /// Check if the processor supports debug interface
  ///
  if (IsDebugInterfaceSupported ()) {
    Ia32DebugInterface = AsmReadMsr64 (MSR_IA32_DEBUG_INTERFACE);
    if (!(Ia32DebugInterface & B_DEBUG_INTERFACE_LOCK)) {
      if (Support & DEBUG_SUPPORT) {
        ///
        /// Enable Debug Interface (MSR 0xC80.Bit0 = 1)
        ///
        Ia32DebugInterface |= B_DEBUG_INTERFACE_ENABLE;
      } else {
        ///
        /// Disable Debug Interface (MSR 0xC80.Bit0 = 0)
        ///
        Ia32DebugInterface &= (UINT64) ~B_DEBUG_INTERFACE_ENABLE;
      }
      if (Support & DEBUG_LOCK_SUPPORT) {
        Ia32DebugInterface |= B_DEBUG_INTERFACE_LOCK;
      }
      AsmWriteMsr64 (MSR_IA32_DEBUG_INTERFACE, Ia32DebugInterface);
    }
  }
  return;
}

/**
  Lock VMX/TXT feature bits on the processor.
  Set "CFG Lock" (MSR 0E2h Bit[15]
**/

VOID
LockFeatureBit (
  VOID
  )
{
  MSR_IA32_FEATURE_CONTROL_REGISTER Msr;

  ///
  /// MSR 3Ah for VMX/TXT Lock
  ///
  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_FEATURE_CONTROL);
  Msr.Uint64 &= ~((UINT64) OPTION_FEATURE_RESERVED_MASK); ///< @todo Remove if possible, otherwise document the requirement.

  if (Msr.Bits.Lock == 0) {
    ///
    /// Set Feature Lock bits.
    ///
    Msr.Bits.Lock = 1;
    AsmWriteMsr64 (MSR_IA32_FEATURE_CONTROL, Msr.Uint64);
  }

  return;
}

/**
  Detect if X2APIC supported or not

  @retval X2APIC_SUPPORT if supported or 0 if not supported
**/
UINTN
IsX2apicSupported (
  VOID
  )
{
  CPUID_VERSION_INFO_ECX Ecx;
  UINTN                  Support;
  UINT64                 MsrValue;

  Support = 0;

  MsrValue  = AsmReadMsr64 (MSR_IA32_APIC_BASE);
  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &Ecx.Uint32, NULL);
  if (Ecx.Bits.x2APIC == 1) {
    ///
    /// X2APIC Mode feature is supported on this processor.
    ///
    Support = X2APIC_SUPPORT;
  }
  return Support;
}

/**
  Detect if Processor Trace Feature is supported or not

  @retval PROC_TRACE_SUPPORT if supported or 0 if not supported
**/
UINTN
IsProcTraceSupported (
  VOID
  )
{
  CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS_EBX Ebx;
  UINTN                                       Support;

  Support = 0;
  AsmCpuidEx (CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS, 0, NULL, &Ebx.Uint32, NULL, NULL);
  if (Ebx.Bits.IntelProcessorTrace == 1) {
    Support = PROC_TRACE_SUPPORT;
  }
  return Support;
};


/**
  Initialize Processor Trace Feature

  @param[in] Support    Bitmap that indicate HT supported or not
**/
VOID
InitializeProcTrace (
  IN UINTN Support
  )
{
  UINT64                                    MsrValue;
  UINT32                                    MemRegionSize;
  UINTN                                     Pages;
  UINTN                                     Alignment;
  UINTN                                     MemRegionBaseAddr = 0;
  STATIC UINTN                              *ThreadMemRegionTable;
  STATIC UINTN                              ThreadMemRegionIndex = 0;
  STATIC UINTN                              AllocatedThreads = 0;
  UINTN                                     Index;
  UINTN                                     TopaTableBaseAddr;
  UINTN                                     AlignedAddress;
  STATIC UINTN                              *TopaMemArray;
  STATIC UINTN                              TopaMemIndex = 0;
  PROC_TRACE_TOPA_TABLE                     *TopaTable;
  CPUID_INTEL_PROCESSOR_TRACE_MAIN_LEAF_ECX Ecx;
  BOOLEAN                                   IsTopaSupported;
  BOOLEAN                                   IsSingleRangeSupported;
  BOOLEAN                                   IsBspInt;
  EFI_BOOT_MODE                             BootMode;
  UINT32                                    ApicId;

  IsBspInt     = IsBsp ();

  if (IsBspInt) {
    DEBUG ((DEBUG_INFO, "Initialize Processor Trace\n"));
  }

  ///
  /// On S3 resume, wait and restore MSR settings during S3 initialization
  ///
  PeiServicesGetBootMode (&BootMode);
  if (BootMode == BOOT_ON_S3_RESUME) {
    return;
  }

  ///
  /// Check if Processor Trace is supported, or ProcTraceMemorySize option is enabled (0xFF means disable by user)
  ///
  if ((!IsProcTraceSupported ()) || (mCpuTestConfig->ProcTraceMemSize >= EnumProcTraceMemDisable)) {
    return;
  }

  ///
  /// Detect which processor trace output schemes are supported.
  ///
  AsmCpuidEx (CPUID_INTEL_PROCESSOR_TRACE, CPUID_INTEL_PROCESSOR_TRACE_MAIN_LEAF, NULL, NULL, &Ecx.Uint32, NULL);
  IsTopaSupported = (Ecx.Bits.RTIT == 1) ? TRUE : FALSE;
  IsSingleRangeSupported = (Ecx.Bits.SingleRangeOutput == 1) ? TRUE : FALSE;

  if (!(IsTopaSupported || IsSingleRangeSupported)) {
    return;
  }
  ///
  /// Refer to PROC_TRACE_MEM_SIZE Table for Size Encoding
  ///
  MemRegionSize = (UINT32) (1 << (mCpuTestConfig->ProcTraceMemSize + 12));
  if (IsBspInt) {
    DEBUG ((DEBUG_INFO, "ProcTrace: MemSize requested: 0x%X \n", MemRegionSize));
  }

  //
  // Clear MSR_IA32_RTIT_CTL[0] and IA32_RTIT_STS only if MSR_IA32_RTIT_CTL[0]==1b
  //
  MsrValue = AsmReadMsr64 (MSR_IA32_RTIT_CTL);
  if (MsrValue & B_RTIT_CTL_TRACE_ENABLE) {
    ///
    /// Clear bit 0 in MSR IA32_RTIT_CTL (570)
    ///
    MsrValue &= (UINT64) ~B_RTIT_CTL_TRACE_ENABLE;
    AsmWriteMsr64 (MSR_IA32_RTIT_CTL, MsrValue);

    ///
    /// Clear MSR IA32_RTIT_STS (571h) to all zeros
    ///
    MsrValue = AsmReadMsr64 (MSR_IA32_RTIT_STATUS);
    MsrValue &= 0x0;
    AsmWriteMsr64 (MSR_IA32_RTIT_STATUS, MsrValue);
  }

  if (IsBspInt) {
    /**
       Let BSP allocate and create the necessary memory region (Aligned to the size of
       the memory region from setup option(ProcTraceMemSize) which is an integral multiple of 4kB)
       for the all the enabled threads for storing Processor Trace debug data. Then Configure the trace
       address base in MSR, IA32_RTIT_OUTPUT_BASE (560h) bits 47:12. Note that all regions must be
       aligned based on their size, not just 4K. Thus a 2M region must have bits 20:12 clear.
    **/
    ThreadMemRegionTable = (UINTN *) AllocatePool (mMpSystemData->TotalCpusForThisSystem * sizeof (UINTN *));
    if (ThreadMemRegionTable == NULL) {
      DEBUG ((DEBUG_ERROR, "Allocate ProcTrace ThreadMemRegionTable Failed\n"));
      return;
    }

    for (Index = 0; Index < mMpSystemData->TotalCpusForThisSystem; Index++, AllocatedThreads++) {
      Pages = EFI_SIZE_TO_PAGES (MemRegionSize);
      Alignment = MemRegionSize;
      AlignedAddress = (UINTN) AllocateAlignedReservedPages (Pages, Alignment);
      if (AlignedAddress == 0) {
        DEBUG ((DEBUG_ERROR, "ProcTrace: Out of mem, allocated only for %d threads\n", AllocatedThreads));
        if (Index == 0) {
          //
          // Could not allocate for BSP even
          //
          ThreadMemRegionTable = NULL;
          return;
        }
        break;
      }

      ThreadMemRegionTable[Index] = AlignedAddress;
      DEBUG ((DEBUG_INFO, "ProcTrace: PT MemRegionBaseAddr(aligned) for thread %d: 0x%llX \n", Index, (UINT64) ThreadMemRegionTable[Index]));
    }

    DEBUG ((DEBUG_INFO, "ProcTrace: Allocated PT mem for %d thread \n", AllocatedThreads));
    //
    // BSP gets the first block
    //
    MemRegionBaseAddr = ThreadMemRegionTable[0];
  } else {
    //
    // Each AP gets different index
    //
    //
    // Count for currently executing AP.
    //
    ThreadMemRegionIndex++;
    if (ThreadMemRegionIndex < AllocatedThreads) {
      MemRegionBaseAddr = ThreadMemRegionTable[ThreadMemRegionIndex];
    } else {
      return;
    }
  }

  ///
  /// Check Processor Trace output scheme: Single Range output or ToPA table
  ///
  //
  //  Single Range output scheme
  //
  if (IsSingleRangeSupported && (mCpuTestConfig->ProcTraceOutputScheme == 0)) {
    if (IsBspInt) {
      DEBUG ((DEBUG_INFO, "ProcTrace: Enabling Single Range Output scheme \n"));
    }

    //
    // Clear MSR IA32_RTIT_CTL (0x570) ToPA (Bit 8)
    //
    MsrValue = AsmReadMsr64 (MSR_IA32_RTIT_CTL);
    MsrValue &= (UINT64) ~BIT8;
    AsmWriteMsr64 (MSR_IA32_RTIT_CTL, MsrValue);

    //
    // Program MSR IA32_RTIT_OUTPUT_BASE (0x560) bits[47:12] with the allocated Memory Region
    //
    MsrValue = (UINT64) MemRegionBaseAddr;
    AsmWriteMsr64 (MSR_IA32_RTIT_OUTPUT_BASE, MsrValue);

    //
    // Program the Mask bits for the Memory Region to MSR IA32_RTIT_OUTPUT_MASK_PTRS (561h)
    //
    MsrValue = (UINT64) MemRegionSize - 1;
    AsmWriteMsr64 (MSR_IA32_RTIT_OUTPUT_MASK_PTRS, MsrValue);

    ApicId = GetCpuApicId ();

    //
    // Only support MAX_PROCESSOR_THREADS threads so far
    //
    ASSERT (ApicId < MAX_PROCESSOR_THREADS);
    if (ApicId < MAX_PROCESSOR_THREADS) {
      mMpSystemData->CpuPrivateData.ProcessorTraceAddress[ApicId] = MemRegionBaseAddr;
    }
  }

  //
  //  ToPA(Table of physical address) scheme
  //
  if (IsTopaSupported && (mCpuTestConfig->ProcTraceOutputScheme == 1)) {
    /**
      Create ToPA structure aligned at 4KB for each logical thread
      with at least 2 entries by 8 bytes size each. The first entry
      should have the trace output base address in bits 47:12, 6:9
      for Size, bits 4,2 and 0 must be cleared. The second entry
      should have the base address of the table location in bits
      47:12, bits 4 and 2 must be cleared and bit 0 must be set.
    **/
    if (IsBspInt) {
      DEBUG ((DEBUG_INFO, "ProcTrace: Enabling ToPA scheme \n"));
      /**
         Let BSP allocate ToPA table mem for all threads
      **/
      TopaMemArray = (UINTN *) AllocatePool (AllocatedThreads * sizeof (UINTN *));
      if (TopaMemArray == NULL) {
        DEBUG ((DEBUG_ERROR, "ProcTrace: Allocate mem for ToPA Failed\n"));
        return;
      }

      for (Index=0; Index < AllocatedThreads; Index++) {
        Pages = EFI_SIZE_TO_PAGES (sizeof (PROC_TRACE_TOPA_TABLE));
        Alignment = 0x1000;
        AlignedAddress = (UINTN) AllocateAlignedReservedPages (Pages, Alignment);
        if (AlignedAddress == 0) {
          if ( Index < AllocatedThreads) {
            AllocatedThreads = Index;
          }
          DEBUG ((DEBUG_ERROR, "ProcTrace:  Out of mem, allocating ToPA mem only for %d threads\n", AllocatedThreads));
          if (Index == 0) {
            //
            // Could not allocate for BSP
            //
            TopaMemArray = NULL;
            return;
          }
          break;
        }

        TopaMemArray[Index] = AlignedAddress;
        DEBUG ((DEBUG_INFO, "ProcTrace: Topa table address(aligned) for thread %d is 0x%llX \n", Index,  (UINT64) TopaMemArray[Index]));
      }

      DEBUG ((DEBUG_INFO, "ProcTrace: Allocated ToPA mem for %d thread \n", AllocatedThreads));
      //
      // BSP gets the first block
      //
      TopaTableBaseAddr = TopaMemArray[0];
    } else {
      //
      // Count for currently executing AP.
      //
      TopaMemIndex++;
      if (TopaMemIndex < AllocatedThreads) {
        TopaTableBaseAddr = TopaMemArray[TopaMemIndex];
      } else {
        return;
      }
    }

    TopaTable = (PROC_TRACE_TOPA_TABLE *) TopaTableBaseAddr;
    TopaTable->TopaEntry[0] = (UINT64) (MemRegionBaseAddr | ((mCpuTestConfig->ProcTraceMemSize) << 6)) & ~BIT0;
    TopaTable->TopaEntry[1] = (UINT64) TopaTableBaseAddr | BIT0;

    //
    // Program the MSR IA32_RTIT_OUTPUT_BASE (0x560) bits[47:12] with ToPA base
    //
    MsrValue = (UINT64) TopaTableBaseAddr;
    AsmWriteMsr64 (MSR_IA32_RTIT_OUTPUT_BASE, MsrValue);
    //
    // Set the MSR IA32_RTIT_OUTPUT_MASK (0x561) bits[63:7] to 0
    //
    AsmWriteMsr64 (MSR_IA32_RTIT_OUTPUT_MASK_PTRS, 0x7f);
    //
    // Enable ToPA output scheme by enabling MSR IA32_RTIT_CTL (0x570) ToPA (Bit 8)
    //
    MsrValue = AsmReadMsr64 (MSR_IA32_RTIT_CTL);
    MsrValue |= BIT8;
    AsmWriteMsr64 (MSR_IA32_RTIT_CTL, MsrValue);

    ApicId = GetCpuApicId ();

    //
    // Only support MAX_PROCESSOR_THREADS threads so far
    //
    ASSERT (ApicId < MAX_PROCESSOR_THREADS);
    if (ApicId < MAX_PROCESSOR_THREADS) {
      mMpSystemData->CpuPrivateData.ProcessorTraceAddress[ApicId] = TopaTableBaseAddr;
    }
  }

  ///
  /// Enable the Processor Trace feature from MSR IA32_RTIT_CTL (570h)
  ///
  MsrValue = AsmReadMsr64 (MSR_IA32_RTIT_CTL);
  MsrValue |= (UINT64) BIT0 + BIT2 + BIT3 + BIT13;
  if (!(mCpuTestConfig->ProcTraceEnable)) {
    MsrValue &= (UINT64) ~BIT0;
  }
  AsmWriteMsr64 (MSR_IA32_RTIT_CTL, MsrValue);

}

/**
  Initialize Hardware Duty Cycling (HDC)

  @param[in] IsBspInt     Is this BSP
**/
VOID
InitializeHdc (
  BOOLEAN                     IsBspInt
  )
{
  UINT64                      MsrValue;
  BOOLEAN                     HdcSupported;


  ///
  /// HDC is supported in SKL CPUs if Bit 10 of MSR_MISC_PWR_MGMT (0x1AA) is set.
  /// HDC control is enabled and controlled by OS.
  ///
  HdcSupported                = (AsmReadMsr64 (MSR_MISC_PWR_MGMT) & B_MISC_PWR_MGMT_ENABLE_SDC) != 0;
  mMpSystemData->HdcSupported = HdcSupported;

  if (mCpuPowerMgmtBasicConfig->HdcControl > 1) {
    if (IsBspInt) {
      DEBUG ((DEBUG_INFO, "HdcControl value is invalid. Bypass HDC initialization.\n"));
    }
    return;
  }

  if (IsBspInt && HdcSupported && (mCpuPowerMgmtBasicConfig->HdcControl == 0)) {
    ///
    /// If Disabled, clear MSR_MISC_PWR_MGMT (1AAh) [10]
    ///
    MsrValue = AsmReadMsr64 (MSR_MISC_PWR_MGMT);
    MsrValue &= (UINT64) ~B_MISC_PWR_MGMT_ENABLE_SDC;
    AsmWriteMsr64 (MSR_MISC_PWR_MGMT, MsrValue);
  } else {
    if (IsBspInt) {
      DEBUG ((DEBUG_INFO, "Hardware Duty Cycle is not supported.\n"));
    }
  }
}

/**
  Initialize other processor functions (TPR messaging, floating point)
**/
VOID
InitializeMiscProcessorFunctions (
  VOID
  )
{
  UINT64 MsrValue;

  ///
  /// Enable TPR Update messages,if supported (see section 2.5)
  ///
  MsrValue = AsmReadMsr64 (PIC_THREAD_CONTROL);
  MsrValue &= (UINT64) (~B_PIC_THREAD_CONTROL_TPR_DIS);
  AsmWriteMsr64 (PIC_THREAD_CONTROL, MsrValue);

  if (mCpuTestConfig->ThreeStrikeCounterDisable) {
    MsrValue = AsmReadMsr64 (MISC_FEATURE_CONTROL);
    MsrValue |= (B_MISC_FEATURE_CONTROL_3_STRIKE_CNT);
    AsmWriteMsr64 (MISC_FEATURE_CONTROL, MsrValue);
  }

  ///
  /// Enable the Save Floating Point feature on every logical processors in the
  /// platform when available. The BIOS must verify the SMM SAVE CONTROL capability
  /// bit is set to 1 in PLATFORM_INFO MSR CEh [16] (see Section 2.16) before setting
  /// the SMM_SAVE_CONTROL MSR 3Eh [0] to [1].
  ///
  MsrValue = AsmReadMsr64 (MSR_PLATFORM_INFO);
  if ((MsrValue & B_PLATFORM_INFO_SMM_SAVE_CONTROL) != 0) {
    MsrValue = AsmReadMsr64 (MSR_IA32_SMM_SAVE_CONTROL);
    MsrValue |= B_MSR_IA32_SMM_SAVE_CONTROL_SFPPE;
    AsmWriteMsr64 (MSR_IA32_SMM_SAVE_CONTROL, MsrValue);
  }
}

/**
  Create feature control structure which will be used to program each feature on each core.
**/
VOID
InitializeFeaturePerSetup (
  VOID
  )
{

  mMpSystemData->CommonFeatures = (UINTN) -1;
  mMpSystemData->SetupFeatures  = (UINTN) -1;

  if (!mCpuConfigLibPreMemConfig->VmxEnable) {
    mMpSystemData->SetupFeatures &= ~VMX_SUPPORT;
  }
  if (!mCpuConfig->TxtEnable) {
    mMpSystemData->SetupFeatures &= ~TXT_SUPPORT;
  }
  if (!mCpuConfig->AesEnable) {
    mMpSystemData->SetupFeatures &= ~AES_SUPPORT;
  }
  if (!mCpuTestConfig->DebugInterfaceEnable) {
    mMpSystemData->SetupFeatures &= ~DEBUG_SUPPORT;
  }
  if (!mCpuTestConfig->DebugInterfaceLockEnable) {
    mMpSystemData->SetupFeatures &= ~DEBUG_LOCK_SUPPORT;
  }
  if (!mCpuTestConfig->ProcTraceEnable) {
    mMpSystemData->SetupFeatures &= ~PROC_TRACE_SUPPORT;
  }
  if (!mCpuConfigLibPreMemConfig->HyperThreading) {
    mMpSystemData->SetupFeatures &= ~HT_SUPPORT;
  }

}

/**
  Detect each processor feature and log all supported features
**/
VOID
EFIAPI
CollectProcessorFeature (
  VOID
  )
{
  UINTN Support;

  Support = 0;
  Support |= IsXdSupported ();
  Support |= IsVmxSupported ();
  Support |= IsDcaSupported ();
  Support |= IsAesSupported ();
  Support |= IsX2apicSupported ();
  Support |= IsHTSupported ();
  Support |= IsDebugInterfaceSupported ();
  Support |= IsProcTraceSupported ();

  mMpSystemData->CommonFeatures &= Support;

  return;
}

#ifndef MINTREE_FLAG
/**
  Get Trace Hub Acpi Base address for BSP
**/
VOID
EFIAPI
GetTraceHubAcpiBaseAddressForBsp (
  VOID
  )
{
  ///
  /// Get Trace Hub ACPI base address from BSP
  ///
  mTraceHubAcpiBaseAddress = AsmReadMsr64 (MSR_TRACE_HUB_STH_ACPIBAR_BASE);
  DEBUG ((DEBUG_INFO, "TraceHubAcpiBaseAddress = %x\n", mTraceHubAcpiBaseAddress));

  ///
  /// Check the pass in Trace Hub ACPI base if equal zero.
  ///
  if (mTraceHubAcpiBaseAddress != 0) {
    mTraceHubFeatureEnable = TRUE;
  }
  return;
}
#endif

/**
  Program all processor features basing on desired settings

  @param[in] Buffer - A pointer to a buffer used to pass Cpu Policy PPI
**/
VOID
EFIAPI
ProgramProcessorFeature (
  IN VOID *Buffer
  )
{
  UINTN                         Supported;
  EFI_STATUS                    Status;
  BOOLEAN                       IsBspInt;
  SI_PREMEM_POLICY_PPI          *SiPreMemPolicyPpi;
  CPU_SECURITY_PREMEM_CONFIG    *CpuSecurityPreMemConfig;

  IsBspInt          = IsBsp ();
  SiPreMemPolicyPpi = ((SI_PREMEM_POLICY_PPI *) Buffer);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);

#ifndef MINTREE_FLAG
  ///
  /// Get Trace Hub Acpi Base address for BSP
  ///
  if (IsBspInt) {
    GetTraceHubAcpiBaseAddressForBsp ();
  }

  if (!IsBspInt) {
    ///
    /// This is to program Trace Hub ACPI base address for all the threads
    ///
    if (mTraceHubFeatureEnable) {
      AsmWriteMsr64 (MSR_TRACE_HUB_STH_ACPIBAR_BASE, mTraceHubAcpiBaseAddress);
    }
  }
#endif

  Supported = mMpSystemData->CommonFeatures & mMpSystemData->SetupFeatures;

  ///
  /// Configure features such as Xd, Vmx, Smx, XAPIC, AES, DebugInterface, Processor Trace feature
  ///
  ProgramXd (Supported);
  EnableDisableVmx (Supported);
  EnableDisableAes (Supported);
  EnableDisableDebugInterface (Supported);
  InitializeProcTrace (Supported);

  ///
  /// Initialize Hardware Duty Cycling
  ///
  if (IsBspInt) {
    DEBUG ((DEBUG_INFO, "Initialize Hardware Duty Cycle\n"));
  }
  InitializeHdc (IsBspInt);

  ///
  /// Program XApic register
  ///
  if (IsBspInt) {
    DEBUG ((DEBUG_INFO, "Program xAPIC\n"));
  }
  ProgramXApic (IsBspInt);

  ///
  /// Initialize MonitorMWait register
  ///
  if (IsBspInt) {
    DEBUG ((DEBUG_INFO, "Initialize Monitor Wait register\n"));
  }
  CpuMiscEnable ((BOOLEAN)mCpuTestConfig->MonitorMwaitEnable, B_MSR_IA32_MISC_ENABLE_MONITOR);

  ///
  /// Initialize Machine Check registers
  ///
  if (IsBspInt) {
    DEBUG ((DEBUG_INFO, "Initialize Machine check registers\n"));
  }
  InitializeMachineCheckRegisters (NULL, (BOOLEAN) mCpuTestConfig->MachineCheckEnable);

  //
  // Misc functions
  //
  if (IsBspInt) {
    DEBUG ((DEBUG_INFO, "Initialize miscellaneous processor functions\n"));
  }
  InitializeMiscProcessorFunctions ();

  ///
  /// Initialize Core PRMRRs if SGX or C6DRAM is enabled
  ///
  if (IsBspInt) {
    mC6DramStatus = GetC6DramStatus (CpuSecurityPreMemConfig->EnableC6Dram);
  }
  if ((CpuSecurityPreMemConfig->EnableSgx) || mC6DramStatus) {
    ///
    /// Initialize Core PRMRRs.
    ///
    if (IsBspInt) {
      DEBUG ((DEBUG_INFO, "Initialize Core PRMRRs\n"));
    }
    InitializeCorePrmrr ();
  }

  ///
  /// Configure BIOS uCode PM_TMR Emulation MSR 121h on all logical processors (BSP & APs).
  /// Only enable this when PCH PM Timer is disabled.
  ///
  if (mPmTimerEmulationEnable) {
    BiosUcodePmTmrEmulationMsrCfg ();
  }

  return;
}

/**
  Program CPUID Limit before booting to OS
**/
VOID
EFIAPI
ProgramCpuidLimit (
  VOID
  )
{
  UINT64 MsrValue;

  ///
  /// Finally write MISC MSR to avoid access for multiple times
  ///
  MsrValue = AsmReadMsr64 (MSR_IA32_MISC_ENABLE);
  AsmWriteMsr64 (MSR_IA32_MISC_ENABLE, MsrValue);

  return;
}

/**
  Initialize prefetcher settings

  @param[in] MlcStreamerprefecterEnabled - Enable/Disable MLC streamer prefetcher
  @param[in] MlcSpatialPrefetcherEnabled - Enable/Disable MLC spatial prefetcher
**/
VOID
InitializeProcessorsPrefetcher (
  IN UINTN MlcStreamerprefecterEnabled,
  IN UINTN MlcSpatialPrefetcherEnabled
  )
{
  UINT64 MsrValue;
  MsrValue = AsmReadMsr64 (MISC_FEATURE_CONTROL);

  if (MlcStreamerprefecterEnabled == CPU_FEATURE_DISABLE) {
    MsrValue |= B_MISC_FEATURE_CONTROL_MLC_STRP;
  }

  if (MlcSpatialPrefetcherEnabled == CPU_FEATURE_DISABLE) {
    MsrValue |= B_MISC_FEATURE_CONTROL_MLC_SPAP;
  }

  if ((MsrValue & (B_MISC_FEATURE_CONTROL_MLC_STRP | B_MISC_FEATURE_CONTROL_MLC_SPAP)) != 0) {
    AsmWriteMsr64 (MISC_FEATURE_CONTROL, MsrValue);
  }

  return;
}

/**
   Initialize Silicon Info
   @param[in] CPU_INIT_DATA_HOB          *CpuInitDataHob
   @retval EFI_SUCCESS  The driver updated Silicon data
           successfully
   @retval EFI_NOT_FOUND No Silicon info was found.
**/
EFI_STATUS
InitSiliconInfo (
  CPU_INIT_DATA_HOB          *CpuInitDataHob
  )
{
  if (!CpuInitDataHob) {
    return EFI_NOT_FOUND;
  }

  CpuInitDataHob->SiliconInfo |= ((mMpSystemData->HdcSupported) << N_HDC_SUPPORT) & B_HDC_SUPPORT;
  DEBUG ((DEBUG_INFO, "CpuInitDataHob->SiliconInfo = %016X\n", CpuInitDataHob->SiliconInfo));
  return EFI_SUCCESS;
}

/**
  Initialize CPU Data Hob

  @retval EFI_SUCCESS     The driver installed/initialized correctly.
  @retval EFI_OUT_OF_RESOURCES  Allocation of the hob failed.
**/
EFI_STATUS
InitializeCpuDataHob (
  VOID
  )
{
  CPU_INIT_DATA_HOB      *CpuInitDataHob;
  VOID                   *Hob;
  EFI_STATUS             Status;
  CPU_CONFIG_DATA        *CpuConfigData;

  DEBUG((DEBUG_INFO, "InitializeCpuDataHob Start \n"));
  PostCode (0xC43);

  ///
  /// Initial cpu data into one hob, it will be used by MP CPU DXE.
  ///
  CpuInitDataHob = AllocateRuntimeZeroPool (sizeof (CPU_INIT_DATA_HOB));
  if (CpuInitDataHob==NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  CpuConfigData = (CPU_CONFIG_DATA *) &mMpSystemData->CpuConfigData;

  CpuConfigData->SmmbaseSwSmiNumber      = (UINT8) mCpuConfig->SmmbaseSwSmiNumber;
  CpuConfigData->ApHandoffManner         = mCpuTestConfig->ApHandoffManner;
  CpuConfigData->ApIdleManner            = mCpuTestConfig->ApIdleManner;
  CpuConfigData->EnableDts               = mCpuConfig->EnableDts;
  CpuConfigData->HdcControl              = mCpuPowerMgmtBasicConfig->HdcControl;
  CpuConfigData->Hwp                     = mCpuPowerMgmtBasicConfig->Hwp;
  CpuConfigData->ConfigTdpBios           = mCpuPowerMgmtCustomConfig->ConfigTdpBios;

  CpuInitDataHob->CpuConfigData      = (EFI_PHYSICAL_ADDRESS)(UINTN) &mMpSystemData->CpuConfigData;
  CpuInitDataHob->MpData             = (EFI_PHYSICAL_ADDRESS)(UINTN) &mMpSystemData->AcpiCpuData;
  CpuInitDataHob->FvidTable          = (EFI_PHYSICAL_ADDRESS)(UINTN) &mMpSystemData->FvidTable;

  Status = InitSiliconInfo (CpuInitDataHob);
  ASSERT_EFI_ERROR (Status);

  Hob = BuildGuidDataHob (
          &gCpuInitDataHobGuid,
          (VOID *) CpuInitDataHob,
          (UINTN) sizeof (CPU_INIT_DATA_HOB)
          );
  ASSERT (Hob != NULL);

  DEBUG((DEBUG_INFO, "InitializeCpuDataHob Done \n"));
  PostCode (0xC44);

  return EFI_SUCCESS;
}

/**
  Re-load microcode patch.

  @param[in] Buffer      - A pointer to buffer which need to append the element
**/
VOID
EFIAPI
ReloadMicrocodePatch (
  VOID
  )
{
  EFI_STATUS           Status;
  UINT32               FailedRevision;
  BOOLEAN              IsBspVal;

  IsBspVal = IsBsp();

  if (IsBspVal) {
    DEBUG ((DEBUG_INFO, "ReloadMicrocodePatch: second patch load started\n"));
  }


  ///
  /// Init XMM
  ///
  XmmInit ();

  if (IsBspVal) {
    ProgramXApic (TRUE);
  } else {
    ProgramXApic (FALSE);
  }

  Status = InitializeMicrocode (
             (CPU_MICROCODE_HEADER *) (UINTN) mCpuConfig->MicrocodePatchAddress,
             &FailedRevision
             );

  if (!IsBspVal) {
    ProcessorsPrefetcherInitialization (
      (UINTN) mCpuTestConfig->MlcStreamerPrefetcher,
      (UINTN) mCpuTestConfig->MlcSpatialPrefetcher
      );
  }

  if (Status != EFI_SUCCESS) {
    if (IsBspVal) {
      DEBUG ((DEBUG_INFO, "ReloadMicrocodePatch: Second patch load failed, SGX is not activated\n"));
    }
  }

  return;
}

/**
  Get CPU platform features settings to fill MP system data.

  @param[in] TotalCpusForThisSystem - Total number of logical processors in this system.

  @retval EFI_SUCCESS              - Function successfully executed.
  @retval Other                    - Error occurred while allocating memory.
**/
EFI_STATUS
EFIAPI
FillMpSystemData (
  IN UINTN                  TotalCpusForThisSystem
  )
{
  ///
  /// Fill up MpSystemData
  ///
  mMpSystemData->AcpiCpuData.CpuPrivateData           = (EFI_PHYSICAL_ADDRESS) (UINTN) (&mMpSystemData->CpuPrivateData);
  mMpSystemData->AcpiCpuData.NumberOfCpus             = TotalCpusForThisSystem;
  mMpSystemData->AcpiCpuData.APState                  = TRUE;
  mMpSystemData->HdcSupported                         = (AsmReadMsr64 (MSR_MISC_PWR_MGMT) & B_MISC_PWR_MGMT_ENABLE_SDC) != 0;
  mMpSystemData->CpuPrivateData.S3BspMtrrTablePointer = (UINT32) (UINTN) mMpSystemData->S3BspMtrrTable;
  mMpSystemData->TotalCpusForThisSystem               = TotalCpusForThisSystem;
  mMpSystemData->BSP                                  = 0;

  return EFI_SUCCESS;
}

/**
  Finalization of settings post Microcode patch reload
**/
VOID
ApSafePostMicrocodePatchInit (
  VOID
  )
{
  SgxInitializationPostPatchLoad ();

  ///
  /// Setting lock bit on feature MSR
  ///
  LockFeatureBit ();

  return;
}

/**
  This function sends PECI related mailbox commands early in boot if needed

  @param[in] CpuConfigLibPreMemConfig Pointer to the cpu config lib premem config block instance

  @retval EFI_SUCCESS              - Function successfully executed.
  @retval Other                    - Error occurred during mailbox commands.
**/
EFI_STATUS
EFIAPI
CpuPeciMailboxCommands (
  IN CPU_CONFIG_LIB_PREMEM_CONFIG *CpuConfigLibPreMemConfig
  )

{
  EFI_STATUS Status;
  UINT32  MailboxType;
  UINT32  MailboxCmd;
  UINT32  MailboxData;
  UINT32  MailboxStatus;

  DEBUG((DEBUG_INFO, "CpuPeciMailboxCommands Start \n"));

  MailboxType = MAILBOX_TYPE_VR_MSR;
  Status = EFI_SUCCESS;
  ///
  /// Send the PECI Sx command only if needed, otherwise, don't send any message
  ///
  if (CpuConfigLibPreMemConfig->PeciSxReset == TRUE) {
    MailboxCmd = MAILBOX_PECI_SX_RESET_CMD;
    MailboxData = 0;
    Status = MailboxWrite(MailboxType,MailboxCmd,MailboxData,&MailboxStatus);
    if (EFI_ERROR(Status) || (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS)) {
      DEBUG((DEBUG_ERROR, "PECI: Error in PECI Sx command. EFI_STATUS = %X, MailboxStatus = %X\n", Status, MailboxStatus));
    } else {
      DEBUG ((DEBUG_INFO, "PECI: Peci Sx Status = 0x%x\n", MailboxStatus));
    }
  }

  ///
  /// Send the PECI C10 command only if needed, otherwise, don't send any message
  ///
  if (CpuConfigLibPreMemConfig->PeciC10Reset == TRUE) {
    MailboxCmd = MAILBOX_PECI_C10_RESET_CMD;
    MailboxData = 1;
    Status = MailboxWrite(MailboxType,MailboxCmd,MailboxData,&MailboxStatus);
    if (EFI_ERROR(Status) || (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS)) {
      DEBUG((DEBUG_ERROR, "PECI: Error in PECI C10 command. EFI_STATUS = %X, MailboxStatus = %X\n", Status, MailboxStatus));
    } else {
      DEBUG ((DEBUG_INFO, "PECI: Peci C10 Status = 0x%x\n", MailboxStatus));
    }
  }

  return Status;
}

/**
  Initialize processor features, performance and power management features, BIOS Guard, and Overclocking etc features before RESET_CPL at post-memory phase.

  @param[in] PeiServices      Pointer to PEI Services Table
  @param[in] SiPolicyPpi      The SI Policy PPI instance

  @retval EFI_SUCCESS     The driver installed/initialized correctly.
**/
EFI_STATUS
CpuInit (
  IN  CONST EFI_PEI_SERVICES  **PeiServices,
  IN  SI_POLICY_PPI           *SiPolicyPpi
  )
{
  EFI_STATUS                 Status;
  SI_PREMEM_POLICY_PPI       *SiPreMemPolicyPpi;
  CPU_SECURITY_PREMEM_CONFIG *CpuSecurityPreMemConfig;
  BIOS_GUARD_CONFIG          *BiosGuardConfig;
  UINTN                      NumberOfProcessors;
  UINTN                      NumberOfEnabledProcessors;
  CPU_FAMILY                 CpuFamilyId;
  CPU_STEPPING               CpuStepping;
  EFI_BOOT_MODE              BootMode;
  VOID                       *Hob;
  CPU_OVERCLOCKING_PREMEM_CONFIG  *CpuOverClockingPreMemConfig;
  MSR_REGISTER                    TempMsr;

  DEBUG((DEBUG_INFO, "CpuInit Start \n"));
  PostCode (0xC15);

  DEBUG ((DEBUG_INFO, "Cpu Initialization in PostMem start\n"));

  ///
  /// Allocate Cpu MP system data structure memory.
  ///
  mMpSystemData = (MP_SYSTEM_DATA *) AllocatePages (EFI_SIZE_TO_PAGES ((sizeof (MP_SYSTEM_DATA))));
  if (mMpSystemData == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SetMem ((VOID *) mMpSystemData, sizeof (MP_SYSTEM_DATA), 0x00);

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuConfigGuid, (VOID *) &mCpuConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuTestConfigGuid, (VOID *) &mCpuTestConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtBasicConfigGuid, (VOID *) &mCpuPowerMgmtBasicConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtCustomConfigGuid, (VOID *) &mCpuPowerMgmtCustomConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gBiosGuardConfigGuid, (VOID *) &BiosGuardConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuConfigLibPreMemConfigGuid, (VOID *) &mCpuConfigLibPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuOverclockingPreMemConfigGuid, (VOID *) &CpuOverClockingPreMemConfig);
  ASSERT_EFI_ERROR (Status);


  if (mCpuConfig->SkipMpInit == 0) {
    ///
    /// Locate CpuMpCpu MpService Ppi
    ///
    Status = PeiServicesLocatePpi (
               &gEfiPeiMpServicesPpiGuid,
               0,
               NULL,
               (VOID **) &gMpServicesPpi);
    ASSERT_EFI_ERROR (Status);
  }

  if (mCpuConfig->SkipMpInit == 0) {
    ///
    /// Fill Cpu MP system data
    ///
    gMpServicesPpi->GetNumberOfProcessors (PeiServices, gMpServicesPpi, (UINTN *)&NumberOfProcessors, (UINTN *)&NumberOfEnabledProcessors);
    Status = FillMpSystemData (NumberOfEnabledProcessors);

    if ((AsmReadMsr64 (MSR_PLATFORM_INFO)) & B_MSR_PLATFORM_INFO_BIOSGUARD_AVAIL) {
      if (CpuSecurityPreMemConfig->BiosGuard) {
        if (IsBiosGuardModuleDebugSigned(BiosGuardConfig->BiosGuardModulePtr)) {
          mCpuTestConfig->DebugInterfaceEnable       = TRUE;
        }
      }
    }

    ///
    /// Initialize feature control structure
    ///
    InitializeFeaturePerSetup ();

    DEBUG((DEBUG_INFO, "SgxInitializationPrePatchLoad Start \n"));
    PostCode (0xC16);
    SgxInitializationPrePatchLoad (SiPreMemPolicyPpi, SiPolicyPpi);

    DEBUG((DEBUG_INFO, "CollectProcessorFeature Start \n"));
    PostCode (0xC17);

    ///
    /// Collect processor supported features on BSP only for Client(not required to run on all APs)
    /// @todo for Server
    ///
    CollectProcessorFeature ();

    DEBUG((DEBUG_INFO, "ProgramProcessorFeature Start \n"));
    PostCode (0xC18);

    ///
    /// Check if PM_TMR emulation is required.
    ///
    CpuFamilyId = GetCpuFamily ();
    CpuStepping = GetCpuStepping ();
    if (IsPchPmTimerEnabled () == FALSE) {
       mPmTimerEmulationEnable = TRUE;
    }

    ///
    /// Program processor supported features on BSP and on all APs
    ///
    ProgramProcessorFeature (SiPreMemPolicyPpi);
    gMpServicesPpi->StartupAllAPs (
                      PeiServices,
                      gMpServicesPpi,
                      (EFI_AP_PROCEDURE) ProgramProcessorFeature,
                      FALSE,
                      0,
                      (VOID *)SiPreMemPolicyPpi
                      );

    DEBUG((DEBUG_INFO, "ProgramProcessorFeature Done\n"));
    PostCode (0xC19);

    ///
    /// Initialize SGX by logical processor.
    ///
    SgxInitializationByLogicalProcessorPrePatchLoad (TRUE);
    gMpServicesPpi->StartupAllAPs (
                      PeiServices,
                      gMpServicesPpi,
                      (EFI_AP_PROCEDURE) SgxInitializationByLogicalProcessorPrePatchLoad,
                      FALSE,
                      0,
                      (VOID *)FALSE
                      );
  }

  ///
  /// Program the OverClocking Lock Bit before 2nd patch load
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_FLEX_RATIO);
  if (CpuOverClockingPreMemConfig->OcLock) {
    TempMsr.Dwords.Low |= B_OVERCLOCKING_LOCK;
  } else {
    TempMsr.Dwords.Low &= ~(B_OVERCLOCKING_LOCK);
  }
  AsmWriteMsr64 (MSR_FLEX_RATIO, TempMsr.Qword);

  ///
  /// Initialize performance and power management features before RESET_CPL at post-memory phase.
  ///
  CpuInitPreResetCpl (PeiServices, SiPolicyPpi);

  if (mCpuConfig->SkipMpInit == 0) {
    ///
    ///  Setting the B_MSR_LT_LOCK_MEMORY_CONFIG_LOCK bit.
    ///
    AsmWriteMsr64 (MSR_LT_LOCK_MEMORY,(AsmReadMsr64 (MSR_LT_LOCK_MEMORY) | B_MSR_LT_LOCK_MEMORY_CONFIG_LOCK));

    DEBUG((DEBUG_INFO, "ReloadMicrocodePatch Start\n"));
    PostCode (0xC40);

    ///
    /// Reload Microcode Patch
    ///
    ReloadMicrocodePatch ();
    gMpServicesPpi->StartupAllAPs (
                      PeiServices,
                      gMpServicesPpi,
                      (EFI_AP_PROCEDURE) ReloadMicrocodePatch,
                      FALSE,
                      0,
                      NULL
                      );

    DEBUG((DEBUG_INFO, "ReloadMicrocodePatch Done\n"));
    PostCode (0xC41);

    DEBUG((DEBUG_INFO, "ApSafePostMicrocodePatchInit Start\n"));
    PostCode (0xC42);

    ApSafePostMicrocodePatchInit ();
    gMpServicesPpi->StartupAllAPs (
                      PeiServices,
                      gMpServicesPpi,
                      (EFI_AP_PROCEDURE) ApSafePostMicrocodePatchInit,
                      FALSE,
                      0,
                      NULL
                      );

    ///
    /// Initialize CPU Data Hob
    ///
    InitializeCpuDataHob ();

    ///
    /// Initialize CPU S3 Resume Data Hob
    ///
    PeiServicesGetBootMode (&BootMode);
    if (BootMode != BOOT_ON_S3_RESUME) {
      Hob = BuildGuidDataHob (
              &gCpuS3ResumeDataHobGuid,
              (VOID *) &mMpSystemData->CpuPrivateData,
              (UINTN) sizeof (CPU_PRIVATE_DATA)
              );
      ASSERT (Hob != NULL);
    }
  }

  DEBUG ((DEBUG_INFO, "Cpu Initialize performance and power management features before RESET_CPL Done\n"));

  DEBUG((DEBUG_INFO, "CpuInit Done \n"));
  PostCode (0xC4F);

  return EFI_SUCCESS;
}
