/** @file
  Header file for Basic String functions.

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

#ifndef __STRING_H__
#define __STRING_H__

#ifdef MRC_MINIBIOS_BUILD
#include "MrcMiniBiosEfiDefs.h"
#endif //MRC_MINIBIOS_BUILD
#include <MrcTypes.h>

#ifdef _MSC_VER
// Disable warning for benign redefinition of type
#pragma warning(disable : 4142)
#endif

VOID
StrCpyLocal (
  INT8 *dest,
  INT8 *src
  );

UINT32
StrCmpLocal (
  INT8 *src1,
  INT8 *src2
  );

UINT32
StrLenLocal (
  INT8 *Str
  );

INT8
SsaLoaderTolower (
  INT8 c
  );

#endif // __STRING_H__
