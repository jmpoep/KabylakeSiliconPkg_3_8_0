/** @file
  This files contains Pch Cio2 PPI routines and internal Cio2 routines

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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
#include <Library/PostCodeLib.h>

/**
  Performs Global Reset required to change CIO2 static power gating state.
**/
STATIC
VOID
Cio2PerformGlobalReset (
  VOID
  )
{
  PCH_RESET_DATA             ResetData;

  PostCode (0xB17);
  DEBUG ((DEBUG_INFO, "Cio2PerformGlobalReset()\n"));

  CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
  StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
  (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetPlatformSpecific, EFI_SUCCESS, sizeof (PCH_RESET_DATA), &ResetData);

  ASSERT (FALSE);
}

/**
  Disable CIO2 device
**/
VOID
PchDisableCio2 (
  VOID
  )
{
  UINTN  BaseAddress;
  UINT32 PchPwrmBase;

  DEBUG ((DEBUG_INFO, "PchDisableCio2() - Start\n"));

  PchPwrmBaseGet (&PchPwrmBase);
  BaseAddress = MmPciBase (
                  DEFAULT_PCI_BUS_NUMBER_PCH,
                  PCI_DEVICE_NUMBER_PCH_CIO2,
                  PCI_FUNCTION_NUMBER_PCH_CIO2
                  );

  //
  // Power off the CIO2 core - put the device into D3HOT through the PS (bits 1:0) of CFG_PMCSR configuration register
  //
  DEBUG ((DEBUG_INFO, "Powering off CIO2 core\n"));
  MmioOr8 (BaseAddress + R_PCH_CIO2_CFG_PMCSR, V_PCH_CIO2_CFG_PMCSR_PS_D3HOT);

  //
  // Perform PSF function disable
  //
  DEBUG ((DEBUG_INFO, "PSF function disable\n"));
  PsfDisableCio2Device ();

  //
  // CAM PMC function disable (PWRM + 620h) [6] = 1 to disable CAM IP
  //
  DEBUG ((DEBUG_INFO, "CAMERA found enabled and requested to be disabled - set PG bit and issue reset!\n"));
  MmioOr32 (PchPwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1, B_PCH_PWRM_ST_PG_FDIS_PMC_1_CAM_FDIS_PMC);

  //
  // Perform reset for disabling to take effect
  //
  Cio2PerformGlobalReset ();
}

/**
  Program private FLS registers of CSI
**/
VOID
Cio2ProgramFlsRegisters (
  IN  SI_POLICY_PPI     *SiPolicy
  )
{
  UINT32           Data32;
  UINT32           Status;
  UINT8            Response;
  PCH_CIO2_CONFIG  *Cio2Config;
  //
  // For PCH B1 and above, only program Port C = 0
  // for LP B0 stepping
  // Program RXCNTRL=0x1FF81 for each SkyCam port A,B,C if workaround is enable
  // Program RXCNTRL=0x19 for SkyCam port D if workaround is enable and Port C must be 0x1FF81 or 1FF80
  // Note: The following PCR registers must use SBI method and not MMIO PCR
  //
  DEBUG ((DEBUG_INFO, "Cio2ProgramFlsRegisters() - Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gCio2ConfigGuid, (VOID *) &Cio2Config);
  ASSERT_EFI_ERROR (Status);

  if (PchStepping () >= PchLpB1) {

    // RXCNTRL
    Data32 = 0;
    Status = PchSbiExecution (
               PID_CAM_FLS,
               R_PCH_PCR_CAM_FLIS_CSI2_RXCNTRL,
               PrivateControlWrite,
               FALSE,
               &Data32,
               &Response
               );
    ASSERT_EFI_ERROR (Status);

    // CTLE
    Data32 = (Cio2Config->PortACtleCapValue |
              (Cio2Config->PortBCtleCapValue << 10) |
              (Cio2Config->PortCDCtleCapValue << 20) |
              (Cio2Config->PortACtleResValue << 4) |
              (Cio2Config->PortBCtleResValue << 14) |
              (Cio2Config->PortCDCtleResValue << 24) |
              (Cio2Config->PortACtleEnable << 9) |
              (Cio2Config->PortBCtleEnable << 19) |
              (Cio2Config->PortCDCtleEnable << 29));
    Status = PchSbiExecution (
               PID_CAM_FLS,
               R_PCH_PCR_CAM_FLIS_CSI_CTLE,
               PrivateControlWrite,
               FALSE,
               &Data32,
               &Response
               );
    ASSERT_EFI_ERROR (Status);

    // CLKTRIM
    Data32 = (Cio2Config->PortAClkTrimValue |
              (Cio2Config->PortBClkTrimValue << 4) |
              (Cio2Config->PortCClkTrimValue << 8) |
              (Cio2Config->PortDClkTrimValue << 12) |
              (Cio2Config->PortATrimEnable << 16) |
              (Cio2Config->PortBTrimEnable << 17) |
              (Cio2Config->PortCTrimEnable << 18) |
              (Cio2Config->PortDTrimEnable << 19));
    Status = PchSbiExecution (
               PID_CAM_FLS,
               R_PCH_PCR_CAM_FLIS_CSI_CLKTRIM,
               PrivateControlWrite,
               FALSE,
               &Data32,
               &Response
               );
    ASSERT_EFI_ERROR (Status);

    // DATATRIM
    Data32 = (Cio2Config->PortADataTrimValue |
              (Cio2Config->PortBDataTrimValue << 16));
    Status = PchSbiExecution (
               PID_CAM_FLS,
               R_PCH_PCR_CAM_FLIS_CSI_DATATRIM,
               PrivateControlWrite,
               FALSE,
               &Data32,
               &Response
               );
    ASSERT_EFI_ERROR (Status);

    // DATATRIM1
    Data32 = Cio2Config->PortCDDataTrimValue;
    Status = PchSbiExecution (
               PID_CAM_FLS,
               R_PCH_PCR_CAM_FLIS_CSI_DATATRIM1,
               PrivateControlWrite,
               FALSE,
               &Data32,
               &Response
               );
    ASSERT_EFI_ERROR (Status);

    Data32 = 0;
    Status = PchSbiExecution (
               PID_CAM_FLS,
               R_PCH_PCR_CAM_FLIS_CSI_CFG,
               PrivateControlRead,
               FALSE,
               &Data32,
               &Response
               );
    ASSERT_EFI_ERROR (Status);

    Data32 |= B_PCH_PCR_CAM_FLIS_CSI_CFG_ACIO_LB_EN;
    Status = PchSbiExecution (
               PID_CAM_FLS,
               R_PCH_PCR_CAM_FLIS_CSI_CFG,
               PrivateControlWrite,
               FALSE,
               &Data32,
               &Response
               );
    ASSERT_EFI_ERROR (Status);

  } else {
    if (Cio2Config->SkyCamPortATermOvrEnable == TRUE) {
      Data32 = 0x1FF81;
      Status = PchSbiExecution (
                 PID_CAM_FLS,
                 R_PCH_PCR_CAM_FLIS_CSI0_RXCNTRL,
                 PrivateControlWrite,
                 FALSE,
                 &Data32,
                 &Response
                 );
      ASSERT_EFI_ERROR (Status);
    }

    if (Cio2Config->SkyCamPortBTermOvrEnable == TRUE) {
      Data32 = 0x1FF81;
      Status = PchSbiExecution (
                 PID_CAM_FLS,
                 R_PCH_PCR_CAM_FLIS_CSI1_RXCNTRL,
                 PrivateControlWrite,
                 FALSE,
                 &Data32,
                 &Response
                 );
      ASSERT_EFI_ERROR (Status);
    }

    if (Cio2Config->SkyCamPortCTermOvrEnable == TRUE) {
      Data32 = 0x1FF81;
    } else {
      Data32 = 0x1FF80;
    }
    Status = PchSbiExecution (
               PID_CAM_FLS,
               R_PCH_PCR_CAM_FLIS_CSI2_RXCNTRL,
               PrivateControlWrite,
               FALSE,
               &Data32,
               &Response
               );
    ASSERT_EFI_ERROR (Status);

    if (Cio2Config->SkyCamPortDTermOvrEnable == TRUE) {
      Data32 = 0x19;
      Status = PchSbiExecution (
                 PID_CAM_FLS,
                 R_PCH_PCR_CAM_FLIS_CSI3_RXCNTRL,
                 PrivateControlWrite,
                 FALSE,
                 &Data32,
                 &Response
                 );
      ASSERT_EFI_ERROR (Status);
    }
  }

  DEBUG ((DEBUG_INFO, "Cio2ProgramFlsRegisters() - End\n"));
  return;
}

/**
  Initialize CIO2 according to Cio2Config policy of the SI Policy PPI

  @param[in] SiPolicy  The SI Policy PPI instance

  @retval EFI_SUCCESS             Succeeds.
**/
EFI_STATUS
PchCio2Init (
  IN  SI_POLICY_PPI     *SiPolicy
  )
{
  EFI_STATUS       Status;
  UINT32           PchPwrmBase;
  UINT32           FuseDis2State;
  PCH_CIO2_CONFIG  *Cio2Config;

  DEBUG ((DEBUG_INFO, "PchCio2Init() - Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gCio2ConfigGuid, (VOID *) &Cio2Config);
  ASSERT_EFI_ERROR (Status);

  //
  // Get fuse info from PWRMBASE + FUSE_DIS_RD_2 (Offset 644h)
  //
  PchPwrmBaseGet (&PchPwrmBase);
  FuseDis2State = MmioRead32 ((UINTN) (PchPwrmBase + R_PCH_PWRM_FUSE_DIS_RD_2));

  if (Cio2Config->DeviceEnable == 0) {
    //
    // Check if fuse disabled
    //
    if (FuseDis2State & B_PCH_PWRM_FUSE_DIS_RD_2_CAM_FUSE_SS_DIS) {
      //
      // PSF Function Disable set in PchEarlyDisabledDeviceHandling()
      //
      DEBUG ((DEBUG_INFO, "PSF Function Disable already set\n"));
      return EFI_SUCCESS;
    }
    //
    // Check if CAM is static power gated
    //
    if (MmioRead32 (PchPwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1) & B_PCH_PWRM_ST_PG_FDIS_PMC_1_CAM_FDIS_PMC) {
      DEBUG ((DEBUG_INFO, "CAMERA found already static power gated\n"));
      return EFI_SUCCESS;
    }
    PchDisableCio2 ();
  } else {
    //
    // Check if fuse disabled
    //
    if (FuseDis2State & B_PCH_PWRM_FUSE_DIS_RD_2_CAM_FUSE_SS_DIS) {
      //
      // PSF Function Disable set in PchEarlyDisabledDeviceHandling()
      //
      DEBUG ((DEBUG_INFO, "Don't try to enable CIO2 as it has been fused out\n"));
      return EFI_UNSUPPORTED;
    }

    //
    // If CAM is static power gated but has not been fused out, clear the static power gate bit and do a reset.
    //
    if (MmioRead32 (PchPwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1) & B_PCH_PWRM_ST_PG_FDIS_PMC_1_CAM_FDIS_PMC) {
      DEBUG ((DEBUG_INFO, "CAMERA found disabled and requested to be enabled - clear PG bit in PMC and issue reset!\n"));
      //
      // CAM PMC function disable (PWRMBASE + 620h) [6] = 0 to enable CAM IP
      //
      MmioAnd32 (PchPwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1, (UINT32) ~B_PCH_PWRM_ST_PG_FDIS_PMC_1_CAM_FDIS_PMC);

      //
      // Perform reset for enabling to take effect
      //
      Cio2PerformGlobalReset ();
    }
  }
  DEBUG ((DEBUG_INFO, "PchCio2Init() - End\n"));

  return EFI_SUCCESS;
}

/**
   Finalize CIO2 configuration: power off CSI2 HC core logic and lock registers

   @param[in] SiPolicy                  The SI Policy PPI instance
   @param[in] TempMemBaseAddr           Temporary Memory Base Address for PCI
                                        devices to be used to initialize MMIO
                                        registers.

   @retval EFI_SUCCESS                  Succeeds.
   @retval EFI_DEVICE_ERROR             Device error, aborts abnormally.
**/
EFI_STATUS
PchCio2FinalizeDeviceConfiguration (
  IN  SI_POLICY_PPI                     *SiPolicy,
  IN  UINT32                            TempMemBaseAddr
  )
{
  EFI_STATUS       Status;
  UINTN            Cio2Base;
  UINTN            CamMMIOBase;
  UINT32           PchPwrmBase;
  PCH_STEPPING     PchStep;
  UINT32           Data32;

  DEBUG ((DEBUG_INFO, "PchCio2FinalizeDeviceConfiguration() - Start\n"));
  /// Check if PCH PWRM Base has been set
  Status = PchPwrmBaseGet (&PchPwrmBase);
  PchStep = PchStepping ();

  // Check if CIO2 was enabled...
  Cio2Base = MmPciBase (
               DEFAULT_PCI_BUS_NUMBER_PCH,
               PCI_DEVICE_NUMBER_PCH_CIO2,
               PCI_FUNCTION_NUMBER_PCH_CIO2
               );

  if (MmioRead16 (Cio2Base + PCI_VENDOR_ID_OFFSET) != 0xFFFF) {
    DEBUG ((DEBUG_INFO, "Cio2 Enabled\n"));

    PostCode (0xB18);
    Cio2ProgramFlsRegisters (SiPolicy);

    //
    // PWRMBASE + 0x31C [12] = 0 for PchLpC0 and above
    // PWRMBASE + 0x31C [12] = 1 for older steppings
    //
    ConfigurePmcWhenCio2Disabled (FALSE);
    //
    // CIO2 is enabled -to finalize the initialization CSI2 HC core logic must be powered off
    //
    if (PchStep >= PchLpC0) {
      CamMMIOBase = TempMemBaseAddr;
      MmioWrite8 (Cio2Base + R_PCH_CIO2_CFG_MID_MMC + 1, (UINT8) R_PCH_CIO2_CFG_PID_PC);
    } else {
      CamMMIOBase = PCH_CIO2_BASE_ADDRESS;
    }
    //
    // Since CAM_MMIO_CSI2 Base Address is not defined here yet, a temporary Base Address must be written to CAM BAR
    // disable MSE
    //
    MmioAnd32 (Cio2Base + PCI_COMMAND_OFFSET, (UINT32) ~EFI_PCI_COMMAND_MEMORY_SPACE);
    //
    // write temp address to lower base
    //
    MmioWrite32 (Cio2Base + R_PCH_CIO2_CIOLBA, CamMMIOBase);
    //
    // and clear the upper base
    //
    MmioWrite32 (Cio2Base + R_PCH_CIO2_CIOUBA, 0);

    //
    //enable MSE and BME
    //
    MmioOr32 (Cio2Base + PCI_COMMAND_OFFSET, (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER));
    //
    // D3HOT and I3 Enable
    // PCE (0x1430[2]) = 1b
    // PCE (0x1430[1]) = 1b
    //
    DEBUG ((DEBUG_INFO, "PCE: D3HOT and I3 Enable\n"));
    MmioOr8 (CamMMIOBase + R_PCH_CAM_MMIO_PRI_PCE, B_PCH_CAM_MMIO_PRI_PCE_D3HE | B_PCH_CAM_MMIO_PRI_PCE_I3E);
    //
    //  Store values of LTRs for CIO2 HC driver
    //
    MmioWrite32 (CamMMIOBase + R_PCH_CAM_MMIO_PRI_CIO2_GPR0, 0x01134640);
    MmioWrite32 (CamMMIOBase + R_PCH_CAM_MMIO_PRI_CIO2_GPR1, 0x000031C0);
    //
    // Set CIO2_D0I3C_I3 which moves CAM IP to D0i3 state (internal power off)
    //
    MmioWrite8 (CamMMIOBase + R_PCH_CAM_MMIO_PRI_CIO2_D0I3C, B_PCH_CAM_MMIO_PRI_CIO2_D0I3C_I3);

    //
    // Enable clock gating
    //
    Data32 = MmioRead32 (CamMMIOBase + R_PCH_CAM_MMIO_PRI_CIO2_CGC);
    Data32 |= V_PCH_CAM_MMIO_PRI_CIO2_CGC_CLK_GATING_EN;
    MmioWrite32 (CamMMIOBase + R_PCH_CAM_MMIO_PRI_CIO2_CGC, Data32);

    if (PchStep >= PchLpC0) {
      //
      // disable MSE and BME
      //
      MmioAnd32 (Cio2Base + PCI_COMMAND_OFFSET, (UINT32) ~(EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER));
      //
      // clear lower base
      //
      MmioWrite32 (Cio2Base + R_PCH_CIO2_CIOLBA, 0);
    } else {
      //
      // when working in ACPI mode, hide CIO2 Device using PSF (Config Disable)
      //
      PsfHideCio2Device ();
    }
  } else {
    DEBUG ((DEBUG_INFO, "CIO2 disabled\n"));

    ///
    /// PWRMBASE + 0x31C [12] = 1
    ///
    ConfigurePmcWhenCio2Disabled (TRUE);
  }
  //
  // Lock all lockable fields in CAM CFG space
  //
  PostCode (0xB19);
  DEBUG ((DEBUG_INFO, "Lock registers\n"));
  PchPcrAndThenOr8 (
    PID_CAM_CHC,
    R_PCH_PCR_CAM_CHC_PVT_FNCFG,
    (UINT8) ~0,
    B_PCH_PCR_CAM_CHC_PVT_FNCFG_BCLD
    );

  DEBUG ((DEBUG_INFO, "PchCio2FinalizeDeviceConfiguration() - End\n"));
  return EFI_SUCCESS;
}

