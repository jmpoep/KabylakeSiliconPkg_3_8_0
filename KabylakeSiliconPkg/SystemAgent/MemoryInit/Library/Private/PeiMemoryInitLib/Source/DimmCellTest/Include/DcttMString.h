/** @file
  String helper definitions.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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
#ifndef _DCTT_MSTRING_H_
#define _DCTT_MSTRING_H_
#include "DcttApi.h"
#include "DcttDebug.h"

typedef struct mString{
  char    *_string;
  char    *currStrPos;
  UINT16  len;
} mString;

unsigned int cstrlen (const char * str);
int cstrncmp (const char *s1, const char *s2, unsigned int n);
char* cstrchr (const char *s, int c);

#define _cStrLen(charString) cstrlen(charString)

#define _cStrChr(charString, charToFind) cstrchr(charString, charToFind)

#define _cStrnCmp(charString1,charString2, MaxCount) cstrncmp(charString1, charString2, MaxCount)
// This can fail if the call to character has side effects. Not a problem now because is internal.
#define _cIsDigit(character) ((character) >= '0' && (character) <= '9')


#define mString_GetSize(pmString) (pmString)->len

#define _mString_GetcString(pmString) (pmString)->currStrPos

DCTTINLINE VOID mString_Init(mString* self, char *charString)
{
  DcttError_UAssert(self != NULL);

  self->_string = charString;
  self->len = (UINT16) _cStrLen (charString);
  self->currStrPos = self->_string;
}

DCTTINLINE VOID mString_SubString(mString* self, UINT16 newStartPos)
{
  DcttError_UAssert(self != NULL);

  if (newStartPos >= self->len)
  {
    newStartPos = self->len;
  }

  self->len = self->len - newStartPos;
  self->currStrPos = self->currStrPos + newStartPos;
}

DCTTINLINE VOID mString_ShallowElementsCopy(mString* self, mString* mStringToCopy)
{
  DcttError_UAssert(self != NULL);
  DcttError_UAssert(mStringToCopy != NULL);

  self->currStrPos = mStringToCopy->currStrPos;
  self->len = mStringToCopy->len;
  self->_string = mStringToCopy->_string;
}

DCTTINLINE
VOID
mString_LTrim (
  mString *self
  )
{
  UINT16 i, numElements;

  DcttError_UAssert (self != NULL);

  numElements = mString_GetSize (self);

  for(i = 0; i < numElements; i++) {
    if(self->currStrPos[0] == ' ') {
      self->len = self->len - 1;
      self->currStrPos = self->currStrPos + 1;
    } else {
      break;
    }
  }
}

DCTTINLINE BOOLEAN mString_StartsWith(mString* self, mString* mStrToCompare)
{
  int cmpResult;

  DcttError_UAssert(self != NULL);
  DcttError_UAssert(mStrToCompare != NULL);

  if (mString_GetSize(self) < mString_GetSize(mStrToCompare))
  {
    return FALSE;
  }

  cmpResult = _cStrnCmp(_mString_GetcString(self),_mString_GetcString(mStrToCompare),
    mString_GetSize(mStrToCompare));
  if (cmpResult == 0)
  {
    return TRUE;
  }

  return FALSE;
}

DCTTINLINE BOOLEAN mString_PosIsDigit(mString* self, UINT16 pos)
{
  char* cstr;

  if (pos >= mString_GetSize(self))
  {
    return FALSE;
  }

  cstr = _mString_GetcString(self);

  if (_cIsDigit(cstr[pos]))
  {
    return TRUE;
  }

  return FALSE;
}

DCTTINLINE char mString_GetChar(mString* self, UINT16 charPos)
{
  char* cstr;

  if (charPos >= mString_GetSize(self))
  {
    return 0;
  }

  cstr = _mString_GetcString(self);

  return cstr[charPos];
}

/*DCTTINLINE UINT32 mString_ExtractU32(mString* self)
{
  UINT64 result = 0;
  UINT32 maxU32 = (UINT32)-1;
  //If the string do not start with a # the function
  //will return a 0. OK for now because is an internal function.
  ////TODO: Optimize this function.

  while (mString_PosIsDigit(self, 0))
  {
    char* cstr = _mString_GetcString(self);
    result *= 10;
    result += (cstr[0] - '0');
    mString_SubString(self, 1);
    if (result > maxU32)
    {
      //Overflow
      ////TODO: check if it would be better to continue extracting the number and then return the overflowed value
      return maxU32;
    }
  }
  return (UINT32)result;
}*/

DCTTINLINE UINT32 mString_ExtractU32(mString* self)
{
  UINT32 Result   = 0;
  UINT32 Previous;

  // If the string do not start with a # the function
  // will return a 0. OK for now because is an internal function.
  while (mString_PosIsDigit(self, 0)) {
    char* cstr = _mString_GetcString(self);
    Previous = Result;
    Result *= 10;
    Result += (cstr[0] - '0');
    if (Result < Previous) {
      return (UINT32) ~0; // If we overflow, return max.
    }
    mString_SubString(self, 1);
  }
  return Result;
}

// TODO: Remove?
DCTTINLINE char *mString_StrChr(mString* self, char charToFind)
{
  // This function do not work yet with mString_Truncate
  return _cStrChr(_mString_GetcString(self), charToFind);
}

DCTTINLINE
BOOLEAN
mString_FindChr (
  mString *self,
  char    charToFind,
  UINT16  *charPos
  )
{
  char  *CharPtr;
  UINT16 CharPosition;

  CharPtr = _cStrChr(_mString_GetcString(self), charToFind);

  if (CharPtr == NULL) {
    return FALSE;
  }
  // TODO: Check variable size, cast should be OK
  CharPosition = (UINT16)(CharPtr - _mString_GetcString(self));

  if (CharPosition >= mString_GetSize(self)) {
    return FALSE;
  }

  *charPos = CharPosition;

  return TRUE;
}

DCTTINLINE INT16 mString_Truncate(mString* self, UINT16 newLen)
{
  if (newLen > mString_GetSize(self))
  {
    return -1;
  }

  self->len = newLen;

  return DCTT_SUCCESS;
}
#endif // _DCTT_MSTRING_H_
