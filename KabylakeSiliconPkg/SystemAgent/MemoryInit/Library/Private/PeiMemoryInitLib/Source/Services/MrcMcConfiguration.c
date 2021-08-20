/** @file
  The functions in this file implement the memory controller registers that
  are not training specific. After these functions are executed, the
  memory controller will be ready to execute the timing training sequences.

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

@par Specification Reference:
**/
//
// Include files
//
#include "MrcMcConfiguration.h"

/**
  This function calculates the two numbers that get you closest to the slope.

  @param[in] Slope - targeted slope (multiplied by 1000 for integer math)

  @retval Returns the Slope Index to be programmed for VtSlope.
**/
UINT8
MrcCalcVtSlopeCode (
  IN const UINT16 Slope
  )
{
  static const INT16 Coding[] = {0, -125, -62, -31, 250, 125, 62, 31}; // 0: 0, 1: -1/8, 2: -1/16, 3: -1/32. 4: +1/4, 5: +1/8, 6: +1/16. 7: +1/32
  INT16     Error;
  INT16     BestError;
  UINT8     BestI;
  UINT8     BestJ;
  UINT8     i;
  UINT8     j;

  BestError = 1000;
  BestI     = 0;
  BestJ     = 0;
  for (i = 0; i < (sizeof (Coding) / sizeof (Coding[0])); i++) {
    for (j = 0; j < (sizeof (Coding) / sizeof (Coding[0])); j++) {
      Error = Slope - (Coding[i] + Coding[j]);
      if (Error < 0) {
        Error = -Error;
      }

      if (BestError > Error) {
        BestError = Error;
        BestI     = i;
        BestJ     = j;
      }
    }
  }

  return (BestI << 3) + BestJ;
}

const UINT8 CompParamList[] = { RdOdt, WrDS, WrDSCmd, WrDSCtl, WrDSClk };

const UINT8 StdCASLat[]   = {7, 9, 11, 13, 14};             // 1067, 1333, 1600, 1867 & 2133 MHz
const UINT8 ByteStagger[] = {0, 4, 1, 5, 2, 6, 3, 7, 8};

// Slew rate order: { SCompDq, SCompCmd, SCompCtl, SCompClk }
const UINT8  BufferStageDelayPS[] = { 59, 53, 53, 53 }; // Slew = 1V / (# Stages * StageDelayPS * Derating)

/**
  This function performs the memory controller configuration non training sequence.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
MrcMcConfiguration (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput          *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  const MrcChannelIn *ChannelIn;
  MrcStatus         Status;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcIntOutput      *MrcIntData;
  MrcIntControllerOut *IntControllerOut;
  MrcIntChannelOut  *IntChannelOut;
  MrcControllerOut  *ControllerOut;
  MrcCpuModel       CpuModel;
  MrcCpuStepping    CpuStepping;
  MrcProfile        Profile;
  MrcVddSelect      Vdd;
  MrcFrequency      DdrFrequency;
  BOOLEAN           Cmd2N;
  UINT32            Offset;
  UINT32            Data32;
  UINT32            RxBias;
  UINT16            VssHiSwingTarget;
  UINT16            vpanic;
  UINT16            SAFE;
  UINT16            NS;
  UINT16            VssHi;                                        // Target VssHi Voltage
  UINT16            Target;
  UINT16            Slope;
  INT8              RxFselect;
  UINT8             delta;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             Byte;
  UINT8             VddHi;
  UINT8             OverClock;
  UINT8             MinLatency;
  UINT8             Latency[MAX_CHANNEL];
  UINT8             ChannelLatency;
  UINT8             RxCBSelect;
  UINT8             stagger;
  UINT8             Any2dpc;
  UINT8             i;
  DDRDATA_CR_RXTRAINRANK0_STRUCT                RxTrainRank;
  DDRDATA_CR_TXTRAINRANK0_STRUCT                TxTrainRank;
  DDRDATA_CR_DDRCRDATACONTROL0_STRUCT           DdrCrDataControl0;
  DDRDATA_CR_DDRCRDATACONTROL1_STRUCT           DdrCrDataControl1;
  DDRDATA0CH0_CR_DDRCRDATACONTROL2_STRUCT       DdrCrDataControl2;
  BOOLEAN                                       Lpddr;
  UINT32                                        Group;
  UINT32                                        Cke;
  UINT32                                        CkeRankMapping;
  DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_STRUCT       DdrCrCompVssHiControl;
  DDRDATA_CR_DDRCRVREFADJUST1_STRUCT            DdrCrVrefAdjust;
  DDRCLKCH0_CR_DDRCRCLKCONTROLS_STRUCT          DdrCrClkControls;
  DDRCMDCH0_CR_DDRCRCMDCONTROLS_STRUCT          DdrCrCmdControls;
  DDRCKECH0_CR_DDRCRCTLCONTROLS_STRUCT          DdrCrCkeControls;
  DDRCTLCH0_CR_DDRCRCTLCONTROLS_STRUCT          DdrCrCtlControls;
  DDRCKECTLCH0_CR_DDRCRCTLPICODING_STRUCT       DdrCrCtlPiCoding;
  DDRCMDCH0_CR_DDRCRCMDPICODING_STRUCT          DdrCrCmdPiCoding;
  DDRCLKCH0_CR_DDRCRCLKRANKSUSED_STRUCT         DdrCrClkRanksUsed;
  DDRCTLCH0_CR_DDRCRCTLRANKSUSED_STRUCT         CtlDdrCrCtlRanksUsed;
  DDRCKECH0_CR_DDRCRCTLRANKSUSED_STRUCT         CkeDdrCrCtlRanksUsed;
  DDRCOMP_CR_DDRCRCOMPVSSHI_STRUCT              DdrCrCompVssHi;
  DDRSCRAM_CR_DDRMISCCONTROL0_STRUCT            DdrMiscControl;
  PCU_CR_M_COMP_PCU_STRUCT                      CrMCompPcu;
#if (SUPPORT_DDR4 == SUPPORT)
  BOOLEAN                                       Ddr4;
#endif // SUPPORT_DDR4
  UINT32                                        Itarget;
  UINT32                                        PanicCompDnMult;
  UINT32                                        PanicCompUpMult;
  UINT32                                        PanicThreshold;
  DDRCOMP_CR_DDRCRCOMPOVR_STRUCT                CompDdrCrCompOvr;
  DDRCOMP_CR_DDRCRCOMPCTL1_STRUCT               DdrCrCompCtl1;
  DDRCOMP_CR_DDRCRCOMPCTL2_STRUCT               DdrCrCompCtl2;
  DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_STRUCT        DdrCrClkCompOffset;
  DDRDATA0CH0_CR_DDRCRVTTGENCONTROL_STRUCT      VttGenControl;
  DDRCLK_CR_DDRVSSHICOMPCTL_STRUCT              VssHiCompCtl;
  DDRDATA_CR_DLLPITESTANDADC_STRUCT             DataDllPiTestAndAdc;
  DDRCKECTL_CR_DLLPITESTANDADC_STRUCT           DllPiTestAndAdc;
  BOOLEAN                                       DqPinsInterleaved;
  BOOLEAN                                       DtHalo;
  UINT8                                         StageDelay;

  MrcIntData        = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntControllerOut  = &MrcIntData->Controller[0];
  Inputs            = &MrcData->Inputs;
  MrcCall           = Inputs->Call.Func;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  ControllerOut     = &Outputs->Controller[0];
  Profile           = Inputs->MemoryProfile;
  Status            = mrcSuccess;
  CpuModel          = Inputs->CpuModel;
  CpuStepping       = Inputs->CpuStepping;
  Vdd               = Outputs->VddVoltage[Inputs->MemoryProfile];
  VddHi             = 0;
  OverClock         = 0;
  MinLatency        = 24;
  SAFE              = 0;
  VssHiSwingTarget  = 950;  // VssHi target voltage in mV
  vpanic            = 24;   // Panic Treshold at 24 mV
  delta             = 20;   // VssHi change voltage during panic, in mV
  DqPinsInterleaved = (Inputs->DqPinsInterleaved != 0);
  DtHalo            = ((CpuModel == cmSKL_DT_HALO) || (CpuModel == cmKBL_DT_HALO));

  MrcCall->MrcSetMem (Latency, sizeof (Latency), 0);

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    ControllerOut->DeviceId   = (UINT16) (MrcPciRead32 (MrcData, HOST_BRIDGE_BUS, HOST_BRIDGE_DEVICE, HOST_BRIDGE_FUNCTION, HOST_BRIDGE_DEVID) >> 16);
    ControllerOut->RevisionId = (UINT8)  (MrcPciRead32 (MrcData, HOST_BRIDGE_BUS, HOST_BRIDGE_DEVICE, HOST_BRIDGE_FUNCTION, HOST_BRIDGE_REVID));
  }


  //
  // Make sure tCL-tCWL <= 4
  // This is needed to support ODT properly for 2DPC case
  // TODO: do we need this for SKL ?
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      if (ChannelOut->DimmCount == 2) {
        if ((ChannelOut->Timing[Profile].tCL - ChannelOut->Timing[Profile].tCWL) > 4) {
          ChannelOut->Timing[Profile].tCWL = ChannelOut->Timing[Profile].tCL - 4;
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "(tCL-tCWL) > 4, CH %u - tCWL has been updated to %u\n",
            Channel,
            ChannelOut->Timing[Profile].tCWL
            );
        }
      }
    }
  }

  //
  // Set memory controller frequency
  //
  if (MrcInternalCheckPoint (MrcData, OemFrequencySet, NULL) == mrcSuccess) {
    Status = McFrequencySet (MrcData);
    if (Status != mrcSuccess) {
      return Status;
    }
  }
  MrcInternalCheckPoint (MrcData, OemFrequencySetDone, NULL);
  Outputs->Qclkps = (UINT16) (Outputs->MemoryClock / (2 * 1000)); // QCLK period in pico seconds.
  DdrFrequency = Outputs->Frequency;

  //
  // Check if LPDDR3 memory is used
  //
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  Ddr4 = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  //
  // Select the interleaving mode of DQ/DQS pins
  // This must be the first DDR IO register to be programmed on ULT
  //
  DdrMiscControl.Data                   = 0;
  DdrMiscControl.Bits.DdrNoChInterleave = (Inputs->DqPinsInterleaved) ? 0 : 1;
  DdrMiscControl.Bits.DllDataWeakLckEn  = (Inputs->WeaklockEn) ? 1 : 0;
  if (Lpddr) {
    DdrMiscControl.Bits.LPDDR_Mode = 1;
    //
    // Initialize the CKE-to-rank mapping for LPDDR
    //
    DdrMiscControl.Bits.CKEMappingCh0 = Inputs->CkeRankMapping & 0x0F;
    DdrMiscControl.Bits.CKEMappingCh1 = (Inputs->CkeRankMapping >> 4) & 0x0F;
#if (SUPPORT_DDR4 == SUPPORT)
  } else if (Ddr4) {
    DdrMiscControl.Bits.Ddr4_Mode = 1;
#endif // SUPPORT_DDR4
  }
  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL0_REG, DdrMiscControl.Data);
  //
  // Save MRC Version into CR
  //
  MrcSetMrcVersion (MrcData);

  Any2dpc = 0;
  if (Vdd > VDD_1_35) {
    VddHi = 1;                                  // Set HiVdd bit if Vdd is over 1.35v
  }

  NS        = ~SAFE;

  //
  // RX BIAS calculations
  //
  GetRxFselect (MrcData, &RxFselect, &RxCBSelect);

  // TODO: Get SKL table
  RxFselect = MIN (RxFselect, RXF_SELECT_MAX_ULT);    // Maximum 1600 MHz

  //
  // Determine Overclocking
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut       = &ControllerOut->Channel[Channel];
      Latency[Channel] = (UINT8) ChannelOut->Timing[Profile].tCL;
      if (Latency[Channel] < MinLatency) {
        MinLatency = Latency[Channel];
      }
    }
  }

  if ((DdrFrequency > 2133) || (MinLatency < StdCASLat[ (UINT8) RxFselect])) {
    OverClock = 1;
  }

  //
  // Initialize ValidChBitMask and ValidRankMask used during all training steps
  // Program various Rank Occupancy / RanksUsed bits.
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    ChannelIn = &Inputs->Controller[0].Channel[Channel];

    //
    // Set the Rank_occupancy per channel.
    //
    Offset = MCHBAR_CH0_CR_MC_INIT_STATE_REG +
      ((MCHBAR_CH1_CR_MC_INIT_STATE_REG - MCHBAR_CH0_CR_MC_INIT_STATE_REG) * Channel);
    MrcWriteCR8 (MrcData, Offset, ChannelOut->ValidRankBitMask);

    if (!MrcChannelExist (Outputs, Channel)) {
      //
      // Set RanksUsed to 0 in CLK, CTL and CKE fubs
      //
      Offset = DDRCLKCH0_CR_DDRCRCLKRANKSUSED_REG +
        ((DDRCLKCH1_CR_DDRCRCLKRANKSUSED_REG - DDRCLKCH0_CR_DDRCRCLKRANKSUSED_REG) * Channel);
      MrcWriteCR (MrcData, Offset, 0);

      Offset = DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG +
        ((DDRCTLCH1_CR_DDRCRCTLRANKSUSED_REG - DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG) * Channel);
      MrcWriteCR (MrcData, Offset, 0);

      Offset = DDRCKECH0_CR_DDRCRCTLRANKSUSED_REG +
        ((DDRCKECH1_CR_DDRCRCTLRANKSUSED_REG - DDRCKECH0_CR_DDRCRCTLRANKSUSED_REG) * Channel);
      MrcWriteCR (MrcData, Offset, 0);

      continue;
    }

    if (ChannelOut->DimmCount == 2) {
      Any2dpc++;
    }

    Outputs->ValidChBitMask |= (1 << Channel);
    Outputs->ValidRankMask  |= ChannelOut->ValidRankBitMask;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "C%uValidRankBitMask / ValidRankMask - 0x%x / 0x%x\n",
      Channel,
      ChannelOut->ValidRankBitMask,
      Outputs->ValidRankMask
      );

    //
    // Initialize RanksUsed in CLK fub
    //
    DdrCrClkRanksUsed.Data = 0;
    DdrCrClkRanksUsed.Bits.RankEn = ChannelOut->ValidRankBitMask;
    if (Inputs->Ddr4DdpSharedClock) {       // CLK0 is shared between Rank0 and Rank1
      DdrCrClkRanksUsed.Bits.RankEn &= 0xD; // CLK1 is not used, save power
    }
    if (Lpddr) {
      //
      // On LPDDR the CLK RanksUsed goes by CLK group instead of by Rank
      //
      DdrCrClkRanksUsed.Bits.RankEn = 0;
      for (Group = 0; Group < 2; Group++) {
        if (ChannelIn->DQByteMap[MrcIterationClock][Group] != 0) {
          DdrCrClkRanksUsed.Bits.RankEn |= (1 << Group);
        }
      }
    }
    Offset = DDRCLKCH0_CR_DDRCRCLKRANKSUSED_REG +
      ((DDRCLKCH1_CR_DDRCRCLKRANKSUSED_REG - DDRCLKCH0_CR_DDRCRCLKRANKSUSED_REG) * Channel);
    MrcWriteCR (MrcData, Offset, DdrCrClkRanksUsed.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCLKCH%d_CR_DDRCRCTLRANKSUSED = 0x%X\n", Channel, DdrCrClkRanksUsed.Data);

    //
    // Initialize RanksUsed in CTL fub - CS (and ODT for LPDDR)
    //
    CtlDdrCrCtlRanksUsed.Data = 0;
    CtlDdrCrCtlRanksUsed.Bits.RankEn = ChannelOut->ValidRankBitMask;
    //
    // Keep ODT pins enabled until the end of JEDEC Reset/Init
    // This register will be updated at the end of JEDEC Init.
    //
    CtlDdrCrCtlRanksUsed.Bits.OdtDisable = 0;

    Offset = DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG +
      ((DDRCTLCH1_CR_DDRCRCTLRANKSUSED_REG - DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG) * Channel);
    MrcWriteCR (MrcData, Offset, CtlDdrCrCtlRanksUsed.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCTLCH%d_CR_DDRCRCTLRANKSUSED = 0x%X\n", Channel, CtlDdrCrCtlRanksUsed.Data);

    //
    // Initialize RanksUsed in CKE fub
    //
    CkeDdrCrCtlRanksUsed.Data = 0;
    CkeDdrCrCtlRanksUsed.Bits.RankEn = ChannelOut->ValidRankBitMask;
    if (Lpddr) {
      CkeDdrCrCtlRanksUsed.Bits.RankEn = 0;
      //
      // Use CKE-to-Rank mapping: [3:0] - Channel 0, [7:4] - Channel 1
      //
      CkeRankMapping = (Inputs->CkeRankMapping >> (Channel * 4)) & 0x0F;
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        for (Cke = 0; Cke <= 3; Cke++) {
          if (((CkeRankMapping >> Cke) & 1) == Rank) {
            //
            // This CKE pin is connected to this Rank...
            //
            if (ChannelOut->ValidRankBitMask & (1 << Rank)) {
              //
              // ...and this rank is enabled
              //
              CkeDdrCrCtlRanksUsed.Bits.RankEn |= (1 << Cke);
            }
          }
        }
      }
      if (Inputs->ForceSingleRank) {
        // Need to keep CKE1 enabled for T-topology CKE like on RVP1
        CkeDdrCrCtlRanksUsed.Bits.RankEn |= (1 << 1);
      }
    }
    Offset = DDRCKECH0_CR_DDRCRCTLRANKSUSED_REG +
      ((DDRCKECH1_CR_DDRCRCTLRANKSUSED_REG - DDRCKECH0_CR_DDRCRCTLRANKSUSED_REG) * Channel);
    MrcWriteCR (MrcData, Offset, CkeDdrCrCtlRanksUsed.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCKECH%d_CR_DDRCRCTLRANKSUSED = 0x%X\n", Channel, CkeDdrCrCtlRanksUsed.Data);
    //
    // Save for future use in JEDEC Reset, etc.
    //
    ChannelOut->ValidCkeBitMask = (UINT8) CkeDdrCrCtlRanksUsed.Bits.RankEn;
  }  //  for Channel

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init Data CRs\n");


  //
  // Initialize Rx and Tx Data CRs
  //
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (((1 << Rank) & Outputs->ValidRankMask) == 0) {
      continue;
    }
    //
    // RxDqsN/P_Pi = 32, RcvEn = 64
    //
    RxTrainRank.Data           = 0;
    RxTrainRank.Bits.RxRcvEnPi = 64;
    RxTrainRank.Bits.RxDqsPPi  = 32;
    RxTrainRank.Bits.RxDqsNPi  = 32;
    RxTrainRank.Bits.RxEq      = 0;  // Start with Rx Equalization Disabled
    //
    // RxGroup - Broadcast all channels
    //
    Offset = DDRDATA_CR_RXTRAINRANK0_REG + ((DDRDATA_CR_RXTRAINRANK1_REG - DDRDATA_CR_RXTRAINRANK0_REG) * Rank);
    MrcWriteCrMulticast (MrcData, Offset, RxTrainRank.Data);

    //
    // Rx per bit offset - Middle value. Train later.
    //
    Offset = DDRDATA_CR_RXPERBITRANK0_REG + ((DDRDATA_CR_RXPERBITRANK1_REG - DDRDATA_CR_RXPERBITRANK0_REG) * Rank);
    Data32 = SAFE ? 0 : 0x88888888;
    MrcWriteCrMulticast (MrcData, Offset, Data32);

    //
    // Set TxEq to full strength, TxDqs = 0 and TxDq = 32,
    //
    TxTrainRank.Data                = 0;
    // SKL TODO: ULT/ULX vs. DT/Halo ?
    TxTrainRank.Bits.TxEqualization = 0x3F;  // Full Drive
    TxTrainRank.Bits.TxDqDelay      = 96;
    TxTrainRank.Bits.TxDqsDelay     = 64;

    Offset = DDRDATA_CR_TXTRAINRANK0_REG + ((DDRDATA_CR_TXTRAINRANK1_REG - DDRDATA_CR_TXTRAINRANK0_REG) * Rank);
    MrcWriteCrMulticast (MrcData, Offset, TxTrainRank.Data);
    //
    // Middle value. Train later.
    //
    Offset = DDRDATA_CR_TXPERBITRANK0_REG + ((DDRDATA_CR_TXPERBITRANK1_REG - DDRDATA_CR_TXPERBITRANK0_REG) * Rank);
    MrcWriteCrMulticast (MrcData, Offset, 0x88888888);

    //
    // Save in MrcData
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Byte = 0; Byte < MAX_SDRAM_IN_DIMM; Byte++) {
        ChannelOut->TxDq[Rank][Byte]    = (UINT16) (TxTrainRank.Bits.TxDqDelay);
        ChannelOut->TxDqs[Rank][Byte]   = (UINT16) (TxTrainRank.Bits.TxDqsDelay);
        ChannelOut->TxEq[Rank][Byte]    = (UINT8) (TxTrainRank.Bits.TxEqualization);

        ChannelOut->RcvEn[Rank][Byte]   = (UINT16) (RxTrainRank.Bits.RxRcvEnPi);
        ChannelOut->RxDqsP[Rank][Byte]  = (UINT8) (RxTrainRank.Bits.RxDqsPPi);
        ChannelOut->RxDqsN[Rank][Byte]  = (UINT8) (RxTrainRank.Bits.RxDqsNPi);
        ChannelOut->RxEq[Rank][Byte]    = (UINT8) (RxTrainRank.Bits.RxEq);
      }
    }
  } // for Rank

  if (Ddr4) {
    MrcSetDefaultRxVrefDdr4 (MrcData, TRUE, TRUE);
  }

  //
  // Initial value to corresponding 0.
  //
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_TXXTALK_REG, 0x0);
  //
  // Amplifier voltage offset {0: Most negative offset,... 8: 0 offset, ... 15: Most postive offset}
  //
  MrcSetRxOffsetVdqBroadcast (MrcData, 0xFF, 0xFF, 0x88888888);
  MrcWriteCrMulticast (MrcData, MrcGetOffsetDataOffsetTrain (MrcData, 0xFF, 0xFF), 0x0);
  MrcWriteCrMulticast (MrcData, MrcGetOffsetDataOffsetComp (MrcData, 0xFF, 0xFF), 0x0);

  //
  // Initialize CompCtl2
  //
  DdrCrCompCtl2.Data = 0;
  DdrCrCompCtl2.Bits.EnVddqOdt        = Inputs->EnVttOdt ? 0 : Ddr4;
  DdrCrCompCtl2.Bits.EnVttOdt         = Inputs->EnVttOdt;
  DdrCrCompCtl2.Bits.Cben             = 3;
  DdrCrCompCtl2.Bits.CmdDrvVref200ohm = 8;
  IntControllerOut->CompCtl2.Data     = DdrCrCompCtl2.Data;
  MrcWriteCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL2_REG, DdrCrCompCtl2.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CompCtl2=0x%08X\n", DdrCrCompCtl2.Data);

  //
  // Initialize DataControl0/1/2
  //
  DdrCrDataControl0.Data                  = 0;
  DdrCrDataControl0.Bits.DataVccddqHi     = VddHi;
  DdrCrDataControl0.Bits.DisableOdtStatic = 0;
  if (Lpddr) {
    DdrCrDataControl0.Bits.LPDDR_Mode       = 1;
    DdrCrDataControl0.Bits.EarlyRleakEn     = 1;  // Mutually exclusive with DdrCrDataControl0.EnReadPreamble
    DdrCrDataControl0.Bits.OdtSampExtendEn  = 0;
  }
  Offset = MrcGetOffsetDataControl0 (MrcData, 0xFF, 0xFF);
  MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);

  DdrCrDataControl1.Data = 0;
  DdrCrDataControl1.Bits.DllMask          = 1;                                                 // 2 qclk DLL mask
  DdrCrDataControl1.Bits.OdtDelay         = -2;
  DdrCrDataControl1.Bits.SenseAmpDelay    = -2;
  DdrCrDataControl1.Bits.SenseAmpDuration = DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDuration_MAX; // Max Samp Duration.
  DdrCrDataControl1.Bits.OdtDuration      = DDRDATA_CR_DDRCRDATACONTROL1_OdtDuration_MAX;      // Max Odt Duration.
  //
  // Pick RxBias value according to DDR frequency
  //
  if (DdrFrequency >= f1867) {
    RxBias = 8;
  } else if (DdrFrequency >= f1600) {
    RxBias = 10;
  } else if (DdrFrequency >= f1333) {
    RxBias = 13;
  } else {
    RxBias = 15;
  }
  DdrCrDataControl1.Bits.RxBiasCtl = RxBias;

  if (Lpddr) {
    DdrCrDataControl1.Bits.StrongWkLeaker = Inputs->StrongWkLeaker;
  }

  MrcWriteCrMulticast (MrcData, MrcGetOffsetDataControl1 (MrcData, 0xFF, 0xFF), DdrCrDataControl1.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DataControl1=0x%08X\n", DdrCrDataControl1.Data);

  DdrCrDataControl2.Data = 0;       // Define DQControl2

  DdrCrDataControl2.Bits.RxDqsAmpOffset = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_DEF;
  DdrCrDataControl2.Bits.RxClkStgNum    = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MAX;
  if (Lpddr) {
    DdrCrDataControl2.Bits.LeakerComp = 3;
  }

  DdrCrDataControl2.Bits.EnVddqOdt      = IntControllerOut->CompCtl2.Bits.EnVddqOdt;
  DdrCrDataControl2.Bits.EnVttOdt       = IntControllerOut->CompCtl2.Bits.EnVttOdt;
  DdrCrDataControl2.Bits.RxVrefProgMFC  = IntControllerOut->CompCtl2.Bits.EnVttOdt;
  DdrCrDataControl2.Bits.Cben           = IntControllerOut->CompCtl2.Bits.Cben;

  if (Inputs->EnableVrefPwrDn) {
    DdrCrDataControl2.Bits.EnableVrefPwrDn = 1;
  }
  if (Ddr4) {
    DdrCrDataControl2.Bits.Ddr4Mode = 1;
  }

  if (SAFE) {
    //
    // Disable per-bit deskew if SAFE mode
    //
    DdrCrDataControl2.Bits.RxDeskewDisable = 1;
    DdrCrDataControl2.Bits.TxDeskewDisable = 1;
  }

  if (DdrFrequency < f1600) {
    DdrCrDataControl2.Bits.TxDeskewDisable = 1;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel) || Inputs->EnVttOdt) {
      ChannelOut                     = &ControllerOut->Channel[Channel];
      IntChannelOut                  = &MrcIntData->Controller[0].Channel[Channel];
      IntChannelOut->DqControl0.Data = DdrCrDataControl0.Data;
      ChannelLatency                 = 2 * Latency[Channel] - 6;
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        //
        // These CRs do a lot of RMW.
        //
        ChannelOut->DataOffsetTrain[Byte]    = 0;    // Faster to store the value in host
        ChannelOut->DataCompOffset[Byte]     = 0;
        IntChannelOut->DqControl1[Byte].Data = DdrCrDataControl1.Data;

        //
        // Stagger byte turnon to reduce dI/dT. In safe mode, turn off stagger feature
        //
        stagger = (SAFE) ? 0 : ((ChannelLatency * ByteStagger[Byte]) / (UINT8) Outputs->SdramCount) & 0x1F;
        Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
        DdrCrDataControl2.Bits.RxStaggerCtl = stagger;
        MrcWriteCR (MrcData, Offset, DdrCrDataControl2.Data);
        IntChannelOut->DqControl2[Byte].Data = DdrCrDataControl2.Data;
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init Data VssHi CRs\n");
  //
  // Initialize VssHi CRs
  //
  // SKL TODO: check if VssHiSwingTarget of 850 mV works
  //
  VssHi = ((UINT16) Vdd - VssHiSwingTarget);   // VssHiSwingTarget = 950 mV, VddmV=1500 mV
  Target = (VssHi * 192) / (UINT16) Vdd - 20;  // Sets target for VssHi.

  //
  // Vsshi threshold is defined in terms of steps size (Vdd/192)
  //
  PanicThreshold = (SAFE) ? 56 : 24;
  PanicThreshold = DIVIDEROUND (PanicThreshold * 192, Vdd);

  Data32 = (SAFE) ?                                           // SAFE: Panic at 7*8=56mV, !SAFE: Panic at 24mV, GainBoost.
    (PanicThreshold << 18) + (2 << 14) + (2 << 8) + (2 << 6) :             // Set BwError and *BWDivider to safe values
    (1 << 22) + (PanicThreshold << 18) + (2 << 14) + (1 << 8) + (1 << 6);  // Normal values for BwError //BWDivider
  Data32 += (1 << 16);                                        // Enable Panic Driver
  Data32 += Target + (0 << 10);                               // Set loop sample frequency at max
  if (SAFE) { // SKL TODO:
    Data32 |= (1 << 17);                                     // SAFE: DisPanicDuringCkePwrDn, only disable Panic during CkePwrDn
  }
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DDRCRVSSHICONTROL_REG, Data32); // Multicast to both channels

  //
  // Set COMP VssHi the same
  //
  DdrCrCompVssHiControl.Data = Data32;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DdrCrCompVsshiControl = 0x%08X\n", DdrCrCompVssHiControl.Data);
  MrcWriteCrMulticast (MrcData, DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_REG, DdrCrCompVssHiControl.Data);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init Dimm Vref CRs\n");
  //
  // Initialize Dimm Vref CRs - Use CH0 BYTE 0
  //
  // Ideal Slope EQN = (192/128*VccIo/Vdd-1)
  //
  Slope = (UINT16) ((1000 * 192 * Inputs->VccIomV) / (128 * (UINT16) Vdd) - 1000);
  Slope = MrcCalcVtSlopeCode (Slope);             // Translate ideal slope in CR value

  //
  // Apply 62mV offset to VtCode
  //
  Offset = (60 * 48) / Vdd;

  //
  // Apply Slope adjustment, Set SlowBWError = 1
  //
  Data32 = (Offset << 18) + (Slope << 12) + (1 << 8);
  //
  // Enable HiBW mode, Set Loop Frequency
  //
  Data32 += (1 << 10) + (1 << 4);
  //
  // Set LoBWDiv, HiBWDiv
  //
  Data32 += (3 << 2) + (0 << 0);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DdrCrVrefControl: 0x%X\n", Data32);
  MrcWriteCR (MrcData, DDRDATA0CH0_CR_DDRCRVREFCONTROL_REG, Data32);

  //
  // Enable all DimmVref and VddHi based on VddVoltage
  //
  DdrCrVrefAdjust.Data               = 0;
  DdrCrVrefAdjust.Bits.EnDimmVrefCA  = 1;
  DdrCrVrefAdjust.Bits.EnDimmVrefCh0 = 1;
  DdrCrVrefAdjust.Bits.EnDimmVrefCh1 = 1;
  DdrCrVrefAdjust.Bits.VccddqHiQnnnH = VddHi;
  DdrCrVrefAdjust.Bits.HiZTimerCtrl  = DDRDATA_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MAX;
  //
  // Enable DimmVref Drivers with Vref = 0
  //
  MrcWriteCrMulticast (MrcData, MrcGetOffsetVrefAdjust1 (MrcData, 0xFF, 0xFF), DdrCrVrefAdjust.Data);
  IntControllerOut->VrefAdjust1.Data = DdrCrVrefAdjust.Data;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      //
      // Initialize Clock CRs
      //
      DdrCrClkControls.Data = 0;
      if (Inputs->CpuFamily == cfKbl) {
        if (DdrFrequency <= 1333) {
          DdrCrClkControls.Bits.RefPi = 7;
        }
      }
      DdrCrClkControls.Bits.DllMask  = 1;                 // Set 2 qclk DLL mask
      DdrCrClkControls.Bits.VccddqHi = VddHi;             // Set Vdd
      if (Lpddr) {
        DdrCrClkControls.Bits.LPDDR_Mode = 1;
      }
      DdrCrClkControls.Bits.ClkGateDisable = SAFE;
      Offset = DDRCLKCH0_CR_DDRCRCLKCONTROLS_REG +
        ((DDRCLKCH1_CR_DDRCRCLKCONTROLS_REG - DDRCLKCH0_CR_DDRCRCLKCONTROLS_REG) * Channel);
      MrcWriteCR (MrcData, Offset, DdrCrClkControls.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCLKCH%u_DdrCrClkControls: 0x%08X\n", Channel, DdrCrClkControls.Data);

      DdrCrCmdControls.Data = DdrCrClkControls.Data;
      DdrCrCtlControls.Data = DdrCrClkControls.Data;

      DdrCrCmdControls.Data &= ~DDRCLKCH0_CR_DDRCRCLKCONTROLS_ClkGateDisable_MSK;
      DdrCrCtlControls.Data &= ~DDRCLKCH0_CR_DDRCRCLKCONTROLS_ClkGateDisable_MSK;
      DdrCrCmdControls.Bits.ClkGateDisable = SAFE;
      DdrCrCtlControls.Bits.ClkGateDisable = SAFE;
      //
      // Initialize CmdN/CmdS CRs
      //
      DdrCrCmdControls.Bits.EarlyWeakDrive  = 3;
      DdrCrCmdControls.Bits.CmdTxEq         = NS & 1; // Enable Early Warning and Cmd DeEmphasis
      MrcWriteCR (MrcData, DDRCMDCH0_CR_DDRCRCMDCONTROLS_REG +
        ((DDRCMDCH1_CR_DDRCRCMDCONTROLS_REG - DDRCMDCH0_CR_DDRCRCMDCONTROLS_REG) * Channel), DdrCrCmdControls.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCMDCH%u_DdrCrCmdControls: 0x%08X\n", Channel, DdrCrCmdControls.Data);
      //
      // Initialize CKE CRs
      //
      DdrCrCkeControls.Data           = DdrCrCmdControls.Data;
      DdrCrCkeControls.Bits.CtlSRDrv  = NS & 2;
      DdrCrCkeControls.Bits.CtlTxEq   = NS & 1; // Enable Weak CKE in SR and Cke DeEmphasis
      MrcWriteCR (
        MrcData,
        DDRCKECH0_CR_DDRCRCTLCONTROLS_REG +
        ((DDRCKECH1_CR_DDRCRCTLCONTROLS_REG - DDRCKECH0_CR_DDRCRCTLCONTROLS_REG) * Channel),
        DdrCrCkeControls.Data
        );
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCKECH%u_DdrCrCtlControls: 0x%08X\n", Channel, DdrCrCkeControls.Data);
      //
      // Initialize CTL CRs
      //
      DdrCrCtlControls.Bits.CtlTxEq  = (NS & 1);  // Enable Weak CKE in SR and Cke DeEmphasis
      DdrCrCtlControls.Bits.CtlSRDrv = (NS & 2);  // Enable Weak CKE in SR and Cke DeEmphasis
      MrcWriteCR (
        MrcData,
        DDRCTLCH0_CR_DDRCRCTLCONTROLS_REG +
        ((DDRCTLCH1_CR_DDRCRCTLCONTROLS_REG - DDRCTLCH0_CR_DDRCRCTLCONTROLS_REG) * Channel),
        DdrCrCtlControls.Data
        );
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCTLCH%u_DdrCrCtlControls: 0x%08X\n", Channel, DdrCrCtlControls.Data);
      //
      // Initialize CRs shared between CKE/CTL/CMD/CLK
      //
      // PI setting must match value written for TxDQs above.
      // There are no shared registers for CLK, only CKE/CTL but only CTLPICODING and CTLCOMPOFFSET
      // Set CTL/CLK PI to 64.
      // Set CMD to 64 for DDR3/4 and to 96 for LPDDR3 (64 + 1/2 QCLK), for ideal initial command centering.
      //
      DdrCrCmdPiCoding.Data            = 0;
      DdrCrCmdPiCoding.Bits.CmdPi0Code =
      DdrCrCmdPiCoding.Bits.CmdPi1Code = (Lpddr) ? 96 : 64;

      Offset = DDRCMDCH0_CR_DDRCRCMDPICODING_REG +
        ((DDRCMDCH1_CR_DDRCRCMDPICODING_REG - DDRCMDCH0_CR_DDRCRCMDPICODING_REG) * Channel);
      MrcWriteCR (MrcData, Offset, DdrCrCmdPiCoding.Data);

      Offset = DDRCKECH0_CR_DDRCRCMDPICODING_REG +
        ((DDRCKECH1_CR_DDRCRCMDPICODING_REG - DDRCKECH0_CR_DDRCRCMDPICODING_REG) * Channel);
      MrcWriteCR (MrcData, Offset, DdrCrCmdPiCoding.Data);

      for (Group = 0; Group < 2; Group++) {
        ChannelOut->CkeCmdPiCode[Group]  = DdrCrCmdPiCoding.Bits.CmdPi0Code;
        ChannelOut->CmdsCmdPiCode[Group] = DdrCrCmdPiCoding.Bits.CmdPi0Code;
        ChannelOut->CmdnCmdPiCode[Group] = DdrCrCmdPiCoding.Bits.CmdPi0Code;
      }

      DdrCrCtlPiCoding.Bits.CtlPiCode0 =
      DdrCrCtlPiCoding.Bits.CtlPiCode1 =
      DdrCrCtlPiCoding.Bits.CtlPiCode2 =
      DdrCrCtlPiCoding.Bits.CtlPiCode3 = 64;

      Offset = DDRCKECTLCH0_CR_DDRCRCTLPICODING_REG +
        ((DDRCKECTLCH1_CR_DDRCRCTLPICODING_REG - DDRCKECTLCH0_CR_DDRCRCTLPICODING_REG) * Channel);
      MrcWriteCR (MrcData, Offset, DdrCrCtlPiCoding.Data);

      Offset = DDRCLKCH0_CR_DDRCRCLKPICODE_REG +
        ((DDRCLKCH1_CR_DDRCRCLKPICODE_REG - DDRCLKCH0_CR_DDRCRCLKPICODE_REG) * Channel);
      MrcWriteCR (MrcData, Offset, DdrCrCtlPiCoding.Data);

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        ChannelOut->CtlPiCode[Rank] = (UINT8) DdrCrCtlPiCoding.Bits.CtlPiCode0;
        ChannelOut->ClkPiCode[Rank] = (UINT8) DdrCrCtlPiCoding.Bits.CtlPiCode0;
      }

      Offset = DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_REG +
        ((DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_REG - DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_REG) * Channel);
      MrcWriteCR (MrcData, Offset, 0x0);     // Zero for now. May offset comp in future

      Offset = DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_REG +
        ((DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_REG - DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_REG) * Channel);
      MrcWriteCR (MrcData, Offset, 0x0);  // Zero for now. May offset comp in future

      DdrCrClkCompOffset.Data = 0;
      if (DtHalo) {
        DdrCrClkCompOffset.Bits.RcompDrvUpOffset   = 7;
        DdrCrClkCompOffset.Bits.RcompDrvDownOffset = 7;
      }
      Offset = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_REG +
        ((DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_REG - DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_REG) * Channel);
      MrcWriteCR (MrcData, Offset, DdrCrClkCompOffset.Data);
    }
  } // End of for Channel...

  //
  // Disable Periodic RComp
  // Set periodic comp = (10uS * 2^COMP_INT)
  //
  CrMCompPcu.Data               = 0;
  CrMCompPcu.Bits.COMP_DISABLE  = 1;
  CrMCompPcu.Bits.COMP_INTERVAL = COMP_INT;  // Set COMP_INT to happen every 10mS
  MrcWriteCR (MrcData, PCU_CR_M_COMP_PCU_REG, CrMCompPcu.Data);

  //
  // Initialize COMP CRs for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
  //

  DdrCrCompCtl1.Data           = 0;
  DdrCrCompCtl1.Bits.VccddqHi  = VddHi;            // Set Vdd, 2 qclk DLL mask
  DdrCrCompCtl1.Bits.CompClkOn = SAFE;             // Override PwrDn in Safe Mode
  DdrCrCompCtl1.Bits.DqRcompStatLegs = 3;          // Should be the same as TxTrainRank.TxEqualization[5:4]
  if (DtHalo) {
    DdrCrCompCtl1.Bits.DqRcompStatLegs = 0;
  }
  DdrCrCompCtl1.Bits.VccddqLo = (Vdd > VDD_1_20) ? 0 : 1;
  IntControllerOut->CompCtl1.Data = DdrCrCompCtl1.Data;

  //
  // Calculate how to program the slew rate targets
  // Buffer Type         DQ  CMD  CTL  CLK
  // Num Stages           3    5    5    3
  // Slew Rate          4.5  3.0  3.0  5.0
  // Derating            .8   .8   .8   .8
  //

  Cmd2N = FALSE;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      if (ControllerOut->Channel[Channel].Timing[Profile].NMode == 2) {
        Cmd2N = TRUE;
        break;
      }
    }
  }
  MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Init Slew Rate\n");

  for (i = 0; i < ARRAY_COUNT (gSlewRateCompParamList); i++) {
    StageDelay = BufferStageDelayPS[i];
    // Special treatment for SCompCmd
    if (gSlewRateCompParamList[i] == SCompCmd) {
      if (Cmd2N == TRUE) {
        StageDelay = 89; // CMD Slew Rate  = 1.8  for 2N
      }
      if (Lpddr) {
        StageDelay = 63; // CMD Slew Rate  = 4 V/ns for double-pumped CMD bus
      }
    }
    UpdateSlewRateCompTargetValue (MrcData, gSlewRateCompParamList[i], StageDelay, TRUE);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CompCtl1 = 0x%x\n", IntControllerOut->CompCtl1.Data);

  //
  // Initialize COMP CRs for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init COMP CRs\n");

  for (i = 0; i < sizeof (CompParamList) / sizeof (CompParamList[0]); i++) {
    UpdateCompTargetValue (MrcData, CompParamList[i], Inputs->RcompTarget[i], 1);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CompCtl0 = 0x%08X\n", IntControllerOut->CompCtl0.Data);
  //
  // Calculate Target Values for VssHi Panic Driver
  //
  // Rtarget = Tperiod / Cdie / ln( VssHi / (VssHi - Delta) )
  //

  DdrCrCompVssHi.Data          = 0;

    //
    //Target Current.  pF * mV / pS -> mA
    // SKL TODO: Divide by 2 here as well ?
    //
    Itarget = CDIEVSSHI * delta / Outputs->Qclkps;
    //
    // Compensated to this current
    //
    PanicCompUpMult = (Itarget * Inputs->RcompResistor[2]) / VssHi;
    PanicCompDnMult = (Itarget * Inputs->RcompResistor[2]) / (Inputs->VccIomV - VssHi);

    DdrCrCompVssHi.Bits.VtOffset = 0x1F;
    DdrCrCompVssHi.Bits.VtSlopeA = 0x4;
    DdrCrCompVssHi.Bits.VtSlopeB = 0x3;  // SKL TODO: DT/Halo uses 0x2
    //
    // Calculate multipler to get target current
    //
    DdrCrCompVssHi.Bits.PanicCompUpMult = MIN (PanicCompUpMult, DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompUpMult_MAX);
    DdrCrCompVssHi.Bits.PanicCompDnMult = MIN (PanicCompDnMult, DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompDnMult_MAX);
    DdrCrCompVssHi.Bits.PanicDrvUpVref  = DdrCrCompVssHiControl.Bits.Target;
  MrcWriteCR (MrcData, DDRCOMP_CR_DDRCRCOMPVSSHI_REG, DdrCrCompVssHi.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DdrCrCompVssHi = 0x%08X\n", DdrCrCompVssHi.Data);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init MISC CRs\n");
  //
  // Initialize MISC CRs
  //

  DdrMiscControl.Data                  = MrcReadCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL0_REG);
  DdrMiscControl.Bits.WeakLock_Latency = 12;
  DdrMiscControl.Bits.WL_SleepCycles   = 5;
  DdrMiscControl.Bits.WL_WakeCycles    = 2;

  DdrMiscControl.Bits.DataClkGateDisAtIdle = 1;

  IntControllerOut->MiscControl0.Data  = DdrMiscControl.Data;
  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL0_REG, DdrMiscControl.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRMISCCONTROL0: 0x%08X\n", DdrMiscControl.Data);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    Offset = DDRSCRAM_CR_DDRSCRAMBLECH0_REG +
      ((DDRSCRAM_CR_DDRSCRAMBLECH1_REG - DDRSCRAM_CR_DDRSCRAMBLECH0_REG) * Channel);
    MrcWriteCR (MrcData, Offset, 0);// Keep scrambling disabled for training
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Update LS COMP CRs\n");

  //
  // Override LevelShifter Compensation to 0x4
  //
  CompDdrCrCompOvr.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRCOMPOVR_REG);
#if (SUPPORT_DDR4 == SUPPORT)
  CompDdrCrCompOvr.Bits.LsComp = (Ddr4 || Lpddr) ? 6 : 3;
#endif // SUPPORT_DDR4
  MrcWriteCR (MrcData, DDRCOMP_CR_DDRCRCOMPOVR_REG, CompDdrCrCompOvr.Data);

    //
    // Use SAFE for DLLPITESTANDADC settings
    //
    DataDllPiTestAndAdc.Data = DllPiTestAndAdc.Data = 0;
    DataDllPiTestAndAdc.Bits.PhaseDrvPwrSavOn = NS;
    DllPiTestAndAdc.Bits.PhaseDrvPwrSavOn = NS;
    MrcWriteCR (MrcData, MrcGetOffsetDllPiTestAndAdc (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM), DataDllPiTestAndAdc.Data);
    MrcWriteCR (MrcData, DDRCKECTL_CR_DLLPITESTANDADC_REG, DllPiTestAndAdc.Data);
    MrcWriteCR (MrcData, DDRCLK_CR_DLLPITESTANDADC_REG, DllPiTestAndAdc.Data);
    MrcWriteCR (MrcData, DDRCMD_CR_DLLPITESTANDADC_REG, DllPiTestAndAdc.Data);

    if (Inputs->EnVttOdt) {
      MrcSetupVtt (MrcData, TRUE);
    }

    //
    // VTT programming
    //
    VttGenControl.Data = 0;

    //
    // Top
    //
    VttGenControl.Bits.Panic = VPANIC3;
    MrcWriteCR (MrcData, DDRDATA6CH1_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
    if (DqPinsInterleaved == FALSE) {
      MrcWriteCR (MrcData, DDRDATA6CH0_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
    } else {
      MrcWriteCR (MrcData, DDRDATA2CH1_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
    }

    //
    // Bottom
    //
    VttGenControl.Bits.Panic = VPANIC2;
    if (DqPinsInterleaved == FALSE) {
      MrcWriteCR (MrcData, DDRDATA2CH1_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
      MrcWriteCR (MrcData, DDRDATA2CH0_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
    } else {
      MrcWriteCR (MrcData, DDRDATA4CH1_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
      MrcWriteCR (MrcData, DDRDATA0CH1_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
    }

    //
    // Middle
    //
    VttGenControl.Bits.Panic = VPANIC1;
    if (DqPinsInterleaved == FALSE) {
      MrcWriteCR (MrcData, DDRDATA3CH1_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
      MrcWriteCR (MrcData, DDRDATA3CH0_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
    } else {
      MrcWriteCR (MrcData, DDRDATA5CH1_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
      MrcWriteCR (MrcData, DDRDATA1CH1_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
    }

    //
    // VSSHI Programming
    //
    VttGenControl.Data                   = 0;
    VssHiCompCtl.Data                    = 0;
    if (Inputs->VttCompForVsshi) {
      VttGenControl.Bits.EnVttCompforVsshi = NS;
      VssHiCompCtl.Bits.EnVttCompforVsshi = NS;
    }
    if (DqPinsInterleaved == FALSE) {
      MrcWriteCR (MrcData, DDRDATA1CH1_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
      MrcWriteCR (MrcData, DDRDATA4CH0_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
    } else {
      MrcWriteCR (MrcData, DDRDATA5CH0_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
      MrcWriteCR (MrcData, DDRDATA2CH0_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);
    }

    MrcWriteCR (MrcData, DDRCLK_CR_DDRVSSHICOMPCTL_REG, VssHiCompCtl.Data);

  //
  // Set the DDR voltage in PCU
  //
  MrcSetPcuDdrVoltage (MrcData, Vdd);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Timing Config\n");
  MrcTimingConfiguration (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Refresh Config\n");
  MrcRefreshConfiguration (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Scheduler parameters\n");
  MrcSchedulerParametersConfig (MrcData);

  //
  // this function must be in the end.
  // if one of the function close channel the function execute this close.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Address Decoding Config\n");
  MrcAdConfiguration (MrcData);

  if (Ddr4) {
    MrcSetOdtMatrix (MrcData, 1);
  }

  //
  // Need to force COMP update after MAD_INTRA_CHx.ECC is programmed
  //
  ForceRcomp (MrcData);

  if (((CpuModel == cmSKL_ULX_ULT) && (CpuStepping <= csSklB0)) ||
      ((CpuModel == cmSKL_DT_HALO) && (CpuStepping == csSklP0))) {
    Offset = MrcGetOffsetDataControl0 (MrcData, 0xFF, 0xFF);
    for (i = 0; i < 254; i++) {
      //
      //
      DdrCrDataControl0.Bits.TxPiOn = 1;
      MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);
      DdrCrDataControl0.Bits.TxPiOn = 0;
      MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);
      DdrCrDataControl0.Bits.RxPiOn = 1;
      MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);
      DdrCrDataControl0.Bits.RxPiOn = 0;
      MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);
      IoReset (MrcData);
    }
  }

  return Status;
}

/**
  This function init all the necessary registers for the training.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcPreTraining (
  IN MrcParameters *const MrcData
  )
{
  MrcIntOutput                          *MrcIntData;
  MrcOutput                             *Outputs;
  MrcInput                              *Inputs;
  MrcControllerOut                      *ControllerOut;
  MrcChannelOut                         *ChannelOut;
  MrcIntChannelOut                      *IntChannelOut;
  UINT32                                Offset;
  UINT8                                 Channel;
  UINT8                                 Rank;
#if (SUPPORT_DDR4 == SUPPORT)
  UINT8                                 TxEqualization;
  UINT8                                 Byte;
#endif // SUPPORT_DDR4
  UINT8                                 RankMod2;
  MrcDdrType                            DdrType;
  BOOLEAN                               UlxUlt;
  MrcDebug                              *Debug;

  MrcIntData    = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  DdrType       = Outputs->DdrType;
  Inputs        = &MrcData->Inputs;
  UlxUlt        = ((Inputs->CpuModel == cmSKL_ULX_ULT) || (Inputs->CpuModel == cmKBL_ULX_ULT));

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }

    //
    // Dump the MR registers for DDR3
    // LPDDR Jedec Init is done after Early Command Training
    //
    if (DdrType != MRC_DDR_TYPE_LPDDR3) {
      ChannelOut    = &ControllerOut->Channel[Channel];
      IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }

        RankMod2 = Rank % 2;
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "MrcSetMR0  Channel %u Rank %u = 0x%X\n",
          Channel,
          Rank,
          ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR0]
          );

        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "MrcSetMR1  Channel %u Rank %u = 0x%X\n",
          Channel,
          Rank,
          ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR1]
          );

        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "MrcSetMR2  Channel %u Rank %u = 0x%X\n",
          Channel,
          Rank,
          ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR2]
          );

        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "MrcSetMR3  Channel %u Rank %u = 0x%X\n",
          Channel,
          Rank,
          ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR3]
          );
#if (SUPPORT_DDR4 == SUPPORT)
        if (DdrType == MRC_DDR_TYPE_DDR4) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "MR4 Channel %u Rank %u = 0x%X\n",
            Channel,
            Rank,
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR4]
            );

          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "MR5 Channel %u Rank %u = 0x%X\n",
            Channel,
            Rank,
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR5]
            );

          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "MR6 Channel %u Rank %u = 0x%X\n",
            Channel,
            Rank,
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR6]
            );

          //Check RttWr if not 0 (not off)
          if (ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR2] & (MRC_BIT10 | MRC_BIT9)) {
            TxEqualization = 0x3F;
            for (Byte = 0; Byte < MAX_SDRAM_IN_DIMM; Byte++) {
              ChannelOut->TxEq[Rank][Byte] = TxEqualization;
              UpdateTxT (MrcData, Channel, Rank, Byte, 2, TxEqualization);
              IntChannelOut->DqControl2[Byte].Bits.EnConstZEqTx = UlxUlt ? 0 : 1;
              Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
              MrcWriteCR (MrcData, Offset, IntChannelOut->DqControl2[Byte].Data);
            }
          }
        }
#endif // SUPPORT_DDR4
      }//Rank

    }//!Lpddr3
  } // for Channel

  //
  // Set up Write data Buffer before training steps
  //
  SetupWDB (MrcData);

  return mrcSuccess;
}

/**
  This function initializes all the necessary registers after main training steps but before LCT.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess

**/
MrcStatus
MrcPostTraining (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  UINT8             Channel;

  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      //
      // Update CmdN timing, Round Trip Latency and tXP
      // OldN=3, NewN=2*Cmd2N
      //
      UpdateCmdNTiming (
        MrcData,
        Channel,
        2 * 2,
        (ControllerOut->Channel[Channel].Timing[MrcData->Inputs.MemoryProfile].NMode == 2) ? 2 : 0
      );
    }
  }

  return mrcSuccess;
}

/**
  Program PCU_CR_DDR_VOLTAGE register.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] VddVoltage - Current DDR voltage.

**/
void
MrcSetPcuDdrVoltage (
  IN OUT MrcParameters *MrcData,
  IN     MrcVddSelect  VddVoltage
  )
{
  MrcInput                      *Inputs;
  MrcOutput                     *Outputs;
  MrcDebug                      *Debug;
  UINT8                         Data8;
  PCU_CR_DDR_VOLTAGE_PCU_STRUCT DdrVoltage;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  switch (VddVoltage) {
    case VDD_1_35:
      Data8 = 1;
      break;

    case VDD_1_20:
      Data8 = 3;  // @todo For single CA bus set this to 2
#if (SUPPORT_DDR4 == SUPPORT)
      if (Outputs->DdrType == MRC_DDR_TYPE_DDR4) {
        Data8 = 7;
      }
#endif // SUPPORT_DDR4
      break;

    default:
      Data8 = 0;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PCU_CR_DDR_VOLTAGE = 0x%02X\n", Data8);
  DdrVoltage.Data = 0;
  DdrVoltage.Bits.DDR_VOLTAGE = Data8;
  MrcWriteCR (MrcData, PCU_CR_DDR_VOLTAGE_PCU_REG, DdrVoltage.Data);
}

/**
  This function sets up the Vtt termination.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] DebugMsg - Whether to display debug messages

**/
void
MrcSetupVtt (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              DebugMsg
  )
{
  const MrcInput                                *Inputs;
  MrcDebug                                      *Debug;
  MrcIntOutput                                  *MrcIntData;
  MrcOutput                                     *Outputs;
  MrcVddSelect                                  Vdd;
  MrcChannelOut                                 *ChannelOut;
  MrcIntControllerOut                           *IntControllerOut;
  MrcControllerOut                              *ControllerOut;
  MrcProfile                                    Profile;
  MrcCpuStepping                                CpuStepping;
  UINT8                                         Channel;
  UINT16                                        RodtCpu;
  UINT8                                         Rank;
  UINT8                                         TotalDimms;
  UINT32                                        Itarget;
  UINT32                                        Idelta;
  UINT32                                        Vpanic2;
  UINT32                                        Vpanic3;
  UINT32                                        Iload;
  UINT32                                        IcompUp;
  UINT32                                        IcompDn;
  UINT32                                        RonDimm;
  UINT32                                        TotalRon;
  UINT32                                        NumberOfSegments;
  UINT32                                        CmdTarget;
  UINT32                                        Vtt;
  UINT8                                         DebugLevel;
  DDRCOMP_CR_DDRCRCOMPCTL2_STRUCT               DdrCrCompCtl2;
#ifdef MRC_DEBUG_PRINT
  DDRCOMP_CR_DDRCRDATACOMP2_STRUCT              DdrCrDataComp2;
#endif //MRC_DEBUG_PRINT

  MrcIntData        = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  ControllerOut     = &Outputs->Controller[0];
  IntControllerOut  = &MrcIntData->Controller[0];
  Profile           = Inputs->MemoryProfile;
  CpuStepping       = Inputs->CpuStepping;
  TotalRon          = 0;
  TotalDimms        = 0;
  Vdd               = Outputs->VddVoltage[Inputs->MemoryProfile];

  DebugLevel = (DebugMsg) ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;

  //
  // Target Vtt Voltage
  //
  Vtt = Vdd / 2;
  //
  // Calculate RodtCPU
  //
  // @todo: in power training this might vary between different bytes so need to avg
  RodtCpu = CalcCpuImpedance (MrcData, 0, 0, 0, OptRdOdt, FALSE, 0, FALSE,  0, 0);
  //
  // Calculate RonDimm Per Dimm (assuming)
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += 2) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        TotalDimms++;
        TotalRon += CalcDimmImpedance(MrcData, Channel, Rank, OptDimmRon, TRUE, 0);
      } // Rank exist
    } // Channel exist
  } // Channel

  if (TotalDimms == 0) {
    TotalDimms++;
  }
  RonDimm = TotalRon / TotalDimms;

  //
  // Delta Current.  pF * mV / pS -> mA
  // iload = vdd/(2*(rodt+ron))*64
  Vpanic2 = VPANIC2;
  Vpanic3 = VPANIC3;
  if ((RodtCpu == 0) && (RonDimm == 0)) {
    RonDimm++;
  }
  Iload = Vdd * 64 * 1000 / (2 * (RodtCpu + RonDimm));  // uA
  Idelta = (CDIEVTT * (Vpanic3 - Vpanic2) * Vdd / ((Outputs->Qclkps) * 192 )) * 1000; // uA
  Itarget = (Iload + Idelta) / 32; //uA

  MRC_DEBUG_MSG (Debug, DebugLevel, "MrcSetupVtt: RodtCpu=%u ohm, RonDimm=%u ohm\n", RodtCpu, RonDimm);
  MRC_DEBUG_MSG (Debug, DebugLevel, "Itarget=%u uA, Iload=%u uA, Idelta=%u uA\n", Itarget, Iload, Idelta);

  // CmdDrv has 5 segments in SKL/KBL
  NumberOfSegments = 5;
  CmdTarget = NumberOfSegments * Inputs->RcompTarget[WrDSCmd];
  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3) {
    CmdTarget = RCMDREF_VTT_UP;
  }
  //
  // Compensated to this current
  //
  IcompDn = 1000 * (Inputs->VccIomV - Vtt) / CmdTarget; // uA
  IcompUp = 1000 * Vtt / (2 * CmdTarget); // uA
  if (IcompDn == 0) {
    IcompDn++;
  }
  if (IcompUp == 0) {
    IcompUp++;
  }
  MRC_DEBUG_MSG (Debug, DebugLevel, "IcompDn=%u uA, IcompUp=%u uA\n", IcompDn, IcompUp);
  //
  // Calculate multipler to get target current
  //
  DdrCrCompCtl2.Data = IntControllerOut->CompCtl2.Data;
  DdrCrCompCtl2.Bits.VttPanicCompUpMult = MIN (2 * (Itarget / IcompUp), DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompUpMult_MAX);
  DdrCrCompCtl2.Bits.VttPanicCompDnMult = MIN (2 * (Itarget / IcompDn), DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompDnMult_MAX);
  IntControllerOut->CompCtl2.Data = DdrCrCompCtl2.Data;
  MrcWriteCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL2_REG, DdrCrCompCtl2.Data);

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, DebugLevel, "write VttPanicCompUpMult = 0x%X\n", DdrCrCompCtl2.Bits.VttPanicCompUpMult);
  MRC_DEBUG_MSG (Debug, DebugLevel, "write VttPanicCompDnMult = 0x%X\n", DdrCrCompCtl2.Bits.VttPanicCompDnMult);

  DdrCrCompCtl2.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRCOMPCTL2_REG);
  MRC_DEBUG_MSG (Debug, DebugLevel, "read VttPanicCompUpMult = 0x%X\n", DdrCrCompCtl2.Bits.VttPanicCompUpMult);
  MRC_DEBUG_MSG (Debug, DebugLevel, "read VttPanicCompDnMult = 0x%X\n", DdrCrCompCtl2.Bits.VttPanicCompDnMult);
#endif //MRC_DEBUG_PRINT

  ForceRcomp (MrcData);

#ifdef MRC_DEBUG_PRINT
  DdrCrDataComp2.Data = MrcReadCR (MrcData, DDRCOMP_CR_DDRCRDATACOMP2_REG);
  MRC_DEBUG_MSG (Debug, DebugLevel, "final panicvttup = 0x%X\n", DdrCrDataComp2.Bits.PanicVttUp);
  MRC_DEBUG_MSG (Debug, DebugLevel, "final panicvttdn = 0x%X\n", DdrCrDataComp2.Bits.PanicVttDn);
#endif //MRC_DEBUG_PRINT
}

