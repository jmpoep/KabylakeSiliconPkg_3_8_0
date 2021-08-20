/** @file
  This file include all the MRC common data.

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
#ifndef _MrcCommon_h_
#define _MrcCommon_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcIoControl.h"
#include "McAddress.h"
#include "MrcDdr3.h"
#include "MrcReset.h"
#include "MrcCrosser.h"
#include "MrcDebugPrint.h"



///
/// Convert rank to dimm number
///
#ifndef RANK_TO_DIMM_NUMBER
#define RANK_TO_DIMM_NUMBER(Rank) ((Rank) / 2)
#endif

///
/// Convert DIMM number to a rank bitmask, assuming 2 ranks per DIMM
///
#ifndef DIMM_TO_RANK_MASK
#define DIMM_TO_RANK_MASK(Dimm) (3 << (2 * (Dimm)))
#endif

///
/// Bit operation commands
///
#ifndef MRC_MASK
#define MRC_MASK(offset, width) (((1 << width) - 1) << (offset))
#endif

#ifndef MRC_MASK_NOT
#define MRC_MASK_NOT(offset, width) (~(MRC_MASK (offset, width)))
#endif

#ifndef MRC_CR_UPDATE
#define MRC_CR_UPDATE(Register, Offset, Width, Value) \
        (((Register) & MRC_MASK_NOT (Offset, Width)) | ((Value) << (Offset)))
#endif

#ifndef MRC_CR_DUMP
#define MRC_CR_DUMP(Register, offset, Width)\
        (((Register) & (MRC_MASK(offset, Width))) >> offset)
#endif

#define BER_TARGET              4
#define BER_LOG_TARGET          7             ///< MRC_Log8(BER_TARGET) = 7
#define BER_ERROR_MASK          0xFFFF00FF

#define MRC_ASSERT(cond, DEBUG, ...)   \
  if (!(cond)) { \
    MRC_DEBUG_MSG (DEBUG, MSG_LEVEL_ERROR, ## __VA_ARGS__); \
    MRC_DEADLOOP (); \
  }

///
/// Cache line size
///
#define WDB_CACHE_LINE_SIZE (8)

///
/// CADB Entries
///
#define MRC_NUM_CADB_ENTRIES (8)

///
/// Number of WDB Mux
///
#define MRC_WDB_NUM_MUX_SEEDS (3)

#define OFFSET_CALC_CH(CH0, CH1, CH) (((CH0) + (((CH1) - (CH0)) * (CH))))

///
/// Dimm Mode register selection
///
typedef enum {
  mrMR0 = 0,
  mrMR1,
  mrMR2,
  mrMR3,
  mrMR4,
  mrMR5,
  mrMR6,
  mrRCW,
  mrMR11 = 11
} MrcModeRegister;

typedef enum {
  dDIMM0= 0,
  dDIMM1
} MrcDimmType;

typedef enum {
  cCHANNEL0 = 0,
  cCHANNEL1
} MrcChannelType;

typedef enum {
  rRank0    = 0,
  rRank1,
  rRank2,
  rRank3
} MrcRank;

typedef enum {
  ssOne     = 0,
  ssTwo,
  ssThree,
  ssFour
} TSubSequencesNumber;

///
/// Define ECC mode.
///
typedef enum {
  emNoEcc,
  emEccIoActive,
  emEccLogicActive,
  emBothActive
} TEccModes;

///
/// Raw card list
///
typedef enum {
  rcA,
  rcB,
  rcC,
  rcD,
  rcE,
  rcF,
  rcG,
  rcH,
} TRawCard;

///
/// Reut Addressing Parameters
///
typedef enum {
  MrcReutFieldRank,
  MrcReutFieldBank,
  MrcReutFieldRow,
  MrcReutFieldCol,
  MrcReutFieldMax   ///< This must be the last entry in the enum.
} MrcReutField;

typedef struct {
  UINT16 Start[MrcReutFieldMax];   ///< (4, uint16)    // Rank, Bank, Row, Col
  UINT16 Stop[MrcReutFieldMax];    ///< (4, uint16)    // Rank, Bank, Row, Col
  UINT8  Order[MrcReutFieldMax];   ///< [4, uint8)     // Rank, Bank, Row, Col
  UINT32 IncRate[MrcReutFieldMax]; ///< (4, unit32)    // Rank, Bank, Row, Col
  UINT16 IncVal[MrcReutFieldMax];  ///< (4, unit16)    // Rank, Bank, Row, Col
} MRC_REUTAddress;

typedef struct {
  UINT16 IncRate;                    ///< How quickly the WDB walks through cachelines (uint16)
  UINT32 Start;                      ///< Starting pointer in WDB
  UINT32 Stop;                       ///< Stopping pointer in WDB
  UINT8  DQPat;                      ///< [0:BasicVA, 1:SegmentWDB, 2:CADB, 3:TurnAround,
                                  ///< 4: LMNVa, 5: TurnAroundWR, 6: TurnAroundODT
                                  ///< 7: CADBCol, 8: CADBRow]
} MRC_WDBPattern;

#pragma pack (push, 1)
typedef union {
  struct {
    UINT32 Enable_2x_Refresh                       :  1;  // Bits 0:0
    UINT32 LPDDR_Min_MR4                           :  3;  // Bits 1:3
    UINT32                                         :  27; // Bits 4:30
    UINT32 Lock_Bit                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MrcMailbox2xRefresh;
#pragma pack (pop)

typedef enum {
  BasicVA = 0,                    ///< Use 2 LFSR VicAggressor pattern with rotation of 10 bits
  SegmentWDB,                     ///< Use 2 LFSR VA pattern 10 bit rotation + 3 LFSR VA pattern 6 bit rotation
  CADB,                           ///< Do CADB on command/address bus and LMN VA on DQ (power supply noise)
  TurnAround,
  LMNVa,                          ///< Use (LMN aggressor + LFSR Victim) with rotation of 10 bits
  TurnAroundRW,                   ///< Single SSQ test WR-RD and with RankInc 1
  TurnAroundRW_SG,                ///< Single SSQ test WR-RD and with RankInc 32 same bank
  TurnAroundRW_DG,                ///< Single SSQ test WR-RD and with RankInc 32 and Bank inc 4 (BG)
  TurnAroundWR,                   ///< Run 8 tests, one for each subsequence with RankIncRate = 1/2/2/2/2/2/2/1
  TurnAroundWR_SG,                ///< Run 8 tests, one for each subsequence with RankIncRate = 32/64/64/64/64/64/64/32 and Relevant Bank inc
  TurnAroundWR_DG,                ///< Run 8 tests, one for each subsequence with RankIncRate = 32/64/64/64/64/64/64/32 and Relevant Bank inc
  TurnAroundODT,                  ///< Run 4 tests, one for each subsequence with RankIncRate = 1/2/1/2
  CADBCol,
  CADBRow,
  RdRdTA,                         ///< Run 2 tests, one with Trdrd=4 and one with Trdrd=5
  RdRdTA_All                      ///< Run 8 tests, Covering tRDRD_sr 4,5,6,7 and tRDRD_dr = Min,+1,+2,+3
} MrcDqPat;

typedef enum {
  NSOE = 0,                       ///< Never Stop On Any Error
  NTHSOE,                         ///< Stop on the Nth Any Lane Error
  ABGSOE,                         ///< Stop on All Byte Groups Error
  ALSOE                           ///< Stop on All Lanes Error
} TStopOnError;

typedef enum {
  MrcRegFileRank,                 ///< Used if ChangeMargin is being called within a Rank loop and the Parameters are Rank based.
  MrcRegFileStart,                ///< Used when changing parameters before the test.
  MrcRegFileCurrent,              ///< Used when changing parameters after the test.
  MrcRegFileMax                   ///< This must be the last in the list
} MrcRegFile;

///
/// CADB commands (Bit 0: WE#, Bit 1: CAS#, Bit 2: RAS#, Bit 3(DDR4-only): ACT#)
///
#define MRS_CMD                             0
#define REF_CMD                             1
#define PRE_CMD                             2
#define ACT_CMD                             3
#define WR_CMD                              4
#define RD_CMD                              5
#define ZQ_CMD                              6
#define NOP_CMD                             7
#if (SUPPORT_DDR4 == SUPPORT)
#define DDR4_MRS_CMD                        8
#define DDR4_REF_CMD                        9
#define DDR4_PRE_CMD                        0xA
#define DDR4_WR_CMD                         0xC
#define DDR4_RD_CMD                         0xD
#define DDR4_ZQ_CMD                         0xE
#define DDR4_NOP_CMD                        0xF
#endif // SUPPORT_DDR4

///
/// REUT Init modes
///
#define Idle_Mode                           0
#define REUT_Testing_Mode                   1
#define MRS_Mode                            2
#define NOP_Mode                            3  ///< Normal Operation Mode

///
/// REUT CmdPattern
///
#define PatWrRd                             0
#define PatWr                               1
#define PatRd                               2
#define PatRdWrTA                           3
#define PatWrRdTA                           4
#define PatODTTA                            5
#define DimmTest                            6
#define PatCADBCol                          7
#define PatCADBRow                          8

///
/// REUT Mux Control
///
#define LMNMode                             0
#define BTBUFFER                            1
#define LFSRMode                            2

///
/// REUT Subsequence types
///
#define BRd                                 0
#define BWr                                 1
#define BRdWr                               2
#define BWrRd                               3
#define ORd                                 4
#define OWr                                 5

///
/// WDB Patterns
///
#define BASIC_VA_PATTERN_SPRED_8  0x01010101

///
/// DQ time centering param: read or write
///
///
/// Margin params
///

/*
 1D Margin Types:
  RcvEn:  Shifts just RcvEn.  Only side effect is it may eat into read dq-dqs for first bit of burst
  RdT:    Shifts read DQS timing, changing where DQ is sampled
  WrT:    Shifts write DQ timing, margining DQ-DQS timing
  WrDqsT: Shifts write DQS timing, margining both DQ-DQS and DQS-CLK timing
  RdV:    Shifts read Vref voltage for DQ only
  WrV:    Shifts write Vref voltage for DQ only
  WrLevel: Shifts write DQ and DQS timing, margining only DQS-CLK timing
  WrTBit:  Shifts write DQ per bit timing.
  RdTBit:  Shifts read DQ per bit timing.
  RdVBit:  Shifts read DQ per bit voltage.

 2D Margin Types (Voltage, Time)
  RdFan2:  Margins both RdV and RdT at { (off, -2/3*off),  (off, 2/3*off) }
  WrFan2:  Margins both WrV and WrT at { (off, -2/3*off),  (off, 2/3*off) }
  RdFan3:  argins both RdV and RdT at { (off, -2/3*off),  (5/4*off, 0),  (off, 2/3*off)  }
  WrFan3:  Margins both WrV and WrT at { (off, -2/3*off),  (5/4*off, 0),  (off, 2/3*off)  }

  param = {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
          8:WrTBit, 9:RdTBit, 10:RdVBit,
          16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
*/

 typedef enum {
  RcvEna = 0,
  RdT,
  WrT,
  WrDqsT,
  RdV,
  WrV,
  WrLevel,
  WrTBox,
  WrTBit,
  RdTBit,
  RdVBit,  ///< 10
  RcvEnaX,
  CmdT,
  CmdV,
  RdFan2 = 16,
  WrFan2 = 17,
  RdFan3 = 32,
  WrFan3 = 33,
  MarginTypeMax
} MRC_MarginTypes;

typedef enum {
  OptWrDS = 0,
  OptSComp,
  OptTComp,
  OptTxEq,
  OptRdOdt,
  OptRxEq,
  OptRxBias,
  OptRxCb,
  OptDimmOdt,
  OptDimmOdtWr,
  OptDimmOdtNom,
  OptDimmOdtNomNT,
  OptDimmOdtPark,
  OptDimmOdtParkNT,
  OptDimmOdtParkSlot1,
  OptDimmOdtComb,
  OptDimmOdtComb_1R1R,
  OptDimmRon,
  OptWrDSUp,
  OptWrDSDn,
  OptWrDSUpCoarse,
  OptWrDSDnCoarse,
  OptRdOdtUp,
  OptRdOdtDn,
  OptCtlDS,
  OptClkDS,
  OptRxBiasCb, //param0=RxBias param1=RxCb
  OptTxEqWrDS, //param0=TxEq param1=WrDS
  OptCmdSComp,
  OptCtlSComp,
  OptClkSComp,
  OptCmdWrDS,
  OptCmdTxEq,
  OptDefault
} TOptParamOffset;

typedef enum {
  drrd2rd = 0,
  ddrd2rd,
  drwr2wr,
  ddwr2wr,
  drrd2wr,
  ddrd2wr,
  drwr2rd,
  ddwr2rd,
  rdodtd,
  wrodtd,
  mcodts,
  mcodtd,
  rtl,
  srrd2rd,
  srwr2rd_sg,
  srwr2rd_dg,
  srrd2wr_sg,
  srrd2wr_dg
} TOptParamTAT;

///
/// Self refresh idle timer value
///
#define SELF_REFRESH_IDLE_COUNT (0x200)

#define RXF_SELECT_RC_100  (6)
#define RXF_SELECT_RC_133  (4)
#define RXF_SELECT_MIN     (0)
#define RXF_SELECT_MAX     (4)
#define RXF_SELECT_MAX_ULT (2)

#ifdef MRC_DEBUG_PRINT
extern const char CcdString[];
#endif

///
/// MRC common functions
///

/**
  Verify that the indicated socket is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.

  @retval Success if present and enabled, otherwise SocketNotSupported.
**/
extern
MrcStatus
IsSocketPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket
  );

/**
  Verify that the indicated controller is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.

  @retval Success if present and enabled, otherwise ControllerNotSupported.
**/
extern
MrcStatus
IsControllerPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller
  );

/**
  Verify that the indicated channel is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.
  @param[in] Channel    - Zero based memory channel number.

  @retval Success if present and enabled, otherwise ChannelNotSupported.
**/
extern
MrcStatus
IsChannelPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller,
  const UINT32                Channel
  );

/**
  Verify that the indicated DIMM is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.
  @param[in] Channel    - Zero based memory channel number.
  @param[in] Dimm       - Zero based memory DIMM number.

  @retval Success if present and enabled, otherwise DimmNotSupported.
**/
extern
MrcStatus
IsDimmPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller,
  const UINT32                Channel,
  const UINT32                Dimm
  );

/**
  Verify that the indicated rank is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.
  @param[in] Channel    - Zero based memory channel number.
  @param[in] Dimm       - Zero based memory DIMM number.
  @param[in] Rank       - Zero based memory rank number in the DIMM.

  @retval Success if present and enabled, otherwise RankNotSupported.
**/
extern
MrcStatus
IsRankPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller,
  const UINT32                Channel,
  const UINT32                Dimm,
  const UINT32                Rank
  );


/**
  Set ideal Dimm Write Vref for DDR4 assuming CPU Ron and Dimm termination.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Channel     - Channel to setup
  @param[in]      RankBitMask - Rank bit mask to setup
  @param[in]      Byte        - Byte to setup (for PDA mode only)
  @param[in]      CpuRon      - CPU Ron value in Ohm
  @param[in]      OdtWr       - Write DIMM Odt value in Ohm
  @param[in]      DimmOdt     - Equ. DIMM Odt value in Ohm
  @retval none
**/
void
MrcSetIdealTxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  UINT8                       Channel,
  UINT8                       RankBitMask,
  UINT8                       Byte,
  UINT32                      CpuRon,
  UINT32                      OdtWr,
  UINT32                      DimmOdt
  );

/**
  Set default CPU Read Vref for DDR4 assuming CPU uses Vddq termination.
  Use default CPU ODT and DIMM Ron values.

  @param[in, out] MrcData      - Include all MRC global data.
  @param[in]      GetFromTable - Get the DIMM ODT parameters from the initial table.
  @param[in]      PrintMsg     - Enable debug prints

  @retval none
**/
extern
void
MrcSetDefaultRxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  IN     BOOLEAN         GetFromTable,
  IN     BOOLEAN         PrintMsg
  );

/**
  Return the rank mask in channel if rank exist exist.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] Channel - Channel to work on.
  @param[in] Rank    - Rank to check.

  @retval Bit mask of Rank requested if the Rank exists in the system.
**/
extern
UINT8
MrcRankInChannelExist (
  IN MrcParameters *const MrcData,
  IN const UINT8          Rank,
  IN const UINT8          Channel
  );

/**
  Return the number of ranks in specific dimm.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] Channel - Channel to work on.
  @param[in] Dimm    - Dimm in channel to return.

  @retval The number of ranks in the dimm.
**/
extern
UINT8
MrcGetRankInDimm (
  IN MrcParameters *const MrcData,
  IN const UINT8          Dimm,
  IN const UINT8          Channel
  );

/**
  Returns whether Channel is or is not present.

  @param[in] Outputs - Pointer to MRC global Output data.
  @param[in] Channel - Channel to test.

  @retval TRUE  - if there is at least one enabled DIMM in the channel.
  @retval FALSE - if there are no enabled DIMMs in the channel.
**/
extern
BOOLEAN
MrcChannelExist (
  IN const MrcOutput *const Outputs,
  IN const UINT8            Channel
  );

/**
  This function disable channel parameters.
  After this function the MRC don't use with the channel.

  @param[in] MrcData           - Include all MRC global data.
  @param[in] ChannelToDisable  - Channel to disable.
  @param[in] SkipDimmCapacity  - Switch to skip setting the DimmCapacity to 0 for the dimms in the channel disabled.

  @retval Nothing
**/
extern
void
MrcChannelDisable (
  IN MrcParameters *const MrcData,
  IN const UINT8          ChannelToDisable,
  IN const UINT8          SkipDimmCapacity
  );

/**
  Convert the given frequency and reference clock to a clock ratio.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Frequency - The memory frequency.
  @param[in] RefClk    - The memory reference clock.
  @param[in] BClk      - The base system reference clock.

  @retval Returns the memory clock ratio.
**/
extern
MrcClockRatio
MrcFrequencyToRatio (
  IN MrcParameters *const  MrcData,
  IN const MrcFrequency    Frequency,
  IN const MrcRefClkSelect RefClk,
  IN const MrcBClkRef      BClk
  );

/**
  Convert the given ratio and reference clocks to a memory frequency.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] Ratio   - The memory ratio.
  @param[in] RefClk  - The memory reference clock.
  @param[in] BClk    - The base system reference clock.

  @retval Returns the memory frequency.
**/
extern
MrcFrequency
MrcRatioToFrequency (
  IN MrcParameters *const  MrcData,
  IN const MrcClockRatio   Ratio,
  IN const MrcRefClkSelect RefClk,
  IN const MrcBClkRef      BClk
  );

/**
  Convert the given ratio and reference clocks to a memory clock.

  @param[in] Ratio  - The memory ratio.
  @param[in] RefClk - The memory reference clock.
  @param[in] BClk   - The base system reference clock.

  @retval Returns the memory clock in femtoseconds.
**/
extern
UINT32
MrcRatioToClock (
  IN MrcParameters *const  MrcData,
  IN const MrcClockRatio   Ratio,
  IN const MrcRefClkSelect RefClk,
  IN const MrcBClkRef      BClk
);

/**
  This function return the DIMM number according to the rank number.

  @param[in] Rank - The requested rank.

  @retval The DIMM number.
**/
extern
UINT8
MrcGetDimmFromRank (
  IN const UINT8 Rank
  );

/**
  This function sets the memory frequency.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess on success, mrcFrequencyError on error.
**/
extern
MrcStatus
McFrequencySet (
  IN MrcParameters * const MrcData
  );

/**
  Returns the extrapolated margin to a fixed # of errors (logT)
  vrefpass is 10x the first passing margin (with no errors) (10x used for int math)
  Errors at vrefpass/10+1 = log1
  Errors at vrefpass/10+2 = logT

  @param[in]      vrefpass      - 10x the first pass margin (w/no errors) (10x used for int match)
  @param[in]      errLog_1      - Errors at vrefpass/10+1
  @param[in]      errLog_2      - Errors at vrefpass/10+2
  @param[in]      errLog_Target - Error target determines extrapolation vs interpolation
  @param[in, out] *berStats     - Used to track interpolation vs extrapolation or if the slope is non-monotonic.
                                  NOTE: target would be Interpolation only

  @retval Interpolated/Extrapolated vref with the scale increased by 10.
**/
extern
UINT32
interpolateVref (
  IN     UINT32  vrefpass,
  IN     UINT32  errLog_1,
  IN     UINT32  errLog_2,
  IN     UINT32  errLog_Target,
  IN OUT UINT32  *berStats
  );

/**
  This function swaps a subfield, within a 32 bit integer value with the specified value.

  @param[in] CurrentValue - 32 bit input value.
  @param[in] NewValue     - 32 bit New value.
  @param[in] Start        - Subfield start bit.
  @param[in] Length       - Subfield length in bits/

  @retval The updated 32 bit value.
**/
extern
UINT32
MrcBitSwap (
  IN UINT32    CurrentValue,
  IN const UINT32 NewValue,
  IN const UINT8  Start,
  IN const UINT8  Length
  );

/**
  This function returns the maximim Rx margin for a given Channel, Rank(s), and byte.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Param     - Test parameter.
  @param[in] Channel   - Channel to calculate max Rx margin.
  @param[in] RankRx    - Rank index.  0xFF causes all ranks to be considered.
  @param[in] Byte      - Byte to check.
  @param[in] Sign      - Sign of the margins (0 - negative/min, 1 - positive/max).
  @param[in] MaxMargin - Current max margin value.

  @retval The max Rx margin, either MaxMargin or value from stored margins.
**/
extern
UINT8
MrcCalcMaxRxMargin (
  IN MrcParameters  *const MrcData,
  IN UINT8                 Param,
  IN const UINT8           Channel,
  IN const UINT8           RankRx,
  IN const UINT8           Byte,
  IN const UINT8           Sign,
  IN UINT16                MaxMargin
  );

/**
  This function returns the maximim Vref margin for a given Channel if WrV.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Channel   - Channel to calculate max Tx margin.
  @param[in] RankTx    - Rank Mask for DDR4.
  @param[in] Byte      - Zero based byte number.
  @param[in] Param     - Parameter of Vref to use
  @param[in] Sign      - Sign of the margins (0 - negative/min, 1 - positive/max).
  @param[in] MaxMargin - Current max margin value.
  @param[in] Pda       - Use PDA or not.

  @retval The max Vref margin, either MaxMargin or value from stored margins.
**/
extern
UINT8
MrcCalcMaxVrefMargin (
  IN MrcParameters  *const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           RankTx,
  IN const UINT8           Byte,
  IN const UINT8           Param,
  IN const UINT8           Sign,
  IN UINT8                 MaxMargin,
  IN BOOLEAN               Pda
  );

/**
  This function determines if a bit lane[0-7] has seen a pass and a fail in each byte for all channels populated.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] chBitmask - Bit mask of channels to consider.
  @param[in] OnePass   - Array of Bit masks marking DQ lanes has had a passing value.
  @param[in] OneFail   - Array of Bit masks marking DQ lanes has had a failing value.

  @retval The AND result of each Channel/byte for OnePass and OneFail.
**/
extern
UINT8
MrcAndBytes (
  IN MrcParameters *const MrcData,
  IN const UINT8          chBitmask,
  IN UINT8                OnePass[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN UINT8                OneFail[MAX_CHANNEL][MAX_SDRAM_IN_DIMM]
  );

/**
  This function Finds the margin for all channels/all bits. The margin sweep is a parameterized
  Assume REUT test has already been fully setup to run
  This will unscale the results such that future tests start at the correct point
  Uses ChangeMargin function to handle a variety cases (Timing, Voltage, Fan, etc.)

  @param[in]     MrcData    - Include all MRC global data.
  @param[in]     chBitMask  - Channel BIT mask for Channel(s) to work on
  @param[in]     Rank       - Rank to work on
  @param[in,out] marginbit  - used as the return data ( real margin measurement, no 10x)
                              marginbit[ch,byte,bit,sign] = abs(Margin)
                              Note: If param == RdTBit/RdVBit/WrVBit, marginbit is also the starting point
  @param[in,out] marginbyte - provides the starting point on a per byte basis (still 10x)
  @param[in]     param      - defines the margin type
  @param[in]     mode       - allows for different types of modes for margining
                              {Bit0: PhLock (keep all bytes within in ch in phase),
                               Bit1: Ch2Ch Data out of phase (LFSR seed)
                               Bits 15:2: Reserved}
  @param[in]     MaxMargin  - Default Maximum margin
  @param[in]     MsgPrint   - Enables printing of debug messages.

  @retval mrcSuccess if successful, otherwise it returns an error status.
**/
extern
MrcStatus
MrcGetMarginBit (
  IN     MrcParameters *const MrcData,
  IN     UINT8                chBitMask,
  IN     UINT8                Rank,
  IN OUT UINT32               marginbit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES],
  IN OUT UINT32               marginbyte[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8                param,
  IN     UINT16               mode,
  IN     UINT8                MaxMargin,
  IN     BOOLEAN              MsgPrint
  );

/**
  Assume REUT test has already been fully setup to run
  Finds the margin for all channels/all bytes
  The margin sweep is parameterized
  Uses ChangeMargin function to handle a variety of cases (Timing, Voltage, Fan, etc.)
  mode allows for different types of modes for margining:
    mode is {Bit0: PhLock (keep all bytes within in ch in phase),
             Bit1: Ch2Ch Data out of phase (LFSR seed), Bit 15:2: Reserved}
  marginByte is used as the starting point for the search (10x the actual margin)
  marginch returns the results (10x the actual margin)
  Interior: Search inside marginch limits, enabling multiple calls with different setups
  To reduce repeatibility noise, the returned margins is actually a BER extrapolation

  @param[in]     MrcData    - The global MrcData
  @param[in,out] marginByte - Data structure with the latest margin results
  @param[in]     chBitmask  - Bit mask of present channels
  @param[in]     RankIn     - Rank to change margins for
  @param[in]     RankRx     - Ranks for Rx margin
  @param[in]     param      - parameter to get margins for
  @param[in]     mode       - allows for different types of modes for margining:
  @param[in]     BMap       - Byte mapping to configure error counter control register
  @param[in]     EnBER      - Enable BER extrapolation calculations
  @param[in]     MaxMargin  - Max Margin allowed for the parameter
  @param[in]     Interior   - Search inside marginch limits, enabling multiple calls with different setups
  @param[in,out] BERStats   - Bit Error Rate Statistics.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
extern
MrcStatus
MrcGetBERMarginByte (
  IN     MrcParameters * const MrcData,
  IN OUT UINT32          marginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8           chBitmask,
  IN     UINT8           RankIn,
  IN     UINT8           RankRx,
  IN     UINT8           param,
  IN     UINT16          mode,
  IN     UINT8           *BMap,
  IN     UINT8           EnBER,
  IN     UINT8           MaxMargin,
  IN     UINT8           Interior,
  IN OUT UINT32          *BERStats
  );

/**
  Assume REUT test has already been fully setup to run
  Finds the margin for all channels/all bytes
  The margin sweep is parameterized
  Uses ChangeMargin function to handle a variety of cases (Timing, Voltage, Fan, etc.)
  mode allows for different types of modes for margining:
  mode is {Bit0: PhLock (keep all bytes within in ch in phase),
  Bit1: Ch2Ch Data out of phase (LFSR seed), Bit 15:2: Reserved}
  marginCh is used as the starting point for the search (10x the actual margin)
  marginch returns the results (10x the actual margin)
  Interior: Search inside marginch limits, enabling multiple calls with different setups
  To reduce repeatibility noise, the returned margins is actually a BER extrapolation

  @param[in]     MrcData   - The global MrcData
  @param[in,out] marginCh  - Data structure with the latest margin results
  @param[in]     chBitmask - Bit mask of present channels
  @param[in]     RankRx    - Ranks for Rx margin
  @param[in]     RankIn    - Rank to change margins for
  @param[in]     param     - parameter to get margins for
  @param[in]     mode      - allows for different types of modes for margining:
  @param[in]     EnBER     - Enable BER extrapolation calculations
  @param[in]     MaxMargin - Max Margin allowed for the parameter
  @param[in]     Interior  - Search inside marginch limits, enabling multiple calls with different setups
  @param[in,out] BERStats  - Bit Error Rate Statistics.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
extern
MrcStatus
MrcGetBERMarginCh (
  IN     MrcParameters   *MrcData,
  IN     UINT32          marginCh[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN OUT UINT8           chBitmask,
  IN     UINT8           RankRx,
  IN     UINT8           RankIn,
  IN     UINT8           param,
  IN     UINT16          mode,
  IN     UINT8           EnBER,
  IN     UINT8           MaxMargin,
  IN     UINT8           Interior,
  IN OUT UINT32          *BERStats
  );

/**
  This function shifts a 32 bit int either positive or negative

  @param[in] Value       - Input value to be shifted
  @param[in] ShiftAmount - Number of bits places to be shifted.

  @retval 0 if ShiftAmount exceeds +/- 31.  Otherwise the updated 32 bit value.
**/
extern
UINT32
MrcBitShift (
  IN const UINT32 Value,
  IN const INT8  ShiftAmount
  );

/**
  This function Sign extends OldMSB to NewMSB Bits (Eg: Bit 6 to Bit 7)

  @param[in] CurrentValue - Input value to be shifted
  @param[in] OldMSB       - The original most significant Bit
  @param[in] NewMSB       - The new most significant bit.

  @retval The updated 8 bit value.
**/
extern
UINT8
MrcSE (
  IN UINT8     CurrentValue,
  IN const UINT8  OldMSB,
  IN const UINT8  NewMSB
  );

/**
  This function calculates the Log base 2 of the value to a maximum of Bits

  @param[in] Value - Input value

  @retval Returns the log base 2 of input value
**/
extern
UINT8
MrcLog2 (
  IN const UINT32 Value
  );

/**
  This function calculates the power of integer numbers.

  @param[in] Value - Input value.
  @param[in] Power -

  @retval Returns power percentage
**/
UINT32
MrcPercentPower (
  IN const UINT32 Value,
  IN  UINT32 Power
  );


/**
  This function search for item in a list.

  @param[in] Param - Param to search for.
  @param[in] ParamList - List of Params.
  @param[in] ParamLen - Params length.

  @retval Returns index + 1 or 0 if Param not found.
**/

UINT8
MrcSearchList(
  IN UINT8 Param,
  IN const UINT8 *ParamList,
  IN const UINT8  ParamLen
  );
/**
  ***** Has Buffer Overflow for 68-71, 544-575, 4352-4607, ... ****
  This function calculates the Log base 8 of the Input parameter using integers

  @param[in] Value - Input value

  @retval Returns 10x the log base 8 of input Value
**/
extern
UINT32
MrcLog8 (
  IN UINT32 Value
  );

/**
  This function Sorts Arr from largest to smallest

  @param[in,out] Arr     - Array to be sorted
  @param[in]     Channel - Channel to sort.
  @param[in]     lenArr  - Length of the array

  @retval Nothing
**/
extern
void
MrcBsortPerChannel (
  IN OUT UINT32   Arr[MAX_CHANNEL][4],
  IN     const UINT8 Channel,
  IN     const UINT8 lenArr
  );

/**
  This function Sorts Arr from largest to smallest

  @param[in,out] Arr    - Array to be sort
  @param[in]     lenArr - Lenght of the array

  @retval Nothing
**/
extern
void
MrcBsort (
  IN OUT UINT32 *const Arr,
  IN     const UINT8   lenArr
  );

/**
  This function calculates the Natural Log of the Input parameter using integers

  @param[in] Input - 100 times a number to get the Natural log from.
                      Max Input Number is 40,000 (without 100x)

  @retval 100 times the actual result. Accurate within +/- 2
**/
extern
UINT32
MrcNaturalLog (
  IN UINT32 Input
  );

/**
  This function calculates the number of bits set to 1 in a 32-bit value.

  @param[in] Input - The value to work on.

  @retval The number of bits set to 1 in Input.
**/
extern
UINT8
MrcCountBitsEqOne (
  IN UINT32 Input
  );

/**
  This function calculates e to the power of of the Input parameter using integers.

  @param[in] Input - 100 times a number to elevate e to.

  @retval 100 times the actual result. Accurate within +/- 2.
**/
extern
UINT32
Mrceexp (
  IN UINT32 Input
  );

/**
  This function writes a 32 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - Value to write.

  @retval The register value.
**/
extern
UINT32
MrcWriteCrMulticast (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const UINT32  Value
  );

/**
  This function writes a 64 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - Value to write.

  @retval The register value.
**/
extern
UINT64
MrcWriteCR64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const UINT64  Value
  );

/**
  This function writes a 32 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - Value to write.

  @retval The register value.
**/
extern
UINT32
MrcWriteCR (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const UINT32  Value
  );

/**
  This function writes a 8 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - The value to write.

  @retval The register value.
**/
extern
UINT8
MrcWriteCR8 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const UINT8   Value
  );

/**
  This function reads a 64 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.

  @retval Value read from the register.
**/
extern
UINT64
MrcReadCR64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset
  );

/**
  This function reads a 32 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.

  @retval Value read from the register
**/
extern
UINT32
MrcReadCR (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset
  );

/**
  This function blocks the CPU for the duration specified in HPET Delay time.

  @param[in] MrcData   - Include all MRC global data.
  @param[in] DelayHPET - time to wait in 41.666667ns

  @retval Nothing
**/
extern
void
MrcWait (
  IN MrcParameters *const MrcData,
  IN UINT32               DelayHPET
  );

/**
  This function forces an RCOMP.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
extern
MrcStatus
ForceRcomp (
  IN MrcParameters * const MrcData
  );

/**
  This function sets the self refresh idle timer and enables it.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing
**/
extern
void
EnterSR (
  IN MrcParameters * const MrcData
  );

/**
  This function sets the self refresh idle timer and disables it.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
extern
MrcStatus
ExitSR(
  IN MrcParameters * const MrcData
  );

/**
  This function programs the WDB.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing
**/
extern
void
SetupWDB(
  IN MrcParameters * const MrcData
  );

/*
  This function will program all present channels with the seeds passed in.

  @param[in] MrcData   - Global MRC data structure
  @param[in] Seeds     - Array of seeds programmed into PAT_WDB_CL_MUX_PB_RD/WR
  @param[in] Start     - Zero based starting seed location
  @param[in] SeedCount - Number of seeds in the array

  @retval - Nothing
*/
extern
void
MrcProgramLFSR (
  IN MrcParameters *const MrcData,
  IN const UINT32  *const Seeds,
  IN const UINT8          Start,
  IN const UINT8          SeedCount
  );

/**
  This function Write 1 cacheline worth of data to the WDB

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Patterns - Array of bytes.  Each bytes represents 8 chunks of the cachelines for 1 lane.
                         Each entry in Patterns represents a different cacheline for a different lane.
  @param[in] PMask    - Array of len Spread uint8.  Maps the patterns to the actual DQ lanes.
                         DQ[0] = Patterns[PMask[0]], ... DQ[Spread-1] = Patterns[PMask[Spread-1]]
                         DQ[Spread] = DQ[0], ... DQ[2*Spread-1] = DQ[Spread-1]
  @param[in] Start    - Starting entry in the WDB.

  @retval Nothing
**/
extern
void
WriteWDBFixedPattern (
  IN MrcParameters *const MrcData,
  IN UINT8 *const            Patterns,
  IN UINT8 *const            PMask,
  IN const UINT8          Spread,
  IN const UINT16         Start
  );

/**
  This rotine performs the following steps:
    Step 0: Iterate through all VicRots
    Step 1: Create a compressed vector for a given 32 byte cacheline
            Each byte has a value of LFSR0=AA/LFSR1=CC/LFSR2=F0
    Step 2: Expand compressed vector into chunks and 32 bit segments

  @param[in] MrcData - Include all MRC global data.
  @param[in] vmask   - 32 bit victim mask.  1 indicates this bit should use LFSR0
  @param[in] amask   - 32 bit aggressor mask. 0/1 indicates this bit should use LFSR1/2
  @param[in] VicRot  - Number of times to circular rotate vmask/amask
  @param[in] Start   - Starting entry in the WDB

  @retval Nothing
**/
extern
void
WriteWDBVAPattern (
  IN MrcParameters *const MrcData,
  IN UINT32               amask,
  IN UINT32               vmask,
  IN const UINT8          VicRot,
  IN const UINT16         Start
  );

/**
  Write VA pattern in CADB
  Use basic VA pattern for CADB with 2 LFSRs. Rotation is manual
  Bit Order is  [CKE[3:0], ODT[3:0], CMD[2:0], CS[3:0], BA[2:0], MA[15:0]]
  [59:56]  [51:48]  [42:40] [35:32]  [26:24]  [15:0]

  NOTE: CKE, ODT and CS are not used in functional mode and are ignored

  @param[in] MrcData   - Include all MRC global data.
  @param[in] Channel   - Channel to setup.
  @param[in] VicSpread - Separation of the Victim Bit.
  @param[in] VicBit    - The Bit to be the Victim.
  @param[in] LMNEn     - To enable LMN counter

  @retval Nothing
**/
extern
void
SetupCADB (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          VicSpread,
  IN const UINT8          VicBit,
  IN const UINT8          LMNEn
  );

/*
  This function handles writing to the REUT Addressing sequence for IO Tests.
  To not write a certain parameter, pass a NULL pointer to the function.

  @param[in] MrcData       - MRC global data structure.
  @param[in] Channel       - Specifies the channel to program.
  @param[in] StartAddr     - Start value for Rank/Bank/Row/Col.
  @param[in] StopAddr      - Stop value for Rank/Bank/Row/Col.
  @param[in] FieldOrder    - Relative order for carry propagates of Rank/Bank/Row/Col.
  @param[in] IncRate       - The number of writes to Rank/Bank/Row/Col before updating the address.
                              Note: The function will handle linear vs exponential and a value of 0 specifies a rate of 1.
  @param[in] IncValue      - The amount to increase Rank/Bank/Row/Col address.
  @param[in] WrapTriggerEn - Enables wrap trigger for Rank/Bank/Row/Col to enable stopping on subsequence and sequence.
  @param[in] WrapCarryEn   - Enables carry propagation on wrap to the next higest order field
  @param[in] AddrInvertEn  - Enables inverting the Rank/Bank/Row/Col addresses based on AddrInvertRate.
  @param[in] AddrIvertRate - Exponential rate of address inversion.  Only updated if AddrInvertEn != NULL.
  @param[in] EnableDebug   - Enables/Disables debug printing.

  @retval Nothing
*/
extern
void
MrcProgramSequenceAddress (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT16         StartAddr[MrcReutFieldMax],
  IN const UINT16         StopAddr[MrcReutFieldMax],
  IN const UINT8          FieldOrder[MrcReutFieldMax],
  IN const UINT32         IncRate[MrcReutFieldMax],
  IN const UINT16         IncValue[MrcReutFieldMax],
  IN const UINT8          WrapTriggerEn[MrcReutFieldMax],
  IN const UINT8          WrapCarryEn[MrcReutFieldMax],
  IN const UINT8          AddrInvertEn[MrcReutFieldMax],
  IN const UINT8          AddrInvertRate,
  IN const BOOLEAN        EnableDebug
  );

/**
  Programs all the key registers to define a CPCG test

  @param[in] MrcData     - Include all MRC global data.
  @param[in] WDBPattern  - Structure that stores start, Stop, IncRate and Dqpat for pattern.
  @param[in] ChbitMask   - Channel Bit mak for which test should be setup for.
  @param[in] CmdPat      - [0: PatWrRd (Standard Write/Read Loopback),
                            1: PatWr (Write Only),
                            2: PatRd (Read Only),
                            3: PatRdWrTA (ReadWrite Turnarounds),
                            4: PatWrRdTA (WriteRead Turnarounds),
                            5: PatODTTA (ODT Turnaround]
  @param[in] NumCL       - Number of Cache lines
  @param[in] LC          - Loop Count exponent
  @param[in] REUTAddress - Structure that stores start, stop and increment details for address
  @param[in] SOE         - [0: Never Stop, 1: Stop on Any Lane, 2: Stop on All Byte, 3: Stop on All Lane]
  @param[in] WDBPattern  - Structure that stores start, Stop, IncRate and Dqpat for pattern.
  @param[in] EnCADB      - Enable test to write random deselect packages on bus to create xtalk/isi
  @param[in] EnCKE       - Enable CKE power down by adding 64
  @param[in] SubSeqWait  - # of Dclks to stall at the end of a sub-sequence

  @retval Nothing
**/
extern
void
SetupIOTest (
  IN MrcParameters *const         MrcData,
  IN const UINT8                  ChbitMask,
  IN const UINT8                  CmdPat,
  IN const UINT16                 NumCL,
  IN const UINT8                  LC,
  IN const MRC_REUTAddress *const REUTAddress,
  IN const UINT8                  SOE,
  IN MRC_WDBPattern *const        WDBPattern,
  IN const UINT8                  EnCADB,
  IN const UINT8                  EnCKE,
  IN UINT16                       SubSeqWait
  );

/**
  This function sets up a test with CADB for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
extern
void
SetupIOTestCADB (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  );

/**
  This function sets up a basic victim-aggressor test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.
  @param[in]     Spread    - Stopping point of the pattern.

  @retval Nothing
**/
extern
void
SetupIOTestBasicVA (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE,
  IN     const UINT32         Spread
  );

/**
  This function sets up a DQ test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
extern
void
SetupIOTestDQ (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  );

/**
  This function sets up a test with CADB for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
extern
void
SetupIOTestC2C (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  );

/**
  This function sets up a MPR test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
extern
void
SetupIOTestMPR (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  );

/**
  Runs one or more REUT tests (based on TestType)

  @param[in] MrcData     - Include all MRC global data.
  @param[in] ChbitMask   - Channel Bit mask for which test should be setup for.
  @param[in] DQPat       - [0: BasicVA
                            1: SegmentWDB
                            2: CADB
                            3: TurnAround
                            4: LMNVa
                            5: TurnAroundWR
                            6: TurnAroundODT
                            7: RdRdTA]
  @param[in] SeqLCs      - An array of one or more loopcounts.
  @param[in] ClearErrors - Decision to clear or not errors.
  @param[in] Mode        - Allows for different types of modes for margining
                           {Bit0: PhLock (keep all bytes within in ch in phase),
                            Bit1: Ch2Ch Data out of phase (LFSR seed)
                            Bits 15:2: Reserved}

  @retval Returns ch errors
**/
extern
UINT8
RunIOTest (
  IN MrcParameters *const MrcData,
  IN const UINT8          ChbitMask,
  IN const UINT8          DQPat,
  IN const UINT8 *const      SeqLCs,
  IN const UINT8          ClearErrors,
  IN const UINT16         Mode
  );

/**
  Programs REUT to run on the selected physical ranks.

  @param[in] MrcData           - Pointer to MRC global data.
  @param[in] ch                - Channel to enable.
  @param[in] RankBitMask       - Bit mask of ranks to enable.
  @param[in] RankFeatureEnable - RankFeatureEnable is a bit mask that can enable CKE, Refresh or ZQ
                                 RankFeatureEnable[0] enables Refresh on all non-selected ranks
                                 RankFeatureEnable[1] enables Refresh on all ranks
                                 RankFeatureEnable[2] enables ZQ on all non-selected ranks
                                 RankFeatureEnable[3] enables ZQ on all ranks
                                 RankFeatureEnable[4] enables CKE on all non-selected ranks
                                 RankFeatureEnable[5] enables CKE on all ranks

  @retval Bit mask of channel enabled if rank in the channel exists.
**/
extern
UINT8
SelectReutRanks (
  IN MrcParameters *const MrcData,
  IN const UINT8          ch,
  IN UINT8                RankBitMask,
  IN const UINT8          RankFeatureEnable
  );

/**
  This routine updates RXTRAINRANK values and downloads the new
  values from the Register File to the pads.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Defines channel to update
  @param[in] Rank     - Defines rank to update
  @param[in] Byte     - Defines byte to update
  @param[in] Subfield - Defines the register's field or fields to update
  @param[in] Value    - value to be writen into register fields

  @retval Nothing
**/
extern
void
UpdateRxT (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          Rank,
  IN const UINT8          Byte,
  IN const UINT8          Subfield,
  IN const UINT16         Value
  );

/**
  This routine updates RXTRAINRANK register's specific fields defined by the subfield
  subfield values:
    0 - Update RcvEn   - leave other parameter the same
    1 - Update RxDqsP  - leave other parameter the same
    2 - Update RxEq    - leave other parameter the same
    3 - Update RxDqsN  - leave other parameter the same
    4 - Update RxVref  - leave other parameter the same
    5 - Update RxDqsP & RxDqsN - leave other parameter the same
    FF - leave all parameter the same

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Defines channel to update
  @param[in] Rank     - Defines rank to update
  @param[in] Byte     - Defines byte to update
  @param[in] Subfield - Defines the register's field or fields to update
  @param[in] Value    - value to be writen into register fields

  @retval Nothing
**/
void
UpdateRxTValues (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          Rank,
  IN const UINT8          Byte,
  IN const UINT8          Subfield,
  IN const UINT16         Value
  );

/**
  This routine updates TXTRAINRANK values and downloads the new
  values from the Register File to the pads.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Defines channel to update
  @param[in] Rank     - Defines rank to update
  @param[in] Byte     - Defines byte to update
  @param[in] Subfield - Defines the register's field or fields to update
  @param[in] Value    - value to be writen into register fields

  @retval Nothing
**/
extern
void
UpdateTxT (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          Rank,
  IN const UINT8          Byte,
  IN const UINT8          Subfield,
  IN const UINT32         Value
  );

/**
  This routine updates TXTRAINRANK register's specific fields defined by the subfield
  subfield values:
    0 - Update TxDq    - leave other parameter the same
    1 - Update TxDqs   - leave other parameter the same
    2 - Update TxEq    - leave other parameter the same
    3 - Update ALL from input value (non from Mrcdata structure)

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Defines channel to update
  @param[in] Rank     - Defines rank to update
  @param[in] Byte     - Defines byte to update
  @param[in] Subfield - Defines the register's field or fields to update
  @param[in] Value    - value to be writen into register fields

  @retval Nothing
**/
void
UpdateTxTValues (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          Rank,
  IN const UINT8          Byte,
  IN const UINT8          Subfield,
  IN const UINT32         Value
  );

/**
  Returns the index into the array MarginResult in the MrcOutput structure.

  @param[in] ParamV - Margin parameter

  @retval One of the following values: LastRxV(0), LastRxT (1), LastTxV(2), LastTxT (3), LastRcvEna (4),
                                       LastWrLevel (5), LastCmdT (6), LastCmdV (7)
**/
extern
UINT8
GetMarginResultType (
  IN const UINT8  ParamV
  );

/**
  This function Reads MrcData structure and finds the minimum last recorded margin for param
  Searches across all bytes and ranks in RankMask

  @param[in]     MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Data structure with the latest margin results.
  @param[in]     Param           - Defines the margin type
  @param[in]     Ranks           - Condenses down the results from multiple ranks
  @param[in]     ResultRank      - This rank will keep the results from multiple ranks

  @retval mrcWrongInputParameter if a bad Param is passed in, otherwise mrcSuccess.
**/
extern
MrcStatus
GetMarginCh (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          Ranks,
  IN     const UINT8          ResultRank
  );

/**
  This function Reads MrcData structure and finds the minimum last recorded margin for param
  Searches across all bytes and ranks in RankMask

  @param[in]     MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Data structure with the latest margin results.
  @param[in]     Param           - Defines the margin type
  @param[in]     Ranks           - Condenses down the results from multiple ranks

  @retval mrcWrongInputParameter if a bad Param is passed in, otherwise mrcSuccess.
**/
MrcStatus
GetPdaMargins (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          Ranks
  );

/**
  This function Update the Non PDA DDR4 Vref to match the PDA average
  across all bytes (per rank/ch).
  This will allow the use of Non PDA sweep using GetBerMarginByte

  @param[in]     MrcData         - Include all MRC global data.
  @param[in]     Ranks           - ranks to work on

  @retval mrcWrongInputParameter if a bad Param is passed in, otherwise mrcSuccess.
**/
MrcStatus
UpdatePdaCenter (
  IN     MrcParameters *const MrcData,
  IN     const UINT8          Ranks
  );

/**
  Use this function to retrieve the last margin results from MrcData

  @param[in]     MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Data structure with the latest margin results.
  @param[in]     Param           - Defines the margin type
  @param[in]     RankIn          - Which rank of the host structure you want the result returned on
  @param[in]     Ranks           - Condenses down the results from multiple ranks

  @retval MarginResult structure has been updated if MrcStatus returns mrcSuccess.
  @retval Otherwise, mrcWrongInputParameter is returned if an incorrect Param is passed in.
**/
extern
MrcStatus
GetMarginByte (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          RankIn,
  IN     const UINT8          Ranks
  );

/**
  This function is use to "unscale" the MrcData last margin point
  GetMarginByte will scale the results for FAN margin
  This will unscale the results such that future tests start at the correct point

  @param[in]     MrcData      - Include all MRC global data.
  @param[in,out] MarginResult - Input array to be unscaled.
  @param[in]     Param        - Defines the margin type for proper scale selection.
  @param[in]     Rank         - Which rank of the host structure to work on

  @retval mrcSuccess
**/
extern
MrcStatus
ScaleMarginByte (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          Rank
  );

/**
  This function is used by most margin search functions to change te underlying margin parameter.
  This function allows single search function to be used for different types of margins with minimal impact.
  It provides multiple different parameters, including 2D parameters like Read or Write FAN.
  It can work in either MultiCast or single register mode.

  @param[in,out] MrcData       - Include all MRC global data.
  @param[in]     param         - Includes parameter(s) to change including two dimentional.
  @param[in]     value0        - Selected value to program margin param to
  @param[in]     value1        - Selected value to program margin param to in 2D mode (FAN mode)
  @param[in]     EnMultiCast   - To enable Multicast (broadcast) or single register mode
  @param[in]     channel       - Desired Channel
  @param[in]     rankIn        - Desired Rank - only used for the RxTBit and TxTBit settings and to propagate RdVref
  @param[in]     byte          - Desired byte offset register
  @param[in]     bitIn         - Desired bit offset Mrc data strucure if UpdateMrcData is 1
  @param[in]     UpdateMrcData - Used to decide if Mrc host must be updated
  @param[in]     SkipWait      - Used to skip wait until all channel are done
  @param[in]     RegFileParam  - Used to determine which Rank to download.  Passed to MrcDownloadRegFile.

  @retval MrcStatus -  if succeeded, return mrcSuccess
**/
extern
MrcStatus
ChangeMargin (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          param,
  IN     const INT32          value0,
  IN     const INT32          value1,
  IN     const UINT8          EnMultiCast,
  IN     const UINT8          channel,
  IN     const UINT8          rankIn,
  IN     const UINT16         byte,
  IN     const UINT8          bitIn,
  IN     const UINT8          UpdateMrcData,
  IN     const UINT8          SkipWait,
  IN     const MrcRegFile     RegFileParam
  );

/**
  This function triggers the hardware to download the specified RegFile.
  The setting of ReadRfRd and ReadRfWr must be mutually exclusive.
  Only 1 (start download) and 0 (do nothing) are valid values for ReadRfXx.

  @param[in] MrcData       - Global MRC Data
  @param[in] Channel       - The Channel to download target.
  @param[in] ByteMulticast - Enable Multicasting all bytes on that Channel.
  @param[in] Rank          - The Rank download target.
  @param[in] RegFileParam  - Used to determine which Rank to download.
                              MrcRegFileRank    - Uses the Rank Parameter.
                              MrcRegFileStart   - Uses the Rank in REUT_CH_SEQ_BASE_ADDR_START after decoding logical to physical.
                              MrcRegFileCurrent - Uses the Rank in REUT_CH_SEQ_BASE_ADDR_CURRENT after decoding logical to physical.
  @param[in] Byte          - The Byte download target.
  @param[in] ReadRfRd      - Download the read RegFile. 1 enables, 0 otherwise
  @param[in] ReadRfWr      - Download the write RegFile. 1 enables, 0 otherwise

  @retval MrcStatus - If both ReadRfRd and ReadRfWr are set, the functions returns mrcWrongInputParameters.
                         Otherwise, mrcSuccess.
**/
void
MrcDownloadRegFile (
  IN MrcParameters * const  MrcData,
  IN const UINT8            Channel,
  IN const BOOLEAN          ByteMulticast,
  IN UINT8                  Rank,
  IN const MrcRegFile       RegFileParam,
  IN const UINT8            Byte,
  IN const BOOLEAN          ReadRfRd,
  IN const BOOLEAN          ReadRfWr
  );

/**
  This procedure is meant to handle basic timing centering, places strobe in the middle of the data eye,
  for both read and write DQ/DQS using a very robust, linear search algorthim.

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     chBitMaskIn    - Channel bit mask.
  @param[in]     param          - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                   8:WrTBit, 9:RdTBit, 10:RdVBit,
                                   16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                   ONLY RdT and WrT are allowed in this function
  @param[in]     ResetPerBit    - Option to Reset PerBit Deskew to middle value before byte training
  @param[in]     loopcount      - loop count
  @param[in]     MsgPrint       - Serial debug output message enable.
  @param[in]     EarlyCentering - Execute as early centering routine

  @retval MrcStatus -  If succeeded, return mrcSuccess
**/
extern
MrcStatus
DQTimeCentering1D (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          chBitMaskIn,
  IN     const UINT8          param,
  IN     const UINT8          ResetPerBit,
  IN     const UINT8          loopcount,
  IN     BOOLEAN              MsgPrint,
  IN     BOOLEAN              EarlyCentering
  );

/**
  This procedure is meant to handle much more complex centering that will use a 2D algorithm to optimize asymetical
  eyes for both timing and voltage margin.

  @param[in,out] MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Margin data from centering
  @param[in]     ChBitMaskIn     - Channel bit mask.
  @param[in]     param           - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                    8:WrTBit, 9:RdTBit, 10:RdVBit,
                                    16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                    ONLY RdT and WrT are allowed in this function
  @param[in]     EnPerBit        - Option to enable per bit margining
  @param[in]     EnRxDutyCycleIn - Phase to center.
  @param[in]     ResetPerBit     - Option to Reset PerBit Deskew to middle value before byte training
  @param[in]     LoopCount       - loop count
  @param[in]     En2D            - Option to only run center at nominal Vref point

  @retval MrcStatus -  If succeeded, return mrcSuccess
**/
extern
MrcStatus
DataTimeCentering2D (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          ChBitMaskIn,
  IN     const UINT8          Param,
  IN     const UINT8          EnPerBit,
  IN     const UINT8          EnRxDutyCycleIn,
  IN     const UINT8          ResetPerBit,
  IN     const UINT8          LoopCount,
  IN     const UINT8          En2D
  );

/**
  Subfunction of 2D Timing Centering
  Measures paramV margin across ch/bytes and updates the EH/VrefScale variables

  @param[in]     MrcData   - Include all MRC global data.
  @param[in]     ChBitMask - Channel Bit mak for which test should be setup for.
  @param[in]     rank      - Defines rank to used for MrcData
  @param[in]     ParamV    - Margin parameter
  @param[in]     MaxVScale - Maximum Voltage Scale to use
  @param[in]     BMap      - Byte mapping to configure error counter control register
  @param[in,out] EH        - Structure that stores start, stop and increment details for address
  @param[in,out] VrefScale - Parameter to be updated
  @param[in,out] BERStats  - Bit Error Rate Statistics.

  @retval mrcSuccess if successful, otherwise the function returns an error status.
**/
extern
MrcStatus
DQTimeCenterEH (
  IN     MrcParameters * const MrcData,
  IN     const UINT8           ChBitMask,
  IN     const UINT8           rank,
  IN     const UINT8           ParamV,
  IN     const UINT8           MaxVScale,
  IN     UINT8 * const            BMap,
  IN OUT UINT32                EH[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN OUT UINT32                VrefScale[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN OUT UINT32 * const           BERStats
  );

/**
  Update the Vref value
  if VrefType = 0     Updates Ch0 Vref_Dq
  if VrefType = 1     Updates Ch1 Vref_Dq
  if VrefType = 2     Updates Vref_CA

  @param[in,out] MrcData       - Include all MRC global data.
  @param[in]     VrefType      - Determines the Vref to change
  @param[in]     UpdateMrcData - Used to decide if Mrc host must be updated
  @param[in]     Offset        - Vref value
  @param[in]     RankMask      - Selecting which Rank to talk to (only valid for DDR4 and adjusting VrefDQ)
  @param[in]     DeviceMask    - Selecting which Devices to talk to (only valid for DDR4 and adjusting VrefDQ)
  @param[in]     PDAmode       - Selecting to use MRH or old method for MRS (only valid for DDR4 and adjusting VrefDQ)
  @param[in]     SkipWait      - Determines if we will wait for vref to settle after writing to register

  @retval Nothing
**/
extern
void
UpdateVrefWaitTilStable (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          VrefType,
  IN     const UINT8          UpdateMrcData,
  IN     INT32                Offset,
  IN     UINT8                RankMask,
  IN     UINT16               DeviceMask,
  IN     BOOLEAN              PDAmode,
  IN     UINT8                SkipWait
  );

/**
  This function is used to move CMD/CTL/CLK/CKE PIs during training

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel to shift PI for
  @param[in]     Iteration  - Determines which PI to shift:
                              MrcIterationClock = 0
                              MrcIterationCmdN  = 1
                              MrcIterationCmdS  = 2
                              MrcIterationCke   = 3
                              MrcIterationCtl   = 4
                              MrcIterationCmdV  = 5
  @param[in]     RankMask   - Ranks to work on
  @param[in]     GroupMask  - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR3
  @param[in]     NewValue   - value to shift in case of CLK Iteration, New value for all other cases
  @param[in]     UpdateHost - Determines if MrcData structure is updated

  @retval Nothing
**/
extern
void
ShiftPIforCmdTraining (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          Iteration,
  IN     const UINT8          RankMask,
  IN     const UINT8          GroupMask,
  IN     INT32                NewValue,
  IN     const UINT8          UpdateHost
  );

/**
  Finds the limit that PIs can be adjusted to the left and right for a specific channel
  This compares CMD, CLK, CTL, and DQ PIs.

  @param[in,out]  MrcData      - Include all MRC global data.
  @param[in]      Channel      - Channel to check
  @param[in]      RankMask     - Ranks to check
  @param[out]     MinPi        - Minimum PI value across all bytes.
  @param[out]     MaxPi        - Maximum PI value across all bytes.

  @retval Nothing
**/
void
FindNormalizationPiLimits (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          RankMask,
  OUT          UINT16         *MinPi,
  OUT          UINT16         *MaxPi
  );

/**
  Finds the limit that clock can be adjusted for a specific channel
  Compares TxDq, TxDqs and RcvEn values

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel to check
  @param[in]     RankMask   - Ranks to check
  @param[out]    MinPi      - Minimum PI value across all bytes.
  @param[out]    MaxPi      - Maximum PI value across all bytes.

  @retval Nothing
**/
void
FindDqPiLimits (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          RankMask,
  OUT          UINT16         *MinPi,
  OUT          UINT16         *MaxPi
  );

/**
  Shifts RcvEn, WriteLevel and WriteDQS timing for all bytes
  Usually used when moving the clocks on a channel

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel to update
  @param[in]     Rank       - Rank to update
  @param[in]     ByteMask   - Bytes to update
  @param[in]     Offset     - value to shift
  @param[in]     UpdateHost - Determines if MrcData structure is updated

  @retval Nothing
**/
extern
void
ShiftDQPIs (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          Rank,
  IN     const UINT32         ByteMask,
  IN     const INT8           Offset,
  IN     const UINT8          UpdateHost
  );

/**
  Writes to the RxOffsetVdq Broadcast register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel to write to (0xFF to use the broadcast)
  @param[in]   Rank    - Rank to write to (0xFF to use the broadcast)
  @param[in]   Value   - Value to write

**/
extern
void
MrcSetRxOffsetVdqBroadcast (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Rank,
  IN const UINT32          Value
  );

/**
  Writes to the RxOffsetVdq specific registers

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel to write to
  @param[in]   Rank    - Rank to write to
  @param[in]   Byte    - Byte to write to
  @param[in]   Value   - Value to write

**/
extern
void
MrcSetRxOffsetVdq (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Rank,
  IN const UINT8           Byte,
  IN const UINT32          Value
  );

/**
  Returns the Offset for DataTrainFeedback register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
extern
UINT32
MrcGetOffsetDataTrainFeedback (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  );

/**
  Returns the Offset for DllPiTestAndAdc register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetDllPiTestAndAdc (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  );

/**
  Returns the Offset for DataOffsetComp register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetDataOffsetComp (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  );

/**
  Returns the Offset for DataControl0 register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetDataControl0 (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  );

/**
  Returns the Offset for DataControl1 register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetDataControl1 (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  );

/**
  Returns the Offset for DataControl2 register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetDataControl2 (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  );

/**
  Returns the Offset for DataOffsetTrain register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetDataOffsetTrain (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  );

/**
  Returns the Offset for VrefAdjust1 register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetVrefAdjust1 (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  );

/**
  Determines if PerBitDeskew is needed

  @param[in]   MrcData      - The MRC global data.
  @param[in]   MarginResult - Data structure with the latest margin results.
  @param[in]   Param        - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                              8:WrTBit, 9:RdTBit, 10:RdVBit,
                              16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                              ONLY RdT and WrT are allowed in this function

  @retval Update - If DeskewDisable needs to be updated to CPU

**/
BOOLEAN
MrcPerBitDeskew (
  IN MrcParameters * const MrcData,
  IN UINT32                MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN const UINT8           Param
  );

/**
  Translate LPDDR command from CA[9:0] high and low phase to DDR3 MA/BA/CMD.
  This is needed to program CADB.

  @param[in]   CaHigh  - CA[9:0] value on the rising clock
  @param[in]   CaLow   - CA[9:0] value on the falling clock
  @param[out]  MA      - Translated value of MA[15:0]
  @param[out]  BA      - Translated value of BA[2:0]
  @param[out]  CMD     - Translated value of CMD[2:0] = [RASb, CASb, WEb]

**/
extern
void
MrcConvertLpddr2Ddr (
  IN UINT32          const CaHigh,
  IN UINT32          const CaLow,
  OUT UINT32       * MA,
  OUT UINT32       * BA,
  OUT UINT32       * CMD
  );

/**
  Run a short CADB sequence on selected channels

  @param[in] MrcData      - The MRC global data.
  @param[in] ChBitMask    - channels to work on.

**/
extern
void
ShortRunCADB (
  IN MrcParameters * const  MrcData,
  IN UINT8                  ChBitMask
  );


/**
  Get the Rx Bias values

  @param[in, out] MrcData    - Include all MRC global data.
  @param[in, out] RxFselect  - Location to save RxFselect.
  @param[in, out] RxCBSelect - Location to save RxCBSelect.

**/
extern
void
GetRxFselect (
  IN MrcParameters *const MrcData,
  IN OUT INT8          *RxFselect,
  IN OUT UINT8         *RxCBSelect
  );

/**
  Read 32-bit value from the specified bus/device/function/offset.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Bus      - PCI bus number.
  @param[in] Device   - PCI device number.
  @param[in] Function - PCI function number.
  @param[in] Offset   - PCI address offset.

  @retval 32-bit PCI value.
**/
extern
UINT32
MrcPciRead32 (
  IN const MrcParameters * const MrcData,
  IN const UINT8 Bus,
  IN const UINT8 Device,
  IN const UINT8 Function,
  IN const UINT8 Offset
  );

/**
  This function changes the DIMM Voltage to the closest desired voltage without
  going higher. Default wait time is the minimum value of 200us, if more time
  is needed before deassertion of DIMM Reset#, then change the parameter.

  @param[in, out] MrcData            - The MRC "global data" area.
  @param[in]      VddVoltage         - Selects the DDR voltage to use, in mV.
  @param[in, out] VddSettleWaitTime  - Time needed for Vdd to settle after the update

  @retval TRUE if a voltage change occurred, otherwise FALSE.
**/
BOOLEAN
MrcVDDVoltageCheckAndSwitch (
  IN OUT MrcParameters      *MrcData,
  IN     const MrcVddSelect VddVoltage,
  IN OUT UINT32 * const        VddSettleWaitTime
  );


/**
  Debug output of MarginResults for specific ResultType

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] ResultType - Margin Result Type

**/
extern
void
MrcDisplayMarginResultArray (
  IN MrcParameters *MrcData,
  IN UINT8         ResultType
  );

/**
  Setup for Memory Check like Alias Checking and DDR4 PDA mapping

  @param[in, out] MrcData           - Pointer to MRC global data.
  @param[in, out] ReutAddress       - Pointer to ReutAddress that will be programmed to REUT engine
  @param[in] Rank                   - Rank to setup
  @param[in] NumOfCachelines        - # of Cachelines to write and read to.  0 is a special value that will write the number
                                      of Cachelines that is required to determine Row/Column Aliasing.
  @param[in, out] ReutUninitialized - Pointer of whether ReutAddress Pointer needs initializing or not.

**/
void
MrcMemoryCheckSetup (
  IN OUT MrcParameters *const MrcData,
  IN OUT MRC_REUTAddress      *ReutAddress,
  IN UINT8                    Rank,
  IN UINT8                    NumOfCachelines,
  IN OUT BOOLEAN              *ReutUninitialized
  );

/**
  Hook before normal mode is enabled.

  @param[in, out] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
void
MrcBeforeNormalModeTestMenu (
  IN OUT MrcParameters *const MrcData
  );

/**
  Returns the effective Dimm Write ODT.
  Consider the dram tech, Rtt configuration (Wr, Nom, Park) and Normal Odt logic.
  Note : We still have the assumption of same Rtt's for all ranks in a same dimm.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in] Channel                - Channel to setup
  @param[in] Rank                   - Rank to setup
  @param[in] OdtType                - OdtType - 0:write 1:read
  @param[in] GetFromTable           - Get the Values from Odt tables

  @retval Value in Ohms
**/
extern
UINT16
MrcGetEffDimmWriteOdt (
  IN OUT MrcParameters *const MrcData,
  UINT8                       Channel,
  UINT8                       Rank,
  UINT8                       OdtType,
  BOOLEAN                     GetFromTable
  );

/**
  Set default Tx Dimm Vref for DDR4.
  Use default CPU Ron and DIMM Write Odt values.

  @param[in, out] MrcData - Include all MRC global data.

  @retval none
**/
extern
void
MrcSetDefaultTxVrefDdr4 (
  IN OUT MrcParameters *const MrcData
  );

/**
  Set Tx Dimm Vref absolute Value for DDR4.
  Use custom MRC range [-36:+37] where zero offset is 820mV and step is 7.8mV (JEDEC spec).

  @param[in, out] MrcData       - Include all MRC global data.
  @param[in]      Channel       - Channel to setup
  @param[in]      Rank          - Rank to setup
  @param[in]      TxVrefOffset  - TxVref Offset.
  @param[in]      UpdateMrcData - update MRC host struct

  @retval none
**/
extern
void
MrcSetTxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  UINT8                Channel,
  UINT8                Rank,
  INT8                 TxVrefOffset,
  BOOLEAN              UpdateMrcData
  );

/**
  Generic routine to perform Linear Centering in different 2D points.
  Re-uses DQTimeCentering1D routine as the linear centering routine.
  Optimize Per channel in the 2D param space.
  Run-Time - about 20nsec for 6 vref points and loopcout of 10

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     ChBitMask      - Channel bit mask.
  @param[in]     RankBitMask    - Ranks to center.
  @param[in]     Param          - Param to center with linear search.  Uses DQTimeCentering1D (RdT,WrT,WrV,RdV,RcvX).
  @param[in]     Param2D        - The 2D Param to Offset. Use change margin routine
  @param[in]     Points2DMin    - Minimum value of second dimension points to sweep.
  @param[in]     Points2DMax    - Maxmimum value of second dimension points to sweep.
  @param[in]     ParamStepSize  - Step size of second dimension points to sweep.
  @param[in]     LoopCount      - Loop count.
  @param[in]     TestType       - 0: normal reads, 1: Read MPR
  @param[in]     Prints         - Debug prints enable/disable

  @retval MrcStatus - If it successed return mrcSuccess
**/
MrcStatus
EarlyLinearCentering2D (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                ChBitMask,
  IN     UINT8                RankBitMask,
  IN     UINT8                Param,
  IN     UINT8                Param2D,
  IN     INT8                 Points2DMin,
  IN     INT8                 Points2DMax,
  IN     UINT8                ParamStepSize,
  IN     UINT8                LoopCount,
  IN     UINT8                TestType,
  IN     BOOLEAN              Prints
  );

/**
  Set ODT Logic behavior for DDR4.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Profile - behavior Type. Currently Profile 1 is supported (DDR3-like)
  @retval none
**/
void
MrcSetOdtMatrix (
  IN OUT MrcParameters *const MrcData,
  IN UINT8                    Profile
  );


/**
  Get the Other Dimm in Channel.

  @param[in, out] MrcData  - Include all MRC global data.
  @param[in]      Channel  - Channel to search in.
  @param[in]      RankMask - Rank mask for the current DIMM.

  @retval The other Dimm outside the RankMask.  If no such DIMM, then return current DIMM.
**/
UINT8
MrcGetOtherDimm (
  IN MrcParameters *const MrcData,
  IN UINT8                Channel,
  IN UINT8                RankMask
  );

/**
  Disable CADB Deselects, used after SetupIOTestCADB was called during Command Training or RMT.

  @param[in] MrcData  - Include all MRC global data.

  @retval none
**/
VOID
MrcDisableCadbOnDeselect (
  IN MrcParameters *const MrcData
  );

/**
  This function returns the Minimal Eye Height required

  @param[in] MrcData        - Pointer to MRC global data.
  @param[in] EarlyCentering - TRUE if this is an early centering step

  @retval Returns minimal eye height required
**/
UINT32
MrcGetMinimalEyeHeight (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              EarlyCentering
  );

#endif // _MrcCommon_h_
