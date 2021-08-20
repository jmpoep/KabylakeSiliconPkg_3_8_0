/** @file
  This file contains the memory scrubbing and alias checking functions.

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

@par Specification Reference:
**/

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcMemoryScrub.h"

/**
  This function sets all the memory to a known value when ECC is enabled and
  either we are not in warm boot or we are in warm boot and TXT is set.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if the clean succeeded, otherwise an error status.
**/
MrcStatus
MrcEccClean (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  MrcDebug              *Debug;
  const MRC_FUNCTION    *MrcCall;
  static const UINT8    WrapCarryEn[MrcReutFieldMax]   = {0, 0, 0, 0};
  static const UINT8    WrapTriggerEn[MrcReutFieldMax] = {0, 0, 0, 0};
  static const UINT8    AddrInvertEn[MrcReutFieldMax]  = {0, 0, 0, 0};
  MrcControllerOut      *ControllerOut;
  MrcDimmOut            *DimmOut;
  MrcOutput             *Outputs;
  MrcStatus             Status;
  UINT8                 Pattern;
  UINT8                 PMask;
  UINT8                 Rank;
  UINT8                 BankCount;
  UINT8                 Channel;
  UINT8                 ActiveChBitMask;
  UINT8                 RankToDimm;
  UINT32                Offset;
  MRC_REUTAddress       ReutAddress;
  MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_STRUCT ReutSubSeqCtl;
  MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT     ReutChSeqCfg;
  MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_STRUCT  ReutChPatWdbCl;
  MCDECS_CR_MC_INIT_STATE_G_MCMAIN_STRUCT       McInitStateG;
  MCHBAR_CH0_CR_SC_PCIT_STRUCT                  ScPcit;
  MCHBAR_CH0_CR_SC_PCIT_STRUCT                  ScPcitSave[MAX_CHANNEL];

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;
  Pattern       = 0;
  PMask         = 0;
  MrcCall->MrcSetMem ((UINT8 *) &ReutAddress, sizeof (ReutAddress), 0);

  if ((Outputs->EccSupport == TRUE) || (Inputs->CleanMemory == TRUE) || (Debug->PostCode[MRC_POST_CODE] == MRC_SSA_STOP_POINT)) {

    //
    // Enable refreshes on MC before we start ECC scrubbing.
    //
    McInitStateG.Data = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
    McInitStateG.Bits.refresh_enable = 1;
    MrcWriteCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG, McInitStateG.Data);

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Scrubbing Memory\n");
    //
    // Setup the first cache line to zeros.
    //
    WriteWDBFixedPattern (MrcData, &Pattern, &PMask, 1, 0);

    //
    // Setup Reut for both channels. Reut test will write 0x0 to all memory
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }

      //
      // Set Reut sequence cfg register
      //
      ReutChSeqCfg.Data                                    = 0;
      ReutChSeqCfg.Bits.Initialization_Mode                = REUT_Testing_Mode;
      ReutChSeqCfg.Bits.Global_Control                     = 1;
      ReutChSeqCfg.Bits.Start_Test_Delay                   = 2;
      ReutChSeqCfg.Bits.Address_Update_Rate_Mode           = 0;
      ReutChSeqCfg.Bits.Stop_Base_Sequence_On_Wrap_Trigger = 0;
      MrcWriteCR64 (
        MrcData,
        MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG +
        ((MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG) * Channel),
        ReutChSeqCfg.Data
        );

      //
      // Program Write Data Buffer Control.  Since we are using 1 cache line, we only need
      // to set the increment scale to linear.
      //
      ReutChPatWdbCl.Data = 0;
      ReutChPatWdbCl.Bits.WDB_Increment_Scale = 1;
      MrcWriteCR (
        MrcData,
        MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_REG +
        ((MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_REG) * Channel),
        ReutChPatWdbCl.Data
        );
      //
      // Change PCIT to 0xFF
      //
      Offset = MCHBAR_CH0_CR_SC_PCIT_REG + (MCHBAR_CH1_CR_SC_PCIT_REG - MCHBAR_CH0_CR_SC_PCIT_REG) * Channel;
      ScPcit.Data = MrcReadCR (MrcData, Offset);
      ScPcitSave[Channel] = ScPcit;
      ScPcit.Bits.PCIT = 0xFF;
      MrcWriteCR (MrcData, Offset, ScPcit.Data);
    }

    //
    // Continue to setup Reut and Run Per Rank
    //
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (((1 << Rank) & Outputs->ValidRankMask) == 0) {
        continue;
      }
      RankToDimm = RANK_TO_DIMM_NUMBER (Rank);
      //
      // Determine the Active Channels
      //
      ActiveChBitMask = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ActiveChBitMask |= SelectReutRanks (MrcData, Channel, MRC_BIT0 << Rank, 0);
      }

      //
      // Program the sequence addresses and loopcount per channel
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if ((ActiveChBitMask & (1 << Channel)) == 0) {
          continue;
        }
        DimmOut = &ControllerOut->Channel[Channel].Dimm[RankToDimm];
        BankCount = DimmOut->BankGroups * DimmOut->Banks;

        // Go over all addresses
        ReutAddress.Stop[MrcReutFieldCol]  = DimmOut->ColumnSize - WDB_CACHE_LINE_SIZE;
        ReutAddress.Stop[MrcReutFieldRow]  = (UINT16) DimmOut->RowSize - 1;
        ReutAddress.Stop[MrcReutFieldBank] = BankCount - 1;

        ReutAddress.IncVal[MrcReutFieldCol]  = 1;  // Each write is 1 cache line which is 8 column addresses worth of data.
        ReutAddress.IncVal[MrcReutFieldRow]  = 1;  // Walk through rows 1 at a time.
        ReutAddress.IncVal[MrcReutFieldBank] = 1;  // Walk through bank 1 at a time.

        ReutAddress.IncRate[MrcReutFieldRow]  = DimmOut->ColumnSize / WDB_CACHE_LINE_SIZE;
        ReutAddress.IncRate[MrcReutFieldBank] = DimmOut->RowSize * (DimmOut->ColumnSize / WDB_CACHE_LINE_SIZE);

        MrcProgramSequenceAddress (
          MrcData,
          Channel,
          ReutAddress.Start,
          ReutAddress.Stop,
          ReutAddress.Order,
          ReutAddress.IncRate,
          ReutAddress.IncVal,
          WrapTriggerEn,
          WrapCarryEn,
          AddrInvertEn,
          0,                    // AddrInvertRate
          FALSE
          );

        //
        // Set up the Subsequence control.
        //
        ReutSubSeqCtl.Data = 0;
        ReutSubSeqCtl.Bits.Subsequence_Type = BWr;
        ReutSubSeqCtl.Bits.Number_of_Cachelines = MrcLog2 ((DimmOut->ColumnSize / WDB_CACHE_LINE_SIZE)) - 1; // MrcLog2 is giving log value plus 1
        ReutSubSeqCtl.Bits.Number_of_Cachelines_Scale = 0;
        MrcWriteCR (
          MrcData,
          MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_REG +
          ((MCDFXS_CR_REUT_CH1_SUBSEQ_CTL_MCMAIN_0_REG - MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_REG) * Channel),
          ReutSubSeqCtl.Data
          );

        //
        // Program loopcount registers
        //
        MrcWriteCR (
          MrcData,
          MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_0_REG +
          ((MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_0_REG) * Channel),
          (BankCount * DimmOut->RowSize)
          );
      } // for Channel

      //
      // Run the test on both Channels
      //
      Status = MrcRunMemoryScrub (MrcData, ActiveChBitMask, TRUE);
      if (Status != mrcSuccess) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Rank %d error!\n", Rank);
        break;
      }
    } // for Rank

    if (Debug->PostCode[MRC_POST_CODE] != MRC_SSA_STOP_POINT) {
      //
      // Return to normal operation mode
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcChannelExist (Outputs, Channel)) {
          ReutChSeqCfg.Data                     = 0;
          ReutChSeqCfg.Bits.Initialization_Mode = NOP_Mode;
          MrcWriteCR (
            MrcData,
            MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG +
            ((MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG) * Channel),
            (UINT32) ReutChSeqCfg.Data
            );
        }
      }
    }

    if (Status != mrcSuccess) {
      MrcCall->MrcDebugHook (MrcData, MRC_ECC_CLEAN_ERROR);
    }
    //
    // Restore PCIT value
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        Offset = MCHBAR_CH0_CR_SC_PCIT_REG + (MCHBAR_CH1_CR_SC_PCIT_REG - MCHBAR_CH0_CR_SC_PCIT_REG) * Channel;
        MrcWriteCR (MrcData, Offset, ScPcitSave[Channel].Data);
      }
    }
  } // if scrubbing required

  return Status;
}

/**
  This function performs a memory alias check.

  @param[in] MrcData - The global host structure

  @retval mrcSuccess or error value.
**/
MrcStatus
MrcAliasCheck (
  IN OUT MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcDebug            *Debug;
  const MrcInput      *Inputs;
  static const UINT16 SdramCapacityTable[] = {256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 12288, 24576, 3072, 6144, 18432}; // Mb
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcDimmOut          *DimmOut;
  MrcStatus           Status;
  BOOLEAN             InvalidSpdAddressingCapacity;
  UINT32              SdramAddressingCapacity;
  UINT32              CrOffset;
  UINT16              SdramCapacity;
  UINT8               Rank;
  UINT8               RankToDimm;
  UINT8               Channel;
  UINT8               ActiveChBitMask;
  MRC_REUTAddress     ReutAddress;
  MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT       ReutChSeqCfg;
  MCDECS_CR_MAD_INTRA_CH0_MCMAIN_STRUCT           MadIntraOrig[MAX_CHANNEL];
  MCDECS_CR_MAD_INTRA_CH0_MCMAIN_STRUCT           MadIntra;
  BOOLEAN                                         ReutUninitialized;

  Outputs       = &MrcData->Outputs;
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Status        = mrcSuccess;
  InvalidSpdAddressingCapacity  = FALSE;
  //
  // Check to see if the SDRAM Addressing * Primary Bus Width == SDRAM capacity.
  // If not, report an alias and exit.
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += MAX_RANK_IN_DIMM) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        RankToDimm              = RANK_TO_DIMM_NUMBER (Rank);
        DimmOut                 = &ControllerOut->Channel[Channel].Dimm[RankToDimm];
        SdramAddressingCapacity = (DimmOut->ColumnSize * DimmOut->RowSize);
        //
        // Since the minimum number of row and column bits are 12 and 9 respectively,
        // we can shift by 20 to get the result in Mb before multiplying by the bus width.
        //
        SdramAddressingCapacity  = SdramAddressingCapacity >> 20;
        SdramAddressingCapacity *= DimmOut->Banks;
        SdramAddressingCapacity *= DimmOut->BankGroups;
        SdramAddressingCapacity *= DimmOut->SdramWidth;
        SdramCapacity            = SdramCapacityTable[DimmOut->DensityIndex];
        if (SdramCapacity != SdramAddressingCapacity) {
          InvalidSpdAddressingCapacity = TRUE;
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_ERROR,
            "ERROR: Channel %d Dimm %d SPD SDRAM Adressing Capacity(0x%xMb) does not match SDRAM Capacity(0x%xMb)\nPlease verify:\n",
            Channel,
            RankToDimm,
            SdramAddressingCapacity,
            SdramCapacity
            );
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_ERROR,
            " Capacity: 0x%x\n RowSize: 0x%x\n ColumnSize: 0x%x\n Banks: 0x%x\n Bank Groups: 0x%x\n Device Width: 0x%x\n",
            SdramCapacity,
            DimmOut->RowSize,
            DimmOut->ColumnSize,
            DimmOut->Banks,
            DimmOut->BankGroups,
            DimmOut->SdramWidth
            );
          break;
        }
      }
    }
  }
  //
  // Since we will not hang the system, signal that an Alias could exist and return mrcSuccess.
  //
  if (TRUE == InvalidSpdAddressingCapacity) {
    Outputs->SpdSecurityStatus = MrcSpdStatusAliased;
    return Status;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Performing Alias Test\n");
  MrcCall->MrcSetMem ((UINT8 *) &ReutAddress, sizeof (ReutAddress), 0);
  ReutUninitialized = TRUE;

  //
  // Determine if we are ECC enabled.  If so, disable ECC since the ECC scrub has yet to occur.
  //
  if (Outputs->EccSupport == TRUE) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ECC enabled.  Disabling ECC for the test.  Must scrub after this!!!\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        CrOffset = MCDECS_CR_MAD_INTRA_CH0_MCMAIN_REG +
          ((MCDECS_CR_MAD_INTRA_CH1_MCMAIN_REG - MCDECS_CR_MAD_INTRA_CH0_MCMAIN_REG) * Channel);

        MadIntraOrig[Channel].Data = MrcReadCR (MrcData, CrOffset);
        MadIntra.Data              = MadIntraOrig[Channel].Data;
        MadIntra.Bits.ECC          = emNoEcc;
        MrcWriteCR (MrcData, CrOffset, MadIntra.Data);
      }
    }
  }

  //
  // Run test Per Dimm
  //
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += MAX_RANK_IN_DIMM) {
    if ((MRC_BIT0 << Rank) & Outputs->ValidRankMask) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Testing Dimm %d\n", Rank / 2);
      MrcMemoryCheckSetup (MrcData, &ReutAddress, Rank, 0, &ReutUninitialized);
      //
      // Determine Active Channels
      //
      ActiveChBitMask = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ActiveChBitMask |= SelectReutRanks (MrcData, Channel, MRC_BIT0 << Rank, 0);
      }

      //
      // Run the test
      //
      Status = MrcRunMemoryScrub (MrcData, ActiveChBitMask, TRUE);
      if (Status != mrcSuccess) {
        break;
      }
    }
  }

  if (Outputs->EccSupport == TRUE) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ReEnabling ECC Logic.  Must scrub after this!\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        CrOffset = MCDECS_CR_MAD_INTRA_CH0_MCMAIN_REG +
          ((MCDECS_CR_MAD_INTRA_CH1_MCMAIN_REG - MCDECS_CR_MAD_INTRA_CH0_MCMAIN_REG) * Channel);

        MrcWriteCR (MrcData, CrOffset, MadIntraOrig[Channel].Data);
      }
    }
  }
  //
  // Wait 4 usec after enabling the ECC IO, needed by HW
  //
  MrcWait (MrcData, 4 * HPET_1US);

  //
  // Return to normal operation mode
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ReutChSeqCfg.Data                     = 0;
      ReutChSeqCfg.Bits.Initialization_Mode = NOP_Mode;
      MrcWriteCR (
        MrcData,
        MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG +
        ((MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG - MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG) * Channel),
        (UINT32) ReutChSeqCfg.Data
        );
    }
  }

  if (mrcSuccess != Status) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*** Alias Detected!  See REUT Error above. ***\n");
    Outputs->SpdSecurityStatus = MrcSpdStatusAliased;
    Status = mrcSuccess;
  }

  return Status;
}

/**
  This function runs the srcubbing test reporting any timeouts/errors.

  @param[in] MrcData - The global host structure
  @param[in] ChBitMask - Bitmask of channels the test is run on.
  @param[in] MsgPrint  - Print debug messages

  @retval mrcSuccess or error value.
**/
MrcStatus
MrcRunMemoryScrub (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                ChBitMask,
  IN     BOOLEAN              MsgPrint
  )
{
  const MRC_FUNCTION *MrcCall;
  MrcDebug           *Debug;
  MrcDebugMsgLevel   DebugLevel;
  MrcStatus          Status;
  UINT8              ErrorStatus;
  UINT8              TestDoneStatus;
  MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_STRUCT       ReutGlobalCtl;
  MCDFXS_CR_REUT_GLOBAL_ERR_MCMAIN_STRUCT       ReutGlobalErr;
  UINT64  Timer;

  Status  = mrcSuccess;
  Debug   = &MrcData->Outputs.Debug;
  MrcCall = MrcData->Inputs.Call.Func;
  DebugLevel = MsgPrint ? MSG_LEVEL_ERROR : MSG_LEVEL_NEVER;

  IoReset (MrcData);
  //
  // Setup Timer and run the test
  //
  Timer = MrcCall->MrcGetCpuTime (MrcData) + 20000; // 20 Second timeout
  ReutGlobalCtl.Data                                = 0;
  ReutGlobalCtl.Bits.Global_Start_Test              = 1;
  ReutGlobalCtl.Bits.Global_Clear_Errors            = 1;
  ReutGlobalCtl.Bits.Global_Stop_Test_On_Any_Error  = NSOE;
  MrcWriteCR (MrcData, MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG, ReutGlobalCtl.Data);

  //
  // Wait until Channel test done status matches ChbitMask or TimeoutCounter value reaches 0;
  //
  do {
    ReutGlobalErr.Data = MrcReadCR (MrcData, MCDFXS_CR_REUT_GLOBAL_ERR_MCMAIN_REG);
    TestDoneStatus     = (UINT8) ((ReutGlobalErr.Bits.Channel_Test_Done_Status_1 << 1) |
                                  ReutGlobalErr.Bits.Channel_Test_Done_Status_0);
  } while (((TestDoneStatus & ChBitMask) != ChBitMask) && (MrcCall->MrcGetCpuTime (MrcData) < Timer));

  if ((TestDoneStatus & ChBitMask) != ChBitMask) {
    Status = mrcDeviceBusy;
    MRC_DEBUG_MSG (
      Debug,
      DebugLevel,
      "Timeout occured while running the test: ReutGlobalErr: 0x%X.\n",
      ReutGlobalErr.Data
      );
  }

  ErrorStatus = (UINT8) ((ReutGlobalErr.Bits.Channel_Error_Status_1 << 1) | ReutGlobalErr.Bits.Channel_Error_Status_0);
  if (ErrorStatus & ChBitMask) {
    Status = mrcReutSequenceError;
    MRC_DEBUG_MSG (
      Debug,
      DebugLevel,
      "REUT Error: Channel(s):%s%s\n",
      (ReutGlobalErr.Bits.Channel_Error_Status_0 == 1) ? " 0" : "",
      (ReutGlobalErr.Bits.Channel_Error_Status_1 == 1) ? " 1" : ""
      );
  }

  return Status;
}

/**
  This function provides MRC core hook to call TXT Alias Check before DRAM Init Done.

  @param[in]  MrcData - Pointer to global MRC structure.

  @retval mrcSuccess.
**/
MrcStatus
MrcTxtAliasCheck (
  IN MrcParameters *const MrcData
  )
{
  MrcData->Inputs.Call.Func->MrcTxtAcheck ();
  return mrcSuccess;
}
