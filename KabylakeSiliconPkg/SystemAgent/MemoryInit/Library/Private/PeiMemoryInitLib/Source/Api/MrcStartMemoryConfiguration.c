/** @file
  Starting point for the core memory reference code.

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

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcCommandTraining.h"
#include "MrcCommon.h"
#include "MrcCrosser.h"
#include "MrcDdr3.h"
#include "MrcDebugHook.h"
#include "MrcDebugPrint.h"
#include "MrcGeneral.h"
#include "MrcGlobal.h"
#include "MrcBdat.h"
#include "MrcMcConfiguration.h"
#include "MrcMemoryMap.h"
#include "MrcMemoryScrub.h"
#include "MrcReadDqDqs.h"
#include "MrcReadReceiveEnable.h"
#include "MrcRegisterCache.h"
#include "MrcReset.h"
#include "MrcSaveRestore.h"
#include "MrcSpdProcessing.h"
#ifdef SSA_FLAG
#include "MrcSsaInitialize.h"
#include "MrcSsaCommon.h"
#endif
#ifdef DCTT_FLAG
#include "MrcDimmCellTest.h"
#endif // DCTT_FLAG
#include "MrcStartMemoryConfiguration.h"
#include "MrcWriteDqDqs.h"
#include "MrcWriteLeveling.h"
#include "MrcDdr3.h"

/**
  Print the input parameters to the debug message output port.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess
**/

//
// Functions:
//
GLOBAL_REMOVE_IF_UNREFERENCED const CallTableEntry  MrcCallTable[] = {
  ///
  /// The functions are executed in the following order, as the policy flag dictates.
  /// Mrctask, post_code, OEM command, policy_flag, iteration, debug_string
  ///
  {MrcFastBootPermitted,            MRC_FAST_BOOT_PERMITTED,    OemFastBootPermitted,   1,                             MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Fast boot permitted") },
  {MrcRestoreNonTrainingValues,     MRC_RESTORE_NON_TRAINING,   OemRestoreNonTraining,  1,           MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Restore non-training values") },
#ifdef MRC_DEBUG_PRINT
  {MrcPrintInputParameters,         MRC_PRINT_INPUT_PARAMS,     OemPrintInputParameters,1, MF_COLD | MF_WARM         | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Print input parameters") },
#endif // MRC_DEBUG_PRINT
  {MrcSetOverridesPreSpd,           MRC_SET_OVERRIDES_PSPD,     OemSetOverridePreSpd,   1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Pre-SPD Timing overrides") },
  {MrcSpdProcessing,                MRC_SPD_PROCESSING,         OemSpdProcessingRun,    1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("SPD PROCESSING") },
  {MrcSetOverrides,                 MRC_SET_OVERRIDES,          OemSetOverride,         1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Timing overrides") },
  {MrcMcCapability,                 MRC_MC_CAPABILITY,          OemMcCapability,        1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("MC Capabilities") },
  {MrcMcConfiguration,              MRC_MC_CONFIG,              OemMcInitRun,           1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("MC CONFIG") },
//#ifdef STUB_FLAG
//  {PowerCalcverification,         MRC_PRE_TRAINING,           OemPreTraining,         1, MF_COLD                   | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT("PowerCalcverification")},
//#endif
  {MrcSetMemoryMap,                 MRC_MC_MEMORY_MAP,          OemMcMemoryMap,         1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("MC MEMORY MAP") },
  {MrcResetSequence,                MRC_RESET_SEQUENCE,         OemMcResetRun,          1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("JEDEC RESET") },
  {MrcPreTraining,                  MRC_PRE_TRAINING,           OemPreTraining,         1, MF_COLD                   | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Pre-Training")},
  {MrcSenseAmpOffsetTraining,       MRC_SENSE_AMP_OFFSET,       OemSenseAmpTraining,    1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("SenseAmp Offset Training") },
  {MrcEarlyReadMprTimingCentering2D,MRC_EARLY_RDMPR_TIMING_2D,  OemEarlyReadMprDqDqs2D, 1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Early ReadMPR Timing Centering 2D") },
  {MrcEarlyCommandTraining,         MRC_EARLY_COMMAND,          OemEarlyCommandTraining,1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Early command training") },
  {MrcJedecInitLpddr3,              MRC_JEDEC_INIT_LPDDR3,      OemJedecInitLpddr3,     1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("LPDDR3 JEDEC INIT") },
  {MrcReadLevelingTraining,         MRC_RECEIVE_ENABLE,         OemReceiveEnable,       1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Read Leveling training") },
  {MrcReadMprTraining,              MRC_READ_MPR,               OemReadMprTraining,     1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Read MPR training") },
  {MrcLpddrLatencySetB,             MRC_LPDDR_LATENCY_SET_B,    OemLpddrLatencySetB,    1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("LPDDR3 Latency Set B") },
  {MrcJedecWriteLevelingTraining,   MRC_JEDEC_WRITE_LEVELING,   OemJedecWriteLeveling,  1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Jedec Write Leveling training") },

  {MrcEarlyWriteTimingCentering2D,  MRC_EARLY_WRITE_TIMING_2D,  OemEarlyWriteDqDqs2D,   1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Early Write Timing Centering 2D") },
  {MrcEarlyWrDsEqTraining,          MRC_EARLY_WRITE_DS_EQ,      OemEarlyWrDsEq,         1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Early WrDsEq Training") },
  {MrcWriteTimingCentering,         MRC_WRITE_TIMING_1D,        OemWriteDqDqs,          1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Write Timing Centering") },
  {MrcWriteVoltageCentering,        MRC_WRITE_VOLTAGE_1D,       OemWriteVoltage,        1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Write Voltage Centering") },
  {MrcEarlyReadTimingCentering2D,   MRC_EARLY_READ_TIMING_2D,   OemEarlyReadDqDqs2D,    1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Early Read Timing Centering 2D") },
  {MrcReadTimingCentering,          MRC_READ_TIMING_1D,         OemReadDqDqs,           1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Read Timing Centering") },

// This is used for debug
//  {CommandPlot2D,                 MRC_CMD_PLOT_2D,            OemReadDqDqs,           1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT("2D command plot")},

  {MrcCmdVoltageCentering,          MRC_CMD_VREF,               OemCmdVoltCenterPreLct, 1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Command Voltage Centering pre-LCT") },
  {MrcPostTraining,                 MRC_POST_TRAINING,          OemPostTraining,        1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Post-training") },
  {MrcLateCommandTraining,          MRC_LATE_COMMAND,           OemLateCommandTraining, 1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Late command training") },
  {MrcCmdVoltageCentering,          MRC_CMD_VREF,               OemCmdVoltCentering,    1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Command Voltage Centering") },
  {MrcCmdDsTxEq,                    MRC_CMD_DS,                 OemCmdDriveStrengthEq,  1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Command Drive Strength and Equalization 2D") },
  {MrcCmdSlewRate,                  MRC_CMD_SR,                 OemCmdSlewRate,         1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Command Slew Rate Training") },
  {MrcCmdNormalization,             MRC_CMD_NORMALIZE,          OemCmdNormalization,    1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Normalize Command Timing") },

  {MrcPowerSavingMeter,             MRC_PWR_MTR,                OemPowerSavingMeter,    1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("PowerSavingMeter Base Line Update") },
  {MrcDimmRonTraining,              MRC_DIMM_RON,               OemDimmRonTraining,     1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("DIMM Ron Training") },
  {MrcDimmODTTraining,              MRC_DIMM_ODT,               OemDimmODTTraining,     1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("DIMM ODT Training") },
  {MrcWriteEqDsTraining,            MRC_WRITE_DS,               OemWriteDriveStrengthEq,1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Write Drive Strength and Equalization 2D") },
  {MrcWriteDsUpDnTraining,          MRC_WRITE_DS,               OemWriteDriveUpDn,      1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Write Drive Strength Up/Dn 2D") },
  {MrcReadODTTraining,              MRC_READ_ODT,               OemReadODTTraining,     1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Read ODT Training") },
  {MrcWriteSlewRate,                MRC_WRITE_SR,               OemWriteSlewRate,       1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Write Slew Rate") },
  {MrcReadEQTraining,               MRC_READ_EQ,                OemReadEQTraining,      1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Read Equalization Training") },
  {MrcReadAmplifierPower,           MRC_READ_AMP_POWER,         OemReadAmplifierPower,  1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Read Amplifier Power") },
  {MrcOptimizeComp,                 MRC_CMP_OPT,                OemOptimizeComp,        1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Comp Optimization Training") },
  {MrcForceOltm,                    MRC_FORCE_OLTM,             OemForceOltm,           1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Force OLTM") },

  {MrcRoundTripLatency,             MRC_ROUND_TRIP_LAT,         OemRoundTripLatency,    1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Round Trip Latency Training") },
  {MrcTurnAroundTiming,             MRC_TURN_AROUND,            OemTurnAroundTimes,     1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Turn Around Trip Training") },

  {MrcWriteVoltageCentering2D,      MRC_WRITE_VREF_2D,          OemWriteVoltCentering2D,1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Write Voltage Centering 2D") },
  {MrcReadVoltageCentering2D,       MRC_READ_VREF_2D,           OemReadVoltCentering2D, 1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Read Voltage Centering 2D") },
  {MrcWriteTimingCentering2D,       MRC_WRITE_TIMING_2D,        OemWriteDqDqs2D,        1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Write Timing Centering 2D") },
  {MrcReadTimingCentering2D,        MRC_READ_TIMING_2D,         OemReadDqDqs2D,         1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Read Timing Centering 2D") },
  {MrcReceiveEnTimingCentering,     MRC_RCVEN_TIMING_1D,        OemRcvEnCentering1D,    1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH | MF_RMT, MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Receive Enable Timing Centering") },

  {MrcRetrainMarginCheck,           MRC_RETRAIN_CHECK,          OemRetrainMarginCheck,  1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          1,                 MRC_DEBUG_TEXT ("Check Margin for Retrain") },
  {MrcRankMarginTool,               MRC_RMT_TOOL,               OemRmt,                 1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Rank Margin Tool") },
#ifdef BDAT_SUPPORT
  {MrcRankMarginToolBit,            MRC_RMT_TOOL_BIT,           OemRmtPerBit,           1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Rank Margin Tool Bit")},
#endif
  {MrcPowerSavingMeter,             MRC_PWR_MTR,                OemPowerSavingMeter,    1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("PowerSavingMeter update") },
  {MrcTrainDdrTxDqVrefRange,        MRC_DDR4_TXVREF_RANGE,      OemDdr4TxVrefRange,     1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Ddr4 TxVref Range Optimization") },
  {MrcFillMrScratchRegs,            MRC_MR_FILL,                OemNumOfCommands,       1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Save MRs to Scratch Registers") },
#ifdef SSA_FLAG
  {MrcSsaStopPoint,                 MRC_SSA_STOP_POINT,         OemSsaStopPoint,        1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("SSA stop point") },
#endif // SSA_FLAG
  {MrcRhPrevention,                 MRC_RH_PREVENTION,          OemMrcRhPrevention,     1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Row Hammer Prevention") },
  {MrcMcActivate,                   MRC_MC_ACTIVATE,            OemMrcActivate,         1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("MRC activate") },
  {MrcSaveMCValues,                 MRC_SAVE_MC_VALUES,         OemSaveMCValues,        1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Save MC Values") },
  {MrcRestoreTrainingValues,        MRC_RESTORE_TRAINING,       OemRestoreTraining,     1,           MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Restore Training Values") },

  {MrcResetSequence,                MRC_RESET_SEQUENCE,         OemMcResetRun,          1,                             MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("JEDEC RESET on Fast flow") },
//{MrcRankMarginTool,               MRC_RMT_TOOL,               OemRmt,                 1,                             MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Rank Margin Tool on Fast flow")},

#ifdef SSA_FLAG
  {MrcSsaPreStopPoint,              MRC_SSA_PRE_STOP_POINT,     OemSsaStopPoint,        1,           MF_WARM         | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("SSA pre stop point") },
  {MrcSsaStopPoint,                 MRC_SSA_STOP_POINT,         OemSsaStopPoint,        1,           MF_WARM         | MF_FAST             | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("SSA stop point") },
  {MrcRestoreTrainingValues,        MRC_RESTORE_TRAINING,       OemRestoreTraining,     1,           MF_WARM         | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Restore Training Values") },
#endif // SSA_FLAG
  {MrcSelfRefreshExit,              MRC_SELF_REFRESH_EXIT,      OemSelfRefreshExit,     1,           MF_WARM | MF_S3           | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Perform Self Refresh Exit") },
  {MrcNormalMode,                   MRC_NORMAL_MODE,            OemNormalMode,          1,           MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Normal Operation For Non-Cold Boots") },
/// @attention: MrcAliasCheck must run before any test modifying the WDB entries to zero for memory scrubbing.
  {MrcAliasCheck,                   MRC_ALIAS_CHECK,            OemAliasCheck,          1, MF_COLD                                         | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("MRC Memory alias check") },
#ifdef DCTT_FLAG
  {MrcHwMemTest,                    MRC_CPGC_MEMORY_TEST,       OemMemTest,             1, MF_COLD                             | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("MRC HW Memory test") },
#endif // DCTT_FLAG
  {MrcEccClean,                     MRC_ECC_CLEAN_START,        OemHwMemInit,           1, MF_COLD                   | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("MRC Memory Scrubbing") },
  {MrcEnergyPerfGain,               MRC_ENG_PERF_GAIN,          OemEngPerfGain,         1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("MRC Energy Performance Gain") },
  {MrcSaGvSwitch,                   MRC_SA_GV_SWITCH,           OemSaGvSwitch,          1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("MRC SA GV Switch") },
  {MrcTxtAliasCheck,                MRC_TXT_ALIAS_CHECK,        OemTxtAliasCheck,       1, MF_COLD | MF_WARM         | MF_FAST             | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("TXT Memory alias check") },
  {MrcDone,                         MRC_DONE,                   OemMrcDone,             1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("MRC done") },
#ifdef BDAT_SUPPORT
  {MrcFillBdatStructure,            MRC_FILL_BDAT_STRUCTURE,     OemMrcFillBdat,        1, MF_COLD                                         | MF_GV_HIGH,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("MRC Fill BDAT Structure") },
#endif // BDAT_SUPPORT
};

/**
  this function use by the OEM to do dedicated task during the MRC.

  @param[in] MrcData           - include all the MRC data
  @param[in] OemStatusCommand  - A command that indicates the task to perform.
  @param[in] ptr               - general ptr for general use.

  @retval The status of the task.
**/
MrcStatus
MrcInternalCheckPoint (
  IN MrcParameters        *MrcData,
  IN MrcOemStatusCommand  OemStatusCommand,
  IN void                 *ptr
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcOutput         *Outputs;
  MrcIntOutput      *MrcIntData;
  MrcStatus         Status;
  MrcDdrType        DdrType;
  TrainingStepsEn   *TrainingEnables;
  TrainingStepsEn2  *TrainingEnables2;
  TrainingModeType  TrainingMode;
  BOOLEAN           Ddr4;
  BOOLEAN           Lpddr3;
  BOOLEAN           UltUlx;
  BOOLEAN           UltUlx_Lpddr3_2133;

  Status      = mrcSuccess;
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  DdrType     = Outputs->DdrType;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  TrainingEnables   = &Inputs->TrainingEnables;
  TrainingEnables2  = &Inputs->TrainingEnables2;
  TrainingMode      = Inputs->PowerTrainingMode;

  Lpddr3 = (DdrType == MRC_DDR_TYPE_LPDDR3);
  Ddr4   = (DdrType == MRC_DDR_TYPE_DDR4);
  UltUlx = ((Inputs->CpuModel == cmSKL_ULX_ULT) || (Inputs->CpuModel == cmKBL_ULX_ULT));
  UltUlx_Lpddr3_2133 = (Outputs->Frequency >= f2133) && (UltUlx) && (Lpddr3);


  switch (OemStatusCommand) {
    case OemSpdProcessingRun:
      break;

    case OemPreTraining:
      break;

    case OemMcTrainingRun:
      break;

    case OemMcResetRun:
      break;

    case OemEarlyCommandTraining:
      if (Lpddr3) {
        Status = mrcSuccess;  // This is required for LPDDR
      } else if (!TrainingEnables->ECT) {
        Status = mrcFail; // Skip this training step
      } else if (Ddr4) {
        Status = mrcFail; // Cannot run ECT on DDR4 due to PDA not stable before basic training
      }
      break;

    case OemJedecInitLpddr3:    // MrcJedecInitLpddr3
      if (!Lpddr3) {            // Skip this step for non-LPDDR
        Status = mrcFail;
      }
      break;

    case OemSenseAmpTraining:
      if (!TrainingEnables->SOT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadMprTraining:
      if (!TrainingEnables->RDMPRT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReceiveEnable:
      if (!TrainingEnables->RCVET) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemJedecWriteLeveling:
      if (!TrainingEnables->JWRL) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemLpddrLatencySetB:
      if (Lpddr3 && (Inputs->LpddrMemWriteLatencySet == 1)) {
        Status = mrcSuccess;
      } else {
        Status = mrcFail;  // Skip this step for non-LPDDR or if (LPDDR and Latency Set B not chosen)
      }
      break;

    case OemWriteDqDqs:
      if (!TrainingEnables->WRTC1D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemEarlyWrDsEq:
      if ((!TrainingEnables2->EWRDSEQ) || !UltUlx_Lpddr3_2133) {
        // Enable only for ULT/ULX LPDDR3 2133 and above
        Status = mrcFail; // Skip this training step
      }
      break;
    case OemWriteVoltage:
      if (!TrainingEnables->WRVC1D || !Ddr4) { // This is for DDR4 only
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemEarlyWriteDqDqs2D:
      if (!TrainingEnables->EWRTC2D || (!(Ddr4 || UltUlx_Lpddr3_2133))) { // This is for DDR4 Or UltUlx_Lpddr3_2133 only
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemEarlyReadDqDqs2D:
      if (!TrainingEnables->ERDTC2D || !Ddr4) { // This is for DDR4 only
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemEarlyReadMprDqDqs2D:
      if (!TrainingEnables->ERDMPRTC2D || !Ddr4) { // This is for DDR4 only
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadDqDqs:
      if (!TrainingEnables->RDTC1D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDdr4Map:
      if ((!Inputs->DDR4MAP) || !Ddr4) { // This is for DDR4 only
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDimmODTTraining:
      if (!TrainingEnables->DIMMODTT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDimmRonTraining:
      if ((!TrainingEnables->DIMMRONT) || (DdrType == MRC_DDR_TYPE_DDR3)) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteSlewRate:
      if (!TrainingEnables->WRSRT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteDriveUpDn:
      if (!TrainingEnables->WRDSUDT || !Ddr4) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteDriveStrengthEq:
      if (!TrainingEnables->WRDSEQT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadODTTraining:
      if (!TrainingEnables->RDODTT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadEQTraining:
      if (!TrainingEnables->RDEQT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemPostTraining:
      if (Lpddr3) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadAmplifierPower:
      if (!TrainingEnables->RDAPT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemOptimizeComp:
      break;

    case OemForceOltm:
      if (!Ddr4) {        // This is for DDR4 only
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteDqDqs2D:
      if (!TrainingEnables->WRTC2D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadDqDqs2D:
      if (!TrainingEnables->RDTC2D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemCmdVoltCentering:
      if (!TrainingEnables->CMDVC) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemCmdSlewRate:
      if (!TrainingEnables2->CMDSR || !Ddr4 || (TrainingMode == MrcTmPower)) { // Only run on DDR4 in Margin Training mode
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemCmdDriveStrengthEq:
      if (!TrainingEnables2->CMDDSEQ || (!(Ddr4 || UltUlx_Lpddr3_2133))) { // This is for DDR4 Or UltUlx_Lpddr3_2133 only
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemCmdNormalization:
      if (!TrainingEnables2->CMDNORM) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemCmdVoltCenterPreLct:
      if (!TrainingEnables->CMDVC || !Lpddr3) { // Pre-LCT CMDVC should only run on LPDDR3, skip on DDR3/4
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteVoltCentering2D:
      if (!TrainingEnables->WRVC2D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadVoltCentering2D:
      if (!TrainingEnables->RDVC2D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemLateCommandTraining:
      if (!TrainingEnables->LCT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemRoundTripLatency:
      if (!TrainingEnables->RTL) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemTurnAroundTimes:
      //
      // @todo: TAT has to be updated for LPDDR3, skip it for now.
      //
      if ((!TrainingEnables->TAT) || Lpddr3) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDdr4TxVrefRange:
      if ((!TrainingEnables2->TXDQVREF) || (!Ddr4)) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemRcvEnCentering1D:
      if ((!TrainingEnables->RCVENC1D) || !Lpddr3) {
        Status = mrcFail;  // Skip this step for non-LPDDR
      }
      break;

    case OemRetrainMarginCheck:
      if ((!TrainingEnables->RMC) || (Inputs->PowerTrainingMode != MrcTmPower)) {
        Status = mrcFail; // Skip if disabled or not in Power Training mode
      }
      break;


    case OemRmt:
      if (!TrainingEnables->RMT) {
        Status = mrcFail; // Skip this training step
      }
      break;

#ifdef BDAT_SUPPORT
    case OemRmtPerBit:
      if ((!Inputs->BdatEnable) || (Inputs->BdatTestType != RankMarginToolPerBitType)) {
        Status = mrcFail; // Skip this training step
      }
      break;
#endif

    case OemMemTest:
      if (!TrainingEnables->MEMTST) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemAliasCheck:
      if (!TrainingEnables->ALIASCHK) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemHwMemInit:
      if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint == MrcSaGvPointLow)) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemBeforeNormalMode:
      break;

    case OemAfterNormalMode:
      MrcTurnaroundTimingOverrides (MrcData);
      break;

    case OemFrequencySetDone:
#ifdef SSA_FLAG
      SsaBiosInitialize (MrcData);
#endif // SSA_FLAG
      break;

#ifdef BDAT_SUPPORT
    case OemMrcFillBdat:
      if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint == MrcSaGvPointLow)) {
        Status = mrcFail; // Skip this training step
      }
      break;
#endif // BDAT_SUPPORT

    case OemSaGvSwitch:
      if (Inputs->SaGv != MrcSaGvEnabled) {
        Status = mrcFail; // Skip this training step
      }
      break;

    default:
      break;
  }

  Status |= MrcCall->MrcCheckpoint (MrcData, OemStatusCommand, NULL);
  return Status;
}

/**
  Initializes the memory controller and DIMMs.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Select  - Specific task index to execute, or zero to run all tasks from the call table.
                            Used in the interpreter.

  @retval mrcSuccess if the initialization succeeded, otherwise an error status indicating the failure.
**/
MrcStatus
MrcStartMemoryConfiguration (
  IN OUT MrcParameters *const MrcData,
  IN     UINT32               Select
  )
{
  const MRC_FUNCTION    *MrcCall;
  const CallTableEntry  *Task;
  MrcDebug              *Debug;
  MrcInput              *Inputs;
  MrcOutput             *Outputs;
  MrcIntOutput          *MrcIntData;
  MrcSaGvPoint          SaGvPoint;
  MrcSaGv               SaGv;
  UINT64                start_time;
  UINT64                finish_time;
  UINT32                ElapsedTime;
  UINT32                TotalTime;
  UINT32                PointTime;
  UINT32                LowestStackAddr;
  UINT32                RetrainLoop;
  UINT16                index;
  UINT8                 Run;
  MrcPostCode           post_code;
  MrcPostCode           PostCodeOut;
  MrcStatus             CpStatus;
  MrcStatus             MrcStatus;
  MrcBootMode           BootMode;
  MrcUpmPwrRetrainLimits  RetrainLimits[MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS];
  INT32                 DebugLevel;
#ifdef BDAT_SUPPORT
  MRC_BDAT_SCHEMA_LIST_HOB  *SaveBdatSchemasHob;
  BDAT_MEMORY_DATA_HOB      *SaveBdatMemoryHob[MAX_SCHEMA_LIST_LENGTH];
#endif


  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  SaGv    = Inputs->SaGv;

  BootMode  = Inputs->BootMode;
  DebugLevel = Inputs->DebugLevel;
#ifndef MRC_MINIBIOS_BUILD
  MRC_DEBUG_MSG_OPEN (MrcData, Inputs->DebugLevel, Inputs->DebugStream, Inputs->SerialBuffer, Inputs->SerialBufferSize);
#endif
  if (Select == 0) {
    MrcVersionGet (MrcData, &Outputs->Version);
    MrcVersionPrint (MrcData, &Outputs->Version);
  }
#ifdef SSA_FLAG
  InitializeRegisterCache (MrcData);
#endif
  MrcStatus = mrcFail;
  post_code = MRC_INITIALIZATION_START;
  Run       = 1;
  TotalTime = 0;
  LowestStackAddr = Debug->LowestStackAddr;

  for (SaGvPoint = MrcSaGvPointLow; SaGvPoint <= MrcSaGvPointHigh; SaGvPoint++) {
    //
    // First iteration  = LOW point
    // Second iteration = HIGH point
    //
    if ((SaGv == MrcSaGvDisabled) || (SaGv == MrcSaGvFixedHigh)) {
      SaGvPoint = MrcSaGvPointHigh;
    }

    MrcIntData->SaGvPoint = SaGvPoint;
    Inputs->Iteration = 0;
    PointTime = 0;

    //
    // Reset UPM/PWR limits to initial values; previous SAGV point might have done retrain.
    //
    MrcCall->MrcCopyMem (
               (UINT8 *) RetrainLimits,
               (UINT8 *) InitialLimits,
               sizeof (MrcUpmPwrRetrainLimits) * MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS
               );

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SAGV: %sabled, running at %s point\n", (SaGv == MrcSaGvEnabled) ? "En" : "Dis", SaGvPoint ? "HIGH" : "LOW");

    for (RetrainLoop = 0; RetrainLoop <= 1; RetrainLoop++) {
      MrcVersionGet (MrcData, &Outputs->Version);
      MrcIntData->UpmPwrRetrainLimits.Pointer = RetrainLimits;
      for (index = 0; Run && (index < ARRAY_COUNT (MrcCallTable)); index++, post_code++) {
        Task = &MrcCallTable[index];
        //
        // Decide if we need to execute the selected MRC task.
        //
        if ((NULL == Task->mrc_task) || (Inputs->Iteration >= Task->iteration)) {
          continue;
        }
        if   (((BootMode == bmS3)   && (Task->policy_flag & MF_S3))
              ||  ((BootMode == bmFast) && (Task->policy_flag & MF_FAST))
              ||  ((BootMode == bmWarm) && (Task->policy_flag & MF_WARM))
              ||  ((BootMode == bmCold) && (Task->policy_flag & MF_COLD))
              ||  ((Select != 0))) {
          if  ((Select == 0) || (Select == index)) {
            if (((MrcIntData->SaGvPoint == MrcSaGvPointLow)  && (Task->policy_flag & MF_GV_LOW))  ||
                ((MrcIntData->SaGvPoint == MrcSaGvPointHigh) && (Task->policy_flag & MF_GV_HIGH)) ||
                (SaGv == MrcSaGvDisabled)) {
              if (Task->oem_cmd < OemNumOfCommands) {
                CpStatus = MrcInternalCheckPoint (MrcData, Task->oem_cmd, NULL);
                if (mrcSuccess != CpStatus) {
                  continue;
                }
              }
              //
              // Output post code to post code I/O port.
              //
              PostCodeOut = (Task->post_code_ovr == POST_CODE_NO_OVR) ? post_code : Task->post_code_ovr;
              if ((Select == 0) || ((Select > 0) && (Select == index))) {
                MrcCall->MrcDebugHook (MrcData, PostCodeOut);
#ifdef SSA_FLAG
                SsaBiosCheckpoint (MrcData, PostCodeOut, NULL);
#endif // SSA_FLAG
              }
              //
              // Output debug string to serial output and execute the MRC task.
              //
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nMRC task -- %s -- Started.\n", Task->String);
              if (!Task->DebugPrint) {
                DebugLevel = Debug->Level;
                Debug->Level = MSG_LEVEL_NEVER;
              }
              start_time  = MrcCall->MrcGetCpuTime (MrcData);
              MrcStatus   = Task->mrc_task (MrcData);
              finish_time = MrcCall->MrcGetCpuTime (MrcData);
              if (!Task->DebugPrint) {
                Debug->Level = DebugLevel;
              }
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_ERROR,
                "MRC task %s -- %s, Status = %Xh.",
                Task->String,
                (mrcSuccess == MrcStatus) ? "SUCCEEDED" : "FAILED",
                MrcStatus
                );
              if (Debug->LowestStackAddr < LowestStackAddr) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, " Stack Depth: %d\n", Debug->TopStackAddr - Debug->LowestStackAddr);
                LowestStackAddr = Debug->LowestStackAddr;
              } else {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");
              }
              if (mrcSuccess != MrcStatus) {
                Run = 0;  // Stop task execution on failure.
              }

              ElapsedTime = (UINT32) (finish_time - start_time);
              TotalTime += ElapsedTime;
              PointTime += ElapsedTime;
              // <MrcTimer Task="Print input parameters" msec="2"/>
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_TIME, "<MrcTimer Task=\"%s\" msec=\"%u\"/>\n", Task->String, ElapsedTime);

              if (Inputs->RmtPerTask && (Task->policy_flag & MF_RMT)) {  // Run RMT after this task
                MrcRankMarginTool (MrcData);
              }
            }
          } // Select match
        } // if boot mode match
      } // for index
      //
      // Check if MRC failed due to RetrainMarginCheck
      //
      if (MrcStatus == mrcRetrain) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nRerunning training with higher UPM/PWR limits!\n");
#ifdef BDAT_SUPPORT
        SaveBdatSchemasHob = Outputs->BdatSchemasHob.Pointer;
        for (index = 0; index < MAX_SCHEMA_LIST_LENGTH; index++) {
          SaveBdatMemoryHob[index] = Outputs->BdatMemoryHob[index].Pointer;
        }
#endif // BDAT_SUPPORT
        MrcCall->MrcSetMem ((UINT8 *) Outputs, sizeof (MrcOutput), 0);
        MrcCall->MrcSetMem ((UINT8 *) MrcIntData, sizeof (MrcIntOutput), 0);
        Outputs->Size              = sizeof (MrcOutput);
        MrcIntData->Size           = sizeof (MrcIntOutput);
        MrcIntData->SaGvPoint      = SaGvPoint;
#ifdef BDAT_SUPPORT
        Outputs->BdatSchemasHob.Pointer = SaveBdatSchemasHob;
        for (index = 0; index < MAX_SCHEMA_LIST_LENGTH; index++) {
          Outputs->BdatMemoryHob[index].Pointer = SaveBdatMemoryHob[index];
        }
#endif // BDAT_SUPPORT
        Outputs->UpmPwrRetrainFlag = TRUE;
#ifdef MRC_MINIBIOS_BUILD
#ifdef SSA_FLAG
        MrcIntData->SsaBiosServicesPpi = (UINT32) &MrcIntData->SsaBiosServicesBuffer;
#endif // SSA_FLAG
#endif // MRC_MINIBIOS_BUILD
        MRC_DEBUG_MSG_OPEN (MrcData, Inputs->DebugLevel, Inputs->DebugStream, Inputs->SerialBuffer, Inputs->SerialBufferSize);
        Inputs->Iteration++;
        Run = 1;
      } else {
        break;    // No need to retrain
      }
    } // Retrain loop

    if (SaGv == MrcSaGvFixedLow) {
      break;  // Only run LOW SAGV point
    }

    if ((SaGv == MrcSaGvEnabled) && (SaGvPoint == MrcSaGvPointLow)) {
      //
      // Prepare for the second MRC iteration
      //
#ifdef BDAT_SUPPORT
      SaveBdatSchemasHob = Outputs->BdatSchemasHob.Pointer;
      for (index = 0; index < MAX_SCHEMA_LIST_LENGTH; index++) {
        SaveBdatMemoryHob[index] = Outputs->BdatMemoryHob[index].Pointer;
      }
#endif // BDAT_SUPPORT
      MrcCall->MrcSetMem ((UINT8 *) Outputs, sizeof (MrcOutput), 0);
      MrcCall->MrcSetMem ((UINT8 *) MrcIntData, sizeof (MrcIntOutput), 0);
      MrcIntData->Size  = sizeof (MrcIntOutput);
      Outputs->Size     = sizeof (MrcOutput);
#ifdef BDAT_SUPPORT
      Outputs->BdatSchemasHob.Pointer = SaveBdatSchemasHob;
      for (index = 0; index < MAX_SCHEMA_LIST_LENGTH; index++) {
        Outputs->BdatMemoryHob[index].Pointer = SaveBdatMemoryHob[index];
      }
#endif // BDAT_SUPPORT
      MrcIntData->SaGvPoint = MrcSaGvPointHigh;
      MRC_DEBUG_MSG_OPEN (MrcData, Inputs->DebugLevel, Inputs->DebugStream, Inputs->SerialBuffer, Inputs->SerialBufferSize);
    }

    if (SaGv == MrcSaGvEnabled) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_TIME,
        "MRC timer: Total time for SAGV %s point = %u msec.\n",
        SaGvPoint ? "HIGH" : "LOW",
        PointTime
        );
    }
  } // for GvPoint

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_TIME, "MRC timer: Total time to execute tasks = %u msec.\n", TotalTime);

  return MrcStatus;
}

/**

@brief

  Get the number of call table entries.

  @param[in, out] MrcData - Include all MRC global data.

  @retval The number of call table entries.

**/
UINT16
MrcGetCallTableCount (
  IN OUT MrcParameters *const MrcData
  )
{
  return ARRAY_COUNT (MrcCallTable);
}
