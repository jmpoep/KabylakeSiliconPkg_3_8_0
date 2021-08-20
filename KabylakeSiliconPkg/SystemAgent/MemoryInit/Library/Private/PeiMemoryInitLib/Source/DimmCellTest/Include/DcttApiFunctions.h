/** @file
  This file defines macros for calling DCTT_CALLBACK_FUNCTIONS used within
  the DCTT source.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

#ifndef _DCTT_API_FUNCTIONS_H_
#define _DCTT_API_FUNCTIONS_H_

/**
Function used to get an Address object to read/write a register.

  @param[in] MainHandle - Used to get the CallBack function pointer.
  @param[in] Offset     - Register bar Offset.
  @param[in] Controller - Memory Controller index.
  @param[in] Channel    - Channel the register operates on. This is used for loop iteration.
                          If not used, leave as 0
  @param[in] ExtraIndex   - Separate register index using for looping when multiple registers exist on one Channel.
                          If not used, leave as 0

  @retval UINT32 - The requested register address.
**/
#define DcttGetMcAddressFunc(MainHandle, Offset, Controller, Channel, ExtraIndex) (MainHandle)->DcttCbFunctions.DcttSysGetMcAddress ((MainHandle), (Offset), (Controller), (Channel), (ExtraIndex))

/*
Function used to write a 32 bit register.

Parameters:
- DCTT_API* MainHandle: handled provided by the BIOS SSA framework to the application's entry point.
- UINT32 Address: Address object returned by DcttGetMcAddressFunc.
- UINT32 Value: Value to write to the register

Function doesn't return anything.
*/
#define DcttWriteReg32Func(MainHandle, Address, Value) (MainHandle)->DcttCbFunctions.DcttWriteReg32 ((MainHandle), (Address), (Value))

/*
Function used to read a 32 bit register.

Parameters:
- DCTT_API* MainHandle: handled provided by the BIOS SSA framework to the application's entry point.
- UINT32 Address: Address object returned by DcttGetMcAddressFunc.

Function returns the read Value.
*/
#define DcttReadReg32Func(MainHandle, Address) (MainHandle)->DcttCbFunctions.DcttReadReg32 ((MainHandle), (Address))

/*
Function used to write a 64 bit register.

Parameters:
- DCTT_API* MainHandle: handled provided by the BIOS SSA framework to the application's entry point.
- UINT32 Address: Address object returned by DcttGetMcAddressFunc.
- UINT64 Value: Value to write to the register

Function doesn't return anything.
*/
#define DcttWriteReg64Func(MainHandle, Address, Value) (MainHandle)->DcttCbFunctions.DcttWriteReg64 ((MainHandle), (Address), (Value))

/*
Function used to read a 64 bit register.

Parameters:
- DCTT_API* MainHandle: handled provided by the BIOS SSA framework to the application's entry point.
- UINT32 Address: Address object returned by DcttGetMcAddressFunc.

Function returns the read Value.
*/
#define DcttReadReg64Func(MainHandle, Address) (MainHandle)->DcttCbFunctions.DcttReadReg64 ((MainHandle), (Address))

#define DcttSysGetPresentChannelBitMaskFunc(MainHandle, Controller) (MainHandle)->DcttCbFunctions.DcttSysGetPresentChannelBitMask ((MainHandle), (Controller))

#define DcttSysChannelExistsFunc(MainHandle, Controller, Channel) (MainHandle)->DcttCbFunctions.DcttSysChannelExists ((MainHandle), (Controller), (Channel))

#define DcttSysRankInChannelExistsFunc(MainHandle, Controller, Channel, Rank) (MainHandle)->DcttCbFunctions.DcttSysRankInChannelExists ((MainHandle), (Controller), (Channel), (Rank))

/**
Function used to get an Address object to read/write a register.

  @param[in] MainHandle  - Used to get the CallBack function pointer.
  @param[in] WaitSysUnit - Number of DCTT_SYS_MIN_DELAY_FS to wait. (DcttWrapper.h)

  @retval void - Nothing
**/
#define DcttWaitFunc(MainHandle, WaitSysUnits) (MainHandle)->DcttCbFunctions.DcttSysWait ((MainHandle), (WaitSysUnits))

#define DcttEnterSelfRefreshFunc(MainHandle) (MainHandle)->DcttCbFunctions.DcttSysEnterSelfRefresh ((MainHandle))

#define DcttExitSelfRefreshFunc(MainHandle) (MainHandle)->DcttCbFunctions.DcttSysExitSelfRefresh ((MainHandle))

#define DcttGetRowSizeFunc(MainHandle, Controller, Channel, Dimm) (MainHandle)->DcttCbFunctions.DcttDimmGetRowSize ((MainHandle), (Controller), (Channel), (Dimm))

#define DcttGetColumnSizeFunc(MainHandle, Controller, Channel, Dimm) (MainHandle)->DcttCbFunctions.DcttDimmGetColumnSize ((MainHandle), (Controller), (Channel), (Dimm))

#define DcttGetNumberOfRanksFunc(MainHandle, Controller, Channel, Dimm) (MainHandle)->DcttCbFunctions.DcttDimmGetNumberOfRanks ((MainHandle), (Controller), (Channel), (Dimm))

#define DcttGetDimmSizeFunc(MainHandle, Controller, Channel, Dimm) (MainHandle)->DcttCbFunctions.DcttDimmGetSize ((MainHandle), (Controller), (Channel), (Dimm))

#define DcttSysWriteWdbFixedPatFunc(MainHandle, Controller, Patterns, Mask, Spread, Start) (MainHandle)->DcttCbFunctions.DcttSysSetWdbFixedPat ((MainHandle), (Controller), (Patterns), (Mask), (Spread), (Start))

#define DcttGetMcFrequencyFunc(MainHandle, Controller) (MainHandle)->DcttCbFunctions.DcttSysGetMcFrequency ((MainHandle), (Controller))

#define DcttSetClFunc(MainHandle, Controller, Channel, Value) (MainHandle)->DcttCbFunctions.DcttSetCl ((MainHandle), (Controller), (Channel), (Value))

#define DcttSetCwlFunc(MainHandle, Controller, Channel, Value) (MainHandle)->DcttCbFunctions.DcttSetCwl ((MainHandle), (Controller), (Channel), (Value))

#define DcttSetRefiFunc(MainHandle, Controller, Channel, Value) (MainHandle)->DcttCbFunctions.DcttSysSetRefi ((MainHandle), (Controller), (Channel), (Value))

#define DcttGetRefiFunc(MainHandle, Controller, Channel) (MainHandle)->DcttCbFunctions.DcttSysGetRefi ((MainHandle), (Controller), (Channel))

#define DcttPrintFunc(MainHandle, FormatString, ...) (MainHandle)->DcttCbFunctions.DcttSysPrint ((MainHandle), (FormatString), ## __VA_ARGS__)

#define DcttLeft64Shift(MainHandle, Data, NumBits) (MainHandle)->DcttCbFunctions.DcttLeftShift64 ((MainHandle), (Data), (NumBits))

#define DcttRight64Shift(MainHandle, Data, NumBits) (MainHandle)->DcttCbFunctions.DcttRightShift64 ((MainHandle), (Data), (NumBits))

#define DcttResetFunc(MainHandle) (MainHandle)->DcttCbFunctions.DcttSysReset ((MainHandle))

#define DcttGetSelfRefreshConfigFunc(MainHandle, SrefEnPtr, IdleTimePtr) (MainHandle)->DcttCbFunctions.DcttSysGetSetSelfRefreshConfig ((MainHandle), (SrefEnPtr), (IdleTimePtr), FALSE)

#define DcttSetSelfRefreshConfigFunc(MainHandle, SrefEnPtr, IdleTimePtr) (MainHandle)->DcttCbFunctions.DcttSysGetSetSelfRefreshConfig ((MainHandle), (SrefEnPtr), (IdleTimePtr), TRUE)
#endif // _DCTT_API_FUNCTIONS_H_
