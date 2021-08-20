/** @file
  Functions for parsing, and executing the test string by defined
  symbols.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2015 Intel Corporation.

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
#include "DcttApi.h"
#include "DcttApiFunctions.h"
#include "DcttRegList.h"
#include "DcttMString.h"
#include "DcttDebug.h"
#include "DcttSymbol.h"
#include "DcttCpgcFunctions.h"
#include "DcttSetContainer.h"
#include "DcttSwizzleFunctions.h"

GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 NUMBER_SYMBOL_TYPES = symbol_type_enum_max - symbol_type_enum_min + 1;
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 NUMBER_SYMBOL_CLASSIFICATIONS = symbol_class_enum_max - symbol_class_enum_min + 1;

GLOBAL_REMOVE_IF_UNREFERENCED const char SubMemoryRangeTestNotAvailable[] = "SubMemoryRangeTest is only available on optimized second order tests.\n";

DCTTINLINE
BOOLEAN
_symbol_common_parsing (
  Symbol               *self,
  mString              *strToParse,
  SymbolExecParameters *parseParams
  )
{
  BOOLEAN retValue = FALSE;

  if (mString_StartsWith (strToParse, self->symbolStr)) {
    retValue = TRUE;
    mString_SubString (strToParse, mString_GetSize (self->symbolStr));

    if (self->classification == CL_ACTION) {
      //Setting up this operation to None, so the action operation can be
      //merged with a target operation next to it
      SymbolExecParameters_SetOffsetType (parseParams, TO_NONE);
      if (self->symbolType == ST_WRITE_DATA) {
        SymbolExecParameters_SetBaseCellOperation (parseParams, CO_WRITE);
        SymbolExecParameters_SetBaseInverted (parseParams, FALSE);
      } else if (self->symbolType == ST_WRITE_INVERTED) {
        SymbolExecParameters_SetBaseCellOperation (parseParams, CO_WRITE);
        SymbolExecParameters_SetBaseInverted (parseParams, TRUE);
      } else if (self->symbolType == ST_READ_DATA) {
        SymbolExecParameters_SetBaseCellOperation (parseParams, CO_READ);
        SymbolExecParameters_SetBaseInverted (parseParams, FALSE);
      } else if (self->symbolType == ST_READ_INVERTED) {
        SymbolExecParameters_SetBaseCellOperation (parseParams, CO_READ);
        SymbolExecParameters_SetBaseInverted (parseParams, TRUE);
      } else {
        // This should never happen
        DcttError_UAssert (1 == 0);
      }
    } else if (self->symbolType == ST_READ_DATA_BFR) {
      SymbolExecParameters_SetOffsetOperation (parseParams, CO_READ);
      SymbolExecParameters_SetOffsetInverted (parseParams, FALSE);
      SymbolExecParameters_SetOffsetType (parseParams, TO_BFR);
    } else if (self->symbolType == ST_READ_INVERTED_BFR) {
      SymbolExecParameters_SetOffsetOperation (parseParams, CO_READ);
      SymbolExecParameters_SetOffsetInverted (parseParams, TRUE);
      SymbolExecParameters_SetOffsetType (parseParams, TO_BFR);
    } else if (self->symbolType == ST_WRITE_DATA_BFR) {
      SymbolExecParameters_SetOffsetOperation (parseParams, CO_WRITE);
      SymbolExecParameters_SetOffsetInverted (parseParams, FALSE);
      SymbolExecParameters_SetOffsetType (parseParams, TO_BFR);
    } else if (self->symbolType == ST_WRITE_INVERTED_BFR) {
      SymbolExecParameters_SetOffsetOperation (parseParams, CO_WRITE);
      SymbolExecParameters_SetOffsetInverted (parseParams, TRUE);
      SymbolExecParameters_SetOffsetType (parseParams, TO_BFR);
    } else {
      //Other operation
      SymbolExecParameters_SetOffsetType (parseParams, TO_NA);
    }
  }
  return retValue;
}

BOOLEAN
_Symbol_GenericParse (
  Symbol               *self,
  mString              *strToParse,
  SymbolExecParameters *parseParams
  )
{
  return _symbol_common_parsing (self, strToParse, parseParams);
}

BOOLEAN
_Symbol_DelayParse (
  Symbol               *self,
  mString              *strToParse,
  SymbolExecParameters *parseParams
  )
{

  BOOLEAN retValue = FALSE;

  SymbolClassifications symbolClass = Symbol_GetClassification (self);

  if (symbolClass == CL_UNIQUE_ACTION_WITH_OFFSET) {
    SymbolExecParameters_SetOffsetType (parseParams, TO_NONE);
  }

  if (mString_StartsWith (strToParse, self->symbolStr)) {
    retValue = TRUE;
    //Deleting start of the string
    mString_SubString (strToParse, mString_GetSize (self->symbolStr));
    if (mString_PosIsDigit (strToParse,0)) {
      UINT32 opDelay;
      //Delay has been provided, parse it
      opDelay = mString_ExtractU32 (strToParse);
      SymbolExecParameters_SetDelay (parseParams, opDelay);
    } else {
      //Using default value for the delay
      SymbolExecParameters_SetDelay (parseParams, 0);
    }
  }

  return retValue;
}

BOOLEAN
_Symbol_HammerParse (
  Symbol               *self,
  mString              *strToParse,
  SymbolExecParameters *parseParams
  )
{
  BOOLEAN retValue = FALSE;

  if (mString_StartsWith (strToParse, self->symbolStr) && mString_PosIsDigit (strToParse,1)) {
    // @todo: Add checking for overflow of the extracted integer number here
    UINT32 repetitions;

    //Getting rid of the * at the beginning of the string
    mString_SubString (strToParse, 1);

    repetitions = mString_ExtractU32 (strToParse);

    SymbolExecParameters_SetNumberRepetitions (parseParams, repetitions);
    SymbolExecParameters_SetOffsetType (parseParams, TO_NA);
    retValue = TRUE;
  }

  return retValue;
}


BOOLEAN
_Symbol_AddrUpParse (
  Symbol               *self,
  mString              *strToParse,
  SymbolExecParameters *parseParams
  )
{
  BOOLEAN retValue;

  retValue = _symbol_common_parsing (self, strToParse, parseParams);
  if (retValue == TRUE) {
    SymbolExecParameters_SetDirection (parseParams, UP);
    SymbolExecParameters_SetOffsetType (parseParams, TO_NA);
  }

  return retValue;
}

BOOLEAN
_Symbol_AddrDownParse (
  Symbol               *self,
  mString              *strToParse,
  SymbolExecParameters *parseParams
  )
{
  BOOLEAN retValue;

  retValue = _symbol_common_parsing (self, strToParse, parseParams);
  if (retValue == TRUE) {
    SymbolExecParameters_SetDirection (parseParams, DOWN);
    SymbolExecParameters_SetOffsetType (parseParams, TO_NA);
  }

  return retValue;
}

//Common functions for exec functions
static
BOOLEAN
_runMoreTests (
  TestParameters  *globalParams
  )
{
  DCTT_API            *DcttMain;
  DCTT_CONFIG_PARAMS  *DcttConfig;
  UINT8               channel;
  UINT8               rank;

  DcttConfig  = TestParameters_GetConfig (globalParams);
  DcttMain    = TestParameters_GetDcttHandle (globalParams);

  for (rank = 0; rank < DCTT_MAX_RANK_IN_CHANNEL; rank++) {
    for (channel = 0; channel < DCTT_MAX_NUM_CHANNELS; channel++) {
      if ((TestParameters_GetNumberErrorsRankCh (globalParams, channel, rank)) < DcttConfig->maxNumberErrors) {
        return TRUE;
      }
    }
  }

  return FALSE;
}

//@todo: Move the exec functions out of this file
//Exec Functions
INT8 _Symbol_AddressUpDownExecFunc (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  DCTT_API* DcttMain;

  DcttMain = TestParameters_GetDcttHandle (globalParams);

  if (!_runMoreTests (globalParams)) {
    return DCTT_SUCCESS;
  }

  DcttLogDebug (DcttMain, "+++++++");
  DcttLogVerbose (DcttMain, "Direction Function: ");

  if (TestParameters_GetDirection (globalParams) != _Symbol_GetDirection (symParams)) {
    DcttLogVerbose (DcttMain, "Changing Test direction to ");
    if (SymbolExecParameters_GetDirection (symParams) == UP) {
      DcttLogVerbose (DcttMain, "UP\n");
    } else if (SymbolExecParameters_GetDirection (symParams) == DOWN) {
      DcttLogVerbose (DcttMain,"DOWN\n");
    }
    CPGCFunctions_ChangeDirection
      (
      TestParameters_GetDcttHandle (globalParams),
      SymbolExecParameters_GetDirection (symParams)
      );
  } else {
    DcttLogVerbose (DcttMain,"Keeping current direction\n");
  }
  TestParameters_SetDirection (globalParams, _Symbol_GetDirection (symParams));

  SymbolSeqParameters_ResetSubsequence (seqParams);
  SymbolSeqParameters_ResetSequenceRunnerType (seqParams);

  return 0;
}

VOID _Symbol_SetBFRRegisters (SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  OffsetType offsetType;
  CellOperation offOperation;
  CellOperation baseOperation;
  BOOLEAN offInv, baseInv;
  DCTT_CONFIG_PARAMS *DcttConfig;
  DCTT_API* DcttMain;
  UINT8 subseqNumber;
  UINT32 pattern;
  UINT8 delay;

  offsetType = SymbolExecParameters_GetOffsetType (symParams);
  offOperation = SymbolExecParameters_GetOffsetOperation (symParams);
  baseOperation = SymbolExecParameters_GetBaseCellOperation (symParams);
  baseInv = SymbolExecParameters_GetBaseInverted (symParams);
  offInv = SymbolExecParameters_GetOffsetInverted (symParams);
  DcttConfig = TestParameters_GetConfig (globalParams);
  DcttMain = TestParameters_GetDcttHandle (globalParams);
  subseqNumber = SymbolSeqParameters_GetSubsequence (seqParams);
  delay = DcttConfig->subsequenceWait;
  pattern = DcttConfig->backgroundType;

  if (DcttConfig->addrSwizzleAlg == DcttAddrSwizzleAglWT) {
    //Wrap trigger swizzle algorithm

    //Workaround for offset wrap problem
    CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber,
      offInv, pattern, CPGC_SUBSEQ_TYPE_OFFSET_OP_BASE + offOperation,
      delay, DcttConfig->wrapTrgWANumCachelines, FALSE);

    //Setting the type of offset operation depending on pattern
    //checkerboard will do diagonals, others will use rows

    if (pattern == DcttBackgroundPatternCheckerboard) {
      CPGCFunctions_SetSubsequenceOffsetCtrl (DcttMain,
        subseqNumber,baseInv, baseOperation, 1, 1, 0, 0,
        2, CPGC_OFFSET_TRIGGER_NONE, 0);
      DcttLogVerbose (DcttMain, "Using Diagonals for Offset operation\n");
    } else {
      CPGCFunctions_SetSubsequenceOffsetCtrl (DcttMain,
        subseqNumber,baseInv, baseOperation, 1, 0, 0, 0,
        2, CPGC_OFFSET_TRIGGER_NONE, 0);
      DcttLogVerbose (DcttMain, "Using Rows for Offset operation\n");
    }
  } else {
    CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber,
      offInv, pattern, CPGC_SUBSEQ_TYPE_OFFSET_OP_BASE + offOperation,
      delay, 0, FALSE);
    CPGCFunctions_SetSubsequenceOffsetCtrl (DcttMain,
      subseqNumber,baseInv, baseOperation, 1, 0, 0, 1,
      2, CPGC_OFFSET_TRIGGER_NONE, 0);
  }

  DcttLogDebug (DcttMain, "++BFR Offset: base op %d, base inv %d, offset type %d, offset op %d, offset inv %d\n", baseOperation, baseInv, offsetType, offOperation, offInv);
}

INT8 _Symbol_WDExecFunc (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  DCTT_CONFIG_PARAMS* DcttConfig;
  UINT32 pattern;
  UINT32 repetitions;
  UINT8 subseqNumber;
  UINT8 delay;
  DCTT_API* DcttMain;

  DcttMain = TestParameters_GetDcttHandle (globalParams);
  DcttConfig = TestParameters_GetConfig (globalParams);
  subseqNumber = SymbolSeqParameters_GetSubsequence (seqParams);
  repetitions = SymbolExecParameters_GetNumberRepetitions (symParams);
  delay = DcttConfig->subsequenceWait;
  pattern = DcttConfig->backgroundType;

  if (!_runMoreTests (globalParams)) {
    return DCTT_SUCCESS;
  }

  DcttLogDebug (DcttMain, "+++++++");
  DcttLogVerbose (DcttMain, "WD function");
  DcttLogDebug (DcttMain, ": subsequence %d, repetitions %d",SymbolSeqParameters_GetSubsequence (seqParams), repetitions);

  if (SymbolExecParameters_GetOffsetType (symParams) == TO_BFR) {
    DcttLogVerbose (DcttMain, " BFR\n");
    _Symbol_SetBFRRegisters (symParams, seqParams, globalParams);
  } else {
    if (repetitions > 0) {
      DcttLogVerbose (DcttMain, " Hammer: 2^%d\n", repetitions);
    } else {
      DcttLogVerbose (DcttMain, "\n");
    }
    CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber, FALSE, pattern, CPGC_BASE_SUBSEQ_TYPE_WRITE, delay, repetitions, FALSE);
  }
  SymbolSeqParameters_IncrementSubsequence (seqParams);
  return 0;
}

INT8 _Symbol_RDExecFunc (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  DCTT_CONFIG_PARAMS* DcttConfig;
  UINT32 pattern;
  UINT8 subseqNumber;
  DCTT_API* DcttMain;
  UINT32 repetitions;
  UINT8 delay;

  DcttMain = TestParameters_GetDcttHandle (globalParams);
  DcttConfig = TestParameters_GetConfig (globalParams);
  subseqNumber = SymbolSeqParameters_GetSubsequence (seqParams);
  repetitions = SymbolExecParameters_GetNumberRepetitions (symParams);
  delay = DcttConfig->subsequenceWait;
  pattern = DcttConfig->backgroundType;

  if (!_runMoreTests (globalParams)) {
    return DCTT_SUCCESS;
  }

  DcttLogDebug (DcttMain, "+++++++");
  DcttLogVerbose (DcttMain, "RD function");
  DcttLogDebug (DcttMain, ": subsequence %d, repetitions:%d ",SymbolSeqParameters_GetSubsequence (seqParams), repetitions);

  if (SymbolExecParameters_GetOffsetType (symParams) == TO_BFR) {
    DcttLogVerbose (DcttMain, " BFR\n");
    _Symbol_SetBFRRegisters (symParams, seqParams, globalParams);
  } else {
    if (repetitions > 0) {
      DcttLogVerbose (DcttMain, " Hammer: 2^%d\n", repetitions);
    } else {
      DcttLogVerbose (DcttMain, "\n");
    }
    CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber, FALSE, pattern, CPGC_BASE_SUBSEQ_TYPE_READ, delay, repetitions, FALSE);
  }
  SymbolSeqParameters_IncrementSubsequence (seqParams);
  return 0;
}

INT8 _Symbol_WIExecFunc (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  DCTT_CONFIG_PARAMS* DcttConfig;
  UINT32 pattern;
  UINT8 subseqNumber;
  DCTT_API* DcttMain;
  UINT32 repetitions;
  UINT8 delay;

  DcttMain = TestParameters_GetDcttHandle (globalParams);
  DcttConfig = TestParameters_GetConfig (globalParams);
  subseqNumber = SymbolSeqParameters_GetSubsequence (seqParams);
  repetitions = SymbolExecParameters_GetNumberRepetitions (symParams);
  delay = DcttConfig->subsequenceWait;
  pattern = DcttConfig->backgroundType;

  if (!_runMoreTests (globalParams)) {
    return DCTT_SUCCESS;
  }

  DcttLogDebug (DcttMain, "+++++++");
  DcttLogVerbose (DcttMain, "WI function");
  DcttLogDebug (DcttMain, ": subsequence %d, repetitions:%d ",SymbolSeqParameters_GetSubsequence (seqParams), repetitions);
  if (SymbolExecParameters_GetOffsetType (symParams) == TO_BFR) {
    DcttLogVerbose (DcttMain, " BFR\n");
    _Symbol_SetBFRRegisters (symParams, seqParams, globalParams);
  } else {
    if (repetitions > 0) {
      DcttLogVerbose (DcttMain, " Hammer: 2^%d\n", repetitions);
    } else {
      DcttLogVerbose (DcttMain, "\n");
    }
    CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber, TRUE, pattern, CPGC_BASE_SUBSEQ_TYPE_WRITE, delay, repetitions, FALSE);
  }

  SymbolSeqParameters_IncrementSubsequence (seqParams);
  return 0;
}

INT8 _Symbol_RIExecFunc (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  DCTT_CONFIG_PARAMS* DcttConfig;
  UINT32 pattern;
  UINT8 subseqNumber;
  DCTT_API* DcttMain;
  UINT32 repetitions;
  UINT8 delay;

  DcttMain = TestParameters_GetDcttHandle (globalParams);
  DcttConfig = TestParameters_GetConfig (globalParams);
  subseqNumber = SymbolSeqParameters_GetSubsequence (seqParams);
  repetitions = SymbolExecParameters_GetNumberRepetitions (symParams);
  delay = DcttConfig->subsequenceWait;
  pattern = DcttConfig->backgroundType;

  if (!_runMoreTests (globalParams)) {
    return DCTT_SUCCESS;
  }

  DcttLogDebug (DcttMain, "+++++++");
  DcttLogVerbose (DcttMain, "RI function");
  DcttLogDebug (DcttMain, ": subsequence %d, repetitions:%d ",SymbolSeqParameters_GetSubsequence (seqParams), repetitions);

  if (SymbolExecParameters_GetOffsetType (symParams) == TO_BFR) {
    DcttLogVerbose (DcttMain, " BFR\n");

    _Symbol_SetBFRRegisters (symParams, seqParams, globalParams);
  } else {
    if (repetitions > 0) {
      DcttLogVerbose (DcttMain, " Hammer: 2^%d\n", repetitions);
    } else {
      DcttLogVerbose (DcttMain, "\n");
    }

    CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber, TRUE, pattern, CPGC_BASE_SUBSEQ_TYPE_READ, delay, repetitions, FALSE);
  }

  SymbolSeqParameters_IncrementSubsequence (seqParams);
  return 0;
}

INT8 _Symbol_RDBFRExecFunc (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  DCTT_API* DcttMain;
  UINT32 repetitions;

  DcttMain = TestParameters_GetDcttHandle (globalParams);
  repetitions = SymbolExecParameters_GetNumberRepetitions (symParams);

  DcttOutputPrint (DcttMain, "+++++++RD<tBFR> function: subsequence %d, repetitions:%d\n",SymbolSeqParameters_GetSubsequence (seqParams), repetitions);
  SymbolSeqParameters_IncrementSubsequence (seqParams);
  return 0;
}

INT8 _Symbol_RIBFRExecFunc (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  DCTT_API* DcttMain;
  UINT32 repetitions;

  DcttMain = TestParameters_GetDcttHandle (globalParams);
  repetitions = SymbolExecParameters_GetNumberRepetitions (symParams);

  DcttOutputPrint (DcttMain, "+++++++RI<tBFR> function: subsequence %d, repetitions:%d\n",SymbolSeqParameters_GetSubsequence (seqParams), repetitions);
  SymbolSeqParameters_IncrementSubsequence (seqParams);
  return 0;
}

INT8 _Symbol_WDBFRExecFunc (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  DCTT_API* DcttMain;
  UINT32 repetitions;

  DcttMain = TestParameters_GetDcttHandle (globalParams);
  repetitions = SymbolExecParameters_GetNumberRepetitions (symParams);

  DcttOutputPrint (DcttMain, "+++++++WD<tBFR> function: subsequence %d, repetitions:%d\n",SymbolSeqParameters_GetSubsequence (seqParams), repetitions);
  SymbolSeqParameters_IncrementSubsequence (seqParams);
  return 0;
}

INT8 _Symbol_WIBFRExecFunc (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  DCTT_API* DcttMain;
  UINT32 repetitions;

  DcttMain = TestParameters_GetDcttHandle (globalParams);
  repetitions = SymbolExecParameters_GetNumberRepetitions (symParams);

  DcttOutputPrint (DcttMain, "+++++++WI<tBFR> function: subsequence %d, repetitions:%d\n",SymbolSeqParameters_GetSubsequence (seqParams), repetitions);
  SymbolSeqParameters_IncrementSubsequence (seqParams);
  return 0;
}

VOID
PrintCurrentTestString (
  DCTT_API             *DcttMain,
  DCTT_CONFIG_PARAMS   *DcttConfig
  )
{
  UINT32               currCharIdx;
  CHAR8                currChar;

  if (DcttConfig->ExecutingTestChars == NULL) {
    return;
  }

  for (currCharIdx = 0; currCharIdx < DcttConfig->ExecutingTestCharsLen; currCharIdx++) {
    currChar = DcttConfig->ExecutingTestChars[currCharIdx];
    if (currChar == 0) {
      break;
    }
    DcttOutputPrint (DcttMain, "%c", currChar);
  }
}

INT8 _Symbol_CPExecFunc (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  DCTT_CONFIG_PARAMS* DcttConfig;
  UINT8 subseqNumber;
  DCTT_API* DcttMain;
  UINT32 repetitions;
  RankErrors* currentNumberErrors;
  MemTravDir testDirection;
  INT8 retVal;
#ifndef DISABLE_SECOND_ORDER_TESTS
  SeqHammerRegisterValues regValsStorage;
#endif
  RunTestSymbolTypes runnerType;
  SetContainer* ErrorAddresses;
  UINT32 scPageTimerReg = 64;

  DcttMain = TestParameters_GetDcttHandle (globalParams);
  DcttConfig = TestParameters_GetConfig (globalParams);
  subseqNumber = SymbolSeqParameters_GetSubsequence (seqParams);
  repetitions = SymbolExecParameters_GetNumberRepetitions (symParams);
  testDirection = TestParameters_GetDirection (globalParams);
  runnerType = SymbolSeqParameters_GetSequenceRunnerType (seqParams);
  ErrorAddresses = TestParameters_GetErrAddresssContainer (globalParams);
  DcttError_Assert (DcttMain, ErrorAddresses != NULL, "Error Addresses was NULL");

  if (!_runMoreTests (globalParams)) {
    return DCTT_SUCCESS;
  }
  // @todo: Abstract HW access
  if ((runnerType == ST_FINE_GRAIN_SEQ_HAMMER) || (runnerType == ST_FINE_GRAIN_SEQ_HAMMER_SLOW)) {
    DcttOutputPrint (DcttMain, "Modifying page timer value to force page closes\n");
    scPageTimerReg = DcttReadReg32Func (DcttMain, MCSCHEDS_CR_SC_PCIT_REG);
    DcttWriteReg32Func (DcttMain, MCSCHEDS_CR_SC_PCIT_REG, 1);
  }

#ifndef DISABLE_SECOND_ORDER_TESTS
  if (repetitions > 0) {
    //Running a sequence hammer
    //Set registers for a page close and set up everything to get a sequence hammer
    DcttError_Assert (DcttMain, repetitions <= 15 , "Maximum repetitions for sequence hammer is 15. Received: %d\n", repetitions);
    CPGCFunctions_SetRegistersSequenceHammer (DcttMain, &regValsStorage, globalParams, subseqNumber);
  }
#endif

  DcttLogDebug (DcttMain, "+++++++");
  DcttOutputPrint (DcttMain, "Executing test:");
  PrintCurrentTestString (DcttMain, DcttConfig);
  DcttLogDebug (DcttMain, " total number subsequences %d, repetitions:%d", SymbolSeqParameters_GetSubsequence (seqParams), repetitions);
  DcttOutputPrint (DcttMain, "\n");
  currentNumberErrors = TestParameters_GetRankErrors (globalParams);

#ifndef DISABLE_SECOND_ORDER_TESTS
  if (DcttConfig->OptimizeSecondOrderRun) {
    DcttOutputPrint (DcttMain, "Running second order optimized \n");
    retVal = (INT8) CPGCFunctions_ExecuteTestOnSecondOrderOptimized (DcttMain, subseqNumber, testDirection, repetitions, runnerType, (VOID*) seqParams, globalParams);
  }
#ifndef DISABLE_UNOPTIMIZED_SECOND_ORDER
  else if (DcttConfig->runTestOnSecondOrder) {
    if (repetitions > 0) {
      DcttError_Assert (DcttMain, 1==0, "Running sequence hammers is not implemented when running per bank without reporting multiple errors yet.\n");
    }
    DcttError_Assert (DcttMain, runnerType == ST_NORMAL_RUN, "Pause refresh is not enabled when running per bank without reporting multiple errors yet.\n");
    DcttError_Assert (DcttMain, DcttConfig->SubMemoryRangeTest == FALSE, (char*) SubMemoryRangeTestNotAvailable);
    retVal = (INT8) CPGCFunctions_ExecuteTestOnSecondOrder (DcttMain, subseqNumber, testDirection, globalParams);
  }
#else
  else if (DcttConfig->runTestOnSecondOrder) {
    retVal = (INT8) CPGCFunctions_ExecuteTestOnSecondOrderOptimized (DcttMain, subseqNumber, testDirection, repetitions, runnerType, (VOID*) seqParams, globalParams);
  }
#endif
  else {
    if (repetitions > 0) {
      DcttError_Assert (DcttMain, 1==0, "Running sequence hammers is not implemented without reporting multiple errors yet.\n");
    }
    DcttError_Assert (DcttMain, runnerType == ST_NORMAL_RUN, "Pause refresh is not enabled without reporting multiple errors yet.\n");
    DcttError_Assert (DcttMain, DcttConfig->SubMemoryRangeTest == FALSE, (char*) SubMemoryRangeTestNotAvailable);
    retVal = (INT8) CPGCFunctions_ExecuteTest (TestParameters_GetDcttHandle (globalParams), subseqNumber, currentNumberErrors, testDirection,globalParams);
  }
#else
  if (repetitions > 0) {
    DcttError_Assert (DcttMain, 1==0, "Running sequence hammers is not implemented without reporting multiple errors yet.\n");
  }
  DcttError_Assert (DcttMain, runnerType == ST_NORMAL_RUN, "Pause refresh is not enabled without reporting multiple errors yet.\n");
  DcttError_Assert (DcttMain, DcttConfig->SubMemoryRangeTest == FALSE, (char*) SubMemoryRangeTestNotAvailable);
  retVal = (INT8) CPGCFunctions_ExecuteTest (TestParameters_GetDcttHandle (globalParams), subseqNumber, currentNumberErrors, testDirection,globalParams);
#endif

  //Next consolidate addresses can be moved to after the whole test is finished
  //In that we will be faster but we could run out of space due to repeated run errors
  // TODO: we can add a check here to see if we have space on the ErrStorage and stop the test if we don't.
  SetContainer_SetRunUnsorted (ErrorAddresses);
  SetContainer_ConsolidateStorages (ErrorAddresses);

#ifndef DISABLE_SECOND_ORDER_TESTS
  if (repetitions > 0) {
    //Resetting all the sequence hammer parameters
    //Set registers for a page close and set up everything to get a sequence hammer
    CPGCFunctions_RestoreRegistersSequenceHammer (DcttMain, &regValsStorage);
  }
#endif

  if ((runnerType == ST_FINE_GRAIN_SEQ_HAMMER) || (runnerType == ST_FINE_GRAIN_SEQ_HAMMER_SLOW)) {
    DcttOutputPrint (DcttMain, "Restoring Page timer value\n");
    DcttWriteReg32Func (DcttMain, MCSCHEDS_CR_SC_PCIT_REG, scPageTimerReg);
  }

  //Enabling refreshes again if disabled by pause refresh test
  if ((runnerType == ST_PAUSE_REFRESH_RUN) ||
      ((runnerType == ST_FINE_GRAIN_SEQ_HAMMER) && (!globalParams->config->HammerRefreshEnable))
      ) {
    DcttOutputPrint (DcttMain, "Re-enabling refreshes\n");
    CPGCFunctions_SetRefreshDisableBitmask (DcttMain, 0);
  }

  DcttOutputPrint (DcttMain, "\n");
  SymbolSeqParameters_IncrementSubsequence (seqParams);
  if (retVal != DCTT_SUCCESS) {
    return retVal;
  }

  return DCTT_SUCCESS;
}

static
INT8
PauseRefreshExecute (
  Symbol               *self,
  SymbolExecParameters *symParams,
  SymbolSeqParameters  *seqParams,
  TestParameters       *globalParams,
  BOOLEAN               invertData
  )
{
  DCTT_API              *DcttMain;
  DCTT_CONFIG_PARAMS *DcttConfig;
  UINT32                delay;
  UINT32                pattern;
  UINT8                 subseqNumber;


  delay = SymbolExecParameters_GetDelay (symParams);
  DcttConfig = TestParameters_GetConfig (globalParams);

  if (delay == 0) {
    //Replacing delay with the default delay
    delay = DcttConfig->pauseRefreshDelay;
  }

  SymbolSeqParameters_SetDelay (seqParams, delay);

  DcttMain = TestParameters_GetDcttHandle (globalParams);
  DcttConfig = TestParameters_GetConfig (globalParams);
  subseqNumber = SymbolSeqParameters_GetSubsequence (seqParams);
  pattern = DcttConfig->backgroundType;

  if (invertData) {
    DcttOutputPrint (DcttMain, "WI-Pause-RI function");
  } else {
    DcttOutputPrint (DcttMain, "WD-Pause-RD function");
  }

  DcttOutputPrint (DcttMain, " delay: %d\n", delay);

  SymbolSeqParameters_SetSequenceRunnerType (seqParams, ST_PAUSE_REFRESH_RUN);

  //Setting the first write on the subsequence
  //the read will be set when running the test.
  CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber, invertData, pattern, CPGC_BASE_SUBSEQ_TYPE_WRITE, DcttConfig->subsequenceWait, 0, FALSE);

  //Disabling refresh on all ranks to run this test
  CPGCFunctions_SetRefreshDisableBitmask (DcttMain, (UINT8) -1);

  SymbolSeqParameters_IncrementSubsequence (seqParams);

  return DCTT_SUCCESS;
}

static INT8 HammerExecute_Slow (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams, BOOLEAN invertData)
{
  DCTT_API* DcttMain;
  UINT32 numberRepetitions;
  DCTT_CONFIG_PARAMS* DcttConfig;
  UINT8 subseqNumber;
  UINT32 pattern;
  UINT32 baseOp;
  UINT32 numberCheckSeq;

  numberRepetitions = SymbolExecParameters_GetDelay (symParams);
  DcttConfig = TestParameters_GetConfig (globalParams);

  if (numberRepetitions == 0) {
    //Replacing delay with the default delay
    numberRepetitions = DcttConfig->hammerRepetitions;
  }

  SymbolSeqParameters_SetDelay (seqParams, numberRepetitions);

  DcttMain = TestParameters_GetDcttHandle (globalParams);
  DcttConfig = TestParameters_GetConfig (globalParams);
  subseqNumber = SymbolSeqParameters_GetSubsequence (seqParams);
  pattern = DcttConfig->backgroundType;

  if (DcttConfig->rowSwizzleType != DcttRowSwizzleNone) {
    DcttError_Assert (DcttMain, 1 == 0, "This Hammer operation don't support custom swizzles. Use fast hammer instead.\n");
  }

  if (DcttConfig->useWriteHammers) {
    DcttOutputPrint (DcttMain, "W");
    baseOp = CPGC_BASE_SUBSEQ_TYPE_WRITE;
  } else {
    DcttOutputPrint (DcttMain, "R");
    baseOp = CPGC_BASE_SUBSEQ_TYPE_READ;
  }

  if (invertData) {
    DcttOutputPrint (DcttMain, "I Hammer");
  } else {
    DcttOutputPrint (DcttMain, "D Hammer");
  }

  DcttOutputPrint (DcttMain, " Number of repetitions: %d\n", numberRepetitions);

  DcttOutputPrint (DcttMain, "Neighbors to check: ");

  switch (DcttConfig->hammerCheckType) {
    case DcttHamerCheckAllNB:
      DcttOutputPrint (DcttMain, "All Neighbors\n");
      CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber + 1, symParams->offsetInverted, DcttConfig->backgroundType, CPGC_SUBSEQ_TYPE_OFFSET_OP_BASE + symParams->offsetOperation, DcttConfig->subsequenceWait, 0, FALSE);
      CPGCFunctions_SetSubsequenceOffsetCtrl (DcttMain, subseqNumber + 1, FALSE, 0, 1, 1, 0, 0, 0, CPGC_OFFSET_TRIGGER_NONE, 0);
      seqParams->numberHammerCheckSubSeq = 2;
      CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber + 2, symParams->offsetInverted, DcttConfig->backgroundType, CPGC_SUBSEQ_TYPE_OFFSET_OP_BASE + symParams->offsetOperation, DcttConfig->subsequenceWait, 0, FALSE);
      CPGCFunctions_SetSubsequenceOffsetCtrl (DcttMain, subseqNumber + 2, FALSE, 0, 1, 1, 1, 0, 0, CPGC_OFFSET_TRIGGER_NONE, 0);
      break;
    case DcttHamerCheckRowNB:
      DcttOutputPrint (DcttMain, "Row Neighbors\n");
      CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber + 1, symParams->offsetInverted, DcttConfig->backgroundType, CPGC_SUBSEQ_TYPE_OFFSET_OP_BASE + symParams->offsetOperation, DcttConfig->subsequenceWait, 0, FALSE);
      CPGCFunctions_SetSubsequenceOffsetCtrl (DcttMain, subseqNumber + 1, FALSE, 0, 1, 0, 0, 0, 0, CPGC_OFFSET_TRIGGER_NONE, 0);
      seqParams->numberHammerCheckSubSeq = 1;
      break;
    case DcttHamerCheckColumnNB:
      DcttOutputPrint (DcttMain, "Col Neighbors\n");
      CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber + 1, symParams->offsetInverted, DcttConfig->backgroundType, CPGC_SUBSEQ_TYPE_OFFSET_OP_BASE + symParams->offsetOperation, DcttConfig->subsequenceWait, 0, FALSE);
      CPGCFunctions_SetSubsequenceOffsetCtrl (DcttMain, subseqNumber + 1, FALSE, 0, 0, 1, 0, 0, 0, CPGC_OFFSET_TRIGGER_NONE, 0);
      seqParams->numberHammerCheckSubSeq = 1;
      break;
    case DcttHamerCheckDiagonalNB:
      DcttOutputPrint (DcttMain, "Diagonal Neighbors\n");
      CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber + 1, symParams->offsetInverted, DcttConfig->backgroundType, CPGC_SUBSEQ_TYPE_OFFSET_OP_BASE + symParams->offsetOperation, DcttConfig->subsequenceWait, 0, FALSE);
      CPGCFunctions_SetSubsequenceOffsetCtrl (DcttMain, subseqNumber + 1, FALSE, 0, 1, 1, 0, 0, 0, CPGC_OFFSET_TRIGGER_NONE, 0);
      seqParams->numberHammerCheckSubSeq = 1;
      break;
    case DcttHamerCheckNone:
      DcttOutputPrint (DcttMain, "None\n");
      seqParams->numberHammerCheckSubSeq = 0;
      break;
    case DcttHamerCheckAllBank:
      DcttOutputPrint (DcttMain, "All Bank\n");
      seqParams->numberHammerCheckSubSeq = 1;
      //break;
    default:
      DcttError_Assert (DcttMain, 1 == 0, "Unsupported option: %d\n", DcttConfig->hammerCheckType);
      seqParams->numberHammerCheckSubSeq = 0;
      break;
  }

  SymbolSeqParameters_SetSequenceRunnerType (seqParams, ST_FINE_GRAIN_SEQ_HAMMER_SLOW);

  CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber, invertData, pattern, baseOp, DcttConfig->hammerPageCloseDelay, 0, FALSE);

  SymbolSeqParameters_IncrementSubsequence (seqParams);

  for (numberCheckSeq = 0; numberCheckSeq < seqParams->numberHammerCheckSubSeq; numberCheckSeq ++) {
    SymbolSeqParameters_IncrementSubsequence (seqParams);
  }

  return DCTT_SUCCESS;
}

static INT8 HammerExecute (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams, BOOLEAN invertData)
{
  DCTT_API* DcttMain;
  UINT32 numberRepetitions;
  DCTT_CONFIG_PARAMS* DcttConfig;
  UINT8 subseqNumber;
  UINT32 pattern;
  UINT32 baseOp;

  numberRepetitions = SymbolExecParameters_GetDelay (symParams);
  DcttConfig = TestParameters_GetConfig (globalParams);

  if (numberRepetitions == 0) {
    //Replacing delay with the default delay
    numberRepetitions = DcttConfig->hammerRepetitions;
  }

  SymbolSeqParameters_SetDelay (seqParams, numberRepetitions);

  DcttMain = TestParameters_GetDcttHandle (globalParams);
  DcttConfig = TestParameters_GetConfig (globalParams);
  subseqNumber = SymbolSeqParameters_GetSubsequence (seqParams);
  pattern = DcttConfig->backgroundType;

  DcttError_Assert (DcttMain, subseqNumber == 0, "Sequence hammer should be the first and only operation in a sequence\n");

  if (DcttConfig->hammerCheckType != DcttHamerCheckRowNB) {
    DcttError_Assert (DcttMain, 1 == 0, "This Hammer operation only supports checking row neighbors.\n");
  }

  if (DcttConfig->useWriteHammers) {
    DcttOutputPrint (DcttMain, "W");
    baseOp = CPGC_BASE_SUBSEQ_TYPE_WRITE;
  } else {
    DcttError_Assert (DcttMain, 1 == 0, "Fast hammer can only use write operations for hammering\n");
    DcttOutputPrint (DcttMain, "R");
    baseOp = CPGC_BASE_SUBSEQ_TYPE_READ;
  }

  if (invertData) {
    DcttOutputPrint (DcttMain, "I Fast Hammer");
    //Subsequence to set neighbors
    CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber + 1, FALSE, pattern, CPGC_BASE_SUBSEQ_TYPE_WRITE, DcttConfig->subsequenceWait, 0, FALSE);
    //Subsequence to check neighbors
    CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber + 2, FALSE, pattern, CPGC_BASE_SUBSEQ_TYPE_READ, DcttConfig->subsequenceWait, 0, FALSE);
  } else {
    DcttOutputPrint (DcttMain, "D Fast Hammer");
    //Subsequence to set neighbors
    CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber + 1, TRUE, pattern, CPGC_BASE_SUBSEQ_TYPE_WRITE, DcttConfig->subsequenceWait, 0, FALSE);
    //Subsequence to check neighbors
    CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber + 2, TRUE, pattern, CPGC_BASE_SUBSEQ_TYPE_READ, DcttConfig->subsequenceWait, 0, FALSE);
  }

  DcttOutputPrint (DcttMain, " Number of repetitions: %d\n", numberRepetitions);

  CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber, invertData, pattern, baseOp, DcttConfig->hammerPageCloseDelay, 0, FALSE);

  CPGCFunctions_SetSubsequenceCtrl (DcttMain, subseqNumber + 3, invertData, pattern, baseOp, DcttConfig->subsequenceWait, 0, FALSE);

  DcttOutputPrint (DcttMain, "Checking Row Neighbors, Row Swizzle: ");

  switch (DcttConfig->rowSwizzleType) {
    case DcttRowSwizzleNone:
      DcttOutputPrint (DcttMain, "None\n");
      seqParams->swizzleFunction = Swizzle_GetLogicalAddressNoSwizzle;
      break;
    case DcttRowSwizzle3XOr1_3XOr2:
      DcttOutputPrint (DcttMain, "2 = 3 XOR 2, 1 = 3 XOR 1\n");
      seqParams->swizzleFunction = Swizzle_GetLogicalAddress3xor1_3xor2;
      break;
    case DcttRowSwizzle01234567EFCDAB89:
      DcttOutputPrint (DcttMain, "01234567EFCDAB89\n");
      seqParams->swizzleFunction = Swizzle_GetLogicalAddress01234567EFCDAB89;
      break;
    default:
      DcttError_Assert (DcttMain, 1 == 0, "Unsupported Swizzle: %d\n", DcttConfig->rowSwizzleType);
      seqParams->swizzleFunction = NULL;
      break;
  }

  DcttOutputPrint (DcttMain, "Number of Hammer Iterations per Row: %d\n", DcttConfig->hammerIterationsOnRow);

  SymbolSeqParameters_SetSequenceRunnerType (seqParams, ST_FINE_GRAIN_SEQ_HAMMER);

  SymbolSeqParameters_IncrementSubsequence (seqParams);
  SymbolSeqParameters_IncrementSubsequence (seqParams);
  SymbolSeqParameters_IncrementSubsequence (seqParams);
  SymbolSeqParameters_IncrementSubsequence (seqParams);

  //Disabling refresh on all ranks to run this test
  if (!globalParams->config->HammerRefreshEnable) {
    DcttOutputPrint (DcttMain, "Disabling Refreshes\n");
    CPGCFunctions_SetRefreshDisableBitmask (DcttMain, (UINT8) -1);
  }

  return DCTT_SUCCESS;
}

INT8 _Symbol_HammerData (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  return HammerExecute_Slow (self, symParams, seqParams, globalParams, FALSE);
}

INT8 _Symbol_HammerInvert (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  return HammerExecute_Slow (self, symParams, seqParams, globalParams, TRUE);
}

INT8 _Symbol_FastHammerData (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  return HammerExecute (self, symParams, seqParams, globalParams, FALSE);
}

INT8 _Symbol_FastHammerInvert (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  return HammerExecute (self, symParams, seqParams, globalParams, TRUE);
}

INT8 _Symbol_PauseRefreshData (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  return PauseRefreshExecute (self, symParams, seqParams, globalParams, FALSE);
}
INT8 _Symbol_PauseRefreshInverted (Symbol* self, SymbolExecParameters*  symParams, SymbolSeqParameters* seqParams, TestParameters* globalParams)
{
  return PauseRefreshExecute (self, symParams, seqParams, globalParams, TRUE);
}

INT8 Symbol_Init (Symbol* self, SymbolTypes type)
{
  DcttError_UAssert (self != NULL);
  self->parse = NULL;

  switch (type) {
    case ST_ADDRESS_UP:
      mString_Init (self->symbolStr, "^");
      self->classification = CL_ADR;
      self->parse = _Symbol_AddrUpParse;
      self->symbolFunction = _Symbol_AddressUpDownExecFunc;
      break;

    case ST_ADDRESS_DOWN:
      mString_Init (self->symbolStr, "v");
      self->classification = CL_ADR;
      self->parse = _Symbol_AddrDownParse;
      self->symbolFunction = _Symbol_AddressUpDownExecFunc;
      break;

    case ST_OPEN_PARENTHESIS:
      mString_Init (self->symbolStr, "(");
      self->classification = CL_O;
      break;

    case ST_CLOSE_PARENTHESIS:
      mString_Init (self->symbolStr, ")");
      self->classification = CL_C;
      self->symbolFunction =_Symbol_CPExecFunc;
      break;

    case ST_COMMA:
      mString_Init (self->symbolStr, ",");
      self->classification = CL_COMMA;
      break;

    case ST_WRITE_DATA:
      mString_Init (self->symbolStr, "wd");
      self->classification = CL_ACTION;
      self->symbolFunction = _Symbol_WDExecFunc;
      break;

    case ST_WRITE_INVERTED:
      mString_Init (self->symbolStr, "wi");
      self->classification = CL_ACTION;
      self->symbolFunction = _Symbol_WIExecFunc;
      break;

    case ST_READ_DATA:
      mString_Init (self->symbolStr, "rd");
      self->classification = CL_ACTION;
      self->symbolFunction = _Symbol_RDExecFunc;
      break;

    case ST_READ_INVERTED:
      mString_Init (self->symbolStr, "ri");
      self->classification = CL_ACTION;
      self->symbolFunction = _Symbol_RIExecFunc;
      break;

    case ST_READ_DATA_BFR:
      mString_Init (self->symbolStr, "rd<tbfr>");
      self->classification = CL_TARGET_ACTION;
      self->symbolFunction = _Symbol_RDBFRExecFunc;
      break;

    case ST_READ_INVERTED_BFR:
      mString_Init (self->symbolStr, "ri<tbfr>");
      self->classification = CL_TARGET_ACTION;
      self->symbolFunction = _Symbol_RIBFRExecFunc;
      break;

    case ST_WRITE_DATA_BFR:
      mString_Init (self->symbolStr, "wd<tbfr>");
      self->classification = CL_TARGET_ACTION;
      self->symbolFunction = _Symbol_WDBFRExecFunc;
      break;

    case ST_WRITE_INVERTED_BFR:
      mString_Init (self->symbolStr, "wi<tbfr>");
      self->classification = CL_TARGET_ACTION;
      self->symbolFunction = _Symbol_WIBFRExecFunc;
      break;

    case ST_STAR_REPETITIONS:
      mString_Init (self->symbolStr, "*");
      self->classification = CL_REPETITIONS;
      self->parse = _Symbol_HammerParse;
      break;

    case ST_PAUSE_REFRESH_DATA:
      mString_Init (self->symbolStr, "prefreshd");
      self->classification = CL_UNIQUE_ACTION;
      self->parse = _Symbol_DelayParse;
      self->symbolFunction = _Symbol_PauseRefreshData;
      break;

    case ST_PAUSE_REFRESH_INVERTED:
      mString_Init (self->symbolStr, "prefreshi");
      self->classification = CL_UNIQUE_ACTION;
      self->parse = _Symbol_DelayParse;
      self->symbolFunction = _Symbol_PauseRefreshInverted;
      break;

    case ST_HAMMER_DATA:
      mString_Init (self->symbolStr, "hammerd");
      self->classification = CL_UNIQUE_ACTION_WITH_OFFSET;
      self->parse = _Symbol_DelayParse;
      self->symbolFunction = _Symbol_HammerData;
      break;

    case ST_HAMMER_INVERTED:
      mString_Init (self->symbolStr, "hammeri");
      self->classification = CL_UNIQUE_ACTION_WITH_OFFSET;
      self->parse = _Symbol_DelayParse;
      self->symbolFunction = _Symbol_HammerInvert;
      break;

    case ST_FAST_HAMMER_DATA:
      mString_Init (self->symbolStr, "fhammerd");
      self->classification = CL_UNIQUE_ACTION;
      self->parse = _Symbol_DelayParse;
      self->symbolFunction = _Symbol_FastHammerData;
      break;

    case ST_FAST_HAMMER_INVERTED:
      mString_Init (self->symbolStr, "fhammeri");
      self->classification = CL_UNIQUE_ACTION;
      self->parse = _Symbol_DelayParse;
      self->symbolFunction = _Symbol_FastHammerInvert;
      break;


    default:
      DcttError_UAssert(1 == 0);////this can be changed to returning an error in production code
  }

  self->symbolType = type;
  if (self->parse == NULL) {
    self->parse = _Symbol_GenericParse;
  }
  return DCTT_SUCCESS;
}

VOID _Symbol_SetExecuteFunction (Symbol* self, ExecuteFunction exeFunction)
{
  self->symbolFunction = exeFunction;
}
