/** @file
  Symbol definitions and macros.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

@par Specification
**/

#ifndef _DCTT_SYMBOL_H_
#define _DCTT_SYMBOL_H_
#include "DcttMString.h"
#include "DcttSetContainer.h"
#include "DcttSwizzleFunctions.h"

#define Symbol_Execute(pSymbol, pSymbolParams, pSequenceParams, pGlobalParams) (pSymbol)->symbolFunction((pSymbol), (pSymbolParams), (pSequenceParams), (pGlobalParams))

#define _Symbol_GetParseStr(pSymbol) (pSymbol)->symbolStr

#define _Symbol_GetDirection(pSymbolParams) ((pSymbolParams)->Direction)

#define TestParameters_GetNumberErrors(pTestParams) ((pTestParams)->rankErrors[0].channelErrors)

#define TestParameters_GetNumberErrorsCh(pTestParams, channel) ((pTestParams)->rankErrors[0].channelErrors[channel])

#define TestParameters_GetNumberErrorsRankCh(pTestParams, channel, rank) ((pTestParams)->rankErrors[rank].channelErrors[channel])

#define TestParameters_GetRankErrors(pTestParams) ((pTestParams)->rankErrors)

#define TestParameters_GetErrAddresssContainer(pTestParams) ((pTestParams)->ErrorAddresses)

#define TestParameters_SetErrAddresssContainer(pTestParams, ErrAddresssContainer) ((pTestParams)->ErrorAddresses = (ErrAddresssContainer))

#define TestParameters_GetDirection(pTestParams) ((pTestParams)->currentDirection)

#define TestParameters_SetDirection(pTestParams, direction) ((pTestParams)->currentDirection) = direction

#define TestParameters_SetDcttHandle(pTestParams, pHandle) ((pTestParams)->DcttMain) = pHandle

#define TestParameters_GetDcttHandle(pTestParams) ((pTestParams)->DcttMain)

#define TestParameters_SetConfig(pTestParams, pConfig) ((pTestParams)->config) = pConfig

#define TestParameters_GetConfig(pTestParams) ((pTestParams)->config)

#define SymbolSeqParameters_GetSubsequence(pSequenceParams) (pSequenceParams)->currentSubsequence

#define SymbolSeqParameters_IncrementSubsequence(pSequenceParams) ((pSequenceParams)->currentSubsequence = (pSequenceParams)->currentSubsequence + 1)

#define SymbolSeqParameters_ResetSubsequence(pSequenceParams) ((pSequenceParams)->currentSubsequence = 0)

#define SymbolSeqParameters_ResetSequenceRunnerType(pSequenceParams) ((pSequenceParams)->sequenceRunnerType = ST_NORMAL_RUN)

#define SymbolSeqParameters_SetSequenceRunnerType(pSequenceParams, runnerType) ((pSequenceParams)->sequenceRunnerType = runnerType)

#define SymbolSeqParameters_GetSequenceRunnerType(pSequenceParams) ((pSequenceParams)->sequenceRunnerType)

#define SymbolSeqParameters_GetDelay(pSequenceParams) ((pSequenceParams)->delay)

#define SymbolSeqParameters_SetDelay(pSequenceParams,Delay) ((pSequenceParams)->delay = (Delay))

#define SymbolExecParameters_GetDirection(pSymbolParams) ((pSymbolParams)->Direction)

#define SymbolExecParameters_SetDirection(pSymbolParams,direction) ((pSymbolParams)->Direction = direction)

#define SymbolExecParameters_SetNumberRepetitions(pSymbolParams, repetitions) ((pSymbolParams)->numberRepetitions = repetitions)

#define SymbolExecParameters_GetNumberRepetitions(pSymbolParams) ((pSymbolParams)->numberRepetitions)

#define SymbolExecParameters_SetBaseCellOperation(pSymbolParams,cellOp) ((pSymbolParams)->baseOperation = cellOp)

#define SymbolExecParameters_GetBaseCellOperation(pSymbolParams) ((pSymbolParams)->baseOperation)

#define SymbolExecParameters_SetOffsetType(pSymbolParams,targetOp) ((pSymbolParams)->offsetType = targetOp)

#define SymbolExecParameters_GetOffsetType(pSymbolParams) ((pSymbolParams)->offsetType)

#define SymbolExecParameters_SetOffsetOperation(pSymbolParams,offOp) ((pSymbolParams)->offsetOperation = offOp)

#define SymbolExecParameters_GetOffsetOperation(pSymbolParams) ((pSymbolParams)->offsetOperation)

#define SymbolExecParameters_SetOffsetInverted(pSymbolParams, boolVal) ((pSymbolParams)->offsetInverted = boolVal)

#define SymbolExecParameters_GetOffsetInverted(pSymbolParams) ((pSymbolParams)->offsetInverted)

#define SymbolExecParameters_SetBaseInverted(pSymbolParams, boolVal) ((pSymbolParams)->baseInverted = boolVal)

#define SymbolExecParameters_GetBaseInverted(pSymbolParams) ((pSymbolParams)->baseInverted)

#define SymbolExecParameters_GetDelay(pSymbolParams) ((pSymbolParams)->delay)

#define SymbolExecParameters_SetDelay(pSymbolParams,Delay) ((pSymbolParams)->delay = Delay)

typedef enum SymbolClassifications{
  symbol_class_enum_min = 100,
  CL_ADR = symbol_class_enum_min,
  CL_O,
  CL_C,
  CL_ACTION,
  CL_COMMA,
  CL_REPETITIONS,
  CL_TARGET_ACTION,
  CL_MEMTRAV,
  CL_UNIQUE_ACTION,
  CL_UNIQUE_ACTION_WITH_OFFSET,
  symbol_class_enum_max = CL_UNIQUE_ACTION_WITH_OFFSET
} SymbolClassifications;

typedef enum MemTravDir {
  UNDEFINED,
  UP,
  DOWN
} MemTravDir;

////const UINT8 NUMBER_SYMBOL_CLASSIFICATIONS = symbol_class_enum_max - symbol_class_enum_min + 1;
extern const UINT8 NUMBER_SYMBOL_CLASSIFICATIONS;

typedef enum SymbolTypes{
  symbol_type_enum_min = 0,
  ST_ADDRESS_UP = symbol_type_enum_min,
  ST_ADDRESS_DOWN,
  ST_OPEN_PARENTHESIS,
  ST_CLOSE_PARENTHESIS,
  ST_COMMA,
  ST_WRITE_DATA_BFR,
  ST_WRITE_INVERTED_BFR,
  ST_READ_DATA_BFR,
  ST_READ_INVERTED_BFR,
  ST_STAR_REPETITIONS,
  ST_WRITE_DATA,
  ST_WRITE_INVERTED,
  ST_READ_DATA,
  ST_READ_INVERTED,
  ST_PAUSE_REFRESH_DATA,
  ST_PAUSE_REFRESH_INVERTED,
  ST_HAMMER_DATA,
  ST_HAMMER_INVERTED,
  ST_FAST_HAMMER_DATA,
  ST_FAST_HAMMER_INVERTED,
  symbol_type_enum_max = ST_FAST_HAMMER_INVERTED
} SymbolTypes;

extern const UINT8 NUMBER_SYMBOL_TYPES;

typedef enum CellOperation{
  CO_READ,
  CO_WRITE
}CellOperation;

typedef enum OffsetType{
  TO_NA,
  TO_NONE,
  TO_BFR
}OffsetType;

typedef enum RunTestSymbolTypes{
  symbol_rt_type_enum_min = symbol_type_enum_max + 1,
  ST_NORMAL_RUN = symbol_rt_type_enum_min,
  ST_PAUSE_REFRESH_RUN,
  ST_FINE_GRAIN_SEQ_HAMMER,
  ST_FINE_GRAIN_SEQ_HAMMER_SLOW,
  symbol_rt_type_enum_max = ST_FINE_GRAIN_SEQ_HAMMER_SLOW
} RunTestSymbolTypes;

// TODO: ? - Move the next 3 structures to a different header file.
typedef struct SymbolSeqParameters{
  UINT8 currentSubsequence;
  RunTestSymbolTypes sequenceRunnerType;
  UINT32 delay;
  UINT32 numberHammerCheckSubSeq;
  SWIZZLE_FUNCTION swizzleFunction;
}SymbolSeqParameters;

typedef struct RankErrors{
  UINT8 channelErrors[DCTT_MAX_NUM_CHANNELS];
}RankErrors;

typedef struct TestParameters{
  MemTravDir currentDirection;
  DCTT_API* DcttMain;
  DCTT_CONFIG_PARAMS* config;
  RankErrors rankErrors[DCTT_MAX_RANK_IN_CHANNEL];
  SetContainer* ErrorAddresses;
} TestParameters;

typedef struct SymbolExecParameters{
  MemTravDir Direction;
  UINT32 numberRepetitions;
  CellOperation baseOperation;
  BOOLEAN baseInverted;
  OffsetType offsetType;
  CellOperation offsetOperation;
  BOOLEAN offsetInverted;
  UINT32 delay;
}SymbolExecParameters;

typedef struct Symbol {
  SymbolClassifications classification;
  SymbolTypes symbolType;
  mString* symbolStr;
  // Return true and deletes string from command if it can parse it.
  BOOLEAN (*parse)(struct Symbol* self, mString* strToParse,SymbolExecParameters* parseParams);
  INT8 (*symbolFunction)(struct Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams);
} Symbol;

typedef INT8 (*ExecuteFunction)(struct Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams);

INT8 Symbol_Init(Symbol* self, SymbolTypes type);

//Next function used only for testing
VOID _Symbol_SetExecuteFunction(Symbol* self, ExecuteFunction exeFunction);

DCTTINLINE BOOLEAN Symbol_Parse(Symbol* self, mString* strToParse, SymbolExecParameters* parseParams)
{
  DcttError_UAssert(self != NULL);
  return self->parse(self, strToParse, parseParams);
}

DCTTINLINE SymbolClassifications Symbol_GetClassification(Symbol* self)
{
  return self->classification;
}

DCTTINLINE SymbolTypes Symbol_GetType(Symbol* self)
{
  return self->symbolType;
}

DCTTINLINE VOID TestParameters_ClearNumberErrors(TestParameters* testParameters)
{
  UINT8 channel;
  UINT8 rank;

  for (rank = 0; rank < DCTT_MAX_RANK_IN_CHANNEL; rank++) {
    for (channel = 0; channel < DCTT_MAX_NUM_CHANNELS; channel++) {
      testParameters->rankErrors[rank].channelErrors[channel] = 0;
    }
  }
}
#endif // _DCTT_SYMBOL_H_
