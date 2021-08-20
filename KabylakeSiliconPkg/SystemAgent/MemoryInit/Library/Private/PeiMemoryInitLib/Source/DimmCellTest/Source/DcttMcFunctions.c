/** @file
  Memory Controller related functions.
  // TODO: Depracate

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2015 Intel Corporation.

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

#include "DcttApi.h"
#include "DcttApiFunctions.h"
#include "DcttRegList.h"
#include "DcttHelpers.h"

UINT16
McFunctions_GetTcBankField (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  UINT8                 FieldStart,
  UINT8                 FieldLength
  )
{
  UINT32  ReutRegAddress;
  UINT32  Value;

  ReutRegAddress = DcttGetMcAddressFunc (
                     DcttMain,
                     DCTT_CH_TC_PRE_REG,
                     0,
                     Channel,
                     DCTT_BYTE_CTL_NA
                     );

  Value = DcttReadReg32Func (DcttMain, ReutRegAddress);

  Value = (UINT32) Helpers_GetField (Value, FieldStart, FieldLength);

  return ((UINT16) Value);
}

UINT16
McFunctions_GetTcBankRankDField (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  UINT8                 FieldStart,
  UINT8                 FieldLength
  )
{
  UINT32  ReutRegAddress;
  UINT32  Value;

  ReutRegAddress = DcttGetMcAddressFunc (
                     DcttMain,
                     DCTT_CH_TC_ODT_REG,
                     0,
                     Channel,
                     DCTT_BYTE_CTL_NA
                     );

  Value = DcttReadReg32Func (DcttMain, ReutRegAddress);

  Value = (UINT32) Helpers_GetField (Value, FieldStart, FieldLength);

  return ((UINT16) Value);
}


VOID
McFunctions_UpdateTcBank (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  UINT8                 NewValue,
  UINT8                 UpdateStart,
  UINT8                 UpdateLength
  )
{
  UINT32  ReutRegAddress;
  UINT32  TcBank;

  ReutRegAddress = DcttGetMcAddressFunc (
                     DcttMain,
                     DCTT_CH_TC_PRE_REG,
                     0,
                     Channel,
                     DCTT_BYTE_CTL_NA
                     );

  TcBank = DcttReadReg32Func (DcttMain, ReutRegAddress);

  TcBank = (UINT32) Helpers_SetField (TcBank, NewValue, UpdateStart, UpdateLength);

  DcttWriteReg32Func (DcttMain, ReutRegAddress, TcBank);
}

VOID
McFunctions_UpdateTcBankRankD (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  UINT8                 NewValue,
  UINT8                 UpdateStart,
  UINT8                 UpdateLength
  )
{
  UINT32  ReutRegAddress;
  UINT32  TcBank;

  ReutRegAddress = DcttGetMcAddressFunc (
                     DcttMain,
                     DCTT_CH_TC_ODT_REG,
                     0,
                     Channel,
                     DCTT_BYTE_CTL_NA
                     );

  TcBank = DcttReadReg32Func (DcttMain, ReutRegAddress);

  TcBank = (UINT32) Helpers_SetField (TcBank, NewValue, UpdateStart, UpdateLength);

  DcttWriteReg32Func (DcttMain, ReutRegAddress, TcBank);
}
