/** @file
  Header file for GpioPrivateLib.
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
#ifndef _GPIO_PRIVATE_LIB_H_
#define _GPIO_PRIVATE_LIB_H_

#include <GpioConfig.h>

/**
  This procedure will get value of selected gpio register

  @param[in]  Group               GPIO group number
  @param[in]  Offset              GPIO register offset
  @param[out] RegVal              Value of gpio register

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid group or pad number
**/
EFI_STATUS
GpioGetReg (
  IN  GPIO_GROUP              Group,
  IN  UINT32                  Offset,
  OUT UINT32                  *RegVal
  );

/**
  This procedure will set value of selected gpio register

  @param[in] Group               GPIO group number
  @param[in] Offset              GPIO register offset
  @param[in] RegVal              Value of gpio register

  @retval EFI_SUCCESS            The function completed successfully
  @retval EFI_INVALID_PARAMETER  Invalid group or pad number
**/
EFI_STATUS
GpioSetReg (
  IN GPIO_GROUP              Group,
  IN UINT32                  Offset,
  IN UINT32                  RegVal
  );

/**
  This procedure is used by PchSmiDispatcher and will return information
  needed to register GPI SMI. Relation between Index and GpioPad number is:
  Index = GpioGroup + 24 * GpioPad

  @param[in]  Index               GPI SMI number
  @param[out] GpioPin             GPIO pin
  @param[out] GpiSmiBitOffset     GPI SMI bit position within GpiSmi Registers
  @param[out] GpiSmiEnRegAddress  Address of GPI SMI Enable register
  @param[out] GpiSmiStsRegAddress Address of GPI SMI status register

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid group or pad number
**/
EFI_STATUS
GpioGetPadAndSmiRegs (
  IN UINT32            Index,
  OUT GPIO_PAD         *GpioPin,
  OUT UINT8            *GpiSmiBitOffset,
  OUT UINT32           *GpiSmiEnRegAddress,
  OUT UINT32           *GpiSmiStsRegAddress
  );

/**
  This procedure will clear GPIO_UNLOCK_SMI_STS

  @param[in]  None

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid group or pad number
**/
EFI_STATUS
GpioClearUnlockSmiSts (
  VOID
  );

/**
  This procedure will set GPIO Driver IRQ number

  @param[in]  Irq                 Irq number

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid IRQ number
**/
EFI_STATUS
GpioSetIrq (
  IN  UINT8          Irq
  );

/**
  This procedure will perform special handling of GPP_A_12 on PCH-LP.

  @param[in]  None

  @retval None
**/
VOID
GpioA12SpecialHandling (
  VOID
  );

/**
  This function sets ISH I2C controller pins into native mode

  @param[in]  IshI2cControllerNumber   I2C controller

  @retval Status
**/
EFI_STATUS
GpioSetIshI2cPinsIntoNativeMode (
  IN  UINT32            IshI2cControllerNumber
  );

/**
  This function sets ISH UART controller pins into native mode

  @param[in]  IshUartControllerNumber   UART controller

  @retval Status
**/
EFI_STATUS
GpioSetIshUartPinsIntoNativeMode (
  IN  UINT32            IshUartControllerNumber
  );

/**
  This function sets ISH SPI controller pins into native mode

  @param[in]  none

  @retval Status
**/
EFI_STATUS
GpioSetIshSpiPinsIntoNativeMode (
  VOID
  );

/**
  This function sets ISH GP pins into native mode

  @param[in]  IshGpPinNumber   ISH GP pin number

  @retval Status
**/
EFI_STATUS
GpioSetIshGpPinsIntoNativeMode (
  IN  UINT32            IshGpPinNumber
  );

/**
  Returns pad for given CLKREQ# index.

  @param[in]  ClkreqIndex       CLKREQ# number

  @return CLKREQ# pad.
**/
GPIO_PAD
GpioGetClkreqPad (
  IN     UINT32   ClkreqIndex
  );

/**
  Enables CLKREQ# pad in native mode.

  @param[in]  ClkreqIndex       CLKREQ# number

  @return none
**/
VOID
GpioEnableClkreq (
  IN     UINT32   ClkreqIndex
  );

/**
  This function checks if GPIO pin for PCHHOTB is in NATIVE MODE

  @param[in]  none

  @retval TRUE                    Pin is in PCHHOTB native mode
          FALSE                   Pin is in gpio mode or is not owned by HOST
**/
BOOLEAN
GpioIsPchHotbPinInNativeMode (
  VOID
  );

/**
  This function sets CPU GP pins into native mode

  @param[in]  CpuGpPinNum               CPU GP pin number

  @retval Status
**/
EFI_STATUS
GpioSetCpuGpPinsIntoNativeMode (
  IN  UINT32                            CpuGpPinNum
  );

#endif // _GPIO_PRIVATE_LIB_H_
