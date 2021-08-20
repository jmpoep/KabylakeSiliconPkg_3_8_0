/** @file
  Active Management Technology Protocol to return the state of ASF Boot Options
  related to Active Management Technology.

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
#ifndef _ACTIVE_MANAGEMENT_PROTOCOL_H_
#define _ACTIVE_MANAGEMENT_PROTOCOL_H_

#include <Protocol/AlertStandardFormat.h>

///
/// Intel Active Management Technology Protocol
/// This protocol provides interface to get ASF boot options status
///

//
// Extern the GUID for protocol users.
//
extern EFI_GUID gActiveManagementProtocolGuid;

#define DXE_ACTIVE_MANAGEMENT_PROTOCOL_REVISION_1  1
//
// Forward reference for ANSI C compatibility
//
typedef struct _ACTIVE_MANAGEMENT_PROTOCOL  ACTIVE_MANAGEMENT_PROTOCOL;

///
/// Protocol definitions
///

/**
  Return current state of Boot Options
  @param[in] This                 Pointer to the EFI_ACTIVE_MANAGEMENT_PROTOCOL instance.
  @param[in, out] CurrentState    TRUE when the boot options is enabled

  @retval EFI_SUCCESS             Command succeed.
**/
typedef
EFI_STATUS
(EFIAPI *ACTIVE_MANAGEMENT_BOOT_OPTIONS_STATE) (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT BOOLEAN                          *CurrentState
);

/**
   This will return Storage Redirection boot device to boot

  @param[in] This                 The address of protocol
  @param[in, out] IdeBootDevice   Return the boot device number to boot
                                  Bit 1  Bit0
                                   0      0    USBr is connected to CD/DVD device
                                   0      1    USBr is connected to floppy device
                                  Bits 2-7: Reserved set to 0

  @retval EFI_SUCCESS             The function completed successfully.
**/
typedef
EFI_STATUS
(EFIAPI *ACTIVE_MANAGEMENT_STORAGE_REDIR_BOOT_DEVICE_SELECTED) (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT UINT8                            *IdeBootDevice
);

/**
  Return current ASF Boot Options

  @param[in] This                 Pointer to the EFI_ACTIVE_MANAGEMENT_PROTOCOL instance.
  @param[in, out] AsfBootOptions  ASF Boot Options

  @retval EFI_SUCCESS             Command succeed.
**/
typedef
EFI_STATUS
(EFIAPI *ACTIVE_MANAGEMENT_ASF_BOOT_OPTIONS_GET) (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT ASF_BOOT_OPTIONS                 **AsfBootOptions
);

/**
  This will return verbosity request option

  @param[in] This                 Pointer to the EFI_ACTIVE_MANAGEMENT_PROTOCOL instance.
  @param[in, out] CurrentState    Return the state of verbosity option

  @retval EFI_SUCCESS             The function completed successfully.
  @retval CurrentState            00 - No BootOption available
                                  01 - Non-Verbosity request
                                  02 - Verbosity request
**/
typedef
EFI_STATUS
(EFIAPI *ACTIVE_MANAGEMENT_VERBOSITY_REQUESTED) (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT UINT8                            *CurrentState
);

///
/// Intel Active Management Technology Protocol
/// It provides abstract level function of ASF boot options defined in ASF 2.0 specification for
/// other modules to get ASF boot options status.
///
struct _ACTIVE_MANAGEMENT_PROTOCOL {
  ///
  /// Revision for the protocol structure
  ///
  UINT8                                                Revision;
  ACTIVE_MANAGEMENT_ASF_BOOT_OPTIONS_GET               GetAsfBootOptions;
  ACTIVE_MANAGEMENT_BOOT_OPTIONS_STATE                 GetStorageRedirState;
  ACTIVE_MANAGEMENT_STORAGE_REDIR_BOOT_DEVICE_SELECTED GetStorageRedirBootDeviceSelected;
  ACTIVE_MANAGEMENT_BOOT_OPTIONS_STATE                 GetEnforceSecureBootState;
  ACTIVE_MANAGEMENT_BOOT_OPTIONS_STATE                 GetRemoteFlashState;
  ACTIVE_MANAGEMENT_BOOT_OPTIONS_STATE                 GetBiosSetupState;
  ACTIVE_MANAGEMENT_BOOT_OPTIONS_STATE                 GetBiosPauseState;
  ACTIVE_MANAGEMENT_BOOT_OPTIONS_STATE                 GetKvmState;
  ACTIVE_MANAGEMENT_BOOT_OPTIONS_STATE                 GetSecureEraseState;
  ACTIVE_MANAGEMENT_BOOT_OPTIONS_STATE                 GetConsoleLockState;
  ACTIVE_MANAGEMENT_BOOT_OPTIONS_STATE                 GetProgressMsgRequest;
  ACTIVE_MANAGEMENT_BOOT_OPTIONS_STATE                 GetSolState;
};

#endif
