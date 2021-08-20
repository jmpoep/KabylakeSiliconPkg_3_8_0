/** @file
  Implementation of the memory controller hardware abstraction layer.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2015 Intel Corporation.

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
#include "McAddress.h"
#include "MrcMcRegisterMacro.h"
#include "MrcInterface.h"
#include "MrcCommon.h"
#include "MrcReadReceiveEnable.h"
#include "MrcDdrIoDataOffsets.h"
#include "MrcRegisterCache.h"

#ifdef SSA_FLAG
#define MAX_CHUNK_SIZE (8)

/**
  This function sets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetBitField32 (
  IN const UINT32 HashIn,
  IN const UINT32 BitfieldValue,
  IN const UINT32 RegisterValue
  )
{
  UINT32 Mask;
  UINT32 BfOffset;
  UINT32 BfWidth;
  MRC_REGISTER_HASH_STRUCT Hash;

  Hash.Data = HashIn;
  BfOffset  = Hash.Bits.BfOffset;
  BfWidth   = Hash.Bits.BfWidth;
  Mask      = ((BfWidth >= 32) ? (0xFFFFFFFFUL) : ((1UL << BfWidth) - 1)) << BfOffset;
  return ((RegisterValue & ~Mask) | ((BitfieldValue << BfOffset) & Mask));
}

/**
  This function sets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetBitFieldS32 (
  IN const UINT32 HashIn,
  IN const INT32  BitfieldValue,
  IN const UINT32 RegisterValue
  )
{
  return (MrcHalSetBitField32 (HashIn, BitfieldValue, RegisterValue));
}

/**
  This function will determine if the group access is signed or unsigned and take care of sign extension.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to modify.

  @retval The register bit field value.
**/
INT64
MrcHalGsmGetBitField (
  IN MrcParameters *const MrcData,
  IN const MRC_REGISTER_HASH_STRUCT HashIn,
  IN const UINT64 RegisterValue
  )
{
  UINT64_STRUCT Value;

  Value.Data = RegisterValue;
  if (HashIn.Bits.RegSize == 0) {
    if (HashIn.Bits.BfSign == 0) {
      return (MrcHalGetBitField32 (HashIn.Data, Value.Data32.Low));
    } else {
      return (MrcHalGetBitFieldS32 (HashIn.Data, Value.Data32.Low));
    }
  } else {
    if (HashIn.Bits.BfSign == 0) {
      return (MrcHalGetBitField64 (MrcData, HashIn.Data, Value.Data));
    } else {
      return (MrcHalGetBitFieldS64 (MrcData, HashIn.Data, Value.Data));
    }
  }
}

/**
  This function will determine if the group access is signed or unsigned and take care of sign extension.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value to modify.
  @param[in] RegisterValue - The register value to modify.

  @retval The updated register.
**/
UINT64
MrcHalGsmSetBitField (
  IN MrcParameters *const MrcData,
  IN const MRC_REGISTER_HASH_STRUCT HashIn,
  IN const INT64  BitFieldValue,
  IN const UINT64 RegisterValue
  )
{
  IN INT64_STRUCT BfValue;
  IN UINT64_STRUCT Value;

  BfValue.Data = BitFieldValue;
  Value.Data = RegisterValue;
  if (HashIn.Bits.RegSize == 0) {
    if (HashIn.Bits.BfSign == 0) {
      return (MrcHalSetBitField32 (HashIn.Data, BfValue.Data32.Low, Value.Data32.Low));
    } else {
      return (MrcHalSetBitFieldS32 (HashIn.Data, BfValue.Data32.Low, Value.Data32.Low));
    }
  } else {
    if (HashIn.Bits.BfSign == 0) {
      return (MrcHalSetBitField64 (MrcData, HashIn.Data, BfValue.Data, Value.Data));
    } else {
      return (MrcHalSetBitFieldS64 (MrcData, HashIn.Data, BfValue.Data, Value.Data));
    }
  }
}

/**
  This function gets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalGetBitField32 (
  IN const UINT32 HashIn,
  IN const UINT32 RegisterValue
  )
{
  UINT32 BfWidth;
  MRC_REGISTER_HASH_STRUCT Hash;

  Hash.Data = HashIn;
  BfWidth   = Hash.Bits.BfWidth;
  return ((RegisterValue >> Hash.Bits.BfOffset) & ((BfWidth >= 32) ? (0xFFFFFFFFUL) : ((1UL << BfWidth) - 1)));
}

/**
  This function gets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
INT32
MrcHalGetBitFieldS32 (
  IN const UINT32 HashIn,
  IN const UINT32 RegisterValue
  )
{
  UINT32 Value;
  UINT32 BfWidth;
  MRC_REGISTER_HASH_STRUCT Hash;

  Hash.Data = HashIn;
  Value     = MrcHalGetBitField32 (HashIn, RegisterValue);
  BfWidth   = Hash.Bits.BfWidth;
  if (BfWidth < 32) {
    if (Value & (1 << (BfWidth - 1))) {
      Value |= ~((1 << BfWidth) - 1);
    }
  }
  return (Value);
}

/**
  This function sets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT64
MrcHalSetBitField64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const UINT64  BitfieldValue,
  IN const UINT64  RegisterValue
  )
{
  MRC_FUNCTION *Func;
  UINT64 Mask;
  UINT32 BfOffset;
  UINT32 BfWidth;
  MRC_REGISTER_HASH_STRUCT Hash;

  Hash.Data = HashIn;
  BfWidth   = Hash.Bits.BfWidth;
  if (BfWidth >= 64) {
    return (BitfieldValue);
  }
  BfOffset = Hash.Bits.BfOffset;
  Func     = MrcData->Inputs.Call.Func;
  Mask     = Func->MrcLeftShift64 ((Func->MrcLeftShift64 (1ULL, BfWidth) - 1), BfOffset);
  return ((RegisterValue & ~Mask) | (Func->MrcLeftShift64 (BitfieldValue, BfOffset) & Mask));
}

/**
  This function sets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT64
MrcHalSetBitFieldS64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const INT64   BitfieldValue,
  IN const UINT64  RegisterValue
  )
{
  return (MrcHalSetBitField64 (MrcData, HashIn, BitfieldValue, RegisterValue));
}

/**
  This function gets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT64
MrcHalGetBitField64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const UINT64  RegisterValue
  )
{
  MRC_FUNCTION *Func;
  UINT32 BfWidth;
  MRC_REGISTER_HASH_STRUCT Hash;

  Hash.Data = HashIn;
  BfWidth   = Hash.Bits.BfWidth;
  if (BfWidth >= 64) {
    return (RegisterValue);
  }
  Func = MrcData->Inputs.Call.Func;
  return ((Func->MrcRightShift64 (RegisterValue, Hash.Bits.BfOffset)) & (Func->MrcLeftShift64 (1ULL, BfWidth) - 1));
}

/**
  This function gets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
INT64
MrcHalGetBitFieldS64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const UINT64  RegisterValue
  )
{
  MRC_FUNCTION *Func;
  UINT64 Value;
  UINT64 Sign;
  UINT32 BfWidth;
  MRC_REGISTER_HASH_STRUCT Hash;

  Value     = MrcHalGetBitField64 (MrcData, HashIn, RegisterValue);
  Hash.Data = HashIn;
  BfWidth   = Hash.Bits.BfWidth;
  if (BfWidth < 64) {
    Func = MrcData->Inputs.Call.Func;
    Sign = Func->MrcLeftShift64 (1ULL, BfWidth - 1);
    if (Value & Sign) {
      Value |= ~(Func->MrcLeftShift64 (1ULL, BfWidth) - 1);
    }
  }
  return (Value);
}

/**
  This function sets the scheduler cbit disable ZQ control value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Value   - The value to set.
**/
void
MrcHalRmwRegSchedCbitDisableZq (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Value
  )
{
  UINT32 Offset;

  Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_SCHED_CBIT_REG, MCHBAR_CH1_CR_SCHED_CBIT_REG, Channel);
  MrcWriteCR (
    MrcData,
    Offset,
    MrcHalSetBfMcschedsCrSchedCbitDisZq (
      Value,
      MrcReadCR (
        MrcData,
        Offset
        )
      )
    );
  return;
}

/**
  This function gets the scheduler cbit disable ZQ control value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
UINT32
MrcHalGetRegSchedCbitDisableZq (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcHalGetBfMcschedsCrSchedCbitDisZq (
      MrcReadCR (
        MrcData,
        OFFSET_CALC_CH (MCHBAR_CH0_CR_SCHED_CBIT_REG, MCHBAR_CH1_CR_SCHED_CBIT_REG, Channel)
        )
      )
    );
}

/**
  This function sets the rcomp disable control.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Value   - The value to set.

  @retval The value written to the register.
**/
UINT32
MrcHalRmwRegDisableRcomp (
  IN MrcParameters *const MrcData,
  IN const UINT32  Value
  )
{
  return (
    MrcHalSetRegPcuCrPCompPcu (
      MrcData,
      MrcHalSetBfPcuCrPCompPcuCompDisable (
        Value,
        MrcHalGetRegPcuCrMCompPcu (
          MrcData
          )
        )
      )
    );
}

/**
  This function gets the rcomp disable control.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.

  @retval The value read from the register.
**/
UINT32
MrcHalGetRegDisableRcomp (
  IN MrcParameters *const MrcData
  )
{
  return (
    MrcHalGetBfPcuCrMCompPcuCompDisable (
      MrcHalGetRegPcuCrMCompPcu (
        MrcData
        )
      )
    );
}

/**
  This function gets the address as data control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
UINT32
MrcHalGetReutChPatWdbAddressAsData (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_WDB_ADDRESS_AS_DATA_CTRL_REG, MCHBAR_CH1_CR_REUT_CH_PAT_WDB_ADDRESS_AS_DATA_CTRL_REG, Channel)
      )
    );
}

/**
  This function configures the data in 0 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegQclkLdatDatain0 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_0_REG, MCHBAR_CH1_CR_QCLK_LDAT_DATAIN_0_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the data in 0 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
UINT32
MrcHalGetRegQclkLdatDatain0 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_0_REG, MCHBAR_CH1_CR_QCLK_LDAT_DATAIN_0_REG, Channel)
      )
    );
}

/**
  This function configures the data in 1 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegQclkLdatDatain1 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_1_REG, MCHBAR_CH1_CR_QCLK_LDAT_DATAIN_1_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the data in 1 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
UINT32
MrcHalGetRegQclkLdatDatain1 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_1_REG, MCHBAR_CH1_CR_QCLK_LDAT_DATAIN_1_REG, Channel)
      )
    );
}

/**
  This function configures the ldat sdat register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegQclkLdatSdat (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_QCLK_LDAT_SDAT_REG, MCHBAR_CH1_CR_QCLK_LDAT_SDAT_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the ldat pdat register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegQclkLdatPdat (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_QCLK_LDAT_PDAT_REG, MCHBAR_CH1_CR_QCLK_LDAT_PDAT_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the WDB pattern control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChPatWdbClCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_REG, MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the WDB pattern mux config register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChPatWdbClMuxCfg (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_REG, MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the WDB pattern mux config register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
UINT32
MrcHalGetRegReutChPatWdbClMuxCfg (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_REG, MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_REG, Channel)
      )
    );
}

/**
  This function gets the WDB write pattern buffer register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Index   - Zero based pattern buffer index.

  @retval The value read from the register.
**/
UINT32
MrcHalGetRegReutChPatWdbClMuxPbWr (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Index
  )
{
  //
  // Note that this implementation assumes that the width of each of the pattern buffers is the same.
  //
  return (
    MrcHalGetBfMchbarCh0CrReutChPatWdbClMuxPbWr0PatternBuffer (
      MrcReadCR (
        MrcData,
        OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_REG, MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_REG, Channel) +
        ((MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_1_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_REG) * Index)
        )
      )
    );
}

/**
  This function gets the WDB read pattern buffer register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Index   - Zero based pattern buffer index.

  @retval The value read from the register.
**/
UINT32
MrcHalGetRegReutChPatWdbClMuxPbRd (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Index
  )
{
  //
  // Note that this implementation assumes that the width of each of the pattern buffers is the same.
  //
  return (
    MrcHalGetBfMchbarCh0CrReutChPatWdbClMuxPbRd0PatternBuffer (
      MrcReadCR (
        MrcData,
        OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_REG, MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_REG, Channel) +
        ((MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_1_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_REG) * Index)
        )
      )
    );
}

/**
  This function configures the WDB pattern mux LMN register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChPatWdbClMuxLmn (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_REG, MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the WDB invert dc register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChPatWdbInv (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_WDB_INV_REG, MCHBAR_CH1_CR_REUT_CH_PAT_WDB_INV_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the WDB invert dc register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
UINT32
MrcHalGetRegReutChPatWdbInv (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_WDB_INV_REG, MCHBAR_CH1_CR_REUT_CH_PAT_WDB_INV_REG, Channel)
      )
    );
}

/**
  This function configures the WDB data invert register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT64
MrcHalSetRegReutChPatWdbDataInv (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT64  RegisterValue
  )
{
  return (
    MrcWriteCR64 (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_WDB_DATA_INV_REG, MCHBAR_CH1_CR_REUT_CH_PAT_WDB_DATA_INV_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the CADB control.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChPatCadbCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CTRL_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_CTRL_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the CADB control.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
UINT32
MrcHalGetRegReutChPatCadbCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CTRL_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_CTRL_REG, Channel)
      )
    );
}

/**
  This function configures the CADB pattern write pointer.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetReutChPatCadbWritePointer (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_WRITE_POINTER_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_WRITE_POINTER_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the CADB pattern write pointer.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
UINT32
MrcHalGetReutChPatCadbWritePointer (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_WRITE_POINTER_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_WRITE_POINTER_REG, Channel)
      )
    );
}

/**
  This function configures the CADB pattern.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT64
MrcHalSetReutChPatCadbProg (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT64  RegisterValue
  )
{
  return (
    MrcWriteCR64 (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_PROG_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_PROG_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the CADB pattern.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value read from sthe register.
**/
UINT64
MrcHalGetReutChPatCadbProg (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR64 (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_PROG_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_PROG_REG, Channel)
      )
    );
}

/**
  This function configures the CADB unisequencer mode.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetReutChPatCadbMuxCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_CTRL_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_CTRL_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the CADB unisequencer mode.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
UINT32
MrcHalGetReutChPatCadbMuxCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_CTRL_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_CTRL_REG, Channel)
      )
    );
}

/**
  This function configures the CADB deselect mux pattern buffer 0 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChPatCadbMuxPb0 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_0_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_PB_0_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the CADB deselect mux pattern buffer 1 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChPatCadbMuxPb1 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_1_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_PB_1_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the CADB deselect mux pattern buffer 2 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChPatCadbMuxPb2 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_2_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_PB_2_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the CADB select mux pattern buffer 0 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChPatCadbSelMuxPb0 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_0_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_0_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the CADB select mux pattern buffer 1 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChPatCadbSelMuxPb1 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_1_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_1_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the CADB select mux pattern buffer 2 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChPatCadbSelMuxPb2 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_2_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_2_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the CADB pattern mux LMN register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChPatCadbClMuxLmn (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_REG, MCHBAR_CH1_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the CADB pattern mux LMN register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChSeqDummyreadCtlMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_1_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the CADB dummy read mask register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChSeqDummyreadMaskMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_1_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the CADB dummy read mask register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
UINT32
MrcHalGetRegReutChSeqDummyreadMaskMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_1_REG, Channel)
      )
    );
}

/**
  This function configures the dummy read logical to physical mapping.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChSeqRankLogicalToPhysicalMappingMcMain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the dummy read logical to physical mapping.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
UINT32
MrcHalGetRegReutChSeqRankLogicalToPhysicalMappingMcMain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG, Channel)
      )
    );
}

/**
  This function configures the bank logical to physical mapping.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT64
MrcHalSetRegReutChSeqBankLogicalToPhysicalMappingMcMain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT64  RegisterValue
  )
{
  return (
    MrcWriteCR64 (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the bank logical to physical mapping.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
UINT64
MrcHalGetRegReutChSeqBankLogicalToPhysicalMappingMcMain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR64 (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_REG, Channel)
      )
    );
}

/**
  This function configures the subsequence control.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] Index         - Zero based subsequence number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChSubseqCtlMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Index,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_REG, MCDFXS_CR_REUT_CH1_SUBSEQ_CTL_MCMAIN_0_REG, Channel) +
      ((MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_1_REG - MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_REG) * Index),
      RegisterValue
      )
    );
}

/**
  This function configures the subsequence offset control.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] Index         - Zero based subsequence number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChSubseqOffsetCtlMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Index,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH0_SUBSEQ_OFFSET_CTL_MCMAIN_0_REG, MCDFXS_CR_REUT_CH1_SUBSEQ_OFFSET_CTL_MCMAIN_0_REG, Channel) +
      ((MCDFXS_CR_REUT_CH0_SUBSEQ_OFFSET_CTL_MCMAIN_1_REG - MCDFXS_CR_REUT_CH0_SUBSEQ_OFFSET_CTL_MCMAIN_0_REG) * Index),
      RegisterValue
      )
    );
}

/**
  This function sets the sequence configuration.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT64
MrcHalSetRegReutChSeqCfgMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT64  RegisterValue
  )
{
  return (
    MrcWriteCR64 (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the sequence configuration.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
UINT64
MrcHalGetRegReutChSeqCfgMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR64 (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG, Channel)
      )
    );
}

/**
  This function configures the sequence loop count limit.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] ChannelIn     - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChSeqLoopcountLimitMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  ChannelIn,
  IN const UINT32  RegisterValue
  )
{
  UINT32 Channel;
  UINT32 ChannelStart;
  UINT32 ChannelEnd;
  UINT32 Value;

  if (ChannelIn >= MAX_CHANNEL) {
    ChannelStart = 0;
    ChannelEnd   = MAX_CHANNEL - 1;
  } else {
    ChannelStart = ChannelIn;
    ChannelEnd   = ChannelIn;
  }
  Value = 0;
  for (Channel = ChannelStart; Channel <= ChannelEnd; Channel++) {
    Value = MrcWriteCR (
              MrcData,
              OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_1_REG, Channel),
              RegisterValue
              );
  }
  return (Value);
}

/**
  This function configures the sequence base address order carry invert control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChSeqBaseAddrOrderCarryInvertCtlMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_1_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the sequence base address order carry invert control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
UINT32
MrcHalGetRegReutChSeqBaseAddrOrderCarryInvertCtlMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_1_REG, Channel)
      )
    );
}

/**
  This function configures the error control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChErrCtl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG, MCHBAR_CH1_CR_REUT_CH_ERR_CTL_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the error control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
UINT32
MrcHalGetRegReutChErrCtl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG, MCHBAR_CH1_CR_REUT_CH_ERR_CTL_REG, Channel)
      )
    );
}

/**
  This function configures the error counter control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] Counter       - Zero based counter number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChErrCounterCtl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Counter,
  IN const UINT32  RegisterValue
  )
{
  UINT32 CounterOffset;

  CounterOffset = (MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_1_REG - MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_0_REG) * Counter;
  if (Channel >= MAX_CHANNEL) {
    return (
      MrcWriteCrMulticast (
        MrcData,
        MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_0_REG + CounterOffset,
        RegisterValue
        )
      );
  } else {
    return (
      MrcWriteCR (
        MrcData,
        OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_0_REG, MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_0_REG, Channel) + CounterOffset,
        RegisterValue
        )
      );
  }
}

/**
  This function gets the error counter control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] Counter       - Zero based counter number in the memory controller.

  @retval The value written to the register.
**/
UINT32
MrcHalGetRegReutChErrCounterCtl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Counter
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_0_REG, MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_0_REG, Channel) +
      ((MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_1_REG - MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_0_REG) * Counter)
      )
    );
}

/**
  This function configures the error data mask register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT64
MrcHalSetRegReutChErrDataMask (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT64  RegisterValue
  )
{
  return (
    MrcWriteCR64 (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_ERR_DATA_MASK_REG, MCHBAR_CH1_CR_REUT_CH_ERR_DATA_MASK_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the error ECC mask register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChErrEccMask (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_ERR_ECC_MASK_REG, MCHBAR_CH1_CR_REUT_CH_ERR_ECC_MASK_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the error counter status register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Channel         - Zero based channel number in the memory controller.
  @param[in] Counter         - Zero based counter number in the memory controller.
  @param[in, out] ErrorCount - The current error counter value.

  @retval TRUE if an overflow occurred, otherwise FALSE.
**/
BOOLEAN
MrcHalGetRegReutChErrCounterStatus (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Counter,
  IN OUT UINT32    *const ErrorCount
  )
{
  if ((MrcReadCR (
         MrcData,
         OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_REG,
           MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_REG, Channel)) &
       (1 << Counter)) != 0) {
    *ErrorCount = MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_Counter_Status_MAX + 1;
    return TRUE;
  } else {
    *ErrorCount = MrcReadCR (
                    MrcData,
                    OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG, MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG, Channel) +
                    ((MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_1_REG - MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG) * Counter)
                    );
    return FALSE;
  }
}

/**
  This function gets the error status register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
UINT64
MrcHalGetReutChErrChunkRankByteNthStatus (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR64 (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG, MCHBAR_CH1_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG, Channel)
      )
    );
}

/**
  This function configures the sequence control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChSeqCtlMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_CTL_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_CTL_MCMAIN_1_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the scrambler register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegDdrscramble (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (DDRSCRAM_CR_DDRSCRAMBLECH0_REG, DDRSCRAM_CR_DDRSCRAMBLECH1_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the scrambler register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
UINT32
MrcHalGetRegDdrscramble (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (DDRSCRAM_CR_DDRSCRAMBLECH0_REG, DDRSCRAM_CR_DDRSCRAMBLECH1_REG, Channel)
      )
    );
}

/**
  This function configures the miscellaneous refresh control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChMiscRefreshCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG, MCHBAR_CH1_CR_REUT_CH_MISC_REFRESH_CTRL_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the miscellaneous ZQ control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChMiscZqCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_MISC_ZQ_CTRL_REG, MCHBAR_CH1_CR_REUT_CH_MISC_ZQ_CTRL_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the miscellaneous ODT control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChMiscOdtCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG, MCHBAR_CH1_CR_REUT_CH_MISC_ODT_CTRL_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the miscellaneous ODT control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChMiscCkeCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG, MCHBAR_CH1_CR_REUT_CH_MISC_CKE_CTRL_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function configures the sequence row address swizzle lower register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegReutChSeqRowAddrSwizzleLowerMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_MCMAIN_1_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the sequence row address swizzle lower register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
UINT32
MrcHalGetRegReutChSeqRowAddrSwizzleLowerMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_MCMAIN_1_REG, Channel)
      )
    );
}

/**
  This function configures the sequence row address swizzle upper register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT64
MrcHalSetRegReutChSeqRowAddrSwizzleUpperMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT64  RegisterValue
  )
{
  return (
    MrcWriteCR64 (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_MCMAIN_1_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the sequence row address swizzle upper register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value read from the register.
**/
UINT64
MrcHalGetRegReutChSeqRowAddrSwizzleUpperMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR64 (
      MrcData,
      OFFSET_CALC_CH (MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_MCMAIN_0_REG, MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_MCMAIN_1_REG, Channel)
      )
    );
}

/**
  This function sets the receive training per bit register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] Bit           - Zero based bit number in the byte.
  @param[in] BitFieldValue - The register bitfield value.
  @param[in] RegisterValue - The starting register value.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRxperbitrankLane (
  IN const UINT32 Bit,
  IN const UINT32 BitFieldValue,
  IN const UINT32 RegisterValue
  )
{
  UINT32 Mask;
  UINT32 Shift;

  Shift = DDRDATA0CH0_CR_RXPERBITRANK0_Lane0_WID * Bit;
  Mask  = DDRDATA0CH0_CR_RXPERBITRANK0_Lane0_MSK << Shift;
  return ((RegisterValue & ~Mask)  | (BitFieldValue & DDRDATA0CH0_CR_RXPERBITRANK0_Lane0_MSK) << Shift);
}

/**
  This function sets the transmit training per bit register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] Rank          - Zero based rank number in the channel.
  @param[in] Byte          - Zero based byte number in the rank.
  @param[in] RegisterValue - The starting register value.

  @retval The value written to the register.
**/
UINT32
MrcHalSetRegTxperbitrank (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Rank,
  IN const UINT32  Byte,
  IN const UINT32  RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (DDRDATA0CH0_CR_TXPERBITRANK0_REG, DDRDATA0CH1_CR_TXPERBITRANK0_REG, Channel) +
      ((DDRDATA0CH0_CR_TXPERBITRANK1_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG) * Rank) +
      ((DDRDATA1CH0_CR_TXPERBITRANK0_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG) * Byte),
      RegisterValue
      )
    );
}

/**
  This function gets the transmit training per bit register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] Rank          - Zero based rank number in the channel.
  @param[in] Byte          - Zero based byte number in the rank.
  @param[in] Bit           - Zero based bit number in the byte.

  @retval The value read from the register.
**/
INT8
MrcHalGetRegTxperbitrank (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Rank,
  IN const UINT32  Byte,
  IN const UINT32  Bit
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (
                    MrcData,
                    OFFSET_CALC_CH (DDRDATA0CH0_CR_TXPERBITRANK0_REG, DDRDATA0CH1_CR_TXPERBITRANK0_REG, Channel) +
                    ((DDRDATA0CH0_CR_TXPERBITRANK1_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG) * Rank) +
                    ((DDRDATA1CH0_CR_TXPERBITRANK0_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG) * Byte)
                    );
  return ((RegisterValue >> (DDRDATA0CH0_CR_TXPERBITRANK0_Lane0_WID * Bit)) & DDRDATA0CH0_CR_TXPERBITRANK0_Lane0_MSK);
}

/**
  This function sets the transmit training per bit register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] Bit           - Zero based bit number in the byte.
  @param[in] BitFieldValue - The register bitfield value.
  @param[in] RegisterValue - The starting register value.

  @retval The value written to the register.
**/
UINT32
MrcHalSetTxperbitrankLane (
  IN const UINT32 Bit,
  IN const UINT32 BitFieldValue,
  IN const UINT32 RegisterValue
  )
{
  UINT32 Mask;
  UINT32 Shift;

  Shift = DDRDATA0CH0_CR_TXPERBITRANK0_Lane0_WID * Bit;
  Mask  = DDRDATA0CH0_CR_TXPERBITRANK0_Lane0_MSK << Shift;
  return ((RegisterValue & ~Mask)  | (BitFieldValue & DDRDATA0CH0_CR_TXPERBITRANK0_Lane0_MSK) << Shift);
}

/**
  This function gets the transmit training register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData     - Include all MRC global data.
  @param[in] Channel     - Zero based channel number in the memory controller.
  @param[in] Rank        - Zero based rank number in the channel.
  @param[in] Byte        - Zero based byte number in the rank.
  @param[in] MarginGroup - Margin group index.

  @retval The value read from the register.
**/
INT16
MrcHalGetRegTxtrainrank (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Rank,
  IN const UINT32  Byte,
  IN const GSM_GT  MarginGroup
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (
                    MrcData,
                    OFFSET_CALC_CH (DDRDATA0CH0_CR_TXTRAINRANK0_REG, DDRDATA0CH1_CR_TXTRAINRANK0_REG, Channel) +
                    ((DDRDATA0CH0_CR_TXTRAINRANK1_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Rank) +
                    ((DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Byte)
                    );
  switch (MarginGroup) {
    case TxDqsDelay:
      return ((INT16) MrcHalGetBfDdrdata0ch0CrTxtrainrank0Txdqsdelay (RegisterValue));
    case TxDqDelay:
      return ((INT16) MrcHalGetBfDdrdata0ch0CrTxtrainrank0Txdqdelay (RegisterValue));
    case TxEq:
      return ((INT16) MrcHalGetBfDdrdata0ch0CrTxtrainrank0Txequalization (RegisterValue));
    default:
      break;
  }
  return (0);
}

/**
  This function sets the transmit Vref register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Value   - The new bitfield vref value.
  @param[in] Enable  - The new bitfield enable value.
**/
void
MrcHalSetRegVrefadjust1 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Value,
  IN const UINT32  Enable
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (MrcData, DDRDATA0CH0_CR_DDRCRVREFADJUST1_REG);
  if (Channel == cCHANNEL0) {
    if (Value != MRC_IGNORE_ARG) {
      RegisterValue = MrcHalSetBfDdrdata0ch0CrDdrcrvrefadjust1Ch0vrefctl (Value, RegisterValue);
    }
    if (Enable != MRC_IGNORE_ARG) {
      RegisterValue = MrcHalSetBfDdrdata0ch0CrDdrcrvrefadjust1Endimmvrefch0 (Enable, RegisterValue);
    }
  } else if (Channel == cCHANNEL1) {
    if (Value != MRC_IGNORE_ARG) {
      RegisterValue = MrcHalSetBfDdrdata0ch0CrDdrcrvrefadjust1Ch1vrefctl (Value, RegisterValue);
    }
    if (Enable != MRC_IGNORE_ARG) {
      RegisterValue = MrcHalSetBfDdrdata0ch0CrDdrcrvrefadjust1Endimmvrefch1 (Enable, RegisterValue);
    }
  } else {
    if (Value != MRC_IGNORE_ARG) {
      RegisterValue = MrcHalSetBfDdrdata0ch0CrDdrcrvrefadjust1Cavrefctl (Value, RegisterValue);
    }
    if (Enable != MRC_IGNORE_ARG) {
      RegisterValue = MrcHalSetBfDdrdata0ch0CrDdrcrvrefadjust1Endimmvrefca (Enable, RegisterValue);
    }
  }
  MrcWriteCR (MrcData, DDRDATA0CH0_CR_DDRCRVREFADJUST1_REG, RegisterValue);
  return;
}

/**
  This function gets the transmit Vref register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData     - Include all MRC global data.
  @param[in] Channel     - Zero based channel number in the memory controller or >= MAX_CHANNEL to get command voltage.
  @param[in, out] Enable - TRUE if enabled otherwise FALSE.

  @retval The value read from the register.
**/
INT16
MrcHalGetRegVrefadjust1 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN OUT BOOLEAN   *const Enable
  )
{
  UINT32 RegisterValue;
  INT16 Offset;

  RegisterValue = MrcReadCR (MrcData, DDRDATA0CH0_CR_DDRCRVREFADJUST1_REG);
  if (Channel == cCHANNEL0) {
    *Enable = (BOOLEAN) MrcHalGetBfDdrdata0ch0CrDdrcrvrefadjust1Endimmvrefch0 (RegisterValue);
    Offset = (*Enable == 0) ? 0 : (INT16) MrcHalGetBfDdrdata0ch0CrDdrcrvrefadjust1Ch0vrefctl (RegisterValue);
  } else if (Channel == cCHANNEL1) {
    *Enable = (BOOLEAN) MrcHalGetBfDdrdata0ch0CrDdrcrvrefadjust1Endimmvrefch1 (RegisterValue);
    Offset = (*Enable == 0) ? 0 : (INT16) MrcHalGetBfDdrdata0ch0CrDdrcrvrefadjust1Ch1vrefctl (RegisterValue);
  } else {
    *Enable = (BOOLEAN) MrcHalGetBfDdrdata0ch0CrDdrcrvrefadjust1Endimmvrefca (RegisterValue);
    Offset = (*Enable == 0) ? 0 : (INT16) MrcHalGetBfDdrdata0ch0CrDdrcrvrefadjust1Cavrefctl (RegisterValue);
  }
  return (Offset);
}

/**
  This function sets the clock PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Rank    - Zero based rank number in the channel.
  @param[in] Value   - The new value.

  @retval The value written to the register.
**/
UINT32
MrcHalRmwRegClkClkPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Rank,
  IN const UINT32  Value
  )
{
  UINT32 Offset;
  UINT32 Mask;
  UINT32 Shift;

  Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DDRCRCLKPICODE_REG, DDRCLKCH1_CR_DDRCRCLKPICODE_REG, Channel);
  Shift  = DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_WID * Rank;
  Mask   = DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MSK << Shift;
  return (MrcWriteCR (MrcData, Offset, ((MrcReadCR (MrcData, Offset) & ~Mask)  | ((Value & DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MSK) << Shift))));
}

/**
  This function gets the clock PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] Rank          - Zero based rank number in the channel.

  @retval The value read from the register.
**/
UINT16
MrcHalGetRegClkClkPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Rank
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (MrcData, OFFSET_CALC_CH (DDRCLKCH0_CR_DDRCRCLKPICODE_REG, DDRCLKCH1_CR_DDRCRCLKPICODE_REG, Channel));
  return ((RegisterValue >> (DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_WID * Rank)) & DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MSK);
}

/**
  This function sets the command N PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] PiOffset      - The PI code offset.
  @param[in] Value         - The starting register value.

  @retval The value read from the register.
**/
UINT32
MrcHalRmwRegCmdnCmdPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset,
  IN const UINT32  Value
  )
{
  UINT32 Offset;
  UINT32 Mask;
  UINT32 Shift;

  Offset = OFFSET_CALC_CH (DDRCMDNCH0_CR_DDRCRCMDPICODING_REG, DDRCMDNCH1_CR_DDRCRCMDPICODING_REG, Channel);
  Shift  = DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_WID * PiOffset;
  Mask   = DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MSK << Shift;
  return (MrcWriteCR (MrcData, Offset, ((MrcReadCR (MrcData, Offset) & ~Mask)  | ((Value & DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MSK) << Shift))));
}

/**
  This function gets the command N PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Offset  - Command PI code offset.

  @retval The value read from the register.
**/
UINT16
MrcHalGetRegCmdnCmdPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Offset
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (MrcData, OFFSET_CALC_CH (DDRCMDNCH0_CR_DDRCRCMDPICODING_REG, DDRCMDNCH1_CR_DDRCRCMDPICODING_REG, Channel));
  return ((RegisterValue >> (DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_WID * Offset)) & DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MSK);
}

/**
  This function sets the command S PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] PiOffset      - The PI code offset.
  @param[in] Value         - The starting register value.

  @retval The value read from the register.
**/
UINT32
MrcHalRmwRegCmdsCmdPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset,
  IN const UINT32  Value
  )
{
  UINT32 Offset;
  UINT32 Mask;
  UINT32 Shift;

  Offset = OFFSET_CALC_CH (DDRCMDSCH0_CR_DDRCRCMDPICODING_REG, DDRCMDSCH1_CR_DDRCRCMDPICODING_REG, Channel);
  Shift  = DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_WID * PiOffset;
  Mask   = DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MSK << Shift;
  return (MrcWriteCR (MrcData, Offset, ((MrcReadCR (MrcData, Offset) & ~Mask)  | ((Value & DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MSK) << Shift))));
}

/**
  This function gets the command S PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Offset  - Zero based pi offset.

  @retval The value read from the register.
**/
UINT16
MrcHalGetRegCmdsCmdPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Offset
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (MrcData, OFFSET_CALC_CH (DDRCMDSCH0_CR_DDRCRCMDPICODING_REG, DDRCMDSCH1_CR_DDRCRCMDPICODING_REG, Channel));
  return ((RegisterValue >> (DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_WID * Offset)) & DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MSK);
}


/**
  This function sets the command CKE PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Zero based channel number in the memory controller.
  @param[in] PiOffset - Zero based pi offset.
  @param[in] Value    - The starting register value.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalRmwRegCkeCmdPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset,
  IN const UINT32  Value
  )
{
  UINT32 Offset;
  UINT32 Mask;
  UINT32 Shift;

  Offset = OFFSET_CALC_CH (DDRCKECH0_CR_DDRCRCMDPICODING_REG, DDRCKECH1_CR_DDRCRCMDPICODING_REG, Channel);
  Shift  = DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_WID * PiOffset;
  Mask   = DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_MSK << Shift;
  return (MrcWriteCR (MrcData, Offset, ((MrcReadCR (MrcData, Offset) & ~Mask)  | ((Value & DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_MSK) << Shift))));
}

/**
  This function gets the command CKE PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData   - Include all MRC global data.
  @param[in] Channel   - Zero based channel number in the memory controller.
  @param[in] PiOffset  - Zero based pi offset.

  @retval The value read from the register.
**/
INT16
MrcHalGetRegCkeCmdPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (MrcData, OFFSET_CALC_CH (DDRCKECH0_CR_DDRCRCMDPICODING_REG, DDRCKECH1_CR_DDRCRCMDPICODING_REG, Channel));
  return ((RegisterValue >> (DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_WID * PiOffset)) & DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_MSK);
}

/**
  This function sets the control command PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Zero based channel number in the memory controller.
  @param[in] PiOffset - The PI code offset.
  @param[in] Value    - The starting register value.

  @retval The value read from the register.
**/
UINT32
MrcHalRmwRegCtlCtlPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset,
  IN const UINT32  Value
  )
{
  UINT32 Offset;
  UINT32 Mask;
  UINT32 Shift;

  Offset = OFFSET_CALC_CH (DDRCTLCH0_CR_DDRCRCTLPICODING_REG, DDRCTLCH1_CR_DDRCRCTLPICODING_REG, Channel);
  Shift  = DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_WID * PiOffset;
  Mask   = DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_MSK << Shift;
  return (MrcWriteCR (MrcData, Offset, ((MrcReadCR (MrcData, Offset) & ~Mask)  | ((Value & DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_MSK) << Shift))));
}

/**
  This function gets the control command PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] PiOffset      - The PI code offset.

  @retval The value read from the register.
**/
INT16
MrcHalGetRegCtlCtlPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (MrcData, OFFSET_CALC_CH (DDRCTLCH0_CR_DDRCRCTLPICODING_REG, DDRCTLCH1_CR_DDRCRCTLPICODING_REG, Channel));
  return ((RegisterValue >> (DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_WID * PiOffset)) & DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_MSK);
}

/**
  This function sets the CKE control PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Zero based channel number in the memory controller.
  @param[in] PiOffset - The PI code offset.
  @param[in] Value    - The starting register value.

  @retval The value read from the register.
**/
UINT32
MrcHalRmwRegCkeCtlPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset,
  IN const UINT32  Value
  )
{
  UINT32 Offset;
  UINT32 Mask;
  UINT32 Shift;

  Offset = OFFSET_CALC_CH (DDRCKECH0_CR_DDRCRCTLPICODING_REG, DDRCKECH1_CR_DDRCRCTLPICODING_REG, Channel);
  Shift  = DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_WID * PiOffset;
  Mask   = DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_MSK << Shift;
  return (MrcWriteCR (MrcData, Offset, ((MrcReadCR (MrcData, Offset) & ~Mask)  | ((Value & Mask) << Shift))));
}

/**
  This function gets the CKE control PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] PiOffset      - The PI code offset.

  @retval The value read from the register.
**/
INT16
MrcHalGetRegCkeCtlPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (MrcData, OFFSET_CALC_CH (DDRCKECH0_CR_DDRCRCTLPICODING_REG, DDRCKECH1_CR_DDRCRCTLPICODING_REG, Channel));
  return ((RegisterValue >> (DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_WID * PiOffset)) & DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_MSK);
}
#endif // SSA_FLAG

/**
  Program MCHBAR_CHx_CR_SC_IO_LATENCY register using Host data.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Channel to work on.
**/
void
MrcHalSetIoLatency (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  )
{
  const MrcChannelOut                 *ChannelOut;
  const UINT8                         *IoLatency;
  MCHBAR_CH0_CR_SC_IO_LATENCY_STRUCT  ScIoLatency;
  UINT32                              Offset;

  ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
  IoLatency = ChannelOut->IoLatency;

  ScIoLatency.Data = 0;
  ScIoLatency.Bits.Rank_0_flyby = MIN (IoLatency[0], MCHBAR_CH0_CR_SC_IO_LATENCY_Rank_0_flyby_MAX);
  ScIoLatency.Bits.Rank_1_flyby = MIN (IoLatency[1], MCHBAR_CH0_CR_SC_IO_LATENCY_Rank_1_flyby_MAX);
  ScIoLatency.Bits.Rank_2_flyby = MIN (IoLatency[2], MCHBAR_CH0_CR_SC_IO_LATENCY_Rank_2_flyby_MAX);
  ScIoLatency.Bits.Rank_3_flyby = MIN (IoLatency[3], MCHBAR_CH0_CR_SC_IO_LATENCY_Rank_3_flyby_MAX);
  ScIoLatency.Bits.IO_Latency_offset = MIN (ChannelOut->RTIoComp, MCHBAR_CH0_CR_SC_IO_LATENCY_IO_Latency_offset_MAX);
  ScIoLatency.Bits.RFR_delay = HW_RFR_DELAY;

  Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_SC_IO_LATENCY_REG, MCHBAR_CH1_CR_SC_IO_LATENCY_REG, Channel);
  MrcWriteCR (MrcData, Offset, ScIoLatency.Data);
}

/**
  Program MCHBAR_CHx_CR_SC_ROUNDTRIP_LATENCY register using Host data.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Channel to work on.
**/
void
MrcHalSetRoundtripLatency (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  )
{
  const UINT8                               *RtLatency;
  MCHBAR_CH0_CR_SC_ROUNDTRIP_LATENCY_STRUCT ScRoundtripLatency;
  UINT32                                    Offset;

  RtLatency = MrcData->Outputs.Controller[0].Channel[Channel].RTLatency;

  ScRoundtripLatency.Data = 0;
  ScRoundtripLatency.Bits.Rank_0_latency = MIN (RtLatency[0], MCHBAR_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_MAX);
  ScRoundtripLatency.Bits.Rank_1_latency = MIN (RtLatency[1], MCHBAR_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_MAX);
  ScRoundtripLatency.Bits.Rank_2_latency = MIN (RtLatency[2], MCHBAR_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_MAX);
  ScRoundtripLatency.Bits.Rank_3_latency = MIN (RtLatency[3], MCHBAR_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_MAX);

  Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_SC_ROUNDTRIP_LATENCY_REG, MCHBAR_CH1_CR_SC_ROUNDTRIP_LATENCY_REG, Channel);
  MrcWriteCR (MrcData, Offset, ScRoundtripLatency.Data);
}

/**
  Read MCHBAR_CHx_CR_SC_ROUNDTRIP_LATENCY register value.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Channel to work on.

  @retval The value read from the register.
**/
UINT32
MrcHalGetRoundtripLatency (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_SC_ROUNDTRIP_LATENCY_REG, MCHBAR_CH1_CR_SC_ROUNDTRIP_LATENCY_REG, Channel)
      )
    );
}

#ifdef SSA_FLAG
/**
  This function gets the date error status register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
UINT64
MrcHalGetRegErrDataStatus (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    MrcReadCR64 (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_ERR_DATA_STATUS_REG, MCHBAR_CH1_CR_REUT_CH_ERR_DATA_STATUS_REG, Channel)
      )
    );
}

/**
  This function returns the current status of the REUT engine.

  @param[in]  MrcData   - Include all MRC global data.
  @param[out] TestDone  - Channel bit mask indicating which channels are done executing.
  @param[out] TestError - Channel bit mask indicating which channels have a test error.
**/
void
MrcHalGetReutGlobalStatus (
  IN MrcParameters *const MrcData,
  OUT UINT32       *const TestDone,
  OUT UINT32       *const TestError
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcHalGetRegMcdfxsCrReutGlobalErrMcmain (MrcData);
  *TestDone     = MrcHalGetBfMcdfxsCrReutGlobalErrMcmainChannelTestDoneStatus0 (RegisterValue) |
    MrcHalGetBfMcdfxsCrReutGlobalErrMcmainChannelTestDoneStatus1 (RegisterValue) << 1;
  *TestError    = MrcHalGetBfMcdfxsCrReutGlobalErrMcmainChannelErrorStatus0 (RegisterValue) |
    MrcHalGetBfMcdfxsCrReutGlobalErrMcmainChannelErrorStatus1 (RegisterValue) << 1;
  return;
}

/**
  This function gets the CKE mapping value for the selected channel.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The register bitfield value.
**/
UINT32
MrcHalGetCkeMapping (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL0_REG);
  if (Channel != 0) {
    return (MrcHalGetBfDdrscramCrDdrmisccontrol0Ckemappingch1 (RegisterValue));
  } else {
    return (MrcHalGetBfDdrscramCrDdrmisccontrol0Ckemappingch0 (RegisterValue));
  }
}

/**
  This function gets the current subsequence loopcount value for the selected channel.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The register bitfield value.
**/
UINT32
MrcHalGetSeqLoopcountStatus (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (
                    MrcData,
                    OFFSET_CALC_CH (
                      MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_STATUS_MCMAIN_0_REG,
                      MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_STATUS_MCMAIN_1_REG,
                      Channel
                      )
                    );
  return MrcHalGetBfMcdfxsCrReutChSeqLoopcountStatusMcmain0CurrentLoopcount (RegisterValue);
}

/**
  This function gets the current subsequence pointer value for the selected channel.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The register bitfield value.
**/
UINT32
MrcHalGetSeqPointer (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (
                    MrcData,
                    OFFSET_CALC_CH (
                      MCDFXS_CR_REUT_CH_SEQ_SUBSEQ_PNTR_MCMAIN_0_REG,
                      MCDFXS_CR_REUT_CH_SEQ_SUBSEQ_PNTR_MCMAIN_1_REG,
                      Channel
                      )
                    );
  return MrcHalGetBfMcdfxsCrReutChSeqSubseqPntrMcmain0CurrentSubsequencePointer (RegisterValue);
}

/**
  This function gets the current subsequence cacheline value for the selected channel.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The register bitfield value.
**/
UINT32
MrcHalGetSeqCurrentCacheline (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (
                    MrcData,
                    OFFSET_CALC_CH (
                      MCDFXS_CR_REUT_CH_SEQ_CACHELINE_STATUS_MCMAIN_0_REG,
                      MCDFXS_CR_REUT_CH_SEQ_CACHELINE_STATUS_MCMAIN_1_REG,
                      Channel
                      )
                    );
  return MrcHalGetBfMcdfxsCrReutChSeqCachelineStatusMcmain0CurrentCacheline (RegisterValue);
}

/**
  This function gets the value from the base address current register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The register value.
**/
UINT64
MrcHalGetBaseAddressCurrent (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  )
{
  return MrcReadCR64 (
           MrcData,
           OFFSET_CALC_CH (
             MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_CURRENT_MCMAIN_0_REG,
             MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_CURRENT_MCMAIN_1_REG,
             Channel
             )
           );
}

/**
  This function gets the value from the offset address current register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The register value.
**/
UINT64
MrcHalGetOffsetAddressCurrent (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  )
{
  return MrcReadCR64 (
           MrcData,
           OFFSET_CALC_CH (
             MCDFXS_CR_REUT_CH_SEQ_OFFSET_ADDR_CURRENT_MCMAIN_0_REG,
             MCDFXS_CR_REUT_CH_SEQ_OFFSET_ADDR_CURRENT_MCMAIN_1_REG,
             Channel
             )
           );
}

/**
  This function gets address of the most current error.

  @param[in]  MrcData - Include all MRC global data.
  @param[in]  Channel - Zero based channel number in the memory controller.
  @param[out] Rank    - Pointer to buffer containing rank address.
  @param[out] Bank    - Pointer to buffer containing bank address.
  @param[out] Row     - Pointer to buffer containing row address.
  @param[out] Col     - Pointer to buffer containing column address.

**/
void
MrcHalGetReutChErrorAddress (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  OUT UINT8               *Rank,
  OUT UINT8               *Bank,
  OUT UINT32              *Row,
  OUT UINT16              *Col
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcReadCR (
                    MrcData,
                    OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_ERROR_ADDR_REG, MCHBAR_CH1_CR_REUT_CH_ERROR_ADDR_REG, Channel)
                    );
  *Rank = (UINT8)  MrcHalGetBfMchbarCh0CrReutChErrorAddrRankAddress (MrcData, RegisterValue);
  *Bank = (UINT8)  MrcHalGetBfMchbarCh0CrReutChErrorAddrBankAddress (MrcData, RegisterValue);
  *Row  = (UINT32) MrcHalGetBfMchbarCh0CrReutChErrorAddrRowAddress (MrcData, RegisterValue);
  *Col  = (UINT16) MrcHalGetBfMchbarCh0CrReutChErrorAddrColumnAddress (MrcData, RegisterValue);
  return;
}

/**
  This function gets the WDB capture control register.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value read from the register.
**/
UINT32
MrcHalGetReutWdbCaptureControl (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  )
{
  return (
    MrcReadCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_WDB_CAPTURE_CTL_REG, MCHBAR_CH1_CR_REUT_CH_WDB_CAPTURE_CTL_REG, Channel)
      )
    );
}

/**
  This function configures the WDB capture control register.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetReutWdbCaptureControl (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel,
  IN const UINT32         RegisterValue
  )
{
  return (
    MrcWriteCR (
      MrcData,
      OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_WDB_CAPTURE_CTL_REG, MCHBAR_CH1_CR_REUT_CH_WDB_CAPTURE_CTL_REG, Channel),
      RegisterValue
      )
    );
}

/**
  This function gets the current write data buffer capture pointer.

  @param[in] MrcData                   - Include all MRC global data.
  @param[in] Channel                   - Zero based channel number.

  @retval Value of current capture pointer bitfield
**/
UINT8
MrcHalGetReutWdbCurrentCapturePointer (
  IN MrcParameters *const   MrcData,
  IN const UINT32           Channel
  )
{
  return (
    (UINT8) MrcHalGetBfMchbarCh1CrReutChWdbCaptureStatusWdbCurrentCapturePointer (
              MrcReadCR (
                MrcData,
                OFFSET_CALC_CH (
                  MCHBAR_CH0_CR_REUT_CH_WDB_CAPTURE_STATUS_REG,
                  MCHBAR_CH1_CR_REUT_CH_WDB_CAPTURE_STATUS_REG,
                  Channel
                  )
                )
              )
    );
}

/**
  This function sets the WDB address as data controls.

  @param[in] MrcData            - Include all MRC global data.
  @param[in] WriteAsDataControl - Write as data control.
  @param[in] ReadAsDataControl  - Read as data control.
**/
void
MrcHalRmwPatWdbAddressAsDataCtrl (
  IN MrcParameters *const MrcData,
  IN const BOOLEAN WriteAsDataControl,
  IN const BOOLEAN ReadAsDataControl
  )
{
  MrcHalSetRegMcschedsCrReutChPatWdbAddressAsDataCtrl (
    MrcData,
    MrcHalSetBfMcschedsCrReutChPatWdbAddressAsDataCtrlWriteAddressAsData (
      (UINT32) WriteAsDataControl,
      MrcHalSetBfMcschedsCrReutChPatWdbAddressAsDataCtrlReadAddressAsData (
        (UINT32) ReadAsDataControl,
        0
        )
      )
    );
  return;
}

/**
  This function sets the write data buffer pattern.

  @param[in] MrcData             - Include all MRC global data.
  @param[in] Channel             - Zero based channel number.
  @param[in] Pattern             - Pointer to buffer containing the DqDB pattern.
  @param[in] CachelineCount      - Size of the buffer pattern in number of cachelines.  Each cacheline has 8 UINT64 elements.  For example, if CachelineCount is 1 then the Pattern buffer size is 64 bytes.
  @param[in] StartCachelineIndex - Start offset on the DqDB.  The sum of the CachelineCount and StartCachelineIndex values must be less than or equal to the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.
**/
void
MrcHalSetWdbPattern (
  IN MrcParameters *const MrcData,
  IN const UINT32 Channel,
  IN const UINT64 *Pattern,
  IN const UINT32 CachelineCount,
  IN const UINT32 StartCachelineIndex
  )
{
  UINT64_STRUCT *Pointer;
  UINT32        NextCachelineIndex;
  UINT8         PatternCachelineIdx;
  UINT8         Chunk;

  Pointer            = (UINT64_STRUCT *) Pattern;
  NextCachelineIndex = StartCachelineIndex;
  for (PatternCachelineIdx = 0; PatternCachelineIdx < CachelineCount; PatternCachelineIdx++, NextCachelineIndex++, Pointer++) {
    for (Chunk = 0; Chunk < MAX_CHUNK_SIZE; Chunk++) {
      MrcHalSetRegQclkLdatDatain0 (MrcData, Channel, Pointer[Chunk].Data32.Low);
      MrcHalSetRegQclkLdatDatain1 (MrcData, Channel, Pointer[Chunk].Data32.High);

      // Set rep = 0, don't want to replicate the data.
      // Set banksel field to the value of the chunk you want to write the 64 bits to.
      // Set arraysel = 0 (indicating it is the MC WDB) and mode = 'b01 in the SDAT register.
      MrcHalSetRegQclkLdatSdat (
        MrcData,
        Channel,
        MrcHalSetBfMchbarCh0CrQclkLdatSdatMode (
          1,
          MrcHalSetBfMchbarCh0CrQclkLdatSdatBanksel (
            Chunk,
            0
            )
          )
        );

      // Finally, write the PDAT register indicating which cacheline of the WDB you want to write to
      // by setting fastaddr field to one of the 64 cache lines. Also set cmdb in the pdat register to 4'b1000,
      // indicating that this is a LDAT write.
      MrcHalSetRegQclkLdatPdat (
        MrcData,
        Channel,
        MrcHalSetBfMchbarCh0CrQclkLdatPdatCmdb (
          8,
          MrcHalSetBfMchbarCh0CrQclkLdatPdatFastaddr (
            NextCachelineIndex,
            0
            )
          )
        );
    } // Chunk

    // Turn off LDAT mode after writing to WDB is complete.
    MrcHalSetRegQclkLdatSdat (MrcData, Channel, 0);
  } // PatternCachelineIdx
  return;
}

/**
  This function gets the write data buffer pattern.

  @param[in] MrcData             - Include all MRC global data.
  @param[in] Channel             - Zero based channel number.
  @param[out] Pattern            - Pointer to buffer to be filled with the DqDB pattern.
  @param[in] CachelineCount      - Size of the buffer pattern in number of cachelines.  Each cacheline has 8 UINT64 elements.  For example, if CachelineCount is 1 then the Pattern buffer size is 64 bytes.
  @param[in] StartCachelineIndex - Start offset on the DqDB.  The sum of the CachelineCount and StartCachelineIndex values must be less than or equal to the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.
**/
void
MrcHalGetWdbPattern (
  IN  MrcParameters *const MrcData,
  IN  const UINT32 Channel,
  OUT const UINT64 *Pattern,
  IN  const UINT32 CachelineCount,
  IN  const UINT32 StartCachelineIndex
  )
{
  UINT64_STRUCT *Pointer;
  UINT32        NextCachelineIndex;
  UINT8         PatternCachelineIdx;
  UINT8         Chunk;

  Pointer            = (UINT64_STRUCT *) Pattern;
  NextCachelineIndex = StartCachelineIndex;
  for (PatternCachelineIdx = 0; PatternCachelineIdx < CachelineCount; PatternCachelineIdx++, NextCachelineIndex++, Pointer++) {
    for (Chunk = 0; Chunk < MAX_CHUNK_SIZE; Chunk++) {
      // Set rep = 0, don't want to replicate the data.
      // Set banksel field to the value of the chunk you want to write the 64 bits to.
      // Set arraysel = 0 (indicating it is the MC WDB) and mode = 'b01 in the SDAT register.
      MrcHalSetRegQclkLdatSdat (
        MrcData,
        Channel,
        MrcHalSetBfMchbarCh0CrQclkLdatSdatMode (
          1,
          MrcHalSetBfMchbarCh0CrQclkLdatSdatBanksel (
            Chunk,
            0
            )
          )
        );

      // Finally, write the PDAT register indicating which cacheline of the WDB you want to write to
      // by setting fastaddr field to one of the 64 cache lines. Also set cmdb in the pdat register to 4'b1000,
      // indicating that this is a LDAT write.
      MrcHalSetRegQclkLdatPdat (
        MrcData,
        Channel,
        MrcHalSetBfMchbarCh0CrQclkLdatPdatCmdb (
          8,
          MrcHalSetBfMchbarCh0CrQclkLdatPdatFastaddr (
            NextCachelineIndex,
            0
            )
          )
        );

      Pointer[Chunk].Data32.Low  = MrcHalGetRegQclkLdatDatain0 (MrcData, Channel);
      Pointer[Chunk].Data32.High = MrcHalGetRegQclkLdatDatain1 (MrcData, Channel);
    } // Chunk

    // Turn off LDAT mode after writing to WDB is complete.
    MrcHalSetRegQclkLdatSdat (MrcData, Channel, 0);
  } // PatternCachelineIdx
  return;
}

/**
  This function sets the write data buffer pattern controls.

  @param[in] MrcData     - Include all MRC global data.
  @param[in] Channel     - Zero based channel number.
  @param[in] StartIndex  - Starting index in the DqDB.  The value must be less than or equal to the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.
  @param[in] EndIndex    - Ending index in the DqDB.  The value must be less than or equal to the StartIndex value and less than or equal to the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.
  @param[in] IncRateMode - Increment rate scale control.
  @param[in] IncRate     - Increment rate value.  If the IncRateMode is ExponentialDqdbIncRateMode then the IncRate value must be less than or equal to the MaxDqdbIncRateExponentVal from the GetCpgcInfo() function.  If the IncRateMode is LinearDqdbIncRateMode then the IncRate value must be less than or equal to the MaxDqdbIncRateLinearVal from the GetCpgcInfo() function.
**/
void
MrcHalRmwWdbPatternControl (
  IN MrcParameters                             *const MrcData,
  IN const UINT32                              Channel,
  IN const UINT32                              StartIndex,
  IN const UINT32                              EndIndex,
  IN const MRC_HAL_ENUM_INCRMENT_SCALE_CONTROL IncRateMode,
  IN const UINT32                              IncRate
  )
{
  UINT32 IncRateLocal;
  MRC_HAL_ENUM_INCRMENT_SCALE_CONTROL IncRateControl;

  if (IncRateMode < MrcHalIncrementScaleMax) {
    IncRateLocal  = IncRate;
    IncRateControl = IncRateMode;
  } else {
    if (IncRate > MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_MAX) {
      IncRateLocal  = MrcLog2 (IncRate - 1);
      IncRateControl = MrcHalIncrementScaleExponential;
    } else {
      IncRateLocal  = IncRate;
      IncRateControl = MrcHalIncrementScaleLinear;
    }
  }
  MrcHalSetRegReutChPatWdbClCtrl (
    MrcData,
    Channel,
    MrcHalSetBfMchbarCh0CrReutChPatWdbClCtrlWdbStartPointer (
      StartIndex,
      MrcHalSetBfMchbarCh0CrReutChPatWdbClCtrlWdbEndPointer (
        EndIndex,
        MrcHalSetBfMchbarCh0CrReutChPatWdbClCtrlWdbIncrementRate (
          IncRateLocal,
          MrcHalSetBfMchbarCh0CrReutChPatWdbClCtrlWdbIncrementScale (
            IncRateControl,
            0
            )
          )
        )
      )
    );
  return;
}

/**
  This function sets the write data buffer pattern mux controls.

  @param[in] MrcData                    - Include all MRC global data.
  @param[in] Channel                    - Zero based channel number.
  @param[in] MuxControl                 - Mux selector. LFSR, 24 bit buffer, or LMN value.
  @param[in] MuxControlCount            - The number of MuxControl elements.
  @param[in] LfsrType                   - LFSR type control.
  @param[in] ChainingLfsr               - LFSR chaining control.
  @param[in] EccReplaceByteControl      - ECC replace byte control.
  @param[in] EccDataSourceSel           - Indicates whether byte 0 or byte 7 is transmitted and compared for the ECC byte.
  @param[in] SaveLfsrSeedRate           - The rate at which the LFSR seed is saved.
  @param[in] ReloadLfsrSeedRate         - The rate at which the LFSR seed is reloaded.
  @param[in] ReloadSaveLfsrSeedRateMode - LFSR seed reload, save rate mode.
**/
void
MrcHalRmwWdbPatternMuxControl (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             Channel,
  IN const MRC_HAL_ENUM_MUX_CONTROL           *const MuxControl,
  IN const UINT32                             MuxControlCount,
  IN const MRC_HAL_ENUM_LFSR_TYPE             LfsrType,
  IN const MRC_HAL_ENUM_LFSR_CHAINING_CONTROL ChainingLfsr,
  IN const MRC_HAL_ENUM_ECC_REPLACE_BYTE      EccReplaceByteControl,
  IN const MRC_HAL_ENUM_ECC_SOURCE_SELECT     EccDataSourceSel,
  IN const UINT32                             SaveLfsrSeedRate,
  IN const UINT32                             ReloadLfsrSeedRate,
  IN const MRC_HAL_ENUM_SEED_RATE_MODE        ReloadSaveLfsrSeedRateMode
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcHalGetRegReutChPatWdbClMuxCfg (MrcData, (Channel >= MAX_CHANNEL) ? 0 : Channel);
  if (MuxControl[0] != MrcHalMuxControlIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxCfgMux0Control ((UINT32) MuxControl[0], RegisterValue);
  }
  if (MuxControl[1] != MrcHalMuxControlIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxCfgMux1Control ((UINT32) MuxControl[1], RegisterValue);
  }
  if (MuxControl[2] != MrcHalMuxControlIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxCfgMux2Control ((UINT32) MuxControl[2], RegisterValue);
  }
  if (LfsrType != MrcHalLfsrTypeIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxCfgLfsrType ((UINT32) LfsrType, RegisterValue);
  }
  if (ChainingLfsr != MrcHalLfsrChainingIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxCfgChainingLfsr ((UINT32) ChainingLfsr, RegisterValue);
  }
  if (EccReplaceByteControl != MrcHalEccReplaceByteIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxCfgEccReplaceByteControl ((UINT32) EccReplaceByteControl, RegisterValue);
  }
  if (EccDataSourceSel != MrcHalEccDataSourceSelectIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxCfgEccDataSourceSel (EccDataSourceSel, RegisterValue);
  }
  if (SaveLfsrSeedRate != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxCfgSaveLfsrSeedRate (SaveLfsrSeedRate, RegisterValue);
  }
  if (ReloadLfsrSeedRate != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxCfgReloadLfsrSeedRate (ReloadLfsrSeedRate, RegisterValue);
  }
  if (ReloadSaveLfsrSeedRateMode != MrcHalSeedRateModeIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxCfgReloadSaveLfsrSeedRateMode ((UINT32) ReloadSaveLfsrSeedRateMode, RegisterValue);
  }
  if (Channel >= MAX_CHANNEL) {
    MrcHalSetRegMcschedsCrReutChPatWdbClMuxCfg (MrcData, RegisterValue);
  } else {
    MrcHalSetRegReutChPatWdbClMuxCfg (MrcData, Channel, RegisterValue);
  }
  return;
}

/**
  This function will program all present channels with the seeds passed in.

  @param[in] MrcData   - Global MRC data structure
  @param[in] ChannelIn - Zero based channel number.
  @param[in] Seeds     - Array of seeds programmed into PAT_WDB_CL_MUX_PB_RD/WR
  @param[in] Start     - Zero based starting seed location
  @param[in] SeedCount - Number of seeds in the array
  @param[in] ReadWrite - Read/Write buffer select bit field. Bit 0 = Read, Bit 1 = Write.
**/
void
MrcHalProgramLfsr (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             ChannelIn,
  IN const UINT32                             *const Seeds,
  IN const UINT32                             Start,
  IN const UINT32                             SeedCount,
  IN const MRC_HAL_ENUM_PATTERN_BUFFER_SELECT ReadWrite
  )
{
  UINT32 CrRdOffset;
  UINT32 CrWrOffset;
  UINT32 Value;
  UINT32 Channel;
  UINT32 ChannelStart;
  UINT32 ChannelEnd;
  UINT32 Index;

  if (ChannelIn == MRC_CHANNEL_MULTICAST) {
    ChannelStart = 0;
    ChannelEnd   = MAX_CHANNEL - 1;
  } else {
    ChannelStart = ChannelIn;
    ChannelEnd   = ChannelIn;
  }

  for (Channel = ChannelStart; Channel <= ChannelEnd; Channel++) {
    if (mrcSuccess == IsChannelPresent (MrcData, SOCKET_0, CONTROLLER_0, Channel)) {
      CrRdOffset = OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_REG, MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_REG, Channel) +
        ((MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_1_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_REG) * Start);
      CrWrOffset = OFFSET_CALC_CH (MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_REG, MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_REG, Channel) +
        ((MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_1_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_REG) * Start);
      for (Index = 0; Index < SeedCount; Index++) {
        Value = Seeds[Index];
        if (ReadWrite & MrcHalSelectPatternBufferRead) {
          MrcWriteCR (MrcData, CrRdOffset, Value);
          CrRdOffset += MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_1_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_REG;
        }
        if (ReadWrite & MrcHalSelectPatternBufferWrite) {
          MrcWriteCR (MrcData, CrWrOffset, Value);
          CrWrOffset += MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_1_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_REG;
        }
      }
    }
  }
  return;
}

/**
  Function used to set the DqDB unisequencer L/M/N values.

  @param[in] MrcData         - Global MRC data structure
  @param[in] Channel         - Zero based channel number.
  @param[in] LValue          - DqDB unisequencer L counter value.
  @param[in] MValue          - DqDB unisequencer M counter value.
  @param[in] NValue          - DqDB unisequencer N counter value.
  @param[in] LDataSel        - DqDB unisequencer L data select value.
  @param[in] EnableFreqSweep - Enables the Frequency Sweep feature.
**/
void
MrcHalProgramLmnMux (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const UINT32                         LValue,
  IN const UINT32                         MValue,
  IN const UINT32                         NValue,
  IN const MRC_HAL_ENUM_L_DATA_SELECT     LDataSel,
  IN const MRC_HAL_ENUM_ENABLE_SWEEP_FREQ EnableFreqSweep
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxLmnLDataSelect (
                    (UINT32) LDataSel,
                    MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxLmnEnableSweepFrequency (
                      (UINT32) EnableFreqSweep,
                      MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxLmnLCounter (
                        LValue,
                        MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxLmnMCounter (
                          MValue,
                          MrcHalSetBfMchbarCh0CrReutChPatWdbClMuxLmnNCounter (
                            NValue,
                            0
                            )
                          )
                        )
                      )
                    );

  if (Channel == MRC_CHANNEL_MULTICAST) {
    MrcHalSetRegMcschedsCrReutChPatWdbClMuxLmn (MrcData, RegisterValue);
  } else {
    if (mrcSuccess == IsChannelPresent (MrcData, SOCKET_0, CONTROLLER_0, Channel)) {
      MrcHalSetRegReutChPatWdbClMuxLmn (MrcData, Channel, RegisterValue);
    }
  }
  return;
}

/**
  Function used to set the DqDB Invert/DC configuration.

  @param[in] MrcData           - Global MRC data structure
  @param[in] Channel           - Zero based channel number.
  @param[in] InvOrDcControl    - Invert/DC mode.
  @param[in] DcPolarity        - DC polarity (when operating in the DC mode). 0 = DC low. 1 = DC high.
  @param[in] ShiftRateExponent - Exponent of the bitmask shift rate.
**/
void
MrcHalProgramDqDbInvertDc (
  IN MrcParameters                          *const MrcData,
  IN const UINT32                           Channel,
  IN const MRC_HAL_ENUM_INV_OR_DC_CONTROL   InvOrDcControl,
  IN const MRC_HAL_ENUM_DC_POLARITY_CONTROL DcPolarity,
  IN const UINT32                           ShiftRateExponent
  )
{
  MrcHalSetRegReutChPatWdbInv (
    MrcData,
    Channel,
    MrcHalSetBfMchbarCh0CrReutChPatWdbInvInvOrDcControl (
      (UINT32) InvOrDcControl,
      MrcHalSetBfMchbarCh0CrReutChPatWdbInvDcPolarityControl (
        (UINT32) DcPolarity,
        MrcHalSetBfMchbarCh0CrReutChPatWdbInvInvOrDcShiftRate (
          ShiftRateExponent,
          MrcHalGetRegReutChPatWdbInv (
            MrcData,
            Channel
            )
          )
        )
      )
    );
  return;
}

/**
  This function sets the command address data buffer pattern controls.

  @param[in] MrcData              - Include all MRC global data.
  @param[in] Channel              - Zero based channel number.
  @param[in] EnableCadbOnDeselect - Enable CADB on deselect control.
  @param[in] EnableCadbAlwaysOn   - Enable CADB always on control.
  @param[in] CmdDeselectStart     - Command deselect start value.
  @param[in] CmdDeselectStop      - Command deselect stop value.
  @param[in] LaneDeselectEnable   - Lane deselect control.
  @param[in] CasSelectEnable      - CAS select control.
  @param[in] ActSelectEnable      - Activate select control.
  @param[in] PreSelectEnable      - Preselect control.
  @param[in] SaveCurrentSeed      - Save current seed control.
  @param[in] ReloadStartingSeed   - Reload starting seed control.
**/
void
MrcHalRmwCadbPatternControl (
  IN MrcParameters                         *const MrcData,
  IN const UINT32                          Channel,
  IN MRC_HAL_ENUM_CADB_ON_DESELECT_CONTROL EnableCadbOnDeselect,
  IN MRC_HAL_ENUM_CADB_ALWAYS_ON_CONTROL   EnableCadbAlwaysOn,
  IN MRC_HAL_ENUM_CMD_DESELECT_CONTROL     CmdDeselectStart,
  IN MRC_HAL_ENUM_CMD_DESELECT_CONTROL     CmdDeselectStop,
  IN MRC_HAL_ENUM_LANE_DESELECT_CONTROL    LaneDeselectEnable,
  IN MRC_HAL_ENUM_CAS_SELECT_CONTROL       CasSelectEnable,
  IN MRC_HAL_ENUM_ACT_SELECT_CONTROL       ActSelectEnable,
  IN MRC_HAL_ENUM_PRE_SELECT_CONTROL       PreSelectEnable,
  IN MRC_HAL_ENUM_SAVE_SEED_CONTROL        SaveCurrentSeed,
  IN MRC_HAL_ENUM_RELOAD_SEED_CONTROL      ReloadStartingSeed
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcHalGetRegReutChPatCadbCtrl (MrcData, (Channel >= MAX_CHANNEL) ? 0 : Channel);
  if (EnableCadbOnDeselect != MrcHalCadbOnDeselectIgnoreArg) {
    RegisterValue = MrcHalSetBfMcschedsCrReutChPatCadbCtrlEnableCadbOnDeselect ((UINT32) EnableCadbOnDeselect, RegisterValue);
  }
  if (EnableCadbAlwaysOn != MrcHalCadbAlwaysOnIgnoreArg) {
    RegisterValue = MrcHalSetBfMcschedsCrReutChPatCadbCtrlEnableCadbAlwaysOn ((UINT32) EnableCadbAlwaysOn, RegisterValue);
  }
  if (CmdDeselectStart != MrcHalCmdDeselectIgnoreArg) {
    RegisterValue = MrcHalSetBfMcschedsCrReutChPatCadbCtrlCmdDeselectStart ((UINT32) CmdDeselectStart, RegisterValue);
  }
  if (CmdDeselectStop != MrcHalCmdDeselectIgnoreArg) {
    RegisterValue = MrcHalSetBfMcschedsCrReutChPatCadbCtrlCmdDeselectStop ((UINT32) CmdDeselectStop, RegisterValue);
  }
  if (LaneDeselectEnable != MrcHalLaneDeselectIgnoreArg) {
    RegisterValue = MrcHalSetBfMcschedsCrReutChPatCadbCtrlLaneDeselectEnable ((UINT32) LaneDeselectEnable, RegisterValue);
  }
  if (CasSelectEnable != MrcHalCasSelectIgnoreArg) {
    RegisterValue = MrcHalSetBfMcschedsCrReutChPatCadbCtrlCasSelectEnable ((UINT32) CasSelectEnable, RegisterValue);
  }
  if (ActSelectEnable != MrcHalActSelectIgnoreArg) {
    RegisterValue = MrcHalSetBfMcschedsCrReutChPatCadbCtrlActSelectEnable ((UINT32) ActSelectEnable, RegisterValue);
  }
  if (PreSelectEnable != MrcHalPreSelectIgnoreArg) {
    RegisterValue = MrcHalSetBfMcschedsCrReutChPatCadbCtrlPreSelectEnable ((UINT32) PreSelectEnable, RegisterValue);
  }
  if (SaveCurrentSeed != MrcHalSaveSeedOnIgnoreArg) {
    RegisterValue = MrcHalSetBfMcschedsCrReutChPatCadbCtrlSaveCurrentSeed ((UINT32) SaveCurrentSeed, RegisterValue);
  }
  if (ReloadStartingSeed != MrcHalReloadSeedOnIgnoreArg) {
    RegisterValue = MrcHalSetBfMcschedsCrReutChPatCadbCtrlReloadStartingSeed ((UINT32) ReloadStartingSeed, RegisterValue);
  }
  if (Channel >= MAX_CHANNEL) {
    MrcHalSetRegMcschedsCrReutChPatCadbCtrl (MrcData, RegisterValue);
  } else {
    MrcHalSetRegReutChPatCadbCtrl (MrcData, Channel, RegisterValue);
  }
  return;
}

/**
  This function sets the command address data buffer pattern.

  @param[in] MrcData           - Include all MRC global data.
  @param[in] CadbDataAddress   - CADB data address value.
  @param[in] CadbDataBank      - CADB data bank value.
  @param[in] CadbDataCs        - CADB data chip select value.
  @param[in] CadbDataControl   - CADB data control value.
  @param[in] CadbDataOdt       - CADB data on die termination value.
  @param[in] CadbDataCke       - CADB data CKE value.
  @param[in] CadbDataParityInv - CADB data parity invert value.
**/
UINT64
MrcHalSetCadbPatternBufferRecord (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             CadbDataAddress,
  IN const UINT32                             CadbDataBank,
  IN const UINT32                             CadbDataCs,
  IN const UINT32                             CadbDataControl,
  IN const UINT32                             CadbDataOdt,
  IN const UINT32                             CadbDataCke,
  IN const MRC_HAL_ENUM_PARITY_INVERT_CONTROL CadbDataParityInv
  )
{
  UINT64 RegisterValue;

  RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbProgCadbDataAddress (
                    MrcData,
                    CadbDataAddress,
                    MrcHalSetBfMchbarCh0CrReutChPatCadbProgCadbDataBank (
                      MrcData,
                      CadbDataBank,
                      MrcHalSetBfMchbarCh0CrReutChPatCadbProgCadbDataCs (
                        MrcData,
                        CadbDataCs,
                        MrcHalSetBfMchbarCh0CrReutChPatCadbProgCadbDataControl (
                          MrcData,
                          CadbDataControl,
                          MrcHalSetBfMchbarCh0CrReutChPatCadbProgCadbDataOdt (
                            MrcData,
                            CadbDataOdt,
                            MrcHalSetBfMchbarCh0CrReutChPatCadbProgCadbDataCke (
                              MrcData,
                              CadbDataCke,
                              MrcHalSetBfMchbarCh0CrReutChPatCadbProgCadbDataParityInv (
                                MrcData,
                                (UINT32) CadbDataParityInv,
                                0
                                )
                              )
                            )
                          )
                        )
                      )
                    );
  return (RegisterValue);
}

/**
  This function sets the command address data buffer pattern.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number.
  @param[in] Pattern       - Pointer to buffer containing the CADB pattern.
  @param[in] PatternCount  - Size of the buffer pattern in term of the count of CADB patterns.  Each row has 2 UINT32 elements.
  @param[in] StartPointer  - Start offset on the CADB.
**/
void
MrcHalRmwCadbPatternBufferInit (
  IN MrcParameters       *const MrcData,
  IN const UINT32        Channel,
  IN const UINT64_STRUCT *Pattern,
  IN UINT32              PatternCount,
  IN const UINT32        StartPointer
  )
{
  {
    MrcHalSetReutChPatCadbWritePointer (
      MrcData,
      Channel,
      MrcHalSetBfMchbarCh0CrReutChPatCadbWritePointerCadbWritePointer (
        StartPointer,
        MrcHalSetBfMchbarCh0CrReutChPatCadbWritePointerWriteEnable (
          (UINT32) MrcHalWritePointerEnable,
          0
          )
        )
      );
  }

  while (PatternCount--) {
    // Write CADB pattern buffer. Pointer is auto incremented by hardware after every write.
    {
      MrcHalSetReutChPatCadbProg (MrcData, Channel, Pattern->Data);
      Pattern++;
    }
  }
  return;
}

/**
  This function sets the write data buffer pattern mux controls.

  @param[in] MrcData               - Include all MRC global data.
  @param[in] Channel               - Zero based channel number.
  @param[in] MuxControl            - Mux control.
  @param[in] MuxControlCount       - Number of MuxControl entries.
  @param[in] SelectMuxControl      - Select mux control.
  @param[in] SelectMuxControlCount - Number of SelectMuxControl entries.
  @param[in] LfsrType              - LSFR type.
  @param[in] ChainingLfsr          - Chaining LFSR control.
**/
void
MrcHalRmwCadbPatternMuxControl (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             Channel,
  IN const MRC_HAL_ENUM_MUX_CONTROL           *const MuxControl,
  IN const UINT32                             MuxControlCount,
  IN const MRC_HAL_ENUM_MUX_CONTROL           *const SelectMuxControl,
  IN const UINT32                             SelectMuxControlCount,
  IN const MRC_HAL_ENUM_LFSR_TYPE             LfsrType,
  IN const MRC_HAL_ENUM_LFSR_CHAINING_CONTROL ChainingLfsr
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcHalGetReutChPatCadbMuxCtrl (MrcData, (Channel >= MAX_CHANNEL) ? 0 : Channel);
  if (MuxControl[0] != MrcHalMuxControlIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbMuxCtrlMux0Control ((UINT32) MuxControl[0], RegisterValue);
  }
  if (MuxControl[1] != MrcHalMuxControlIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbMuxCtrlMux1Control ((UINT32) MuxControl[1], RegisterValue);
  }
  if (MuxControl[2] != MrcHalMuxControlIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbMuxCtrlMux2Control ((UINT32) MuxControl[2], RegisterValue);
  }
  if (SelectMuxControl[0] != MrcHalMuxControlIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbMuxCtrlSelectMux0Control ((UINT32) SelectMuxControl[0], RegisterValue);
  }
  if (SelectMuxControl[1] != MrcHalMuxControlIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbMuxCtrlSelectMux1Control ((UINT32) SelectMuxControl[1], RegisterValue);
  }
  if (SelectMuxControl[2] != MrcHalMuxControlIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbMuxCtrlSelectMux2Control ((UINT32) SelectMuxControl[2], RegisterValue);
  }
  if (LfsrType != MrcHalLfsrTypeIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbMuxCtrlLfsrType ((UINT32) LfsrType, RegisterValue);
  }
  if (ChainingLfsr != MrcHalLfsrChainingIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbMuxCtrlChainingLfsr ((UINT32) ChainingLfsr, RegisterValue);
  }
  if (Channel >= MAX_CHANNEL) {
    MrcHalSetRegMcschedsCrReutChPatCadbMuxCtrl (MrcData, RegisterValue);
  } else {
    MrcHalSetReutChPatCadbMuxCtrl (MrcData, Channel, RegisterValue);
  }
  return;
}

/**
  This function sets the command address data buffer mux pattern.

  @param[in] MrcData            - Include all MRC global data.
  @param[in] Channel            - Zero based channel number.
  @param[in] PatternBuffer      - Pattern buffer values.
  @param[in] PatternBufferCount - Number of PatternBuffer entries.
**/
void
MrcHalSetCadbMuxPatternBuffer (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  *const PatternBuffer,
  IN const UINT32  PatternBufferCount
  )
{
  UINT32 RegisterValue;

  if (PatternBuffer[0] != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbMuxPb0PatternBuffer (PatternBuffer[0], 0);
    if (Channel >= MAX_CHANNEL) {
      MrcHalSetRegMchbarCh0CrReutChPatCadbMuxPb0 (MrcData, RegisterValue);
    } else {
      MrcHalSetRegReutChPatCadbMuxPb0 (MrcData, Channel, RegisterValue);
    }
  }
  if (PatternBuffer[1] != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbMuxPb1PatternBuffer (PatternBuffer[1], 0);
    if (Channel >= MAX_CHANNEL) {
      MrcHalSetRegMchbarCh0CrReutChPatCadbMuxPb1 (MrcData, RegisterValue);
    } else {
      MrcHalSetRegReutChPatCadbMuxPb1 (MrcData, Channel, RegisterValue);
    }
  }
  if (PatternBuffer[2] != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbMuxPb2PatternBuffer (PatternBuffer[2], 0);
    if (Channel >= MAX_CHANNEL) {
      MrcHalSetRegMchbarCh0CrReutChPatCadbMuxPb2 (MrcData, RegisterValue);
    } else {
      MrcHalSetRegReutChPatCadbMuxPb2 (MrcData, Channel, RegisterValue);
    }
  }
  return;
}

/**
  This function sets the command address data buffer sel pattern.

  @param[in] MrcData            - Include all MRC global data.
  @param[in] Channel            - Zero based channel number.
  @param[in] PatternBuffer      - Pattern buffer values.
  @param[in] PatternBufferCount - Number of PatternBuffer entries.
**/
void
MrcHalSetCadbSelMuxPatternBuffer (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  *const PatternBuffer,
  IN const UINT32  PatternBufferCount
  )
{
  UINT32 RegisterValue;

  if (PatternBuffer[0] != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbSelMuxPb0PatternBuffer (PatternBuffer[0], 0);
    if (Channel >= MAX_CHANNEL) {
      MrcHalSetRegMchbarCh0CrReutChPatCadbSelMuxPb0 (MrcData, RegisterValue);
    } else {
      MrcHalSetRegReutChPatCadbSelMuxPb0 (MrcData, Channel, RegisterValue);
    }
  }
  if (PatternBuffer[1] != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbSelMuxPb1PatternBuffer (PatternBuffer[1], 0);
    if (Channel >= MAX_CHANNEL) {
      MrcHalSetRegMchbarCh0CrReutChPatCadbSelMuxPb1 (MrcData, RegisterValue);
    } else {
      MrcHalSetRegReutChPatCadbSelMuxPb1 (MrcData, Channel, RegisterValue);
    }
  }
  if (PatternBuffer[2] != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChPatCadbSelMuxPb2PatternBuffer (PatternBuffer[2], 0);
    if (Channel >= MAX_CHANNEL) {
      MrcHalSetRegMchbarCh0CrReutChPatCadbSelMuxPb2 (MrcData, RegisterValue);
    } else {
      MrcHalSetRegReutChPatCadbSelMuxPb2 (MrcData, Channel, RegisterValue);
    }
  }
  return;
}

/**
  This function sets the command address data buffer CL mux LMN.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Channel         - Zero based channel number.
  @param[in] LDataSel        - L data select value.
  @param[in] EnableFreqSweep - Frequency sweep control.
  @param[in] LCounter        - L counter value.
  @param[in] MCounter        - M counter value.
  @param[in] NCounter        - N counter value.
**/
void
MrcHalSetCadbClMuxLmn (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const MRC_HAL_ENUM_L_DATA_SELECT     LDataSel,
  IN const MRC_HAL_ENUM_ENABLE_SWEEP_FREQ EnableFreqSweep,
  IN const UINT32                         LCounter,
  IN const UINT32                         MCounter,
  IN const UINT32                         NCounter
  )
{
  MrcHalSetRegReutChPatCadbClMuxLmn (
    MrcData,
    Channel,
    MrcHalSetBfMchbarCh0CrReutChPatCadbClMuxLmnLDataSelect (
      (UINT32) LDataSel,
      MrcHalSetBfMchbarCh0CrReutChPatCadbClMuxLmnEnableSweepFrequency (
        (UINT32) EnableFreqSweep,
        MrcHalSetBfMchbarCh0CrReutChPatCadbClMuxLmnLCounter (
          LCounter,
          MrcHalSetBfMchbarCh0CrReutChPatCadbClMuxLmnMCounter (
            MCounter,
            MrcHalSetBfMchbarCh0CrReutChPatCadbClMuxLmnNCounter (
              NCounter,
              0
              )
            )
          )
        )
      )
    );
  return;
}

/**
  This function sets the dummy read control.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Channel         - Zero based channel number.
  @param[in] LDataSel        - L data select value.
  @param[in] EnableFreqSweep - Frequency sweep control.
  @param[in] LCounter        - L counter value.
  @param[in] MCounter        - M counter value.
  @param[in] NCounter        - N counter value.
**/
void
MrcHalSetDummyReadControl (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const MRC_HAL_ENUM_L_DATA_SELECT     LDataSel,
  IN const MRC_HAL_ENUM_ENABLE_SWEEP_FREQ EnableFreqSweep,
  IN const UINT32                         LCounter,
  IN const UINT32                         MCounter,
  IN const UINT32                         NCounter
  )
{
  MrcHalSetRegReutChSeqDummyreadCtlMcmain (
    MrcData,
    Channel,
    MrcHalSetBfMcdfxsCrReutChSeqDummyreadCtlMcmain0LDummyreadSelect (
      (UINT32) LDataSel,
      MrcHalSetBfMcdfxsCrReutChSeqDummyreadCtlMcmain0EnableSweepFrequency (
        (UINT32) EnableFreqSweep,
        MrcHalSetBfMcdfxsCrReutChSeqDummyreadCtlMcmain0LCounter (
          LCounter,
          MrcHalSetBfMcdfxsCrReutChSeqDummyreadCtlMcmain0MCounter (
            MCounter,
            MrcHalSetBfMcdfxsCrReutChSeqDummyreadCtlMcmain0NCounter (
              NCounter,
              0
              )
            )
          )
        )
      )
    );
  return;
}

/**
  This function sets the dummy read rank and bank masks.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Zero based channel number.
  @param[in] RankMask - Rank bit field mask.
  @param[in] BankMask - Bank bit field mask.
**/
void
MrcHalRmwDummyReadRankBankMask (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL RankMask,
  IN const MRC_HAL_ENUM_BANK_MASK_CONTROL BankMask
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcHalGetRegReutChSeqDummyreadMaskMcmain (MrcData, (Channel >= MAX_CHANNEL) ? 0 : Channel);
  if (RankMask != MrcHalRankMaskIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqDummyreadMaskMcmain0DummyReadRankMask ((UINT32) RankMask, RegisterValue);
  }
  if (BankMask != MrcHalBankMaskIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqDummyreadMaskMcmain0DummyReadBankMask ((UINT32) BankMask, RegisterValue);
  }

  MrcHalSetRegReutChSeqDummyreadMaskMcmain (MrcData, Channel, RegisterValue);
  return;
}

/**
  This function sets the logical to physical mapping for the specified rank in the specified channel.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Channel      - Zero based channel number.
  @param[in] LogicalRank  - Zero based logical rank number.
  @param[in] PhysicalRank - The physical rank value.
**/
void
MrcHalSetLogicalToPhysicalRankMapping (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  LogicalRank,
  IN const UINT32  PhysicalRank
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcHalGetRegReutChSeqRankLogicalToPhysicalMappingMcMain (MrcData, Channel);
  switch (LogicalRank) {
    case 0:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank0Mapping (PhysicalRank, RegisterValue);
      break;
    case 1:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank1Mapping (PhysicalRank, RegisterValue);
      break;
    case 2:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank2Mapping (PhysicalRank, RegisterValue);
      break;
    case 3:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank3Mapping (PhysicalRank, RegisterValue);
      break;
    case 4:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank4Mapping (PhysicalRank, RegisterValue);
      break;
    case 5:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank5Mapping (PhysicalRank, RegisterValue);
      break;
    case 6:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank6Mapping (PhysicalRank, RegisterValue);
      break;
    case 7:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank7Mapping (PhysicalRank, RegisterValue);
      break;
    default:
      return;
  }
  MrcHalSetRegReutChSeqRankLogicalToPhysicalMappingMcMain (MrcData, Channel, RegisterValue);
  return;
}

/**
  This function gets the logical to physical mapping for the specified rank in the specified channel.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Channel      - Zero based channel number.
  @param[in] LogicalRank  - Zero based logical rank number.
**/
UINT32
MrcHalGetLogicalToPhysicalRankMapping (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  LogicalRank
  )
{
  UINT32 RegisterValue;
  UINT32 PhysicalRank;

  RegisterValue = MrcHalGetRegReutChSeqRankLogicalToPhysicalMappingMcMain (MrcData, Channel);
  switch (LogicalRank) {
    case 0:
      PhysicalRank = MrcHalGetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank0Mapping (RegisterValue);
      break;
    case 1:
      PhysicalRank = MrcHalGetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank1Mapping (RegisterValue);
      break;
    case 2:
      PhysicalRank = MrcHalGetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank2Mapping (RegisterValue);
      break;
    case 3:
      PhysicalRank = MrcHalGetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank3Mapping (RegisterValue);
      break;
    case 4:
      PhysicalRank = MrcHalGetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank4Mapping (RegisterValue);
      break;
    case 5:
      PhysicalRank = MrcHalGetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank5Mapping (RegisterValue);
      break;
    case 6:
      PhysicalRank = MrcHalGetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank6Mapping (RegisterValue);
      break;
    case 7:
      PhysicalRank = MrcHalGetBfMcdfxsCrReutChSeqRankLogicalToPhysicalMappingMcmain0LogicalToPhysicalRank7Mapping (RegisterValue);
      break;
    default:
      PhysicalRank = 0;
      break;
  }
  return (PhysicalRank);
}

/**
  This function sets the logical to physical mapping for the specified bank in the specified channel.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Channel      - Zero based channel number.
  @param[in] LogicalBank  - Zero based logical rank number.
  @param[in] PhysicalBank - The physical rank value.
**/
void
MrcHalSetLogicalToPhysicalBankMapping (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  LogicalBank,
  IN const UINT32  PhysicalBank
  )
{
  UINT64 RegisterValue;

  RegisterValue = MrcHalGetRegReutChSeqBankLogicalToPhysicalMappingMcMain (MrcData, Channel);
  switch (LogicalBank) {
    case 0:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank0Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 1:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank1Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 2:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank2Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 3:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank3Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 4:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank4Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 5:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank5Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 6:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank6Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 7:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank7Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 8:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank8Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 9:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank9Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 10:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank10Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 11:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank11Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 12:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank12Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 13:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank13Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 14:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank14Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    case 15:
      RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBankLogicalToPhysicalMappingMcmain0LogicalToPhysicalBank15Mapping (MrcData, PhysicalBank, RegisterValue);
      break;
    default:
      return;
  }
  MrcHalSetRegReutChSeqBankLogicalToPhysicalMappingMcMain (MrcData, Channel, RegisterValue);
  return;
}

/**
  This function sets the row address swizzle for the specified channel.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.
  @param[in] Row     - Zero based logical row bit number.
  @param[in] Value   - Zero based physical row address.
**/
void
MrcHalSetRowAddressSwizzle (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Row,
  IN const UINT32  Value
  )
{
  UINT64_STRUCT RegisterValue;

  if (Row < 6) {
    RegisterValue.Data32.Low = MrcHalGetRegReutChSeqRowAddrSwizzleLowerMcmain (MrcData, Channel);
  } else {
    RegisterValue.Data = MrcHalGetRegReutChSeqRowAddrSwizzleUpperMcmain (MrcData, Channel);
  }
  switch (Row) {
    case 0:
      RegisterValue.Data32.Low = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleLowerMcmain0LogicalToPhysicalRow0Swizzle (Value, RegisterValue.Data32.Low);
      break;
    case 1:
      RegisterValue.Data32.Low = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleLowerMcmain0LogicalToPhysicalRow1Swizzle (Value, RegisterValue.Data32.Low);
      break;
    case 2:
      RegisterValue.Data32.Low = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleLowerMcmain0LogicalToPhysicalRow2Swizzle (Value, RegisterValue.Data32.Low);
      break;
    case 3:
      RegisterValue.Data32.Low = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleLowerMcmain0LogicalToPhysicalRow3Swizzle (Value, RegisterValue.Data32.Low);
      break;
    case 4:
      RegisterValue.Data32.Low = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleLowerMcmain0LogicalToPhysicalRow4Swizzle (Value, RegisterValue.Data32.Low);
      break;
    case 5:
      RegisterValue.Data32.Low = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleLowerMcmain0LogicalToPhysicalRow5Swizzle (Value, RegisterValue.Data32.Low);
      break;
    case 6:
      RegisterValue.Data = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleUpperMcmain1LogicalToPhysicalRow6Swizzle (MrcData, Value, RegisterValue.Data);
      break;
    case 7:
      RegisterValue.Data = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleUpperMcmain1LogicalToPhysicalRow7Swizzle (MrcData, Value, RegisterValue.Data);
      break;
    case 8:
      RegisterValue.Data = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleUpperMcmain1LogicalToPhysicalRow8Swizzle (MrcData, Value, RegisterValue.Data);
      break;
    case 9:
      RegisterValue.Data = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleUpperMcmain1LogicalToPhysicalRow9Swizzle (MrcData, Value, RegisterValue.Data);
      break;
    case 10:
      RegisterValue.Data = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleUpperMcmain1LogicalToPhysicalRow10Swizzle (MrcData, Value, RegisterValue.Data);
      break;
    case 11:
      RegisterValue.Data = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleUpperMcmain1LogicalToPhysicalRow11Swizzle (MrcData, Value, RegisterValue.Data);
      break;
    case 12:
      RegisterValue.Data = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleUpperMcmain1LogicalToPhysicalRow12Swizzle (MrcData, Value, RegisterValue.Data);
      break;
    case 13:
      RegisterValue.Data = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleUpperMcmain1LogicalToPhysicalRow13Swizzle (MrcData, Value, RegisterValue.Data);
      break;
    case 14:
      RegisterValue.Data = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleUpperMcmain1LogicalToPhysicalRow14Swizzle (MrcData, Value, RegisterValue.Data);
      break;
    case 15:
      RegisterValue.Data = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleUpperMcmain1LogicalToPhysicalRow15Swizzle (MrcData, Value, RegisterValue.Data);
      break;
    case 16:
      RegisterValue.Data = MrcHalSetBfMcdfxsCrReutChSeqRowAddrSwizzleUpperMcmain1LogicalToPhysicalRow16Swizzle (MrcData, Value, RegisterValue.Data);
      break;
    default:
      return;
  }
  if (Row < 6) {
    MrcHalSetRegReutChSeqRowAddrSwizzleLowerMcmain (MrcData, Channel, RegisterValue.Data32.Low);
  } else {
    MrcHalSetRegReutChSeqRowAddrSwizzleUpperMcmain (MrcData, Channel, RegisterValue.Data);
  }
  return;
}

/**
  Function used to set the subsequence configuration.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Channel      - Zero based channel number.
  @param[in] SubseqStart  - Zero based starting subsequence number.
  @param[in] SubSeqCount  - Number of SubSequence entries in the SubSeqCtl and SubSeqOffset arrays.
  @param[in] SubSeqCtl    - Specifies whether address inversion enabled for this subsequence.
  @param[in] SubSeqOffset - Specifies whether data inversion enabled for this subsequence.
**/
void
MrcHalSetReutSubsequence (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             Channel,
  IN const UINT32                             SubSeqStart,
  IN const UINT32                             SubSeqCount,
  IN const MRC_HAL_SUBSEQUENCE_CONTROL_STRUCT *const SubSeqCtl,
  IN const MRC_HAL_SUBSEQUENCE_OFFSET_STRUCT  *const SubSeqOffset
  )
{
  UINT32                                   SubSeq;
  UINT32                                   SubSeqEnd;
  const MRC_HAL_SUBSEQUENCE_CONTROL_STRUCT *Control;
  const MRC_HAL_SUBSEQUENCE_OFFSET_STRUCT  *Offset;

  SubSeqEnd = SubSeqStart + SubSeqCount;
  if (SubSeqCtl != NULL) {
    Control   = &SubSeqCtl[0];
    for (SubSeq = SubSeqStart; SubSeq < SubSeqEnd; SubSeq++, Control++) {
      MrcHalSetRegReutChSubseqCtlMcmain (
        MrcData,
        Channel,
        SubSeq,
        MrcHalSetBfMcdfxsCrReutCh0SubseqCtlMcmain0NumberOfCachelines (
          Control->NumberofCachelines,
          MrcHalSetBfMcdfxsCrReutCh0SubseqCtlMcmain0NumberOfCachelinesScale (
            Control->NumberofCachelinesScale,
            MrcHalSetBfMcdfxsCrReutCh0SubseqCtlMcmain0SubsequenceWait (
              Control->SubsequenceWait,
              MrcHalSetBfMcdfxsCrReutCh0SubseqCtlMcmain0SubsequenceType (
                Control->SubsequenceType,
                MrcHalSetBfMcdfxsCrReutCh0SubseqCtlMcmain0SaveCurrentBaseAddressToStart (
                  Control->SaveCurrentBaseAddressToStart,
                  MrcHalSetBfMcdfxsCrReutCh0SubseqCtlMcmain0ResetCurrentBaseAddressToStart (
                    Control->ResetCurrentBaseAddressToStart,
                    MrcHalSetBfMcdfxsCrReutCh0SubseqCtlMcmain0DataAndEccAddressInversion (
                      Control->DataandEccAddressInversion,
                      MrcHalSetBfMcdfxsCrReutCh0SubseqCtlMcmain0InvertDataAndEcc (
                        Control->InvertDataandEcc,
                        MrcHalSetBfMcdfxsCrReutCh0SubseqCtlMcmain0StopBaseSubsequenceOnWrapTrigger (
                          Control->StopBaseSubsequenceOnWrapTrigger,
                          0
                          )
                        )
                      )
                    )
                  )
                )
              )
            )
          )
        );
    }
  }

  if (SubSeqOffset != NULL) {
    Offset = &SubSeqOffset[0];
    for (SubSeq = SubSeqStart; SubSeq < SubSeqEnd; SubSeq++, Offset++) {
      MrcHalSetRegReutChSubseqOffsetCtlMcmain (
        MrcData,
        Channel,
        SubSeq,
        MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0OffsetAddressUpdateRate (
          Offset->OffsetAddressUpdateRate,
          MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0BaseSubsequenceRepeatRate (
            Offset->BaseSubsequenceRepeatRate,
            MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0ColumnOffsetWrapTriggerEnable (
              Offset->ColumnOffsetWrapTriggerEnable,
              MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0RowOffsetWrapTriggerEnable (
                Offset->RowOffsetWrapTriggerEnable,
                MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0BaseSubsequenceType (
                  Offset->BaseSubsequenceType,
                  MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0CadbDeselectEnable (
                    Offset->CadbDeselectEnable,
                    MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0CadbSelectEnable (
                      Offset->CadbSelectEnable,
                      MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0CadbSeedsSaveEnable (
                        Offset->CadbSeedsSaveEnable,
                        MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0ColumnIncrementOrder (
                          Offset->ColumnIncrementOrder,
                          MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0CadbSeedsReloadEnable (
                            Offset->CadbSeedsReloadEnable,
                            MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0ColumnIncrementEnable (
                              Offset->ColumnIncrementEnable,
                              MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0RowIncrementOrder (
                                Offset->RowIncrementOrder,
                                MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0RowIncrementEnable (
                                  Offset->RowIncrementEnable,
                                  MrcHalSetBfMcdfxsCrReutCh0SubseqOffsetCtlMcmain0BaseInvertDataAndEcc (
                                    Offset->BaseInvertDataandEcc,
                                    0
                                    )
                                  )
                                )
                              )
                            )
                          )
                        )
                      )
                    )
                  )
                )
              )
            )
          )
        );
    }
  }
  return;
}

/**
  This function sets the reut sequence configuration.

  @param[in] MrcData   - Include all MRC global data.
  @param[in] Channel   - Zero based channel number.
  @param[in] SeqConfig - Sequence configuration.

  @retval The previous setting of the sequence configuration register.
**/
UINT64
MrcHalSetReutSequenceConfig (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const MRC_HAL_SEQUENCE_CONFIG_STRUCT *const SeqConfig
  )
{
  UINT64 RegisterValue;
  UINT64 PreviousValue;

  RegisterValue = MrcHalGetRegReutChSeqCfgMcmain (MrcData, Channel);
  PreviousValue = RegisterValue;
  if (SeqConfig->StopBaseSequenceOnWrapTrigger != MrcHalSequenceWrapIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqCfgMcmain0StopBaseSequenceOnWrapTrigger (MrcData, (UINT64) SeqConfig->StopBaseSequenceOnWrapTrigger, RegisterValue);
  }
  if (SeqConfig->AddressUpdateRateMode != MrcHalAddressUpdateRateModeIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqCfgMcmain0AddressUpdateRateMode (MrcData, (UINT64) SeqConfig->AddressUpdateRateMode, RegisterValue);
  }
  if (SeqConfig->EnableDummyReads != MrcHalDummyReadIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqCfgMcmain0EnableDummyReads (MrcData, (UINT64) SeqConfig->EnableDummyReads, RegisterValue);
  }
  if (SeqConfig->ReutAllowOppRefresh != MrcHalOpportunisticRefreshIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqCfgMcmain0ReutAllowoppRefresh (MrcData, (UINT64) SeqConfig->ReutAllowOppRefresh, RegisterValue);
  }
  if (SeqConfig->GlobalControl != MrcHalGlobalControlIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqCfgMcmain0GlobalControl (MrcData, (UINT64) SeqConfig->GlobalControl, RegisterValue);
  }
  if (SeqConfig->InitializationMode != MrcHalInitializationModeIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqCfgMcmain0InitializationMode (MrcData, (UINT64) SeqConfig->InitializationMode, RegisterValue);
  }
  if (SeqConfig->SubsequenceStartPointer != MrcHalSubSequencePointerIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqCfgMcmain0SubsequenceStartPointer (MrcData, (UINT64) SeqConfig->SubsequenceStartPointer, RegisterValue);
  }
  if (SeqConfig->SubsequenceEndPointer != MrcHalSubSequencePointerIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqCfgMcmain0SubsequenceEndPointer (MrcData, (UINT64) SeqConfig->SubsequenceEndPointer, RegisterValue);
  }
  if (SeqConfig->StartTestDelay != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqCfgMcmain0StartTestDelay (MrcData, (UINT64) SeqConfig->StartTestDelay, RegisterValue);
  }
  if (SeqConfig->SubSequenceCachelineCounterMode != MrcHalCachelineCounterIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqCfgMcmain0SubsequenceCachelineCounterMode (MrcData, (UINT64) SeqConfig->SubSequenceCachelineCounterMode, RegisterValue);
  }

  MrcHalSetRegReutChSeqCfgMcmain (MrcData, Channel, RegisterValue);
  return (PreviousValue);
}

/**
  This function configures the sequence base address start register by doing a read/modify/write on those input
  fields that are valid.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.
  @param[in] Address - Address constructed using rank, bank, row, column.
**/
void
MrcHalSetReutChSeqBaseAddrStart (
  IN MrcParameters                         *const MrcData,
  IN const UINT32                          Channel,
  IN const MRC_HAL_SEQ_BASE_ADDRESS_STRUCT *const Address
  )
{
  UINT64 RegisterValue;

  RegisterValue = (Channel == cCHANNEL1) ? MrcHalGetRegMcdfxsCrReutChSeqBaseAddrStartMcmain1 (MrcData) : MrcHalGetRegMcdfxsCrReutChSeqBaseAddrStartMcmain0 (MrcData);
  if (Address->Rank != MRC_IGNORE_ARG_8) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrStartMcmain0RankAddress (MrcData, (UINT32) Address->Rank, RegisterValue);
  }
  if (Address->Bank != MRC_IGNORE_ARG_8) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrStartMcmain0BankAddress (MrcData, (UINT32) Address->Bank, RegisterValue);
  }
  if (Address->Row != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrStartMcmain0RowAddress (MrcData, Address->Row, RegisterValue);
  }
  if (Address->Column != MRC_IGNORE_ARG_16) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrStartMcmain0ColumnAddress (MrcData, (UINT32) Address->Column, RegisterValue);
  }
  (Channel == cCHANNEL1) ? MrcHalSetRegMcdfxsCrReutChSeqBaseAddrStartMcmain1 (MrcData, RegisterValue) : MrcHalSetRegMcdfxsCrReutChSeqBaseAddrStartMcmain0 (MrcData, RegisterValue);
  return;
}

/**
  This function configures the sequence base address wrap register by doing a read/modify/write on those input
  fields that are valid.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.
  @param[in] Address - Address constructed using rank, bank, row, column.

  @retval The value written to the register.
**/
void
MrcHalSetReutChSeqBaseAddrWrap (
  IN MrcParameters                         *const MrcData,
  IN const UINT32                          Channel,
  IN const MRC_HAL_SEQ_BASE_ADDRESS_STRUCT *const Address
  )
{
  UINT64 RegisterValue;

  RegisterValue = (Channel == cCHANNEL1) ? MrcHalGetRegMcdfxsCrReutChSeqBaseAddrWrapMcmain1 (MrcData) : MrcHalGetRegMcdfxsCrReutChSeqBaseAddrWrapMcmain0 (MrcData);
  if (Address->Rank != MRC_IGNORE_ARG_8) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrWrapMcmain0RankAddress (MrcData, (UINT32) Address->Rank, RegisterValue);
  }
  if (Address->Bank != MRC_IGNORE_ARG_8) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrWrapMcmain0BankAddress (MrcData, (UINT32) Address->Bank, RegisterValue);
  }
  if (Address->Row != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrWrapMcmain0RowAddress (MrcData, Address->Row, RegisterValue);
  }
  if (Address->Column != MRC_IGNORE_ARG_16) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrWrapMcmain0ColumnAddress (MrcData, (UINT32) Address->Column, RegisterValue);
  }
  (Channel == cCHANNEL1) ? MrcHalSetRegMcdfxsCrReutChSeqBaseAddrWrapMcmain1 (MrcData, RegisterValue) : MrcHalSetRegMcdfxsCrReutChSeqBaseAddrWrapMcmain0 (MrcData, RegisterValue);
  return;
}

/**
  This function configures the sequence base address increment control register by doing a read/modify/write on those input
  fields that are valid.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.
  @param[in] Count   - Zero based number of elements in the IncCtl array.
  @param[in] IncCtl  - Array containing increment control values.
**/
void
MrcHalSetReutChSeqBaseAddrIncCtl (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const UINT32                         Count,
  IN const MRC_HAL_REUT_BASE_ADDR_INC_CTL *IncCtlPtr
  )
{
  UINT64 RegisterValue;

  RegisterValue = (Channel == cCHANNEL1) ? MrcHalGetRegMcdfxsCrReutChSeqBaseAddrIncCtlMcmain1 (MrcData) : MrcHalGetRegMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0 (MrcData);

  if (IncCtlPtr->Increment != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0RankBaseAddressIncrement (MrcData, IncCtlPtr->Increment, RegisterValue);
  }
  if (IncCtlPtr->Rate != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0RankBaseAddressUpdateRate (MrcData, IncCtlPtr->Rate, RegisterValue);
  }
  if (IncCtlPtr->Scale != MrcHalIncrementScaleIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0RankBaseAddressUpdateScale (MrcData, (UINT32) IncCtlPtr->Scale, RegisterValue);
  }

  IncCtlPtr++;
  if (IncCtlPtr->Increment != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0BankBaseAddressIncrement (MrcData, IncCtlPtr->Increment, RegisterValue);
  }
  if (IncCtlPtr->Rate != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0BankBaseAddressUpdateRate (MrcData, IncCtlPtr->Rate, RegisterValue);
  }
  if (IncCtlPtr->Scale != MrcHalIncrementScaleIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0BankBaseAddressUpdateScale (MrcData, (UINT32) IncCtlPtr->Scale, RegisterValue);
  }

  IncCtlPtr++;
  if (IncCtlPtr->Increment != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0RowBaseAddressIncrement (MrcData, IncCtlPtr->Increment, RegisterValue);
  }
  if (IncCtlPtr->Rate != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0RowBaseAddressUpdateRate (MrcData, IncCtlPtr->Rate, RegisterValue);
  }
  if (IncCtlPtr->Scale != MrcHalIncrementScaleIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0RowBaseAddressUpdateScale (MrcData, (UINT32) IncCtlPtr->Scale, RegisterValue);
  }

  IncCtlPtr++;
  if (IncCtlPtr->Increment != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0ColumnBaseAddressIncrement (MrcData, IncCtlPtr->Increment, RegisterValue);
  }
  if (IncCtlPtr->Rate != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0ColumnBaseAddressUpdateRate (MrcData, IncCtlPtr->Rate, RegisterValue);
  }
  if (IncCtlPtr->Scale != MrcHalIncrementScaleIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0ColumnBaseAddressUpdateScale (MrcData, (UINT32) IncCtlPtr->Scale, RegisterValue);
  }

  (Channel == cCHANNEL1) ? MrcHalSetRegMcdfxsCrReutChSeqBaseAddrIncCtlMcmain1 (MrcData, RegisterValue) : MrcHalSetRegMcdfxsCrReutChSeqBaseAddrIncCtlMcmain0 (MrcData, RegisterValue);
  return;
}

/**
  This function configures the sequence base address order/carry/invert control register by doing a read/modify/write on those input
  fields that are valid.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Channel    - Zero based channel number.
  @param[in] InvertRate - The base address invert rate.
  @param[in] Count      - Zero based number of elements in the Ctl array.
  @param[in] Ctl        - Array containing order/carry/invert control values.
**/
void
MrcHalSetReutChSeqBaseAddrOciCtl (
  IN MrcParameters                         *const MrcData,
  IN const UINT32                          Channel,
  IN const UINT32                          InvertRate,
  IN const UINT32                          Count,
  IN const MRC_HAL_REUT_BASE_ADDR_OCI_CTL  *CtlPtr
  )
{
  UINT32 RegisterValue;

  RegisterValue = (Channel == cCHANNEL1) ? MrcHalGetRegMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain1 (MrcData) : MrcHalGetRegMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0 (MrcData);

  if (InvertRate != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0BaseAddressInvertRate (InvertRate, RegisterValue);
  }

  if (CtlPtr->Order != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0BaseRankAddressOrder (CtlPtr->Order, RegisterValue);
  }
  if (CtlPtr->InvertEnable != MrcHalAddressInvertIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0RankBaseAddressInvertEnable ((UINT32) CtlPtr->InvertEnable, RegisterValue);
  }
  if (CtlPtr->TriggerEnable != MrcHalAddressWrapTriggerIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0RankBaseWrapTriggerEnable ((UINT32) CtlPtr->TriggerEnable, RegisterValue);
  }
  if (CtlPtr->CarryEnable != MrcHalAddressWrapCarryIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0RankBaseWrapCarryEnable ((UINT32) CtlPtr->CarryEnable, RegisterValue);
  }

  CtlPtr++;
  if (CtlPtr->Order != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0BaseBankAddressOrder (CtlPtr->Order, RegisterValue);
  }
  if (CtlPtr->InvertEnable != MrcHalAddressInvertIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0BankBaseAddressInvertEnable ((UINT32) CtlPtr->InvertEnable, RegisterValue);
  }
  if (CtlPtr->TriggerEnable != MrcHalAddressWrapTriggerIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0BankBaseWrapTriggerEnable ((UINT32) CtlPtr->TriggerEnable, RegisterValue);
  }
  if (CtlPtr->CarryEnable != MrcHalAddressWrapCarryIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0BankBaseWrapCarryEnable ((UINT32) CtlPtr->CarryEnable, RegisterValue);
  }

  CtlPtr++;
  if (CtlPtr->Order != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0BaseRowAddressOrder (CtlPtr->Order, RegisterValue);
  }
  if (CtlPtr->InvertEnable != MrcHalAddressInvertIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0RowBaseAddressInvertEnable ((UINT32) CtlPtr->InvertEnable, RegisterValue);
  }
  if (CtlPtr->TriggerEnable != MrcHalAddressWrapTriggerIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0RowBaseWrapTriggerEnable ((UINT32) CtlPtr->TriggerEnable, RegisterValue);
  }
  if (CtlPtr->CarryEnable != MrcHalAddressWrapCarryIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0RowBaseWrapCarryEnable ((UINT32) CtlPtr->CarryEnable, RegisterValue);
  }

  CtlPtr++;
  if (CtlPtr->Order != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0BaseColumnAddressOrder (CtlPtr->Order, RegisterValue);
  }
  if (CtlPtr->InvertEnable != MrcHalAddressInvertIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0ColumnBaseAddressInvertEnable ((UINT32) CtlPtr->InvertEnable, RegisterValue);
  }
  if (CtlPtr->TriggerEnable != MrcHalAddressWrapTriggerIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0ColumnBaseWrapTriggerEnable ((UINT32) CtlPtr->TriggerEnable, RegisterValue);
  }
  if (CtlPtr->CarryEnable != MrcHalAddressWrapCarryIgnoreArg) {
    RegisterValue = MrcHalSetBfMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0ColumnBaseWrapCarryEnable ((UINT32) CtlPtr->CarryEnable, RegisterValue);
  }

  (Channel == cCHANNEL1) ? MrcHalSetRegMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain1 (MrcData, RegisterValue) : MrcHalSetRegMcdfxsCrReutChSeqBaseAddrOrderCarryInvertCtlMcmain0 (MrcData, RegisterValue);
  return;
}

/**
  This function gets the sequence base address start rank value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The value from the register.
**/
UINT32
MrcHalGetReutChSeqBaseAddrStartRank (
  IN MrcParameters                 *const MrcData,
  IN const UINT32                  Channel
  )
{
  UINT64 RegisterValue;

  RegisterValue = (Channel == cCHANNEL1) ? MrcHalGetRegMcdfxsCrReutChSeqBaseAddrStartMcmain1 (MrcData) : MrcHalGetRegMcdfxsCrReutChSeqBaseAddrStartMcmain0 (MrcData);
  return ((UINT32) MrcHalGetBfMcdfxsCrReutChSeqBaseAddrStartMcmain0RankAddress (MrcData, RegisterValue));
}

/**
  This function gets the sequence base address current rank value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The value from the register.
**/
UINT32
MrcHalGetReutChSeqBaseAddrCurrentRank (
  IN MrcParameters                 *const MrcData,
  IN const UINT32                  Channel
  )
{
  UINT64 RegisterValue;

  RegisterValue = (Channel == cCHANNEL1) ? MrcHalGetRegMcdfxsCrReutChSeqBaseAddrCurrentMcmain1 (MrcData) : MrcHalGetRegMcdfxsCrReutChSeqBaseAddrCurrentMcmain0 (MrcData);
  return ((UINT32) MrcHalGetBfMcdfxsCrReutChSeqBaseAddrCurrentMcmain0RankAddress (MrcData, RegisterValue));
}

/**
  This function configures the reut channel error control.

  @param[in] MrcData                       - Include all MRC global data.
  @param[in] Channel                       - Zero based channel number.
  @param[in] StopOnNthError                - Stop on Nth error control.
  @param[in] StopOnCaAlert                 - Stop on CA alert control.
  @param[in] StopOnErrorControl            - Stop on error control.
  @param[in] SelectiveErrorEnableChunk     - Selective error enable chunk control bit mask.
  @param[in] SelectiveErrorEnableCacheline - Selective error enable cacheline control bit mask.
**/
void
MrcHalSetReutChannelErrorControl (
  IN MrcParameters                                       *const MrcData,
  IN const UINT32                                        Channel,
  IN const UINT32                                        StopOnNthError,
  IN const MRC_HAL_ENUM_STOP_ON_CA_ALERT                 StopOnCaAlert,
  IN const MRC_HAL_ENUM_STOP_ON_ERROR_CONTROL            StopOnErrorControl,
  IN const MRC_HAL_ENUM_SELECTIVE_ERROR_ENABLE_CHUNK     SelectiveErrorEnableChunk,
  IN const MRC_HAL_ENUM_SELECTIVE_ERROR_ENABLE_CACHELINE SelectiveErrorEnableCacheline
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcHalGetRegReutChErrCtl (MrcData, Channel);

  if (StopOnNthError != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChErrCtlStopOnNthError (StopOnNthError, RegisterValue);
  }
  if (StopOnCaAlert != MrcHalStopOnCaAlertIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChErrCtlStopOnCaAlert ((UINT32) StopOnCaAlert, RegisterValue);
  }
  if (StopOnErrorControl != MrcHalStopOnErrorIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChErrCtlStopOnErrorControl ((UINT32) StopOnErrorControl, RegisterValue);
  }
  if (SelectiveErrorEnableChunk != MrcHalSelectiveErrorEnableIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChErrCtlSelectiveErrorEnableChunk ((UINT32) SelectiveErrorEnableChunk, RegisterValue);
  }
  if (SelectiveErrorEnableCacheline != MrcHalSelectiveErrorEnableCachelineIgnoreArg) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChErrCtlSelectiveErrorEnableCacheline ((UINT32) SelectiveErrorEnableCacheline, RegisterValue);
  }
  MrcHalSetRegReutChErrCtl (MrcData, Channel, RegisterValue);

  return;
}

/**
  This function gets the reut channel stop on error control.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The value read from the register.
**/
MRC_HAL_ENUM_STOP_ON_ERROR_CONTROL
MrcHalGetReutChannelStopOnErrorControl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return (
    (MRC_HAL_ENUM_STOP_ON_ERROR_CONTROL)
    MrcHalGetBfMchbarCh0CrReutChErrCtlStopOnErrorControl (
      MrcHalGetRegReutChErrCtl (MrcData, Channel)
      )
    );
}

/**
  Function used to set the error counter mode.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number. Pass MRC_CHANNEL_MULTICAST to do all channels.
  @param[in] Counter - Zero based counter number. Pass MRC_BYTE_MULTICAST to do all bytes.
  @param[in] Control - Error counter mode.
  @param[in] Pointer - Extra index used to provide additional information if needed by the mode selected. This indicates which lane, nibble, byte, or chunk has been selected.  If CounterMode value is LaneErrorCounterMode then the ModeIndex value must be less than the BusWidth value from the GetSystemInfo() function.  If CounterMode is NibbleErrorCounterMode then the ModeIndex value must be less than the BusWidth/4 value from the GetSystemInfo() function.  If CounterMode is ByteErrorCounterMode then the ModeIndex value must be less than the BusWidth/8 value from the GetSystemInfo() function.  If CounterMode is ChunkErrorCounterMode then the ModeIndex value must be less than 8.
**/
void
MrcHalSetChannelErrorCounterControl (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             Channel,
  IN const UINT32                             Counter,
  IN const MRC_HAL_ENUM_ERROR_COUNTER_CONTROL Control,
  IN const UINT32                             Pointer
  )
{
  UINT32 Byte;
  UINT32 Start;
  UINT32 End;
  UINT32 RegisterValue;

  if (Counter >= MAX_SDRAM_IN_DIMM) {
    Start = 0;
    End   = MAX_SDRAM_IN_DIMM - 1;
  } else {
    Start = Counter;
    End   = Counter;
  }
  for (Byte = Start; Byte <= End; Byte++) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChErrCounterCtl0CounterPointer (
                      Pointer,
                      MrcHalSetBfMchbarCh0CrReutChErrCounterCtl0CounterControl (
                        (UINT32) Control,
                        (Channel >= MAX_CHANNEL) ? 0 : MrcHalGetRegReutChErrCounterCtl (MrcData, Channel, Byte)
                        )
                      );
    MrcHalSetRegReutChErrCounterCtl (MrcData, Channel, Byte, RegisterValue);
  }
  return;
}

/**
  Function used to get the data error status.

  @param[in]      MrcData     - Include all MRC global data.
  @param[in]      Channel     - Zero based channel number.
  @param[in, out] ErrorStatus - Error status value. This buffer must be at least MAX_SDRAM_IN_DIMM bytes in size. The ECC byte will always be provided, even if ECC is disabled.

  @retval TRUE if the data error status indicates all bit lanes failed, otherwise FALSE. The ECC byte will not be included if ECC is disabled.
**/
BOOLEAN
MrcHalGetChannelErrorStatus (
  IN     MrcParameters *const MrcData,
  IN     const UINT32  Channel,
  IN OUT UINT8         *ErrorStatus
  )
{
  struct _DataErrorStatus {
    UINT64_STRUCT ErrorStatus;
    UINT8         EccStatus;
  } *RegisterValue;

  RegisterValue                   = (struct _DataErrorStatus *) ErrorStatus;
  RegisterValue->ErrorStatus.Data = MrcHalGetRegErrDataStatus (MrcData, Channel);
  RegisterValue->EccStatus        = (UINT8) MrcHalGetBfMchbarCh0CrReutChErrEccChunkRankByteNthStatusEccErrorStatus (MrcData, MrcHalGetReutChErrChunkRankByteNthStatus (MrcData, Channel));
  return (((RegisterValue->ErrorStatus.Data != 0xFFFFFFFFFFFFFFFFULL) || (MrcData->Outputs.EccSupport && (RegisterValue->EccStatus != 0xFF))) ? FALSE : TRUE);
}

/**
  Function used to get the data chunk error status.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval TRUE if the data error status indicates all bit lanes failed, otherwise FALSE.
**/
UINT32
MrcHalGetChannelChunkErrorStatus (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  )
{
  return ((UINT32) MrcHalGetBfMchbarCh0CrReutChErrEccChunkRankByteNthStatusChunkErrorStatus (MrcData, MrcHalGetReutChErrChunkRankByteNthStatus (MrcData, Channel)));
}

/**
  Function used to get the data rank error status.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval TRUE if the data error status indicates all bit lanes failed, otherwise FALSE.
**/
UINT32
MrcHalGetChannelRankErrorStatus (
  IN     MrcParameters *const MrcData,
  IN     const UINT32  Channel
  )
{
  return ((UINT32) MrcHalGetBfMchbarCh0CrReutChErrEccChunkRankByteNthStatusRankErrorStatus (MrcData, MrcHalGetReutChErrChunkRankByteNthStatus (MrcData, Channel)));
}

/**
  Function used to get the data byte group error status.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval TRUE if the data error status indicates all bit lanes failed, otherwise FALSE.
**/
UINT32
MrcHalGetChannelByteGroupErrorStatus (
  IN     MrcParameters *const MrcData,
  IN     const UINT32  Channel
  )
{
  return ((UINT32) MrcHalGetBfMchbarCh0CrReutChErrEccChunkRankByteNthStatusByteGroupErrorStatus (MrcData, MrcHalGetReutChErrChunkRankByteNthStatus (MrcData, Channel)));
}

/**
  This function configures the reut channel sequence control.

  @param[in] MrcData          - Include all MRC global data.
  @param[in] Channel          - Zero based channel number.
  @param[in] LocalStartTest   - Start the local test.
  @param[in] LocalStopTest    - Stop the local test.
  @param[in] LocalClearErrors - Clear local errors.
**/
void
MrcHalSetReutChannelSequenceControl (
  IN MrcParameters                          *const MrcData,
  IN const UINT32                           Channel,
  IN const MRC_HAL_ENUM_TEST_CONTROL        TestControl,
  IN const MRC_HAL_ENUM_CLEAR_ERROR_CONTROL LocalClearErrors
  )
{
  MrcHalSetRegReutChSeqCtlMcmain (MrcData,
    Channel,
    MrcHalSetBfMcdfxsCrReutChSeqCtlMcmain0LocalStartTest (
      TestControl == MrcHalTestControlStart,
      MrcHalSetBfMcdfxsCrReutChSeqCtlMcmain0LocalStopTest (
        TestControl == MrcHalTestControlStop,
        MrcHalSetBfMcdfxsCrReutChSeqCtlMcmain0LocalClearErrors (
          (UINT32) LocalClearErrors,
          0
          )
        )
      )
    );
  return;
}

/**
  This function configures the reut global sequence control.

  @param[in] MrcData            - Include all MRC global data.
  @param[in] GlobalStartTest    - Start the global test.
  @param[in] GlobalStopTest     - Stop the global test.
  @param[in] GlobalClearErrors  - Clear global errors.
  @param[in] StopTestOnAnyError - Stop test on any error.
**/
void
MrcHalSetReutGlobalSequenceControl (
  IN MrcParameters                            *const MrcData,
  IN const MRC_HAL_ENUM_TEST_CONTROL          TestControl,
  IN const MRC_HAL_ENUM_CLEAR_ERROR_CONTROL   GlobalClearErrors,
  IN const MRC_HAL_ENUM_STOP_ON_ERROR_CONTROL StopTestOnAnyError
  )
{
  MrcHalSetRegMcdfxsCrReutGlobalCtlMcmain (
    MrcData,
    MrcHalSetBfMcdfxsCrReutGlobalCtlMcmainGlobalStartTest (
      TestControl == MrcHalTestControlStart,
      MrcHalSetBfMcdfxsCrReutGlobalCtlMcmainGlobalStopTest (
        TestControl == MrcHalTestControlStop,
        MrcHalSetBfMcdfxsCrReutGlobalCtlMcmainGlobalClearErrors (
          (UINT32) GlobalClearErrors,
          MrcHalSetBfMcdfxsCrReutGlobalCtlMcmainGlobalStopTestOnAnyError (
            (UINT32) StopTestOnAnyError,
            0
            )
          )
        )
      )
    );
  return;
}

/**
  Function used to get the global stop test value.

  @param[in] MrcData - Include all MRC global data.

  @retval The global stop test value.
**/
MRC_HAL_ENUM_TEST_CONTROL
MrcHalGetGlobalStopTest (
  IN MrcParameters *const MrcData
  )
{
  return (MrcHalGetBfMcdfxsCrReutGlobalCtlMcmainGlobalStopTest (MrcHalGetRegMcdfxsCrReutGlobalCtlMcmain (MrcData)));
}

/**
  This function configures the scrambler.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Channel         - Zero based channel number.
  @param[in] Enable          - Enable the scrambler.
  @param[in] Key             - Scrambler key.
  @param[in] ClockGateABMode - Clock gate AB mode.
  @param[in] ClockGateCMode  - Clock gate C mode.
  @param[in] EnableDbiAB     - DBI AB control.
**/
void
MrcHalSetScramblerControl (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             Channel,
  IN const MRC_HAL_ENUM_SCRAMBLER_CONTROL     Control,
  IN const UINT32                             Key,
  IN const MRC_HAL_ENUM_CLOCK_GATE_AB_CONTROL ClockGateABMode,
  IN const MRC_HAL_ENUM_CLOCK_GATE_C_CONTROL  ClockGateCMode,
  IN const MRC_HAL_ENUM_DBI_AB_CONTROL        EnableDbiAB
  )
{
  MrcHalSetRegDdrscramble (
    MrcData,
    Channel,
    MrcHalSetBfDdrscramCrDdrscramblech0Scramen (
      (UINT32) Control,
      MrcHalSetBfDdrscramCrDdrscramblech0Scramkey (
        Key,
        MrcHalSetBfDdrscramCrDdrscramblech0Clockgateab (
          (UINT32) ClockGateABMode,
          MrcHalSetBfDdrscramCrDdrscramblech0Clockgatec (
            (UINT32) ClockGateCMode,
            MrcHalSetBfDdrscramCrDdrscramblech0Enabledbiab (
              (UINT32) EnableDbiAB,
              0
              )
            )
          )
        )
      )
    );
  return;
}

/**
  This function gets the scrambler configuration.

  @param[in]  MrcData         - Include all MRC global data.
  @param[in]  Channel         - Zero based channel number.
  @param[out] Enable          - Enable the scrambler.
  @param[out] Key             - Scrambler key.
  @param[out] ClockGateABMode - Clock gate AB mode.
  @param[out] ClockGateCMode  - Clock gate C mode.
  @param[out] EnableDbiAB     - Enable AB DBI.
**/
void
MrcHalGetScramblerControl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  OUT UINT32       *const Enable,
  OUT UINT32       *const Key,
  OUT UINT32       *const ClockGateABMode,
  OUT UINT32       *const ClockGateCMode,
  OUT UINT32       *const EnableDbiAB
  )
{
  UINT32 RegisterValue;

  RegisterValue    = MrcHalGetRegDdrscramble (MrcData, Channel);
  *Enable          = MrcHalGetBfDdrscramCrDdrscramblech0Scramen (RegisterValue);
  *Key             = MrcHalGetBfDdrscramCrDdrscramblech0Scramkey (RegisterValue);
  *ClockGateABMode = MrcHalGetBfDdrscramCrDdrscramblech0Clockgateab (RegisterValue);
  *ClockGateCMode  = MrcHalGetBfDdrscramCrDdrscramblech0Clockgatec (RegisterValue);
  *EnableDbiAB     = MrcHalGetBfDdrscramCrDdrscramblech0Enabledbiab (RegisterValue);
  return;
}

/**
  This function sets the self refresh configuration.

  @param[in] MrcData   - Include all MRC global data.
  @param[in] IdleTimer - Self refresh idle timer value.
  @param[in] SrEnable  - Self refresh control.
**/
void
MrcHalSetSelfRefreshConfiguration (
  IN MrcParameters                           *const MrcData,
  IN const UINT32                            IdleTimer,
  IN const MRC_HAL_ENUM_SELF_REFRESH_CONTROL SrEnable
  )
{
  MrcHalSetRegMcdecsCrPmSrefConfigMcmain (
    MrcData,
    MrcHalSetBfMcdecsCrPmSrefConfigMcmainIdleTimer (
      IdleTimer,
      MrcHalSetBfMcdecsCrPmSrefConfigMcmainSrEnable (
        (UINT32) SrEnable,
        0
        )
      )
    );
  return;
}

/**
  This function gets the self refresh configuration.

  @param[in]  MrcData   - Include all MRC global data.
  @param[out] IdleTimer - Self refresh idle timer value.
  @param[out] SrEnable  - Self refresh control.
**/
void
MrcHalGetSelfRefreshConfiguration (
  IN MrcParameters                      *const MrcData,
  OUT UINT32                            *const IdleTimer,
  OUT MRC_HAL_ENUM_SELF_REFRESH_CONTROL *const SrEnable
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcHalGetRegMcdecsCrPmSrefConfigMcmain (MrcData);
  *IdleTimer    = MrcHalGetBfMcdecsCrPmSrefConfigMcmainIdleTimer (RegisterValue);
  *SrEnable     = (MRC_HAL_ENUM_SELF_REFRESH_CONTROL) MrcHalGetBfMcdecsCrPmSrefConfigMcmainSrEnable (RegisterValue);
  return;
}

/**
  This function sets the self refresh override configuration.

  @param[in] MrcData          - Include all MRC global data.
  @param[in] Channel          - Zero based channel number.
  @param[in] RefreshRankMask  - Refresh disable rank mask.
  @param[in] EnStartTestSync  - RefZQ start test sync control.
  @param[in] PanicRefreshOnly - Panic refresh only control.
**/
void
MrcHalSetSelfRefreshOverrideConfiguration (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             Channel,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL     RefreshRankMask,
  IN const MRC_HAL_ENUM_START_TEST_SYNC       EnStartTestSync,
  IN const MRC_HAL_ENUM_PANIC_REFRESH_CONTROL PanicRefreshOnly
  )
{
  MrcHalSetRegReutChMiscRefreshCtrl (
    MrcData,
    Channel,
    MrcHalSetBfMchbarCh0CrReutChMiscRefreshCtrlRefreshRankMask (
      (UINT32) RefreshRankMask,
      MrcHalSetBfMchbarCh0CrReutChMiscRefreshCtrlRefzqEnStartTestSync (
        (UINT32) EnStartTestSync,
        MrcHalSetBfMchbarCh0CrReutChMiscRefreshCtrlPanicRefreshOnly (
          (UINT32) PanicRefreshOnly,
          0
          )
        )
      )
    );
  return;
}

/**
  This function sets the ZQ calibration override configuration.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Channel    - Zero based channel number.
  @param[in] RankMask   - Rank disable bit mask. Bit 0 = Rank 0. 1 = disable the rank.
  @param[in] AlwaysDoZq - Always do ZQ control.
**/
void
MrcHalSetZqCalOverrideConfiguration (
  IN MrcParameters                           *const MrcData,
  IN const UINT32                            Channel,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL    RankMask,
  IN const MRC_HAL_ENUM_ZQ_OPERATION_CONTROL AlwaysDoZq
  )
{
  MrcHalSetRegReutChMiscZqCtrl (
    MrcData,
    Channel,
    MrcHalSetBfMchbarCh0CrReutChMiscZqCtrlZqRankMask (
      (UINT32) RankMask,
      MrcHalSetBfMchbarCh0CrReutChMiscZqCtrlAlwaysDoZq (
        (UINT32) AlwaysDoZq,
        0
        )
      )
    );
  return;
}

/**
  This function sets the ODT override configuration.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number.
  @param[in] RankMask      - Rank bit mask.
  @param[in] OverrideMask  - Override bit mask.
  @param[in] MprTrainDdrOn - MPR train DDR control.
**/
void
MrcHalSetOdtOverrideConfiguration (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL RankMask,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL OverrideMask,
  IN const MRC_HAL_ENUM_MPR_TRAIN_CONTROL MprTrainDdrOn
  )
{
  MrcHalSetRegReutChMiscOdtCtrl (
    MrcData,
    Channel,
    MrcHalSetBfMchbarCh0CrReutChMiscOdtCtrlOdtOverride (
      (UINT32) OverrideMask,
      MrcHalSetBfMchbarCh0CrReutChMiscOdtCtrlOdtOn (
        (UINT32) RankMask,
        MrcHalSetBfMchbarCh0CrReutChMiscOdtCtrlMprTrainDdrOn (
          (UINT32) MprTrainDdrOn,
          0
          )
        )
      )
    );
  return;
}

/**
  This function sets the CKE override configuration.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number.
  @param[in] RankMask      - Rank bit mask.
  @param[in] OverrideMask  - Override bit mask.
  @param[in] StartTestSync - Start test sync control.
**/
void
MrcHalSetCkeOverrideConfiguration (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL RankMask,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL OverrideMask,
  IN const MRC_HAL_ENUM_START_TEST_SYNC   StartTestSync
  )
{
  MrcHalSetRegReutChMiscCkeCtrl (
    MrcData,
    Channel,
    MrcHalSetBfMchbarCh0CrReutChMiscCkeCtrlCkeOverride (
      (UINT32) OverrideMask,
      MrcHalSetBfMchbarCh0CrReutChMiscCkeCtrlCkeOn (
        (UINT32) RankMask,
        MrcHalSetBfMchbarCh0CrReutChMiscCkeCtrlCkeEnStartTestSync (
          (UINT32) StartTestSync,
          0
          )
        )
      )
    );
  return;
}

/**
  Function used to get the current sequence state.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Channel      - Zero based channel number.
  @param[out] LoopCount   - Pointer to buffer containing current loop count.
  @param[out] SubSeqIndex - Pointer to buffer containing current subsequence index.
  @param[out] Cacheline   - Pointer to buffer containing current cacheline.
  @param[out] BaseRank    - Pointer to buffer containing current base rank.
  @param[out] BaseBank    - Pointer to buffer containing current base bank.
  @param[out] BaseRow     - Pointer to buffer containing current base row.
  @param[out] BaseCol     - Pointer to buffer containing current base column.
  @param[out] OffsetRow   - Pointer to buffer containing current offset row.
  @param[out] OffsetCol   - Pointer to buffer containing current offset column.
**/
void
MrcHalGetCurrentSubSeqStatus (
  IN  MrcParameters *const MrcData,
  IN  const UINT32         Channel,
  OUT UINT32               *LoopCount,
  OUT UINT8                *SubSeqIndex,
  OUT UINT32               *Cacheline,
  OUT UINT8                *BaseRank,
  OUT UINT8                *BaseBank,
  OUT UINT32               *BaseRow,
  OUT UINT32               *BaseCol,
  OUT UINT32               *OffsetRow,
  OUT UINT32               *OffsetCol
  )
{
  UINT64 RegisterValue;

  *LoopCount   = (UINT32) MrcHalGetSeqLoopcountStatus (MrcData, Channel);
  *SubSeqIndex = (UINT8) MrcHalGetSeqPointer (MrcData, Channel);
  *Cacheline   = (UINT32) MrcHalGetSeqCurrentCacheline (MrcData, Channel);

  RegisterValue = MrcHalGetBaseAddressCurrent (MrcData, Channel);
  *BaseRank = (UINT8) MrcHalGetBfMcdfxsCrReutChSeqBaseAddrCurrentMcmain0RankAddress (MrcData, RegisterValue);
  *BaseBank = (UINT8) MrcHalGetBfMcdfxsCrReutChSeqBaseAddrCurrentMcmain0BankAddress (MrcData, RegisterValue);
  *BaseRow  = (UINT32) MrcHalGetBfMcdfxsCrReutChSeqBaseAddrCurrentMcmain0RowAddress (MrcData, RegisterValue);
  *BaseCol  = (UINT32) MrcHalGetBfMcdfxsCrReutChSeqBaseAddrCurrentMcmain0ColumnAddress (MrcData, RegisterValue);

  RegisterValue = MrcHalGetOffsetAddressCurrent (MrcData, Channel);
  *OffsetRow = (UINT32) MrcHalGetBfMcdfxsCrReutChSeqOffsetAddrCurrentMcmain0RowAddress (MrcData, RegisterValue);
  *OffsetCol = (UINT32) MrcHalGetBfMcdfxsCrReutChSeqOffsetAddrCurrentMcmain0ColumnAddress (MrcData, RegisterValue);

  return;
}

/**
  This function sets write data buffer capture controls.

  @param[in] MrcData                   - Include all MRC global data.
  @param[in] Channel                   - Zero based channel number.
  @param[in] EnableWdbCapture          - Write data buffer capture enable.
  @param[in] WdbErrorSelCapture        - Write data buffer error select capture control.
  @param[in] WdbDataSelCapture         - Write data buffer data select capture control.
  @param[in] WdbStartingCapturePointer - Write data buffer starting capture pointer.
  @param[in] WdbEndingCapturePointer   - Write data buffer ending capture pointer.
**/
void
MrcHalRmwWdbCaptureControl (
  IN MrcParameters *const   MrcData,
  IN const UINT32           Channel,
  IN const UINT32           EnableWdbCapture,
  IN const UINT32           WdbErrorSelCapture,
  IN const UINT32           WdbDataSelCapture,
  IN const UINT32           WdbStartingCapturePointer,
  IN const UINT32           WdbEndingCapturePointer
  )
{
  UINT32 RegisterValue;

  RegisterValue = MrcHalGetReutWdbCaptureControl (MrcData, (Channel >= MAX_CHANNEL) ? 0 : Channel);
  if (EnableWdbCapture != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChWdbCaptureCtlEnableWdbCapture (EnableWdbCapture, RegisterValue);
  }
  if (WdbErrorSelCapture != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChWdbCaptureCtlWdbErrorSelCapture (WdbErrorSelCapture, RegisterValue);
  }
  if (WdbDataSelCapture != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChWdbCaptureCtlWdbDataSelCapture (WdbDataSelCapture, RegisterValue);
  }
  if (WdbStartingCapturePointer != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChWdbCaptureCtlWdbStartingCapturePointer (WdbStartingCapturePointer, RegisterValue);
  }
  if (WdbEndingCapturePointer != MRC_IGNORE_ARG) {
    RegisterValue = MrcHalSetBfMchbarCh0CrReutChWdbCaptureCtlWdbEndingCapturePointer (WdbEndingCapturePointer, RegisterValue);
  }

  if (Channel >= MAX_CHANNEL) {
    MrcHalSetRegMcmntsCrReutChWdbCaptureCtl (MrcData, RegisterValue);
  } else {
    MrcHalSetReutWdbCaptureControl (MrcData, Channel, RegisterValue);
  }
  return;
}

/**
  Top level function used to interact with DDRIO parameters.
    NOTE: This assumes the max register size of DDRIO Group is 32-bits.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Dimm      - DIMM Number within the DDR Channel (0-based). Ignored as Rank is rank number in the channel.
  @param[in]      Rank      - Rank number within a channel (0-based).
  @param[in]      Strobe    - Dqs data group within the rank (0-based).
  @param[in]      Bit       - Bit index within the data group (0-based).
  @param[in]      FreqIndex - Index supporting multiple operating frequencies.
  @param[in]      Level     - DDRIO level to access.
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroup (
  IN      MrcParameters *const  MrcData,
  IN      UINT8         const   Socket,
  IN      UINT8         const   Channel,
  IN      UINT8         const   Dimm,
  IN      UINT8         const   Rank,
  IN      UINT8         const   Strobe,
  IN      UINT8         const   Bit,
  IN      UINT8         const   FreqIndex,
  IN      GSM_LT        const   Level,
  IN      GSM_GT        const   Group,
  IN      UINT8         const   Mode,
  IN OUT  INT64         *const  Value
  )
{
  MrcStatus         Status;
  UINT32            Offset;
  UINT32            Delay;
  INT64             CurrentVal;
  INT64             WriteVal;
  INT64             Min;
  INT64             Max;
  UINT64            RegVal;
  UINT64            NewRegVal;
  BOOLEAN           RegSize;
  MRC_REGISTER_HASH_STRUCT HashVal;
#ifdef MRC_DEBUG_PRINT
  MrcDebug          *Debug;
  BOOLEAN           ReadCrFlag;

  Debug      = &MrcData->Outputs.Debug;
  ReadCrFlag = (Mode & GSM_READ_CSR) == GSM_READ_CSR;

  //
  // Check that the level is supported
  //
  switch (Level) {
    case DdrLevel:
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Level %d is not supported!\n", Level);
      return mrcWrongInputParameter;
      break;
  }

  //
  // Check that the Group is supported
  //
  switch (Group) {
    case RecEnDelay:
    case RxDqsPDelay:
    case RxDqsNDelay:
    case RxVref:
    case RxEq:
    case RxDqBitDelay:
    case RxOdt:
    case RxOdtUp:
    case RxOdtDn:
    case RxCtleR:
    case RxCtleC:
    case TxDqsDelay:
    case TxDqDelay:
    case TxEq:
    case TxDqBitDelay:
    case TxRonUp:
    case TxRonDn:
    case TxSlewRate:
    case RecEnOffset:
    case RxDqsOffset:
    case RxVrefOffset:
    case TxDqsOffset:
    case TxDqOffset:
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Group %d is not supported!\n", Group);
      return mrcWrongInputParameter;
      break;
  }

  //
  // Ensure no one is trying to read with multicast parameters.
  //
  if ((ReadCrFlag) && (
                        ((Channel != MRC_IGNORE_ARG_8) && (Channel >= MAX_CHANNEL)) ||
                        ((Rank != MRC_IGNORE_ARG_8) && (Rank >= MAX_RANK_IN_CHANNEL)) ||
                        ((Strobe != MRC_IGNORE_ARG_8) && (Strobe >= MAX_SDRAM_IN_DIMM)))) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Attempted to read from a Multicast. Group: %u Channel: %u, Rank: %u, Byte: %u\n",
      Group, Channel, Rank, Strobe);
    return mrcWrongInputParameter;
  }
#endif // MRC_DEBUG_PRINT

  //
  // Get CR offset and field hash value
  //
  Status = MrcGetDdrIoHash (MrcData, Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex, &HashVal.Data);
  if (Status == mrcSuccess) {
    Offset = HashVal.Bits.Offset;
    RegSize = (HashVal.Bits.RegSize != 0);

    //
    // Init data.
    //
    RegVal = MrcCrCacheRead (MrcData, Offset, RegSize, Mode, Group, Socket, Channel, Rank, Strobe, Bit);

    //
    // Get the group value
    //
    CurrentVal = MrcHalGsmGetBitField (MrcData, HashVal, RegVal);

    if ((Mode & GSM_READ_ONLY) == GSM_READ_ONLY) {
      *Value = CurrentVal;
    } else {
      WriteVal = ((Mode & GSM_WRITE_OFFSET) == GSM_WRITE_OFFSET) ? CurrentVal + *Value : *Value;

      //
      // Check value limits.
      //
      MrcGetDdrIoGroupLimits (MrcData, Socket, Channel, Dimm, Level, Group, &Min, &Max, &Delay);
#ifdef MRC_DEBUG_PRINT
      if ((WriteVal < Min) || (WriteVal > Max)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Group %u is out of range [%ld:%ld].  Clamped to %ld\n", Group, Min, Max, WriteVal);
      }
#endif
      WriteVal = RANGE (WriteVal, Min, Max);

      //
      // Update CR with new value
      //
      NewRegVal = MrcHalGsmSetBitField (MrcData, HashVal, WriteVal, RegVal);
      if (((Mode & GSM_FORCE_WRITE) == GSM_FORCE_WRITE) || (RegVal != NewRegVal)) {
        MrcCrCacheWrite (MrcData, Offset, RegSize, Mode, Group, Socket, Channel, Rank, Strobe, Bit, Delay, NewRegVal);
      }
    }
  }

#ifdef MRC_DEBUG_PRINT
  if (Status != mrcSuccess) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MrcGetSetDdrIoGroup status %u\n", Status);
  }
#endif
  return Status;
}

/**
  This function handles getting the register offset for the requested parameter.
  It will determine multicast by the parameter exceeding the MAX of the
  Socket/Channel/Rank/Strobe/Bit.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - DDRIO group to access.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  Rank      - Rank number within a channel (0-based).
  @param[in]  Strobe    - Dqs data group within the rank (0-based).
  @param[in]  Bit       - Bit index within the data group (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] Offset    - Pointer to return the MMIO Offset in.

  @retval MrcStatus
**/
MrcStatus
MrcGetDdrIoRegOffset (
  IN  MrcParameters *const  MrcData,
  IN  GSM_GT  const   Group,
  IN  UINT8   const   Socket,
  IN  UINT8   const   Channel,
  IN  UINT8   const   Rank,
  IN  UINT8   const   Strobe,
  IN  UINT8   const   Bit,
  IN  UINT8   const   FreqIndex,
  OUT UINT32  *const  Offset
  )
{
  MrcStatus       Status;
  MrcDebug        *Debug;
  MRC_REG_OFFSETS RegOffset;

  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;

  switch (Group) {
    case RecEnDelay:
    case RxDqsPDelay:
    case RxDqsNDelay:
    case RxVref:
    case RxEq:
    case RxDqBitDelay:
      *Offset = GetDdrIoDataReadOffsets (Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex, &RegOffset);
      break;

    case RxOdt:
      *Offset = DDRCOMP_CR_DDRCRCOMPCTL0_REG;
      break;

    case RxCtleR:
      *Offset = GetDdrIoDataControl1 (Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex);
      break;

    case RxCtleC:
      *Offset = GetDdrIoDataControl2 (Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex);
      break;

    case TxDqsDelay:
    case TxDqDelay:
    case TxEq:
    case TxDqBitDelay:
      *Offset = GetDdrIoDataWriteOffsets (Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex, &RegOffset);
      break;

    case RecEnOffset:
    case RxDqsOffset:
    case RxVrefOffset:
    case TxDqsOffset:
    case TxDqOffset:
      *Offset = GetDdrIoDataTrainOffsets (Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex, &RegOffset);
      break;

    case RxOdtUp:
    case RxOdtDn:
    case TxRonUp:
    case TxRonDn:
    case TxSlewRate:
      *Offset = GetDdrIoDataOffsetComp (Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex);
      break;

    default:
      // @todo: create strings for each group used for MRC_DEBUG_PRINT
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Group %u is unsupported\n", Group);
      Status = mrcWrongInputParameter;
      break;
  }

  if (*Offset == MRC_UINT32_MAX) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Register Offset is undefined. Group %u Channel %u Rank %u Strobe %u\n",
      Group, Channel, Rank, Strobe);
    Status = mrcWrongInputParameter;
  }

  return Status;
}

/**
  This function returns the register limits.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  Dimm      - DIMM index in the channel. (0-based).
  @param[in]  Level     - DDRIO level to access.
  @param[in]  Group     - DDRIO group to access.
  @param[out] MinVal    - Return pointer for Minimum Value supported.
  @param[out] MaxVal    - Return pointer for Maximum Value supported.
  @param[out] WaitTime  - Return pointer for settle time required in microseconds.

  @retval MrcStatus
**/
MrcStatus
MrcGetDdrIoGroupLimits (
  IN  MrcParameters *const MrcData,
  IN  UINT8   const   Socket,
  IN  UINT8   const   Channel,
  IN  UINT8   const   Dimm,
  IN  GSM_LT  const   Level,
  IN  GSM_GT  const   Group,
  OUT INT64   *const  MinVal,
  OUT INT64   *const  MaxVal,
  OUT UINT32  *const  WaitTime
  )
{
  MrcStatus Status;
  Status    = mrcSuccess;
  *WaitTime = 0;

  switch (Group) {
    case RecEnDelay:
      *MinVal = DDRDATA0CH0_CR_RXTRAINRANK0_RxRcvEnPi_MIN;
      *MaxVal = DDRDATA0CH0_CR_RXTRAINRANK0_RxRcvEnPi_MAX;
      break;

    case RxDqsPDelay:
      *MinVal = DDRDATA0CH0_CR_RXTRAINRANK0_RxDqsPPi_MIN;
      *MaxVal = DDRDATA0CH0_CR_RXTRAINRANK0_RxDqsPPi_MAX;
      break;

    case RxDqsNDelay:
      *MinVal = DDRDATA0CH0_CR_RXTRAINRANK0_RxDqsNPi_MIN;
      *MaxVal = DDRDATA0CH0_CR_RXTRAINRANK0_RxDqsNPi_MAX;
      break;

    case RxVref:
      *MinVal = DDRDATA0CH0_CR_RXTRAINRANK0_RxVref_MIN;
      *MaxVal = DDRDATA0CH0_CR_RXTRAINRANK0_RxVref_MAX;
      break;

    case RxEq:
      *MinVal = DDRDATA0CH0_CR_RXTRAINRANK0_RxEq_MIN;
      *MaxVal = DDRDATA0CH0_CR_RXTRAINRANK0_RxEq_MAX;
      break;

    case RxDqBitDelay:
      *MinVal = DDRDATA0CH0_CR_RXPERBITRANK0_Lane0_MIN;
      *MaxVal = DDRDATA0CH0_CR_RXPERBITRANK0_Lane0_MAX;
      break;

    case RxOdt:
      *MinVal = DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_MIN;
      *MaxVal = DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_MAX;
      break;

    case RxOdtUp:
      *MinVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MIN;
      *MaxVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MAX;
      break;

    case RxOdtDn:
      *MinVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MIN;
      *MaxVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MAX;
      break;

    case RxCtleR:
      *MinVal = DDRDATA0CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_MIN;
      *MaxVal = DDRDATA0CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_MAX;
      break;

    case RxCtleC:
      *MinVal = DDRDATA0CH0_CR_DDRCRDATACONTROL2_Cben_MIN;
      *MaxVal = DDRDATA0CH0_CR_DDRCRDATACONTROL2_Cben_MAX;
      break;

    case TxDqsDelay:
      *MinVal = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqsDelay_MIN;
      *MaxVal = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqsDelay_MAX;
      break;

    case TxDqDelay:
      *MinVal = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MIN;
      *MaxVal = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX;
      break;

    case TxEq:
      *MinVal = DDRDATA0CH0_CR_TXTRAINRANK0_TxEqualization_MIN;
      *MaxVal = DDRDATA0CH0_CR_TXTRAINRANK0_TxEqualization_MAX;
      break;

    case TxDqBitDelay:
      *MinVal = DDRDATA0CH0_CR_TXPERBITRANK0_Lane0_MIN;
      *MaxVal = DDRDATA0CH0_CR_TXPERBITRANK0_Lane0_MAX;
      break;

    case TxRonUp:
      *MinVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MIN;
      *MaxVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MAX;
      break;

    case TxRonDn:
      *MinVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MIN;
      *MaxVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MAX;
      break;

    case TxSlewRate:
      *MinVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MIN;
      *MaxVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MAX;
      break;

    case RecEnOffset:
      *MinVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MIN;
      *MaxVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MAX;
      break;

    case RxDqsOffset:
      *MinVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MIN;
      *MaxVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MAX;
      break;

    case RxVrefOffset:
      *MinVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MIN;
      *MaxVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MAX;
      break;

    case TxDqsOffset:
      *MinVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MIN;
      *MaxVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MAX;
      break;

    case TxDqOffset:
      *MinVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MIN;
      *MaxVal = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MAX;
      break;

    default:
      // @todo: create strings for each group used for MRC_DEBUG_PRINT
      MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "Group %u has no limits defined\n", Group);
      *MinVal = MRC_INT64_MIN;
      *MaxVal = MRC_INT64_MAX;
      Status = mrcWrongInputParameter;
      break;
  }

  return Status;
}
/**
  This function generates the hash used to execute the Get/Set function.
  The hash consists of: Register Offset, BitField start bit, BitField length.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - DDRIO group to access.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  Rank      - Rank number within a channel (0-based).
  @param[in]  Strobe    - Dqs data group within the rank (0-based).
  @param[in]  Bit       - Bit index within the data group (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] Offset    - Pointer to return the MMIO Offset in.

  @retval MrcStatus
**/
MrcStatus
MrcGetDdrIoHash (
  IN  MrcParameters *const  MrcData,
  IN  GSM_GT  const   Group,
  IN  UINT8   const   Socket,
  IN  UINT8   const   Channel,
  IN  UINT8   const   Rank,
  IN  UINT8   const   Strobe,
  IN  UINT8   const   Bit,
  IN  UINT8   const   FreqIndex,
  OUT UINT32  *const  HashVal
  )
{
  MrcStatus Status;
  MrcDebug  *Debug;
  MRC_REGISTER_HASH_STRUCT *HashPtr;
  UINT32 CrOffset = MRC_UINT32_MAX;

  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;
  HashPtr = (MRC_REGISTER_HASH_STRUCT *) HashVal;

  switch (Group) {
    case RecEnDelay:
      HashPtr->Data = DDRDATA0CH0_CR_RXTRAINRANK0_RxRcvEnPi_HSH;
      break;

    case RxDqsPDelay:
      HashPtr->Data = DDRDATA0CH0_CR_RXTRAINRANK0_RxDqsPPi_HSH;
      break;

    case RxDqsNDelay:
      HashPtr->Data = DDRDATA0CH0_CR_RXTRAINRANK0_RxDqsNPi_HSH;
      break;

    case RxVref:
      HashPtr->Data = DDRDATA0CH0_CR_RXTRAINRANK0_RxVref_HSH;
      break;

    case RxEq:
      HashPtr->Data = DDRDATA0CH0_CR_RXTRAINRANK0_RxEq_HSH;
      break;

    case RxDqBitDelay:
      switch (Bit) {
        default:
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Hash is undefined. Group %u Channel %u Rank %u Strobe %u Bit %u\n",
            Group, Channel, Rank, Strobe, Bit);
          Status = mrcWrongInputParameter;
          // no break;
        case 0:
          HashPtr->Data = DDRDATA0CH0_CR_RXPERBITRANK0_Lane0_HSH;
          break;

        case 1:
          HashPtr->Data = DDRDATA0CH0_CR_RXPERBITRANK0_Lane1_HSH;
          break;

        case 2:
          HashPtr->Data = DDRDATA0CH0_CR_RXPERBITRANK0_Lane2_HSH;
          break;

        case 3:
          HashPtr->Data = DDRDATA0CH0_CR_RXPERBITRANK0_Lane3_HSH;
          break;

        case 4:
          HashPtr->Data = DDRDATA0CH0_CR_RXPERBITRANK0_Lane4_HSH;
          break;

        case 5:
          HashPtr->Data = DDRDATA0CH0_CR_RXPERBITRANK0_Lane5_HSH;
          break;

        case 6:
          HashPtr->Data = DDRDATA0CH0_CR_RXPERBITRANK0_Lane6_HSH;
          break;

        case 7:
          HashPtr->Data = DDRDATA0CH0_CR_RXPERBITRANK0_Lane7_HSH;
          break;
      }
      break;

    case RxOdt:
      HashPtr->Data = DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_HSH;
      break;

    case RxOdtUp:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_HSH;
      break;

    case RxOdtDn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_HSH;
      break;

    case RxCtleR:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_HSH;
      break;

    case RxCtleC:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_Cben_HSH;
      break;

    case TxDqsDelay:
      HashPtr->Data = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqsDelay_HSH;
      break;

    case TxDqDelay:
      HashPtr->Data = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_HSH;
      break;

    case TxEq:
      HashPtr->Data = DDRDATA0CH0_CR_TXTRAINRANK0_TxEqualization_HSH;
      break;

    case TxDqBitDelay:
      switch (Bit) {
        default:
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Hash is undefined. Group %u Channel %u Rank %u Strobe %u Bit %u\n",
            Group, Channel, Rank, Strobe, Bit);
          Status = mrcWrongInputParameter;
          // no break;
        case 0:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITRANK0_Lane0_HSH;
          break;

        case 1:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITRANK0_Lane1_HSH;
          break;

        case 2:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITRANK0_Lane2_HSH;
          break;

        case 3:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITRANK0_Lane3_HSH;
          break;

        case 4:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITRANK0_Lane4_HSH;
          break;

        case 5:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITRANK0_Lane5_HSH;
          break;

        case 6:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITRANK0_Lane6_HSH;
          break;

        case 7:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITRANK0_Lane7_HSH;
          break;
      }
      break;

    case TxRonUp:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_HSH;
      break;

    case TxRonDn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_HSH;
      break;

    case TxSlewRate:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_HSH;
      break;

    case RecEnOffset:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_HSH;
      break;

    case RxDqsOffset:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_HSH;
      break;

    case RxVrefOffset:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_HSH;
      break;

    case TxDqsOffset:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_HSH;
      break;

    case TxDqOffset:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_HSH;
      break;

    default:
      // @todo: create strings for each group used for MRC_DEBUG_PRINT
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Hash is undefined. Group %u Channel %u Rank %u Strobe %u\n",
        Group, Channel, Rank, Strobe);
      Status = mrcWrongInputParameter;
      break;
  }

  if (Status == mrcSuccess) {
    Status = MrcGetDdrIoRegOffset (MrcData, Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex, &CrOffset);
  }

  HashPtr->Bits.Offset = CrOffset;

  return Status;
}

#ifdef MRC_DEBUG_PRINT
/**
  This function outputs the specified group values to the debug print device.

  @param[in] MrcData   - Pointer to global data.
  @param[in] Group     - DDRIO group to access.
  @param[in] Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in] Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in] Rank      - Rank number within a channel (0-based).
  @param[in] Strobe    - Dqs data group within the rank (0-based).
  @param[in] Bit       - Bit index within the data group (0-based).
  @param[in] FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval MrcStatus
**/
MrcStatus
MrcPrintDdrIoGroup (
  IN MrcParameters *const  MrcData,
  IN UINT8   const Socket,
  IN UINT8   const Channel,
  IN UINT8   const Rank,
  IN UINT8   const Strobe,
  IN UINT8   const Bit,
  IN UINT8   const FreqIndex,
  IN GSM_GT  const Group
  )
{
  MrcDebug *Debug;
  INT64_STRUCT Value;
  UINT8        Byte;
  UINT8        BitIndex;

  Debug = &MrcData->Outputs.Debug;
  switch (Group) {
    case RecEnDelay:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RecEnDelay Channel %u Rank %u:\n", Channel, Rank);
      for (Byte = Strobe; Byte < MrcData->Outputs.SdramCount; Byte++) {
        MrcGetSetDdrIoGroup (
          MrcData,
          SOCKET_0,
          Channel,
          MRC_IGNORE_ARG_8,
          Rank,
          Byte,
          MRC_IGNORE_ARG_8,
          MRC_IGNORE_ARG_8,
          DdrLevel,
          RecEnDelay,
          GSM_READ_ONLY,
          &Value.Data
          );
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " B%u: %d\n", Byte, Value.Data32.Low);
      } // Byte
      break;

    case RxDqBitDelay:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RxDqBitDelay Channel %u Rank %u Byte %u:", Channel, Rank, Strobe);
      for (BitIndex = 0; BitIndex < MAX_BITS; BitIndex++) {
        MrcGetSetDdrIoGroup (
          MrcData,
          SOCKET_0,
          Channel,
          MRC_IGNORE_ARG_8,
          Rank,
          Strobe,
          BitIndex,
          MRC_IGNORE_ARG_8,
          DdrLevel,
          RxDqBitDelay,
          GSM_READ_ONLY,
          &Value.Data
          );
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %02X", Value.Data32.Low);
      } // Bit
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
      break;

    default:
      break;
  }
  return (mrcSuccess);
}
#endif
#endif // SSA_FLAG
