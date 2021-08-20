/** @file
  Header file for the EVI Callback Init PEIM

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2016 Intel Corporation.

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
#ifndef _EV_LOADER_PEIM_H_
#define _EV_LOADER_PEIM_H_

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/ReadOnlyVariable2.h>
#include "MrcTypes.h"
#include "SsaCallbackPeim.h"
#include "MrcSsaServices.h"

//
// PPI GUID definition.
//
extern EFI_GUID gSsaBiosCallBacksPpiGuid;
extern EFI_GUID gSsaBiosVariablesGuid;
extern EFI_GUID gSsaBiosResultsGuid;

typedef struct SSA_BIOS_SERVICES_LOADER_STATE {
  MRC_OEM_STATUS_COMMAND      RunCheckpoint;
  BOOLEAN                     LoadFromTarget;
  BOOLEAN                     LoaderPresenceCheck;
  VOID *                      SysConfig;
} SSA_BIOS_SERVICES_LOADER_STATE;

#define VAR_BUFFER_SIZE                          2048

#define MAX_NUM_CONFIGS                          20
#define MAX_NUM_CHUNKS                           9999

#define SYS_CONFIG_NAME                          L"syscg"
#define TOOL_BINARY_NAME                         L"toolh"

#pragma pack(push, 1)

typedef struct SSA_BIOS_SYS_CONFIG_HEADER {
  UINT32         SystemConfigRevision;
  UINT32         ToolSize;
  UINT32         PostCode;
  UINT32         PrintLevel;
  UINT32         ConfigCount;
} SSA_BIOS_SYS_CONFIG_HEADER;

#pragma pack(pop)

#define VAR_NAME_LENGTH 5
#define VAR_NAME_SIZE (sizeof (CHAR16) * VAR_NAME_LENGTH)

#define VAR_NULL_NAME_LENGTH VAR_NAME_LENGTH + 1     // length as a null terminated string
#define VAR_NULL_NAME_SIZE (sizeof (CHAR16) * VAR_NULL_NAME_LENGTH)

#define NULL_STRING L""

//Serial port definitions
#define SSA_LOADER_COM_TRANSMIT_HOLDING          (0x00)

#define SSA_LOADER_COM_LINE_STATUS               (0x05)
#define SSA_LOADER_COM_TRANS_HOLDING_REG_EMPTY   (0x20)
#define SSA_LOADER_COM_BREAK_INTERRUPT           (0x10)
#define SSA_LOADER_COM_DATA_READY                (0x01)
#define SSA_LOADER_COM_RECEIVER_BUFFER           (0x00)
#define SSA_LOADER_COM_EOF                       (0xFF)
#define SSA_LOADER_COM_DELETE                    (0x7F)
#define SSA_LOADER_COM_BACKSPACE                 (0x08)

#define SSA_LOADER_COM1_BASE                     (0x3f8)
#define SSA_LOADER_COM2_BASE                     (0x2f8)
#define SSA_LOADER_COM3_BASE                     (0x3e8)
#define SSA_LOADER_COM4_BASE                     (0x2e8)

#define SSA_LOADER_GLOBALCOMPORT                 (SSA_LOADER_COM1_BASE)

#define SSA_LOADER_CHAR_LF                       (0x0A)
#define SSA_LOADER_CHAR_CR                       (0x0D)

#define SSA_LOADER_SKIP_TEST_WAIT_STEPS          10
#define SSA_LOADER_SKIP_TEST_WAIT_STEP_SIZE_USEC 500000
#define SSA_LOADER_MESSAGE_WAIT_STEPS            4

#endif //_EV_LOADER_PEIM_H_
