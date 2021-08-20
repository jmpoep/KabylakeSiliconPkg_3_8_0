/** @file
  Memory Controller function definitions.

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

#ifndef _DCTT_MC_FUNCTIONS_H_
#define _DCTT_MC_FUNCTIONS_H_

UINT16
McFunctions_GetTcBankField (
  DCTT_API              *MainHandle,
  UINT8                 Channel,
  UINT8                 FieldStart,
  UINT8                 FieldLength
  );

UINT16
McFunctions_GetTcBankRankDField (
  DCTT_API              *MainHandle,
  UINT8                 Channel,
  UINT8                 FieldStart,
  UINT8                 FieldLength
  );

VOID
McFunctions_UpdateTcBank (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  UINT8                 NewValue,
  UINT8                 UpdateStart,
  UINT8                 UpdateLength
  );

VOID
McFunctions_UpdateTcBankRankD (
  DCTT_API              *MainHandle,
  UINT8                 Channel,
  UINT8                 NewValue,
  UINT8                 UpdateStart,
  UINT8                 UpdateLength
  );

#endif // _DCTT_MC_FUNCTIONS_H_
