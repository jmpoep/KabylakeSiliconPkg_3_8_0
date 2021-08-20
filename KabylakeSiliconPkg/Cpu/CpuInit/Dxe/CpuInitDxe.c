/** @file
  Cpu driver, which initializes CPU and implements CPU Architecture
  Protocol as defined in Framework specification.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Protocol/HiiDatabase.h>
#include <Protocol/MpService.h>
#include "CpuInitDxe.h"
#include "Exception.h"
#ifndef MINTREE_FLAG
#include "BiosGuard.h"
#include <Library/BootGuardLib.h>
#include <Private/Library/SoftwareGuardLib.h>
#endif
#include <Private/Library/CpuCommonLib.h>
#include <Private/PowerMgmtNvsStruct.h>
#include <Protocol/DxeSmmReadyToLock.h>

#ifndef MINTREE_FLAG
//
// Private GUID for BIOS Guard initializes
//
extern EFI_GUID gBiosGuardHobGuid;
#endif

#define SAMPLE_TICK_COUNT 1000

extern UINT64                   mValidMtrrAddressMask;
extern UINT64                   mValidMtrrBitsMask;
extern UINT8                    CpuInitDxeStrings[];
extern UINT8                    mDefaultMemoryType;

GLOBAL_REMOVE_IF_UNREFERENCED EFI_METRONOME_ARCH_PROTOCOL      *mMetronome;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                          mIsFlushingGCD = TRUE;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                            mSmmbaseSwSmiNumber;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                          mVariableMtrrChanged;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                          mFixedMtrrChanged;
GLOBAL_REMOVE_IF_UNREFERENCED UINT64                           mCpuFrequency = 0;

GLOBAL_REMOVE_IF_UNREFERENCED EFI_CPU_INTERRUPT_HANDLER        mExternalVectorTable[0x100];
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                          mInterruptState = FALSE;
///
/// The Cpu Init Data Hob
///
GLOBAL_REMOVE_IF_UNREFERENCED CPU_INIT_DATA_HOB                *mCpuInitDataHob   = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_CONFIG_DATA                  *mCpuConfigData    = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED FVID_TABLE                       *mFvidTable        = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_INFO_PROTOCOL                *mCpuInfo;
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                            mCommonFeatures;
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                            mSiliconFeatures;
///
/// The Cpu Architectural Protocol that this Driver produces
///
GLOBAL_REMOVE_IF_UNREFERENCED EFI_CPU_ARCH_PROTOCOL gCpu = {
  FlushCpuDataCache,
  EnableInterrupt,
  DisableInterrupt,
  CpuGetInterruptState,
  Init,
  RegisterInterruptHandler,
  GetTimerValue,
  SetMemoryAttributes,
  1, ///< NumberOfTimers
  4, ///< DmaBufferAlignment
};

/**
  Flush CPU data cache. If the instruction cache is fully coherent
  with all DMA operations then function can just return EFI_SUCCESS.

  @param[in] This                - Protocol instance structure
  @param[in] Start               - Physical address to start flushing from.
  @param[in] Length              - Number of bytes to flush. Round up to chipset
                                   granularity.
  @param[in] FlushType           - Specifies the type of flush operation to perform.

  @retval EFI_SUCCESS           - If cache was flushed
  @exception EFI_UNSUPPORTED    - If flush type is not supported.
  @retval EFI_DEVICE_ERROR      - If requested range could not be flushed.
**/
EFI_STATUS
EFIAPI
FlushCpuDataCache (
  IN EFI_CPU_ARCH_PROTOCOL *This,
  IN EFI_PHYSICAL_ADDRESS  Start,
  IN UINT64                Length,
  IN EFI_CPU_FLUSH_TYPE    FlushType
  )
{
  if (FlushType == EfiCpuFlushTypeWriteBackInvalidate) {
    AsmWbinvd ();
    return EFI_SUCCESS;
  } else if (FlushType == EfiCpuFlushTypeInvalidate) {
    AsmInvd ();
    return EFI_SUCCESS;
  } else {
    return EFI_UNSUPPORTED;
  }
}

/**
  Enables CPU interrupts.

  @param[in] This                - Protocol instance structure

  @retval EFI_SUCCESS           - If interrupts were enabled in the CPU
  @retval EFI_DEVICE_ERROR      - If interrupts could not be enabled on the CPU.
**/
EFI_STATUS
EFIAPI
EnableInterrupt (
  IN EFI_CPU_ARCH_PROTOCOL *This
  )
{
  EnableInterrupts ();
  mInterruptState = TRUE;
  return EFI_SUCCESS;
}

/**
  Disables CPU interrupts.

  @param[in] This                - Protocol instance structure

  @retval EFI_SUCCESS           - If interrupts were disabled in the CPU.
**/
EFI_STATUS
EFIAPI
DisableInterrupt (
  IN EFI_CPU_ARCH_PROTOCOL *This
  )
{
  DisableInterrupts ();

  mInterruptState = FALSE;
  return EFI_SUCCESS;
}

/**
  Return the state of interrupts.

  @param[in] This                - Protocol instance structure
  @param[in] State               - Pointer to the CPU's current interrupt state

  @retval EFI_SUCCESS           - If interrupts were disabled in the CPU.
  @retval EFI_INVALID_PARAMETER - State is NULL.
**/
EFI_STATUS
EFIAPI
CpuGetInterruptState (
  IN EFI_CPU_ARCH_PROTOCOL *This,
  OUT BOOLEAN              *State
  )
{
  if (State == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *State = mInterruptState;
  return EFI_SUCCESS;
}

/**
  Generates an INIT to the CPU

  @param[in] This                - Protocol instance structure
  @param[in] InitType            - Type of CPU INIT to perform

  @retval EFI_SUCCESS           - If CPU INIT occurred. This value should never be seen
  @retval EFI_DEVICE_ERROR      - If CPU INIT failed.
  @exception EFI_UNSUPPORTED    - Requested type of CPU INIT not supported.
**/
EFI_STATUS
EFIAPI
Init (
  IN EFI_CPU_ARCH_PROTOCOL *This,
  IN EFI_CPU_INIT_TYPE     InitType
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Registers a function to be called from the CPU interrupt handler.

  @param[in] This                - Protocol instance structure
  @param[in] InterruptType       - Defines which interrupt to hook.
                                   IA-32 valid range is 0x00 through 0xFF
  @param[in] InterruptHandler    - A pointer to a function of type EFI_CPU_INTERRUPT_HANDLER
                                   that is called when a processor interrupt occurs.
                                   A null pointer is an error condition.

  @retval EFI_SUCCESS            - If handler installed or uninstalled.
  @retval EFI_ALREADY_STARTED    - InterruptHandler is not NULL, and a handler for
                                   InterruptType was previously installed
  @retval EFI_INVALID_PARAMETER  - InterruptHandler is NULL, and a handler for
                                   InterruptType was not previously installed.
  @exception EFI_UNSUPPORTED     - The interrupt specified by InterruptType is not supported.
**/
EFI_STATUS
EFIAPI
RegisterInterruptHandler (
  IN EFI_CPU_ARCH_PROTOCOL     *This,
  IN EFI_EXCEPTION_TYPE        InterruptType,
  IN EFI_CPU_INTERRUPT_HANDLER InterruptHandler
  )
{
  BOOLEAN   State;

  if (InterruptType < 0 || InterruptType > 0xff) {
    return EFI_UNSUPPORTED;
  }

  if (InterruptHandler == NULL && mExternalVectorTable[InterruptType] == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (InterruptHandler != NULL && mExternalVectorTable[InterruptType] != NULL) {
    return EFI_ALREADY_STARTED;
  }

  //
  // State is stored with the current interrupt state from CPU Arch Prot.
  // Keep interrupts disabled until we finish registering.
  //
  (This->GetInterruptState) (This, &State);
  if (State) {
    This->DisableInterrupt (This);
  }

  if (InterruptHandler != NULL) {
    SetInterruptDescriptorTableHandlerAddress ((UINTN) InterruptType);
  } else {
    //
    // Restore the original IDT handler address if InterruptHandler is NULL.
    //
    RestoreInterruptDescriptorTableHandlerAddress ((UINTN) InterruptType);
  }

  mExternalVectorTable[InterruptType] = InterruptHandler;

  if (State) {
    This->EnableInterrupt (This);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
GetTimerValue (
  IN EFI_CPU_ARCH_PROTOCOL *This,
  IN UINT32                TimerIndex,
  OUT UINT64               *TimerValue,
  OUT UINT64 *TimerPeriod  OPTIONAL
  )
/**
  Returns a timer value from one of the CPU's internal timers. There is no
  inherent time interval between ticks but is a function of the CPU frequency.

  @param[in] This                - Protocol instance structure.
  @param[in] TimerIndex          - Specifies which CPU timer is requested.
  @param[in] TimerValue          - Pointer to the returned timer value.
  @param[in] TimerPeriod         - A pointer to the amount of time that passes in femtoseconds (10-15) for each
                                   increment of TimerValue. If TimerValue does not increment at a predictable
                                   rate, then 0 is returned. The amount of time that has passed between two calls to
                                   GetTimerValue() can be calculated with the formula
                                   (TimerValue2 - TimerValue1) * TimerPeriod. This parameter is optional and may be NULL.

  @retval EFI_SUCCESS            - If the CPU timer count was returned.
  @exception EFI_UNSUPPORTED     - If the CPU does not have any readable timers.
  @retval EFI_DEVICE_ERROR       - If an error occurred while reading the timer.
  @retval EFI_INVALID_PARAMETER  - TimerIndex is not valid or TimerValue is NULL.
**/
{
  UINT64 Actual;

  if (TimerValue == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (TimerIndex != 0) {
    return EFI_INVALID_PARAMETER;
  }

  *TimerValue = AsmReadTsc ();

  if (TimerPeriod != NULL) {
    GetActualFrequency (mMetronome, &Actual);
    *TimerPeriod = DivU64x32 (1000000000, (UINT32) Actual);
  }

  return EFI_SUCCESS;
}

/**
  Set memory cacheability attributes for given range of memory

  @param[in] This                - Protocol instance structure
  @param[in] BaseAddress         - Specifies the start address of the memory range
  @param[in] Length              - Specifies the length of the memory range
  @param[in] Attributes          - The memory cacheability for the memory range

  @retval EFI_SUCCESS            - If the cacheability of that memory range is set successfully
  @exception EFI_UNSUPPORTED     - If the desired operation cannot be done
  @retval EFI_INVALID_PARAMETER  - The input parameter is not correct, such as Length = 0
**/
EFI_STATUS
EFIAPI
SetMemoryAttributes (
  IN EFI_CPU_ARCH_PROTOCOL  *This,
  IN EFI_PHYSICAL_ADDRESS   BaseAddress,
  IN UINT64                 Length,
  IN UINT64                 Attributes
  )
{
  EFI_STATUS                Status;
  UINT64                    TempQword;
  UINT32                    MsrNum;
  UINTN                     MtrrNumber;
  BOOLEAN                   Positive;
  BOOLEAN                   OverLap;
#define SKIP_ALIGN_CHECK  0
#if SKIP_ALIGN_CHECK
  UINT32                    Remainder;
#endif
  EFI_MP_SERVICES_PROTOCOL  *MpService;
  EFI_STATUS                Status1;
  MSR_IA32_MTRRCAP_REGISTER MtrrCapMsr;
  EFI_TPL                   OldTpl;

  mFixedMtrrChanged     = FALSE;
  mVariableMtrrChanged  = FALSE;

  MtrrCapMsr.Uint64 = AsmReadMsr64 (MSR_IA32_MTRRCAP);

  if (mIsFlushingGCD) {
    return EFI_SUCCESS;
  }

  TempQword = 0;

  ///
  /// Check for invalid parameter
  ///
  if (Length == 0) {
    return EFI_INVALID_PARAMETER;
  }

  if ((BaseAddress &~mValidMtrrAddressMask) != 0 || (Length &~mValidMtrrAddressMask) != 0) {
    return EFI_UNSUPPORTED;
  }

  switch (Attributes) {
    case EFI_MEMORY_UC:
      Attributes = CACHE_UNCACHEABLE;
      break;

    case EFI_MEMORY_WC:
      Attributes = CACHE_WRITECOMBINING;
      break;

    case EFI_MEMORY_WT:
      Attributes = CACHE_WRITETHROUGH;
      break;

    case EFI_MEMORY_WP:
      Attributes = CACHE_WRITEPROTECTED;
      break;

    case EFI_MEMORY_WB:
      Attributes = CACHE_WRITEBACK;
      break;

    default:
      return EFI_UNSUPPORTED;
  }

  Status1 = gBS->LocateProtocol (
                   &gEfiMpServiceProtocolGuid,
                   NULL,
                   (VOID **) &MpService
                   );

  ///
  /// Raise TPL to avoid interruption because of timer interrupt.
  ///
  OldTpl = gBS->RaiseTPL (TPL_HIGH_LEVEL);

  ///
  /// Check if Fixed MTRR
  ///
  Status = EFI_SUCCESS;
  while ((BaseAddress < (1 << 20)) && (Length > 0) && Status == EFI_SUCCESS) {
    Status = CalculateFixedMtrr (Attributes, &BaseAddress, &Length);
    if (EFI_ERROR (Status)) {
      gBS->RestoreTPL (OldTpl);
      return Status;
    }
  }

  if (mFixedMtrrChanged) {
    ProgramFixedMtrr ();
  }

  if (Length == 0) {
    ///
    /// Just Fixed MTRR. NO need to go through Variable MTRR
    ///
    goto Done;
  }

  ///
  /// since mem below 1m will be override by fixed mtrr, we can set it to 0 to save mtrr.
  ///
  if (BaseAddress == 0x100000) {
    BaseAddress = 0;
    Length += 0x100000;
  }

  ///
  /// Check memory base address alignment
  ///
#if SKIP_ALIGN_CHECK
  DivU64x32Remainder (BaseAddress, (UINT32) Power2MaxMemory (LShiftU64 (Length, 1)), &Remainder);
  if (Remainder != 0) {
    DivU64x32Remainder (BaseAddress, (UINT32) Power2MaxMemory (Length), &Remainder);
    if (Remainder != 0) {
      Status = EFI_UNSUPPORTED;
      goto Done;
    }
  }
#endif

  ///
  /// Check overlap
  ///
  GetMemoryAttribute ();
  OverLap = CheckMemoryAttributeOverlap (BaseAddress, BaseAddress + Length - 1);
  if (OverLap) {
    Status = CombineMemoryAttribute (Attributes, &BaseAddress, &Length);
    if (EFI_ERROR (Status)) {
      goto Done;
    }
    if (Length == 0) {
      ///
      /// combine successfully
      ///
      Status = EFI_SUCCESS;
      goto Done;
    }
  } else {
    if (Attributes == mDefaultMemoryType) {
      Status = EFI_SUCCESS;
      goto Done;
    }
  }

  ///
  /// Program Variable MTRRs
  ///
  if (mUsedMtrr >= MtrrCapMsr.Bits.VCNT) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }

  ///
  /// Find first unused MTRR
  ///
  for (MsrNum = MSR_IA32_MTRR_PHYSBASE0; MsrNum < (MSR_IA32_MTRR_PHYSBASE0 + (MtrrCapMsr.Bits.VCNT * 2) - 1); MsrNum += 2) {
    if ((AsmReadMsr64 (MsrNum + 1) & B_CACHE_MTRR_VALID) == 0) {
      break;
    }
  }

  TempQword = Length;
  if (TempQword == Power2MaxMemory (TempQword)) {
    ProgramVariableMtrr (
      MsrNum,
      BaseAddress,
      Length,
      Attributes
      );
  } else {
    GetDirection (TempQword, &MtrrNumber, &Positive);
    if ((mUsedMtrr + MtrrNumber) > MtrrCapMsr.Bits.VCNT) {
      goto Done;
    }
    if (!Positive) {
      Length = Power2MaxMemory (LShiftU64 (TempQword, 1));
      ProgramVariableMtrr (
        MsrNum,
        BaseAddress,
        Length,
        Attributes
        );
      BaseAddress += TempQword;
      TempQword   = Length - TempQword;
      Attributes  = CACHE_UNCACHEABLE;
    }
    do {
      ///
      /// Find unused MTRR
      ///
      for (; MsrNum < (MSR_IA32_MTRR_PHYSBASE0 + (MtrrCapMsr.Bits.VCNT * 2) - 1); MsrNum += 2) {
        if ((AsmReadMsr64 (MsrNum + 1) & B_CACHE_MTRR_VALID) == 0) {
          break;
        }
      }
      Length = Power2MaxMemory (TempQword);
      ProgramVariableMtrr (
        MsrNum,
        BaseAddress,
        Length,
        Attributes
        );
      BaseAddress += Length;
      TempQword -= Length;
    } while (TempQword);
  }

Done:
  if (!EFI_ERROR (Status1)) {
    if (mVariableMtrrChanged || mFixedMtrrChanged) {
      ///
      /// PERF_START (NULL, L"CacheSync", NULL, 0);
      ///
      ReadMtrrRegisters ();
      Status1 = MpService->StartupAllAPs (
                             MpService,
                             MpMtrrSynchUp,
                             FALSE,
                             NULL,
                             0,
                             NULL,
                             NULL
                             );
      ///
      /// PERF_END (NULL, L"CacheSync", NULL, 0);
      ///
    }
  }

  gBS->RestoreTPL (OldTpl);
  return Status;
}

#ifndef MINTREE_FLAG
/**
  CpuInitOnReadyToLockCallback - Callback will be triggered when OnReadyToLock event is signaled
   - Create SMBIOS Table type - FviSmbiosType
   - Drop into SMM to register IOTRAP for BIOS Guard tools interface

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
CpuInitOnReadyToLockCallback (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  BIOSGUARD_HOB        *BiosGuardHobPtr;
  EFI_BOOT_MODE        BootMode;
  UINT64               MsrValue;
  VOID                *Hob;
  EFI_STATUS           Status;
  VOID                *DxeSmmReadyToLock;

  ///
  /// Account for the initial call from EfiCreateProtocolNotifyEvent
  ///
  Status = gBS->LocateProtocol (
                  &gEfiDxeSmmReadyToLockProtocolGuid,
                  NULL,
                  &DxeSmmReadyToLock
                  );
  if (EFI_ERROR (Status)) {
    return;
  }

  ///
  /// Get CPU Init Data Hob
  ///
  Hob = GetFirstGuidHob (&gCpuInitDataHobGuid);
  if (Hob == NULL) {
    DEBUG ((DEBUG_ERROR, "CPU Data HOB not available\n"));
    return;
  }
  mCpuInitDataHob    = (CPU_INIT_DATA_HOB *) ((UINTN) Hob + sizeof (EFI_HOB_GUID_TYPE));
  ///
  /// Close the event
  ///
  gBS->CloseEvent (Event);

  BootMode = GetBootModeHob ();

  ///
  /// Drop into SMM to register IOTRAP for BIOS Guard tools interface
  ///
  BiosGuardHobPtr = GetFirstGuidHob (&gBiosGuardHobGuid);
  if (BiosGuardHobPtr == NULL) {
    return;
  }

  ///
  /// Writing to this MSR will enable Flash Wear-Out Protection mitigation.
  /// Write to MSR if FlashWearOutProtection policy is enabled.
  /// This MSR is only written to on a non update flow
  /// @note CPU steppings are not enumerated alphabetically
  ///
  if (BootMode != BOOT_ON_FLASH_UPDATE) {
    if (BiosGuardHobPtr->Bgpdt.BiosGuardAttr & EnumFlashwearoutProtection) {
      MsrValue = AsmReadMsr64 (MSR_PLAT_BIOS_INFO_FLAGS);
      MsrValue |= BIT0;
      AsmWriteMsr64 (MSR_PLAT_BIOS_INFO_FLAGS, MsrValue);
    }
  }


  return;
}
#endif //MINTREE_FLAG

/**
  Initialize the state information for the CPU Architectural Protocol

  @param[in] ImageHandle - Image handle of the loaded driver
  @param[in] SystemTable - Pointer to the System Table

  @retval EFI_SUCCESS           - Thread was successfully created
  @retval EFI_OUT_OF_RESOURCES  - Can not allocate protocol data structure
  @retval EFI_DEVICE_ERROR      - Can not create the thread
  @retval EFI_NOT_FOUND         - Can not locate CPU Data HOB
**/
EFI_STATUS
EFIAPI
InitializeCpu (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS        Status;
  EFI_HANDLE        NewHandle1;
  VOID              *Hob;
#ifndef MINTREE_FLAG
  VOID              *Registration;
#endif

  ///
  /// Initialize the Global Descriptor Table
  ///
  InitializeSelectors ();

  ///
  /// Setup Cache attributes and Interrupt Tables
  ///
  PrepareMemory ();

  ///
  /// Initialize Exception Handlers
  /// @todo: Use UefiCpuPkg exception handling to handle both source debug and non-source debug exception handlers.
  ///

  if (PcdGetBool(PcdSourceDebugEnable) == FALSE) {
    InitializeException (&gCpu);
  }

  ///
  /// Install CPU Architectural Protocol
  ///
  NewHandle1  = NULL;
  Status = gBS->InstallProtocolInterface (
                  &NewHandle1,
                  &gEfiCpuArchProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &gCpu
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Refresh memory space attributes according to MTRRs
  ///
  Status          = RefreshGcdMemoryAttributes ();
  mIsFlushingGCD  = FALSE;
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ///
  /// Get CPU Init Data Hob
  ///
  Hob = GetFirstGuidHob (&gCpuInitDataHobGuid);
  if (Hob == NULL) {
    DEBUG ((DEBUG_ERROR, "CPU Data HOB not available\n"));
    return EFI_NOT_FOUND;
  }
  mCpuInitDataHob    = (CPU_INIT_DATA_HOB *) ((UINTN) Hob + sizeof (EFI_HOB_GUID_TYPE));
  mCpuConfigData     = (CPU_CONFIG_DATA *)   (UINTN) mCpuInitDataHob->CpuConfigData;
  mSiliconFeatures   = mCpuInitDataHob->SiliconInfo;
  mFvidTable         = (FVID_TABLE *) (UINTN) mCpuInitDataHob->FvidTable;

  ///
  /// Initialize the global SmmBase SWSMI number
  ///
  mSmmbaseSwSmiNumber = mCpuConfigData->SmmbaseSwSmiNumber;

  Status  = gBS->LocateProtocol (&gEfiMetronomeArchProtocolGuid, NULL, (VOID **) &mMetronome);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ///
  /// Initialize DxeCpuInfo protocol instance and gather CPU information
  ///
  Status = InitCpuInfo ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to initialize DxeCpuInfo\n"));
  }

  ///
  /// Initialize MP Support if necessary
  ///
  Status = InitializeMpSupport ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to initialize MPs\n"));
  }

#ifndef MINTREE_FLAG
  ///
  /// Create an OnReadyToLock protocol callback event for BIOS Guard.
  /// This function causes CpuInitOnReadyToLockCallback() to be executed,
  /// Ensure CpuInitOnReadyToLockCallback() accounts for this initial call.
  ///
  EfiCreateProtocolNotifyEvent (
    &gEfiDxeSmmReadyToLockProtocolGuid,
    TPL_CALLBACK,
    CpuInitOnReadyToLockCallback,
    NULL,
    &Registration
    );
#endif

  CpuAcpiInit (ImageHandle);
  return EFI_SUCCESS;
}

/**
  Returns the actual CPU core frequency in MHz.

  @param[in] Metronome           - Metronome protocol
  @param[in] Frequency           - Pointer to the CPU core frequency

  @retval EFI_SUCCESS            - If the frequency is returned successfully
  @retval EFI_INVALID_PARAMETER  - If the input parameter is wrong
**/
EFI_STATUS
GetActualFrequency (
  IN EFI_METRONOME_ARCH_PROTOCOL *Metronome,
  OUT UINT64                     *Frequency
  )
{
  UINT64     BeginValue;
  UINT64     EndValue;
  UINT64     TotalValue;
  UINT32     TickCount;
  BOOLEAN    InterruptState;
  EFI_STATUS Status;

  if (Metronome == NULL || Frequency == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (mCpuFrequency == 0) {
    ///
    /// In order to calculate the actual CPU frequency, we keep track of the CPU Tsc value (which
    /// increases by 1 for every cycle) for a know period of time. The Metronome is not accurate
    /// for the 1st tick, so I choose to wait for 1000 ticks, thus the error can be control to be
    /// lower than 1%.
    ///
    TickCount = SAMPLE_TICK_COUNT;
    CpuGetInterruptState (&gCpu, &InterruptState);
    if (InterruptState) {
      DisableInterrupt (&gCpu);
    }
    ///
    /// In DxeCis-0.91 specs.
    /// Metronome->WaitForTick is possible for interrupt processing,
    /// or exception processing to interrupt the execution of the WaitForTick() function.
    /// Depending on the hardware source for the ticks, it is possible for a tick to be missed.
    /// This function cannot guarantee that ticks will not be missed.
    ///
    while (TRUE) {
      BeginValue  = AsmReadTsc ();
      Status      = Metronome->WaitForTick (Metronome, TickCount);
      EndValue    = AsmReadTsc ();
      if (!EFI_ERROR (Status)) {
        TotalValue = EndValue - BeginValue;
        break;
      }
    }

    if (InterruptState) {
      EnableInterrupt (&gCpu);
    }

    mCpuFrequency = MultU64x32 (TotalValue, 10);
    mCpuFrequency = DivU64x32 (mCpuFrequency, Metronome->TickPeriod * TickCount);
  }

  *Frequency = mCpuFrequency;

  return EFI_SUCCESS;
}

/**
  Initialize CPU info.

  @retval EFI_SUCCESS          - Successfully prepared.
  @retval EFI_OUT_OF_RESOURCES - Not enough memory to complete the function.
**/
EFI_STATUS
InitCpuInfo (
  VOID
  )
{
  CACHE_DESCRIPTOR_INFO  *CacheInfo;
  CHAR8                  *BrandString;
  EFI_CPUID_REGISTER     CpuidRegs;
  CPUID_CACHE_PARAMS_EAX CacheEax;
  CPUID_CACHE_PARAMS_EBX CacheEbx;
  UINT32                 CacheEcx;
  UINT32                 CpuSignature;
  UINT8                  CacheInfoCount;
  UINT16                 CachePartitions;
  UINT16                 CacheLineSize;
  UINT32                 CacheNumberofSets;
  UINT8                  ThreadsPerCore;
#ifndef MINTREE_FLAG
  UINT64                 MsrData;
#endif
  UINT8                  Index;
  EFI_HANDLE             Handle;
  UINT16                 EnabledThreadsPerCore;
  UINT16                 EnabledCoresPerDie;

  Handle                = NULL;

  ///
  /// Install CPU info protocol
  ///
  mCpuInfo                             = AllocateZeroPool (sizeof (CPU_INFO_PROTOCOL));
  if (mCpuInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  mCpuInfo->Revision                   = CPU_INFO_PROTOCOL_REVISION;
  mCpuInfo->CpuCommonFeatures          = mCommonFeatures | (mSiliconFeatures << 10);
  mCpuInfo->CpuInfo                    = AllocateZeroPool (sizeof (CPU_INFO));
  if (mCpuInfo->CpuInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  mCpuInfo->CpuInfo->BrandString       = AllocateZeroPool (49 * sizeof (CHAR8));
  if (mCpuInfo->CpuInfo->BrandString == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  mCpuInfo->SmramCpuInfo               = AllocateZeroPool (sizeof (SMRAM_CPU_INFO));
  if (mCpuInfo->SmramCpuInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  mCpuInfo->SgxInfo                    = AllocateZeroPool (sizeof (SGX_INFO));
  if (mCpuInfo->SgxInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
#ifndef MINTREE_FLAG
  MsrData = AsmReadMsr64 (MSR_UCODE_CR_BIOS_SE_SVN);
  mCpuInfo->SgxInfo->SgxSinitNvsData = MsrData;
#endif

  ///
  /// Get Cache Descriptors.
  ///
  CacheInfoCount = 0;
  do {
    AsmCpuidEx (CPUID_CACHE_PARAMS, CacheInfoCount, &CacheEax.Uint32, NULL, NULL, NULL);
    CacheInfoCount++;
  } while (CacheEax.Bits.CacheType != 0);

  DEBUG ((DEBUG_INFO, "CacheInfoCount = %x\n", CacheInfoCount));
  mCpuInfo->CpuInfo->CacheInfo = AllocateZeroPool (CacheInfoCount * sizeof (CACHE_DESCRIPTOR_INFO));
  if (mCpuInfo->CpuInfo->CacheInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  mCpuInfo->CpuInfo->MaxCacheSupported  = CacheInfoCount - 1; // Subtract 1 because there are 2 counts for L1 (Data and Code).
  mCpuInfo->CpuInfo->SmmbaseSwSmiNumber = mSmmbaseSwSmiNumber;
  mCpuInfo->CpuInfo->NumberOfPStates    = mFvidTable[0].FvidHeader.EistStates;;

  BrandString = mCpuInfo->CpuInfo->BrandString;
  CacheInfo   = mCpuInfo->CpuInfo->CacheInfo;

  ///
  /// Get Brand string
  ///
  AsmCpuid (CPUID_BRAND_STRING1, &CpuidRegs.RegEax, &CpuidRegs.RegEbx, &CpuidRegs.RegEcx, &CpuidRegs.RegEdx);
  *(UINT32*) BrandString = CpuidRegs.RegEax; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEbx; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEcx; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEdx; BrandString +=4;

  AsmCpuid (CPUID_BRAND_STRING2, &CpuidRegs.RegEax, &CpuidRegs.RegEbx, &CpuidRegs.RegEcx, &CpuidRegs.RegEdx);
  *(UINT32*) BrandString = CpuidRegs.RegEax; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEbx; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEcx; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEdx; BrandString +=4;

  AsmCpuid (CPUID_BRAND_STRING3, &CpuidRegs.RegEax, &CpuidRegs.RegEbx, &CpuidRegs.RegEcx, &CpuidRegs.RegEdx);
  *(UINT32*) BrandString = CpuidRegs.RegEax; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEbx; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEcx; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEdx; BrandString +=4;
  *BrandString = '\0';
  ///
  /// Remove leading spaces. After removing leading spaces, the Brand String can not be freed. However, it should never be freed.
  ///
  while (*mCpuInfo->CpuInfo->BrandString == ' ') {
    ++mCpuInfo->CpuInfo->BrandString;
  }

  ///
  /// Get information on enabled threads, cores, dies and package for the CPU(s) on this platform
  ///
  GetEnabledCount (&EnabledThreadsPerCore, &EnabledCoresPerDie, NULL, NULL);

  ///
  /// Gather CPU info
  ///
  AsmCpuid (CPUID_VERSION_INFO, &CpuSignature, NULL, &CpuidRegs.RegEcx, &CpuidRegs.RegEdx);
  mCpuInfo->CpuInfo->CpuSignature               = CpuSignature;
  mCpuInfo->CpuInfo->Features                   = LShiftU64 (CpuidRegs.RegEcx, 32) + CpuidRegs.RegEdx;

  AsmCpuidEx (CPUID_EXTENDED_TOPOLOGY, 0, NULL, &CpuidRegs.RegEbx, NULL, NULL);
  mCpuInfo->CpuInfo->NumSupportedThreadsPerCore = (UINT8) CpuidRegs.RegEbx;
  ThreadsPerCore = (UINT8) CpuidRegs.RegEbx;

  AsmCpuidEx (CPUID_EXTENDED_TOPOLOGY, 1, NULL, &CpuidRegs.RegEbx, NULL, NULL);
  mCpuInfo->CpuInfo->NumSupportedCores          = (UINT8) (CpuidRegs.RegEbx / ThreadsPerCore);

  mCpuInfo->CpuInfo->NumCores                   = (UINT8) EnabledCoresPerDie;
  mCpuInfo->CpuInfo->NumHts                     = (UINT8) EnabledThreadsPerCore;
  mCpuInfo->CpuInfo->IntendedFreq               = (10000 * (((UINT32) AsmReadMsr64 (MSR_PLATFORM_INFO) >> 8) & 0xFF)) /100;
  mCpuInfo->CpuInfo->Voltage                    = 0;

  for (Index = 0; Index < CacheInfoCount; Index++) {
    AsmCpuidEx (CPUID_CACHE_PARAMS, Index, &CacheEax.Uint32, &CacheEbx.Uint32, &CacheEcx, NULL);
    CacheInfo[Index].Type = (UINT8) CacheEax.Bits.CacheType;
    CacheInfo[Index].Level = (UINT8) CacheEax.Bits.CacheLevel;
    CacheInfo[Index].Associativity = (UINT16) (CacheEbx.Bits.Ways + 1);
    ///
    /// Determine Cache Size in Bytes = (Associativity) * (Partitions + 1) * (Line_Size + 1) * (Sets + 1)= (EBX[31:22] + 1) * (EBX[21:12] + 1) * (EBX[11:0] + 1) * (ECX + 1)
    ///
    CachePartitions = (UINT16) (CacheEbx.Bits.LinePartitions + 1);
    CacheLineSize = (UINT16) (CacheEbx.Bits.LineSize + 1);
    CacheNumberofSets = CacheEcx + 1;
    CacheInfo[Index].Size = (UINT32) ((CacheInfo[Index].Associativity *  CachePartitions * CacheLineSize * CacheNumberofSets) /1024);
  }

  gBS->InstallMultipleProtocolInterfaces (
         &Handle,
         &gCpuInfoProtocolGuid,
         mCpuInfo,
         NULL
         );

  return EFI_SUCCESS;
}
