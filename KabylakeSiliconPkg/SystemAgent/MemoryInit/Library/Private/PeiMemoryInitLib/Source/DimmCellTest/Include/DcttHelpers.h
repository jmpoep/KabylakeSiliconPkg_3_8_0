/** @file
  Helper definitions.

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

#ifndef _DCTT_HELPERS_H_
#define _DCTT_HELPERS_H_

#ifndef MIN
  #define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif // MIN
#ifndef MAX
  #define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif // MAX

UINT8
Helpers_Log2 (
  UINT32  Value
  );

UINT8
Helpers_FloorLog2 (
  UINT32  Value
  );

UINT32
Helpers_GetField (
  UINT64  RegValue,
  UINT8   Start,
  UINT8   Length
  );

UINT64
Helpers_SetField (
  UINT64  RegValue,
  UINT32  FieldValue,
  UINT8   Start,
  UINT8   Length
  );
#endif // _DCTT_HELPERS_H_
