/** @file
  This file contains the call table functions to execute a memory test
  through the Dimm Cell Test Tool library.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

@par Specification
**/
#include "DcttApi.h"
#include "MrcDimmCellTest.h"
#include "MrcCommon.h"
#include "MrcDebugPrint.h"
#include "MrcReset.h"
///
/// Local and Public functions.
///
/**
  Mrc hook to read a 32-bit register.

  @param[in] DcttMain - Pointer to DCTT global structure.
  @param[in] Offset   - Offset of of MCHBAR to read.

  @retval UINT32 - Register value.
**/
UINT32
DcttRead32 (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT32            Offset
  )
{
  UINT32 RetVal = 0;

  RetVal = MrcReadCR ((MrcParameters *) DcttMain->MrcData, Offset);

  return RetVal;
}

/**
  MRC hook to read a 64-bit register.

  @param[in] DcttMain - Pointer to DCTT global structure.
  @param[in] Offset   - Offset of MCHBAR to read.

  @retval UINT64 - Register value.
**/
UINT64
DcttRead64 (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT32            Offset
  )
{
  UINT64 RetVal = 0;

  RetVal = MrcReadCR64 ((MrcParameters *) DcttMain->MrcData, Offset);

  return RetVal;
}

/**
  MRC hook to write a 32-bit register.

  @param[in] DcttMain - Pointer to DCTT global structure.
  @param[in] Offset   - Offset off of MCHBAR.
  @param[in] Data     - Value to write.

  @retval VOID - Nothing.
**/
VOID
DcttWrite32 (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT32            Offset,
  IN  UINT32            Data
  )
{
  MrcWriteCR ((MrcParameters *) DcttMain->MrcData, Offset, Data);
}

/**
  MRC hook to write a 64-bit register.

  @param[in] DcttMain - Pointer to DCTT global structure.
  @param[in] Offset   - Offset off of MCHBAR.
  @param[in] Data     - Value to write.

  @retval VOID - Nothing.
**/
VOID
DcttWrite64 (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT32            Offset,
  IN  UINT64            Data
  )
{
  MrcWriteCR64 ((MrcParameters *) DcttMain->MrcData, Offset, Data);
}

/**
  MRC hook to get the present channel bit mask.

  @param[in] DcttMain   - Pointer to DCTT global structure.
  @param[in] Controller - Controller index.

  @retval UINT8 - Channel bit mask.
**/
UINT8
DcttGetPresentChannelBitMask (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT8             Controller
  )
{
  return (Controller < MAX_CONTROLLERS) ? ((MrcParameters *) DcttMain->MrcData)->Outputs.ValidChBitMask : 0;
}

/**
  MRC hook to determine if the channel exists in the system.

  @param[in] DcttMain   - Pointer to DCTT global structure.
  @param[in] Controller - Controller index.
  @param[in] Channel    - Channel index.

  @retval BOOLEAN - TRUE if the channel exists on the controller; Otherwise, FALSE.
**/
BOOLEAN
DcttChannelExists (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT8             Controller,
  IN  UINT8             Channel
  )
{
  BOOLEAN RetVal = FALSE;
  if (Controller < MAX_CONTROLLERS) {
    if (MrcChannelExist (&((MrcParameters *) DcttMain->MrcData)->Outputs, Channel)) {
      RetVal = TRUE;
    }
  }

  return RetVal;
}

/**
  MRC hook to determine if the specified rank exists in the channel/controller.

  @param[in] DcttMain   - Pointer to DCTT global structure.
  @param[in] Controller - Controller index.
  @param[in] Channel    - Channel index.
  @param[in] Rank       - Rank index.

  @retval BOOLEAN - TRUE if the rank exists; Otherwise FALSE.
**/
BOOLEAN
DcttRankInChannelExists (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT8             Controller,
  IN  UINT8             Channel,
  IN  UINT8             Rank
  )
{
  if ((Controller < MAX_CONTROLLERS) && (MrcRankInChannelExist ((MrcParameters *) DcttMain->MrcData, Rank, Channel) > 0)) {
    return TRUE;
  }

  return FALSE;
}

/**
  MRC hook to enter Self Refresh.

  @param[in]  DcttMain  - Pointer to DCTT global structure.

  @retval Nothing
**/
VOID
DcttEnterSelfRefresh (
  IN  DCTT_API  *const  DcttMain
  )
{
  EnterSR ((MrcParameters *) DcttMain->MrcData);
}

/**
  MRC hook to exit Self Refresh.

  @param[in]  DcttMain  - Pointer to DCTT global structure.

  @retval Nothing
**/
VOID
DcttExitSelfRefresh (
  IN  DCTT_API  *const  DcttMain
  )
{
  ExitSR ((MrcParameters *) DcttMain->MrcData);
}

/**
  MRC hook to get the Memory Controller operating frequency.

  @param[in] DcttMain   - Pointer to DCTT global structure.
  @param[in] Controller - Controller index.

  @retval UINT32 - Frequency in MHz.
**/
UINT32
DcttGetMcFrequency (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT8             Controller
  )
{
  return (Controller < MAX_CONTROLLERS) ? ((MrcParameters *) DcttMain->MrcData)->Outputs.Frequency : 0;
}

/**
  @todo: Refactor out where DCTT doesn't need register address info.  For now, DCTT register defineds are based
         on channel 0 of the register.
  MRC Hook to get the address to read/write a register.

  @param[in] MainHandle - Used to get the CallBack function pointer.
  @param[in] Offset     - Register bar Offset.
  @param[in] Controller - Memory Controller index.
  @param[in] Channel    - Channel the register operates on. This is used for loop iteration.
                          If not used, leave as 0
  @param[in] ExtraIndex   - Separate register index using for looping when multiple registers exist on one Channel.
                          If not used, leave as 0

  @retval UINT32 - The requested register address.
**/
UINT32
DcttGetMcAddress (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT32            Register,
  IN  UINT8             Controller,
  IN  UINT8             Channel,
  IN  UINT8             ExtraIndex
  )
{
  UINT32  RetVal  = 0xFFFFFFFF;

  switch (Register) {
    case MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_CFG
    case MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL
    case MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_BASE_ADDR_START
    case MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP
    case MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0
    case MCDFXS_CR_REUT_CH_SEQ_OFFSET_ADDR_CURRENT_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0
    case MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_CURRENT_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_0
      RetVal = Register + (8 * Channel);
      break;

    case MCDFXS_CR_REUT_CH_SEQ_CTL_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_CTL
    case MCDFXS_CR_REUT_CH_SEQ_SUBSEQ_PNTR_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_SUBSEQ_PTR_0
    case MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL
    case MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0
    case MCDFXS_CR_REUT_CH_SEQ_CACHELINE_STATUS_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_CACHELINE_STATUS_0
    case MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_DUMMYREAD_MASK_0 <ST> Fix for enabling dummyreads
    case MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_0
    case MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_0
      RetVal = Register + (4 * Channel);
      break;

    case MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_0_REG: //DCTT_REUT_CH_SEQ_LOOPCOUNT_LIMIT
      RetVal = Register + (4 * Channel);
      break;

    case MCHBAR_CH0_CR_REUT_CH_WDB_CAPTURE_CTL_REG: //DCTT_REUT_WDB_CAPTURE_CTL
    case MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_REG: //DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS
    case MCHBAR_CH0_CR_REUT_CH_ERR_DATA_STATUS_REG: //DCTT_REUT_CH_ERR_DATA_STATUS
    case MCHBAR_CH0_CR_REUT_CH_ERROR_ADDR_REG: //DCTT_REUT_CH_ERROR_Address
    case MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_REG: //DCTT_REUT_CH_PAT_WDB_CL_CTRL
    case MCHBAR_CH0_CR_REUT_CH_ERR_CTL_REG: //DCTT_REUT_CH_ERR_CTL
    case MCHBAR_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG: //DCTT_REUT_CH_MISC_REFRESH_CTRL
    case MCHBAR_CH0_CR_TC_PRE_REG: //DCTT_CH_TC_PRE_REG
    case MCHBAR_CH0_CR_TC_ODT_REG: //DCTT_CH_TC_ODT_REG
      RetVal = Register + (0x400 * Channel);
      break;

    case MCDFXS_CR_REUT_GLOBAL_ERR_MCMAIN_REG: //DCTT_REUT_GLOBAL_ERR
    case MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG: //DCTT_REUT_GLOBAL_CTRL
      RetVal = Register;
      break;

    case MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_REG: //DCTT_REUT_CH_SUBSEQ_CTL_0
    case MCDFXS_CR_REUT_CH0_SUBSEQ_OFFSET_CTL_MCMAIN_0_REG: //DCTT_REUT_CH_SUBSEQ_OFFSET_CTL_0
      RetVal = Register + (0x28 * Channel) + ExtraIndex * 4;
      break;

    case MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_REG: //DCTT_REUT_CH_ERR_COUNTER_STATUS
      RetVal = Register + (0x400 * Channel) + ExtraIndex * 4;
      break;

    default:
      //
      // Assert, unimplemented register
      //
      MRC_ASSERT (
        1 == 0,
        &((MrcParameters *) DcttMain->MrcData)->Outputs.Debug,
        "Register Offset %d is not supported yet.",
        Register
        );
  }

  return RetVal;
}

/**
  @todo: Refactor to be MRC independent
  This function will program the requested type of pattern to the specific WDB entry.

  @param[in] MainHandle - Used to get the CallBack function pointer.
  @param[in] Controller - Memory Controller index.
  @param[in] Patterns   - Pointer to pattern type.
  @param[in] Mask       - Pointer to bit lane mask select.
  @param[in] Spread     - Number of entries in arrays.
  @param[in] Start      - WDB to start at.

  @retval VOID - Nothing
**/
VOID
DcttSetWdbFixedPat (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT8             Controller,
  IN  UINT8*            Patterns,
  IN  UINT8*            Mask,
  IN  UINT8             Spread,
  IN  UINT8             Start
  )
{
  if (Controller < MAX_CONTROLLERS) {
    WriteWDBFixedPattern ((MrcParameters *) DcttMain->MrcData, Patterns, Mask, Spread, Start);
  }
}

/**
  Getsystem Refi.

  @param[in] MainHandle - Used to get the CallBack function pointer.
  @param[in] Controller - Memory Controller index.
  @param[in] Channel    - Channel index.

  @retval UINT16 - Current tRefi
**/
UINT16
DcttGetRefi (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT8             Controller,
  IN  UINT8             Channel
  )
{
  MrcParameters *MrcData;
  UINT16         RetVal = 0;

  if (Controller < MAX_CONTROLLERS) {
    MrcData = (MrcParameters *) DcttMain->MrcData;
    RetVal = MrcData->Outputs.Controller[Controller].Channel[Channel].Timing[MrcData->Inputs.MemoryProfile].tREFI;
  }

  return RetVal;
}

/**
  Set system Refi.  This will update all refresh timings dependent on tRefi.

  @param[in] MainHandle - Used to get the CallBack function pointer.
  @param[in] Controller - Memory Controller index.
  @param[in] Channel    - Channel index.
  @param[in] Value      - Refi value to program in DClk cycles.

  @retval UINT16 - tRefi programmed
**/
UINT16
DcttSetRefi (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT8             Controller,
  IN  UINT8             Channel,
  IN  UINT16             Value
  )
{
  MrcParameters *MrcData;
  UINT16         RetVal = 0;

  MrcData = (MrcParameters *) DcttMain->MrcData;
  if ((Controller < MAX_CONTROLLERS) && (Channel < MAX_CHANNEL) && (MrcData->Inputs.MemoryProfile < MAX_PROFILE)) {
    RetVal   = MIN (MCHBAR_CH0_CR_TC_RFTP_tREFI_MAX, Value);
    MrcData->Outputs.Controller[Controller].Channel[Channel].Timing[MrcData->Inputs.MemoryProfile].tREFI = RetVal;

    SetTcRfpRftpReg (MrcData, Channel);
  }

  return RetVal;
}

/**
  Returns the row size of the DIMM.

  @param[in] MainHandle - Used to get the CallBack function pointer.
  @param[in] Controller - Memory Controller index.
  @param[in] Channel    - Channel index.
  @param[in] Dimm       - Dimm index.

  @retval UINT32 - Row size.
**/
UINT32
DcttGetDimmRowSize (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT8             Controller,
  IN  UINT8             Channel,
  IN  UINT8             Dimm
  )
{
  return (Controller < MAX_CONTROLLERS) ?
  ((MrcParameters *) DcttMain->MrcData)->Outputs.Controller[Controller].Channel[Channel].Dimm[Dimm].RowSize : 0;
}

/**
  Returns the column size of the DIMM.

  @param[in] MainHandle - Used to get the CallBack function pointer.
  @param[in] Controller - Memory Controller index.
  @param[in] Channel    - Channel index.
  @param[in] Dimm       - Dimm index.

  @retval UINT16 - Column size.
**/
UINT16
DcttGetDimmColumnSize (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT8             Controller,
  IN  UINT8             Channel,
  IN  UINT8             Dimm
  )
{
  return (Controller < MAX_CONTROLLERS) ?
  ((MrcParameters *) DcttMain->MrcData)->Outputs.Controller[Controller].Channel[Channel].Dimm[Dimm].ColumnSize : 0;
}

/**
  Returns the number of ranks in the specified DIMM.

  @param[in] MainHandle - Used to get the CallBack function pointer.
  @param[in] Controller - Memory Controller index.
  @param[in] Channel    - Channel index.
  @param[in] Dimm       - Dimm index.

  @retval UINT8 - Number of ranks.
**/
UINT8
DcttGetDimmNumberOfRanks (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT8             Controller,
  IN  UINT8             Channel,
  IN  UINT8             Dimm
  )
{
  return (Controller < MAX_CONTROLLERS) ?
    ((MrcParameters *) DcttMain->MrcData)->Outputs.Controller[Controller].Channel[Channel].Dimm[Dimm].RankInDimm : 0;
}

/**
  Returns the specified DIMM capacity.

  @param[in] MainHandle - Used to get the CallBack function pointer.
  @param[in] Controller - Memory Controller index.
  @param[in] Channel    - Channel index.
  @param[in] Dimm       - Dimm index.

  @retval UINT32 - Dimm size.
**/
UINT32
DcttGetDimmSize (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT8             Controller,
  IN  UINT8             Channel,
  IN  UINT8             Dimm
  )
{
  return (Controller < MAX_CONTROLLERS) ?
  ((MrcParameters *) DcttMain->MrcData)->Outputs.Controller[Controller].Channel[Channel].Dimm[Dimm].DimmCapacity : 0;
}

/**
  Sets System and Dimm tCL.

  @param[in] MainHandle - Used to get the CallBack function pointer.
  @param[in] Controller - Memory Controller index.
  @param[in] Channel    - Channel index.
  @param[in] Value      - tCL value.

  @retval UINT8 - tCL value programmed.
**/
UINT8
DcttSetCl (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT8             Controller,
  IN  UINT8             Channel,
  IN  UINT8             Value
  )
{
  MrcParameters               *MrcData;
  DDR3_MODE_REGISTER_0_STRUCT *MrPtr;
  UINT16                      Offset;
  UINT16                      Cl_A2;
  UINT8                       Rank;
  UINT8                       RetVal = 0;

  MrcData = (MrcParameters *) DcttMain->MrcData;

  // LPDDR3 RL/WL are tied together.  Cannot margin one independently.  DDR4 NYI
  if (MrcData->Outputs.DdrType != MRC_DDR_TYPE_DDR3) {
    return RetVal;
  }

  // @todo: limit handling?
  RetVal = Value;

  //
  // convert CAS to jedec ddr3 values
  //
  if (Value <= 11) {
    Offset  = 4;
    Cl_A2   = 0;
  } else {
    Offset  = 12;
    Cl_A2   = 1;
  }

  // MR's should be restored from the host structure.  Update host structure entry and call MR set function
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank+= MAX_RANK_IN_DIMM) {
    if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
      MrPtr = (DDR3_MODE_REGISTER_0_STRUCT *) &MrcData->Outputs.Controller[Controller].Channel[Channel].Dimm[Rank % 2].Rank[Rank / 2].MR[mrMR0];
      MrPtr->Bits.CasLatencyLow = Cl_A2;
      MrPtr->Bits.CasLatencyHigh= Value - Offset;

      MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "C%d.R%d.MR0: 0%x\n", Channel, Rank, *MrPtr);
      MrcWriteMRS (MrcData, Channel, 1 << Rank, mrMR0, MrPtr->Data);// @todo: Error Handling?
    }
  }

  return RetVal;
}

/**
  Sets DIMM and System tCWL.

  @param[in] MainHandle - Used to get the CallBack function pointer.
  @param[in] Controller - Memory Controller index.
  @param[in] Channel    - Channel index.
  @param[in] Value      - tCWL value to program.

  @retval UINT8 - tCWL value set.
**/
UINT8
DcttSetCwl (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT8             Controller,
  IN  UINT8             Channel,
  IN  UINT8             Value
  )
{
  MrcParameters               *MrcData;
  DDR3_MODE_REGISTER_2_STRUCT *MrPtr;
  UINT8                       Rank;
  UINT8                       RetVal = 0;


  MrcData = (MrcParameters *) DcttMain->MrcData;

  // LPDDR3 RL/WL are tied together.  Cannot margin one independently.  DDR4 NYI
  if (MrcData->Outputs.DdrType != MRC_DDR_TYPE_DDR3) {
    return RetVal;
  }

  // @todo: Limit handling?
  RetVal = Value;

  // MR's should be restored from the host structure.  Update host structure entry and call MR set function
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank+= MAX_RANK_IN_DIMM) {
    if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
      MrPtr = (DDR3_MODE_REGISTER_2_STRUCT *) &MrcData->Outputs.Controller[Controller].Channel[Channel].Dimm[Rank % 2].Rank[Rank / 2].MR[mrMR2];
      MrPtr->Bits.CasWriteLatency = Value - 5;

      MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "C%d.R%d.MR2: 0x%x\n", Channel, Rank, *MrPtr);
      MrcWriteMRS (MrcData, Channel, 1 << Rank, mrMR2, MrPtr->Data); // @todo: Error Handling?
    }
  }

  return RetVal;
}

/**
  Hook to get access to debug prints.

  @param[in] MainHandle   - Used to get the CallBack function pointer.
  @param[in] FormatString - Print string.
  @param[in] __VA_ARGS__  - Print arguments for the FormatString.

  @retval VOID - Nothing.
**/
VOID
DcttPrint (
  IN  DCTT_API  *const  DcttMain,
  IN  char*             FormatString,
  ...
  )
{
#ifdef MRC_DEBUG_PRINT
  MrcVaList Marker;

  VA_START (Marker, FormatString);
  MrcPrintfVaList (&((MrcParameters *) DcttMain->MrcData)->Outputs.Debug, MSG_LEVEL_NOTE, FormatString, Marker);
#endif // MRC_DEBUG_PRINT
}

/**
  Delay function hook to allow DCTT to stall.

  @param[in] MainHandle     - Used to get the CallBack function pointer.
  @param[in] DelaySysUnits  - Delay duration in multiples of DCTT_SYS_MIN_DELAY_FS.

  @retval VOID - Nothing.
**/
VOID
DcttWait (
  IN  DCTT_API  *const  DcttMain,
  IN  UINT32            DelaySysUnits
  )
{
  MrcWait ((MrcParameters *) DcttMain->MrcData, DelaySysUnits);
}

/**
  This function performs a bitwise left shift on a UINT64 number.

  @param[in] DcttMain - DCTT main structure.
  @param[in] Data - Value to be left shifted.
  @param[in] Count - Number of bits to shift. Value should be between 0 and 63.

  @retval UINT64 - Returns the left shifted value
**/
UINT64
DcttLShiftU64 (
  IN DCTT_API  *DcttMain,
  IN UINT64 Data,
  IN UINT32 Count
  )
{
  MRC_FUNCTION         *MrcCall;
  MrcParameters        *MrcParams;

  MrcParams = (MrcParameters *) DcttMain->MrcData;
  MrcCall = MrcParams->Inputs.Call.Func;
  return MrcCall->MrcLeftShift64 (Data, Count);
}

/**
  This function performs a bitwise right shift on a UINT64 number.

  @param[in] DcttMain - DCTT main structure.
  @param[in] Data - Value to be right shifted.
  @param[in] Count - Number of bits to shift. Value should be between 0 and 63.

  @retval UINT64 - Returns the right shifted value.
**/
UINT64
DcttRShiftU64 (
  IN DCTT_API  *DcttMain,
  IN UINT64 Data,
  IN UINT32 Count
  )
{
  MRC_FUNCTION         *MrcCall;
  MrcParameters        *MrcParams;

  MrcParams = (MrcParameters *) DcttMain->MrcData;
  MrcCall = MrcParams->Inputs.Call.Func;
  return MrcCall->MrcRightShift64 (Data, Count);
}

/**
  This function allows DCTT to perform a full reset on the MC/DRAM.

  @param[in] DcttMain - DCTT main structure.
**/
VOID
DcttReset (
  IN DCTT_API *DcttMain
  )
{
  MrcResetSequence ((MrcParameters *) DcttMain->MrcData);
}

/**
  This function gets/sets the systems Self-Refresh Configuration.

  @param[in]      DcttMain           - DCTT Main structure.
  @param[in, out] SelfRefreshEnabled - Pointer to Enabled variable.
  @param[in, out] IdleTimer          - Pointer to Idle Time before Self-refresh entry in clocks.
                                       Will be updated to the value set.
  @param[in]      GetSetFlag         - If TRUE we are setting, else we get the values.
**/
VOID
DcttGetSetSelfRefreshConfig (
  IN     DCTT_API *DcttMain,
  IN OUT BOOLEAN  *SelfRefreshEnabled,
  IN OUT UINT32   *IdleTimer,
  IN     BOOLEAN  GetSetFlag
  )
{
  MrcParameters *MrcData;
  MCDECS_CR_PM_SREF_CONFIG_MCMAIN_STRUCT  PmSrefConfig;

  MrcData = (MrcParameters *) DcttMain->MrcData;
  PmSrefConfig.Data = MrcReadCR (MrcData, MCDECS_CR_PM_SREF_CONFIG_MCMAIN_REG);

  if (GetSetFlag == TRUE) {
    if (IdleTimer != NULL) {
      *IdleTimer = RANGE (*IdleTimer, 512, MCDECS_CR_PM_SREF_CONFIG_MCMAIN_Idle_timer_MAX);
      PmSrefConfig.Bits.Idle_timer  = *IdleTimer;
    }
    if (SelfRefreshEnabled != NULL) {
      PmSrefConfig.Bits.SR_Enable = *SelfRefreshEnabled;
    }
    MrcWriteCR (MrcData, MCDECS_CR_PM_SREF_CONFIG_MCMAIN_REG, PmSrefConfig.Data);
  } else {
    if (IdleTimer != NULL) {
      *IdleTimer = PmSrefConfig.Bits.Idle_timer;
    }
    if (SelfRefreshEnabled != NULL) {
      *SelfRefreshEnabled = (BOOLEAN) PmSrefConfig.Bits.SR_Enable;
    }
  }
}

/**
  This function initializes the callback structure of DCTT_API struct
  passed in.

  @param[in] DcttMain - DCTT main structure.

  @retval VOID - Nothing
**/
VOID
DcttCbInit (
  DCTT_API      *const  DcttMain
  )
{
  DCTT_CALLBACK_FUNCTIONS *DcttCbFunctions;

  DcttCbFunctions = &DcttMain->DcttCbFunctions;

  DcttCbFunctions->DcttWriteReg32                   = DcttWrite32;
  DcttCbFunctions->DcttWriteReg64                   = DcttWrite64;
  DcttCbFunctions->DcttReadReg32                    = DcttRead32;
  DcttCbFunctions->DcttReadReg64                    = DcttRead64;
  DcttCbFunctions->DcttSysGetPresentChannelBitMask  = DcttGetPresentChannelBitMask;
  DcttCbFunctions->DcttSysChannelExists             = DcttChannelExists;
  DcttCbFunctions->DcttSysRankInChannelExists       = DcttRankInChannelExists;
  DcttCbFunctions->DcttSysGetMcFrequency            = DcttGetMcFrequency;
  DcttCbFunctions->DcttSysGetMcAddress              = DcttGetMcAddress;
  DcttCbFunctions->DcttSysSetWdbFixedPat            = DcttSetWdbFixedPat;
  DcttCbFunctions->DcttSysSetRefi                   = DcttSetRefi;
  DcttCbFunctions->DcttSysGetRefi                   = DcttGetRefi;
  DcttCbFunctions->DcttDimmGetRowSize               = DcttGetDimmRowSize;
  DcttCbFunctions->DcttDimmGetColumnSize            = DcttGetDimmColumnSize;
  DcttCbFunctions->DcttDimmGetNumberOfRanks         = DcttGetDimmNumberOfRanks;
  DcttCbFunctions->DcttDimmGetSize                  = DcttGetDimmSize;
  DcttCbFunctions->DcttSetCl                        = DcttSetCl;
  DcttCbFunctions->DcttSetCwl                       = DcttSetCwl;
  DcttCbFunctions->DcttSysPrint                     = DcttPrint;
  DcttCbFunctions->DcttSysWait                      = DcttWait;
  DcttCbFunctions->DcttSysEnterSelfRefresh          = DcttEnterSelfRefresh;
  DcttCbFunctions->DcttSysExitSelfRefresh           = DcttExitSelfRefresh;
  DcttCbFunctions->DcttLeftShift64                  = DcttLShiftU64;
  DcttCbFunctions->DcttRightShift64                 = DcttRShiftU64;
  DcttCbFunctions->DcttSysReset                     = DcttReset;
  DcttCbFunctions->DcttSysGetSetSelfRefreshConfig   = DcttGetSetSelfRefreshConfig;
}

VOID
DcttSetupCustomPattern (
  DCTT_CONFIG_PARAMS  *TestParams,
  UINT64              CustomPattern
  )
{
  TestParams->backgroundBase = DcttBackBaseCustom;
  TestParams->CustomPattern = CustomPattern;
}

VOID
DcttBasicSetup (
  DCTT_CONFIG_PARAMS  *TestParams
  )
{
  //
  //  @test - Test cases for hardware memtest.  Keep these patterns for reference.
  // ConfigPtr->testStrings[0]           = "^(wd) ^(rd, wi, ri) ^(ri, wd, rd) v(rd, wi, ri) v(ri, wd, rd) v(rd)";
  // ConfigPtr->testStrings[0]           = "^(wd) ^(ri, wi) ^(ri, wd) v(rd, wi) v(ri, wd) v(rd)";
  // ConfigPtr->testStrings[1]           = "^(wd) ^(wi, rd<tbfr>, ri, wd)";
  // ConfigPtr->testStrings[1]           = "^(wd) ^(rd, wi, ri, wd, rd, wi) ^(ri, wd, wi) v(ri, wd, wi, wd) v(rd, wi, wd) ^(rd, wi, ri) ^(ri, wd, rd)";
  //
  TestParams->testStrings[0]          = "^(wd) ^(rd, wi) v(ri, wd) v(rd)";
  TestParams->firstOrder              = DcttOrderColumn;
  TestParams->secondOrder             = DcttOrderRow;
  TestParams->thirdOrder              = DcttOrderBank;
  TestParams->backgroundBase          = DcttBackBaseZeros;
  TestParams->maxNumberErrors         = 10;
  TestParams->failOnError             = FALSE;
  TestParams->dontStopErrors          = FALSE;
  TestParams->SubMemoryRangeTest      = FALSE;
  TestParams->startBackground         = DcttBackgroundPatternStripes;
  TestParams->endBackground           = DcttBackgroundPatternStripes;
}

VOID
DcttRowHammerSetup (
  DCTT_CONFIG_PARAMS  *TestParams
  )
{
  TestParams->testStrings[0]          = "^(fhammerd)";
  TestParams->useWriteHammers         = TRUE;
  TestParams->hammerRepetitions       = 100000;
  TestParams->HammerRefreshEnable     = TRUE;
  TestParams->hammerIterationsOnRow   = 1;
  TestParams->hammerPageCloseDelay    = 27;
  TestParams->hammerCheckType         = DcttHamerCheckRowNB;
  TestParams->startBackground         = DcttBackgroundPatternSolid;
  TestParams->endBackground           = DcttBackgroundPatternSolid;
  TestParams->backgroundType          = DcttBackgroundPatternSolid;
  TestParams->runTestPerBank          = TRUE;
  TestParams->OptimizeSecondOrderRun  = TRUE;
  TestParams->rowSwizzleType          = DcttRowSwizzleNone;
}

/**
  This function initializes the configuration structure of the DCTT
  to change the start and stop addresses of a test. It assumes that
  the caller have called DcttSetDefaultParams and DcttBasicSetup before
  calling it.

  @param[in] DcttMain - DCTT main structure.
  @param[in] StartRankCh0 - First Rank to be tested on Ch0.
  @param[in] StartBankCh0 - First Bank to be tested on Ch0.
  @param[in] StartRowCh0 - First Row to be tested on Ch0.
  @param[in] StartColCh0 - First Col to be tested on Ch0.
  @param[in] StopRankCh0 - Last Rank to be tested on Ch0.
  @param[in] StopBankCh0 - Last Bank to be tested on Ch0.
  @param[in] StopRowCh0 - Last Row to be tested on Ch0.
  @param[in] StopColCh0 - Last Col to be tested on Ch0.
  @param[in] StartRankCh1 - First Rank to be tested on Ch1.
  @param[in] StartBankCh1 - First Bank to be tested on Ch1.
  @param[in] StartRowCh1 - First Row to be tested on Ch1.
  @param[in] StartColCh1 - First Col to be tested on Ch1.
  @param[in] StopRankCh1 - Last Rank to be tested on Ch1.
  @param[in] StopBankCh1 - Last Bank to be tested on Ch1.
  @param[in] StopRowCh1 - Last Row to be tested on Ch1.
  @param[in] StopColCh1 - Last Col to be tested on Ch1.

  @retval VOID - Nothing
**/
VOID
DcttStartStopSetup (
  DCTT_CONFIG_PARAMS  *TestParams,
  UINT32               StartRankCh0,
  UINT32               StartBankCh0,
  UINT32               StartRowCh0,
  UINT32               StartColCh0,
  UINT32               StopRankCh0,
  UINT32               StopBankCh0,
  UINT32               StopRowCh0,
  UINT32               StopColCh0,
  UINT32               StartRankCh1,
  UINT32               StartBankCh1,
  UINT32               StartRowCh1,
  UINT32               StartColCh1,
  UINT32               StopRankCh1,
  UINT32               StopBankCh1,
  UINT32               StopRowCh1,
  UINT32               StopColCh1
  )
{
  TestParams->dontStopErrors =         FALSE;
  TestParams->runTestPerBank =         TRUE;
  TestParams->runTestOnSecondOrder =   TRUE;
  TestParams->OptimizeSecondOrderRun = TRUE;
  TestParams->SubMemoryRangeTest =     TRUE;
  TestParams->bottomAddress[0].Col =   StartColCh0;
  TestParams->bottomAddress[0].Row =   StartRowCh0;
  TestParams->bottomAddress[0].Bank =  StartBankCh0;
  TestParams->bottomAddress[0].Rank =  StartRankCh0;
  TestParams->bottomAddress[1].Col =   StartColCh1;
  TestParams->bottomAddress[1].Row =   StartRowCh1;
  TestParams->bottomAddress[1].Bank =  StartBankCh1;
  TestParams->bottomAddress[1].Rank =  StartRankCh1;
  TestParams->topAddress[0].Col =      StopColCh0;
  TestParams->topAddress[0].Row =      StopRowCh0;
  TestParams->topAddress[0].Bank =     StopBankCh0;
  TestParams->topAddress[0].Rank =     StopRankCh0;
  TestParams->topAddress[1].Col =      StopColCh1;
  TestParams->topAddress[1].Row =      StopRowCh1;
  TestParams->topAddress[1].Bank =     StopBankCh1;
  TestParams->topAddress[1].Rank =     StopRankCh1;
}

/**
  This function performs memory cell testing.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - Always returns mrcSuccess.
**/
MrcStatus
MrcHwMemTest (
  IN     MrcParameters *const MrcData
  )
{
  DCTT_API              DcttMain;
  DCTT_CONFIG_PARAMS    *ConfigPtr;
  MrcInput              *Inputs;
  MrcDebug              *Debug;
  INT32                 RetVal;

  Inputs = &MrcData->Inputs;
  Debug  = &MrcData->Outputs.Debug;
  Inputs->Call.Func->MrcSetMem ((UINT8*) &DcttMain, sizeof (DCTT_API), 0);
  ConfigPtr = &DcttMain.DcttConfigData;
  DcttMain.MrcData = MrcData;
  DcttMain.DebugLevel = DcttLogNormal;

  DcttCbInit (&DcttMain);
  DcttSetDefaultParams (ConfigPtr);
      ///
    /// Replace with DcttRowHammerSetup (ConfigPtr) to enable Row Hammer test.
    ///
    DcttBasicSetup (ConfigPtr);
  RetVal = DcttRun (&DcttMain);

  if (RetVal != DCTT_SUCCESS) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DCTT did not return a successful status: 0x%x", RetVal);
  }

  return mrcSuccess;
}
