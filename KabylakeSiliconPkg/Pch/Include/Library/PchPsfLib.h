/** @file
  Header file for PchPsfLib.
  This is helper library of RC for PSF register programming.
  It's not expected to be used in platform code.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 Intel Corporation.

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
#ifndef _PCH_PSF_LIB_H_
#define _PCH_PSF_LIB_H_

#include <Library/PchSerialIoLib.h>

/**
  This procedure will enable SerialIO device BAR1 at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)

  @retval None
**/
VOID
PsfEnableSerialIoDeviceBar1 (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  );

/**
  This procedure will disable SerialIO device BAR1 at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)

  @retval None
**/
VOID
PsfDisableSerialIoDeviceBar1 (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  );

/**
  This procedure will disable SerailIO device at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)

  @retval None
**/
VOID
PsfDisableSerialIoDevice (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  );

/**
  This procedure will hide SerialIo device PciCfgSpace at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)

  @retval None
**/
VOID
PsfHideSerialIoDevice (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  );

/**
  This procedure will reveal SerialIo device PciCfgSpace at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)

  @retval None
**/
VOID
PsfRevealSerialIoDevice (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  );

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
  );

/**
  This procedure will enable MSE for TraceHub ACPI device at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfEnableTraceHubAcpiDeviceMemorySpace (
  VOID
  );

/**
  Enable HECI device at PSF level

  @param[in] HeciDevice       HECIx Device (HECI1-3)

  @retval None
**/
VOID
PsfEnableHeciDevice (
  IN UINT8      HeciDevice
  );

/**
  Disable HECI device at PSF level

  @param[in] HeciDevice       HECIx Device (HECI1-3)

  @retval None
**/
VOID
PsfDisableHeciDevice (
  IN UINT8      HeciDevice
  );

/**
  Enable IDER device at PSF level

  @retval None
**/
VOID
PsfEnableIderDevice (
  VOID
  );

/**
  Disable IDER device at PSF level

  @retval None
**/
VOID
PsfDisableIderDevice (
  VOID
  );

/**
  Enable SOL device at PSF level

  @retval None
**/
VOID
PsfEnableSolDevice (
  VOID
  );

/**
  Disable SOL device at PSF level

  @retval None
**/
VOID
PsfDisableSolDevice (
  VOID
  );
#endif // _PCH_PSF_LIB_H_
