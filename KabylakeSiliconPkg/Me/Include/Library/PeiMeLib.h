/** @file
  Header file for PEI Me functionality

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2019 Intel Corporation.

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
#ifndef _PEI_ME_LIB_H_
#define _PEI_ME_LIB_H_

#include <MkhiMsgs.h>
#include <MeChipset.h>
#include <MeBiosPayloadData.h>

#define ME_STATE_STALL_1_SECOND 1000000
#define MSG_MAX_WAIT_TIMEOUT    5

//
// Prototype for HECI message PEI phase
//

/**
  Send DRAM init done message through HECI to inform ME of memory initialization done.

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] MeHgs                ME UMA data
  @param[out] MeHfs              ME response to DID

  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
PeiHeciSendDid (
  IN  UINT32                      DidInput,
  OUT UINT8                       *BiosAction
  );

/**
  Send ICC request through HECI to query if CSME FW requires the warm reset flow from a previous boot.

  @param[out] WarmResetRequired   1 - CSME requires a warm reset to complete BCLK ramp en flow

  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
PeiHeciIccBclkMsg (
  OUT UINT8    *WarmResetRequired
  );

/**
  Send HSIO request through HECI to get the HSIO settings version on CSME side.

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] BiosCmd              HSIO command: 0 - close interface, 1 - report HSIO version
  @param[out] FwSts               FwSts

  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
PeiHeciHsioMsg (
  IN  UINT32                      BiosCmd,
  OUT UINT16                      *Crc
  );

/**
  Send the required system ChipsetInit Table to ME FW.

  @param[in] ChipsetInitTable     The required system ChipsetInit Table.
  @param[in] ChipsetInitTableLen  Length of the table in bytes
  @param[in] BypassPhySyncReset   Bypass the reset after PhySync

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
PeiHeciChipsetInitSyncMsg (
  IN  UINT8                       *ChipsetInitTable,
  IN  UINT32                      ChipsetInitTableLen,
  IN  BOOLEAN                     BypassPhySyncReset
  );

/**
  Send Get MBP from FW

  @param[in] MbpHeader              MBP header of the response
  @param[in] MbpItems               MBP items of the response
  @paran[in] SkipMbp                Skip MBP

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciGetMbpMsg (
  IN OUT MBP_HEADER            *MbpHeader,
  IN OUT UINT32                *MbpItems,
  IN BOOLEAN                   SkibMbp
  );

/**
  Send Manufacturing Reset and Halt

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciBupManufacturingResetAndHalt (
  VOID
  );

/**
  Send Get Firmware SKU Request to ME

  @param[in] FwCapsSku              ME Firmware Capability SKU

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciGetFwCapsSkuMsg (
  IN OUT MEFWCAPS_SKU               *FwCapsSku
  );

/**
  The Get FW Feature Status message is based on MKHI interface.
  This command is used by BIOS/IntelR MEBX to get firmware runtime status.
  The GET FW RUNTIME STATUS message doesn't need to check the HFS.FWInitComplete
  value before sending the command.
  It means this message can be sent regardless of HFS.FWInitComplete.

  @param[out] RuleData            MEFWCAPS_SKU message

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciGetFwFeatureStateMsg (
  OUT MEFWCAPS_SKU                *RuleData
  );

/**
  This message is sent by the BIOS or IntelR MEBX. One of usages is to utilize
  this command to determine if the platform runs in Consumer or Corporate SKU
  size firmware.

  @param[in] RuleData             PlatformBrand,
                                  IntelMeFwImageType,
                                  SuperSku,
                                  PlatformTargetUsageType

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciGetPlatformTypeMsg (
  OUT PLATFORM_TYPE_RULE_DATA     *RuleData
  );

/**
  Send Host Reset Notification Message to determine if warm reset is required.

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciSendHostResetNotificationMsg (
  VOID
  );

/**
  Send Core BIOS Reset Request Message through HECI to reset the system.

  @param[in] ResetOrigin         Reset source
  @param[in] ResetType           Global or Host reset

  @retval EFI_UNSUPPORTED        Current ME mode doesn't support this function
  @retval EFI_SUCCESS            Command succeeded
  @retval EFI_NOT_FOUND          No ME present
  @retval EFI_DEVICE_ERROR       HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT            HECI does not return the buffer before timeout
**/
EFI_STATUS
PeiHeciSendCbmResetRequest (
  IN  UINT8                      ResetOrigin,
  IN  UINT8                      ResetType
  );

/**
  This message is sent by the BIOS in PEI phase to query
  ME Unconfig on RTC Clear Disable state.

  @param[out] RuleData            1 - Unconfig on RTC clear is disabled
                                  0 - Unconfig on RTC clear is enabled

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciGetUnconfigOnRtcClearDisableMsg (
  OUT UINT32                *RuleData
  );

/**
  This message is sent by the BIOS in PEI phase to set
  ME Unconfig on RTC Clear Disable state.

  @param[in] RuleData             1 - Disable Unconfig on RTC clear
                                  0 - Enable Unconfig on RTC clear

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function or EOP was sent
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciSetUnconfigOnRtcClearDisableMsg (
  IN UINT32                RuleData
  );

//
// Prototype for ME Policy PEI phase
//

/**
  Read the ME policy to see if HECI timeouts are enabled.

  @retval TRUE             Timeout is enabled
  @retval FALSE            Timeout is disabled
**/
BOOLEAN
MeHeciTimeoutsEnabled (
  VOID
  );

/**
  Check if HECI2 should be removed from PCI space or not

  @retval FALSE                   HECI2 should be Disabled and removed from PCI space
  @retval TRUE                    HECI2 should be enabled and not removed from PCI space
**/
BOOLEAN
MeHeci2Enabled (
  VOID
  );

/**
  Read the ME policy to see if HECI retry is enabled.

  @retval TRUE             HECI retry is enabled
  @retval FALSE            HECI retry is disabled
**/
BOOLEAN
MeHeciRetryEnabled (
  VOID
  );

/**
  Read the ME policy to see if HECI message check is enabled for Bios Boot Path.

  @retval TRUE             HECI message check is enabled
  @retval FALSE            HECI message check is disabled
**/
BOOLEAN
MeHeciMessageCheckEnabled (
  VOID
  );

/**
  Read the ME policy to see if MBP HOB is skipped.

  @retval TRUE             MBP HOB is skipped
  @retval FALSE            MBP HOB is not skipped
**/
BOOLEAN
MeMbpHobSkipped (
  VOID
  );

/**
  Get default Heci1 BAR address from policy.

  @param[in] MeDev         The ME device to be accessed.

  @retval                  32-bit BAR address
**/
UINT32
MeGetHeciBarAddress (
  IN ME_DEVICE             MeDev
  );

/**
  Read the ME policy to see if D0I3 for HECI devices are enabled.

  @retval TRUE             D0I3 for HECI devices are enabled
  @retval FALSE            D0I3 for HECI devices are disabled
**/
BOOLEAN
MeHeciD0I3Enabled (
  VOID
  );

/**
  Check if End of Post Message is enabled in setup options.

  @retval FALSE                   EndOfPost is disabled.
  @retval TRUE                    EndOfPost is enabled.
**/
BOOLEAN
MeEndOfPostEnabled (
  VOID
  );

/**
  Checks if EndOfPost event already happened

  @retval TRUE                    End of post already happened
  @retval FALSE                   End of post did not happen yet
**/
BOOLEAN
MeIsAfterEndOfPost (
  VOID
  );

/**
  Set EndOfPost done
**/
VOID
MeSetEndOfPostDone (
  VOID
  );

/**
  Retrieves information on whether Pcie root port configuration SoftStrap override is being done or not

  @param[in]      NumberOfControllers    On input, it is the number of controllers caller expects.

  @param[in, out] ControllerConfig       Pointer to the controller config message.

  @retval EFI_SUCCESS                   Command succeeded
  @retval EFI_DEVICE_ERROR              HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT                   HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL          Message Buffer is too small for the Acknowledge
  @retval EFI_UNSUPPORTED               Current ME mode doesn't support send this message through this HECI
  @retval EFI_OUT_OF_RESOURCES          Unable to allocate required resources
**/
EFI_STATUS
PeiHeciGetSoftStrpConfigMsg (
  IN      UINT16     NumberOfControllers,
  IN OUT  UINT8      *ControllerConfig
  );

/**
  Set Pcie Root port configuration SoftStrap override for the specified Pcie Root Port controller

  @param[in] NumberOfControllers         On input, it is the number of controllers caller expects.
  @param[in] ConfigIndex                 RpIndex where TG is present and softstraps need to be overridden, if Invalid number (0xFF) then clear the override
  @param[in] OverrideIndex               Config override index, Please refer to PCIE_CONTROLLER_SOFTSTRAP_OVERRIDE

  @retval EFI_SUCCESS                    Command succeeded
  @retval EFI_DEVICE_ERROR               HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT                    HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL           Message Buffer is too small for the Acknowledge
  @retval EFI_UNSUPPORTED                Current ME mode doesn't support send this message through this HECI
  @retval EFI_OUT_OF_RESOURCES           Unable to allocate required resources
**/
EFI_STATUS
PeiHeciOverrideSoftStrapMsg (
  IN UINT16                                 NumberOfControllers,
  IN UINT8                                  ConfigIndex,
  IN PCIE_CONTROLLER_SOFTSTRAP_OVERRIDE     OverrideIndex
  );
#endif
