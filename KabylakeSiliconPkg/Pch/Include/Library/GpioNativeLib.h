/** @file
  Header file for GpioLib for native and Si specific usage.
  All function in this library is available for PEI, DXE, and SMM,

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

@par Specification Reference:
**/
#ifndef _GPIO_NATIVE_LIB_H_
#define _GPIO_NATIVE_LIB_H_

#include <GpioConfig.h>

/**
  This procedure will get number of pads for certain GPIO group

  @param[in] Group            GPIO group number

  @retval Value               Pad number for group
                              If illegal group number then return 0
**/
UINT32
GpioGetPadPerGroup (
  IN GPIO_GROUP        Group
  );

/**
  This procedure will get number of groups

  @param[in] none

  @retval Value               Group number
**/
UINT8
GpioGetNumberOfGroups (
  VOID
  );
/**
  This procedure will get lowest group

  @param[in] none

  @retval Value               Lowest Group
**/
GPIO_GROUP
GpioGetLowestGroup (
  VOID
  );

/**
  This procedure will get highest group

  @param[in] none

  @retval Value               Highest Group
**/
GPIO_GROUP
GpioGetHighestGroup (
  VOID
  );

/**
  This procedure will get group

  @param[in] GpioPad          Gpio Pad

  @retval Value               Group
**/
GPIO_GROUP
GpioGetGroupFromGpioPad (
  IN GPIO_PAD        GpioPad
  );

/**
  This procedure will get group index (0 based) from GpioPad

  @param[in] GpioPad          Gpio Pad

  @retval Value               Group Index
**/
UINT32
GpioGetGroupIndexFromGpioPad (
  IN GPIO_PAD        GpioPad
  );

/**
  This procedure will get group index (0 based) from group

  @param[in] GpioGroup        Gpio Group

  @retval Value               Group Index
**/
UINT32
GpioGetGroupIndexFromGroup (
  IN GPIO_GROUP        GpioGroup
  );

/**
  This procedure will get pad number (0 based) from Gpio Pad

  @param[in] GpioPad          Gpio Pad

  @retval Value               Pad Number
**/
UINT32
GpioGetPadNumberFromGpioPad (
  IN GPIO_PAD        GpioPad
  );

/**
  This procedure will return GpioPad from Group and PadNumber

  @param[in] Group              GPIO group
  @param[in] PadNumber          GPIO PadNumber

  @retval GpioPad               GpioPad
**/
GPIO_PAD
GpioGetGpioPadFromGroupAndPadNumber (
  IN GPIO_GROUP      Group,
  IN UINT32          PadNumber
  );

/**
  This procedure will return GpioPad from GroupIndex and PadNumber

  @param[in] GroupIndex         GPIO GroupIndex
  @param[in] PadNumber          GPIO PadNumber

  @retval GpioPad               GpioPad
**/
GPIO_PAD
GpioGetGpioPadFromGroupIndexAndPadNumber (
  IN UINT32          GroupIndex,
  IN UINT32          PadNumber
  );

/**
  This function sets SerialIo I2C controller pins into native mode

  @param[in]  SerialIoI2cControllerNumber   I2C controller

  @retval Status
**/
EFI_STATUS
GpioSetSerialIoI2cPinsIntoNativeMode (
  IN  UINT32            SerialIoI2cControllerNumber
  );

/**
  This function sets SerialIo I2C controller pins tolerance

  @param[in]  SerialIoI2CControllerNumber   I2C controller
  @param[in]  Pad1v8Tolerance               TRUE:  Enable  1v8 Pad tolerance
                                            FALSE: Disable 1v8 Pad tolerance

  @retval Status
**/
EFI_STATUS
GpioSetSerialIoI2CPinsTolerance (
  IN  UINT32            SerialIoI2CControllerNumber,
  IN  BOOLEAN           Pad1v8Tolerance
  );

/**
  This function sets SerialIo UART controller pins into native mode

  @param[in]  SerialIoI2CControllerNumber   UART controller
  @param[in]  HardwareFlowControl           Hardware Flow control

  @retval Status
**/
EFI_STATUS
GpioSetSerialIoUartPinsIntoNativeMode (
  IN  UINT32            SerialIoUartControllerNumber,
  IN  BOOLEAN           HardwareFlowControl
  );

/**
  This function sets SerialIo SPI controller pins into native mode

  @param[in]  SerialIoI2CControllerNumber   SPI controller

  @retval Status
**/
EFI_STATUS
GpioSetSerialIoSpiPinsIntoNativeMode (
  IN  UINT32            SerialIoUartControllerNumber
  );

/**
  This function checks if GPIO pin for SATA reset port is in GPIO MODE

  @param[in]  SataPort            SATA port number

  @retval TRUE                    Pin is in GPIO mode
          FALSE                   Pin is in native mode
**/
BOOLEAN
GpioIsSataResetPortInGpioMode (
  IN  UINTN            SataPort
  );

/**
  This function checks if SataDevSlp pin is in native mode

  @param[in]  SataPort            SATA port
  @param[out] DevSlpPad           DevSlpPad

  @retval TRUE                    DevSlp is in native mode
          FALSE                   DevSlp is not in native mode
**/
BOOLEAN
GpioIsSataDevSlpPinEnabled (
  IN  UINTN           SataPort,
  OUT GPIO_PAD        *DevSlpPad
  );

#endif // _GPIO_NATIVE_LIB_H_
