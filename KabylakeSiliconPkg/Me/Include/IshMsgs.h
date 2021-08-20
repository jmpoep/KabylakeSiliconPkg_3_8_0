/** @file
  ISH Messages

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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
#ifndef _ISH_MSGS_H
#define _ISH_MSGS_H

#include <MkhiMsgs.h>

#pragma pack(1)

#define ISH_SET_FILE_CMD  0x1

#define PDT_UNLOCK_DATA_DATA_TYPE     0x1
#define PDT_UNLOCK_DATA_PAYLOAD_SIZE  0x0

typedef struct {
  UINT16  DataType;
  UINT16  PayloadSize;
} PDT_UNLOCK_DATA;

typedef struct {
  UINT16                 Command;
  UINT16                 MessageLength;
  UINT8                  FileName [12];
  UINT16                 NumberOfElements;
  PDT_UNLOCK_DATA        Data;
} PDT_UNLOCK;

#pragma pack()

#endif // _ISH_MSGS_H
