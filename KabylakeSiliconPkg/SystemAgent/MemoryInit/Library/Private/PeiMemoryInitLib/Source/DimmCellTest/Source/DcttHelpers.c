/** @file
  Various helper functions.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2014 Intel Corporation.

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

#include "DcttWrapper.h"
#include "DcttDebug.h"

UINT8
Helpers_Log2 (
  UINT32  Value
  )
{
  UINT8 log = 0;
  UINT8 bit;
  UINT8 Bits = 32;
  //
  // Return 0 if value is negative
  //
  if ((Value + 1) == 0) {
    return log;
  }

  for (bit = 0; bit < Bits; bit++) {
    if (Value & (1 << bit)) {
      log = (bit + 1);
    }
  }

  return log;
}

UINT8
Helpers_FloorLog2 (
  UINT32  Value
  )
{
  UINT8 log = 0;
  UINT8 bit;
  UINT8 Bits = 32;
  //
  // Return 0 if value is negative
  //
  if ((Value + 1) == 0) {
    return log;
  }

  for (bit = 0; bit < Bits; bit++) {
    if (Value & (1 << bit)) {
      log = (bit);
    }
  }

  return log;
}

UINT32
Helpers_GetField (
  UINT64  RegValue,
  UINT8   Start,
  UINT8   Length
  )
{
  UINT32  RetVal;
  UINT32  LowerMask;
  UINT32  UpperMask;
  UINT32  LowerRetValue;
  UINT32  UpperRetValue;
  UINT32  *CurrentIndex;
  UINT8   LowerMaskLen;
  UINT8   UpperMaskLen;

  CurrentIndex = (UINT32 *) &RegValue;
  if (((Start + Length) > 32) && (Start < 32)) {
    //
    // Across the DWord boundary.
    //
    UpperMaskLen    = Start + Length - 32;
    LowerMaskLen    = 32 - Start;
    LowerMask       = (1 << LowerMaskLen) - 1;
    UpperMask       = (1 << UpperMaskLen) - 1;
    LowerRetValue   = (CurrentIndex[0] >> Start);
    LowerRetValue  &= LowerMask;
    UpperRetValue   = CurrentIndex[1] & UpperMask;
    UpperRetValue <<= LowerMaskLen;
    RetVal          = LowerRetValue | UpperRetValue;
  } else if (Start >= 32) {
    //
    // Everything is on the upper 32 bits.
    //
    UpperMask = (1 << Length) - 1;
    RetVal    = (CurrentIndex[1] >> (Start - 32));
    RetVal   &= UpperMask;
  } else if (Start < 32) {
    //
    //Everything is on the lower 32 bits.
    //
    LowerMask = (1 << Length) - 1;
    RetVal    = (CurrentIndex[0] >> Start);
    RetVal   &= LowerMask;
  } else {
    //
    // Improper call of the function.
    //
    RetVal = (UINT32) ~0;
    DcttError_UAssert (1 == 0);
  }

  return RetVal;
}

UINT64
Helpers_SetField (
  UINT64  RegValue,
  UINT32  FieldValue,
  UINT8   Start,
  UINT8   Length
  )
{
  UINT64  RetVal;
  UINT32  LowerMask;
  UINT32  UpperMask;
  UINT32  LowerNewValue;
  UINT32  UpperNewValue;
  UINT32  *RetValIndex;
  UINT8   LowerMaskLen;
  UINT8   UpperMaskLen;

  RetVal      = RegValue;
  RetValIndex = (UINT32 *) &RetVal;
  if (((Start + Length) > 32) && (Start < 32)) {
    //
    // Across the DWord boundary.
    //
    UpperMaskLen    = Start + Length - 32;
    LowerMaskLen    = 32 - Start;
    LowerMask       = (1 << LowerMaskLen) - 1;
    UpperMask       = (1 << UpperMaskLen) - 1;
    LowerNewValue   = FieldValue & LowerMask;
    UpperNewValue   = (FieldValue >> LowerMaskLen);
    UpperNewValue  &= UpperMask;
    RetValIndex[0] &= ~(LowerMask << Start);
    RetValIndex[1] &= ~UpperMask;
    RetValIndex[0] |= (LowerNewValue << Start);
    RetValIndex[1] |= UpperNewValue;

  } else if (Start >= 32) {
    //
    // Everything is on the upper 32 bits.
    //
    UpperMask       = (1 << Length) - 1;
    RetValIndex[1] &= ~(UpperMask << (Start - 32));
    RetValIndex[1] |= ((FieldValue & UpperMask) << (Start - 32));
  } else if (Start < 32) {
    //
    //Everything is on the lower 32 bits.
    //
    LowerMask       = (1 << Length) - 1;
    RetValIndex[0] &= ~(LowerMask << Start);
    RetValIndex[0] |= ((FieldValue & LowerMask) << Start);
  } else {
    //
    // Improper call of the function.
    //
    RetVal = (UINT64) ~0;
    DcttError_UAssert (1 == 0);
  }

  return RetVal;
}
