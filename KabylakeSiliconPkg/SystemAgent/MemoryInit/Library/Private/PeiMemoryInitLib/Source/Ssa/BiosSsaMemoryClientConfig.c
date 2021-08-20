/** @file
  This file contains the BIOS implementation of the BIOS-SSA Client Memory Configuration API.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2014 Intel Corporation.

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
#include "MrcSsaServices.h"
#include "MrcSsaCommon.h"
#include "McAddress.h"
#include "MrcHalMiddleLevel.h"
#include "MrcCommon.h"
#include "MrcGeneral.h"

#ifdef SSA_FLAG
#define MAX_CHUNK_SIZE (8)

GLOBAL_REMOVE_IF_UNREFERENCED const MRC_CLIENT_CPGC_INFO CpgcInfoConst = {
  MAX_NUMBER_DQDB_CACHELINES,
  MAX_DQDB_INC_RATE_EXPONENTIAL_VAL,
  MAX_DQDB_INC_RATE_LINEAR_VAL,
  MAX_NUMBER_DQDB_UNISEQS,
  MAX_DQDB_UNISEQ_SEED_VAL,
  MAX_DQDB_UNISEQ_L_VAL,
  MAX_DQDB_UNISEQ_M_VAL,
  MAX_DQDB_UNISEQ_N_VAL,
  MAX_DQDB_UNISEQ_SEED_RELOAD_RATE_VAL,
  MAX_DQDB_UNISEQ_SEED_SAVE_RATE_VAL,
  MAX_DQDB_INVERT_DC_SHIFT_RATE_EXPONENTIAL,
  MAX_NUMBER_CADB_ROWS,
  MAX_NUMBER_CADB_UNISEQS,
  MAX_CADB_UNISEQ_SEED_VAL,
  MAX_CADB_UNISEQ_L_VAL,
  MAX_CADB_UNISEQ_M_VAL,
  MAX_CADB_UNISEQ_N_VAL,
  MAX_DUMMY_READ_L_VAL,
  MAX_DUMMY_READ_M_VAL,
  MAX_DUMMY_READ_N_VAL,
  MAX_START_DELAY_VAL,
  IS_LOOP_COUNT_EXPONENTIAL,
  MAX_LOOP_COUNT_VAL,
  MAX_NUMBER_SUBSEQS,
  MAX_BURST_LENGTH_EXPONENTIAL_VAL,
  MAX_BURST_LENGTH_LINEAR_VAL,
  MAX_INTER_SUBSEQ_WAIT_VAL,
  MAX_OFFSET_ADDR_UPDATE_RATE_VAL,
  MAX_ADDR_INVERT_RATE_VAL,
  MAX_RANK_ADDR_INC_RATE_EXPONENT_VAL,
  MAX_RANK_ADDR_INC_RATE_LINEAR_VAL,
  MIN_RANK_ADDR_INC_VAL,
  MAX_RANK_ADDR_INC_VAL,
  MAX_BANK_ADDR_INC_RATE_EXPONENT_VAL,
  MAX_BANK_ADDR_INC_RATE_LINEAR_VAL,
  Min_BANK_ADDR_INC_VAL,
  MAX_BANK_ADDR_INC_VAL,
  MAX_ROW_ADDR_INC_RATE_EXPONENT_VAL,
  MAX_ROW_ADDR_INC_RATE_LINEAR_VAL,
  MIN_ROW_ADDR_INC_VAL,
  MAX_ROW_ADDR_INC_VAL,
  MAX_COL_ADDR_INC_RATE_EXPONENT_VAL,
  MAX_COL_ADDR_INC_RATE_LINEAR_VAL,
  MIN_COL_ADDR_INC_VAL,
  MAX_COL_ADDR_INC_VAL,
  MAX_NUMBER_RANK_MAP_ENTRIES,
  MAX_NUMBER_BANK_MAP_ENTRIES,
  MAX_NUMBER_ROW_ADDR_SWIZZLE_ENTRIES,
  MAX_ROW_ADDR_SWIZZLE_VAL,
  MAX_STOP_ON_NTH_ERROR_COUNT_VAL,
  MAX_NUMBER_ERROR_COUNTERS,
  MAX_SCRAMBLER_KEY_VAL,
  MAX_REFRESH_IDLE_TIMER_VAL
};

/**
  Function used to get information about about the CPGC capabilities.

  @param[in, out] This     - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[out]     CpgcInfo - Pointer to buffer to be filled with CPGC capabilities information.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientGetCpgcInfo) (
  SSA_BIOS_SERVICES_PPI *This,
  MRC_CLIENT_CPGC_INFO  *CpgcInfo
  )
{
  MrcParameters *MrcData;

#ifdef SSA_PARAM_ERROR_CHECK
  if (CpgcInfo != NULL)
#endif
  {
    MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
    MrcData->Inputs.Call.Func->MrcCopyMem ((UINT8 *) CpgcInfo, (UINT8 *) &CpgcInfoConst, sizeof (MRC_CLIENT_CPGC_INFO));
    SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) CpgcInfo, sizeof (MRC_CLIENT_CPGC_INFO));
  }
  return;
}

/**
  Function used to enable/disable address-as-data.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket      - Zero based CPU socket number.
  @param[in]      Controller  - Zero based controller number.
  @param[in]      EnableRead  - Specifies whether address-as-data for reads is enabled.  TRUE enables address-as-data for reads, FALSE disables it.
  @param[in]      EnableWrite - Specifies whether address-as-data for writes is enabled.  TRUE enables address-as-data for writes, FALSE disables it.

  @retval NotAvailable if the system does not support the address-as-data feature.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetAddressAsData) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  BOOLEAN               EnableRead,
  BOOLEAN               EnableWrite
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "BiosClientSetAddressAsData %u %u %u %u\n", Socket, Controller, EnableRead, EnableWrite);
#ifdef SSA_PARAM_ERROR_CHECK
  SsaStatus = (mrcSuccess == IsControllerPresent (MrcData, Socket, Controller)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    MrcHalRmwPatWdbAddressAsDataCtrl (MrcData, (BOOLEAN) EnableWrite, (BOOLEAN) EnableRead);
  }
  return (SsaStatus);
}

/**
  Function used to write pattern content to the DqDB.

  @param[in, out] This                - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket              - Zero based CPU socket number.
  @param[in]      Controller          - Zero based controller number.
  @param[in]      Channel             - Zero based channel number.
  @param[in]      Pattern             - Pointer to buffer containing the DqDB pattern.
  @param[in]      CachelineCount      - Size of the buffer pattern in number of cachelines.  Each cacheline has 8 UINT64 elements.  For example, if CachelineCount is 1 then the Pattern buffer size is 64 bytes.
  @param[in]      StartCachelineIndex - Start offset on the DqDB.  The sum of the CachelineCount and StartCachelineIndex values must be less than or equal to the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetDqdbPattern) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  CONST UINT64          *Pattern,
  UINT8                 CachelineCount,
  UINT8                 StartCachelineIndex
  )
{
  MrcParameters *MrcData;
#ifdef SSA_DEBUG_PRINT
  UINT32 Chunk;
  UINT64_STRUCT *Pointer;
#endif

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_DEBUG_PRINT
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "BiosClientSetDqdbPattern %u, %u, %u, %u, %u", Socket, Controller, Channel, StartCachelineIndex, CachelineCount);
  for (Chunk = 0; Chunk < CachelineCount; Chunk++) {
    Pointer = (UINT64_STRUCT *) &Pattern[Chunk];
    SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, ", 0x%08X_%08X", Pointer->Data32.High, Pointer->Data32.Low);
  }
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "\n");
#endif
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Pattern == NULL) ||
      (CachelineCount == 0) ||
      ((StartCachelineIndex + CachelineCount) > MCHBAR_CH0_CR_QCLK_LDAT_PDAT_FASTADDR_MAX) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  {
    MrcHalSetWdbPattern (MrcData, Channel, Pattern, CachelineCount, StartCachelineIndex);
  }
  return;
}

/**
  Function used to read pattern content from the DqDB.

  @param[in, out] This                - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket              - Zero based CPU socket number.
  @param[in]      Controller          - Zero based controller number.
  @param[in]      Channel             - Zero based channel number.
  @param[out]     Pattern             - Pointer to buffer to be filled with the DqDB pattern.
  @param[in]      CachelineCount      - Size of the buffer pattern in number of cachelines.  Each cacheline has 8 UINT64 elements.  For example, if CachelineCount is 1 then the Pattern buffer size is 64 bytes.
  @param[in]      StartCachelineIndex - Start offset on the DqDB.  The sum of the CachelineCount and StartCachelineIndex values must be less than or equal to the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientGetDqdbPattern) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT64                *Pattern,
  UINT8                 CachelineCount,
  UINT8                 StartCachelineIndex
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_DEBUG_PRINT
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "BiosClientGetDqdbPattern %u, %u, %u, %u, %u\n", Socket, Controller, Channel, StartCachelineIndex, CachelineCount);
#endif
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Pattern == NULL) ||
      (CachelineCount == 0) ||
      ((StartCachelineIndex + CachelineCount) > MCHBAR_CH0_CR_QCLK_LDAT_PDAT_FASTADDR_MAX) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  {
    MrcHalGetWdbPattern (MrcData, Channel, Pattern, CachelineCount, StartCachelineIndex);
  }
  return;
}

/**
  Function used to set the WDB start and end indexes as well as the WDB increment rate.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket      - Zero based CPU socket number.
  @param[in]      Controller  - Zero based controller number.
  @param[in]      Channel     - Zero based channel number.
  @param[in]      StartIndex  - Starting index in the DqDB.  The value must be less than or equal to the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.
  @param[in]      EndIndex    - Ending index in the DqDB.  The value must be less than or equal to the StartIndex value and less than or equal to the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.
  @param[in]      IncRateMode - Increment rate mode.
  @param[in]      IncRate     - Increment rate value.  If the IncRateMode is ExponentialDqdbIncRateMode then the IncRate value must be less than or equal to the MaxDqdbIncRateExponentVal from the GetCpgcInfo() function.  If the IncRateMode is LinearDqdbIncRateMode then the IncRate value must be less than or equal to the MaxDqdbIncRateLinearVal from the GetCpgcInfo() function.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetDqdbIndexes) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 StartIndex,
  UINT8                 EndIndex,
  DQDB_INC_RATE_MODE    IncRateMode,
  UINT8                 IncRate
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetDqdbIndexes (%u, %u, %u, %u, %u, %u, %u);\n", Socket, Controller, Channel, StartIndex, EndIndex, IncRateMode, IncRate);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((StartIndex > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_MAX) ||
      (EndIndex > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_MAX) ||
      (IncRateMode >= DqdbIncRateModeMax) ||
      (IncRate > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_MAX) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  MrcHalRmwWdbPatternControl (MrcData, Channel, StartIndex, EndIndex, (MRC_HAL_ENUM_INCRMENT_SCALE_CONTROL) IncRateMode, IncRate);
  return;
}

/**
  Function used to set the WDB start and end indexes as well as the WDB increment rate.

  @param[in, out] This          - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      EccDataSource - Specifies the ECC signal data source.

  @retval NotAvailable if the system does not support the ECC Data Source feature.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetDqdbEccDataSource) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  ECC_DATA_SOURCE       EccDataSource
  )
{
  const MRC_FUNCTION *MrcCall;
  MrcParameters      *MrcData;
  SSA_STATUS         SsaStatus;
  UINT32             Mux[MAX_NUMBER_DQDB_UNISEQS];

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetDqdbEccDataSource (%u, %u, %u, %u);\n", Socket, Controller, Channel, EccDataSource);
#ifdef SSA_PARAM_ERROR_CHECK
  if (EccDataSource >= EccDataSourceMax) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    MrcCall = MrcData->Inputs.Call.Func;
    MrcCall->MrcSetMemDword ((UINT32 *) &Mux[0], sizeof (Mux) / sizeof (Mux[0]), MRC_IGNORE_ARG);
    MrcHalRmwWdbPatternMuxControl (
      MrcData,
      Channel,
      (MRC_HAL_ENUM_MUX_CONTROL *) &Mux[0],
      sizeof (Mux) / sizeof (Mux[0]),
      MrcHalLfsrTypeIgnoreArg,
      MrcHalLfsrChainingIgnoreArg,
      MrcHalEccReplaceByteIgnoreArg,
      (MRC_HAL_ENUM_ECC_SOURCE_SELECT) EccDataSource,
      MRC_IGNORE_ARG,
      MRC_IGNORE_ARG,
      MrcHalSeedRateModeIgnoreArg
      );
  }
  return (SsaStatus);
}

/**
  Function used to set the DqDB unisequencer mode.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      Uniseq     - Zero based DqDB unisequencer number.
  @param[in]      Mode       - DqDB unisequencer mode.

  @retval NotAvailable if the given Mode value is not available on the given Uniseq.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetDqdbUniseqMode) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Uniseq,
  DQDB_UNISEQ_MODE      Mode
  )
{
  const MRC_FUNCTION *MrcCall;
  MrcParameters      *MrcData;
  SSA_STATUS         SsaStatus;
  UINT32             Mux[MAX_NUMBER_DQDB_UNISEQS];

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetDqdbUniseqMode (%u, %u, %u, %u %u);\n", Socket, Controller, Channel, Uniseq, Mode);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Uniseq >= MAX_NUMBER_DQDB_UNISEQS) ||
      (Mode >= DqdbUniseqModeMax)) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    MrcCall = MrcData->Inputs.Call.Func;
    MrcCall->MrcSetMemDword ((UINT32 *) &Mux[0], sizeof (Mux) / sizeof (Mux[0]), MRC_IGNORE_ARG);
    Mux[Uniseq] = Mode;
    MrcHalRmwWdbPatternMuxControl (
      MrcData,
      Channel,
      (MRC_HAL_ENUM_MUX_CONTROL *) &Mux[0],
      sizeof (Mux) / sizeof (Mux[0]),
      MrcHalLfsrTypeIgnoreArg,
      MrcHalLfsrChainingIgnoreArg,
      MrcHalEccReplaceByteIgnoreArg,
      MrcHalEccDataSourceSelectIgnoreArg,
      MRC_IGNORE_ARG,
      MRC_IGNORE_ARG,
      MrcHalSeedRateModeIgnoreArg
      );
  }
  return (SsaStatus);
}

/**
  Function used to set the DqDB write unisequencer seed value.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      Uniseq     - Zero based DqDB unisequencer number.
  @param[in]      Seed       - DqDB write unisequencer seed value.  The value must be less than or equal to the MaxDqdbUniseqSeedVal value from the GetCpgcInfo() function.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetDqdbUniseqWrSeed) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Uniseq,
  UINT32                Seed
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetDqdbUniseqWrSeed (%u, %u, %u, %u, %u);\n", Socket, Controller, Channel, Uniseq, Seed);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Uniseq >= MAX_NUMBER_DQDB_UNISEQS) ||
      (Seed > MAX_DQDB_UNISEQ_SEED_VAL) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  MrcHalProgramLfsr (MrcData, Channel, (UINT32 *) &Seed, Uniseq, 1, MrcHalSelectPatternBufferWrite);
  return;
}

/**
  Function used to set the DqDB read unisequencer seed value.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      Uniseq     - Zero based DqDB unisequencer number.
  @param[in]      Seed       - DqDB write unisequencer seed value.  The value must be less than or equal to the MaxDqdbUniseqSeedVal value from the GetCpgcInfo() function.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetDqdbUniseqRdSeed) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Uniseq,
  UINT32                Seed
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetDqdbUniseqRdSeed (%u, %u, %u, %u, %u);\n", Socket, Controller, Channel, Uniseq, Seed);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Uniseq >= MAX_NUMBER_DQDB_UNISEQS) ||
      (Seed > MAX_DQDB_UNISEQ_SEED_VAL) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  MrcHalProgramLfsr (MrcData, Channel, (UINT32 *) &Seed, Uniseq, 1, MrcHalSelectPatternBufferRead);
  return;
}

/**
  Function used to get the DqDB write unisequencer seed value.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      Uniseq     - Zero based DqDB unisequencer number.
  @param[out]     Seed       - Pointer to where the DqDB write unisequencer seed value will be stored.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientGetDqdbUniseqWrSeed) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Uniseq,
  UINT32                *Seed
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Uniseq >= MAX_NUMBER_DQDB_UNISEQS) ||
      (Seed != NULL) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  *Seed = MrcHalGetRegReutChPatWdbClMuxPbWr (MrcData, Channel, Uniseq);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetDqdbUniseqWrSeed (%u, %u, %u, %u, %u);\n", Socket, Controller, Channel, Uniseq, *Seed);
  return;
}

/**
  Function used to get the DqDB read unisequencer seed value.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      Uniseq     - Zero based DqDB unisequencer number.
  @param[out]     Seed       - Pointer to where the DqDB read unisequencer seed value will be stored.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientGetDqdbUniseqRdSeed) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Uniseq,
  UINT32                *Seed
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Uniseq >= MAX_NUMBER_DQDB_UNISEQS) ||
      (Seed != NULL) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  *Seed = MrcHalGetRegReutChPatWdbClMuxPbRd (MrcData, Channel, Uniseq);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetDqdbUniseqRdSeed (%u, %u, %u, %u, %u);\n", Socket, Controller, Channel, Uniseq, *Seed);
  return;
}

/**
  Function used to set the DqDB unisequencer L/M/N values.

  @param[in, out] This            - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket          - Zero based CPU socket number.
  @param[in]      Controller      - Zero based controller number.
  @param[in]      Channel         - Zero based channel number.
  @param[in]      Uniseq          - DqDB unisequencer mode.
  @param[in]      L               - DqDB unisequencer L counter value.  The value must be less than or equal to the MaxDqdbUniseqLVal value from the GetCpgcInfo() function.
  @param[in]      M               - DqDB unisequencer M counter value.  The value must be less than or equal to the MaxDqdbUniseqMVal value from the GetCpgcInfo() function.
  @param[in]      N               - DqDB unisequencer N counter value.  The value must be less than or equal to the MaxDqdbUniseqNVal value from the GetCpgcInfo() function.
  @param[in]      LDataSel        - DqDB unisequencer L data select value.  The value must be 0 or 1.
  @param[in]      EnableFreqSweep - Enables the Frequency Sweep feature.

  @retval NotAvailable if the LMN mode is not available on the given Uniseq.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetDqdbUniseqLmn) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Uniseq,
  UINT16                L,
  UINT16                M,
  UINT16                N,
  UINT8                 LDataSel,
  BOOLEAN               EnableFreqSweep
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetDqdbUniseqLmn (%u, %u, %u, %u, 0x%X, 0x%X, 0x%X, 0x%X, %u);\n", Socket, Controller, Channel, Uniseq, L, M, N, LDataSel, EnableFreqSweep);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((L > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_L_counter_MAX) ||
      (M > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_M_counter_MAX) ||
      (N > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_N_counter_MAX) ||
      (EnableFreqSweep > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_Enable_Sweep_Frequency_MAX) ||
      (LDataSel > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_L_data_select_MAX)) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    MrcHalProgramLmnMux (MrcData, Channel, L, M, N, LDataSel, EnableFreqSweep);
  }
  return (SsaStatus);
}

/**
  Function used to set the DqDB unisequencer LFSR configuration.

  @param[in, out] This            - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket          - Zero based CPU socket number.
  @param[in]      Controller      - Zero based controller number.
  @param[in]      Channel         - Zero based channel number.
  @param[in]      ReloadRate      - DqDB unisequencer LFSR seed reload rate.  The value must be less than or equal to the MaxDqdbUniseqSeedReloadRateVal value from the GetCpgcInfo() function.
  @param[in]      SaveRate        - DqDB unisequencer LFSR seed save rate.  The value must be less than or equal to the MaxDqdbUniseqSeedSaveRateVal value from the GetCpgcInfo() function.
  @param[in]      LfsrMode        - LFSR mode.
  @param[in]      EnableChaining  - If TRUE then the LFSR seeds will be chained causing wrap of LFSR[n] to increase the seed of LFSR[n+2], LFSR[0] is not incremented due to wrap.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetDqdbUniseqLfsrConfig) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 ReloadRate,
  UINT8                 SaveRate,
  DQDB_LFSR_MODE        LfsrMode,
  BOOLEAN               EnableChaining
  )
{
  const MRC_FUNCTION *MrcCall;
  MrcParameters      *MrcData;
  UINT32             Mux[MAX_NUMBER_DQDB_UNISEQS];

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (
    &MrcData->Outputs.Debug,
    MSG_LEVEL_NOTE,
    "SetDqdbUniseqLfsrConfig (%u, %u, %u, %u, %u, %u, %u);\n",
    Socket,
    Controller,
    Channel,
    ReloadRate,
    SaveRate,
    LfsrMode,
    EnableChaining
    );
#ifdef SSA_PARAM_ERROR_CHECK
  if ((ReloadRate > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_Reload_LFSR_Seed_Rate_MAX) ||
      (SaveRate > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_Save_LFSR_Seed_Rate_MAX) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  MrcCall = MrcData->Inputs.Call.Func;
  MrcCall->MrcSetMemDword ((UINT32 *) &Mux[0], sizeof (Mux) / sizeof (Mux[0]), MRC_IGNORE_ARG);
  MrcHalRmwWdbPatternMuxControl (
    MrcData,
    Channel,
    (MRC_HAL_ENUM_MUX_CONTROL *) &Mux[0],
    sizeof (Mux) / sizeof (Mux[0]),
    (MRC_HAL_ENUM_LFSR_TYPE) LfsrMode,
    (MRC_HAL_ENUM_LFSR_CHAINING_CONTROL) EnableChaining,
    MrcHalEccReplaceByteIgnoreArg,
    MrcHalEccDataSourceSelectIgnoreArg,
    (UINT32) SaveRate,
    (UINT32) ReloadRate,
    MrcHalSeedRateModeIgnoreArg
    );
  return;
}

/**
  Function used to set the DqDB Invert/DC configuration.

  @param[in, out] This              - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket            - Zero based CPU socket number.
  @param[in]      Controller        - Zero based controller number.
  @param[in]      Channel           - Zero based channel number.
  @param[in]      LaneMasks         - Pointer to array of lane bitmasks.  The number of array elements is the BusWidth value from the GetSystemInfo() function divided by 8.  Bit value 1 = participate in the Invert/DC feature; bit value 0 = do not participate in the Invert/DC feature.  If all lane bitmasks are 0 then the feature is disabled.
  @param[in]      Mode              - Invert/DC mode.
  @param[in]      DcPolarity        - DC polarity (when operating in the DC mode). 0 = DC low. 1 = DC high.
  @param[in]      ShiftRateExponent - Exponent of the bitmask shift rate.  The value must be less than or equal to the MaxDqdbInvertDcShiftRateExponentVal value from the GetCpgcInfo() function.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetDqdbInvertDcConfig) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  CONST UINT8           *LaneMasks,
  INVERT_DC_MODE        Mode,
  UINT8                 DcPolarity,
  UINT8                 ShiftRateExponent
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetDqdbInvertDcConfig (%u, %u, %u, %X, %u, %u, %u);\n", Socket, Controller, Channel, LaneMasks, Mode, DcPolarity, ShiftRateExponent);
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) LaneMasks, 64 / 8);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((LaneMasks != NULL) ||
      (Mode >= InvertDcModeMax) ||
      (DcPolarity > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_INV_DC_Polarity_Control_MAX) ||
      (ShiftRateExponent > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_INV_Inv_or_DC_Shift_Rate_MAX) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  MrcHalSetRegReutChPatWdbDataInv (MrcData, Channel, *((UINT64 *) LaneMasks));
  MrcHalProgramDqDbInvertDc (
    MrcData,
    Channel,
    (MRC_HAL_ENUM_INV_OR_DC_CONTROL) Mode,
    (MRC_HAL_ENUM_DC_POLARITY_CONTROL) DcPolarity,
    ShiftRateExponent
    );
  return;
}

/**
  This function sets the given channels CADB pattern generation mode to the given value.  The default value is NormalCadbMode.

  @param[in, out] This                   - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket                 - Zero based CPU socket number.
  @param[in]      Controller             - Zero based controller number.
  @param[in]      Channel                - Zero based channel number.
  @param[in]      EnableAlwaysOn         - Specifies whether CADB patterns will be driven out on all command and address pins every Dclk while a test is running.
  @param[in]      EnableOnDeselect       - Specifies whether CADB patterns will be driven out during deselect packets.
  @param[in]      CmdDeselectStartMask   - Provides a per command mechanism to enable driving CADB patterns during deselect cycles.  This parameter only applies if the EnableOnDeselect parameter is TRUE.  Bit 0 = 1: Start driving CADB patterns during deselects on the cycle following a WR CMD.  Bit 1 = 1: Start driving CADB patterns during deselects on the cycle following a RD CMD.  Bit 2 = 1: Start driving CADB patterns during deselects on the cycle following a ACT CMD.  Bit 3 = 1: Start driving CADB patterns during deselects on the cycle following a PRE CMD.
  @param[in]      CmdDeselectStopMask    - Provides a per command mechanism to disable driving CADB patterns during deselect cycles.  This parameter only applies if the EnableOnDeselect parameter is TRUE.  Bit 0 = 1: Stop driving CADB patterns during deselects on the cycle following a WR CMD.  Bit 1 = 1: Stop driving CADB patterns during deselects on the cycle following a RD CMD.  Bit 2 = 1: Stop driving CADB patterns during deselects on the cycle following a ACT CMD.  Bit 3 = 1: Stop driving CADB patterns during deselects on the cycle following a PRE CMD.
  @param[in]      LaneDeselectMask       - Specifies which lanes will have CADB patterns driven on deselects.  This parameter only applies if the EnableOnDeselect parameter is TRUE.  Bit 0 = 1: Drive CADB patterns on deselects on MA.  Bit 1 = 1: Drive CADB patterns on deselects on BA.  Bit 2 = 1: Drive CADB patterns on deselects on CMD.  Bit 3 = 1: Drive CADB patterns on deselects on CS.
  @param[in]      CasSelectMask          - Provides a per signal group mechanism to enable driving CADB patterns during CAS CMD select cycles.  Bit 0 = 1: Drive CADB patterns during an CAS on MA [11] and MA [9:3].  Bit 1 = 1: Drive CADB patterns during an CAS on BA.
  @param[in]      ActSelectMask          - Provides a per signal group mechanism to enable driving CADB patterns during ACT CMD select cycles.  Bit 0 = 1: Drive CADB patterns during an ACT on MA.  Bit 1 = 1: Drive CADB patterns during an ACT on BA.
  @param[in]      PreSelectMask          - Provides a per signal group mechanism to enable driving CADB patterns during PRE CMD select cycles.  Bit 0 = 1: Drive CADB patterns during an PRE on MA except AP bit.  Bit 1 = 1: Drive CADB patterns during an PRE on BA.
  @param[in]      SaveCurrentSeedMask    - Provides a per command mechanism to saving the current CADB seed to the starting seed.  Bit 0 = 1: Save the current CADB seed to the starting seed on a WR CMD.  Bit 1 = 1: Save the current CADB seed to the starting seed on a RD CMD.  Bit 2 = 1: Save the current CADB seed to the starting seed on a ACT CMD.  Bit 3 = 1: Save the current CADB seed to the starting seed on a PRE CMD.
  @param[in]      ReloadStartingSeedMask - Provides a per command mechanism to reloading the starting CADB seed to the current seed.  Bit 0 = 1: Reload the starting CADB seed to the current seed on a WR CMD.  Bit 1 = 1: Reload the starting CADB seed to the current seed on a RD CMD.  Bit 2 = 1: Reload the starting CADB seed to the current seed on a ACT CMD.  Bit 3 = 1: Reload the starting CADB seed to the current seed on a PRE CMD.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetCadbConfig) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  BOOLEAN               EnableAlwaysOn,
  BOOLEAN               EnableOnDeselect,
  UINT8                 CmdDeselectStartMask,
  UINT8                 CmdDeselectStopMask,
  UINT8                 LaneDeselectMask,
  UINT8                 CasSelectMask,
  UINT8                 ActSelectMask,
  UINT8                 PreSelectMask,
  UINT8                 SaveCurrentSeedMask,
  UINT8                 ReloadStartingSeedMask
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG ( &MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetCadbConfig (%u, %u, %u, %u, %u, ", Socket, Controller, Channel, EnableAlwaysOn, EnableOnDeselect );
  SSA_DEBUG_MSG ( &MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "%X, %X, %X, %X, ", CmdDeselectStartMask, CmdDeselectStopMask, LaneDeselectMask, CasSelectMask);
  SSA_DEBUG_MSG ( &MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "%X, %X, %X, %X);\n", ActSelectMask, PreSelectMask, SaveCurrentSeedMask, ReloadStartingSeedMask );
#ifdef SSA_PARAM_ERROR_CHECK
  if (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel)) {
    return;
  }
#endif
  MrcHalRmwCadbPatternControl (
    MrcData,
    Channel,
    (MRC_HAL_ENUM_CADB_ON_DESELECT_CONTROL) EnableOnDeselect,
    (MRC_HAL_ENUM_CADB_ALWAYS_ON_CONTROL) EnableAlwaysOn,
    (MRC_HAL_ENUM_CMD_DESELECT_CONTROL) CmdDeselectStartMask,
    (MRC_HAL_ENUM_CMD_DESELECT_CONTROL) CmdDeselectStopMask,
    (MRC_HAL_ENUM_LANE_DESELECT_CONTROL) LaneDeselectMask,
    (MRC_HAL_ENUM_CAS_SELECT_CONTROL) CasSelectMask,
    (MRC_HAL_ENUM_ACT_SELECT_CONTROL) ActSelectMask,
    (MRC_HAL_ENUM_PRE_SELECT_CONTROL) PreSelectMask,
    (MRC_HAL_ENUM_SAVE_SEED_CONTROL) SaveCurrentSeedMask,
    (MRC_HAL_ENUM_RELOAD_SEED_CONTROL) ReloadStartingSeedMask
    );
  return;
}

/**
  Function used to write to the CADB.

  @param[in, out] This          - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      Pattern       - Pointer to buffer containing the CADB pattern.
  @param[in]      RowCount      - Size of the buffer pattern in term of the count of rows.  Each row has 2 UINT32 elements.
  @param[in]      StartRowIndex - Start offset on the CADB.  The sum of the RowCount and StartRowIndex values must be less than or equal to the MaxNumberCadbRows value from the GetCpgcInfo() function.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetCadbPattern) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  CONST UINT64          *Pattern,
  UINT8                 RowCount,
  UINT8                 StartRowIndex
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetCadbPattern (%u, %u, %u %u %u);\n", Socket, Controller, Channel, RowCount, StartRowIndex);
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) Pattern, RowCount * sizeof (UINT64));
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Pattern == NULL) ||
      (RowCount == 0) ||
      (RowCount > MAX_NUMBER_CADB_ROWS) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  MrcHalRmwCadbPatternBufferInit (MrcData, Channel, (const UINT64_STRUCT *) Pattern, RowCount, StartRowIndex);
  return;
}

/**
  Function used to set the CADB unisequencer modes.

  @param[in, out] This         - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket       - Zero based CPU socket number.
  @param[in]      Controller   - Zero based controller number.
  @param[in]      Channel      - Zero based channel number.
  @param[in]      Uniseq       - Zero based CADB unisequencer number.
  @param[in]      DeselectMode - CADB deselect cycle unisequencer mode.  The value must be less than or equal to the MaxCadbUniseqSeedVal value from the GetCpgcInfo() function.
  @param[in]      SelectMode   - CADB select cycle unisequencer mode.  The value must be less than or equal to the MaxCadbUniseqSeedVal value from the GetCpgcInfo() function.

  @retval NotAvailable if the given DeselectMode or SelectMode value is not available on the given Uniseq.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetCadbUniseqMode) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Uniseq,
  CADB_UNISEQ_MODE      DeselectMode,
  CADB_UNISEQ_MODE      SelectMode
  )
{
  MrcParameters      *MrcData;
  const MRC_FUNCTION *MrcCall;
  SSA_STATUS         SsaStatus;
  UINT32             Select[MAX_NUMBER_CADB_UNISEQS];
  UINT32             Deselect[MAX_NUMBER_CADB_UNISEQS];

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetCadbUniseqMode (%u, %u, %u, %u, %u %u);\n", Socket, Controller, Channel, Uniseq, DeselectMode, SelectMode);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Uniseq >= MAX_NUMBER_CADB_UNISEQS) ||
      (DeselectMode >= CadbUniseqModeMax) ||
      (SelectMode >= CadbUniseqModeMax)) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    MrcCall = MrcData->Inputs.Call.Func;
    MrcCall->MrcSetMemDword ((UINT32 *) &Select[0], sizeof (Select) / sizeof (Select[0]), MRC_IGNORE_ARG);
    MrcCall->MrcSetMemDword ((UINT32 *) &Deselect[0], sizeof (Deselect) / sizeof (Deselect[0]), MRC_IGNORE_ARG);
    Deselect[Uniseq] = DeselectMode;
    Select[Uniseq]   = SelectMode;
    MrcHalRmwCadbPatternMuxControl (
      MrcData,
      Channel,
      (MRC_HAL_ENUM_MUX_CONTROL *) &Deselect[0],
      sizeof (Deselect) / sizeof (Deselect[0]),
      (MRC_HAL_ENUM_MUX_CONTROL *) &Select[0],
      sizeof (Select) / sizeof (Select[0]),
      MrcHalLfsrTypeIgnoreArg,
      MrcHalLfsrChainingIgnoreArg
      );
  }
  return (SsaStatus);
}

/**
  Function used to set the CADB unisequencer seed values.

  @param[in, out] This         - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket       - Zero based CPU socket number.
  @param[in]      Controller   - Zero based controller number.
  @param[in]      Channel      - Zero based channel number.
  @param[in]      Uniseq       - Zero based CADB unisequencer number.
  @param[in]      DeselectSeed - CADB deselect cycle unisequencer seed value.The value must be less than or equal to the MaxCadbUniseqSeedVal value from the GetCpgcInfo() function.
  @param[in]      SelectSeed   - CADB select cycle unisequencer seed value.The value must be less than or equal to the MaxCadbUniseqSeedVal value from the GetCpgcInfo() function.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetCadbUniseqSeed) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Uniseq,
  UINT32                DeselectSeed,
  UINT32                SelectSeed
  )
{
  MrcParameters      *MrcData;
  const MRC_FUNCTION *MrcCall;
  UINT32             Select[MAX_NUMBER_CADB_UNISEQ_SEED];
  UINT32             Deselect[MAX_NUMBER_CADB_UNISEQ_SEED];

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetCadbUniseqSeed (%u, %u, %u, %u, %u %u);\n", Socket, Controller, Channel, Uniseq, DeselectSeed, SelectSeed);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Uniseq >= MAX_NUMBER_CADB_UNISEQS) ||
      (DeselectSeed >= CadbUniseqModeMax) ||
      (SelectSeed >= CadbUniseqModeMax) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  MrcCall = MrcData->Inputs.Call.Func;
  MrcCall->MrcSetMemDword ((UINT32 *) &Select[0], sizeof (Select) / sizeof (Select[0]), MRC_IGNORE_ARG);
  MrcCall->MrcSetMemDword ((UINT32 *) &Deselect[0], sizeof (Deselect) / sizeof (Deselect[0]), MRC_IGNORE_ARG);
  Deselect[Uniseq] = DeselectSeed;
  Select[Uniseq]   = SelectSeed;
  MrcHalSetCadbMuxPatternBuffer (MrcData, Channel, (UINT32 *) &Deselect[0], sizeof (Deselect) / sizeof (Deselect[0]));
  MrcHalSetCadbSelMuxPatternBuffer (MrcData, Channel, (UINT32 *) &Select[0], sizeof (Select) / sizeof (Select[0]));
  return;
}

/**
  Function used to set the CADB unisequencer L/M/N values.

  @param[in, out] This            - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket          - Zero based CPU socket number.
  @param[in]      Controller      - Zero based controller number.
  @param[in]      Channel         - Zero based channel number.
  @param[in]      Uniseq          - Zero based CADB unisequencer number.
  @param[in]      L               - CADB unisequencer L counter value.  The value must be less than or equal to the MaxCadbUniseqLVal value from the GetCpgcInfo() function.
  @param[in]      M               - CADB unisequencer M counter value.  The value must be less than or equal to the MaxCadbUniseqMVal value from the GetCpgcInfo() function.
  @param[in]      N               - CADB unisequencer N counter value.  The value must be less than or equal to the MaxCadbUniseqNVal value from the GetCpgcInfo() function.
  @param[in]      LDataSel        - CADB unisequencer L data select value.  The value must be 0 or 1.
  @param[in]      EnableFreqSweep - Enables LMN frequency sweep feature.

  @retval NotAvailable if the LMN mode is not available on the given Uniseq.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetCadbUniseqLmn) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Uniseq,
  UINT16                L,
  UINT16                M,
  UINT16                N,
  UINT8                 LDataSel,
  BOOLEAN               EnableFreqSweep
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetCadbUniseqLmn (%u, %u, %u, %u, 0x%X, 0x%X, 0x%X, 0x%X, %u);\n", Socket, Controller, Channel, Uniseq, L, M, N, LDataSel, EnableFreqSweep);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((L > MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_L_counter_MAX) ||
      (M > MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_M_counter_MAX) ||
      (N > MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_N_counter_MAX) ||
      (EnableFreqSweep > MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_Enable_Sweep_Frequency_MAX) ||
      (LDataSel > MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_L_data_select_MAX)) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    MrcHalSetCadbClMuxLmn (
      MrcData,
      Channel,
      (MRC_HAL_ENUM_L_DATA_SELECT) LDataSel,
      (MRC_HAL_ENUM_ENABLE_SWEEP_FREQ) EnableFreqSweep,
      L,
      M,
      N
      );
  }
  return (SsaStatus);
}

/**
  Function used to set the Dummy Read LMN values.

  @param[in, out] This            - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket          - Zero based CPU socket number.
  @param[in]      Controller      - Zero based controller number.
  @param[in]      Channel         - Zero based channel number.
  @param[in]      L               - Dummy Read unisequencer L counter value.
  @param[in]      M               - Dummy Read unisequencer M counter value.
  @param[in]      N               - Dummy Read unisequencer N counter value.
  @param[in]      LDataSel        - Dummy Read unisequencer L data select value (0 or 1).
  @param[in]      EnableFreqSweep - Enables LMN frequency sweep feature.

  @retval NotAvailable if the system does not support the Dummy Read feature.  Else UnsupportedValue if the given L, M, N, or LDataSel values are out of range.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetDummyReadLmn) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT16                L,
  UINT16                M,
  UINT16                N,
  UINT8                 LDataSel,
  BOOLEAN               EnableFreqSweep
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetDummyReadLmn (%u, %u, %u, %u, 0x%X, 0x%X, 0x%X, 0x%X);\n", Socket, Controller, Channel, L, M, N, LDataSel, EnableFreqSweep);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((L > MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_0_L_counter_MAX) ||
      (M > MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_0_M_counter_MAX) ||
      (N > MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_0_N_Counter_MAX) ||
      (EnableFreqSweep > MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_0_Enable_Sweep_Frequency_MAX) ||
      (LDataSel > MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_0_L_DummyRead_Select_MAX)) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    MrcHalSetDummyReadControl (
      MrcData,
      Channel,
      (MRC_HAL_ENUM_L_DATA_SELECT) LDataSel,
      (MRC_HAL_ENUM_ENABLE_SWEEP_FREQ) EnableFreqSweep,
      L,
      M,
      N
      );
  }
  return (SsaStatus);
}

/**
  Function used to set the Dummy Read bank mask.

  @param[in, out] This            - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket          - Zero based CPU socket number.
  @param[in]      Controller      - Zero based controller number.
  @param[in]      Channel         - Zero based channel number.
  @param[in]      BankMask        - Dummy Read bank mask.

  @retval NotAvailable if the system does not support the Dummy Read feature.  Else UnsupportedValue if the given BankMask value is out of range.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetDummyReadBankMask) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT16                BankMask
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetDummyReadBankMask (%u, %u, %u, 0x%X);\n", Socket, Controller, Channel, BankMask);
#ifdef SSA_PARAM_ERROR_CHECK
  if (BankMask > MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_0_Dummy_Read_Bank_Mask_MAX) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    MrcHalRmwDummyReadRankBankMask (MrcData, Channel, MrcHalRankMaskIgnoreArg, (MRC_HAL_ENUM_BANK_MASK_CONTROL) BankMask);
  }
  return (SsaStatus);
}

/**
  Function used to set the Dummy Read ranks.

  @param[in, out] This          - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      DimmRankPairs - Array of DIMM and physical rank pair values.  If a DIMM/rank appears in the list, then the corresponding bit will be set to 1 in the rank mask.  If a DIMM/rank doesn't appear in the list then then the corresponding bit will be set to 0 in the rank mask.

  @retval NotAvailable if the system does not support the Dummy Read feature.  Else UnsupportedValue if the given PairCount or DimmRankPairs value is out of range.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetDummyReadRanks) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 PairCount,
  CONST DIMM_RANK_PAIR  *DimmRankPairs
  )
{
  MrcParameters        *MrcData;
  CONST DIMM_RANK_PAIR *DimmRankPtr;
  SSA_STATUS           SsaStatus;
  UINT32               LogicalRank;
  UINT32               PhysicalRank;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetDummyReadRanks (%u, %u, %u, %u);\n", Socket, Controller, Channel, PairCount);
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) DimmRankPairs, PairCount * sizeof (DIMM_RANK_PAIR));
#ifdef SSA_PARAM_ERROR_CHECK
  if ((PairCount == 0) ||
      (PairCount > MAX_NUMBER_RANK_MAP_ENTRIES) ||
      (DimmRankPairs != NULL)) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    DimmRankPtr = &DimmRankPairs[0];
    for (LogicalRank = 0; LogicalRank < PairCount; LogicalRank++, DimmRankPtr++) {
      PhysicalRank = (DimmRankPtr->Dimm * MAX_RANK_IN_DIMM) + DimmRankPtr->Rank;
      MrcHalSetLogicalToPhysicalRankMapping (MrcData, Channel, LogicalRank, PhysicalRank);
    }
  }
  return (SsaStatus);
}

/**
  Function used to set the subsequence configuration.

  @param[in, out] This                              - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket                            - Zero based CPU socket number.
  @param[in]      Controller                        - Zero based controller number.
  @param[in]      Channel                           - Zero based channel number.
  @param[in]      Subseq                            - Zero based subsequence number.  The value must be less than the MaxNumberSubseqs value from the GetCpgcInfo() function.
  @param[in]      BurstLengthMode,                  - Burst length mode.
  @param[in]      BurstLength                       - Burst length in cachelines.  If BurstLengthMode is ExponentialBurstLengthMode then the Burstlength value is an exponent and the value must be less than or equal to the MaxBurstLengthExponentVal value from the in GetCpgcInfo() function.  If BurstLengthMode is LinearBurstLengthMode then the Burstlength value is linear and the value must be less than or equal to the MaxBurstLengthLinearVal value from the in GetCpgcInfo() function.
  @param[in]      InterSubseqWait                   - Inter-subsequence wait in dclks.  The value must be less than or equal to the MaxInterSubseqWaitVal value from the GetCpgcinfo() function.
  @param[in]      SubseqType                        - Subsequence type.
  @param[in]      EnableSaveCurrentBaseAddrToStart  - Specifies whether the current base address is saved to the start address with this subsequence.
  @param[in]      EnableResetCurrentBaseAddrToStart - Specifies whether the current base address is reset to the start address with this subsequence.
  @param[in]      EnableAddrInversion               - Specifies whether address inversion enabled for this subsequence.
  @param[in]      EnableDataInversion               - Specifies whether data inversion enabled for this subsequence.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetSubseqConfig) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Subseq,
  BURST_LENGTH_MODE     BurstLengthMode,
  UINT32                BurstLength,
  UINT32                InterSubseqWait,
  SUBSEQ_TYPE           SubseqType,
  BOOLEAN               EnableSaveCurrentBaseAddrToStart,
  BOOLEAN               EnableResetCurrentBaseAddrToStart,
  BOOLEAN               EnableAddrInversion,
  BOOLEAN               EnableDataInversion
  )
{
  MrcParameters                      *MrcData;
  MRC_HAL_SUBSEQUENCE_CONTROL_STRUCT SubSeqCtl;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetSubseqConfig (%u, %u, %u, %u %u %u, ", Socket, Controller, Channel, Subseq, BurstLengthMode, BurstLength);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "%u, %u, %u, %u %u %u);\n", InterSubseqWait, SubseqType, EnableSaveCurrentBaseAddrToStart, EnableResetCurrentBaseAddrToStart, EnableAddrInversion, EnableDataInversion);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Subseq >= MAX_NUMBER_SUBSEQS) ||
      mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel)) {
    return;
  }
#endif
  {
    SubSeqCtl.NumberofCachelines               = (UINT8) BurstLength;
    SubSeqCtl.NumberofCachelinesScale          = BurstLengthMode;
    SubSeqCtl.SubsequenceWait                  = (UINT16) InterSubseqWait;
    SubSeqCtl.SubsequenceType                  = SubseqType;
    SubSeqCtl.SaveCurrentBaseAddressToStart    = EnableSaveCurrentBaseAddrToStart;
    SubSeqCtl.ResetCurrentBaseAddressToStart   = EnableResetCurrentBaseAddrToStart;
    SubSeqCtl.DataandEccAddressInversion       = EnableAddrInversion;
    SubSeqCtl.InvertDataandEcc                 = EnableDataInversion;
    SubSeqCtl.StopBaseSubsequenceOnWrapTrigger = 0;
    MrcHalSetReutSubsequence (MrcData, Channel, Subseq, 1, &SubSeqCtl, (MRC_HAL_SUBSEQUENCE_OFFSET_STRUCT *) NULL);
  }
  return;
}

/**
  Function used to set the subsequence configuration.

  @param[in, out] This                   - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket                 - Zero based CPU socket number.
  @param[in]      Controller             - Zero based controller number.
  @param[in]      Channel                - Zero based channel number.
  @param[in]      Subseq                 - Zero based subsequence number.  The value must be less than the MaxNumberSubseqs value from the GetCpgcInfo() function.
  @param[in]      EnableBaseInvertData   - Specifies whether base inversion of the data is enabled.
  @param[in]      EnableRowIncrement     - Specifies whether row increment is enabled.
  @param[in]      RowIncrementOrder      - Specifies row increment order.  The value must be 0 or 1.
  @param[in]      EnableColIncrement     - Specifies whether column increment is enabled.
  @param[in]      ColIncrementOrder      - Specifies column increment order.  The value must be 0 or 1.
  @param[in]      EnableCadbSeedsSave    - Specifies whether saving the CADB seeds is enabled.
  @param[in]      EnableCadbSeedsRestore - Specifies whether restoring the CADB seeds is enabled.
  @param[in]      EnableCadbSelect       - Specifies whether CADB patterns will be driven during select cycles.
  @param[in]      EnableCadbDeselect     - Specifies whether CADB patterns will be driven during deselect cycles.
  @param[in]      BaseSubseqType         - Every time the BaseSubseqRepeatRate is reached a Read or Write is performed for one command based on the following fields: BaseSubseqType indicates whether a read (BaseReadSubseqType) or write (BaseWriteSubseqType) operation will occur at the current base address.  EnableBaseInvertData indicates whether the read or write (BaseSubseqType) operation at the current base address is inverted (EnableBaseInvertData = TRUE) or not (EnableBaseInvertData = FALSE).
  @param[in]      BaseSubseqRepeatRate   - Specifies how often the BaseSubseqType operation occurs for 1 cacheline.  0 = No BaseSubseqType cacheline operations will occur during the Offset_Read or Offset_Write.  1 = Reserved value.  2 = Repeat the BaseSubseqType cacheline operation after every offset cacheline operation.  ...  31 = Repeat the BaseSubseqType cacheline operation after 30 offset cacheline operations.
  @param[in]      OffsetAddrUpdateRate   - Specifies the rate that the Current Offset Address is updated.  The value must be less than or equal to the MaxOffsetAddrUpdateRateVal value from the GetCpgcInfo() function.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetSubseqOffsetConfig) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                     Socket,
  UINT8                     Controller,
  UINT8                     Channel,
  UINT8                     Subseq,
  BOOLEAN                   EnableBaseInvertData,
  BOOLEAN                   EnableRowIncrement,
  UINT8                     RowIncrementOrder,
  BOOLEAN                   EnableColIncrement,
  UINT8                     ColIncrementOrder,
  BOOLEAN                   EnableCadbSeedsSave,
  BOOLEAN                   EnableCadbSeedsRestore,
  BOOLEAN                   EnableCadbSelect,
  BOOLEAN                   EnableCadbDeselect,
  SUBSEQ_TYPE               BaseSubseqType,
  UINT32                    BaseSubseqRepeatRate,
  UINT32                    OffsetAddrUpdateRate
  )
{
  MrcParameters                     *MrcData;
  MRC_HAL_SUBSEQUENCE_OFFSET_STRUCT SubSeqOffset;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetSubseqOffsetConfig (%u, %u, %u, %u, %u, ", Socket, Controller, Channel, Subseq, EnableBaseInvertData);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "%u, %u, %u, %u, %u, %u, ", EnableRowIncrement, RowIncrementOrder, EnableColIncrement, ColIncrementOrder, EnableCadbSeedsSave, EnableCadbSeedsRestore);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "%u, %u, %u, %u, %u);\n", EnableCadbSelect, EnableCadbDeselect, BaseSubseqType, BaseSubseqRepeatRate, OffsetAddrUpdateRate);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Subseq >= MAX_NUMBER_SUBSEQS) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  {
    SubSeqOffset.OffsetAddressUpdateRate       = (UINT8) OffsetAddrUpdateRate;
    SubSeqOffset.BaseSubsequenceRepeatRate     = (UINT8) BaseSubseqRepeatRate;
    SubSeqOffset.ColumnOffsetWrapTriggerEnable = 0;
    SubSeqOffset.RowOffsetWrapTriggerEnable    = 0;
    SubSeqOffset.BaseSubsequenceType           = BaseSubseqType;
    SubSeqOffset.CadbDeselectEnable            = EnableCadbDeselect;
    SubSeqOffset.CadbSelectEnable              = EnableCadbSelect;
    SubSeqOffset.CadbSeedsSaveEnable           = EnableCadbSeedsSave;
    SubSeqOffset.ColumnIncrementOrder          = ColIncrementOrder;
    SubSeqOffset.CadbSeedsReloadEnable         = EnableCadbSeedsRestore;
    SubSeqOffset.ColumnIncrementEnable         = EnableColIncrement;
    SubSeqOffset.RowIncrementOrder             = RowIncrementOrder;
    SubSeqOffset.RowIncrementEnable            = EnableRowIncrement;
    SubSeqOffset.BaseInvertDataandEcc          = EnableBaseInvertData;
    MrcHalSetReutSubsequence (MrcData, Channel, Subseq, 1, (MRC_HAL_SUBSEQUENCE_CONTROL_STRUCT *) NULL, &SubSeqOffset);
  }
  return;
}

/**
  Function used to set the loop count.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      LoopCount  - Specifies how many iterations of the complete sequence loop takes place before a test stops, where a sequence loop is defined by the completion of all subsequences indicated by the SubseqStartIndex to SubseqEndIndex. The value must be less than or equal to the MaxLoopCountVal from the GetCpgcInfo() function.  If the IsLoopCountExponential value from the GetCpgcInfo() function is TRUE then the number of loops is 2^(LoopCount-1).  If the IsLoopCountExponential value from the GetCpgcInfo() function is FALSE then the number of loops is simply LoopCount.  In both the linear of exponential cases, 0 is a special value means that the loop count is infinite.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetLoopCount) (
  struct _SSA_BIOS_SERVICES_PPI *This,
  UINT8                         Socket,
  UINT8                         Controller,
  UINT8                         Channel,
  UINT32                        LoopCount
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetLoopCount (%u, %u, %u, %u);\n", Socket, Controller, Channel, LoopCount);
#ifdef SSA_PARAM_ERROR_CHECK
  if (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel)) {
    return;
  }
#endif
  {
    MrcHalSetRegReutChSeqLoopcountLimitMcmain (MrcData, Channel, LoopCount);
  }
  return;
}

/**
  Function used to set the sequence configuration.

  @param[in, out] This                      - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket                    - Zero based CPU socket number.
  @param[in]      Controller                - Zero based controller number.
  @param[in]      Channel                   - Zero based channel number.
  @param[in]      StartDelay                - Specifies the delay period (in dclks) between the start of the test and the actual entry to Loopback.Pattern where the first SubSequence is executed immediately.  The value must be less than or equal to the MaxStartDelayVal value from the GetCpgcInfo() function.
  @param[in]      SubseqStartIndex          - Specifies the initial SubSequence pointer where a Sequence first enters Loopback.Pattern (start of test).  The value must be less than the MaxNumberSubseqs value from the GetCpgcInfo() function.
  @param[in]      SubseqEndIndex            - When the subsequence pointed to by the SubseqEndIndex is completed the loop count is incremented by 1 and the current subsequence index is reset to the SubseqStartIndex.  The SubseqEndIndex must be greater than or equal to the SubseqStartIndex value.  The value must be less than the MaxNumberSubseqs value from the GetCpgcInfo() function.
  @param[in]      LoopCount                 - Specifies how many iterations of the complete sequence loop takes place before a test stops, where a sequence loop is defined by the completion of all subsequences indicated by the SubseqStartIndex to SubseqEndIndex. The value must be less than or equal to the MaxLoopCountVal from the GetCpgcInfo() function.  If the IsLoopCountExponential value from the GetCpgcInfo() function is TRUE then the number of loops is 2^(LoopCount-1).  If the IsLoopCountExponential value from the GetCpgcInfo() function is FALSE then the number of loops is simply LoopCount.  In both the linear of exponential cases, 0 is a special value means that the loop count is infinite.
  @param[in]      InitMode                  - Initialization mode.
  @param[in]      EnableGlobalControl       - Specifies whether global control is enabled for the given channel.
  @param[in]      EnableConstantWriteStrobe - Specifies whether constant write strobe is enabled.
  @param[in]      EnableDummyReads          - Specifies whether dummy reads are enabled.
  @param[in]      AddrUpdateRateMode        - Address update rate mode.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetSeqConfig) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT32                StartDelay,
  UINT8                 SubseqStartIndex,
  UINT8                 SubseqEndIndex,
  UINT32                LoopCount,
  CPGC_INIT_MODE        InitMode,
  BOOLEAN               EnableGlobalControl,
  BOOLEAN               EnableConstantWriteStrobe,
  BOOLEAN               EnableDummyReads,
  ADDR_UPDATE_RATE_MODE AddrUpdateRateMode
  )
{
  MrcParameters *MrcData;
  MRC_HAL_SEQUENCE_CONFIG_STRUCT SeqConfig;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetSeqConfig (%u, %u, %u, %u, ", Socket, Controller, Channel, StartDelay);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "%u, %u, %u, %u, ", SubseqStartIndex, SubseqEndIndex, LoopCount, InitMode);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "%u, %u, %u, %u);\n", InitMode, EnableGlobalControl, EnableConstantWriteStrobe, EnableDummyReads);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((0) ||
      mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel)) {
    return;
  }
#endif
  {
    SeqConfig.StopBaseSequenceOnWrapTrigger   = MrcHalSequenceWrapIgnoreArg;
    SeqConfig.AddressUpdateRateMode           = (MRC_HAL_ENUM_ADDRESS_UPDATE_RATE_CONTROL) AddrUpdateRateMode;
    SeqConfig.EnableDummyReads                = (MRC_HAL_ENUM_DUMMY_READ_CONTROL) EnableDummyReads;
    SeqConfig.ReutAllowOppRefresh             = MrcHalOpportunisticRefreshIgnoreArg;
    SeqConfig.GlobalControl                   = (MRC_HAL_ENUM_GLOBAL_CONTROL) EnableGlobalControl;
    SeqConfig.InitializationMode              = (MRC_HAL_ENUM_INITIALIZATION_MODE) InitMode;
    SeqConfig.SubsequenceStartPointer         = (MRC_HAL_ENUM_SUBSEQUENCE_POINTER_VALUE) SubseqStartIndex;
    SeqConfig.SubsequenceEndPointer           = (MRC_HAL_ENUM_SUBSEQUENCE_POINTER_VALUE) SubseqEndIndex;
    SeqConfig.StartTestDelay                  = StartDelay;
    SeqConfig.SubSequenceCachelineCounterMode = MrcHalCachelineCounterIgnoreArg;
    MrcHalSetReutSequenceConfig (MrcData, Channel, &SeqConfig);
    BiosClientSetLoopCount (This, Socket, Controller, Channel, LoopCount);
  }
  return;
}

/**
  Function used to set the sequence address configuration.

  @param[in, out] This                 - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket               - Zero based CPU socket number.
  @param[in]      Controller           - Zero based controller number.
  @param[in]      Channel              - Zero based channel number.
  @param[in]      EnableRankWrapCarry  - If a base rank address wrap occurs  and EnableRankWrapCarry is set to TRUE then a carry increment or decrement from the rank address (order N) will propagate to the N+1 order address field(s).
  @param[in]      EnableBankWrapCarry  - If a base bank address wrap occurs  and EnableBankWrapCarry is set to TRUE then a carry increment or decrement from the bank address (order N) will propagate to the N+1 order address field(s).
  @param[in]      EnableRowWrapCarry   - If a base row address wrap occurs and EnableRowWrapCarry is set to TRUE then a carry increment or decrement from the row address (order N) will propagate to the N+1 order address field(s).
  @param[in]      EnableColWrapCarry   - If a base column address wrap occurs  and EnableColWrapCarry is set to TRUE then a carry increment or decrement from the column address (order N) will propagate to the N+1 order address field(s).
  @param[in]      EnableRankAddrInvert - Setting to TRUE will cause the current rank address to be inverted with the periodicity described by the AddrInvertRate parameter.
  @param[in]      EnableBankAddrInvert - Setting to TRUE will cause the current bank address to be inverted with the periodicity described by the AddrInvertRate parameter.
  @param[in]      EnableRowAddrInvert  - Setting to TRUE will cause the current row address to be inverted with the periodicity described by the AddrInvertRate parameter.
  @param[in]      EnableColAddrInvert  - Setting to TRUE will cause the current column address to be inverted with the periodicity described by the AddrInvertRate parameter.
  @param[in]      AddrInvertRate       - Base address inversion rate.  The SetSeqConfig() function's AddrUpdateRateMode parameter specifies whether the base address inversion logic is based on number of cachelines written and read or on the number of sequences performed.  If AddrUpdateRateMode from the SetSeqConfig() function is CachelineAddrUpdateRate then the current base address is inverted based on 2^AddrInvertRate read and write cacheline transactions.  If AddrUpdateRateMode from the SetSeqConfig() function is LoopCountAddrUpdateRate then the current base address is inverted based on 2^AddrInvertRate loops through the sequence.  The value must be less than or equal to the MaxAddrInvertRateVal value from the GetCpgcInfo() function.
  @param[in]      RankAddrOrder        - Specifies the relative ordering of the rank address update logic in the nested for loop in relation to the bank, row, and column address update logic.  Any address fields set to the same order that roll over will cause a distinct carry of +1 or -1 to the next higher order address field (multiple simultaneous carries will cause only one increment/decrement).  All fields can be arbitrarily placed in any order as long as all address order fields are set in a continuous order starting from 0 and may not skip over an order number.  Example: setting 0,1,2,1 in the 4 fields (Col,Row,Bank,Rank) is legal; setting 0,2,2,3 is illegal (not continuous).  The value must be less than or equal to 3.
  @param[in]      BankAddrOrder        - Specifies the relative ordering of the bank address update logic in the nested for loop in relation to the rank, row, and column address update logic.  The value must be less than or equal to 3.
  @param[in]      RowAddrOrder         - Specifies the relative ordering of the row address update logic in the nested for loop in relation to the rank, bank, and column address update logic.  The value must be less than or equal to 3.
  @param[in]      ColAddrOrder         - Specifies the relative ordering of the column address update logic in the nested for loop in relation to the rank, bank, and row address update logic.  The value must be less than or equal to 3.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetSeqAddrConfig) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  BOOLEAN               EnableRankWrapCarry,
  BOOLEAN               EnableBankWrapCarry,
  BOOLEAN               EnableRowWrapCarry,
  BOOLEAN               EnableColWrapCarry,
  BOOLEAN               EnableRankAddrInvert,
  BOOLEAN               EnableBankAddrInvert,
  BOOLEAN               EnableRowAddrInvert,
  BOOLEAN               EnableColAddrInvert,
  UINT8                 AddrInvertRate,
  UINT8                 RankAddrOrder,
  UINT8                 BankAddrOrder,
  UINT8                 RowAddrOrder,
  UINT8                 ColAddrOrder
  )
{
  MrcParameters                  *MrcData;
  MRC_HAL_REUT_BASE_ADDR_OCI_CTL AddrOciCtl[MrcHalAddressSelectMax];
  MRC_HAL_REUT_BASE_ADDR_OCI_CTL *AddrOciCtlPtr;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetSeqAddrConfig (%u, %u, %u, ", Socket, Controller, Channel);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "%u, %u, %u, %u, ", EnableRankWrapCarry, EnableBankWrapCarry, EnableRowWrapCarry, EnableColWrapCarry);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "%u, %u, %u, %u, ", EnableRankAddrInvert, EnableBankAddrInvert, EnableRowAddrInvert, EnableColAddrInvert);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "%u, %u, %u, %u, %u);\n",  AddrInvertRate, RankAddrOrder, BankAddrOrder, RowAddrOrder, ColAddrOrder);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((0) ||
      mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel)) {
    return;
  }
#endif
  {
    AddrOciCtlPtr                = AddrOciCtl;
    AddrOciCtlPtr->Order         = RankAddrOrder;
    AddrOciCtlPtr->InvertEnable  = (MRC_HAL_ENUM_ADDRESS_INVERT_CONTROL) EnableRankAddrInvert;
    AddrOciCtlPtr->TriggerEnable = (MRC_HAL_ENUM_ADDRESS_WRAP_TRIGGER) MrcHalAddressWrapTriggerDisable;
    AddrOciCtlPtr->CarryEnable   = (MRC_HAL_ENUM_ADDRESS_WRAP_CARRY) EnableRankWrapCarry;

    AddrOciCtlPtr++;
    AddrOciCtlPtr->Order         = BankAddrOrder;
    AddrOciCtlPtr->InvertEnable  = (MRC_HAL_ENUM_ADDRESS_INVERT_CONTROL) EnableBankAddrInvert;
    AddrOciCtlPtr->TriggerEnable = (MRC_HAL_ENUM_ADDRESS_WRAP_TRIGGER) MrcHalAddressWrapTriggerDisable;
    AddrOciCtlPtr->CarryEnable   = (MRC_HAL_ENUM_ADDRESS_WRAP_CARRY) EnableBankWrapCarry;

    AddrOciCtlPtr++;
    AddrOciCtlPtr->Order         = RowAddrOrder;
    AddrOciCtlPtr->InvertEnable  = (MRC_HAL_ENUM_ADDRESS_INVERT_CONTROL) EnableRowAddrInvert;
    AddrOciCtlPtr->TriggerEnable = (MRC_HAL_ENUM_ADDRESS_WRAP_TRIGGER) MrcHalAddressWrapTriggerDisable;
    AddrOciCtlPtr->CarryEnable   = (MRC_HAL_ENUM_ADDRESS_WRAP_CARRY) EnableRowWrapCarry;

    AddrOciCtlPtr++;
    AddrOciCtlPtr->Order         = ColAddrOrder;
    AddrOciCtlPtr->InvertEnable  = (MRC_HAL_ENUM_ADDRESS_INVERT_CONTROL) EnableColAddrInvert;
    AddrOciCtlPtr->TriggerEnable = (MRC_HAL_ENUM_ADDRESS_WRAP_TRIGGER) MrcHalAddressWrapTriggerDisable;
    AddrOciCtlPtr->CarryEnable   = (MRC_HAL_ENUM_ADDRESS_WRAP_CARRY) EnableColWrapCarry;

    MrcHalSetReutChSeqBaseAddrOciCtl (MrcData, Channel, AddrInvertRate, MrcHalAddressSelectMax, AddrOciCtl);
  }
  return;
}

/**
  Function used to set the sequence start address.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      RankAddr   - Rank start address.  This value is the index into the CPGC rank map (see the SetSeqRankMap() function).  The value must be less than the MaxNumberRankMapEntries value from the GetCpgcInfo() function.
  @param[in]      BankAddr   - Bank start address.  If the CPGC engine supports a bank map (i.e., the MaxNumberBankMapEntried value from the GetCpgcInfo() function is greater than 0) then this value is is the index into the CPGC bank map (see the SetSeqBankMap() function) and the value must be less than the MaxNumberBankMapEntried value from the GetCpgcInfo() function.  If the CPGC engine does not support a bank map then the value must be less than the BankCount value from the GetDimmInfo function for the DIMMs that will be tested.
  @param[in]      RowAddr    - Row start address.  The value must be less than the RowSize value from the GetDimmInfo function for the DIMMs that will be tested.
  @param[in]      ColAddr    - Column start address.  The value must be less than the ColumnSize value from the GetDimmInfo function for the DIMMs that will be tested.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetSeqStartAddr) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 RankAddr,
  UINT8                 BankAddr,
  UINT32                RowAddr,
  UINT32                ColAddr
  )
{
  MrcParameters *MrcData;
  MRC_HAL_SEQ_BASE_ADDRESS_STRUCT Address;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetSeqStartAddr (%u, %u, %u, %X, %X, %X, %X);\n", Socket, Controller, Channel, RankAddr, BankAddr, RowAddr, ColAddr);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((RankAddr > MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_Rank_Address_MAX) ||
      (BankAddr > MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_Bank_Address_MAX) ||
      (RowAddr  > MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_Row_Address_MAX) ||
      (ColAddr  > MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_Column_Address_MAX) ||
      mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel)) {
    return;
  }
#endif
  {
    Address.Rank   = RankAddr;
    Address.Bank   = BankAddr;
    Address.Row    = RowAddr;
    Address.Column = (UINT16) ColAddr;
    MrcHalSetReutChSeqBaseAddrStart (MrcData, Channel, &Address);
  }
  return;
}

/**
  Function used to set the sequence wrap address.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      RankAddr   - Rank start address.  This value is the index into the CPGC rank map (see the SetSeqRankMap() function).  The value must be less than the MaxNumberRankMapEntries value from the GetCpgcInfo() function.
  @param[in]      BankAddr   - Bank start address.  If the CPGC engine supports a bank map (i.e., the MaxNumberBankMapEntried value from the GetCpgcInfo() function is greater than 0) then this value is is the index into the CPGC bank map (see the SetSeqBankMap() function) and the value must be less than the MaxNumberBankMapEntried value from the GetCpgcInfo() function.  If the CPGC engine does not support a bank map then the value must be less than the BankCount value from the GetDimmInfo function for the DIMMs that will be tested.
  @param[in]      RowAddr    - Row start address.  The value must be less than the RowSize value from the GetDimmInfo function for the DIMMs that will be tested.
  @param[in]      ColAddr    - Column start address.  The value must be less than the ColumnSize value from the GetDimmInfo function for the DIMMs that will be tested.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetSeqWrapAddr) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 RankAddr,
  UINT8                 BankAddr,
  UINT32                RowAddr,
  UINT32                ColAddr
  )
{
  MrcParameters *MrcData;
  MRC_HAL_SEQ_BASE_ADDRESS_STRUCT Address;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetSeqWrapAddr (%u, %u, %u, %u, %u, %u, %u);\n", Socket, Controller, Channel, RankAddr, BankAddr, RowAddr, ColAddr);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((RankAddr > MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_Rank_Address_MAX) ||
      (BankAddr > MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_Bank_Address_MAX) ||
      (RowAddr  > MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_Row_Address_MAX) ||
      (ColAddr  > MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_Column_Address_MAX) ||
      mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel)) {
    return;
  }
#endif
  {
    Address.Rank   = RankAddr;
    Address.Bank   = BankAddr;
    Address.Row    = RowAddr;
    Address.Column = (UINT16) ColAddr;
    MrcHalSetReutChSeqBaseAddrWrap (MrcData, Channel, &Address);
  }
  return;
}

/**
  Function used to set the sequence address increment.

  @param[in, out] This            - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket          - Zero based CPU socket number.
  @param[in]      Controller      - Zero based controller number.
  @param[in]      Channel         - Zero based channel number.
  @param[in]      RankAddrIncMode - Rank address increment rate mode.
  @param[in]      RankAddrIncRate - Rank address increment rate.  In linear mode (see RankAddrIncMode), RankAddrIncRate+1 specifies how many times a specific rank address is repeated before adding the RankAddrIncVal.  In exponential mode, 2^RankAddrIncRate defines how many times a specific rank address is repeated before adding the RankAddrIncVal.  If RankAddrIncMode is ExponentialAddrIncMode then the value must be less than or equal to the MaxRankAddrIncRateExponentVal from the GetCpgcInfo() function.  If RankAddrIncMode is LinearAddrIncMode then the value must be less than or equal to the MaxRankAddrIncRateLinearVal from the GetCpgcInfo() function.
  @param[in]      RankAddrIncVal  - Rank start address increment value.  When dictated by RankAddrIncRate the current rank address will be modified by the RankAddrIncVal (which is a 2's compliment field).  A value of 0 means the rank address increment is effectively disabled since no offset will be applied.  Disabling the rank address increment by setting RankAddrIncVal to 0 does not affect a carry from a lower order field rolling over to a higher order field which will also result in an increment or decrement to the higher order field of +1 or -1.  Note that a positive value in this field will cause a +1 carry to propagate while a negative value will cause a -1 carry to propagate from order N to order N+1.  The value must be greater than or equal to the MinRankAddrIncVal from the GetCpgcInfo() function.  The value must be less than or equal to the MaxRankAddrIncVal from the GetCpgcInfo() function.
  @param[in]      BankAddrIncMode - Bank address increment rate mode.
  @param[in]      BankAddrIncRate - Bank address increment rate.  In linear mode (see BankAddrIncMode), BankAddrIncRate+1 specifies how many times a specific rank address is repeated before adding the BankAddrIncVal.  In exponential mode, 2^BankAddrIncRate defines how many times a specific rank address is repeated before adding the BankAddrIncVal.  If BankAddrIncMode is ExponentialAddrIncMode then the value must be less than or equal to the MaxBankAddrIncRateExponentVal from the GetCpgcInfo() function.  If BankAddrIncMode is LinearAddrIncMode then the value must be less than or equal to the MaxBankAddrIncRateLinearVal from the GetCpgcInfo() function.
  @param[in]      BankAddrIncVal  - Bank start address increment value.  When dictated by BankAddrIncRate the current bank address will be modified by the BankAddrIncVal (which is a 2's compliment field).  A value of 0 means the bank address increment is effectively disabled since no offset will be applied.  Disabling the bank address increment by setting BankAddrIncVal to 0 does not affect a carry from a lower order field rolling over to a higher order field which will also result in an increment or decrement to the higher order field of +1 or -1.  Note that a positive value in this field will cause a +1 carry to propagate while a negative value will cause a -1 carry to propagate from order N to order N+1.  The value must be greater than or equal to the MinBankAddrIncVal from the GetCpgcInfo() function.  The value must be less than or equal to the MaxBankAddrIncVal from the GetCpgcInfo() function.
  @param[in]      RowAddrIncMode  - Row address increment rate mode.
  @param[in]      RowAddrIncRate  - Row address increment rate.  In linear mode (see RowAddrIncMode), RowAddrIncRate+1 specifies how many times a specific rank address is repeated before adding the RowAddrIncVal.  In exponential mode, 2^RowAddrIncRate defines how many times a specific rank address is repeated before adding the RowAddrIncVal.  If RowAddrIncMode is ExponentialAddrIncMode then the value must be less than or equal to the MaxRowAddrIncRateExponentVal from the GetCpgcInfo() function.  If RowAddrIncMode is LinearAddrIncMode then the value must be less than or equal to the MaxRowAddrIncRateLinearVal from the GetCpgcInfo() function.
  @param[in]      RowAddrIncVal   - Row start address increment value.  When dictated by RowAddrIncRate the current row address will be modified by the RowAddrIncVal (which is a 2's compliment field.  A value of 0 means the row address increment is effectively disabled since no offset will be applied.  Disabling the row address increment by setting RowAddrIncVal to 0 does not affect a carry from a lower order field rolling over to a higher order field which will also result in an increment or decrement to the higher order field of +1 or -1.  Note that a positive value in this field will cause a +1 carry to propagate while a negative value will cause a -1 carry to propagate from order N to order N+1.  The value must be greater than or equal to the MinRowAddrIncVal from the GetCpgcInfo() function.  The value must be less than or equal to the MaxRowAddrIncVal from the GetCpgcInfo() function.
  @param[in]      ColAddrIncMode  - Column address increment rate mode.
  @param[in]      ColAddrIncRate  - Column address increment rate.  If ColAddrIncMode is ExponentialAddrIncMode then 2^ColAddrIncRate defines how many times a specific rank address is repeated before adding the ColAddrIncVal.  If ColAddrIncMode is LinearAddrIncMode then ColAddrIncRate+1 specifies how many times a specific rank address is repeated before adding the ColAddrIncVal.  If ColAddrIncMode is ExponentialAddrIncMode then the value must be less than or equal to the MaxColAddrIncRateExponentVal from the GetCpgcInfo() function.  If ColAddrIncMode is LinearAddrIncMode then the value must be less than or equal to the MaxColAddrIncRateLinearVal from the GetCpgcInfo() function.
  @param[in]      ColAddrIncVal   - Column start address increment value.  When dictated by ColAddrIncRate the current column address will be modified by the ColAddrIncVal (which is a 2's compliment field).  A value of 0 means the column address increment is effectively disabled since no offset will be applied.  Disabling the column address increment by setting column address increment to 0 does not affect a carry from a lower order field rolling over to a higher order field which will also result in an increment or decrement to the higher order field of +1 or -1.  Note that a positive value in this field will cause a +1 carry to propagate while a negative value will cause a -1 carry to propagate from order N to order N+1.  The value must be greater than or equal to the MinColAddrIncVal from the GetCpgcInfo() function.  The value must be less than or equal to the MaxColAddrIncVal from the GetCpgcInfo() function.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetSeqAddrInc) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  ADDR_INC_MODE         RankAddrIncMode,
  UINT32                RankAddrIncRate,
  INT8                  RankAddrIncVal,
  ADDR_INC_MODE         BankAddrIncMode,
  UINT32                BankAddrIncRate,
  INT8                  BankAddrIncVal,
  ADDR_INC_MODE         RowAddrIncMode,
  UINT32                RowAddrIncRate,
  INT16                 RowAddrIncVal,
  ADDR_INC_MODE         ColAddrIncMode,
  UINT32                ColAddrIncRate,
  INT16                 ColAddrIncVal
  )
{
  MrcParameters                  *MrcData;
  MRC_HAL_REUT_BASE_ADDR_INC_CTL IncCtl[MrcHalAddressSelectMax];
  MRC_HAL_REUT_BASE_ADDR_INC_CTL *IncCtlPtr;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetSeqAddrInc (%u, %u, %u, ", Socket, Controller, Channel);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "%u, %u, %u, %u, %u, %u", RankAddrIncMode, RankAddrIncRate, RankAddrIncVal, BankAddrIncMode, BankAddrIncRate, BankAddrIncVal);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "%u, %u, %u, %u, %u, %u);\n", RowAddrIncMode, RowAddrIncRate, RowAddrIncVal, ColAddrIncMode, ColAddrIncRate, ColAddrIncVal);

#ifdef SSA_PARAM_ERROR_CHECK
  if ((0) ||
      mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel)) {
    return;
  }
#endif
  {
    IncCtlPtr            = IncCtl;
    IncCtlPtr->Increment = RankAddrIncVal;
    IncCtlPtr->Rate      = RankAddrIncRate;
    IncCtlPtr->Scale     = (MRC_HAL_ENUM_INCRMENT_SCALE_CONTROL) RankAddrIncMode;

    IncCtlPtr++;
    IncCtlPtr->Increment = BankAddrIncVal;
    IncCtlPtr->Rate      = BankAddrIncRate;
    IncCtlPtr->Scale     = (MRC_HAL_ENUM_INCRMENT_SCALE_CONTROL) BankAddrIncMode;

    IncCtlPtr++;
    IncCtlPtr->Increment = RowAddrIncVal;
    IncCtlPtr->Rate      = RowAddrIncRate;
    IncCtlPtr->Scale     = (MRC_HAL_ENUM_INCRMENT_SCALE_CONTROL) RowAddrIncMode;

    IncCtlPtr++;
    IncCtlPtr->Increment = ColAddrIncVal;
    IncCtlPtr->Rate      = ColAddrIncRate;
    IncCtlPtr->Scale     = (MRC_HAL_ENUM_INCRMENT_SCALE_CONTROL) ColAddrIncMode;

    MrcHalSetReutChSeqBaseAddrIncCtl (MrcData, Channel, MrcHalAddressSelectMax, &IncCtl[0]);
  }
  return;
}

/**
  Function used to set the sequence rank map.

  @param[in, out] This          - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      PairCount     - Number of entries in the DimmRankPairs array.  The minimum value is 1.  The value must be less than or equal to the MaxNumberRankMapEntries value from the GetCpgcInfo() function.
  @param[in]      DimmRankPairs - Pointer to array of DIMM and physical rank pair values.  The valid DIMM/rank pairs can be determined via the GetDimmBitMask() and GetRankInDimm() functions.  Note that the same rank may appear more than once in the map.  Note also that all ranks do not need to appear in the map.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetSeqRankMap) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 PairCount,
  CONST DIMM_RANK_PAIR  *DimmRankPairs
  )
{
  MrcParameters        *MrcData;
  CONST DIMM_RANK_PAIR *PhysicalRank;
  UINT32               Rank;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetSeqRankMap (%u, %u, %u, %u);\n", Socket, Controller, Channel, PairCount);
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) DimmRankPairs, PairCount * sizeof (DIMM_RANK_PAIR));
#ifdef SSA_PARAM_ERROR_CHECK
  if ((PairCount == 0) ||
      (PairCount > MAX_NUMBER_RANK_MAP_ENTRIES) ||
      (DimmRankPairs != NULL) ||
      mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel)) {
    return;
  }
#endif
  PhysicalRank = DimmRankPairs;
  for (Rank = 0; Rank < PairCount; Rank++, PhysicalRank++) {
    MrcHalSetLogicalToPhysicalRankMapping (MrcData, Channel, Rank, (PhysicalRank->Dimm * MAX_RANK_IN_DIMM) + PhysicalRank->Rank);
  }
  return;
}

/**
  Function used to set the sequence bank map.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      BankCount  - Number of entries in the Banks array.  The minimum value is 1.  The value must be less than or equal to the MaxNumberBankMapEntries value from the GetCpgcInfo() function.
  @param[in]      Banks      - Pointer to array of zero-based bank values.  The values must be less than the BankCount value from the GetDimmInfo function for the DIMMs that will be tested.  Note that the same bank may appear more than once in the map.  Note also that all banks do not need to appear in the map.

  @retval NotAvailable if the system does not support the bank mapping feature.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetSeqBankMap) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 BankCount,
  CONST UINT8           *Banks
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;
  UINT32        BankNum;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetSeqBankMap (%u, %u, %u, %u);\n", Socket, Controller, Channel, BankCount);
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) Banks, BankCount);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((BankCount == 0) ||
      (BankCount > MAX_NUMBER_BANK_MAP_ENTRIES) ||
      (Banks != NULL)) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    for (BankNum = 0; BankNum < BankCount; BankNum++) {
      MrcHalSetLogicalToPhysicalBankMapping (MrcData, Channel, BankNum, Banks[BankNum]);
    }
  }
  return (SsaStatus);
}

/**
  Function used to set the sequence lower row address swizzle.

  @param[in, out] This         - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket       - Zero based CPU socket number.
  @param[in]      Controller   - Zero based controller number.
  @param[in]      Channel      - Zero based channel number.
  @param[in]      SwizzleCount - Number of entries in the Swizzles array.  The value must be less than or equal to the MaxNumberRowAddrSwizzleEntries value from the GetCpgcInfo() function.  If the SwizzleCount value is 0 (and the Swizzles value is NULL) then the row address swizzling will be configured so that all the lower row addresses are mapped to themselves; effectively disabling the swizzling.
  @param[in]      Swizzles     - Pointer to array of lower row address swizzle values.  The values must be unique and less than or equal to the MaxRowAddrSwizzleVal value from the GetCpgcInfo() function.  The array position indicates the row address that the specified row address will be swapped with, e.g., a value of 10 at the array index 1 means that row addresses 10 and 1 will be swapped.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetSeqRowAddrSwizzle) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 SwizzleCount,
  CONST UINT8           *Swizzles
  )
{
  MrcParameters *MrcData;
  UINT32        Row;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetCkeOverride (%u, %u, %u, %u);\n", Socket, Controller, Channel, SwizzleCount);
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) Swizzles, SwizzleCount);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((SwizzleCount == 0) ||
      (SwizzleCount > MAX_NUMBER_RANK_MAP_ENTRIES) ||
      (Swizzles != NULL) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel)));
#endif
  {
    for (Row = 0; Row < SwizzleCount; Row++) {
      MrcHalSetRowAddressSwizzle (MrcData, Channel, Row, Swizzles[Row]);
    }
  }
  return;
}

/**
  Function used to get the current sequence state.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[out]     SeqState   - Pointer to buffer where sequence state will be stored.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientGetSeqState) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  SSA_SEQ_STATE         *SeqState
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((SeqState == NULL) || (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  MrcHalGetCurrentSubSeqStatus (
    MrcData,
    Channel,
    (UINT32 *) &SeqState->LoopCount,
    (UINT8 *)  &SeqState->SubSeqIndex,
    (UINT32 *) &SeqState->Cacheline,
    (UINT8 *)  &SeqState->BaseRank,
    (UINT8 *)  &SeqState->BaseBank,
    (UINT32 *) &SeqState->BaseRow,
    (UINT32 *) &SeqState->BaseCol,
    (UINT32 *) &SeqState->OffsetRow,
    (UINT32 *) &SeqState->OffsetCol
    );

  SSA_DEBUG_MSG (
    &MrcData->Outputs.Debug,
    MSG_LEVEL_NOTE,
    "GetSeqState (%u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u);\n",
    Socket,
    Controller,
    Channel,
    SeqState->LoopCount,
    SeqState->SubSeqIndex,
    SeqState->Cacheline,
    SeqState->BaseRank,
    SeqState->BaseBank,
    SeqState->BaseRow,
    SeqState->BaseCol,
    SeqState->OffsetRow,
    SeqState->OffsetCol
    );

  return;
}

/**
  Function used to set the CPGC stop mode.

  @param[in, out] This                - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket              - Zero based CPU socket number.
  @param[in]      Controller          - Zero based controller number.
  @param[in]      Channel             - Zero based channel number.
  @param[in]      StopMode            - CPGC stop mode.
  @param[in]      StopOnNthErrorCount - Error count for stop-on-nth-any-lane error mode.  Minimum value is 1.  The value must be less than or equal to the MaxStopOnNthErrorCountVal value from the GetCpgcInfo() function.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetStopMode) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  CPGC_STOP_MODE        StopMode,
  UINT32                StopOnNthErrorCount
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetStopMode (%u, %u, %u, %u, %u);\n", Socket, Controller, Channel, StopMode, StopOnNthErrorCount);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((StopMode >= CpgcStopModeMax) || (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  MrcHalSetReutChannelErrorControl (
    MrcData,
    Channel,
    StopOnNthErrorCount,
    MrcHalStopOnCaAlertIgnoreArg,
    (MRC_HAL_ENUM_STOP_ON_ERROR_CONTROL) StopMode,
    MrcHalSelectiveErrorEnableIgnoreArg,
    MrcHalSelectiveErrorEnableCachelineIgnoreArg
    );
  return;
}

/**
  Function used to set the error counter mode.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket      - Zero based CPU socket number.
  @param[in]      Controller  - Zero based controller number.
  @param[in]      Channel     - Zero based channel number.
  @param[in]      Counter     - Zero based error counter number.  The value must be less than or equal to the MaxNumberErrorCounters value from the GetCpgcInfo() function.
  @param[in]      Mode        - Error counter mode.
  @param[in]      ModeIndex   - Extra index used to provide additional information if needed by the mode selected. This indicates which lane, nibble, byte, or chunk has been selected.  If CounterMode value is LaneErrorCounterMode then the ModeIndex value must be less than the BusWidth value from the GetSystemInfo() function.  If CounterMode is NibbleErrorCounterMode then the ModeIndex value must be less than the BusWidth/4 value from the GetSystemInfo() function.  If CounterMode is ByteErrorCounterMode then the ModeIndex value must be less than the BusWidth/8 value from the GetSystemInfo() function.  If CounterMode is ChunkErrorCounterMode then the ModeIndex value must be less than 8.

  @retval NotAvailable if the given Mode value is not supported.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetErrorCounterMode) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Counter,
  ERROR_COUNTER_MODE    Mode,
  UINT32                ModeIndex
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetErrorCounterMode (%u, %u, %u, %u, %u 0x%X);\n", Socket, Controller, Channel, Counter, Mode, ModeIndex);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Counter > MAX_NUMBER_ERROR_COUNTERS) ||
      (Mode >= ErrorCounterModeMax) ||
      (ModeIndex > MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_0_Counter_Pointer_MAX)) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    MrcHalSetChannelErrorCounterControl (MrcData, Channel, Counter, (MRC_HAL_ENUM_ERROR_COUNTER_CONTROL) Mode, ModeIndex);
  }
  return (SsaStatus);
}

/**
  Function used to set the lane validation mask.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      LaneMasks  - Pointer to array of lane bitmasks.  The number of array elements is the BusWidth value from the GetSystemInfo() function divided by 8.  Bit value 1 = perform validation; bit value 0 = do not perform validation.  Note that this may not be the same logic as the hardware.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetLaneValidationMask) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  CONST UINT8           *LaneMasks
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetLaneValidationMask (%u, %u, %u);\n", Socket, Controller, Channel);
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) LaneMasks, 8);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((LaneMasks == NULL) || (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  MrcHalSetRegReutChErrDataMask (
    MrcData,
    Channel,
    ~(*((CONST UINT64 *) LaneMasks))
    );
  MrcHalSetRegReutChErrEccMask (
    MrcData,
    Channel,
    MrcData->Outputs.EccSupport ? ~LaneMasks[8] : 0xFF
    );
  return;
}

/**
  Function used to set the chunk validation mask.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      ChunkMask  - Mask for the chunks. One bit for each chunk of a cacheline.  Bit value 1 = perform validation; bit value 0 = do not perform validation.  Bit position 0 = chunk 0; bit position 1 = chunk 1, etc.  Note that this may not be the same logic as the hardware.

  @retval NotAvailable if the system does not provide chunk validation control.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetChunkValidationMask) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 ChunkMask
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetChunkValidationMask (%u, %u, %u, %X);\n", Socket, Controller, Channel, ChunkMask);
#ifdef SSA_PARAM_ERROR_CHECK
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    MrcHalSetReutChannelErrorControl (MrcData, Channel, MRC_IGNORE_ARG, MrcHalStopOnCaAlertIgnoreArg, MrcHalStopOnErrorIgnoreArg, ChunkMask, MrcHalSelectiveErrorEnableCachelineIgnoreArg);
  }
  return (SsaStatus);
}

/**
  Function used to set the cacheline mask.

  @param[in, out] This          - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      CachelineMask - Mask for cachelines to be enabled.  Bit value 1 = perform validation; bit value 0 = do not perform validation.  Bit position 0 = cacheline 0; bit position 1 = cacheline 1, etc.  Note that this may not be the same logic as the hardware.

  @retval NotAvailable if the system does not provide cacheline validation control.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetCachelineValidationMask) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 CachelineMask
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetCachelineValidationMask (%u, %u, %u, %X);\n", Socket, Controller, Channel, CachelineMask);
#ifdef SSA_PARAM_ERROR_CHECK
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    MrcHalSetReutChannelErrorControl (MrcData, Channel, MRC_IGNORE_ARG, MrcHalStopOnCaAlertIgnoreArg, MrcHalStopOnErrorIgnoreArg, MrcHalSelectiveErrorEnableIgnoreArg, CachelineMask);
  }
  return (SsaStatus);
}

/**
  Function used to get the lane error status.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      ChunkMask  - Mask for the chunks. One bit for each chunk.  This mask should set to be the same value as the mask being passed to the SetChunkValidationMask() function.  Products don't have separate error status for even and odd UI should ignore this parameter.
  @param[out]     Status     - Pointer to array where the lane error status values will be stored.  The number of array elements is the BusWidth value from the GetSystemInfo() function divided by 8.  Bit value 1 = at least one error occurred; bit value 0 = no errors occurred.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientGetLaneErrorStatus) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 ChunkMask,
  UINT8                 *Status
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
 #ifdef SSA_PARAM_ERROR_CHECK
  if (Status == NULL) {
    return;
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  MrcHalGetChannelErrorStatus (MrcData, Channel, Status);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetLaneErrorStatus (%u, %u, %u, %X, %X);\n", Socket, Controller, Channel, ChunkMask, *Status);
  return;
}

/**
  Function used to get the chunk error status.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[out]     Status     - Pointer to where the chunk error status will be stored.  Bit value 1 = at least one error occurred; bit value 0 = no errors occurred. Bit position 0 = chunk 0; bit position 1 = chunk 1, etc.

  @retval NotAvailable if the system does not provide chunk error status.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientGetChunkErrorStatus) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 *Status
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if (Status == NULL) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    *Status = (UINT8) MrcHalGetChannelChunkErrorStatus (MrcData, Channel);
  }
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetChunkErrorStatus (%u, %u, %u, %X);\n", Socket, Controller, Channel, *Status);
  return (SsaStatus);
}

/**
  Function used to get the rank error status.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[out]     Status     - Pointer to where the phyical rank error status of the given Dimm will be stored.  Bit value 1 = at least one error occurred; bit value 0 = no errors occurred. Bit position 0 = rank 0; bit position 1 = rank 1, etc.

  @retval NotAvailable if the system does not provide rank error status.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientGetRankErrorStatus) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 *Status
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if (Status == NULL) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    *Status = (UINT8) MrcHalGetChannelRankErrorStatus (MrcData, Channel);
  }
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetRankErrorStatus (%u, %u, %u, %X);\n", Socket, Controller, Channel, *Status);
  return (SsaStatus);
}

/**
  Function used to get the address associated with the last error detected.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[out]     Address    - Pointer to buffer where error address will be stored.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientGetErrorAddress) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  SSA_ADDRESS           *Address
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Address == NULL) || (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  {
    MrcHalGetReutChErrorAddress (
      MrcData,
      Channel,
      (UINT8 *) &Address->Rank,
      (UINT8 *) &Address->Bank,
      (UINT32 *) &Address->Row,
      (UINT16 *) &Address->Col
      );
  }
  SSA_DEBUG_MSG (
    &MrcData->Outputs.Debug,
    MSG_LEVEL_NOTE,
    "GetErrorAddress (%u, %u, %u, %u, %u, %u, %u);\n",
    Socket,
    Controller,
    Channel,
    Address->Rank,
    Address->Bank,
    Address->Row,
    Address->Col
    );
  return;
}

/**
  Function used to get the error count.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      Counter    - Zero based counter number.  The value must be less than or equal to the MaxNumberErrorCounters value from the GetCpgcInfo() function.
  @param[out]     Count      - Pointer to where the error counter value will be stored.
  @param[out]     Overflow   - Pointer to where the error counter overflow status will be stored.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientGetErrorCount) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 Counter,
  UINT32                *Count,
  BOOLEAN               *Overflow
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((Counter >= MAX_NUMBER_ERROR_COUNTERS) ||
      (Count == NULL) ||
      (Overflow == NULL) ||
      (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  *Overflow = MrcHalGetRegReutChErrCounterStatus (MrcData, Channel, Counter, (UINT32 *) Count);
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetErrorCount (%u, %u, %u, %u, %u, %u);\n", Socket, Controller, Channel, Counter, *Count, *Overflow);
  return;
}

/**
  Function used to set the DqDB error capture configuration.

  @param[in, out] This           - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket         - Zero based CPU socket number.
  @param[in]      Controller     - Zero based controller number.
  @param[in]      Channel        - Zero based channel number.
  @param[in]      Enable         - If set to TRUE then cachelines for which errors are detected are written to the DqDB starting at the StartCacheline and continuing to the EndCacheline before wrapping around to the StartCacheline.  If set to FALSE then the DqDB error capture feature is disabled.
  @param[in]      StartCacheline - The starting cacheline in the DqDB where the error status will be captured.  The value must be less than the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.
  @param[in]      EndCacheline   - The ending cacheline in the DqDB where the error status will be captured.  The value must be greater than or equal to the StartCacheline value.  The value must be less than the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetDqdbErrorCaptureConfig) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  BOOLEAN               Enable,
  UINT8                 StartCacheline,
  UINT8                 EndCacheline
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (
    &MrcData->Outputs.Debug,
    MSG_LEVEL_NOTE,
    "SetDqdbErrorCaptureConfig (%u, %u, %u, %u, %u, %u);\n",
    Socket,
    Controller,
    Channel,
    Enable,
    StartCacheline,
    EndCacheline
    );
#ifdef SSA_PARAM_ERROR_CHECK
  if (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel)) {
    return;
  }
#endif
  MrcHalRmwWdbCaptureControl (MrcData, Channel, Enable, MRC_IGNORE_ARG, MRC_IGNORE_ARG, StartCacheline, EndCacheline);
  return;
}

/**
  Function used to get the DqDB error capture status.

  @param[in, out] This             - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket           - Zero based CPU socket number.
  @param[in]      Controller       - Zero based controller number.
  @param[in]      Channel          - Zero based channel number.
  @param[out]     CurrentCacheline - Pointer to where the current DqDB error capture cacheline value will be stored.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientGetDqdbErrorCaptureStatus) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  UINT8                 *CurrentCacheline
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if ((CurrentCacheline == NULL) || (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel))) {
    return;
  }
#endif
  *CurrentCacheline = MrcHalGetReutWdbCurrentCapturePointer (MrcData, Channel);
  SSA_DEBUG_MSG (
    &MrcData->Outputs.Debug,
    MSG_LEVEL_NOTE,
    "GetDqdbErrorCaptureStatus (%u, %u, %u, %u);\n",
    Socket,
    Controller,
    Channel,
    *CurrentCacheline
    );
  return;
}

/**
  Function used to set the local test control.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket      - Zero based CPU socket number.
  @param[in]      Controller  - Zero based controller number.
  @param[in]      Channel     - Zero based channel number.
  @param[in]      ClearErrors - Setting this parameter to TRUE causes all the channel's error counters and status to be cleared.
  @param[in]      StartTest   - Setting this parameter to TRUE starts the channel's CPGC engine.
  @param[in]      StopTest    - Setting this parameter to TRUE stops the channel's CPGC engine.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetLocalTestControl) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  BOOLEAN               ClearErrors,
  BOOLEAN               StartTest,
  BOOLEAN               StopTest
  )
{
  MrcParameters             *MrcData;
  MRC_HAL_ENUM_TEST_CONTROL TestControl;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetLocalTestControl (%u, %u, %u, %u, %u, %u);\n", Socket, Controller, Channel, ClearErrors, StartTest, StopTest);
#ifdef SSA_PARAM_ERROR_CHECK
  if (mrcSuccess != IsChannelPresent (MrcData, Socket, Controller, Channel)) {
    return;
  }
#endif
  if ((StartTest == 0) && (StopTest == 1)) {
    TestControl = MrcHalTestControlStop;
  } else if ((StartTest == 1) && (StopTest == 0)) {
    TestControl = MrcHalTestControlStart;
  } else {
    TestControl = MrcHalTestControlNull;
  }
  MrcHalSetReutChannelSequenceControl (
    MrcData,
    Channel,
    TestControl,
    (MRC_HAL_ENUM_CLEAR_ERROR_CONTROL) ClearErrors
    );
  return;
}

/**
  Function used to set the global test control.  Settings apply to all channels whose EnableGlobalControl is set to TRUE (see SetSeqConfig function).

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket      - Zero based CPU socket number.
  @param[in]      Controller  - Zero based controller number.
  @param[in]      ClearErrors - Setting this parameter to TRUE causes all controller's error counters and status to be cleared.
  @param[in]      StartTest   - Setting this parameter to TRUE starts the channel's CPGC engine.
  @param[in]      StopTest    - Setting this parameter to TRUE stops the channel's CPGC engine.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetGlobalTestControl) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  BOOLEAN               ClearErrors,
  BOOLEAN               StartTest,
  BOOLEAN               StopTest
  )
{
  MrcParameters             *MrcData;
  MRC_HAL_ENUM_TEST_CONTROL TestControl;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetGlobalTestControl (%u, %u, %u, %u, %u);\n", Socket, Controller, ClearErrors, StartTest, StopTest);
#ifdef SSA_PARAM_ERROR_CHECK
  if (mrcSuccess != IsControllerPresent (MrcData, Socket, Controller)) {
    return;
  }
#endif
  if ((StartTest == 0) && (StopTest == 1)) {
    TestControl = MrcHalTestControlStop;
  } else if ((StartTest == 1) && (StopTest == 0)) {
    TestControl = MrcHalTestControlStart;
  } else {
    TestControl = MrcHalTestControlNull;
  }
  MrcHalSetReutGlobalSequenceControl (
    MrcData,
    TestControl,
    (MRC_HAL_ENUM_CLEAR_ERROR_CONTROL) ClearErrors,
    MrcHalStopOnErrorDisable
    );
  return;
}

/**
  Function used to get the test done status.

  @param[in, out] This         - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket       - Zero based CPU socket number.
  @param[in]      Controller   - Zero based controller number.
  @param[in]      ChannelMask  - Channel mask.  Each bit represents a channel to be checked.  Bit value 1 = perform check; bit value 0 = do not perform check.  Bit position 0 = channel 0; bit position 1 = channel 1, etc.
  @param[out]     TestDoneMask - Pointer to where mask of per-channel test done status will be placed.  Bit value 1 = test complete; bit value 0 = test not complete or check not performed.  Bit position 0 = channel 0; bit position 1 = channel 1, etc.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientGetTestDone) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 ChannelMask,
  UINT8                 *TestDoneMask
  )
{
  MrcParameters       *MrcData;
  UINT32              RunStatusMask;
  UINT32              ErrorStatusMask;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if (mrcSuccess != IsControllerPresent (MrcData, Socket, Controller)) {
    return;
  }
#endif
  *TestDoneMask = 0;
  MrcHalGetReutGlobalStatus (MrcData, &RunStatusMask, &ErrorStatusMask);
  *TestDoneMask = (UINT8) RunStatusMask;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetTestDone (%u, %u, %X, %X);\n", Socket, Controller, ChannelMask, *TestDoneMask);
  return;
}

/**
  Function used to set the scrambler configuration.

  @param[in, out] This                - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket              - Zero based CPU socket number.
  @param[in]      Controller          - Zero based controller number.
  @param[in]      Enable              - Specifies whether the scrambler is enabled.
  @param[in]      ClockGateABMode     - Clock gate cipher A/B mode.
  @param[in]      ClockGateCMode      - Clock gate cipher C mode.
  @param[in]      EnableDbiAB         - Specifies whether DBI is enabled for cipher A/B.
  @param[in]      Key                 - Scrambler key.  The value must be less than or equal to the MaxScramblerKeyVal value from the GetCpgcInfo() function.
  @param[out]     PrevEnable          - Pointer to where the previous scrambler enable setting will be stored.  This value may be NULL.
  @param[out]     PrevClockGateABMode - Pointer to where the previous clock gate cipher A/B mode setting will be stored.  This value may be NULL.
  @param[out]     PrevClockGateCMode  - Pointer to where the previous clock gate cipher C mode setting will be stored.  This value may be NULL.
  @param[out]     PrevEnableDbiAB     - Pointer to where the previous DBI enable for cipher A/B setting will be stored.  This value may be NULL.
  @param[out]     PrevKey             - Pointer to where the previous scrambler key setting will be stored.  This value may be NULL.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetScramblerConfig) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  BOOLEAN               Enable,
  CLOCK_GATE_AB_MODE    ClockGateABMode,
  CLOCK_GATE_C_MODE     ClockGateCMode,
  BOOLEAN               EnableDbiAB,
  UINT16                Key,
  BOOLEAN               *PrevEnable,
  CLOCK_GATE_AB_MODE    *PrevClockGateABMode,
  CLOCK_GATE_C_MODE     *PrevClockGateCMode,
  BOOLEAN               *PrevEnableDbiAB,
  UINT16                *PrevKey
  )
{
  MrcParameters *MrcData;
  UINT32        Channel;
  UINT32        SsaEnable;
  UINT32        SsaKey;
  UINT32        SsaClockGateABMode;
  UINT32        SsaClockGateCMode;
  UINT32        SsaEnableDbiAB;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetScramblerConfig (%u, %u, %u, %u, %u, %u, %04Xh);\n", Socket, Controller, Enable, ClockGateABMode, ClockGateCMode, EnableDbiAB, Key);
#ifdef SSA_PARAM_ERROR_CHECK
  if (mrcSuccess != IsControllerPresent (MrcData, Socket, Controller)) {
    return;
  }
#endif
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) {
      MrcHalGetScramblerControl (MrcData, Channel, (UINT32 *) &SsaEnable, (UINT32 *) &SsaKey, (UINT32 *) &SsaClockGateABMode, (UINT32 *) &SsaClockGateCMode, (UINT32 *) &SsaEnableDbiAB);
      if (PrevEnable != NULL) {
        *PrevEnable = (BOOLEAN) SsaEnable;
      }
      if (PrevKey != NULL) {
        *PrevKey = (UINT16) SsaKey;
      }
      if (PrevClockGateABMode != NULL) {
        *PrevClockGateABMode = SsaClockGateABMode;
      }
      if (PrevClockGateCMode != NULL) {
        *PrevClockGateCMode = SsaClockGateCMode;
      }
      if (PrevEnableDbiAB != NULL) {
        *PrevEnableDbiAB = (BOOLEAN) SsaEnableDbiAB;
      }
      break;
    }
  }
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) {
      MrcHalSetScramblerControl (
        MrcData,
        Channel,
        (MRC_HAL_ENUM_SCRAMBLER_CONTROL) Enable,
        Key,
        (MRC_HAL_ENUM_CLOCK_GATE_AB_CONTROL) ClockGateABMode,
        (MRC_HAL_ENUM_CLOCK_GATE_C_CONTROL) ClockGateCMode,
        (MRC_HAL_ENUM_DBI_AB_CONTROL) EnableDbiAB
        );
    }
  }
  return;
}

/**
  Function used to set the self-refresh configuration.

  @param[in, out] This          - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Enable        - Specifies whether self-refreshes are enabled.
  @param[in]      IdleTimer     - Specifies the number of consecutive cycles without any transaction in order to enter self-refresh.  The value must be less than or equal to the MaxRefreshIdleTimerVal value from the GetCpgcInfo() function.
  @param[out]     PrevEnable    - Pointer to where the previous self-refresh enable setting will be stored.  This value may be NULL.
  @param[out]     PrevIdleTimer - Pointer to where the previous idle timer setting will be stored.  This value may be NULL.

  @retval Nothing.
**/
VOID
(EFIAPI BiosClientSetSelfRefreshConfig) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  BOOLEAN               Enable,
  UINT32                IdleTimer,
  BOOLEAN               *PrevEnable,
  UINT32                *PrevIdleTimer
  )
{
  MrcParameters                     *MrcData;
  UINT32                            PrevValue;
  MRC_HAL_ENUM_SELF_REFRESH_CONTROL PrevControl;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetSelfRefreshConfig (%u, %u, %u, %u);\n", Socket, Controller, Enable, IdleTimer);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((IdleTimer > MAX_REFRESH_IDLE_TIMER_VAL) || (mrcSuccess != IsControllerPresent (MrcData, Socket, Controller))) {
    return;
  }
#endif
  MrcHalGetSelfRefreshConfiguration (MrcData, (UINT32 *) &PrevValue, &PrevControl);
  if (PrevEnable != NULL) {
    *PrevEnable = (BOOLEAN) PrevControl;
  }
  if (PrevIdleTimer != NULL) {
    *PrevIdleTimer = PrevValue;
  }
  MrcHalSetSelfRefreshConfiguration (MrcData, IdleTimer, (MRC_HAL_ENUM_SELF_REFRESH_CONTROL) Enable);
  MrcHalWaitForSelfRefreshTransition (MrcData, Enable);
  return;
}

/**
  Function used to set the refresh override.

  @param[in, out] This                   - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket                 - Zero based CPU socket number.
  @param[in]      Controller             - Zero based controller number.
  @param[in]      Channel                - Zero based channel number.
  @param[in]      EnablePanicRefreshOnly - If set to TRUE then opportunistic and high priority auto refreshes will be disabled for all ranks and refreshes will only occur when the panic refresh watermark has been exceeded.  If set to FALSE then refreshes will occur using the existing MC functional refresh logic.
  @param[in]      EnableStartTestSync    - If set to TRUE then all refresh/ZQ powerdown logic (counters, FSMs, etc.) is kept in the default reset state (no refresh/ZQ happening) while in Loopback.Marker during REUT Mode. Once the test starts and the transition to Loopback.Pattern occurs the refresh/ZQ logic will behave identical to normal functional MC mode based on the values programmed in the refresh/ZQ CRs. This allows deterministic and reproducible behavior across REUT tests with respect to refresh/ZQ since the logic is synchronized to the start of a REUT test.  IF set to FALSE then the refresh/ZQ logic will not be synchronized to the start of a REUT test and will always behave identical to normal functional MC mode based on the values programmed in the refresh/ZQ CRs, whether in Loopback.Marker or Loopback.Pattern.  NOTE: This bit should not be used in conjunction with Self Refresh.
  @param[in]      PairCount              - Number of entries in the DimmRankPairs array.  If you wish to have no rank's refresh overridden then set PairCnt=0 and DimmRankPairs=NULL.  The value must be less than the MaxNumberRankMapEntries value from the GetCpgcInfo() function.
  @param[in]      DimmRankPairs          - Pointer to array of DIMM and physical rank pair values.  If a DIMM/rank appears in the list, then the CPGC engine will disable executing any refresh to that rank while in REUT mode. If a DIMM/rank doesn't appear in the list then the CPGC engine will enable executing a refresh (assuming the MC has refreshes enabled) to that rank while in REUT mode based on the EnablePanicRefreshOnly parameter value.  The valid DIMM/rank pairs can be determined via the GetDimmBitMask() and GetRankInDimm() functions.

  @retval NotAvailable if the system does not support the refresh override feature.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetRefreshOverride) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  BOOLEAN               EnablePanicRefreshOnly,
  BOOLEAN               EnableStartTestSync,
  UINT8                 PairCount,
  CONST DIMM_RANK_PAIR  *DimmRankPairs
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;
  UINT32        RankMask;
  UINT32        Rank;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetRefreshOverride (%u, %u, %u, %u, %u, %u);\n", Socket, Controller, Channel, EnablePanicRefreshOnly, EnableStartTestSync, PairCount);
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) DimmRankPairs, PairCount * sizeof (DIMM_RANK_PAIR));
#ifdef SSA_PARAM_ERROR_CHECK
  if ((PairCount == 0) ||
      (PairCount > MAX_NUMBER_RANK_MAP_ENTRIES) ||
      (DimmRankPairs != NULL)) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    for (RankMask = 0, Rank = 0; Rank < PairCount; Rank++) {
      RankMask |= 1 << ((DimmRankPairs->Dimm * MAX_RANK_IN_DIMM) + DimmRankPairs->Rank);
    }
    MrcHalSetSelfRefreshOverrideConfiguration (
      MrcData,
      Channel,
      (MRC_HAL_ENUM_RANK_MASK_CONTROL) RankMask,
      (MRC_HAL_ENUM_START_TEST_SYNC) EnableStartTestSync,
      (MRC_HAL_ENUM_PANIC_REFRESH_CONTROL) EnablePanicRefreshOnly
      );
  }
  return (SsaStatus);
}

/**
  Function used to set the ZQ calibration override.

  @param[in, out] This                    - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket                  - Zero based CPU socket number.
  @param[in]      Controller              - Zero based controller number.
  @param[in]      Channel                 - Zero based channel number.
  @param[in]      EnableZQCalAfterRefresh - If set to TRUE then a ZQ operation will always take place after a refresh occurs as long as the DIMM/rank does not appear in the DimmRankPairs array.  If set to FALSE then a ZQ operation will take place at the normal programmed period after a refresh occurs as long as the DIMM/rank does not appear in the DimmRankPairs array.
  @param[in]      PairCount               - Number of entries in the DimmRankPairs array.  If you wish to have no rank's ZQCal overridden then set PairCnt=0 and DimmRankPairs=NULL.  The value must be less than the product of the MaxNumberDimms and MaxNumberRanks values from the GetSystemInfo() function.
  @param[in]      DimmRankPairs           - Pointer to array of DIMM and physical rank pair values.  If a DIMM/rank appears in the list, then the CPGC engine will disable executing any ZQCal to that rank while in REUT mode.  The valid DIMM/rank pairs can be determined via the GetDimmBitMask() and GetRankInDimm() functions.

  @retval NotAvailable if the system does not support the ZQCal override feature.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetZQCalOverride) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  BOOLEAN               EnableZQCalAfterRefresh,
  UINT8                 PairCount,
  CONST DIMM_RANK_PAIR  *DimmRankPairs
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;
  UINT32        RankMask;
  UINT32        Rank;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetZQCalOverride (%u, %u, %u, %u, %u);\n", Socket, Controller, Channel, EnableZQCalAfterRefresh, PairCount);
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) DimmRankPairs, PairCount * sizeof (DIMM_RANK_PAIR));
#ifdef SSA_PARAM_ERROR_CHECK
  if ((PairCount == 0) ||
      (PairCount > MAX_NUMBER_RANK_MAP_ENTRIES) ||
      (DimmRankPairs != NULL)) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    for (RankMask = 0, Rank = 0; Rank < PairCount; Rank++) {
      RankMask |= 1 << ((DimmRankPairs->Dimm * MAX_RANK_IN_DIMM) + DimmRankPairs->Rank);
    }
    MrcHalSetZqCalOverrideConfiguration (
      MrcData,
      Channel,
      (MRC_HAL_ENUM_RANK_MASK_CONTROL) RankMask,
      (MRC_HAL_ENUM_ZQ_OPERATION_CONTROL) EnableZQCalAfterRefresh
      );
  }
  return (SsaStatus);
}

/**
  Function used to set the on-die-termination override.

  @param[in, out] This                  - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket                - Zero based CPU socket number.
  @param[in]      Controller            - Zero based controller number.
  @param[in]      Channel               - Zero based channel number.
  @param[in]      EnableMprDdrTrain     - This parameter is set to TRUE during DDR training.
  @param[in]      ValCount              - Number of entries in the DimmRankPairs and OverrideVals arrays.  If you wish to have no rank's ODT overridden then set ValCnt=0, DimmRankPairs=NULL, and OverrideVals=NULL.  The value must be less than twice the MaxNumberDimms value from the GetSystemInfo() function.
  @param[in]      DimmRankPairs         - Pointer to array of DIMM and physical rank pair values.  If a DIMM/rank appears in this array then its ODT value will be overridden with the value from the corresponding index in the OverrideVals array.  If a DIMM/rank does not appear in this array then its ODT will not be overridden.  The valid DIMM/rank pairs can be determined via the GetDimmBitMask() and GetRankInDimm() functions.
  @param[in]      OverrideVals          - Pointer to array of override values.  Value 1 = enable ODT for that rank while in REUT mode; value 0 = disable ODT for that rank while in REUT mode.

  @retval NotAvailable if the system does not support the ODT override feature.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetOdtOverride) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  BOOLEAN               EnableMprDdrTrain,
  UINT8                 ValCount,
  CONST DIMM_RANK_PAIR  *DimmRankPairs,
  CONST UINT8           *OverrideVals
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;
  UINT32        RankMask;
  UINT32        OverrideMask;
  UINT32        Rank;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetOdtOverride (%u, %u, %u, %u, %u);\n", Socket, Controller, Channel, EnableMprDdrTrain, ValCount);
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) DimmRankPairs, ValCount * sizeof (DIMM_RANK_PAIR));
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) OverrideVals, ValCount);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((ValCount == 0) ||
      (ValCount > MAX_NUMBER_RANK_MAP_ENTRIES) ||
      (DimmRankPairs != NULL)) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    for (OverrideMask = 0, RankMask = 0, Rank = 0; Rank < ValCount; Rank++) {
      RankMask |= 1 << ((DimmRankPairs->Dimm * MAX_RANK_IN_DIMM) + DimmRankPairs->Rank);
      OverrideMask |= (OverrideVals[Rank] != 0) << Rank;
    }
    MrcHalSetOdtOverrideConfiguration (
      MrcData,
      Channel,
      (MRC_HAL_ENUM_RANK_MASK_CONTROL) RankMask,
      (MRC_HAL_ENUM_RANK_MASK_CONTROL) OverrideMask,
      (MRC_HAL_ENUM_MPR_TRAIN_CONTROL) EnableMprDdrTrain
      );
  }
  return (SsaStatus);
}

/**
  Function used to set the clock-enable override.

  @param[in, out] This                  - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket                - Zero based CPU socket number.
  @param[in]      Controller            - Zero based controller number.
  @param[in]      Channel               - Zero based channel number.
  @param[in]      DisableCkePowerdown   - If set to TRUE then a CKE powerdown will be disabled when in REUT mode.  If set to FALSE then CKE power down will behave normally when in REUT.
  @param[in]      ValCount              - Number of entries in the DimmRankPairs and OverrideVals arrays.  If you wish to have no rank's CKE overridden then set ValCnt=0, DimmRankPairs=NULL, and OverrideVals=NULL.  The value must be less than the MaxNumberRankMapEntries value from the GetCpgcInfo() function.
  @param[in]      DimmRankPairs         - Pointer to array of DIMM and physical rank pair values.  If a DIMM/rank appears in this array then its CKE value will be overridden with the value from the corresponding index in the OverrideVals array.  If a DIMM/rank does not appear in this array then its CKE will not be overridden.  The valid DIMM/rank pairs can be determined via the GetDimmBitMask() and GetRankInDimm() functions.
  @param[in]      OverrideVals          - Pointer to array of override values.  Value 1 = enable CKE for that rank while in REUT mode; value 0 = disable CKE for that rank while in REUT mode.

  @retval NotAvailable if the system does not support the CKE override feature.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosClientSetCkeOverride) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Channel,
  BOOLEAN               DisableCkePowerDown,
  UINT8                 ValCount,
  CONST DIMM_RANK_PAIR  *DimmRankPairs,
  CONST UINT8           *OverrideVals
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;
  UINT32        RankMask;
  UINT32        OverrideMask;
  UINT32        Rank;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SetCkeOverride (%u, %u, %u, %u, %u);\n", Socket, Controller, Channel, DisableCkePowerDown, ValCount);
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) DimmRankPairs, ValCount * sizeof (DIMM_RANK_PAIR));
  SSA_PRINT_MEMORY (&MrcData->Outputs.Debug, (UINT8 *) OverrideVals, ValCount);
#ifdef SSA_PARAM_ERROR_CHECK
  if ((ValCount == 0) ||
      (ValCount > MAX_NUMBER_RANK_MAP_ENTRIES) ||
      (DimmRankPairs != NULL)) {
    return (UnsupportedValue);
  }
  SsaStatus = (mrcSuccess == IsChannelPresent (MrcData, Socket, Controller, Channel)) ? Success : UnsupportedValue;
  if (SsaStatus == Success)
#else
  SsaStatus = Success;
#endif
  {
    for (OverrideMask = 0, RankMask = 0, Rank = 0; Rank < ValCount; Rank++) {
      RankMask |= 1 << ((DimmRankPairs->Dimm * MAX_RANK_IN_DIMM) + DimmRankPairs->Rank);
      OverrideMask |= (OverrideVals[Rank] != 0) << Rank;
    }
    MrcHalSetCkeOverrideConfiguration (
      MrcData,
      Channel,
      (MRC_HAL_ENUM_RANK_MASK_CONTROL) RankMask,
      (MRC_HAL_ENUM_RANK_MASK_CONTROL) OverrideMask,
      (MRC_HAL_ENUM_START_TEST_SYNC) DisableCkePowerDown
      );
  }
  return (SsaStatus);
}

#endif // SSA_FLAG
// end file BiosSsaMemoryClientConfig.c
