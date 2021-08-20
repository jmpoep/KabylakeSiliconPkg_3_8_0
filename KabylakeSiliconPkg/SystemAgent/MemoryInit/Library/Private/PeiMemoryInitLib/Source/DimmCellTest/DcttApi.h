/** @file
  Dimm Cell Test Tool (DCTT) Api.  This file defines the configuration structure
  that the DCTT uses to determine the test to run.  In addition, it defines
  the Callback structure that the tool requires the caller to provide in
  order to perform the test.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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
#ifndef _DCTT_API_H_
#define _DCTT_API_H_
#include "DcttWrapper.h"

#pragma pack (push, 1)
///
/// DCTT enumerations and defines.
///
#define MAX_NUMBER_TESTS    10
#define DCTT_BYTE_CTL_NA    0
#define DCTT_CHANNEL_CTL_NA 0
#define DCTT_SUCCESS        0
#define DCTT_FAIL           (-1)

///
/// Special Row Swuzzle support.
/// @todo - Detail row swizzle per option
///
typedef enum {
  DcttRowSwizzleNone,
  DcttRowSwizzle3XOr1_3XOr2,
  DcttRowSwizzle01234567EFCDAB89,
  DcttRowSwizzleMax
} DCTT_ROW_SWIZZLE;

///
/// Defines what neighbors(NB) to check during a hammer test.
/// @todo - Detail pattern per option.
///
typedef enum {
  DcttHamerCheckNone,
  DcttHamerCheckRowNB,
  DcttHamerCheckColumnNB,
  DcttHamerCheckDiagonalNB,
  DcttHamerCheckAllNB,
  DcttHamerCheckAllBank,
  DcttHammerCheckMax
} DCTT_HAMMER_CHECK;

///
/// Testing Data Background
///
typedef enum {
  DcttBackBaseZeros,
  DcttBackBaseOnes,
  DcttBackBaseFive,
  DcttBackBaseA,
  DcttBackBaseCustom,
  DcttBackBaseMax
} DCTT_BACKGROUND_BASE;

///
/// Pattern of Background Base.
///
typedef enum {
  DcttBackgroundPatternSolid,
  DcttBackgroundPatternStripes,
  DcttBackgroundPatternRowStripes,
  DcttBackgroundPatternCheckerboard,
  DcttBackgroundPatternMax
} DCTT_BACKGROUND_PATTERN;

///
/// Row Address Swizzle algorithm.
///
typedef enum {
  DcttAddrSwizzleAglNone,
  DcttAddrSwizzleAglWT,
  DcttAddrSwizzleAlgMax
} DCTT_ADDR_SWIZZLE_ALG;

///
/// DcttLowerOrderLimit is used to size arrays based on Address type.
/// This depends on what address types are supported in the first and second order.
///
typedef enum {
  DcttOrderColumn,
  DcttOrderRow,
  DcttOrderBank,
  DcttOrderRank,
  DcttOrderMax,
  DcttOrderInvalid    = DcttOrderMax,
  DcttLowerOrderLimit = DcttOrderBank
} DCTT_ORDER_NAMES;

///
/// Log levels.  Compile flag to reduce debug code size is DCTT_DEBUG_LOG_LEVEL in DcttWrapper.h
///
typedef enum {
  DcttLogOff      = 0,
  DcttLogNormal   = 1,
  DcttLogVerbose  = 25,
  DcttLogDebug    = 50,
  DcttLogMax
} DCTT_LOG_LEVELS;

///
/// Forward declaration of DCTT_API
///
typedef struct _DCTT_API DCTT_API;

///
/// DCTT Structures
///
typedef struct {
  UINT32 Rank;
  UINT32 Bank;
  UINT32 Row;
  UINT32 Col;
} DCTT_DIMM_ADDRESS;

typedef struct {
  UINT8 RcdValue;
  UINT8 RpValue;
  UINT8 RasValue;
  UINT8 RdPre;
  UINT8 WrPre;
  UINT8 Cl;
  UINT8 Cwl;
} DCTT_TIMING_PARAMS;

typedef struct {
  UINT8 Major;
  UINT8 Minor;
  UINT8 Revision;
  UINT8 Build;
} DCTT_VERSION;

///
/// DCTT Configuration Structure
///
typedef struct {
  char                  *stringToParse; // @todo Check to remove
  DCTT_BACKGROUND_BASE  backgroundBase;                               ///< Control's the base data pattern
  UINT8                 backgroundType;
  UINT8                 numberChannels;
  UINT8                 numberRankPerChannel;
  UINT32                channelBitMask;                               ///< Specifies what Channels to run
  DCTT_ORDER_NAMES      firstOrder;
  DCTT_ORDER_NAMES      secondOrder;
  DCTT_ORDER_NAMES      thirdOrder;
  DCTT_ORDER_NAMES      fourthOrder;
  DCTT_DIMM_ADDRESS     bottomAddress[DCTT_MAX_NUM_CHANNELS];
  DCTT_DIMM_ADDRESS     topAddress[DCTT_MAX_NUM_CHANNELS];
  DCTT_ADDR_SWIZZLE_ALG addrSwizzleAlg;
  UINT8                 numberTests;
  char                  *testStrings[MAX_NUMBER_TESTS];
  UINT8                 DEBUGtestDirection;
  UINT8                 maxNumberErrors;
  BOOLEAN               failOnError;
  BOOLEAN               dontStopErrors;
  UINT8                 startTestDelay;
  UINT8                 subsequenceWait;
  UINT8                 wrapTrgWANumCachelines;
  UINT8                 startBackground;
  UINT8                 endBackground;                                ///< Ending Backgroung Pattern
  BOOLEAN               modifySwizzle;
  UINT8                 swizzle[DCTT_MAX_NUM_SWIZZLE_LANES];
  UINT8                 numberLanesSwizzle;
  UINT8                 maxLaneSwizzle;
  BOOLEAN               traverseDiagonal;
  BOOLEAN               enableDummyReads;
  BOOLEAN               runTestPerBank;
  BOOLEAN               runTestOnSecondOrder;
  BOOLEAN               OptimizeSecondOrderRun;
  UINT8                 RefiMultiplier;
  UINT8                 ranksToIgnoreBitMask[DCTT_MAX_NUM_CHANNELS];  ///< Mask to disable testing on a Rank.
  UINT32                pauseRefreshDelay;
  UINT32                marginOperation;
  INT32                 marginStartValue;
  UINT32                marginNumberSteps;
  INT32                 marginStepValue;
  UINT32                hammerRepetitions;                            ///< Number of Hammers per row.
  BOOLEAN               useWriteHammers;
  UINT32                hammerCheckType;
  UINT32                hammerPageCloseDelay;
  UINT32                rowSwizzleType;
  UINT32                BankDisableMask;
  BOOLEAN               singleRowForHammer;
  UINT32                hammerIterationsOnRow;                        ///< Number of times to repeat a row.
  BOOLEAN               HammerRefreshEnable;                          ///< Control's enabling Refresh/
  DCTT_TIMING_PARAMS    TimingParams;
  UINT16                Vdd;
  BOOLEAN               StopOnMaxMarginErrors;
  UINT64                CustomPattern;
  BOOLEAN               SubMemoryRangeTest;
  DCTT_DIMM_ADDRESS     internalBottomAddress[DCTT_MAX_NUM_CHANNELS];
  DCTT_DIMM_ADDRESS     internalTopAddress[DCTT_MAX_NUM_CHANNELS];
  CHAR8                 *ExecutingTestChars;
  UINT16                ExecutingTestCharsLen;
} DCTT_CONFIG_PARAMS;

///
/// DCTT System Callback Structure.
///
typedef struct {
  ///
  /// I/O Functions
  ///
  VOID    (*DcttWriteReg32)(DCTT_API *DcttMain, UINT32 Address, UINT32 Value);

  VOID    (*DcttWriteReg64)(DCTT_API *DcttMain, UINT32 Address, UINT64 Value);

  UINT32  (*DcttReadReg32)(DCTT_API *DcttMain, UINT32 Address);

  UINT64  (*DcttReadReg64)(DCTT_API *DcttMain, UINT32 Address);

  ///
  /// System Functions
  ///
  UINT8   (*DcttSysGetPresentChannelBitMask) (DCTT_API *DcttMain, UINT8 Controller);

  BOOLEAN (*DcttSysChannelExists) (DCTT_API *DcttMain, UINT8 Controller, UINT8 Channel);

  BOOLEAN (*DcttSysRankInChannelExists) (DCTT_API *DcttMain, UINT8 Controller, UINT8 Channel, UINT8 Rank);

  UINT32  (*DcttSysGetMcFrequency) (DCTT_API *DcttMain, UINT8 Controller);
  UINT32  (*DcttSysGetMcAddress) (DCTT_API *DcttMain, UINT32 Register, UINT8 Controller, UINT8 Channel, UINT8 ExtraIndex);

  UINT16  (*DcttSysGetRefi) (DCTT_API *DcttMain, UINT8 Controller, UINT8 Channel);

  VOID    (*DcttSysSetWdbFixedPat) (DCTT_API *DcttMain, UINT8 Controller, UINT8* Patterns, UINT8* Mask, UINT8 Spread, UINT8 Start);

  UINT16  (*DcttSysSetRefi) (DCTT_API *DcttMain, UINT8 Controller, UINT8 Channel, UINT16 Value);

  VOID    (*DcttSysEnterSelfRefresh) (DCTT_API *DcttMain);

  VOID    (*DcttSysExitSelfRefresh) (DCTT_API *DcttMain);

  VOID    (*DcttSysReset) (DCTT_API *DcttMain);

  VOID    (*DcttSysGetSetSelfRefreshConfig) (DCTT_API *DcttMain, BOOLEAN *SelfRefEnabled, UINT32 *IdleTimer, BOOLEAN GetSetFlag);

  ///
  /// DIMM Getters
  ///
  UINT32  (*DcttDimmGetRowSize) (DCTT_API *DcttMain, UINT8 Controller, UINT8 Channel, UINT8 Dimm);

  UINT16  (*DcttDimmGetColumnSize) (DCTT_API *DcttMain, UINT8 Controller, UINT8 Channel, UINT8 Dimm);

  UINT8   (*DcttDimmGetNumberOfRanks) (DCTT_API *DcttMain, UINT8 Controller, UINT8 Channel, UINT8 Dimm);

  UINT32  (*DcttDimmGetSize) (DCTT_API *DcttMain, UINT8 Controller, UINT8 Channel, UINT8 Dimm);

  ///
  /// DIMM Setters
  ///

  ///
  /// Setters that change DIMM and System settings
  ///
  UINT8   (*DcttSetCl) (DCTT_API *DcttMain, UINT8 Controller, UINT8 Channel, UINT8 Value);

  UINT8   (*DcttSetCwl) (DCTT_API *DcttMain, UINT8 Controller, UINT8 Channel, UINT8 Value);

  ///
  /// Debug Functions
  ///
  VOID    (*DcttSysPrint) (DCTT_API *DcttMain, char* FormatString, ...);

  ///
  /// @todo: Functions to be organized
  ///
  VOID    (*DcttSysWait) (DCTT_API *DcttMain, UINT32 DelaySysUnits);

  UINT64  (*DcttLeftShift64) (DCTT_API *DcttMain, UINT64 Data, UINT32 NumBits);

  UINT64  (*DcttRightShift64) (DCTT_API *DcttMain, UINT64 Data, UINT32 NumBits);
} DCTT_CALLBACK_FUNCTIONS;

struct _DCTT_API {
  DCTT_CALLBACK_FUNCTIONS DcttCbFunctions;  ///< Hooks required by DCTT to work.
  DCTT_CONFIG_PARAMS      DcttConfigData;   ///< Configuration specifying what type of test to run.
  DCTT_LOG_LEVELS         DebugLevel;       ///< Control dynamic level of printing.
  VOID                    *MrcData;         ///< MrcData structure to support callback functions.
  VOID                    *ReturnBufferPtr; ///< Optional return buffer for Error Addresses.
  UINT16                  RetBufferSize;    ///< Size in Bytes
};
#pragma pack (pop)

///
/// DCTT External Functions
///
/*
  Returns the DIMM Cell Test Tool's version number.

  @param[out] Version - Pointer to store version information

  @retval Nothing
*/
VOID
DcttGetVersion (
  DCTT_VERSION *Version
  );

/*
  Prints the DCTT version banner.

  @param[in] DcttMain - Dctt Global Data

  @retval Nothing
*/
VOID
DcttPrintVersion (
  DCTT_API  *DcttMain
  );

/*
  Function which initializes the config variables to do a basic memory test of:
    // TODO: Specify test movement

  @param[out] TestParams - Config variable to initialize

  @retval Nothing
*/
VOID
DcttSetDefaultParams (
  DCTT_CONFIG_PARAMS  *TestParams
  );

/*
  Executes a memory test based on the configuration data.

  @param[in] DcttMain - Dctt Global Data

  @retval Status of the test that was run.
*/
INT32
DcttRun (
  DCTT_API  *DcttMain
  );
#endif
