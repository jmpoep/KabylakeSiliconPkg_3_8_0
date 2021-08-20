/** @file
  Basic String functions.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2015 Intel Corporation.

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

#include "String.h"

void
StrCpyLocal (
  INT8 *dest,
  INT8 *src
  )
/*++

Routine Description:

  Copy string from source to destination

Arguments:

  dest  - Pointer to destination for string copy
  src   - Pointer to source of string to copy

Returns:

  VOID

--*/
{
  while (*src) *dest++ = *src++;
  *dest = 0;
}

UINT32
StrCmpLocal (
  INT8 *src1,
  INT8 *src2
  )
/*++

Routine Description:

  Compares two strings

Arguments:

  src1  - first string to compare
  src2  - second string to compare

Returns:

  0 - strings match
  1 - strings dont match

--*/
{
  UINT32 status = 0;

  while (*src1 && *src2 && (SsaLoaderTolower (*src1) == SsaLoaderTolower (*src2))) {
    src1++;
    src2++;
  }
  if (*src1 || *src1 != *src2) status = 1;
  return status;
}

UINT32
StrLenLocal (
  INT8 *Str
  )
/*++

Routine Description:

  Determines the length of the string

Arguments:

  Str - Pointer to string to measure

Returns:

  Length of string

--*/
{
  UINT32 i = 0;

  while (*(Str + i)) i++;
  return i;
}

INT8
SsaLoaderTolower (
  INT8 c
  )
/*++

Routine Description:

  Convert character to lower case

Arguments:

  c - character to convert

Returns:

  lower case character

--*/
{
  if (c >= 65 && c <= 90) c = c + 32;
  return c;
}