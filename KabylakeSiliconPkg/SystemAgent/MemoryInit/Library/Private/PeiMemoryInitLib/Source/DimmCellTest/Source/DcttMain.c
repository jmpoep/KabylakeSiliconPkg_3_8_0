/** @file
  Main Entry point to the DCTT.

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
#include "DcttParser.h"
#include "DcttCpgcFunctions.h"
#include "DcttSysRestore.h"
#include "DcttPermutations.h"
#include "DcttParametersCheck.h"
#include "DcttSetContainer.h"
#include "DcttMarginFunctions.h"
#include "DcttHelpers.h"
#include "DcttPrintHelpers.h"

// TODO: Move to margin and treat as ObjOr
#define NUMBER_MARGIN_RUNS_TO_STORE (10)
#define NUMBER_STORAGES_NEEDED      (NUMBER_MARGIN_RUNS_TO_STORE + 2)
#define UINT16_MAX  (0xFFFF)

// TODO: Look for appropriate location
typedef struct {
  SetContainer  *ErrorAddresses;
} DCTT_POINT_RUN_CONFIG;

typedef struct {
  INT32   MarginValue;
  UINT32  TotalErrors;
  UINT32  NewErrors;
  UINT32  MissedErrors;
} DCTT_MARGIN_RUN_DATA;

///
/// Global Constants
///
GLOBAL_REMOVE_IF_UNREFERENCED const DCTT_VERSION  gDcttVersion = {
#include "DcttVersion.h"
};

VOID
DcttSetDefaultParams (
  DCTT_CONFIG_PARAMS  *TestParams
  )
{
  DCTT_DIMM_ADDRESS     *Address;
  DCTT_TIMING_PARAMS    *Timing;
  UINT8                 Index;

  Timing = &TestParams->TimingParams;

  for (Index = 0; Index < (sizeof (TestParams->swizzle) / sizeof (TestParams->swizzle[0])); Index++) {
    TestParams->swizzle[Index] = Index;
  }
  for (Index = 0; Index < (sizeof (TestParams->bottomAddress) / sizeof (TestParams->bottomAddress[0])); Index++) {
    Address       = &TestParams->bottomAddress[Index];
    Address->Bank = 0;
    Address->Col  = 0;
    Address->Row  = 0;
    Address->Rank = 0;
  }
  for (Index = 0; Index < (sizeof (TestParams->topAddress) / sizeof (TestParams->topAddress[0])); Index++) {
    Address       = &TestParams->topAddress[Index];
    Address->Bank = 7;
    Address->Col  = 1016;
    Address->Row  = 2047;
    Address->Rank = 0;
  }
  for (Index = 0; Index < (sizeof (TestParams->ranksToIgnoreBitMask) / sizeof (TestParams->ranksToIgnoreBitMask[0])); Index++) {
    TestParams->ranksToIgnoreBitMask[Index] = 0;
  }
  TestParams->modifySwizzle = FALSE;
  TestParams->numberLanesSwizzle = 1;
  TestParams->maxLaneSwizzle = 0;
  TestParams->traverseDiagonal = FALSE;
  TestParams->numberTests = 1;
  TestParams->testStrings[0] = "^(wd) ^(rd, wi) v(ri, wd) v(rd)";
  TestParams->numberChannels = DCTT_MAX_NUM_CHANNELS;
  TestParams->channelBitMask = (1 << DCTT_MAX_NUM_CHANNELS) - 1;
  TestParams->numberRankPerChannel = DCTT_MAX_RANK_IN_CHANNEL;
  TestParams->firstOrder = DcttOrderColumn;
  TestParams->secondOrder = DcttOrderRow;
  TestParams->thirdOrder = DcttOrderBank;
  TestParams->fourthOrder = DcttOrderRank;
  TestParams->backgroundBase = DcttBackBaseZeros;
  TestParams->backgroundType = DcttBackgroundPatternSolid;
  TestParams->maxNumberErrors = 1;
  TestParams->failOnError = TRUE;
  TestParams->dontStopErrors = FALSE;
  TestParams->startTestDelay = 2;
  TestParams->subsequenceWait = 0;
  TestParams->addrSwizzleAlg = DcttAddrSwizzleAglNone;
  TestParams->wrapTrgWANumCachelines = 15; //num cachelines = 2^wrapTrgWANumCachelines
  TestParams->startBackground = DcttBackgroundPatternRowStripes;
  TestParams->endBackground = DcttBackgroundPatternRowStripes;
  TestParams->enableDummyReads = FALSE;
  TestParams->runTestPerBank = FALSE;
  TestParams->runTestOnSecondOrder = FALSE;
  TestParams->OptimizeSecondOrderRun = FALSE;
  TestParams->RefiMultiplier = 1;
  TestParams->pauseRefreshDelay = 0;
  TestParams->marginOperation = 0;
  TestParams->marginStartValue = 0;
  TestParams->marginStepValue = 0;
  TestParams->marginNumberSteps = 0;
  TestParams->HammerRefreshEnable = 0;
  Timing->RcdValue = 0;
  Timing->RpValue = 0;
  Timing->Cl = 0;
  Timing->Cwl = 0;
  Timing->RdPre = 0;
  Timing->WrPre = 0;
  TestParams->Vdd = 0;
  TestParams->StopOnMaxMarginErrors = FALSE;
  TestParams->SubMemoryRangeTest    = FALSE;
}

INT32
DcttPointRun (
  DCTT_API              *DcttMain,
  DCTT_POINT_RUN_CONFIG *PointRunConfig
  )
{
  DCTT_CONFIG_PARAMS *DcttRunConfig;
  UINT32 TotalNumberErrors;
  UINT8 i;
  UINT8 j;
  UINT8 Channel;
  UINT8 Rank;
  BOOLEAN ChannelHasRanksEnabled;
#ifndef DISABLE_SWIZZLE
  UINT8 SwappedElements[DCTT_MAX_NUM_SWIZZLE_LANES];
  Permutations_VARDEF (permutationsGen);
#endif
  Parser_VARDEF (parser);

  DcttRunConfig = &DcttMain->DcttConfigData;
#ifndef DISABLE_SWIZZLE
  Permutations_VARINIT (permutationsGen, (DcttRunConfig->maxLaneSwizzle + 1), DcttRunConfig->numberLanesSwizzle);
#endif

  DcttOutputPrint (DcttMain, "\n");
  DcttLogDebug (DcttMain, "++++++++++");
  DcttOutputPrint (DcttMain, "Starting Memory Tester");
  DcttLogDebug (DcttMain, "++++++++++");
  DcttOutputPrint (DcttMain, "\n\n");
  DcttOutputPrint (DcttMain, "Memory Traversing Order: ");
  DcttOutputPrint (DcttMain, getMemoryElementName (DcttRunConfig->firstOrder));
  DcttOutputPrint (DcttMain, ", ");
  DcttOutputPrint (DcttMain, getMemoryElementName (DcttRunConfig->secondOrder));
  DcttOutputPrint (DcttMain, ", ");
  DcttOutputPrint (DcttMain, getMemoryElementName (DcttRunConfig->thirdOrder));
  DcttOutputPrint (DcttMain, ", ");
  DcttOutputPrint (DcttMain, getMemoryElementName (DcttRunConfig->fourthOrder));
  DcttOutputPrint (DcttMain, "\n");
  DcttOutputPrint (DcttMain, "Values Written to WDB: ");
  if (DcttRunConfig->backgroundBase == DcttBackBaseCustom) {
    DcttOutputPrint (DcttMain, "User Defined");
  } else {
    DcttOutputPrint (DcttMain, getWDBPattern (DcttRunConfig->backgroundBase));
  }
  DcttOutputPrint (DcttMain, "\n");

  if (DcttRunConfig->traverseDiagonal) {
    DcttOutputPrint (DcttMain,"Diagonally traversing memory\n");
  }

  if (DcttRunConfig->addrSwizzleAlg == DcttAddrSwizzleAglWT) {
    DcttOutputPrint (DcttMain,"Number cachelines for wrap trigger: %d\n",DcttRunConfig->wrapTrgWANumCachelines);
  }

  CPGCFunctions_RefreshControl (DcttMain, TRUE);
  CPGCFunctions_PrintMemConfig (DcttMain);

  //If we are ignoring any Rank, print that
  for (Channel = 0; Channel < DCTT_MAX_NUM_CHANNELS; Channel++) {
    ChannelHasRanksEnabled = FALSE;
    for (Rank = 0; Rank < DCTT_MAX_RANK_IN_CHANNEL; Rank++) {
      if (DcttSysRankInChannelExistsFunc (DcttMain, 0, Channel, Rank)) {
        //The Rank exist in the system, check if it exists for the DCTT
        if (!DCTT_RankInChannelExists (DcttMain, 0, Rank, Channel)) {
          DcttOutputPrint (DcttMain, "Rank %d in Channel %d is masked. It won't be tested.\n", Rank, Channel);
        } else {
          ChannelHasRanksEnabled = TRUE;
        }
      }
    }
    if (!ChannelHasRanksEnabled) {
      //No ranks enabled on this Channel, disable it
      DcttRunConfig->channelBitMask = (DcttRunConfig->channelBitMask) & (~(1 << Channel));
      DcttOutputPrint (DcttMain, "Disabling Channel %d because it doesn't have any enabled Rank\n", Channel);
    }
  }

  if (DcttRunConfig->channelBitMask == 0) {
    DcttOutputPrint (DcttMain, "No Channel was enabled for testing.\n", Channel);
    DcttOutputPrint (DcttMain,"Finished testing memory\n");
    return DCTT_SUCCESS;
  }

#ifndef DISABLE_SWIZZLE
  if (DcttRunConfig->modifySwizzle) {
    CPGCFunctions_ChangeSwizzle (DcttMain, DcttRunConfig->swizzle);
  }
#endif

#ifndef DISABLE_DUMMY_READS
  if (DcttRunConfig->enableDummyReads) {
    CPGCFunctions_SetDummyReadRegisters (DcttMain);
  }
#endif

#ifndef DISABLE_SWIZZLE
  Permutation_CalculateNextValue (permutationsGen);
  do {
    UINT8 laneToSwap;

    for (laneToSwap = 0; laneToSwap < DcttRunConfig->numberLanesSwizzle; laneToSwap++) {
      UINT8 swapTemp;

      SwappedElements[laneToSwap] = Permutations_GetElement (permutationsGen, DcttRunConfig->numberLanesSwizzle - laneToSwap - 1);
      swapTemp = DcttRunConfig->swizzle[laneToSwap];
      DcttRunConfig->swizzle[laneToSwap] = DcttRunConfig->swizzle[ (SwappedElements[laneToSwap]) ];
      DcttRunConfig->swizzle[ (SwappedElements[laneToSwap]) ] = swapTemp;
    }

    CPGCFunctions_ChangeSwizzle (DcttMain, DcttRunConfig->swizzle);
    CPGCFunctions_PrintSwizzle (DcttMain);

    for (i = 0; i < DcttRunConfig->numberTests; i++) {
      DcttLogDebug (DcttMain, "--------");
      DcttOutputPrint (DcttMain,"Running test %d: ",i);
      DcttOutputPrint (DcttMain,DcttRunConfig->testStrings[i]);
      DcttLogDebug (DcttMain, "--------");
      DcttOutputPrint (DcttMain,"\n");

      for (j = DcttRunConfig->startBackground; j < (DcttRunConfig->endBackground + 1); j++) {
        INT16 retCode;

        Parser_VARINIT (parser, DcttMain, DcttRunConfig);
        Parser_ClearNumberErrors (parser);
        Parser_AddAddressStorage (parser, PointRunConfig->ErrorAddresses);

        DcttRunConfig->backgroundType = j;

        DcttOutputPrint (DcttMain,"Pattern: ");
        DcttOutputPrint (DcttMain, getBackgroundPattern (DcttRunConfig->backgroundType));
        DcttOutputPrint (DcttMain,"\n");

        CPGCFunctions_PreInit (DcttMain);
        CPGCFunctions_InitAddress (DcttMain);
        CPGCFunctions_InitData (DcttMain);
        CPGCFunctions_InitMisc (DcttMain);

        do {
          retCode = Parser_ParseSequences (parser, DcttRunConfig->testStrings[i]);
          DcttOutputPrint (DcttMain,"Finished Parser Iteration\n");
        } while (retCode == PARSER_ERROR_RERUN);

        DcttLogDebug (DcttMain, "\n\n\n");
      }
    }

    for (laneToSwap = 0; laneToSwap < DcttRunConfig->numberLanesSwizzle; laneToSwap++) {
      DcttRunConfig->swizzle[laneToSwap] = laneToSwap;
      DcttRunConfig->swizzle[ (SwappedElements[laneToSwap]) ] = SwappedElements[laneToSwap];
    }
  } while (Permutation_CalculateNextValue (permutationsGen) == TRUE);
#else
  for (Channel = 0; Channel < DCTT_MAX_NUM_CHANNELS; Channel++) {
    DcttOutputPrint (DcttMain, "Swizzle Ch %d: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 (fixed)\n", Channel);
  }

  for (i = 0; i < DcttRunConfig->numberTests; i++) {
    DcttOutputPrint (DcttMain,"Running test %d: ",i);
    DcttOutputPrint (DcttMain,DcttRunConfig->testStrings[i]);
    DcttOutputPrint (DcttMain,"\n");

    for (j = DcttRunConfig->startBackground; j < (DcttRunConfig->endBackground + 1); j++) {
      INT16 retCode;

      Parser_VARINIT (parser, DcttMain, DcttRunConfig);
      Parser_ClearNumberErrors (parser);
      Parser_AddAddressStorage (parser, PointRunConfig->ErrorAddresses);

      DcttRunConfig->backgroundType = j;

      DcttOutputPrint (DcttMain,"Pattern: ");
      DcttOutputPrint (DcttMain, getBackgroundPattern (DcttRunConfig->backgroundType));
      DcttOutputPrint (DcttMain,"\n");

      CPGCFunctions_PreInit (DcttMain, DcttRunConfig);
      CPGCFunctions_InitAddress (DcttMain, DcttRunConfig);
      CPGCFunctions_InitData (DcttMain, DcttRunConfig);
      CPGCFunctions_InitMisc (DcttMain, DcttRunConfig);

      do {
        retCode = Parser_ParseSequences (parser,DcttRunConfig->testStrings[i]);
        DcttOutputPrint (DcttMain,"Finished Parser Iteration\n");
      } while (retCode == PARSER_ERROR_RERUN);

      DcttLogDebug (DcttMain, "\n\n\n");
    }
  }
#endif
  TotalNumberErrors = SetContainer_NumberElements (PointRunConfig->ErrorAddresses);
  DcttOutputPrint (DcttMain, "Number of unique errors on run: %d\n", TotalNumberErrors);

  DcttLogDebug (DcttMain,"++++++++++");
  DcttOutputPrint (DcttMain,"Finished testing memory");
  DcttLogDebug (DcttMain,"++++++++++");
  DcttOutputPrint (DcttMain,"\n");

  return DCTT_SUCCESS;
}

///
/// Main Entry Point
///
INT32
DcttRun (
  DCTT_API  *DcttMain
  )
{
  DCTT_CONFIG_PARAMS      *DcttRunConfig;
  DCTT_POINT_RUN_CONFIG   PointRunConfig;
  DCTT_MARGIN_RUN_DATA    RunMarginData[NUMBER_MARGIN_RUNS_TO_STORE];
  SetContainer            MarginPointErrors[NUMBER_MARGIN_RUNS_TO_STORE];
  SetContainer            *MarginPointErrorsRef = NULL;
  SetStorage              AddrStorages[NUMBER_STORAGES_NEEDED];
  SetStorage              *ErrorStorage1;
  SetStorage              *ErrorStorage2;
  SetStorage              *ErrorStorage3;
  DCTT_SYSTEM_RESTORE     SystemRestore;
  BOOLEAN                 ContainerRetVal;
  INT32                   RetValue;
  INT32                   MarginValue;
  INT32                   StartMargin;
  INT32                   MarginStep;
  UINT32                  NumberGlobalErrors;
  UINT32                  NumberErrorsRun;
  UINT32                  NumberMissedErrors;
  UINT32                  NumberNewErrors;
  UINT32                  NumberCommonErrors;
  UINT32                  MarginRunNumber;
  UINT32                  TotalNumberSteps;
  UINT32                  RefiValue;
  UINT8                   Channel;
  UINT8                   Rank;
  UINT32                  NumCols;
  UINT32                  MaxNumCols;
  SetStorage_VARDEF (GlobalAddressStorage);
  SetContainer_VARDEF (GlobalErrorAddresses);

  DcttRunConfig = &DcttMain->DcttConfigData;
  DcttPrintVersion (DcttMain);
  RetValue = DcttConfigCheck (DcttMain);
  DcttError_Assert (DcttMain, RetValue == DCTT_SUCCESS, "Failed config parameters check.");
  if (RetValue != DCTT_SUCCESS) {
    return RetValue;
  }

  for (Channel = 0; Channel < DCTT_MAX_NUM_CHANNELS; Channel++) {
    DcttRunConfig->internalBottomAddress[Channel].Bank = DcttRunConfig->bottomAddress[Channel].Bank;
    DcttRunConfig->internalBottomAddress[Channel].Rank = DcttRunConfig->bottomAddress[Channel].Rank;
    DcttRunConfig->internalBottomAddress[Channel].Col = DcttRunConfig->bottomAddress[Channel].Col;
    DcttRunConfig->internalBottomAddress[Channel].Row = DcttRunConfig->bottomAddress[Channel].Row;
    DcttRunConfig->internalTopAddress[Channel].Bank = DcttRunConfig->topAddress[Channel].Bank;
    DcttRunConfig->internalTopAddress[Channel].Rank = DcttRunConfig->topAddress[Channel].Rank;
    DcttRunConfig->internalTopAddress[Channel].Col = DcttRunConfig->topAddress[Channel].Col;
    DcttRunConfig->internalTopAddress[Channel].Row = DcttRunConfig->topAddress[Channel].Row;
    if (DcttRunConfig->SubMemoryRangeTest) {
      DcttRunConfig->bottomAddress[Channel].Row = 0;
      DcttRunConfig->bottomAddress[Channel].Col = 0;
      MaxNumCols = 1024;
      for (Rank = 0; ((Rank < DcttRunConfig->numberRankPerChannel)); Rank++) {
        NumCols = DcttGetColumnSizeFunc (DcttMain, 0, Channel, (Rank / DCTT_MAX_RANK_IN_DIMM));
        if (NumCols > MaxNumCols) {
          MaxNumCols = NumCols;
        }
      }
      DcttLogDebug (DcttMain,"MaxNumCols on Channel %d: %d\n",Channel, MaxNumCols);
      DcttRunConfig->topAddress[Channel].Col    = MaxNumCols - CPGC_NUMBER_BYTES_CACHELINES;
    }
  }

  SysRestore_InitObject (DcttMain, &SystemRestore);
  DcttLogDebug (DcttMain, "Saving system registers\n");
  SysRestore_TakeSnapshot (DcttMain, &SystemRestore);

  SetStorage_VARINIT (GlobalAddressStorage);
  ErrorStorage1 = &(AddrStorages[0]);
  ErrorStorage2 = &(AddrStorages[1]);
  SetStorage_Init (ErrorStorage1);
  SetStorage_Init (ErrorStorage2);

  SetContainer_VARINIT (GlobalErrorAddresses, GlobalAddressStorage, ErrorStorage1, ErrorStorage2);

#ifndef DISABLE_MARGINING
  if (DcttRunConfig->marginOperation != NoMarginOperation) {
    StartMargin = DcttRunConfig->marginStartValue;
    TotalNumberSteps = DcttRunConfig->marginNumberSteps;
    MarginStep = DcttRunConfig->marginStepValue;
    DcttOutputPrint (
      DcttMain,
      "Running a Margin Test on %s from %d to %d in steps of %d\n",
      MarginStrings[DcttRunConfig->marginOperation],
      StartMargin,
      StartMargin + (TotalNumberSteps * MarginStep),
      MarginStep
      );
  } else {
    StartMargin = 0;
    TotalNumberSteps = 1;
    MarginStep = 1;
  }
#else
  StartMargin = 0;
  TotalNumberSteps = 1;
  MarginStep = 1;
#endif

  if (DcttRunConfig->RefiMultiplier > 1) {
    DcttOutputPrint (DcttMain,"Changing tRefi by a factor of %d\n", DcttRunConfig->RefiMultiplier);
    for (Channel = 0; Channel < DCTT_MAX_NUM_CHANNELS; Channel++) {
      RefiValue = DcttGetRefiFunc (DcttMain, 0, Channel) * DcttRunConfig->RefiMultiplier;
      RefiValue &= UINT16_MAX;
      DcttSetRefiFunc (DcttMain, 0, Channel, (UINT16) RefiValue);
    }
  }

  for (MarginRunNumber = 0; MarginRunNumber < TotalNumberSteps; MarginRunNumber++) {
    if (MarginRunNumber <= NUMBER_MARGIN_RUNS_TO_STORE) {
      DcttError_Assert (DcttMain, NUMBER_MARGIN_RUNS_TO_STORE >= 1,"Insufficient Error containers provided");
      MarginPointErrorsRef = &(MarginPointErrors[MarginRunNumber]);
      ErrorStorage3 = &(AddrStorages[MarginRunNumber + 2]);
      SetStorage_Init (ErrorStorage3);

      ContainerRetVal = SetContainer_ReturnAuxStorages (GlobalErrorAddresses, &ErrorStorage1, &ErrorStorage2);
      DcttError_Assert (DcttMain, ContainerRetVal, "Couldn't get back error storages");

      SetContainer_Init (MarginPointErrorsRef, ErrorStorage3, ErrorStorage1, ErrorStorage2);
    } else {
      DcttError_Assert (DcttMain, MarginPointErrorsRef != NULL, "Margin Point Error Object was not initialized");
      DcttOutputPrint (DcttMain, "Number of margin points requested is bigger than available storage.\n");
      DcttOutputPrint (DcttMain, "System will reuse last error address storage for future points.\n");

      ContainerRetVal = SetContainer_TransferAuxStorages (GlobalErrorAddresses, MarginPointErrorsRef);
      DcttError_Assert (DcttMain, ContainerRetVal, "Error transfer aux containers");
    }

    PointRunConfig.ErrorAddresses = MarginPointErrorsRef;
    MarginValue = StartMargin + (MarginRunNumber * MarginStep);

#ifndef DISABLE_MARGINING
    for (Channel = 0;  Channel < DCTT_MAX_NUM_CHANNELS; Channel++) {
      RetValue = MarginFunctions_ChangeMargin (DcttMain, Channel, DcttRunConfig->marginOperation, MarginValue);
      DcttError_Assert (DcttMain, RetValue == DCTT_SUCCESS, "Error while trying to change margin value");
    }
#endif
    SetContainer_Clear (PointRunConfig.ErrorAddresses);
    RetValue = DcttPointRun (DcttMain, &PointRunConfig);
    DcttError_Assert (DcttMain, RetValue == DCTT_SUCCESS, "Error while trying to run DCTT point test");
    //Checking how many of the found errors were on our global storage
    NumberCommonErrors = SetContainer_NumberCommonElements (MarginPointErrorsRef, GlobalErrorAddresses);
    NumberGlobalErrors = SetContainer_NumberElements (GlobalErrorAddresses);
    NumberErrorsRun = SetContainer_NumberElements (MarginPointErrorsRef);
    NumberNewErrors = NumberErrorsRun - NumberCommonErrors;
    NumberMissedErrors = NumberGlobalErrors - NumberCommonErrors;
    if (MarginRunNumber < NUMBER_MARGIN_RUNS_TO_STORE) {
      RunMarginData[MarginRunNumber].MarginValue = MarginValue;
      RunMarginData[MarginRunNumber].TotalErrors = NumberErrorsRun;
      RunMarginData[MarginRunNumber].MissedErrors = NumberMissedErrors;
      RunMarginData[MarginRunNumber].NewErrors = NumberNewErrors;
    }
    //Copying the run results to our global storage
    ContainerRetVal = SetContainer_TransferAuxStorages (MarginPointErrorsRef, GlobalErrorAddresses);
    DcttError_Assert (DcttMain, ContainerRetVal, "Error transfer aux containers");
    ContainerRetVal = SetContainer_ConsolidateContainers (GlobalErrorAddresses, MarginPointErrorsRef);
    if (ContainerRetVal == FALSE) {
      DcttOutputPrint (DcttMain, "Cannot consolidate errors to the global storage!\n");
      if (DcttRunConfig->StopOnMaxMarginErrors == TRUE) {
        break;
      }
      DcttOutputPrint (DcttMain, "Continuing error detection.  Unique/New/Total report will be incorrect!\n");
    }

    NumberGlobalErrors = SetContainer_NumberElements (GlobalErrorAddresses);
    DcttOutputPrint (DcttMain, "Number of new errors during run: %u\n", NumberNewErrors);
    DcttOutputPrint (DcttMain, "Number of errors missed by run: %u\n", NumberMissedErrors);
    DcttOutputPrint (DcttMain, "Total number of unique errors: %u\n", NumberGlobalErrors);
  }

  //
  // Need to do reset before restoring normal mode.
  //
  DcttResetFunc (DcttMain);
  DcttLogDebug (DcttMain,"\nRestoring system registers\n");
  SysRestore_RestoreSnapshot (DcttMain, &SystemRestore);

#ifndef DISABLE_MARGINING
  if (DcttRunConfig->marginOperation != NoMarginOperation) {
    UINT32 i, j, k;
    UINT32 commonErrorsRun, errorsRun1, errorsRun2;
    SetContainer *MarginPointErrorsRef1, *MarginPointErrorsRef2;

    MarginRunNumber = MIN (MarginRunNumber, NUMBER_MARGIN_RUNS_TO_STORE);

    // Margin Results
    DcttOutputPrint (DcttMain, "Margin Value - Total Errors - New Errors - Missed Errors\n");
    for (i = 0; i < MarginRunNumber; i++) {
      DcttOutputPrint (DcttMain, "%12d %14u %12u %15u\n", RunMarginData[i].MarginValue, RunMarginData[i].TotalErrors, RunMarginData[i].NewErrors, RunMarginData[i].MissedErrors);
    }

    DcttOutputPrint (DcttMain, "\nRun Comparisons: New Errors\n");
    //Print Header
    DcttOutputPrint (DcttMain, "        ");
    for (i = 0; i < MarginRunNumber; i++) {
      DcttOutputPrint (DcttMain, "%8d", RunMarginData[i].MarginValue);
    }
    DcttOutputPrint (DcttMain, "\n");
    for (i = 0; i < (MarginRunNumber - 1); i++) {
      MarginPointErrorsRef1 = &(MarginPointErrors[i]);
      errorsRun1 = SetContainer_NumberElements (MarginPointErrorsRef1);
      DcttOutputPrint (DcttMain, "%8d", RunMarginData[i].MarginValue);
      //Printing spaces
      for (k = 0; k < (i+1); k++) {
        DcttOutputPrint (DcttMain, "       X");
      }
      for (j = (i+1); j < MarginRunNumber; j++) {
        MarginPointErrorsRef2 = &(MarginPointErrors[j]);
        commonErrorsRun = SetContainer_NumberCommonElements (MarginPointErrorsRef1, MarginPointErrorsRef2);
        errorsRun2 = SetContainer_NumberElements (MarginPointErrorsRef2);
        DcttOutputPrint (DcttMain, "%8d", (errorsRun2 - commonErrorsRun));
      }
      DcttOutputPrint (DcttMain, "\n", RunMarginData[i].MarginValue);
    }

    // Errors Missed between runs.
    DcttOutputPrint (DcttMain, "\nRun Comparisons: Missed Errors\n");
    //Print Header
    DcttOutputPrint (DcttMain, "        ");
    for (i = 0; i < MarginRunNumber; i++) {
      DcttOutputPrint (DcttMain, "%8d", RunMarginData[i].MarginValue);
    }
    DcttOutputPrint (DcttMain, "\n", RunMarginData[i].MarginValue);
    for (i = 0; i < (MarginRunNumber - 1); i++) {
      MarginPointErrorsRef1 = &(MarginPointErrors[i]);
      errorsRun1 = SetContainer_NumberElements (MarginPointErrorsRef1);
      DcttOutputPrint (DcttMain, "%8d", RunMarginData[i].MarginValue);
      //Printing spaces
      for (k = 0; k < (i+1); k++) {
        DcttOutputPrint (DcttMain, "       X");
      }
      for (j = (i+1); j < MarginRunNumber; j++) {
        MarginPointErrorsRef2 = &(MarginPointErrors[j]);
        commonErrorsRun = SetContainer_NumberCommonElements (MarginPointErrorsRef1, MarginPointErrorsRef2);
        errorsRun2 = SetContainer_NumberElements (MarginPointErrorsRef2);
        DcttOutputPrint (DcttMain, "%8d", (errorsRun1 - commonErrorsRun));
      }
      DcttOutputPrint (DcttMain, "\n", RunMarginData[i].MarginValue);
    }
    DcttOutputPrint (DcttMain, "\nFinished Margin test\n");
  }
#endif

  return DCTT_SUCCESS;
}



/*
  Returns the DIMM Cell Test Tool's version number.

  @params[out] Version - Pointer to store version information

  @retval Nothing
*/
VOID
DcttGetVersion (
  DCTT_VERSION *Version
  )
{
  if (Version != NULL) {
    *Version = gDcttVersion;
  }
}

VOID
DcttPrintVersion (
  DCTT_API  *DcttMain
  )
{
  DcttOutputPrint (DcttMain, "*********************************************************************\n");
  DcttOutputPrint (DcttMain, "** Copyright (c) 2011-2013 Intel Corporation. All rights reserved. **\n");
  DcttOutputPrint (DcttMain, "** DIMM Cell Test Tool.                                            **\n");
  DcttOutputPrint (DcttMain, "** Major version number is:   %2u                                  **\n", gDcttVersion.Major);
  DcttOutputPrint (DcttMain, "** Minor version number is:   %2u                                  **\n", gDcttVersion.Minor);
  DcttOutputPrint (DcttMain, "** Rev version number is:     %2u                                  **\n", gDcttVersion.Revision);
  DcttOutputPrint (DcttMain, "** Build number is:           %2u                                  **\n", gDcttVersion.Build);
  DcttOutputPrint (DcttMain, "*********************************************************************\n");
}
