/** @file
  Executes Symbols parsed.

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
#include "DcttSymbol.h"
#include "DcttAnalyzer.h"
#include "DcttDebug.h"
#include "DcttInterpreter.h"

DCTTINLINE
VOID _Interpreter_StartSequence (
  Interpreter *self
  )
{
  DcttError_UAssert (self != NULL);
  DcttError_UAssert (self->sequenceParams != NULL);

  self->sequenceParams->currentSubsequence = 0;
}

INT16
Interpreter_RunSequence (
  Interpreter *self,
  Analyzer    *analyzerOutput
  )
{
  UINT8 numSubsequences, i;

  DcttError_UAssert (self != NULL);
  DcttError_UAssert (analyzerOutput != NULL);

  numSubsequences = Analyzer_GetNumberSymbolsExecute (analyzerOutput);

  _Interpreter_StartSequence (self);

  for (i = 0; i < numSubsequences; i++) {
    Symbol* symbol;
    SymbolExecParameters* params;
    UINT8 retCode;

    symbol = Analyzer_GetSymbolToExecute (analyzerOutput, i);
    params = Analyzer_GetSymbolToExecuteParams (analyzerOutput, i);

    retCode = Symbol_Execute (symbol, params, self->sequenceParams, self->globalParams);
    if (retCode != DCTT_SUCCESS) {
      return retCode;
    }
  }
  return DCTT_SUCCESS;
}
