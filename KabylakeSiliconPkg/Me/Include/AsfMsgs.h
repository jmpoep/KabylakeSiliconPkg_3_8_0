/** @file
  AMT/ASF Messages

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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

#ifndef _ASF_MSGS_H
#define _ASF_MSGS_H

#include <AlertStandardFormat.h>

#pragma pack(1)


//
// Always define the whole ASF message structure so you can use the macro for ByteCount calculation
//
#define ASF_MESSAGE_BYTE_COUNT_MAP(a) (sizeof(a)-2)

///
/// Abstract ASF message header. This header is part of HECI message sent from BIOS to AMT/ASF ME Client
///
typedef union {
  UINT32  Data;
  struct {
    UINT32  Command       : 8;
    UINT32  ByteCount     : 8;
    UINT32  SubCommand    : 8;
    UINT32  VersionNumber : 8;
  } Fields;
} ASF_MESSAGE_HEADER;

//
// Management Control Command Definitions
//

///
/// Start Watchdog Timer
///
#define ASF_START_BIOS_WDT  0
#define ASF_START_OS_WDT    1

typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;
  UINT8                TimeoutLow;
  UINT8                TimeoutHigh;
  UINT8                EventSensorType;
  UINT8                EventType;
  UINT8                EventOffset;
  UINT8                EventSourceType;
  UINT8                EventSeverity;
  UINT8                SensorDevice;
  UINT8                SensorNumber;
  UINT8                Entity;
  UINT8                EntityInstance;
  UINT8                EventData[5];
} ASF_START_WDT;

///
/// Stop Watchdog Timer
///
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;
} ASF_STOP_WDT;


//
// ASF Configuration Command Definitions
//

//
// Clear Boot Options
//
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;
} CLEAR_BOOT_OPTIONS;

//
// Return Boot Options
//
typedef struct {
  UINT8   SubCommand;
  UINT8   Version;
  UINT32  IanaId;
  UINT8   SpecialCommand;
  UINT16  SpecialCommandParam;
  UINT16  BootOptions;
  UINT16  OemParameters;
} ASF_BOOT_OPTIONS;

typedef struct {
  UINT8                 Command;
  UINT8                 ByteCount;
  ASF_BOOT_OPTIONS      AsfBootOptions;
} GET_BOOT_OPTIONS_RESPONSE;


typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;
} GET_BOOT_OPTIONS;

//
// Get Remote Secure Erase Password
//
#define RSE_PASSWORD_MAX_LENGTH 32

typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;
  UINT16               PasswordLength;
  CHAR8                Password[RSE_PASSWORD_MAX_LENGTH];
} GET_RSE_PASSWORD_RESPONSE;

typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;
} GET_RSE_PASSWORD;

//
// Report BIOS Status
//
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;
  UINT16               BiosStatus;
  UINT16               StatusCause;
} REPORT_BIOS_STATUS;


//
// Messaging Command Definitions
//

//
// Push Progress Code
//
typedef struct {
  UINT8 SubCommand;
  UINT8 Version;
  UINT8 EventSensorType;
  UINT8 EventType;
  UINT8 EventOffset;
  UINT8 EventSourceType;
  UINT8 EventSeverity;
  UINT8 SensorDevice;
  UINT8 SensorNumber;
  UINT8 Entity;
  UINT8 EntityInstance;
  UINT8 EventData1;
  UINT8 EventData2;
} ASF_MESSAGE;

typedef struct {
  UINT8           Command;
  UINT8           ByteCount;
  ASF_MESSAGE     AsfMessage;
  UINT8           EventData[6];
} HECI_ASF_PUSH_PROGRESS_CODE;

#define HECI_ASF_PUSH_PROGRESS_CODE_LENGTH  0x15

typedef struct {
  ASF_FRAMEWORK_MESSAGE_TYPE      MessageType;
  ASF_MESSAGE                     Message;
} ASF_FRAMEWORK_MESSAGE;

typedef struct {
  ASF_FRAMEWORK_MESSAGE_TYPE      MessageType;
  EFI_STATUS_CODE_VALUE           StatusCodeValue;
} ASF_DATA_HUB_MAP;

//
// PET Alert
//
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;
  UINT8                EventSensorType;
  UINT8                EventType;
  UINT8                EventOffset;
  UINT8                EventSourceType;
  UINT8                EventSeverity;
  UINT8                SensorDevice;
  UINT8                Sensornumber;
  UINT8                Entity;
  UINT8                EntityInstance;
  UINT8                EventData1;
  UINT8                EventData2;
  UINT8                EventData3;
  UINT8                EventData4;
  UINT8                EventData5;
} PET_ALERT;


//
// KVM Command Definitions
//

///
/// AMT Query KVM related timer definition
///
#define KVM_QUERY_RESPONSE  0x02
#define KVM_STALL_1_SECOND  1000000   ///< Stall 1 second
#define KVM_MAX_WAIT_TIME   (60 * 8)  ///< 8 Mins

///
/// Query KVM Response Type
///
typedef enum {
  KvmSessionEstablished  = 1,
  KvmSessionCancelled
} RESPONSE_CODE;

///
/// Query KVM Response Structure
///
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;
  UINT32               ResponseCode;
} AMT_QUERY_KVM_RESPONSE;

///
/// Query KVM Type
///
typedef enum {
  QueryRequest            = 0,
  CancelRequest
} QUERY_TYPE;

///
/// Query KVM Request Structure
///
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;
  UINT32               QueryType;
} AMT_QUERY_KVM;

///
/// Query KVM Union Buffer
///
typedef union {
  AMT_QUERY_KVM          Request;
  AMT_QUERY_KVM_RESPONSE Response;
} AMT_QUERY_KVM_BUFFER;

#pragma pack()

#endif // _ASF_MSGS_H
