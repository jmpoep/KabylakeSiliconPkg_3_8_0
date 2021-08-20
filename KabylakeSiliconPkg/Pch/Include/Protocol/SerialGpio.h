/** @file
  This file defines the PCH Serial GPIO Interface Protocol which implements the
  Intel(R) Serial Data over GPIO Pin functionality Protocol Interface.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2016 Intel Corporation.

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
#ifndef _PCH_SERIAL_GPIO_PROTOCOL_H_
#define _PCH_SERIAL_GPIO_PROTOCOL_H_

//
// Extern the GUID for protocol users.
//
extern EFI_GUID                           gPchSerialGpioProtocolGuid;
//
// Forward reference for ANSI C compatibility
//
typedef struct _PCH_SERIAL_GPIO_PROTOCOL  PCH_SERIAL_GPIO_PROTOCOL;

#define SERIAL_GPIO_MAX_DATA_RATE   63
#define WAIT_TIME                   100000
#define WAIT_PERIOD                 10

///
/// Serial GPIO protocol data structures and definitions
///
typedef enum {
  EnumSerialGpioDataByte,
  EnumSerialGpioDataWord,
  EnumSerialGpioDataUndefined,
  EnumSerialGpioDataDword,
  EnumSerialGpioDataMax
} SERIAL_GPIO_DATA_WIDTH;

//
// Protocol member functions
//
/**
  Register for one GPIO Pin that will be used as serial GPIO.
  For SKL PCH only GPP_D_0-4 will have the capability to be used as serial GPIO.
  The caller of this procedure need to be very clear of which GPIO should be used as serial GPIO,
  it should not be input, native, conflict with other GPIO, or Index > 4 on the caller's platform.

  @param[in] This                 Pointer to the PCH_SERIAL_GPIO_PROTOCOL instance.
  @param[in] SerialGpioPad        The GPIO pad number that will be used as serial GPIO for data sending.

  @retval EFI_SUCCESS             Opcode initialization on the SERIAL_GPIO host controller completed.
  @retval EFI_ACCESS_DENIED       The SERIAL_GPIO configuration interface is locked.
  @retval EFI_OUT_OF_RESOURCES    Not enough resource available to initialize the device.
  @retval EFI_DEVICE_ERROR        Device error, operation failed.
  @retval EFI_INVALID_PARAMETER   SerialGpioPinIndex is out of range
**/
typedef
EFI_STATUS
(EFIAPI *PCH_SERIAL_GPIO_REGISTER) (
  IN PCH_SERIAL_GPIO_PROTOCOL       * This,
  IN UINT8                          SerialGpioPad
  );

/**
  Unregister for one GPIO Pin that has been used as serial GPIO, and recover the registers before
  registering.

  @param[in] This                 Pointer to the PCH_SERIAL_GPIO_PROTOCOL instance.
  @param[in] SerialGpioPad        The GPIO pad number that will be used as serial GPIO for data sending.

  @retval EFI_SUCCESS             Opcode initialization on the SERIAL_GPIO host controller completed.
  @retval EFI_ACCESS_DENIED       The SERIAL_GPIO configuration interface is locked.
  @retval EFI_OUT_OF_RESOURCES    Not enough resource available to initialize the device.
  @retval EFI_DEVICE_ERROR        Device error, operation failed.
  @retval EFI_INVALID_PARAMETER   Invalid function parameters
**/
typedef
EFI_STATUS
(EFIAPI *PCH_SERIAL_GPIO_UNREGISTER) (
  IN PCH_SERIAL_GPIO_PROTOCOL       * This,
  IN UINT8                          SerialGpioPad
  );

/**
  Execute SERIAL_GPIO commands from the host controller.

  @param[in] This                 Pointer to the PCH_SERIAL_GPIO_PROTOCOL instance.
  @param[in] GpioPad         GPIO pad number.
  @param[in] DataRate             The data rate for serial data transferring. 1 ~ SERIAL_GPIO_MAX_DATA_RATE; 1: 128ns intervals; ...; 8: 8*128 = 1024ns intervals, default value;...
  @param[in] DataCountInByte      Number of bytes of the data will be transmitted through the GPIO pin.
  @param[in, out] Buffer          Pointer to caller-allocated buffer containing the data sent through the GPIO pin.

  @retval EFI_SUCCESS             Execute succeed.
  @retval EFI_INVALID_PARAMETER   The parameters specified are not valid.
  @retval EFI_DEVICE_ERROR        Device error, GPIO serial data sent failed.
**/
typedef
EFI_STATUS
(EFIAPI *PCH_SERIAL_GPIO_SEND_DATA) (
  IN     PCH_SERIAL_GPIO_PROTOCOL   * This,
  IN     UINT8                      GpioPad,
  IN     UINT8                      DataRate,
  IN     UINTN                      DataCountInByte,
  IN OUT UINT8                      *Buffer
  );
/**
  This Protocol allows a platform module to execute the IntelR Serial Data over
  GPIO Pin functionality Protocol Interface.
  The caller will first call the SerialGpioRegister() function to configure the GPIO
  to be used. Then the caller will execute one or more calls to the SerialGpioSendData()
  function to perform serial GPIO activities. Finally, the caller will use the
  SerialGpioUnRegister() function to un-register and allow other consumers to utilize
  the serial GPIO services.
  If the serial GPIO capabilities are in use by another caller, the registration
  function will return an error.
**/
struct _PCH_SERIAL_GPIO_PROTOCOL {
  PCH_SERIAL_GPIO_REGISTER    SerialGpioRegister;   ///< Register for one GPIO pin that will be used as serial GPIO.
  PCH_SERIAL_GPIO_SEND_DATA   SerialGpioSendData;   ///< Execute SERIAL_GPIO commands from the host controller.
  PCH_SERIAL_GPIO_UNREGISTER  SerialGpioUnRegister; ///< Un-register the current GPIO pin used for serial GPIO, and recovers the registers before registering.
};

#endif
