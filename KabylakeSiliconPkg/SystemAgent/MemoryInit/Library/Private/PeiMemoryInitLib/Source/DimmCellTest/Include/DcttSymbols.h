/** @file
  Symbols definitions and structures.

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

#ifndef _DCTT_SYMBOLS_H_
#define _DCTT_SYMBOLS_H_

#include "DcttMString.h"
#include "DcttSymbol.h"

#define SYMBOLS_LIST_SIZE 20

#define Symbols_GetMinType() symbol_type_enum_min
#define Symbols_GetMaxType() symbol_type_enum_max


typedef struct Symbols {
  Symbol *symbolList[SYMBOLS_LIST_SIZE];
}Symbols;

#define Symbols_VARDEF(varName) \
  Symbols* varName;\
  Symbols _internalVar_##varName##_symbolsMemStruct; \
  mString _internalVar_##varName##_addrUpStr, _internalVar_##varName##_addrDownStr, _internalVar_##varName##_readInvertedStr; \
  mString _internalVar_##varName##_openParStr, _internalVar_##varName##_closeParStr, _internalVar_##varName##_commaStr; \
  mString _internalVar_##varName##_writeDataStr, _internalVar_##varName##_writeInvertedStr, _internalVar_##varName##_readDataStr; \
  mString _internalVar_##varName##_readDataTBFRStr, _internalVar_##varName##_readInvertedTBFRStr, _internalVar_##varName##_writeDataTBFRStr; \
  mString _internalVar_##varName##_writeInvertedTBFRStr, _internalVar_##varName##_starRepetitionsStr; \
  mString _internalVar_##varName##_pauseRefreshDStr, _internalVar_##varName##_pauseRefreshIStr; \
  mString _internalVar_##varName##_hammerDStr, _internalVar_##varName##_hammerIStr; \
  mString _internalVar_##varName##_fastHammerDStr, _internalVar_##varName##_fastHammerIStr; \
  Symbol _internalVar_##varName##_addrUp, _internalVar_##varName##_addrDown, _internalVar_##varName##_openPar; \
  Symbol _internalVar_##varName##_closePar, _internalVar_##varName##_comma, _internalVar_##varName##_writeData; \
  Symbol _internalVar_##varName##_writeInverted, _internalVar_##varName##_readData, _internalVar_##varName##_readInverted; \
  Symbol _internalVar_##varName##_readDataTBFR, _internalVar_##varName##_readInvertedTBFR, _internalVar_##varName##_writeDataTBFR;\
  Symbol _internalVar_##varName##_writeInvertedTBFR, _internalVar_##varName##_starRepetitions;\
  Symbol _internalVar_##varName##_pauseRefreshD, _internalVar_##varName##_pauseRefreshI;\
  Symbol _internalVar_##varName##_hammerD, _internalVar_##varName##_hammerI;\
  Symbol _internalVar_##varName##_fastHammerD, _internalVar_##varName##_fastHammerI

#define Symbols_VARINIT(varName) \
  do{\
     SymbolTypes i;\
     /*If this assert fails our list is not big enough to hold all the defined symbols*/\
     DcttError_UAssert(NUMBER_SYMBOL_TYPES <= SYMBOLS_LIST_SIZE); \
     varName = &(_internalVar_##varName##_symbolsMemStruct); \
     \
     ((varName)->symbolList)[ST_ADDRESS_UP] = &(_internalVar_##varName##_addrUp); \
     (((varName)->symbolList)[ST_ADDRESS_UP])->symbolStr = &(_internalVar_##varName##_addrUpStr); \
     \
     ((varName)->symbolList)[ST_ADDRESS_DOWN] = &(_internalVar_##varName##_addrDown); \
     (((varName)->symbolList)[ST_ADDRESS_DOWN])->symbolStr = &(_internalVar_##varName##_addrDownStr); \
     \
     ((varName)->symbolList)[ST_OPEN_PARENTHESIS] = &(_internalVar_##varName##_openPar); \
     (((varName)->symbolList)[ST_OPEN_PARENTHESIS])->symbolStr = &(_internalVar_##varName##_openParStr); \
     \
     ((varName)->symbolList)[ST_CLOSE_PARENTHESIS] = &(_internalVar_##varName##_closePar); \
     (((varName)->symbolList)[ST_CLOSE_PARENTHESIS])->symbolStr = &(_internalVar_##varName##_closeParStr); \
     \
     ((varName)->symbolList)[ST_COMMA] = &(_internalVar_##varName##_comma); \
     (((varName)->symbolList)[ST_COMMA])->symbolStr = &(_internalVar_##varName##_commaStr); \
     \
     ((varName)->symbolList)[ST_WRITE_DATA] = &(_internalVar_##varName##_writeData); \
     (((varName)->symbolList)[ST_WRITE_DATA])->symbolStr = &(_internalVar_##varName##_writeDataStr); \
     \
     ((varName)->symbolList)[ST_WRITE_INVERTED] = &(_internalVar_##varName##_writeInverted); \
     (((varName)->symbolList)[ST_WRITE_INVERTED])->symbolStr = &(_internalVar_##varName##_writeInvertedStr); \
     \
     ((varName)->symbolList)[ST_READ_DATA] = &(_internalVar_##varName##_readData); \
     (((varName)->symbolList)[ST_READ_DATA])->symbolStr = &(_internalVar_##varName##_readDataStr); \
     \
     ((varName)->symbolList)[ST_READ_INVERTED] = &(_internalVar_##varName##_readInverted); \
     (((varName)->symbolList)[ST_READ_INVERTED])->symbolStr = &(_internalVar_##varName##_readInvertedStr); \
     \
     ((varName)->symbolList)[ST_READ_DATA_BFR] = &(_internalVar_##varName##_readDataTBFR); \
     (((varName)->symbolList)[ST_READ_DATA_BFR])->symbolStr = &(_internalVar_##varName##_readDataTBFRStr); \
     \
     ((varName)->symbolList)[ST_READ_INVERTED_BFR] = &(_internalVar_##varName##_readInvertedTBFR); \
     (((varName)->symbolList)[ST_READ_INVERTED_BFR])->symbolStr = &(_internalVar_##varName##_readInvertedTBFRStr); \
     \
     ((varName)->symbolList)[ST_WRITE_DATA_BFR] = &(_internalVar_##varName##_writeDataTBFR); \
     (((varName)->symbolList)[ST_WRITE_DATA_BFR])->symbolStr = &(_internalVar_##varName##_writeDataTBFRStr); \
     \
     ((varName)->symbolList)[ST_WRITE_INVERTED_BFR] = &(_internalVar_##varName##_writeInvertedTBFR); \
     (((varName)->symbolList)[ST_WRITE_INVERTED_BFR])->symbolStr = &(_internalVar_##varName##_writeInvertedTBFRStr); \
     \
     ((varName)->symbolList)[ST_STAR_REPETITIONS] = &(_internalVar_##varName##_starRepetitions); \
     (((varName)->symbolList)[ST_STAR_REPETITIONS])->symbolStr = &(_internalVar_##varName##_starRepetitionsStr); \
     \
     ((varName)->symbolList)[ST_PAUSE_REFRESH_DATA] = &(_internalVar_##varName##_pauseRefreshD); \
     (((varName)->symbolList)[ST_PAUSE_REFRESH_DATA])->symbolStr = &(_internalVar_##varName##_pauseRefreshDStr); \
     \
     ((varName)->symbolList)[ST_PAUSE_REFRESH_INVERTED] = &(_internalVar_##varName##_pauseRefreshI); \
     (((varName)->symbolList)[ST_PAUSE_REFRESH_INVERTED])->symbolStr = &(_internalVar_##varName##_pauseRefreshIStr); \
     \
     ((varName)->symbolList)[ST_HAMMER_DATA] = &(_internalVar_##varName##_hammerD); \
     (((varName)->symbolList)[ST_HAMMER_DATA])->symbolStr = &(_internalVar_##varName##_hammerDStr); \
     \
     ((varName)->symbolList)[ST_HAMMER_INVERTED] = &(_internalVar_##varName##_hammerI); \
     (((varName)->symbolList)[ST_HAMMER_INVERTED])->symbolStr = &(_internalVar_##varName##_hammerIStr); \
     \
     ((varName)->symbolList)[ST_FAST_HAMMER_DATA] = &(_internalVar_##varName##_fastHammerD); \
     (((varName)->symbolList)[ST_FAST_HAMMER_DATA])->symbolStr = &(_internalVar_##varName##_fastHammerDStr); \
     \
     ((varName)->symbolList)[ST_FAST_HAMMER_INVERTED] = &(_internalVar_##varName##_fastHammerI); \
     (((varName)->symbolList)[ST_FAST_HAMMER_INVERTED])->symbolStr = &(_internalVar_##varName##_fastHammerIStr); \
     \
     for(i = symbol_type_enum_min; i <= symbol_type_enum_max; i++) \
     {\
      Symbol_Init(((varName)->symbolList)[i], i);\
     }\
  }while(0)

DCTTINLINE Symbol* Symbols_GetSymbol(Symbols* self, SymbolTypes symbolType)
{
  DcttError_UAssert(self != NULL);
  // TODO: Add more error checking if necessary
  return (self->symbolList)[symbolType];
}
#endif // _DCTT_SYMBOLS_H_
