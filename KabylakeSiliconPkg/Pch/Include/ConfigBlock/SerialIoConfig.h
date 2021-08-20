/** @file
  Serial IO policy

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#ifndef _SERIAL_IO_CONFIG_H_
#define _SERIAL_IO_CONFIG_H_

#define SERIAL_IO_CONFIG_REVISION 1
extern EFI_GUID gSerialIoConfigGuid;

#pragma pack (push,1)

/**
  The PCH_SERIAL_IO_CONFIG block provides the configurations to set the Serial IO controllers
  to Acpi devices or Pci controllers, and also set the interrupt type to Acpi or Pci
  through Policy. It also provides to configure the I2c0 and I2c1 voltage
  to 1.8v or 3.3v by platform setting.
  Please refer to PeiDxeSmmPchSerialIoLib.h for definition of device numbers and enum values for the below fields
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                             ///< Config Block Header
  /**
    0: Disabled; 1: ACPI Mode; <b>2: PCI Mode</b>; 3: Hidden mode, 4: Legacy UART mode, 5: Skip Init
    @note: Considering the PcdSerialIoUartDebugEnable and PcdSerialIoUartNumber for all SerialIo UARTx,
           the PCD is more meaningful to represent the board design. It means, if PcdSerialIoUartDebugEnable is not 0,
           the board is designed to use the SerialIo UART for debug message and the PcdSerialIoUartNumber is dedicated
           to be Debug UART usage. Therefore, it should grayout the option from setup menu since no other options
           available for this UART controller on this board, and also override the policy default accordingly.
           While PcdSerialIoUartDebugEnable is 0, then it's allowed to configure the UART controller by policy.
    @note: While DevMode is set to 5 (Skip Init), BIOS will not initialize this controller. GPIO and PSF configuration is skipped.
           Platform is resonsible for configuring this controller. If platform initializes the Serial IO controller in
           Hidden Mode, it MUST follow the predefined BAR address for the controller.
  **/
  UINT8  DevMode[PCH_SERIALIO_MAX_CONTROLLERS];
  UINT8  Gpio;                                              ///< 0: Disabled; <b>1: Enabled</b>.
  /**
    Selects the IO voltage for I2C controllers. It can be 1.8v or 3.3v. <b>0: PchSerialIoIs33V</b>; 1: PchSerialIoIs18V.
    @note: I2C 2/3/4/5 (GPP_F) does not support  3.3V on PCH-LP
  **/
  UINT8  I2cVoltage[PCH_SERIALIO_MAX_I2C_CONTROLLERS];
  UINT8  SpiCsPolarity[PCH_SERIALIO_MAX_SPI_CONTROLLERS];   ///< Selects SPI ChipSelect signal polarity, <b>0=active low</b>.
  UINT8  UartHwFlowCtrl[PCH_SERIALIO_MAX_UART_CONTROLLERS]; ///< Enables UART hardware flow control, CTS and RTS lines, <b>0:disabled</b>, 1:enabled
  UINT8  Rsvd0[1];                                          ///< Bytes reserved for reuse when new fields are added to struct
  UINT32 DebugUartNumber           :  2;                    ///< UART number for debug purpose. 0:UART0, 1: UART1, <b>2:UART2</b>
  UINT32 EnableDebugUartAfterPost  :  1;                    ///< Enable debug UART controller after post. 0: diabled, <b>1: enabled</b>
  UINT32 RsvdBits0                 : 29;
} PCH_SERIAL_IO_CONFIG;

#pragma pack (pop)

#endif // _SERIAL_IO_CONFIG_H_
