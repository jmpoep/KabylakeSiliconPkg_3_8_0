/** @file
  These functions implement the crosser training algorithm.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

@par Specification Reference:
**/
//
// Include files
//
#include "MrcCrosser.h"
#include "MrcWriteDqDqs.h"
#include "MrcReadDqDqs.h"
#include "MrcCommon.h"
#include "MrcMcConfiguration.h"

#if SUPPORT_SODIMM == SUPPORT
#include "MrcSpdProcessing.h"
#endif //SUPPORT_SODIMM == SUPPORT

///
/// Module Definitions
///
#define BIT_TX_XTALK_SWEEP_START  (-3)
#define BIT_TX_XTALK_SWEEP_STOP   (3)
#define BIT_TX_XTALK_SWEEP_LEN    (BIT_TX_XTALK_SWEEP_STOP - BIT_TX_XTALK_SWEEP_START + 1)
#define BIT_TX_XTALK_RANGE        (16)
#define DIMM_ODT_DIMM_MASK_SHIFT  (4)

///
/// Power optimizations Global Parameters
///
#define OPT_PARAM_LOOP_COUNT (15)
#define OPT_PARAM_1D_LC      (15)

///
/// UPM/PWR increment value if margins are at or below the retrain limit.
///
#define MRC_UPM_PWR_INC_VAL (80)

//Local functions
/**
  This function approximates a non linear heaviside function using 5 linear curves.
  The curves are defind by 3 paramters:
  a - The curve's slope
  b - Intercept with y axis.
  x_max - The maximal x value to which curve paramters apply. i.e., for x < x1 a = a1, b = b1.
  It should select a balanced wr/rd operating point with respect to UPM

  @param[in]     MrcCall          - FindOptimalTradeOff function , Inputs->Call.Func variable;
  @param[in]     PostMar            Margins array after training
  @param[in]     GoodPwrLimitPost   UPM limits for margins

  @Retval  linear approximation function output
**/
UINT64
LinearApproximationTradeOff (
  IN const MRC_FUNCTION * MrcCall,
  IN UINT32   PostMar,
  IN UINT16   GoodPwrLimitPost
);


//
// Module Globals
//
GLOBAL_REMOVE_IF_UNREFERENCED const MrcUpmPwrRetrainLimits  InitialLimits[MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS] = {
  //
  //           UPM,     PWR      Retrain
  //
  {RdT,       {240,     320,     90 }},
  {WrT,       {240,     320,     90 }},
  {RdV,       {400,     520,     160}},
  // For ULT DDR3L rcF the values are increased by 20 ticks, see MrcGetUpmPwrLimit()
  {WrV,       {400,     520,     170}},
  {RdFan2,    {240,     480,     0  }},
  {WrFan2,    {240,     480,     0  }},
  {RdFan3,    {240*4/5, 480*4/5, 0  }},
  {WrFan3,    {240*4/5, 480*4/5, 0  }},
  {CmdV,      {1300,    1300,    0  }}, // Decide on appropriate UPM limits for Cmd
  {CmdT,      {1300,    1300,    0  }},
  // algo. change in SKL we move only rcven pi's
  // {650ps,750ps} * 64 pi ticks * 2 (for width) = 134 PI Ticks ->  ~1.3nsec for UPM, 154 PI Ticks -> ~1.5nsec for PWR
  // Margin function works in steps of 4, so we divide the margin by 4.
  // Margin numbers are scaled by 10.
  {RcvEnaX,  { (134 / 4 * 10), (154 / 4 * 10), 0}}
};

GLOBAL_REMOVE_IF_UNREFERENCED const MrcOptParamsLimits  MrcOptParamLimit[MRC_NUMBER_OPT_PARAMS_TRAIN] = {
  //
  //                Normal/SAGV(high), SAGV (low), DT/Halo (max perf.)
  //
  {OptRdOdt,        {-15,  15}, {-15,  15}, {-5,   10}},
  {OptRxBias,       {0,    10}, {8,    15}, {8,    15}},
  {OptRxCb,         {0,     3}, {0,     3}, {0,     3}},
  {OptRxEq,         {0,     8}, {0,     8}, {0,     8}},
  {OptTxEq,         {5,    10}, {4,     8}, {6,    15}},
  {OptWrDS,         {-13,   2}, {-11,   0}, {-9,   10}},
  {OptWrDSDnCoarse, {-13,   2}, {-11,   0}, {-7,    7}},
  {OptWrDSUpCoarse, {-13,   2}, {-11,   0}, {-7,    7}},
  {OptSComp,        {-15,   5}, {-15,   5}, {-15,  10}},
  {OptCmdSComp,     {2,     8}, {2,     8}, {2,     8}}, // Scan range is in NumStages
  {OptCmdWrDS,      {-6,    7}, {-6,    7}, {-6,    7}},
  {OptCmdTxEq,      {0,     1}, {0,     1}, {0,     1}}
};

const MRC_RSM_POWER_FORMULA RSMPowerCalcTableRx[] = {
  //
  // CpuOdt, Dram_Odt, Mb_mail_len, Sodimm_len
  // table structure (from Struct def):
  //  {SysConfig}, Intercept0,
  //  {Intercept, FirstOrder, SecondOrder, {Interactions[MaxTxPowerParam]}
  //
  //
  // DDR4 Rx - will plan to use it for all Ddr tech - should be close enough
  //

  {{{f1333, MRC_DDR_TYPE_DDR4, 34, 0}},     105395535,
   {{300,   -5847,       12,    {0,     18,    1,    4}},
    {300,   -69132,     232,    {18,     0,    0,    3}},
    {1800,  925,         -2,    {1,      0,    0,   -4}},
    {500,   5016,        -1,    {4,      3,   -4,    0}}}},
  {{{f1333, MRC_DDR_TYPE_DDR4, 48, 0}},     92397977,
   {{300,   -7601,       18,    {0,     26,    0,    3}},
    {300,   -63125,     204,    {26,     0,    0,    2}},
    {1800,     330,      -1,    {0,      0,    0,   -2}},
    {500,     2957,       0,    {3,      2,   -2,    0}}}},
  {{{f1600, MRC_DDR_TYPE_DDR4, 34, 0}},     115767593,
   {{300,   -6506,       15,    {0,     15,   -3,    0}},
    {300,   -69132,      231,   {15,     0,    0,    3}},
    {1800,   -3171,       0,    {-3,     0,    0,   -2}},
    {500,      744,      -2,    {0,      3,   -2,    0}}}},
  {{{f1600, MRC_DDR_TYPE_DDR4, 48, 0}},     98453822,
   {{300,   -8211,       20,    {0,     23,    -2,   0}},
    {300,   -62632,     204,    {23,     0,    0,    2}},
    {1800,   -2023,       0,    {-2,     0,    0,   -1}},
    {500,      491,       0,    {0,      2,   -1,    0}}}},
  {{{f1867, MRC_DDR_TYPE_DDR4, 34, 0}},     109653751,
   {{300,   -6728,       17,    {0,     17,    0,    1}},
    {300,   -67527,     225,    {17,     0,    1,    0}},
    {1800,  -91,          3,    {0,      1,    0,    7}},
    {500,   1973,         0,    {1,      0,    7,    0}}}},
  {{{f1867, MRC_DDR_TYPE_DDR4, 48, 0}},     94425599,
   {{300,   -8145,       21,    {0,     25,    0,    2}},
    {300,   -62024,     200,    {25,     0,    1,    0}},
    {1800,  63,           2,    {0,      1,    0,    4}},
    {500,   1332,         0,    {2,      0,    4,    0}}}}
 };

const MRC_RSM_POWER_FORMULA RSMPowerCalcTableTx[] = {
  //
  // SR, Ron, TxEq, Mb_len
  // table structure (from Struct def):
  //  {SysConfig}, Intercept0,
  //  {Intercept, FirstOrder, SecondOrder, {Interactions[MaxTxPowerParam]}
  //
  // Table is arranged from low to high (DdrType(enu), Freq, Odt)
  //
  // DDR4 (6 params - SR, Ron, TxEq, Dimm Passive Odt, MBlength, SodimmLen)
  //
  {{{f1333, MRC_DDR_TYPE_DDR4, RttWrOff , 0}},  115462438,
  {{55,   26245,    205,    {0,    -1308,        3,      -18,       -2,        1}},
  {50,    -755958,  6427,   {-1308,    0,     -349,      305,      -59,      -24}},
  {409,   -13432,   27,     {3,     -349,        0,        7,        0,        0}},
  {300,   -32419,   90,     {-18,    305,        7,        0,        0,        0}},
  {1800,    1339,   -1,     {-2,     -59,        0,        0,        0,       -3}},
  {500,   104,      -1,     {1,      -24,        0,        0,       -3,        0}}}},
  {{{f1333, MRC_DDR_TYPE_DDR4, RttWr120 , 0}},  133044732,
  {{55,   26537,    198,    {0,    -1279,        5,       -4,       -1,        1}},
  {50,    -928307,  7413,   {-1279,    0,        -465,       287,      -40,    3}},
  {409,   -17043,   36,     {5,     -465,        0,        6,        0,        0}},
  {300,   -14221,   46,     {-4,     287,        6,        0,        0,        0}},
  {1800,  1030,     0,      {-1,     -40,        0,        0,        0,       -2}},
  {500,   -114,     -1,     {1,        3,        0,        0,       -2,        0}}}},
  {{{f1333, MRC_DDR_TYPE_DDR4, RttWr240 , 0}},  125126929,
  {{55,     26515,    211,  {0,     -1265,         3,      -15,       -2,        0}},
  {50,    -843921,  6705,   {-1265,     0,      -418,      325,      -48,      -12}},
  {409,   -15312,   30,     {3,      -418,         0,        6,        0,        0}},
  {300,   -20526,   61,     {-15,     325,         6,        0,        0,        0}},
  {1800,  1180,     -1,     {-2,      -48,         0,        0,        0,       -2}},
  {500,   -6,       -1,     {0,       -12,         0,        0,       -2,        0}}}},
  {{{f1600, MRC_DDR_TYPE_DDR4, RttWrOff , 0}},    125976146,
  {{55,   31187,    262,    {0,      -1473,       -8,        0,       -1,        3}},
  {50,    -793451,  7071,   {-1473,      0,     -388,      299,       23,       29}},
  {409,   -13601,   29,     {-8,      -388,        0,       10,        0,        0}},
  {300,   -32894,   90,     {0,         299,      10,        0,       -1,        0}},
  {1800,  -1699,    -1,     {-1,        23,        0,       -1,        0,        0}},
  {500,   -1855,     0,     {3,         29,        0,        0,        0,        0}}}},
  {{{f1600, MRC_DDR_TYPE_DDR4, RttWr120 , 0}},    141684820,
  {{55,   31563,    237,    {0,     -1481,        -1,       0,         0,        4}},
  {50,    -966674,  8023,   {-1481,     0,      -502,      284,        8,       34}},
  {409,   -17306,   38,     {-1,     -502,         0,       10,        0,        0}},
  {300,   -14414,   46,     {0,       284,        10,        0,        0,        0}},
  {500,   -994,     0,      {0,        8,          0,        0,        0,        0}},
  {500,   -1357,    0,      {4,        34,         0,        0,        0,        0}}}},
  {{{f1600, MRC_DDR_TYPE_DDR4, RttWr240 , 0}},    134734817,
  {{55,   31272,    262,    {0,     -1448,        -5,        0,       -1,        2}},
  {50,    -882744,  7319,   {-1448,     0,       -456,     321,        15,      29}},
  {409,   -15555,   33,     {-5,     -456,         0,       10,        0,        0}},
  {300,   -20861,   61,     {0,       321,        10,        0,        0,        0}},
  {1800,  -1321,   -1,      {-1,       15,         0,        0,        0,        0}},
  {500,   -1611,    0,      {2,        29,         0,        0,        0,        0}}}},
  {{{f1867, MRC_DDR_TYPE_DDR4, RttWrOff , 0}},    123734556,
  {{55,   34896,    283,    {0,     -1621,        -4,      -10,       -2,        4}},
  {50,    -797003,  7976,   {-1621,      0,     -380,      368,       21,       -7}},
  {409,   -14209,   29,     {-4,      -380,        0,        8,        0,       -2}},
  {300,   -33617,   92,     {-10,      368,        8,        0,        0,        0}},
  {1800,  -451,     2,      {-2,        21,        0,        0,        0,        6}},
  {500,   514,      1,      {4,         -7,        -2,       0,        6,        0}}}},
  {{{f1867, MRC_DDR_TYPE_DDR4, RttWr120 , 0}},    143297952,
  {{55,   35400,    315,    {0,    -1546,       -3,      -20,       -1,          2}},
  {50,    -984620,  8717,   {-1546,        0,     -519,      341,       13,     -9}},
  {409,   -18248,   36,     {-3,      -519,        0,        5,        0,        0}},
  {300,   -15136,   45,     {-20,      341,        5,        0,        0,        0}},
  {1800,  -454,     0,      {-1,        13,        0,        0,        0,        4}},
  {500,   566,      0,      {2,       -9,        0,        0,        4,          0}}}},
  {{{f1867, MRC_DDR_TYPE_DDR4, RttWr240 , 0}},    134001833,
  {{55,   35128,    293,    {0,      -1599,       -3,      -11,       -1,         4}},
  {50,    -892813,  8145,   {-1599,      0,     -458,      380,       17,        -6}},
  {409,   -16209,   33,     {-3,      -458,        0,        8,        0,        -1}},
  {300,   -21631,   64,     {-11,      380,        8,        0,        0,         0}},
  {1800,  -452,     1,      {-1,        17,        0,        0,        0,         5}},
  {500,   549,      1,      {4,          -6,      -1,        0,        5,         0}}}},
  //
  // DDR3L
  //
  {{{f1067, MRC_DDR_TYPE_DDR3, RttWrOff , 0}}, 108195563,
  {{61,   54259,    0,     {0,      -2300,  0,    0}},
  {44,   -902250,  8333,  {-2300,  0,      -419,  0}},
  {409,   -13407,  27,    {0,      -419,    0,    0}},
  {1799, 1780,    4,      {0,      0,      0,    0}}}},
  {{{f1333, MRC_DDR_TYPE_DDR3, RttWrOff , 0}}, 117762198,
  {{61,   57577,    0,     {0,      -3370,  0,    0}},
  {44,   -1049010,10594,  {-3370,  0,      -435,  0}},
  {409,   -14258,  31,    {0,      -435,    0,    0}},
  {1799, 5767,    -1,     {0,      0,      0,    0}}}},
  {{{f1600, MRC_DDR_TYPE_DDR3, RttWrOff , 0}}, 142022608,
  {{61,  71004,   0,      {0,     -1505,  0,    0}},
  {44,   -1188717,13516,  {-1505, 0,      -442, 0}},
  {409,  -14850,  35,     {0,     -442,   0,    0}},
  {1799, 212,    -5,      {0,     0,      0,    0}}}},
  {{{f1600, MRC_DDR_TYPE_DDR3, RttWr120 , 0}}, 190588495,
  {{61,   73392,    0,     {0,      -2263,  0,    0}},
  {44,   -1171460,13181,  {-2263,  0,      -444,  0}},
  {409,   -15220,  35,    {0,      -444,    0,    0}},
  {1799, 399,    -3,      {0,      0,      0,    0}}}},
  {{{f1600, MRC_DDR_TYPE_DDR3, RttWr240 , 0}}, 166151972,
  {{61,   72410,    0,     {0,      -1938,  0,    0}},
  {44,   -1179645,13282,  {-1938,  0,      -446,  0}},
  {409,   -15095,  35,    {0,      -446,    0,    0}},
  {1799, 330,    -4,      {0,      0,      0,    0}}}},
  {{{f1867, MRC_DDR_TYPE_DDR3, RttWrOff , 0}}, 151799958,
  {{61,  74728,   0,      {0,     -4192,  0,    0}},
  {44,   -1220099,15400,  {-4192, 0,      -414, 0}},
  {409,  -15832,  37,     {0,     -414,   0,    0}},
  {1799, -3968,   0,      {0,     0,      0,    0}}}},
  {{{f1867, MRC_DDR_TYPE_DDR3, RttWr120 , 0}}, 199558673,
  {{61,   78010,    0,     {0,      -4031,  0,    0}},
  {44,   -1208306,14614,  {-4031,  0,      -437,  0}},
  {409,   -15805,  36,    {0,      -437,    0,    0}},
  {1799, -2529,    0,     {0,      0,      0,    0}}}},
  {{{f1867, MRC_DDR_TYPE_DDR3, RttWr240 , 0}}, 175549579,
  {{61,   76658,    0,     {0,      -4083,  0,    0}},
  {44,   -1213480,14868,  {-4083,  0,      -431,  0}},
  {409,   -15840,  36,    {0,      -431,    0,    0}},
  {1799, -3213,    0,     {0,      0,      0,    0}}}},
  //
  // LPDDR3
  //
  {{{f1067, MRC_DDR_TYPE_LPDDR3, RttWrOff, 0}}, 106603589,
   {{80,   19833,    0,     {0,     -739,   0,    0}},
    {50,   -856523,  9074,  {-739,  0,      -273, 0}},
    {409,  -6926,    15,    {0,     -273,   0,    0}},
    {1099, 950,      -9,    {0,     0,      0,    0}}}},
  {{{f1333, MRC_DDR_TYPE_LPDDR3, RttWrOff, 0}}, 115178290,
   {{80,   24153,     0,    {0,      -1180,  0,    0}},
    {50,   -865982,   9677, {-1180, 0,      -327,  0}},
    {409,   -10515,   23,   {0,      -327,    0,    0}},
    {1099, -6601,     -3,   {0,      0,      0,    0}}}},
  {{{f1600, MRC_DDR_TYPE_LPDDR3, RttWrOff, 0}}, 114565521,
   {{80,   34158,    0,     {0,      -1467,  0,    0}},
    {50,   -846187,  10144, {-1467,  0,      -335,  0}},
    {409,   -13245,  29,    {0,      -335,    0,    0}},
    {1099, -9283,    1,     {0,      0,      0,    0}}}},
  {{{f1867, MRC_DDR_TYPE_LPDDR3, RttWrOff, 0}}, 107490163,
   {{80,   44175,    0,     {0,      -1861,  0,    0}},
    {50,   -825584,  10364, {-1861,  0,      -332,  0}},
    {409,   -14545,  33,    {0,      -332,    0,    0}},
    {1099, -5825,    9,     {0,      0,      0,    0}}}},
  {{{f1867, MRC_DDR_TYPE_LPDDR3, RttWr120, 0}}, 126800419,
   {{79,   45367,    0,     {0,      -1464,  0,    0}},
    {50,   -847125,  7984,  {-1464,  0,      -397,  0}},
    {409,   -14781,  32,    {0,      -397,    0,    0}},
    {1099, -5169,    8,     {0,      0,      0,    0}}}},
  {{{f1867, MRC_DDR_TYPE_LPDDR3, RttWr240, 0}}, 122800419,
   {{79,   45367,    0,     {0,      -1464,  0,    0}},
    {50,   -847125,  7984,  {-1464,  0,      -397,  0}},
    {409,   -14781,  32,    {0,      -397,    0,    0}},
    {1099, -5169,    8,     {0,      0,      0,    0}}}},

 };


const UINT8  gOptSlewRateCompParamList[] = { OptSComp, OptCmdSComp, OptCtlSComp, OptClkSComp };
const UINT8  gSlewRateCompParamList[]    = { SCompDq,  SCompCmd,    SCompCtl,    SCompClk    };

// The Minimal Stage delay [Psec] for slew rate programing, in order to avoid corner cases
const UINT8 gMinCycleStageDelay[] = { 46, 70, 70, 46 }; // Format: { SCompDq, SCompCmd, SCompCtl, SCompClk }

//
// DDR Params encoding
//

//
// Vref step size for the following: DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 VrefStepSize[] = { 96, 64, 64, 64, 64 };

#ifdef MRC_DEBUG_PRINT
// This must match TOptParamOffset
GLOBAL_REMOVE_IF_UNREFERENCED const char  *TOptParamOffsetString[] = {
  "WrDS",
  "SComp",
  "TComp",
  "TxEq",
  "RdOdt",
  "RxEq",
  "RxBias",
  "RxCb",
  "DimmOdt",
  "DimmOdtWr",
  "DimmOdtNom",
  "DimmOdtNomNT",
  "OptOdtPark",
  "OptOdtParkNT",
  "OptDimmOdtParkSlot1",
  "OptDimmOdtComb",
  "OptDimmOdtComb_1R1R",
  "DimmRon",
  "WrDSUp",
  "WrDSDn",
  "WrDSUpX",
  "WrDSDnX",
  "OptRdOdtUp",
  "OptRdOdtDn",
  "CtlDS",
  "ClkDS",
  "RxBiasCb",
  "TxEqWrDS",
  "CmdSR",
  "CtlSR",
  "ClkSR",
  "CmdWrDS",
  "CmdTxEq",
  "Default"
};

GLOBAL_REMOVE_IF_UNREFERENCED const char  *MarginTypesString[] = {
  "RcvEna", // 0
  "RdT",
  "WrT",
  "WrDqsT",
  "RdV",
  "WrV",
  "WrL",
  "WrTBox",
  "WrTBit",
  "RdTBit",
  "RdVBit", // 10
  "RcX",
  "CmdT",
  "CmdV",
  "",
  "",
  "RdFan2",
  "WrFan2",
  "",
  "",
  "", // 20
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "", // 30
  "",
  "RdFan3",
  "WrFan3",
  ""
};

///
/// These strings match the OptResultPerByteDbgStr enum for indexing
/// the switch PrintCalcResultTableCh and PrintODTResultTable.
///
GLOBAL_REMOVE_IF_UNREFERENCED const char *OptResultDbgStrings[] = {
  "Best",
  "GrdBnd",
  "OffSel",
  "Scale",
  "MaxPost",
  "MinPost"
};

//
// Strings for TGlobalCompOffset decoding
//
GLOBAL_REMOVE_IF_UNREFERENCED const char *GlobalCompOffsetStr[] = {
  "RdOdt",
  "WrDS",
  "WrDSCmd",
  "WrDSCtl",
  "WrDSClk",
  "SCompDq",
  "SCompCmd",
  "SCompCtl",
  "SCompClk",
  "DisOdtStatic"
};

const char *OdtTypeString[] = {
  "RttWr",
  "RttNom",
  "RttPark",
  "RttMaxType"
};

const char  *CmdIterTypesString[] = {
  "MrcIterationClock",
  "MrcIterationCmdN" ,
  "MrcIterationCmdS" ,
  "MrcIterationCke"  ,
  "MrcIterationCtl"  ,
  "MrcIterationCmdV"
};

#endif // MRC_DEBUG_PRINT

/**
  This function implements Sense Amp Offset training.
  SenseAmp/ODT offset cancellation
  Find the best "average" point for Vref Control
  Test Vref point with SampOffset=-7 and Test Vref Point with SampOffset=+7
  Find Vref on per ch/byte basis where -7 samples all 1 and +7 samples all 0

  @param[in,out] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeded return mrcSuccess
**/
MrcStatus
MrcSenseAmpOffsetTraining (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput                          *Inputs;
  MrcDebug                                *Debug;
  const MRC_FUNCTION                      *MrcCall;
  MrcIntOutput                            *MrcIntData;
  MrcOutput                               *Outputs;
  MrcControllerOut                        *ControllerOut;
  MrcChannelOut                           *ChannelOut;
  MrcIntControllerOut                     *IntControllerOut;
  MrcIntChannelOut                        *IntChannelOut;
  MrcStatus                               Status;
  UINT32                                  Offset;
  UINT16                                  OdtTarget;
  INT8                                    sumBits[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT8                                    FirstBestPoint[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT8                                    LastBestPoint[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  //
  // additional bit for DQS per each byte
  //
  INT8                                    firstZero[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS_FOR_OFFSET_TRAINING];
  //
  // additional bit for DQS per each byte
  //
  INT8                                    lastOne[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS_FOR_OFFSET_TRAINING];
  INT8                                    sampOffset;
  INT8                                    vref;
  INT8                                    VrefStep;
  INT8                                    VrefWidth;
  UINT8                                   HighMask[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8                                   LowMask[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8                                   Channel;
  UINT8                                   Rank;
  UINT8                                   byte;
  UINT8                                   bit;
  UINT8                                   MaxRank;
  UINT8                                   RankHalf;
  UINT8                                   RankMod2;
  UINT8                                   RankMask;
  INT8                                    LowVrefTested;
  INT8                                    HighVrefTested;
  BOOLEAN                                 Lpddr;
  BOOLEAN                                 Ddr4;
  BOOLEAN                                 StrongWkLeaker;
  BOOLEAN                                 VrefStageFailed;
  DDRDATACH0_CR_DDRCRDATACONTROL0_STRUCT  DdrCrDataControl0;
  DDRDATACH0_CR_DDRCRDATACONTROL1_STRUCT  DdrCrDataControl1;
  DDRDATA0CH0_CR_DDRCRDATACONTROL2_STRUCT DdrCrDataControl2;
  DDRDATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DataTrainFeedback;
  DDRCOMP_CR_DDRCRCOMPCTL2_STRUCT         DdrCrCompCtl2;
  UINT32                                  RxOffsetVdq;
  UINT32                                  RankForRegFile[MAX_CHANNEL];
  DDR4_MODE_REGISTER_5_STRUCT             Ddr4ModeRegister5;

  MrcIntData       = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs           = &MrcData->Inputs;
  MrcCall          = Inputs->Call.Func;
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  ControllerOut    = &Outputs->Controller[0];
  IntControllerOut = &MrcIntData->Controller[0];
  Status           = mrcSuccess;
  Lpddr            = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  Ddr4             = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  MaxRank          = MAX_RANK_IN_CHANNEL;

  VrefStageFailed = FALSE;
  LowVrefTested  = -31;
  HighVrefTested = 31;

  VrefStep = 1;

  StrongWkLeaker = Lpddr;

  //
  // Init LastBestPoint to 0, FirstBestPoint to -8, LowMask to 0xff and HighMask to 0
  //
  MrcCall->MrcSetMem ((UINT8 *) LastBestPoint, sizeof (LastBestPoint), 0);
  MrcCall->MrcSetMem ((UINT8 *) FirstBestPoint, sizeof (FirstBestPoint), (UINT8) (LowVrefTested));
  MrcCall->MrcSetMem ((UINT8 *) LowMask, sizeof (LowMask), (UINT8) (-1));
  MrcCall->MrcSetMem ((UINT8 *) HighMask, sizeof (LowMask), 0);

  if (Ddr4) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        //
        // Disable RttPark on DDR4
        //
        RankMask = 1 << Rank;
        RankHalf = Rank / 2;
        RankMod2 = Rank % 2;
        Ddr4ModeRegister5.Data = ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR5];
        Ddr4ModeRegister5 = UpdateRttParkValue_DDR4 (MrcData, 0, Ddr4ModeRegister5);
        Status = MrcWriteMRS (MrcData, Channel, RankMask, mrMR5, (UINT16) Ddr4ModeRegister5.Data);
        //
        // Set CPU Read Vref to 0 which is Vdd/2 for CTT mode
        //
        for (byte = 0; byte < Outputs->SdramCount; byte++) {
          ChannelOut->RxVref[byte] = 0;
          UpdateRxTValues (MrcData, Channel, Rank, byte, 0xFF, 0);
        } // for byte
        //
        // Download new settings from the RegFile to the Pads, using broadcast to all bytes in the channel
        //
        MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);
      } // for Rank
    } // for Channel
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Stage 1: Vref Offset Training\nPlot Of SumOfBits across Vref settings\nChannel\t0\t\t1\nByte\t"
    );
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8\n" : "0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7\n"
    );

  //
  // Find one populated rank for the purpose of Reg File read, per channel
  //
  RankForRegFile[0] = 0;
  RankForRegFile[1] = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          RankForRegFile[Channel] = Rank;
          break;
        }
      }
    }
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel) || Inputs->EnVttOdt) {
      IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
      //
      // Set ForceBiasOn and ForceRxOn, clear EnVddqOdt and EnVttOdt
      //
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        DdrCrDataControl2.Data              = IntChannelOut->DqControl2[byte].Data;
        DdrCrDataControl2.Bits.ForceBiasOn    = 1;
        DdrCrDataControl2.Bits.ForceRxOn      = 1;
        DdrCrDataControl2.Bits.EnVddqOdt      = 0;
        DdrCrDataControl2.Bits.EnVttOdt       = 0;
        DdrCrDataControl2.Bits.RxVrefProgMFC  = 0;
        Offset = MrcGetOffsetDataControl2 (MrcData, Channel, byte);
        MrcWriteCR (MrcData, Offset, DdrCrDataControl2.Data);
      }
    }
  }
  if (Inputs->EnVttOdt || Ddr4) {
    DdrCrCompCtl2.Data = IntControllerOut->CompCtl2.Data;
    DdrCrCompCtl2.Bits.EnVttOdt  = 0;
    DdrCrCompCtl2.Bits.EnVddqOdt = 0;
    MrcWriteCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL2_REG, DdrCrCompCtl2.Data);
    OdtTarget = Inputs->RcompTarget[RdOdt];
    if (Inputs->EnVttOdt) {
      OdtTarget = OdtTarget * 2;  // The function will use 1 segment but we want CTT mode
    }
    UpdateCompTargetValue (MrcData, RdOdt, OdtTarget, 1);
  }
  //
  // Sweep through vref settings and find point SampOffset of +/- 7 passes
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "1/2 Vref");
  for (vref = LowVrefTested; vref <= HighVrefTested; vref += VrefStep) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 5d\t", vref);

    //
    // Run Test and Record Results.
    //
    Status = ChangeMargin (MrcData, RdV, vref, 0, 1, 0, 0, 0, 0, 0, 0, MrcRegFileRank);

    //
    // Program settings for Vref and SampOffset = 7
    //
    MrcSetRxOffsetVdqBroadcast (MrcData, 0xFF, 0xFF, 0xFFFFFFFF); // (8+7)
    //
    // To run test, enable Offset Cancel mode and Enable ODT
    // Check Results and Update variables.  Ideal result is all 0
    // Clear Offset Cancel mode at end test to enable writing RX_OffsetV
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        IntChannelOut = &IntControllerOut->Channel[Channel];

        //
        // Propagate delay values (without a read command)
        //
        DdrCrDataControl0.Data                      = IntChannelOut->DqControl0.Data;
        DdrCrDataControl0.Bits.ReadRFRd             = 1;
        DdrCrDataControl0.Bits.ReadRFWr             = 0;
        DdrCrDataControl0.Bits.ReadRFRank           = RankForRegFile[Channel];
        DdrCrDataControl0.Bits.ForceOdtOn           = 1;
        DdrCrDataControl0.Bits.SenseampTrainingMode = 1;
        Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
        MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);

        MrcWait (MrcData, HPET_1US);

        DdrCrDataControl0.Bits.ReadRFRd             = 0;
        DdrCrDataControl0.Bits.SenseampTrainingMode = 0;
        Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
        MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);

        for (byte = 0; byte < Outputs->SdramCount; byte++) {
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, byte);
          DataTrainFeedback.Data  = (UINT8) MrcReadCR (MrcData, Offset);
          sumBits[Channel][byte]  = - (MrcCountBitsEqOne (DataTrainFeedback.Bits.DataTrainFeedback));
          LowMask[Channel][byte] &= (UINT8) DataTrainFeedback.Bits.DataTrainFeedback;
        }
      }
    }
    //
    // Program settings for SampOffset = -7
    //
    MrcSetRxOffsetVdqBroadcast (MrcData, 0xFF, 0xFF, 0x11111111); // (8-7)

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          (Channel != 0) ? "" : ((Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "                  " : "                ")
          );
      } else {
        IntChannelOut = &IntControllerOut->Channel[Channel];
        ChannelOut    = &ControllerOut->Channel[Channel];

        //
        // Propagate delay values (without a read command)
        //
        DdrCrDataControl0.Data                      = IntChannelOut->DqControl0.Data;
        DdrCrDataControl0.Bits.ReadRFRd             = 1;
        DdrCrDataControl0.Bits.ReadRFWr             = 0;
        DdrCrDataControl0.Bits.ReadRFRank           = RankForRegFile[Channel];
        DdrCrDataControl0.Bits.ForceOdtOn           = 1;
        DdrCrDataControl0.Bits.SenseampTrainingMode = 1;
        Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
        MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);

        MrcWait (MrcData, HPET_1US);

        DdrCrDataControl0.Bits.ReadRFRd             = 0;
        DdrCrDataControl0.Bits.SenseampTrainingMode = 0;
        Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
        MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);

        for (byte = 0; byte < Outputs->SdramCount; byte++) {
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, byte);
          DataTrainFeedback.Data = (UINT8) MrcReadCR (MrcData, Offset);
          sumBits[Channel][byte] += MrcCountBitsEqOne (DataTrainFeedback.Bits.DataTrainFeedback);
          HighMask[Channel][byte] |= DataTrainFeedback.Bits.DataTrainFeedback;

          //
          // Check if this point is better
          //
          if (sumBits[Channel][byte] > FirstBestPoint[Channel][byte]) {
            FirstBestPoint[Channel][byte] = sumBits[Channel][byte];
            LastBestPoint[Channel][byte]  = vref;
            ChannelOut->RxVref[byte]      = vref;
          } else if (sumBits[Channel][byte] == FirstBestPoint[Channel][byte]) {
            LastBestPoint[Channel][byte] = vref;
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d ", sumBits[Channel][byte]);
        }
      }
    }
  } // for vref

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nHi-Lo\t");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "0x%x 0x%x ", HighMask[Channel][byte], LowMask[Channel][byte]);
        //
        // Exit with error if any bit did not change
        //
        if ((HighMask[Channel][byte] ^ LowMask[Channel][byte]) != 0xFF) {
          VrefStageFailed = TRUE;
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_ERROR,
            "\nERROR! At least one bit with unexpected results for Channel %u Byte %u\n",
            Channel,
            byte
            );
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_ERROR,
            "A '0' in the following BitMask value represents the failing Bit(s) 0x%x\n",
            (HighMask[Channel][byte] ^ LowMask[Channel][byte])
            );
        }
      }
    }
  }

  if (VrefStageFailed && Inputs->ExitOnFailure) {
    return mrcSenseAmpErr;
  }

  // Display the selected Read Vref per byte
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRdVref\t");
#endif // MRC_DEBUG_PRINT
  //
  // Clear RdV offset
  //
  Status = ChangeMargin (MrcData, RdV, 0, 0, 1, 0, 0, 0, 0, 0, 0, MrcRegFileRank);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      //
      // Upate RxVref delay center
      //
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        VrefWidth = (INT8) (LastBestPoint[Channel][byte] - ChannelOut->RxVref[byte]);
        vref      = (INT8) (ChannelOut->RxVref[byte] + (VrefWidth / 2));

        //
        // Add 1 to Round Up and find the center
        //
        if (vref < 0) {
          vref--;
        } else {
          vref++;
        }
        //
        // step size for RxVref is about 7.8mv AND for RxVrefOffset is about 3.9mv
        //
        ChannelOut->RxVref[byte] = vref / 2;

        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            UpdateRxT (MrcData, Channel, Rank, byte, 0xFF, 0);
          }
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d ", (INT8) ChannelOut->RxVref[byte]);
      }
    }
  }
  //
  // init firstZero and lastOne to 0
  //
  MrcCall->MrcSetMem ((UINT8 *) firstZero, sizeof (firstZero), 0);
  MrcCall->MrcSetMem ((UINT8 *) lastOne, sizeof (lastOne), 0);

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nStage 2: SampOffset Training\nChannel 0\t\t\t\t\t\t\t\t\t \t1\nByte    ");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (byte = 0; byte < Outputs->SdramCount; byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d         ", byte);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nBits    ");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (byte = 0; byte < Outputs->SdramCount; byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "01234567S ");
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n SAmp");
#endif // MRC_DEBUG_PRINT

  for (sampOffset = 1; sampOffset <= 15; sampOffset++) {
    //
    // Display per Byte Feedback from REUT Registers
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 5d\t", sampOffset);

    //
    // Program Offset and Propagate new value from RF
    //
    RxOffsetVdq = 0;
    for (bit = 0; bit < MAX_BITS; bit++) {
      RxOffsetVdq += (sampOffset & DDRDATA_CR_RXOFFSETVDQRANK0_Lane0_MSK) << (DDRDATA_CR_RXOFFSETVDQRANK0_Lane0_WID * bit);
    }
    MrcSetRxOffsetVdqBroadcast (MrcData, 0xFF, 0xFF, RxOffsetVdq);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t\t\t");
        continue;
      }

      IntChannelOut = &IntControllerOut->Channel[Channel];
      //
      // write DQS offset to control2 reg sampOffset
      //
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        DdrCrDataControl2.Data                = IntChannelOut->DqControl2[byte].Data;

        DdrCrDataControl2.Bits.RxDqsAmpOffset = sampOffset;
        DdrCrDataControl2.Bits.ForceBiasOn    = 1;
        DdrCrDataControl2.Bits.ForceRxOn      = 1;
        DdrCrDataControl2.Bits.EnVddqOdt      = 0;
        DdrCrDataControl2.Bits.EnVttOdt       = 0;
        DdrCrDataControl2.Bits.LeakerComp     = 0;
        DdrCrDataControl2.Bits.RxVrefProgMFC  = 0;

        Offset = MrcGetOffsetDataControl2 (MrcData, Channel, byte);
        MrcWriteCR (MrcData, Offset, DdrCrDataControl2.Data);
        if (StrongWkLeaker) {
          Offset = MrcGetOffsetDataControl1 (MrcData, Channel, byte);
          DdrCrDataControl1.Data = IntChannelOut->DqControl1[byte].Data;
          DdrCrDataControl1.Bits.StrongWkLeaker = 0;
          MrcWriteCR (MrcData, Offset, DdrCrDataControl1.Data);
        }
      }
      //
      // Propagate delay values (without a read command)
      //
      DdrCrDataControl0.Data                      = IntChannelOut->DqControl0.Data;
      DdrCrDataControl0.Bits.ReadRFRd             = 1;
      DdrCrDataControl0.Bits.ReadRFWr             = 0;
      DdrCrDataControl0.Bits.ReadRFRank           = RankForRegFile[Channel];
      DdrCrDataControl0.Bits.ForceOdtOn           = 1;
      DdrCrDataControl0.Bits.SenseampTrainingMode = 1;
      Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
      MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);

      MrcWait (MrcData, HPET_1US);

      DdrCrDataControl0.Bits.ReadRFRd             = 0;
      DdrCrDataControl0.Bits.SenseampTrainingMode = 0;
      Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
      MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);

      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, byte);
        DataTrainFeedback.Data = MrcReadCR (MrcData, Offset);
        //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DataTrainFeedback = 0x%x, sampOffset = %d\n", DataTrainFeedback.Data, sampOffset);

        for (bit = 0; bit < MAX_BITS_FOR_OFFSET_TRAINING; bit++) {
          if (DataTrainFeedback.Bits.DataTrainFeedback & (MRC_BIT0 << bit)) {
            lastOne[Channel][byte][bit] = sampOffset;
          } else {
            if (firstZero[Channel][byte][bit] == 0) {
              firstZero[Channel][byte][bit] = sampOffset;
            }
          }
          //
          // Display in bits
          //
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            ((MRC_BIT0 << bit) & DataTrainFeedback.Bits.DataTrainFeedback) ? "1" : "0"
            );
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " ");
      }
    } // for Channel
  } // for sampOffset

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nBitSAmp ");

  //
  // Calculate and Program Offsets and display per bit SenseAmp Offset
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t\t\t"); // Line up Channel 1
      continue;
    }
    ChannelOut    = &ControllerOut->Channel[Channel];
    IntChannelOut = &IntControllerOut->Channel[Channel];
    for (byte = 0; byte < Outputs->SdramCount; byte++) {
      RxOffsetVdq = 0;
      for (bit = 0; bit < MAX_BITS_FOR_OFFSET_TRAINING; bit++) {
        //
        // Find vref center, add 1 for Round Up
        //
        vref = (firstZero[Channel][byte][bit] + lastOne[Channel][byte][bit]) / 2;

        //
        // Check for saturation conditions
        // to make sure we are as close as possible to vdd/2 (750mv)
        //
        if (firstZero[Channel][byte][bit] == 0) {
          vref = 15;
        }

        if (lastOne[Channel][byte][bit] == 0) {
          vref = 0;
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%X", vref);
        if (bit == 8) {
          //
          // Write the DQS sense amp offset value to the host struct.
          // It will be written to the HW at the end of this routine.
          //
          // Add 8 to the center value, to better suppress DQS reflections before the read preamble on LPDDR3
          //
          if (Lpddr) {
            vref += 8;
          }
          IntChannelOut->DqControl2[byte].Bits.RxDqsAmpOffset = MIN (vref, DDRDATA_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MAX);
          break;
        }

        RxOffsetVdq += (vref & DDRDATA_CR_RXOFFSETVDQRANK0_Lane0_MSK) << (DDRDATA_CR_RXOFFSETVDQRANK0_Lane0_WID * bit);
        for (Rank = 0; Rank < MaxRank; Rank++) {
          ChannelOut->RxDqVrefPb[Rank][byte][bit].Center = vref;
        }
      } // for Bit

      for (Rank = 0; Rank < MaxRank; Rank++) {
        MrcSetRxOffsetVdq (MrcData, Channel, Rank, byte, RxOffsetVdq);
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " ");
    } // for Byte

    for (Rank = 0; Rank < MaxRank; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        //
        // Propagate delay values (without a read command)
        //
        MrcDownloadRegFile (MrcData, Channel, 1, Rank, MrcRegFileRank, 0, 1, 0);
      }
    }
  } // for Channel
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  //
  // Clean up after test
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel) || Inputs->EnVttOdt) {
      ChannelOut    = &ControllerOut->Channel[Channel];
      IntChannelOut = &IntControllerOut->Channel[Channel];
      //
      // Restore DataControl0 - do it first, to disable ForceOdtOn before ODT mode switch
      //
      Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
      MrcWriteCrMulticast (MrcData, Offset, IntChannelOut->DqControl0.Data);
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        //
        // Restore DataControl2
        //
        Offset = MrcGetOffsetDataControl2 (MrcData, Channel, byte);
        MrcWriteCR (MrcData, Offset, IntChannelOut->DqControl2[byte].Data);

        //
        // Restore DataControl1
        //
        if (StrongWkLeaker) {
          Offset = MrcGetOffsetDataControl1 (MrcData, Channel, byte);
          MrcWriteCR (MrcData, Offset, IntChannelOut->DqControl1[byte].Data);
        }

        if (Inputs->EnVttOdt) {
          //
          // Put RxVref back to zero in VTT mode
          //
          ChannelOut->RxVref[byte] = 0;
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
              UpdateRxT (MrcData, Channel, Rank, byte, 0xFF, 0);
            }
          }
        }
      } // for byte
    }
  }

  if (Inputs->EnVttOdt || Ddr4) {
    MrcWriteCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL2_REG, IntControllerOut->CompCtl2.Data);
    UpdateCompTargetValue (MrcData, RdOdt, Inputs->RcompTarget[RdOdt], 1);
  }

  if (Ddr4) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        RankMask = 1 << Rank;
        RankHalf = Rank / 2;
        RankMod2 = Rank % 2;
        //
        // Restore RTT_PARK for this rank
        //
        Ddr4ModeRegister5.Data = ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR5];
        Status = MrcWriteMRS (MrcData, Channel, RankMask, mrMR5, (UINT16) Ddr4ModeRegister5.Data);
      } // for Rank
    } // for Channel
    //
    // Restore CPU Read Vref to match Vddq termination
    //
    MrcSetDefaultRxVrefDdr4 (MrcData, FALSE,  TRUE);
  }

  Status = IoReset (MrcData);

  return Status;
}

/**
  This function looks at the margin values stored in the global data structure and checks
  WrT, WrV, RdT, and RdV to see if they are above the minimum margin required.

  @param[in, out] MrcData - MRC global data.

  @retval mrcSuccess if margins are acceptable.
  @retval Otherwise, mrcRetrain.
**/
MrcStatus
MrcRetrainMarginCheck (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcDebug                *Debug;
  MrcOutput               *Outputs;
  MrcIntOutput            *IntOutputs;
  MrcControllerOut        *ControllerOut;
  MrcUpmPwrRetrainLimits  *UpmPwrRetrainLimits;
  MRC_FUNCTION            *MrcCall;
  MRC_MarginTypes         MarginParam;
  MrcMarginResult         LastResultParam;
  MrcStatus               Status;
  MRC_MARGIN_LIMIT_TYPE   MarginLimitType;
  UINT32                  (*LastMargins) [MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32                  BERStats[4];
  UINT16                  MinEdgeMargin[MAX_EDGES];
  UINT16                  RetrainMarginLimit;
  UINT16                  RetrainMarginLimitArr[MAX_RESULT_TYPE];
  UINT16                  CurrentMargin;
  UINT8                   Channel;
  UINT8                   ChannelMask;
  UINT8                   Rank;
  UINT8                   RankMask;
  UINT8                   Edge;
  UINT8                   Loopcount;
  UINT8                   MaxMargin;
  BOOLEAN                 RdWrMarginFail[2];
  BOOLEAN                 Ddr4;

  MrcCall             = MrcData->Inputs.Call.Func;
  IntOutputs          = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  ControllerOut       = &Outputs->Controller[0];
  LastMargins         = Outputs->MarginResult;
  UpmPwrRetrainLimits = IntOutputs->UpmPwrRetrainLimits.Pointer;
  Status              = mrcSuccess;
  Loopcount           = 17;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) RetrainMarginLimitArr, sizeof (RetrainMarginLimitArr), 0);
  RdWrMarginFail[0] = FALSE;
  RdWrMarginFail[1] = FALSE;

  Ddr4  = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);


  //
  // Loop is dependent on the order of MRC_MarginTypes.  If this changes, pleas ensure functionality
  // stays the same.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Loopcount: %d\n", Loopcount);
  SetupIOTestBasicVA (MrcData, Outputs->ValidChBitMask, Loopcount, NSOE, 0, 0, 8);
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask    = 1 << Rank;
    ChannelMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelMask |= SelectReutRanks (MrcData, Channel, RankMask, 0);
      if ((1 << Channel) & ChannelMask) {
        MrcCall->MrcSetMemDword (&ControllerOut->Channel[Channel].DataOffsetTrain[0], Outputs->SdramCount, 0);
      }
    }

    if (ChannelMask == 0) {
      continue;
    }

    for (MarginParam = RdT; MarginParam <= WrV; MarginParam++) {
      if (MarginParam == WrDqsT) {
        continue;
      }

      if (MarginParam == RdT) {
        Outputs->DQPat = RdRdTA;
      } else if (MarginParam == RdV) {
        Outputs->DQPat = BasicVA;
      }

      MaxMargin = ((MarginParam == RdV) || (MarginParam == WrV)) ? MAX_POSSIBLE_VREF : MAX_POSSIBLE_TIME;

      if ((Ddr4) && (MarginParam == WrV)) {
        MaxMargin = MAX_POSSIBLE_DDR4_WRITE_VREF;
      }

      Status = MrcGetBERMarginCh (
                 MrcData,
                 LastMargins,
                 ChannelMask,
                 (Ddr4 && (MarginParam == WrV)) ? RankMask : 0xFF,
                 (Ddr4 && (MarginParam == WrV)) ? RankMask : Rank,
                 MarginParam,
                 0,
                 1,
                 MaxMargin,
                 0,
                 BERStats
                 );
    }
  }

  // Print Retrain Limits
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRetrain Limits Per Side\nParams: RdT\tWrT\tRdV\tWrV\n\t");
  for (MarginParam = RdT; MarginParam <= WrV; MarginParam++) {
    if (MarginParam == WrDqsT) {
      continue;
    }
    RetrainMarginLimit = MrcGetUpmPwrLimit (MrcData, MarginParam, RetrainLimit);
    RetrainMarginLimitArr[MarginParam] = UDIVIDEROUND (RetrainMarginLimit, 10);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", RetrainMarginLimitArr[MarginParam]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");  // End of table

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Margins\nParams: RdT\tWrT\tRdV\tWrV\n\tLft Rgt Lft Rgt Low Hi  Low Hi");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nC%dR%d\t", Channel, Rank);
      for (MarginParam = RdT; MarginParam <= WrV; MarginParam++) {
        if (MarginParam == WrDqsT) {
          continue;
        }

        LastResultParam     = GetMarginResultType (MarginParam);
        RetrainMarginLimit = RetrainMarginLimitArr[MarginParam];
        MrcCall->MrcSetMemWord (MinEdgeMargin, MAX_EDGES, (UINT16) (~0));

        for (Edge = 0; Edge < MAX_EDGES; Edge++) {
          CurrentMargin       = (UINT16) LastMargins[LastResultParam][Rank][Channel][0][Edge] / 10;
          MinEdgeMargin[Edge] = MIN (MinEdgeMargin[Edge], CurrentMargin);
          if ((CurrentMargin <= RetrainMarginLimit)) {
            Status =  mrcRetrain;
            if ((MarginParam == RdT) || (MarginParam == RdV)) {
              RdWrMarginFail[0] = TRUE;
            } else if ((MarginParam == WrT) || (MarginParam == WrV)) {
              RdWrMarginFail[1] = TRUE;
            }
          }
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%2d  %2d\t", MinEdgeMargin[0], MinEdgeMargin[1]);
        if ((RdWrMarginFail[0] == TRUE) && (RdWrMarginFail[1] == TRUE)) {
          Rank    = MAX_RANK_IN_CHANNEL;
          Channel = MAX_CHANNEL;
          break;
        }
      }
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");  // End of table

  if (Status == mrcRetrain) {
    //
    // Loop is dependent on the order of MRC_MarginTypes.  If this changes, please ensure functionality
    // stays the same.
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*** Margin Limit Check Failed! ***\nNew Limits:\nParam\tUPM\tPWR");
    for (MarginParam = RdT; MarginParam <= WrV; MarginParam++) {
      if (((RdWrMarginFail[0] == FALSE) && ((MarginParam == RdT) || (MarginParam == RdV))) ||
          ((RdWrMarginFail[1] == FALSE) && ((MarginParam == WrT) || (MarginParam == WrV))) ||
          (MarginParam == WrDqsT)) {
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%s", MarginTypesString[MarginParam]);
      for (MarginLimitType = UpmLimit; MarginLimitType < RetrainLimit; MarginLimitType++) {
        RetrainMarginLimit = MrcUpdateUpmPwrLimits (MrcData, MarginParam, MarginLimitType, MRC_UPM_PWR_INC_VAL);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", RetrainMarginLimit);
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");  // End of table.
  }

  return Status;
}

/**
  Force OLTM (Open Loop Thermal Management) on Hynix DDR4 DRAMs before ww45'2015.
  Only applied for 2DPC.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus - if it succeed return mrcSuccess
**/
extern
MrcStatus
MrcForceOltm (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcDimmOut        *DimmOut;
  MrcInput          *Inputs;
  MrcDebug          *Debug;
  MrcSpd            *SpdIn;
  MrcStatus         Status;
  UINT16            DateCode;
  UINT8             Channel;
  UINT8             Dimm;
  BOOLEAN           UpdateNeeded;
  UINT32            Offset;
  SPD4_MANUFACTURING_DATA              *ManufactureData;
  MCSCHEDS_CR_SCHED_SECOND_CBIT_STRUCT SchedSecondCbit;
  MCMNTS_CR_MCMNTS_SPARE_STRUCT        McmntsSpare;
  MCHBAR_CH0_CR_DDR_MR_PARAMS_STRUCT   DdrMrParams;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Status        = mrcSuccess;

  UpdateNeeded = FALSE;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (((1 << Channel) & Outputs->ValidChBitMask) == 0) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    if (ChannelOut->DimmCount != 2) {
      continue;  // Not 2DPC
    }

    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      DimmOut = &ChannelOut->Dimm[Dimm];
      SpdIn = &Inputs->Controller[0].Channel[Channel].Dimm[Dimm].Spd.Data;
      ManufactureData = &SpdIn->Ddr4.ManufactureInfo;
      if ((ManufactureData->DramIdCode.Data == 0xAD80) ||
          (ManufactureData->ModuleId.IdCode.Data == 0xAD80)) { // Hynix
        DateCode = (ManufactureData->ModuleId.Date.Year << 8) | ManufactureData->ModuleId.Date.Week;
        if (DateCode < 0x1545) {  // Before ww45'2015
          UpdateNeeded = TRUE;
          break;
        }
      }
    }
  } // for Channel

  //
  // Force OLTM
  //
  if (UpdateNeeded) {
    if (Inputs->ForceOltmOrRefresh2x == 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Forcing OLTM...\n");
      Inputs->EnableOltm         = 1;
      Inputs->EnableCltm         = 0;
      Inputs->Refresh2X          = 2;
      Inputs->UserPowerWeightsEn = 0;
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Forcing 2x refresh...\n");
    }
    Inputs->DdrThermalSensor   = 0;

    SchedSecondCbit.Data = MrcReadCR (MrcData, MCHBAR_CH0_CR_SCHED_SECOND_CBIT_REG);
    SchedSecondCbit.Bits.dis_srx_mr4 = 1;
    MrcWriteCrMulticast (MrcData, MCSCHEDS_CR_SCHED_SECOND_CBIT_REG, SchedSecondCbit.Data);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      Offset = MCHBAR_CH0_CR_DDR_MR_PARAMS_REG +
        (MCHBAR_CH1_CR_DDR_MR_PARAMS_REG - MCHBAR_CH0_CR_DDR_MR_PARAMS_REG) * Channel;
      DdrMrParams.Data = MrcReadCR (MrcData, Offset);
      DdrMrParams.Bits.MR4_PERIOD         = 0;
      DdrMrParams.Bits.DDR4_TS_readout_en = 0;
      MrcWriteCR (MrcData, Offset, DdrMrParams.Data);

      if (Inputs->ForceOltmOrRefresh2x == 1) {
        Offset = MCHBAR_CH0_CR_MCMNTS_SPARE_REG +
          (MCHBAR_CH1_CR_MCMNTS_SPARE_REG - MCHBAR_CH0_CR_MCMNTS_SPARE_REG) * Channel;
        McmntsSpare.Data = MrcReadCR (MrcData, Offset);
        McmntsSpare.Bits.ForceX2Ref = 1;  // force 2X refresh
        MrcWriteCR (MrcData, Offset, McmntsSpare.Data);
      }
    }
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Force OLTM is not needed in the current DRAM configuration\n");
  }

  return Status;
}

/**
  Print DIMM ODT / Ron values per DIMM.
  Also print CPU ODT / Ron.

  @param[in] MrcData  - Include all MRC global data.

  @retval none
**/
extern
void
MrcPrintDimmOdtValues (
  IN MrcParameters *const MrcData
  )
{
#ifdef MRC_DEBUG_PRINT
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcDebug          *Debug;
  UINT8             Channel;
  UINT8             RankMask;
  UINT8             Rank;
  UINT8             Dimm;
  BOOLEAN           Ddr4;
  UINT16            OdtWrite;
  UINT16            OdtNom;
  UINT16            OdtPark;
  UINT16            DimmRon;
  UINT16            CpuOdt;
  UINT16            CpuRon;

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  //   DIMM summary:
  //
  //           Ron     OdtWr   OdtNom  OdtPark
  //   ---------------------------------------
  //   C0D0:   48      Hi-Z    48      80
  //   C0D1:   48      240     60      120
  //   ---------------------------------------
  //   C1D0:   48      48      34      34
  //   C1D1:   48      48      34      34
  //   ---------------------------------------
  //
  //   CPU Summary: Ron = 56, Read ODT = 109
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDIMM summary:\n\tRon\tOdtWr\tOdtNom\t%s\n", Ddr4 ? "OdtPark" : "");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "---------------------------------------\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    if (!ChannelOut->ValidRankBitMask) {
      continue;
    }
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      RankMask = DIMM_TO_RANK_MASK (Dimm);
      Rank = Dimm * 2;
      if ((RankMask & ChannelOut->ValidRankBitMask) == 0) {
        continue;
      }
      OdtWrite = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtWr,   FALSE, 0);
      OdtNom   = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtNom,  FALSE, 0);
      OdtPark  = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtPark, FALSE, 0);
      DimmRon  = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmRon,     FALSE, 0);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dD%d:\t%d\t", Channel, Dimm, DimmRon);
      if ((OdtWrite == 0xFFFF) || (OdtWrite == 0)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (OdtWrite == 0xFFFF) ? "Hi-Z\t" : "Off\t");
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", OdtWrite);
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (OdtNom == 0xFFFF) ? "Hi-Z\t" : "%d\t", OdtNom);
      if (Ddr4) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (OdtPark == 0xFFFF) ? "Hi-Z\n" : "%d\n", OdtPark);
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
      }
    } // for Dimm
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "---------------------------------------\n");
  } // for Channel

  // Override digital offset to zero, after Comp Optimization the global value reflects the average across all bytes.
  CpuRon = CalcCpuImpedance (MrcData, Channel, 0, 0, OptWrDS,  TRUE, 0, FALSE, 0, 0);
  CpuOdt = CalcCpuImpedance (MrcData, Channel, 0, 0, OptRdOdt, TRUE, 0, FALSE, 0, 0);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCPU Summary: Ron = %d, Read ODT = %d\n\n", CpuRon, CpuOdt);

#endif
}

/**
  This function wrap DimmODTTraining routine.
  It will enable to control ch/ranks for this training and additional options.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus - if it succeed return mrcSuccess
**/
extern
MrcStatus
MrcDimmODTTraining (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcInput          *Inputs;
  MrcDebug          *Debug;
  MrcStatus         Status;
  MrcDdrType        DdrType;
  UINT8             Channel;
  UINT8             ChMask;
  UINT8             RankMask;
  UINT8             RankMaskRttPark1;
  UINT8             Dimm;
  BOOLEAN           DisSubOpt;
  BOOLEAN           Lpddr;
  BOOLEAN           Ddr4;
  BOOLEAN           Ddr3;
  BOOLEAN           AnyChannel2DPC;
  UINT8             DimmParamList[4];
  UINT8             DimmParamSize;
  BOOLEAN           AllChannels1R1R;
  BOOLEAN           AllChannels1Dpc1R;//FALSE= 1DPC2R, TRUE= 1DPC1R

  Outputs       = &MrcData->Outputs;
  Inputs        = &MrcData->Inputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];

  ChMask    = Outputs->ValidChBitMask;
  DdrType   = Outputs->DdrType;
  Lpddr     = (DdrType == MRC_DDR_TYPE_LPDDR3);
  Ddr3      = (DdrType == MRC_DDR_TYPE_DDR3);
  Ddr4      = (DdrType == MRC_DDR_TYPE_DDR4);
  DisSubOpt = FALSE;
  Status    = mrcFail;
  AnyChannel2DPC      = FALSE;
  AllChannels1R1R     = TRUE;
  AllChannels1Dpc1R   = TRUE;
  RankMaskRttPark1 = 0xC; // Slot 1 only

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((MRC_BIT0 << Channel) & ChMask)) {
      continue;
    }

    ChannelOut = &ControllerOut->Channel[Channel];
    AllChannels1Dpc1R &= ((ChannelOut->ValidRankBitMask == 0x1) || (ChannelOut->ValidRankBitMask == 0x4));
    // optional disable sub optimizations for low ROI and runtime
    // assuming we have already good enough setting
    AllChannels1R1R   &= (ChannelOut->ValidRankBitMask == 0x5); // 2DPC 1R on Slot 0 and 1R on Slot 1
    AnyChannel2DPC    |= (ChannelOut->DimmCount == 2);
  }
  DisSubOpt = AnyChannel2DPC;

  if (Inputs->PowerTrainingMode == MrcTmMargin) {
    DisSubOpt = TRUE;
  }

  // To optimize park we need to run per channel.
  if (Ddr4 && AnyChannel2DPC && 0) { // disabled for now
    DimmParamList[0] = OptDimmOdtPark;
    DimmParamSize    = 1;
    RankMask         = 0xF;
    Status = DimmODTTraining (MrcData, ChMask, RankMask, DisSubOpt, DimmParamList, DimmParamSize);
    if (Status != mrcSuccess) {
      return Status;
    }
  }
  if (Ddr3) {
    if (!AnyChannel2DPC) {
      DimmParamList[0] = OptDimmOdtWr;
      DimmParamSize    = 1;
    } else {
      if (Inputs->PowerTrainingMode == MrcTmPower) {
        DimmParamList[0] = OptDimmOdtNomNT;
        DimmParamList[1] = OptDimmOdtWr;
        DimmParamSize    = 2;
      } else { // margin training
        DimmParamList[0] = OptDimmOdtComb;
        DimmParamSize    = 1;
      }
    }
  } else if (Ddr4) {
    if (!AnyChannel2DPC) {//1DPC.- 1R Slot0/1, 2R Slot 0/1
      if (Inputs->PowerTrainingMode == MrcTmPower) { // Power Training 1DPC case
        DimmParamList[0] = OptDimmOdtWr;
        DimmParamSize    = 1;
      } else { // margin training
        if (AllChannels1Dpc1R) {            // Margin Training 1DPC case
          DimmParamList[0] = OptDimmOdtWr;
          DimmParamSize = 1;
        } else { //Is1Dpc2R
          DimmParamList[0] = OptDimmOdtComb;
          DimmParamSize = 1;
        }
      }
    } else {// 2DPC
      if (Inputs->PowerTrainingMode == MrcTmPower) {
        DimmParamList[0] = OptDimmOdtNomNT;
        DimmParamList[1] = OptDimmOdtWr;
        DimmParamSize    = 2;
      } else { // margin training
        if (AllChannels1R1R) {
          DimmParamList[0] = OptDimmOdtComb_1R1R;
          DimmParamSize    = 1;
        } else { // 1R-2R, 2R-1R, 2R-2R
          DimmParamList[0] = OptDimmOdtComb;
          DimmParamSize    = 1;
        }
      }
    }
  } else { // LPDDR3
    DimmParamList[0] = OptDimmOdtWr;
    DimmParamSize    = 1;
  }

  DimmParamSize = MIN (ARRAY_COUNT (DimmParamList), DimmParamSize);

  for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm ++) {
    RankMask = DIMM_TO_RANK_MASK (Dimm);
    if ((RankMask & Outputs->ValidRankMask) == 0) {
      continue;
    }

    Status = DimmODTTraining (MrcData, ChMask, RankMask, DisSubOpt, DimmParamList, DimmParamSize);
    if (Status != mrcSuccess) {
      return Status;
    }
  }

  // Train RttPark of Slot 1
  if ((Ddr4) && (AnyChannel2DPC) && !(AllChannels1R1R)) {
    DimmParamList[0] = OptDimmOdtParkSlot1;
    DimmParamSize = 1;
    Status = DimmODTTraining (MrcData, ChMask, (RankMaskRttPark1 & Outputs->ValidRankMask), DisSubOpt, DimmParamList, DimmParamSize);
  }
  // Print out the end results of the training step in Table Format
  MrcPrintDimmOdtValues (MrcData);

  return Status;
}

/**
  This function implements DIMM ODT training.
  Adjust DIMM RTT_NOM/RTT_WR value to maximize read/write voltage/timing

  RdOdtPriority Needs to be an input parameter
  option to prioritize the ReadODT setting and attempt to optimize that value first,
  reducing CPU TDP power (as opposed to system power for the DRAM).
  For this case, the base value for ReadODT is changed at the compensation block
  by looking at the following values:
     RdOdt Global: (50, 64, 84, 110)

  In the case of 2 dpc, the flow will first optimizing RttNom, while keeping RttWr fixed
  at 60 Ohms (60 Ohms usually gives the best results).  It will then try to reduce RttWr
  to 120 Ohms if possible.

  In the case of 1 dpc, only RttNom is used and only a single pass is required.
  However, it is important to note that the two channels are completely independent
  and can have different numbers of dimms populated.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] ChMask   - channels to optimize
  @param[in] RankMask - rank to optimize
  @param[in] skipSubOpt - skip sub optimization (Ron, Odt ect.)
  @param[in] *DimmParamList - list of dimm parameters to optimize
  @param[in] DimmParamSize - parametes list size
  @retval MrcStatus   - if it succeed return mrcSuccess
**/
MrcStatus
DimmODTTraining (
  IN MrcParameters *const MrcData,
  IN UINT8                ChMask,
  IN UINT8                RankMask,
  IN BOOLEAN              skipSubOpt,
  IN UINT8                *DimmParamList,
  IN UINT8                DimmParamSize
  )
{
  const MRC_FUNCTION *MrcCall;
  MrcDebug          *Debug;
  const MrcInput    *Inputs;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcIntOutput      *IntOutput;
  MrcIntControllerOut *IntControllerOut;
  MrcStatus         Status;
  MrcDdrType        DdrType;
  MrcDebugMsgLevel  LocalDebugLevel;
  MRC_MARGIN_LIMIT_TYPE LimitType;
  UINT8             Channel;
  UINT8             LocalRanks[MAX_CHANNEL];
  UINT8             IntRankMask;
  UINT8             DimmParam;
  UINT8             DimmIdx;
  UINT8             DimmOdtOff;
  UINT8             Test;
  UINT8             *TestList = NULL;
  UINT8             TestListSize = 0;
  BOOLEAN           any2DPC;
  BOOLEAN           any1DPC;
  BOOLEAN           Lpddr;
  BOOLEAN           Ddr4;
  BOOLEAN           Ddr3;
  UINT8             TestListWr[]  = {OptTxEqWrDS};//OptSComp
  UINT8             TestListRdWr[] = {OptRdOdt, OptTxEqWrDS};
  UINT8             Scale4Test[] = { 1, 1, 1, 1, 0 }; // must specify scale=0 to unpopulated slots !!
  UINT8             Scale2Test[] = { 1, 1, 0, 0, 0 }; // must specify scale=0 to unpopulated slots !!
  UINT8             *Scale = Scale2Test;
  UINT16            PwrLimits[MAX_TRADEOFF_TYPES];
  DimmOptPoint      DimmOptPoints[MAX_DIMM_OPT_OFF];
  UINT8             DimmOptPointIdx;
  UINT16            Points2calc[MAX_TRADEOFF_TYPES][MAX_DIMM_OPT_OFF];
  UINT8             ArrayLength;
  UINT8             DimmParamIdx;
  OptResultsPerByte BestOff;
  UINT16            Margin;
  UINT8             ChNotDoneMask;
  UINT8             ChBit;
  UINT8             SetRttRanksMask; // To which ranks the RTT settings will be applied
  // @todo - in DDR 4 1DPC to make Rtt nom effect only on write the OdtMatrix reg should be program accordingly
  UINT8             OdtWrDDR3[]   = {0, 2, 1};            //  off, 120, 60
  UINT8             OdtNomDDR3[]  = {0, 2, 1, 3, 5, 4};   //  off, 120, 60
  UINT8             OdtWrLPDDR3[] = {0, 3, 2};            //  off, 240, 120
  UINT8             OdtWrDDR4[]   = {2, 1, 4};         //  240, 120, 80
  UINT8             OdtNomParkDDR4[]  = {0, 4, 2, 6, 1, 5, 3, 7};  //  off, 240, 120, 80, 60, 48, 40, 34
  UINT8             *OdtWrPtr;
  UINT8             *OdtNomPtr;
  UINT8             *OdtParkPtr;
  UINT8             OdtWrSize;
  UINT8             OdtNomSize;
  UINT8             OdtParkSize;
  UINT8             OdtSetSize[RttMaxType];
  UINT8             *OdtSetPtr[RttMaxType];
  UINT8             RttTypeList[RttMaxType];
  UINT8             RttTypeSize;
  UINT8             RttLoop;
  UINT8             RttCnt;
  UINT8             RttSetSize;
  UINT8             DimmOptTestLength[MAX_CHANNEL];
  UINT8             UPMOptimize[MAX_TRADEOFF_TYPES];
  UINT32            Offset;
  BOOLEAN           LpddrOdtEnabled;
  BOOLEAN           PowerTrainingMode;
  MCSCHEDS_CR_SCHED_CBIT_STRUCT         SchedCbit;

  Inputs              = &MrcData->Inputs;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  ControllerOut       = &Outputs->Controller[0];
  IntOutput           = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut    = (MrcIntControllerOut *) &IntOutput->Controller[0];
  Status              = mrcSuccess;
  LocalDebugLevel     = MSG_LEVEL_NEVER;
  ArrayLength         = (UINT8) (sizeof (Points2calc) / sizeof (Points2calc[0][0]) / MAX_TRADEOFF_TYPES);
  MrcCall             = Inputs->Call.Func;
  DdrType = Outputs->DdrType;

  Lpddr = (DdrType == MRC_DDR_TYPE_LPDDR3);
  LpddrOdtEnabled = (Lpddr && Outputs->LpddrDramOdt);
  Ddr3  = (DdrType == MRC_DDR_TYPE_DDR3);
  Ddr4  = (DdrType == MRC_DDR_TYPE_DDR4);
  PowerTrainingMode = (MrcTmPower == Inputs->PowerTrainingMode);

  MrcCall->MrcSetMem ((UINT8 *) &BestOff, sizeof (BestOff), 0);
  MrcCall->MrcSetMem ((UINT8 *) Points2calc, sizeof (Points2calc), 0);
  MrcCall->MrcSetMem ((UINT8 *) LocalRanks, sizeof (LocalRanks), 0);
  MrcCall->MrcSetMem ((UINT8 *) UPMOptimize, sizeof (UPMOptimize), 0);
  MrcCall->MrcSetMemWord (PwrLimits, MAX_TRADEOFF_TYPES, 0);

  ChMask    &= Outputs->ValidChBitMask;
  RankMask  &= Outputs->ValidRankMask;

  any2DPC = FALSE;
  any1DPC = FALSE;

  OdtParkPtr = NULL;
  OdtParkSize = 0;

  //
  // ODT matrix already init from McConfig for DDR4
  //
  // Read flow:
  // Keep RttWr un-touched from McConfig, go by the OdtMatrix for Rtt nom/park from max power save to min
  //
  //
  // Write flow:
  // Keep RttNom/park un-touched, go by the OdtMatrix for Rtt Wr from max power save to min.
  // If 1DPC, we can have combos of wr/nom/park to get other Rtt values (wont effect read).
  // option 0: Keep RttWr the same for both DIMMs (ie: train per Ch for both RttWr & WrDrv) - SKL
  // option 1: Allow different RttWr for each DIMM and break WrDrv out of this optimization (ie: do it later).- HSW
  //
  // For DDR4 per Dimm/Rank Optimization, we run this function with RankBitMask param
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChBit = 1 << Channel;
    if (!(ChBit & ChMask)) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    //
    // Setup Dimm Masks for NormalizePowerToMargins so we don't access a Dimm that isn't present.
    //
    if (ChannelOut->DimmCount == 2) {
      any2DPC |= 1;
    } else {
      any1DPC |= 1;
    }
    LocalRanks[Channel] = RankMask & ChannelOut->ValidRankBitMask;
    if (LocalRanks[Channel] == 0) {
      // Clear channel not populated with input ranks
      ChMask &= (~ChBit);
    }
  }

  if (Ddr3) {
    OdtWrPtr    = OdtWrDDR3;
    OdtWrSize   = ARRAY_COUNT (OdtWrDDR3);
    OdtNomPtr   = OdtNomDDR3;
    OdtNomSize  = ARRAY_COUNT (OdtNomDDR3);

  } else if (Ddr4) {
    OdtNomPtr   = OdtNomParkDDR4;
    OdtNomSize  = ARRAY_COUNT (OdtNomParkDDR4);
    OdtParkPtr  = OdtNomParkDDR4;
    OdtParkSize = ARRAY_COUNT (OdtNomParkDDR4);
    OdtWrPtr    = OdtWrDDR4;
    OdtWrSize   = ARRAY_COUNT (OdtWrDDR4);
  } else { // LPDDR3
    OdtWrPtr    = OdtWrLPDDR3;
    OdtWrSize   = (LpddrOdtEnabled) ? ARRAY_COUNT (OdtWrLPDDR3) : 1;
    OdtNomPtr   = NULL;
    OdtNomSize  = 0;
  }

  for (DimmParamIdx = 0; DimmParamIdx < DimmParamSize; DimmParamIdx++) {
    // init the results struct
    MrcCall->MrcSetMem ((UINT8 *) DimmOptPoints, ARRAY_COUNT (DimmOptPoints), 0);
    DimmParam = DimmParamList[DimmParamIdx];

    switch (DimmParam) {
      case OptDimmOdtNom:
      case OptDimmOdtNomNT:
        // Assuming we run Nom sweep only when 2DPC
        OdtSetPtr[0]   = OdtNomPtr;
        OdtSetSize[0]  = RttSetSize = OdtNomSize;
        RttTypeList[0] = DimmParam;
        RttTypeSize    = 1;
        TestList       = TestListRdWr;
        TestListSize   = ARRAY_COUNT (TestListRdWr);
        Scale          = Scale4Test;
        SetRttRanksMask = RankMask;
        break;

      case OptDimmOdtWr:
        OdtSetPtr[0]   = OdtWrPtr;
        OdtSetSize[0]  = RttSetSize = OdtWrSize;
        RttTypeList[0] = DimmParam;
        RttTypeSize    = 1;
        TestList       = TestListWr;
        TestListSize   = ARRAY_COUNT (TestListWr);
        Scale          = Scale2Test;
        SetRttRanksMask = RankMask;
        break;

      case OptDimmOdtPark:
      case OptDimmOdtParkNT:
        OdtSetPtr[0]   = OdtParkPtr;
        OdtSetSize[0]  = RttSetSize = OdtParkSize;
        RttTypeList[0] = DimmParam;
        RttTypeSize    = 1;
        TestList       = TestListRdWr;
        TestListSize   = ARRAY_COUNT (TestListRdWr);
        Scale          = Scale4Test;
        SetRttRanksMask = RankMask;
        break;

      case OptDimmOdtComb_1R1R:
        RttTypeList[0] = OptDimmOdtWr;
        OdtSetPtr[0]   = OdtWrPtr;
        OdtSetSize[0]  = OdtWrSize;  // Search all values

        RttTypeList[1] = OptDimmOdtNomNT;
        OdtSetPtr[1]   = OdtNomPtr; // Search all values
        OdtSetSize[1]  = OdtNomSize;

        RttTypeSize = 2;

        RttSetSize = 1;
        for (RttLoop = 0; RttLoop < RttTypeSize; RttLoop++) {
          RttSetSize *= OdtSetSize[RttLoop];
        }
        TestList     = TestListRdWr;
        TestListSize = ARRAY_COUNT (TestListRdWr);
        Scale = Scale4Test;
        SetRttRanksMask = RankMask;
        break;

      case OptDimmOdtParkSlot1:
        // Train RttPark of Slot1, consider both slots while marginning
        RttTypeList[0] = OptDimmOdtPark;
        OdtSetPtr[0] = OdtParkPtr; // Search all values
        OdtSetSize[0] = RttSetSize = OdtParkSize;
        RttTypeSize = 1;
        TestList = TestListRdWr;
        TestListSize = ARRAY_COUNT(TestListRdWr);
        Scale = Scale4Test;
        SetRttRanksMask = DIMM_TO_RANK_MASK(dDIMM1);
        break;

      case OptDimmOdtComb:
        // Set new limits for special cases
        SetRttRanksMask = RankMask;
        if (Ddr4 && !any2DPC) {
          // Optimization performed only for DDR4 1DPC
          // Wr : 80, 120, 240
          // Park/Read :  off, 240, 120, 80, 60, 48, 40, 34

          RttTypeList[0]  = OptDimmOdtWr;
          OdtSetPtr[0]    = OdtWrPtr;
          OdtSetSize[0]   = OdtWrSize;  // Search all values

          RttTypeList[1]  = OptDimmOdtPark;
          OdtSetPtr[1]    = OdtParkPtr; // Search all values
          OdtSetSize[1]   = OdtParkSize;

          RttTypeSize     = 2;
        } else if ((RankMask & 0x3) && Ddr4) {
          // Slot 0 (we optimize also park assuming this is our w/c slot)
          // Wr : 120, 240
          // Park/Read :  off, 240, 120, 80, 60, 48, 40, 34
          RttTypeList[0]  = OptDimmOdtNomNT;
          OdtSetPtr[0]    = OdtNomPtr + 3; // start from 80
          OdtSetSize[0]   = MIN (5, OdtNomSize);

          RttTypeList[1]  = OptDimmOdtWr;
          OdtSetPtr[1]    = OdtWrPtr;
          OdtSetSize[1]   = MIN (2, OdtWrSize);  // 120, 240

          RttTypeList[2]  = OptDimmOdtPark;
          OdtSetPtr[2]    = OdtParkPtr + 3; // start from 80
          OdtSetSize[2]   = MIN (5, OdtParkSize);
          RttTypeSize     = 3;
          if (!(PowerTrainingMode) && Ddr4 && any2DPC) {
            UPMOptimize[LastRxT] = 1;
            UPMOptimize[LastTxT] = 1;
          }
        } else {
          // DDR4 slot 1 or DDR3L
          RttTypeList[0]  = OptDimmOdtNomNT;
          OdtSetPtr[0]    = OdtNomPtr;
          OdtSetSize[0]   = OdtNomSize;

          RttTypeList[1]  = OptDimmOdtWr;
          OdtSetPtr[1]    = OdtWrPtr;
          OdtSetSize[1]   = OdtWrSize;
          RttTypeSize     = 2;
          if (!(PowerTrainingMode) && Ddr3) {
            OdtSetPtr[1]++;  // Avoid WrOdt = Off option when margin training, only use 120 and 60 Ohms
            OdtSetSize[1]--;
          }
        }
        RttSetSize   = 1;
        for (RttLoop = 0; RttLoop < RttTypeSize; RttLoop++) {
          RttSetSize *= OdtSetSize[RttLoop];
        }
        TestList      = TestListRdWr;
        TestListSize  = ARRAY_COUNT (TestListRdWr);
        Scale = Scale4Test;
        break;

      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DimmOdt : Unknown value for Optparam : %d DimmParamIdx : %d\n", DimmParam, DimmParamIdx);
        return mrcFail;
        break;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Training (ChannelMask = 0x%X, RankMask = 0x%X) SetSize =  %d\n", TOptParamOffsetString[DimmParam], ChMask, RankMask, RttSetSize);

    //
    // The loop can be done per rank/dimm if needed using rank mask
    // In 1DPC we use same odt per "dimm"(==ch), assuming no much difference. (true for DDR4?)
    //
    MrcCall->MrcSetMem (DimmOptTestLength, MAX_CHANNEL, 0);
    ChNotDoneMask   = ChMask;
    for (DimmOptPointIdx = 0; ((DimmOptPointIdx < RttSetSize) && (ChNotDoneMask != 0)); DimmOptPointIdx++) {
      // Propagate Odt changes per ch
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if ((1 << Channel) & ChNotDoneMask) {
          ChannelOut = &ControllerOut->Channel[Channel];
          DimmOptTestLength[Channel] = DimmOptPointIdx + 1;
          // Copy the odt values to DimmOdtSet array for all
          for (DimmIdx = 0; DimmIdx < MAX_DIMMS_IN_CHANNEL; DimmIdx++) {
            // Set Rtt only to Ranks that are populated and in SetRttRanksMask
            if (DIMM_TO_RANK_MASK (DimmIdx) & ChannelOut->ValidRankBitMask & SetRttRanksMask) {
              for (RttLoop = 0; RttLoop < RttTypeSize; RttLoop++) {
                //DimmOptPointIdx is the index need to advance each RttType
                if ((DimmParam == OptDimmOdtComb) || (DimmParam == OptDimmOdtComb_1R1R)) {
                  if (RttLoop == 0) {
                    RttCnt = DimmOptPointIdx % OdtSetSize[RttLoop];
                  } else if (RttLoop == 1) {
                    RttCnt = (DimmOptPointIdx / OdtSetSize[0]) % OdtSetSize[RttLoop];
                  } else {
                    RttCnt = (DimmOptPointIdx / (OdtSetSize[0] * OdtSetSize[1])) % OdtSetSize[RttLoop];
                  }
                } else {
                  RttCnt = DimmOptPointIdx;
                }
                DimmOptPoints[DimmOptPointIdx].ODTSet.DimmOdt[Channel][DimmIdx].Rtt[RttLoop] = OdtSetPtr[RttLoop][RttCnt];
                DimmOptPoints[DimmOptPointIdx].ODTSet.DimmOdt[Channel][DimmIdx].RttType[RttLoop] = RttTypeList[RttLoop];
                MRC_DEBUG_MSG (
                  Debug,
                  LocalDebugLevel,
                  "--> Ch%d Dimm%d set Odt %s to %d\n",
                  Channel,
                  DimmIdx,
                  TOptParamOffsetString[RttTypeList[RttLoop]],
                  CalcDimmImpedance (MrcData, Channel, 2 * DimmIdx, RttTypeList[RttLoop], TRUE, OdtSetPtr[RttLoop][RttCnt])
                  );
              }
              UpdateOptPointValues (MrcData, Channel, DIMM_TO_RANK_MASK (DimmIdx), &DimmOptPoints[DimmOptPointIdx], RttTypeSize, TRUE, FALSE, TRUE, TRUE);
            }
          }
        }
      } // ch loop
      if (Ddr4) {
        MrcSetDefaultRxVrefDdr4 (MrcData, FALSE, FALSE);
        DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, WrV, 0, 10, FALSE, FALSE);
      } else if (LpddrOdtEnabled) {
        MrcWriteVoltageCentering (MrcData);
      }

      Status = TrainDimmOdtSetting (
                 MrcData,
                 &DimmOptPoints[DimmOptPointIdx],
                 Outputs->ValidChBitMask,     // We still run both channel (if selected) although one can already have its ODT selected
                 RankMask,
                 TestList,
                 TestListSize,
                 Inputs->PowerTrainingMode,
                 skipSubOpt,
                 (!Lpddr),
                 0, // Center Reads Bool
                 0  // Center Writes Bool
                 );
      if (Status != mrcSuccess) {
        return Status;
      }

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!((0x1 << Channel) & ChNotDoneMask)) {
          continue;
        }
        ChNotDoneMask &= ~(1 << Channel); // Mark Ch as Done
        for (Test = 0; Test < (DimmOptPoints[DimmOptPointIdx].NumTests); Test++) {
          Margin = DimmOptPoints[DimmOptPointIdx].Points2Trade[Test][Channel];
          MRC_DEBUG_MSG (Debug, LocalDebugLevel, "Dimm Odt point Result Summary - CH%d Test %s\t EH/EW %d\n",
            Channel, MarginTypesString[DimmOptPoints[DimmOptPointIdx].TestList[Test]], Margin);
          LimitType = (Inputs->PowerTrainingMode == MrcTmMargin) ? PowerLimit : UpmLimit;

          //
          // This channel didn't reach the required margin limit for Margin or Power Training (on Any Test).
          //
          if (Margin < MrcGetUpmPwrLimit (MrcData, DimmOptPoints[DimmOptPointIdx].TestList[Test], LimitType)) {
            MRC_DEBUG_MSG (Debug, LocalDebugLevel, "Channel: %d\tMargin Fail UPM: %d\n", Channel, Margin);
            ChNotDoneMask |= (1 << Channel);
            break;
          }
        }
      }
      MRC_DEBUG_MSG (Debug, LocalDebugLevel, "ChNotDoneMask: 0x%X\tDimmOptPointIdx: %u\n", ChNotDoneMask, DimmOptPointIdx);
#ifdef POWER_TRAINING_DEBUG
      // @todo:      CalcSysPower (MrcData, DimmOptPoints[DimmOptPointIdx].PowerCalc);
#endif
    }  // for DimmOptPointIdx

    //
    // Find the best point.
    //
    if (!(PowerTrainingMode)) {
      if (Ddr4) {
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Margin Training using LinearApproximationTradeOff function\n");
      } else {
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Margin Training using MarginTrainingLegacyTradeOff function\n");
      }
    }

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((0x1 << Channel) & ChMask)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      for (DimmOdtOff = 0; DimmOdtOff < DimmOptTestLength[Channel]; DimmOdtOff++) {
        //
        // copy point for the FindOptTradeOff routing
        //
        for (Test = 0; Test < (DimmOptPoints[DimmOdtOff].NumTests); Test++) {
          Points2calc[Test][DimmOdtOff] = DimmOptPoints[DimmOdtOff].Points2Trade[Test][Channel];
        }
      }
      //
      // Get appropriate UPM Limits based on test Margin Type.  Reusing DimmOdtOff variable as index.
      //
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "UpmLimits\n");
      for (DimmOdtOff = 0; DimmOdtOff < DimmOptPoints[0].NumTests; DimmOdtOff++) {
        PwrLimits[DimmOdtOff] = MrcGetUpmPwrLimit (MrcData, DimmOptPoints[0].TestList[DimmOdtOff], UpmLimit);
        MRC_DEBUG_MSG (
          Debug,
          LocalDebugLevel,
          "%s: %d\n",
          MarginTypesString[DimmOptPoints[0].TestList[DimmOdtOff]],
          PwrLimits[DimmOdtOff]
          );
      }
      FindOptimalTradeOff (
        MrcData,
        &BestOff,
        &Points2calc[0][0],
        ArrayLength,
        DimmOptTestLength[Channel], // number offset point to trade
        Scale,
        UPMOptimize,
        0, // EnSq
        1, // AvgN
        1, // IncEnds
        1, // ScaleM
        PwrLimits,
        (PowerTrainingMode) ? 0 : 100, // Select first point above UPM or 100% of MaxR.  (Assumes ordered low -> high power)
        0, // GuardBand
        TRUE //EnableLinearApproximationOptimizationMode
        );

      for (DimmIdx = 0; DimmIdx < MAX_DIMMS_IN_CHANNEL; DimmIdx++) {
        IntRankMask = DIMM_TO_RANK_MASK (DimmIdx);
        if (IntRankMask & ChannelOut->ValidRankBitMask & SetRttRanksMask) {
          UpdateOptPointValues (
            MrcData,
            Channel,
            IntRankMask,
            &DimmOptPoints[BestOff.Best],
            RttTypeSize,
            (DimmParam == RdOdt) ? FALSE : TRUE,
            FALSE,
            FALSE || skipSubOpt,
            TRUE
            );

          if (LpddrOdtEnabled && (BestOff.Best == 0)){
            // If ODT kept Hi-Z setting, disable odt pin
            MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Disabling ODT PIN on Ch%u Dimm%u\n", Channel, DimmIdx);
            Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_SCHED_CBIT_REG, MCHBAR_CH1_CR_SCHED_CBIT_REG, Channel);
            SchedCbit.Data = MrcReadCR(MrcData, Offset);
            SchedCbit.Bits.dis_odt = 1;
            MrcWriteCR(MrcData, Offset, SchedCbit.Data);
          }
        }
      }
#ifdef MRC_DEBUG_PRINT
      PrintODTResultTable (
        MrcData,
        &BestOff,
        DimmOptPoints,
        DimmOptTestLength[Channel],
        0, // mid point
        1, // include end points
        DimmParam,
        RttTypeSize,
        Channel,
        (ChannelOut->ValidRankBitMask & SetRttRanksMask),
        1, // Tline
        !skipSubOpt,
        Scale,
        0, // per nibble
        1  // PerCh
        );
#endif // MRC_DEBUG_PRINT
    } // end of channel loop

    if (Ddr4) {
      // set vref accordingly to odt's
      MrcSetDefaultRxVrefDdr4 (MrcData, FALSE, FALSE);
      DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, WrV, 0, 10, FALSE, FALSE);
      DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdV, 0, 10, FALSE, FALSE);
    } else if (LpddrOdtEnabled) {
      MrcWriteVoltageCentering (MrcData);
    }

    if ((DimmParam == OptDimmOdtNom) || (DimmParam == OptDimmOdtPark) || (DimmParam == OptDimmOdtParkNT)
         || (DimmParam == OptDimmOdtComb) || (DimmParam == OptDimmOdtParkSlot1)) {
      // Centering read
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Re-center Read Voltage\n");
      Status = ReadVoltageCentering2D (
                 MrcData,
                 Outputs->MarginResult,
                 Outputs->ValidChBitMask,
                 RdV,
                 0,
                 0,
                 OPT_PARAM_LOOP_COUNT,
                 0
                 );

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Re-center Read Timing\n");
      Status = DataTimeCentering2D (
                 MrcData,
                 Outputs->MarginResult, // prev. margin results
                 Outputs->ValidChBitMask,
                 RdT,
                 0, // EnPerBit,
                 0, // EnRxDutyCycle
                 0, // ResetPerBit
                 OPT_PARAM_LOOP_COUNT,
                 0  // En2D
                 );
    }

    if ((DimmParam == OptDimmOdtWr) || (DimmParam == OptDimmOdtNom) || (DimmParam == OptDimmOdtPark) || (DimmParam == OptDimmOdtParkNT)
        || (DimmParam == OptDimmOdtComb) || (DimmParam == OptDimmOdtParkSlot1)) {
      // Centering write
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Re-center Write Vref\n");
      Status = MrcWriteVoltageCentering2D (MrcData);

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Re-center Write Timing\n");
      Status = DataTimeCentering2D (
                 MrcData,
                 Outputs->MarginResult, // prev. margin results
                 Outputs->ValidChBitMask,
                 WrT,
                 0, // EnPerBit,
                 0, // EnRxDutyCycle
                 0, // ResetPerBit
                 OPT_PARAM_LOOP_COUNT,
                 0  // En2D
                 );
    }
  } // end Odt type  loop

  return Status;
}

/**
  This function implements Read Equalization training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcReadEQTraining (
  IN MrcParameters *const MrcData
  )
{
  UINT8               RankMask;
  static const UINT8  TestList[]  = { RdV, RdT };
  static const UINT8  Scale[]     = { 1, 2, 0, 0, 0 };
  static const UINT8  OptParam[]  = { OptRxEq };
  OptOffsetChByte     BestOff;
  INT8                Start;
  INT8                Stop;

  Start = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop  = OptParamLimitValue (MrcData, OptParam[0], 1);

  //
  // Function Call for RxEQ Training
  //
  for (RankMask = 1; RankMask < (0x1 << MAX_RANK_IN_CHANNEL); RankMask <<= 1) {
    if (RankMask & MrcData->Outputs.ValidRankMask) {
      TrainDDROptParam (
        MrcData,
        &BestOff,
        0x3,
        RankMask,
        OptParam,
        ARRAY_COUNT (OptParam),
        FullGrid,
        TestList,
        ARRAY_COUNT (TestList),
        Scale,
        NULL,
        &Start,  // Start
        &Stop,  // Stop
        OPT_PARAM_1D_LC,
        1,    // Repeats
        0,    // NoPrint
        0,    // SkipOptUpdate
        0,    // RdRd2Test
        0     // GuardBand
        );
    }
  }

  return mrcSuccess;
}

/**
  This function implements Write (Transmitter) Equalization and Drive Strength training.

  @param[in] MrcData        - Include all MRC global data.
  @param[in] EarlyCentering - Execute as early centering routine

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
WriteEqDsTraining (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              EarlyCentering
  )
{
  const MrcInput      *Inputs;
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcStatus           Status;
  static const UINT8  TestList[]  = { WrV, WrT };
  UINT8               Scale[]     = { 1, 2, 1, 0, 0 }; // Must specify scale = 0 to unpopulate slots!!
  static const UINT8  OptParam[]  = { OptTxEq, OptWrDS };
  OptOffsetChByte     BestOff;
  UINT8               LoopCount;
  INT8                Start[2];
  INT8                Stop[2];

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;

  Start[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop[0]  = OptParamLimitValue (MrcData, OptParam[0], 1);
  Start[1] = OptParamLimitValue (MrcData, OptParam[1], 0);
  Stop[1]  = OptParamLimitValue (MrcData, OptParam[1], 1);

  LoopCount = EarlyCentering ? 13 : OPT_PARAM_1D_LC + 1;

  if ((Inputs->PowerTrainingMode == MrcTmMargin) || (EarlyCentering)) {
    Scale[ARRAY_COUNT (TestList)] = 0;
  }

  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xF,
    OptParam,
    ARRAY_COUNT (OptParam),
    ChessOdd,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    Start,
    Stop,
    LoopCount,
    1,                    // Repeats
    0,                    // NoPrint
    0,                    // SkipOptUpdate
    0,                    // RdRd2Test
    0                     // GuardBand
    );

  if (EarlyCentering) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Write Vref\n");
    Status = MrcWriteVoltageCentering2D (MrcData);

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Write Timing\n");
    Status = DataTimeCentering2D (
      MrcData,
      Outputs->MarginResult, // prev. margin results
      Outputs->ValidChBitMask,
      WrT,
      0, // EnPerBit,
      0, // EnRxDutyCycle
      0, // ResetPerBit
      LoopCount,
      0  // En2D
      );
  }
  return Status;
}

/**
  This function implements Early Write (Transmitter) Drive Strength / Equalization training.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
extern
MrcStatus
MrcEarlyWrDsEqTraining (
  IN MrcParameters *const MrcData
  )
{
  MrcIntChannelOut  *IntChannelOut;
  MrcIntOutput      *MrcIntData;
  MrcOutput         *Outputs;
  MrcStatus         Status;
  UINT32            Offset;
  UINT8             Channel;
  BOOLEAN           Lpddr3;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT TcRdRd;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Outputs = &MrcData->Outputs;
  Lpddr3  = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      // Increase the same rank RDRD turnaround to avoid delayed data overlap.
      IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
      TcRdRd.Data = IntChannelOut->MchbarTcRdRd.Data;
      TcRdRd.Bits.tRDRD_sg += 8;
      TcRdRd.Bits.tRDRD_dg += 8;
      Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_TC_RDRD_REG, MCHBAR_CH1_CR_TC_RDRD_REG, Channel);
      MrcWriteCR (MrcData, Offset, TcRdRd.Data);
    }
  }

  Status = WriteEqDsTraining (MrcData, TRUE);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      // Restore the same rank RDRD turnaround
      IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
      Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_TC_RDRD_REG, MCHBAR_CH1_CR_TC_RDRD_REG, Channel);
      MrcWriteCR (MrcData, Offset, IntChannelOut->MchbarTcRdRd.Data);
    }
  }

  return Status;
}

/**
  This function implements Write (Transmitter) Equalization and Drive Strength training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcWriteEqDsTraining (
  IN MrcParameters *const MrcData
  )
{
  return WriteEqDsTraining (MrcData, FALSE);
}

/**
  This function implements Write (Transmitter) Drive Strength Up / Down training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcWriteDsUpDnTraining (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  static const UINT8  TestList[]  = { WrV, WrT };
  UINT8               Scale[]     = { 1, 1, 0, 0, 0 }; // Must specify scale = 0 to unpopulated slots!!
  static const UINT8  OptParam[]  = { OptWrDSUpCoarse, OptWrDSDnCoarse };
  OptOffsetChByte     BestOff;
  UINT8               UPMOptimize[MAX_TRADEOFF_TYPES] = {0, 1};

  INT8                Start[2];
  INT8                Stop[2];

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  Start[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop[0]  = OptParamLimitValue (MrcData, OptParam[0], 1);
  Start[1] = OptParamLimitValue (MrcData, OptParam[1], 0);
  Stop[1]  = OptParamLimitValue (MrcData, OptParam[1], 1);

  if (Inputs->PowerTrainingMode == MrcTmMargin) {
    Scale[ARRAY_COUNT (TestList) ] = 0;
  }

  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xF,
    OptParam,
    ARRAY_COUNT (OptParam),
    ChessOdd,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    UPMOptimize,
    Start,
    Stop,
    OPT_PARAM_1D_LC + 1,  // @todo adjust lc by rank population
    1,                    // Repeats
    0,                    // NoPrint
    0,                    // SkipOptUpdate
    0,                    // RdRd2Test
    0                     // GuardBand
    );

  // Centering write
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Re-center Write Vref\n");
  MrcWriteVoltageCentering2D (MrcData);

  return mrcSuccess;
}

/**
  This function implements Read Amplifier Power training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it succeeds return mrcSuccess
**/
MrcStatus
MrcReadAmplifierPower (
  IN MrcParameters *const MrcData
  )
{
  MrcStatus           Status;
  MrcOutput           *Outputs;
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  static const UINT8  TestList[]  = { RdV, RdT, RcvEnaX };
  UINT8               Scale[]     = { 1, 2, 1, 1, 0 }; // Must specify scale = 0 to unpopulated slots!!
  static const UINT8  OptParam[]  = { OptRxBias, OptRxCb };
  OptOffsetChByte     BestOff;
  UINT8               RecenterLC;
  INT8                Start[2];
  INT8                Stop[2];
  INT8                GuardBand;

  RecenterLC  = 15;
  Status      = mrcSuccess;
  Outputs     = &MrcData->Outputs;
  Inputs      = &MrcData->Inputs;
  Debug       = &Outputs->Debug;

  Start[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop[0]  = OptParamLimitValue (MrcData, OptParam[0], 1);
  Start[1] = OptParamLimitValue (MrcData, OptParam[1], 0);
  Stop[1]  = OptParamLimitValue (MrcData, OptParam[1], 1);

  if (Inputs->PowerTrainingMode == MrcTmMargin) {
    Scale[ARRAY_COUNT (TestList) ] = 0;
  }

  GuardBand = 1;

  //
  // Function Call for RxBias
  //
  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xF,
    OptParam,
    ARRAY_COUNT (OptParam),
    FullGrid,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    Start,            // Start
    Stop,             // Stop
    OPT_PARAM_1D_LC,
    1,                // Repeats
    0,                // NoPrint
    0,                // SkipOdtUpdate
    0,                // RdRd2Test
    GuardBand
    );

  // @todo : we might want to do here Sense amp training instead.
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Read Timing\n");
  Status = DataTimeCentering2D (
             MrcData,
             Outputs->MarginResult, // prev. margin results
             0x3,
             RdT,
             0, // EnPerBit,
             0, // EnRxDutyCycle
             0, // ResetPerBit
             RecenterLC,
             0  // En2D
             );

  return Status;
}

/**
  This function implements Dimm Ron training.
  Should be called on DDR4 and LPDDR3 only.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeeds return mrcSuccess
**/
MrcStatus
MrcDimmRonTraining (
  IN MrcParameters *const MrcData
  )
{
  OptOffsetChByte     BestOff;
  static const UINT8  TestList[]  = { RdV, RdT };
  UINT8               Scale[]     = { 1, 2, 1, 0, 0 }; // Must specify scale = 0 to unpopulate slots!!
  static const UINT8  OptParam[]  = { OptDimmRon };
  INT8                Start;
  INT8                Stop;

  if (MrcData->Inputs.PowerTrainingMode == MrcTmMargin) {
    Scale[ARRAY_COUNT (TestList) ] = 0;
  }

  Start = 0;
  Stop = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_DDR4) ? 1 : 2;
  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,         // Channels
    0xF,         // Ranks
    OptParam,
    ARRAY_COUNT (OptParam),
    Reversed1D,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    &Start,          // Start
    &Stop,           // Stop
    OPT_PARAM_1D_LC, // Loopcount
    1,               // Repeats
    0,               // NoPrint
    0,               // SkipOdtUpdate
    0,               // RdRd2Test
    0                // GuardBand
    );

  return mrcSuccess;
}

/**
  This function implements the general training algorithm for DDR and IO parameters
  that impact margin and power.

  This function can train for power or for margin, and the function determines the mode as follows:
    PowerTraining: (NumTests <= MAX_TRADEOFF_TYPES) && (Scale[NumTests] != 0)
    else MarginTraining.

  The Parameters that are supported:
    [0: WrDS, 1: RdODT, 2: SComp, 3: TComp, 3: TxEq, 4: RxEq, 5: RxBias, 6: DimmOdt, 7: DimmOdtWr]

  @param[in,out] MrcData         - Include all MRC global data.
  @param[in,out] BestOff         - Structure containg the best offest and margins for th Opt param.
  @param[in]     ChannelMask     - Channels to train
  @param[in]     RankMask        - Condenses down the results from multiple ranks
  @param[in]     OptParam        - Defines the OptParam Offsets.
  @param[in]     TestList        - List of margin params that will be tested (up to 4)
  @param[in]     NumTests        - The length of TestList
  @param[in]     Scale           - List of the relative importance between the 4 tests
  @param[in]     UPMOptimize     - Optimize in FindOptimalTradeOff only for UPM limit for selected params, so if they pass UPM they do not affect the score.
  @param[in]     Start           - Start point of sweeping the Comp values
  @param[in]     Stop            - Stop point of sweeping the Comp values
  @param[in]     LoopCount       - The number of loops to run in IO tests.
  @param[in]     Repeats         - Number of times to repeat the test to average out any noise
  @param[in]     NoPrint         - Switch to disable printing.
  @param[in]     SkipOptUpdate   - Switch to train but not update Opt settings.
  @param[in]     RdRd2Test       - Switch to run with different TA times: possible values are [0, RdRdTA, RdRdTA_All]
  @param[in]     GuardBand       - Signed offset to apply to the Opt param best value.

  @retval Nothing
**/
void
TrainDDROptParam (
  IN OUT MrcParameters *const MrcData,
  IN OUT OptOffsetChByte      *BestOff,
  IN     UINT8                ChannelMask,
  IN     UINT8                RankMask,
  IN     const UINT8          OptParam[],
  IN     UINT8                OptParamLen,
  IN     UINT8                GridMode,
  IN     const UINT8          *TestList,
  IN     UINT8                NumTests,
  IN     const UINT8          *Scale,
  IN     UINT8                UPMOptimize[MAX_TRADEOFF_TYPES],
  IN     INT8                 Start[],
  IN     INT8                 Stop[],
  IN     UINT8                LoopCount,
  IN     UINT8                Repeats,
  IN     BOOLEAN              NoPrint,
  IN     BOOLEAN              SkipOptUpdate,
  IN     UINT8                RdRd2Test,
  IN     INT8                 GuardBand
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcChannelOut       *ChannelOut;
  MrcControllerOut    *ControllerOut;
  MrcStatus           Status;
  UINT32              (*MarginByte) [MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32              BERStats[4];
  UINT16              SaveMargin[MAX_MARGINS_TRADEOFF][MAX_OPT_POINTS][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT16              PostMargin[MAX_MARGINS_TRADEOFF][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8               Test;
  UINT16              MinEye;
  UINT16              Margins[MAX_TRADEOFF_TYPES][MAX_OPT_POINTS]; // TestParam X 24 Comp Points
  UINT16              UpmLimits[MAX_TRADEOFF_TYPES];
  UINT16              PwrLimits[MAX_TRADEOFF_TYPES];
  INT16               Best;
  UINT8               OptimizationMode;
  UINT8               ResultType;
  UINT8               AveN;
  UINT8               Ave2DXDim;
  UINT8               Ave2DXLim;
  UINT8               MarginStart;
  INT8                RxEqMarginLength;
  UINT8               ChBitMask;
  UINT8               Channel;
  UINT8               Byte;
  UINT8               Rank;
  UINT8               Edge;
  UINT8               FirstRank;
  UINT8               NumBytes;
  UINT8               BMap[9]; // Need by GetBERMarginByte
  UINT8               Param;
  UINT8               MaxMargin;
  UINT8               localR[MAX_CHANNEL];
  UINT8               FirstRankPerCh[MAX_CHANNEL];
  UINT8               Rep;
  UINT8               CurrentComp;
  INT8                ReservedComp;
  INT8                MaxComp;
  UINT16              OptPower[MAX_CHANNEL][MAX_OPT_POINTS];
  INT8                Delta;
  UINT8               Index;
  UINT8               OffLen[MAX_GRID_DIM];
  INT8                ParamOff[MAX_GRID_DIM];
  UINT8               LenMargin;
  BOOLEAN             IncEnds;
  BOOLEAN             IncEndsForPrint;
  BOOLEAN             CPUComp;
  BOOLEAN             NeedForceComp;
  BOOLEAN             printPerCh;
  UINT8               OptIdx;
  MrcPower            BytePower;
  BOOLEAN             EnBer;
  BOOLEAN             Ddr4;
  UINT16              Margin;
  BOOLEAN             Lpddr;
  DDRCOMP_CR_DDRCRCMDCOMP_STRUCT          DdrCrCmdComp;
  DDRCOMP_CR_DDRCRCOMPCTL0_STRUCT         DdrCrCompCtl0;
  INT32               CmdCompVref[MAX_CHANNEL];
  UINT8               CmdCompCode[MAX_CHANNEL];
  UINT8               ClkPiMax[MAX_CHANNEL];
  INT8                ClkPiMin[MAX_CHANNEL];
  UINT16              MaxPi;
  UINT16              MinPi;
#ifdef LB_STUB_FLAG
  UINT16                ParamVector[3];
  UINT16                SimMargin;
  MRC_POWER_SYS_CONFIG  SysConfig;
#endif
  OptResultsPerByte calcResultSummary; // Result print summary: 5 columns per byte

  ResultType          = 0;
  CurrentComp         = 0;
  IncEnds             = 1;
  IncEndsForPrint     = 1;
  printPerCh          = 0;
  Inputs              = &MrcData->Inputs;
  MrcCall             = Inputs->Call.Func;
  ReservedComp        = 3; // Reserve 3 comp codes for adjustment range
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  ControllerOut       = &Outputs->Controller[0];
  MarginByte          = &Outputs->MarginResult;
  ChannelMask        &= Outputs->ValidChBitMask;
  RankMask           &= Outputs->ValidRankMask;
  NeedForceComp = FALSE;
  MrcCall->MrcSetMem ((UINT8 *) &calcResultSummary, sizeof (calcResultSummary), 0);
  MrcCall->MrcSetMem ((UINT8 *) BestOff, sizeof (OptOffsetChByte), 0xFF); // @todo: cleanup multiple clears.
  MrcCall->MrcSetMem ((UINT8 *) Margins, sizeof (Margins), 0);
  MrcCall->MrcSetMem ((UINT8 *) SaveMargin, sizeof (SaveMargin), 0);
  MrcCall->MrcSetMem ((UINT8 *) PostMargin, sizeof (PostMargin), 0);
  MrcCall->MrcSetMem ((UINT8 *) OptPower, sizeof (OptPower), 0);
  MrcCall->MrcSetMem ((UINT8 *) localR, sizeof (localR), 0);
  MrcCall->MrcSetMem ((UINT8 *) FirstRankPerCh, sizeof (FirstRankPerCh), 0);
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) &BytePower, sizeof (BytePower), 0);
  MrcCall->MrcSetMem ((UINT8 *) &OffLen, sizeof (OffLen), 0);
  MrcCall->MrcSetMemWord (UpmLimits, MAX_TRADEOFF_TYPES, 0);
  MrcCall->MrcSetMemWord (PwrLimits, MAX_TRADEOFF_TYPES, 0);
  MrcCall->MrcSetMem ((UINT8 *) &CmdCompVref, sizeof (CmdCompVref), 0);
  MrcCall->MrcSetMem ((UINT8 *) &CmdCompCode, sizeof (CmdCompCode), 0);
  Ddr4  = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  for (Byte = 0; Byte < ARRAY_COUNT (BMap); Byte++) {
    BMap[Byte] = Byte;
  }

  if (RdRd2Test == RdRdTA) {
    LoopCount -= 1;  // 2 TA tests, so cut the loop count in half.
  } else if (RdRd2Test == RdRdTA_All) {
    LoopCount -= 3;  // 8 TA tests, so divide the loop count by 8.
  }

  SetupIOTestBasicVA (MrcData, ChannelMask, LoopCount, 0, 0, 0, 8); // Set test to all channels.
  if (RdRd2Test != 0) {
    Outputs->DQPat = RdRd2Test;
  }
  //
  // Select All Ranks for REUT test
  //
  ChBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((0x1 << Channel) & ChannelMask)) {
      continue;
    }

    ChannelOut      = &ControllerOut->Channel[Channel];
    localR[Channel] = ChannelOut->ValidRankBitMask & RankMask;
    //
    // Use ChBitMask from here down - if ch is set that mean at least 1 rank for testing, also remove ch w/o active ranks
    //
    ChBitMask |= SelectReutRanks (MrcData, Channel, localR[Channel], 0);
    //
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "reut ranks ChBitMask %x Local ranks=%x\n", ChBitMask,localR[Channel]);
    // Clear any old state in DataTrain Offset
    //
    MrcCall->MrcSetMem ((UINT8 *) &ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((0x1 << Rank) & localR[Channel]) {
        FirstRankPerCh[Channel] = Rank;
        break;
      }
    }
  }

  if (ChBitMask == 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "TrainDDROptParam() ChBitMask == %d\n", ChBitMask);
    return;
  }
  //
  // Find the first selected rank
  //
  FirstRank = 0;
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((0x1 << Rank) & RankMask ) {
      FirstRank = Rank; // could be in any channel
      break;
    }
  }

  //
  // Store margin results (per byte or ch)
  //
  NumBytes = 1;
  for (OptIdx = 0; OptIdx < OptParamLen; OptIdx++ ) {
    if ((OptParam[OptIdx] != OptDimmOdt)  && (OptParam[OptIdx] != OptDimmOdtWr) && (OptParam[OptIdx] != OptDimmRon) &&
        (OptParam[OptIdx] != OptCmdSComp) && (OptParam[OptIdx] != OptCmdWrDS)   && (OptParam[OptIdx] != OptCmdTxEq)) {
      NumBytes = (UINT8) Outputs->SdramCount; // if one of param is per byte store per byte
    }
    //
    // Calculate Start/Stop Point for Comp Optimization
    //
    CPUComp = ((OptParam[OptIdx] == OptWrDS) || (OptParam[OptIdx] == OptWrDSUpCoarse) || (OptParam[OptIdx] == OptWrDSDnCoarse) || (OptParam[OptIdx] == OptRdOdt) ||
               (OptParam[OptIdx] == OptTComp) || (OptParam[OptIdx] == OptSComp));
    if (CPUComp) {
      if (OptParam[OptIdx] == OptSComp) {
        MaxComp = 31;
      } else {
        MaxComp = 63;
      }
      CurrentComp = GetCompCode (MrcData, OptParam[OptIdx], 2);
      if ((OptParam[OptIdx] == OptWrDSUpCoarse) || (OptParam[OptIdx] == OptWrDSDnCoarse)) {
        MaxComp /= 4;
        ReservedComp = DIVIDEROUND (ReservedComp, 4);
      }
      Delta = CurrentComp - ReservedComp + Start[OptIdx];
      if (Delta < 0) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "------------> warning offset range is clipped by %d\n", Delta);
        Start[OptIdx] -= Delta;
      }

      Delta = MaxComp - CurrentComp - ReservedComp - Stop[OptIdx];
      if (Delta < 0) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "------------> warning offset range is clipped by %d\n", Delta);
        Stop[OptIdx] += Delta;
      }

      if (Stop[OptIdx] < Start[OptIdx]) {
        Stop[OptIdx] = Start[OptIdx];
      }
      if (!SkipOptUpdate) {
        // print is irrelevant in this case
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "CurrentComp = %d, Start = %d, Stop = %d\n",
          CurrentComp,
          Start[OptIdx],
          Stop[OptIdx]
          );
      }
      NeedForceComp = TRUE;
    } else if ((OptParam[OptIdx] == OptCmdWrDS) || (OptParam[OptIdx] == OptCmdTxEq) || (OptParam[OptIdx] == OptCmdSComp)) {
      NeedForceComp = TRUE;
    }
  } // End OptIdx loop

  //
  // Determine where the power column is, or if we're training for best margin.
  //
  OptimizationMode = ((NumTests <= MAX_TRADEOFF_TYPES) && (Scale[NumTests] != 0)) ?
    NumTests : 100;

  //
  // Loop through all test params and measure margin.
  // Calc total num of points for full grid.
  //
  LenMargin = 1;
  for (OptIdx = 0; OptIdx < OptParamLen; OptIdx++) {
    OffLen[OptIdx] = (Stop[OptIdx] - Start[OptIdx] + 1);
    LenMargin *= OffLen[OptIdx];
    BestOff->GridDataSet.Start[OptIdx] = Start[OptIdx];
    BestOff->GridDataSet.OffLen[OptIdx] = OffLen[OptIdx];
  }
  if (SkipOptUpdate) {
    // Just run Margins test
    LenMargin = 1;
    GridMode = FullGrid;
  }
  if ((GuardBand !=0 ) && (OptParamLen == 2)) {
    // Make sure we apply the GB to the DS
    if (OptParam[1] == OptWrDS) {
      GuardBand *= OffLen[0];
    }
  }
  BestOff->GridDataSet.GridMode = GridMode;
  BestOff->GridDataSet.OptParamLen = OptParamLen;
  if (LenMargin >  MAX_OPT_POINTS) {
    LenMargin = MAX_OPT_POINTS;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "------------> warning : LenMargin exceed max: %d length is clipped\n", MAX_OPT_POINTS);
  }
  if (!NoPrint) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "LenMargin = %d, Test LoopCount = %d\n",LenMargin, LoopCount);
  }
  for (Test = 0; Test < NumTests; Test++) {
    Param = TestList[Test]; // tl[0]=4 tl[1]=1
    UpmLimits[Test] = MrcGetUpmPwrLimit (MrcData, Param, UpmLimit);
    PwrLimits[Test] = MrcGetUpmPwrLimit (MrcData, Param, PowerLimit);
    ResultType      = GetMarginResultType (Param); // rxv=0 rxt=1
    if ((Param == CmdT) || (Param == CmdV)) {
      SetupIOTestCADB (MrcData, ChannelMask, LoopCount, NSOE, 1, 0);
      IncEnds = 1;
    }
    //
    // Assign to last pass margin results by reference
    // get lowest margin from all ch/rankS/byte save in FirstRank
    //
    Status = GetMarginByte (MrcData, Outputs->MarginResult, Param, FirstRank, RankMask);
    //
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n--- FirstRank = %d ResultType=%d Param=%d ranks=0x%x\n", FirstRank,ResultType,Param,RankMask);
    // Calculate the MaxMargin for this test
    //
    MaxMargin = MAX_POSSIBLE_TIME;
#if (SUPPORT_DDR4 == SUPPORT)
    if (Ddr4 && ((Param == WrV) || (Param == WrFan2) || (Param == WrFan3))) {
      MaxMargin = MAX_POSSIBLE_DDR4_WRITE_VREF;
    } else
#endif //SUPPORT_DDR4
    if ((Param == RdV) ||
        (Param == RdFan2) ||
        (Param == RdFan3) ||
        (Param == WrV) ||
        (Param == WrFan2) ||
        (Param == WrFan3) ||
        (Param == CmdV)
        ) {
      MaxMargin = MAX_POSSIBLE_VREF;
    } else if (Param == CmdT) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if ((1 << Channel) & ChBitMask) {
          // Find the maximum CLK Sweep range based on Min/Max values of TxDq, TxDqs and RcvEn.
          FindDqPiLimits (MrcData, Channel, localR[Channel], &MinPi, &MaxPi);
          ClkPiMin[Channel] = (MinPi < 64) ? (INT8) (0 - MinPi) : -64;

          ClkPiMax[Channel] = ((MaxPi + 64) > DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX) ?
                        (UINT8) (DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX - MaxPi) : 64;
        } else {
          // Apply values for unpopulated channels
          ClkPiMin[Channel] = DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MAX;
          ClkPiMax[Channel] = DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MIN;
        }
      }
    }
    //
    // No need to search too far
    //
    if (MaxMargin > (PwrLimits[Test] / 20)) {
      MaxMargin = (UINT8) (PwrLimits[Test] / 20);
    }
    //
    // Loop Through all Comp Codes
    //
    for (Index = 0; Index < LenMargin; Index ++) {
      //
      // Continue accordingly to GridMode
      //
      if (GetParamsXYZ (MrcData, ParamOff, OptParamLen, GridMode, Index, Start, OffLen)) { // return ParamOff[param]
        continue;
      }
      for (OptIdx = 0; OptIdx < OptParamLen; OptIdx++ ) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!((0x1 << Channel) & ChBitMask)) {
            continue;
          }

          ChannelOut = &ControllerOut->Channel[Channel];
          for (Byte = 0; Byte < NumBytes; Byte++) {
            if (!SkipOptUpdate) {
              //
              // Change OpParam offset for all ch/byte/LocalR
              // Note: When using multi OptParams need to take care that one is not overwritten
              //       by the other in UpdateOptParamOffset routine (because UpdateHost=0).
              // Note: Some are limited in range inside e.g: RdOdt +15:-16
              //
              UpdateOptParamOffset (MrcData, Channel, localR[Channel], Byte, OptParam[OptIdx], ParamOff[OptIdx], 0);
            }
            //
            // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n--Channel=%d, localR[Channel]=%x Byte=%d OffsetComp=%d Off=%d\n",Channel,localR[Channel],Byte,OffsetComp,Off);
            //
          }
        }
      }
      if (NeedForceComp) {
        ForceRcomp (MrcData);
      }

      for (Rep = 0; Rep < Repeats; Rep++) {
        //
        // Run Margin Test - margin_1d with chosen param
        // run on all ranks but change param only for firstRank??
        //
        EnBer = 1;

#ifndef LB_STUB_FLAG
        if ((Param == CmdT) || (Param == CmdV)) {
          // For CMD margins we add a preliminary centering of CMD timing due to the possible impact on CTL margin limited by CMD.
          // This pre-centering is expected to leverage problems resulted in worsened CmdV/CmdT margin in RMT.
          // Important - Update Host must be set to zero!!!
          // This parameter may impact the final selection of the centered CMD Timing, in order to avoid high repetition noise or possible degradation.
          Status = MrcCmdTimingCentering (MrcData, ChannelMask, LoopCount, FALSE, MRC_PRINTS_OFF, 0);
        }
        if (Param == CmdT) {
          if (Lpddr) {
            CmdLinearFindEdgesLpddr (MrcData, MrcIterationClock, ChBitMask, 0xF, MRC_PRINTS_OFF);
          } else {
            CmdLinearFindEdges (MrcData, MrcIterationClock, ChBitMask, 0xF, 3, ClkPiMin, ClkPiMax, 1, 1, (INT8 *) NULL, MRC_PRINTS_OFF, TRUE, FALSE);
          }

          //
          // Restore centered value
          //
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
              if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
                ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, 1 << Rank, 3, 0, 0);
              }
            }
          }
        } else if (Param == CmdV) {
          Status = MrcGetBERMarginCh (
            MrcData,
            Outputs->MarginResult,
            ChBitMask,
            0xFF,
            FirstRank,
            Param,
            0,  // Mode
            0,
            MaxMargin,
            0,
            BERStats
            );
        } else {
          //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcGetBERMarginByte ChBitMask=%x FirstRank=%d Param=%d\n",ChBitMask, FirstRank, Param);
          Status = MrcGetBERMarginByte (
            MrcData,
            Outputs->MarginResult,
            ChBitMask,
            (Ddr4 && (Param == WrV)) ? RankMask : FirstRank,
            (Ddr4 && (Param == WrV)) ? RankMask : FirstRank,
            Param,
            0,  // Mode
            BMap,
            EnBer,
            MaxMargin,
            0,
            BERStats
            );
        }
        if ((Param == CmdT) || (Param == CmdV)) {
          Status = MrcResetSequence (MrcData);
        }
#endif
        //
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " finish MrcGetBERMarginByte \n");
        // Record Results
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!((0x1 << Channel) & ChBitMask)) {
            continue;
          }
          MinEye = 0xFFFF;
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            SaveMargin[Test][Index][Channel][Byte] = 0;
            for (Edge = 0; Edge < MAX_EDGES; Edge++) {
              if (Param != CmdT) {
                // CmdT margins are stored according to a slightly different convention - Save in first populated rank per channel
                // All other margins are saved to first populated rank among all channels
                Margin = (UINT16) (*MarginByte)[ResultType][FirstRank][Channel][Byte][Edge];
                SaveMargin[Test][Index][Channel][Byte] += Margin;
              }
            }
            if (Param == CmdT) {
              // For the case of CmdT we had previously performed centering of CMD Timing. If the margin is not centered then we apply a penalty to avoid this selection.
              SaveMargin[Test][Index][Channel][Byte] = 2 * MIN ((UINT16) (*MarginByte)[ResultType][FirstRankPerCh[Channel]][Channel][Byte][0],
                                                                (UINT16) (*MarginByte)[ResultType][FirstRankPerCh[Channel]][Channel][Byte][1]);
            }
            if (MinEye > SaveMargin[Test][Index][Channel][Byte]) {
              MinEye = SaveMargin[Test][Index][Channel][Byte];
            }
            if ((Param == CmdT) || (Param == CmdV)) {
              break;  // Exit per-byte loop
            }
          }
          if (NumBytes == 1) {
            SaveMargin[Test][Index][Channel][0] = MinEye;
          }
        }
      }
    } // end of offset

    if ((Param == CmdT) || (Param == CmdV)) {
      MrcDisableCadbOnDeselect (MrcData);
    }

#ifdef MRC_DEBUG_PRINT
    PrintResultTableByte4by24 (
      MrcData,
      ChBitMask,
      SaveMargin,
      Test,
      LenMargin,
      0,
      OptParam[0],// @todo expand to more then 1
      TestList[Test],
      PwrLimits,
      NoPrint
      );

#endif // MRC_DEBUG_PRINT
  } // end of test list
  //
  // Calculate the best value for every byte
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((0x1 << Channel) & ChBitMask)) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    // no need to run on channel with no selected ranks
    if (!(ChannelOut->ValidRankBitMask & localR[Channel])) {
      continue;
    }
    for (Byte = 0; Byte < NumBytes; Byte++) {
      //
      // Populate Margins array and asymmetric penalty
      //
      for (Test = 0; Test < NumTests; Test++) {
        for (Index = 0; Index < LenMargin; Index++) {
          Margins[Test][Index] = SaveMargin[Test][Index][Channel][Byte];
        }
      }
      //
      // Special Cases for Running Average Filter
      //
      if (OptParamLen == 1) { // 1D case
        if ((OptParam[0] == OptDimmOdt) || (OptParam[0] == OptDimmOdtWr) || (OptParam[0] == OptDimmRon) || (OptParam[0] == OptCmdSComp)) {
          AveN = 1;
        } else if (OptParam[0] == OptRxBias) {
          AveN = 3;
        } else if (OptParam[0] == OptRxEq) {
          //
          // Use special, 2D running average for RxEq
          //
          Ave2DXDim         = 4;
          Ave2DXLim         = 0;
          MarginStart       = 1;  // Skipping the first setting since it is a bypass mode.
          RxEqMarginLength  = LenMargin - 1;
          AveN = 1;
          for (Test = 0; Test < NumTests; Test++) {
            RunningAverage2D (&Margins[Test][MarginStart], RxEqMarginLength, Ave2DXDim, Ave2DXLim, Test);
          }
        } else {
          AveN = 7;
          if (LenMargin < AveN) {
            AveN = LenMargin - 1;
          }
        }
      } else {
        // 2D case (for now) - Todo: should depend on GridMode.
        AveN = 1;
        for (Test = 0; Test < NumTests; Test++) {
          if (GridMode < FullGrid) {
            Fill2DAverage (MrcData, Margins, Test, LenMargin, OffLen[0], 0, 1);
            for (Index = 0; Index < LenMargin; Index++) { // refill the SaveMargin array after filling the gaps
              SaveMargin[Test][Index][Channel][Byte] = Margins[Test][Index];
            }
          }
          RunningAverage2D (&Margins[Test][0], LenMargin, OffLen[0], 0, 1);
        }
      }
      //
      // Use one of the Margin Arrays for fine grain power tradeoffs. This is only used if Scale[NumTests] is not 0
      //
      for (Index = 0; Index < LenMargin; Index++) {
        MrcCall->MrcSetMem ((UINT8 *) &BytePower, sizeof (BytePower), 0);
        GetParamsXYZ (MrcData, ParamOff, OptParamLen, GridMode, Index, Start, OffLen);
        CalcOptPowerByte (MrcData, &BytePower, Channel, FirstRank, Byte, OptParam, ParamOff, OptParamLen, CurrentComp, 10);
        if (((OptParam[0] >= OptRdOdt) && (OptParam[0] <= OptRxCb)) || (OptParam[0] == OptDimmRon)) {
          Margins[NumTests][Index] = BytePower.RdPower;
        } else {
          Margins[NumTests][Index] = BytePower.WrPower;
        }
        OptPower[Channel][Index] = Margins[NumTests][Index]; //+= BytePower.TotalPwr; // sum all bytes.  @todo check if OptPower[Index]can be remove (for print)
        //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "OptPower[%d][%d]: %d Power->WrPower: %d\n", Channel, Index, OptPower[Channel][Index], BytePower.TotalPwr);
      }
      //
      // need to provide set of power numbers depending on the OffsetComp codes (per byte)for trend line.
      //
      NormalizePowerToMargins (MrcData, Margins, MAX_OPT_POINTS, LenMargin, NumTests);

      //
      // Use that value to create Margin Results based on power.
      // Creates a smooth, linear function that goes from MaxSum to N/(N-1)*MaxSum
      // RatioNum = FinePwrRatio[OptParam] * LenMargin; //e.g FinePwrRatio[RdOdt]=5
      // Find the Best Overall Setting
      // senSq=0,caleM=1,powerOpHigh=0
      //
      FindOptimalTradeOff (
        MrcData,
        &calcResultSummary,
        &Margins[0][0],
        MAX_OPT_POINTS,
        LenMargin,
        Scale,
        UPMOptimize,
        0,
        AveN,
        IncEnds,
        1,
        UpmLimits,
        OptimizationMode,
        GuardBand,
        FALSE  //EnableLinearApproximationOptimizationMode
        );
      //
      // Get the best index considering the GuardBand
      //
      Best = calcResultSummary.Best + calcResultSummary.GuardBand;
      for (Test = 0; Test < NumTests; Test++) {
        // PostMargin will be reported back to DimmOdt
        // in old method you can get non coherency between result here and what reported out
        PostMargin[Test][Channel][Byte] = calcResultSummary.Margins[Test][Best].EW;
      }
      //
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n Best =%d ch=%d byte=%d \n",Best,Channel,Byte);
      // Update CR
      //
      //
      // Best is Index, need to convert to OptParam Offset (ParamOff)
      //
      //Best -= Shift  // update take offset look like bug

      GetParamsXYZ (MrcData, ParamOff, OptParamLen, GridMode, (UINT8) Best, Start, OffLen);
      if (!SkipOptUpdate) {
        for (OptIdx = 0; OptIdx < OptParamLen; OptIdx++ ) {
          UpdateOptParamOffset (MrcData, Channel, localR[Channel], Byte, OptParam[OptIdx], ParamOff[OptIdx], 1);

          if ((OptParam[OptIdx] == OptCmdSComp) || (OptParam[OptIdx] == OptCmdWrDS)) {
            // Cmd SR / DS training is performed using global comp (due to insufficient range of offsets).
            // After global comp is found, the average value of both channels is programmed
            // and the channel offsets are used to compensate for the channel variations.

            DdrCrCmdComp.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRCMDCOMP_REG);

            if (OptParam[OptIdx] == OptCmdSComp) {
              CmdCompVref[Channel] = (INT32) ParamOff[OptIdx];
              CmdCompCode[Channel] = (UINT8) DdrCrCmdComp.Bits.Scomp;
            } else if (OptParam[OptIdx] == OptCmdWrDS) {
              DdrCrCompCtl0.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL0_REG);
              CmdCompVref[Channel] = DdrCrCompCtl0.Bits.CmdDrvVref;
              CmdCompCode[Channel] = (UINT8) DdrCrCmdComp.Bits.RcompDrvUp;
            }
            MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Channel %u Param %s Cmd Optimal CmdVref %d Got Comp Code %u\n",
              Channel,
              TOptParamOffsetString[OptParam[OptIdx]],
              CmdCompVref[Channel],
              CmdCompCode[Channel]);
          }
        }
      }
      //
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " localR[Channel]=%x Best =%d ch=%d byte=%d \n",localR[Channel],(UINT8) Best,Channel,Byte);
      //
      BestOff->Offset[Channel][Byte] = Best;
#ifdef MRC_DEBUG_PRINT
      for (Test = 0; Test < NumTests; Test++) {
        Print2DResultTableChByte (
          MrcData,
          Channel,
          Byte,
          &calcResultSummary,
          BestOff,
          TestList[Test],
          LenMargin,
          Start,
          Stop,
          OptParam,
          OffLen,
          PwrLimits,
          OptParamLen,
          Test,
          NumTests,
          NoPrint
          );
      }
#endif // MRC_DEBUG_PRINT
    } // end byte
    // Print After Calc (Stack Size Reduction)
    //
    // Printing the results
    //
#ifdef MRC_DEBUG_PRINT


    if (0) {
      //
      // printing the results
      //
      // @todo: make some loop here
      IncEndsForPrint =
      (
        OptParam[0] == OptDimmOdt ||
        OptParam[0] == OptDimmOdtWr ||
        OptParam[0] == OptDimmRon ||
        OptParam[0] == OptRxEq ||
        IncEnds
        );
      printPerCh = (OptParam[0] == OptDimmOdt || OptParam[0] == OptDimmOdtWr || OptParam[0] == OptDimmRon);
      //
      // lower bytes
      //
      PrintCalcResultTableCh (
        MrcData,
        &calcResultSummary,
        TestList,
        NumTests,
        LenMargin,
        0,
        IncEndsForPrint,
        OptParam[0],
        OptPower[Channel],
        Channel,
        localR[Channel],
        Scale[NumTests],
        0,
        printPerCh,
        NoPrint
        );
      //
      // higher bytes
      //
      if (!printPerCh) {
        PrintCalcResultTableCh (
          MrcData,
          &calcResultSummary,
          TestList,
          NumTests,
          LenMargin,
          0,
          IncEndsForPrint,
          OptParam[0],
          OptPower[Channel],
          Channel,
          localR[Channel],
          Scale[NumTests],
          1,
          printPerCh,
          NoPrint
          );
      }
    } // if (0)
#endif // MRC_DEBUG_PRINT
  } // End of Calculating best value (ch)

  // Compensate Cmd SR / DS comp code
  for (OptIdx = 0; OptIdx < OptParamLen; OptIdx++) {
    if ((OptParam[OptIdx] == OptCmdSComp) || (OptParam[OptIdx] == OptCmdWrDS)) {
      CmdCompensateOptParam (MrcData, ChBitMask, CmdCompVref, CmdCompCode, OptParam[OptIdx]);
    }
  }

  //
  // Update the LastPass points in host
  //
  for (Test = 0; Test < NumTests; Test++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((MRC_BIT0 << Channel) & ChBitMask)) {
        continue;
      }

      ResultType = GetMarginResultType (TestList[Test]);
      for (Byte = 0; Byte < NumBytes; Byte++) {
        //
        // save the margins in best offset point for each byte/ch in  rank 0/1
        //
        Best = (UINT8) (BestOff->Offset[Channel][Byte]);

        (*MarginByte) [ResultType][0][Channel][Byte][0] =
          SaveMargin[Test][Best][Channel][Byte] / 2;
        (*MarginByte) [ResultType][0][Channel][Byte][1] =
          SaveMargin[Test][Best][Channel][Byte] / 2;
        //
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "best offset= %d ;byte=%d ;(*MarginByte)[ResultType][0][Channel][Byte][0] -%d (*MarginByte)[ResultType][0][Channel][Byte][1] -%d add=%d\n",(UINT8) (BestOff->Offset[Channel][Byte] - Start),Byte,(UINT16) (*MarginByte)[ResultType][0][Channel][Byte][0] , (*MarginByte)[ResultType][0][Channel][Byte][1],((UINT16) (*MarginByte)[ResultType][0][Channel][Byte][0] + (UINT16)(*MarginByte)[ResultType][0][Channel][Byte][1]));
        //
      }
    }

    Status = ScaleMarginByte (MrcData, Outputs->MarginResult, TestList[Test], 0);
  }

  BestOff->NumTests = NumTests;
  for (Test = 0; Test < NumTests; Test++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((MRC_BIT0 << Channel) & ChBitMask)) {
        continue;
      }
      //
      // Track minimum eye width per ch
      //
      for (Byte = 0; Byte < NumBytes; Byte++) {
        if (Byte == 0) {
          BestOff->Margins[Test][Channel] = PostMargin[Test][Channel][0];
        } else if (BestOff->Margins[Test][Channel] > PostMargin[Test][Channel][Byte]) {
          BestOff->Margins[Test][Channel] = PostMargin[Test][Channel][Byte];
        }
      }
      BestOff->TestList[Test][Channel] = TestList[Test];
      // @todo : add OptParam list
    }
  }
  //
  // Clean up
  //
  if (NeedForceComp) {
    ForceRcomp (MrcData);
  }

  return;
}

/**
  This function implements Read ODT training.
  Optimize Read ODT strength for performance & power

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it succeded return mrcSuccess
**/
MrcStatus
MrcReadODTTraining (
  IN MrcParameters *const MrcData
  )
{
  MrcStatus                         Status;
  const MrcInput                    *Inputs;
  MrcDebug                          *Debug;
  MrcIntOutput                      *IntOutput;
  MrcIntControllerOut               *IntControllerOut;
  MrcOutput                         *Outputs;
  UINT8                             *TestList;
  UINT8                             TestListNonLp[]  = { RdV, RdT };
  UINT8                             TestListSize;
  UINT8                             ScaleNonLp[]     = { 1, 2, 1, 0, 0 };
  UINT8                             *Scale;
  INT8                              Start;
  INT8                              Stop;
  UINT8                             OdtCodeMin;
  UINT8                             OdtCodeMax;
  INT8                              Delta;
  UINT16                            Rleg;
  INT8                              StatLegs;
  UINT8                             OdtLegsDis;
  INT8                              CurrentVref;
  UINT8                             CurrentCompDn;
  UINT8                             CurrentCompUp;
  OptOffsetChByte                   BestOff;
  UINT8                             RecenterLC;
  UINT8                             RdTATestType;
  UINT8                             OptParam[] = {OptRdOdt};
  UINT8                             TestListLpddr[] = { RdV, RdT, RcvEnaX };
  UINT8                             ScaleLpddr[]    = { 1, 2, 2, 1, 0 };
  BOOLEAN                           Lpddr;
  DDRCOMP_CR_DDRCRCOMPCTL0_STRUCT   DdrCrCompCtl0;
  DDRCOMP_CR_DDRCRDATACOMP1_STRUCT  DdrCrDataComp1;

  IntOutput         = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut  = &IntOutput->Controller[0];
  Outputs     = &MrcData->Outputs;
  Inputs      = &MrcData->Inputs;
  Debug       = &Outputs->Debug;
  Status      = mrcSuccess;
  RecenterLC  = 15;

  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  Start = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop  = OptParamLimitValue (MrcData, OptParam[0], 1);
  //
  // Find a start offset where we below 180ohm to protect against OS/US
  //
  DdrCrDataComp1.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRDATACOMP1_REG);
  CurrentCompUp       = (INT8) DdrCrDataComp1.Bits.RcompOdtUp;
  CurrentCompDn       = (INT8) DdrCrDataComp1.Bits.RcompOdtDown;
  OdtCodeMin          = MIN(CurrentCompUp, CurrentCompDn); //ohm
  OdtCodeMax          = MAX(CurrentCompUp, CurrentCompDn); //ohm
  RdTATestType        = RdRdTA;

  if (Lpddr) {
    RdTATestType = RdRdTA_All;
    TestList     = TestListLpddr;
    Scale        = ScaleLpddr;
    TestListSize = ARRAY_COUNT (TestListLpddr);
  } else {
    TestList            = TestListNonLp;
    TestListSize        = ARRAY_COUNT (TestListNonLp);
    Scale               = ScaleNonLp;
  }

  if (Inputs->EnVttOdt || (Inputs->PowerTrainingMode == MrcTmMargin)) {
    Scale[TestListSize] = 0; // no power considuration in Vtt
  }


  DdrCrCompCtl0.Data  = IntControllerOut->CompCtl0.Data;
  OdtLegsDis          = (UINT8) DdrCrCompCtl0.Bits.DisableOdtStatic;
  CurrentVref         = (INT8) DdrCrCompCtl0.Bits.DqOdtVref;
  StatLegs            = 4 * 4; // we enable only 1/3 segment for odt @todo vtt/DT  change
  if (CurrentVref & 0x10) {
    CurrentVref -= 0x20; // 2's complement
  }

  Rleg  = CalcCpuImpedance (MrcData, 0, 0, 0, OptRdOdt, TRUE, 0, TRUE, CurrentVref, CurrentCompUp) * (StatLegs * (!OdtLegsDis) + CurrentCompUp);;

  //
  // Check Comp code limit on start and stop
  //
  Delta = OdtCodeMin + Start;
  if (Delta < 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "------------> warning offset range is clipped by %d\n", Delta);
    Start -= Delta;
  }

  Delta = 63 - OdtCodeMax - Stop;
  if (Delta < 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "------------> warning offset range is clipped by %d\n", Delta);
    Stop += Delta;
  }

  if (Stop > (MAX_OPT_POINTS + Start)) {
    Stop = (INT8) (MAX_OPT_POINTS + Start); // MAX_OPT_POINTS offsets in the margin array.
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    " current code = %d OdtLegsDis = %d Rleg = %d CurrentVref = %d  Start = %d Stop = %d\n",
    CurrentCompUp,
    OdtLegsDis,
    Rleg,
    CurrentVref,
    Start,
    Stop
    );

  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xF,
    OptParam,
    ARRAY_COUNT (OptParam),
    FullGrid,
    TestList,
    TestListSize,
    Scale,
    NULL,
    &Start,
    &Stop,           // Stop
    OPT_PARAM_LOOP_COUNT + 2, // Loopcount increased from 15 to better match RMT margins
    1,              // Repeats
    0,              // NoPrint
    0,              // SkipOptUpdate
    RdTATestType,   // RdRd2Test
    0               // GuardBand
    );

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Read Timing\n");
  Status = ReadVoltageCentering2D (
             MrcData,
             Outputs->MarginResult,
             Outputs->ValidChBitMask,
             RdV,
             0,
             0,
             RecenterLC,
             1
             );
  Status = DataTimeCentering2D (
             MrcData,
             Outputs->MarginResult, // prev. margin results
             0x3,
             RdT,
             0, // EnPerBit,
             0, // EnRxDutyCycle
             0, // ResetPerBit
             RecenterLC,
             0  // En2D
             );

  return Status;
}

/**
  This function implements Write Slew Rate training.
  Optimize Write Slew Rate for performance & power

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcWriteSlewRate (
  IN MrcParameters *const MrcData
  )
{
  static const UINT8  TestList[] = { WrV, WrT };
  static const UINT8  Scale[]    = { 1, 2, 0, 0, 0 };
  static const UINT8  OptParam[] = { OptSComp };
  OptOffsetChByte     BestOff;
  INT8                Start;
  INT8                Stop;

  Start = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop  = OptParamLimitValue (MrcData, OptParam[0], 1);

  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xf,
    OptParam,
    ARRAY_COUNT (OptParam),
    CustomSR,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    &Start,            // Start
    &Stop,             // Stop
    OPT_PARAM_1D_LC,
    1,    // Repeats
    0,    // NoPrint
    0,    // SkipOdtUpdate
    0,    // RdRd2Test
    0     // GuardBand
    );

  return mrcSuccess;
}

/**
  Updates a given ch/Rank/byte combination with a new value for OptParam
  OptParam can be: WrDS, RdOdt, TComp, SComp, RxEq, TxEq, RxBias, DimmOdt,OptCmdSComp, OptCmdWrDS or OptCmdTxEq
  OptParam == OptDefault restore values from Host except Dimms Odt's
  @param[in,out] MrcData         - Include all MRC global data.
  @param[in]     Channel         - Channel index to work on.
  @param[in]     Ranks           - Condenses down the results from multiple ranks
  @param[in]     Byte            - Byte index to work on.
  @param[in]     OptParam        - Defines the OptParam Offsets.
                                   Supported OptParam = [0: WrDS, 1: RdODT, 2: SComp, 3: TComp, 4: TxEq,
                                                         5: RxEq, 6: RxBias, 7: DimmOdt, 8: DimmOdtWr]
  @param[in]     Off             - Offset
  @param[in]     UpdateHost      - Desides if MrcData has to be updated

  @retval Nothing
**/
void
UpdateOptParamOffset (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN           UINT8          Ranks,
  IN     const UINT8          Byte,
  IN           UINT8          OptParam,
  IN     INT16                Off,
  IN     const UINT8          UpdateHost
  )
{
  static const UINT16    RttNomMRSEncodingConst[]       = {0x00, 0x01, 0x10, 0x11, 0x80, 0x81};              // DDR3 RttNom   :0, 60, 120, 40, 20, 30 Ohms
  static const UINT16    RttWrMRSEncodingConst[]        = {0x00, 0x01, 0x02};                                // DDR3 RttWr    :RttNom, 60, 120 Ohms
  static const UINT16    RttDimmRonEncodingDDR3Const[]  = {0x00, 0x02};                                      // DDR3 Ron      :40, 34 Ohms
  static const UINT16    RttWrMRSEncodingDDR4Const[]    = {0x00, 0x01, 0x02, 0x03, 0x04};                    // DDR4 RttWr    :0, 120, 240, Hi-z, 80 Ohms
  static const UINT16    RttDimmRonEncodingDDR4Const[]  = {0x00, 0x02};                                      // DDR4 Ron      :34, 48 Ohms
  static const UINT16    DDR4RttNomMRSEncodingConst[]   = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};  // DDR4 RttNom   :0, 60, 120, 40, 240, 48, 80, 34 Ohms
  static const UINT8     LpddrRonEnc[]                  = {0x1, 0x2, 0x3};                                   // LPDDR3 Ron    :34, 40, 48 Ohm
  static const UINT8     LpddrOdtEnc[]                  = {0x0, 0x1, 0x2, 0x3};                              // LPDDR3 RttWr  :Off, 60, 120, 240 Ohm
  const MRC_FUNCTION *MrcCall;
  const MrcInput  *Inputs;
  MrcDebug        *Debug;
  BOOLEAN         UlxUlt;
  BOOLEAN         Lpddr;
#if (SUPPORT_DDR4 == SUPPORT)
  BOOLEAN         Ddr4;
  UINT16          DDR4RttNomMRSEncoding[ARRAY_COUNT (DDR4RttNomMRSEncodingConst) ];
  UINT16          DDR4RttWrMRSEncoding[ARRAY_COUNT (RttWrMRSEncodingDDR4Const) ];
#endif // SUPPORT_DDR4
  MrcOutput           *Outputs;
  MrcChannelOut       *ChannelOut;
  MrcIntOutput        *IntOutput;
  MrcIntControllerOut *IntControllerOut;
  MrcIntChannelOut    *IntChannelOut;
  UINT16          *MrReg;
  MrcStatus       Status;
  BOOLEAN         Type;
  UINT8           Rank;
  UINT8           RankMask;
  UINT8           Value;
  UINT8           Index;
  UINT8           RttNomShift;
  UINT8           RttNomMax;
  UINT8           RttWrMax;
  UINT16          MRValue;
  INT16           TempOff;
  UINT16          RttNomMRSEncoding[ARRAY_COUNT (RttNomMRSEncodingConst) ];
  UINT16          RttWrMRSEncoding[ARRAY_COUNT (RttWrMRSEncodingConst) ];
  UINT16          *pRttWrEncoding;
  UINT16          RttWr, RttNom, RttNomMask;
  UINT8           MrAddress;
  UINT16          DimmRon;
  UINT16          RttWrMask;
  UINT16          DimmRonMask;
  UINT32          Offset;
  INT16           OffCode;
  INT16           OffMin;
  INT16           OffMax;
  UINT8           CompCode;
  UINT8           SlewRateVref;
  DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetComp;
  DDRSCRAM_CR_DDRMISCCONTROL0_STRUCT        DdrMiscControl0;
  DDRDATA0CH0_CR_DDRCRDATACONTROL1_STRUCT   DdrCrDataControl1;
  DDRDATA0CH0_CR_DDRCRDATACONTROL2_STRUCT   DdrCrDataControl2;
  DDRCOMP_CR_DDRCRCOMPCTL2_STRUCT           DdrCrCompCtl2;
  DDRCMDCH0_CR_DDRCRCMDCONTROLS_STRUCT      DdrCrCmdControls;

  IntOutput    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutput->Controller[0];
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ChannelOut    = &Outputs->Controller[0].Channel[Channel];
  IntChannelOut = &IntControllerOut->Channel[Channel];
  MrcCall->MrcCopyMem ((UINT8 *) RttNomMRSEncoding, (UINT8 *) RttNomMRSEncodingConst, sizeof (RttNomMRSEncoding));
  MrcCall->MrcCopyMem ((UINT8 *) RttWrMRSEncoding, (UINT8 *) RttWrMRSEncodingConst, sizeof (RttWrMRSEncoding));
  UlxUlt        = ((Inputs->CpuModel == cmSKL_ULX_ULT) || (Inputs->CpuModel == cmKBL_ULX_ULT));

  //
  // Check if LPDDR3 memory is used
  //
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
#if (SUPPORT_DDR4 == SUPPORT)
  Ddr4 = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  MrcCall->MrcCopyMem ((UINT8 *) DDR4RttNomMRSEncoding, (UINT8 *) DDR4RttNomMRSEncodingConst, sizeof (DDR4RttNomMRSEncoding));
  MrcCall->MrcCopyMem ((UINT8 *) DDR4RttWrMRSEncoding, (UINT8 *) RttWrMRSEncodingDDR4Const, sizeof (DDR4RttWrMRSEncoding));
#endif // SUPPORT_DDR4

  //
  // Compensation Offsets
  //
  Type =
    (
      (OptParam == OptWrDS) ||
      (OptParam == OptWrDSUp) ||
      (OptParam == OptWrDSDn) ||
      (OptParam == OptWrDSUpCoarse) ||
      (OptParam == OptWrDSDnCoarse) ||
      (OptParam == OptRdOdt) ||
      (OptParam == OptRdOdtUp) ||
      (OptParam == OptRdOdtDn) ||
      (OptParam == OptTComp) ||
      (OptParam == OptSComp) ||
      (OptParam == OptDefault)
    );
  if (Type) {
    if (OptParam == OptWrDS ||
        (OptParam == OptWrDSUp) ||
        (OptParam == OptWrDSDn)) {
      OffMin = -32;
      OffMax = 31;
    } else if ((OptParam == OptWrDSUpCoarse) ||
               (OptParam == OptWrDSDnCoarse)) {
      OffMin = -8;
      OffMax = 7;
    } else if (OptParam == OptSComp) {
      OffMin = -17; // -17 for SR dis.
      OffMax = 15;
    } else {
      OffMin = -16;
      OffMax = 15;
    }

    if (Off > OffMax) {
      Off = OffMax;
    } else if (Off < OffMin) {
      Off = OffMin;
    }

    DdrCrDataOffsetComp.Data = ChannelOut->DataCompOffset[Byte];
    DdrCrDataControl2.Data = IntChannelOut->DqControl2[Byte].Data;

    if (OptParam == OptWrDS) {
      DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset    = Off;
      DdrCrDataOffsetComp.Bits.DqDrvDownCompOffset  = Off;
    } else if (OptParam == OptRdOdt) {
      DdrCrDataOffsetComp.Bits.DqOdtUpCompOffset    = Off;
      DdrCrDataOffsetComp.Bits.DqOdtDownCompOffset  = Off;
    } else if (OptParam == OptTComp) {
      DdrCrDataOffsetComp.Bits.DqTcoCompOffset      = Off;
    } else if (OptParam == OptSComp) {
      if (Off == -17) {
        // Just picked value outside SR range.
        DdrCrDataControl2.Bits.DqSlewDlyByPass = 1;
      } else {
        DdrCrDataOffsetComp.Bits.DqSlewRateCompOffset = Off;
        DdrCrDataControl2.Bits.DqSlewDlyByPass = 0;
      }
    } else if (OptParam == OptWrDSDn) {
      DdrCrDataOffsetComp.Bits.DqDrvDownCompOffset  = Off;
    } else if (OptParam == OptWrDSUp) {
      DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset    = Off;
    } else if (OptParam == OptWrDSDnCoarse) {
      DdrCrDataOffsetComp.Bits.DqDrvDownCompOffset  = 4 * Off;
    } else if (OptParam == OptWrDSUpCoarse) {
      DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset    = 4 * Off;
    } else if (OptParam == OptRdOdtUp) {
      DdrCrDataOffsetComp.Bits.DqOdtUpCompOffset    = Off;
    } else if (OptParam == OptRdOdtDn) {
      DdrCrDataOffsetComp.Bits.DqOdtDownCompOffset  = Off;
    }
    Offset = MrcGetOffsetDataOffsetComp (MrcData, Channel, Byte);
    MrcWriteCR (MrcData, Offset, DdrCrDataOffsetComp.Data);
    if (UpdateHost) {
      ChannelOut->DataCompOffset[Byte] = DdrCrDataOffsetComp.Data;
    }
    if (OptParam == OptSComp) {
      Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
      MrcWriteCR (MrcData, Offset, DdrCrDataControl2.Data);
      if (UpdateHost) {
        IntChannelOut->DqControl2[Byte].Data = DdrCrDataControl2.Data;
      }
    }
    //
    // Propagate new value and force comp update
    //
    DdrMiscControl0.Data = IntControllerOut->MiscControl0.Data;

    DdrMiscControl0.Bits.DataClkGateDisAtIdle = 1;

    DdrMiscControl0.Bits.ForceCompUpdate = 1;
    MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL0_REG, DdrMiscControl0.Data);

  }
  //
  // Equalization Settings
  //
  Type = ((OptParam == OptTxEq) || (OptParam == OptRxEq) || (OptParam == OptDefault));
  if (Type) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((MrcRankInChannelExist (MrcData, Rank, Channel)) && ((Ranks & (MRC_BIT0 << Rank)))) {
        //
        // TxEq[5:4] = Emphasize   = [4, 8, 12, 15] legs 3/2 seg? SKL : TODO
        // TxEq[3:0] = Deemphasize = [0:15] legs
        //(TxEq[3:0]%3 == 0) : off+
        //
        if (OptParam == OptTxEq) {
          if (UlxUlt) {
            //
            // Update setting for 2 segments (ULX/ULT), range up to 10 legs vs. 3 segments (DT/Halo), range up to 15 legs
            // Map setting [0..10] to [0..15] range while skipping settings that are not used
            //
            TempOff = Off + (Off - 1) / 2;
          } else {
            TempOff = Off;
          }
          if (TempOff > 15) {
            TempOff = 15;
          }

          if (TempOff < 0) {
            TempOff = 0;
          }
          //
          // 15 Emphasize legs (not trained)
          //
          OffCode = TempOff | TXEQFULLDRV;
          //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel=%d,Rank= %d update to %x \n",Channel,Rank,OffCode);
          UpdateTxT (MrcData, Channel, Rank, Byte, 2, OffCode);
          if (UpdateHost) {
            ChannelOut->TxEq[Rank][Byte] = (INT8) OffCode;
          }
        }
        //
        // RxEQ[4:1] CR Decoding (pF/kOhm) SKL
        //            [2:1]
        //  [4:3]     0        1        2        3
        //     0      0.5/.15  0.5/0.25  0.5/0.5  0.5/1.0
        //     1      1.0/.15  1.0/0.25  1.0/0.5  1.0/1.0
        //     2      1.5/.15  1.5/0.25  1.5/0.5  1.5/1.0
        //     3      2.0/.15  2.0/0.25  2.0/0.5  2.0/1.0
        // [0] = CTLE Enabled with 20 Ohm bypass resistor.
        // Sweep = 0-16        if Sweep == 0, all bits [4:0] are 0
        //         all other Sweep values  [4:3] = ((Sweep-1)/4)  [2:0] = ((Sweep-1)%4)
        //
        if (OptParam == OptRxEq) {
          Value = 0;
          if (Off <= 0) {
            Value = 0;
          } else {
            if (Off > 16) {
              Off = 16;
            }
            Value = (UINT8) ((((Off - 1) / 4) << 3) + (((Off - 1) % 4) << 1) + 1);
          }

          UpdateRxT (MrcData, Channel, Rank, Byte, 2, Value);
          if (UpdateHost) {
            ChannelOut->RxEq[Rank][Byte] = Value;
          }
        }

        if (OptParam == OptDefault) {
          UpdateTxT (MrcData, Channel, Rank, Byte, 0xff, 0);
          UpdateRxT (MrcData, Channel, Rank, Byte, 0xff, 0);
        }
      }
    }
  }
  //
  // RxCb Amplifier BIAS
  //
  if ((OptParam == OptRxCb) || (OptParam == OptDefault)) {
    if (Off > 7) {
      Off = 7;
    }

    if (Off < 0) {
      Off = 0;
    }

    DdrCrDataControl2.Data = IntChannelOut->DqControl2[Byte].Data;
    if (OptParam == OptRxCb) {
      DdrCrDataControl2.Bits.Cben = Off;
    }

    Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
    MrcWriteCR (MrcData, Offset, DdrCrDataControl2.Data);
    if (UpdateHost) {
      IntChannelOut->DqControl2[Byte].Data = DdrCrDataControl2.Data;
      //
      DdrCrCompCtl2.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL2_REG);
      Offset = 0;
      for (Value = 0; Value < Outputs->SdramCount; Value++) {
        Offset += (UINT8) IntChannelOut->DqControl2[Value].Bits.Cben;
      }
      DdrCrCompCtl2.Bits.Cben = Offset / Outputs->SdramCount;
      MrcWriteCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL2_REG, DdrCrCompCtl2.Data);
      //
    }
  }
  //
  // CMD Comp Settings
  //
  if (OptParam == OptCmdSComp) {
    // For Cmd Slew Rate the Off is assumed to be the number of stages desired
    // 1. Convert CMD Slew Rate stages to Vref value
    SlewRateVref = CmdSlewRateStagesToVref (MrcData, (UINT8) Off);
    // 2. Program the CMD Slew Rate Vref value (Maximal allowed Cell Delay is 14)
    CompCode = (UINT8) UpdateCompGlobalOffset (MrcData, SCompCmd, SlewRateVref, FALSE, UpdateHost);
  }

  if (OptParam == OptCmdWrDS) {
    CompCode = (UINT8) UpdateCompGlobalOffset (MrcData, WrDSCmd, MrcSE ((UINT8) Off, 4, 8), FALSE, UpdateHost);
  }

  if (OptParam == OptCmdTxEq) {
    // Set CmdN TxEq
    Offset = DDRCMDNCH0_CR_DDRCRCMDCONTROLS_REG +
      ((DDRCMDNCH1_CR_DDRCRCMDCONTROLS_REG - DDRCMDNCH0_CR_DDRCRCMDCONTROLS_REG) * Channel);
    DdrCrCmdControls.Data = MrcReadCR (MrcData, Offset);
    DdrCrCmdControls.Bits.CmdTxEq = Off;
    MrcWriteCR (MrcData, Offset, DdrCrCmdControls.Data);
    // Set CmdS TxEq
    Offset = DDRCMDSCH0_CR_DDRCRCMDCONTROLS_REG +
      ((DDRCMDSCH1_CR_DDRCRCMDCONTROLS_REG - DDRCMDSCH0_CR_DDRCRCMDCONTROLS_REG) * Channel);
    DdrCrCmdControls.Data = MrcReadCR (MrcData, Offset);
    DdrCrCmdControls.Bits.CmdTxEq = Off;
    MrcWriteCR (MrcData, Offset, DdrCrCmdControls.Data);
  }
  //
  // RX Amplifier BIAS
  //
  if ((OptParam == OptRxBias) || (OptParam == OptDefault)) {
    if (Off > 15) {
      Off = 15;
    }

    if (Off < 0) {
      Off = 0;
    }
    //
    // Mapping SKL: [0: 0.125, 1: 0.25, 2: 0.375, 3: 0.5, 4: 0.625, 5: 0.75, 6: 0.875, 7: 1.0]
    //              [8: 1.125, 9: 1.25, 10: 1.375, 11: 1.5, 12: 1.625, 13: 1.75, 14: 1.875, 15: 2.0]
    //
    DdrCrDataControl1.Data = IntChannelOut->DqControl1[Byte].Data;
    if (OptParam == OptRxBias) {
      DdrCrDataControl1.Bits.RxBiasCtl = Off;
    }

    Offset = MrcGetOffsetDataControl1 (MrcData, Channel, Byte);
    MrcWriteCR (MrcData, Offset, DdrCrDataControl1.Data);
    if (UpdateHost) {
      IntChannelOut->DqControl1[Byte].Data = DdrCrDataControl1.Data;
    }
  }
  //
  // Update Dimm Ron value
  //
  if (OptParam == OptDimmRon) {
    //
    // Check if LPDDR3 memory is used
    //
    if (Lpddr) {
      DimmRonMask = (UINT16) ~(MRC_BIT3 | MRC_BIT2 | MRC_BIT1 | MRC_BIT0);
      Index       = (UINT8) Off;
      Index       = MIN (Index, ARRAY_COUNT (LpddrRonEnc) - 1);
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        RankMask = MRC_BIT0 << Rank;
        if ((MrcRankInChannelExist (MrcData, Rank, Channel)) && (Ranks & RankMask)) {
          MrReg = &ChannelOut->Dimm[Rank / 2].Rank[ (Rank % 2) ].MR[mrMR0];
          //
          // Program Dimm Ron
          //
          DimmRon = LpddrRonEnc[Index];
          MRValue = (MrReg[mrMR3] & DimmRonMask) | DimmRon;
          Status = MrcIssueMrw (
                     MrcData,
                     Channel,
                     Rank,
                     mrMR3,
                     MRValue,
                     FALSE,  // InitMrw
                     FALSE,  // ChipSelect2N
                     FALSE   // DebugPrint
                     );
          if (UpdateHost) {
            MrReg[mrMR3] = MRValue;
          }
        }
      }
    } else {
      Index       = (UINT8) Off;
      Index       = MIN (Index, 1);
#if (SUPPORT_DDR4 == SUPPORT)
      if (Ddr4) {
        //
        // DIMM Ron Encoding   D.I.C.[A2,A1]
        //
        DimmRonMask = (UINT16) ~(MRC_BIT2 | MRC_BIT1);
        DimmRon = RttDimmRonEncodingDDR4Const[Index];
      } else
#endif // SUPPORT_DDR4
      {
        //
        // DIMM Ron Encoding   D.I.C.[A5,A1]
        //
        DimmRonMask = (UINT16) ~(MRC_BIT5 | MRC_BIT1);
        DimmRon = RttDimmRonEncodingDDR3Const[Index];
      }
      //
      // can be 0 or 1
      //
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        RankMask = MRC_BIT0 << Rank;
        if ((MrcRankInChannelExist (MrcData, Rank, Channel)) && (Ranks & RankMask)) {
          MrReg = &ChannelOut->Dimm[Rank / 2].Rank[ (Rank % 2) ].MR[mrMR0];
          //
          // Program Dimm Ron
          //
          MRValue = (MrReg[mrMR1] & DimmRonMask) | DimmRon;
          Status  = MrcWriteMRS (MrcData, Channel, RankMask, mrMR1, MRValue);
          if (UpdateHost) {
            MrReg[mrMR1] = MRValue;
          }
        }
      }
    }
  }
  //
  // DIMM ODT Values
  //
  if ((OptParam == OptDimmOdtParkNT) || (OptParam == OptDimmOdtNomNT)) {
    Ranks = DIMM_TO_RANK_MASK (MrcGetOtherDimm (MrcData, Channel, Ranks));
    if (OptParam == OptDimmOdtNomNT) {
      OptParam = OptDimmOdtNom;
    } else {
      OptParam = OptDimmOdtPark;
    }
  }

  if ((OptParam >= OptDimmOdt) && (OptParam <= OptDimmOdtPark)) {
    if (Lpddr) {
      if (OptParam != OptDimmOdtWr) {  // We have only Odt write
        return;
      }
      RttWrMask = (UINT16) ~(MRC_BIT1 | MRC_BIT0);
      Index     = (UINT8) Off;
      Index     = MIN (Index, ARRAY_COUNT (LpddrOdtEnc) - 1);
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        RankMask = MRC_BIT0 << Rank;
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        if ((0 == Rank) && (RankMask & (1 << Rank))) {  // Enable LP3 DIMM ODT on Rank0 only
          MrReg   = &ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR11;
          MRValue = *MrReg;
          //
          // Program DIMM ODT
          //
          RttWr   = LpddrOdtEnc[Index];
          MRValue = (MRValue & RttWrMask) | RttWr;
          Status = MrcIssueMrw (
                     MrcData,
                     Channel,
                     Rank,
                     mrMR11,
                     MRValue,
                     FALSE,  // InitMrw
                     FALSE,  // ChipSelect2N
                     FALSE   // DebugPrint
                     );
          if (UpdateHost) {
            *MrReg = MRValue;
          }
        }
      } // for Rank

      return;
    } // if LPDDR3
    if (Ddr4) {
      //
      // DIMM ODT Encoding   RttNom[A10,A9,A8]   RttWr[A10, A9]
      //
      RttNomMask  = (UINT16) ~(MRC_BIT10 | MRC_BIT9 | MRC_BIT8);
      RttNomShift = 8;
      RttNomMax   = ARRAY_COUNT (DDR4RttNomMRSEncodingConst) - 1;
      MrAddress = mrMR1;
      if (OptParam == OptDimmOdtPark) {
        RttNomShift = 6;
        RttNomMask = (UINT16) ~(MRC_BIT8 | MRC_BIT7 | MRC_BIT6);
        MrAddress = mrMR5;
      }

      RttWrMax    = ARRAY_COUNT (RttWrMRSEncodingDDR4Const) - 1;
      RttWrMask   = (UINT16) ~(MRC_BIT11 | MRC_BIT10 | MRC_BIT9);
      pRttWrEncoding = DDR4RttWrMRSEncoding;
    } else {
      if (OptParam == OptDimmOdtPark) {
        return;
      }
      //
      // DDR3
      // DIMM ODT Encoding   RttNom[A9,A6,A2]   RttWr[A10, A9]
      //
      RttNomMask  = (UINT16) ~(MRC_BIT9 | MRC_BIT6 | MRC_BIT2);
      RttNomShift = 2;
      RttNomMax   = ARRAY_COUNT (RttNomMRSEncodingConst) - 1;
      RttWrMax    = ARRAY_COUNT (RttWrMRSEncodingConst) - 1;
      RttWrMask   = (UINT16) ~(MRC_BIT10 | MRC_BIT9);
      pRttWrEncoding = RttWrMRSEncoding;
      MrAddress = mrMR1;
    }

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      RankMask = MRC_BIT0 << Rank;
      if ((MrcRankInChannelExist (MrcData, Rank, Channel)) && (Ranks & RankMask)) {
        MrReg = &ChannelOut->Dimm[Rank / 2].Rank[ (Rank % 2) ].MR[mrMR0];

        if ((OptParam == OptDimmOdtWr) || (OptParam == OptDimmOdt)) {
          //
          // Program RTT WR
          //
          Index   = (UINT8) ((OptParam == OptDimmOdt) ? (Off >> 4) : Off);
          Index   = MIN (Index, RttWrMax);
          RttWr   = pRttWrEncoding[Index] << 9;
          MRValue = (MrReg[mrMR2] & RttWrMask) | RttWr;
          Status  = MrcWriteMRS (MrcData, Channel, RankMask, mrMR2, MRValue);
          if (UpdateHost) {
            MrReg[mrMR2] = MRValue;
          }
        }
        //
        // Program RTT NOM
        //
        if (OptParam == OptDimmOdtWr) {
          continue;
        }

        Index = ((UINT8) Off & 0xF);
        Index = MIN (Index, RttNomMax);

        if (Ddr4) {
          RttNom  = DDR4RttNomMRSEncoding[Index]; // same for park
        } else {
          RttNom  = RttNomMRSEncoding[Index];
        }
        RttNom  = RttNom << RttNomShift;
        MRValue = (MrReg[MrAddress] & RttNomMask) | RttNom;
        Status  = MrcWriteMRS (MrcData, Channel, RankMask, MrAddress, MRValue);
        if (UpdateHost) {
          MrReg[MrAddress] = MRValue;
        }
      }
    }
  }

  return;
}

/**
  Slightly penalize any Asymmetry in margin

  @param[in] NegEdge - Negative edge of the margin
  @param[in] PosEdge - Positive edge of the margin

  @retval p2p - Width/Height reduced by the asymmetric difference in margin.
**/
UINT16
EffectiveMargin (
  IN const UINT16 NegEdge,
  IN const UINT16 PosEdge
  )
{
  INT16 p2p;
  UINT16 p2pDiff;

  p2p     = 2 * (PosEdge + NegEdge);
  p2pDiff = PosEdge - NegEdge;

  if (PosEdge > NegEdge) {
    p2p -= p2pDiff;
  } else {
    p2p += p2pDiff;
  }

  return p2p / 2;
}

/**
  This function does a running average on Margins in two dimentional fashion.

  @param[in,out] Margins - Margins to average in a 1D array.
  @param[in]     MLen    - Determines the Y-Dimension lengths
  @param[in]     XDim    - Determines the X-Dimension lengths
  @param[in]     XMin    - Used to skip the first elements in the Margin when averaging.
  @param[in]     CScale  - Used to place more weight on the center point.

  @retval Nothing
**/
void
RunningAverage2D (
  IN OUT UINT16       Margins[MAX_OPT_POINTS],
  IN     const UINT8  MLen,
  IN     const UINT8  XDim,
  IN     const UINT8  XMin,
  IN     const UINT8  CScale
  )
{
  UINT8  XMax;
  UINT8  YMax;
  UINT16 TMargins[MAX_OPT_POINTS];
  UINT8  i;
  UINT8  x;
  UINT8  y;
  UINT8  xo;
  UINT8  yo;
  UINT8  XOff;
  INT8   YOff;

  if (MLen == 1) {
    return;
  }
  XMax  = XDim - 1;
  YMax  = ((MLen + XDim - 1) / XDim) - 1; // Ceiling to int in case the matrix is not fully populated

  for (i = 0; i < MLen; i++) {
    x = (i % XDim);
    y = (i / XDim);

    //
    // Center Point
    //
    TMargins[i] = Margins[i] * (CScale - 1); // Also add margin at the centerpoint below
    //
    // Sum up surrounding results
    //
    for (xo = 0; xo < 3; xo++) {
      XOff = x + xo - 1;
      //
      // Avoid negative numbers on XOff
      //
      if ((x == 0) && (xo == 0)) {
        XOff = 0;
      }
      //
      // (x < XMin) allows averaging across points (1;0) and (2;0)
      //
      if ((XOff < XMin) && (x < XMin)) {
        XOff = x; // RxEq special case.  Skip averaging on Col0/Col1
      }

      if (XOff > XMax) {
        XOff = XMax;
      }

      for (yo = 0; yo < 3; yo++) {
        YOff = y + yo - 1;
        if (YOff < 0) {
          YOff = 0;
        }

        if (YOff > YMax) {
          YOff = YMax;
        }
        //
        // Avoid averaging with unpopulated matrix elements when dealing with partially populated matrices
        //
        if ((XDim * YOff + XOff) > (MLen - 1)) {
          YOff = YOff - 1;
        }

        TMargins[i] += Margins[XDim * YOff + XOff];
      }
    }
  }
  //
  // Copy TempMargins back over to real margins
  //
  for (i = 0; i < MLen; i++) {
    Margins[i] = TMargins[i] / (8 + CScale); // Added div to maintain margin scaling
  }

  return;
}

/**
  This function does a running average on Margins in two dimentional fashion.

  @param[in,out] Margins - Margins to average
  @param[in]     Test    - Selects the Margins to average
  @param[in]     MLen    - Determines the Y-Dimension lengths
  @param[in]     XDim    - Determines the X-Dimension lengths
  @param[in]     XMin    - Used to skip the first elements in the Margin when averaging.
  @param[in]     CScale  - Used to place more weight on the center point.

  @retval Nothing
**/
void
Fill2DAverage (
  IN     MrcParameters *const MrcData,
  IN OUT UINT16               Margins[2][MAX_OPT_POINTS],
  IN     const UINT8          Test,
  IN     const UINT8          MLen,
  IN     const UINT8          XDim,
  IN     const UINT8          XMin,
  IN     const UINT8          CScale
  )
{
  UINT8  XMax;
  UINT8  YMax;
  UINT16 TMargins[MAX_OPT_POINTS];
  UINT8  i;
  UINT8  x;
  UINT8  y;
  UINT8  xo;
  UINT8  yo;
  UINT8  XOff;
  INT8   YOff;
  UINT8  Edge;
  INT16  Gradient;
  INT16  MaxGradient;
  MrcDebug *Debug;
  Debug = &MrcData->Outputs.Debug;

  XMax  = XDim - 1;
  YMax  = ((MLen + XDim - 1) / XDim) - 1; // Ceiling to int in case the matrix is not fully populated

  for (i = 0; i < MLen; i++) {
    if (Margins[Test][i]) { // skip already populated entries
      continue;
    }

    x = (i % XDim);
    y = (i / XDim);
    Edge = 0;

    //     if (i == 14)
    //       MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d Margins[%d][%d]=%d\n", x, y, Test, i, Margins[Test][i]);

    //
    // Center Point
    //
    TMargins[i] = Margins[Test][i] * (CScale - 1); // Also add margin at the centerpoint below
    //
    // Sum up surrounding results
    //
    for (xo = 0; xo < 3; xo += 2) {
      XOff = x + xo - 1;
      //
      // Avoid negative numbers on XOff
      //
      if (((INT8) XOff) < 0) {
        //XOff = 0;
        Edge++;
        continue;
      }
      //
      // (x < XMin) allows averaging across points (1;0) and (2;0)
      //
      if ((XOff < XMin) && (x < XMin)) {
        XOff = x; // RxEq special case.  Skip averaging on Col0/Col1
      }

      if (XOff > XMax) {
        //XOff = XMax;
        Edge++;
        continue;
      }
      //
      // Avoid averaging with unpopulated matrix elements when dealing with partially populated matrices
      //
      if ((XDim * y + XOff) > (MLen - 1)) {
        Edge++;
        continue;
      }
      TMargins[i] += Margins[Test][XDim * y + XOff];
      //       if (i == 14)
      //         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d TMargins[%d]=%d Edge=%d\n", x, y, i, TMargins[i],Edge);
    }
    for (yo = 0; yo < 3; yo += 2) {
      YOff = y + yo - 1;
      if (YOff < 0) {
        // YOff = 0;
        Edge++;
        continue;
      }

      if (YOff > YMax) {
        // YOff = YMax;
        Edge++;
        continue;
      }

      TMargins[i] += Margins[Test][XDim * YOff + x];
      //       if (i == 14)
      //         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d TMargins[%d]=%d Edge=%d\n", x, y, i, TMargins[i],Edge);
    }
    //
    // Copy TempMargins back over to real margins
    //
    //     if (Edge > 0) {
    //       Margins[Test][i] = Margins[Test][i] * 8 / 10; // Penalize the edges by decreaseing margin by 20%
    //     }
    Margins[Test][i] = TMargins[i] / (4 - Edge + CScale - 1); // Added div to maintain margin scaling
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d TMargins[%d]=%d Margins[%d][i]=%d Edge=%d\n", x, y, i, TMargins[i], Test, Margins[Test][i], Edge);
  }

  //
  // penalize for high margin gradient
  //
  for (i = 0; i < MLen; i++) {
    x = (i % XDim);
    y = (i / XDim);
    MaxGradient = 0;
    //
    // Sum up surrounding results
    //
    for (xo = 0; xo < 3; xo += 2) {
      XOff = x + xo - 1;
      //
      // Avoid negative numbers on XOff
      //
      if ((x == 0) && (xo == 0)) {
        XOff = 0;
      }
      if (XOff > XMax) {
        XOff = XMax;
      }
      //
      // Avoid averaging with unpopulated matrix elements when dealing with partially populated matrices
      //
      if ((XDim * y + XOff) > (MLen - 1)) {
        XOff = XOff - 1;
      }
      Gradient = Margins[Test][XDim * y + x] - Margins[Test][XDim * y + XOff];
      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d Gradient=%d Margins[Test][XDim * y + x] = %d Margins[Test][XDim * y + XOff] = %d XOff = %d\n",x, y, Gradient, Margins[Test][XDim * y + x], Margins[Test][XDim * y + XOff], XOff);
      if (Gradient > MaxGradient) {
        // if we loose margin update MaxGradient
        MaxGradient = Gradient;
      }
    }
    for (yo = 0; yo < 3; yo += 2) {
      YOff = y + yo - 1;
      if (YOff < 0) {
        YOff = 0;
      }

      if (YOff > YMax) {
        YOff = YMax;
      }

      //
      // Avoid averaging with unpopulated matrix elements when dealing with partially populated matrices
      //
      if ((XDim * YOff + x) > (MLen - 1)) {
        YOff = YOff - 1;
      }

      Gradient = (Margins[Test][XDim * y + x] - Margins[Test][XDim * YOff + x]);
      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d Gradient=%d Margins[Test][XDim * y + x] = %d Margins[Test][XDim * y + XOff] = %d YOff = %d\n",x, y, Gradient, Margins[Test][XDim * y + x], Margins[Test][XDim * y + YOff], YOff);
      if (Gradient > MaxGradient) {
        MaxGradient = Gradient;
      }
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d TMargins[%d]=%d Edge=%d\n", x, y, i, TMargins[i],Edge);
    }
    //
    // save MaxGradient in Temp array and clip for max margin.
    //
    if (MaxGradient > Margins[Test][i]) {
      MaxGradient = Margins[Test][i];
    }
    TMargins[i] = MaxGradient;
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d  Margins[%d][%d]=%d MaxGradient=%d \n", x, y, i, Test, Margins[Test][i], TMargins[i]);
  }
  // apply the MaxGradient to Original array
  for (i = 0; i < MLen; i++) {
    Margins[Test][i] -= TMargins[i];
  }
  return;
}


/**
  This function approximates a non linear heaviside function using 5 linear curves.
  The curves are defind by 3 paramters:
  a - The curve's slope
  b - Intercept with y axis.
  x_max - The maximal x value to which curve paramters apply. i.e., for x < x1 a = a1, b = b1.
  It should select a balanced wr/rd operating point with respect to UPM

  @param[in]     MrcCall          - FindOptimalTradeOff function , Inputs->Call.Func variable;
  @param[in]     PostMar            Margins array after training
  @param[in]     GoodPwrLimitPost   UPM limits for margins

  @Retval  linear approximation function output
**/
UINT64
LinearApproximationTradeOff(
  IN const MRC_FUNCTION * MrcCall,
  IN UINT32   PostMar,
  IN UINT16   GoodPwrLimitPost
  )
{
  UINT64  LocalResult;

  static const UINT32  a[]     = {  10,   50,   200,   50,    10,    1};
  static const INT32   b[]     = {   0, -100, -1225,  650,  1450, 1810};
  static const UINT32  x_max[] = { 250,  750,  1250, 2000,  4000, 0xFFFFFFFF };
  UINT32  a_LocalResult;
  INT32   b_LocalResult;
  UINT32  x_ind;

  //Five Linear approximation optimization function value, y1=a1x+b1, 1000*y1=1000*a1*(LocalResult/UPM)+1000*b1, 1000*y1 = a1*((LocalResults*1000)/UPM)+1000*b1
  LocalResult = MrcCall->MrcDivU64x64(MrcCall->MrcMultU64x32(PostMar, 1000), GoodPwrLimitPost, NULL);//UPM normalized with three digits after zero

  b_LocalResult = 0;
  a_LocalResult = 0;
  for (x_ind = 0; x_ind < ARRAY_COUNT(x_max) ; x_ind++) {
    if (LocalResult <= x_max[x_ind]) {
      a_LocalResult = a[x_ind];
      b_LocalResult = b[x_ind];
      break;
    }
  }

  return (MrcCall->MrcDivU64x64(MrcCall->MrcMultU64x32(LocalResult, a_LocalResult), 100, NULL) + b_LocalResult);//two digits after decimal point
}

/**
  This function takes in 2D array of Margins: MarginType / Parameter Index.
  This index to the array represents some arbitrary parameter value that we are optimizing.
  The function will look for up to MAX_TRADEOFF_TYPES entries to optimize on.
  OptResultByte will store the results of the optimization, and various other data.

  In addition to optimizing for margin, this function can also optimize for power.
  GoodPowerLimit is an array that sets level where power is more important than margin.
    i.e. Any points where ((Margin[0]>GoodPowerLimit[0]) & (Margin[1]>GoodPowerLimit[1]) & ... )
  To avoid overflow, this function will automatic scale margins to fit in UINT64

  @param[in]     MrcData          - The global MRC data structure.
  @param[in,out] OptResultByte    - Structure containing the optimized results.
  @param[in]     InputMargins     - Margins we are optimizing
  @param[in]     MarginsLength    - The length of InputMargins
  @param[in]     LenMargin        - The length of InputMargins we are optimizing (0 - LenMargin -1).
  @param[in]     Scale            - Controls the relative importance on Margins[0] vs. [1] ...
                                      ex: To make Margins[0] twice as important, set Scale = [1, 2, 2, 2, 2].
                                      Since the search optimizes the lowest margin, increasing [1:4] makes 0 more important.
                                      This function can be used to optimize only Margin[0] by setting Scale = [1, 0, 0, 0, 0].
  @param[in]     UPMOptimize      - Optimize only for UPM limit for selected params, so if they pass UPM they do not affect the score.
  @param[in]     EnSq             - Enables the square root term in the optimization functions to make the tradeoff steeper.
  @param[in]     AveN             - The number of points used for the averaging filter.
  @param[in]     IncEnds          - Controls if the endpoints are to be included.
  @param[in]     ScaleM           - Controls the scaling of the middle point in 1-D average filter.
  @param[in]     GoodPowerLimit   - The power limit above which we only trade-off for power and not margin.
  @param[in]     OptimizationMode - 0:    Returns first good margin limit point.
                                    1-4:  Return the first index that meets GoodPowerLimit and lowest power.
                                            OptimizationMode is power column index.
                                    5-99: Return the index that meets GoodPowerLimit and >= % of the Max Optimization result.
                                    >100: Returns the highest Optimization Result.
  @param[in]     GuardBand        - Signed offest to check if margin drop is acceptable.  Save good guardband
                                    in OptResultByte.
  @param[in]     EnableLinearApproximationOptimizationMode.....If TRUE then If(OptimizationMode == 100) && DDR4 then Heaviside approximate function
                                                               optimization mode will be used.  Else Legacy optimization will be used.

  @retval Nothing.
**/
void
FindOptimalTradeOff (
  IN     MrcParameters      *const  MrcData,
  IN OUT OptResultsPerByte          *OptResultByte,
  IN     UINT16                     *InputMargins,
  IN     UINT8                      MarginsLength,
  IN     UINT8                      LenMargin,
  IN     const UINT8                Scale[MAX_TRADEOFF_TYPES],
  IN     const UINT8                UPMOptimize[MAX_TRADEOFF_TYPES],
  IN     UINT8                      EnSq,
  IN     UINT8                      AveN,
  IN     UINT8                      IncEnds,
  IN     UINT8                      ScaleM,
  IN     UINT16                     GoodPowerLimit[],
  IN     UINT8                      OptimizationMode,
  IN     INT8                       GuardBand,
  IN     BOOLEAN                    EnableLinearApproximationOptimizationMode
  )
{
  const MrcInput      *Inputs;
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  UINT32               PostMar[MAX_TRADEOFF_TYPES][MAX_OPT_POINTS];
  UINT32               SMaxPost[MAX_TRADEOFF_TYPES];
  UINT32               MaxPost[MAX_TRADEOFF_TYPES];
  UINT32               MinPost[MAX_TRADEOFF_TYPES];
  UINT16               GoodPwrLimitPost[MAX_TRADEOFF_TYPES];
  UINT32               ScaleMin;
  UINT8                Nby2;
  UINT8                EqOrder;
  UINT8                MarginArray;
  UINT8                yArr;
  UINT8                x;
  UINT8                i;
  UINT8                Off;
  INT16                xEff;
  UINT8                NumBits;
  UINT32               localY;
  UINT8                Shift;
  UINT8                Adder;
  UINT8                Start;
  UINT8                Stop;
  UINT64               Result;
  UINT64               LocalResult;
  UINT64               MaxR;
  UINT64               MarginLimit;
  UINT8                BestX;
  UINT8                PowerX;
  UINT8                FoundPwrOpt;
  UINT8                NumCalcArr;
  INT8                 StepSize;
  UINT8                MarginDropPercent;
  UINT32               MinPost1;
  BOOLEAN              GoodPower;
  BOOLEAN              MarginTrainingLegacyTradeOff;

  Outputs           = &MrcData->Outputs;
  Inputs            = &MrcData->Inputs;
  MrcCall           = Inputs->Call.Func;
  Debug             = &MrcData->Outputs.Debug;
  MarginDropPercent = 10;  // 10% loss of margin is a bad guardband offset.
  EqOrder           = 0; // Is the optimization equation: X^1, X^2, X^5
  Result            = 0;
  MaxR              = 0;
  BestX             = 0;
  PowerX            = 0;
  FoundPwrOpt       = 0;

  //This is the default optimization method, Only in Margin training,optimization = 100,DDR4 mode we support new MarginTraining mode
  MarginTrainingLegacyTradeOff = ((TRUE == EnableLinearApproximationOptimizationMode)
                                  && (MRC_DDR_TYPE_DDR4 == Outputs->DdrType)
                                  && (100 == OptimizationMode)) ? FALSE : TRUE;

  MrcCall->MrcSetMemDword (MaxPost, sizeof (MaxPost) / sizeof (UINT32), 1);
  MrcCall->MrcSetMemDword (SMaxPost, sizeof (SMaxPost) / sizeof (UINT32), 1);
  MrcCall->MrcSetMemDword (MinPost, sizeof (MinPost) / sizeof (UINT32), 0xFFFFFFFF);
  MrcCall->MrcSetMemWord (GoodPwrLimitPost, sizeof (GoodPwrLimitPost) / sizeof (UINT16), 0);
  MrcCall->MrcSetMem ((UINT8 *) PostMar, sizeof (PostMar), 0);
  MrcCall->MrcSetMem ((UINT8 *) OptResultByte, sizeof (OptResultsPerByte), 0);

  if (AveN <= 0) {
    AveN = 1;
  }
  Nby2    = (AveN >> 1);

  //
  // Process Raw Margins Results with a running average filter of AveN
  //
  for (MarginArray = 0; MarginArray < MAX_TRADEOFF_TYPES; MarginArray++) {
    //
    // Scale GoodPowerLimit to match PostMar results
    //
    GoodPwrLimitPost[MarginArray] = GoodPowerLimit[MarginArray] * (AveN + ScaleM - 1) * Scale[MarginArray];

    for (x = 0; x < LenMargin; x++) {
      if (Scale[MarginArray] == 0) {
        //
        // Not in the game
        //
        MinPost[MarginArray] = PostMar[MarginArray][x] = 1;
      } else {
        if (x == 0) {
          //
          // Update EqOrder once for each MarginArray value with a non-zero scale factor.
          //   e.g.:so for {RdT,RdV,0,0} it will be = 2
          //
          EqOrder += 1;
        }

        for (Off = 0; Off < AveN; Off++) {
          xEff = x + Off - Nby2;
          if (xEff < 0) {
            PostMar[MarginArray][x] += *(InputMargins + MarginArray * MarginsLength + 0);  // InputMargins[MarginArray][0];
          } else if (xEff >= LenMargin) {
            PostMar[MarginArray][x] += *(InputMargins + MarginArray * MarginsLength + LenMargin - 1);
          } else if (x == xEff) {
            PostMar[MarginArray][x] += ScaleM * *(InputMargins + MarginArray * MarginsLength + xEff);
          } else {
            PostMar[MarginArray][x] += *(InputMargins + MarginArray * MarginsLength + xEff);
          }
        }
        // save none scaled margins after avg filtering
        OptResultByte->Margins[MarginArray][x].EW = (UINT16) PostMar[MarginArray][x] / (AveN + ScaleM - 1);
        PostMar[MarginArray][x] *= Scale[MarginArray];
        if (MaxPost[MarginArray] < PostMar[MarginArray][x]) {
          MaxPost[MarginArray] = PostMar[MarginArray][x];
        }

        if (MinPost[MarginArray] > PostMar[MarginArray][x]) {
          MinPost[MarginArray] = PostMar[MarginArray][x];
        }
      }
    }

    if (Scale[MarginArray] == 0) {
      continue;
    }

    SMaxPost[MarginArray]               = MaxPost[MarginArray];
    OptResultByte->Scale[MarginArray]   = Scale[MarginArray];
    OptResultByte->MaxPost[MarginArray] = MaxPost[MarginArray] / (AveN + ScaleM - 1);
    OptResultByte->MinPost[MarginArray] = MinPost[MarginArray] / (AveN + ScaleM - 1);
  }
  //
  // Sort Array
  //
  MrcBsort (SMaxPost, MAX_TRADEOFF_TYPES);
  //
  // Calculate Number of Bits Required to represent this number. Make sure to handle care of EnSq
  //
  NumBits = 0;

  for (MarginArray = 0; MarginArray < MAX_TRADEOFF_TYPES; MarginArray++) {
    if (MarginArray < (MAX_TRADEOFF_TYPES - 1)) {
      //
      // if EnSq we do Max^2 so the num get twice the bits...
      //
      localY = SMaxPost[MarginArray];
      if (EnSq) {
        localY = (localY * localY);
      }

      NumBits += MrcLog2 (localY);
    } else {
      NumBits += MrcLog2 (SMaxPost[MarginArray]);
    }
  }

  NumBits += 11; // reserved another 10 bits for division in order to format for printing ; 3 for adding - up to 8
  //
  // EqOrder for square terms
  //
  if (EnSq) {
    EqOrder = (EqOrder + (EqOrder - 1));
  }
  //
  // Handle Potential Saturation
  //
  if (NumBits > 64) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Warning number of bits exceeds 64 bit : %d \n", NumBits);
    //
    // Shift all numbers to reduce final result to be less than 32 bits.  Round Up
    //
    Shift = (NumBits - 64 + EqOrder - 1) / EqOrder;
    //
    // RoundUp Adder
    //
    Adder = (1 << (Shift - 1));
    //
    // Divide by (1<<Shift) and Round Up
    //
    for (MarginArray = 0; MarginArray < MAX_TRADEOFF_TYPES; MarginArray++) {
      MaxPost[MarginArray]       = (MaxPost[MarginArray] + Adder) >> Shift;
      GoodPwrLimitPost[MarginArray]  = (GoodPwrLimitPost[MarginArray] + Adder) >> Shift;
      for (x = 0; x < LenMargin; x++) {
        PostMar[MarginArray][x] = (PostMar[MarginArray][x] + Adder) >> Shift;
      }
    }
  }
  //
  // Calculate Square terms:
  //
  if (EnSq) {
    for (MarginArray = 0; MarginArray < MAX_TRADEOFF_TYPES; MarginArray++) {
      MaxPost[MarginArray] = MaxPost[MarginArray] * MaxPost[MarginArray];
    }
  }
  //
  // Set Limits for Search
  //
  Start = 0;
  Stop  = LenMargin;
  if ((IncEnds == 0) && (LenMargin > AveN)) {
    if (Nby2 > 0) {
      Start++;
      Stop--;
    }
  }
  if (UPMOptimize != NULL) {
    for (x = Start; x < Stop; x++) {
      for (MarginArray = 0; MarginArray < MAX_TRADEOFF_TYPES; MarginArray++) {
        if (UPMOptimize[MarginArray] == 0) {
          continue; // not need to calculate those
        }
        if (PostMar[MarginArray][x] > GoodPwrLimitPost[MarginArray]) {
          PostMar[MarginArray][x] = GoodPwrLimitPost[MarginArray];
          OptResultByte->Margins[MarginArray][x].EW = (UINT16) PostMar[MarginArray][x] / (AveN + ScaleM - 1) / Scale[MarginArray];
        }
      }
    }
  }
  //
  // Find Optimal Point from Margin Point of View
  // Combine the points using the formula:
  //   Max0*Max1*Max2*Post3 + Max1*Max2*Max3*Post0 + Max2*Max3*Max0*Post1 +
  //   Max3*Max0*Max1*Post2 + Scale*min(Post0,Post1,Post2,Post3)^EqOrder
  //   Scale = 1 + (10*(SMaxPost[0]-SMaxPost[1]))/SMaxPost[MAX_TRADEOFF_TYPES-1]
  //
  for (x = Start; x < Stop; x++) {
    Result      = 0;
    MinPost1    = 0xFFFFFFFF;
    GoodPower   = TRUE;
    NumCalcArr  = 0;
    for (MarginArray = 0; MarginArray < MAX_TRADEOFF_TYPES; MarginArray++) {
      if (Scale[MarginArray] == 0) {
        continue; // not need to calculate those
      }
      NumCalcArr++; // Count the number of MarginTypes in the optimization function.
      //
      // Find Min of all PostMar at offset x
      // Does this point meet the min power Margin requirements?
      //
      if (Scale[MarginArray] > 0) {
        if (MinPost1 > PostMar[MarginArray][x]) {
          MinPost1 = PostMar[MarginArray][x];
        }

        if (PostMar[MarginArray][x] < GoodPwrLimitPost[MarginArray]) {
          GoodPower = FALSE;
        }
      }
      //
      // Calculate this portion of result
      //
      if (MarginTrainingLegacyTradeOff) {
        LocalResult = 1;
        for (yArr = 0; yArr < MAX_TRADEOFF_TYPES; yArr++) {
          if (Scale[yArr] == 0) {
            continue; // not need to calculate those
          }

          if (MarginArray == yArr) {
            continue;
          } else {
            LocalResult = MrcCall->MrcMultU64x32(LocalResult, MaxPost[yArr]);
          }
        }

        Result += MrcCall->MrcMultU64x32(LocalResult, PostMar[MarginArray][x]);
      } else {
        Result += LinearApproximationTradeOff(MrcCall, PostMar[MarginArray][x], GoodPwrLimitPost[MarginArray]);
      }
    }
    //
    // Add in (MinPost ^ EqOrder)
    // If NumCalcArr is 0, set it to 1 so that it still in the range of array size.
    //  This will cause PowerCalcIndex to underflow.  Set to 1 in this case.
    //
    if (NumCalcArr == 0) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "Error: wrong input parameter caused NumCalcArr = 0 when calling FindOptimalTradeOff()\n"
        );
      NumCalcArr = 1;
    }

    if (MarginTrainingLegacyTradeOff) {
      ScaleMin = 1;
      LocalResult = ScaleMin;
      for (i = 0; i < EqOrder; i++) {
        LocalResult = MrcCall->MrcMultU64x32(LocalResult, MinPost1);
      }

      Result += LocalResult;
    }

    if (Result > MaxR) {
      MaxR  = Result;
      BestX = x; // save first highest function result offset
    }

    OptResultByte->Result[x] = Result;
    //
    // Find Optimal Point from Power Point of View.
    // All the margin types must be >= GoodPowerLimit
    //
    if (GoodPower) {
      if (FoundPwrOpt == 0) {
        FoundPwrOpt = 1;
        PowerX      = x;
      } else {
        //
        // Find the first lowest power point.
        // PostMar[Power] is inverted: higher number is lower power.
        //
        if ((OptimizationMode > 0) && (OptimizationMode < MAX_TRADEOFF_TYPES)) {
          if (PostMar[OptimizationMode][x] > PostMar[OptimizationMode][PowerX]) {
            PowerX = x;
          }
        }
      }
    }
  } // end shmoo offsets
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (MaxR == 0) ? "Warning : MaxR is Zero !!!\n" : "");
  //
  // At this point, BestX will have the highest Margin Result index.  PowerX will have
  // the highest or lowest index that is marked good based on MarginLimits.
  //
  if (FoundPwrOpt) {
    if (OptimizationMode < MAX_TRADEOFF_TYPES) {
      BestX = PowerX;
    } else if (OptimizationMode < 100) {
      for (x = PowerX; x < Stop; x++) {
        Result = (MrcCall->MrcDivU64x64 (MrcCall->MrcMultU64x32 (OptResultByte->Result[x], 100), MaxR, NULL));
        if (Result >= OptimizationMode) {
          BestX = x;
          break;
        }
      }
    }
  }

  OptResultByte->Best     = BestX;
  OptResultByte->MaxR     = MaxR;
  //
  // Apply a guard band to the best setting, clamped at edges of the search.
  //
  if (GuardBand != 0) {
    //
    // Determine step direction and limit to the search edge.
    //
    if (GuardBand < 0) {
      StepSize = 1;
      Off = ((BestX + GuardBand) < Start) ? Start : (BestX + GuardBand);
    } else {
      StepSize = -1;
      Off = ((BestX + GuardBand) >= Stop) ? (Stop - 1) : (BestX + GuardBand);
    }
    //
    // Check each test for margin drop of MarginDropPercent.
    // If any test fails, we step towards the original selection.
    //
    MarginLimit = MrcCall->MrcMultU64x32 (OptResultByte->Result[BestX], (100 - MarginDropPercent));
    MarginLimit = MrcCall->MrcDivU64x64 (MarginLimit, 100, NULL);
    for (; (Off != BestX); Off += StepSize) {
      if (OptResultByte->Result[Off] > MarginLimit) {
        break;
      }
    }

    OptResultByte->GuardBand = Off - (INT8) BestX;
  }

  return;
}

/**
  This function implements Turn Around Timing training.
  Optimize TA ODT Delay and Duration

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it succeeds return mrcSuccess.
**/
MrcStatus
MrcTurnAroundTiming (
  IN MrcParameters *const MrcData
  )
{
  MrcDebug            *Debug;
  const MrcInput      *Inputs;
  MrcOutput           *Outputs;
  MrcIntOutput        *IntOutputs;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcIntChannelOut    *IntChannelOut;
  MrcStatus           Status;
  UINT8               Channel;
  UINT8               RankMaskCh;
  UINT8               RankMask;
  BOOLEAN             RunDD;
  BOOLEAN             RunDR;
  static const UINT8  ParamListX[6]  = {RdV, RdT, WrV, WrT, RcvEnaX, WrLevel};
  static const UINT8  TestListRdX[3] = {RdV, RdT, RcvEnaX};
  static const UINT8  TestListWr[2]  = {WrV, WrT};
  static const INT8   ClkShifts[2]   = {-7, 7};
  INT8                NoShifts[1];
  UINT8               GuardBand;
  UINT8               NomWR2RD_dr;
  UINT8               NomWR2RD_dd;
  UINT8               NomRD2WR_dd;
  UINT8               NomRD2WR_dr;
  UINT8               NomWR2RD_sg;
  UINT8               NomWR2RD_dg;
  UINT8               NomRD2WR_sg;
  UINT8               NomRD2WR_dg;
  UINT8               NomRD2RD_dr;
  UINT8               NomRD2RD_dd;
  UINT8               NomWR2WR_dr;
  UINT8               NomWR2WR_dd;
  UINT8               Update;
  UINT8               LoopCount;
  UINT32              Offset;
  BOOLEAN             Ddr4;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT  *TcRdRd;
  MCHBAR_CH0_CR_TC_RDWR_STRUCT  *TcRdWr;
  MCHBAR_CH0_CR_TC_WRRD_STRUCT  *TcWrRd;
  MCHBAR_CH0_CR_TC_WRWR_STRUCT  *TcWrWr;
  MCHBAR_CH0_CR_SC_PCIT_STRUCT  ScPcit;
  MCHBAR_CH0_CR_SC_PCIT_STRUCT  ScPcitSave[MAX_CHANNEL];

#ifdef MRC_DEBUG_PRINT
  UINT8               i;
  UINT8               PrintValue;
  static const char   *TypeStr[] = {
    "Sg",
    "Dg",
    "Dr",
    "Dd"
  };
  PrintValue = 0;
#endif

  Status        = mrcSuccess;
  RankMaskCh    = 0;
  Update        = 1;
  LoopCount     = 12;
  RunDD         = FALSE;
  RunDR         = FALSE;
  NomWR2RD_dr   = 0;
  NomWR2RD_dd   = 0;
  NomRD2WR_dd   = 0;
  NomRD2WR_dr   = 0;
  NomWR2RD_sg   = 0;
  NomWR2RD_dg   = 0;
  NomRD2WR_sg   = 0;
  NomRD2WR_dg   = 0;
  NomRD2RD_dr   = 0;
  NomRD2RD_dd   = 0;
  NomWR2WR_dr   = 0;
  NomWR2WR_dd   = 0;
  RankMask      = 0xF;
  NoShifts[0]   = 0;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  IntOutputs    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    if (!ChannelOut->ValidRankBitMask) {
      continue;
    }
    IntChannelOut = &IntOutputs->Controller[0].Channel[Channel];

    TcRdRd = &IntChannelOut->MchbarTcRdRd;
    TcRdWr = &IntChannelOut->MchbarTcRdWr;
    TcWrRd = &IntChannelOut->MchbarTcWrRd;
    TcWrWr = &IntChannelOut->MchbarTcWrWr;

    RankMaskCh  = ChannelOut->ValidRankBitMask;
    RunDD       = RunDD || (ChannelOut->DimmCount == 2);
    RunDR       = RunDR || ((RankMaskCh & 0xC) == 0xC) || ((RankMaskCh & 0x3) == 0x3);
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Channel %d: RunDR = 0x%x, RunDD = 0x%x, RankMaskCh = 0x%x\n",
      Channel,
      RunDR,
      RunDD,
      RankMaskCh
      );

    //
    // Use nominal values (previously programmed) +1 and -1 to test.
    //
    // Taking worst case of both channels.
    // Ideally the Cliff routine should support offset per channel or better make the param a real offset (not the abs value)
    //
    NomWR2RD_dr = MAX (NomWR2RD_dr, (UINT8) (TcWrRd->Bits.tWRRD_dr));
    NomWR2RD_dd = MAX (NomWR2RD_dd, (UINT8) (TcWrRd->Bits.tWRRD_dd));
    NomWR2RD_sg = MAX (NomWR2RD_sg, (UINT8) (TcWrRd->Bits.tWRRD_sg));
    NomWR2RD_dg = MAX (NomWR2RD_dg, (UINT8) (TcWrRd->Bits.tWRRD_dg));

    NomRD2WR_dr = MAX (NomRD2WR_dr, (UINT8) (TcRdWr->Bits.tRDWR_dr));
    NomRD2WR_dd = MAX (NomRD2WR_dd, (UINT8) (TcRdWr->Bits.tRDWR_dd));
    NomRD2WR_sg = MAX (NomRD2WR_sg, (UINT8) (TcRdWr->Bits.tRDWR_sg));
    NomRD2WR_dg = MAX (NomRD2WR_dg, (UINT8) (TcRdWr->Bits.tRDWR_dg));

    NomRD2RD_dr = MAX (NomRD2RD_dr, (UINT8) (TcRdRd->Bits.tRDRD_dr));
    NomRD2RD_dd = MAX (NomRD2RD_dd, (UINT8) (TcRdRd->Bits.tRDRD_dd));

    NomWR2WR_dr = MAX (NomWR2WR_dr, (UINT8) (TcWrWr->Bits.tWRWR_dr));
    NomWR2WR_dd = MAX (NomWR2WR_dd, (UINT8) (TcWrWr->Bits.tWRWR_dd));

    //
    // Change PCIT to 0xFF
    // This allows proper tRDWR_dg stress without extra PRE/ACT cycles.
    //
    Offset = MCHBAR_CH0_CR_SC_PCIT_REG + (MCHBAR_CH1_CR_SC_PCIT_REG - MCHBAR_CH0_CR_SC_PCIT_REG) * Channel;
    ScPcit.Data = MrcReadCR (MrcData, Offset);
    ScPcitSave[Channel] = ScPcit;
    ScPcit.Bits.PCIT = 0xFF;
    MrcWriteCR (MrcData, Offset, ScPcit.Data);
  } // for Channel

  //
  // Same DIMM turnarounds
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s WR2RD_SG\n", "\n ##### Running");
  Status = TrainDDROptParamCliff (
             MrcData,
             srwr2rd_sg,
             ParamListX,
             ARRAY_COUNT (ParamListX),
             NomWR2RD_sg - 1,
             NomWR2RD_sg + 1,
             LoopCount,
             Update,
             Outputs->MarginResult,
             NoShifts,
             ARRAY_COUNT (NoShifts),
             0,
             RankMask,
             0
             );
  if (Status != mrcSuccess) {
    return mrcTurnAroundTripError;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s RD2WR_SG\n", "\n ##### Running");
  Status = TrainDDROptParamCliff (
             MrcData,
             srrd2wr_sg,
             ParamListX,
             ARRAY_COUNT (ParamListX),
             NomRD2WR_sg - 1,
             NomRD2WR_sg + 1,
             LoopCount,
             Update,
             Outputs->MarginResult,
             NoShifts,
             ARRAY_COUNT (NoShifts),
             0,
             RankMask,
             0
             );
  if (Status != mrcSuccess) {
    return mrcTurnAroundTripError;
  }

  if (Ddr4) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s WR2RD_DG\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
               MrcData,
               srwr2rd_dg,
               ParamListX,
               ARRAY_COUNT (ParamListX),
               NomWR2RD_dg - 1,
               NomWR2RD_dg + 1,
               LoopCount,
               Update,
               Outputs->MarginResult,
               NoShifts,
               ARRAY_COUNT (NoShifts),
               0,
               RankMask,
               0
               );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTripError;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s RD2WR_DG\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
               MrcData,
               srrd2wr_dg,
               ParamListX,
               ARRAY_COUNT (ParamListX),
               NomRD2WR_dg - 1,
               NomRD2WR_dg + 1,
               LoopCount,
               Update,
               Outputs->MarginResult,
               NoShifts,
               ARRAY_COUNT (NoShifts),
               0,
               RankMask,
               0
               );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTripError;
    }
  }
  //
  // Different DIMM turnarounds
  //
  if (RunDD) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DDRD2RD\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
               MrcData,
               ddrd2rd,
               TestListRdX,
               ARRAY_COUNT (TestListRdX),
               NomRD2RD_dd,
               NomRD2RD_dd + 1,
               LoopCount,
               Update,
               Outputs->MarginResult,
               ClkShifts,
               ARRAY_COUNT (ClkShifts),
               0,
               RankMask,
               0
               );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTripError;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DDWR2WR\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
               MrcData,
               ddwr2wr,
               TestListWr,
               ARRAY_COUNT (TestListWr),
               NomWR2WR_dd - 1,
               NomWR2WR_dd + 1,
               LoopCount,
               Update,
               Outputs->MarginResult,
               ClkShifts,
               ARRAY_COUNT (ClkShifts),
               0,
               RankMask,
               0
               );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTripError;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DDWR2RD\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
               MrcData,
               ddwr2rd,
               ParamListX,
               ARRAY_COUNT (ParamListX),
               MAX (NomWR2RD_dd - 1, 4),
               NomWR2RD_dd + 1,
               LoopCount,
               Update,
               Outputs->MarginResult,
               ClkShifts,
               ARRAY_COUNT (ClkShifts),
               0,
               RankMask,
               0
               );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTripError;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DDRD2WR\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
               MrcData,
               ddrd2wr,
               ParamListX,
               ARRAY_COUNT (ParamListX),
               NomRD2WR_dd - 1,
               NomRD2WR_dd + 1,
               LoopCount,
               Update,
               Outputs->MarginResult,
               ClkShifts,
               ARRAY_COUNT (ClkShifts),
               0,
               RankMask,
               0
               );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTripError;
    }
  }
  //
  // Different Rank turnarounds
  //
  if (RunDR) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DRRD2RD\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
               MrcData,
               drrd2rd,
               TestListRdX,
               ARRAY_COUNT (TestListRdX),
               NomRD2RD_dr,
               NomRD2RD_dr + 1,
               LoopCount,
               Update,
               Outputs->MarginResult,
               ClkShifts,
               ARRAY_COUNT (ClkShifts),
               0,
               RankMask,
               0
               );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTripError;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DRWR2WR\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
               MrcData,
               drwr2wr,
               TestListWr,
               ARRAY_COUNT (TestListWr),
               NomWR2WR_dr - 1,
               NomWR2WR_dr + 1,
               LoopCount,
               Update,
               Outputs->MarginResult,
               ClkShifts,
               ARRAY_COUNT (ClkShifts),
               0,
               RankMask,
               0
               );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTripError;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DRWR2RD\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
               MrcData,
               drwr2rd,
               ParamListX,
               ARRAY_COUNT (ParamListX),
               MAX (NomWR2RD_dr - 1, 4),
               NomWR2RD_dr + 1,
               LoopCount,
               Update,
               Outputs->MarginResult,
               ClkShifts,
               ARRAY_COUNT (ClkShifts),
               0,
               RankMask,
               0
               );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTripError;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DRRD2WR\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
               MrcData,
               drrd2wr,
               ParamListX,
               ARRAY_COUNT (ParamListX),
               NomRD2WR_dr - 1,
               NomRD2WR_dr + 1,
               LoopCount,
               Update,
               Outputs->MarginResult,
               ClkShifts,
               ARRAY_COUNT (ClkShifts),
               0,
               RankMask,
               0
               );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTripError;
    }
  }

  //
  // Program SAFE values for ODT and SAmp
  //
  GuardBand = 1;
  UpdateSampOdtTiming (MrcData, GuardBand);

  //
  // ODT Delay (start) / Duration
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s mcodts\n", "\n ##### Running");
  Status = TrainDDROptParamCliff (
             MrcData,
             mcodts,
             TestListRdX,          // Including RcvEnaX to the test list
             ARRAY_COUNT (TestListRdX),
             0,
             2 + GuardBand,
             LoopCount,
             Update,
             Outputs->MarginResult,
             ClkShifts,
             ARRAY_COUNT (ClkShifts),
             0,
             RankMask,
             GuardBand
             );
  if (Status != mrcSuccess) {
    return mrcTurnAroundTripError;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s mcodtd\n", "\n ##### Running");
  Status = TrainDDROptParamCliff (
             MrcData,
             mcodtd,
             TestListRdX,
             ARRAY_COUNT (TestListRdX),
             (-1 - GuardBand),
             0,
             LoopCount,
             Update,
             Outputs->MarginResult,
             ClkShifts,
             ARRAY_COUNT (ClkShifts),
             0,
             RankMask,
             GuardBand
             );
  if (Status != mrcSuccess) {
    return mrcTurnAroundTripError;
  }

  //
  // Restore PCIT value
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    Offset = MCHBAR_CH0_CR_SC_PCIT_REG + (MCHBAR_CH1_CR_SC_PCIT_REG - MCHBAR_CH0_CR_SC_PCIT_REG) * Channel;
    MrcWriteCR (MrcData, Offset, ScPcitSave[Channel].Data);
  }

  // Print out the end results of the training step in Table Format
#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n--- Final TA values ---\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tC%d", Channel);
  }
  for (i = 0; i < 4; i++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRdRd%s", TypeStr[i]);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      if (!ChannelOut->ValidRankBitMask) {
        continue;
      }
      IntChannelOut = &IntOutputs->Controller[0].Channel[Channel];
      TcRdRd = &IntChannelOut->MchbarTcRdRd;
      if (i == 0) {
        PrintValue = (UINT8) TcRdRd->Bits.tRDRD_sg;
      } else if (i == 1) {
        PrintValue = (UINT8) TcRdRd->Bits.tRDRD_dg;
      } else if (i == 2) {
        PrintValue = (UINT8) TcRdRd->Bits.tRDRD_dr;
      } else {
        PrintValue = (UINT8) TcRdRd->Bits.tRDRD_dd;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", PrintValue);
    }
  }
  for (i = 0; i < 4; i++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRdWr%s", TypeStr[i]);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      if (!ChannelOut->ValidRankBitMask) {
        continue;
      }
      IntChannelOut = &IntOutputs->Controller[0].Channel[Channel];
      TcRdWr = &IntChannelOut->MchbarTcRdWr;
      if (i == 0) {
        PrintValue = (UINT8) TcRdWr->Bits.tRDWR_sg;
      } else if (i == 1) {
        PrintValue = (UINT8) TcRdWr->Bits.tRDWR_dg;
      } else if (i == 2) {
        PrintValue = (UINT8) TcRdWr->Bits.tRDWR_dr;
      } else {
        PrintValue = (UINT8) TcRdWr->Bits.tRDWR_dd;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", PrintValue);
    }
  }
  for (i = 0; i < 4; i++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nWrRd%s", TypeStr[i]);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      if (!ChannelOut->ValidRankBitMask) {
        continue;
      }
      IntChannelOut = &IntOutputs->Controller[0].Channel[Channel];
      TcWrRd = &IntChannelOut->MchbarTcWrRd;
      if (i == 0) {
        PrintValue = (UINT8) TcWrRd->Bits.tWRRD_sg;
      } else if (i == 1) {
        PrintValue = (UINT8) TcWrRd->Bits.tWRRD_dg;
      } else if (i == 2) {
        PrintValue = (UINT8) TcWrRd->Bits.tWRRD_dr;
      } else {
        PrintValue = (UINT8) TcWrRd->Bits.tWRRD_dd;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", PrintValue);
    }
  }
  for (i = 0; i < 4; i++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nWrWr%s", TypeStr[i]);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      if (!ChannelOut->ValidRankBitMask) {
        continue;
      }
      IntChannelOut = &IntOutputs->Controller[0].Channel[Channel];
      TcWrWr = &IntChannelOut->MchbarTcWrWr;
      if (i == 0) {
        PrintValue = (UINT8) TcWrWr->Bits.tWRWR_sg;
      } else if (i == 1) {
        PrintValue = (UINT8) TcWrWr->Bits.tWRWR_dg;
      } else if (i == 2) {
        PrintValue = (UINT8) TcWrWr->Bits.tWRWR_dr;
      } else {
        PrintValue = (UINT8) TcWrWr->Bits.tWRWR_dd;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", PrintValue);
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
#endif
  return Status;
}

/**
  General purpose function to optimize an abritray value, OptParam (see list above)
    OptParam is generally some timing number that impacts performance or power
    Expects that as OptParam gets smaller*, margins are flat until we hit a cliff
    This procedure defines a cliff as a reducution of 4 ticks in eye height/width
    * In the case of mcodts, higher values are actually worst
    To stress out the timing, xxDDR_CLK is shifted by +/- 15 PI ticks

  @param[in] MrcData         - Include all MRC global data.
  @param[in] OptParam        - Supports Turnaround Timings and ODT Start / Duration
  @param[in] TestList        - List of margin param to check to make sure timing are okay.
  @param[in] NumTests        - The size of TestList
  @param[in] Start           - Start point for this turn around time setting.
  @param[in] Stop            - Stop point for this turnaround time setting.
                                 Note that the Start/Stop values are the real values, not the encoded value
  @param[in] LoopCount       - Length of a given test
  @param[in] Update          - Update the CRs and host structure with ideal values
  @param[in] MarginByte      - Byte level margins
  @param[in] ClkShifts       - Array of PI clocks to be shifted
  @param[in] NumR2RPhases    - Number of PI clock phases
  @param[in] rank            - rank to work on
  @param[in] RankMask        - RankMask to be optimized
  @param[in] GuardBand       - GuardBand to be added to last pass value (to be a bit conservative).

  @retval MrcStatus      - If it succeeds return mrcSuccess
**/
MrcStatus
TrainDDROptParamCliff (
  IN MrcParameters *const MrcData,
  IN UINT8                OptParam,
  IN const UINT8          TestList[],
  IN UINT8                NumTests,
  IN INT8                 Start,
  IN INT8                 Stop,
  IN UINT8                LoopCount,
  IN UINT8                Update,
  IN UINT32               MarginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN const INT8           *ClkShifts,
  IN UINT8                NumR2RPhases,
  IN UINT8                rank,
  IN UINT8                RankMask,
  IN UINT8                GuardBand
  )
{
  static const MRC_REUTAddress REUTAddressConst = {
    // Rank, Bank, Row, Col
    {  0,    0,    0,   0    }, // Start
    {  7,    0,    0,   1023 }, // Stop
    {  0,    0,    0,   0    }, // Order
    {  0,    0,    0,   0    }, // IncRate
    {  1,    0,    0,   1    }  // IncValue
  };
  static const UINT8 OptParamDDType[] = { // Does this test run dr, dd or both?
  //drrd2rd ddrd2rd drwr2wr ddwr2wr drrd2wr ddrd2wr drwr2rd ddwr2rd rdodtd wrodtd mcodts mcodtd rtl srrd2rd srwr2rd_sg srwr2rd_dg srrd2wr_sg srrd2wr_dg
    1,      2,      1,      2,      1,      2,      1,      2,      3,     3,     3,     3,     0,  0,      0,         0,         0,         0
    };
  static const UINT8 RankMapping[16] = {15, 15, 15, 4, 15, 3, 15, 1, 15, 15, 15, 15, 5, 2, 15, 0};
  // Order of rank turnarounds for dr & dd.
  static const UINT32  RankOrder[2][6] = {
    { 0x32320101, 0x20101010, 0x23232320, 0x20, 0x10, 0x23 }, // RankOrder[0]: drsd - same DIMM
    { 0x21303120, 0x00002120, 0x00003020, 0x20, 0x00, 0x00 }  // RankOrder[1]: drdd - diff DIMM
  };
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcDimmOut        *DimmOut;
  MrcStatus         Status;
  MRC_REUTAddress   REUTAddress;
  MRC_WDBPattern    WDBPattern;                   // For 8 bit VA, this walks through each WDB pointer ~ 2X
  BOOLEAN           IsDual;
  BOOLEAN           ODT;
  BOOLEAN           PerByte;
  BOOLEAN           NotRankTraining;
  BOOLEAN           Lpddr;
  BOOLEAN           FindFirstPass;
  UINT32            BERStats[4];                                  // Track BER results
  UINT32            RankList;
  UINT32            Offset;
  UINT16            Margins[MAX_TESTS_OPT_PARAM_CLIFF][2][2][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];  // Tests X DR/DD x ClkPhases x Ch X Byte
  UINT16            NumCL;                                        // Number of cachelines per SubSeq
  UINT16            m;
  UINT16            SeqLC;
  UINT16            MinMarginLimit;
  UINT16            MaxMarginLimit;
  UINT16            MaxPiLimit;
  UINT16            ChMinMarginLimit[2];                            // Minimum Margin Limit, across channels for DD/DR tests. [0]: Used with v0, [1]: Used with -v0.
  UINT16            ChMaxMarginLimit[2];                            // Maximum Margin Limit, across channels for DD/DR tests. [0]: Used with v0, [1]: Used with -v0.
  UINT8             ShiftValue;
  UINT8             Channel;
  UINT8             ChannelMask;
  UINT8             Byte;
  UINT16            ByteMask;
  UINT8             Rank;
  UINT8             Dimm;
  UINT8             ChBitMask;
  UINT8             RankCount;
  UINT8             ChBitMaskdd;
  UINT8             RankMaskCh;
  UINT8             GlobalRankMask;
  UINT8             drddPresent[2];                               // [0]: ChBitMask for dr, [1]: ChBitMask for dd
  UINT8             CmdPat;
  UINT8             BMap[9];                                      // Needed for GetBERMarginByte function
  UINT8             MarginLimit;                                  // Need to change it to 20%of eye heigth
  UINT8             ResetDDR;
  UINT8             SelfRefresh;
  UINT8             RankInc;                                      // Increment every cacheline (HW adds +1 automatically)
  UINT16            ByteFailMask[MAX_CHANNEL];                    // Per ch mask indicating which bytes have failed
  UINT8             offs[MAX_CHANNEL];
  UINT8             Param;
  UINT8             iparam;
  UINT16            ByteDone;
  UINT8             dd;
  UINT8             test;
  UINT8             RankOrderIndex;
  UINT8             UpdateHostMargin;
  UINT8             Done;
  UINT8             MaxMargin;
  UINT8             ResultType;
  UINT8             WDBIncRate;                                   // Number of cachelines between incrementing WDB.
  UINT8             LoopEnd;
  INT8              v0;
  INT8              Inc;
  INT8              Off;
  INT8              Index;
  INT8              LastPass[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];     // Lass Pass Value for off
  INT8              Begin;
  INT8              End;
  INT8              ChLastPass;
  INT8              ActualGuardBand;
  BOOLEAN           Ddr4Vref;
  BOOLEAN           Ddr4;
  BOOLEAN           ClkShifted;
  UINT8             ResultRank;
  UINT8             BankCount;
  UINT8             MinBanks;
  UINT64            BankMapping;
  UINT64            BankMappingSave[MAX_CHANNEL];
#ifdef MRC_DEBUG_PRINT
  INT8              ChLastPass1[MAX_CHANNEL];
#endif // MRC_DEBUG_PRINT
  UINT8             RepeatInitialTest;
  MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_STRUCT  ReutChSeqRankL2PMapping;
  MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT                               ReutChSeqCfg;

  Inputs          = &MrcData->Inputs;
  MrcCall         = Inputs->Call.Func;
  Outputs         = &MrcData->Outputs;
  Debug           = &Outputs->Debug;
  Status          = mrcSuccess;
  Done            = 0;
  drddPresent[0]  = 0;
  drddPresent[1]  = 0;
  MarginLimit     = 10;  // Drop of X% in margin means failure
  ResetDDR        = 1;
  SelfRefresh     = 0;
  WDBIncRate      = 13;
  NumCL           = 128;
  RepeatInitialTest = 4;  // Run initial RTL point 5 times

  MRC_ASSERT (NumTests <= MAX_TESTS_OPT_PARAM_CLIFF, Debug, "ERROR: too many tests passed into TrainDDROptParamCliff()\n");

  //
  // For {8,5,4,3,2} ranks, this covers each rank ~ {3,5,6,8,12}X
  // For 8 bit VA, this walks through each WDB pointer ~ 2X
  //
  WDBPattern.IncRate  = 0;
  WDBPattern.Start    = 0;
  WDBPattern.Stop     = 7;
  WDBPattern.DQPat    = 0;
  MrcCall->MrcSetMem ((UINT8 *) ByteFailMask, sizeof (ByteFailMask), 0);
  MrcCall->MrcSetMem (offs, sizeof (offs), 0);
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) BankMappingSave, sizeof (BankMappingSave), 0);
  MrcCall->MrcSetMem ((UINT8 *) ChMinMarginLimit, sizeof (ChMinMarginLimit), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) ChMaxMarginLimit, sizeof (ChMaxMarginLimit), 0);
  MrcCall->MrcCopyMem ((UINT8 *) &REUTAddress, (UINT8 *) &REUTAddressConst, sizeof (REUTAddress));
  for (Byte = 0; Byte < ARRAY_COUNT (BMap); Byte++) {
    BMap[Byte] = Byte;
  }

  ControllerOut   = &Outputs->Controller[0];

  GlobalRankMask = Outputs->ValidRankMask & RankMask;
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  Ddr4  = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  NotRankTraining = ((OptParam == rtl) || (OptParam == srwr2rd_sg) || (OptParam == srwr2rd_dg) || (OptParam == srrd2wr_sg) || (OptParam == srrd2wr_dg));
  FindFirstPass   = (OptParam == rtl);  // FindFirstPass logic only works for RTL!
  ODT             = (OptParam == rdodtd) || (OptParam == wrodtd) || (OptParam == mcodtd) || (OptParam == mcodts);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nNotRankTraining = %u, ODT = %d\n", NotRankTraining, ODT);

  //
  // Decide which channels need to be run and program NumCachelines
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    if (ChannelOut->ValidRankBitMask) {
      ChannelMask = MRC_BIT0 << Channel;
      RankMaskCh  = ChannelOut->ValidRankBitMask;
      IsDual      = ((RankMaskCh & 0xC) == 0xC) || ((RankMaskCh & 0x3) == 0x3);

      if (Ddr4) {
        //
        // Save Bank Mapping
        //
        Offset = MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG +
          (MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG) * Channel;
        BankMappingSave[Channel] = MrcReadCR64 (MrcData, Offset);
      }

      //
      // Continue if no ranks in this channel
      //
      if ((RankMaskCh & RankMask) == 0) {
        continue;
      }

      if ((OptParamDDType[OptParam] & 0x2) && (ChannelOut->DimmCount == 2)) {
        drddPresent[1] |= ChannelMask; // dd parameter and channel has 2 DIMMs
      }

      if (((OptParamDDType[OptParam] & 0x1) && IsDual) || NotRankTraining) {
        drddPresent[0] |= ChannelMask; // dr parameter and channel has a dual rank
      }

      if (ODT && ((drddPresent[0] & (1 << Channel)) == 0)) {
        //
        // ODT matters when Single rank
        // dr parameter and channel has a dual rank
        //
        drddPresent[0] |= ChannelMask;
      }
    }
  }

  ChBitMask = drddPresent[1] | drddPresent[0]; // Chanel is present if it has either a dr or dd
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "drddPresent[0] = 0x%x, drddPresent[1] = 0x%x, ChBitMask = 0x%x\n",
    drddPresent[0],
    drddPresent[1],
    ChBitMask
    );

  //
  // There is nothing to optimize for this parameter
  //
  if ((ChBitMask == 0) || (Stop <= Start)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChBitMask = %d, Start = 0x%x, Stop = 0x%x\n", ChBitMask, Start, Stop);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "No need to optimize TA, OptParam = %d\n", OptParam);
    return mrcFail;
  }
  //
  // Setup the REUT Test
  //
  SeqLC           = LoopCount;
  RankInc         = 0;
  if ((OptParam == ddwr2rd) || (OptParam == drwr2rd) || (OptParam == srwr2rd_sg) || (OptParam == srwr2rd_dg)) {
    CmdPat = PatWrRdTA;
    REUTAddress.Start[2] = 0;    // Row
    REUTAddress.Stop[2]  = 1024; // Row
    // Rank inc and Row inc adjusted inside RunIOTest()
    if (OptParam == srwr2rd_dg) {
      Outputs->DQPat  = TurnAroundWR_DG;
    } else if (OptParam == srwr2rd_sg) {
      Outputs->DQPat  = TurnAroundWR_SG;
    } else {
      Outputs->DQPat  = TurnAroundWR;
    }
  } else if ((OptParam == ddrd2wr) || (OptParam == drrd2wr) || (OptParam == srrd2wr_sg) || (OptParam == srrd2wr_dg)) {
    CmdPat          = PatRdWrTA;
    RankInc         = 31;
    NumCL           = 512;
    REUTAddress.Start[2]   = 0;    // Row
    REUTAddress.Stop[2]    = 1024;
    REUTAddress.IncRate[2] = 128;
    REUTAddress.IncVal[2]  = 1;
    if (OptParam == srrd2wr_dg) {
      Outputs->DQPat  = TurnAroundRW_DG;
    } else if (OptParam == srrd2wr_sg) {
      Outputs->DQPat  = TurnAroundRW_SG;
    } else {
      Outputs->DQPat  = TurnAroundRW;
      RankInc         = 1;
    }
  } else if (ODT) {
    CmdPat          = PatODTTA;
    Outputs->DQPat  = TurnAroundODT;
    RankInc         = 1;
  } else if (OptParam == rtl) {
    CmdPat = PatWrRd;
    Outputs->DQPat  = RdRdTA;
    //
    // Less optimistic values since we are updating values and RMT fails
    //
    WDBIncRate  = 16;
    NumCL       = 4;
  } else {
    CmdPat = PatWrRd;
    Outputs->DQPat  = TurnAround;
  }

  WDBPattern.DQPat        = Outputs->DQPat;
  WDBPattern.IncRate      = WDBIncRate;
  REUTAddress.IncRate[0]  = RankInc; // Rank
  REUTAddress.IncRate[3]  = RankInc; // Col

  if (Ddr4) {
    if ((OptParam == srrd2wr_dg) || (OptParam == srwr2rd_dg) || ODT || (OptParam == rtl)) {
      //
      // Set Bank address logic to hit same rank RdWr
      // Bank Start/Stop will be also reprogrammed inside RunIOTest when DQPat=TurnAroundODT
      //
      REUTAddress.Start[1]   = 0; // Bank start
      REUTAddress.Stop[1]    = 3; // Bank stop
      REUTAddress.IncVal[1]  = 1;
      REUTAddress.IncRate[1] = 0; // inc every CL
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        //
        // Setup Bank Logical to Physical mapping so that only Bank Groups are toggled
        //
        // 16 banks case (x8):
        // Logical Bank:         0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
        //                       -----------------------------------------------
        // Physical Bank:        0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
        // Physical Bank Group:  0  1  2  3  0  1  1  2  2  3  3  0  0  0  0  0
        //
        // 8 banks case (x16):
        // Logical Bank:         0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
        //                       -----------------------------------------------
        // Physical Bank:        0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
        // Physical Bank Group:  0  1  0  1  0  1  1  0  0  1  1  0  0  0  0  0

        MinBanks = 16;
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          if (MrcRankInChannelExist (MrcData, Dimm * MAX_RANK_IN_DIMM, Channel)) {
            DimmOut = &ChannelOut->Dimm[Dimm];
            //
            // Find the minimum number of banks on all the DIMMs in this channel
            //
            BankCount = DimmOut->BankGroups * DimmOut->Banks;
            MinBanks = MIN (MinBanks, BankCount);
          }
        }

        BankMapping = (MinBanks == 16) ? 0x00000CC88440C840ULL : 0x0000044004404040ULL;

        Offset = MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG +
          (MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG) * Channel;
        MrcWriteCR64 (MrcData, Offset, BankMapping);
      } // for Channel
    } else if ((OptParam == srrd2wr_sg) || (OptParam == srwr2rd_sg)) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        //
        // Setup Bank Logical to Physical mapping so that only Banks are toggled (same bank group)
        //
        // Logical Bank:         0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
        //                       -----------------------------------------------
        // Physical Bank:        0  1  2  3  0  1  1  2  2  3  3  0  0  0  0  0
        // Physical Bank Group:  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
        //
        Offset = MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG +
          (MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG) * Channel;
        MrcWriteCR64 (MrcData, Offset, 0x33221103210ULL);
      } // for Channel
    }
  }
  //
  // SOE=0, EnCADB=0, EnCKE=0, SubSeqWait=0
  //
  SetupIOTest (MrcData, ChBitMask, CmdPat, NumCL, (UINT8) SeqLC, &REUTAddress, NSOE, &WDBPattern, 0, 0, 0);

  Outputs->DQPatLC = MRC_BIT0 << (LoopCount - MrcLog2 ((UINT32) (NumCL - 1)));
  if (Outputs->DQPatLC < 1) {
    Outputs->DQPatLC = 1;
  }
  //
  // Optimize parameter per byte.  Everything else is per channel
  //
  PerByte = (OptParam == mcodts) || (OptParam == mcodtd);

  //
  // Keep track of which bytes have failed and are we done yet
  //
  ByteDone = (1 << Outputs->SdramCount) - 1;

  //
  // ###########################################################
  // ####  Loop through OptParam X DD X ClkPhases X Params and measure margin #####
  // ###########################################################
  //
  if (OptParam == mcodts) {
    //
    // In the case of mcodts, higher values are actually worst.
    //
    Begin = Start;
    End   = Stop;
    Inc   = 1;
  } else {
    Begin = Stop;
    End   = Start;
    Inc   = -1;
  }

  ActualGuardBand = (Inc * GuardBand);

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Start = %d, Stop = %d, Begin = %d, End = %d, Inc = %d\n",
    Start,
    Stop,
    Begin,
    End,
    Inc
    );
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (OptParam == rtl) ? "Rank = %d\n" : "", rank);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel 0\t\t\t\t\t\t\t\t1\nByte\t");
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE, (
                      Outputs->SdramCount == MAX_SDRAM_IN_DIMM
                      ) ? "0\t1\t2\t3\t4\t5\t6\t7\t8\t0\t1\t2\t3\t4\t5\t6\t7\t8\n" :
                      "0\t1\t2\t3\t4\t5\t6\t7\t0\t1\t2\t3\t4\t5\t6\t7\n"
    );

  //
  // Init Variables
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      MrcCall->MrcSetMem ((UINT8 *) &LastPass[Channel][0], Outputs->SdramCount, (UINT8) (Begin - ActualGuardBand));
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        for (iparam = 0; iparam < NumTests; iparam++) {
          for (dd = 0; dd < 2; dd++) {
            for (test = 0; test < NumR2RPhases; test++) {
              Margins[iparam][dd][test][Channel][Byte] = 1280;
            }
          }
        }
      }
    }
  }
  //
  // Walk through different OptParam values
  //
  for (Off = (INT8) Begin; Off != (INT8) (End + Inc); Off += Inc) {
    if (Done) {
      break;
    }
    Index = (Off - Begin) * Inc; // Index = 0, 1, 2..
    if (Index == 1) {
      if ((RepeatInitialTest != 0) && FindFirstPass) {  // Repeat initial measurement of RTL to filter out repetition noise
        Off -= Inc;
        Index = 0;
        RepeatInitialTest--;
      }
    }
    //
    // Inc can only take a value of +/- 1.
    //
    if ((Index == 1) && FindFirstPass) {
      Inc  *= -1;
      Off   = End;
      End   = Begin - Inc;  // One Inc less since we have already done Index 0.
      Begin = Off - Inc;    // One Inc less to get us starting at Index 1
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "Find First Pass - Walking backwards.\n Off = %d, Begin = %d, End = %d, Inc = %d\n",
        Off,
        Begin,
        End,
        Inc
        );
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Param^ Offset-> %d\n   Actl\t", Off);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut  = &ControllerOut->Channel[Channel];
      RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
      //
      // if nothing for this channel OR No Ranks in this channel
      //
      if (!((MRC_BIT0 << Channel) & ChBitMask) || (RankMaskCh == 0)) {
#ifdef MRC_DEBUG_PRINT
        if (Channel == 0) {
          if (Outputs->SdramCount == (MAX_SDRAM_IN_DIMM - 1)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t");
          } else {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t\t");
          }
        }
#endif // MRC_DEBUG_PRINT
        continue;
      }

      if (FindFirstPass && (Index == 0)) {
        //
        // We use the current RTL value for the initial test
        //
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n Ch%u initial RTL: %u", Channel, ChannelOut->RTLatency[rank]);
      } else {
        //
        // No need to update MrcData host during this step even if not collecting data
        //
        LoopEnd = (UINT8) ((PerByte) ? Outputs->SdramCount : 1);
        for (Byte = 0; Byte < LoopEnd; Byte++) {
          UpdateTAParamOffset (MrcData, Channel, Byte, OptParam, Off, 0, 0, RankMaskCh);
        }
        if ((OptParam == wrodtd) || (OptParam == rdodtd)) {
          // Set UpdateHost to TRUE because TA values share the same register
          MrcTatStretch (MrcData, Channel, OptParam, Off - Start, TRUE);
        }
      }
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

    //
    // Test both: different dr and dd as required
    //
    for (dd = 0; dd < 2; dd++) {
      if (Done) {
        break;
      }
      //
      // Check if this test type should be run
      //
      ChBitMaskdd = drddPresent[dd];
      if (ChBitMaskdd == 0) {
        continue;
      }

      if (OptParam != rtl) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (dd == 0) ? "Dual Rank\n" : "Dual Dimm\n");
      }
      //
      // Select Ranks in the correct order based on the test type
      // Need to re-order the ranks based on the value of ddw2r
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        //
        // Set global start bit on participating channels only
        //
        Offset = MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG +
          ((MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG) * Channel);
        ReutChSeqCfg.Data = MrcReadCR64 (MrcData, Offset);
        if ((ChBitMaskdd & (1 << Channel)) == 0) {
          ReutChSeqCfg.Bits.Global_Control  = 0;
          MrcWriteCR64 (MrcData, Offset, ReutChSeqCfg.Data);
          continue;
        } else {
          ReutChSeqCfg.Bits.Global_Control  = 1;
          MrcWriteCR64 (MrcData, Offset, ReutChSeqCfg.Data);
        }

        ChannelOut  = &ControllerOut->Channel[Channel];
        RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
        if (RankMaskCh == 0) {
          continue; // No Ranks in this channel
        }
        //
        // Initialize variables and read out ordered rank list
        //
        ReutChSeqRankL2PMapping.Data  = 0;
        RankCount                     = 0;

        if (NotRankTraining) {
          RankList = 0x00003210;
        } else {
          RankOrderIndex = RankMapping[RankMaskCh];
          if (RankOrderIndex == 15) {
            RankList = 0x00003210;
          } else {
            RankList = RankOrder[dd][RankOrderIndex];
          }
        }

        while (RankList > 0) {
          Rank = (RankList & 0xF); // Nibble by Nibble
          RankList = (RankList >> 4);
          if (!(RankMaskCh & (MRC_BIT0 << Rank))) {
            continue;
          }

          ShiftValue = RankCount *
            MRC_BIT0 <<
            MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_Logical_to_Physical_Rank0_Mapping_WID;
          ReutChSeqRankL2PMapping.Data |= (Rank << ShiftValue);
          RankCount++;
        }

        Offset = MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG +
          (
            (
              MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG -
              MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG
            ) * Channel
          );
        MrcWriteCR (MrcData, Offset, ReutChSeqRankL2PMapping.Data);
        Offset = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_REG +
          (
            (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_REG) *
            Channel
          ) + 7;
        MrcWriteCR8 (MrcData, Offset, RankCount - 1);
      } // for Channel
      //
      // ###################################################
      // ### Walk through different sets of rank2rank timings  ###
      // ###################################################
      //
      for (test = 0; test < NumR2RPhases; test++) {
        if (Done) {
          break;
        }

        v0 = ClkShifts[test];

        //
        // Program rank offsets differently for dd vs. dr
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!(ChBitMaskdd & (MRC_BIT0 << Channel))) {
            if (NotRankTraining) {
              offs[Channel] = 0;
            } else {
              continue;
            }
          } else {
            ChannelOut  = &ControllerOut->Channel[Channel];
            RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;

            if (NotRankTraining) {
              // Shift all signals in the channel (Clk/Ctl/Cmd/Dq) by v0 if there is enough room.
              FindNormalizationPiLimits (MrcData, Channel, RankMaskCh, NULL, &MaxMarginLimit);
              FindDqPiLimits (MrcData, Channel, RankMaskCh, NULL, &MaxPiLimit);
              offs[Channel] = (UINT8) v0;

              // Make sure the shift does not saturate TxDq/RcvEna PIs
              if ((MaxPiLimit + v0) > DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX) {
                offs[Channel] = (UINT8) MIN (offs[Channel], DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX - MaxPiLimit);
              }

              // Make sure the shift does not saturate Clk/Ctl/Cmd PIs
              if ((MaxMarginLimit + v0) > DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX) {
                offs[Channel] = (UINT8) MIN (offs[Channel], DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX - MaxMarginLimit);
              }
            } else {
              // Determine the Max/Min PI Values for how much to shift CLK. Depending on DD/DR test, use different ranks.
              FindDqPiLimits (MrcData, Channel, (dd == 1) ? 0x3 : 0x5, &MinMarginLimit, &MaxMarginLimit);
              ChMinMarginLimit[0] = MIN (MinMarginLimit, ChMinMarginLimit[0]);
              ChMaxMarginLimit[0] = MAX (MaxMarginLimit, ChMaxMarginLimit[0]);

              // Determine the Max/Min PI Values for how much to shift CLK. Depending on DD/DR test, use different ranks.
              FindDqPiLimits (MrcData, Channel, (dd == 1) ? 0xC : 0xA, &MinMarginLimit, &MaxMarginLimit);
              ChMinMarginLimit[1] = MIN (MinMarginLimit, ChMinMarginLimit[1]);
              ChMaxMarginLimit[1] = MAX (MaxMarginLimit, ChMaxMarginLimit[1]);
            }
          }
        } // For Channel

        if (!NotRankTraining) {
          // For DD/DR, determine if CLK and the dependent DQ PIs can be shifted by v0, otherwise limit how much we shift.
          if ((ChMaxMarginLimit[0] + v0) > DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX) {
            offs[0] = (UINT8) (DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX - ChMaxMarginLimit[0]);
          } else if ((v0 < 0) && (ChMinMarginLimit[0] < -v0)) {
            offs[0] = (UINT8) ChMinMarginLimit[0];
          } else {
            offs[0] = (UINT8) v0;
          }

          // for DD/DR, determine if CLK and the dependent DQ PIs can be shifted by -v0, otherwise limit how much we shift.
          if ((ChMaxMarginLimit[1] - v0) > DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX) {
            offs[1] = (UINT8) (DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX - ChMaxMarginLimit[1]);
          } else if (((-v0) < 0) && (ChMinMarginLimit[1] < v0)) {
            offs[1] = (UINT8) ChMinMarginLimit[1];
          } else {
            offs[1] = (UINT8) -v0;
          }
        }

        ClkShifted = FALSE;
        if (NotRankTraining) {
          //
          // UpdateHost=0, SkipTx=0
          //
          if (v0 != 0) {
            ShiftCh2Ch (MrcData, RankMask, offs, ResetDDR, SelfRefresh, 0, 0);
            ClkShifted = TRUE;
          }
        } else if (dd == 1) {
          //
          // For DD
          // Shift Clk/DQ on one DIMM by v0 and Clk/DQ on other DIMM by -v0
          // @todo: CTL picode should be optionally shifted to improve margins
          //
          SetCmdMargin (MrcData, ChBitMaskdd, 0x3, WrT, offs[0], 0, ResetDDR, SelfRefresh);
          SetCmdMargin (MrcData, ChBitMaskdd, 0xC, WrT, offs[1], 0, ResetDDR, SelfRefresh);
          ClkShifted = TRUE;
        } else if (!Inputs->Ddr4DdpSharedClock) {
          //
          // For DR
          // Shift Clk/DQ on front side by v0 and Clk/DQ on backside by -v0
          // @todo: CTL picode should be optionally shifted to improve margins
          //
          SetCmdMargin (MrcData, ChBitMaskdd, 0x5, WrT, offs[0], 0, ResetDDR, SelfRefresh);
          SetCmdMargin (MrcData, ChBitMaskdd, 0xA, WrT, offs[1], 0, ResetDDR, SelfRefresh);
          ClkShifted = TRUE;
        }
        if (ClkShifted) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLK Shift: [%d %d]\n", offs[0], offs[1]);
        }
        //
        // Test different margin param
        //
        for (iparam = 0; iparam < NumTests; iparam++) {
          Param = TestList[iparam];
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s ", MarginTypesString[Param]);

          ResultType = GetMarginResultType (Param);

          //
          // Get the width/height limit for the parameter
          //
          //MinMarginLimit = MrcGetUpmPwrLimit (MrcData, Param, UpmLimit);
          //
          // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d ", MinMarginLimit);
          // Calculate MaxMargin and Starting Point for margin search
          //
          MaxMargin = MAX_POSSIBLE_TIME;
          Ddr4Vref = FALSE;
          ResultRank = rank;
          if (Ddr4 && ((Param == WrV) || (Param == WrFan2) || (Param == WrFan3))) {
            MaxMargin = MAX_POSSIBLE_DDR4_WRITE_VREF;
            Ddr4Vref = TRUE;
          } else if ((Param == RdV)    ||
                     (Param == RdFan2) ||
                     (Param == RdFan3) ||
                     (Param == WrV)    ||
                     (Param == WrFan2) ||
                     (Param == WrFan3)
                     ) {
            MaxMargin = MAX_POSSIBLE_VREF;
          }
          //
          // Are we done yet or should we keep testing?
          //
          Done = 1;
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!(ChBitMaskdd & (MRC_BIT0 << Channel))) {
              continue;
            }

            ChannelOut  = &ControllerOut->Channel[Channel];
            RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
            if (RankMaskCh == 0) {
              continue; // No Ranks in this channel
            }

            //
            // When FindFirstPass is used, all Bytes have to have passed before we stop.
            // We uses ByteFailMask[] to track the passing bytes in this case.
            //
            if (PerByte || FindFirstPass) {
              if (ByteFailMask[Channel] != ByteDone) {
                Done = 0;
              }
            } else {
              if (ByteFailMask[Channel] == 0) {
                Done = 0;
              }
            }
          }

          if (Done) {
            break;
          }

          Status = GetMarginByte (MrcData, Outputs->MarginResult, Param, 0, 0xF);
          if (Status != mrcSuccess) {
            return Status;
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "% 3d\t", v0);
          Status = MrcGetBERMarginByte (
                     MrcData,
                     Outputs->MarginResult,
                     ChBitMaskdd,
                     Ddr4Vref ? GlobalRankMask : rank,
                     Ddr4Vref ? GlobalRankMask : 0xFF,
                     Param,
                     0,  // Mode
                     BMap,
                     1,
                     MaxMargin,
                     0,
                     BERStats
                     );
          if (Status != mrcSuccess) {
            return Status;
          }

          if (Ddr4Vref) {
            //
            // We return results on first available rank.
            //
            for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
              if ((1 << Rank) & GlobalRankMask) {
                ResultRank = Rank;
                break;
              }
            }
          }
          //
          // Record Results
          //
          UpdateHostMargin = 1;

          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            ChannelOut  = &ControllerOut->Channel[Channel];
            RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
            //
            // if nothing for this channel OR No Ranks in this channel
            //
            if (!((MRC_BIT0 << Channel) & ChBitMaskdd) || (RankMaskCh == 0)) {
#ifdef MRC_DEBUG_PRINT
              if (Channel == 0) {
                if (Outputs->SdramCount == (MAX_SDRAM_IN_DIMM - 1)) {
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t");
                } else {
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t\t");
                }
              }
#endif // MRC_DEBUG_PRINT
              continue;
            }

            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              //
              // For this optimization, it makes more sense to look at the full sum
              //
              ByteMask = 1 << Byte;
              m = EffectiveMargin (
                    (UINT16) MarginByte[ResultType][ResultRank][Channel][Byte][0],
                    (UINT16) MarginByte[ResultType][ResultRank][Channel][Byte][1]
                    );

              if (m < 20) {
                m = 20;
              }
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d", m);

              //
              // If previously failed, this is also a failure unless we are looking for
              // the first passing offset.
              //
              if ((ByteFailMask[Channel] & ByteMask) && !FindFirstPass) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "#\t");
                continue;
              }

              //
              // Check if the first test is failing with zero margin.
              // Stop the test in this case - initial point should be passing.
              //
              if ((Index == 0) && (m == 20)) {
                ByteFailMask[Channel] = ByteDone;
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "#\t");
                continue;
              }

              /* @todo: disable this as it make the resutsl very conservative
              //
              // Byte fails if margin is below MinMarginLimit at any time
              //
              if (m < MinMarginLimit) {
                //
                // If we are looking for pass, continue and do not update LastPass
                //
                if (TRUE == FindFirstPass) {
                  if (Index == 0) {
                    //
                    // When training from the most aggressive setting to the conservative setting,
                    // if we fail the first setting we stop.
                    //
                    ByteFailMask[Channel] = ByteDone;
                  }
                  UpdateHostMargin = 0;
                } else {
                  ByteFailMask[Channel] |= ByteMask;
                  LastPass[Channel][Byte] = Off - Inc - ActualGuardBand;
                }
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "#\t");
                continue;
              }
              */
              if (Index == 0) {
                //
                // Get the smallest marging at Index 0
                //
                if (Margins[iparam][dd][test][Channel][Byte] > m) {
                  Margins[iparam][dd][test][Channel][Byte] = m;
                }
              } else {
                //
                // Check if we dropped more than the percent allowed
                //
                if (m < ((Margins[iparam][dd][test][Channel][Byte] * (100 - MarginLimit)) / 100)) {
                  if (!FindFirstPass) {
                    ByteFailMask[Channel] |= ByteMask;
                    LastPass[Channel][Byte] = Off - Inc - ActualGuardBand;
                  }
                  UpdateHostMargin = 0;
                  MRC_DEBUG_MSG (
                    Debug,
                    MSG_LEVEL_NOTE,
                    "#-%d\t",
                    (ABS (m - Margins[iparam][dd][test][Channel][Byte]) * 100) / Margins[iparam][dd][test][Channel][Byte]
                    );
                  continue;
                } else {
                  if (FindFirstPass) {
                    if ((ByteFailMask[Channel] & ByteMask) != ByteMask) {
                      LastPass[Channel][Byte] = Off - ActualGuardBand;
                      ByteFailMask[Channel] |= ByteMask;
                    }
                  } else {
                    LastPass[Channel][Byte] = Off - ActualGuardBand;
                  }
                }
              }

              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                ".%c%d\t",
                (m > Margins[iparam][dd][test][Channel][Byte]) ? '+' : '-',
                (ABS (m - Margins[iparam][dd][test][Channel][Byte]) * 100) / Margins[iparam][dd][test][Channel][Byte]
                );
            } // for Byte
          } // for Channel

          //
          // Stop the test if we fail on the initial setting
          //
          if (Index == 0) {
            for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
              if (ByteFailMask[Channel] != 0) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nCh%u failed initial value!\n", Channel);
                return mrcFail;
              }
            }
          }

          if (UpdateHostMargin) {
            Status = ScaleMarginByte (MrcData, Outputs->MarginResult, Param, ResultRank);
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
        } // for iparam

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

        //
        // Clean up
        //
        if (NotRankTraining) {
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            offs[Channel] = 0;
          }
          //
          // UpdateHost=0, SkipTx=0
          //
          if (v0 != 0) {
            ShiftCh2Ch (MrcData, RankMask, offs, ResetDDR, SelfRefresh, 0, 0);
          }
        } else {
          SetCmdMargin (MrcData, ChBitMaskdd, RankMask, WrT, 0, 0, ResetDDR, SelfRefresh);
        }
      } // for test in ClkShifts[]

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    } // for dd
    if ((OptParam == wrodtd) || (OptParam == rdodtd)) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut  = &ControllerOut->Channel[Channel];
        RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
        //
        // If nothing for this channel OR No Ranks in this channel
        //
        if (!((MRC_BIT0 << Channel) & ChBitMask) || (RankMaskCh == 0)) {
          continue;
        }
        // MrcTatStretch was called with UpdateHost so need to clean back to original values
        MrcTatStretch (MrcData, Channel, OptParam, - (Off - Start), TRUE);
      }
    }
  } // for Off

  //
  // If we are sweeping agressive settings to conservative settings, we
  // need to restore original Inc, Begin, and End values to select the
  // proper offset if bytes have varying offsets values for a parameter
  // that is NOT specified per Byte.
  //
  if (FindFirstPass) {
    Off   = End;         // Temp storage for swap
    End   = Begin + Inc;
    Begin = Off + Inc;
    Inc  *= -1;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Find First Pass - Reverting Inc, Begin, and End\n Begin = %d, End = %d, Inc = %d,\n",
      Begin,
      End,
      Inc
      );
  }

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Optimal offset per Byte\n\t");
  //
  // Print OPTIMAL value
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut            = &ControllerOut->Channel[Channel];
    RankMaskCh            = ChannelOut->ValidRankBitMask & RankMask;
    ChLastPass1[Channel]  = End;
    //
    // if nothing for this channel OR No Ranks in this channel
    //
    if (!((1 << Channel) & ChBitMask) || (RankMaskCh == 0)) {
      if (Channel == 0) {
        if (Outputs->SdramCount == (MAX_SDRAM_IN_DIMM - 1)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t");
        } else {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t\t");
        }
      }
      continue;
    }

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", LastPass[Channel][Byte]);
      if ((Inc == 1) && (ChLastPass1[Channel] > LastPass[Channel][Byte])) {
        ChLastPass1[Channel] = LastPass[Channel][Byte];
      }

      if ((Inc == -1) && (ChLastPass1[Channel] < LastPass[Channel][Byte])) {
        ChLastPass1[Channel] = LastPass[Channel][Byte];
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut  = &ControllerOut->Channel[Channel];
    RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
    //
    // if nothing for this channel OR No Ranks in this channel
    //
    if (!((MRC_BIT0 << Channel) & ChBitMask) || (RankMaskCh == 0)) {
      continue;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Optimal offset Channel %d = %d\n", Channel, ChLastPass1[Channel]);
  }
#endif // MRC_DEBUG_PRINT
  //
  // Program new value
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((MRC_BIT0 << Channel) & ChBitMask)) {
      continue;
    }

    ChannelOut  = &ControllerOut->Channel[Channel];
    RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
    if (RankMaskCh == 0) {
      continue; // No Ranks in this channel
    }
    //
    // Start with the most aggressive setting
    //
    ChLastPass = End;
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (Update == 0) {
        LastPass[Channel][Byte] = Begin;
      }

      if ((Inc == 1) && (ChLastPass > LastPass[Channel][Byte])) {
        ChLastPass = LastPass[Channel][Byte];
      }

      if ((Inc == -1) && (ChLastPass < LastPass[Channel][Byte])) {
        ChLastPass = LastPass[Channel][Byte];
      }

      if (PerByte) {
        UpdateTAParamOffset (MrcData, Channel, Byte, OptParam, LastPass[Channel][Byte], Update, 1, RankMaskCh);
      }
    }

    if (PerByte == FALSE) {
      UpdateTAParamOffset (MrcData, Channel, 0, OptParam, ChLastPass, Update, 1, RankMaskCh);
      if ((OptParam == wrodtd) || (OptParam == rdodtd)) {
        // @check: should pass offset so subtract Start
        MrcTatStretch (MrcData, Channel, OptParam, ChLastPass - Start, TRUE);
      }
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected Offset for channel %d is = %d\n", Channel, ChLastPass);
  }

  if (Ddr4) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      Offset = MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG +
        (MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG) * Channel;
      MrcWriteCR64 (MrcData, Offset, BankMappingSave[Channel]);
    } // for Channel
  }

  return Status;
}

/**
  Sets commnad margins when moving WrT, WrTBox, or WrV
  NOTE: ONLY one, ResetDDR or SelfRefresh can be set inside this function

  @param[in] MrcData         - Include all MRC global data.
  @param[in] ChBitMask       - Bit mask of populated channels
  @param[in] Ranks           - Bit Mask of populated ranks
  @param[in] Param           - Input parameter to update
  @param[in] Value0          - value to be added
  @param[in] Value1          - value to be added
  @param[in] ResetDDR        - Do we reset DDR?
  @param[in] SelfRefresh     - Do we perform Self refresh?

  @retval MrcStatus      - If it succeeds return mrcSuccess
**/
void
SetCmdMargin (
  IN MrcParameters *const MrcData,
  IN const UINT8          ChBitMask,
  IN const UINT8          Ranks,
  IN const UINT8          Param,
  IN const UINT8          Value0,
  IN const UINT8          Value1,
  IN UINT8                ResetDDR,
  IN const UINT8          SelfRefresh
  )
{
  MrcControllerOut  *ControllerOut;
  UINT8             Channel;
  UINT8             RankMaskCh;
  UINT8             Offset;
  const MrcInput    *Inputs;

  ControllerOut = &MrcData->Outputs.Controller[0];
  Inputs        = &MrcData->Inputs;

  Offset        = 0;
  if (SelfRefresh && ResetDDR) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_ERROR,
      "WARNING SelfRefresh OR ResetDDR can be set at once...performing SelfRefresh\n"
      );
    ResetDDR = 0;
  }

  if (SelfRefresh) {
    EnterSR (MrcData);
  }
  //
  // Change Clock Timing
  //
  if ((Param == WrT) || (Param == WrTBox)) {
    //
    // Walk though all chs and ranks
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (ChBitMask & (MRC_BIT0 << Channel)) {
        //
        // determine which ranks from parameter "Ranks" exist in this channel
        //
        RankMaskCh = Ranks & ControllerOut->Channel[Channel].ValidRankBitMask;
        if (RankMaskCh == 0) {
          continue; // No Ranks in this channel
        }

        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, RankMaskCh, 3, Value0, 0);
      }
    }
  }

  if ((Param == WrV) || (Param == (WrTBox))) {
    if (Param == WrV) {
      Offset = Value0;
    } else {
      if (Param == WrTBox) {
        Offset = ((2 * Value1) - 1) * 8;
      }
    }

    UpdateVrefWaitTilStable (MrcData, 2, 0, Offset, 0, 0, FALSE, 0);
    if (Inputs->CaVrefConfig == 2) {
      UpdateVrefWaitTilStable (MrcData, 3, 0, Offset, 0, 0, FALSE, 0);
    }
  }

  if (ResetDDR) {
    MrcResetSequence (MrcData);
  } else if (SelfRefresh) {
    ExitSR (MrcData);
  }

  return;
}

/**
  Updates the value for following OptParamCliff variables:
  drrd2rd=0, ddrd2rd=1, drwr2wr=2, ddwr2wr=3, drrd2wr=4, ddrd2wr=5, drwr2rd=6, ddwr2rd=7,
  rdodtd=8, wrodtd=9, mcodts=10, mcodtd=11, rtl=12}

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel to update the specificed parameter.
  @param[in]     Byte       - Byte to update the specified parameter.
  @param[in]     OptParam   - Parameter to update.
  @param[in]     Off        - Value to offset the current setting.
  @param[in]     UpdateHost - Switch to update the host structure with the new value.
  @param[in]     SkipPrint  - Switch to skip debug prints.
  @param[in]     RankMask   - Bit mask of Ranks to update.

  @retval MrcStatus
**/
MrcStatus
UpdateTAParamOffset (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          Byte,
  IN     const UINT8          OptParam,
  IN     const UINT8          Off,
  IN     const UINT8          UpdateHost,
  IN     const UINT8          SkipPrint,
  IN     const UINT8          RankMask
  )
{
  MrcDebug                                *Debug;
  MrcIntOutput                            *MrcIntData;
  MrcOutput                               *Outputs;
  MrcChannelOut                           *ChannelOut;
  MrcIntChannelOut                        *IntChannelOut;
  UINT8                                   Rank;
  UINT8                                   IoLatency;
  INT8                                    New;
  UINT32                                  Offset1;
  BOOLEAN                                 Ddr4;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT            TcRdRd;
  MCHBAR_CH0_CR_TC_WRWR_STRUCT            TcWrWr;
  MCHBAR_CH0_CR_TC_WRRD_STRUCT            TcWrRd;
  MCHBAR_CH0_CR_TC_RDWR_STRUCT            TcRdWr;
  MCHBAR_CH0_CR_TC_ODT_STRUCT             TcOdt;
  DDRDATA0CH0_CR_DDRCRDATACONTROL1_STRUCT DdrDataControl1;
  MrcStatus                               Status;

  Status        = mrcSuccess;
  MrcIntData    = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ChannelOut    = &Outputs->Controller[0].Channel[Channel];
  IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  switch (OptParam) {
    case drrd2rd:
      //
      // Different Rank RD 2 RD Turn Around offsets
      //
      TcRdRd.Data          = IntChannelOut->MchbarTcRdRd.Data;
      TcRdRd.Bits.tRDRD_dr = Off;
      Offset1 = MCHBAR_CH0_CR_TC_RDRD_REG + ((MCHBAR_CH1_CR_TC_RDRD_REG - MCHBAR_CH0_CR_TC_RDRD_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcRdRd.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcRdRd.Data = TcRdRd.Data;
      }
      break;

    case ddrd2rd:
      //
      // Different DIMM RD 2 RD Turn Around offsets
      //
      TcRdRd.Data          = IntChannelOut->MchbarTcRdRd.Data;
      TcRdRd.Bits.tRDRD_dd = Off;
      Offset1 = MCHBAR_CH0_CR_TC_RDRD_REG + ((MCHBAR_CH1_CR_TC_RDRD_REG - MCHBAR_CH0_CR_TC_RDRD_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcRdRd.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcRdRd.Data = TcRdRd.Data;
      }
      break;

    case drwr2wr:
      //
      // Different Rank WR 2 WR Turn Around offsets
      //
      TcWrWr.Data          = IntChannelOut->MchbarTcWrWr.Data;
      TcWrWr.Bits.tWRWR_dr = Off;
      Offset1 = MCHBAR_CH0_CR_TC_WRWR_REG + ((MCHBAR_CH1_CR_TC_WRWR_REG - MCHBAR_CH0_CR_TC_WRWR_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcWrWr.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcWrWr.Data = TcWrWr.Data;
      }
      break;

    case ddwr2wr:
      //
      // Different DIMM WR 2 WR Turn Around offsets
      //
      TcWrWr.Data          = IntChannelOut->MchbarTcWrWr.Data;
      TcWrWr.Bits.tWRWR_dd = Off;
      Offset1 = MCHBAR_CH0_CR_TC_WRWR_REG + ((MCHBAR_CH1_CR_TC_WRWR_REG - MCHBAR_CH0_CR_TC_WRWR_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcWrWr.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcWrWr.Data = TcWrWr.Data;
      }
      break;

    case drrd2wr:
      //
      // Different Rank RD 2 WR Turn Around offsets
      //
      TcRdWr.Data          = IntChannelOut->MchbarTcRdWr.Data;
      TcRdWr.Bits.tRDWR_dr = Off;
      Offset1 = MCHBAR_CH0_CR_TC_RDWR_REG + ((MCHBAR_CH1_CR_TC_RDWR_REG - MCHBAR_CH0_CR_TC_RDWR_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcRdWr.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcRdWr.Data = TcRdWr.Data;
      }
      break;

    case ddrd2wr:
      //
      // Different DIMM RD 2 WR Turn Around offsets
      //
      TcRdWr.Data          = IntChannelOut->MchbarTcRdWr.Data;
      TcRdWr.Bits.tRDWR_dd = Off;
      Offset1 = MCHBAR_CH0_CR_TC_RDWR_REG + ((MCHBAR_CH1_CR_TC_RDWR_REG - MCHBAR_CH0_CR_TC_RDWR_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcRdWr.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcRdWr.Data = TcRdWr.Data;
      }
      break;

    case drwr2rd:
      //
      // Different Rank WR 2 RD Turn Around offsets
      //
      TcWrRd.Data          = IntChannelOut->MchbarTcWrRd.Data;
      TcWrRd.Bits.tWRRD_dr = Off;
      Offset1 = MCHBAR_CH0_CR_TC_WRRD_REG + ((MCHBAR_CH1_CR_TC_WRRD_REG - MCHBAR_CH0_CR_TC_WRRD_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcWrRd.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcWrRd.Data = TcWrRd.Data;
      }
      break;

    case ddwr2rd:
      //
      // Different DIMM WR 2 RD Turn Around offsets
      //
      TcWrRd.Data          = IntChannelOut->MchbarTcWrRd.Data;
      TcWrRd.Bits.tWRRD_dd = Off;
      Offset1 = MCHBAR_CH0_CR_TC_WRRD_REG + ((MCHBAR_CH1_CR_TC_WRRD_REG - MCHBAR_CH0_CR_TC_WRRD_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcWrRd.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcWrRd.Data = TcWrRd.Data;
      }
      break;

    case rdodtd:
      TcOdt.Data                    = IntChannelOut->MchbarTcOdt.Data;
      TcOdt.Bits.ODT_read_duration  = Off - 6; // Convert into Register values. 2'b00 = BL/2 + 2 (6 DCLKs
      Offset1 = MCHBAR_CH0_CR_TC_ODT_REG +
        ((MCHBAR_CH1_CR_TC_ODT_REG - MCHBAR_CH0_CR_TC_ODT_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcOdt.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcOdt.Data = TcOdt.Data;
      }
      break;

    case wrodtd:
      TcOdt.Data = IntChannelOut->MchbarTcOdt.Data;
      if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3) {//TODO:check
        TcOdt.Bits.ODT_write_duration = Off - 6; // Convert into Register values. 2'b00 = BL/2 + 2 (6 DCLKs
      } else {
        TcOdt.Bits.ODT_write_duration = Off - 6; // Convert into Register values. 2'b00 = BL/2 + 2 (6 DCLKs
      }
      Offset1 = MCHBAR_CH0_CR_TC_ODT_REG +
        ((MCHBAR_CH1_CR_TC_ODT_REG - MCHBAR_CH0_CR_TC_ODT_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcOdt.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcOdt.Data = TcOdt.Data;
      }
      break;

    case mcodts:
      //
      // MC ODT delay
      //
      DdrDataControl1.Data  = IntChannelOut->DqControl1[Byte].Data;
      New                   = MrcSE ((UINT8) DdrDataControl1.Bits.OdtDelay, 4, 8) + Off; // SignExtend
      if (New < -4) {
        New = -4; // RcvEnPi[8:6] - 5 qclk Min
      } else if (New > 6) {
        New = 6; // RcvEnPi[8:6] + 5 qclk Max
      }

      DdrDataControl1.Bits.OdtDelay       = New;
      DdrDataControl1.Bits.SenseAmpDelay  = New;
      Offset1 = MrcGetOffsetDataControl1 (MrcData, Channel, Byte);
      MrcWriteCR (MrcData, Offset1, DdrDataControl1.Data);
      if (UpdateHost) {
        IntChannelOut->DqControl1[Byte].Data = DdrDataControl1.Data;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (SkipPrint) ? "" : "%d\t", New);
      break;

    case mcodtd:
      //
      // Duration
      //
      DdrDataControl1.Data  = IntChannelOut->DqControl1[Byte].Data;
      New                   = (UINT8) DdrDataControl1.Bits.OdtDuration + Off;
      if (New < 0) {
        New = 0; // 11 tQCK Min
      } else if (New > DDRDATA0CH0_CR_DDRCRDATACONTROL1_OdtDuration_MAX) {
        New = DDRDATA0CH0_CR_DDRCRDATACONTROL1_OdtDuration_MAX; // 18 tQCK Max
      }

      DdrDataControl1.Bits.OdtDuration      = New;
      DdrDataControl1.Bits.SenseAmpDuration = New;
      //
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "mcodtd CRValue = 0x%x\n", DdrDataControl1.Bits.OdtDuration);
      //
      Offset1 = MrcGetOffsetDataControl1 (MrcData, Channel, Byte);
      MrcWriteCR (MrcData, Offset1, DdrDataControl1.Data);
      if (UpdateHost) {
        IntChannelOut->DqControl1[Byte].Data = DdrDataControl1.Data;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (SkipPrint) ? "" : "%d\t", DdrDataControl1.Bits.OdtDuration);
      break;

    case rtl:
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (RankMask & (1 << Rank)) {
          //
          // Keep RecvEn in place - adjust IoLatency by RTL delta
          //
          IoLatency = ChannelOut->IoLatency[Rank] - (ChannelOut->RTLatency[Rank] - Off);
          if ((INT8) IoLatency < 0) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\nERROR: IOLatency truncated at %s!\n", "zero");
            IoLatency = 0;
            Status = mrcFail;
            break;
          } else if (IoLatency > MCHBAR_CH0_CR_SC_IO_LATENCY_Rank_0_flyby_MAX) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\nERROR: IOLatency truncated at %s!\n", "max");
            IoLatency = MCHBAR_CH0_CR_SC_IO_LATENCY_Rank_0_flyby_MAX;
            Status = mrcFail;
            break;
          }

          ChannelOut->RTLatency[Rank] = Off;
          ChannelOut->IoLatency[Rank] = IoLatency;
          //
          // Write values from host to HW
          //
          MrcHalSetIoLatency (MrcData, Channel);
          MrcHalSetRoundtripLatency (MrcData, Channel);
        }
      }
      break;

    case srrd2rd:
      //
      // Same Rank RD 2 RD Turn Around offsets
      //
      TcRdRd.Data          = IntChannelOut->MchbarTcRdRd.Data;
      TcRdRd.Bits.tRDRD_sg = Off;
      TcRdRd.Bits.tRDRD_dg = Off;
      Offset1 = MCHBAR_CH0_CR_TC_RDRD_REG + ((MCHBAR_CH1_CR_TC_RDRD_REG - MCHBAR_CH0_CR_TC_RDRD_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcRdRd.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcRdRd.Data = TcRdRd.Data;
      }
      break;

    case srrd2wr_sg:
      //
      // Same Rank RD 2 WR Turn Around offsets - Same Group
      //
      TcRdWr.Data          = IntChannelOut->MchbarTcRdWr.Data;
      TcRdWr.Bits.tRDWR_sg = Off;
      if (!Ddr4) {
        TcRdWr.Bits.tRDWR_dg = Off; // Keep DG and SG equal for non-DDR4
      }
      Offset1 = MCHBAR_CH0_CR_TC_RDWR_REG + ((MCHBAR_CH1_CR_TC_RDWR_REG - MCHBAR_CH0_CR_TC_RDWR_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcRdWr.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcRdWr.Data = TcRdWr.Data;
      }
      break;

    case srrd2wr_dg:
      //
      // Same Rank RD 2 WR Turn Around offsets - Different Group
      //
      TcRdWr.Data          = IntChannelOut->MchbarTcRdWr.Data;
      TcRdWr.Bits.tRDWR_dg = Off;
      Offset1 = MCHBAR_CH0_CR_TC_RDWR_REG + ((MCHBAR_CH1_CR_TC_RDWR_REG - MCHBAR_CH0_CR_TC_RDWR_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcRdWr.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcRdWr.Data = TcRdWr.Data;
      }
      break;

    case srwr2rd_sg:
      //
      // Same Rank WR 2 RD Turn Around offsets - Same Group
      //
      TcWrRd.Data          = IntChannelOut->MchbarTcWrRd.Data;
      TcWrRd.Bits.tWRRD_sg = Off;
      if (!Ddr4) {
        TcWrRd.Bits.tWRRD_dg = Off; // Keep DG and SG equal for non-DDR4
      }
      Offset1 = MCHBAR_CH0_CR_TC_WRRD_REG + ((MCHBAR_CH1_CR_TC_WRRD_REG - MCHBAR_CH0_CR_TC_WRRD_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcWrRd.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcWrRd.Data = TcWrRd.Data;
      }
      break;

    case srwr2rd_dg:
      //
      // Same Rank WR 2 RD Turn Around offsets - Different Group
      //
      TcWrRd.Data          = IntChannelOut->MchbarTcWrRd.Data;
      TcWrRd.Bits.tWRRD_dg = Off;
      Offset1 = MCHBAR_CH0_CR_TC_WRRD_REG + ((MCHBAR_CH1_CR_TC_WRRD_REG - MCHBAR_CH0_CR_TC_WRRD_REG) * Channel);
      MrcWriteCR (MrcData, Offset1, TcWrRd.Data);
      if (UpdateHost) {
        IntChannelOut->MchbarTcWrRd.Data = TcWrRd.Data;
      }
      break;

    default:
      break;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    ((OptParam != mcodtd) && (OptParam != mcodts) && (!SkipPrint)) ? "%d\t" : "",
    Off
    );

  return Status;
}

/**
  This function applies the new DRAM ODT settings
  Walks through various optimizations to get the best result with new ODT values
  This includes WrDS, RdODT, Eq, etc.
  Updates Best* variables if this point if better than the prior points
  chDone is both an input and output.  Reports which channels have a good enough value
  if SkipRd is high, it will skip the read related functions (RdODT, RdEq, RdTiming)

  @param[in]     MrcData              - Include all MRC global data.
  @param[in,out] DimmOptPoints        - Structure of all the DIMM ODT optimal settings.
  @param[in]     ChMask               - Channel to work on.
  @param[in]     RankMask             - Rank to work on.
  @param[in]     OptParamTestList     - List of Opt test(Drive Strength, RxBias, TxEq, RxEq) to run.
  @param[in]     OptParamTestListSize - Size of OptParamTestList.
  @param[in]     SubOptMode           - Training for power or for margin for suboptimizations.
  @param[in]     skipOptTests         - Skips the suboptimization.
  @param[in]     skipOptPrint         - Skip printing of the suboptimization steps.
  @param[in]     RdCenter             - Switch to recenter read.
  @param[in]     WrCenter             - Switch to recenter write.

  @retval mrcSuccess or mrcWrongInputParameter.
**/
MrcStatus
TrainDimmOdtSetting (
  IN     MrcParameters *const MrcData,
  IN OUT DimmOptPoint         *DimmOptPoints,
  IN     UINT8                ChMask,
  IN     UINT8                RankMask,
  IN     UINT8                *OptParamTestList,
  IN     UINT8                OptParamTestListSize,
  IN     TrainingModeType     SubOptMode,
  IN     BOOLEAN              skipOptTests,
  IN     BOOLEAN              skipOptPrint,
  IN     BOOLEAN              RdCenter,
  IN     BOOLEAN              WrCenter
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  DimmOptPoint      *PointResults;
  MrcIntOutput      *MrcIntData;
  OptOffsetChByte   BestOffArr[MAX_RANK_IN_CHANNEL];
  UINT8             UPMOptimize[MAX_TRADEOFF_TYPES];
  UINT8             rank;
  UINT8             GlobalRankMask;
  UINT8             LocalRanks[MAX_CHANNEL];
  UINT8             ChBitMask;
  UINT8             Channel;
  //  UINT8             TestListFull[] = { RdV, RdT, WrV, WrT }; // List of parameters to margin
  UINT8             TestListRd[]  = { RdV, RdT };
  UINT8             TestListWr[]  = { WrV, WrT };
  UINT8             *TestList;
  UINT8             TestListSize;
  UINT8             Scale3Test[]      = { 1, 2, 1, 0, 0 };
  UINT8             TestListRdLpddr[] = { RdV, RdT, RcvEnaX };
  UINT8             ScaleRdLpddr[]    = { 1, 2, 2, 1, 0 };
  UINT8             *Scale;
  UINT8             i;
  UINT8             t;
  UINT8             ResultType;
  UINT8             RecenterLC;
  UINT8             OptParamLC;
  UINT8             TestResultType[5];
  UINT8             OptParam[2];
  INT8              LStart[2];
  INT8              LStop[2];
  BOOLEAN           Lpddr3;
  INT8              GB;

  TestList      = TestListRd;
  TestListSize  = 0;
  RecenterLC    = 15;
  OptParamLC    = OPT_PARAM_LOOP_COUNT + 1;
  MrcIntData    = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Outputs       = &MrcData->Outputs;
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Lpddr3        = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  PointResults  = DimmOptPoints;
  MrcCall->MrcSetMem ((UINT8 *) BestOffArr, sizeof (BestOffArr), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) UPMOptimize, sizeof (UPMOptimize), 0);
  MrcCall->MrcSetMem ((UINT8 *) TestResultType, sizeof (TestResultType), 0);

  //
  // TrainDDROptParam already check the valid against host chRankBit mask
  // Walk through channels, check if this point is redundant, set RttNom
  //
  ChMask &= Outputs->ValidChBitMask;
  GlobalRankMask = 0;
  ChBitMask     = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    LocalRanks[Channel] = 0;
    if ((MRC_BIT0 << Channel) & ChMask) {
      LocalRanks[Channel] = RankMask & ControllerOut->Channel[Channel].ValidRankBitMask;
      if (LocalRanks[Channel]) {
        ChBitMask |= MRC_BIT0 << Channel; // remove ch with no "active" ranks
        GlobalRankMask |= LocalRanks[Channel];
      }
    }
  }

  if (RdCenter) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Read Vref\n");
    ReadVoltageCentering2D (
      MrcData,
      Outputs->MarginResult,
      ChBitMask,
      RdV,
      0,
      0,
      RecenterLC,
      0
      );
    //
    // @todo: We can add if status fail go to next point.
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Read Timing ChBitMask=%x\n", ChBitMask);
    DataTimeCentering2D (
      MrcData,
      Outputs->MarginResult,
      ChBitMask,
      RdT,
      0, // EnPerBit,
      0, // EnRxDutyCycle
      0, // ResetPerBit
      RecenterLC,
      0  // En2D
      );
  }

  if (WrCenter) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Write Vref\n");
    MrcWriteVoltageCentering2D (MrcData);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Write Timing ChBitMask=%x\n", ChBitMask);
    DataTimeCentering2D (
      MrcData,
      Outputs->MarginResult, // prev. margin results
      ChBitMask,
      WrT,
      0, // EnPerBit,
      0, // EnRxDutyCycle
      0, // ResetPerBit
      RecenterLC,
      0  // En2D
      );
  }
  //
  // @todo: we could check here if we have some reasonable amount of margin to play with
  //

  //
  // Check if we need to ignore the power column
  //
  if (SubOptMode == MrcTmMargin) {
    ScaleRdLpddr[3] = 0;
    Scale3Test[2]   = 0;
  }

  PointResults->OptParamTestListSize = OptParamTestListSize;
  for (t = 0; t < OptParamTestListSize; t++) {
    Scale = Scale3Test; // Assume base scale.  Update for LPDDR3 during OptRdOdt
    PointResults->OptParamTestList[t] = OptParamTestList[t];
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "OptParamTestList[%d]=%d , %s\n",t,OptParamTestList[t],TOptParamOffsetString[OptParamTestList[t]]);
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "OptParamTestList[%d]=%d OptParamTestListSize=%d\n",t,OptParamTestList[t],OptParamTestListSize);
    OptParam[0] = OptParamTestList[t];
    switch (OptParamTestList[t]) {
      case (OptWrDS) :
        TestList = TestListWr;
        TestListSize = ARRAY_COUNT (TestListWr);
        LStart[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
        LStop[0]  = OptParamLimitValue (MrcData, OptParam[0], 1);
        TrainDDROptParam (
          MrcData,
          &BestOffArr[0],
          ChBitMask,
          GlobalRankMask,
          OptParam,
          1,
          FullGrid,
          TestList,
          TestListSize,
          Scale,
          UPMOptimize,
          LStart,
          LStop,
          OptParamLC,
          1,  // Repeats
          skipOptPrint,
          skipOptTests,
          0,  // RdRd2Test
          1   // GuardBand
          );
        MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[WrDSOfft][0], (UINT8 *) &BestOffArr[0], sizeof (BestOffArr[0])); // Result in Rank 0
        break;

      case (OptRdOdt) :
        if (Lpddr3) {
          TestList = TestListRdLpddr;
          TestListSize = ARRAY_COUNT (TestListRdLpddr);
          Scale = ScaleRdLpddr; // does also RcvEnX
        } else {
          TestList = TestListRd;
          TestListSize = ARRAY_COUNT (TestListRd);
        }
        if (Inputs->EnVttOdt) {
          Scale[3] = 0;  //in Vtt mode Odt dont effect power go for best margins
        }
        LStart[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
        LStop[0]  = OptParamLimitValue (MrcData, OptParam[0], 1);
        TrainDDROptParam (
          MrcData,
          &BestOffArr[0],
          ChBitMask,
          GlobalRankMask,
          OptParam,
          1,
          FullGrid,
          TestList,
          TestListSize,
          Scale,
          UPMOptimize,
          LStart,
          LStop,
          OptParamLC,
          1,            // Repeats
          skipOptPrint,
          skipOptTests,
          Lpddr3 ? RdRdTA_All : RdRdTA,       // RdRd2Test
          0             // GuardBand
          );
        MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[RdOdtOfft][0], (UINT8 *) &BestOffArr[0], sizeof (BestOffArr[0])); // Result in Rank 0
        break;

      case (OptSComp) :
      case (OptTComp) :
        break;

      case (OptTxEq) :
        TestList = TestListWr;
        TestListSize = ARRAY_COUNT (TestListWr);
        LStart[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
        LStop[0]  = OptParamLimitValue (MrcData, OptParam[0], 1);
        for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
          if (!((MRC_BIT0 << rank) & GlobalRankMask)) {
            continue; // check if rank at least on one channel
          }

          TrainDDROptParam (
            MrcData,
            &BestOffArr[rank],
            ChBitMask,
            (MRC_BIT0 << rank),
            OptParam,
            1,
            FullGrid,
            TestList,
            TestListSize,
            Scale,
            UPMOptimize,
            LStart,
            LStop,
            OptParamLC,
            1,            // Repeats
            skipOptPrint,
            skipOptTests,
            0,            // RdRd2Test
            1             // GuardBand
            );
          //MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[TxEqOfft][rank], (UINT8 *) &BestOffArr[rank], sizeof (BestOffArr[rank]));
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!((MRC_BIT0 << rank) & LocalRanks[Channel])) {
              continue;
              //
              // check if the rank exist in this ch
              //
            }
            for (i = 0; i < TestListSize; i++) {
              //
              // track min margin per ch
              //
              if (BestOffArr[rank].Margins[i][Channel] < BestOffArr[0].Margins[i][Channel]) {
                BestOffArr[0].Margins[i][Channel] = BestOffArr[rank].Margins[i][Channel];
              }
            }
          }
        }
        // copy min result for rank 0
        MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[TxEqOfft][0], (UINT8 *) &BestOffArr[0], sizeof (BestOffArr[0]));
        break;

      case (OptTxEqWrDS) :
        OptParam[0] = OptTxEq;
        OptParam[1] = OptWrDS;
        TestList = TestListWr;
        TestListSize = ARRAY_COUNT (TestListWr);
        LStart[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
        LStop[0]  = OptParamLimitValue (MrcData, OptParam[0], 1);
        LStart[1] = OptParamLimitValue (MrcData, OptParam[1], 0);
        LStop[1]  = OptParamLimitValue (MrcData, OptParam[1], 1);
        GB = 0;
        if (Inputs->PowerTrainingMode == MrcTmPower) {
          if ((Inputs->VccIomV > 900) && (Outputs->Frequency > f1600)) {
            GB = 3;
          } else {
            GB = 1;
          }
        }

        TrainDDROptParam (
          MrcData,
          &BestOffArr[0],
          ChBitMask,
          GlobalRankMask,
          OptParam,
          2,
          ChessEven,
          TestList,
          TestListSize,
          Scale,
          UPMOptimize,
          LStart,
          LStop,
          OptParamLC + 1, // @todo adjust lc by rank population
          1,            // Repeats
          skipOptPrint,
          skipOptTests,
          0,            // RdRd2Test
          GB            // GuardBand
          );

        MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[WrDSOfft][0], (UINT8 *) &BestOffArr[0], sizeof (BestOffArr[0])); // Result in Rank 0
        break;

      case (OptRxEq) :
        TestList = TestListRd;
        TestListSize = ARRAY_COUNT (TestListRd);
        LStart[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
        LStop[0]  = OptParamLimitValue (MrcData, OptParam[0], 1);
        for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
          if (!((MRC_BIT0 << rank) & GlobalRankMask)) {
            continue; // check if rank at least on one channel
          }

          TrainDDROptParam (
            MrcData,
            &BestOffArr[rank],
            ChBitMask,
            (MRC_BIT0 << rank),
            OptParam,
            1,
            FullGrid,
            TestList,
            TestListSize,
            Scale,
            UPMOptimize,
            LStart,
            LStop,
            OptParamLC,
            1,       // Repeats
            skipOptPrint,
            skipOptTests,
            RdRdTA,  // RdRd2Test
            0        // GuardBand
            );
          //MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[RxEqOfft][rank], (UINT8 *) &BestOffArr[rank], sizeof (BestOffArr[rank]));
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!((1 << rank) & LocalRanks[Channel])) {
              continue; // check if the rank exist in this ch
            }

            for (i = 0; i < ARRAY_COUNT (TestListRd); i++) {
              //
              // track min margin per ch and asign to rank0
              //
              if (BestOffArr[rank].Margins[i][Channel] < BestOffArr[0].Margins[i][Channel]) {
                BestOffArr[0].Margins[i][Channel] = BestOffArr[rank].Margins[i][Channel];
              }
            }
          }
        }
        // copy min result for rank 0
        MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[RxEqOfft][0], (UINT8 *) &BestOffArr[0], sizeof (BestOffArr[0]));
        break;

      case (OptRxBiasCb) :
        TestList = TestListRd;
        TestListSize = ARRAY_COUNT (TestListRd);
        OptParam[0] = OptRxBias;
        OptParam[1] = OptRxCb;
        LStart[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
        LStop[0]  = OptParamLimitValue (MrcData, OptParam[0], 1);
        LStart[1] = OptParamLimitValue (MrcData, OptParam[1], 0);
        LStop[1]  = OptParamLimitValue (MrcData, OptParam[1], 1);

        TrainDDROptParam (
          MrcData,
          &BestOffArr[0],
          ChBitMask,
          GlobalRankMask,
          OptParam,
          2,
          ChessEven,
          TestList,
          TestListSize,
          Scale,
          UPMOptimize,
          LStart,
          LStop,
          OptParamLC,
          1,       // Repeats
          skipOptPrint,
          skipOptTests,
          RdRdTA,  // RdRd2Test
          0        // GuardBand
          );

        MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[RdSAmpOfft][0], (UINT8 *) &BestOffArr[0], sizeof (BestOffArr[0])); // Result in Rank 0
        break;

      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "OptParam Test not valid\n");
        return mrcWrongInputParameter;
    }

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(LocalRanks[Channel])) {
        continue; // check if the active rank run this ch
      }
      //
      // run through all BestOff[optParam][0] and track min[RdV,RdT,WrV,WrT]
      //
      for (i = 0; i < TestListSize; i++) {
        ResultType = GetMarginResultType (TestList[i]);
        if ((ResultType >= ARRAY_COUNT (TestResultType)) || (ResultType >= MAX_TRADEOFF_TYPES)) {
          return mrcFail;
        }
        TestResultType[ResultType] = TestList[i]; // indicate which test we run and create the reverse dic
        //
        //we need to update only last results
        //
        PointResults->Test[ResultType][Channel] = BestOffArr[0].Margins[i][Channel];
        //MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "BestOffArr[0].Margins[test index i=%d][%d] =%d\n", i, Channel, BestOffArr[0].Margins[i][Channel]);
      }
    }
  } // end for OptParamTest
  //
  // assign the point for passing to the FindOptimalTradeOff function
  //
  i                       = 0;
  PointResults->NumTests  = 0;
  for (t = 0; t < 4; t++) {
    if (TestResultType[t] == 0) {
      continue; // can only be 1,2,4,5 (WrV,RdV ..)
    } else {
      PointResults->TestList[i] = TestResultType[t];
      PointResults->NumTests++;
      //
      // sorting test for TradeOff
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(LocalRanks[Channel])) {
          continue; // check if the active rank run this ch
        }
        PointResults->Points2Trade[i][Channel] = PointResults->Test[t][Channel];
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "PointResults->TestList[%d]=%d PointResults->Test[test index=%d][channel=%d] =%d\n",i,PointResults->TestList[i],t,Channel,PointResults->Test[t][Channel]);
      }
      i++;
    }
  }
  //
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "PointResults->NumTests =%d\n",PointResults->NumTests);
  //
  return mrcSuccess;
}

/**
  This function applies an offset to the global compensation logic.
  Reruns Compensation and returns the new comp value

  @param[in,out] MrcData         - Include all MRC global data.
  @param[in]     param           - Parameter defining the desired global compensation logic
  @param[in]     offset          - Value to apply
  @param[in]     UpdateHost      - Desides if MrcData has to be updated

  @retval Returns the new comp value.
**/
UINT32
UpdateCompGlobalOffset (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          param,
  IN     const UINT32         offset,
  IN     const BOOLEAN        AjustOdtStatic,
  IN     const UINT8          UpdateHost
  )
{
  const MrcInput                          *Inputs;
  MrcDebug                                *Debug;
  MrcIntOutput                            *IntOutputs;
  MrcOutput                               *Outputs;
  MrcIntControllerOut                     *IntControllerOut;
  MrcIntChannelOut                        *IntChannelOut;
  DDRCOMP_CR_DDRCRCOMPCTL0_STRUCT         DdrCrCompCtl0;
  DDRCOMP_CR_DDRCRCOMPCTL1_STRUCT         DdrCrCompCtl1;
  DDRCOMP_CR_DDRCRDATACOMP0_STRUCT        DdrCrDataComp0;
  DDRCOMP_CR_DDRCRDATACOMP1_STRUCT        DdrCrDataComp1;
  DDRCOMP_CR_DDRCRCMDCOMP_STRUCT          DdrCrCmdComp;
  DDRCOMP_CR_DDRCRCTLCOMP_STRUCT          DdrCrCtlComp;
  DDRCOMP_CR_DDRCRCLKCOMP_STRUCT          DdrCrClkComp;
  DDRDATACH0_CR_DDRCRDATACONTROL0_STRUCT  DdrCrDataControl0;
  DDRCOMP_CR_DDRCRCOMPCTL0_STRUCT         DdrCrCompCtl0_Temp;
  UINT32                                  RegOffset;
  UINT8                                   Channel;

  IntOutputs             = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  Outputs                = &MrcData->Outputs;
  IntControllerOut       = &IntOutputs->Controller[0];
  Inputs                 = &MrcData->Inputs;
  Debug                  = &Outputs->Debug;
  DdrCrCompCtl0.Data     = IntControllerOut->CompCtl0.Data;
  DdrCrCompCtl1.Data     = IntControllerOut->CompCtl1.Data;
  DdrCrDataControl0.Data = 0;

  //
  // Update offset in local CR variable
  //
  switch (param) {
    case RdOdt:
      //
      // Disable FixOdt feature before changing this param
      //
      DdrCrCompCtl0.Bits.FixOdtD = 0;
      //
      // Apply Comp Offset to RdOdt
      //
      DdrCrCompCtl0.Bits.DqOdtVref = offset;
      break;

    case WrDS:
      //
      // Apply Comp Offset to WrDS-DQ
      //
      DdrCrCompCtl0.Bits.DqDrvVref = offset;
      break;

    case WrDSCmd:
      //
      // Apply Comp Offset to WrDS-CMD
      //
      DdrCrCompCtl0.Bits.CmdDrvVref = offset;
      break;

    case WrDSCtl:
      //
      // Apply Comp Offset to WrDS-CTL
      //
      DdrCrCompCtl0.Bits.CtlDrvVref = offset;
      break;

    case WrDSClk:
      //
      // Apply Comp Offset to WrDS-CLK
      //
      DdrCrCompCtl0.Bits.ClkDrvVref = offset;
      break;

    case SCompDq:
      //
      // Apply Comp Offset to Scomp-DQ
      //
      DdrCrCompCtl1.Bits.DqScompCells = offset;
      DdrCrCompCtl1.Bits.DqScompPC    = offset >> 4;
      break;

    case SCompCmd:
      //
      // Apply Comp Offset to Scomp-CMD
      //
      DdrCrCompCtl1.Bits.CmdScompCells  = offset;
      DdrCrCompCtl1.Bits.CmdScompPC     = offset >> 4;
      break;

    case SCompCtl:
      //
      // Apply Comp Offset to Scomp-CTL
      //
      DdrCrCompCtl1.Bits.CtlScompCells  = offset;
      DdrCrCompCtl1.Bits.CtlScompPC     = offset >> 4;
      break;

    case SCompClk:
      //
      // Apply Comp Offset to Scomp-CLK
      //
      DdrCrCompCtl1.Bits.ClkScompCells  = offset;
      DdrCrCompCtl1.Bits.ClkScompPC     = offset >> 4;
      break;

    case DisOdtStatic:
      //
      // disable static read Otd legs
      //
      DdrCrCompCtl0.Bits.DisableOdtStatic = offset;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        IntChannelOut = &IntControllerOut->Channel[Channel];
        DdrCrDataControl0.Data = IntChannelOut->DqControl0.Data;
        DdrCrDataControl0.Bits.DisableOdtStatic = offset; // apply to bytes fubs
        RegOffset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
        MrcWriteCrMulticast (MrcData, RegOffset, DdrCrDataControl0.Data);
        if (UpdateHost) {
          IntChannelOut->DqControl0.Data = DdrCrDataControl0.Data;
        }
      }
      break;

    default:
      break;
  }
  //
  // Update the Comp Offsets and Host Structure
  //
  MrcWriteCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL0_REG, DdrCrCompCtl0.Data);
  MrcWriteCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL1_REG, DdrCrCompCtl1.Data);
  if (UpdateHost) {
    IntControllerOut->CompCtl0.Data = DdrCrCompCtl0.Data;
    IntControllerOut->CompCtl1.Data = DdrCrCompCtl1.Data;
  }
  //
  // Run Compensation
  // Start Comp Engine
  //
  ForceRcomp (MrcData);
  if ((param == RdOdt) && (AjustOdtStatic)) {
    //
    // we check if we close to saturation and try dis/en the static legs
    //
    DdrCrDataComp1.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRDATACOMP1_REG);
    if ((DdrCrDataComp1.Bits.RcompOdtUp < 16) || (DdrCrDataComp1.Bits.RcompOdtUp > 48)) {
      //
      // disable/enable  static read Otd legs
      //
      if (DdrCrDataComp1.Bits.RcompOdtUp < 16) {
        DdrCrCompCtl0.Bits.DisableOdtStatic = 1;
      } else {
        DdrCrCompCtl0.Bits.DisableOdtStatic = 0;
      }
      //
      // Update the Comp Offsets and Host Structure
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        IntChannelOut = &IntControllerOut->Channel[Channel];
        IntChannelOut->DqControl0.Bits.DisableOdtStatic = DdrCrCompCtl0.Bits.DisableOdtStatic; // apply to bytes fubs
        RegOffset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
        //
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DdrCrDataControl0.Bits.DisableOdtStatic=%d\n",DdrCrDataControl0.Bits.DisableOdtStatic);
        //
        MrcWriteCrMulticast (MrcData, RegOffset, IntChannelOut->DqControl0.Data);
      }

      MrcWriteCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL0_REG, DdrCrCompCtl0.Data);
      //
      // host need to always be updated with static state
      //
      DdrCrCompCtl0_Temp.Data                  = IntControllerOut->CompCtl0.Data;
      DdrCrCompCtl0_Temp.Bits.DisableOdtStatic = DdrCrCompCtl0.Bits.DisableOdtStatic;
      IntControllerOut->CompCtl0.Data                   = DdrCrCompCtl0_Temp.Data;
      //
      // Run Compensation
      // Start Comp Engine
      //
      ForceRcomp (MrcData);
    }

  }
  //
  // Return the new comp code
  //
  switch (param) {
    case DisOdtStatic:
    case RdOdt:
      DdrCrDataComp1.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRDATACOMP1_REG);
      //
      // re-Enable FixOdt feature after changing this param
      //
      DdrCrCompCtl0.Bits.DqOdtUpDnOff = DdrCrDataComp1.Bits.RcompOdtDown - DdrCrDataComp1.Bits.RcompOdtUp;
      DdrCrCompCtl0.Bits.FixOdtD      = 1;
      MrcWriteCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL0_REG, DdrCrCompCtl0.Data);
      if (UpdateHost) {
        IntControllerOut->CompCtl0.Data = DdrCrCompCtl0.Data;
      }
      return DdrCrDataComp1.Bits.RcompOdtUp;

    case WrDS:
    case SCompDq:
      DdrCrDataComp0.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRDATACOMP0_REG);
      return (param == WrDS) ? DdrCrDataComp0.Bits.RcompDrvUp : DdrCrDataComp0.Bits.SlewRateComp;

    case WrDSCmd:
    case SCompCmd:
      DdrCrCmdComp.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRCMDCOMP_REG);
      return (param == WrDSCmd) ? DdrCrCmdComp.Bits.RcompDrvUp : DdrCrCmdComp.Bits.Scomp;

    case WrDSCtl:
    case SCompCtl:
      DdrCrCtlComp.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRCTLCOMP_REG);
      return (param == WrDSCtl) ? DdrCrCtlComp.Bits.RcompDrvUp : DdrCrCtlComp.Bits.Scomp;

    case WrDSClk:
    case SCompClk:
      DdrCrClkComp.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRCLKCOMP_REG);
      return (param == WrDSClk) ? DdrCrClkComp.Bits.RcompDrvUp : DdrCrClkComp.Bits.Scomp;

    default:
      break;
  }

  return 0;
}

/**
  Programs Delay/Duration for the SenseAmp and MCODT based on RcvEn timing
  Provide GuardBand > 0 if needed to be more conservative in timing
  Main goal is to optimize power

  @param[in,out] MrcData   - Include all MRC global data.
  @param[in]     GuardBand - Input parameter with more conservative value

  @retval Nothing
**/
void
UpdateSampOdtTiming (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          GuardBand
  )
{
  MrcIntOutput                            *IntOutputs;
  MrcOutput                               *Outputs;
  MrcDebug                                *Debug;
  MrcControllerOut                        *ControllerOut;
  MrcChannelOut                           *ChannelOut;
  MrcIntChannelOut                        *IntChannelOut;
  UINT16                                  *CurRcvEn;
  UINT8                                   Channel;
  UINT8                                   Byte;
  UINT8                                   rank;
  UINT16                                  MaxRcvEn;
  UINT16                                  MinRcvEn;
  UINT32                                  Offset;
  UINT32                                  SWakeUp;
  UINT32                                  SAWakeUppS;  // Round up to nearest Qclk
  INT8                                    SOn;         // SenseAmpDelay
  INT8                                    OOn;         // OdtDelay
  INT32                                   SOff;        // SenseAmpDuration
  INT32                                   OOff;        // OdtDuration
  DDRDATA0CH0_CR_DDRCRDATACONTROL1_STRUCT *DqControl1;

  IntOutputs    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  SAWakeUppS    = 1250;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "UpdateSampOdtTiming: GuardBand = %d\n", GuardBand);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut    = &Outputs->Controller[0].Channel[Channel];
      IntChannelOut = &IntOutputs->Controller[0].Channel[Channel];
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch %d\tOdtOn\tOdtOff\tSAmpOn\tSAmpOff\n", Channel);

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MaxRcvEn  = 0;
        MinRcvEn  = 512;

        for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
          if (MrcRankInChannelExist (MrcData, rank, Channel)) {
            CurRcvEn = &ChannelOut->RcvEn[rank][Byte];
            if (MaxRcvEn < *CurRcvEn) {
              MaxRcvEn = *CurRcvEn;
            }

            if (MinRcvEn > *CurRcvEn) {
              MinRcvEn = *CurRcvEn;
            }
          }
        }
        //
        // Round Max to nearest cycle
        //
        MaxRcvEn = (MaxRcvEn >> 6) + 1;

        //
        // SENSE AMP CAN ONLY BE ON WHEN ODT IS ON FOR EOS REASONS.
        // SWakeUp = (UINT32)( (SAWakeUppS + Outputs->Qclkps - 1) / Outputs->Qclkps );
        // SOn = MinRcvEn - SWakeUp - GuardBand;
        // OOn = MinRcvEn - 2 - GuardBand;
        //
        SWakeUp = (UINT32) ((64 * SAWakeUppS) / Outputs->Qclkps); // Convert to PI codes
        //
        // Turn On ODT & Samp at least 2 Qclks before earlier RcvEn Rise
        //
        if (SWakeUp < 128) {
          SWakeUp = 128; // at least 2-Qclks
        }

        OOn = SOn = (INT8) ((MinRcvEn - SWakeUp) >> 6) - GuardBand;
        //
        // SenseAmp Delay
        //
        if (SOn < -4) {
          SOn = -4; // RcvEnPi[8:6] - 5 qclk
        } else if (SOn > 6) {
          SOn = 6; // RcvEnPi[8:6] + 5 qclk
        }
        //
        // OdtDelay
        //
        if (OOn < -4) {
          OOn = -4; // RcvEnPi[8:6] - 5 qclk
        } else if (OOn > 6) {
          OOn = 6; // RcvEnPi[8:6] + 5 qclk
        }
        //
        // Turn Off Samp 1 qclk after postamble
        // Turn Off ODT 1 qclk after postamble
        // Program the duration to leave Odt/Samp On
        //      OnBeforeRcvEn   BL+Post  AfterPost   CR Encoding
        //
        SOff  = (MaxRcvEn - SOn) + (8 + 1) + 1 + GuardBand - 11;
        OOff  = (MaxRcvEn - OOn) + (8 + 1) + 1 + GuardBand - 11;

        if (SOff < 0) {
          SOff = 0; // 11 tQCK Min
        } else if (SOff > 7) {
          SOff = 7; // 18 tQCK Max
        }

        if (OOff < 0) {
          OOff = 0;  // 11 tQCK Min
        } else if (OOff > 7) {
          OOff = 7;  // 18 tQCK mAx
        }

        DqControl1 = &IntChannelOut->DqControl1[Byte];
        DqControl1->Bits.OdtDelay         = OOn;
        DqControl1->Bits.OdtDuration      = OOff;
        DqControl1->Bits.SenseAmpDelay    = SOn;
        DqControl1->Bits.SenseAmpDuration = SOff;
        Offset = MrcGetOffsetDataControl1 (MrcData, Channel, Byte);
        MrcWriteCR (MrcData, Offset, DqControl1->Data);

        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "%d:\t%d\t%d\t%d\t%d\n",
          Byte,
          DqControl1->Bits.OdtDelay,
          DqControl1->Bits.OdtDuration,
          DqControl1->Bits.SenseAmpDelay,
          DqControl1->Bits.SenseAmpDuration
          );
      }
    }
  }

  return;
}

/**
  Turns off unused portions of the slave DLL to save power

  @param[in,out] MrcData - Include all MRC global data.

  @retval Nothing
**/
void
UpdateSlaveDLLLength (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcIntOutput        *IntOutputs;
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcIntControllerOut *IntControllerOut;
  MrcIntChannelOut    *IntChannelOut;
  UINT8             *CurRxDqs;
  UINT32            Offset;
  UINT8             Channel;
  UINT8             byte;
  UINT8             rank;
  UINT8             MaxPi;

  IntOutputs       = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  Outputs          = &MrcData->Outputs;
  ControllerOut    = &Outputs->Controller[0];
  IntControllerOut = &IntOutputs->Controller[0];
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut    = &ControllerOut->Channel[Channel];
      IntChannelOut = &IntControllerOut->Channel[Channel];
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        MaxPi = 0;
        for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
          if (MrcRankInChannelExist (MrcData, rank, Channel)) {
            CurRxDqs = &ChannelOut->RxDqsP[rank][byte];
            if (MaxPi < *CurRxDqs) {
              MaxPi = *CurRxDqs;
            }

            CurRxDqs = &ChannelOut->RxDqsN[rank][byte];
            if (MaxPi < *CurRxDqs) {
              MaxPi = *CurRxDqs;
            }
          }
        }
        //
        // Update SlaveDLL Length for power Savings
        // Calculate which segments to turn off:
        // NEW (OFF: 0, PI<48: 0x2, PI<32: 0x4, PI<16: 0x6)
        // results are:   0, 2 , 4 or 6
        //
        IntChannelOut->DqControl1[byte].Bits.SdllSegmentDisable = ((7 - (MaxPi >> 3)) &~MRC_BIT0);
        Offset = MrcGetOffsetDataControl1 (MrcData, Channel, byte);
        MrcWriteCR (MrcData, Offset, IntChannelOut->DqControl1[byte].Data);
      }
    }
  }

  return;
}

/**
  This function Shifts the CMD timing.
  NOTE: ONLY one, ResetDDR or SelfRefresh can be set inside this function

  @param[in,out] MrcData     - Include all MRC global data.
  @param[in]     Ranks       - Parameter defining the desired global compensation logic
  @param[in]     offset      - per channel Value to shift picode for
  @param[in]     ResetDDR    - Do we reset DDR?
  @param[in]     SelfRefresh - Do we perform Self refresh?
  @param[in]     UpdateHost  - Determines if MrcData has to be updated
  @param[in]     SkipTx      - Determines if TX update should be skipped
                               @todo: SkipTx is NOT USED at this time and we don't skip it anyway

  @retval MrcStatus       - If it succeeds return mrcSuccess
**/
MrcStatus
ShiftCh2Ch (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Ranks,
  IN     const UINT8 *const   offset,
  IN     UINT8                ResetDDR,
  IN     const UINT8          SelfRefresh,
  IN     const UINT8          UpdateHost,
  IN     const UINT8          SkipTx
  )
{
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcStatus         Status;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             RankMaskCh;
  INT32             NewValue;
  INT32             Offset;
  BOOLEAN           Lpddr;
  UINT32            RegOffset;
  MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_STRUCT MiscCkeCtrl;

  Status        = mrcSuccess;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Lpddr         = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);

  if (SelfRefresh && ResetDDR) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "WARNING SelfRefresh OR ResetDDR can be set at once...performing SelfRefresh\n"
      );
    ResetDDR = 0;
  }

  if (SelfRefresh) {
    EnterSR (MrcData);
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }

    ChannelOut = &ControllerOut->Channel[Channel];
    RankMaskCh = Ranks & ChannelOut->ValidRankBitMask;

    if (RankMaskCh == 0) {
      continue;
    }

    if (Lpddr) {
      // Lower CKE, we will change CLK PI while DRAM is in Power Down
      MiscCkeCtrl.Data = 0;
      MiscCkeCtrl.Bits.CKE_Override = 0x0F;
      MiscCkeCtrl.Bits.CKE_On       = 0;
      RegOffset = OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG,MCHBAR_CH1_CR_REUT_CH_MISC_CKE_CTRL_REG, Channel);
      MrcWriteCR (MrcData, RegOffset, MiscCkeCtrl.Data);
    }

    Offset = offset[Channel];

    //
    // Shift CLK (this will shift DQ PIs as well)
    //
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, RankMaskCh, 3, Offset, UpdateHost);

    //
    // Shift CTL
    //
    NewValue = 0;
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (RankMaskCh & (1 << Rank)) {
        NewValue = ChannelOut->CtlPiCode[Rank] + Offset;
        break;
      }
    }

    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, RankMaskCh, 1, NewValue, UpdateHost);

    //
    // Shift CmdS
    //
    ShiftPIforCmdTraining (
      MrcData,
      Channel,
      MrcIterationCmdS,
      RankMaskCh,
      1,
      ChannelOut->CmdsCmdPiCode[0] + Offset,
      UpdateHost
      );

    //
    // Shift CmdN
    //
    ShiftPIforCmdTraining (
      MrcData,
      Channel,
      MrcIterationCmdN,
      RankMaskCh,
      1,
      ChannelOut->CmdnCmdPiCode[0] + Offset,
      UpdateHost
      );

    if (Lpddr) {
      //
      // For LPDDR need to shift CmdS PiCode[1] separately.
      // Host struct is not updated, so update PiCode[0] manually, and then restore back.
      //
      ChannelOut->CmdsCmdPiCode[0] = ChannelOut->CmdsCmdPiCode[0] + Offset;
      ShiftPIforCmdTraining (
        MrcData,
        Channel,
        MrcIterationCmdS,
        RankMaskCh,
        2,
        ChannelOut->CmdsCmdPiCode[1] + Offset,
        UpdateHost
        );
      ChannelOut->CmdsCmdPiCode[0] = ChannelOut->CmdsCmdPiCode[0] - Offset;
    }
    //
    // Shift CKE
    //
    ShiftPIforCmdTraining (
      MrcData,
      Channel,
      MrcIterationCke,
      RankMaskCh,
      1,
      ChannelOut->CkeCmdPiCode[0] + Offset,
      UpdateHost
      );

    if (Lpddr) {
      // Restore CKE (exit Power Down)
      MiscCkeCtrl.Bits.CKE_On = ChannelOut->ValidCkeBitMask;
      RegOffset = OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG,MCHBAR_CH1_CR_REUT_CH_MISC_CKE_CTRL_REG, Channel);
      MrcWriteCR (MrcData, RegOffset, MiscCkeCtrl.Data);
    }
  } // for Channel
  //
  // Reset DDR is required
  //
  if (ResetDDR && !Lpddr) {
    Status = MrcResetSequence (MrcData);
  } else if (SelfRefresh) {
    Status = ExitSR (MrcData);
  }

  return Status;
}

/**
  Returns the index into the array OptResult in the MrcOutput structure.

  @param[in] OptParam - Margin parameter

  @retval One of the following values: RdSAmpOfft(0), WrDSOfft (1), RxEqOfft(2), TxEqOfft (3), RdOdtOfft(4)
**/
UINT8
GetOptResultType (
  IN UINT8 OptParam
  )
{
  switch (OptParam) {
    case OptRxBias:
    case OptRxBiasCb:
      return RdSAmpOfft;

    case OptWrDS:
    case OptTxEqWrDS:
      return WrDSOfft;

    case OptRxEq:
      return RxEqOfft;

    case OptTxEq:
      return TxEqOfft;

    case OptRdOdt:
      return RdOdtOfft;

    default:
      return 0; // Return RdSAmpOfft to point to the beginning of the array
  }
}

/**
  Program DimmOptPoint values on CPU and DIMM sides, such as DIMM ODT, CPU ODT, Ron, Slew Rate, Equalization.

  @param[in, out] MrcData          - Include all MRC global data.
  @param[in]      Channel          - Channel to work on.
  @param[in]      RankMask         - Ranks to update Opt Settings.
  @param[in, out] BestDimmOptPoint - Best DIMM Opt settings used to update hardware
  @param[in, out] RttTypeSize      - Which termination to set.
  @param[in]      SkipGRdOdt       - Switch to skip updating CPU ODT
  @param[in]      SkipDimmOdts     - Switch to skip updating DIMM ODT
  @param[in]      SkipBestOffsets  - Switch to skip updating Opt settings
  @param[in]      UpdateHost       - Switch to skip updating MRC host structure

  @retval Nothing
**/
void
UpdateOptPointValues (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                RankMask,
  IN OUT DimmOptPoint         *BestDimmOptPoint,
  IN     UINT8                RttTypeSize,
  IN     BOOLEAN              SkipGRdOdt,
  IN     BOOLEAN              SkipDimmOdts,
  IN     BOOLEAN              SkipBestOffsets,
  IN     BOOLEAN              UpdateHost
  )
{
  MrcOutput       *Outputs;
  UINT8           byte;
  UINT8           rank;
  //UINT8           offset;
  //UINT8           Dimm;
  UINT8           RttLoop;
  UINT8           test;
  UINT8           TestArray[SizeOfTCompOffset];
  BOOLEAN         DebugPrint;
  BOOLEAN         PerRank;
  UINT8           Ranks;
  UINT8           OptParam[MAX_GRID_DIM];
  //UINT8           OptParamTest;
  UINT8           OptIdx;
  INT8            ParamOff[MAX_GRID_DIM];
  OptOffsetChByte *PBestOff;
  UINT8           NumTests;
  const MrcInput  *Inputs;
  MrcDebug        *Debug;
  const MRC_FUNCTION *MrcCall;

  Outputs     = &MrcData->Outputs;
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Debug       = &Outputs->Debug;
  NumTests    = BestDimmOptPoint->OptParamTestListSize;
  DebugPrint  = 0;

  MrcCall->MrcSetMem (TestArray, sizeof (TestArray), 0);
  if (SkipBestOffsets) {
    NumTests = 0;
  }
  //
  // build tests array to update RdSAmpOfft(0), WrDSOfft (1), RxEqOfft(2), TxEqOfft (3), RdOdtOfft(4)
  //
  for (test = 0; test < NumTests; test++) {
    OptParam[0]  = BestDimmOptPoint->OptParamTestList[test];
    TestArray[GetOptResultType (OptParam[0]) ] = 1;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Test - %s : %d ,UpdateHost: %d\n",
      TOptParamOffsetString[OptParam[0]],
      test,
      UpdateHost
      );
  }

  if (!SkipGRdOdt) {
    //
    // update GRdOdt
    //
    UpdateCompTargetValue (MrcData, RdOdt, BestDimmOptPoint->ODTSet.GRdOdt, UpdateHost);
    BestDimmOptPoint->ODTSet.GRdOdtCode = GetCompCode ( MrcData, RdOdt, 2);

    if (DebugPrint) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "GRdODT aplly is : %d \n",
        CalcCpuImpedance (MrcData, 0, 0, 0, OptRdOdt, FALSE, 0, FALSE, 0, 0)
        );
    }
  }

  //
  // On ULT (1DPC) DIMM ODT is connected to Vdd, so RttNom must be disabled
  // SKL <EA> TODO: what about SKL platforms?
  //
  // Apply Best RTT Points
  //
  if (!SkipDimmOdts) {
    for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank += 2) {
      if (!MrcRankInChannelExist (MrcData, rank, Channel)) {
        continue;
      }
      Ranks = (0x3 << rank) & RankMask;
      if (Ranks == 0) {
        continue;
      }
      for (RttLoop = 0; RttLoop < RttTypeSize; RttLoop++) {
        UpdateOptParamOffset (MrcData, Channel, Ranks, 0, BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank/2].RttType[RttLoop],
          BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank/2].Rtt[RttLoop], UpdateHost);
        if (DebugPrint) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "%s Channel %d Ranks  0x%X apply is : %d\t\n",
            TOptParamOffsetString[BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank/2].RttType[RttLoop]],
            Channel,
            Ranks,
            CalcDimmImpedance (MrcData, Channel, rank, BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank/2].RttType[RttLoop], FALSE,
              BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank/2].Rtt[RttLoop])
            );
        }
      }
    }
  }

  if (NumTests) {
    for (byte = 0; byte < Outputs->SdramCount; byte++) {
      //
      // Apply Best RdOdt and WrDS
      // OdtOff = Off[RdOdtOfft][0][Channel][byte] + RdOdtChOffset[Channel];
      //
      for (test = 0; test < NumTests; test++) {
        OptParam[0]  = BestDimmOptPoint->OptParamTestList[test];
        PBestOff = &BestDimmOptPoint->BestOptOff[GetOptResultType (OptParam[0]) ][0];
        if ((OptParam[0] == OptRxEq) || (OptParam[0] == OptTxEq)) {
          PerRank = TRUE;
        } else {
          PerRank = FALSE;
        }
        if (OptParam[0] == OptTxEqWrDS) {
          OptParam[0] = OptTxEq;
          OptParam[1] = OptWrDS;
        } else if (OptParam[0] == OptRxBiasCb) {
          OptParam[0] = OptRxBias;
          OptParam[1] = OptRxCb;
        }
        GetParamsXYZ (MrcData, ParamOff, PBestOff->GridDataSet.OptParamLen, PBestOff->GridDataSet.GridMode,
          (UINT8) PBestOff->Offset[Channel][byte], PBestOff->GridDataSet.Start, PBestOff->GridDataSet.OffLen);
        for (OptIdx = 0; OptIdx < PBestOff->GridDataSet.OptParamLen; OptIdx++ ) { // @todo: error checking, exceeding loop
          for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
            if (PerRank) {
              Ranks = 1 << rank;
              if (!(MrcRankInChannelExist (MrcData, rank, Channel) && (Ranks & RankMask))) {
                continue;
              }
            } else {
              Ranks = RankMask;
            }
            UpdateOptParamOffset (
              MrcData,
              Channel,
              Ranks,
              byte,
              OptParam[OptIdx],
              ParamOff[OptIdx],
              UpdateHost
              );
            if (DebugPrint) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "param[%d]=%s best Offset for byte %d RankMask = %x is : %d\t\n",
                OptIdx,
                TOptParamOffsetString[OptParam[OptIdx]],
                byte,
                Ranks,
                ParamOff[OptIdx]
                );
            }
            if (!PerRank) {
              break;
            }
          }
        }
      }
    }
  }
}

/**
  Normalizes the Power values to the Margins passed in Points2Calc.
  Assumes that power numbers are represented as lowest number is the lowest power,
  and inverts the scale such that highest number is the lowest power.  This is done
  before normalizing to margins.

  @param[in]     MrcData       - Include all MRC global data.
  @param[in]     Points2calc   - Data normalize power.
  @param[in]     ArrayLength   - Array length of Points2calc.
  @param[in]     LenMargin     - The length of inputMargins we are optimizing (0 - LenMargin -1).
  @param[in]     TestListSize  - Size of TestList/Scale

  @retval Nothing
**/
void
NormalizePowerToMargins (
  IN     MrcParameters   *MrcData,
  IN     void            *Points2calc,
  IN     UINT8           ArrayLength,
  IN     UINT8           LenMargin,
  IN     UINT8           TestListSize
  )
{
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  UINT16          MaxPoints[MAX_MARGINS_TRADEOFF];
  UINT16          MinPoints[MAX_MARGINS_TRADEOFF];
  UINT16          MaxPwr;
  UINT16          MinPwr;
  UINT8           off;
  UINT8           test;
  UINT16          AveOfMax;
  UINT16          X;
  UINT16          *Points;
  UINT16          *PointsElement;

  MrcCall     = MrcData->Inputs.Call.Func;
  Debug       = &MrcData->Outputs.Debug;
  Points      = (UINT16 *) Points2calc;
  MaxPwr      = 0;
  MinPwr      = 0xffff;

  MrcCall->MrcSetMemWord (MaxPoints, sizeof (MaxPoints) / sizeof (UINT16), 0);
  MrcCall->MrcSetMemWord (MinPoints, sizeof (MinPoints) / sizeof (UINT16), 0xFFFF);

  //
  // Sorting the min max margin points for each test
  //
  for (off = 0; off < LenMargin; off++) {
    for (test = 0; test < TestListSize; test++) {
      PointsElement = (Points + ArrayLength * test + off);
      if (MaxPoints[test] < *PointsElement) {
        MaxPoints[test] = *PointsElement;
      }

      if (MinPoints[test] > *PointsElement) {
        MinPoints[test] = *PointsElement;
      }
    }
    PointsElement = (Points + ArrayLength * TestListSize + off);

    if (MaxPwr < *PointsElement) {
      MaxPwr = *PointsElement;
    }

    if (MinPwr > *PointsElement) {
      MinPwr = *PointsElement;
    }

    if (LenMargin == 1) {
      MaxPwr  = *PointsElement;
      MinPwr  = *PointsElement;
    }
  }

  MRC_POWER_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "MaxPwr=%d MinPwr=%d\n",MaxPwr,MinPwr);
  AveOfMax  = 0;
  TestListSize = MIN (TestListSize, ARRAY_COUNT (MaxPoints));
  for (test = 0; test < TestListSize; test++) {
    AveOfMax += MaxPoints[test];
  }
  AveOfMax = AveOfMax / TestListSize;

  MRC_POWER_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "Power Values\nBefore\tAfter\n");
  for (off = 0; off < LenMargin; off++) {
    PointsElement = (Points + ArrayLength * TestListSize + off);
    MRC_POWER_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "%d\t", *PointsElement);
    if (MaxPwr == MinPwr) {
      X = 0;
    } else {
      X = 100 - 100 * (*PointsElement - MinPwr) / (MaxPwr);
    }
    *PointsElement = AveOfMax * X / 100;
    MRC_POWER_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "%d\n", *PointsElement);
  }
}

#ifdef MRC_DEBUG_PRINT


/**
  This function implements switch to print the correct format and data for the
  OptResultsPerByte struct members.

  @param[in] Debug     - Debug pointer for printing.
  @param[in] Data      - Pointer to OptResultsPerByte struct.
  @param[in] TypeIndex - Member of OptResultsPerByte to print.
  @param[in] TestIndex - Some parameters store multiple test results to be printed.
  @param[in] MidPoint  - Used to convert from zero-based indexing to the selected value

  @retval Nothing.
**/
void
MrcOptResultsPerBytePrint (
  IN MrcDebug *const    Debug,
  IN OptResultsPerByte  *Data,
  IN UINT8              TypeIndex,
  IN UINT8              TestIndex,
  IN INT8               MidPoint
  )
{
  UINT32  Value;
  BOOLEAN PrintVal;
  BOOLEAN PrintTab;

  PrintVal = FALSE;
  PrintTab = FALSE;
  Value = 0;

  switch (TypeIndex) {
    case MrcOptResultBest:
      if (TestIndex == 0) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "=== %d ===", Data->Best - MidPoint);
      } else {
        PrintTab = TRUE;
      }
      break;

    case MrcOptResultGrdBnd:
      if (TestIndex == 0) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*** %d ***", Data->GuardBand);
      } else {
        PrintTab = TRUE;
      }
      break;

    case MrcOptResultOffSel:
      if (TestIndex == 0) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--> %d <--", Data->Best - MidPoint + Data->GuardBand);
      } else {
        PrintTab = TRUE;
      }
      break;

    case MrcOptResultScale:
      Value     = Data->Scale[TestIndex];
      PrintVal  = TRUE;
      break;

    case MrcOptResultMaxPost:
      Value     = Data->MaxPost[TestIndex];
      PrintVal  = TRUE;
      break;

    case MrcOptResultMinPost:
      Value     = Data->MinPost[TestIndex];
      PrintVal  = TRUE;
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MrcOptResultsPerBytePrint: invalid TypeIndex\n");
  }
  if (PrintTab) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
  }
  if (PrintVal) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Value);
  }
}


/**
  This function prints the Optimize margin result table
  e.g: calcResultSummary[MAX_CHANNEL][MAX_SDRAM_IN_DIMM]

  @param[in] MrcData           - MRC data structure
  @param[in] calcResultSummary - The data array [MAX_CHANNEL][MAX_SDRAM_IN_DIMM]
  @param[in] TestList          - Test list
  @param[in] NumTest           - Number of test
  @param[in] NumOffsets        - Number of offsets
  @param[in] MidPoint          - Middle point
  @param[in] IncEnds           - Print ends points
  @param[in] OptParam          - Used to convert to the Opt param string for printing
  @param[in] OptPower          - Opt Power values to be printed
  @param[in] Channel           - Channel to print
  @param[in] Ranks             - Ranks to print
  @param[in] TrendLine         - Switch to print the trend line
  @param[in] Nibble            - take low/high bytes
  @param[in] perCh             - Switch to only print 1 Byte of data
  @param[in] noPrint           - Boolean used to disable printing of results

  @retval Nothing
**/
void
PrintCalcResultTableCh (
  IN MrcParameters *const MrcData,
  IN OptResultsPerByte    calcResultSummary[MAX_SDRAM_IN_DIMM],
  IN const UINT8          *TestList,
  IN UINT8                NumTest,
  IN UINT8                NumOffsets,
  IN INT8                 MidPoint,
  IN BOOLEAN              IncEnds,
  IN UINT8                OptParam,
  IN UINT16               *OptPower,
  IN UINT8                Channel,
  IN UINT8                Ranks,
  IN BOOLEAN              TrendLine,
  IN UINT8                Nibble,
  IN BOOLEAN              perCh,
  IN BOOLEAN              noPrint
  )
{
  const MRC_FUNCTION *MrcCall;
  MrcDebug          *Debug;
  OptResultsPerByte *data;
  UINT8             Off; // @todo: change for the new alg.
  UINT8             Start;
  UINT8             Stop;
  UINT8             i;
  UINT8             j;
  UINT8             b;
  UINT8             FirstByte;
  UINT8             NumBytes;
  UINT8             NumTestPlus;
  UINT32            Result;
  BOOLEAN           Format64Results;
  UINT8             Param;

  MrcCall         = MrcData->Inputs.Call.Func;
  Format64Results = 1;
  //
  // Display result in %/Delta , 0-displat raw 64bit result in HEX
  //
  Debug = &MrcData->Outputs.Debug;
  Start = (!IncEnds);
  Stop  = NumOffsets - (!IncEnds);
  if (noPrint) {
    return;

  }

  FirstByte = (Nibble) ? 4 : 0;
  NumBytes  = FirstByte + 4 + Nibble * MrcData->Outputs.SdramCount % 8;
  if (perCh) {
    NumBytes = 1;
  }

  NumTestPlus = (TrendLine) ? NumTest + 1 : NumTest;

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "\n<======== optimize %s ========>Plot results ",
    TOptParamOffsetString[OptParam]
    );
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "<Channel=%d><rank/s=0x%x><Nibble=%s> across settings :(Start=%d,Stop=%d)\n",
    Channel,
    Ranks,
    (Nibble) ? "High" : "Low",
    Start - MidPoint,
    Stop - MidPoint - 1
    );
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Bytes\t");
  for (b = FirstByte; b < NumBytes; b++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", b);
    for (i = 0; i < NumTestPlus + 1; i++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t"); // tab insertion
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n"); // row end here !
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Offset\t"); // row starts here !
  if (OptPower[Stop - 1] != 0) {//WA: need to add param to enable this print
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t","TotPwr");
  }

  for (b = FirstByte; b < NumBytes; b++) {
    for (i = 0; i < NumTest; i++) {
      //
      // Test types header
      //
      Param = TestList[i];
      if (Param > CmdV) {
        Param = (Param % 16) + 4;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", MarginTypesString[Param]);
    }

    if (TrendLine) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", "PwrVal");
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Opt.func\t"); // more header..
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n"); // row end here !
  for (Off = Start; Off < Stop; Off++) {
    //
    // row starts here !
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Off - MidPoint);
    if (OptPower[Stop - 1] != 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d.%d\t", OptPower[Off]/10, OptPower[Off]%10);
    }

    for (b = FirstByte; b < NumBytes; b++) {
      if (b < MAX_SDRAM_IN_DIMM) {
        data = &calcResultSummary[b];
      } else {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "Error: calcResultSummary array out of bounds! %d > %d \n",
          b,
          MAX_SDRAM_IN_DIMM - 1
          );
        return;
      }

      for (i = 0; i < NumTestPlus; i++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", data->Margins[i][Off].EW);
      }

      if (Format64Results) {
        Result = (UINT32) (MrcCall->MrcDivU64x64 (MrcCall->MrcMultU64x32 (data->Result[Off], 100), data->MaxR, NULL));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t\t", Result);
      }

      if (!Format64Results) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "%08x-%08x\t\t",
          (UINT32) MrcCall->MrcRightShift64 (data->Result[Off],
                              32),
          (UINT32) (data->Result[Off])
          );
      }
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n"); // row end here !
  }

  for (i = 0; i < ARRAY_COUNT (OptResultDbgStrings); i++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", OptResultDbgStrings[i]);
    for (b = FirstByte; b < NumBytes; b++) {
      if (b < MAX_SDRAM_IN_DIMM) {
        data = &calcResultSummary[b];
      } else {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "Error: calcResultSummary array out of bounds! %d > %d \n",
          b,
          MAX_SDRAM_IN_DIMM - 1
          );
        return;
      }

      for (j = 0; j < NumTestPlus; j++) {
        MrcOptResultsPerBytePrint (Debug, data, i, j, MidPoint);
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t"); // tab insertion
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  } // row end here !
  return;
}

/**
  This function prints the Optimize margin result table: calcResultSummary.

  @param[in] MrcData           - MRC data structure
  @param[in] calcResultSummary - The data array [MAX_STROBES]
  @param[in] DimmOptPoints     - Pointer to the structure holding the test data
  @param[in] NumOffsets        - Number of offsets
  @param[in] MidPoint          - Middle point
  @param[in] IncEnds           - Print ends points
  @param[in] OptParam          - Used to convert to the Opt param string for printing
  @param[in] RttTypeSize       - Rtt values that are being trained
  @param[in] Channel           - Channel to print
  @param[in] Ranks             - Ranks to print
  @param[in] TrendLine         - Switch to print the trend line
  @param[in] printOptSetting   - print sub optimization prints (TxEq/DS etc.) per byte (for power optimization)
  @param[in] Scale             - print the scale (weight) we applied for each test (WrV, WrT, RdV, RdT) for optimization
  @param[in] Nibble            - take low/high bytes
  @param[in] perCh             - Switch to only print 1 Byte of data

  @retval Nothing
**/
void
PrintODTResultTable (
  IN MrcParameters *const MrcData,
  IN OptResultsPerByte    *calcResultSummary,
  IN DimmOptPoint         *DimmOptPoints,
  IN UINT8                NumOffsets,
  IN INT8                 MidPoint,
  IN BOOLEAN              IncEnds,
  IN UINT8                OptParam,
  IN UINT8                RttTypeSize,
  IN UINT8                Channel,
  IN UINT8                Ranks,
  IN BOOLEAN              TrendLine,
  IN BOOLEAN              printOptSetting,
  IN UINT8                *Scale,
  IN UINT8                Nibble,
  IN BOOLEAN              perCh
  )
{
  static const char *Strings[] = {
    //"GRdOdt",
    "Pwr[mW]",
    "Pwr Rd",
    "Pwr Wr"
  };
  const MRC_FUNCTION *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  OptResultsPerByte *data;
  UINT8             Off;
  UINT8             Start;
  UINT8             Stop;
  UINT8             i;
  UINT8             j;
  UINT8             b;
  UINT8             r;
  UINT8             Rank;
  UINT8             FirstByte;
  UINT8             NumBytes;
  UINT8             NumTestPlus;
  UINT8             *TestList;
  UINT8             Param;
  UINT8             TestSize;
  UINT32            Result;
  UINT8             OptParamType;
  UINT8             OptResultType;
  BOOLEAN           Format64Results; // Display result in %/MaxR , 0-display raw 64bit result in HEX
  INT8              Opt0;
  INT8              Opt1;
  GridData         *GridDataSet;
  UINT8            OtherRanks;
  INT8             ParamOff[MAX_GRID_DIM];
  UINT8            FirstRank;
  UINT8            Idx;

  MrcCall         = MrcData->Inputs.Call.Func;
  Format64Results = 1;
  Outputs         = &MrcData->Outputs;
  Debug           = &Outputs->Debug;
  Start           = (!IncEnds);
  Stop            = NumOffsets - (!IncEnds);
  TestList        = DimmOptPoints[0].TestList;
  FirstByte       = (Nibble) ? 4 : 0;
  NumBytes        = FirstByte + 4 + Nibble * Outputs->SdramCount % 8;
  OtherRanks     = (~Ranks) & Outputs->Controller[0].Channel[Channel].ValidRankBitMask;

  //
  // Find the first selected rank
  //
  FirstRank = 0;
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((1 << Rank) & Ranks) {
      FirstRank = Rank;  // could be in any channel
      break;
    }
  }

  if (perCh) {
    NumBytes = 1;
  }

  NumTestPlus = (TrendLine) ? DimmOptPoints[0].NumTests + 1 : DimmOptPoints[0].NumTests;
  //
  // RttNomOffset = (MrcData->Outputs.Channel[Channel].DimmCount == 1) ? 0 : RttOffset; // if 2DPC - RttNom 40,30,20 Ohms
  //
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "\n<======== optimize %s ========>Plot results ",
    TOptParamOffsetString[OptParam]
    );
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "<Channel=%d><rank/s=0x%x> across settings :(Start=%d,Stop=%d)\n",
    Channel,
    Ranks,
    Start - MidPoint,
    Stop - MidPoint - 1
    );
  //
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ODT\t");
  // for (b = 0; b < ARRAY_COUNT (OdtStrings); b++) {
  //  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t",OdtStrings[b] );
  //  for (i = 0; i < NumTestPlus+1; i++) MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");//tab insertion
  // }
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");//row end here!
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Offset\t"); // row starts here!
  for (b = 0; b < RttTypeSize; b++) {
    Idx = MIN ((UINT8) GetRttType (DimmOptPoints[0].ODTSet.DimmOdt[Channel][FirstRank/2].RttType[b]), ARRAY_COUNT (OdtTypeString) - 1);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", OdtTypeString[Idx]);
  }
  for (b = 0; b < ARRAY_COUNT (Strings); b++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", Strings[b]);
  }

  for (i = 0; i < DimmOptPoints[0].NumTests; i++) {
    //
    // Test types header
    //
    Param = TestList[i];
    if (Param > CmdV) {
      Param = (Param % 16) + 4;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", MarginTypesString[Param]);
  }

  if (TrendLine) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", "T.line");
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Opt.func\nScale\t"); // Row starts here
  for (b = 0; b < RttTypeSize; b++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
  }
  for (b = 0; b < ARRAY_COUNT (Strings); b++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
  }

  TestSize = DimmOptPoints[0].NumTests;
  if (TrendLine) {
    TestSize++;
  }
  for (i = 0; i < TestSize; i++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Scale[i]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n");

  for (Off = Start; Off < Stop; Off++) {
    //
    // row starts here !
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Off - MidPoint);
    for (b = 0; b < RttTypeSize; b++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", CalcDimmImpedance (MrcData, Channel, FirstRank,
                                                      DimmOptPoints[Off].ODTSet.DimmOdt[Channel][FirstRank/2].RttType[b], TRUE, DimmOptPoints[Off].ODTSet.DimmOdt[Channel][FirstRank/2].Rtt[b]));
    }
    for (b = 0; b < ARRAY_COUNT (Strings); b++) {
      //       if (b == 0) {
      //         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t",
      //           DimmOptPoints[Off].ODTSet.GRdOdt
      //           );
      //       }
      if (b == 0) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "%d.%d\t",
          DimmOptPoints[Off].PowerCalc.TotalPwr / 10,
          DimmOptPoints[Off].PowerCalc.TotalPwr % 10
          );
      }
      if (b == 1) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "%d.%d\t",
          DimmOptPoints[Off].PowerCalc.RdPower / 10,
          DimmOptPoints[Off].PowerCalc.RdPower % 10
          );
      }
      if (b == 2) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "%d.%d\t",
          DimmOptPoints[Off].PowerCalc.WrPower / 10,
          DimmOptPoints[Off].PowerCalc.WrPower % 10
          );
      }
    }

    data = calcResultSummary;
    for (i = 0; i < NumTestPlus; i++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t",DimmOptPoints[Off].Points2Trade[i][Channel]);
    }

    if (data->MaxR == 0) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_ERROR,
        "MaxR - Div by Zero error"
        );
      data->MaxR++;
    }
    if (Format64Results) {
        Result = (UINT32) (MrcCall->MrcDivU64x64 (MrcCall->MrcMultU64x32 (data->Result[Off], 100), data->MaxR, NULL));
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t\t", Result);
    } else {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "%08x-%08x\t\t",
        (UINT32) MrcCall->MrcRightShift64 (data->Result[Off],
                            32),
        (UINT32) (data->Result[Off])
        );
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n"); // row end here !
    if (printOptSetting) {
      for (i = 0; i < DimmOptPoints[0].OptParamTestListSize; i++) {
        OptParamType = DimmOptPoints[0].OptParamTestList[i];
        OptResultType = GetOptResultType (OptParamType);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s  \t", TOptParamOffsetString[OptParamType]);
        if ((OptParamType == OptRxEq) || (OptParamType == OptTxEq)) {
          //
          // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
          //
          for (r = 0; r < MAX_RANK_IN_CHANNEL; r++) {
            if (!(Ranks & (0x1 << r))) {
              continue;
            }

            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "<Rank %d>|", r);
            for (b = 0; b < Outputs->SdramCount; b++) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "%02d|",
                DimmOptPoints[Off].BestOptOff[OptResultType][r].Offset[Channel][b]
                );
            }

            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
          }
        } else {
          GridDataSet = &DimmOptPoints[Off].BestOptOff[OptResultType][0].GridDataSet;
          for (b = 0; b < Outputs->SdramCount; b++) {
            if (GridDataSet->OptParamLen > 1) {
              GetParamsXYZ (MrcData, ParamOff, GridDataSet->OptParamLen, GridDataSet->GridMode, (UINT8) DimmOptPoints[Off].BestOptOff[OptResultType][0].Offset[Channel][b], GridDataSet->Start, GridDataSet->OffLen);
              Opt0 = ParamOff[0];
              Opt1 = ParamOff[1];
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "%d:%d|",
                Opt0,
                Opt1
                );
            } else {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "%d|",
                DimmOptPoints[Off].BestOptOff[OptResultType][0].Offset[Channel][b]
                );
            }
          }
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n"); // row end here !
      }
    }

  }

  for (i = 0; i < ARRAY_COUNT (OptResultDbgStrings); i++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", OptResultDbgStrings[i]);
    for (b = FirstByte; b < NumBytes; b++) {
      data = calcResultSummary;
      for (j = 0; j < NumTestPlus; j++) {
        MrcOptResultsPerBytePrint (Debug, data, i, j, MidPoint);
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t");  // tab insertion
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  } // row end here !
}

/**
  This function prints the Optimize margin result table
  e.g: MarginResult[Test][Offset][Channel][Byte][sign]

  @param[in] MrcData     - MRC data structure
  @param[in] ChMask      - Channels to print
  @param[in] ResultArray - Array with saved margin results
  @param[in] TestNum     - Test index
  @param[in] OffsetsNum  - number of offsets
  @param[in] MidPoint    - Zero point
  @param[in] OptParam    - Used to convert to the Opt param string for printing
  @param[in] Param       - Margin type to be printed.
  @param[in] PowerLimits - Power limits to print.
  @param[in] noPrint     - Used to skip printing.

  @retval Nothing
**/
void
PrintResultTableByte4by24 (
  IN MrcParameters   *MrcData,
  IN UINT8           ChMask,
  IN UINT16          ResultArray[4][MAX_OPT_POINTS][MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN UINT16          TestNum,
  IN UINT8           OffsetsNum,
  IN UINT8           MidPoint,
  IN UINT8           OptParam,
  IN UINT8           Param,
  IN UINT16          *PowerLimits,
  IN BOOLEAN         noPrint
  )
{
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  UINT8           Channel;
  UINT8           Byte;
  UINT8           Off;
  UINT8           Start;
  UINT8           Stop;

  // @todo new alg. change pass start stop...
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Start   = -MidPoint;
  Stop    = OffsetsNum - MidPoint - 1;
  if (Param > CmdV) {
    Param = (Param % 16) + 4;
  }

  if (noPrint) {
    return;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "\nTest number: %d - %s, Plot results across OptParam=%s (Start=%d,Stop=%d)",
    TestNum,
    MarginTypesString[Param],
    TOptParamOffsetString[OptParam],
    Start,
    Stop
    );

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "w/power limits(width): %d\nChannel\t0\t\t\t\t\t\t\t\t1\nByte\t",
    PowerLimits[TestNum]
    );

  for (Channel = 0; Channel < 2; Channel ++) {
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%u\t", Byte);
    }
  }
  //
  // Sweep through OpParam settings
  //
  for (Off = Start; Off < Stop + 1; Off++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n  %d:\t", Off);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      //
      // spaces for non populated channel
      //
      if (!((1 << Channel) & ChMask)) {
        if (Channel == 0) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (Outputs->SdramCount == 8) ? "\t\t\t\t\t\t\t\t" : "\t\t\t\t\t\t\t\t\t");
        }
        continue;
      }

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (Byte < MAX_SDRAM_IN_DIMM) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "%d\t",
            ResultArray[TestNum][Off - Start][Channel][Byte]
            );
        }
      }
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");  // New line after the end of the table

  return;
}

/**
  This function prints the Optimize margin result table
  e.g: MarginResult[Test][Offset][Channel][Byte][sign]

  @param[in] MrcData            - MRC data structure
  @param[in] Channel            - Channel to print
  @param[in] Byte               - Byte to print
  @param[in] calcResultSummary  - Array with saved margin results
  @param[in] BestOff            - Pointer to the selected offsets
  @param[in] Param              - Margin type to print.
  @param[in] OffsetsNum         - number of offsets
  @param[in] Start              - Start offsets
  @param[in] Stop               - End offsets
  @param[in] OptParam           - List of optimization parameters
  @param[in] OptParamLen        - Number of optimization parameters
  @param[in] PowerLimits        - Power limits to print.
  @param[in] Dim                - Dimension
  @param[in] TestNum            - Test index
  @param[in] NumTests           - Number of tests
  @param[in] noPrint            - Used to skip printing.

  @retval Nothing
**/
void
Print2DResultTableChByte (
  IN MrcParameters      *MrcData,
  IN UINT8              Channel,
  IN UINT8              Byte,
  IN OptResultsPerByte  *calcResultSummary,
  IN OptOffsetChByte    *BestOff,
  IN UINT8              Param,
  IN UINT8              OffsetsNum,
  IN INT8               *Start,
  IN INT8               *Stop,
  IN const UINT8        *OptParam,
  IN UINT8              *OptParamLen,
  IN UINT16             *PowerLimits,
  IN UINT8              Dim,
  IN UINT16             TestNum,
  IN UINT8              NumTests,
  IN BOOLEAN            noPrint
  )
{
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  const MRC_FUNCTION *MrcCall;
  UINT8             Off;
  UINT8             XOff;
  UINT8             YOff;
  OptResultsPerByte *data;

  MrcCall = MrcData->Inputs.Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  if (Param > CmdV) {
    Param = (Param % 16) + 4;
  }

  if (noPrint) {
    return;
  }

  if ((Byte == 0) && ((Dim > 1) || (TestNum == 0))) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "\nPlot Margin %s results across OptParam=%s Start=%d Stop=%d ",
      (Dim > 1) ? MarginTypesString[Param] : "",
      TOptParamOffsetString[OptParam[0]],
      Start[0],
      Stop[0]
      );

    if (Dim > 1) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "& OptParam=%s Start=%d Stop=%d, power limits=%d\n",
        TOptParamOffsetString[OptParam[1]],
        Start[1],
        Stop[1],
        PowerLimits[TestNum]
        );
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    }
  }
  //
  // Sweep through OpParam settings
  //
  data = calcResultSummary;
  // print param0 header and offsets
  if ((Dim > 1) || ((TestNum == 0) && (Byte == 0))) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", TOptParamOffsetString[OptParam[0]]);
    //     MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dB%d\t", Channel, Byte);
    for (Off = 0; Off < OptParamLen[0]; Off++) {// print param0 offsets
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Off + Start[0]);
    }
  }
  // print param1 header
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%s\t", (Dim > 1) ? TOptParamOffsetString[OptParam[1]] : "");

  if ((Dim > 1 ) || (TestNum == 0)) {
    // print Ch Byte and separators, the -1 is result of the 2 tab width of below line
    for (Off = 0; Off < (OptParamLen[0] - 1); Off++) {
      if (Off == (OptParamLen[0] / 2 - 1)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dB%d %s", Channel, Byte, (Dim > 1) ? MarginTypesString[Param] : "---");
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--------");
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "----");
  }

  for (Off = 0; Off <  OffsetsNum; Off++) {
    XOff = Off % OptParamLen[0];
    YOff = Off / OptParamLen[0];
    if (XOff == 0) {
      if (Dim > 1) { // print param1 offset
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%d\t", YOff + Start[1]);
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%s\t", MarginTypesString[Param]);
      }
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d", data->Margins[TestNum][Off].EW);
    if (BestOff->Offset[Channel][Byte] == Off) { // mark the chosen one
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "**");
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
  }

  if ((Dim > 1) || (TestNum == (NumTests - 1))) {
    // print separators between ch or at last test in list
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\t");
    for (Off = 0; Off < (OptParamLen[0] - 1); Off++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--------");
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "----\n");
  }

  return;
}
#endif // MRC_DEBUG_PRINT

/**
  This function returns the UPM or PWR limit value for the specified parameter

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Param     - Margin type
  @param[in] LimitType - Type of limit: UpmLimit or PowerLimit

  @retval Returns the UPM or PWR limit
**/
UINT16
MrcGetUpmPwrLimit (
  IN MrcParameters *const MrcData,
  IN UINT8                Param,
  IN UINT8                LimitType
  )
{
  MrcIntOutput           *IntOutputs;
  MrcOutput              *Outputs;
  const MrcInput         *Inputs;
  MrcDimmOut             *Dimm;
  MrcDdrType             DdrType;
  MrcUpmPwrRetrainLimits *MrcLimits;
  UINT32                 Index;
  UINT16                 Limit;
  UINT8                  Channel;

  Limit      = 0;
  Outputs    = &MrcData->Outputs;
  Inputs     = &MrcData->Inputs;
  IntOutputs = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  MrcLimits  = IntOutputs->UpmPwrRetrainLimits.Pointer;
  DdrType    = Outputs->DdrType;

  for (Index = 0; Index < MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS; Index++) {
    if (Param == MrcLimits[Index].Param) {
      Limit = MrcLimits[Index].ParamLimit[LimitType];
      break;
    }
  }

  if (LimitType != RetrainLimit) {
    if ((DdrType == MRC_DDR_TYPE_DDR3) && (Param == WrV)) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcChannelExist (Outputs, Channel)) {
          Dimm = &Outputs->Controller[0].Channel[Channel].Dimm[0];
          if ((Dimm[0].ReferenceRawCard == rcF) || (Dimm[1].ReferenceRawCard == rcF)) {
            Limit += 100;  // Add 10 ticks for WrV when DDR3L raw card F is present
            break;
          }
        }
      }
    }

    if ((Param == WrV) && (Outputs->Frequency > f1867)) {
      Limit += 160;
    }

    if ((Inputs->PowerTrainingMode == MrcTmMargin) && (LimitType == PowerLimit)) {
      Limit += 120;
    }
  }

  if ((DdrType == MRC_DDR_TYPE_DDR4) && (Param == WrV)) {
    Limit = (Limit * 10) / 25;  // DDR4 step is 7.8mV, and LPDDR3 step is 3.125mV (Vdd/384)
  }

  return Limit;
}


/**
  This function returns the Start/Stop limits value for the specified parameter

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Param     - Opt Param type
  @param[in] LimitType - Type of limit: 0 - Start 1 - Stop

  @retval Returns the Start or Stop limit
**/
INT8
OptParamLimitValue (
  IN MrcParameters *const MrcData,
  IN UINT8                Param,
  IN UINT8                LimitType
  )
{
  MrcIntOutput             *IntOutputs;
  MrcDebug                 *Debug;
  MrcOutput                *Outputs;
  const MrcInput           *Inputs;
  const MrcOptParamsLimits *MrcLimits;
  UINT32                   Index;
  INT8                     Limit;
  BOOLEAN                  NotFound;
  BOOLEAN                  UltUlx_Lpddr3_2133;

  Limit      = 0;
  NotFound   = TRUE;
  Outputs    = &MrcData->Outputs;
  Debug      = &Outputs->Debug;
  Inputs     = &MrcData->Inputs;
  IntOutputs = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  MrcLimits  = MrcOptParamLimit;
  UltUlx_Lpddr3_2133 = (Outputs->Frequency >= f2133) && (((Inputs->CpuModel == cmSKL_ULX_ULT) || (Inputs->CpuModel == cmKBL_ULX_ULT))) && (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);

  for (Index = 0; Index < MRC_NUMBER_OPT_PARAMS_TRAIN; Index++) {
    if (Param == MrcLimits[Index].Param) {
      if (Outputs->Frequency  < f1600) {
        Limit = MrcLimits[Index].SaGvLimits[LimitType];
      } else if (Inputs->PowerTrainingMode == MrcTmMargin) {
        Limit = MrcLimits[Index].MaxPerfLimits[LimitType];
      } else {
        Limit = MrcLimits[Index].Limits[LimitType];
        if ((Param == OptWrDS) && UltUlx_Lpddr3_2133) {
          // For U/Y 2133 extend WrDs range
          if (LimitType == 1) {
            Limit += 3;
          }
          Limit += 4;
        }
      }
      NotFound = FALSE;
      break;
    }
  }

  if (NotFound) {
    MRC_ASSERT (
      FALSE,
      Debug,
      "Can't find OptParamLimit for param %s",
      TOptParamOffsetString[Param]
      );
  }
  return Limit;
}

/**
  This function will adjust the requested Limit Type of the margin parameter by the signed offset passed in.

  @param[in]  MrcData   - MRC global data.
  @param[in]  Param     - Margin parameter type to adjust.
  @param[in]  LimitType - MRC_MARGIN_LIMIT_TYPE to adjust.
  @param[in]  Offset    - The adjustment value.

  @retval UINT16 - The new value of Param[MRC_MARGIN_LIMIT_TYPE]
**/
UINT16
MrcUpdateUpmPwrLimits (
  IN OUT MrcParameters * const  MrcData,
  IN UINT8                      Param,
  IN UINT8                      LimitType,
  IN INT8                       Offset
  )
{
  MrcIntOutput            *IntOutputs;
  MrcUpmPwrRetrainLimits  *MrcLimits;
  UINT32                  Index;
  INT32                   UpdatedValue;

  IntOutputs    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  MrcLimits     = IntOutputs->UpmPwrRetrainLimits.Pointer;
  UpdatedValue  = 0;

  for (Index = 0; Index < MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS; Index++) {
    if (Param == MrcLimits[Index].Param) {
      UpdatedValue = MrcLimits[Index].ParamLimit[LimitType];
      break;
    }
  }

  UpdatedValue += Offset;
  UpdatedValue = MAX (UpdatedValue, 0);
  UpdatedValue = MIN (UpdatedValue, 0xFFFF);

  MrcLimits[Index].ParamLimit[LimitType] = (UINT16) UpdatedValue;

  return (UINT16) UpdatedValue;
}

/**
  Returns the Actual DIMM Driver/Odt Impedance in Ohms.
  Note: host structure calculation based.

  @param[in] MrcData       - Pointer to MRC global data.
  @param[in] Channel       - Zero based channel number.
  @param[in] Rank          - Zero based rank number.
  @param[in] OptParam      - Param to read.
  @param[in] Override      - Override host read value.
  @param[in] OverrideValue - Value to override.

  @retval Returns the DIMM driver impedance value in Ohms
**/
UINT16
CalcDimmImpedance (
  IN MrcParameters *const MrcData,
  IN UINT8                Channel,
  IN UINT8                Rank,
  IN UINT8                OptParam,
  IN BOOLEAN              Override,
  IN UINT8                OverrideValue
  )
{

  MrcOutput                   *Outputs;
  MrcChannelOut               *ChannelOut;
  MrcDebug                    *Debug;
  MrcDdrType                  DdrType;
  static const UINT16         RttNomDic[6]     = {0xFFFF, 60, 120, 40, 20, 30 };
  static const UINT8          RttWrDic[3]      = {0, 60, 120};
  static const UINT8          Ddr3RonDic[2]    = {40, 34};
  static const UINT16         Ddr4RttNomDic[8] = {0xFFFF, 60, 120, 40, 240, 48, 80, 34 }; // Same for Rtt_Park
  static const UINT16         Ddr4RttWrDic[5]  = {0, 120, 240, 0xFFFF, 80 };         // in DDR4 we dont assert odt to target so 0 = off also
  static const UINT16         Ddr4RonDic[2]    = {34, 48};
  static const UINT16         LpddrOdtDic[4]   = {0xFFFF, 60, 120, 240 };
  static const UINT8          LpddrRonDic[3]   = {34, 40, 48 };
  DDR3_MODE_REGISTER_1_STRUCT Ddr3ModeRegister1;
  DDR3_MODE_REGISTER_2_STRUCT Ddr3ModeRegister2;
  DDR4_MODE_REGISTER_1_STRUCT Ddr4ModeRegister1;
  DDR4_MODE_REGISTER_2_STRUCT Ddr4ModeRegister2;
  DDR4_MODE_REGISTER_5_STRUCT Ddr4ModeRegister5;
  UINT8                       MaxLpddrIndex;
  UINT16                      LpddrMr;
  UINT8                       OtherDimm;
  UINT16                      *MR;
  UINT16                      Impedance = 0xFFFF; // Odt off

  Outputs     = &MrcData->Outputs;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  Debug      = &Outputs->Debug;
  DdrType     = Outputs->DdrType;

  if ((OptParam == OptDimmOdtNomNT) || (OptParam == OptDimmOdtParkNT)) {
    OtherDimm = MrcGetOtherDimm (MrcData, Channel, 1 << Rank);
    MR = ChannelOut->Dimm[OtherDimm % MAX_DIMMS_IN_CHANNEL].Rank[0].MR;
  } else {
    MR = ChannelOut->Dimm[ (Rank / 2) % MAX_DIMMS_IN_CHANNEL].Rank[Rank % 2].MR;
  }
  switch (OptParam) {
    case  (OptDimmOdtWr) :
      if (DdrType == MRC_DDR_TYPE_LPDDR3) {
        LpddrMr = ChannelOut->Dimm[ (Rank / 2) % MAX_DIMMS_IN_CHANNEL].Rank[Rank % 2].MR11;
        MaxLpddrIndex = ARRAY_COUNT (LpddrOdtDic) - 1;
        Impedance = Override ? LpddrOdtDic[MIN (MaxLpddrIndex, OverrideValue) ] : LpddrOdtDic[MIN (MaxLpddrIndex, LpddrMr & 0x3) ];
      } else if (DdrType == MRC_DDR_TYPE_DDR3) {
        Ddr3ModeRegister2.Data  = MR[mrMR2];
        Impedance = Override ? RttWrDic[MIN (DDR3_MODE_REGISTER_2_Rtt_WR_MAX, OverrideValue) ] : RttWrDic[Ddr3ModeRegister2.Bits.DynamicOdt];
      } else { // DDR4
        Ddr4ModeRegister2.Data  = MR[mrMR2];
        Impedance = Override ? Ddr4RttWrDic[MIN (DDR4_MODE_REGISTER_2_Rtt_WR_MAX, OverrideValue) ] : Ddr4RttWrDic[Ddr4ModeRegister2.Bits.DynamicOdt];
      }
      break;

    case (OptDimmOdtNom) :
    case (OptDimmOdtNomNT) :
      if (DdrType == MRC_DDR_TYPE_DDR3) {
        Ddr3ModeRegister1.Data  = MR[mrMR1];
        Impedance = Override ? RttNomDic[MIN (DDR3_MODE_REGISTER_1_Rtt_Nom_A9_A6_A2_MAX, OverrideValue) ] :
          RttNomDic[ (Ddr3ModeRegister1.Bits.OdtRttValueHigh << 2) |
          (Ddr3ModeRegister1.Bits.OdtRttValueMid  << 1) |
          Ddr3ModeRegister1.Bits.OdtRttValueLow];
      } else { // DDR4
        Ddr4ModeRegister1.Data  = MR[mrMR1];
        Impedance = Override ? Ddr4RttNomDic[MIN (DDR4_MODE_REGISTER_1_Rtt_Nom_MAX, OverrideValue) ] : Ddr4RttNomDic[Ddr4ModeRegister1.Bits.OdtRttValue];
      }
      break;

    case (OptDimmOdtPark) :
    case (OptDimmOdtParkNT) :
      if (DdrType == MRC_DDR_TYPE_DDR4) {
        Ddr4ModeRegister5.Data  = MR[mrMR5];
        Impedance = Override ? Ddr4RttNomDic[MIN (DDR4_MODE_REGISTER_5_Rtt_PARK_MAX, OverrideValue) ] : Ddr4RttNomDic[Ddr4ModeRegister5.Bits.RttPark];
      }
      break;

    case (OptDimmRon) :
      if (DdrType == MRC_DDR_TYPE_LPDDR3) {
        LpddrMr = MR[mrMR3];
        MaxLpddrIndex = ARRAY_COUNT (LpddrRonDic) - 1;
        Impedance = Override ? LpddrRonDic[MIN (MaxLpddrIndex, OverrideValue) ] : LpddrRonDic[MIN (MaxLpddrIndex, MAX (LpddrMr - 1, 0)) ];
      } else if (DdrType == MRC_DDR_TYPE_DDR3) {
        Ddr3ModeRegister1.Data  = MR[mrMR1];
        Impedance = Override ? Ddr3RonDic[MIN (DDR3_MODE_REGISTER_1_D_I_C_A5_A1_MAX, OverrideValue) ] : Ddr3RonDic[ (Ddr3ModeRegister1.Bits.ODImpedanceHigh << 1) |
          Ddr3ModeRegister1.Bits.ODImpedanceLow];
      } else { // DDR4
        Ddr4ModeRegister1.Data  = MR[mrMR1];
        Impedance = Override ? Ddr4RonDic[MIN (DDR4_MODE_REGISTER_1_D_I_C_MAX, OverrideValue) ] : Ddr4RonDic[Ddr4ModeRegister1.Bits.ODImpedance];
      }
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "undefined OptParam input for CalcDimmImpedance OptParam = %d\n", OptParam);
  }
  return Impedance;
}

/**
  This function returns the Actual Cpu Impedance in Ohms for given OptParam.
  The values will be taken from the host structure, unless override is used.

  @param[in] MrcData        - Pointer to MRC global data.
  @param[in] Channel        - channel to work on.
  @param[in] Rank           - rank to work on.
  @param[in] Byte           - byte to work on.
  @param[in] OptParam       - param to read
  @param[in] Override       - override enable to verf and offset
  @param[in] OffsetOverride - to override host read value
  @param[in] CompOverride   - override enable
  @param[in] VrefOverride   - value to override
  @param[in] CompCode       - value to override

  @retval Returns the DIMM driver impedance value in Ohms
**/
UINT16
CalcCpuImpedance (
  IN MrcParameters *const MrcData,
  IN UINT8                Channel,
  IN UINT8                Rank,
  IN UINT8                Byte,
  IN UINT8                OptParam,
  IN BOOLEAN              Override,
  IN INT8                 OffsetOverride,
  IN BOOLEAN              CompOverride,
  IN INT8                 VrefOverride,
  IN UINT8                CompCode
  )
{
  const MrcInput                            *Inputs;
  MrcIntOutput                              *IntOutputs;
  MrcIntControllerOut                       *IntControllerOut;
  MrcOutput                                 *Outputs;
  MrcChannelOut                             *ChannelOut;
  UINT32                                    Result;
  UINT16                                    Rext;
  UINT8                                     StepSize;
  UINT8                                     RComp;
  UINT8                                     LegsPerSeg;
  UINT8                                     RatioR2r;
  UINT32                                    Rleg;
  UINT8                                     Segments;
  UINT16                                    Divider;
  UINT8                                     OdtLegsOn;
  UINT8                                     CurrentComp;
  INT8                                      VrefOffset;
  INT16                                     DigiOffset;
  DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetComp;
  DDRCOMP_CR_DDRCRCOMPCTL0_STRUCT           DdrCrCompCtl0;
  BOOLEAN                                   UlxUlt;

  IntOutputs               = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut         = &IntOutputs->Controller[0];
  Inputs                   = &MrcData->Inputs;
  Outputs                  = &MrcData->Outputs;
  ChannelOut               = &Outputs->Controller[0].Channel[Channel];
  DdrCrDataOffsetComp.Data = ChannelOut->DataCompOffset[Byte];
  DdrCrCompCtl0.Data       = IntControllerOut->CompCtl0.Data;
  UlxUlt                   = ((Inputs->CpuModel == cmSKL_ULX_ULT) || (Inputs->CpuModel == cmKBL_ULX_ULT));

  if (CompOverride) {
    VrefOffset = VrefOverride;
    CurrentComp = CompCode;
  } else {
    CurrentComp = GetCompCode (MrcData, OptParam, 0); // Get comp code up
    if (OptParam == OptRdOdt) {
      VrefOffset   = (INT8) MrcSE ((UINT8) DdrCrCompCtl0.Bits.DqOdtVref, DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_WID, 8);
    } else if (OptParam == OptWrDS || OptParam == OptTxEq) {
      VrefOffset = (INT8) MrcSE ((UINT8) DdrCrCompCtl0.Bits.DqDrvVref, DDRCOMP_CR_DDRCRCOMPCTL0_DqDrvVref_WID, 8);
    } else {
      VrefOffset = 0;
    }
  }

  OdtLegsOn = 1;
  RatioR2r  = 46; // ratio times x10 @todo: wait for more DV data - first data shows we need to set ratio to 4.8 for code > 32 and 4.2 otherwise

  if (OptParam == OptRdOdt) {
    LegsPerSeg = 5;
    StepSize = 96;
    RComp = 0;  // RCOMP0 controls read DQ ODT
    if (Inputs->EnVttOdt) {
      Segments = 1; // in Vtt mode the segment is compensated to the actual ext. resistor
    } else {
      Segments = 2; // in Odt mode we have 1 segment but we treat up & dn as 2
    }
    OdtLegsOn = DdrCrCompCtl0.Bits.DisableOdtStatic ? 0 : 1;
    if (Override) {
      DigiOffset = OffsetOverride;
    } else {
      DigiOffset = (INT8) MrcSE ((UINT8) DdrCrDataOffsetComp.Bits.DqOdtUpCompOffset, DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_WID, 8);
    }
  } else if ((OptParam == OptWrDS) || (OptParam == OptTxEq)) {
    Segments = (UlxUlt) ? 2 : 3;
    //
    // TxEq full drive bits [4:5]
    // A0: ULX - 3, 6, 8, 10  DT - 4, 8, 12, 15
    // B0: ULX - 4, 6, 8, 10  DT - 6, 9, 12, 15
    //
    LegsPerSeg = ((0x3 & (ChannelOut->TxEq[Rank][Byte] >> 4)) + 2 ) * Segments;
    StepSize = 64;
    RComp = 1;  // RCOMP1 controls write drive strength
    if (Override) {
      DigiOffset = OffsetOverride;
    } else { // from host
      if (OptParam == OptWrDS) {
        DigiOffset = (INT8) MrcSE ((UINT8) DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset, DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_WID, 8);
      } else { // OptTxEq
        DigiOffset = (UlxUlt) ? (((0xF & (ChannelOut->TxEq[Rank][Byte])) * 2 + 2) / 3) : (0xF & (ChannelOut->TxEq[Rank][Byte]));// in ulx num legs 0-10
      }
    }
  } else {
    return 0;
  }

  if ((StepSize / 2 + VrefOffset) == 0) {  // protect divide by zero
    return 0;
  } else {
    Rext = Inputs->RcompResistor[RComp];
    //
    // Calc global (Comp) value
    //
    Result = Rext * (StepSize / 2 - VrefOffset) / (StepSize / 2 + VrefOffset);
    Rleg = Result * (OdtLegsOn * (LegsPerSeg * RatioR2r) + CurrentComp * 10);
  }

  if (OptParam == OptTxEq) { // we calc here the tx relative to global drv value
    DigiOffset = RatioR2r * DigiOffset; // total number of static legs
    if (DigiOffset == 0) {
      Result = 0xFFFF; // Infinite resistance
    } else {
      Result = DIVIDEROUND (Rleg, DigiOffset); // result is for entire buffer
    }
  } else {
    Divider = OdtLegsOn * (LegsPerSeg * RatioR2r)  + 10 * (CurrentComp + DigiOffset);
    if (Divider == 0) {
      Divider = 1;
    }
    Result = DIVIDEROUND (Rleg , (Divider * Segments));
  }
  return (UINT16) Result;
}

/**
  Calculate Power for the selected Opt param based on

  @param[in] MrcData     - Include all MRC global data.
  @param[in] Channel     - Channel to work on
  @param[in] Rank        - Rank to work on
  @param[in] Byte        - Byte to work on
  @param[in] OptParam    - The Opt Parameters to work on
  @param[in] Offset      - The corresponded Offsets to work on
  @param[in] OptParamLen - Length of the Optparam list
  @param[in] CurrentComp - The current Comp code for OptParam
  @param[in] ReadHost    - Switch to read current offset and CompCode from Host structure.

  @retval Calc power in mW
**/
MrcStatus
CalcOptPowerByte (
  IN MrcParameters   *MrcData,
  IN MrcPower        *Power,
  IN UINT8           Channel,
  IN UINT8           Rank,
  IN UINT8           Byte,
  IN const UINT8     *OptParam,
  IN INT8            *Offset,
  IN UINT8           OptParamLen,
  IN INT8            CurrentComp,
  IN UINT8           Scale
  )
{
  const MRC_FUNCTION                        *MrcCall;
  const MrcInput                            *Inputs;
  MrcDebug                                  *Debug;
  MrcOutput                                 *Outputs;
  MrcIntOutput                              *IntOutputs;
  MrcChannelOut                             *ChannelOut;
  MrcIntControllerOut                       *IntControllerOut;
  static const UINT16                       RxPowerConstuW[][2] = {{1288,900}, {1525, 1105}, {1800, 1180}}; // [Vddq current/Vccio Current][ULX/ULT/ULT(DDR3)]  - 100x [mA]  Per Byte
  static const UINT16                       RxPowerScaleSKL[] = {125, 250, 375, 500, 625, 750, 875, 1000, 1125, 1250, 1375, 1500, 1625, 1750, 1875, 2000};
  UINT8                                     RxDefault;
  UINT32                                    CPURXPower;
  DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetComp;
  UINT16                                    TxParamVector[MaxTxPowerParam];
  UINT16                                    RxParamVector[MaxRxPowerParam];
  BOOLEAN                                   Override;
  UINT8                                     Idx;
  MRC_POWER_SYS_CONFIG                      SysConfig;
  DimmRttWr                                 DimmWrOdt;
  INT8                                      LocalOffset;
  DDRCOMP_CR_DDRCRCOMPCTL1_STRUCT           DdrCrCompCtl1;
  UINT16                                    BufferStageDelayPS;
  UINT8                                     ScaleRdPwr;
  UINT8                                     ScaleWrPwr;
  UINT16                                    DimmRon;
  BOOLEAN                                   Ddr4;
  UINT32                                    VccIO;
  UINT32                                    Vdd;
  UINT8                                     BiasConfig;
  UINT8                                     NumStages;
  UINT8                                     SlewRateCompCells;
  SCompType                                 SlewRateType;

  Inputs                   = &MrcData->Inputs;
  Outputs                  = &MrcData->Outputs;
  IntOutputs               = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  Debug                    = &Outputs->Debug;
  ChannelOut               = &Outputs->Controller[0].Channel[Channel];
  IntControllerOut         = &IntOutputs->Controller[0];
  MrcCall                  = Inputs->Call.Func;
  Ddr4                     = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  VccIO                    = Inputs->VccIomV;
  Vdd                      = Outputs->VddVoltage[Inputs->MemoryProfile];

  DdrCrDataOffsetComp.Data = ChannelOut->DataCompOffset[Byte];
  DdrCrCompCtl1.Data       = IntControllerOut->CompCtl1.Data;
  ScaleRdPwr = 60;
  ScaleWrPwr = 40;

  //
  // Tx
  //
  TxParamVector[MbLengthTx] = 1000; // @todo: Mrc inputs [mil's]
  // keep within the simulation range
  TxParamVector[MbLengthTx] = RANGE (TxParamVector[MbLengthTx], 800, 2800);

  TxParamVector[SoDimmLenTx] = 200;  // @todo: Mrc inputs [mil's]
  // keep within the simulation range
  TxParamVector[SoDimmLenTx] = RANGE (TxParamVector[SoDimmLenTx], 50, 900);

  Idx = MrcSearchList (OptWrDS, OptParam, OptParamLen);
  Override = (Idx == 0) ? FALSE : TRUE;
  LocalOffset = (Override) ? Offset[Idx - 1] : 0;
  TxParamVector[CpuRon]  = CalcCpuImpedance (
                             MrcData,
                             Channel,
                             Rank,
                             Byte,
                             OptWrDS,
                             Override,
                             LocalOffset,
                             Override,
                             (UINT8) IntControllerOut->CompCtl0.Bits.DqDrvVref,
                             CurrentComp
                             );
  // keep within the simulation range
  TxParamVector[CpuRon] = RANGE (TxParamVector[CpuRon], 35, 65);

  Idx = MrcSearchList (OptSComp, OptParam, OptParamLen);
  Override = (Idx == 0) ? FALSE : TRUE;
  if (Override) {
    LocalOffset = Offset[Idx - 1];
  } else {
    LocalOffset = (INT8) MrcSE ((UINT8) DdrCrDataOffsetComp.Bits.DqSlewRateCompOffset, DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_WID, 8);
  }
  // read global cell delay for Tx
  SlewRateCompCells = (UINT8) DdrCrCompCtl1.Bits.DqScompCells;
  SlewRateType  = (SCompType) DdrCrCompCtl1.Bits.DqScompPC;
  NumStages = (SlewRateType == ScompTypePhase) ? 2 * (SlewRateCompCells + 1) : (SlewRateCompCells + 1);
  BufferStageDelayPS = DIVIDEROUND (Outputs->Qclkps, NumStages);
  TxParamVector[CpuCellDelay] = BufferStageDelayPS * ((UINT16) MrcPercentPower ((LocalOffset < 0) ? 95 : 105, ABS(LocalOffset))) / 100; // simple linear T-line
  // keep within the simulation range
  TxParamVector[CpuCellDelay] = RANGE (TxParamVector[CpuCellDelay], 10, 100);

  Idx = MrcSearchList (OptTxEq, OptParam, OptParamLen);
  Override = (Idx == 0) ? FALSE : TRUE;
  LocalOffset = (Override) ? Offset[Idx - 1] : 0;
  TxParamVector[CpuTxEq]  = CalcCpuImpedance (
                              MrcData,
                              Channel,
                              Rank,
                              Byte,
                              OptTxEq,
                              Override,
                              LocalOffset,
                              Override,
                              (UINT8) IntControllerOut->CompCtl0.Bits.DqDrvVref,
                              CurrentComp
                              );
  // x2 to match simulation input for the RSM calc. and clip to range [100 - 700]
  TxParamVector[CpuTxEq] *= 2;
  TxParamVector[CpuTxEq] = RANGE (TxParamVector[CpuTxEq], 100, 700);

  if (Ddr4) {
    Idx = MrcSearchList (DimmWrOdtNT, OptParam, OptParamLen);
    Override = (Idx == 0) ? FALSE : TRUE;
    LocalOffset = (Override) ? Offset[Idx - 1] : 0;
    TxParamVector[DimmWrOdtNT]  = MrcGetEffDimmWriteOdt(MrcData, Channel, Rank, 1, FALSE);
    // keep within the simulation range
    TxParamVector[DimmWrOdtNT] = RANGE (TxParamVector[DimmWrOdtNT], 100, 500);
  } else {
    // in LP3 and DDR3 we use entry [3] for Mb_len
    TxParamVector[DimmWrOdtNT] = TxParamVector[MbLengthTx];
  }

  Idx = MrcSearchList (OptDimmOdtWr, OptParam, OptParamLen);
  Override = (Idx == 0) ? FALSE : TRUE;
  LocalOffset = (Override) ? Offset[Idx - 1] : 0;
  DimmWrOdt = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtWr, Override, LocalOffset);
  if (DimmWrOdt == 0xFFFF) {// DDR4 HiZ
    DimmWrOdt = 0;
  } else if (DimmWrOdt == 0) {// when dynamic odt off the nom is picked
    DimmWrOdt = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtNom, Override, LocalOffset);
  }


  //
  // Rx
  //
  RxParamVector[MbLengthRx]   = 1000; //@todo: Mrc inputs [mil's]
  // keep within the simulation range
  RxParamVector[MbLengthRx]   = RANGE (RxParamVector[MbLengthRx], 800, 2800);
  RxParamVector[SoDimmLenRx]  = 200;  //@todo: Mrc inputs [mil's]
  // keep within the simulation range
  RxParamVector[SoDimmLenRx]  = RANGE (RxParamVector[SoDimmLenRx], 50, 900);

  Idx = MrcSearchList (OptRdOdt, OptParam, OptParamLen);
  Override = (Idx == 0) ? FALSE : TRUE;
  LocalOffset = (Override) ? Offset[Idx - 1] : 0;
  RxParamVector[CpuOdt]  = CalcCpuImpedance (
                             MrcData,
                             Channel,
                             Rank,
                             Byte,
                             OptRdOdt,
                             Override,
                             LocalOffset,
                             Override,
                             (UINT8) IntControllerOut->CompCtl0.Bits.DqDrvVref,
                             CurrentComp
                             );
  // keep within the simulation range
  RxParamVector[CpuOdt] = RANGE (RxParamVector[CpuOdt], 60, 500);

  Idx = MrcSearchList (DimmRdOdtNT, OptParam, OptParamLen);
  Override = (Idx == 0) ? FALSE : TRUE;
  LocalOffset = (Override) ? Offset[Idx - 1] : 0;
  RxParamVector[DimmRdOdtNT]  = MrcGetEffDimmWriteOdt (MrcData, Channel, Rank, 1, FALSE);
  // keep within the simulation range
  RxParamVector[DimmRdOdtNT] = RANGE (RxParamVector[DimmRdOdtNT], 60, 500);

  Idx = MrcSearchList (OptDimmRon, OptParam, OptParamLen);
  Override = (Idx == 0) ? FALSE : TRUE;
  LocalOffset = (Override) ? Offset[Idx - 1] : 0;
  DimmRon = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmRon, Override, LocalOffset);


  Idx = MrcSearchList (OptRxBias, OptParam, OptParamLen);
  Override = (Idx == 0) ? FALSE : TRUE;
  //
  // RX BIAS calculations
  //
  if (VccIO < 900) {
    // LPDDR3 UlX - 0.85v
    BiasConfig = 0;
    RxDefault  = 8;
  } else if (Outputs->DdrType == MRC_DDR_TYPE_DDR3) {
    // DDR3 Ult - 0.95v
    BiasConfig = 2;
    RxDefault = 7;
  } else {
    // LPDDR3 Ult - 0.95v
    BiasConfig = 1;
    RxDefault  = 8;
  }

  CPURXPower = Vdd * RxPowerConstuW[BiasConfig][0] / 100 + VccIO * RxPowerConstuW[BiasConfig][1] / 100;

  if (Override) {
    LocalOffset = (UINT8) Offset[Idx - 1];
    LocalOffset = RANGE (LocalOffset, 0, 15);
  } else {
    LocalOffset = (UINT8) IntControllerOut->Channel[Channel].DqControl1[Byte].Bits.RxBiasCtl;
  }

  CPURXPower  = (RxPowerScaleSKL[ (UINT8) LocalOffset] * CPURXPower) / RxPowerScaleSKL[RxDefault];
  CPURXPower /= 1000; // div by 1000 to get mW (result is per byte)
  Power->RdPower += (UINT16) CPURXPower * Scale;

  // Set the RSM configuration for Tx
  SysConfig.Data = 0;
  SysConfig.Bits.DdrType = Outputs->DdrType;
  SysConfig.Bits.Frequency = Outputs->Frequency;
  SysConfig.Bits.RttWr = DimmWrOdt;
  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DimmWrOdt: %d ch %d  rank %d\n", DimmWrOdt, Channel, Rank);
  GetPowerTable (MrcData, &SysConfig, &(IntOutputs->SysTxPowerFormula),  RSMPowerCalcTableTx, sizeof (RSMPowerCalcTableTx) / sizeof (MRC_RSM_POWER_FORMULA));
  // calc Tx Power
  Power->WrPower += (UINT16) CalcPowerRSM (
                               MrcData,
                               IntOutputs->SysTxPowerFormula,
                               TxParamVector,
                               Ddr4 ? 6 : 4,
                               Scale
                               );

  // Set the RSM configuration for Rx
  SysConfig.Data = 0;
  SysConfig.Bits.DdrType = MRC_DDR_TYPE_DDR4; // we currently have only DDR4 equ. Outputs->DdrType;
  SysConfig.Bits.Frequency = f1333; // we currently have only 1333 equ. Outputs->Frequency;
  SysConfig.Bits.RttWr = DimmRon; //  we currently have only 34 and 48 values
  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DimmWrOdt: %d ch %d  rank %d\n", DimmWrOdt, Channel, Rank);
  GetPowerTable (MrcData, &SysConfig, &(IntOutputs->SysRxPowerFormula),  RSMPowerCalcTableRx, sizeof (RSMPowerCalcTableRx) / sizeof (MRC_RSM_POWER_FORMULA));

  // calc Rx Power
  Power->RdPower += (UINT16) CalcPowerRSM (
                               MrcData,
                               IntOutputs->SysRxPowerFormula,
                               RxParamVector,
                               4,
                               Scale
                               );

  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Power->RdPower : %d Power->WrPower: %d ParamVector: %d ParamVector: %d ParamVector: %d ParamVector: %d \n", Power->RdPower, Power->WrPower, ParamVector[0], ParamVector[1], ParamVector[2], ParamVector[3]);
  Power->TotalPwr = ((Power->RdPower * ScaleRdPwr ) + (Power->WrPower * ScaleWrPwr )) / 100; // [mW] when Scale=1
  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Power->TotalPwr %d\n", Power->TotalPwr);
  return mrcSuccess;
}

#if EYE_MARGIN_SUPPORT
/**
  This function prints out the Margin eye diagram for ParamT/ParamV.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Channel to margin.
  @param[in] Ranks   - Bit mask of Ranks to margin.
  @param[in] ParamT  - Time parameter to margin.
  @param[in] ParamV  - Voltage parameter to margin.
  @param[in] Start   - Starting point for margining.
  @param[in] Stop    - Stopping point for margining.
  @param[in] Repeats - Number of times to repeat the test to average out any noise.
  @param[in] NoPrint - Switch to skip printing.

  @retval Nothing
**/
void
EyeMargin (
  IN MrcParameters *const MrcData,
  IN UINT8                Channel,
  IN UINT8                Ranks,
  IN UINT8                ParamT,
  IN UINT8                ParamV,
  IN UINT8                CmdIteration,
  IN INT8                 Start,
  IN INT8                 Stop,
  IN UINT16               SearchLimits,
  IN UINT8                LoopCount,
  IN UINT8                Repeats,
  IN BOOLEAN              NoPrint
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcControllerOut  *ControllerOut;
  MrcStatus         Status;
  UINT32            (*MarginByte) [MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32            BERStats[4];
  UINT16            SaveMargin[63][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  BOOLEAN           Eye[63][108];
  BOOLEAN           Lines[108];
  UINT8             MaxH=108;
  UINT8             MaxW=63;
  UINT8             i,j;
  UINT16            MinEdge;
  UINT8             ResultTypeV = 0;
  UINT8             ChBitMask;
  UINT8             Byte;
  UINT8             Rank;
  UINT8             Edge;
  UINT8             FirstRank;
  UINT8             NumBytes;
  UINT8             BMap[9];  // Need by GetBERMarginByte
  UINT8             MaxMarginV;
  UINT8             localR[MAX_CHANNEL];
  UINT8             Rep;
  INT8              Index;
  UINT8             IndexOff;
  INT8              Off;
  UINT8             OffStep;
  UINT8             byteMax[MAX_CHANNEL];
  UINT32            Offset;
  UINT64            CrValue64;
  UINT8             sign;
  UINT8             Channeloop;
  UINT8             RankMask;
  UINT8             SafeOff[MAX_CHANNEL]={0,0};
  UINT8             CurrValue;
  BOOLEAN           RunAllCh;
  BOOLEAN           Ddr4;
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  MarginByte    = &Outputs->MarginResult;
  ControllerOut = &Outputs->Controller[0];
  IndexOff      = 0;
  CrValue64     = 0x0ULL; //64 bit Data bit mask
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  RunAllCh      = TRUE;

  MrcCall->MrcSetMem ((UINT8 *) localR, sizeof (localR), 0);
  MrcCall->MrcSetMem ((UINT8 *) Eye, sizeof (Eye), 0);
  MrcCall->MrcSetMem ((UINT8 *) Lines, sizeof (Lines), 0);
  MrcCall->MrcSetMem ((UINT8 *) SaveMargin, sizeof (SaveMargin), 0);
  MrcCall->MrcSetMemDword (BERStats, sizeof (BERStats) / sizeof (UINT32), 0);
  for (Byte = 0; Byte < ARRAY_COUNT (BMap); Byte++) {
    BMap[Byte] = Byte;
  }

  if ((ParamT == CmdT) | (ParamT == CmdV)) {
    SetupIOTestCADB (MrcData, Outputs->ValidChBitMask, LoopCount, NSOE, 1, 0);
  }
  else {
    SetupIOTestBasicVA(MrcData, Outputs->ValidChBitMask, LoopCount, 0, 0, 0,8);  //set test to all channels
  }
  //
  // Select All Ranks for REUT test
  //

  //
  // use ChBitMask from here down - if ch is set that mean at least 1 rank for testing, also remove ch w/o active ranks
  //
  ChBitMask = 0;
  for (Channeloop = 0; Channeloop < MAX_CHANNEL; Channeloop++) {
    if (!((MRC_BIT0 << Channeloop) & Outputs->ValidChBitMask)) {
      continue;
    }
    ChannelOut      = &ControllerOut->Channel[Channeloop];
    if (Channeloop == Channel) {
      RankMask = Ranks & ChannelOut->ValidRankBitMask;
    } else {
      // run the other channel with existing ranks
      RankMask = RunAllCh? ChannelOut->ValidRankBitMask : 0;
    }
    //
    // use ChBitMask from here down - if ch is set that mean at least 1 rank for testing, also remove ch w/o active ranks
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Eye Margin Channeloop %d RankMask = %02X\n", Channeloop, RankMask);
    ChBitMask |= SelectReutRanks (MrcData, Channeloop, RankMask, 0);

  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Eye Margin ChBitMask = %02X\n", ChBitMask);
  if (!(ChBitMask & (0x1 << Channel))) {
    return;
  }

  ChannelOut      = &ControllerOut->Channel[Channel];
  localR[Channel] = ChannelOut->ValidRankBitMask & Ranks;

  for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
    ChannelOut->DataOffsetTrain[Byte] = 0;
  }
  //
  // Find the first selected rank
  //
  FirstRank = 0;
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((1 << Rank) & localR[Channel]) {
      FirstRank = Rank;  // could be in any channel
      break;
    }
  }

  //
  // Store margin results for
  //
  NumBytes = (UINT8) Outputs->SdramCount;
  if (ParamV == CmdV) {
    NumBytes = 1;
  }

  //
  // Loop through all Test Params and Measure Margin
  //

  Offset = MCHBAR_CH0_CR_REUT_CH_ERR_DATA_MASK_REG +
    ((MCHBAR_CH1_CR_REUT_CH_ERR_DATA_MASK_REG - MCHBAR_CH0_CR_REUT_CH_ERR_DATA_MASK_REG) * Channel);

  MrcWriteCR64 (MrcData, Offset, CrValue64);

  //
  // Find MaxMargin for this channel
  //
  MaxMarginV = MAX_POSSIBLE_VREF;
#if (SUPPORT_DDR4 == SUPPORT)
  if ((Outputs->DdrType == MRC_DDR_TYPE_DDR4) && (ParamV == WrV)) {
    MaxMarginV = MAX_POSSIBLE_DDR4_WRITE_VREF;
  }
#endif //SUPPORT_DDR4
  if (MAX_POSSIBLE_TIME < Stop) {
    Stop = MAX_POSSIBLE_TIME;
  }

  if (-MAX_POSSIBLE_TIME > Start) {
    Start = -MAX_POSSIBLE_TIME;
  }

  if (ParamT == RdT) {
    for (sign = 0; sign < 2; sign++) {
      byteMax[sign] = sign? ABS (Stop) : ABS (Start);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        byteMax[sign] = MrcCalcMaxRxMargin (MrcData, ParamT, Channel, FirstRank, Byte, 0, byteMax[sign]);
      }
    }
    Start = - byteMax[0];
    Stop  = byteMax[1];
  }

  IndexOff = MaxW / 2 + Start;
  //
  // No need to search too far
  //
  if (MaxMarginV > SearchLimits) {
    MaxMarginV = (UINT8) (SearchLimits);
  }

  OffStep = 1;

  for (Off = Start; Off < Stop + 1; Off += OffStep) {
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Timing: %d\n", Off);
    Index = Off - Start;
    //
    // change margin ParamT
    //
    //selects CmdT iteration
    //  MrcIterationClock = 0,
    //  MrcIterationCkmdN  = 1,
    //  MrcIterationCmdS  = 2,
    //  MrcIterationCke   = 3,
    //  MrcIterationCtl   = 4,
    //  MrcIterationCmdV  = 5,

    if (ParamT == CmdT) { // maybe add cmd group - cmd, ctl, address
      if (CmdIteration == MrcIterationClock) {
        ShiftPIforCmdTraining (MrcData, Channel, CmdIteration, localR[Channel], 3,  Off, 0); // the 3 is to select two packages (groups)
      }
      if (CmdIteration == MrcIterationCmdN) {
        ShiftPIforCmdTraining (MrcData, Channel, CmdIteration, localR[Channel], 2, ChannelOut->CmdnCmdPiCode[1] + Off, 0);
      }
      if (CmdIteration == MrcIterationCmdS) {
        ShiftPIforCmdTraining (MrcData, Channel, CmdIteration, localR[Channel], 1, ChannelOut->CmdsCmdPiCode[0] + Off, 0);
        ShiftPIforCmdTraining (MrcData, Channel, CmdIteration, localR[Channel], 2, ChannelOut->CmdsCmdPiCode[1] + Off, 0);
      }
      if (CmdIteration == MrcIterationCke) {
        ShiftPIforCmdTraining (MrcData, Channel, CmdIteration, localR[Channel], 1, ChannelOut->CkeCmdPiCode[0] + Off, 0);
      }
      if (CmdIteration == MrcIterationCtl) {
        CurrValue = 0;
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (localR[Channel] & (1 << Rank)) {
            CurrValue = ChannelOut->CtlPiCode[Rank];
            break;
          }
        }
        ShiftPIforCmdTraining (MrcData, Channel, CmdIteration, localR[Channel], localR[Channel], CurrValue + Off, 0);
      }
      MrcResetSequence (MrcData);
    }
    else {
      for (Byte = 0; Byte < NumBytes; Byte++) {
        Status = ChangeMargin (MrcData, ParamT, Off, 0, 0, Channel, FirstRank, Byte, 0, 1, 0, MrcRegFileStart);
      }
    }
    ResultTypeV = GetMarginResultType (ParamV); // rxv=0 rxt=1
    //
    // Assign to last pass margin results by reference
    // get lowest margin from all ch/rankS/byte save in FirstRank
    //
    if (ParamT != CmdT) {
      Status = GetMarginByte (
                 MrcData,
                 Outputs->MarginResult,
                 ParamV,
                 FirstRank,
                 localR[Channel]
                 );
    }
    for (Rep = 0; Rep < Repeats; Rep++) {
      //
      // Run Margin Test - margin_1d with chosen param
      // run on all ranks but change param only for firstRank??
      //
      if (ParamV != CmdV) {
        Status = MrcGetBERMarginByte (
                   MrcData,
                   Outputs->MarginResult,
                   ChBitMask,
                   (Ddr4 && (ParamV == WrV)) ? localR[Channel] : FirstRank,
                   (Ddr4 && (ParamV == WrV)) ? localR[Channel] : FirstRank,
                   ParamV,
                   0, // Mode
                   BMap,
                   0,
                   MaxMarginV,
                   0,
                   BERStats
                   );
      }
      else {
        //
        // Run test for Cmd Voltage
        //
        Status = MrcGetBERMarginCh (
                   MrcData,
                   Outputs->MarginResult,
                   ChBitMask,
                   0xFF,
                   FirstRank,
                   CmdV,
                   0, // Mode
                   0,
                   MaxMarginV,
                   0,
                   BERStats
                   );
        //         ShiftCh2Ch (MrcData, 0xff, SafeOff, 1, 0, 0, 0);
        //         Status = MrcResetSequence (MrcData);
        //         ShiftPIforCmdTraining (MrcData, 1 << Channel, CmdIteration, localR[Channel], 3, Off, 0); // the 3 is to select two packages (groups)
      }
      //
      // Record Results
      //
      for (Edge = 0; Edge < MAX_EDGES; Edge++) {
        for (Byte = 0; Byte < NumBytes; Byte++) {
          if ((Index > 62) || (Index < 0)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: SaveMargin array out of bounds! %d", Index);
            return;
          }

          if (Rep == 0) {
            SaveMargin[Index][Channel][Byte][Edge] = 0;
          }

          SaveMargin[Index][Channel][Byte][Edge] += (UINT16) (*MarginByte) [ResultTypeV][FirstRank][Channel][Byte][Edge];
        }
      }
    }

    for (Edge = 0; Edge < MAX_EDGES; Edge++) {
      MinEdge = 0xFFFF;
      for (Byte = 0; Byte < NumBytes; Byte++) {
        if ((Index > 62) || (Index < 0)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: SaveMargin array out of bounds! %d", Index);
          return;
        }

        SaveMargin[Index][Channel][Byte][Edge] /= Repeats;
        if (MinEdge > SaveMargin[Index][Channel][Byte][Edge]) {
          MinEdge = SaveMargin[Index][Channel][Byte][Edge];
        }
      }

      if (((Index + IndexOff) > 62) ||
          ((Index + IndexOff) < 0) ||
          ((MaxH / 2 - (MinEdge - 1) / 10) > 107) ||
          ((MaxH / 2 - (MinEdge - 1) / 10) < 0) ||
          ((MaxH / 2 + (MinEdge - 1) / 10) > 107) ||
          ((MaxH / 2 + (MinEdge - 1) / 10) < 0)
          ) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: Eye or Lines array out of bounds!\n");
        return;
      }

      if (Edge) {
        Eye[Index + IndexOff][MaxH / 2 - (MinEdge - 1) / 10]  = 1;
        Lines[MaxH / 2 - (MinEdge - 1) / 10]                  = 1;
      } else {
        Eye[Index + IndexOff][MaxH / 2 + (MinEdge - 1) / 10]  = 1;
        Lines[MaxH / 2 + (MinEdge - 1) / 10]                  = 1;
      }
    }
  }//end of offset
  //
  // Print the box
  //
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Plot Eye across ParamT = %s ParamV = %s CmdIter =%s settings:(Start=%d,Stop=%d) LC = %d  Channel = %d Ranks = 0x%x\n",
    MarginTypesString[ParamT],
    MarginTypesString[ParamV],
    CmdIterTypesString[CmdIteration],
    Start,
    Stop,
    LoopCount,
    Channel,
    localR[Channel]
    );
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t------------------------------- +++++++++++++++++++++++++++++++\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t332222222222111111111100000000000000000001111111111222222222233\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Vref\t109876543210987654321098765432101234567890123456789012345678901\n");
  for (i = 0; i < MaxH; i++) {
    if (Lines[i]) {
      //
      // print only fail lines
      //
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%3d:\t", MaxH / 2 - i); // per ch
      for (j = 0; j < MaxW; j++) {
        if (Eye[j][i]) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", "#"); // per ch
        } else {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", ((j == (MaxW) / 2) || (i == (MaxH) / 2)) ? "+" : " "); // per ch
        }
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");//per ch
    }
  }
  //
  // Clean up after test
  //
  ChannelOut = &ControllerOut->Channel[Channel];
  MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
  if (ParamT != CmdT) {
    Status = ChangeMargin (MrcData, ParamT, 0, 0, 1, 0, 0, 0, 0, 0, 0, MrcRegFileCurrent);
  } else {
    //restore settings
    ShiftCh2Ch (MrcData, 0xff, SafeOff, 1, 0, 0, 0);
  }
  Status = MrcResetSequence (MrcData);
}
#endif // EYE_MARGIN_SUPPORT

/**
  This function fill the input array (e.g array[ch][rank]) with the power calculation
  per rank/ch for current sys. setting.

  @param[in]     MrcData   - MRC data struct;
  @param[in,out] PwrChRank - Array to fill;

  @retval Nothing
**/
void
CalcSysPower (
  IN     MrcParameters *const MrcData,
  IN OUT MrcPower             PwrChRank[MAX_CHANNEL][MAX_RANK_IN_CHANNEL]
  )
{
  MrcDebug                    *Debug;
  MrcChannelOut               *ChannelOut;
  MrcOutput                   *Outputs;
  MrcOdtPowerSaving           *OdtPowerSaving;
  UINT8                       Rank;
  UINT8                       Byte;
  UINT8                       Channel;
  UINT8                       TotalRankCount;
  UINT32                      PwrAvgRd;
  UINT32                      PwrAvgWr;
  UINT32                      PwrAvgTotal;

  Outputs         = &MrcData->Outputs;
  OdtPowerSaving  = &Outputs->OdtPowerSavingData;
  Debug           = &Outputs->Debug;
  TotalRankCount  = 0;
  PwrAvgRd        = 0;
  PwrAvgWr        = 0;
  PwrAvgTotal     = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      ChannelOut  = &Outputs->Controller[0].Channel[Channel];
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          // CalcOptPowerByte will sum the bytes to get overall power
          CalcOptPowerByte (MrcData, &PwrChRank[Channel][Rank], Channel, Rank, Byte, NULL, NULL, 0, 0, 10);
        }
        PwrAvgRd += PwrChRank[Channel][Rank].RdPower;
        PwrAvgWr += PwrChRank[Channel][Rank].WrPower;
        PwrAvgTotal += PwrChRank[Channel][Rank].TotalPwr;
        TotalRankCount++;
      }
    }
  }

  if (TotalRankCount == 0) {
    TotalRankCount = 1;  // Prevent divide by 0
  }

  PwrAvgRd    /= TotalRankCount;
  PwrAvgWr    /= TotalRankCount;
  PwrAvgTotal /= TotalRankCount;
  //
  // update Mrc struct with Base line numbers
  //
  if (OdtPowerSaving->BaseFlag == FALSE) {
    OdtPowerSaving->BaseSavingRd  = (UINT16) PwrAvgRd;
    OdtPowerSaving->BaseSavingWr  = (UINT16) PwrAvgWr;
    OdtPowerSaving->BaseSavingCmd = 0; // currently no power train for CMD
  } else {
    OdtPowerSaving->MrcSavingRd  = (UINT16) PwrAvgRd;
    OdtPowerSaving->MrcSavingWr  = (UINT16) PwrAvgWr;
    OdtPowerSaving->MrcSavingCmd = 0; // currently no power train for CMD
  }

  return;
}

/**
  This function optimize the digital offsets by reducing the digital
  offset and apply the difference to the global one.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Param      - Parameter defining the desired digital compensation offset.
  @param[in] UpdateHost - Decides if MrcData is to be updated.

  @retval The new comp value.
**/
UINT32
OptimizeCompOffset (
  IN MrcParameters *const MrcData,
  IN const UINT8          Param,
  IN const UINT8          UpdateHost
  )
{
  const MrcInput                            *Inputs;
  MrcDebug                                  *Debug;
  MrcIntOutput                              *IntOutputs;
  MrcIntControllerOut                       *IntControllerOut;
  MrcOutput                                 *Outputs;
  MrcControllerOut                          *ControllerOut;
  MrcChannelOut                             *ChannelOut;
  DDRCOMP_CR_DDRCRDATACOMP0_STRUCT          DdrCrDataComp0;
  DDRCOMP_CR_DDRCRDATACOMP1_STRUCT          DdrCrDataComp1;
  DDRCOMP_CR_DDRCRCOMPCTL0_STRUCT           DdrCrCompCtl0;
  DDRCOMP_CR_DDRCRCOMPCTL1_STRUCT           DdrCrCompCtl1;
  DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetComp;
  UINT8                                     GlobalParam;
  UINT8                                     CurrCompVref;
  INT8                                      NewCompVref;
  UINT8                                     CurrentComp;
  UINT8                                     CurrentCompDn;
  UINT8                                     NewComp;
  UINT8                                     NewCompDn;
  INT8                                      Sign;
  UINT8                                     Done;
  INT16                                     AvgOffset;
  UINT8                                     Offset;
  UINT8                                     OffsetDn;
  UINT8                                     StartDelta;
  UINT8                                     CurrDelta;
  UINT8                                     MinDelta;
  UINT8                                     Off;
  UINT8                                     BestVrefOff;
  UINT8                                     SignBit;
  UINT8                                     Byte;
  UINT8                                     Channel;
  UINT8                                     NumCh;
  UINT8                                     ReservedCodes;
  INT8                                      MaxCompVref;
  INT8                                      MinCompVref;
  UINT8                                     DqSCompPC;
  UINT8                                     CurrDqSCompPC;
  INT8                                      CompCodes[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT8                                      CompCodesDn[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32                                    RegisterValue;
  UINT8                                     RcompUp;
  UINT8                                     RcompDn;
  UINT8                                     SlewRateComp;

  IntOutputs                = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut          = &IntOutputs->Controller[0];
  Outputs                   = &MrcData->Outputs;
  ControllerOut             = &Outputs->Controller[0];
  Inputs                    = &MrcData->Inputs;
  Debug                     = &Outputs->Debug;
  DdrCrCompCtl0.Data        = IntControllerOut->CompCtl0.Data;
  DdrCrCompCtl1.Data        = IntControllerOut->CompCtl1.Data;

  DdrCrDataOffsetComp.Data  = 0;
  ReservedCodes             = 3;
  NewComp                   = 0;
  Offset                    = 0;
  SignBit                   = 0;
  DqSCompPC                 = 0;
  CurrDqSCompPC             = 0;
  CurrentCompDn             = 0;
  NewCompDn                 = 0;
  OffsetDn                  = 0;
  RcompUp = RcompDn = SlewRateComp = 0;

  if (Param == OptWrDS || Param == OptSComp) {
    RegisterValue = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRDATACOMP0_REG);
    DdrCrDataComp0.Data = RegisterValue;
    RcompUp   = (UINT8) DdrCrDataComp0.Bits.RcompDrvUp;
    RcompDn   = (UINT8) DdrCrDataComp0.Bits.RcompDrvDown;
    SlewRateComp = (UINT8) DdrCrDataComp0.Bits.SlewRateComp;
  } else {
    RegisterValue = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRDATACOMP1_REG);
    DdrCrDataComp1.Data = RegisterValue;
    RcompUp   = (UINT8) DdrCrDataComp1.Bits.RcompOdtUp;
    RcompDn   = (UINT8) DdrCrDataComp1.Bits.RcompOdtDown;
  }

  switch (Param) {
    case OptWrDS:
      CurrentComp         = RcompUp;
      CurrentCompDn       = RcompDn;
      CurrCompVref        = MrcSE ((UINT8) DdrCrCompCtl0.Bits.DqDrvVref, 4, 8);
      MaxCompVref         = (1 << (DDRCOMP_CR_DDRCRCOMPCTL0_DqDrvVref_WID - 1)) - 1;
      MinCompVref         = (-1) * (1 << (DDRCOMP_CR_DDRCRCOMPCTL0_DqDrvVref_WID - 1));
      GlobalParam         = WrDS;
      break;

    case OptRdOdt:
      CurrentComp         = RcompUp;
      CurrentCompDn       = RcompDn;
      CurrCompVref        = MrcSE ((UINT8) DdrCrCompCtl0.Bits.DqOdtVref, 5, 8);
      MaxCompVref         = (1 << (DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_WID - 1)) - 1;
      MinCompVref         = (-1) * (1 << (DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_WID - 1));
      GlobalParam         = RdOdt;
      break;

    case OptSComp:
      CurrentComp         = SlewRateComp;
      CurrDqSCompPC       = (UINT8) DdrCrCompCtl1.Bits.DqScompPC;
      CurrCompVref        = (UINT8) DdrCrCompCtl1.Bits.DqScompCells;
      MaxCompVref         = (1 << (DDRCOMP_CR_DDRCRCOMPCTL1_DqScompCells_WID)) - 1;
      MinCompVref         = 4;
      GlobalParam         = SCompDq;
      break;

    default:
      CurrentComp   = 0;
      CurrCompVref  = 0;
      MaxCompVref   = 0;
      MinCompVref   = 0;
      GlobalParam   = 0;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Invalid Param : %d", Param);
      break;
  }

  AvgOffset = 0;
  NumCh     = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((MrcChannelExist (Outputs, Channel))) {
      ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        DdrCrDataOffsetComp.Data = ChannelOut->DataCompOffset[Byte];
        if (Param == OptWrDS) {
          Offset  = (UINT8) DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset;
          OffsetDn  = (UINT8) DdrCrDataOffsetComp.Bits.DqDrvDownCompOffset;
          SignBit = 6;
        }

        if (Param == OptRdOdt) {
          Offset  = (UINT8) DdrCrDataOffsetComp.Bits.DqOdtUpCompOffset;
          OffsetDn  = (UINT8) DdrCrDataOffsetComp.Bits.DqOdtDownCompOffset;
          SignBit = 5;
        }

        if (Param == OptSComp) {
          Offset  = (UINT8) DdrCrDataOffsetComp.Bits.DqSlewRateCompOffset;
          OffsetDn = 0;
          SignBit = 5;
        }

        AvgOffset += (INT8) MrcSE (Offset, SignBit, 8);
        CompCodes[Channel][Byte] = CurrentComp + MrcSE (Offset, SignBit, 8);
        CompCodesDn[Channel][Byte] = CurrentCompDn + MrcSE (OffsetDn, SignBit, 8);
      }
    }
    NumCh++;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nParam:%s CompUp:%d CompDn:%d CompVref:%d", TOptParamOffsetString[Param], CurrentComp, CurrentCompDn, (INT8) CurrCompVref);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((MrcChannelExist (Outputs, Channel))) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nCh%dByte  ",Channel);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%d:% 3d/",Byte, (INT8) (CompCodes[Channel][Byte] - CurrentComp));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "% 3d\t", (INT8) (CompCodesDn[Channel][Byte] - CurrentCompDn));
      }
    }
  }
  Sign = (AvgOffset < 0) ? -1 : 1;
  //
  // Calculate the average offset and round to the nearest integer.
  //
  AvgOffset = (AvgOffset + Sign * NumCh * ((UINT8) Outputs->SdramCount) / 2) / (NumCh * ((UINT8) Outputs->SdramCount));

  if (AvgOffset == 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");
    return CurrentComp;
  }
  //
  // Find the CompVref minimum of the delta between (CurrentComp + AvgOffset) to NewComp.
  // Take care of keeping 3 code reserved.
  // Exit if no vref range left.
  //
  Done        = 0;
  Off         = 1;
  BestVrefOff = CurrCompVref;
  NewComp     = CurrentComp;
  DqSCompPC   = CurrDqSCompPC;
  StartDelta  = ABS ((INT8) AvgOffset);
  MinDelta    = StartDelta;
  if (Param == OptSComp) {
    Sign *= -1;
  }

  while (!Done) {
    NewCompVref = CurrCompVref + (Sign * Off);
    if ((MinCompVref > NewCompVref) || (NewCompVref > MaxCompVref)) {
      Done = 1;
    }
    if (Param == OptSComp) {
      if ((NewCompVref + 1) > 16) {
        DqSCompPC = 0;
      }

      NewCompVref = (DqSCompPC << 4) + NewCompVref;
    }
    NewComp   = (UINT8) UpdateCompGlobalOffset (MrcData, GlobalParam, NewCompVref, FALSE, 0);
    NewCompDn = GetCompCode(MrcData, Param, 1); // take care of up/dn
    //
    // Reserve 3 comp codes
    //
    if ((ReservedCodes > NewComp) || (NewComp > (63 - ReservedCodes))) {
      Done = 1;
    }
    if ((ReservedCodes > NewCompDn) || (NewCompDn > (63 - ReservedCodes))) {
      Done = 1;
    }

    if (!Done) {
      CurrDelta = ABS (CurrentComp + (INT8) AvgOffset - NewComp);
      if (CurrDelta < StartDelta) {
        if (CurrDelta < MinDelta) {
          MinDelta    = CurrDelta;
          BestVrefOff = NewCompVref;
          if (MinDelta == 0) {
            Done = 1;
          }
        }
      } else {
        Done = 1;
      }
    }

    Off++;
  }
  //
  // update new compVref setting
  //
  if (BestVrefOff != CurrCompVref) {
    NewComp = (UINT8) UpdateCompGlobalOffset (MrcData, GlobalParam, BestVrefOff, FALSE, UpdateHost);
    if (Param == OptWrDS) {
      DdrCrDataComp0.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRDATACOMP0_REG);
      NewCompDn  = (UINT8) DdrCrDataComp0.Bits.RcompDrvDown;
    }
    if (Param == OptRdOdt) {
      DdrCrDataComp1.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRDATACOMP1_REG);
      NewCompDn  = (UINT8) DdrCrDataComp1.Bits.RcompOdtDown;
    }
    //
    // Update all bytes with new offset: Offset + code - newcode = +newoffset
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
      if ((MrcChannelExist (Outputs, Channel))) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          UpdateOptParamOffset (MrcData, Channel, 0, Byte, Param, CompCodes[Channel][Byte] - NewComp, UpdateHost);
          if (Param == OptWrDS) {
            UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptWrDSDn, CompCodesDn[Channel][Byte] - NewCompDn, UpdateHost);
          } else if (Param == OptRdOdt) {
            UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptRdOdtDn, CompCodesDn[Channel][Byte] - NewCompDn, UpdateHost);
          }
        }
      }
    }
  } else {
    //
    // Restore CompVref
    //
    if (Param == OptSComp) {
      NewCompVref = (CurrDqSCompPC << 4) + CurrCompVref;
    }

    NewComp = (UINT8) UpdateCompGlobalOffset (MrcData, GlobalParam, CurrCompVref, FALSE, UpdateHost);
    if (Param == OptWrDS) {
      DdrCrDataComp0.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRDATACOMP0_REG);
      NewCompDn  = (UINT8) DdrCrDataComp0.Bits.RcompDrvDown;
    }
    if (Param == OptRdOdt) {
      DdrCrDataComp1.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRDATACOMP1_REG);
      NewCompDn  = (UINT8) DdrCrDataComp1.Bits.RcompOdtDown;
    }
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
      if ((MrcChannelExist (Outputs, Channel))) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          UpdateOptParamOffset (MrcData, Channel, 0, Byte, Param, CompCodes[Channel][Byte] - NewComp, UpdateHost);
          if (Param == OptWrDS) {
            UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptWrDSDn, CompCodesDn[Channel][Byte] - NewCompDn, UpdateHost);
          } else if (Param == OptRdOdt) {
            UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptRdOdtDn, CompCodesDn[Channel][Byte] - NewCompDn, UpdateHost);
          }
        }
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nParam:%s NewCompUp:%d NewCompDn:%d NewCompVref:%d", TOptParamOffsetString[Param], NewComp, NewCompDn, (INT8) BestVrefOff);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((MrcChannelExist (Outputs, Channel))) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nCh%dByte  ",Channel);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%d:% 3d/", Byte, (INT8) (CompCodes[Channel][Byte] - NewComp));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "% 3d\t", (INT8) (CompCodesDn[Channel][Byte] - NewCompDn));
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");
  return NewComp;
}

/**
  This step performs Comp Offset optimization on the param list defined in this function.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess
**/
MrcStatus
MrcOptimizeComp (
  IN MrcParameters *const MrcData
  )
{
  static const UINT8 ParamList[] = {OptWrDS, OptRdOdt, OptSComp};
  UINT8            Param;

  for (Param = 0; Param < ARRAY_COUNT (ParamList); Param++) {
    OptimizeCompOffset (MrcData, ParamList[Param], 1);
  }
#ifdef LB_STUB_FLAG
  return mrcFail;
#endif

  return mrcSuccess;
}

/**
  This function calculates the percent of power saving from the power optimization steps and
  updates the proper registers in the PCU.  To get the correct base line for this calculation,
  this routing needs to run first time early in the training in order to update the MrcStruct
  with the base line.  After the power training steps, it will run again to get the actual
  percent of power saving.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess

**/
MrcStatus
MrcPowerSavingMeter (
  IN MrcParameters *const MrcData
  )
{
  MrcDebug                                *Debug;
  const MRC_FUNCTION                      *MrcCall;
  const MrcInput                          *Inputs;
  MrcOutput                               *Outputs;
  MrcPower                                PwrChRank[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  MrcOdtPowerSaving                       *OdtPowerSaving;
  UINT8                                   PercentRd = 0;
  UINT8                                   PercentWr = 0;
  UINT8                                   PercentCmd = 0;
  PCU_CR_MRC_ODT_POWER_SAVING_PCU_STRUCT  CrMrcOdtPowerSavingPcu;

  Inputs          = &MrcData->Inputs;
  MrcCall         = Inputs->Call.Func;
  Outputs         = &MrcData->Outputs;
  Debug           = &Outputs->Debug;
  OdtPowerSaving  = &Outputs->OdtPowerSavingData;
  MrcCall->MrcSetMem ((UINT8 *) PwrChRank, sizeof (PwrChRank), 0);

  CalcSysPower (MrcData, PwrChRank);

  if (OdtPowerSaving->BaseFlag) {
    //
    // Calculate power saving and update PCU regs
    //
    if (OdtPowerSaving->BaseSavingRd > OdtPowerSaving->MrcSavingRd) {
      PercentRd = (UINT8) (((UINT32) (OdtPowerSaving->BaseSavingRd - OdtPowerSaving->MrcSavingRd) * 256) / OdtPowerSaving->BaseSavingRd);
    } else {
      PercentRd = 0;
    }

    if (OdtPowerSaving->BaseSavingWr > OdtPowerSaving->MrcSavingWr) {
      PercentWr = (UINT8) (((UINT32) (OdtPowerSaving->BaseSavingWr - OdtPowerSaving->MrcSavingWr) * 256) / OdtPowerSaving->BaseSavingWr);
    } else {
      PercentWr = 0;
    }

    if (OdtPowerSaving->BaseSavingCmd > OdtPowerSaving->MrcSavingCmd) {
      PercentCmd = (UINT8) (((UINT32) (OdtPowerSaving->BaseSavingCmd - OdtPowerSaving->MrcSavingCmd) * 256) / OdtPowerSaving->BaseSavingCmd);
    } else {
      PercentCmd = 0;
    }

    CrMrcOdtPowerSavingPcu.Bits.MRC_Saving_Rd   = PercentRd;
    CrMrcOdtPowerSavingPcu.Bits.MRC_Saving_Wt   = PercentWr;
    CrMrcOdtPowerSavingPcu.Bits.MRC_Saving_Cmd  = PercentCmd;

    MrcWriteCR (MrcData, PCU_CR_MRC_ODT_POWER_SAVING_PCU_REG, CrMrcOdtPowerSavingPcu.Data);
  } else {
    OdtPowerSaving->BaseFlag = TRUE;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "\tBaseLine\tMrcSaving\tSaving\nAvgRd\t%d\t\t%d\t\t%d%%\nAvgWr\t%d\t\t%d\t\t%d%%\n",
    OdtPowerSaving->BaseSavingRd/10,
    OdtPowerSaving->MrcSavingRd/10,
    ((UINT16) PercentRd) * 100 / 256,
    OdtPowerSaving->BaseSavingWr/10,
    OdtPowerSaving->MrcSavingWr/10,
    ((UINT16) PercentWr) * 100 / 256
    );

  MrcPrintDimmOdtValues (MrcData);  // Print DIMM ODT table

  return mrcSuccess;
}



/**
  This function assign the pointer to the relevant power Coefficient table to the MRC structure
  offset and apply the difference to the global one.

  @param[in] MrcData        - Include all MRC global data.
  @param[in] Formula        -
  @param[in] ParamVector[MaxTxPowerParam] - Parameter vector of Rx/TxPowerOptParam enum holding the actual value in ohms
  @param[in] VectoreSize    - This vector hold the input params to the RSM equations, it should match the equations order
  @param[in] Scale          - optional Scale to get more precision in integer math

  @retval Result in 10x [mW]
**/
INT32
CalcPowerRSM (
  IN MrcParameters *const       MrcData,
  const MRC_RSM_POWER_FORMULA   *Formula,
  UINT16                        ParamVector[],
  UINT8                         VectoreSize,
  UINT8                         Scale
  )
{
  INT32                           Result;
  const MRC_RSM_POWER_FORMULA     *RSMCoeff;
  const MRC_POWER_COEFF           *iCoeff;
  UINT8                           i;
  UINT8                           j;

  // b0+sum(BiXi)+sum(BiiXi^2)+sum(sum(BijXiXj)) ; i!=j
  RSMCoeff = Formula;
  Result = RSMCoeff->Intercept0;
  for (i=0; i < VectoreSize; i++) {
    iCoeff = &RSMCoeff->Coeff[i];
    Result += (ParamVector[i]) * iCoeff->FirstOrder;
    Result += (ParamVector[i] - iCoeff->Intercept) * (ParamVector[i] - iCoeff->Intercept) * iCoeff->SecondOrder;
    for (j = 0; (j < i);  j++) {
      Result += (ParamVector[i] - iCoeff->Intercept) * (ParamVector[j] - RSMCoeff->Coeff[j].Intercept) * iCoeff->Interactions[j];
    }
  }

  // coeff are mult by 1e6
  Result /= (1000000 / Scale);
  return Result;
}



/**
  This function assign the pointer to the relevant power Coefficient table to the MRC structure
  offset and apply the difference to the global one.
  The search algorithm:
    - We match the DIMM technology,
    - Power.Frequency <= Config.Frequency,
    - Power.RttWr <= Config.RttWr.
    - This is assuming that we pre-arrange (low to high) the table to match this algorithm.

  This function implements the following config search algorithm:
    We match the DIMM technology
    Power.Frequency <= Config.Frequency
    Power.RttWr <= Config.RttWr
  This is assuming that we pre-arrange (low to high) the table to match this algo.

  @param[in] MrcData          - Include all MRC global data.
  @param[in] SysPwrConfig     - Parameter defining the desired system configuration (frequency, ddr type, dimm termination).
  @param[in] SysPowerFormula  -
  @param[in] Table            - Pointer to the relevant power equations table
  @param[in] TableSize        -

  @retval None
**/
void
GetPowerTable (
  IN MrcParameters *const      MrcData,
  MRC_POWER_SYS_CONFIG         *SysPwrConfig,
  const MRC_RSM_POWER_FORMULA  **SysPowerFormula,
  const MRC_RSM_POWER_FORMULA  *Table,
  UINT32                       TableSize
  )
{
  UINT32          Index;
  MrcDebug        *Debug;

  const MRC_RSM_POWER_FORMULA *ClosestConfig;

  Debug      = &MrcData->Outputs.Debug;
  // init Mrc struct if not populated yet
  if ((*SysPowerFormula) == NULL) {
    (*SysPowerFormula) = Table;
  }

  ClosestConfig = &Table[0];
  if ((*SysPowerFormula)->Config.Data != SysPwrConfig->Data) {
    for (Index = 0; Index < TableSize; Index++) {
      if (SysPwrConfig->Data == Table[Index].Config.Data) {
        (*SysPowerFormula) = &Table[Index];
        return;
      } else {
        if (Table[Index].Config.Bits.DdrType <= SysPwrConfig->Bits.DdrType) {
          if (Table[Index].Config.Bits.Frequency <= SysPwrConfig->Bits.Frequency) {
            if (Table[Index].Config.Bits.RttWr <= SysPwrConfig->Bits.RttWr) {
              ClosestConfig = &Table[Index];
            }
          }
        }
      }
    }
    (*SysPowerFormula) = ClosestConfig;

    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR,
    //  "Requested Power Config,  Freq - %d DdrType - %d RttWr - %d was not found \n",
    //  SysPwrConfig->Bits.Frequency,
    //  SysPwrConfig->Bits.DdrType,
    //  SysPwrConfig->Bits.RttWr);
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR,
    //  "Power Config was not found, assign the closest one, Freq - %d DdrType - %d RttWr - %d\n",
    //  SysPowerFormula->Config.Bits.Frequency,
    //  SysPowerFormula->Config.Bits.DdrType,
    //  SysPowerFormula->Config.Bits.RttWr);
  }
}

/**
  This function reads the selected comp code.
  In case of comp up/dn we select the value that is closer to saturation (0 or 63).
  Safe assumption is that up/dn codes don't differ by too much.
  So if one of the codes is in the upper range (more than 32), we select MAX of both, otherwise we select MIN of both.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] OptParam - Parameter to read the relevant comp code.
  @param[in] UpDown   - 0 : up only. 1 : down only. 2 : use min/max of both Up and Down codes.

  @retval The selected Comp code
**/
UINT8
GetCompCode (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                OptParam,
  IN     UINT8                UpDown
  )
{
  MrcDebug                            *Debug;
  UINT32                              CurrentComp;
  UINT32                              UpCode;
  UINT32                              DownCode;
  DDRCOMP_CR_DDRCRDATACOMP0_STRUCT    DdrCrDataComp0;
  DDRCOMP_CR_DDRCRDATACOMP1_STRUCT    DdrCrDataComp1;
  DDRCOMP_CR_DDRCRCMDCOMP_STRUCT      DdrCrCmdComp;
  DDRCOMP_CR_DDRCRCTLCOMP_STRUCT      DdrCrCtlComp;
  DDRCOMP_CR_DDRCRCLKCOMP_STRUCT      DdrCrClkComp;

  Debug = &MrcData->Outputs.Debug;

  DdrCrDataComp0.Data = 0;
  CurrentComp = 0;
  UpCode = DownCode = 0;

  if ((OptParam == OptRdOdt) && MrcData->Inputs.EnVttOdt) {
    // in Vtt mode only odt up is valid
    UpDown = 0;
  }

  if ((OptParam == OptWrDS) || (OptParam == OptWrDSUpCoarse) || (OptParam == OptWrDSDnCoarse) || (OptParam == OptSComp) || (OptParam == OptTComp) || (OptParam == OptTxEq)) {
    DdrCrDataComp0.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRDATACOMP0_REG);
  }

  switch (OptParam) {
    case OptWrDS:
    case OptTxEq:
      UpCode   = DdrCrDataComp0.Bits.RcompDrvUp;
      DownCode = DdrCrDataComp0.Bits.RcompDrvDown;
      break;
    case OptWrDSUpCoarse:
      UpCode = DownCode = DdrCrDataComp0.Bits.RcompDrvUp / 4;
      break;
    case OptWrDSDnCoarse:
      UpCode = DownCode = DdrCrDataComp0.Bits.RcompDrvDown / 4;
      break;

    case OptCmdWrDS:
      DdrCrCmdComp.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRCMDCOMP_REG);
      UpCode   = DdrCrCmdComp.Bits.RcompDrvUp;
      DownCode = DdrCrCmdComp.Bits.RcompDrvDown;
      break;

    case OptCmdSComp:
      DdrCrCmdComp.Data = MrcReadCR(MrcData, DDRCOMP_CR_DDRCRCMDCOMP_REG);
      UpCode   = DdrCrCmdComp.Bits.Scomp;
      DownCode = DdrCrCmdComp.Bits.Scomp;
      break;

    case OptCtlDS:
      DdrCrCtlComp.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRCTLCOMP_REG);
      UpCode   = DdrCrCtlComp.Bits.RcompDrvUp;
      DownCode = DdrCrCtlComp.Bits.RcompDrvDown;
      break;

    case OptClkDS:
      DdrCrClkComp.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRCLKCOMP_REG);
      UpCode   = DdrCrClkComp.Bits.RcompDrvUp;
      DownCode = DdrCrClkComp.Bits.RcompDrvDown;
      break;

    case OptRdOdt:
      DdrCrDataComp1.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRDATACOMP1_REG);
      UpCode   = DdrCrDataComp1.Bits.RcompOdtUp;
      DownCode = DdrCrDataComp1.Bits.RcompOdtDown;
      break;

    case OptSComp:
      UpCode = DownCode = DdrCrDataComp0.Bits.SlewRateComp;
      break;

    case OptTComp:
      UpCode = DownCode = DdrCrDataComp0.Bits.TcoComp;
      break;

    default:
      UpCode = 0;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "GetCompCode(): Invalid OptParam %d\n", OptParam);
      break;
  }

  if (UpDown == 2) {
    CurrentComp = (UpCode > 32) ?  MAX (UpCode, DownCode) : MIN (UpCode, DownCode);
  } else if (UpDown == 1) {
    CurrentComp = DownCode;
  } else {
    CurrentComp = UpCode;
  }

  return (UINT8) CurrentComp;
}

/**
  Program COMP Vref offset according to the passed parameter and target values.
  DqOdt segments:
   CTT ODT:  2 resistors (up & dn)
   VDDQ ODT: 2 resistors (up & up)
   VTT ODT:  1 resistor (up to VTT)

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Param        - COMP Vref parameter (see TGlobalCompOffset)
  @param[in] TargetValue  - target COMP value in Ohm
  @param[in] UpdateHost   - update host struct with the new value or not.

  @retval mrcSuccess  - if Param is a valid COMP Vref parameter
**/
MrcStatus
UpdateCompTargetValue (
  MrcParameters *const MrcData,
  UINT8                Param,
  UINT16               TargetValue,
  BOOLEAN              UpdateHost
  )
{
  MrcDebug          *Debug;
  MrcInput          *Inputs;
  UINT8             NumOfSegments[] = { 2, 2, 5, 5, 3 };  // DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
  INT16             CompVref;
  INT16             Min;
  INT16             Max;
  UINT8             CompCode;
  UINT16            ReferenceR;
  UINT8             RComp;
  BOOLEAN           DtHalo;

  Inputs = &MrcData->Inputs;
  Debug  = &MrcData->Outputs.Debug;
  DtHalo = ((Inputs->CpuModel == cmSKL_DT_HALO) || (Inputs->CpuModel == cmKBL_DT_HALO));

  //
  // For SKL ULX/ULT DqDrv is 2 segments, DT/Halo is 3 segments
  //
  if (DtHalo) {
    NumOfSegments[WrDS] = 3;
  }

  //
  // RCOMP0: DQ ODT (read)
  // RCOMP1: DQ  / CLK Ron (drive strength)
  // RCOMP2: CMD / CTL Ron (drive strength)
  //
  switch (Param) {
    case RdOdt:
      if (Inputs->EnVttOdt) {
        NumOfSegments[0] = 1;
      }
      RComp = 0;
      break;

    case WrDS:
    case WrDSClk:
      RComp = 1;
      break;

    case WrDSCmd:
    case WrDSCtl:
      RComp = 2;
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Bad Param : %d\n", Param);
      return mrcFail;
  }

  ReferenceR = DIVIDEROUND (Inputs->RcompResistor[RComp], NumOfSegments[Param]);
  CompVref = DIVIDEROUND (VrefStepSize[Param] * (ReferenceR - TargetValue), 2 * (ReferenceR + TargetValue));

  //
  // Check for field ranges
  //
  if (Param == RdOdt) {
    Min = -16;  // RdOdt is 5 bits 2's complement
    Max = 15;
  } else {
    Min = -8;   // Others are 4 bits 2's complement
    Max = 7;
  }
  CompVref = RANGE (CompVref, Min, Max);

  CompCode = (UINT8) UpdateCompGlobalOffset (MrcData, Param, (UINT32) CompVref, TRUE, UpdateHost);

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "%7s: Target value: %3d ReferenceR: %3d VrefOffset: %3d Current Comp code: %3d\n",
    GlobalCompOffsetStr[Param],
    TargetValue,
    ReferenceR,
    CompVref,
    CompCode
    );

  if ((CompCode == 0) || (CompCode == 63)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING: COMP code is saturated !\n");
  }

  return mrcSuccess;
}

/**
  Program Slew Rate Comp Delay according to the passed parameter and target values.

  @param[in] MrcData            - Include all MRC global data.
  @param[in] Param              - COMP Vref parameter (see TGlobalCompOffset)
  @param[in] BufferStageDelayPS - Slew Rate buffer stage delay in [ps]
  @param[in] UpdateHost         - Update host struct with the new value or not.

  @retval mrcSuccess  - if Param is a valid COMP Vref parameter
**/
MrcStatus
UpdateSlewRateCompTargetValue (
  IN MrcParameters *const MrcData,
  IN UINT8                Param,
  IN UINT8                BufferStageDelayPS,
  IN BOOLEAN              UpdateHost
  )
{
  MrcDebug            *Debug;
  MrcInput            *Inputs;
  MrcOutput           *Outputs;
  UINT8               MinCycleStageDelay;
  UINT8               NumStages;
  UINT8               CompCode;
  UINT8               i;
  SCompType           SlewRateType;
  UINT8               SlewRateCompCells;
  UINT32              SlewRateVref;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &MrcData->Outputs.Debug;

  //
  // Calculate how to program the slew rate targets
  // Buffer Type         DQ  CMD  CTL  CLK
  // Num Stages           3    5    5    3
  // Slew Rate          4.5  3.0  3.0  5.0
  // Derating            .8   .8   .8   .8
  //

  // Get Minimal Cell Delay
  MinCycleStageDelay = 0;
  for (i = 0; i < sizeof (gSlewRateCompParamList); i++) {
    if ((gSlewRateCompParamList[i] == Param) || (gOptSlewRateCompParamList[i] == Param)) {
      MinCycleStageDelay = gMinCycleStageDelay[i];
      break;
    }
  }
  if (MinCycleStageDelay == 0) {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "Bad Param : %d\n", Param);
    return mrcFail;
  }

  // Number of Stages in DLL, rounded to nearest integer
  NumStages = (UINT8) (DIVIDEROUND (Outputs->Qclkps, BufferStageDelayPS));

  SlewRateType = ((NumStages > 16) || (BufferStageDelayPS < MinCycleStageDelay)) ? ScompTypePhase : ScompTypeCycle;
  SlewRateCompCells = (SlewRateType == ScompTypePhase) ? ((NumStages / 2) - 1) : (NumStages - 1);

  if (SlewRateCompCells > MAX_SLEWRATE_CELLS) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, " Warning CellDelay %d exceeds limit %d, clipping\n", SlewRateCompCells, MAX_SLEWRATE_CELLS);
    SlewRateCompCells = MAX_SLEWRATE_CELLS; // Maximum allowed comp cells
  }

  SlewRateVref = SlewRateCompCells | (SlewRateType << 4);
  CompCode = (UINT8) UpdateCompGlobalOffset (MrcData, Param, SlewRateVref, FALSE, UpdateHost);
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "%8s: BufferStageDelayPS: %d, NumStages: %2d, Cells: %2d (%s), VrefOffset: 0x%02X, CompCode: %d\n",
    GlobalCompOffsetStr[Param],
    BufferStageDelayPS,
    NumStages,
    SlewRateCompCells,
    SlewRateType == ScompTypePhase ? "Phase" : "Cycle",
    SlewRateVref,
    CompCode
    );

  if ((CompCode == 0) || (CompCode == 63)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING: COMP code is saturated !\n");
  }

  return mrcSuccess;
}

/**
  This function returns the params setting accordingly to input.

  @param[in out] ParamOff- Parameters result Offsets
  @param[in]     GridMode- Selects the way we sweep the params
  @param[in]     Index   - Linear Index for all params
  @param[in]     YLen    - Determines the Y-Dimension lengths
  @param[in]     XLen    - Determines the X-Dimension lengths


  @retval if point is valid (tested)
**/
BOOLEAN
GetParamsXYZ (
  IN     MrcParameters      *const MrcData,
  IN OUT INT8              *ParamOff,
  IN     const UINT8        OptParamLen,
  IN     const UINT8        GridMode,
  IN     const UINT8        Index,
  IN     const INT8         *Start,
  IN     const UINT8        *ParamOffLen
  )
{
  MrcDebug          *Debug;
  UINT8             XOff;
  INT8              YOff;
  BOOLEAN           SkipPoint = FALSE;

  Debug  = &MrcData->Outputs.Debug;

  if (OptParamLen == 1) {
    switch (GridMode) {
      case FullGrid:
        break;
      case HalfGrid:
        if (Index % 2) {
          SkipPoint = TRUE;
        }
        break;
    }
    ParamOff[0] =  Index + Start[0];

  } else if (OptParamLen == 2) {
    XOff =  Index % ParamOffLen[0];
    YOff =  Index / ParamOffLen[0];
    switch (GridMode) {
      case FullGrid:
        break;
      case ChessOdd:
        if (XOff % 2) {
          if (YOff % 2) {
            SkipPoint = TRUE;
          }
        } else {
          if (YOff % 2 == 0) {
            SkipPoint = TRUE;
          }
        }
        break;
      case ChessEven:
        if (XOff % 2) {
          if (YOff % 2 == 0) {
            SkipPoint = TRUE;
          }
        } else {
          if (YOff % 2) {
            SkipPoint = TRUE;
          }
        }
        break;
      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "unknow GridMode %d\t", GridMode);
    }

    ParamOff[0] = XOff + Start[0];
    ParamOff[1] = YOff + Start[1];
  }

  if (GridMode == CustomSR) {
    if (Index == 0) {
      ParamOff[0] =  -17; // disable SR for fastest SR
    }
  }

  if (GridMode == Reversed1D) {
    ParamOff[0] =  Start[0] + ParamOffLen[0] - 1 - Index; // reversed ordering for param
  }

  return SkipPoint;
}

/**
  Returns the index into RttType array

  @param[in] OptDimmOdt - DimmOdt type

  @retval One of the following values: RttWr RttNom RttPark

**/
DimmOdtType
GetRttType (
  IN const UINT8 OptDimmOdt
  )
{
  switch (OptDimmOdt) {
    case OptDimmOdtWr:
      return RttWr;

    case OptDimmOdtNom:
    case OptDimmOdtNomNT:
      return RttNom;

    case OptDimmOdtPark:
    case OptDimmOdtParkNT:
      return RttPark;

    default:
      break;
  }

  return RttMaxType;
}

/**
  Convert CMD Slew Rate values (in Number of stages) to the vref value.
  I.e. the CmdScompCells (Bits 8:5), CmdScompPC (Bit 9) in DDRCOMP_CR_DDRCRCOMPCTL1_0_0_0_MCHBAR

  @param[in] MrcData      - Include all MRC global data.
  @param[in] NumStages    - The required number of stages

  @retval  - the corresponding CmdSVref value - Bit 4 is the Phase / Cycle value ; Bits 3:0 are the CmdScompCells
**/
UINT8
CmdSlewRateStagesToVref (
  IN MrcParameters *const MrcData,
  IN const UINT8          NumStages
  )
{
  MrcOutput *Outputs;
  UINT8     MinStages;
  UINT8     SlewRateCells;
  SCompType SlewRateType;

  Outputs = &MrcData->Outputs;

  MinStages = (UINT8) (DIVIDEROUND (Outputs->Qclkps, gMinCycleStageDelay[1]));
  SlewRateType = ((NumStages > 16) || (NumStages > MinStages)) ? ScompTypePhase : ScompTypeCycle;
  if (SlewRateType == ScompTypePhase) {
    SlewRateCells = DIVIDEROUND ((UINT8) NumStages, 2) - 1;
  } else {
    SlewRateCells = (UINT8) NumStages - 1;
  }

  return (UINT8) SlewRateCells | ((UINT8) SlewRateType << 4);
}

/**
  Compensate the CMD Slew Rate & Drive Strength values.
  In contrast to DQ training values, CMD is trained using the global Comp register.
  The function recieves the optimal GLOBAL comp value (Vref) and the correspodning Comp code per Channel and
  sets the Comp value to the averaged Comp value, and compensates the Channel Comp code variation using the Comp Offset.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] ChBitMask    - Channel bit mask
  @param[in] CompVref     - An array of the CMD Comp Vref per Channel, or Number of stages in CMD Slew Rate case.
  @param[in] CmdCompCode  - An array of the Corresponding Comp Code per Channel
  @param[in] OptParam     - The Param being compensated, possible inputs: OptCmdWrDS, OptCmdSComp

  @retval - None
**/
void
CmdCompensateOptParam (
  IN OUT MrcParameters *const MrcData,
  IN UINT8                    ChBitMask,
  IN INT32                    CompVref[MAX_CHANNEL],
  IN UINT8                    CmdCompCode[MAX_CHANNEL],
  IN UINT8                    OptParam
  )
{
  MrcDebug    *Debug;
  MrcOutput   *Outputs;
  UINT8       AvgSlewRateVref;
  UINT32      CompCode;
  UINT32      OffsetN;
  UINT32      OffsetS;
  UINT8       ChannelCount;
  UINT8       Channel;
  INT32       AvgCompVref;
  INT32       Offset;
  DDRCMD_CR_DDRCRCMDCOMPOFFSET_STRUCT  DdrCrCmdNCompOffset;
  DDRCMD_CR_DDRCRCMDCOMPOFFSET_STRUCT  DdrCrCmdSCompOffset;

  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;

  ChannelCount = 0;
  AvgCompVref  = 0;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((1 << Channel) & ChBitMask) || !(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    ChannelCount += 1;
    AvgCompVref += CompVref[Channel];
  }
  AvgCompVref = DIVIDEROUND (AvgCompVref, ChannelCount);

  // If only 1 channel there is nothing to compensate between the channels
  if (ChannelCount > 1) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      // Read the Comp offset register for CmdN
      OffsetN = DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_REG +
        ((DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_REG - DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_REG) * Channel);
      DdrCrCmdNCompOffset.Data = MrcReadCR (MrcData, OffsetN);
      // Read the Comp offset register for CmdS
      OffsetS = DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_REG +
        ((DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_REG - DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_REG) * Channel);
      DdrCrCmdSCompOffset.Data = MrcReadCR (MrcData, OffsetS);

      switch (OptParam) {
        case OptCmdWrDS:
          CompCode = UpdateCompGlobalOffset (MrcData, WrDSCmd, (UINT8) (AvgCompVref & 0xF), FALSE, TRUE);
          Offset = (INT32) CmdCompCode[Channel] - (INT32) CompCode;
          Offset = RANGE (Offset, DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MIN, DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MAX);
          // Set CmdN Comp offset
          DdrCrCmdNCompOffset.Bits.RcompDrvUpOffset   = Offset;
          DdrCrCmdNCompOffset.Bits.RcompDrvDownOffset = Offset;
          MrcWriteCR (MrcData, OffsetN, DdrCrCmdNCompOffset.Data);
          // Set CmdS Comp offset
          DdrCrCmdSCompOffset.Bits.RcompDrvUpOffset   = Offset;
          DdrCrCmdSCompOffset.Bits.RcompDrvDownOffset = Offset;
          MrcWriteCR (MrcData, OffsetS, DdrCrCmdSCompOffset.Data);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u: CMD DS OrigVref: %d Code: %u, AvgVref: %d AvgCode: %u Offset: %d\n",
            Channel,
            CompVref[Channel],
            CmdCompCode[Channel],
            AvgCompVref,
            CompCode,
            Offset
            );
          break;
        case OptCmdSComp:
          AvgSlewRateVref = CmdSlewRateStagesToVref (MrcData, (UINT8) (AvgCompVref & 0xF));
          CompCode = UpdateCompGlobalOffset (MrcData, SCompCmd, AvgSlewRateVref, FALSE, TRUE);
          // Cmd DS offset range is limited
          Offset = (INT32) CmdCompCode[Channel] - (INT32) CompCode;
          Offset = RANGE (Offset, DDRCMD_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MIN, DDRCMD_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MAX);
          // Set CmdN Comp offset
          DdrCrCmdNCompOffset.Bits.ScompOffset = Offset;
          MrcWriteCR (MrcData, OffsetN, DdrCrCmdNCompOffset.Data);
          // Set CmdS Comp offset
          DdrCrCmdSCompOffset.Bits.ScompOffset = Offset;
          MrcWriteCR (MrcData, OffsetS, DdrCrCmdSCompOffset.Data);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u: CMD SR OrigStages: %d Code: %u, AvgStages: %d AvgCode: %u Offset: %d\n",
            Channel,
            CompVref[Channel],
            CmdCompCode[Channel],
            AvgCompVref,
            CompCode,
            Offset
            );
          break;
        default:
          break;
      }
    } // for Channel
    // Force Comp cycle
    ForceRcomp (MrcData);

    // Read back the new comp code
    CompCode = GetCompCode (MrcData, OptParam, 0);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "New comp code: %u\n", CompCode);
  } // if we have two channels
}


