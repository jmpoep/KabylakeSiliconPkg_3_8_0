/** @file
  Once DQS is aligned against the clock in the receive enable training flow,
  the second stage of the read training is the DQ/DQS training, aligning each
  strobe with it's byte of data. The DQ/DQS training is once again using the
  DDR read synchronization mode, in this mode a predetermined pattern is read
  out of the DDR. The following algorithm is used to align the data sampling
  to the best sampling point.

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
#include "MrcReadDqDqs.h"
#include "MrcCrosser.h"


/**
  Perform Read MPR Training.
  Center read DQ-DQS with MPR pattern.

  @param[in, out] MrcData   - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
MrcReadMprTraining (
  IN OUT MrcParameters *const MrcData
  )
{
  return ReadMprTraining (MrcData, TRUE);
}

/**
  Perform Read MPR Training.
  Center read DQ-DQS with MPR pattern.
  This is the HW method of the Read MPR algorithm.

  @param[in, out] MrcData   - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
ReadMprTraining (
  IN OUT MrcParameters *const MrcData,
  IN     BOOLEAN              Print
  )
{
  const MrcInput                              *Inputs;
  MrcDebug                                    *Debug;
  const MRC_FUNCTION                          *MrcCall;
  MrcIntOutput                                *MrcIntData;
  MrcOutput                                   *Outputs;
  MrcChannelOut                               *ChannelOut;
  MrcIntChannelOut                            *IntChannelOut;
  MrcStatus                                   Status;
  MrcStatus                                   MprStatus;
  UINT8                                       Channel;
  UINT8                                       Rank;
  UINT8                                       Byte;
  UINT8                                       ChBitMask;
  UINT8                                       RankMask;  // RankBitMask for both channels
  UINT8                                       LoopCount;
  INT8                                        DqsDelay;
  INT32                                       CurrentPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                       CurrentPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                       LargestPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                       LargestPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                       cWidth;
  INT32                                       lWidth;
  INT32                                       Center;
  INT32                                       Center2;
  INT32                                       Left;
  INT32                                       Right;
  BOOLEAN                                     Pass;
  BOOLEAN                                     Lpddr;
  BOOLEAN                                     Ddr3;
  UINT32                                      *Margin;
#if (SUPPORT_DDR4 == SUPPORT)
  BOOLEAN                                     Ddr4;
  DDR4_MODE_REGISTER_3_STRUCT                 Ddr4Mr3;
  MCSCHEDS_CR_SCHED_CBIT_STRUCT               SchedCbit;
#endif // SUPPORT_DDR4
  UINT32                                      Offset;
  UINT32                                      OdtSampExtendDelay;
  UINT64                                      BankMapping[MAX_CHANNEL];
  MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_STRUCT  ReutChMiscOdtCtrl;
  MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_STRUCT     ReutGlobalCtl;
  DDRDATACH0_CR_DDRCRDATACONTROL0_STRUCT      DdrCrDataControl0;
  DDRDATA0CH0_CR_DDRCRDATACONTROL2_STRUCT     DdrCrDataControl2;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs     = &MrcData->Inputs;
  MrcCall    = Inputs->Call.Func;
  Outputs    = &MrcData->Outputs;
  Debug      = Print ? &Outputs->Debug : NULL;
  Status     = mrcSuccess;
  MprStatus  = mrcSuccess;
  Lpddr      = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  Ddr3       = (Outputs->DdrType == MRC_DDR_TYPE_DDR3);
#if (SUPPORT_DDR4 == SUPPORT)
  Ddr4       = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
#endif // SUPPORT_DDR4

  LoopCount = 10;
  OdtSampExtendDelay  = 1 * HPET_MIN;
  MrcCall->MrcSetMem ((UINT8 *) BankMapping, sizeof (BankMapping), 0);

  //
  // Use basic addressing mode (open a page on a rank and keep writing/reading to it)
  // Rotate through all 8 logical ranks
  // LFSR and LMN disabled.
  //
  ChBitMask = Outputs->ValidChBitMask;
  RankMask  = Outputs->ValidRankMask;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &Outputs->Controller[0].Channel[Channel];

      //
      // Set DQS Delay to 32
      //
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            //
            // Update RxDqsP & RxDqsN - leave other parameter the same; can we update in the next loop or do it per channel
            //
            UpdateRxTValues (MrcData, Channel, Rank, Byte, 5, 32);
          }
          //
          // Download new Read settings from the RegFile to the Pads, using broadcast to all bytes in the channel
          //
          MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);
        }
      }

      //
      // Clear any old state in DataTrain Offset
      //
      MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);

#if (SUPPORT_DDR4 == SUPPORT)
      //
      // Read SCHED_CBIT for Page Table Idle Timer
      //
      Offset = MCHBAR_CH0_CR_SCHED_CBIT_REG + ((MCHBAR_CH1_CR_SCHED_CBIT_REG - MCHBAR_CH0_CR_SCHED_CBIT_REG) * Channel);
      SchedCbit.Data = MrcReadCR (MrcData, Offset);
#endif // SUPPORT_DDR4

      if (Ddr4) {
        //
        // Save Bank Mapping
        //
        Offset = MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG +
          (MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG) * Channel;
        BankMapping[Channel] = MrcReadCR64 (MrcData, Offset);
        //
        // Set the bank mapping so that bank groups are toggled before banks (we will use logical banks 0 and 1 only)
        //
        // Logical Bank:         0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
        //                       -----------------------------------------------
        // Physical Bank:        0  0  2  3  0  1  2  3  0  1  2  3  0  1  2  3
        // Physical Bank Group:  0  1  0  0  1  1  1  1  0  0  0  0  1  1  1  1
        //
        MrcWriteCR64 (MrcData, Offset, 0x7654321076543240ULL);
      }
    }
  }

#if (SUPPORT_DDR4 == SUPPORT)
  if (Ddr4) {
    //
    // Disable Page Table Idle Timer
    //
    SchedCbit.Bits.dis_pt_it = 1;
    MrcWriteCrMulticast (MrcData, MCSCHEDS_CR_SCHED_CBIT_REG, SchedCbit.Data);
  }
#endif // SUPPORT_DDR4

  //
  // Setup REUT Engine
  //
  SetupIOTestMPR (MrcData, ChBitMask, LoopCount, NSOE, 0, 0);

  //
  // Set LoopCount to 0 - Infinite
  //
  MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_0_REG, 0);
  MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_1_REG, 0);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (!((MRC_BIT0 << Rank) & RankMask)) {
      continue; // Skip if both channels empty
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank = %u\n", Rank);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel\t0                1\nByte\t");
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE, (
                        Outputs->SdramCount == (MAX_SDRAM_IN_DIMM)
                        ) ? "0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8" : "0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7"
      );

    //
    // Program MR3 and Mask RAS/WE to prevent scheduler for issuing non-Read commands
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      SelectReutRanks (MrcData, Channel, 1 << Rank, 0);
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      if (Ddr3) {
        Status = MrcWriteMRS (MrcData, Channel, (MRC_BIT0 << Rank), mrMR3, 0x4);
      }
#if (SUPPORT_DDR4 == SUPPORT)
      else if (Ddr4) {
        //
        // Setup MR3 for MPR
        //
        Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
        Ddr4Mr3.Bits.MprOperation = 1;
        Status = MrcWriteMRS (MrcData, Channel, (1 << Rank), mrMR3, Ddr4Mr3.Data);
      }
#endif // SUPPORT_DDR4

      Offset  = MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG +
        ((MCHBAR_CH1_CR_REUT_CH_MISC_ODT_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG) * Channel);
      ReutChMiscOdtCtrl.Data                  = MrcReadCR (MrcData, Offset);
      ReutChMiscOdtCtrl.Bits.MPR_Train_DDR_On = 1;
      MrcWriteCR (MrcData, Offset, ReutChMiscOdtCtrl.Data);
    } // for Channel

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDqsDelay");
    for (DqsDelay = RMPR_DQS_START; DqsDelay < RMPR_DQS_STOP; DqsDelay += RMPR_DQS_STEP) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 5d\t", DqsDelay);

      //
      // Program DQS Delays and download the Reg File for the current rank.
      //
      Status = ChangeMargin (MrcData, RdT, DqsDelay, 0, 1, 0, 0, 0, 0, 0, 0, MrcRegFileStart);

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            (Channel != 0) ? "" : ((Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "                  " : "                ")
            );
        } else {
          ChannelOut    = &Outputs->Controller[0].Channel[Channel];
          IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];

          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            //
            // Force on SenseAmp
            //
            Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
            DdrCrDataControl2.Data              = IntChannelOut->DqControl2[Byte].Data;
            DdrCrDataControl2.Bits.ForceBiasOn  = 1;
            DdrCrDataControl2.Bits.ForceRxOn    = 1;
            DdrCrDataControl2.Bits.LeakerComp   = 0;  // SKL B0 TODO: disable StrongWkLeaker as well
            MrcWriteCR (MrcData, Offset, DdrCrDataControl2.Data);
          }
          //
          // Enable RX Training mode. Turn on the ODT.
          //
          Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
          DdrCrDataControl0.Data = IntChannelOut->DqControl0.Data;
          if (!Lpddr) {
            DdrCrDataControl0.Bits.ForceOdtOn = 1;
          } else {
            DdrCrDataControl0.Bits.OdtSampExtendEn = 1; // W/A to prevent LS glitch
          }
          DdrCrDataControl0.Bits.RxTrainingMode = 1;

          //
          // Need to disable EnReadPreamble
          //
          DdrCrDataControl0.Bits.EnReadPreamble   = 0;
          MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);
        }
      }

      Status = IoReset (MrcData);


      //
      // Start REUT and run for 1uS
      //
      ReutGlobalCtl.Data                    = 0;
      ReutGlobalCtl.Bits.Global_Start_Test  = 1;
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
      // Update results for all ch/bytes
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
          Pass = (MrcReadCR (MrcData, Offset) == 1);

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, Pass ? ". " : "# ");

          if (DqsDelay == RMPR_DQS_START) {
            if (Pass) {
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte] = DqsDelay;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte] = DqsDelay;
            } else {
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte] = -33;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte] = -33;
            }
          } else {
            if (Pass) {
              if (CurrentPassingEnd[Channel][Byte] == (DqsDelay - RMPR_DQS_STEP)) {
                CurrentPassingEnd[Channel][Byte] = DqsDelay;
              } else {
                CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte] = DqsDelay;
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
        }
      }

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          //
          // Restore DataControl2
          //
          Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
          MrcWriteCR (MrcData, Offset, IntChannelOut->DqControl2[Byte].Data);
        }

        //
        // Restore DataControl0 (clear RxTrainingMode and ForceOdtOn)
        //
        Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
        MrcWriteCrMulticast (MrcData, Offset, IntChannelOut->DqControl0.Data);
      } // for Channel

      Status = IoReset (MrcData);
    } // for DqsDelay

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

    //
    // Clean Up registers.
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        ChannelOut = &Outputs->Controller[0].Channel[Channel];

        //
        // MPR_TRAIN_DDR_ON bit will force a special command so clear it before MRS command
        //
        Offset = MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG +
          ((MCHBAR_CH1_CR_REUT_CH_MISC_ODT_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG) * Channel);
        ReutChMiscOdtCtrl.Data                  = MrcReadCR (MrcData, Offset);
        ReutChMiscOdtCtrl.Bits.MPR_Train_DDR_On = 0;
        MrcWriteCR (MrcData, Offset, ReutChMiscOdtCtrl.Data);

        if (Ddr3) {
          Status = MrcWriteMRS (MrcData, Channel, (MRC_BIT0 << Rank), mrMR3, 0x0);
        }
#if (SUPPORT_DDR4 == SUPPORT)
        else if (Ddr4) {
          //
          // Setup MR3 for exiting MPR
          //
          Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
          Status = MrcWriteMRS (MrcData, Channel, (MRC_BIT0 << Rank), mrMR3, Ddr4Mr3.Data);
        }
#endif // SUPPORT_DDR4
        //
        // Clear up after test
        //
        MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u.R%u: \tLeft\tRight\tWidth\tCenter\tRxDqsPN\n", Channel, Rank);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Left  = LargestPassingStart[Channel][Byte];
          Right = LargestPassingEnd[Channel][Byte];
          lWidth = Right - Left;
          Center = Left + (lWidth / 2);
          //
          // Error Handler if eye not found for all bytes
          //
          if (lWidth == 0) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_ERROR,
              "ERROR!! NO EYE found for Channel: %u Rank: %u Byte: %u\n",
              Channel,
              Rank,
              Byte
              );
            //
            // Mark it as zero margin in MarginResult
            //
            Left   = 0;
            Right  = 0;
            Center = 0;
            MprStatus = mrcReadMPRErr;
          } else if (lWidth <= RMPR_MIN_WIDTH) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_WARNING,
              "WARNING!! lWidth <= %u for Channel: %u Rank: %u Byte: %u\n",
              RMPR_MIN_WIDTH,
              Channel,
              Rank,
              Byte
              );
          }
          Center2                         = 32 + Center;
          ChannelOut->RxDqsP[Rank][Byte]  = (UINT8) Center2;
          ChannelOut->RxDqsN[Rank][Byte]  = (UINT8) Center2;
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "  B%u: \t%d\t%d\t%d\t%d\t%d\n",
            Byte,
            Left,
            Right,
            lWidth,
            Center,
            ChannelOut->RxDqsP[Rank][Byte]
            );
          //
          // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Center = %d, RxDqsPN[%d][%d] = %d\n", Center, Channel, Byte, ChannelOut->RxDqsP[Rank][Byte]);
          //
          // Update the MarginResult struct for future tests
          // Store the new margins relative to the center
          //
          Margin    = &Outputs->MarginResult[LastRxT][Rank][Channel][Byte][0];
          Margin[0] = ABS (10 * (Left  - Center));
          Margin[1] = ABS (10 * (Right - Center));
        } // for Byte
      }
    } // for Channel
  } // for Rank

#if (SUPPORT_DDR4 == SUPPORT)
  if (Ddr4) {
    //
    // Re-enable Page Table Idle Timer
    //
    SchedCbit.Bits.dis_pt_it = 0;
    MrcWriteCrMulticast (MrcData, MCSCHEDS_CR_SCHED_CBIT_REG, SchedCbit.Data);
    //
    // Restore the bank mapping
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      Offset = MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG +
        (MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG) * Channel;
      MrcWriteCR64 (MrcData, Offset, BankMapping[Channel]);
    } // for Channel
  }
#endif // SUPPORT_DDR4

  if (MprStatus != mrcSuccess) {
    return MprStatus;
  }

  //
  // Now program the DQS center values on populated ranks, data is taken from the host struct.
  // Need to do it after all ranks are trained, because we need to keep the same DQS value on all ranks
  // during the training.
  //
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          UpdateRxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
        }
        //
        // Download new Read settings from the RegFile to the Pads, using broadcast to all bytes in the channel
        //
        MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);
      }
    }
  }

  //
  // Clean up after Test.  Download the Reg file of the last rank used.
  //
  Status  = ChangeMargin (MrcData, RdT, 0, 0, 1, 0, 0, 0, 0, 0, 0, MrcRegFileCurrent);
  Status  = IoReset (MrcData);
  return Status;
}
// #endif // if 0

/**
  Peform Read Timing Centering.
  Center Rx DQS-DQ using moderate pattern with 1D eye

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus       - if it succeded returns mrcSuccess
**/
MrcStatus
MrcReadTimingCentering (
  IN     MrcParameters *const MrcData
  )
{
  MrcOutput *Outputs;
  UINT8     ResetPerBit;
  UINT8     LoopCount;
  MrcStatus Status;

  Outputs = &MrcData->Outputs;
  ResetPerBit = 1;

  LoopCount   = 10;

  Status =  DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdT, ResetPerBit, LoopCount, TRUE, FALSE);
  IoReset (MrcData);

  return Status;
}

/**
  This function executes the read Voltage centering.
  Center Rx DQ Vref using moderate pattern with 1D eye.

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus      - if it succeded returns mrcSuccess
**/
MrcStatus
MrcReadVoltageCentering (
  IN     MrcParameters *const MrcData
  )
{
  MrcOutput *Outputs;
  UINT8     LoopCount;

  Outputs = &MrcData->Outputs;

  LoopCount   = 10;

  return DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdV, 0, LoopCount, TRUE, FALSE);
}

/**
  Perform Read Timing Centering in 2D.
  Final read timing centering using 2D algorithm and per bit optimization

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus       - if it succeded returns mrcSuccess
**/
MrcStatus
MrcReadTimingCentering2D (
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
             RdT,
             EnPerBit,
             EnRxDutyCycle,
             ResetPerBit,
             LoopCount,
             En2D
             );

  if (mrcSuccess == Status) {
    MrcPerBitDeskew (
      MrcData,
      Outputs->MarginResult,
      RdT
      );

    EnPerBit      = 0;
    EnRxDutyCycle = 1;
    ResetPerBit   = 0;
    En2D          = 1;
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
               RdT,
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
  Peform Read Voltage Centering in 2D.
  Note: This function currently only supports param = RdV

  @param[in,out] MrcData     - Include all MRC global data.
  @param[in,out] MarginByte  - Pointer to Marging Results data structure
  @param[in]     ChBitMask   - Channel bit mask.
  @param[in]     Param       - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                8:WrTBit, 9:RdTBit, 10:RdVBit,
                                16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                ONLY RdV is allowed in this function
  @param[in]     EnPerBit    - Option to enable per bit margining
  @param[in]     ResetPerBit - Option to Reset PerBit Deskew to middle value before byte training
  @param[in]     LoopCount   - Loop count
  @param[in]     En2D        - Option to only run center at nominal Vref point

  @retval MrcStatus - If it succeded return mrcSuccess
**/
MrcStatus
ReadVoltageCentering2D (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT32               MarginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8                ChBitMask,
  IN     UINT8                Param,
  IN     UINT8                EnPerBit,
  IN     UINT8                ResetPerBit,
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
  MrcStatus                               Status;
  UINT8                                   ResultType;
  UINT8                                   Channel;
  UINT8                                   Byte;
  UINT8                                   Rank;
  UINT8                                   MaxRank;
  UINT8                                   RankMask;
  UINT8                                   RankLoop;
  UINT8                                   bit;
  UINT8                                   lcloop;
  UINT8                                   tim;
  UINT8                                   paramB;
  UINT8                                   paramT;
  UINT8                                   BMap[MAX_SDRAM_IN_DIMM];
  INT8                                    SumEH;
  INT8                                    SumEHSign;
  UINT8                                   MaxTscale;
  UINT8                                   SaveLC;
  UINT16                                  mode;
  INT32                                   center[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                   value0[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32                                  BERStats[4];
  UINT32                                  TimScale[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                   CenterSumByte[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                   CenterSumBit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];
  UINT32                                  marginbit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES];
  UINT32                                  EyeShape[3][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32                                  Offset;
  MCHBAR_CH0_CR_REUT_CH_ERR_CTL_STRUCT    ReutChErrCtl;
  UINT32                                  RxOffsetVdq;
  INT8                                    VrefValue;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  Status    = mrcSuccess;
  SumEH     = 0;
  MaxTscale = 12;
  MaxRank   = MAX_RANK_IN_CHANNEL;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  for (lcloop = 0; lcloop < (sizeof (BMap) / sizeof (BMap[0])); lcloop++) {
    BMap[lcloop] = lcloop;
  }
  //
  // Assume rank0 is always popuplated
  //
  if (Param == RdV) {
    paramB = RdVBit;
    paramT = RdT;
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

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (EnPerBit == 1) {
      // For Per bit run centering per Rank to get
      RankMask  = 1 << Rank;
    } else {
      RankMask = 0xF;
    }
    //
    // Reset PerBit Deskew to middle value before Byte training
    // Amplifier voltage offset for bit[x] of the DQ Byte.
    // {0: Most negative offset,... 8: 0 offset, ... 15: Most postive offset}
    //
    if (ResetPerBit == 1) {
      //
      // EnMultiCast=1, 0,0,0,0, UpdateHost=1, SkipWait=0
      //
      Status = ChangeMargin (MrcData, paramB, 0x88888888, 0, 1, 0, Rank, 0, 0, 1, 0, MrcRegFileStart);
    }
    //
    // Select rank for REUT test
    //
    ChBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChBitMask |= SelectReutRanks (MrcData, Channel, RankMask, 0);
      if ((MRC_BIT0 << Channel) & ChBitMask) {
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
    if (!(ChBitMask)) {
      continue;
    }
    //
    // ####################################################
    // ################  Initialize EW/EH variables  ######
    // ####################################################
    //
    Status      = GetMarginByte (MrcData, Outputs->MarginResult, paramT, 0, 0xF);
    ResultType  = GetMarginResultType (paramT);

#ifdef MRC_DEBUG_PRINT
    if (En2D) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n### Measure Eye Height, per BYTE, at %s RankMask = 0x%X\n", "ALL (2D) Timing Points", RankMask);
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n### Measure Eye Height, per BYTE, at %s RankMask = 0x%X\n", "NOMINAL Timing", RankMask);
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

    Status      = GetMarginByte (MrcData, Outputs->MarginResult, Param, 0, 0xF);
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
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nRdTime\t");

      //
      // Setup Timing Offset for this point
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(ChBitMask & (MRC_BIT0 << Channel))) {
          continue;
        }

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          value0[Channel][Byte] = (INT32) (TimePoints[tim] * TimScale[Channel][Byte]) / MaxTscale;
          Status = ChangeMargin (MrcData, paramT, value0[Channel][Byte], 0, 0, Channel, Rank, Byte, 0, 1, 0, MrcRegFileRank);
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
                 0,
                 0xFF,
                 Param,
                 mode,
                 BMap,
                 1,
                 MAX_POSSIBLE_VREF,
                 0,
                 BERStats
                 );

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
            MarginByte[ResultType][0][Channel][Byte][0],
            MarginByte[ResultType][0][Channel][Byte][1]
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
            center[Channel][0][Byte] = (INT32) (MarginByte[ResultType][0][Channel][Byte][1] -
                                                MarginByte[ResultType][0][Channel][Byte][0]);
            if (tim == 0) {
              CenterSumByte[Channel][Byte] = 0;
            }
            //
            // Calculate weight for this point
            //
            CenterSumByte[Channel][Byte] += EHWeights[tim] * center[Channel][0][Byte];

            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", center[Channel][0][Byte] / 20);

            //
            // Record edges for use in per bit margining
            //
            EyeShape[tim][Channel][Byte][0] = MarginByte[ResultType][0][Channel][Byte][0];
            EyeShape[tim][Channel][Byte][1] = MarginByte[ResultType][0][Channel][Byte][1];
          }
        }
      }
      //
      // Loop once at nominal Vref point
      //
      if (En2D == 0) {
        tim = sizeof (TimePoints);
      }
    } // for tim

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

      //
      // Calculate CenterPoint.  Round to Nearest Int
      //
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        SumEHSign                     = (CenterSumByte[Channel][Byte] < 0) ? (-1) : 1;

        CenterSumByte[Channel][Byte]  = (CenterSumByte[Channel][Byte] + 10 * (SumEHSign * SumEH)) / (20 * SumEH);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"%d\t", CenterSumByte[Channel][Byte] / 2);

        //
        // Apply new centerpoint
        // step size for RxVref is about 7.8mv AND for RxVrefOffset is about 3.9mv
        //
        VrefValue = (INT8) ((INT32) ChannelOut->RxVref[Byte] + (CenterSumByte[Channel][Byte] / 2));
        VrefValue = RANGE (VrefValue, -MAX_POSSIBLE_RX_VREF, MAX_POSSIBLE_RX_VREF);
        ChannelOut->RxVref[Byte] = (UINT8) (VrefValue);

        for (RankLoop = 0; RankLoop < MAX_RANK_IN_CHANNEL; RankLoop++) {
          if (MrcRankInChannelExist (MrcData, RankLoop, Channel)) {
            UpdateRxT (MrcData, Channel, RankLoop, Byte, 0xFF, 0);
          }
        }
        //
        // Update the Eye Edges
        //
        for (tim = 0; tim < sizeof (TimePoints); tim++) {
          EyeShape[tim][Channel][Byte][0] = (INT32) EyeShape[tim][Channel][Byte][0] + (10 * CenterSumByte[Channel][Byte]);
          EyeShape[tim][Channel][Byte][1] = (INT32) EyeShape[tim][Channel][Byte][1] - (10 * CenterSumByte[Channel][Byte]);

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
        MarginByte[ResultType][0][Channel][Byte][0] = EyeShape[0][Channel][Byte][0];
        MarginByte[ResultType][0][Channel][Byte][1] = EyeShape[0][Channel][Byte][1];
      } // for Byte

      //
      // Clear up after test
      //
      MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);

      //
      // Propagate new settings from the RegFile to the Pads
      //
      MrcDownloadRegFile (MrcData, Channel, 1, Rank, MrcRegFileRank, 0, 1, 0);
    } // for Channel

#ifdef MRC_DEBUG_PRINT
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRdVref\t");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", (INT8) ChannelOut->RxVref[Byte]);
      }
    }
    //
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nPerByte Margins after per BYTE Centering\nLo-Hi   ");
    //
#endif // MRC_DEBUG_PRINT
    //
    // ####################################################
    // ############    Measure Eye Height Per BIT   ########
    // ####################################################
    //
    if (EnPerBit) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        (En2D) ?
        "\n### Measure Eye Height, per BIT, at ALL (2D) Timing Points\n" :
        "\n### Measure Eye Height, per BIT, at NOMINAL Timing\n"
        );

      //
      // Stop on all lane fail
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
  #ifdef MRC_DEBUG_PRINT
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel      %d", Channel);
          if (Channel == 0) {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t");
            }
          }
  #endif // MRC_DEBUG_PRINT
          //
          // SOE = 11b ( Stop on All Lanes Error )
          //
          Offset = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG + ((MCHBAR_CH1_CR_REUT_CH_ERR_CTL_REG - MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG) * Channel);
          ReutChErrCtl.Data = 0;

          ReutChErrCtl.Bits.Selective_Error_Enable_Chunk = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_Selective_Error_Enable_Chunk_MAX;
          ReutChErrCtl.Bits.Selective_Error_Enable_Cacheline = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_Selective_Error_Enable_Cacheline_MAX;
          ReutChErrCtl.Bits.Stop_On_Error_Control = ALSOE;
          ReutChErrCtl.Bits.Stop_on_Nth_Error     = 1;
          MrcWriteCR (MrcData, Offset, ReutChErrCtl.Data);
        }
      }

  #ifdef MRC_DEBUG_PRINT
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "             Byte % 24d ", Byte);
          }
        }
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  #endif // MRC_DEBUG_PRINT
      //
      // Loop through all the Vref Points to Test
      //
      SaveLC = Outputs->DQPatLC;
      for (tim = 0; tim < sizeof (TimePoints); tim++) {
        //
        // Setup Timing Offset for this point
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {

            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              value0[Channel][Byte] = (INT32) (TimePoints[tim] * TimScale[Channel][Byte]) / MaxTscale;
              Status = ChangeMargin (MrcData, paramT, value0[Channel][Byte], 0, 0, Channel, Rank, Byte, 0, 1, 0, MrcRegFileRank);

              //
              // Amplifier voltage offset for bit[x] of the DQ Byte.
              // {0: Most negative offset,... 8: 0 offset, ... 15: Most postive offset}
              //
              for (bit = 0; bit < MAX_BITS; bit++) {
                marginbit[Channel][Byte][bit][0] = marginbit[Channel][Byte][bit][1] = 8;
              }
            }
          }
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank %d \n", Rank);
        //
        // Run Margin Test
        // Loop through 2 times.  Once at low loop count and Once at high loopcount
        // Improves runtime
        // @TODO: Need 2 loops below if not using BASICVA
        //
        for (lcloop = 0; lcloop < 1; lcloop++) {
          Outputs->DQPatLC  = (lcloop == 0) ? 1 : SaveLC;
          mode              = 0;
          Status            = MrcGetMarginBit (MrcData, ChBitMask, Rank, marginbit, EyeShape[tim], paramB, mode, 15, TRUE);
        }
        //
        // Store Results
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {

            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              for (bit = 0; bit < MAX_BITS; bit++) {
                center[Channel][Rank][Byte] = ((marginbit[Channel][Byte][bit][1] - 8) - (8 - marginbit[Channel][Byte][bit][0]));
                if (tim == 0) {
                  CenterSumBit[Channel][Rank][Byte][bit] = 0;
                }
                //
                // Calculate weight for this point
                //
                CenterSumBit[Channel][Rank][Byte][bit] += EHWeights[tim] * center[Channel][Rank][Byte];
              }
            }
          }
        }

        //
        // Loop once at nominal Vref point
        //
        if (En2D == 0) {
          tim = sizeof (TimePoints);
        }
      } // for tim
      //
      // ####################################################
      // ############   Center Result Per BIT  ##############
      // ####################################################
      //
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nWgted Center ");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(ChBitMask & (MRC_BIT0 << Channel))) {
          continue;
        }

        ChannelOut = &Outputs->Controller[0].Channel[Channel];

        //
        // Calculate and apply CenterPoint.  Round to Nearest Int
        //
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          RxOffsetVdq = 0;

          for (bit = 0; bit < MAX_BITS; bit++) {
            SumEHSign                         = (CenterSumBit[Channel][Rank][Byte][bit] < 0) ? (-1) : 1;

            CenterSumBit[Channel][Rank][Byte][bit]  = (CenterSumBit[Channel][Rank][Byte][bit] + (SumEHSign * SumEH)) / (2 * SumEH);

            //
            // Centerpoint needs to be added to starting DqPb value
            //
            CenterSumBit[Channel][Rank][Byte][bit] += (INT32) ChannelOut->RxDqVrefPb[Rank][Byte][bit].Center;

            //
            // Check for saturation
            //
            if (CenterSumBit[Channel][Rank][Byte][bit] > 15) {
              CenterSumBit[Channel][Rank][Byte][bit] = 15;
            } else if (CenterSumBit[Channel][Rank][Byte][bit] < 0) {
              CenterSumBit[Channel][Rank][Byte][bit] = 0;
            }

            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%x   ", CenterSumBit[Channel][Rank][Byte][bit]);

            //
            // Update MrcData
            //
            ChannelOut->RxDqVrefPb[Rank][Byte][bit].Center = (UINT8) CenterSumBit[Channel][Rank][Byte][bit];

            RxOffsetVdq |= (CenterSumBit[Channel][Rank][Byte][bit] << (DDRDATA0CH0_CR_RXOFFSETVDQRANK0_Lane0_WID * bit));
          } // for bit
          //
          // Apply and propagate new centerpoint
          //
          Status = ChangeMargin (MrcData, RdVBit, RxOffsetVdq, 0, 0, Channel, Rank, Byte, 0, 1, 0, MrcRegFileRank);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "           ");
        } // for Byte

        //
        // Clear up after test
        //
        MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
      } // for Channel
    } // if EnPerBit

    if (EnPerBit == 0) { // We use RankMask = 0x0F in this case
      break;
    }
  } // for Rank
///
/// @attention - This is used to determine if the PerBit routines are correct.  Left for sanity.
///
/*
#ifdef MRC_DEBUG_PRINT
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (ChBitMask & (MRC_BIT0 << Channel)) {
        ChannelOut = &Outputs->Controller[0].Channel[Channel];
        for (Rank = 0; Rank < MaxRank; Rank++) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            Offset = DDRDATA0CH0_CR_RXOFFSETVDQRANK0_REG +
              ((DDRDATA0CH1_CR_RXOFFSETVDQRANK0_REG - DDRDATA0CH0_CR_RXOFFSETVDQRANK0_REG) * Channel) +
              ((DDRDATA1CH0_CR_RXOFFSETVDQRANK0_REG - DDRDATA0CH0_CR_RXOFFSETVDQRANK0_REG) * Byte) +
              (DDRDATA0CH0_CR_RXOFFSETVDQRANK1_REG - DDRDATA0CH0_CR_RXOFFSETVDQRANK0_REG) * Rank;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRdVref = % 3d   RdVBit = 0x%08X", (INT8) ChannelOut->RxVref[Byte],
              MrcReadCR (MrcData, Offset));
          }
        }
      }
    }
#endif // MRC_DEBUG_PRINT
*/
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  //
  // Clean up after test
  //
  Status = ChangeMargin (MrcData, paramT, 0, 0, 1, 0, 0, 0, 0, 1, 0, MrcRegFileRank);

  return Status;
}

/**
  Perform Read Voltage Centering in 2D.
  Note: This function currently only supports param = RdV

  @param[in] MrcData       - Include all MRC global data.

  @retval MrcStatus       - if it succeded return mrcSuccess
**/
MrcStatus
MrcReadVoltageCentering2D (
  IN     MrcParameters *const MrcData
  )
{
  MrcOutput *Outputs;
  MrcStatus Status;
  UINT8     EnPerBit;
  UINT8     ResetPerBit;
  UINT8     LoopCount1;
  UINT8     LoopCount2;
  UINT8     En2D;
  UINT8     Channel;
  BOOLEAN   Ddr4;
  BOOLEAN   Any2Dpc;

  Outputs = &MrcData->Outputs;
  Ddr4    = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Any2Dpc = FALSE;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      if (Outputs->Controller[0].Channel[Channel].DimmCount == 2) {
        Any2Dpc = TRUE;
        break;
      }
    }
  }

  EnPerBit    = 1;
  ResetPerBit = 1;
  En2D        = 0;

  LoopCount1  = 10;  // Lower loopcount for the first 2D pass on DDR4 2DPC
  LoopCount2  = 15;

  Status = ReadVoltageCentering2D (
             MrcData,
             Outputs->MarginResult,
             Outputs->ValidChBitMask,
             RdV,
             EnPerBit,
             ResetPerBit,
             LoopCount2,
             En2D
             );

  if (mrcSuccess == Status) {
    //
    // EnPerBit = 0; ResetPerbit = 0; loopcount = 10; En2D=1
    //
    EnPerBit    = 0;
    ResetPerBit = 0;
    En2D        = 1;
    if (Ddr4 && Any2Dpc) {
      Status = ReadVoltageCentering2D (
                 MrcData,
                 Outputs->MarginResult,
                 Outputs->ValidChBitMask,
                 RdV,
                 EnPerBit,
                 ResetPerBit,
                 LoopCount1,
                 En2D
                 );
    }
    if (Status == mrcSuccess) {
      Status = ReadVoltageCentering2D (
                 MrcData,
                 Outputs->MarginResult,
                 Outputs->ValidChBitMask,
                 RdV,
                 EnPerBit,
                 ResetPerBit,
                 LoopCount2,
                 En2D
                 );
    }
  }

  return Status;
}

/**
  Perform Read Timing Linear Centering in different Read Vref points using MPR mode.
  (Does not require Writes to be functional)

  @param[in] MrcData       - Include all MRC global data.

  @retval MrcStatus       - if it success return mrcSuccess
**/
MrcStatus
MrcEarlyReadMprTimingCentering2D (
  IN     MrcParameters *const MrcData
  )
{
  MrcInput  *Inputs;
  MrcOutput *Outputs;
  MrcStatus Status;
  UINT8     LoopCount;
  INT8      Points2DMin;
  INT8      Points2DMax;
  UINT8     StepSize;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;

  StepSize = (Inputs->MemoryProfile != STD_PROFILE) ? 1 : 4;

  if (Inputs->EnVttOdt) {
    Points2DMin = -12;
    Points2DMax = 12;
  } else {
    Points2DMin = -32;
    Points2DMax = 24;
  }

  LoopCount   = 10;
  Status = EarlyLinearCentering2D (
             MrcData,
             Outputs->ValidChBitMask,
             Outputs->ValidRankMask,
             RdT,
             RdV,
             Points2DMin,
             Points2DMax,
             StepSize,
             LoopCount,
             1, // test type = MPR
             TRUE // DebugPrint
             );

  return Status;
}

/**
  Perform Early Read Timing 2D centering Training.
  Center read DQ-DQS timing while testing differents RxVref points.

  @param[in, out] MrcData   - Include all MRC global data.
  @param[in]      Prints    - Debug prints enable/disable

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
EarlyReadTimingCentering2D (
  IN     MrcParameters *const MrcData,
  IN     BOOLEAN              Prints
  )
{
  MrcOutput *Outputs;
  MrcInput  *Inputs;
  MrcStatus Status;
  UINT8     LoopCount;
  INT8      Points2DMin;
  INT8      Points2DMax;
  UINT8     StepSize;
  UINT8     Ddr4;

  Outputs   = &MrcData->Outputs;
  Inputs    = &MrcData->Inputs;
  Ddr4 = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  if (!Inputs->EnVttOdt && Ddr4) {  //  2D Training Vddq Points
    Points2DMin   = -32;
    Points2DMax   = 24;
    StepSize  = 8;
  } else {                          //  2D Training Nominal Points
    Points2DMin   = -12;
    Points2DMax   = 12;
    StepSize  = 4;
  }
  if (Inputs->MemoryProfile != STD_PROFILE) {  //  Adjust 2D Training Points to include full range of values between min and max
    StepSize  = 1;
  }
  LoopCount   = 10;
  Status = EarlyLinearCentering2D (
             MrcData,
             Outputs->ValidChBitMask,
             Outputs->ValidRankMask,
             RdT,
             RdV,
             Points2DMin,
             Points2DMax,
             StepSize,
             LoopCount,
             0, // test type = normal reads
             Prints
             );

  return Status;
}

/**
  Perform Early Read Timing 2D centering Training.
  Center read DQ-DQS timing while testing differents RxVref points.

  @param[in, out] MrcData   - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
MrcEarlyReadTimingCentering2D (
  IN     MrcParameters *const MrcData
  )
{
  return EarlyReadTimingCentering2D (MrcData, TRUE);
}
