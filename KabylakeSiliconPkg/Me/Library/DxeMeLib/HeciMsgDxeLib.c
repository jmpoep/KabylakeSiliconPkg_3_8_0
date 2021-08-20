/** @file
  Implementation file for Heci Message functionality

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2018 Intel Corporation.

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

#include "MeDxeLibInternals.h"

#define ME_STATE_STALL_1_SECOND 1000000
#define MSG_MAX_WAIT_TIMEOUT    5
#define FW_INIT_DONE_TIMEOUT    15

//
// Interface functions of HeciMsgLib
//

//
// ME Client - ISH Service
//

/**
  This message is sent by the BIOS when it wants to send
  PDT Unlock Message to ISH.

  @param[in] FileName             Filename of bios2ish file.

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function or EOP was sent
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
**/
EFI_STATUS
HeciPdtUnlockMsg (
  IN CONST CHAR8*                FileName
  )
{
  EFI_STATUS                                Status;
  UINT16                                    Length;
  PDT_UNLOCK                                PdtUnlock;
  UINT32                                    MeMode;
  HECI_PROTOCOL                             *Heci;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Length = sizeof (PDT_UNLOCK);

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  PdtUnlock.Command                      = ISH_SET_FILE_CMD;
  PdtUnlock.MessageLength                = Length - 4;
  PdtUnlock.NumberOfElements             = 0x1;
  PdtUnlock.Data.DataType                = PDT_UNLOCK_DATA_DATA_TYPE;
  PdtUnlock.Data.PayloadSize             = PDT_UNLOCK_DATA_PAYLOAD_SIZE;

  ASSERT (AsciiStrLen (FileName) <= (sizeof (PdtUnlock.FileName)));

  ZeroMem (&PdtUnlock.FileName, sizeof (PdtUnlock.FileName));
  CopyMem (&PdtUnlock.FileName, FileName, AsciiStrLen (FileName));

  Status = Heci->SendMsg (
                   HECI1_DEVICE,
                   (UINT32 *) &PdtUnlock,
                   Length,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_ISH_SERVICE_MESSAGE_ADDR
                   );

  return Status;
}

//
// ME Client - MKHI
//

//
// MKHI_CBM_GROUP_ID = 0x00
//

/**
  Send Core BIOS Reset Request Message through HECI to reset the system.

  @param[in] ResetOrigin          Reset source
  @param[in] ResetType            Global or Host reset

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
HeciSendCbmResetRequest (
  IN  UINT8                      ResetOrigin,
  IN  UINT8                      ResetType
  )
{
  HECI_PROTOCOL                  *Heci;
  EFI_STATUS                     Status;
  UINT32                         HeciLength;
  UINT32                         AckLength;
  CBM_RESET_REQ                  CbmResetRequest;
  PLATFORM_ME_HOOK_PROTOCOL      *PlatformMeHook;
  WDT_PROTOCOL                   *WdtProtocol;
  UINT32                         MeMode;
  UINT32                         Result;

  DEBUG ((DEBUG_INFO, "ME-BIOS: ME: Global Reset Request Entry.\n"));
  PostCode (0xE06);

  if (MeIsAfterEndOfPost ()) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: ME: Global Reset Request Exit - Error by message is not allowed.\n"));
    PostCode (0xE86);
    return EFI_UNSUPPORTED;
  }

  Status = gBS->LocateProtocol (
                  &gPlatformMeHookProtocolGuid,
                  NULL,
                  (VOID **) &PlatformMeHook
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "Unable to Locate PlatformMeHook Protocol for Global Reset Hook, so skip instead.- %r\n", Status));
  } else {
    PlatformMeHook->PreGlobalReset ();
  }

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: ME: Global Reset Request Exit - Error by HECI service not found.\n"));
    PostCode (0xEA6);
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: ME: Global Reset Request Exit - Error by message is not allowed.\n"));
    PostCode (0xE86);
    return EFI_UNSUPPORTED;
  }

  CbmResetRequest.MkhiHeader.Data               = 0;
  CbmResetRequest.MkhiHeader.Fields.Command     = CBM_RESET_CMD;
  CbmResetRequest.MkhiHeader.Fields.IsResponse  = 0;
  CbmResetRequest.MkhiHeader.Fields.GroupId     = MKHI_CBM_GROUP_ID;
  CbmResetRequest.MkhiHeader.Fields.Reserved    = 0;
  CbmResetRequest.MkhiHeader.Fields.Result      = 0;
  CbmResetRequest.Data.RequestOrigin            = ResetOrigin;
  CbmResetRequest.Data.ResetType                = ResetType;

  HeciLength = sizeof (CBM_RESET_REQ);
  AckLength = sizeof (CBM_RESET_ACK);

  Status = gBS->LocateProtocol (&gWdtProtocolGuid, NULL, (VOID **) &WdtProtocol);
  ASSERT_EFI_ERROR (Status);
  WdtProtocol->AllowKnownReset ();

  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &CbmResetRequest,
                   HeciLength,
                   &AckLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Unable to Send Reset Request - %r\n", Status));
    DEBUG ((DEBUG_ERROR, "ME-BIOS: ME: Global Reset Request Exit - Error by message sent fail.\n"));
    PostCode (0xEC6);
    return Status;
  }

  Result = ((CBM_RESET_ACK*)&CbmResetRequest)->MkhiHeader.Fields.Result;
  if (Result != 0) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: ME: Global Reset Request Exit - Error by message ack error. Result: %x\n", Result));
    Status = EFI_DEVICE_ERROR;
    PostCode (0xEE6);
  } else {
    DEBUG ((DEBUG_INFO, "ME-BIOS: ME: Global Reset Request Exit - Success.\n"));
    PostCode (0xE26);
  }

  return Status;
}

//
// MKHI_FWCAPS_GROUP_ID = 0x03
//

/**
  Send Get Firmware SKU Request to ME

  @param[in, out] *FwCapsSku        Firmware Capabilities

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
HeciGetFwCapsSkuMsg (
  IN OUT MEFWCAPS_SKU             *FwCapsSku
  )
{
  EFI_STATUS                      Status;
  GET_FW_CAPS_SKU_BUFFER          GetFwCapsSku;
  UINT32                          Length;
  UINT32                          RecvLength;
  HECI_PROTOCOL                   *Heci;
  UINT32                          MeMode;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  GetFwCapsSku.Request.MkhiHeader.Data               = 0;
  GetFwCapsSku.Request.MkhiHeader.Fields.GroupId     = MKHI_FWCAPS_GROUP_ID;
  GetFwCapsSku.Request.MkhiHeader.Fields.Command     = FWCAPS_GET_RULE_CMD;
  GetFwCapsSku.Request.MkhiHeader.Fields.IsResponse  = 0;
  GetFwCapsSku.Request.Data.RuleId                   = FW_CAPS_RULE_ID;
  Length                                             = sizeof (GET_FW_CAPSKU);
  RecvLength                                         = sizeof (GET_FW_CAPS_SKU_ACK);

  ///
  /// Send Get FW SKU Request to ME
  ///
  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &GetFwCapsSku,
                   Length,
                   &RecvLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  if (!EFI_ERROR (Status) && ((GetFwCapsSku.Response.MkhiHeader.Fields.Command) == FWCAPS_GET_RULE_CMD) &&
      ((GetFwCapsSku.Response.MkhiHeader.Fields.IsResponse) == 1) &&
      (GetFwCapsSku.Response.MkhiHeader.Fields.Result == 0)
      ) {
    *FwCapsSku = GetFwCapsSku.Response.Data.FWCapSku;
  }

  return Status;
}

/**
  This message is sent by the BIOS or IntelR MEBX prior to the End of Post (EOP) on the boot
  where host wants to query the local firmware update interface status.

  @param[out] RuleData            1 - local firmware update interface enable
                                  0 - local firmware update interface disable

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
HeciGetLocalFwUpdate (
  OUT UINT8                       *RuleData
  )
{
  EFI_STATUS                      Status;
  UINT32                          Length;
  UINT32                          RecvLength;
  HECI_PROTOCOL                   *Heci;
  GET_LOCAL_FW_UPDATE_ACK         GetLocalFwUpdate;
  UINT32                          MeMode;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  GetLocalFwUpdate.MkhiHeader.Data              = 0;
  GetLocalFwUpdate.MkhiHeader.Fields.GroupId    = MKHI_FWCAPS_GROUP_ID;
  GetLocalFwUpdate.MkhiHeader.Fields.Command    = FWCAPS_GET_RULE_CMD;
  GetLocalFwUpdate.MkhiHeader.Fields.IsResponse = 0;
  GetLocalFwUpdate.Data.RuleId                  = LOCAL_FW_UPDATE_RULE_ID;
  Length                                        = sizeof (GET_LOCAL_FW_UPDATE);
  RecvLength                                    = sizeof (GET_LOCAL_FW_UPDATE_ACK) - LOCAL_FW_UPDATE_RSVD_LENGTH;

  ///
  /// Send Get Local FW update Request to ME
  ///
  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &GetLocalFwUpdate,
                   Length,
                   &RecvLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  if (!EFI_ERROR (Status)) {
    *RuleData = (UINT8)GetLocalFwUpdate.Data.RuleData;
  }

  return Status;
}

/**
  This message is sent by the BIOS or IntelR MEBX prior to the End of Post (EOP) on the boot
  where host wants to enable or disable the local firmware update interface.
  The firmware allows a single update once it receives the enable command

  @param[in] RuleData             1 - local firmware update interface enable
                                  0 - local firmware update interface disable

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
HeciSetLocalFwUpdate (
  IN UINT8                        RuleData
  )
{
  EFI_STATUS                      Status;
  UINT32                          Length;
  UINT32                          RecvLength;
  HECI_PROTOCOL                   *Heci;
  SET_LOCAL_FW_UPDATE             SetLocalFwUpdate;
  UINT32                          MeMode;

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  SetLocalFwUpdate.MkhiHeader.Data              = 0;
  SetLocalFwUpdate.MkhiHeader.Fields.GroupId    = MKHI_FWCAPS_GROUP_ID;
  SetLocalFwUpdate.MkhiHeader.Fields.Command    = FWCAPS_SET_RULE_CMD;
  SetLocalFwUpdate.MkhiHeader.Fields.IsResponse = 0;
  SetLocalFwUpdate.Data.RuleId                  = LOCAL_FW_UPDATE_RULE_ID;
  SetLocalFwUpdate.Data.RuleDataLen             = LOCAL_FW_UPDATE_RULE_DATA_LENGTH;
  SetLocalFwUpdate.Data.RuleData                = RuleData;
  Length                                        = sizeof (SET_LOCAL_FW_UPDATE) - LOCAL_FW_UPDATE_RSVD_LENGTH;
  RecvLength                                    = sizeof (SET_LOCAL_FW_UPDATE_ACK);

  ///
  /// Send Get Local FW update Request to ME
  ///
  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &SetLocalFwUpdate,
                   Length,
                   &RecvLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );

  return Status;
}

/**
  This message is sent by the BIOS or IntelR MEBX prior to the End of Post (EOP)
  on the boot where host wants to get Ibex Peak platform type.
  One of usages is to utilize this command to determine if the platform runs in
  Consumer or Corporate SKU size firmware.

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
HeciGetPlatformTypeMsg (
  OUT PLATFORM_TYPE_RULE_DATA     *RuleData
  )
{
  EFI_STATUS                      Status;
  UINT32                          Length;
  UINT32                          RecvLength;
  HECI_PROTOCOL                   *Heci;
  GET_PLATFORM_TYPE_BUFFER        GetPlatformType;
  UINT32                          MeMode;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  GetPlatformType.Request.MkhiHeader.Data               = 0;
  GetPlatformType.Request.MkhiHeader.Fields.GroupId     = MKHI_FWCAPS_GROUP_ID;
  GetPlatformType.Request.MkhiHeader.Fields.Command     = FWCAPS_GET_RULE_CMD;
  GetPlatformType.Request.MkhiHeader.Fields.IsResponse  = 0;
  GetPlatformType.Request.Data.RuleId                   = PLATFORM_TYPE_RULE_ID;
  Length                                                = sizeof (GET_PLATFORM_TYPE);
  RecvLength                                            = sizeof (GET_PLATFORM_TYPE_ACK);

  ///
  /// Send Get Platform Type Request to ME
  ///
  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &GetPlatformType,
                   Length,
                   &RecvLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  if (!EFI_ERROR (Status)) {
    *RuleData = GetPlatformType.Response.Data.RuleData;
  }

  return Status;
}

/**
  This message is sent by the BIOS on the boot where the host wants to get the firmware provisioning state.
  The firmware will respond to AMT BIOS SYNCH INFO message even after the End of Post.

  @param[out] RuleData            Bit [2:0] Reserved
                                  Bit [4:3] Provisioning State
                                    00 - Pre -provisioning
                                    01 - In -provisioning
                                    02 - Post !Vprovisioning
                                  Bit [31:5] Reserved

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
HeciAmtBiosSynchInfo (
  OUT UINT32                      *RuleData
  )
{
  EFI_STATUS                      Status;
  UINT32                          Length;
  UINT32                          RecvLength;
  HECI_PROTOCOL                   *Heci;
  AMT_BIOS_SYNCH_INFO_ACK         AmtBiosSynchInfo;
  UINT32                          MeMode;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  AmtBiosSynchInfo.MkhiHeader.Data              = 0;
  AmtBiosSynchInfo.MkhiHeader.Fields.GroupId    = MKHI_FWCAPS_GROUP_ID;
  AmtBiosSynchInfo.MkhiHeader.Fields.Command    = FWCAPS_GET_RULE_CMD;
  AmtBiosSynchInfo.MkhiHeader.Fields.IsResponse = 0;
  AmtBiosSynchInfo.RuleId                       = AMT_BIOS_SYNC_INFO_RULE_ID;
  Length                                        = sizeof (AMT_BIOS_SYNCH_INFO);
  RecvLength                                    = sizeof (AMT_BIOS_SYNCH_INFO_ACK);

  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &AmtBiosSynchInfo,
                   Length,
                   &RecvLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  if (!EFI_ERROR (Status)) {
    *RuleData = AmtBiosSynchInfo.RuleData;
  }

  return Status;
}

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
HeciGetFwFeatureStateMsg (
  OUT MEFWCAPS_SKU                *RuleData
  )
{
  EFI_STATUS                      Status;
  UINT32                          Length;
  UINT32                          RecvLength;
  GET_FW_FEATURE_STATUS_ACK       GetFwFeatureStatus;
  UINT32                          MeMode;
  HECI_PROTOCOL                   *Heci;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  GetFwFeatureStatus.MkhiHeader.Data              = 0;
  GetFwFeatureStatus.MkhiHeader.Fields.GroupId    = MKHI_FWCAPS_GROUP_ID;
  GetFwFeatureStatus.MkhiHeader.Fields.Command    = FWCAPS_GET_RULE_CMD;
  GetFwFeatureStatus.MkhiHeader.Fields.IsResponse = 0;
  GetFwFeatureStatus.RuleId                       = FW_FEATURE_STATE_RULE_ID;
  Length                                          = sizeof (GET_FW_FEATURE_STATUS);
  RecvLength                                      = sizeof (GET_FW_FEATURE_STATUS_ACK);

  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &GetFwFeatureStatus,
                   Length,
                   &RecvLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );

  if (!EFI_ERROR (Status)) {
    RuleData->Data = GetFwFeatureStatus.RuleData.Data;
  }

  return Status;
}

/**
  The firmware will respond to GET OEM TAG message even after the End of Post (EOP).

  @param[in] RuleData             Default is zero. Tool can create the OEM specific OEM TAG data.

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
HeciGetOemTagMsg (
  OUT UINT32                      *RuleData
  )
{
  EFI_STATUS                      Status;
  UINT32                          Length;
  UINT32                          RecvLength;
  HECI_PROTOCOL                   *Heci;
  GET_OEM_TAG_ACK                 GetOemTag;
  UINT32                          MeMode;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  GetOemTag.MkhiHeader.Data                = 0;
  GetOemTag.MkhiHeader.Fields.GroupId      = MKHI_FWCAPS_GROUP_ID;
  GetOemTag.MkhiHeader.Fields.Command      = FWCAPS_GET_RULE_CMD;
  GetOemTag.MkhiHeader.Fields.IsResponse   = 0;
  GetOemTag.RuleId                         = OEM_TAG_RULE_ID;
  Length                                   = sizeof (GET_OEM_TAG);
  RecvLength                               = sizeof (GET_OEM_TAG_ACK);

  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &GetOemTag,
                   Length,
                   &RecvLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  if (!EFI_ERROR (Status)) {
    *RuleData = GetOemTag.RuleData;
  }

  return Status;
}

/**
  This message is sent by the BIOS or IntelR MEBX prior to the End of Post (EOP)
  on the boot where host wants to disable the ME State. The firmware allows a single
  update once it receives the disable command Once firmware receives this message,
  the firmware will work in "Soft Temporary Disable" mode (HFS[19:16] = 3) after a
  global reset. Note, this message is not allowed when AT firmware is enrolled/configured.

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             ME is disabled
**/
EFI_STATUS
HeciSetMeDisableMsg (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINT32                          Length;
  HECI_PROTOCOL                   *Heci;
  SET_FW_CAPSKU                   MeStateControl;
  UINT32                          MeMode;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (MeMode == ME_MODE_TEMP_DISABLED) {
    return EFI_SUCCESS;
  }

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  MeStateControl.MkhiHeader.Data               = 0;
  MeStateControl.MkhiHeader.Fields.GroupId     = MKHI_FWCAPS_GROUP_ID;
  MeStateControl.MkhiHeader.Fields.Command     = FWCAPS_SET_RULE_CMD;
  MeStateControl.MkhiHeader.Fields.IsResponse  = 0;
  MeStateControl.Data.RuleId.Data              = ME_PLATFORM_STATUS_RULE_ID;
  MeStateControl.Data.RuleDataLen              = 1;
  MeStateControl.Data.RuleData                 = 0;

  Length = sizeof (SET_FW_CAPSKU);

  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &MeStateControl,
                   Length,
                   &Length,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  return Status;
}

/**
  This message is sent by the BIOS to inform ME FW whether or not to take the
  TPM 1.2 Deactivate flow

  @param[in] UINT8 TpmDeactivate  0 - ME FW should not take the
                                      deactivate flow.
                                  1 - ME FW should take the deactivate
                                      flow.

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             HECI interfaces disabled by ME
**/
EFI_STATUS
HeciSendTpmData (
  IN UINT8               TpmDeactivate
  )
{
  EFI_STATUS             Status;
  UINT32                 HeciSendLength;
  UINT32                 HeciRecvLength;
  HECI_PROTOCOL          *Heci;
  BIOSNV_SET_ACM_TPM     SetAcmTpm;

  DEBUG ((DEBUG_INFO, "HeciSendTpmData Message.  TpmDeactivate Setup Data = %d\n", TpmDeactivate));

  ZeroMem (&SetAcmTpm, sizeof (BIOSNV_SET_ACM_TPM));

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  SetAcmTpm.MkhiHeader.Data                          = 0;
  SetAcmTpm.MkhiHeader.Fields.GroupId                = MKHI_FWCAPS_GROUP_ID;
  SetAcmTpm.MkhiHeader.Fields.Command                = FWCAPS_SET_RULE_CMD;
  SetAcmTpm.MkhiHeader.Fields.IsResponse             = 0;
  SetAcmTpm.AcmTpmData.RuleId.Fields.RuleTypeId      = ACM_TPM_DATA_RULE_ID;
  SetAcmTpm.AcmTpmData.RuleDataLen                   = ACM_TPM_DATA_RULE_DATA_LENGTH;
  SetAcmTpm.AcmTpmData.TpmState.Fields.TpmDeactivate = FALSE;

  if (TpmDeactivate == 1) {
    SetAcmTpm.AcmTpmData.TpmState.Fields.TpmDeactivate = TRUE;
  }

  //
  // Send Set ACM TPM Data MKHI message
  //
  HeciSendLength = sizeof (BIOSNV_SET_ACM_TPM);
  HeciRecvLength = sizeof (BIOSNV_SET_ACM_TPM_ACK);

  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &SetAcmTpm,
                   HeciSendLength,
                   &HeciRecvLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );

  return Status;
}

/**
  This message is sent by the BIOS when it wants to query
  ME Unconfig on RTC Clear Disable state.

  @param[out] RuleData            1 - Unconfig on RTC clear is disabled
                                  0 - Unconfig on RTC clear is not disabled

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
HeciGetUnconfigOnRtcClearDisableMsg (
  OUT UINT32                *RuleData
  )
{
  EFI_STATUS                                Status;
  UINT32                                    Length;
  UINT32                                    RespLength;
  ME_GET_UNCONFIG_ON_RTC_CLEAR_STATE_BUFFER GetMeUnconfigOnRtcClearState;
  UINT32                                    MeMode;
  HECI_PROTOCOL                             *Heci;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  GetMeUnconfigOnRtcClearState.Request.MkhiHeader.Data              = 0;
  GetMeUnconfigOnRtcClearState.Request.MkhiHeader.Fields.GroupId    = MKHI_FWCAPS_GROUP_ID;
  GetMeUnconfigOnRtcClearState.Request.MkhiHeader.Fields.Command    = FWCAPS_GET_RULE_CMD;
  GetMeUnconfigOnRtcClearState.Request.MkhiHeader.Fields.IsResponse = 0;
  GetMeUnconfigOnRtcClearState.Request.Data.RuleId                  = UNCONFIG_ON_RTC_CLEAR_RULE_ID;

  Length = sizeof (ME_GET_UNCONFIG_ON_RTC_CLEAR_STATE);
  RespLength = sizeof (ME_GET_UNCONFIG_ON_RTC_CLEAR_STATE_ACK);

  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &GetMeUnconfigOnRtcClearState,
                   Length,
                   &RespLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  *RuleData = GetMeUnconfigOnRtcClearState.Response.Data.RuleData;

  return Status;
}


/**
  This message is sent by the BIOS when it wants to set
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
HeciSetUnconfigOnRtcClearDisableMsg (
  IN UINT32                RuleData
  )
{
  EFI_STATUS                                Status;
  UINT32                                    Length;
  UINT32                                    RespLength;
  ME_SET_UNCONFIG_ON_RTC_CLEAR_STATE_BUFFER SetMeUnconfigOnRtcClearState;
  UINT32                                    MeMode;
  HECI_PROTOCOL                             *Heci;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  SetMeUnconfigOnRtcClearState.Request.MkhiHeader.Data              = 0;
  SetMeUnconfigOnRtcClearState.Request.MkhiHeader.Fields.GroupId    = MKHI_FWCAPS_GROUP_ID;
  SetMeUnconfigOnRtcClearState.Request.MkhiHeader.Fields.Command    = FWCAPS_SET_RULE_CMD;
  SetMeUnconfigOnRtcClearState.Request.MkhiHeader.Fields.IsResponse = 0;
  SetMeUnconfigOnRtcClearState.Request.Data.RuleId                  = UNCONFIG_ON_RTC_CLEAR_RULE_ID;
  SetMeUnconfigOnRtcClearState.Request.Data.RuleDataLen             = 4;
  SetMeUnconfigOnRtcClearState.Request.Data.RuleData                = RuleData;

  Length = sizeof (ME_SET_UNCONFIG_ON_RTC_CLEAR_STATE);
  RespLength = sizeof (ME_SET_UNCONFIG_ON_RTC_CLEAR_STATE_ACK);
  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &SetMeUnconfigOnRtcClearState,
                   Length,
                   &RespLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );

  return Status;
}

//
// MKHI_HMRFPO_GROUP_ID = 0x05
//

/**
  Sends a message to ME to unlock a specified SPI Flash region for writing and receiving a response message.
  It is recommended that HMRFPO_ENABLE MEI message needs to be sent after all OROMs finish their initialization.

  @param[in] Nonce                Nonce received in previous HMRFPO_ENABLE Response Message
  @param[in] Result               HMRFPO_ENABLE response

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
HeciHmrfpoEnable (
  IN  UINT64                      Nonce,
  OUT UINT8                       *Result
  )
{
  EFI_STATUS                      Status;
  HECI_PROTOCOL                   *Heci;
  HMRFPO_ENABLE                   HmrfpoEnableRequest;
  HMRFPO_ENABLE_RESPONSE          HmrfpoEnableResponse;
  UINT32                          HeciLength;
  UINT32                          MeMode;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  HmrfpoEnableRequest.MkhiHeader.Data               = 0;
  HmrfpoEnableRequest.MkhiHeader.Fields.GroupId     = MKHI_HMRFPO_GROUP_ID;
  HmrfpoEnableRequest.MkhiHeader.Fields.Command     = HMRFPO_ENABLE_CMD_ID;
  HmrfpoEnableRequest.MkhiHeader.Fields.IsResponse  = 0;
  HmrfpoEnableRequest.Nonce                         = Nonce;

  HeciLength = sizeof (HMRFPO_ENABLE);

  Status = Heci->SendMsg (
                   HECI1_DEVICE,
                   (UINT32 *) &HmrfpoEnableRequest,
                   HeciLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Unable to Send HMRFPO_ENABLE_CMD_ID Request - %r\n", Status));
    return Status;
  }

  HeciLength = sizeof (HMRFPO_ENABLE_RESPONSE);
  Status = Heci->ReadMsg (
                   HECI1_DEVICE,
                   BLOCKING,
                   (UINT32 *) &HmrfpoEnableResponse,
                   &HeciLength
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Unable to Read HMRFPO_ENABLE_CMD_ID Result - %r\n", Status));
    return Status;
  }

  *Result = HmrfpoEnableResponse.Status;

  return Status;
}

/**
  Sends a message to ME to lock a specified SPI Flash region for writing and receiving a response message.

  @param[out] Nonce               Random number generated by Ignition ME FW. When BIOS
                                  wants to unlock region it should use this value
                                  in HMRFPO_ENABLE Request Message
  @param[out] FactoryDefaultBase  The base of the factory default calculated from the start of the ME region.
                                  BIOS sets a Protected Range (PR) register!?s "Protected Range Base" field with this value
                                  + the base address of the region.
  @param[out] FactoryDefaultLimit The length of the factory image.
                                  BIOS sets a Protected Range (PR) register!?s "Protected Range Limit" field with this value
  @param[out] Result              Status report

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_NOT_READY           HECI Device hasn't ready yet
**/
EFI_STATUS
HeciHmrfpoLock (
  OUT UINT64                      *Nonce,
  OUT UINT32                      *FactoryDefaultBase,
  OUT UINT32                      *FactoryDefaultLimit,
  OUT UINT8                       *Result
  )
{
  EFI_STATUS                      Status;
  HECI_PROTOCOL                   *Heci;
  HMRFPO_LOCK                     HmrfpoLockRequest;
  HMRFPO_LOCK_RESPONSE            HmrfpoLockResponse;
  UINT32                          HeciLength;
  UINT32                          MeMode;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  HmrfpoLockRequest.MkhiHeader.Data               = 0;
  HmrfpoLockRequest.MkhiHeader.Fields.GroupId     = MKHI_HMRFPO_GROUP_ID;
  HmrfpoLockRequest.MkhiHeader.Fields.Command     = HMRFPO_LOCK_CMD_ID;
  HmrfpoLockRequest.MkhiHeader.Fields.IsResponse  = 0;

  HeciLength = sizeof (HMRFPO_LOCK);

  Status = Heci->SendMsg (
                   HECI1_DEVICE,
                   (UINT32 *) &HmrfpoLockRequest,
                   HeciLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Unable to Send HMRFPO_LOCK_CMD_ID Request - %r\n", Status));
    return Status;
  }

  HeciLength = sizeof (HMRFPO_LOCK_RESPONSE);
  Status = Heci->ReadMsg (
                   HECI1_DEVICE,
                   BLOCKING,
                   (UINT32 *) &HmrfpoLockResponse,
                   &HeciLength
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Unable to read HMRFPO_LOCK_CMD_ID response - %r.\n", Status));
    return Status;
  }

  *Nonce                = HmrfpoLockResponse.Nonce;
  *FactoryDefaultBase   = HmrfpoLockResponse.FactoryDefaultBase;
  *FactoryDefaultLimit  = HmrfpoLockResponse.FactoryDefaultLimit;
  *Result               = HmrfpoLockResponse.Status;

  return Status;
}

/**
  System BIOS sends this message to get status for HMRFPO_LOCK message.

  @param[out] Result              HMRFPO_GET_STATUS response

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
HeciHmrfpoGetStatus (
  OUT UINT8                       *Result
  )
{
  EFI_STATUS                      Status;
  HECI_PROTOCOL                   *Heci;
  HMRFPO_GET_STATUS               HmrfpoGetStatusRequest;
  HMRFPO_GET_STATUS_RESPONSE      HmrfpoGetStatusResponse;
  UINT32                          HeciLength;
  UINT32                          MeMode;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  HmrfpoGetStatusRequest.MkhiHeader.Data              = 0;
  HmrfpoGetStatusRequest.MkhiHeader.Fields.GroupId    = MKHI_HMRFPO_GROUP_ID;
  HmrfpoGetStatusRequest.MkhiHeader.Fields.Command    = HMRFPO_GET_STATUS_CMD_ID;
  HmrfpoGetStatusRequest.MkhiHeader.Fields.IsResponse = 0;

  HeciLength = sizeof (HMRFPO_GET_STATUS);

  Status = Heci->SendMsg (
                   HECI1_DEVICE,
                   (UINT32 *) &HmrfpoGetStatusRequest,
                   HeciLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Unable to Send HMRFPO_GET_STATUS_CMD_ID - %r\n", Status));
    return Status;
  }

  HeciLength = sizeof (HMRFPO_GET_STATUS_RESPONSE);
  Status = Heci->ReadMsg (
                   HECI1_DEVICE,
                   BLOCKING,
                   (UINT32 *) &HmrfpoGetStatusResponse,
                   &HeciLength
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Unable to Read HMRFPO_GET_STATUS_CMD_ID Result - %r\n", Status));
  }

  *Result = HmrfpoGetStatusResponse.Status;

  return Status;
}

//
// MKHI_MCA_GROUP_ID = 0x0A
//

/**
  This message is sent by the BIOS when it wants to notify that the BIOS is starting
  to run 3rd party code.

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function or EOP was sent
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
**/
EFI_STATUS
HeciCoreBiosDoneMsg (
  VOID
  )
{
  EFI_STATUS                                Status;
  UINT32                                    Length;
  UINT32                                    RespLength;
  CORE_BIOS_DONE                            CoreBiosDone;
  UINT32                                    MeMode;
  HECI_PROTOCOL                             *Heci;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Length = sizeof (CORE_BIOS_DONE);
  RespLength = sizeof (CORE_BIOS_DONE_ACK);

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  CoreBiosDone.MkhiHeader.Data              = 0;
  CoreBiosDone.MkhiHeader.Fields.GroupId    = MKHI_MCA_GROUP_ID;
  CoreBiosDone.MkhiHeader.Fields.Command    = MCA_CORE_BIOS_DONE_CMD;
  CoreBiosDone.MkhiHeader.Fields.IsResponse = 0;

  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &CoreBiosDone,
                   Length,
                   &RespLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );

  return Status;
}


//
// MKHI_GEN_GROUP_ID = 0xF0
//

/**
  This message is sent by the BIOS or IntelR MEBX prior to the End of Post (EOP)
  on the boot where host wants to enable the ME State. The firmware allows a single
  update once it receives the enable command. Once firmware receives this message,
  the firmware will be in normal mode after a global reset.

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_TIMEOUT             Timeout has occured
  @retval EFI_SUCCESS             ME enabled message sent
**/
EFI_STATUS
HeciSetMeEnableMsg (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINT32                          Length;
  UINT32                          RespLength;
  HECI_PROTOCOL                   *Heci;
  ME_ENABLE_CMD_REQ               MeEnableReq;
  UINT32                          MeMode;
  UINT32                          MeStatus;
  UINT8                           Timeout;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Heci->GetMeMode (&MeMode);
  if (MeMode == ME_MODE_NORMAL) {
    return EFI_SUCCESS;
  }

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  if (EFI_ERROR (Status) || (MeMode != ME_MODE_TEMP_DISABLED)) {
    return EFI_UNSUPPORTED;
  }

  MeEnableReq.MkhiHeader.Data               = 0;
  MeEnableReq.MkhiHeader.Fields.Command     = ME_ENABLE_CMD;
  MeEnableReq.MkhiHeader.Fields.IsResponse  = 0;
  MeEnableReq.MkhiHeader.Fields.GroupId     = BUP_COMMON_GROUP_ID;
  MeEnableReq.MkhiHeader.Fields.Reserved    = 0;
  MeEnableReq.MkhiHeader.Fields.Result      = 0;

  Length     = sizeof (ME_ENABLE_CMD_REQ);
  RespLength = sizeof (ME_ENABLE_CMD_RESP);

  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &MeEnableReq,
                   Length,
                   &RespLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  if (!EFI_ERROR (Status) && ((ME_ENABLE_CMD_RESP*)&MeEnableReq)->MkhiHeader.Fields.Result != 0) {
    //
    // Command succeeded but ME was not in disabled state
    //
    return EFI_UNSUPPORTED;
  }

  Timeout = FW_INIT_DONE_TIMEOUT;
  Heci->GetMeStatus (&MeStatus);
  while (!ME_STATUS_IS_ME_FW_INIT_COMPLETE (MeStatus)) {
    MicroSecondDelay (ME_STATE_STALL_1_SECOND);
    if (Timeout == 0) {
      Status = EFI_TIMEOUT;
      break;
    }
    Timeout--;
    Heci->GetMeStatus (&MeStatus);
  }

  return Status;
}

/**
  Send HMRFPO disable MKHI to CSME.

  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
HeciHmrfpoDisable (
  VOID
  )
{
  EFI_STATUS                  Status;
  HECI_PROTOCOL               *Heci;
  HMRFPO_DISABLE_CMD_REQ      HmrfpoDisableReq;
  UINT32                      Length;
  UINT32                      RespLength;
  UINT32                      MeMode;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  HmrfpoDisableReq.MkhiHeader.Data               = 0;
  HmrfpoDisableReq.MkhiHeader.Fields.Command     = HMRFPO_DISABLE_CMD;
  HmrfpoDisableReq.MkhiHeader.Fields.IsResponse  = 0;
  HmrfpoDisableReq.MkhiHeader.Fields.GroupId     = BUP_COMMON_GROUP_ID;
  HmrfpoDisableReq.MkhiHeader.Fields.Reserved    = 0;
  HmrfpoDisableReq.MkhiHeader.Fields.Result      = 0;

  Length     = sizeof (HMRFPO_DISABLE_CMD_REQ);
  RespLength = sizeof (HMRFPO_DISABLE_CMD_RESP);

  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &HmrfpoDisableReq,
                   Length,
                   &RespLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  if (!EFI_ERROR (Status) && ((HMRFPO_DISABLE_CMD_RESP*)&HmrfpoDisableReq)->MkhiHeader.Fields.Result != 0) {
    //
    // Command succeeded but ME is in wrong state to process it
    //
    DEBUG ((DEBUG_ERROR, "HMRFPO_DISABLE ACK returns unsuccessful result - %r\n", Status));
    Status = EFI_UNSUPPORTED;
  }

  return Status;
}

//
// MKHI_GEN_GROUP_ID = 0xFF
//

/**
  Send Get Firmware Version Request to ME

  @param[in, out] MsgGenGetFwVersionAck   Return the message of FW version

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
HeciGetFwVersionMsg (
  IN OUT GET_FW_VER_ACK_DATA      *GetFwVersionAckData
  )
{
  EFI_STATUS                      Status;
  GET_FW_VER_ACK                  GetFwVersion;
  UINT32                          Length;
  UINT32                          RecvLength;
  HECI_PROTOCOL                   *Heci;
  UINT32                          MeMode;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }
  ///
  /// Allocate MsgGenGetFwVersion data structure
  ///
  GetFwVersion.MkhiHeader.Data              = 0;
  GetFwVersion.MkhiHeader.Fields.GroupId    = MKHI_GEN_GROUP_ID;
  GetFwVersion.MkhiHeader.Fields.Command    = GEN_GET_FW_VERSION_CMD;
  GetFwVersion.MkhiHeader.Fields.IsResponse = 0;
  Length                                    = sizeof (GET_FW_VER);
  RecvLength                                = sizeof (GET_FW_VER_ACK);
  ///
  /// Send Get Firmware Version Request to ME
  ///
  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &GetFwVersion,
                   Length,
                   &RecvLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );
  if (!EFI_ERROR (Status) && (GetFwVersion.MkhiHeader.Fields.Command == GEN_GET_FW_VERSION_CMD) &&
      (GetFwVersion.MkhiHeader.Fields.IsResponse == 1) &&
      (GetFwVersion.MkhiHeader.Fields.Result == 0)
      ) {
    *GetFwVersionAckData = GetFwVersion.Data;
  }
  return Status;
}

/**
  Sends the MKHI Enable/Disable FW Features.

  @param[in] EnableBitMask        Bitmask of features to enable
  @param[in] DisableBitMask       Bitmask of features to disable

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
  @retval EFI_ACCESS_DENIED       Command request is rejected
**/
EFI_STATUS
HeciFwFeatureStateOverride (
  IN UINT32                       EnableBitmask,
  IN UINT32                       DisableBitmask
  )
{
  EFI_STATUS                                      Status;
  UINT32                                          Length;
  UINT32                                          RecvLength;
  UINT32                                          MeMode;
  FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_BUFFER  FwFeatureStateOverride;
  HECI_PROTOCOL                                   *Heci;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  FwFeatureStateOverride.Request.MkhiHeader.Data             = 0;
  FwFeatureStateOverride.Request.MkhiHeader.Fields.GroupId   = MKHI_GEN_GROUP_ID;
  FwFeatureStateOverride.Request.MkhiHeader.Fields.Command   = GEN_FW_FEATURE_STATE_OVERRIDE_CMD;
  FwFeatureStateOverride.Request.FeatureState.EnableFeature  = EnableBitmask;
  FwFeatureStateOverride.Request.FeatureState.DisableFeature = DisableBitmask;
  Length                                                     = sizeof (FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE);
  RecvLength                                                 = sizeof (FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_ACK);

  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &FwFeatureStateOverride,
                   Length,
                   &RecvLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );

  if (!EFI_ERROR (Status) && (FwFeatureStateOverride.Response.Status == SetFeatureStateRejected)) {
    Status = EFI_ACCESS_DENIED;
  }

  return Status;
}

/**
  Send Set Manufacturing Me Reset and Halt Request to ME

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
HeciSetManufacturingMeResetAndHalt (
  VOID
  )
{
  EFI_STATUS                      Status;
  SET_ME_RESET_HALT_ACK           SetMeResetAndHalt;
  UINT32                          HeciSendLength;
  HECI_PROTOCOL                   *Heci;
  UINT32                          MeMode;
  UINTN                           HeciBaseAddress;
  HECI_FWS_REGISTER               MeFirmwareStatus;
  UINTN                           TimeOut;

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  HeciBaseAddress = MmPciBase (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER);
  DEBUG ((DEBUG_INFO, "HeciSetManufacturingMeResetAndHalt: MeFirmwareStatus: %08x before messaging.\n", MmioRead32 (HeciBaseAddress + R_FWSTATE)));

  ///
  /// Allocate MsgGenSetMeResetAndHalt data structure
  ///
  SetMeResetAndHalt.MkhiHeader.Data              = 0;
  SetMeResetAndHalt.MkhiHeader.Fields.GroupId    = MKHI_GEN_GROUP_ID;
  SetMeResetAndHalt.MkhiHeader.Fields.Command    = GEN_SET_ME_RESET_HALT_CMD;
  SetMeResetAndHalt.MkhiHeader.Fields.IsResponse = 0;
  HeciSendLength                                 = sizeof (SET_ME_RESET_HALT);

  Status = Heci->SendMsg (
                   HECI1_DEVICE,
                   (UINT32 *) &SetMeResetAndHalt,
                   HeciSendLength,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_MKHI_MESSAGE_ADDR
                   );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  TimeOut = 0;
  while (1) {
    ///
    /// Read ME status and check for operation mode
    ///
    MeFirmwareStatus.ul = MmioRead32 (HeciBaseAddress + R_FWSTATE);
    if (MeFirmwareStatus.r.MeOperationMode == ME_OPERATION_MODE_SOFT_TEMP_DISABLE) {
      break;
    }

    MicroSecondDelay (ME_STATE_STALL_1_SECOND);
    TimeOut++;

    if (TimeOut >= MSG_MAX_WAIT_TIMEOUT) {
      DEBUG ((DEBUG_ERROR, "Timeout occur, MeFirmwareStatus: %08x.\n", MeFirmwareStatus.ul));
      return EFI_TIMEOUT;
    }
  }

  DEBUG ((DEBUG_INFO, "HeciSetManufacturingMeResetAndHalt succeeds.\n"));
  return EFI_SUCCESS;
}

//
// ME Client - Integrated Clock Chip (ICC)
//

/**
  Retrieves the current FW Register Lock State

  @param[out] LockState        FW Lock State (default, locked, unlocked)

  @retval EFI_UNSUPPORTED      Incorrect ME Mode
  @retval EFI_NOT_READY        Heci device hasn't ready yet
  @retval EFI_SUCCESS          Command succeeded
**/
EFI_STATUS
HeciGetIccRegLock (
  OUT UINT8                       *LockState
  )
{
  EFI_STATUS                      Status;
  ICC_GET_REG_LOCK_BUFFER         Buffer;
  UINT32                          CommandSize;
  UINT32                          ResponseSize;
  HECI_PROTOCOL                   *Heci;
  UINT32                          MeMode;
  UINT32                          MeStatus;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  Status = Heci->GetMeStatus (&MeStatus);
  if (EFI_ERROR (Status) || ((MeStatus & 0xF) != ME_READY)) {
    return EFI_NOT_READY;
  }

  CommandSize                         = sizeof (ICC_GET_REG_LOCK_MESSAGE);
  ResponseSize                        = sizeof (ICC_GET_REG_LOCK_RESPONSE);

  Buffer.message.Header.ApiVersion    = SKYLAKE_PCH_PLATFORM;
  Buffer.message.Header.IccCommand    = ICC_GET_REGISTERS_LOCK_CMD;
  Buffer.message.Header.IccResponse   = 0;
  Buffer.message.Header.BufferLength  = CommandSize - sizeof (ICC_HEADER);
  Buffer.message.Header.Reserved      = 0;

  PERF_START_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80D0);
  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &Buffer,
                   CommandSize,
                   &ResponseSize,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_ICC_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "(ICC) GetIccRegLock: Message failed! EFI_STATUS = %r\n", Status));
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80D2);
    return Status;
  }

  if (Buffer.response.Header.IccResponse != ICC_STATUS_SUCCESS) {
    DEBUG (
      (DEBUG_ERROR,
       "(ICC) GetIccRegLock: Wrong response! IccHeader.Response = %X\n",
       Buffer.response.Header.IccResponse)
      );
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80D3);
    Status = EFI_DEVICE_ERROR;
  } else {
    DEBUG ((DEBUG_INFO, "(ICC) GetIccRegLock: Current LockState = %X\n", Buffer.response.LockState));
  }

  if (LockState != NULL) {
    *LockState = Buffer.response.LockState;
    DEBUG ((DEBUG_INFO, "(ICC) GetIccRegLock: LockState = %X\n", *LockState));
  }

  PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80D1);

  return Status;
}

/**
  Sets ICC clock profile to be used on next and following boots

  @param[in] LockState            Requested FW LockState

  @retval EFI_UNSUPPORTED         Incorrect ME Mode/ After EOP
  @retval EFI_DEVICE_ERROR        Wrong response
  @retval EFI_NOT_READY           Heci device hasn't ready yet
  @retval EFI_SUCCESS             Command succeeded
**/
EFI_STATUS
HeciSetIccRegLock (
  IN UINT8                        LockState
  )
{
  EFI_STATUS                      Status;
  ICC_SET_REG_LOCK_BUFFER         Buffer;
  UINT32                          CommandSize;
  UINT32                          ResponseSize;
  HECI_PROTOCOL                   *Heci;
  UINT32                          MeMode;
  UINT32                          MeStatus;

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  Status = Heci->GetMeStatus (&MeStatus);
  if (EFI_ERROR (Status) || ((MeStatus & 0xF) != ME_READY)) {
    return EFI_NOT_READY;
  }

  DEBUG ((DEBUG_INFO, "(ICC) SetIccRegLock\n"));

  CommandSize                         = sizeof (ICC_SET_REG_LOCK_MESSAGE);
  ResponseSize                        = sizeof (ICC_SET_REG_LOCK_RESPONSE);

  Buffer.message.Header.ApiVersion    = SKYLAKE_PCH_PLATFORM;
  Buffer.message.Header.IccCommand    = ICC_SET_REGISTERS_LOCK_CMD;
  Buffer.message.Header.IccResponse   = 0;
  Buffer.message.Header.BufferLength  = CommandSize - sizeof (ICC_HEADER);
  Buffer.message.Header.Reserved      = 0;
  Buffer.message.LockState            = LockState;
  Buffer.message.PaddingA             = 0;
  Buffer.message.PaddingB             = 0;

  PERF_START_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80E0);
  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &Buffer,
                   CommandSize,
                   &ResponseSize,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_ICC_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(ICC) SetIccRegLock: Message failed! EFI_STATUS = %r\n", Status));
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80E2);
    return Status;
  }

  if (Buffer.response.Header.IccResponse != ICC_STATUS_SUCCESS) {
    DEBUG (
      (DEBUG_ERROR,
       "(ICC) SetIccRegLock: Wrong response! IccHeader.Response = 0x%x\n",
       Buffer.response.Header.IccResponse)
      );
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80E3);
    return EFI_DEVICE_ERROR;
  }

  PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80E1);

  return Status;
}

/**
  Retrieves the number of currently used ICC clock profile

  @param[out] Profile             Number of current ICC clock profile

  @retval EFI_UNSUPPORTED         ICC clock profile doesn't support
  @retval EFI_NOT_READY           Heci device hasn't ready yet
  @retval EFI_SUCCESS             Command succeeded
**/
EFI_STATUS
HeciGetIccProfile (
  OUT UINT8                       *Profile,
  OUT UINT8                       *NumProfiles,
  OUT ICC_PROFILE_DESC            *ProfileDescriptions
  )
{
  EFI_STATUS                      Status;
  ICC_GET_PROFILE_BUFFER          Buffer;
  UINT32                          CommandSize;
  UINT32                          ResponseSize;
  HECI_PROTOCOL                   *Heci;
  UINT32                          MeMode;
  UINT32                          MeStatus;

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  Status = Heci->GetMeStatus (&MeStatus);
  if (EFI_ERROR (Status) || ((MeStatus & 0xF) != ME_READY)) {
    return EFI_NOT_READY;
  }

  DEBUG ((DEBUG_INFO, "(ICC) GetIccProfile\n"));
  ///
  /// IccGetProfile response size will vary based on the amount of ICC profiles installed on the system.
  ///
  CommandSize = sizeof (ICC_GET_PROFILE_MESSAGE);
  ResponseSize = sizeof (ICC_GET_PROFILE_RESPONSE);

  Buffer.message.Header.ApiVersion    = SKYLAKE_PCH_PLATFORM;
  Buffer.message.Header.IccCommand    = ICC_GET_PROFILE_CMD;
  Buffer.message.Header.IccResponse   = 0;
  Buffer.message.Header.BufferLength  = CommandSize - sizeof (ICC_HEADER);
  Buffer.message.Header.Reserved      = 0;

  PERF_START_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80F0);
  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &Buffer,
                   CommandSize,
                   &ResponseSize,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_ICC_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(ICC) GetIccProfile: Message failed! EFI_STATUS = %r\n", Status));
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80F2);
    return Status;
  }

  if (Buffer.response.Header.IccResponse != ICC_STATUS_SUCCESS) {
    DEBUG (
      (DEBUG_ERROR,
       "(ICC) GetIccProfile: Wrong response! IccHeader.Response = 0x%x\n",
       Buffer.response.Header.IccResponse)
      );
    Status = EFI_DEVICE_ERROR;
  } else {
    DEBUG ((DEBUG_INFO, "(ICC) GetIccProfile: Current profile = 0x%x\n", Buffer.response.IccProfileIndex));
  }

  ///
  /// Copy ICC Profile information
  ///
  if (Profile != NULL) {
    *Profile = Buffer.response.IccProfileIndex;
  }

  if (NumProfiles != NULL) {
    *NumProfiles = Buffer.response.IccNumOfProfiles;
  }

  if (ProfileDescriptions != NULL) {
    CopyMem (ProfileDescriptions, Buffer.response.IccProfileDesc, sizeof (ICC_PROFILE_DESC)*MAX_NUM_ICC_PROFILES);
  }

  PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80F1);

  return Status;
}

/**
  Sets ICC clock profile to be used on next and following boots

  @param[in] Profile              Number of profile to be used

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_DEVICE_ERROR        Wrong response
  @retval EFI_NOT_READY           Heci device hasn't ready yet
  @retval EFI_SUCCESS             Command succeeded
**/
EFI_STATUS
HeciSetIccProfile (
  IN UINT8                        Profile
  )
{
  EFI_STATUS                      Status;
  ICC_SET_PROFILE_BUFFER          Buffer;
  UINT32                          CommandSize;
  UINT32                          ResponseSize;
  HECI_PROTOCOL                   *Heci;
  UINT32                          MeMode;
  UINT32                          MeStatus;

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  Status = Heci->GetMeStatus (&MeStatus);
  if (EFI_ERROR (Status) || ((MeStatus & 0xF) != ME_READY)) {
    return EFI_NOT_READY;
  }

  DEBUG ((DEBUG_INFO, "(ICC) SetIccProfile\n"));

  CommandSize                         = sizeof (ICC_SET_PROFILE_MESSAGE);
  ResponseSize                        = sizeof (ICC_SET_PROFILE_RESPONSE);

  Buffer.message.Header.ApiVersion    = SKYLAKE_PCH_PLATFORM;
  Buffer.message.Header.IccCommand    = ICC_SET_PROFILE_CMD;
  Buffer.message.Header.IccResponse   = 0;
  Buffer.message.Header.BufferLength  = CommandSize - sizeof (ICC_HEADER);
  Buffer.message.Header.Reserved      = 0;
  Buffer.message.BiosIccProfile       = Profile;
  Buffer.message.PaddingA             = 0;
  Buffer.message.PaddingB             = 0;

  PERF_START_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x8100);
  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &Buffer,
                   CommandSize,
                   &ResponseSize,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_ICC_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(ICC) SetIccProfile: Message failed! EFI_STATUS = %r\n", Status));
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x8102);
    return Status;
  }

  if (Buffer.response.Header.IccResponse != ICC_STATUS_SUCCESS) {
    DEBUG (
      (DEBUG_ERROR,
       "(ICC) SetIccProfile: Wrong response! IccHeader.Response = 0x%x\n",
       Buffer.response.Header.IccResponse)
      );
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x8103);
    return EFI_DEVICE_ERROR;
  }
  PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x8101);

  return Status;
}

/**
  Retrieves the number of currently used ICC clock profile

  @param[out] Profile             number of current ICC clock profile

  @retval EFI_UNSUPPORTED         ICC clock profile doesn't support
  @retval EFI_NOT_READY           Heci device hasn't ready yet
  @retval EFI_INVALID_PARAMETER   IccClockSettings is a NULL pointer
  @retval EFI_SUCCESS             Command succeeded
**/
EFI_STATUS
HeciGetIccClockSettings (
  OUT ICC_GETSET_CLOCK_SETTINGS_REQRSP  *IccClockSettings
  )
{
  EFI_STATUS                      Status;
  ICC_GET_CLOCK_SETTINGS_BUFFER   Buffer;
  UINT32                          CommandSize;
  UINT32                          ResponseSize;
  HECI_PROTOCOL                   *Heci;
  UINT32                          MeMode;
  UINT32                          MeStatus;

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  if (IccClockSettings == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  Status = Heci->GetMeStatus (&MeStatus);
  if (EFI_ERROR (Status) || ((MeStatus & 0xF) != ME_READY)) {
    return EFI_NOT_READY;
  }

  DEBUG ((DEBUG_INFO, "(ICC) HeciGetIccClockSettings\n"));
  CommandSize                         = sizeof (ICC_GETSET_CLOCK_SETTINGS_REQRSP);
  ResponseSize                        = sizeof (ICC_GETSET_CLOCK_SETTINGS_REQRSP);

  Buffer.message.Header.ApiVersion    = SKYLAKE_PCH_PLATFORM;
  Buffer.message.Header.IccCommand    = ICC_GET_CLOCK_SETTINGS_CMD;
  Buffer.message.Header.IccResponse   = 0;
  Buffer.message.Header.BufferLength  = CommandSize - sizeof (ICC_HEADER);
  Buffer.message.Header.Reserved      = 0;
  Buffer.message.ReqClock             = IccClockSettings->ReqClock;
  Buffer.message.SettingType          = IccClockSettings->SettingType;

  PERF_START_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80F0);
  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &Buffer,
                   CommandSize,
                   &ResponseSize,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_ICC_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(ICC) HeciGetIccClockSettings: Message failed! EFI_STATUS = %r\n", Status));
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80F2);
    return Status;
  }

  if (Buffer.response.Header.IccResponse != ICC_STATUS_SUCCESS) {
    DEBUG (
      (DEBUG_ERROR,
       "(ICC) HeciGetIccClockSettings: Wrong response! IccHeader.Response = 0x%x\n",
       Buffer.response.Header.IccResponse)
      );
    Status = EFI_DEVICE_ERROR;
  } else {
    DEBUG ((DEBUG_INFO, "(ICC) HeciGetIccClockSettings: Current profile = 0x%x\n"));
  }

  if (IccClockSettings != NULL) {
    CopyMem (IccClockSettings, &Buffer.response.Header, sizeof (ICC_GETSET_CLOCK_SETTINGS_REQRSP));
  }

  PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80F1);

  return Status;
}

/**
  Sets ICC clock profile to be used on next and following boots

  @param[in] IccClockSettings     Pointer for requested ICC Clock Settings

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_DEVICE_ERROR        Wrong response
  @retval EFI_NOT_READY           Heci device hasn't ready yet
  @retval EFI_SUCCESS             Command succeeded
**/
EFI_STATUS
HeciSetIccClockSettings (
  IN ICC_GETSET_CLOCK_SETTINGS_REQRSP *IccClockSettings
  )
{
  EFI_STATUS                      Status;
  ICC_SET_CLOCK_SETTINGS_BUFFER   Buffer;
  UINT32                          CommandSize;
  UINT32                          ResponseSize;
  HECI_PROTOCOL                   *Heci;
  UINT32                          MeMode;
  UINT32                          MeStatus;

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  Status = Heci->GetMeStatus (&MeStatus);
  if (EFI_ERROR (Status) || ((MeStatus & 0xF) != ME_READY)) {
    return EFI_NOT_READY;
  }

  DEBUG ((DEBUG_INFO, "(ICC) HeciSetIccClockSettings\n"));

  CommandSize                         = sizeof (ICC_GETSET_CLOCK_SETTINGS_REQRSP);
  ResponseSize                        = sizeof (ICC_GETSET_CLOCK_SETTINGS_REQRSP);

  ///
  ///  Copy input clock settings data to Heci message clock settings buffer
  ///
  CopyMem (&Buffer.message, IccClockSettings, sizeof (ICC_GETSET_CLOCK_SETTINGS_REQRSP));

  ///
  ///  Update HECI buffer header
  ///
  Buffer.message.Header.ApiVersion    = SKYLAKE_PCH_PLATFORM;
  Buffer.message.Header.IccCommand    = ICC_SET_CLOCK_SETTINGS_CMD;
  Buffer.message.Header.IccResponse   = 0;
  Buffer.message.Header.BufferLength  = CommandSize - sizeof (ICC_HEADER);
  Buffer.message.Header.Reserved      = 0;

  PERF_START_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x8100);
  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &Buffer,
                   CommandSize,
                   &ResponseSize,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_ICC_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(ICC) HeciSetIccClockSettings: Message failed! EFI_STATUS = %r\n", Status));
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x8102);
    return Status;
  }

  if (Buffer.response.Header.IccResponse != ICC_STATUS_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "(ICC) HeciSetIccClockSettings: Wrong response! IccHeader.Response = 0x%x\n", Buffer.response.Header.IccResponse));
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x8103);
    return EFI_DEVICE_ERROR;
  }
  PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x8101);

  return Status;
}

/**
  Retrieves the Clock Range Definition Record

  @param[out] IccClockRangeRecords     Clock Range Definition Records containing 2 single CRDR

  @retval EFI_UNSUPPORTED         ICC clock profile doesn't support
  @retval EFI_NOT_READY           Heci device hasn't ready yet
  @retval EFI_SUCCESS             Command succeeded
**/
EFI_STATUS
HeciGetClockRangeDefinitionRecord (
  OUT ICC_CLK_RANGE_DEF_REC  *IccClockRangeRecords
  )
{
  EFI_STATUS                      Status;
  ICC_GET_CLOCK_RANGE_BUFFER      Buffer;
  UINT32                          CommandSize;
  UINT32                          ResponseSize;
  HECI_PROTOCOL                   *Heci;
  UINT32                          MeMode;
  UINT32                          MeStatus;

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  Status = Heci->GetMeStatus (&MeStatus);
  if (EFI_ERROR (Status) || ((MeStatus & 0xF) != ME_READY)) {
    return EFI_NOT_READY;
  }

  DEBUG ((DEBUG_INFO, "(ICC) HeciGetClockRangeDefinitionRecord\n"));
  CommandSize                         = sizeof (ICC_GET_CLOCK_RANGE_MESSAGE);
  ResponseSize                        = sizeof (ICC_GET_CLOCK_RANGE_RESPONSE);

  Buffer.message.Header.ApiVersion    = SKYLAKE_PCH_PLATFORM;
  Buffer.message.Header.IccCommand    = ICC_GET_CLOCK_RANGE_DEF_REC_CMD;
  Buffer.message.Header.IccResponse   = 0;
  Buffer.message.Header.BufferLength  = CommandSize - sizeof (ICC_HEADER);
  Buffer.message.Header.Reserved      = 0;
  Buffer.message.Mode                 = 0;
  Buffer.message.RequiredRecord       = 0;
  Buffer.message.Reserved             = 0;

  PERF_START_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80F0);
  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *) &Buffer,
                   CommandSize,
                   &ResponseSize,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_ICC_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(ICC) HeciGetClockRangeDefinitionRecord: Message failed! EFI_STATUS = %r\n", Status));
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80F2);
    return Status;
  }

  if (Buffer.response.Header.IccResponse != ICC_STATUS_SUCCESS) {
    DEBUG (
      (DEBUG_ERROR,
       "(ICC) HeciGetClockRangeDefinitionRecord: Wrong response! IccHeader.Response = 0x%x\n",
       Buffer.response.Header.IccResponse)
      );
    Status = EFI_DEVICE_ERROR;
  } else {
    DEBUG ((DEBUG_INFO, "(ICC) HeciGetClockRangeDefinitionRecord: Current profile = 0x%x\n"));
  }

  if (IccClockRangeRecords != NULL) {
    CopyMem (IccClockRangeRecords, Buffer.response.Crdr.SingleClkRangeDef, sizeof (ICC_CLK_RANGE_DEF_REC));
  }

  PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80F1);

  return Status;
}

/**
  Writes 1 dword of data to the icc register offset specified by RegOffset in the ICC Aux space
  @param[in] RegOffset            Register Offset in ICC Aux Space to write
  @param[in] RegData              Dword ICC register data to write
  @param[in] ResponseMode 0       Wait for response, 1 - skip

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_DEVICE_ERROR        Wrong response
  @retval EFI_NOT_READY           ME is not ready
  @retval EFI_INVALID_PARAMETER   ResponseMode is invalid value
  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
HeciWriteIccRegDword (
  IN UINT16                       RegOffset,
  IN UINT32                       RegData,
  IN UINT8                        ResponseMode
  )
{
  EFI_STATUS                      Status;
  ICC_WRITE_ICC_REG_BUFFER        Buffer;
  UINT32                          CommandSize;
  UINT32                          ResponseSize;
  HECI_PROTOCOL                   *Heci;
  UINT32                          MeMode;
  UINT32                          MeStatus;

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  if ((ResponseMode != ICC_RESPONSE_MODE_SKIP) && (ResponseMode != ICC_RESPONSE_MODE_WAIT)) {
    return EFI_INVALID_PARAMETER;
  }

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  Status = Heci->GetMeStatus (&MeStatus);
  if (EFI_ERROR (Status) || ((MeStatus & 0xF) != ME_READY)) {
    return EFI_NOT_READY;
  }

  CommandSize                         = sizeof (ICC_WRITE_ICC_REG_DWORD_MESSAGE);
  ResponseSize                        = sizeof (ICC_WRITE_ICC_REG_DWORD_RESPONSE);

  Buffer.message.Header.ApiVersion                        = SKYLAKE_PCH_PLATFORM;
  Buffer.message.Header.IccCommand                        = ICC_SET_RECORD_CMD;
  Buffer.message.Header.IccResponse                       = 0;
  Buffer.message.Header.BufferLength                      = CommandSize - sizeof (ICC_HEADER);
  Buffer.message.Header.Reserved                          = 0;
  Buffer.message.Reserved                                 = 0;
  Buffer.message.Reserved1                                = 0;
  Buffer.message.Params                                   = ResponseMode;
  Buffer.message.RecordDword.RecordFlags                  = WRITE_ICC_RECORD_FLAGS;
  Buffer.message.RecordDword.BundleCount.BundlesCnt       = WRITE_ICC_REG_BUNDLE_COUNT;
  Buffer.message.RecordDword.BundleCount.AU               = 0;
  Buffer.message.RecordDword.BundleCount.Reserved         = 0;
  Buffer.message.RecordDword.AddressMask.AddressMaskData  = RegOffset | ADDRESS_MASK_FIXED_DATA;
  Buffer.message.RecordDword.RegValue                     = RegData;

  PERF_START_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80D0);
  Status = Heci->SendMsg (
                   HECI1_DEVICE,
                   (UINT32 *) &Buffer,
                   CommandSize,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_ICC_MESSAGE_ADDR
                   );

  if (ResponseMode == ICC_RESPONSE_MODE_WAIT) {
    Status = Heci->ReadMsg (
                     HECI1_DEVICE,
                     BLOCKING,
                     (UINT32 *) &Buffer,
                     &ResponseSize
                     );

  }
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(ICC) HeciWriteIccRegDword: Message failed! EFI_STATUS = %r\n", Status));
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80D2);
    return Status;
  }

  if (ResponseMode == ICC_RESPONSE_MODE_SKIP) {
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80D3);
    return EFI_SUCCESS;
  }

  if (Buffer.response.Header.IccResponse != ICC_STATUS_SUCCESS) {
    DEBUG (
      (DEBUG_ERROR,
       "(ICC) HeciWriteIccRegDword: Wrong response! IccHeader.Response = 0x%x\n",
       Buffer.response.Header.IccResponse)
      );
    PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x80D4);
    return EFI_DEVICE_ERROR;
  }

  return Status;
}

//
// ME Client - Hardware Asset
//

/**
  Send Hardware Asset Tables to Firmware

  @param[in] Handle               A handle for this module
  @param[in] AssetTableData       Hardware Asset Table Data
  @param[in] TableDataSize        Size of Asset table

  @retval EFI_SUCCESS             Table sent
  @retval EFI_ABORTED             Could not allocate Memory
**/
EFI_STATUS
HeciAssetUpdateFwMsg (
  IN EFI_HANDLE                   Handle,
  IN TABLE_PUSH_DATA              *AssetTableData,
  IN UINT16                       TableDataSize
  )
{
  AU_TABLE_PUSH_MSG *SendAssetTableDataMsg;
  EFI_STATUS        Status;
  HECI_PROTOCOL     *Heci;
  UINT32            Length;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ///
  /// Subtract off single byte from TABLE_PUSH_DATA.TableData[1]
  ///
  SendAssetTableDataMsg = AllocateZeroPool (sizeof (AU_TABLE_PUSH_MSG) + MAX_ASSET_TABLE_ALLOCATED_SIZE - 1);
  if (SendAssetTableDataMsg == NULL) {
    DEBUG ((DEBUG_ERROR, "AssetUpdateFwMsg Error: Could not allocate Memory\n"));
    return EFI_ABORTED;
  }

  if (TableDataSize > MAX_ASSET_TABLE_ALLOCATED_SIZE) {
    TableDataSize = MAX_ASSET_TABLE_ALLOCATED_SIZE;
  }

  SendAssetTableDataMsg->Header.Data = 0;
  ///
  /// Subtract off single byte from TABLE_PUSH_DATA.TableData[1]
  ///
  SendAssetTableDataMsg->Header.Fields.MessageLength      = TableDataSize + sizeof (TABLE_PUSH_DATA) - 1;
  SendAssetTableDataMsg->Header.Fields.Command            = HWA_TABLE_PUSH_CMD;
  SendAssetTableDataMsg->Header.Fields.FRUTablePresent    = 1;
  SendAssetTableDataMsg->Header.Fields.SMBIOSTablePresent = 1;
  SendAssetTableDataMsg->Header.Fields.ASFTablePresent    = 1;

  if (AssetTableData->Tables[HWAI_TABLE_TYPE_INDEX_MEDIA_DEVICE].Length == 0) {
    SendAssetTableDataMsg->Header.Fields.MediaTablePresent = 0;
  } else {
    SendAssetTableDataMsg->Header.Fields.MediaTablePresent = 1;
  }

  CopyMem (&SendAssetTableDataMsg->Data, AssetTableData, SendAssetTableDataMsg->Header.Fields.MessageLength);

  Length = SendAssetTableDataMsg->Header.Fields.MessageLength + sizeof (AU_MESSAGE_HEADER);

  PERF_START_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x3020);
  Status = Heci->SendMsg (
                   HECI1_DEVICE,
                   (UINT32 *) SendAssetTableDataMsg,
                   Length,
                   BIOS_FIXED_HOST_ADDR,
                   HECI_HWA_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "AssetUpdateFwMsg: Failed to Send SendAssetTableDataMsg\n"));
  }
  PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x3021);

  FreePool (SendAssetTableDataMsg);

  return Status;

}
