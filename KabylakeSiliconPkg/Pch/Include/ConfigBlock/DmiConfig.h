/** @file
  DMI policy

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
#ifndef _DMI_CONFIG_H_
#define _DMI_CONFIG_H_

#define DMI_CONFIG_REVISION 2
extern EFI_GUID gDmiConfigGuid;


#pragma pack (push,1)


/**
  The PCH_DMI_CONFIG block describes the expected configuration of the PCH for DMI.

  <b>Revision 1</b>:
  - Initial version.
  <b>Revision 2</b>:
  - Add LegacyIoLowLatency support.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;         ///< Config Block Header
  /**
    0: Disable; <b>1: Enable</b> ASPM on PCH side of the DMI Link.
    While DmiAspm is enabled, DMI ASPM will be set to Intel recommended value.
  **/
  UINT32     DmiAspm            :  1;
  UINT32     PwrOptEnable       :  1;   ///< <b>0: Disable</b>; 1: Enable DMI Power Optimizer on PCH side.
  /**
    Set to enable low latenc of legacy IO.
    Some systems require lower IO latency irrespective of power.
    This is a tradeoff between power and IO latency.
    @note: Once this is enabled, DmiAspm is forced to disabled and so do Pcie DmiAspm in SystemAgent.
    <b>0:Disable</b>, 1:Enable
  **/
  UINT32     LegacyIoLowLatency :  1;
  UINT32     Rsvdbits           : 29;   ///< Reserved bits
} PCH_DMI_CONFIG;

#pragma pack (pop)

#endif // _DMI_CONFIG_H_
