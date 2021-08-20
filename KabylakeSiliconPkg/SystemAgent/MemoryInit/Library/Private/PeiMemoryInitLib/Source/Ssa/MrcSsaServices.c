/** @file
  This file contains the implementation of the BIOS version of the SSA services PPI.

  This version contains code for both client and server implementations.

  For Client:
    - Delete include of BiosSsaMemoryServerConfig.h and BiosSsaMemoryDdrtConfig.h.
    - Delete definitions of SSA_REVISION_MEMORY_SERVER and SSA_REVISION_MEMORY_DDRT.
    - Delete declarations of SsaMemoryServerConfig and SsaMemoryDdrtConfig.
    - Replace SsaMemoryServerConfig and SsaMemoryDdrtConfig field values in SsaBiosServicesPpi with NULL.

  For Server:
    - Delete include of BiosSsaMemoryClientConfig.h.
    - Delete definition of SSA_REVISION_MEMORY_CLIENT.
    - Delete declaration of SsaMemoryClientConfig.
    - Replace SsaMemoryClientConfig field value in SsaBiosServicesPpi with NULL.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2014 Intel Corporation.

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

#include "SsaBios.h"
#include "MrcSsaServices.h"

#ifdef SSA_FLAG
#include "BiosSsaCommonConfig.h"
#include "BiosSsaResultsConfig.h"
#include "BiosSsaMemoryConfig.h"
#include "BiosSsaMemoryClientConfig.h"
#include "BiosSsaMemoryServerConfig.h"
#include "BiosSsaMemoryDdrtConfig.h"

// PPI/API revisions - Major.Minor.Release.Build
#define SSA_REVISION_BIOS          ((0x01 << 24) | (0x00 << 16) | (0x00 << 8) | 0x00)
#define SSA_REVISION_COMMON        ((0x01 << 24) | (0x00 << 16) | (0x00 << 8) | 0x00)
#define SSA_REVISION_RESULT        ((0x01 << 24) | (0x00 << 16) | (0x00 << 8) | 0x00)
#define SSA_REVISION_MEMORY        ((0x01 << 24) | (0x00 << 16) | (0x00 << 8) | 0x00)
#define SSA_REVISION_MEMORY_CLIENT ((0x01 << 24) | (0x00 << 16) | (0x00 << 8) | 0x00)
#define SSA_REVISION_MEMORY_SERVER ((0x01 << 24) | (0x00 << 16) | (0x00 << 8) | 0x00)
#define SSA_REVISION_MEMORY_DDRT   ((0x01 << 24) | (0x00 << 16) | (0x00 << 8) | 0x00)

GLOBAL_REMOVE_IF_UNREFERENCED SSA_CONST SSA_COMMON_CONFIG SsaCommonConfig = {
  SSA_REVISION_COMMON,
  NULL,                   // MrcData
  NULL,                   // HookBuffer
  BiosReadMem,
  BiosWriteMem,
  BiosReadIo,
  BiosWriteIo,
  BiosReadPci,
  BiosWritePci,
  BiosGetBaseAddress,
  BiosMalloc,
  BiosFree,
  DEBUG_ERROR,
  BiosSsaDebugPrint,
  BiosWait,
  BiosSaveToBdat,
  BiosRegisterHookHandler,
  BiosRunHook,
  BiosSaveDataPointer,
  BiosRestoreDataPointer,
  BiosDisableWatchdogTimer,
  BiosGetTimestamp
};

GLOBAL_REMOVE_IF_UNREFERENCED SSA_CONST SSA_RESULTS_CONFIG SsaResultsConfig = {
  SSA_REVISION_RESULT,
  NULL,                   // Results buffer
  BiosCreateResultBuffer,
  BiosSetRevision,
  BiosGetRevision,
  BiosSetMetadataType,
  BiosGetMetadataType,
  BiosGetMetadataSize,
  BiosGetMetadata,
  BiosSetResultElementType,
  BiosGetResultElementType,
  BiosGetResultElementSize,
  BiosGetResultElementCapacity,
  BiosGetResultElementCount,
  BiosGetNextResultElement,
  BiosSetExplicitTransferMode,
  BiosGetExplicitTransferMode,
  BiosPushResults
};

GLOBAL_REMOVE_IF_UNREFERENCED SSA_CONST SSA_MEMORY_CONFIG SsaMemoryConfig = {
  SSA_REVISION_MEMORY,
  NULL,                   // MrcData
  BiosGetSystemInfo,
  BiosGetMemVoltage,
  BiosSetMemVoltage,
  BiosGetMemTemp,
  BiosGetControllerBitMask,
  BiosGetChannelBitMask,
  BiosGetDimmBitMask,
  BiosGetRankInDimm,
  BiosGetLogicalRank,
  BiosGetDimmInfo,
  BiosGetDimmUniqueModuleId,
  BiosGetSpdData,
  BiosJedecReset,
  BiosIoReset,
  BiosGetMarginParamSpecificity,
  BiosInitMarginParam,
  BiosGetMarginParamLimits,
  BiosSetMarginParamOffset,
  BiosSetZQCalConfig,
  BiosSetRCompUpdateConfig,
  BiosSetPageOpenConfig,
  BiosScrubMemory,
  BiosInitCpgc
};

#ifdef SSA_CLIENT_FLAG
GLOBAL_REMOVE_IF_UNREFERENCED SSA_CONST SSA_MEMORY_CLIENT_CONFIG SsaMemoryClientConfig = {
  SSA_REVISION_MEMORY_CLIENT,
  BiosClientGetCpgcInfo,
  BiosClientSetAddressAsData,
  BiosClientSetDqdbPattern,
  BiosClientGetDqdbPattern,
  BiosClientSetDqdbIndexes,
  BiosClientSetDqdbEccDataSource,
  BiosClientSetDqdbUniseqMode,
  BiosClientSetDqdbUniseqWrSeed,
  BiosClientSetDqdbUniseqRdSeed,
  BiosClientGetDqdbUniseqWrSeed,
  BiosClientGetDqdbUniseqRdSeed,
  BiosClientSetDqdbUniseqLmn,
  BiosClientSetDqdbUniseqLfsrConfig,
  BiosClientSetDqdbInvertDcConfig,
  BiosClientSetCadbConfig,
  BiosClientSetCadbPattern,
  BiosClientSetCadbUniseqMode,
  BiosClientSetCadbUniseqSeed,
  BiosClientSetCadbUniseqLmn,
  BiosClientSetDummyReadLmn,
  BiosClientSetDummyReadBankMask,
  BiosClientSetDummyReadRanks,
  BiosClientSetSubseqConfig,
  BiosClientSetSubseqOffsetConfig,
  BiosClientSetSeqConfig,
  BiosClientSetLoopCount,
  BiosClientSetSeqAddrConfig,
  BiosClientSetSeqStartAddr,
  BiosClientSetSeqWrapAddr,
  BiosClientSetSeqAddrInc,
  BiosClientSetSeqRankMap,
  BiosClientSetSeqBankMap,
  BiosClientSetSeqRowAddrSwizzle,
  BiosClientGetSeqState,
  BiosClientSetStopMode,
  BiosClientSetErrorCounterMode,
  BiosClientSetLaneValidationMask,
  BiosClientSetChunkValidationMask,
  BiosClientSetCachelineValidationMask,
  BiosClientGetLaneErrorStatus,
  BiosClientGetChunkErrorStatus,
  BiosClientGetRankErrorStatus,
  BiosClientGetErrorAddress,
  BiosClientGetErrorCount,
  BiosClientSetDqdbErrorCaptureConfig,
  BiosClientGetDqdbErrorCaptureStatus,
  BiosClientSetLocalTestControl,
  BiosClientSetGlobalTestControl,
  BiosClientGetTestDone,
  BiosClientSetScramblerConfig,
  BiosClientSetSelfRefreshConfig,
  BiosClientSetRefreshOverride,
  BiosClientSetZQCalOverride,
  BiosClientSetOdtOverride,
  BiosClientSetCkeOverride
};
#endif

#ifdef SSA_SERVER_FLAG
GLOBAL_REMOVE_IF_UNREFERENCED SSA_CONST SSA_MEMORY_SERVER_CONFIG SsaMemoryServerConfig = {
  SSA_REVISION_MEMORY_SERVER,
  BiosServerGetCpgcInfo,
  BiosServerGetCsEncoding,
  BiosServerGet3dsRankPerCs,
  BiosServerSetCreditWaitConfig,
  BiosServerSetWpqInOrderConfig,
  BiosServerSetMultipleWrCreditConfig,
  BiosServerSetCpgcLockState,
  BiosServerSetDqdbPattern,
  BiosServerGetDqdbPattern,
  BiosServerSetDqdbIndexes,
  BiosServerSetDqdbEccDataSource,
  BiosServerSetDqdbUniseqMode,
  BiosServerSetDqdbUniseqWrSeed,
  BiosServerSetDqdbUniseqRdSeed,
  BiosServerGetDqdbUniseqWrSeed,
  BiosServerGetDqdbUniseqRdSeed,
  BiosServerSetDqdbUniseqLmn,
  BiosServerSetDqdbUniseqLfsrConfig,
  BiosServerSetDqdbInvertDcConfig,
  BiosServerSetCadbConfig,
  BiosServerSetCadbPattern,
  BiosServerSetCadbUniseqMode,
  BiosServerSetCadbUniseqSeed,
  BiosServerSetCadbUniseqLmn,
  BiosServerSetDummyReadLmn,
  BiosServerSetDummyReadBankMask,
  BiosServerSetSubseqConfig,
  BiosServerSetSubseqOffsetConfig,
  BiosServerSetSeqConfig,
  BiosServerSetLoopCount,
  BiosServerSetSeqAddrConfig,
  BiosServerSetSeqStartAddr,
  BiosServerSetSeqWrapAddr,
  BiosServerSetSeqAddrInc,
  BiosServerSetSeqRankMap,
  BiosServerSetSeqRowAddrSwizzle,
  BiosServerGetSeqState,
  BiosServerSetStopMode,
  BiosServerSetErrorCounterMode,
  BiosServerSetLaneValidationMask,
  BiosServerSetChunkValidationMask,
  BiosServerSetCachelineValidationMask,
  BiosServerGetLaneErrorStatus,
  BiosServerGetChunkErrorStatus,
  BiosServerGetRankErrorStatus,
  BiosServerGetErrorAddress,
  BiosServerGetErrorCount,
  BiosServerSetDqdbErrorCaptureConfig,
  BiosServerGetDqdbErrorCaptureStatus,
  BiosServerSetLocalTestControl,
  BiosServerSetGlobalTestControl,
  BiosServerSetAddrConfig,
  BiosServerGetTestDone,
  BiosServerSetScramblerConfig,
  BiosServerSetSelfRefreshConfig,
  BiosServerSetRefreshOverride,
  BiosServerSetZQCalOverride,
  BiosServerSetOdtOverride,
  BiosServerSetCkeOverride
};

GLOBAL_REMOVE_IF_UNREFERENCED SSA_CONST SSA_MEMORY_DDRT_CONFIG SsaMemoryDdrtConfig = {
  SSA_REVISION_MEMORY_DDRT,
  BiosSetEridValidationMask,
  BiosGetEridErrorStatus,
  BiosGetEridErrorCount,
  BiosSetEridPattern,
  BiosSetEridTrainingConfig,
  BiosSetAepDimmTrainingMode
};
#endif

GLOBAL_REMOVE_IF_UNREFERENCED SSA_CONST SSA_BIOS_SERVICES_PPI SsaBiosServicesPpi = {
  SSA_REVISION_BIOS,
  (SSA_COMMON_CONFIG *) &SsaCommonConfig,
  (SSA_RESULTS_CONFIG *) &SsaResultsConfig,
  (SSA_MEMORY_CONFIG *) &SsaMemoryConfig,
#ifdef SSA_CLIENT_FLAG
  (SSA_MEMORY_CLIENT_CONFIG *) &SsaMemoryClientConfig,
#else
  NULL,
#endif
#ifdef SSA_SERVER_FLAG
  (SSA_MEMORY_SERVER_CONFIG *) &SsaMemoryServerConfig,
  (SSA_MEMORY_DDRT_CONFIG *) &SsaMemoryDdrtConfig
#else
  NULL,
  NULL
#endif
};

#endif // SSA_FLAG
// end file MrcSsaServices.c
