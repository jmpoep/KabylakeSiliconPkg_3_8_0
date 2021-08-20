/** @file
  Header file for AMT functionality

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
#ifndef _DXE_AMT_LIB_H_
#define _DXE_AMT_LIB_H_

#include <MeBiosExtensionSetup.h>


//
// Prototype for AMT
//

/**
  Check if Asf is enabled in setup options.

  @retval EFI_SUCCESS             mActiveManagement is not NULL
  @retval                         Error Status code returned by
                                  LocateProtocol.
**/
EFI_STATUS
AmtLibInit (
  VOID
  );

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
  );

/**
  This will return Storage Redirection Boot Option.
  True if the option is enabled.

  @retval True                    Storage Redirection boot option is enabled.
  @retval False                   Storage Redirection boot option is disabled.
**/
BOOLEAN
ActiveManagementIsStorageRedirectionEnabled (
  VOID
  );

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
  );

/**
  This will return IDE Redirection boot device index to boot

  @retval IdeBootDevice           Return the boot device number to boot
                                    Bit 1  Bit0
                                     0    0    USBr is connected to CD/DVD device
                                     0    1    USBr is connected to floppy device
                                  Bits 2-7: Reserved set to 0
**/
UINT8
ActiveManagementGetStorageRedirectionBootDevice(
  VOID
  );

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
  );

/**
  This will return Enforce Secure Boot over Storage Redirection Boot Option.
  True if the option is enabled.

  @retval True                    Enforce Secure Boot is enabled.
  @retval False                   Enforce Secure Boot is disabled.
**/
BOOLEAN
ActiveManagementIsEnforceSecureBootEnabled (
  VOID
  );

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
  );

/**
  This will return BIOS Setup Boot Option.
  True if the option is enabled.

  @retval True                    BIOS Setup is enabled.
  @retval False                   BIOS Setup is disabled.
**/
BOOLEAN
ActiveManagementIsEnterSetupEnabled (
  VOID
  );

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
  );

/**
  This will return BIOS Pause Boot Option.
  True if the option is enabled.

  @retval True                    BIOS Pause is enabled.
  @retval False                   BIOS Pause is disabled.
**/
BOOLEAN
ActiveManagementIsPauseBootEnabled (
  VOID
  );

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
  );

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
  );

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
  );

/**
  This will return Secure Erase Boot Option.
  True if the option is enabled.

  @retval True                    Secure Erase is enabled.
  @retval False                   Secure Erase is disabled.
**/
BOOLEAN
ActiveManagementIsSecureEraseEnabled (
 VOID
 );

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
  );

/**
  This will return Serial-over-Lan Boot Option.
  True if the option is enabled.

  @retval True                    Serial-over-Lan is enabled.
  @retval False                   Serial-over-Lan is disabled.
**/
BOOLEAN
ActiveManagementIsSolEnabled (
  VOID
  );

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
  );

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
  );

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
  );

/**
  This will return Progress Event Option.
  True if the option is enabled.

  @retval True                    Progress event is enabled.
  @retval False                   Progress event is disabled.
**/
BOOLEAN
ActiveManagementIsFwProgressEnabled (
  VOID
  );

/**
  Send KVM initialization message

  @retval True                    KVM Initialization is successful
  @retval False                   KVM is not enabled
**/
BOOLEAN
BdsKvmInitialization (
  VOID
  );

//
// Prototype for AMT Policy
//
/**
  Initialize module variable - mAmtDxeConfig for AMT DXE Config Block.

  @retval EFI_SUCCESS             mAmtDxeConfig is initialized.
  @retval All other error conditions encountered when mAmtDxeConfig initialized fail.
**/
EFI_STATUS
AmtDxeConfigInit (
  VOID
  );

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
  );

/**
  Check if Asf is enabled in setup options.

  @retval FALSE                   Asf is disabled.
  @retval TRUE                    Asf is enabled.
**/
BOOLEAN
IsAsfBiosSupportEnabled (
  VOID
  );

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
  );

/**
  Check if Amt is enabled in setup options.

  @retval FALSE                   Amt is disabled.
  @retval TRUE                    Amt is enabled.
**/
BOOLEAN
IsAmtBiosSupportEnabled (
  VOID
  );

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtIsHotkeyPressedEnabled () function from now on.

  Check if AMT BIOS Extension hotkey pressed is enabled in setup options.

  @retval FALSE                   MEBx hotkey pressed option is enabled.
  @retval TRUE                    MEBx hotkey pressed option is enabled.
**/
BOOLEAN
AmtHotkeyPressed (
  VOID
  );

/**
  Check if AMT BIOS Extension hotkey pressed is enabled in setup options.

  @retval FALSE                   MEBx hotkey pressed option is enabled.
  @retval TRUE                    MEBx hotkey pressed option is enabled.
**/
BOOLEAN
AmtIsHotkeyPressedEnabled (
  VOID
  );

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
  );

/**
  Check if AMT BIOS Extension Selection Screen is enabled in setup options.

  @retval FALSE                   AMT Selection Screen is disabled.
  @retval TRUE                    AMT Selection Screen is enabled.
**/
BOOLEAN
AmtIsSelectionScreenEnabled (
  VOID
  );

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
  );

/**
  Check if AMT Watchdog Timer is enabled in setup options.

  @retval FALSE                   AMT Watchdog Timer is disabled.
  @retval TRUE                    AMT Watchdog Timer is enabled.
**/
BOOLEAN
AmtIsWatchdogTimerEnabled (
  VOID
  );

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtGetBiosWatchdogTimer () function from now on.

  Return BIOS watchdog timer value

  @retval UINT16                  BIOS ASF Watchdog Timer value
**/
UINT16
AmtWatchDogTimerBiosGet (
  VOID
  );

/**
  Return BIOS watchdog timer value

  @retval UINT16                  BIOS ASF Watchdog Timer value
**/
UINT16
AmtGetBiosWatchdogTimer(
  VOID
  );

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtGetOsWatchdogTimer () function from now on.

  Return OS Watchdog timer value

  @retval UINT16                  OS ASF Watchdog Timer value
**/
UINT16
AmtWatchDogTimerOsGet (
  VOID
  );

/**
  Return OS Watchdog timer value

  @retval UINT16                  OS ASF Watchdog Timer value
**/
UINT16
AmtGetOsWatchdogTimer (
  VOID
  );

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtCiraRequestTrigger () function from now on.

  Provide CIRA request information from OEM code.

  @retval Check if any CIRA requirement during POST
**/
BOOLEAN
AmtCiraRequestTrigger (
  VOID
  );

/**
  Provide CIRA request information from OEM code.

  @retval Check if any CIRA requirement during POST
**/
BOOLEAN
AmtIsCiraRequested (
  VOID
  );

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtCiraRequestTimeout () function from now on.

  Provide CIRA request Timeout from OEM code.

  @retval CIRA require Timeout for MPS connection to be established
**/
UINT8
AmtCiraRequestTimeout (
  VOID
  );

/**
  Provide CIRA request Timeout from OEM code.

  @retval CIRA require Timeout for MPS connection to be established
**/
UINT8
AmtGetCiraRequestTimeout (
  VOID
  );

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use ManageabilityModeSetting () function from now on.

  Provide Manageability Mode setting from MEBx BIOS Sync Data


  @retval UINT8                   Manageability Mode = MNT_ON or MNT_OFF
**/
UINT8
ManageabilityModeSetting (
  VOID
  );

/**
  Provide Manageability Mode setting from MEBx BIOS Sync Data

  @retval UINT8                   Manageability Mode = MNT_ON or MNT_OFF
**/
UINT8
GetManageabilityModeSetting (
  VOID
  );

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtIsUnconfigureMeEnabled () function from now on.

  Provide UnConfigure ME without password request from OEM code.

  @retval Check if unConfigure ME without password request
**/
BOOLEAN
AmtUnConfigureMe (
  VOID
  );

/**
  Provide UnConfigure ME without password request from OEM code.

  @retval Check if Unconfigure ME without password request
**/
BOOLEAN
AmtIsUnconfigureMeEnabled (
  VOID
  );

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtIsHideUnconfigureMeConfPromptEnabled () function from now on.

  Provide 'Hiding the Unconfigure ME without password confirmation prompt' request from OEM code.

  @retval Check if 'Hide unConfigure ME without password Confirmation prompt' request
**/
BOOLEAN
AmtHideUnConfigureMeConfPrompt (
  VOID
  );

/**
  Provide 'Hiding the Unconfigure ME without password confirmation prompt' request from OEM code.

  @retval Check if 'Hide unConfigure ME without password Confirmation prompt' request
**/
BOOLEAN
AmtIsHideUnconfigureMeConfPromptEnabled (
  VOID
  );

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use AmtIsMebxDebugMsgEnabled () function from now on.

  Provide show MEBx debug message request from OEM code.

  @retval Check show MEBx debug message request
 **/
BOOLEAN
AmtMebxDebugMsg (
  VOID
  );

/**
  Provide show MEBx debug message request from OEM code.

  @retval Check show MEBx debug message request
 **/
BOOLEAN
AmtIsMebxDebugMsgEnabled (
  VOID
  );

/**
  Provide on-board device list table and do not need to report them to AMT.  AMT only need to know removable PCI device
  information.

  @retval on-board device list table pointer other than system device.
**/
UINT32
AmtPciDeviceFilterOutTable (
  VOID
  );

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
  );

/**
  Check if USB provisioning enabled/disabled in Policy.

  @retval FALSE                   USB provisioning is disabled.
  @retval TRUE                    USB provisioning is enabled.
**/
BOOLEAN
IsUsbProvisionSupportEnabled(
  VOID
  );

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
  );

/**
  This will return progress event Option.
  True if the option is enabled.

  @retval True                    progress event is enabled.
  @retval False                   progress event is disabled.
**/
BOOLEAN
IsFwProgressSupported (
  VOID
  );

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
  );

/**
  Check if ForcMebxSyncUp is enabled in setup options.

  @retval FALSE                   ForcMebxSyncUp is disabled.
  @retval TRUE                    ForcMebxSyncUp is enabled.
**/
BOOLEAN
AmtIsForceMebxSyncUpEnabled (
  VOID
  );

/**
  Dump ME_BIOS_EXTENSION_SETUP variable

  @param[in] *MeBiosExtensionSetup Pointer to ME_BIOS_EXTENSION_SETUP variable
**/
VOID
DxeMebxSetupVariableDebugDump (
  IN ME_BIOS_EXTENSION_SETUP  *MeBiosExtensionSetup OPTIONAL
  );

//
// Heci Messages for AMT/ASF ME Client
//

/**
  Stop ASF Watch Dog Timer HECI message.
**/
VOID
AsfStopWatchDog (
  VOID
  );

/**
  Start ASF Watch Dog Timer

  @param[in] WatchDogType         Which kind of WatchDog, ASF OS WatchDog Timer setting or ASF BIOS WatchDog Timer setting

**/
VOID
AsfStartWatchDog (
  IN  UINT8                       WatchDogType
  );

/**
  This is used to send KVM request message to Intel ME. When
  Bootoptions indicate that a KVM session is requested then BIOS
  will send this message before any graphical display output to
  ensure that FW is ready for KVM session.

  @param[in] QueryType            0 - Query Request
                                  1 - Cancel Request
  @param[out] ResponseCode        1h - Continue, KVM session established.
                                  2h - Continue, KVM session cancelled.

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
AmtQueryKvm (
  IN  UINT32                      QueryType,
  OUT UINT32                      *ResponseCode
  );

/**
  Send secure erase operation status using PET

  @param[in]    OperationResult   Status of secure erase operation

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
SendRsePetAlert (
  IN EFI_STATUS                        OperationResult
  );

/**
  Use ASF_GetRsePassword to get disk password from the FW

  @param[in,out]   Password            Preallocated buffer to save c string
                                       password to. It has to be at least 32
                                       characters wide.

  @retval EFI_SUCCESS                  Buffer Password contains returned password
  @retval EFI_NOT_FOUND                Either there is no password in AMT memory
                                       or Heci communication failed
  @retval EFI_DEVICE_ERROR             Failed to initialize HECI
  @retval EFI_TIMEOUT                  HECI is not ready for communication
  @retval EFI_UNSUPPORTED              Current ME mode doesn't support send this function
**/
EFI_STATUS
GetRsePassword (
  IN OUT CHAR16                       *Password
  );

/**
  Clears boot options by sending a proper ASF command through HECI

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
ClearBootOptions (
  VOID
  );

/**
  Send ASF_ReportBiosStatus message

  @param[in]       BiosStatus     Current bios status

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
ReportBiosStatus (
  EFI_STATUS                           BiosStatus
  );

#endif
