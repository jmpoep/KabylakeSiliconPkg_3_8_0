/** @file
  This file contains PSF routines

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation.

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
#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <PchAccess.h>
#include <Library/PchPcrLib.h>
#include <Library/PchPsfLib.h>
#include <Library/PchInfoLib.h>
#include <Library/MeChipsetLib.h>  // AdvancedFeaturesContent

GLOBAL_REMOVE_IF_UNREFERENCED UINT32 mPchLpSerialIoPsfRegs[PCH_SERIALIO_MAX_CONTROLLERS] =
{
  R_PCH_LP_PCR_PSF3_T0_SHDW_I2C0_REG_BASE,
  R_PCH_LP_PCR_PSF3_T0_SHDW_I2C1_REG_BASE,
  R_PCH_LP_PCR_PSF3_T0_SHDW_I2C2_REG_BASE,
  R_PCH_LP_PCR_PSF3_T0_SHDW_I2C3_REG_BASE,
  R_PCH_LP_PCR_PSF3_T0_SHDW_I2C4_REG_BASE,
  R_PCH_LP_PCR_PSF3_T0_SHDW_I2C5_REG_BASE,
  R_PCH_LP_PCR_PSF3_T0_SHDW_SPI0_REG_BASE,
  R_PCH_LP_PCR_PSF3_T0_SHDW_SPI1_REG_BASE,
  R_PCH_LP_PCR_PSF3_T0_SHDW_UART0_REG_BASE,
  R_PCH_LP_PCR_PSF3_T0_SHDW_UART1_REG_BASE,
  R_PCH_LP_PCR_PSF3_T0_SHDW_UART2_REG_BASE
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT32 mPchHSerialIoPsfRegs[PCH_SERIALIO_MAX_CONTROLLERS] =
{
  R_PCH_H_PCR_PSF3_T0_SHDW_I2C0_REG_BASE,
  R_PCH_H_PCR_PSF3_T0_SHDW_I2C1_REG_BASE,
  R_PCH_H_PCR_PSF3_T0_SHDW_I2C2_REG_BASE,
  R_PCH_H_PCR_PSF3_T0_SHDW_I2C3_REG_BASE,
  0,
  0,
  R_PCH_H_PCR_PSF3_T0_SHDW_SPI0_REG_BASE,
  R_PCH_H_PCR_PSF3_T0_SHDW_SPI1_REG_BASE,
  R_PCH_H_PCR_PSF3_T0_SHDW_UART0_REG_BASE,
  R_PCH_H_PCR_PSF3_T0_SHDW_UART1_REG_BASE,
  R_PCH_H_PCR_PSF3_T0_SHDW_UART2_REG_BASE
};

/**
  This procedure will enable SerialIO device BAR1 at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)

  @retval None
**/
VOID
PsfEnableSerialIoDeviceBar1 (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  )
{
  UINT32  *SerialIoPsfReg;


  if (GetPchSeries () == PchLp) {
    SerialIoPsfReg = mPchLpSerialIoPsfRegs;
  } else {
    SerialIoPsfReg = mPchHSerialIoPsfRegs;
    if ((SerialIoDevice == PchSerialIoIndexI2C4) ||
       (SerialIoDevice == PchSerialIoIndexI2C5)) {
      ASSERT (FALSE);
    }
  }

  //
  // Set AGNT_T0_SHDW_PCIEN[19:18] = 00b
  // SerialIo device BAR is 64bit wide so to enable BAR1
  // at PSF both BAR2 (32bit wide) and BAR3 (32bit wide) need to be enabled
  //
  PchPcrAndThenOr32 (
    PID_PSF3,
    (UINT16)SerialIoPsfReg[SerialIoDevice] + R_PCH_PCR_PSFX_T0_SHDW_PCIEN,
    (UINT32)~(B_PCH_PCR_PSFX_T0_SHDW_PCIEN_BAR2DIS | B_PCH_PCR_PSFX_T0_SHDW_PCIEN_BAR3DIS),
    0
    );
}

/**
  This procedure will disable SerialIO device BAR1 at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)

  @retval None
**/
VOID
PsfDisableSerialIoDeviceBar1 (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  )
{
  UINT32  *SerialIoPsfReg;

  if (GetPchSeries () == PchLp) {
    SerialIoPsfReg = mPchLpSerialIoPsfRegs;
  } else {
    SerialIoPsfReg = mPchHSerialIoPsfRegs;
    if ((SerialIoDevice == PchSerialIoIndexI2C4) ||
       (SerialIoDevice == PchSerialIoIndexI2C5)) {
      ASSERT (FALSE);
    }
  }

  //
  // Set AGNT_T0_SHDW_PCIEN[19:18] = 11b
  // SerialIo device BAR is 64bit wide so to disable BAR1
  // at PSF both BAR2 (32bit wide) and BAR3 (32bit wide) need to be disabled
  //
  PchPcrAndThenOr32 (
    PID_PSF3,
    (UINT16)SerialIoPsfReg[SerialIoDevice] + R_PCH_PCR_PSFX_T0_SHDW_PCIEN,
    ~0u,
    (B_PCH_PCR_PSFX_T0_SHDW_PCIEN_BAR2DIS | B_PCH_PCR_PSFX_T0_SHDW_PCIEN_BAR3DIS)
    );
}

/**
  This procedure will disable SerailIO device at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)

  @retval None
**/
VOID
PsfDisableSerialIoDevice (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  )
{
  UINT32  *SerialIoPsfReg;

  if (GetPchSeries () == PchLp) {
    SerialIoPsfReg = mPchLpSerialIoPsfRegs;
  } else {
    SerialIoPsfReg = mPchHSerialIoPsfRegs;
    if ((SerialIoDevice == PchSerialIoIndexI2C4) ||
       (SerialIoDevice == PchSerialIoIndexI2C5)) {
      ASSERT (FALSE);
    }
  }

  PchPcrAndThenOr32 (
    PID_PSF3,
    (UINT16)SerialIoPsfReg[SerialIoDevice] + R_PCH_PCR_PSFX_T0_SHDW_PCIEN,
    0xFFFFFFFF,
    B_PCH_PCR_PSFX_T0_SHDW_PCIEN_FUNDIS
    );
}

/**
  This procedure will hide SerialIo device PciCfgSpace at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)

  @retval None
**/
VOID
PsfHideSerialIoDevice (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  )
{
  UINT32  *SerialIoPsfReg;

  if (GetPchSeries () == PchLp) {
    SerialIoPsfReg = mPchLpSerialIoPsfRegs;
  } else {
    SerialIoPsfReg = mPchHSerialIoPsfRegs;
    if ((SerialIoDevice == PchSerialIoIndexI2C4) ||
       (SerialIoDevice == PchSerialIoIndexI2C5)) {
      ASSERT (FALSE);
    }
  }

  PchPcrAndThenOr32 (
    PID_PSF3,
    (UINT16)SerialIoPsfReg[SerialIoDevice] + R_PCH_PCR_PSFX_T0_SHDW_CFG_DIS,
    ~0u,
    B_PCH_PCR_PSFX_T0_SHDW_CFG_DIS_CFGDIS
    );
}

/**
  This procedure will reveal SerialIo device PciCfgSpace at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)

  @retval None
**/
VOID
PsfRevealSerialIoDevice (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  )
{
  UINT32  *SerialIoPsfReg;

  if (GetPchSeries () == PchLp) {
    SerialIoPsfReg = mPchLpSerialIoPsfRegs;
  } else {
    SerialIoPsfReg = mPchHSerialIoPsfRegs;
    if ((SerialIoDevice == PchSerialIoIndexI2C4) ||
       (SerialIoDevice == PchSerialIoIndexI2C5)) {
      ASSERT (FALSE);
    }
  }

  PchPcrAndThenOr32 (
    PID_PSF3,
    (UINT16)SerialIoPsfReg[SerialIoDevice] + R_PCH_PCR_PSFX_T0_SHDW_CFG_DIS,
    (UINT32) ~(B_PCH_PCR_PSFX_T0_SHDW_CFG_DIS_CFGDIS),
    0
    );
}

/**
  This procedure will set BARx value for TraceHub ACPI device at PSF level

  @param[in] BarNum          BAR Number (0:BAR0, 1:BAR1)
  @param[in] BarValue        32bit BAR value

  @retval None
**/
VOID
PsfSetTraceHubAcpiDeviceBarValue (
  IN UINT8   BarNum,
  IN UINT32  BarValue
  )
{
  UINT16  RegOffset;

  if (BarNum > 1) {
    ASSERT (FALSE);
  }

  RegOffset = R_PCH_PCR_PSF3_T0_SHDW_TRACE_HUB_ACPI_REG_BASE + R_PCH_PCR_PSFX_T0_SHDW_BAR0 + BarNum * 0x4;

  PchPcrAndThenOr32 (
    PID_PSF3,
    RegOffset,
    0x0,
    BarValue
    );
}

/**
  This procedure will enable MSE for TraceHub ACPI device at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfEnableTraceHubAcpiDeviceMemorySpace (
  VOID
  )
{
  PchPcrAndThenOr8 (
    PID_PSF3, R_PCH_PCR_PSF3_T0_SHDW_TRACE_HUB_ACPI_REG_BASE + R_PCH_PCR_PSFX_T0_SHDW_PCIEN,
    0xFF,
    B_PCH_PCR_PSFX_T0_SHDW_PCIEN_MEMEN
    );
}

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchLpHeciPsfRegBase[] =
{
  R_PCH_LP_PCR_PSF1_T0_SHDW_HECI1_REG_BASE,
  R_PCH_LP_PCR_PSF1_T0_SHDW_HECI2_REG_BASE,
  R_PCH_LP_PCR_PSF1_T0_SHDW_HECI3_REG_BASE
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchHHeciPsfRegBase[] =
{
  R_PCH_H_PCR_PSF1_T0_SHDW_HECI1_REG_BASE,
  R_PCH_H_PCR_PSF1_T0_SHDW_HECI2_REG_BASE,
  R_PCH_H_PCR_PSF1_T0_SHDW_HECI3_REG_BASE
};

/**
  Enable HECI device at PSF level

  @param[in] HeciDevice       HECIx Device (HECI1-3)

  @retval None
**/
VOID
PsfEnableHeciDevice (
  IN UINT8      HeciDevice
  )
{
  UINT16     *DevPsfBase;

  if ((HeciDevice < 1) || (HeciDevice > 3)) {
    ASSERT (FALSE);
  }

  if (GetPchSeries () == PchLp) {
    DevPsfBase = mPchLpHeciPsfRegBase;
  } else {
    DevPsfBase = mPchHHeciPsfRegBase;
  }

  PchPcrAndThenOr32 (
    PID_PSF1, DevPsfBase[HeciDevice - 1] + R_PCH_PCR_PSFX_T0_SHDW_PCIEN,
    (UINT32) ~(B_PCH_PCR_PSFX_T0_SHDW_PCIEN_FUNDIS),
    0
    );
}

/**
  Disable HECI device at PSF level

  @param[in] HeciDevice       HECIx Device (HECI1-3)

  @retval None
**/
VOID
PsfDisableHeciDevice (
  IN UINT8      HeciDevice
  )
{
  UINT16     *DevPsfBase;

  if ((HeciDevice < 1) || (HeciDevice > 3)) {
    ASSERT (FALSE);
  }

  if (GetPchSeries () == PchLp) {
    DevPsfBase = mPchLpHeciPsfRegBase;
  } else {
    DevPsfBase = mPchHHeciPsfRegBase;
  }

  PchPcrAndThenOr32 (
    PID_PSF1, DevPsfBase[HeciDevice - 1] + R_PCH_PCR_PSFX_T0_SHDW_PCIEN,
    ~0u,
    B_PCH_PCR_PSFX_T0_SHDW_PCIEN_FUNDIS
    );
}

/**
  Enable IDER device at PSF level

  @retval None
**/
VOID
PsfEnableIderDevice (
  VOID
  )
{
  UINT16     DevPsfBase;

  if (GetPchSeries () == PchLp) {
    DevPsfBase = R_PCH_LP_PCR_PSF1_T0_SHDW_IDER_REG_BASE;
  } else {
    DevPsfBase = R_PCH_H_PCR_PSF1_T0_SHDW_IDER_REG_BASE;
  }

  PchPcrAndThenOr32 (
    PID_PSF1, DevPsfBase + R_PCH_PCR_PSFX_T0_SHDW_PCIEN,
    (UINT32) ~(B_PCH_PCR_PSFX_T0_SHDW_PCIEN_FUNDIS),
    0
    );
}

/**
  Disable IDER device at PSF level

  @retval None
**/
VOID
PsfDisableIderDevice (
  VOID
  )
{
  UINT16     DevPsfBase;

  if (GetPchSeries () == PchLp) {
    DevPsfBase = R_PCH_LP_PCR_PSF1_T0_SHDW_IDER_REG_BASE;
  } else {
    DevPsfBase = R_PCH_H_PCR_PSF1_T0_SHDW_IDER_REG_BASE;
  }

  PchPcrAndThenOr32 (
    PID_PSF1, DevPsfBase + R_PCH_PCR_PSFX_T0_SHDW_PCIEN,
    ~0u,
    B_PCH_PCR_PSFX_T0_SHDW_PCIEN_FUNDIS
    );
}

/**
  Enable SOL device at PSF level

  @retval None
**/
VOID
PsfEnableSolDevice (
  VOID
  )
{
  UINT16     DevPsfBase;

  if (GetPchSeries () == PchLp) {
    DevPsfBase = R_PCH_LP_PCR_PSF1_T0_SHDW_KT_REG_BASE;
  } else {
    DevPsfBase = R_PCH_H_PCR_PSF1_T0_SHDW_KT_REG_BASE;
  }

  PchPcrAndThenOr32 (
    PID_PSF1, DevPsfBase + R_PCH_PCR_PSFX_T0_SHDW_PCIEN,
    (UINT32) ~(B_PCH_PCR_PSFX_T0_SHDW_PCIEN_FUNDIS),
    0
    );
}

/**
  Disable SOL device at PSF level

  @retval None
**/
VOID
PsfDisableSolDevice (
  VOID
  )
{
  UINT16     DevPsfBase;

  if (GetPchSeries () == PchLp) {
    DevPsfBase = R_PCH_LP_PCR_PSF1_T0_SHDW_KT_REG_BASE;
  } else {
    DevPsfBase = R_PCH_H_PCR_PSF1_T0_SHDW_KT_REG_BASE;
  }

  PchPcrAndThenOr32 (
    PID_PSF1, DevPsfBase + R_PCH_PCR_PSFX_T0_SHDW_PCIEN,
    ~0u,
    B_PCH_PCR_PSFX_T0_SHDW_PCIEN_FUNDIS
    );
}
