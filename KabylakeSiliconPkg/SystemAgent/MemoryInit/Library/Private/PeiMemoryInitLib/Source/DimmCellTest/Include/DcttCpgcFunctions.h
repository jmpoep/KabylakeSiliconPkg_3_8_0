/** @file
  DCTT CPGC definitions.

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

#ifndef _DCTT_CPGC_FUNCTIONS_H_
#define _DCTT_CPGC_FUNCTIONS_H_

#include "DcttSymbol.h"

#define CPGC_BASE_SUBSEQ_TYPE_READ 0
#define CPGC_BASE_SUBSEQ_TYPE_WRITE 1
#define CPGC_BASE_SUBSEQ_TYPE_BASE_READ_WRITE 2
#define CPGC_BASE_SUBSEQ_TYPE_WRITE_READ 3
#define CPGC_SUBSEQ_TYPE_OFFSET_OP_BASE 4
#define CPGC_SUBSEQ_TYPE_OFFSET_READ 4
#define CPGC_SUBSEQ_TYPE_OFFSET_WRITE 5

#define CPGC_ST_OFFSET_BASE_READ 0
#define CPGC_ST_OFFSET_BASE_WRITE 1
#define CPGC_ST_OFFSET_BASE_NONE 2

#define CPGC_CLEAR_ERRORS_START_TEST 5
#define CPGC_ERROR_STATUS_MASK 3
#define CPGC_TEST_DONE_MASK 0x30000

#define CPGC_OFFSET_TRIGGER_NONE 0
#define CPGC_OFFSET_TRIGGER_COL 1
#define CPGC_OFFSET_TRIGGER_ROW 2
#define CPGC_OFFSET_TRIGGER_COL_ROW 3

#define CPGC_NUMBER_BITS_CACHELINE 3
#define CPGC_NUMBER_BITS_COL 7
#define CPGC_CACHELINE_MASK_OFF  (~((1 << CPGC_NUMBER_BITS_CACHELINE) - 1))
#define CPGC_NUMBER_COLS (((1 << CPGC_NUMBER_BITS_COL) - 1) << CPGC_NUMBER_BITS_CACHELINE)
#define CPGC_NUMBER_BYTES_CACHELINES (1 << CPGC_NUMBER_BITS_CACHELINE)

#define CPGC_MAX_LOOPCOUNT        0xFFFFFFFF
#define CPGC_MAX_COL_UPDATE_RATE  20
#define CPGC_MAX_ROW_UPDATE_RATE  10
#define CPGC_MAX_BANK_UPDATE_RATE 23

typedef struct {
  UINT8   subsequenceWait;
  UINT32  seqBaseAddrOrderCarryInvertCtlVal[DCTT_MAX_NUM_CHANNELS];
} SeqHammerRegisterValues;

VOID
CPGCFunctions_SetRefreshDisableBitmask (
  DCTT_API  *DcttMain,
  UINT8     RankMask
  );

INT32
CPGCFunctions_PreInit (
  DCTT_API  *DcttMain
  );

/**
  This function handles entering and exiting Self Refresh mode.

  @param[in]  DcttMain  - Pointer to DCTT_API struct.
  @param[in]  Enable    - Boolean.  TRUE enables/enters Self Refresh, False disables/exits Self Refresh.

  @retval INT32 - DCTT_SUCCESS
**/
INT32
CPGCFunctions_RefreshControl (
  DCTT_API  *DcttMain,
  BOOLEAN   Enable
  );

INT32
CPGCFunctions_InitAddress (
  DCTT_API  *DcttMain
  );

INT32
CPGCFunctions_SetBackgroundBase (
  DCTT_API              *DcttMain,
  DCTT_BACKGROUND_BASE  Base
  );

INT32
CPGCFunctions_InitData (
  DCTT_API  *DcttMain
  );

INT32
CPGCFunctions_InitMisc (
  DCTT_API  *DcttMain
  );

INT32
CPGCFunctions_ErrorHandler (
  DCTT_API          *DcttMain,
  UINT8             TestMask,
  UINT32            *PerBankErrors,
  TestParameters    *GlobalParameters,
  UINT32            *BaseRowAddress,
  DCTT_DIMM_ADDRESS CurrentAddress[DCTT_MAX_NUM_CHANNELS]
  );

INT32
CPGCFunctions_ChangeDirection (
  DCTT_API  *DcttMain,
  MemTravDir NewDirection
  );

INT32
CPGCFunctions_SetSubsequenceCtrl (
  DCTT_API  *DcttMain,
  UINT8     SubsequenceNumber,
  BOOLEAN   InvertData,
  UINT32    Pattern,
  UINT32    SubsequenceType,
  UINT32    Delay,
  UINT32    RepeatRate,
  BOOLEAN   FinishOnWrap
  );

INT32
CPGCFunctions_SetSubsequenceOffsetCtrl (
  DCTT_API  *DcttMain,
  UINT8     SubsequenceNumber,
  UINT8     BaseInverted,
  UINT8     BaseSubseqType,
  UINT8     EnableRowIncrement,
  UINT8     EnableColIncrement,
  UINT8     RowIncrementOrder,
  UINT8     ColIncrementOrder,
  UINT8     BaseRepeatRate,
  UINT8     TriggerType,
  UINT8     OffsetAddrUpdateRate
  );

INT32
CPGCFunctions_ExecuteTest (
  DCTT_API        *DcttMain,
  UINT8           NumberSubsequences,
  RankErrors      *CurrentNumberErrors,
  MemTravDir      TestDirection,
  TestParameters  *GlobalParameters
  );

VOID
CPGCFunctions_PrintMemConfig (
  DCTT_API  *DcttMain
  );

INT32
CPGCFunctions_ModifiedExecuteTest (
  DCTT_API    *DcttMain,
  UINT8       NumberSubsequences,
  RankErrors  *CurrentNumberErrors,
  MemTravDir  TestDirection,
  BOOLEAN     IgnoreWrapError
  );

#ifndef DISABLE_SWIZZLE
INT32
CPGCFunctions_PrintSwizzle (
  DCTT_API  *DcttMain
  );

INT32
CPGCFunctions_ChangeSwizzle (
  DCTT_API  *DcttMain,
  UINT8     *NewSwizzle
  );
#endif

#ifndef DISABLE_DUMMY_READS
INT32
CPGCFunctions_SetDummyReadRegisters (
  DCTT_API  *DcttMain
  );
#endif

#ifndef DISABLE_SECOND_ORDER_TESTS

#ifndef DISABLE_UNOPTIMIZED_SECOND_ORDER
INT32
CPGCFunctions_ExecuteTestOnSecondOrder (
  DCTT_API        *DcttMain,
  UINT8           NumberSubsequences,
  MemTravDir      TestDirection,
  TestParameters  *GlobalParameters
  );
#endif

INT32
CPGCFunctions_CalculateRemainingLoopcount (
  DCTT_API          *DcttMain,
  MemTravDir        TestDirection,
  UINT32            *NewLoopcount,
  DCTT_DIMM_ADDRESS *CurrentAddress,
  UINT8             Channel,
  UINT32            HammerRepetitions,
  BOOLEAN           FirstBank,
  BOOLEAN           LastBank,
  BOOLEAN           InitialCalculation
  );

INT32
CPGCFunctions_ExecuteTestOnSecondOrderOptimized (
  DCTT_API            *DcttMain,
  UINT8               NumberSubsequences,
  MemTravDir          TestDirection,
  UINT32              HammerRepetitions,
  RunTestSymbolTypes  RunnerType,
  VOID                *RunnerParameters,
  TestParameters      *GlobalParameters
  );

VOID
CPGCFunctions_SetRegistersSequenceHammer (
  DCTT_API                *DcttMain,
  SeqHammerRegisterValues *RegValsStorage,
  TestParameters          *GlobalParams,
  UINT8                   NumberSubsequences
  );

VOID
CPGCFunctions_RestoreRegistersSequenceHammer (
  DCTT_API                *DcttMain,
  SeqHammerRegisterValues *RegValsStorage
  );
#endif

BOOLEAN
DCTT_RankInChannelExists (
  DCTT_API  *DcttMain,
  UINT8     Controller,
  UINT8     Rank,
  UINT8     Channel
  );

BOOLEAN
DCTT_ChannelExists (
  DCTT_API  *DcttMain,
  UINT8     Controller,
  UINT8     Channel
  );

UINT8
DCTT_GetChannelMask (
  DCTT_API  *DcttMain,
  UINT8     Controller
  );
#endif // _DCTT_CPGC_FUNCTIONS_H_
