/** @file
  Header file for the Active Management Driver.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2016 Intel Corporation.

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
#ifndef _ACTIVE_MANAGEMENT_H_
#define _ACTIVE_MANAGEMENT_H_

#include <MeChipset.h>
#include <Amt.h>
#include <Library/DxeAmtLib.h>

//
// Used during initialization
//
#include <Protocol/AlertStandardFormat.h>
//
// Driver Produced Protocols
//
#include <Protocol/ActiveManagement.h>

//
// Private data structure definitions for the driver
//
#define ACTIVE_MANAGEMENT_PRIVATE_DATA_SIGNATURE  SIGNATURE_32 ('A', 'M', 'T', 'P')

typedef struct {
  UINTN                               Signature;
  EFI_HANDLE                          Handle;
  ACTIVE_MANAGEMENT_PROTOCOL          ActiveManagementProtocol;
  ALERT_STANDARD_FORMAT_PROTOCOL      *Asf;
} ACTIVE_MANAGEMENT_INSTANCE;

#define ACTIVE_MANAGEMENT_INSTANCE_FROM_ACTIVE_MANAGEMENT_PROTOCOL(a) \
  CR ( \
  a, \
  ACTIVE_MANAGEMENT_INSTANCE, \
  ActiveManagementProtocol, \
  ACTIVE_MANAGEMENT_PRIVATE_DATA_SIGNATURE \
  )

//
// Function prototypes used by the AMT protocol.
//

/**
  Return current ASF Boot Options

  @param[in] This                 Pointer to the EFI_ACTIVE_MANAGEMENT_PROTOCOL instance.
  @param[in, out] AsfBootOptions  ASF Boot Options

  @retval EFI_SUCCESS             Boot options updated
**/
EFI_STATUS
EFIAPI
GetAsfBootOptions (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT ASF_BOOT_OPTIONS                 **AsfBootOptions
);

/**
  This will return Storage Redirection Boot Option.
  True if the option is enabled.

  @param[in] This                 The address of protocol
  @param[in, out] CurrentState    Return the state of Storage Redireciton Boot Option

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
GetStorageRedirState (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT BOOLEAN                          *CurrentState
);

/**
  This will return Storage Redirection boot device to boot

  @param[in] This                 The address of protocol
  @param[in, out] BootDevice      Return the boot device number to boot
                                  Bit 1  Bit0
                                   0      0    USBr is connected to CD/DVD device
                                   0      1    USBr is connected to floppy device
                                  Bits 2-7: Reserved set to 0

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
GetStorageRedirBootDeviceSelected (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT UINT8                            *BootDevice
);

/**
  This will return Enforce Secure Boot over Storage Redirection Boot Option.
  True if the option is enabled.

  @param[in] This                 The address of protocol
  @param[in, out] CurrentState    Return the state of Enforce Secure Boot over Storage Redirection Boot Option

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
GetEnforceSecureBootState (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT BOOLEAN                          *CurrentState
);

/**
  This will return Remote Flash Boot Option.
  True if the option is enabled.

  @param[in] This                 The address of protocol
  @param[in, out] CurrentState    Return the state of Remote Flash Boot Option

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
GetRemoteFlashState (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT BOOLEAN                          *CurrentState
);

/**
  This will return BIOS Setup Boot Option.
  True if the option is enabled.

  @param[in] This                 The address of protocol
  @param[in, out] CurrentState    Return the state of BIOS Setup Boot Option

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
GetBiosSetupState (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT BOOLEAN                          *CurrentState
);

/**
  This will return BIOS Pause Boot Option.
  True if the option is enabled.

  @param[in] This                 The address of protocol
  @param[in, out] CurrentState    Return the state of BIOS Pause Boot Option

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
GetBiosPauseState (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT BOOLEAN                          *CurrentState
);

/**
  This will return KVM Boot Option.
  True if the option is enabled.

  @param[in] This                 The address of protocol
  @param[in, out] CurrentState    Return the state of KVM Boot Option

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
GetKvmState (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT BOOLEAN                          *CurrentState
);

/**
  This will return Secure Erase state.
  True if the option is enabled.

  @param[in] This                 The address of protocol
  @param[in, out] CurrentState    Return the state of Secure Erase Option

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
GetSecureEraseState (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT BOOLEAN                          *CurrentState
);

/**
  This will return Console Lock Boot Option.
  True if the option is enabled.

  @param[in] This                 The address of protocol
  @param[in, out] CurrentState    Return the state of Console Lock Boot Option

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
GetConsoleLockState (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT BOOLEAN                          *CurrentState
);

/**
  This will return Progress Event Option.
  True if the option is enabled.

  @param[in] This                 The address of protocol
  @param[in, out] CurrentState    Return the state of progress event Option

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
GetProgressMsgRequest (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT BOOLEAN                          *CurrentState
);

/**
  This will return Serial-over-Lan Boot Option.
  True if the option is enabled.

  @param[in] This                 The address of protocol
  @param[in, out] CurrentState    Return the state of Serial-over-Lan Boot Option

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
GetSolState (
  IN     ACTIVE_MANAGEMENT_PROTOCOL       *This,
  IN OUT BOOLEAN                          *CurrentState
);


/**
  Entry point for the Active Management Driver.

  @param[in] ImageHandle          Image handle of this driver.
  @param[in] SystemTable          Global system service table.

  @retval EFI_SUCCESS             Initialization complete.
  @exception EFI_UNSUPPORTED      The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR        Device error, driver exits abnormally.
**/
EFI_STATUS
EFIAPI
ActiveManagementEntryPoint (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
);

#endif
