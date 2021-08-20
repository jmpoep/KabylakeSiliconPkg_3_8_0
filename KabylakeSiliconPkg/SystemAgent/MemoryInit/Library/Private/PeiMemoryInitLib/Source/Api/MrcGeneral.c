/** @file
  This file all the MRC general API to the MRC wrapper.

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


#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcGeneral.h"
#include "MrcDdr3.h"
#include "MrcStartMemoryConfiguration.h"
#include "MrcTimingConfiguration.h"
#include <Library/MemoryAddressEncodeDecodeLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED const MrcVersion  cVersion[] = {
  #include "MrcVersion.h"
};

#ifdef MRC_DEBUG_PRINT
extern const char CcdString[];
const char TrainEnString[]  = "TrainingEnables";
const char GdxcString[]     = "Gdxc";
const char BaseTimeString[] = "BaseTime";
const char ThermEnString[]  = "ThermalEnables";
const char PrintBorder[]    = "*************************************\n";
#endif // MRC_DEBUG_PRINT

//
// This table is used for LPDDR3 MR5 decoding
//
struct {
  UINT8   VendorId;
  UINT16  JedecId;
  char    *VendorName;
} DramVendorList [] = {
  { 1,    0xCE00, "Samsung" },
  { 3,    0xFE02, "Elpida"  },
  { 6,    0xAD00, "Hynix"   },
  { 0xFF, 0x2C00, "Micron"  },
};

/**
  Enable DLL WeakLock if needed. We don't enable it in McConfig
  because CKE is still low during that step.

  @param[in] MrcData - The MRC general data.

  @retval None
**/

void
MrcSetWeaklock (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput  *Inputs;
  MrcIntOutput    *MrcIntData;
  MrcOutput       *Outputs;
  MrcChannelOut   *ChannelOut;
  MrcIntChannelOut *IntChannelOut;
  UINT32          Offset;
  UINT8           Channel;
  UINT8           Byte;
  DDRCLKCH0_CR_DDRCRCLKCONTROLS_STRUCT  DdrCrClkControls;
  DDRCMDCH0_CR_DDRCRCMDCONTROLS_STRUCT  DdrCrCmdControls;
  DDRCKECH0_CR_DDRCRCTLCONTROLS_STRUCT  DdrCrCkeControls;
  DDRCTLCH0_CR_DDRCRCTLCONTROLS_STRUCT  DdrCrCtlControls;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  if (!(Inputs->WeaklockEn)
      ) {
    return;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    ChannelOut    = &Outputs->Controller[0].Channel[Channel];
    IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      IntChannelOut->DqControl1[Byte].Bits.DllWeakLock = 1;
      Offset = MrcGetOffsetDataControl1 (MrcData, Channel, Byte);
      MrcWriteCR (MrcData, Offset, IntChannelOut->DqControl1[Byte].Data);
    }

    if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3) {
      Offset = DDRCLKCH0_CR_DDRCRCLKCONTROLS_REG +
        ((DDRCLKCH1_CR_DDRCRCLKCONTROLS_REG - DDRCLKCH0_CR_DDRCRCLKCONTROLS_REG) * Channel);
      DdrCrClkControls.Data = MrcReadCR (MrcData, Offset);
      DdrCrClkControls.Bits.DllWeakLock = 1;
      MrcWriteCR (MrcData, Offset, DdrCrClkControls.Data);
    }

    Offset = DDRCMDCH0_CR_DDRCRCMDCONTROLS_REG +
      ((DDRCMDCH1_CR_DDRCRCMDCONTROLS_REG - DDRCMDCH0_CR_DDRCRCMDCONTROLS_REG) * Channel);
    DdrCrCmdControls.Data = MrcReadCR (MrcData, Offset);
    DdrCrCmdControls.Bits.DllWeakLock = 1;
    MrcWriteCR (MrcData, Offset, DdrCrCmdControls.Data);

    Offset = DDRCTLCH0_CR_DDRCRCTLCONTROLS_REG +
      ((DDRCTLCH1_CR_DDRCRCTLCONTROLS_REG - DDRCTLCH0_CR_DDRCRCTLCONTROLS_REG) * Channel);
    DdrCrCtlControls.Data = MrcReadCR (MrcData, Offset);
    DdrCrCtlControls.Bits.DllWeakLock = 1;
    MrcWriteCR (MrcData, Offset, DdrCrCtlControls.Data);

    Offset = DDRCKECH0_CR_DDRCRCTLCONTROLS_REG +
      ((DDRCKECH1_CR_DDRCRCTLCONTROLS_REG - DDRCKECH0_CR_DDRCRCTLCONTROLS_REG) * Channel);
    DdrCrCkeControls.Data = MrcReadCR (MrcData, Offset);
    DdrCrCkeControls.Bits.DllWeakLock = 1;
    MrcWriteCR (MrcData, Offset, DdrCrCkeControls.Data);
  } // for Channel
}

/**
  Read LPDDR3 information from MR5 and MR8 and print to the debug log.
  Also update the Manufacturer's ID in the SPD table, for BIOS Setup and SMBIOS table.

  @param[in] MrcData - include all the MRC general data.

  @retval none
**/
void
ShowLpddrInfo (
  IN  MrcParameters *const MrcData
  )
{
  MrcInput        *Inputs;
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  MrcIntOutput    *MrcIntData;
  MrcSpd          *SpdIn;
  UINT32          Channel;
  UINT32          Rank;
  UINT8           MrrResult[4];
  UINT32          MrAddr;
  UINT32          Device;
  UINT32          Index;
  BOOLEAN         VendorFound;
  UINT16          JedecId;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Debug   = &Outputs->Debug;
  VendorFound = FALSE;
  Index = 0;

  if (Inputs->BootMode != bmCold) {
    //
    // Full deswizzle table is not present on non-cold flows, so cannot parse MR read.
    //
    return;
  }
  //
  // LPDDR: Read MR5 and MR8
  //
  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, (UINT8) Rank, (UINT8) Channel)) {
          continue;
        }

        //
        // MR5 - Manufacturer ID
        //
        MrAddr = 5;
        MrcIssueMrr (MrcData, Channel, Rank, MrAddr, MrrResult);
        for (Device = 0; Device < sizeof (MrrResult) / sizeof (MrrResult[0]); Device++) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tDevice[%u]= 0x%02X", Device, MrrResult[Device]);
          VendorFound = FALSE;
          for (Index = 0; Index < sizeof (DramVendorList) / sizeof (DramVendorList[0]); Index++) {
            if (DramVendorList[Index].VendorId == MrrResult[Device]) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %s\n", DramVendorList[Index].VendorName);
              VendorFound = TRUE;
              break;
            }
          }
          if (!VendorFound) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Unknown\n");
          }
        }

        if (VendorFound) {
          //
          // Patch SPD data with vendor ID code.
          // This is consumed by BIOS Setup and SMBIOS Type 17 table creation code.
          // If SAGV enabled, only do this on the second pass.
          //
          if ((Inputs->SaGv != MrcSaGvEnabled) || (MrcIntData->SaGvPoint != MrcSaGvPointLow)) {
            JedecId = DramVendorList[Index].JedecId;
            SpdIn = &Inputs->Controller[0].Channel[Channel].Dimm[Rank / 2].Spd.Data;
            if (SpdIn->Lpddr.Base.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER) {
              SpdIn->Ddr3.ModuleId.IdCode.Data = JedecId;
              SpdIn->Ddr3.DramIdCode.Data      = JedecId;
            } else {
              SpdIn->Lpddr.ManufactureInfo.ModuleId.IdCode.Data = JedecId;
              SpdIn->Lpddr.ManufactureInfo.DramIdCode.Data      = JedecId;
            }
          }
        }

#ifdef MRC_DEBUG_PRINT
        //
        // MR8 - I/O Width, Density, Type
        //
        MrAddr = 8;
        MrcIssueMrr (MrcData, Channel, Rank, MrAddr, MrrResult);
        for (Device = 0; Device < sizeof (MrrResult) / sizeof (MrrResult[0]); Device++) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tDevice[%u]= 0x%02X - %s\n", Device, MrrResult[Device],
            (MRC_BIT6 & MrrResult[Device]) ? "x16" : "x32");
        }
#endif // #ifdef MRC_DEBUG_PRINT
      } // for Rank
    } // for Channel
  }
}

/**
  This function changes the MC to normal mode, enables the ECC
  if needed. If the ECC is enabled, this function should be
  called after memory is cleaned.

  @param[in, out] MrcData - Include all MRC global data.

  @retval Always returns mrcSuccess.
**/
MrcStatus
MrcMcActivate (
  IN     MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION                        *MrcCall;
  const MrcInput                            *Inputs;
  MrcDebug                                  *Debug;
  MrcIntOutput                              *MrcIntData;
  MrcOutput                                 *Outputs;
  MrcControllerOut                          *ControllerOut;
  MrcIntControllerOut                       *IntControllerOut;
  MrcChannelOut                             *ChannelOut;
  MrcIntChannelOut                          *IntChannelOut;
  MrcCpuModel                               CpuModel;
  MrcCpuStepping                            CpuStepping;
  MCHBAR_CH0_CR_SC_GS_CFG_STRUCT            ScGsCfg;
  DDRSCRAM_CR_DDRSCRAMBLECH0_STRUCT         DdrScramble;
  MCDECS_CR_MAD_INTRA_CH0_MCMAIN_STRUCT     MadIntra;
  UINT32                                    Offset;
  UINT32                                    GeneratedSeed;
  UINT8                                     Controller;
  UINT8                                     Channel;
  UINT8                                     Byte;
  UINT8                                     Rank;
  UINT8                                     MaxRcvEn;
  UINT8                                     RcvEnDrift;
  UINT8                                     RcvEnTurnOff;
  INT8                                      OdtTurnOff;
  BOOLEAN                                   Lpddr;
  UINT16                                    SAFE;
  UINT16                                    NS;

  MrcIntData    = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &MrcData->Outputs.Debug;
  GeneratedSeed = 0;
  CpuModel      = Inputs->CpuModel;
  CpuStepping   = Inputs->CpuStepping;
  SAFE          = 0;

  NS = ~SAFE;

  MrcBeforeNormalModeTestMenu (MrcData);
  //
  // Oem hook before normal mode configuration starts
  //
  MrcInternalCheckPoint (MrcData, OemBeforeNormalMode, NULL);

  //
  // Read LPDDR3 MR5 and MR8 info
  //
  ShowLpddrInfo (MrcData);

  //
  // Program DllWeaklock bit after training, when CKE is high
  //
  MrcSetWeaklock (MrcData);

  //
  //
  IntControllerOut = &MrcIntData->Controller[0];
  IntControllerOut->MiscControl0.Bits.DataClkGateDisAtIdle = 0;
  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL0_REG, IntControllerOut->MiscControl0.Data);

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }

      ChannelOut = &ControllerOut->Channel[Channel];

      //
      // Enable Scrambling
      //
      if (Inputs->ScramblerEnable == TRUE) {
        MrcCall->MrcGetRandomNumber (&GeneratedSeed);
        //
        // Set Scramble key and enable bits
        //
        DdrScramble.Data          = 0;
        DdrScramble.Bits.ScramKey = GeneratedSeed;
        DdrScramble.Bits.ScramEn  = 1;
        DdrScramble.Bits.ClockGateAB = NS;
        DdrScramble.Bits.ClockGateC  = NS;
        DdrScramble.Bits.EnableDbiAB = NS;
        MrcWriteCR (
          MrcData,
          DDRSCRAM_CR_DDRSCRAMBLECH0_REG + ((DDRSCRAM_CR_DDRSCRAMBLECH1_REG - DDRSCRAM_CR_DDRSCRAMBLECH0_REG) * Channel),
          DdrScramble.Data
          );
      }

      Offset = MCHBAR_CH0_CR_SC_GS_CFG_REG + ((MCHBAR_CH1_CR_SC_GS_CFG_REG - MCHBAR_CH0_CR_SC_GS_CFG_REG) * Channel);
      ScGsCfg.Data = MrcReadCR (MrcData, Offset);
      //
      // Enable the command tri state at the end of the training.
      //
      if (!Inputs->CmdTriStateDis) {
        ScGsCfg.Bits.cmd_3st = 0;
      }
      MrcWriteCR (MrcData, Offset, ScGsCfg.Data);

      //
      // Set the MC to ECC mode for all channels if needed.
      //
      if (Outputs->EccSupport == TRUE) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ECC support\n");
        Offset = MCDECS_CR_MAD_INTRA_CH0_MCMAIN_REG + ((MCDECS_CR_MAD_INTRA_CH1_MCMAIN_REG - MCDECS_CR_MAD_INTRA_CH0_MCMAIN_REG) * Channel);
        MadIntra.Data      = MrcReadCR (MrcData, Offset);
        MadIntra.Bits.ECC = emBothActive;
        MrcWriteCR (MrcData, Offset, MadIntra.Data);
      }
    }
  }

  //
  // Switch MC to Normal Mode, configure Power Down mode
  //
  MrcNormalMode (MrcData);

  //
  // Check if LPDDR3 memory is used
  //
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);

  //
  // Update Odt timing, Samp timing and SlaveDLL to minimize power
  // @todo TAT step is skipped on LPDDR for now.
  //
  if ((Inputs->TrainingEnables.TAT == 0) || Lpddr) {
    UpdateSampOdtTiming (MrcData, 1); // Use guardband of 1, as 0 is too aggressive sometimes
  }

  if (Lpddr) {
    //
    // Enable the OdtSampExtendEn feature for Lpddr
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
      IntChannelOut->DqControl0.Bits.OdtSampExtendEn = 1;
      Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
      MrcWriteCrMulticast (MrcData, Offset, IntChannelOut->DqControl0.Data);
    }
  }

  UpdateSlaveDLLLength (MrcData);

  //
  // Program RxClkStgNum
  //
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
      MaxRcvEn   = 0;
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MaxRcvEn = (UINT8) MAX (MaxRcvEn, ChannelOut->RcvEn[Rank][Byte] / 64);
        }
      }
      RcvEnDrift   = (Lpddr) ? (UINT8) ((tDQSCK_DRIFT + Outputs->Qclkps - 1) / Outputs->Qclkps) : 1;
      RcvEnTurnOff = MaxRcvEn + (5 - 6) + 1 + 7 + 3 + 3 + 2 + (2 * RcvEnDrift);
      if (IntChannelOut->DqControl1[0].Bits.LpDdrLongOdtEn) {
        RcvEnTurnOff ++;
      }

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        RcvEnTurnOff = MIN (RcvEnTurnOff, DDRDATA_CR_DDRCRDATACONTROL2_RxClkStgNum_MAX);

        OdtTurnOff = MrcSE ((UINT8) IntChannelOut->DqControl1[Byte].Bits.OdtDelay, 4, 8) +
          (UINT8) IntChannelOut->DqControl1[Byte].Bits.OdtDuration + 14;
        OdtTurnOff = MIN (OdtTurnOff, DDRDATA_CR_DDRCRDATACONTROL2_RxClkStgNum_MAX);

        IntChannelOut->DqControl2[Byte].Bits.RxClkStgNum = (IntChannelOut->DqControl0.Bits.OdtSampExtendEn) ?
          MAX (IntChannelOut->DqControl2[Byte].Bits.RxClkStgNum, RcvEnTurnOff) : MAX (17, OdtTurnOff);
        Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
        MrcWriteCR (MrcData, Offset, IntChannelOut->DqControl2[Byte].Data);
      }
    }
  }
  //
  // Program DDRPL_CR_DDR_TX_DELAY if Memory Trace is enabled
  //
  MrcSetDdrplTxDelay (MrcData);

  //
  // Set Idle timer and Self Refresh enable bits
  //
  EnterSR (MrcData);

  //
  // Oem hook when normal mode configuration is done.
  //
  MrcInternalCheckPoint (MrcData, OemAfterNormalMode, (void *) &Inputs->McLock);
  
  // Update Turnarounds Output Structure with Final Values.
  MrcUpdateTatOutputs (MrcData);

#ifdef UP_SERVER_FLAG
  if (Inputs->BoardType != btUpServer) {
#endif
    if (Inputs->UserPowerWeightsEn == 0) {
      //
      // Apply power weight values
      //
      MrcPowerWeight (MrcData);
    }
#ifdef UP_SERVER_FLAG
  } else{
    if ((Inputs->UserPowerWeightsEn == 0) || (Inputs->UserBudgetEnable == 0) || (Inputs->TsodManualEnable == 0) || (Inputs->UserThresholdEnable == 0)) {
      //
      // Apply Budget, Power Weights , Thermal Threshold, TSOD register values according to DIMM(s) features
      //
      MrcUpPowerWeightAndTsod (MrcData);
    }
  }
#endif

  MrcBerSetup (MrcData);
  return mrcSuccess;
}

/**
  This function enables Normal Mode and configures the Power Down Modes.
  We also have special flow here for SAGV in S3/Warm boot modes.

  @param[in] MrcData - The MRC general data.

  @retval Always returns mrcSuccess.
**/
MrcStatus
MrcNormalMode (
  IN MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION  *MrcCall;
  const MrcInput      *Inputs;
  MrcOutput           *Outputs;
  UINT8               Channel;
  UINT32              Offset;
  UINT32              MrParams[MAX_CHANNEL];
  UINT32              SecondCbit;
  UINT64              Timeout;
  BOOLEAN             SaGvAndSelfRefresh;
  BOOLEAN             Flag;
  MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT ReutChSeqCfg;
  MCDECS_CR_STALL_DRAIN_MCMAIN_STRUCT       StallDrain;
  MCSCHEDS_CR_SCHED_SECOND_CBIT_STRUCT      SchedSecondCbit;
  MCHBAR_CH0_CR_DDR_MR_PARAMS_STRUCT        DdrMrParams;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcCall = Inputs->Call.Func;

  SecondCbit = 0;
  MrcCall->MrcSetMem ((UINT8 *) MrParams, sizeof (MrParams), 0);

  //
  // Check if SAGV is enabled and memory is in Self-Refresh right now (Warm reset or S3 resume)
  //
  SaGvAndSelfRefresh = (Inputs->SaGv == MrcSaGvEnabled) && (Inputs->BootMode != bmCold) && (Inputs->BootMode != bmFast);
  if (SaGvAndSelfRefresh) {
    //
    // Disable MR4 reads before going to Normal Mode (which will exit SelfRefresh):
    // 1. SCHED_SECOND_CBIT.dis_srx_mr4 = 1
    // 2. SCHED_SECOND_CBIT.dis_SRX_MRS_MR4 = 1
    // 3. DDR_MR_PARAMS.MR4_PERIOD = 0
    // 4. DDR_MR_PARAMS.DDR4_TS_readout_en = 0
    //
    SchedSecondCbit.Data = MrcReadCR (MrcData, MCHBAR_CH0_CR_SCHED_SECOND_CBIT_REG);
    SecondCbit = SchedSecondCbit.Data;                    // Backup the current value
    SchedSecondCbit.Bits.dis_srx_mr4 = 1;
    SchedSecondCbit.Bits.dis_SRX_MRS_MR4 = 1;
    MrcWriteCrMulticast (MrcData, MCSCHEDS_CR_SCHED_SECOND_CBIT_REG, SchedSecondCbit.Data);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      Offset = MCHBAR_CH0_CR_DDR_MR_PARAMS_REG +
        (MCHBAR_CH1_CR_DDR_MR_PARAMS_REG - MCHBAR_CH0_CR_DDR_MR_PARAMS_REG) * Channel;
      DdrMrParams.Data = MrcReadCR (MrcData, Offset);
      MrParams[Channel] = DdrMrParams.Data;               // Backup the current value
      DdrMrParams.Bits.MR4_PERIOD = 0;
      DdrMrParams.Bits.DDR4_TS_readout_en = 0;
      MrcWriteCR (MrcData, Offset, DdrMrParams.Data);
    }
  }

  //
  // Set Normal Operation Mode
  // Write to both channels, we need to set this even if a channel is not populated, due to MC requirements for SAGV.
  //
  ReutChSeqCfg.Data                     = 0;
  ReutChSeqCfg.Bits.Initialization_Mode = NOP_Mode;
  MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG, (UINT32) ReutChSeqCfg.Data);
  MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG, (UINT32) ReutChSeqCfg.Data);

  //
  // Poll until MCDECS_CR_STALL_DRAIN_MCMAIN_STRUCT.sr_state becomes zero (DDR is not in self-refresh)
  //
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000; // 10 seconds timeout
  do {
    StallDrain.Data = MrcReadCR (MrcData, MCDECS_CR_STALL_DRAIN_MCMAIN_REG);
    Flag            = (StallDrain.Bits.sr_state == 1);
  } while (Flag && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  if (Flag) {
    return mrcFail;
  }

  if (SaGvAndSelfRefresh) {
    //
    // Program DRAM MRs to match the High point
    //
    MrcProgramMrsFsm (MrcData);

    //
    // Re-enable MR4 reads
    //
    MrcWriteCrMulticast (MrcData, MCSCHEDS_CR_SCHED_SECOND_CBIT_REG, SecondCbit);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      Offset = MCHBAR_CH0_CR_DDR_MR_PARAMS_REG +
        (MCHBAR_CH1_CR_DDR_MR_PARAMS_REG - MCHBAR_CH0_CR_DDR_MR_PARAMS_REG) * Channel;
      MrcWriteCR (MrcData, Offset, MrParams[Channel]);
    }
  }

  //
  // Configure Power Down CR
  //
  MrcPowerDownConfig (MrcData);

  return mrcSuccess;
}

/**
  SA GV flow for the cold boot

  @param[in] MrcData - include all the MRC general data.

  @retval mrcStatus if succeeded.
**/
MrcStatus
MrcSaGvSwitch (
  IN     MrcParameters *const MrcData
  )
{
  MrcInput                                *Inputs;
  MrcDebug                                *Debug;
  const MRC_FUNCTION                      *MrcCall;
  MrcIntOutput                            *MrcIntData;
  MrcOutput                               *Outputs;
  MrcStatus                               Status;
  BOOLEAN                                 Busy;
  MCDECS_CR_MC_INIT_STATE_G_MCMAIN_STRUCT McInitStateG;
  MCDECS_CR_STALL_DRAIN_MCMAIN_STRUCT     StallDrain;
  UINT64                                  Timeout;
  UINT8                                   PowerDownModeSave;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  //
  // At this point the MC is in Normal mode with Refreshes enabled
  //

  McInitStateG.Data = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000; // 10 seconds timeout

  if (MrcIntData->SaGvPoint == MrcSaGvPointLow) {
    //
    // Disable CKE Power Down
    //
    PowerDownModeSave = Inputs->PowerDownMode;
    Inputs->PowerDownMode = pdmNoPowerDown;
    MrcPowerDownConfig (MrcData);
    Inputs->PowerDownMode = PowerDownModeSave;

    //
    // Save the LOW point, enable refreshes
    //
    McInitStateG.Bits.mrc_save_low   = 1;
    McInitStateG.Bits.refresh_enable = 1;
    MrcWriteCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG, McInitStateG.Data);
    //
    // Poll for acknowledgement
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Waiting for SAGV LOW point save acknowledge\n");
    do {
      McInitStateG.Data = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
      Busy = (McInitStateG.Bits.mrc_save_low == 1);
    } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

    if (Busy) {
      return mrcDeviceBusy;
    }

    //
    // Wait for MC to get into Self-Refresh
    // Poll until MCDECS_CR_STALL_DRAIN_MCMAIN_STRUCT.sr_state becomes '1' (DDR is in self-refresh)
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Waiting for MC to enter self-refresh\n");
    do {
      StallDrain.Data = MrcReadCR (MrcData, MCDECS_CR_STALL_DRAIN_MCMAIN_REG);
    } while (StallDrain.Bits.sr_state == 0);
  } else {
    //
    // Save the HIGH point
    //
    McInitStateG.Bits.mrc_save_high = 1;
    MrcWriteCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG, McInitStateG.Data);
    //
    // Poll for acknowledgement
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Waiting for SAGV HIGH point save acknowledge\n");
    do {
      McInitStateG.Data = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
      Busy = (McInitStateG.Bits.mrc_save_high == 1);
    } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

    if (Busy) {
      return mrcDeviceBusy;
    }
  }

  return Status;
}

/**
  SA GV flow for the FixedLow mode.

  @param[in] MrcData - include all the MRC general data.

  @retval mrcStatus if succeeded.
**/
MrcStatus
MrcSetFixedLow (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput                          *Inputs;
  MrcDebug                                *Debug;
  const MRC_FUNCTION                      *MrcCall;
  MrcOutput                               *Outputs;
  MrcStatus                               Status;
  BOOLEAN                                 Busy;
  MCDECS_CR_MC_INIT_STATE_G_MCMAIN_STRUCT McInitStateG;
  UINT64                                  Timeout;
  UINT32                                  Data32;
  UINT32                                  MailboxStatus;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;

  //
  // Save the current point as both Low and High
  //

  McInitStateG.Data = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000; // 10 seconds timeout

  McInitStateG.Bits.mrc_save_low   = 1;
  MrcWriteCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG, McInitStateG.Data);
  //
  // Poll for acknowledgement
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Waiting for SAGV LOW point save acknowledge\n");
  do {
    McInitStateG.Data = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
    Busy = (McInitStateG.Bits.mrc_save_low == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  if (Busy) {
    return mrcDeviceBusy;
  }

  McInitStateG.Bits.mrc_save_high = 1;
  MrcWriteCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG, McInitStateG.Data);
  //
  // Poll for acknowledgement
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Waiting for SAGV HIGH point save acknowledge\n");
  do {
    McInitStateG.Data = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
    Busy = (McInitStateG.Bits.mrc_save_high == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  if (Busy) {
    return mrcDeviceBusy;
  }

  //
  // Set the Low point via CPU Mailbox
  //
  Data32 = 0;
  MrcCall->MrcCpuMailboxWrite (MAILBOX_TYPE_PCODE, CPU_MAILBOX_CMD_SAGV_SET_POLICY, Data32, &MailboxStatus);
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "CPU_MAILBOX_CMD_SAGV_SET_POLICY %s. MailboxStatus = %Xh\n",
    (MailboxStatus == PCODE_MAILBOX_CC_SUCCESS) ? "success" : "failed",
    MailboxStatus
    );

  return Status;
}

/**
  Energy Performance Gain.

  @param[in]  MrcData - Pointer to the MRC global data structure

  @retval - Status.
**/
MrcStatus
MrcEnergyPerfGain (
  IN MrcParameters *const MrcData
  )
{
  MrcStatus           Status;
  const MRC_FUNCTION  *MrcCall;
  const MrcInput      *Inputs;
  MrcOutput           *Outputs;
  MrcIntOutput        *MrcIntData;
  MrcDebug            *Debug;
  UINT32              MailboxStatus;
  UINT8               Index;
  UINT16              MilliWatt[2];
  UINT16              Data[2];

  MrcCall  = MrcData->Inputs.Call.Func;
  Debug    = &MrcData->Outputs.Debug;
  Inputs   = &MrcData->Inputs;
  Outputs  = &MrcData->Outputs;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  Status  = mrcSuccess;

  if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint == MrcSaGvPointLow)) {
    //
    // Do nothing.
    //
  } else {
    //
    // If enabled, set up EPG.
    //
    if (Inputs->EpgEnable == 1) {
      for (Index = 0; Index < 2; Index++) {
        //
        // Calculate the 3 parameters (mW):  (Idd3x * Vdd * number of DIMMs present in the system) / 1000.
        //
        MilliWatt[Index] =
          (UINT16) ((((Index == 0) ? (Inputs->Idd3n) : (Inputs->Idd3p))
          * (Outputs->VddVoltage[Inputs->MemoryProfile]) * (Outputs->Controller[0].Channel[0].DimmCount
          + Outputs->Controller[0].Channel[1].DimmCount)) / 1000);
        //
        // Convert to fixed point 8.8 value.  Integer8.8 = (milliwatts / 1000) * 2^8
        //
        Data[Index] = MilliWatt[Index] * 256 / 1000;
        //
        // Write to mailbox register.
        //
        if (MrcCall->MrcCpuMailboxWrite != NULL) {
          MrcCall->MrcCpuMailboxWrite (
                     MAILBOX_TYPE_PCODE,
                     ((Index == 0) ? SET_EPG_BIOS_POWER_OVERHEAD_0_CMD : SET_EPG_BIOS_POWER_OVERHEAD_1_CMD),
                     Data[Index], &MailboxStatus);
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "SET_EPG_BIOS_POWER_OVERHEAD_%d_CMD %s. Value = %08Xh. MailboxStatus = %Xh\n",
            Index,
            (MailboxStatus == PCODE_MAILBOX_CC_SUCCESS) ? "success" : "failed",
            Data[Index],
            MailboxStatus);
        }  // Write to mailbox register.
      }  // for loop
    }  // EpgEnable
  }  // else
  return Status;
}

/**
  this function is the last funtion that call from the MRC core.
    the function set DISB and set the MRC_Done.

  @param[in] MrcData - include all the MRC general data.

  @retval Always returns mrcSuccess.
**/
MrcStatus
MrcDone (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput                          *Inputs;
  const MRC_FUNCTION                      *MrcCall;
  MrcDebug                                *Debug;
  MrcIntOutput                            *MrcIntData;
  MrcOutput                               *Outputs;
  UINT64                                  Timeout;
  BOOLEAN                                 Flag;
  MCDECS_CR_MC_INIT_STATE_G_MCMAIN_STRUCT McInitStateG;
  PCU_CR_M_COMP_PCU_STRUCT                MCompPcu;

  Inputs  = &MrcData->Inputs;
  Debug   = &MrcData->Outputs.Debug;
  Outputs = &MrcData->Outputs;
  MrcCall = Inputs->Call.Func;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  //
  // If SA GV is enabled, only run MrcDone at HIGH point.
  //
  if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint == MrcSaGvPointLow)) {
    return mrcSuccess;
  }

  if (Inputs->SaGv == MrcSaGvFixedLow) {
    MrcSetFixedLow (MrcData);
  }

  MrcBerActivate (MrcData);

  McInitStateG.Data = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
  //
  // Set refresh enable Bit
  //
  McInitStateG.Bits.refresh_enable = 1;

  //
  // used to know what is the state of the boot mode.
  //
  McInitStateG.Bits.pu_mrc_done = 1;

  //
  // set the MRC_Done bit.
  //
  McInitStateG.Bits.mrc_done = 1;

  MrcWriteCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG, McInitStateG.Data);

  //
  // lock the MC and memory map registers.
  //
  McRegistersLock (MrcData);

  //
  // Wait for PCODE to set mc_init_done_ack
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Waiting for mc_init_done Acknowledge\n");
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000; // 10 seconds timeout
  do {
    McInitStateG.Data = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
    Flag = (McInitStateG.Bits.mc_init_done_ack == 0);
  } while (Flag && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  if (Flag) {
    return mrcFail;
  }

  //
  // Enable Periodic Comp with periodic interval = 10uS*2^COMP_INT
  //
  MCompPcu.Data               = 0;
  MCompPcu.Bits.COMP_INTERVAL = COMP_INT;
  MrcWriteCR (MrcData, PCU_CR_M_COMP_PCU_REG, MCompPcu.Data);

  MrcWriteCR64 (MrcData, PCU_CR_SSKPD_PCU_REG, 1); // We use this register to indicate "MRC done"

  return mrcSuccess;
}

/**
  Print the MRC version to the MRC output device.

  @param[in] Debug   - Pointer to the MRC Debug structure.
  @param[in] Version - The MRC version.

  @retval Nothing.
**/
void
MrcVersionPrint (
  IN MrcParameters     *MrcData,
  IN const MrcVersion  *Version
  )
{
#ifdef MRC_DEBUG_PRINT
  const MrcInput *Inputs;
  MrcDebug *Debug;

  Inputs   = &MrcData->Inputs;
  Debug    = &MrcData->Outputs.Debug;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "*********************************************************************\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "** Copyright (c) 2011-2015 Intel Corporation. All rights reserved. **\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "** %sylake memory detection and initialization code.              **\n", (Inputs->CpuFamily == cfKbl) ? "Kab" : "Sk");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "** Major version number is:   %2u                                  **\n", Version->Major);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "** Minor version number is:   %2u                                  **\n", Version->Minor);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "** Rev version number is:     %2u                                  **\n", Version->Rev);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "** Build number is:           %2u                                  **\n", Version->Build);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "*********************************************************************\n");
#endif
  return;
}

/**
  This function return the MRC version.

  @param[in] MrcData - Include all MRC global data.
  @param[out] Version - Location to store the MRC version.

  @retval Nothing.
**/
void
MrcVersionGet (
  IN  const MrcParameters *const MrcData,
  OUT MrcVersion *const Version
  )
{
  const MrcInput     *Inputs;
  const MRC_FUNCTION *MrcCall;

  if (Version != NULL) {
    Inputs  = &MrcData->Inputs;
    MrcCall = Inputs->Call.Func;
    MrcCall->MrcCopyMem ((UINT8 *) Version, (UINT8 *) &cVersion[Inputs->CpuFamily], sizeof (MrcVersion));
  }
}

/**
  This function set the MRC vertion to MCDECS_SPARE register.
  The function need to be call by the wrapper after MrcStartMemoryConfiguration function where the MC CLK enable.
  The function write:
  Major number to bits 16-23
  Minor number to bits 8-15
  Build number to bits 0 - 7

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
MrcStatus
MrcSetMrcVersion (
  IN     MrcParameters *const MrcData
  )
{
  MrcVersion const                      *Version;
  MCDECS_CR_MRC_REVISION_MCMAIN_STRUCT  MrcRevision;

  Version = &MrcData->Outputs.Version;
  MrcRevision.Data =
    (((UINT32) Version->Major) << 24) |
    (((UINT32) Version->Minor) << 16) |
    (((UINT32) Version->Rev)   << 8)  |
    (((UINT32) Version->Build));

  MrcWriteCR (MrcData, MCDECS_CR_MRC_REVISION_MCMAIN_REG, MrcRevision.Data);
  return mrcSuccess;
}

/**
  This function locks the memory controller and memory map registers.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
McRegistersLock (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput                          *Inputs;
  const MRC_FUNCTION                      *MrcCall;
  MrcDebug                                *Debug;
  MCDECS_CR_MC_LOCK_MCMAIN_STRUCT         McLock;
  UNCORE_CR_TOM_0_0_0_PCI_STRUCT          Tom;
  UNCORE_CR_TOLUD_0_0_0_PCI_STRUCT        Tolud;
  UNCORE_CR_TOUUD_0_0_0_PCI_STRUCT        Touud;
  UNCORE_CR_REMAPBASE_0_0_0_PCI_STRUCT    RemapBase;
  UNCORE_CR_REMAPLIMIT_0_0_0_PCI_STRUCT   RemapLimit;
  UNCORE_CR_BDSM_0_0_0_PCI_STRUCT         Bdsm;
  UNCORE_CR_BGSM_0_0_0_PCI_STRUCT         Bgsm;
  UNCORE_CR_MESEG_MASK_0_0_0_PCI_STRUCT   MeSegMask;
  UNCORE_CR_GGC_0_0_0_PCI_STRUCT          Ggc;
  UNCORE_CR_DPR_0_0_0_PCI_STRUCT          Dpr;
  PCU_CR_DDR_PTM_CTL_PCU_STRUCT           DdrPtmCtl;
  UINT32                                  Offset;
  UINT32                                  PciEBaseAddress;

  Debug   = &MrcData->Outputs.Debug;
  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  PciEBaseAddress = Inputs->PciEBaseAddress;

  //
  // Lock the memory controller registers.
  //
  McLock.Data                   = 0;
  McLock.Bits.lock_addr_map     = 1;
  McLock.Bits.lock_mc_config    = 1;
  McLock.Bits.lock_iosav_init   = 1;
  McLock.Bits.lock_pwr_mngment  = 1;
  McLock.Bits.lock_mc_dft       = 1;
  MrcWriteCR (MrcData, MCDECS_CR_MC_LOCK_MCMAIN_REG, McLock.Data);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nMemory controller config is locked\n");

  //
  // Lock PRMRR.  Convert from MB to Address.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcSetLockPrmrr: 0x%x\n", MrcCall->MrcSetLockPrmrr);
  MrcCall->MrcSetLockPrmrr (MrcData->Outputs.MemoryMapData.PrmrrBase << 20, Inputs->PrmrrSize << 20);

  if (Inputs->McLock) {
    //
    // Lock the memory map registers.
    // Lock TOM.
    //
    Offset        = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_TOM_0_0_0_PCI_REG);
    Tom.Data32[0] = MrcCall->MrcMmioRead32 (Offset);
    Tom.Bits.LOCK = 1;
    MrcCall->MrcMmioWrite32 (Offset, Tom.Data32[0]);

    //
    // Lock TOLUD.
    //
    Offset          = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_TOLUD_0_0_0_PCI_REG);
    Tolud.Data      = MrcCall->MrcMmioRead32 (Offset);
    Tolud.Bits.LOCK = 1;
    MrcCall->MrcMmioWrite32 (Offset, Tolud.Data);

    //
    // Lock TOUUD.
    //
    Offset          = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_TOUUD_0_0_0_PCI_REG);
    Touud.Data32[0] = MrcCall->MrcMmioRead32 (Offset);
    Touud.Bits.LOCK = 1;
    MrcCall->MrcMmioWrite32 (Offset, Touud.Data32[0]);

    //
    // Lock REMAPBASE.
    //
    Offset              = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_REMAPBASE_0_0_0_PCI_REG);
    RemapBase.Data32[0] = MrcCall->MrcMmioRead32 (Offset);
    RemapBase.Bits.LOCK = 1;
    MrcCall->MrcMmioWrite32 (Offset, RemapBase.Data32[0]);

    //
    // Lock REMAPLIMIT.
    //
    Offset               = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_REMAPLIMIT_0_0_0_PCI_REG);
    RemapLimit.Data32[0] = MrcCall->MrcMmioRead32 (Offset);
    RemapLimit.Bits.LOCK = 1;
    MrcCall->MrcMmioWrite32 (Offset, RemapLimit.Data32[0]);

    //
    // Lock DPR register
    //
    Offset        = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_DPR_0_0_0_PCI_REG);
    Dpr.Data      = MrcCall->MrcMmioRead32 (Offset);
    Dpr.Bits.LOCK = 1;
    MrcCall->MrcMmioWrite32 (Offset, Dpr.Data);

    //
    // Lock BDSM.
    //
    Offset         = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_BDSM_0_0_0_PCI_REG);
    Bdsm.Data      = MrcCall->MrcMmioRead32 (Offset);
    Bdsm.Bits.LOCK = 1;
    MrcCall->MrcMmioWrite32 (Offset, Bdsm.Data);

    //
    // Lock BGSM.
    //
    Offset         = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_BGSM_0_0_0_PCI_REG);
    Bgsm.Data      = MrcCall->MrcMmioRead32 (Offset);
    Bgsm.Bits.LOCK = 1;
    MrcCall->MrcMmioWrite32 (Offset, Bgsm.Data);

    //
    // Lock MESEG_MASK.
    //
    Offset               = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_MESEG_MASK_0_0_0_PCI_REG);
    MeSegMask.Data32[0]  = MrcCall->MrcMmioRead32 (Offset);
    MeSegMask.Bits.MELCK = 1;
    MrcCall->MrcMmioWrite32 (Offset, MeSegMask.Data32[0]);

    //
    // Lock GGC.
    //
    Offset          = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_GGC_0_0_0_PCI_REG);
    Ggc.Data        = (UINT16) MrcCall->MrcMmioRead32 (Offset);
    Ggc.Bits.GGCLCK = 1;
    MrcCall->MrcMmioWrite32 (Offset, Ggc.Data);

    //
    // Lock POWER THERMAL MANAGEMENT CONTROL
    //
    DdrPtmCtl.Data                   = MrcReadCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG);
    DdrPtmCtl.Bits.LOCK_PTM_REGS_PCU = Inputs->LockPTMregs;
    MrcWriteCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG, DdrPtmCtl.Data);

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nMemory map registers are locked\n");
  }

  return;
}

/**
  This function returns the recommended MRC boot mode.

  @param[in] MrcData - The global host structure

  @retval bmWarm if we are in self refresh and the DISB bit is set, otherwise returns bmCold.
**/
MrcBootMode
MrcGetBootMode (
  IN MrcParameters * const MrcData
  )
{
  MrcBootMode BootMode;
  MrcInput     *Inputs;
  MRC_FUNCTION *MrcCall;
  UINT32       Register;
  UINT32       ioAddress;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  ioAddress = (UINT32) MrcCall->MrcGetPciDeviceAddress (
                                  GENERAL_PM_CONFIGURATION_2_BUS_ADDRESS,
                                  GENERAL_PM_CONFIGURATION_2_DEVICE_ADDRESS,
                                  GENERAL_PM_CONFIGURATION_2_FUNCTION_ADDRESS,
                                  GENERAL_PM_CONFIGURATION_2
                                  );

  MrcCall->MrcIoWrite32 (Inputs->PciIndex, ioAddress);

  //
  // We read 32 bits but we need only 8 bits of GENERAL_PM_CONFIGURATION_2 that start at offset 0xA2 and not 0xA0.
  //
  Register = (MrcCall->MrcIoRead32 (Inputs->PciData) >> 16);

  if ((Register & GENERAL_PM_CONFIGURATION_2_MEM_SR_MASK) == GENERAL_PM_CONFIGURATION_2_MEM_SR_MASK &&
      (Register & GENERAL_PM_CONFIGURATION_2_DISB_MASK) == GENERAL_PM_CONFIGURATION_2_DISB_MASK
      ) {
    BootMode = bmWarm;
  } else {
    BootMode = bmCold;
  }

  return BootMode;
}

/**
  This function sets the DISB bit in General PM Configuration.

  @param[in] MrcData - The global host structure

  @retval Nothing.
**/
void
MrcSetDISB (
  IN MrcParameters * const MrcData
  )
{
  MrcInput     *Inputs;
  MRC_FUNCTION *MrcCall;
  UINT32       ioAddress;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  ioAddress = (UINT32) MrcCall->MrcGetPciDeviceAddress (
                                  GENERAL_PM_CONFIGURATION_2_BUS_ADDRESS,
                                  GENERAL_PM_CONFIGURATION_2_DEVICE_ADDRESS,
                                  GENERAL_PM_CONFIGURATION_2_FUNCTION_ADDRESS,
                                  GENERAL_PM_CONFIGURATION_2
                                  );

  //
  // GENERAL_PM_CONFIGURATION_2 is A2[7]. Byte access to not clear other WR/1C bits.
  // All other bits are RO and RW/1C. So only set bit7 = 1.
  //
  MrcCall->MrcIoWrite32 (Inputs->PciIndex, ioAddress);
  MrcCall->MrcIoWrite8 (Inputs->PciData + 2, GENERAL_PM_CONFIGURATION_2_DISB_MASK);
}

/**
  This function resets the DISB bit in General PM Configuration.

  @param[in] MrcData - The global host structure

  @retval Nothing.
**/
void
MrcResetDISB (
  IN MrcParameters * const MrcData
  )
{
  MrcInput     *Inputs;
  MRC_FUNCTION *MrcCall;
  UINT32       ioAddress;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  ioAddress = (UINT32) MrcCall->MrcGetPciDeviceAddress (
                                  GENERAL_PM_CONFIGURATION_2_BUS_ADDRESS,
                                  GENERAL_PM_CONFIGURATION_2_DEVICE_ADDRESS,
                                  GENERAL_PM_CONFIGURATION_2_FUNCTION_ADDRESS,
                                  GENERAL_PM_CONFIGURATION_2
                                  );

  //
  // GENERAL_PM_CONFIGURATION_2 is A2[7]. Byte access to not clear other WR/1C bits.
  // All other bits are RO and RW/1C. So only set bit7 = 0.
  //
  MrcCall->MrcIoWrite32 (Inputs->PciIndex, ioAddress);
  MrcCall->MrcIoWrite8 (Inputs->PciData + 2, 0);
}

/**
  This function reads the CAPID0 register and sets the memory controller's capability.

  @param[in, out] MrcData - All the MRC global data.

  @retval Returns mrcSuccess if the memory controller's capability has been determined, otherwise returns mrcFail.
**/
MrcStatus
MrcMcCapability (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput            *Inputs;
  MrcDebug                  *Debug;
  const MRC_FUNCTION        *MrcCall;
  MrcOutput                 *Outputs;
  MrcControllerOut          *ControllerOut;
  MrcChannelOut             *ChannelOut;
  MrcDimmOut                *DimmOut;
  MrcDdrType                DdrType;
  BOOLEAN                   EccSupport;
  BOOLEAN                   IgnoreNonEccDimm;
  UNCORE_CR_CAPID0_A_0_0_0_PCI_STRUCT Capid0A;
  UNCORE_CR_CAPID0_B_0_0_0_PCI_STRUCT Capid0B;
  UNCORE_CR_DEVEN_0_0_0_PCI_STRUCT    Deven;
  MrcProfile                Profile;
  UINT32                    ChannelCount;
  UINT32                    DimmCount;
  UINT32                    Max;
  UINT32                    Size;
  UINT32                    ChannelNum;
  UINT32                    DimmNum;
  UINT32                    ChDimmCount;
  UINT32                    Offset;
  UINT16                    NModeMinimum;
  UINT8                     Controller;
  UINT8                     Channel;
  UINT8                     Dimm;
  BOOLEAN                   Cmd2N;
  BOOLEAN                   UlxUlt;
  BOOLEAN                   Ddr3;
  BOOLEAN                   Ddr4;
  const char                *StrDdrType;

  Inputs       = &MrcData->Inputs;
  MrcCall      = Inputs->Call.Func;
  Outputs      = &MrcData->Outputs;
  Debug        = &Outputs->Debug;
  ChDimmCount  = MAX_DIMMS_IN_CHANNEL;
  Profile      = Inputs->MemoryProfile;
  DdrType      = Outputs->DdrType;
  UlxUlt       = ((Inputs->CpuModel == cmSKL_ULX_ULT) || (Inputs->CpuModel == cmKBL_ULX_ULT));
  Ddr3         = (DdrType == MRC_DDR_TYPE_DDR3);
  Ddr4         = (DdrType == MRC_DDR_TYPE_DDR4);

  //
  // Obtain the capabilities of the memory controller.
  //
  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_CAPID0_A_0_0_0_PCI_REG);
  Capid0A.Data = MrcCall->MrcMmioRead32 (Offset);

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_CAPID0_B_0_0_0_PCI_REG);
  Capid0B.Data = MrcCall->MrcMmioRead32 (Offset);

  Offset     = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_DEVEN_0_0_0_PCI_REG);
  Deven.Data = MrcCall->MrcMmioRead32 (Offset);

  //
  // Check that current DDR type is allowed on this CPU
  //
  StrDdrType = NULL;
  if (Ddr3 && (Capid0A.Bits.DDR3L_EN == 0)) {
    StrDdrType = "DDR3L";
  } else if (Ddr4 && (Capid0B.Bits.DDR4_EN == 0)) {
    StrDdrType = "DDR4";
  } else if ((DdrType == MRC_DDR_TYPE_LPDDR3) && (Capid0B.Bits.LPDDR3_EN == 0)) {
    StrDdrType = "LPDDR3";
  }

  if (StrDdrType != NULL) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: %s is not supported on this CPU\n", StrDdrType);
    return mrcDimmNotSupport;
  }

  //
  // Determine if the internal graphics engine is supported.
  //
  if ((Capid0A.Bits.IGD == 0) && (Deven.Bits.D2EN > 0)) {
    Outputs->GraphicsStolenSize = Inputs->GraphicsStolenSize;
    Outputs->GraphicsGttSize    = Inputs->GraphicsGttSize;
  } else {
    Outputs->GraphicsStolenSize = 0;
    Outputs->GraphicsGttSize    = 0;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Memory allocated for IGD = %uMB and for GTT = %uMB.\n",
    Outputs->GraphicsStolenSize,
    Outputs->GraphicsGttSize
    );

  //
  // Determine the maximum size of memory per channel, based on fuses.
  //
  switch (Capid0A.Bits.DDRSZ) {
    case tcs32GB:
      Outputs->MrcTotalChannelLimit = (32 * 1024);
      break;

    case tcs8GB:
      Outputs->MrcTotalChannelLimit = (8 * 1024);
      break;

    case tcs4GB:
      Outputs->MrcTotalChannelLimit = (4 * 1024);
      break;

    case tcs2GB:
    default:
      Outputs->MrcTotalChannelLimit = (2 * 1024);
      break;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Maximum size of memory allowed on a channel = %uMB.\n",
    Outputs->MrcTotalChannelLimit
    );

  //
  // Determine how many channels are supported on this memory controller,
  // based on fuse and how many channels have DIMMs installed.
  //
  ChannelCount  = (Capid0A.Bits.PDCD == 0) ? MAX_CHANNEL : 1;
  DimmCount     = (Capid0A.Bits.DDPCD == 0) ? MAX_DIMMS_IN_CHANNEL : 1;

  if ((Inputs->Force1Dpc == TRUE) || UlxUlt) {
    //
    // Only 1DPC is supported on SKL ULX / ULT platform
    //
    DimmCount = 1;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Number of channels supported = %u\nNumber of DIMMs per channel supported = %u\n",
    ChannelCount,
    DimmCount
    );

  //
  // Determine the minimum NMode supported on this memory controller.
  //
  NModeMinimum = (Capid0A.Bits.D1NM == 0) ? 1 : 2;

  //
  // Determine the ECC capability of the memory controller.
  //
  IgnoreNonEccDimm = (Capid0A.Bits.FDEE == 0) ? FALSE : TRUE;

  //
  // Set EccSupport flag to TRUE if we must NOT ignore ECC DIMMs
  //
  if (IgnoreNonEccDimm == TRUE) {
    Outputs->EccSupport = TRUE;
    EccSupport = TRUE; // FDEE has presedence over ECCDIS
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ALL DIMMs MUST be ECC capable\n");
  } else {
    EccSupport = ((Capid0A.Bits.ECCDIS > 0) || (Outputs->EccSupport == FALSE)) ? FALSE : TRUE;
  }
  //
  // Now copy ECC and NMode information to the channel and DIMM results.
  //
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      if (ChannelOut->Status == CHANNEL_PRESENT) {
        Cmd2N = (NModeMinimum == 2);
        if (Inputs->MemoryProfile == STD_PROFILE && (Inputs->NModeSupport == 0)) {
          if ((Ddr4 && (Outputs->Frequency > f2133)) ||
              (Ddr3 && (Outputs->Frequency > f1867)) ||
              (Ddr3 && (ChannelOut->DimmCount >= 2) && (Outputs->Frequency >= f1333)) ||
              (Ddr4 && !UlxUlt && (Outputs->Frequency >= f1333))
              ) {
            Cmd2N = TRUE;
          }
        }
        if (Cmd2N) {
          ChannelOut->Timing[Profile].NMode = MAX (2, ChannelOut->Timing[Profile].NMode);
        }
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DimmOut->Status == DIMM_PRESENT) {
            DimmOut->Timing[Profile].NMode = ChannelOut->Timing[Profile].NMode;
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  %s %u/%u/%u NMode = %u\n",
              CcdString,
              Controller,
              Channel,
              Dimm,
              DimmOut->Timing[Profile].NMode
              );
            if (EccSupport == TRUE) {
              if ((DimmOut->EccSupport == FALSE) && (IgnoreNonEccDimm == TRUE)) {
                DimmOut->Status = DIMM_DISABLED;
                MRC_DEBUG_MSG (
                  Debug,
                  MSG_LEVEL_ERROR,
                  "ERROR: Unsupported configuration, system contains a mix of ECC and Non-ECC DIMMs and FDEE bit is set\n"
                  );
                return mrcUnsupportedTechnology;
              } else if (DimmOut->EccSupport == TRUE) {
                DimmOut->EccSupport = TRUE;
                DimmOut->SdramCount = MAX_SDRAM_IN_DIMM;
              } else {
                DimmOut->SdramCount = MAX_SDRAM_IN_DIMM - 1;
                Outputs->EccSupport = FALSE; // Final ECCSupport must be disabled if one DIMM is NOT capable
              }
            } else {
              DimmOut->EccSupport = FALSE;
              DimmOut->SdramCount = MAX_SDRAM_IN_DIMM - 1;
              Outputs->EccSupport = FALSE; // Final ECCSupport must be disabled if ECCDIS is set
            }
          }
        }
      }
    }
  }

  //
  // Make sure we have the same NMode limit on both channels
  //
  Cmd2N = FALSE;
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (ControllerOut->Channel[Channel].Timing[Profile].NMode == 2) {
        Cmd2N = TRUE;
        break;
      }
    }
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ControllerOut->Channel[Channel].Timing[Profile].NMode = (Cmd2N) ? 2 : 1;
    }
  }

  //
  // Update FInal SdramCount
  //
  Outputs->SdramCount = (Outputs->EccSupport == TRUE) ? MAX_SDRAM_IN_DIMM : (MAX_SDRAM_IN_DIMM - 1);

  //
  // Determine the size of memory in each channel.
  // Also determine the channel with the largest amount.
  //
  Max = ChannelNum = Outputs->MemoryMapData.TotalPhysicalMemorySize = 0;
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      Size        = 0;
      if (ChannelOut->Status == CHANNEL_PRESENT) {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DimmOut->Status == DIMM_PRESENT) {
            Size += DimmOut->DimmCapacity;
          }
        }

        ChannelOut->Capacity = Size;
        if (Size > Max) {
          Max         = Size;
          ChannelNum  = Channel;
          ChDimmCount = ChannelOut->DimmCount;
        } else if ((Size == Max) && (DimmCount == 1)) {
          //
          // Choose channel with least amount of DIMMs if 2DPC is disabled
          //
          if (ChannelOut->DimmCount < ChDimmCount) {
            ChDimmCount = ChannelOut->DimmCount;
            ChannelNum  = Channel;
          }
        }
      }

      Outputs->MemoryMapData.TotalPhysicalMemorySize += ChannelOut->Capacity;
    }
  }

  if (ChannelCount == 1) {
    //
    // Determine which channels are supported on this memory controller.
    // If fused for one channel, we pick the channel with the most memory.
    //
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        if ((ChannelOut->Status == CHANNEL_PRESENT) && (Channel != ChannelNum)) {
          //
          // Disable Channel don't skip DIMM capacity
          //
          MrcChannelDisable (MrcData, (UINT8) Channel, 0);
        }
      }

      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "Controller configured to one channel, we've selected channel %u.\n",
        ChannelNum
        );
    }
  }

  if (DimmCount == 1) {
    //
    // Determine which DIMMs are supported on this memory controller.
    // If fused for one DIMM per channel, we pick the DIMM in a channel with the most memory.
    //
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        Max                   = Size = DimmNum = 0;
        if (ChannelOut->Status == CHANNEL_PRESENT) {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            DimmOut = &ChannelOut->Dimm[Dimm];
            if (DimmOut->Status == DIMM_PRESENT) {
              Size = DimmOut->DimmCapacity;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%uD%uDimmCapacity = 0x%x\n", Channel, Dimm, DimmOut->DimmCapacity);
              if (Size > Max) {
                Max     = Size;
                DimmNum = Dimm;
              }
            }
          }

          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            DimmOut = &ChannelOut->Dimm[Dimm];
            if ((DimmOut->Status == DIMM_PRESENT) && (Dimm != DimmNum)) {
              DimmOut->Status = DIMM_DISABLED;
            }
          }

          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "Controller configured to one DIMM per channel, we've selected channel %u, Dimm %u.\n",
            Channel,
            DimmNum
            );
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ValidRankBitMask = 0x%x\n", ChannelOut->ValidRankBitMask);
        }
      }
    }
  }

  //
  // Now that we know the enabled and disabled DIMM/Channel population,
  // determine if all enabled DIMMS support ASR.
  //
  // It is necessary to have all DIMMS in ASR or no DIMMS in ASR
  // when enabling 2x Refresh.
  //
  if (Inputs->RhPrevention) {
    Outputs->AutoSelfRefresh = TRUE;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      if (ControllerOut->Status == CONTROLLER_PRESENT) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          ChannelOut = &ControllerOut->Channel[Channel];
          if (ChannelOut->Status == CHANNEL_PRESENT) {
            for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
              DimmOut = &ChannelOut->Dimm[Dimm];
              if ((DimmOut->Status == DIMM_PRESENT) && (DimmOut->AutoSelfRefresh == FALSE)) {
                MRC_DEBUG_MSG (
                  Debug,
                  MSG_LEVEL_NOTE,
                  "Channel %d, Dimm %d does not support Auto Self Refresh.  Disabling ASR since 2x Refresh is enabled!\n",
                  Channel,
                  Dimm
                  );
                Outputs->AutoSelfRefresh = FALSE;
              }
            }
          }
        }
      }
    }
  }

  return mrcSuccess;
}

/**
  This function reads the CAPID0 register and sets the following values
  according to memory controller's capability and user input:
    Outputs->RefClk
    Outputs->FreqMax
    Outputs->Capable100
    Outputs->MemoryClockMax

  @param[in, out] MrcData - All the MRC global data.

  @retval Always returns mrcSuccess.
**/
MrcStatus
MrcMcCapabilityPreSpd (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput            *Inputs;
  const MRC_FUNCTION        *MrcCall;
  const MrcSpd              *SpdIn;
  MrcDebug                  *Debug;
  MrcOutput                 *Outputs;
  MrcIntOutput              *IntOutputs;
  MrcFrequency              FreqMax;
  MrcFrequency              FreqMax100;
  MrcFrequency              FreqMax133;
  MrcRefClkSelect           RefClk;
  MrcClockRatio             MaxRatio100;
  MrcClockRatio             MaxRatio133;
  MrcDdrType                DdrType;
  BOOLEAN                   OverclockCapable;
  BOOLEAN                   OverclockEnabled;
  BOOLEAN                   ExtendedDdrOverclock;
  BOOLEAN                   FirstDimm;
  UINT32                    Capable100;
  UINT32                    Capable133;
  UINT32                    Offset;
  MrcControllerOut          *ControllerOut;
  MrcChannelOut             *ChannelOut;
  MrcDimmOut                *DimmOut;
  UINT8                     Controller;
  UINT8                     Channel;
  UINT8                     Dimm;
  BOOLEAN                   Is2DPC;
  UINT8                     Ddr4ModulePartNumber[SPD4_MODULE_PART_NUMBER_SIZE];
  UNCORE_CR_CAPID0_A_0_0_0_PCI_STRUCT Capid0A;
  UNCORE_CR_CAPID0_B_0_0_0_PCI_STRUCT Capid0B;
  UNCORE_CR_CAPID0_C_0_0_0_PCI_STRUCT Capid0C;
  const SPD4_MANUFACTURING_DATA       *ManufactureData;
#ifdef MRC_DEBUG_PRINT
  UINT32                    Data32;
#endif

  Inputs     = &MrcData->Inputs;
  MrcCall    = Inputs->Call.Func;
  Outputs    = &MrcData->Outputs;
  Debug      = &Outputs->Debug;
  IntOutputs = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  DdrType    = Outputs->DdrType;
  ExtendedDdrOverclock = FALSE;

  //
  // Obtain the capabilities of the memory controller.
  //
  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_CAPID0_A_0_0_0_PCI_REG);
  Capid0A.Data = MrcCall->MrcMmioRead32 (Offset);

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_CAPID0_B_0_0_0_PCI_REG);
  Capid0B.Data = MrcCall->MrcMmioRead32 (Offset);

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_CAPID0_C_0_0_0_PCI_REG);
  Capid0C.Data = MrcCall->MrcMmioRead32 (Offset);

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "CAPID0_A: %08Xh\nCAPID0_B: %08Xh\nCAPID0_C: %08Xh\n",
    Capid0A.Data,
    Capid0B.Data,
    Capid0C.Data
    );

  //
  // Determine the maximum memory frequency supported and the memory reference clock.
  //
  switch (DdrType) {
    case MRC_DDR_TYPE_DDR4:
      Capable133 = Capid0C.Bits.DMFC_DDR4;
      break;

    case MRC_DDR_TYPE_LPDDR3:
      Capable133 = Capid0C.Bits.DMFC_LPDDR3;
      break;

    case MRC_DDR_TYPE_DDR3:
    default:
      Capable133 = Capid0B.Bits.DMFC_DDR3;
  }
#ifdef MRC_DEBUG_PRINT
  Data32 = (11 - Capable133) * 266666;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DMFC: %u\n", (Capable133 == 0) ? 2667 : DIVIDEROUND (Data32, 1000));
#endif

  OverclockCapable = (Capid0A.Bits.DDR_OVERCLOCK > 0) ? TRUE : FALSE;
  OverclockEnabled = OverclockCapable;
  Capable100       = Capid0B.Bits.PLL_REF100_CFG;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_OVERCLOCK: %d, PLL_REF100_CFG: %d\n", OverclockCapable, Capable100);

  if ((Inputs->CpuModel == cmKBL_DT_HALO) && (Inputs->CpuStepping >= csKblN0)) {
    Outputs->ExtendedDdrOverclock = OverclockCapable;
    ExtendedDdrOverclock = OverclockCapable;
    OverclockEnabled = OverclockCapable && (Inputs->OcSupport == 1);
  }

  Outputs->RefClk  = Inputs->RefClk;
  Outputs->FreqMax = ((Inputs->FreqMax > fNoInit) && (Inputs->FreqMax < fInvalid)) ? Inputs->FreqMax : ((ExtendedDdrOverclock) ?  MAX_FREQ_OC_EXT_133 : MAX_FREQ_OC_133);

  if (Capable100 == 0) {
    Outputs->RefClk = MRC_REF_CLOCK_133;
  }

  RefClk = Outputs->RefClk;
  if (OverclockCapable) {
    Capable133 = 0;
    if (Capable100 > 0) {
      Capable100 = UNCORE_CR_CAPID0_B_0_0_0_PCI_PLL_REF100_CFG_MAX;
      Outputs->Capable100 = TRUE;
    }
  }

  MaxRatio100 = (MrcClockRatio) (Capable100 + 6);                           // Unlimited gives 7 + 6 = 13 --> 13 * 200 = 2600
  MaxRatio133 = (MrcClockRatio) ((Capable133 == 0) ? 10 : 11 - Capable133); // Unlimited gives 10 * 266 = 2667

  Outputs->MixedUDimmConfig2Dpc = FALSE;
  Is2DPC = FALSE;

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      if (ChannelOut->DimmCount == 2) {
        Is2DPC = TRUE;
      }
      FirstDimm = TRUE;
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        SpdIn = &Inputs->Controller[0].Channel[Channel].Dimm[Dimm].Spd.Data;
        ManufactureData = &SpdIn->Ddr4.ManufactureInfo;
        DimmOut = &ChannelOut->Dimm[Dimm];
        if ((DimmOut->Status == DIMM_PRESENT) && (DdrType == MRC_DDR_TYPE_DDR4) && (DimmOut->ModuleType == UDimmMemoryPackage)) {
          if (FirstDimm) {
            MrcCall->MrcCopyMem ((UINT8 *) &Ddr4ModulePartNumber[0], (UINT8 *) &(ManufactureData->ModulePartNumber.ModulePartNumber[0]), SPD4_MODULE_PART_NUMBER_SIZE);
            FirstDimm = FALSE;
          } else {
            if (Mrcstrncmp ((const char *) Ddr4ModulePartNumber, (const char *) ManufactureData->ModulePartNumber.ModulePartNumber, SPD4_MODULE_PART_NUMBER_SIZE) != 0) {
              Outputs->MixedUDimmConfig2Dpc = TRUE;
            }
          }
        }
      }
    }
  }

  if (Inputs->CpuModel == cmKBL_DT_HALO) {
    if (Inputs->CpuStepping < csKblN0) {
      if ((Capable133 != 0) && (MaxRatio133 == (MrcClockRatio) 10)) {
        if (Is2DPC) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Limiting DMFC in systems with 2DPC\n");
          MaxRatio133--;
        }
      }
    } else {
      if (Inputs->Ddr4MixedUDimm2DpcLimit && !OverclockEnabled && Outputs->MixedUDimmConfig2Dpc && (MaxRatio133 == (MrcClockRatio) 10)) {
        MaxRatio133 = 9;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING! 2667 Frequency is only allowed for homogeneous 2DPC memory configurations, reducing to 2400\n");
      }
    }
  }

  FreqMax100  = (Capable100 == 0) ? fNoInit : MrcRatioToFrequency (MrcData, MaxRatio100, MRC_REF_CLOCK_100, BCLK_DEFAULT);
  FreqMax133  = MrcRatioToFrequency (MrcData, MaxRatio133, MRC_REF_CLOCK_133, BCLK_DEFAULT);
  //
  // If overclocking is supported, then there is no frequency limitation, otherwise check for limitation.
  // Note 1: If we are using standard memory profile, DIMMS should run at RefClk 133.
  // Note 2: If the 2 values are equal, then we want to pick RefClk 133.
  //

  if (Inputs->MemoryProfile == STD_PROFILE) {
    FreqMax = (OverclockEnabled) ? ((ExtendedDdrOverclock) ?  MAX_FREQ_OC_EXT_133 : MAX_FREQ_OC_133) : FreqMax133;
    RefClk  = MRC_REF_CLOCK_133;
  } else {
    if (OverclockEnabled) {
      if (ExtendedDdrOverclock) {
        FreqMax = (RefClk == MRC_REF_CLOCK_100) ? MAX_FREQ_OC_EXT_100 : MAX_FREQ_OC_EXT_133;
      } else {
        FreqMax = (RefClk == MRC_REF_CLOCK_100) ? MAX_FREQ_OC_100 : MAX_FREQ_OC_133;
      }
    } else if (FreqMax100 > FreqMax133) {
      FreqMax = FreqMax100;
      RefClk  = MRC_REF_CLOCK_100;
    } else {
      FreqMax = FreqMax133;
      RefClk  = MRC_REF_CLOCK_133;
    }
  }

  if (FreqMax < Outputs->FreqMax) {
    Outputs->FreqMax  = FreqMax;
    Outputs->RefClk   = RefClk;
  }

  if (((Inputs->SaGv == MrcSaGvEnabled) && (IntOutputs->SaGvPoint == MrcSaGvPointLow)) ||
      (Inputs->SaGv == MrcSaGvFixedLow)) {
    //
    // Set the LOW point for SA GV
    //
    if (Inputs->FreqSaGvLow != 0) { // 0 means Auto
      Outputs->FreqMax = Inputs->FreqSaGvLow;
    } else {
      Outputs->FreqMax = (DdrType == MRC_DDR_TYPE_DDR4) ? f1333 : f1067;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SAGV Low point\n");
  }

  Outputs->MemoryClockMax = ConvertFreq2Clock (MrcData, Outputs->FreqMax);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "The maximum memory frequency allowed is %u, tCK=%ufs\n", Outputs->FreqMax, Outputs->MemoryClockMax);
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "%uMHz reference clock is selected\n",
    (Outputs->RefClk == MRC_REF_CLOCK_133) ? 133 : 100
    );

  return mrcSuccess;
}

/**
  This function sets the appropriate timing overrides in the output structure
  prior to Spd processing.

  @param[in, out] MrcData - All the MRC global data.

  @retval Returns mrcSuccess if the timing overrides have been completed.
**/
MrcStatus
MrcSetOverridesPreSpd (
  IN OUT MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION  *MrcCall;
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  BOOLEAN             OverclockCapable;
  UINT32              Offset;
  UNCORE_CR_CAPID0_A_0_0_0_PCI_STRUCT Capid0A;
  UINT32              MailboxStatus;
  MrcMailboxDllBwEn   MailboxDllBwEn;
  volatile int        i;

  Inputs             = &MrcData->Inputs;
  Debug              = &MrcData->Outputs.Debug;
  MrcCall            = Inputs->Call.Func;

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_CAPID0_A_0_0_0_PCI_REG);
  Capid0A.Data = MrcCall->MrcMmioRead32 (Offset);

  OverclockCapable = (Capid0A.Bits.DDR_OVERCLOCK > 0) ? TRUE : FALSE;

  if (OverclockCapable) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_OVERCLOCK = 1\n");

    MrcCall->MrcCpuMailboxRead (
               MAILBOX_TYPE_PCODE,
               CPU_MAILBOX_CMD_READ_DLLBWEN,
               &MailboxDllBwEn.Data,
               &MailboxStatus
               );
    if (MailboxStatus == PCODE_MAILBOX_CC_SUCCESS) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Current DllBwEn: 0x%08X (%u, %u, %u, %u)\n", MailboxDllBwEn.Data,
        MailboxDllBwEn.Bits.DllBwEn1067, MailboxDllBwEn.Bits.DllBwEn1333, MailboxDllBwEn.Bits.DllBwEn1600, MailboxDllBwEn.Bits.DllBwEn1867);
      if ((Inputs->DllBwEn0 == MailboxDllBwEn.Bits.DllBwEn1067) &&
          (Inputs->DllBwEn1 == MailboxDllBwEn.Bits.DllBwEn1333) &&
          (Inputs->DllBwEn2 == MailboxDllBwEn.Bits.DllBwEn1600) &&
          (Inputs->DllBwEn3 == MailboxDllBwEn.Bits.DllBwEn1867)
          ) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "No change required\n");
      } else {
        //
        // Program the new value
        //
        MailboxDllBwEn.Bits.DllBwEn1067 = Inputs->DllBwEn0;
        MailboxDllBwEn.Bits.DllBwEn1333 = Inputs->DllBwEn1;
        MailboxDllBwEn.Bits.DllBwEn1600 = Inputs->DllBwEn2;
        MailboxDllBwEn.Bits.DllBwEn1867 = Inputs->DllBwEn3;

        MrcCall->MrcCpuMailboxWrite (
                   MAILBOX_TYPE_PCODE,
                   CPU_MAILBOX_CMD_WRITE_DLLBWEN,
                   MailboxDllBwEn.Data,
                   &MailboxStatus
                   );
        if (MailboxStatus == PCODE_MAILBOX_CC_SUCCESS) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CPU Mailbox write succeeded\n");
          MrcCall->MrcCpuMailboxRead (
                     MAILBOX_TYPE_PCODE,
                     CPU_MAILBOX_CMD_READ_DLLBWEN,
                     &MailboxDllBwEn.Data,
                     &MailboxStatus
                     );
          if (MailboxStatus == PCODE_MAILBOX_CC_SUCCESS) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "New DllBwEn: 0x%08X (%u, %u, %u, %u)\nPerforming Warm Reset...\n", MailboxDllBwEn.Data,
              MailboxDllBwEn.Bits.DllBwEn1067, MailboxDllBwEn.Bits.DllBwEn1333, MailboxDllBwEn.Bits.DllBwEn1600, MailboxDllBwEn.Bits.DllBwEn1867);
            //
            // Perform a warm reset for the new setting to take effect
            //
            MrcCall->MrcIoWrite8 (0xCF9, 2);
            MrcCall->MrcIoWrite8 (0xCF9, 6);
            for (i = 0; i < 1;) {
            }
          }
        } else {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "CPU Mailbox write error, code = 0x%x\n", MailboxStatus);
        }
      }
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "CPU Mailbox read error, code = 0x%x\n", MailboxStatus);
    }
  } // if Overclock capable

  return mrcSuccess;
}

/**
  This function reads the current setting of the GDXC MOT regiion.

  @param[in]      MrcData - All the MRC global data.
  @param[in, out] Start   - The starting GDXC MOT address.
  @param[in, out] End     - The ending GDXC MOT address.

  @retval Returns mrcSuccess if the value has been read.
**/
MrcStatus
MrcGetGdxcMot (
  IN MrcParameters *const MrcData,
  IN OUT UINT32    *const Start,
  IN OUT UINT32    *const End
  )
{
  const MRC_FUNCTION                 *MrcCall;
  MrcDebug                           *Debug;
  const MrcInput                     *Inputs;
  MrcOutput                          *Outputs;
  MPCOHTRK_CR_GDXC_MOT_REGION_STRUCT GdxcMotRegion;

  Inputs             = &MrcData->Inputs;
  Outputs            = &MrcData->Outputs;
  Debug              = &Outputs->Debug;
  MrcCall            = Inputs->Call.Func;
  GdxcMotRegion.Data = MrcCall->MrcMmioRead32 (Inputs->GdxcBaseAddress + MPCOHTRK_CR_GDXC_MOT_REGION_REG);
  *Start             = GdxcMotRegion.Bits.START_ADDRESS;
  *End               = GdxcMotRegion.Bits.END_ADDRESS;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GDXC MOT: START=0x%x, END=0x%x\n", *Start, *End);
  return mrcSuccess;
}

/**
  This function reads the current setting of the GDXC OCLA region.

  @param[in]      MrcData - All the MRC global data.
  @param[in, out] Start   - The starting GDXC MOT address.
  @param[in, out] End     - The ending GDXC MOT address.

  @retval Returns mrcSuccess if the value has been read.
**/
MrcStatus
MrcGetGdxcOcla (
  IN MrcParameters *const MrcData,
  IN OUT UINT32    *const Start,
  IN OUT UINT32    *const End
  )
{
  const MRC_FUNCTION                  *MrcCall;
  MrcDebug                            *Debug;
  const MrcInput                      *Inputs;
  MrcOutput                           *Outputs;
  MPCOHTRK_CR_GDXC_OCLA_REGION_STRUCT GdxcOclaRegion;

  Inputs              = &MrcData->Inputs;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  MrcCall             = Inputs->Call.Func;
  GdxcOclaRegion.Data = MrcCall->MrcMmioRead32 (Inputs->GdxcBaseAddress + MPCOHTRK_CR_GDXC_OCLA_REGION_REG);
  *Start              = GdxcOclaRegion.Bits.START_ADDRESS;
  *End                = GdxcOclaRegion.Bits.END_ADDRESS;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GDXC IOT: START=0x%x, END=0x%x\n", *Start, *End);
  return mrcSuccess;
}

/**
  This function reads the input data structure and sets the appropriate timing overrides in the output structure.

  @param[in, out] MrcData - All the MRC global data.

  @retval Returns mrcSuccess if the timing overrides have been completed.
**/
MrcStatus
MrcSetOverrides (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput     *Inputs;
  MrcOutput          *Outputs;
  UINT32             Start;
  UINT32             End;

  Inputs                   = &MrcData->Inputs;
  Outputs                  = &MrcData->Outputs;
  Outputs->EccSupport      = Inputs->EccSupport != 0;
  Outputs->VddVoltageDone  = FALSE;
  Outputs->Gdxc.GdxcEnable = Inputs->Gdxc.GdxcEnable;

  //
  // Read MOT register
  //
  MrcGetGdxcMot (MrcData, (UINT32 *const) &Start, (UINT32 *const) &End);
  Outputs->Gdxc.GdxcMotSize = ((Start == 0) && (End > 1)) ? (UINT8) (End) : Inputs->Gdxc.GdxcMotSize;

  //
  // Read OCLA register
  //
  MrcGetGdxcOcla (MrcData, (UINT32 *const) &Start, (UINT32 *const) &End);
  Outputs->Gdxc.GdxcIotSize = ((Start == 0) && (End > 1)) ? (UINT8) (End) : Inputs->Gdxc.GdxcIotSize;

  // Only enable LPDDR3 ODT if frequency >= 2133.
  Outputs->LpddrDramOdt = ((Inputs->LpddrDramOdt) && (Outputs->Frequency >= f2133)) ? 1 : 0;

  return mrcSuccess;
}

/**
  This function get the current value of the sticky scratchpad register.

  @param[in] MrcData - include all the MRC data.

  @retval The current value of the sticky scratchpad register.

  **/
UINT64
MrcWmRegGet (
  IN     MrcParameters *const MrcData
  )
{
  return (MrcReadCR64 (MrcData, PCU_CR_SSKPD_PCU_REG));
}

/**
  This function fills the scratch registers
  [DDRDATAxCHx_CR_DATATRAINFEEDBACK_REG] with MR data per rank and channel.
  These MRs are copied from the host structure.
  It also logs the final MR values and saves MR registers to MRS FSM for SA GV.

  ------------------- DDR3/4 ------------------------
  Note 1: DDR4 values are for Byte 0 only
  Note 2: MR5 is for DDR4 only.
  Per channel:
   DDRDATA0CHx_CR_DATATRAINFEEDBACK    [MR1_Rank0, MR0_Rank0] (31-16, 15-0)
   DDRDATA1CHx_CR_DATATRAINFEEDBACK    [MR1_Rank1, MR0_Rank1] (31-16, 15-0)
   DDRDATA2CHx_CR_DATATRAINFEEDBACK    [MR1_Rank2, MR0_Rank2] (31-16, 15-0)
   DDRDATA3CHx_CR_DATATRAINFEEDBACK    [MR1_Rank3, MR0_Rank3] (31-16, 15-0)
   DDRDATA4CHx_CR_DATATRAINFEEDBACK    [MR2_Rank1, MR2_Rank0] (31-16, 15-0)
   DDRDATA5CHx_CR_DATATRAINFEEDBACK    [MR2_Rank3, MR2_Rank2] (31-16, 15-0)
   DDRDATA6CHx_CR_DATATRAINFEEDBACK    [MR5_Rank1, MR5_Rank0] (31-16, 15-0)
   DDRDATA7CHx_CR_DATATRAINFEEDBACK    [MR5_Rank3, MR5_Rank2] (31-16, 15-0)

------------------- LPDDR3 ------------------------
  Per channel:
   DDRDATA0CHx_CR_DATATRAINFEEDBACK    [MR2_Rank0,  MR1_Rank0] (31-16, 15-0)
   DDRDATA1CHx_CR_DATATRAINFEEDBACK    [MR2_Rank1,  MR1_Rank1] (31-16, 15-0)
   DDRDATA2CHx_CR_DATATRAINFEEDBACK    [MR11_Rank0, MR3_Rank0] (31-16, 15-0)
   DDRDATA3CHx_CR_DATATRAINFEEDBACK    [MR11_Rank1, MR3_Rank1] (31-16, 15-0)

  @param[in] MrcData - The global host structure

  @retval mrcSuccess.
**/
MrcStatus
MrcFillMrScratchRegs (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput          *Inputs;
  MrcDebug                *Debug;
  MrcOutput               *Outputs;
  const MrcControllerOut  *ControllerOut;
  const MrcChannelOut     *ChannelOut;
  const MrcRankOut        *RankOut;
  MrcDdrType              DdrType;
  MRC_FUNCTION            *MrcCall;
  UINT32                  Offset;
  UINT32                  DclkPs;
  UINT8                   VrefCode;
  UINT8                   Rank;
  UINT8                   Byte;
  UINT8                   Channel;
  UINT8                   RankMod2;
  UINT8                   Mr;
  BOOLEAN                 FsmSaved;
  BOOLEAN                 SaGv;
  DDRDATA0CH0_CR_DATATRAINFEEDBACK_STRUCT     DataTrainFeedback[3];
  MCHBAR_CH0_CR_LPDDR3_MR_CONTENT_STRUCT      LpddrMrContent;
  MCHBAR_CH0_CR_DDR4_MR0_MR1_CONTENT_STRUCT   Mr0Mr1Content;
  MCHBAR_CH0_CR_DDR4_MR2_MR3_CONTENT_STRUCT   Mr2Mr3Content;
  MCHBAR_CH0_CR_DDR4_MR4_MR5_CONTENT_STRUCT   Mr4Mr5Content;
  MCHBAR_CH0_CR_DDR4_MR6_MR7_CONTENT_STRUCT   Mr6Mr7Content;
  //  MCHBAR_CH0_CR_DDR4_MR1_ODIC_VALUES_STRUCT   Mr1OdicValues;
  //  MCHBAR_CH0_CR_DDR4_MR2_RTT_WR_VALUES_STRUCT Mr2RttWrValues;
  MCHBAR_CH0_CR_DDR4_MR6_VREF_VALUES_0_STRUCT Mr6VrefValues;
  MCHBAR_CH0_CR_MRS_FSM_CONTROL_STRUCT        MrsFsmControl;

  Inputs  = &MrcData->Inputs;
  MrcCall = MrcData->Inputs.Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  DdrType = Outputs->DdrType;
  ControllerOut = &Outputs->Controller[0];

  MrsFsmControl.Data = 0;
  MrsFsmControl.Bits.do_ZQCL = 1;
  SaGv = (Inputs->SaGv == MrcSaGvEnabled);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    FsmSaved = FALSE;
    if (DdrType == MRC_DDR_TYPE_LPDDR3) {
      for (Rank = 0; Rank < 2; Rank++) {
        RankMod2 = Rank % 2;
        RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2];

#ifdef MRC_DEBUG_PRINT
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          for (Mr = 1; Mr <= 3; Mr++) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch %d Rank %d MR[%d] = 0x%04X\n", Channel, Rank, Mr, RankOut->MR[Mr]);
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch %d Rank %d MR[%d]= 0x%04X\n", Channel, Rank, 11, RankOut->MR11);
        }
#endif
        //
        // MR1 and MR2
        //
        DataTrainFeedback[0].Data16[0] = RankOut->MR[1];
        DataTrainFeedback[0].Data16[1] = RankOut->MR[2];
        Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Rank);
        MrcWriteCR (MrcData, Offset, DataTrainFeedback[0].Data);

        //
        // MR3 and MR11
        //
        DataTrainFeedback[1].Data16[0] = RankOut->MR[3];
        DataTrainFeedback[1].Data16[1] = RankOut->MR11;
        Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, 2 + Rank);
        MrcWriteCR (MrcData, Offset, DataTrainFeedback[1].Data);

        if (!FsmSaved) {
          LpddrMrContent.Data = 0;
          LpddrMrContent.Bits.MR1  = RankOut->MR[1];
          LpddrMrContent.Bits.MR2  = RankOut->MR[2];
          LpddrMrContent.Bits.MR3  = RankOut->MR[3];
          LpddrMrContent.Bits.MR11 = RankOut->MR11;
          Offset = MCHBAR_CH0_CR_LPDDR3_MR_CONTENT_REG +
            (MCHBAR_CH1_CR_LPDDR3_MR_CONTENT_REG - MCHBAR_CH0_CR_LPDDR3_MR_CONTENT_REG) * Channel;
          MrcWriteCR (MrcData, Offset, LpddrMrContent.Data);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH%d_LPDDR3_MR_CONTENT = 0x%08X\n", Channel, LpddrMrContent.Data);

          MrsFsmControl.Bits.LPDDR3_Restore_MR = 0x0F;
          FsmSaved = TRUE;
        }
      } // for Rank
    } else { // DDR3 or DDR4
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        RankMod2 = Rank % 2;
        RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2];

#ifdef MRC_DEBUG_PRINT
        if (DdrType == MRC_DDR_TYPE_DDR3) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            for (Mr = 0; Mr <= 2; Mr++) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch %d Rank %d MR[%d] = 0x%04X\n", Channel, Rank, Mr, RankOut->MR[Mr]);
            }
          }
        }
#endif
        //
        // MR0 - MR1
        //
        for (Mr = 0; Mr < 2; Mr++) {
          DataTrainFeedback[0].Data16[Mr % 2] = RankOut->MR[Mr];
        }
        Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Rank);
        MrcWriteCR (MrcData, Offset, DataTrainFeedback[0].Data);

        //
        // MR2
        //
        DataTrainFeedback[1].Data16[RankMod2] = RankOut->MR[2];
        if (RankMod2) {
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, 4 + (Rank / 2));
          MrcWriteCR (MrcData, Offset, DataTrainFeedback[1].Data);
        }

        if (DdrType == MRC_DDR_TYPE_DDR4) {
          //
          // MR5
          //
          DataTrainFeedback[2].Data16[RankMod2] = RankOut->MR[5];
          if (RankMod2) {
            Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, 6 + (Rank / 2));
            MrcWriteCR (MrcData, Offset, DataTrainFeedback[2].Data);
          }
          //
          // Per-device registers restore for DDR4 - for EV
          //
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            Mr6VrefValues.Data = 0;
            for (Byte = 0; Byte < 8; Byte++) { // Only 8 bytes, no place for ECC byte
              VrefCode = RankOut->Ddr4PdaMr6[Byte] & 0x7F;
              Mr6VrefValues.Data |= MrcCall->MrcLeftShift64 ((UINT64) VrefCode, Byte * MCHBAR_CH0_CR_DDR4_MR6_VREF_VALUES_0_Byte1_OFF);
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "CH%d RANK%d BYTE%d: Vref offset = %d (0 = 820mV) Code = 0x%X \n",
                Channel,
                Rank,
                Byte,
                MrcVrefDqToOffset (VrefCode),
                VrefCode
                );
            }
            Offset = MCHBAR_CH0_CR_DDR4_MR6_VREF_VALUES_0_REG +
              (MCHBAR_CH1_CR_DDR4_MR6_VREF_VALUES_0_REG - MCHBAR_CH0_CR_DDR4_MR6_VREF_VALUES_0_REG) * Channel +
              (MCHBAR_CH0_CR_DDR4_MR6_VREF_VALUES_1_REG - MCHBAR_CH0_CR_DDR4_MR6_VREF_VALUES_0_REG) * Rank;
            MrcWriteCR64 (MrcData, Offset, Mr6VrefValues.Data);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "CH%d RANK%d: DDR4_MR6_VREF_VALUES = 0x%08X%08X\n",
              Channel,
              Rank,
              Mr6VrefValues.Data32[1],
              Mr6VrefValues.Data32[0]
              );
          }
        } // if Ddr4

        if (!FsmSaved && MrcRankInChannelExist (MrcData, Rank, Channel)) {
          Mr0Mr1Content.Data = 0;
          Mr2Mr3Content.Data = 0;
          Mr4Mr5Content.Data = 0;
          Mr6Mr7Content.Data = 0;
          Mr0Mr1Content.Bits.MR0 = RankOut->MR[0];
          Mr0Mr1Content.Bits.MR1 = RankOut->MR[1];
          Mr2Mr3Content.Bits.MR2 = RankOut->MR[2];
          Mr2Mr3Content.Bits.MR3 = RankOut->MR[3];
          MrsFsmControl.Bits.DDR4_Restore_MR = 0xF; // Restore MR0..MR3

          Offset = MCHBAR_CH0_CR_DDR4_MR0_MR1_CONTENT_REG +
            (MCHBAR_CH1_CR_DDR4_MR0_MR1_CONTENT_REG - MCHBAR_CH0_CR_DDR4_MR0_MR1_CONTENT_REG) * Channel;
          MrcWriteCR (MrcData, Offset, Mr0Mr1Content.Data);

          Offset = MCHBAR_CH0_CR_DDR4_MR2_MR3_CONTENT_REG +
            (MCHBAR_CH1_CR_DDR4_MR2_MR3_CONTENT_REG - MCHBAR_CH0_CR_DDR4_MR2_MR3_CONTENT_REG) * Channel;
          MrcWriteCR (MrcData, Offset, Mr2Mr3Content.Data);
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "CH%d: MR0_MR1_CONTENT = 0x%08X, MR2_MR3_CONTENT = 0x%08X\n",
            Channel,
            Mr0Mr1Content.Data,
            Mr2Mr3Content.Data
            );

          if (DdrType == MRC_DDR_TYPE_DDR4) {
            Mr4Mr5Content.Bits.MR4 = RankOut->MR[4];
            Mr4Mr5Content.Bits.MR5 = RankOut->MR[5];
            Mr6Mr7Content.Bits.MR6 = RankOut->MR[6];
            MrsFsmControl.Bits.DDR4_Restore_MR = 0x7F;          // Restore MR0..MR6
            MrsFsmControl.Bits.DDR4_Restore_MR6_Per_Device = 1; // Restore MR6 using PDA
            MrsFsmControl.Bits.vref_time_per_byte = 1;
            DclkPs = Outputs->Qclkps * 2;
            MrsFsmControl.Bits.tVREFDQ = DIVIDECEIL (tVREF_DQ, DclkPs);
            //
            // @todo Add per-device registers restore for DDR4
            //
            Offset = MCHBAR_CH0_CR_DDR4_MR4_MR5_CONTENT_REG +
              (MCHBAR_CH1_CR_DDR4_MR4_MR5_CONTENT_REG - MCHBAR_CH0_CR_DDR4_MR4_MR5_CONTENT_REG) * Channel;
            MrcWriteCR (MrcData, Offset, Mr4Mr5Content.Data);

            Offset = MCHBAR_CH0_CR_DDR4_MR6_MR7_CONTENT_REG +
              (MCHBAR_CH1_CR_DDR4_MR6_MR7_CONTENT_REG - MCHBAR_CH0_CR_DDR4_MR6_MR7_CONTENT_REG) * Channel;
            MrcWriteCR (MrcData, Offset, Mr6Mr7Content.Data);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "CH%d: MR4_MR5_CONTENT = 0x%08X, MR6_MR7_CONTENT = 0x%08X\n",
              Channel,
              Mr4Mr5Content.Data,
              Mr6Mr7Content.Data
              );
          }
          FsmSaved = TRUE;
        } // if !FsmSaved and rank exists
      } // for Rank
    } // DDR3 or DDR4

    if (SaGv) {
      Offset = MCHBAR_CH0_CR_MRS_FSM_CONTROL_REG +
        (MCHBAR_CH1_CR_MRS_FSM_CONTROL_REG - MCHBAR_CH0_CR_MRS_FSM_CONTROL_REG) * Channel;
      MrcWriteCR (MrcData, Offset, MrsFsmControl.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH%d_MRS_FSM_CONTROL = 0x%08X\n", Channel, MrsFsmControl.Data);
    }
  } // for Channel

#ifdef MRC_DEBUG_PRINT
  if (DdrType == MRC_DDR_TYPE_DDR4) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (((1 << Rank) & Outputs->ValidRankMask) == 0) {
        //
        // Skip if this rank is not present on any of the channels
        //
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank %d\tCh0\tCh1", Rank);
      RankMod2 = Rank % 2;
      for (Mr = 0; Mr <= 6; Mr++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nMR[%d]:", Mr);
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          ChannelOut = &ControllerOut->Channel[Channel];
          RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[RankMod2];
          if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
            if (Channel == 0) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
            }
            continue;
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t0x%04X", RankOut->MR[Mr]);
        } // for Channel
      } // for Mr
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    } // for Rank
  } // if DDR4
#endif

  return mrcSuccess;
}

/**
  Program DDRPL_CR_DDR_TX_DELAY if Memory Trace is enabled

  @param[in] MrcData - The MRC general data.

**/
void
MrcSetDdrplTxDelay (
  IN MrcParameters *const MrcData
  )
{
  MrcIntOutput    *MrcIntData;
  MrcInput        *Inputs;
  MRC_FUNCTION    *MrcCall;
  MrcOutput       *Outputs;
  MrcDebug        *Debug;
  MrcIntChannelOut *IntChannelOut;
  MrcDdrType      DdrType;
  UINT32          Rank;
  UINT32          TxDelay;
  UINT32          tDQSCK;
  UINT32          Roundtrip;
  UINT32          tCL;
  UINT32          tCWL;
  UINT32          tCAL;
  UINT32          CmdDelay;
  UINT32          CmdStretch;
  UINT32          DecWrd;
  UINT32          AddWrDelay;
  UINT32          tCWL5_reduction;
  UINT32          StretchMode;
  UINT32          Channel;
  UINT32          Offset;
  DDRPL_CR_DDR_TX_DELAY_LOW_STRUCT          DdrTxDelay;
  MCHBAR_CH0_CR_TC_ODT_STRUCT               TcOdt;
  MCHBAR_CH0_CR_SC_ROUNDTRIP_LATENCY_STRUCT ScRoundtLat;
  MCHBAR_CH0_CR_SC_WR_ADD_DELAY_STRUCT      ScWrAddDelay;
  MCHBAR_CH0_CR_SC_GS_CFG_STRUCT            ScGsCfg;
  MCHBAR_CH0_CR_DFT_MISC_STRUCT             DftMisc;

  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  DdrType = Outputs->DdrType;

  if (!Inputs->MemoryTrace) {
    return;
  }

  //
  // TxDelay(rank) = Roundtrip(rank) - [2*RD_cmd2data_dclk_delay] + [2*Dec_WRD] - additional_wr_delay(rank) - [2*tCWL5_reduction] + [8*(STM - 1)] + Constant(5)
  //
  // RD_cmd2data_dclk_delay = tCL + tDQSCK + cmd_delay + cmd_stretch
  //                        tCL, tDQSCK      - according to JEDEC spec
  //                        cmd_delay        - zero in SKL
  //                        cmd_stretch      - MCSCHEDS_CR_TC_BANK_RANK_A. cmd_stretch (0,1,2 for 1N,2N,3N respectively)
  //
  // tCWL5_reduction = (ddr_type==DDR3 && (tCWL + cmd_stretch - Dec_WRD == 5)) ? 1 : 0;
  //
  // STM = (STM_mode == SYSTEM ? STM_stf : 1)

  //
  // Assume we are tracing DDR channel 0 - taking all the timing parameters from Channel 0
  //
  Channel = 0;
  IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];

  Offset = MCHBAR_CH0_CR_SC_ROUNDTRIP_LATENCY_REG +
    (MCHBAR_CH1_CR_SC_ROUNDTRIP_LATENCY_REG - MCHBAR_CH0_CR_SC_ROUNDTRIP_LATENCY_REG) * Channel;
  ScRoundtLat.Data  = MrcReadCR (MrcData, Offset);

  Offset = MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG +
    (MCHBAR_CH1_CR_SC_WR_ADD_DELAY_REG - MCHBAR_CH0_CR_SC_WR_ADD_DELAY_REG) * Channel;
  ScWrAddDelay.Data = MrcReadCR (MrcData, Offset);

  Offset = MCHBAR_CH0_CR_SC_GS_CFG_REG +
    (MCHBAR_CH1_CR_SC_GS_CFG_REG - MCHBAR_CH0_CR_SC_GS_CFG_REG) * Channel;
  ScGsCfg.Data      = MrcReadCR (MrcData, Offset);

  Offset = MCHBAR_CH0_CR_DFT_MISC_REG +
    (MCHBAR_CH1_CR_DFT_MISC_REG - MCHBAR_CH0_CR_DFT_MISC_REG) * Channel;
  DftMisc.Data      = MrcReadCR (MrcData, Offset);

  TcOdt       = IntChannelOut->MchbarTcOdt;
  tCL         = TcOdt.Bits.tCL;
  tCWL        = TcOdt.Bits.tCWL;
  CmdDelay    = 0;
  CmdStretch  = ScGsCfg.Bits.CMD_stretch % 3;
  tCAL        = ScGsCfg.Bits.tCAL;
  DecWrd      = ScWrAddDelay.Bits.Dec_WRD;
  tDQSCK      = (DdrType == MRC_DDR_TYPE_LPDDR3) ? DIVIDECEIL (tDQSCK_MIN, Outputs->Qclkps) : 0;

  if ((DdrType == MRC_DDR_TYPE_DDR3) && (tCWL + CmdStretch - DecWrd == 5)) {
    tCWL5_reduction = 1;
  } else {
    tCWL5_reduction = 0;
  }

  StretchMode = (DftMisc.Bits.Stretch_mode == 2) ? DftMisc.Bits.STF : 1;

  DdrTxDelay.Data = 0;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TX Delay values for Memory Trace:\n");
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (!MrcRankInChannelExist (MrcData, (UINT8) Rank, 0)) {
      continue;
    }

    Roundtrip  = (ScRoundtLat.Data >> (Rank * 8)) & MCHBAR_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_MSK;
    Roundtrip -= tCAL;
    AddWrDelay = (ScWrAddDelay.Data >> (Rank * 2)) & MCHBAR_CH0_CR_SC_WR_ADD_DELAY_D0R0_MSK;

    TxDelay = Roundtrip - 2 * (tCL + tDQSCK + CmdDelay + CmdStretch) +
      2 * DecWrd - AddWrDelay - 2 * tCWL5_reduction + 8 * (StretchMode - 1) + 4;

    DdrTxDelay.Data |= ((TxDelay & DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R0_MSK) << (Rank * DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R0_WID));

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Rank%u:\n RT = %u\n tCL = %u\n tCWL = %u\n CMD_stretch = %u\n Dec_WRD = %u\n AddWrDelay = %u\n tCWL5_reduction = %u\n STM = %u\n",
      Rank,
      Roundtrip,
      tCL,
      tCWL,
      CmdStretch,
      DecWrd,
      AddWrDelay,
      tCWL5_reduction,
      StretchMode
      );
  }

  Offset = (MrcIntData->SaGvPoint == MrcSaGvPointHigh) ? DDRPL_CR_DDR_TX_DELAY_HIGH_REG : DDRPL_CR_DDR_TX_DELAY_LOW_REG;
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDRPL_CR_DDR_TX_DELAY_%s = 0x%08X\n",
    (MrcIntData->SaGvPoint == MrcSaGvPointHigh) ? "HIGH" : "LOW",
    DdrTxDelay.Data
    );

  MrcCall->MrcMmioWrite32 (Inputs->GdxcBaseAddress + Offset, DdrTxDelay.Data);
}


/**
  Program BER Addresses if enabled

  @param[in] MrcData - The MRC general data.

**/
void
MrcBerSetup (
  IN     MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION                        *MrcCall;
  const MrcInput                            *Inputs;
  MrcDebug                                  *Debug;
  MrcOutput                                 *Outputs;
  UINT8                                     MaxIndex;
  UINT8                                     MaxIndexMinus;
  UINT8                                     Index1;
  UINT8                                     Index2;
  UINT8                                     ValidAddress;
  UINT8                                     OverlappingAddresses;
  UINT64                                    Address;
  MrcStatus                                 Status;
  UINT64                                    Touud;
  UINT32                                    LowerMask;
  UINT32                                    UpperMask;
  UINT32                                    Data32;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;

  MaxIndex = Inputs->BerEnable;
#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "IN BER Enable : %u\n", MaxIndex);
  for (Index1 = 0; Index1 < 4; Index1++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "IN BER Address[%u] : 0x%x_%08x\n", Index1, (UINT32) (MrcCall->MrcRightShift64 (Inputs->BerAddress[Index1], 32)), (UINT32) (Inputs->BerAddress[Index1]));
  }
#endif //MRC_DEBUG_PRINT
  if (MaxIndex != 0) {
    MrcCall  = Inputs->Call.Func;
    OverlappingAddresses = 0;

    if (MaxIndex <= 4) {
      //
      // Passed in addresses
      //
      MrcCall->MrcCopyMem ((UINT8 *) Outputs->BerAddress, (UINT8 *) Inputs->BerAddress, sizeof (UINT64) * MaxIndex);
      ValidAddress = (MRC_BIT0 << MaxIndex) - 1;

      //
      // Align to 64B cacheline
      //
      for (Index1 = 0; Index1 < MaxIndex; Index1++) {
        Outputs->BerAddress[Index1] &= 0x07FFFFFFFC0ULL;
      }

      //
      // Check for overlap addresses after cacheline alignment
      //
      MaxIndexMinus = MaxIndex - 1;
      for (Index1 = 0; Index1 < MaxIndexMinus; Index1++) {
        for (Index2 = (Index1 + 1); Index2 < MaxIndex; Index2++) {
          if (Outputs->BerAddress[Index1] == Outputs->BerAddress[Index2]) {
            ValidAddress &= ~(MRC_BIT0 << Index1);
            OverlappingAddresses++;
            break;
          }
        }
      }

      //
      // Check if within Memory Map
      //
      for (Index1 = 0; Index1 < MaxIndex; Index1++) {
        if (ValidAddress & (MRC_BIT0 << Index1)) {
          if ((MrcBitErrRecAddressCompare (MrcData, Outputs->BerAddress[Index1])) == mrcFail) {
            ValidAddress &= ~(MRC_BIT0 << Index1);
            OverlappingAddresses++;
          }
        }
      }

      //
      // Set # of BER Enable to match
      //
      Outputs->BerEnable = MaxIndex - OverlappingAddresses;

      //
      // Shift Addresses in array if there were overlapping addresses and have any valid addresses left
      //
      if ((OverlappingAddresses) && (Outputs->BerEnable)) {
        for (Index1 = 0; Index1 < MaxIndexMinus; Index1++) {
          if (ValidAddress & (MRC_BIT0 << Index1)) {
            //
            // ValidAddress, skip to next address
            //
            continue;
          }
          for (Index2 = (Index1 + 1); Index2 < MaxIndex; Index2++) {
            if (ValidAddress & (MRC_BIT0 << Index2)) {
              //
              // Shift Index2 address to Index1 location and adjust ValidAddress accordingly
              //
              Outputs->BerAddress[Index1] = Outputs->BerAddress[Index2];
              ValidAddress |= (MRC_BIT0 << Index1);
              ValidAddress &= ~(MRC_BIT0 << Index2);
              break;
            }
          }
        }
      } //if (OverlappingAddresses)
    } else {
      //
      // Randomize addresses and adjust MaxIndex to # of random addresses
      //
      MaxIndexMinus = MaxIndex - 4;
      MaxIndex = MIN (MaxIndexMinus, 4);
      Outputs->BerEnable = MaxIndex;
      Touud = (UINT64) Outputs->MemoryMapData.TouudBase;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TOUUD_MB: 0x%x, ", (UINT32) Touud);
      Touud = MrcCall->MrcLeftShift64 (Touud, 20);
      Touud--;
      LowerMask = ((UINT32) Touud & 0xFFFFFFC0);
      UpperMask = (UINT32) (MrcCall->MrcRightShift64 (Touud, 32));
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Lower Mask: 0x%08x, UpperMask: 0x%08x\n", LowerMask, UpperMask);

      for (Index1 = 0; Index1 < MaxIndex; Index1++) {
        do {
          //
          // TOUUD Max is bit 38 and Data32 is for upper 32bit of 64bit address (thus the mask of 0x07F)
          //
          MrcCall->MrcGetRandomNumber (&Data32);
          Address = MrcCall->MrcLeftShift64 ((UINT64) (Data32 & UpperMask), 32);
          MrcCall->MrcGetRandomNumber (&Data32);
          Address |= (UINT64) (Data32 & LowerMask);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Random Address : 0x%x_%08x\n", (UINT32) (MrcCall->MrcRightShift64 (Address, 32)), (UINT32) (Address));

          Status = MrcBitErrRecAddressCompare (MrcData, Address);
        } while (Status == mrcFail);
        Outputs->BerAddress[Index1] = Address;
      }
    }
#ifdef MRC_DEBUG_PRINT
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "OUT BER Enable : %u\n", Outputs->BerEnable);
    for (Index1 = 0; Index1 < Outputs->BerEnable; Index1++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "OUT BER Address[%u] : 0x%x_%08x\n", Index1, (UINT32) (MrcCall->MrcRightShift64 (Outputs->BerAddress[Index1], 32)), (UINT32) (Outputs->BerAddress[Index1]));
    }
#endif //MRC_DEBUG_PRINT
  } else {
    Outputs->BerEnable = 0;
  }
}

/**
  Enable Bit Error Recovery feature

  @param[in] MrcData - The MRC general data.

**/
void
MrcBerActivate (
  IN  MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION  *MrcCall;
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcMemoryMap        *MemoryMap;
  UINT32              Offset;
  UINT32              Index;
  UINT64              TomAddress;
  UINT64              RemapBaseAddress;
  MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_STRUCT   BerAddress;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  if (Outputs->BerEnable) {
    //
    // BER addresses
    //
    MemoryMap = &Outputs->MemoryMapData;
    if (MemoryMap->ReclaimEnable) {
      TomAddress       = MrcCall->MrcLeftShift64 ((UINT64) (MemoryMap->TotalPhysicalMemorySize), 20);
      RemapBaseAddress = MrcCall->MrcLeftShift64 ((UINT64) (MemoryMap->RemapBase), 20);
    } else {
      TomAddress       = 0;
      RemapBaseAddress = 0;
    }

    for (Index = 0; Index < Outputs->BerEnable; Index++) {
      BerAddress.Data = Outputs->BerAddress[Index];

      //
      // Check if BER Address is between below TOM and above Remap Base
      //
      if ((MemoryMap->ReclaimEnable) && (BerAddress.Data < TomAddress) && (BerAddress.Data >= RemapBaseAddress)) {
        BerAddress.Bits.is_tcm = 1;
      } else {
        BerAddress.Bits.is_tcm = 0;
      }
      BerAddress.Bits.valid  = 1;

      Offset =
        MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_REG +
        ((MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_REG -
        MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_REG) * Index);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BERSSAR[%u] = 0x%x_%08x\n", Index,
        (UINT32) (MrcCall->MrcRightShift64 (BerAddress.Data, 32)), (UINT32) BerAddress.Data);
      MrcWriteCR64 (MrcData, Offset, BerAddress.Data);
    }
  }
}

/**
  Program Row Hammer mitigation if enabled

  @param[in] MrcData - The MRC general data.

  @retval Returns MrcStatus
**/
MrcStatus
MrcRhPrevention (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput     *Inputs;
  const MRC_FUNCTION *MrcCall;
  MrcDebug           *Debug;
  MrcOutput          *Outputs;
  MrcStatus          Status;
  MrcStatus          DimmStatus;
  MrcProfile         Profile;
  MrcSpd             *Spd;
  UINT8              Channel;
  UINT8              Dimm;
  UINT32             DimmMask;
  BOOLEAN            Ddr4;
  UINT32             Offset;
  MrcDimmOut         *DimmOut;
  BOOLEAN            ChannelHardwareRhp[MAX_CHANNEL];
  BOOLEAN            ChannelDoNothing[MAX_CHANNEL];
  UINT32             Data32;

  SPD_MANUFACTURER_ID_CODE               IdCode;
  MCMNTS_CR_MCMNTS_SPARE_STRUCT          McmntsSpare;
  MCMNTS_CR_RH_LFSR_STRUCT               RhLfsr;
  MCMNTS_CR_RH_CONTROL_STRUCT            RhControl;
  MCSCHEDS_CR_SCHED_CBIT_STRUCT          SchedCbit;

  Inputs            = &MrcData->Inputs;
  MrcCall           = Inputs->Call.Func;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  Profile           = Inputs->MemoryProfile;
  Ddr4              = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Status            = mrcSuccess;

  if (!Inputs->RhPrevention) {
    return Status;
  }

  MrcCall->MrcSetMem ((BOOLEAN *) ChannelDoNothing, sizeof (ChannelDoNothing), FALSE);
  MrcCall->MrcSetMem ((BOOLEAN *) ChannelHardwareRhp, sizeof (ChannelHardwareRhp), TRUE);

  // Search for any RH free DIMMs and RH untested DIMMs per channel
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {  // per channel granularity
    if (MrcChannelExist (Outputs, Channel)) {
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmStatus = IsDimmPresent (MrcData, 0, 0, Channel, Dimm);
        if (DimmStatus == mrcSuccess) {
          DimmOut = &MrcData->Outputs.Controller[0].Channel[Channel].Dimm[Dimm];
          if (Ddr4) {
            ChannelDoNothing[Channel] = TRUE;  // DDR4 on channel
          } else if (DimmOut->tMAC == MRC_TMAC_UNTESTED) {
            ChannelHardwareRhp[Channel] = FALSE;  // Refresh2x on channel
          }
        }  // IsDimmPresent
      }  // for Dimm
    }  // If Channel exists
  }  // for Channel

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {  // per channel granularity
    if (ChannelDoNothing[Channel] == FALSE) {
      //
      // HardwareRhp and Refresh2x
      //
      if (MrcChannelExist (Outputs, Channel)) {

        MrcCall->MrcGetRandomNumber (&Data32);
        RhLfsr.Bits.LFSR_0 = (UINT32) Data32;  // any non-zero number
        MrcCall->MrcGetRandomNumber (&Data32);
        RhLfsr.Bits.LFSR_1 = (UINT32) Data32;  // any non-zero number
        Offset = MCHBAR_CH0_CR_RH_LFSR_REG +
          (MCHBAR_CH1_CR_RH_LFSR_REG - MCHBAR_CH0_CR_RH_LFSR_REG) * Channel;
        MrcWriteCR64 (MrcData, Offset, RhLfsr.Data);

        RhControl.Data             = 0;  // register default is all zeros.
        RhControl.Bits.LFSR_0_MASK = Inputs->RhActProbability;
        RhControl.Bits.LFSR_1_MASK = 0;

        RhControl.Bits.MA3_Swizzling = 0;
        RhControl.Bits.MA0_Swizzling = 0;

        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmStatus = IsDimmPresent (MrcData, 0, 0, Channel, Dimm);
          if (DimmStatus == mrcSuccess) {
            DimmMask = 1 << Dimm;
            Spd = &MrcData->Inputs.Controller[0].Channel[Channel].Dimm[Dimm].Spd.Data;
            IdCode.Data = Spd->Ddr3.ModuleId.IdCode.Data;
            if (IdCode.Data == 0xFE02) {  // Elpida
              RhControl.Bits.MA3_Swizzling |= DimmMask;
              RhControl.Bits.MA0_Swizzling |= DimmMask;
            } else if (IdCode.Data == 0xCE00) {  // Samsung
              RhControl.Bits.MA3_Swizzling |= DimmMask;
            }
            //  (2 << (2 * Dimm))          ->  1010 for both DIMMs
            RhControl.Bits.Mode |= (2 << (2 * Dimm));
          }  // IsDimmPresent
        }  // for Dimm

        SchedCbit.Data = MrcReadCR (MrcData, MCHBAR_CH0_CR_SCHED_CBIT_REG);
        SchedCbit.Bits.dis_clk_gate = 1;
        MrcWriteCrMulticast (MrcData, MCSCHEDS_CR_SCHED_CBIT_REG, SchedCbit.Data);

        Offset = MCHBAR_CH0_CR_RH_CONTROL_REG +
          (MCHBAR_CH1_CR_RH_CONTROL_REG - MCHBAR_CH0_CR_RH_CONTROL_REG) * Channel;
        MrcWriteCR (MrcData, Offset, RhControl.Data);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH%d_RH_CONTROL: 0x%X\n", Channel, RhControl.Data);

        if ((ChannelHardwareRhp[Channel] == FALSE) || (Inputs->RhSolution == Refresh2x)) {
          Offset = MCHBAR_CH0_CR_MCMNTS_SPARE_REG +
            (MCHBAR_CH1_CR_MCMNTS_SPARE_REG - MCHBAR_CH0_CR_MCMNTS_SPARE_REG) * Channel;
          McmntsSpare.Data = MrcReadCR (MrcData, Offset);
          McmntsSpare.Bits.ForceX2Ref = 1;  // force 2X refresh
          MrcWriteCR (MrcData, Offset, McmntsSpare.Data);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "2x Refresh on channel %d\n", Channel);
        }
      }  // If Channel exists
    }  // if (ChannelDoNothing[Channel] == FALSE)
  }  // for Channel
  return Status;
}

/**
  Gets pointers to functions inside of core.

  @param[in]  MrcData                     - All the MRC global data.
  @param[out] CallMcAddressDecode         - Pointer to the function MrcMcAddressDecode
  @param[out] CallMcAddressEncode         - Pointer to the function MrcMcAddressEncode
  @param[out] CallChannelExist            - Pointer to the function MrcChannelExist
  @param[out] CallPrintf                  - Pointer to the function MrcPrintf
  @param[out] CallChangeMargin            - Pointer to the function ChangeMargin
  @param[out] CallSignExtend              - Pointer to the function MrcSignExtend
  @param[out] CallShiftPIforCmdTraining   - Pointer to the function ShiftPIforCmdTraining
  @param[out] CallUpdateVrefWaitTilStable - Pointer to the function UpdateVrefWaitTilStable

  @retval Returns mrcSuccess if the function succeeds.
**/
MrcStatus
MrcGetCoreFunction (
  IN const MrcParameters *const MrcData,
  OUT UINT32                   *CallMcAddressDecode,
  OUT UINT32                   *CallMcAddressEncode,
  OUT UINT32                   *CallChannelExist,
  OUT UINT32                   *CallPrintf,
  OUT UINT32                   *CallChangeMargin,
  OUT UINT32                   *CallSignExtend,
  OUT UINT32                   *CallShiftPIforCmdTraining,
  OUT UINT32                   *CallUpdateVrefWaitTilStable,
  OUT UINT32                   *CallMrcThermalOverrides
  )
{
  *CallMcAddressDecode         = (UINT32) &MrcMemoryAddressDecode;
  *CallMcAddressEncode         = (UINT32) &MrcMemoryAddressEncode;
  *CallChannelExist            = (UINT32) &MrcChannelExist;
  *CallPrintf                  = (UINT32) &MrcPrintf;
  *CallChangeMargin            = (UINT32) &ChangeMargin;
  *CallSignExtend              = (UINT32) &MrcSE;
  *CallShiftPIforCmdTraining   = (UINT32) &ShiftPIforCmdTraining;
  *CallUpdateVrefWaitTilStable = (UINT32) &UpdateVrefWaitTilStable;
  *CallMrcThermalOverrides     = (UINT32) &MrcThermalOverrides;
  return (mrcSuccess);
}

#if ((defined MRC_MINIBIOS_BUILD) || (defined MINI_FLAG))
/**
  Set up the overrides required by the MiniBios execution.

  @param[in] MrcData - Pointer to the MRC global data structure
**/
void
MrcMiniBiosOverrides (
  OUT MrcParameters *const MrcData
  )
{
  MrcInput        *Inputs;
  TrainingStepsEn *TrainingEnables;

  Inputs          = &MrcData->Inputs;
  TrainingEnables = &Inputs->TrainingEnables;

  Inputs->BerAddress[0]   = 0x7FFFFFFFFFULL;
  Inputs->BerAddress[1]   = 0x87654321ULL;
  Inputs->BerAddress[2]   = 0x100000000ULL;
  Inputs->BerAddress[3]   = 0x87654300ULL;
  Inputs->ExitOnFailure   = TRUE;
  Inputs->MrcMode         = MrcModeMini;
  Inputs->RmtPerTask      = TRUE;
  Inputs->SetRxDqs32      = TRUE;


  return;
}
#endif // ((defined MRC_MINIBIOS_BUILD) || (defined MINI_FLAG))

#ifdef MRC_DEBUG_PRINT
/**
  Print the input parameters to the debug message output port.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcPrintInputParameters (
  IN MrcParameters *const MrcData
  )
{
  MrcDebug                              *Debug;
  const MrcInput                        *Inputs;
  MrcIntOutput                          *MrcIntData;
  const MRC_FUNCTION                    *MrcCall;
  const MrcControllerIn                 *ControllerIn;
  const MrcChannelIn                    *ChannelIn;
  const MrcDimmIn                       *DimmIn;
  const TrainingStepsEn                 *TrainingSteps;
  const TrainingStepsEn2                *TrainingSteps2;
  const UINT8                           *Buffer;
  UINT16                                Line;
  UINT16                                Address;
  UINT16                                Offset;
  UINT8                                 Controller;
  UINT8                                 Channel;
  UINT8                                 Dimm;
  UINT8                                 Iteration;
  UINT8                                 DivideValue;
  UINT32                                Index;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &MrcData->Outputs.Debug;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint == MrcSaGvPointHigh)) {
    //
    // No need to print the list twice
    //
    return mrcSuccess;
  }

  //
  // The following are system level definitions. All memory controllers in the system are set to these values.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Debug.Stream: %Xh\n", Debug->Stream);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Debug.Level: %Xh\n", Debug->Level);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "HeapBase: %08Xh\n", Inputs->HeapBase);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "HeapSize: %u\n", Inputs->HeapSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SerialBuffer: %08Xh\n", Inputs->SerialBuffer);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SerialBufferSize: %u\n", Inputs->SerialBufferSize);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "FreqMax: %u\n", Inputs->FreqMax);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "FreqSaGvLow: %u\n", Inputs->FreqSaGvLow);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ratio: %u\n", Inputs->Ratio);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RefClk: %uMHz\n", (Inputs->RefClk == MRC_REF_CLOCK_100) ? 100 : 133);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BClk: %uHz\n", Inputs->BClkFrequency);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "OddRatioMode: %u\n", Inputs->OddRatioMode);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BoardType: %Xh\n", Inputs->BoardType);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DqPinsInterleaved: %u\n", Inputs->DqPinsInterleaved);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CpuStepping: %Xh\n", Inputs->CpuStepping);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CpuModel: %Xh\n", Inputs->CpuModel);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GraphicsStolenSize: %Xh\n", Inputs->GraphicsStolenSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GraphicsGttSize: %Xh\n", Inputs->GraphicsGttSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Iteration: %Xh\n", Inputs->Iteration);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcMode: %Xh\n", Inputs->MrcMode);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VddVoltage: %u mV\n", Inputs->VddVoltage);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MemoryProfile: %Xh\n", Inputs->MemoryProfile);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BootMode: %Xh\n", Inputs->BootMode);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TxtFlag: %Xh\n", Inputs->TxtFlag);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MobilePlatform: %Xh\n", Inputs->MobilePlatform);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EccSupport: %Xh\n", Inputs->EccSupport);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SetRxDqs32: %Xh\n", Inputs->SetRxDqs32);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GfxIsVersatileAcceleration: %Xh\n", Inputs->GfxIsVersatileAcceleration);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ScramblerEnable: %Xh\n", Inputs->ScramblerEnable);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "McLock: %Xh\n", Inputs->McLock);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RemapEnable: %Xh\n", Inputs->RemapEnable);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PowerDownMode: %Xh\n", Inputs->PowerDownMode);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PwdwnIdleCounter: %Xh\n", Inputs->PwdwnIdleCounter);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RankInterleave: %Xh\n", Inputs->RankInterleave);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EnhancedInterleave: %Xh\n", Inputs->EnhancedInterleave);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WeaklockEn: %Xh\n", Inputs->WeaklockEn);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "NModeSupport: %Xh\n", Inputs->NModeSupport);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EnCmdRate: %Xh\n", Inputs->EnCmdRate);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CmdTriStateDis: %Xh\n", Inputs->CmdTriStateDis);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BaseAddresses\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  PciE: %Xh\n", Inputs->PciEBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  MchBar: %Xh\n", Inputs->MchBarBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Smbus: %Xh\n", Inputs->SmbusBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Gdxc: %Xh\n", Inputs->GdxcBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Hpet: %Xh\n\n", Inputs->HpetBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MeStolenSize: %Xh\n", Inputs->MeStolenSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MmioSize: %Xh\n", Inputs->MmioSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TsegSize: %Xh\n", Inputs->TsegSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "IedSize: %Xh\n", Inputs->IedSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DprSize: %Xh\n", Inputs->DprSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PrmrrSize: %Xh\n", Inputs->PrmrrSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VddSettleWaitTime: %Xh\n", Inputs->VddSettleWaitTime);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VccIomV: %d\n", Inputs->VccIomV);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RmtPerTask: %d\n", Inputs->RmtPerTask);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "AutoSelfRefreshSupport: %u\n", Inputs->AutoSelfRefreshSupport);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ExtTemperatureSupport: %u\n", Inputs->ExtTemperatureSupport);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RhPrevention: %u\n", Inputs->RhPrevention);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RhSolution: %Xh\n", Inputs->RhSolution);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RhActProbability: %Xh\nRetrainOnFastFail: %u\nForceOltmOrRefresh2x: %u\n",
    Inputs->RhActProbability, Inputs->RetrainOnFastFail, Inputs->ForceOltmOrRefresh2x);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChHashEnable: %Xh\n", Inputs->ChHashEnable);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChHashMask: %Xh\n", Inputs->ChHashMask);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChHashInterleaveBit: %Xh\n", Inputs->ChHashInterleaveBit);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%sEnable: %Xh\n", GdxcString, Inputs->Gdxc.GdxcEnable);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%sIotSize: %Xh\n", GdxcString, Inputs->Gdxc.GdxcIotSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%sMotSize: %Xh\n", GdxcString, Inputs->Gdxc.GdxcMotSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MemoryTrace: %u\n", Inputs->MemoryTrace);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Force1Dpc: %u\n", Inputs->Force1Dpc);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ForceSingleRank: %u\n", Inputs->ForceSingleRank);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BER Enable: %u\n", Inputs->BerEnable);
  for (Offset = 0; Offset < 4; Offset++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BER Address[%u]: %X_%08Xh\n", Offset, (UINT32) (MrcCall->MrcRightShift64 (Inputs->BerAddress[Offset], 32)), (UINT32) (Inputs->BerAddress[Offset]));
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "StrongWkLeaker: %u\n", Inputs->StrongWkLeaker);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VttCompForVsshi: %u\n", Inputs->VttCompForVsshi);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EnVttOdt: %u\n", Inputs->EnVttOdt);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CaVrefConfig: %u\n", Inputs->CaVrefConfig);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BdatEnable %u\nBdatTestType %Xh\nBdatSchema %Xh\n", Inputs->BdatEnable, Inputs->BdatTestType, Inputs->BdatSchema);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RMTLoopCount %Xh\n", Inputs->RMTLoopCount);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EvLoader: %u\n", Inputs->EvLoader);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EvLoaderDelay: %u\n", Inputs->EvLoaderDelay);
#ifdef FSP_FLAG
#ifdef SSA_FLAG
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MmaTestContentPtr: %u\n", Inputs->MmaTestContentPtr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MmaTestContentSize: %u\n", Inputs->MmaTestContentSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MmaTestConfigPtr: %u\n", Inputs->MmaTestConfigPtr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MmaTestConfigSize: %u\n", Inputs->MmaTestConfigSize);
#endif // SSA_FLAG
#endif // FSP_FLAG
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DllBwEn0: %u\nDllBwEn1: %u\nDllBwEn2: %u\nDllBwEn3: %u\n",
    Inputs->DllBwEn0, Inputs->DllBwEn1, Inputs->DllBwEn2, Inputs->DllBwEn3);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PowerTrainingMode: %s optimization\n", Inputs->PowerTrainingMode ? "margin" : "power");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****    MRC TRAINING STEPS     *****\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  TrainingSteps   = &Inputs->TrainingEnables;
  TrainingSteps2  = &Inputs->TrainingEnables2;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.SOT: %u\n", TrainEnString, TrainingSteps->SOT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ERDMPRTC2D: %u\n", TrainEnString, TrainingSteps->ERDMPRTC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ECT: %u\n", TrainEnString, TrainingSteps->ECT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RCVET: %u\n", TrainEnString, TrainingSteps->RCVET);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDMPRT: %u\n", TrainEnString, TrainingSteps->RDMPRT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.JWRL: %u\n", TrainEnString, TrainingSteps->JWRL);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EWRTC2D: %u\n", TrainEnString, TrainingSteps->EWRTC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ERDTC2D: %u\n", TrainEnString, TrainingSteps->ERDTC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s2.EWRDSEQ: %u\n", TrainEnString, TrainingSteps2->EWRDSEQ);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRTC1D: %u\n", TrainEnString, TrainingSteps->WRTC1D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRVC1D: %u\n", TrainEnString, TrainingSteps->WRVC1D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDTC1D: %u\n", TrainEnString, TrainingSteps->RDTC1D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR4MAP: %u\n", Inputs->DDR4MAP);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.DIMMODTT: %u\n", TrainEnString, TrainingSteps->DIMMODTT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.DIMMRONT: %u\n", TrainEnString, TrainingSteps->DIMMRONT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRDSEQT: %u\n", TrainEnString, TrainingSteps->WRDSEQT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRDSUDT: %u\n", TrainEnString, TrainingSteps->WRDSUDT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRSRT: %u\n", TrainEnString, TrainingSteps->WRSRT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDODTT: %u\n", TrainEnString, TrainingSteps->RDODTT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDEQT: %u\n", TrainEnString, TrainingSteps->RDEQT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDAPT: %u\n", TrainEnString, TrainingSteps->RDAPT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.CMDVC: %u\n", TrainEnString, TrainingSteps->CMDVC);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRTC2D: %u\n", TrainEnString, TrainingSteps->WRTC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDTC2D: %u\n", TrainEnString, TrainingSteps->RDTC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRVC2D: %u\n", TrainEnString, TrainingSteps->WRVC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDVC2D: %u\n", TrainEnString, TrainingSteps->RDVC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.LCT: %u\n", TrainEnString, TrainingSteps->LCT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RTL: %u\n", TrainEnString, TrainingSteps->RTL);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.TAT: %u\n", TrainEnString, TrainingSteps->TAT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RMT: %u\n", TrainEnString, TrainingSteps->RMT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.MEMTST: %u\n", TrainEnString, TrainingSteps->MEMTST);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ALIASCHK: %u\n", TrainEnString, TrainingSteps->ALIASCHK);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RCVENC1D: %u\n", TrainEnString, TrainingSteps->RCVENC1D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RMC: %u\n", TrainEnString, TrainingSteps->RMC);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s2.CMDSR: %u\n%s2.CMDDSEQ: %u\n", TrainEnString, TrainingSteps2->CMDSR, TrainEnString, TrainingSteps2->CMDDSEQ);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s2.CMDNORM: %u\n", TrainEnString, TrainingSteps2->CMDNORM);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****      MRC TIMING DATA      *****\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "LpddrMemWriteLatencySet : Set %c\n", Inputs->LpddrMemWriteLatencySet ? 'B' : 'A');

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn = &Inputs->Controller[Controller];
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Controller[%u] ChannelCount: %Xh\n", Controller, ControllerIn->ChannelCount);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn = &ControllerIn->Channel[Channel];
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel[%u].Status: %Xh\n", Channel, ChannelIn->Status);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel[%u].DimmCount: %Xh\n", Channel, ChannelIn->DimmCount);

      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmIn = &ChannelIn->Dimm[Dimm];
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u Status: %Xh\n", CcdString, Controller, Channel, Dimm, DimmIn->Status);
        if (Inputs->MemoryProfile == USER_PROFILE) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tCK    : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tCK);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u NMode  : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.NMode);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tCL    : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tCL);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tCWL   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tCWL);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tFAW   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tFAW);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRAS   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tRAS);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRCDtRP: %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tRCDtRP);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tREFI  : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tREFI);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRFC   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tRFC);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRRD   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tRRD);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRTP   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tRTP);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tWR    : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tWR);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tWTR   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tWTR);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tWTR_L : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tWTR_L);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tWTR_S : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tWTR_S);
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u SpdAddress: %Xh\n", CcdString, Controller, Channel, Dimm, DimmIn->SpdAddress);
        Buffer = (UINT8 *) &DimmIn->Spd.Data;
        DivideValue = 2;

        if (Buffer[2] == MRC_SPD_DDR4_SDRAM_TYPE_NUMBER) {
          DivideValue = 1;
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SPD:           00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
        for (Line = 0; Line < (sizeof (MrcSpd) / (16 * DivideValue)); Line++) {
          Address = Line * 16;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " % 4Xh(% 5u): ", Address, Address);
          for (Offset = 0; Offset < 16; Offset++) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%02X ", Buffer[Address + Offset]);
          }
          for (Offset = 0; Offset < 16; Offset++) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%c", isprint (Buffer[Address + Offset]) ? Buffer[Address + Offset] : '.');
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
        }
      }
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****    TURNAROUND TIMING    *******\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tSG\tDG\tDR\tDD\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "tRd2Rd:\t%Xh\t%Xh\t%Xh\t%Xh\n", Inputs->tRd2Rd.SG, Inputs->tRd2Rd.DG, Inputs->tRd2Rd.DR, Inputs->tRd2Rd.DD);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "tRd2Wr:\t%Xh\t%Xh\t%Xh\t%Xh\n", Inputs->tRd2Wr.SG, Inputs->tRd2Wr.DG, Inputs->tRd2Wr.DR, Inputs->tRd2Wr.DD);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "tWr2Rd:\t%Xh\t%Xh\t%Xh\t%Xh\n", Inputs->tWr2Rd.SG, Inputs->tWr2Rd.DG, Inputs->tWr2Rd.DR, Inputs->tWr2Rd.DD);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "tWr2Wr:\t%Xh\t%Xh\t%Xh\t%Xh\n", Inputs->tWr2Wr.SG, Inputs->tWr2Wr.DG, Inputs->tWr2Wr.DR, Inputs->tWr2Wr.DD);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****    THERMAL OVERWRITE    *******\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ddr4SkipRefreshEn  : %Xh\n",                  Inputs->Ddr4SkipRefreshEn);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnableExtts     : %Xh\n",   ThermEnString, Inputs->EnableExtts);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnableCltm      : %Xh\n",   ThermEnString, Inputs->EnableCltm);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnableOltm      : %Xh\n",   ThermEnString, Inputs->EnableOltm);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnablePwrDn     : %Xh\n",   ThermEnString, Inputs->EnablePwrDn);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnablePwrDnLpddr: %Xh\n",   ThermEnString, Inputs->EnablePwrDnLpddr);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.Refresh2X       : %Xh\n",   ThermEnString, Inputs->Refresh2X);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.DdrThermalSensor: %Xh\n",   ThermEnString, Inputs->DdrThermalSensor);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.LockPTMregs     : %Xh\n",   ThermEnString, Inputs->LockPTMregs);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.UserPowerWeightsEn: %Xh\n", ThermEnString, Inputs->UserPowerWeightsEn);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnergyScaleFact : %Xh\n",   ThermEnString, Inputs->EnergyScaleFact);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim2Lock    : %Xh\n",   ThermEnString, Inputs->RaplLim2Lock);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim2WindX   : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim2WindX);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim2WindY   : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim2WindY);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim2Ena     : %Xh\n",   ThermEnString, Inputs->RaplLim2Ena);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim2Pwr     : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim2Pwr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim1WindX   : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim1WindX);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim1WindY   : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim1WindY);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim1Ena     : %Xh\n",   ThermEnString, Inputs->RaplLim1Ena);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim1Pwr     : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim1Pwr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RaplPwrFlCh0       : %Xh\n",   Inputs->RaplPwrFlCh0);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RaplPwrFlCh01      : %Xh\n",   Inputs->RaplPwrFlCh1);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WarmThresholdCh[%u]Dimm[%u] : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.WarmThreshold[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.HotThresholdCh[%u]Dimm[%u]  : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.HotThreshold[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WarmBudgetCh[%u]Dimm[%u]    : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.WarmBudget[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.HotBudgetCh[%u]Dimm[%u]     : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.HotBudget[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.IdleEnergyCh[%u]Dimm[%u]    : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.IdleEnergy[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.PdEnergyCh[%u]Dimm[%u]      : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.PdEnergy[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ActEnergyCh[%u]Dimm[%u]     : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.ActEnergy[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RdEnergyCh[%u]Dimm[%u]      : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.RdEnergy[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WrEnergyCh[%u]Dimm[%u]      : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.WrEnergy[Channel][Dimm]);
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SrefCfgEna      : %Xh\n",      Inputs->SrefCfgEna);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SrefCfgIdleTmr  : %Xh\n",      Inputs->SrefCfgIdleTmr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ThrtCkeMinDefeat: %Xh\n",      Inputs->ThrtCkeMinDefeat);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ThrtCkeMinTmr   : %Xh\n",      Inputs->ThrtCkeMinTmr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ThrtCkeMinDefeatLpddr: %Xh\n", Inputs->ThrtCkeMinDefeatLpddr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ThrtCkeMinTmrLpddr   : %Xh\n", Inputs->ThrtCkeMinTmrLpddr);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****     DQ BYTE MAPPING     *******\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  ControllerIn = &Inputs->Controller[0];
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelIn = &ControllerIn->Channel[Channel];
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch %u:\n", Channel);
    for (Iteration = 0; Iteration < MrcIterationMax; Iteration++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Iteration %u: %02X %02X\n", Iteration, ChannelIn->DQByteMap[Iteration][0], ChannelIn->DQByteMap[Iteration][1]);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****   DQS BYTE SWIZZLING    *******\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelIn = &ControllerIn->Channel[Channel];
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch %u:", Channel);
    for (Iteration = 0; Iteration < (sizeof (ChannelIn->DqsMapCpu2Dram) / sizeof (ChannelIn->DqsMapCpu2Dram[0])); Iteration++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", ChannelIn->DqsMapCpu2Dram[Iteration]);
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  }
  for (Index = 0; Index < MAX_RCOMP; Index++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RcompResistor[%u]: %u\n", Index, Inputs->RcompResistor[Index]);
  }
  for (Index = 0; Index < MAX_RCOMP_TARGETS; Index++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RcompTarget[%s]: %u\n", GlobalCompOffsetStr[Index], Inputs->RcompTarget[Index]);
  }

  return mrcSuccess;
}

/**
  Print the specified memory to the serial message debug port.

  @param[in] Debug - Serial message debug structure.
  @param[in] Start - The starting address to dump.
  @param[in] Size  - The amount of data in bytes to dump.

  @retval Nothing.
**/
void
MrcPrintMemory (
  IN MrcDebug *const    Debug,
  IN const UINT8 *const Start,
  IN const UINT32       Size
  )
{
  const UINT8  *Address;
  const UINT8  *End;
  UINT32       Line;
  UINT32       Offset;
  union {
    UINT64     Data64[2];
    UINT32     Data32[4];
    UINT16     Data16[8];
    UINT8      Data8[16];
  } Buffer;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "          ");
  for (Offset = 0; Offset < 16; Offset++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%02X ", ((UINT32) Start + Offset) % 16);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  End = Start + Size;
  for (Line = 0; Line < ((Size / 16) + 1); Line++) {
    Address = Start + (Line * 16);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "% 8X: ", Address);
    for (Offset = 0; Offset < 16; Offset++) {
      Buffer.Data8[Offset] = ((Address + Offset) < End) ? Address[Offset] : 0;
    }
    for (Offset = 0; Offset < 16; Offset++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, ((Address + Offset) < End) ? "%02X " : "   ", Buffer.Data8[Offset]);
    }
    for (Offset = 0; (Offset < 16) && ((Address + Offset) < End); Offset++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%c", isprint (Buffer.Data8[Offset]) ? Buffer.Data8[Offset] : '.');
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  }
  return;
}
#endif
