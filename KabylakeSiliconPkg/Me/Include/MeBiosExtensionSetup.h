/** @file
  Me Bios Extension Setup Options Guid definitions

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2005 - 2016 Intel Corporation.

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
#ifndef _ME_BIOS_EXTENSION_SETUP_H_
#define _ME_BIOS_EXTENSION_SETUP_H_

///
/// A NV-RAM variable for storing Intel MEBX setup option settings is created if this variable is not
/// present.  Those settings are used by BIOS during POST to bypass portions of the code if the
/// Intel ME features are not available
///

#define ME_BIOS_EXTENSION_SETUP_VARIABLE_NAME         (L"MeBiosExtensionSetup")

extern CHAR16   gMeBiosExtensionSetupName[];

extern EFI_GUID gMeBiosExtensionSetupGuid;

#pragma pack(1)

///
/// A NV-RAM variable for storing Intel MEBX setup option settings is created if this variable is not
/// present.  Those settings are used by BIOS during POST to bypass portions of the code if the
/// Intel ME features are not available. The information is obtained from Intel MEBx BIOS sync data
/// structure
///
typedef struct {
  ///
  /// Sync Data Structure Version, a non-zero version indicates the variable is being initialized or valid
  ///
  UINT16  InterfaceVersion;
  UINT16  Reserved;
  ///
  /// Bit 0 - UPDATED - this structure has been updated by MEBX
  ///
  UINT32  Flags;
  ///
  /// Platform Manageability Selection
  ///   00h - Off
  ///   01h - On
  ///
  UINT8   PlatformMngSel;
  UINT8   Reserved4;
  UINT8   AmtSol;
  UINT8   Reserved1[2];
  ///
  /// CIRA Feature
  ///   00h - DISABLED
  ///   01h - ENABLED
  ///
  UINT8   RemoteAssistanceTriggerAvailablilty;
  ///
  /// KVM state (0 - DISABLED, 1 - ENABLED)
  ///
  UINT8   KvmEnable;
  ///
  /// 0 - On every later boot after BIOS 1st boot
  /// 1 - Mebx will not require a reboot for synchronizing SOL state, used when BIOS 1st boot only.
  ///
  UINT8   MebxDefaultSol;
  UINT8   Reserved2[10];
} ME_BIOS_EXTENSION_SETUP;

#define MNT_OFF     0x00
#define MNT_ON      0x01
#define LAN_ENABLE  0x01
#define SOL_ENABLE  0x01
#define KVM_ENABLE  0x01

#pragma pack()

#endif
