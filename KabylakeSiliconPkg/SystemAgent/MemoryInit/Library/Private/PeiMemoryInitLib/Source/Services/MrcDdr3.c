/** @file
  This file includes all the DDR3 specific characteristic functions.

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
#include "MrcDdr3.h"
#include "MrcRefreshConfiguration.h"
#include "MrcPowerModes.h"
#include "MrcMemoryScrub.h"

//
// ODT values are in this order: { RttWr, RttNom }
// Only 1DPC is supported on ULT/ULX
//
GLOBAL_REMOVE_IF_UNREFERENCED const TOdtValue MbUltOdtTable[MAX_DIMMS_IN_CHANNEL][2] = {
// 1DPC 1R,  1DPC 2R
  {{120,0},  {120,0}},
};

GLOBAL_REMOVE_IF_UNREFERENCED const TOdtValue User1UltOdtTable[MAX_DIMMS_IN_CHANNEL][2] = {
/// 1DPC 1R,  1DPC 2R
  {{120,0},  {120,0}},
};


#if (SUPPORT_DDR4 == SUPPORT)
//
// ODT values are in this order: { RttWr, RttNom, RttPark }
//
// SKL-Y/U is 1DPC
//
GLOBAL_REMOVE_IF_UNREFERENCED const TOdtValueDdr4 MbDdr4OdtTable[MAX_DIMMS_IN_CHANNEL][2] = {
/// 1DPC 1R,    1DPC 2R
  {{120,0,0},  {120,0,0}},
};

GLOBAL_REMOVE_IF_UNREFERENCED const TOdtValueDdr4 DtDdr4OdtTable[MAX_DIMMS_IN_CHANNEL][oiNotValid] = {
/// 1DPC 1R,     1DPC 2R,     2DPC 1R 1R,    2DPC 1R 2R,      2DPC 2R 1R,      2DPC 2R 2R
  {{80,0,240},  {80,0,240},  {240,48,0},    {240,40,240},    {240,48,120},    {240,60,120}}, // DIMM 0
  {{80,0,240},  {80,0,240},  {240,48,0},    {240,48,240},    {240,40,120},    {240,60,120}}  // DIMM 1
};

GLOBAL_REMOVE_IF_UNREFERENCED const TOdtValueDdr4 DtDdr4OdtTable2667[MAX_DIMMS_IN_CHANNEL] = {
// Used in 2DPC 1R 1R Configuration for 2667 and above frequencies.
  {80,40,40}, // DIMM 0
  {80,40,40}  // DIMM 1
};

GLOBAL_REMOVE_IF_UNREFERENCED const TOdtValueDdr4 User1Ddr4OdtTable[MAX_DIMMS_IN_CHANNEL][2] = {
/// 1DPC 1R,  1DPC 2R
  {{80,0,240},  {80,0,240}},
};
#endif // SUPPORT_DDR4

GLOBAL_REMOVE_IF_UNREFERENCED const TOdtValue MbTradOdtTable[MAX_DIMMS_IN_CHANNEL][oiNotValid] = {
/// 1DPC 1R,  1DPC 2R,  2DPC 1R 1R,  2DPC 1R 2R,  2DPC 2R 1R,  2DPC 2R 2R
  {{00,40},  {00,40},  {60,30},    {60,30},    {60,30},    {60,30}},
  {{00,40},  {00,40},  {60,30},    {60,30},    {60,30},    {60,30}}
};

GLOBAL_REMOVE_IF_UNREFERENCED const TOdtValue DtTradOdtTable[MAX_DIMMS_IN_CHANNEL][oiNotValid] = {
/// 1DPC 1R,  1DPC 2R,  2DPC 1R 1R,  2DPC 1R 2R,  2DPC 2R 1R,  2DPC 2R 2R
  {{60,00},  {60,00},  {60,30},    {60,30},    {60,30},    {60,30}},
  {{60,00},  {60,00},  {60,30},    {60,30},    {60,30},    {60,30}}
};

GLOBAL_REMOVE_IF_UNREFERENCED const TOdtValue User1TradOdtTable[MAX_DIMMS_IN_CHANNEL][oiNotValid] = {
/// 1DPC 1R,  1DPC 2R,  2DPC 1R 1R,  2DPC 1R 2R,  2DPC 2R 1R,  2DPC 2R 2R
  {{60,60},  {60,60},  {60,30},    {60,30},    {60,30},    {60,30}},
  {{60,60},  {60,60},  {60,30},    {60,30},    {60,30},    {60,30}}
};

GLOBAL_REMOVE_IF_UNREFERENCED const TOdtValue User2TradOdtTable[MAX_DIMMS_IN_CHANNEL][oiNotValid] = {
/// 1DPC 1R,  1DPC 2R,  2DPC 1R 1R,  2DPC 1R 2R,  2DPC 2R 1R,  2DPC 2R 2R
  {{60,60},  {60,60},  {60,40},    {60,40},    {60,40},    {60,40}},
  {{60,60},  {60,60},  {60,40},    {60,40},    {60,40},    {60,40}}
};

//
// Module external functions
//
/**
  this function reverses MA and BA bits for Rank1

  @param[in] MrcData         - include all the MRC data
  @param[in] Dimm            - current DIMM
  @param[in] BA              - MRS command to be sent
  @param[in] MA              - Value to be sent

  @retval Proper MA and BA BITS.
**/
UINT32
MrcMirror (
  IN MrcParameters *const MrcData,
  IN MrcDimmOut      *Dimm,
  IN UINT8           BA,
  IN UINT16          MA
  )
{
  UINT16 ma357;
  UINT16 ma468;

  //
  // DDR3 UDIMM/SODIMM reverses the following bits on Rank1
  // A3 - 4, A5 - 6, A7 - 8
  // BA0 - 1
  //
  ma357 = 0xA8 & MA;
  ma468 = 0x150 & MA;
  MA    = (0xFE07 & MA) | (ma357 << 1) | (ma468 >> 1);
  BA    = (0xC & BA) | ((0x2 & BA) >> 1) | ((0x1 & BA) << 1);

  if (MrcData->Outputs.DdrType == MRC_DDR_TYPE_DDR4) {
    //
    // DDR4 UDIMM/SODIMM reverses the following bits on Rank1
    // A3 - 4, A5 - 6, A7 - 8, A11 - A13
    // BA0 - 1, BG0 - BG1 (only for x8)
    //
    MA = (0xD7FF & MA) | ((MRC_BIT13 & MA) >> 2) | ((MRC_BIT11 & MA) << 2);

    if (Dimm->SdramWidth == 8) {
      BA = (0x3 & BA) | ((MRC_BIT3 & BA) >> 1) | ((MRC_BIT2 & BA) << 1);
    }
  }

  return (BA << 24) + MA;
}

/**
  this function writes to CADB

  @param[in] MrcData         - include all the MRC data
  @param[in] Channel         - Channel to send command to
  @param[in] RankMask        - Rank mask for which command will be sent to.
  @param[in] CMD             - 0: MRS, 1: REF, 2: PRE, 3: ACT, 4: WR, 5: RD, 6: ZQ, 7: NOP
  @param[in] BA              - MRS command to be sent
  @param[in] MA              - Value to be sent
  @param[in] Delay           - Delay in Dclocks

  @retval MrcStatus
**/
MrcStatus
MrcWriteCADBCmd (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          RankMask,
  IN const UINT8          CMD,
  IN const UINT8          BA,
  IN const UINT16 *const  MA,
  IN const UINT8          Delay
  )
{
  const MrcInput                              *Inputs;
  MrcOutput                                   *Outputs;
  MrcChannelOut                               *ChannelOut;
  MrcStatus                                   Status;
  UINT32                                      Offset;
  UINT32                                      OffsetCfg;
  UINT32                                      OffsetCtl;
  UINT8                                       Stop;
  UINT8                                       Dimm;
  UINT8                                       Rank;
  UINT8                                       AddressMirrored; // bitMask
  MCHBAR_CH0_CR_REUT_CH_PAT_CADB_WRITE_POINTER_STRUCT  ReutChPatCadbWritePointer;
  MCHBAR_CH0_CR_REUT_CH_PAT_CADB_PROG_STRUCT  ReutChPatCadbProg;
  MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MRS_STRUCT   ReutChPatCadbMrs;
  MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT   ReutChSeqCfg;
  MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT   ReutChSeqCfgSave;
  MCDFXS_CR_REUT_CH_SEQ_CTL_MCMAIN_0_STRUCT   ReutChSeqCtl;
  MCDFXS_CR_REUT_GLOBAL_ERR_MCMAIN_STRUCT     ReutGlobalErr;
  MrcDebug                                    *Debug;

  Inputs          = &MrcData->Inputs;
  Outputs         = &MrcData->Outputs;
  Debug           = &Outputs->Debug;
  ChannelOut      = &Outputs->Controller[0].Channel[Channel];
  Status          = mrcSuccess;
  Stop            = 0;
  AddressMirrored = 0;

  //
  // Check for AddressMirrored on each DIMM present
  //
  for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
    if (ChannelOut->Dimm[Dimm].AddressMirrored == TRUE) {
      AddressMirrored |= (MRC_BIT0 << Dimm);
    }
  }
  //
  // Pointer will be dynamically incremented after a write to CADB_PROG register
  //
  ReutChPatCadbWritePointer.Data = 0;
  ReutChPatCadbWritePointer.Bits.Write_Enable = 1;
  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_WRITE_POINTER_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_WRITE_POINTER_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_WRITE_POINTER_REG) * Channel);
  MrcWriteCR (MrcData, Offset, ReutChPatCadbWritePointer.Data);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
      continue;
    }
    if ((1 << Rank) & RankMask) {
      Dimm = RANK_TO_DIMM_NUMBER (Rank);

      ReutChPatCadbProg.Data                   = 0;
      ReutChPatCadbProg.Bits.CADB_Data_Bank    = BA;
      ReutChPatCadbProg.Bits.CADB_Data_Address = MA[Dimm];

      //
      // Check if Rank 1 and if DIMM requires AddressMirrored
      //
      if ((Rank % 2) && (AddressMirrored & ((Rank / 2) + 1))) {
        //
        // Remainder is 1 only for Rank1 of each DIMM
        //
        ReutChPatCadbProg.Data = MrcMirror (MrcData, &ChannelOut->Dimm[Dimm], BA, MA[Dimm]);
      }

      ReutChPatCadbProg.Bits.CADB_Data_CKE     = 0xF;
      ReutChPatCadbProg.Bits.CADB_Data_Control = CMD;
      ReutChPatCadbProg.Bits.CADB_Data_CS      = ~(MRC_BIT0 << Rank);

      Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_PROG_REG +
        ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_PROG_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_PROG_REG) * Channel);
      MrcWriteCR64 (MrcData, Offset, ReutChPatCadbProg.Data);

      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "CH%d Rank %d ReutChPatCadbProg: 0x%08X%08X\n", Channel, Rank, ReutChPatCadbProg.Data32[1], ReutChPatCadbProg.Data32[0]);

      Stop += 1;
    }
  }

  if (Stop == 0) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "MrcWriteCADBCmd: Channel %d RankMask %d ValidRankBitMask 0x%X\n",
      Channel,
      RankMask,
      ChannelOut->ValidRankBitMask
      );
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MrcWriteCADBCmd: Not a valid Rank in RankBitMask\n");
    Status = mrcFail;
    return Status;
  }
  //
  // Execute MRS Mode
  //
  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MRS_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MRS_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MRS_REG) * Channel);
  ReutChPatCadbMrs.Data                      = 0;
  ReutChPatCadbMrs.Bits.MRS_Gap              = (Delay == 0) ? 3 : Delay;
  ReutChPatCadbMrs.Bits.MRS_Gap_Scale        = 1;                           // Linear
  ReutChPatCadbMrs.Bits.CADB_MRS_End_Pointer = Stop - 1;
  ReutChPatCadbMrs.Bits.MRS_Wait             = 1;
  ReutChPatCadbMrs.Bits.MRS_Wait_Scale       = 1;                           // Linear
  MrcWriteCR (MrcData, Offset, ReutChPatCadbMrs.Data);

  //
  // Save before MR command
  //
  OffsetCfg = MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG +
    ((MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG) * Channel);
  ReutChSeqCfgSave.Data = MrcReadCR (MrcData, OffsetCfg);

  //
  // Clear errors while we are in CPGC mode
  //
  ReutChSeqCfg.Data                     = ReutChSeqCfgSave.Data;
  ReutChSeqCfg.Bits.Global_Control      = 0;
  ReutChSeqCfg.Bits.Initialization_Mode = REUT_Testing_Mode;
  MrcWriteCR (MrcData, OffsetCfg, (UINT32) ReutChSeqCfg.Data);

  OffsetCtl = MCDFXS_CR_REUT_CH_SEQ_CTL_MCMAIN_0_REG +
    ((MCDFXS_CR_REUT_CH_SEQ_CTL_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CTL_MCMAIN_0_REG) * Channel);
  ReutChSeqCtl.Data                    = 0;
  ReutChSeqCtl.Bits.Local_Clear_Errors = 1;
  MrcWriteCR (MrcData, OffsetCtl, ReutChSeqCtl.Data);

  //
  // Prepare for MRS command
  //
  ReutChSeqCfg.Bits.Initialization_Mode = MRS_Mode;
  MrcWriteCR (MrcData, OffsetCfg, (UINT32) ReutChSeqCfg.Data); // Set MRS Mode w/o Global control

  //
  // Set the MRS LoopCount to a single iteration
  //
  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MRS_LOOPCOUNT_LIMIT_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MRS_LOOPCOUNT_LIMIT_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MRS_LOOPCOUNT_LIMIT_REG) * Channel);
  MrcWriteCR (MrcData, Offset, 1);

  //
  // Start test and clear errors
  //
  ReutChSeqCtl.Bits.Local_Start_Test = 1;
  MrcWriteCR (MrcData, OffsetCtl, ReutChSeqCtl.Data);

  //
  // Wait for Channel_Test_Done_Status for the channel.
  //
  // @todo: Infinite loop possible, need timer.
  //
  do {
    ReutGlobalErr.Data = MrcReadCR (MrcData, MCDFXS_CR_REUT_GLOBAL_ERR_MCMAIN_REG);
    if (1 == ((Channel == 0) ? ReutGlobalErr.Bits.Channel_Error_Status_0 : ReutGlobalErr.Bits.Channel_Error_Status_1)) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR IN MrcWriteCADBCmd: REUT_GLOBAL_ERR 0x%X\n", ReutGlobalErr.Data);
      Status = mrcFail;
      break;
    }
  } while (0 == ((Channel == 0) ? ReutGlobalErr.Bits.Channel_Test_Done_Status_0 : ReutGlobalErr.Bits.Channel_Test_Done_Status_1));

  //
  // Restore after MR command
  //
  MrcWriteCR (MrcData, OffsetCfg, (UINT32) ReutChSeqCfgSave.Data);

  ReutChSeqCtl.Data                    = 0;
  ReutChSeqCtl.Bits.Local_Clear_Errors = 1;
  MrcWriteCR (MrcData, OffsetCtl, ReutChSeqCtl.Data);

  return Status;
}

/**
  This function sends the proper MRS command for specific ranks as indicated by RankMask

  @param[in] MrcData         - include all the MRC data
  @param[in] Channel         - Channel to send command to
  @param[in] RankMask        - Rank mask for which command will be sent to
  @param[in] MR              - MRS command to be sent
  @param[in] DimmValue       - Dimm Values to be sent

  @retval MrcStatus
**/
MrcStatus
MrcWriteMRSAll (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          RankMask,
  IN const UINT8          MR,
  IN const UINT16 *const  DimmValue
  )
{
  UINT8 MRSCmd;

#if (SUPPORT_DDR4 == SUPPORT)
  if (MrcData->Outputs.DdrType == MRC_DDR_TYPE_DDR4) {
    //
    // DDR4 CMD = [8: MRS, 9: REF, 0xA: PRE,     0xC: WR, D: RD, E: ZQ, F: NOP]
    //
    MRSCmd = DDR4_MRS_CMD;
  } else
#endif // SUPPORT_DDR4
  {
    //
    // DDR3 CMD = [0: MRS, 1: REF, 2: PRE, 3: ACT, 4: WR, 5: RD, 6: ZQ, 7: NOP]
    //
    MRSCmd = MRS_CMD;
  }
  return MrcWriteCADBCmd (MrcData, Channel, RankMask, MRSCmd, MR, DimmValue, 0);;
}

/**
  This function sends the proper MRS command for specific ranks as indicated by RankMask

  @param[in] MrcData         - Include all the MRC data
  @param[in] Channel         - Channel to send command to
  @param[in] RankMask        - Rank mask for which command will be sent to
  @param[in] MR              - MRS command to be sent
  @param[in] Value           - Value to be sent

  @retval MrcStatus
**/
MrcStatus
MrcWriteMRS (
  IN MrcParameters  *const MrcData,
  IN const UINT8           Channel,
  IN UINT8                 RankMask,
  IN const UINT8           MR,
  IN const UINT16          Value
  )
{
  MrcChannelOut *ChannelOut;
  MrcStatus     Status;
  UINT8         MRSCmd;
  UINT16        DimmValue[MAX_DIMMS_IN_CHANNEL];

  ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
  RankMask &= ChannelOut->ValidRankBitMask;

  //
  // Update proper Dimm Values based on Ranks (rank bit mask)
  //
  if (RankMask & 0x3) {
    //
    // For DIMM 0
    //
    DimmValue[0] = Value;
  } else  {
    DimmValue[0] = 0;
  }
  if (RankMask & 0xC) {
    //
    // For DIMM 1
    //
    DimmValue[1] = Value;
  } else  {
    DimmValue[1] = 0;
  }

#if (SUPPORT_DDR4 == SUPPORT)
  if (MrcData->Outputs.DdrType == MRC_DDR_TYPE_DDR4) {
    //
    // DDR4 CMD = [8: MRS, 9: REF, 0xA: PRE,     0xC: WR, D: RD, E: ZQ, F: NOP]
    //
    MRSCmd = DDR4_MRS_CMD;
  } else
#endif // SUPPORT_DDR4
  {
    //
    // DDR3 CMD = [0: MRS, 1: REF, 2: PRE, 3: ACT, 4: WR, 5: RD, 6: ZQ, 7: NOP]
    //
    MRSCmd = MRS_CMD;
  }
  Status = MrcWriteCADBCmd (MrcData, Channel, RankMask, MRSCmd, MR, DimmValue, 0);

  return Status;
}

/**
  Issue ZQ calibration command on all ranks.
  When done, wait appropriate delay depending on the ZQ type.

  @param[in] MrcData         - include all the MRC data
  @param[in] chBitMask       - Channel bit mask to be sent to.
  @param[in] ZqType          - Type of ZQ Calibration: see MrcZqType enum

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcIssueZQ (
  IN MrcParameters *const MrcData,
  IN const UINT8          chBitMask,
  IN const MrcZqType      ZqType
  )
{
  MrcOutput *Outputs;
  MrcStatus Status;
  MrcDebug  *Debug;
  MrcTiming *Timing;
  UINT8     Channel;
  UINT8     Dimm;
  UINT8     Delay;
  UINT16    MaValue;
  UINT16    DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT32    OpCode;
#ifdef MRC_DEBUG_PRINT
  char      *StrZqType;
#endif // MRC_DEBUG_PRINT
  UINT8     Rank;
  BOOLEAN   Lpddr;
  BOOLEAN   DelayNeeded;
#if (SUPPORT_DDR4 == SUPPORT)
  BOOLEAN   Ddr4;
#endif // SUPPORT_DDR4
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;
  Timing  = NULL;
  DelayNeeded = FALSE;
  Delay   = 1;

  //
  // Check if LPDDR3 memory is used
  //
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
#if (SUPPORT_DDR4 == SUPPORT)
  Ddr4 = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
#endif // SUPPORT_DDR4
  MaValue = 0;

  switch (ZqType) {
    case MRC_ZQ_INIT:
#ifdef MRC_DEBUG_PRINT
      StrZqType = "INIT";
#endif
      MaValue = MRC_BIT10;
      OpCode  = 0xFF;
      break;

    case MRC_ZQ_LONG:
#ifdef MRC_DEBUG_PRINT
      StrZqType = "LONG";
#endif
      MaValue = MRC_BIT10;
      OpCode  = 0xAB;
      break;

    case MRC_ZQ_SHORT:
#ifdef MRC_DEBUG_PRINT
      StrZqType = "SHORT";
#endif
      OpCode  = 0x56;
      break;

    case MRC_ZQ_RESET:
#ifdef MRC_DEBUG_PRINT
      StrZqType = "RESET";
#endif
      OpCode  = 0xC3;
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Wrong ZQ type: %d\n", ZqType);
      return mrcWrongInputParameter;
  }

  //
  // Program MA value for all DIMMs
  //
  for (Dimm = 0; Dimm < (sizeof (DimmValue) / sizeof (DimmValue[0])); Dimm++) {
    DimmValue[Dimm] = MaValue;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      if ((MRC_BIT0 << Channel) & chBitMask) {
        DelayNeeded = TRUE;
        Timing = &Outputs->Controller[0].Channel[Channel].Timing[MrcData->Inputs.MemoryProfile];
        if (!(MRC_BIT0 << (Channel + 1) & chBitMask) && (ZqType == MRC_ZQ_SHORT)) {
          Delay = 7;
        }
        //
        // Issue ZQ calibration command on all ranks of this channel
        //
        if (Lpddr) {
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
              //
              // MR10, ZQ calibration
              //
              if (!Outputs->JedecInitDone) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "LPDDR: Issue ZQ %s on ch %d rank %d\n", StrZqType, Channel, Rank);
              }
              Status = MrcIssueMrw (MrcData, Channel, Rank, 10, OpCode, FALSE, FALSE, TRUE);

              //
              // Delay after each rank, we have to do ZQ calibration serially between ranks on LPDDR3.
              //
              if ((ZqType == MRC_ZQ_INIT) || (ZqType == MRC_ZQ_LONG)) {
                MrcWait (MrcData, 6 * HPET_MIN);
              } else if (ZqType == MRC_ZQ_SHORT) {
                MrcWait (MrcData, 2 * HPET_MIN);
              }
            }
          } // for Rank
          DelayNeeded = FALSE;
        } else
#if (SUPPORT_DDR4 == SUPPORT)
        if (Ddr4) {
          if (MrcData->Inputs.Ddr4DdpSharedZq) {  // Send ZQ calibration on one rank at a time
            for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
              if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
                if (!Outputs->JedecInitDone) {
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR4: Issue ZQ %s on ch %d rank %d\n", StrZqType, Channel, Rank);
                }
                Status = MrcWriteCADBCmd (MrcData, Channel, 1 << Rank, DDR4_ZQ_CMD, 0, DimmValue, Delay);

                // Delay after each rank, we have to do ZQ calibration serially on DDP package with shared ZQ pin
                if ((ZqType == MRC_ZQ_INIT) || (ZqType == MRC_ZQ_LONG)) {
                  MrcWait (MrcData, 37 * HPET_MIN);
                } else if (ZqType == MRC_ZQ_SHORT) {
                  MrcWait (MrcData, 5 * HPET_MIN);
                }
              }
            }
            DelayNeeded = FALSE;
          } else {  // Send ZQ calibration on all ranks in parallel
            if (!Outputs->JedecInitDone) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR4: Issue ZQ %s on ch %d\n", StrZqType, Channel);
            }
            Status = MrcWriteCADBCmd (MrcData, Channel, 0x0F, DDR4_ZQ_CMD, 0, DimmValue, Delay);
          }
        } else
#endif // SUPPORT_DDR4
        {
          //
          //          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR3: Issue ZQ %s on ch %d\n", StrZqType, Channel);
          //
          Status = MrcWriteCADBCmd (MrcData, Channel, 0x0F, ZQ_CMD, 0, DimmValue, Delay);
        }
      }
    }
  }

  if (DelayNeeded) {
    if ((ZqType == MRC_ZQ_INIT) || (ZqType == MRC_ZQ_LONG)) {
      MrcWait (MrcData, 19 * HPET_MIN);
    } else if (ZqType == MRC_ZQ_SHORT) {
      MrcWait (MrcData, 2 * HPET_MIN);
    }
  }

  return Status;
}

/**
  This function writes the MR2 register for all the ranks and channels

  @param[in, out] MrcData    - general data
  @param[in]      Pasr       - Partial array self refresh bit A0-A2

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcSetMR2 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Pasr
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  TOdtValue         *OdtTableIndex;
  MrcProfile        Profile;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             RankMod2;
  UINT8             AutoSelfRefresh;
  UINT8             SelfRefreshTemp;
  UINT16            DimmValue[MAX_DIMMS_IN_CHANNEL];
  MrcStatus         Status;
  DDR3_MODE_REGISTER_2_STRUCT Ddr3ModeRegister;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;
  Profile       = Inputs->MemoryProfile;

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut                            = &ControllerOut->Channel[Channel];
      Ddr3ModeRegister.Data                 = 0;
      Ddr3ModeRegister.Bits.PartialArraySR  = Pasr;
      //
      // Subtract 5 because of jedec mr2 CWL table 0 = 5 1=6 2=7 ...
      //
      Ddr3ModeRegister.Bits.CasWriteLatency = ChannelOut->Timing[Profile].tCWL - 5;

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += MAX_RANK_IN_DIMM) {
        //
        // loop only for each DIMM
        //
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          if (Outputs->RestoreMRs) {
            RankMod2              = Rank % 2;
            Ddr3ModeRegister.Data = ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2].MR[mrMR2];
          } else {
            //
            // ASR: Set if both bits 0 and 2 of byte 31 in SPD are set.
            //
            // @todo: Need to check and see if we need to set DDR3_MODE_REGISTER_2_STR_OFF based on EXTENDED_TEMP support
            //           If ASR need BIT6 set, else if EXTENDED_TEMP set BIT7.
            //           Need to understand the policy here or should we follow NHM's approach for LFD/CFD.
            //
            if (
                 (ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].AutoSelfRefresh == TRUE) &&
                 (!(Inputs->RhPrevention
                     && (Inputs->RhSolution == Refresh2x)
                     ) || (Outputs->AutoSelfRefresh == TRUE))
                 ) {
              AutoSelfRefresh = 1;
              SelfRefreshTemp = 0;
            } else if (ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].SelfRefreshTemp == TRUE) {
              AutoSelfRefresh = 0;
              SelfRefreshTemp = 1;
            } else {
              AutoSelfRefresh = 0;
              SelfRefreshTemp = 0;
            }

            Ddr3ModeRegister.Bits.AutoSelfRefresh = AutoSelfRefresh;
            Ddr3ModeRegister.Bits.SelfRefreshTemp = SelfRefreshTemp;

            OdtTableIndex = (TOdtValue *) GetOdtTableIndex (MrcData, Channel, RANK_TO_DIMM_NUMBER (Rank));
            if (OdtTableIndex == NULL) {
              return mrcFail;
            }

            Ddr3ModeRegister = UpdateRttWrValue (MrcData, OdtTableIndex->RttWr, Ddr3ModeRegister);

            //
            // *** must be before the MRC command because of address swizzling bits in SODIMM/UDIMM
            //
            SetTcMr2ShadowReg (MrcData, Channel, RANK_TO_DIMM_NUMBER (Rank), Ddr3ModeRegister.Data);

            //
            // save MR2 for later validation usage
            //
            RankMod2 = Rank % 2;
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2].MR[mrMR2]     = Ddr3ModeRegister.Data;
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2 + 1].MR[mrMR2] = Ddr3ModeRegister.Data;
            //
            // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MrcSetMR2  Channel %u Dimm %u Rank %u = 0x%X\n",
            //                Channel, RANK_TO_DIMM_NUMBER (Rank), Rank, Ddr3ModeRegister.Data);
            //
          }
          //
          // Update proper DIMM value
          //
          DimmValue[RANK_TO_DIMM_NUMBER (Rank) ] = Ddr3ModeRegister.Data;
        }
      }
      //
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      //
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR2, DimmValue);
    }
  }

  return Status;
}

/**
  This function writes the MR3 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] MPRLoc          - MPR Location bit A0-A1
  @param[in] Mpr             - MPR bit A2

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcSetMR3 (
  IN MrcParameters *const MrcData,
  IN const UINT8          MPRLoc,
  IN const UINT8          Mpr
  )
{
  const MrcInput              *Inputs;
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT8                       Channel;
  UINT8                       Dimm;
  MrcStatus                   Status;
  DDR3_MODE_REGISTER_3_STRUCT Ddr3ModeRegister;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;

  //
  // Independent channel data
  //
  Ddr3ModeRegister.Data              = 0;
  Ddr3ModeRegister.Bits.MprLocation  = MPRLoc;
  Ddr3ModeRegister.Bits.MprOperation = Mpr;

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (Dimm = 0; Dimm < (sizeof (DimmValue) / sizeof (DimmValue[0])); Dimm++) {
        DimmValue[Dimm] = Ddr3ModeRegister.Data;
      }
      //
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      //
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR3, DimmValue);
    }
  }

  return Status;
}

/**
  This function writes the MR1 register for all the ranks and channels

  @param[in, out] MrcData         - include all the MRC data
  @param[in]      DLLEnable       - DLL enable bit A0
  @param[in]      Odic            - Output driver impedance control A5, A1
  @param[in]      AdditiveLatency - Additive latency bit A3-A4
  @param[in]      WlEnable        - Write leveling enable bit A7
  @param[in]      Tdqs            - TDQS enable bit A11
  @param[in]      Qoff            - Qoff bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcSetMR1 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          DLLEnable,
  IN     const UINT8          Odic,
  IN     const UINT8          AdditiveLatency,
  IN     const UINT8          WlEnable,
  IN     const UINT8          Tdqs,
  IN     const UINT8          Qoff
  )
{
  const MrcInput              *Inputs;
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  TOdtValue                   *OdtTableIndex;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT8                       Channel;
  UINT8                       Rank;
  UINT8                       RankMod2;
  UINT8                       RttNom;
  MrcStatus                   Status;
  DDR3_MODE_REGISTER_1_STRUCT Ddr3ModeRegister;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;
  OdtTableIndex = NULL;

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {

      ChannelOut = &ControllerOut->Channel[Channel];
      //
      // independent channel data
      //
      Ddr3ModeRegister.Data                 = 0;
      Ddr3ModeRegister.Bits.DllEnable       = DLLEnable;
      Ddr3ModeRegister.Bits.ODImpedanceLow  = Odic & 1;
      Ddr3ModeRegister.Bits.ODImpedanceHigh = (Odic & 2) >> 1;
      Ddr3ModeRegister.Bits.AdditiveLatency = AdditiveLatency;
      Ddr3ModeRegister.Bits.WriteLeveling   = WlEnable;
      Ddr3ModeRegister.Bits.Tdqs            = Tdqs; // @todo: We used to set Tdqs if the DIMM is X8.
      Ddr3ModeRegister.Bits.Qoff            = Qoff;

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += 2) {
        //
        // loop only for each DIMM
        //
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          if (Outputs->RestoreMRs) {
            RankMod2              = Rank % 2;
            Ddr3ModeRegister.Data = ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2].MR[mrMR1];
          } else {
            //
            // Get the ODT table index.
            //
            OdtTableIndex = (TOdtValue *) GetOdtTableIndex (MrcData, Channel, RANK_TO_DIMM_NUMBER (Rank));
            if (OdtTableIndex == NULL) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: Un support board type\n");
              return mrcFail;
            }
            //
            // Set the RttNom value
            //
            if (!Inputs->Ddr3DramOdt) {
              RttNom = 0;   // DIMM ODT is not used
            } else {
              RttNom = OdtTableIndex->RttNom;
            }

            Ddr3ModeRegister = UpdateRttNomValue (MrcData, RttNom, Ddr3ModeRegister);

            //
            // save MR1 for later validation usage
            //
            RankMod2 = Rank % 2;
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2].MR[mrMR1]     = Ddr3ModeRegister.Data;
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2 + 1].MR[mrMR1] = Ddr3ModeRegister.Data;
            //
            // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcSetMR1  Channel %u Dimm %u Rank %u = 0x%X\n",
            //                Channel, RANK_TO_DIMM_NUMBER (Rank), Rank, Ddr3ModeRegister.Data);
            //
          }
          //
          // Update proper DIMM value
          //
          DimmValue[RANK_TO_DIMM_NUMBER (Rank) ] = Ddr3ModeRegister.Data;
        }
      }
      //
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      //
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR1, DimmValue);
    }
  }

  return Status;
}

/**
  This function writes the MR0 register for all the ranks

  @param[in, out] MrcData         - include all the MRC data
  @param[in]      CommandControl  - include the command control params
  @param[in]      BurstLength     - Burst length bit A0-A1
  @param[in]      ReadBurstType   - Read burst type bit A3
  @param[in]      TestMode        - Test mode type bit A7
  @param[in]      DllReset        - DLL reset bit A8

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcSetMR0 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          BurstLength,
  IN     const UINT8          ReadBurstType,
  IN     const UINT8          TestMode,
  IN     const UINT8          DllReset
  )
{
  /*
  CAS Latency
  A6 A5 A4 A2 CAS Latency
  0  0  0  0  Reserved
  0  0  1  0  5
  0  1  0  0  6
  0  1  1  0  7
  1  0  0  0  8
  1  0  1  0  9
  1  1  0  0  10
  1  1  1  0  11(Optional for DDR3-1600)
  CAS = (CAS - 4) <<1

  Write recovery
  A11 A10 A9 WR(cycles)
  0   0   0  16*2
  0   0   1   5*2
  0   1   0   6*2
  0   1   1   7*2
  1   0   0   8*2
  1   0   1   10*2
  1   1   0   12*2
  1   1   1   14*2
  Wr = Wr - 5
*/
  static const UINT8          WrTable[] = {1, 2, 3, 4, 0, 5, 0, 6, 0, 7, 0, 0};
  const MrcInput              *Inputs;
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  MrcProfile                  Profile;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT16                      Cas;
  UINT16                      Wr;
  UINT16                      Offset;
  UINT16                      Cl_A2;
  UINT8                       Channel;
  UINT8                       Rank;
  UINT8                       RankMod2;
  MrcStatus                   Status;
  DDR3_MODE_REGISTER_0_STRUCT Ddr3ModeRegister;
  BOOLEAN                     UlxUlt;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;
  Profile       = Inputs->MemoryProfile;
  UlxUlt        = ((Inputs->CpuModel == cmSKL_ULX_ULT) || (Inputs->CpuModel == cmKBL_ULX_ULT));

  //
  // independent channel data
  //
  Ddr3ModeRegister.Data               = 0;
  Ddr3ModeRegister.Bits.BurstLength   = BurstLength;
  Ddr3ModeRegister.Bits.ReadBurstType = ReadBurstType;
  Ddr3ModeRegister.Bits.TestMode      = TestMode;
  Ddr3ModeRegister.Bits.DllReset      = DllReset;

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {

      ChannelOut  = &ControllerOut->Channel[Channel];

      Cas         = ChannelOut->Timing[Profile].tCL;
      Wr          = ChannelOut->Timing[Profile].tWR;

      //
      // find the new cas value from the CAS table
      //
      if (Cas < 5 || Cas > 16) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: CAS value %d is not valid \n", Cas);
        Status = mrcCasError;
      }

      if ((Wr < 5) || (Wr > 8 && Wr != 10 && Wr != 12 && Wr != 14 && Wr != 16)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: Write recovery Wr value %d is not valid \n", Wr);
        return mrcWrError;
      }
      //
      // convert CAS to jedec ddr3 values
      //
      if (Cas <= 11) {
        Offset  = 4;
        Cl_A2   = 0;
      } else {
        Offset  = 12;
        Cl_A2   = 1;
      }

      Ddr3ModeRegister.Bits.CasLatencyLow   = Cl_A2;
      Ddr3ModeRegister.Bits.CasLatencyHigh  = Cas - Offset;

      //
      // convert Wr to jedec ddr3 values
      //
      Ddr3ModeRegister.Bits.WriteRecovery = WrTable[Wr - 5];

      //
      // DLL control for PPD: slow (0) for mobile, fast (1) for desktop, open for external input
      // Note - PM_PDWN_CONFIG_C# should be aligned with this. For slow exit use DLL_off. Otherwise use all others.
      //
      Ddr3ModeRegister.Bits.PrechargePdDll =
        (
          Inputs->PowerDownMode == pdmNoPowerDown ||
          Inputs->PowerDownMode == pdmAPD
        ) ? 1 : 0;
      if ((Inputs->PowerDownMode == pdmPPD) || (Inputs->PowerDownMode == pdmAuto)) {
        //
        // A12: 0 = Slow Exit (DLL Off), 1 = Fast Exit (DLL On)
        //
        // Slow Exit (DLL Off) on ULX/ULT
        // Fast Exit on DT/Halo
        // @todo: might need Slow Exit on Halo (BGA) as well
        //
        Ddr3ModeRegister.Bits.PrechargePdDll = (UlxUlt) ? 0 : 1;
      }
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += 2) {
        //
        // loop only for each DIMM
        //
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          if (Outputs->RestoreMRs) {
            RankMod2              = Rank % 2;
            Ddr3ModeRegister.Data = ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2].MR[mrMR0];
          } else {
            //
            // save MR0 for later validation usage
            //
            RankMod2  = Rank % 2;
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2].MR[mrMR0]     = Ddr3ModeRegister.Data;
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2 + 1].MR[mrMR0] = Ddr3ModeRegister.Data;
            //
            // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MrcSetMR0  Channel %u Dimm %u Rank %u = 0x%X\n",
            //               Channel, RANK_TO_DIMM_NUMBER (Rank), Rank, Ddr3ModeRegister.Data);
            //
          }
          //
          // Update proper DIMM value
          //
          DimmValue[RANK_TO_DIMM_NUMBER (Rank) ] = Ddr3ModeRegister.Data;
        }
      }
      //
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      //
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR0, DimmValue);
    }
  }

  return Status;
}

#if (SUPPORT_DDR4 == SUPPORT)
/**
  This function writes the MR6 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] VrefDQValue     - VrefDQ Training Value bit A0-A5
  @param[in] VrefDQRange     - VrefDQ Training Range bit A6
  @param[in] VrefDQEnable    - VrefDQ Training Enable bit A7
  @param[in] TccdL           - tCCD_L bit A10-A12
  @param[in] Restore         - When in RestoreMRs set it to FALSE to propagate the VrefDQEnable input.

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR6_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          VrefDQValue,
  IN const UINT8          VrefDQRange,
  IN const UINT8          VrefDQEnable,
  IN const UINT8          TccdL,
  IN const BOOLEAN        Restore
  )
{
  const MrcInput              *Inputs;
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT8                       Channel;
  UINT8                       Dimm;
  MrcStatus                   Status;
  DDR4_MODE_REGISTER_6_STRUCT Ddr4ModeRegister;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;

  Ddr4ModeRegister.Data                      = 0;
  Ddr4ModeRegister.Bits.VrefDqTrainingValue  = MIN (VrefDQValue, DDR4_MODE_REGISTER_6_VrefDQ_V_MAX);
  Ddr4ModeRegister.Bits.VrefDqTrainingRange  = MIN (VrefDQRange, DDR4_MODE_REGISTER_6_VrefDQ_R_MAX);
  Ddr4ModeRegister.Bits.VrefDqTrainingEnable = MIN (VrefDQEnable, DDR4_MODE_REGISTER_6_VrefDQ_E_MAX);
  Ddr4ModeRegister.Bits.Tccd_l               = MIN (TccdL, DDR4_MODE_REGISTER_6_tCCD_L_MAX);

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Dimm = 0; Dimm < (sizeof (DimmValue) / sizeof (DimmValue[0])); Dimm++) {
        if (MrcRankInChannelExist (MrcData, Dimm * 2, Channel)) {
          if (Outputs->RestoreMRs) {
            Ddr4ModeRegister.Data = ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR6];
            if (!Restore) { // for Dq Vref propagating
              //
              // Independent channel data
              //
              Ddr4ModeRegister.Bits.VrefDqTrainingEnable = VrefDQEnable;
            }
          } else {
            //
            // save MR6 for later validation usage
            //
            ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR6] = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[Dimm].Rank[1].MR[mrMR6] = Ddr4ModeRegister.Data;
            if (!Outputs->JedecInitDone) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MrcSetMR6_DDR4  Channel %u Dimm %u = 0x%X\n",
                Channel, Dimm, Ddr4ModeRegister.Data);
            }
          }
          DimmValue[Dimm] = Ddr4ModeRegister.Data;
          //
          // 3rd parameter is really a rank mask of which ranks to send command to.
          // If need it for all possible and present ranks, it should be 0xF.
          //
          Status = MrcWriteMRSAll (MrcData, Channel, DIMM_TO_RANK_MASK (Dimm), mrMR6, DimmValue);
        } // if Rank
      } // for Dimm
    } // if channel
  } // for Channel

  return Status;
}

/**
  This function writes the MR5 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] CaParityLat     - C/A Parity Latency Mode bit A0-A2
  @param[in] CRCErrClr       - CRC Error Clear bit A3
  @param[in] CaParityErrSts  - C/A Parity Error Status bit A4
  @param[in] OdtBufferPD     - ODT Input Buffer for Power Down bit A5
  @param[in] CaParityPErr    - CA parity Persistent Error bit A9
  @param[in] DataMask        - Data Mask bit A10
  @param[in] WriteDbi        - Write DBI bit A11
  @param[in] ReadDbi         - Read DBI bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR5_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          CaParityLat,
  IN const UINT8          CRCErrClr,
  IN const UINT8          CaParityErrSts,
  IN const UINT8          OdtBufferPD,
  IN const UINT8          CaParityPErr,
  IN const UINT8          DataMask,
  IN const UINT8          WriteDbi,
  IN const UINT8          ReadDbi
  )
{
  const MrcInput              *Inputs;
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  TOdtValueDdr4               *OdtTableIndex;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT8                       Channel;
  UINT8                       Dimm;
  UINT8                       RttParkValue;
  MrcStatus                   Status;
  DDR4_MODE_REGISTER_5_STRUCT Ddr4ModeRegister;
  BOOLEAN                     UlxUlt;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;
  UlxUlt        = ((Inputs->CpuModel == cmSKL_ULX_ULT) || (Inputs->CpuModel == cmKBL_ULX_ULT));

  //
  // Independent channel data
  //
  Ddr4ModeRegister.Data                            = 0;
  Ddr4ModeRegister.Bits.C_AParityLatencyMode       = MIN (CaParityLat, DDR4_MODE_REGISTER_5_CA_PLM_MAX);
  Ddr4ModeRegister.Bits.CrcErrorClear              = MIN (CRCErrClr, DDR4_MODE_REGISTER_5_CRC_EC_MAX);
  Ddr4ModeRegister.Bits.C_AParityErrorStatus       = MIN (CaParityErrSts, DDR4_MODE_REGISTER_5_CA_PES_MAX);
  //
  // Keep ODT input buffer enabled for DT/Halo (2DPC)
  //
  Ddr4ModeRegister.Bits.OdtInputBufferforPowerDown = (UlxUlt) ? 1 : 0;
  Ddr4ModeRegister.Bits.C_AParityPersistentError   = MIN (CaParityPErr, DDR4_MODE_REGISTER_5_CA_PPE_MAX);
  Ddr4ModeRegister.Bits.DataMask                   = MIN (DataMask, DDR4_MODE_REGISTER_5_DATAMASK_MAX);
  Ddr4ModeRegister.Bits.WriteDbi                   = MIN (WriteDbi, DDR4_MODE_REGISTER_5_WRITEDBI_MAX);
  Ddr4ModeRegister.Bits.ReadDbi                    = MIN (ReadDbi, DDR4_MODE_REGISTER_5_READ_DBI_MAX);

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Dimm = 0; Dimm < (sizeof (DimmValue) / sizeof (DimmValue[0])); Dimm++) {
        //
        // loop only for each DIMM
        //
        if (MrcRankInChannelExist (MrcData, Dimm * 2, Channel)) {
          if (Outputs->RestoreMRs) {
            Ddr4ModeRegister.Data = ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR5];
          } else {
            OdtTableIndex = (TOdtValueDdr4 *) GetOdtTableIndex (MrcData, Channel, Dimm);
            if (OdtTableIndex == NULL) {
              return mrcFail;
            }
            //
            // RttPark should not be used in VTT mode
            //
            RttParkValue = (Inputs->EnVttOdt) ? 0 : OdtTableIndex->RttPark;
            Ddr4ModeRegister = UpdateRttParkValue_DDR4 (MrcData, RttParkValue, Ddr4ModeRegister);

            //
            // save MR5 for later validation usage
            //
            ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR5] = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[Dimm].Rank[1].MR[mrMR5] = Ddr4ModeRegister.Data;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MrcSetMR5_DDR4  Channel %u Dimm %u = 0x%X\n",
              Channel, Dimm, Ddr4ModeRegister.Data);
          }
          //
          // Update proper DIMM value
          //
          DimmValue[Dimm] = Ddr4ModeRegister.Data;
        }
      }
      //
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      //
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR5, DimmValue);
    }
  }

  return Status;
}

/**
  This function writes the MR4 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] MaxPDMode       - Maximum Power Down Mode bit A1
  @param[in] TempRange       - Temperature Controlled Refresh Range bit A2
  @param[in] TempMode        - Temperature Controlled Refresh Mode bit A3
  @param[in] IntVref         - Internal Vref Monitor bit A4
  @param[in] CS2CALatency    - CS to CMD/ADDR Latency Mode (cycles) bit A6-A8
  @param[in] SelfRefAbort    - Self Refresh Abort bit A9
  @param[in] RdPreaMode      - Read Preamble Training Mode bit A10
  @param[in] RdPrea          - Read Preamble bit A11
  @param[in] WrPrea          - Write Preamble bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR4_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          MaxPDMode,
  IN const UINT8          TempRange,
  IN const UINT8          TempMode,
  IN const UINT8          IntVref,
  IN const UINT8          CS2CALatency,
  IN const UINT8          SelfRefAbort,
  IN const UINT8          RdPreaMode,
  IN const UINT8          RdPrea,
  IN const UINT8          WrPrea
  )
{
  const MrcInput              *Inputs;
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT8                       Channel;
  UINT8                       Dimm;
  MrcStatus                   Status;
  DDR4_MODE_REGISTER_4_STRUCT Ddr4ModeRegister;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;

  //
  // Independent channel data
  //
  Ddr4ModeRegister.Data                          = 0;
  Ddr4ModeRegister.Bits.MaxPowerDownMode         = MIN (MaxPDMode, DDR4_MODE_REGISTER_4_MAX_PD_MAX);
  Ddr4ModeRegister.Bits.TempRefreshRange         = MIN (TempRange, DDR4_MODE_REGISTER_4_TCRR_MAX);
  //
  // MR4[2] = 0 (Temperature Controlled Refresh Range = Normal)
  // MR4[3] = 1 (Temperature Controlled Refresh Mode = Enabled)
  //
  if ((Outputs->TCRSensitiveHynixDDR4) || (Outputs->TCRSensitiveMicronDDR4)) {
    Ddr4ModeRegister.Bits.TempRefreshMode          = 0;
  } else {
    Ddr4ModeRegister.Bits.TempRefreshMode          = 1;
  }
  Ddr4ModeRegister.Bits.InternalVrefMonitor      = MIN (IntVref, DDR4_MODE_REGISTER_4_IVM_MAX);
  Ddr4ModeRegister.Bits.CstoCmd_AddrLatencyMode  = MIN (CS2CALatency, DDR4_MODE_REGISTER_4_C_CA_LAT_MAX);
  Ddr4ModeRegister.Bits.SelfRefreshAbort         = MIN (SelfRefAbort, DDR4_MODE_REGISTER_4_SRA_MAX);
  Ddr4ModeRegister.Bits.ReadPreambleTrainingMode = MIN (RdPreaMode, DDR4_MODE_REGISTER_4_R_PRE_TM_MAX);
  Ddr4ModeRegister.Bits.ReadPreamble             = MIN (RdPrea, DDR4_MODE_REGISTER_4_R_PRE_MAX);
  Ddr4ModeRegister.Bits.WritePreamble            = MIN (WrPrea, DDR4_MODE_REGISTER_4_W_PRE_MAX);

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Dimm = 0; Dimm < (sizeof (DimmValue) / sizeof (DimmValue[0])); Dimm++) {
        if (MrcRankInChannelExist (MrcData, Dimm * 2, Channel)) {
          if (Outputs->RestoreMRs) {
            Ddr4ModeRegister.Data = ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR4];
          } else {
            //
            // save MR4 for later validation usage
            //
            ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR4] = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[Dimm].Rank[1].MR[mrMR4] = Ddr4ModeRegister.Data;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MrcSetMR4_DDR4  Channel %u Dimm %u = 0x%X\n",
              Channel, Dimm, Ddr4ModeRegister.Data);
          }
          DimmValue[Dimm] = Ddr4ModeRegister.Data;
        }
      }
      //
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      //
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR4, DimmValue);
    }
  }

  return Status;
}

/**
  This function writes the MR3 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] MprPage         - MPR Page Selection bit A0-A1
  @param[in] MprOper         - MPR Operation bit A2
  @param[in] MprReadFormat   - MPR Read Format bit A11-A12
  @param[in] Geardown        - Geardown Mode bit A3
  @param[in] PDA             - Per DRAM Addressability bit A4
  @param[in] TempSensor      - Temperature Sensor Readout bit A5
  @param[in] RefreshRate     - Fine Granularity Refresh Mode bit A6-A8
  @param[in] WriteCMDLatency - Write CMD Latency when DM are enabled bit A9-A10

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR3_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          MprPage,
  IN const UINT8          MprOper,
  IN const UINT8          MprReadFormat,
  IN const UINT8          Geardown,
  IN const UINT8          PDA,
  IN const UINT8          TempSensor,
  IN const UINT8          RefreshRate,
  IN const UINT8          WriteCMDLatency
  )
{
  const MrcInput              *Inputs;
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT8                       Channel;
  UINT8                       Dimm;
  MrcStatus                   Status;
  DDR4_MODE_REGISTER_3_STRUCT Ddr4ModeRegister;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;

  //
  // Independent channel data
  //
  Ddr4ModeRegister.Data                       = 0;
  Ddr4ModeRegister.Bits.MprPageSelection      = MIN (MprPage, DDR4_MODE_REGISTER_3_MPR_PAGE_MAX);
  Ddr4ModeRegister.Bits.MprOperation          = MIN (MprOper, DDR4_MODE_REGISTER_3_MPR_MAX);
  Ddr4ModeRegister.Bits.MprReadFormat         = MIN (MprReadFormat, DDR4_MODE_REGISTER_3_MPR_READ_MAX);
  Ddr4ModeRegister.Bits.GeardownMode          = MIN (Geardown, DDR4_MODE_REGISTER_3_GM_MAX);
  Ddr4ModeRegister.Bits.PerDramAddressability = MIN (PDA, DDR4_MODE_REGISTER_3_PDA_MAX);
  Ddr4ModeRegister.Bits.TempSensorReadout     = MIN (TempSensor, DDR4_MODE_REGISTER_3_TSR_MAX);
  Ddr4ModeRegister.Bits.RefreshRateMode       = MIN (RefreshRate, DDR4_MODE_REGISTER_3_FGRM_MAX);
  Ddr4ModeRegister.Bits.WriteCmdLatency       = MIN (WriteCMDLatency, DDR4_MODE_REGISTER_3_WCMDL_MAX);

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Dimm = 0; Dimm < (sizeof (DimmValue) / sizeof (DimmValue[0])); Dimm++) {
        if (MrcRankInChannelExist (MrcData, Dimm * 2, Channel)) {
          if (Outputs->RestoreMRs) {
            Ddr4ModeRegister.Data = ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR3];
          } else {
            //
            // save MR3 for later validation usage
            //
            ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR3] = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[Dimm].Rank[1].MR[mrMR3] = Ddr4ModeRegister.Data;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MrcSetMR3_DDR4  Channel %u Dimm %u = 0x%X\n",
              Channel, Dimm, Ddr4ModeRegister.Data);
          }
          DimmValue[Dimm] = Ddr4ModeRegister.Data;
        }
      }
      //
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      //
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR3, DimmValue);
    }
  }

  return Status;
}

/**
  This function writes the MR2 register for all the ranks and channels

  @param[in, out] MrcData    - general data
  @param[in]      WriteCRC   - Write CRC Enable bit (A12)

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR2_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          WriteCRC
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  TOdtValueDdr4     *OdtTableIndex;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             RankMod2;
  UINT8             JedecCwlValue;
  UINT16            DimmValue[MAX_DIMMS_IN_CHANNEL];
  MrcStatus         Status;
  MrcProfile        Profile;
  DDR4_MODE_REGISTER_2_STRUCT Ddr4ModeRegister;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Profile       = Inputs->MemoryProfile;
  Status        = mrcSuccess;

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut                            = &ControllerOut->Channel[Channel];
      Ddr4ModeRegister.Data                 = 0;
      Ddr4ModeRegister.Bits.WriteCrc        = WriteCRC;

      if (ChannelOut->Timing[Profile].tCWL <= 12) {
        //
        // Subtract 9 because of jedec mr2 CWL table 0 = 9 1=10 2=11 3=12
        //
        JedecCwlValue = (UINT8) (ChannelOut->Timing[Profile].tCWL - 9);
      } else {
        JedecCwlValue = (UINT8) ((ChannelOut->Timing[Profile].tCWL - 14) / 2);
        JedecCwlValue |= MRC_BIT2;  //corresponds to MR2[A5] bit
      }
      Ddr4ModeRegister.Bits.CasWriteLatency = JedecCwlValue;
/*IVT
      if (Outputs->Frequency <= f1333) {
        JedecCwlValue = 0; //tCWL = 9
      } else if (Outputs->Frequency <= f1600) {
        JedecCwlValue = 2; //tCWL = 11
      } else if (Outputs->Frequency <= f1867) {
        JedecCwlValue = 3; //tCWL = 12
      } else if (Outputs->Frequency <= f2133) {
        JedecCwlValue = 4; //tCWL = 14
      } else {
        JedecCwlValue = 5; //tCWL = 16
      }
//IVT*/

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += MAX_RANK_IN_DIMM) {
        //
        // loop only for each DIMM
        //
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          if (Outputs->RestoreMRs) {
            RankMod2              = Rank % 2;
            Ddr4ModeRegister.Data = ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2].MR[mrMR2];
          } else {
            //
            // LP ASR: 00b = Manual Normal (0-85C), 01b = Manual Reduced (0-45C), 10b = Manual Extended (0-95C), 11b = Auto
            //
            Ddr4ModeRegister.Bits.LowPowerArraySelfRefresh = 3;

            OdtTableIndex = (TOdtValueDdr4 *) GetOdtTableIndex (MrcData, Channel, RANK_TO_DIMM_NUMBER (Rank));
            if (OdtTableIndex == NULL) {
              return mrcFail;
            }

            Ddr4ModeRegister = UpdateRttWrValue_DDR4 (MrcData, OdtTableIndex->RttWr, Ddr4ModeRegister);

            //
            // *** must be before the MRC command because of address swizzling bits in SODIMM/UDIMM
            //
            SetTcMr2ShadowReg (MrcData, Channel, RANK_TO_DIMM_NUMBER (Rank), Ddr4ModeRegister.Data);

            //
            // save MR2 for later validation usage
            //
            RankMod2 = Rank % 2;
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2].MR[mrMR2]     = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2 + 1].MR[mrMR2] = Ddr4ModeRegister.Data;
            //
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MrcSetMR2_DDR4  Channel %u Dimm %u Rank %u = 0x%X\n",
              Channel, RANK_TO_DIMM_NUMBER (Rank), Rank, Ddr4ModeRegister.Data);
            //
          }
          //
          // Update proper DIMM value
          //
          DimmValue[RANK_TO_DIMM_NUMBER (Rank) ] = Ddr4ModeRegister.Data;
        }
      }
      //
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      //
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR2, DimmValue);
    }
  }

  return Status;
}

/**
  This function writes the MR1 register for all the ranks and channels

  @param[in, out] MrcData         - include all the MRC data
  @param[in]      DLLEnable       - DLL enable bit A0
  @param[in]      Odic            - Output driver impedance control A1-A2
  @param[in]      AdditiveLatency - Additive latency bit A3-A4
  @param[in]      WlEnable        - Write leveling enable bit A7
  @param[in]      Qoff            - Qoff bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR1_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          DLLEnable,
  IN     const UINT8          Odic,
  IN     const UINT8          AdditiveLatency,
  IN     const UINT8          WlEnable,
  IN     const UINT8          Qoff
  )
{
  const MrcInput              *Inputs;
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  TOdtValueDdr4               *OdtTableIndex;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT8                       Channel;
  UINT8                       Rank;
  UINT8                       RankMod2;
  MrcStatus                   Status;
  DDR4_MODE_REGISTER_1_STRUCT Ddr4ModeRegister;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;
  OdtTableIndex = NULL;

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {

      ChannelOut = &ControllerOut->Channel[Channel];
      //
      // independent channel data
      //
      Ddr4ModeRegister.Data                 = 0;
      Ddr4ModeRegister.Bits.DllEnable       = DLLEnable;
      Ddr4ModeRegister.Bits.ODImpedance     = Odic;
      Ddr4ModeRegister.Bits.AdditiveLatency = AdditiveLatency;
      Ddr4ModeRegister.Bits.WriteLeveling   = WlEnable;
      Ddr4ModeRegister.Bits.Qoff            = Qoff;

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += 2) {
        //
        // loop only for each DIMM
        //
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          if (Outputs->RestoreMRs) {
            RankMod2              = Rank % 2;
            Ddr4ModeRegister.Data = ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2].MR[mrMR1];
          } else {
            //
            // Get the ODT table index.
            //
            OdtTableIndex = (TOdtValueDdr4 *) GetOdtTableIndex (MrcData, Channel, RANK_TO_DIMM_NUMBER (Rank));
            if (OdtTableIndex == NULL) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: Un support board type\n");
              return mrcFail;
            }
            //
            // Set the RttNom value
            //
            Ddr4ModeRegister = UpdateRttNomValue_DDR4 (MrcData, OdtTableIndex->RttNom, Ddr4ModeRegister);

            //
            // save MR1 for later validation usage
            //
            RankMod2 = Rank % 2;
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2].MR[mrMR1]     = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2 + 1].MR[mrMR1] = Ddr4ModeRegister.Data;
            //
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcSetMR1_DDR4  Channel %u Dimm %u Rank %u = 0x%X\n",
              Channel, RANK_TO_DIMM_NUMBER (Rank), Rank, Ddr4ModeRegister.Data);
            //
          }
          //
          // Update proper DIMM value
          //
          DimmValue[RANK_TO_DIMM_NUMBER (Rank) ] = Ddr4ModeRegister.Data;
        }
      }
      //
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      //
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR1, DimmValue);
    }
  }

  return Status;
}

/**
  This function writes the MR0 register for all the ranks

  @param[in, out] MrcData         - include all the MRC data
  @param[in]      BurstLength     - Burst length bit A0-A1
  @param[in]      ReadBurstType   - Read burst type bit A3
  @param[in]      TestMode        - Test mode type bit A7
  @param[in]      DllReset        - DLL reset bit A8

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR0_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          BurstLength,
  IN     const UINT8          ReadBurstType,
  IN     const UINT8          TestMode,
  IN     const UINT8          DllReset
  )
{
  /*
  CAS Latency
  A6 A5 A4 A2 CAS Latency
  0  0  0  0  9
  0  0  0  1  10
  0  0  1  0  11
  0  0  1  1  12
  0  1  0  0  13
  0  1  0  1  14
  0  1  1  0  15
  0  1  1  1  16
  1  0  0  0  18
  1  0  0  1  20
  1  0  1  0  22
  1  0  1  1  24
  1  1  0  0  Reserved
  1  1  0  1  17
  1  1  1  0  19
  1  1  1  1  21

  Write recovery and Read to Precharge
  A11 A10 A9 WR(cycles) RTP(cycles)
  0   0   0  10          5
  0   0   1  12          6
  0   1   0  14          7
  0   1   1  16          8
  1   0   0  18          9
  1   0   1  20          10
  1   1   0  24          12
  1   1   1  Reserved    Reserved
*/
  const MrcInput              *Inputs;
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  BOOLEAN                     CasFound;
  UINT32                      Index;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT16                      Cas;
  UINT16                      Wr;
  UINT16                      Rtp;
  UINT8                       Channel;
  UINT8                       Rank;
  UINT8                       RankMod2;
  MrcStatus                   Status;
  MrcProfile                  Profile;
  DDR4_MODE_REGISTER_0_STRUCT Ddr4ModeRegister;
  static const UINT8           CasMapping[16] = { 9, 10, 11, 12, 13, 14, 15, 16, 18, 20, 22, 24, 0, 17, 19, 21 };

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Profile       = Inputs->MemoryProfile;
  Status        = mrcSuccess;

  //
  // independent channel data
  //
  Ddr4ModeRegister.Data               = 0;
  Ddr4ModeRegister.Bits.BurstLength   = MIN (BurstLength, DDR4_MODE_REGISTER_0_BL_MAX);
  Ddr4ModeRegister.Bits.ReadBurstType = MIN (ReadBurstType, DDR4_MODE_REGISTER_0_RBT_MAX);
  Ddr4ModeRegister.Bits.TestMode      = MIN (TestMode, DDR4_MODE_REGISTER_0_TM_MAX);
  Ddr4ModeRegister.Bits.DllReset      = MIN (DllReset, DDR4_MODE_REGISTER_0_DLL_MAX);

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {

      ChannelOut  = &ControllerOut->Channel[Channel];

      Cas         = ChannelOut->Timing[Profile].tCL;
      Wr          = ChannelOut->Timing[Profile].tWR;
      Rtp         = ChannelOut->Timing[Profile].tRTP;

      //
      // Check tWR and tRTP against the spec.
      //
      if (Wr != 10 && Wr != 12 && Wr != 14 && Wr != 16 && Wr != 18 && Wr != 20 && Wr != 24) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: Write recovery Wr value %d is not valid \n", Wr);
        return mrcWrError;
      }

      if (Rtp * 2 != Wr) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: Read to Precharge RTP value %d is not half of Write recovery Wr value %d\n", Rtp, Wr);
        return mrcRtpError;
      }
      //
      // Convert CAS to jedec ddr4 MR0 encoding, this also checks that tCL is a valid value by the spec.
      //
      CasFound = FALSE;
      for (Index = 0; Index < sizeof (CasMapping) / sizeof (CasMapping[0]); Index++) {
        if ((Cas == CasMapping[Index]) && (Cas != 0)) {
          Ddr4ModeRegister.Bits.CasLatencyLow  = Index & 1;           // MR0[A2]
          Ddr4ModeRegister.Bits.CasLatencyHigh = (Index & 0x0E) >> 1; // MR0[A6:A4]
          CasFound = TRUE;
          break;
        }
      }
      if (!CasFound) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: CAS value %d is not valid \n", Cas);
        return mrcCasError;
      }

      //
      // convert Wr/RTP to jedec ddr4 values
      //
      if (Wr <= 20) {
        Ddr4ModeRegister.Bits.WriteRecoveryAndRTP = (Wr - 10) / 2;
      } else {
        Ddr4ModeRegister.Bits.WriteRecoveryAndRTP = Wr / 4;
      }

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += 2) {
        //
        // loop only for each DIMM
        //
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          if (Outputs->RestoreMRs) {
            RankMod2              = Rank % 2;
            Ddr4ModeRegister.Data = ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2].MR[mrMR0];
          } else {
            //
            // save MR0 for later validation usage
            //
            RankMod2  = Rank % 2;
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2].MR[mrMR0]     = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2 + 1].MR[mrMR0] = Ddr4ModeRegister.Data;
            //
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MrcSetMR0_DDR4  Channel %u Dimm %u Rank %u = 0x%X\n",
              Channel, RANK_TO_DIMM_NUMBER (Rank), Rank, Ddr4ModeRegister.Data);
            //
          }
          //
          // Update proper DIMM value
          //
          DimmValue[RANK_TO_DIMM_NUMBER (Rank) ] = Ddr4ModeRegister.Data;
        }
      }
      //
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      //
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR0, DimmValue);
    }
  }

  return Status;
}

/**
  This function updates the Rtt value in the MR2 value passed in.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt index.
  @param[in] Ddr3ModeRegister - Register to update.

  @retval Ddr4ModeRegister - Updated MR2 register

**/
DDR4_MODE_REGISTER_2_STRUCT
UpdateRttWrValue_DDR4 (
  MrcParameters *const        MrcData,
  const UINT8                 OdtValue,
  DDR4_MODE_REGISTER_2_STRUCT Ddr4ModeRegister
  )
{
  UINT8 RttValue;

  switch (OdtValue) {
    case 120:
      //
      // RZQ/2
      //
      RttValue = 1;
      break;
    case 240:
      //
      // RZQ/1
      //
      RttValue = 2;
      break;
    case 0xFF:
      //
      // Hi-Z
      //
      RttValue = 3;
      break;
    case 80:
      //
      // RZQ/3
      //
      RttValue = 4;
      break;
    default:
      MRC_DEBUG_MSG (
        &MrcData->Outputs.Debug,
        MSG_LEVEL_ERROR,
        "ERROR: unsupported odt RttWr value of %u\n",
        OdtValue
        );
      //no break
    case 0:
      //
      // Dynamic ODT Off
      //
      RttValue = 0;
      break;
  }

  Ddr4ModeRegister.Bits.DynamicOdt = RttValue;
  return Ddr4ModeRegister;
}

/**
  This function updates the Rtt value in the MR5 value passed in.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt index.
  @param[in] Ddr4ModeRegister - Register to update.

  @retval Ddr4ModeRegister - Updated MR5 register

**/
DDR4_MODE_REGISTER_5_STRUCT
UpdateRttParkValue_DDR4 (
  MrcParameters *const        MrcData,
  const UINT8                 OdtValue,
  DDR4_MODE_REGISTER_5_STRUCT Ddr4ModeRegister
  )
{
  UINT8 RttValue;

  switch (OdtValue) {
    case 60:
      //
      // RZQ/4
      //
      RttValue = 1;
      break;
    case 120:
      //
      // RZQ/2
      //
      RttValue = 2;
      break;
    case 40:
      //
      // RZQ/6
      //
      RttValue = 3;
      break;
    case 240:
      //
      // RZQ/1
      //
      RttValue = 4;
      break;
    case 48:
      //
      // RZQ/5
      //
      RttValue = 5;
      break;
    case 80:
      //
      // RZQ/3
      //
      RttValue = 6;
      break;
    case 34:
      //
      // RZQ/7
      //
      RttValue = 7;
      break;
    default:
      MRC_DEBUG_MSG (
        &MrcData->Outputs.Debug,
        MSG_LEVEL_ERROR,
        "ERROR: unsupported odt RttPark value of %u\n",
        OdtValue
        );
      //no break
    case 0:
      //
      // RTT_PARK Disable
      //
      RttValue = 0;
      break;
  }

  Ddr4ModeRegister.Bits.RttPark = RttValue;
  return Ddr4ModeRegister;
}

/**
  This funtion takes the MR1 register value and updates the odt value
 inside the register.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt index.
  @param[in] Ddr4ModeRegister - Register to update.

  @retval Ddr4ModeRegister  - Updated register

**/
DDR4_MODE_REGISTER_1_STRUCT
UpdateRttNomValue_DDR4 (
  IN MrcParameters *const        MrcData,
  IN const UINT8                 OdtValue,
  IN DDR4_MODE_REGISTER_1_STRUCT Ddr4ModeRegister
  )
{
  MrcDebug        *Debug;
  UINT8           Value;

  Debug = &MrcData->Outputs.Debug;
  if (OdtValue == 0) {
    //
    // rtt_nom is disable
    //
    Value = 0;
  } else if (OdtValue == 60) {
    //
    // RZQ/4
    //
    Value = 1;
  } else if (OdtValue == 120) {
    //
    // RZQ/2
    //
    Value = 2;
  } else if (OdtValue == 40) {
    //
    // RZQ/6
    //
    Value = 3;
  } else if (OdtValue == 240) {
    //
    // RZQ/1
    //
    Value = 4;
  } else if (OdtValue == 48) {
    //
    // RZQ/5
    //
    Value = 5;
  } else if (OdtValue == 80) {
    //
    // RZQ/3
    //
    Value = 6;
  } else if (OdtValue == 34) {
    //
    // RZQ/7
    //
    Value = 7;
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: unsupported odt RttNom value\n");
    Value = 0;
  }

  Ddr4ModeRegister.Bits.OdtRttValue = Value;
  return Ddr4ModeRegister;
}

/**
  This function selects the ODT table according to the board type.

  @param[in] MrcData         - Include all the MRC general data.
  @param[in] Dimm            - selected DIMM.
  @param[in] OdtIndex        - selected ODT index.

  @retval TOdtValueDdr4 * - Pointer to the relevant table or NULL if the table was not found.
**/
TOdtValueDdr4 *
SelectTable_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          Dimm,
  IN const TOdtIndex      OdtIndex
  )
{
  const MrcInput *Inputs;
  MrcDebug       *Debug;
  MrcOutput      *Outputs;
  TOdtValueDdr4  *OdtTable;

  Inputs   = &MrcData->Inputs;
  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;
  OdtTable = NULL;

  switch (Inputs->BoardType) {
    case btCRBMB:
    case btUser4:
      if ((OdtIndex >= 2) || (Dimm > 0)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Error: MbDdr4OdtTable array out of bounds! OdtIndex: %u, Dimm: %u\n", OdtIndex, Dimm);
        return NULL;
      }
      OdtTable = (TOdtValueDdr4 *) &MbDdr4OdtTable[Dimm][OdtIndex];
      break;
    case btUpServer:
    case btCRBDT:
    case btRvpOc:
      if ((Outputs->Frequency >= f2667) && (OdtIndex == oi2DPC1R1R)) {
        OdtTable = (TOdtValueDdr4 *) &DtDdr4OdtTable2667[Dimm];
      } else {
        // @todo: add support for different board topologies - T/daisy chain
        OdtTable = (TOdtValueDdr4 *) &DtDdr4OdtTable[Dimm][OdtIndex];
      }
      break;

    case btUser1:
      if ((OdtIndex >= 2) || (Dimm > 0)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Error: User1Ddr4OdtTable array out of bounds! OdtIndex: %u, Dimm: %u\n", OdtIndex, Dimm);
        return NULL;
      }
      OdtTable = (TOdtValueDdr4 *) &User1Ddr4OdtTable[Dimm][OdtIndex];
      break;

    default:
      OdtTable = NULL;
      break;
  }

  return OdtTable;
}
#endif // SUPPORT_DDR4

/**
  Return the ODT table index for the given Channel / DIMM.

  @param[in] MrcData         - Include all the mrc global data.
  @param[in] Channel         - Channel to work on.
  @param[in] Dimm            - DIMM to work on.

  @retval Pointer to the relevant ODT structure - (TOdtValue *) or (TOdtValueDdr4 *)
**/
void *
GetOdtTableIndex (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          Dimm
  )
{
  MrcDebug      *Debug;
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  MrcDimmOut    *DimmOut;
  TOdtIndex     OdtIndex;
  UINT8         Ddr4;
  UINT8         RanksInDimm0;
  UINT8         RanksInDimm1;

  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  Ddr4        = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  DimmOut     = &ChannelOut->Dimm[dDIMM0];
  RanksInDimm0 = DimmOut[dDIMM0].RankInDimm;
  RanksInDimm1 = DimmOut[dDIMM1].RankInDimm;
  OdtIndex    = oiNotValid;

  switch (ChannelOut->DimmCount) {
    case 2:
      //
      // Two dimms per channel.
      //
      if ((RanksInDimm0 == 1) && (RanksInDimm1 == 1)) {
        OdtIndex = oi2DPC1R1R;
      } else if ((RanksInDimm0 == 1) && (RanksInDimm1 == 2)) {
        OdtIndex = oi2DPC1R2R;
      } else if ((RanksInDimm0 == 2) && (RanksInDimm1 == 1)) {
        OdtIndex = oi2DPC2R1R;
      } else if ((RanksInDimm0 == 2) && (RanksInDimm1 == 2)) {
        OdtIndex = oi2DPC2R2R;
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: Invalid 2DPC rank mode\n");
      }
      break;

    case 1:
      //
      // One dimm per channel.
      //
      if ((RanksInDimm0 == 1) ||
          ((RanksInDimm1 == 1) && (MAX_DIMMS_IN_CHANNEL > 1))
          ) {
        OdtIndex = oi1DPC1R;
      } else if ((RanksInDimm0 == 2) ||
                 ((RanksInDimm1 == 2) && (MAX_DIMMS_IN_CHANNEL > 1))
                 ) {
        OdtIndex = oi1DPC2R;
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: Invalid 1DPC rank mode\n");
      }
      break;

    default:
      break;
  }

  if (Ddr4) {
    return (OdtIndex == oiNotValid) ? NULL : SelectTable_DDR4 (MrcData, Dimm, OdtIndex);
  } else {
    return (OdtIndex == oiNotValid) ? NULL : SelectTable (MrcData, Dimm, OdtIndex);
  }
}

/**
  This funtion takes the MR1 register value and updates the odt value
 inside the register.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt index.
  @param[in] Ddr3ModeRegister - Register to update.

  @retval Ddr3ModeRegister  - Updated register
**/
DDR3_MODE_REGISTER_1_STRUCT
UpdateRttNomValue (
  IN MrcParameters *const        MrcData,
  IN const UINT8                 OdtValue,
  IN DDR3_MODE_REGISTER_1_STRUCT Ddr3ModeRegister
  )
{
  MrcDebug        *Debug;
  UINT8           A2Value;
  UINT8           A6Value;
  UINT8           A9Value;

  Debug = &MrcData->Outputs.Debug;
  if (OdtValue == 0) {
    //
    // rtt_nom is disable
    //
    A2Value = 0;
    A6Value = 0;
    A9Value = 0;
  } else if (OdtValue == 60) {
    //
    // RZQ/4
    //
    A2Value = 1;
    A6Value = 0;
    A9Value = 0;
  } else if (OdtValue == 120) {
    //
    // RZQ/2
    //
    A2Value = 0;
    A6Value = 1;
    A9Value = 0;
  } else if (OdtValue == 40) {
    //
    // RZQ/6
    //
    A2Value = 1;
    A6Value = 1;
    A9Value = 0;
  } else if (OdtValue == 20) {
    //
    // RZQ/12
    //
    A2Value = 0;
    A6Value = 0;
    A9Value = 1;
  } else if (OdtValue == 30) {
    //
    // RZQ/8
    //
    A2Value = 1;
    A6Value = 0;
    A9Value = 1;
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: unsupported odt RttNom value\n");
    A2Value = 1;
    A6Value = 1;
    A9Value = 1;
  }

  Ddr3ModeRegister.Bits.OdtRttValueLow  = A2Value;
  Ddr3ModeRegister.Bits.OdtRttValueMid  = A6Value;
  Ddr3ModeRegister.Bits.OdtRttValueHigh = A9Value;
  return Ddr3ModeRegister;
}

/**
  This function updates the Rtt value in the MR2 value passed in.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt index.
  @param[in] Ddr3ModeRegister - Register to update.

  @retval Ddr3ModeRegister - Updated MR2 register
**/
DDR3_MODE_REGISTER_2_STRUCT
UpdateRttWrValue (
  MrcParameters *const        MrcData,
  const UINT8                 OdtValue,
  DDR3_MODE_REGISTER_2_STRUCT Ddr3ModeRegister
  )
{
  UINT8 RttValue;

  if ((OdtValue > 120) || ((OdtValue % 60) != 0)) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_ERROR,
      "ERROR: unsupported odt RttWr value of %u\n",
      OdtValue
      );
    RttValue = 0;
  } else {
    RttValue = OdtValue / 60;
  }

  Ddr3ModeRegister.Bits.DynamicOdt = RttValue;
  return Ddr3ModeRegister;
}

/**
  This function selects the ODT table according to the board type.

  @param[in] MrcData         - Include all the MRC general data.
  @param[in] Dimm            - selected DIMM.
  @param[in] OdtIndex        - selected ODT index.

  @retval TOdtValue * - Pointer to the relevant table or NULL if the table was not found.
**/
TOdtValue *
SelectTable (
  IN MrcParameters *const MrcData,
  IN const UINT8          Dimm,
  IN const TOdtIndex      OdtIndex
  )
{
  const MrcInput *Inputs;
  TOdtValue      *OdtTable;
  MrcDebug       *Debug;

  Inputs   = &MrcData->Inputs;
  Debug    = &MrcData->Outputs.Debug;
  OdtTable = NULL;

  switch (Inputs->BoardType) {
    case btCRBMB:
    case btCRBEMB:
    case btUser4:
      if ((OdtIndex >= 2) || (Dimm > 0)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Error: MbUltOdtTable array out of bounds! OdtIndex: %u, Dimm: %u\n", OdtIndex, Dimm);
        return NULL;
      }
      OdtTable = (TOdtValue *) &MbUltOdtTable[Dimm][OdtIndex];
      break;

    case btUpServer:
    case btCRBDT:
    case btRvpOc:
      OdtTable = (TOdtValue *) &DtTradOdtTable[Dimm][OdtIndex];
      break;

    case btUser1:
      if ((OdtIndex >= 2) || (Dimm > 0)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: User1UltOdtTable array out of bounds!\n");
        return NULL;
      }
      OdtTable = (TOdtValue *) &User1UltOdtTable[Dimm][OdtIndex];
      break;

    case btUser2:
      OdtTable = (TOdtValue *) &User2TradOdtTable[Dimm][OdtIndex];
      break;

    default:
      OdtTable = NULL;
      break;
  }

  return OdtTable;
}


/**
  Issue LPDDR MRW (Mode Register Write) command using MRH (Mode Register Handler).

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - the channel to work on
  @param[in] Rank    - the rank to work on
  @param[in] Address - MRW address
  @param[in] Data    - MRW Data
  @param[in] InitMrw - when TRUE, command is stretched (used before CA training is done)
  @param[in] ChipSelect2N - when TRUE, use 2N stretch mode for CS (used before CA training is done)
  @param[in] DebugPrint - when TRUE, will print debugging information

  @retval mrcSuccess    - MRW was sent successfully
  @retval mrcDeviceBusy - timed out waiting for MRH
**/
MrcStatus
MrcIssueMrw (
  IN MrcParameters *const MrcData,
  IN UINT32               Channel,
  IN UINT32               Rank,
  IN UINT32               Address,
  IN UINT32               Data,
  IN BOOLEAN              InitMrw,
  IN BOOLEAN              ChipSelect2N,
  IN BOOLEAN              DebugPrint
  )
{
  const MRC_FUNCTION                    *MrcCall;
  MrcDebug                              *Debug;
  MrcOutput                             *Outputs;
  UINT32                                OffsetMrCommand;
  UINT32                                OffsetGsCfg;
  MCHBAR_CH0_CR_DDR_MR_COMMAND_STRUCT   MrCommand;
  MCHBAR_CH0_CR_SC_GS_CFG_STRUCT        ScGsCfg;
  BOOLEAN                               Busy;
  UINT64                                Timeout;

  MrcCall = MrcData->Inputs.Call.Func;
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  OffsetMrCommand = MCHBAR_CH0_CR_DDR_MR_COMMAND_REG +
    ((MCHBAR_CH1_CR_DDR_MR_COMMAND_REG - MCHBAR_CH0_CR_DDR_MR_COMMAND_REG) * Channel);

  //
  // Make sure MRH is not busy
  //
  do {
    MrCommand.Data = MrcReadCR (MrcData, OffsetMrCommand);
    Busy           = (MrCommand.Bits.Busy == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out waiting for previous MRH command to finish!\n");
    return mrcDeviceBusy;
  }

  OffsetGsCfg = MCHBAR_CH0_CR_SC_GS_CFG_REG + ((MCHBAR_CH1_CR_SC_GS_CFG_REG - MCHBAR_CH0_CR_SC_GS_CFG_REG) * Channel);
  if (ChipSelect2N) {
    //
    // Enable 2N stretch mode for CS
    //
    ScGsCfg.Data = MrcReadCR (MrcData, OffsetGsCfg);
    ScGsCfg.Bits.LPDDR_2N_CS_MRW = 1;
    MrcWriteCR (MrcData, OffsetGsCfg, ScGsCfg.Data);
  }
  //
  // Send the MRW
  //
  MrCommand.Bits.Address  = Address;
  MrCommand.Bits.Data     = Data;
  MrCommand.Bits.Command = (InitMrw) ? 3 : 1; // LPDDR3: 00-MRR 01-MRW 10-Illegal 11-MRW with two cycles setup and hold
  MrCommand.Bits.Rank     = Rank;
  MrCommand.Bits.Busy     = 1;

  if (DebugPrint && (!Outputs->JedecInitDone || !Outputs->LpddrWLUpdated)) {
    MRC_DEBUG_MSG (
      Debug, MSG_LEVEL_NOTE,
      "MrcIssueMrw on ch %d rank %d: MR%d, Opcode=0x%02X, InitMrw=%d, 2N_CS=%d\n",
      Channel, Rank, Address, Data, InitMrw, ChipSelect2N
      );
  }
  MrcWriteCR (MrcData, OffsetMrCommand, MrCommand.Data);

  //
  // Wait till MRH is done sending the command
  //
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout
  do {
    MrCommand.Data = MrcReadCR (MrcData, OffsetMrCommand);
    Busy           = (MrCommand.Bits.Busy == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out sending MRH command!\n");
    return mrcDeviceBusy;
  }

  if (ChipSelect2N) {
    //
    // Disable 2N stretch mode for CS
    //
    ScGsCfg.Bits.LPDDR_2N_CS_MRW = 0;
    MrcWriteCR (MrcData, OffsetGsCfg, ScGsCfg.Data);
  }

  return mrcSuccess;
}

/**
  Issue LPDDR MRR (Mode Register Read) command using MRH (Mode Register Handler).
  Use DQ mapping array to deswizzle the MR data.

  @param[in]  MrcData - Include all MRC global data.
  @param[in]  Channel - the channel to work on
  @param[in]  Rank    - the rank to work on
  @param[in]  Address - MRR address
  @param[out] Data    - MRR Data array per SDRAM device

  @retval mrcSuccess    - MRR was executed successfully
  @retval mrcDeviceBusy - timed out waiting for MRH
**/
MrcStatus
MrcIssueMrr (
  IN MrcParameters *const MrcData,
  IN UINT32               Channel,
  IN UINT32               Rank,
  IN UINT32               Address,
  OUT UINT8               Data[4]
  )
{
  const MrcInput        *Inputs;
  MrcDebug              *Debug;
  const MRC_FUNCTION    *MrcCall;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;

  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  UINT32            OffsetMrCommand;
  UINT32            OffsetMrrResult;
  BOOLEAN           Busy;
  UINT32            CurrCpuBit;
  UINT32            CurrCpuByte;
  UINT32            CpuByteCnt;
  UINT32            DeviceCnt;
  UINT32            CurrDramBit;
  UINT32            BitVal;
  MCHBAR_CH0_CR_DDR_MR_RESULT_0_STRUCT  MrResult;
  MCHBAR_CH0_CR_DDR_MR_COMMAND_STRUCT   MrCommand;
  UINT64            Timeout;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Timeout       = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerIn  = &Inputs->Controller[0];
  ControllerOut = &Outputs->Controller[0];
  ChannelOut    = &ControllerOut->Channel[Channel];
  ChannelIn     = &ControllerIn->Channel[Channel];
  CurrCpuByte   = 0;
  MrcCall->MrcSetMem (Data, 4 * sizeof (Data[0]), 0);

  OffsetMrCommand = MCHBAR_CH0_CR_DDR_MR_COMMAND_REG +
    ((MCHBAR_CH1_CR_DDR_MR_COMMAND_REG - MCHBAR_CH0_CR_DDR_MR_COMMAND_REG) * Channel);

  OffsetMrrResult = MCHBAR_CH0_CR_DDR_MR_RESULT_0_REG +
    ((MCHBAR_CH1_CR_DDR_MR_RESULT_0_REG - MCHBAR_CH0_CR_DDR_MR_RESULT_0_REG) * Channel);

  //
  // Make sure MRH is not busy
  //
  do {
    MrCommand.Data = MrcReadCR (MrcData, OffsetMrCommand);
    Busy           = (MrCommand.Bits.Busy == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));
  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out waiting for previous MRH command to finish!\n");
    return mrcDeviceBusy;
  }

  //
  // Send the MRR
  //
  MrCommand.Bits.Address  = Address;
  MrCommand.Bits.Data     = 1; // Put non-zero data for CTE MRH checker
  MrCommand.Bits.Command  = 0; // LPDDR3: 00-MRR 01-MRW 10-Illegal 11-MRW with two cycles setup and hold
  MrCommand.Bits.Rank     = Rank;
  MrCommand.Bits.Busy     = 1;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcIssueMrr on ch %d rank %d: MR%d\n", Channel, Rank, Address);
  MrcWriteCR (MrcData, OffsetMrCommand, MrCommand.Data);

  //
  // Wait till MRH is done sending the command and getting the result
  //
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout
  do {
    MrCommand.Data = MrcReadCR (MrcData, OffsetMrCommand);
    Busy           = (MrCommand.Bits.Busy == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out sending MRH command!\n");
    return mrcDeviceBusy;
  }

  MrResult.Data = MrcReadCR (MrcData, OffsetMrrResult);

  for (DeviceCnt = 0; DeviceCnt < 4; DeviceCnt++) {
    if ((ChannelOut->Dimm[dDIMM0].SdramWidth == 32) && (1 == (DeviceCnt & 1))) {
      //
      // We only know DQ mapping for the lower 16 bits of the x32 devices
      // So we'll copy their MRR feedback to the upper bytes' place
      // Hence, we skip the odd dies for x32
      //
      Data[DeviceCnt] = Data[DeviceCnt - 1];
      continue;
    }

    //
    // Find which CPU byte is mapped to the relevant DRAM byte
    //
    for (CpuByteCnt = 0; CpuByteCnt < Outputs->SdramCount; CpuByteCnt++) {
      if ((DeviceCnt * 2) == ChannelIn->DqsMapCpu2Dram[CpuByteCnt]) {
        CurrCpuByte = CpuByteCnt;
        break;
      }
    }

    for (CurrCpuBit = 0; CurrCpuBit < MAX_BITS; CurrCpuBit++) {
      //
      // The actual DRAM bit that is connected to the current CPU DQ pin
      //
      CurrDramBit = ChannelIn->DqMapCpu2Dram[CurrCpuByte][CurrCpuBit] - 8 * (DeviceCnt * 2); // Subtract 8xDramByte

      BitVal = (MrResult.Data8[DeviceCnt] >> CurrCpuBit) & 1; // The 0/1 value that came from the DRAM bit
      Data[DeviceCnt] |= (BitVal << CurrDramBit);             // Putting the value in the correct place
    }
  }  // for DeviceCnt

  return mrcSuccess;
}

/**
  Use MRS Burst FSM to program all relevant MR registers in one quick operation.
  Can only be used on ULT/ULX (up to 2 ranks, no ECC)

  @param[in]  MrcData - Include all MRC global data.

  @retval mrcSuccess    - MRS FSM was executed successfully
  @retval mrcDeviceBusy - timed out waiting for MRH or MRS FSM
**/
MrcStatus
MrcProgramMrsFsm (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  MrcDebug              *Debug;
  const MRC_FUNCTION    *MrcCall;
  MrcOutput             *Outputs;
  BOOLEAN               Busy;
  UINT64                Timeout;
  UINT32                OffsetMrCommand;
  UINT32                OffsetMrsFsm;
  UINT8                 Channel;
  MrcStatus             Status;
  MCHBAR_CH0_CR_DDR_MR_COMMAND_STRUCT   MrCommand;
  MCHBAR_CH0_CR_MRS_FSM_RUN_STRUCT      MrsFsm;


  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;

  Status = ExitSR (MrcData); // Disable Self Refresh when using MRS FSM
  if (Status != mrcSuccess) {
    return Status;
  }

  //
  // Make sure both MRH and MRS FSM are not busy
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }

    OffsetMrCommand = MCHBAR_CH0_CR_DDR_MR_COMMAND_REG +
      (MCHBAR_CH1_CR_DDR_MR_COMMAND_REG - MCHBAR_CH0_CR_DDR_MR_COMMAND_REG) * Channel;

    OffsetMrsFsm = MCHBAR_CH0_CR_MRS_FSM_RUN_REG +
      (MCHBAR_CH1_CR_MRS_FSM_RUN_REG - MCHBAR_CH0_CR_MRS_FSM_RUN_REG) * Channel;

    Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout
    do {
      MrCommand.Data = MrcReadCR (MrcData, OffsetMrCommand);
      MrsFsm.Data    = MrcReadCR (MrcData, OffsetMrsFsm);
      Busy = (MrCommand.Bits.Busy == 1) || (MrsFsm.Bits.Run == 1);
    } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));
    if (Busy) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out waiting for previous MRH command to finish!\n");
      return mrcDeviceBusy;
    }
  }

  //
  // Start MRS FSM on both channels in parallel
  //
  MrsFsm.Data = 0;
  MrsFsm.Bits.Run = 1;
  MrcWriteCR (MrcData, MCMNTS_CR_MRS_FSM_RUN_REG, MrsFsm.Data);

  //
  // Poll for completion
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }

    OffsetMrsFsm = MCHBAR_CH0_CR_MRS_FSM_RUN_REG +
      (MCHBAR_CH1_CR_MRS_FSM_RUN_REG - MCHBAR_CH0_CR_MRS_FSM_RUN_REG) * Channel;

    Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout
    do {
      MrsFsm.Data = MrcReadCR (MrcData, OffsetMrsFsm);
      Busy = (MrsFsm.Bits.Run == 1);
    } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));
    if (Busy) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out waiting for MRS FSM finish!\n");
      return mrcDeviceBusy;
    }
  }

  EnterSR (MrcData); // Re-enable Self Refresh when done using MRS FSM

  return Status;
}

/**
  Issue LPDDR PRECHARGE ALL command using CADB.

  @param[in]  MrcData   - Include all MRC global data.
  @param[in]  Channel   - The channel to work on
  @param[in]  RankMask  - The rank(s) to work on

**/
void
MrcIssuePrechargeAll (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          RankMask
  )
{
  UINT32 CaHigh;
  UINT32 CaLow;
  UINT32 CMD;
  UINT32 BA;
  UINT32 MA;

  CaHigh = 0x1B;
  CaLow  = 0;

  MrcConvertLpddr2Ddr (CaHigh, CaLow, &MA, &BA, &CMD);

  //  MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "MA: 0x%X, BA: 0x%X, CMD: 0x%X\n", MA, BA, CMD);

  MrcWriteCADBCmd (MrcData, Channel, RankMask, (UINT8) CMD, (UINT8) BA, (UINT16 *) &MA, 0);
}

#if (SUPPORT_DDR4 == SUPPORT)
/**
  Issue DDR4 MRS command (PDA Mode)

  @param[in]  MrcData   - Include all MRC global data.
  @param[in]  Channel   - Channel to send MRS command to.
  @param[in]  Rank      - Rank to send MRS command to.
  @param[in]  Address   - MRS command value.
  @param[in]  MR        - Which MR command to send.
  @param[in]  DeviceMask- Which set(s) of 8 DQs to set to low for PDA mode.
  @param[in]  PDAmode   - Whether in PDA mode or not.

  @retval mrcSuccess    - PDA command was sent successfully
  @retval mrcDeviceBusy - Timed out waiting for MRH
**/
MrcStatus
MrcDdr4PdaCmd (
  IN MrcParameters *const MrcData,
  IN UINT32               Channel,
  IN UINT32               Rank,
  IN UINT16               Address,
  IN UINT8                MR,
  IN UINT16               DeviceMask,
  IN BOOLEAN              PDAmode
  )
{
  const MRC_FUNCTION                    *MrcCall;
  MrcDebug                              *Debug;
  MrcOutput                             *Outputs;
  UINT32                                Offset;
  MCHBAR_CH0_CR_DDR_MR_COMMAND_STRUCT MrCommand;
  BOOLEAN                               Busy;
  UINT8                                 Data;
  UINT8                                 MrCmdAdd;
  UINT64                                Timeout;

  MrcCall = MrcData->Inputs.Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout

  Offset = MCHBAR_CH0_CR_DDR_MR_COMMAND_REG +
    ((MCHBAR_CH1_CR_DDR_MR_COMMAND_REG - MCHBAR_CH0_CR_DDR_MR_COMMAND_REG) * Channel);

  //
  // Make sure MRH is not busy
  //
  do {
    MrCommand.Data = MrcReadCR (MrcData, Offset);
    Busy           = (MrCommand.Bits.Busy == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));
  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out waiting for previous MRH command to finish!\n");
    return mrcDeviceBusy;
  }

  Data = (Address & 0xFF);
  MrCmdAdd = ((UINT8) ((Address & 0x1F00) >> 5)) | (MR & 0x7); //(MR & 0xFF);

  //
  // Send the PDA command
  //
  MrCommand.Data                 = 0;
  MrCommand.Bits.Data            = Data;
  MrCommand.Bits.Address         = MrCmdAdd;
  MrCommand.Bits.Rank            = Rank;
  MrCommand.Bits.Busy            = 1;
  MrCommand.Bits.DRAM_mask       = 0x1FF & (~DeviceMask); // 0 - for device enable
  MrCommand.Bits.Command         = 2; // Per DRAM addressability mode (PDA)
  MrCommand.Bits.Assume_idle     = 0;
  MrCommand.Bits.DDR4_MA13       = 0;
  MrcWriteCR (MrcData, Offset, MrCommand.Data);

  //
  // Wait till MRH is done sending the command
  //
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout
  do {
    MrCommand.Data = MrcReadCR (MrcData, Offset);
    Busy           = (MrCommand.Bits.Busy == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out sending MRH command!\n");
    return mrcDeviceBusy;
  }

  return mrcSuccess;
}

/**
  Offset to DDR4 VrefDQ Range/Value (MR6)

  @param[in]  MrcData  - Include all MRC global data.
  @param[in]  Offset   - Value to be converted to actual VrefDQ Range/Value.
  @param[in]  Channel  - Channel to be converted

  @retval DDR4 VrefDQ Range/Value
**/
UINT8
MrcOffsetToVrefDq (
  IN MrcParameters *const MrcData,
  IN INT8                 Offset,
  IN UINT8                Channel
  )
{
  MrcIntOutput        *IntOutputs;
  MrcIntControllerOut *IntControllerOut;
  static const INT8   MaxVrefOffsetRange1 = MAX_POSSIBLE_DDR4_WRITE_VREF;
  static const INT8   MinVrefOffsetRange1 = MIN_DDR4_WRITE_VREF_RANGE1;
  static const INT8   MaxVrefOffsetRange2 = MAX_DDR4_WRITE_VREF_RANGE2;
  static const INT8   MinVrefOffsetRange2 = -1 * MAX_POSSIBLE_DDR4_WRITE_VREF;
  INT8                MaxVrefOffset;
  INT8                MinVrefOffset;
  UINT8               VrefDQ;  //Bit6 Range, Bit5:0 Value
  UINT8               Range;

  IntOutputs = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];
  Range = IntControllerOut->Channel[Channel].Ddr4TxDrVefRange;

  if (Range == 1) {
    MaxVrefOffset = MaxVrefOffsetRange1;
    MinVrefOffset = MinVrefOffsetRange1;
  } else if (Range == 2) {
    MaxVrefOffset = MaxVrefOffsetRange2;
    MinVrefOffset = MinVrefOffsetRange2;
  } else {
    MaxVrefOffset = MAX_POSSIBLE_DDR4_WRITE_VREF;
    MinVrefOffset = -1 * MAX_POSSIBLE_DDR4_WRITE_VREF;
  }

  if ((Offset > MaxVrefOffset) || (Offset < MinVrefOffset)) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_ERROR,
      "ERROR Invalid Vref Setting %d is out of range [%d:%d]. Clamping\n",
      Offset,
      MinVrefOffset,
      MaxVrefOffset
      );
    if (Offset > (MaxVrefOffset)) {
      Offset = MaxVrefOffset;
    } else {
      Offset = MinVrefOffset;
    }
  } 
  Offset += 13;

  if (Range == 1) {
    VrefDQ = Offset;
  } else if (Range == 2) {
    VrefDQ = Offset - 41;
  } else { // Default Range = 0
    if (Offset < 0) {
      VrefDQ = Offset - 41;
    } else {
      VrefDQ = Offset;
    }
  }

  return VrefDQ;
}

/**
  DDR4 VrefDQ Range/Value (MR6) to Offset

  @param[in]  VrefDQ   - VrefDQ Range/Value to be converted back to corresponding Offset value.

  @retval Offset
**/
INT8
MrcVrefDqToOffset (
  IN UINT8                VrefDQ
  )
{
  INT8  Offset;

  // move to -23 to 50 range
  Offset = (INT8) MrcSE (VrefDQ, 7, 8);
  if (Offset < 0) {
    Offset = Offset + 41;
  }
  if (Offset > 50) {
    Offset = 50;
  } else if (Offset < -23) {
    Offset = -23;
  }
  Offset -= 13; // so offset 0 is middle of range -36 +37

  return Offset;
}

#endif // SUPPORT_DDR4

/**
  Setup for using Set B Latency (Read and Write) for LPDDR3

  @param[in]  MrcData   - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcLpddrLatencySetB (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput    *Inputs;
  MrcStatus         Status;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  UINT8             Channel;
  UINT8             Rank;
  BOOLEAN           SavedRestoreMRS;
  BOOLEAN           DifferentCWL;
  MrcProfile        Profile;
  MrcFrequency      DdrFreq;
  UINT8             MrrResult[4];
  UINT8             Device;
  UINT8             WLSetBSupport;
  UINT8             CasWriteLatency;

  Inputs           = &MrcData->Inputs;
  Outputs          = &MrcData->Outputs;
  ControllerOut    = &Outputs->Controller[0];
  Debug            = &Outputs->Debug;

  if (Outputs->LpddrWLUpdated == FALSE) {
    // Save the flag and force MRS recalculation
    SavedRestoreMRS     = Outputs->RestoreMRs;
    Outputs->RestoreMRs = FALSE;

    DdrFreq             = Outputs->Frequency;
    WLSetBSupport       = 0xFF;
    Profile             = Inputs->MemoryProfile;

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        //
        // MR0 bit [6] - WL Set B support
        //
        MrcIssueMrr (MrcData, Channel, Rank, 0, MrrResult);
        for (Device = 0; Device < (sizeof (MrrResult) / sizeof (MrrResult[0])); Device++) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tDevice[%d].MR0= 0x%02X - WL Set B %ssupported\n", Device, MrrResult[Device],
            (MRC_BIT6 & MrrResult[Device]) ? "" : "not ");
          WLSetBSupport &= (MRC_BIT6 & MrrResult[Device]);
        }
      }
    }
    Outputs->LpddrMemWriteLatencySet = Inputs->LpddrMemWriteLatencySet & (WLSetBSupport >> 6);

    if (Outputs->LpddrMemWriteLatencySet) {
      DifferentCWL = FALSE;
      //
      // WL Set B from MR2 spec, adding 1 to take tDQSS into account.
      // We will subtract this 1 when programming TC_ODT.tCWL
      //
      // At 1067 the TC_ODT.tCWL must be at least 5 on SKL,
      // so we start from RL=9 / WL=5 option in MR2 WL Set B (f1200).
      //
      // We will decrement WL on MC, so start from RL=10 / WL=8 option in MR2 WL Set B (f1333).
      //
      if (DdrFreq <= f1333) {
        CasWriteLatency = 9;  // WL = 8
      } else if (DdrFreq <= f1600) {
        CasWriteLatency = 10; // WL = 9
      } else if (DdrFreq <= f1867) {
        CasWriteLatency = 12; // WL = 11
      } else {
        CasWriteLatency = 14; // WL = 13
      }

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcChannelExist (Outputs, Channel)) {
          if (ControllerOut->Channel[Channel].Timing[Profile].tCWL != CasWriteLatency) {
            DifferentCWL = TRUE;
            ControllerOut->Channel[Channel].Timing[Profile].tCWL = CasWriteLatency;
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "LPDDR3 WL Set B used, CH %u - tCWL has been updated to %u\n",
              Channel,
              CasWriteLatency
              );
          }
        }
      }
      if (DifferentCWL) {
        MrcTimingConfiguration (MrcData);
        Status = MrcResetSequence (MrcData);
        if (Status != mrcSuccess) {
          return Status;
        }
      }
    }
    Outputs->LpddrWLUpdated = TRUE;
    // Restore flag
    Outputs->RestoreMRs     = SavedRestoreMRS;
  }

  return mrcSuccess;
}

/**
  This function ensures that DDR4 TxDq Vref Range values is the same across all ranks and bytes
  in a single channel.
  Function checks for each channel there are different ranges used. If no - nothing will happen.
  If there are different ranges it will check what is the most fitting range bit that fits all
  bytes. There should not be any need for different ranges in one channel, however if they do
  exist then it will choose the one that exceeds the range limit least.

  @param[in] MrcData         - Include all the MRC general data.


  @retval MrcStatus - Success if passed, Failure otherwise.
**/
MrcStatus
MrcTrainDdrTxDqVrefRange (
  IN MrcParameters     *const MrcData
  )
{
  MrcOutput             *Outputs;
  MrcChannelOut         *ChannelOut;
  MrcRankOut            *RankOut;
  MrcIntOutput          *IntOutputs;
  MrcIntControllerOut   *IntControllerOut;
  MrcDebug              *Debug;
  UINT8                 Channel;
  UINT8                 Rank;
  UINT8                 Byte;
  UINT8                 Range;
  INT32                 MaxOffset;
  INT32                 MinOffset;
  INT32                 ByteOffset;
  BOOLEAN               IsMixedRange;
  BOOLEAN               IsAnyMixedRange;
  MrcStatus             Status;

  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  IntOutputs        = (MrcIntOutput *)(MrcData->IntOutputs.Internal);
  IntControllerOut  = &IntOutputs->Controller[0];
  Status            = mrcSuccess;

  IsAnyMixedRange = FALSE;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    Range = 0;
    MaxOffset = -1 * MAX_POSSIBLE_DDR4_WRITE_VREF;
    MinOffset = MAX_POSSIBLE_DDR4_WRITE_VREF;
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      IsMixedRange = FALSE;
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[Rank % 2];
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Range += ((RankOut->Ddr4PdaMr6[Byte] & 0x7F) >> 6);
          ByteOffset = MrcVrefDqToOffset (RankOut->Ddr4PdaMr6[Byte] & 0x7F);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Ch%uRank%uByte%u Offset %d, Vref %u, Range %u \n", Channel, Rank, Byte, ByteOffset, (RankOut->Ddr4PdaMr6[Byte] & 0x3F), ((RankOut->Ddr4PdaMr6[Byte] & 0x7F) >> 6));
          MinOffset = MIN (MinOffset, ByteOffset);
          MaxOffset = MAX (MaxOffset, ByteOffset);
        }
        IsMixedRange    |= !((Range == 0) || (Range == Outputs->SdramCount));
        IsAnyMixedRange |= IsMixedRange;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Ch%uRank%u SumRange %u IsMixedRange %u IsAnyMixedRange %u\n", Channel, Rank, Range, IsMixedRange, IsAnyMixedRange);
      }
      if (IsMixedRange) {
        if ((MaxOffset > MAX_DDR4_WRITE_VREF_RANGE2) && (MinOffset > -1 * MAX_DDR4_WRITE_VREF_RANGE2)) {
          IntControllerOut->Channel[Channel].Ddr4TxDrVefRange = 1;
        } else if ((MaxOffset <= MAX_DDR4_WRITE_VREF_RANGE2) && (MinOffset <= -1 * MAX_DDR4_WRITE_VREF_RANGE2)) {
          IntControllerOut->Channel[Channel].Ddr4TxDrVefRange = 2;
        } else {  // (MaxOffset > -1* MAX_DDR4_WRITE_VREF_RANGE2) && (MinOffset < -1 * MAX_DDR4_WRITE_VREF_RANGE2)
          IntControllerOut->Channel[Channel].Ddr4TxDrVefRange = ((MaxOffset - MAX_DDR4_WRITE_VREF_RANGE2) > (-1 * MAX_DDR4_WRITE_VREF_RANGE2 - MinOffset)) ? 2 : 1;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Got extremely high difference between Bytes Truncating to offsets in Range %u\n", IntControllerOut->Channel[Channel].Ddr4TxDrVefRange - 1);
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Ch%u overriding Range to %u \n", Channel, IntControllerOut->Channel[Channel].Ddr4TxDrVefRange - 1);
      }
    }
  }

  if (IsAnyMixedRange) {
    Status = ChangeMargin (MrcData, WrV, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        ChannelOut = &Outputs->Controller[0].Channel[Channel];
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
            continue;
          }
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            Status = ChangeMargin (MrcData, WrV, 0, 0, 0, Channel, 1 << Rank, 1 << Byte, 0, TRUE, 0, 0);
          }
        }
      }
    }
  }
  return Status;
}
