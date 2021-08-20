/** @file
  The third stage of the write training is determining the PI setting for
  each byte strobe to make sure that data is sent at the optimal location.
  In order to do that a pattern of alternating zeros and ones is written to
  a block of the memory, and then read out.  By identifying the location
  where it is farthest away from where errors are shown the DQS will be
  aligned to the center of the eye.

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
#include "MrcWriteDqDqs.h"

/**
  this function executes the write timing centering.
  Center Tx DQS-DQ using moderate pattern with 1D eye.

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus      - if it succeeded returns mrcSuccess
**/
MrcStatus
MrcWriteTimingCentering (
  IN     MrcParameters *const MrcData
  )
{
  MrcIntChannelOut  *IntChannelOut;
  MrcIntOutput      *MrcIntData;
  MrcOutput         *Outputs;
  MrcStatus         Status;
  UINT32            Offset;
  UINT8             Channel;
  UINT8             ResetPerbit;
  UINT8             LoopCount;
  BOOLEAN           Lpddr3;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT TcRdRd;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Outputs = &MrcData->Outputs;
  Lpddr3  = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  ResetPerbit = 1;

  LoopCount   = 10;

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

  Status = DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, WrT, ResetPerbit, LoopCount, TRUE, FALSE);

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
  This function executes the write Voltage centering (LPDDR3 or DDR4 only).
  Center Tx DQ Vref using moderate pattern with 1D eye (using PDA mode for DDR4).

  @param[in] MrcData     - Include all MRC global data.

  @retval MrcStatus      - if it succeeded return mrcSuccess. mrcUnsupportedTechnology if the memory technology isn't LPDDR3 or DDR4.
**/
MrcStatus
MrcWriteVoltageCentering (
  IN     MrcParameters *const MrcData
  )
{
  MrcIntChannelOut  *IntChannelOut;
  MrcIntOutput      *MrcIntData;
  MrcStatus         Status;
  MrcOutput *Outputs;
  MrcInput  *Inputs;
  MrcDebug  *Debug;
  const MRC_FUNCTION *MrcCall;
  UINT32    Low[MAX_CHANNEL];
  UINT32    High[MAX_CHANNEL];
  INT32     Center[MAX_CHANNEL];
  UINT32    *Margin;
  UINT32    Offset;
  UINT8     LoopCount;
  UINT8     Channel;
  UINT8     Rank;
  UINT8     Byte;
  BOOLEAN   MarginSignReversedChannel[MAX_CHANNEL][MAX_EDGES];
  BOOLEAN   *MarginSignReversed;
  BOOLEAN   MsgPrint;
  BOOLEAN   Lpddr3;
  BOOLEAN   Ddr4;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT TcRdRd;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Outputs = &MrcData->Outputs;
  Inputs  = &MrcData->Inputs;
  Debug   = &Outputs->Debug;
  MrcCall = Inputs->Call.Func;
  Lpddr3  = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  Ddr4    = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  if ((!Ddr4) && (!Lpddr3)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Error Handler: Wrong Memory Technology\n");
    return mrcUnsupportedTechnology;
  }

  LoopCount   = 10;

  MsgPrint = (Lpddr3) ? FALSE : TRUE;

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

  Status = DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, WrV, 0, LoopCount, MsgPrint, FALSE);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      // Restore the same rank RDRD turnaround
      IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
      Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_TC_RDRD_REG, MCHBAR_CH1_CR_TC_RDRD_REG, Channel);
      MrcWriteCR (MrcData, Offset, IntChannelOut->MchbarTcRdRd.Data);
    }
  }

  if (Lpddr3) {
    MrcCall->MrcSetMem ((UINT8 *) Low, sizeof (Low), 0xFF);
    MrcCall->MrcSetMem ((UINT8 *) High, sizeof (High), 0xFF);
    MrcCall->MrcSetMem ((UINT8 *) MarginSignReversedChannel, sizeof (MarginSignReversedChannel), 0);
    // For Non-PDA extract the latest Margin Results and performance Post-Centering
    // Find center value and program it

    // For each Channel, determine if the lowest margin result is Sign Reversed.
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MarginSignReversed = &Outputs->MarginSignReversed[Rank][Channel][Byte][0];;
            MarginSignReversedChannel[Channel][0] |= MarginSignReversed[0];
            MarginSignReversedChannel[Channel][1] |= MarginSignReversed[1];
          } // for Byte
        }
      } // for Rank
      // If the limiting margin in the channel is sign reversed, change the initial value for proper MIN/MAX logic.
      Low[Channel]  = MarginSignReversedChannel[Channel][0] ? 0 : Low[Channel];
      High[Channel] = MarginSignReversedChannel[Channel][1] ? 0 : High[Channel];
    } // for Channel


    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Margin = &Outputs->MarginResult[LastTxV][Rank][Channel][Byte][0];
          MarginSignReversed = &Outputs->MarginSignReversed[Rank][Channel][Byte][0];
          // Based on Sign Reversed Margin results, find limiting edge for each channel
          if (MarginSignReversedChannel[Channel][1]) {
            // Only compare Margin results for Sign Reversed Bytes/Ranks
            if (MarginSignReversed[1]) {
              High[Channel] = MAX(High[Channel], Margin[1]);
            }
          } else {
            High[Channel] = MIN(High[Channel], Margin[1]);
          }
          if (MarginSignReversedChannel[Channel][0]) {
            // Only compare Margin results for Sign Reversed Bytes/Ranks
            if (MarginSignReversed[0]) {
              Low[Channel] = MAX(Low[Channel], Margin[0]);
            }
          } else {
            Low[Channel] = MIN(Low[Channel], Margin[0]);
          }
        } // for Byte
      } // for Rank
    } // for Channel

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      // Calculate Margin height and center based on Low/High side sign
      if (MarginSignReversedChannel[Channel][0]) {
        Center[Channel] = ((INT32) (High[Channel] + Low[Channel])) / 2;
      }
      else if (MarginSignReversedChannel[Channel][1]) {
        Center[Channel] = (-1) * (((INT32) (High[Channel] + Low[Channel])) / 2);
      }
      else {
        Center[Channel] = ((INT32) (High[Channel] - Low[Channel])) / 2;
      }

      // Program Center Value.
      UpdateVrefWaitTilStable(MrcData, Channel, 1, Center[Channel] / 10, 0, 0, FALSE, 0);
    } // for Channel
  }

  return  Status;
}

/**
  this function executes the write timing centering in 2D.
    Final write timing centering using 2D algorithm and per bit optimization.

    @param[in] MrcData - Include all MRC global data.

    @retval MrcStatus -  if it succeded returns mrcSuccess

  **/
MrcStatus
MrcWriteTimingCentering2D (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput  *Inputs;
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  MrcStatus       Status;
  UINT8           EnPerBit;
  UINT8           EnRxDutyCycle;
  UINT8           ResetPerBit;
  UINT8           LoopCount;
  UINT8           En2D;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  EnPerBit      = 1;
  EnRxDutyCycle = 0;
  ResetPerBit   = 1;
  LoopCount     = 15;
  En2D          = 0;

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "\n\nCalling with EnRxDutyCycle = %d, EnPerBit = %d, ResetPerBit = %d En2D = %d\n",
    EnRxDutyCycle,
    EnPerBit,
    ResetPerBit,
    En2D
    );

  Status = DataTimeCentering2D (
             MrcData,
             Outputs->MarginResult,
             Outputs->ValidChBitMask,
             WrT,
             EnPerBit,
             EnRxDutyCycle,
             ResetPerBit,
             LoopCount,
             En2D
             );

  if (mrcSuccess == Status) {
    if (Outputs->DdrType == MRC_DDR_TYPE_DDR3) {
      MrcPerBitDeskew (
        MrcData,
        Outputs->MarginResult,
        WrT
        );
    }

    EnPerBit    = 0;
    ResetPerBit = 0;
    En2D        = 1;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "\n\nCalling with EnRxDutyCycle = %d, EnPerBit = %d, ResetPerBit = %d En2D = %d\n",
      EnRxDutyCycle,
      EnPerBit,
      ResetPerBit,
      En2D
      );

    Status = DataTimeCentering2D (
               MrcData,
               Outputs->MarginResult,
               Outputs->ValidChBitMask,
               WrT,
               EnPerBit,
               EnRxDutyCycle,
               ResetPerBit,
               LoopCount,
               En2D
               );
  }

  return Status;
}

/**
  Rank Margin Tool - Measure margins across various parameters

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  mrcSuccess if succeded
**/
MrcStatus
MrcRankMarginTool (
  IN OUT MrcParameters *const MrcData
  )
{
  static const UINT16                  mode = 0;
  const MrcInput                      *Inputs;
  MrcDebug                            *Debug;
  const MRC_FUNCTION                  *MrcCall;
  MrcOutput                           *Outputs;
  MrcControllerOut                    *ControllerOut;
  MrcChannelOut                       *ChannelOut;
  MrcCommandMargin                    *CommandOut;
  MrcRecvEnMargin                     *RecvEnOut;
  MrcWrLevelMargin                    *WrLevelOut;
  MrcStatus                           Status;
  UINT32                              BERStats[4];
  UINT32                              Offset;
  UINT8                               Rank;
  UINT8                               Param;
  UINT8                               RankMask;
  UINT8                               Controller;
  UINT8                               Channel;
  UINT8                               byte;
  UINT8                               bit;
  UINT8                               LcLoop;
  UINT8                               BMap[MAX_SDRAM_IN_DIMM];
  UINT8                               chBitMask;
  UINT8                               MaxMargin;
  UINT8                               DqLoopCount;
  UINT8                               CmdLoopCount;
  INT8                                VrefOffsets[2];
  INT8                                ClkPiMin[MAX_CHANNEL];
  UINT8                               ClkPiMax[MAX_CHANNEL];
  BOOLEAN                             Lpddr;
  BOOLEAN                             Ddr4;
  BOOLEAN                             SkipVref;
  MrcPower                            PwrChRank[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  MCHBAR_CH0_CR_SC_GS_CFG_STRUCT      ScGsCfg;
  MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT ReutChSeqCfg;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) VrefOffsets, sizeof (VrefOffsets), 0);
  MrcCall->MrcSetMem ((UINT8 *) PwrChRank, sizeof (PwrChRank), 0);
  MrcCall->MrcSetMem ((UINT8 *) ClkPiMin, sizeof (ClkPiMin), ((UINT8) -64));
  MrcCall->MrcSetMem ((UINT8 *) ClkPiMax, sizeof (ClkPiMax), 64);
  for (LcLoop = 0; LcLoop < (sizeof (BMap) / sizeof (BMap[0])); LcLoop++) {
    BMap[LcLoop] = LcLoop;
  }

  if (Inputs->BootMode == bmFast) {
    //
    // Set CPGC mode
    //
    ReutChSeqCfg.Data                     = 0;
    ReutChSeqCfg.Bits.Initialization_Mode = REUT_Testing_Mode;
    MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG, (UINT32) ReutChSeqCfg.Data);
    MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG, (UINT32) ReutChSeqCfg.Data);
  }

#if DATA_EYE_MARGIN_SUPPORT
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }

      EyeMargin (
        MrcData,
        Channel,
        0x1 << Rank,
        WrT,
        WrV,
        0,
        -MAX_POSSIBLE_TIME,
        MAX_POSSIBLE_TIME,
        MAX_POSSIBLE_VREF,
        15,
        1,
        0
        );

      EyeMargin (
        MrcData,
        Channel,
        0x1 << Rank,
        RdT,
        RdV,
        0,
        -MAX_POSSIBLE_TIME,
        MAX_POSSIBLE_TIME,
        MAX_POSSIBLE_VREF,
        15,
        1,
        0
        );
    }
  }

#endif

#if CMD_EYE_MARGIN_SUPPORT
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Param = 0; Param < MrcIterationCmdV; Param++) {//MrcIterationCmdV
      EyeMargin (MrcData, Channel, 0xf, CmdT, CmdV, Param, -15, 15, 35, 10, 1, 0);
    }
  }
#endif
  //
  // Check memory used
  //
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  Ddr4  = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  //
  // Enable command tri state during RMT training.
  //
  if (!Inputs->CmdTriStateDis) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        Offset = MCHBAR_CH0_CR_SC_GS_CFG_REG + ((MCHBAR_CH1_CR_SC_GS_CFG_REG - MCHBAR_CH0_CR_SC_GS_CFG_REG) * Channel);
        ScGsCfg.Data = MrcReadCR (MrcData, Offset);
        ScGsCfg.Bits.cmd_3st = 0;
        MrcWriteCR (MrcData, Offset, ScGsCfg.Data);
      }
    }
  }

  DqLoopCount  = 17;
  CmdLoopCount = 17;

  //
  // Calculate all the Ranks/Channel power.
  //
  CalcSysPower (MrcData, PwrChRank);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank Margin Testing: DQ LC = %d, Cmd LC = %d\n\n", DqLoopCount, CmdLoopCount);
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Margin\nParams: RcvEna\tWrLevel\tRdT\tWrT\tRdV\tWrV\tCmdT\tCmdV\tRdPower\tWrPower\tTotPwr\n"
    );
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "\tLft Rgt Lft Rgt Lft Rgt Lft Rgt Low Hi  Low Hi  Lft Rgt Low Hi\t[mW]\t[mW]\t[mW]\n"
    );
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    //
    // Select rank for REUT test
    //
    RankMask  = 1 << Rank;
    chBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      chBitMask |= SelectReutRanks (MrcData, Channel, RankMask, 0);
      if ((MRC_BIT0 << Channel) & chBitMask) {
        ChannelOut = &Outputs->Controller[0].Channel[Channel];
        //
        // Clear any old state in DataOffsetTrain
        //
        MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
      }
    }
    //
    // Continue with next rank if this rank is not present on any channel
    //
    if (!(chBitMask)) {
      continue;
    }
    //
    // Setup Test
    // SOE=1, EnCADB=0, EnCKE=0 SOE=1 sets bit12 of REUT_CH_ERR_CTL
    //
    SetupIOTestBasicVA (MrcData, chBitMask, DqLoopCount, NSOE, 0, 0, 8);
    for (Param = RcvEna; Param <= WrLevel; Param++) {
      if (Param == WrDqsT) {
        continue;
      }

      //
      // For Write/Read timing margining, we want to run traffic with Rd->Rd turnaround times of 4 and 5.
      // This statement depends on the order of MRC_MarginTypes.  If this enum's order changes, this
      // statement must change.
      //
      if (Param == RdT) {
        Outputs->DQPat = RdRdTA;
      } else if (Param == RdV) {
        Outputs->DQPat = BasicVA;
      }

      MaxMargin = ((Param == RdV) || (Param == WrV)) ? MAX_POSSIBLE_VREF : MAX_POSSIBLE_TIME;
      if ((Ddr4) && (Param == WrV)) {
        MaxMargin = MAX_POSSIBLE_DDR4_WRITE_VREF;
        Status = MrcGetBERMarginByte (
                   MrcData,
                   Outputs->MarginResult,
                   chBitMask,
                   RankMask,
                   RankMask,
                   Param,
                   mode,
                   BMap,
                   (UINT8) Inputs->EnBER,
                   MaxMargin,
                   0,
                   BERStats
                   );
        // Put worst case margin into the given Rank
        GetMarginCh (MrcData, Outputs->MarginResult, Param, RankMask, Rank);
      } else {
        //
        // Run test for different Params
        //
        Status = MrcGetBERMarginCh (
                   MrcData,
                   Outputs->MarginResult,
                   chBitMask,
                   (Ddr4 && (Param == WrV)) ? RankMask : Rank,
                   (Ddr4 && (Param == WrV)) ? RankMask : Rank,
                   Param,
                   mode,
                   (UINT8) Inputs->EnBER,
                   MaxMargin,
                   0,
                   BERStats
                   );
      }
    }

    //
    // Use CADB test for Cmd to match Late Command Training
    //
    SetupIOTestCADB (MrcData, chBitMask, CmdLoopCount, NSOE, 1, 0);

    //
    // Run test for Cmd Timing
    //
    SkipVref    = TRUE;

    if (Lpddr) {
      CmdLinearFindEdgesLpddr (MrcData, MrcIterationClock, chBitMask, RankMask, MRC_PRINTS_OFF);
    } else {
      CmdLinearFindEdges (MrcData, MrcIterationClock, chBitMask, RankMask, 3, ClkPiMin, ClkPiMax, 1, 1, VrefOffsets, MRC_PRINTS_OFF, SkipVref, FALSE);
    }

    //
    // Restore centered value
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, RankMask, 3, 0, 0);
      }
    }

    Status = MrcResetSequence (MrcData);

    //
    // Run test for Cmd Voltage
    //
    Status = MrcGetBERMarginCh (
               MrcData,
               Outputs->MarginResult,
               chBitMask,
               0xFF,
               Rank,
               CmdV,
               mode,
               0,
               MAX_POSSIBLE_VREF,
               0,
               BERStats
               );

    Status = MrcResetSequence (MrcData);



    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          ChannelOut        = &ControllerOut->Channel[Channel];
          CommandOut        = &ChannelOut->Command[Rank];
          CommandOut->Left  = (UINT8) (Outputs->MarginResult[LastCmdT][Rank][Channel][0][0] / 10);
          CommandOut->Right = (UINT8) (Outputs->MarginResult[LastCmdT][Rank][Channel][0][1] / 10);
          CommandOut->Low   = (UINT8) (Outputs->MarginResult[LastCmdV][Rank][Channel][0][0] / 10);
          CommandOut->High  = (UINT8) (Outputs->MarginResult[LastCmdV][Rank][Channel][0][1] / 10);
          RecvEnOut         = &ChannelOut->ReceiveEnable[Rank];
          RecvEnOut->Left   = (UINT8) (Outputs->MarginResult[LastRcvEna][Rank][Channel][0][0] / 10);
          RecvEnOut->Right  = (UINT8) (Outputs->MarginResult[LastRcvEna][Rank][Channel][0][1] / 10);
          WrLevelOut        = &ChannelOut->WriteLevel[Rank];
          WrLevelOut->Left  = (UINT8) (Outputs->MarginResult[LastWrLevel][Rank][Channel][0][0] / 10);
          WrLevelOut->Right = (UINT8) (Outputs->MarginResult[LastWrLevel][Rank][Channel][0][1] / 10);
          for (byte = 0; byte < Outputs->SdramCount; byte++) {
            for (bit = 0; bit < MAX_BITS; bit++) {
              ChannelOut->RxDqPb[Rank][byte][bit].Left      = (UINT8) (Outputs->MarginResult[LastRxT][Rank][Channel][0][0] / 10);
              ChannelOut->RxDqPb[Rank][byte][bit].Right     = (UINT8) (Outputs->MarginResult[LastRxT][Rank][Channel][0][1] / 10);
              ChannelOut->TxDqPb[Rank][byte][bit].Left      = (UINT8) (Outputs->MarginResult[LastTxT][Rank][Channel][0][0] / 10);
              ChannelOut->TxDqPb[Rank][byte][bit].Right     = (UINT8) (Outputs->MarginResult[LastTxT][Rank][Channel][0][1] / 10);
              ChannelOut->RxDqVrefPb[Rank][byte][bit].Low   = (UINT8) (Outputs->MarginResult[LastRxV][Rank][Channel][0][0] / 10);
              ChannelOut->RxDqVrefPb[Rank][byte][bit].High  = (UINT8) (Outputs->MarginResult[LastRxV][Rank][Channel][0][1] / 10);
              ChannelOut->TxDqVrefPb[Rank][byte][bit].Low   = (UINT8) (Outputs->MarginResult[LastTxV][Rank][Channel][0][0] / 10);
              ChannelOut->TxDqVrefPb[Rank][byte][bit].High  = (UINT8) (Outputs->MarginResult[LastTxV][Rank][Channel][0][1] / 10);
            }
          }
        }
      }
    }
  } // for Rank

  //
  // Disable CADB Deselects after RMT
  //
  MrcDisableCadbOnDeselect (MrcData);

  //
  // Disable command tri state back
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      Offset = MCHBAR_CH0_CR_SC_GS_CFG_REG + ((MCHBAR_CH1_CR_SC_GS_CFG_REG - MCHBAR_CH0_CR_SC_GS_CFG_REG) * Channel);
      ScGsCfg.Data = MrcReadCR (MrcData, Offset);
      ScGsCfg.Bits.cmd_3st = 1;
      MrcWriteCR (MrcData, Offset, ScGsCfg.Data);
    }
  }

#ifdef MRC_DEBUG_PRINT
  //
  // Print test results
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dR%d:\t", Channel, Rank);
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "%2d  %2d\t%2d  %2d\t%2d  %2d\t%2d  %2d\t%2d  %2d\t%2d  %2d\t%2d  %2d\t%2d  %2d\t%2d.%d\t%2d.%d\t%2d.%d\n",
          Outputs->MarginResult[LastRcvEna][Rank][Channel][0][0] / 10,
          Outputs->MarginResult[LastRcvEna][Rank][Channel][0][1] / 10,
          Outputs->MarginResult[LastWrLevel][Rank][Channel][0][0] / 10,
          Outputs->MarginResult[LastWrLevel][Rank][Channel][0][1] / 10,
          Outputs->MarginResult[LastRxT][Rank][Channel][0][0] / 10,
          Outputs->MarginResult[LastRxT][Rank][Channel][0][1] / 10,
          Outputs->MarginResult[LastTxT][Rank][Channel][0][0] / 10,
          Outputs->MarginResult[LastTxT][Rank][Channel][0][1] / 10,
          Outputs->MarginResult[LastRxV][Rank][Channel][0][0] / 10,
          Outputs->MarginResult[LastRxV][Rank][Channel][0][1] / 10,
          Outputs->MarginResult[LastTxV][Rank][Channel][0][0] / 10,
          Outputs->MarginResult[LastTxV][Rank][Channel][0][1] / 10,
          Outputs->MarginResult[LastCmdT][Rank][Channel][0][0] / 10,
          Outputs->MarginResult[LastCmdT][Rank][Channel][0][1] / 10,
          Outputs->MarginResult[LastCmdV][Rank][Channel][0][0] / 10,
          Outputs->MarginResult[LastCmdV][Rank][Channel][0][1] / 10,
          PwrChRank[Channel][Rank].RdPower / 10,
          PwrChRank[Channel][Rank].RdPower % 10,
          PwrChRank[Channel][Rank].WrPower / 10,
          PwrChRank[Channel][Rank].WrPower % 10,
          PwrChRank[Channel][Rank].TotalPwr / 10,
          PwrChRank[Channel][Rank].TotalPwr % 10
          );
      }
    }
  }
#endif

  if (Inputs->BootMode == bmFast) {
    //
    // Set Normal Operation Mode
    // Write to both channels, we need to set this even if a channel is not populated, due to MC requirements for SAGV.
    //
    ReutChSeqCfg.Data                     = 0;
    ReutChSeqCfg.Bits.Initialization_Mode = NOP_Mode;
    MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG, (UINT32) ReutChSeqCfg.Data);
    MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG, (UINT32) ReutChSeqCfg.Data);
  }

  return Status;
}

/**
  Rank Margin Tool - Measure margins across various parameters

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  mrcSuccess if succeded
**/
MrcStatus
MrcRankMarginToolBit (
  IN OUT MrcParameters *const MrcData
)
{
  static const UINT16                  mode = 0;
  const MrcInput                      *Inputs;
  MrcDebug                            *Debug;
  const MRC_FUNCTION                  *MrcCall;
  MrcOutput                           *Outputs;
  MrcControllerOut                    *ControllerOut;
  MrcChannelOut                       *ChannelOut;
  MrcStatus                           Status;
  UINT32                              Offset;
  UINT8                               Controller;
  UINT8                               Channel;
  UINT8                               RankMask;
  UINT8                               Rank;
  UINT8                               Byte;
  UINT8                               Bit;
  UINT8                               Edge;
  UINT8                               Param;
  UINT8                               chBitMask;
  UINT8                               MaxMargin;
  UINT8                               DqLoopCount;
  UINT8                               ResultType;
  BOOLEAN                             Ddr4;
  UINT32                              MarginBit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES];
  UINT32                              MarginByte[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  MCHBAR_CH0_CR_SC_GS_CFG_STRUCT      ScGsCfg;
  MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT ReutChSeqCfg;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;

  if (Inputs->BootMode == bmFast) {
    //
    // Set CPGC mode
    //
    ReutChSeqCfg.Data                     = 0;
    ReutChSeqCfg.Bits.Initialization_Mode = REUT_Testing_Mode;
    MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG, (UINT32) ReutChSeqCfg.Data);
    MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG, (UINT32) ReutChSeqCfg.Data);
  }

  // Check memory used
  Ddr4  = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  //
  // Enable command tri state during RMT training.
  //
  if (!Inputs->CmdTriStateDis) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        Offset = MCHBAR_CH0_CR_SC_GS_CFG_REG + ((MCHBAR_CH1_CR_SC_GS_CFG_REG - MCHBAR_CH0_CR_SC_GS_CFG_REG) * Channel);
        ScGsCfg.Data = MrcReadCR (MrcData, Offset);
        ScGsCfg.Bits.cmd_3st = 0;
        MrcWriteCR (MrcData, Offset, ScGsCfg.Data);
      }
    }
  }

  DqLoopCount = (Inputs->RMTLoopCount == 0) ? 17 : Inputs->RMTLoopCount;
  Outputs->NumCL = 128;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank Margin Bit Testing: LC = %d\n\n", DqLoopCount);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    //
    // Select rank for REUT test
    //
    RankMask  = 1 << Rank;
    chBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      chBitMask |= SelectReutRanks (MrcData, Channel, RankMask, 0);
      if ((MRC_BIT0 << Channel) & chBitMask) {
        ChannelOut = &Outputs->Controller[0].Channel[Channel];
        //
        // Clear any old state in DataOffsetTrain
        //
        MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
      }
    }
    //
    // Continue with next rank if this rank is not present on any channel
    //
    if (!(chBitMask)) {
      continue;
    }
    //
    // Setup Test
    // SOE=1, EnCADB=0, EnCKE=0 SOE=1 sets bit12 of REUT_CH_ERR_CTL
    //
    SetupIOTestBasicVA (MrcData, chBitMask, DqLoopCount, NSOE, 0, 0, 8);
    for (Param = RdT; Param < WrLevel; Param++) {
      if (Param == WrDqsT) {
        continue;
      }

      ResultType = GetMarginResultType (Param);
      if (Param == WrV) {
        MaxMargin = (Ddr4) ? MAX_POSSIBLE_DDR4_WRITE_VREF : MAX_POSSIBLE_VREF;
      } else if (Param == RdV) {
        MaxMargin = MAX_POSSIBLE_VREF;
      } else {
        MaxMargin = MAX_POSSIBLE_TIME;
      }

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          for (Edge = 0; Edge < MAX_EDGES; Edge++) {
            MarginByte[Channel][Byte][Edge] = Outputs->MarginResult[ResultType][Rank][Channel][Byte][Edge];
          }
        }
      }

      MrcGetMarginBit (MrcData, chBitMask, Rank, MarginBit, MarginByte, Param, mode, MaxMargin, FALSE);

      for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
        ControllerOut = &Outputs->Controller[Controller];
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
            continue;
          }
          ChannelOut        = &ControllerOut->Channel[Channel];
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            for (Bit = 0; Bit < MAX_BITS; Bit++) {
              switch (Param) {
              case WrV:
                ChannelOut->TxDqVrefPb[Rank][Byte][Bit].High = (UINT8) MarginBit[Channel][Byte][Bit][1];
                ChannelOut->TxDqVrefPb[Rank][Byte][Bit].Low  = (UINT8) MarginBit[Channel][Byte][Bit][0];
                break;

              case WrT:
                ChannelOut->TxDqPb[Rank][Byte][Bit].Right = (UINT8) MarginBit[Channel][Byte][Bit][1];
                ChannelOut->TxDqPb[Rank][Byte][Bit].Left  = (UINT8) MarginBit[Channel][Byte][Bit][0];
                break;

              case RdV:
                ChannelOut->RxDqVrefPb[Rank][Byte][Bit].High = (UINT8) MarginBit[Channel][Byte][Bit][1];
                ChannelOut->RxDqVrefPb[Rank][Byte][Bit].Low  = (UINT8) MarginBit[Channel][Byte][Bit][0];
                break;

              case RdT:
                ChannelOut->RxDqPb[Rank][Byte][Bit].Right = (UINT8) MarginBit[Channel][Byte][Bit][1];
                ChannelOut->RxDqPb[Rank][Byte][Bit].Left  = (UINT8) MarginBit[Channel][Byte][Bit][0];
                break;

              default:
                break;
              } // switch (Param)
            } // for Bit
          } // for Byte
        } // for Channel
      } // for Controller
    } // for Param
  } // for Rank

    //
    // Disable command tri state back
    //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      Offset = MCHBAR_CH0_CR_SC_GS_CFG_REG + ((MCHBAR_CH1_CR_SC_GS_CFG_REG - MCHBAR_CH0_CR_SC_GS_CFG_REG) * Channel);
      ScGsCfg.Data = MrcReadCR (MrcData, Offset);
      ScGsCfg.Bits.cmd_3st = 1;
      MrcWriteCR (MrcData, Offset, ScGsCfg.Data);
    }
  }
  if (Inputs->BootMode == bmFast) {
    //
    // Set Normal Operation Mode
    // Write to both channels, we need to set this even if a channel is not populated, due to MC requirements for SAGV.
    //
    ReutChSeqCfg.Data                     = 0;
    ReutChSeqCfg.Bits.Initialization_Mode = NOP_Mode;
    MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG, (UINT32) ReutChSeqCfg.Data);
    MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG, (UINT32) ReutChSeqCfg.Data);
  }

  return Status;
}

/**
  Peform Write Voltage Centering in 2D.
  Note: This function currently only supports param = WrV

  @param[in, out] MrcData       - Include all MRC global data.

  @retval MrcStatus -  if it succeded returns mrcSuccess
  @todo - Need option for loopcount
**/
MrcStatus
MrcWriteVoltageCentering2D (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput       *Outputs;
  MrcChannelOut   *ChannelOut;
  MrcStatus       Status;
  UINT32 (*marginch) [MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];

  UINT8 ResultType;
  UINT8 ResultTypeT;
  UINT8 loopcount;
  UINT8 param;
  UINT8 paramT;
  UINT8 Channel;
  UINT8 byte;
  UINT8 tim;
  UINT8 chBitMask;
  UINT8 MaxTscale;
  UINT8 SkipWait;
  INT8  SumEH;
  INT8  SumEHSign;
  INT8  TimePoints[3];
  UINT8 EHWeights[sizeof (TimePoints) ];
  UINT16 mode;
  INT32 center;
  INT32 height;
  UINT32 value0[MAX_CHANNEL];
  UINT32 BERStats[4];
  UINT32 TimScale[MAX_CHANNEL];
  INT32 centersum[MAX_CHANNEL];
  UINT32 MinHalfMargin[MAX_CHANNEL];
  UINT16 PwrLimit;
  UINT16 UPMLimit;
  UINT8 MaxMargin;
  BOOLEAN Ddr4Pda;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  marginch  = &Outputs->MarginResult;
  Status    = mrcSuccess;
  loopcount = 17;
  MaxTscale = 12;
  SumEH     = 0;
  Ddr4Pda   = TRUE;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) EHWeights, sizeof (EHWeights), 1);
  MrcCall->MrcSetMem ((UINT8 *) centersum, sizeof (centersum), 0);
  MrcCall->MrcSetMem ((UINT8 *) value0, sizeof (value0), 0);
  MrcCall->MrcSetMem ((UINT8 *) MinHalfMargin, sizeof (MinHalfMargin), 0xFF);
  TimePoints[0] = -4;
  TimePoints[1] = 4;
  TimePoints[2] = 0;
  if (Outputs->DdrType == MRC_DDR_TYPE_DDR4) {
    if (Ddr4Pda) {
      Status = MrcWriteVoltageCentering2D_DDR4 (MrcData);
      return Status;
    } else {
      MaxMargin = MAX_POSSIBLE_DDR4_WRITE_VREF;
    }
  } else {
    MaxMargin = MAX_POSSIBLE_VREF;
  }

  //
  // No input for param so set it to RdV
  //
  param = WrV;

  PwrLimit = MrcGetUpmPwrLimit (MrcData, param, PowerLimit);
  UPMLimit = MrcGetUpmPwrLimit (MrcData, param, UpmLimit);

  //
  // Assume rank0 is always popuplated
  //
  if (param == WrV) {
    paramT = WrT;
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Error Handler: Unknown Margin Parameter\n");
    Status = mrcFail;
    return Status;
  }

  ResultType  = GetMarginResultType (param);
  ResultTypeT = GetMarginResultType (paramT);

  //
  /// @todo: Need to check if we can enable it for A0 or not
  // SOE = 00b(No Stop on error), EnCADB=0, EnCKE=0
  //
  //
  /// @todo: Will enable the DQ tests instead of basic in the future
  //  SetupIOTestDQ (MrcData,Outputs->ValidChBitMask, loopcount, NSOE, 0, 0);
  //
  SetupIOTestBasicVA (MrcData, Outputs->ValidChBitMask, loopcount, NSOE, 0, 0, 8);

  //
  // Calculate SumEH for use in weighting equations
  //
  for (tim = 0; tim < sizeof (TimePoints); tim++) {
    SumEH += EHWeights[tim];
  }
  //
  // Select rank for REUT test
  //
  chBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }

    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    chBitMask |= SelectReutRanks (MrcData, Channel, ChannelOut->ValidRankBitMask, 0);

    //
    // Clear any old state in DataTrain Offset
    //
    MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
  }
  //
  // ####################################################
  // #############  Initialize EW/EH variables   ########
  // ####################################################
  //
  Status = GetMarginCh (MrcData, Outputs->MarginResult, paramT, 0xF, 0);

  //
  // Update TimScale with results
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    TimScale[Channel] = 0;
    if (!(chBitMask & (1 << Channel))) {
      continue;
    }

    TimScale[Channel] = ((*marginch) [ResultTypeT][0][Channel][0][0] + (*marginch) [ResultTypeT][0][Channel][0][1]) / 20;
    //
    // It is possible TimScale[Channel] is 0.
    //
    if (!TimScale[Channel] || (TimScale[Channel] > MaxTscale)) {
      TimScale[Channel] = MaxTscale;
    }
  }

  Status = GetMarginCh (MrcData, Outputs->MarginResult, param, 0xF, 0);

  //
  // ####################################################
  // ######   Measure Eye Height at all Timing Points  #####
  // ####################################################
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TimScale[0] is %d, TimScale[1] is %d\n", TimScale[0], TimScale[1]);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel\t0\t\t\t\t1\n");

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WrTime\tLow\tHigh\tHeight\tCenter\t");
  }

  //
  // Loop through all the Time Points to Test
  //
  for (tim = 0; tim < sizeof (TimePoints); tim++) {
    //
    // Setup Timing Offset for this point
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(chBitMask & (1 << Channel))) {
        continue;
      }

      value0[Channel] = (INT32) (TimePoints[tim] * TimScale[Channel]) / MaxTscale;

      //
      // There is no multicast per channel...
      //
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        Status = ChangeMargin (MrcData, paramT, value0[Channel], 0, 0, Channel, 0, byte, 0, 1, 0, MrcRegFileStart);
      }
    }
    //
    // Run Margin Test
    //
    mode = 0;
    Status = MrcGetBERMarginCh (
               MrcData,
               Outputs->MarginResult,
               chBitMask,
               0xFF,
               0xFF,
               param,
               mode,
               1,
               MaxMargin,
               0,
               BERStats
               );

    //
    // Store Results
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(chBitMask & (1 << Channel))) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t");
        continue;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", value0[Channel]);

      height  = ((*marginch) [ResultType][0][Channel][0][1] + (*marginch) [ResultType][0][Channel][0][0]) / 10;
      center  = (INT32) ((*marginch) [ResultType][0][Channel][0][1] - (*marginch) [ResultType][0][Channel][0][0]);
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "%d\t%d\t%d\t%d\t",
        (*marginch) [ResultType][0][Channel][0][0] / 10,
        (*marginch) [ResultType][0][Channel][0][1] / 10,
        height,
        center / 20
        );

      //
      // Calculate weight for this point
      //
      centersum[Channel] += EHWeights[tim] * center;
      //
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "+----->centersum[%d] = %d, \n", Channel, centersum[Channel]);
      //
      //
      // Determine the smallest half margin
      //
      MinHalfMargin[Channel] = MIN (MinHalfMargin[Channel], (*marginch) [ResultType][0][Channel][0][0]);
      MinHalfMargin[Channel] = MIN (MinHalfMargin[Channel], (*marginch) [ResultType][0][Channel][0][1]);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nWtdCntr\t");
  //
  // ####################################################
  // ###########   Center Results per Ch    #############
  // ####################################################
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(chBitMask & (1 << Channel))) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t");
      continue;
    }

    ChannelOut = &Outputs->Controller[0].Channel[Channel];

    //
    // Calculate CenterPoint.  Round to Nearest Int
    //
    SumEHSign           = (centersum[Channel] < 0) ? (-1) : 1;

    centersum[Channel]  = (centersum[Channel] + 10 * SumEH * SumEHSign) / (20 * SumEH);

    //
    // Apply new centerpoint
    // Only Byte 0 on Channel 0 is needed to update DIMM Vref
    // Skip if there are more channels
    //
    SkipWait = (chBitMask >> (Channel + 1));
    Status = ChangeMargin (MrcData, param, centersum[Channel], 0, 0, Channel, 0xFF, 0, 0, 1, SkipWait, MrcRegFileCurrent);

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t\t\t\t", centersum[Channel]);

    //
    // Update MrcData for future tests
    //
    (*marginch) [ResultType][0][Channel][0][0] = (INT32) ((*marginch) [ResultType][0][Channel][0][0]) + (10 * (centersum[Channel]));
    (*marginch) [ResultType][0][Channel][0][1] = (INT32) ((*marginch) [ResultType][0][Channel][0][1]) - (10 * (centersum[Channel]));

    //
    // Clean up after test
    //
    MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  //
  // Clean up
  //
  Status  = ChangeMargin (MrcData, paramT, 0, 0, 1, 0, 0, 0, 0, 1, 0, MrcRegFileCurrent);

  return Status;
}

/**
  Peform Write Voltage Centering in 2D For DDR4 PDA mode.
  Note: This function currently only supports param = WrV

  @param[in,out] MrcData     - Include all MRC global data.
  @param[in,out] MarginByte  - Pointer to Marging Results data structure
  @param[in]     ChBitMask   - Channel bit mask.
  @param[in]     RankMask    - @todo
  @param[in]     Param       - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                8:WrTBit, 9:RdTBit, 10:RdVBit,
                                16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                ONLY RdV is allowed in this function
  @param[in]     LoopCount   - Loop count
  @param[in]     En2D        - Option to only run center at nominal Vref point

  @retval MrcStatus - If it succeded return mrcSuccess
**/
MrcStatus
WriteVoltageCentering2D_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT32               MarginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8                ChBitMask,
  IN     UINT8                RankMask,
  IN     UINT8                Param,
  IN     UINT8                LoopCount,
  IN     UINT8                En2D
  )
{
  static const INT8                       TimePoints[] = { 0, -8, 8 };
  static const UINT8                      EHWeights[sizeof (TimePoints) ] = { 1, 1, 1 };
  const MrcInput                          *Inputs;
  MrcDebug                                *Debug;
  const MRC_FUNCTION                      *MrcCall;
  MrcOutput                               *Outputs;
  MrcChannelOut                           *ChannelOut;
  MrcRankOut                              *RankOut;
  MrcStatus                               Status;
  UINT8                                   ResultType;
  UINT8                                   Channel;
  UINT8                                   Byte;
  UINT8                                   Rank;
  UINT8                                   MaxRank;
  UINT8                                   lcloop;
  UINT8                                   tim;
  UINT8                                   paramT;
  UINT8                                   BMap[MAX_SDRAM_IN_DIMM];
  INT8                                    SumEH;
  INT8                                    SumEHSign;
  UINT8                                   MaxTscale;
  UINT16                                  mode;
  INT32                                   center[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                   value0[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32                                  BERStats[4];
  UINT32                                  TimScale[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                   CenterSumByte[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32                                  EyeShape[sizeof (TimePoints) ][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32                                  Low;
  UINT32                                  High;
  INT8                                    VrefValue;
  INT8                                    CurrentOff;
  UINT8                                   FirstRank;
  UINT32                                  MinWidth;
  BOOLEAN                                 EyeTooSmall[MAX_CHANNEL];

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  Status    = mrcSuccess;
  SumEH     = 0;
  MaxTscale = 12;
  MaxRank   = MAX_RANK_IN_CHANNEL;
  MinWidth  = MrcGetMinimalEyeHeight (MrcData, FALSE);
  MrcCall->MrcSetMem ((UINT8 *) EyeTooSmall, sizeof (EyeTooSmall), FALSE);
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  for (lcloop = 0; lcloop < (sizeof (BMap) / sizeof (BMap[0])); lcloop++) {
    BMap[lcloop] = lcloop;
  }
  if (Outputs->Ddr4PdaEnable == FALSE) {
    Outputs->Ddr4PdaEnable = TRUE;
  }

  //
  // Find the first selected rank
  //
  RankMask &= Outputs->ValidRankMask;
  FirstRank = 0;
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((1 << Rank) & RankMask) {
      FirstRank = Rank;  // could be in any channel
      break;
    }
  }


  //
  // Assume rank0 is always populated
  //
  if (Param == WrV) {
    paramT = WrT;
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Error Handler: Unknown Margin Parameter\n");
    Status = mrcReadVoltage2DError;
    return Status;
  }

  SetupIOTestBasicVA (MrcData, ChBitMask, LoopCount, ABGSOE, 0, 0, 8);
  //
  // Calculate SumEH for use in weighting equations
  //
  for (tim = 0; tim < sizeof (TimePoints); tim++) {
    SumEH += EHWeights[tim];

    //
    // Loop once at nominal Vref point
    //
    if (En2D == 0) {
      tim = sizeof (TimePoints);
    }
  }
  //
  // SumEH is used as divisor, make sure is never 0
  //
  if (SumEH == 0) {
    SumEH = 1;
  }
  //
  // Select rank for REUT test
  //
  ChBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    ChBitMask |= SelectReutRanks (MrcData, Channel, ChannelOut->ValidRankBitMask & RankMask, 0);
    //
    // Clear any old state in DataTrain Offset
    //
    MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
  }
  //
  // ####################################################
  // ################  Initialize EW/EH variables  ######
  // ####################################################
  //
  Status      = GetMarginByte (MrcData, Outputs->MarginResult, paramT, 0, RankMask);
  ResultType  = GetMarginResultType (paramT);

#ifdef MRC_DEBUG_PRINT
  if (En2D) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n### Measure Eye Height, per BYTE, at ALL (2D) Timing Points - RankBitMask = 0x%X\n", RankMask);
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n### Measure Eye Height, per BYTE, at NOMINAL Timing - RankBitMask = 0x%X\n", RankMask);
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (MRC_BIT0 << Channel))) {
      continue;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d", Channel);
    if (Channel == 0) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "        ");
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nByte    ");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (MRC_BIT0 << Channel))) {
      continue;
    }

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d       ", Byte);
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nTScale\t");
#endif // MRC_DEBUG_PRINT
  //
  // Update TimScale to have the appropriate eye width (read from last saved parameters)
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (MRC_BIT0 << Channel))) {
      continue;
    }

    ChannelOut = &Outputs->Controller[0].Channel[Channel];

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (En2D > 0) {
        TimScale[Channel][Byte] =
        (
          MarginByte[ResultType][0][Channel][Byte][0] +
          MarginByte[ResultType][0][Channel][Byte][1]
          ) /
        20;
      } else {
        TimScale[Channel][Byte] = 1;
      }
      //
      // It is possible sumT is 0.
      //
      if (!(TimScale[Channel][Byte]) || (TimScale[Channel][Byte] > MaxTscale)) {
        TimScale[Channel][Byte] = MaxTscale;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", TimScale[Channel][Byte]);
    }
  }

  Status      = GetMarginByte (MrcData, Outputs->MarginResult, Param, 0, RankMask);
  ResultType  = GetMarginResultType (Param);

  //
  // ####################################################
  // ######   Measure Eye Height at all Timing Points  #####
  // ####################################################
  //
  //
  // Loop through all the Time Points to Test
  //
  for (tim = 0; tim < sizeof (TimePoints); tim++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nWrTime\t");

    //
    // Setup Timing Offset for this point
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        value0[Channel][Byte] = (INT32) (TimePoints[tim] * TimScale[Channel][Byte]) / MaxTscale;
        Status = ChangeMargin (MrcData, paramT, value0[Channel][Byte], 0, 0, Channel, 0, Byte, 0, 1, 0, MrcRegFileCurrent);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", value0[Channel][Byte]);
      }
    }
    //
    // Run Margin Test
    //
    mode = 0;
    Status = MrcGetBERMarginByte (
               MrcData,
               Outputs->MarginResult,
               ChBitMask,
               RankMask,
               RankMask,
               Param,
               mode,
               BMap,
               1,
               MAX_POSSIBLE_DDR4_WRITE_VREF,
               0,
               BERStats
               );

    // condense the results to FirstRank
    GetMarginByte (MrcData, Outputs->MarginResult, Param, FirstRank, RankMask);

#ifdef MRC_DEBUG_PRINT
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nLo-Hi\t");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "%d %d\t",
          MarginByte[ResultType][FirstRank][Channel][Byte][0],
          MarginByte[ResultType][FirstRank][Channel][Byte][1]
          );
      }
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCenter\t");
#endif // MRC_DEBUG_PRINT
    //
    // Store Results
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (ChBitMask & (MRC_BIT0 << Channel)) {

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Low  = MarginByte[ResultType][FirstRank][Channel][Byte][0];
          High = MarginByte[ResultType][FirstRank][Channel][Byte][1];
          center[Channel][FirstRank][Byte] = (INT32) (High - Low);

          // See if any byte has eye height below minimum on this channel
          if ((Low + High) < (MinWidth * 10)) {
            EyeTooSmall[Channel] = TRUE;
          }

          if (tim == 0) {
            CenterSumByte[Channel][Byte] = 0;
          }
          //
          // Calculate weight for this point
          //
          CenterSumByte[Channel][Byte] += EHWeights[tim] * center[Channel][FirstRank][Byte];

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", center[Channel][FirstRank][Byte] / 20);

          //
          // Record edges for use in per bit margining
          //
          EyeShape[tim][Channel][Byte][0] = Low;
          EyeShape[tim][Channel][Byte][1] = High;
        }
      }
    }
    //
    // Loop once at nominal Vref point
    //
    if (En2D == 0) {
      tim = sizeof (TimePoints);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nWtdCntr\t");
  //
  // ####################################################
  // ###########   Center Results per Byte   ############
  // ####################################################
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (MRC_BIT0 << Channel))) {
      continue;
    }

    ChannelOut = &Outputs->Controller[0].Channel[Channel];

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      if ((1 << Rank) & RankMask) {
        RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER(Rank)].Rank[Rank % 2];
        //
        // Calculate CenterPoint.  Round to Nearest Int
        // @todo: might need to ajust because now step is 7.8mV
        //
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          SumEHSign = (CenterSumByte[Channel][Byte] < 0) ? (-1) : 1;

          CenterSumByte[Channel][Byte] = (CenterSumByte[Channel][Byte] + 10 * (SumEHSign * SumEH)) / (20 * SumEH);
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", CenterSumByte[Channel][Byte]);
          //
          // Apply new centerpoint
          // step size for Write Dimm Vref is about 7.8mv
          //
          CurrentOff = MrcVrefDqToOffset(RankOut->Ddr4PdaMr6[Byte] & 0x7F);
          VrefValue = CurrentOff + (INT8)(CenterSumByte[Channel][Byte]);
          if (VrefValue > MAX_POSSIBLE_DDR4_WRITE_VREF) {
            VrefValue = MAX_POSSIBLE_DDR4_WRITE_VREF;
          } else if (VrefValue < -MAX_POSSIBLE_DDR4_WRITE_VREF) {
            VrefValue = -MAX_POSSIBLE_DDR4_WRITE_VREF;
          }
          // update Mrc Struct and program
          RankOut->Ddr4PdaMr6[Byte] = MrcOffsetToVrefDq(MrcData, VrefValue, Channel);
          //
          // Update the Eye Edges
          //
          for (tim = 0; tim < sizeof (TimePoints); tim++) {
            EyeShape[tim][Channel][Byte][0] = (INT32)EyeShape[tim][Channel][Byte][0] + (10 * CenterSumByte[Channel][Byte]);
            EyeShape[tim][Channel][Byte][1] = (INT32)EyeShape[tim][Channel][Byte][1] - (10 * CenterSumByte[Channel][Byte]);

            //
            // Loop once at nominal Vref point
            //
            if (En2D == 0) {
              tim = sizeof (TimePoints);
            }
          }
          //
          // Update MrcData for future tests (MarginResult points back to MrcData)
          // EyeShape for Vref 0 is assumed to have the best shape for future tests.
          //
          MarginByte[ResultType][FirstRank][Channel][Byte][0] = EyeShape[0][Channel][Byte][0];
          MarginByte[ResultType][FirstRank][Channel][Byte][1] = EyeShape[0][Channel][Byte][1];
        }
        //
        // Program common center in Non PDA fashion in order to make sure the PDA is successful
        //
        UpdatePdaCenter (MrcData, 1 << Rank);
        UpdateVrefWaitTilStable (MrcData, Channel, FALSE, 0, 1 << Rank, 0, FALSE, 1); // UpdateHost = FALSE to keep per-byte MR6 values
        //
        // Write using PDA only when we have a passing window
        //
        if (!EyeTooSmall[Channel]) {
          UpdateVrefWaitTilStable (MrcData, Channel, TRUE, 0, 1 << Rank, 0x1FF, TRUE, 1);
        }
      }
    } // for Rank
    //
    // Clear up after test
    //
    MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);

    //
    // Propagate new settings from the RegFile to the Pads
    //
    MrcDownloadRegFile (MrcData, Channel, 1, 0, MrcRegFileCurrent, 0, 0, 1);
  } // for Channel

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nWrVref\t");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (MRC_BIT0 << Channel))) {
      continue;
    }
    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (FirstRank) ].Rank[FirstRank % 2];
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", MrcVrefDqToOffset (RankOut->Ddr4PdaMr6[Byte] & 0x7F));
    }
  }
  //
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nPerByte Margins after per BYTE Centering\nLo-Hi   ");
  //
#endif // MRC_DEBUG_PRINT

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  //
  // Clean up after test
  //
  Status  = ChangeMargin (MrcData, paramT, 0, 0, 1, 0, 0, 0, 0, 1, 0, MrcRegFileCurrent);
  return Status;
}

/**
  Peform Write Voltage Centering in 2D.
  Note: This function currently only supports param = WrV

  @param[in] MrcData       - Include all MRC global data.

  @retval MrcStatus       - if it succeded return mrcSuccess
**/
MrcStatus
MrcWriteVoltageCentering2D_DDR4 (
  IN     MrcParameters *const MrcData
  )
{
  MrcOutput *Outputs;
  MrcStatus Status;
  UINT8     LoopCount;
  UINT8     En2D;
  UINT8     RankMask;
  UINT8     Rank;

  Outputs   = &MrcData->Outputs;
  Status    = mrcSuccess;

  LoopCount   = 15;
  En2D        = 1;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = (0x1 << Rank) & Outputs->ValidRankMask;
    if (RankMask) {
      Status = WriteVoltageCentering2D_DDR4 (
                 MrcData,
                 Outputs->MarginResult,
                 Outputs->ValidChBitMask,
                 RankMask,
                 WrV,
                 LoopCount,
                 En2D
                 );
    }
  }
  return Status;
}

/**
  Peform Write Timing Linear Centering in different Write Vref points.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Prints        - Debug prints enable/disable

  @retval MrcStatus       - if it was successful return mrcSuccess
**/
MrcStatus
EarlyWriteTimingCentering2D (
  IN     MrcParameters *const MrcData,
  IN     BOOLEAN              Prints
  )
{
  MrcIntChannelOut  *IntChannelOut;
  MrcIntOutput      *MrcIntData;
  MrcOutput         *Outputs;
  MrcStatus         Status;
  UINT32            Offset;
  UINT8             Channel;
  UINT8             LoopCount;
  UINT8             Dimm;
  UINT8             RankMask;
  INT8              Points2DMin;
  INT8              Points2DMax;
  UINT8             StepSize;
  BOOLEAN           Ddr4;
  BOOLEAN           Lpddr3;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT TcRdRd;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Outputs   = &MrcData->Outputs;
  Lpddr3    = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  Ddr4      = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Status    =  mrcSuccess;

  Points2DMin     = -12;
  Points2DMax     = 12;
  StepSize = (MrcData->Inputs.MemoryProfile != STD_PROFILE) ? 1 : 3;
  if (!Ddr4) {
    // For Non-DDR4 step size is ~ double in TxV
    Points2DMin *= 2;
    Points2DMax *= 2;
    StepSize    *= 2;
  }

  LoopCount   = 10;

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

  for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
    RankMask = DIMM_TO_RANK_MASK (Dimm) & Outputs->ValidRankMask;
    if (RankMask) {
      Status = EarlyLinearCentering2D (
                 MrcData,
                 Outputs->ValidChBitMask,
                 RankMask,
                 WrT,
                 WrV,
                 Points2DMin,
                 Points2DMax,
                 StepSize,
                 LoopCount,
                 0, // test type - normal reads
                 Prints
                 );
    }
  }

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
  Peform Write Timing Linear Centering in different Write Vref points.

  @param[in] MrcData       - Include all MRC global data.

  @retval MrcStatus       - if it success return mrcSuccess
**/
MrcStatus
MrcEarlyWriteTimingCentering2D (
  IN     MrcParameters *const MrcData
  )
{
  return EarlyWriteTimingCentering2D (MrcData, TRUE);
}
