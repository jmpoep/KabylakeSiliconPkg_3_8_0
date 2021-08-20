/** @file
  This module configures the memory controller address decoder.

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
#include "MrcAddressDecodeConfiguration.h"

#if (MAX_CHANNEL > 2)
#error This module only supports a maximum of 2 channels.
#endif
#if (MAX_DIMMS_IN_CHANNEL > 2)
#error This module only supports a maximum of 2 DIMMs per channel.
#endif

/**
  This function configures the zone configuration registers MAD-CR and MAD-ZR-CR.

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
ZoneConfiguration (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput                              *Inputs;
  MrcOutput                             *Outputs;
  MrcDebug                              *Debug;
  const MRC_FUNCTION                    *MrcCall;
  MrcControllerOut                      *ControllerOut;
  MrcChannelOut                         *ChannelOut;
  MrcChannelOut                         *ChannelOut0;
  MrcChannelOut                         *ChannelOut1;
  UINT32                                ChannelSizeMin;
  UINT32                                ChannelSize[MAX_CHANNEL];
  UINT8                                 Channel;
  UINT8                                 Dimm;
  MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STRUCT           MadInterCh;
  MCDECS_CR_CHANNEL_HASH_MCMAIN_STRUCT                ChannelHash;

  MadInterCh.Data   = 0;
  ChannelHash.Data  = 0;
  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  MrcCall           = Inputs->Call.Func;
  Debug             = &Outputs->Debug;
  ControllerOut     = &Outputs->Controller[0];

  //
  // Add up the amount of memory in each channel.
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut            = &ControllerOut->Channel[Channel];
    ChannelSize[Channel]  = 0;
    if (ChannelOut->Status == CHANNEL_PRESENT) {
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        if (ChannelOut->Dimm[Dimm].Status == DIMM_PRESENT) {
          ChannelSize[Channel] += ChannelOut->Dimm[Dimm].DimmCapacity;
        }
      }
    }
  }

  ChannelOut0 = &ControllerOut->Channel[cCHANNEL0];
  ChannelOut1 = &ControllerOut->Channel[cCHANNEL1];
  if (ChannelSize[cCHANNEL1] <= ChannelSize[cCHANNEL0]) {
    MadInterCh.Bits.CH_L_MAP = 0;
    //
    // Set the virtual channel type according to the address decoding decision.
    //
    ChannelOut0->VirtualChannel = vcL;
    ChannelOut1->VirtualChannel = vcS;

    ChannelSizeMin              = ChannelSize[cCHANNEL1];
  } else {
    //
    //  ChannelSize0 < ChannelSize1
    //
    MadInterCh.Bits.CH_L_MAP = 1;

    //
    // Set the virtual channel type according to the address decoding decision.
    //
    ChannelOut0->VirtualChannel = vcS;
    ChannelOut1->VirtualChannel = vcL;

    ChannelSizeMin              = ChannelSize[cCHANNEL0];
  }

  MadInterCh.Bits.CH_S_SIZE = ChannelSizeMin / 1024;  // In 1GB units

  MadInterCh.Bits.DDR_TYPE = Outputs->DdrType;        // Matches MRC_DDR_TYPE_xxx encoding

  //
  // Interleaved mode
  // Check for any Channel hash support
  //
  if (Inputs->ChHashEnable) {
    ChannelHash.Bits.HASH_MASK         = MIN (Inputs->ChHashMask, MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MASK_MAX);
    ChannelHash.Bits.HASH_LSB_MASK_BIT = MIN (Inputs->ChHashInterleaveBit, MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_LSB_MASK_BIT_MAX);
    ChannelHash.Bits.HASH_MODE         = 1;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel HASH Enabled\n");
  }

  if (Inputs->MemoryTrace) {
    if (ChannelSize[cCHANNEL0] == ChannelSize[cCHANNEL1]) {
      //
      // Enable the Stacked Mode for memory tracing
      //
      MadInterCh.Bits.STKD_MODE = 1;
      MadInterCh.Bits.STKD_MODE_CH1 = 0;
      MadInterCh.Bits.STKD_MODE_CH_BITS = MrcLog2 (ChannelSizeMin) - 11; // Need to subtract 10 but MrcLog2 is giving log value plus 1
      ChannelHash.Bits.HASH_MODE = 1;
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "Enabling Stacked Mode for Memory Trace, Stacked Mode Ch bit = %u (%u MB per channel)\n",
        MadInterCh.Bits.STKD_MODE_CH_BITS + 30,
        ChannelSizeMin
        );
    } else {
      Inputs->MemoryTrace = 0;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Channels are not equal in size, cannot enable Memory Trace !\n");
    }
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "CHANNEL_HASH = 0x%08X\nMAD_INTER_CHANNEL = 0x%08X\n",
    ChannelHash.Data,
    MadInterCh.Data
    );
  MrcWriteCR (MrcData, MCDECS_CR_CHANNEL_HASH_MCMAIN_REG, ChannelHash.Data);
  MrcWriteCR (MrcData, MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_REG, MadInterCh.Data);
}

/**
  This function configures the MAD_DIMM_CH0/1 register.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] ChannelIndex - Channel index

  @retval Nothing.
**/
void
ChannelAddressDecodeConfiguration (
  IN MrcParameters *const MrcData,
  IN const UINT32         ChannelIndex
  )
{
  const MrcInput                        *Inputs;
  MrcOutput                             *Outputs;
  MrcChannelOut                         *ChannelOut;
  MrcDimmOut                            *DimmL;
  MrcDimmOut                            *DimmS;
  MCDECS_CR_MAD_DIMM_CH0_MCMAIN_STRUCT  MadDimm;
  MCDECS_CR_MAD_INTRA_CH0_MCMAIN_STRUCT MadIntraCh;
  UINT32                                DimmCapacity;
  UINT32                                Dimm0Capacity;
  UINT32                                Dimm1Capacity;
  UINT32                                Scratch;
  UINT32                                Offset;
  MCHBAR_CH0_CR_DDR_MR_PARAMS_STRUCT    DdrMrParams;
  MrcDdrType                            DdrType;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ChannelOut    = &Outputs->Controller[0].Channel[ChannelIndex];
  MadDimm.Data      = 0;
  MadIntraCh.Data   = 0;
  DdrMrParams.Data  = 0;
  DdrType = Outputs->DdrType;

  if (ChannelOut->Dimm[dDIMM0].Status == DIMM_PRESENT) {
    Dimm0Capacity = ChannelOut->Dimm[dDIMM0].DimmCapacity;
  } else {
    Dimm0Capacity = 0;
  }

  if (ChannelOut->Dimm[dDIMM1].Status == DIMM_PRESENT) {
    Dimm1Capacity = (MAX_DIMMS_IN_CHANNEL > 1) ? ChannelOut->Dimm[dDIMM1].DimmCapacity : 0;
  } else {
    Dimm1Capacity = 0;
  }

  //
  // larger dimm will be located to Dimm L and small dimm will be located to dimm S
  //
  if (Dimm1Capacity <= Dimm0Capacity) {
    DimmL = &ChannelOut->Dimm[dDIMM0];
    DimmS = &ChannelOut->Dimm[dDIMM1];
    //
    // larger DIMM in capacity 0 - DIMM 0 or 1 - DIMM 1
    //
    MadIntraCh.Bits.DIMM_L_MAP = 0;
  } else {
    DimmL = &ChannelOut->Dimm[dDIMM1];
    DimmS = &ChannelOut->Dimm[dDIMM0];
    //
    // larger DIMM in capacity 0 - DIMM 0 or 1 - DIMM 1
    //
    MadIntraCh.Bits.DIMM_L_MAP = 1;
  }
  //
  // Dimm L
  //
  if ((0 < DimmL->RankInDimm) && (DimmL->Status == DIMM_PRESENT)) {
    DimmCapacity              = DimmL->DimmCapacity / 1024;
    MadDimm.Bits.DIMM_L_SIZE  = MIN (DimmCapacity, MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_L_SIZE_MAX);
    //
    // RankInDimm must be 1 or 2, we test the case that the value is 0
    //
    Scratch             = DimmL->RankInDimm - 1;
    MadDimm.Bits.DLNOR  = MIN (Scratch, MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLNOR_MAX);
    //
    // SDRAM width
    //
    switch (DimmL->SdramWidth) {
      case 8:
        MadDimm.Bits.DLW = 0;
        break;

      case 16:
        MadDimm.Bits.DLW = 1;
        break;

      case 32:
      case 64:
        MadDimm.Bits.DLW = 2;
        break;
    }
    //
    // DDR3 8Gb case
    //
    if ((DimmL->DensityIndex == 5) && (DdrType == MRC_DDR_TYPE_DDR3)) {
      MadDimm.Bits.DL8Gb = 1;
    }
  }
  //
  // Dimm S
  //
  if ((MAX_DIMMS_IN_CHANNEL > 1) && (0 < DimmS->RankInDimm) && (DimmS->Status == DIMM_PRESENT)) {
    DimmCapacity              = DimmS->DimmCapacity / 1024;
    MadDimm.Bits.DIMM_S_SIZE  = MIN (DimmCapacity, MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_S_SIZE_MAX);
    //
    // RankInDimm must be 1 or 2, we test the case that this value is 0.
    //
    Scratch             = DimmS->RankInDimm - 1;
    MadDimm.Bits.DSNOR  = MIN (Scratch, MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSNOR_MAX);
    //
    // SDRAM width
    //
    switch (DimmS->SdramWidth) {
      case 8:
        MadDimm.Bits.DSW = 0;
        break;

      case 16:
        MadDimm.Bits.DSW = 1;
        break;

      case 32:
      case 64:
        MadDimm.Bits.DSW = 2;
        break;
    }
    //
    // DDR3 8Gb case
    //
    if ((DimmS->DensityIndex == 5) && (DdrType == MRC_DDR_TYPE_DDR3)) {
      MadDimm.Bits.DS8Gb = 1;
    }
  }

  //
  // TODO: if only 1DPC is supported, should we make DSW == DLW ?
  //
  //MadDimm.Bits.DSW = MadDimm.Bits.DLW;

  if (Inputs->RankInterleave) {
    MadIntraCh.Bits.RI = MRC_DIMM_RANK_INTERLEAVE;
  }
  if (Inputs->EnhancedInterleave) {
    MadIntraCh.Bits.EIM = MRC_ENHANCED_INTERLEAVE_MODE;
  }

  if (Outputs->EccSupport) {
    //
    // Set to '01' - ECC is active in IO, ECC logic is not active.
    //
    MadIntraCh.Bits.ECC = emEccIoActive;

    //
    // Wait 4 usec after enabling the ECC IO, needed by HW
    //
    MrcWait (MrcData, 4 * HPET_1US);
  }

  MRC_DEBUG_MSG (
    &Outputs->Debug,
    MSG_LEVEL_NOTE,
    "MAD_DIMM_CH%u = 0x%08X\nMAD_INTRA_CH%u = 0x%08X\n",
    ChannelIndex,
    MadDimm.Data,
    ChannelIndex,
    MadIntraCh.Data
    );

  Offset = MCDECS_CR_MAD_DIMM_CH0_MCMAIN_REG +
    (MCDECS_CR_MAD_DIMM_CH1_MCMAIN_REG - MCDECS_CR_MAD_DIMM_CH0_MCMAIN_REG) * ChannelIndex;
  MrcWriteCR (MrcData, Offset, MadDimm.Data);

  Offset = MCDECS_CR_MAD_INTRA_CH0_MCMAIN_REG +
    (MCDECS_CR_MAD_INTRA_CH1_MCMAIN_REG - MCDECS_CR_MAD_INTRA_CH0_MCMAIN_REG) * ChannelIndex;
  MrcWriteCR (MrcData, Offset, MadIntraCh.Data);

  if (DdrType != MRC_DDR_TYPE_DDR3) {
    DdrMrParams.Bits.MR4_PERIOD = 0x200D;  // TODO: Confirm value for LPDDR3 and DDR4

    if (DdrType == MRC_DDR_TYPE_DDR4) {
      DdrMrParams.Bits.DDR4_TS_readout_en = 1;
    }

    if (MadIntraCh.Bits.DIMM_L_MAP == 0) {
      DdrMrParams.Bits.Rank_0_width = MadDimm.Bits.DLW;
      DdrMrParams.Bits.Rank_1_width = MadDimm.Bits.DLW;
      DdrMrParams.Bits.Rank_2_width = MadDimm.Bits.DSW;
      DdrMrParams.Bits.Rank_3_width = MadDimm.Bits.DSW;
    } else {
      DdrMrParams.Bits.Rank_0_width = MadDimm.Bits.DSW;
      DdrMrParams.Bits.Rank_1_width = MadDimm.Bits.DSW;
      DdrMrParams.Bits.Rank_2_width = MadDimm.Bits.DLW;
      DdrMrParams.Bits.Rank_3_width = MadDimm.Bits.DLW;
    }
    Offset = MCHBAR_CH0_CR_DDR_MR_PARAMS_REG +
      (MCHBAR_CH1_CR_DDR_MR_PARAMS_REG - MCHBAR_CH0_CR_DDR_MR_PARAMS_REG) * ChannelIndex;
    MrcWriteCR (MrcData, Offset, DdrMrParams.Data);
  }
  return;
}

/**
  This function is the main address decoding configuration function.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
MrcAdConfiguration (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcControllerOut  *ControllerOut;
  MrcDimmOut        *DimmOut;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             Dimm;

  ZoneConfiguration (MrcData);

  Outputs = &MrcData->Outputs;
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];

      ChannelAddressDecodeConfiguration (MrcData, Channel);

      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; ++Dimm) {
        DimmOut = &ChannelOut->Dimm[Dimm];
        if (DimmOut->Status == DIMM_PRESENT) {
          MRC_DEBUG_MSG (
            &Outputs->Debug,
            MSG_LEVEL_NOTE,
            "Channel: %u, Dimm %d Rank in DIMM is: %u\n",
            Channel,
            Dimm,
            DimmOut->RankInDimm
            );
        }
      } // for Dimm
    } // for Channel
  } // for Controller

  return;
}

