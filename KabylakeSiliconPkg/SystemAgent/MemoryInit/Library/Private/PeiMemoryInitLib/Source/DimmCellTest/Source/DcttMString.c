/** @file
  String support functions

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

#include "DcttMString.h"

unsigned
int
cstrlen (
  const char *str
  )
{
  char* endptr;

  endptr = (char *) str;
  while (*endptr != 0) {
    endptr = endptr + 1;
  }

  return (endptr - str);
}

int
(cstrncmp) (
  const char *s1,
  const char *s2,
  unsigned int n
  )
{
  unsigned int i;

  for (i = 0; i < n; i++) {
    if (s1[i]!= s2[i]) {
      return s1[i] - s2[i];
    } else if ((s1[i] == 0) || (s2[i] == 0)) {
      return 0;
    }
  }

  return 0;
}

char *
(cstrchr) (
  const char *p,
  int ch
  )
{
  char* charPointer;

  charPointer = (char *) p;
  while (*charPointer != 0) {
    if (*charPointer == ((char) ch)) {
      return charPointer;
    }

    charPointer++;
  }

  return 0;
}
