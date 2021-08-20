/** @file
  This file include all the common tools for the MRC algorithms

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
#include "MrcCommon.h"
#include "MrcReadDqDqs.h"

#define MRC_EXIT_VALUE (0xFF)

#ifdef MRC_DEBUG_PRINT
GLOBAL_REMOVE_IF_UNREFERENCED const char  CcdString[] = "Controller, Channel, Dimm";
GLOBAL_REMOVE_IF_UNREFERENCED const char  RcvEnDelayString[] = "RcvEnDelay";
GLOBAL_REMOVE_IF_UNREFERENCED const char  WrVDelayString[] = "WriteVoltage";
GLOBAL_REMOVE_IF_UNREFERENCED const char  RdVDelayString[] = "ReadVoltage";
GLOBAL_REMOVE_IF_UNREFERENCED const char  DqsDelayString[] = "DqsDelay";
GLOBAL_REMOVE_IF_UNREFERENCED const char  CmdVDelayString[] = "CmdVoltage";
#endif

/**
  Verify that the indicated socket is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.

  @retval Success if present and enabled, otherwise SocketNotSupported.
**/
MrcStatus
IsSocketPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket
  )
{
  return ((Socket < MAX_CPU_SOCKETS) ? mrcSuccess : mrcSocketNotSupported);
}

/**
  Verify that the indicated controller is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.

  @retval Success if present and enabled, otherwise ControllerNotSupported.
**/
MrcStatus
IsControllerPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller
  )
{
  MrcStatus Status;

  Status = IsSocketPresent (MrcData, Socket);
  if (Status == mrcSuccess) {
    return (((Controller < MAX_CONTROLLERS) &&
             (MrcData->Outputs.Controller[Controller].Status == CONTROLLER_PRESENT)) ?
             mrcSuccess : mrcControllerNotSupported);
  }
  return (Status);
}

/**
  Verify that the indicated channel is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.
  @param[in] Channel    - Zero based memory channel number.

  @retval Success if present and enabled, otherwise ChannelNotSupported.
**/
MrcStatus
IsChannelPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller,
  const UINT32                Channel
  )
{
  MrcStatus Status;

  Status = IsControllerPresent (MrcData, Socket, Controller);
  if (Status == mrcSuccess) {
    return (((Channel < MAX_CHANNEL) &&
             (MrcData->Outputs.Controller[Controller].Channel[Channel].Status == CHANNEL_PRESENT)) ?
             mrcSuccess : mrcChannelNotSupport);
  }
  return (Status);
}

/**
  Verify that the indicated DIMM is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.
  @param[in] Channel    - Zero based memory channel number.
  @param[in] Dimm       - Zero based memory DIMM number.

  @retval Success if present and enabled, otherwise DimmNotSupported.
**/
MrcStatus
IsDimmPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller,
  const UINT32                Channel,
  const UINT32                Dimm
  )
{
  MrcStatus Status;

  Status = IsChannelPresent (MrcData, Socket, Controller, Channel);
  if (Status == mrcSuccess) {
    return (((Dimm < MAX_DIMMS_IN_CHANNEL) &&
             (MrcData->Outputs.Controller[Controller].Channel[Channel].Dimm[Dimm].Status == DIMM_PRESENT)) ?
             mrcSuccess : mrcDimmNotSupport);
  }
  return (Status);
}

/**
  Verify that the indicated rank is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.
  @param[in] Channel    - Zero based memory channel number.
  @param[in] Dimm       - Zero based memory DIMM number.
  @param[in] Rank       - Zero based memory rank number in the DIMM.

  @retval Success if present and enabled, otherwise RankNotSupported.
**/
MrcStatus
IsRankPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller,
  const UINT32                Channel,
  const UINT32                Dimm,
  const UINT32                Rank
  )
{
  MrcStatus Status;

  Status = IsDimmPresent (MrcData, Socket, Controller, Channel, Dimm);
  if (Status == mrcSuccess) {
    return (((Rank < MAX_RANK_IN_DIMM) &&
             (((UINT32) MrcData->Outputs.Controller[Controller].Channel[Channel].Dimm[Dimm].RankInDimm - 1) >= Rank)) ?
             mrcSuccess : mrcRankNotSupported);
  }
  return (Status);
}

/**
  Return the rank mask in channel if rank exist exist.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] Channel - Channel to work on.
  @param[in] Rank    - Rank to check.

  @retval Bit mask of Rank requested if the Rank exists in the system.
**/
UINT8
MrcRankInChannelExist (
  IN MrcParameters *const MrcData,
  IN const UINT8          Rank,
  IN const UINT8          Channel
  )
{
  return (MRC_BIT0 << Rank) & MrcData->Outputs.Controller[0].Channel[Channel].ValidRankBitMask;
}

/**
  Return the number of ranks in specific dimm.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] Channel - Channel to work on.
  @param[in] Dimm    - Dimm in channel to return.

  @retval The number of ranks in the dimm.
**/
UINT8
MrcGetRankInDimm (
  IN MrcParameters *const MrcData,
  IN const UINT8          Dimm,
  IN const UINT8          Channel
  )
{
  return MrcData->Outputs.Controller[0].Channel[Channel].Dimm[Dimm].RankInDimm;
}

/**
  Returns whether Channel is or is not present.

  @param[in] Outputs - Pointer to MRC global Output data.
  @param[in] Channel - Channel to test.

  @retval TRUE  - if there is at least one enabled DIMM in the channel.
  @retval FALSE - if there are no enabled DIMMs in the channel.
**/
BOOLEAN
MrcChannelExist (
  IN const MrcOutput *const Outputs,
  IN const UINT8            Channel
  )
{

  return (Outputs->Controller[0].Channel[Channel].Status == CHANNEL_PRESENT) ? TRUE : FALSE;
}

/**
  This function disable channel parameters.
  After this function the MRC don't use with the channel.

  @param[in] MrcData           - Include all MRC global data.
  @param[in] ChannelToDisable  - Channel to disable.
  @param[in] SkipDimmCapacity  - Switch to skip setting the DimmCapacity to 0 for the dimms in the channel disabled.

  @retval Nothing
**/
void
MrcChannelDisable (
  IN MrcParameters *const MrcData,
  IN const UINT8          ChannelToDisable,
  IN const UINT8          SkipDimmCapacity
  )
{
  MrcChannelOut *ChannelOut;
  MrcDimmOut    *DimmOut;
  UINT32        Dimm;

  ChannelOut = &MrcData->Outputs.Controller[0].Channel[ChannelToDisable];
  if (ChannelOut->Status == CHANNEL_PRESENT) {
    ChannelOut->Status            = CHANNEL_DISABLED;
    ChannelOut->ValidRankBitMask  = 0;
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      DimmOut = &ChannelOut->Dimm[Dimm];
      if (DimmOut->Status == DIMM_PRESENT) {
        DimmOut->Status     = DIMM_DISABLED;
        DimmOut->RankInDimm = 0;
        if (!SkipDimmCapacity) {
          DimmOut->DimmCapacity = 0;
        }
      }
    }
  }
}

/**
  Convert the given frequency and reference clock to a clock ratio.
  This function doesn't support OddRatioMode because it's not used in OddRatioMode scenarios.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Frequency - The memory frequency.
  @param[in] RefClk    - The memory reference clock.
  @param[in] BClk      - The base system reference clock.

  @retval Returns the memory clock ratio.
**/
MrcClockRatio
MrcFrequencyToRatio (
  IN MrcParameters *const  MrcData,
  IN const MrcFrequency    Frequency,
  IN const MrcRefClkSelect RefClk,
  IN const MrcBClkRef      BClk
  )
{
  const MRC_FUNCTION *MrcCall;
  UINT64 Value;
  UINT64 FreqValue;
  UINT32 RefClkValue;
  UINT32 BClkValue;

  MrcCall     = MrcData->Inputs.Call.Func;
  BClkValue   = (BClk == 0) ? (BCLK_DEFAULT / 100000) : (BClk / 100000);
  RefClkValue = (RefClk == MRC_REF_CLOCK_100) ? 200000 : 266667;
  FreqValue   = MrcCall->MrcMultU64x32 (Frequency, 1000000000ULL);
  Value       = MrcCall->MrcDivU64x64 (FreqValue, (RefClkValue * BClkValue), NULL);
  Value       = ((UINT32) Value + 500) / 1000;
  return ((MrcClockRatio) Value);
}

/**
  Convert the given ratio and reference clocks to a memory frequency.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] Ratio   - The memory ratio.
  @param[in] RefClk  - The memory reference clock.
  @param[in] BClk    - The base system reference clock.

  @retval Returns the memory frequency.
**/
MrcFrequency
MrcRatioToFrequency (
  IN MrcParameters *const  MrcData,
  IN const MrcClockRatio   Ratio,
  IN const MrcRefClkSelect RefClk,
  IN const MrcBClkRef      BClk
  )
{
  const MrcInput     *Inputs;
  const MRC_FUNCTION *MrcCall;
  MrcClockRatio      LocalRatio;
  UINT64 Value;
  UINT32 BClkValue;
  UINT32 RefClkValue;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;

  LocalRatio  = Ratio;
  BClkValue   = (BClk == 0) ? BCLK_DEFAULT : BClk;
  RefClkValue = (RefClk == MRC_REF_CLOCK_100) ? 200000000 : 266666667;
  if (MrcData->Outputs.OddRatioMode && (Ratio != 0)) {
    RefClkValue = RefClkValue / 2;
    LocalRatio  = (Ratio * 2) + 1;
  }
  Value  = MrcCall->MrcMultU64x32 (RefClkValue, LocalRatio);
  Value  = MrcCall->MrcMultU64x32 (Value, BClkValue);
  Value  += 50000000000000ULL;
  Value  = MrcCall->MrcDivU64x64 (Value, 100000000000000ULL, NULL);
  return ((MrcFrequency) Value);
}

/**
  Convert the given ratio and reference clocks to a memory clock.

  @param[in] Ratio  - The memory ratio.
  @param[in] RefClk - The memory reference clock.
  @param[in] BClk   - The base system reference clock.

  @retval Returns the memory clock in femtoseconds.
**/
UINT32
MrcRatioToClock (
  IN MrcParameters *const  MrcData,
  IN const MrcClockRatio   Ratio,
  IN const MrcRefClkSelect RefClk,
  IN const MrcBClkRef      BClk
  )
{
  const MrcInput     *Inputs;
  const MRC_FUNCTION *MrcCall;
  MrcClockRatio      LocalRatio;
  UINT32 BClkValue;
  UINT32 RefClkValue;
  UINT32 Factor;
  UINT64 Value;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;

  LocalRatio  = Ratio;
  BClkValue   = (BClk == 0) ? 100000000UL : BClk;
  Factor      = BClkValue / 100000UL;
  RefClkValue = (RefClk == MRC_REF_CLOCK_100) ? 1000000000UL : 1333333333UL;
  if (MrcData->Outputs.OddRatioMode  && (Ratio != 0)) {
    RefClkValue = RefClkValue / 2;
    LocalRatio  = (Ratio * 2) + 1;
  }
  Value       = MrcCall->MrcMultU64x32 (Factor, RefClkValue);
  Value       = MrcCall->MrcMultU64x32 (Value, LocalRatio);
  return ((Value == 0) ? 0 : (UINT32) MrcCall->MrcDivU64x64 (10000000000000000000ULL, Value, NULL));
}

/**
  This function return the DIMM number according to the rank number.

  @param[in] Rank - The requested rank.

  @retval The DIMM number.
**/
UINT8
MrcGetDimmFromRank (
  IN const UINT8 Rank
  )
{
  UINT8 Dimm;

  if (Rank == rRank0 || Rank == rRank1) {
    Dimm = dDIMM0;
  } else {
    Dimm = dDIMM1;
  }

  return Dimm;
}

/**
  This function sets the memory frequency.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess on success, mrcFrequencyError on error.
**/
MrcStatus
McFrequencySet (
  IN MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION            *MrcCall;
  MrcDebug                      *Debug;
  const MrcInput                *Inputs;
  MrcIntOutput                  *MrcIntData;
  MrcOutput                     *Outputs;
  MrcFrequency                  NewFrequency;
  MrcClockRatio                 Ratio;
  MrcRefClkSelect               RefClk;
  MrcStatus                     Status;
  UINT64                        Timeout;
  UINT32                        MemoryClock;
  UINT8                         MemoryRatioMax;
  BOOLEAN                       OddRatioMode;
  BOOLEAN                       ExtendedDdrOverclock;
  PCU_CR_MC_BIOS_REQ_PCU_STRUCT           McBiosReq;
  MCDECS_CR_MCDECS_CBIT_MCMAIN_STRUCT     McdecsCbit;
  MCSCHEDS_CR_SCHED_CBIT_STRUCT           SchedCbit;
  MCDECS_CR_MC_INIT_STATE_G_MCMAIN_STRUCT McInitStateG;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Status      = mrcSuccess;
  ExtendedDdrOverclock = Outputs->ExtendedDdrOverclock;

  NewFrequency = MrcGetCurrentMemoryFrequency (MrcData, &MemoryClock, &Ratio, &RefClk, &OddRatioMode);
  if (NewFrequency != fNoInit) {
    if ((Inputs->SaGv != MrcSaGvEnabled) || (MrcIntData->SaGvPoint != MrcSaGvPointHigh)) {
      Outputs->Frequency   = NewFrequency;
      Outputs->MemoryClock = MemoryClock;
      Outputs->RefClk      = RefClk;
      Outputs->Ratio       = Ratio;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING: Memory frequency is already initialized to %u\n", Outputs->Frequency);
      return Status;
    }
  }
  //
  // Set the reference clock, ratio and run_busy bit.
  //
  if (Inputs->BootMode == bmCold) {
    if ((Inputs->MemoryProfile == USER_PROFILE) && (Inputs->Ratio > 0)) {
      Outputs->Ratio = Inputs->Ratio;
    } else {
      Outputs->Ratio = MrcFrequencyToRatio (MrcData, Outputs->Frequency, Outputs->RefClk, Inputs->BClkFrequency);
    }
  }

  MemoryRatioMax = (ExtendedDdrOverclock) ? MEMORY_EXTENDED_RATIO_MAX : MEMORY_RATIO_MAX;

  if ((MEMORY_RATIO_MIN > Outputs->Ratio) || (MemoryRatioMax < Outputs->Ratio)) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "Invalid DDR ratio of %u specified, range %u - %u\n",
      Outputs->Ratio,
      MEMORY_RATIO_MIN,
      MemoryRatioMax
      );
    return mrcFrequencyError;
  }

  if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint == MrcSaGvPointHigh)) {
    McdecsCbit.Data = MrcReadCR (MrcData, MCDECS_CR_MCDECS_CBIT_MCMAIN_REG);
    McdecsCbit.Bits.dis_msg_clk_gate = 1;
    MrcWriteCR (MrcData, MCDECS_CR_MCDECS_CBIT_MCMAIN_REG, McdecsCbit.Data);
  }

  McBiosReq.Data          = 0;
  McBiosReq.Bits.REQ_DATA = (Outputs->Ratio & PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_MSK);
  if (ExtendedDdrOverclock) {
    McBiosReq.Bits.REQ_DATA_MSB = (Outputs->Ratio >> PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_WID) & PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_MSB_WID;
  }
  McBiosReq.Bits.REQ_TYPE = (Outputs->RefClk == MRC_REF_CLOCK_133) ? 0 : 1;
  McBiosReq.Bits.REQ_QCLK_ODD_RATIO = Outputs->OddRatioMode;
  McBiosReq.Bits.RUN_BUSY = 1;
  MrcWriteCR (MrcData, PCU_CR_MC_BIOS_REQ_PCU_REG, McBiosReq.Data);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Attempting value = 0x%x - Pll busy wait ", McBiosReq.Data);
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;  // 10 sec timeout
  while (McBiosReq.Bits.RUN_BUSY && (MrcCall->MrcGetCpuTime (MrcData) < Timeout)) {
    McBiosReq.Data = MrcReadCR (MrcData, PCU_CR_MC_BIOS_REQ_PCU_REG);
  }

  if (McBiosReq.Bits.RUN_BUSY) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "- NOT DONE. DDR frequency Update FAILED!\n");
    return mrcFrequencyError;
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "- done\n");
  }

  Outputs->Frequency = MrcGetCurrentMemoryFrequency (MrcData, &MemoryClock, &Ratio, &RefClk, &OddRatioMode);
  MRC_DEBUG_MSG (
    Debug,
    (Ratio == Outputs->Ratio) ? MSG_LEVEL_NOTE : MSG_LEVEL_ERROR,
    "Requested/actual ratio %u/%u, OddRatio=%u, Frequency=%u, BClk=%uHz RefClk=%uMHz, tCK=%ufs\n",
    Outputs->Ratio,
    Ratio,
    OddRatioMode,
    Outputs->Frequency,
    Inputs->BClkFrequency,
    (RefClk == MRC_REF_CLOCK_133) ? 133 : 100,
    MemoryClock
    );

  if (Ratio != Outputs->Ratio) {
    if (Ratio == 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: Pll locked with Ratio set to 0.\n");
    }
    return mrcFrequencyError;
  }

  //
  // Wait on RCOMP Done.  Needed to ensure Rcomp completes on warm reset/S3 before restoring dclk_enable.
  //
  Status = CheckFirstRcompDone (MrcData);
  if (Status != mrcSuccess) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "RComp did not complete before the timeout in McFrequencySet\n");
    return Status;
  }

  MrcWait (MrcData, 10 * HPET_1US);

  if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint == MrcSaGvPointHigh)) {
    McdecsCbit.Bits.dis_msg_clk_gate = 0;
    MrcWriteCR (MrcData, MCDECS_CR_MCDECS_CBIT_MCMAIN_REG, McdecsCbit.Data);
    //
    // Exit DDR Self-Refresh before the second MRC run:
    //  1. Disable clock gating to allow REFFSM progress: MCHBAR_CH*_CR_SCHED_CBIT_0_0_0_MCHBAR.dis_clk_gate = 1
    //  2. Disable Refreshes so the REFFSM will not leave IDLE state once reached - MC_INIT_STAGE_G.refresh_enable = 0
    //  3. Disable Self-Refresh (to cause the SRX) - MCDECS_CR_PM_SREF_CONFIG.SR_Enable = 0
    //  4. Re-enable clock gating
    //
    SchedCbit.Data = MrcReadCR (MrcData, MCHBAR_CH0_CR_SCHED_CBIT_REG);
    SchedCbit.Bits.dis_clk_gate = 1;
    MrcWriteCrMulticast (MrcData, MCSCHEDS_CR_SCHED_CBIT_REG, SchedCbit.Data);

    McInitStateG.Data = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
    McInitStateG.Bits.refresh_enable = 0;
    MrcWriteCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG, McInitStateG.Data);

    Status = ExitSR (MrcData);
    if (Status != mrcSuccess) {
      return Status;
    }

    SchedCbit.Bits.dis_clk_gate = 0;
    MrcWriteCrMulticast (MrcData, MCSCHEDS_CR_SCHED_CBIT_REG, SchedCbit.Data);

    //
    // Change MC mode from Normal to CPGC
    //
    MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG, REUT_Testing_Mode << MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_Initialization_Mode_OFF);
    MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG, REUT_Testing_Mode << MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_Initialization_Mode_OFF);
    //
    // Reset FIFOs as we might have got MR4 during Normal mode while new frequency doesn't match MC and memory MRs.
    //
    IoReset (MrcData);
  }

  return Status;
}

/**
  Returns the extrapolated margin to a fixed # of errors (logT)
  vrefpass is 10x the first passing margin (with no errors) (10x used for int math)
  Errors at vrefpass/10+1 = log1
  Errors at vrefpass/10+2 = logT

  @param[in]      vrefpass      - 10x the first pass margin (w/no errors) (10x used for int match)
  @param[in]      errLog_1      - Errors at vrefpass/10+1
  @param[in]      errLog_2      - Errors at vrefpass/10+2
  @param[in]      errLog_Target - Error target determines extrapolation vs interpolation
  @param[in, out] *berStats     - Used to track interpolation vs extrapolation or if the slope is non-monotonic.
                                  NOTE: target would be Interpolation only

  @retval Interpolated/Extrapolated vref with the scale increased by 10.
**/
UINT32
interpolateVref (
  IN     UINT32  vrefpass,
  IN     UINT32  errLog_1,
  IN     UINT32  errLog_2,
  IN     UINT32  errLog_Target,
  IN OUT UINT32  *berStats
  )
{
  UINT32 vref;
  UINT32 slope;
  UINT32 ErrLogDiff;

  ErrLogDiff = errLog_2 - errLog_1;
  if (errLog_2 <= errLog_1) {
    berStats[3] += 1;                 // non-monotonic case
    return (vrefpass * 10 + 10);
  } else if (errLog_2 < errLog_Target) {
    berStats[2] += 1;                 // error target above errLog_2 -> extrapolation
  } else if (errLog_1 <= errLog_Target) {
    berStats[1] += 1;                 // error target between errLog_1 and errLog_2 -> interpolation
  } else {
    berStats[0] += 1;                 // error target below errLog_1 -> extrapolation
  }

  //
  //extrapolate above errLog_2, max extrapolation is 1 tick (10)
  //
  if (errLog_2 < errLog_Target) {
    vref =  vrefpass * 10 + 20 + MIN (10, (10 * (errLog_Target - errLog_2)) / (ErrLogDiff));
  } else if ((errLog_1 <= errLog_Target) && (errLog_Target <= errLog_2) && (ErrLogDiff != 0)) {
    vref =  vrefpass * 10 + 10 + (10 * (errLog_Target - errLog_1)) / (ErrLogDiff);  //interpolate
  } else {
    //
    //extrapolate below errLog_1
    //
    slope = (ErrLogDiff) > errLog_1 ? (ErrLogDiff) : errLog_1;
    if (slope != 0) {
      vref = vrefpass * 10 + (10 * errLog_Target) / slope;
    } else {
      vref = 0;
    }
  }

  return vref;  //returns a (vref * 10) interpolation/extrapolation
};

/**
  This function swaps a subfield, within a 32 bit integer value with the specified value.

  @param[in] CurrentValue - 32 bit input value.
  @param[in] NewValue     - 32 bit New value.
  @param[in] Start        - Subfield start bit.
  @param[in] Length       - Subfield length in bits/

  @retval The updated 32 bit value.
**/
UINT32
MrcBitSwap (
  IN UINT32       CurrentValue,
  IN const UINT32 NewValue,
  IN const UINT8  Start,
  IN const UINT8  Length
  )
{
  UINT32 mask;

  //
  // Do bitwise replacement:
  //
  mask = (MRC_BIT0 << Length) - 1;
  CurrentValue &= ~(mask << Start);
  CurrentValue |= ((NewValue & mask) << Start);

  return CurrentValue;
}

/**
  This function returns the maximim Rx margin for a given Channel, Rank(s), and byte.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Param     - Test parameter.
  @param[in] Channel   - Channel to calculate max Rx margin.
  @param[in] RankRx    - Rank index.  0xFF causes all ranks to be considered.
  @param[in] Byte      - Byte to check.
  @param[in] Sign      - Sign of the margins (0 - negative/min, 1 - positive/max).
  @param[in] MaxMargin - Current max margin value.

  @retval The max Rx margin, either MaxMargin or value from stored margins.
**/
UINT8
MrcCalcMaxRxMargin (
  IN MrcParameters  *const MrcData,
  IN UINT8                 Param,
  IN const UINT8           Channel,
  IN const UINT8           RankRx,
  IN const UINT8           Byte,
  IN const UINT8           Sign,
  IN UINT16                MaxMargin
  )
{
  const MRC_FUNCTION *MrcCall;
  MrcChannelOut *ChannelOut;
  UINT16        ParamList[2];
  UINT8         ParamLen;
  UINT8         Idx;
  UINT8         Start;
  UINT8         Stop;
  UINT8         Rank;
  UINT8         MinRange;
  UINT16        MaxRange;

  MrcCall = MrcData->Inputs.Call.Func;
  MrcCall->MrcSetMem ((UINT8 *) ParamList, sizeof (ParamList), 0);

  //
  // Check for saturation on Rx Timing
  //
  if (RankRx >= MAX_RANK_IN_CHANNEL) {
    //
    // If desired for all ranks
    //
    Start = 0;              // Start in rank 0
    Stop = 4;               // Up to 4 ranks
  } else {
    Start = RankRx;
    Stop  = RankRx + 1;
  }

  ParamLen = 1;
  MinRange = 0;
  MaxRange = 63;
  if (Param == RcvEnaX) {
  MaxRange = 511;
  }
  ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
  for (Rank = Start; Rank < Stop; Rank++) {
    if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
      if (Param == RdT) {
        ParamList[0] = ChannelOut->RxDqsP[Rank][Byte];
        ParamList[1] = ChannelOut->RxDqsN[Rank][Byte];
        ParamLen = 2;
      } else if (Param == RdV) {
        ParamList[0] = 0x3F & ChannelOut->RxVref[Byte];
        if (ParamList[0] > 31) { // convert to positive scale [0:63]
          ParamList[0] = ParamList[0] - 32;
        } else {
          ParamList[0] += 32;
        }
        // for RdV offset step is 2x
        MaxMargin /= 2;
      } else if (Param == RcvEnaX) {
        ParamList[0] = ChannelOut->RcvEn[Rank][Byte];
        MaxMargin *= 4;
      }
      for (Idx = 0; Idx < ParamLen; Idx++) {
        if (Sign == 0) {
          if (MaxMargin > ParamList[Idx] - MinRange) {
            MaxMargin = ParamList[Idx] - MinRange;
          }
        } else {
          if (MaxMargin > MaxRange - ParamList[Idx]) {
            MaxMargin = MaxRange - ParamList[Idx];
          }
        }
      }

      // Scale back MaxMargin
      if (Param == RdV) {
        MaxMargin *= 2;
        break;
      } else if (Param == RcvEnaX) {
        MaxMargin /= 4;
      }
    }
  }
  return (UINT8) MaxMargin;
}

/**
  This function returns the maximim Vref margin for a given Channel if WrV.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Channel   - Channel to calculate max Tx margin.
  @param[in] RankTx    - Rank Mask for DDR4.
  @param[in] Byte      - Zero based byte number.
  @param[in] Param     - Parameter of Vref to use
  @param[in] Sign      - Sign of the margins (0 - negative/min, 1 - positive/max).
  @param[in] MaxMargin - Current max margin value.
  @param[in] Pda       - Use PDA or not.

  @retval The max Vref margin, either MaxMargin or value from stored margins.
**/
UINT8
MrcCalcMaxVrefMargin (
  IN MrcParameters  *const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           RankTx,
  IN const UINT8           Byte,
  IN const UINT8           Param,
  IN const UINT8           Sign,
  IN UINT8                 MaxMargin,
  IN BOOLEAN               Pda
  )
{

  MrcDebug                                          *Debug;
  MrcIntOutput                                      *MrcIntData;
  MrcIntControllerOut                               *IntControllerOut;
  MrcOutput                                         *Outputs;
  MrcChannelOut                                     *ChannelOut;
  MrcRankOut                                        *RankOut;
  UINT8                                             VrefValue;
  INT8                                              CurrentVrefOff;
  INT8                                              TotalVrefOff;
  UINT8                                             MaxRange;
  UINT8                                             TempRange;
  INT8                                              CurrVref;
  UINT8                                             Rank;
  BOOLEAN                                           Ddr4;

  MrcIntData       = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntControllerOut = &MrcIntData->Controller[0];
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  Ddr4             = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  if (Ddr4 && (Param == WrV)) {
    //
    // Check for saturation on Rx Timing
    //
    ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
    MaxRange = MaxMargin;
    TempRange = MaxMargin;
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel) & RankTx) {
        RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[Rank % 2];
        if (Pda) {
          CurrVref = MrcVrefDqToOffset (RankOut->Ddr4PdaMr6[Byte] & 0x7F);
        } else {
          CurrVref = MrcVrefDqToOffset ((UINT8) (RankOut->MR[mrMR6] & 0x7F));
        }
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MrcSetMR6_DDR4  Channel %u rank %u RankOut->MR[mrMR6]= 0x%X\n",Channel, rank, RankOut->MR[mrMR6]);
        if (Sign == 0) {
          if (MaxMargin > (36 + CurrVref)) {
            TempRange = 36 + CurrVref;
          }
        } else {
          if (MaxMargin > (36 - CurrVref)) {
            TempRange = 36 - CurrVref;
          }
        }
        MaxRange = MIN (MaxRange, TempRange);
      }
    }
  } else {
    if (Param == CmdV) {
      if (Ddr4 && Channel == 1) {
        VrefValue = (UINT8) IntControllerOut->VrefAdjust1.Bits.Ch1VrefCtl;
      } else {
        VrefValue = (UINT8) IntControllerOut->VrefAdjust1.Bits.CAVrefCtl;
      }
    } else if (Channel == 0) {
      VrefValue = (UINT8) IntControllerOut->VrefAdjust1.Bits.Ch0VrefCtl;
    } else {
      VrefValue = (UINT8) IntControllerOut->VrefAdjust1.Bits.Ch1VrefCtl;
    }

    CurrentVrefOff = (INT8) (MrcSE (VrefValue, 7, 8));
    if (Sign == 0) {
      TotalVrefOff = (INT8) -MaxMargin;
    } else {
      TotalVrefOff = (INT8) MaxMargin;
    }
    TotalVrefOff += CurrentVrefOff;
    //  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dparam %x, MaxMargin %d, CurrentVref %d, TotalVref %d\n", Channel, param, MaxMargin, CurrentVrefOff, TotalVrefOff);
    if ((Sign == 0) && (TotalVrefOff < (-1 * MAX_POSSIBLE_VREF))) {
      //
      // Saturation point of Vref
      //
      MaxRange = MAX_POSSIBLE_VREF + CurrentVrefOff;
      //    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Saturation possible C%d, New MaxMargin %d\n", Channel, MaxRange);
    } else if ((Sign == 1) && (TotalVrefOff > MAX_POSSIBLE_VREF)) {
      //
      // Saturation point of Vref
      //
      MaxRange = MAX_POSSIBLE_VREF - CurrentVrefOff;
      //    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Saturation possible C%d, New MaxMargin %d\n", Channel, MaxRange);
    } else {
      MaxRange = MaxMargin;
    }
  }

  return MaxRange;
}

/**
  This function determines if a bit lane[0-7] has seen a pass and a fail in each byte for all channels populated.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] chBitmask - Bit mask of channels to consider.
  @param[in] OnePass   - Array of Bit masks marking DQ lanes has had a passing value.
  @param[in] OneFail   - Array of Bit masks marking DQ lanes has had a failing value.

  @retval The AND result of each Channel/byte for OnePass and OneFail.
**/
UINT8
MrcAndBytes (
  IN MrcParameters *const MrcData,
  IN const UINT8          chBitmask,
  IN UINT8                OnePass[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN UINT8                OneFail[MAX_CHANNEL][MAX_SDRAM_IN_DIMM]
  )
{
  UINT8 Res;
  UINT8 Channel;
  UINT8 byte;

  Res = 0xFF;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
      continue;
    }

    for (byte = 0; byte < MrcData->Outputs.SdramCount; byte++) {
      Res &= OnePass[Channel][byte];
      Res &= OneFail[Channel][byte];
    }
  }

  return Res;
}

/**
  This function Finds the margin for all channels/all bits. The margin sweep is a parameterized
  Assume REUT test has already been fully setup to run
  This will unscale the results such that future tests start at the correct point
  Uses ChangeMargin function to handle a variety cases (Timing, Voltage, Fan, etc.)

  @param[in]     MrcData    - Include all MRC global data.
  @param[in]     chBitMask  - Channel BIT mask for Channel(s) to work on
  @param[in]     Rank       - Rank to work on
  @param[in,out] marginbit  - used as the return data ( real margin measurement, no 10x)
                              marginbit[ch,byte,bit,sign] = abs(Margin)
                              Note: If param == RdTBit/RdVBit/WrVBit, marginbit is also the starting point
  @param[in,out] marginbyte - provides the starting point on a per byte basis (still 10x)
  @param[in]     param      - defines the margin type
  @param[in]     mode       - allows for different types of modes for margining
                              {Bit0: PhLock (keep all bytes within in ch in phase),
                               Bit1: Ch2Ch Data out of phase (LFSR seed)
                               Bits 15:2: Reserved}
  @param[in]     MaxMargin  - Default Maximum margin
  @param[in]     MsgPrint   - Enables printing of debug messages

  @retval mrcSuccess if successful, otherwise it returns an error status.
**/
MrcStatus
MrcGetMarginBit (
  IN     MrcParameters *const MrcData,
  IN     UINT8                chBitMask,
  IN     UINT8                Rank,
  IN OUT UINT32               marginbit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES],
  IN OUT UINT32               marginbyte[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8                param,
  IN     UINT16               mode,
  IN     UINT8                MaxMargin,
  IN    BOOLEAN               MsgPrint
  )
{
  MrcDebug        *Debug;
  MrcInput        *Inputs;
  MrcOutput       *Outputs;
  MrcDebugMsgLevel DebugLevel;
  MrcStatus       Status;
  UINT8           Channel;
  UINT8           Byte;
  UINT8           RankMask;
  UINT8           bit;
  UINT8           sign;
  INT8            realSign;
  UINT8           pbyte;
  BOOLEAN         PerCh;
  UINT8           PerBit;
  UINT8           SeqLC[4];
  UINT8           Points2D;
  UINT8           DoneMask;
  UINT8           ByteMax;
  UINT8           SkipWait;
  UINT8           chPass;
  UINT8           chFail;
  UINT8           NoECC;
  UINT8           AllFail;
  // Set to 1 after ch/byte/bit has a passing point
  UINT8           OnePass[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  // Set to 1 after ch/byte/bit has a failing point
  UINT8           OneFail[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8           ErrByte;
  UINT8           ErrECC;
  UINT32          ErrLower;
  UINT32          ErrUpper;
  UINT8           MinMargin;
  UINT32          value0;
  UINT32          value1;
  UINT32          v0;
  UINT32          CMargin[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];    // Current Margin Point Testing
  UINT32          ABMargin[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];             // Average Byte Margin
  UINT32          MinTested[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];  // Min Margin Point Tested
  UINT8           PrintPetByte;
  INT8            RdTAdjust;
  UINT32          Offset;
  UINT32          BitTimePerBit;
  UINT8           BitMask;
  BOOLEAN         Ddr4;
  MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_STRUCT ReutGlobalCtl;

  Status    = mrcSuccess;
  SkipWait  = 0;
  NoECC     = 0;
  Inputs    = &MrcData->Inputs;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  RankMask  = 1 << Rank;
  Ddr4      = Outputs->DdrType == MRC_DDR_TYPE_DDR4;
  DebugLevel = MsgPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;

  //
  // Define Constants
  //
  ByteMax = MaxMargin;

  //
  // Define the correct loopcount for test
  //
  if (Outputs->DQPat == SegmentWDB) {
    SeqLC[0] = Outputs->DQPatLC;
    SeqLC[1] = Outputs->DQPatLC;
    SeqLC[2] = Outputs->DQPatLC + 4;
    SeqLC[3] = Outputs->DQPatLC + 2;
  } else {
    SeqLC[0] = 1;
    SeqLC[1] = 1;
    SeqLC[2] = 1;
    SeqLC[3] = 1;
  }
  //
  // How many points to test
  //
  Points2D = 1 + (param / 16);

  //
  // Define PerByte param for PerBit cases
  //
  if (param == RdTBit) {
    pbyte   = RdT;
    PerBit  = 1;
  } else if (param == WrTBit) {
    pbyte   = WrT;
    PerBit  = 1;
  } else if (param == RdVBit) {
    pbyte   = RdV;
    PerBit  = 1;
  } else {
    pbyte   = 0;
    PerBit  = 0;
  }
  //
  // Print results PerBit or PerByte
  //
  PrintPetByte = (param == RdT || param == WrT || param == RdV);
  //
  // Created for debug purpose
  // Are we using DIMM Vref?  If so, need to use the same Vref across all bytes
  //
  PerCh = ((param == WrFan2) || (param == WrFan3) || (param == WrV) || (mode & 0x1)) && (PerBit == 0);

  //
  // Get Average Byte back to real margin numbers
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (chBitMask & (MRC_BIT0 << Channel)) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        ABMargin[Channel][Byte] = (marginbyte[Channel][Byte][0] + marginbyte[Channel][Byte][1]) / 20;
      }
    }
  }
  //
  // Find Left and Right Edges
  //
  for (sign = 0; sign < 2; sign++) {
    realSign = (INT8) ((2 * sign) - 1);
    MRC_DEBUG_MSG (Debug, DebugLevel, "\n+--MrcGetMarginBit, rsign = %d\n", realSign);
    MRC_DEBUG_MSG (Debug, DebugLevel, (PrintPetByte) ? "\nMargin\tBits\n" : "");

    //
    // Initialize variables
    //
    DoneMask = 0xFF;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(chBitMask & (MRC_BIT0 << Channel))) {
        continue; // This channel is not populated
      }

      MinMargin = 0x7F; // Start with a huge unsigned number
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        //
        // Init arrays to 0
        //
        OnePass[Channel][Byte] = OneFail[Channel][Byte] = 0;

        //
        // Find MaxMargin for this byte
        //
        ByteMax = MaxMargin;
        if ((param == RdT) || (param == RdV)) {
          ByteMax = MrcCalcMaxRxMargin (MrcData, param, Channel, Rank, Byte, sign, MaxMargin);
        } else if (param == WrV) {
          ByteMax = MrcCalcMaxVrefMargin (MrcData, Channel, RankMask, Byte, param, sign, MaxMargin, FALSE);
        }

        CMargin[Channel][Byte][0] = ABMargin[Channel][Byte] - 2; //start from a definite pass for all bytes/bits

        if ((param == RdTBit) || (param == WrTBit)) {
          // Special case for PerBit Timing
          v0 = realSign * (CMargin[Channel][Byte][0] + 0); // Push into failing region
          Status = ChangeMargin (MrcData, pbyte, v0, 0, 0, Channel, Rank, Byte, 0, 0, 0, MrcRegFileStart);
        } else if (param == RdVBit) {
          // Special case for PerBit Voltage
          v0 = realSign * (CMargin[Channel][Byte][0] + 4); // Push into failing region
          Status = ChangeMargin (MrcData, pbyte, v0, 0, 0, Channel, Rank, Byte, 0, 0, 0, MrcRegFileStart);
        }
        //
        // Update the variables for PerBit tracking
        //
        if (PerBit) {
          for (bit = 0; bit < MAX_BITS; bit++) {
            CMargin[Channel][Byte][bit] = marginbit[Channel][Byte][bit][sign];
            //
            // Double check saturation limits
            //
            if (CMargin[Channel][Byte][bit] > MaxMargin) {
              CMargin[Channel][Byte][bit] = MaxMargin;
            }
          }
        }
        //
        // Find MinMargin to start and set marginbyte for the PerCh case
        //
        if (PerCh) {
          if (CMargin[Channel][Byte][0] < MinMargin) {
            MinMargin = (UINT8) CMargin[Channel][Byte][0];
          }

          CMargin[Channel][Byte][0] = MinMargin;
        }

        for (bit = 0; bit < MAX_BITS; bit++) {
          MinTested[Channel][Byte][bit]       = CMargin[Channel][Byte][bit * PerBit];
          marginbit[Channel][Byte][bit][sign] = CMargin[Channel][Byte][bit * PerBit];
        }
      }
    } // END OF CHANNEL LOOP

    //##########################################################
    // Search algorithm:
    // Walk up until everybody fails.  Then Walk down until everybody passes.
    //##########################################################
    while (MrcAndBytes (MrcData, chBitMask, OnePass, OneFail) != DoneMask) {
      //
      // Walk through all 2D points
      ReutGlobalCtl.Data = 0;
      ReutGlobalCtl.Bits.Global_Clear_Errors = 1;
      MrcWriteCR8 (MrcData, MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG, (UINT8) ReutGlobalCtl.Data); // Clear errors
      for (value1 = 0; value1 < Points2D; value1++) {
        //
        // Set Margin level
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!(chBitMask & (MRC_BIT0 << Channel))) {
            continue;
          }

          SkipWait = (chBitMask >> (Channel + 1)); // Skip if there are more channels
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (PerBit) {
              value0 = 0;
              for (bit = 0; bit < MAX_BITS; bit++) {
                //
                // Per Bit Deskew.  Note: When (sign==1), then CMargin is off by 1.
                // Suppose RdTBit and Right/Left Edge Last Pass @ CMargin = 12, 9
                //    Real Right Edge = (15-12)=3,  Right Edge Moved By (8-3)=5
                //    Real Left Edge = 9,           Left Edge Moved By (9-8) =1
                // Center Movement = (5-1)/2 = +2
                // To get correct answer, need to add +1 to CMargin for Right Edge
                //   ie: Center Moverment = (12+1-9)/2 = +2
                // This error will be corrected at the edge of the function
                // For RdTBit we shift data not strobe.Since we shift the opposite signal, sign is inverted
                //
                if ((param == RdTBit && sign) || ((param != RdTBit) && (sign == 0))) {
                  v0 = (MaxMargin - CMargin[Channel][Byte][bit]);
                } else {
                  v0 = CMargin[Channel][Byte][bit];
                }

                if (v0 > MaxMargin) {
                  v0 = MaxMargin;
                }
                value0 |= (v0 << (4 * bit));
              }
            } else {
              value0 = realSign * CMargin[Channel][Byte][0];
            }
            //
            // EnMultiCast=0, ch,rank,byte,0, UpdateHost=0, SkipWait
            //
            Status = ChangeMargin (
                       MrcData,
                       param,
                       value0,
                       value1,
                       0,
                       Channel,
                       (Ddr4 && (param == WrV)) ? RankMask : (Rank),
                       Byte,
                       0,
                       0,
                       SkipWait,
                       MrcRegFileStart
                       );
            if (PerCh && ((mode & 1) == 0)) {
              break;
            }
          }
        }
        //
        // Run Test
        //
        RunIOTest (MrcData, chBitMask, Outputs->DQPat, SeqLC, (value1 == 0), 0);

        //
        // Check if we have already failed and can stop running
        //
        if (value1 < (UINT32) (Points2D - 1)) {
          AllFail = 1;
          NoECC   = (Outputs->EccSupport == FALSE);
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!(chBitMask & (MRC_BIT0 << Channel))) {
              continue;
            }
            Offset = MCHBAR_CH0_CR_REUT_CH_ERR_DATA_STATUS_REG +
              (Channel * (MCHBAR_CH1_CR_REUT_CH_ERR_DATA_STATUS_REG - MCHBAR_CH0_CR_REUT_CH_ERR_DATA_STATUS_REG));
            AllFail &= (MrcReadCR (MrcData, Offset) == 0xFFFFFFFF);
            AllFail &= (MrcReadCR (MrcData, Offset + 4) == 0xFFFFFFFF);
            Offset = MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG +
            (
              Channel *
              (
                MCHBAR_CH1_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG -
                MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG
                )
              );
            AllFail &= (NoECC || ((UINT8) MrcReadCR (MrcData, Offset) == 0xFF));
          }

          if (AllFail) {
            break;  // break if any error
          }
        }
      }
      //
      // Collect results and Update variables for next point to test
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(chBitMask & (MRC_BIT0 << Channel))) {
          continue;
        }

        // Read Error Results (Assume all reads are 32 bit access
        Offset = MCHBAR_CH0_CR_REUT_CH_ERR_DATA_STATUS_REG +
          (Channel * (MCHBAR_CH1_CR_REUT_CH_ERR_DATA_STATUS_REG - MCHBAR_CH0_CR_REUT_CH_ERR_DATA_STATUS_REG));
        ErrLower = MrcReadCR (MrcData, Offset); // Lower 32 bits
        ErrUpper = MrcReadCR (MrcData, Offset + 4); // Upper 32 bits
        Offset = MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG +
        (
          Channel *
          (
            MCHBAR_CH1_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG -
            MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG
            )
          );
        ErrECC = (UINT8) MrcReadCR (MrcData, Offset);

        chPass = 0xFF;
        chFail = 0xFF;

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          //
          // Extract Errors
          //
          if (Byte < 4) {
            ErrByte = (UINT8) (ErrLower >> (8 * Byte));
          } else if (Byte < 8) {
            ErrByte = (UINT8) (ErrUpper >> (8 * (Byte - 4)));
          } else {
            ErrByte = ErrECC;
          }

          ErrByte &= DoneMask;
#ifdef MRC_DEBUG_PRINT
          if (param == WrTBit) {
            Offset = DDRDATA0CH0_CR_TXPERBITRANK0_REG +
              ((DDRDATA0CH1_CR_TXPERBITRANK0_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG) * Channel) +
              ((DDRDATA0CH0_CR_TXPERBITRANK1_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG) * Rank) +
              ((DDRDATA1CH0_CR_TXPERBITRANK0_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG) * Byte);
            MRC_DEBUG_MSG (Debug, DebugLevel, "0x%08X", MrcReadCR (MrcData, Offset));
          } else if (param == RdTBit) {
            Offset = DDRDATA0CH0_CR_RXPERBITRANK0_REG +
              ((DDRDATA0CH1_CR_RXPERBITRANK0_REG - DDRDATA0CH0_CR_RXPERBITRANK0_REG) * Channel) +
              ((DDRDATA0CH0_CR_RXPERBITRANK1_REG - DDRDATA0CH0_CR_RXPERBITRANK0_REG) * Rank) +
              ((DDRDATA1CH0_CR_RXPERBITRANK0_REG - DDRDATA0CH0_CR_RXPERBITRANK0_REG) * Byte);
            MRC_DEBUG_MSG (Debug, DebugLevel, "0x%08X", MrcReadCR (MrcData, Offset));
          } else if (param == RdVBit) {
            Offset = DDRDATA0CH0_CR_RXOFFSETVDQRANK0_REG +
              ((DDRDATA0CH1_CR_RXOFFSETVDQRANK0_REG - DDRDATA0CH0_CR_RXOFFSETVDQRANK0_REG) * Channel) +
              ((DDRDATA0CH0_CR_RXOFFSETVDQRANK1_REG - DDRDATA0CH0_CR_RXOFFSETVDQRANK0_REG) * Rank) +
              ((DDRDATA1CH0_CR_RXOFFSETVDQRANK0_REG - DDRDATA0CH0_CR_RXOFFSETVDQRANK0_REG) * Byte);
            MRC_DEBUG_MSG (Debug, DebugLevel, "0x%08X", MrcReadCR (MrcData, Offset));
          } else if (param == WrT || param == RdT || param == RdV || param == WrV) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "% 2d", CMargin[Channel][Byte][0]);
          }
#endif // MRC_DEBUG_PRINT

          for (bit = 0; bit < MAX_BITS; bit++) {
            BitMask       = MRC_BIT0 << bit;
            BitTimePerBit = bit * PerBit;
            //
            // Skip if this Bit Group is done
            //
            if (OnePass[Channel][Byte] & OneFail[Channel][Byte] & (BitMask)) {
              MRC_DEBUG_MSG (Debug, DebugLevel, "   $");
              continue;
            }
            //
            // Update variables for fail
            //
            if (ErrByte & (BitMask)) {
              OneFail[Channel][Byte] |= (BitMask);

              MRC_DEBUG_MSG (Debug, DebugLevel, "   #");

              //
              // Handle Speckles
              //
              if (marginbit[Channel][Byte][bit][sign] >= CMargin[Channel][Byte][BitTimePerBit]) {
                marginbit[Channel][Byte][bit][sign] = CMargin[Channel][Byte][BitTimePerBit] - 1;
                OnePass[Channel][Byte] &= ~(BitMask);
              }
              //
              // Update variables for pass
              //
            } else {
              OnePass[Channel][Byte] |= (BitMask);

              MRC_DEBUG_MSG (Debug, DebugLevel, "   .");

              if (marginbit[Channel][Byte][bit][sign] < CMargin[Channel][Byte][BitTimePerBit]) {
                marginbit[Channel][Byte][bit][sign] = CMargin[Channel][Byte][BitTimePerBit];
              }
            }
          }
          //
          // FIND MAX Saturation limit
          //
          ByteMax = MaxMargin;
          if ((param == RdT) || (param == RdV)) {
            ByteMax = MrcCalcMaxRxMargin (MrcData, param, Channel, Rank, Byte, sign, MaxMargin);
          } else if (param == WrV) {
            ByteMax = MrcCalcMaxVrefMargin (MrcData, Channel, RankMask, Byte, param, sign, MaxMargin, FALSE);
          }
          //
          // HANDLE Saturation
          //
          if (PerBit) {
            for (bit = 0; bit < MAX_BITS; bit++) {
              BitMask = MRC_BIT0 << bit;
              if (CMargin[Channel][Byte][bit] >= ByteMax) {
                OneFail[Channel][Byte] |= (BitMask);
              }

              if (CMargin[Channel][Byte][bit] == 0) {
                OnePass[Channel][Byte] |= (BitMask);
              }
            }
          } else {
            if (CMargin[Channel][Byte][0] >= ByteMax) {
              OneFail[Channel][Byte] = DoneMask;
            }

            if (CMargin[Channel][Byte][0] == 0) {
              OnePass[Channel][Byte] = DoneMask;
            }
          }
          //
          // DECIDE WHAT TO TEST NEXT
          // If PerByte, Do this within the for byte loop
          //
          chPass &= OnePass[Channel][Byte];
          chFail &= OneFail[Channel][Byte];

          if (PerCh == FALSE) {
            if (PerBit) {
              for (bit = 0; bit < MAX_BITS; bit++) {
                BitMask = MRC_BIT0 << bit;
                //
                // Skip if this Bit Group is done
                //
                if (OnePass[Channel][Byte] & OneFail[Channel][Byte] & (BitMask)) {
                  continue;
                }

                if ((OneFail[Channel][Byte] & BitMask) == 0) {
                  CMargin[Channel][Byte][bit] += 1;
                } else if ((OnePass[Channel][Byte] & BitMask) == 0) {
                  MinTested[Channel][Byte][bit] -= 1;
                  CMargin[Channel][Byte][bit] = MinTested[Channel][Byte][bit];
                } else {
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING! Can't have both: OnePass and OneFail Not Done\n");
                }
              }
            } else {
              //
              // PerCh
              // Skip if this Byte Group is done
              //
              if ((OnePass[Channel][Byte] & OneFail[Channel][Byte]) == DoneMask) {
                MRC_DEBUG_MSG (Debug, DebugLevel, " ");
                continue;
              }

              if (OneFail[Channel][Byte] != DoneMask) {
                CMargin[Channel][Byte][0] += 1;
              } else if (OnePass[Channel][Byte] != DoneMask) {
                MinTested[Channel][Byte][0] -= 1;
                CMargin[Channel][Byte][0] = MinTested[Channel][Byte][0];
              }
            }
          }

          MRC_DEBUG_MSG (Debug, DebugLevel, " ");
        }
        //
        // END OF BYTE LOOP
        // DECIDE WHAT TO TEST NEXT
        // If PerCh, Do this within the for ch loop
        //
        if (PerCh == TRUE) {
          if ((chPass & chFail) == DoneMask) {
            continue;
          }

          if (chFail != DoneMask) {
            CMargin[Channel][0][0] += 1;
          } else {
            MinTested[Channel][0][0] -= 1;
            CMargin[Channel][0][0] = MinTested[Channel][0][0];
          }
          //
          // All bytes must use the same margin point
          //
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            CMargin[Channel][Byte][0] = CMargin[Channel][0][0];
          }
        }
      }
      //
      // END OF CHANNEL LOOP
      //
      MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
    }
    //
    // END OF WHILE LOOP
    // Update MarginByte to have the correct result
    //
    if (PerBit == 0) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (chBitMask & (MRC_BIT0 << Channel)) {

          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MinMargin = 0x7F; // Start with a huge unsigned number
            for (bit = 0; bit < MAX_BITS; bit++) {
              if (MinMargin > marginbit[Channel][Byte][bit][sign]) {
                MinMargin = (UINT8) marginbit[Channel][Byte][bit][sign];
              }
            }

            marginbyte[Channel][Byte][sign] = MinMargin * 10;
            //
            // MRC_DEBUG_MSG (Debug, DebugLevel,"+--marginbyte = MinMargin*10 = %d\n", MinMargin*10);
            //
          }
        }
      }
    } else {
      //
      // Bit Margins
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(chBitMask & (1 << Channel))) {
          continue;
        }

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          for (bit = 0; bit < MAX_BITS; bit++) {
            if ((param == RdTBit && sign) || ((param != RdTBit) && (sign == 0))) {
              marginbit[Channel][Byte][bit][sign] = MaxMargin - marginbit[Channel][Byte][bit][sign];
            }
          }
        }
      }
      //
      // Cleanup after test
      //
      Status = ChangeMargin (MrcData, pbyte, 0, 0, 1, 0, Rank, 0, 0, 0, 0, MrcRegFileCurrent);
    }
  }
  //
  // END OF SIGN LOOP
  // Clean up after step
  // @todo Restore perBit to last saved value
  //
  value0 = (PerBit == 1 ? 0x88888888 : 0);
  Status = ChangeMargin (MrcData, param, value0, 0, 1, 0, Rank, 0, 0, 0, 0, MrcRegFileCurrent);

  //
  // Correct for 1 tick error in Per Bit Deskew right edge
  //
  RdTAdjust = 1;
#ifdef MRC_DEBUG_PRINT
  if (PerBit == 1) {
    if (param == RdTBit) {
      RdTAdjust = -1;
    }

    MRC_DEBUG_MSG (Debug, DebugLevel, "\nGains     ");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (chBitMask & (MRC_BIT0 << Channel)) {

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          for (bit = 0; bit < MAX_BITS; bit++) {
            MRC_DEBUG_MSG (
              Debug,
              DebugLevel,
              " %d %d",
              ((RdTAdjust) * (8 - marginbit[Channel][Byte][bit][0])),
              ((RdTAdjust) * (marginbit[Channel][Byte][bit][1] - 8))
              );
          }

          MRC_DEBUG_MSG (Debug, DebugLevel, "           ");
        }
      }
    }
  } else {
    MRC_DEBUG_MSG (Debug, DebugLevel, "\nCt");

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((chBitMask & (MRC_BIT0 << Channel))) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          for (bit = 0; bit < MAX_BITS; bit++) {
            MRC_DEBUG_MSG (
              Debug,
              DebugLevel,
              "%4d",
              (INT8) (marginbit[Channel][Byte][bit][1] - marginbit[Channel][Byte][bit][0]) / 2
              );
          }

          MRC_DEBUG_MSG (Debug, DebugLevel, "   ");
        }
      }
    }
  }

  MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
#endif // MRC_DEBUG_PRINT

  return Status;
}

/**
  Assume REUT test has already been fully setup to run
  Finds the margin for all channels/all bytes
  The margin sweep is parameterized
  Uses ChangeMargin function to handle a variety of cases (Timing, Voltage, Fan, etc.)
  mode allows for different types of modes for margining:
    mode is {Bit0: PhLock (keep all bytes within in ch in phase),
             Bit1: Ch2Ch Data out of phase (LFSR seed), Bit 15:2: Reserved}
  marginByte is used as the starting point for the search (10x the actual margin)
  marginch returns the results (10x the actual margin)
  Interior: Search inside marginch limits, enabling multiple calls with different setups
  To reduce repeatibility noise, the returned margins is actually a BER extrapolation

  @param[in]     MrcData    - The global MrcData
  @param[in,out] marginByte - Data structure with the latest margin results
  @param[in]     chBitmask  - Bit mask of present channels
  @param[in]     Rank       - Rank to change margins for
  @param[in]     RankRx     - Ranks for Rx margin
  @param[in]     param      - parameter to get margins for
  @param[in]     mode       - allows for different types of modes for margining:
  @param[in]     BMap       - Byte mapping to configure error counter control register
  @param[in]     EnBER      - Enable BER extrapolation calculations
  @param[in]     MaxMargin  - Max Margin allowed for the parameter
  @param[in]     Interior   - Search inside marginch limits, enabling multiple calls with different setups
  @param[in,out] BERStats   - Bit Error Rate Statistics.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
MrcStatus
MrcGetBERMarginByte (
  IN     MrcParameters * const MrcData,
  IN OUT UINT32          marginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8           chBitmask,
  IN     UINT8           RankIn,
  IN     UINT8           RankRx,
  IN     UINT8           param,
  IN     UINT16          mode,
  IN     UINT8           *BMap,
  IN     UINT8           EnBER,
  IN     UINT8           MaxMargin,
  IN     UINT8           Interior,
  IN OUT UINT32          *BERStats
  )
{
  const MrcInput  *Inputs;
  MrcDebug        *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput        *Outputs;
  MrcControllerOut *ControllerOut;
  UINT32           *MarginByteTemp;
  MrcStatus        Status;
  UINT8            ResultType;
  UINT8            sign;
  INT8             rSign;
  UINT8            SeqLC[4];
  UINT8            Points2D;
  UINT8            Channel;
  UINT8            byte;
  UINT8            chByte;
  UINT8            SkipWait;
  UINT8            byteMax;
  UINT8            Margin;
  BOOLEAN          MinEyeFlag;
  UINT8            Byte;
  UINT8            Edge;
  UINT16           DoneMask;
  // Set to 1 after ch has 2 passing points
  UINT16           TwoPass[MAX_CHANNEL];
  // Set to 1 after ch has 2 failing points
  UINT16           TwoFail[MAX_CHANNEL];
  UINT16           res;
  UINT16           BitMask;
  INT8             Delta;
  BOOLEAN          Done;
  BOOLEAN          allFail;
  BOOLEAN          PerCh;
  UINT32           value0;
  UINT32           value1;
  UINT32           tmp;
  UINT32           ErrCount;
  UINT8            LastPassVref[MAX_CHANNEL][MAX_SDRAM_IN_DIMM]; // Last passing Vref
  UINT32           InitValue[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];    // Initial value from margin byte
  UINT8            MaxTested[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];    // Highest Vref Point Tested
  UINT8            MinTested[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];    // Lowest Vref Point Tested
  // Log8(Error count) at different Vref Points. 32 bit number that is broken in 4 bytes
  // [LastPass+2, LastPass+1, LastPass, LastPass-1]
  UINT32           Errors[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32           Offset;
  BOOLEAN          Ddr4;
  UINT8            Rank;
  UINT8            RankLoop;
  BOOLEAN          DimmVrefParam;
  MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_0_STRUCT                  ReutChErrCounterCtl;
  MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_STRUCT                         ReutGlobalCtl;
  MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_STRUCT               ReutChErrCounterStatus;


  Status        = mrcSuccess;
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  chByte        = 0;
  Points2D      = (param / RdFan2) + 1;
  ResultType    = GetMarginResultType (param);
  Ddr4       = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  //
  // Are we using DIMM Vref? (and not DDR4)
  //
  DimmVrefParam = (param == WrFan2 || param == WrFan3 || param == WrV );   // WrFan not defined
  PerCh = (param == WrFan2 || param == WrFan3 || (param == WrV) || ((mode & 1) == 1));   // WrFan not defined

  if (Ddr4 && (param == WrV)) {
    Rank = 0;
    //
    // We return results on first available rank and RankIn is RankMask.
    //
    for (RankLoop = 0; RankLoop < MAX_RANK_IN_CHANNEL; RankLoop++) {
      if ((1 << RankLoop) & RankIn & Outputs->ValidRankMask) {
        Rank = RankLoop;
        break;
      }
    }
  } else {
    Rank  = (RankIn == 0xFF) ? 0 : RankIn;
  }
  //  if (param == WrV)
  //  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+--->MrcGetBERMarginByte, Points2D: %d, PerCh: %d --\n", Points2D,PerCh);

  DoneMask = (MRC_BIT0 << Outputs->SdramCount) - 1; // 0x1FF or 0xFF

  if (Outputs->DQPat == SegmentWDB) {
    SeqLC[0] = Outputs->DQPatLC;
    SeqLC[1] = Outputs->DQPatLC;
    SeqLC[2] = Outputs->DQPatLC + 4;
    SeqLC[3] = Outputs->DQPatLC + 2;
  } else {
    SeqLC[0] = 1;
    SeqLC[1] = 1;
    SeqLC[2] = 1;
    SeqLC[3] = 1;
  }
  //
  // Run through margin test
  //
  for (sign = 0; sign < 2; sign++) {
    rSign = (INT8) ((2 * sign) - 1);
    //
    //    if (param == WrV)
    //    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+--MrcGetBERMarginByte, rsign = %d\n", rSign);
    //
    MrcCall->MrcSetMem ((UINT8 *) TwoPass, sizeof (TwoPass), 0);
    MrcCall->MrcSetMem ((UINT8 *) TwoFail, sizeof (TwoFail), 0);

    //
    // Initialize variables
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((MRC_BIT0 << Channel) & chBitmask)) {
        TwoPass[Channel] = DoneMask;
        TwoFail[Channel] = DoneMask;
        continue;
      }

      MinTested[Channel][0] = 0x7F;
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        LastPassVref[Channel][byte] = 0x7F; // Start with a huge unsigned number 127
        Errors[Channel][byte] = 0;

        //
        // Find MaxMargin for this byte
        //
        byteMax = MaxMargin;
        if ((param == RdT) || (param == RdV) || (param == RcvEnaX)) {
          byteMax = MrcCalcMaxRxMargin (MrcData, param, Channel, RankRx, byte, sign, MaxMargin);
        } else if ((param == CmdV) || DimmVrefParam) {
          byteMax = MrcCalcMaxVrefMargin (MrcData, Channel, RankRx, byte, param, sign, MaxMargin, FALSE);
          //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "\nChannel %u rank %u byte=%u sign=%d byteMax= %d\n",Channel, Rank, byte, sign, byteMax);
        }
        //
        // Scale MarginResult back to real margin numbers.  Set Max/MinTested
        //

        MarginByteTemp  = &marginByte[ResultType][Rank][Channel][byte][sign];
        *MarginByteTemp = *MarginByteTemp / 10;
        if (*MarginByteTemp > byteMax) {
          *MarginByteTemp = byteMax;
        }

        InitValue[Channel][byte] = *MarginByteTemp;

        //
        // if Per Ch, find MinMargin to start.  Else set margin for that Byte
        //
        if (PerCh == TRUE) {
          if (*MarginByteTemp < MinTested[Channel][0]) {
            MaxTested[Channel][0] = (UINT8) *MarginByteTemp;
            MinTested[Channel][0] = (UINT8) *MarginByteTemp;
          }
        } else {
          MaxTested[Channel][byte] = (UINT8) *MarginByteTemp;
          MinTested[Channel][byte] = (UINT8) *MarginByteTemp;
        }
        //
        // Setup REUT Error Counters to count errors per byte lane
        // Count Errors on a particular Byte Group BITS 8:7 = 10b
        //
        ReutChErrCounterCtl.Data = 0;
        ReutChErrCounterCtl.Bits.Counter_Pointer = BMap[byte];
        ReutChErrCounterCtl.Bits.Counter_Control = 2;
        Offset = MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_0_REG +
          ((MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_0_REG - MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_0_REG) * Channel) +
          ((MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_1_REG - MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_0_REG) * byte);
        MrcWriteCR (MrcData, Offset, ReutChErrCounterCtl.Data);
      }
      //
      // Set MarginResult for the PerCh case
      //
      if (PerCh == TRUE) {
        for (byte = 0; byte < Outputs->SdramCount; byte++) {
          marginByte[ResultType][Rank][Channel][byte][sign] = MinTested[Channel][0];
        }
      }
    }
    //
    // Search algorithm:
    // If start with a passing point, walk to hit 2 failing points
    //    Return as needed to hit a second passing point
    // If start with a failing point, walk to hit 2 passing points
    //    Return as needed to hit a second failing point
    // Keep testing until all ch/bytes find 2 passes and 2 fails
    //
    Done = FALSE;
    do {
      //
      // Walk through all 2D points
      //
      ReutGlobalCtl.Data = 0;
      ReutGlobalCtl.Bits.Global_Clear_Errors = 1;
      MrcWriteCR (MrcData, MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG, ReutGlobalCtl.Data); // Clear errors
      for (value1 = 0; value1 < Points2D; value1++) {
        //
        // Set Vref level
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!((MRC_BIT0 << Channel) & chBitmask)) {
            continue;
          }

          SkipWait = (chBitmask >> (Channel + 1)); // Skip if there are more channels
          for (byte = 0; byte < Outputs->SdramCount; byte++) {
            value0 = rSign * marginByte[ResultType][Rank][Channel][byte][sign];
            //
            //            if (param == WrV)
            //            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->Value0 is %d, Value1 is %d\n", (INT32)value0, value1);
            //

            Status = ChangeMargin (
                       MrcData,
                       param,
                       value0,
                       value1,
                       0,
                       Channel,
                       RankIn,
                       byte,
                       0,
                       0,
                       SkipWait,
                       MrcRegFileStart
                       );
            if ((PerCh) && ((mode & 1) == 0)) {
              //
              // Only Byte 7 on Channel 1 is needed to update Wr DIMM Vref - Taken care of inside ChangeMargin routine
              // for Ddr4 WrV is define per ch so we break after byte 0
              //
              break;
            }
          }
        }
        //
        // Run Test
        //
        RunIOTest (MrcData, chBitmask, Outputs->DQPat, SeqLC, (value1 == 0), 0);

        //
        // What is the idea behind this? What if all byte groups failed?
        //
        if (EnBER == 0 && value1 < (UINT32) (Points2D - 1)) {
          allFail = TRUE;
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!((MRC_BIT0 << Channel) & chBitmask)) {
              continue;
            }
            //
            // Read out per byte error results
            //
            Offset = 4 + MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG +
            ((MCHBAR_CH1_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG -
              MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG) * Channel);
            res = (UINT16) MrcReadCR (MrcData, Offset);
            if ((res & DoneMask) != DoneMask) {
              allFail = FALSE;
            }
          }

          if (allFail == TRUE) {
            break;
          }
        }
      }
      //
      // Collect results and Update variables for next point to test
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!((MRC_BIT0 << Channel) & chBitmask)) {
          continue;
        }

        for (byte = 0; byte < Outputs->SdramCount; byte++) {
          BitMask = MRC_BIT0 << byte;
          //
          // Skip if this Byte Group is done
          //
          if ((TwoPass[Channel] & TwoFail[Channel] & (BitMask)) != 0) {
            continue;
          }
          //
          // Handle PerCh vs. PerByte variable differences
          //
          chByte = (PerCh == TRUE ? 0 : byte);

          //
          // Read Error Count
          //
          Offset = MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG +
            ((MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG - MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG) * Channel) +
            ((MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_1_REG - MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG) * byte);
          ReutChErrCounterStatus.Data = MrcReadCR (MrcData, Offset);
          ErrCount = ReutChErrCounterStatus.Bits.Counter_Status;
          Margin = (UINT8) marginByte[ResultType][Rank][Channel][byte][sign];
          Delta = (Margin - LastPassVref[Channel][byte]);
          //          if (param == WrV) {
          //          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->channel: %d, Error count:%x.\n", Channel, ErrCount);
          //          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->Margin:%d, LastPassVref:%d, delta:%d. sign:%d\n", Margin, LastPassVref[Channel][byte], (INT8) Delta, sign);
          //          }

          // Update Pass/Fail Variables:
          //
          if (ErrCount == 0 && Margin == MaxTested[Channel][chByte]) {
            //
            // Passing while walking up
            //
            if (Delta < 0) {
              //
              // First passing point
              // @todo: Next line should be changed to return failure. Code should never hang.
              //
              MRC_ASSERT (
                MinTested[Channel][chByte] == MaxTested[Channel][chByte],
                Debug,
                "Error: MaxTested < LastPass after first point"
                );
              LastPassVref[Channel][byte] = Margin;
            } else if (Delta == 1) {
              //
              // Normal, walk to fail
              //
              Errors[Channel][byte]       = MrcBitShift (Errors[Channel][byte], -8 * Delta) & BER_ERROR_MASK;
              LastPassVref[Channel][byte] = Margin;
              TwoPass[Channel] |= (BitMask);
            } else if (Delta == 2) {
              //
              // Speckling in response, Consider point as error
              //
              Errors[Channel][byte] = MrcBitSwap (Errors[Channel][byte], MrcLog8 (ErrCount), 24, 8);
              TwoFail[Channel] |= (BitMask);
            } else {
              //
              // @todo: Next line should be changed to return failure. Code should never hang.
              //
              MRC_ASSERT (
                FALSE,
                Debug,
                "Error: Tested point twice or Tested >2 above LastPass (Passing while walking up)"
                );
            }
          } else if (ErrCount == 0 && Margin == MinTested[Channel][chByte]) {
            //
            // Skip if this byte is already done
            //
            if ((TwoPass[Channel] & (BitMask)) != 0) {
              continue;
            }

            if (Delta == -1) {
              //
              // Finding 2nd pass
              //
              Errors[Channel][byte] = MrcBitSwap (Errors[Channel][byte], 0, 0, 8);
              TwoPass[Channel] |= (BitMask);
            } else {
              //
              // 1st passing point
              // Don't shift Errors.  Fail points already assumed correct LastPass
              //
              LastPassVref[Channel][byte] = Margin;
              TwoPass[Channel] &= ~(BitMask);
            }
          } else if (ErrCount > 0 && Margin == MaxTested[Channel][chByte]) {
            //
            // Failing while walking up
            // @todo: Next line should be changed to return failure. Code should never hang.
            //
            MRC_ASSERT (Delta <= 2, Debug, "Error: Tested >2 above LastPass (Failing while walking up)");
            if (Delta < 2) {
              //
              // first failing point
              //
              Errors[Channel][byte] = MrcBitSwap (Errors[Channel][byte], MrcLog8 (ErrCount), 16, 8);
              TwoFail[Channel] &= ~(BitMask);
            } else if (Delta == 2) {
              //
              // 2nd failing point
              //
              Errors[Channel][byte] = MrcBitSwap (Errors[Channel][byte], MrcLog8 (ErrCount), 24, 8);
              TwoFail[Channel] |= (BitMask);
            }
          } else if (ErrCount > 0 && Margin == MinTested[Channel][chByte]) {
            //
            // Failing while walking down
            //
            if (LastPassVref[Channel][byte] < 0xFF && Delta <= 0) {
              //
              // Adjust LastPassVref and Error count to be below this failure point.
              //
              Errors[Channel][byte]       = MrcBitSwap (Errors[Channel][byte], MrcLog8 (ErrCount), 8 * (Delta + 1), 8);
              Errors[Channel][byte]       = MrcBitShift (Errors[Channel][byte], 8 * (1 - Delta));
              LastPassVref[Channel][byte] = Margin - 1;
            } else {
              tmp                   = ((Errors[Channel][byte] & 0xFF0000) << 8) + MrcLog8 (ErrCount);
              Errors[Channel][byte] = MrcBitSwap (Errors[Channel][byte], tmp, 16, 16);
              //              if (param == WrV)
              //              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"Unexpected case for channel: %d, delta: %d.\n", Channel, Delta);
            }

            if (MinTested[Channel][chByte] < MaxTested[Channel][chByte]) {
              TwoFail[Channel] |= (BitMask);
            }

            if (Delta <= 0) {
              TwoPass[Channel] &= ~(BitMask);
            }
          } else {
            //
            // @todo: Next line should be changed to return failure. Code should never hang.
            //
            MRC_ASSERT (FALSE, Debug, "Error: Testing points other than Max/MinTested");
          }
          //
          // FIND MAX Saturation limit
          //
          byteMax = MaxMargin;
          if ((param == RdT) || (param == RdV) || (param == RcvEnaX)) {
            byteMax = MrcCalcMaxRxMargin (MrcData, param, Channel, RankRx, byte, sign, MaxMargin);
          } else if ((param == CmdV) || DimmVrefParam) {
            byteMax = MrcCalcMaxVrefMargin (MrcData, Channel, RankRx, byte, param, sign, MaxMargin, FALSE);
          }

          if (Interior && InitValue[Channel][byte] == Margin) {
            byteMax = Margin;
          }
          //
          // HANDLE MAX Saturation
          //
          if (Margin == byteMax) {
            TwoFail[Channel] |= (BitMask);
          }

          if (ErrCount == 0 && byteMax == LastPassVref[Channel][byte] && (TwoPass[Channel] & (BitMask)) != 0) {
            Errors[Channel][byte] = MrcBitSwap (Errors[Channel][byte], 0xFFFE, 16, 16);
          }
          //
          // HANDLE MIN Saturation
          //
          if (Margin == 0) {
            TwoPass[Channel] |= (BitMask);
            if (ErrCount > 0) {
              TwoFail[Channel] |= (BitMask);
              LastPassVref[Channel][byte] = 0;
              Errors[Channel][byte] = MrcBitSwap (
                                        Errors[Channel][byte],
                                        (BER_LOG_TARGET << 8) + BER_LOG_TARGET,
                                        16,
                                        16
                                        );
            }
          }
          //
          // DECIDE WHAT TO TEST NEXT
          // If In PerByte, Do this within the for byte loop
          //
          if (PerCh == FALSE) {
            //
            // Skip if this Byte Group is done
            //
            if ((TwoPass[Channel] & TwoFail[Channel] & (BitMask)) != 0) {
              continue;
            }

            if (ErrCount == 0) {
              if ((TwoFail[Channel] & (BitMask)) == 0) {
                //
                // Count up to find 2 fails
                //
                marginByte[ResultType][Rank][Channel][byte][sign] = ++MaxTested[Channel][chByte];
              } else {
                //
                // Count down to find 2 passes
                //
                marginByte[ResultType][Rank][Channel][byte][sign] = --MinTested[Channel][chByte];
              }
            } else {
              if ((TwoPass[Channel] & (BitMask)) == 0) {
                marginByte[ResultType][Rank][Channel][byte][sign] = --MinTested[Channel][chByte];
              } else {
                marginByte[ResultType][Rank][Channel][byte][sign] = ++MaxTested[Channel][chByte];
              }
            }
          }
        }
        //
        // DECIDE WHAT TO TEST NEXT
        // If In PerCh, Do this within the for ch loop
        //
        if (PerCh == TRUE) {
          if ((TwoPass[Channel] & TwoFail[Channel]) == DoneMask) {
            continue;
          }

          if (TwoPass[Channel] != DoneMask) {
            marginByte[ResultType][Rank][Channel][0][sign] = --MinTested[Channel][chByte];
          } else {
            marginByte[ResultType][Rank][Channel][0][sign] = ++MaxTested[Channel][chByte];
          }
          //
          // All bytes must use the same margin point
          //
          for (byte = 0; byte < Outputs->SdramCount; byte++) {
            marginByte[ResultType][Rank][Channel][byte][sign] = marginByte[ResultType][Rank][Channel][0][sign];
          }
        }
      }
      //
      // check if we are done
      //
      Done = TRUE;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if ((TwoPass[Channel] & DoneMask) != DoneMask || (TwoFail[Channel] & DoneMask) != DoneMask) {
          Done = FALSE;
          break;
        }
      }
    } while (Done == FALSE);

    //
    // Calculate the effective margin
    // Update MarginResult with extroploated BER Margin
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
        continue;
      }

      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        //        if (param == WrV)
        //        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->marginByte[Ch %d, Byte%d, Sign %d] is: %d\n", Channel, byte, sign,  marginByte[ResultType][Rank][Channel][byte][sign]);
        if (EnBER) {
          marginByte[ResultType][Rank][Channel][byte][sign] = interpolateVref (
                                                                LastPassVref[Channel][byte],
                                                                (Errors[Channel][byte] >> 16) & 0xFF,
                                                                (Errors[Channel][byte] >> 24) & 0xFF,
                                                                BER_LOG_TARGET,
                                                                BERStats
                                                                );
          //          if (param == WrV)
          //          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->BERmarginByte[Ch %d, Byte%d, Sign %d] is: %d\n", Channel, byte, sign,  marginByte[ResultType][Rank][Channel][byte][sign]);
        } else {
          marginByte[ResultType][Rank][Channel][byte][sign] = 10 * LastPassVref[Channel][byte];
          //          if (param == WrV)
          //          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->marginByte[Ch %d, Byte%d, Sign %d] is: %d\n", Channel, byte, sign,  marginByte[ResultType][Rank][Channel][byte][sign]);
        }
      }
    }
  }
  //
  // Clean up after step
  //
  Status = ChangeMargin (MrcData, param, 0, 0, 1, 0, 0, 0, 0, 0, 0, MrcRegFileCurrent);
  if (Ddr4 && (param == WrV)) {
    // If eye < 4 dont program PDA and leave it
    // Calc min eye
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((0x1 << Channel) & chBitmask)) {
        continue;
      }
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MinEyeFlag = TRUE;
        for (Edge = 0; Edge < MAX_EDGES; Edge++) {
          // Rank here is result/first rank
          if (marginByte[ResultType][Rank][Channel][Byte][Edge] < 40) {
            MinEyeFlag = FALSE;
            break;
          }
        }
        if (MinEyeFlag) {
          // Program PDA only in case of healthy eye per Byte.
          Status = ChangeMargin (MrcData, param, 0, 0, 0, Channel, RankIn, 1 << Byte, 0, 0, 0, MrcRegFileCurrent);
        }
      }
    }
    // need to reference the margins to their real center per byte
    GetPdaMargins (MrcData, Outputs->MarginResult, param, RankIn & Outputs->ValidRankMask);
  }

  for (byte = 0; byte < Outputs->SdramCount; byte++) {
    Offset = MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_0_REG +
      ((MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_1_REG - MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_0_REG) * byte);
    MrcWriteCrMulticast (MrcData, Offset, 0);
  }

  return Status;

}

/**
  Assume REUT test has already been fully setup to run
  Finds the margin for all channels/all bytes
  The margin sweep is parameterized
  Uses ChangeMargin function to handle a variety of cases (Timing, Voltage, Fan, etc.)
  mode allows for different types of modes for margining:
  mode is {Bit0: PhLock (keep all bytes within in ch in phase),
  Bit1: Ch2Ch Data out of phase (LFSR seed), Bit 15:2: Reserved}
  marginCh is used as the starting point for the search (10x the actual margin)
  marginch returns the results (10x the actual margin)
  Interior: Search inside marginch limits, enabling multiple calls with different setups
  To reduce repeatibility noise, the returned margins is actually a BER extrapolation

  @param[in]     MrcData   - The global MrcData
  @param[in,out] marginCh  - Data structure with the latest margin results
  @param[in]     chBitmask - Bit mask of present channels
  @param[in]     RankRx    - Ranks for Rx margin and Tx Vref (Ddr4)
  @param[in]     RankIn    - Rank to change margins for
  @param[in]     param     - parameter to get margins for
  @param[in]     mode      - allows for different types of modes for margining:
  @param[in]     EnBER     - Enable BER extrapolation calculations
  @param[in]     MaxMargin - Max Margin allowed for the parameter
  @param[in]     Interior  - Search inside marginch limits, enabling multiple calls with different setups
  @param[in,out] BERStats  - Bit Error Rate Statistics.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
MrcStatus
MrcGetBERMarginCh (
  IN     MrcParameters   *MrcData,
  IN     UINT32          marginCh[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN OUT UINT8           chBitmask,
  IN     UINT8           RankRx,
  IN     UINT8           RankIn,
  IN     UINT8           param,
  IN     UINT16          mode,
  IN     UINT8           EnBER,
  IN     UINT8           MaxMargin,
  IN     UINT8           Interior,
  IN OUT UINT32          *BERStats
  )
{
  const MrcInput  *Inputs;
  MrcDebug        *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput       *Outputs;
  MrcStatus       Status;
  UINT8           ResultType;
  UINT8           sign;
  INT8            rSign;
  UINT8           SeqLC[4];
  UINT8           Points2D;
  UINT8           Channel;
  UINT8           byte;
  UINT8           SkipWait;
  UINT8           byteMax[MAX_CHANNEL];
  UINT8           Margin;
  // Set to 1 after ch has 2 passing points
  UINT16          TwoPass[MAX_CHANNEL];
  // Set to 1 after ch has 2 failing points
  UINT8           TwoFail[MAX_CHANNEL];
  INT8            Delta;
  BOOLEAN         Done;
  BOOLEAN         DimmVrefParam;
  UINT32          value0;
  UINT32          value1;
  UINT32          tmp;
  UINT8           chError;
  UINT32          ErrCount;
  UINT8           LastPassVref[MAX_CHANNEL];  // Last passing Vref
  UINT8           MaxTested[MAX_CHANNEL];     // Highest Vref Point Tested
  UINT8           MinTested[MAX_CHANNEL];     // Lowest Vref Point Tested
  // Log8(Error count) at different Vref Points. 32 bit number that is broken in 4 bytes
  // [LastPass+2, LastPass+1, LastPass, LastPass-1]
  UINT32          Errors[MAX_CHANNEL];
  UINT32          Offset;
  BOOLEAN         PerMc;
  UINT8           McChannel;
  UINT8           Rank;
  UINT8           RankLoop;
  BOOLEAN         Ddr4;
  UINT16          ByteMask;
  MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_STRUCT           ReutGlobalCtl;
  MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_STRUCT ReutChErrCounterStatus;

  Inputs     = &MrcData->Inputs;
  MrcCall    = Inputs->Call.Func;
  Outputs    = &MrcData->Outputs;
  Debug      = &Outputs->Debug;
  Status     = mrcSuccess;
  ResultType = GetMarginResultType (param);
  Points2D   = (param / 16) + 1;        // 2 for Fan2 and 3 for Fan3
  McChannel  = 0;
  Ddr4       = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  if (Ddr4 && (param == WrV)) {
    Rank = 0;
    //
    // We return results on first available rank and RankIn is RankMask.
    //
    for (RankLoop = 0; RankLoop < MAX_RANK_IN_CHANNEL; RankLoop++) {
      if ((1 << RankLoop) & RankIn & Outputs->ValidRankMask) {
        Rank = RankLoop;
        break;
      }
    }
  } else {
    Rank  = (RankIn >= MAX_RANK_IN_CHANNEL) ? 0 : RankIn;
  }

  if (Outputs->DQPat == SegmentWDB) {
    SeqLC[0] = Outputs->DQPatLC;
    SeqLC[1] = Outputs->DQPatLC;
    SeqLC[2] = Outputs->DQPatLC + 4;
    SeqLC[3] = Outputs->DQPatLC + 2;
  } else {
    SeqLC[0] = 1;
    SeqLC[1] = 1;
    SeqLC[2] = 1;
    SeqLC[3] = 1;
  }

  //
  // Make sure we cover all DIMM Vref cases
  //
  DimmVrefParam = (param == WrFan2 || param == WrFan3 || param == WrV );   // WrFan not defined
  PerMc         = (param == CmdV) && (MrcCountBitsEqOne (chBitmask) >= 2) && (!Ddr4);

  //
  // Run through margin test
  //
  for (sign = 0; sign < 2; sign++) {
    rSign = (INT8) ((2 * sign) - 1);
    //    if (DimmVrefParam)
    //    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->rsign: %d \n", rSign);

    MrcCall->MrcSetMem ((UINT8 *) TwoPass, sizeof (TwoPass), 0);
    MrcCall->MrcSetMem ((UINT8 *) TwoFail, sizeof (TwoFail), 0);

    //
    // Initialize variables
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      //
      // Set default of all variables
      //
      byteMax[Channel]      = MaxMargin;
      LastPassVref[Channel] = 0x7F;  // Start with a huge unsigned numer - 128
      Errors[Channel]       = 0;
      MinTested[Channel]    = 0;
      MaxTested[Channel]    = 0;

      if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
        TwoPass[Channel] = 1;
        TwoFail[Channel] = 1;
        continue;
      }
      //
      // Find MaxMargin for this channel
      //
      if (param == RdT || (param == RdV)) {
        for (byte = 0; byte < Outputs->SdramCount; byte++) {
          byteMax[Channel] = MrcCalcMaxRxMargin (MrcData, param, Channel, RankRx, byte, sign, byteMax[Channel]);
        }
      } else if ((param == CmdV) || DimmVrefParam) {
        byteMax[Channel] = MrcCalcMaxVrefMargin (MrcData, Channel, RankRx, 0, param, sign, byteMax[Channel], FALSE);

      }
      //
      // Scale back variables to normal margins and check saturation
      //
      marginCh[ResultType][Rank][Channel][0][sign] = marginCh[ResultType][Rank][Channel][0][sign] / 10;
      if (marginCh[ResultType][Rank][Channel][0][sign] > byteMax[Channel]) {
        marginCh[ResultType][Rank][Channel][0][sign] = byteMax[Channel];
      }
      //
      // If PerMC, all channels should start with the lowest margin across all the channel
      //
      if (PerMc) {
        if (marginCh[ResultType][Rank][McChannel][0][sign] > marginCh[ResultType][Rank][Channel][0][sign]) {
          marginCh[ResultType][Rank][McChannel][0][sign] = marginCh[ResultType][Rank][Channel][0][sign];
        }
      }

      MinTested[Channel]  = (UINT8) marginCh[ResultType][Rank][Channel][0][sign];
      MaxTested[Channel]  = MinTested[Channel];

      //
      // Setup REUT Error Counters to count errors per channel
      //
      Offset = MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_0_REG +
        ((MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_0_REG - MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_0_REG) * Channel);
      MrcWriteCR (MrcData, Offset, 0);
    }
    //
    // If PerMC, set all channels to use margin associated with mcChannel = 0
    //
    if (PerMc) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
          continue;
        }
        marginCh[ResultType][Rank][Channel][0][sign] = marginCh[ResultType][Rank][McChannel][0][sign];
        MinTested[Channel] = (UINT8) marginCh[ResultType][Rank][McChannel][0][sign];
        MaxTested[Channel] = MinTested[Channel];
      }
    }
    //
    // Search algorithm:
    // If start with a passing point, walk to hit 2 failing points
    //    Return as needed to hit a second passing point
    // If start with a failing point, walk to hit 2 passing points
    //    Return as needed to hit a second failing point
    // Keep testing until all ch/bytes find 2 passes and 2 fails
    //
    Done = FALSE;
    do {
      //
      // Walk through all 2D points
      //
      ReutGlobalCtl.Data = 0;
      ReutGlobalCtl.Bits.Global_Clear_Errors = 1;
      MrcWriteCR (MrcData, MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG, ReutGlobalCtl.Data);  // Clear errors
      chError = 0;

      for (value1 = 0; value1 < Points2D; value1++) {
        //
        // Set Vref level
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
            continue;
          }

          SkipWait = (chBitmask >> (Channel + 1)); // Skip if there are more channels
          value0 = rSign * marginCh[ResultType][Rank][Channel][0][sign];
          //          if (DimmVrefParam) {
          //            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "+----->Value0 is %d, Value1 is %d\n", (INT32) value0, value1);
          //            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "+----->marginCh is %d\n", marginCh[ResultType][Rank][Channel][0][sign]);
          //          }

          if (param == CmdV) {
            if (!Ddr4 || Channel == 0) {
              UpdateVrefWaitTilStable (MrcData, 2, 0, value0, 0, 0, FALSE, 0);
            }
            if (Ddr4 && Channel == 1) {
              // ch1 CA vref in DDR4
              UpdateVrefWaitTilStable (MrcData, 3, 0, value0, 0, 0, FALSE, 0);
            }
            MrcResetSequence (MrcData);
            //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "+----->Value0 is %d, Value1 is %d\n", (INT32) value0, value1);
            if (PerMc)  {
              break; // Just update ones
            }
          } else {
            for (byte = 0; byte < Outputs->SdramCount; byte++) {
              Status = ChangeMargin (
                         MrcData,
                         param,
                         value0,
                         value1,
                         0,
                         Channel,
                         RankIn,
                         byte,
                         0,
                         0,
                         SkipWait,
                         MrcRegFileStart
                         );
              if (DimmVrefParam) {
                //
                // Only Byte 7 on Channel 1 is needed to update Wr DIMM Vref - Taken care of inside ChangeMargin routine
                //
                break;
              }
            }
          }
        }
        //
        // Run Test
        //
        chError |= RunIOTest (MrcData, chBitmask, Outputs->DQPat, SeqLC, (value1 == 0), 0);

        //
        // check if we have already failed and can stop running
        //
        if (EnBER == 0 && value1 < (UINT32) (Points2D - 1) && chError == chBitmask) {
          break;
        }
        //
        // Collect results and Update variables for next point to test
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if ((TwoPass[Channel] == 1 && TwoFail[Channel] == 1) || ((MRC_BIT0 << Channel) & chBitmask) == 0) {
            continue;
          }

          McChannel = (PerMc) ? 0 : Channel;

          //
          // Read Error Count
          //
          Offset = MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG +
            ((MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG - MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG) * Channel);
          ReutChErrCounterStatus.Data = MrcReadCR (MrcData, Offset);
          ErrCount                    = ReutChErrCounterStatus.Bits.Counter_Status;
          Margin                      = (UINT8) marginCh[ResultType][Rank][Channel][0][sign];
          Delta                       = (Margin - LastPassVref[Channel]);

          //
          // Update Pass/Fail Variables:
          //
          if (ErrCount == 0 && Margin == MaxTested[McChannel]) {
            //
            // Passing while walking up
            //
            if (Delta < 0) {
              //
              // First passing point
              // @todo: Next line should be changed to return failure. Code should never hang.
              //
              MRC_ASSERT (
                MinTested[McChannel] == MaxTested[McChannel],
                Debug,
                "Error: MaxTested < LastPass after first point"
                );
              LastPassVref[Channel] = Margin;
            } else if (Delta == 1) {
              //
              // Normal, walk to fail
              //
              Errors[Channel]       = MrcBitShift (Errors[Channel], -8 * Delta) & BER_ERROR_MASK;
              LastPassVref[Channel] = Margin;
              TwoPass[Channel]      = 1;
            } else if (Delta == 2) {
              //
              // Speckling in response, Consider point as error
              //
              Errors[Channel]   = MrcBitSwap (Errors[Channel], MrcLog8 (ErrCount), 24, 8);
              TwoFail[Channel]  = 1;
            } else {
              //
              // @todo: Next line should be changed to return failure. Code should never hang.
              //
              MRC_ASSERT (FALSE, Debug, "Error: Tested point twice or Tested >2 above LastPass");
            }
          } else if (ErrCount == 0 && Margin == MinTested[McChannel]) {
            if (TwoPass[Channel] == 1) {
              continue; // Skip if this channel is already done
            }
            //
            // Passing while walking down
            //
            if (Delta == -1) {
              Errors[Channel]  = MrcBitSwap (Errors[Channel], 0, 0, 8);
              TwoPass[Channel] = 1;     // found second pass
            } else {
              //
              // 1st passing point
              // Don't shift errors.  Fail points already assumed correct
              //
              LastPassVref[Channel] = Margin;
              TwoPass[Channel]      = 0;
            }
          } else if (ErrCount > 0 && Margin == MaxTested[McChannel]) {
            //
            // Failing while walking up
            // @todo: Next line should be changed to return failure. Code should never hang.
            //
            MRC_ASSERT (Delta <= 2, Debug, "Error: Tested >2 above LastPass");
            if (Delta < 2) {
              //
              // first failing point
              //
              Errors[Channel]   = MrcBitSwap (Errors[Channel], MrcLog8 (ErrCount), 16, 8);
              TwoFail[Channel]  = 0;
            } else if (Delta == 2) {
              //
              // 2nd failing point
              //
              Errors[Channel]   = MrcBitSwap (Errors[Channel], MrcLog8 (ErrCount), 24, 8);
              TwoFail[Channel]  = 1;
            }
          } else if (ErrCount > 0 && Margin == MinTested[McChannel]) {
            //
            // Failing while walking down
            //
            if (LastPassVref[Channel] < 0xFF && Delta <= 0) {
              //
              // Adjust LastPassVref and Error count to be below this failure point
              //
              Errors[Channel]       = MrcBitSwap (Errors[Channel], MrcLog8 (ErrCount), 8 * (Delta + 1), 8);
              Errors[Channel]       = MrcBitShift (Errors[Channel], 8 * (1 - Delta));
              LastPassVref[Channel] = Margin - 1;
            } else {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Unexpected case for channel: %d, delta: %d.\n", Channel, Delta);
              tmp             = ((Errors[Channel] & 0xFF0000) >> 8) + MrcLog8 (ErrCount);
              Errors[Channel] = MrcBitSwap (Errors[Channel], tmp, 16, 16);
            }

            if (MinTested[McChannel] < MaxTested[McChannel]) {
              TwoFail[Channel] = 1;
            }

            if (Delta <= 0) {
              TwoPass[Channel] = 0;
            }
          } else {
            //
            // @todo: Next line should be changed to return failure. Code should never hang.
            //
            MRC_ASSERT (FALSE, Debug, "Error: Testing points other than Max/MinTested");
          }
          //
          // Find Max Saturation limit
          //
          if (Interior && MaxTested[Channel] == Margin) {
            byteMax[Channel] = Margin;
          }
          //
          // Handle Max Saturation
          //
          if (Margin == byteMax[Channel]) {
            TwoFail[Channel] = 1;
          }

          if (ErrCount == 0 && byteMax[Channel] == LastPassVref[Channel] && TwoPass[Channel] == 1) {
            Errors[Channel] = MrcBitSwap (Errors[Channel], 0xFFFE, 16, 16);
          }
          //
          // Handle Min Saturation
          //
          if (Margin == 0) {
            TwoPass[Channel] = 1;
            if (ErrCount > 0) {
              TwoFail[Channel]      = 1;
              LastPassVref[Channel] = 0;
              Errors[Channel]       = MrcBitSwap (Errors[Channel], (BER_LOG_TARGET << 8) + BER_LOG_TARGET, 16, 16);
            }
          }
          //
          // Decide what to test next for PerMC == FALSE
          //
          if (!PerMc) {
            if (TwoPass[Channel] == 1) {
              if (TwoFail[Channel] == 1) {
                continue;
              }
              //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"++---->MaxTested[Ch] before ++:%d\n", MaxTested[Channel]);////////
              marginCh[ResultType][Rank][Channel][0][sign] = ++MaxTested[Channel];
            } else {
              //            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"++---->MinTested[Ch] before --:%d\n", MinTested[Channel]);////////
              marginCh[ResultType][Rank][Channel][0][sign] = --MinTested[Channel];
            }
          }
        }
        //
        // Decide what to test next for PerMC == TRUE
        //
        if (PerMc) {
          if ((TwoPass[0] == 1) && (TwoPass[1] == 1)) {
            //
            // All Channels have 2 passes
            //
            if ((TwoFail[0] == 1) && (TwoFail[1] == 1)) {
              //
              // All Channels have 2 fails
              //
              continue;
            }
            //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"++---->MaxTested[Ch] before ++:%d\n", MaxTested[Channel]);////////
            marginCh[ResultType][Rank][McChannel][0][sign] = ++MaxTested[McChannel];
          } else {
            //            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"++---->MinTested[Ch] before --:%d\n", MinTested[Channel]);////////
            marginCh[ResultType][Rank][McChannel][0][sign] = --MinTested[McChannel];
          }

          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
              continue;
            }

            marginCh[ResultType][Rank][Channel][0][sign] = marginCh[ResultType][Rank][McChannel][0][sign];
            MinTested[Channel] = MinTested[McChannel];
            MaxTested[Channel] = MaxTested[McChannel];
          }
        }
      }
      //
      // check if we are done
      //
      Done = TRUE;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (TwoPass[Channel] == 0 || TwoFail[Channel] == 0) {
          Done = FALSE;
          break;
        }
      }
    } while (Done == FALSE);

    //
    // Calculate the effective margin
    // Update marginch with extroploated BER Margin
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
        continue;
      }
      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->marginCh[%d,%d] is: %d\n", Channel, sign,  marginCh[ResultType][Rank][Channel][0][sign]);
      if (EnBER) {
        marginCh[ResultType][Rank][Channel][0][sign] = interpolateVref (
                                                         LastPassVref[Channel],
                                                         (Errors[Channel] >> 16) & 0xFF,
                                                         (Errors[Channel] >> 24) & 0xFF,
                                                         BER_LOG_TARGET,
                                                         BERStats
                                                         );
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "+----->BERmarginCh[%d,%d] is: %d, Errors = 0x%x\n", Channel, sign,  marginCh[ResultType][Rank][Channel][0][sign], Errors[Channel]);
      } else {
        marginCh[ResultType][Rank][Channel][0][sign] = 10 * LastPassVref[Channel];
        //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "+----->marginCh[%d,%d] is: %d\n", Channel, sign,  marginCh[ResultType][Rank][Channel][0][sign]);
      }
    }
  }
  //
  // Clean up after step
  //
  if (param == CmdV) {
    UpdateVrefWaitTilStable (MrcData, 2, 0, 0, 0, 0, FALSE, 0);
    if (Ddr4) {
      UpdateVrefWaitTilStable (MrcData, 3, 0, 0, 0, 0, FALSE, 0);
    }
  } else {
    ByteMask = ((param == WrV) && Ddr4 ) ? 0x1FF : 0;
    Status = ChangeMargin (MrcData, param, 0, 0, 1, 0, 0, ByteMask, 0, 0, 0, MrcRegFileCurrent);
  }

  MrcWriteCrMulticast (MrcData, MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_0_REG, 0);

  return Status;
}

/**
  This function shifts a 32 bit int either positive or negative

  @param[in] Value       - Input value to be shifted
  @param[in] ShiftAmount - Number of bits places to be shifted.

  @retval 0 if ShiftAmount exceeds +/- 31.  Otherwise the updated 32 bit value.
**/
UINT32
MrcBitShift (
  IN const UINT32 Value,
  IN const INT8  ShiftAmount
  )
{
  if ((ShiftAmount > 31) || (ShiftAmount < -31)) {
    return 0;
  }

  if (ShiftAmount > 0) {
    return Value << ShiftAmount;
  } else {
    return Value >> (-1 * ShiftAmount);
  }
}

/**
  This function Sign extends OldMSB to NewMSB Bits (Eg: Bit 6 to Bit 7)

  @param[in] CurrentValue - Input value to be shifted
  @param[in] OldMSB       - The original most significant Bit
  @param[in] NewMSB       - The new most significant bit.

  @retval The updated 8 bit value.
**/
UINT8
MrcSE (
  IN UINT8     CurrentValue,
  IN const UINT8 OldMSB,
  IN const UINT8 NewMSB
  )
{
  UINT8 Scratch;

  Scratch = ((MRC_BIT0 << (NewMSB - OldMSB)) - 1) << OldMSB;
  if (CurrentValue >> (OldMSB - 1)) {
    CurrentValue |= Scratch;
  } else {
    CurrentValue &= (~Scratch);
  }

  return CurrentValue;
}

/**
  This function calculates the Log base 2 of the value to a maximum of Bits

  @param[in] Value - Input value

  @retval Returns the log base 2 of input value
**/
UINT8
MrcLog2 (
  IN const UINT32 Value
  )
{
  UINT8 Log;
  UINT8 Bit;

  //
  // Return 0 if value is negative
  //
  Log = 0;
  if ((Value + 1) != 0) {
    for (Bit = 0; Bit < 32; Bit++) {
      if (Value & (MRC_BIT0 << Bit)) {
        Log = (Bit + 1);
      }
    }
  }

  return Log;
}

/**
  This function calculates the power of integer numbers.

  @param[in] Value - Input value.
  @param[in] Power - the power to raise the Value to

  @retval Returns (Value ^ Power) * 100
**/
UINT32
MrcPercentPower (
  IN const UINT32 Value,
  IN UINT32    Power
  )
{
  UINT32  Result;

  Result = 100;
  while (Power--) {
    Result *= Value;
    if (Result != Value) { // normalize to percent
      Result /= 100;
    }
  }

  return Result;
}

/**
  This function search for item in a list and return index + 1 or 0 in not found

  @param[in] Param - Param to search for
  @param[in] ParamList - list of Params
  @param[in] ParamLen - Params length
  @retval Returns result
**/
UINT8
MrcSearchList (
  IN UINT8 Param,
  IN const UINT8 *ParamList,
  IN const UINT8 ParamLen
  )
{
  UINT8 Result = 0;
  UINT8 Idx;

  for (Idx = 0; Idx < ParamLen; Idx ++) {
    if (ParamList[Idx] == Param) {
      Result = Idx + 1;
      break;
    }
  }
  return Result;
}

/**
  ***** Has Buffer Overflow for 68-71, 544-575, 4352-4607, ... ****
  This function calculates the Log base 8 of the Input parameter using integers

  @param[in] Value - Input value

  @retval Returns 10x the log base 8 of input Value
**/
UINT32
MrcLog8 (
  IN UINT32 Value
  )
{
  static const UINT8 Loglook[18] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 8, 8, 9, 9, 9, 10, 10, 10 };
  UINT32    Loga;
  UINT32    Rema;

  Loga  = 0;
  Rema  = 2 * Value;
  while (Value > 8) {
    Rema  = Value >> 2;
    Value = Value >> 3;
    Loga += 10;
  };

  return (Loga + Loglook[Rema]); //returns an integer approximation of "log8(a) * 10"
}

/**
  This function Sorts Arr from largest to smallest

  @param[in,out] Arr     - Array to be sorted
  @param[in]     Channel - Channel to sort.
  @param[in]     lenArr  - Length of the array

  @retval Nothing
**/
void
MrcBsortPerChannel (
  IN OUT UINT32   Arr[MAX_CHANNEL][4],
  IN     const UINT8 Channel,
  IN     const UINT8 lenArr
  )
{
  UINT8 i;
  UINT8 j;
  UINT32 temp;

  for (i = 0; i < lenArr - 1; i++) {
    for (j = 0; j < lenArr - (1 + i); j++) {
      if (Arr[Channel][j] < Arr[Channel][j + 1]) {
        temp                = Arr[Channel][j];
        Arr[Channel][j]     = Arr[Channel][j + 1];
        Arr[Channel][j + 1] = temp;
      }
    }
  }

  return;
}

/**
  This function Sorts Arr from largest to smallest

  @param[in,out] Arr    - Array to be sort
  @param[in]     lenArr - Lenght of the array

  @retval Nothing
**/
void
MrcBsort (
  IN OUT UINT32 *const Arr,
  IN     const UINT8 lenArr
  )
{
  UINT8 i;
  UINT8 j;
  UINT32 temp;

  for (i = 0; i < lenArr - 1; i++) {
    for (j = 0; j < lenArr - (1 + i); j++) {
      if (Arr[j] < Arr[j + 1]) {
        temp        = Arr[j];
        Arr[j]      = Arr[j + 1];
        Arr[j + 1]  = temp;
      }
    }
  }

  return;
}

/**
  This function calculates the Natural Log of the Input parameter using integers

  @param[in] Input - 100 times a number to get the Natural log from.
                      Max Input Number is 40,000 (without 100x)

  @retval 100 times the actual result. Accurate within +/- 2
**/
UINT32
MrcNaturalLog (
  UINT32 Input
  )
{
  UINT32 Output;

  Output = 0;
  while (Input > 271) {
    Input = (Input * 1000) / 2718;
    Output += 100;
  }

  Output += ((-16 * Input * Input + 11578 * Input - 978860) / 10000);

  return Output;
}

/**
  This function calculates the number of bits set to 1 in a 32-bit value.

  @param[in] Input - The value to work on.

  @retval The number of bits set to 1 in Input.
**/
UINT8
MrcCountBitsEqOne (
  IN UINT32 Input
  )
{
  UINT8 NumOnes;

  NumOnes = 0;
  while (Input > 0) {
    NumOnes++;
    Input &= (Input - 1);
  }

  return NumOnes;
}

/**
  This function calculates e to the power of the Input parameter using integers.

  @param[in] Input - 100 times a number to elevate e to.

  @retval 100 times the actual result. Accurate within +/- 2.
**/
UINT32
Mrceexp (
  IN UINT32 Input
  )
{
  UINT32 Extra100;
  UINT32 Output;

  Extra100  = 0;
  Output    = 1;
  while (Input > 100) {
    Input -= 100;
    Output = (Output * 2718) / 10;
    if (Extra100) {
      Output /= 100;
    }

    Extra100 = 1;
  }

  Output = ((Output * (8 * Input * Input + 900 * Input + 101000)) / 1000);

  if (Extra100) {
    Output /= 100;
  }

  return Output;
}

/**
  This function writes a 32 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - Value to write.

  @retval The register value.
**/
UINT32
MrcWriteCrMulticast (
  IN MrcParameters *const MrcData,
  IN const UINT32         Offset,
  IN const UINT32         Value
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput     *Inputs;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcData->Outputs.MchBarWriteCount++;
  MrcCall->MrcMmioWrite32 (Inputs->MchBarBaseAddress + Offset, Value);
#ifdef MRC_DEBUG_PRINT
  if (MrcData->Outputs.Debug.PostCode[MRC_POST_CODE_WRITE] == MrcData->Outputs.Debug.PostCode[MRC_POST_CODE]) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "<mc>%04X M %08X</mc>\n",
      Offset,
      Value
      );
  }
#endif // MRC_DEBUG_PRINT
  return (Value);
}

/**
  This function writes a 64 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - Value to write.

  @retval The register value.
**/
UINT64
MrcWriteCR64 (
  IN MrcParameters *const MrcData,
  IN const UINT32         Offset,
  IN const UINT64         Value
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput     *Inputs;
  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcData->Outputs.MchBarWriteCount++;
  MrcCall->MrcMmioWrite64 (Inputs->MchBarBaseAddress + Offset, Value);
#ifdef MRC_DEBUG_PRINT
  if (MrcData->Outputs.Debug.PostCode[MRC_POST_CODE_WRITE] == MrcData->Outputs.Debug.PostCode[MRC_POST_CODE]) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "<mc>%04X W %l_X</mc>\n",
      Offset,
      Value
      );
  }
#endif // MRC_DEBUG_PRINT
  return (Value);
}

/**
  This function writes a 32 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - Value to write.

  @retval The register value.
**/
UINT32
MrcWriteCR (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const UINT32  Value
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput     *Inputs;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcData->Outputs.MchBarWriteCount++;
  MrcCall->MrcMmioWrite32 (Inputs->MchBarBaseAddress + Offset, Value);
#ifdef MRC_DEBUG_PRINT
  if (MrcData->Outputs.Debug.PostCode[MRC_POST_CODE_WRITE] == MrcData->Outputs.Debug.PostCode[MRC_POST_CODE]) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "<mc>%04X W %08X</mc>\n",
      Offset,
      Value
      );
  }
#endif // MRC_DEBUG_PRINT
  return (Value);
}

/**
  This function writes a 8 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - The value to write.

  @retval The register value.
**/
UINT8
MrcWriteCR8 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const UINT8   Value
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput     *Inputs;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcData->Outputs.MchBarWriteCount++;
  MrcCall->MrcMmioWrite8 (MrcData->Inputs.MchBarBaseAddress + Offset, Value);
#ifdef MRC_DEBUG_PRINT
  if (MrcData->Outputs.Debug.PostCode[MRC_POST_CODE_WRITE] == MrcData->Outputs.Debug.PostCode[MRC_POST_CODE]) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "<mc>%04X W %02X</mc>\n",
      Offset,
      Value
      );
  }
#endif // MRC_DEBUG_PRINT
  return (Value);
}

/**
  This function reads a 64 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.

  @retval Value read from the register.
**/
UINT64
MrcReadCR64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput     *Inputs;
  UINT64             Value;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcData->Outputs.MchBarReadCount++;
  Value = (MrcCall->MrcMmioRead64 (Inputs->MchBarBaseAddress + Offset));
#ifdef MRC_DEBUG_PRINT
  if (MrcData->Outputs.Debug.PostCode[MRC_POST_CODE_READ] == MrcData->Outputs.Debug.PostCode[MRC_POST_CODE]) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "<mc>%04X R %l_X</mc>\n",
      Offset,
      Value
      );
  }
#endif // MRC_DEBUG_PRINT
  return (Value);
}

/**
  This function reads a 32 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.

  @retval Value read from the register
**/
UINT32
MrcReadCR (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput     *Inputs;
  UINT32             Value;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcData->Outputs.MchBarReadCount++;
  Value = MrcCall->MrcMmioRead32 (Inputs->MchBarBaseAddress + Offset);
#ifdef MRC_DEBUG_PRINT
  if (MrcData->Outputs.Debug.PostCode[MRC_POST_CODE_READ] == MrcData->Outputs.Debug.PostCode[MRC_POST_CODE]) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "<mc>%04X R %08X</mc>\n",
      Offset,
      Value
      );
  }
#endif // MRC_DEBUG_PRINT
  return (Value);
}

/**
  This function blocks the CPU for the duration specified in HPET Delay time.

  @param[in] MrcData   - Include all MRC global data.
  @param[in] DelayHPET - time to wait in 41.666667ns

  @retval Nothing
**/
void
MrcWait (
  IN MrcParameters *const MrcData,
  IN UINT32               DelayHPET
  )
{
  const MrcInput     *Inputs;
  const MRC_FUNCTION *MrcCall;
  BOOLEAN            Done;
  UINT32             Offset;
  UINT32             Start;
  volatile UINT32    Finish;
  UINT32             Now;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Done    = FALSE;


  if (DelayHPET >= (5 * HPET_1US)) {
    Offset = Inputs->HpetBaseAddress + 0xF0;
    Start = MrcCall->MrcMmioRead32 (Offset);
    Finish = Start + DelayHPET;

    do {
      Now = MrcCall->MrcMmioRead32 (Offset);
      if (Finish > Start) {
        if (Now >= Finish) {
          Done = TRUE;
        }
      } else {
        if ((Now < Start) && (Now >= Finish)) {
          Done = TRUE;
        }
      }
    } while (Done == FALSE);
  } else {
    for (Start = 0; Start < ((DelayHPET + HPET_MIN) / (2 * HPET_MIN)); Start++) {
      //
      // Just perform Dummy reads to CPU CR
      //
      Finish = MrcReadCR (MrcData, MCHBAR_CH0_CR_REUT_CH_ERR_DATA_STATUS_REG);
    }
  }
  return;

}

/**
  This function forces an RCOMP.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
MrcStatus
ForceRcomp (
  IN MrcParameters *const MrcData
  )
{

  const MRC_FUNCTION        *MrcCall;
  PCU_CR_M_COMP_PCU_STRUCT  PcuCrMComp;
  UINT64                    Timeout;
  BOOLEAN                   Flag;

  MrcCall         = MrcData->Inputs.Call.Func;
  PcuCrMComp.Data = MrcReadCR (MrcData, PCU_CR_M_COMP_PCU_REG);
  PcuCrMComp.Bits.COMP_FORCE = 1;
  MrcWriteCR (MrcData, PCU_CR_M_COMP_PCU_REG, PcuCrMComp.Data);
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000; // 10 seconds timeout
  do {
    PcuCrMComp.Data = MrcReadCR (MrcData, PCU_CR_M_COMP_PCU_REG);
    Flag = (PcuCrMComp.Bits.COMP_FORCE == 1);
  } while (Flag && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  if (Flag) {
    return mrcFail;
  }

  MrcWait (MrcData, 10 * HPET_1US); // Wait 10 - 20 us for Comp to Complete

  return mrcSuccess;
}

/**
  This function sets the self refresh idle timer and enables it.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing
**/
void
EnterSR (
  IN MrcParameters *const MrcData
  )
{
  MCDECS_CR_PM_SREF_CONFIG_MCMAIN_STRUCT  PmSrefConfig;

  PmSrefConfig.Data             = 0;
  PmSrefConfig.Bits.SR_Enable   = 1;
  PmSrefConfig.Bits.Idle_timer  = SELF_REFRESH_IDLE_COUNT;
  MrcWriteCR (MrcData, MCDECS_CR_PM_SREF_CONFIG_MCMAIN_REG, PmSrefConfig.Data);
  MrcWait (MrcData, HPET_1US);
  return;
}

/**
  This function sets the self refresh idle timer and disables it.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
MrcStatus
ExitSR (
  IN MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION                      *MrcCall;
  UINT64                                  Timeout;
  BOOLEAN                                 Flag;
  MCDECS_CR_PM_SREF_CONFIG_MCMAIN_STRUCT  PmSrefConfig;
  MCDECS_CR_STALL_DRAIN_MCMAIN_STRUCT     StallDrain;

  MrcCall                       = MrcData->Inputs.Call.Func;
  Timeout                       = MrcCall->MrcGetCpuTime (MrcData) + 10000; // 10 seconds timeout
  PmSrefConfig.Data             = 0;
  PmSrefConfig.Bits.Idle_timer  = SELF_REFRESH_IDLE_COUNT;
  MrcWriteCR (MrcData, MCDECS_CR_PM_SREF_CONFIG_MCMAIN_REG, PmSrefConfig.Data);

  //
  // Poll until MCDECS_CR_STALL_DRAIN_MCMAIN_STRUCT.sr_state becomes zero (DDR is not in self-refresh)
  //
  do {
    StallDrain.Data = MrcReadCR (MrcData, MCDECS_CR_STALL_DRAIN_MCMAIN_REG);
    Flag            = (StallDrain.Bits.sr_state == 1);
  } while (Flag && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  if (Flag) {
    return mrcFail;
  }

  return mrcSuccess;
}

/**
  This function programs the WDB.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing
**/
void
SetupWDB (
  IN MrcParameters *const MrcData
  )
{
  UINT8     a;
  const UINT32 vmask    =  0x41041041;
  const UINT32 amask[9] = {0x86186186, 0x18618618, 0x30C30C30, 0xA28A28A2, 0x8A28A28A,
                           0x14514514, 0x28A28A28, 0x92492492, 0x24924924};
  static const UINT32 seeds[MRC_WDB_NUM_MUX_SEEDS] = {0xA10CA1, 0xEF0D08, 0xAD0A1E};
  UINT8     Channel;
  UINT32    Offset;
  MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_STRUCT ReutPatWdbClMuxLmn;

  //
  // Fill first 8 entries as simple 2 LFSR VA pattern
  // VicRot=8, Start=0
  //
  WriteWDBVAPattern (MrcData, 0, BASIC_VA_PATTERN_SPRED_8, 8, 0);

  //
  // Fill next 54 entries as 3 LFSR VA pattern
  //
  for (a = 0; a < 9; a++) {
    //
    // VicRot=6, Start=8+a*6
    //
    WriteWDBVAPattern (MrcData, amask[a], vmask, 6, 8 + a * 6);
  }
  //
  // Write the LFSR seeds
  //
  MrcProgramLFSR (MrcData, &seeds[0], 0, MRC_WDB_NUM_MUX_SEEDS);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (&MrcData->Outputs, Channel)) {
      ReutPatWdbClMuxLmn.Data                         = 0;
      ReutPatWdbClMuxLmn.Bits.N_counter               = 10;
      ReutPatWdbClMuxLmn.Bits.M_counter               = 1;
      ReutPatWdbClMuxLmn.Bits.L_counter               = 1;
      ReutPatWdbClMuxLmn.Bits.Enable_Sweep_Frequency  = 1;
      Offset = MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_REG +
        ((MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_REG) * Channel);
      MrcWriteCR (MrcData, Offset, ReutPatWdbClMuxLmn.Data);
    }
  }

  return;
}

/**
  This function will program all present channels with the seeds passed in.

  @param[in] MrcData   - Global MRC data structure
  @param[in] Seeds     - Array of seeds programmed into PAT_WDB_CL_MUX_PB_RD/WR
  @param[in] Start     - Zero based starting seed location
  @param[in] SeedCount - Number of seeds in the array

  @retval - Nothing

**/
void
MrcProgramLFSR (
  IN MrcParameters *const MrcData,
  IN const UINT32  *const Seeds,
  IN const UINT8          Start,
  IN const UINT8          SeedCount
  )
{
  UINT32 CrOffset;
  UINT8 Channel;
  UINT8 Index;
  UINT8 Stop;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (&MrcData->Outputs, Channel)) {
      Stop = Start + SeedCount;
      for (Index = Start; Index < Stop; Index++) {
        CrOffset = MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_REG +
          ((MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_REG) * Channel) +
          ((MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_1_REG - MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_REG) * Index);
        MrcWriteCR (MrcData, CrOffset, Seeds[Index]);
        CrOffset = MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_REG +
          ((MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_REG) * Channel) +
          ((MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_1_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_REG) * Index);
        MrcWriteCR (MrcData, CrOffset, Seeds[Index]);
      }
    }
  }
}

/**
  This function Write 1 cacheline worth of data to the WDB

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Patterns - Array of bytes.  Each bytes represents 8 chunks of the cachelines for 1 lane.
                         Each entry in Patterns represents a different cacheline for a different lane.
  @param[in] PMask    - Array of len Spread uint8.  Maps the patterns to the actual DQ lanes.
                         DQ[0] = Patterns[PMask[0]], ... DQ[Spread-1] = Patterns[PMask[Spread-1]]
                         DQ[Spread] = DQ[0], ... DQ[2*Spread-1] = DQ[Spread-1]
  @param[in] Start    - Starting entry in the WDB.

  @retval Nothing
**/
void
WriteWDBFixedPattern (
  IN MrcParameters *const MrcData,
  IN UINT8 *const            Patterns,
  IN UINT8 *const            PMask,
  IN const UINT8          Spread,
  IN const UINT16         Start
  )
{
  MrcOutput                           *Outputs;
  UINT8                               Channel;
  UINT8                               up32;
  UINT8                               chunk;
  UINT8                               b;
  UINT8                               beff;
  UINT8                               burst;
  UINT32                              data;
  UINT32                              pointer;
  UINT32                              Offset;
  MCHBAR_CH0_CR_QCLK_LDAT_PDAT_STRUCT QclkLdatPdat;

  Outputs = &MrcData->Outputs;
  for (chunk = 0; chunk < 8; chunk++) {
    //
    // Program LDAT_DATAIN_*
    //
    for (up32 = 0; up32 < 2; up32++) {
      data = 0;
      for (b = 0; b < 32; b++) {
        beff  = (b + 32 * up32) % Spread;
        burst = Patterns[PMask[beff]];
        if (burst & (MRC_BIT0 << chunk)) {
          data |= (MRC_BIT0 << b);
        }
      }

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcChannelExist (Outputs, Channel)) {
          Offset = MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_0_REG +
            ((MCHBAR_CH1_CR_QCLK_LDAT_DATAIN_0_REG - MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_0_REG) * Channel) +
            ((MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_1_REG - MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_0_REG) * up32);
          MrcWriteCR (MrcData, Offset, data);
        }
      }
    } // up32

    pointer = MRC_BIT16 + chunk;

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        //
        // Set rep = 0 don't want to replicate the data
        // Set banksel field to the value of the chunk you want to write the 64 bits to.
        // Set arraysel = 0 ( indicating it is the MC WDB) and mode = 'b01 in the SDAT register
        //
        Offset = MCHBAR_CH0_CR_QCLK_LDAT_SDAT_REG +
          ((MCHBAR_CH1_CR_QCLK_LDAT_SDAT_REG - MCHBAR_CH0_CR_QCLK_LDAT_SDAT_REG) * Channel);
        MrcWriteCR (MrcData, Offset, pointer);

        //
        // Finally, write the PDAT register indicating which cacheline of the WDB you want to write to
        // by setting fastaddr field to one of the 64 cache lines. Also set cmdb in the pdat register to 4'b1000,
        // indicating that this is a LDAT write
        //
        Offset = MCHBAR_CH0_CR_QCLK_LDAT_PDAT_REG +
          ((MCHBAR_CH1_CR_QCLK_LDAT_PDAT_REG - MCHBAR_CH0_CR_QCLK_LDAT_PDAT_REG) * Channel);
        QclkLdatPdat.Data = 0;
        QclkLdatPdat.Bits.CMDB = 8;
        QclkLdatPdat.Bits.FASTADDR = MIN (Start, MCHBAR_CH0_CR_QCLK_LDAT_PDAT_FASTADDR_MAX);
        MrcWriteCR (MrcData, Offset, QclkLdatPdat.Data);
      }
    }
  } // chunk
  //
  // Turn off LDAT mode after writing to WDB is complete
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      Offset = MCHBAR_CH0_CR_QCLK_LDAT_SDAT_REG +
        ((MCHBAR_CH1_CR_QCLK_LDAT_SDAT_REG - MCHBAR_CH0_CR_QCLK_LDAT_SDAT_REG) * Channel);
      MrcWriteCR (MrcData, Offset, 0);
    }
  }

  return;
}

/**
  This rotine performs the following steps:
    Step 0: Iterate through all VicRots
    Step 1: Create a compressed vector for a given 32 byte cacheline
            Each byte has a value of LFSR0=AA/LFSR1=CC/LFSR2=F0
    Step 2: Expand compressed vector into chunks and 32 bit segments

  @param[in] MrcData - Include all MRC global data.
  @param[in] vmask   - 32 bit victim mask.  1 indicates this bit should use LFSR0
  @param[in] amask   - 32 bit aggressor mask. 0/1 indicates this bit should use LFSR1/2
  @param[in] VicRot  - Number of times to circular rotate vmask/amask
  @param[in] Start   - Starting entry in the WDB

  @retval Nothing
**/
void
WriteWDBVAPattern (
  IN MrcParameters *const MrcData,
  IN UINT32               amask,
  IN UINT32               vmask,
  IN const UINT8          VicRot,
  IN const UINT16         Start
  )
{
  static const UINT8 VAMask2Compressed[4] = {0xAA, 0xC0, 0xCC, 0xF0};
  MrcOutput       *Outputs;
  UINT8           b;
  UINT8           chunk;
  UINT8           Channel;
  UINT8           cmask;
  UINT16          v;
  UINT32          Vic;
  UINT32          Agg2;
  UINT32          data;
  UINT32          pointer;
  UINT32          msb;
  UINT8           Compressed[32];
  UINT32          BitMask;
  UINT8           Index;
  UINT16          Scratch;
  UINT32          Offset;
  MCHBAR_CH0_CR_QCLK_LDAT_PDAT_STRUCT QclkLdatPdat;

  Outputs = &MrcData->Outputs;
  for (v = 0; v < VicRot; v++) {
    //
    // Iterate through all 32 bits and create a compressed version of cacheline
    // AA = Victim (LFSR0), CC = Agg1(LFSR1), F0 = Agg2 (LFSR2)
    //
    for (b = 0; b < 32; b++) {
      BitMask = MRC_BIT0 << b;
      Vic     = (vmask & BitMask);
      Agg2    = (amask & BitMask);

      //
      // Program compressed vector
      //
      if (Vic && Agg2) {
        Index = 1;
      } else if (Vic && !Agg2) {
        Index = 0;
      } else if (!Vic && !Agg2) {
        Index = 3; //@todo: Check the change.
      } else {
        Index = 2;
      }

      Compressed[b] = VAMask2Compressed[Index];
    }

    for (chunk = 0; chunk < 8; chunk++) {
      data  = 0;
      cmask = (MRC_BIT0 << chunk);
      for (b = 0; b < 32; b++) {
        if (Compressed[b] & cmask) {
          data |= (MRC_BIT0 << b);
        }
      }
      //
      // Set rep = 0 don't want to replicate the data
      // Set banksel field to the value of the chunk you want to write the 64 bits to.
      // Set arraysel = 0 ( indicating it is the MC WDB) and mode = 'b01 in the SDAT register
      //
      pointer = MRC_BIT16 + chunk;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcChannelExist (Outputs, Channel)) {
          Offset = MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_0_REG +
            ((MCHBAR_CH1_CR_QCLK_LDAT_DATAIN_0_REG - MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_0_REG) * Channel);
          MrcWriteCR (MrcData, Offset, data);
          Offset = MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_1_REG +
            ((MCHBAR_CH1_CR_QCLK_LDAT_DATAIN_1_REG - MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_1_REG) * Channel);
          MrcWriteCR (MrcData, Offset, data);
          Offset = MCHBAR_CH0_CR_QCLK_LDAT_SDAT_REG +
            ((MCHBAR_CH1_CR_QCLK_LDAT_SDAT_REG - MCHBAR_CH0_CR_QCLK_LDAT_SDAT_REG) * Channel);
          MrcWriteCR (MrcData, Offset, pointer);

          //
          // Finally, write the PDAT register indicating which cacheline of the WDB you want to write to
          // by setting fastaddr field to one of the 64 cache lines. Also set cmdb in the pdat register to 4'b1000,
          // indicating that this is a LDAT write
          //
          Scratch = Start + v;
          Offset = MCHBAR_CH0_CR_QCLK_LDAT_PDAT_REG +
            ((MCHBAR_CH1_CR_QCLK_LDAT_PDAT_REG - MCHBAR_CH0_CR_QCLK_LDAT_PDAT_REG) * Channel);
          QclkLdatPdat.Data           = 0;
          QclkLdatPdat.Bits.CMDB      = 8;
          QclkLdatPdat.Bits.FASTADDR  = MIN (Scratch, MCHBAR_CH0_CR_QCLK_LDAT_PDAT_FASTADDR_MAX);
          MrcWriteCR (MrcData, Offset, QclkLdatPdat.Data);
        }
      }
    }
    //
    // Circular Rotate Vic/Agg Masks
    //
    msb   = (vmask >> 31) & 0x1;
    vmask = (vmask << 1) | msb;
    msb   = (amask >> 31) & 0x1;
    amask = (amask << 1) | msb;
  }
  //
  // Clear LDAT mode
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      Offset = MCHBAR_CH0_CR_QCLK_LDAT_SDAT_REG +
        ((MCHBAR_CH1_CR_QCLK_LDAT_SDAT_REG - MCHBAR_CH0_CR_QCLK_LDAT_SDAT_REG) * Channel);
      MrcWriteCR (MrcData, Offset, 0);
    }
  }

  return;
}

/**
  Write VA pattern in CADB
  Use basic VA pattern for CADB with 2 LFSRs. Rotation is manual
  Bit Order is:
   DDR3/LPDDR3: [CKE[3:0], ODT[3:0], CMD[2:0], CS[3:0], BA[2:0], MA[15:0]]
                  [59:56]   [51:48]   [42:40]  [35:32]  [26:24]    [15:0]

   DDR4:        [CKE[3:0], ODT[3:0], CMD[3:0], CS[3:0], BA[3:0], MA[16:0]]
                  [59:56]   [51:48]   [43:40]  [35:32]  [27:24]    [16:0]

  (See MCHBAR_CHx_CR_REUT_CH_PAT_CADB_PROG layout)

  NOTE: CKE, ODT and CS are not used in functional mode and are ignored

  @param[in] MrcData   - Include all MRC global data.
  @param[in] Channel   - Channel to setup.
  @param[in] VicSpread - Separation of the Victim Bit.
  @param[in] VicBit    - The Bit to be the Victim.
  @param[in] LMNEn     - To enable LMN counter

  @retval Nothing
**/
void
SetupCADB (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          VicSpread,
  IN const UINT8          VicBit,
  IN const UINT8          LMNEn
  )
{
  static const UINT32 seeds[3] = {0x96EA1, 0xCABEEF, 0x53DEAD};
  const MRC_FUNCTION *MrcCall;
  UINT8     Row;
  UINT8     bit;
  UINT8     CadbBits;
  UINT8     lfsr0;
  UINT8     lfsr1;
  UINT8     Lfsr;
  UINT8     bremap;
  UINT8     Fine;
  UINT32    Offset;
  BOOLEAN   Ddr4;
  MCHBAR_CH0_CR_REUT_CH_PAT_CADB_PROG_STRUCT        ReutChPatCadbProg;
  MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_CTRL_STRUCT    ReutChPatCadbMuxCtrl;
  MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_STRUCT  ReutCadbClMuxLmn;
  MCHBAR_CH0_CR_REUT_CH_PAT_CADB_WRITE_POINTER_STRUCT  ReutChPatCadbWritePointer;

  MrcCall = MrcData->Inputs.Call.Func;
  Ddr4    = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_DDR4);
  //
  // Currently, always start writing at CADB row0.  Could add Start point in future.
  //
  ReutChPatCadbWritePointer.Data = 0;
  ReutChPatCadbWritePointer.Bits.Write_Enable = 1;
  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_WRITE_POINTER_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_WRITE_POINTER_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_WRITE_POINTER_REG) * Channel);
  {
    MrcWriteCR (MrcData, Offset, ReutChPatCadbWritePointer.Data);
  }

  if (Ddr4) {
    CadbBits = 25;  // MA + BA + CMD = 17 + 4 + 4
  } else {
    CadbBits = 22;  // MA + BA + CMD = 16 + 3 + 3
  }
  //
  // Plan to use VicSpread of 7 bits
  // Walk through CADB rows, assigning bit for 1 VA pattern
  //
  for (Row = 0; Row < MRC_NUM_CADB_ENTRIES; Row++) {

    lfsr0 = (Row & 0x1);         // 0, 1, 0, 1, 0, 1, 0, 1 for r = 0,1, ..., 7
    lfsr1 = ((Row >> 1) & 0x1);  // 0, 0, 1, 1, 0, 0, 1, 1 for r = 0,1, ..., 7
    //
    // Assign Victim/Aggressor Bits
    //
    ReutChPatCadbProg.Data = 0;
    for (bit = 0; bit < CadbBits; bit++) {
      Fine = bit % VicSpread;
      if (Ddr4) {
        if (bit >= 21) {        // CMD
          bremap = bit + 19;    // b = [40-43]
        } else if (bit >= 17) { // BA
          bremap = bit + 7;     // b = [24-27]
        } else {                // MA
          bremap = bit;         // b = [0-16]
        }
      } else {
        if (bit >= 19) {        // CMD
          bremap = bit + 21;    // b = [40-42]
        } else if (bit >= 16) { // BA
          bremap = bit + 8;     // b = [24-26]
        } else {                // MA
          bremap = bit;         // b = [0-15]
        }
      }

      if (Fine == VicBit) {
        Lfsr = lfsr0;
      } else {
        Lfsr = lfsr1;
      }
      ReutChPatCadbProg.Data |= MrcCall->MrcLeftShift64 ((UINT64) Lfsr, bremap);
    }
    //
    // Write Row. CADB is auto incremented after every write
    //
    Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_PROG_REG +
      ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_PROG_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_PROG_REG) * Channel);
    {
      MrcWriteCR64 (MrcData, Offset, ReutChPatCadbProg.Data);
    }
  }
  //
  // Setup CADB in terms of LFSR selects, LFSR seeds, LMN constants and overall control
  //
  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_CTRL_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_CTRL_REG) * Channel);
  ReutChPatCadbMuxCtrl.Data               = 0;
  ReutChPatCadbMuxCtrl.Bits.Mux0_Control  = LMNEn ? 0 : 2;
  ReutChPatCadbMuxCtrl.Bits.Mux1_Control  = 2;
  ReutChPatCadbMuxCtrl.Bits.Mux2_Control  = 2;
  ReutChPatCadbMuxCtrl.Bits.LFSR_Type     = 3; // LFSR8
  MrcWriteCR (MrcData, Offset, ReutChPatCadbMuxCtrl.Data);

  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_REG) * Channel);
  ReutCadbClMuxLmn.Data                         = 0;
  ReutCadbClMuxLmn.Bits.Enable_Sweep_Frequency  = 1;
  ReutCadbClMuxLmn.Bits.L_counter               = 1;
  ReutCadbClMuxLmn.Bits.M_counter               = 1;
  ReutCadbClMuxLmn.Bits.N_counter               = 6;
  MrcWriteCR (MrcData, Offset, ReutCadbClMuxLmn.Data);

  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_0_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_PB_0_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_0_REG) * Channel);
  MrcWriteCR (MrcData, Offset, seeds[0]);

  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_1_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_PB_1_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_1_REG) * Channel);
  MrcWriteCR (MrcData, Offset, seeds[1]);

  Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_2_REG +
    ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_PB_2_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_2_REG) * Channel);
  MrcWriteCR (MrcData, Offset, seeds[2]);

  return;
}

/**
  This function handles writing to the REUT Addressing sequence for IO Tests.
  To not write a certain parameter, pass a NULL pointer to the function.

  @param[in] MrcData       - MRC global data structure.
  @param[in] Channel       - Specifies the channel to program.
  @param[in] StartAddr     - Start value for Rank/Bank/Row/Col.
  @param[in] StopAddr      - Stop value for Rank/Bank/Row/Col.
  @param[in] FieldOrder    - Relative order for carry propagates of Rank/Bank/Row/Col.
  @param[in] IncRate       - The number of writes to Rank/Bank/Row/Col before updating the address.
                              Note: The function will handle linear vs exponential and a value of 0 specifies a rate of 1.
  @param[in] IncValue      - The amount to increase Rank/Bank/Row/Col address.
  @param[in] WrapTriggerEn - Enables wrap trigger for Rank/Bank/Row/Col to enable stopping on subsequence and sequence.
  @param[in] WrapCarryEn   - Enables carry propagation on wrap to the next higest order field
  @param[in] AddrInvertEn  - Enables inverting the Rank/Bank/Row/Col addresses based on AddrInvertRate.
  @param[in] AddrIvertRate - Exponential rate of address inversion.  Only updated if AddrInvertEn != NULL.
  @param[in] EnableDebug   - Enables/Disables debug printing.

  @retval Nothing
**/
void
MrcProgramSequenceAddress (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT16         StartAddr[MrcReutFieldMax],
  IN const UINT16         StopAddr[MrcReutFieldMax],
  IN const UINT8          FieldOrder[MrcReutFieldMax],
  IN const UINT32         IncRate[MrcReutFieldMax],
  IN const UINT16         IncValue[MrcReutFieldMax],
  IN const UINT8          WrapTriggerEn[MrcReutFieldMax],
  IN const UINT8          WrapCarryEn[MrcReutFieldMax],
  IN const UINT8          AddrInvertEn[MrcReutFieldMax],
  IN const UINT8          AddrInvertRate,
  IN const BOOLEAN        EnableDebug
  )
{
  const MRC_FUNCTION *MrcCall;
  MrcInput  *Inputs;
  UINT64    RowMask;
  UINT32    ColumnMask;
  UINT32    CrOffset;
  UINT32    IncRateScratch;
  UINT16    ColAddrIncMax;
  MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_STRUCT                   ReutChSeqBaseAddrStart;
  MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_STRUCT                    ReutChSeqBaseAddrWrap;
  MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_0_STRUCT                 ReutChSeqBaseAddrIncCtl;
  MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_0_STRUCT  ReutChSeqBaseAddrOrderCarryInvertCtl;
#ifdef MRC_DEBUG_PRINT
  UINT32    RowMax;
  UINT32    BankMax;
  MrcDebug  *Debug;
  Debug   = &MrcData->Outputs.Debug;
  RowMax  = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_Row_Address_MAX;
  BankMax = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_Bank_Address_MAX;
#endif

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;

  //
  // @todo: Review next stepping
  //
  RowMask       = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_Row_Address_MSK;
  ColumnMask    = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_Column_Address_MSK;
  ColAddrIncMax = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_0_Column_Base_Address_Increment_MAX;

#ifdef MRC_DEBUG_PRINT
  if (EnableDebug) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Ch.%d Masks: Col - 0x%x\t Row - 0x%08x%08x\tColAddrIncMax: 0x%x\n",
      Channel,
      ColumnMask,
      (UINT32) MrcCall->MrcRightShift64 (RowMask, 32),
      (UINT32) RowMask,
      ColAddrIncMax
      );
  }
#endif

  if (StartAddr != NULL) {
    ReutChSeqBaseAddrStart.Data = MrcCall->MrcLeftShift64 (
                                             (UINT64) ((StartAddr[MrcReutFieldRank] << (56 - 32)) + (StartAddr[MrcReutFieldBank] << (48 - 32))),
                                             32
                                             );
    ReutChSeqBaseAddrStart.Data |= MrcCall->MrcLeftShift64 ((UINT64) StartAddr[MrcReutFieldRow], 24) & RowMask;
    ReutChSeqBaseAddrStart.Data |= (UINT64) (StartAddr[MrcReutFieldCol] & ColumnMask);

    CrOffset = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_REG +
    (
      (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_REG)
      * Channel
      );
    MrcWriteCR64 (MrcData, CrOffset, ReutChSeqBaseAddrStart.Data);

#ifdef MRC_DEBUG_PRINT
    if (EnableDebug) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Start:\n\tField\tInput\t\tStruct\n");
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\tCol:\t0x%x\t\t0x%x\n",
        StartAddr[MrcReutFieldCol],
        ReutChSeqBaseAddrStart.Data & ColumnMask
        );
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\tRow:\t0x%x\t\t0x%x\n",
        StartAddr[MrcReutFieldRow],
        MrcCall->MrcRightShift64 (ReutChSeqBaseAddrStart.Data, 24) & RowMax
        );
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\tBank:\t0x%x\t\t0x%x\n",
        StartAddr[MrcReutFieldBank],
        MrcCall->MrcRightShift64 (ReutChSeqBaseAddrStart.Data, 48) & BankMax
        );
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\tRank:\t0x%x\t\t0x%x\n",
        StartAddr[MrcReutFieldRank],
        MrcCall->MrcRightShift64 (ReutChSeqBaseAddrStart.Data, 56) & MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_Rank_Address_MAX
        );
    }
#endif
  }

  if (StopAddr != NULL) {
    ReutChSeqBaseAddrWrap.Data = MrcCall->MrcLeftShift64 (
                                            (UINT64) ((StopAddr[MrcReutFieldRank] << (56 - 32)) + (StopAddr[MrcReutFieldBank] << (48 - 32))),
                                            32
                                            );
    ReutChSeqBaseAddrWrap.Data |= MrcCall->MrcLeftShift64 ((UINT64) StopAddr[MrcReutFieldRow], 24) & RowMask;
    ReutChSeqBaseAddrWrap.Data |= (UINT64) (StopAddr[MrcReutFieldCol] & ColumnMask);

    CrOffset = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_REG +
    (
      (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_REG)
      * Channel
      );
    MrcWriteCR64 (MrcData, CrOffset, ReutChSeqBaseAddrWrap.Data);

#ifdef MRC_DEBUG_PRINT
    if (EnableDebug) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Stop:\n\tField\tInput\t\tStruct\n");
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\tCol:\t0x%x\t\t0x%x\n",
        StopAddr[MrcReutFieldCol],
        ReutChSeqBaseAddrWrap.Data & ColumnMask
        );
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\tRow:\t0x%x\t\t0x%x\n",
        StopAddr[MrcReutFieldRow],
        MrcCall->MrcRightShift64 (ReutChSeqBaseAddrWrap.Data, 24) & RowMax
        );
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\tBank:\t0x%x\t\t0x%x\n",
        StopAddr[MrcReutFieldBank],
        MrcCall->MrcRightShift64 (ReutChSeqBaseAddrWrap.Data, 48) & BankMax
        );
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\tRank:\t0x%x\t\t0x%x\n",
        StopAddr[MrcReutFieldRank],
        MrcCall->MrcRightShift64 (ReutChSeqBaseAddrWrap.Data, 56) & MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_Rank_Address_MAX
        );
    }
#endif
  }

  if (FieldOrder != NULL || WrapTriggerEn != NULL || WrapCarryEn != NULL || AddrInvertEn != NULL) {
    ReutChSeqBaseAddrOrderCarryInvertCtl.Data = 0;

    CrOffset = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_0_REG +
    (
      (
        MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_1_REG -
        MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_0_REG
        ) * Channel
      );

    if (FieldOrder == NULL || WrapTriggerEn == NULL || WrapCarryEn == NULL || AddrInvertEn == NULL) {
      ReutChSeqBaseAddrOrderCarryInvertCtl.Data = MrcReadCR (MrcData, CrOffset);
    }

    if (FieldOrder != NULL) {
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Base_Column_Address_Order = FieldOrder[MrcReutFieldCol];
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Base_Row_Address_Order    = FieldOrder[MrcReutFieldRow];
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Base_Bank_Address_Order   = FieldOrder[MrcReutFieldBank];
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Base_Rank_Address_Order   = FieldOrder[MrcReutFieldRank];

#ifdef MRC_DEBUG_PRINT
      if (EnableDebug) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Order:\n\tField\tInput\t\tStruct\t\t\n");
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tCol:\t0x%x\t\t0x%x\t\t\n",
          FieldOrder[MrcReutFieldCol],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Base_Column_Address_Order
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tRow:\t0x%x\t\t0x%x\t\t\n",
          FieldOrder[MrcReutFieldRow],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Base_Row_Address_Order
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tBank:\t0x%x\t\t0x%x\t\t\n",
          FieldOrder[MrcReutFieldBank],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Base_Bank_Address_Order
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tRank:\t0x%x\t\t0x%x\t\t\n",
          FieldOrder[MrcReutFieldRank],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Base_Rank_Address_Order
          );
      }
#endif
    }

    if (WrapTriggerEn != NULL) {
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Column_Base_Wrap_Trigger_Enable = WrapTriggerEn[MrcReutFieldCol];
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Row_Base_Wrap_Trigger_Enable    = WrapTriggerEn[MrcReutFieldRow];
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Bank_Base_Wrap_Trigger_Enable   = WrapTriggerEn[MrcReutFieldBank];
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Rank_Base_Wrap_Trigger_Enable   = WrapTriggerEn[MrcReutFieldRank];
#ifdef MRC_DEBUG_PRINT
      if (EnableDebug) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WrapT:\n\tField\tInput\t\tStruct\t\t\n");
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tCol:\t0x%x\t\t0x%x\t\t\n",
          WrapTriggerEn[MrcReutFieldCol],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Column_Base_Wrap_Trigger_Enable
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tRow:\t0x%x\t\t0x%x\t\t\n",
          WrapTriggerEn[MrcReutFieldRow],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Row_Base_Wrap_Trigger_Enable
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tBank:\t0x%x\t\t0x%x\t\t\n",
          WrapTriggerEn[MrcReutFieldBank],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Bank_Base_Wrap_Trigger_Enable
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tRank:\t0x%x\t\t0x%x\t\t\n",
          WrapTriggerEn[MrcReutFieldRank],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Rank_Base_Wrap_Trigger_Enable
          );
      }
#endif
    }

    if (WrapCarryEn != NULL) {
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Column_Base_Wrap_Carry_Enable = WrapCarryEn[MrcReutFieldCol];
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Row_Base_Wrap_Carry_Enable    = WrapCarryEn[MrcReutFieldRow];
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Bank_Base_Wrap_Carry_Enable   = WrapCarryEn[MrcReutFieldBank];
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Rank_Base_Wrap_Carry_Enable   = WrapCarryEn[MrcReutFieldRank];

#ifdef MRC_DEBUG_PRINT
      if (EnableDebug) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WrapC:\n\tField\tInput\t\tStruct\t\t\n");
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tCol:\t0x%x\t\t0x%x\t\t\n",
          WrapCarryEn[MrcReutFieldCol],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Column_Base_Wrap_Carry_Enable
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tRow:\t0x%x\t\t0x%x\t\t\n",
          WrapCarryEn[MrcReutFieldRow],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Row_Base_Wrap_Carry_Enable
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tBank:\t0x%x\t\t0x%x\t\t\n",
          WrapCarryEn[MrcReutFieldBank],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Bank_Base_Wrap_Carry_Enable
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tRank:\t0x%x\t\t0x%x\t\t\n",
          WrapCarryEn[MrcReutFieldRank],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Rank_Base_Wrap_Carry_Enable
          );
      }
#endif
    }

    if (AddrInvertEn != NULL) {
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Base_Address_Invert_Rate          = AddrInvertRate;
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Column_Base_Address_Invert_Enable = AddrInvertEn[MrcReutFieldCol];
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Row_Base_Address_Invert_Enable    = AddrInvertEn[MrcReutFieldRow];
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Bank_Base_Address_Invert_Enable   = AddrInvertEn[MrcReutFieldBank];
      ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Rank_Base_Address_Invert_Enable   = AddrInvertEn[MrcReutFieldRank];

#ifdef MRC_DEBUG_PRINT
      if (EnableDebug) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "InvtEn:\n\tField\tInput\t\tStruct\t\t\n");
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tCol:\t0x%x\t\t0x%x\t\t\n",
          AddrInvertEn[MrcReutFieldCol],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Column_Base_Address_Invert_Enable
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tRow:\t0x%x\t\t0x%x\t\t\n",
          AddrInvertEn[MrcReutFieldRow],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Row_Base_Address_Invert_Enable
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tBank:\t0x%x\t\t0x%x\t\t\n",
          AddrInvertEn[MrcReutFieldBank],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Bank_Base_Address_Invert_Enable
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tRank:\t0x%x\t\t0x%x\t\t\n",
          AddrInvertEn[MrcReutFieldRank],
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Rank_Base_Address_Invert_Enable
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tRate:\t0x%x\t\t0x%x\t\t\n",
          AddrInvertRate,
          ReutChSeqBaseAddrOrderCarryInvertCtl.Bits.Base_Address_Invert_Rate
          );
      }
#endif
    }

    MrcWriteCR (MrcData, CrOffset, ReutChSeqBaseAddrOrderCarryInvertCtl.Data);
  }

  if (IncRate != 0 || IncValue != 0) {
    ReutChSeqBaseAddrIncCtl.Data = 0;

    CrOffset = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_0_REG +
    (
      (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_0_REG)
      * Channel
      );

    if (IncRate == 0 || IncValue == 0) {
      ReutChSeqBaseAddrIncCtl.Data = MrcReadCR64 (MrcData, CrOffset);
    }

    if (IncRate != 0) {
      //
      // RANK
      //
      IncRateScratch = (IncRate[MrcReutFieldRank] > 31) ? (MrcLog2 (IncRate[MrcReutFieldRank] - 1)) :
        (128 + IncRate[MrcReutFieldRank]);
      ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Update_Rate  = IncRateScratch;
      ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Update_Scale = IncRateScratch >> 7;
      //
      // BANK
      //
      IncRateScratch = (IncRate[MrcReutFieldBank] > 31) ? (MrcLog2 (IncRate[MrcReutFieldBank] - 1)) :
        (128 + IncRate[MrcReutFieldBank]);
      ReutChSeqBaseAddrIncCtl.Bits.Bank_Base_Address_Update_Rate  = IncRateScratch;
      ReutChSeqBaseAddrIncCtl.Bits.Bank_Base_Address_Update_Scale = IncRateScratch >> 7;
      //
      // ROW
      //
      IncRateScratch = (IncRate[MrcReutFieldRow] > 15) ? (MrcLog2 (IncRate[MrcReutFieldRow] - 1)) :
        (32 + IncRate[MrcReutFieldRow]);
      ReutChSeqBaseAddrIncCtl.Bits.Row_Base_Address_Update_Rate   = IncRateScratch;
      ReutChSeqBaseAddrIncCtl.Bits.Row_Base_Address_Update_Scale  = IncRateScratch >> 5;
      //
      // COL
      //
      IncRateScratch = (IncRate[MrcReutFieldCol] > 31) ? (MrcLog2 (IncRate[MrcReutFieldCol] - 1)) :
        (128 + IncRate[MrcReutFieldCol]);
      ReutChSeqBaseAddrIncCtl.Bits.Column_Base_Address_Update_Rate  = IncRateScratch;
      ReutChSeqBaseAddrIncCtl.Bits.Column_Base_Address_Update_Scale = IncRateScratch >> 7;

#ifdef MRC_DEBUG_PRINT
      if (EnableDebug) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "IncRate:\n\tField\tInput\t\tStruct\t\tScale\n");
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tCol:\t0x%x\t\t0x%x\t\t0x%x\n",
          IncRate[MrcReutFieldCol],
          ReutChSeqBaseAddrIncCtl.Bits.Column_Base_Address_Update_Rate,
          ReutChSeqBaseAddrIncCtl.Bits.Column_Base_Address_Update_Scale
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tRow:\t0x%x\t\t0x%x\t\t0x%x\n",
          IncRate[MrcReutFieldRow],
          ReutChSeqBaseAddrIncCtl.Bits.Row_Base_Address_Update_Rate,
          ReutChSeqBaseAddrIncCtl.Bits.Row_Base_Address_Update_Scale
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tBank:\t0x%x\t\t0x%x\t\t0x%x\n",
          IncRate[MrcReutFieldBank],
          ReutChSeqBaseAddrIncCtl.Bits.Bank_Base_Address_Update_Rate,
          ReutChSeqBaseAddrIncCtl.Bits.Bank_Base_Address_Update_Scale
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tRank:\t0x%x\t\t0x%x\t\t0x%x\n",
          IncRate[MrcReutFieldRank],
          ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Update_Rate,
          ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Update_Scale
          );
      }
#endif
    }

    if (IncValue != 0) {
      ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Increment    = IncValue[MrcReutFieldRank];
      ReutChSeqBaseAddrIncCtl.Bits.Bank_Base_Address_Increment    = IncValue[MrcReutFieldBank];
      ReutChSeqBaseAddrIncCtl.Bits.Row_Base_Address_Increment     = IncValue[MrcReutFieldRow];
      ReutChSeqBaseAddrIncCtl.Bits.Column_Base_Address_Increment  = IncValue[MrcReutFieldCol] & ColAddrIncMax;

#ifdef MRC_DEBUG_PRINT
      if (EnableDebug) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "IncVal:\n\tField\tInput\t\tStruct\t\t\n");
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tCol:\t0x%x\t\t0x%x\t\t\n",
          IncValue[MrcReutFieldCol],
          ReutChSeqBaseAddrIncCtl.Bits.Column_Base_Address_Increment
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tRow:\t0x%x\t\t0x%x\t\t\n",
          IncValue[MrcReutFieldRow],
          ReutChSeqBaseAddrIncCtl.Bits.Row_Base_Address_Increment
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tBank:\t0x%x\t\t0x%x\t\t\n",
          IncValue[MrcReutFieldBank],
          ReutChSeqBaseAddrIncCtl.Bits.Bank_Base_Address_Increment
          );
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\tRank:\t0x%x\t\t0x%x\t\t\n",
          IncValue[MrcReutFieldRank],
          ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Increment
          );
      }
#endif
    }

    MrcWriteCR64 (MrcData, CrOffset, ReutChSeqBaseAddrIncCtl.Data);
  }
}

/**
  Programs all the key registers to define a CPCG test

  @param[in] MrcData     - Include all MRC global data.
  @param[in] ChbitMask   - Channel Bit mak for which test should be setup for.
  @param[in] CmdPat      - [0: PatWrRd (Standard Write/Read Loopback),
                            1: PatWr (Write Only),
                            2: PatRd (Read Only),
                            3: PatRdWrTA (ReadWrite Turnarounds),
                            4: PatWrRdTA (WriteRead Turnarounds),
                            5: PatODTTA (ODT Turnaround]
  @param[in] NumCL       - Number of Cache lines
  @param[in] LC          - Loop Count exponent
  @param[in] REUTAddress - Structure that stores start, stop and increment details for address
  @param[in] SOE         - [0: Never Stop, 1: Stop on Any Lane, 2: Stop on All Byte, 3: Stop on All Lane]
  @param[in] WDBPattern  - Structure that stores start, Stop, IncRate and Dqpat for pattern.
  @param[in] EnCADB      - Enable test to write random deselect packages on bus to create xtalk/isi
  @param[in] EnCKE       - Enable CKE power down by adding 64
  @param[in] SubSeqWait  - # of Dclks to stall at the end of a sub-sequence

  @retval Nothing
**/
void
SetupIOTest (
  IN MrcParameters *const         MrcData,
  IN const UINT8                  ChbitMask,
  IN const UINT8                  CmdPat,
  IN const UINT16                 NumCL,
  IN const UINT8                  LC,
  IN const MRC_REUTAddress *const REUTAddress,
  IN const UINT8                  SOE,
  IN MRC_WDBPattern *const        WDBPattern,
  IN const UINT8                  EnCADB,
  IN const UINT8                  EnCKE,
  IN UINT16                       SubSeqWait
  )
{
  MrcDebug        *Debug;
  const MrcInput  *Inputs;
  static const UINT8 WrapCarryEn[MrcReutFieldMax]   = {0, 0, 0, 0}; // Not used in training tests
  static const UINT8 WrapTriggerEn[MrcReutFieldMax] = {0, 0, 0, 0}; // Not used in training tests
  static const UINT8 AddrInvertEn[MrcReutFieldMax]  = {0, 0, 0, 0}; // Not used in training tests
  MrcOutput       *Outputs;
  UINT8           Channel;
  INT8            LCeff;
  UINT32          LoopCountLinear;
  UINT8           Mux0;
  UINT8           Reload;
  UINT8           NumCLCR;
  UINT8           NumCL2CR;
  UINT16          Wait;
  UINT16          NumCL2;
  UINT32          LMNFreq[2];
  UINT32          Offset;
  UINT8           SubSeqStart;
  UINT8           SubSeqEnd;
  UINT8           Index;
  MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CTRL_STRUCT              ReutChPatCadbCtrl;
  MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT               ReutChSeqCfg;
  MCSCHEDS_CR_PM_PDWN_CONFIG_STRUCT                       PmPdwnConfig;
  MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_STRUCT           ReutSubSeqCtl0;
  MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_STRUCT           ReutSubSeqCtl1;
  MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_STRUCT            ReutChPatWdbCl;
  MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_STRUCT         ReutChPatWdbClMuxCfg;
  MCHBAR_CH0_CR_REUT_CH_ERR_CTL_STRUCT                    ReutChErrCtrl;
  MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_0_STRUCT     ReutChSeqDummyReadCtl;
  struct LocalSubSeqCtl {
    UINT8 ValidMask;
    MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_STRUCT Ctl[8];
  } SubSeq;

  Outputs = &MrcData->Outputs;
  Inputs  = &MrcData->Inputs;
  Debug   = &Outputs->Debug;

  //
  // Prepare variables needed for both channels
  //
  // Check for the cases where this MUST be 1: When we manually walk through SUBSEQ ODT and TAWR
  //
  LCeff = LC - MrcLog2 (NumCL - 1) + 1;
  if ((LCeff < 1) || (CmdPat == PatWrRdTA) || (CmdPat == PatODTTA)) {
    LCeff = 1;
  }

  LoopCountLinear = 1 << (LCeff - 1);

  if (NumCL > 127) {
    NumCLCR = MrcLog2 (NumCL - 1);       // Assume Exponential number
  } else {
    NumCLCR = (UINT8) NumCL + (MRC_BIT0 << 7);  // Set Number of Cache Lines as linear number
  }

  NumCL2 = 2 * NumCL;
  if (NumCL2 > 127) {
    NumCL2CR = MrcLog2 (NumCL2 - 1);    // Assume Exponential number
  } else {
    NumCL2CR = (UINT8) NumCL2 + (MRC_BIT0 << 7); // Set Number of Cache Lines as linear number
  }

  Reload = MrcLog2 (WDBPattern->IncRate - 1);

  if (WDBPattern->IncRate > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_MAX) {
    WDBPattern->IncRate = Reload;   // Have to use the exponential IncRate
  } else {
    WDBPattern->IncRate |= (1 << MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_WID);  // Linear IncRate
  }

  if (EnCKE) {
    //
    // @todo: Need to check that PDWN is programmed already.
    //
    PmPdwnConfig.Data = MrcReadCR (MrcData, MCSCHEDS_CR_PM_PDWN_CONFIG_REG);
    Wait = (UINT16) (PmPdwnConfig.Bits.PDWN_idle_counter + 16); // Adding extra DCKs, 16,  to make sure we make it to power down.
    if (Wait > SubSeqWait) {
      SubSeqWait = Wait;
    }
  }

  if (SubSeqWait > 0xFF) {
    SubSeqWait = 0xFF;
  }
  //
  // Per channel settings
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((MRC_BIT0 << Channel) & ChbitMask)) {
      Offset = MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG +
        ((MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG) * Channel);
      MrcWriteCR (MrcData, Offset, 0);   // Clear global control
      continue;
    }

    //###########################################################
    //
    // Program CADB
    //
    //###########################################################
    Offset = MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CTRL_REG +
      ((MCHBAR_CH1_CR_REUT_CH_PAT_CADB_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CTRL_REG) * Channel);
    ReutChPatCadbCtrl.Data = 0;
    ReutChPatCadbCtrl.Bits.Enable_CADB_on_Deselect = EnCADB;
    MrcWriteCR (MrcData, Offset, ReutChPatCadbCtrl.Data);
    if (EnCADB) {
      SetupCADB (MrcData, Channel, 7, 8, 0);   // LMNEn=0
    }

    //###########################################################
    //
    // Program Sequence
    //
    //###########################################################
    SubSeqStart = SubSeqEnd = 0;
    switch (CmdPat) {
      case PatWrRd:
        SubSeqEnd = 1;
        break;

      case PatWr:
        break;

      case PatRd:
        SubSeqStart = SubSeqEnd = 1;
        break;

      case PatRdWrTA:
        break;

      case PatWrRdTA:
        SubSeqEnd = 7;
        break;

      case PatODTTA:
        SubSeqEnd = 3;
        break;

      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "SetupIOTest: Unknown value for Pattern\n");
        break;
    }
    ReutChSeqCfg.Data                             = 0;
    ReutChSeqCfg.Bits.Subsequence_Start_Pointer   = SubSeqStart;
    ReutChSeqCfg.Bits.Subsequence_End_Pointer     = SubSeqEnd;
    ReutChSeqCfg.Bits.Initialization_Mode         = REUT_Testing_Mode;
    ReutChSeqCfg.Bits.Global_Control              = 1;
    ReutChSeqCfg.Bits.Enable_Dummy_Reads          = MIN (
                                                      Outputs->EnDumRd,
                                                      MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_Enable_Dummy_Reads_MAX
                                                      );
    if (CmdPat == DimmTest) { // Inc address based on LC
      ReutChSeqCfg.Bits.Address_Update_Rate_Mode  = 1;
    }
    ReutChSeqCfg.Bits.Start_Test_Delay            = 2;

    Offset = MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_0_REG +
      (MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_0_REG) * Channel;
    MrcWriteCR (MrcData, Offset, LoopCountLinear);

    Offset = MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG +
      ((MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG) * Channel);
    MrcWriteCR64 (MrcData, Offset, ReutChSeqCfg.Data);
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SetupIOTest: C%d REUT_CH_SEQ_CFG_0 = 0x%X %X\n", Channel, ReutChSeqCfg.Data32[1], ReutChSeqCfg.Data32[0]);

    Offset = MCDFXS_CR_REUT_CH_SEQ_CTL_MCMAIN_0_REG +
      ((MCDFXS_CR_REUT_CH_SEQ_CTL_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CTL_MCMAIN_0_REG) * Channel);
    MrcWriteCR8 (MrcData, Offset, MCDFXS_CR_REUT_CH_SEQ_CTL_MCMAIN_0_Local_Clear_Errors_MSK);

    //###########################################################
    //
    // Program Sub Sequences
    //
    //###########################################################
    ReutSubSeqCtl0.Data                                     = 0;
    ReutSubSeqCtl0.Bits.Number_of_Cachelines                = NumCLCR;
    ReutSubSeqCtl0.Bits.Number_of_Cachelines_Scale          = NumCLCR >> 7;
    ReutSubSeqCtl0.Bits.Reset_Current_Base_Address_To_Start = 1;
    ReutSubSeqCtl0.Bits.Subsequence_Wait                    = SubSeqWait;

    ReutSubSeqCtl1.Data                            = ReutSubSeqCtl0.Data;
    ReutSubSeqCtl1.Bits.Number_of_Cachelines       = NumCL2CR;
    ReutSubSeqCtl1.Bits.Number_of_Cachelines_Scale = NumCL2CR >> 7;

    switch (CmdPat) {
      case PatWrRdTA:
        SubSeq.Ctl[0].Data                        = ReutSubSeqCtl0.Data;
        SubSeq.Ctl[0].Bits.Subsequence_Type       = BWr;         // Write CMD
        for (Index = 1; Index <= 6; Index++) {
          SubSeq.Ctl[Index].Data                  = ReutSubSeqCtl1.Data;
          SubSeq.Ctl[Index].Bits.Subsequence_Type = BRdWr;       // Read-Write CMD
        }
        SubSeq.Ctl[7].Data                        = ReutSubSeqCtl0.Data;
        SubSeq.Ctl[7].Bits.Subsequence_Type       = BRd;         // Read CMD
        SubSeq.ValidMask                          = 0xFF;
        break;

      case PatRdWrTA:
        SubSeq.Ctl[0].Data                        = ReutSubSeqCtl1.Data;
        SubSeq.Ctl[0].Bits.Subsequence_Type       = BWrRd;       // Write-Read CMD
        SubSeq.ValidMask                          = 0x01;
        break;

      case PatODTTA:
        SubSeq.Ctl[0].Data                        = ReutSubSeqCtl0.Data;
        SubSeq.Ctl[0].Bits.Subsequence_Type       = BWr;         // Write CMD

        SubSeq.Ctl[1].Data                        = ReutSubSeqCtl1.Data;
        SubSeq.Ctl[1].Bits.Subsequence_Type       = BRdWr;       // Read-Write CMD

        SubSeq.Ctl[2].Data                        = ReutSubSeqCtl0.Data;
        SubSeq.Ctl[2].Bits.Subsequence_Type       = BRd;         // Read CMD

        SubSeq.Ctl[3].Data                        = ReutSubSeqCtl1.Data;
        SubSeq.Ctl[3].Bits.Subsequence_Type       = BWrRd;       // Write-Read CMD

        SubSeq.ValidMask                          = 0x0F;
        break;

      default:
        SubSeq.Ctl[0].Data                        = ReutSubSeqCtl0.Data;
        SubSeq.Ctl[0].Bits.Subsequence_Type       = BWr;         // Write CMD

        SubSeq.Ctl[1].Data                        = ReutSubSeqCtl0.Data;
        SubSeq.Ctl[1].Bits.Subsequence_Type       = BRd;         // Read CMD

        SubSeq.ValidMask                          = 0x03;
        break;
    }
    Offset = MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_REG +
      ((MCDFXS_CR_REUT_CH1_SUBSEQ_CTL_MCMAIN_0_REG - MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_REG) * Channel);
    for (Index = 0; Index < 8; Index++) {
      if (SubSeq.ValidMask & (MRC_BIT0 << Index)) {
        MrcWriteCR (MrcData, Offset, SubSeq.Ctl[Index].Data);
        Offset += MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_1_REG - MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_REG;
      } else {
        break;
      }
    }

    //###########################################################
    //
    // Program Sequence Address
    //
    //###########################################################
    MrcProgramSequenceAddress (
      MrcData,
      Channel,
      REUTAddress->Start,
      REUTAddress->Stop,
      REUTAddress->Order,
      REUTAddress->IncRate,
      REUTAddress->IncVal,
      WrapCarryEn,
      WrapTriggerEn,
      AddrInvertEn,
      0,
      FALSE
      );

    //###########################################################
    //
    // Program Write Data Buffer Related Entries
    //
    //###########################################################
    ReutChPatWdbCl.Data                     = 0;
    ReutChPatWdbCl.Bits.WDB_End_Pointer     = WDBPattern->Stop;
    ReutChPatWdbCl.Bits.WDB_Start_Pointer   = WDBPattern->Start;
    ReutChPatWdbCl.Bits.WDB_Increment_Rate  = WDBPattern->IncRate;
    ReutChPatWdbCl.Bits.WDB_Increment_Scale = WDBPattern->IncRate >> MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_WID;
    Offset = MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_REG +
      ((MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_REG) * Channel);
    MrcWriteCR (MrcData, Offset, ReutChPatWdbCl.Data);

    ReutChPatWdbClMuxCfg.Data = 0;

    //
    // Enable LMN in either LMN mode or CADB -to create lots of supply noise
    //
    Mux0  = ((WDBPattern->DQPat == LMNVa) || (WDBPattern->DQPat == CADB)) ? LMNMode : LFSRMode;

    ReutChPatWdbClMuxCfg.Bits.ECC_Data_Source_Sel = 1;
    ReutChPatWdbClMuxCfg.Bits.Mux2_Control        = LFSRMode;
    ReutChPatWdbClMuxCfg.Bits.Mux1_Control        = LFSRMode;
    ReutChPatWdbClMuxCfg.Bits.Mux0_Control        = Mux0;      // ECC, Select LFSR
    ReutChPatWdbClMuxCfg.Bits.LFSR_Type           = 6;         // LFSR16
    //
    // Program LFSR Save/Restore.  Too complex unless everything is power of 2
    //
    if ((CmdPat == PatODTTA) || (CmdPat == PatWrRdTA)) {
      ReutChPatWdbClMuxCfg.Bits.Reload_LFSR_Seed_Rate = MIN (MrcLog2 (NumCL - 1) + 1, 7); // In Exponential mode MAX value is 7 (reload after 64 CLs)
      ReutChPatWdbClMuxCfg.Bits.Save_LFSR_Seed_Rate   = 1;
    }

    Offset = MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_REG +
      ((MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_REG) * Channel);
    MrcWriteCR (MrcData, Offset, ReutChPatWdbClMuxCfg.Data);

    //
    // Currently, not planning to use the Inversion Mask
    //
    Offset = MCHBAR_CH0_CR_REUT_CH_PAT_WDB_INV_REG + ((MCHBAR_CH1_CR_REUT_CH_PAT_WDB_INV_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_INV_REG) * Channel);
    MrcWriteCR (MrcData, Offset, 0);

    //###########################################################
    //
    // Program Error Checking
    //
    //###########################################################

    //
    // Enable selective_error_enable_chunk and selective_error_enable_cacheline, mask later
    // the bits we don't want to check.
    //
    Offset = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG +
      ((MCHBAR_CH1_CR_REUT_CH_ERR_CTL_REG - MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG) * Channel);
    ReutChErrCtrl.Data                                  = 0;
    ReutChErrCtrl.Bits.Stop_on_Nth_Error                = 1;
    ReutChErrCtrl.Bits.Stop_On_Error_Control            = SOE;
    ReutChErrCtrl.Bits.Selective_Error_Enable_Chunk     = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_Selective_Error_Enable_Chunk_MAX;
    ReutChErrCtrl.Bits.Selective_Error_Enable_Cacheline = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_Selective_Error_Enable_Cacheline_MAX;
    MrcWriteCR (MrcData, Offset, ReutChErrCtrl.Data);

    Offset = MCHBAR_CH0_CR_REUT_CH_ERR_DATA_MASK_REG +
      ((MCHBAR_CH1_CR_REUT_CH_ERR_DATA_MASK_REG - MCHBAR_CH0_CR_REUT_CH_ERR_DATA_MASK_REG) * Channel);
    MrcWriteCR64 (MrcData, Offset, 0);

    Offset = MCHBAR_CH0_CR_REUT_CH_ERR_ECC_MASK_REG +
      ((MCHBAR_CH1_CR_REUT_CH_ERR_ECC_MASK_REG - MCHBAR_CH0_CR_REUT_CH_ERR_ECC_MASK_REG) * Channel);
    MrcWriteCR8 (MrcData, Offset, 0);

    //###########################################################
    //
    // Program Dummy Read
    //
    //###########################################################
    if (Outputs->EnDumRd) {
      //
      // REUT traffic only uses BA[1:0] - Mask BANK that will not be used
      //
      Offset = MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_0_REG +
      (
        (MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_0_REG) *
        Channel
        );
      MrcWriteCR8 (MrcData, Offset, 0xFC);

      //
      // Rotated from 40nS to 200nS
      //
      if (Outputs->Qclkps > 0) {
        LMNFreq[0] = (40000 / Outputs->Qclkps);
        LMNFreq[1] = (200000 / Outputs->Qclkps);
      } else {
        LMNFreq[0] = LMNFreq[1] = 0xFF;
      }

      ReutChSeqDummyReadCtl.Data                        = 0;
      ReutChSeqDummyReadCtl.Bits.L_counter              = LMNFreq[0];
      ReutChSeqDummyReadCtl.Bits.M_counter              = LMNFreq[0];
      ReutChSeqDummyReadCtl.Bits.N_Counter              = LMNFreq[1];
      ReutChSeqDummyReadCtl.Bits.Enable_Sweep_Frequency = 1;
      //
      // Chirp Freq from 5 to 25 MHz
      //
      Offset =
        MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_0_REG +
          (
           (MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_0_REG) * Channel
          );
      MrcWriteCR (MrcData, Offset, ReutChSeqDummyReadCtl.Data);
    }
  }
  //
  // Always do a ZQ Short before the beginning of a test
  //
  MrcIssueZQ (MrcData, ChbitMask, MRC_ZQ_SHORT);

  return;
}

/**
  This function sets up a test with CADB for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
void
SetupIOTestCADB (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  )
{
  static const MRC_REUTAddress REUTAddress_8banks = {
    // Rank, Bank,  Row, Col
    {    0,  0,     0,    0 },  // Start
    {    0,  7,  2047, 1023 },  // Stop
    {    0,  0,     0,    0 },  // Order
    {   32,  3,     3,    0 },  // IncRate
    {    1,  1,    73,   53 }   // IncValue
  };
  static const MRC_REUTAddress REUTAddress_16banks = {
    // Rank, Bank,  Row, Col
    {    0,  0,     0,    0 },  // Start
    {    0, 15, 16383, 1023 },  // Stop: DDR4 has at least 14 Row bits and always 10 Column bits
    {    0,  0,     0,    0 },  // Order
    {   32,  3,     3,    0 },  // IncRate
    {    1,  1,    73,   53 }   // IncValue
  };
  const MRC_REUTAddress *ReutAddress;
  MRC_WDBPattern  WDBPattern;
  MrcOutput       *Outputs;
  UINT16          NumCL;

  Outputs            = &MrcData->Outputs;
  WDBPattern.IncRate = 4;
  WDBPattern.Start   = 0;
  WDBPattern.Stop    = 9;
  WDBPattern.DQPat   = CADB;

  if (Outputs->DdrType == MRC_DDR_TYPE_DDR4) {
    ReutAddress = &REUTAddress_16banks;  // 16 logical banks, will be mapped to 8 or 16 physical banks
  } else {
    ReutAddress = &REUTAddress_8banks;
  }

  NumCL = 128;

  SetupIOTest (MrcData, ChbitMask, PatWrRd, NumCL, LC, ReutAddress, SOE, &WDBPattern, EnCADB, EnCKE, 0);

  Outputs->DQPatLC = LC - 2 - 3 + 1;
  if (Outputs->DQPatLC < 1) {
    Outputs->DQPatLC = 1;
  }

  Outputs->DQPat = CADB;
  return;
}

/**
  This function sets up a basic victim-aggressor test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.
  @param[in]     Spread    - Stopping point of the pattern.

  @retval Nothing
**/
void
SetupIOTestBasicVA (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE,
  IN     const UINT32         Spread
  )
{
  static const MRC_REUTAddress REUTAddress = {
    // Rank, Bank, Row, Col
    {    0,  0,    0,    0 },  // Start
    {    0,  0,    0, 1023 },  // Stop
    {    0,  0,    0,    0 },  // Order
    {   32,  0,    0,    0 },  // IncRate
    {    1,  0,    0,    1 }   // IncValue
  };

  MRC_WDBPattern        WDBPattern;
  MrcOutput             *Outputs;
  UINT16                NumCL;

  Outputs            = &MrcData->Outputs;
  WDBPattern.IncRate = 4;
  WDBPattern.Start   = 0;
  WDBPattern.Stop    = Spread - 1;
  WDBPattern.DQPat   = BasicVA;

  NumCL = 128;

  SetupIOTest (MrcData, ChbitMask, PatWrRd, NumCL, LC, &REUTAddress, SOE, &WDBPattern, EnCADB, EnCKE, 0);

  Outputs->DQPatLC = LC - 8 + 1;
  if (Outputs->DQPatLC < 1) {
    Outputs->DQPatLC = 1;
  }

  Outputs->DQPat = BasicVA;
  return;
}

/**
  This function sets up a DQ test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
void
SetupIOTestDQ (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  )
{
  static const MRC_REUTAddress REUTAddress = {{0, 0, 0, 0},        // Start
  {0, 1, 512, 1023},   // Stop
  {0, 0, 0, 0},        // Order
  {2047, 255, 255, 0}, // IncRate
  {1, 1, 512, 1}};     // IncValue
  MRC_WDBPattern        WDBPattern;
  MrcOutput             *Outputs;
  UINT16                NumCL;

  Outputs            = &MrcData->Outputs;
  WDBPattern.IncRate = 32;
  WDBPattern.Start   = 0;
  WDBPattern.Stop    = 63;
  WDBPattern.DQPat   = SegmentWDB;

  NumCL = 256;

  SetupIOTest (MrcData, ChbitMask, PatWrRd, NumCL, LC, &REUTAddress, SOE, &WDBPattern, EnCADB, EnCKE, 0);

  Outputs->DQPatLC = LC - 8 - 3 + 1;
  if (Outputs->DQPatLC < 1) {
    Outputs->DQPatLC = 1;
  }

  Outputs->DQPat = SegmentWDB;
  return;
}

/**
  This function sets up a test with CADB for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
void
SetupIOTestC2C (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  )
{
  static const MRC_REUTAddress REUTAddress = {{0, 0, 0, 0},    // Start
  {0, 0, 0, 1023}, // Stop
  {0, 0, 0, 0},    // Order
  {2047, 0, 0, 0}, // IncRate
  {1, 0, 0, 1}};   // IncValue
  MRC_WDBPattern        WDBPattern;
  MrcOutput             *Outputs;

  Outputs            = &MrcData->Outputs;
  WDBPattern.IncRate = 32;
  WDBPattern.Start   = 0;
  WDBPattern.Stop    = 63;
  WDBPattern.DQPat   = SegmentWDB;

  SetupIOTest (MrcData, ChbitMask, PatWrRd, 32, LC, &REUTAddress, SOE, &WDBPattern, EnCADB, EnCKE, 0);

  Outputs->DQPatLC = LC - 5 + 1;
  if (Outputs->DQPatLC < 1) {
    Outputs->DQPatLC = 1;
  }

  Outputs->DQPat = SegmentWDB;
  return;
}

/**
  This function sets up a MPR test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
void
SetupIOTestMPR (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  )
{
#if (SUPPORT_DDR4 == SUPPORT)
  static const MRC_REUTAddress REUTAddress_ddr4 = {
    // Rank, Bank, Row, Col
    {    0,  0, 0, 0    }, // Start
    {    0,  1, 0, 0    }, // Stop
    {    0,  0, 0, 0    }, // Order
    {    0,  0, 0, 0    }, // IncRate
    {    0,  1, 0, 0    }  // IncValue
  };
#endif // SUPPORT_DDR4
  static const MRC_REUTAddress REUTAddress_ddr3 = {
    // Rank, Bank, Row, Col
    {    0,   0,    0,    0  }, // Start
    {    0,   0,    0, 1023  }, // Stop
    {    0,   0,    0,    0  }, // Order
    {   32,   0,    0,    0  }, // IncRate
    {    1,   0,    0,    1  }  // IncValue
  };
  static const MRC_REUTAddress REUTAddress_lpddr = {
    // Rank, Bank, Row, Col
    {    0,   4,    0,   0 },     // Start
    {    0,   4,    0,   0 },     // Stop
    {    0,   0,    0,   0 },     // Order
    {    0,   0,    0,   0 },     // IncRate
    {    0,   0,    0,   0 }      // IncValue
  };
  const MRC_REUTAddress *ReutAddress;
  MRC_WDBPattern        WDBPattern;
  MrcOutput             *Outputs;
  UINT16                NumCL;

  Outputs            = &MrcData->Outputs;
  WDBPattern.IncRate = 1;  // was 4 with HW ReadMPR algorithm
  WDBPattern.Start   = 0;
  WDBPattern.Stop    = 3;  // was 9 with HW ReadMPR algorithm
  WDBPattern.DQPat   = BasicVA;

  NumCL = 128;

  ReutAddress = &REUTAddress_ddr3;
  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3) {
    ReutAddress = &REUTAddress_lpddr;
  } else if (Outputs->DdrType == MRC_DDR_TYPE_DDR3) {
    ReutAddress = &REUTAddress_ddr3;
#if (SUPPORT_DDR4 == SUPPORT)
  } else {
    ReutAddress = &REUTAddress_ddr4;
#endif // SUPPORT_DDR4
  }

  SetupIOTest (MrcData, ChbitMask, PatRd, NumCL, LC, ReutAddress, SOE, &WDBPattern, EnCADB, EnCKE, 0);

  Outputs->DQPatLC = 1;
  Outputs->DQPat   = BasicVA;
  return;
}

/**
  Runs one or more REUT tests (based on TestType)

  @param[in] MrcData     - Include all MRC global data.
  @param[in] ChbitMask   - Channel Bit mask for which test should be setup for.
  @param[in] DQPat       - [0: BasicVA
                            1: SegmentWDB
                            2: CADB
                            3: TurnAround
                            4: LMNVa
                            5: TurnAroundWR
                            6: TurnAroundODT
                            7: RdRdTA]
  @param[in] SeqLCs      - An array of one or more loopcounts.
  @param[in] ClearErrors - Decision to clear or not errors.
  @param[in] ResetMode   - Parameter that specifies what training step we are running the reset in.

  @retval Returns ch errors
**/
UINT8
RunIOTest (
  IN MrcParameters *const MrcData,
  IN const UINT8          ChbitMask,
  IN const UINT8          DQPat,
  IN const UINT8 *const   SeqLCs,
  IN const UINT8          ClearErrors,
  IN const UINT16         ResetMode
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcIntOutput      *MrcIntData;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcIntControllerOut *IntControllerOut;
  UINT8             ch;
  UINT8             Reload;
  UINT8             NumTests;
  UINT8             t;
  UINT8             IncRate;
  UINT8             RankIncRate;
  UINT8             IncScale;
  UINT8             TestSOE;
  UINT8             TestDoneStatus;
  UINT8             ErrorStatus;
  UINT32            CRValue;
  UINT32            TestRand;
  UINT32            Offset;
  UINT32            LoopCountLinear;
  UINT8             tRDRD_dr_Min[MAX_CHANNEL];
  UINT8             tRDRD_sg_Min[MAX_CHANNEL];
  UINT8             tRDRD_dg_Min[MAX_CHANNEL];
  UINT8             TurnAroundOffset;
  UINT8             BankStart;
  UINT8             BankStop;
  BOOLEAN           Ddr4;
  static const UINT8  BankSW[2][4] = {
    {0, 0x4, 1, 0x5}, // Start
    {3, 0xB, 4, 0xC}  // Wrap
    }; // Bank [Start/Wrap][Test Num]

  // When we segment the WDB, we run a normal 2 LFSR VA pattern on the first 10 entries
  // The last 54 entries are used for a more complex 3 LFSR pattern
  // In this mode:
  // SeqLC is usually [0: host.DQPatLC, 1: host.DQPatLC, 2: host.DQPatLC+4, 3: host.DQPatLC+2]
  //
  // Anotherwords:
  // The first 10 entries of the LFSR are run for twice, each for 2^DQPatLC
  //   and the WDB is incremented every 25 cachelines
  //
  // 25 was chosen since 10 Entry * 25 cachelines = 250.
  // This is pretty close to 256, a power of 2, which should be roughly uniform coverage across all entries
  //
  // The second 54 entries of the LFSR are run twice
  //            Once with 2^(DQPatLC+4) and the WDB is incremented every 19 cachelines
  //            Once with 2^(DQPatLC+2) and the WDB is incremented every 10 cachelines
  //            Again, 19*54 = 1026 and 10*54 = 540 and both of these numbers are close
  //             to power of 2 and will provide roughly uniform coverage
  //
  // Each entry in the first 10 entries is hit 2 ^ (DQPatLC + NumCachelines + 1) / 10
  //           or 2 ^ (DQPatLC + NumCachelines -2.32)
  //
  // Each entry in the second 54 entries is hit 2 ^ (DQPatLC + NumCachelines + 4.32) / 54
  //           or ~2 ^ (DQPatLC + NumCachelines -1.43)
  //           or ~2x more than the first 10 entries

  UINT8 WDBIncRates[8];
  UINT8 WDBStart[8];
  UINT8 WDBStop[8];

  MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_STRUCT                 ReutGlobalCtl;
  MCDFXS_CR_REUT_GLOBAL_ERR_MCMAIN_STRUCT                 ReutGlobalErr;
  MCHBAR_CH0_CR_REUT_CH_ERR_CTL_STRUCT                    ReutChErrCtl;
  MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_STRUCT            ReutChPatWdbCl;
  MCHBAR_CH0_CR_TC_RDRD_STRUCT                            TcRdRd[MAX_CHANNEL];
  MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_0_STRUCT ReutChSeqBaseAddrIncCtl;
  MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_STRUCT   ReutChSeqBaseAddrStart;
  MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_STRUCT    ReutChSeqBaseAddrWrap;

  TestSOE       = 0;
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  MrcIntData       = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntControllerOut = &MrcIntData->Controller[0];
  MrcCall->MrcSetMem (WDBIncRates, sizeof (WDBIncRates), 1);
  MrcCall->MrcSetMem (WDBStart, sizeof (WDBStart), 0);
  MrcCall->MrcSetMem (WDBStop, sizeof (WDBStop), 9);
  MrcCall->MrcSetMem (tRDRD_dr_Min, sizeof (tRDRD_dr_Min), 0);
  MrcCall->MrcSetMem (tRDRD_sg_Min, sizeof (tRDRD_sg_Min), 0);
  MrcCall->MrcSetMem (tRDRD_dg_Min, sizeof (tRDRD_dg_Min), 0);
  MrcCall->MrcSetMemDword ((UINT32 *) TcRdRd, sizeof (TcRdRd) / sizeof (TcRdRd[0]), 0);
  ReutGlobalErr.Data  = 0;
  ErrorStatus         = 0;
  Ddr4 = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  TestRand     = 0xBAD00451;
  NumTests     = 1;
  if (DQPat == SegmentWDB) {
    NumTests = 4;
    WDBIncRates[3] = 10;
    WDBIncRates[2] = 19;
    WDBIncRates[1] = 25;
    WDBIncRates[0] = 25;

    WDBStart[3]    = 10;
    WDBStart[2]    = 10;
    WDBStop[3]     = 63;
    WDBStop[2]     = 63;
  } else if (DQPat == CADB) {
    NumTests = 7;
  } else if ((DQPat == TurnAroundWR) || (DQPat == TurnAroundWR_DG) || (DQPat == TurnAroundWR_SG)) {
    NumTests = 8;
  } else if (DQPat == TurnAroundODT) {
    NumTests = 4;
  } else if (DQPat == RdRdTA) {
    NumTests = 2;
    for (ch = 0; ch < MAX_CHANNEL; ch++) {
      if (!((MRC_BIT0 << ch) & ChbitMask)) {
        continue;
      }

      TcRdRd[ch] = IntControllerOut->Channel[ch].MchbarTcRdRd;
      tRDRD_sg_Min[ch] = (UINT8) TcRdRd[ch].Bits.tRDRD_sg; // save the min value allowed
      tRDRD_dg_Min[ch] = (UINT8) TcRdRd[ch].Bits.tRDRD_dg; // save the min value allowed
    }
  } else if (DQPat == RdRdTA_All) {
    NumTests = 8;
    for (ch = 0; ch < MAX_CHANNEL; ch++) {
      if (((1 << ch) & ChbitMask) == 0) {
        continue;
      }

      TcRdRd[ch] = IntControllerOut->Channel[ch].MchbarTcRdRd;
      tRDRD_dr_Min[ch] = (UINT8) TcRdRd[ch].Bits.tRDRD_dr; // save the min value allowed
      tRDRD_sg_Min[ch] = (UINT8) TcRdRd[ch].Bits.tRDRD_sg; // save the min value allowed
      tRDRD_dg_Min[ch] = (UINT8) TcRdRd[ch].Bits.tRDRD_dg; // save the min value allowed
    }
  } else if ((DQPat == TurnAroundRW_DG) || (DQPat == TurnAroundRW_SG)) {
    for (ch = 0; ch < MAX_CHANNEL; ch++) {
      if (!((MRC_BIT0 << ch) & ChbitMask)) {
        continue;
      }
      //
      // Program Start/Stop per SSQ for Bank addressing
      //
      Offset = OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_1_REG, ch);
      ReutChSeqBaseAddrStart.Data = MrcReadCR64 (MrcData, Offset);
      ReutChSeqBaseAddrStart.Bits.Bank_Address = BankSW[0][3];
      MrcWriteCR64 (MrcData, Offset, ReutChSeqBaseAddrStart.Data);

      Offset = OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_1_REG, ch);
      ReutChSeqBaseAddrWrap.Data = MrcReadCR64 (MrcData, Offset);
      ReutChSeqBaseAddrWrap.Bits.Bank_Address = BankSW[1][3];
      MrcWriteCR64 (MrcData, Offset, ReutChSeqBaseAddrWrap.Data);
    }
  }

  for (t = 0; t < NumTests; t++) {
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RunIOTest: t = %d\n",t);
    Reload = MrcLog2 (WDBIncRates[t] - 1);

    if (WDBIncRates[t] > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_MAX) {
      WDBIncRates[t] = Reload;   // Have to use the exponential IncRate
    } else {
      WDBIncRates[t] |= (1 << MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_WID);  // Linear IncRate
    }

    for (ch = 0; ch < MAX_CHANNEL; ch++) {
      if (!((MRC_BIT0 << ch) & ChbitMask)) {
        continue;
      }
      //
      // Check for SOE == NTHSOE, ALSOE
      // @todo: I still feel we need to exit if we get  errors on any test
      //
      TestSOE = 0;
      Offset = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG +
        ((MCHBAR_CH1_CR_REUT_CH_ERR_CTL_REG - MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG) * ch);
      ReutChErrCtl.Data = MrcReadCR (MrcData, Offset);
      CRValue = ReutChErrCtl.Bits.Stop_On_Error_Control;
      if ((CRValue == NTHSOE) || (CRValue == ALSOE)) {
        TestSOE = 1; // SOE bits are set
      }

      if (DQPat == SegmentWDB) {
        Offset = MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_REG +
          ((MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_REG) * ch);
        ReutChPatWdbCl.Data                     = 0;
        ReutChPatWdbCl.Bits.WDB_Start_Pointer   = WDBStart[t];
        ReutChPatWdbCl.Bits.WDB_End_Pointer     = WDBStop[t];
        ReutChPatWdbCl.Bits.WDB_Increment_Rate  = WDBIncRates[t];
        ReutChPatWdbCl.Bits.WDB_Increment_Scale = WDBIncRates[t] >> MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_WID;
        MrcWriteCR (MrcData, Offset, ReutChPatWdbCl.Data);

        //
        // Skip programming LFSR Save/Restore.  Too complex unless power of 2
        //

        //
        // Program desired loopcount
        //
        LoopCountLinear = 1 << SeqLCs[t];
        Offset = MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_0_REG +
          (MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_0_REG) * ch;
        MrcWriteCR (MrcData, Offset, LoopCountLinear);

      } else if (DQPat == CADB) {
        SetupCADB (MrcData, ch, NumTests, t, 0);   // LMNEn=0
      } else if ((DQPat == TurnAroundWR) || (DQPat == TurnAroundWR_DG) || (DQPat == TurnAroundWR_SG) || (DQPat == TurnAroundODT)) {
        //
        // Program which subseq to run
        //
        Offset = MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG + 3 +
          ((MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG) * ch);
        MrcWriteCR8 (MrcData, Offset, (t << 4) + t);

        //
        // Program RankInc Rate
        //
        IncRate =
          (
           (((DQPat == TurnAroundWR) || (DQPat == TurnAroundWR_DG) || (DQPat == TurnAroundWR_SG)) && ((t == 0) || (t == 7))) ||
           ((DQPat == TurnAroundODT) && ((t == 0) || (t == 2)))
          ) ? 0 : 1;
        if ((DQPat == TurnAroundWR_DG) || (DQPat == TurnAroundWR_SG)) {
          // idea is to check all ranks but still not TAT between them
          RankIncRate = IncRate + 5;
          IncScale = 0;
        } else {
          RankIncRate = IncRate;
          IncScale = 1;
        }
        Offset = OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_1_REG, ch);
        ReutChSeqBaseAddrIncCtl.Data = MrcReadCR64 (MrcData, Offset);
        ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Update_Scale = IncScale;
        ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Update_Rate = RankIncRate;
        ReutChSeqBaseAddrIncCtl.Bits.Row_Base_Address_Increment = 1;
        ReutChSeqBaseAddrIncCtl.Bits.Row_Base_Address_Update_Rate = 7 + IncRate;
        ReutChSeqBaseAddrIncCtl.Bits.Row_Base_Address_Update_Scale = 0;
        ReutChSeqBaseAddrIncCtl.Bits.Column_Base_Address_Update_Scale = 1;
        ReutChSeqBaseAddrIncCtl.Bits.Column_Base_Address_Update_Rate = IncRate;
        MrcWriteCR64 (MrcData, Offset, ReutChSeqBaseAddrIncCtl.Data);

        if (DQPat == TurnAroundWR_DG) {
          //
          // Program Start/Stop per SSQ for Bank addressing
          //
          if (t == 0) {
            BankStart = BankSW[0][2];
            BankStop  = BankSW[1][2];
          } else if (t == 7) {
            BankStart = BankSW[0][2];
            BankStop  = BankSW[1][2];
          } else {
            BankStart = BankSW[0][3];
            BankStop  = BankSW[1][3];
          }

          Offset = OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_1_REG, ch);
          ReutChSeqBaseAddrStart.Data = MrcReadCR64 (MrcData, Offset);
          ReutChSeqBaseAddrStart.Bits.Bank_Address = BankStart;
          MrcWriteCR64 (MrcData, Offset, ReutChSeqBaseAddrStart.Data);

          Offset = OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_1_REG, ch);
          ReutChSeqBaseAddrWrap.Data = MrcReadCR64 (MrcData, Offset);
          ReutChSeqBaseAddrWrap.Bits.Bank_Address = BankStop;
          MrcWriteCR64 (MrcData, Offset, ReutChSeqBaseAddrWrap.Data);
        }

        if (Ddr4 && (DQPat == TurnAroundODT)) {
          //
          // Program Start/Stop per SSQ for Bank addressing
          //
          Offset = OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_1_REG, ch);
          ReutChSeqBaseAddrStart.Data = MrcReadCR64 (MrcData, Offset);
          ReutChSeqBaseAddrStart.Bits.Bank_Address = BankSW[0][t];
          MrcWriteCR64 (MrcData, Offset, ReutChSeqBaseAddrStart.Data);

          Offset = OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_1_REG, ch);
          ReutChSeqBaseAddrWrap.Data = MrcReadCR64 (MrcData, Offset);
          ReutChSeqBaseAddrWrap.Bits.Bank_Address = BankSW[1][t];
          MrcWriteCR64 (MrcData, Offset, ReutChSeqBaseAddrWrap.Data);
        }
      } else if (DQPat == RdRdTA) {
        //
        // Program tRDRD parameter
        //
        Offset = MCHBAR_CH0_CR_TC_RDRD_REG + (MCHBAR_CH1_CR_TC_RDRD_REG - MCHBAR_CH0_CR_TC_RDRD_REG) * ch;
        TcRdRd[ch].Bits.tRDRD_sg = tRDRD_sg_Min[ch] + t;
        TcRdRd[ch].Bits.tRDRD_dg = tRDRD_dg_Min[ch] + t;
        MrcWriteCR (MrcData, Offset, TcRdRd[ch].Data);
      } else if (DQPat == RdRdTA_All) {
        //
        // Program tRDRD for SR and DR
        //  Run 8 tests, Covering tRDRD_sr = 4,5,6,7 and tRDRD_dr = Min,+1,+2,+3
        //
        TurnAroundOffset = (t % 4);
        Offset = MCHBAR_CH0_CR_TC_RDRD_REG + (MCHBAR_CH1_CR_TC_RDRD_REG - MCHBAR_CH0_CR_TC_RDRD_REG) * ch;
        TcRdRd[ch].Bits.tRDRD_sg = tRDRD_sg_Min[ch] + TurnAroundOffset;
        TcRdRd[ch].Bits.tRDRD_dg = tRDRD_dg_Min[ch] + TurnAroundOffset;
        TcRdRd[ch].Bits.tRDRD_dr = tRDRD_dr_Min[ch] + TurnAroundOffset;

        MrcWriteCR (MrcData, Offset, TcRdRd[ch].Data);
        //
        // Program RankInc Rate
        //
        IncRate = (t > 3)? 0 : 31; // this field + 1

        Offset = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_0_REG +
          (
           (
            MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_0_REG
           ) * ch
          );
        ReutChSeqBaseAddrIncCtl.Data = MrcReadCR64 (MrcData, Offset);
        ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Update_Scale = 1;
        ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Update_Rate = IncRate;
        MrcWriteCR64 (MrcData, Offset, ReutChSeqBaseAddrIncCtl.Data);
      }
    }

    //###########################################################
    //
    // Start Test and Poll on completion
    //
    //###########################################################
    //
    // IO Reset neded before starting test.
    //
    if (ResetMode == 0) {
      IoReset (MrcData);
    } else {
      MrcIoReset (MrcData, ResetMode);
    }

    ReutGlobalCtl.Data                    = 0;
    ReutGlobalCtl.Bits.Global_Start_Test  = 1;
    if (ClearErrors && (t == 0)) {
      ReutGlobalCtl.Bits.Global_Clear_Errors = 1;
    }

    MrcWriteCR (MrcData, MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG, ReutGlobalCtl.Data);

    //
    // Wait until Channel test done status matches ChbitMask
    //
    do {
      ReutGlobalErr.Data = MrcReadCR (MrcData, MCDFXS_CR_REUT_GLOBAL_ERR_MCMAIN_REG);
      TestDoneStatus = (UINT8) ((ReutGlobalErr.Bits.Channel_Test_Done_Status_1 << 1) | ReutGlobalErr.Bits.Channel_Test_Done_Status_0);
    } while ((TestDoneStatus & ChbitMask) != ChbitMask);

    //
    // Exit if SOE and Channel_Test_Done_Status bits matches ChbitMask
    //
    ErrorStatus = (UINT8) ((ReutGlobalErr.Bits.Channel_Error_Status_1 << 1) | ReutGlobalErr.Bits.Channel_Error_Status_0);
    if ((ErrorStatus & ChbitMask) && TestSOE) {
      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ERROR IN RunIOTest: REUT_GLOBAL_CTRL = %Xh, REUT_GLOBAL_ERR %Xh\n", ReutGlobalErr.Data, ErrorStatus);
      return (ReutGlobalErr.Data & ChbitMask);
    }
  }

  if ((DQPat == RdRdTA) || (DQPat == RdRdTA_All)) {
    //
    // Restore original tRDRD value
    //
    for (ch = 0; ch < MAX_CHANNEL; ch++) {
      if (!((MRC_BIT0 << ch) & ChbitMask)) {
        continue;
      }

      Offset = MCHBAR_CH0_CR_TC_RDRD_REG + (MCHBAR_CH1_CR_TC_RDRD_REG - MCHBAR_CH0_CR_TC_RDRD_REG) * ch;
      MrcWriteCR (MrcData, Offset, IntControllerOut->Channel[ch].MchbarTcRdRd.Data);
    }
  }

  return (ReutGlobalErr.Data & ChbitMask);
}

/**
  Programs REUT to run on the selected physical ranks.

  @param[in] MrcData           - Pointer to MRC global data.
  @param[in] ch                - Channel to enable.
  @param[in] RankBitMask       - Bit mask of ranks to enable.
  @param[in] RankFeatureEnable - RankFeatureEnable is a bit mask that can enable CKE, Refresh or ZQ
                                 RankFeatureEnable[0] enables Refresh on all non-selected ranks
                                 RankFeatureEnable[1] enables Refresh on all ranks
                                 RankFeatureEnable[2] enables ZQ on all non-selected ranks
                                 RankFeatureEnable[3] enables ZQ on all ranks
                                 RankFeatureEnable[4] enables CKE on all non-selected ranks
                                 RankFeatureEnable[5] enables CKE on all ranks

  @retval Bit mask of channel enabled if rank in the channel exists.
**/
UINT8
SelectReutRanks (
  IN MrcParameters *const MrcData,
  IN const UINT8          ch,
  IN UINT8                RankBitMask,
  IN const UINT8          RankFeatureEnable
  )
{
  const MrcInput     *Inputs;
  const MRC_FUNCTION *MrcCall;
  UINT32 Offset;
  UINT8 En;
  UINT8 rank;
  UINT8 RankCount;
  MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT       ReutChSeqCfg;
  MCHBAR_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_STRUCT  ReutChMiscRefreshCtrl;
  MCHBAR_CH0_CR_REUT_CH_MISC_ZQ_CTRL_STRUCT       ReutChMiscZqCtrl;
  MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_STRUCT      ReutChMiscCkeCtrl;
  MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_STRUCT  ReutChSeqRankL2PMapping;
  MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_STRUCT    ReutChSeqBaseAddrWrap;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;

  //
  // Make sure valid rank bit mask for this channel
  //
  RankBitMask &= MrcData->Outputs.Controller[0].Channel[ch].ValidRankBitMask;

  //
  // Check if nothing is selected
  //
  if ((RankBitMask & 0xF) == 0) {
    Offset = MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG +
      (
       (
        MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG -
        MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG
       ) * ch
      );
    MrcWriteCR (MrcData, Offset, 0);

    //
    // Disable Channel by clearing global start bit in change config
    //
    Offset = MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG +
      ((MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG) * ch);
    ReutChSeqCfg.Data                 = MrcReadCR (MrcData, Offset);
    ReutChSeqCfg.Bits.Global_Control  = 0;
    MrcWriteCR (MrcData, Offset, (UINT32) ReutChSeqCfg.Data);

    return 0;

  } else {
    //
    // Normal case
    // Setup REUT Test to iteration through appropriate ranks during test
    //
    ReutChSeqRankL2PMapping.Data  = 0;
    RankCount                     = 0;

    //
    // Prepare Rank Mapping and Max Rank
    //
    for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
      //
      // rank in range(4):
      //
      if ((MRC_BIT0 << rank) & RankBitMask) {
        ReutChSeqRankL2PMapping.Data |= (rank << (4 * RankCount));
        RankCount += 1;
      }
    }
    //
    // Write New Rank Mapping and Max Rank
    //
    Offset = MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG +
      (
       (
        MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG -
        MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG
       ) * ch
      );
    MrcWriteCR (MrcData, Offset, ReutChSeqRankL2PMapping.Data);
    Offset = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_REG +
      ((MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_REG) * ch);
    ReutChSeqBaseAddrWrap.Data = MrcReadCR64 (MrcData, Offset);
    // ReutChSeqBaseAddrWrap.Bits.Rank_Address = RankCount - 1; // Causes 64-bit shifts in MS compiler
    ReutChSeqBaseAddrWrap.Data &= ~MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_Rank_Address_MSK;
    ReutChSeqBaseAddrWrap.Data |= MrcCall->MrcLeftShift64 (RankCount - 1, MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_Rank_Address_OFF);
    MrcWriteCR64 (MrcData, Offset, ReutChSeqBaseAddrWrap.Data);

    //
    // Make sure channel is enabled
    //
    Offset = MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG + ((MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG) * ch);
    ReutChSeqCfg.Data                 = MrcReadCR (MrcData, Offset);
    ReutChSeqCfg.Bits.Global_Control  = 1;
    MrcWriteCR (MrcData, Offset, (UINT32) ReutChSeqCfg.Data);
  }
  //
  // Need to convert RankFeatureEnable as an input parameter so we don't pass it all the time
  //
  if (RankFeatureEnable != 0) {
    //
    // Enable Refresh and ZQ - 0's to the the desired ranks
    //
    En = RankFeatureEnable & 0x3; // Refresh
    ReutChMiscRefreshCtrl.Data                    = 0;
    ReutChMiscRefreshCtrl.Bits.Refresh_Rank_Mask  = MCHBAR_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_MAX;
    ReutChMiscRefreshCtrl.Bits.Panic_Refresh_Only = 1;

    if (En == 1) {
      ReutChMiscRefreshCtrl.Bits.Refresh_Rank_Mask = ~RankBitMask; // Enable all non-selected ranks
    } else if (En > 1) {
      ReutChMiscRefreshCtrl.Bits.Refresh_Rank_Mask = 0;           // Enable all ranks
    }
    Offset = MCHBAR_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG +
      ((MCHBAR_CH1_CR_REUT_CH_MISC_REFRESH_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG) * ch);
    MrcWriteCR (MrcData, Offset, ReutChMiscRefreshCtrl.Data);

    En = (RankFeatureEnable >> 2) & 0x3; // ZQ
    ReutChMiscZqCtrl.Data              = 0;
    ReutChMiscZqCtrl.Bits.ZQ_Rank_Mask = MCHBAR_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_MAX;
    ReutChMiscZqCtrl.Bits.Always_Do_ZQ = 1;
    if (En == 1) {
      ReutChMiscZqCtrl.Bits.ZQ_Rank_Mask = ~RankBitMask;
    } else if (En > 1) {
      ReutChMiscZqCtrl.Bits.ZQ_Rank_Mask = 0; // Enable all ranks
    }
    Offset =  MCHBAR_CH0_CR_REUT_CH_MISC_ZQ_CTRL_REG +
      ((MCHBAR_CH1_CR_REUT_CH_MISC_ZQ_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_ZQ_CTRL_REG) * ch);
    MrcWriteCR (MrcData, Offset, ReutChMiscZqCtrl.Data);

    //
    // Enable CKE ranks - 1's to enable desired ranks
    //
    En = (RankFeatureEnable >> 4) & 0x3;
    ReutChMiscCkeCtrl.Data        = 0;
    ReutChMiscCkeCtrl.Bits.CKE_On = MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_On_MAX;
    if (En == 1) {
      ReutChMiscCkeCtrl.Bits.CKE_On       = ~RankBitMask;
      ReutChMiscCkeCtrl.Bits.CKE_Override = ~RankBitMask; // Enable all non-selected ranks
    } else if (En > 1) {
      ReutChMiscCkeCtrl.Bits.CKE_On       = MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_On_MAX;
      ReutChMiscCkeCtrl.Bits.CKE_Override = MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_MAX; // Enable all ranks.
    }
    Offset = MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG +
      ((MCHBAR_CH1_CR_REUT_CH_MISC_CKE_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG) * ch);
    MrcWriteCR (MrcData, Offset, ReutChMiscCkeCtrl.Data);
  }

  return (UINT8) (MRC_BIT0 << ch);
}

/**
  This routine updates RXTRAINRANK values and downloads the new
  values from the Register File to the pads.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Defines channel to update
  @param[in] Rank     - Defines rank to update
  @param[in] Byte     - Defines byte to update
  @param[in] Subfield - Defines the register's field or fields to update
  @param[in] Value    - value to be writen into register fields

  @retval Nothing
**/
void
UpdateRxT (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          Rank,
  IN const UINT8          Byte,
  IN const UINT8          Subfield,
  IN const UINT16         Value
  )
{
  UpdateRxTValues (MrcData, Channel, Rank, Byte, Subfield, Value);

  //
  // Download new settings from the RegFile to the Pads
  //
  MrcDownloadRegFile (MrcData, Channel, 0, Rank, MrcRegFileRank, Byte, 1, 0);
  return;
}

/**
  This routine updates RXTRAINRANK register's specific fields defined by the subfield
  subfield values:
    0 - Update RcvEn   - leave other parameter the same
    1 - Update RxDqsP  - leave other parameter the same
    2 - Update RxEq    - leave other parameter the same
    3 - Update RxDqsN  - leave other parameter the same
    4 - Update RxVref  - leave other parameter the same
    5 - Update RxDqsP & RxDqsN - leave other parameter the same
    FF - leave all parameter the same

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Defines channel to update
  @param[in] Rank     - Defines rank to update
  @param[in] Byte     - Defines byte to update
  @param[in] Subfield - Defines the register's field or fields to update
  @param[in] Value    - value to be writen into register fields

  @retval Nothing
**/
void
UpdateRxTValues (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          Rank,
  IN const UINT8          Byte,
  IN const UINT8          Subfield,
  IN const UINT16         Value
  )
{
  MrcChannelOut                       *ChannelOut;
  UINT32                              Offset;
  DDRDATA0CH0_CR_RXTRAINRANK0_STRUCT  CrRxTrainRank;

  ChannelOut                   = &MrcData->Outputs.Controller[0].Channel[Channel];
  CrRxTrainRank.Data           = 0;
  CrRxTrainRank.Bits.RxRcvEnPi = (Subfield == 0) ? Value : ChannelOut->RcvEn[Rank][Byte];
  CrRxTrainRank.Bits.RxDqsPPi  = ((Subfield == 1) || (Subfield == 5)) ? Value : ChannelOut->RxDqsP[Rank][Byte];
  CrRxTrainRank.Bits.RxEq      = (Subfield == 2) ? Value : ChannelOut->RxEq[Rank][Byte];
  CrRxTrainRank.Bits.RxDqsNPi  = ((Subfield == 3) || (Subfield == 5)) ? Value : ChannelOut->RxDqsN[Rank][Byte];
  CrRxTrainRank.Bits.RxVref    = (Subfield == 4) ? Value : ChannelOut->RxVref[Byte];

  Offset = DDRDATA0CH0_CR_RXTRAINRANK0_REG +
    ((DDRDATA0CH1_CR_RXTRAINRANK0_REG - DDRDATA0CH0_CR_RXTRAINRANK0_REG) * Channel) +
    ((DDRDATA0CH0_CR_RXTRAINRANK1_REG - DDRDATA0CH0_CR_RXTRAINRANK0_REG) * Rank) +
    ((DDRDATA1CH0_CR_RXTRAINRANK0_REG - DDRDATA0CH0_CR_RXTRAINRANK0_REG) * Byte);
  MrcWriteCR (MrcData, Offset, CrRxTrainRank.Data);
}

/**
  This routine updates TXTRAINRANK values and downloads the new
  values from the Register File to the pads.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Defines channel to update
  @param[in] Rank     - Defines rank to update
  @param[in] Byte     - Defines byte to update
  @param[in] Subfield - Defines the register's field or fields to update
  @param[in] Value    - value to be writen into register fields

  @retval Nothing
**/
void
UpdateTxT (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          Rank,
  IN const UINT8          Byte,
  IN const UINT8          Subfield,
  IN const UINT32         Value
  )
{
  UpdateTxTValues (MrcData, Channel, Rank, Byte, Subfield, Value);

  // Download new settings from the RegFile to the Pads
  //
  MrcDownloadRegFile (MrcData, Channel, 0, Rank, MrcRegFileRank, Byte, 0, 1);
  return;
}

/**
  This routine updates TXTRAINRANK register's specific fields defined by the subfield
  subfield values:
    0 - Update TxDq    - leave other parameter the same
    1 - Update TxDqs   - leave other parameter the same
    2 - Update TxEq    - leave other parameter the same
    3 - Update ALL from input value (non from Mrcdata structure)

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Defines channel to update
  @param[in] Rank     - Defines rank to update
  @param[in] Byte     - Defines byte to update
  @param[in] Subfield - Defines the register's field or fields to update
  @param[in] Value    - value to be writen into register fields

  @retval Nothing
**/
void
UpdateTxTValues (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          Rank,
  IN const UINT8          Byte,
  IN const UINT8          Subfield,
  IN const UINT32         Value
  )
{
  MrcChannelOut                       *ChannelOut;
  UINT32                              Offset;
  DDRDATA0CH0_CR_TXTRAINRANK0_STRUCT  CrTxTrainRank;

  ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
  if (Subfield == 3) {
    CrTxTrainRank.Data = Value;
  } else {
    CrTxTrainRank.Data                = 0;
    CrTxTrainRank.Bits.TxDqDelay      = (Subfield == 0) ? Value : ChannelOut->TxDq[Rank][Byte];
    CrTxTrainRank.Bits.TxDqsDelay     = (Subfield == 1) ? Value : ChannelOut->TxDqs[Rank][Byte];
    CrTxTrainRank.Bits.TxEqualization = (Subfield == 2) ? Value : ChannelOut->TxEq[Rank][Byte];
  }

  Offset = DDRDATA0CH0_CR_TXTRAINRANK0_REG +
    ((DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Channel) +
    ((DDRDATA0CH0_CR_TXTRAINRANK1_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Rank) +
    ((DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Byte);
  MrcWriteCR (MrcData, Offset, CrTxTrainRank.Data);
}

/**
  Returns the index into the array MarginResult in the MrcOutput structure.

  @param[in] ParamV - Margin parameter

  @retval One of the following values: LastRxV(0), LastRxT (1), LastTxV(2), LastTxT (3), LastRcvEna (4),
                                       LastWrLevel (5), LastCmdT (6), LastCmdV (7)
**/
UINT8
GetMarginResultType (
  IN const UINT8 ParamV
  )
{
  switch (ParamV) {
    case WrV:
    case WrFan2:
    case WrFan3:
      return LastTxV;

    case WrT:
      return LastTxT;

    case RdV:
    case RdFan2:
    case RdFan3:
      return LastRxV;

    case RdT:
      return LastRxT;

    case RcvEna:
    case RcvEnaX:
      return LastRcvEna;

    case WrLevel:
      return LastWrLevel;

    case CmdT:
      return LastCmdT;

    case CmdV:
      return LastCmdV;

    default:
      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "GetMarginByte: Unknown Margin Parameter\n");
      break;
  }

  return 0; // Return LastRxV to point to the beginning of the array
}

/*
1D Margin Types:
RcvEn:   Shifts just RcvEn.  Only side effect is it may eat into read dq-dqs for first bit of burst
RdT:     Shifts read DQS timing, changing where DQ is sampled
WrT:     Shifts write DQ timing, margining DQ-DQS timing
WrDqsT:  Shifts write DQS timing, margining both DQ-DQS and DQS-CLK timing
RdV:     Shifts read Vref voltage for DQ only
WrV:     Shifts write Vref voltage for DQ only
WrLevel: Shifts write DQ and DQS timing, margining only DQS-CLK timing
WrTBit:  Shifts write DQ per bit timing.
RdTBit:  Shifts read DQ per bit timing.
RdVBit:  Shifts read DQ per bit voltage.

2D Margin Types (Voltage, Time)
RdFan2:  Margins both RdV and RdT at { (off, -2/3*off),  (off, 2/3*off) }
WrFan2:  Margins both WrV and WrT at { (off, -2/3*off),  (off, 2/3*off) }
RdFan3:  Margins both RdV and RdT at { (off, -2/3*off),  (5/4*off, 0),  (off, 2/3*off)  }
WrFan3:  Margins both WrV and WrT at { (off, -2/3*off),  (5/4*off, 0),  (off, 2/3*off)  }
*/
/**
  This function Reads MrcData structure and finds the minimum last recorded margin for param
  Searches across all bytes and ranks in RankMask

  @param[in]     MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Data structure with the latest margin results.
  @param[in]     Param           - Defines the margin type
  @param[in]     Ranks           - Condenses down the results from multiple ranks
  @param[in]     ResultRank      - This rank will keep the results from multiple ranks

  @retval mrcWrongInputParameter if a bad Param is passed in, otherwise mrcSuccess.
**/
MrcStatus
GetMarginCh (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          Ranks,
  IN     const UINT8          ResultRank
  )
{
  MrcOutput *Outputs;
  UINT32    *Margin1;
  UINT32    *Margin2;
  UINT8     ResultType;
  UINT8     Channel;
  UINT8     Rank;
  UINT8     Byte;
  UINT8     Edge;
  UINT8     Scale;

  Outputs = &MrcData->Outputs;
  switch (Param) {
    case WrV:
    case WrT:
    case RdV:
    case RdT:
      Scale = 10;
      break;

    case WrFan2:
    case WrFan3:
    case RdFan2:
    case RdFan3:
      Scale = 21 / 3;
      break;

    default:
      MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "GetMarginCh: Unknown Margin Parameter\n");
      return mrcWrongInputParameter;
  }

  ResultType = GetMarginResultType (Param);
  ResultType = MIN (MAX_RESULT_TYPE - 1, ResultType);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      Margin2 = &MarginResult[ResultType][ResultRank][Channel][0][0];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
            continue;
          }
          if ((1 << Rank) & Ranks) {
            Margin1 = &MarginResult[ResultType][Rank][Channel][Byte][0];
            for (Edge = 0; Edge < MAX_EDGES; Edge++) {
              if (Margin2[Edge] > Margin1[Edge]) {
                Margin2[Edge] = Margin1[Edge];
              }
            }
          }
        }
      }
      //
      // Scale results as needed
      //
      for (Edge = 0; Edge < MAX_EDGES; Edge++) {
        Margin2[Edge] = (Margin2[Edge] * Scale) / 10;
      }
    }
  }

  return mrcSuccess;
}


/**
  This function Reads MrcData structure and finds the minimum last recorded margin for param
  Searches across all bytes and ranks in RankMask

  @param[in]     MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Data structure with the latest margin results.
  @param[in]     Param           - Defines the margin type
  @param[in]     Ranks           - Condenses down the results from multiple ranks

  @retval mrcWrongInputParameter if a bad Param is passed in, otherwise mrcSuccess.
**/
MrcStatus
GetPdaMargins (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          Ranks
  )
{
  MrcDebug      *Debug;
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  MrcRankOut    *RankOut;
  UINT32        *Margin1;
  UINT8         ResultType;
  UINT8         Channel;
  UINT8         Rank;
  UINT8         Byte;
  UINT8         Edge;
  INT8          CurrentOff;
  INT8          GlobalCenter;
  INT16         MarginOffset;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  ResultType = GetMarginResultType (Param);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((MrcRankInChannelExist (MrcData, Rank, Channel) & Ranks) == 0) {
        continue;
      }
      RankOut = &ChannelOut->Dimm[Rank / 2].Rank[Rank % 2];
      GlobalCenter = MrcVrefDqToOffset ((UINT8) (RankOut->MR[mrMR6] & 0x7F));
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        CurrentOff = MrcVrefDqToOffset (RankOut->Ddr4PdaMr6[Byte] & 0x7F);
        MarginOffset = 10 * (CurrentOff - GlobalCenter);
        Margin1 = &MarginResult[ResultType][Rank][Channel][Byte][0];
        for (Edge = 0; Edge < MAX_EDGES; Edge++) {
          if (Edge == 0) {
            Margin1[Edge] += MarginOffset;
          } else {
            Margin1[Edge] -= MarginOffset;
          }
          if ((INT16) Margin1[Edge] < 0) {
            Margin1[Edge] = 0;
          }
        } // for Edge
      } // for Byte
    } // for Rank
  } // for Channel

  return mrcSuccess;
}

/**
  This function Update the Non PDA DDR4 Vref to match the PDA average
  across all bytes (per rank/ch).
  This will allow the use of Non PDA sweep using GetBerMarginByte

  @param[in]     MrcData         - Include all MRC global data.
  @param[in]     RankMask        - ranks to work on

  @retval mrcWrongInputParameter if a bad Param is passed in, otherwise mrcSuccess.
**/
MrcStatus
UpdatePdaCenter (
  IN     MrcParameters *const MrcData,
  IN     const UINT8          RankMask
  )
{
  MrcDebug      *Debug;
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  MrcRankOut    *RankOut;
  UINT8         Channel;
  UINT8         Rank;
  UINT8         Byte;
  UINT8         VrefDq;
  INT16         ByteCenterAvg;
  DDR4_MODE_REGISTER_6_STRUCT Ddr4Mr6;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        if ((1 << Rank) & RankMask) {
          RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[Rank % 2];
          ByteCenterAvg = 0;
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            ByteCenterAvg += MrcVrefDqToOffset (RankOut->Ddr4PdaMr6[Byte] & 0x7F);
          }
          ByteCenterAvg /= Outputs->SdramCount;
          VrefDq = MrcOffsetToVrefDq (MrcData, (INT8) ByteCenterAvg, Channel);
          Ddr4Mr6.Data = RankOut->MR[mrMR6];
          Ddr4Mr6.Bits.VrefDqTrainingRange  = VrefDq >> 6;
          Ddr4Mr6.Bits.VrefDqTrainingValue  = VrefDq & 0x3F;
          RankOut->MR[mrMR6] = Ddr4Mr6.Data;
        }
      }
    }
  }
  return mrcSuccess;
}

/**
  Use this function to retrieve the last margin results from MrcData

  @param[in]     MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Data structure with the latest margin results.
  @param[in]     Param           - Defines the margin type
  @param[in]     RankIn          - Which rank of the host structure you want the result returned on
  @param[in]     Ranks           - Condenses down the results from multiple ranks

  @retval MarginResult structure has been updated if MrcStatus returns mrcSuccess.
  @retval Otherwise, mrcWrongInputParameter is returned if an incorrect Param is passed in.
**/
MrcStatus
GetMarginByte (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          RankIn,
  IN     const UINT8          Ranks
  )
{
  MrcOutput *Outputs;
  UINT32    *Margin1;
  UINT32    *Margin2;
  UINT8     ResultType;
  UINT8     Channel;
  UINT8     Rank;
  UINT8     Byte;
  UINT8     Edge;
  UINT8     Scale;

  Outputs = &MrcData->Outputs;
  switch (Param) {
    case WrV:
    case WrT:
    case WrLevel:
    case RdV:
    case RdT:
    case RcvEna:
    case RcvEnaX:
    case CmdT:
    case CmdV:
      Scale = 10;
      break;

    case WrFan2:
    case WrFan3:
    case RdFan2:
    case RdFan3:
      Scale = 21 / 3;
      break;

    default:
      MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "GetMarginByte: Unknown Margin Parameter\n");
      return mrcWrongInputParameter;
  }

  ResultType = GetMarginResultType (Param);
  ResultType = MIN (ResultType, MAX_RESULT_TYPE - 1);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel) & Ranks) {
            Margin1 = &MarginResult[ResultType][RankIn][Channel][Byte][0];
            Margin2 = &MarginResult[ResultType][Rank][Channel][Byte][0];
            for (Edge = 0; Edge < MAX_EDGES; Edge++) {
              if (Margin1[Edge] > Margin2[Edge]) {
                Margin1[Edge] = Margin2[Edge];
              }
            }
          }
        }
        //
        // Scale results as needed
        //
        Margin1 = &MarginResult[ResultType][RankIn][Channel][Byte][0];
        for (Edge = 0; Edge < MAX_EDGES; Edge++) {
          Margin1[Edge] = (Margin1[Edge] * Scale) / 10;
        }
      }
    }
  }

  return mrcSuccess;
}

/**
  This function is use to "unscale" the MrcData last margin point
  GetMarginByte will scale the results for FAN margin
  This will unscale the results such that future tests start at the correct point

  @param[in]     MrcData      - Include all MRC global data.
  @param[in,out] MarginResult - Input array to be unscaled.
  @param[in]     Param        - Defines the margin type for proper scale selection.
  @param[in]     Rank         - Which rank of the host structure to work on

  @retval mrcSuccess
**/
MrcStatus
ScaleMarginByte (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          Rank
  )
{
  MrcOutput *Outputs;
  UINT32    *Margin;
  UINT8     ResultType;
  UINT8     Channel;
  UINT8     Byte;
  UINT8     Edge;

  //
  // Calculate scale parameter based on param
  // Leave room for expansion in case other params needed to be scaled
  //
  Outputs = &MrcData->Outputs;
  if ((Param == RdFan2) || (Param == RdFan3) || (Param == WrFan2) || (Param == WrFan3)) {
    ResultType = GetMarginResultType (Param);
    ResultType = MIN (MAX_RESULT_TYPE - 1, ResultType);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Margin = &MarginResult[ResultType][Rank][Channel][Byte][0];
          for (Edge = 0; Edge < MAX_EDGES; Edge++) {
            Margin[Edge] = (Margin[Edge] * 15) / 10;
          }
        }
      }
    }
  }

  return mrcSuccess;
}

/**
  This function is used by most margin search functions to change te underlying margin parameter.
  This function allows single search function to be used for different types of margins with minimal impact.
  It provides multiple different parameters, including 2D parameters like Read or Write FAN.
  It can work in either MultiCast or single register mode.

  @param[in,out] MrcData       - Include all MRC global data.
  @param[in]     param         - Includes parameter(s) to change including two dimentional.
  @param[in]     value0        - Selected value to program margin param to
  @param[in]     value1        - Selected value to program margin param to in 2D mode (FAN mode)
  @param[in]     EnMultiCast   - To enable Multicast (broadcast) or single register mode
  @param[in]     channel       - Desired Channel
  @param[in]     rankIn        - Desired Rank - only used for the RxTBit, TxTBit, and RdVBit settings, and to propagate RdVref, for Ddr4 WrV we need to pass rank bit mask
  @param[in]     byte          - Desired byte offset register
  @param[in]     bitIn         - Desired bit offset Mrc data strucure if UpdateMrcData is 1
  @param[in]     UpdateMrcData - Used to decide if Mrc host must be updated
  @param[in]     SkipWait      - Used to skip wait until all channel are done
  @param[in]     RegFileParam  - Used to determine which Rank to download.  Passed to MrcDownloadRegFile.

  @retval MrcStatus -  if succeeded, return mrcSuccess
**/
MrcStatus
ChangeMargin (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          param,
  IN     const INT32          value0,
  IN     const INT32          value1,
  IN     const UINT8          EnMultiCast,
  IN     const UINT8          channel,
  IN     const UINT8          rankIn,
  IN     const UINT16         byte,
  IN     const UINT8          bitIn,
  IN     const UINT8          UpdateMrcData,
  IN     const UINT8          SkipWait,
  IN     const MrcRegFile     RegFileParam
  )
{
  //
  // Programs margin param to the selected value0
  // If param is a 2D margin parameter (ex: FAN), then it uses both value0 and value1
  //    For an N point 2D parameter, value1 can be an interger from 0 to (N-1)
  //    For per bit timing parameter, value1 is the sign of the shift
  // param = {0:RcvEna, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
  //               7:WrTBox, 8:WrTBit, 9:RdTBit, 10:RdVBit,
  //              16:RdFan2, 17:WrFan2, 32:RdFan3, 33:WrFan3}
  // Note: For Write Vref, the trained value and margin register are the same
  // Note: rank is only used for the RxTBit, TxTBit, and RdVBit settings, and to propagate RdVref
  // Note: PerBit Settings (WrTBit, RdTBit, RdVBit) provide all 8 offsets in value0

  MrcDebug          *Debug;
  const MrcInput    *Inputs;
  MrcOutput         *Outputs;
  MrcIntOutput      *IntOutputs;
  MrcIntControllerOut *IntControllerOut;
  MrcIntChannelOut  *IntChannelOut;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcChannelOut     *CurrentChannelOut;
  MrcStatus         Status;
  UINT8             CurrentCh;
  UINT8             CurrentByte;
  UINT8             Max0;
  UINT8             MaxT;
  UINT8             MaxV;
  UINT8             maskT;
  UINT8             rank;
  UINT8             Rank;
  UINT8             bit;
  UINT8             ReadRFRd;
  UINT8             ReadRFWr;
  INT32             sign;
  INT32             v0;
  INT32             v0Input;
  INT32             v0Local;
  INT32             v1;
  INT32             Min;
  UINT32            Offset;
  BOOLEAN           UpdateDataOffset;
  DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT CRValue;
  BOOLEAN           PdaMode;
  BOOLEAN           Ddr4;
  UINT8             RankMask;

  Status            = mrcSuccess;
  UpdateDataOffset  = FALSE;
  ReadRFRd          = 0;
  ReadRFWr          = 0;
  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  IntOutputs        = MrcData->IntOutputs.Internal;
  Debug             = &Outputs->Debug;
  ControllerOut     = &Outputs->Controller[0];
  IntControllerOut  = &IntOutputs->Controller[0];
  Ddr4              = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  RankMask          = rankIn;
  PdaMode           = FALSE;

  //
  // Pre-Process the margin numbers
  //
  MaxT   = MAX_POSSIBLE_TIME;   // Maximum value for Time
  MaxV   = MAX_POSSIBLE_VREF;   // Maximum value for Vref
  maskT  = 0x3F; // 6 bits (2's complement)

  if ((param < RdV) || (param == WrLevel)) {
    Max0 = MaxT;
  } else if ((param == WrTBit) || (param == RdTBit) || (param == RdVBit)) {
    Max0 = 0xFF;
  } else {
#if (SUPPORT_DDR4 == SUPPORT)
    if ((Outputs->DdrType == MRC_DDR_TYPE_DDR4) && (param == WrV || param == WrFan2 || param == WrFan3)) {
      MaxV = MAX_POSSIBLE_DDR4_WRITE_VREF;
    }
#endif //SUPPORT_DDR4
    Max0 = MaxV; // Vref for RdV, WrV, and FAN modes
  }
  //
  // Pre-Process the margin numbers.  Calculate 2D points based on FAN slopes
  //
  v0    = value0;
  sign  = (2 * value1 - 1);

  //
  // For Fan3, optimize point orders to minimize Vref changes and # of tests required
  //
  if (param >= RdFan3) {
    sign = ((3 * value1 - 5) * value1) / 2;   // Translates to {0:0, 1:-1, 2:+1}
    if (value1 == 0) {
      v0 = (5 * value0) / 4;
    }
  }

  v1 = (sign * value0) / 3;

  Min = (-1) - Max0;
  v0 = RANGE (v0, Min, Max0);

  Min = (-1) - MaxT;
  v1 = RANGE (v1, Min, MaxT);

  //
  // Rank = 0xFF - all rank , only apply to WrV with DDR4
  // rank param only apply for RcvEnX,and WrV in DDR4
  // DDR4 will use RanBitMask only to support per dimm optimization
  //
  rank          = (rankIn >= MAX_RANK_IN_CHANNEL) ? 0 : rankIn;

  ChannelOut    = &ControllerOut->Channel[channel];
  IntChannelOut = &IntControllerOut->Channel[channel];
  CRValue.Data  = (byte == 0x1FF) ? 0 : (ChannelOut->DataOffsetTrain[byte]);
  switch (param) {
    case RcvEna:
      CRValue.Bits.RcvEnOffset = (UINT32) v0;
      UpdateDataOffset         = TRUE;
      break;

    case RdT:
      CRValue.Bits.RxDqsOffset = (UINT32) v0;
      UpdateDataOffset         = TRUE;
      break;

    case WrT:
      CRValue.Bits.TxDqOffset = (UINT32) v0;
      UpdateDataOffset        = TRUE;
      break;

    case WrDqsT:
      CRValue.Bits.TxDqsOffset = (UINT32) v0;
      UpdateDataOffset         = TRUE;
      break;

    case RdV:
      CRValue.Bits.VrefOffset = (UINT32) v0;
      UpdateDataOffset        = TRUE;
      break;

    case RcvEnaX:
      //
      // Need to change io_lat on all ranks
      //
      v0Input = v0; // save the input offset (after min/max truncate)
      for (CurrentCh = 0; CurrentCh < MAX_CHANNEL; CurrentCh++) {
        if ((MrcChannelExist (Outputs, CurrentCh)) && (EnMultiCast || (CurrentCh == channel))) {
          ChannelOut    = &ControllerOut->Channel[CurrentCh];
          v0 = v0 * 4;
          v0Local = v0; // save the modified v0 for multicast mode
          for (CurrentByte = 0; (CurrentByte < Outputs->SdramCount); CurrentByte++) {
            if ((CurrentByte == byte) || (EnMultiCast)) {
              for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
                if (MrcRankInChannelExist (MrcData, Rank, CurrentCh)) {
                  v0 += ChannelOut->RcvEn[Rank][CurrentByte];// the assumption is that we are @ 1 Qclk before edge
                  //
                  // Limit RcvEna 0-511 to prevent under/overflow.
                  //
                  if (v0 < 0) {
                    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING: RcvEn PI wrapped below zero!\n");
                    v0 = 0;
                  } else if (v0 > DDRDATA_CR_RXTRAINRANK0_RxRcvEnPi_MAX) {
                    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING: RcvEn PI wrapped above 9 bits!\n");
                    v0 = DDRDATA_CR_RXTRAINRANK0_RxRcvEnPi_MAX;
                  }
                  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "ch%d rank%d byte%d value %d\n", CurrentCh, Rank, CurrentByte, v0);
                  UpdateRxTValues (MrcData, CurrentCh, Rank, CurrentByte, 0,(UINT16) v0);
                  MrcDownloadRegFile (MrcData, CurrentCh, 0, 0, MrcRegFileStart, CurrentByte, 1, 0);
                  v0 = v0Local;
                }
              }
            }
          }
        } // if channel exists
        v0 = v0Input; // restore v0 for next channel
      } // for CurrentCh
      break;

    case WrV:
    case WrFan2:
    case WrFan3:
      for (CurrentCh = 0; CurrentCh < MAX_CHANNEL; CurrentCh++) {
        if (MrcChannelExist (Outputs, CurrentCh)) {
          if ((EnMultiCast == 1) || (CurrentCh == channel)) {
            if (Ddr4) {
              PdaMode = (byte == 0) ? FALSE : TRUE;  //Works only with WrV and not WrFan2 or WrFan3
              if (EnMultiCast == 1) {
                RankMask = 0xF;
              }
            }
            UpdateVrefWaitTilStable (MrcData, CurrentCh, UpdateMrcData, v0, RankMask, byte, PdaMode, SkipWait); //byte is now DeviceMask, Rank mask is for DDr4
          }
        }
      }

      if ((param == WrFan2) || (param == WrFan3)) {
        CRValue.Data            = ChannelOut->DataOffsetTrain[byte];
        CRValue.Bits.TxDqOffset = v1; // Update TxDqOffset
        UpdateDataOffset = TRUE;
      }
      break;

    case RdFan2:  // Read margin in FAN modes.
    case RdFan3:
      CRValue.Data             = ChannelOut->DataOffsetTrain[byte];
      CRValue.Bits.VrefOffset  = v0; // Update VrefOffset
      CRValue.Bits.RxDqsOffset = v1; // Update RxDqsOffset
      UpdateDataOffset = TRUE;
      break;

    case WrLevel: // Write DQ and DQS timing, margining only DQS-CLK timing
      CRValue.Data             = ChannelOut->DataOffsetTrain[byte];
      CRValue.Bits.TxDqOffset  = v0; // Update TxDqOffset
      CRValue.Bits.TxDqsOffset = v0; // Update TxDqsOffset
      UpdateDataOffset = TRUE;
      break;

    case WrTBit:  // Write DQ per BIT timing
      ReadRFWr = 1;
      if (EnMultiCast) {
        Offset = DDRDATA_CR_TXPERBITRANK0_REG +
          ((DDRDATA_CR_TXPERBITRANK1_REG - DDRDATA_CR_TXPERBITRANK0_REG) * rank);
        MrcWriteCrMulticast (MrcData, Offset, value0);
        for (CurrentCh = 0; CurrentCh < MAX_CHANNEL; CurrentCh++) {
          CurrentChannelOut = &ControllerOut->Channel[CurrentCh];
          //
          // Download new settings from the RegFile to the Pads
          //
          MrcDownloadRegFile (MrcData, CurrentCh, 1, rank, RegFileParam, 0, ReadRFRd, ReadRFWr);
          if (UpdateMrcData) {
            for (CurrentByte = 0; CurrentByte < Outputs->SdramCount; CurrentByte++) {
              for (bit = 0; bit < MAX_BITS; bit++) {
                CurrentChannelOut->TxDqPb[rank][CurrentByte][bit].Center = (value0 >> (4 * bit)) & 0xF;
              }
            }
          }
        }
      } else {
        Offset = DDRDATA0CH0_CR_TXPERBITRANK0_REG +
          ((DDRDATA0CH0_CR_TXPERBITRANK1_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG) * rank) +
          ((DDRDATA1CH0_CR_TXPERBITRANK0_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG) * byte) +
          ((DDRDATA0CH1_CR_TXPERBITRANK0_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG) * channel);
        MrcWriteCR (MrcData, Offset, value0);
        //
        // Download new settings from the RegFile to the Pads
        //
        MrcDownloadRegFile (MrcData, channel, 0, rank, RegFileParam, (UINT8) byte, ReadRFRd, ReadRFWr);
        if (UpdateMrcData) {
          for (bit = 0; bit < MAX_BITS; bit++) {
            ChannelOut->TxDqPb[rank][byte][bit].Center = (value0 >> (4 * bit)) & 0xF;
          }
        }
      }
      break;

    case RdTBit:  // Read DQ per BIT timing
      ReadRFRd = 1;
      if (EnMultiCast) {
        Offset = DDRDATA_CR_RXPERBITRANK0_REG +
          ((DDRDATA_CR_RXPERBITRANK1_REG - DDRDATA_CR_RXPERBITRANK0_REG) * rank);
        MrcWriteCrMulticast (MrcData, Offset, value0);
        for (CurrentCh = 0; CurrentCh < MAX_CHANNEL; CurrentCh++) {
          CurrentChannelOut = &ControllerOut->Channel[CurrentCh];
          //
          // Download new settings from the RegFile to the Pads
          //
          MrcDownloadRegFile (MrcData, CurrentCh, 1, rank, RegFileParam, 0, ReadRFRd, ReadRFWr);
          if (UpdateMrcData) {
            for (CurrentByte = 0; CurrentByte < Outputs->SdramCount; CurrentByte++) {
              for (bit = 0; bit < MAX_BITS; bit++) {
                CurrentChannelOut->RxDqPb[rank][CurrentByte][bit].Center = (value0 >> (4 * bit)) & 0xF;
              }
            }
          }
        }
      } else {
        Offset = DDRDATA0CH0_CR_RXPERBITRANK0_REG +
          ((DDRDATA0CH0_CR_RXPERBITRANK1_REG - DDRDATA0CH0_CR_RXPERBITRANK0_REG) * rank) +
          ((DDRDATA1CH0_CR_RXPERBITRANK0_REG - DDRDATA0CH0_CR_RXPERBITRANK0_REG) * byte) +
          ((DDRDATA0CH1_CR_RXPERBITRANK0_REG - DDRDATA0CH0_CR_RXPERBITRANK0_REG) * channel);
        MrcWriteCR (MrcData, Offset, value0);
        //
        // Download new settings from the RegFile to the Pads
        //
        MrcDownloadRegFile (MrcData, channel, 0, rank, RegFileParam, (UINT8) byte, ReadRFRd, ReadRFWr);
        if (UpdateMrcData) {
          for (bit = 0; bit < MAX_BITS; bit++) {
            ChannelOut->RxDqPb[rank][byte][bit].Center = (value0 >> (4 * bit)) & 0xF;
          }
        }
      }
      break;

    case RdVBit:  // Read DQ per BIT Voltage
      ReadRFRd = 1;
      if (EnMultiCast) {
        MrcSetRxOffsetVdqBroadcast (MrcData, 0xFF, (rankIn == 0xFF) ? 0xFF : rank, value0);
        for (CurrentCh = 0; CurrentCh < MAX_CHANNEL; CurrentCh++) {
          CurrentChannelOut = &ControllerOut->Channel[CurrentCh];
          //
          // Download new settings from the RegFile to the Pads
          //
          MrcDownloadRegFile (MrcData, CurrentCh, 1, rank, RegFileParam, 0, ReadRFRd, ReadRFWr);
          if (UpdateMrcData) {
            for (CurrentByte = 0; CurrentByte < Outputs->SdramCount; CurrentByte++) {
              for (bit = 0; bit < MAX_BITS; bit++) {
                CurrentChannelOut->RxDqVrefPb[rank][CurrentByte][bit].Center = (value0 >> (4 * bit)) & 0xF;
              }
            }
          }
        }
      } else {
        MrcSetRxOffsetVdq (MrcData, channel, rank, (UINT8) byte, value0);
        //
        // Download new settings from the RegFile to the Pads
        //
        MrcDownloadRegFile (MrcData, channel, 0, rank, RegFileParam, (UINT8) byte, ReadRFRd, ReadRFWr);
        if (UpdateMrcData) {
          ChannelOut = &ControllerOut->Channel[channel];
          for (bit = 0; bit < MAX_BITS; bit++) {
            ChannelOut->RxDqVrefPb[rank][byte][bit].Center = (value0 >> (4 * bit)) & 0xF;
          }
        }
      }

      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Function ChangeMargin, Invalid parameter %d\n", param);
      return mrcWrongInputParameter;
  } // end switch (param)

  if (UpdateDataOffset) {
    //
    // Download new settings from the RegFile to the Pads
    //
    if ((param == RcvEnaX) || (param == RcvEna) || (param == RdT) || (param == RdV) || (param == RdFan2) || (param == RdFan3)) {
      ReadRFRd = 1;
    } else if ((param == WrT) || (param == WrDqsT) || (param == WrLevel) || (param == WrFan2) || (param == WrFan3)) {
      ReadRFWr = 1;
    }
    //
    // Write CR
    //
    if (EnMultiCast) {
      MrcWriteCrMulticast (MrcData, MrcGetOffsetDataOffsetTrain (MrcData, 0xFF, 0xFF), CRValue.Data);
      for (CurrentCh = 0; CurrentCh < MAX_CHANNEL; CurrentCh++) {
        if (MrcChannelExist (Outputs, CurrentCh)) {
          CurrentChannelOut = &ControllerOut->Channel[CurrentCh];
          if (!MrcRankInChannelExist (MrcData, rank, CurrentCh)) {
            //
            // No such rank on this channel - this may happen when EnMultiCast is used.
            // Pick up any populated rank on this channel.
            //
            for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
              if (MrcRankInChannelExist (MrcData, rank, CurrentCh)) {
                break;
              }
            }
          }
          //
          // Download new settings from the RegFile to the Pads
          //
          MrcDownloadRegFile (MrcData, CurrentCh, 1, rank, RegFileParam, 0, ReadRFRd, ReadRFWr);
          for (CurrentByte = 0; CurrentByte < Outputs->SdramCount; CurrentByte++) {
            if (UpdateMrcData) {
              CurrentChannelOut->DataOffsetTrain[CurrentByte] = CRValue.Data;
            }
          }
        }
      }
    } else {
      Offset = MrcGetOffsetDataOffsetTrain (MrcData, channel, (UINT8) byte);
      MrcWriteCR (MrcData, Offset, CRValue.Data);
      //
      // Download new settings from the RegFile to the Pads
      //
      MrcDownloadRegFile (MrcData, channel, 0, rank, RegFileParam, (UINT8) byte, ReadRFRd, ReadRFWr);
      if (UpdateMrcData) {
        ChannelOut->DataOffsetTrain[byte] = CRValue.Data;
      }
    }
  }

  return Status;
}

/**
  This function triggers the hardware to download the specified RegFile.
  The setting of ReadRfRd and ReadRfWr must be mutually exclusive.
  Only 1 (start download) and 0 (do nothing) are valid values for ReadRfXx.

  @param[in] MrcData       - Global MRC Data
  @param[in] Channel       - The Channel to download target.
  @param[in] ByteMulticast - Enable Multicasting all bytes on that Channel.
  @param[in] Rank          - The Rank download target.
  @param[in] RegFileParam  - Used to determine which Rank to download.
                              MrcRegFileRank - Uses the Rank Parameter.
                              MrcRegFileStart    - Uses the Rank in REUT_CH_SEQ_BASE_ADDR_START after decoding logical to physical.
                              MrcRegFileCurrent  - Uses the Rank in REUT_CH_SEQ_BASE_ADDR_CURRENT after decoding logical to physical.
  @param[in] Byte          - The Byte download target.
  @param[in] ReadRfRd      - Download the read RegFile. 1 enables, 0 otherwise
  @param[in] ReadRfWr      - Download the write RegFile. 1 enables, 0 otherwise

  @retval MrcStatus - If both ReadRfRd and ReadRfWr are set, the functions returns mrcWrongInputParameters.
                         Otherwise, mrcSuccess.
**/
void
MrcDownloadRegFile (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const BOOLEAN        ByteMulticast,
  IN  UINT8               Rank,
  IN const MrcRegFile     RegFileParam,
  IN const UINT8          Byte,
  IN const BOOLEAN        ReadRfRd,
  IN const BOOLEAN        ReadRfWr
  )
{
  const MRC_FUNCTION                                                      *MrcCall;
  DDRDATA0CH0_CR_DDRCRDATACONTROL0_STRUCT                                 DdrCrDataControl0;
  MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_STRUCT  ReutChSeqRankL2PMapping;
  UINT64                                                                  ReutChSeqBaseAddr;
  MrcChannelOut                                                           *ChannelOut;
  UINT32                                                                  CrOffset;
  UINT8                                                                   LogicalRank;

  MrcCall    = MrcData->Inputs.Call.Func;
  ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
  //
  // Determine the rank to download the Reg File
  //
  switch (RegFileParam) {
    case MrcRegFileStart:
      CrOffset = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_REG +
        (
         (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_REG) *
         Channel
        );
      break;

    case MrcRegFileCurrent:
      CrOffset = MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_CURRENT_MCMAIN_0_REG +
        (
         (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_CURRENT_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_CURRENT_MCMAIN_0_REG) *
         Channel
        );
      break;

    case MrcRegFileRank:
    default:
      CrOffset = 0;
      break;
  }

  if (CrOffset != 0) {
    ReutChSeqBaseAddr  = MrcReadCR64 (MrcData, CrOffset);
    ReutChSeqBaseAddr &= MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_CURRENT_MCMAIN_0_Rank_Address_MSK;
    LogicalRank        = (UINT8) MrcCall->MrcRightShift64 (
                                            ReutChSeqBaseAddr,
                                            MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_CURRENT_MCMAIN_0_Rank_Address_OFF
                                            );

    CrOffset = MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG +
      (
       (
        MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG -
        MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG
       ) * Channel
      );
    ReutChSeqRankL2PMapping.Data = MrcReadCR (MrcData, CrOffset);
    Rank = (UINT8)
      (
       (ReutChSeqRankL2PMapping.Data >> (LogicalRank * 4)) &
       MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_Logical_to_Physical_Rank0_Mapping_MSK
      );
  }

  if (ByteMulticast) {
    //
    // Multicast settings on the channel
    //
    CrOffset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
  } else {
    CrOffset = MrcGetOffsetDataControl0 (MrcData, Channel, Byte);
  }

  DdrCrDataControl0.Data            = MrcReadCR (MrcData, CrOffset);
  DdrCrDataControl0.Bits.ReadRFRd   = ReadRfRd;
  DdrCrDataControl0.Bits.ReadRFWr   = ReadRfWr;
  DdrCrDataControl0.Bits.ReadRFRank = Rank;
  MrcWriteCR (MrcData, CrOffset, DdrCrDataControl0.Data);
}

/**
  This procedure is meant to handle basic timing centering, places strobe in the middle of the data eye,
  for both read and write DQ/DQS using a very robust, linear search algorthim.

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     chBitMaskIn    - Channel bit mask.
  @param[in]     param          - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                   8:WrTBit, 9:RdTBit, 10:RdVBit,
                                   16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                   ONLY RdT and WrT are allowed in this function
  @param[in]     ResetPerBit    - Option to Reset PerBit Deskew to middle value before byte training
  @param[in]     loopcount      - loop count
  @param[in]     MsgPrint       - Show debug prints
  @param[in]     EarlyCentering - Execute as early centering routine

  @retval MrcStatus -  If succeeded, return mrcSuccess
**/
MrcStatus
DQTimeCentering1D (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          chBitMaskIn,
  IN     const UINT8          param,
  IN     const UINT8          ResetPerBit,
  IN     const UINT8          loopcount,
  IN     BOOLEAN              MsgPrint,
  IN     BOOLEAN              EarlyCentering
  )
{
  const MrcInput    *Inputs;
  const MRC_FUNCTION *MrcCall;
  MrcDebug          *Debug;
  MrcDebugMsgLevel   DebugLevel;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcRankOut        *RankOut;
  MrcIntControllerOut *IntControllerOut;
  MrcIntOutput        *MrcIntData;
  INT32             *CurrentPS;
  INT32             *CurrentPE;
  INT32             *LargestPS;
  INT32             *LargestPE;
  UINT32            *Margin;
  BOOLEAN           *MarginSignReversed;
  MrcStatus         Status;
  BOOLEAN           Pass;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             RankMask;
  UINT8             RankRx;
  UINT8             Byte;
  UINT8             Step;
  UINT32            MinWidth;
  UINT8             chBitMask;
  UINT8             DumArr[7];
  UINT16            Result;
  UINT16            TxDqValue;
  INT32             CurrentPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             CurrentPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             LargestPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             LargestPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             cWidth;
  INT32             lWidth;
  INT32             Center;
  INT32             DqsDelay;
  INT32             DqsStart;
  INT32             DqsStop;
  UINT32            Start;
  UINT32            End;
  UINT32            Offset;
  BOOLEAN           Ddr4;
  BOOLEAN           Ddr4WriteVrefParam;
  BOOLEAN           EccSupport;
  BOOLEAN           EyeTooSmall[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  UINT8             VoltageOffset;
#ifdef MRC_DEBUG_PRINT
  UINT64            BitLaneFailures[MAX_CHANNEL][ (MAX_POSSIBLE_VREF * 2) + 1];
  UINT8             EccBitLaneFailures[MAX_CHANNEL][ (MAX_POSSIBLE_VREF * 2) + 1];
  UINT8             BitCountTensMax;
  UINT8             BitCountMax;
  UINT8             BitCount;
  const char        *DelayString;
#endif
  MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_STRUCT ReutChErrChunkRankByteNthStatus;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  MrcIntData = ((MrcIntOutput *)(MrcData->IntOutputs.Internal));
  IntControllerOut = &MrcIntData->Controller[0];
  chBitMask     = chBitMaskIn;
  Status        = mrcSuccess;
  Center        = 0;
  MinWidth      = MrcGetMinimalEyeHeight (MrcData, EarlyCentering);
  MrcCall->MrcSetMem ((UINT8 *) EyeTooSmall, sizeof (EyeTooSmall), FALSE);
  MrcCall->MrcSetMem (DumArr, sizeof (DumArr), 1);
  Ddr4 = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Ddr4WriteVrefParam = Ddr4 && (param == WrV);
  DebugLevel = MsgPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  EccSupport = Outputs->EccSupport;

  if ((param != RdT) && (param != WrT) && (param != RcvEnaX)  && (param != WrV) && (param != RdV) && (param != CmdV)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DataTimeCentering1D: Unknown Margin Parameter\n");
    return mrcWrongInputParameter;
  }

  if ((param == WrV) || (param == RdV) || (param == CmdV)) {
    if (Ddr4 && (param == WrV)) {
      DqsStart = -MAX_POSSIBLE_DDR4_WRITE_VREF;
      DqsStop  = MAX_POSSIBLE_DDR4_WRITE_VREF;
    } else {
      DqsStart = -MAX_POSSIBLE_VREF;
      DqsStop  = MAX_POSSIBLE_VREF;
    }
  } else {
    DqsStart = -MAX_POSSIBLE_TIME;
    DqsStop  = MAX_POSSIBLE_TIME;
  }

  Step     = 1;
  if ((param == CmdV) && (Inputs->MemoryProfile == STD_PROFILE)) {
    Step = 2;
  }


  if (param == RcvEnaX) {
    SetupIOTestBasicVA (MrcData, chBitMask, loopcount - 3, 0, 0, 0, 8);
    Outputs->DQPat = RdRdTA_All;
    // RcvEnX Tot range of 112 per side
    DqsStart = -28;
    DqsStop  = 28;
  } else if (param == CmdV) {
    SetupIOTestCADB (MrcData, chBitMask, loopcount, NSOE, 1, 0);
  } else {
    SetupIOTestBasicVA (MrcData, chBitMask, loopcount, NSOE, 0, 0, 8);
  }

#ifdef MRC_DEBUG_PRINT
  switch (param) {
    case RcvEnaX :
      DelayString = RcvEnDelayString;
      break;
    case WrV :
      DelayString = WrVDelayString;
      break;
    case RdV :
      DelayString = RdVDelayString;
      break;
    case CmdV:
      DelayString = CmdVDelayString;
      break;
      default :
      DelayString = DqsDelayString;
  }
#endif

  //
  // Reset PerBit Deskew to middle value before byte training
  // Write timing offset for bit[x] of the DQ byte. Linear from 0-15, each step size is tQCLK/64
  // Read timing offset for bit[x] of the DQ byte. Linear from 0-15, each step size is tQCLK/64
  //
  if (ResetPerBit == 1) {
    //
    // EnMultiCast, UpdateMrcData
    //
    Status = ChangeMargin (
               MrcData,
               (param == RdT) ? RdTBit : WrTBit,
               0x88888888,
               0,
               1,
               0,
               0,
               0,
               0,
               1,
               0,
               MrcRegFileStart
               );
  }
  //
  // Center all Ranks
  //
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {

#ifdef MRC_DEBUG_PRINT
    if (Outputs->ValidRankMask & (MRC_BIT0 << Rank)) {
      MRC_DEBUG_MSG (Debug, DebugLevel, "Rank = %d\nChannel 0                1\nByte\t", Rank);
      MRC_DEBUG_MSG (
        Debug,
        DebugLevel, (
                      EccSupport
                      ) ? "0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 Error Count" : "0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 Error Count"
        );
    }
#endif  // MRC_DEBUG_PRINT

    chBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      if (param == RcvEnaX) {
        if ((ChannelOut->ValidRankBitMask & (1 << Rank)) != 0) { // If rank under test exists, then select all ranks
          RankMask = 0xFF; // run on all available ranks for TAT stress
        } else {
          RankMask = 0;
        }
      } else if (param == RdV) {
        RankMask = 0xFF; // run on all available ranks for RdV param - we dont use different vref per rank
      } else {
        RankMask = (1 << Rank);
      }
      chBitMask |= SelectReutRanks (MrcData, Channel, RankMask, 0);

      if ((1 << Channel) & chBitMask) {
        //
        // Clear out anything left over in DataOffsetTrain
        // Update rank timing to middle value
        //
        for (Byte = 0; (Byte < Outputs->SdramCount) && (param != RcvEnaX) && (param != WrV); Byte++) {
          if (param == RdT) {
            //
            // Read Dq/Dqs
            //
            ChannelOut->RxDqsP[Rank][Byte] = 32;
            ChannelOut->RxDqsN[Rank][Byte] = 32;
            UpdateRxT (MrcData, Channel, Rank, Byte, 0xFF, 0);
          } else if (param == WrT) {
            //
            // Write Dq/Dqs
            // Put TxDq in the middle of the Strobe and ensure there is enough room to sweep to the right.
            //
            if ((ChannelOut->TxDqs[Rank][Byte] + 32 + DqsStop) <= DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX) {
              TxDqValue = ChannelOut->TxDqs[Rank][Byte] + 32;
            } else {
              TxDqValue = (UINT16) (DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX - DqsStop);
            }
            ChannelOut->TxDq[Rank][Byte] = TxDqValue;
            UpdateTxT (MrcData, Channel, Rank, Byte, 0xFF, 0);
          } else if (param == RdV) {
            //
            // Read Vref
            //
            ChannelOut->RxVref[Byte] = 0;
            for (RankRx = 0; RankRx < MAX_RANK_IN_CHANNEL; RankRx++) {
              UpdateRxT (MrcData, Channel, RankRx, Byte, 0xFF, 0);
            }
          }
        }
        if (param == WrV) {
          if (Ddr4) {
            //
            // Write Vref - program to middle (zero offset) range before sweep
            //
            MrcSetTxVrefDdr4(MrcData, Channel, Rank, 0, TRUE);
          } else {
            //
            // Dispose of any existing Offsets on non DDR4 as well
            //
            if (Channel == 0) {
              VoltageOffset = (UINT8) IntControllerOut->VrefAdjust1.Bits.Ch0VrefCtl;
            } else { //Channel 1
              VoltageOffset = (UINT8) IntControllerOut->VrefAdjust1.Bits.Ch1VrefCtl;
            }
            UpdateVrefWaitTilStable(MrcData, Channel, 1, -1 * (INT8) MrcSE (VoltageOffset, 7, 8), 0, 0, FALSE, 0);
          }
        }
        //
        // Clear any old state in DataTrain Offset
        //
        MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);

        //
        // Setup REUT Error Counters to count errors on all lanes
        //
        Offset = MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_0_REG +
          ((MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_0_REG - MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_0_REG) * Channel);
        MrcWriteCR (MrcData, Offset, 0);
      }
    } // for Channel
    //
    // Continue if not valid rank on any channel
    //
    if (chBitMask == 0) {
      continue; // This rank does not exist on any of the channels
    }
    //
    // Sweep through values
    //
    MRC_DEBUG_MSG (Debug, DebugLevel, "\n%s", DelayString);
    for (DqsDelay = DqsStart; DqsDelay <= DqsStop; DqsDelay += Step) {
      //
      // Program DQS Delays
      //
      if (param == CmdV) {
        UpdateVrefWaitTilStable (MrcData, 2, 0, DqsDelay, 0, 0, FALSE, 0);
        if (Ddr4 && (chBitMask & MRC_BIT1)) {
          UpdateVrefWaitTilStable (MrcData, 3, 0, DqsDelay, 0, 0, FALSE, 0); // DDR4 ch1
        }
        MrcResetSequence (MrcData);
      } else {
        if (Ddr4WriteVrefParam) {
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (chBitMask & (MRC_BIT0 << Channel)) {
              UpdateVrefWaitTilStable (MrcData, Channel, 0, DqsDelay, 1 << Rank, 0, FALSE, 0);
            }
          }
        } else {
          Status = ChangeMargin (MrcData, param, DqsDelay, 0, 1, 0, Rank, 0, 0, 0, 0, MrcRegFileStart);
        }
      }

      //
      // Clear Errors and Run Test
      //
      RunIOTest (MrcData, chBitMask, Outputs->DQPat, DumArr, 1, 0);

      MRC_DEBUG_MSG (Debug, DebugLevel, "\n% 5d  \t", DqsDelay);

      //
      // Update results for all Channel/bytes
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(chBitMask & (MRC_BIT0 << Channel))) {
          MRC_DEBUG_MSG (
            Debug,
            DebugLevel,
            (Channel != 0) ? "" : (EccSupport ? "                  " : "                ")
            );
          continue;
        }

        //
        // Read out per byte error results and update limit
        //
        Offset = MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG +
          (
           (
            MCHBAR_CH1_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG -
            MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG
           ) * Channel
          );
        ReutChErrChunkRankByteNthStatus.Data  = MrcReadCR64 (MrcData, Offset);
        Result = (UINT16) ReutChErrChunkRankByteNthStatus.Bits.Byte_Group_Error_Status;

#ifdef MRC_DEBUG_PRINT
        if (MsgPrint) {
          Offset = MCHBAR_CH0_CR_REUT_CH_ERR_DATA_STATUS_REG +
            ((MCHBAR_CH1_CR_REUT_CH_ERR_DATA_STATUS_REG - MCHBAR_CH0_CR_REUT_CH_ERR_DATA_STATUS_REG) * Channel);

          BitLaneFailures[Channel][DqsDelay + DqsStop] = MrcReadCR64 (MrcData, Offset);
          EccBitLaneFailures[Channel][DqsDelay + DqsStop] = (UINT8) ReutChErrChunkRankByteNthStatus.Bits.ECC_Error_Status;
        }
#endif
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          //
          // Check for Byte group error status
          //
          Pass = ((Result & (MRC_BIT0 << Byte)) == 0);

          MRC_DEBUG_MSG (Debug, DebugLevel, Pass ? ". " : "# ");

          CurrentPS = &CurrentPassingStart[Channel][Byte];
          CurrentPE = &CurrentPassingEnd[Channel][Byte];
          LargestPS = &LargestPassingStart[Channel][Byte];
          LargestPE = &LargestPassingEnd[Channel][Byte];
          if (DqsDelay == DqsStart) {
            if (Pass) {
              //
              // No error on this Byte group
              //
              *CurrentPS = *CurrentPE = *LargestPS = *LargestPE = DqsDelay;
            } else {
              //
              // Selected Byte group has accumulated an error during loop back pattern
              //
              *CurrentPS = *CurrentPE = *LargestPS = *LargestPE = DqsStart - 2;
            }
          } else {
            if (Pass) {
              //
              // No error on this Byte group
              //
              if (*CurrentPE != (DqsDelay - Step)) {
                *CurrentPS = DqsDelay;
              }
              *CurrentPE = DqsDelay;

              //
              // Update Largest variables
              //
              cWidth = *CurrentPE - *CurrentPS;
              lWidth = *LargestPE - *LargestPS;
              if (cWidth > lWidth) {
                *LargestPS = *CurrentPS;
                *LargestPE = *CurrentPE;
              }
            }
          }
        } // for Byte
      } // for Channel
#ifdef MRC_DEBUG_PRINT
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (chBitMask & (MRC_BIT0 << Channel)) {
          Offset = MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG +
            ((MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG - MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG) * Channel);
          MRC_DEBUG_MSG (Debug, DebugLevel, " 0x%x\t", MrcReadCR (MrcData, Offset));
        }
      }
#endif  // MRC_DEBUG_PRINT
    } // for DqsDelay
    MRC_DEBUG_MSG (Debug, DebugLevel, "\n");  // End last line of Byte table.

#ifdef MRC_DEBUG_PRINT
    //
    // Print out the bit lane failure information
    //
    if (param != CmdV) {
      if (EccSupport) {
        BitCountMax = 72;
        BitCountTensMax = 8;
      } else {
        BitCountMax = 64;
        BitCountTensMax = 7;
      }
      MRC_DEBUG_MSG (Debug, DebugLevel, "Bit Lane Information\n");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (chBitMask & (1 << Channel)) {
          MRC_DEBUG_MSG (Debug, DebugLevel, "Channel %d\nBitLane ", Channel);
          for (BitCount = 0; BitCount < BitCountTensMax; BitCount++) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "%u         ", BitCount);
          }

          MRC_DEBUG_MSG (Debug, DebugLevel, "\n        ");  // End tens number and align ones number
          for (BitCount = 0; BitCount < BitCountMax; BitCount++) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "%u", BitCount % 10);
          }

          MRC_DEBUG_MSG (Debug, DebugLevel, "\n%s", DelayString);

          for (DqsDelay = DqsStart; DqsDelay <= DqsStop; DqsDelay += Step) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "\n% 5d\t", DqsDelay); // Begin with a new line and print the DqsDelay value
            for (BitCount = 0; BitCount < 64; BitCount++) {
              MRC_DEBUG_MSG (
                Debug,
                DebugLevel,
                (BitLaneFailures[Channel][DqsDelay + DqsStop] & MrcCall->MrcLeftShift64 (1, BitCount)) ? "#" : "."
                );
            }
            if (EccSupport) {
              for (BitCount = 0; BitCount < MAX_BITS; BitCount++) {
                MRC_DEBUG_MSG (
                  Debug,
                  DebugLevel,
                  (EccBitLaneFailures[Channel][DqsDelay + DqsStop] & (1 << BitCount)) ? "#" : "."
                  );
              }
            }
          }

          MRC_DEBUG_MSG (Debug, DebugLevel, "\n"); // Gap after Channel
        }
      }
    }
#endif

    //
    // Clean Up for next Rank
    //
    if (param == CmdV) {
      UpdateVrefWaitTilStable (MrcData, 2, 0, 0, 0, 0, FALSE, 0);
      if (Ddr4 && (chBitMask & MRC_BIT1)) {
        UpdateVrefWaitTilStable (MrcData, 3, 0, 0, 0, 0, FALSE, 0); // DDR4 ch1
      }
      MrcResetSequence (MrcData);
    } else {
      if (Ddr4WriteVrefParam) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (chBitMask & (MRC_BIT0 << Channel)) {
            UpdateVrefWaitTilStable (MrcData, Channel, 0, 0, 1 << Rank, 0, FALSE, 0);
          }
        }
      } else {
        Status = ChangeMargin (MrcData, param, 0, 0, 1, 0, Rank, 0, 0, 0, 0, MrcRegFileCurrent);
      }
    }

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (chBitMask & (MRC_BIT0 << Channel)) {
        ChannelOut = &ControllerOut->Channel[Channel];
        RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank) ].Rank[Rank % 2];
        MRC_DEBUG_MSG (Debug, DebugLevel, "C%d.R%d:  Left\tRight\tWidth\tCenter\n", Channel, Rank);

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          LargestPS = &LargestPassingStart[Channel][Byte];
          LargestPE = &LargestPassingEnd[Channel][Byte];
          if (*LargestPS == *LargestPE) {
            // we like to see 0 margins when the eye closed ;)
            *LargestPS = *LargestPE = 0;
          }
          lWidth = *LargestPE - *LargestPS;
          Center = *LargestPS + (lWidth / 2);
          if (lWidth < (INT32) MinWidth) {
            EyeTooSmall[Channel][Rank] = TRUE;
            MRC_DEBUG_MSG (
              Debug,
              DebugLevel,
              "ERROR!! DataTimeCentering1D Eye Too Small Channel: %u, Rank: %u, Byte: %u\n",
              Channel,
              Rank,
              Byte
              );
            if (Inputs->ExitOnFailure) {
              Status = mrcDataTimeCentering1DErr;
            }
          }

          MRC_DEBUG_MSG (
            Debug,
            DebugLevel,
            "  B%d:   %d\t%d\t%d\t%d\n",
            Byte,
            *LargestPS,
            *LargestPE,
            lWidth,
            Center
            );

          //
          // Store the new margins relative to the center into MarginResult
          //
          Start = ABS ((*LargestPS - Center) * 10);
          End   = ABS ((*LargestPE - Center) * 10);
          if (param == RdT) {
            //
            // read Dq./Dqs
            //
            Margin                          = &Outputs->MarginResult[LastRxT][Rank][Channel][Byte][0];
            *Margin                         = Start;
            Margin[1]                       = End;
            ChannelOut->RxDqsP[Rank][Byte]  = (UINT8) ((INT32) ChannelOut->RxDqsP[Rank][Byte] + Center);
            ChannelOut->RxDqsN[Rank][Byte]  = (UINT8) ((INT32) ChannelOut->RxDqsN[Rank][Byte] + Center);
            UpdateRxT (MrcData, Channel, Rank, Byte, 0xFF, 0);
          } else if (param == WrT) {
            //
            // Write Dq/Dqs
            //
            Margin                        = &Outputs->MarginResult[LastTxT][Rank][Channel][Byte][0];
            *Margin                       = Start;
            Margin[1]                     = End;
            ChannelOut->TxDq[Rank][Byte]  = (UINT16) ((INT32) ChannelOut->TxDq[Rank][Byte] + Center);
            UpdateTxT (MrcData, Channel, Rank, Byte, 0xFF, 0);
          } else if (param == RcvEnaX) {
            //
            // Receive Enable
            //
            for (RankRx = 0; RankRx < MAX_RANK_IN_CHANNEL; RankRx++) {
              if (ChannelOut->ValidRankBitMask & (MRC_BIT0 << RankRx)) {
                Margin                          = &Outputs->MarginResult[LastRcvEna][RankRx][Channel][Byte][0];
                *Margin                         = Start;
                Margin[1]                       = End;
                ChannelOut->RcvEn[RankRx][Byte] = (ChannelOut->RcvEn[RankRx][Byte] + (UINT16) (4 * Center));
                UpdateRxT (MrcData, Channel, RankRx, Byte, 0xFF, 0);
              }
            }
          } else if (param == WrV) {
            //
            // Write Vref
            //
            Margin = &Outputs->MarginResult[LastTxV][Rank][Channel][Byte][0];
            if (Ddr4) {
              *Margin = Start;
              Margin[1] = End;
              RankOut->Ddr4PdaMr6[Byte] = MrcOffsetToVrefDq(MrcData, MrcVrefDqToOffset(RankOut->Ddr4PdaMr6[Byte] & 0x7F) + (INT8)Center, Channel);
            } else {
              //
              // Write Vref - NonPda
              //
              MarginSignReversed = &Outputs->MarginSignReversed[Rank][Channel][Byte][0];
              MarginSignReversed[0] = ((*LargestPS) > 0);
              MarginSignReversed[1] = ((*LargestPE) < 0);
              Margin[0] = ABS((*LargestPS) * 10);
              Margin[1] = ABS((*LargestPE) * 10);
            }
          } else if (param == RdV) {
            //
            // Read Vref
            //
            ChannelOut->RxVref[Byte]        = (UINT8) ((INT32) ChannelOut->RxVref[Byte] + Center / 2);
            for (RankRx = 0; RankRx < MAX_RANK_IN_CHANNEL; RankRx++) {
              Margin    = &Outputs->MarginResult[LastRxV][RankRx][Channel][Byte][0];
              *Margin   = Start;
              Margin[1] = End;
              UpdateRxT (MrcData, Channel, RankRx, Byte, 0xFF, 0);
            }
          } else if (param == CmdV) {
            //
            // Command Vref
            //
            Margin            = &Outputs->MarginResult[LastCmdV][Rank][Channel][Byte][0];
            Margin[0]         = ABS ((*LargestPS) * 10);
            Margin[1]         = ABS ((*LargestPE) * 10);
          }
        } // for Byte
      }
    } // for Channel
    if ((param == RdV) || (param == RcvEnaX)) {
      break; // We don't use different Rx vref per rank and RcvEnX already stress on all rank.
    }
  } // for Rank

  if (Ddr4WriteVrefParam) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        RankMask = (1 << Rank);
        if (ChannelOut->ValidRankBitMask & RankMask) {
          //
          // Program common center in Non PDA fashion in order to make sure the PDA is successful
          //
          UpdatePdaCenter (MrcData, RankMask);
          UpdateVrefWaitTilStable (MrcData, Channel, FALSE, 0, RankMask, 0, FALSE, 1); // UpdateHost = FALSE to keep per-byte MR6 values

          if (!EyeTooSmall[Channel][Rank]) {
            //
            // Write using PDA only when we have a passing window
            //
            UpdateVrefWaitTilStable (MrcData, Channel, TRUE, 0, RankMask, 0x1FF, TRUE, 1);
          }
        }
      }
    }
    Outputs->Ddr4PdaEnable = TRUE;
  }

  if (param == RcvEnaX) {
    // Cleanup after test
    IoReset (MrcData);
  }

  return Status;
}

/**
  This procedure is meant to handle much more complex centering that will use a 2D algorithm to optimize asymetical
  eyes for both timing and voltage margin.

  @param[in,out] MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Margin data from centering
  @param[in]     ChBitMaskIn     - Channel bit mask.
  @param[in]     param           - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                    8:WrTBit, 9:RdTBit, 10:RdVBit,
                                    16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                    ONLY RdT and WrT are allowed in this function
  @param[in]     EnPerBit        - Option to enable per bit margining
  @param[in]     EnRxDutyCycleIn - Phase to center.
  @param[in]     ResetPerBit     - Option to Reset PerBit Deskew to middle value before byte training
  @param[in]     LoopCount       - loop count
  @param[in]     En2D            - Option to only run center at nominal Vref point

  @retval MrcStatus -  If succeeded, return mrcSuccess
**/
MrcStatus
DataTimeCentering2D (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          ChBitMaskIn,
  IN     const UINT8          Param,
  IN     const UINT8          EnPerBit,
  IN     const UINT8          EnRxDutyCycleIn,
  IN     const UINT8          ResetPerBit,
  IN     const UINT8          LoopCount,
  IN     const UINT8          En2D
  )
{
  static const UINT32      EHWeights[]       = {6, 2, 1, 0, 2, 1, 0};
  static const UINT32      EWWeights[]       = {0, 1, 2, 3, 1, 2, 3};
  static const INT32       VrefPointsConst[] = {0, -6, -12, -18, 6, 12, 18};
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  UINT8             *RxDqPbCenter;
  UINT8             *TxDqPbCenter;
  UINT16            centerTiming;
  UINT32            *Margin;
  UINT32            *Eye;
  INT32             *CenterBit;
  INT32             *CSum;
  MrcStatus         Status;
  UINT8             ResultType;
  UINT8             Channel;
  UINT8             Rank;
  UINT16            Byte;
  UINT8             Bit;
  UINT8             ParamV;
  UINT8             ParamB;
  UINT8             MaxVScale;
  UINT8             EnPerBitEH;
  UINT8             Strobe;
  UINT8             Strobes;
  UINT8             Vref;
  UINT8             SaveLC;
  UINT8             LCloop;
  UINT8             i;
  UINT8             SkipWait;
  UINT8             ChBitMask;
  UINT8             EnRxDutyCycle;
  UINT8             Edge;
  UINT8             BMap[9];
  UINT8             LoopEnd;
  UINT16            Mode;
  UINT32            MarginBit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES];
  INT32             Center;
  UINT32            Weight;
  INT32             VrefPoints[sizeof (VrefPointsConst) / sizeof (VrefPointsConst[0]) ];
  UINT32            SumEH;
  UINT32            SumEW;
  UINT32            BERStats[4];
  UINT32            VrefScale[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32            EH[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32            EW[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32            EyeShape[7][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES]; // Store all eye edges for Per Bit
  UINT32            StrobeMargin[7][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][2][MAX_EDGES];//Save Edges per Strobe to pass Min (Stobe1, Strobe2)
  INT32             CenterSum[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             DivBy;
  INT8              DivBySign;
  INT32             Value0;
  UINT32            Offset;
  INT32             CenterSumBit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];
  INT32             Calc;
  BOOLEAN           Ddr4;
  BOOLEAN           PdaMode;
  MCHBAR_CH0_CR_REUT_CH_ERR_CTL_STRUCT  ReutChErrCtl;
  DDRDATA0CH0_CR_RXPERBITRANK0_STRUCT   CrPerBitRank;
#ifdef BDAT_SUPPORT
  UINT32            EyeType;
  UINT32            MarginValue;
#endif

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MrcCall = Inputs->Call.Func;
  //
  // 2D Margin Types (Voltage, Time)
  // RdFan2:  Margins both RdV and RdT at { (off, -2/3*off),  (off, 2/3*off) }
  // WrFan2:  Margins both WrV and WrT at { (off, -2/3*off),  (off, 2/3*off) }
  // RdFan3:  Margins both RdV and RdT at { (off, -2/3*off),  (5/4*off, 0),  (off, 2/3*off)  }
  // WrFan3:  Margins both WrV and WrT at { (off, -2/3*off),  (5/4*off, 0),  (off, 2/3*off)  }
  //
  if ((Param != RdT) && (Param != WrT)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DataTimeCentering2D: Incorrect Margin Parameter %d\n", Param);
    return mrcWrongInputParameter;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Parameter = %d (%sT)\n", Param, (Param == RdT) ? "Rd" : "Wr");
  ControllerOut = &Outputs->Controller[0];
  ChBitMask     = ChBitMaskIn;
  EnRxDutyCycle = EnRxDutyCycleIn;
  Status        = mrcSuccess;
  MaxVScale     = 24;
  Strobes       = 2;
  Center        = 0;
  Value0        = 0;
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  for (i = 0; i < (sizeof (BMap) / sizeof (BMap[0])); i++) {
    BMap[i] = i;
  }

  ResultType = GetMarginResultType (Param);

  EnPerBitEH = 1; // Repeat EH Measurement after byte training, before bit training
  //
  // SOE = 10b ( Stop on All Byte Groups Error )
  //
  SetupIOTestBasicVA (MrcData, ChBitMask, LoopCount - 1, NSOE, 0, 0, 8);
  Outputs->DQPat = RdRdTA;
  //
  // Duty cycle should be ONLY for Rx
  //
  if (Param != RdT) {
    EnRxDutyCycle = 0;
  }

  Strobes = 1 + EnRxDutyCycle;

  //
  // Option to only run center at nominal Vref point
  //
  if (En2D == 0) {
    MrcCall->MrcSetMem ((UINT8 *) &VrefPoints[0], sizeof (VrefPoints), 0);
  } else {
    MrcCall->MrcCopyMem ((UINT8 *) &VrefPoints[0], (UINT8 *) &VrefPointsConst[0], sizeof (VrefPoints));
  }
  //
  // Calculate SumEH / SumEW for use in weighting equations
  //
  SumEH = SumEW = 0;
  for (Vref = 0; Vref < sizeof (VrefPoints) / sizeof (VrefPoints[0]); Vref++) {
    SumEH += EHWeights[Vref];
    SumEW += EWWeights[Vref];

    //
    // Loop once at nominal Vref point
    //
    if (En2D == 0) {
      break;
    }
  }

  if (Param == RdT) {
    ParamV = RdV;
    ParamB = RdTBit;
  } else {
    ParamV = WrV;
    ParamB = WrTBit;
  }
  PdaMode = Ddr4 && (ParamV == WrV);
  //
  // Optimize timing per rank
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Optimization is per rank\n");
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    ChBitMask = 0;
    //
    // Select rank for REUT test
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((MRC_BIT0 << Channel) & ChBitMaskIn) {
        ChBitMask |= SelectReutRanks (MrcData, Channel, (MRC_BIT0 << Rank), 0);
        if ((MRC_BIT0 << Channel) & ChBitMask) {
          ChannelOut = &ControllerOut->Channel[Channel];
          //
          // Clear any old state in DataTrain Offset
          //
          MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
        }
      }
    }
    //
    // Continue if this rank does not exist on any of the channels
    //
    if (ChBitMask == 0) {
      continue;
    }
    //
    // Reset PerBit Deskew to middle value before byte training
    // Write timing offset for bit[x] of the DQ byte. Linear from 0-15, each step size is tQCLK/64
    // Read timing offset for bit[x] of the DQ byte. Linear from 0-15, each step size is tQCLK/64
    //
    if (ResetPerBit == 1) {
      Status = ChangeMargin (MrcData, ParamB, 0x88888888, 0, 1, 0, Rank, 0, 0, 1, 0, MrcRegFileRank);
    }

    //####################################################
    //######   Get EH to scale vref sample point by  #####
    //####################################################
    //
    // Pass the host last edges by reference
    // Get EH/VrefScale for the use in timing centering
    //
    if (En2D > 0) {
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCalling DQTimeCenterEH\n");
      Status = DQTimeCenterEH (
                 MrcData,
                 ChBitMask,
                 Rank,
                 ParamV,
                 MaxVScale,
                 BMap,
                 EH,
                 VrefScale,
                 BERStats
                 );
      if (Status != mrcSuccess) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\nDQTimeCenterEH FAILED - Using VrefScale = %d\n", MaxVScale);
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          MrcCall->MrcSetMemDword (&VrefScale[Channel][0], Outputs->SdramCount, MaxVScale);
        }
      }
    } else {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        MrcCall->MrcSetMemDword (&EH[Channel][0], Outputs->SdramCount, 1);
        MrcCall->MrcSetMemDword (&VrefScale[Channel][0], Outputs->SdramCount, 1);
      }
    }

    Status = GetMarginByte (MrcData, MarginResult, Param, Rank, (MRC_BIT0 << Rank));


    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank: %d", Rank);
    for (Strobe = 0; Strobe < Strobes; Strobe++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nStrobe: %d\n\nChannel\t\t0\t\t\t\t\t\t\t\t1\nByte\t\t", Strobe);
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", Byte);
        }
      }
      //####################################################
      //######   Measure Eye Width at all Vref Points  #####
      //####################################################
      //
      // Program Selective error checking for RX. if strobe = 0 then Check even else Check odd
      //
      if (EnRxDutyCycle) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {
            Offset = 2 + MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG +
              ((MCHBAR_CH1_CR_REUT_CH_ERR_CTL_REG - MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG) * Channel);
            MrcWriteCR8 (MrcData, Offset, (0x55 << Strobe));
          }
        }
      }
      //
      // Loop through all the Vref Points to Test
      //
      for (Vref = 0; Vref < sizeof (VrefPoints) / sizeof (VrefPoints[0]); Vref++) {
        //
        // Setup Vref Voltage for this point
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {
            SkipWait = (ChBitMask >> (Channel + 1)); // Skip if there are more channels

            LoopEnd = (UINT8) (((ParamV == RdV) || PdaMode) ? Outputs->SdramCount : 1);
            for (Byte = 0; Byte < LoopEnd; Byte++) {
              Value0 = (INT32) (VrefPoints[Vref] * VrefScale[Channel][Byte]) / MaxVScale;
              Status = ChangeMargin (
                         MrcData,
                         ParamV,
                         Value0,
                         0,
                         0,
                         Channel,
                         PdaMode ? (1 << Rank) : Rank,
                         PdaMode ? (1 << Byte) : Byte,
                         0,
                         0,
                         SkipWait,
                         MrcRegFileRank
                         );
            }
          }
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nVref = %d:\t", Value0);

        //
        // Run Margin Test
        //
        Mode = 0;
        Status = MrcGetBERMarginByte (
                   MrcData,
                   MarginResult,
                   ChBitMask,
                   Rank,
                   Rank,
                   Param,
                   Mode,
                   BMap,
                   1,
                   31,
                   0,
                   BERStats
                   );
        //
        // Store Results; Setup Vref Voltage for this point
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if ((ChBitMask & (MRC_BIT0 << Channel))) {

            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              Margin = &MarginResult[ResultType][Rank][Channel][Byte][0];
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "%3d %3d ",
                Margin[0],
                Margin[1]
                );

              Center = (INT32) (Margin[1] -*Margin);
              if (Vref == 0) {
                EW[Channel][Byte]         = (Margin[1] +*Margin) / 10;
                CenterSum[Channel][Byte]  = 0;
              }
              //
              // Calculate weight for this point
              //
              Weight = EHWeights[Vref] * EH[Channel][Byte] + EWWeights[Vref] * EW[Channel][Byte];
              CenterSum[Channel][Byte] += Weight * Center;
              //
              // Store Edges for Per Bit deskew
              //
              Eye = &EyeShape[Vref][Channel][Byte][0];
              for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                Eye[Edge] = Margin[Edge];
              }
              //
              // RunTime Improvement.  Set margin back to Vref = 0 point when the sign  of the VrefPoint changes
              //
              if ((VrefPoints[Vref] < 0) &&
                  (Vref < (sizeof (VrefPoints) / sizeof (VrefPoints[0]) - 1)) &&
                  (VrefPoints[Vref + 1] > 0)
                  ) {
                Eye = &EyeShape[0][Channel][Byte][0];
                for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                  Margin[Edge] = Eye[Edge];
                }
              }
            }
          }
        }
        //
        // Loop once at nominal Vref point
        //
        if (En2D == 0) {
          Vref = sizeof (VrefPoints) / sizeof (VrefPoints[0]);
        }
      }

      //####################################################
      //############    Center Results per Byte  ###########
      //####################################################
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nWeighted Center\t");

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          ChannelOut = &ControllerOut->Channel[Channel];

          //
          // Calculate and apply CenterPoint.  Round to Nearest Int
          //
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            DivBy = (SumEH * EH[Channel][Byte] + SumEW * EW[Channel][Byte]);
            if (DivBy == 0) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DataTimeCentering2D: Divide by zero\n");
              return mrcFail;
            }

            CSum      = &CenterSum[Channel][Byte];
            DivBySign = (*CSum < 0) ? (-1) : 1;

            *CSum     = (*CSum + 10 * (DivBySign * DivBy)) / (20 * DivBy);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", *CSum);

            //
            // Apply new centerpoint
            //
            if (Param == RdT) {
              if (Strobe == 0) {
                ChannelOut->RxDqsP[Rank][Byte] = (UINT8) ((INT32) ChannelOut->RxDqsP[Rank][Byte] +*CSum);
              }

              if ((!EnRxDutyCycle) || (Strobe == 1)) {
                ChannelOut->RxDqsN[Rank][Byte] = (UINT8) ((INT32) ChannelOut->RxDqsN[Rank][Byte] +*CSum);
                UpdateRxT (MrcData, Channel, Rank, (UINT8) Byte, 0xFF, 0);
              }
            } else {
              ChannelOut->TxDq[Rank][Byte] = (UINT16) ((INT32) ChannelOut->TxDq[Rank][Byte] +*CSum);
              UpdateTxT (MrcData, Channel, Rank, (UINT8) Byte, 0xFF, 0);
            }
            //
            // Update the Eye Edges
            //
            for (Vref = 0; Vref < sizeof (VrefPoints) / sizeof (VrefPoints[0]); Vref++) {
              Calc  = 10 **CSum;
              Eye   = &EyeShape[Vref][Channel][Byte][0];
              *Eye += Calc;
              Eye[1] -= Calc;

              //
              // Save Per Strobe Edges
              //
              for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                StrobeMargin[Vref][Channel][Byte][Strobe][Edge] = EyeShape[Vref][Channel][Byte][Edge];
              }
              //
              // Loop once at nominal Vref point
              //
              if (En2D == 0) {
                Vref = sizeof (VrefPoints) / sizeof (VrefPoints[0]);
              }
            }
            //
            // Update MrcData for future tests (MarginResult points back to MrcData)
            // EyeShape for Vref 0 is assumed to have the best shape for future tests.
            //
            for (Edge = 0; Edge < MAX_EDGES; Edge++) {
              MarginResult[ResultType][Rank][Channel][Byte][Edge] = EyeShape[0][Channel][Byte][Edge];
            }
          }
          //
          // Clean up after test
          //
          MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
        }
      }

      centerTiming = 0;
#ifdef MRC_DEBUG_PRINT
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nFinal Center\t");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          ChannelOut = &ControllerOut->Channel[Channel];

          //
          // Calculate final center point relative to "zero" as in the 1D case
          //
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (Param == RdT) {
              if (Strobe == 0) {
                centerTiming = (UINT8) (ChannelOut->RxDqsP[Rank][Byte] - 32);
              }

              if ((!EnRxDutyCycle) || (Strobe == 1)) {
                centerTiming = (UINT8) (ChannelOut->RxDqsN[Rank][Byte] - 32);
              }
            } else {
              centerTiming = ChannelOut->TxDq[Rank][Byte] - (ChannelOut->TxDqs[Rank][Byte] + 32);
            }

            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", (INT8) centerTiming);
          }
        }
      }
#endif // MRC_DEBUG_PRINT
    } // End of Byte Centering

    //######################################################
    //############     Measure Eye Width Per BIT  ##########
    //######################################################

    if (EnPerBit) {

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n### Measure Eye Width Per BIT\n");
      //
      // Recalculate the EH after the Byte Centering
      //
      if (EnPerBitEH && (En2D > 0)) {
        Status = DQTimeCenterEH (
                   MrcData,
                   ChBitMask,
                   Rank,
                   ParamV,
                   MaxVScale,
                   BMap,
                   EH,
                   VrefScale,
                   BERStats
                   );
        if (Status != mrcSuccess) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\nDQTimeCenterEH FAILED - Using VrefScale = %d\n", MaxVScale);
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            MrcCall->MrcSetMemDword (&VrefScale[Channel][0], Outputs->SdramCount, MaxVScale);
          }
        }
      }
      //
      // No stop on error or selective error cheking
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
          Offset = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG +
            ((MCHBAR_CH1_CR_REUT_CH_ERR_CTL_REG - MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG) * Channel);
          ReutChErrCtl.Data                                   = 0;
          ReutChErrCtl.Bits.Selective_Error_Enable_Cacheline  = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_Selective_Error_Enable_Cacheline_MAX;
          ReutChErrCtl.Bits.Selective_Error_Enable_Chunk      = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_Selective_Error_Enable_Chunk_MAX;
          ReutChErrCtl.Bits.Stop_On_Error_Control             = ALSOE;
          ReutChErrCtl.Bits.Stop_on_Nth_Error                 = 1;
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
      for (Vref = 0; Vref < sizeof (VrefPoints) / sizeof (VrefPoints[0]); Vref++) {
        //
        // Setup Vref Voltage for this point
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if ((ChBitMask & (MRC_BIT0 << Channel))) {

            SkipWait = (ChBitMask >> (Channel + 1)); // Skip if there are more channels
            //
            // Change Vref margin
            //
            LoopEnd = (UINT8) (((ParamV == RdV) || PdaMode) ? Outputs->SdramCount : 1);
            for (Byte = 0; Byte < LoopEnd; Byte++) {
              Value0 = (INT32) (VrefPoints[Vref] * VrefScale[Channel][Byte]) / MaxVScale;
              Status = ChangeMargin (
                         MrcData,
                         ParamV,
                         Value0,
                         0,
                         0,
                         Channel,
                         PdaMode ? (1 << Rank) : Rank,
                         PdaMode ? (1 << Byte) : Byte,
                         0,
                         0,
                         SkipWait,
                         MrcRegFileRank
                         );
            }
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Vref = %d\t", Channel, Value0);
          MrcCall->MrcSetMemDword (&MarginBit[Channel][0][0][0], MAX_SDRAM_IN_DIMM * MAX_BITS * MAX_EDGES, 8);
        }
        //
        // Run Margin Test; Loop through 2 times. Once at low loop count and Once at high loopcount. Improves runtime
        // @todo: Need loop count of 2 when not using BASICVA
        //
        for (LCloop = 0; LCloop < 1; LCloop++) {
          Outputs->DQPatLC  = (LCloop == 0) ? 1 : SaveLC;

          Mode = 0;
          Status = MrcGetMarginBit (MrcData, ChBitMask, Rank, MarginBit, EyeShape[Vref], ParamB, Mode, 15, TRUE);
        }
        //
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCSum      ");
        // Store Results
        // Setup Vref Voltage for this point
        //
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {

            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              //
              // Calculate weight for this point
              //
              Weight = EHWeights[Vref] * EH[Channel][Byte] + EWWeights[Vref] * EW[Channel][Byte];
              for (Bit = 0; Bit < MAX_BITS; Bit++) {
                Margin  = &MarginBit[Channel][Byte][Bit][0];
                CSum    = &CenterSumBit[Channel][Byte][Bit];

                Center = ((Margin[1] - 8) - (8 - *Margin));
                if (Vref == 0) {
                  *CSum = 0;
                }

                *CSum += Weight * Center;
                //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "% 4d", *CSum);
              }
              //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Weight %d  ", Weight);
            }
          }
        }
        //
        // Loop once at nominal Vref point
        //
        if (En2D == 0) {
          Vref = sizeof (VrefPoints) / sizeof (VrefPoints[0]);
        }
      }

      //######################################################
      //#############     Center Result Per BIT  #############
      //######################################################
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nWtd Ctr\t  ");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          ChannelOut = &ControllerOut->Channel[Channel];

          //
          // Cleanup after test - go back to the per byte setup
          //
          ReutChErrCtl.Data                                  = 0;
          ReutChErrCtl.Bits.Stop_on_Nth_Error                = 1;
          ReutChErrCtl.Bits.Stop_On_Error_Control            = NSOE;
          ReutChErrCtl.Bits.Selective_Error_Enable_Chunk     = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_Selective_Error_Enable_Chunk_MAX;
          ReutChErrCtl.Bits.Selective_Error_Enable_Cacheline = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_Selective_Error_Enable_Cacheline_MAX;
          Offset = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG +
            ((MCHBAR_CH1_CR_REUT_CH_ERR_CTL_REG - MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG) * Channel);
          MrcWriteCR (MrcData, Offset, ReutChErrCtl.Data);

          //
          // Calculate and apply CenterPoint.  Round to Nearest Int
          //
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            DivBy = (SumEH * EH[Channel][Byte] + SumEW * EW[Channel][Byte]);

            //
            // Make sure DivBy is never 0
            //
            if (DivBy == 0) {
              DivBy = 1;
            }

            CrPerBitRank.Data = 0;
            for (Bit = 0; Bit < MAX_BITS; Bit++) {
              CenterBit    = &CenterSumBit[Channel][Byte][Bit];
              RxDqPbCenter = &ChannelOut->RxDqPb[Rank][Byte][Bit].Center;
              TxDqPbCenter = &ChannelOut->TxDqPb[Rank][Byte][Bit].Center;

              DivBySign  = (*CenterBit < 0) ? (-1) : 1;
              *CenterBit = (*CenterBit + (DivBySign * DivBy)) / (2 * DivBy);

              //
              // Centerpoint needs to be added to starting DqPb value
              //
              *CenterBit += (Param == RdT) ? (INT32) *RxDqPbCenter : (INT32) *TxDqPbCenter;

              //
              // Check for saturation
              //
              if (*CenterBit > DDRDATA0CH0_CR_RXPERBITRANK0_Lane0_MAX) {
                *CenterBit = DDRDATA0CH0_CR_RXPERBITRANK0_Lane0_MAX;
              } else if (*CenterBit < 0) {
                *CenterBit = 0;
              }

              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "% 4x", *CenterBit);

              //
              // Update MrcData
              //
              if (Param == RdT) {
                *RxDqPbCenter = (UINT8) *CenterBit;
              } else {
                *TxDqPbCenter = (UINT8) *CenterBit;
              }

              CrPerBitRank.Data |= (*CenterBit << (4 * Bit));
            }
            //
            // Apply new centerpoint
            // ParamB already has the proper per bit parameter based on Param
            //
            Status = ChangeMargin (
                       MrcData,
                       ParamB,
                       CrPerBitRank.Data,
                       0,
                       0,
                       Channel,
                       Rank,
                       Byte,
                       0,
                       0,
                       0,
                       MrcRegFileRank
                       );

            //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " DivBy %d   ", DivBy);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "           ");
          }
          //
          // Clear any old state in DataTrain Offset
          //
          MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
        }
      }
      //
      // No stop on error or selective error cheking
      // Stop on all lane fail
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          //
          // SOE = 11b ( Stop on All Lanes Error )
          //
          ReutChErrCtl.Data                                  = 0;
          ReutChErrCtl.Bits.Stop_on_Nth_Error                = 1;
          ReutChErrCtl.Bits.Stop_On_Error_Control            = ALSOE;
          ReutChErrCtl.Bits.Selective_Error_Enable_Chunk     = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_Selective_Error_Enable_Chunk_MAX;
          ReutChErrCtl.Bits.Selective_Error_Enable_Cacheline = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_Selective_Error_Enable_Cacheline_MAX;
          Offset = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG +
            ((MCHBAR_CH1_CR_REUT_CH_ERR_CTL_REG - MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG) * Channel);
          MrcWriteCR (MrcData, Offset, ReutChErrCtl.Data);
        }
      }


      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          //
          // Cleanup after test
          //
          ReutChErrCtl.Data                                  = 0;
          ReutChErrCtl.Bits.Stop_on_Nth_Error                = 1;
          ReutChErrCtl.Bits.Stop_On_Error_Control            = NSOE;
          ReutChErrCtl.Bits.Selective_Error_Enable_Chunk     = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_Selective_Error_Enable_Chunk_MAX;
          ReutChErrCtl.Bits.Selective_Error_Enable_Cacheline = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_Selective_Error_Enable_Cacheline_MAX;
          Offset = MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG +
            ((MCHBAR_CH1_CR_REUT_CH_ERR_CTL_REG - MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG) * Channel);
          MrcWriteCR (MrcData, Offset, ReutChErrCtl.Data);
        }
      }
    }


#ifdef BDAT_SUPPORT
    if (Inputs->BdatEnable && (Inputs->BdatTestType == Margin2DType)) {
      if ((Param == RdT) || (Param == WrT)) {
        Outputs->NumCL = 128;
        EyeType = (Param == RdT) ? 0 : 1;
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!(ChBitMask & (MRC_BIT0 << Channel))) {
            continue;
          }
          for (Vref = 0; Vref < sizeof (VrefPoints) / sizeof (VrefPoints[0]); Vref++) {
            for (Edge = 0; Edge < MAX_EDGES; Edge++) {
              MarginValue = MRC_UINT32_MAX;
              for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
                MarginValue = MIN (MarginValue, (UINT8) EyeShape[Vref][Channel][Byte][Edge]);
              }
              Outputs->Margin2DResult[EyeType][Rank][Channel][Vref][Edge] = (UINT8) (MarginValue / 10);
            }
          }
        }
      }
    }
#endif

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  } //End of Rank


  //
  // Clean Up after test
  //
  if (Param == RdT) {
    IoReset (MrcData);
  }
  Byte = PdaMode ? 0x1FF : 0;
  Outputs->EnDumRd  = 0;
  Status            = ChangeMargin (MrcData, ParamV, 0, 0, 1, 0, 0, Byte, 0, 0, 0, MrcRegFileCurrent);
  return Status;
}

/**
  Subfunction of 2D Timing Centering
  Measures paramV margin across ch/bytes and updates the EH/VrefScale variables

  @param[in]     MrcData   - Include all MRC global data.
  @param[in]     ChBitMask - Channel Bit mak for which test should be setup for.
  @param[in]     rank      - Defines rank to used for MrcData
  @param[in]     ParamV    - Margin parameter
  @param[in]     MaxVScale - Maximum Voltage Scale to use
  @param[in]     BMap      - Byte mapping to configure error counter control register
  @param[in,out] EH        - Structure that stores start, stop and increment details for address
  @param[in,out] VrefScale - Parameter to be updated
  @param[in,out] BERStats  - Bit Error Rate Statistics.

  @retval mrcSuccess if successful, otherwise the function returns an error status.
**/
MrcStatus
DQTimeCenterEH (
  IN     MrcParameters * const MrcData,
  IN     const UINT8           ChBitMask,
  IN     const UINT8           rank,
  IN     const UINT8           ParamV,
  IN     const UINT8           MaxVScale,
  IN     UINT8 * const         BMap,
  IN OUT UINT32                EH[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN OUT UINT32                VrefScale[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN OUT UINT32 * const        BERStats
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput  *Inputs;
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  UINT32          *MarginResult;
  UINT32          *VrefS;
  MrcStatus       Status;
  UINT8           ResultType;
  UINT8           Channel;
  UINT8           Byte;
  UINT32          MinVrefScale;
  UINT16          Mode;
  UINT8           MaxVref;
  BOOLEAN         Ddr4Vref;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
#if (SUPPORT_DDR4 == SUPPORT)
  if ((Outputs->DdrType == MRC_DDR_TYPE_DDR4) && (ParamV == WrV)) {
    MaxVref = MAX_POSSIBLE_DDR4_WRITE_VREF;
    Ddr4Vref = TRUE;
  } else
#endif //SUPPORT_DDR4
  {
    MaxVref = MAX_POSSIBLE_VREF;
    Ddr4Vref = FALSE;
  }

  //
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DQTimeCenterEH:\n");
  // Run Margin Test
  //
  Mode    = 0;
  Status  = GetMarginByte (MrcData, Outputs->MarginResult, ParamV, rank, (MRC_BIT0 << rank));
  if (mrcSuccess == Status) {
    Status = MrcGetBERMarginByte (
               MrcData,
               Outputs->MarginResult,
               ChBitMask,
               Ddr4Vref ? (1 << rank) : rank,
               Ddr4Vref ? (1 << rank) : rank,
               ParamV,
               Mode,
               BMap,
               1,
               MaxVref,
               0,
               BERStats
               );
    if (mrcSuccess == Status) {
      Status = ScaleMarginByte (MrcData, Outputs->MarginResult, ParamV, rank);
      if (mrcSuccess == Status) {
        ResultType = GetMarginResultType (ParamV);

        //
        // Update VrefScale with results
        //
        for (Channel = 0; (Channel < MAX_CHANNEL) && (mrcSuccess == Status); Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {
            //
            // Calculate EH and VrefScale
            //
            MinVrefScale = MaxVScale;
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              MarginResult      = &Outputs->MarginResult[ResultType][rank][Channel][Byte][0];
              VrefS             = &VrefScale[Channel][Byte];
              EH[Channel][Byte] = (*MarginResult + *(MarginResult + 1)) / 10;
              *VrefS            = EH[Channel][Byte] / 2;

              if (*VrefS > MaxVScale) {
                *VrefS = MaxVScale;
              }

              if (MinVrefScale > *VrefS) {
                MinVrefScale = *VrefS;
              }
              //
              // Scale host back to correct values
              //
              Status = ScaleMarginByte (MrcData, Outputs->MarginResult, ParamV, rank);
              if (mrcSuccess != Status) {
                break;
              }
              //
              // For Tx, use the same Vref limit for all bytes. Store result in byte0
              //
              if (ParamV == WrV) {
                MrcCall->MrcSetMemDword (&VrefScale[Channel][0], Outputs->SdramCount, MinVrefScale);
              }
            }
          }
        }
      }
    }
  }
  //
  // Updates EH and VrefScale
  //
  return Status;
}

/**
  Update the Vref value
  if VrefType = 0, 3  Updates Ch0 Vref_Dq
  if VrefType = 1     Updates Ch1 Vref_Dq
  if VrefType = 2     Updates Vref_CA

  @param[in,out] MrcData       - Include all MRC global data.
  @param[in]     VrefType      - Determines the Vref to change
  @param[in]     UpdateMrcData - Used to decide if Mrc host must be updated
  @param[in]     Offset        - Vref value
  @param[in]     RankMask      - Selecting which Rank to talk to (only valid for DDR4 and adjusting VrefDQ)
  @param[in]     DeviceMask    - Selecting which Devices to talk to (only valid for DDR4 and adjusting VrefDQ)
  @param[in]     PDAmode       - Selecting to use MRH or old method for MRS (only valid for DDR4 and adjusting VrefDQ)
  @param[in]     SkipWait      - Determines if we will wait for vref to settle after writing to register

  @retval Nothing
**/
void
UpdateVrefWaitTilStable (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          VrefType,
  IN     const UINT8          UpdateMrcData,
  IN     INT32                Offset,
  IN     UINT8                RankMask,
  IN     UINT16               DeviceMask,
  IN     BOOLEAN              PDAmode,
  IN     UINT8                SkipWait
  )
{
  MrcDebug                                *Debug;
  MrcIntOutput                            *MrcIntData;
  MrcInput                                *Inputs;
  MrcOutput                               *Outputs;
  MrcIntControllerOut                     *IntControllerOut;
  UINT32                                  CheckMask;
  UINT8                                   OffH;
  UINT8                                   Count;
  DDRDATA7CH1_CR_DDRCRVREFADJUST1_STRUCT  DdrCrVrefAdjust;
  MrcChannelOut                           *ChannelOut;
  MrcRankOut                              *RankOut;
  UINT8                                   Channel;
  UINT8                                   Rank;
  UINT8                                   RankHalf;
  UINT8                                   RankMod2;
  UINT8                                   RankBit;
  DDR4_MODE_REGISTER_6_STRUCT             Ddr4Mr6;
  UINT8                                   Device;
  UINT8                                   VrefDq;
  INT8                                    CurrentOff;
  UINT8                                   Mr6Loop;
  UINT8                                   Ddr4;
  DDR4_MODE_REGISTER_5_STRUCT             Ddr4ModeRegister5;
  UINT16                                  OdtWrite;

  MrcIntData       = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs           = &MrcData->Inputs;
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  IntControllerOut = &MrcIntData->Controller[0];
  Ddr4             = (Outputs->DdrType ==  MRC_DDR_TYPE_DDR4);
  CheckMask        = 0;

#if (SUPPORT_DDR4 == SUPPORT)
  if ((VrefType < 2) && Ddr4) {
    Channel = VrefType;
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "UpdateVrefWaitTilStable called with channel %d Offset %d DeviceMask %d PDAmode %d UpdateMrcData %d DeviceMask %d, RankMask %d\n", Channel, Offset, DeviceMask, PDAmode, UpdateMrcData, DeviceMask, RankMask);
    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    RankMask   &= ChannelOut->ValidRankBitMask;
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      RankBit = 1 << Rank;
      if (RankMask & RankBit) {
        RankHalf = Rank / 2;
        RankMod2 = Rank % 2;
        RankOut = &ChannelOut->Dimm[RankHalf].Rank[RankMod2];
        Ddr4Mr6.Data = RankOut->MR[mrMR6];

        if (PDAmode) {

          // Dynamic Odt not supported in PDA - Park <- RttWr for target rank
          Ddr4ModeRegister5.Data = RankOut->MR[mrMR5];
          OdtWrite = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtWr, FALSE, 0);
          if (OdtWrite == 0xFFFF) {
            // for setting park to off
            OdtWrite = 0;
          }
          Ddr4ModeRegister5 = UpdateRttParkValue_DDR4 (MrcData, (UINT8) OdtWrite, Ddr4ModeRegister5);
          MrcWriteMRS (MrcData, Channel, RankBit, mrMR5, (UINT16) Ddr4ModeRegister5.Data);
          //
          // Send MR6 sequence for each device, using MRH with PDA mode.
          // MRH will go in/out of PDA mode automatically.
          //
          for (Device = 0; Device < Outputs->SdramCount; Device++) {
            if ((MRC_BIT0 << Device) & DeviceMask) {
              CurrentOff = MrcVrefDqToOffset (RankOut->Ddr4PdaMr6[Device] & 0x7F);
              VrefDq = MrcOffsetToVrefDq (MrcData, CurrentOff + (INT8) (Offset), Channel);

              // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "                            Dev %d VrefDQ 0x%x\n", Device, VrefDq);
              // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "                                        A6 %x\n", VrefDq >> 6);
              // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "                                A5:A0(bin) %x%x%x%x%x%x\n", (VrefDq & 0x20) >> 5, (VrefDq & 0x10) >> 4,
              //                              (VrefDq & 0x08) >> 3, (VrefDq & 0x04) >> 2, (VrefDq & 0x02) >> 1, (VrefDq & 0x01));
              Ddr4Mr6.Bits.VrefDqTrainingEnable = 1;
              Ddr4Mr6.Bits.VrefDqTrainingRange  = VrefDq >> 6;
              Ddr4Mr6.Bits.VrefDqTrainingValue  = VrefDq & 0x3F;

              for (Mr6Loop = 0; Mr6Loop < 3; Mr6Loop++) {
                if (Mr6Loop == 2) {
                  Ddr4Mr6.Bits.VrefDqTrainingEnable = 0;
                }
                MrcDdr4PdaCmd (MrcData, Channel, Rank, Ddr4Mr6.Data, mrMR6, (MRC_BIT0 << Device), TRUE);
                MrcWait (MrcData, tVREFDQ_MIN);
              }

              //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tPDAmode, Rank: %d, Dev: %d MR6.Data = 0x%x Offset=%d CurrentOff=%d\n", Rank, Device, Ddr4Mr6.Data, Offset, CurrentOff);
              if (UpdateMrcData) {
                RankOut->Ddr4PdaMr6[Device] = Ddr4Mr6.Data8[0];
                // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PDAmode, Ddr4Mr6.Data = %X Rank = %d\n",Ddr4Mr6.Data & 0x7F, Rank);
              }
            }
          }
          //
          // Restore RTT_PARK for this rank
          //
          MrcWriteMRS (MrcData, Channel, RankBit, mrMR5, RankOut->MR[mrMR5]);
          UpdatePdaCenter (MrcData, RankMask);
        } else { // non-PDA mode
          CurrentOff = MrcVrefDqToOffset ((UINT8) (RankOut->MR[mrMR6] & 0x7F));
          CurrentOff += (INT8) (Offset);
          //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tOffset=%d CurrentOff=%d ", Offset, CurrentOff);
          MrcSetTxVrefDdr4 (MrcData, Channel, Rank, CurrentOff, UpdateMrcData);
        } // if PDA
      }
    } // for Rank
  } else
#endif // SUPPORT_DDR4
  {
    // Calculate and write the new Vref offset value.
    switch (VrefType) {
      case 0:
        OffH = (UINT8) IntControllerOut->VrefAdjust1.Bits.Ch0VrefCtl;
        break;

      case 1:
      case 3: //@todo: if >RVP2 use TxVref ch B
        OffH = (UINT8) IntControllerOut->VrefAdjust1.Bits.Ch1VrefCtl;
        break;

      case 2:
        OffH = (UINT8) IntControllerOut->VrefAdjust1.Bits.CAVrefCtl;
        break;

      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "UpdateVrefWaitTilStable called with an incorrect value!\n");
        return;
    }

    Offset = Offset + (INT8) MrcSE (OffH, 7, 8); // Get offset from host. SE = Sign Extend number 7->8 bits
    if (Offset > MAX_POSSIBLE_VREF) {
      Offset =  MAX_POSSIBLE_VREF;
    } else if (Offset < (-1 * MAX_POSSIBLE_VREF)) {
      Offset = -1 * MAX_POSSIBLE_VREF;
    }

    if (UpdateMrcData) {
      switch (VrefType) {
        case 0:
          IntControllerOut->VrefAdjust1.Bits.Ch0VrefCtl = Offset;
          break;

        case 1:
        case 3:
          IntControllerOut->VrefAdjust1.Bits.Ch1VrefCtl = Offset;
          break;

        case 2:
          IntControllerOut->VrefAdjust1.Bits.CAVrefCtl = Offset;
          break;
      }
    }

    DdrCrVrefAdjust.Data = MrcReadCR (MrcData, MrcGetOffsetVrefAdjust1 (MrcData, 0, 0));
    switch (VrefType) {
      case 0:
        DdrCrVrefAdjust.Bits.Ch0VrefCtl     = Offset;
        DdrCrVrefAdjust.Bits.EnDimmVrefCh0  = 1;
        CheckMask                           = DDRDATA7CH1_CR_DDRCRVREFADJUST1_ch0SlowBW_MSK;
        break;

      case 1:
      case 3:
        DdrCrVrefAdjust.Bits.Ch1VrefCtl     = Offset;
        DdrCrVrefAdjust.Bits.EnDimmVrefCh1  = 1;
        CheckMask                           = DDRDATA7CH1_CR_DDRCRVREFADJUST1_ch1SlowBW_MSK;
        break;

      case 2:
        DdrCrVrefAdjust.Bits.CAVrefCtl      = Offset;
        DdrCrVrefAdjust.Bits.EnDimmVrefCA   = 1;
        CheckMask                           = DDRDATA7CH1_CR_DDRCRVREFADJUST1_caSlowBW_MSK;
        break;
    }

    MrcWriteCrMulticast (MrcData, MrcGetOffsetVrefAdjust1 (MrcData, 0, 0), DdrCrVrefAdjust.Data);
  }

  //
  // Wait for Vref to settle.  Note VrefCA needs longer to settle.
  //
  if (!SkipWait) {
    if (Ddr4 && (VrefType < 2)) {
      MrcWait (MrcData, tVREFDQ_MIN);
    } else {
      Count = 0;
      while (Count < 50) {
        //
        // Don't wait more than 50uS
        //
        if ((MrcReadCR (MrcData, MrcGetOffsetVrefAdjust1 (MrcData, 0, 0)) & CheckMask) == CheckMask) {
          break;
        }

        MrcWait (MrcData, 1 * HPET_1US);
        Count += 1;
      }

      if (Count >= 50) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "CAVref circuit failed to converge, \n");
      }

      MrcWait (MrcData, 5 * HPET_1US); // Add 5us to make sure everything is done
    }
  }
}

/**
  This function is used to move CMD/CTL/CLK/CKE PIs during training

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel to shift PI for
  @param[in]     Iteration  - Determines which PI to shift:
                              MrcIterationClock = 0
                              MrcIterationCmdN  = 1
                              MrcIterationCmdS  = 2
                              MrcIterationCke   = 3
                              MrcIterationCtl   = 4
                              MrcIterationCmdV  = 5
  @param[in]     RankMask   - Ranks to work on
  @param[in]     GroupMask  - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR3
  @param[in]     NewValue   - value to shift in case of CLK Iteration, New value for all other cases
  @param[in]     UpdateHost - Determines if MrcData structure is updated

  @retval Nothing
**/
void
ShiftPIforCmdTraining (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          Iteration,
  IN     const UINT8          RankMask,
  IN     const UINT8          GroupMask,
  IN     INT32                NewValue,
  IN     const UINT8          UpdateHost
  )
{
  const MrcInput                        *Inputs;
  MrcDebug                              *Debug;
  const MrcChannelIn                    *ChannelIn;
  MrcChannelOut                         *ChannelOut;
  MrcOutput                             *Outputs;
  UINT32                                Offset;
  UINT32                                ByteMask;
  UINT32                                BitOffset;
  UINT8                                 Rank;
  UINT8                                 LocalRankMask;
  UINT8                                 Group;
  UINT32                                Cke;
  UINT32                                CkeRankMapping;
  INT8                                  Shift;
  BOOLEAN                               Lpddr;
  DDRCLKCH0_CR_DDRCRCLKPICODE_STRUCT    ClkPiCode;
  DDRCKECH0_CR_DDRCRCMDPICODING_STRUCT  CkeCmdPiCoding;
  DDRCMDSCH0_CR_DDRCRCMDPICODING_STRUCT CmdSPiCoding;
  DDRCMDNCH0_CR_DDRCRCMDPICODING_STRUCT CmdNPiCoding;
  DDRCTLCH0_CR_DDRCRCTLPICODING_STRUCT  CtlPiCoding;

  Inputs     = &MrcData->Inputs;
  Outputs    = &MrcData->Outputs;
  Debug      = &Outputs->Debug;
  ChannelIn  = &Inputs->Controller[0].Channel[Channel];
  ChannelOut = &Outputs->Controller[0].Channel[Channel];
  Lpddr      = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);

  if (Iteration != MrcIterationClock) {
    if (NewValue < 0) {
      NewValue = 0;
    } else if (NewValue > 127) {
      NewValue = 127;
    }
  }

  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nShiftPIforCmdTraining: Iteration: %d, Channel: %d, RankMask: %d, GroupMask: %d, NewValue = 0x%x\n", Iteration, Channel, RankMask, GroupMask, NewValue);

  switch (Iteration) {
    case MrcIterationClock: // SHIFT CLOCK
      ClkPiCode.Data = 0;
      ByteMask  = 0x1FF;    // Shift DQ PI on all 9 bytes by default on DDR3
      LocalRankMask = RankMask;
      if (Inputs->Ddr4DdpSharedClock) { // CLK0 is shared between Rank0 and Rank1
        if (RankMask & (1 << 1)) {      // If Rank1 is selected,
          LocalRankMask |= (1 << 0);    // then select Rank0 as well, for CLK PI shift
        }
      }

      if (Lpddr) {
        //
        // In LPDDR clocks are per group, not per rank
        //
        for (Group = 0; Group < 2; Group++) {
          BitOffset = DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_WID * Group;
          if (GroupMask & (1 << Group)) {
            Shift = (ChannelOut->ClkPiCode[Group] + NewValue) % 128;
            if (Shift < 0) {
              Shift = (128 - ABS (Shift));
            }

            Shift &= DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MSK;
            if (UpdateHost) {
              ChannelOut->ClkPiCode[Group] = Shift;
            }

            ClkPiCode.Data += (Shift << BitOffset);
            //
            // Each clock spans all ranks, so need to shift DQ PIs on all ranks, for bytes in this group only
            //
            ByteMask = ChannelIn->DQByteMap[MrcIterationClock][Group];
            for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
              if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
                ShiftDQPIs (MrcData, Channel, Rank, ByteMask, (INT8) NewValue, UpdateHost);
              }
            }
          } else {
            ClkPiCode.Data += (ChannelOut->ClkPiCode[Group] << BitOffset);
          }
        } // for Group
      } else {
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          BitOffset = DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_WID * Rank;
          if (LocalRankMask & (1 << Rank)) {
            Shift = (ChannelOut->ClkPiCode[Rank] + NewValue) % 128;
            if (Shift < 0) {
              Shift = (128 - ABS (Shift));
            }

            Shift &= DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MSK;
            if (UpdateHost) {
              ChannelOut->ClkPiCode[Rank] = Shift;
            }

            ClkPiCode.Data += (Shift << BitOffset);
            if (LocalRankMask & (1 << Rank)) {
              ShiftDQPIs (MrcData, Channel, Rank, ByteMask, (INT8) NewValue, UpdateHost);
            }
          } else {
            ClkPiCode.Data += (ChannelOut->ClkPiCode[Rank] << BitOffset);
          }
        }
      }

      Offset = DDRCLKCH0_CR_DDRCRCLKPICODE_REG + ((DDRCLKCH1_CR_DDRCRCLKPICODE_REG - DDRCLKCH0_CR_DDRCRCLKPICODE_REG) * Channel);
      MrcWriteCR (MrcData, Offset, ClkPiCode.Data);
      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "**** ShiftPIforCmdTraining, Iteration = %d, CRValue = 0x%x ****\n", Iteration,CRValue);
      break;

    case MrcIterationCmdN: // SHIFT COMMAND NORTH
      CmdNPiCoding.Data = 0;
      NewValue = MIN (NewValue, DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX);
      //
      // LPDDR3: CMDN.CmdPi1Code controls CAB
      // DDR3L/DDR4:  Both CmdPi0Code and CmdPi1Code should have the same value
      //
      CmdNPiCoding.Bits.CmdPi0Code = NewValue;
      CmdNPiCoding.Bits.CmdPi1Code = NewValue;
      Offset = DDRCMDNCH0_CR_DDRCRCMDPICODING_REG +
        ((DDRCMDNCH1_CR_DDRCRCMDPICODING_REG - DDRCMDNCH0_CR_DDRCRCMDPICODING_REG) * Channel);
      MrcWriteCR (MrcData, Offset, CmdNPiCoding.Data);
      if (UpdateHost) {
        ChannelOut->CmdnCmdPiCode[0] = NewValue;
        ChannelOut->CmdnCmdPiCode[1] = NewValue;
      }
      break;

    case MrcIterationCmdS: // SHIFT COMMAND SOUTH
      CmdSPiCoding.Data = 0;
      NewValue = MIN (NewValue, DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX);
      //
      // LPDDR3: CMDS.CmdPi0Code controls CAA, CMDS.CmdPi1Code controls CAB
      // DDR3L/DDR4:  Both CmdPi0Code and CmdPi1Code should have the same value
      //
      if (Lpddr) {
        CmdSPiCoding.Bits.CmdPi0Code = (GroupMask & 1) ? (UINT32) NewValue : ChannelOut->CmdsCmdPiCode[0]; // CAA
        CmdSPiCoding.Bits.CmdPi1Code = (GroupMask & 2) ? (UINT32) NewValue : ChannelOut->CmdsCmdPiCode[1]; // CAB
      } else {
        CmdSPiCoding.Bits.CmdPi0Code = NewValue;
        CmdSPiCoding.Bits.CmdPi1Code = NewValue;

        CkeCmdPiCoding.Data             = 0;
        NewValue                        = MIN (NewValue, DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX);
        CkeCmdPiCoding.Bits.CmdPi0Code  = NewValue;
        CkeCmdPiCoding.Bits.CmdPi1Code  = NewValue;
        Offset = DDRCKECH0_CR_DDRCRCMDPICODING_REG +
          ((DDRCKECH1_CR_DDRCRCMDPICODING_REG - DDRCKECH0_CR_DDRCRCMDPICODING_REG) * Channel);
        MrcWriteCR (MrcData, Offset, CkeCmdPiCoding.Data);
        if (UpdateHost) {
          ChannelOut->CkeCmdPiCode[0] = NewValue;
          ChannelOut->CkeCmdPiCode[1] = NewValue;
        }
      }

      if (UpdateHost) {
        ChannelOut->CmdsCmdPiCode[0] = CmdSPiCoding.Bits.CmdPi0Code;
        ChannelOut->CmdsCmdPiCode[1] = CmdSPiCoding.Bits.CmdPi1Code;
      }

      Offset = DDRCMDSCH0_CR_DDRCRCMDPICODING_REG +
        ((DDRCMDSCH1_CR_DDRCRCMDPICODING_REG - DDRCMDSCH0_CR_DDRCRCMDPICODING_REG) * Channel);
      MrcWriteCR (MrcData, Offset, CmdSPiCoding.Data);
      break;

    case MrcIterationCke: // Shift CKE command
      CkeCmdPiCoding.Data = 0;
      NewValue            = MIN (NewValue, DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX);
      //
      // LPDDR3: CKE.CmdPi0Code controls CAA
      // DDR3L/DDR4:  Both CmdPi0Code and CmdPi1Code should have the same value
      //
      CkeCmdPiCoding.Bits.CmdPi0Code = NewValue;
      CkeCmdPiCoding.Bits.CmdPi1Code = NewValue;
      Offset = DDRCKECH0_CR_DDRCRCMDPICODING_REG +
        ((DDRCKECH1_CR_DDRCRCMDPICODING_REG - DDRCKECH0_CR_DDRCRCMDPICODING_REG) * Channel);
      MrcWriteCR (MrcData, Offset, CkeCmdPiCoding.Data);
      if (UpdateHost) {
        ChannelOut->CkeCmdPiCode[0] = NewValue;
        ChannelOut->CkeCmdPiCode[1] = NewValue;
      }
      break;

    case MrcIterationCtl: // Shift CS/ODT and CKE.Control
      CtlPiCoding.Data = 0;
      NewValue         = MIN (NewValue, DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MAX);
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (RankMask & (1 << Rank)) {
          CtlPiCoding.Data += (NewValue << (DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_WID * Rank));
          if (UpdateHost) {
            ChannelOut->CtlPiCode[Rank] = (UINT8) NewValue;
            ChannelOut->CkePiCode[Rank] = (UINT8) NewValue;
          }
        } else {
          CtlPiCoding.Data += (ChannelOut->CtlPiCode[Rank] << (DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_WID * Rank));
        }
      }
      if (Lpddr && Outputs->LpddrDramOdt) {
        //
        // ODT[0] (equal to CS[0] PI setting) goes in to CTL.CtlPiCode2
        //
        CtlPiCoding.Bits.CtlPiCode2 = ChannelOut->CtlPiCode[0];
      }

      Offset = DDRCTLCH0_CR_DDRCRCTLPICODING_REG +
        ((DDRCTLCH1_CR_DDRCRCTLPICODING_REG - DDRCTLCH0_CR_DDRCRCTLPICODING_REG) * Channel);
      MrcWriteCR (MrcData, Offset, CtlPiCoding.Data);

      if (Lpddr) {
        CtlPiCoding.Data = 0;
        //
        // Use CKE-to-Rank mapping: [3:0] - Channel 0, [7:4] - Channel 1
        //
        CkeRankMapping = (Inputs->CkeRankMapping >> (Channel * 4)) & 0x0F;
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          for (Cke = 0; Cke <= 3; Cke++) {
            if (((CkeRankMapping >> Cke) & 1) == Rank) {
              //
              // This CKE pin is connected to this Rank
              //
              if (UpdateHost) {
                CtlPiCoding.Data += (ChannelOut->CkePiCode[Rank] << (DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_WID * Cke));
              } else {
                CtlPiCoding.Data += (NewValue << (DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_WID * Cke));
              }
            }
          }
        }
        //
        // Put average of CKE2 and CKE3 into CKE2 PI setting.
        //
        CtlPiCoding.Bits.CtlPiCode2 = (CtlPiCoding.Bits.CtlPiCode2 + CtlPiCoding.Bits.CtlPiCode3) / 2;
      }
      Offset = DDRCKECH0_CR_DDRCRCTLPICODING_REG +
        ((DDRCKECH1_CR_DDRCRCTLPICODING_REG - DDRCKECH0_CR_DDRCRCTLPICODING_REG) * Channel);
      CtlPiCoding.Bits.CtlPiCode3 = 0;  // Do not write PiCode3
      MrcWriteCR (MrcData, Offset, CtlPiCoding.Data);
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING...Unknown parameter to shift\n");
      break;
  }

  return;
}

/**
  Finds the limit that PIs can be adjusted to the left and right for a specific channel
  This compares CMD and CTL PIs.
  No need to compare CLK, because CLK PI can wrap around.

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel to check.
  @param[in]     RankMask   - Ranks to check.
  @param[out]    MinPi      - Minimum PI value across all bytes. This value may be NULL.
  @param[out]    MaxPi      - Maximum PI value across all bytes. This value may be NULL.

  @retval Nothing
**/
void
FindNormalizationPiLimits (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          RankMask,
  OUT          UINT16         *MinPi,
  OUT          UINT16         *MaxPi
  )
{
  MrcOutput             *Outputs;
  MrcDebug              *Debug;
  MrcChannelOut         *ChannelOut;
  UINT16                MinValue;
  UINT16                MaxValue;
  UINT8                 Rank;
  BOOLEAN               Lpddr;

  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  MinValue = DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX;
  MaxValue = DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN;

  MinValue = (UINT16) MIN (MinValue, ChannelOut->CkeCmdPiCode[0]);
  MaxValue = (UINT16) MAX (MaxValue, ChannelOut->CkeCmdPiCode[0]);
  MinValue = (UINT16) MIN (MinValue, ChannelOut->CmdsCmdPiCode[0]);
  MaxValue = (UINT16) MAX (MaxValue, ChannelOut->CmdsCmdPiCode[0]);

  if (Lpddr) {
    MinValue = (UINT16) MIN (MinValue, ChannelOut->CmdsCmdPiCode[1]);
    MaxValue = (UINT16) MAX (MaxValue, ChannelOut->CmdsCmdPiCode[1]);
    MinValue = (UINT16) MIN (MinValue, ChannelOut->CmdnCmdPiCode[1]);
    MaxValue = (UINT16) MAX (MaxValue, ChannelOut->CmdnCmdPiCode[1]);
  } else {
    MinValue = (UINT16) MIN (MinValue, ChannelOut->CmdnCmdPiCode[0]);
    MaxValue = (UINT16) MAX (MaxValue, ChannelOut->CmdnCmdPiCode[0]);
  }

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (MrcRankInChannelExist (MrcData, Rank, Channel) && (RankMask & (1 << Rank))) {
      MinValue = MIN (MinValue, ChannelOut->CkePiCode[Rank]);
      MaxValue = MAX (MaxValue, ChannelOut->CkePiCode[Rank]);
      MinValue = MIN (MinValue, ChannelOut->CtlPiCode[Rank]);
      MaxValue = MAX (MaxValue, ChannelOut->CtlPiCode[Rank]);
    }
  }

  if (MinPi != NULL) {
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%dR%d, MinPi = %d\n", Channel, Rank, MinValue);
    *MinPi = MinValue;
  }
  if (MaxPi != NULL) {
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%dR%d, MaxPi = %d\n", Channel, Rank, MaxValue);
    *MaxPi = MaxValue;
  }
}

/**
  Finds the limit that clock can be adjusted for a specific channel
  Compares TxDq, TxDqs and RcvEn values

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel to check.
  @param[in]     RankMask   - Ranks to check.
  @param[out]    MinPi      - Minimum PI value across all bytes. This value may be NULL.
  @param[out]    MaxPi      - Maximum PI value across all bytes. This value may be NULL.

  @retval Nothing
**/
void
FindDqPiLimits (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          RankMask,
  OUT          UINT16         *MinPi,
  OUT          UINT16         *MaxPi
  )
{
  MrcOutput             *Outputs;
  MrcDebug              *Debug;
  MrcChannelOut         *ChannelOut;
  UINT16                MinValue;
  UINT16                MaxValue;
  UINT8                 Rank;
  UINT8                 Byte;

  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];

  MinValue = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX;
  MaxValue = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MIN;
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (MrcRankInChannelExist (MrcData, Rank, Channel) && (RankMask & (1 << Rank))) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MinValue = MIN (ChannelOut->TxDq[Rank][Byte], MinValue);
        MinValue = MIN (ChannelOut->TxDqs[Rank][Byte], MinValue);
        MinValue = MIN (ChannelOut->RcvEn[Rank][Byte], MinValue);
        MaxValue = MAX (ChannelOut->TxDq[Rank][Byte], MaxValue);
        MaxValue = MAX (ChannelOut->TxDqs[Rank][Byte], MaxValue);
        MaxValue = MAX (ChannelOut->RcvEn[Rank][Byte], MaxValue);
      }
    }
  }

  if (MinPi != NULL) {
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%d-RankMask:0x%8x, MinPi = %d\n", Channel, RankMask, MinValue);
    *MinPi = MinValue;
  }
  if (MaxPi != NULL) {
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%d-RankMask:0x%8x, MaxPi = %d\n", Channel, RankMask, MaxValue);
    *MaxPi = MaxValue;
  }
}

/**
  Shifts RcvEn, WriteLevel and WriteDQS timing for all bytes
  Usually used when moving the clocks on a channel

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel to update
  @param[in]     Rank       - Rank to update
  @param[in]     ByteMask   - Bytes to update
  @param[in]     Offset     - value to shift
  @param[in]     UpdateHost - Determines if MrcData structure is updated

  @retval Nothing
**/
void
ShiftDQPIs (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          Rank,
  IN     const UINT32         ByteMask,
  IN     const INT8           Offset,
  IN     const UINT8          UpdateHost
  )
{
  MrcOutput                           *Outputs;
  MrcChannelOut                       *ChannelOut;
  UINT8                               Byte;
  UINT16                              RcvEnValue;
  UINT32                              TxDqValue;
  UINT32                              TxDqsValue;
  DDRDATA0CH0_CR_TXTRAINRANK0_STRUCT  CrTxTrainRank;
  MrcDebug                            *Debug;

  Outputs     = &MrcData->Outputs;
  Debug       = UpdateHost ? &Outputs->Debug : NULL;  // Don't show clip warnings when sweeping in RMT
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];

  for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
    if (((1 << Byte) & ByteMask) == 0) {
      continue;
    }

    RcvEnValue = ChannelOut->RcvEn[Rank][Byte] + Offset;
    if ((INT16) RcvEnValue < 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING: RcvEn PI truncated at %s!\n", "zero");
      RcvEnValue = 0;   // Don't go below zero
    } else if (RcvEnValue > DDRDATA_CR_RXTRAINRANK0_RxRcvEnPi_MAX) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING: RcvEn PI truncated at %s!\n", "max");
      RcvEnValue = DDRDATA_CR_RXTRAINRANK0_RxRcvEnPi_MAX;   // Don't go above max
    }

    UpdateRxT (MrcData, Channel, Rank, Byte, 0, RcvEnValue);

    TxDqValue = ChannelOut->TxDq[Rank][Byte] + Offset;
    if ((INT32) TxDqValue < 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING: TxDq PI truncated at %s!\n", "zero");
      TxDqValue = 0;   // Don't go below zero
    } else if (TxDqValue > DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING: TxDq PI truncated at %s!\n", "max");
      TxDqValue = DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX;   // Don't go above max
    }

    TxDqsValue = ChannelOut->TxDqs[Rank][Byte] + Offset;
    if ((INT32) TxDqsValue < 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING: TxDqs PI truncated at %s!\n", "zero");
      TxDqsValue = 0;   // Don't go below zero
    } else if (TxDqsValue > DDRDATA_CR_TXTRAINRANK0_TxDqsDelay_MAX) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING: TxDqs PI truncated at %s!\n", "max");
      TxDqsValue = DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX;   // Don't go above max
    }

    CrTxTrainRank.Data                = 0;
    CrTxTrainRank.Bits.TxEqualization = ChannelOut->TxEq[Rank][Byte];
    CrTxTrainRank.Bits.TxDqsDelay     = TxDqsValue;
    CrTxTrainRank.Bits.TxDqDelay      = TxDqValue;
    UpdateTxT (MrcData, Channel, Rank, Byte, 3, CrTxTrainRank.Data);

    if (UpdateHost) {
      ChannelOut->RcvEn[Rank][Byte] = RcvEnValue;
      ChannelOut->TxDqs[Rank][Byte] = (UINT16) TxDqsValue;
      ChannelOut->TxDq[Rank][Byte]  = (UINT16) TxDqValue;
    }
  }

  return;
}

/**
  Retrieve the current memory frequency and clock from the memory controller.

  @param[in]      MrcData      - Include all MRC global data.
  @param[in, out] MemoryClock  - The current memory clock.
  @param[in, out] Ratio        - The current memory ratio setting.
  @param[in, out] RefClk       - The current memory reference clock.
  @param[in, out] OddRatioMode - The current QCLK Odd Ratio mode.

  @retval: The current memory frequency.
**/
MrcFrequency
MrcGetCurrentMemoryFrequency (
  MrcParameters * const   MrcData,
  UINT32 * const          MemoryClock,
  MrcClockRatio * const   Ratio,
  MrcRefClkSelect * const RefClk,
  BOOLEAN * const         OddRatioMode
  )
{
  const MrcInput                 *Inputs;
  const MrcOutput                *Outputs;
  PCU_CR_MC_BIOS_DATA_PCU_STRUCT McBiosData;
  PCU_CR_MC_BIOS_REQ_PCU_STRUCT  McBiosReqPcu;
  MrcClockRatio                  MemoryRatio;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  McBiosReqPcu.Data = MrcReadCR (MrcData, PCU_CR_MC_BIOS_REQ_PCU_REG);
  McBiosData.Data   = MrcReadCR (MrcData, PCU_CR_MC_BIOS_DATA_PCU_REG);

  MemoryRatio = (UINT8) McBiosData.Bits.MC_FREQ;
  MemoryRatio |= (Outputs->ExtendedDdrOverclock) ? (UINT8) (McBiosData.Bits.MC_FREQ_MSB << PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_WID) : 0;

  if (MemoryClock != NULL) {
    *MemoryClock = MrcRatioToClock (MrcData, MemoryRatio, McBiosReqPcu.Bits.REQ_TYPE, Inputs->BClkFrequency);
  }
  if (Ratio != NULL) {
    *Ratio = MemoryRatio;
  }
  if (RefClk != NULL) {
    *RefClk = (MrcRefClkSelect) McBiosReqPcu.Bits.REQ_TYPE;
  }
  if (OddRatioMode != NULL) {
    *OddRatioMode = (BOOLEAN) McBiosData.Bits.QCLK_ODD_RATIO;
  }
  return MrcRatioToFrequency (
           MrcData,
           MemoryRatio,
           McBiosReqPcu.Bits.REQ_TYPE,
           Inputs->BClkFrequency
           );
}

/**
  Writes to the RxOffsetVdq Broadcast register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel to write to (0xFF to use the broadcast)
  @param[in]   Rank    - Rank to write to (0xFF to use the broadcast)
  @param[in]   Value   - Value to write

**/
void
MrcSetRxOffsetVdqBroadcast (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Rank,
  IN const UINT32          Value
  )
{
  UINT32                        Offset;
  UINT32                        RankOffset;
  UINT8                         Index;
  UINT8                         StartRank;
  UINT8                         StopRank;

  RankOffset = DDRDATA_CR_RXOFFSETVDQRANK1_REG - DDRDATA_CR_RXOFFSETVDQRANK0_REG;
  if (Rank == 0xFF) {
    StartRank = 0;
    StopRank = MAX_RANK_IN_CHANNEL;
  } else {
    StartRank = Rank;
    StopRank = Rank + 1;
  }

  if (Channel == 0) {
    Offset = DDRDATACH0_CR_RXOFFSETVDQRANK0_REG;
  } else if (Channel == 1) {
    Offset = DDRDATACH1_CR_RXOFFSETVDQRANK0_REG;
  } else {
    Offset = DDRDATA_CR_RXOFFSETVDQRANK0_REG;
  }

  for (Index = StartRank; Index < StopRank; Index++) {
    MrcWriteCrMulticast (MrcData, Offset + Index * RankOffset, Value);
  }
}

/**
  Writes to the RxOffsetVdq specific registers

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel to write to
  @param[in]   Rank    - Rank to write to
  @param[in]   Byte    - Byte to write to
  @param[in]   Value   - Value to write

**/
void
MrcSetRxOffsetVdq (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Rank,
  IN const UINT8           Byte,
  IN const UINT32          Value
  )
{
  UINT32  Offset;

  Offset = DDRDATA0CH0_CR_RXOFFSETVDQRANK0_REG +
    ((DDRDATA0CH1_CR_RXOFFSETVDQRANK0_REG - DDRDATA0CH0_CR_RXOFFSETVDQRANK0_REG) * Channel) +
    ((DDRDATA0CH0_CR_RXOFFSETVDQRANK1_REG - DDRDATA0CH0_CR_RXOFFSETVDQRANK0_REG) * Rank) +
    ((DDRDATA1CH0_CR_RXOFFSETVDQRANK0_REG - DDRDATA0CH0_CR_RXOFFSETVDQRANK0_REG) * Byte);

  MrcWriteCR (MrcData, Offset, Value);

}

/**
  Returns the Offset for DataTrainFeedback register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetDataTrainFeedback (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  )
{
  UINT32  Offset;

  if (Channel >= MAX_CHANNEL) {
    //
    // Overall Broadcast
    //
    Offset = DDRDATA_CR_DATATRAINFEEDBACK_REG;
  } else if (Byte >= MAX_SDRAM_IN_DIMM) {
    //
    // Channel Broadcast
    //
    Offset = DDRDATACH0_CR_DATATRAINFEEDBACK_REG +
      ((DDRDATACH1_CR_DATATRAINFEEDBACK_REG - DDRDATACH0_CR_DATATRAINFEEDBACK_REG) * Channel);
  } else {
    //
    // Specific Channel and Byte
    //
    Offset = DDRDATA0CH0_CR_DATATRAINFEEDBACK_REG +
      ((DDRDATA0CH1_CR_DATATRAINFEEDBACK_REG - DDRDATA0CH0_CR_DATATRAINFEEDBACK_REG) * Channel) +
      ((DDRDATA1CH0_CR_DATATRAINFEEDBACK_REG - DDRDATA0CH0_CR_DATATRAINFEEDBACK_REG) * Byte);
  }

  return Offset;

}

/**
  Returns the Offset for DllPiTestAndAdc register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetDllPiTestAndAdc (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  )
{
  UINT32  Offset;

  if (Channel >= MAX_CHANNEL) {
    //
    // Overall Broadcast
    //
    Offset = DDRDATA_CR_DLLPITESTANDADC_REG;
  } else if (Byte >= MAX_SDRAM_IN_DIMM) {
    //
    // Channel Broadcast
    //
    Offset = DDRDATACH0_CR_DLLPITESTANDADC_REG +
      ((DDRDATACH1_CR_DLLPITESTANDADC_REG - DDRDATACH0_CR_DLLPITESTANDADC_REG) * Channel);
  } else {
    //
    // Specific Channel and Byte
    //
    Offset = DDRDATA0CH0_CR_DLLPITESTANDADC_REG +
      ((DDRDATA0CH1_CR_DLLPITESTANDADC_REG - DDRDATA0CH0_CR_DLLPITESTANDADC_REG) * Channel) +
      ((DDRDATA1CH0_CR_DLLPITESTANDADC_REG - DDRDATA0CH0_CR_DLLPITESTANDADC_REG) * Byte);
  }

  return Offset;

}

/**
  Returns the Offset for DataOffsetComp register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetDataOffsetComp (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  )
{
  UINT32  Offset;

  if (Channel >= MAX_CHANNEL) {
    //
    // Overall Broadcast
    //
    Offset = DDRDATA_CR_DDRCRDATAOFFSETCOMP_REG;
  } else if (Byte >= MAX_SDRAM_IN_DIMM) {
    //
    // Channel Broadcast
    //
    Offset = DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_REG +
      ((DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_REG - DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_REG) * Channel);
  } else {
    //
    // Specific Channel and Byte
    //
    Offset = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG +
      ((DDRDATA0CH1_CR_DDRCRDATAOFFSETCOMP_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG) * Channel) +
      ((DDRDATA1CH0_CR_DDRCRDATAOFFSETCOMP_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG) * Byte);
  }

  return Offset;

}

/**
  Returns the Offset for DataControl0 register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetDataControl0 (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  )
{
  UINT32  Offset;

  if (Channel >= MAX_CHANNEL) {
    //
    // Overall Broadcast
    //
    Offset = DDRDATA_CR_DDRCRDATACONTROL0_REG;
  } else if (Byte >= MAX_SDRAM_IN_DIMM) {
    //
    // Channel Broadcast
    //
    Offset = DDRDATACH0_CR_DDRCRDATACONTROL0_REG +
      ((DDRDATACH1_CR_DDRCRDATACONTROL0_REG - DDRDATACH0_CR_DDRCRDATACONTROL0_REG) * Channel);
  } else {
    //
    // Specific Channel and Byte
    //
    Offset = DDRDATA0CH0_CR_DDRCRDATACONTROL0_REG +
      ((DDRDATA0CH1_CR_DDRCRDATACONTROL0_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL0_REG) * Channel) +
      ((DDRDATA1CH0_CR_DDRCRDATACONTROL0_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL0_REG) * Byte);
  }

  return Offset;

}

/**
  Returns the Offset for DataControl1 register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetDataControl1 (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  )
{
  UINT32  Offset;

  if (Channel >= MAX_CHANNEL) {
    //
    // Overall Broadcast
    //
    Offset = DDRDATA_CR_DDRCRDATACONTROL1_REG;
  } else if (Byte >= MAX_SDRAM_IN_DIMM) {
    //
    // Channel Broadcast
    //
    Offset = DDRDATACH0_CR_DDRCRDATACONTROL1_REG +
      ((DDRDATACH1_CR_DDRCRDATACONTROL1_REG - DDRDATACH0_CR_DDRCRDATACONTROL1_REG) * Channel);
  } else {
    //
    // Specific Channel and Byte
    //
    Offset = DDRDATA0CH0_CR_DDRCRDATACONTROL1_REG +
      ((DDRDATA0CH1_CR_DDRCRDATACONTROL1_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL1_REG) * Channel) +
      ((DDRDATA1CH0_CR_DDRCRDATACONTROL1_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL1_REG) * Byte);
  }

  return Offset;

}

/**
  Returns the Offset for DataControl2 register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetDataControl2 (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  )
{
  UINT32  Offset;

  if (Channel >= MAX_CHANNEL) {
    //
    // Overall Broadcast
    //
    Offset = DDRDATA_CR_DDRCRDATACONTROL2_REG;
  } else if (Byte >= MAX_SDRAM_IN_DIMM) {
    //
    // Channel Broadcast
    //
    Offset = DDRDATACH0_CR_DDRCRDATACONTROL2_REG +
      ((DDRDATACH1_CR_DDRCRDATACONTROL2_REG - DDRDATACH0_CR_DDRCRDATACONTROL2_REG) * Channel);
  } else {
    //
    // Specific Channel and Byte
    //
    Offset = DDRDATA0CH0_CR_DDRCRDATACONTROL2_REG +
      ((DDRDATA0CH1_CR_DDRCRDATACONTROL2_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL2_REG) * Channel) +
      ((DDRDATA1CH0_CR_DDRCRDATACONTROL2_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL2_REG) * Byte);
  }

  return Offset;

}

/**
  Returns the Offset for DataOffsetTrain register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetDataOffsetTrain (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  )
{
  UINT32  Offset;

  if (Channel >= MAX_CHANNEL) {
    //
    // Overall Broadcast
    //
    Offset = DDRDATA_CR_DDRCRDATAOFFSETTRAIN_REG;
  } else if (Byte >= MAX_SDRAM_IN_DIMM) {
    //
    // Channel Broadcast
    //
    Offset = DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_REG +
      ((DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_REG - DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_REG) * Channel);
  } else {
    //
    // Specific Channel and Byte
    //
    Offset = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG +
      ((DDRDATA0CH1_CR_DDRCRDATAOFFSETTRAIN_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG) * Channel) +
      ((DDRDATA1CH0_CR_DDRCRDATAOFFSETTRAIN_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG) * Byte);
  }

  return Offset;

}

/**
  Returns the Offset for VrefAdjust1 register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset

**/
UINT32
MrcGetOffsetVrefAdjust1 (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  )
{
  UINT32  Offset;

  if (Channel >= MAX_CHANNEL) {
    //
    // Overall Broadcast
    //
    Offset = DDRDATA_CR_DDRCRVREFADJUST1_REG;
  } else if (Byte >= MAX_SDRAM_IN_DIMM) {
    //
    // Channel Broadcast
    //
    Offset = DDRDATACH0_CR_DDRCRVREFADJUST1_REG +
      ((DDRDATACH1_CR_DDRCRVREFADJUST1_REG - DDRDATACH0_CR_DDRCRVREFADJUST1_REG) * Channel);
  } else {
    //
    // Specific Channel and Byte
    //
    Offset = DDRDATA0CH0_CR_DDRCRVREFADJUST1_REG +
      ((DDRDATA0CH1_CR_DDRCRVREFADJUST1_REG - DDRDATA0CH0_CR_DDRCRVREFADJUST1_REG) * Channel) +
      ((DDRDATA1CH0_CR_DDRCRVREFADJUST1_REG - DDRDATA0CH0_CR_DDRCRVREFADJUST1_REG) * Byte);
  }

  return Offset;

}

/**
  Determines if PerBitDeskew is needed

  @param[in]   MrcData      - The MRC global data.
  @param[in]   MarginResult - Data structure with the latest margin results.
  @param[in]   Param        - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                              8:WrTBit, 9:RdTBit, 10:RdVBit,
                              16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                              ONLY RdT and WrT are allowed in this function

  @retval Update - If DeskewDisable needs to be updated to CPU

**/
BOOLEAN
MrcPerBitDeskew (
  IN MrcParameters * const MrcData,
  IN UINT32                MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN const UINT8           Param
  )
{
  MrcDebug          *Debug;
  const MrcInput    *Inputs;
  MrcIntOutput      *MrcIntData;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcIntControllerOut *IntControllerOut;
  MrcIntChannelOut  *IntChannelOut;
  UINT32            MinEyeWidth;
  UINT32            EyeWidth;
  UINT32            Offset;
  UINT8             ResultType;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             Byte;
  UINT8             ParamB;
  BOOLEAN           Update;
  UINT16            PwrLimit;
  UINT16            UPMLimit;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs     = &MrcData->Inputs;
  Outputs    = &MrcData->Outputs;
  Debug      = &Outputs->Debug;

  Update           = FALSE;
  if ((Param != RdT) && (Param != WrT)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MrcPerBitDeskew: Incorrect Margin Parameter %d\n", Param);
    return Update;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Parameter = %d (%sT)\n", Param, (Param == RdT) ? "Rd" : "Wr");
  ControllerOut    = &Outputs->Controller[0];
  IntControllerOut = &MrcIntData->Controller[0];
  ResultType       = GetMarginResultType (Param);

  ParamB = (Param == RdT) ? RdTBit : WrTBit;

  PwrLimit = MrcGetUpmPwrLimit (MrcData, Param, PowerLimit);
  UPMLimit = MrcGetUpmPwrLimit (MrcData, Param, UpmLimit);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MrcPerBitDeskew: PwrLimit %u UPMLimit %u ((PwrLimit + UPMLimit) / 2) %u\n", PwrLimit, UPMLimit, (PwrLimit + UPMLimit) / 2);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut    = &ControllerOut->Channel[Channel];
      IntChannelOut = &IntControllerOut->Channel[Channel];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MinEyeWidth = 0xFFFFFFFF;
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            EyeWidth = MarginResult[ResultType][Rank][Channel][Byte][0] + MarginResult[ResultType][Rank][Channel][Byte][1];
            MinEyeWidth = MIN (MinEyeWidth, EyeWidth);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MrcPerBitDeskew: Channel %u Byte %u Rank %u LM %u RM %u Width %u MinWidth %u\n", Channel, Byte, Rank,
              MarginResult[ResultType][Rank][Channel][Byte][0], MarginResult[ResultType][Rank][Channel][Byte][1], EyeWidth, MinEyeWidth);
          }// if Rank Exist
        }// for Rank
        if (MinEyeWidth > (UINT32) ((PwrLimit + UPMLimit) / 2)) {
          Update = TRUE;
          //
          // Program PerBitDeskew to 0x00000000 which means RxDqsN/P needs to be pulled in by 8 ticks and TxDq needs pushed out by 8 ticks
          //
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
              ChangeMargin (MrcData, ParamB, 0, 0, 0, Channel, Rank, Byte, 0, 1, 0, MrcRegFileRank);
            }// if Rank Exist
          }// for Rank
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nMrcPerBitDeskew: Disabling PerBitDeskew for Channel %u Byte %u\n\n", Channel, Byte);
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
              if (Param == RdT) {
                ChannelOut->RxDqsN[Rank][Byte] = MAX (ChannelOut->RxDqsN[Rank][Byte], 8) - 8;
                ChannelOut->RxDqsP[Rank][Byte] = MAX (ChannelOut->RxDqsP[Rank][Byte], 8) - 8;
                UpdateRxT (MrcData, Channel, Rank, Byte, 0xFF, 0);
                Offset = DDRDATA_CR_DDRCRDATACONTROL2_RxDeskewDisable_MSK;
              } else {
                ChannelOut->TxDq[Rank][Byte] = MIN (ChannelOut->TxDq[Rank][Byte], 0x1F7) + 8;
                UpdateTxT (MrcData, Channel, Rank, Byte, 0xFF, 0);
                Offset = DDRDATA_CR_DDRCRDATACONTROL2_TxDeskewDisable_MSK;
              }
              IntChannelOut->DqControl2[Byte].Data |= Offset;
            }// if Rank Exist
          }// for Rank
        }// if MinEyeWidth
      }// for Byte
    }// if Channel Exist
  }// for Channel

  if (Update) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        IntChannelOut = &IntControllerOut->Channel[Channel];
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Offset = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
          MrcWriteCR (MrcData, Offset, IntChannelOut->DqControl2[Byte].Data);
        }// for Byte
      }// if Channel Exist
    }// for Channel
  }

  return Update;
}



/**
  Translate LPDDR command from CA[9:0] high and low phase to DDR3 MA/BA/CMD.
  This is needed to program CADB.

  @param[in]  CaHigh - CA[9:0] value on the rising clock
  @param[in]  CaLow  - CA[9:0] value on the falling clock
  @param[out] MA     - Translated value of MA[15:0]
  @param[out] BA     - Translated value of BA[2:0]
  @param[out] CMD    - Translated value of CMD[2:0] = [RASb, CASb, WEb]

**/
void
MrcConvertLpddr2Ddr (
  IN  UINT32 const CaHigh,
  IN  UINT32 const CaLow,
  OUT UINT32       *MA,
  OUT UINT32       *BA,
  OUT UINT32       *CMD
  )
{
  *MA  = 0;
  *BA  = 0;
  *CMD = 0;

  //
  // Translation table
  //
  // Command  High phase Low phase
  //-----------------------------
  // CA[0]    RASb       MA[0]
  // CA[1]    CASb       MA[1]
  // CA[2]    WEb        MA[2]
  // CA[3]    MA[11]     MA[3]
  // CA[4]    MA[12]     MA[4]
  // CA[5]    MA[13]     MA[5]
  // CA[6]    MA[10]     MA[6]
  // CA[7]    BA[0]      MA[7]
  // CA[8]    BA[1]      MA[8]
  // CA[9]    BA[2]      MA[9]

  *MA  |= (CaLow & 0x3FF);         // MA[9:0]
  *MA  |= ((CaHigh & 0x40) << 4);  // MA[10]
  *MA  |= ((CaHigh & 0x38) << 8);  // MA[13:11]

  *BA  |= ((CaHigh & 0x380) >> 7); // BA[2:0]

  *CMD |= ((CaHigh & 0x04) >> 2);  // CMD[0] = WEb
  *CMD |= ((CaHigh & 0x02));       // CMD[1] = CASb
  *CMD |= ((CaHigh & 0x01) << 2);  // CMD[2] = RASb
}

/**
  Run a short CADB sequence on selected channels

  @param[in] MrcData   - The MRC global data.
  @param[in] ChBitMask - channels to work on.

**/
void
ShortRunCADB (
  IN MrcParameters *const  MrcData,
  IN UINT8                 ChBitMask
  )
{
  UINT32   Channel;
  UINT32   Offset;
  MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_STRUCT   ReutGlobalCtl;
  MCSCHEDS_CR_REUT_CH_PAT_CADB_CTRL_STRUCT  ReutChPatCadbCtrl;
  MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT ReutChSeqCfg;

  //
  // Enable REUT mode and Global Control on selected channels
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    Offset = MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG +
      ((MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG) * Channel);
    ReutChSeqCfg.Data = MrcReadCR64 (MrcData, Offset);
    if (((1 << Channel) & ChBitMask) != 0) {
      ReutChSeqCfg.Bits.Initialization_Mode = REUT_Testing_Mode;
      ReutChSeqCfg.Bits.Global_Control      = 1;
    } else {
      ReutChSeqCfg.Bits.Global_Control = 0;
    }

    MrcWriteCR64 (MrcData, Offset, ReutChSeqCfg.Data);
  }
  //
  // Enable CADB Always On mode
  //
  ReutChPatCadbCtrl.Data                        = 0;
  ReutChPatCadbCtrl.Bits.Enable_CADB_Always_On  = 1;
  MrcWriteCR (MrcData, MCSCHEDS_CR_REUT_CH_PAT_CADB_CTRL_REG, ReutChPatCadbCtrl.Data);

  //
  // Start CADB
  //
  ReutGlobalCtl.Data                    = 0;
  ReutGlobalCtl.Bits.Global_Start_Test  = 1;
  MrcWriteCR (MrcData, MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG, ReutGlobalCtl.Data);

  //
  // It's enough to read from this register, no need for an extra delay
  //
  ReutGlobalCtl.Data = MrcReadCR (MrcData, MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG);
  //
  // Disable CADB Always On mode
  //
  ReutChPatCadbCtrl.Bits.Enable_CADB_Always_On = 0;
  MrcWriteCR (MrcData, MCSCHEDS_CR_REUT_CH_PAT_CADB_CTRL_REG, ReutChPatCadbCtrl.Data);

  //
  // Stop CADB
  //
  ReutGlobalCtl.Bits.Global_Start_Test  = 0;
  ReutGlobalCtl.Bits.Global_Stop_Test   = 1;
  MrcWriteCR (MrcData, MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG, ReutGlobalCtl.Data);

  //
  // Read back
  //
  ReutGlobalCtl.Data = MrcReadCR (MrcData, MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG);

  //
  // Disable Global Control on selected channels
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (((1 << Channel) & ChBitMask) != 0) {
      Offset = MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG +
        ((MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG) * Channel);
      ReutChSeqCfg.Data                 = MrcReadCR64 (MrcData, Offset);
      ReutChSeqCfg.Bits.Global_Control  = 0;
      MrcWriteCR64 (MrcData, Offset, ReutChSeqCfg.Data);
    }
  }
}



/**
  Get the Rx Bias values

  @param[in, out] MrcData    - Include all MRC global data.
  @param[in, out] RxFselect  - Location to save RxFselect.
  @param[in, out] RxCBSelect - Location to save RxCBSelect.

**/
void
GetRxFselect (
  IN MrcParameters *const MrcData,
  IN OUT INT8             *RxFselect,
  IN OUT UINT8            *RxCBSelect
  )
{
  MrcOutput                    *Outputs;
  DDRCLK_CR_DDRCBSTATUS_STRUCT DdrCbStatus;

  Outputs          = &MrcData->Outputs;
  DdrCbStatus.Data = MrcReadCR (MrcData, DDRCLK_CR_DDRCBSTATUS_REG);
  *RxCBSelect      = (UINT8) DdrCbStatus.Bits.DllCB;
  *RxFselect       = (Outputs->Ratio - ((Outputs->RefClk == MRC_REF_CLOCK_133) ? RXF_SELECT_RC_133 : RXF_SELECT_RC_100));

  //
  // Limit ratios for 1067, 1333, 1600, 1867 & 2133 MHz
  //
  *RxFselect = MIN (*RxFselect, RXF_SELECT_MAX);  // Maximum 2133 MHz
  *RxFselect = MAX (*RxFselect, RXF_SELECT_MIN);  // Minimum 1067 MHz
  return;
}

/**
  Read 32-bit value from the specified bus/device/function/offset.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Bus      - PCI bus number.
  @param[in] Device   - PCI device number.
  @param[in] Function - PCI function number.
  @param[in] Offset   - PCI address offset.

  @retval 32-bit PCI value.
**/
UINT32
MrcPciRead32 (
  IN const MrcParameters * const MrcData,
  IN const UINT8 Bus,
  IN const UINT8 Device,
  IN const UINT8 Function,
  IN const UINT8 Offset
  )
{
  const MrcInput     *Inputs;
  const MRC_FUNCTION *MrcCall;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcCall->MrcIoWrite32 (Inputs->PciIndex, MrcCall->MrcGetPciDeviceAddress (Bus, Device, Function, Offset));
  return (MrcCall->MrcIoRead32 (Inputs->PciData));
}

/**
  This function changes the DIMM Voltage to the closest desired voltage without
  going higher. Default wait time is the minimum value of 200us, if more time
  is needed before deassertion of DIMM Reset#, then change the parameter.

  @param[in, out] MrcData            - The MRC "global data" area.
  @param[in]      VddVoltage         - Selects the DDR voltage to use, in mV.
  @param[in, out] VddSettleWaitTime  - Time needed for Vdd to settle after the update

  @retval TRUE if a voltage change occurred, otherwise FALSE.
**/
BOOLEAN
MrcVDDVoltageCheckAndSwitch (
  IN OUT MrcParameters      *MrcData,
  IN     const MrcVddSelect VddVoltage,
  IN OUT UINT32 * const     VddSettleWaitTime
  )
{
  MRC_FUNCTION *MrcCall;
  MrcInput     *Inputs;
  MrcOutput    *Outputs;
  MrcDebug     *Debug;
  MrcVddSelect Current;
  MrcVddSelect DefaultVdd;
  MrcVddSelect NewVdd;
  BOOLEAN      Status;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = FALSE;
  DefaultVdd = (Outputs->DdrType == MRC_DDR_TYPE_DDR3) ? VDD_1_35 : VDD_1_20;   // LPDDR3 and DDR4 use 1.2v by default

  Current = (MrcVddSelect) MrcCall->MrcGetMemoryVdd (MrcData, DefaultVdd);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Current VddVoltage is %u mV\n", Current);
  if (VddVoltage != Current) {
    NewVdd = MrcCall->MrcSetMemoryVdd (MrcData, DefaultVdd, VddVoltage);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*** VddVoltage updated to %u mV\n", NewVdd);
    Status = TRUE;
  }

  //
  // Increase the VddSettleWaitTime by the amount requested in the Input structure
  //
  *VddSettleWaitTime += Inputs->VddSettleWaitTime;

  //
  // Either update was already done or change is not necessary every time this is called
  //
  Outputs->VddVoltageDone = TRUE;

  return Status;
}


#ifdef MRC_DEBUG_PRINT
/**
  Debug output of MarginResults for specific ResultType

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] ResultType - Margin Result Type

**/
void
MrcDisplayMarginResultArray (
  IN MrcParameters *MrcData,
  IN UINT8         ResultType
  )
{
  MrcDebug                      *Debug;
  const MrcInput                *Inputs;
  MrcOutput                     *Outputs;
  UINT8                         Channel;
  UINT8                         Rank;
  UINT8                         Byte;
  UINT8                         Edge;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*********************************************\nMargin Results for ");
  switch (ResultType) {
    case LastTxV:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TxV\n");
      break;

    case LastTxT:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TxT\n");
      break;

    case LastRxV:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RxV\n");
      break;

    case LastRxT:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RxT\n");
      break;

    case LastRcvEna:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RcvEna\n");
      break;

    case LastWrLevel:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WrLevel\n");
      break;

    case LastCmdT:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CmdT\n");
      break;

    default:
    case LastCmdV:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CmdV\n");
      break;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tB0E0\tB0E1\tB1E0\tB1E1\tB2E0\tB2E1\tB3E0\tB3E1\tB4E0\tB4E1\tB5E0\tB5E1\tB6E0\tB6E1\tB7E0\tB7E1\tB8E0\tB8E1\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dR%d\t", Channel, Rank);
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            for (Edge = 0; Edge < MAX_EDGES; Edge++) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Outputs->MarginResult[ResultType][Rank][Channel][Byte][Edge]);
            }//Edge
          }//Byte
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
        }//RankExist
      }//Rank
    }//ChannelExist
  }//Channel

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*********************************************\n");
}
#endif //MRC_DEBUG_PRINT

/**
  This function sets up the REUT registers for Alias Check and DDR4 PDA mapping

  Setup for Memory Check like Alias Checking and DDR4 PDA mapping

  @param[in, out] MrcData           - Pointer to MRC global data.
  @param[in, out] ReutAddress       - Pointer to ReutAddress that will be programmed to REUT engine
  @param[in] Rank                   - Rank to setup
  @param[in] NumOfCachelines        - # of Cachelines to write and read to.  0 is a special value that will write the number
                                      of Cachelines that is required to determine Row/Column Aliasing.
  @param[in, out] ReutUninitialized - Pointer of whether ReutAddress Pointer needs initializing or not.

**/
void
MrcMemoryCheckSetup (
  IN OUT MrcParameters *const MrcData,
  IN OUT MRC_REUTAddress      *ReutAddress,
  IN UINT8                    Rank,
  IN UINT8                    NumOfCachelines,
  IN OUT BOOLEAN              *ReutUninitialized
  )
{
  MrcDebug           *Debug;
  const MrcInput     *Inputs;
  static const UINT8 WrapCarryEn[MrcReutFieldMax]   = {0, 0, 0, 0};
  static const UINT8 WrapTriggerEn[MrcReutFieldMax] = {0, 0, 0, 0};  // Trigger Stop on Bank Wrap
  static const UINT8 AddrInvertEn[MrcReutFieldMax]  = {0, 0, 0, 0};
  MrcOutput          *Outputs;
  MrcControllerOut   *ControllerOut;
  MrcDimmOut         *DimmOut;
  UINT32             CrOffset;
  UINT32             WritesPerPage;
  UINT16             ColumnIncValUnaligned;
  UINT8              RankToDimm;
  UINT8              Channel;
  UINT8              GlobalControl;
  MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT       ReutChSeqCfg;
  MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_STRUCT    ReutChPatWdbCl;
  MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_STRUCT ReutChPatWdbClMuxCfg;
  MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_STRUCT   ReutSubSeqCtl;

  Outputs       = &MrcData->Outputs;
  Inputs        = &MrcData->Inputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];

  if (*ReutUninitialized == TRUE) {
    //
    // Test Initialization
    //
    //
    // Start with IncRate = 3 so we have 4 column writes per page.  This will change with Column Size.
    // Must have 4 (reg + 1) writes to move to the next LFSR code for unique values.
    //
    ReutAddress->IncRate[MrcReutFieldRow]  = 3;
    //
    // IncVal[Col] is chosen to be 1/4 of the minimum column supported to get 4 writes per page.
    // Each write is 1 cache line (8 column addresses worth of data).
    // IncVal is on a cache line basis when programmed.  Account for this here ( >> 3).
    //
    ColumnIncValUnaligned                 = MRC_BIT10 >> 2; // divide by 4
    ReutAddress->IncVal[MrcReutFieldCol]  = ColumnIncValUnaligned >> 3; // cache line shift

    // Smallest Row address size is 2^12, but Row_Base_Address_Increment is a 12-bit signed field [0-11].
    // Thus we have to increment by 2^10.
    //
    ReutAddress->IncVal[MrcReutFieldRow]  = MRC_BIT10;
    ReutAddress->Stop[MrcReutFieldCol]    = 24; // 4 ([0-3] << 3) column writes before wrapping
    ReutAddress->Start[MrcReutFieldBank]  = 1;
    ReutAddress->Stop[MrcReutFieldBank]   = 1;

    //
    // Setup Reut all present channels.
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }

      //
      // Write initial Reut Address Values.
      //
      MrcProgramSequenceAddress (
        MrcData,
        Channel,
        ReutAddress->Start,
        NULL,              // Stop
        ReutAddress->Order,
        ReutAddress->IncRate,
        ReutAddress->IncVal,
        WrapTriggerEn,
        WrapCarryEn,
        AddrInvertEn,
        0,
        FALSE
        );

      //
      // Set Reut to Write
      //
      CrOffset = MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG +
        ((MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG) * Channel);
      ReutChSeqCfg.Data                 = MrcReadCR (MrcData, CrOffset);
      GlobalControl                     = (UINT8) ReutChSeqCfg.Bits.Global_Control;
      ReutChSeqCfg.Data = 0;
      ReutChSeqCfg.Bits.Initialization_Mode     = REUT_Testing_Mode;
      ReutChSeqCfg.Bits.Start_Test_Delay        = 2;
      ReutChSeqCfg.Bits.Subsequence_End_Pointer = 1;
      ReutChSeqCfg.Bits.Global_Control = GlobalControl;

      MrcWriteCR64 (
        MrcData,
        CrOffset,
        ReutChSeqCfg.Data
        );

      CrOffset = MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_0_REG +
      ((MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_0_REG) *
       Channel);
      MrcWriteCR (MrcData, CrOffset, 1);

      //
      // Program Write Data Buffer Control.
      //
      ReutChPatWdbCl.Data = 0;
      ReutChPatWdbCl.Bits.WDB_Increment_Scale = 1;
      MrcWriteCR (
        MrcData,
        MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_REG +
        ((MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_REG) * Channel),
        ReutChPatWdbCl.Data
        );

      ReutChPatWdbClMuxCfg.Data                     = 0;
      ReutChPatWdbClMuxCfg.Bits.ECC_Data_Source_Sel = 1;
      ReutChPatWdbClMuxCfg.Bits.Mux2_Control        = LFSRMode;
      ReutChPatWdbClMuxCfg.Bits.Mux1_Control        = LFSRMode;
      ReutChPatWdbClMuxCfg.Bits.Mux0_Control        = LFSRMode;
      ReutChPatWdbClMuxCfg.Bits.LFSR_Type           = 3;         // LFSR8
      CrOffset = MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_REG +
        ((MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_REG) * Channel);
      MrcWriteCR (MrcData, CrOffset, ReutChPatWdbClMuxCfg.Data);
    }// Channel
    *ReutUninitialized = FALSE;
  }// ReutUninitialized

  if ((MRC_BIT0 << Rank) & Outputs->ValidRankMask) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      //
      // Update Rank stop address based on DIMM SPD if Active.
      //
      RankToDimm  = RANK_TO_DIMM_NUMBER (Rank);
      DimmOut     = &ControllerOut->Channel[Channel].Dimm[RankToDimm];
      //
      // Since we're counting cache lines and won't wrap the row address,
      // program Row Stop to RowSize - 1 to avoid resetting the current address.
      // Column must wrap.  The wrap occurs on the increment which is after writing,
      // to that address.  Thus, we set wrap to be the last accessed column.
      //
      ColumnIncValUnaligned                 = ReutAddress->IncVal[MrcReutFieldCol] << 3; // cache line shift
      WritesPerPage                         = DimmOut->ColumnSize / ColumnIncValUnaligned;
      ReutAddress->Stop[MrcReutFieldRow]    = (UINT16) DimmOut->RowSize - 1;
      ReutAddress->Stop[MrcReutFieldCol]    = DimmOut->ColumnSize - ColumnIncValUnaligned;
      ReutAddress->IncRate[MrcReutFieldRow] = WritesPerPage - 1; // IncRate is +1 the programmed value

      MrcProgramSequenceAddress (
        MrcData,
        Channel,
        NULL,
        ReutAddress->Stop,
        NULL,
        ReutAddress->IncRate,
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        FALSE
        );
      //
      // Determine if we are doing an alias check, or a specific number of cachelines.
      //
      WritesPerPage = (NumOfCachelines > 0) ? NumOfCachelines : ((DimmOut->RowSize / MRC_BIT10) * WritesPerPage);
      //
      // Set up the Subsequence control.
      //
      CrOffset = MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_REG +
        ((MCDFXS_CR_REUT_CH1_SUBSEQ_CTL_MCMAIN_0_REG - MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_REG) * Channel);
      ReutSubSeqCtl.Data = 0;
      ReutSubSeqCtl.Bits.Subsequence_Type     = BWr;
      ReutSubSeqCtl.Bits.Number_of_Cachelines = MrcLog2 (WritesPerPage - 1);
      MrcWriteCR (
        MrcData,
        CrOffset,
        ReutSubSeqCtl.Data
        );
      CrOffset += MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_1_REG - MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_REG;
      ReutSubSeqCtl.Bits.Reset_Current_Base_Address_To_Start  = 1;
      ReutSubSeqCtl.Bits.Subsequence_Type = BRd;
      MrcWriteCR (
        MrcData,
        CrOffset,
        ReutSubSeqCtl.Data
        );
    }
  }
}

/**
  Hook before normal mode is enabled.

  @param[in, out] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
void
MrcBeforeNormalModeTestMenu (
  IN OUT MrcParameters *const MrcData
  )
{
  return;
}

/**
  Set ideal CPU Read Vref for DDR4 assuming CPU uses Vddq termination.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      DimmRon - DIMM Ron value in Ohm
  @param[in]      CpuOdt - CPU Read ODT value in Ohm
  @param[in]      PrintMsg - enable debug prints

  @retval none
**/
void
MrcSetIdealRxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  IN UINT8                    Channel,
  IN UINT32                   DimmRon,
  IN UINT32                   CpuOdt,
  IN BOOLEAN                  PrintMsg
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcVddSelect      Vdd;
  UINT8             Rank;
  UINT8             Byte;
  INT32             RxVref;
  UINT8             RxVrefCode;

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  ControllerOut     = &Outputs->Controller[0];

  //
  // (Vdd * (2 * DimmRon + DqOdt) / (DimmRon + DqOdt) / 2 - 0.75 * Vdd) * 192 / Vdd
  //
  Vdd = Outputs->VddVoltage[Inputs->MemoryProfile];
  RxVref = (Vdd * (2 * DimmRon + CpuOdt)) / (DimmRon + CpuOdt) / 2;
  RxVrefCode = (UINT8) DIVIDEROUND ((RxVref * 4 - 3 * Vdd) * 192, Vdd * 4);
  if (Inputs->EnVttOdt) {
    // in Vtt Odt mode the ideal Vref is Vdd/2.
    RxVref = Vdd / 2;
    RxVrefCode = 0; // the formula above assumes Vdd mode !!
  }
  if (PrintMsg) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CPU Odt = %d DimmRon = %d\n", CpuOdt, DimmRon);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CPU Read Vref = %dmV, RXTRAINRANK.RxVref=0x%02X\n", RxVref, RxVrefCode);
  }
  ChannelOut = &ControllerOut->Channel[Channel];
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
      continue;
    }
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      ChannelOut->RxVref[Byte] = RxVrefCode;
      UpdateRxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
    } // for Byte
    //
    // Download new settings from the RegFile to the Pads, using broadcast to all bytes in the channel
    //
    MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);
  } // for Rank
}

/**
  Set default CPU Read Vref for DDR4 assuming CPU uses Vddq termination.
  Use default CPU ODT and DIMM Ron values.

  @param[in, out] MrcData      - Include all MRC global data.
  @param[in]      GetFromTable - Get the DIMM ODT parameters from the initial table.
  @param[in]      PrintMsg     - Enable debug prints

  @retval none
**/
void
MrcSetDefaultRxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  IN     BOOLEAN         GetFromTable,
  IN     BOOLEAN         PrintMsg
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  UINT8             Ddr4;
  UINT32            EquOdt;
  UINT32            OdtTarget;
  UINT32            EffODT;
  UINT8             NumRanks;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             Dimm;
  UINT8             SerialR;
  BOOLEAN           is2R;
  UINT8             RankInDimm;

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  Ddr4              = (Outputs->DdrType ==  MRC_DDR_TYPE_DDR4);
  SerialR           = 15; // Ohm

  OdtTarget = Inputs->RcompTarget[RdOdt];
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    ChannelOut        = &Outputs->Controller[0].Channel[Channel];
    EffODT            = 0;
    NumRanks          = 0;
    is2R              = FALSE; // when 2R is detected
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        Dimm = RANK_TO_DIMM_NUMBER (Rank);
        RankInDimm = ChannelOut->Dimm[Dimm].RankInDimm;
        if ((!is2R) && (Dimm == 1) && (RankInDimm == 2)) {
          // If first DIMM is 1R and second DIMM is 2R, take into account only the 2R DIMM
          EffODT = 0;
          NumRanks = 0;
        }
        if ((RankInDimm == 1) && is2R) {
          // take into account only the 2R
          break;
        }
        EffODT += MrcGetEffDimmWriteOdt (MrcData, Channel, Rank, 1, GetFromTable);
        NumRanks++;
        if (RankInDimm == 2) {
          is2R = TRUE;
        }
      }
    }
    if (NumRanks > 0 ) {
      EffODT /= NumRanks;
    }

    EquOdt = OdtTarget *  EffODT / (OdtTarget + EffODT);

    MrcSetIdealRxVrefDdr4 (MrcData, Channel, 34 + SerialR, EquOdt, PrintMsg); // DIMM Ron = RZQ/7 = 34
  } // channel loop
}

/**
  Set ideal Dimm Write Vref for DDR4 assuming CPU Ron and Dimm termination.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Channel     - Channel to setup
  @param[in]      RankBitMask - Rank bit mask to setup
  @param[in]      Byte        - Byte to setup (for PDA mode only)
  @param[in]      CpuRon      - CPU Ron value in Ohm
  @param[in]      OdtWr       - Write DIMM Odt value in Ohm
  @param[in]      DimmOdt     - Equ. DIMM Odt value in Ohm
  @retval none
**/
void
MrcSetIdealTxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  UINT8                       Channel,
  UINT8                       RankBitMask,
  UINT8                       Byte,
  UINT32                      CpuRon,
  UINT32                      OdtWr,
  UINT32                      DimmOdt
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  UINT8             Rank;
  INT32             TxVrefMid;
  INT32             TxVref;
  INT8              TxVrefCode;
  MrcVddSelect      Vdd;
  UINT8             SerialR;

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  ControllerOut     = &Outputs->Controller[0];
  ChannelOut        = &ControllerOut->Channel[Channel];
  SerialR           = 15; // Ohm

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CpuRon = %d, OdtWr = %d, DimmOdt = %d\n", CpuRon, OdtWr, DimmOdt);
  Vdd = Outputs->VddVoltage[Inputs->MemoryProfile];
  TxVrefMid = (Vdd * (2 * CpuRon + DimmOdt)) / (CpuRon + DimmOdt) / 2;
  TxVref = (Vdd * SerialR + TxVrefMid * OdtWr) / (SerialR + OdtWr);
  TxVref *= 1000; // convert to uV
  TxVrefCode = (INT8) DIVIDEROUND (TxVref - 1000 * DDR4_VREF_MIDDLE_RANGE, DDR4_VREF_STEP_SIZE);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Dimm Write Vref = %dmV, TxVref Code = %d\n", TxVref / 1000, TxVrefCode);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (!(MrcRankInChannelExist (MrcData, Rank, Channel) & RankBitMask)) {
      continue;
    }
    MrcSetTxVrefDdr4 (MrcData, Channel, Rank, TxVrefCode, TRUE);
  } // for Rank
}

/**
  Set default Tx Dimm Vref for DDR4.
  Use default CPU Ron and DIMM Write Odt values.

  @param[in, out] MrcData - Include all MRC global data.

  @retval none
**/
void
MrcSetDefaultTxVrefDdr4 (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  UINT8             Channel;
  UINT8             Rank;
  UINT32            EffODT;
  UINT32            OdtWr;

  Outputs           = &MrcData->Outputs;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank , Channel)) {
        EffODT = MrcGetEffDimmWriteOdt(MrcData, Channel, Rank, 0, FALSE); // GetFromTable = FALSE because we already programmed the MR's
        OdtWr = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtWr, FALSE, 0);
        OdtWr = (OdtWr == 0) ? 0xFFFF : OdtWr;
        MrcSetIdealTxVrefDdr4 (MrcData, Channel, 0x1 << Rank, 0, MrcData->Inputs.RcompTarget[WrDS], OdtWr, EffODT);
      }
    }
  } // channel loop
}


/**
  Returns the effective Dimm Write ODT.
  Consider the DRAM tech, Rtt configuration (Wr, Nom, Park) and Normal Odt logic.
  Note: We still have the assumption of same Rtt's for all ranks in the same DIMM.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in] Channel      - Channel to setup
  @param[in] Rank         - Rank to setup
  @param[in] OdtType      - 0:write 1:read
  @param[in] GetFromTable - Get the Values from Odt tables

  @retval value in ohms
**/
UINT16
MrcGetEffDimmWriteOdt (
  IN OUT MrcParameters *const MrcData,
  UINT8                       Channel,
  UINT8                       Rank,
  UINT8                       OdtType,
  BOOLEAN                     GetFromTable
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  UINT32            OdtWr;
  UINT32            OdtNom;
  UINT32            OdtNom1;
  UINT32            OdtPark;
  UINT32            OdtPark1;
  BOOLEAN           Ddr4;
  BOOLEAN           Is2DPC;
  UINT32            RttT;
  UINT32            RttNT;
  UINT32            EffOdt;
  UINT8             Dimm;
  UINT8             OtherDimm;
  UINT8             SerialR;
  TOdtValueDdr4     *Ddr4OdtTableIndex;
  TOdtValue         *OdtTableIndex;

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  ControllerOut     = &Outputs->Controller[0];
  ChannelOut        = &ControllerOut->Channel[Channel];
  SerialR           = 15; // Ohm resistor on the dimm card

  Is2DPC = (ChannelOut->DimmCount == 2);
  Ddr4 = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Dimm = RANK_TO_DIMM_NUMBER (Rank);
  OtherDimm = (Dimm ^ 1) & 1;
  OdtPark = OdtPark1 = 0xFFFF;
  OdtNom  = OdtNom1  = 0xFFFF;

  if (GetFromTable) {
    if (Ddr4) {
      Ddr4OdtTableIndex = (TOdtValueDdr4 *) GetOdtTableIndex (MrcData, Channel, Dimm);
      if (Ddr4OdtTableIndex == NULL) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: OdtTableIndex is NULL!\n");
        return 0;
      }
      OdtWr = Ddr4OdtTableIndex->RttWr;
      OdtPark = (Ddr4OdtTableIndex->RttPark == 0) ? 0xFFFF : Ddr4OdtTableIndex->RttPark;
      //
      // Our convention is that ODT Write/Park is symmetric, ODT Nom is not (e.g 1R-2R vs. 2R-1R)
      //
      OdtNom = (Ddr4OdtTableIndex->RttNom == 0) ? 0xFFFF : Ddr4OdtTableIndex->RttNom;
      if (Is2DPC) {
        Ddr4OdtTableIndex = (TOdtValueDdr4 *) GetOdtTableIndex (MrcData, Channel, OtherDimm);
        if (Ddr4OdtTableIndex == NULL) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: OdtTableIndex is NULL!\n");
          return 0;
        }
        OdtNom1 = (Ddr4OdtTableIndex->RttNom == 0) ? 0xFFFF : Ddr4OdtTableIndex->RttNom;
        OdtPark1 = (Ddr4OdtTableIndex->RttPark == 0) ? 0xFFFF : Ddr4OdtTableIndex->RttPark;
      }
    } else {
      OdtTableIndex = (TOdtValue *) GetOdtTableIndex (MrcData, Channel, Dimm);
      if (OdtTableIndex == NULL) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: OdtTableIndex is NULL!\n");
        return 0;
      }
      OdtNom = (OdtTableIndex->RttNom == 0) ? 0xFFFF : OdtTableIndex->RttNom;
      OdtWr = OdtTableIndex->RttWr;
      if (Is2DPC) {
        OdtTableIndex = (TOdtValue *) GetOdtTableIndex (MrcData, Channel, OtherDimm);
        if (OdtTableIndex == NULL) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: OdtTableIndex is NULL!\n");
          return 0;
        }
        OdtNom1 = (OdtTableIndex->RttNom == 0) ? 0xFFFF : OdtTableIndex->RttNom;
      }
    }
  } else {
    OdtWr  = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtWr, FALSE, 0);
    OdtNom = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtNom, FALSE, 0);
    if (Is2DPC) {
      OdtNom1 = CalcDimmImpedance (MrcData, Channel, 2 * OtherDimm, OptDimmOdtNom, FALSE, 0);
    }
    if (Ddr4) {
      OdtPark = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtPark, FALSE, 0);
      if (Is2DPC) {
        OdtPark1 = CalcDimmImpedance (MrcData, Channel, 2 * OtherDimm, OptDimmOdtPark, FALSE, 0);
      }
    }
  }
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel = %d Is2DPC = %d OdtWr = %d OdtNom = %d OdtNom1 = %d OdtPark = %d OdtPark1 = %d\n", Channel, Is2DPC, OdtWr, OdtNom, OdtNom1, OdtPark, OdtPark1);
  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3) {
    //
    // for now no use in Odt for LPDDR (also we dont have the static tables for it)
    //
    OdtWr = 0xFFFF;
    return (UINT16) OdtWr;
  }
  // Add the serial resistor and protect clip at 16k to not overflow when mul
  OdtWr     = (OdtWr == 0) ? 0 : OdtWr + SerialR;
  OdtNom    = MIN ((OdtNom + SerialR), 0xFFFF);
  OdtNom1   = MIN ((OdtNom1 + SerialR), 0xFFFF);
  OdtPark   = MIN ((OdtPark + SerialR), 0xFFFF);
  OdtPark1  = MIN ((OdtPark1 + SerialR), 0xFFFF);
  //
  // Check that in DDR4 the mc toggles odt pin for the target rank for write.
  //

  if (Ddr4) {
    RttT = (OdtWr == 0) ? 0xFFFF : OdtWr;
  } else {
    RttT = (OdtWr == 0) ? OdtNom : OdtWr;
  }

  //
  // calc the effective park value
  //
  if (Ddr4) {
    if (ChannelOut->Dimm[Dimm].RankInDimm == 1) {
      OdtPark = 0xFFFF;
    }
    if (Is2DPC) {
      // in 1R we will have only Rtt nom
      if (ChannelOut->Dimm[OtherDimm].RankInDimm == 2) {
        OdtPark = DIVIDEROUND (OdtPark * OdtPark1, OdtPark + OdtPark1);
      }
    }
  }

  //
  // calc the effective NT value
  //
  if (Is2DPC) {
    RttNT =  (Ddr4) ? DIVIDEROUND (OdtPark * OdtNom1, OdtPark + OdtNom1) : OdtNom1;
  } else {
    RttNT = (Ddr4) ? OdtPark : 0xFFFF;
  }

  if (OdtType == 0) { // Write - Target Equivalent Rtt
    EffOdt = DIVIDEROUND (RttT * RttNT, RttT + RttNT);
  } else { // Read - NonTarget Equivalent Rtt
    EffOdt = RttNT;
  }
  return (UINT16) EffOdt;
}


/**
  Set Tx Dimm Vref absolute Value for DDR4.
  Use custom MRC range [-36:+37] where zero offset is 820mV and step is 7.8mV (JEDEC spec).

  @param[in, out] MrcData       - Include all MRC global data.
  @param[in]      Channel       - Channel to setup
  @param[in]      Rank          - Rank to setup
  @param[in]      TxVrefOffset  - TxVref Offset.
  @param[in]      UpdateMrcData - update MRC host struct

  @retval none
**/
void
MrcSetTxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  UINT8                Channel,
  UINT8                Rank,
  INT8                 TxVrefOffset,
  BOOLEAN              UpdateMrcData
  )
{
  MrcDebug                          *Debug;
  MrcChannelOut                     *ChannelOut;
  MrcOutput                         *Outputs;
  MrcRankOut                        *RankOut;
  DDR4_MODE_REGISTER_6_STRUCT       Ddr4Mr6;
  UINT8                             Mr6Loop;
  UINT8                             VrefDq;
  UINT8                             ByteLoop;

  Outputs    = &MrcData->Outputs;
  Debug      = &Outputs->Debug;
  ChannelOut = &Outputs->Controller[0].Channel[Channel];
  RankOut    = &ChannelOut->Dimm[ (Rank / 2) % MAX_DIMMS_IN_CHANNEL].Rank[Rank % 2];
  Ddr4Mr6.Data = RankOut->MR[mrMR6];

  VrefDq = MrcOffsetToVrefDq (MrcData, TxVrefOffset, Channel);
  Ddr4Mr6.Bits.VrefDqTrainingEnable = 1;
  Ddr4Mr6.Bits.VrefDqTrainingRange  = VrefDq >> 6;
  Ddr4Mr6.Bits.VrefDqTrainingValue  = VrefDq & 0x3F;

  for (Mr6Loop = 0; Mr6Loop < 3; Mr6Loop++) {
    if (Mr6Loop == 2) {
      Ddr4Mr6.Bits.VrefDqTrainingEnable = 0;
    }
    MrcWriteMRS (MrcData, Channel, 1 << Rank, mrMR6, Ddr4Mr6.Data);
    MrcWait (MrcData, tVREFDQ_MIN);
  }
  if (UpdateMrcData) {
    RankOut->MR[mrMR6] = Ddr4Mr6.Data;
    // update the per byte vref in case need later
    for (ByteLoop = 0; ByteLoop < Outputs->SdramCount; ByteLoop++) {
      RankOut->Ddr4PdaMr6[ByteLoop] = Ddr4Mr6.Data8[0];
    }
  }
  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tNon-PDA VrefDQ Ch%d Rank=%d MR6.Data=0x%x\n", Channel, Rank, Ddr4Mr6.Data);
}

/**
  Generic routine to perform Linear Centering in different 2D points.
  Re-uses DQTimeCentering1D routine as the linear centering routine.
  Optimize Per channel in the 2D param space.
  Run-Time - about 20nsec for 6 vref points and loopcout of 10

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     ChBitMask      - Channels to test.
  @param[in]     RankBitMask    - Ranks to test.
  @param[in]     Param          - Param to center with linear search - use DQTimeCentering1D (RdT,WrT,WrV,RdV,RcvX)
  @param[in]     Param2D        - The 2D Param to Offset - Use change margin routine
  @param[in]     Points2DMin    - Minimum value of second dimension points to sweep.
  @param[in]     Points2DMax    - Maxmimum value of second dimension points to sweep.
  @param[in]     ParamStepSize  - Step size of second dimension points to sweep.
  @param[in]     LoopCount      - Loop count
  @param[in]     TestType       - 0: normal reads, 1: Read MPR
  @param[in]     Prints         - Debug prints enable/disable

  @retval MrcStatus - If it successed return mrcSuccess
**/
MrcStatus
EarlyLinearCentering2D (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                ChBitMask,
  IN     UINT8                RankBitMask,
  IN     UINT8                Param,
  IN     UINT8                Param2D,
  IN     INT8                 Points2DMin,
  IN     INT8                 Points2DMax,
  IN     UINT8                ParamStepSize,
  IN     UINT8                LoopCount,
  IN     UINT8                TestType,
  IN     BOOLEAN              Prints
  )
{
  const MrcInput                          *Inputs;
  MrcDebug                                *Debug;
  const MRC_FUNCTION                      *MrcCall;
  MrcOutput                               *Outputs;
  MrcControllerOut                        *ControllerOut;
  MrcChannelOut                           *ChannelOut;
  MrcStatus                               Status;
  UINT32                                  (*MarginByte) [MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT8                                   ResultType;
  UINT8                                   Channel;
  UINT8                                   Rank;
  UINT8                                   Byte;
  UINT8                                   ChRankMask;
  UINT8                                   Idx;
  UINT8                                   MinByte[MAX_CHANNEL];
  UINT8                                   MinRank[MAX_CHANNEL];
  UINT8                                   BestByte[MAX_CHANNEL];
  UINT8                                   BestRank[MAX_CHANNEL];
  UINT16                                  MinEye[MAX_CHANNEL];
  UINT16                                  EyeSize;
  UINT16                                  NonZeroBytes[MAX_RANK_IN_CHANNEL][MAX_CHANNEL];
  INT8                                    Param2DVal;
  INT8                                    Best2DPoint[MAX_CHANNEL];
  UINT16                                  Best1DEye[MAX_CHANNEL];
  BOOLEAN                                 Ddr4;
  UINT8                                   Num2DPoints;

  Inputs          = &MrcData->Inputs;
  MrcCall         = Inputs->Call.Func;
  Outputs         = &MrcData->Outputs;
  Debug           = Prints ? &Outputs->Debug : NULL;
  Status          = mrcSuccess;
  Ddr4            = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Num2DPoints     = (UINT8) (Points2DMax - Points2DMin) / ParamStepSize;
  ControllerOut = &Outputs->Controller[0];
  MarginByte  = Outputs->MarginResult;
  MrcCall->MrcSetMem ((UINT8 *) Best1DEye, sizeof (Best1DEye), 0);
  MrcCall->MrcSetMem ((UINT8 *) Best2DPoint, sizeof (Best2DPoint), 0);
  MrcCall->MrcSetMem (BestByte, sizeof (BestByte), 0);
  MrcCall->MrcSetMem (BestRank, sizeof (BestRank), 0);
  MrcCall->MrcSetMemWord (&NonZeroBytes[0][0], (MAX_RANK_IN_CHANNEL * MAX_CHANNEL), 0);

  MRC_ASSERT (Points2DMin < Points2DMax, Debug, "\nERROR: Invalid Parameters, Points2DMin and Points2DMax\n");
  //
  // ####################################################
  // ################  Initialize EW/EH variables  ######
  // ####################################################
  //

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n### Measure Eye Width, per BYTE, at ALL (2D) Timing Points - RankBitMask = 0x%X\n", RankBitMask);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tChannel %d", Channel);
    for (Byte = 0; Byte < Outputs->SdramCount - 2; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nByte\t");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Byte);
    }
  }
#endif // MRC_DEBUG_PRINT

  Status      = GetMarginByte (MrcData, Outputs->MarginResult, Param, 0, RankBitMask);
  ResultType  = GetMarginResultType (Param);

  //
  // ####################################################
  // ######   Measure Eye Width at all Vref Points  #####
  // ####################################################
  //
  //
  // Loop through all the 2D Points to Test
  //
  for (Idx = 0; Idx <= Num2DPoints; Idx++) {
    Param2DVal = Points2DMin + (Idx * ParamStepSize);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nVref: %d\t", Param2DVal);

    // @todo: add max margins check
    //  byteMax[Channel] = MrcCalcMaxVrefMargin (MrcData, Channel, 0xFF, byte, Param2D, sign, byteMax[Channel]);

    //
    // Setup 2D Offset for this point
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      ChRankMask = RankBitMask & ChannelOut->ValidRankBitMask;
      if (ChRankMask == 0) {
        continue;
      }
      if (Param2D == RdV) {
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (!((1 << Rank) & ChRankMask)) {
            continue;
          }
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            ChannelOut->RxVref[Byte] = Param2DVal;
            UpdateRxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
          }
          //
          // Download new settings from the RegFile to the Pads, using broadcast to all bytes in the channel
          //
          MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);
        }
      } else {
        Status = ChangeMargin (MrcData, Param2D, Param2DVal, 0, 0, Channel, (Ddr4 && (Param2D == WrV)) ? ChRankMask : 0xFF, 0, 0, 0, 0, MrcRegFileCurrent);
      }
      // Init Best2DPoint
      if (Idx == 0) {
        Best2DPoint[Channel] = Param2DVal;
      }
    }
    //
    // Run Param Margin Test
    //
    if (TestType == 0) {
      Status = DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, Param, 0, LoopCount, FALSE, TRUE);
    } else if (TestType == 1) {
      Status = ReadMprTraining (MrcData, FALSE);
    }

#ifdef MRC_DEBUG_PRINT
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((0x1 << Rank) & Outputs->ValidRankMask & RankBitMask) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nR%d L-R\t",Rank);
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t", Byte);
            }
          } else {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "%d-%d\t",
                MarginByte[ResultType][Rank][Channel][Byte][0] / 10,
                MarginByte[ResultType][Rank][Channel][Byte][1] / 10
                );
            }
          }
        }
      }
    }
#endif // MRC_DEBUG_PRINT
    //
    // Store Results
    //
    MrcCall->MrcSetMem ((UINT8 *) MinEye, sizeof (MinEye), 0xFF);
    MrcCall->MrcSetMem ((UINT8 *) MinByte, sizeof (MinByte), 0xFF);
    MrcCall->MrcSetMem ((UINT8 *) MinRank, sizeof (MinRank), 0xFF);
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((1 << Rank) & Outputs->ValidRankMask & RankBitMask) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
            continue;
          }
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            EyeSize = (UINT16) (MarginByte[ResultType][Rank][Channel][Byte][1] + MarginByte[ResultType][Rank][Channel][Byte][0]);
            // Track bytes with eyesize of zero for all Vref points
            if (EyeSize && !(NonZeroBytes[Rank][Channel] & (1 << Byte))) {
              NonZeroBytes[Rank][Channel] |= (1 << Byte);
            }
            //
            // Track minimum eye width per ch/rank
            //
            if (MinEye[Channel] > EyeSize) {
              MinEye[Channel] = EyeSize;
              MinByte[Channel] = Byte;
              MinRank[Channel] = Rank;
            }
          }
        } // for Channel
      } // if Rank exists
    } // for Rank
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs,Channel)) {
        continue;
      }
      // track best eye in the 2D space
      if (Best1DEye[Channel] < MinEye[Channel]) {
        Best2DPoint[Channel] = Param2DVal;
        Best1DEye[Channel] = MinEye[Channel];
        BestByte[Channel]  = MinByte[Channel];
        BestRank[Channel]  = MinRank[Channel];
      }
    } // for Channel
  } // 2D Points

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((1 << Rank) & Outputs->ValidRankMask & RankBitMask) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!(NonZeroBytes[Rank][Channel] & (1 << Byte))) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_ERROR,
              "\n Channel[%d] Rank[%d] Byte[%d] has Zero Margin at all Vref points...",
              Channel,
              Rank,
              Byte
            );
            Status = mrcFail;
          }
        }
      }
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  if (Status == mrcFail) {
    return Status;
  }

  //
  // ####################################################
  // ###########   Center Results per Byte   ############
  // ####################################################
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (MRC_BIT0 << Channel))) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    ChRankMask = RankBitMask & ChannelOut->ValidRankBitMask;
    if (ChRankMask == 0) {
      continue;
    }
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "\nChannel %d: Selected Vref <%d>  Smallest eye width <%d> found at Rank %d Byte %d",
      Channel,
      Best2DPoint[Channel],
      Best1DEye[Channel],
      BestRank[Channel],
      BestByte[Channel]
      );
    //
    // Note : the Change margin will work only on non TrainOffset params like WrV, RcvEnX (if other needed use UpdateTxT/RxT)
    //
    if (Param2D == RdV) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!((1 << Rank) & ChRankMask)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          ChannelOut->RxVref[Byte] = Best2DPoint[Channel];
          UpdateRxTValues (MrcData, Channel, Rank, Byte, 0xFF, 0);
        }
        //
        // Download new settings from the RegFile to the Pads, using broadcast to all bytes in the channel
        //
        MrcDownloadRegFile (MrcData, Channel, TRUE, Rank, MrcRegFileRank, 0, 1, 0);
      }
    } else {
      ChangeMargin (MrcData, Param2D, Best2DPoint[Channel], 0, 0, Channel, (Ddr4 && (Param2D == WrV)) ? ChRankMask : 0xFF, 0, 0, 1, 1, MrcRegFileCurrent);
    }
    //
    // Clear up after test
    //
    MrcCall->MrcSetMemDword (&ChannelOut->DataOffsetTrain[0], Outputs->SdramCount, 0);
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  // final centering at best offset
  if (TestType == 0) {
    Status = DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, Param, 0, LoopCount, FALSE, TRUE);
    IoReset (MrcData);
  } else if (TestType == 1) {
    Status = ReadMprTraining (MrcData, FALSE);
  }

  return Status;
}

/**
  Set ODT Logic behavior for DDR4.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Profile - Behavior type. Currently Profile 1 is supported (DDR3-like)
  @retval none
**/
void
MrcSetOdtMatrix (
  IN OUT MrcParameters *const MrcData,
  IN UINT8                    Profile
  )
{
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  UINT8             Channel;
  UINT8             Dimm;
  UINT32            Offset;
  MCHBAR_CH0_CR_SC_ODT_MATRIX_STRUCT  OdtMatrix;
  MCHBAR_CH0_CR_SC_GS_CFG_STRUCT      ScGsCfg;

  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    OdtMatrix.Data = 0;
    switch (Profile) {
      case 1:
        //
        // DDR3 like behavior: put OdtNom on rank 0 of the other DIMM
        // DDR4 difference is that ODT pin is not asserted on the target rank
        //
        if (ChannelOut->DimmCount == 2) {
          OdtMatrix.Bits.Write_Rank_0 = 0x4;
          OdtMatrix.Bits.Write_Rank_1 = 0x4;
          OdtMatrix.Bits.Write_Rank_2 = 0x1;
          OdtMatrix.Bits.Write_Rank_3 = 0x1;
          OdtMatrix.Bits.Read_Rank_0  = 0x4;
          OdtMatrix.Bits.Read_Rank_1  = 0x4;
          OdtMatrix.Bits.Read_Rank_2  = 0x1;
          OdtMatrix.Bits.Read_Rank_3  = 0x1;
        } else {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            if (ChannelOut->Dimm[Dimm].RankInDimm > 1) {
              if (Dimm == 0) {
                OdtMatrix.Bits.Write_Rank_0 = 0x1;
                OdtMatrix.Bits.Write_Rank_1 = 0x2;
              } else {
                OdtMatrix.Bits.Write_Rank_2 = 0x4;
                OdtMatrix.Bits.Write_Rank_3 = 0x8;
              }
            }
          }
        }
        break;
      case 0:
        // set odt pins to zero.
        break;
      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MrcSetOdtMatrix : Unknown Odt Matrix Profile\n");
        break;
    } // switch Profile
    Offset = MCHBAR_CH0_CR_SC_ODT_MATRIX_REG +
      (MCHBAR_CH1_CR_SC_ODT_MATRIX_REG - MCHBAR_CH0_CR_SC_ODT_MATRIX_REG) * Channel;
    MrcWriteCR (MrcData, Offset, OdtMatrix.Data);

    Offset = MCHBAR_CH0_CR_SC_GS_CFG_REG +
      (MCHBAR_CH1_CR_SC_GS_CFG_REG - MCHBAR_CH0_CR_SC_GS_CFG_REG) * Channel;
    ScGsCfg.Data = MrcReadCR (MrcData, Offset);
    ScGsCfg.Bits.enable_odt_matrix = 1;
    MrcWriteCR (MrcData, Offset, ScGsCfg.Data);
  } // for Channel
}

/**
  Get the Other Dimm in Channel.

  @param[in, out] MrcData  - Include all MRC global data.
  @param[in]      Channel  - Channel to search in.
  @param[in]      RankMask - Rank mask for the current DIMM.

  @retval The other Dimm outside the RankMask.  If no such DIMM, then return current DIMM.
**/
UINT8
MrcGetOtherDimm (
  IN MrcParameters *const MrcData,
  IN UINT8                Channel,
  IN UINT8                RankMask
  )
{
  UINT8 Dimm;
  UINT8 CurrentDimm;
  UINT8 OtherDimm;
  UINT8 ChannelRankMask;

  ChannelRankMask = MrcData->Outputs.Controller[0].Channel[Channel].ValidRankBitMask;
  CurrentDimm    = (RankMask & 0x3) ? 0 : 1;

  OtherDimm = CurrentDimm;
  for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
    if (Dimm == CurrentDimm) {
      continue;
    } else {
      if (DIMM_TO_RANK_MASK (Dimm) & ChannelRankMask) {
        OtherDimm = Dimm;
        break;
      }
    }
  }

  return OtherDimm;
}

/**
  Disable CADB Deselects, used after SetupIOTestCADB was called during Command Training or RMT.

  @param[in] MrcData  - Include all MRC global data.

  @retval none
**/
VOID
MrcDisableCadbOnDeselect (
  IN MrcParameters *const MrcData
  )
{
  UINT32  Offset;
  UINT8   Channel;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (&MrcData->Outputs, Channel)) {
      Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CTRL_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_CTRL_REG, Channel);
      MrcWriteCR (MrcData, Offset, 0);
    }
  }
}

/**
  This function returns the Minimal Eye Height required

  @param[in] MrcData        - Pointer to MRC global data.
  @param[in] EarlyCentering - TRUE if this is an early centering step

  @retval Returns minimal eye height required
**/
UINT32
MrcGetMinimalEyeHeight (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              EarlyCentering
  )
{
  MrcOutput   *Outputs;
  BOOLEAN     Ddr4;
  UINT32      MinEyeHeight;

  Outputs = &MrcData->Outputs;
  Ddr4 = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  MinEyeHeight = 8;
  if (Ddr4 && (Outputs->Frequency >= f2400)) {
    MinEyeHeight = 4;
  }
  if ((MrcData->Inputs.MemoryProfile != STD_PROFILE) && EarlyCentering) {
    MinEyeHeight = 1;
  }

  return MinEyeHeight;
}
