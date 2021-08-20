/** @file
  Initializes PCH LAN Device in PEI

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

/**
  Check whether GbE is enabled in PMC.
**/
STATIC
BOOLEAN
PchPmcIsGbeEnabled (
  VOID
  )
{
  UINT32  PwrmBase;
  UINT32  FuseDis2State;
  UINT32  StPgFdis1;

  PchPwrmBaseGet (&PwrmBase);
  //
  // Is GbE disabled by PMC strap/fuse
  //
  FuseDis2State = MmioRead32 (PwrmBase + R_PCH_PWRM_FUSE_DIS_RD_2);
  if (FuseDis2State & B_PCH_PWRM_FUSE_DIS_RD_2_GBE_FUSE_SS_DIS) {
    return FALSE;
  }
  //
  // Is GbE statically power gated
  //
  StPgFdis1 = MmioRead32 (PwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1);
  if (StPgFdis1 & B_PCH_PWRM_ST_PG_FDIS_PMC_1_GBE_FDIS_PMC) {
    return FALSE;
  }

  return TRUE;
}


/**
  Performs global reset required to change GbE static power gating state.
**/
STATIC
VOID
PchGbeGlobalReset (
  VOID
  )
{
  PCH_RESET_DATA             ResetData;

  DEBUG ((DEBUG_ERROR, "PchGbeGlobalReset\n"));

  CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
  StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
  (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetPlatformSpecific, EFI_SUCCESS, sizeof (PCH_RESET_DATA), &ResetData);

  ASSERT (FALSE);
}

/**
  Enable GbE by disabling static power gating.
**/
STATIC
VOID
PchEnableGbe (
  VOID
  )
{
  UINT32  PwrmBase;

  DEBUG ((DEBUG_INFO, "Enabling internal LAN...\n"));

  PchPwrmBaseGet (&PwrmBase);

  //
  // Before modifying LAN Disable bit, make sure it's not locked.
  //
  ASSERT ((MmioRead32 (PwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1) & B_PCH_PWRM_ST_PG_FDIS_PMC_1_ST_FDIS_LK) == 0);

  //
  // Enable the Internal GbE Controller
  // Set PWRMBASE + 620h[0] = 0b to enable GbE controller
  //
  MmioAnd32 (PwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1, (UINT32) ~B_PCH_PWRM_ST_PG_FDIS_PMC_1_GBE_FDIS_PMC);
  //
  // Read back for posted write to take effect
  //
  MmioRead32 (PwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1);
}


/**
  Disable the Internal GbE Controller

  BIOS has the ability to disable the LAN Controller functionality, in addition to
  configuring PMC to disable the LAN Controller BIOS need to set Disable bit in the
  LANDISCTRL register and then lock the LANDISCTRL register by setting the Lock bit in
  the LOCKLANDIS register.
**/
STATIC
VOID
PchDisableGbe (
  VOID
  )
{
  UINTN   GbePciBase;
  UINT32  PwrmBase;

  DEBUG ((DEBUG_INFO, "Disabling internal LAN...\n"));

  GbePciBase = MmPciBase (
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_LAN,
                 PCI_FUNCTION_NUMBER_PCH_LAN
                 );

  ASSERT (MmioRead32 (GbePciBase) != 0xFFFFFFFF);

  //
  // Set LANDISCTRL, GbE PCI config + 0xA0 bit[0] to 1
  //
  MmioOr32 (GbePciBase + R_PCH_LAN_LANDISCTRL, B_PCH_LAN_LANDISCTRL_DISABLE);
  ASSERT (MmioRead32 (GbePciBase) != 0xFFFFFFFF);

  //
  // Set LOCKLANDIS, GbE PCI config + 0xA4 bit[0] to 1
  //
  MmioOr32 (GbePciBase + R_PCH_LAN_LOCKLANDIS, B_PCH_LAN_LOCKLANDIS_LOCK);

  //
  // LAN function is hidden now
  //
  ASSERT (MmioRead32 (GbePciBase) == 0xFFFFFFFF);

  PchPwrmBaseGet (&PwrmBase);
  //
  // Before modifying LAN Disable bit, make sure it's not locked and not disabled yet
  //
  ASSERT ((MmioRead32 (PwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1) & B_PCH_PWRM_ST_PG_FDIS_PMC_1_ST_FDIS_LK) == 0);
  ASSERT ((MmioRead32 (PwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1) & B_PCH_PWRM_ST_PG_FDIS_PMC_1_GBE_FDIS_PMC) == 0);

  //
  // Set PWRMBASE + 620h[0] = 1b to statically disable GbE Controller
  //
  MmioOr32 (PwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1, B_PCH_PWRM_ST_PG_FDIS_PMC_1_GBE_FDIS_PMC);
  //
  // Read back for posted write to take effect
  //
  MmioRead32 (PwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1);
}

/**
  Configure LAN device registers based on policy settings.
  @param[in] SiPolicy             The SI Policy PPI instance
  @param[in] TempMemBaseAddr      Temporary Memory Base Address for PCI
                                  devices to be used to initialize MMIO
                                  registers.
**/
STATIC
VOID
PchConfigureGbeRegisters (
  IN  SI_POLICY_PPI               *SiPolicy,
  IN  UINT32                      TempMemBaseAddr
  )
{
  UINTN           GbePciBase;
  UINT32          GbeMemBar;
  PCH_SERIES      PchSeries;
  EFI_STATUS      Status;
  PCH_LAN_CONFIG  *LanConfig;
  PCH_PM_CONFIG   *PmConfig;

  DEBUG ((DEBUG_INFO, "ConfigureGbe\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gLanConfigGuid, (VOID *) &LanConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);

  PchSeries = GetPchSeries ();

  GbePciBase = MmPciBase (
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_LAN,
                 PCI_FUNCTION_NUMBER_PCH_LAN
                 );

  ASSERT (LanConfig->Enable);
  ASSERT (MmioRead32 (GbePciBase) != 0xFFFFFFFF);

  //
  // Set GbE PCI config + 0x80 (CPCE) bit[5] (HAE) = 1
  //
  MmioOr32 (GbePciBase + R_PCH_LAN_CPCE, B_PCH_LAN_CPCE_HAE);

  //
  // Set GbE PCI config + 0x94 (clock control of GBE) to 0x1F
  // To avoid blocking PCH floor power measurement when GbE enabled.
  //
  MmioWrite8 (GbePciBase + R_PCH_LAN_CLCTL, 0x1F);

  //
  // Set LOCKLANDIS, GbE PCI config + 0xA4 bit[0]
  //
  MmioOr32 (GbePciBase + R_PCH_LAN_LOCKLANDIS, B_PCH_LAN_LOCKLANDIS_LOCK);

  //
  //
  // LAN LTR Programming
  // The maximum snoop/non-snoop platform latency values to 3ms
  // Program GbE controller's PCI LTR capability register at D31:F6:Reg 0A8h
  //
  if (LanConfig->LtrEnable == TRUE) {
    MmioWrite32 (GbePciBase + R_PCH_LAN_LTR_CAP, 0x10031003);
  }

  //
  // Assign MMIO resource to Gbe controller
  //
  GbeMemBar = TempMemBaseAddr;
  MmioWrite32 (GbePciBase + R_PCH_LAN_MBARA, GbeMemBar);
  MmioOr16 (GbePciBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);

  //
  // Additional GbE Controller Configurations for WOL Support
  // System BIOS requires to program the registers listed below for internal GbE.
  // 1. Set MBARA + 2Ch[31] = 1b
  // 2. If WOL is enabled set MBARA + Offset 2Ch[30] = 1b
  //    Else if disabled set MBARA + 2Ch[30] = 0b
  //
  if (PmConfig->WakeConfig.WolEnableOverride) {
    MmioOr32 (GbeMemBar + R_PCH_LAN_CSR_FEXT, B_PCH_LAN_CSR_FEXT_WOL | B_PCH_LAN_CSR_FEXT_WOL_VALID);
  } else {
    MmioAndThenOr32 (GbeMemBar + R_PCH_LAN_CSR_FEXT, (UINT32) ~(B_PCH_LAN_CSR_FEXT_WOL), B_PCH_LAN_CSR_FEXT_WOL_VALID);
  }

  //
  // Enable K1 off to use CLKREQ for GbE
  //
  if (LanConfig->K1OffEnable) {
    if (LanConfig->ClkReqSupported) {
      MmioOr32 (GbeMemBar + R_PCH_LAN_CSR_F18, B_PCH_LAN_CSR_F18_K1OFF_EN);
      DEBUG ((DEBUG_INFO, "K1Off enabled.\n"));
    } else {
      DEBUG ((DEBUG_ERROR, "Error: K1Off requires CLKREQ# support -- disabled!\n"));
    }
  }

  //
  // Enable internal ECC for Gbe Controller
  // Set GbeMemBar + 0x100c [16] to 1b
  // Set GbeMemBar + 0 [19] to 1b
  //
  MmioOr32 (GbeMemBar + R_PCH_LAN_CSR_PBECCSTS, B_PCH_LAN_CSR_PBECCSTS_ECC_EN);
  MmioOr32 (GbeMemBar + R_PCH_LAN_CSR_CTRL, B_PCH_LAN_CSR_CTRL_MEHE);

  //
  // Disable memory space decoding
  //
  MmioAnd16 (GbePciBase + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  MmioWrite32 (GbePciBase + R_PCH_LAN_MBARA, 0);
}


/**
  Initialize LAN device.

  Global reset may be perfomed due to static power gating requirements.

  @param[in] SiPolicy             The SI Policy PPI instance
  @param[in] TempMemBaseAddr      Temporary Memory Base Address for PCI
                                  devices to be used to initialize MMIO
                                  registers.
**/
VOID
PchConfigureLan (
  IN  SI_POLICY_PPI               *SiPolicy,
  IN  UINT32                      TempMemBaseAddr
  )
{
  UINT32                          PchPwrmBase;
  EFI_STATUS                      Status;
  PCH_LAN_CONFIG                  *LanConfig;

  DEBUG ((DEBUG_INFO, "PchConfigureLan() Start\n"));
  Status = GetConfigBlock ((VOID *) SiPolicy, &gLanConfigGuid, (VOID *) &LanConfig);
  ASSERT_EFI_ERROR (Status);

  PchPwrmBaseGet (&PchPwrmBase);

  DEBUG ((DEBUG_INFO, "GbePmcEnabled:  %d\n",  PchPmcIsGbeEnabled ()));
  DEBUG ((DEBUG_INFO, "GbePortNumber:  %d\n",  PchGetGbePortNumber ()));
  DEBUG ((DEBUG_INFO, "GbeRegionValid: %d\n",  PchIsGbeRegionValid ()));
  DEBUG ((DEBUG_INFO, "GbePresent:     %d\n",  PchIsGbePresent ()));

  if (LanConfig->ClkReqSupported) {
    //
    // Enable CLKREQ# if supported by board regardless of GbE being enabled
    // to allow clock shut-down.
    //
    GpioEnableClkreq (LanConfig->ClkReqNumber);
  }

  if (PchPmcIsGbeEnabled ()) {
    if (LanConfig->Enable && PchIsGbePresent ()) {
      //
      // Apply GbE settings
      //
      PchConfigureGbeRegisters (SiPolicy, TempMemBaseAddr);
    } else {
      //
      // GbE is not power gated by PMC but is not available in the platform or is disabled via policy
      // Perform GbE disabling flow
      //
      PchDisableGbe ();
      //
      // Global reset is required for GbE to enter static power gating
      //
      PchGbeGlobalReset ();
      ASSERT (FALSE);
    }
  } else {
    if (LanConfig->Enable && PchIsGbePresent ()) {
      //
      // GbE is power gated but available in the platform and enabled with policy.
      // Perform enabling flow.
      //
      PchEnableGbe ();
      //
      // Global reset is required to get GbE out of static power gating
      //
      PchGbeGlobalReset ();
      ASSERT (FALSE);
    } else {
      DEBUG ((DEBUG_INFO, "LAN disabled\n"));
    }
  }
  DEBUG ((DEBUG_INFO, "PchConfigureLan() End\n"));
}

