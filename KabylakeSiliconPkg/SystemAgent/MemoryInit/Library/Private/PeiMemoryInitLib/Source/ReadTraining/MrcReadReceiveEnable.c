/** @file
  Implementation of the receive enable algorithm.
  Receive enable training is made out of two stages, the first is finding the
  DQS rising edge for each DRAM device, and the second is determining the
  roundtrip latency by locating the preamble cycle.

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
#include "MrcReadReceiveEnable.h"

//
// SKL Roundtrip/ IoLatency RTL constraint:
// (RoundtripLatency - IoLatency - IoComp) must be 4 or more
//
// Take into account :
//  - Roundtrip latency will be decreased by 4 when we go to 1N mode (DDR3/4)
//  - Need additional 1 QCLK of IoLatency for RecvEnaX step (LPDDR3)
//
// This constraint is verified in some parts of ReadLeveling training.
//
#define SKL_RT_IOLAT_MIN  (4)

/**
  Perform receive enable training.
  Optimize RcvEn timing with MPR pattern

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if succeeded, return mrcSuccess
**/
MrcStatus
MrcReadLevelingTraining (
  IN OUT MrcParameters *const MrcData
  )
{
  static const MRC_REUTAddress REUTAddress = {
    // Rank, Bank, Row, Col
    {   0,    0,    0,   0    }, // Start
    {   0,    1,    0,   1023 }, // Stop
    {   0,    0,    0,   0    }, // Order
    {   0,    0,    0,   0    }, // IncRate
    {   0,    1,    0,   1    }  // IncValue
  };

  const MrcInput        *Inputs;
  MrcDebug              *Debug;
  const MRC_FUNCTION    *MrcCall;
  MrcIntOutput          *MrcIntData;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcIntChannelOut      *IntChannelOut;
  MrcStatus             Status;
  MrcProfile            Profile;
  MrcDdrType            DdrType;
  BOOLEAN               Lpddr;
  BOOLEAN               Ddr4;
  UINT8                 NumSamples;
  UINT8                 FineStep;
  UINT8                 DumArr[7];
  UINT8                 Channel;
  UINT8                 Rank;
  UINT8                 RankMask;
  UINT8                 Byte;
  UINT8                 ChBitMask;
  UINT8                 ValidRankMask;  // RankBitMask for both channels
  UINT8                 Done;
  UINT8                 Inc;
  UINT16                RLStart;
  UINT16                RLStop;
  UINT16                RLStep0;
  UINT16                RLDelay;
  UINT64                BankMapping[MAX_CHANNEL];
  UINT16                ChResult[MAX_CHANNEL];
  UINT16                ChMask;
  UINT32                Offset;
  UINT32                RtIoComp;
  UINT32                RtLatency;
  UINT32                LatencyConstraint;
  UINT16                PiTicks;
  UINT8                 Roundtrip;
  UINT8                 IoLatency;
  INT32                 InitialPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 InitialPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 CurrentPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 CurrentPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 LargestPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 LargestPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 IncPreAmble[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 cWidth;
  INT32                 lWidth;
  INT32                 Center;
  INT32                 Width;
  BOOLEAN               Pass;
  BOOLEAN               DecreaseRecvEn;
  MRC_WDBPattern        WDBPattern;
  UINT8                 NumCL;
  UINT8                 SamplesAdd;
  UINT8                 Guardband;
  UINT16                TDqsCkDrift;

  DDR4_MODE_REGISTER_3_STRUCT                 Ddr4Mr3;
  DDR4_MODE_REGISTER_4_STRUCT                 Ddr4Mr4;
  DDRDATACH0_CR_DDRCRDATACONTROL0_STRUCT      DdrCrDataControl0;
  DDRDATA0CH0_CR_DDRCRDATACONTROL2_STRUCT     DdrCrDataControl2;
  DDRDATA0CH0_CR_DATATRAINFEEDBACK_STRUCT     DataTrainFeedback;
  MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_STRUCT  ReutChMiscOdtCtrl;

  WDBPattern.IncRate  = 32;
  WDBPattern.Start    = 0;
  WDBPattern.Stop     = 9;
  WDBPattern.DQPat    = BasicVA;
  Status              = mrcSuccess;
  Done                = 0;
  MrcIntData          = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs              = &MrcData->Inputs;
  MrcCall             = Inputs->Call.Func;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  DdrType             = Outputs->DdrType;
  ControllerOut       = &Outputs->Controller[0];
  ChBitMask           = Outputs->ValidChBitMask;
  ValidRankMask       = Outputs->ValidRankMask;
  Profile             = Inputs->MemoryProfile;
  TDqsCkDrift         = tDQSCK_DRIFT;  // Pull in RcvEna by 1 QClk.
  Lpddr               = (DdrType == MRC_DDR_TYPE_LPDDR3);
  Ddr4                = (DdrType == MRC_DDR_TYPE_DDR4);
  MrcCall->MrcSetMem ((UINT8 *) BankMapping, sizeof (BankMapping), 0);

  MrcCall->MrcSetMem (DumArr, sizeof (DumArr), 1);

  NumSamples = 6;
  RLStep0    = 8;
  FineStep   = 1;
  NumCL      = 8; // gives us about tCL*2 + flyby + NumCL*8 + 2(preamble) ~ 86QClk till last dqs (the init RTL should be big enough to overcome this delay !)


  RtIoComp  = HW_IOLATENCY_OFFSET_DELAY;
  IoLatency = MRC_IO_LATENCY_INIT_VALUE;

  if (Outputs->Frequency == f1067) {
    IoLatency = MRC_IO_LATENCY_INIT_VALUE_1067;
  }

  SamplesAdd = MrcLog2 (NumCL) - 1;  // The log function return +1 so we subtract 1
  //
  // CmdPat=PatRd, NumCL, LC, REUTAddress, SOE=0, WDBPattern, EnCADB=0, EnCKE=0, SubSeqWait=4
  //
  SetupIOTest (MrcData, ChBitMask, PatRd, NumCL, NumSamples + SamplesAdd, &REUTAddress, 0, &WDBPattern, 0, 0, 4);

  //
  // Enable RLMode, force ODT and SAmp, set initial roundtrip values.
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    ChannelOut    = &ControllerOut->Channel[Channel];
    IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];

    //
    // Enable ReadLeveling Mode and Force On ODT and SenseAmp
    //
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
      DdrCrDataControl2.Data            = IntChannelOut->DqControl2[Byte].Data;
      DdrCrDataControl2.Bits.ForceRxOn  = 1;
      MrcWriteCR (MrcData, Offset, DdrCrDataControl2.Data);
    }
    Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
    DdrCrDataControl0.Data = IntChannelOut->DqControl0.Data;
    DdrCrDataControl0.Bits.ForceOdtOn     = 1;
    DdrCrDataControl0.Bits.RLTrainingMode = 1;
    MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);

    //
    // Set initial IO Latency, IO_COMP and Roundtrip latency
    //
    RtLatency = RtIoComp + IoLatency + (2 * ChannelOut->Timing[Profile].tCL) + 10;

    ChannelOut->RTIoComp = RtIoComp;
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      ChannelOut->IoLatency[Rank] = IoLatency;
      ChannelOut->RTLatency[Rank] = (UINT8) RtLatency;
    }
    //
    // Write values from host to HW
    //
    MrcHalSetIoLatency (MrcData, Channel);
    MrcHalSetRoundtripLatency (MrcData, Channel);

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
  } // for Channel

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = (1 << Rank);
    if ((RankMask & ValidRankMask) == 0) {
      //
      // Skip if this rank is not present on any of the channels
      //
      continue;
    }

    ChBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChBitMask |= SelectReutRanks (MrcData, Channel, RankMask, 0);
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }

      ChannelOut = &ControllerOut->Channel[Channel];

      if (Ddr4) {
        //
        // Enable MPR mode - needed for DDR4 Read Preamble Training mode
        //
        Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
        Ddr4Mr3.Bits.MprOperation = 1;
        MrcWriteMRS (MrcData, Channel, RankMask, mrMR3, Ddr4Mr3.Data);
        //
        // Enable DDR4 Read Preamble Training mode
        //
        Ddr4Mr4.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR4];
        Ddr4Mr4.Bits.ReadPreambleTrainingMode = 1;
        MrcWriteMRS (MrcData, Channel, RankMask, mrMR4, Ddr4Mr4.Data);
        //
        // Enable MPR mode in MC
        //
        Offset  = MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG +
          ((MCHBAR_CH1_CR_REUT_CH_MISC_ODT_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG) * Channel);
        ReutChMiscOdtCtrl.Data                  = MrcReadCR (MrcData, Offset);
        ReutChMiscOdtCtrl.Bits.MPR_Train_DDR_On = 1;
        MrcWriteCR (MrcData, Offset, ReutChMiscOdtCtrl.Data);
      }
    }
    //
    // ******************************************
    // STEP 1 and 2: Find middle of high region
    // ******************************************
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRank %d\nStep 1 and 2 Find Middle of high region\nCh/Byte\t0\t  1\nRcvEnPi\t", Rank);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %s", "012345678", "012345678");

    RLStart = 128;
    RLStop  = 128 + 192;
    if (Ddr4 && (Outputs->Frequency >= 1867)) {
      RLStart -= 128;
      RLStop  -= 128;
    }
    for (RLDelay = RLStart; RLDelay < RLStop; RLDelay += RLStep0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%d:\t", RLDelay);
      //
      // Program RL Delays:
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          UpdateRxTValues (MrcData, Channel, Rank, Byte, 0, RLDelay);
        }
        //
        // Download new settings from the RegFile to the Pads, using broadcast to all bytes in the channel
        //
        MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);
      }
      //
      // Run Test, Reset FIFOs will be done before running test
      //
      RunIOTest (MrcData, ChBitMask, BasicVA, DumArr, 1, OemReceiveEnable);

      //
      // Update results for all Channels/Bytes
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%s", (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? " " : "  ");
          continue;
        }

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
          Pass = (MrcReadCR (MrcData, Offset) >= (UINT8) (MRC_BIT0 << (NumSamples - 1)));
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", Pass ? "1" : "0");
          if (RLDelay == RLStart) {
            if (Pass) {
              InitialPassingStart[Channel][Byte] = InitialPassingEnd[Channel][Byte]  = RLStart;
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte]  = RLStart;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte]  = RLStart;
            } else {
              InitialPassingStart[Channel][Byte] = InitialPassingEnd[Channel][Byte]  = -RLStep0;
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte]  = -RLStep0;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte]  = -RLStep0;
            }
          } else {
            if (Pass) {
              if (InitialPassingEnd[Channel][Byte] == (RLDelay - RLStep0)) {
                InitialPassingEnd[Channel][Byte] = RLDelay;
              }

              if (CurrentPassingEnd[Channel][Byte] == (RLDelay - RLStep0)) {
                CurrentPassingEnd[Channel][Byte] = RLDelay;
              } else {
                CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte] = RLDelay;
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
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? " " : "  ");
      } // for Channel
    } // for RLDelay

    //
    // Update RcvEn timing to be in the center of the high region.
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }

      ChannelOut = &ControllerOut->Channel[Channel];

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d.R%d:\tLeft\tRight\tWidth\tCenter\n", Channel, Rank);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        Center  = (LargestPassingEnd[Channel][Byte] + LargestPassingStart[Channel][Byte]) / 2;
        Width   = LargestPassingEnd[Channel][Byte] - LargestPassingStart[Channel][Byte];

        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          " B%d:\t%d\t%d\t%d\t%d\n",
          Byte,
          LargestPassingStart[Channel][Byte],
          LargestPassingEnd[Channel][Byte],
          Width,
          Center
          );

        //
        // Check if width is valid
        //
        if ((Width < 32) || (Width > 96)) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_ERROR,
            "\nERROR! Width region (%d) outside expected limits [32..96] for Ch: %u Byte: %u\n",
            Width,
            Channel,
            Byte
            );
          if (Inputs->ExitOnFailure) {
            return mrcReadLevelingError;
          }
        }

        ChannelOut->RcvEn[Rank][Byte] = (UINT16) Center;
        UpdateRxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
      } // for Byte
      //
      // Download new settings from the RegFile to the Pads, using broadcast to all bytes in the channel
      //
      MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);
    }
    //
    // ******************************************************************************
    // STEP 3: Walk Backwards
    // ******************************************************************************
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nStep 3: Quarter Preamble - Walk Backwards\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel     0                 1\nByte        ");
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ?
      "0 1 2 3 4 5 6 7 8      0 1 2 3 4 5 6 7 8" : "0 1 2 3 4 5 6 7      0 1 2 3 4 5 6 7"
      );

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChResult[Channel] = 0x1FF;
    }

    //
    // 0x1FF or 0xFF
    //
    ChMask = (MRC_BIT0 << Outputs->SdramCount) - 1;
    while ((ChResult[0] != 0) || (ChResult[1] != 0)) {
      //
      // Run Test
      //
      RunIOTest (MrcData, ChBitMask, BasicVA, DumArr, 1, OemReceiveEnable);

      //
      // Update results for all Channel/Bytes
      //
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRTL =");

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChResult[Channel] = 0;

        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          if (Channel == 0) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "                       " : "                     "
              );
          }

          continue;
        }

        ChannelOut = &ControllerOut->Channel[Channel];

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %u  ", ChannelOut->RTLatency[Rank]);

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
          DataTrainFeedback.Data  = MrcReadCR (MrcData, Offset);
          Pass                    = (DataTrainFeedback.Bits.DataTrainFeedback >= (UINT16) (1 << (NumSamples - 1)));
          if (Pass) {
            ChResult[Channel] |= (1 << Byte);
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, Pass ? "H " : "L ");
        }
        //
        // Adjust Timing
        //
        Roundtrip = ChannelOut->RTLatency[Rank];
        Roundtrip -= (Lpddr) ? 1 : 4;
        LatencyConstraint = Roundtrip - ChannelOut->IoLatency[Rank] - ChannelOut->RTIoComp;
        if (ChResult[Channel] == ChMask) {  // If no preambles
          //
          // Check the SKL Roundtrip / IoLatency RTL constraint (see file header)
          //
          if ((LatencyConstraint - 2) < SKL_RT_IOLAT_MIN) {
            //
            // We cannot subtract 2 QCLKs from Roundtrip anymore, see if we can at least subtract 1 QCLK.
            // See how many PI ticks we need to subtract from RecvEn.
            //
            if ((LatencyConstraint - 1) >= SKL_RT_IOLAT_MIN) {
              PiTicks = 64;                     // One QCLK using RecvEn, another QCLK using Roundtrip.
              ChannelOut->RTLatency[Rank] -= 1;
              MrcHalSetRoundtripLatency (MrcData, Channel);
            } else {
              PiTicks = 128;                    // Two QCLKs using RecvEn
            }

            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              if (ChannelOut->RcvEn[Rank][Byte] >= PiTicks) {
                ChannelOut->RcvEn[Rank][Byte] -= PiTicks;
              } else if (ChannelOut->RcvEn[Rank][Byte] >= (PiTicks - 28)) { // Last chance to find a preamble
                ChannelOut->RcvEn[Rank][Byte] = 0;
              } else {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nERROR! Ch%u R%u B%u - cannot go backwards anymore\n", Channel, Rank, Byte);
                if (Inputs->ExitOnFailure) {
                  return mrcReadLevelingError;
                }
              }
              UpdateRxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
            } // for Byte
            //
            // Download new settings from the RegFile to the Pads, using broadcast to all bytes in the channel
            //
            MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);
          } else {
            //
            // Adjust Timing globally for all Bytes - Number in Qclks
            //
            ChannelOut->RTLatency[Rank] -= 2;
            MrcHalSetRoundtripLatency (MrcData, Channel);
          }

        } else if ((ChResult[Channel] != 0)) {  // if any preambles
          //
          // Check the SKL Roundtrip / IoLatency RTL constraint (see file header)
          //
          if ((LatencyConstraint - 2) >= SKL_RT_IOLAT_MIN) {
            ChannelOut->IoLatency[Rank] += 2;
            MrcHalSetIoLatency (MrcData, Channel);
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              if ((ChResult[Channel] & (1 << Byte)) == 0) { // if byte is low
                if (ChannelOut->RcvEn[Rank][Byte] < (512 - 128)) {
                  ChannelOut->RcvEn[Rank][Byte] += 128;
                } else {
                  MRC_DEBUG_MSG (
                    Debug,
                    MSG_LEVEL_ERROR,
                    "\nERROR! Channel: %u Rank: %uByte: %u - RcvEn %u/IoLat %u while walking backwards\n",
                    Channel,
                    Rank,
                    Byte,
                    ChannelOut->RcvEn[Rank][Byte],
                    ChannelOut->IoLatency[Rank]
                    );
                  if (Inputs->ExitOnFailure) {
                    return mrcReadLevelingError;
                  }
                }
                UpdateRxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
              }
            } // for Byte
            //
            // Download new settings from the RegFile to the Pads, using broadcast to all bytes in the channel
            //
            MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);
          } else {
            //
            // We cannot add 2 QCLKs to IoLatency anymore, see if we can at least add 1 QCLK.
            // See how many PI ticks we need to subtract from RecvEn.
            //
            if ((LatencyConstraint - 1) >= SKL_RT_IOLAT_MIN) {
              PiTicks = 64;                     // One QCLK using RecvEn, another QCLK using IoLatency.
              ChannelOut->IoLatency[Rank] += 1;
              MrcHalSetIoLatency (MrcData, Channel);
              for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
                if ((ChResult[Channel] & (1 << Byte)) == 0) { // if byte is low
                  if (ChannelOut->RcvEn[Rank][Byte] < (512 - PiTicks)) {
                    ChannelOut->RcvEn[Rank][Byte] += PiTicks;
                  } else {
                    MRC_DEBUG_MSG (
                      Debug,
                      MSG_LEVEL_ERROR,
                      "\nERROR! Channel: %u Rank: %uByte: %u - RcvEn %u/IoLat %u while walking backwards #2\n",
                      Channel,
                      Rank,
                      Byte,
                      ChannelOut->RcvEn[Rank][Byte],
                      ChannelOut->IoLatency[Rank]
                      );
                    if (Inputs->ExitOnFailure) {
                      return mrcReadLevelingError;
                    }
                  }
                  UpdateRxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
                }
              } // for Byte
            } else {
              PiTicks = 128;                    // Two QCLKs using RecvEn
            }
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              if ((ChResult[Channel] & (1 << Byte)) != 0) { // if byte is high
                if (ChannelOut->RcvEn[Rank][Byte] >= PiTicks) {
                  ChannelOut->RcvEn[Rank][Byte] -= PiTicks;
                } else if (ChannelOut->RcvEn[Rank][Byte] >= (PiTicks - 28)) { // Last chance to find a preamble
                  ChannelOut->RcvEn[Rank][Byte] = 0;
                } else {
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nERROR! Ch%u R%u B%u IoLat=%u - cannot go backwards anymore\n",
                    Channel, Rank, Byte, ChannelOut->IoLatency[Rank]);
                  if (Inputs->ExitOnFailure) {
                    return mrcReadLevelingError;
                  }
                }
                UpdateRxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
              }
            } // for Byte
            //
            // Download new settings from the RegFile to the Pads, using broadcast to all bytes in the channel
            //
            MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);
          }
        }
      } // for Channel
    } // while preamble not found on all bytes yet

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];

      //
      // MC read FIFO guardband: Add a number of QCLKs to Roundtrip and compensate by IoLat
      // Use +1 below because we are going to decrement IoLatency in Step 4.
      //
      Guardband = MIN (MRC_MC_FIFO_GUARDBAND, MCHBAR_CH0_CR_SC_IO_LATENCY_Rank_0_flyby_MAX - ChannelOut->IoLatency[Rank] + 1);
      ChannelOut->RTLatency[Rank] += Guardband;
      MrcHalSetRoundtripLatency (MrcData, Channel);

      ChannelOut->IoLatency[Rank] += Guardband;
      MrcHalSetIoLatency (MrcData, Channel);

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Added RTL guardband of %u clocks\nC%u:  Preamble\n", Guardband, Channel);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " B%u: %u\n", Byte, ChannelOut->RcvEn[Rank][Byte]);
      }
    }
    //
    // ******************************************
    // STEP 4: Add 1 qclk
    // ******************************************
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      //
      // Subtract 1 QCLK from IoLatency instead of increasing PI, to avoid PI overflow.
      //
      ChannelOut = &ControllerOut->Channel[Channel];
      ChannelOut->IoLatency[Rank] -= 1;
      MrcHalSetIoLatency (MrcData, Channel);
      //
      // Check that we have enough headroom in RecvEn PI to walk forward 64 ticks in Step 5
      // If not, subtract 64 ticks from RecvEn on all bytes and compensate by subtracting 1 QCLK from IoLatency.
      //
      DecreaseRecvEn = FALSE;
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if ((ChannelOut->RcvEn[Rank][Byte] + 64) > 511) {
          DecreaseRecvEn = TRUE;
        }
      }
      if (DecreaseRecvEn) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%d: Subtract 1 QCLK from RecvEn and IoLatency\n", Channel);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (ChannelOut->RcvEn[Rank][Byte] < 64) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nERROR! Ch%d: RecvEn underflow on byte %d !!\n", Channel, Byte);
            if (Inputs->ExitOnFailure) {
              return mrcReadLevelingError;
            }
          }
          ChannelOut->RcvEn[Rank][Byte] -= 64;
          UpdateRxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
        }
        //
        // Download new settings from the RegFile to the Pads, using broadcast to all bytes in the channel
        //
        MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);

        ChannelOut->IoLatency[Rank] -= 1;
        MrcHalSetIoLatency (MrcData, Channel);
      }
    }
    //
    // ******************************************
    // STEP 5: Walk forward
    // ******************************************
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Step 4/5 Add 1qclk and Walk forward\n");
    //
    // Find Rising Edge
    //
    ChResult[0] = 0;
    ChResult[1] = 0;

    for (Inc = 0; Inc < 64; Inc += FineStep) {
      //
      // Run Test
      //
      RunIOTest (MrcData, ChBitMask, BasicVA, DumArr, 1, OemReceiveEnable);

      //
      // Update results for all Channel/bytes
      //
      Done = 1;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }
        ChannelOut = &ControllerOut->Channel[Channel];

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          //
          // Skip Bytes that are already done
          //
          if (ChResult[Channel] & (1 << Byte)) {
            continue;
          }
          //
          // Check if this byte is done
          //
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
          Pass = (MrcReadCR (MrcData, Offset) >= (UINT8) (1 << (NumSamples - 1)));
          if (Pass) {
            ChResult[Channel] |= (1 << Byte);
          } else {
            ChannelOut->RcvEn[Rank][Byte] += FineStep;
            UpdateRxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
            IncPreAmble[Channel][Byte] = Inc;
          }
        } // for Byte
        //
        // Download new settings from the RegFile to the Pads, using broadcast to all bytes in the channel
        //
        MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);

        if (ChResult[Channel] != ChMask) {
          Done = 0;
        }
      } // for Channel
      //
      // Skip additional testing if all Channel/bytes done
      //
      if (Done) {
        break;
      }
    }
    //
    // Check if Edge was found for all Bytes in the channels
    //
    if (!Done) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_ERROR,
        "Error! Pre-amble edge not found for all Bytes with following final RcvEn results\n"
        );

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }

        ChannelOut = &ControllerOut->Channel[Channel];

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %u Rank %u:  Preamble\n", Channel, Rank);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            " Byte %u: %u %s\n",
            Byte,
            ChannelOut->RcvEn[Rank][Byte],
            ((ChResult[Channel] ^ ChMask) & (1 << Byte)) ? "*** ERROR! Check This Byte ***" : ""
            );
        }
      }

      if (Inputs->ExitOnFailure) {
        return mrcReadLevelingError;
      }
    }
    //
    // ******************************************
    // STEP 6: Sub 1 qclk and Clean Up Rank
    // ******************************************
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Step 6: Mid Preamble\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u:  Preamble Increment\n", Channel);

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        //
        // For Traditional, pull in RcvEn by 64
        // For ULT, Take the DQS drift into account to the specified guardband: tDQSCK_DRIFT.
        //
        ChannelOut->RcvEn[Rank][Byte] -= TDqsCkDrift;

        UpdateRxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);

        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          " B%u: %u      %u\n",
          Byte,
          ChannelOut->RcvEn[Rank][Byte],
          IncPreAmble[Channel][Byte]
          );
      }
      //
      // Download new settings from the RegFile to the Pads, using broadcast to all bytes in the channel
      //
      MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);
    }

    //
    // Clean up DDR4 read preamble mode and MPR mode
    //
    if (Ddr4) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }
        ChannelOut = &ControllerOut->Channel[Channel];
        //
        // Clear MPR mode in MC before sending MRS commands
        //
        Offset = MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG +
          ((MCHBAR_CH1_CR_REUT_CH_MISC_ODT_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG) * Channel);
        ReutChMiscOdtCtrl.Data                  = MrcReadCR (MrcData, Offset);
        ReutChMiscOdtCtrl.Bits.MPR_Train_DDR_On = 0;
        MrcWriteCR (MrcData, Offset, ReutChMiscOdtCtrl.Data);
        //
        // Disable DDR4 Read Preamble Training mode
        //
        Ddr4Mr4.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR4];
        MrcWriteMRS (MrcData, Channel, RankMask, mrMR4, Ddr4Mr4.Data);
        //
        // Disable MPR mode
        //
        Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
        MrcWriteMRS (MrcData, Channel, RankMask, mrMR3, Ddr4Mr3.Data);
      }
    } // if DDR4
  } // END OF RANK LOOP
  //
  // Clean up after Test
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    ChannelOut    = &ControllerOut->Channel[Channel];
    IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];

    Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
    DdrCrDataControl0.Data = IntChannelOut->DqControl0.Data;
    MrcWriteCrMulticast (MrcData, Offset, IntChannelOut->DqControl0.Data);

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
      MrcWriteCR (MrcData, Offset, IntChannelOut->DqControl2[Byte].Data);
    }

    if (Ddr4) {
      //
      // Restore the bank mapping
      //
      Offset = MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG +
        (MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG) * Channel;
      MrcWriteCR64 (MrcData, Offset, BankMapping[Channel]);
    }
  }

  Status = MrcIoReset (MrcData, OemReceiveEnable);

  //
  // Step 7: Try to get IO Lat the same across all ranks per channel
  //

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Step 7: Sync IoLatency Across Ranks\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      Status = MrcChangeRcvEnTiming (
                 MrcData,
                 Channel,
                 RRE_ALL_RANKS_MASK,
                 0,  // ByteMask
                 0,  // Offset
                 RRE_PI_TO_RESERVE
                 );
    }
  }

  //
  // Print IO Latency/RcvEn
  //
#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Adjusted Receive Enable and IO Lat Values\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((MrcRankInChannelExist (MrcData, Rank, Channel))) {
          MRC_DEBUG_MSG (Debug,
            MSG_LEVEL_NOTE,
            "C%d.R%d: Roundtrip = %u, IOLAT = %u  RT_IOCOMP = %d\n",
            Channel,
            Rank,
            ChannelOut->RTLatency[Rank],
            ChannelOut->IoLatency[Rank],
            ChannelOut->RTIoComp
            );
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " B%d: %u\n", Byte, ChannelOut->RcvEn[Rank][Byte]);
          }
        }
      }
    }
  }
#endif

  return Status;
}

/**
  Apply an signed offset to all selected bytes/ ranks in a channel to RcvEn timing
  Robustly handles any carries to/from the IO Latency vs. RcvEn FlyBy
  PiReserve will reserve a certain number of +/- PI ticks for margin purposes
  Routine also minimizes the difference in RcvEn settings across ranks

  @param[in,out] MrcData       - MRC Global Data
  @param[in]     Channel       - The channel to adjust
  @param[in]     RankMask      - Mask of Ranks to adjust
  @param[in]     ByteMask      - Mask of Bytes to adjust by the RcvEnOffset
  @param[in]     RcvEnOffset   - Amount to offset RcvEn
  @param[in]     PiReserve     - The number of PiTicks to reserve on each edge of RcvEn

  @retval MrcStatus - mrcSuccess if successfull
                      mrcWrongInputParameter if channel doesnt exist or a RankMask of 0 is provided
                      mrcReadLevelingError if we over/underflow RT_IOCOMP field.
**/
MrcStatus
MrcChangeRcvEnTiming (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          RankMask,
  IN     const UINT16         ByteMask,
  IN     const INT16          RcvEnOffset,
  IN     const INT16          PiReserve
  )
{
  MRC_FUNCTION                       *MrcCall;
  MrcStatus                          Status;
  MrcOutput                          *Outputs;
  MrcDebug                           *Debug;
  MrcIntOutput                       *MrcIntData;
  MrcIntControllerOut                *IntControllerOut;
  MrcChannelOut                      *ChannelOut;
  MrcIntChannelOut                   *IntChannelOut;
  BOOLEAN                            Lpddr;
  MCHBAR_CH0_CR_SC_IO_LATENCY_STRUCT ScIoLatency;
  UINT8                              Rank;
  UINT8                              Byte;
  INT8                               CycleOffset;
  INT8                               IoGlobalOffset;
  INT8                               IoLatRank[MAX_RANK_IN_CHANNEL];
  INT8                               MaxRankLat;
  INT8                               MinRankLat;
  INT8                               IoLatDelta;
  UINT8                              Roundtrip;
  INT16                              NewRcvEn;
  INT16                              MaxRcvEn;
  INT16                              MinRcvEn;
  INT16                              MaxRcvEnRank[MAX_RANK_IN_CHANNEL];
  INT16                              MinRcvEnRank[MAX_RANK_IN_CHANNEL];
  UINT32                             CrOffset;

  //
  // Init variables with min and max values
  //
  MrcCall        = MrcData->Inputs.Call.Func;
  Status         = mrcSuccess;
  Outputs        = &MrcData->Outputs;
  Debug          = &Outputs->Debug;
  ChannelOut     = &Outputs->Controller[0].Channel[Channel];
  MrcIntData     = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntControllerOut = &MrcIntData->Controller[0];
  IntChannelOut  = &IntControllerOut->Channel[Channel];
  Lpddr          = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  MaxRankLat     = 0;
  MinRankLat     = 15;
  MaxRcvEn       = -4096;
  MinRcvEn       = 4096;
  IoGlobalOffset = 0;
  MrcCall->MrcSetMemWord ((UINT16*) MaxRcvEnRank, MAX_RANK_IN_CHANNEL, (UINT16) (-4096));
  MrcCall->MrcSetMemWord ((UINT16*) MinRcvEnRank, MAX_RANK_IN_CHANNEL, 4096);
  MrcCall->MrcSetMem ((UINT8*) IoLatRank, MAX_RANK_IN_CHANNEL, 0);

  //
  // Quick error check on parameters
  //
  if ((!(MrcChannelExist (Outputs, Channel))) || (RankMask == 0)) {
    return mrcWrongInputParameter;
  }

  //
  // Walk through all the ranks/bytes to find Max/Min RcvEn values
  //
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((((MRC_BIT0 << Rank) & RankMask) != 0) && ((MrcRankInChannelExist (MrcData, Rank, Channel)))) {
      //
      // Find Max/Min for RcvEn across bytes.  RcvEn is the total (RcvEnPi - 64 * IOLat)
      //
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        NewRcvEn = (INT16) ChannelOut->RcvEn[Rank][Byte] - (64 * (INT16) ChannelOut->IoLatency[Rank]);
        if (ByteMask & (MRC_BIT0 << Byte)) {
          //
          // Apply an offset for this byte
          //
          NewRcvEn += RcvEnOffset;
        }

        if (MaxRcvEnRank[Rank] < NewRcvEn) {
          MaxRcvEnRank[Rank] = NewRcvEn;
        }

        if (MinRcvEnRank[Rank] > NewRcvEn) {
          MinRcvEnRank[Rank] = NewRcvEn;
        }
      }
      //
      // Find Max/Min for RcvEn across ranks
      //
      if (MaxRcvEn < MaxRcvEnRank[Rank]) {
        MaxRcvEn = MaxRcvEnRank[Rank];
      }

      if (MinRcvEn > MinRcvEnRank[Rank]) {
        MinRcvEn = MinRcvEnRank[Rank];
      }
    }
  }

  //
  // Determine how far we are from the ideal center point for RcvEn timing.
  // (PiIdeal - AveRcvEn)/64 is the ideal number of cycles we should have for IOLatency
  // Command training will reduce this by 64, so plan for that now in the ideal value
  //

  //
  // Walk through all the ranks and calculate new values of IOLat
  //
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((((MRC_BIT0 << Rank) & RankMask) != 0) && ((MrcRankInChannelExist (MrcData, Rank, Channel)))) {

      IoLatRank[Rank] = (INT8) DIVIDEROUND (RRE_PI_IDEAL - (MaxRcvEnRank[Rank] + MinRcvEnRank[Rank]) / 2, 64); // Round to closest int

      //
      // Check the SKL Roundtrip / IoLatency RTL constraint (see file header),
      // and decrease IoLatency as possible.
      //
      Roundtrip = (Lpddr) ? ChannelOut->RTLatency[Rank] - 1 : ChannelOut->RTLatency[Rank] - 4;
      IoLatDelta = IoLatRank[Rank] + (INT8) ChannelOut->RTIoComp - Roundtrip + SKL_RT_IOLAT_MIN;
      if (IoLatDelta > 0) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "C%d.R%d: Decreasing IoLatency by IoLatDelta: %d\n", Channel, Rank, IoLatDelta);
        IoLatRank[Rank] -= IoLatDelta;
      }

      //
      // Check for RcvEn underflow
      //
      NewRcvEn = 64 * IoLatRank[Rank] + MinRcvEnRank[Rank];
      if (NewRcvEn < PiReserve) {
        IoLatRank[Rank] += (UINT8) ((PiReserve - NewRcvEn + 63) / 64); // Ceiling
      }

      //
      // Check for RcvEn overflow
      //
      NewRcvEn = 64 * IoLatRank[Rank] + MaxRcvEnRank[Rank];
      if (NewRcvEn > (511 - PiReserve)) {
        IoLatRank[Rank] -= (UINT8) ((NewRcvEn - (511 - PiReserve) + 63) / 64); // Ceiling
      }


      //
      // Check for IO Latency over/underflow
      //
      //
      // Update Byte level results
      //
      if ((IoLatRank[Rank] < 16) || (IoLatRank[Rank] > -1)) {
        CycleOffset = IoLatRank[Rank] - (INT8) ChannelOut->IoLatency[Rank];
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          ChannelOut->RcvEn[Rank][Byte] += 64 * (UINT16) CycleOffset;
          if (ByteMask & (MRC_BIT0 << Byte)) {
            ChannelOut->RcvEn[Rank][Byte] += (UINT16) RcvEnOffset;
          }
          UpdateRxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
        }
        //
        // Download new settings from the RegFile to the Pads, using broadcast to all bytes in the channel
        //
        MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);
      } else {
        IoLatRank[Rank] = ChannelOut->IoLatency[Rank]; //restore setting - IoLat out of range
      }
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_ERROR,
        "C%d.R%d: Old: %d  New: %d\n",
        Channel,
        Rank,
        ChannelOut->IoLatency[Rank],
        IoLatRank[Rank]
        );
    }
  } // for Rank

  //
  // Walk through all ranks to program new IO Latency values
  //
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((((MRC_BIT0 << Rank) & RankMask) != 0) && ((MrcRankInChannelExist (MrcData, Rank, Channel)))) {
      ChannelOut->IoLatency[Rank] = IoLatRank[Rank];
    }
  }

  //
  // Program new IO Latency
  //
  MrcHalSetIoLatency (MrcData, Channel);

  // update host
  CrOffset = MCHBAR_CH0_CR_SC_IO_LATENCY_REG +
    ((MCHBAR_CH1_CR_SC_IO_LATENCY_REG - MCHBAR_CH0_CR_SC_IO_LATENCY_REG) * Channel);
  ScIoLatency.Data = MrcReadCR (MrcData, CrOffset);
  IntChannelOut->ScIoLatency.Data = ScIoLatency.Data;

  return Status;
}

/**
  Once the DQS high phase has been found (for each DRAM) the next stage is to find out the round trip latency,
  by locating the preamble cycle. This is achieved by trying smaller and smaller roundtrip
  values until the strobe sampling is done on the preamble cycle.
  The following algorithm is used to find the preamble cycle:

  @param[in] MrcData         - all the global data

  @retval Nothing.
**/
MrcStatus
MrcRoundTripLatency (
  IN     MrcParameters *const MrcData
  )
{
  MrcStatus         Status;
  MrcOutput         *Outputs;
  MrcIntOutput      *MrcIntData;
  MrcControllerOut  *ControllerOut;
  MrcIntControllerOut *IntControllerOut;
  MrcIntChannelOut  *IntChannelOut;
  MrcChannelOut     *ChannelOut;
  MrcInput          *Inputs;
  MrcDebug          *Debug;
  UINT32            Offset;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             OptParam;
  UINT8             RankMask;
  UINT8             TestList[1];
  INT8              ClkShifts[1];
  UINT8             Start;
  UINT8             Stop;
  UINT8             LoopCount;
  UINT8             Update;
  UINT8             MinIoLat;
  UINT8             MaxRankRtl;
  INT8              DeltaLimitRtl;
  UINT8             DeltaRtl;
  UINT8             PowerTrainingMode;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT  TcRdRd;
  MCHBAR_CH0_CR_SC_PCIT_STRUCT  ScPcit;
  MCHBAR_CH0_CR_SC_PCIT_STRUCT  ScPcitSave[MAX_CHANNEL];
  UINT8             StoredRTLatency[MAX_RANK_IN_CHANNEL][MAX_CHANNEL];
  UINT8             StoredIoLatency[MAX_RANK_IN_CHANNEL][MAX_CHANNEL];

  Status        = mrcSuccess;
  TestList[0]   = RdT;        // Test based on read eye width
  LoopCount     = 10;
  Update        = 1;          // Apply the optimal settings
  MaxRankRtl    = 0;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Inputs        = &MrcData->Inputs;
  MrcIntData    = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntControllerOut = &MrcIntData->Controller[0];
  OptParam      = rtl;        // Which parameter to optimize for
  ClkShifts[0] = 25;          // Delay by 25 pi ticks to guardband for delay drift/jitter
  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3) {
    // Additional guardband for tDQSCK drift of 400ps
    ClkShifts[0]  += (INT8) ((400 * 64) / Outputs->Qclkps);
  }

  PowerTrainingMode = 0;
  if (Inputs->PowerTrainingMode == 1) {
    // disable margin training mode to keep the correct UPM limits for this routine
    Inputs->PowerTrainingMode = 0;
    PowerTrainingMode = 1; // save/restore
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    // Change PCIT to 0xFF
    Offset = MCHBAR_CH0_CR_SC_PCIT_REG + (MCHBAR_CH1_CR_SC_PCIT_REG - MCHBAR_CH0_CR_SC_PCIT_REG) * Channel;
    ScPcit.Data = MrcReadCR (MrcData, Offset);
    ScPcitSave[Channel] = ScPcit;
    ScPcit.Bits.PCIT = 0xFF;
    MrcWriteCR (MrcData, Offset, ScPcit.Data);
  }


  //
  // Train timing separately for each rank
  //
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = (MRC_BIT0 << Rank);
    if (!(RankMask & Outputs->ValidRankMask)) {
      continue;
    }
    //
    // Pick starting and stopping points
    //
    Stop      = 0;
    Start     = 0;
    MinIoLat  = 15;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      //Store initial value if convergance will fail so could be restored
      StoredRTLatency[Rank][Channel] = ChannelOut->RTLatency[Rank];
      StoredIoLatency[Rank][Channel] = ChannelOut->IoLatency[Rank];

      if (Stop < ChannelOut->RTLatency[Rank]) {
        Stop = ChannelOut->RTLatency[Rank];
      }

      if (MinIoLat > ChannelOut->IoLatency[Rank]) {
        MinIoLat = ChannelOut->IoLatency[Rank];
      }

      Start = Stop - MinIoLat;
    }

    if ((INT8) Start < 0) {
      Start = 0;
    }
    //
    // Find optimal answer
    //
    Status = TrainDDROptParamCliff (
               MrcData,
               OptParam,
               TestList,
               sizeof (TestList),
               Start,
               Stop,
               LoopCount,
               Update,
               Outputs->MarginResult,
               ClkShifts,
               sizeof (ClkShifts),
               Rank,
               RankMask,
               0
               );
    if (Status == mrcFail) {
      return mrcRoundTripLatencyError;
    }
  }

  //
  // Limit the RTL delta across the ranks present.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nLimit the delta between Rank's RTL value.\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      MaxRankRtl = 0;

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d\n", Channel);
      ChannelOut    = &ControllerOut->Channel[Channel];
      IntChannelOut = &IntControllerOut->Channel[Channel];
      TcRdRd.Data = IntChannelOut->MchbarTcRdRd.Data;
      DeltaLimitRtl = MIN ((INT8) TcRdRd.Bits.tRDRD_dr, (INT8) TcRdRd.Bits.tRDRD_dd);
      //
      // TA Times are in dclks.  Must convert to qclks and subtract the burst length.
      // Ensure we do not underflow the variable.
      //
      DeltaLimitRtl = ((2 * DeltaLimitRtl) - 8);
      DeltaLimitRtl = MAX (DeltaLimitRtl, 0);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RTL Delta Limit: %d\n", DeltaLimitRtl);

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          MaxRankRtl = MAX (MaxRankRtl, ChannelOut->RTLatency[Rank]);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Rank %u RTL: %u\n", Rank, ChannelOut->RTLatency[Rank]);
        }
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MaxRankRtl: %u\n", MaxRankRtl);

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          DeltaRtl = MaxRankRtl - ChannelOut->RTLatency[Rank];
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "Rank %d: DeltaRtl: %u\tDeltaLimitRtl: %u%s",
            Rank,
            DeltaRtl,
            DeltaLimitRtl,
            (DeltaRtl > DeltaLimitRtl) ? "\tNew RTL: " : ""
            );
          if (DeltaRtl > DeltaLimitRtl) {
            if (mrcFail == UpdateTAParamOffset (MrcData, Channel, 0, OptParam, MaxRankRtl - DeltaLimitRtl, 1, 0, 1 << Rank)) {
            //New values failed to converage restoring inital values
              MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "New values failed to converage on channel %x rank %x restoring inital values to all ranks on channel\n", Channel, Rank);
              for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
                if (MrcRankInChannelExist(MrcData, Rank, Channel)) {
                  ChannelOut->RTLatency[Rank] = StoredRTLatency[Rank][Channel];
                  ChannelOut->IoLatency[Rank] = StoredIoLatency[Rank][Channel];
                  MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, " Channel[%d]/Rank[%d]: RTL=%d, IOLatency= %d\n", Channel, Rank, ChannelOut->RTLatency[Rank], ChannelOut->IoLatency[Rank]);
                  //
                  // Write values from host to HW
                  //
                  MrcHalSetIoLatency (MrcData, Channel);
                  MrcHalSetRoundtripLatency (MrcData, Channel);
                }
              }
              break;
            }
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
        }
      }
    }
  }
  // clean up
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    // Restore PCIT Setting
    Offset = MCHBAR_CH0_CR_SC_PCIT_REG + (MCHBAR_CH1_CR_SC_PCIT_REG - MCHBAR_CH0_CR_SC_PCIT_REG) * Channel;
    MrcWriteCR (MrcData, Offset, ScPcitSave[Channel].Data);
  }
  Inputs->PowerTrainingMode = PowerTrainingMode;

  return Status;
}

/**
  Perform Receive Enable Timing Centering.
  Center Receive Enable using moderate pattern with 1D eye.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If successful, returns mrcSuccess.
**/
MrcStatus
MrcReceiveEnTimingCentering (
  IN MrcParameters *const MrcData
  )
{
  UINT8     LoopCount;

  LoopCount = 17;

  return DQTimeCentering1D (MrcData, MrcData->Outputs.ValidChBitMask, RcvEnaX, 0, LoopCount, TRUE, FALSE);
}
