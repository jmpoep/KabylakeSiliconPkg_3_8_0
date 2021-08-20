/** @file
  Lexer declarations.

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

#ifndef _DCTT_LEXER_H_
#define _DCTT_LEXER_H_
#include "DcttSymbol.h"
#include "DcttSymbols.h"
#include "DcttMString.h"

#define NUMBER_TOKENS_SEQUENCE          30
#define LEX_COMMAND_FINISHED            1
#define LEX_SEQUENCE_FINISHED           2
#define LEX_ERROR_CLOSE_PAR_NOT_FOUND   3
#define LEX_ERROR_CANNOT_LEX_ALL_INPUT  4

#define Lexer_GetNumberTokensSequence(pLexer) (pLexer)->numberTokensSequence
#define _Lexer_GetSequenceTokens(pLexer) (pLexer)->sequenceTokens
// TODO: Next macro can be changed to a function to do more validation
#define Lexer_GetSequenceToken(pLexer, pos) (pLexer)->sequenceTokens[(pos)]
// TODO: Next macro can be changed to a function to do more validation
#define Lexer_GetSequenceTokenParams(pLexer, pos) (pLexer)->sequenceParams[(pos)]
#define _Lexer_GetCommandToLex(pLexer) (pLexer)->commandToLex
#define _Lexer_GetSequenceToLex(pLexer) (pLexer)->sequenceToLex
#define _Lexer_GetLexerSymbols(pLexer) (pLexer)->LexerSymbols

#define Lexer_VARDEF(varName) \
  Symbols_VARDEF(_##varName##_symbols); \
  Lexer* varName; \
  Lexer _internalVar_##varName; \
  SymbolExecParameters _internalVar_##varName##_sequenceParams[NUMBER_TOKENS_SEQUENCE];\
  mString _internalVar_##varName##_commandToLex; \
  mString _internalVar_##varName##_sequenceToLex

#define Lexer_VARINIT(varName, pStringToLex, pTestParameters) \
  do{\
    UINT8 idx;\
    varName = &(_internalVar_##varName); \
    (varName)->commandToLex = &(_internalVar_##varName##_commandToLex); \
    (varName)->testParams = (pTestParameters); \
    (varName)->sequenceToLex = &(_internalVar_##varName##_sequenceToLex); \
    Symbols_VARINIT(_##varName##_symbols); \
    (varName)->LexerSymbols = _##varName##_symbols; \
    /*(varName)->LexerSymbols = NewSymbols();*/ \
    /*Symbols_Init((varName)->LexerSymbols);*/ \
    (varName)->numberTokensSequence = 0; \
    mString_Init((varName)->commandToLex, pStringToLex); \
    for(idx = 0; idx < NUMBER_TOKENS_SEQUENCE; idx++) \
    { \
      ((varName)->sequenceParams)[idx] = &(_internalVar_##varName##_sequenceParams[idx]); \
    }\
  }while(0)

typedef struct Lexer{
  mString* commandToLex;
  mString* sequenceToLex;
  Symbols* LexerSymbols;
  Symbol* sequenceTokens[NUMBER_TOKENS_SEQUENCE];
  SymbolExecParameters* sequenceParams[NUMBER_TOKENS_SEQUENCE];
  UINT8 numberTokensSequence;
  TestParameters* testParams;
}Lexer;

INT16
Lexer_LexOneSequence (
  Lexer *self
  );
#endif // _DCTT_LEXER_H_
