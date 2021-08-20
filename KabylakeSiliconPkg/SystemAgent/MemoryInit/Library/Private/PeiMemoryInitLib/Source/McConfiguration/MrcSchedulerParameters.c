/** @file
  This module configures the memory controller scheduler.

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
#include "MrcSchedulerParameters.h"

/**
  This function configures the memory controller scheduler.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
MrcSchedulerParametersConfig (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput                        *Inputs;
  MrcOutput                             *Outputs;
  MrcDebug                              *Debug;
  MrcIntOutput                          *MrcIntData;
  MrcChannelOut                         *ChannelOut;
  MrcDimmOut                            *DimmOut;
  MrcDdrType                            DdrType;
  MCDECS_CR_MCDECS_CBIT_MCMAIN_STRUCT   McdecsCbit;
  MCDECS_CR_MCDECS_MISC_MCMAIN_STRUCT   McdecsMisc;
  MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_STRUCT  McGlobalDriverGateCfg;
  MCSCHEDS_CR_SCHED_CBIT_STRUCT         SchedCbit;
  MCSCHEDS_CR_SCHED_SECOND_CBIT_STRUCT  SchedSecondCbit;
  MCSCHEDS_CR_SC_GS_CFG_STRUCT          ScGsCfg;
  MCSCHEDS_CR_SC_WDBWM_STRUCT           ScWdbWm;
  MCDECS_CR_SC_QOS_MCMAIN_STRUCT        ScQos;
  MCSCHEDS_CR_SC_PCIT_STRUCT            ScPcit;
  UINT8                                 Channel;
  UINT8                                 Dimm;
  UINT8                                 BankCount;
  UINT8                                 MinBanks;
  UINT32                                Offset;
  UINT32                                tCPDED;
  UINT64                                BankMapping;


  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  DdrType = Outputs->DdrType;

  McdecsCbit.Data = MrcReadCR (MrcData, MCDECS_CR_MCDECS_CBIT_MCMAIN_REG);
  McdecsCbit.Bits.dis_single_ch_sr        = 0;
  McdecsCbit.Bits.dis_other_ch_stolen_ref = 0;
  MrcWriteCR (MrcData, MCDECS_CR_MCDECS_CBIT_MCMAIN_REG, McdecsCbit.Data);

  McdecsMisc.Data = MrcReadCR (MrcData, MCDECS_CR_MCDECS_MISC_MCMAIN_REG);
  McdecsMisc.Bits.Spare_RW &= (UINT16) ~(0x1F);
  McdecsMisc.Bits.Spare_RW |= 0x13;
  MrcWriteCR (MrcData, MCDECS_CR_MCDECS_MISC_MCMAIN_REG, McdecsMisc.Data);

  McGlobalDriverGateCfg.Data = MrcReadCR (MrcData, MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_REG);
  McGlobalDriverGateCfg.Bits.MNT_GLB_DRV_GATE_DIS   = 1;
  McGlobalDriverGateCfg.Bits.MAINS_GLB_DRV_GATE_DIS = 1;
  MrcWriteCR (MrcData, MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_REG, McGlobalDriverGateCfg.Data);

  SchedCbit.Data = 0;
  MinBanks = 16;

  if ((Inputs->CpuModel == cmSKL_ULX_ULT) && (Inputs->CpuStepping <= csSklB0)) {
    SchedCbit.Bits.dis_2c_byp = 1;
  }

  SchedCbit.Bits.dis_odt = 1; // TODO: Input parameter for ODT Disable should depend on board type ?
  if (DdrType == MRC_DDR_TYPE_LPDDR3) {
    //
    // LPDDR3 DDP and QDP (multi-die) packages share the same ZQ pin,
    // so we need to serialize the ZQ calibration for different ranks.
    //
    SchedCbit.Bits.serialize_zq = 1;

    if (Outputs->LpddrDramOdt) {
      //
      // DRAM ODT is used
      //
      SchedCbit.Bits.dis_odt = 0;
    }
  }
  if (DdrType == MRC_DDR_TYPE_DDR3) {
    if (Inputs->Ddr3DramOdt) {
      SchedCbit.Bits.dis_odt = 0;
    }
  }
  if (DdrType == MRC_DDR_TYPE_DDR4) {
    if (Inputs->Ddr4DdpSharedZq) {
      SchedCbit.Bits.serialize_zq = 1;  // ZQ Pin can be shared on DDR4 DDP parts
    }
    if (Inputs->Ddr4DramOdt) {
      SchedCbit.Bits.dis_odt = 0;
    }
  }

  MrcWriteCrMulticast (MrcData, MCSCHEDS_CR_SCHED_CBIT_REG, SchedCbit.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SCHED_CBIT = %08Xh\n", SchedCbit.Data);

  //
  //
  ScWdbWm.Data = 0;
  ScWdbWm.Bits.WMM_entry_wm     = 0x38;
  ScWdbWm.Bits.WMM_exit_wm      = 0x28;
  ScWdbWm.Bits.WIM_wm           = 0x3F;
  ScWdbWm.Bits.EDRAM_scrub_wm   = 0x38;
  ScWdbWm.Bits.Read_CAS_count   = 0x10;
  ScWdbWm.Bits.Write_CAS_count  = 0x10;
  ScWdbWm.Bits.Write_CAS_count_for_VC1  = 0x40;
  MrcWriteCR64 (MrcData, MCSCHEDS_CR_SC_WDBWM_REG, ScWdbWm.Data);

  ScQos.Data = 0;
  ScQos.Bits.Isoch_time_window            = 0x1C2;
  ScQos.Bits.Write_starvation_window      = 0x5A;
  ScQos.Bits.Read_starvation_windowLow    = 0x0A;
  ScQos.Bits.Read_starvation_windowHigh   = 0x05;
  ScQos.Bits.VC0_read_count               = 0x16;
  ScQos.Bits.VC1_Read_starvation_en       = 1;
  ScQos.Bits.Write_starvation_in_Isoc_en  = 1;
  ScQos.Bits.Read_starvation_in_Isoch_en  = 1;

  ScQos.Bits.VC0_counter_disable          = 1;

  ScQos.Bits.Force_MCVC1Demote            = 0;
  ScQos.Bits.MC_Ignore_VC1Demote          = 0;
  MrcWriteCR64 (MrcData, MCDECS_CR_SC_QOS_MCMAIN_REG, ScQos.Data);

  SchedSecondCbit.Data = 0;
  SchedSecondCbit.Bits.dis_burst_ref_limit = 1;
  MrcWriteCrMulticast (MrcData, MCSCHEDS_CR_SCHED_SECOND_CBIT_REG, SchedSecondCbit.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SCHED_SECOND_CBIT = %08Xh\n", SchedSecondCbit.Data);
  ///
  ///
  ScPcit.Data = 0;
  ScPcit.Bits.PCIT = 0x40;
  ScPcit.Bits.PCIT_GT = 0x60;
  MrcWriteCrMulticast (MrcData, MCSCHEDS_CR_SC_PCIT_REG, ScPcit.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SC_PCIT = %08Xh\n", ScPcit.Data);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    ScGsCfg.Data = 0;
    //
    // Set the N mode and Command Rate Limit
    //
    ScGsCfg.Bits.N_to_1_ratio = 3;    // This was called Command Rate Limit before
    if (DdrType == MRC_DDR_TYPE_LPDDR3) {
      ScGsCfg.Bits.CMD_stretch = 3;     // N:1 Mode for LPDDR3
    } else {
      ScGsCfg.Bits.CMD_stretch = 2;     // 3N Mode for DDR3/4
    }

    ScGsCfg.Bits.DRAM_technology = DdrType;  // Matches MRC_DDR_TYPE_xxx encoding

    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      if (MrcRankInChannelExist (MrcData, Dimm * MAX_RANK_IN_DIMM, Channel)) {
        DimmOut = &ChannelOut->Dimm[Dimm];
        if (DimmOut->AddressMirrored) {
          ScGsCfg.Bits.Address_mirror |= (1 << Dimm);
        }
        if (DimmOut->SdramWidth == 8) {
          ScGsCfg.Bits.x8_device |= (1 << Dimm);
        }
        //
        // Find the minimum number of banks on all the DIMMs in this channel
        //
        BankCount = DimmOut->BankGroups * DimmOut->Banks;
        MinBanks = MIN (MinBanks, BankCount);
      }
    }

    switch (DdrType) {
      case MRC_DDR_TYPE_LPDDR3:
        tCPDED = 2;
        break;

      case MRC_DDR_TYPE_DDR4:
        tCPDED = 4;
        break;

      case MRC_DDR_TYPE_DDR3:
      default:
        if (Outputs->Frequency >= f1867) {
          tCPDED = 2;
        } else {
          tCPDED = 1;
        }
    }
    ScGsCfg.Bits.tCPDED = tCPDED;

    //
    // Disable command tri state before training.
    //
    ScGsCfg.Bits.cmd_3st = 1;

    ScGsCfg.Bits.ck_to_cke = 4;

    if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint == MrcSaGvPointLow)) {
      ScGsCfg.Bits.ddr_probeless_low_frequency = 1;
    }

    Offset = MCHBAR_CH0_CR_SC_GS_CFG_REG + ((MCHBAR_CH1_CR_SC_GS_CFG_REG - MCHBAR_CH0_CR_SC_GS_CFG_REG) * Channel);
    MrcWriteCR (MrcData, Offset, ScGsCfg.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u: SC_GS_CFG = %08Xh\n", Channel, ScGsCfg.Data);


    if (DdrType == MRC_DDR_TYPE_DDR4) {
      //
      // Setup Bank Logical to Physical mapping, according to the minimum number of banks on a channel
      //
      // 16 banks case (x8):
      // Logical Bank:         0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
      //                       -----------------------------------------------
      // Physical Bank:        0  1  2  3  0  1  2  3  0  1  2  3  0  1  2  3
      // Physical Bank Group:  0  0  0  0  1  1  1  1  2  2  2  2  3  3  3  3
      //
      // 8 banks case (x16):
      // Logical Bank:         0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
      //                       -----------------------------------------------
      // Physical Bank:        0  1  2  3  0  1  2  3  0  1  2  3  0  1  2  3
      // Physical Bank Group:  0  0  0  0  1  1  1  1  0  0  0  0  1  1  1  1

      BankMapping = (MinBanks == 16) ? 0xFEDCBA9876543210ULL : 0x7654321076543210ULL;

      Offset = MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG +
        (MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG) * Channel;
      MrcWriteCR64 (MrcData, Offset, BankMapping);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u: BANK_LOGICAL_TO_PHYSICAL_MAPPING = %lXh\n", Channel, BankMapping);
    }
  } // for Channel

  return;
}

