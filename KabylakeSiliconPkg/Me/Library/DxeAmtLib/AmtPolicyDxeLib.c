/** @file
  Implementation file for AMT Policy functionality

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2016 Intel Corporation.

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

//
// Global variables
//
GLOBAL_REMOVE_IF_UNREFERENCED AMT_PEI_CONFIG               *mAmtPeiConfig = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED AMT_DXE_CONFIG               *mAmtDxeConfig = NULL;


/**
  Initialize module varialbe - mAmtPeiConfig for AMT PEI Config Block.

  @retval EFI_SUCCESS             mAmtPeiConfig is initialized.
  @retval All other error conditions encountered when mAmtPeiConfig initialized fail.
**/
STATIC
EFI_STATUS
AmtPeiConfigInit (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS            HobPtr;

  if (mAmtPeiConfig != NULL) {
    return EFI_SUCCESS;
  }

  //
  // Get AMT Policy HOB.
  //
  HobPtr.Guid  = GetFirstGuidHob (&gAmtPolicyHobGuid);
  ASSERT (HobPtr.Guid != NULL);
  if (HobPtr.Guid != NULL) {
    mAmtPeiConfig = (AMT_PEI_CONFIG *) GET_GUID_HOB_DATA (HobPtr.Guid);
    return EFI_SUCCESS;
  }

  return EFI_UNSUPPORTED;
}

/**
  Initialize module variable - mAmtDxeConfig for AMT DXE Config Block.

  @retval EFI_SUCCESS             mAmtDxeConfig is initialized.
  @retval All other error conditions encountered when mAmtDxeConfig initialized fail.
**/
EFI_STATUS
AmtDxeConfigInit (
  VOID
  )
{
  EFI_STATUS                      Status;
  ME_POLICY_PROTOCOL              *DxeMePolicy;

  if (mAmtDxeConfig != NULL) {
    return EFI_SUCCESS;
  }

  DxeMePolicy = NULL;
  Status = gBS->LocateProtocol (&gDxeAmtPolicyGuid, NULL, (VOID **) &DxeMePolicy);
  if (EFI_ERROR (Status) || (DxeMePolicy == NULL)) {
    DEBUG ((DEBUG_ERROR, "No AMT Policy Protocol available"));
    return EFI_UNSUPPORTED;
  }

  Status = GetConfigBlock ((VOID *) DxeMePolicy, &gAmtDxeConfigGuid, (VOID *) &mAmtDxeConfig);
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use IsAsfBiosSupportEnabled () function from now on.

  Check if Asf is enabled in setup options.

  @retval FALSE                   Asf is disabled.
  @retval TRUE                    Asf is enabled.
**/
BOOLEAN
AsfSupported (
  VOID
  )
{
  return IsAsfBiosSupportEnabled ();
}

/**
  Check if Asf is enabled in setup options.

  @retval FALSE                   Asf is disabled.
  @retval TRUE                    Asf is enabled.
**/
BOOLEAN
IsAsfBiosSupportEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;

  Status = AmtPeiConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  //
  // First check if ASF support is enabled in Setup.
  //
  if (mAmtPeiConfig->AsfEnabled != 1) {
    return FALSE;
  }

  return TRUE;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use IsAmtBiosSupportEnabled () function from now on.

  Check if Amt is enabled in setup options.

  @retval FALSE                   Amt is disabled.
  @retval TRUE                    Amt is enabled.
**/
BOOLEAN
AmtSupported (
  VOID
  )
{
  return IsAmtBiosSupportEnabled ();
}

/**
  Check if Amt is enabled in setup options.

  @retval FALSE                   Amt is disabled.
  @retval TRUE                    Amt is enabled.
**/
BOOLEAN
IsAmtBiosSupportEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;

  Status = AmtPeiConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  //
  // First check if AMT support is enabled in Setup.
  //
  if (mAmtPeiConfig->AmtEnabled != 1) {
    return FALSE;
  }

  return TRUE;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtIsHotkeyPressedEnabled () function from now on.

  Check if AMT BIOS Extension hotkey pressed is enabled in setup options.

  @retval FALSE                   MEBx hotkey pressed option is disabled.
  @retval TRUE                    MEBx hotkey pressed option is enabled.
**/
BOOLEAN
AmtHotkeyPressed (
  VOID
  )
{
  return AmtIsHotkeyPressedEnabled ();
}

/**
  Check if AMT BIOS Extension hotkey pressed is enabled in setup options.

  @retval FALSE                   MEBx hotkey pressed option is disabled.
  @retval TRUE                    MEBx hotkey pressed option is enabled.
**/
BOOLEAN
AmtIsHotkeyPressedEnabled (
  VOID
  )
{
  BOOLEAN                         Enabled;
  EFI_STATUS                      Status;

  Status = AmtDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  //
  // First check if AMT Setup Prompt is enabled in Setup.
  //
  if (mAmtDxeConfig->AmtbxHotkeyPressed == 1) {
    Enabled = TRUE;
  } else {
    Enabled = FALSE;
  }

  return Enabled;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtIsSelectionScreenEnabled () function from now on.

  Check if AMT BIOS Extension Selection Screen is enabled in setup options.

  @retval FALSE                   AMT Selection Screen is disabled.
  @retval TRUE                    AMT Selection Screen is enabled.
**/
BOOLEAN
AmtSelectionScreen (
  VOID
  )
{
  return AmtIsSelectionScreenEnabled ();
}

/**
  Check if AMT BIOS Extension Selection Screen is enabled in setup options.

  @retval FALSE                   AMT Selection Screen is disabled.
  @retval TRUE                    AMT Selection Screen is enabled.
**/
BOOLEAN
AmtIsSelectionScreenEnabled (
  VOID
  )
{
  BOOLEAN                         Enabled;
  EFI_STATUS                      Status;

  Status = AmtDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  //
  // First check if AMT Selection Screen is enabled in Setup.
  //
  if (mAmtDxeConfig->AmtbxSelectionScreen == 1) {
    Enabled = TRUE;
  } else {
    Enabled = FALSE;
  }

  return Enabled;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtIsWatchdogTimerEnabled () function from now on.

  Check if AMT Watchdog Timer is enabled in setup options.

  @retval FALSE                   AMT Watchdog Timer is disabled.
  @retval TRUE                    AMT Watchdog Timer is enabled.
**/
BOOLEAN
AmtWatchDog (
  VOID
  )
{
  return AmtIsWatchdogTimerEnabled ();
}

/**
  Check if AMT Watchdog Timer is enabled in setup options.

  @retval FALSE                   AMT Watchdog Timer is disabled.
  @retval TRUE                    AMT Watchdog Timer is enabled.
**/
BOOLEAN
AmtIsWatchdogTimerEnabled (
  VOID
  )
{
  BOOLEAN                         Enabled;
  EFI_STATUS                      Status;

  Status = AmtPeiConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  Enabled = FALSE;
  if (GetManageabilityModeSetting () != MNT_OFF) {
    if (IsAsfBiosSupportEnabled ()) {
      if (mAmtPeiConfig->WatchDog == 1) {
        Enabled = TRUE;
      }
    }
  }

  return Enabled;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtGetBiosWatchdogTimer () function from now on.

  Return BIOS watchdog timer value

  @retval UINT16                  BIOS ASF Watchdog Timer value
**/
UINT16
AmtWatchDogTimerBiosGet (
  VOID
  )
{
  return AmtGetBiosWatchdogTimer ();
}

/**
  Return BIOS watchdog timer value

  @retval UINT16                  BIOS ASF Watchdog Timer value
**/
UINT16
AmtGetBiosWatchdogTimer (
  VOID
  )
{
  EFI_STATUS                      Status;

  Status = AmtPeiConfigInit ();
  if (EFI_ERROR (Status)) {
    return 0;
  }

  return mAmtPeiConfig->WatchDogTimerBios;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtGetOsWatchdogTimer () function from now on.

  Return OS Watchdog timer value

  @retval UINT16                  OS ASF Watchdog Timer value
**/
UINT16
AmtWatchDogTimerOsGet (
  VOID
  )
{
  return AmtGetOsWatchdogTimer ();
}

/**
  Return OS Watchdog timer value

  @retval UINT16                  OS ASF Watchdog Timer value
**/
UINT16
AmtGetOsWatchdogTimer (
  VOID
  )
{
  EFI_STATUS                      Status;

  Status = AmtPeiConfigInit ();
  if (EFI_ERROR (Status)) {
    return 0;
  }

  return mAmtPeiConfig->WatchDogTimerOs;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtCiraRequestTrigger () function from now on.

  Provide CIRA request information from OEM code.

  @retval Check if any CIRA requirement during POST
**/
BOOLEAN
AmtCiraRequestTrigger (
  VOID
  )
{
  return AmtIsCiraRequested ();
}

/**
  Provide CIRA request information from OEM code.

  @retval Check if any CIRA requirement during POST
**/
BOOLEAN
AmtIsCiraRequested (
  VOID
  )
{
  EFI_STATUS                      Status;

  Status = AmtDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  return mAmtDxeConfig->CiraRequest == 1;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtCiraRequestTimeout () function from now on.

  Provide CIRA request Timeout from OEM code.

  @retval CIRA require Timeout for MPS connection to be established
**/
UINT8
AmtCiraRequestTimeout (
  VOID
  )
{
  return AmtGetCiraRequestTimeout ();
}

/**
  Provide CIRA request Timeout from OEM code.

  @retval CIRA require Timeout for MPS connection to be established
**/
UINT8
AmtGetCiraRequestTimeout (
  VOID
  )
{
  EFI_STATUS                      Status;

  Status = AmtDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  return (UINT8) (UINTN) mAmtDxeConfig->CiraTimeout;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use ManageabilityModeSetting () function from now on.

  Provide Manageability Mode setting from MEBx BIOS Sync Data

  @retval UINT8                   Manageability Mode = MNT_ON or MNT_OFF
**/
UINT8
ManageabilityModeSetting (
  VOID
  )
{
  return GetManageabilityModeSetting ();
}

/**
  Provide Manageability Mode setting from MEBx BIOS Sync Data

  @retval UINT8                   Manageability Mode = MNT_ON or MNT_OFF
**/
UINT8
GetManageabilityModeSetting (
  VOID
  )
{
  EFI_STATUS                      Status;

  Status = AmtDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return 0;
  }

  return (UINT8) (mAmtDxeConfig->ManageabilityMode);
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtIsUnconfigureMeEnabled () function from now on.

  Provide UnConfigure ME without password request from OEM code.

  @retval Check if unConfigure ME without password request
**/
BOOLEAN
AmtUnConfigureMe (
  VOID
  )
{
  return AmtIsUnconfigureMeEnabled ();
}

/**
  Provide UnConfigure ME without password request from OEM code.

  @retval Check if Unconfigure ME without password request
**/
BOOLEAN
AmtIsUnconfigureMeEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;

  Status = AmtDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  return mAmtDxeConfig->UnConfigureMe == 1;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtIsHideUnconfigureMeConfPromptEnabled () function from now on.

  Provide 'Hiding the Unconfigure ME without password confirmation prompt' request from OEM code.

  @retval Check if 'Hide unConfigure ME without password Confirmation prompt' request
**/
BOOLEAN
AmtHideUnConfigureMeConfPrompt (
  VOID
  )
{
  return AmtIsHideUnconfigureMeConfPromptEnabled ();
}

/**
  Provide 'Hiding the Unconfigure ME without password confirmation prompt' request from OEM code.

  @retval Check if 'Hide Unconfigure ME without password Confirmation prompt' request
**/
BOOLEAN
AmtIsHideUnconfigureMeConfPromptEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;

  Status = AmtDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  return mAmtDxeConfig->HideUnConfigureMeConfirm == 1;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtIsMebxDebugMsgEnabled () function from now on.

  Provide show MEBx debug message request from OEM code.

  @retval Check show MEBx debug message request
 **/
BOOLEAN
AmtMebxDebugMsg (
  VOID
  )
{
  return AmtIsMebxDebugMsgEnabled ();
}

/**
  Provide show MEBx debug message request from OEM code.

  @retval Check show MEBx debug message request
 **/
BOOLEAN
AmtIsMebxDebugMsgEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;

  Status = AmtDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  return mAmtDxeConfig->MebxDebugMsg == 1;
}

/**
  Provide on-board device list table and do not need to report them to AMT.  AMT only need to know removable PCI device
  information.

  @retval on-board device list table pointer other than system device.
**/
UINT32
AmtPciDeviceFilterOutTable (
  VOID
  )
{
  EFI_STATUS                      Status;

  Status = AmtDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  return mAmtDxeConfig->PciDeviceFilterOutTable;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use IsUsbProvisionSupportEnabled () function from now on.

  Check if USB provisioning enabled/disabled in Policy.

  @retval FALSE                   USB provisioning is disabled.
  @retval TRUE                    USB provisioning is enabled.
**/
BOOLEAN
USBProvisionSupport (
  VOID
  )
{
  return IsUsbProvisionSupportEnabled ();
}

/**
  Check if USB provisioning enabled/disabled in Policy.

  @retval FALSE                   USB provisioning is disabled.
  @retval TRUE                    USB provisioning is enabled.
**/
BOOLEAN
IsUsbProvisionSupportEnabled (
  VOID
  )
{
  BOOLEAN                         Enabled;
  EFI_STATUS                      Status;

  Status = AmtDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  Enabled = FALSE;

  //
  // First check if USB Provision is enabled in Setup.
  //
  if (mAmtDxeConfig->UsbProvision == 1) {
    Enabled = TRUE;
  }

  return Enabled;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use IsFwProgressSupported () function from now on.

  This will return Progress event Option.
  True if the option is enabled.

  @retval True                    Progress Event is enabled.
  @retval False                   Progress Event is disabled.
**/
BOOLEAN
FwProgressSupport (
  VOID
  )
{
  return IsFwProgressSupported ();
}

/**
  This will return Progress event Option.
  True if the option is enabled.

  @retval True                    Progress Event is enabled.
  @retval False                   Progress Event is disabled.
**/
BOOLEAN
IsFwProgressSupported (
  VOID
  )
{
  BOOLEAN                         Supported;
  EFI_STATUS                      Status;

  Status = AmtPeiConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  Supported = FALSE;

  //
  // First check if FW Progress is enabled in Setup.
  //
  if (mAmtPeiConfig->FwProgress == 1) {
    Supported = TRUE;
  }

  return Supported;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtIsForceMebxSyncUpEnabled () function from now on.

  Check if ForcMebxSyncUp is enabled in setup options.

  @retval FALSE                   ForcMebxSyncUp is disabled.
  @retval TRUE                    ForcMebxSyncUp is enabled.
**/
BOOLEAN
AmtForcMebxSyncUp (
  VOID
  )
{
  return AmtIsForceMebxSyncUpEnabled ();
}

/**
  Check if ForcMebxSyncUp is enabled in setup options.

  @retval FALSE                   ForcMebxSyncUp is disabled.
  @retval TRUE                    ForcMebxSyncUp is enabled.
**/
BOOLEAN
AmtIsForceMebxSyncUpEnabled (
  VOID
  )
{
  BOOLEAN                         Enabled;
  EFI_STATUS                      Status;

  Status = AmtDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  if (mAmtDxeConfig->ForcMebxSyncUp == 1) {
    Enabled = TRUE;
  } else {
    Enabled = FALSE;
  }

  return Enabled;
}
