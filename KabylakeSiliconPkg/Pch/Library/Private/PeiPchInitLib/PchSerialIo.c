/** @file
  Initializes Serial IO Controllers.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2016 Intel Corporation.

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
#include <Library/PchSerialIoLib.h>

UINT32 mFunctionDisableBits[PCH_SERIALIO_MAX_CONTROLLERS] = {
  B_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C0_FDIS_PMC,
  B_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C1_FDIS_PMC,
  B_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C2_FDIS_PMC,
  B_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C3_FDIS_PMC,
  B_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C4_FDIS_PMC,
  B_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C5_FDIS_PMC,
  B_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_GSPI0_FDIS_PMC,
  B_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_GSPI1_FDIS_PMC,
  B_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_UART0_FDIS_PMC,
  B_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_UART1_FDIS_PMC,
  B_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_UART2_FDIS_PMC
};

BOOLEAN
IsWholeSerialIoDisabled (
  UINT32 FunctionDisableMask
  )
{
  if ((FunctionDisableMask & V_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_FDIS_PMC) ==
      V_PCH_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_FDIS_PMC ) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Configures Serial IO Controllers

  @param[in] SiPolicy

  @retval None
**/
VOID
ConfigureSerialIoPei (
  IN SI_POLICY_PPI           *SiPolicy
  )
{
  PCH_SERIAL_IO_CONTROLLER    Controller;
  UINT32                      PchPwrmBase;
  UINT32                      OldFunctionDisableMask;
  UINT32                      NewFunctionDisableMask;
  EFI_STATUS                  Status;
  PCH_SERIAL_IO_CONFIG        *SerialIoConfig;
  PCH_RESET_DATA              ResetData;

  DEBUG ((DEBUG_INFO, "ConfigureSerialIoPei() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSerialIoConfigGuid, (VOID *) &SerialIoConfig);
  ASSERT_EFI_ERROR (Status);

  PchPwrmBaseGet (&PchPwrmBase);

  NewFunctionDisableMask = 0;
  OldFunctionDisableMask = MmioRead32 (PchPwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_2);

  //
  // enable clock gating and power gating
  //
  PchPcrAndThenOr32 (PID_SERIALIO, R_PCH_PCR_SERIAL_IO_GPPRVRW2, 0xFFFFFFFF, V_PCH_PCR_SERIAL_IO_GPPRVRW2_CLK_GATING);
  PchPcrAndThenOr32 (PID_SERIALIO, R_PCH_PCR_SERIAL_IO_PMCTL   , 0xFFFFFFFF, V_PCH_PCR_SERIAL_IO_PMCTL_PWR_GATING);

  for (Controller = 0; Controller < PchSerialIoIndexMax; Controller++) {
    ConfigureSerialIoController (Controller, SerialIoConfig->DevMode[Controller]);
  }

  for (Controller = 0; Controller < PchSerialIoIndexMax; Controller++) {
    if (SerialIoConfig->DevMode[Controller] == PchSerialIoDisabled) {
      NewFunctionDisableMask |= mFunctionDisableBits[Controller];
    }
  }

  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_2, NewFunctionDisableMask);
  if ( IsWholeSerialIoDisabled (OldFunctionDisableMask) &&
       !IsWholeSerialIoDisabled (NewFunctionDisableMask)) {
    DEBUG ((DEBUG_INFO, "Reset due to changes in SerialIo FunctionDisable (%x->%x)\n", OldFunctionDisableMask, NewFunctionDisableMask));
    CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
    StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
    (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetPlatformSpecific, EFI_SUCCESS, sizeof (PCH_RESET_DATA), &ResetData);

    CpuDeadLoop ();
  }

  for (Controller = PchSerialIoIndexI2C0; Controller <= GetMaxI2cNumber (); Controller++) {
    SerialIoI2cGpioInit (Controller, SerialIoConfig->DevMode[Controller], SerialIoConfig->I2cVoltage[Controller]);
  }
  for (Controller = PchSerialIoIndexSpi0; Controller <= PchSerialIoIndexSpi1; Controller++) {
    SerialIoSpiGpioInit (Controller, SerialIoConfig->DevMode[Controller], SerialIoConfig->SpiCsPolarity[Controller-PchSerialIoIndexSpi0]);
  }
  for (Controller = PchSerialIoIndexUart0; Controller <= PchSerialIoIndexUart2; Controller++) {
    SerialIoUartGpioInit (Controller, SerialIoConfig->DevMode[Controller], SerialIoConfig->UartHwFlowCtrl[Controller-PchSerialIoIndexUart0]);
  }
  DEBUG ((DEBUG_INFO, "ConfigureSerialIoPei() End\n"));
}

/**
  Puts all SerialIo controllers (except UARTs in debug mode) in D3.
  Clears MemoryEnable for all PCI-mode controllers
**/
VOID
ConfigureSerialIoAtS3Resume (
  IN SI_POLICY_PPI           *SiPolicy
  )
{
  PCH_SERIAL_IO_CONTROLLER    Index;
  UINTN                       PciCfgBase;
  EFI_STATUS                  Status;
  PCH_SERIAL_IO_CONFIG        *SerialIoConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSerialIoConfigGuid, (VOID *) &SerialIoConfig);
  ASSERT_EFI_ERROR (Status);

  for (Index = 0; Index < PchSerialIoIndexMax; Index++) {
    if ((SerialIoConfig->DevMode[Index] == PchSerialIoDisabled) ||
        (SerialIoConfig->DevMode[Index] == PchSerialIoSkipInit)) {
      continue;
    }
    if ((Index >= PchSerialIoIndexUart0) &&
        (SerialIoConfig->EnableDebugUartAfterPost) &&
        (SerialIoConfig->DebugUartNumber == (UINT32) (Index - PchSerialIoIndexUart0))) {
      continue;
    }
    PciCfgBase = FindSerialIoBar (Index,1);
    MmioOr32 (PciCfgBase + R_PCH_SERIAL_IO_PME_CTRL_STS, B_PCH_SERIAL_IO_PME_CTRL_STS_PWR_ST);
    MmioRead32 (PciCfgBase + R_PCH_SERIAL_IO_PME_CTRL_STS);

    if (SerialIoConfig->DevMode[Index] == PchSerialIoPci) {
      MmioAnd32 (PciCfgBase + PCI_COMMAND_OFFSET, (UINT32) ~(EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER));
    }
  }
}

