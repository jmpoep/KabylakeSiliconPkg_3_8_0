#ifndef __MrcMcRegisterMacro_h__
#define __MrcMcRegisterMacro_h__
/** @file
  This file was automatically generated. Modify at your own risk.
  Note that no error checking is done in these functions so ensure that the correct values are passed.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

#pragma pack(push, 1)
#include "MrcTypes.h"
#include "MrcMcRegister.h"
#include "MrcHalRegisterAccess.h"
#include "MrcCommon.h"

typedef union {
  struct {
    UINT32 Offset   :  16; // Bits 15:0
    UINT32 BfOffset :   6; // Bits 21:16
    UINT32          :   2; // Bits 23:22
    UINT32 BfWidth  :   6; // Bits 29:24
    UINT32 RegSize  :   1; // Bits 30:30
    UINT32 BfSign   :   1; // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MRC_REGISTER_HASH_STRUCT;

#include "MrcMcRegisterMacro0xxx.h"
#include "MrcMcRegisterMacro1xxx.h"
#include "MrcMcRegisterMacro2xxx.h"
#include "MrcMcRegisterMacro3xxx.h"
#include "MrcMcRegisterMacro4xxx.h"
#include "MrcMcRegisterMacro5xxx.h"
#include "MrcMcRegisterMacro6xxx.h"
#include "MrcMcRegisterMacro7xxx.h"

#pragma pack(pop)
#endif
