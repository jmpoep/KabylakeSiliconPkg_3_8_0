/** @file
  This module sets the memory controller refresh parameters.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2015 Intel Corporation.

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
///
/// Include files
///
#include "MrcRefreshConfiguration.h"

/**
  This function returns the tXS offset in DCLKs, minus 8 DCLKs.
  tXS-offset: tXS = tRFC+10ns. Setup of tXS-offset is # of DCLKs
  for 10 ns, minus 8 DCLKs.

  @param[in] tCK - the memory DCLK in femtoseconds..

  @retval tXS-offset value.
**/
static
UINT32
tXsOffset (
  IN const UINT32 tCK
  )
{
  UINT32 Value;

  //
  // Convert 10ns to DCLKs using the current tCK
  //
  Value = DIVIDECEIL (10 * 1000 * 1000, tCK);

  //
  // Subtract up to 8 DCLKs, because HW already adds 8 DCLKs
  //
  Value = (Value <= 8) ? 0 : (Value - 8);

  return Value;
}

/**
  This function returns the tXSDLL in DCLKs based on DDR Type, and Frequency.
  DDR3 has one value.  DDR4 has values per frequency, and LPDDR3/4 do not have
  a DLL.  From the spec, we must wait tXSR before issuing a command.  Thus,
  we set tXSDLL to tXSR to ensure tXSR before read/write commands.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Frequency  - The memory frequency.
  @param[in] tXSR       - Value of tXSR.
**/
static
UINT32
tXSDLLGet (
  IN MrcParameters *const MrcData,
  IN const MrcFrequency   Frequency,
  IN const UINT32         tXSR
  )
{
  UINT32      tXSDLLVal;
  MrcDdrType  DdrType;

  DdrType = MrcData->Outputs.DdrType;

  if (DdrType == MRC_DDR_TYPE_DDR3) {
    tXSDLLVal = tDLLK_VALUE_DDR3;
  } else if (DdrType == MRC_DDR_TYPE_DDR4) {
    if (Frequency <= f1867) {
      tXSDLLVal = tDLLK_DDR4_1867;
    } else if (Frequency <= f2400) {
      tXSDLLVal = tDLLK_DDR4_2400;
    } else {
      tXSDLLVal = tDLLK_DDR4_MAX;
    }
  } else {
    //
    // No DLL in LPDDR3 - use tXSR
    //
    tXSDLLVal = tXSR;
  }

  return tXSDLLVal;
}

/**
  This function configures TC_RFP and TC_RFTP registers and their fields tREFI,
  tRFC, tREFIx9, OREF_RI.
  Note that TC_RFTP.tREFIx9 was moved to TC_RFP from SKL B0 onwards.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Channel to work on.

  @retval Nothing.
**/
void
SetTcRfpRftpReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  )
{
  const MrcInput                *Inputs;
  MrcTiming                     *TimingOut;
  MCHBAR_CH0_CR_TC_RFP_STRUCT   TcRfp;
  MCHBAR_CH0_CR_TC_RFTP_STRUCT  TcRftp;
  MrcProfile                    Profile;
  UINT32                        tRefi;
  UINT32                        tRefix9;
  UINT32                        Offset;

  Inputs              = &MrcData->Inputs;
  Profile             = Inputs->MemoryProfile;
  TimingOut           = &MrcData->Outputs.Controller[0].Channel[Channel].Timing[Profile];
  tRefi               = TimingOut->tREFI;

  if (Inputs->SaGv == MrcSaGvEnabled) {
    // Reduce tREFI by a factor 2.8%
    tRefi *= 972;
    tRefi = DIVIDEROUND (tRefi, 1000);
  }
  tRefix9             = (tRefi * 89) / (1024 * 10);

  TcRftp.Data         = 0;
  TcRftp.Bits.tREFI   = MIN (MCHBAR_CH0_CR_TC_RFTP_tREFI_MAX, tRefi);
  TcRftp.Bits.tRFC    = MIN (MCHBAR_CH0_CR_TC_RFTP_tRFC_MAX, TimingOut->tRFC);

  Offset = MCHBAR_CH0_CR_TC_RFP_REG + (MCHBAR_CH1_CR_TC_RFP_REG - MCHBAR_CH0_CR_TC_RFP_REG) * Channel;
  TcRfp.Data = MrcReadCR (MrcData, Offset);
  TcRfp.Bits.tREFIx9  = MIN (MCHBAR_CH0_CR_TC_RFP_tREFIx9_MAX, tRefix9);

  //
  // Set LP0 WM and OREF_RI to support high memory BW traffic
  //
  TcRfp.Bits.OREF_RI = 0x40;
  MrcWriteCR (MrcData, Offset, TcRfp.Data);
  MRC_DEBUG_MSG (
    &MrcData->Outputs.Debug,
    MSG_LEVEL_NOTE,
    "Ch%u: TC_RFP = %Xh\n OREF_RI = %u\n",
    Channel,
    TcRfp.Data,
    TcRfp.Bits.OREF_RI
    );

  Offset = MCHBAR_CH0_CR_TC_RFTP_REG + (MCHBAR_CH1_CR_TC_RFTP_REG - MCHBAR_CH0_CR_TC_RFTP_REG) * Channel;
  MrcWriteCR (MrcData, Offset, TcRftp.Data);
  MRC_DEBUG_MSG (
    &MrcData->Outputs.Debug,
    MSG_LEVEL_NOTE,
    "Ch%u: TC_RFTP = %Xh\n tREFI = %u\n tRFC = %u\n",
    Channel,
    TcRftp.Data,
    TcRftp.Bits.tREFI,
    TcRftp.Bits.tRFC
    );
}

/**
  This function configures the TC-SRFTP register and its fields tZQOPER, tXS-offset, tXSDLL.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] ChannelIndex    - Channel to work on.

  @retval Nothing.
**/
static
void
SetTcSrftpReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         ChannelIndex
  )
{
  const MrcInput                *Inputs;
  MrcFrequency                  Frequency;
  MrcTiming                     *Timing;
  UINT32                        tZQOPER;
  UINT32                        tXS_offset;
  UINT32                        tMod;
  UINT32                        tDLLK;
  UINT32                        tXSR;
  UINT32                        Offset;
  MCHBAR_CH0_CR_TC_SRFTP_STRUCT CrTcSrftp;

  Inputs                    = &MrcData->Inputs;
  Frequency                 = MrcData->Outputs.Frequency;
  Timing                    = &MrcData->Outputs.Controller[0].Channel[ChannelIndex].Timing[Inputs->MemoryProfile];
  tZQOPER                   = tZQOPERGet (MrcData, Frequency);
  tXS_offset                = tXsOffset (Timing->tCK);
  tMod                      = tMODGet (MrcData, Frequency);
  tXSR                      = Timing->tRFC + DIVIDECEIL (10 * 1000 * 1000, Timing->tCK);  // Convert 10ns to DCLKs using the current tCK
  tDLLK                     = tXSDLLGet (MrcData, Frequency, tXSR);

  CrTcSrftp.Data            = 0;
  CrTcSrftp.Bits.tXSDLL     = MIN (MCHBAR_CH0_CR_TC_SRFTP_tXSDLL_MAX, tDLLK);
  CrTcSrftp.Bits.tXS_offset = MIN (MCHBAR_CH0_CR_TC_SRFTP_tXS_offset_MAX, tXS_offset);
  CrTcSrftp.Bits.tZQOPER    = MIN (MCHBAR_CH0_CR_TC_SRFTP_tZQOPER_MAX, tZQOPER);
  CrTcSrftp.Bits.tMOD       = MIN (MCHBAR_CH0_CR_TC_SRFTP_tMOD_MAX, tMod);
  Offset                    =
    MCHBAR_CH0_CR_TC_SRFTP_REG +
    ((MCHBAR_CH1_CR_TC_SRFTP_REG - MCHBAR_CH0_CR_TC_SRFTP_REG) * ChannelIndex);
  MrcWriteCR (MrcData, Offset, CrTcSrftp.Data);
  MRC_DEBUG_MSG (
    &MrcData->Outputs.Debug,
    MSG_LEVEL_NOTE,
    "Ch%u: TC_SRFTP = %Xh\n tXSDLL = %u\n tXS_offset = %u\n tZQOPER = %u\n tMOD = %u\n",
    ChannelIndex,
    CrTcSrftp.Data,
    CrTcSrftp.Bits.tXSDLL,
    CrTcSrftp.Bits.tXS_offset,
    CrTcSrftp.Bits.tZQOPER,
    CrTcSrftp.Bits.tMOD
    );
  return;
}

/**
  This function returns the tZQOPER value.
  tZQOPER = Defines the period required for ZQCL after SR exit.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Frequency       - The memory frequency.

  @retval The tZQOPER value.
**/
UINT32
tZQOPERGet (
  IN MrcParameters *const MrcData,
  IN const MrcFrequency   Frequency
  )
{
  MrcOutput  *Outputs;
  UINT32     tZQOPER;
  MrcDdrType DdrType;

  Outputs = &MrcData->Outputs;
  DdrType = Outputs->DdrType;
  if (DdrType == MRC_DDR_TYPE_LPDDR3) {
    tZQOPER = tZQCL_MIN / (Outputs->Qclkps * 2);
  } else
#if (SUPPORT_DDR4 == SUPPORT)
    if (DdrType == MRC_DDR_TYPE_DDR4) {
    tZQOPER = tZQOPER_DDR4;
  } else
#endif // SUPPORT_DDR4
  {
    if (Frequency <= f1600) {
      ///
      /// All frequencies below 1600 uses the same value
      ///
      tZQOPER = tZQOPER_1600;
    } else if (Frequency <= f1867) {
      tZQOPER = tZQOPER_1867;
    } else if (Frequency <= f2133) {
      tZQOPER = tZQOPER_2133;
    } else if (Frequency <= f2400) {
      tZQOPER = tZQOPER_2400;
    } else if (Frequency <= f2667) {
      tZQOPER = tZQOPER_2667;
    } else if (Frequency <= f2933) {
      tZQOPER = tZQOPER_2933;
    } else {
      tZQOPER = tZQOPER_3200;
    }
  }

  return tZQOPER;
}

/**
  This function returns the tMOD value.
  tMOD = max(12nCK, 15ns) nCK change by the frequency for DDR3
         max(24nCK, 15ns) nCK change by the frequency for DDR4

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Frequency       - The memory frequency.

  @retval The tMOD value.
**/
UINT32
tMODGet (
  IN MrcParameters *const MrcData,
  IN const MrcFrequency Frequency
  )
{
  UINT32 tMOD;

#if (SUPPORT_DDR4 == SUPPORT)
  if (MrcData->Outputs.DdrType == MRC_DDR_TYPE_DDR4) {
    tMOD = tMOD_DDR4;
  } else
#endif // SUPPORT_DDR4
  if (Frequency <= f800) {
    tMOD = tMOD_800;
  } else if (Frequency <= f1067) {
    tMOD = tMOD_1067;
  } else if (Frequency <= f1333) {
    tMOD = tMOD_1333;
  } else if (Frequency <= f1600) {
    tMOD = tMOD_1600;
  } else if (Frequency <= f1867) {
    tMOD = tMOD_1867;
  } else if (Frequency <= f2133) {
    tMOD = tMOD_2133;
  } else if (Frequency <= f2400) {
    tMOD = tMOD_2400;
  } else if (Frequency <= f2667) {
    tMOD = tMOD_2667;
  } else if (Frequency <= f2800) {
    tMOD = tMOD_2800;
  } else if (Frequency <= f2933) {
    tMOD = tMOD_2933;
  } else if (Frequency <= f3000) {
    tMOD = tMOD_3000;
  } else {
    tMOD = tMOD_3200;
  }

  return tMOD;
}

/**
  This function configures the TC-ZQCAL register and its fields tZQCS and tZQCS_PERIOD.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] ChannelIndex    - Channel to work on.

  @retval Nothing.
**/
static
void
SetTcZqCalReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         ChannelIndex
  )
{
  MrcInput                      *Inputs;
  MrcOutput                     *Outputs;
  MCHBAR_CH0_CR_TC_ZQCAL_STRUCT ZqCal;
  UINT32                        Offset;
  MrcTiming                     *Timing;

  Inputs   = &MrcData->Inputs;
  Outputs  = &MrcData->Outputs;
  Timing   = &Outputs->Controller[0].Channel[ChannelIndex].Timing[Inputs->MemoryProfile];

  Offset = MCHBAR_CH0_CR_TC_ZQCAL_REG + (MCHBAR_CH1_CR_TC_ZQCAL_REG - MCHBAR_CH0_CR_TC_ZQCAL_REG) * ChannelIndex;

  ZqCal.Data  = 0;
  ZqCal.Bits.tZQCS = tZQCSGet (MrcData, Timing->tCK);
  ZqCal.Bits.ZQCS_period = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3) ? ZQCS_PERIOD_LPDDR3 : ZQCS_PERIOD_DDR3;
  MrcWriteCR (MrcData, Offset, ZqCal.Data);

  MRC_DEBUG_MSG (
    &Outputs->Debug,
    MSG_LEVEL_NOTE,
    "Ch%u: TC_ZQCAL = %Xh\n ZQCS_period = %u\n tZQCS = %u\n",
    ChannelIndex,
    ZqCal.Data,
    ZqCal.Bits.ZQCS_period,
    ZqCal.Bits.tZQCS
    );
}

/**
  This function returns the tZQCS value.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] tCK             - DCLK period in femtoseconds.

  @retval The tZQCS value.
**/
UINT32
tZQCSGet (
  IN MrcParameters *const MrcData,
  IN UINT32               tCK
  )
{
  UINT32 tZQCS;

  tZQCS = 0;

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_LPDDR3:
      tZQCS = DIVIDECEIL (tZQCS_LPDDR3_FS, tCK);
      break;

    case MRC_DDR_TYPE_DDR3:
    default:
      tZQCS = DIVIDECEIL (tZQCS_DDR3_FS, tCK);
      tZQCS = MAX (tZQCS, tZQCS_DDR3_CK);
      break;

    case MRC_DDR_TYPE_DDR4:
      tZQCS = tZQCS_DDR4;
      break;
  }
  return tZQCS;
}

/**
  This function configures the TC_MR2_SHADDOW register and its fields.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Channel         - Channel to work on.
  @param[in] Dimm            - Dimm to work on.
  @param[in] Mr2Value        - The value of MR2 to setup.

  @retval Nothing.
**/
void
SetTcMr2ShadowReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel,
  IN const UINT32         Dimm,
  IN UINT32               Mr2Value
  )
{
  MrcDimmOut                          *DimmOut;
  MCHBAR_CH0_CR_TC_MR2_SHADDOW_STRUCT TcMr2Shaddow;
  UINT32                              Offset;

  Offset = MCHBAR_CH0_CR_TC_MR2_SHADDOW_REG +
    ((MCHBAR_CH1_CR_TC_MR2_SHADDOW_REG - MCHBAR_CH0_CR_TC_MR2_SHADDOW_REG) * Channel);
  TcMr2Shaddow.Data = MrcReadCR (MrcData, Offset);

  DimmOut = &MrcData->Outputs.Controller[0].Channel[Channel].Dimm[Dimm];
  if (DimmOut->SelfRefreshTemp && !DimmOut->AutoSelfRefresh) {
    TcMr2Shaddow.Bits.SRT_avail |= (1 << Dimm);
  }

  TcMr2Shaddow.Bits.MR2_shaddow = Mr2Value & 0x3FFF;  // Bits [13:0] of MR2

  MrcWriteCR (MrcData, Offset, TcMr2Shaddow.Data);
  MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "Ch%u: TC_MR2_SHADOW = %Xh\n", Channel, TcMr2Shaddow.Data);
}

/**
  This function executes the refresh configuration process.

  @param[in] MrcData         - Include all MRC global data.

  @retval Nothing.
**/
void
MrcRefreshConfiguration (
  IN MrcParameters *const MrcData
  )
{
  UINT32 Offset;
  UINT8 Channel;
  MCHBAR_CH0_CR_MC_REFRESH_STAGGER_STRUCT RefreshStagger;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (&MrcData->Outputs, Channel)) {
      SetTcRfpRftpReg (MrcData, Channel);
      SetTcSrftpReg (MrcData, Channel);
      SetTcZqCalReg (MrcData, Channel);

      RefreshStagger.Data = 0;
      RefreshStagger.Bits.En_Ref_Type_Display = 1;
      Offset = MCHBAR_CH0_CR_MC_REFRESH_STAGGER_REG +
        ((MCHBAR_CH1_CR_MC_REFRESH_STAGGER_REG - MCHBAR_CH0_CR_MC_REFRESH_STAGGER_REG) * Channel);
      MrcWriteCR (MrcData, Offset, RefreshStagger.Data);
    }
  }
}

