/** @file
  BIOS SSA loader main definitions.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

#ifndef __EV_ITP_DOWNLOAD_AGENT_H__
#define __EV_ITP_DOWNLOAD_AGENT_H__

#ifndef MRC_MINIBIOS_BUILD
#include <Library/DebugLib.h>
#endif
#include <MrcTypes.h>
#include <MrcSsaServices.h>

#ifndef EV_LOADER_ENABLE_DEBUG_PRINTS
#define EV_LOADER_PRINT(LEVEL, FORMAT, ...)
#else
#define EV_LOADER_PRINT(LEVEL, FORMAT, ...) DebugPrint(LEVEL, FORMAT, ##__VA_ARGS__)
#endif

#ifdef MRC_MINIBIOS_BUILD
#ifndef DebugPrint
#define DebugPrint
#endif
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4214)
#endif

//
// EV agent command list
//
#define MRC_EVAGENT_CMD_PING                        0x0
#define MRC_EVAGENT_CMD_GET_CALLBACK_REV            0x1
#define MRC_EVAGENT_CMD_GET_TOOL_BUFFER             0x2
#define MRC_EVAGENT_CMD_LOAD_TOOL                   0x3
#define MRC_EVAGENT_CMD_UNLOAD_TOOL                 0x4
#define MRC_EVAGENT_CMD_GET_INPUT_BUFFER            0x5
#define MRC_EVAGENT_CMD_FREE_MEMORY                 0x6
#define MRC_EVAGENT_CMD_RUN_EV_TOOL                 0x7
#define MRC_EVAGENT_CMD_EXIT                        0x8
#define MRC_EVAGENT_CMD_GET_AGENT_VERSION           0x9
#define MRC_EVAGENT_CMD_GET_DLL_VERSION             0xA
#define MRC_EVAGENT_CMD_FLUSH_CACHE                 0xB
#define MRC_EVAGENT_CMD_FREE_RESULTS                0x11

//
// EV agent status and error code
//
#define MRC_EVAGENT_PENDING_CMD                     1
#define MRC_EVAGENT_NO_PENDING_CMD                  0
#define MRC_EVAGENT_STATUS_READY                    0
#define MRC_EVAGENT_STATUS_BUSY                     1

#define MRC_EVAGENT_CMD_NO_ERROR                    0x0
#define MRC_EVAGENT_CMD_ERROR_UNKNOWN_CMD           0x1
#define MRC_EVAGENT_CMD_ERROR_MALLOC_FAIL           0x2
#define MRC_EVAGENT_CMD_ERROR_INVALID_TOOL_HANDLE   0x3
#define MRC_EVAGENT_CMD_ERROR_INVALID_MEMORY_HANDLE 0x4

//
// Definition of the EV agent command register
//
typedef union {
  struct{
    UINT32 status                    :1;
    UINT32 error_code                :6;
    UINT32 command_pending_execution :1;
    UINT32 command_opcode            :8;
    UINT32 reserved                  :16;
  } Bits;
  UINT32 Data;
} MRC_EV_AGENT_CMD_STRUCT;

MrcStatus
EvItpDownloadCmd (
  SSA_BIOS_SERVICES_PPI *SsaServicesPpi,
  VOID                  *CheckpointData
  );

typedef EFI_STATUS (EvToolEntryPoint) (SSA_BIOS_SERVICES_PPI *SsaBiosServicesPpi, void *Configuration);

#ifndef TOOL_MAJOR_VERSION
  #define TOOL_MAJOR_VERSION 0
#endif
#ifndef TOOL_MINOR_VERSION
  #define TOOL_MINOR_VERSION 0
#endif
#ifndef TOOL_REVISION
  #define TOOL_REVISION 0
#endif

#endif //__EV_ITP_DOWNLOAD_AGENT_H__
