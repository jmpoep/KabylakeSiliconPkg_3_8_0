/** @file
  Interface definition details for MBP during DXE phase.

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
#ifndef _MBP_DATA_PROTOCOL_H_
#define _MBP_DATA_PROTOCOL_H_
#include <CoreBiosMsg.h>

///
/// MBP Protocol for DXE phase
///

///
/// Revision 1:  Original version
///
#define MBP_DATA_PROTOCOL_REVISION_1  1

#define MBP_ITEM_FLAG_SENSITIVE     BIT0  ///< Item contains sensitive data.  Do not store in flash.
#define MBP_ITEM_FLAG_RUNTIME       BIT1  ///< Item is generated at runtime.  Do not store in flash.
#define MBP_ITEM_FLAG_RSVD2         BIT2  ///< Reserved for future use.
#define MBP_ITEM_FLAG_RSVD3         BIT3  ///< Reserved for future use.
#define MBP_ITEM_FLAG_RSVD4         BIT4  ///< Reserved for future use.
#define MBP_ITEM_FLAG_RSVD5         BIT5  ///< Reserved for future use.
#define MBP_ITEM_FLAG_RSVD6         BIT6  ///< Reserved for future use.
#define MBP_ITEM_FLAG_RSVD7         BIT7  ///< Reserved for future use.

#pragma pack(push, 1)

///
/// Common MBP types
///
typedef union _MBP_HEADER {
  UINT32 Data;
  struct {
    UINT32 MbpSize    : 8;  ///< Byte 0 - MBP Size in DW including Header
    UINT32 NumEntries : 8;  ///< Byte 1 - Number of Entries (Data Items) in MBP
    UINT32 Flags      : 8;  ///< Byte 2 - Flags
    UINT32 Rsvd       : 8;  ///< Byte 3 - Reserved
  } Fields;
} MBP_HEADER;

typedef union _MBP_ITEM_HEADER {
  UINT32 Data;
  struct {
    UINT32 AppId  : 8; ///< Byte 0 - Application ID
    UINT32 ItemId : 8; ///< Byte 1 - Item ID
    UINT32 Length : 8; ///< Byte 2 - Length in DW
    UINT32 Flags  : 8; ///< Byte 3 - Flags
  } Fields;
} MBP_ITEM_HEADER;

///
/// MBP items
///
typedef struct _MBP_FW_VERSION_NAME {
  UINT32  MajorVersion : 16;
  UINT32  MinorVersion : 16;
  UINT32  HotfixVersion : 16;
  UINT32  BuildVersion : 16;
} MBP_FW_VERSION_NAME;

typedef struct _ICC_PROFILE_SELECTION_TYPE
{
   UINT8            IccProfileId          :4;
   UINT8            Reserved              :3;
   UINT8            IccProfileSelectedBy  :1;
} ICC_PROFILE_SELECTION_TYPE;

typedef struct _ICC_PROFILE_INDEX_TYPE
{
   UINT8            IccProfileId   :4;
   UINT8            Reserved       :4;
} ICC_PROFILE_INDEX_TYPE;

typedef struct
{
   UINT8                    IccNumOfProfiles;
   ICC_PROFILE_INDEX_TYPE   IccProfileIndex;
   UINT8                    IccProfileChangeable;
   UINT8                    IccLockMaskType;
} MBP_ICC_PROFILE;

typedef struct _MBP_FW_CAPS_SKU {
  MEFWCAPS_SKU  FwCapabilities;
  BOOLEAN       Available;
  UINT8         Reserved[3];
} MBP_FW_CAPS_SKU;

typedef struct _MBP_FW_FEATURES_STATE {
  MEFWCAPS_SKU  FwFeatures;
  BOOLEAN       Available;
  UINT8         Reserved[3];
} MBP_FW_FEATURES_STATE;

typedef struct _MBP_ROM_BIST_DATA {
  UINT16  DeviceId;
  UINT16  FuseTestFlags;
  UINT32  UMCHID[4];
} MBP_ROM_BIST_DATA;

typedef struct _MBP_PLATFORM_KEY {
  UINT32  Key[8];
} MBP_PLATFORM_KEY;

typedef struct _MBP_PLAT_TYPE {
  PLATFORM_TYPE_RULE_DATA RuleData;
  BOOLEAN                 Available;
  UINT8                   Reserved[3];
} MBP_PLAT_TYPE;

typedef union _HWA_DATA {
  UINT32  Raw;
  struct {
    UINT32  MediaTablePush : 1;
    UINT32  Reserved : 31;
  } Fields;
} HWA_DATA;

typedef struct _MBP_HWA_REQ {
  HWA_DATA Data;
  BOOLEAN  Available;
  UINT8    Reserved[3];
} MBP_HWA_REQ;

typedef struct _MBP_PERF_DATA {
  UINT32  PwrbtnMrst;
  UINT32  MrstPltrst;
  UINT32  PltrstCpurst;
} MBP_PERF_DATA;

typedef struct _PLAT_BOOT_PERF_DATA {
  MBP_PERF_DATA MbpPerfData;
  BOOLEAN       Available;
  UINT8         Reserved[3];
} PLAT_BOOT_PERF_DATA;

typedef struct _MBP_NFC_DATA {
  UINT32 DeviceType :2;
  UINT32 Reserved : 30;
} MBP_NFC_DATA;

typedef struct _MBP_NFC_SUPPORT {
  MBP_NFC_DATA   NfcData;
  BOOLEAN        Available;
  UINT8          Reserved[3];
} MBP_NFC_SUPPORT;

typedef struct _MBP_ME_UNCONF_ON_RTC_DATA {
  UINT32 DisUnconfigOnRtcClearState :1;
  UINT32 Reserved : 31;
} MBP_ME_UNCONF_ON_RTC_DATA;

typedef struct _MBP_ME_UNCONF_ON_RTC_STATE {
  MBP_ME_UNCONF_ON_RTC_DATA   UnconfigOnRtcClearData;
  BOOLEAN                     Available;
  UINT8                       Reserved[3];
} MBP_ME_UNCONF_ON_RTC_STATE;

///
/// ME BIOS Payload structure containing insensitive data only
///
typedef struct {
  MBP_FW_VERSION_NAME        FwVersionName;
  MBP_FW_CAPS_SKU            FwCapsSku;
  MBP_FW_FEATURES_STATE      FwFeaturesState;
  MBP_PLAT_TYPE              FwPlatType;
  MBP_ICC_PROFILE            IccProfile;
  UINT32                     MFSIntegrity;
  MBP_HWA_REQ                HwaRequest;
  PLAT_BOOT_PERF_DATA        PlatBootPerfData;
  MBP_NFC_SUPPORT            NfcSupport;
  MBP_ME_UNCONF_ON_RTC_STATE UnconfigOnRtcClearState;
} ME_BIOS_PAYLOAD;

///
/// All items which can't be available when 3rd part OPROMs/drivers are loaded
/// must be added to below structure only
///
typedef struct {
  MBP_ROM_BIST_DATA          RomBistData;
  MBP_PLATFORM_KEY           PlatformKey;
} ME_BIOS_PAYLOAD_SENSITIVE;

#pragma pack(pop)

#endif
