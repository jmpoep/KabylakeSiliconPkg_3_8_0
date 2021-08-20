/** @file
  Implementation file for Heci Message functionality

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

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

#include "MePeiLibInternals.h"

//
// ME Client - MKHI
//

//
// MKHI_FWCAPS_GROUP_ID = 0x03
//

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
  IN OUT MEFWCAPS_SKU             *FwCapsSku
  )
{
  EFI_STATUS                      Status;
  GET_FW_CAPS_SKU_BUFFER          GetFwCapsSku;
  UINT32                          Length;
  UINT32                          RecvLength;
  HECI_PPI                        *HeciPpi;
  UINT32                          MeMode;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  Status = HeciPpi->GetMeMode (&MeMode);
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
  Status = HeciPpi->SendwAck (
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
  )
{
  EFI_STATUS                      Status;
  UINT32                          Length;
  UINT32                          RecvLength;
  GET_FW_FEATURE_STATUS_ACK       GetFwFeatureStatus;
  UINT32                          MeMode;
  HECI_PPI                        *HeciPpi;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  Status = HeciPpi->GetMeMode (&MeMode);
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

  Status = HeciPpi->SendwAck (
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
  )
{
  EFI_STATUS                      Status;
  UINT32                          Length;
  UINT32                          RecvLength;
  HECI_PPI                        *HeciPpi;
  GET_PLATFORM_TYPE_BUFFER        GetPlatformType;
  UINT32                          MeMode;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  Status = HeciPpi->GetMeMode (&MeMode);
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
  Status = HeciPpi->SendwAck (
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


//
// BUP_COMMON_GROUP_ID = 0xF0
//

/**
  Send DRAM init done message through HECI to inform ME of memory initialization done.

  @param[in] DidInput             ME UMA data
  @param[out] BiosAction          ME response to DID

  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
PeiHeciSendDid (
  IN  UINT32                      DidInput,
  OUT UINT8                       *BiosAction
  )
{
  EFI_STATUS              Status;
  HECI_PPI                *HeciPpi;
  DRAM_INIT_DONE_CMD_REQ  DidRequest;
  UINT32                  ReqLength;
  UINT32                  RespLength;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  DidRequest.MkhiHeader.Data               = 0;
  DidRequest.MkhiHeader.Fields.Command     = DRAM_INIT_DONE_CMD;
  DidRequest.MkhiHeader.Fields.IsResponse  = 0;
  DidRequest.MkhiHeader.Fields.GroupId     = BUP_COMMON_GROUP_ID;
  DidRequest.MkhiHeader.Fields.Reserved    = 0;
  DidRequest.MkhiHeader.Fields.Result      = 0;
  DidRequest.DIDData.ul                    = DidInput;

  ReqLength  = sizeof (DRAM_INIT_DONE_CMD_REQ);
  RespLength = sizeof (DRAM_INIT_DONE_CMD_RESP);

  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &DidRequest,
                      ReqLength,
                      &RespLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (((DRAM_INIT_DONE_CMD_RESP*)&DidRequest)->MkhiHeader.Fields.Result != 0) {
    return EFI_DEVICE_ERROR;
  }

  *BiosAction = ((DRAM_INIT_DONE_CMD_RESP*)&DidRequest)->BiosAction;

  return Status;
}

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
  IN BOOLEAN                   SkipMbp
  )
{
  EFI_STATUS     Status;
  MBP_CMD_REQ    *MsgGetMbp;
  MBP_CMD_RESP   *MsgGetMbpAck;
  UINT8          MsgGetMbpAckBuffer[sizeof (MBP_CMD_RESP) + MAX_MBP_SIZE - 1];
  UINT32         Length;
  UINT32         RecvLength;
  HECI_PPI       *HeciPpi;

  ZeroMem (MsgGetMbpAckBuffer, sizeof (MsgGetMbpAckBuffer));

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  MsgGetMbp                                = (MBP_CMD_REQ*) &MsgGetMbpAckBuffer;
  MsgGetMbp->MkhiHeader.Data               = 0;
  MsgGetMbp->MkhiHeader.Fields.GroupId     = BUP_COMMON_GROUP_ID;
  MsgGetMbp->MkhiHeader.Fields.Command     = MBP_REQUEST_CMD;
  MsgGetMbp->MkhiHeader.Fields.IsResponse  = 0;
  MsgGetMbp->SkipMbp                       = SkipMbp;
  Length                                   = sizeof (MBP_CMD_REQ);
  RecvLength                               = sizeof (MBP_CMD_RESP) + MAX_MBP_SIZE - 1;

  ///
  /// Send Get MBP Request to ME
  ///
  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) MsgGetMbp,
                      Length,
                      &RecvLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );

  MsgGetMbpAck = (MBP_CMD_RESP*) MsgGetMbpAckBuffer;
  DEBUG ((DEBUG_INFO, "ReadMsg returned %r\n", Status));
  DEBUG ((DEBUG_INFO, "MsgGetMbpAck->MkhiHeader.Fields.Command = %d\n", MsgGetMbpAck->MkhiHeader.Fields.Command));
  DEBUG ((DEBUG_INFO, "MsgGetMbpAck->MkhiHeader.Fields.IsResponse = %d\n", MsgGetMbpAck->MkhiHeader.Fields.IsResponse));
  DEBUG ((DEBUG_INFO, "MsgGetMbpAck->MkhiHeader.Fields.Result = %d\n", MsgGetMbpAck->MkhiHeader.Fields.Result));

  if (!EFI_ERROR (Status) && !SkipMbp &&
      ((MsgGetMbpAck->MkhiHeader.Fields.Command) == MBP_REQUEST_CMD) &&
      ((MsgGetMbpAck->MkhiHeader.Fields.IsResponse) == 1) &&
      (MsgGetMbpAck->MkhiHeader.Fields.Result == 0)
      ) {
    CopyMem (MbpHeader, &MsgGetMbpAck->MbpHeader, sizeof (MBP_HEADER));
    CopyMem (MbpItems, &MsgGetMbpAck->MbpItems, RecvLength - sizeof (MBP_HEADER) - sizeof (MKHI_MESSAGE_HEADER));
  }

  //
  // Clear buffers from sensitive data
  //
  ZeroMem (MsgGetMbpAckBuffer, sizeof (MsgGetMbpAckBuffer));
  return Status;
}


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
  )
{
  EFI_STATUS                  Status;
  MANUF_RESET_AND_HALT_BUFFER ManufResetAndHalt;
  UINT32                      Length;
  UINT32                      RecvLength;
  HECI_PPI                    *HeciPpi;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  ManufResetAndHalt.Request.MkhiHeader.Data           = 0;
  ManufResetAndHalt.Request.MkhiHeader.Fields.GroupId = BUP_COMMON_GROUP_ID;
  ManufResetAndHalt.Request.MkhiHeader.Fields.Command = MANUF_RESET_AND_HALT_CMD;
  Length                                              = sizeof (MANUF_RESET_AND_HALT_REQ);
  RecvLength                                          = sizeof (MANUF_RESET_AND_HALT_RESP);

  ///
  /// Send Manufacturing Reset and Halt Request to ME
  ///
  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &ManufResetAndHalt,
                      Length,
                      &RecvLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );

  if (ManufResetAndHalt.Response.MkhiHeader.Fields.Result != 0) {
    return EFI_DEVICE_ERROR;
  }

  return Status;
}


//
// BUP_ICC_GROUP_ID = 0xF1
//

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
  )
{
  EFI_STATUS     Status;
  HECI_PPI       *HeciPpi;
  ICC_CMD_RESP   IccResp;
  UINT32         RespLength;

  DEBUG ((DEBUG_INFO, "(ICC) PeiHeciIccBclkMsg\n"));

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  IccResp.MkhiHeader.Data               = 0;
  IccResp.MkhiHeader.Fields.Command     = ICC_CMD;
  IccResp.MkhiHeader.Fields.IsResponse  = 0;
  IccResp.MkhiHeader.Fields.GroupId     = BUP_ICC_GROUP_ID;
  IccResp.MkhiHeader.Fields.Reserved    = 0;
  IccResp.MkhiHeader.Fields.Result      = 0;
  IccResp.Data.FwNeedsWarmResetFlag     = 0;
  RespLength = sizeof (ICC_CMD_RESP);

  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &IccResp,
                      RespLength,
                      &RespLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );

  if (!EFI_ERROR (Status) && (IccResp.MkhiHeader.Fields.Result != 0x0)) {
    DEBUG ((DEBUG_ERROR, "(ICC) result non zero\n"));

    Status = EFI_DEVICE_ERROR;
  }

  if (IccResp.Data.FwNeedsWarmResetFlag == 0x1) {
    *WarmResetRequired = 1;
  }

  return Status;
}

//
// BUP_HSIO_GROUP_ID = 0xF2
//

/**
  Send HSIO request through HECI to get the HSIO settings version on CSME side.

  @param[in]  BiosCmd              HSIO command: 0 - close interface, 1 - report HSIO version
  @param[out] Crc                  CRC16 of ChipsetInit Table

  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
PeiHeciHsioMsg (
  IN  UINT32                      BiosCmd,
  OUT UINT16                      *Crc
  )
{
  EFI_STATUS      Status;
  HECI_PPI        *HeciPpi;
  HSIO_CMD_BUFFER HsioRequest;
  UINT32          ReqLength;
  UINT32          RespLength;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  HsioRequest.Request.MkhiHeader.Data               = 0;
  HsioRequest.Request.MkhiHeader.Fields.Command     = HSIO_CMD;
  HsioRequest.Request.MkhiHeader.Fields.GroupId     = BUP_HSIO_GROUP_ID;

  ReqLength  = sizeof (HSIO_CMD_REQ);
  RespLength = sizeof (HSIO_CMD_RESP);

  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &HsioRequest,
                      ReqLength,
                      &RespLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );

  if (!EFI_ERROR (Status) && (HsioRequest.Response.MkhiHeader.Fields.Result != 0)) {
    Status = EFI_DEVICE_ERROR;
  }

  *Crc = HsioRequest.Response.Data.Crc;

  return Status;
}

//
// BUP_PM_GROUP_ID = 0xF3
//

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
  )
{
  EFI_STATUS             Status;
  HECI_PPI               *HeciPpi;
  UINT32                 Length;
  UINT32                 RecvLength;
  HR_NOTIFICATION_BUFFER HrNotification;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  HrNotification.Request.MkhiHeader.Data           = 0;
  HrNotification.Request.MkhiHeader.Fields.GroupId = BUP_PM_GROUP_ID;
  HrNotification.Request.MkhiHeader.Fields.Command = NPCR_NOTIFICATION_CMD;
  Length                                           = sizeof (HR_NOTIFICATION_CMD);
  RecvLength                                       = sizeof (HR_NOTIFICATION_CMD_RESP);

  ///
  /// Send Host Reset Notification Request to ME
  ///
  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &HrNotification,
                      Length,
                      &RecvLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );

  if (!EFI_ERROR(Status) && (HrNotification.Response.ResetRequested == 0x1)) {
    (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetWarm, EFI_SUCCESS, 0, NULL);
  }

  return Status;
}

//
// Interface functions of HeciMsgLib
//

//
// ME Client - Integrated Clock Chip (ICC)
//

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
  )
{
  HECI_PPI                       *HeciPpi;
  EFI_STATUS                     Status;
  UINT32                         ReqSize;
  HSIO_WRITE_SETTINGS_REQ        *HsioWriteSettingsReqPtr;

  DEBUG ((DEBUG_INFO, "PeiHeciChipsetInitSyncMsg(0x%08X, %x, %x): Start\n", ChipsetInitTable, ChipsetInitTableLen, BypassPhySyncReset));
  if (ChipsetInitTableLen > 4096) {
    ASSERT(ChipsetInitTableLen <= 4096);  // ChipsetInit table should not get too large
    return EFI_DEVICE_ERROR;
  }

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  //
  // Allocate a buffer for the Request Structure and the ChipsetInit Table
  //
  ReqSize = sizeof (HSIO_WRITE_SETTINGS_REQ) + ChipsetInitTableLen;
  HsioWriteSettingsReqPtr = AllocateZeroPool (ReqSize);
  if (HsioWriteSettingsReqPtr == NULL) {
    DEBUG ((DEBUG_ERROR, "(HSIO) PeiHeciChipsetInitSyncMsg: Could not allocate Memory\n"));
    return EFI_ABORTED;
  }
  //
  // Setup the HECI message for a HSIO Write
  //
  HsioWriteSettingsReqPtr->Header.ApiVersion   = SKYLAKE_PCH_PLATFORM;
  HsioWriteSettingsReqPtr->Header.IccCommand   = ICC_SET_HSIO_SETTINGS_CMD;
  HsioWriteSettingsReqPtr->Header.BufferLength = ReqSize - sizeof (ICC_HEADER);
  CopyMem (HsioWriteSettingsReqPtr+1, ChipsetInitTable, ChipsetInitTableLen);

  //
  // Send ChipsetInit Table to ME
  //
  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) HsioWriteSettingsReqPtr,
                      ReqSize,
                      &ReqSize,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_ICC_MESSAGE_ADDR
                      );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(HSIO) ERROR: Write HSIO Settings Message failed! EFI_STATUS = %r\n", Status));
  } else if (HsioWriteSettingsReqPtr->Header.IccResponse != ICC_STATUS_SUCCESS) {
    DEBUG ((DEBUG_ERROR,"(HSIO) ERROR: Write HSIO Settings failed!: FW Response=0x%x\n", HsioWriteSettingsReqPtr->Header.IccResponse));
    Status = EFI_DEVICE_ERROR;
  }

  if (BypassPhySyncReset) {
    DEBUG ((DEBUG_ERROR, "(HSIO) ERROR: Bypass the mSync reset.\n"));
    Status = EFI_DEVICE_ERROR;
  }

  FreePool (HsioWriteSettingsReqPtr);
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "PeiHeciChipsetInitSyncMsg(): Reset required for ChipsetInit Settings synch\n"));
    (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetCold, EFI_SUCCESS, 0, NULL);
  }

  DEBUG ((DEBUG_INFO, "PeiHeciChipsetInitSyncMsg(): End\n"));
  return Status;
}

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
  )
{
  HECI_PPI                       *HeciPpi;
  EFI_STATUS                     Status;
  UINT32                         HeciLength;
  UINT32                         AckLength;
  CBM_RESET_REQ                  CbmResetRequest;
  UINT32                         MeMode;
  UINT32                         Result;

  DEBUG ((DEBUG_INFO, "ME-BIOS: ME: Global Reset Request Entry.\n"));
  PostCode (0xE06);

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: ME: Global Reset Request Exit - Error by HECI service not found.\n"));
    PostCode (0xEA6);
    return EFI_NOT_FOUND;
  }

  Status = HeciPpi->GetMeMode (&MeMode);
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

  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &CbmResetRequest,
                      HeciLength,
                      &AckLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "PeiHeciSendCbmResetRequest() - Unable to Send Reset Request - %r\n", Status));
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
  )
{
  EFI_STATUS                                Status;
  UINT32                                    Length;
  UINT32                                    RespLength;
  ME_GET_UNCONFIG_ON_RTC_CLEAR_STATE_BUFFER GetMeUnconfigOnRtcClearState;
  UINT32                                    MeMode;
  HECI_PPI                                  *HeciPpi;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  Status = HeciPpi->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  GetMeUnconfigOnRtcClearState.Request.MkhiHeader.Data              = 0;
  GetMeUnconfigOnRtcClearState.Request.MkhiHeader.Fields.GroupId    = MKHI_FWCAPS_GROUP_ID;
  GetMeUnconfigOnRtcClearState.Request.MkhiHeader.Fields.Command    = FWCAPS_GET_RULE_CMD;
  GetMeUnconfigOnRtcClearState.Request.Data.RuleId                  = UNCONFIG_ON_RTC_CLEAR_RULE_ID;

  Length = sizeof (ME_GET_UNCONFIG_ON_RTC_CLEAR_STATE);
  RespLength = sizeof (ME_GET_UNCONFIG_ON_RTC_CLEAR_STATE_ACK);

  Status = HeciPpi->SendwAck (
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
  )
{
  EFI_STATUS                                Status;
  UINT32                                    Length;
  UINT32                                    RespLength;
  ME_SET_UNCONFIG_ON_RTC_CLEAR_STATE_BUFFER SetMeUnconfigOnRtcClearState;
  UINT32                                    MeMode;
  HECI_PPI                                  *HeciPpi;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  Status = HeciPpi->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  SetMeUnconfigOnRtcClearState.Request.MkhiHeader.Data              = 0;
  SetMeUnconfigOnRtcClearState.Request.MkhiHeader.Fields.GroupId    = MKHI_FWCAPS_GROUP_ID;
  SetMeUnconfigOnRtcClearState.Request.MkhiHeader.Fields.Command    = FWCAPS_SET_RULE_CMD;
  SetMeUnconfigOnRtcClearState.Request.Data.RuleId                  = UNCONFIG_ON_RTC_CLEAR_RULE_ID;
  SetMeUnconfigOnRtcClearState.Request.Data.RuleDataLen             = RULE_DATA_LENGTH;
  SetMeUnconfigOnRtcClearState.Request.Data.RuleData                = RuleData;

  Length = sizeof (ME_SET_UNCONFIG_ON_RTC_CLEAR_STATE);
  RespLength = sizeof (ME_SET_UNCONFIG_ON_RTC_CLEAR_STATE_ACK);
  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &SetMeUnconfigOnRtcClearState,
                      Length,
                      &RespLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );

  return Status;
}

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
  )
{
  EFI_STATUS                             Status;
  UINT32                                 CommandSize;
  UINT32                                 ResponseSize;
  ICC_GET_SOFT_STRAP_CONFIG_CMD_BUFFER   *GetSoftStrapBuffer;
  HECI_PPI                               *HeciPpi;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  DEBUG ((DEBUG_INFO, "(ICC) PeiHeciGetSoftStrpConfigMsg Message\n"));
  ResponseSize         = NumberOfControllers * sizeof (UINT8) + sizeof (ICC_GET_SOFT_STRAP_CONFIG_CMD_RESP) + (4 * sizeof (UINT32));//(4 * sizeof (UINT32)) is needed for reserved field
  DEBUG ((DEBUG_INFO, "NumberOfControllers = 0x%x\n",NumberOfControllers));
  DEBUG ((DEBUG_INFO, "Response Size = 0x%x\n",ResponseSize));
  GetSoftStrapBuffer   = AllocateZeroPool (ResponseSize);
  if (GetSoftStrapBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  CommandSize                                     = sizeof (ICC_GET_SOFT_STRAP_CONFIG_CMD_REQ);
  GetSoftStrapBuffer->Message.Header.ApiVersion   = SKYLAKE_PCH_PLATFORM;
  GetSoftStrapBuffer->Message.Header.IccCommand   = ICC_GET_SOFT_STRAP_CONFIG_CMD;
  GetSoftStrapBuffer->Message.Header.BufferLength = CommandSize - sizeof (ICC_HEADER);

  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) GetSoftStrapBuffer,
                      CommandSize,
                      &ResponseSize,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_ICC_MESSAGE_ADDR
                      );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Message failed! Status = %r\n", Status));
  } else if (GetSoftStrapBuffer->Response.Header.IccResponse != ICC_STATUS_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "Wrong response! IccHeader.Response = 0x%x\n", GetSoftStrapBuffer->Response.Header.IccResponse));
    Status = EFI_DEVICE_ERROR;
  } else if (GetSoftStrapBuffer->Response.NumOfControllers != NumberOfControllers) {
    DEBUG ((DEBUG_ERROR, "Controller number not match! Number Of Controllers = 0x%x\n", GetSoftStrapBuffer->Response.NumOfControllers));
    Status = EFI_DEVICE_ERROR;
  } else {
    CopyMem (ControllerConfig, GetSoftStrapBuffer->Response.ControllerConfig, GetSoftStrapBuffer->Response.NumOfControllers);
  }

  FreePool (GetSoftStrapBuffer);
  DEBUG ((DEBUG_INFO, "(ICC) PeiHeciGetSoftStrpConfigMsg Status = %r\n", Status));
  return Status;
}

/**
  Set Pcie Root port configuration SoftStrap override for the specified Pcie Root Port controller

  @param[in] NumberOfControllers         On input, it is the number of controllers caller expects.
  @param[in] ConfigIndex                 RpIndex where TG is present and softstraps need to be overridden, if Invalid number then clear the override
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
  IN UINT16                                NumberOfControllers,
  IN UINT8                                 ConfigIndex,
  IN PCIE_CONTROLLER_SOFTSTRAP_OVERRIDE    OverrideIndex
  )
{
  EFI_STATUS                                  Status;
  UINT32                                      CommandSize;
  UINT32                                      ResponseSize;
  ICC_OVERRIDE_PCIE_SOFT_STRAP_CMD_BUFFER     *OverrideSoftStrapBuffer;
  HECI_PPI                                    *HeciPpi;
  UINT8                                       *ConfigBuffer;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DEBUG ((DEBUG_INFO, "(ICC) PeiHeciOverrideSoftStrapMsg Message\n"));

  CommandSize = NumberOfControllers * sizeof (UINT8) + sizeof (ICC_OVERRIDE_SOFT_STRAP_CMD_REQ) + (4 * sizeof (UINT32));//(4 * sizeof (UINT32)) is needed for reserved field
  OverrideSoftStrapBuffer = AllocateZeroPool (CommandSize);
  if (OverrideSoftStrapBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  ResponseSize = sizeof (ICC_OVERRIDE_SOFT_STRAP_CMD_RESP);
  OverrideSoftStrapBuffer->Message.Header.ApiVersion    = SKYLAKE_PCH_PLATFORM;
  OverrideSoftStrapBuffer->Message.Header.IccCommand    = ICC_OVERRIDE_SOFT_STRAP_CMD;
  OverrideSoftStrapBuffer->Message.Header.BufferLength  = CommandSize - sizeof (ICC_HEADER);
  OverrideSoftStrapBuffer->Message.NumOfControllers     = NumberOfControllers;
  ConfigBuffer                                          = OverrideSoftStrapBuffer->Message.ControllerConfig;
  ConfigBuffer [ConfigIndex]                            = OverrideIndex;
  DEBUG ((DEBUG_INFO, "NumberOfControllers = 0x%x\n",NumberOfControllers));
  DEBUG ((DEBUG_INFO, "Command Size = 0x%x\n",CommandSize));
  DEBUG ((DEBUG_INFO, "Response Size = 0x%x\n",ResponseSize));
  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *)OverrideSoftStrapBuffer,
                      CommandSize,
                      &ResponseSize,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_ICC_MESSAGE_ADDR
                      );

  if (EFI_ERROR (Status) || (OverrideSoftStrapBuffer->Response.Header.IccResponse != ICC_STATUS_SUCCESS)) {
    DEBUG ((DEBUG_ERROR, "(ICC) PeiHeciOverrideSoftStrapMsg: Message failed! Status = %r\n", Status));
    Status = EFI_DEVICE_ERROR;
  }

  DEBUG ((DEBUG_INFO, "(ICC) PeiHeciOverrideSoftStrapMsg: Message Status = %r\n", Status));
  FreePool (OverrideSoftStrapBuffer);
  return Status;
}