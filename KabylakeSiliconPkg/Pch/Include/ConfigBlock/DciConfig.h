/** @file
  Dci policy

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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
#ifndef _DCI_CONFIG_H_
#define _DCI_CONFIG_H_

#define DCI_PREMEM_CONFIG_REVISION 2
extern EFI_GUID gDciPreMemConfigGuid;

#pragma pack (push,1)

/**
  This structure contains the policies which are related to Direct Connection Interface (DCI).

  <b>Revision 1:</b>
  - Inital version.
  <b>Revision 2:</b>
  - Deprecate DciAutoDetect
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;         ///< Config Block Header
  /**
    DCI enable (HDCIEN bit)
    when Enabled, allow DCI to be enabled. When Disabled, the host control is not enabling DCI feature.
    BIOS provides policy to enable or disable DCI, and user would be able to use BIOS option to change this policy.
    The user changing the setting from disable to enable, is taken as a consent from the user to enable this DCI feature.
    <b>0:Disabled</b>; 1:Enabled
  **/
  UINT32    DciEn           :  1;
  /**
    @deprecated from revision 2.
    <b>(Test)</b> When set to Auto detect mode, it detects CCA being connected during BIOS post time.
    This policy only applies when DciEn is disabled.
    NOTE: this policy should not be visible to end customer.
    0: Disable AUTO mode, <b>1: Enable AUTO mode</b>
  **/
  UINT32    DciAutoDetect   :  1;
  UINT32    RsvdBits        : 30;       ///< Reserved bits
} PCH_DCI_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _DCI_CONFIG_H_
