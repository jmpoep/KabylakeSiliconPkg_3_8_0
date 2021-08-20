/** @file
  MKHI Messages

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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
#ifndef _MKHI_MSGS_H
#define _MKHI_MSGS_H

#pragma pack(1)

///
/// MKHI host message header. This header is part of HECI message sent from MEBx via
/// Host Configuration Interface (HCI). ME Configuration Manager or Power Configuration
/// Manager also include this header with appropriate fields set as part of the
/// response message to the HCI.
///
typedef union {
  UINT32  Data;
  struct {
    UINT32  GroupId    : 8;
    UINT32  Command    : 7;
    UINT32  IsResponse : 1;
    UINT32  Reserved   : 8;
    UINT32  Result     : 8;
  } Fields;
} MKHI_MESSAGE_HEADER;


///
/// Defines for GroupID
///
#define MKHI_CBM_GROUP_ID     0x00
#define MKHI_FWCAPS_GROUP_ID  0x03
#define MKHI_HMRFPO_GROUP_ID  0x05
#define MKHI_MCA_GROUP_ID     0x0A
#define MKHI_GEN_GROUP_ID     0xFF


///
/// Defines for Command
///
///
/// Defines for CBM_GROUP Command
///
#define CBM_RESET_CMD         0x0B
///
/// Defines for FWCAPS_GROUP Command
///
#define FWCAPS_GET_RULE_CMD   0x02
#define FWCAPS_SET_RULE_CMD   0x03
///
/// Defines for HMRFPO_GROUP Command
///
#define HMRFPO_ENABLE_CMD_ID      0x01
#define HMRFPO_LOCK_CMD_ID        0x02
#define HMRFPO_GET_STATUS_CMD_ID  0x03
///
/// Defines for MCA_GROUP Command
///
#define MCA_CORE_BIOS_DONE_CMD     0x05
///
/// Defines for GEN_GROUP Command
///
#define GEN_GET_FW_VERSION_CMD             0x02
#define GEN_END_OF_POST_CMD                0x0C
#define GEN_SET_ME_RESET_HALT_CMD          0x10
#define GEN_FW_FEATURE_STATE_OVERRIDE_CMD  0x14


//
// Typedef for Result field of MHKI Header
//
typedef enum {
  MeSuccess,
  MeErrorAliasCheckFailed,
  MeInvalidMessage,
  MeM1DataOlderVer,
  MeM1DataInvalidVer,
  MeInvalidM1Data
} MKHI_RESULT;


//
// MKHI_FWCAPS_GROUP_ID Definitions
//

//
// Definitions for Firmware Capabilities Group Rule Id
//

#define FW_CAPS_RULE_ID                0x00
#define ME_PLATFORM_STATUS_RULE_ID     0x06
#define LOCAL_FW_UPDATE_RULE_ID        0x07
#define PLATFORM_TYPE_RULE_ID          0x1D
#define FW_FEATURE_STATE_RULE_ID       0x20
#define OEM_TAG_RULE_ID                0x2B
#define ACM_TPM_DATA_RULE_ID           0x2F
#define UNCONFIG_ON_RTC_CLEAR_RULE_ID  0x30
#define AMT_BIOS_SYNC_INFO_RULE_ID     0x30005

#define RULE_DATA_LENGTH               0x04

///
/// Get Firmware Capability
///
typedef struct {
  UINT32  RuleId;
} GET_RULE_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  GET_RULE_DATA       Data;
} GET_FW_CAPSKU;

typedef union {
  UINT32  Data;
  struct {
    UINT32  FullNet         : 1;      ///< [0] Full network manageability
    UINT32  StdNet          : 1;      ///< [1] Standard network manageability
    UINT32  Manageability   : 1;      ///< [2] Manageability
    UINT32  SmallBusiness   : 1;      ///< [3] Small business adavantage
    UINT32  IntegratedTouch : 1;      ///< [4] Intel Integrated Touch
    UINT32  Reserved1       : 1;      ///< [5] Reserved
    UINT32  IntelCLS        : 1;      ///< [6] IntelR Capability Licensing Service (CLS)
    UINT32  Reserved2       : 3;      ///< [9:7] Reserved
    UINT32  ISH             : 1;      ///< [10] IntelR Sensor Hub
    UINT32  Reserved3       : 1;      ///< [11] Reserved
    UINT32  PAVP            : 1;      ///< [12] Protected Audio Video Path (PAVP)
    UINT32  Reserved4       : 4;      ///< [16:13] Reserved
    UINT32  IPV6            : 1;      ///< [17] IPV6
    UINT32  KVM             : 1;      ///< [18] KVM Remote Control (KVM)
    UINT32  OCH             : 1;      ///< [19] Outbreak Containment Heuristic (OCH)
    UINT32  DAL             : 1;      ///< [20] Dynamic Application Loader (DAL)
    UINT32  TLS             : 1;      ///< [21] Cipher Transport Layer (TLS)
    UINT32  Reserved5       : 1;      ///< [22] Reserved
    UINT32  WLAN            : 1;      ///< [23] Wireless LAN (WLAN)
    UINT32  Reserved6       : 5;      ///< [28:24] Reserved
    UINT32  PTT             : 1;      ///< [29] Platform Trust Technology (PTT)
    UINT32  Reserved7       : 1;      ///< [30] Reserved
    UINT32  NFC             : 1;      ///< [31] Near Field Communication (NFC)
  } Fields;
} MEFWCAPS_SKU;

typedef struct {
  UINT32        RuleID;
  UINT8         RuleDataLen;
  MEFWCAPS_SKU  FWCapSku;
} GET_FW_CAPS_SKU_ACK_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER           MkhiHeader;
  GET_FW_CAPS_SKU_ACK_DATA  Data;
} GET_FW_CAPS_SKU_ACK;

typedef union {
  GET_FW_CAPSKU       Request;
  GET_FW_CAPS_SKU_ACK Response;
} GET_FW_CAPS_SKU_BUFFER;


///
/// Get/Set Local FW Update
///
#define LOCAL_FW_UPDATE_RULE_DATA_LENGTH 0x04

#define LOCAL_FW_UPDATE_RSVD_LENGTH      27

typedef enum {
  UpdateDisabled,
  UpdateEnabled
} LOCAL_FW_UPDATE;

typedef struct {
  UINT32  RuleId;
  UINT8   RuleDataLen;
  UINT32  RuleData;
  UINT8   Reserved[LOCAL_FW_UPDATE_RSVD_LENGTH];
} LOCAL_FW_UPDATE_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  GET_RULE_DATA       Data;
} GET_LOCAL_FW_UPDATE;

typedef struct {
  MKHI_MESSAGE_HEADER       MkhiHeader;
  LOCAL_FW_UPDATE_DATA  Data;
} GET_LOCAL_FW_UPDATE_ACK;

typedef struct {
  MKHI_MESSAGE_HEADER       MkhiHeader;
  LOCAL_FW_UPDATE_DATA  Data;
} SET_LOCAL_FW_UPDATE;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  GET_RULE_DATA       Data;
} SET_LOCAL_FW_UPDATE_ACK;

///
/// Get Platform Type
///
typedef enum {
  NoBrand,
  IntelAmtBrand,
  IntelStandardManageabilityBrand,
  IntelReservedBrand1,
  IntelReservedBrand2,
  IntelSmallBusinessTechnologyBrand
} PLATFORM_BRAND;

typedef enum {
  IntelMeConsumerFw                        = 3,
  IntelMeCorporateFw
} ME_IMAGE_TYPE;

typedef enum {
  RegularSku,
  SuperSku
} SKU_TYPE;

typedef enum {
  PlatformMobile                             = 1,
  PlatformDesktop                            = 2,
  PlatformServer                             = 4,
  PlatformWorkstation                        = 8
} PLATFORM_TARGET_USAGE_TYPE;

typedef union {
  UINT32  Data;
  struct {
    UINT32  PlatformTargetUsageType : 4;
    UINT32  Reserved                : 2;
    UINT32  SuperSku                : 1;
    UINT32  Reserved1               : 1;
    UINT32  IntelMeFwImageType      : 4;
    UINT32  PlatformBrand           : 4;
    UINT32  Reserved2               : 16;
  } Fields;
} PLATFORM_TYPE_RULE_DATA;

typedef struct {
  UINT32                  RuleId;
  UINT8                   RuleDataLen;
  PLATFORM_TYPE_RULE_DATA RuleData;
  UINT8                   Reserved[27];
} PLATFORM_TYPE_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  GET_RULE_DATA       Data;
} GET_PLATFORM_TYPE;

typedef struct {
  MKHI_MESSAGE_HEADER     MkhiHeader;
  PLATFORM_TYPE_DATA  Data;
} GET_PLATFORM_TYPE_ACK;

typedef union {
  GET_PLATFORM_TYPE     Request;
  GET_PLATFORM_TYPE_ACK Response;
} GET_PLATFORM_TYPE_BUFFER;

///
/// AMT BIOS Sync Info
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              RuleId;
} AMT_BIOS_SYNCH_INFO;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              RuleId;
  UINT8               RuleDataLength;
  UINT32              RuleData;
} AMT_BIOS_SYNCH_INFO_ACK;

///
/// Get FW Feature State
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              RuleId;
} GET_FW_FEATURE_STATUS;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              RuleId;
  UINT8               RuleDataLength;
  MEFWCAPS_SKU        RuleData;
} GET_FW_FEATURE_STATUS_ACK;

///
/// Get OEM Tag
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              RuleId;
} GET_OEM_TAG;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              RuleId;
  UINT8               RuleDataLength;
  UINT32              RuleData;
} GET_OEM_TAG_ACK;

///
/// Set ME Disable
///
typedef union {
  UINT32  Data;
  struct {
    UINT32  RuleTypeId : 16;
    UINT32  FeatureId  : 8;
    UINT32  Reserved   : 8;
  } Fields;
} RULE_ID;

typedef struct {
  RULE_ID RuleId;
  UINT8   RuleDataLen;
  UINT8   RuleData;
} SET_RULE_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  SET_RULE_DATA       Data;
} SET_FW_CAPSKU;

typedef struct {
  UINT32  RuleId;
} SET_RULE_ACK_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  SET_RULE_ACK_DATA   Data;
} SET_FW_CAPSKU_ACK;

///
/// Set ACM TPM
///
#define ACM_TPM_DATA_RULE_DATA_LENGTH 0x04

typedef union {
  UINT16 Data;
  struct {
    UINT16 Reserved_0    : 8;
    UINT16 TpmDeactivate : 1;
    UINT16 Reserved_1    : 7;
  } Fields;
} TPM_STATE;

typedef struct {
  RULE_ID   RuleId;
  UINT8     RuleDataLen;
  TPM_STATE TpmState;
  UINT8     Reserved[2];
} ACM_TPM_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  ACM_TPM_DATA        AcmTpmData;
} BIOSNV_SET_ACM_TPM;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  RULE_ID             RuleId;
} BIOSNV_SET_ACM_TPM_ACK;

///
/// Get/Set Unconfigure on RTC Clear Disable State
///

///
/// Unconfig On Rtc Clear Status
///
typedef enum {
  EnableState  = 0,  ///< [Unconfigure on RTC Clear] is enabled.
  DisableState = 1   ///< [Unconfigure on RTC Clear] is disabled.
} ME_UNCONFIG_ON_RTC_CLEAR_STATUS;

typedef struct {
  UINT32  RuleId;
  UINT8   RuleDataLen;
  UINT32  RuleData;
} ME_UNCONFIG_ON_RTC_CLEAR_STATE_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  GET_RULE_DATA       Data;
} ME_GET_UNCONFIG_ON_RTC_CLEAR_STATE;

typedef struct {
  MKHI_MESSAGE_HEADER                  MkhiHeader;
  ME_UNCONFIG_ON_RTC_CLEAR_STATE_DATA  Data;
} ME_GET_UNCONFIG_ON_RTC_CLEAR_STATE_ACK;

typedef union {
  ME_GET_UNCONFIG_ON_RTC_CLEAR_STATE     Request;
  ME_GET_UNCONFIG_ON_RTC_CLEAR_STATE_ACK Response;
} ME_GET_UNCONFIG_ON_RTC_CLEAR_STATE_BUFFER;

typedef struct {
  MKHI_MESSAGE_HEADER                  MkhiHeader;
  ME_UNCONFIG_ON_RTC_CLEAR_STATE_DATA  Data;
} ME_SET_UNCONFIG_ON_RTC_CLEAR_STATE;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  GET_RULE_DATA       Data;
} ME_SET_UNCONFIG_ON_RTC_CLEAR_STATE_ACK;

typedef union {
  ME_SET_UNCONFIG_ON_RTC_CLEAR_STATE     Request;
  ME_SET_UNCONFIG_ON_RTC_CLEAR_STATE_ACK Response;
} ME_SET_UNCONFIG_ON_RTC_CLEAR_STATE_BUFFER;

//
// MKHI_HMRFPO_GROUP_ID Definitions
//

///
/// HMRFPO ENABLE
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT64              Nonce;                 ///< this value should be set to 0
} HMRFPO_ENABLE;

//MRFPO_ENABLE returned Status
#define HMRFPO_ENABLE_SUCCESS         0x00
#define HMRFPO_ENABLE_LOCKED          0x01
#define HMRFPO_NVAR_FAILURE           0x02
#define HMRFPO_ATP_POLICY             0x03
#define HMRFPO_ENABLE_UNKNOWN_FAILURE 0x04

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              FactoryDefaultBase;   ///< this value should be set to 0
  UINT32              FactoryDefaultLimit;  ///< this value should be set to 0
  UINT8               Status;
  UINT8               Rsvd[3];
} HMRFPO_ENABLE_RESPONSE;

///
/// HMRFPO LOCK
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} HMRFPO_LOCK;

//HMRFPO_LOCK_RESPONSE returned Status
#define HMRFPO_LOCK_SUCCESS 0x00
#define HMRFPO_LOCK_FAILURE 0x01

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT64              Nonce;               ///< this value should be set to 0
  UINT32              FactoryDefaultBase;  ///< this value should be set to 0
  UINT32              FactoryDefaultLimit; ///< this value should be set to 0
  UINT8               Status;
  UINT8               Reserved[3];
} HMRFPO_LOCK_RESPONSE;

///
/// HMRFPO GET STATUS
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} HMRFPO_GET_STATUS;

//HMRFPO_GET_STATUS returned Status
#define HMRFPO_DISABLED         0x00
#define HMRFPO_LOCKED           0x01
#define HMRFPO_ENABLED          0x02

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT8               Status;
  UINT8               Reserved[3];
} HMRFPO_GET_STATUS_RESPONSE;

//
// MKHI_MCA_GROUP_ID Definitions
//

//
// Core Bios Done
//
typedef struct {
  MKHI_MESSAGE_HEADER    MkhiHeader;
} CORE_BIOS_DONE;

typedef struct {
  MKHI_MESSAGE_HEADER    MkhiHeader;
} CORE_BIOS_DONE_ACK;

//
// MKHI_GEN_GROUP_ID Definitions
//

///
/// Get FW Version
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} GET_FW_VER;

typedef struct {
  UINT32  CodeMinor   : 16;
  UINT32  CodeMajor   : 16;
  UINT32  CodeBuildNo : 16;
  UINT32  CodeHotFix  : 16;
  UINT32  RcvyMinor   : 16;
  UINT32  RcvyMajor   : 16;
  UINT32  RcvyBuildNo : 16;
  UINT32  RcvyHotFix  : 16;
  UINT32  FitcMinor   : 16;
  UINT32  FitcMajor   : 16;
  UINT32  FitcBuildNo : 16;
  UINT32  FitcHotFix  : 16;
} GET_FW_VER_ACK_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER     MkhiHeader;
  GET_FW_VER_ACK_DATA Data;
} GET_FW_VER_ACK;

///
/// End of Post
///
#define EOP_DISABLED    0
#define EOP_SEND_IN_PEI 1
#define EOP_SEND_IN_DXE 2

typedef struct {
  MKHI_MESSAGE_HEADER Header;
} END_OF_POST;

typedef enum {
  HeciEopStatusSuccess,
  HeciEopPerformGlobalReset
} EOP_REQUESTED_ACTIONS;

typedef struct {
  UINT32  RequestedActions;
} EOP_ACK_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER Header;
  EOP_ACK_DATA        Data;
} END_OF_POST_ACK;

///
/// FW Feature Shipment Time State Override
///
typedef struct {
  UINT32  EnableFeature;
  UINT32  DisableFeature;
} FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER                          MkhiHeader;
  FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_DATA FeatureState;
} FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE;

//
// FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE returned Status
//
typedef enum {
  SetFeatureStateAccepted,
  SetFeatureStateRejected
} FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_RESPONSE;

typedef struct {
  MKHI_MESSAGE_HEADER   MkhiHeader;
  UINT32                Status;
} FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_ACK;

typedef union {
  FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE      Request;
  FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_ACK  Response;
} FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_BUFFER;

///
/// Set Manufacturing ME Reset and Halt messages
///
typedef struct {
  MKHI_MESSAGE_HEADER     MkhiHeader;
} SET_ME_RESET_HALT;

typedef struct {
  MKHI_MESSAGE_HEADER     MkhiHeader;
} SET_ME_RESET_HALT_ACK;

#pragma pack()

#endif // _MKHI_MSGS_H
