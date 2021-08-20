/** @file
  Implementation file for AMT functionality

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2015 Intel Corporation.

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

#include "AmtDxeLibInternals.h"
#include <Protocol/AlertStandardFormat.h>

#include <Library/BaseLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED ACTIVE_MANAGEMENT_PROTOCOL  *mActiveManagement = NULL;


/**
  Check if Asf is enabled in setup options.

  @retval EFI_SUCCESS             mActiveManagement is not NULL
  @retval                         Error Status code returned by
                                  LocateProtocol.
**/
EFI_STATUS
AmtLibInit (
  VOID
  )
{
  EFI_STATUS  Status;

  if (mActiveManagement == NULL) {
    Status = gBS->LocateProtocol (
                    &gActiveManagementProtocolGuid,
                    NULL,
                    (VOID **) &mActiveManagement
                    );
  } else {
    Status = EFI_SUCCESS;
  }

  return Status;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use ActiveManagementIsStorageRedirectionEnabled () function from now on.

  This will return Storage Redirection Boot Option.
  True if the option is enabled.

  @retval True                    Storage Redirection boot option is enabled.
  @retval False                   Storage Redirection boot option is disabled.
**/
BOOLEAN
ActiveManagementEnableStorageRedir (
  VOID
  )
{
  return ActiveManagementIsStorageRedirectionEnabled ();
}

/**
  This will return Storage Redirection Boot Option.
  True if the option is enabled.

  @retval True                    Storage Redirection boot option is enabled.
  @retval False                   Storage Redirection boot option is disabled.
**/
BOOLEAN
ActiveManagementIsStorageRedirectionEnabled (
  VOID
  )
{
  BOOLEAN                 CurrentState;

  CurrentState  = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetStorageRedirState (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use ActiveManagementGetStorageRedirectionBootDevice () function from now on.

  This will return Storage Redirection boot device number/type

  @retval            Return the boot device number to boot
                                  Bit 1  Bit0
                                   0    0    USBr is connected to CD/DVD device
                                   0    1    USBr is connected to floppy device
                                  Bits 2-7: Reserved set to 0
**/
UINT8
ActiveManagementStorageRedirBootDeviceGet (
  VOID
  )
{
  return ActiveManagementGetStorageRedirectionBootDevice ();
}

/**
  This will return Storage Redirection boot device number/type

  @retval            Return the boot device number to boot
                                  Bit 1  Bit0
                                   0    0    USBr is connected to CD/DVD device
                                   0    1    USBr is connected to floppy device
                                  Bits 2-7: Reserved set to 0
**/
UINT8
ActiveManagementGetStorageRedirectionBootDevice (
  VOID
  )
{
  UINT8 StorageRedirBootDevice;
  StorageRedirBootDevice = 0;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetStorageRedirBootDeviceSelected (mActiveManagement, &StorageRedirBootDevice);
  }

  return StorageRedirBootDevice;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use ActiveManagementIsEnforceSecureBootEnabled () function from now on.

  This will return Enforce Secure Boot over Storage Redirection Boot Option.
  True if the option is enabled.

  @retval True                    Enforce Secure Boot is enabled.
  @retval False                   Enforce Secure Boot is disabled.
**/
BOOLEAN
ActiveManagementEnforceSecureBoot (
  VOID
  )
{
  return ActiveManagementIsEnforceSecureBootEnabled ();
}

/**
  This will return Enforce Secure Boot over Storage Redirection Boot Option.
  True if the option is enabled.

  @retval True                    Enforce Secure Boot is enabled.
  @retval False                   Enforce Secure Boot is disabled.
**/
BOOLEAN
ActiveManagementIsEnforceSecureBootEnabled (
  VOID
  )
{
  BOOLEAN CurrentState;

  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetEnforceSecureBootState (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use ActiveManagementIsEnterSetupEnabled () function from now on.

  This will return BIOS Setup Boot Option.
  True if the option is enabled.

  @retval True                    BIOS Setup is enabled.
  @retval False                   BIOS Setup is disabled.
**/
BOOLEAN
ActiveManagementEnterSetup (
  VOID
  )
{
  return ActiveManagementIsEnterSetupEnabled ();
}

/**
  This will return BIOS Setup Boot Option.
  True if the option is enabled.

  @retval True                    BIOS Setup is enabled.
  @retval False                   BIOS Setup is disabled.
**/
BOOLEAN
ActiveManagementIsEnterSetupEnabled (
  VOID
  )
{
  BOOLEAN CurrentState;

  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetBiosSetupState (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use ActiveManagementIsPauseBootEnabled () function from now on.

  This will return BIOS Pause Boot Option.
  True if the option is enabled.

  @retval True                    BIOS Pause is enabled.
  @retval False                   BIOS Pause is disabled.
**/
BOOLEAN
ActiveManagementPauseBoot (
  VOID
  )
{
  return ActiveManagementIsPauseBootEnabled ();
}

/**
  This will return BIOS Pause Boot Option.
  True if the option is enabled.

  @retval True                    BIOS Pause is enabled.
  @retval False                   BIOS Pause is disabled.
**/
BOOLEAN
ActiveManagementIsPauseBootEnabled (
  VOID
  )
{
  BOOLEAN CurrentState;

  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetBiosPauseState (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use ActiveManagementIsKvmEnabled () function from now on.

  This will return KVM Boot Option.
  True if the option is enabled.

  @retval True                    KVM is enabled.
  @retval False                   KVM is disabled.
**/
BOOLEAN
EFIAPI
ActiveManagementEnableKvm (
  VOID
  )
{
  return ActiveManagementIsKvmEnabled ();
}

/**
  This will return KVM Boot Option.
  True if the option is enabled.

  @retval True                    KVM is enabled.
  @retval False                   KVM is disabled.
**/
BOOLEAN
EFIAPI
ActiveManagementIsKvmEnabled (
  VOID
  )
{
  BOOLEAN CurrentState;

  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetKvmState (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use ActiveManagementIsSecureEraseEnabled () function from now on.

  This will return Secure Erase Boot Option.
  True if the option is enabled.

  @retval True                    Secure Erase is enabled.
  @retval False                   Secure Erase is disabled.
**/
BOOLEAN
ActiveManagementEnableSecureErase (
  VOID
  )
{
  return ActiveManagementIsSecureEraseEnabled ();
}

/**
  This will return Secure Erase Boot Option.
  True if the option is enabled.

  @retval True                    Secure Erase is enabled.
  @retval False                   Secure Erase is disabled.
**/
BOOLEAN
ActiveManagementIsSecureEraseEnabled (
  VOID
  )
{
  BOOLEAN CurrentState;

  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetSecureEraseState (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use ActiveManagementIsSolEnabled () function from now on.

  This will return Serial-over-Lan Boot Option.
  True if the option is enabled.

  @retval True                    Serial-over-Lan is enabled.
  @retval False                   Serial-over-Lan is disabled.
**/
BOOLEAN
ActiveManagementEnableSol (
  VOID
  )
{
  return ActiveManagementIsSolEnabled ();
}

/**
  This will return Serial-over-Lan Boot Option.
  True if the option is enabled.

  @retval True                    Serial-over-Lan is enabled.
  @retval False                   Serial-over-Lan is disabled.
**/
BOOLEAN
ActiveManagementIsSolEnabled (
  VOID
  )
{
  BOOLEAN                 CurrentState;
  UINTN                   VariableSize;
  EFI_STATUS              Status;
  ME_BIOS_EXTENSION_SETUP MeBiosExtensionSetupData;

  VariableSize  = 0;
  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetSolState (mActiveManagement, &CurrentState);
  }

  VariableSize = sizeof (MeBiosExtensionSetupData);
  Status = gRT->GetVariable (
                  ME_BIOS_EXTENSION_SETUP_VARIABLE_NAME,
                  &gMeBiosExtensionSetupGuid,
                  NULL,
                  &VariableSize,
                  &MeBiosExtensionSetupData
                  );
  if (!EFI_ERROR (Status)) {
    if ((MeBiosExtensionSetupData.AmtSol & SOL_ENABLE) == 0) {
      CurrentState = FALSE;
    }
  }

  return CurrentState;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use ActiveManagementIsConsoleLocked () function from now on.

  This will return Console Lock Boot Option.
  True if the option is enabled.

  @retval True                    Console Lock is enabled.
  @retval False                   Console Lock is disabled.
**/
BOOLEAN
EFIAPI
ActiveManagementConsoleLocked (
  VOID
  )
{
  return ActiveManagementIsConsoleLocked ();
}

/**
  This will return Console Lock Boot Option.
  True if the option is enabled.

  @retval True                    Console Lock is enabled.
  @retval False                   Console Lock is disabled.
**/
BOOLEAN
EFIAPI
ActiveManagementIsConsoleLocked (
  VOID
  )
{
  BOOLEAN CurrentState;

  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetConsoleLockState (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use ActiveManagementIsFwProgressEnabled () function from now on.

  This will return Progress Event Option.
  True if the option is enabled.

  @retval True                    Progress Event is enabled.
  @retval False                   Progress Event is disabled.
**/
BOOLEAN
ActiveManagementFwProgress (
  VOID
  )
{

  return ActiveManagementIsFwProgressEnabled ();
}

/**
  This will return Progress Event Option.
  True if the option is enabled.

  @retval True                    Progress Event is enabled.
  @retval False                   Progress Event is disabled.
**/
BOOLEAN
ActiveManagementIsFwProgressEnabled (
  VOID
  )
{
  BOOLEAN CurrentState;

  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetProgressMsgRequest (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  Send KVM initialization message

  @retval True                    KVM Initialization is successful
  @retval False                   KVM is not enabled
**/
BOOLEAN
BdsKvmInitialization (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINT32                          ResponseCode;

  MeReportError (MSG_KVM_WAIT);
  Status = AmtQueryKvm (QueryRequest, &ResponseCode);
  if (EFI_ERROR (Status)) {
    MeReportError (MSG_KVM_TIMES_UP);
    AmtQueryKvm (CancelRequest, &ResponseCode);
  } else if (ResponseCode == KvmSessionCancelled) {
    MeReportError (MSG_KVM_REJECTED);
  } else {
    return TRUE;
  }

  return FALSE;
}
