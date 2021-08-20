/** @file
  This file defines the PCH Info Protocol.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2008 - 2016 Intel Corporation.

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
#ifndef _PCH_INFO_H_
#define _PCH_INFO_H_

//
// Extern the GUID for protocol users.
//
extern EFI_GUID                       gPchInfoProtocolGuid;

//
// Forward reference for ANSI C compatibility
//
typedef struct _PCH_INFO_PROTOCOL PCH_INFO_PROTOCOL;

/**
  Protocol revision number
  Any backwards compatible changes to this protocol will result in an update in the revision number
  Major changes will require publication of a new protocol

  Revision 1:  Original version
  Revision 2:  Add PcieControllerCfg6 for KBL PCH-H
**/
#define PCH_INFO_PROTOCOL_REVISION    2

/**
 This protocol is used to provide the information of PCH controller.
**/
struct _PCH_INFO_PROTOCOL {
  /**
    This member specifies the revision of the PCH Info protocol. This field is used
    to indicate backwards compatible changes to the protocol. Platform code that
    consumes this protocol must read the correct revision value to correctly interpret
    the content of the protocol fields.
  **/
  UINT8        Revision;

  UINT8        PcieControllerCfg1;
  UINT8        PcieControllerCfg2;
  UINT8        PcieControllerCfg3;
  UINT8        PcieControllerCfg4;
  UINT8        PcieControllerCfg5;
  UINT8        PcieControllerCfg6;
};

#endif
