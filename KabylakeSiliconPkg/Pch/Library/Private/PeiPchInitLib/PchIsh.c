/** @file
  Initializes Integrated Sensor Hub Controller (ISH3.0).

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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
#include <Private/Library/GpioPrivateLib.h>

/**
  Configures ISH-related GPIO pins to ISH native mode
**/
VOID
SetIshGpio (
  IN  SI_POLICY_PPI    *SiPolicy
  )
{
  EFI_STATUS            Status;
  PCH_ISH_CONFIG        *IshConfig;

  DEBUG ((DEBUG_INFO, "SetIshGpio() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gIshConfigGuid, (VOID *) &IshConfig);
  ASSERT_EFI_ERROR (Status);

  if (IshConfig->SpiGpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH SPI pins set to Native Mode\n"));
    GpioSetIshSpiPinsIntoNativeMode ();
  }
  if (IshConfig->Uart0GpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH UART0 pins set to Native Mode\n"));
    GpioSetIshUartPinsIntoNativeMode (0);
  }
  if (IshConfig->Uart1GpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH UART1 pins set to Native Mode\n"));
    GpioSetIshUartPinsIntoNativeMode (1);
  }
  if (IshConfig->I2c0GpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH I2C0 pins set to Native Mode\n"));
    GpioSetIshI2cPinsIntoNativeMode (0);
  }
  if (IshConfig->I2c1GpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH I2C1 pins set to Native Mode\n"));
    GpioSetIshI2cPinsIntoNativeMode (1);
  }
  if (IshConfig->I2c2GpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH I2C2 pins set to Native Mode\n"));
    GpioSetIshI2cPinsIntoNativeMode (2);
  }
  if (IshConfig->Gp0GpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH GP_0 pin set to Native Mode\n"));
    GpioSetIshGpPinsIntoNativeMode (0);
  }
  if (IshConfig->Gp1GpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH GP_1 pin set to Native Mode\n"));
    GpioSetIshGpPinsIntoNativeMode (1);
  }
  if (IshConfig->Gp2GpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH GP_2 pin set to Native Mode\n"));
    GpioSetIshGpPinsIntoNativeMode (2);
  }
  if (IshConfig->Gp3GpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH GP_3 pin set to Native Mode\n"));
    GpioSetIshGpPinsIntoNativeMode (3);
  }
  if (IshConfig->Gp4GpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH GP_4 pin set to Native Mode\n"));
    GpioSetIshGpPinsIntoNativeMode (4);
  }
  if (IshConfig->Gp5GpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH GP_5 pin set to Native Mode\n"));
    GpioSetIshGpPinsIntoNativeMode (5);
  }
  if (IshConfig->Gp6GpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH GP_6 pin set to Native Mode\n"));
    GpioSetIshGpPinsIntoNativeMode (6);
  }
  if (IshConfig->Gp7GpioAssign) {
    DEBUG ((DEBUG_INFO, "ISH GP_7 pin set to Native Mode\n"));
    GpioSetIshGpPinsIntoNativeMode (7);
  }
}

/**
  Configures Integrated Sensor Hub (ISH) Controller

  @param[in] SiPolicy

  @retval EFI_SUCCESS       The function completed successfully
  @retval EFI_UNSUPPORTED   Controller fuse disabled
**/
EFI_STATUS
ConfigureIsh (
  IN  SI_POLICY_PPI   *SiPolicy
  )
{
  EFI_STATUS              Status;
  UINT32                  PchPwrmBase;
  UINT32                  FuseDis2State;
  UINT32                  StPg1State;
  PCH_RESET_DATA          ResetData;

  DEBUG ((DEBUG_INFO, "ConfigureIsh() Start\n"));

  Status = EFI_SUCCESS;

  PchPwrmBaseGet (&PchPwrmBase);
  //
  // Get fuse info from PWRMBASE + FUSE_DIS_RD_2 (Offset 644h)
  //
  FuseDis2State = MmioRead32 ((UINTN) (PchPwrmBase + R_PCH_PWRM_FUSE_DIS_RD_2));

  //
  // Check if fuse disabled
  //
  if (FuseDis2State & B_PCH_PWRM_FUSE_DIS_RD_2_ISH_FUSE_SS_DIS) {
    //
    // PSF Function Disable set in PchEarlyDisabledDeviceHandling()
    //
    DEBUG ((DEBUG_INFO, "ISH Fuse disabled - PSF Function Disable already set!\n"));
    return EFI_UNSUPPORTED;
  }

  //
  // Get PG info from PWRMBASE + ST_PG_FDIS_PMC_1 (Offset 620h)
  //
  StPg1State = MmioRead32 ((UINTN) (PchPwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1));

  //
  // Check if static PG disabled
  //
  if (StPg1State & B_PCH_PWRM_ST_PG_FDIS_PMC_1_ISH_FDIS_PMC) {
    DEBUG ((DEBUG_INFO, "ISH Static PG disabled - Enable and issue reset!\n"));

    //
    // Set PWRMBASE + 620h[5] = 0b to enable ISH controller
    //
    MmioAnd32 (PchPwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1, (UINT32) (~B_PCH_PWRM_ST_PG_FDIS_PMC_1_ISH_FDIS_PMC));

    CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
    StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
    (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetPlatformSpecific, EFI_SUCCESS, sizeof (PCH_RESET_DATA), &ResetData);
    ///
    /// Shouldn't reach here
    ///
    return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "ISH: BAR1 - Shadowed PCI Config Space Disabled\n"));
  //
  // Configure in PCI mode - disable BAR1 (Shadowed PCI)
  // PCICFGCTR.BAR1_DISABLE, offset (200h) [7] = 1b
  //
  PchPcrAndThenOr32 (
    PID_ISHBR,
    R_PCH_PCR_ISH_PCICFGCTRL,
    (UINT32) ~0,
    B_PCH_PCR_ISH_PCICFGCTRL_BAR1DIS
    );

  //
  // Disable ISH BAR1 in PSF
  //
  PsfDisableIshBar1 ();

  //
  // Power management programming
  // Set "PMCTL", PCR[ISHBR] + 1D0h[5:0] = 1111111b
  //
  PchPcrAndThenOr32 (
    PID_ISHBR,
    R_PCH_PCR_ISH_PMCTL,
    (UINT32) ~(0),
    (BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0)
    );

  SetIshGpio (SiPolicy);

  DEBUG ((DEBUG_INFO, "ConfigureIsh() End\n"));
  return EFI_SUCCESS;
}

/**
  Sets Integrated Sensor Hub (ISH) PSF Function Disable

  @retval EFI_SUCCESS
**/
EFI_STATUS
DisableIsh (
  VOID
  )
{
  UINT32          PchPwrmBase;

  DEBUG ((DEBUG_INFO, "DisableIsh() Start\n"));

  PsfDisableIshDevice ();

  PchPwrmBaseGet (&PchPwrmBase);
  //
  // Before modifying ISH Disable bit, make sure it's not locked.
  //
  if ((MmioRead32 (PchPwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1)
       &  B_PCH_PWRM_ST_PG_FDIS_PMC_1_ST_FDIS_LK) == 0) {
    //
    // Set PWRMBASE + 620h[5] = 1b to statically disable ISH Controller
    //
    MmioOr32 (PchPwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1, B_PCH_PWRM_ST_PG_FDIS_PMC_1_ISH_FDIS_PMC);
  } else {
    DEBUG ((DEBUG_ERROR, "ISH function disable bit is locked!\n"));
  }

  DEBUG ((DEBUG_INFO, "DisableIsh() End \n"));
  return EFI_SUCCESS;
}

/**
  Initialize Integrated Sensor Hub (ISH)

  @param[in] SiPolicy

  @retval EFI_SUCCESS       Initialized successfully
  @retval EFI_UNSUPPORTED   Controller fuse disabled
**/
EFI_STATUS
PchIshInit (
  IN  SI_POLICY_PPI    *SiPolicy
  )
{
  EFI_STATUS            Status;
  PCH_ISH_CONFIG        *IshConfig;

  DEBUG ((DEBUG_INFO, "PchIshInit() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gIshConfigGuid, (VOID *) &IshConfig);
  ASSERT_EFI_ERROR (Status);

  if (IshConfig->Enable == TRUE) {
    // Initialize ISH
    Status = ConfigureIsh (SiPolicy);
  } else {
    // Disable ISH
    Status = DisableIsh ();
  }

  DEBUG ((DEBUG_INFO, "PchIshInit() End - Status = %r\n", Status));
  return Status;
}
