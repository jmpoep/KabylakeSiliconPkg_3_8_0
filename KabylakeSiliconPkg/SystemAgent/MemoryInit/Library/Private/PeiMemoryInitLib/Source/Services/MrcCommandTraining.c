/** @file
  Implementation of the command training algorithms.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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
#include "MrcCommandTraining.h"

#define MRC_CADB_PB_LENGTH 24

/**
  This function performs early command training.
  Center CTL-CLK timing to allow subsequent steps to work

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus -  mrcSuccess if it succeeded
**/
MrcStatus
MrcEarlyCommandTraining (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput                              *Inputs;
  MrcDebug                                    *Debug;
  const MRC_FUNCTION                          *MrcCall;
  MrcIntOutput                                *MrcIntData;
  MrcOutput                                   *Outputs;
  MrcControllerOut                            *ControllerOut;
  MrcChannelOut                               *ChannelOut;
  MrcIntControllerOut                         *IntControllerOut;
  MrcIntChannelOut                            *IntChannelOut;
  INT32                                       *IPStart;
  INT32                                       *IPEnd;
  INT32                                       *CPStart;
  INT32                                       *CPEnd;
  INT32                                       *LPStart;
  INT32                                       *LPEnd;
  MrcStatus                                   Status;
  BOOLEAN                                     Pass;
  BOOLEAN                                     Done;
  DDRCLK_CR_DDRCRCLKPICODE_STRUCT             DdrCrClkPiCode;
  MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_STRUCT  ReutChMiscOdtCtrl;
  MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_STRUCT     ReutGlobalCtl;
  DDRDATA0CH0_CR_DDRCRDATACONTROL0_STRUCT     DdrCrDataControl0;
  DDRDATA0CH0_CR_DDRCRDATACONTROL2_STRUCT     DdrCrDataControl2;
  UINT32                                      CRValue;
  INT32                                       cWidth;
  INT32                                       lWidth;
  INT32                                       InitialPassingStart[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  INT32                                       InitialPassingEnd[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  INT32                                       CurrentPassingStart[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  INT32                                       CurrentPassingEnd[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  INT32                                       LargestPassingStart[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  INT32                                       LargestPassingEnd[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  UINT32                                      DqsDoneMask;
  UINT32                                      bytePass[MAX_CHANNEL];
  UINT32                                      byteFail[MAX_CHANNEL];
  UINT32                                      Offset;
  UINT8                                       Channel;
  UINT8                                       Rank;
  UINT8                                       byte;
  UINT8                                       chBitMask;
  UINT8                                       RankMask;
  UINT8                                       ValidRankMask;
  UINT8                                       clkDelay;
  UINT8                                       clkDelayArray;
  UINT8                                       PiCode;
  INT8                                        DqsDelay;
  INT8                                        LastDqsRan[ECT_CLK_LOOPS][MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  MrcDdrType                                  DdrType;

  MrcIntData       = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs           = &MrcData->Inputs;
  MrcCall          = Inputs->Call.Func;
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  ControllerOut    = &Outputs->Controller[0];
  IntControllerOut = &MrcIntData->Controller[0];

  MrcCall->MrcSetMem ((UINT8 *) LastDqsRan, sizeof (LastDqsRan), ECT_DQS_STOP);

  //
  // RankBitMask for both channels
  //
  ValidRankMask = Outputs->ValidRankMask;
  //
  // Channel bit mask
  //
  chBitMask = Outputs->ValidChBitMask;
  DdrType   = Outputs->DdrType;

  //
  // Check if LPDDR3 memory is used
  //
  if (DdrType == MRC_DDR_TYPE_LPDDR3) {
    return EarlyCommandTrainingLpddr (MrcData);
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];

      //
      // Set DQS Delay to 32
      //
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if ((MrcRankInChannelExist (MrcData, Rank, Channel)) && (Inputs->SetRxDqs32 == TRUE)) {
            //
            // Update RxDqsP & RxDqsN - leave other parameter the same; can we update in the next loop or do it per channel
            //
            UpdateRxT (MrcData, Channel, Rank, byte, 5, 32);
          }
        }
      }
      //
      // Clear any old state in DataTrain Offset
      //
      MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
    }
  }
  //
  // Setup REUT Engine
  // LC = 10, SOE = 0 (NSOE), EnCADB = 0, EnCKE = 0
  //
  SetupIOTestMPR (MrcData, chBitMask, 10, NSOE, 0, 0);

  //
  // Set LoopCount to 0 - Infinite
  //
  MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_0_REG, 0);
  MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_1_REG, 0);

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nChannel\t");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%u\t\t\t\t", Channel);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRank\t");

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%u", Rank);
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nClock");
#endif // MRC_DEBUG_PRINT
  for (clkDelay = ECT_CLK_START; clkDelay < ECT_CLK_STOP; clkDelay += ECT_CLK_STEP) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 5u\t", clkDelay);
    clkDelayArray = clkDelay / ECT_CLK_STEP;
    //
    // Program Clock Delays
    //
    DdrCrClkPiCode.Data = 0;
    DdrCrClkPiCode.Bits.PiSettingRank0 =
      DdrCrClkPiCode.Bits.PiSettingRank1 =
        DdrCrClkPiCode.Bits.PiSettingRank2 =
          DdrCrClkPiCode.Bits.PiSettingRank3 = clkDelay;
    MrcWriteCrMulticast (MrcData, DDRCLK_CR_DDRCRCLKPICODE_REG, DdrCrClkPiCode.Data);

    //
    // Reset FIFOs and Reset all DIMM/all channels after changing PI codes
    //
    Status = MrcResetSequence (MrcData);

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      RankMask = MRC_BIT0 << Rank;
      //
      // Skip ranks that are not populated
      //
      if ((ValidRankMask & RankMask) == 0) {
        continue;
      }
      //
      // Program MR3 and Mask RAS/WE to prevent scheduler from issuing non-Read commands
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        SelectReutRanks (MrcData, Channel, RankMask, 0);
        bytePass[Channel] = 0;
        byteFail[Channel] = 0;
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          Status = MrcWriteMRS (MrcData, Channel, RankMask, mrMR3, 4);

          Offset = MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG +
            ((MCHBAR_CH1_CR_REUT_CH_MISC_ODT_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG) * Channel);
          ReutChMiscOdtCtrl.Data                  = MrcReadCR (MrcData, Offset);
          ReutChMiscOdtCtrl.Bits.MPR_Train_DDR_On = 1;
          MrcWriteCR (MrcData, Offset, ReutChMiscOdtCtrl.Data);
        }
      }
      //
      // Run ReadDQS Test
      //
      DqsDoneMask = (MRC_BIT0 << Outputs->SdramCount) - 1;
      //
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRank %u DqsDelay for clkDelay = %u", Rank, clkDelay);
      //
      for (DqsDelay = ECT_DQS_START; DqsDelay < ECT_DQS_STOP; DqsDelay += ECT_DQS_STEP) {
        //
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n %d\t", DqsDelay);
        //
        // Write DqsDelay
        //
        Status = ChangeMargin (MrcData, RdT, DqsDelay, 0, 1, 0, 0, 0, 0, 0, 0, MrcRegFileStart);

        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
            /*MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              (Channel != 0) ? "" : ((Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ?
              "                  " : "                ")
              );*/
          } else {
            IntChannelOut = &IntControllerOut->Channel[Channel];

            for (byte = 0; byte < Outputs->SdramCount; byte++) {
              //
              // Force on SenseAmp
              //
              Offset = MrcGetOffsetDataControl2 (MrcData, Channel, byte);
              DdrCrDataControl2.Data             = IntChannelOut->DqControl2[byte].Data;
              DdrCrDataControl2.Bits.ForceBiasOn = DDRDATA0CH0_CR_DDRCRDATACONTROL2_ForceBiasOn_MAX;
              DdrCrDataControl2.Bits.ForceRxOn   = DDRDATA0CH0_CR_DDRCRDATACONTROL2_ForceRxOn_MAX;
              MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl2.Data);
            }
            //
            // Enable RX Training mode.  Turn on Odt
            //
            Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
            DdrCrDataControl0.Data                = IntChannelOut->DqControl0.Data;
            DdrCrDataControl0.Bits.ForceOdtOn     = DDRDATACH0_CR_DDRCRDATACONTROL0_ForceOdtOn_MAX;
            DdrCrDataControl0.Bits.RxTrainingMode = DDRDATACH0_CR_DDRCRDATACONTROL0_RxTrainingMode_MAX;
            MrcWriteCR (MrcData, Offset, DdrCrDataControl0.Data);
          }
        }
        //
        // Clear Results for Prior Test and wait to obtain results
        //
        Status = IoReset (MrcData);

        //
        // Start REUT and run for 1uS
        //
        ReutGlobalCtl.Data                     = 0;
        ReutGlobalCtl.Bits.Global_Clear_Errors = 1;
        ReutGlobalCtl.Bits.Global_Start_Test   = 1;
        MrcWriteCR (MrcData, MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG, ReutGlobalCtl.Data);

        //
        // Wait for test to start clearing errors.
        //
        MrcWait (MrcData, START_TEST_DELAY);

        //
        // Clear Results for Prior Test and wait to obtain results
        //
        Status = IoReset (MrcData);
        MrcWait (MrcData, IO_RESET_DELAY);

        //
        // Stop REUT
        //
        ReutGlobalCtl.Data                  = 0;
        ReutGlobalCtl.Bits.Global_Stop_Test = 1;
        MrcWriteCR (MrcData, MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG, ReutGlobalCtl.Data);

        //
        // Get Results for all ch/bytes
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            for (byte = 0; byte < Outputs->SdramCount; byte++) {
              Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, byte);
              Pass = (MrcReadCR (MrcData, Offset) == 1);
              //
              // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, Pass ? ". " : "# ");
              //
              CRValue = (MRC_BIT0 << byte);
              if (Pass) {
                bytePass[Channel] |= CRValue;
              } else {
                byteFail[Channel] |= CRValue;
              }
            }
            //
            // Save DqsDelay where all bytes passed
            //
            if ((bytePass[Channel] == DqsDoneMask) && (LastDqsRan[clkDelayArray][Channel][Rank] == ECT_DQS_STOP)) {
              LastDqsRan[clkDelayArray][Channel][Rank] = DqsDelay;
            }
          }
        }

        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            IntChannelOut = &IntControllerOut->Channel[Channel];
            for (byte = 0; byte < Outputs->SdramCount; byte++) {
              //
              // Restore orginal value
              //
              Offset = MrcGetOffsetDataControl2 (MrcData, Channel, byte);
              MrcWriteCR (MrcData, Offset, IntChannelOut->DqControl2[byte].Data);
            }

            Status = IoReset (MrcData);

            //
            // Clear RX Mode
            //
            Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
            MrcWriteCrMulticast (MrcData, Offset, IntChannelOut->DqControl0.Data);
          }
        }
        //
        // Are We done yet?
        //
        Done = TRUE;
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            if ((bytePass[Channel] != DqsDoneMask) // || (byteFail[Channel] != DqsDoneMask)
                ) {
              Done = FALSE;
              break;
            }
          }
        }
        //
        // If we re done, we passed or failed for all bytes
        //
        if (Done == TRUE) {
          break;
        }
      }
      //
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
      //
      // Update results for all channel at this rank
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          Pass = ((bytePass[Channel] == DqsDoneMask) //&& (byteFail[Channel] == DqsDoneMask)
                  );

          //
          // Check if we have a valid pass
          //
          if (Pass &&
              (clkDelay != ECT_CLK_START) &&
              ((LastDqsRan[clkDelayArray][Channel][Rank] - LastDqsRan[clkDelayArray - 1][Channel][Rank]) > 16)
              ) {
            Pass = FALSE;
          }

          IPStart = &InitialPassingStart[Channel][Rank];
          IPEnd   = &InitialPassingEnd[Channel][Rank];
          CPStart = &CurrentPassingStart[Channel][Rank];
          CPEnd   = &CurrentPassingEnd[Channel][Rank];
          LPStart = &LargestPassingStart[Channel][Rank];
          LPEnd   = &LargestPassingEnd[Channel][Rank];
          if (clkDelay == ECT_CLK_START) {
            if (Pass) {
              *IPStart = clkDelay;
              *IPEnd   = clkDelay;
              *CPStart = clkDelay;
              *CPEnd   = clkDelay;
              *LPStart = clkDelay;
              *LPEnd   = clkDelay;
            } else {
              *IPStart = -ECT_CLK_STEP;
              *IPEnd   = -ECT_CLK_STEP;
              *CPStart = -ECT_CLK_STEP;
              *CPEnd   = -ECT_CLK_STEP;
              *LPStart = -ECT_CLK_STEP;
              *LPEnd   = -ECT_CLK_STEP;
            }
          } else {
            if (Pass) {
              //
              // Update Initial variables
              //
              if (*IPEnd == clkDelay - ECT_CLK_STEP) {
                *IPEnd = clkDelay;          // In passing region
              }
              //
              // Update Current variables
              //
              if (*CPEnd == clkDelay - ECT_CLK_STEP) {
                *CPEnd = clkDelay;          // In passing region
              } else {
                *CPStart = clkDelay;        // New region
                *CPEnd = clkDelay;
              }
              //
              // Special case for last step: Append Initial Passing Region
              // clkDelay should be considered a continuous range that wraps around 0
              //
              if (clkDelay == 128 - ECT_CLK_STEP && *IPStart == ECT_CLK_START && *IPEnd != clkDelay) {
                *CPEnd += ECT_CLK_STEP + (*IPEnd -*IPStart);
              }
              //
              // Update Largest variables
              //
              cWidth = *CPEnd - *CPStart;
              lWidth = *LPEnd - *LPStart;
              if (cWidth > lWidth) {
                *LPStart  = *CPStart;
                *LPEnd    = *CPEnd;
              }
            }
          }
        }
      }
      //
      // Clean up registers.  No need to clear MR3 since DIMM will be reset
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          Offset = MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG +
            ((MCHBAR_CH1_CR_REUT_CH_MISC_ODT_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG) * Channel);
          ReutChMiscOdtCtrl.Data                  = MrcReadCR (MrcData, Offset);
          ReutChMiscOdtCtrl.Bits.MPR_Train_DDR_On = 0;
          MrcWriteCR (MrcData, Offset, ReutChMiscOdtCtrl.Data);
        }
      }
    }

#ifdef MRC_DEBUG_PRINT
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            CPEnd = &CurrentPassingEnd[Channel][Rank];
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              (LastDqsRan[clkDelayArray][Channel][Rank] != ECT_DQS_STOP) ? ". " : "# "
              );
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "(% 3d)", LastDqsRan[clkDelayArray][Channel][Rank]);
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
        }
      }
    }
#endif // MRC_DEBUG_PRINT
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tLeft\tRight\tWidth\tClkDelay\n");
  //
  // Find largest passing region and Update PICodes
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut          = &ControllerOut->Channel[Channel];
      DdrCrClkPiCode.Data = 0;
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          LPStart = &LargestPassingStart[Channel][Rank];
          LPEnd   = &LargestPassingEnd[Channel][Rank];
          lWidth  = *LPEnd - *LPStart;

          //
          // Error Handler if eye not found for all bytes
          //
          if (lWidth == 0) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nERROR!! NO EYE found for Channel:%u Rank:%u\n", Channel, Rank);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "Channel %u Rank %u:\t%d\t%d\t%d\t%d\n",
              Channel,
              Rank,
              *LPStart,
              *LPEnd,
              lWidth,
              0
              );
            return mrcReadMPRErr;
          }

          if (lWidth > ECT_MIN_WIDTH) {
            PiCode = (UINT8) (*LPStart + lWidth / 2);
          } else {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_WARNING,
              "\nWARNING!! lWidth <= %u for Channel %u Rank %u \n",
              ECT_MIN_WIDTH,
              Channel,
              Rank
              );
            PiCode = 64;
          }
          //
          // Update Host Structure with new PiCode
          //
          switch (Rank) {
            case 0:
              DdrCrClkPiCode.Bits.PiSettingRank0 = PiCode;
              break;

            case 1:
              DdrCrClkPiCode.Bits.PiSettingRank1 = PiCode;
              break;

            case 2:
              DdrCrClkPiCode.Bits.PiSettingRank2 = PiCode;
              break;

            case 3:
              DdrCrClkPiCode.Bits.PiSettingRank3 = PiCode;
              break;

            default:
              break;
          }

          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "C%u.R%u:\t%d\t%d\t%d\t%d\n",
            Channel,
            Rank,
            *LPStart,
            *LPEnd,
            lWidth,
            PiCode
            );
        }
      }

      Offset = DDRCLKCH0_CR_DDRCRCLKPICODE_REG +
        ((DDRCLKCH1_CR_DDRCRCLKPICODE_REG - DDRCLKCH0_CR_DDRCRCLKPICODE_REG) * Channel);
      MrcWriteCR (MrcData, Offset, DdrCrClkPiCode.Data);
      MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
    }
  }

  Status = ChangeMargin (MrcData, RdT, 0, 0, 1, 0, 0, 0, 0, 0, 0, MrcRegFileCurrent);
  Status = MrcResetSequence (MrcData);

  return Status;
}

/**
  Find a good starting point for DDR3/4 CTL/CMD/CLK, using a quick 2D search.
  Sweep CTL/CMD PI range and look for best CLK margin using linear CLK sweep at each point.

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus
**/
MrcStatus
CtlClockCentering (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  UINT32              Left[MAX_CHANNEL];
  UINT32              Right[MAX_CHANNEL];
  UINT32              Width[MAX_CHANNEL];
  UINT32              MaxWidth[MAX_CHANNEL];
  UINT16              MaxPi;
  UINT16              MinPi;
  static const UINT16 MinPiGb = 75;
  static const UINT16 MaxPiGb = 0;
  UINT8               MaxClk;
  UINT8               MinClk;
  UINT8               BestCtlPi[MAX_CHANNEL];
  UINT8               BestCtlPiLast[MAX_CHANNEL];
  UINT8               ChBitMask;
  UINT8               ChRankMask;
  UINT8               RankMask;
  UINT8               Channel;
  UINT8               ResultRank[MAX_CHANNEL];
  UINT8               Rank;
  UINT8               CtlPiCode;
  UINT8               CtlLow;
  UINT8               CtlHigh;
  UINT8               CtlStep;
  INT32               ShiftPi;
  INT8                ClkLow[MAX_CHANNEL];
  UINT8               ClkHigh[MAX_CHANNEL];
  UINT8               ClkStep;
  BOOLEAN             SkipVref;

  Inputs         = &MrcData->Inputs;
  MrcCall        = Inputs->Call.Func;
  Outputs        = &MrcData->Outputs;
  Debug          = &Outputs->Debug;
  ControllerOut  = &Outputs->Controller[0];
  Status         = mrcSuccess;
  MrcCall->MrcSetMem ((UINT8 *) Left, sizeof (Left), 0);
  MrcCall->MrcSetMem ((UINT8 *) Right, sizeof (Right), 0);
  MrcCall->MrcSetMem ((UINT8 *) Width, sizeof (Width), 0);
  MrcCall->MrcSetMem (BestCtlPi, sizeof (BestCtlPi), 0);
  MrcCall->MrcSetMem (BestCtlPiLast, sizeof (BestCtlPiLast), 0);
  MrcCall->MrcSetMem (ResultRank, sizeof (ResultRank), 0);
  CtlLow  = 32;   // [0..127] --> [32..96], keep 32 ticks on each side for later margining steps.
  CtlHigh = 96;
  CtlStep = 16;

  RankMask = Outputs->ValidRankMask;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((1 << Rank) & ControllerOut->Channel[Channel].ValidRankBitMask) {  // Pick one rank to get the results from
        ResultRank[Channel] = Rank;
        break;
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCLK PI Range\tLeft\tRight\tWidth\n");

  // Setup REUT Test to iteration through appropriate ranks during test
  ChBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChBitMask |= SelectReutRanks (MrcData, Channel, RankMask, 0);
    if ((1 << Channel) & ChBitMask) {
      ChannelOut = &ControllerOut->Channel[Channel];
      ChRankMask = ChannelOut->ValidRankBitMask;

      // Find the maximum PI value for TxDq, TxDqs and RecEn which may limit CLK Sweep
      FindDqPiLimits (MrcData, Channel, ChRankMask, NULL, &MaxPi);

      // Calculate the upper CLK value possible for sweep range based on Max PI Value.
      if ((MaxPi + DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MAX) < DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX) {
        MaxClk = DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MAX;
      } else {
        MaxClk = (UINT8) (DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX - MaxPi);
      }
      // Determine the lower limiting CLK setting out of all ranks in the Channel.
      MinClk = 0;
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((1 << Rank) & ChRankMask) {
          MinClk = MAX (MinClk, ChannelOut->ClkPiCode[Rank]);
        }
      }
      ClkLow[Channel] = (INT8) MinClk;
      ClkHigh[Channel] = MIN (MinClk + MaxClk, DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MAX);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%d\t\t%d\t%d\t%d\n", Channel, ClkLow[Channel], ClkHigh[Channel], ClkHigh[Channel] - ClkLow[Channel]);
    } else {
      // Apply values for unpopulated channels
      ClkLow[Channel] = DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MAX;
      ClkHigh[Channel] = DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MIN;
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Center Clock Timing per rank\n\tChannel 0\t\t\tChannel 1\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CTL/CMD\tLeft\tRight\tWidth\t\tLeft\tRight\tWidth\n");

  SkipVref    = TRUE;
  MrcCall->MrcSetMem ((UINT8 *) MaxWidth, sizeof (MaxWidth), 0);

  for (CtlPiCode = CtlLow; CtlPiCode <= CtlHigh; CtlPiCode += CtlStep) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%u", CtlPiCode);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((1 << Channel) & ChBitMask) {
        // Shift both CTL and CMD
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl,  RankMask, 3, CtlPiCode, 1);
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdN, RankMask, 3, CtlPiCode, 1);
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, RankMask, 3, CtlPiCode, 1);
      }
    }

    ClkStep = 6;
    CmdLinearFindEdges (MrcData, MrcIterationClock, ChBitMask, RankMask, 3, ClkLow, ClkHigh, ClkStep, 1, (INT8 *) NULL, MRC_PRINTS_OFF, SkipVref, FALSE);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((1 << Channel) & ChBitMask) == 0) {
        if (Channel == 0) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t");
        }
        continue;
      }
      Rank = ResultRank[Channel];
      Left[Channel]  = Outputs->MarginResult[LastCmdT][Rank][Channel][0][0] / 10;
      Right[Channel] = Outputs->MarginResult[LastCmdT][Rank][Channel][0][1] / 10;
      Width[Channel] = Right[Channel] - Left[Channel];
      if (Width[Channel] > MaxWidth[Channel]) {
        MaxWidth[Channel] = Width[Channel];
        BestCtlPi[Channel] = BestCtlPiLast[Channel] = CtlPiCode;
      } else if (Width[Channel] == MaxWidth[Channel]) { // Track the last PI which still gives the max width
        BestCtlPiLast[Channel] = CtlPiCode;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%u\t%u\t%u\t", Left[Channel], Right[Channel], Width[Channel]);
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  } // for CtlPiCode

  // Apply the best CTL/CMD PI and re-center the CLK
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((1 << Channel) & ChBitMask) {
      CtlPiCode = (BestCtlPi[Channel] + BestCtlPiLast[Channel]) / 2;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u: Best CTL/CMD PI is %u, CLK width = %u\n", Channel, CtlPiCode, MaxWidth[Channel]);
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl,  RankMask, 3, CtlPiCode, 1);
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdN, RankMask, 3, CtlPiCode, 1);
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, RankMask, 3, CtlPiCode, 1);
    }
  }
  ClkStep = 4;
  Status = CmdLinearFindEdges (MrcData, MrcIterationClock, ChBitMask, RankMask, 3, ClkLow, ClkHigh, ClkStep, 1, (INT8 *) NULL, MRC_PRINTS_ON, SkipVref, TRUE);
  // Enforce Data Pi GuardBand
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((1 << Channel) & ChBitMask) {
      ChannelOut = &ControllerOut->Channel[Channel];
      ChRankMask = ChannelOut->ValidRankBitMask;

      // Find the minimal PI value for TxDq, TxDqs and RecEn which may limit CLK Sweep
      FindDqPiLimits (MrcData, Channel, ChRankMask, &MinPi, &MaxPi);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Checking DQSPI GB criteria MinPI %u MinPiGb %u\n", MinPi, MinPiGb);
      ShiftPi = (INT32) (MinPiGb - MinPi);
      if (MinPi < MinPiGb) {
        if ((ShiftPi + MaxPi) > (DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX - MaxPiGb)) {
          ShiftPi = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX - MaxPiGb - MaxPi;
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Shifting Channel by %d\n", ShiftPi);
        ShiftChannelTiming (MrcData, Channel, ShiftPi, TRUE, TRUE);
      }
    }
  }
  return Status;
}

/**
  Center CMD with respect to CLK & CTL.

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     ChannelMask    - Channels to train
  @param[in]     LoopCount      - Loop count for CMD stress.
  @param[in]     SetupCadb      - Indicates if SetupCadb should be called and disabled at the end.
  @param[in]     DebugPrint     - Enable / disable debug printing
  @param[in]     UpdateHost     - Determines if MrcData structure is updated

  @retval MrcStatus
**/
MrcStatus
MrcCmdTimingCentering (
  IN MrcParameters *const MrcData,
  IN UINT8                ChannelMask,
  IN UINT8                LoopCount,
  IN BOOLEAN              SetupCadb,
  IN BOOLEAN              DebugPrint,
  IN const UINT8          UpdateHost
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcStatus         Status;
  MrcProfile        Profile;
  MrcDebugMsgLevel  DebugLevel;
  UINT8             Channel;
  UINT8             ChBitMask;
  UINT8             RankMask;
  UINT8             MidPointCke[MAX_CHANNEL];
  UINT8             MidPointCmdN[MAX_CHANNEL];
  UINT8             MidPointCmdS[MAX_CHANNEL];
  BOOLEAN           ExitOnFailure;
  BOOLEAN           Lpddr;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Profile = Inputs->MemoryProfile;
  ControllerOut = &Outputs->Controller[0];
  ExitOnFailure = (BOOLEAN) Inputs->ExitOnFailure;
  DebugLevel    = DebugPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  Lpddr         = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  ChBitMask     = Outputs->ValidChBitMask & ChannelMask;
  RankMask      = Outputs->ValidRankMask;

  // Program default rank mapping
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    SelectReutRanks (MrcData, Channel, RankMask, 0);
  }

  if (SetupCadb) {
    // SetupIOTest is already called in TrainDDROptParms and LCT.
    SetupIOTestCADB (MrcData, ChBitMask, LoopCount, NTHSOE, 1, 0);
  }

  if (Lpddr) {
    //
    // Center Command Timing
    //
    MRC_DEBUG_MSG (Debug, DebugLevel, "\n*** Previous training results\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      MidPointCke[Channel] = (UINT8)ChannelOut->CkeCmdPiCode[0];
      MidPointCmdS[Channel] = (UINT8)ChannelOut->CmdsCmdPiCode[0];
      MRC_DEBUG_MSG (
        Debug,
        DebugLevel,
        "C%u: CAA: CKE fub: %d, CmdS fub: %d\n",
        Channel,
        MidPointCke[Channel],
        MidPointCmdS[Channel]
        );
    }

    MRC_DEBUG_MSG (Debug, DebugLevel, "\n*** Center CAA[5,6,7,8,9] Timing using CKE fub\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCke, RankMask, 1, MidPointCke, DebugPrint, UpdateHost);
    if ((Status != mrcSuccess) && ExitOnFailure) {
      return Status;
    }

    MRC_DEBUG_MSG (Debug, DebugLevel, "\n*** Center CAA[0,1,2,3,4] Timing using CmdS fub\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmdS, RankMask, 1, MidPointCmdS, DebugPrint, UpdateHost);
    if ((Status != mrcSuccess) && ExitOnFailure) {
      return Status;
    }

    MRC_DEBUG_MSG (Debug, DebugLevel, "\n*** Previous results\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      MidPointCmdS[Channel] = (UINT8)ChannelOut->CmdsCmdPiCode[1];
      MidPointCmdN[Channel] = (UINT8)ChannelOut->CmdnCmdPiCode[1];
      MRC_DEBUG_MSG (
        Debug,
        DebugLevel,
        "C%u: CAB: CmdS fub: %d, CmdN fub: %d\n",
        Channel,
        MidPointCmdS[Channel],
        MidPointCmdN[Channel]
        );
    }

    MRC_DEBUG_MSG (Debug, DebugLevel, "\n*** Center CAB[5,8] Timing using CmdS fub\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmdS, RankMask, 2, MidPointCmdS, DebugPrint, UpdateHost);
    if ((Status != mrcSuccess) && ExitOnFailure) {
      return Status;
    }

    MRC_DEBUG_MSG (Debug, DebugLevel, "\n*** Center CAB[0,1,2,3,4,6,7,9] Timing using CmdN fub\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmdN, RankMask, 2, MidPointCmdN, DebugPrint, UpdateHost);
    if ((Status != mrcSuccess) && ExitOnFailure) {
      return Status;
    }
  } else { // not Lpddr
    //
    // Center Command Timing
    //
    MRC_DEBUG_MSG (Debug, DebugLevel, "\n*** Previous results\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      MidPointCmdS[Channel] = (UINT8)ChannelOut->CmdsCmdPiCode[0];
      MidPointCmdN[Channel] = (UINT8)ChannelOut->CmdnCmdPiCode[0];
      MRC_DEBUG_MSG (
        Debug,
        DebugLevel,
        "C%u: CmdS fub: %d, CmdN fub: %d\n",
        Channel,
        MidPointCmdS[Channel],
        MidPointCmdN[Channel]
        );
    }
    MRC_DEBUG_MSG (Debug, DebugLevel, "\n\n*** Center Command S Timing\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmdS, RankMask, 1, MidPointCmdS, DebugPrint, UpdateHost);
    if ((Status != mrcSuccess) && ExitOnFailure) {
      return Status;
    }
    MRC_DEBUG_MSG (Debug, DebugLevel, "\n\n*** Center Command N Timing\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmdN, RankMask, 1, MidPointCmdN, DebugPrint, UpdateHost);
    if ((Status != mrcSuccess) && ExitOnFailure) {
      return Status;
    }
  }

  //
  // Disable CADB Deselects after Command Training
  //
  if (SetupCadb) {
    MrcDisableCadbOnDeselect (MrcData);
  }

  //
  // Finish Training with JEDEC Reset / Init
  //
  Status = MrcResetSequence (MrcData);
  return Status;
}

/**
  This function performs Late command training.
  Center CMD/CTL-CLK timing using complex patterns.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it's a success return mrcSuccess
**/
MrcStatus
MrcLateCommandTraining (
  MrcParameters *const MrcData
  )
{
  const MrcInput                      *Inputs;
  MrcDebug                            *Debug;
  MrcOutput                           *Outputs;
  MrcControllerOut                    *ControllerOut;
  MrcChannelOut                       *ChannelOut;
  MrcStatus                           Status;
  MrcProfile                          Profile;
  UINT32                              Offset;
  UINT16                              PiMin;
  UINT8                               Cmd2N;
  UINT8                               Channel;
  UINT8                               ChBitMask;
  UINT8                               RankMask;
  UINT8                               LocalRankMask;
  UINT8                               Rank;
  UINT8                               Ranks;
  UINT8                               CmdPiCode[MAX_CHANNEL];
  UINT8                               CtlPiCode[MAX_CHANNEL];
  INT32                               ClkPiShift;
  INT32                               ClkPiValue;
  BOOLEAN                             Lpddr;
  BOOLEAN                             ExitOnFailure;
  MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_0_STRUCT  ReutChSeqBaseAddrOrderCarryInvertCtl;
  MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_0_STRUCT ReutChSeqBaseAddrIncCtl;
  MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CTRL_STRUCT              ReutChPatCadbCtrl;
  MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_STRUCT    ReutChSeqBaseAddrWrap;


  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Profile       = Inputs->MemoryProfile;
  ExitOnFailure = (Inputs->ExitOnFailure == TRUE);

  //
  // Check if LPDDR3 memory is used
  //
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);

  ChBitMask     = Outputs->ValidChBitMask;
  RankMask      = Outputs->ValidRankMask;

  // Program default rank mapping
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    SelectReutRanks (MrcData, Channel, RankMask, 0);
  }

  if (Lpddr) {
    SetupIOTestCADB (MrcData, ChBitMask, 14, NTHSOE, 1, 0); // LC = 10
  } else {
    Cmd2N = FALSE;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        Cmd2N = (ControllerOut->Channel[Channel].Timing[Profile].NMode == 2) ? TRUE : FALSE; // All channels have same NMode
        break;
      }
    }
    CmdPiCode[0] = CmdPiCode[1] = (Cmd2N == TRUE) ? 85 : 64;
    CtlPiCode[0] = CtlPiCode[1] = 64;

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      " Cmd2N %d, CmdPiCode %d, ChBitMask = 0x%x\n",
      Cmd2N,
      CmdPiCode[0],
      ChBitMask
      );

    //
    // Setup REUT
    // LC= 10, SOE  = 1 (NTHSOE), EnCADB = 1, EnCKE = 0
    //
    SetupIOTestCADB (MrcData, ChBitMask, 14, NTHSOE, 1, 0);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      LocalRankMask = ChannelOut->ValidRankBitMask;
      ClkPiShift    = MRC_INT32_MIN;

      //
      // Shift everything to the right.  To get DQ timing right, program Clk as close to 0 as possible
      //
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((1 << Rank) & LocalRankMask) {
          FindDqPiLimits (MrcData, Channel, 1 << Rank, &PiMin, NULL); 
          ClkPiValue = ClkPiShift;
          ClkPiShift = (0 - (MIN (PiMin, ChannelOut->ClkPiCode[Rank])));

          if (Inputs->Ddr4DdpSharedClock) {
            if (Rank == 0) {
              continue;
            } else {
              ClkPiShift = MAX (ClkPiShift, ClkPiValue);
            }
          }
          
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "Ch%dR%d - ClkPiShift = %d\n",
            Channel,
            Rank,
            ClkPiShift
            );

          ShiftPIforCmdTraining (
            MrcData,
            Channel,
            MrcIterationClock,
            1 << Rank,
            1,
            ClkPiShift,
            1
            );
        }
      }

      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, LocalRankMask, 1, CmdPiCode[Channel], 1);
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdN, LocalRankMask, 1, CmdPiCode[Channel], 1);
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl,  LocalRankMask, 1, CtlPiCode[Channel], 1);
    }
  }

  if (!Lpddr) {
    // Center CMD/CTL vs. CLK
    Status = CtlClockCentering (MrcData);
    if ((Status != mrcSuccess) && ExitOnFailure) {
      return Status;
    }

    // Get the new midpoint for CMD and CTL
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      CmdPiCode[Channel] = (UINT8) ChannelOut->CmdsCmdPiCode[0];
      CtlPiCode[Channel] = (UINT8) ChannelOut->CtlPiCode[0];
    }
  }

  // Center Command Timing and update host
  Status = MrcCmdTimingCentering (MrcData, ChBitMask, 14, FALSE, MRC_PRINTS_ON, 1);

  if (Lpddr) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Center Control Timing\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      Offset = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_0_REG +
        ((MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_0_REG) * Channel);
      ReutChSeqBaseAddrOrderCarryInvertCtl.Data = 0;
      MrcWriteCR (MrcData, Offset, ReutChSeqBaseAddrOrderCarryInvertCtl.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d ReutChSeqBaseAddrOrderCarryInvertCtl: 0x%08X\n", Channel, ReutChSeqBaseAddrOrderCarryInvertCtl.Data);

      Offset = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_0_REG +
        ((MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_0_REG) * Channel);
      ReutChSeqBaseAddrIncCtl.Data = 0;
      ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Update_Scale   = 1;
      ReutChSeqBaseAddrIncCtl.Bits.Bank_Base_Address_Update_Scale   = 1;
      ReutChSeqBaseAddrIncCtl.Bits.Row_Base_Address_Update_Scale    = 1;
      ReutChSeqBaseAddrIncCtl.Bits.Column_Base_Address_Update_Scale = 1;
      ReutChSeqBaseAddrIncCtl.Bits.Column_Base_Address_Increment    = 1;
      MrcWriteCR64 (MrcData, Offset, ReutChSeqBaseAddrIncCtl.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d ReutChSeqBaseAddrIncCtl: 0x%08X%08X\n", Channel, ReutChSeqBaseAddrIncCtl.Data32[1],
        ReutChSeqBaseAddrIncCtl.Data32[0]);

      Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CTRL_REG +
        ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CTRL_REG) * Channel);
      ReutChPatCadbCtrl.Data = 0;
      ReutChPatCadbCtrl.Bits.Lane_Deselect_Enable = 0xB; // All, except CMD
      ReutChPatCadbCtrl.Bits.CMD_Deselect_Start = 2;     // Start on RD
      MrcWriteCR (MrcData, Offset, ReutChPatCadbCtrl.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d ReutChPatCadbCtrl: 0x%08X\n", Channel, ReutChPatCadbCtrl.Data);

      Offset = MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_0_REG +
        ((MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_0_REG) * Channel);
      MrcWriteCR8 (MrcData, Offset, 0xFF);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d ReutChSeqDummyreadMask Offset:0x%X Value:0x%X\n", Channel, Offset, 0xFF);

      // Start from logical Rank 0
      Offset = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_REG +
        ((MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_REG) * Channel);
      MrcWriteCR64 (MrcData, Offset, 0);

      //
      // Wrap at column 127
      // Logical Rank Wrap address will be updated in SelectReutRanks() later on.
      //
      Offset = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_REG +
        ((MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_REG) * Channel);
      ReutChSeqBaseAddrWrap.Data = 0;
      ReutChSeqBaseAddrWrap.Bits.Column_Address = 0x7F;
      MrcWriteCR64 (MrcData, Offset, ReutChSeqBaseAddrWrap.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d ReutChSeqBaseAddrWrap: 0x%08X%08X\n", Channel, ReutChSeqBaseAddrWrap.Data32[1],
        ReutChSeqBaseAddrWrap.Data32[0]);
    } // for Channel

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      Ranks = (1 << Rank);
      if ((Ranks & RankMask) == 0) {
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** ECT results\n");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          CtlPiCode[Channel] = ControllerOut->Channel[Channel].CtlPiCode[Rank];
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%uR%u: CTL: %u\n", Channel, Rank, CtlPiCode[Channel]);
        } else {
          CtlPiCode[Channel] = 0;
        }
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCentering CTL on Rank %d\n", Rank);
      Status = CmdTimingCentering (MrcData, MrcIterationCtl, Ranks, Ranks, CtlPiCode, MRC_PRINTS_ON, 1);
      if ((Status != mrcSuccess) && ExitOnFailure) {
        return Status;
      }
    }
  } else { // not Lpddr
    //
    // Center Control Timing. For control pins, CKE PI is shared between Rank 2 and 3
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n*** Center Control Timing. CKE PI is shared between Rank 2 and 3");
    for (Rank = 0; Rank < (MAX_RANK_IN_CHANNEL - 1); Rank++) {
      Ranks = (1 << Rank);

      if (Rank == 2) {
        Ranks = 0xC;
      }

      Ranks = Ranks & RankMask;

      if (Ranks) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n Rank %d\n", Rank);
        Status = CmdTimingCentering (MrcData, MrcIterationCtl, Ranks, 1, CtlPiCode, MRC_PRINTS_ON, 1);
        if ((Status != mrcSuccess) && ExitOnFailure) {
          return Status;
        }
      }
    }
  }

  //
  // Disable CADB Deselects after Command Training
  //
  MrcDisableCadbOnDeselect (MrcData);

  //
  // Finish Training with JEDEC Reset / Init
  //
  Status = MrcResetSequence (MrcData);
  return Status;
}

/**
  Shift CMD/CTL/CLK PI's to the left as much as possible to reduce CMD latency.

  @param[in] MrcData  -  Include all MRC global data.

  @retval MrcStatus
**/
MrcStatus
MrcCmdNormalization (
  IN MrcParameters *const MrcData
  )
{

  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  UINT32            MinCode;
  UINT32            MinCodeTxDq;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             Byte;
  BOOLEAN           Lpddr;
  MrcStatus         Status;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);

  //
  // Normalize timing back to 0 to improve performance
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Normalize timing back to 0\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist(Outputs, Channel)) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    //
    // Find the minimum PI Code across all relevant CMD and CTL fubs
    // CLK shift will also change RcvEn / TxDq / TxDqs, so check them as well.
    //
    MinCode = ChannelOut->CkeCmdPiCode[0];
    MinCode = MIN(MinCode, ChannelOut->CmdsCmdPiCode[0]);
    MinCodeTxDq = DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX;

    if (Lpddr) {
      MinCode = MIN(MinCode, ChannelOut->CmdsCmdPiCode[1]);
      MinCode = MIN(MinCode, ChannelOut->CmdnCmdPiCode[1]);
    } else {
      MinCode = MIN(MinCode, ChannelOut->CmdnCmdPiCode[0]);
    }

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist(MrcData, Rank, Channel)) {
        MinCode = MIN(MinCode, ChannelOut->CkePiCode[Rank]);
        MinCode = MIN(MinCode, ChannelOut->CtlPiCode[Rank]);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MinCode = MIN(MinCode, ChannelOut->TxDqs[Rank][Byte]);
          MinCode = MIN(MinCode, ChannelOut->TxDq[Rank][Byte]);
          MinCode = MIN(MinCode, ChannelOut->RcvEn[Rank][Byte]);
          MinCodeTxDq = MIN(MinCodeTxDq, ChannelOut->TxDq[Rank][Byte]); // Keep track of Min TxDq PI
        }
      }
    }

    if (MinCodeTxDq >= 128) {
      MinCode = MIN(MinCode, MinCodeTxDq - 128);  // Keep at least 128 PI ticks on TxDq for Tx FIFO.
    } else {
      MinCode = 0;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d: shifting all PI settings by Min PI Code = %d\n", Channel, MinCode);
    ShiftChannelTiming(MrcData, Channel, (-1) * MinCode, 1, TRUE);
  } // for Channel

  Status = MrcResetSequence (MrcData);

  return mrcSuccess;
}

/**
  Perform Command Voltage Centering.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeded returns mrcSuccess
**/
MrcStatus
MrcCmdVoltageCentering (
  IN OUT MrcParameters *const MrcData
  )
{
  static const UINT16 mode = 0;
  const MrcInput *Inputs;
  MrcDebug       *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput      *Outputs;
  MrcChannelOut  *ChannelOut;
  MrcStatus      Status;
  UINT32         BERStats[4];
  UINT32         *Margin;
  UINT8          LoopCount;
  UINT8          Channel;
  UINT8          Rank;
  UINT8          Byte;
  UINT8          chBitMask;
  UINT32         Low[MAX_CHANNEL];
  UINT32         High[MAX_CHANNEL];
  UINT32         Height;
  UINT16         MinHeight;
  INT32          Center[MAX_CHANNEL];
  BOOLEAN        PerMC;
  BOOLEAN        Ddr4;
  BOOLEAN        Lpddr3;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  Lpddr3    = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  Ddr4      = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  LoopCount = 10;
  Status    = mrcSuccess;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) Low, sizeof (Low), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) High, sizeof (High), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) Center, sizeof (Center), 0);
  PerMC = (!Ddr4)  || (Inputs->CaVrefConfig == 0);  // CA Vref per channel or not

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Cmd Vref Training with LC = %d\n", LoopCount);

  if (Lpddr3) {
    SetupIOTestCADB (MrcData, Outputs->ValidChBitMask, LoopCount, NSOE, 1, 0);
    //
    // Select all available ranks
    //
    chBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      chBitMask |= SelectReutRanks (MrcData, Channel, ChannelOut->ValidRankBitMask, 0);
      if ((1 << Channel) & chBitMask) {
        MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
      }
    }
    //
    // Run test for Cmd Voltage
    //
    Status = MrcGetBERMarginCh (
               MrcData,
               Outputs->MarginResult,
               chBitMask,
               0xFF,
               0,
               CmdV,
               mode,
               0,
               MAX_POSSIBLE_VREF,
               0,
               BERStats
               );
    Status = MrcResetSequence (MrcData);
  } else {  // DDR3 or DDR4
    Status = DQTimeCentering1D (
               MrcData,
               Outputs->ValidChBitMask,
               CmdV,
               0,          // ResetPerBit
               LoopCount,
               TRUE,       // MsgPrint
               FALSE       // EarlyCentering
               );
  }

  //
  // Find center value and program it
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Margin = &Outputs->MarginResult[LastCmdV][Rank][Channel][Byte][0];
          Low[Channel]  = MIN (Low[Channel], Margin[0]);
          High[Channel] = MIN (High[Channel], Margin[1]);
          if (Lpddr3) {
            break;  // GetBerMarginCh() stores resutls in rank 0 byte 0
          }
        } // for Byte
      }
      if (Lpddr3) {
        break;  // GetBerMarginCh() stores resutls in rank 0 byte 0
      }
    } // for Rank
  }

  //
  // Print per-channel results summary
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCmd Vref Summary:\n\tLow\tHigh\tHeight\tCenter\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "C%u:\t%u\t%u\t%u\t%d\n",
        Channel,
        Low[Channel] / 10,
        High[Channel] / 10,
        (Low[Channel] + High[Channel]) / 10,
        ((INT32) (High[Channel] - Low[Channel])) / 20
        );
    }
  } // for Channel

  if (PerMC) {  // Put the worst case of both channels in ch0 variables
    Low[0]  = MIN (Low[0], Low[1]);
    High[0] = MIN (High[0], High[1]);
  }
  if (PerMC || (MrcChannelExist (Outputs, 0))) {
    Center[0] = ((INT32) (High[0] - Low[0])) / 2;
    UpdateVrefWaitTilStable (MrcData, 2, 1, Center[0] / 10, 0, 0, FALSE, 0);
  }
  if (!PerMC && (MrcChannelExist (Outputs, 1))) {
    // Ch1 CAvref in DDR4
    Center[1] = ((INT32) (High[1] - Low[1])) / 2;
    UpdateVrefWaitTilStable (MrcData, 3, 1, Center[1] / 10, 0, 0, FALSE, 0);
  }
  MrcResetSequence (MrcData);

  if (PerMC) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Sys:\t%u\t%u\t%u\t%d\n",
      Low[0] / 10,
      High[0] / 10,
      (Low[0] + High[0]) / 10,
      Center[0] / 10
      );
  }

  //
  // Check UPM limits
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      //
      // Get Min Height from 1/2 WrV UPM Limit.
      //
      MinHeight = MrcGetUpmPwrLimit (MrcData, WrV, UpmLimit) / 2;   // 1/2 WrV UPM Limit
      Height = Low[Channel] + High[Channel];
      if (Height < MinHeight) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_ERROR,
          "\nERROR! Height region (%d) less than expected value (%d)\n",
          Height / 10,
          MinHeight / 10
          );
        if (Inputs->ExitOnFailure) {
          return mrcMiscTrainingError;
        }
      }
      if (PerMC) {
        break;
      }
    }
  } // for Channel

  //
  // Update MrcData for future tests
  //
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (((1 << Rank) & Outputs->ValidRankMask) == 0) {
      continue;  // No such rank
    }
    Outputs->MarginResult[LastCmdV][Rank][0][0][0] = Low[0] + Center[0];
    Outputs->MarginResult[LastCmdV][Rank][0][0][1] = High[0] - Center[0];
    if (!PerMC && (MrcChannelExist (Outputs, 1))) {
      Outputs->MarginResult[LastCmdV][Rank][1][0][0] = Low[1] + Center[1];
      Outputs->MarginResult[LastCmdV][Rank][1][0][1] = High[1] - Center[1];
    }
  }
  //
  // Disable CADB Deselects
  //
  MrcDisableCadbOnDeselect (MrcData);

  return Status;
}

/**
  Training the Cmd slew rate for best margins.
  Steps:
  1. Find the minimal number of stages for which Comp is not saturated (Start).
  2. Find the maximal number of stages for which Comp is not saturated (Stop).
  3. Train Cmd Slew rate stages in the region [Start, Stop].
  4. Re-center Cmd Timing.
  5. Re-center Cmd Voltage.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus
**/
MrcStatus
MrcCmdSlewRate (
  IN MrcParameters *const MrcData
  )
{
  static const UINT8  TestList[]  = { CmdV, CmdT};
  static const UINT8  Scale[]     = { 1, 2, 0, 0, 0 };
  static const UINT8  OptParam[]  = { OptCmdSComp };
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcIntOutput        *IntOutputs;
  MrcIntControllerOut *IntControllerOut;
  MrcStatus           Status;
  OptOffsetChByte     BestOff;
  INT8                Start;
  INT8                Stop;
  UINT8               CurrNumStages;
  UINT8               SlewRateVref;
  UINT8               CompCode;
  UINT8               CompCodeGb;
  UINT8               MaxNumStages;
  UINT8               MinNumStages;
  BOOLEAN             Lpddr;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  IntOutputs = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);

  MinNumStages = OptParamLimitValue (MrcData, OptParam[0], 0);
  MaxNumStages = OptParamLimitValue (MrcData, OptParam[0], 1);
  CompCodeGb = 2;

  if (Lpddr) {
    // For LPDDR perform a limited search of the CMD slew rate due to complete failure danger
    CurrNumStages = (UINT8) (IntControllerOut->CompCtl1.Bits.CmdScompPC ? (IntControllerOut->CompCtl1.Bits.CmdScompCells + 1) : (IntControllerOut->CompCtl1.Bits.CmdScompCells * 2 + 1));
    MinNumStages = (UINT8) (DIVIDEROUND (Outputs->Qclkps, gMinCycleStageDelay[1]));
    MinNumStages = MIN (CurrNumStages, MinNumStages) - 1;
    MaxNumStages = CurrNumStages + 5;
  }

  // Find the minimal and maximal Cell delay that does not overflow the Comp Code.
  // Search is performed by initializing the read Comp code to a saturated value
  // in order to ensure entry to while loop

  // 1. Find minimal number of stages
  Start = MinNumStages - 1;
  CompCode = 63; // Force entry to search by asigning saturate comp code
  while (CompCode > 63 - CompCodeGb) { // While comp code is saturated
    Start++;
    SlewRateVref = CmdSlewRateStagesToVref (MrcData, Start);
    CompCode = (UINT8) UpdateCompGlobalOffset (MrcData, SCompCmd, SlewRateVref, FALSE, FALSE);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Cmd Slew Rate: %d, CompCode: %d\n", Start, CompCode);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Start Search region for Cmd Slew Rate: %d, CompCode: %d\n", Start, CompCode);

  // 2. Find maximal number of stages
  Stop = Start; // Begin search for maximal stages from entry point
  CompCode = CompCodeGb + 1; // Force entry to search by assigning saturated comp code
  while ((CompCode > CompCodeGb) && (Stop < MaxNumStages)){ // While comp code is saturated
    Stop++;
    SlewRateVref = CmdSlewRateStagesToVref (MrcData, Stop);
    CompCode = (UINT8) UpdateCompGlobalOffset (MrcData, SCompCmd, SlewRateVref, FALSE, FALSE);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Cmd Slew Rate: %d, CompCode: %d\n", Stop, CompCode);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Stop Search region for Cmd Slew Rate: %d, CompCode: %d\n", Stop, CompCode);

  // Reset to default value + MrcReset Sequence
  MrcWriteCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL1_REG, IntControllerOut->CompCtl1.Data);
  ForceRcomp (MrcData);

  // Train Slew Rate for best margins
  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xf,
    OptParam,
    ARRAY_COUNT (OptParam),
    FullGrid,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    &Start, // Start
    &Stop,  // Stop
    14,     // LoopCount
    1,      // Repeats
    0,      // NoPrint
    0,      // SkipOdtUpdate
    0,      // RdRd2Test
    0       // GuardBand
    );

  // Re-Center CMD Timing and voltage and update Host Struct with new center
  Status = MrcCmdTimingCentering (MrcData, Outputs->ValidChBitMask, 10, TRUE, MRC_PRINTS_ON, 1);
  if (Status != mrcSuccess) {
    return Status;
  }
  Status = MrcCmdVoltageCentering (MrcData);
  return Status;
}

/**
  Training the Command TxEq and Ron for best margins.
  Steps:
  1. Find the minimal Vref (Ron) for which Comp is no saturated (Start).
  2. Find the maximal Vref (Ron) for which Comp is no saturated (Stop).
  3. Train Cmd Ron (Vref) & TxEq in the region [Start, Stop].
  4. Center Cmd Timing.
  5. Center Cmd Voltage.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus
**/
MrcStatus
MrcCmdDsTxEq (
  IN MrcParameters *const MrcData
  )
{
  static const UINT8  TestList[]  = { CmdV, CmdT };
  static const UINT8  Scale[]     = { 1, 2, 0, 0, 0 };
  static const UINT8  OptParam[]  = { OptCmdWrDS, OptCmdTxEq };
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcIntOutput        *IntOutputs;
  MrcIntControllerOut *IntControllerOut;
  MrcStatus           Status;
  OptOffsetChByte     BestOff;
  INT8                Start[2];
  INT8                Stop[2];
  UINT32              CompCode;
  UINT32              CompCodeGb;
  DDRCOMP_CR_DDRCRCOMPCTL0_STRUCT  DdrCrCompCtl0;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  IntOutputs = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];
  DdrCrCompCtl0.Data = IntControllerOut->CompCtl0.Data;

  CompCodeGb = 3;
  Start[0]  = OptParamLimitValue (MrcData, OptParam[0], 0) - 1;
  Stop[0]   = OptParamLimitValue (MrcData, OptParam[0], 1) + 1;

  // Find the minimal and maximal CMD Ron Vref that does not overflow the Comp Code.
  // Search is performed by initializing the read Comp code to a saturated value
  // in order to ensure entry to while loop.
  CompCode = 0; // Set CompCode to a saturated value

  // 1. Find the minimal Drive Strength that doesn't overflow the Comp Code
  while ((CompCode > 63 - CompCodeGb) || (CompCode < CompCodeGb)) { // While comp is saturated
    Start[0]++;
    CompCode = UpdateCompGlobalOffset (MrcData, WrDSCmd, (UINT32) Start[0], FALSE, FALSE);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CMD Ron: %d, CompCode: %d\n", Start[0], CompCode);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Start Search region for Cmd WrDs: %d, CompCode: %d\n", Start[0], CompCode);

  // 2. Find the maximal Drive Strength that doesn't overflow the Comp Code
  CompCode = 64; // Set CompCode to a saturated value
  while ((CompCode > 63 - CompCodeGb) || (CompCode < CompCodeGb)) { // While comp is saturated
    Stop[0]--;
    CompCode = UpdateCompGlobalOffset (MrcData, WrDSCmd, (UINT32) Stop[0], FALSE, FALSE);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CMD Ron: %d, CompCode: %d\n", Stop[0], CompCode);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Stop Search region for Cmd WrDs: %d, CompCode: %d\n", Stop[0], CompCode);

  MrcWriteCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL0_REG, DdrCrCompCtl0.Data);

  // For TxEq simply using the Codes defined in OptParamLimitValue
  Start[1] = OptParamLimitValue (MrcData, OptParam[1], 0);
  Stop[1]  = OptParamLimitValue (MrcData, OptParam[1], 1);

  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xf,
    OptParam,
    ARRAY_COUNT (OptParam),
    ChessOdd,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    Start,  // Start
    Stop,   // Stop
    12,     // Loopcount
    1,      // Repeats
    0,      // NoPrint
    0,      // SkipOdtUpdate
    0,      // RdRd2Test
    0       // GuardBand
    );

  // Re-Center CMD Timing and voltage and update Host Struct with new center
  Status = MrcCmdTimingCentering (MrcData, Outputs->ValidChBitMask, 10, TRUE, MRC_PRINTS_ON, 1);
  if (Status != mrcSuccess) {
    return Status;
  }
  Status = MrcCmdVoltageCentering (MrcData);
  return Status;
}

/**
  Centers Command Timing around a MidPoint

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Iteration       - Determines which PI to shift
  @param[in] Ranks           - Valid Rank bit mask
  @param[in] GroupMask       - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR3
  @param[in] MidPoint        - The MidPoint to center around (per channel)
  @param[in] DebugPrint      - Print messages or not.
  @param[in] UpdateHost      - Determines if MrcData structure is updated
  @retval Nothing
**/
MrcStatus
CmdTimingCentering (
  IN MrcParameters *const MrcData,
  IN UINT8                Iteration,
  IN UINT8                Ranks,
  IN UINT8                GroupMask,
  IN UINT8                MidPoint[MAX_CHANNEL],
  IN BOOLEAN              DebugPrint,
  IN const UINT8          UpdateHost
  )
{
  const MrcInput     *Inputs;
  MrcDebug           *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput          *Outputs;
  MrcControllerOut   *ControllerOut;
  MrcStatus          Status;
  MrcDebugMsgLevel   DebugLevel;
  UINT8              Ledge[MAX_CHANNEL];
  UINT8              Redge[MAX_CHANNEL];
  UINT8              Mid[MAX_CHANNEL];
  UINT8              Low[MAX_CHANNEL];
  UINT8              High[MAX_CHANNEL];
  UINT8              MidValue;
  static const INT8  VrefOffsets[2] = {-8, 8};
  UINT8              Center;
  UINT8              ChBitMask;
  UINT8              RankMask;
  UINT8              Channel;
  UINT8              MinWidth = 18;
  UINT8              lWidth;
  BOOLEAN            SkipVref;

  Inputs         = &MrcData->Inputs;
  MrcCall        = Inputs->Call.Func;
  Outputs        = &MrcData->Outputs;
  Debug          = &Outputs->Debug;
  ControllerOut  = &Outputs->Controller[0];
  Status         = mrcSuccess;
  DebugLevel     = DebugPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  MrcCall->MrcSetMem (Ledge, sizeof (Ledge), 0);
  MrcCall->MrcSetMem (Redge, sizeof (Redge), 0);

  if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR3) &&
      ((Iteration == MrcIterationCmdN) || (Iteration == MrcIterationCmdS) || (Iteration == MrcIterationCke) || (Iteration == MrcIterationCtl))
      ) {
    //
    // Limit the binary search to +/- 32 PI ticks from the ECT midpoint, for LPDDR3 Command/Control
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      MidValue = MidPoint[Channel];
      Low[Channel]  = (MidValue > 32) ? (MidValue - 32) : 0;
      High[Channel] = (MidValue < 127 - 32) ? (MidValue + 32) : 127;
      MRC_DEBUG_MSG (Debug, DebugLevel, "Ch%d: search range is [%d..%d]\n", Channel, Low[Channel], High[Channel]);
    }
    // For LPDDR3 the CMD min eye limit should be like DQ
    MinWidth = 12;
  } else {
    //
    // Binary search will use the full PI range of [0..127]
    //
    MrcCall->MrcSetMem (Low, sizeof (Low), 0);
    MrcCall->MrcSetMem (High, sizeof (High), 127);
  }

  MRC_DEBUG_MSG (Debug, DebugLevel, "Channel\t\t\t0 1\n");

  //
  // Setup REUT Test to iteration through appropriate ranks during test
  //
  ChBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChBitMask |= SelectReutRanks (MrcData, Channel, Ranks, 0);
    if (MidPoint != NULL) {
      Mid[Channel] = MidPoint[Channel];
    }
  }

  if (Iteration == MrcIterationClock) {
    //
    // Use a linear search to center clock and Update Clock Delay/Host
    // Allow wrap around since this is clock
    // CmdLinearFindEdges also programs the new values
    //
    SkipVref = FALSE;
    Status = CmdLinearFindEdges (MrcData, Iteration, ChBitMask, Ranks, GroupMask, (INT8 *) &Low[0], High, 6, 1, (INT8 *) VrefOffsets, DebugPrint, SkipVref, TRUE);
  } else {
    CmdBinaryFindEdge (MrcData, Iteration, ChBitMask, Ranks, GroupMask, Low, Mid, 0, (INT8 *) VrefOffsets, DebugPrint);
    Ledge[0] = Mid[0];
    Ledge[1] = Mid[1];  // CountUp is 0 so return High.
    if (MidPoint == NULL) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Midpoint[] is NULL and MrcIterationClock not selected!\n");
      return mrcWrongInputParameter;
    } else {
      Mid[0]   = MidPoint[0];
      Mid[1]   = MidPoint[1]; //Mid Modified by CmdBinaryFindEdge
    }
    CmdBinaryFindEdge (MrcData, Iteration, ChBitMask, Ranks, GroupMask, Mid, High, 1, (INT8 *) VrefOffsets, DebugPrint);
    Redge[0] = Mid[0];
    Redge[1] = Mid[1];  // CountUp is 1 so return Low.
    //
    // Update Variables:
    //
    MRC_DEBUG_MSG (Debug, DebugLevel, "\nCH\tLeft\tRight\tWidth\tCenter");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((1 << Channel) & ChBitMask) == 0) {
        continue;
      }
      RankMask  = Ranks & ControllerOut->Channel[Channel].ValidRankBitMask;
      lWidth    = Redge[Channel] - Ledge[Channel];

      if ((Redge[Channel] == 127) && (Ledge[Channel] == 0)) {
        //
        // No errors found
        //
        MRC_DEBUG_MSG (Debug, DebugLevel, "\nNo Errors Found for C%u!\n", Channel);
        Center = MidPoint[Channel];
      } else {
        Center = (Ledge[Channel] + Redge[Channel] + 1) / 2;
        if (lWidth < MinWidth) {
          MRC_DEBUG_MSG (Debug, DebugLevel, "\nEye < %u for C%u!\n", MinWidth, Channel);
          Status = mrcMiscTrainingError;
        }
      }

      ShiftPIforCmdTraining (MrcData, Channel, Iteration, RankMask, GroupMask, Center, UpdateHost);

      MRC_DEBUG_MSG (
        Debug,
        DebugLevel,
        "\n %d\t%d\t%d\t%d\t%d",
        Channel,
        Ledge[Channel],
        Redge[Channel],
        lWidth,
        Center
        );
    } // for Channel
  }
  MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
  return Status;
}


/**
  Use a linear search to find the edges between Low and High
  if WrapAround = 0: Look for largest passing region between low and high
  if WrapAround = 1: Look for largest passing region, including wrapping from high to low

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Iteration   - Determines which PI to shift. Only MrcIterationClock is supported.
  @param[in]      chBitMask   - Valid Channel bit mask
  @param[in]      Ranks       - Valid Rank bit mask
  @param[in]      GroupMask   - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR3
  @param[in]      Low         - Low limit
  @param[in]      High        - High limit
  @param[in]      Step        - Step size
  @param[in]      WrapAllowed - Determines the search region
  @param[in]      VrefOffsets - Array of Vref offsets
  @param[in]      DebugPrint  - Switch to enable or disable debug printing
  @param[in]      SkipVref    - Skip changing CMD Vref offsets, only run test once at the current Vref.

  @retval MrcStatus -  If it succeeds return mrcSuccess
**/
MrcStatus
CmdLinearFindEdges (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Iteration,
  IN     UINT8                chBitMask,
  IN     UINT8                Ranks,
  IN     UINT8                GroupMask,
  IN     INT8                 Low[MAX_CHANNEL],
  IN     UINT8                High[MAX_CHANNEL],
  IN     UINT8                Step,
  IN     UINT8                WrapAllowed,
  IN     INT8                 *VrefOffsets,
  IN     BOOLEAN              DebugPrint,
  IN     BOOLEAN              SkipVref,
  IN     BOOLEAN              UpdateCenter
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcDebugMsgLevel   DebugLevel;
  INT32             *IPStart;
  INT32             *IPEnd;
  INT32             *CPStart;
  INT32             *CPEnd;
  INT32             *LPStart;
  INT32             *LPEnd;
  MrcStatus         Status;
  BOOLEAN           Pass;
  BOOLEAN           Lpddr;
  INT32             InitialPassingStart[MAX_CHANNEL];
  INT32             InitialPassingEnd[MAX_CHANNEL];
  INT32             CurrentPassingStart[MAX_CHANNEL];
  INT32             CurrentPassingEnd[MAX_CHANNEL];
  INT32             LargestPassingStart[MAX_CHANNEL];
  INT32             LargestPassingEnd[MAX_CHANNEL];
  INT32             lWidth;
  INT32             iWidth;
  INT32             cWidth;
  INT32             Center;
  INT16             LCTDelay;
  INT16             LCTMin;
  INT16             LCTMax;
  UINT8             Channel;
  UINT8             ChannelMask;
  UINT8             LocalchBitMask;
  UINT8             RankMask;
  UINT8             Rank;
  UINT8             LCTStep;
  UINT8             LastStep;
  UINT8             Vloop;
  UINT8             ChError;
  UINT8             DumArr[7];
  UINT8             ChannelClkPiCode[MAX_CHANNEL];
  INT8              Vref;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  lWidth        = 0;
  iWidth        = 0;
  cWidth        = 0;
  MrcCall->MrcSetMem (DumArr, sizeof (DumArr), 1);
  MrcCall->MrcSetMem (ChannelClkPiCode, sizeof (ChannelClkPiCode), 0);
  DebugLevel = DebugPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;

  if (Iteration != MrcIterationClock) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "CmdLinearFindEdges: Unknown Iteration Parameter\n");
    return mrcWrongInputParameter;
  }

  //
  // Check if LPDDR3 memory is used
  //
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);

  // Save the Cached Channel Clk PI Code for updating the centered value
  if (UpdateCenter) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((1 << Channel) & chBitMask) {
        RankMask = Ranks & ControllerOut->Channel[Channel].ValidRankBitMask;
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if ((1 << Rank) & RankMask) {
            ChannelClkPiCode[Channel] = ControllerOut->Channel[Channel].ClkPiCode[Rank];
            break;
          }
        }
      }
    }
  }


  // Allow for the full sweep range between channels
  LCTMin = MIN (Low[0], Low[1]);
  LCTMax = MAX (High[0], High[1]);
  LCTStep = (Lpddr) ? 2 : Step;

  MRC_DEBUG_MSG (Debug, DebugLevel, "CLkDlay\t\t0 1");

  for (LCTDelay = LCTMin; LCTDelay <= LCTMax; LCTDelay += LCTStep) {
    //
    // Update Timing
    //
    LocalchBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((1 << Channel) & chBitMask) &&
          ((LCTDelay >= Low[Channel]) && (LCTDelay <= High[Channel]))) {
        RankMask = Ranks & ControllerOut->Channel[Channel].ValidRankBitMask;
        LocalchBitMask |= 1 << Channel;
        ShiftPIforCmdTraining (MrcData, Channel, Iteration, RankMask, GroupMask, LCTDelay, 0);
      }
    }
    //
    // Reset DDR
    //
    Status = MrcResetSequence (MrcData);

    //
    // Run REUT until both channels fail or we finish all Vref points
    //
    if (SkipVref) {
      ChError = RunIOTest (MrcData, LocalchBitMask, Outputs->DQPat, DumArr, 1, 0);
    } else {
      ChError = 0;
      for (Vloop = 0; Vloop < 2; Vloop++) {
        Vref = VrefOffsets[Vloop];
        UpdateVrefWaitTilStable (MrcData, 2, 0, Vref, 0, 0, FALSE, 0);
        if (Inputs->CaVrefConfig == 2) {
          UpdateVrefWaitTilStable (MrcData, 3, 0, Vref, 0, 0, FALSE, 0);
        }

        ChError |= RunIOTest (MrcData, LocalchBitMask, Outputs->DQPat, DumArr, 1, 0);

        if (ChError == LocalchBitMask) {
          break;
        }

      }
    }

    MRC_DEBUG_MSG (Debug, DebugLevel, "\n %d\t\t", LCTDelay);

    //
    // Update Passing Variables
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelMask = MRC_BIT0 << Channel;
      if (!(ChannelMask & chBitMask)) {
        MRC_DEBUG_MSG (Debug, DebugLevel, (Channel == 0) ? "  " : "");
        continue;
      }

      if ((LCTDelay >= Low[Channel]) && (LCTDelay <= High[Channel])) {
        Pass = !(ChError & ChannelMask);
      } else {
        Pass = FALSE;
      }

      MRC_DEBUG_MSG (Debug, DebugLevel, Pass ? ". " : "# ");

      IPStart = &InitialPassingStart[Channel];
      IPEnd   = &InitialPassingEnd[Channel];
      CPStart = &CurrentPassingStart[Channel];
      CPEnd   = &CurrentPassingEnd[Channel];
      LPStart = &LargestPassingStart[Channel];
      LPEnd   = &LargestPassingEnd[Channel];

      if (LCTDelay == LCTMin) {
        if (Pass) {
          *IPStart = *IPEnd = *CPStart = *CPEnd = *LPStart = *LPEnd = Low[Channel];
        } else {
          *IPStart = *IPEnd = *CPStart = *CPEnd = *LPStart = *LPEnd = Low[Channel] - LCTStep;
        }
      } else {
        if (Pass) {
          //
          // Update Initial variables
          //
          if (*IPEnd == (LCTDelay - LCTStep)) {
            *IPEnd = LCTDelay; // In passing region
          }
          //
          // Update Current variables
          //
          if (*CPEnd == (LCTDelay - LCTStep)) {
            *CPEnd = LCTDelay; // In passing region
          } else {
            *CPStart = *CPEnd = LCTDelay;
          }
          //
          // Special case for last step: Append Initial Passing Region
          // LCTDelay should be considered a continuous range that wraps around 0
          //
          LastStep = DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MAX - LCTStep;
          if ((LCTDelay >= LastStep) && (*IPStart == 0) && WrapAllowed) {
            iWidth = *IPEnd -*IPStart;
            *CPEnd += (LCTStep + iWidth);
          }
          //
          // Update Largest variables
          //
          cWidth = *CPEnd - *CPStart;
          lWidth = *LPEnd - *LPStart;
          if (cWidth > lWidth) {
            *LPStart = *CPStart;
            *LPEnd   = *CPEnd;
          }
        }
      }
    } // for Channel
  } // for LCTDelay

  MRC_DEBUG_MSG (Debug, DebugLevel, "\nCH\tLeft\tRight\tWidth\tCenter\n");

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((MRC_BIT0 << Channel) & chBitMask) {
      LPStart = &LargestPassingStart[Channel];
      LPEnd   = &LargestPassingEnd[Channel];
      lWidth  = *LPEnd - *LPStart;
      Center = (*LPEnd + *LPStart) / 2;
      if (lWidth < (3 * LCTStep)) {
        MRC_DEBUG_MSG (Debug, DebugLevel, "\nERROR! Bad command eye width: %u\n", lWidth);
        if (lWidth == 0) {
          *LPStart = *LPEnd = 0;
        }
#ifndef MRC_MINIBIOS_BUILD
        if (Inputs->ExitOnFailure) {
          return mrcMiscTrainingError;
        }
#endif // MRC_MINIBIOS_BUILD
      }
      RankMask = Ranks & ControllerOut->Channel[Channel].ValidRankBitMask;
      if (UpdateCenter) {
        //
        // Shift Timing
        //
        ShiftPIforCmdTraining (MrcData, Channel, Iteration, RankMask, GroupMask, Center - ChannelClkPiCode[Channel], 1);
      }

      MRC_DEBUG_MSG (
        Debug,
        DebugLevel,
        " %d\t%d\t%d\t%d\t%d\n",
        Channel,
        *LPStart,
        *LPEnd,
        lWidth,
        Center
        );

      //
      // Determine in which rank to save the margins...
      //
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((1 << Rank) & RankMask) {
          Outputs->MarginResult[LastCmdT][Rank][Channel][0][0] = 10 * ABS (*LPStart);
          Outputs->MarginResult[LastCmdT][Rank][Channel][0][1] = 10 * ABS (*LPEnd);
        }
      }
    }
  }
  //
  // Clean Up
  //
  if (!SkipVref) {
    UpdateVrefWaitTilStable (MrcData, 2, 0, 0, 0, 0, FALSE, 0);
    if (Inputs->CaVrefConfig == 2) {
      UpdateVrefWaitTilStable (MrcData, 3, 0, 0, 0, 0, FALSE, 0);
    }
  }

  Status = MrcResetSequence (MrcData);
  return Status;
}

/**
  Use a binary search to find the edge between Low and High
  High and Low track passing points
  if CountUp: Low is a passing point and need to count up to find a failing point
  if CountDn: High is a passing point and need to count dn to find a failing point

  @param[in]      MrcData     - Include all MRC global data.
  @param[in]      Iteration   - Determines which PI to shift
  @param[in]      ChBitMask   - Valid Channel bit mask
  @param[in]      Ranks       - Valid Rank bit mask
  @param[in]      GroupMask   - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR3
  @param[in, out] Low         - Low limit
  @param[in, out] High        - High limit
  @param[in]      CountUp     - The direction to search
  @param[in]      VrefOffsets - Array of Vref offsets
  @param[in]      DebugPrint  - Switch to enable or disable debug printing

  @retval Nothing
**/
void
CmdBinaryFindEdge (
  IN     MrcParameters *const MrcData,
  IN     UINT8                Iteration,
  IN     UINT8                ChBitMask,
  IN     UINT8                Ranks,
  IN     UINT8                GroupMask,
  IN OUT UINT8                *Low,
  IN OUT UINT8                *High,
  IN     UINT8                CountUp,
  IN     INT8                 *VrefOffsets,
  IN     BOOLEAN              DebugPrint
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcDebugMsgLevel  DebugLevel;
  UINT8             Target[MAX_CHANNEL];
  UINT8             Done;
  UINT8             ChError;
  UINT8             DumArr[7];
  INT8              Vref;
  UINT8             Channel;
  UINT8             ChannelMask;
  UINT8             RankMask;
  UINT8             Group;
  UINT8             Fail;
  UINT8             Vloop;
  BOOLEAN           SkipWait;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Done          = 0;
  ChError       = 0;
  DebugLevel    = DebugPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  MrcCall->MrcSetMem (Target, sizeof (Target), 0);
  MrcCall->MrcSetMem (DumArr, sizeof (DumArr), 1);

  SkipWait = FALSE;

  MRC_DEBUG_MSG (Debug, DebugLevel, "CmdTgt\nCh0G0\tCh0G1\tCh1G0\tCh1G1\n");

  while (!Done) {
    //
    // Update Timing
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((1 << Channel) & ChBitMask) == 0) {
        MRC_DEBUG_MSG (Debug, DebugLevel, "\t");
      } else {
        Target[Channel] = (High[Channel] + Low[Channel] + CountUp) / 2;    // CountUp gets rounding correct
        RankMask = Ranks & ControllerOut->Channel[Channel].ValidRankBitMask;
        for (Group = 0; Group < 2; Group++) {
          if (((1 << Group) & GroupMask) == 0) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "\t");
          } else {
            ShiftPIforCmdTraining (MrcData, Channel, Iteration, RankMask, 1 << Group, Target[Channel], 0);
            MRC_DEBUG_MSG (Debug, DebugLevel, "%d\t", Target[Channel]);
          }
        }
      }
    }

    MRC_DEBUG_MSG (Debug, DebugLevel, "\t");

    //
    // Run REUT until both channels fail or we finish all Vref points
    //
    ChError = 0;
    for (Vloop = 0; Vloop < 2; Vloop++) {
      Vref = VrefOffsets[Vloop];
      //
      // MRC_DEBUG_MSG (Debug, DebugLevel, "**** Run REUT until both channels fail or we finish all Vref points, Vref = %d\n", Vref);
      //
      UpdateVrefWaitTilStable (MrcData, 2, 0, Vref, 0, 0, FALSE, SkipWait);
      if (Inputs->CaVrefConfig == 2) {
        UpdateVrefWaitTilStable (MrcData, 3, 0, Vref, 0, 0, FALSE, SkipWait);
      }

      ChError |= RunIOTest (MrcData, ChBitMask, Outputs->DQPat, DumArr, 1, 0);
      if (ChError == ChBitMask) {
        break;
      }

    }

    //
    // Update High/Low
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelMask = 1 << Channel;
      if (!(ChannelMask & ChBitMask)) {
        MRC_DEBUG_MSG (Debug, DebugLevel, (Channel == 0) ? "  " : "");
      } else {
        Fail = (ChError & ChannelMask);

        MRC_DEBUG_MSG (Debug, DebugLevel, Fail ? "# " : ". ");

        //
        // Skip if this channel is done
        //
        if (High[Channel] > Low[Channel]) {
          if (CountUp) {
            if (Fail) {
              High[Channel] = Target[Channel] - 1;
            } else {
              Low[Channel] = Target[Channel];
            }
          } else {
            if (Fail) {
              Low[Channel] = Target[Channel] + 1;
            } else {
              High[Channel] = Target[Channel];
            }
          }
        }
      }
    }

    if ((ChError & ChBitMask) != 0) {
      //
      // Perform JEDEC Reset/Init if at least one of the channels failed this PI iteration
      //
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "Failed, doing JEDEC Reset..\n");
      MrcResetSequence (MrcData);
    }

    //
    // Update Done
    //
    Done = 1;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((1 << Channel) & ChBitMask) {
        if (High[Channel] > Low[Channel]) {
          Done = 0;
        }
      }
    }

    MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
  }
  //
  // Clean Up
  //
  UpdateVrefWaitTilStable (MrcData, 2, 0, 0, 0, 0, FALSE, SkipWait);
  if (Inputs->CaVrefConfig == 2) {
    UpdateVrefWaitTilStable (MrcData, 3, 0, 0, 0, 0, FALSE, SkipWait);
  }

  MrcResetSequence (MrcData);
  return;
}

/**
  Shift the CLK/CMD/CTL Timing by the given PI setting value
  CLK shift will also change RcvEn / TxDq / TxDqs.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Channel    - Channel to shift
  @param[in] Offset     - Offset to shift by
  @param[in] UpdateHost - Switch to update the host structure

  @retval Nothing
**/
void
ShiftChannelTiming (
  IN MrcParameters *const MrcData,
  IN UINT8                Channel,
  IN INT32                Offset,
  IN UINT8                UpdateHost,
  IN BOOLEAN              MsgPrint
  )
{
  MrcDebug            *Debug;
  const MrcInput      *Inputs;
  const MrcChannelIn  *ChannelIn;
  MrcOutput           *Outputs;
  MrcChannelOut       *ChannelOut;
  INT32               NewCode;
  UINT8               Rank;
  UINT8               RankBit;
  UINT8               Group;
  BOOLEAN             Lpddr;
  MrcDebugMsgLevel    DebugLevel;
  UINT32              RegOffset;
  MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_STRUCT MiscCkeCtrl;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  ChannelIn   = &Inputs->Controller[0].Channel[Channel];
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  DebugLevel  = MsgPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  MRC_DEBUG_MSG (Debug, DebugLevel, "Channel %d new values:\n", Channel);

  //
  // Check if LPDDR3 memory is used
  //
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);

  //
  // Shift the CLK/CTL Timing
  //
  MRC_DEBUG_MSG (Debug, DebugLevel, "\t%sCTL\n", Lpddr ? "" : "CLK\t");
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
      MRC_DEBUG_MSG (Debug, DebugLevel, " R%d", Rank);
      RankBit = 1 << Rank;
      NewCode = ChannelOut->ClkPiCode[Rank] + Offset;
      if (!Lpddr) {
        //
        // CLK is per Rank in DDR3/4
        //
        if (Inputs->Ddr4DdpSharedClock && (Rank == 1)) {  // Clocks are shared, so only shift rank 0
          MRC_DEBUG_MSG (Debug, DebugLevel, "\t--");
        } else {
          if (Inputs->Ddr4DdpSharedClock) {  // Shift DQ's on both ranks
            RankBit = 3;
          }
          ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, RankBit, RankBit, Offset, UpdateHost);
          RankBit = 1 << Rank;
          MRC_DEBUG_MSG (Debug, DebugLevel, "\t%d", NewCode);
        }
      }

      NewCode = ChannelOut->CtlPiCode[Rank] + Offset;
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, RankBit, 1, NewCode, UpdateHost);
      MRC_DEBUG_MSG (Debug, DebugLevel, "\t%d\n", NewCode);
    }
  }

  //
  // Shift the CMD Timing
  //
  NewCode = ChannelOut->CmdsCmdPiCode[0] + Offset;
  ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, ChannelOut->ValidRankBitMask, 1, NewCode, UpdateHost);
  MRC_DEBUG_MSG (Debug, DebugLevel, " New CMDS[0] value = %d\n", NewCode);

  if (Lpddr) {
    // Lower CKE, we will change CLK PI while DRAM is in Power Down
    MiscCkeCtrl.Data = 0;
    MiscCkeCtrl.Bits.CKE_Override = 0x0F;
    MiscCkeCtrl.Bits.CKE_On = 0;
    RegOffset = OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG, MCHBAR_CH1_CR_REUT_CH_MISC_CKE_CTRL_REG, Channel);
    MrcWriteCR(MrcData, RegOffset, MiscCkeCtrl.Data);
    //
    // CLK is per Group in LPDDR3
    //
    for (Group = 0; Group < 2; Group++) {
      if (ChannelIn->DQByteMap[MrcIterationClock][Group] != 0) {
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, 0, 1 << Group, Offset, UpdateHost);
        MRC_DEBUG_MSG (Debug, DebugLevel, " New CLK%d value = %d\n", Group, ChannelOut->ClkPiCode[Group]);
      }
    }
    // Restore CKE (exit Power Down)
    MiscCkeCtrl.Bits.CKE_On = ChannelOut->ValidCkeBitMask;
    RegOffset = OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG, MCHBAR_CH1_CR_REUT_CH_MISC_CKE_CTRL_REG, Channel);
    MrcWriteCR (MrcData, RegOffset, MiscCkeCtrl.Data);

    NewCode = ChannelOut->CkeCmdPiCode[0] + Offset;
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCke, ChannelOut->ValidRankBitMask, 1, NewCode, UpdateHost);
    MRC_DEBUG_MSG (Debug, DebugLevel, " New CKE[0] value = %d\n", NewCode);

    NewCode = ChannelOut->CmdsCmdPiCode[1] + Offset;
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, ChannelOut->ValidRankBitMask, 2, NewCode, UpdateHost);
    MRC_DEBUG_MSG (Debug, DebugLevel, " New CMDS[1] value = %d\n", NewCode);

    NewCode = ChannelOut->CmdnCmdPiCode[1] + Offset;
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdN, ChannelOut->ValidRankBitMask, 2, NewCode, UpdateHost);
    MRC_DEBUG_MSG (Debug, DebugLevel, " New CMDN[1] value = %d\n", NewCode);
  } else {
    NewCode = ChannelOut->CmdnCmdPiCode[0] + Offset;
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdN, ChannelOut->ValidRankBitMask, 1, NewCode, UpdateHost);
    MRC_DEBUG_MSG (Debug, DebugLevel, " New CMDN[0] value = %d\n", NewCode);
  }
  return;
}

/**
  This function updates Command Mode register, tXP and Roundtrip latency.
  This should only be called for DDR3/4.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Channel     - Channel to perform update to
  @param[in]      OldN        - Old N Mode value
  @param[in]      NewN        - New N mode value

  @retval Nothing
**/
void
UpdateCmdNTiming (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                OldN,
  IN     UINT8                NewN
  )
{
  MrcDebug                            *Debug;
  MrcOutput                           *Outputs;
  MrcChannelOut                       *ChannelOut;
  MrcTiming                           *Timing;
  MCHBAR_CH0_CR_SC_GS_CFG_STRUCT      ScGsCfg;
  MCHBAR_CH0_CR_TC_PWRDN_STRUCT       TcPwrdn;
  UINT32                              Offset;
  UINT32                              Value;
  UINT8                               Rank;
  INT8                                Diff;

  Outputs    = &MrcData->Outputs;
  Debug      = &Outputs->Debug;
  ChannelOut = &Outputs->Controller[0].Channel[Channel];
  Timing     = &ChannelOut->Timing[MrcData->Inputs.MemoryProfile];

  //
  // Update Cmd NMode, till now we ran DDR3/4 at 3N
  // If we are in 1N mode, set Command Rate Limit to 3
  //
  Offset = MCHBAR_CH0_CR_SC_GS_CFG_REG + ((MCHBAR_CH1_CR_SC_GS_CFG_REG - MCHBAR_CH0_CR_SC_GS_CFG_REG) * Channel);
  ScGsCfg.Data = MrcReadCR (MrcData, Offset);
  if (Timing->NMode == 1) {
    Value = MrcData->Inputs.EnCmdRate;
    if (Value == 0) {
      ScGsCfg.Bits.CMD_stretch = 0;    // 1N Mode
    } else {
      ScGsCfg.Bits.CMD_stretch = 3;    // N:1 Mode
      ScGsCfg.Bits.N_to_1_ratio = Value;
    }
  } else {
    ScGsCfg.Bits.CMD_stretch = Timing->NMode - 1;
  }
  MrcWriteCR (MrcData, Offset, ScGsCfg.Data);

  //
  // Adjust tXP value - it depends on NMode
  //
  Offset = MCHBAR_CH0_CR_TC_PWRDN_REG + ((MCHBAR_CH1_CR_TC_PWRDN_REG - MCHBAR_CH0_CR_TC_PWRDN_REG) * Channel),
  TcPwrdn.Data = MrcReadCR (MrcData, Offset);
  Value = tXPValue (Outputs->DdrType, Outputs->Frequency, Timing->tCK, (UINT8) Timing->NMode);
  TcPwrdn.Bits.tXP = RANGE (Value, tXP_MIN, tXP_MAX);
  MrcWriteCR (MrcData, Offset, TcPwrdn.Data);

  //
  // Adjust Roundtrip Latency - it depends on NMode
  //
  Diff = (NewN - OldN);
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
      ChannelOut->RTLatency[Rank] = ChannelOut->RTLatency[Rank] + Diff;
    }
  }
  MrcHalSetRoundtripLatency (MrcData, Channel);

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Ch%u: SC_GS_CFG = %Xh\n TC_PWRDN.tXP = %u\n SC_ROUNDTRIP_LATENCY = %08Xh\n",
    Channel,
    ScGsCfg.Data,
    TcPwrdn.Bits.tXP,
    MrcHalGetRoundtripLatency (MrcData, Channel)
    );
}

/**
  Enter / exit LPDDR3 CA training modes.
  Main flow:
  1. Force CKE high.
  2. Send MRW 41, 48 or 42.
  3. Force CKE low for MRW 41 or 48

  @param[in] MrcData      - The MRC global data.
  @param[in] ChBitMask    - channels to work on.
  @param[in] RankBitMask  - ranks to work on.
  @param[in] Mode         - CA training mode.

  @retval mrcSuccess if succeeded
**/
MrcStatus
LpddrCommandTrainingMode (
  IN MrcParameters * const MrcData,
  IN UINT8                 ChBitMask,
  IN UINT8                 RankBitMask,
  IN MrcCaTrainingMode     Mode
  )
{
  MrcStatus         Status;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  UINT8             Channel;
  UINT8             Rank;
  UINT32            Offset;
  UINT32            Address;
  UINT32            Data;
  BOOLEAN           InitMrw;
  BOOLEAN           ChipSelect2N;
  MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_STRUCT MiscCkeCtrl;

  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];

  InitMrw = TRUE;
  ChipSelect2N = FALSE;

  switch (Mode) {
    case CaTrainingMode41:
      Address = 0x29;
      Data    = 0xA4;   // Data is selected so that High and Low phases of CA[9:0] are equal
      break;

    case CaTrainingMode48:
      Address = 0x30;
      Data    = 0xC0;
      break;

    case CaTrainingMode42:
      Address = 0x2A;
      Data    = 0xA8;
      ChipSelect2N = FALSE;
      break;

    default:
      return mrcFail;
  }

  //
  // Send the MRW41 command to populated ranks
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (((1 << Channel) & ChBitMask) == 0) {
      continue;
    }

    //
    // Force CKE high
    //
    MiscCkeCtrl.Data = 0;
    MiscCkeCtrl.Bits.CKE_Override = 0x0F;
    MiscCkeCtrl.Bits.CKE_On       = ControllerOut->Channel[Channel].ValidCkeBitMask;
    Offset = MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG +
      (MCHBAR_CH1_CR_REUT_CH_MISC_CKE_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG) * Channel;
    MrcWriteCR (MrcData, Offset, MiscCkeCtrl.Data);

    //
    // Wait for CKE to become effective
    //
    MrcWait (MrcData, 1 * HPET_MIN);

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank ++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      if (((1 << Rank) & RankBitMask) != 0) {
        Status = MrcIssueMrw (MrcData, Channel, Rank, Address, Data, InitMrw, ChipSelect2N, FALSE);
        if (Status != mrcSuccess) {
          return Status;
        }
      }
    }

    //
    // Force CKE Low for MRW 41 or 48
    //
    if (Mode != CaTrainingMode42) {
      //
      // Wait tCACKEL = 10 tCK
      //
      MrcWait (MrcData, 1 * HPET_MIN);

      //
      // Force CKE low, tCACKEL after MRW41 issued
      //
      MiscCkeCtrl.Bits.CKE_On = 0;
      MrcWriteCR (MrcData, Offset, MiscCkeCtrl.Data);
    }
  }  // for Channel
  return mrcSuccess;
}

/**
  Program CADB Pattern Buffers with given values

  @param[in] MrcData    - The MRC global data.
  @param[in] Channel    - channel to work on.
  @param[in] PatBuf0    - Pattern Buffer 0 value
  @param[in] PatBuf1    - Pattern Buffer 1 value
  @param[in] PatBuf2    - Pattern Buffer 2 value

**/
void
SetCadbPatternBuffers (
  IN MrcParameters * const  MrcData,
  IN UINT8                  Channel,
  IN UINT32                 PatBuf0,
  IN UINT32                 PatBuf1,
  IN UINT32                 PatBuf2
  )
{
  UINT32 Offset;

  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_0_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_PB_0_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_0_REG) * Channel);
  MrcWriteCR (MrcData, Offset, PatBuf0);

  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_1_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_PB_1_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_1_REG) * Channel);
  MrcWriteCR (MrcData, Offset, PatBuf1);

  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_2_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_PB_2_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_2_REG) * Channel);
  MrcWriteCR (MrcData, Offset, PatBuf2);
}

//
//  Sets up 4 CADB lines that will be used to send out a CS / CA pattern.
//
//  -----------------------
//  CADB  Phase  Phase  CS
//  Line  High   Low
//  -----------------------
//   0    0x000  0x000  Off
//   1    0x3FF  0x3FF  Off
//   2    0x2AA  0x2AA  On
//   3    0x155  0x155  On
//
//  The CS pattern uses Pattern Buffer and hence has 24 lines, with CS active for one line only.
//  This will send a command every 24 DCLKs.
//
//  Pattern Buffer details:
//  The line order is:    0, 0, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//  or different command: 0, 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//
//  000
//  000
//  000
//  000
//
//  000
//  000
//  000
//  000
//
//  000
//  000
//  000
//  000
//
//  000
//  000
//  000
//  000
//
//  000
//  000
//  000
//  000
//
//  001
//  001
//  010 or 011
//  000
//  ----
//  000  --> PB[0] = 0x300000 or 0x700000
//  000      PB[1] = 0x400000
//  000      PB[2] = 0x000000
//  043 or 047
//
CADB_LINE CadbLinesCs[] = {
  { 0x000, 0x000, 0 },
  { 0x3FF, 0x3FF, 0 },
  { 0x2AA, 0x2AA, 1 },
  { 0x155, 0x155, 1 }
};

/**
  Setup the CADB for CS or CA training.

  @param[in] MrcData    - The MRC global data.
  @param[in] Channel    - channel to work on
  @param[in] Rank       - rank to work on
  @param[in] CadbLines  - CADB lines to program
  @param[in] CadbCount  - Number of CADB lines to program
  @param[in] PatBuf0    - Pattern Buffer 0 value
  @param[in] PatBuf1    - Pattern Buffer 1 value
  @param[in] PatBuf2    - Pattern Buffer 2 value
**/
void
SetupCaTrainingCadb (
  IN MrcParameters  * const MrcData,
  IN UINT8          Channel,
  IN UINT8          Rank,
  IN CADB_LINE      *CadbLines,
  IN UINT32         CadbCount,
  IN UINT32         PatBuf0,
  IN UINT32         PatBuf1,
  IN UINT32         PatBuf2
  )
{
  UINT32 Offset;
  UINT32 MA;
  UINT32 BA;
  UINT32 CMD;
  UINT32 i;

  MCHBAR_CH0_CR_REUT_CH_PAT_CADB_WRITE_POINTER_STRUCT   ReutChPatCadbWritePointer;
  MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_CTRL_STRUCT        ReutChPatCadbMuxCtrl;
  MCHBAR_CH0_CR_REUT_CH_PAT_CADB_PROG_STRUCT            ReutChPatCadbProg;

  //
  // Set Mux0/1/2 to Pattern Buffer mode
  //
  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_CTRL_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_CTRL_REG) * Channel);
  ReutChPatCadbMuxCtrl.Data = MrcReadCR (MrcData, Offset);
  ReutChPatCadbMuxCtrl.Bits.Mux0_Control = 1;
  ReutChPatCadbMuxCtrl.Bits.Mux1_Control = 1;
  ReutChPatCadbMuxCtrl.Bits.Mux2_Control = 1;
  MrcWriteCR (MrcData, Offset, ReutChPatCadbMuxCtrl.Data);

  //
  // Program Pattern Buffers for a specific progression over CADB,
  // according to the given Pattern Buffer values
  //
  SetCadbPatternBuffers (MrcData, Channel, PatBuf0, PatBuf1, PatBuf2);

  //
  // Start writing at CADB row 0
  //
  ReutChPatCadbWritePointer.Data = 0;
  ReutChPatCadbWritePointer.Bits.Write_Enable = 1;
  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_WRITE_POINTER_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_WRITE_POINTER_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_WRITE_POINTER_REG) * Channel);
  MrcWriteCR (MrcData, Offset, ReutChPatCadbWritePointer.Data);

  ReutChPatCadbProg.Data = 0;
  ReutChPatCadbProg.Bits.CADB_Data_ODT = (0 << Rank);
  ReutChPatCadbProg.Bits.CADB_Data_CKE = (0 << Rank);

  //
  // Program the CADB lines
  //
  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_PROG_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_PROG_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_PROG_REG) * Channel);
  for (i = 0; i < CadbCount ; i++) {
    MrcConvertLpddr2Ddr (CadbLines[i].CaHigh, CadbLines[i].CaLow, &MA, &BA, &CMD);
    ReutChPatCadbProg.Bits.CADB_Data_Address  = MA;
    ReutChPatCadbProg.Bits.CADB_Data_Bank     = BA;
    ReutChPatCadbProg.Bits.CADB_Data_Control  = CMD;
    ReutChPatCadbProg.Bits.CADB_Data_CS       = 0x0F & ~(CadbLines[i].ChipSelect << Rank);

    //
    // Write CADB line. It is auto incremented after every write
    //
    MrcWriteCR64 (MrcData, Offset, ReutChPatCadbProg.Data);
  }
}

/**
  Program DESWIZZLE_HIGH/LOW registers for MR4 decoding

  @param[in] MrcData - The MRC global data.

**/
void
ProgramDeswizzleRegisters (
  IN MrcParameters * const  MrcData
  )
{
  MrcInput          *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcChannelIn      *ChannelIn;
  MrcChannelOut     *ChannelOut;
  MrcControllerOut  *ControllerOut;
  UINT8             Channel;
  UINT32            Byte;
  UINT8             Bit;
  UINT32            Offset;
  MCHBAR_CH0_CR_DESWIZZLE_LOW_STRUCT  DeswizzleLow;
  MCHBAR_CH0_CR_DESWIZZLE_HIGH_STRUCT DeswizzleHigh;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelIn = &Inputs->Controller[0].Channel[Channel];
    ChannelOut = &ControllerOut->Channel[Channel];

    DeswizzleLow.Data   = 0;
    DeswizzleHigh.Data  = 0;

    for (Byte = 0; Byte <= 7; Byte++) {
      //
      // DqsMapCpu2Dram maps CPU bytes to DRAM, we need to find the reverse mapping here
      //
      switch (ChannelIn->DqsMapCpu2Dram[Byte]) {
        case 0:
          DeswizzleLow.Bits.Byte_0  = Byte;
          break;
        case 2:
          DeswizzleLow.Bits.Byte_2  = Byte;
          break;
        case 4:
          DeswizzleHigh.Bits.Byte_4 = Byte;
          break;
        case 6:
          DeswizzleHigh.Bits.Byte_6 = Byte;
          break;
      }
    }

    for (Bit = 0; Bit <= 7; Bit++) {
      //
      // DqMapCpu2Dram maps CPU DQ pins to DRAM, we need to find the reverse mapping here
      //
      Byte = DeswizzleLow.Bits.Byte_0;
      switch (ChannelIn->DqMapCpu2Dram[Byte][Bit]) {
        case 0:
          DeswizzleLow.Bits.Bit_0 = Bit;
          break;
        case 1:
          DeswizzleLow.Bits.Bit_1 = Bit;
          break;
        case 2:
          DeswizzleLow.Bits.Bit_2 = Bit;
          break;
      }

      Byte = DeswizzleLow.Bits.Byte_2;
      switch (ChannelIn->DqMapCpu2Dram[Byte][Bit]) {
        case 16:
          DeswizzleLow.Bits.Bit_16 = Bit;
          break;
        case 17:
          DeswizzleLow.Bits.Bit_17 = Bit;
          break;
        case 18:
          DeswizzleLow.Bits.Bit_18 = Bit;
          break;
      }

      Byte = DeswizzleHigh.Bits.Byte_4;
      switch (ChannelIn->DqMapCpu2Dram[Byte][Bit]) {
        case 32:
          DeswizzleHigh.Bits.Bit_32 = Bit;
          break;
        case 33:
          DeswizzleHigh.Bits.Bit_33 = Bit;
          break;
        case 34:
          DeswizzleHigh.Bits.Bit_34 = Bit;
          break;
      }

      Byte = DeswizzleHigh.Bits.Byte_6;
      switch (ChannelIn->DqMapCpu2Dram[Byte][Bit]) {
        case 48:
          DeswizzleHigh.Bits.Bit_48 = Bit;
          break;
        case 49:
          DeswizzleHigh.Bits.Bit_49 = Bit;
          break;
        case 50:
          DeswizzleHigh.Bits.Bit_50 = Bit;
          break;
      }
    } // for Bit

    if (ChannelOut->Dimm[dDIMM0].SdramWidth == 32) {
      //
      // Bytes 2 and 6 (and their bits) are irrelevant for x32 devices - copy from Bytes 0 and 4 instead
      //
      DeswizzleLow.Bits.Byte_2 = DeswizzleLow.Bits.Byte_0;
      DeswizzleLow.Bits.Bit_16 = DeswizzleLow.Bits.Bit_0;
      DeswizzleLow.Bits.Bit_17 = DeswizzleLow.Bits.Bit_1;
      DeswizzleLow.Bits.Bit_18 = DeswizzleLow.Bits.Bit_2;

      DeswizzleHigh.Bits.Byte_6 = DeswizzleHigh.Bits.Byte_4;
      DeswizzleHigh.Bits.Bit_48 = DeswizzleHigh.Bits.Bit_32;
      DeswizzleHigh.Bits.Bit_49 = DeswizzleHigh.Bits.Bit_33;
      DeswizzleHigh.Bits.Bit_50 = DeswizzleHigh.Bits.Bit_34;
    }

    Offset = MCHBAR_CH0_CR_DESWIZZLE_LOW_REG +
      (MCHBAR_CH1_CR_DESWIZZLE_LOW_REG - MCHBAR_CH0_CR_DESWIZZLE_LOW_REG) * Channel;
    MrcWriteCR (MrcData, Offset, DeswizzleLow.Data);

    Offset = MCHBAR_CH0_CR_DESWIZZLE_HIGH_REG +
      (MCHBAR_CH1_CR_DESWIZZLE_HIGH_REG - MCHBAR_CH0_CR_DESWIZZLE_HIGH_REG) * Channel;
    MrcWriteCR (MrcData, Offset, DeswizzleHigh.Data);

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Ch%d DESWIZZLE_HIGH=%08X, DESWIZZLE_LOW=%08X\n",
      Channel,
      DeswizzleHigh.Data,
      DeswizzleLow.Data
      );
  } // for Channel
}


/**
  This routine is used throughout LPDDR3 ECT code to initialize DDR IO for CA training.
  Enable the following bits because we will use DATATRAINFEEDBACK to read back CA values on DQ pins:
    DataControl0.SenseampTrainingMode and ForceOdtOn
    DataControl2.ForceRxOn and ForceBiasOn

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
LpddrCaTrainingInitIo (
  IN MrcParameters * const  MrcData
  )
{
  MrcIntOutput        *MrcIntData;
  MrcOutput           *Outputs;
  MrcIntControllerOut *IntControllerOut;
  MrcIntChannelOut    *IntChannelOut;
  UINT8               Channel;
  UINT8               Byte;
  UINT32              Offset;
  DDRDATACH0_CR_DDRCRDATACONTROL0_STRUCT    DdrCrDataControl0;
  DDRDATA0CH0_CR_DDRCRDATACONTROL2_STRUCT   DdrCrDataControl2;

  Outputs           = &MrcData->Outputs;
  MrcIntData        = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntControllerOut  = &MrcIntData->Controller[0];

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    IntChannelOut = &IntControllerOut->Channel[Channel];
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      DdrCrDataControl2.Data = IntChannelOut->DqControl2[Byte].Data;
      DdrCrDataControl2.Bits.ForceBiasOn = 1;
      DdrCrDataControl2.Bits.ForceRxOn   = 1;
      Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
      MrcWriteCR (MrcData, Offset, DdrCrDataControl2.Data);
    }
    DdrCrDataControl0.Data = IntChannelOut->DqControl0.Data;
    DdrCrDataControl0.Bits.ForceOdtOn           = 1;
    DdrCrDataControl0.Bits.SenseampTrainingMode = 1;
    Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
    MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);
  }
}

/**
  This routine is used throughout LPDDR3 ECT code to restore DDR IO from CA training.

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
LpddrCaTrainingRestoreIo (
  IN MrcParameters * const  MrcData
  )
{
  MrcIntOutput        *MrcIntData;
  MrcOutput           *Outputs;
  MrcIntControllerOut *IntControllerOut;
  MrcIntChannelOut    *IntChannelOut;
  UINT8               Channel;
  UINT8               Byte;
  UINT32              Offset;

  Outputs           = &MrcData->Outputs;
  MrcIntData        = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntControllerOut  = &MrcIntData->Controller[0];

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    IntChannelOut = &IntControllerOut->Channel[Channel];
    Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
    MrcWriteCrMulticast (MrcData, Offset, IntChannelOut->DqControl0.Data);

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
      MrcWriteCR (MrcData, Offset, IntChannelOut->DqControl2[Byte].Data);
    }
  }
}

/**
  Run the CADB test on all channles / ranks at the current CS/CMD PIs.

  @param[in] MrcData - The MRC global data.

  @retval Bitmask of passing ranks
**/
UINT8
RunEarlyCsCmdTestLp3 (
  IN MrcParameters * const  MrcData
  )
{
  MRC_FUNCTION        *MrcCall;
  MrcDebug            *Debug;
  MrcInput            *Inputs;
  MrcOutput           *Outputs;
  MrcControllerIn     *ControllerIn;
  MrcControllerOut    *ControllerOut;
  MrcChannelIn        *ChannelIn;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  UINT8               Channel;
  UINT8               ChannelMask;
  UINT8               Rank;
  UINT8               RankBit;
  UINT8               Byte;
  UINT8               ByteMask;
  UINT8               DramByte;
  UINT8               RankPassMask;
  UINT32              ChannelPassMask;
  UINT8               BytePassMask[MAX_CHANNEL];
  UINT32              Feedback[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32              DelayCadb;
  UINT32              Offset;
  UINT32              Pattern;
  CHAR8               PassFail;
  DDRDATA0CH0_CR_DATATRAINFEEDBACK_STRUCT   DataTrainFeedback;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  MrcCall       = Inputs->Call.Func;
  ControllerIn  = &Inputs->Controller[0];
  ControllerOut = &Outputs->Controller[0];

  DelayCadb = 1 * HPET_1US;

  RankPassMask = 0; // Bitmask of passed ranks
  MrcCall->MrcSetMem ((UINT8 *) BytePassMask, sizeof (BytePassMask), 0);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankBit = 1 << Rank;
    if ((RankBit & Outputs->ValidRankMask) == 0) {
      continue;
    }

    ChannelPassMask = 0; // Bitmask of passed channels on the current rank
    ChannelMask = 0;     // Bitmask of channels that have current rank populated

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      ChannelMask |= (1 << Channel);

      SetupCaTrainingCadb (
        MrcData,
        Channel,
        Rank,
        CadbLinesCs,
        sizeof (CadbLinesCs) / sizeof (CadbLinesCs[0]),
        0x300000,
        0x400000,
        0x000000
        );
    }  // for Channel

    //
    // Put the current Rank in CA training mode using MRW41.
    //
    Status = LpddrCommandTrainingMode (MrcData, ChannelMask, RankBit, CaTrainingMode41);
    if (Status != mrcSuccess) {
      return Status;
    }

    //
    // Try two different paterns (0x2AA or 0x155), to see if the command is still decoded correctly
    //
    for (Pattern = 0; Pattern <= 1; Pattern++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        SetCadbPatternBuffers (MrcData, Channel, (Pattern == 0) ? 0x300000 : 0x700000, 0x400000, 0x000000);
      }
      //
      // Run CADB pattern on selected channels at the same time
      //
      ShortRunCADB (MrcData, ChannelMask);
      MrcWait (MrcData, DelayCadb);
      //
      // Read and process the results
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          if (Pattern == 1) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
          }
          continue;
        }
        ChannelIn  = &ControllerIn->Channel[Channel];
        ChannelOut = &ControllerOut->Channel[Channel];
        BytePassMask[Channel] = 0;
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          ByteMask = (1 << Byte);
          DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
          if (ChannelOut->Dimm[dDIMM0].SdramWidth == 32) {
            if ((DramByte & 0x02) != 0) {
              //
              // Ignore upper 16 bits on x32 devices in MRW41 feedback - DRAM bytes 2, 3, 6 and 7
              //
              BytePassMask[Channel] |= ByteMask;
              continue;
            }
          }
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
          DataTrainFeedback.Data = MrcReadCR (MrcData, Offset) & 0xFF;  // Get only DQ bits, not DQS
          if (Pattern == 0) {
            Feedback[Channel][Byte] = DataTrainFeedback.Data; // Save the first pattern
          } else {
            //
            // Second Pattern
            // If still read the same data, then DRAM was not able to decode the new command
            //
            if ((Feedback[Channel][Byte] != DataTrainFeedback.Data) &&
                (MrcCountBitsEqOne (DataTrainFeedback.Data) == 4)) {
              BytePassMask[Channel] |= ByteMask;
            }
          }
        }  // for Byte
        if (Pattern == 1) {
          if (BytePassMask[Channel] == 0xFF) { // If all bytes on a channel passed, mark this channel as passed.
            ChannelPassMask |= (1 << Channel);
            PassFail = '.';
          } else {
            PassFail = '#';
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%c%02X", PassFail, BytePassMask[Channel]);
        }
      }  // for Channel
    } // for Pattern
    if (ChannelPassMask == ChannelMask) {
      RankPassMask |= RankBit; // If all channels passed, mark this rank as passed
    }

    //
    // Exit CA training mode on the current rank
    //
    Status = LpddrCommandTrainingMode (MrcData, ChannelMask, RankBit, CaTrainingMode42);
    if (Status != mrcSuccess) {
      return Status;
    }
  } // for Rank
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  return RankPassMask;
}

/**
  Find a good starting point for LPDDR3 CMD/CS, using a quick 2D search.
  CLK is being kept at default (64).
  Start from ideal theoretical point: CS=64, CMD=96.
  Sweep CS with a step of 24 PI ticks.
  Sweep CMD with a step of 16 PI ticks, and look for 3 consecutive passing points.
  The CMD eye in ECT stress is about 60 ticks, so we can always find such 3 points.
  Run CS training CADB pattern to robustly catch CS/CMD errors.
  Stop when a PASS found on all channels/ranks.
  Select the middle of the three CMD passing points.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess if succeeded
**/
MrcStatus
EarlyCsCmdLpddr3 (
  IN MrcParameters * const  MrcData
  )
{
  MRC_FUNCTION        *MrcCall;
  MrcInput            *Inputs;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcStatus           Status;
  UINT8               Channel;
  UINT8               RankMask;
  UINT8               RankPassMask;
  UINT8               CaPiCode;
  UINT8               CsPiCode;
  UINT32              CaPiCodePass[3];
  UINT32              CsPiCodePass[3];
  UINT8               CaPassIndex;
  UINT8               CsPassIndex;
  UINT32              CsPiIndex;
  UINT32              CaPiIndex;
  static const UINT8  CsPiTable[] = { 64, 48, 32, 16, 0, 112, 96, 80 };
  static const UINT8  CaPiTable[] = { 96, 80, 64, 48, 32, 16, 0, 112 };

  Status            = mrcSuccess;
  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  MrcCall           = Inputs->Call.Func;

  RankMask = Outputs->ValidRankMask;
  CsPiCode = 0;
  CaPiCode = 0;
  CaPassIndex = 0;
  CsPassIndex = 0;
  RankPassMask = 0; // Bitmask of passed ranks
  MrcCall->MrcSetMem ((UINT8 *) CaPiCodePass, sizeof (CaPiCodePass), 0);
  MrcCall->MrcSetMem ((UINT8 *) CsPiCodePass, sizeof (CsPiCodePass), 0);

  //
  // Init DDR IO for CA training
  //
  LpddrCaTrainingInitIo (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Early CS/CMD 2D search\n\t\tR0C0\tR0C1\tR1C0\tR1C1\n");

  for (CsPiIndex = 0; CsPiIndex < sizeof (CsPiTable) / sizeof (CsPiTable[0]); CsPiIndex++) {
    CsPiCode = CsPiTable[CsPiIndex];
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CS: %d\n", CsPiCode);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      //
      // Shift the CS PI on all ranks, keep the value in the host struct.
      //
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, RankMask, 1, CsPiCode, 1);
    }

    for (CaPiIndex = 0; CaPiIndex < sizeof (CaPiTable) / sizeof (CaPiTable[0]); CaPiIndex++) {
      CaPiCode = CaPiTable[CaPiIndex];
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CMD:%d\t", CaPiCode);
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        //
        // Shift the Command PI on both CAA and CAB groups; RankMask is not relevant for CMD/CKE.
        // Keep the value in the host struct.
        //
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdN, 0, 3, CaPiCode, 1);
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, 0, 3, CaPiCode, 1);
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCke,  0, 3, CaPiCode, 1);
      }

      RankPassMask = RunEarlyCsCmdTestLp3 (MrcData); // Run the test on all channles / ranks at the current CS/CMD PIs

      if (RankPassMask == RankMask) {           // If all ranks passed, we are done for this PI
        CaPiCodePass[CaPassIndex] = CaPiCode;   // Store passing CMD PI code
        CaPassIndex++;
        if (CaPassIndex > 2) {                  // Do we have 3 passing CA points ?
          break;
        }
      }
    } // for CMD PI
    if (RankPassMask == RankMask) { // If all ranks passed, we are done
      if (CaPassIndex > 2) {        // Do we have 3 passing CA points ?
        break;
      } else {
        CaPassIndex = 0;            // Restart search for 3 passing CMD points
      }
    }
  }  // for CS PI

  if (RankPassMask != RankMask) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: cannot find a working starting point for CS/CMD for all channels/ranks\n");
    return mrcFail;
  }

  MrcBsort (CaPiCodePass, ARRAY_COUNT (CaPiCodePass));  // Sort the array, because the passing range might wrap around
  CaPiCode = (UINT8) CaPiCodePass[1];                   // Select the middle code out of three.

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    //
    // Shift the Command PI on both CAA and CAB groups; RankMask is not relevant for CMD/CKE.
    // Keep the value in the host struct.
    //
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdN, 0, 3, CaPiCode, 1);
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, 0, 3, CaPiCode, 1);
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCke,  0, 3, CaPiCode, 1);
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected values: CS = %d, CMD = %d\n\n", CsPiCode, CaPiCode);

  //
  // Now let's find 3 passing CS points at this CMD point
  //
  for (CsPiIndex = 0; CsPiIndex < sizeof (CsPiTable) / sizeof (CsPiTable[0]); CsPiIndex++) {
    CsPiCode = CsPiTable[CsPiIndex];
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CS: %d\t", CsPiCode);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      //
      // Shift the CS PI on all ranks, keep the value in the host struct.
      //
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, RankMask, 1, CsPiCode, 1);
    }

    RankPassMask = RunEarlyCsCmdTestLp3 (MrcData); // Run the test on all channles / ranks at the current CS/CMD PIs

    if (RankPassMask == RankMask) {           // If all ranks passed, we are done for this PI
      CsPiCodePass[CsPassIndex] = CsPiCode;   // Store passing CS PI code
      CsPassIndex++;
      if (CsPassIndex > 2) {                  // Do we have 3 passing CS points ?
        break;
      }
    }
  } // for CS PI

  if (RankPassMask != RankMask) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: cannot find a working starting point for CS/CMD for all channels/ranks\n");
    return mrcFail;
  }

  MrcBsort (CsPiCodePass, ARRAY_COUNT (CsPiCodePass));  // Sort the array, because the passing range might wrap around
  CsPiCode = (UINT8) CsPiCodePass[1];                   // Select the middle code out of three.

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      //
      // Shift the CS PI on all ranks, keep the value in the host struct.
      //
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, RankMask, 1, CsPiCode, 1);
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Final selected values: CS = %d, CMD = %d\n\n", CsPiCode, CaPiCode);

  //
  // Restore DDR IO values that were used for CA training
  //
  LpddrCaTrainingRestoreIo (MrcData);

  return Status;
}

/**
  Sweep CMD PI up or down and find edges for all bytes.
  Main flow:
  1.
  2.
  3.

  @param[in] MrcData - The MRC global data.

**/
void
EarlyCaFindEdge (
  IN MrcParameters * const  MrcData,
  UINT8                     Rank,
  UINT8                     Start,
  UINT8                     Stop,
  INT8                      Step,
  UINT8                     Limit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM]
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerIn   *ControllerIn;
  MrcControllerOut  *ControllerOut;
  MrcChannelIn      *ChannelIn;
  MrcChannelOut     *ChannelOut;
  UINT8             Channel;
  UINT8             ChannelMask;
  UINT8             Byte;
  UINT8             ByteMask;
  UINT8             DramByte;
  UINT8             ByteDoneMask[MAX_CHANNEL];
  UINT8             PiCode;
  UINT32            DelayCadb;
  UINT32            Offset;
  BOOLEAN           Done;
  char              *BytesHeader;
  char              PassFail;
  DDRDATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DataTrainFeedback;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerIn  = &Inputs->Controller[0];
  ControllerOut = &Outputs->Controller[0];

  DelayCadb = 1 * HPET_1US;

  MrcCall->MrcSetMem (ByteDoneMask, sizeof (ByteDoneMask), 0);

  PiCode = Start;
  Done = FALSE;

  ChannelMask   = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
      ChannelMask |= (1 << Channel);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t Ch0\t\t\t\t   Ch1\n");
  BytesHeader = "0   1   2   3   4   5   6   7     ";
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CMD PI\t %s%s\n", BytesHeader, BytesHeader);

  while (!Done) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d: \t", PiCode);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      //
      // Shift the Command PI on both CAA and CAB groups
      //
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdN, 1 << Rank, 3, PiCode, 0);
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, 1 << Rank, 3, PiCode, 0);
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCke,  1 << Rank, 3, PiCode, 0);
    }

    //
    // Run CADB pattern on selected channels at the same time
    //
    ShortRunCADB (MrcData, ChannelMask);
    MrcWait (MrcData, DelayCadb);

    //
    // Read and process the results
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        ByteDoneMask[Channel] = 0xFF;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "                                  ");
        continue;
      }
      if (ByteDoneMask[Channel] == 0xFF) { // All bytes failed on this channel, no need to sweep anymore
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "                                  ");
        continue;
      }
      ChannelIn = &ControllerIn->Channel[Channel];
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        ByteMask = (1 << Byte);
        DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
        if (ChannelOut->Dimm[dDIMM0].SdramWidth == 32) {
          if ((DramByte & 0x02) != 0) {
            //
            // Ignore upper 16 bits on x32 devices in MRW41 feedback - DRAM bytes 2, 3, 6 and 7
            //
            ByteDoneMask[Channel] |= ByteMask;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    ");
            continue;
          }
        }
        Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
        DataTrainFeedback.Data = (MrcReadCR (MrcData, Offset) & 0xFF);  // Get only DQ bits, not DQS

        PassFail = '#';
        if ((ByteDoneMask[Channel] & ByteMask) == 0) {
          //
          // If we don't see 4 ones in the byte, then the command was not aligned properly
          //
          if (MrcCountBitsEqOne (DataTrainFeedback.Data) != 4) {
            Limit[Channel][Rank][Byte] = PiCode;
            ByteDoneMask[Channel] |= ByteMask;
          } else {
            PassFail = '.';
          }
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%c%02X ", PassFail, DataTrainFeedback.Data);
      }  // for Byte
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
    }  // for Channel
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    if ((ByteDoneMask[0] == 0xFF) && (ByteDoneMask[1] == 0xFF)) {
      // Found the limit on all bytes on both channels - no need to sweep Pi any longer
      break;
    }

    PiCode += Step;
    if (Step > 0) {
      // Sweep up
      Done = (PiCode > Stop);
    } else {
      // Sweep down
      Done = (((INT8) PiCode) < Stop);
    }
  }  // while not done
}

/**
  Process the results of the early LPDDR3 CMD training and find the best PI settings for CmdS/CmdN/Cke.
  Flow:
   1. Find the worst case Right and Left limits for each channel
   2. Find the Center for each channel

  @param[in]  MrcData     - The MRC global data.
  @param[in]  LeftLimit   - array of left edge values per channel, rank and CPU byte
  @param[in]  RightLimit  - array of right edge values per channel, rank and CPU byte
  @param[out] BestCs      - array of best CMD PI settings, per channel

  @retval mrcSuccess if succeeded
**/
MrcStatus
FindBestCmdPi (
  IN  MrcParameters * const MrcData,
  IN  UINT8                 LeftLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN  UINT8                 RightLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM],
  OUT UINT8                 BestCmd[MAX_CHANNEL][2]    // per Channel and per group (CAA and CAB)
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcStatus         Status;
  MrcChannelIn      *ChannelIn;
  MrcControllerIn   *ControllerIn;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             Byte;
  UINT8             CaGroup;
  UINT8             CmdLeftLimit[MAX_CHANNEL][2];  // Per ch and group
  UINT8             CmdRightLimit[MAX_CHANNEL][2]; // Per ch and group

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerIn  = &Inputs->Controller[0];

  Status = mrcSuccess;

  MrcCall->MrcSetMem ((UINT8 *) CmdRightLimit, sizeof (CmdRightLimit), 127);
  MrcCall->MrcSetMem ((UINT8 *) CmdLeftLimit, sizeof (CmdLeftLimit), 0);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Finding best CMD PIs:\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelIn = &ControllerIn->Channel[Channel];
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel: %d\t\tLeft\tRight\tCenter\n", Channel);
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      //
      // Find the worst case Right and Left limits for all ranks, for bytes from the particular CA group
      //
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        //
        // CmdS CAA goes to Bytes[3:0], CmdS CAB goes to Byte[7:4]
        //
        if ((1 << Byte) & ChannelIn->DQByteMap[MrcIterationCmdS][0]) {
          CaGroup = 0;
        } else {
          CaGroup = 1;
        }
        CmdRightLimit[Channel][CaGroup] = MIN (CmdRightLimit[Channel][CaGroup], RightLimit[Channel][Rank][Byte]);
        CmdLeftLimit[Channel][CaGroup]  = MAX (CmdLeftLimit[Channel][CaGroup], LeftLimit[Channel][Rank][Byte]);
      }
    } // for Rank

    //
    // Find the Center for each group, worst case of all ranks
    //
    BestCmd[Channel][0] = (CmdRightLimit[Channel][0] + CmdLeftLimit[Channel][0]) / 2;
    BestCmd[Channel][1] = (CmdRightLimit[Channel][1] + CmdLeftLimit[Channel][1]) / 2;

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "CA%c\t\t\t%d\t%d\t%d\n",
      'A',
      CmdLeftLimit[Channel][0],
      CmdRightLimit[Channel][0],
      BestCmd[Channel][0]
      );

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "CA%c\t\t\t%d\t%d\t%d\n",
      'B',
      CmdLeftLimit[Channel][1],
      CmdRightLimit[Channel][1],
      BestCmd[Channel][1]
      );
  } // for Channel

  return Status;
}

/**
  Update DqMapCpu2Dram array

  @param[in] MrcData  - The MRC global data.
  @param[in] Channel  - the channel to work on
  @param[in] Feedback - array of DATATRAINFEEDBACK values for all 8 bytes
  @param[in] Bit      - The DQ bit the should be set in each DRAM byte

  @retval mrcSuccess if succeeded
**/
MrcStatus
FillCA2DQMapResult (
  IN OUT MrcParameters * const  MrcData,
  IN const UINT8                Channel,
  IN const UINT8                Feedback[8],
  IN const UINT8                Bit
  )
{
  MrcInput          *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcControllerOut  *ControllerOut;
  MrcControllerIn   *ControllerIn;
  MrcChannelIn      *ChannelIn;
  MrcStatus         Status;
  UINT8             Byte;
  UINT8             Temp;
  UINT8             CpuBit;
  INT8              BitNumber;
  BOOLEAN           BitFound;

  Status        = mrcSuccess;
  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  ControllerIn  = &Inputs->Controller[0];

  ChannelOut = &ControllerOut->Channel[Channel];
  ChannelIn  = &ControllerIn->Channel[Channel];

  BitNumber = -1;

  //
  // Loop on CPU bytes
  //
  for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
    if (Feedback[Byte] == 0) {
      continue;
    }
    Temp = Feedback[Byte];
    BitNumber = 0;
    CpuBit    = 0;
    BitFound  = FALSE;
    while (Temp > 0) {
      if (Temp & 1) {
        if (!BitFound) {
          CpuBit = BitNumber;
          BitFound = TRUE;
        } else {
          Status = mrcFail;
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "Ch%d: ERROR: More than one DQ pin toggled while looking for DQ%d in Byte%d, Feedback=0x%X\n",
            Channel,
            Bit,
            Byte,
            Feedback[Byte]
            );
          break;
        }
      }
      Temp >>= 1;
      BitNumber++;
    }
    ChannelIn->DqMapCpu2Dram[Byte][CpuBit] = ChannelIn->DqsMapCpu2Dram[Byte] * 8 + Bit;
  } // for Byte

  return Status;
}

/**
  Rotate a given number left by a specified number of bits.

  @param[in] Value      - The input value
  @param[in] BitLength  - How many bits to rotate in the input value. Should be >1 and <32, tested for 16
  @param[in] RotateBy   - Number of bits to rotate by.

  @retval The rotated number
**/
UINT32
RotateLeft (
  IN const UINT32 Value,
  IN const UINT8 BitLength,
  IN const UINT8 RotateBy
  )
{
  UINT32 Mask;
  UINT32 Lsb;
  UINT32 Result;
  UINT8 i;

  Result = Value;
  Mask = (1 << BitLength) - 1;

  for (i = 0; i < RotateBy; i++) {
    Lsb = 1 & (((Result) & (1 << (BitLength - 1))) >> (BitLength-1)); // The MSB value needs to move to LSB
    Result = (Mask & (Result << 1)) | Lsb;                            // Shift Left once and add the new LSB
  }

  return Result;
}

/**
  Calculate 3 Pattern Buffers values for the given CADB sequence.

  @param[in] MrcData             - The MRC global data.
  @param[in] CadbSequence        - CADB line numbers in the order of transmission.
                                   Example: 0,1,0,0,...0 for DQ mapping, 0,0,2,1,1,0,0,...0 for CS training
  @param[out] CadbPatternBuffers - Array of 3 Pattern Buffer values

**/
void
CalculateCadbPB (
  IN MrcParameters * const  MrcData,
  IN const UINT8            CadbSequence[MRC_CADB_PB_LENGTH],
  OUT UINT32                CadbPatternBuffers[3]
  )
{
  MrcInput     *Inputs;
  MRC_FUNCTION *MrcCall;
  MrcDebug     *Debug;
  UINT8        i;
  UINT8        j;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &MrcData->Outputs.Debug;

  MrcCall->MrcSetMem ((UINT8 *) CadbPatternBuffers, 3 * sizeof (CadbPatternBuffers[0]), 0);

  for (i = 0; i < MRC_CADB_PB_LENGTH; i++) {
    for (j = 0; j < 3; j++) {
      CadbPatternBuffers[j] =
        RotateLeft (CadbPatternBuffers[j], MRC_CADB_PB_LENGTH, 1) |
        ((CadbSequence[i] & (1 << j)) >> j);
    }
  }

  for (j = 0; j < 3; j++) {
    CadbPatternBuffers[j] = RotateLeft (CadbPatternBuffers[j], MRC_CADB_PB_LENGTH, 1);
  }
}

/**
  Map CA to DQ Pins for CA training and MR4 bit swizzling settings for LPDDR3.
  Main flow:
  Repeat for each of the 8 bits per DQ byte (total 8 iterations for both channels, for rank0 only):
    Transmit single CA phase expected to appear on a known DQ pin
     One CA phase per byte, 2 different CA phases for Even and Odd bytes in parallel
    Locate the single DQ in each byte based on DATATRAINFEEDBACK
     Report error if more than one DQ pin toggles
     Report error if no active DQ pin found
     Ignore Byte2 and Byte3 for x32 devices if they don't return feedback (only DQ[15:0] must return feedback per JEDEC)
    Update the DQ mapping data structure.

  Assumption: runs on stable and correct CLK, CS and CA PI settings (either guaranteed by design or pre-trained)

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess if succeeded
**/
MrcStatus
MapCA2DQPins (
  IN MrcParameters * const MrcData
  )
{
  MrcInput                                    *Inputs;
  MRC_FUNCTION                                *MrcCall;
  MrcDebug                                    *Debug;
  MrcOutput                                   *Outputs;
  MrcControllerIn                             *ControllerIn;
  MrcControllerOut                            *ControllerOut;
  MrcChannelIn                                *ChannelIn;
  MrcChannelOut                               *ChannelOut;
  MrcStatus                                   Status;
  MrcStatus                                   StatusLocal;
  UINT8                                       Channel;
  UINT8                                       ChannelMask;
  UINT8                                       Rank;
  UINT8                                       Byte;
  UINT8                                       DramByte;
  UINT8                                       Bit;
  UINT32                                      Offset;
  UINT32                                      CaPattern;
  UINT8                                       Feedback[8];
  CADB_LINE CadbLinesDqMapping[2];
  UINT32  CadbPatternBuffers[3];
  UINT8   CadbSequence[MRC_CADB_PB_LENGTH];
#ifdef MRC_DEBUG_PRINT
  UINT8                                       DramBit;
  UINT8                                       i;
#endif

  Status           = mrcSuccess;
  Inputs           = &MrcData->Inputs;
  MrcCall          = Inputs->Call.Func;
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  ControllerIn     = &Inputs->Controller[0];
  ControllerOut    = &Outputs->Controller[0];
  Rank             = 0;
  ChannelMask      = 0;
  CadbLinesDqMapping[0].CaHigh = 0x000;
  CadbLinesDqMapping[0].CaLow = 0x000;
  CadbLinesDqMapping[0].ChipSelect = 0;
  CadbLinesDqMapping[1].CaHigh = 0x001;
  CadbLinesDqMapping[1].CaLow = 0x000;
  CadbLinesDqMapping[1].ChipSelect = 1;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MapCA2DQPins started\n");
  if (ControllerOut->Channel[0].Dimm[dDIMM0].SdramWidth == 32) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x32 DRAM devices - skipping Bytes 2,3 in each DRAM!\n");
  }

  MrcCall->MrcSetMem (CadbSequence, sizeof (CadbSequence), 0);
  CadbSequence[1] = 1; // The 2nd PB entry is the 2nd CADB line with active CS. The rest are 0.

  //
  // Calculate the Pattern Buffers values for the given CADB sequence
  //
  CalculateCadbPB (MrcData, CadbSequence, CadbPatternBuffers);

  //
  // Init DDR IO for CA training
  //
  LpddrCaTrainingInitIo (MrcData);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcRankInChannelExist (MrcData, 0, Channel)) {
      continue;
    }
    MrcCall->MrcSetMem (
               (UINT8 *) (ControllerIn->Channel[Channel].DqMapCpu2Dram),
               sizeof (ControllerIn->Channel[0].DqMapCpu2Dram),
               0xFF
               );
    //
    // Put Rank 0 in CA training mode using MRW41.
    //
    StatusLocal = LpddrCommandTrainingMode (MrcData, 1 << Channel, 1 << Rank, CaTrainingMode41);
    if (StatusLocal != mrcSuccess) {
      return StatusLocal;
    }
  }

  for (Bit = 0; Bit < MAX_BITS; Bit++) {
    //
    // Create CA patterns for high and low phases,
    // such that only one DQ bit should toggle on each phase, per DRAM byte
    //
    CaPattern = (1 << (Bit / 2)) | (1 << (Bit / 2 + 5));
    CadbLinesDqMapping[1].CaHigh = ((Bit % 2) == 0) ? CaPattern : 0;
    CadbLinesDqMapping[1].CaLow  = ((Bit % 2) == 1) ? CaPattern : 0;

#ifdef MRC_DEBUG_PRINT
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRunning Bit %d\n", Bit);
    for (i = 0; i < sizeof (CadbLinesDqMapping) / sizeof (CadbLinesDqMapping[0]); i++) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\tCADB[%d] CaHigh=0x%03X\tCaLow=0x%03X\tCS=0x%03X\n",
        i,
        CadbLinesDqMapping[i].CaHigh,
        CadbLinesDqMapping[i].CaLow,
        CadbLinesDqMapping[i].ChipSelect
        );
    }
#endif //MRC_DEBUG_PRINT

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, 0, Channel)) {
        continue;
      }
      ChannelMask |= (1 << Channel);

      SetupCaTrainingCadb (
        MrcData,
        Channel,
        Rank,
        CadbLinesDqMapping,
        sizeof (CadbLinesDqMapping) / sizeof (CadbLinesDqMapping[0]),
        CadbPatternBuffers[0],
        CadbPatternBuffers[1],
        CadbPatternBuffers[2]
        );
    }

    //
    // Run CADB pattern on populated channels
    //
    ShortRunCADB (MrcData, ChannelMask);

    //
    // Get Results for all ch/bytes
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, 0, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      ChannelIn  = &ControllerIn->Channel[Channel];

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
        if (ChannelOut->Dimm[dDIMM0].SdramWidth == 32) {
          if ((DramByte & 0x02) != 0) {
            //
            // Ignore upper 16 bits (in DRAM terms) on x32 devices in MRW41 feedback - DRAM bytes 2, 3, 6 and 7
            //
            Feedback[Byte] = 0;
            continue;
          }
        }
        Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
        Feedback[Byte] = (UINT8) (MrcReadCR (MrcData, Offset) & 0xFF);
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\t   Channel %d CPU Byte %d DRAM Byte %d => Feedback = %02X - %s feedback\n",
          Channel,
          Byte,
          DramByte,
          Feedback[Byte],
          (MrcCountBitsEqOne (Feedback[Byte]) == 1) ? "Good" : "Bad"
          );
      } // for Byte
      //
      // Store results in ChannelIn->DqMapCpu2Dram
      //
      StatusLocal = FillCA2DQMapResult (MrcData, Channel, Feedback, Bit);
      if (StatusLocal != mrcSuccess) {
        Status = StatusLocal;  // This will signal ECT failure
      }
    } // for Channel
  }  // for Bit

  //
  // Exit CA training mode on rank 0 on all channels
  //
  StatusLocal = LpddrCommandTrainingMode (MrcData, ChannelMask, 1 << Rank, CaTrainingMode42);
  if (StatusLocal != mrcSuccess) {
    return StatusLocal;
  }

  //
  // Restore DDR IO values that were used for CA training
  //
  LpddrCaTrainingRestoreIo (MrcData);

#ifdef MRC_DEBUG_PRINT
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcRankInChannelExist (MrcData, 0, Channel)) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    ChannelIn  = &ControllerIn->Channel[Channel];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "\nMapCA2DQPins Results for Ch%d (\"-1\" for skipped Bytes, DRAM DQ pins offsets):\n",
      Channel
      );
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "CPU Bit: \t[0]\t[1]\t[2]\t[3]\t[4]\t[5]\t[6]\t[7]\n"
      );
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CPU Byte%d:", Byte);
      for (Bit = 0; Bit <  MAX_BITS; Bit++) {
        DramBit = ChannelIn->DqMapCpu2Dram[Byte][Bit];
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", (DramBit == 255) ? -1: DramBit);
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    }
  }
#endif //MRC_DEBUG_PRINT

  return Status;
}

/**
  Sweep the given PI up or down and find the edge.

  @param[in]  MrcData     - The MRC global data.
  @param[in]  Iteration   - Determines which PI to shift
  @param[in]  ChannelMask - Valid Channel bit mask
  @param[in]  RankMask    - Valid Rank bit mask
  @param[in]  Stop        - End of the PI range
  @param[in]  Step        - PI step for the sweep
  @param[out] Limit       - array of edge values (per channel), filled by this function
  @param[in]  DebugPrint  - Print debug messages or not

**/
void
CaFindEdge (
  IN  MrcParameters * const  MrcData,
  IN  UINT8                  Iteration,
  IN  UINT8                  ChannelMask,
  IN  UINT8                  RankMask,
  IN  INT16                  Stop,
  IN  INT16                  Step,
  OUT UINT8                  Limit[MAX_CHANNEL],
  IN  BOOLEAN                DebugPrint
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  UINT8             Channel;
  UINT8             ChannelBit;
  UINT8             ChError;
  UINT8             DumArr[7];
  INT16             PiOffset;
  BOOLEAN           Pass;
  BOOLEAN           Done;
  BOOLEAN           ChannelDone[MAX_CHANNEL];

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  PiOffset = 0;
  Done = FALSE;
  ChannelDone[0] = ChannelDone[1] = FALSE;
  MrcCall->MrcSetMem (DumArr, sizeof (DumArr), 1);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (DebugPrint) ? "\t0 1\n" : "");

  while (!Done) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (DebugPrint) ? "%d:\t" : "", PiOffset);
    //
    // Update Timing
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((1 << Channel) & ChannelMask) {
        if (!ChannelDone[Channel]) {
          ShiftPIforCmdTraining (MrcData, Channel, Iteration, RankMask, 3, PiOffset, 0);
        }
      }
    }
    //
    // Reset DDR after changing the CLK PI
    //
    MrcResetSequence (MrcData);

    //
    // Run CPGC test on both channels
    //
    ChError = RunIOTest (MrcData, ChannelMask, Outputs->DQPat, DumArr, 1, 0);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelBit = (1 << Channel);
      if (((ChannelBit & ChannelMask) == 0) || (ChannelDone[Channel])) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (DebugPrint && (Channel == 0)) ? "  " : "");
        continue;
      }

      Pass = !(ChError & ChannelBit);

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (DebugPrint) ? (Pass ? ". " : "# ") : "");

      if (Pass) {
        Limit[Channel] = (UINT8) (ABS (PiOffset));
      } else {
        ChannelDone[Channel] = TRUE;
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (DebugPrint) ? "\n" : "");

    PiOffset += Step;
    if (Step > 0) {
      // Sweep up
      Done = (PiOffset > Stop);
    } else {
      // Sweep down
      Done = (PiOffset < Stop);
    }

    if (ChannelDone[0] && ChannelDone[1]) {
      // Found the limit on both channels - no need to sweep PI any longer
      Done = TRUE;
    }
  }  // while not done
}

/**
  Sweep right and left from the current point to find the margins.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Iteration   - Determines which PI to shift
  @param[in]      ChannelMask - Valid Channel bit mask
  @param[in]      RankMask    - Valid Rank bit mask
  @param[in]      DebugPrint  - Print debug messages or not

  @retval MrcStatus -  If it succeeds return mrcSuccess
**/
void
CmdLinearFindEdgesLpddr (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Iteration,
  IN     UINT8                ChannelMask,
  IN     UINT8                RankMask,
  IN     BOOLEAN              DebugPrint
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  UINT8             Channel;
  UINT8             Rank;
  INT16             PiLow;
  INT16             PiHigh;
  INT16             PiStep;
  UINT8             RightLimit[MAX_CHANNEL];
  UINT8             LeftLimit[MAX_CHANNEL];

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  //
  // We are going to sweep clock 32 PI ticks to the left and to the right
  //
  PiLow   = -32;
  PiHigh  = 32;

  PiStep = 1;


  //
  // Initialize to zero margin
  //
  MrcCall->MrcSetMem ((UINT8 *) RightLimit, sizeof (RightLimit), 0);
  MrcCall->MrcSetMem ((UINT8 *) LeftLimit, sizeof (LeftLimit), 0);

  //
  // Find right and left margins
  //
  CaFindEdge (MrcData, Iteration, ChannelMask, RankMask, PiHigh, PiStep, RightLimit, DebugPrint);
  CaFindEdge (MrcData, Iteration, ChannelMask, RankMask, PiLow, -PiStep, LeftLimit, DebugPrint);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((1 << Channel) & ChannelMask) {
      //
      // Save margins for RMT
      //
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((1 << Rank) & RankMask) {
          Outputs->MarginResult[LastCmdT][Rank][Channel][0][0] = 10 * LeftLimit[Channel];
          Outputs->MarginResult[LastCmdT][Rank][Channel][0][1] = 10 * RightLimit[Channel];
        }
      }
    }
  }
}

/**
  Early CMD / CLK training for LPDDR3.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess if succeeded
**/
MrcStatus
EarlyCaTraining (
  IN MrcParameters * const MrcData
  )
{
  MrcInput                                    *Inputs;
  MrcDebug                                    *Debug;
  MRC_FUNCTION                                *MrcCall;
  MrcOutput                                   *Outputs;
  MrcControllerIn                             *ControllerIn;
  MrcControllerOut                            *ControllerOut;
  MrcChannelOut                               *ChannelOut;
  MrcStatus                                   Status;
  UINT8                                       Channel;
  UINT8                                       Rank;
  UINT8                                       RankBit;
  UINT8                                       RankMask;
  UINT8                                       PiLow;
  UINT8                                       PiHigh;
  UINT8                                       PiMiddle;
  UINT8                                       PiStep;
  UINT8                                       RightLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8                                       LeftLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8                                       BestCmd[MAX_CHANNEL][2]; // per Channel and per group (CAA and CAB)
#ifdef MRC_DEBUG_PRINT
  MrcChannelIn                                *ChannelIn;
  UINT8                                       Left;
  UINT8                                       Right;
  UINT8                                       Byte;
  UINT8                                       DramByte;
#endif

  Inputs           = &MrcData->Inputs;
  MrcCall          = Inputs->Call.Func;
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  ControllerIn     = &Inputs->Controller[0];
  ControllerOut    = &Outputs->Controller[0];

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EarlyCaTraining started\n");

  Status = mrcSuccess;
  RankMask  = Outputs->ValidRankMask;

  PiLow     = DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN;
  PiHigh    = DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX;
  PiMiddle  = (DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN + DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX + 1) / 2; // // Will be updated below from the host struct
  PiStep = 2;


  MrcCall->MrcSetMem ((UINT8 *) RightLimit, sizeof (RightLimit), PiHigh);
  MrcCall->MrcSetMem ((UINT8 *) LeftLimit, sizeof (LeftLimit), PiLow);

  //
  // Init DDR IO for CA training
  //
  LpddrCaTrainingInitIo (MrcData);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankBit = 1 << Rank;
    if ((RankBit & RankMask) == 0) {
      continue;
    }

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      PiMiddle = (UINT8) ChannelOut->CmdsCmdPiCode[0]; // Found in EarlyCsCmdLpddr3()

      //
      // Put the current Rank in CA training mode using MRW41.
      //
      Status = LpddrCommandTrainingMode (MrcData, 1 << Channel, RankBit, CaTrainingMode41);
      if (Status != mrcSuccess) {
        return Status;
      }

      SetupCaTrainingCadb (
        MrcData,
        Channel,
        Rank,
        CadbLinesCs,
        sizeof (CadbLinesCs) / sizeof (CadbLinesCs[0]),
        0x300000,
        0x400000,
        0x000000
        );
    }  // for Channel

    //
    // Sweep CMD PI up and down from the middle, on both channels at the same time
    //


    EarlyCaFindEdge (MrcData, Rank, PiMiddle, PiHigh, PiStep, RightLimit);
    EarlyCaFindEdge (MrcData, Rank, PiMiddle, PiLow, -PiStep, LeftLimit);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
#ifdef MRC_DEBUG_PRINT
      ChannelIn  = &ControllerIn->Channel[Channel];
      ChannelOut = &ControllerOut->Channel[Channel];
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CA training data Ch%d Rank%d\nCPU Byte\tLeft\tRight\tWidth\n", Channel, Rank);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
        if (ChannelOut->Dimm[dDIMM0].SdramWidth == 32) {
          if ((DramByte & 0x02) != 0) {
            //
            // Ignore upper 16 bits on x32 devices in MRW41 feedback - DRAM bytes 2, 3, 6 and 7
            //
            continue;
          }
        }
        Left  = LeftLimit[Channel][Rank][Byte];
        Right = RightLimit[Channel][Rank][Byte];
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t\t%d\t%d\t%d\n", Byte, Left, Right, Right - Left);
      }
#endif // MRC_DEBUG_PRINT
      //
      // Put the CMD PI back to middle for MRW42 command
      //
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, RankBit,        3, PiMiddle, 1);
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCke,  RankBit, (1 << 0), PiMiddle, 1);
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdN, RankBit, (1 << 1), PiMiddle, 1);

      //
      // Exit CA training mode on the current rank
      //
      Status = LpddrCommandTrainingMode (MrcData, 1 << Channel, RankBit, CaTrainingMode42);
      if (Status != mrcSuccess) {
        return Status;
      }
    } // for Channel
  }  // for Rank

  //
  // Restore DDR IO values that were used for CA training
  //
  LpddrCaTrainingRestoreIo (MrcData);

  //
  // Select optimal CMD timings for both channels
  //
  FindBestCmdPi (MrcData, LeftLimit, RightLimit, BestCmd);

  //
  // Apply the new CmdN, CmdS and CKE command PI settings
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    //
    // CAA is controlled by CMDS.CmdPi0Code and CKE.CmdPi0Code
    //
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, RankMask, (1 << 0), BestCmd[Channel][0], 1);
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCke,  RankMask, (1 << 0), BestCmd[Channel][0], 1);

    //
    // CAB is controlled by CMDS.CmdPi1Code and CMDN.CmdPi1Code
    //
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, RankMask, (1 << 1), BestCmd[Channel][1], 1);
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdN, RankMask, (1 << 1), BestCmd[Channel][1], 1);
  } // for Channel

  return Status;
}

/**
  Early CA / CS training for LPDDR3.
  Main flow:
  1. Run Early 2D CS/CMD training.
  2. Run CPU-to-DRAM DQ Mapping (map DQ pins according to the board swizzling).
  3. Run CS vs. CLK training.
  4. Run CA vs. CLK training.
  5. Program DESWIZZLE_HIGH/LOW registers.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess if succeeded
**/
MrcStatus
EarlyCommandTrainingLpddr (
  IN MrcParameters * const MrcData
  )
{
  const MrcInput                              *Inputs;
  MrcDebug                                    *Debug;
  MrcOutput                                   *Outputs;
  MrcControllerOut                            *ControllerOut;
  MrcStatus                                   Status;
  UINT8                                       ChannelBitMask;
  UINT8                                       ValidRankMask;


  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];

  ValidRankMask   = Outputs->ValidRankMask;
  ChannelBitMask  = Outputs->ValidChBitMask;
  Status = mrcSuccess;


  //
  // Early 2D CS/CMD training - find the good starting point for the rest of the ECT steps.
  //
  Status = EarlyCsCmdLpddr3 (MrcData);
  if (Status != mrcSuccess) {
    return Status;
  }

  //
  // Run CPU-to-DRAM DQ Mapping
  //
  Status = MapCA2DQPins (MrcData);
  if (Status != mrcSuccess) {
    return Status;
  }

  //
  // Run CS vs. CLK training
  //
  Status = EarlyChipSelectTraining (MrcData);
  if (Status != mrcSuccess) {
    return Status;
  }

  //
  // Run CA vs. CLK training
  //
  Status = EarlyCaTraining (MrcData);
  if (Status != mrcSuccess) {
    return Status;
  }

  //
  // Program DESWIZZLE_HIGH/LOW registers
  //
  ProgramDeswizzleRegisters (MrcData);

  //
  // Set this flag so that MrcResetSequence() will include MrcJedecInitLpddr3() as well.
  //
  Outputs->LpddrEctDone = TRUE;

  return Status;
}

/**
  Sweep CS Pi up or down and find edges for all bytes.
  Main flow:
  1.
  2.
  3.

  @param[in]  MrcData - The MRC global data.
  @param[out] Limit   - array of edge PI values per channel, rank and CPU byte

**/
void
ChipSelectFindEdge (
  IN MrcParameters * const  MrcData,
  UINT8                     Rank,
  UINT8                     Start,
  UINT8                     Stop,
  INT8                      Step,
  OUT UINT8                 Limit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM]
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerIn   *ControllerIn;
  MrcControllerOut  *ControllerOut;
  MrcChannelIn      *ChannelIn;
  MrcChannelOut     *ChannelOut;
  UINT8             Channel;
  UINT8             ChannelMask;
  UINT8             Byte;
  UINT8             ByteMask;
  UINT8             DramByte;
  UINT8             ByteDoneMask[MAX_CHANNEL];
  UINT8             PiCode;
  UINT8             Feedback[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32            Pattern;
  UINT32            DelayChipSelectCadb;
  UINT32            Offset;
  BOOLEAN           Done;
  BOOLEAN           Failed;
  char              *BytesHeader;
  char              PassFail;
  DDRDATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DataTrainFeedback;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerIn  = &Inputs->Controller[0];
  ControllerOut = &Outputs->Controller[0];
  ChannelMask   = 0;

  DelayChipSelectCadb = 1 * HPET_1US;

  MrcCall->MrcSetMem (ByteDoneMask, sizeof (ByteDoneMask), 0);

  PiCode = Start;
  Done = FALSE;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t Ch0 pattern 1\t\t\t   Ch1 pattern 1\t\t     Ch 0 pattern 2\t\t       Ch 1 pattern 2\n");
  BytesHeader = "0   1   2   3   4   5   6   7     ";
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CTL PI\t %s%s", BytesHeader, BytesHeader);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s\n", BytesHeader, BytesHeader);

  while (!Done) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d:\t", PiCode);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 1 << Rank, 1, PiCode, 1);
    }

    //
    // Try two different paterns (0x2AA or 0x155), to see if the command is still decoded correctly
    //
    for (Pattern = 0; Pattern <= 1; Pattern++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        ChannelMask |= (1 << Channel);
        SetCadbPatternBuffers (MrcData, Channel, (Pattern == 0) ? 0x300000 : 0x700000, 0x400000, 0x000000);
      }

      //
      // Run CADB pattern on selected channels at the same time
      //
      ShortRunCADB (MrcData, ChannelMask);
      MrcWait (MrcData, DelayChipSelectCadb);

      //
      // Read and process the results
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          ByteDoneMask[Channel] = 0xFF;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "                                  ");
          continue;
        }
        if (ByteDoneMask[Channel] == 0xFF) { // All bytes failed on this channel, no need to sweep anymore
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "                                  ");
          continue;
        }
        ChannelIn  = &ControllerIn->Channel[Channel];
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          ByteMask = (1 << Byte);
          DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
          if (ChannelOut->Dimm[dDIMM0].SdramWidth == 32) {
            if ((DramByte & 0x02) != 0) {
              //
              // Ignore upper 16 bits on x32 devices in MRW41 feedback - DRAM bytes 2, 3, 6 and 7
              //
              ByteDoneMask[Channel] |= ByteMask;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    ");
              continue;
            }
          }
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
          DataTrainFeedback.Data = (MrcReadCR (MrcData, Offset) & 0xFF);  // Get only DQ bits, not DQS
          PassFail = '#';
          if ((ByteDoneMask[Channel] & ByteMask) == 0) {
            if (Pattern == 0) {
              //
              // First pattern
              //
              Feedback[Channel][Byte] = (UINT8) DataTrainFeedback.Data;
              PassFail = ' ';
            } else {
              //
              // Second Pattern
              // If still read the same data, then DRAM was not able to decode the new command
              //
              Failed = FALSE;
              if (Feedback[Channel][Byte] == (UINT8) DataTrainFeedback.Data) {
                Failed = TRUE;
              }
              if (MrcCountBitsEqOne (DataTrainFeedback.Data) != 4) {
                Failed = TRUE;
              }
              if (Failed) {
                Limit[Channel][Rank][Byte] = PiCode;
                ByteDoneMask[Channel] |= ByteMask;
              } else {
                PassFail = '.';
              }
            }
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%c%02X ", PassFail, DataTrainFeedback.Data);
        }  // for Byte
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
      }  // for Channel
    } // for Pattern
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

    if ((ByteDoneMask[0] == 0xFF) && (ByteDoneMask[1] == 0xFF)) {
      // Found the limit on all bytes on both channels - no need to sweep Pi any longer
      break;
    }

    PiCode += Step;
    if (Step > 0) {
      // Sweep up
      Done = (PiCode > Stop);
    } else {
      // Sweep down
      Done = (((INT8) PiCode) < Stop);
    }
  }  // while not done
}

/**
  Process the results of the early LPDDR3 CS training and find the best PI settings for CS and CLK.
  Flow:
   1. Find the worst case Right and Left limits for each group
   2. Find the Center for each group

  @param[in]  MrcData     - The MRC global data.
  @param[in]  LeftLimit   - array of left edge values per channel, rank and CPU byte
  @param[in]  RightLimit  - array of right edge values per channel, rank and CPU byte
  @param[out] BestCs      - array of best CS PI settings, per channel and group
  @param[out] BestClk     - array of best CLK PI settings, per channel and group

  @retval mrcSuccess if succeeded
**/
MrcStatus
FindBestCsClkPi (
  IN  MrcParameters * const MrcData,
  IN  UINT8                 LeftLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN  UINT8                 RightLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM],
  OUT UINT8                 BestCs[MAX_CHANNEL][MAX_RANK_IN_CHANNEL],
  OUT UINT8                 BestClk[MAX_CHANNEL][2]
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcChannelIn      *ChannelIn;
  MrcStatus         Status;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             Byte;
  UINT8             Group;
  UINT8             Count;
  UINT8             GroupLeftLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][2];  // Per ch, rank and group
  UINT8             GroupRightLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][2]; // Per ch, rank and group
  UINT8             GroupCenter[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][2];     // Per ch, rank and group
  INT8              ClkDelta[MAX_RANK_IN_CHANNEL];
  INT8              MeanClkDelta;
  INT8              CsDelta[2];  // Per group
  INT8              MeanCsDelta;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;

  MrcCall->MrcSetMem ((UINT8 *) GroupRightLimit, sizeof (GroupRightLimit), 127);
  MrcCall->MrcSetMem ((UINT8 *) GroupLeftLimit, sizeof (GroupLeftLimit), 0);
  MrcCall->MrcSetMem ((UINT8 *) GroupCenter, sizeof (GroupCenter), 0);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Finding best CS/CLK PIs:\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel: %d\tLeft\tRight\tCenter\n", Channel);
    ChannelIn = &Inputs->Controller[0].Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      for (Group = 0; Group < 2; Group++) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          //
          // Find the worst case Right and Left limits for each group
          //
          if (ChannelIn->DQByteMap[MrcIterationClock][Group] & (1 << Byte)) {
            if (GroupRightLimit[Channel][Rank][Group] > RightLimit[Channel][Rank][Byte]) {
              GroupRightLimit[Channel][Rank][Group] = RightLimit[Channel][Rank][Byte];
            }

            if (GroupLeftLimit[Channel][Rank][Group] < LeftLimit[Channel][Rank][Byte]) {
              GroupLeftLimit[Channel][Rank][Group] = LeftLimit[Channel][Rank][Byte];
            }
          }
        } // for Byte

        //
        // Find the Center for each group
        //
        GroupCenter[Channel][Rank][Group] =
          (GroupRightLimit[Channel][Rank][Group] + GroupLeftLimit[Channel][Rank][Group]) / 2;

        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "Rank%d CLK%d\t%d\t%d\t%d\n",
          Rank,
          Group,
          GroupLeftLimit[Channel][Rank][Group],
          GroupRightLimit[Channel][Rank][Group],
          GroupCenter[Channel][Rank][Group]
          );
      } // for Group
    } // for Rank

    //
    // Find the CS delta between ranks for each clock group, and then group average
    //
    for (Count = 0, Group = 0; Group < 2; Group++) {
      if (MrcRankInChannelExist (MrcData, 1, Channel)) {
        CsDelta[Group] = (GroupCenter[Channel][1][Group] - GroupCenter[Channel][0][Group]);
        Count++;
      } else {
        CsDelta[Group] = 0; // Single rank 0 case
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLK%d delta (Rank0-Rank1) = %d  \n", Group, CsDelta[Group]);
    }

    MeanCsDelta = (Count != 0) ? (CsDelta[0] + CsDelta[1]) / Count : 0;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mean CS delta = %d\n", MeanCsDelta);

    //
    // Find the Clock delta for each rank, and then average between ranks
    // @todo Add case of single CLK group
    //
    for (Count = 0, Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        ClkDelta[Rank] = (GroupCenter[Channel][Rank][1] - GroupCenter[Channel][Rank][0]);
        Count++;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank%d delta (CLK1-CLK0) = %d  \n", Rank, ClkDelta[Rank]);
      } else {
        ClkDelta[Rank] = 0; // No such rank
      }
    }
    MeanClkDelta = (Count != 0) ? (ClkDelta[0] + ClkDelta[1]) / Count : 0;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mean Clock delta = %d\n", MeanClkDelta);

    BestClk[Channel][0] = (UINT8) (64 - MeanClkDelta / 2);               // CLK0
    BestClk[Channel][1] = (UINT8) (BestClk[Channel][0] + MeanClkDelta);  // CLK1

    BestCs[Channel][0] = (GroupCenter[Channel][0][0] + GroupCenter[Channel][0][1]) / 2; // CS0
    BestCs[Channel][1] = (GroupCenter[Channel][1][0] + GroupCenter[Channel][1][1]) / 2; // CS1

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Best PI CLK0=%d, CLK1=%d, CS0=%d, CS1=%d\n",
      BestClk[Channel][0],
      BestClk[Channel][1],
      BestCs[Channel][0],
      BestCs[Channel][1]
      );
  } // for Channel

  return Status;
}

/**
  Early CS / CLK training for LPDDR.
  Main flow:
  1. Setup CADB pattern for CS Training.
  2. Run CS vs. CLK training.
  3. Select optimal CS and CLK timings

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess if succeeded
**/
MrcStatus
EarlyChipSelectTraining (
  IN MrcParameters * const MrcData
  )
{
  MrcInput                                    *Inputs;
  MRC_FUNCTION                                *MrcCall;
  MrcDebug                                    *Debug;
  MrcOutput                                   *Outputs;
  MrcControllerIn                             *ControllerIn;
  MrcControllerOut                            *ControllerOut;
  MrcChannelIn                                *ChannelIn;
  MrcChannelOut                               *ChannelOut;
  MrcStatus                                   Status;
  BOOLEAN                                     ClockPiChanged;
  UINT8                                       Channel;
  UINT8                                       Rank;
  UINT8                                       RankBit;
  UINT8                                       Group;
  UINT8                                       RankMask;
  INT32                                       ClkDelta;
  UINT8                                       PiLow;
  UINT8                                       PiHigh;
  UINT8                                       PiMiddle;
  UINT8                                       PiStep;
  UINT8                                       RightLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8                                       LeftLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8                                       BestCs[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  UINT8                                       BestClk[MAX_CHANNEL][2];
#ifdef MRC_DEBUG_PRINT
  UINT8                                       Left;
  UINT8                                       Right;
  UINT8                                       Byte;
  UINT8                                       DramByte;
#endif // MRC_DEBUG_PRINT

  Inputs           = &MrcData->Inputs;
  MrcCall          = Inputs->Call.Func;
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  ControllerIn     = &Inputs->Controller[0];
  ControllerOut    = &Outputs->Controller[0];

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EarlyChipSelectTraining started\n");

  Status = mrcSuccess;
  RankMask  = Outputs->ValidRankMask;

  PiLow    = DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MIN;
  PiHigh   = DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MAX;
  PiMiddle = (DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MIN + DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MAX + 1) / 2; // Will be updated below from the host struct
  PiStep = 2;


  MrcCall->MrcSetMem ((UINT8 *) RightLimit, sizeof (RightLimit), PiHigh);
  MrcCall->MrcSetMem ((UINT8 *) LeftLimit, sizeof (LeftLimit), PiLow);

  //
  // Init DDR IO for CA training
  //
  LpddrCaTrainingInitIo (MrcData);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankBit = 1 << Rank;
    if ((RankBit & RankMask) == 0) {
      continue;
    }

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      PiMiddle = ChannelOut->CtlPiCode[Rank];  // Found in EarlyCsCmdLpddr3()

      //
      // Put the current Rank in CA training mode using MRW41.
      //
      Status = LpddrCommandTrainingMode (MrcData, 1 << Channel, RankBit, CaTrainingMode41);
      if (Status != mrcSuccess) {
        return Status;
      }

      SetupCaTrainingCadb (
        MrcData,
        Channel,
        Rank,
        CadbLinesCs,
        sizeof (CadbLinesCs) / sizeof (CadbLinesCs[0]),
        0x300000,
        0x400000,
        0x000000
        );
    }  // for Channel

    //
    // Sweep CS Pi up and down from the middle, on both channels at the same time
    //
    ChipSelectFindEdge (MrcData, Rank, PiMiddle, PiHigh, PiStep, RightLimit);
    ChipSelectFindEdge (MrcData, Rank, PiMiddle, PiLow, -PiStep, LeftLimit);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
#ifdef MRC_DEBUG_PRINT
      ChannelIn  = &ControllerIn->Channel[Channel];
      ChannelOut = &ControllerOut->Channel[Channel];
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CS training data Ch%d Rank%d\nCPU Byte\tLeft\tRight\tWidth\n", Channel, Rank);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
        if (ChannelOut->Dimm[dDIMM0].SdramWidth == 32) {
          if ((DramByte & 0x02) != 0) {
            //
            // Ignore upper 16 bits on x32 devices in MRW41 feedback - DRAM bytes 2, 3, 6 and 7
            //
            continue;
          }
        }
        Left  = LeftLimit[Channel][Rank][Byte];
        Right = RightLimit[Channel][Rank][Byte];
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t\t%d\t%d\t%d\n", Byte, Left, Right, Right - Left);
      }
#endif // MRC_DEBUG_PRINT
      //
      // Put the CTL PI back to middle for MRW42 command
      //
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 3, 1, PiMiddle, 1);

      //
      // Exit CA training mode on the current rank
      //
      Status = LpddrCommandTrainingMode (MrcData, 1 << Channel, RankBit, CaTrainingMode42);

      if (Status != mrcSuccess) {
        return Status;
      }
    } // for Channel
  }  // for Rank

  //
  // Restore DDR IO values that were used for CA training
  //
  LpddrCaTrainingRestoreIo (MrcData);

  //
  // Select optimal CS and CLK timings for both channels
  //
  FindBestCsClkPi (MrcData, LeftLimit, RightLimit, BestCs, BestClk);

  //
  // Apply the new CTL and CLK PI settings
  //
  ClockPiChanged = FALSE;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelIn  = &ControllerIn->Channel[Channel];
    ChannelOut = &ControllerOut->Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      //
      // Shift CS per rank
      //
      ShiftPIforCmdTraining (
        MrcData,
        Channel,
        MrcIterationCtl,
        1 << Rank,
        1,
        BestCs[Channel][Rank],
        1            // UpdateHost
        );
    }
    for (Group = 0; Group < 2; Group++) {
      //
      // Shift CLK per group, if needed, and update host struct
      //
      ClkDelta = (INT32) BestClk[Channel][Group] - (INT32) ChannelOut->ClkPiCode[Group];
      if (ClkDelta != 0) {
        ClockPiChanged = TRUE;
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, RankMask, 1 << Group, ClkDelta, 1);

        //
        // Shift the corresponding CMD PI by the same amount as the CLK
        //
        if (ChannelIn->DQByteMap[MrcIterationClock][Group] == ChannelIn->DQByteMap[MrcIterationCmdS][0]) {
          //
          // CAA is controlled by CMDS.CmdPi0Code and CKE.CmdPi0Code
          //
          ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, RankMask, (1 << 0),
            ChannelOut->CmdsCmdPiCode[0] + ClkDelta, 1);
          ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCke,  RankMask, (1 << 0),
            ChannelOut->CkeCmdPiCode[0] + ClkDelta, 1);
        }
        if (ChannelIn->DQByteMap[MrcIterationClock][Group] == ChannelIn->DQByteMap[MrcIterationCmdS][1]) {
          //
          // CAB is controlled by CMDS.CmdPi1Code and CMDN.CmdPi1Code
          //
          ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdS, RankMask, (1 << 1),
            ChannelOut->CmdsCmdPiCode[1] + ClkDelta, 1);
          ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmdN, RankMask, (1 << 1),
            ChannelOut->CmdnCmdPiCode[1] + ClkDelta, 1);
        }
      }
    }
  } // for Channel

  //
  // Perform IO reset and JEDEC reset if clock PI was changed.
  //
  if (ClockPiChanged) {
    MrcResetSequence (MrcData);
  }

  return Status;
}
