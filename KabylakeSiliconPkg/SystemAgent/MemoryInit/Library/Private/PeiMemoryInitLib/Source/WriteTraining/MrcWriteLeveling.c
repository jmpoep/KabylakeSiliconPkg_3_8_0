/** @file
  The write leveling flow is the first part of the write training.
  In this stage the memory controller needs to synchronize its DQS sending
  with the clock for each DRAM.  The DRAM can be put in a mode where for a
  write command it responds by sampling the clock using DQS and sending it
  back as the data.  The IO can receive this and tune the DQS alignment so
  it will appear in sync with the clock at the DRAM side.
  The following algorithm is used for the write leveling flow:

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
#include "MrcWriteLeveling.h"
#include "MrcCommandTraining.h"

/**
  This function executes post processing to reduce logical rank to rank delays.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeeds return mrcSuccess
**/
MrcStatus
MrcWriteLevelingPostProcessing (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcIntOutput        *MrcIntData;
  MrcIntChannelOut    *IntChannelOut;
  MrcStatus           Status;
  UINT32              RankSum;
  UINT32              CRAddDelay[MAX_CHANNEL];
  UINT32              ChannelAddDelay[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  INT32               ChannelDelayShift[MAX_RANK_IN_CHANNEL];
  UINT32              CurrRankValue;
  UINT32              CyclePiShift;
  UINT32              Offset;
  UINT32              Data32;
  UINT32              RankPiDifference;
  UINT32              DimmPiDifference;
  UINT32              TargetAddDelay;
  INT16               LeftDqPiReserve;
  INT16               RightDqPiReserve;
  INT16               LeftDqPiMargin;
  INT16               RightDqPiMargin;
  INT32               ShiftPI;
  INT32               ShiftCmdPI;
  INT32               NewPICode;
  UINT16              MaxCode[MAX_CHANNEL];
  UINT16              MinCode[MAX_CHANNEL];
  UINT8               OtherRank;
  UINT8               UpdateRank;
  UINT8               Channel;
  UINT8               Rank;
  UINT8               Byte;
  UINT8               RankMask;  // RankBitMask for both channels
  UINT8               Start;
  UINT8               Dimm;
  UINT8               RankMod2;
  UINT8               DelayDiffRank;
  UINT8               DelayDiffDimm;
  UINT8               StretchTurnAroundDD;
  UINT8               StretchTurnAroundDR;
  UINT8               Sign;
  UINT8               NumRanks;
  UINT8               HighRank;
  UINT8               LowRank;
  UINT8               Group;
  UINT8               RanksShifted;
  INT8                rSign;
  BOOLEAN             PiOverflow;
  BOOLEAN             PiUnderflow;
  BOOLEAN             RunDD;
  BOOLEAN             RunDR;
  BOOLEAN             Lpddr;
  BOOLEAN             Any2Dpc2667;
  MCHBAR_CH0_CR_TC_WRRD_STRUCT                                    *TcWrRd;
  MCHBAR_CH0_CR_TC_WRWR_STRUCT                                    *TcWrWr;
  MCHBAR_CH0_CR_SC_WR_ADD_DELAY_STRUCT                            ScWrAddDelay;

  Inputs              = &MrcData->Inputs;
  MrcCall             = Inputs->Call.Func;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  ControllerOut       = &Outputs->Controller[0];
  MrcIntData          = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Status              = mrcSuccess;
  MrcCall->MrcSetMem ((UINT8 *) CRAddDelay, sizeof (CRAddDelay), 0);
  MrcCall->MrcSetMem ((UINT8 *) ChannelAddDelay, sizeof (ChannelAddDelay), 0);
  Lpddr               = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  TargetAddDelay      = 0;

  if (Inputs->MemoryProfile == STD_PROFILE) {
    LeftDqPiReserve  = (Outputs->Frequency <= f2400) ? 64 : 96;
    RightDqPiReserve = (Outputs->Frequency <= f2133) ? 32 : 16;
  } else {
    LeftDqPiReserve  = 0;
    RightDqPiReserve = 0;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++ ) {
    Offset = MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG + ((MCHBAR_CH1_CR_SC_WR_ADD_DELAY_REG - MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG) * Channel);
    CRAddDelay[Channel] = MrcReadCR (MrcData, Offset);
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      ChannelAddDelay[Channel][Rank] = (CRAddDelay[Channel] >> (MCHBAR_CH0_CR_SC_WR_ADD_DELAY_D0R1_OFF * Rank)) & MCHBAR_CH0_CR_SC_WR_ADD_DELAY_D0R0_MSK;
    }
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    ChannelOut    = &ControllerOut->Channel[Channel];
    IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
    RankMask = ChannelOut->ValidRankBitMask;
    RunDD    = ChannelOut->DimmCount == 2;
    Any2Dpc2667 = RunDD && (Outputs->Frequency >= f2667);
    RunDR    = ((RankMask & 0xC) == 0xC) || ((RankMask & 0x3) == 0x3);
    TcWrRd = &IntChannelOut->MchbarTcWrRd;
    TcWrWr = &IntChannelOut->MchbarTcWrWr;

    // Initialize Rank and Dimm Difference Variables
    MrcCall->MrcSetMem ((UINT8 *) ChannelDelayShift, sizeof (ChannelDelayShift), 0);
    DelayDiffRank = 0;
    DelayDiffDimm = 0;
    RankPiDifference = 0;
    DimmPiDifference = 0;
    StretchTurnAroundDR = 0;
    StretchTurnAroundDD = 0;
    ShiftCmdPI = RanksShifted = 0;
    RankSum = 0;
    NumRanks = 0;

    if (Any2Dpc2667) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }
        // Determine the average AddDelay value across all Ranks in the Channel.
        RankSum += ChannelAddDelay[Channel][Rank];
        NumRanks++;
      }
      // For any 2DPC 2667, AddDelay should be the same across all Ranks in the Channel.
      TargetAddDelay = DIVIDEROUND (RankSum, NumRanks);
    }

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      RankMod2 = Rank % 2;
      Dimm = Rank / 2;
      CurrRankValue = ChannelAddDelay[Channel][Rank];

      if (Any2Dpc2667) {
        // Determine the difference between current AddDelay and target AddDelay
        ChannelDelayShift[Rank] = (INT32) (TargetAddDelay - CurrRankValue);
      } else {
        // Compare Rank(s) in first DIMM with all present ranks in other DIMM for the largest difference in AddDelay
        if (RunDD && (Dimm == 0)) {
          // Loop through all Ranks in other DIMM
          for (Start = 0; Start < MAX_RANK_IN_DIMM; Start++) {
            OtherRank = 2 + Start;
            if (MrcRankInChannelExist (MrcData, OtherRank, Channel)) {
              DelayDiffRank = (UINT8) ABS ((INT32) (CurrRankValue - ChannelAddDelay[Channel][OtherRank]));
              DelayDiffDimm = MAX (DelayDiffDimm, DelayDiffRank);
            }
          }
        } // If RunDD

        if (RunDR && (RankMod2 == 0)) {
          // Compare Ranks in the same DIMM for the largest difference in AddDelay
          OtherRank = Rank + 1;
          if ((!MrcRankInChannelExist (MrcData, OtherRank, Channel)) || (OtherRank == MAX_RANK_IN_CHANNEL)) {
            continue;
          }
          // Determine which rank has the larger value
          if (ChannelAddDelay[Channel][Rank] < ChannelAddDelay[Channel][OtherRank]) {
            LowRank = Rank;
            HighRank = OtherRank;
          } else if (ChannelAddDelay[Channel][Rank] > ChannelAddDelay[Channel][OtherRank]) {
            LowRank = OtherRank;
            HighRank = Rank;
          } else {
            continue;
          }
          // Determine the difference between ranks on the same DIMM
          DelayDiffRank = (UINT8) ABS ((INT32) (ChannelAddDelay[Channel][Rank] - ChannelAddDelay[Channel][OtherRank]));
          CyclePiShift = 128 * DelayDiffRank;

          // Check PI Boundaries for if we can shift the Bytes within either rank.
          // High Rank attempts to move to a lower logical cycle, shifting PIs towards the upper bound.
          // Low Rank attempts to move to a higher logical cycle, shifting PIs towards zero.
          PiOverflow = FALSE;
          PiUnderflow = FALSE;
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (PiUnderflow && PiOverflow) {
              break;
            }
            if ((INT16) (ChannelOut->TxDqs[LowRank][Byte] - CyclePiShift) < LeftDqPiReserve) {
              PiUnderflow = TRUE;
            } else if ((ChannelOut->TxDq[HighRank][Byte] + CyclePiShift + RightDqPiReserve) > DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX) {
              PiOverflow = TRUE;
            }
          }
          if (!PiOverflow) {
            UpdateRank = HighRank;
          } else if (!PiUnderflow) {
            UpdateRank = LowRank;
          } else {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, " C%d: Cannot adjust WR_ADD_DELAY between R%d and R%d by %d due to DQ PI Boundaries\n", Channel, LowRank, HighRank, DelayDiffRank);
            StretchTurnAroundDR = MAX (StretchTurnAroundDR, DelayDiffRank);
            continue;
          }
          ChannelDelayShift[UpdateRank] = (UpdateRank == LowRank) ? DelayDiffRank : (-1 * DelayDiffRank);
        } // If RunDR
      } // If Any2Dpc2667
    } // For Rank

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist(MrcData, Rank, Channel)) {
        continue;
      }
      Sign = (ChannelDelayShift[Rank] < 0) ? 1 : 0; // When Add Delay value decreases, TxDq/TxDqs PIs must increase.
      if (ChannelDelayShift[Rank] != 0) {
        CyclePiShift = 128 * ABS (ChannelDelayShift[Rank]); // Use absolute value because rSign will apply proper sign to the calculation.
        CRAddDelay[Channel] = MrcBitSwap (CRAddDelay[Channel], ChannelAddDelay[Channel][Rank] + ChannelDelayShift[Rank], Rank * 2, 2);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%d Rank%d: Adjust CRAddDelay by %d = 0x%08X\n", Channel, Rank, ChannelDelayShift[Rank], CRAddDelay[Channel]);
        //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tDqsPi\tDqPi\n");
        Offset = MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG + ((MCHBAR_CH1_CR_SC_WR_ADD_DELAY_REG - MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG) * Channel);
        ScWrAddDelay.Data = MrcReadCR (MrcData, Offset);
        ScWrAddDelay.Data &= MCHBAR_CH0_CR_SC_WR_ADD_DELAY_Dec_WRD_MSK;
        MrcWriteCR (MrcData, Offset, ScWrAddDelay.Data | CRAddDelay[Channel]);
        rSign = (INT8) ((2 * Sign) - 1);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          ChannelOut->TxDq[Rank][Byte] += (UINT16) (rSign * CyclePiShift);
          ChannelOut->TxDqs[Rank][Byte] += (UINT16) (rSign * CyclePiShift);
          UpdateTxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
          //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  B%d:\t%d\t%d\n", Byte, ChannelOut->TxDqs[Rank][Byte], ChannelOut->TxDq[Rank][Byte]);
        }
        MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 0, 1);
      }
    }


    if (DelayDiffDimm != 0) {
      StretchTurnAroundDD = DelayDiffDimm;
    }

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      RanksShifted++;

      // Find limit of TxDq, TxDqs and RcvEn PIs
      FindDqPiLimits (MrcData, Channel, (Inputs->Ddr4DdpSharedClock) ? RankMask : (MRC_BIT0 << Rank), &MinCode[Channel], &MaxCode[Channel]);

      // Determine how much we can shift CTL/CLK on this rank to center the PI. For LPDDR3, we don't shift CLK.
      ShiftPI = 0;
      LeftDqPiMargin  = MinCode[Channel];
      RightDqPiMargin = DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX - MaxCode[Channel];

      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, " C%d LeftDqPiMargin %d LeftDqPiReserve %d RightDqPiMargin %d RightDqPiReserve %d\n", Channel, LeftDqPiMargin, LeftDqPiReserve, RightDqPiMargin, RightDqPiReserve);

      if ((LeftDqPiMargin < LeftDqPiReserve) || (RightDqPiMargin < RightDqPiReserve)) {
        if ((LeftDqPiMargin < LeftDqPiReserve) && (RightDqPiMargin >= RightDqPiReserve)) {
          // Shift the minimal PI required to achieve the PI reserve without violating Other side reserve
          ShiftPI = MIN (LeftDqPiReserve - LeftDqPiMargin, RightDqPiMargin - RightDqPiReserve);
        } else if ((LeftDqPiMargin >= LeftDqPiReserve) && (RightDqPiMargin < RightDqPiReserve)) {
          // Shift the minimal PI required to achieve the PI reserve without violating Other side reserve
          ShiftPI = -MIN (LeftDqPiMargin - LeftDqPiReserve, RightDqPiReserve - RightDqPiMargin);
        } else {
          // ((LeftDqPiMargin < LeftDqPiReserve) && (RightDqPiMargin < RightDqPiReserve))
          ShiftPI = ((LeftDqPiReserve - LeftDqPiMargin) - (RightDqPiReserve - RightDqPiMargin)) / 2;
        }

        // LPDDR3 Clk is per group
        if (!Lpddr) {
          if (Inputs->Ddr4DdpSharedClock) {
            if (Rank == 0) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "Ch%d: Shifting CLK by %d Pis\n", Channel, ShiftPI);
              // Shift DQ on both rank 0 and rank 1
              ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock,  3, 3, ShiftPI, 1);
            }
          } else {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "Ch%d Rank%d: Shitfting CLK by %d Pis\n", Channel, Rank, ShiftPI);
            ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock,  (1 << Rank), (1 << Rank), ShiftPI, 1);
          }
        }

        NewPICode = ShiftPI + ChannelOut->CtlPiCode[Rank];
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl,  (MRC_BIT0 << Rank), 1, NewPICode, 1);

        // Track all shifts for this channel
        ShiftCmdPI = ShiftCmdPI + ShiftPI;
      }
    } // for Rank

    //
    // Shift the CMD Timing
    //
    if (ShiftCmdPI != 0) {

      // Shift by average of every Rank in this Channel
      ShiftCmdPI = ShiftCmdPI / RanksShifted;

      NewPICode = ShiftCmdPI + ChannelOut->CmdsCmdPiCode[0];
      // Shift Cmd PI by the average of all ranks
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "Ch%d: New CMDS[0] value = %d\n", Channel, NewPICode);
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS,  ChannelOut->ValidRankBitMask, 1, NewPICode, 1);

      if (Lpddr) {
        //
        // CLK is per Group in LPDDR3
        //
        for (Group = 0; Group < 2; Group++) {
          if (Inputs->Controller[0].Channel[Channel].DQByteMap[MrcIterationClock][Group] != 0) {
            ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, 0, 1 << Group, ShiftCmdPI, 1);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "     New CLK%d    value = %d\n", Group, ChannelOut->ClkPiCode[Group]);
          }
        }

        NewPICode = ChannelOut->CkeCmdPiCode[0] + ShiftCmdPI;
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCke, ChannelOut->ValidRankBitMask, 1, NewPICode, 1);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "     New CKE[0]  value = %d\n", NewPICode);

        NewPICode = ChannelOut->CmdsCmdPiCode[1] + ShiftCmdPI;
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, ChannelOut->ValidRankBitMask, 2, NewPICode, 1);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "     New CMDS[1] value = %d\n", NewPICode);

        NewPICode = ChannelOut->CmdnCmdPiCode[1] + ShiftCmdPI;
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdN, ChannelOut->ValidRankBitMask, 2, NewPICode, 1);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "     New CMDN[1] value = %d\n", NewPICode);
      } else {
        NewPICode = ChannelOut->CmdnCmdPiCode[0] + ShiftCmdPI;
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdN, ChannelOut->ValidRankBitMask, 1, NewPICode, 1);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "     New CMDN[0] value = %d\n", NewPICode);
      }
    }

    // Check for differences between Ranks for TxDq/TxDqs PIs which are greater than 64
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      RankMod2 = Rank % 2;
      Dimm = Rank / 2;

      if (RunDD && (Dimm == 0)) {
        // Loop through all Ranks in other DIMM
        for (Start = 0; Start < MAX_RANK_IN_DIMM; Start++) {
          OtherRank = 2 + Start;
          if (MrcRankInChannelExist (MrcData, OtherRank, Channel)) {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              Data32 = ABS ((INT32) (ChannelOut->TxDq[Rank][Byte] - ChannelOut->TxDq[OtherRank][Byte]));
              DimmPiDifference = MAX (DimmPiDifference, Data32);
              Data32 = ABS ((INT32) (ChannelOut->TxDqs[Rank][Byte] - ChannelOut->TxDqs[OtherRank][Byte]));
              DimmPiDifference = MAX (DimmPiDifference, Data32);
            }
          }
        }
      } // If RunDD

      if (RunDR && (RankMod2 == 0)) {
        OtherRank = Rank + 1;
        if ((!MrcRankInChannelExist (MrcData, OtherRank, Channel)) || (OtherRank == MAX_RANK_IN_CHANNEL)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Data32 = ABS ((INT32) (ChannelOut->TxDq[Rank][Byte] - ChannelOut->TxDq[OtherRank][Byte]));
          RankPiDifference = MAX (RankPiDifference, Data32);
          Data32 = ABS ((INT32) (ChannelOut->TxDqs[Rank][Byte] - ChannelOut->TxDqs[OtherRank][Byte]));
          RankPiDifference = MAX (RankPiDifference, Data32);
        }
      } // If RunDR
    } // For Rank

    if (RankPiDifference > 64) {
      StretchTurnAroundDR += 1;
    }
    if (DimmPiDifference > 64) {
      StretchTurnAroundDD += 1;
    }

    // Use maximum Delay Difference between DIMMs and apply to TAT.
    if (StretchTurnAroundDD != 0) {
      TcWrRd->Bits.tWRRD_dd += StretchTurnAroundDD;
      TcWrWr->Bits.tWRWR_dd += StretchTurnAroundDD;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%d: Different Dimm TAT Adjustment = %d\n", Channel, StretchTurnAroundDD);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tWr2Rd = %d\n", TcWrRd->Bits.tWRRD_dd);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tWr2Wr = %d\n", TcWrWr->Bits.tWRWR_dd);
    }
    if (StretchTurnAroundDR != 0) {
      TcWrRd->Bits.tWRRD_dr += StretchTurnAroundDR;
      TcWrWr->Bits.tWRWR_dr += StretchTurnAroundDR;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%d: Different Rank TAT Adjustment = %d\n", Channel, StretchTurnAroundDR);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tWr2Rd = %d\n", TcWrRd->Bits.tWRRD_dr);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tWr2Wr = %d\n", TcWrWr->Bits.tWRWR_dr);
    }

    if ((StretchTurnAroundDD != 0) || (StretchTurnAroundDR != 0)) {
      Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_TC_WRWR_REG, MCHBAR_CH1_CR_TC_WRWR_REG, Channel);
      MrcWriteCR (MrcData, Offset, TcWrWr->Data);
      Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_TC_WRRD_REG, MCHBAR_CH1_CR_TC_WRRD_REG, Channel);
      MrcWriteCR (MrcData, Offset, TcWrRd->Data);
    }
  } // For Channel


  // print updated values
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n--- Final Pi Values ---\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++ ) {
    ChannelOut = &ControllerOut->Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d.R%d:\tDqsPi\tDqPi\tRcvEn\n", Channel, Rank);

      // Print the updated PI values
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  B%d:\t%d\t%d\t%d\n", Byte, ChannelOut->TxDqs[Rank][Byte], ChannelOut->TxDq[Rank][Byte], ChannelOut->RcvEn[Rank][Byte]);
      }
    }
  }
  // end debug print

  return mrcSuccess;
}

/**
  this function execute the Jedec write leveling Cleanup.
  Center TxDQS-CLK timing

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeded return mrcSuccess
**/
MrcStatus
MrcJedecWriteLevelingCleanUp (
  IN OUT MrcParameters *const MrcData
  )
{
  static const MRC_REUTAddress REUTAddress = {{0, 0, 0, 0},    // Start
                                              {0, 0, 0, 1023}, // Stop
                                              {0, 0, 0, 0},    // Order
                                              {0, 0, 0, 0},    // IncRate
                                              {0, 0, 0, 1}};   // IncValue
  static const UINT8  DumArr[7] = {1, 1, 1, 1, 1, 1, 1};
  static const UINT8  DqOffsetMax = 7;
  static const INT8   DqOffsets[7] = {-15, -10, -5, 0, 5, 10, 15};
  static const UINT8  PMaskConst[8] = {0, 0, 1, 1, 1, 1, 0, 0};
  static const UINT32 CleanUpSeeds[MRC_WDB_NUM_MUX_SEEDS] = {0xAAAAAA, 0xCCCCCC, 0xF0F0F0};
  static const UINT32 NormalSeeds[MRC_WDB_NUM_MUX_SEEDS] = {0xA10CA1, 0xEF0D08, 0xAD0A1E};
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcIntOutput        *MrcIntData;
  MrcIntChannelOut    *IntChannelOut;
  MrcStatus           Status;
  UINT8               Channel;
  UINT8               Rank;
  UINT8               Byte;
  UINT8               ChBitMask;
  UINT8               RankMask;  // RankBitMask for both channels
  UINT8               ValidRankMask;
  UINT8               Pattern[4][2];
  UINT8               PMask[sizeof (PMaskConst) ];
  UINT8               AllGoodLoops;
  UINT8               DqOffset;
  UINT8               RankDouble;
  UINT8               RankHalf;
  UINT8               RankMod2;
  UINT8               Start;
  INT16               ByteOff[MAX_CHANNEL][MAX_SDRAM_IN_DIMM]; // Passing offset for each ch/byte.
  INT16               ByteSum[MAX_CHANNEL]; // Sum of passing offsets for a ch
  INT16               TargetOffset;
  INT16               StartOffset[MAX_CHANNEL];
  INT16               EndOffset[MAX_CHANNEL];
  INT16               LeftDqPiReserve;
  INT16               RightDqPiReserve;
  INT16               StartOffsetCommon;
  INT16               EndOffsetCommon;
  INT16               CurrentOffset;
  UINT16              ByteMask;
  UINT16              ValidByteMask;
  UINT16              Result;
  UINT16              SkipMe;
  UINT16              BytePass[MAX_CHANNEL]; // Bit mask indicating which ch/byte has passed
  UINT16              MaxCode[MAX_CHANNEL];
  UINT16              MinCode[MAX_CHANNEL];
  UINT16              TxDqValue;
  UINT16              TxDqsValue;
  INT16               GlobalByteOff;
  UINT32              CRValue;
  UINT32              Offset;
  UINT32              CRAddDelay[MAX_CHANNEL];
  UINT32              CurrRankValue;
  INT32               DqPiDelta;
  INT32               CurrentPiDelta;
  INT32               LocalPiDelta;
  INT32               LocalOffset;
  INT32               TargetDqPi;
  INT32               TargetDqsPi;
  INT32               MinPi;
  INT32               MaxPi;
  BOOLEAN             Done;
  BOOLEAN             Lpddr;
  BOOLEAN             PiOverflow;
  BOOLEAN             RerunCleanup;
  MRC_WDBPattern      WDBPattern;

  MCHBAR_CH0_CR_TC_WRWR_STRUCT                                    TcWrWr;
  MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_STRUCT                 ReutChPatWdbClMuxCfg;
  DDRDATA0CH0_CR_TXTRAINRANK0_STRUCT                              CrTxTrainRank;
  MCHBAR_CH0_CR_SC_WR_ADD_DELAY_STRUCT                            ScWrAddDelay;
#ifdef MRC_DEBUG_PRINT
  UINT32            ErrLower[MAX_CHANNEL];
  UINT32            ErrUpper[MAX_CHANNEL];
#endif // MRC_DEBUG_PRINT

  //
  // Setup REUT Pattern
  // Use 0x00FFC33C pattern to keep DQ-DQS simple but detect any failures
  // Same Pattern as NHM/WSM
  //
  Inputs              = &MrcData->Inputs;
  MrcCall             = Inputs->Call.Func;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  ControllerOut       = &Outputs->Controller[0];
  MrcIntData          = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Status              = mrcSuccess;
  LocalOffset         = 0;
  Done                = TRUE;
  PiOverflow          = FALSE;
  Pattern[0][0]       = 0x00;
  Pattern[0][1]       = 0xFF;
  Pattern[1][0]       = 0xFF;
  Pattern[1][1]       = 0x00;
  Pattern[2][0]       = 0xC3;
  Pattern[2][1]       = 0x3C;
  Pattern[3][0]       = 0x3C;
  Pattern[3][1]       = 0xC3;
  WDBPattern.IncRate  = 1;
  WDBPattern.Start    = 0;
  WDBPattern.Stop     = 3;
  WDBPattern.DQPat    = BasicVA;
  MrcCall->MrcCopyMem (PMask, (UINT8 *) PMaskConst, sizeof (PMask));
  MrcCall->MrcSetMem ((UINT8 *) CRAddDelay, sizeof (CRAddDelay), 0);
  MrcCall->MrcSetMem ((UINT8 *) StartOffset, sizeof (StartOffset), 0);
  MrcCall->MrcSetMem ((UINT8 *) EndOffset, sizeof (EndOffset), 0);
#ifdef MRC_DEBUG_PRINT
  MrcCall->MrcSetMem ((UINT8 *) ErrLower, sizeof (ErrLower), 0);
  MrcCall->MrcSetMem ((UINT8 *) ErrUpper, sizeof (ErrUpper), 0);
#endif // MRC_DEBUG_PRINT

  if (Inputs->MemoryProfile == STD_PROFILE) {
    LeftDqPiReserve  = (Outputs->Frequency <= f2400) ? 64 : 96;
    RightDqPiReserve = (Outputs->Frequency <= f2133) ? 32 : 16;
  } else {
    LeftDqPiReserve  = 0;
    RightDqPiReserve = 0;
  }

  //
  // Check if LPDDR3 memory is used
  //
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);

  //
  // Set LSFR Seed to be sequential
  //
  MrcProgramLFSR (MrcData, &CleanUpSeeds[0], 0, MRC_WDB_NUM_MUX_SEEDS);

  //
  // Set Channel and Rank bit masks
  //
  ChBitMask     = Outputs->ValidChBitMask;
  ValidRankMask = Outputs->ValidRankMask;
  ValidByteMask = (MRC_BIT0 << Outputs->SdramCount) - 1; // 0x1FF or 0xFF
  //
  // Setip IO test CmdPat=PatWrRd, NumCL=4, LC=4, REUTAddress, SOE=3,
  // WDBPattern, EnCADB=0, EnCKE=0, SubSeqWait=0 )
  //
  SetupIOTest (MrcData, ChBitMask, PatWrRd, 2, 4, &REUTAddress, NSOE, &WDBPattern, 0, 0, 0);

  //
  // Progam BITBUFFER for JWLT
  //
  ReutChPatWdbClMuxCfg.Data                     = 0;
  ReutChPatWdbClMuxCfg.Bits.Mux0_Control        = BTBUFFER;
  ReutChPatWdbClMuxCfg.Bits.Mux1_Control        = BTBUFFER;
  ReutChPatWdbClMuxCfg.Bits.Mux2_Control        = BTBUFFER;
  ReutChPatWdbClMuxCfg.Bits.ECC_Data_Source_Sel = 1;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      Offset = MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_REG +
        ((MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_REG) * Channel);
      MrcWriteCR (MrcData, Offset, ReutChPatWdbClMuxCfg.Data);

      //
      // Increase the same rank WRWR turnaround to avoid delayed data overlap with the expected data of the next write.
      //
      IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
      TcWrWr.Data = IntChannelOut->MchbarTcWrWr.Data;
      TcWrWr.Bits.tWRWR_sg = 30;
      TcWrWr.Bits.tWRWR_dg = 30;
      Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_TC_WRWR_REG, MCHBAR_CH1_CR_TC_WRWR_REG, Channel);
      MrcWriteCR (MrcData, Offset, TcWrWr.Data);
    }
  }

  RerunCleanup = FALSE;
  do {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      //
      // Select Rank for REUT test
      //
      ChBitMask   = 0;
      RankMask    = MRC_BIT0 << Rank;
      RankDouble  = Rank * 2;
      RankHalf    = Rank / 2;
      RankMod2    = Rank % 2;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChBitMask |= SelectReutRanks (MrcData, Channel, (RankMask), 0);
        BytePass[Channel] = ByteSum[Channel] = 0;
      }
      //
      // Skip if both channels empty
      //
      if (!(RankMask & ValidRankMask)) {
        continue;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRank %d\n", Rank);

      //
      // *************************************************
      // Sweep through the cycle offsets until we find a value that passes
      // *************************************************
      //
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Sweep through the cycle offsets until we find a value that passes\n");

      //
      // Find the minimum and maximum PI setting across Tx DQ/DQS on a given Rank, per channel.
      // Min value will use DQS, Max value will use DQ (DQ is DQS + 32).
      //
      StartOffsetCommon = 0;
      EndOffsetCommon   = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }
        MaxCode[Channel] = 0;
        MinCode[Channel] = DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX;
        ChannelOut = &Outputs->Controller[0].Channel[Channel];
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          TxDqValue = ChannelOut->TxDq[Rank][Byte];
          MaxCode[Channel] = MAX (MaxCode[Channel], TxDqValue);

          TxDqsValue = ChannelOut->TxDqs[Rank][Byte];
          MinCode[Channel] = MIN (MinCode[Channel], TxDqsValue);
        }
        StartOffset[Channel] = -MinCode[Channel] / 128;  // We can go to negative offsets only using PI settings
        EndOffset[Channel]   = MAX_ADD_DELAY + (DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX - MaxCode[Channel]) / 128;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d: MinCode: %d, MaxCode: %d, Start: %d, End: %d\n", Channel, MinCode[Channel], MaxCode[Channel], StartOffset[Channel], EndOffset[Channel]);
        //
        // Find the common sweep range for both channels - superset of both ranges
        //
        StartOffsetCommon = MIN (StartOffsetCommon, StartOffset[Channel]);
        EndOffsetCommon   = MAX (EndOffsetCommon, EndOffset[Channel]);
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Total range: Start: %d, End: %d\n", StartOffsetCommon, EndOffsetCommon);

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel                 0                1\nDelay  DqOffset   Byte \t");
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "%s 8 %s 8" : "%s %s", "0 1 2 3 4 5 6 7", "0 1 2 3 4 5 6 7");

      for (CurrentOffset = StartOffsetCommon; CurrentOffset <= EndOffsetCommon; CurrentOffset++) {
        //
        // Program new delay offsets to DQ/DQS timing:
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
            continue;
          }
          if ((CurrentOffset < StartOffset[Channel]) || (CurrentOffset > EndOffset[Channel])) {
            continue;
          }
          ChannelOut = &ControllerOut->Channel[Channel];

          //
          // Calculate offsets
          //
          GlobalByteOff = 0;
          if (CurrentOffset > MAX_ADD_DELAY) {
            CRAddDelay[Channel] = MrcBitSwap (CRAddDelay[Channel], MAX_ADD_DELAY, RankDouble, 2);
            GlobalByteOff       = 128 * (CurrentOffset - MAX_ADD_DELAY);
          } else if (CurrentOffset < 0) {
            CRAddDelay[Channel] = MrcBitSwap (CRAddDelay[Channel], 0, RankDouble, 2);
            GlobalByteOff       = 128 * CurrentOffset;
          } else {
            CRAddDelay[Channel] = MrcBitSwap (CRAddDelay[Channel], CurrentOffset, RankDouble, 2);
          }
          //
          // Write Tx DQ/DQS Flyby delays
          // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Add GlobalByteOff = %d to TxDQS Flyby delay: Ch %d \n", GlobalByteOff, Channel);
          //
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            CRValue                       = ChannelOut->TxDqs[Rank][Byte] + GlobalByteOff;
            CrTxTrainRank.Data            = 0;
            CrTxTrainRank.Bits.TxDqDelay  = CRValue + 32;
            CrTxTrainRank.Bits.TxDqsDelay = CRValue;
            CrTxTrainRank.Bits.TxEqualization = ChannelOut->TxEq[Rank][Byte];
            UpdateTxTValues (MrcData, Channel, Rank, Byte, 0x3, CrTxTrainRank.Data);
          }
          //
          // Download new Write settings from the RegFile to the Pads, using broadcast to all bytes in the channel
          //
          MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 0, 1);

          //
          // Write Wr ADD Delays
          // Read the Dec_Wrd state and set all other to 0's
          //
          Offset = MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG + ((MCHBAR_CH1_CR_SC_WR_ADD_DELAY_REG - MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG) * Channel);
          ScWrAddDelay.Data = MrcReadCR (MrcData, Offset);
          ScWrAddDelay.Data &= MCHBAR_CH0_CR_SC_WR_ADD_DELAY_Dec_WRD_MSK;
          MrcWriteCR (MrcData, Offset, ScWrAddDelay.Data | CRAddDelay[Channel]);
          //
          /// @todo - Address debuging switches or remove.
          // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CRAddDelay[%d] = 0x%x \n", Channel, CRAddDelay[Channel]);
          //
        } // for Channel

        if (!Lpddr) {
          //
          // Reset FIFOs & Reset DRAM DLL. Wait 1uS for test to complete
          //
          Status = IoReset (MrcData);

          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
              continue;
            }
            if ((CurrentOffset < StartOffset[Channel]) || (CurrentOffset > EndOffset[Channel])) {
              continue;
            }
            ChannelOut = &ControllerOut->Channel[Channel];
            Status = MrcWriteMRS (
                        MrcData,
                        Channel,
                        RankMask,
                        mrMR0,
                        ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR0] | (MRC_BIT0 << 8)
                        );
          }
          MrcWait (MrcData, (1 * HPET_1US));
        }

        //
        // Run Test across all DqOffsets points
        //
        for (DqOffset = 0; DqOffset < DqOffsetMax; DqOffset++) {
          //
          // Update Offset
          //
          ChangeMargin (MrcData, WrT, DqOffsets[DqOffset], 0, 1, 0, Rank, 0, 0, 0, 0, MrcRegFileRank);
          //
          // Spread = 8, Start = 0, 1, 2 and 3
          // Program the WDB pattern; then change the pattern for the next test, to avoid false PASS issues.
          //
          for (Start = 0; Start < (sizeof (Pattern) / sizeof (Pattern[0])); Start++) {
            WriteWDBFixedPattern (MrcData, Pattern[Start], PMask, 8, Start);
            Pattern[Start][0] = ~Pattern[Start][0];
            Pattern[Start][1] = ~Pattern[Start][1];
          }
          //
          // Run Test
          // DQPat = BasicVA, DumArr, ClearErrors = 1, mode = 0
          //
          RunIOTest (MrcData, ChBitMask, BasicVA, DumArr, 1, 0);
          //
          // Update results for all ch/bytes
          //
          Done = TRUE;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 3d\t% 3d\t       \t", CurrentOffset, DqOffsets[DqOffset]);
          //
          // Update results for all ch/bytes
          //
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!(MrcRankInChannelExist (MrcData, Rank, Channel)) ||
                 ((CurrentOffset < StartOffset[Channel]) || (CurrentOffset > EndOffset[Channel]))
               ) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "%s " : "%s", "                ");
              continue;
            }

            //
            // Read out per byte error results and check for any byte error
            //
            Offset = 4 + MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG +
            (
              (
                MCHBAR_CH1_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG -
                MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG
                ) * Channel
              );
            Result = (UINT16) MrcReadCR (MrcData, Offset);
            SkipMe = (Result & ValidByteMask) | BytePass[Channel];

#ifdef MRC_DEBUG_PRINT
            Offset = MCHBAR_CH0_CR_REUT_CH_ERR_DATA_STATUS_REG + ((MCHBAR_CH1_CR_REUT_CH_ERR_DATA_STATUS_REG - MCHBAR_CH0_CR_REUT_CH_ERR_DATA_STATUS_REG) * Channel);
            ErrLower[Channel] = MrcReadCR (MrcData, Offset);
            ErrUpper[Channel] = MrcReadCR (MrcData, Offset + 4);
#endif // MRC_DEBUG_PRINT
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              ByteMask = MRC_BIT0 << Byte;
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                ((Result & ValidByteMask) & ByteMask) ?
                "# " : //Fail
                ". " // Pass
                );
              //
              // If this byte has failed or previously passed, nothing to do
              //
              if (SkipMe & ByteMask) {
                continue;
              }

              BytePass[Channel] |= ByteMask;
              ByteOff[Channel][Byte] = CurrentOffset;
              ByteSum[Channel] += CurrentOffset;
            }
            //
            /// @todo - Address debuging switches or remove.
            // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "For DqOffsets %d: BytePass[%d] = 0x%X, Result = 0x%x, SkipMe = 0x%x\n", DqOffsets[DqOffset], Channel, BytePass[Channel], Result, SkipMe);
            //
            if (BytePass[Channel] != ValidByteMask) {
              Done = FALSE;
            }
          } // for Channel

#ifdef MRC_DEBUG_PRINT
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!(MrcRankInChannelExist (MrcData, Rank, Channel)) ||
                 ((CurrentOffset < StartOffset[Channel]) || (CurrentOffset > EndOffset[Channel]))
               ) {
              if (Channel == 0) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "                   ");
              }
              continue;
            }
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "0x%08x%08x ", ErrUpper[Channel], ErrLower[Channel]);
          }
#endif // MRC_DEBUG_PRINT
          //
          // Jump out of the for DqOffset loop if everybody is passing
          //
#ifdef MRC_DEBUG_PRINT
          if ((Done == TRUE) && (DqOffset >= DqOffsetMax)) {
#else
          if (Done == TRUE) {
#endif // MRC_DEBUG_PRINT
            break;
          }
        } // for DqOffset
        //
        // Jump out of the for offset loop if everybody is passing
        //
        if (Done == TRUE) {
          break;
        }
      } // for offset

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");

      //
      // Walk through and find the correct value for each ch/byte
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }

        ChannelOut = &ControllerOut->Channel[Channel];

        if (BytePass[Channel] != ValidByteMask) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_ERROR,
            "Error! Write Leveling CleanUp - Couldn't find a passing value for all bytes on Channel %u Rank %u:\nBytes - ",
            Channel,
            Rank
            );
#ifdef MRC_DEBUG_PRINT
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, ((BytePass[Channel] ^ ValidByteMask) & (1 << Byte)) ? "%d " : "", Byte);
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");
#endif
          continue;
        }
        //
        // Calculate the average offset, rounding up
        // Apply that offset to the global MC CRAddDelay register
        //
        TargetOffset = DIVIDEROUND (ByteSum[Channel], Outputs->SdramCount);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TargetOffset: %d, ByteSum[%d]: %d\n", TargetOffset, Channel, ByteSum[Channel]);

        Done = FALSE;
        DqPiDelta = 0;
        GlobalByteOff = 0;

        for (AllGoodLoops = 0; (AllGoodLoops < MAX_EDGES) && !Done; AllGoodLoops++) {
          //
          // Update CRAddDelay and GlobalByteOff
          //
          GlobalByteOff = 0;
          CurrentPiDelta = 0;
          if (TargetOffset > MAX_ADD_DELAY) {
            CRAddDelay[Channel] = MrcBitSwap (CRAddDelay[Channel], MAX_ADD_DELAY, RankDouble, 2);
            GlobalByteOff       = 128 * (TargetOffset - MAX_ADD_DELAY);
          } else if (TargetOffset < 0) {
            CRAddDelay[Channel] = MrcBitSwap (CRAddDelay[Channel], 0, RankDouble, 2);
            GlobalByteOff       = 128 * TargetOffset;
          } else {
            CRAddDelay[Channel] = MrcBitSwap (CRAddDelay[Channel], TargetOffset, RankDouble, 2);
          }
          //
          // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GlobalByteOff: %d, CRAddDelay[%d]: 0x%x\n", GlobalByteOff, Channel, CRAddDelay[Channel]);
          // Refine TargetOffset to make sure it works for all byte lanes
          //
          Done = TRUE;
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            LocalOffset = GlobalByteOff + 128 * (ByteOff[Channel][Byte] - TargetOffset);
            //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "B%u: TxDq: %d, LocalOffset: %d, TxDq+LocalOffset: %d\n", Byte, ChannelOut->TxDq[Rank][Byte], LocalOffset, ChannelOut->TxDq[Rank][Byte] + LocalOffset);
            TargetDqPi = ChannelOut->TxDq[Rank][Byte] + LocalOffset;
            TargetDqsPi = ChannelOut->TxDqs[Rank][Byte]+ LocalOffset;
            MinPi = MIN (TargetDqsPi, TargetDqPi);
            MaxPi = MAX (TargetDqsPi, TargetDqPi);
            if (MaxPi > (DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX - RightDqPiReserve)) {
              Done = FALSE;
              LocalPiDelta = MaxPi - (DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX - RightDqPiReserve);
              CurrentPiDelta = MAX (LocalPiDelta, CurrentPiDelta);
              PiOverflow = TRUE;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "CH%d CurrentPiDelta = %d\n", Channel, CurrentPiDelta);
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "B%u: TxDq too big: Requested %d, Limit %d\n", Byte, TargetDqPi, (DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX - RightDqPiReserve));
            }

            if (MinPi < LeftDqPiReserve) {
              Done = FALSE;
              LocalPiDelta = LeftDqPiReserve - MinPi;
              CurrentPiDelta = MAX (LocalPiDelta, CurrentPiDelta);
              PiOverflow = FALSE;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "CH%d CurrentPiDelta = %d\n", Channel, CurrentPiDelta);
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "B%u: TxDqs too small: Requested %d, Limit %d\n", Byte, TargetDqsPi, LeftDqPiReserve);
            }
            //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TargetOffset = 0x%x, ByteOff[%d][%d] = 0x%x \n", TargetOffset, Channel, Byte, ByteOff[Channel][Byte]);
          }

          if (!Done) {
            if (DqPiDelta == 0) {
              DqPiDelta = CurrentPiDelta;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DqPiDelta = %d\n", DqPiDelta);
            } else {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DqPiDelta(%d) < CurrentPiDelta(%d)\n", DqPiDelta, CurrentPiDelta);
              if (DqPiDelta > CurrentPiDelta) {
                break;
              }
            }
            if (PiOverflow) {
              TargetOffset += 1;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH%d Increasing TargetOffset to %d\n", Channel, TargetOffset);
            } else {
              TargetOffset -= 1;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH%d Decreasing TargetOffset to %d\n", Channel, TargetOffset);
            }
            if (TargetOffset > MAX_ADD_DELAY) {
              CRAddDelay[Channel] = MrcBitSwap (CRAddDelay[Channel], MAX_ADD_DELAY, RankDouble, 2);
            } else if (TargetOffset < 0) {
              CRAddDelay[Channel] = MrcBitSwap (CRAddDelay[Channel], 0, RankDouble, 2);
            } else {
              CRAddDelay[Channel] = MrcBitSwap (CRAddDelay[Channel], TargetOffset, RankDouble, 2);
            }
          }
        } // while AllGood

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d.R%d:\tOffset\tDqsPi\tDqPi\n", Channel, Rank);
        //
        // Program the final settings to the DQ bytes and update MrcData
        //
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          LocalOffset = GlobalByteOff + 128 * (ByteOff[Channel][Byte] - TargetOffset);
          ChannelOut->TxDq[Rank][Byte]  += (INT16) LocalOffset;
          ChannelOut->TxDqs[Rank][Byte] += (INT16) LocalOffset;
          UpdateTxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  B%d:\t%d\t%d\t%d\n", Byte, LocalOffset, ChannelOut->TxDqs[Rank][Byte], ChannelOut->TxDq[Rank][Byte]);
        }
        //
        // Download new Write settings from the RegFile to the Pads, using broadcast to all bytes in the channel
        //
        MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 0, 1);
        //
        // Update MC Delay
        //
        Offset = MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG + ((MCHBAR_CH1_CR_SC_WR_ADD_DELAY_REG - MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG) * Channel);
        ScWrAddDelay.Data = MrcReadCR (MrcData, Offset);
        ScWrAddDelay.Data &= MCHBAR_CH0_CR_SC_WR_ADD_DELAY_Dec_WRD_MSK;
        MrcWriteCR (MrcData, Offset, ScWrAddDelay.Data | CRAddDelay[Channel]);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CRAddDelay[%d] = 0x%08X \n", Channel, CRAddDelay[Channel]);

        if (!Lpddr) {
          //
          // Clean up after Test
          //
          Status = MrcWriteMRS (
                     MrcData,
                     Channel,
                     RankMask,
                     mrMR0,
                     ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR0] | (MRC_BIT0 << 8)
                     );
          MrcWait (MrcData, (1 * HPET_1US));
        }
      } // for Channel

      RerunCleanup = FALSE;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }
        if (BytePass[Channel] != ValidByteMask) { // This channel has failing byte(s)
          Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG, MCHBAR_CH1_CR_SC_WR_ADD_DELAY_REG, Channel);
          ScWrAddDelay.Data = MrcReadCR (MrcData, Offset);
          if (ScWrAddDelay.Bits.Dec_WRD == 1) {
            ScWrAddDelay.Bits.Dec_WRD = 0;
            MrcWriteCR (MrcData, Offset, ScWrAddDelay.Data);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d: set Dec_WRD = 0 and rerun Cleanup\n", Channel);
            RerunCleanup = TRUE;
          } else { // Dec_WRD already zero, nothing else we can do
            return mrcWriteLevelingError;
          }
        }
      }
      if (RerunCleanup) {
        break;
      }
    } // for Rank
  } while (RerunCleanup);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++ ) {
    ChannelOut = &ControllerOut->Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }

      MinCode[Channel] = DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX;
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MinCode[Channel] = MIN (MinCode[Channel], ChannelOut->TxDq[Rank][Byte]);  // Find the Min DQ PI setting
      }

      if (MinCode[Channel] < 128) {
        CurrRankValue = (CRAddDelay[Channel] >> (MCHBAR_CH0_CR_SC_WR_ADD_DELAY_D0R1_OFF * Rank)) & MCHBAR_CH0_CR_SC_WR_ADD_DELAY_D0R0_MSK;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, " CurrRankValue: 0x%x\n", CurrRankValue);
        if (CurrRankValue > 0) {
          //
          // Check that we have enough PI range on the upper side, keep 32 ticks for RMT
          //
          PiOverflow = FALSE;
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if ((ChannelOut->TxDq[Rank][Byte] + 128) > (DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX - RightDqPiReserve)) {
              PiOverflow = TRUE;
              break;
            }
          }
          if (PiOverflow) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, " C%d R%d B%d: cannot reduce WR_ADD_DELAY by 1 due to DQ PI overflow\n", Channel, Rank, Byte);
          } else {
            CRAddDelay[Channel] = MrcBitSwap (CRAddDelay[Channel], (CurrRankValue - 1), Rank * 2, 2);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%d Rank%d: Reduce CRAddDelay by 1 = 0x%08X\n\tDqsPi\tDqPi\n", Channel, Rank, CRAddDelay[Channel]);
            Offset = MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG + ((MCHBAR_CH1_CR_SC_WR_ADD_DELAY_REG - MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG) * Channel);
            ScWrAddDelay.Data = MrcReadCR (MrcData, Offset);
            ScWrAddDelay.Data &= MCHBAR_CH0_CR_SC_WR_ADD_DELAY_Dec_WRD_MSK;
            MrcWriteCR (MrcData, Offset, ScWrAddDelay.Data | CRAddDelay[Channel]);
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              ChannelOut->TxDq[Rank][Byte]  += 128;
              ChannelOut->TxDqs[Rank][Byte] += 128;
              UpdateTxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  B%d:\t%d\t%d\n", Byte, ChannelOut->TxDqs[Rank][Byte], ChannelOut->TxDq[Rank][Byte]);
            }
            MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 0, 1);
          }
        } else {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, " C%d R%d: WR_ADD_DELAY is already zero, cannot reduce by 1\n", Channel, Rank);
        }
      }
    } // for Rank
  } // for Channel

  //
  // Clean up after Test
  // Restore WDB - VicRot=8, Start=0 and restore default seed
  //
  WriteWDBVAPattern (MrcData, 0, BASIC_VA_PATTERN_SPRED_8, 8, 0);
  MrcProgramLFSR (MrcData, &NormalSeeds[0], 0, MRC_WDB_NUM_MUX_SEEDS);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      //
      // Restore the same rank WRWR turnaround
      //
      IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
      Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_TC_WRWR_REG, MCHBAR_CH1_CR_TC_WRWR_REG, Channel);
      MrcWriteCR (MrcData, Offset, IntChannelOut->MchbarTcWrWr.Data);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nJedec Write Leveling POST PROCESSING\n");
  Status = MrcWriteLevelingPostProcessing (MrcData);

  MrcWriteCrMulticast (MrcData, MrcGetOffsetDataOffsetTrain (MrcData, 0xFF, 0xFF), 0);
  Status = MrcResetSequence (MrcData);

  return Status;
}

/**
  this function execute the Jedec write leveling training.
  Center TxDQS-CLK timing

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succedes return mrcSuccess
**/
MrcStatus
MrcJedecWriteLevelingTraining (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcIntOutput      *MrcIntData;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcIntControllerOut *IntControllerOut;
  MrcIntChannelOut  *IntChannelOut;
  TOdtValue         *OdtTableIndex;
  MrcStatus         Status;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             RankDouble;
  UINT8             RankHalf;
  UINT8             RankMod2;
  UINT8             Byte;
  UINT8             refbyte;
  UINT8             ChBitMask;
  UINT8             RankMask;  // RankBitMask for both channels
  UINT8             ValidRankMask;
  UINT8             OtherDimm;
  UINT8             OdtMatrix;
  UINT8             RttNom;
  UINT16            WLStart;
  UINT16            WLStop;
  UINT16            WLDelay;
  UINT8             WLStep;
  UINT32            WaitTime;
  UINT32            CRValue;
  UINT32            Offset;
  UINT32            DqsToggleTime;
  INT32             InitialPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             InitialPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             CurrentPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             CurrentPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             LargestPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             LargestPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             iWidth;
  INT32             cWidth;
  INT32             lWidth;
  INT32             ByteWidth;
  BOOLEAN           Pass;
  BOOLEAN           RankIsx16;
  BOOLEAN           SavedRestoreMRS;
  BOOLEAN           Lpddr;
#if (SUPPORT_DDR4 == SUPPORT)
    BOOLEAN           Ddr4;
  UINT8             RttWrite;
  TOdtValueDdr4     *Ddr4OdtTableIndex;
  DDR4_MODE_REGISTER_1_STRUCT                Ddr4ModeRegister1;
  DDR4_MODE_REGISTER_5_STRUCT                Ddr4ModeRegister5;
#endif // SUPPORT_DDR4

  DDR3_MODE_REGISTER_1_STRUCT                 Ddr3ModeRegister1;
  DDRDATA0CH0_CR_DDRCRDATACONTROL2_STRUCT     DdrCrDataControl2;
  MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_STRUCT  ReutChMiscOdtCtrl;
  DDRDATA0CH0_CR_DDRCRDATACONTROL0_STRUCT     DdrCrData0Control0;
  DDRDATA0CH0_CR_DATATRAINFEEDBACK_STRUCT     DataTrainFeedback;
  DDRSCRAM_CR_DDRMISCCONTROL0_STRUCT          DdrMiscControl0;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT                TcRdRd;

  Inputs           = &MrcData->Inputs;
  Outputs          = &MrcData->Outputs;
  ControllerOut    = &Outputs->Controller[0];
  MrcIntData       = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntControllerOut = &MrcIntData->Controller[0];
  Debug            = &Outputs->Debug;
  Status           = mrcSuccess;
  OdtTableIndex    = NULL;
  CRValue          = 0;
  ChBitMask        = Outputs->ValidChBitMask;
  ValidRankMask    = Outputs->ValidRankMask;

  // Save the flag and force MRS recalculation
  SavedRestoreMRS = Outputs->RestoreMRs;
  Outputs->RestoreMRs = FALSE;

  DqsToggleTime = 1024;
  //
  // Check if LPDDR3 memory is used
  //
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);

  if (Lpddr) {
    DqsToggleTime = 2048;
  }
#if (SUPPORT_DDR4 == SUPPORT)
  //
  // Check if DDR4 memory is used
  //
    Ddr4  = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  if (Ddr4 && Outputs->Frequency > f1333) {
    DqsToggleTime = 2048;
  }
#endif // SUPPORT_DDR4

  //
  // Enabling WLmode causes DQS to toggle for 1024 qclk.  Wait for this to stop
  // Round up to nearest uS
  //

  WaitTime = (Outputs->Qclkps * DqsToggleTime + 999999) / 1000000;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      IntChannelOut = &IntControllerOut->Channel[Channel];
      //
      // Set ForceBiasOn and make sure ForceRxAmpOn is cleared
      //
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        DdrCrDataControl2.Data              = IntChannelOut->DqControl2[Byte].Data;
        DdrCrDataControl2.Bits.ForceBiasOn  = 1;
        DdrCrDataControl2.Bits.ForceRxOn    = 0;
        if (Lpddr) {
          DdrCrDataControl2.Bits.WlLongDelEn  = 1;
        }
#if (SUPPORT_DDR4 == SUPPORT)
          if (Ddr4 && Outputs->Frequency > f1333) {
          DdrCrDataControl2.Bits.WlLongDelEn  = 1;
        }
#endif // SUPPORT_DDR4
        Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
        MrcWriteCR (MrcData, Offset, DdrCrDataControl2.Data);
      }
    }
  }

  DdrMiscControl0.Data = IntControllerOut->MiscControl0.Data;
  DdrMiscControl0.Bits.DataClkGateDisAtIdle = 1;
  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL0_REG, DdrMiscControl0.Data);

  //
  // DDR3/4: Set Qoff bit in MR1 on all ranks
  //
  if (!Lpddr) {
    if (Ddr4) {
      MrcSetMR1_DDR4 (MrcData, 1, DDR4_ODIC_34, 0, 0, 1);
    } else { // DDR3
      MrcSetMR1 (MrcData, 0, DIMMRON, 0, 0, 0, 1);
    }
  }

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = MRC_BIT0 << Rank;
    if (!(RankMask & ValidRankMask)) {
      //
      // Skip if all channels empty
      //
      continue;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRank %d\n", Rank);
    RankDouble  = Rank * 2;
    RankHalf    = Rank / 2;
    RankMod2    = Rank % 2;
    //
    // Program MR1: Set A7 to enter Write Leveling mode, and clear A12 (Qoff).
    // Write MaskRasWe to prevent scheduler from issuing non-Read commands
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {

        ChannelOut = &ControllerOut->Channel[Channel];

        //
        // Enable WL mode in MR2[7]
        //
        if (Lpddr) {
          CRValue = (ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR2]);
          Status  = MrcIssueMrw (MrcData, Channel, Rank, mrMR2, (CRValue | MRC_BIT7), FALSE, FALSE, FALSE);
        } else
#if (SUPPORT_DDR4 == SUPPORT)
          if (Ddr4) {
          Ddr4OdtTableIndex = GetOdtTableIndex (MrcData, Channel, RankHalf);
          if (Ddr4OdtTableIndex == NULL) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: OdtTableIndex is NULL!\n");
            return mrcFail;
          }
          if (Ddr4OdtTableIndex->RttWr == 0xFF) { // High-Z
            RttWrite = 0;
          } else {
            RttWrite = Ddr4OdtTableIndex->RttWr;
          }

          Ddr4ModeRegister5.Data = ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR5];
          Ddr4ModeRegister5 = UpdateRttParkValue_DDR4 (MrcData, RttWrite, Ddr4ModeRegister5);
          Status = MrcWriteMRS (MrcData, Channel, RankMask, mrMR5, (UINT16) Ddr4ModeRegister5.Data);

          Ddr4ModeRegister1.Data = ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR1];
          Ddr4ModeRegister1.Bits.WriteLeveling = 1;
          Ddr4ModeRegister1.Bits.Qoff          = 0;
          Status = MrcWriteMRS (MrcData, Channel, RankMask, mrMR1, (UINT16) Ddr4ModeRegister1.Data);
        } else
#endif // SUPPORT_DDR4
        {
          Ddr3ModeRegister1.Data = ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR1];
          Ddr3ModeRegister1.Bits.WriteLeveling = 1;
          Ddr3ModeRegister1.Bits.Qoff          = 0;

          OdtTableIndex = GetOdtTableIndex (MrcData, Channel, RANK_TO_DIMM_NUMBER (Rank));
          if (OdtTableIndex == NULL) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: OdtTableIndex is NULL!\n");
            return mrcFail;
          }
          //        if (!Inputs->Ddr3DramOdt) {  // DDR3L case // TODO check for SKL
          //
          // During JEDEC Write Leveling only RttNom of 120, 60 and 40 Ohms are allowed.
          // TODO: Maybe just use 120 Ohm, regardless of specific board RttWr/RttNom ?
          //
          RttNom = OdtTableIndex->RttWr;
          if ((RttNom != 120) && (RttNom != 60) && (RttNom != 40)) {
            RttNom = 120;
          }
          Ddr3ModeRegister1 = UpdateRttNomValue (MrcData, RttNom, Ddr3ModeRegister1);
          //        }

          //
          // In write leveling mode Rtt_Nom = Rtt_Wr ONLY for 2DPC
          //
          if (ChannelOut->DimmCount == 2) {
            Ddr3ModeRegister1 = UpdateRttNomValue (MrcData, OdtTableIndex->RttWr, Ddr3ModeRegister1);
          }
          Status = MrcWriteMRS (MrcData, Channel, RankMask, mrMR1, (UINT16) Ddr3ModeRegister1.Data);
        }

        //
        // Assert ODT for myself
        //
        OdtMatrix = RankMask;
        if (ChannelOut->DimmCount == 2) {
          //
          // Calculate non-target DIMM
          //
          OtherDimm = ((Rank + 2) / 2) & MRC_BIT0;
          //
          // Assert ODT for non-target DIMM
          //
          OdtMatrix |= 1 << (2 * OtherDimm);
        }

        ReutChMiscOdtCtrl.Data = 0;
        if (Lpddr) {
          //
          // Only one ODT pin for ULT
          //
          ReutChMiscOdtCtrl.Bits.ODT_On       = 1;
          ReutChMiscOdtCtrl.Bits.ODT_Override = 1;
        } else {
          ReutChMiscOdtCtrl.Bits.ODT_On       = OdtMatrix;
          ReutChMiscOdtCtrl.Bits.ODT_Override = MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_MAX;
        }

#if (SUPPORT_DDR4 == SUPPORT)
          if (!Ddr4) {
#endif // SUPPORT_DDR4
          Offset = MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG +
            ((MCHBAR_CH1_CR_REUT_CH_MISC_ODT_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG) * Channel);
          MrcWriteCR (MrcData, Offset, ReutChMiscOdtCtrl.Data);
#if (SUPPORT_DDR4 == SUPPORT)
          }
#endif // SUPPORT_DDR4
      }
    }  // for Channel

    //
    // ******************************************
    // STEP 1 and 2: Find middle of high region
    // ******************************************
    // We will add 64 ticks at the end, so shift the range left by 64.
    //
    WLStart = 192 - 64;
    WLStop  = 192 - 64 + 128;
    WLStep  = 2;


    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "\n\tCh0\t\t\t\t\t\t\t\t%sCh1\n",
      (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "\t" : ""
      );

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "WLDelay%s%s",
      (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "\t0\t1\t2\t3\t4\t5\t6\t7\t8" : "\t0\t1\t2\t3\t4\t5\t6\t7",
      (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "\t0\t1\t2\t3\t4\t5\t6\t7\t8" : "\t0\t1\t2\t3\t4\t5\t6\t7"
      );

    for (WLDelay = WLStart; WLDelay < WLStop; WLDelay += WLStep) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n %d:", WLDelay);
      //
      // Program WL DQS Delays:
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          IntChannelOut = &IntControllerOut->Channel[Channel];

          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            UpdateTxTValues (MrcData, Channel, Rank, Byte, 1, WLDelay);
          }
          //
          // Enable Write Level Mode in DDR and Propagate delay values (without a write command).
          // Stay in WLMode.
          //
          DdrCrData0Control0.Data                 = IntChannelOut->DqControl0.Data;
          DdrCrData0Control0.Bits.WLTrainingMode  = 1;
          DdrCrData0Control0.Bits.TxPiOn          = 1;
          DdrCrData0Control0.Bits.ReadRFRd        = 0;
          DdrCrData0Control0.Bits.ReadRFWr        = 1;
          DdrCrData0Control0.Bits.ReadRFRank      = Rank;
          Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
          MrcWriteCR (MrcData, Offset, DdrCrData0Control0.Data);
        }
      }

      if (WLDelay == WLStart) {
        MrcWait (MrcData, (WaitTime * HPET_1US));  // Wait for the first burst to finish
      }

      Status = IoReset (MrcData);

      MrcWait (MrcData, (WaitTime * HPET_1US));

      //
      // Update results for all Channels/Bytes
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "\t\t\t\t\t\t\t\t%s",
            (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "\t" : ""
            );
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
          DataTrainFeedback.Data  = MrcReadCR (MrcData, Offset);
          Pass                    = (DataTrainFeedback.Bits.DataTrainFeedback >= 16);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%c%d", Pass ? '.' : '#', DataTrainFeedback.Data);
          if (WLDelay == WLStart) {
            if (Pass) {
              InitialPassingStart[Channel][Byte] = InitialPassingEnd[Channel][Byte]  = WLStart;
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte]  = WLStart;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte]  = WLStart;
            } else {
              InitialPassingStart[Channel][Byte] = InitialPassingEnd[Channel][Byte]  = -WLStep;
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte]  = -WLStep;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte]  = -WLStep;
            }
          } else {
            if (Pass) {
              if (InitialPassingEnd[Channel][Byte] == (WLDelay - WLStep)) {
                InitialPassingEnd[Channel][Byte] = WLDelay;
              }

              if (CurrentPassingEnd[Channel][Byte] == (WLDelay - WLStep)) {
                CurrentPassingEnd[Channel][Byte] = WLDelay;
              } else {
                CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte] = WLDelay;
              }
              //
              // Special case for last step: Append Initial Passing Region
              // WLDelay should be considered a continuous range that wraps around 0
              //
              if ((WLDelay >= (WLStop - WLStep)) && (InitialPassingStart[Channel][Byte] == WLStart)) {
                iWidth = (InitialPassingEnd[Channel][Byte] - InitialPassingStart[Channel][Byte]);
                CurrentPassingEnd[Channel][Byte] += (WLStep + iWidth);
              }
              //
              // Update Largest variables
              //
              cWidth  = CurrentPassingEnd[Channel][Byte] - CurrentPassingStart[Channel][Byte];
              lWidth  = LargestPassingEnd[Channel][Byte] - LargestPassingStart[Channel][Byte];
              if (cWidth > lWidth) {
                LargestPassingStart[Channel][Byte]  = CurrentPassingStart[Channel][Byte];
                LargestPassingEnd[Channel][Byte]    = CurrentPassingEnd[Channel][Byte];
              }
            }
          }
        } // for Byte
      } // for Channel
    } // for WLDelay

#ifdef MRC_DEBUG_PRINT
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\tInitPassSt\tInitPassEn\tCurrPassSt\tCurrPassEn\tLargPassSt\tLargPassEn\n");

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d\n", Channel);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "   B%d:\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            Byte,
            InitialPassingStart[Channel][Byte],
            InitialPassingEnd[Channel][Byte],
            CurrentPassingStart[Channel][Byte],
            CurrentPassingEnd[Channel][Byte],
            LargestPassingStart[Channel][Byte],
            LargestPassingEnd[Channel][Byte]
            );
        }
      }
    }
#endif // MRC_DEBUG_PRINT

    //
    // Clean up after step
    // Very coarsely adjust for any cycle errors
    // Program values for TxDQS
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {

        ChannelOut = &ControllerOut->Channel[Channel];

        //
        // Check if rank is a x16
        //
        RankIsx16 = (ChannelOut->Dimm[RankHalf].SdramWidth == 16 ? TRUE : FALSE);

        //
        // Clear ODT before MRS (JEDEC Spec)
        //
        Offset = MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG +
          ((MCHBAR_CH1_CR_REUT_CH_MISC_ODT_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG) * Channel);
        MrcWriteCR (MrcData, Offset, 0);

        //
        // Restore MR2 values
        //
        if (Lpddr) {
          CRValue = (ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR2]);
          Status  = MrcIssueMrw (MrcData, Channel, Rank, mrMR2, CRValue, FALSE, FALSE, FALSE);
        } else {
          //
          // Restore Write Leveling mode and Rtt_Nom for this rank, set Qoff.
          //
          Ddr3ModeRegister1.Data = (ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR1]);
          Ddr3ModeRegister1.Bits.Qoff = 1;
          Status  = MrcWriteMRS (MrcData, Channel, RankMask, mrMR1, (UINT16) Ddr3ModeRegister1.Data);
        }
#if (SUPPORT_DDR4 == SUPPORT)
          if (Ddr4) {
          //
          // Restore RTT_PARK for this rank
          //
          Ddr4ModeRegister5.Data = ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR5];
          Status = MrcWriteMRS (MrcData, Channel, RankMask, mrMR5, (UINT16) Ddr4ModeRegister5.Data);
        }
#endif // SUPPORT_DDR4

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d.R%d:  LftEdge Width\n", Channel, Rank);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          ByteWidth = LargestPassingEnd[Channel][Byte] - LargestPassingStart[Channel][Byte];
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "  B%d:   %d\t%d\n",
            Byte,
            LargestPassingStart[Channel][Byte],
            ByteWidth
            );

          //
          // Check if width is valid
          //
          if ((ByteWidth <= 32) || (ByteWidth >= 96)) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_ERROR,
              "\nERROR! Width region outside expected limits for Channel: %u Rank %u Byte: %u\n",
              Channel,
              Rank,
              Byte
              );
            if (Inputs->ExitOnFailure) {
              return mrcWriteLevelingError;
            }
          }
          //
          // Align byte pairs if DIMM is x16
          //
          if (RankIsx16 && (Byte & MRC_BIT0)) {
            //
            // If odd byte number (1, 3, 5 or 7)
            //
            refbyte = Byte - 1;
            if (LargestPassingStart[Channel][Byte] > (LargestPassingStart[Channel][refbyte] + 64)) {
              LargestPassingStart[Channel][Byte] -= 128;
            }

            if (LargestPassingStart[Channel][Byte] < (LargestPassingStart[Channel][refbyte] - 64)) {
              LargestPassingStart[Channel][Byte] += 128;
            }
          }

          //
          // Add 1 QCLK to DqsPi
          //
          LargestPassingStart[Channel][Byte] += 64;

          ChannelOut->TxDqs[Rank][Byte] = (UINT16) LargestPassingStart[Channel][Byte];
          ChannelOut->TxDq[Rank][Byte]  = (UINT16) (LargestPassingStart[Channel][Byte] + 32);
          UpdateTxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
        } // for Byte
#ifdef MRC_DEBUG_PRINT
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u.R%u:\tDqsPi\tDqPi\n", Channel, Rank);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "  B%d:\t%u\t%u\n",
            Byte,
            ChannelOut->TxDqs[Rank][Byte],
            ChannelOut->TxDq[Rank][Byte]
            );
        }
#endif
        //
        // Download new Write settings from the RegFile to the Pads, using broadcast to all bytes in the channel
        //
        MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 0, 1);
      }
    } // for Channel

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      IntChannelOut = &IntControllerOut->Channel[Channel];
      //
      // Restore DataControl0
      //
      Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
      MrcWriteCrMulticast (MrcData, Offset, IntChannelOut->DqControl0.Data);
    }
    Status = IoReset (MrcData);
  } // for Rank
  //
  // Clean up after Test
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {

      IntChannelOut = &IntControllerOut->Channel[Channel];

      Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
      MrcWriteCrMulticast (MrcData, Offset, IntChannelOut->DqControl0.Data);

      //
      // Restore DqControl2 values.
      //
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
        MrcWriteCR (MrcData, Offset, IntChannelOut->DqControl2[Byte].Data);
      }
    }
  }

  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL0_REG, IntControllerOut->MiscControl0.Data);

  if (!Lpddr) {
#if (SUPPORT_DDR4 == SUPPORT)
      if (Ddr4) {
      //
      // DLLEnable=1, Dic=0, Al=0, Level=0, Tdqs=0, Qoff=0
      //
      MrcSetMR1_DDR4 (MrcData, 1, DDR4_ODIC_34, 0, 0, 0);
    } else
#endif // SUPPORT_DDR4
    {
      //
      // DLLEnable=0, Dic=0, Al=0, Level=0, Tdqs=0, Qoff=0
      //
      MrcSetMR1 (MrcData, 0, DIMMRON, 0, 0, 0, 0);
    }
  }

  // Restore flag
  Outputs->RestoreMRs = SavedRestoreMRS;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nJedec Write Leveling CLEANUP\n");

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist(Outputs, Channel)) {
      // Increase the same rank RDRD turnaround to avoid delayed data overlap.
      IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
      TcRdRd.Data = IntChannelOut->MchbarTcRdRd.Data;
      TcRdRd.Bits.tRDRD_sg += 8;
      TcRdRd.Bits.tRDRD_dg += 8;
      Offset = OFFSET_CALC_CH(MCHBAR_CH0_CR_TC_RDRD_REG, MCHBAR_CH1_CR_TC_RDRD_REG, Channel);
      MrcWriteCR(MrcData, Offset, TcRdRd.Data);
    }
  }

  Status = MrcJedecWriteLevelingCleanUp (MrcData);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist(Outputs, Channel)) {
      // Restore the same rank RDRD turnaround
      IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
      Offset = OFFSET_CALC_CH(MCHBAR_CH0_CR_TC_RDRD_REG, MCHBAR_CH1_CR_TC_RDRD_REG, Channel);
      MrcWriteCR(MrcData, Offset, IntChannelOut->MchbarTcRdRd.Data);
    }
  }

  return Status;
}

