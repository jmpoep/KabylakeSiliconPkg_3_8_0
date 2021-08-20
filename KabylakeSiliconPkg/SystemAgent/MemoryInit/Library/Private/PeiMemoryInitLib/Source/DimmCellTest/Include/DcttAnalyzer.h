/** @file
  Analyzer Definitions

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

#ifndef _DCTT_ANALYZER_H_
#define _DCTT_ANALYZER_H_

#include "DcttSymbol.h"
#include "DcttLexer.h"

#define MAX_NUMBER_EXPECTED_SYMBOLS               8
#define MAX_NUMBER_SYMBOL_FUNCTIONS_SUBSEQUENCE   12

typedef struct Analyzer {
  SymbolClassifications expectedSymbolClass[MAX_NUMBER_EXPECTED_SYMBOLS];
  SymbolExecParameters  *ExecutionParameters[MAX_NUMBER_SYMBOL_FUNCTIONS_SUBSEQUENCE];
  Symbol                *SymbolsToExecute[MAX_NUMBER_SYMBOL_FUNCTIONS_SUBSEQUENCE];
  TestParameters        *testParameters;
  UINT8                 numberExpectedSymbolClasses;
  UINT8                 numberSymbolsToExecute;
} Analyzer;

// TODO: Replace macro def and Init with func implementation.
#define Analyzer_VARDEF(varName) \
  Analyzer* varName; \
  Analyzer _internalVar_##varName

#define Analyzer_VARINIT(varName, ptestParameters) \
  varName = &(_internalVar_##varName); \
  (varName)->numberSymbolsToExecute = 0; \
  (varName)->testParameters = (ptestParameters); \
  (varName)->numberExpectedSymbolClasses = 0

#define Analyzer_GetNumberSymbolsExecute(pAnalyzer) (pAnalyzer)->numberSymbolsToExecute
#define Analyzer_GetSymbolToExecute(pAnalyzer, pos) (pAnalyzer)->SymbolsToExecute[(pos)]
#define Analyzer_GetSymbolToExecuteParams(pAnalyzer, pos) (pAnalyzer)->ExecutionParameters[(pos)]

INT16
Analyzer_GenerateCode (
  Analyzer  *This,
  Lexer     *LexerOutput
  );

#endif // _DCTT_ANALYZER_H_
