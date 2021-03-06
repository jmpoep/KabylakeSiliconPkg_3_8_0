/** @file
  Header file for PCH Serial IO Lib implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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
#ifndef _PCH_SERIAL_IO_LIB_H_
#define _PCH_SERIAL_IO_LIB_H_

typedef enum {
  PchSerialIoIndexI2C0,
  PchSerialIoIndexI2C1,
  PchSerialIoIndexI2C2,
  PchSerialIoIndexI2C3,
  PchSerialIoIndexI2C4,
  PchSerialIoIndexI2C5,
  PchSerialIoIndexSpi0,
  PchSerialIoIndexSpi1,
  PchSerialIoIndexUart0,
  PchSerialIoIndexUart1,
  PchSerialIoIndexUart2,
  PchSerialIoIndexMax
} PCH_SERIAL_IO_CONTROLLER;

typedef enum {
  PchSerialIoDisabled,
  PchSerialIoAcpi,
  PchSerialIoPci,
  PchSerialIoAcpiHidden,
  PchSerialIoLegacyUart,
  PchSerialIoSkipInit
} PCH_SERIAL_IO_MODE;

enum PCH_LP_SERIAL_IO_VOLTAGE_SEL {
  PchSerialIoIs33V = 0,
  PchSerialIoIs18V
};
enum PCH_LP_SERIAL_IO_CS_POLARITY {
  PchSerialIoCsActiveLow = 0,
  PchSerialIoCsActiveHigh = 1
};
enum PCH_LP_SERIAL_IO_HW_FLOW_CTRL {
  PchSerialIoHwFlowCtrlDisabled = 0,
  PchSerialIoHwFlowControlEnabled = 1
};

#define SERIALIO_HID_LENGTH 8 // including null terminator
#define SERIALIO_UID_LENGTH 1
#define SERIALIO_CID_LENGTH 1
#define SERIALIO_TOTAL_ID_LENGTH SERIALIO_HID_LENGTH+SERIALIO_UID_LENGTH+SERIALIO_CID_LENGTH

/**
  Returns index of the last i2c controller

  @param[in] Number  Number of SerialIo controller

  @retval            Index of I2C controller
**/
PCH_SERIAL_IO_CONTROLLER
GetMaxI2cNumber (
  VOID
  );

/**
  Returns string with AcpiHID assigned to selected SerialIo controller

  @param[in] Number  Number of SerialIo controller

  @retval            pointer to 8-byte string
**/
CHAR8*
GetSerialIoAcpiHID (
  IN PCH_SERIAL_IO_CONTROLLER Number
  );

/**
  Checks if Device with given PciDeviceId is one of SerialIo controllers
  If yes, its number is returned through Number parameter, otherwise Number is not updated

  @param[in]  PciDevId  Device ID
  @param[out] Number    Number of SerialIo controller

  @retval TRUE          Yes it is a SerialIo controller
  @retval FALSE         No it isn't a SerialIo controller
**/
BOOLEAN
IsSerialIoPciDevId (
  IN  UINT16                    PciDevId,
  OUT PCH_SERIAL_IO_CONTROLLER  *Number
  );

/**
  Checks if Device with given AcpiHID string is one of SerialIo controllers
  If yes, its number is returned through Number parameter, otherwise Number is not updated

  @param[in]  AcpiHid   String
  @param[out] Number    Number of SerialIo controller

  @retval TRUE          yes it is a SerialIo controller
  @retval FALSE         no it isn't a SerialIo controller
**/
BOOLEAN
IsSerialIoAcpiHid (
  IN CHAR8                      *AcpiHid,
  OUT PCH_SERIAL_IO_CONTROLLER  *Number
  );

/**
  Configures Serial IO Controller

  @param[in] Controller
  @param[in] DeviceMode

  @retval None
**/
VOID
ConfigureSerialIoController (
  IN PCH_SERIAL_IO_CONTROLLER Controller,
  IN PCH_SERIAL_IO_MODE   DeviceMode
  );

/**
  Initializes GPIO pins used by SerialIo I2C devices

  @param[in] Controller
  @param[in] DeviceMode
  @param[in] I2cVoltage

  @retval None
**/
VOID
SerialIoI2cGpioInit (
  IN PCH_SERIAL_IO_CONTROLLER Controller,
  IN PCH_SERIAL_IO_MODE       DeviceMode,
  IN UINT32                   I2cVoltage
  );

/**
  Initializes GPIO pins used by SerialIo SPI devices

  @param[in] Controller
  @param[in] DeviceMode
  @param[in] SpiCsPolarity

  @retval None
**/
VOID
SerialIoSpiGpioInit (
  IN PCH_SERIAL_IO_CONTROLLER Controller,
  IN PCH_SERIAL_IO_MODE       DeviceMode,
  IN UINT32                   SpiCsPolarity
  );

/**
  Initializes GPIO pins used by SerialIo devices

  @param[in] Controller
  @param[in] DeviceMode
  @param[in] HardwareFlowControl

  @retval None
**/
VOID
SerialIoUartGpioInit (
  IN PCH_SERIAL_IO_CONTROLLER Controller,
  IN PCH_SERIAL_IO_MODE       DeviceMode,
  IN BOOLEAN                  HardwareFlowControl
  );

/**
  Finds PCI Device Number of SerialIo devices.
  SerialIo devices' BDF is configurable

  @param[in] SerialIoNumber             0=I2C0, ..., 11=UART2

  @retval                               SerialIo device number
**/
UINT8
GetSerialIoDeviceNumber (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoNumber
  );

/**
  Finds PCI Function Number of SerialIo devices.
  SerialIo devices' BDF is configurable

  @param[in] SerialIoNumber             0=I2C0, ..., 11=UART2

  @retval                               SerialIo funciton number
**/
UINT8
GetSerialIoFunctionNumber (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoNumber
  );

/**
  Finds BAR values of SerialIo devices.
  SerialIo devices can be configured to not appear on PCI so traditional method of reading BAR might not work.

  @param[in] SerialIoDevice             0=I2C0, ..., 11=UART2
  @param[in] BarNumber                  0=BAR0, 1=BAR1

  @retval                               SerialIo Bar value
**/
UINTN
FindSerialIoBar (
  IN PCH_SERIAL_IO_CONTROLLER           SerialIoDevice,
  IN UINT8                              BarNumber
  );


#endif // _PEI_DXE_SMM_PCH_SERIAL_IO_LIB_H_
