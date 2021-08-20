/** @file
  The PCH Init PEIM implements the PCH PEI Init PPI.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2018 Intel Corporation.

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

@par Specification Reference:
**/
#include "PchInitPei.h"
#include "PchSmbus.h"
#include "PchUsb.h"
#include "PchSpi.h"
#include "Wdt.h"
#include <MeChipset.h>
#include <Private/PchHsio.h>
#include <Library/PostCodeLib.h>
#include <Library/OcWdtLib.h>
#include <Library/PchResetLib.h>

#define LEGACY_8259_MASK_REGISTER_MASTER                  0x21
#define LEGACY_8259_MASK_REGISTER_SLAVE                   0xA1

/**
  Write to mask registers of master and slave 8259 PICs.

**/
VOID
STATIC
Mask8259Interrupts (
  VOID
  )
{
  IoWrite8 (LEGACY_8259_MASK_REGISTER_MASTER, 0xFF);
  IoWrite8 (LEGACY_8259_MASK_REGISTER_SLAVE, 0xFF);
}

/**
  Check some PCH policies are valid for debugging unexpected problem if these
  values are not initialized or assigned incorrect resource.

  @param[in] SiPreMemPolicy  The SI PreMem Policy PPI instance

**/
VOID
PchValidatePolicy (
  IN  SI_PREMEM_POLICY_PPI   *SiPreMemPolicy
  )
{
  EFI_STATUS                  Status;
  PCH_GENERAL_PREMEM_CONFIG   *PchGeneralPreMemConfig;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPchGeneralPreMemConfigGuid, (VOID *) &PchGeneralPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  ASSERT (SiPreMemPolicy->TableHeader.Header.Revision == SI_PREMEM_POLICY_REVISION);
  ASSERT (PchGeneralPreMemConfig->AcpiBase != 0);
}

/**
  Build Memory Mapped IO Resource which is used to build E820 Table in LegacyBios,
  the resource range should be preserved in ACPI as well.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
PchPreservedMmioResource (
  VOID
  )
{
  //
  // This function builds a HOB that describes a chunk of system memory.
  //
  BuildResourceDescriptorHob (
    EFI_RESOURCE_MEMORY_MAPPED_IO,
    (EFI_RESOURCE_ATTRIBUTE_PRESENT | EFI_RESOURCE_ATTRIBUTE_INITIALIZED | EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE),
    PCH_PRESERVED_BASE_ADDRESS,
    PCH_PRESERVED_MMIO_SIZE
    );
  //
  // This function builds a HOB for the memory allocation.
  //
  BuildMemoryAllocationHob (
    PCH_PRESERVED_BASE_ADDRESS,
    PCH_PRESERVED_MMIO_SIZE,
    EfiMemoryMappedIO
    );

  return EFI_SUCCESS;
}

/**
  Perform DCI configuration.

  @param[in] SiPreMemPolicyPpi          The SI PREMEM Policy PPI instance
  @param[in] PchPwrmBase                PCH Power Management Base address of this PCH device
**/
VOID
PchDciConfiguration (
  IN  SI_PREMEM_POLICY_PPI             *SiPreMemPolicyPpi,
  IN  UINT32                           PchPwrmBase
  )
{
  EFI_STATUS                            Status;
  UINT32                                Data32;
  BOOLEAN                               DciEnabled;
  BOOLEAN                               DciDetected;
  PCH_DCI_PREMEM_CONFIG                 *DciPreMemConfig;

  DciEnabled  = FALSE;
  DciDetected = FALSE;

  ///
  /// Set PCR[DCI] + 30h bit[5] to 1, and clear 30h [2,1,0] = 0
  ///
  PchPcrAndThenOr32 (
    PID_DCI, R_PCH_PCR_DCI_PCE,
    (UINT32) ~(B_PCH_PCR_DCI_PCE_D3HE | B_PCH_PCR_DCI_PCE_I3E | B_PCH_PCR_DCI_PCE_PMCRE),
    B_PCH_PCR_DCI_PCE_HAE
    );
  ///
  /// BIOS need to set DCI PCR offset 0x08[19,18,17,16]=0
  ///
  PchPcrAndThenOr32 (PID_DCI, R_PCH_PCR_DCI_ECKPWRCTL, (UINT32) ~(BIT19 | BIT18 | BIT17 | BIT16), 0);

  ///
  /// BWG 13.6 DCI support
  /// DCI enable configuration
  ///
  /// If (DCI mode enable) {
  ///   Enable flow
  /// } else {
  ///   If (auto mode enabled) {
  ///     Auto flow
  ///   } else {
  ///    Disable flow
  ///   }
  /// }
  ///
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gDciPreMemConfigGuid, (VOID *) &DciPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  DciEnabled = DciPreMemConfig->DciEn == TRUE;
  ///
  /// If DCI is not enabled then detect DCI connected.
  ///
  if (DciEnabled == FALSE) {
    ///
    /// Detect DCI being avaiable (PCR[DCI] + 0x4[9] == 1 or PCR[DCI] + 0x4[10] == 1)
    ///
    PchPcrRead32 (PID_DCI, R_PCH_PCR_DCI_ECTRL, &Data32);
    DciDetected = (Data32 & (BIT9 | BIT10)) != 0;
  }

  if (DciEnabled) {
    ///
    /// Set PCR[DCI] + 4h bit[4] to 1 if DCI is enabled.
    ///
    PostCode (0xB4C);
    PchPcrAndThenOr32 (PID_DCI, R_PCH_PCR_DCI_ECTRL, (UINT32) ~0, (B_PCH_PCR_DCI_ECTRL_HDCIEN));
  } else {
    ///
    /// Set PCR[DCI] + 4h bit[4] to 0
    ///
    PchPcrAndThenOr32 (PID_DCI, R_PCH_PCR_DCI_ECTRL, (UINT32) ~(B_PCH_PCR_DCI_ECTRL_HDCIEN), 0);
  }

  ///
  /// Set PCR[DCI] + 4h bit[0] to 1
  ///
  PchPcrAndThenOr32 (PID_DCI, R_PCH_PCR_DCI_ECTRL, (UINT32) ~0, B_PCH_PCR_DCI_ECTRL_HDCIEN_LOCK);

  if (DciEnabled || DciDetected) {
    ///
    /// Disable SLP S0 and ModPHY sus power gating feature
    /// Handled in PchPm.c
    ///
    ///
    /// Set HSWPGCR1, PWRMBASE offset 0x5D0 to 0x80000000.
    /// This step has higher priority than the TraceHub mode disable HSWPGCR1 step.
    ///
    MmioWrite32 (PchPwrmBase + R_PCH_PWRM_HSWPGCR1, B_PCH_PWRM_SW_PG_CTRL_LOCK);
  }
}

/**
  Internal function performing HPET initin early PEI phase

  @param[in] SiPreMemPolicyPpi               The SI PREMEM Policy PPI instance
**/
VOID
PchHpetInit (
  IN  SI_PREMEM_POLICY_PPI                    *SiPreMemPolicyPpi
  )
{
  EFI_STATUS                            Status;
  PCH_HPET_PREMEM_CONFIG                *HpetPreMemConfig;
  UINTN                                 P2sbBase;
  UINT16                                Data16;
  UINT32                                HpetBase;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gHpetPreMemConfigGuid, (VOID *) &HpetPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  P2sbBase        = MmPciBase (
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PCI_DEVICE_NUMBER_PCH_P2SB,
                      PCI_FUNCTION_NUMBER_PCH_P2SB
                      );

  //
  // Program this field accordingly if unique bus:device:function number is required for the
  // corresponding HPET
  //
  if (HpetPreMemConfig->BdfValid) {
    Data16 = ((UINT16) (HpetPreMemConfig->BusNumber) << 8) & B_PCH_P2SB_HBDF_BUF;
    Data16 |= ((UINT16) (HpetPreMemConfig->DeviceNumber) << 3) & B_PCH_P2SB_HBDF_DEV;
    Data16 |= (UINT16) (HpetPreMemConfig->FunctionNumber) & B_PCH_P2SB_HBDF_FUNC;
    MmioWrite16 ((UINTN) (P2sbBase + R_PCH_P2SB_HBDF), Data16);
  }
  //
  // Initial and enable HPET High Precision Timer memory address for basic usage
  // If HPET base is not set, the default would be 0xFED00000.
  //
  HpetBase = HpetPreMemConfig->Base;
  if (HpetBase == 0) {
    HpetBase = V_PCH_HPET_BASE0;
  }
  MmioAndThenOr8 (
    P2sbBase + R_PCH_P2SB_HPTC,
    (UINT8) ~B_PCH_P2SB_HPTC_AS,
    (UINT8) (((HpetBase >> N_PCH_HPET_ADDR_ASEL) & B_PCH_P2SB_HPTC_AS) | B_PCH_P2SB_HPTC_AE)
    );
  //
  // Read back for posted write to take effect
  //
  MmioRead8 (P2sbBase + R_PCH_P2SB_HPTC);
  //
  // Set HPET Timer enable to start counter spinning
  //
  if (HpetPreMemConfig->Enable == TRUE) {
    MmioOr32 (HpetBase + 0x10, 0x1);
  }
  //
  // Build the resource descriptor hob for HPET address resource.
  // HPET only claims 0x400 in size, but the minimal size to reserve memory
  // is one page 0x1000.
  //
  BuildResourceDescriptorHob (
    EFI_RESOURCE_MEMORY_MAPPED_IO,
    (EFI_RESOURCE_ATTRIBUTE_PRESENT    |
     EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE),
    HpetBase,
    0x1000
    );
  BuildMemoryAllocationHob (
    HpetBase,
    0x1000,
    EfiMemoryMappedIO
    );
}

/**
  This function performs basic initialization for PCH in PEI phase after Policy produced.
  If any of the base address arguments is zero, this function will disable the corresponding
  decoding, otherwise this function will enable the decoding.
  This function locks down the AcpiBase.

  @param[in] SiPreMemPolicyPpi         The Silicon PreMem Policy PPI instance
**/
VOID
EFIAPI
PchOnPolicyInstalled (
  IN  SI_PREMEM_POLICY_PPI    *SiPreMemPolicyPpi
  )
{
  EFI_STATUS                  Status;
  PCH_SERIES                  PchSeries;
  UINTN                       PmcBaseAddress;
  PCH_GENERAL_PREMEM_CONFIG   *PchGeneralPreMemConfig;
  PCH_WDT_PREMEM_CONFIG       *WdtPreMemConfig;
  PCH_TRACE_HUB_PREMEM_CONFIG *TraceHubPreMemConfig;
  PCH_PCIE_RP_PREMEM_CONFIG   *PcieRpPreMemConfig;
  UINT8                       Controller;

  PostCode (0xB48);
  DEBUG ((DEBUG_INFO, "PchOnPolicyInstalled() - Start\n"));

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPchGeneralPreMemConfigGuid, (VOID *) &PchGeneralPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gWatchDogPreMemConfigGuid, (VOID *) &WdtPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gTraceHubPreMemConfigGuid, (VOID *) &TraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPcieRpPreMemConfigGuid, (VOID *) &PcieRpPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  PmcBaseAddress = MmPciBase (
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_PMC,
                     PCI_FUNCTION_NUMBER_PCH_PMC
                     );

  PchSeries      = GetPchSeries ();
  ///
  /// Set ACPI Base in PMC device
  ///
  Status = PchAcpiBaseSet (PchGeneralPreMemConfig->AcpiBase);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Lock down the ACPI Base
  ///
  MmioOr8 (
    PmcBaseAddress + R_PCH_PMC_GEN_PMCON_B + 2,
    (UINT8) (B_PCH_PMC_GEN_PMCON_B_ACPI_BASE_LOCK >> 16)
    );

  ///
  /// Set PWRM Base in PMC device
  ///
  Status = PchPwrmBaseSet (PCH_PWRM_BASE_ADDRESS);
  ASSERT_EFI_ERROR (Status);

  //
  // Check to disable and lock WDT according to Policy.
  //
  WdtOnPolicyInstalled ((BOOLEAN) WdtPreMemConfig->DisableAndLock);

  //
  // Configure BIOS HSIO if ChipsetInit HSIO Settings in CSME are right
  // The HSIO PPI MUST be ready before this function.
  // The HSIO programming should be done before any IP configuration.
  //
  PostCode (0xB49);
  if (PchHsioChipsetInitProg (FALSE) == EFI_SUCCESS) {
    PchHsioBiosProgPreMem (SiPreMemPolicyPpi);
  }

  EarlyPcieRpDisabling (PcieRpPreMemConfig);

  PostCode (0xB4A);
  PchDciConfiguration (SiPreMemPolicyPpi, PCH_PWRM_BASE_ADDRESS);

  PostCode (0xB4D);
  TraceHubInitialize (
    (UINT8) TraceHubPreMemConfig->EnableMode
    );

  //
  // The following function should be executed after PchDciConfiguration()
  //
  TraceHubManagePowerGateControl ();

  PostCode (0xB15);
  Status = InitializePchSmbus (SiPreMemPolicyPpi);

  for (Controller = 0; Controller < GetPchMaxPcieControllerNum (); Controller++) {
    PsfConfigurePcieGrantCounts (Controller, (UINT8)GetPcieControllerConfig (Controller));
  }
  if (PchGeneralPreMemConfig->Port80Route == PchReservedPageToLpc) {
    PchPcrAndThenOr8 (
      PID_DMI, R_PCH_PCR_DMI_GCS + 1,
      (UINT8) (~(B_PCH_PCR_DMI_RPR >> 8)),
      0
      );
  } else {
    PchPcrAndThenOr8 (
      PID_DMI, R_PCH_PCR_DMI_GCS + 1,
      (UINT8) ~0,
      (UINT8) (B_PCH_PCR_DMI_RPR >> 8)
      );
  }

  ///
  /// Set FIA PCR offset 0x20[31] = 1b
  ///
  PchPcrAndThenOr32 (PID_FIA, R_PCH_PCR_FIA_PLLCTL, (UINT32) ~0, (BIT31));

  PostCode (0xB52);
  PchHpetInit (SiPreMemPolicyPpi);

  ConfigureLpcOnPolicy (SiPreMemPolicyPpi);

  PostCode (0xB55);
  DEBUG ((DEBUG_INFO, "PchOnPolicyInstalled() - End\n"));
}

/**
 Early init P2SB configuration
 For GPIO and ITSS that support sideband posted write, they can support
 back to back write after their correspoing bit sunder P2SB PCI Config
 80h-9fh are set.
**/
VOID
PchP2sbEarlyConfig (
  VOID
  )
{
  UINTN                   P2sbBase;

  P2sbBase  = MmPciBase (
                DEFAULT_PCI_BUS_NUMBER_PCH,
                PCI_DEVICE_NUMBER_PCH_P2SB,
                PCI_FUNCTION_NUMBER_PCH_P2SB
                );
  ///
  /// For GPIO and ITSS that support sideband posted write, they can support
  /// back to back write after their correspoing bit sunder P2SB PCI Config
  /// 80h-9fh are set.
  /// For SKL PCH-LP and SKL PCH-H, program the following at early PCH BIOS init
  /// 1. Set P2SB PCI offset 80h to 0
  /// 2. Set P2SB PCI offset 84h to 0
  /// 3. Set P2SB PCI offset 88h to 0
  /// 4. Set P2SB PCI offset 8Ch to 0
  /// 5. Set P2SB PCI offset 90h to 0
  /// 6. Set P2SB PCI offset 94h to 0000F000h
  /// 7. Set P2SB PCI offset 98h to 00000010h
  /// 8. Set P2SB PCI offset 9Ch to 0
  ///
  MmioWrite32 (P2sbBase + R_PCH_P2SB_80, 0);
  MmioWrite32 (P2sbBase + R_PCH_P2SB_84, 0);
  MmioWrite32 (P2sbBase + R_PCH_P2SB_88, 0);
  MmioWrite32 (P2sbBase + R_PCH_P2SB_8C, 0);
  MmioWrite32 (P2sbBase + R_PCH_P2SB_90, 0);
  MmioWrite32 (P2sbBase + R_PCH_P2SB_94, 0x0000F000);
  MmioWrite32 (P2sbBase + R_PCH_P2SB_98, 0x00000010);
  MmioWrite32 (P2sbBase + R_PCH_P2SB_9C, 0);
  ///
  /// Set P2SB PCI offset 0xF4[0] = 1
  ///
  MmioOr8 (P2sbBase + R_PCH_P2SB_F4, BIT0);
}

/**
  This code is intended to handle all cases where IP could be fuse disabled, static power gated
  or disabled due to soft strap lane assignment

  @param[in] PchPwrmBase       PCH Power Management Base address of this PCH device

  @retval EFI_SUCCESS
**/
VOID
PchEarlyDisabledDeviceHandling (
  IN  UINT32                      PchPwrmBase
  )
{
  UINT32                  FuseDis2State;
  UINTN                   RpStrpFuseCfg;
  UINT8                   CtrlIndex;
  UINT8                   RpIndex;
  UINT8                   MaxPciePortNum;
  UINT32                  Data32;
  UINT32                  SpxPcd[PCH_MAX_PCIE_CONTROLLERS];
  UINT32                  SpxMask;
  UINT8                   Response;
  EFI_STATUS              Status;
  PCH_SERIES              PchSeries;
  PCH_GENERATION          PchGen;

  ZeroMem (SpxPcd, sizeof (SpxPcd));

  PchSeries = GetPchSeries ();
  PchGen = GetPchGeneration ();
  MaxPciePortNum = GetPchMaxPciePortNum ();

  DEBUG ((DEBUG_INFO, "PchEarlyDisabledDeviceHandling() - Start\n"));
  //
  // Get fuse info from PWRMBASE + FUSE_DIS_RD_2 (Offset 644h)
  //
  FuseDis2State = MmioRead32 ((UINTN) (PchPwrmBase + R_PCH_PWRM_FUSE_DIS_RD_2));

  DEBUG ((DEBUG_INFO, "PchPwrmBase + R_PCH_PWRM_FUSE_DIS_RD_2 = %x\n", FuseDis2State));

  ///
  /// BWG 5.3.1 Fuse Disabled, Static Disabled, non-Static function disable Device Handling
  ///

  //
  // Get PCIE Port configuration and disable value for each RP
  // and perform PSF function disable
  //
  for (CtrlIndex = 0; CtrlIndex < MaxPciePortNum / PCH_PCIE_CONTROLLER_PORTS; CtrlIndex++) {
    PchPcrRead32 (PchGetPcieControllerSbiPid (CtrlIndex), R_PCH_PCR_SPX_PCD, &SpxPcd[CtrlIndex]);
    DEBUG ((DEBUG_INFO, "SP%c Controller PCD Value = %x\n", 'A' + CtrlIndex, SpxPcd[CtrlIndex]));
  }

  for (RpIndex = 0; RpIndex < MaxPciePortNum; RpIndex++) {
    CtrlIndex  = RpIndex / PCH_PCIE_CONTROLLER_PORTS;
    SpxMask = B_PCH_PCR_SPX_PCD_P1D << (RpIndex % PCH_PCIE_CONTROLLER_PORTS);
    if ((SpxPcd[CtrlIndex] & SpxMask) == SpxMask) {
      PsfDisablePcieRootPort (RpIndex);
    }
  }

  for (CtrlIndex = 0; CtrlIndex < MaxPciePortNum / PCH_PCIE_CONTROLLER_PORTS; CtrlIndex++) {
    DEBUG ((DEBUG_INFO, "Multilane check for PCIE Controller %d: ", CtrlIndex));
    RpIndex = CtrlIndex * PCH_PCIE_CONTROLLER_PORTS;
    //
    // Get PCIE PCI register from SBI in case it's disabled.
    //
    Status = PchSbiRpPciRead32 (RpIndex, R_PCH_PCIE_STRPFUSECFG, &Data32);
    if (Status == EFI_SUCCESS) {
      RpStrpFuseCfg = (Data32 & B_PCH_PCIE_STRPFUSECFG_RPC) >> N_PCH_PCIE_STRPFUSECFG_RPC;
      switch (RpStrpFuseCfg) {
        case V_PCH_PCIE_STRPFUSECFG_RPC_4:
          //
          // Disable ports 2, 3, 4 of a controller when it's set to 1 x4
          //
          DEBUG ((DEBUG_INFO, "Disabling RP %d/%d/%d\n", RpIndex+2, RpIndex+3, RpIndex+4));
          PsfDisablePcieRootPort (RpIndex + 1);
          PsfDisablePcieRootPort (RpIndex + 2);
          PsfDisablePcieRootPort (RpIndex + 3);
          break;
        case V_PCH_PCIE_STRPFUSECFG_RPC_2_2:
          //
          // Disable ports 2, 4 of a controller when it's set to 2 x2
          //
          DEBUG ((DEBUG_INFO, "Disabling RP %d/%d\n", RpIndex+2, RpIndex+4));
          PsfDisablePcieRootPort (RpIndex + 1);
          PsfDisablePcieRootPort (RpIndex + 3);
          break;
        case V_PCH_PCIE_STRPFUSECFG_RPC_2_1_1:
          //
          // Disable port 2 of a controller when it's set to 1 x2
          //
          DEBUG ((DEBUG_INFO, "Disabling RP %d\n", RpIndex+2));
          PsfDisablePcieRootPort (RpIndex + 1);
          break;
        case V_PCH_PCIE_STRPFUSECFG_RPC_1_1_1_1:
        default:
          DEBUG ((DEBUG_INFO, "No ports disabled\n"));
          break;
      }
    }
  }

  //
  // OTG fused
  //
  if (FuseDis2State & B_PCH_PWRM_FUSE_DIS_RD_2_OTG_FUSE_SS_DIS) {
    DEBUG ((DEBUG_INFO, "xDCI (OTG) Fuse disabled - performing PSF disable\n"));
    PsfDisableXdciDevice ();
  }
  //
  // SATA fused
  //
  if (FuseDis2State & B_PCH_PWRM_FUSE_DIS_RD_2_SATA_FUSE_SS_DIS) {
    DEBUG ((DEBUG_INFO, "SATA Fuse disabled - performing PSF disable\n"));
    PsfDisableSataDevice ();
  }
  //
  // TraceHub fused
  // Hide TraceHub Phantom Device BDF 0/20/4 using PSF (Config Disable)
  //
  PsfHideTraceHubAcpiDevice ();

  //
  // LPSS fused
  //
  if (FuseDis2State & B_PCH_PWRM_FUSE_DIS_RD_2_SERIALIO_FUSE_SS_DIS) {
    DEBUG ((DEBUG_INFO, "SerialIo SPI1 Static PG disabled - performing PSF disable\n"));
    PsfDisableSerialIoDevice (PchSerialIoIndexSpi1);
    DEBUG ((DEBUG_INFO, "SerialIo SPI0 Static PG disabled - performing PSF disable\n"));
    PsfDisableSerialIoDevice (PchSerialIoIndexSpi0);
    DEBUG ((DEBUG_INFO, "SerialIo UART2 Static PG disabled - performing PSF disable\n"));
    PsfDisableSerialIoDevice (PchSerialIoIndexUart2);
    DEBUG ((DEBUG_INFO, "SerialIo UART1 Static PG disabled - performing PSF disable\n"));
    PsfDisableSerialIoDevice (PchSerialIoIndexUart1);
    DEBUG ((DEBUG_INFO, "SerialIo UART0 Static PG disabled - performing PSF disable\n"));
    PsfDisableSerialIoDevice (PchSerialIoIndexUart0);
    if (PchSeries == PchLp) {
      DEBUG ((DEBUG_INFO, "SerialIo I2C5 Static PG disabled - performing PSF disable\n"));
      PsfDisableSerialIoDevice (PchSerialIoIndexI2C5);
      DEBUG ((DEBUG_INFO, "SerialIo I2C4 Static PG disabled - performing PSF disable\n"));
      PsfDisableSerialIoDevice (PchSerialIoIndexI2C4);
    }
    DEBUG ((DEBUG_INFO, "SerialIo I2C3 Static PG disabled - performing PSF disable\n"));
    PsfDisableSerialIoDevice (PchSerialIoIndexI2C3);
    DEBUG ((DEBUG_INFO, "SerialIo I2C2 Static PG disabled - performing PSF disable\n"));
    PsfDisableSerialIoDevice (PchSerialIoIndexI2C2);
    DEBUG ((DEBUG_INFO, "SerialIo I2C1 Static PG disabled - performing PSF disable\n"));
    PsfDisableSerialIoDevice (PchSerialIoIndexI2C1);
    DEBUG ((DEBUG_INFO, "SerialIo I2C0 Static PG disabled - performing PSF disable\n"));
    PsfDisableSerialIoDevice (PchSerialIoIndexI2C0);
  }
  //
  // For H, put SerialIo I2C4 and I2C5 in D3, and set function disable in PMC
  //
  if (PchSeries == PchH) {
    DEBUG ((DEBUG_INFO, "Put SerialIo I2C4 in D3\n"));
    Data32 = BIT18 | BIT17 | BIT16;
    PchSbiExecutionEx (
      PID_SERIALIO,
      R_PCH_SERIAL_IO_D0I3MAXDEVPG,
      PciConfigWrite,
      FALSE,
      0xF,
      0,
      ((PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C4 << 3) | PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C4),
      &Data32,
      &Response
      );

    Data32 = BIT1 | BIT0;
    PchSbiExecutionEx (
      PID_SERIALIO,
      R_PCH_SERIAL_IO_PME_CTRL_STS,
      PciConfigWrite,
      FALSE,
      0xF,
      0,
      ((PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C4 << 3) | PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C4),
      &Data32,
      &Response
      );

    //
    // perform a read to avoid ordering and noncoherency problems
    //
    PchSbiExecutionEx (
      PID_SERIALIO,
      R_PCH_SERIAL_IO_PME_CTRL_STS,
      PciConfigRead,
      FALSE,
      0xF,
      0,
      ((PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C4 << 3) | PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C4),
      &Data32,
      &Response
      );

    DEBUG ((DEBUG_INFO, "Put SerialIo I2C5 in D3\n"));
    Data32 = BIT18 | BIT17 | BIT16;
    PchSbiExecutionEx (
      PID_SERIALIO,
      R_PCH_SERIAL_IO_D0I3MAXDEVPG,
      PciConfigWrite,
      FALSE,
      0xF,
      0,
      ((PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C5 << 3) | PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C5),
      &Data32,
      &Response
      );

    Data32 = BIT1 | BIT0;
    PchSbiExecutionEx (
      PID_SERIALIO,
      R_PCH_SERIAL_IO_PME_CTRL_STS,
      PciConfigWrite,
      FALSE,
      0xF,
      0,
      ((PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C5 << 3) | PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C5),
      &Data32,
      &Response
      );

    //
    // perform a read to avoid ordering and noncoherency problems
    //
    PchSbiExecutionEx (
      PID_SERIALIO,
      R_PCH_SERIAL_IO_PME_CTRL_STS,
      PciConfigRead,
      FALSE,
      0xF,
      0,
      ((PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C5 << 3) | PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C5),
      &Data32,
      &Response
      );

    //
    // Set PWRMBASE + ST_PG_FDIS_PMC_2 Offset 624h [5:4]
    //
    MmioOr32 (
      (UINTN) (PchPwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_2),
      (B_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C5_FDIS_PMC | B_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C4_FDIS_PMC)
      );
  }
  //
  // SCC fused
  //
  if (PchSeries == PchLp) {
    if (FuseDis2State & B_PCH_PWRM_FUSE_DIS_RD_2_SCC_FUSE_SS_DIS) {
      DEBUG ((DEBUG_INFO, "SCC Fuse disabled - performing PSF disable\n"));
      PsfDisableScsDevice (PchPsfSdcard);
      PsfDisableScsDevice (PchPsfSdio);
      PsfDisableScsDevice (PchPsfEmmc);
    }

    //
    // Disable Device 30 Function 7
    // PSF Function Disable: Set PCH[PSF_2] + "AGNT_T0_SHDW_PCIEN"[D30_F7] [8] = 1
    //
    DEBUG ((DEBUG_INFO, "UFS disabled - performing PSF disable\n"));
    PsfDisableScsDevice (PchPsfUfs);

    //
    // Camera fused
    //
    if (FuseDis2State & B_PCH_PWRM_FUSE_DIS_RD_2_CAM_FUSE_SS_DIS) {
      DEBUG ((DEBUG_INFO, "CAMERA Fuse disabled - performing PSF disable\n"));
      PsfDisableCio2Device ();
    }
  }

  //
  // ISH fused
  //
  if (FuseDis2State & B_PCH_PWRM_FUSE_DIS_RD_2_ISH_FUSE_SS_DIS) {
    DEBUG ((DEBUG_INFO, "ISH Fuse disabled - performing PSF disable\n"));
    PsfDisableIshDevice ();
  }
  //
  // Gbe fused
  //
  if (FuseDis2State & B_PCH_PWRM_FUSE_DIS_RD_2_GBE_FUSE_SS_DIS) {
    DEBUG ((DEBUG_INFO, "GBE Fuse disabled - performing PSF disable\n"));
    PsfDisableGbeDevice ();
  }

  DEBUG ((DEBUG_INFO, "PchEarlyDisabledDeviceHandling() - End\n"));
}

/**
  Internal function performing miscellaneous init needed in very early PEI phase

  @param[in] PchPwrmBase       PCH Power Management Base address of this PCH device

**/
VOID
PchEarlyInit (
  IN  UINT32                      PchPwrmBase
  )
{
  UINTN                   PciPmcRegBase;
  UINT8                   Data8;

  DEBUG ((DEBUG_INFO, "PchEarlyInit() - Start\n"));

  //
  // Perform RP PSF device number and function number reset.
  //
  PsfReloadDefaultPcieRpDevFunc ();

  #ifndef MINTREE_FLAG
  ///
  /// Perform PCH SKU detection to check if the RST PCIe Storage Remapping feature is supported
  ///
  PchRstPcieStorageCreEarlyInit ();
  #endif //MINTREE_FLAG
  ///
  /// Before any interrupt is enabled, set ITSS.MMC, PCR[ITSS] + 3334h[0] = 1b.
  ///
  PchPcrWrite16 (PID_ITSS, R_PCH_PCR_ITSS_MMC, (UINT16) B_PCH_PCR_ITSS_MMC_MSTRMSG_EN);

  ///
  /// SKL PCH BWG 7.2.14. Additional PCH DMI and OP-DMI Programming Steps
  /// Step 1.1
  /// Set PCR[DMI] + 2234[17,16] = 1b,1b (using byte access)
  /// This programming must be done before any upstream bus master transactions are enabled.
  ///
  PchPcrAndThenOr8 (PID_DMI, R_PCH_PCR_DMI_DMIC + 0x2, 0xFF, (BIT0 | BIT1));

  ///
  /// According to bios spec,
  /// Setup "uCode Patch Region Enable", PCR [DMI] + 2748h[0] to '0b'
  ///
  PchPcrAndThenOr32 (PID_DMI, R_PCH_PCR_DMI_UCPR, (UINT32) ~B_PCH_PCR_DMI_UCPR_UPRE, 0);

  ///
  /// For GPIO and ITSS that support sideband posted write, they can support
  /// back to back write after their correspoing bit sunder P2SB PCI Config
  /// 80h-9fh are set.
  ///
  PchP2sbEarlyConfig ();

  ///
  /// PCH BIOS Spec Section 19.3 Power Failure Considerations
  /// RTC_PWR_STS bit, GEN_PMCON_B (PMC PCI offset A4h[2])
  /// When the RTC_PWR_STS bit is set, it indicates that the RTCRST# signal went low.
  /// Software should clear this bit. For example, changing the RTC battery sets this bit.
  /// System BIOS should reset CMOS to default values if the RTC_PWR_STS bit is set.
  /// The System BIOS should execute the sequence below if the RTC_PWR_STS bit is set
  /// before memory initialization. This will ensure that the RTC state machine has been
  /// initialized.
  /// 1. If the RTC_PWR_STS bit is set which indicates a new coin-cell battery insertion or a
  ///    battery failure, steps 2 through 5 should be executed.
  /// 2. Set RTC Register 0Ah[6:4] to 110b or 111b
  /// 3. Set RTC Register 0Bh[7].
  /// 4. Set RTC Register 0Ah[6:4] to 010b
  /// 5. Clear RTC Register 0Bh[7].
  ///
  PciPmcRegBase = MmPciBase (
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_PMC,
                    PCI_FUNCTION_NUMBER_PCH_PMC
                    );

  if ((MmioRead8 (PciPmcRegBase + R_PCH_PMC_GEN_PMCON_B) &
       (UINT8) B_PCH_PMC_GEN_PMCON_B_RTC_PWR_STS) != 0) {
    ///
    /// 2. Set RTC Register 0Ah[6:4] to 110b or 111b
    ///
    IoWrite8 (R_PCH_RTC_INDEX_ALT, (UINT8) R_PCH_RTC_REGA);
    Data8 = IoRead8 (R_PCH_RTC_TARGET_ALT) & (UINT8) ~(BIT6 | BIT5 | BIT4);
    Data8 |= (UINT8) (BIT6 | BIT5);
    IoWrite8 (R_PCH_RTC_TARGET_ALT, Data8);
    ///
    /// 3. Set RTC Register 0Bh[7].
    ///
    IoWrite8 (R_PCH_RTC_INDEX_ALT, (UINT8) R_PCH_RTC_REGB);
    IoOr8 (R_PCH_RTC_TARGET_ALT, (UINT8) B_PCH_RTC_REGB_SET);
    ///
    /// 4. Set RTC Register 0Ah[6:4] to 010b
    ///
    IoWrite8 (R_PCH_RTC_INDEX_ALT, (UINT8) R_PCH_RTC_REGA);
    Data8 = IoRead8 (R_PCH_RTC_TARGET_ALT) & (UINT8) ~(BIT6 | BIT5 | BIT4);
    Data8 |= (UINT8) (BIT5);
    IoWrite8 (R_PCH_RTC_TARGET_ALT, Data8);
    ///
    /// 5. Clear RTC Register 0Bh[7].
    ///
    IoWrite8 (R_PCH_RTC_INDEX_ALT, (UINT8) R_PCH_RTC_REGB);
    IoAnd8 (R_PCH_RTC_TARGET_ALT, (UINT8) ~B_PCH_RTC_REGB_SET);
  }
  ///
  /// PCH BIOS Spec Section 19.1 Handling Status Registers
  /// System BIOS must set 1b to clear the following registers during power-on
  /// and resuming from Sx sleep state.
  /// - PWRMBASE + Offset 10h[0] = 1b
  ///   Done in ConfigureMiscPm ()
  /// - PWRMBASE + Offset 10h[4] = 1b, needs to be done as early as possible during PEI
  /// - PWRMBASE + Offset 10h[5] = 1b
  ///   Done in ConfigureMiscPm ()
  ///
  MmioWrite32 (
    (UINTN) (PchPwrmBase + R_PCH_PWRM_PRSTS),
    (UINT32) (B_PCH_PWRM_PRSTS_FIELD_1)
    );

  //
  // Clear CF9GR if it's set in previous boot.
  //
  MmioAnd32 (PciPmcRegBase + R_PCH_PMC_ETR3, (UINT32) ~(B_PCH_PMC_ETR3_CF9GR));

  ConfigureLpcOnEarlyPei ();

  PchEarlyDisabledDeviceHandling (PchPwrmBase);

  ///
  /// Clear PCR PSF_1_PSF_PORT_CONFIG_PG1_PORT7[5] = 0b
  ///
  PsfDisableIsmNpCompletionTrackForGbe ();

  DEBUG_CODE (
    PrintPchPciConfigSpace ();
    );

  DEBUG ((DEBUG_INFO, "PchEarlyInit() - End\n"));

  return;
}

/**
  Performing Pch early init before PchPlatfromPolicy PPI produced

  @retval EFI_SUCCESS             The function completes successfully
  @retval EFI_OUT_OF_RESOURCES    Insufficient resources to create database
**/
EFI_STATUS
EFIAPI
PchInitPreMem (
  VOID
  )
{
  EFI_STATUS              Status;
  UINT32                  PchPwrmBase;
  UINTN                   P2sbBase;
  UINT32                  PcrBase;

  PostCode (0xB00);
  DEBUG ((DEBUG_INFO, "PchInitPreMem() - Start\n"));
  //
  // Check if Pch is supported
  //
  if (!IsPchSupported ()) {
    DEBUG ((DEBUG_ERROR, "PCH SKU is not supported due to no proper PCH LPC found!\n"));
    ASSERT (FALSE);
  }

  ///
  /// Check if SBREG has been set.
  /// If not, program it.
  ///
  P2sbBase = MmPciBase (
               DEFAULT_PCI_BUS_NUMBER_PCH,
               PCI_DEVICE_NUMBER_PCH_P2SB,
               PCI_FUNCTION_NUMBER_PCH_P2SB
               );
  PcrBase  = MmioRead32 (P2sbBase + R_PCH_P2SB_SBREG_BAR);
  if ((PcrBase & B_PCH_P2SB_SBREG_RBA) == 0) {
    DEBUG ((DEBUG_INFO, "SBREG should be programmed before here\n"));
    //
    // Set SBREG base address.
    //
    MmioWrite32 (P2sbBase + R_PCH_P2SB_SBREG_BAR, PCH_PCR_BASE_ADDRESS);
    //
    // Enable the MSE bit for MMIO decode.
    //
    MmioOr8 (P2sbBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
  }

  ///
  /// Check if PCH PWRM Base has been set
  ///
  Status = PchPwrmBaseGet (&PchPwrmBase);
  DEBUG ((DEBUG_INFO, "PCH PWRM Base needs to be programmed before here\n"));
  ASSERT (PchPwrmBase != 0);

  ///
  /// Perform miscellaneous init needed in very early PEI phase
  ///
  PostCode (0xB02);
  PchEarlyInit (PchPwrmBase);

  PostCode (0xB7F);
  DEBUG ((DEBUG_INFO, "PchInitPreMem() - End\n"));

  return Status;
}

/**
  Show PCH related information
**/
VOID
PchShowInfomation (
  VOID
  )
{
  DEBUG_CODE_BEGIN ();
  CHAR8           Buffer[32];
  UINT32          BufferSize;

  BufferSize = sizeof (Buffer);
  PchGetSeriesStr (GetPchSeries (), Buffer, &BufferSize);
  DEBUG ((DEBUG_INFO, "PCH Series   : %a\n", Buffer));
  BufferSize = sizeof (Buffer);
  PchGetSteppingStr (PchStepping (), Buffer, &BufferSize);
  DEBUG ((DEBUG_INFO, "PCH Stepping : %a\n", Buffer));
  BufferSize = sizeof (Buffer);
  PchGetSkuStr (GetLpcDid (), Buffer, &BufferSize);
  DEBUG ((DEBUG_INFO, "PCH SKU      : %a\n", Buffer));
  DEBUG_CODE_END ();
}

/**
  PCH init pre-memory entry point
**/
VOID
EFIAPI
PchInitPrePolicy (
  VOID
  )
{
  EFI_STATUS Status;

  //
  // Dump PCH information
  //
  DEBUG_CODE (
    PchShowInfomation ();
    );

  DEBUG ((DEBUG_INFO, "PchInitPrePolicy() - Start\n"));

  //
  // Build Memory Mapped IO Resource which is used to build E820 Table in LegacyBios.
  // the resource range should be preserved in ACPI as well.
  //
  Status = PchPreservedMmioResource ();

#ifndef FSP_FLAG
  ///
  /// If there was unexpected reset but no WDT expiration and no resume from S3/S4,
  /// clear unexpected reset status and enforce expiration. This is to inform Firmware
  /// which has no access to unexpected reset status bit, that something went wrong.
  ///
  OcWdtResetCheck();
#endif
  //
  // Initialize WDT and install WDT PPI
  //
  Status = WdtEarlyInit ();
  Status = OcWdtInit ();


  //
  // Install PCH RESET PPI and EFI RESET2 PeiService
  //
  Status = PchInitializeReset ();

  //
  // Install PCH SPI PPI
  //
  Status = InstallPchSpi ();

  //
  // Perform PCH early init
  //
  Status = PchInitPreMem ();

  //
  // The 8259 PIC is still functional and not masked by default,
  // even if APIC is enabled.
  // So need to set all 8259 interrupts to disabled.
  //
  Mask8259Interrupts ();

  DEBUG ((DEBUG_INFO, "PchInitPrePolicy() - End\n"));
}

