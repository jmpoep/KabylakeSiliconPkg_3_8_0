/** @file
  P2sb policy

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
#ifndef _P2SB_CONFIG_H_
#define _P2SB_CONFIG_H_

#define P2SB_CONFIG_REVISION 2
extern EFI_GUID gP2sbConfigGuid;

#pragma pack (push,1)

/**
  This structure contains the policies which are related to P2SB device.
  <b>Revision 1:</b>
  - Init version
  <b>Revision 2:</b>
  - Deprecate PsfUnlock and Add SbAccessUnlock to not lock SideBand register access.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  /**
    <b>(Test)</b>
    This unlock the SBI lock bit to allow SBI after post time. <b>0: Disable</b>; 1: Enable.
    NOTE: Do not set this policy "SbiUnlock" unless necessary.
  **/
  UINT32    SbiUnlock         :  1;
  UINT32    PsfUnlock         :  1; //@deprecated
  /**
    <b>(Test)</b>
    The SideBand registers will be locked before 3rd party code execution.
    This policy unlock the SideBand space. <b>0: Disable</b>; 1: Enable.
    NOTE: Do not set this policy "SbAccessUnlock" unless necessary.
  **/
  UINT32    SbAccessUnlock    :  1;
  UINT32    RsvdBits          : 29;
} PCH_P2SB_CONFIG;

#pragma pack (pop)

#endif // _P2SB_CONFIG_H_
