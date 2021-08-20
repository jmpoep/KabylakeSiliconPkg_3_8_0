/** @file
  Module that converts the test string into DCTT internal symbols.

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
#include "DcttDebug.h"
#include "DcttSymbol.h"
#include "DcttSymbols.h"
#include "DcttLexer.h"

INT16
Lexer_LexOneSequence (
  Lexer *self
  )
{
  UINT16              closeParPos;
  UINT16              seqInitialSize;
  UINT16              seqCurrSize;
  UINT16              seqNewSize;
  INT16               retCode = DCTT_SUCCESS;
  DCTT_CONFIG_PARAMS  *configParams;

  DcttError_UAssert (self != NULL);

  mString_LTrim (self->commandToLex);
  if (mString_GetSize (self->commandToLex) == 0) {
    return LEX_COMMAND_FINISHED;
  }

  if (mString_FindChr (self->commandToLex, ')', &closeParPos) != TRUE) {
    return LEX_ERROR_CLOSE_PAR_NOT_FOUND;
  }

  configParams = TestParameters_GetConfig (self->testParams);

  //Adding a sequence repetition (if it exists) to the sequence to lex
  if (mString_GetChar (self->commandToLex, closeParPos + 1) == '*') {
    //We have a sequence repetitions, include it on the sequence to Lex
    UINT16 currentPos;

    currentPos = closeParPos + 2;
    while (mString_PosIsDigit (self->commandToLex, currentPos)) {
      currentPos++;
    }

    if (currentPos > closeParPos + 2) {
      closeParPos = currentPos - 1;
    }
  }

  //Copying only one sequence to lex
  mString_ShallowElementsCopy (self->sequenceToLex, self->commandToLex);
  retCode = mString_Truncate(self->sequenceToLex, closeParPos + 1); //This line shouldn't fail

  configParams->ExecutingTestChars = _mString_GetcString (self->sequenceToLex);
  configParams->ExecutingTestCharsLen = mString_GetSize (self->sequenceToLex);

  if (retCode != DCTT_SUCCESS) {
    return retCode;// TODO: Because this line shouldn't fail we can take out this check later
  }

  DcttError_UAssert (retCode == DCTT_SUCCESS);

  seqInitialSize = mString_GetSize (self->sequenceToLex);
  seqCurrSize = seqInitialSize;
  self->numberTokensSequence = 0;

  while (mString_GetSize (self->sequenceToLex) > 0) {
    SymbolTypes i;

    for (i = Symbols_GetMinType (); i <= Symbols_GetMaxType (); i++) {
      Symbol* symbol;

      if (mString_GetSize (self->sequenceToLex) ==  0) {
        //We finished parsing the sequence
        break;
      }
      symbol = Symbols_GetSymbol (self->LexerSymbols, i);
      if (Symbol_Parse (symbol, self->sequenceToLex, self->sequenceParams[self->numberTokensSequence]) == TRUE) {
        //We found the symbol in the command

        DcttError_Assert (
          TestParameters_GetDcttHandle (self->testParams),
          self->numberTokensSequence < NUMBER_TOKENS_SEQUENCE,
          "Run out of space on our Token List."
          );

        self->sequenceTokens[self->numberTokensSequence] = symbol;
        self->numberTokensSequence = self->numberTokensSequence + 1;
      }
    }
    mString_LTrim (self->sequenceToLex);
    seqNewSize = mString_GetSize (self->sequenceToLex);
    if (seqNewSize == seqCurrSize) {
      return LEX_ERROR_CANNOT_LEX_ALL_INPUT;
    } else {
      seqCurrSize = seqNewSize;
    }
  }
  // "Delete" lexed part of commandToLex
  mString_SubString (self->commandToLex, seqInitialSize);

  return retCode;
}
