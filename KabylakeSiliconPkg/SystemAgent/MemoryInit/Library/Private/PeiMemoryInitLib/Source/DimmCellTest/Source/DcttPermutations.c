/** @file
  Module to go through all the combinations of hardware row swizzling.

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
#include "DcttWrapper.h"
#include "DcttPermutations.h"

GLOBAL_REMOVE_IF_UNREFERENCED Permutations _permutations;

DCTTINLINE BOOLEAN _Permutation_addOne (Permutations* self)
{
  UINT8* carryPos = self->currentPermutation;
  UINT8 currPos = 0;
  while (currPos < self->numberPositions) {
    *carryPos = *carryPos + 1;
    if (*carryPos < self->numberElements) {
      return TRUE;
    } else {
      *carryPos = 0;
      carryPos++;
      currPos++;
    }
  }
  return FALSE;
}

DCTTINLINE BOOLEAN _Permutation_TestPermutation (Permutations* self)
{
  UINT8 i, element;

  for (i = 0; i < self->numberElements; i++) {
    self->elementPresent[i] = 0;
  }

  for (i = 0; i < self->numberPositions; i++) {
    element = self->currentPermutation[i];
    if (self->elementPresent[element] != 0) {
      return FALSE;
    } else {
      self->elementPresent[element] = 1;
    }
  }
  return TRUE;
}

BOOLEAN
Permutation_CalculateNextValue (
  Permutations  *self
  )
{
  BOOLEAN retCode;
  BOOLEAN testResult;

  do {
    retCode = _Permutation_addOne (self);
    if (retCode == FALSE) {
      return FALSE;
    }
    testResult = _Permutation_TestPermutation (self);
  } while (_Permutation_TestPermutation (self) == FALSE);

  return TRUE;
}
