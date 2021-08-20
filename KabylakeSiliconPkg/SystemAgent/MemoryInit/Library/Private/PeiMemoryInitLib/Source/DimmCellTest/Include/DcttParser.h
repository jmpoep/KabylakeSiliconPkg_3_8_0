/** @file
  Parser definitions.

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

#ifndef _DCTT_PARSER_H_
#define _DCTT_PARSER_H_
#include "DcttSymbol.h"
#include "DcttLexer.h"

typedef struct Parser{
  TestParameters* globalParameters;
}Parser;

#define Parser_VARDEF(varName) \
  Parser* varName; \
  Parser _internalVar_##varName; \
  TestParameters _internalVar_##varName##_parserGlobalParameters

#define Parser_VARINIT(varName, pHandle, pConfig) \
  varName = &(_internalVar_##varName); \
  (varName)->globalParameters = &(_internalVar_##varName##_parserGlobalParameters);\
  TestParameters_SetDirection((varName)->globalParameters, UNDEFINED);\
  TestParameters_SetDcttHandle((varName)->globalParameters, (pHandle));\
  TestParameters_SetErrAddresssContainer((varName)->globalParameters, NULL);\
  TestParameters_SetConfig((varName)->globalParameters, (pConfig))

#define _Parser_GetDirection(pParser) TestParameters_GetDirection((pParser)->globalParameters)

VOID Parser_ClearNumberErrors(Parser* self);

VOID Parser_AddAddressStorage(Parser* self, SetContainer* ErrorAddressesContainer);

INT16 Parser_ParseSequences(Parser* self, char* sequenceStr);

VOID _Parser_InitExecTestHooks(Parser* self, Lexer* lex);
#endif // _DCTT_PARSER_H_
