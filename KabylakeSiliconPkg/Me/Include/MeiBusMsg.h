/** @file
  Definitions for MEI Bus message support

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
#ifndef _MEI_BUS_MSG_H_
#define _MEI_BUS_MSG_H_

///
/// ME Address of Fixed Address MEI Header -
/// This is the logical address of the Intel(R) ME client
/// of the message. This address is assigned during ME firmware initialization.
///
#define HECI_MEI_BUS_MESSAGE_ADDR     0x00

#define HECI_BUS_DISABLE_OPCODE       0x0C
#define HECI_BUS_DISABLE_ACK_OPCODE   0x8C

///
/// Disable Heci Bus message
///
typedef union _HBM_COMMAND {
  UINT8 Data;
  struct {
    UINT8 Command    : 7;
    UINT8 IsResponse : 1;
  } Fields;
} HBM_COMMAND;

typedef struct _HECI_BUS_DISABLE_CMD {
  HBM_COMMAND Command;
  UINT8       Reserved[3];
} HECI_BUS_DISABLE_CMD;

typedef struct _HECI_BUS_DISABLE_CMD_ACK {
  HBM_COMMAND Command;
  UINT8       Status;
  UINT8       Reserved[2];
} HECI_BUS_DISABLE_CMD_ACK;

#endif // _MEI_BUS_MSG_H_

