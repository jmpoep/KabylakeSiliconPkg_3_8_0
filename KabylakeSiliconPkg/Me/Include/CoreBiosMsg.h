/** @file
  Core BIOS Messages

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2008 - 2019 Intel Corporation.

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
#ifndef CORE_BIOS_MSG_H
#define CORE_BIOS_MSG_H

#include <MkhiMsgs.h>

#pragma pack(1)

//
//    Core messages to coordinate memory initialization and UMA allocation with ME
//    as well as to inform ME of the end of POST event
//

///
/// Header for all HECI message message placed in an Intel MEI circular buffer
///
typedef union {
  UINT32  Data;
  struct {
    /*
    This is the logical address of the Intel ME client of the message. This address is assigned
    during ME firmware initialization.
  */
    UINT32  MeAddress : 8;
  /*
    This is the logical address of the Host client of the message. This address is assigned
    when the host client registers itself with the Host MEI driver.
  */
    UINT32  HostAddress : 8;
    /*
    This is the message length in bytes, not including the MEI_MESSAGE_HEADER. A value of 0
    indicates no additional bytes are part of the message.
  */
    UINT32  Length : 9;
    UINT32  Reserved : 6;
  UINT32  MessageComplete : 1; /// < Indicates the last message of the list
  } Fields;
} HECI_MESSAGE_HEADER;

///
/// Host Address of Fixed Address MEI Header -
/// This is the logical address of the Host client of the message. This address
/// is assigned when the host client registers itself with the Host MEI driver.
///
/// Address 0 is statically allocated for MEI bus message protocol that assists in MEI bus
/// enumeration, power management, error and other bus control functionality.
///
/// Address 1 is statically allocated for host AMT/ASF message
///
#define BIOS_FIXED_HOST_ADDR                0
#define BIOS_ASF_HOST_ADDR                  1

///
/// ME Address of Fixed Address MEI Header -
/// This is the logical address of the Intel(R) ME client
/// of the message. This address is assigned during ME firmware initialization.
///
#define HECI_ASF_MESSAGE_ADDR               0x02
#define HECI_ISH_SERVICE_MESSAGE_ADDR       0x03
#define HECI_MKHI_MESSAGE_ADDR              0x07
#define HECI_ICC_MESSAGE_ADDR               0x08
#define HECI_HWA_MESSAGE_ADDR               0x0B


#define NON_BLOCKING                        0
#define BLOCKING                            1

//
// MKHI_CBM_GROUP_ID = 0x00
//

///
/// Reset request message data
///
typedef struct {
  UINT8 RequestOrigin;
  UINT8 ResetType;
} CBM_RESET_REQ_DATA;

///
/// Reset request MKHI message
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  CBM_RESET_REQ_DATA  Data;
} CBM_RESET_REQ;

///
/// Reset request MKHI ack message
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} CBM_RESET_ACK;

//
// Enumerations used in Core BIOS Messages
//

//
// Reset Request Origin Codes.
//
#define CBM_RR_REQ_ORIGIN_BIOS_MEMORY_INIT 0x01
#define CBM_RR_REQ_ORIGIN_BIOS_POST        0x02
#define CBM_RR_REQ_ORIGIN_MEBX             0x03

//
// Reset Type Codes.
//
#define CBM_HRR_GLOBAL_RESET  0x01

//
// Reset Response Codes.
//
#define CBM_HRR_RES_REQ_NOT_ACCEPTED  0x01

//
// definitions for ICC MEI Messages
//
#define IBEX_PEAK_PLATFORM      0x00010000
#define COUGAR_POINT_PLATFORM   0x00020000
#define LYNX_POINT_PLATFORM     0x00030000
#define SKYLAKE_PCH_PLATFORM    0x00040000

typedef enum {
   ICC_STATUS_SUCCESS                           = 0x0,
   ICC_STATUS_FAILURE,
   ICC_STATUS_INCORRECT_API_VERSION,
   ICC_STATUS_INVALID_FUNCTION,
   ICC_STATUS_INVALID_BUFFER_LENGTH,
   ICC_STATUS_INVALID_PARAMS,
   ICC_STATUS_FLASH_WEAR_OUT_VIOLATION,
   ICC_STATUS_FLASH_CORRUPTION,
   ICC_STATUS_PROFILE_NOT_SELECTABLE_BY_BIOS,
   ICC_STATUS_TOO_LARGE_PROFILE_INDEX,
   ICC_STATUS_NO_SUCH_PROFILE_IN_FLASH,
   ICC_STATUS_CMD_NOT_SUPPORTED_AFTER_END_OF_POST,
   ICC_STATUS_NO_SUCH_RECORD,
   ICC_STATUS_RESERVED13,
   ICC_STATUS_RESERVED14,
   ICC_STATUS_TOO_LARGE_UOB_RECORD,
   ICC_STATUS_RESERVED16,
   ICC_STATUS_REGISTER_IS_LOCKED,
   ICC_STATUS_RESERVED18,
   ICC_STATUS_RESERVED19,
   ICC_STATUS_RESERVED20,
   ICC_STATUS_RESERVED21,
   ICC_STATUS_RESERVED22,
   ICC_STATUS_RESERVED23,
   ICC_STATUS_UOB_RECORD_IS_ALREADY_INVALID,
   ICC_STATUS_RESERVED25,
   ICC_STATUS_RESERVED26,
   ICC_STATUS_RESERVED27,
   ICC_STATUS_RANGE_VIOLATION_FREQ_TOO_HIGH,
   ICC_STATUS_RESERVED29,
   ICC_STATUS_RESERVED30,
   ICC_STATUS_RESERVED31,
   ICC_STATUS_RESERVED32,
   ICC_STATUS_RESERVED33,
   ICC_STATUS_RESERVED34,
   ICC_STATUS_RESERVED35,
   ICC_STATUS_RANGE_VIOLATION_FREQ_TOO_LOW,
   ICC_STATUS_RESERVED37,
   ICC_STATUS_RESERVED38,
   ICC_STATUS_RESERVED39,
   ICC_STATUS_RESERVED40,
   ICC_STATUS_RESERVED41,
   ICC_STATUS_RESERVED42,
   ICC_STATUS_RESERVED43,
   ICC_STATUS_SSC_MODE_CHANGE_NOT_SUPPORTED,
   ICC_STATUS_RESERVED45,
   ICC_STATUS_RESERVED46,
   ICC_STATUS_RESERVED47,
   ICC_STATUS_RESERVED48,
   ICC_STATUS_RESERVED49,
   ICC_STATUS_RESERVED50,
   ICC_STATUS_RESERVED51,
   ICC_STATUS_NO_SUCH_TARGET_ID,
   ICC_STATUS_NO_SUCH_REGISTER,
   ICC_STATUS_RESERVED54,
   ICC_STATUS_BUFFER_TOO_SMALL,
   ICC_STATUS_RESERVED56,
   ICC_STATUS_WAITING_FOR_POWER_CYCLE,
   ICC_STATUS_SURVIVABILITY_TABLE_ACCESS_VIOLATION,
   ICC_STATUS_SURVIVABILITY_TABLE_TOO_LARGE,
   ICC_STATUS_NO_SUCH_EID,
   ICC_STATUS_RESERVED61,
   ICC_STATUS_UNSPECIFIED_ERROR               = 0xFFFF
} ICC_MEI_CMD_STATUS;

typedef enum {
  ///
  /// Commands 0-15 not used on SKL PCH platform
  ///
  ICC_GET_PROFILE_CMD                       = 0x10,
  ICC_SET_PROFILE_CMD                       = 0x11,
  ICC_GET_REGISTERS_LOCK_CMD                = 0x12,
  ICC_SET_REGISTERS_LOCK_CMD                = 0x13,
  ICC_GET_CLOCK_CAPABILITIES_CMD            = 0x14,
  ICC_GET_CLOCK_RANGE_DEF_REC_CMD           = 0x15,
  ICC_GET_RECORD_CMD                        = 0x16,
  ICC_SET_RECORD_CMD                        = 0x17,
  ICC_GET_HSIO_SETTINGS_CMD                 = 0x18,
  ICC_SET_HSIO_SETTINGS_CMD                 = 0x19,
  ICC_GET_CLOCK_SETTINGS_CMD                = 0x1A,
  ICC_SET_CLOCK_SETTINGS_CMD                = 0x1B,
  ICC_OVERRIDE_SOFT_STRAP_CMD               = 0x27,
  ICC_GET_SOFT_STRAP_CONFIG_CMD             = 0x28
} ICC_MEI_COMMAND_ID;

typedef struct {
  UINT32              ApiVersion;
  ICC_MEI_COMMAND_ID  IccCommand;
  ICC_MEI_CMD_STATUS  IccResponse;
  UINT32              BufferLength;
  UINT32              Reserved;
} ICC_HEADER;

///
/// Get/Set ICC Register Lock
///
typedef struct {
  ICC_HEADER  Header;
} ICC_GET_REG_LOCK_MESSAGE;

typedef struct {
  ICC_HEADER  Header;
  UINT8       LockState;
  UINT8       LockFlags;
  UINT16      Reserved;
} ICC_GET_REG_LOCK_RESPONSE;

typedef union {
  ICC_GET_REG_LOCK_MESSAGE   message;
  ICC_GET_REG_LOCK_RESPONSE  response;
} ICC_GET_REG_LOCK_BUFFER;

typedef struct {
  ICC_HEADER  Header;
  UINT8       LockState;
  UINT8       PaddingA;
  UINT16      PaddingB;
} ICC_SET_REG_LOCK_MESSAGE;

typedef struct {
  ICC_HEADER  Header;
} ICC_SET_REG_LOCK_RESPONSE;

typedef union {
  ICC_SET_REG_LOCK_MESSAGE   message;
  ICC_SET_REG_LOCK_RESPONSE  response;
} ICC_SET_REG_LOCK_BUFFER;

///
/// Get/Set ICC Profile
///
#define MAX_NUM_ICC_PROFILES  16

typedef struct {
  ICC_HEADER  Header;
} ICC_GET_PROFILE_MESSAGE;

typedef struct {
  UINT8       IccProfileName[24];
  UINT8       IccProfileBase[24];
} ICC_PROFILE_DESC;

typedef struct {
  ICC_HEADER    Header;
  UINT8         IccNumOfProfiles;
  union {
    UINT8 Data;
    struct {
      UINT8     IccFailsafeProfile  : 4;
      UINT8     Reserved            : 3;
      UINT8     IccRuntimeSelect    : 1;
    } Fields;
  } OemParams;
  UINT8             IccProfileIndex;
  UINT8             Reserved;
  ICC_PROFILE_DESC  IccProfileDesc[MAX_NUM_ICC_PROFILES];
} ICC_GET_PROFILE_RESPONSE;

typedef union {
  ICC_GET_PROFILE_MESSAGE   message;
  ICC_GET_PROFILE_RESPONSE  response;
} ICC_GET_PROFILE_BUFFER;

typedef struct {
  ICC_HEADER  Header;
  UINT8       BiosIccProfile;
  UINT8       PaddingA;
  UINT16      PaddingB;
} ICC_SET_PROFILE_MESSAGE;

typedef struct {
  ICC_HEADER  Header;
} ICC_SET_PROFILE_RESPONSE;

typedef union {
  ICC_SET_PROFILE_MESSAGE   message;
  ICC_SET_PROFILE_RESPONSE  response;
} ICC_SET_PROFILE_BUFFER;

///
/// Get/Set ICC Clock Capabilites
///
typedef struct {
  ICC_HEADER  Header;
} ICC_GET_CLK_CAPABILITIES_MESSAGE;

typedef struct {
  ICC_HEADER  Header;
  UINT32      VersionNumber;
  UINT8       IccHwSku;
  UINT8       Reserved;
  UINT16      MaxSusramRecordSize;
  UINT64      IccSkuEnforcementTable;
  UINT32      IccBootStatusReport;
} ICC_GET_CLK_CAPABILITIES_RESPONSE;

typedef union {
  ICC_GET_CLK_CAPABILITIES_MESSAGE  message;
  ICC_GET_CLK_CAPABILITIES_RESPONSE response;
} ICC_GET_CLK_CAPABILITIES_BUFFER;

///
/// Get/Set Clock Settings
///
// Used for the FLAGS parameter of Get/Set Clock Settings
typedef union {
   UINT8 u;
   struct {
      UINT8 RoundDown   : 1;
      UINT8 Reserved    : 7;
   } Flags;
} ICC_CLOCK_SETTINGS_FLAGS;

///
/// Used for the CURRENT FLAGS parameter of Get/Set Clock Settings
///
typedef union {
   UINT16 u;
   struct {
      UINT16 Ratio              : 2;
      UINT16 Reserved           : 1;
      UINT16 AppliedOnWarmRst   : 1;
      UINT16 Type               : 2;
      UINT16 SetToDefault       : 1;
      UINT16 Disabled           : 1;
      UINT16 DynSettingsApplied : 1;
      UINT16 WarmRstPending     : 1;
      UINT16 PwrCyclePending    : 1;
      UINT16 Reserved1          : 5;
   } Flags;
} ICC_CLOCK_SETTINGS_CURRENT_FLAGS;

///
/// Used for the SUPPORTED FLAGS parameter of Get/Set Clock Settings
///
typedef union {
   UINT16 u;
   struct {
      UINT16 Ratio              : 1;
      UINT16 DownSpread         : 1;
      UINT16 UpSpread           : 1;
      UINT16 CenterSpread       : 1;
      UINT16 ChangeAllowed      : 1;
      UINT16 HaltAllowed        : 1;
      UINT16 PCIe               : 1;
      UINT16 Bclk               : 1;
      UINT16 Reserved           : 8;
   } Flags;
} ICC_CLOCK_SETTINGS_SUPPORTED_FLAGS;

///
/// Combined Request and Response structure for Get/Set Clock Settings
///
typedef struct {
   ICC_HEADER                         Header;
   UINT8                              ReqClock;
   UINT8                              SettingType;
   ICC_CLOCK_SETTINGS_FLAGS           Flags;
   UINT8                              Reserved;
   UINT32                             Freq;
   UINT32                             UserFreq;
   UINT32                             MaxFreq;
   UINT32                             MinFreq;
   UINT8                              SscMode;
   UINT8                              SscPercent;
   UINT8                              MaxSscPercent;
   UINT8                              Reserved1;
   ICC_CLOCK_SETTINGS_CURRENT_FLAGS   CurrentFlags;
   ICC_CLOCK_SETTINGS_SUPPORTED_FLAGS SupportFlags;
} ICC_GETSET_CLOCK_SETTINGS_REQRSP;

typedef union {
  ICC_GETSET_CLOCK_SETTINGS_REQRSP  message;
  ICC_GETSET_CLOCK_SETTINGS_REQRSP  response;
} ICC_GET_CLOCK_SETTINGS_BUFFER;

typedef union {
  ICC_GETSET_CLOCK_SETTINGS_REQRSP  message;
  ICC_GETSET_CLOCK_SETTINGS_REQRSP  response;
} ICC_SET_CLOCK_SETTINGS_BUFFER;

///
/// Defines clock settings constraints for next-level user record.
///
typedef union {
   UINT32 Dword[2];
   struct {
      UINT32 ClkFreqMax            :16;
      UINT32 ClkFreqMin            :16;
      UINT32 SscChangeAllowed      :1;
      UINT32 SscSprModeCtrlUp      :1;
      UINT32 SscSprModeCtrlCenter  :1;
      UINT32 SscSprModeCtrlDown    :1;
      UINT32 SscHaltAllowed        :1;
      UINT32 Reserved1             :3;
      UINT32 SscSprPercentMax      :8;
      UINT32 ClockUsage            :8;
      UINT32 Reserved2             :8;
   } Fields;
} ICC_SINGLE_CLK_RANGE_DEF;

typedef struct {
   ICC_SINGLE_CLK_RANGE_DEF   SingleClkRangeDef[2];
} ICC_CLK_RANGE_DEF_REC;

typedef struct {
  ICC_HEADER  Header;
  UINT8       Mode;
  UINT8       RequiredRecord;
  UINT16      Reserved;
} ICC_GET_CLOCK_RANGE_MESSAGE;

typedef struct {
  ICC_HEADER             Header;
  ICC_CLK_RANGE_DEF_REC  Crdr;
} ICC_GET_CLOCK_RANGE_RESPONSE;

typedef union {
  ICC_GET_CLOCK_RANGE_MESSAGE  message;
  ICC_GET_CLOCK_RANGE_RESPONSE  response;
} ICC_GET_CLOCK_RANGE_BUFFER;

#define ICC_RESPONSE_MODE_WAIT      0
#define ICC_RESPONSE_MODE_SKIP      1
#define ICC_LOCK_ACCESS_MODE_SET    0
#define ICC_LOCK_ACCESS_MODE_GET    1
#define ICC_LOCK_MASK_COUNT         255
#define WRITE_ICC_REG_BUNDLE_COUNT  1           ///< 1 bundle for 1 DWORD register write
#define ADDRESS_MASK_FIXED_DATA     0x00017F01  ///< Target ID = 7F (Aux), MWM = 1(16 bits)
#define WRITE_ICC_RECORD_FLAGS      0x00012010  ///< 16 byte record length, No param section, valid bit

typedef struct {
  UINT32 BundlesCnt :16; ///< Bundles Count - number of Address Mask entries
  UINT32 AU         :1;  ///< AU=1 -> All regisaters are Unlocked
  UINT32 Reserved   :15;
} ICC_REG_BUNDLES;

typedef struct {
  ICC_REG_BUNDLES RegBundles;
  UINT32          RegMask[ICC_LOCK_MASK_COUNT];
} ICC_LOCK_REGS_INFO;

typedef struct {
  ICC_HEADER          Header;
  UINT8               AccessMode;
  UINT8               Parameters;
  UINT8               Reserved[2];
  ICC_LOCK_REGS_INFO  LockRegInfo;
} ICC_LOCK_REGISTERS_MESSAGE;

typedef struct {
  ICC_HEADER          Header;
  UINT32              Reserved;
  ICC_LOCK_REGS_INFO  LockRegInfo;
} ICC_LOCK_REGISTERS_RESPONSE;

typedef union {
  ICC_LOCK_REGISTERS_MESSAGE  message;
  ICC_LOCK_REGISTERS_RESPONSE response;
} ICC_LOCK_REGISTERS_BUFFER;

typedef union {
  UINT32 AddressMaskData;
  struct {
    UINT32 MaskWidthModifier :2;
    UINT32 Offset            :6;
    UINT32 TargetId          :7;
    UINT32 Reserved          :1;
  } Fields;
} ICC_ADDRESS_MASK;

typedef struct {
  UINT32            RecordFlags;
  ICC_REG_BUNDLES   BundleCount;
  ICC_ADDRESS_MASK  AddressMask;
  UINT32            RegValue;
} ICC_RECORD_DWORD;

typedef struct {
  ICC_HEADER        Header;
  UINT16            Reserved;
  UINT8             Params;
  UINT8             Reserved1;
  ICC_RECORD_DWORD  RecordDword;
} ICC_WRITE_ICC_REG_DWORD_MESSAGE;

typedef struct {
  ICC_HEADER  Header;
  UINT16      BytesProcessed;
  UINT16      Reserved;
} ICC_WRITE_ICC_REG_DWORD_RESPONSE;

typedef union {
  ICC_WRITE_ICC_REG_DWORD_MESSAGE   message;
  ICC_WRITE_ICC_REG_DWORD_RESPONSE  response;
} ICC_WRITE_ICC_REG_BUFFER;

///
/// ICC Soft Strap Config
///
typedef enum {
  PcieOverrideNone    = 0,
  PcieOverride1x4     = 1,
  PcieOverride2x2     = 2,
  PcieOverride1x2_2x1 = 3,
  PcieOverride4x1     = 4
} PCIE_CONTROLLER_SOFTSTRAP_OVERRIDE;

///
/// Get Soft Strap Config
///
typedef struct {
  ICC_HEADER  Header;
} ICC_GET_SOFT_STRAP_CONFIG_CMD_REQ;

///
/// This is only a template. Data should be filled in runtime
///
typedef struct {
  ICC_HEADER  Header;
  /**
    Number of PCI-E ports to be configured
  **/
  UINT16                                     NumOfControllers;
  /**
    0 - NO OVERRIDE
    1 - CFG 1 x 4
    2 - CFG 2 x 2
    3 - CFG 1 x 2 2 x 1
    4 - CFG 4 x 1
  **/
  UINT8 ControllerConfig [0];
  ///
  /// UINT32 Reserved[4];
  ///
} ICC_GET_SOFT_STRAP_CONFIG_CMD_RESP;

#define ICC_OVERRIDE_SOFT_STRAP_CMD_REQ ICC_GET_SOFT_STRAP_CONFIG_CMD_RESP

typedef union {
  ICC_GET_SOFT_STRAP_CONFIG_CMD_REQ          Message;
  ICC_GET_SOFT_STRAP_CONFIG_CMD_RESP         Response;
} ICC_GET_SOFT_STRAP_CONFIG_CMD_BUFFER;

typedef struct {
  ICC_HEADER  Header;
} ICC_OVERRIDE_SOFT_STRAP_CMD_RESP;

typedef union {
  ICC_OVERRIDE_SOFT_STRAP_CMD_REQ          Message;
  ICC_OVERRIDE_SOFT_STRAP_CMD_RESP         Response;
} ICC_OVERRIDE_PCIE_SOFT_STRAP_CMD_BUFFER;
#pragma pack()

#endif
