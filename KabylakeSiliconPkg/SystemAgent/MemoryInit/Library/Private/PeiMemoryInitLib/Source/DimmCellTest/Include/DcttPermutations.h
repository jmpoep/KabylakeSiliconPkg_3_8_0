/** @file
  Permutation module definitions.

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

#ifndef _DCTT_PERMUTATIONS_H_
#define _DCTT_PERMUTATIONS_H_
#ifndef DISABLE_SWIZZLE
#include "DcttDebug.h"

#define PERM_MAX_NUM_ELEMENTS 16
#define PERM_MAX_NUM_POSITIONS 6

#define Permutations_VARDEF(varName) \
  Permutations* varName; \
  Permutations _internalVar_##varName

#define Permutations_VARINIT(varName, nElements, nPositions) \
  varName = &(_internalVar_##varName); \
  Permutations_Init(varName, nElements, nPositions)

////Next macro can be changed to a function to add more error checks
#define Permutations_GetElement(pPermutation, pos) (pPermutation)->currentPermutation[(pos)]

#define Permutations_GetNumberElement(pPermutation) (pPermutation)->numberElements

#define Permutations_GetNumberPositions(pPermutation) (pPermutation)->numberPositions

typedef struct Permutations{
  UINT8 numberElements;
  UINT8 elementPresent[PERM_MAX_NUM_ELEMENTS];
  UINT8 numberPositions;
  UINT8 currentPermutation[PERM_MAX_NUM_POSITIONS];
}Permutations;

DCTTINLINE VOID Permutations_Init(Permutations* self, UINT8 numberElements, UINT8 numberPositions)
{
  UINT8 i;

  DcttError_UAssert(numberElements <= PERM_MAX_NUM_ELEMENTS);
  DcttError_UAssert(numberPositions <= PERM_MAX_NUM_POSITIONS);

  self->numberElements = numberElements;
  self->numberPositions = numberPositions;
  ////for(i = 0; i < self->numberElements; i++)
  for(i = 0; i < self->numberPositions; i++)
  {
    ////self->currentPermutation[i] = i;
    self->currentPermutation[i] = 0;
  }
  ////Hackish init so I can directly call CalculatePermutation
  ////and it will return a correct first value
  ////self->currentPermutation[self->numberElements - 1] = self->numberElements - 2;
}

BOOLEAN
Permutation_CalculateNextValue (
  Permutations  *self
  );
#endif // DISABLE_SWIZZLE
#endif // _DCTT_PERMUTATIONS_H_
