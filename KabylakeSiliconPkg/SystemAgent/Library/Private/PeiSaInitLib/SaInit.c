/** @file
  The PEIM implements the SA PEI Initialization.

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
#include <Library/PeiServicesLib.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Ppi/MemoryDiscovered.h>
#include <Ppi/EndOfPeiPhase.h>
#include <Library/MmPciLib.h>
#include <CpuRegs.h>
#include <PcieRegs.h>
#include <CpuAccess.h>
#include <Private/SaConfigHob.h>
#include <Library/CpuPlatformLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/CpuMailboxLib.h>

#include <Private/Library/SaInitLib.h>
#include <Private/Library/SkyCamInitLib.h>
#include <Private/Library/SaOcInitLib.h>
#include <Private/Library/GmmInitLib.h>
#include <Private/Library/GraphicsInitLib.h>
#include <Private/Library/VtdInitLib.h>
#include <Private/Library/SaPcieInitLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/ConfigBlockLib.h>
#include <Private/Library/DisplayInitLib.h>
#include <Library/PostCodeLib.h>

#ifndef FSP_FLAG
#include <Library/SmmAccessLib.h>
#endif

typedef struct {
  UINT8 DeviceNumber;
  UINT8 FunctionNumber;
  UINT8 SvidRegOffset;
} SA_SVID_SID_INIT_ENTRY;

/*
  Required BIOS configurations for PTM
  System BIOS must set bit 5 of 0x5880 register to lock the configuration.

  System Agent Configuration Locking
  For reliable operation and security, System BIOS must set the following bits:
   1. Lock GGC from writes by setting the B0.D0.F0.R050 [0] = 1b
   2. Lock PAVP settings by setting MCHBAR offset 5500h [0] = 1b
   3. Lock DPR by setting the B0.D0.F0.R05Ch [0] = 1b
   4. Lock ME memory range configuration by setting the B0.D0.F0.R078h [10] = 1b
   5. Lock remap base and limit by setting the B0.D0.F0.R090h [0] = 1b and
      B0.D0.F0.R098h [0] = 1b
   6. Lock TOM by setting the B0.D0.F0.R0A0h [0] = 1b
   7. Lock TOUUD by setting the B0.D0.F0.R0A8h [0] = 1b
   8. Lock BDSM by setting the B0.D0.F0.R0B0h [0] = 1b
   9. Lock BGSM by setting the B0.D0.F0.R0B4h [0] = 1b
   10. Lock TSEG Memory Base by setting the B0.D0.F0.R0B8h [0] = 1b
   11. Lock TOLUD by setting the B0.D0.F0.R0BCh [0] = 1b
   12. Lock Memory controller configuration by setting the MCHBAR offset 50FCh [7:0] = 8Fh
   13. Lock primary channel arbiter weights by setting the MCHBAR offset 7000h [31] = 1b
       MCHBAR offset 77FCh [0] = 1b MCHBAR offset 7BFCh [0] = 1b and MCHBAR offset 6800h [31] = 1b
   14. Lock UMA GFX by setting the MCHBAR offset 6020h [0] = 1b
   15. Lock VTDTRK by setting the MCHBAR offset 63FCh [0] = 1b
   16. Read and write back MCHBAR offset 6030h [31:0].
   17. Read and write back MCHBAR offset 6034h [31:0].
*/
//
// BaseAddr 0 for mSaSecurityRegisters means registers of B0: D0: F0.
//
GLOBAL_REMOVE_IF_UNREFERENCED BOOT_SCRIPT_REGISTER_SETTING mSaSecurityRegisters[] = {
                 {0,  0x0050,  0xFFFFFFFF,  BIT0},
                 {0,  0x005C,  0xFFFFFFFF,  BIT0},
                 {0,  0x0078,  0xFFFFFFFF,  BIT10},
                 {0,  0x0090,  0xFFFFFFFF,  BIT0},
                 {0,  0x0098,  0xFFFFFFFF,  BIT0},
                 {0,  0x00A0,  0xFFFFFFFF,  BIT0},
                 {0,  0x00A8,  0xFFFFFFFF,  BIT0},
                 {0,  0x00B0,  0xFFFFFFFF,  BIT0},
                 {0,  0x00B4,  0xFFFFFFFF,  BIT0},
                 {0,  0x00B8,  0xFFFFFFFF,  BIT0},
                 {0,  0x00BC,  0xFFFFFFFF,  BIT0},
  { (UINT32) FixedPcdGet64 (PcdMchBaseAddress),  0x5500,  0xFFFFFFFF,  BIT0},
  { (UINT32) FixedPcdGet64 (PcdMchBaseAddress),  0x50FC,  0xFFFFFFFF,  0x8F},
  { (UINT32) FixedPcdGet64 (PcdMchBaseAddress),  0x7000,  0xFFFFFFFF,  BIT31},
  { (UINT32) FixedPcdGet64 (PcdMchBaseAddress),  0x77FC,  0xFFFFFFFF,  BIT0},
  { (UINT32) FixedPcdGet64 (PcdMchBaseAddress),  0x7BFC,  0xFFFFFFFF,  BIT0},
  { (UINT32) FixedPcdGet64 (PcdMchBaseAddress),  0x6800,  0xFFFFFFFF,  BIT31},
  { (UINT32) FixedPcdGet64 (PcdMchBaseAddress),  0x6020,  0xFFFFFFFF,  BIT0},
  { (UINT32) FixedPcdGet64 (PcdMchBaseAddress),  0x63FC,  0xFFFFFFFF,  BIT0},
  { (UINT32) FixedPcdGet64 (PcdMchBaseAddress),  0x6030,  0xFFFFFFFF,  0},
  { (UINT32) FixedPcdGet64 (PcdMchBaseAddress),  0x6034,  0xFFFFFFFF,  0},
  { (UINT32) FixedPcdGet64 (PcdMchBaseAddress),  0x5880,  0xFFFFFFFF,  BIT5}
};


/**
  Update SA Hobs in PostMem

  @param[in]  Vtd                 - Instance of VTD_CONFIG
  @param[in]  GtConfig            - Instance of GRAPHICS_PEI_PREMEM_CONFIG
  @param[in]  PciePeiPreMemConfig - Instance of PCIE_CONFIG
  @param[in]  MiscPeiConfig       - Instance of SA_MISC_PEI_CONFIG
  @retval EFI_SUCCESS
**/
EFI_STATUS
UpdateSaHobPostMem (
  IN       VTD_CONFIG                  *Vtd,
  IN       GRAPHICS_PEI_PREMEM_CONFIG  *GtPreMemConfig,
  IN       PCIE_PEI_PREMEM_CONFIG      *PciePeiPreMemConfig,
  IN       PCIE_PEI_CONFIG             *PciePeiConfig,
  IN       SA_MISC_PEI_CONFIG          *MiscPeiConfig
  )
{
  SA_CONFIG_HOB               *SaConfigHob;
  UINT8                       Func;

  ///
  /// Locate HOB for SA Config Data
  ///
  SaConfigHob = (SA_CONFIG_HOB *) GetFirstGuidHob (&gSaConfigHobGuid);
  if (SaConfigHob != NULL) {
    SaConfigHob->InitPcieAspmAfterOprom = (BOOLEAN) (PciePeiPreMemConfig->InitPcieAspmAfterOprom);
    SaConfigHob->ApertureSize = (UINT8) (GtPreMemConfig->ApertureSize);

    ///
    /// Init SaConfigHob->Vtd
    ///
    SaConfigHob->VtdData.VtdDisable = (BOOLEAN) Vtd->VtdDisable;
    SaConfigHob->VtdData.BaseAddress[0] = Vtd->BaseAddress[0];
    SaConfigHob->VtdData.BaseAddress[1] = Vtd->BaseAddress[1];
    SaConfigHob->VtdData.X2ApicOptOut = (BOOLEAN) Vtd->X2ApicOptOut;

    ///
    /// Init Other Hob fields
    ///
    SaConfigHob->CridEnable = (BOOLEAN) (UINTN) MiscPeiConfig->CridEnable;
    SaConfigHob->SkipPamLock = (BOOLEAN) (UINTN) MiscPeiConfig->SkipPamLock;
    ///
    /// Get PegMaxPayload value based on MPS policy
    ///
    for (Func = 0; Func < SA_PEG_MAX_FUN; Func++) {
      SaConfigHob->PegMaxPayload[Func] = PciePeiConfig->PegMaxPayload[Func];
    }
    DEBUG ((DEBUG_INFO, "PostMem SA Data HOB updated\n"));
  }
  return EFI_SUCCESS;
}


/**
  Function to handle SA at end of PEI

  @retval None

**/
EFI_STATUS
EFIAPI
SaOnEndOfPei (
  VOID
  )
{
  EndOfPeiCheckAndForceVddOn ();
  SaS3ResumeAtEndOfPei ();
  return EFI_SUCCESS;
}

///
/// Functions
///
/**
  This function handles SA S3 resume task

  @retval EFI_STATUS       - Always return EFI_SUCCESS
**/
EFI_STATUS
SaS3ResumeAtEndOfPei (
  VOID
  )
{
  EFI_BOOT_MODE               BootMode;
  EFI_STATUS                  Status;
#ifndef FSP_FLAG
  SI_POLICY_PPI               *SiPolicyPpi;
  SA_MISC_PEI_CONFIG          *MiscPeiConfig;
  BOOLEAN                     SkipPamLock;
#endif // FSP_FLAG

  Status = PeiServicesGetBootMode (&BootMode);
  DEBUG ((DEBUG_INFO, "[SA] BootMode = %X\n", BootMode));
  if ((Status != EFI_SUCCESS) || (BootMode != BOOT_ON_S3_RESUME)) {
    return EFI_SUCCESS;
  }
  DEBUG ((DEBUG_INFO, "SaS3ResumeAtEndOfPei Callback Entry\n"));
  PostCode (0xA70);
  //
  // SA S3 tasks that must be done after S3 Boot Script Restore finished.
  //
#ifndef FSP_FLAG
  //
  // In FSP S3 resume path, PAM lock is took care by Notify Phase API, so skipped it here.
  //
  SiPolicyPpi = NULL;
  MiscPeiConfig = NULL;
  SkipPamLock = FALSE;

  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  if ((Status == EFI_SUCCESS) && (SiPolicyPpi != NULL)) {
    Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaMiscPeiConfigGuid, (VOID *) &MiscPeiConfig);
    if (Status == EFI_SUCCESS) {
      SkipPamLock  = (BOOLEAN) (UINTN) MiscPeiConfig->SkipPamLock;
    }
  }

  if (SkipPamLock == FALSE) {
    DEBUG ((DEBUG_INFO, "S3 PAM_LOCK!!\n"));
    MmioOr32 ((MmPciBase (0, 0, 0)) + R_SA_PAM0, BIT0);
  }
#endif // FSP_FLAG

  DEBUG ((DEBUG_INFO, "SaS3ResumeAtEndOfPei Callback Exit\n"));
  PostCode (0xA7F);
  return EFI_SUCCESS;
}

/**
  This function does SA security lock
**/
VOID
SaSecurityLock (
  VOID
  )
{
  UINT8                      Index;
  UINT32                     BaseAddress;
  UINT32                     RegOffset;
  UINT32                     Data32And;
  UINT32                     Data32Or;
  SI_PREMEM_POLICY_PPI       *SiPreMemPolicyPpi;
  SI_POLICY_PPI              *SiPolicyPpi;
  SA_MISC_PEI_PREMEM_CONFIG  *MiscPeiPreMemConfig;
  SA_MISC_PEI_CONFIG         *MiscPeiConfig;
  BOOLEAN                    Device4Enable;
  EFI_STATUS                 Status;
  UINT8                      LockPTMregs;
  UINT64                     DmiBar;

  DEBUG ((DEBUG_INFO, "SaSecurityLock Start\n"));
  PostCode (0xA50);
  Device4Enable = FALSE;
  LockPTMregs = 1;

  ///
  /// 17.2 System Agent Security Lock configuration
  ///
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  if ((Status == EFI_SUCCESS) && (SiPolicyPpi != NULL)) {
    Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaMiscPeiConfigGuid, (VOID *)&MiscPeiConfig);
    if (Status == EFI_SUCCESS) {
      Device4Enable = (UINT8) (UINTN) MiscPeiConfig->Device4Enable;
    }
  }
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  if ((Status == EFI_SUCCESS) && (SiPolicyPpi != NULL)) {
    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSaMiscPeiPreMemConfigGuid, (VOID *) &MiscPeiPreMemConfig);
    if (Status == EFI_SUCCESS) {
      LockPTMregs = MiscPeiPreMemConfig->LockPTMregs;
    }
  }

  DEBUG ((DEBUG_INFO, "Initializing SaSecurityLock\n"));
  for (Index = 0; Index < (sizeof (mSaSecurityRegisters) / sizeof (BOOT_SCRIPT_REGISTER_SETTING)); Index++) {
    BaseAddress = mSaSecurityRegisters[Index].BaseAddr;
    RegOffset   = mSaSecurityRegisters[Index].Offset;
    Data32And   = mSaSecurityRegisters[Index].AndMask;
    Data32Or    = mSaSecurityRegisters[Index].OrMask;
    if (BaseAddress != (UINT32) PcdGet64 (PcdMchBaseAddress)) {
      BaseAddress = MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN);
    }
    if (Device4Enable == TRUE) {
      if (RegOffset ==  0x50FC) {
        Data32Or = 0x87; ///< unlock bit3 if Device (0,4,0) is enabled.
      }
    }
    if (LockPTMregs == 0) {
      if (RegOffset ==  0x5880) {
        continue;
      }
    }
    MmioAndThenOr32 (BaseAddress + RegOffset, Data32And, Data32Or);
  }
  ///
  /// Lock processor/chipset BAR registers, This has moved to CPU code for SoftwareGuard support
  ///
  ///
  /// Set DMI PCIELOCK2.LOCK_GENERAL2
  ///
  DmiBar = (MmioRead32 (MmPciBase (SA_MC_BUS, 0, 0) + R_SA_DMIBAR) &~BIT0) + LShiftU64(MmioRead32 (MmPciBase (SA_MC_BUS, 0, 0) + R_SA_DMIBAR + 4), 32);
  MmioOr32 ((UINTN) DmiBar + R_SA_DMIBAR_PCIELOCK2_OFFSET, BIT0);
  DEBUG ((DEBUG_INFO, "SaSecurityLock End\n"));
  PostCode (0xA5F);
}

/**
    Program SA devices Subsystem Vendor Identifier (SVID) and Subsystem Identifier (SID).

  @param[in] MiscPeiConfig - Instance of SA_MISC_PEI_CONFIG
**/
VOID
ProgramSvidSid (
  IN    SA_MISC_PEI_CONFIG          *MiscPeiConfig
  )
{
  UINT8                         Index;
  UINT8                         BusNumber;
  UINTN                         PciEAddressBase;
  UINT8                         DeviceNumber;
  UINT8                         FunctionNumber;
  UINT8                         SvidRegOffset;
  UINT16                        Data16;
  STATIC SA_SVID_SID_INIT_ENTRY SvidSidInitTable[] = {
    {
      0,
      0,
      PCI_SVID_OFFSET
    },
    {
      1,
      0,
      R_SA_PEG_SS_OFFSET
    },
    {
      1,
      1,
      R_SA_PEG_SS_OFFSET
    },
    {
      1,
      2,
      R_SA_PEG_SS_OFFSET
    },
    {
      2,
      0,
      PCI_SVID_OFFSET
    },
    {
      5,
      0,
      PCI_SVID_OFFSET
    },
    {
      8,
      0,
      PCI_SVID_OFFSET
    },
    {
      4,
      0,
      PCI_SVID_OFFSET
    },
    {
      7,
      0,
      PCI_SVID_OFFSET
    }
  };

  if ((MiscPeiConfig->DefaultSvidSid.SubSystemVendorId != 0) ||
      (MiscPeiConfig->DefaultSvidSid.SubSystemId != 0)
      ) {
    for (Index = 0; Index < (sizeof (SvidSidInitTable) / sizeof (SA_SVID_SID_INIT_ENTRY)); Index++) {
      BusNumber       = 0;
      DeviceNumber    = SvidSidInitTable[Index].DeviceNumber;
      FunctionNumber  = SvidSidInitTable[Index].FunctionNumber;
      SvidRegOffset   = SvidSidInitTable[Index].SvidRegOffset;
      PciEAddressBase = (UINT32) MmPciBase (BusNumber, DeviceNumber, FunctionNumber);
      ///
      /// Skip if the device is disabled
      ///
      if (MmioRead16 (PciEAddressBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
        continue;
      }
      ///
      /// Program SA devices Subsystem Vendor Identifier (SVID)
      ///
      Data16 = MiscPeiConfig->DefaultSvidSid.SubSystemVendorId;
      MmioWrite16 (
        (UINTN) (PciEAddressBase + SvidRegOffset),
        Data16
        );

      ///
      /// Program SA devices Subsystem Identifier (SID)
      ///
      Data16 = MiscPeiConfig->DefaultSvidSid.SubSystemId;
      MmioWrite16 (
        (UINTN) (PciEAddressBase + SvidRegOffset + 2),
        Data16
        );
    }
  }

  return;
}

/**
This function performs SA internal devices enabling/disabling

@param[in] MiscPeiConfig - Instance of SA_MISC_PEI_CONFIG
@param[in] SkyCamPolicy - Instance of SKYCAM_CONFIG
@param[in] GmmConfig - Instance of GMM_CONFIG

**/
VOID
DeviceConfigure (
  IN    SA_MISC_PEI_CONFIG      *MiscPeiConfig,
  IN    SKYCAM_CONFIG           *SkyCamPolicy,
  IN    GMM_CONFIG              *GmmConfig
  )
{
  UINTN      McD0BaseAddress;
  UINT32     DevEn;

  McD0BaseAddress = MmPciBase (SA_MC_BUS, 0, 0);
  DevEn = MmioRead32 (McD0BaseAddress + R_SA_DEVEN);
  ///
  /// Enable/Disable CHAP device (B0,D7,F0).
  ///
  if (MiscPeiConfig->ChapDeviceEnable) {
    DevEn |= B_SA_DEVEN_D7EN_MASK;
  } else {
    DevEn &= ~B_SA_DEVEN_D7EN_MASK;
  }
  ///
  /// Enable/Disable Thermal device (B0,D4,F0).
  ///
  if (MiscPeiConfig->Device4Enable) {
    DevEn |= B_SA_DEVEN_D4EN_MASK;
  } else {
    DevEn &= ~B_SA_DEVEN_D4EN_MASK;
  }
  ///
  /// Enable/Disable SkyCam device (B0,D5,F0).
  ///
  if (SkyCamPolicy->SaImguEnable) {
    DevEn |= B_SA_DEVEN_D5EN_MASK;
  } else {
    DevEn &= ~B_SA_DEVEN_D5EN_MASK;
  }
  ///
  /// Enable/Disable GMM device (B0,D8,F0).
  ///
  if (GmmConfig->GmmEnable) {
    DevEn |= B_SA_DEVEN_D8EN_MASK;
  } else {
    DevEn &= ~B_SA_DEVEN_D8EN_MASK;
  }
  MmioWrite32 (McD0BaseAddress + R_SA_DEVEN, DevEn);
  return;
}

/**
  SA late PEI Initialization.

  @retval EFI_SUCCESS           Function executed successfully
  @retval EFI_NOT_FOUND         The required PPI could not be located.
**/
EFI_STATUS
EFIAPI
SaInit (
  VOID
  )
{
  EFI_STATUS                   Status;
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  SI_POLICY_PPI               *SiPolicyPpi;
  SKYCAM_CONFIG               *SkyCamPolicy;
  SA_MISC_PEI_CONFIG          *MiscPeiConfig;
  PCIE_PEI_PREMEM_CONFIG      *PciePeiPreMemConfig;
  PCIE_PEI_CONFIG             *PciePeiConfig;
  GRAPHICS_PEI_PREMEM_CONFIG  *GtPreMemConfig;
  GRAPHICS_PEI_CONFIG         *GtConfig;
  VTD_CONFIG                  *Vtd;
  GMM_CONFIG                  *GmmConfig;
  UINT32                      MchBar;
  CPU_SKU                     CpuSku;
  EFI_PHYSICAL_ADDRESS        Tolud;

  CpuSku = GetCpuSku ();

  MchBar = MmioRead32 (MmPciBase (SA_MC_BUS, 0, 0) + R_SA_MCHBAR) &~BIT0;

  DEBUG ((DEBUG_INFO, "PostMem SaInit Entry\n"));

  //
  // Reserve the 0x40000000 ~ 0x403FFFFF to prevent other driver use this memory range
  //
  Tolud = MmioRead32 (MmPciBase (SA_MC_BUS, 0, 0) + R_SA_TOLUD) & B_SA_TOLUD_TOLUD_MASK;
  if (Tolud >= BASE_1GB + SIZE_4MB) {
    BuildMemoryAllocationHob (
      BASE_1GB,
      SIZE_4MB,
      EfiReservedMemoryType
    );
  }

  PostCode (0xA00);
  ///
  /// Get policy settings through the SiSaPolicyPpi
  ///
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if ((Status != EFI_SUCCESS) || (SiPolicyPpi == NULL)) {
    return EFI_NOT_FOUND;
  }
  ///
  /// Get policy settings through the SiPreMemPolicyPpi
  ///
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if ((Status != EFI_SUCCESS) || (SiPreMemPolicyPpi == NULL)) {
    return EFI_NOT_FOUND;
  }
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSkyCamConfigGuid, (VOID *) &SkyCamPolicy);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaMiscPeiConfigGuid, (VOID *) &MiscPeiConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSaPciePeiPreMemConfigGuid, (VOID *) &PciePeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaPciePeiConfigGuid, (VOID *) &PciePeiConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gVtdConfigGuid, (VOID *) &Vtd);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGraphicsPeiConfigGuid, (VOID *) &GtConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGmmConfigGuid, (VOID *) &GmmConfig);
  ASSERT_EFI_ERROR (Status);


  ///
  /// Check and Enable Panel Power (Vdd Bit)
  ///
  PostMemCheckAndForceVddOn (GtPreMemConfig, GtConfig);

  ///
  /// SA device configuration
  ///
  DEBUG ((DEBUG_INFO, "DeviceConfigure Start\n"));
  PostCode (0xA01);
  DeviceConfigure (MiscPeiConfig, SkyCamPolicy, GmmConfig);

  ///
  /// Update SA HOBs in PostMem
  ///
  DEBUG ((DEBUG_INFO, "UpdateSaHobPostMem Start\n"));
  PostCode (0xA02);
  UpdateSaHobPostMem (Vtd, GtPreMemConfig, PciePeiPreMemConfig, PciePeiConfig, MiscPeiConfig);

  ///
  /// Initialize PEI Display
  ///
  DEBUG ((DEBUG_INFO, "Initializing Pei Display\n"));
  PostCode (0xA03);
  PeiDisplayInit (GtPreMemConfig, GtConfig);

  ///
  /// Initialize SA SkyCam Device
  ///
  DEBUG ((DEBUG_INFO, "Initializing SA SkyCam device\n"));
  PostCode (0xA14);
  SkyCamInit (SkyCamPolicy);

  ///
  /// Initialize SA GMM Device
  ///
  DEBUG ((DEBUG_INFO, "Initializing SA GMM device\n"));
  PostCode (0xA16);
  GmmInit (GmmConfig);

  ///
  /// Internal devices and Misc configurations.
  ///
  DEBUG ((DEBUG_INFO, "Internal Device and Misc Configurations\n"));
  PostCode (0xA18);
  ProgramSvidSid (MiscPeiConfig);


  ///
  /// PciExpress PostMem Initialization
  ///
  DEBUG ((DEBUG_INFO, "Initializing PciExpressInitPostMem\n"));
  PostCode (0xA20);
  PciExpressInitPostMem (PciePeiPreMemConfig, PciePeiConfig);

  ///
  /// Initialize VT-d
  ///
  DEBUG ((DEBUG_INFO, "Initializing Vtd\n"));
  PostCode (0xA30);
  VtdInit (Vtd, MiscPeiConfig);

  ///
  /// PAVP Initialization
  ///
  DEBUG ((DEBUG_INFO, "Initializing Pavp\n"));
  PostCode (0xA32);
  PavpInit (GtConfig, MiscPeiConfig);

  if ((CpuSku == EnumCpuUlx) || (CpuSku == EnumCpuUlt)) {
    ///
    ///
    MmioAnd32 ((UINTN) MchBar + 0x7060, 0xFFFFFFFE);
    MmioAnd32 ((UINTN) MchBar + 0x7070, 0xFFFFFFFE);
    MmioAnd32 ((UINTN) MchBar + 0x7080, 0xFFFFFFFE);
  }

#ifndef FSP_FLAG
  ///
  /// Install SMM Access PPI
  ///
  DEBUG ((DEBUG_INFO, "PeiInstallSmmAccessPpi Start\n"));
  PostCode (0xA34);
  PeiInstallSmmAccessPpi ();
#endif

  ///
  /// EDRAM J/K/M/N Step Workaround - send the mailbox command/set MMIO register
  ///
  if ((AsmReadMsr64 (MSR_PLATFORM_INFO) & B_PLATFORM_INFO_EDRAM_EN) == B_PLATFORM_INFO_EDRAM_EN) {
    DEBUG ((DEBUG_INFO, "EdramWa Start\n"));
    PostCode (0xA36);
    EdramWa (MiscPeiConfig);
  }
  DEBUG((DEBUG_INFO, "Post-Mem SaInit Exit\n"));
  PostCode (0xA4F);

  return EFI_SUCCESS;
}

/**
  Print SA PCI space in Debug log.

  @retval None
**/
VOID
SaPciPrint (
  VOID
  )
{
  UINTN PciBase;
  UINT8 Device;
  UINT8 i;
  UINT8 j;

  for (Device = 0; Device <= 8; Device++) {
    if ((PcdGetBool (PcdSaPciPrint)) || (Device == 0) || (Device == 2)) {
      PciBase = MmPciBase (0, Device, 0);
      if (MmioRead16 (PciBase) != 0xFFFF) {
        DEBUG ((DEBUG_INFO, "\nPrinting PCI space for device %x\n  ", Device));
        for (i = 0; i <= 0xF ; i++) {
          DEBUG ((DEBUG_INFO,"  %2X",i));
        }
        for (i = 0; i <= 0xF; i++) {
          DEBUG ((DEBUG_INFO, "\n%2X", (i * 0x10)));
          for (j = 0; j <= 0xF; j++) {
            DEBUG ((DEBUG_INFO, "  %2X", MmioRead8 (PciBase + (i * 0x10) + j)));
          }
        }
      }
    }
  }

  DEBUG ((DEBUG_INFO, "\n"));
}
/**
  BIOS_RESET_CPL bit is set for processor to activate the power and thermal management
  features on the platform.

  @retval EFI_SUCCESS
**/
EFI_STATUS
SaResetComplete (
  VOID
  )
{
  EFI_STATUS                  Status;
  UINT32                      MchBar;
  UINT32                      Data32And;
  UINT32                      Data32Or;
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  SI_POLICY_PPI               *SiPolicyPpi;
  SA_MISC_PEI_CONFIG          *MiscPeiConfig;
  GRAPHICS_PEI_PREMEM_CONFIG  *GtPreMemConfig;
  GRAPHICS_PEI_CONFIG         *GtConfig;
  MchBar = MmioRead32 (MmPciBase (SA_MC_BUS, 0, 0) + R_SA_MCHBAR) &~BIT0;

  ///
  /// Get policy settings through the SaPolicy PPI
  ///
  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaMiscPeiConfigGuid, (VOID *) &MiscPeiConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGraphicsPeiConfigGuid, (VOID *) &GtConfig);
  ASSERT_EFI_ERROR (Status);


  ///
  /// Set MCHBAR Offset 5F00h [10:9] = 11b
  ///
  Data32And = (UINT32) ~(BIT10 | BIT9);
  Data32Or  = 0x3 << 9;
  MmioAndThenOr32 ((UINTN) MchBar + R_SA_MCHBAR_SAPMCTL_OFFSET, Data32And, Data32Or);

  ///
  /// Set BIOS_RESET_CPL
  ///
  DEBUG ((DEBUG_INFO, "Set BIOS_RESET_CPL to indicate all configurations complete\n"));
  PostCode (0xA61);
  MmioOr8 ((UINTN) MchBar + R_SA_MCHBAR_BIOS_RESET_CPL_OFFSET, BIT0 | BIT1);
  ///
  /// Graphics PM initialization after BIOS_RESET_CPL
  ///
  DEBUG ((DEBUG_INFO, "GraphicsPmInit Start\n"));
  PostCode (0xA63);
  GraphicsPmInit (GtPreMemConfig, GtConfig);

  DEBUG ((DEBUG_INFO, "SaPciPrint Start\n"));
  PostCode (0xA64);
  SaPciPrint ();

  DEBUG((DEBUG_INFO, "SaSResetComplete Exit\n"));
  PostCode (0xA6F);
  return EFI_SUCCESS;
}

/**
  EDRAM WA for J step - Disable EDRAM by default and enable it through HW Test Mode policy if needed

  @param[in] MiscPeiConfig - Instance of SA_MISC_PEI_CONFIG
**/
VOID
EdramWa (
  IN    SA_MISC_PEI_CONFIG          *MiscPeiConfig
  )
{
  UINT32                    Data32;
  CPU_STEPPING              CpuStepping;
  UINT32                    MchBar;
  CPU_SKU                   CpuSku;

  CpuSku = GetCpuSku ();
  CpuStepping = GetCpuStepping ();
  MchBar = MmioRead32 (MmPciBase (SA_MC_BUS, 0, 0) + R_SA_MCHBAR) &~BIT0;

  if ((((CpuSku == EnumCpuUlx) || (CpuSku == EnumCpuUlt)) && ((CpuStepping == EnumSklK0) || (CpuStepping == EnumKblJ0))) ||
      (((CpuSku == EnumCpuTrad) || (CpuSku == EnumCpuHalo)) && (CpuStepping == EnumSklN0))) {
    Data32 = 0x00000000;  // Edram HW mode by default
    if (MiscPeiConfig->EdramTestMode == 0) {
      Data32 = 0x80000000; //EDRAM SW Disable
      DEBUG ((DEBUG_INFO, "Edram SW Disabled %x\n", Data32));
    } else if (MiscPeiConfig->EdramTestMode == 1) {
      Data32 = 0x80000001; //EDRAM SW Enable
      DEBUG ((DEBUG_INFO, "Edram SW Enabled %x\n", Data32));
    }
    DEBUG ((DEBUG_INFO, " Writing MchBar + 0x5878 :  %X\n", Data32));
    MmioWrite32 ((UINTN) MchBar + 0x5878, Data32);
  }
}

