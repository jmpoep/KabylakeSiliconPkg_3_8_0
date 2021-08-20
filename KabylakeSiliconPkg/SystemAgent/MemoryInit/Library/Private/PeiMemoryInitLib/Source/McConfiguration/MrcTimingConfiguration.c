/** @file
  This module configures the memory controller timing parameters.

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
#include "MrcTimingConfiguration.h"

/**
  This function returns the tCKE value for the specified frequency.

  @param[in] DdrType    - DDR type
  @param[in] Frequency  - The memory frequency.
  @param[in] tCK        - DCLK period in femtoseconds.

  @retval The tCKE value for the specified frequency.
**/
static
UINT32
tCKEValue (
  IN MrcDdrType         DdrType,
  IN const MrcFrequency Frequency,
  IN UINT32             tCK
  )
{
  UINT32 tCKE;

#if (SUPPORT_LPDDR3 == SUPPORT)
    if (DdrType == MRC_DDR_TYPE_LPDDR3) {
    return DIVIDECEIL (tCKE_LPDDR_FS, tCK);
  }
#endif // SUPPORT_LPDDR3

  if (Frequency <= f800) {
    tCKE = TCKE_800;
  } else if (Frequency <= f1067) {
    tCKE = TCKE_1067;
  } else if (Frequency <= f1333) {
    tCKE = TCKE_1333;
  } else if (Frequency <= f1600) {
    tCKE = TCKE_1600;
  } else if (Frequency <= f1867) {
    tCKE = TCKE_1867;
  } else if (Frequency <= f2133) {
    tCKE = TCKE_2133;
  } else if (Frequency <= f2400) {
    tCKE = TCKE_2400;
  } else if (Frequency <= f2667) {
    tCKE = TCKE_2667;
  } else if (Frequency <= f2800) {
    tCKE = TCKE_2800;
  } else if (Frequency <= f2933) {
    tCKE = TCKE_2933;
  } else if (Frequency <= f3000) {
    tCKE = TCKE_3000;
  } else {
    tCKE = TCKE_3200;
  }

  return tCKE;
}

/**
  This function returns the tXPDLL value for the specified frequency.

  @param[in] tCK        - DCLK period in femtoseconds.

  @retval The tXPDLL value for the specified frequency.
**/
static
UINT32
tXPDLLValue (
  IN UINT32  tCK
  )
{
  return DIVIDECEIL (tXPDLL_FS, tCK);
}

/**
  This function returns the tXP value for the specified frequency.

  @param[in] DdrType   - DDR type
  @param[in] Frequency - The memory frequency.
  @param[in] tCK       - DCLK period in femtoseconds.
  @param[in] NMode     - Command mode to lookup.

  @retval The tXP value for the specified frequency.
**/
UINT32
tXPValue (
  IN MrcDdrType         DdrType,
  IN const MrcFrequency Frequency,
  IN UINT32             tCK,
  IN UINT8              NMode
  )
{
  UINT32 tXP;

  if (DdrType == MRC_DDR_TYPE_LPDDR3) {
    tXP = DIVIDECEIL (tXP_LPDDR_FS, tCK);
  } else if (DdrType == MRC_DDR_TYPE_DDR4) {
    if (Frequency <= f1600) {
      tXP = tXP_DDR4_1600;
    } else if (Frequency <= f1867) {
      tXP = tXP_DDR4_1867;
    } else if (Frequency <= f2133) {
      tXP = tXP_DDR4_2133;
    } else {
      tXP = MC_tXP_MAX;
    }
  } else {
    if (Frequency <= f1600) {
      tXP = ((MC_tXP_1600_1N - 1) + NMode);
    } else if (Frequency <= f1867) {
      tXP = ((NMode <= 2) ? MC_tXP_1867_2N : MC_tXP_1867_3N);
    } else if (Frequency <= f2133) {
      tXP = (MC_tXP_2133_1N);
    } else {
      tXP = MC_tXP_MAX;
    }
  }
  return (tXP);
}

/**
  This function returns the tAONPD value for the specified frequency.

  @param[in] tCK       - DCLK period in femtoseconds.

  @retval The tAONPD value for the specified frequency.
**/
static
UINT32
tAONPDValue (
  IN UINT32  tCK
  )
{
  return DIVIDECEIL (tAONPD_FS, tCK);
}

/**
  This function sets up the following MC Timing
  registers: TC_PRE, TC_ACT, TC_ODT

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Channel - Channel select.

  @retval Nothing.

**/
static
void
SetTcPreActOdt (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32         Channel
  )
{
  const MrcInput                *Inputs;
  MrcDebug                      *Debug;
  MrcOutput                     *Outputs;
  MrcIntOutput                  *MrcIntData;
  MrcIntChannelOut              *IntChannelOut;
  MrcChannelOut                 *ChannelOut;
  MrcTiming                     *Timing;
  MrcDdrType                    DdrType;
  MCHBAR_CH0_CR_TC_PRE_STRUCT   TcPre;
  MCHBAR_CH0_CR_TC_ACT_STRUCT   TcAct;
  MCHBAR_CH0_CR_TC_ODT_STRUCT   TcOdt;
  UINT32                        tWRPRE;
  UINT32                        tRP;
  UINT32                        tCWL;
  UINT32                        tAONPD;
  UINT32                        OdtWriteDelay;
  UINT32                        OdtWriteDuration;
  UINT32                        DclkPs;
  BOOLEAN                       DtHalo;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  Timing      = &ChannelOut->Timing[Inputs->MemoryProfile];
  DdrType     = Outputs->DdrType;
  DtHalo      = (Inputs->CpuModel == cmKBL_DT_HALO);

  TcPre.Data = 0;
  TcAct.Data = 0;
  TcOdt.Data = 0;

  //
  // tRP is equal to tRCD on SKL
  //
  tRP = Timing->tRCDtRP;

  //
  // tWRPRE is = 4tCK + tWR + tCWL
  //
  tWRPRE = 4 + Timing->tWR + Timing->tCWL;

  TcPre.Bits.tRP     = RANGE (tRP, tRP_MIN, tRP_MAX);
  if (DdrType == MRC_DDR_TYPE_LPDDR3) {
    TcPre.Bits.tRPab_ext = MIN (MCHBAR_CH0_CR_TC_PRE_tRPab_ext_MAX, Timing->tRPab - tRP);
  }
  TcPre.Bits.tRAS    = RANGE (Timing->tRAS, tRAS_MIN, tRAS_MAX);
  TcPre.Bits.tRDPRE  = RANGE (Timing->tRTP, tRDPRE_MIN, tRDPRE_MAX);
  TcPre.Bits.tWRPRE  = RANGE (tWRPRE, tWRPRE_MIN, tWRPRE_MAX);

  TcAct.Bits.tFAW    = RANGE (Timing->tFAW, tFAW_MIN, tFAW_MAX);

  if (DdrType == MRC_DDR_TYPE_DDR4) {
    TcAct.Bits.tRRD_sg = RANGE (Timing->tRRD_L, tRRD_MIN, tRRD_MAX);
    TcAct.Bits.tRRD_dg = RANGE (Timing->tRRD_S, tRRD_MIN, tRRD_MAX);
  } else {
    TcAct.Bits.tRRD_sg = RANGE (Timing->tRRD,   tRRD_MIN, tRRD_MAX);
    TcAct.Bits.tRRD_dg = RANGE (Timing->tRRD,   tRRD_MIN, tRRD_MAX);
  }

  TcAct.Bits.derating_ext = 2;

  TcOdt.Bits.tCL = RANGE (Timing->tCL, tCL_MIN, tCL_MAX);

  tCWL = Timing->tCWL;

  //
  // Subtract one clock to increase Write FIFO separation
  //
  tCWL--;

  if (DdrType == MRC_DDR_TYPE_LPDDR3) {
    if (Outputs->LpddrDramOdt) {
      //
      // ODT[0] is used for both ranks on LPDDR3
      //
      TcOdt.Bits.ODT_Always_Rank0 = 1;
    }

    //
    // Timing->tCWL has 1 extra clock because of tDQSS - subtract it here.
    //
    tCWL--;

    DclkPs = Outputs->Qclkps * 2;

    //
    // Odt_Write_Delay = WL - 1 - RU(tODTon(max))
    //
    OdtWriteDelay = Timing->tCWL - 1 - DIVIDECEIL (tODT_ON_MAX, DclkPs);
    TcOdt.Bits.ODT_Write_Delay = MIN (OdtWriteDelay, MCHBAR_CH0_CR_TC_ODT_ODT_Write_Delay_MAX);

     //
    // Odt_Write_Duration = 6 + RU(tODTon(max)-tODToff(min)) - 6 + 1 + OdtWriteDelay register max size compensation
    //
    if (Outputs->LpddrDramOdt) {
      OdtWriteDuration = 1 + DIVIDECEIL (tODT_ON_MAX - tODT_OFF_MIN, DclkPs) + ((OdtWriteDelay > MCHBAR_CH0_CR_TC_ODT_ODT_Write_Delay_MAX) ? (OdtWriteDelay - MCHBAR_CH0_CR_TC_ODT_ODT_Write_Delay_MAX) : 0);
    } else {
      OdtWriteDuration = 0;
    }

    TcOdt.Bits.ODT_write_duration = MIN (OdtWriteDuration, MCHBAR_CH0_CR_TC_ODT_ODT_write_duration_MAX);
  }

  if ((DdrType == MRC_DDR_TYPE_DDR4) && (DtHalo)) {
    OdtWriteDuration = 1;
    TcOdt.Bits.ODT_write_duration = MIN (OdtWriteDuration, MCHBAR_CH0_CR_TC_ODT_ODT_write_duration_MAX);
  }

  TcOdt.Bits.tCWL = RANGE (tCWL, tCWL_MIN, tCWL_MAX);
  TcOdt.Bits.ODT_Read_Delay = MIN (Timing->tCL - Timing->tCWL, MCHBAR_CH0_CR_TC_ODT_ODT_Read_Delay_MAX);
  TcOdt.Bits.Write_Early_ODT = 0;  // TODO: check on 2dpc

  tAONPD = tAONPDValue (Timing->tCK);
  TcOdt.Bits.tAONPD = MIN (tAONPD, MCHBAR_CH0_CR_TC_ODT_tAONPD_MAX);

  MrcWriteCR (
    MrcData,
    MCHBAR_CH0_CR_TC_PRE_REG + ((MCHBAR_CH1_CR_TC_PRE_REG - MCHBAR_CH0_CR_TC_PRE_REG) * Channel),
    TcPre.Data
    );

  MrcWriteCR (
    MrcData,
    MCHBAR_CH0_CR_TC_ACT_REG + ((MCHBAR_CH1_CR_TC_ACT_REG - MCHBAR_CH0_CR_TC_ACT_REG) * Channel),
    TcAct.Data
    );

  MrcWriteCR (
    MrcData,
    MCHBAR_CH0_CR_TC_ODT_REG + ((MCHBAR_CH1_CR_TC_ODT_REG - MCHBAR_CH0_CR_TC_ODT_REG) * Channel),
    TcOdt.Data
    );

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Ch%u: TC_PRE = %Xh\n tRCD = tRP = %u\n tRPab_ext = %u\n tRAS = %u\n tRDPRE = %u\n tWRPRE = %u\n",
    Channel,
    TcPre.Data,
    TcPre.Bits.tRP,
    TcPre.Bits.tRPab_ext,
    TcPre.Bits.tRAS,
    TcPre.Bits.tRDPRE,
    TcPre.Bits.tWRPRE
    );

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Ch%u: TC_ACT = %Xh\n tFAW = %u\n tRRD_sg = %u\n tRRD_dg = %u\n derating_ext = %u\n",
    Channel,
    TcAct.Data,
    TcAct.Bits.tFAW,
    TcAct.Bits.tRRD_sg,
    TcAct.Bits.tRRD_dg,
    TcAct.Bits.derating_ext
    );

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Ch%u: TC_ODT = %Xh\n ODT_read_duration = %u\n ODT_Read_Delay = %u\n ODT_write_duration = %u\n",
    Channel,
    TcOdt.Data,
    TcOdt.Bits.ODT_read_duration,
    TcOdt.Bits.ODT_Read_Delay,
    TcOdt.Bits.ODT_write_duration
    );

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    " ODT_Write_Delay=%u\n Write_Early_ODT=%u\n tCL=%u\n tCWL=%u\n tAONPD=%u\n ODT_Always_Rank0=%u\n",
    TcOdt.Bits.ODT_Write_Delay,
    TcOdt.Bits.Write_Early_ODT,
    TcOdt.Bits.tCL,
    TcOdt.Bits.tCWL,
    TcOdt.Bits.tAONPD,
    TcOdt.Bits.ODT_Always_Rank0
    );

  //
  // Save in MrcData structure
  //
  IntChannelOut->MchbarTcPre = TcPre;
  IntChannelOut->MchbarTcAct = TcAct;
  IntChannelOut->MchbarTcOdt = TcOdt;
}

/**
  Program turnaround values from the host structure into the HW.

  @param[in] MrcData  - The MRC "global data" area.
  @param[in] Channel  - Channel select.

  @retval Nothing.
**/
void
MrcProgramTurnarounds (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  )
{
  const MrcInput                *Inputs;
  MrcDebug                      *Debug;
  MrcOutput                     *Outputs;
  MrcChannelOut                 *ChannelOut;
  MrcIntOutput                  *MrcIntData;
  MrcIntChannelOut              *IntChannelOut;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT  *TcRdRd;
  MCHBAR_CH0_CR_TC_RDWR_STRUCT  *TcRdWr;
  MCHBAR_CH0_CR_TC_WRRD_STRUCT  *TcWrRd;
  MCHBAR_CH0_CR_TC_WRWR_STRUCT  *TcWrWr;
  UINT32                        Offset;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];

  TcRdRd = &IntChannelOut->MchbarTcRdRd;
  TcRdWr = &IntChannelOut->MchbarTcRdWr;
  TcWrRd = &IntChannelOut->MchbarTcWrRd;
  TcWrWr = &IntChannelOut->MchbarTcWrWr;

  Offset = MCHBAR_CH0_CR_TC_RDRD_REG + (MCHBAR_CH1_CR_TC_RDRD_REG - MCHBAR_CH0_CR_TC_RDRD_REG) * Channel;
  MrcWriteCR (MrcData, Offset, TcRdRd->Data);

  Offset = MCHBAR_CH0_CR_TC_RDWR_REG + (MCHBAR_CH1_CR_TC_RDWR_REG - MCHBAR_CH0_CR_TC_RDWR_REG) * Channel;
  MrcWriteCR (MrcData, Offset, TcRdWr->Data);

  Offset = MCHBAR_CH0_CR_TC_WRRD_REG + (MCHBAR_CH1_CR_TC_WRRD_REG - MCHBAR_CH0_CR_TC_WRRD_REG) * Channel;
  MrcWriteCR (MrcData, Offset, TcWrRd->Data);

  Offset = MCHBAR_CH0_CR_TC_WRWR_REG + (MCHBAR_CH1_CR_TC_WRWR_REG - MCHBAR_CH0_CR_TC_WRWR_REG) * Channel;
  MrcWriteCR (MrcData, Offset, TcWrWr->Data);

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Ch%u: TC_RDRD = %Xh\n tRDRD_sg = %u\n tRDRD_dg = %u\n tRDRD_dr = %u\n tRDRD_dd = %u\n",
    Channel,
    TcRdRd->Data,
    TcRdRd->Bits.tRDRD_sg,
    TcRdRd->Bits.tRDRD_dg,
    TcRdRd->Bits.tRDRD_dr,
    TcRdRd->Bits.tRDRD_dd
    );

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Ch%u: TC_RDWR = %Xh\n tRDWR_sg = %u\n tRDWR_dg = %u\n tRDWR_dr = %u\n tRDWR_dd = %u\n",
    Channel,
    TcRdWr->Data,
    TcRdWr->Bits.tRDWR_sg,
    TcRdWr->Bits.tRDWR_dg,
    TcRdWr->Bits.tRDWR_dr,
    TcRdWr->Bits.tRDWR_dd
    );

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Ch%u: TC_WRRD = %Xh\n tWRRD_sg = %u\n tWRRD_dg = %u\n tWRRD_dr = %u\n tWRRD_dd = %u\n",
    Channel,
    TcWrRd->Data,
    TcWrRd->Bits.tWRRD_sg,
    TcWrRd->Bits.tWRRD_dg,
    TcWrRd->Bits.tWRRD_dr,
    TcWrRd->Bits.tWRRD_dd
    );

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Ch%u: TC_WRWR = %Xh\n tWRWR_sg = %u\n tWRWR_dg = %u\n tWRWR_dr = %u\n tWRWR_dd = %u\n",
    Channel,
    TcWrWr->Data,
    TcWrWr->Bits.tWRWR_sg,
    TcWrWr->Bits.tWRWR_dg,
    TcWrWr->Bits.tWRWR_dr,
    TcWrWr->Bits.tWRWR_dd
    );
}

/**
  This function sets up the Turnaround timing registers:
  TC_RDRD, TC_RDWR, TC_WRRD and TC_WRWR.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Channel - Channel select.

  @retval Nothing.
**/
static
void
SetTcTurnAround (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32         Channel
  )
{
  const MrcInput                *Inputs;
  MrcDebug                      *Debug;
  MrcOutput                     *Outputs;
  MrcIntOutput                  *MrcIntData;
  MrcIntChannelOut              *IntChannelOut;
  MrcChannelOut                 *ChannelOut;
  MrcTiming                     *Timing;
  MrcFrequency                  DdrFreq;
  MrcDdrType                    DdrType;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT  TcRdRd;
  MCHBAR_CH0_CR_TC_RDWR_STRUCT  TcRdWr;
  MCHBAR_CH0_CR_TC_WRRD_STRUCT  TcWrRd;
  MCHBAR_CH0_CR_TC_WRWR_STRUCT  TcWrWr;
  UINT32                        Value;
  UINT32                        tWTR_L;
  UINT32                        tWTR_S;
  UINT32                        DclkPs;
  UINT32                        tWRRD_dr;
  UINT32                        tCCD_L;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  Timing      = &ChannelOut->Timing[Inputs->MemoryProfile];
  DdrType     = Outputs->DdrType;
  DdrFreq     = Outputs->Frequency;

  TcRdRd.Data = 0;
  TcRdWr.Data = 0;
  TcWrRd.Data = 0;
  TcWrWr.Data = 0;

  //-----------------------------------
  // Calculate tRDRD
  //-----------------------------------
  if (DdrType == MRC_DDR_TYPE_DDR4) {
    //
    // Use tCCD_L for tRDRD_sg
    // Use tCCD_S for tRDRD_dg
    //
    if (DdrFreq <= f1333) {
      tCCD_L = tCCD_L_1333_AND_LOWER;
    } else if (DdrFreq <= f1867) {
      tCCD_L = tCCD_L_1867;
    } else if (DdrFreq <= f2400) {
      tCCD_L = tCCD_L_2400;
    } else {
      tCCD_L = tCCD_L_ABOVE_2400;
    }
  } else {
    tCCD_L = TCCD_ALL_FREQ;
  }

  TcRdRd.Bits.tRDRD_sg = MIN (tCCD_L, tRDRD_MAX);
  TcRdRd.Bits.tRDRD_dg = MIN (TCCD_ALL_FREQ, tRDRD_MAX);

  //
  // Calculate tRDRD_dr = BL/2 + max(tRTR, ODT(R,R,DR)) + tRPRE
  //
  Value = 4 + 1 + TRPRE_ALL_FREQ;

  if (DdrType == MRC_DDR_TYPE_LPDDR3) {
    //
    // Increase tRDRD_dr from 6 to 7 DCLKs on LPDDR3
    //
    Value++;
  }

  TcRdRd.Bits.tRDRD_dr = MIN (Value, tRDRD_MAX);

  //
  // Calculate tRDRD_dd = BL/2 + max(tRTR, ODT(R,R,DD)) + tRPRE
  //
  TcRdRd.Bits.tRDRD_dd = MIN (Value + 1, tRDRD_MAX);

  //-----------------------------------
  // Calculate tRDWR = tCL-tCWL+tCCD+tWPRE+max(tRWSR,ODT(R,W,SR))
  // tWPRE - Write Preamble
  //-----------------------------------
  Value = Timing->tCL - Timing->tCWL + TCCD_ALL_FREQ + TWPRE_ALL_FREQ + 2;
  //
  // Add 1 for frequencies above 1067.
  //
  if (Outputs->Frequency > f1067) {
    Value++;
  }

  //
  // Add 1 for frequencies above 1600.
  //
  if (Outputs->Frequency > f1600) {
    Value++;
  }

  DclkPs = Outputs->Qclkps * 2;

  if (DdrType == MRC_DDR_TYPE_LPDDR3) {
    //
    // tRDWR = tCL - tCWL + tDQSCK_max + tCCD + tWPRE + ElectricalTurnaround
    //
    Value = Timing->tCL - Timing->tCWL + DIVIDECEIL (tDQSCK_MAX, DclkPs) + TCCD_ALL_FREQ + TWPRE_ALL_FREQ + 1;
  }

  TcRdWr.Bits.tRDWR_sg = MIN (Value, tRDWR_MAX);
  TcRdWr.Bits.tRDWR_dg = MIN (Value, tRDWR_MAX);

  //
  // Calculate tRDWR_dr = tCL-tCWL+tCCD+tWPRE+max(tRWDR,ODT(R,W,DR))
  //
  TcRdWr.Bits.tRDWR_dr = MIN (Value, tRDWR_MAX);

  //
  // Calculate tRDWR_dd = tCL-tCWL+tCCD+tWPRE+max(tRWDD,ODT(R,W,DD))
  //
  TcRdWr.Bits.tRDWR_dd = MIN (Value + 1, tRDWR_MAX);

  //-----------------------------------
  // Calculate tWRRD = tCWL + BL/2 + tWTR + max(tWrCAS2RdCAS_sr,ODT(W,R,SR)).
  //-----------------------------------

  if (DdrType == MRC_DDR_TYPE_DDR4) {
    tWTR_S = Timing->tWTR_S;
    tWTR_L = Timing->tWTR_L;
  } else {
    tWTR_S = tWTR_L = Timing->tWTR;
  }
  Value = Timing->tCWL + 4 + tWTR_L + 2;
  TcWrRd.Bits.tWRRD_sg = MIN (Value, tWRRD_SG_MAX);

  Value = Timing->tCWL + 4 + tWTR_S + 2;
  TcWrRd.Bits.tWRRD_dg = MIN (Value, tWRRD_MAX);

  //
  // Calculate tWRRD_dr = tCWL - tCL + BL/2 + max(tWRDRDR,ODT(W,R,DR)) + tRPRE
  //
  tWRRD_dr = Timing->tCWL - Timing->tCL + 4 + 2 + TRPRE_ALL_FREQ;

  if (DdrType == MRC_DDR_TYPE_LPDDR3) {
    //
    // tWRRD_dr is 8 for all LPDDR bins
    //
    tWRRD_dr = 8;
  }

  tWRRD_dr = MIN (tWRRD_dr, tWRRD_MAX);
  tWRRD_dr = MAX (tWRRD_dr, 4);
  TcWrRd.Bits.tWRRD_dr = tWRRD_dr;

  //
  // Calculate tWRRD_dd = tCWL - tCL + BL/2 + max(tWRDRDD,ODT(W,R,DD)) + tRPRE
  //
  TcWrRd.Bits.tWRRD_dd = tWRRD_dr;

  //-----------------------------------
  // Calculate tWRWR
  //-----------------------------------
  TcWrWr.Bits.tWRWR_sg = MIN (tCCD_L, tWRWR_MAX);
  TcWrWr.Bits.tWRWR_dg = MIN (TCCD_ALL_FREQ, tWRWR_MAX);

  //
  // Calculate tWRWR_dr = BL/2 + max(tWWDR,ODT(W,W,DR)) + tWPRE
  //
  Value = 4 + 2 + TWPRE_ALL_FREQ;
  if ((DdrType == MRC_DDR_TYPE_LPDDR3) && Outputs->LpddrDramOdt) {
    Value += 2;  // Need 2 more DCLKs so that Write ODT won't overlap between ranks
  }
  TcWrWr.Bits.tWRWR_dr = MIN (Value, tWRWR_MAX);

  //
  // Calculate tWRWR_dd = BL/2 + max(tWWDD,ODT(W,W,DR)) + tWPRE
  //
  TcWrWr.Bits.tWRWR_dd = MIN (Value, tWRWR_MAX);


  //
  // Save in MrcData structure
  //
  IntChannelOut->MchbarTcRdRd = TcRdRd;
  IntChannelOut->MchbarTcRdWr = TcRdWr;
  IntChannelOut->MchbarTcWrRd = TcWrRd;
  IntChannelOut->MchbarTcWrWr = TcWrWr;

  //
  // Write the values to the hardware
  //
  MrcProgramTurnarounds (MrcData, Channel);
}

/**
  This function sets up the TC_PWRDN register.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Channel - Channel select.

  @retval Nothing.
**/
static
void
SetTcPwrdwn (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32         Channel
  )
{
  const MrcInput                *Inputs;
  MrcDebug                      *Debug;
  MrcOutput                     *Outputs;
  MrcChannelOut                 *ChannelOut;
  MrcTiming                     *Timing;
  MrcDdrType                    DdrType;
  MrcFrequency                  DdrFreq;
  MCHBAR_CH0_CR_TC_PWRDN_STRUCT TcPwrdn;
  UINT32                        tCK;
  UINT32                        Value;
  UINT32                        DclkPs;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  Timing      = &ChannelOut->Timing[Inputs->MemoryProfile];
  DdrType     = Outputs->DdrType;
  DdrFreq     = Outputs->Frequency;
  tCK         = Timing->tCK;
  DclkPs      = Outputs->Qclkps * 2;

  TcPwrdn.Data = 0;

  Value = tCKEValue (DdrType, DdrFreq, tCK);
  TcPwrdn.Bits.tCKE = RANGE (Value, tCKE_MIN, tCKE_MAX);

  Value = tXPValue (DdrType, DdrFreq, tCK, 3);
  TcPwrdn.Bits.tXP = RANGE (Value, tXP_MIN, tXP_MAX);

  Value = tXPDLLValue (tCK);
  TcPwrdn.Bits.tXPDLL = RANGE (Value, tXPDLL_MIN, tXPDLL_MAX);

  TcPwrdn.Bits.tPRPDEN = (DdrFreq < f2133) ? 1 : 2;

  //
  // Calculate tRDPDEN = tCL + BL/2 +1
  //
  Value = Timing->tCL + 5;
  if (DdrType == MRC_DDR_TYPE_LPDDR3) {
    Value += DIVIDECEIL (tDQSCK_MAX, DclkPs);
  }
  TcPwrdn.Bits.tRDPDEN = RANGE (Value, tRDPDEN_MIN, tRDPDEN_MAX);

  //
  // Calculate tWRPDEN = tCWL + BL/2 + tWR
  //
  Value = Timing->tWR + Timing->tCWL + 4;
  TcPwrdn.Bits.tWRPDEN = RANGE (Value, tWRPDEN_MIN, tWRPDEN_MAX);

  MrcWriteCR (
    MrcData,
    MCHBAR_CH0_CR_TC_PWRDN_REG + ((MCHBAR_CH1_CR_TC_PWRDN_REG - MCHBAR_CH0_CR_TC_PWRDN_REG) * Channel),
    TcPwrdn.Data
    );

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Ch%u: TC_PWRDN = %Xh\n tCKE = %u\n tXP = %u\n tXPDLL = %u\n",
    Channel,
    TcPwrdn.Data,
    TcPwrdn.Bits.tCKE,
    TcPwrdn.Bits.tXP,
    TcPwrdn.Bits.tXPDLL
    );

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    " tPRPDEN = %u\n tRDPDEN = %u\n tWRPDEN = %u\n",
    TcPwrdn.Bits.tPRPDEN,
    TcPwrdn.Bits.tRDPDEN,
    TcPwrdn.Bits.tWRPDEN
    );
}

/**
  This function programs the SC_WR_ADD_DELAY register.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Channel - Channel select.

  @retval Nothing.
**/
void
SetWrAddDelay (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32         Channel
  )
{
  const MrcInput                        *Inputs;
  MrcDebug                              *Debug;
  MrcOutput                             *Outputs;
  MrcChannelOut                         *ChannelOut;
  MrcIntOutput                          *MrcIntData;
  MrcIntChannelOut                      *IntChannelOut;
  MCHBAR_CH0_CR_SC_WR_ADD_DELAY_STRUCT  ScWrAddDelay;
  UINT32                                Value;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];

  //
  // Set Dec_WRD.
  // Can be set to 1 only if TC_ODT.tCWL is 7 or more.
  //
  ScWrAddDelay.Data = 0;
  if (IntChannelOut->MchbarTcOdt.Bits.tCWL >= 7) {
    ScWrAddDelay.Bits.Dec_WRD = 1;
  }

  //
  // Set sc_wr_add_delay accordingly = 1 + Dec_WRD
  //
  Value  = ScWrAddDelay.Bits.Dec_WRD + 1;
  ScWrAddDelay.Bits.D1R1  = MIN (MCHBAR_CH0_CR_SC_WR_ADD_DELAY_D1R1_MAX, Value);
  ScWrAddDelay.Bits.D1R0  = MIN (MCHBAR_CH0_CR_SC_WR_ADD_DELAY_D1R0_MAX, Value);
  ScWrAddDelay.Bits.D0R1  = MIN (MCHBAR_CH0_CR_SC_WR_ADD_DELAY_D0R1_MAX, Value);
  ScWrAddDelay.Bits.D0R0  = MIN (MCHBAR_CH0_CR_SC_WR_ADD_DELAY_D0R0_MAX, Value);
  MrcWriteCR (
    MrcData,
    MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG +
    (MCHBAR_CH1_CR_SC_WR_ADD_DELAY_REG - MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG) * Channel,
    ScWrAddDelay.Data
    );
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u: SC_WR_ADD_Delay = %Xh\n", Channel, ScWrAddDelay.Data);
}

/**
  This function configures the memory controller timings.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
MrcTimingConfiguration (
  IN MrcParameters *const MrcData
  )
{
  UINT8 Channel;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (&MrcData->Outputs, Channel)) {
      //
      // Setup TC_PRE, TC_ACT and TC_ODT registers
      //
      SetTcPreActOdt (MrcData, Channel);
      //
      // Setup turnaround timings
      //
      SetTcTurnAround (MrcData, Channel);
      //
      // Setup TC_PWRDWN register
      //
      SetTcPwrdwn (MrcData, Channel);
      //
      // Setup SC_WR_ADD_DELAY register
      //
      SetWrAddDelay (MrcData, Channel);
    }
  }

  //
  // Check RawCard Types and adjust Read ODT if needed
  //
  RdOdtStretch (MrcData);

  return;
}

/**
  This function sets up the Read ODTD values based on RawCard types and adjusts the tDRRD2RD, tDDRD2RD, tDRRD2WR and tDDRD2WR

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
RdOdtStretch (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcDebug              *Debug;
  const MrcInput        *Inputs;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  UINT8                 Channel;
  UINT8                 ChBitMask;
  UINT8                 RankMaskCh;
  INT8                  OdtStretch;
  BOOLEAN               SoDimm;
#if SUPPORT_SODIMM == SUPPORT
  MrcDimmOut            *DimmOut;
  UINT8                 Dimm;
  UINT8                 DimmRawCardType[MAX_DIMMS_IN_CHANNEL];
  BOOLEAN               DtHalo;
#endif //SUPPORT_SODIMM == SUPPORT

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  ControllerOut     = &Outputs->Controller[0];
#if SUPPORT_SODIMM == SUPPORT
  DtHalo            = ((Inputs->CpuModel == cmSKL_DT_HALO) || (Inputs->CpuModel == cmKBL_DT_HALO));
#endif //SUPPORT_SODIMM == SUPPORT

  ChBitMask = 0;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    if (ChannelOut->ValidRankBitMask && (ChannelOut->DimmCount == 2)) {
      ChBitMask |= (MRC_BIT0 << Channel);
    }
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((MRC_BIT0 << Channel) & ChBitMask)) {
      //
      // Skip any channels that do not have 2 DIMMs populated
      //
      continue;
    }

    ChannelOut    = &ControllerOut->Channel[Channel];
    RankMaskCh = ChannelOut->ValidRankBitMask;
    //
    // Start with the most aggressive setting
    //
    OdtStretch = 6;

    SoDimm = FALSE;
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      DimmOut = &ChannelOut->Dimm[Dimm];
      DimmRawCardType[Dimm] = DimmOut->ReferenceRawCard;
      if (((DimmOut->ModuleType == SoDimmMemoryPackage) || (DimmOut->ModuleType == SoUDimmEccMemoryPackageDdr3))
          && (SoDimm == FALSE)) {
        SoDimm = TRUE;
      }
    }

#if SUPPORT_SODIMM == SUPPORT
    if (SoDimm) {
      if ((DimmRawCardType[0] == rcF || DimmRawCardType[1] == rcF)
          && (DimmRawCardType[0] != DimmRawCardType[1])) {
        OdtStretch = 7;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"Rd Odt Stretch F\n");
      }
    }
#endif //SUPPORT_SODIMM == SUPPORT
    //
    // Program Rdodtd value
    //
    UpdateTAParamOffset (MrcData, Channel, 0, rdodtd, OdtStretch, 1, 1, RankMaskCh);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected RdOdtD Offset for channel %d is = %d\n", Channel, OdtStretch);

#if SUPPORT_SODIMM == SUPPORT
    if (OdtStretch > 6) {
      MrcTatStretch (MrcData, Channel, rdodtd, OdtStretch - 6, TRUE);
    } else {
      // Add 1 for ODT read duration for 2DPC
      if (DtHalo) {
        UpdateTAParamOffset (MrcData, Channel, 0, rdodtd, 8, 1, 1, RankMaskCh);
      }
    }
#endif //SUPPORT_SODIMM == SUPPORT
  }

}


/**
  This function adjusts the relevant TAT when changing Read or Write ODT duration.
  TAT list rdOdt = { drrd2rd, ddrd2rd, drrd2wr, ddrd2wr, srrd2wr_sg, srrd2wr_dg };
  TAT list wrOdt = { drwr2wr, ddwr2wr, drwr2rd, ddwr2rd, srwr2rd_sg, srwr2rd_dg };

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      OdtType - rdodtd or wrodtd
  @param[in]      Offset  - signed offset
  @param[in]      UpdateHost - Switch to update the host struct with the new value.

  @retval Nothing.
**/
void
MrcTatStretch (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                OdtType,
  IN     INT8                 Offset,
  IN     BOOLEAN              UpdateHost
  )
{

  MrcControllerOut      *ControllerOut;
  MrcIntControllerOut   *IntControllerOut;
  MrcIntOutput          *MrcIntData;
  MrcIntChannelOut      *IntChannelOut;
  MrcChannelOut         *ChannelOut;
  MrcOutput             *Outputs;
  MrcDebug              *Debug;
  UINT8                 Value;
  UINT8                 RankMaskCh;
  BOOLEAN               Ddr4;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT  *TcRdRd;
  MCHBAR_CH0_CR_TC_RDWR_STRUCT  *TcRdWr;
  MCHBAR_CH0_CR_TC_WRRD_STRUCT  *TcWrRd;
  MCHBAR_CH0_CR_TC_WRWR_STRUCT  *TcWrWr;

  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  ControllerOut    = &Outputs->Controller[0];
  MrcIntData       = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntControllerOut = &MrcIntData->Controller[0];
  ChannelOut       = &ControllerOut->Channel[Channel];
  IntChannelOut    = &IntControllerOut->Channel[Channel];
  RankMaskCh       = ChannelOut->ValidRankBitMask;
  Ddr4             = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  TcRdRd = &IntChannelOut->MchbarTcRdRd;
  TcRdWr = &IntChannelOut->MchbarTcRdWr;
  TcWrRd = &IntChannelOut->MchbarTcWrRd;
  TcWrWr = &IntChannelOut->MchbarTcWrWr;

  if (OdtType == rdodtd) {
    //
    // Program Different Rank RD 2 RD value
    //
    Value = (UINT8) (TcRdRd->Bits.tRDRD_dr) + Offset;
    UpdateTAParamOffset (MrcData, Channel, 0, drrd2rd, Value, UpdateHost, 1, RankMaskCh);
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected DR RD2RD Offset for channel %d is = %d\n", Channel, Value);

    //
    // Program Different DIMM RD 2 RD value
    //
    Value = (UINT8) (TcRdRd->Bits.tRDRD_dd) + Offset;
    UpdateTAParamOffset (MrcData, Channel, 0, ddrd2rd, Value, UpdateHost, 1, RankMaskCh);
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected DD RD2RD Offset for channel %d is = %d\n", Channel, Value);

    //
    // Program Different Rank RD 2 WR value
    //
    Value = (UINT8) (TcRdWr->Bits.tRDWR_dr) + Offset;
    UpdateTAParamOffset (MrcData, Channel, 0, drrd2wr, Value, UpdateHost, 1, RankMaskCh);
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected DR RD2WR Offset for channel %d is = %d\n", Channel, Value);

    //
    // Program Different DIMM RD 2 WR value
    //
    Value = (UINT8) (TcRdWr->Bits.tRDWR_dd) + Offset;
    UpdateTAParamOffset (MrcData, Channel, 0, ddrd2wr, Value, UpdateHost, 1, RankMaskCh);
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected DD RD2WR Offset for channel %d is = %d\n", Channel, Value);

    //
    // Program Same Rank RD 2 WR sg value
    //
    Value = (UINT8) (TcRdWr->Bits.tRDWR_sg) + Offset;
    UpdateTAParamOffset (MrcData, Channel, 0, srrd2wr_sg, Value, UpdateHost, 1, RankMaskCh);
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected SR RD2WR_sg Offset for channel %d is = %d\n", Channel, Value);

    //
    // Program Same Rank RD 2 WR dg value
    //
    if (Ddr4) {
      Value = (UINT8) (TcRdWr->Bits.tRDWR_dg) + Offset;
      UpdateTAParamOffset (MrcData, Channel, 0, srrd2wr_dg, Value, UpdateHost, 1, RankMaskCh);
      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected SR RD2WR_dg Offset for channel %d is = %d\n", Channel, Value);
    }
  } else if (OdtType == wrodtd) {
    //
    // Program Different Rank WR 2 WR value
    //
    Value = (UINT8) (TcWrWr->Bits.tWRWR_dr) + Offset;
    UpdateTAParamOffset (MrcData, Channel, 0, drwr2wr, Value, UpdateHost, 1, RankMaskCh);
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected DR WR2WR Offset for channel %d is = %d\n", Channel, Value);

    //
    // Program Different DIMM WR 2 WR value
    //
    Value = (UINT8) (TcWrWr->Bits.tWRWR_dd) + Offset;
    UpdateTAParamOffset (MrcData, Channel, 0, ddwr2wr, Value, UpdateHost, 1, RankMaskCh);
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected DD WR2WR Offset for channel %d is = %d\n", Channel, Value);

    //
    // Program Different Rank WR 2 RD value
    //
    Value = (UINT8) (TcWrRd->Bits.tWRRD_dr) + Offset;
    UpdateTAParamOffset (MrcData, Channel, 0, drwr2rd, Value, UpdateHost, 1, RankMaskCh);
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected DR WR2RD Offset for channel %d is = %d\n", Channel, Value);

    //
    // Program Different DIMM WR 2 RD value
    //
    Value = (UINT8) (TcWrRd->Bits.tWRRD_dd) + Offset;
    UpdateTAParamOffset (MrcData, Channel, 0, ddwr2rd, Value, UpdateHost, 1, RankMaskCh);
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected DD WR2RD Offset for channel %d is = %d\n", Channel, Value);

    //
    // Program Same Rank WR 2 RD sg value
    //
    Value = (UINT8) (TcWrRd->Bits.tWRRD_sg) + Offset;
    UpdateTAParamOffset (MrcData, Channel, 0, srwr2rd_sg, Value, UpdateHost, 1, RankMaskCh);
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected SR WR2RD_sg Offset for channel %d is = %d\n", Channel, Value);

    //
    // Program Same Rank WR 2 RD dg value
    //
    if (Ddr4) {
      Value = (UINT8) (TcWrRd->Bits.tWRRD_dg) + Offset;
      UpdateTAParamOffset (MrcData, Channel, 0, srwr2rd_dg, Value, UpdateHost, 1, RankMaskCh);
      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected SR WR2RD_dg Offset for channel %d is = %d\n", Channel, Value);
    }
  }
}

/**
  This function updates the MRC Output structure with the values for turnaround times.
  If the turnaround values are different per channel, then the slowest turnaround will be placed in the output structure

  @param[in, out] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
void
MrcUpdateTatOutputs (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcOutput                           *Outputs;
  MrcControllerOut                    *ControllerOut;
  MrcChannelOut                       *ChannelOut;
  MrcIntOutput                        *MrcIntData;
  MrcIntControllerOut                 *IntControllerOut;
  MrcIntChannelOut                    *IntChannelOut;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT        *TcRdRd;
  MCHBAR_CH0_CR_TC_RDWR_STRUCT        *TcRdWr;
  MCHBAR_CH0_CR_TC_WRRD_STRUCT        *TcWrRd;
  MCHBAR_CH0_CR_TC_WRWR_STRUCT        *TcWrWr;
  UINT8                               Controller;
  UINT8                               Channel;

  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Outputs = &MrcData->Outputs;

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut    = &Outputs->Controller[Controller];
    IntControllerOut = &MrcIntData->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      ChannelOut    = &ControllerOut->Channel[Channel];
      IntChannelOut = &IntControllerOut->Channel[Channel];
      TcRdRd = &IntChannelOut->MchbarTcRdRd;
      TcRdWr = &IntChannelOut->MchbarTcRdWr;
      TcWrRd = &IntChannelOut->MchbarTcWrRd;
      TcWrWr = &IntChannelOut->MchbarTcWrWr;

      ChannelOut->tRd2Rd.SG = (UINT8) TcRdRd->Bits.tRDRD_sg;
      ChannelOut->tRd2Rd.DG = (UINT8) TcRdRd->Bits.tRDRD_dg;
      ChannelOut->tRd2Rd.DR = (UINT8) TcRdRd->Bits.tRDRD_dr;
      ChannelOut->tRd2Rd.DD = (UINT8) TcRdRd->Bits.tRDRD_dd;

      ChannelOut->tRd2Wr.SG = (UINT8) TcRdWr->Bits.tRDWR_sg;
      ChannelOut->tRd2Wr.DG = (UINT8) TcRdWr->Bits.tRDWR_dg;
      ChannelOut->tRd2Wr.DR = (UINT8) TcRdWr->Bits.tRDWR_dr;
      ChannelOut->tRd2Wr.DD = (UINT8) TcRdWr->Bits.tRDWR_dd;

      ChannelOut->tWr2Rd.SG = (UINT8) TcWrRd->Bits.tWRRD_sg;
      ChannelOut->tWr2Rd.DG = (UINT8) TcWrRd->Bits.tWRRD_dg;
      ChannelOut->tWr2Rd.DR = (UINT8) TcWrRd->Bits.tWRRD_dr;
      ChannelOut->tWr2Rd.DD = (UINT8) TcWrRd->Bits.tWRRD_dd;

      ChannelOut->tWr2Wr.SG = (UINT8) TcWrWr->Bits.tWRWR_sg;
      ChannelOut->tWr2Wr.DG = (UINT8) TcWrWr->Bits.tWRWR_dg;
      ChannelOut->tWr2Wr.DR = (UINT8) TcWrWr->Bits.tWRWR_dr;
      ChannelOut->tWr2Wr.DD = (UINT8) TcWrWr->Bits.tWRWR_dd;
    }
  }
}

/**
  This function applies the turnaround timing overrides, if any, which are specified in the MRC Input structure.

  @param[in, out] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
void
MrcTurnaroundTimingOverrides (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcDebug                            *Debug;
  MrcInput                            *Inputs;
  MrcOutput                           *Outputs;
  MrcIntOutput                        *MrcIntData;
  MrcIntControllerOut                 *IntControllerOut;
  MrcIntChannelOut                    *IntChannelOut;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT        *TcRdRd;
  MCHBAR_CH0_CR_TC_RDWR_STRUCT        *TcRdWr;
  MCHBAR_CH0_CR_TC_WRRD_STRUCT        *TcWrRd;
  MCHBAR_CH0_CR_TC_WRWR_STRUCT        *TcWrWr;
  UINT8                               Controller;
  UINT8                               Channel;
#ifdef MRC_DEBUG_PRINT
  const char TurnaroundSgDgError[]  = "SG and DG turnarounds must be the same!\nSetting DG timing equal to SG timing\n";
  const char *TurnaroundTimingStrings[]   = {"tRdRd", "tRdWr", "tWrRd", "tWrWr"};
  UINT8      TurnaroundErrorMask;
  UINT8      StringIndex;
#endif

  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  //
  // Override turnaround register timings to user opted values
  //
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    IntControllerOut = &MrcIntData->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      IntChannelOut = &IntControllerOut->Channel[Channel];
      TcRdRd = &IntChannelOut->MchbarTcRdRd;
      TcRdWr = &IntChannelOut->MchbarTcRdWr;
      TcWrRd = &IntChannelOut->MchbarTcWrRd;
      TcWrWr = &IntChannelOut->MchbarTcWrWr;

#ifdef MRC_DEBUG_PRINT
      TurnaroundErrorMask = 0;
#endif

      if (Outputs->DdrType != MRC_DDR_TYPE_DDR4) {
        if (Inputs->tRd2Rd.SG != Inputs->tRd2Rd.DG) {
#ifdef MRC_DEBUG_PRINT
          TurnaroundErrorMask |= 0x1;
#endif
          Inputs->tRd2Rd.DG = Inputs->tRd2Rd.SG;
        }

        if (Inputs->tRd2Wr.SG != Inputs->tRd2Wr.DG) {
#ifdef MRC_DEBUG_PRINT
          TurnaroundErrorMask |= 0x2;
#endif
          Inputs->tRd2Wr.DG = Inputs->tRd2Wr.SG;
        }

        if (Inputs->tWr2Rd.SG != Inputs->tWr2Rd.DG) {
#ifdef MRC_DEBUG_PRINT
          TurnaroundErrorMask |= 0x4;
#endif
          Inputs->tWr2Rd.DG = Inputs->tWr2Rd.SG;
        }

        if (Inputs->tWr2Wr.SG != Inputs->tWr2Wr.DG) {
#ifdef MRC_DEBUG_PRINT
          TurnaroundErrorMask |= 0x8;
#endif
          Inputs->tWr2Wr.DG = Inputs->tWr2Wr.SG;
        }

#ifdef MRC_DEBUG_PRINT
        if (TurnaroundErrorMask != 0) {
          for (StringIndex = 0; StringIndex < 4; StringIndex++) {
            if (TurnaroundErrorMask & 1 << StringIndex) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR - %s %s", TurnaroundTimingStrings[StringIndex], TurnaroundSgDgError);
            }
          }
        }
#endif
      }

      //
      // Override RDRD turnarounds
      //
      if (Inputs->tRd2Rd.SG != 0) {
        TcRdRd->Bits.tRDRD_sg = MIN (Inputs->tRd2Rd.SG, tRDRD_MAX);
      }

      if (Inputs->tRd2Rd.DG != 0) {
        TcRdRd->Bits.tRDRD_dg = MIN (Inputs->tRd2Rd.DG, tRDRD_MAX);
      }

      if (Inputs->tRd2Rd.DR != 0) {
        TcRdRd->Bits.tRDRD_dr = MIN (Inputs->tRd2Rd.DR, tRDRD_MAX);
      }

      if (Inputs->tRd2Rd.DD != 0) {
        TcRdRd->Bits.tRDRD_dd = MIN (Inputs->tRd2Rd.DD, tRDRD_MAX);
      }

      //
      // Override RDWR turnarounds
      //
      if (Inputs->tRd2Wr.SG != 0) {
        TcRdWr->Bits.tRDWR_sg = MIN (Inputs->tRd2Wr.SG, tRDWR_MAX);
      }

      if (Inputs->tRd2Wr.DG != 0) {
        TcRdWr->Bits.tRDWR_dg = MIN (Inputs->tRd2Wr.DG, tRDWR_MAX);
      }

      if (Inputs->tRd2Wr.DR != 0) {
        TcRdWr->Bits.tRDWR_dr = MIN (Inputs->tRd2Wr.DR, tRDWR_MAX);
      }

      if (Inputs->tRd2Wr.DD != 0) {
        TcRdWr->Bits.tRDWR_dd = MIN (Inputs->tRd2Wr.DD, tRDWR_MAX);
      }

      //
      // Override WRRD turnarounds
      //
      if (Inputs->tWr2Rd.SG != 0) {
        TcWrRd->Bits.tWRRD_sg = MIN (Inputs->tWr2Rd.SG, tWRRD_SG_MAX);
      }

      if (Inputs->tWr2Rd.DG != 0) {
        TcWrRd->Bits.tWRRD_dg = MIN (Inputs->tWr2Rd.DG, tWRRD_MAX);
      }

      if (Inputs->tWr2Rd.DR != 0) {
        TcWrRd->Bits.tWRRD_dr = MIN (Inputs->tWr2Rd.DR, tWRRD_MAX);
      }

      if (Inputs->tWr2Rd.DD != 0) {
        TcWrRd->Bits.tWRRD_dd = MIN (Inputs->tWr2Rd.DD, tWRRD_MAX);
      }

      //
      // Override WRWR turnarounds
      //
      if (Inputs->tWr2Wr.SG != 0) {
        TcWrWr->Bits.tWRWR_sg = MIN (Inputs->tWr2Wr.SG, tWRWR_MAX);
      }

      if (Inputs->tWr2Wr.DG != 0) {
        TcWrWr->Bits.tWRWR_dg = MIN (Inputs->tWr2Wr.DG, tWRWR_MAX);
      }

      if (Inputs->tWr2Wr.DR != 0) {
        TcWrWr->Bits.tWRWR_dr = MIN (Inputs->tWr2Wr.DR, tWRWR_MAX);
      }

      if (Inputs->tWr2Wr.DD != 0) {
        TcWrWr->Bits.tWRWR_dd = MIN (Inputs->tWr2Wr.DD, tWRWR_MAX);
      }

      MrcProgramTurnarounds (MrcData, Channel);
      MrcUpdateTatOutputs (MrcData);
    }
  }

  return;
}

