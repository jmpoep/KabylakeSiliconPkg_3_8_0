/** @file
  // TODO: Description

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
#include "DcttAnalyzer.h"
#include "DcttDebug.h"

DCTTINLINE BOOLEAN _lexCheck (
                     Analyzer  *self,
                     Symbol    *symbol
                     )
{
  UINT8 i;

  // Check if the expected number of symbol classes isn't bigger than the
  // size of the array
  DcttError_UAssert (self->numberExpectedSymbolClasses <= MAX_NUMBER_EXPECTED_SYMBOLS);

  for (i = 0; i < self->numberExpectedSymbolClasses; i++) {
    if (Symbol_GetClassification (symbol) == self->expectedSymbolClass[i]) {
      return TRUE;
    }
  }
  return FALSE;
}

DCTTINLINE VOID _addExecSymbol (Analyzer* self, Symbol* symbol, SymbolExecParameters* symbolParams)
{
  DCTT_API* DcttMain;

  DcttMain = TestParameters_GetDcttHandle (self->testParameters);
  DcttError_Assert (
    DcttMain,
    self->numberSymbolsToExecute < MAX_NUMBER_SYMBOL_FUNCTIONS_SUBSEQUENCE,
    "Run out of room to add exec symbols."
    );

  self->SymbolsToExecute[self->numberSymbolsToExecute] = symbol;
  SymbolExecParameters_SetNumberRepetitions (symbolParams, 0);
  self->ExecutionParameters[self->numberSymbolsToExecute] = symbolParams;
  self->numberSymbolsToExecute = self->numberSymbolsToExecute + 1;
}

DCTTINLINE VOID _setRepetitions (Analyzer* self, Symbol* symbol, SymbolExecParameters* symbolParams)
{
  UINT32 repetitions;
  DCTT_API* DcttMain;

  DcttMain = TestParameters_GetDcttHandle (self->testParameters);
  DcttError_Assert (DcttMain, self->numberSymbolsToExecute > 0, "Analyzer: repetitions token found at position 0. This is illegal.");

  // Setting the number of repetitions on the parameters of the previous parsed action
  repetitions = SymbolExecParameters_GetNumberRepetitions (symbolParams);
  SymbolExecParameters_SetNumberRepetitions (self->ExecutionParameters[self->numberSymbolsToExecute - 1], repetitions);
}

DCTTINLINE VOID _setInitialExpectedClasses (Analyzer* self)
{
  self->expectedSymbolClass[0] = CL_ADR;
  self->expectedSymbolClass[1] = CL_MEMTRAV;
  self->numberExpectedSymbolClasses = 2;
}

DCTTINLINE VOID _setExpectedClassesAfterComma (Analyzer* self)
{
  self->expectedSymbolClass[0] = CL_ACTION;
  self->expectedSymbolClass[1] = CL_MEMTRAV;
  self->expectedSymbolClass[2] = CL_TARGET_ACTION;
  self->numberExpectedSymbolClasses = 3;
}

DCTTINLINE VOID _setExpectedClassesAfterMemTrav (Analyzer* self)
{
  self->expectedSymbolClass[0] = CL_O;// open parenthesis
  self->numberExpectedSymbolClasses = 1;
}

DCTTINLINE VOID _setExpectedClassesAfterOpenParenthesis (Analyzer* self)
{
  self->expectedSymbolClass[0] = CL_ACTION;
  self->expectedSymbolClass[1] = CL_MEMTRAV;
  self->expectedSymbolClass[2] = CL_TARGET_ACTION;
  self->expectedSymbolClass[3] = CL_UNIQUE_ACTION;
  self->expectedSymbolClass[4] = CL_UNIQUE_ACTION_WITH_OFFSET;
  self->numberExpectedSymbolClasses = 5;
}

DCTTINLINE VOID _setExpectedClassesAfterAction (Analyzer* self)
{
  self->expectedSymbolClass[0] = CL_COMMA;
  self->expectedSymbolClass[1] = CL_C;
  self->expectedSymbolClass[2] = CL_REPETITIONS;
  self->numberExpectedSymbolClasses = 3;
}

DCTTINLINE VOID _setExpectedClassesAfterRepetitions (Analyzer* self)
{
  DCTT_API* DcttMain;

  DcttMain = TestParameters_GetDcttHandle (self->testParameters);
  DcttError_Assert (DcttMain, self->numberSymbolsToExecute > 0, "Analyzer: repetitions token found at position 0. This is illegal.");

  if (Symbol_GetClassification (self->SymbolsToExecute[self->numberSymbolsToExecute - 1]) == CL_C) {
    // This is the repetitions after a closing parenthesis, there is nothing after this
    self->numberExpectedSymbolClasses = 0;
  } else {
    self->expectedSymbolClass[0] = CL_COMMA;
    self->expectedSymbolClass[1] = CL_C;
    self->numberExpectedSymbolClasses = 2;
  }
}

DCTTINLINE VOID _setExpectedClassesAfterUniqueAction (Analyzer* self)
{
  // There can only be one unique action per sequence
  // so the only allowed symbol after it is a close parenthesis
  self->expectedSymbolClass[0] = CL_C;
  self->numberExpectedSymbolClasses = 1;
}

DCTTINLINE VOID _setExpectedClassesAfterUniqueActionWithOffset (Analyzer* self)
{
  // There can only be one unique action per sequence
  // so the only allowed symbol after it is a close parenthesis
  self->expectedSymbolClass[0] = CL_TARGET_ACTION;
  self->numberExpectedSymbolClasses = 1;
}

DCTTINLINE VOID _setExpectedClassesAfterCloseParenthesis (Analyzer* self)
{
  // The sequence should stop at a close parenthesis
  // unless there is a repetition symbol
  self->expectedSymbolClass[0] = CL_REPETITIONS;
  self->numberExpectedSymbolClasses = 1;
}

DCTTINLINE VOID _addMemoryTraverser (Analyzer* self, Symbol* symbol, SymbolExecParameters* params)
{
  _addExecSymbol (self, symbol, params);
}

DCTTINLINE VOID _closeParenthesis (Analyzer* self, Symbol* symbol, SymbolExecParameters* params)
{
  _addExecSymbol (self, symbol, params);
}

DCTTINLINE VOID _addAction (Analyzer* self, Symbol* symbol, SymbolExecParameters* params)
{
  _addExecSymbol (self, symbol, params);
}

DCTTINLINE VOID _addTargetAction (Analyzer* self, Symbol* symbol, SymbolExecParameters* params)
{
  OffsetType offsetType;
  UINT8 numSymbolsExecute = self->numberSymbolsToExecute;

  if (numSymbolsExecute > 0) {
    // Get type to see if symbol can be merged
    offsetType = SymbolExecParameters_GetOffsetType
      (self->ExecutionParameters[numSymbolsExecute - 1]);
  } else {
    // First action symbol to be executed, impossible to merge
    offsetType = TO_NA;
  }

  if (offsetType == TO_NONE) {
    // The previous action symbol was a WD, WI, RD, RI.
    // Merge this symbol with the previous symbol.
    OffsetType newOffsetType;
    CellOperation newOffsetOperation;
    BOOLEAN newOffsetInverted;

    newOffsetType = SymbolExecParameters_GetOffsetType (params);
    newOffsetOperation = SymbolExecParameters_GetOffsetOperation (params);
    newOffsetInverted = SymbolExecParameters_GetOffsetInverted (params);
    SymbolExecParameters_SetOffsetType (
      self->ExecutionParameters[numSymbolsExecute - 1],
      newOffsetType);
    SymbolExecParameters_SetOffsetOperation (
      self->ExecutionParameters[numSymbolsExecute - 1],
      newOffsetOperation);
    SymbolExecParameters_SetOffsetInverted (
      self->ExecutionParameters[numSymbolsExecute - 1],
      newOffsetInverted);
  } else {
    // Cannot merge; add this offset action operation by itself.
    _addExecSymbol (self, symbol, params);
  }
}

INT16
Analyzer_GenerateCode (
  Analyzer  *self,
  Lexer     *lexerOutput
  )
{
  UINT8 i, numSymbols;

  numSymbols = Lexer_GetNumberTokensSequence (lexerOutput);

  // "Deleting" execution symbols generated before
  self->numberSymbolsToExecute = 0;
  _setInitialExpectedClasses (self);

  for (i = 0; i < numSymbols; i++) {
    Symbol* symbol = Lexer_GetSequenceToken (lexerOutput, i);
    SymbolExecParameters* params = Lexer_GetSequenceTokenParams (lexerOutput, i);

    if (_lexCheck (self, symbol)) {
      SymbolClassifications symbolClass = Symbol_GetClassification (symbol);

      if (symbolClass == CL_COMMA) {
        _setExpectedClassesAfterComma (self);
      } else if (symbolClass == CL_ADR) {  // Address up & address down, special memory traversers
        _addMemoryTraverser (self, symbol, params);
        _setExpectedClassesAfterMemTrav (self);
      } else if (symbolClass == CL_MEMTRAV) {  // This will be different in this case????
        _addMemoryTraverser (self, symbol, params);
        _setExpectedClassesAfterMemTrav (self);
      } else if (symbolClass == CL_O) {
        _setExpectedClassesAfterOpenParenthesis (self);
      } else if (symbolClass == CL_C) {
        _closeParenthesis (self, symbol, params);
        _setExpectedClassesAfterCloseParenthesis (self);
      } else if (symbolClass == CL_ACTION) {
        _addAction (self, symbol, params);
        _setExpectedClassesAfterAction (self);
      } else if (symbolClass == CL_TARGET_ACTION) {
        UINT8 numSymbolsExecute = self->numberSymbolsToExecute;

        _addTargetAction (self, symbol, params);

        //Little hack to close parenthesis if previous action was a
        //Unique action with offset
        if (numSymbolsExecute > 0) {
          //Get type to see if symbol can be merged
          Symbol* prevSymbol = Lexer_GetSequenceToken (lexerOutput, (i - 1));
          SymbolClassifications prevSymbolClass = Symbol_GetClassification (prevSymbol);
          if (prevSymbolClass == CL_UNIQUE_ACTION_WITH_OFFSET) {
            _setExpectedClassesAfterUniqueAction (self);
          } else {
            _setExpectedClassesAfterAction (self);
          }

        } else {
          _setExpectedClassesAfterAction (self);
        }
      } else if (symbolClass == CL_REPETITIONS) {
        _setRepetitions (self, symbol, params);
        _setExpectedClassesAfterRepetitions (self);
      } else if (symbolClass == CL_UNIQUE_ACTION) {
        _addAction (self, symbol, params);
        _setExpectedClassesAfterUniqueAction (self);
      } else if (symbolClass == CL_UNIQUE_ACTION_WITH_OFFSET) {
        _addAction (self, symbol, params);
        _setExpectedClassesAfterUniqueActionWithOffset (self);
      } else {
        DcttError_Assert (
          TestParameters_GetDcttHandle (self->testParameters),
          1 == 0,
          "Found a symbol with an undefined class."
          );
      }
    } else {
      // We found an unexpected symbol, see if its better to continue parsing
      // to report more errors or stop and report this error.
      return -1;
    }
  }

  return DCTT_SUCCESS;
}
