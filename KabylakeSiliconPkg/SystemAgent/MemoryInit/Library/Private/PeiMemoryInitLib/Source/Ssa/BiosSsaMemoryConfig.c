/** @file
  This file contains the BIOS implementation of the BIOS-SSA Memory Configuration API.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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
#include "SsaBios.h"
#include "SsaMemoryConfig.h"
#include "MrcSsaServices.h"
#include "MrcSsaCommon.h"
#include "MrcCommon.h"
#include "McAddress.h"
#include "MrcRmtData.h"
#include "MrcGeneral.h"

#ifdef SSA_FLAG

#define CPU_SOCKET_BIT_MASK             (((UINT32) (~0)) >> (32 - MAX_CPU_SOCKETS))
#define MAX_BUS_WIDTH                   (64)
#define SPD_SENSOR_BASE_ADDRESS         (0x30)
#define SPD_SENSOR_TEMPERATURE_OFFSET   (5)
#define SINGLE_CAST                     (0)
#define MULTI_CAST                      (1)
#define UPDATE_MRCDATA                  (1)
#define RCVEN_PI_SETTING_MAX            (DDRDATA0CH0_CR_RXTRAINRANK0_RxRcvEnPi_MAX)
#define RCVEN_PI_SETTING_MIN            (DDRDATA0CH0_CR_RXTRAINRANK0_RxRcvEnPi_MIN)
#define RCVEN_OFFSET_MAX                (DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MAX)
#define RCVEN_OFFSET_MIN                (DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MIN)
#define RXDQS_PI_SETTING_MAX            (DDRDATA0CH0_CR_RXTRAINRANK0_RxDqsPPi_MAX)
#define RXDQS_PI_SETTING_MIN            (DDRDATA0CH0_CR_RXTRAINRANK0_RxDqsPPi_MIN)
#define RXDQS_OFFSET_MAX                (MAX_POSSIBLE_TIME)
#define RXDQS_OFFSET_MIN                ((-1) * (RXDQS_OFFSET_MAX + 1))
#define RXODT_OFFSET_MAX                (DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_MAX)
#define RXODT_OFFSET_MIN                (DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_MIN)
#define RXODT_UP_OFFSET_MAX             DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MAX
#define RXODT_UP_OFFSET_MIN             DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MIN
#define RXODT_DN_OFFSET_MAX             DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MAX
#define RXODT_DN_OFFSET_MIN             DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MIN
#define DRAM_DRV_STR_DELAY_DDR3_MAX     (1)
#define DRAM_DRV_STR_DELAY_DDR3_MIN     (0)
#define DRAM_DRV_STR_DELAY_LPDDR3_MAX   (2)
#define DRAM_DRV_STR_DELAY_LPDDR3_MIN   (0)
#define DRAM_DRV_STR_DELAY_DDR4_MAX     (1)
#define DRAM_DRV_STR_DELAY_DDR4_MIN     (0)
#define RXEQ_OFFSET_MAX                 (DDRDATA0CH0_CR_RXTRAINRANK0_RxEq_MAX)
#define RXEQ_OFFSET_MIN                 (DDRDATA0CH0_CR_RXTRAINRANK0_RxEq_MIN)
#define RX_CTLE_R_OFFSET_MAX            (DDRDATA0CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_MAX)
#define RX_CTLE_R_OFFSET_MIN            (DDRDATA0CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_MIN)
#define RX_CTLE_C_OFFSET_MAX            (DDRDATA0CH0_CR_DDRCRDATACONTROL2_Cben_MAX)
#define RX_CTLE_C_OFFSET_MIN            (DDRDATA0CH0_CR_DDRCRDATACONTROL2_Cben_MIN)
#define TXDQS_PI_SETTING_MAX            (DDRDATA0CH0_CR_TXTRAINRANK0_TxDqsDelay_MAX)
#define TXDQS_PI_SETTING_MIN            (DDRDATA0CH0_CR_TXTRAINRANK0_TxDqsDelay_MIN)
#define TXDQS_OFFSET_MAX                (DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MAX)
#define TXDQS_OFFSET_MIN                (DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MIN)
#define TXDQ_PI_SETTING_MAX             (DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX)
#define TXDQ_PI_SETTING_MIN             (DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MIN)
#define TXDQ_OFFSET_MAX                 (DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MAX)
#define TXDQ_OFFSET_MIN                 (DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MIN)
#define RXVREF_SETTING_MAX              (DDRDATA0CH0_CR_RXTRAINRANK0_RxVref_MAX)
#define RXVREF_SETTING_MIN              (DDRDATA0CH0_CR_RXTRAINRANK0_RxVref_MIN)
#define RXVREF_OFFSET_MAX               (DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MAX)
#define RXVREF_OFFSET_MIN               (DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MIN)
#define TXVREF_OFFSET_MAX               (DDRDATA7CH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MAX)
#define TXVREF_OFFSET_MIN               (DDRDATA7CH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MIN)
#define TXVREF_OFFSET_DDR4_MAX          (MAX_POSSIBLE_DDR4_WRITE_VREF)
#define TXVREF_OFFSET_DDR4_MIN          (-MAX_POSSIBLE_DDR4_WRITE_VREF)
#define CMDVREF_OFFSET_MAX              (DDRDATA7CH1_CR_DDRCRVREFADJUST1_CAVrefCtl_MAX)
#define CMDVREF_OFFSET_MIN              (DDRDATA7CH1_CR_DDRCRVREFADJUST1_CAVrefCtl_MIN)
#define RXDQBIT_OFFSET_MAX              (DDRDATA0CH0_CR_RXPERBITRANK0_Lane0_MAX)
#define RXDQBIT_OFFSET_MIN              (DDRDATA0CH0_CR_RXPERBITRANK0_Lane0_MIN)
#define TXEQ_OFFSET_MAX                 (DDRDATA0CH0_CR_TXTRAINRANK0_TxEqualization_MAX)
#define TXEQ_OFFSET_MIN                 (DDRDATA0CH0_CR_TXTRAINRANK0_TxEqualization_MIN)
#define TXDQBIT_OFFSET_MAX              (DDRDATA0CH0_CR_TXPERBITRANK0_Lane0_MAX)
#define TXDQBIT_OFFSET_MIN              (DDRDATA0CH0_CR_TXPERBITRANK0_Lane0_MIN)
#define TXRON_UP_OFFSET_MAX             DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MAX
#define TXRON_UP_OFFSET_MIN             DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MIN
#define TXRON_DN_OFFSET_MAX             DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MAX
#define TXRON_DN_OFFSET_MIN             DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MIN
#define TX_SLEW_RATE_OFFSET_MAX         (DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MAX)
#define TX_SLEW_RATE_OFFSET_MIN         (DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MIN)
#define CLOCK_OFFSET_MAX                (DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MAX)
#define CLOCK_OFFSET_MIN                (DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MIN)
#define CMDN_OFFSET_MAX                 (DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX)
#define CMDN_OFFSET_MIN                 (DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN)
#define CMDS_OFFSET_MAX                 (DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX)
#define CMDS_OFFSET_MIN                 (DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN)
#define CMD_CKE_OFFSET_MAX              (DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX)
#define CMD_CKE_OFFSET_MIN              (DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN)
#define CTL_CS_OFFSET_MAX               (DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MAX)
#define CTL_CS_OFFSET_MIN               (DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MIN)
#define CTL_CKE_OFFSET_MAX              (DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_MAX)
#define CTL_CKE_OFFSET_MIN              (DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_MIN)

GLOBAL_REMOVE_IF_UNREFERENCED const MRC_SYSTEM_INFO SysInfoConst = {
  MAX_CPU_SOCKETS,               // MaxNumberSockets
  MAX_CONTROLLERS,               // MaxNumberControllers
  MAX_CHANNEL,                   // MaxNumberChannels
  MAX_DIMMS_IN_CHANNEL,          // MaxNumberDimms
  MAX_RANK_IN_DIMM,              // MaxNumberLogicalRanks
  CPU_SOCKET_BIT_MASK,           // SocketBitMask
  MAX_BUS_WIDTH,                 // BusWidth
  0,                             // BusFreq
  FALSE,                         // IsEccEnabled
  0                              // BootMode
};

/**
  Calculate the minimum and maximum offset to the specified setting.

  @param[in]      MrcData   - Pointer to the MRC global data area.
  @param[in]      Minimum   - The smallest value that the setting can be.
  @param[in]      Current   - The current value of the setting.
  @param[in]      Maximum   - The largest value that the setting can be.
  @param[in, out] MinOffset - Minimum offset supported by the given margin group.
  @param[in, out] MaxOffset - Maximum offset supported by the given margin group.

  @retval Success.
**/
static
SSA_STATUS
CalcMinMax (
  MrcParameters *const MrcData,
  const INT16          Minimum,
  const INT16          Current,
  const INT16          Maximum,
  INT16 *const         MinOffset,
  INT16 *const         MaxOffset
  )
{
  INT16    DistanceLow;
  INT16    DistanceHigh;

  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "CalcMinMax Pi %d %d %d MinO %d MaxO %d\n", Minimum, Current, Maximum, *MinOffset, *MaxOffset);
  DistanceLow  = Minimum - Current;
  DistanceLow  = (-1) * ABS (DistanceLow);
  DistanceHigh = Maximum - Current;
  *MinOffset   = MAX (*MinOffset, DistanceLow);
  *MaxOffset   = MIN (*MaxOffset, DistanceHigh);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "PDL %d PDH %d ", DistanceLow, DistanceHigh);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "MinO %d MaxO %d\n", *MinOffset, *MaxOffset);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[in]  LogicalRank - Zero based rank number in the channel.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsRecEnDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  UINT32        LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  static const struct {
    GSM_GT Group;
    INT16  Min;
    INT16  Max;
  } Limits[] = {
    {RecEnDelay,  RCVEN_PI_SETTING_MIN, RCVEN_PI_SETTING_MAX},
    {RecEnOffset, RCVEN_OFFSET_MIN,     RCVEN_OFFSET_MAX}
  };
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Rank;
  UINT8 Byte;
  UINT8 ByteEnd;
  UINT8 Index;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  // Note: This parameter is channel specific, but the training values examined
  // to determine the limits are rank specific so the rank input value is
  // ignored and all ranks present are examined.

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM)) {
      for (Byte = 0; Byte < ByteEnd; Byte++) {
        for (Index = 0; Index < (sizeof (Limits) / sizeof (Limits[0])); Index++) {
          MrcGetSetDdrIoGroup (
            MrcData,
            (UINT8) Socket,
            (UINT8) Channel,
            MRC_IGNORE_ARG_8,
            (UINT8) Rank,
            (UINT8) Byte,
            MRC_IGNORE_ARG_8,
            MRC_IGNORE_ARG_8,
            DdrLevel,
            Limits[Index].Group,
            GSM_READ_CSR | GSM_READ_ONLY,
            &Value
            );
          CalcMinMax (MrcData, Limits[Index].Min, (INT16) Value, Limits[Index].Max, &PiOffsetMin, &PiOffsetMax);
        } // end for each index
      } // end for each byte
    } // end for each rank
  }
  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsRecEnDelay %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[in]  LogicalRank - Zero based rank number in the channel.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsRxDqsDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  UINT32        LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  static const struct {
    GSM_GT Group;
    INT16  Min;
    INT16  Max;
  } Limits[] = {
    {RxDqsPDelay, RXDQS_PI_SETTING_MIN, RXDQS_PI_SETTING_MAX},
    {RxDqsNDelay, RXDQS_PI_SETTING_MIN, RXDQS_PI_SETTING_MAX},
    {RxDqsOffset, RXDQS_OFFSET_MIN,     RXDQS_OFFSET_MAX}
  };
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Rank;
  UINT8 Byte;
  UINT8 ByteEnd;
  UINT8 Index;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  // Note: This parameter is channel specific, but the training values examined
  // to determine the limits are rank specific so the rank input value is
  // ignored and all ranks present are examined.

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM)) {
      for (Byte = 0; Byte < ByteEnd; Byte++) {
        for (Index = 0; Index < (sizeof (Limits) / sizeof (Limits[0])); Index++) {
          MrcGetSetDdrIoGroup (
            MrcData,
            (UINT8) Socket,
            (UINT8) Channel,
            MRC_IGNORE_ARG_8,
            (UINT8) Rank,
            (UINT8) Byte,
            MRC_IGNORE_ARG_8,
            MRC_IGNORE_ARG_8,
            DdrLevel,
            Limits[Index].Group,
            GSM_READ_CSR | GSM_READ_ONLY,
            &Value
            );
          CalcMinMax (MrcData, Limits[Index].Min, (INT16) Value, Limits[Index].Max, &PiOffsetMin, &PiOffsetMax);
        } // end for each index
      } // end for each byte
    } // end for each rank
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsRxDqsDelay %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[in]  LogicalRank - Zero based rank number in the channel.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsRxDqBitDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  UINT32        LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Rank;
  UINT8 Byte;
  UINT8 ByteEnd;
  UINT8 Bit;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  // Note: This parameter is channel specific, but the training values examined
  // to determine the limits are rank specific so the rank input value is
  // ignored and all ranks present are examined.

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM)) {
      for (Byte = 0; Byte < ByteEnd; Byte++) {
        for (Bit = 0; Bit < MAX_BITS; Bit++) {
          MrcGetSetDdrIoGroup (
            MrcData,
            (UINT8) Socket,
            (UINT8) Channel,
            MRC_IGNORE_ARG_8,
            (UINT8) Rank,
            (UINT8) Byte,
            (UINT8) Bit,
            MRC_IGNORE_ARG_8,
            DdrLevel,
            RxDqBitDelay,
            GSM_READ_CSR | GSM_READ_ONLY,
            &Value
            );
          CalcMinMax (MrcData, RXDQBIT_OFFSET_MIN, (INT16) Value, RXDQBIT_OFFSET_MAX, &PiOffsetMin, &PiOffsetMax);
        }
      } // end for each byte
    } // end for each rank
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsRxDqBitDelay %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsRxOdtDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT64 Value;

  Value = 0;
  MrcGetSetDdrIoGroup (
    MrcData,
    (UINT8) Socket,
    MRC_IGNORE_ARG_8,
    MRC_IGNORE_ARG_8,
    MRC_IGNORE_ARG_8,
    MRC_IGNORE_ARG_8,
    MRC_IGNORE_ARG_8,
    MRC_IGNORE_ARG_8,
    DdrLevel,
    RxOdt,
    GSM_READ_CSR | GSM_READ_ONLY,
    &Value
    );
  CalcMinMax (MrcData, RXODT_OFFSET_MIN, (INT16) Value, RXODT_OFFSET_MAX, MinOffset, MaxOffset);

  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsRxOdtDelay %u %u %u %u %d %d %u\n", Socket, Controller, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsRxOdtUpDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Byte;
  UINT8 ByteEnd;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  for (Byte = 0; Byte < ByteEnd; Byte++) {
    MrcGetSetDdrIoGroup (
      MrcData,
      (UINT8) Socket,
      (UINT8) Channel,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      (UINT8) Byte,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      DdrLevel,
      RxOdtUp,
      GSM_READ_CSR | GSM_READ_ONLY,
      &Value
      );
    CalcMinMax (MrcData, RXODT_UP_OFFSET_MIN, (INT16) Value, RXODT_UP_OFFSET_MAX, &PiOffsetMin, &PiOffsetMax);
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsRxOdtUpDelay %u %u %u %d %d %u\n", Socket, Controller, Channel, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsRxOdtDnDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Byte;
  UINT8 ByteEnd;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  for (Byte = 0; Byte < ByteEnd; Byte++) {
    MrcGetSetDdrIoGroup (
      MrcData,
      (UINT8) Socket,
      (UINT8) Channel,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      (UINT8) Byte,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      DdrLevel,
      RxOdtDn,
      GSM_READ_CSR | GSM_READ_ONLY,
      &Value
      );
    CalcMinMax (MrcData, RXODT_DN_OFFSET_MIN, (INT16) Value, RXODT_DN_OFFSET_MAX, &PiOffsetMin, &PiOffsetMax);
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsRxOdtDnDelay %u %u %u %d %d %u\n", Socket, Controller, Channel, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsDramDrvStrDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  MrcOutput           *Outputs;
  MrcChannelOut       *ChannelOut;
  MrcDdrType          DdrType;
  UINT8               Index;
  UINT8               Rank;
  INT16               PiOffsetMin;
  INT16               PiOffsetMax;
  UINT16              *MrReg;
  UINT16              MrValue;
  UINT16              DimmRonMask;
  UINT16              DimmRon;
  INT32               Value;
  static const UINT8  LpddrRonEnc[] = {0x1, 0x2, 0x3}; // LPDDR3 Ron    :34, 40, 48 Ohm
  static const UINT16 Ddr3RonEnc[]  = {0x00, 0x02};    // DDR3 Ron      :40, 34 Ohms
  static const UINT16 Ddr4RonEnc[]  = {0x00, 0x02};    // DDR4 Ron      :34, 48 Ohms

  Outputs     = &MrcData->Outputs;
  DdrType     = Outputs->DdrType;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;
  Value       = 0;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM)) {
      MrReg = &ChannelOut->Dimm[Rank / 2].Rank[ (Rank % 2) ].MR[mrMR0];
      if (DdrType == MRC_DDR_TYPE_LPDDR3) {
        MrValue     = MrReg[mrMR3];
        DimmRonMask = (UINT16) (MRC_BIT3 | MRC_BIT2 | MRC_BIT1 | MRC_BIT0);
        DimmRon     = MrValue & DimmRonMask;
        for (Index = 0; Index < sizeof (LpddrRonEnc) / sizeof (LpddrRonEnc[0]); Index++) {
          if (DimmRon == LpddrRonEnc[Index]) {
            Value = Index;
          }
        }
        CalcMinMax (MrcData, DRAM_DRV_STR_DELAY_LPDDR3_MIN, (INT16) Value, DRAM_DRV_STR_DELAY_LPDDR3_MAX, &PiOffsetMin, &PiOffsetMax);
      } else if (DdrType == MRC_DDR_TYPE_DDR4) {
        MrValue = MrReg[mrMR1];
        DimmRonMask = (UINT16) (MRC_BIT2 | MRC_BIT1);
        DimmRon     = MrValue & DimmRonMask;
        for (Index = 0; Index < sizeof (Ddr4RonEnc) / sizeof (Ddr4RonEnc[0]); Index++) {
          if (DimmRon == Ddr4RonEnc[Index]) {
            Value = Index;
          }
        }
        CalcMinMax (MrcData, DRAM_DRV_STR_DELAY_DDR4_MIN, (INT16) Value, DRAM_DRV_STR_DELAY_DDR4_MAX, &PiOffsetMin, &PiOffsetMax);
      } else {
        MrValue = MrReg[mrMR1];
        DimmRonMask = (UINT16) (MRC_BIT5 | MRC_BIT1);
        DimmRon     = MrValue & DimmRonMask;
        for (Index = 0; Index < sizeof (Ddr3RonEnc) / sizeof (Ddr3RonEnc[0]); Index++) {
          if (DimmRon == Ddr3RonEnc[Index]) {
            Value = Index;
          }
        }
        CalcMinMax (MrcData, DRAM_DRV_STR_DELAY_DDR3_MIN, (INT16) Value, DRAM_DRV_STR_DELAY_DDR3_MAX, &PiOffsetMin, &PiOffsetMax);
      }
    } // end for each rank
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsDramDrvStrDelay %u %u %u %u %d %d %u\n", Socket, Controller, Channel, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[in]  LogicalRank - Zero based rank number in the channel.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsRxEqDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  UINT32        LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Rank;
  UINT8 Byte;
  UINT8 ByteEnd;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM)) {
      for (Byte = 0; Byte < ByteEnd; Byte++) {
        MrcGetSetDdrIoGroup (
          MrcData,
          (UINT8) Socket,
          (UINT8) Channel,
          MRC_IGNORE_ARG_8,
          (UINT8) Rank,
          (UINT8) Byte,
          MRC_IGNORE_ARG_8,
          MRC_IGNORE_ARG_8,
          DdrLevel,
          RxEq,
          GSM_READ_CSR | GSM_READ_ONLY,
          &Value
          );
        CalcMinMax (MrcData, RXEQ_OFFSET_MIN, (INT16) Value, RXEQ_OFFSET_MAX, &PiOffsetMin, &PiOffsetMax);
      } // end for each byte
    } // end for each rank
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsRxEqDelay %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsRxCtleRDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Byte;
  UINT8 ByteEnd;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  for (Byte = 0; Byte < ByteEnd; Byte++) {
    MrcGetSetDdrIoGroup (
      MrcData,
      (UINT8) Socket,
      (UINT8) Channel,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      (UINT8) Byte,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      DdrLevel,
      RxCtleR,
      GSM_READ_CSR | GSM_READ_ONLY,
      &Value
      );
    CalcMinMax (MrcData, RX_CTLE_R_OFFSET_MIN, (INT16) Value, RX_CTLE_R_OFFSET_MAX, &PiOffsetMin, &PiOffsetMax);
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsRxCtleRDelay %u %u %u %u %d %d %u\n", Socket, Controller, Channel, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsRxCtleCDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Byte;
  UINT8 ByteEnd;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  for (Byte = 0; Byte < ByteEnd; Byte++) {
    MrcGetSetDdrIoGroup (
      MrcData,
      (UINT8) Socket,
      (UINT8) Channel,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      (UINT8) Byte,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      DdrLevel,
      RxCtleC,
      GSM_READ_CSR | GSM_READ_ONLY,
      &Value
      );
    CalcMinMax (MrcData, RX_CTLE_C_OFFSET_MIN, (INT16) Value, RX_CTLE_C_OFFSET_MAX, &PiOffsetMin, &PiOffsetMax);
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsRxCtleCDelay %u %u %u %u %d %d %u\n", Socket, Controller, Channel, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[in]  LogicalRank - Zero based rank number in the channel.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsTxDqsDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  UINT32        LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  static const struct {
    GSM_GT Group;
    INT16  Min;
    INT16  Max;
  } Limits[] = {
    {TxDqsDelay,  TXDQS_PI_SETTING_MIN, TXDQS_PI_SETTING_MAX},
    {TxDqsOffset, TXDQS_OFFSET_MIN,     TXDQS_OFFSET_MAX}
  };
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Rank;
  UINT8 Byte;
  UINT8 ByteEnd;
  UINT8 Index;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  // Note: This parameter is channel specific, but the training values examined
  // to determine the limits are rank specific so the rank input value is
  // ignored and all ranks present are examined.

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM)) {
      for (Byte = 0; Byte < ByteEnd; Byte++) {
        for (Index = 0; Index < (sizeof (Limits) / sizeof (Limits[0])); Index++) {
          MrcGetSetDdrIoGroup (
            MrcData,
            (UINT8) Socket,
            (UINT8) Channel,
            MRC_IGNORE_ARG_8,
            (UINT8) Rank,
            (UINT8) Byte,
            MRC_IGNORE_ARG_8,
            MRC_IGNORE_ARG_8,
            DdrLevel,
            Limits[Index].Group,
            GSM_READ_CSR | GSM_READ_ONLY,
            &Value
            );
          CalcMinMax (MrcData, Limits[Index].Min, (INT16) Value, Limits[Index].Max, &PiOffsetMin, &PiOffsetMax);
        } // end for each index
      } // end for each byte
    } // end for each rank
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsTxDqsDelay %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[in]  LogicalRank - Zero based rank number in the channel.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsTxDqDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  UINT32        LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  static const struct {
    GSM_GT Group;
    INT16  Min;
    INT16  Max;
  } Limits[] = {
    {TxDqDelay,  TXDQ_PI_SETTING_MIN, TXDQ_PI_SETTING_MAX},
    {TxDqOffset, TXDQ_OFFSET_MIN,     TXDQ_OFFSET_MAX}
  };
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Rank;
  UINT8 Byte;
  UINT8 ByteEnd;
  UINT8 Index;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  // Note: This parameter is channel specific, but the training values examined
  // to determine the limits are rank specific so the rank input value is
  // ignored and all ranks present are examined.

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM)) {
      for (Byte = 0; Byte < ByteEnd; Byte++) {
        for (Index = 0; Index < (sizeof (Limits) / sizeof (Limits[0])); Index++) {
          MrcGetSetDdrIoGroup (
            MrcData,
            (UINT8) Socket,
            (UINT8) Channel,
            MRC_IGNORE_ARG_8,
            (UINT8) Rank,
            (UINT8) Byte,
            MRC_IGNORE_ARG_8,
            MRC_IGNORE_ARG_8,
            DdrLevel,
            Limits[Index].Group,
            GSM_READ_CSR | GSM_READ_ONLY,
            &Value
            );
          CalcMinMax (MrcData, Limits[Index].Min, (INT16) Value, Limits[Index].Max, &PiOffsetMin, &PiOffsetMax);
        } // end for each index
      } // end for each byte
    } // end for each rank
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsTxDqDelay %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[in]  LogicalRank - Zero based rank number in the channel.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsTxEqDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  UINT32        LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Rank;
  UINT8 Byte;
  UINT8 ByteEnd;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  // Note: This parameter is channel specific, but the training values examined
  // to determine the limits are rank specific so the rank input value is
  // ignored and all ranks present are examined.

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM)) {
      for (Byte = 0; Byte < ByteEnd; Byte++) {
        MrcGetSetDdrIoGroup (
          MrcData,
          (UINT8) Socket,
          (UINT8) Channel,
          MRC_IGNORE_ARG_8,
          (UINT8) Rank,
          (UINT8) Byte,
          MRC_IGNORE_ARG_8,
          MRC_IGNORE_ARG_8,
          DdrLevel,
          TxEq,
          GSM_READ_CSR | GSM_READ_ONLY,
          &Value
          );
        CalcMinMax (MrcData, TXEQ_OFFSET_MIN, (INT16) Value, TXEQ_OFFSET_MAX, &PiOffsetMin, &PiOffsetMax);
      } // end for each byte
    } // end for each rank
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsTxEqDelay %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[in]  LogicalRank - Zero based rank number in the channel.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsTxDqBitDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  UINT32        LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Rank;
  UINT8 Byte;
  UINT8 ByteEnd;
  UINT8 Bit;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  // Note: This parameter is channel specific, but the training values examined
  // to determine the limits are rank specific so the rank input value is
  // ignored and all ranks present are examined.

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM)) {
      for (Byte = 0; Byte < ByteEnd; Byte++) {
        for (Bit = 0; Bit < MAX_BITS; Bit++) {
          MrcGetSetDdrIoGroup (
            MrcData,
            (UINT8) Socket,
            (UINT8) Channel,
            MRC_IGNORE_ARG_8,
            (UINT8) Rank,
            (UINT8) Byte,
            (UINT8) Bit,
            MRC_IGNORE_ARG_8,
            DdrLevel,
            TxDqBitDelay,
            GSM_READ_CSR | GSM_READ_ONLY,
            &Value
            );
          CalcMinMax (MrcData, TXDQBIT_OFFSET_MIN, (INT16) Value, TXDQBIT_OFFSET_MAX, &PiOffsetMin, &PiOffsetMax);
        }
      } // end for each byte
    } // end for each rank
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsTxDqBitDelay %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsTxRonUpDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Byte;
  UINT8 ByteEnd;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  for (Byte = 0; Byte < ByteEnd; Byte++) {
    MrcGetSetDdrIoGroup (
      MrcData,
      (UINT8) Socket,
      (UINT8) Channel,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      (UINT8) Byte,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      DdrLevel,
      TxRonUp,
      GSM_READ_CSR | GSM_READ_ONLY,
      &Value
      );
    CalcMinMax (MrcData, TXRON_UP_OFFSET_MIN, (INT16) Value, TXRON_UP_OFFSET_MAX, &PiOffsetMin, &PiOffsetMax);
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsTxRonUpDelay %u %u %u %d %d %u\n", Socket, Controller, Channel, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsTxRonDnDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Byte;
  UINT8 ByteEnd;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  for (Byte = 0; Byte < ByteEnd; Byte++) {
    MrcGetSetDdrIoGroup (
      MrcData,
      (UINT8) Socket,
      (UINT8) Channel,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      (UINT8) Byte,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      DdrLevel,
      TxRonDn,
      GSM_READ_CSR | GSM_READ_ONLY,
      &Value
      );
    CalcMinMax (MrcData, TXRON_DN_OFFSET_MIN, (INT16) Value, TXRON_DN_OFFSET_MAX, &PiOffsetMin, &PiOffsetMax);
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsTxRonDnDelay %u %u %u %d %d %u\n", Socket, Controller, Channel, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsTxSlewRateDelay (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT64 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Byte;
  UINT8 ByteEnd;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  for (Byte = 0; Byte < ByteEnd; Byte++) {
    MrcGetSetDdrIoGroup (
      MrcData,
      (UINT8) Socket,
      (UINT8) Channel,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      (UINT8) Byte,
      MRC_IGNORE_ARG_8,
      MRC_IGNORE_ARG_8,
      DdrLevel,
      TxSlewRate,
      GSM_READ_CSR | GSM_READ_ONLY,
      &Value
      );
    CalcMinMax (MrcData, TX_SLEW_RATE_OFFSET_MIN, (INT16) Value, TX_SLEW_RATE_OFFSET_MAX, &PiOffsetMin, &PiOffsetMax);
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsTxSlewRateDelay %u %u %u %d %d %u\n", Socket, Controller, Channel, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[in]  LogicalRank - Zero based rank number in the channel.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsRxVref (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  UINT32        LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT64 TmpValue;
  INT16 Value;
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 Rank;
  UINT8 Byte;
  UINT8 ByteEnd;

  ByteEnd     = MrcData->Outputs.SdramCount;
  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;

  // Note: This parameter is channel specific, but the training values examined
  // to determine the limits are rank specific so the rank input value is
  // ignored and all ranks present are examined.

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM)) {
      for (Byte = 0; Byte < ByteEnd; Byte++) {
        MrcGetSetDdrIoGroup (
          MrcData,
          (UINT8) Socket,
          (UINT8) Channel,
          MRC_IGNORE_ARG_8,
          (UINT8) Rank,
          (UINT8) Byte,
          MRC_IGNORE_ARG_8,
          MRC_IGNORE_ARG_8,
          DdrLevel,
          RxVref,
          GSM_READ_CSR | GSM_READ_ONLY,
          &TmpValue
          );
        Value = (INT16) TmpValue * 2;
        CalcMinMax (MrcData, RXVREF_SETTING_MIN * 2, Value, RXVREF_SETTING_MAX * 2, &PiOffsetMin, &PiOffsetMax);
        MrcGetSetDdrIoGroup (
          MrcData,
          (UINT8) Socket,
          (UINT8) Channel,
          MRC_IGNORE_ARG_8,
          (UINT8) Rank,
          (UINT8) Byte,
          MRC_IGNORE_ARG_8,
          MRC_IGNORE_ARG_8,
          DdrLevel,
          RxVrefOffset,
          GSM_READ_CSR | GSM_READ_ONLY,
          &TmpValue
          );
        CalcMinMax (MrcData, RXVREF_OFFSET_MIN, (INT16) TmpValue, RXVREF_OFFSET_MAX, &PiOffsetMin, &PiOffsetMax);
      } // end for each byte
    } // end for each rank
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsRxVref %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[in]  LogicalRank - Zero based rank number in the channel.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsTxVref (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  UINT32        LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;
  UINT8 MaxMargin;
  UINT8 Rank;

  MaxMargin = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_DDR4) ? TXVREF_OFFSET_DDR4_MAX : TXVREF_OFFSET_MAX;

  PiOffsetMin = - (*MinOffset);
  PiOffsetMax = *MaxOffset;

  Rank = 1 << LogicalRank;
  PiOffsetMin = MrcCalcMaxVrefMargin (MrcData, (UINT8) Channel, Rank, 0, WrV, 0, MaxMargin, 0);
  PiOffsetMax = MrcCalcMaxVrefMargin (MrcData, (UINT8) Channel, Rank, 0, WrV, 1, MaxMargin, 0);
  *MinOffset  = -1 * MIN (- (*MinOffset), PiOffsetMin);
  *MaxOffset  = MIN (*MaxOffset, PiOffsetMax);

  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsTxVref %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[in]  LogicalRank - Zero based rank number in the channel.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsCkAll (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  UINT32        LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  UINT32                          Rank;
  UINT32                          MaxRank;
  BOOLEAN                         Lpddr;
  INT16                           PiOffset;
  INT16                           PiOffsetMin;
  INT16                           PiOffsetMax;

  Lpddr       = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR3);
  MaxRank     = Lpddr ? 2 : MAX_RANK_IN_CHANNEL;

  PiOffsetMin = *MinOffset;
  PiOffsetMax = *MaxOffset;


  // Note: This parameter is channel specific, but the training values examined
  // to determine the limits are rank specific so the rank input value is
  // ignored and all ranks present are examined.

  for (Rank = 0; Rank < MaxRank; Rank++) {
    if (Lpddr || (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM))) {
      PiOffset = MrcHalGetRegClkClkPiCode (MrcData, Channel, Rank);
      CalcMinMax (MrcData, CLOCK_OFFSET_MIN, PiOffset, CLOCK_OFFSET_MAX, &PiOffsetMin, &PiOffsetMax);
    } // end for each rank
  }

  *MinOffset = PiOffsetMin;
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsCkAll %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData        - Pointer to the MRC global data area.
  @param[in]  Socket         - Zero based CPU socket number.
  @param[in]  Controller     - Zero based controller number.
  @param[in]  Channel        - Zero based channel number.
  @param[in]  LogicalRank    - Zero based rank number in the channel.
  @param[in, out] MinOffset  - Minimum offset supported by the given margin group.
  @param[in, out] MaxOffset  - Maximum offset supported by the given margin group.
  @param[out] Delay          - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsCmdAll (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT32        Channel,
  UINT32        LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  static const struct {
    GSM_GT Group;
    INT16  Min;
    INT16  Max;
  } Limits[] = {
    {RecEnDelay,  RCVEN_PI_SETTING_MIN, RCVEN_PI_SETTING_MAX},
    {TxDqsDelay,  TXDQS_PI_SETTING_MIN, TXDQS_PI_SETTING_MAX},
    {TxDqsOffset, TXDQS_OFFSET_MIN,     TXDQS_OFFSET_MAX}
  };
  INT64 Value;
  UINT32 Rank;
  INT16  PiSetting;
  INT16  PiOffsetMin;
  INT16  PiOffsetMax;
  UINT8  Byte;
  UINT8  ByteEnd;
  UINT8  Index;

  if (MrcData->Outputs.DdrType != MRC_DDR_TYPE_LPDDR3) {
    *MinOffset = -64;
    *MaxOffset = 64;
    return (Success);
  }

  PiSetting = 0;

  // reverse the input values - moving the clock in the positive direction corresponds to moving the command in the negative direction
  PiOffsetMin = *MaxOffset * (-1);
  PiOffsetMax = *MinOffset * (-1);
  ByteEnd     = MrcData->Outputs.SdramCount;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM)) {
      for (Byte = 0; Byte < ByteEnd; Byte++) {
        for (Index = 0; Index < (sizeof (Limits) / sizeof (Limits[0])); Index++) {
          MrcGetSetDdrIoGroup (
            MrcData,
            (UINT8) Socket,
            (UINT8) Channel,
            MRC_IGNORE_ARG_8,
            (UINT8) Rank,
            (UINT8) Byte,
            MRC_IGNORE_ARG_8,
            MRC_IGNORE_ARG_8,
            DdrLevel,
            Limits[Index].Group,
            GSM_READ_CSR | GSM_READ_ONLY,
            &Value
            );
          CalcMinMax (MrcData, Limits[Index].Min, (INT16) Value, Limits[Index].Max, &PiOffsetMin, &PiOffsetMax);
        }
      } // end for each byte
    }
  } // end for each rank

  // reverse the output values - moving the clock in the positive direction corresponds to moving the command in the negative direction
  *MinOffset = PiOffsetMax * (-1);
  *MaxOffset = PiOffsetMin * (-1);

  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsCmdAll %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[in]  LogicalRank - Zero based rank number in the channel.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsCtlAll (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT8         Channel,
  UINT8         LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  UINT32  Offset;
  UINT32  CKEMapping;
  INT16   PiOffset[ (MAX_NUMBER_CMD_PI_CODES < MAX_RANK_IN_CHANNEL) ? MAX_RANK_IN_CHANNEL : MAX_NUMBER_CMD_PI_CODES];
  INT16   PiOffsetMin;
  INT16   PiOffsetMax;
  INT16   TmpOffsetMin;
  INT16   TmpOffsetMax;
  UINT8   Rank;
  UINT8   FieldIdx;
  BOOLEAN RankEnbl[MAX_RANK_IN_CHANNEL];
  BOOLEAN Lpddr3;

  PiOffsetMin  = *MinOffset;
  PiOffsetMax  = *MaxOffset;
  TmpOffsetMin = 0;
  TmpOffsetMax = (-1) * PiOffsetMin;
  Lpddr3       = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR3);

  // Get the maximum offset from the margin parameters that comprise the
  // positive side of the meta-parameter.
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((Lpddr3 && (Rank == 2)) || (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM))) {
      PiOffset[Rank] = MrcHalGetRegCtlCtlPiCode (MrcData, Channel, Rank);
      CalcMinMax (MrcData, CTL_CS_OFFSET_MIN, PiOffset[Rank], CTL_CS_OFFSET_MAX, &TmpOffsetMin, &PiOffsetMax);
    }
  }

  // Initialize rank enable values to FALSE
  MrcData->Inputs.Call.Func->MrcSetMem ((UINT8 *) RankEnbl, sizeof (RankEnbl), 0);

  // If the memory is LPDDR3
  if (Lpddr3) {
    // Get map of which CKE signal goes to which rank
    CKEMapping = MrcHalGetCkeMapping (MrcData, Channel);

    // For each bit in the field
    for (FieldIdx = 0; FieldIdx < DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh0_WID; FieldIdx++) {
      // Get the rank associated with this bit
      Rank = (CKEMapping >> FieldIdx) & 0x1;

      // If this rank is present
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        // CKE2+3 control the same field (#2)
        if (FieldIdx == 3) {
          RankEnbl[2] = TRUE;
        }
        else {
          RankEnbl[FieldIdx] = TRUE;
        }
      } // End if this rank is present
    } // End for each bit in the field
  } else { // The memory is DDR3/DDR4
    // For each potential rank in the channel
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      // If the rank is present
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        RankEnbl[Rank] = TRUE;
      }
    } // End for each rank
  } // End else the memory is DDR3

  // For each potential rank in the channel
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    // If this "rank" is enabled
    if (RankEnbl[Rank]) {
      PiOffset[Rank] = MrcHalGetRegCkeCtlPiCode (MrcData, Channel, Rank);
      CalcMinMax (MrcData, CTL_CS_OFFSET_MIN, PiOffset[Rank], CTL_CS_OFFSET_MAX, &TmpOffsetMin, &PiOffsetMax);
    }
  }

  // Get the minimum offset from the margin parameters that comprise the
  // negative side of the meta-parameter

  // These parameters are individually moved in the positive direction when the
  // meta-parameter is moved in the negative direction below its trained offset
  for (Offset = 0; Offset < MAX_NUMBER_CMD_PI_CODES; Offset++) {
    PiOffset[Offset] = MrcHalGetRegCkeCmdPiCode (MrcData, Channel, Offset);
    CalcMinMax (MrcData, CMDN_OFFSET_MIN, PiOffset[Offset], CMDN_OFFSET_MAX, &TmpOffsetMin, &PiOffsetMax);
  }

  for (Offset = 0; Offset < MAX_NUMBER_CMD_PI_CODES; Offset++) {
    PiOffset[Offset] = MrcHalGetRegCmdsCmdPiCode (MrcData, Channel, Offset);
    CalcMinMax (MrcData, CMDN_OFFSET_MIN, PiOffset[Offset], CMDN_OFFSET_MAX, &TmpOffsetMin, &PiOffsetMax);
  }

  for (Offset = 0; Offset < MAX_NUMBER_CMD_PI_CODES; Offset++) {
    PiOffset[Offset] = MrcHalGetRegCmdnCmdPiCode (MrcData, Channel, Offset);
    CalcMinMax (MrcData, CMDN_OFFSET_MIN, PiOffset[Offset], CMDN_OFFSET_MAX, &TmpOffsetMin, &PiOffsetMax);
  }

  GetMarginParamLimitsRecEnDelay (MrcData, Socket, Controller, Channel, LogicalRank, &TmpOffsetMin, &TmpOffsetMax, Delay);
  GetMarginParamLimitsTxDqsDelay (MrcData, Socket, Controller, Channel, LogicalRank, &TmpOffsetMin, &TmpOffsetMax, Delay);
  GetMarginParamLimitsTxDqDelay  (MrcData, Socket, Controller, Channel, LogicalRank, &TmpOffsetMin, &TmpOffsetMax, Delay);
  GetMarginParamLimitsCkAll      (MrcData, Socket, Controller, Channel, LogicalRank, &TmpOffsetMin, &TmpOffsetMax, Delay);

  *MinOffset = MAX (PiOffsetMin, ((-1) * TmpOffsetMax));
  *MaxOffset = PiOffsetMax;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsCtlAll %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function returns the minimum and maximum offsets that can be applied to the margin group.

  @param[in]  MrcData     - Pointer to the MRC global data area.
  @param[in]  Socket      - Zero based CPU socket number.
  @param[in]  Controller  - Zero based controller number.
  @param[in]  Channel     - Zero based channel number.
  @param[in]  LogicalRank - Zero based rank number in the channel.
  @param[out] MinOffset   - Minimum offset supported by the given margin group.
  @param[out] MaxOffset   - Maximum offset supported by the given margin group.
  @param[out] Delay       - Wait time in micro-seconds that is required for the new setting to take effect.

  @retval Success.
**/
static
SSA_STATUS
GetMarginParamLimitsCmdVref (
  MrcParameters *const MrcData,
  UINT32        Socket,
  UINT32        Controller,
  UINT8         Channel,
  UINT8         LogicalRank,
  INT16         *const MinOffset,
  INT16         *const MaxOffset,
  UINT16        *const Delay
  )
{
  INT16 PiOffsetMin;
  INT16 PiOffsetMax;

  PiOffsetMin = - (*MinOffset);
  PiOffsetMax = *MaxOffset;
  PiOffsetMin = MrcCalcMaxVrefMargin (MrcData, (UINT8) Channel, 0xFF, 0, CmdV, 0, CMDVREF_OFFSET_MAX, 0);
  PiOffsetMax = MrcCalcMaxVrefMargin (MrcData, (UINT8) Channel, 0xFF, 0, CmdV, 1, CMDVREF_OFFSET_MAX, 0);
  *MinOffset  = -1 * MIN (- (*MinOffset), PiOffsetMin);
  *MaxOffset  = MIN (*MaxOffset, PiOffsetMax);

  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimitsCmdVref %u %u %u %u %d %d %u\n", Socket, Controller, Channel, LogicalRank, *MinOffset, *MaxOffset, *Delay);
  return (Success);
}

/**
  Function used to adjust a RecEnDelay margin parameter. It will add an offset from the training value
  (if memory has been trained) or from the default value (if memory has not been trained yet).

  @param[in]      MrcData       - Pointer to the MRC global data area.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      LogicalRank   - Zero based rank number in the channel.
  @param[in]      CurrentOffset - Current offset.
  @param[in]      NewOffset     - New offset.

  @retval Success, UnsupportedValue, SocketNotSupported, ControllerNotSupported, ChannelNotSupported, DimmNotSupported, RankNotSupported.
**/
static
SSA_STATUS
SetMarginParamOffsetRecEnDelay (
  MrcParameters         *const MrcData,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 LogicalRank,
  INT16                 CurrentOffset,
  INT16                 NewOffset
  )
{
  SSA_STATUS    SsaStatus;
  UINT8         Byte;

  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetMarginParamOffsetRecEnDelay, %u %u %u %u %d %d\n", Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);

  SsaStatus = Success;
  for (Byte = 0; Byte < MrcData->Outputs.SdramCount; Byte++) {
    if (mrcSuccess != ChangeMargin (MrcData, RcvEna, NewOffset, 0, SINGLE_CAST, Channel, LogicalRank, Byte, 0, UPDATE_MRCDATA, 0, MrcRegFileRank)) {
      SsaStatus = UnsupportedValue;
      break;
    }
  } // end for each byte

  return (SsaStatus);
} // end function SetMarginParamOffsetRecEnDelay

/**
  Function used to adjust the TxDqsDelay margin parameter.It will add an offset from the training value
  (if memory has been trained) or from the default value (if memory has not been trained yet).

  @param[in]      MrcData       - Pointer to the MRC global data area.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      LogicalRank   - Zero based rank number in the channel.
  @param[in]      CurrentOffset - Current offset.
  @param[in]      NewOffset     - New offset.

  @retval Success, UnsupportedValue, SocketNotSupported, ControllerNotSupported, ChannelNotSupported, DimmNotSupported, RankNotSupported.
**/
static
SSA_STATUS
SetMarginParamOffsetTxDqsDelay (
  MrcParameters         *const MrcData,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 LogicalRank,
  INT16                 CurrentOffset,
  INT16                 NewOffset
  )
{
  SSA_STATUS    SsaStatus;
  UINT8         Byte;

  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetMarginParamOffsetTxDqsDelay, %u %u %u %u %d %d\n", Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);

  SsaStatus = Success;
  for (Byte = 0; Byte < MrcData->Outputs.SdramCount; Byte++) {
    if (mrcSuccess != ChangeMargin (MrcData, WrDqsT, NewOffset, 0, SINGLE_CAST, Channel, LogicalRank, Byte, 0, UPDATE_MRCDATA, 0, MrcRegFileRank)) {
      SsaStatus = UnsupportedValue;
      break;
    }
  } // end for each byte

  return (SsaStatus);
} // end function SetMarginParamOffsetTxDqsDelay

/**
  Function used to adjust the TxDqDelay margin parameter.  It will add an offset from the training value
  (if memory has been trained) or from the default value (if memory has not been trained yet).

  @param[in]      MrcData       - Pointer to the MRC global data area.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      LogicalRank   - Zero based rank number in the channel.
  @param[in]      CurrentOffset - Current offset.
  @param[in]      NewOffset     - New offset.

  @retval Success, UnsupportedValue, SocketNotSupported, ControllerNotSupported, ChannelNotSupported, DimmNotSupported, RankNotSupported.
**/
static
SSA_STATUS
SetMarginParamOffsetTxDqDelay (
  MrcParameters         *const MrcData,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 LogicalRank,
  INT16                 CurrentOffset,
  INT16                 NewOffset
  )
{
  SSA_STATUS    SsaStatus;
  UINT8         Byte;

  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetMarginParamOffsetTxDqDelay, %u %u %u %u %d %d\n", Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);

  SsaStatus = Success;
  for (Byte = 0; Byte < MrcData->Outputs.SdramCount; Byte++) {
    if (mrcSuccess != ChangeMargin (MrcData, WrT, NewOffset, 0, SINGLE_CAST, Channel, LogicalRank, Byte, 0, UPDATE_MRCDATA, 0, MrcRegFileRank)) {
      SsaStatus = UnsupportedValue;
      break;
    }
  } // end for each byte

  return (SsaStatus);
} // end function SetMarginParamOffsetTxDqDelay

/**
  Function used to adjust the CkAll margin parameter.  It will add an offset from the training value
  (if memory has been trained) or from the default value (if memory has not been trained yet).

  @param[in]      MrcData       - Pointer to the MRC global data area.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      LogicalRank   - Zero based rank number in the channel.
  @param[in]      CurrentOffset - Current offset.
  @param[in]      NewOffset     - New offset.

  @retval Success, UnsupportedValue, SocketNotSupported, ControllerNotSupported, ChannelNotSupported, DimmNotSupported, RankNotSupported.
**/
static
SSA_STATUS
SetMarginParamOffsetCkAll (
  MrcParameters         *const MrcData,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 LogicalRank,
  INT16                 CurrentOffset,
  INT16                 NewOffset
  )
{
  SSA_STATUS                      SsaStatus;
  UINT32                          Rank;
  UINT32                          MaxRank;
  BOOLEAN                         Lpddr;
  INT16                           Value;
  INT16                           Displacement;

  Lpddr       = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR3);
  MaxRank     = Lpddr ? 2 : MAX_RANK_IN_CHANNEL;

  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetMarginParamOffsetCkAll, %u %u %u %u %d %d\n", Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);

  SsaStatus     = Success;
  Displacement  = NewOffset - CurrentOffset;
  for (Rank = 0; Rank < MaxRank; Rank++) {
    if (Lpddr || (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Rank / MAX_RANK_IN_DIMM, Rank % MAX_RANK_IN_DIMM))) {
      // get the current value
      Value = MrcHalGetRegClkClkPiCode (MrcData, Channel, Rank);

      // add the displacement
      Value += Displacement;

      // range limit the value
      Value = MIN (Value, CLOCK_OFFSET_MAX);
      Value = MAX (Value, CLOCK_OFFSET_MIN);

      // save the value to the field
      MrcHalRmwRegClkClkPiCode (MrcData, Channel, Rank, Value);
    } // end for each rank
  }

  return (SsaStatus);
} // end function SetMarginParamOffsetCkAll

/**
  Function used to adjust the CmdN margin parameter.  It will add an offset from the training value
  (if memory has been trained) or from the default value (if memory has not been trained yet).

  @param[in]      MrcData       - Pointer to the MRC global data area.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      LogicalRank   - Zero based rank number in the channel.
  @param[in]      CurrentOffset - Current offset.
  @param[in]      NewOffset     - New offset.

  @retval Success, UnsupportedValue, SocketNotSupported, ControllerNotSupported, ChannelNotSupported, DimmNotSupported, RankNotSupported.
**/
static
SSA_STATUS
SetMarginParamOffsetCmdN (
  MrcParameters         *const MrcData,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 LogicalRank,
  INT16                 CurrentOffset,
  INT16                 NewOffset
  )
{
  SSA_STATUS SsaStatus;
  UINT32     PiIndex;
  INT16      Value;

  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetMarginParamOffsetCmdN, %u %u %u %u %d %d\n", Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);

  SsaStatus     = Success;
  for (PiIndex = 0; PiIndex < MAX_NUMBER_CMD_PI_CODES; PiIndex++) {
    Value = MrcHalGetRegCmdnCmdPiCode (MrcData, Channel, PiIndex);
    Value += NewOffset - CurrentOffset;
    Value = MIN (Value, CMDN_OFFSET_MAX);
    Value = MAX (Value, CMDN_OFFSET_MIN);
    MrcHalRmwRegCmdnCmdPiCode (MrcData, Channel, PiIndex, Value);
  }

  return (SsaStatus);
} // end function SetMarginParamOffsetCmdN

/**
  Function used to adjust the CmdS margin parameter.  It will add an offset from the training value
  (if memory has been trained) or from the default value (if memory has not been trained yet).

  @param[in]      MrcData       - Pointer to the MRC global data area.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      LogicalRank   - Zero based rank number in the channel.
  @param[in]      CurrentOffset - Current offset.
  @param[in]      NewOffset     - New offset.

  @retval Success, UnsupportedValue, SocketNotSupported, ControllerNotSupported, ChannelNotSupported, DimmNotSupported, RankNotSupported.
**/
static
SSA_STATUS
SetMarginParamOffsetCmdS (
  MrcParameters         *const MrcData,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 LogicalRank,
  INT16                 CurrentOffset,
  INT16                 NewOffset
  )
{
  SSA_STATUS SsaStatus;
  UINT32     PiIndex;
  INT16      Value;

  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetMarginParamOffsetCmdS, %u %u %u %u %d %d\n", Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);

  SsaStatus     = Success;
  for (PiIndex = 0; PiIndex < MAX_NUMBER_CMD_PI_CODES; PiIndex++) {
    Value = MrcHalGetRegCmdsCmdPiCode (MrcData, Channel, PiIndex);
    Value += NewOffset - CurrentOffset;
    Value = MIN (Value, CMDS_OFFSET_MAX);
    Value = MAX (Value, CMDS_OFFSET_MIN);
    MrcHalRmwRegCmdsCmdPiCode (MrcData, Channel, PiIndex, Value);
  }

  return (SsaStatus);
} // end function SetMarginParamOffsetCmdS

/**
  Function used to adjust the CmdCke margin parameter.  It will add an offset from the training value
  (if memory has been trained) or from the default value (if memory has not been trained yet).

  @param[in]      MrcData       - Pointer to the MRC global data area.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      LogicalRank   - Zero based rank number in the channel.
  @param[in]      CurrentOffset - Current offset.
  @param[in]      NewOffset     - New offset.

  @retval Success, UnsupportedValue, SocketNotSupported, ControllerNotSupported, ChannelNotSupported, DimmNotSupported, RankNotSupported.
**/
static
SSA_STATUS
SetMarginParamOffsetCmdCke (
  MrcParameters         *const MrcData,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 LogicalRank,
  INT16                 CurrentOffset,
  INT16                 NewOffset
  )
{
  SSA_STATUS SsaStatus;
  UINT32     PiIndex;
  INT16      Value;

  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetMarginParamOffsetCmdCke, %u %u %u %u %d %d\n", Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);

  SsaStatus     = Success;
  for (PiIndex = 0; PiIndex < MAX_NUMBER_CMD_PI_CODES; PiIndex++) {
    Value = MrcHalGetRegCkeCmdPiCode (MrcData, Channel, PiIndex);
    Value += NewOffset - CurrentOffset;
    Value = MIN (Value, CMD_CKE_OFFSET_MAX);
    Value = MAX (Value, CMD_CKE_OFFSET_MIN);
    MrcHalRmwRegCkeCmdPiCode (MrcData, Channel, PiIndex, Value);
  }

  return (SsaStatus);
} // end function SetMarginParamOffsetCmdCke

/**
  Function used to adjust the CtlCke margin parameter.  It will add an offset from the training value
  (if memory has been trained) or from the default value (if memory has not been trained yet).

  @param[in]      MrcData       - Pointer to the MRC global data area.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      LogicalRank   - Zero based rank number in the channel.
  @param[in]      CurrentOffset - Current offset.
  @param[in]      NewOffset     - New offset.

  @retval Success, UnsupportedValue, SocketNotSupported, ControllerNotSupported, ChannelNotSupported, DimmNotSupported, RankNotSupported.
**/
static
SSA_STATUS
SetMarginParamOffsetCtlCke (
  MrcParameters         *const MrcData,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 LogicalRank,
  INT16                 CurrentOffset,
  INT16                 NewOffset
  )
{
  SSA_STATUS                            SsaStatus;
  UINT32                                CKEMapping;
  INT16                                 Value;
  UINT8                                 Rank;
  UINT8                                 FieldIdx;
  BOOLEAN                               RankEnbl[MAX_RANK_IN_CHANNEL];

  SsaStatus = Success;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetMarginParamOffsetCtlCke, %u %u %u %u %d %d\n", Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);

  // Initialize rank enable values to FALSE
  MrcData->Inputs.Call.Func->MrcSetMem ((UINT8 *) RankEnbl, sizeof (RankEnbl), 0);

  // If the memory is LPDDR3
  if (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR3) {
    // get map of which CKE signal goes to which rank
    CKEMapping = MrcHalGetCkeMapping (MrcData, Channel);

    // For each bit in the field
    for (FieldIdx = 0; FieldIdx < DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh0_WID; FieldIdx++) {
      // get the rank associated with this bit
      Rank = (CKEMapping >> FieldIdx) & 0x1;

      // IF this rank is present
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        // CKE2+3 control the same field (#2)
        if (FieldIdx == 3) {
          RankEnbl[2] = TRUE;
        }
        else {
          RankEnbl[FieldIdx] = TRUE;
        }
      } // end if this rank is present
    } // end for each bit in the field
  } else { // The memory is DDR3
    // FOR each potential rank in the channel
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      // IF the rank is present
      if (MrcRankInChannelExist (MrcData, 0, Channel)) {
        RankEnbl[Rank] = TRUE;
      }
    } // end for each rank
  } // end else the memory is DDR3

  // FOR each potential rank in the channel
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    // IF this "rank" is enabled
    if (RankEnbl[Rank]) {
      // get the current setting
      Value = MrcHalGetRegCkeCtlPiCode (MrcData, Channel, Rank);

      // add the displacement
      Value += NewOffset - CurrentOffset;

      // range limit the value
      Value = MIN (Value, CTL_CKE_OFFSET_MAX);
      Value = MAX (Value, CTL_CKE_OFFSET_MIN);

      // save the value to the field
      MrcHalRmwRegCkeCtlPiCode (MrcData, Channel, Rank, Value);
    } // end if this "rank" is enabled for ODT
  } // end for each rank

  return (SsaStatus);
} // end function SetMarginParamOffsetCtlCke

/**
  Function used to adjust the CtlOdtCs margin parameter.  It will add an offset from the training value
  (if memory has been trained) or from the default value (if memory has not been trained yet).

  @param[in]      MrcData       - Pointer to the MRC global data area.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      LogicalRank   - Zero based rank number in the channel.
  @param[in]      CurrentOffset - Current offset.
  @param[in]      NewOffset     - New offset.

  @retval Success, UnsupportedValue, SocketNotSupported, ControllerNotSupported, ChannelNotSupported, DimmNotSupported, RankNotSupported.
**/
static
SSA_STATUS
SetMarginParamOffsetCtlOdtCs (
  MrcParameters         *const MrcData,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 LogicalRank,
  INT16                 CurrentOffset,
  INT16                 NewOffset
  )
{
  SSA_STATUS                           SsaStatus;
  INT16                                Value;
  UINT8                                Rank;
  BOOLEAN                              RankEnbl[MAX_RANK_IN_CHANNEL];

  SsaStatus = Success;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetMarginParamOffsetCtlOdtCs, %u %u %u %u %d %d\n", Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);

  // initialize rank enable values to FALSE
  MrcData->Inputs.Call.Func->MrcSetMem ((UINT8 *) RankEnbl, sizeof (RankEnbl), 0);

  // IF the memory is LPDDR3
  if (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR3) {
    // FOR each potential rank in the channel
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      // IF the rank is present
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        RankEnbl[Rank] = TRUE;
      }
    } // end for each rank

    // in LPDDR3 there is ODT0 only that is controlled by CtlPiCode2 field
    RankEnbl[2] = TRUE;
  }
  // ELSE the memory is DDR3
  else {
    // FOR each potential rank in the channel
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      // IF the rank is present
      if (MrcRankInChannelExist (MrcData, 0, Channel)) {
        RankEnbl[Rank] = TRUE;
      }
    } // end for each rank
  } // end else the memory is DDR3

  // FOR each potential rank in the channel
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    // IF this "rank" is enabled
    if (RankEnbl[Rank]) {
      // get the current setting
      Value = MrcHalGetRegCtlCtlPiCode (MrcData, Channel, Rank);

      // add the displacement
      Value += NewOffset - CurrentOffset;

      // range limit the value
      Value = MIN (Value, CTL_CS_OFFSET_MAX);
      Value = MAX (Value, CTL_CS_OFFSET_MIN);

      // save the value to the field
      MrcHalRmwRegCtlCtlPiCode (MrcData, Channel, Rank, Value);
    } // end if this "rank" is enabled for ODT
  } // end for each rank

  return (SsaStatus);
} // end function SetMarginParamOffsetCtlOdtCs

/**
  Function used to get the current and new offset values associated with the
  positive and negative sides of the given current and new offset values.  This
  function is used for compound margin parameters that use different sets of
  margin parameters for the positive and negative sides.

  @param[in]      CurrentOffset         - Current offset.
  @param[in]      NewOffset             - New Offset.
  @param[out]     pPosSideCurrentOffset - Pointer to current offset associated with the positive side.
  @param[out]     pPosSideNewOffset     - Pointer to new offset associated with the positive side.
  @param[out]     pNegSideCurrentOffset - Pointer to current offset associated with the negative side.
  @param[out]     pNegSideNewOffset     - Pointer to new offset associated with the negative side.
**/
static
VOID
GetPosAndNegSideOffsets (
  INT16 CurrentOffset,
  INT16 NewOffset,
  INT16 *pPosSideCurrentOffset,
  INT16 *pPosSideNewOffset,
  INT16 *pNegSideCurrentOffset,
  INT16 *pNegSideNewOffset
  )
{
  // calculate the displacements from the current setting for the margin
  // parameters that comprise both the positive and negative side of the
  // meta-parameter
  if (CurrentOffset > 0) {
    *pPosSideCurrentOffset = CurrentOffset;
    *pNegSideCurrentOffset = 0;

    if (NewOffset > 0) {
      *pPosSideNewOffset = NewOffset;
      *pNegSideNewOffset = 0;
    }
    else {
      *pPosSideNewOffset = 0;
      *pNegSideNewOffset = NewOffset;
    }
  }
  else {
    *pPosSideCurrentOffset = 0;
    *pNegSideCurrentOffset = CurrentOffset;

    if (NewOffset < 0) {
      *pPosSideNewOffset = 0;
      *pNegSideNewOffset = NewOffset;
    }
    else {
      *pPosSideNewOffset = NewOffset;
      *pNegSideNewOffset = 0;
    }
  }
} // end function GetPosAndNegSideOffsets

typedef struct {
  SSA_STATUS (*mrc_task) (
    MrcParameters         *const MrcData,
    UINT8                 Socket,
    UINT8                 Controller,
    UINT8                 Channel,
    UINT8                 LogicalRank,
    INT16                 CurrentOffset,
    INT16                 NewOffset);
} SsaMarginCallTableType;
const SsaMarginCallTableType MarginCallTable1[] = {
  {SetMarginParamOffsetCtlOdtCs},
  {SetMarginParamOffsetCtlCke}
};
const SsaMarginCallTableType MarginCallTable2[] = {
  {SetMarginParamOffsetCmdN},
  {SetMarginParamOffsetCmdS},
  {SetMarginParamOffsetCmdCke},
  {SetMarginParamOffsetRecEnDelay},
  {SetMarginParamOffsetTxDqsDelay},
  {SetMarginParamOffsetTxDqDelay},
  {SetMarginParamOffsetCkAll}
};

/**
  Function used to adjust the CmdAll margin parameter.  It will add an offset from the training value
  (if memory has been trained) or from the default value (if memory has not been trained yet).

  @param[in]      MrcData       - Pointer to the MRC global data area.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      LogicalRank   - Zero based rank number in the channel.
  @param[in]      CurrentOffset - Current offset.
  @param[in]      NewOffset     - New offset.

  @retval Success, UnsupportedValue, SocketNotSupported, ControllerNotSupported, ChannelNotSupported, DimmNotSupported, RankNotSupported.
**/
static
SSA_STATUS
SetMarginParamOffsetCmdAll (
  MrcParameters         *const MrcData,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 LogicalRank,
  INT16                 CurrentOffset,
  INT16                 NewOffset
  )
{

  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetMarginParamOffsetCmdAll, %u %u %u %u %d %d\n", Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);

  // reverse the value - moving the clock in the positive direction corresponds to moving the command in the negative direction
  NewOffset *= (-1);

  ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, 0x1 << LogicalRank, 3, NewOffset, FALSE);
  return (Success);
} // end function SetMarginParamOffsetCmdAll

/**
  Function used to adjust the CtlAll margin parameter.  It will add an offset from the training value
  (if memory has been trained) or from the default value (if memory has not been trained yet).

  @param[in]      MrcData       - Pointer to the MRC global data area.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      LogicalRank   - Zero based rank number in the channel.
  @param[in]      CurrentOffset - Current offset.
  @param[in]      NewOffset     - New offset.

  @retval Success, UnsupportedValue, SocketNotSupported, ControllerNotSupported, ChannelNotSupported, DimmNotSupported, RankNotSupported.
**/
static
SSA_STATUS
SetMarginParamOffsetCtlAll (
  MrcParameters         *const MrcData,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 LogicalRank,
  INT16                 CurrentOffset,
  INT16                 NewOffset
  )
{
  SSA_STATUS    SsaStatus;
  INT16         PosSideCurrentOffset;
  INT16         PosSideNewOffset;
  INT16         NegSideCurrentOffset;
  INT16         NegSideNewOffset;
  INT16         TmpCurrentOffset;
  INT16         TmpNewOffset;
  UINT8         Index;

  SsaStatus = Success;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetMarginParamOffsetCtlAll, %u %u %u %u %d %d\n", Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);

  // calculate the displacements from the current setting for the margin
  // parameters that comprise both the positive and negative side of the
  // meta-parameter
  GetPosAndNegSideOffsets (CurrentOffset, NewOffset, &PosSideCurrentOffset, &PosSideNewOffset, &NegSideCurrentOffset, &NegSideNewOffset);

  // IF there is a net change in the offsets of the margin parameters that
  // comprise the positive side of the meta-parameter
  if ((PosSideNewOffset - PosSideCurrentOffset) != 0) {
    for (Index = 0; ((SsaStatus == Success) && (Index < 2)); Index++) {
      SsaStatus = MarginCallTable1[Index].mrc_task (MrcData, Socket, Controller, Channel, LogicalRank, PosSideCurrentOffset, PosSideNewOffset);
    }
  } // end if there is a net change...

  // IF there is a net change in the offsets of the margin parameters that
  // comprise the negative side of the meta-parameter
  if ((NegSideNewOffset - NegSideCurrentOffset) != 0) {
    // when the meta-parameter is moved in the negative direction, the margin
    // parameters that comprise the negative side of the meta-parameter are
    // actually moved in the positive direction
    TmpCurrentOffset = -1 * NegSideCurrentOffset;
    TmpNewOffset     = -1 * NegSideNewOffset;

    for (Index = 0; (SsaStatus == Success) && (Index < (sizeof (MarginCallTable2) / sizeof (MarginCallTable2[0]))); Index++) {
      SsaStatus = MarginCallTable2[Index].mrc_task (MrcData, Socket, Controller, Channel, LogicalRank, TmpCurrentOffset, TmpNewOffset);
    }
  } // end if there is a net change...

  return (SsaStatus);
} // end function SetMarginParamOffsetCtlAll

/**
  Function used to get information about the system.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[out]     SystemInfo - Pointer to buffer to be filled with system information.

  @retval Nothing.
**/
VOID
(EFIAPI BiosGetSystemInfo) (
  SSA_BIOS_SERVICES_PPI *This,
  MRC_SYSTEM_INFO       *SystemInfo
  )
{
  MrcParameters *MrcData;

#ifdef SSA_PARAM_ERROR_CHECK
  if (SystemInfo != NULL)
#endif
  {
    MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
    MrcData->Inputs.Call.Func->MrcCopyMem ((UINT8 *) SystemInfo, (UINT8 *) &SysInfoConst, sizeof (MRC_SYSTEM_INFO));
    SystemInfo->IsEccEnabled = MrcData->Outputs.EccSupport;
    SystemInfo->BusFreq      = MrcData->Outputs.Frequency;
    SystemInfo->BootMode     = MrcData->Inputs.BootMode;
    SSA_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "GetSystemInfo, %u %u %u %u %u %u %u %u %u %u\n",
      SysInfoConst.MaxNumberSockets,
      SysInfoConst.MaxNumberControllers,
      SysInfoConst.MaxNumberChannels,
      SysInfoConst.MaxNumberDimms,
      SysInfoConst.MaxNumberRanks,
      SysInfoConst.SocketBitMask,
      SysInfoConst.BusWidth,
      SysInfoConst.BusFreq,
      SysInfoConst.IsEccEnabled,
      SysInfoConst.BootMode
      );
  }
  return;
}

/**
  Function used to get the platform memory voltage (VDD).

  @param[in, out] This    - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[out]     Voltage - Pointer to were the platform memory voltage (in mV) will be written.

  @retval Nothing.
**/
VOID
(EFIAPI BiosGetMemVoltage) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT32                *Voltage
  )
{
  MrcParameters *MrcData;

#ifdef SSA_PARAM_ERROR_CHECK
  if (Voltage != NULL)
#endif
  {
    MrcData  = (MrcParameters *) This->SsaMemoryConfig->MrcData;
    *Voltage = MrcData->Outputs.VddVoltage[MrcData->Inputs.MemoryProfile];
    SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMemVoltage, %u\n", *Voltage);
  }
  return;
}

/**
  Function used to set the platform memory voltage.

  @param[in, out] This    - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Voltage - The memory voltage (in mV) to be set on the platform.

  @retval Nothing.
**/
VOID
(EFIAPI BiosSetMemVoltage) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT32                Voltage
  )
{
  MrcParameters *MrcData;
  UINT32        VddSettleWaitTime;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  VddSettleWaitTime = MIN (MrcData->Inputs.VddSettleWaitTime, 200);
  MrcVDDVoltageCheckAndSwitch (MrcData, Voltage, (UINT32 * const) &VddSettleWaitTime);
  MrcWait (MrcData, VddSettleWaitTime * HPET_1US);
  MrcData->Outputs.VddVoltage[MrcData->Inputs.MemoryProfile] = Voltage;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetMemVoltage, %u\n", Voltage);
  return;
}

/**
  Function used to get the DIMM temperature.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket      - Zero based CPU socket number.
  @param[in]      Controller  - Zero based controller number.
  @param[in]      Channel     - Zero based channel number.
  @param[in]      Dimm        - Zero based DIMM number.
  @param[out]     Temperature - Pointer to where the DIMM temperature will be written.  Units: Celsius with 1 degree precision.

  @retval NotAvailable if the DIMM does not support a temperature sensor.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetMemTemp) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Dimm,
  INT32                 *Temperature
  )
{
  MrcParameters       *MrcData;
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  SSA_STATUS          SsaStatus;
  UINT32              SmbStatus;
  UINT16              Value;
  UINT8               Address;
  union {
    struct {
      UINT16 Fraction : 4;
      INT16  Whole    : 8;
      UINT16 Sign     : 1;
      UINT16 Low      : 1;
      UINT16 High     : 1;
      UINT16 Tcrit    : 1;
    } Bit;
    UINT16            Data;
    UINT8             Data8[2];
  } TsRegisterSet;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  Address = 0;
  TsRegisterSet.Data = 0;
#ifdef SSA_PARAM_ERROR_CHECK
  if (Temperature == NULL) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsDimmPresent (MrcData, Socket, Controller, Channel, Dimm)) ? Success : NotAvailable;
  if (Success == SsaStatus) {
#else
  {
    SsaStatus = Success;
#endif
    Inputs  = &MrcData->Inputs;
    MrcCall = Inputs->Call.Func;
    Address = SPD_SENSOR_BASE_ADDRESS | (Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0xF);
    Value   = MrcCall->MrcSmbusRead16 (((UINT32) SPD_SENSOR_TEMPERATURE_OFFSET << 8) | Address, (UINT32 *) &SmbStatus);
    if (RETURN_SUCCESS == SmbStatus) {
      // Value read is in big endian format, convert it to little endian.
      TsRegisterSet.Data8[0] = (UINT8) Value;
      TsRegisterSet.Data8[1] = (UINT8) (Value >> 8);
      *Temperature           = TsRegisterSet.Bit.Whole * ((TsRegisterSet.Bit.Sign) ? (-1) : 1);
    } else {
      *Temperature = 0;
      SsaStatus    = NotAvailable;
    }
  }
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMemTemp %u/%u/%u/%u %04Xh %04Xh %d\n", Socket, Controller, Channel, Dimm, Address, TsRegisterSet.Data, *Temperature);
  return (SsaStatus);
}

/**
  Function used to get the bitmask of populated memory controllers on a given CPU socket.

  @param[in, out] This    - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket  - Zero based CPU socket number.
  @param[out]     BitMask     - Pointer to where the memory controller bitmask will be stored.  Bit value 1 = populated; bit value 0 = absent. Bit position 0 = memory controller 0; bit position 1 = memory controller 1, etc.

  @retval Nothing.
**/
VOID
(EFIAPI BiosGetControllerBitMask) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 *BitMask
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((BitMask != NULL) && (mrcSuccess == IsSocketPresent (MrcData, Socket)))
#endif
  {
    *BitMask = (((UINT8) (~0)) >> (8 - MAX_CONTROLLERS));
    SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetControllerBitMask %u %Xh\n", Socket, *BitMask);
  }
  return;
}

/**
  Function used to get the bitmask of populated memory channels on a given memory controller.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket      - Zero based CPU socket number.
  @param[in]      Controller  - Zero based controller number.
  @param[out]     BitMask     - Pointer to where the memory channel bit mask will be stored.  Bit value 1 = populated; bit value 0 = absent. Bit position 0 = memory channel 0; bit position 1 = memory channel 1, etc.

  @retval Nothing.
**/
VOID
(EFIAPI BiosGetChannelBitMask) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 *BitMask
  )
{
  MrcParameters *MrcData;
  UINT8         Channel;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((BitMask != NULL) && (mrcSuccess == IsControllerPresent (MrcData, Socket, Controller)))
#endif
  {
    *BitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) {
        *BitMask |= (MRC_BIT0 << Channel);
        SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetChannelBitMask %u/%u %Xh\n", Socket, Controller, *BitMask);
      }
    }
  }
  return;
}

/**
  Function used to get the bitmask of populated DIMMs on a given memory channel.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[out]     BitMask    - Pointer to where the DIMM bit mask will be stored.  Bit value 1 = populated; bit value 0 = absent. Bit position 0 = DIMM 0; bit position 1 = DIMM 1, etc.

  @retval Nothing.
**/
VOID
(EFIAPI BiosGetDimmBitMask) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 *BitMask
  )
{
  MrcParameters *MrcData;
  MrcDimmOut    *DimmOut;
  UINT8         Dimm;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((BitMask != NULL) && (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)))
#endif
  {
    DimmOut  = &MrcData->Outputs.Controller[Controller].Channel[Channel].Dimm[0];
    *BitMask = 0;
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++, DimmOut++) {
      if (DimmOut->Status == DIMM_PRESENT) {
        *BitMask |= (MRC_BIT0 << Dimm);
        SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetDimmBitMask %u/%u/%u %Xh\n", Socket, Controller, Channel, *BitMask);
      }
    }
  }
  return;
}

/**
  Function used to get the number of ranks in a given DIMM.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket      - Zero based CPU socket number.
  @param[in]      Controller  - Zero based controller number.
  @param[in]      Channel     - Zero based channel number.
  @param[in]      Dimm        - Zero based DIMM number.
  @param[out]     *RankCount  - Pointer to where the rank count will be stored.

  @retval Nothing.
**/
VOID
(EFIAPI BiosGetRankInDimm) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Dimm,
  UINT8                 *RankCount
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((RankCount != NULL) && (mrcSuccess == IsDimmPresent (MrcData, Socket, Controller, Channel, Dimm)))
#endif
  {
    *RankCount = MrcData->Outputs.Controller[Controller].Channel[Channel].Dimm[Dimm].RankInDimm;
    SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetRankInDimm %u/%u/%u/%u %Xh\n", Socket, Controller, Channel, Dimm, *RankCount);
  }
  return;
}

/**
  Function used to get the MC logical rank associated with a given DIMM and rank.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket      - Zero based CPU socket number.
  @param[in]      Controller  - Zero based controller number.
  @param[in]      Channel     - Zero based channel number.
  @param[in]      Dimm        - Zero based DIMM number.
  @param[in]      Rank        - Zero based rank number.
  @param[out]     LogicalRank - Pointer to where the logical rank will be stored.

  @retval None.
**/
VOID
(EFIAPI BiosGetLogicalRank) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Dimm,
  UINT8                 Rank,
  UINT8                 *LogicalRank
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((LogicalRank != NULL) && (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Dimm, Rank)))
#endif
  {
    *LogicalRank = (Dimm * MAX_RANK_IN_DIMM) + Rank;
    SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetLogicalRank %u/%u/%u/%u/%u %Xh\n", Socket, Controller, Channel, Dimm, Rank, *LogicalRank);
  }
  return;
}

/**
  Function used to get DIMM information.

  @param[in, out] This           - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket         - Zero based CPU socket number.
  @param[in]      Controller     - Zero based controller number.
  @param[in]      Channel        - Zero based channel number.
  @param[in]      Dimm           - Zero based DIMM number.
  @param[out]     DimmInfoBuffer - Pointer to buffer to be filled with DIMM information.

  @retval Nothing.
**/
VOID
(EFIAPI BiosGetDimmInfo) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Dimm,
  MRC_DIMM_INFO         *DimmInfoBuffer
  )
{
  MrcDimmOut    *DimmOut;
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((DimmInfoBuffer != NULL) && (mrcSuccess == IsDimmPresent (MrcData, Socket, Controller, Channel, Dimm)))
#endif
  {
    DimmOut                       = &MrcData->Outputs.Controller[Controller].Channel[Channel].Dimm[Dimm];
    DimmInfoBuffer->EccSupport    = DimmOut->EccSupport;
    DimmInfoBuffer->DimmCapacity  = DimmOut->DimmCapacity;
    DimmInfoBuffer->BankCount     = DimmOut->BankGroups * DimmOut->Banks;
    DimmInfoBuffer->RowSize       = DimmOut->RowSize;
    DimmInfoBuffer->ColumnSize    = DimmOut->ColumnSize;
    DimmInfoBuffer->DeviceWidth   = DimmOut->SdramWidth;
    DimmInfoBuffer->MemoryTech    = (MEMORY_TECHNOLOGY) MrcData->Inputs.Controller[Controller].Channel[Channel].Dimm[Dimm].Spd.Data.Ddr3.General.DramDeviceType.Data;
    DimmInfoBuffer->MemoryPackage = DimmOut->ModuleType;
    SSA_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "GetDimmInfo, %u/%u/%u/%u %u %u %u %u %u %u %u %u\n",
      Socket,
      Controller,
      Channel,
      Dimm,
      DimmInfoBuffer->EccSupport,
      DimmInfoBuffer->DimmCapacity,
      DimmInfoBuffer->BankCount,
      DimmInfoBuffer->RowSize,
      DimmInfoBuffer->ColumnSize,
      DimmInfoBuffer->DeviceWidth,
      DimmInfoBuffer->MemoryTech,
      DimmInfoBuffer->MemoryPackage
      );
  }
  return;
}

/**
  Function used to get DIMM unique module ID.

  @param[in, out] This           - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket         - Zero based CPU socket number.
  @param[in]      Controller     - Zero based controller number.
  @param[in]      Channel        - Zero based channel number.
  @param[in]      Dimm           - Zero based DIMM number.
  @param[out]     UniqueModuleId - Pointer to buffer to be filled with DIMM unique module ID.

  @retval Nothing.
**/
VOID
(EFIAPI BiosGetDimmUniqueModuleId) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Dimm,
  SPD_UNIQUE_MODULE_ID  *UniqueModuleId
  )
{
  MrcParameters *MrcData;
  MrcSpd        *Spd;
  UINT8         *DramModuleId;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((UniqueModuleId != NULL) && (mrcSuccess == IsDimmPresent (MrcData, Socket, Controller, Channel, Dimm)))
#endif
  {
    Spd = &MrcData->Inputs.Controller[Controller].Channel[Channel].Dimm[Dimm].Spd.Data;
    if ((Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_DDR3_SDRAM_TYPE_NUMBER) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
      DramModuleId = (UINT8 *) &Spd->Ddr3.ModuleId;
    } else {
      DramModuleId = (UINT8 *) &Spd->Ddr4.ManufactureInfo.ModuleId;
    }
    DramModuleId =
    MrcData->Inputs.Call.Func->MrcCopyMem (
                                 (UINT8 *) UniqueModuleId,
                                 DramModuleId,
                                 sizeof (SPD_UNIQUE_MODULE_ID)
                                 );
    SSA_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "GetDimmUniqueModuleId, %u/%u/%u/%u %u %u %u/%u %u\n",
      Socket,
      Controller,
      Channel,
      Dimm,
      UniqueModuleId->IdCode.Data,
      UniqueModuleId->Location.Location,
      UniqueModuleId->Date.Week,
      UniqueModuleId->Date.Year,
      UniqueModuleId->SerialNumber.Data
      );
  }
  return;
}

/**
  Function used to get DIMM SPD data.

  @param[in, out] This         - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket       - Zero based CPU socket number.
  @param[in]      Controller   - Zero based controller number.
  @param[in]      Channel      - Zero based channel number.
  @param[in]      Dimm         - Zero based DIMM number.
  @param[in]      ByteOffset   - The byte offset in the SPD.
  @param[in]      ByteCount    - The number of bytes to read starting from the offset location specified by the ByteOffset.
  @param[in]      ReadFromBus  - Flag to determine where to retrieve the SPD value.  TRUE = read from bus.  FALSE = return from MRC cache value.
  @param[out]     Data         - Pointer to buffer to be filled with  DIMM SPD data.

  @retval UnsupportedValue if (ByteOffset + ByteCnt) is larger than the SPD size.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetSpdData) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Dimm,
  UINT16                ByteOffset,
  UINT16                ByteCount,
  BOOLEAN               ReadFromBus,
  UINT8                 *Data
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;
#ifdef SSA_DEBUG_PRINT
  UINT32        Byte;
#endif

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetSpdData %u %u %u %u %u %u %u\n", Socket, Controller, Channel, Dimm, ByteOffset, ByteCount, ReadFromBus);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Data == NULL) ||
      (ByteOffset >= sizeof (MrcSpd)) ||
      (ByteCount == 0) ||
      (ByteCount >= (sizeof (MrcSpd) - ByteOffset))) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsDimmPresent (MrcData, Socket, Controller, Channel, Dimm)) ? Success : NotAvailable;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    MrcData->Inputs.Call.Func->MrcCopyMem (
                                 (UINT8 *) Data,
                                 (UINT8 *) &MrcData->Inputs.Controller[Controller].Channel[Channel].Dimm[Dimm].Spd.Data,
                                 ByteCount
                                 );
#ifdef SSA_DEBUG_PRINT
    for (Byte = ByteOffset; Byte < (Byte + ByteCount); Byte++) {
      SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "  %02X", ((UINT8 *) &MrcData->Inputs.Controller[Controller].Channel[Channel].Dimm[Dimm].Spd.Data) [Byte]);
    }
    SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "\n");
#endif
  }
  return (SsaStatus);
}

/**
  Function used to perform a JEDEC reset for all the DIMMs on all channels of a given memory controller.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.

  @retval Nothing.
**/
VOID
(EFIAPI BiosJedecReset) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "JedecReset, %u/%u\n", Socket, Controller);
#ifdef SSA_PARAM_ERROR_CHECK
  if (mrcSuccess == IsControllerPresent (MrcData, Socket, Controller))
#endif
  {
    MrcResetSequence (MrcData);
  }
  return;
}

/**
  Function used to reset the I/O for a given memory controller.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.

  @retval Nothing.
**/
VOID
(EFIAPI BiosIoReset) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "IoReset, %u/%u\n", Socket, Controller);
#ifdef SSA_PARAM_ERROR_CHECK
  if (mrcSuccess == IsControllerPresent (MrcData, Socket, Controller))
#endif
  {
    IoReset (MrcData);
  }
  return;
}

/**
  Function used to get the specificity of a given margin parameter.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      IoLevel     - I/O level.
  @param[in]      MarginGroup - Margin group.
  @param[out]     Specificity - Pointer to where the margin parameter specificity mask will be stored.

  @retval UnsupportedValue if the IoLevel or MarginGroup parameter value is not supported.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetMarginParamSpecificity) (
  SSA_BIOS_SERVICES_PPI    *This,
  GSM_LT                   IoLevel,
  GSM_GT                   MarginGroup,
  MARGIN_PARAM_SPECIFICITY *Specificity
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;
  MrcDdrType    DdrType;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  DdrType = MrcData->Outputs.DdrType;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Specificity == NULL) || (IoLevel != DdrLevel)) {
    return (UnsupportedValue);
  }
#endif
  SsaStatus = Success;
  switch (MarginGroup) {
    case TxVref:
      if (DdrType == MRC_DDR_TYPE_DDR4) {
        *Specificity = PlatformSpecific | SocketSpecific | ControllerSpecific | ChannelSpecific | RankSpecific;
        break;
      }
    case CmdVref:
      // Fall through to ChannelSpecific Specificity when not using DDR4 memory
      if (DdrType == MRC_DDR_TYPE_DDR4) {
        if (!(MrcData->Inputs.CaVrefConfig)) {
          *Specificity = PlatformSpecific | SocketSpecific | ControllerSpecific;
          break;
        }
      }
    case RecEnDelay:
    case RxDqsDelay:
    case RxOdtUp:
    case RxOdtDn:
    case WrLvlDelay:
    case TxDqsDelay:
    case TxDqDelay:
    case RxVref:
    case TxRonUp:
    case TxRonDn:
    case TxSlewRate:
    case CkAll:
      // Fall through to ChannelSpecific Specificity when not using DDR4 memory
      *Specificity = PlatformSpecific | SocketSpecific | ControllerSpecific | ChannelSpecific;
      break;
    case RxOdt:
    case RxEq:
      *Specificity = PlatformSpecific | SocketSpecific | ControllerSpecific;
      break;
    case CtlAll:
    case CmdAll:
    case RxDqBitDelay:
    case TxEq:
    case TxDqBitDelay:
    case DramDrvStr:
    case RxCtleR:
    case RxCtleC:
      *Specificity = PlatformSpecific | SocketSpecific | ControllerSpecific | ChannelSpecific | RankSpecific;
      break;
    default:
      SsaStatus = UnsupportedValue;
      break;
  }
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamSpecificity %u %u %Xh\n", IoLevel, MarginGroup, *Specificity);
  return (SsaStatus);
}

/**
@brief
  Function used to initialize the system before/after a margin parameter's use.
  Prior to calling the GetMarginParamLimits or SetMarginParamOffset functions
  for a margin parameter, this function should be called with the SetupCleanup
  input parameter set to Setup.  When finished with the margin parameter, this
  function should be called with the SetupCleanup input parameter set to
  Cleanup.

  @param[in, out] This         - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket       - Zero based CPU socket number.
  @param[in]      IoLevel      - I/O level.
  @param[in]      MarginGroup  - Margin group.
  @param[in]      SetupCleanup - Specifies setup or cleanup action.

  @retval UnsupportedValue if the IoLevel or MarginGroup parameter value is not supported.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosInitMarginParam) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  GSM_LT                IoLevel,
  GSM_GT                MarginGroup,
  SETUP_CLEANUP         SetupCleanup
  )
{
  MrcParameters *MrcData;
  UINT32        Channel;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "InitMarginParam %u %u %u %u\n", Socket, IoLevel, MarginGroup, SetupCleanup);
  if ((IoLevel >= GsmLtMax) || (MarginGroup >= GsmGtMax)) {
    return UnsupportedValue;
  }
  if (SetupCleanup == Setup) {
    for (Channel = cCHANNEL0; Channel <= MAX_CHANNEL; Channel++) {
      MrcHalSetRegVrefadjust1 (MrcData, Channel, MRC_IGNORE_ARG, TRUE);
    }
  }
  return Success;
}

/**
  Function used to get the minimum and maximum offsets that can be applied to a given margin parameter and the time delay in micro seconds for the new value to take effect.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket      - Zero based CPU socket number.
  @param[in]      Controller  - Zero based controller number.
  @param[in]      Channel     - Zero based channel number.
  @param[in]      Dimm        - Zero based DIMM number.
  @param[in]      Rank        - Zero based physical rank number.
  @param[in]      LaneMasks   - Pointer to array of masks of the lanes/strobes that participate to the margin parameter offset limit calculation.  It is applicable only if margin parameter is per-strobe or per-bit/lane controllable.  The number of array elements is the BusWidth value from the GetSystemInfo() function divided by 8.  If a margin parameter is strobe specific and if any lane associated with that strobe is set in the mask then that strobe is selected.  For example, for a LaneMasks value of [0x00, ... 0x00, 0x01], only the min/max offset of the first strobe group is returned.
  @param[in]      IoLevel     - I/O level.
  @param[in]      MarginGroup - Margin group.
  @param[out]     MinOffset   - Pointer to where the minimum offset from the current setting supported by the margin parameter will be stored.  This is a signed value.
  @param[out]     MaxOffset   - Pointer to where the maximum offset from the current setting supported by the margin parameter parameter will be stored.  This is a signed value.
  @param[out]     Delay       - Pointer to where the wait time in micro-seconds that is required for the new setting to take effect will be stored.
  @param[out]     StepUnit    - Pointer to where the margin parameter step unit will be stored.  For timing parameters, the units are tCK / 2048.  For voltage parameters, the units are Vdd / 100.

  @retval UnsupportedValue if the IoLevel or MarginGroup parameter value is not supported.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetMarginParamLimits) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Dimm,
  UINT8                 Rank,
  CONST UINT8           *LaneMasks,
  GSM_LT                IoLevel,
  GSM_GT                MarginGroup,
  INT16                 *MinOffset,
  INT16                 *MaxOffset,
  UINT16                *Delay,
  UINT16                *StepUnit
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    Status;
  UINT8         LogicalRank;
  MrcVddSelect  VddVoltage;
  MrcDdrType    DdrType;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  DdrType = MrcData->Outputs.DdrType;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetMarginParamLimits %u %u %u %u %u %u %u\n", Socket, Controller, Channel, Dimm, Rank, IoLevel, MarginGroup);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((IoLevel != DdrLevel) || (MinOffset == NULL) || (MaxOffset == NULL) || (Delay == NULL)) {
    return (UnsupportedValue);
  }
  Status = (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Dimm, Rank)) ? Success : UnsupportedValue;
  if (Status == Success)
#else
  Status = Success;
#endif
  {
    LogicalRank = (Dimm * MAX_RANK_IN_DIMM) + Rank;
    VddVoltage  = MrcData->Outputs.VddVoltage[MrcData->Inputs.MemoryProfile];
    *Delay      = 0;
    *StepUnit   = PI_STEP;
    switch (MarginGroup) {
      case RecEnDelay:
        *MinOffset = RCVEN_OFFSET_MIN;
        *MaxOffset = RCVEN_OFFSET_MAX;
        GetMarginParamLimitsRecEnDelay (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        break;

      case RxDqsDelay:
        *MinOffset = RXDQS_OFFSET_MIN;
        *MaxOffset = RXDQS_OFFSET_MAX;
        GetMarginParamLimitsRxDqsDelay (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        break;

      case RxDqBitDelay:
        *MinOffset = (-1) * RXDQBIT_OFFSET_MAX;
        *MaxOffset = RXDQBIT_OFFSET_MAX;
        GetMarginParamLimitsRxDqBitDelay (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        break;

      case RxOdt:
        *MinOffset = RXODT_OFFSET_MIN;
        *MaxOffset = RXODT_OFFSET_MAX;
        GetMarginParamLimitsRxOdtDelay (MrcData, Socket, Controller, MinOffset, MaxOffset, Delay);
        break;

      case RxOdtUp:
        *MinOffset = RXODT_UP_OFFSET_MIN;
        *MaxOffset = RXODT_UP_OFFSET_MAX;
        GetMarginParamLimitsRxOdtUpDelay (MrcData, Socket, Controller, Channel, MinOffset, MaxOffset, Delay);
        break;

      case RxOdtDn:
        *MinOffset = RXODT_DN_OFFSET_MIN;
        *MaxOffset = RXODT_DN_OFFSET_MAX;
        GetMarginParamLimitsRxOdtDnDelay (MrcData, Socket, Controller, Channel, MinOffset, MaxOffset, Delay);
        break;

      case DramDrvStr:
        if (DdrType == MRC_DDR_TYPE_LPDDR3) {
          *MinOffset = DRAM_DRV_STR_DELAY_LPDDR3_MIN;
          *MaxOffset = DRAM_DRV_STR_DELAY_LPDDR3_MAX;
        } else if (DdrType == MRC_DDR_TYPE_DDR4) {
          *MinOffset = DRAM_DRV_STR_DELAY_DDR4_MIN;
          *MaxOffset = DRAM_DRV_STR_DELAY_DDR4_MAX;
        } else {
          *MinOffset = DRAM_DRV_STR_DELAY_DDR3_MIN;
          *MaxOffset = DRAM_DRV_STR_DELAY_DDR3_MAX;
        }
        GetMarginParamLimitsDramDrvStrDelay (MrcData, Socket, Controller, Channel, MinOffset, MaxOffset, Delay);
        break;

      case RxEq:
        *MinOffset = RXEQ_OFFSET_MIN;
        *MaxOffset = RXEQ_OFFSET_MAX;
        GetMarginParamLimitsRxEqDelay (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        break;

      case RxCtleR:
        *MinOffset = RX_CTLE_R_OFFSET_MIN;
        *MaxOffset = RX_CTLE_R_OFFSET_MAX;
        GetMarginParamLimitsRxCtleRDelay (MrcData, Socket, Controller, Channel, MinOffset, MaxOffset, Delay);
        break;

      case RxCtleC:
        *MinOffset = RX_CTLE_C_OFFSET_MIN;
        *MaxOffset = RX_CTLE_C_OFFSET_MAX;
        GetMarginParamLimitsRxCtleCDelay (MrcData, Socket, Controller, Channel, MinOffset, MaxOffset, Delay);
        break;

      case WrLvlDelay:
      case TxDqsDelay:
        *MinOffset = TXDQS_OFFSET_MIN;
        *MaxOffset = TXDQS_OFFSET_MAX;
        GetMarginParamLimitsTxDqsDelay (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        if (TxDqsDelay == MarginGroup) {
          break;
        }
      case TxDqDelay:
        if (TxDqDelay == MarginGroup) {
          *MinOffset = TXDQ_OFFSET_MIN;
          *MaxOffset = TXDQ_OFFSET_MAX;
        }
        GetMarginParamLimitsTxDqDelay (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        break;

      case TxEq:
        *MinOffset = TXEQ_OFFSET_MIN;
        *MaxOffset = TXEQ_OFFSET_MAX;
        GetMarginParamLimitsTxEqDelay (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        break;

      case TxDqBitDelay:
        *MinOffset = (-1) * TXDQBIT_OFFSET_MAX;
        *MaxOffset = TXDQBIT_OFFSET_MAX;
        GetMarginParamLimitsTxDqBitDelay (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        break;

      case TxRonUp:
        *MinOffset = TXRON_UP_OFFSET_MIN;
        *MaxOffset = TXRON_UP_OFFSET_MAX;
        GetMarginParamLimitsTxRonUpDelay (MrcData, Socket, Controller, Channel, MinOffset, MaxOffset, Delay);
        break;

      case TxRonDn:
        *MinOffset = TXRON_DN_OFFSET_MIN;
        *MaxOffset = TXRON_DN_OFFSET_MAX;
        GetMarginParamLimitsTxRonDnDelay (MrcData, Socket, Controller, Channel, MinOffset, MaxOffset, Delay);
        break;

      case TxSlewRate:
        *MinOffset = TX_SLEW_RATE_OFFSET_MIN;
        *MaxOffset = TX_SLEW_RATE_OFFSET_MAX;
        GetMarginParamLimitsTxSlewRateDelay (MrcData, Socket, Controller, Channel, MinOffset, MaxOffset, Delay);
        break;

      case RxVref:
        *StepUnit = (UINT16) RX_VREF (VddVoltage);
        *MinOffset = RXVREF_OFFSET_MIN;
        *MaxOffset = RXVREF_OFFSET_MAX;
        GetMarginParamLimitsRxVref (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        break;

      case TxVref:
        *StepUnit = (UINT16) TX_VREF (VddVoltage);
        // The following "*2"'s are present to prevent clipping the range
        *MinOffset = TXVREF_OFFSET_MIN * 2;
        *MaxOffset = TXVREF_OFFSET_MAX * 2;
        GetMarginParamLimitsTxVref (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        break;

      case CmdAll:
        *MinOffset = (-1) * CLOCK_OFFSET_MAX;
        *MaxOffset = CLOCK_OFFSET_MAX;
        GetMarginParamLimitsCmdAll (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        break;

      case CtlAll:
        *MinOffset = (-1) * CMDN_OFFSET_MAX;
        *MaxOffset = CTL_CS_OFFSET_MAX;
        GetMarginParamLimitsCtlAll (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        break;

      case CkAll:
        *MinOffset = (-1) * CLOCK_OFFSET_MAX;
        *MaxOffset = CLOCK_OFFSET_MAX;
        GetMarginParamLimitsCkAll (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        break;

      case CmdVref:
        *StepUnit = (UINT16) CA_VREF (VddVoltage);
        *MinOffset = CMDVREF_OFFSET_MIN * 2;
        *MaxOffset = CMDVREF_OFFSET_MAX * 2;
        GetMarginParamLimitsCmdVref (MrcData, Socket, Controller, Channel, LogicalRank, MinOffset, MaxOffset, Delay);
        break;

      default:
        Status = UnsupportedValue;
        break;
    }
    SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "  %u %u\n", *StepUnit, *Delay);
  }
  return (Status);
}

/**
  Function used to set the offset of a margin parameter.

  @param[in, out] This          - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      Dimm          - Zero based DIMM number.
  @param[in]      Rank          - Zero based physical rank number.
  @param[in]      LaneMasks     - Pointer to array of masks of the lanes/strobes that participate to the margin parameter offset limit calculation.  It is applicable only if margin parameter is per-strobe or per-bit/lane controllable.  The number of array elements is the BusWidth value from the GetSystemInfo() function divided by 8.  If a margin parameter is strobe specific and if any lane associated with that strobe is set in the mask then that strobe is selected.  For example, for a LaneMasks value of [0x00, ... 0x00, 0x01], only the min/max offset of the first strobe group is returned.
  @param[in]      IoLevel       - Id of the I/O level to access. Can be VmseLevel(0), DdrLevel(1), LrbufLevel(2).
  @param[in]      MarginGroup   - Id of the margin group. Can be RcvEna(0), RdT(1), WrT(2), WrDqsT(3), RdV(4) or WrV(5).
  @param[in]      CurrentOffset - Signed value of the current offset setting.  The range of valid values is available  via the GetMarginParamLimits() function.
  @param[in]      NewOffset     - Signed value of the new offset setting.  The range of valid values is available  via the GetMarginParamLimits() function.

  @retval UnsupportedValue if the IoLevel or MarginGroup parameter value is not supported.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosSetMarginParamOffset) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Dimm,
  UINT8                 Rank,
  CONST UINT8           *LaneMasks,
  GSM_LT                IoLevel,
  GSM_GT                MarginGroup,
  INT16                 CurrentOffset,
  INT16                 NewOffset
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;
  INT64         TmpValue;
  INT16         Value;
  UINT8         LogicalRank;
  UINT8         LogicalRankMask;
  UINT8         Bit;
  UINT8         Byte;
  UINT8         ByteEnd;
  BOOLEAN       Ddr4;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetMarginParamOffset %u %u %u %u %u %u %u %d %d\n", Socket, Controller, Channel, Dimm, Rank, IoLevel, MarginGroup, CurrentOffset, NewOffset);
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) LaneMasks, 8);

  Ddr4 = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_DDR4);

#ifdef SSA_PARAM_ERROR_CHECK
  if ((IoLevel != DdrLevel) || (MarginGroup >= GsmGtMax)) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsRankPresent (MrcData, Socket, Controller, Channel, Dimm, Rank)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    LogicalRank = (Dimm * MAX_RANK_IN_DIMM) + Rank;
    ByteEnd = MrcData->Outputs.SdramCount;
    switch (MarginGroup) {
      case RecEnDelay:
        SsaStatus = SetMarginParamOffsetRecEnDelay (MrcData, Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);
        break;

      case RxDqsDelay:
        Value = NewOffset;
        for (Byte = 0; Byte < ByteEnd; Byte++) {
          if (mrcSuccess != ChangeMargin (MrcData, RdT, Value, 0, SINGLE_CAST, Channel, LogicalRank, Byte, 0, UPDATE_MRCDATA, 0, MrcRegFileRank)) {
            SsaStatus = UnsupportedValue;
            break;
          }
        }
        break;

      case RxDqBitDelay:
      case TxDqBitDelay:
        TmpValue = NewOffset;
        for (Byte = 0; Byte < ByteEnd; Byte++) {
          for (Bit = 0; Bit < MAX_BITS; Bit++) {
            if (LaneMasks[Byte] & (0x1 << Bit)) {
              MrcGetSetDdrIoGroup (
                MrcData,
                (UINT8) Socket,
                (UINT8) Channel,
                MRC_IGNORE_ARG_8,
                (UINT8) Rank,
                (UINT8) Byte,
                Bit,
                MRC_IGNORE_ARG_8,
                DdrLevel,
                MarginGroup,
                GSM_READ_CSR | GSM_FORCE_WRITE,
                &TmpValue
                );
            }
          } // end for each bit
        } // end for each byte
        break;

      case RxOdt:
        UpdateCompGlobalOffset (MrcData, RdOdt, NewOffset, 0, 1);
        break;

      case RxOdtUp:
        for (Byte = 0; Byte < ByteEnd; Byte++) {
          UpdateOptParamOffset (MrcData, Channel, LogicalRank, Byte, OptRdOdtUp, NewOffset, 1);
        }
        break;

      case RxOdtDn:
        TmpValue = NewOffset;
        for (Byte = 0; Byte < ByteEnd; Byte++) {
          UpdateOptParamOffset (MrcData, Channel, LogicalRank, Byte, OptRdOdtDn, NewOffset, 1);
        }
        break;

      case DramDrvStr:
        Value = NewOffset;
        UpdateOptParamOffset (
          MrcData,
          Channel,
          Rank,
          0,
          OptDimmRon,
          Value,
          1
          );
        break;

      case RxEq:
        TmpValue = NewOffset;
        for (Byte = 0; Byte < ByteEnd; Byte++) {
          UpdateOptParamOffset (MrcData, Channel, LogicalRank, Byte, OptRxEq, NewOffset, 1);
        }
        break;

      case RxCtleR:
        TmpValue = NewOffset;
        for (Byte = 0; Byte < ByteEnd; Byte++) {
          MrcGetSetDdrIoGroup (
            MrcData,
            (UINT8) Socket,
            (UINT8) Channel,
            MRC_IGNORE_ARG_8,
            (UINT8) Rank,
            (UINT8) Byte,
            MRC_IGNORE_ARG_8,
            MRC_IGNORE_ARG_8,
            DdrLevel,
            MarginGroup,
            GSM_READ_CSR | GSM_FORCE_WRITE,
            &TmpValue
            );
        }
        break;

      case RxCtleC:
        TmpValue = NewOffset;
        for (Byte = 0; Byte < ByteEnd; Byte++) {
          MrcGetSetDdrIoGroup (
            MrcData,
            (UINT8) Socket,
            (UINT8) Channel,
            MRC_IGNORE_ARG_8,
            (UINT8) Rank,
            (UINT8) Byte,
            MRC_IGNORE_ARG_8,
            MRC_IGNORE_ARG_8,
            DdrLevel,
            MarginGroup,
            GSM_READ_CSR | GSM_FORCE_WRITE,
            &TmpValue
            );
        }
        break;

      case WrLvlDelay:
      case TxDqsDelay:
        SsaStatus = SetMarginParamOffsetTxDqsDelay (MrcData, Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);

        if (TxDqsDelay == MarginGroup) {
          break;
        }
      case TxDqDelay:
        SsaStatus = SetMarginParamOffsetTxDqDelay (MrcData, Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);
        break;

      case TxEq:
        for (Byte = 0; Byte < ByteEnd; Byte++) {
          UpdateOptParamOffset (MrcData, Channel, LogicalRank, Byte, OptTxEq, NewOffset, 1);
        }
        break;

      case TxRonUp:
        TmpValue = NewOffset;
        for (Byte = 0; Byte < ByteEnd; Byte++) {
          MrcGetSetDdrIoGroup (
            MrcData,
            (UINT8) Socket,
            Channel,
            MRC_IGNORE_ARG_8,
            MRC_IGNORE_ARG_8,
            Byte,
            MRC_IGNORE_ARG_8,
            MRC_IGNORE_ARG_8,
            DdrLevel,
            MarginGroup,
            GSM_READ_CSR | GSM_FORCE_WRITE,
            &TmpValue
            );
        }
        break;

      case TxRonDn:
        TmpValue = NewOffset;
        for (Byte = 0; Byte < ByteEnd; Byte++) {
          MrcGetSetDdrIoGroup (
            MrcData,
            (UINT8) Socket,
            Channel,
            MRC_IGNORE_ARG_8,
            MRC_IGNORE_ARG_8,
            Byte,
            MRC_IGNORE_ARG_8,
            MRC_IGNORE_ARG_8,
            DdrLevel,
            MarginGroup,
            GSM_READ_CSR | GSM_FORCE_WRITE,
            &TmpValue
            );
        }
        break;

      case TxSlewRate:
        for (Byte = 0; Byte < ByteEnd; Byte++) {
          UpdateOptParamOffset (MrcData, Channel, LogicalRank, Byte, OptSComp, NewOffset, 1);
        }
        break;

      case RxVref:
        Value = NewOffset;
        for (Byte = 0; Byte < ByteEnd; Byte++) {
          if (mrcSuccess != ChangeMargin (MrcData, RdV, Value, 0, SINGLE_CAST, Channel, LogicalRank, Byte, 0, UPDATE_MRCDATA, 0, MrcRegFileRank)) {
            SsaStatus = UnsupportedValue;
            break;
          }
        }
        break;

      case TxVref:
        Value = NewOffset - CurrentOffset;
        LogicalRankMask  = 1 << LogicalRank;
        UpdateVrefWaitTilStable (MrcData, Channel, UPDATE_MRCDATA, Value, LogicalRankMask, 0x1FF, TRUE, 0);
        break;

      case CmdAll:
        SsaStatus = SetMarginParamOffsetCmdAll (MrcData, Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);
        break;

      case CtlAll:
        SsaStatus = SetMarginParamOffsetCtlAll (MrcData, Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);
        break;

      case CkAll:
        SsaStatus = SetMarginParamOffsetCkAll (MrcData, Socket, Controller, Channel, LogicalRank, CurrentOffset, NewOffset);
        break;

      case CmdVref:
        if (!Ddr4 || (Channel == 0)) {
          UpdateVrefWaitTilStable (MrcData, 2, 0, NewOffset, 0, 0, FALSE, 0);
        }
        if (Ddr4 && (Channel == 1)) {
          // ch1 CA vref in DDR4
          UpdateVrefWaitTilStable (MrcData, 3, 0, NewOffset, 0, 0, FALSE, 0);
        }
        break;

      default:
        break;
    } // end switch MarginGroup
  } // end if SsaStatus == Success

  return (SsaStatus);
}

/**
  Function used to set the ZQCal configuration.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Enable     - Specifies whether ZQCal is enabled.  TRUE enables ZQCal; FALSE disables it.
  @param[out]     PrevEnable - Pointer to where the previous ZQCal enable setting will be stored.  This value may be NULL.

  @retval Nothing.
**/
VOID
(EFIAPI BiosSetZQCalConfig) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  BOOLEAN               Enable,
  BOOLEAN               *PrevEnable
  )
{
  MrcParameters *MrcData;
  UINT32        Channel;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if (mrcSuccess == IsControllerPresent (MrcData, Socket, Controller))
#endif
  {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) {
        if (PrevEnable != NULL) {
          *PrevEnable = (BOOLEAN) MrcHalGetRegSchedCbitDisableZq (MrcData, Channel);
        }
        MrcHalRmwRegSchedCbitDisableZq (MrcData, Channel, Enable ? 0 : 1);
      }
    }
  }
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetZQCalConfig %u %u %u %u\n", Socket, Controller, (PrevEnable == NULL) ? 0 : *PrevEnable, Enable);
  return;
}

/**
  Function used to set the RComp update configuration.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Enable     - Specifies whether RComp updates are enabled.  TRUE enables RComp updates; FALSE disables them.
  @param[out]     PrevEnable - Pointer to where the previous RComp update enable setting will be stored.  This value may be NULL.

  @retval Nothing.
**/
VOID
(EFIAPI BiosSetRCompUpdateConfig) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  BOOLEAN               Enable,
  BOOLEAN               *PrevEnable
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if (mrcSuccess == IsControllerPresent (MrcData, Socket, Controller))
#endif
  {
    if (PrevEnable != NULL) {
      *PrevEnable = (BOOLEAN) MrcHalGetRegDisableRcomp (MrcData);
    }
    MrcHalRmwRegDisableRcomp (MrcData, Enable ? 0 : 1);
  }
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetRCompUpdateConfig %u %u %u %u\n", Socket, Controller, (PrevEnable == NULL) ? 0 : *PrevEnable, Enable);
  return;
}

/**
  Function used to set the page-open configuration.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Enable     - Specifies whether page-open is enabled.  TRUE enables page-open; FALSE disables it.
  @param[out]     PrevEnable - Pointer to where the previous page-open enable setting will be stored.  This value may be NULL.

  @retval Nothing.
**/
VOID
(EFIAPI BiosSetPageOpenConfig) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  BOOLEAN               Enable,
  BOOLEAN               *PrevEnable
  )
{
  MrcDebug *Debug;

  Debug = &((MrcParameters *) This->SsaMemoryConfig->MrcData)->Outputs.Debug;
  SSA_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SetPageOpenConfig %u %u %u\n", Socket, Controller, Enable);
  SSA_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Not implemented\n");
  return;
}

/**
  Function used to clear all memory.

  @param[in, out] This - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.

  @retval NotAvailable if function is not supported by the BIOS.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosScrubMemory) (
  SSA_BIOS_SERVICES_PPI *This
  )
{
  MrcParameters *MrcData;
  UINT32 CleanMemory;
  MrcStatus Status;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "ScrubMemory\n");
  CleanMemory = MrcData->Inputs.CleanMemory;
  MrcData->Inputs.CleanMemory = 1;
  Status = MrcEccClean (MrcData);
  MrcData->Inputs.CleanMemory = CleanMemory;
  return ((Status == mrcSuccess) ? Success : Failure);
}

/**
  Function used to initialize CPGC engine(s) for all channels of a given memory
  controller.  Prior to configuring/using the CPGC engine, this function should
  be called with the SetupCleanup input parameter set to Setup.  When finished
  with the CPGC engine, this function should be called with the SetupCleanup
  input parameter set to Cleanup.

  @param[in, out] This         - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket       - Zero based CPU socket number.
  @param[in]      Controller   - Zero based controller number.
  @param[in]      SetupCleanup - Specifies setup or cleanup action.

  @retval Nothing.
**/
VOID
(EFIAPI BiosInitCpgc) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  SETUP_CLEANUP         SetupCleanup
  )
{
  SSA_DEBUG_MSG (&((MrcParameters *) This->SsaMemoryConfig->MrcData)->Outputs.Debug, MSG_LEVEL_NOTE, "InitCpgc %u %u %u\n", Socket, Controller, SetupCleanup);
  return;
}

#endif // SSA_FLAG
// end file BiosSsaMemoryConfig.c
