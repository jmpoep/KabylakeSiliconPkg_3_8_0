/** @file
  Copies the memory related timing and configuration information into the
  Compatible BIOS data (BDAT) table.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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

#define BDAT_SUPPORT 1
#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcInterface.h"
#include "MrcSpdProcessing.h"
#include "McAddress.h"
#ifndef MRC_MINIBIOS_BUILD
#include "MemoryInit.h"
#endif

#ifdef BDAT_SUPPORT
// Index of signals in the RankResultType0/ByteResultType/LaneResultType
#define RESULTS_RX_DQ_INDEX          0
#define RESULTS_TX_DQ_INDEX          1
#define RESULTS_RX_VREF_INDEX        2
#define RESULTS_TX_VREF_INDEX        3

// Index of signals in the RankResultType1
#define RESULTS_CMD_INDEX            0
#define RESULTS_CMD_VREF_INDEX       1

// Index of signals in the RankResultType3
#define RESULTS_RECEN_INDEX          0
#define RESULTS_WRLVL_INDEX          1

#define LOW_INDEX                    0
#define HIGH_INDEX                   1

#define IO_LEVEL_DDR_LEVEL           1
#define TBD                       0
#define CRC_SEED                  0
#define CRC_XOR_MASK              0x1021
#define MAX_UINT8_VALUE           (((1UL) << CHAR_BITS) - 1)
#define HOST_BRIDGE_BUS           0
#define HOST_BRIDGE_DEVICE        0
#define HOST_BRIDGE_FUNCTION      0
#define HOST_BRIDGE_OFFSET_DEVID  0
#define HOST_BRIDGE_OFFSET_REVID  8
#define GetCrc16                  GetDimmCrc

/**
This function print out the RMT column data

@param[in, out] MrcData       - Include all MRC global data.
@param[in]      RmtRows       - The RMT column result.
@param[in]      ElementNumber - The index of the results.

@retval  None
**/
VOID
PrintBdatResult (
  IN OUT MrcParameters  *const MrcData,
  IN RMT_RESULT_COLUMNS *RmtRows,
  IN UINT32             ElementNumber
)
{
  MrcDebug           *Debug;
  RMT_RESULT_COLUMNS *RmtRow;
  UINT8 i;
  UINT8 j;

  RmtRow = &(RmtRows[ElementNumber]);
  Debug  = &MrcData->Outputs.Debug;

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "i: %d, Ch: %d Rank: %d Type: %d Lane: %d - [",
    ElementNumber,
    RmtRow->Header.Channel,
    RmtRow->Header.RankA,
    RmtRow->Header.ResultType,
    RmtRow->Header.Lane
  );

  for (i = 0; i < 4; i++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "[");
    for (j = 0; j < 2; j++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %d", RmtRow->Margin[i][j]);
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "]");
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "]\n");
}

/**
  Finds the window value for the given DQ value and if it is less than the
    current value, then save the end point values.

  @param[in, out] Rank1         - Pointer to the first rank training value (left or low).
  @param[in, out] Rank2         - Pointer to the second rank training value (right or high).
  @param[in, out] CurrentWindow - The current window value.
  @param[in] Value1        - The first training value (left or low).
  @param[in] Value2        - The second training value (right or high).

  @retval Nothing.
**/
void
ConvertDq2Rank (
  IN OUT UINT8        *Rank1,
  IN OUT UINT8        *Rank2,
  IN OUT UINT8        *CurrentWindow,
  IN     const UINT8  Value1,
  IN     const UINT8  Value2
  )
{
  UINT8 Window;  // The calculated window value.

  Window = MAX (Value1, Value2) - MIN (Value1, Value2);
  if (Window < *CurrentWindow) {
    *CurrentWindow  = Window;
    *Rank1          = Value1;
    *Rank2          = Value2;
  } // if
  return;
}

/**
  Initialize the memory rank margin area of the RMT_STRUCTURE.

  @param[in] MrcData - The MRC "global data".
  @param[in, out] RmtRankMargin - Pointer to the start of the rank margin information in the RMT table.
  @param[in] RmtDq         - Pointer to the start of the dq margin information in the RMT table.

  @retval Nothing.
**/
void
MrcFillRmtRankMargin (
  IN     const MrcParameters        *MrcData,
  IN OUT BDAT_RANK_MARGIN_STRUCTURE *RmtRankMargin,
  IN     BDAT_DQ_MARGIN_STRUCTURE   *RmtDq
  )
{
  BDAT_DQ_MARGIN_STRUCTURE *RmtDqMargin;         // Pointer to the current DQ margin in the RMT structure.
  UINT8                    Dq;                   // DQ number in the rank.
  UINT8                    DqEnd;
  UINT8                    SmallestWindowRxDq;   // The smallest of the Rx DQ windows.
  UINT8                    SmallestWindowTxDq;   // The smallest of the Tx DQ windows.
  UINT8                    SmallestWindowRxVref; // The smallest of the Rx Vref windows.
  UINT8                    SmallestWindowTxVref; // The smallest of the Tx Vref windows.

  SmallestWindowRxDq   = (UINT8) MAX_UINT8_VALUE;
  SmallestWindowTxDq   = (UINT8) MAX_UINT8_VALUE;
  SmallestWindowRxVref = (UINT8) MAX_UINT8_VALUE;
  SmallestWindowTxVref = (UINT8) MAX_UINT8_VALUE;
  DqEnd                = (MrcData->Outputs.EccSupport) ? MAX_DQ : (MAX_DQ - MAX_BITS);
  for (Dq = 0; Dq < DqEnd; Dq++) {
    RmtDqMargin = &RmtDq[Dq];
    ConvertDq2Rank (
      &RmtRankMargin->RxDqLeft,
      &RmtRankMargin->RxDqRight,
      &SmallestWindowRxDq,
      RmtDqMargin->RxDqLeft,
      RmtDqMargin->RxDqRight
      );
    ConvertDq2Rank (
      &RmtRankMargin->TxDqLeft,
      &RmtRankMargin->TxDqRight,
      &SmallestWindowTxDq,
      RmtDqMargin->TxDqLeft,
      RmtDqMargin->TxDqRight
      );
    ConvertDq2Rank (
      &RmtRankMargin->RxVrefLow,
      &RmtRankMargin->RxVrefHigh,
      &SmallestWindowRxVref,
      RmtDqMargin->RxVrefLow,
      RmtDqMargin->RxVrefHigh
      );
    ConvertDq2Rank (
      &RmtRankMargin->TxVrefLow,
      &RmtRankMargin->TxVrefHigh,
      &SmallestWindowTxVref,
      RmtDqMargin->TxVrefLow,
      RmtDqMargin->TxVrefHigh
      );
  } // Dq loop
  return;
}

/**
  Initialize the memory DQ area of the RMT_STRUCTURE.

  @param[in, out] RmtDq   - Pointer to the start of the DQ information in the RMT table.
  @param[in] Channel - Specific Channel
  @param[in] Dimm    - Specific Dimm
  @param[in] Rank    - Specific Rank
  @param[in] MrcData - The MRC "global data".

  @retval Nothing.
**/
void
MrcFillRmtDqMargin (
  IN OUT BDAT_DQ_MARGIN_STRUCTURE *RmtDq,
  IN     const UINT8              Controller,
  IN     const UINT8              Channel,
  IN     const UINT8              Dimm,
  IN     const UINT8              Rank,
  IN     const MrcParameters      *MrcData
  )
{
  const MrcOutput          *Outputs;
  const MrcChannelOut      *ChannelOut;
  const MrcDqTimeMargin    *RxDqMargin;      // Pointer to the output portion of the MRC global data area.
  const MrcDqTimeMargin    *TxDqMargin;      // Pointer to the output portion of the MRC global data area.
  const MrcDqVrefMargin    *RxVrefDqMargin;  // Pointer to the output portion of the MRC global data area.
  const MrcDqVrefMargin    *TxVrefDqMargin;  // Pointer to the output portion of the MRC global data area.
  BDAT_DQ_MARGIN_STRUCTURE *RmtDqMargin;     // Pointer to the current DQ margin in the RMT structure.
  UINT8                    RankInChannel;
  UINT8                    Sdram;
  UINT8                    Dq;               // DQ number in the rank.
  UINT8                    DqEnd;
  UINT8                    Bit;

  Outputs       = &MrcData->Outputs;
  ChannelOut    = &Outputs->Controller[Controller].Channel[Channel];
  RankInChannel = (Dimm * MAX_RANK_IN_DIMM) + Rank;
  DqEnd         = (Outputs->EccSupport) ? MAX_DQ : (MAX_DQ - MAX_BITS);
  for (Dq = 0; Dq < DqEnd; Dq++) {
    Sdram                   = Dq / CHAR_BITS;
    Bit                     = Dq % CHAR_BITS;
    RxDqMargin              = &ChannelOut->RxDqPb[RankInChannel][Sdram][Bit];
    TxDqMargin              = &ChannelOut->TxDqPb[RankInChannel][Sdram][Bit];
    RxVrefDqMargin          = &ChannelOut->RxDqVrefPb[RankInChannel][Sdram][Bit];
    TxVrefDqMargin          = &ChannelOut->TxDqVrefPb[RankInChannel][Sdram][Bit];
    RmtDqMargin             = &RmtDq[Dq];
    RmtDqMargin->RxDqLeft   = RxDqMargin->Left;
    RmtDqMargin->RxDqRight  = RxDqMargin->Right;
    RmtDqMargin->TxDqLeft   = TxDqMargin->Left;
    RmtDqMargin->TxDqRight  = TxDqMargin->Right;
    RmtDqMargin->RxVrefLow  = RxVrefDqMargin->Low;
    RmtDqMargin->RxVrefHigh = RxVrefDqMargin->High;
    RmtDqMargin->TxVrefLow  = TxVrefDqMargin->Low;
    RmtDqMargin->TxVrefHigh = TxVrefDqMargin->High;
  } // Dq loop
  return;
}

/**
  Initialize the memory rank training area of the RMT_STRUCTURE.

  @param[in, out] RmtRankTraining - Pointer to the start of the rank training information in the RMT table.
  @param[in] Channel         - Specific Channel
  @param[in] Dimm            - Specific Dimm
  @param[in] Rank            - Specific Rank
  @param[in] MrcData         - The MRC "global data".

  @retval Nothing.
**/
void
MrcFillRmtRankTraining (
  IN OUT BDAT_RANK_TRAINING_STRUCTURE *RmtRankTraining,
  IN     const UINT8                  Controller,
  IN     const UINT8                  Channel,
  IN     const UINT8                  Dimm,
  IN     const UINT8                  Rank,
  IN     const MrcParameters          *MrcData
  )
{
  const MrcOutput     *Outputs;    // Pointer to the output portion of the MRC global data area.
  const MrcChannelOut *ChannelOut; // Pointer to the channel portion of the MRC global data area.
  UINT8               Index;
  UINT8               RankInChannel;
  UINT8               Sdram;
  UINT8               Strobe;

  Outputs       = &MrcData->Outputs;
  ChannelOut    = &Outputs->Controller[Controller].Channel[Channel];
  RankInChannel = (Dimm * MAX_RANK_IN_DIMM) + Rank;
  for (Strobe = 0; Strobe < MAX_STROBE; Strobe++) {
    Sdram = Strobe / 2;
    RmtRankTraining->RecEnDelay[Strobe] = ChannelOut->RcvEn[RankInChannel][Sdram];
    RmtRankTraining->WlDelay[Strobe]    = ChannelOut->WlDelay[RankInChannel][Sdram];
    RmtRankTraining->RxDqDelay[Strobe]  =
      (Strobe % 2)
      ? ChannelOut->RxDqsN[RankInChannel][Sdram]
      : ChannelOut->RxDqsP[RankInChannel][Sdram];
    RmtRankTraining->TxDqDelay[Strobe]  = ((UINT8) (ChannelOut->TxDq[RankInChannel][Sdram] >> 6)) & 7;
  } // Strobe loop
  RmtRankTraining->ClkDelay = ChannelOut->ClkPiCode[RankInChannel];
  RmtRankTraining->CtlDelay = ChannelOut->CtlPiCode[RankInChannel];
  for (Index = 0; Index < (sizeof (RmtRankTraining->CmdDelay) / sizeof (RmtRankTraining->CmdDelay[0])); Index++) {
    RmtRankTraining->CmdDelay[Index] = TBD;  // Need to implement code.
  } // Index loop
  RmtRankTraining->IoLatency = ChannelOut->IoLatency[RankInChannel];
  RmtRankTraining->Roundtrip = ChannelOut->RTLatency[RankInChannel];
  return;
}

/**
  Initialize the memory rank area of the RMT_STRUCTURE.

  @param[in, out] RmtRank  - Pointer to the start of the rank information in the RMT table.
  @param[in] MrcData  - The MRC "global data".
  @param[in] Channel  - Current channel number.
  @param[in] Dimm     - Current dimm number.

  @retval Nothing.
**/
void
MrcFillRmtRankStructure (
  IN OUT BDAT_RANK_STRUCTURE *RmtRank,
  IN     const MrcParameters *const MrcData,
  IN     UINT8               Controller,
  IN     UINT8               Channel,
  IN     UINT8               Dimm
  )
{
  const MrcOutput              *Outputs;          // Pointer to the output portion of the MRC global data area.
  const MrcChannelOut          *ChannelOut;       // Pointer to the DIMM output portion of the MRC global data area.
  const MrcDimmOut             *DimmOut;          // Pointer to the DIMM output portion of the MRC global data area.
  const MrcInput               *Inputs;
  const MRC_FUNCTION           *MrcCall;
  BDAT_RANK_STRUCTURE          *RmtRankLists;     // Pointer to the current rank list in the RMT structure.
  BDAT_RANK_TRAINING_STRUCTURE *RmtRankTraining;  // Pointer to the current rank training in the RMT structure.
  UINT8                        Rank;              // Rank count for sequencing.
  UINT8                        RankInChannel;     // Rank number in a channel.
  UINT8                        MrIndex;           // Mode register index.
  UINT8                        Byte;              // Byte index.

  Inputs     = &MrcData->Inputs;
  MrcCall    = Inputs->Call.Func;
  Outputs    = &MrcData->Outputs;
  ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
  DimmOut    = &ChannelOut->Dimm[Dimm];
  for (Rank = 0; (Rank < MAX_RANK_IN_DIMM) && (Rank < DimmOut->RankInDimm); Rank++) {
    RmtRankLists                    = &RmtRank[Rank];
    RmtRankTraining                 = &RmtRankLists->RankTraining;
    RankInChannel                   = (Dimm * MAX_RANK_IN_DIMM) + Rank;
    RmtRankLists->RankEnabled       = TRUE;
    RmtRankLists->RankMarginEnabled = TRUE;
    RmtRankLists->DqMarginEnabled   = TRUE;
    MrcFillRmtDqMargin (&RmtRankLists->DqMargin[0], Controller, Channel, Dimm, Rank, MrcData);
    MrcFillRmtRankMargin (MrcData, &RmtRankLists->RankMargin, &RmtRankLists->DqMargin[0]);
    MrcFillRmtRankTraining (&RmtRankLists->RankTraining, Controller, Channel, Dimm, Rank, MrcData);
    for (Byte = 0; Byte < MAX_DRAM_DEVICE; Byte++) {
      for (MrIndex = 0; MrIndex < MAX_MODE_REGISTER; MrIndex++) {
        RmtRankLists->RankMRS[Byte].ModeRegister[MrIndex] = DimmOut->Rank[Rank].MR[MrIndex];
      }
    }
    RmtRankLists->RankMargin.CmdLeft      = ChannelOut->Command[RankInChannel].Left;
    RmtRankLists->RankMargin.CmdRight     = ChannelOut->Command[RankInChannel].Right;
    RmtRankLists->RankMargin.CmdVrefLow   = ChannelOut->Command[RankInChannel].Low;
    RmtRankLists->RankMargin.CmdVrefHigh  = ChannelOut->Command[RankInChannel].High;
    RmtRankLists->RankMargin.RecvenLeft   = ChannelOut->ReceiveEnable[RankInChannel].Left;
    RmtRankLists->RankMargin.RecvenRight  = ChannelOut->ReceiveEnable[RankInChannel].Right;
    RmtRankLists->RankMargin.WrLevelLeft  = ChannelOut->WriteLevel[RankInChannel].Left;
    RmtRankLists->RankMargin.WrLevelRight = ChannelOut->WriteLevel[RankInChannel].Right;
  }  // Rank loop
  return;
}

/**
  Initialize the memory dimm area of the RMT_STRUCTURE.

  @param[in, out] RmtDimm - Pointer to the start of the dimm information in the RMT table.
  @param[in] MrcData - The MRC "global data".
  @param[in] Channel - Current channel number.

  @retval Nothing.
**/
void
MrcFillRmtDimmStructure (
  IN OUT BDAT_DIMM_STRUCTURE *RmtDimm,
  IN     const MrcParameters *const MrcData,
  IN     UINT8               Controller,
  IN     UINT8               Channel
  )
{
  const MRC_FUNCTION  *MrcCall;
  const MrcInput      *Inputs;              // Pointer to the input portion of the MRC global data area.
  const MrcDimmIn     *DimmIn;              // Pointer to the DIMM input portion of the MRC global data area.
  const MrcSpd        *SpdIn;               // Pointer to the SPD input portion of the MRC global data area.
  const MrcOutput     *Outputs;             // Pointer to the output portion of the MRC global data area.
  const MrcChannelOut *ChannelOut;          // Pointer to the channel output portion of the MRC global data area.
  const MrcDimmOut    *DimmOut;             // Pointer to the DIMM output portion of the MRC global data area.
  BDAT_DIMM_STRUCTURE *RmtDimmList;         // Pointer to the current DIMM in the RMT structure.
  BDAT_SPD_STRUCTURE  *RmtSpdList;          // Pointer to the current SPD in the RMT structure.
  UINT8               Dimm;                 // Dimm count for sequencing.

  Inputs     = &MrcData->Inputs;
  MrcCall    = Inputs->Call.Func;
  Outputs    = &MrcData->Outputs;
  ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
  for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
    DimmOut = &ChannelOut->Dimm[Dimm];
    if (DimmOut->Status == DIMM_PRESENT) {
      RmtDimmList               = &RmtDimm[Dimm];
      RmtSpdList                = &RmtDimmList->SpdBytes;
      DimmIn                    = &Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm];
      SpdIn                     = &DimmIn->Spd.Data;
      RmtDimmList->DimmEnabled  = TRUE;
      MrcCall->MrcCopyMem ((UINT8 *) &RmtSpdList->SpdData[0], (UINT8 *) SpdIn, sizeof (MrcSpd));
      MrcCall->MrcSetMem ((UINT8 *) &RmtSpdList->SpdValid, sizeof (RmtDimmList->SpdBytes.SpdValid), 0xFF);

      //
      // Initialize the memory rank area of the RMT_STRUCTURE.
      //
      MrcFillRmtRankStructure (&RmtDimmList->RankList[0], MrcData, Controller, Channel, Dimm);
    } // end if
  } // Dimm loop
  return;
}

/**
  Initialize the memory channel area of the RMT_STRUCTURE.

  @param[in, out] RmtChannel - Pointer to the start of the channel information in the RMT table.
  @param[in] MrcData         - The MRC "global data".

  @retval Nothing.
**/
void
MrcFillRmtChannelStructure (
  IN OUT BDAT_CHANNEL_STRUCTURE *RmtChannel,
  IN     const MrcParameters    *MrcData,
  IN     const UINT8            Controller
  )
{
  const MrcOutput        *Outputs;             // Pointer to the output portion of the MRC global data area.
  BDAT_CHANNEL_STRUCTURE *RmtChannelList;      // Pointer to the current channel in the RMT structure.
  UINT8                  Channel;              // Channel count for sequencing.

  Outputs = &MrcData->Outputs;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (Outputs->Controller[Controller].Channel[Channel].Status == CHANNEL_PRESENT) {
      RmtChannelList                  = &RmtChannel[Channel];
      RmtChannelList->ChannelEnabled  = TRUE;
      RmtChannelList->NumDimmSlot     = MAX_DIMMS_IN_CHANNEL;

      //
      // Initialize the memory DIMM area of the RMT_STRUCTURE.
      //
      MrcFillRmtDimmStructure (&RmtChannelList->DimmList[0], MrcData, Controller, Channel);
    } // end if
  } // Channel loop
  return;
}

/**
  Initialize the memory controller area of the RMT_STRUCTURE.

  @param[in, out] RmtController - Pointer to the start of the controller information in the RMT table.
  @param[in] MrcData            - The MRC "global data".

  @retval Nothing.
**/
void
MrcFillRmtControllerStructure (
  IN OUT BDAT_SOCKET_STRUCTURE *RmtController,
  IN     const MrcParameters   *MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcOutput       *Outputs;
  BDAT_SOCKET_STRUCTURE *RmtControllerList;
  UINT8                 Controller;
  MrcVddSelect          VddVoltage;

  Inputs     = &MrcData->Inputs;
  Outputs    = &MrcData->Outputs;
  VddVoltage = Outputs->VddVoltage[Inputs->MemoryProfile];
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    if (Outputs->Controller[Controller].Status == CONTROLLER_PRESENT) {
      RmtControllerList                       = &RmtController[Controller];
      RmtControllerList->ControllerEnabled    = TRUE;
      RmtControllerList->ControllerDeviceId   = Outputs->Controller[Controller].DeviceId;
      RmtControllerList->ControllerRevisionId = Outputs->Controller[Controller].RevisionId;
      RmtControllerList->MemoryFrequency      = (UINT16) (Outputs->Frequency / 10);
      RmtControllerList->MemoryVoltage        = (UINT16) VddVoltage;
      //
      // Step unit = piStep * (tCK / 2048)
      //
      RmtControllerList->PiStep               = (UINT8) PI_STEP;
      RmtControllerList->RecvenStep           = (UINT8) PI_STEP;
      RmtControllerList->WrLevelStep          = (UINT8) PI_STEP;
      if (VddVoltage > 0) {
        //
        // Step unit = __VrefStep * Vdd / 100
        //
        RmtControllerList->RxVrefStep  = (UINT16) RX_VREF (VddVoltage);
        RmtControllerList->TxVrefStep  = (UINT16) TX_VREF (VddVoltage);
        RmtControllerList->CaVrefStep  = (UINT16) CA_VREF (VddVoltage);
      } else {
        RmtControllerList->RxVrefStep  = 0;
        RmtControllerList->TxVrefStep  = 0;
        RmtControllerList->CaVrefStep  = 0;
      }
      //
      // Initialize the memory channel area of the RMT_STRUCTURE.
      //
      MrcFillRmtChannelStructure (&RmtControllerList->ChannelList[0], MrcData, Controller);
    } // Controller loop
  }

  return;
}


/**
@brief
  Fill the compatible data structure RMT with the information provided by
  the memory initialization code.

  @param[in, out] MrcData      - Constant pointer to the Mrc data structure.
  @param[in, out] MemorySchema - The memory schema to fill.

  @retval Nothing.
**/
MrcStatus
FillRMTBdat2Structure (
  IN OUT MrcParameters *const       MrcData,
  IN OUT BDAT_MEMORY_DATA_STRUCTURE *MemorySchema
  )
{
  const MrcOutput                          *Outputs;
  BDAT_MEMORY_DATA_SCHEMA_2_RMT_STRUCTURE  *RmtSchema2;

  Outputs     = &MrcData->Outputs;

  // Initialize the system area of the RMT_STRUCTURE.
  RmtSchema2 = &MemorySchema->Schema.RmtSchema2;
  RmtSchema2->RefCodeRevision.Version.Major    = Outputs->Version.Major;
  RmtSchema2->RefCodeRevision.Version.Minor    = Outputs->Version.Minor;
  RmtSchema2->RefCodeRevision.Version.Revision = Outputs->Version.Rev;
  RmtSchema2->RefCodeRevision.Version.Build    = Outputs->Version.Build;
  RmtSchema2->MaxController                    = MAX_CONTROLLERS;
  RmtSchema2->MaxChannel                       = MAX_CHANNEL;
  RmtSchema2->MaxDimm                          = MAX_DIMMS_IN_CHANNEL;
  RmtSchema2->MaxRankDimm                      = MAX_RANK_IN_DIMM;
  RmtSchema2->MaxStrobe                        = MAX_STROBE;
  RmtSchema2->MaxDq                            = MAX_DQ;
  RmtSchema2->MarginLoopCount                  = Outputs->DQPatLC;
    
  // Initialize the memory controller area of the RMT_STRUCTURE.
  MrcFillRmtControllerStructure (&RmtSchema2->ControllerList[0], MrcData);

  return mrcSuccess;
}

/**
This function fills the RMT schema 6 which defined in the BDAT spec.
The schema include meta data and columns data sections.

@param[in, out] MrcData           - Include all MRC global data.
@param[out]     RmtDataBuffer     - Pointer to data block to fill up the RMT structure.
@param[in]      RmtDataBufferSize - Size of the RMT data block.
@param[in]      MsgPrint          - Show debug prints

@retval  None
**/
VOID
FillRMTBdat6BStructure (
  IN OUT MrcParameters *const MrcData,
  OUT   VOID           *RmtDataBuffer,
  IN    UINT32          RmtDataBufferSize,
  IN    BOOLEAN         MsgPrint
)
{
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  const MrcChannelOut *ChannelOut;       // Pointer to the channel output portion of the MRC global data area.
  const MrcDimmOut    *DimmOut;          // Pointer to the DIMM output portion of the MRC global data area.
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcDebugMsgLevel    DebugLevel;
  BDAT_SCHEMA_6B_BASE_RMT_RESULT     *RmtResults;
  RMT_RESULT_COLUMNS  *RmtRow;
  INT32 MaxNumberRows;
  INT32 *ResultElementCount;
  UINT8 Controller;
  UINT8 Channel;
  UINT8 Dimm;
  UINT8 Rank;
  UINT8 RankInChannel;     // Rank number in a channel.
  UINT8 Bit;
  UINT8 DqCnt;
  UINT8 Sdram;
  UINT8 Dq;                // DQ number in the rank.
  const MrcDqTimeMargin *RxDqMargin;      // Pointer to the output portion of the MRC global data area.
  const MrcDqTimeMargin *TxDqMargin;      // Pointer to the output portion of the MRC global data area.
  const MrcDqVrefMargin *RxVrefDqMargin;  // Pointer to the output portion of the MRC global data area.
  const MrcDqVrefMargin *TxVrefDqMargin;  // Pointer to the output portion of the MRC global data area.

  Outputs = &MrcData->Outputs;
  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &Outputs->Debug;
  DqCnt   = (Outputs->EccSupport) ? MAX_DQ : (MAX_DQ - MAX_BITS);
  DebugLevel = MsgPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;

  RmtResults = (BDAT_SCHEMA_6B_BASE_RMT_RESULT*) RmtDataBuffer;
  MrcCall->MrcSetMem ((UINT8*) RmtDataBuffer, RmtDataBufferSize, 0);
  MrcCall->MrcCopyMem ((UINT8*) (&RmtResults->ResultsHeader.MdBlock.MetadataType), (UINT8*) (&gRmtResultMetadataGuid), sizeof (RmtResults->ResultsHeader.MdBlock.MetadataType));
  RmtResults->ResultsHeader.MdBlock.MetadataSize = sizeof (RMT_RESULT_METADATA);
  MrcCall->MrcCopyMem ((UINT8*) (&RmtResults->ResultsHeader.RsBlock.ResultType), (UINT8*) (&gRmtResultColumnsGuid), sizeof (RmtResults->ResultsHeader.RsBlock.ResultType));
  RmtResults->ResultsHeader.RsBlock.ResultElementSize = sizeof (RMT_RESULT_COLUMNS);
  MaxNumberRows = RmtDataBufferSize - sizeof (RESULTS_DATA_HDR) - sizeof (RMT_RESULT_METADATA);
  MaxNumberRows = MaxNumberRows / sizeof (RMT_RESULT_COLUMNS);

  RmtResults->ResultsHeader.RsBlock.ResultCapacity = MaxNumberRows;
  ResultElementCount = &(RmtResults->ResultsHeader.RsBlock.ResultElementCount);
  *ResultElementCount = 0;
  RmtResults->Metadata.EnableCtlAllMargin       = 0;
  RmtResults->Metadata.SinglesBurstLength       = 128;  //  NumCL = 128;
  RmtResults->Metadata.SinglesLoopCount         = (Inputs->RMTLoopCount == 0) ? 17 : Inputs->RMTLoopCount;  //   DqLoopCount  = 17; CmdLoopCount = 17;
  RmtResults->Metadata.TurnaroundsBurstLength   = 0;
  RmtResults->Metadata.TurnaroundsLoopCount     = 0;
  RmtResults->Metadata.ScramblerOverrideMode    = DontTouchScrambler;
  RmtResults->Metadata.PiStepUnit[0]            = 0;
  RmtResults->Metadata.RxVrefStepUnit[0]        = 0;
  RmtResults->Metadata.TxVrefStepUnit[0][0]     = 0;
  RmtResults->Metadata.CmdVrefStepUnit[0][0]    = 0;
  RmtResults->Metadata.MajorVer                 = 1;
  RmtResults->Metadata.MinorVer                 = 0;
  RmtRow = &(RmtResults->Rows[0]);

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    if (Outputs->Controller[Controller].Status == CONTROLLER_PRESENT) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (Outputs->Controller[Controller].Channel[Channel].Status == CHANNEL_PRESENT) {
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            DimmOut = &ChannelOut->Dimm[Dimm];
            if (DimmOut->Status == DIMM_PRESENT) {
              for (Rank = 0; (Rank < MAX_RANK_IN_DIMM) && (Rank < DimmOut->RankInDimm); Rank++) {
                RankInChannel = (Dimm * MAX_RANK_IN_DIMM) + Rank;
                MRC_DEBUG_MSG (Debug, DebugLevel, "Ch: %d, D: %d R: %d \n", Channel, Dimm, Rank);
                // Per rank RankResultType0  - RxDqs, TxDq, RxVref and TxVref
                RmtRow[*ResultElementCount].Header.Controller = Controller;
                RmtRow[*ResultElementCount].Header.Channel    = Channel;
                RmtRow[*ResultElementCount].Header.DimmA      = Dimm;
                RmtRow[*ResultElementCount].Header.RankA      = Rank;
                RmtRow[*ResultElementCount].Header.IoLevel    = IO_LEVEL_DDR_LEVEL;
                RmtRow[*ResultElementCount].Header.ResultType = RankResultType0; //RxDqsdelay, TxDqDelay, RxVref, TxVref

                RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][LOW_INDEX]    = 0xFF;
                RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][HIGH_INDEX]   = 0xFF;
                RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][LOW_INDEX]    = 0xFF;
                RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][HIGH_INDEX]   = 0xFF;
                RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][LOW_INDEX]  = 0xFF;
                RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][HIGH_INDEX] = 0xFF;
                RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][LOW_INDEX]  = 0xFF;
                RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][HIGH_INDEX] = 0xFF;

                // Rank margin results are the min value of all DQ lanes.
                for (Dq = 0; Dq < DqCnt; Dq++) {
                  Sdram                   = Dq / MAX_BITS;
                  Bit                     = Dq % MAX_BITS;
                  RxDqMargin              = &ChannelOut->RxDqPb[RankInChannel][Sdram][Bit];
                  TxDqMargin              = &ChannelOut->TxDqPb[RankInChannel][Sdram][Bit];
                  RxVrefDqMargin          = &ChannelOut->RxDqVrefPb[RankInChannel][Sdram][Bit];
                  TxVrefDqMargin          = &ChannelOut->TxDqVrefPb[RankInChannel][Sdram][Bit];

                  if (RxDqMargin->Left < RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][LOW_INDEX]){
                    RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][LOW_INDEX] = RxDqMargin->Left;
                  }
                  if (RxDqMargin->Right < RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][HIGH_INDEX]){
                    RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][HIGH_INDEX] = RxDqMargin->Right;
                  }
                  if (TxDqMargin->Left < RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][LOW_INDEX]){
                    RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][LOW_INDEX] = TxDqMargin->Left;
                  }
                  if (TxDqMargin->Right < RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][HIGH_INDEX]){
                    RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][HIGH_INDEX] = TxDqMargin->Right;
                  }
                  if (RxVrefDqMargin->Low < RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][LOW_INDEX]){
                    RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][LOW_INDEX] = RxVrefDqMargin->Low;
                  }
                  if (RxVrefDqMargin->High < RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][HIGH_INDEX]){
                    RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][HIGH_INDEX] = RxVrefDqMargin->High;
                  }
                  if (TxVrefDqMargin->Low < RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][LOW_INDEX]){
                    RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][LOW_INDEX] = TxVrefDqMargin->Low;
                  }
                  if (TxVrefDqMargin->High < RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][HIGH_INDEX]){
                    RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][HIGH_INDEX] = TxVrefDqMargin->High;
                  }
                } // Dq loop
                if (MsgPrint) {
                  PrintBdatResult (MrcData, RmtRow, *ResultElementCount);
                }
                *ResultElementCount += 1;
                if (*ResultElementCount > MaxNumberRows) {
                  MRC_DEBUG_MSG (Debug, DebugLevel, "BDAT: Not enough space for results after filling per rank DQ signals.\n");
                  return;
                }
                // Per rank RankResultType1  - Cmd, Cmd Vref
                RmtRow[*ResultElementCount].Header.Controller = Controller;
                RmtRow[*ResultElementCount].Header.Channel    = Channel;
                RmtRow[*ResultElementCount].Header.DimmA      = Dimm;
                RmtRow[*ResultElementCount].Header.RankA      = Rank;
                RmtRow[*ResultElementCount].Header.IoLevel    = IO_LEVEL_DDR_LEVEL;
                RmtRow[*ResultElementCount].Header.ResultType = RankResultType1; //CmdAll, CmdVref, CtlAll
                RmtRow[*ResultElementCount].Margin[RESULTS_CMD_INDEX][LOW_INDEX]        = ChannelOut->Command[RankInChannel].Left;
                RmtRow[*ResultElementCount].Margin[RESULTS_CMD_INDEX][HIGH_INDEX]       = ChannelOut->Command[RankInChannel].Right;
                RmtRow[*ResultElementCount].Margin[RESULTS_CMD_VREF_INDEX][LOW_INDEX]   = ChannelOut->Command[RankInChannel].Low;
                RmtRow[*ResultElementCount].Margin[RESULTS_CMD_VREF_INDEX][HIGH_INDEX]  = ChannelOut->Command[RankInChannel].High;
                if (MsgPrint) {
                  PrintBdatResult (MrcData, RmtRow, *ResultElementCount);
                }
                *ResultElementCount += 1;
                if (*ResultElementCount > MaxNumberRows) {
                  MRC_DEBUG_MSG (Debug, DebugLevel, "BDAT: Not enough space for results after filling per rank Cmd signals.\n");
                  return;
                }

                // Per rank RankResultType1  - RecEn, Wrlvl
                RmtRow[*ResultElementCount].Header.Controller = Controller;
                RmtRow[*ResultElementCount].Header.Channel    = Channel;
                RmtRow[*ResultElementCount].Header.DimmA      = Dimm;
                RmtRow[*ResultElementCount].Header.RankA      = Rank;
                RmtRow[*ResultElementCount].Header.IoLevel    = IO_LEVEL_DDR_LEVEL;
                RmtRow[*ResultElementCount].Header.ResultType = RankResultType3; //RecEn and WrLvl
                RmtRow[*ResultElementCount].Margin[RESULTS_RECEN_INDEX][LOW_INDEX]  = ChannelOut->ReceiveEnable[RankInChannel].Left;
                RmtRow[*ResultElementCount].Margin[RESULTS_RECEN_INDEX][HIGH_INDEX] = ChannelOut->ReceiveEnable[RankInChannel].Right;
                RmtRow[*ResultElementCount].Margin[RESULTS_WRLVL_INDEX][LOW_INDEX]  = ChannelOut->WriteLevel[RankInChannel].Left;
                RmtRow[*ResultElementCount].Margin[RESULTS_WRLVL_INDEX][HIGH_INDEX] = ChannelOut->WriteLevel[RankInChannel].Right;
                if (MsgPrint) {
                  PrintBdatResult (MrcData, RmtRow, *ResultElementCount);
                }
                *ResultElementCount += 1;
                if (*ResultElementCount > MaxNumberRows) {
                  MRC_DEBUG_MSG (Debug, DebugLevel, "BDAT: Not enough space for results after filling per rank RecEn Wrlvl.\n");
                  return;
                }

                if (Inputs->BdatTestType == RankMarginToolPerBitType) {
                  for (Dq = 0; Dq < DqCnt; Dq++) {
                    MRC_DEBUG_MSG (Debug, DebugLevel, "Ch: %d, D: %d R: %d L: %d\n", Channel, Dimm, Rank, Dq);
                    // per lane LaneResultType  - RxDqs, TxDq, RxVref and TxVref
                    RmtRow[*ResultElementCount].Header.Controller = Controller;
                    RmtRow[*ResultElementCount].Header.Channel    = Channel;
                    RmtRow[*ResultElementCount].Header.DimmA      = Dimm;
                    RmtRow[*ResultElementCount].Header.RankA      = Rank;
                    RmtRow[*ResultElementCount].Header.Lane       = Dq;
                    RmtRow[*ResultElementCount].Header.IoLevel    = IO_LEVEL_DDR_LEVEL;
                    RmtRow[*ResultElementCount].Header.ResultType = LaneResultType; //RxDqsdelay, TxDqDelay, RxVref, TxVref

                    Sdram                   = Dq / MAX_BITS;
                    Bit                     = Dq % MAX_BITS;
                    RxDqMargin              = &ChannelOut->RxDqPb[RankInChannel][Sdram][Bit];
                    TxDqMargin              = &ChannelOut->TxDqPb[RankInChannel][Sdram][Bit];
                    RxVrefDqMargin          = &ChannelOut->RxDqVrefPb[RankInChannel][Sdram][Bit];
                    TxVrefDqMargin          = &ChannelOut->TxDqVrefPb[RankInChannel][Sdram][Bit];

                    RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][LOW_INDEX]    = RxDqMargin->Left;
                    RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][HIGH_INDEX]   = RxDqMargin->Right;
                    RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][LOW_INDEX]    = TxDqMargin->Left;
                    RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][HIGH_INDEX]   = TxDqMargin->Right;
                    RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][LOW_INDEX]  = RxVrefDqMargin->Low;
                    RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][HIGH_INDEX] = RxVrefDqMargin->High;
                    RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][LOW_INDEX]  = TxVrefDqMargin->Low;
                    RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][HIGH_INDEX] = TxVrefDqMargin->High;

                    if (MsgPrint) {
                      PrintBdatResult(MrcData, RmtRow, *ResultElementCount);
                    }
                    *ResultElementCount += 1;
                    if (*ResultElementCount > MaxNumberRows) {
                      MRC_DEBUG_MSG (Debug, DebugLevel, "BDAT: Not enough space for results after filling per bit DQ signals.\n");
                      return;
                    }
                  } // Dq
                } // RankMarginToolPerBitType
              } // Rank
            } // if Dimm present
          } // Dimm
        } // if Channel present
      } // Channel
    } // if Controller present
  } // Controller

  RmtResults->Metadata.ResultEleCount = (UINT16) *ResultElementCount;
} // FillBdatStructure

  /**
  This function fills the Margin2D.
  The schema include meta data and columns data sections.

  @param[in, out] MrcData           - Include all MRC global data.
  @param[out]     DataBuffer     - Pointer to data block to fill up the Margin2D result structure.
  @param[in]      DataBufferSize - Size of the Margin2D results data block.
  @param[in]      MsgPrint          - Show debug prints

  @retval  None
  **/
VOID
FillMargin2DBdatStructure (
  IN OUT MrcParameters *const MrcData,
  OUT   VOID           *DataBuffer,
  IN    UINT32          DataBufferSize,
  IN    BOOLEAN         MsgPrint
)
{
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  const MrcChannelOut *ChannelOut;       // Pointer to the channel output portion of the MRC global data area.
  const MrcDimmOut    *DimmOut;          // Pointer to the DIMM output portion of the MRC global data area.
  static const INT16  VrefPointsConst[] = {0, -6, -12, -18, 6, 12, 18};
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcDebugMsgLevel    DebugLevel;
  BDAT_MEMORY_DATA_SCHEMA_6B_MARGIN_2D_STRUCTURE *Margin2DResults;
  MARGIN_2D_RESULT_COLUMNS  *Margin2DRow;
  INT32 MaxNumberRows;
  INT32 *ResultElementCount;
  UINT8 Controller;
  UINT8 Channel;
  UINT8 Dimm;
  UINT8 Rank;
  UINT8 RankInChannel;     // Rank number in a channel.
  MARGIN_2D_EYE_TYPE EyeTypeIndex;
  UINT8 OuterOffsetIndex;

  Outputs = &MrcData->Outputs;
  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &Outputs->Debug;
  DebugLevel = MsgPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;

  Margin2DResults = (BDAT_MEMORY_DATA_SCHEMA_6B_MARGIN_2D_STRUCTURE*) DataBuffer;
  MrcCall->MrcSetMem ((UINT8*) DataBuffer, DataBufferSize, 0);
  MrcCall->MrcCopyMem ((UINT8*) (&Margin2DResults->ResultsHeader.MdBlock.MetadataType), (UINT8*) (&gMargin2DResultMetadataGuid), sizeof (Margin2DResults->ResultsHeader.MdBlock.MetadataType));
  Margin2DResults->ResultsHeader.MdBlock.MetadataSize = sizeof (MARGIN_2D_RESULT_METADATA);
  MrcCall->MrcCopyMem ((UINT8*) (&Margin2DResults->ResultsHeader.RsBlock.ResultType), (UINT8*) (&gMargin2DResultColumnsGuid), sizeof (Margin2DResults->ResultsHeader.RsBlock.ResultType));
  Margin2DResults->ResultsHeader.RsBlock.ResultElementSize = sizeof (MARGIN_2D_RESULT_COLUMNS);
  MaxNumberRows = DataBufferSize - sizeof (RESULTS_DATA_HDR) - sizeof (MARGIN_2D_RESULT_METADATA);
  MaxNumberRows = MaxNumberRows / sizeof (MARGIN_2D_RESULT_COLUMNS);
  Margin2DResults->ResultsHeader.RsBlock.ResultCapacity = MaxNumberRows;
  ResultElementCount = &(Margin2DResults->ResultsHeader.RsBlock.ResultElementCount);
  *ResultElementCount = 0;
  Margin2DResults->Metadata.BurstLength       = Outputs->NumCL;
  Margin2DResults->Metadata.LoopCount         = 15;
  Margin2DResults->Metadata.MajorVer          = 1;
  Margin2DResults->Metadata.MinorVer          = 0;
  Margin2DRow = &(Margin2DResults->Rows[0]);

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    if (Outputs->Controller[Controller].Status == CONTROLLER_PRESENT) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (Outputs->Controller[Controller].Channel[Channel].Status == CHANNEL_PRESENT) {
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            DimmOut = &ChannelOut->Dimm[Dimm];
            if (DimmOut->Status == DIMM_PRESENT) {
              for (Rank = 0; (Rank < MAX_RANK_IN_DIMM) && (Rank < DimmOut->RankInDimm); Rank++) {
                RankInChannel = (Dimm * MAX_RANK_IN_DIMM) + Rank;
                MRC_DEBUG_MSG (Debug, DebugLevel, "Ch: %d, D: %d R: %d \n", Channel, Dimm, Rank);
                for (EyeTypeIndex = RxDqsRxVrefEyeType; EyeTypeIndex <= TxDqTxVrefEyeType; EyeTypeIndex++) {
                  for (OuterOffsetIndex = 0; OuterOffsetIndex < MAX_2D_EYE_OFFSETS; OuterOffsetIndex++){
                    Margin2DRow[*ResultElementCount].Controller           = Controller;
                    Margin2DRow[*ResultElementCount].Channel              = Channel;
                    Margin2DRow[*ResultElementCount].Dimm                 = Dimm;
                    Margin2DRow[*ResultElementCount].Rank                 = Rank;
                    Margin2DRow[*ResultElementCount].Lane                 = 0; // We don't collect per lane margin2d data yet
                    Margin2DRow[*ResultElementCount].EyeType              = (UINT8) EyeTypeIndex;
                    Margin2DRow[*ResultElementCount].OuterMarginParamType = (UINT8) VotageMarginParamType;
                    Margin2DRow[*ResultElementCount].OuterOffset          = VrefPointsConst[OuterOffsetIndex];
                    Margin2DRow[*ResultElementCount].LeftMargin           = Outputs->Margin2DResult[EyeTypeIndex][RankInChannel][Channel][OuterOffsetIndex][1];
                    Margin2DRow[*ResultElementCount].RightMargin          = Outputs->Margin2DResult[EyeTypeIndex][RankInChannel][Channel][OuterOffsetIndex][0];
                    MRC_DEBUG_MSG (Debug, DebugLevel, "ElementCount:%d Controller:%d Channel:%d Dimm:%d Rank:%d lane:%d EyeType:%d OuterMarginParamType:%d OuterOffset:%d LeftMargin:%d RightMargin:%d \n",
                      *ResultElementCount,
                      Margin2DRow[*ResultElementCount].Controller,
                      Margin2DRow[*ResultElementCount].Channel,
                      Margin2DRow[*ResultElementCount].Dimm,
                      Margin2DRow[*ResultElementCount].Rank,
                      Margin2DRow[*ResultElementCount].Lane,
                      Margin2DRow[*ResultElementCount].EyeType,
                      Margin2DRow[*ResultElementCount].OuterMarginParamType,
                      Margin2DRow[*ResultElementCount].OuterOffset,
                      Margin2DRow[*ResultElementCount].LeftMargin,
                      Margin2DRow[*ResultElementCount].RightMargin
                    );
                    *ResultElementCount += 1;
                    if (*ResultElementCount > MaxNumberRows) {
                      MRC_DEBUG_MSG (Debug, DebugLevel, "BDAT: Not enough space for Margin2D results after filling row:%d.\n", (*ResultElementCount - 1));
                      return;
                    }
                  } // OuterOffset
                } // EyeType
              } // Rank
            } // if Dimm present
          } // Dimm
        } // if Channel present
      } // Channel
    } // if Controller present
  } // Controller

  Margin2DResults->Metadata.ResultEleCount = (UINT16) *ResultElementCount;
} // FillBdatStructure

/**
@brief
  Fill the compatible data structure RMT with the information provided by
  the memory initialization code.

  @param[in, out] MrcData - Constant pointer to the Mrc data structure which conatins the Rmt structure to fill.

  @retval Nothing.
**/
MrcStatus
MrcFillBdatStructure (
  IN OUT MrcParameters *const MrcData
  )
{
#ifndef MRC_MINIBIOS_BUILD
  const MRC_FUNCTION         *MrcCall;
  const MrcInput             *Inputs;
  MrcOutput                  *Outputs;
  MrcDebug                   *Debug;
  UINT8                      Index;
  EFI_GUID                   SchemaGuid;
  BDAT_MEMORY_DATA_STRUCTURE *MemorySchema;
  MRC_BDAT_SCHEMA_HEADER_STRUCTURE *BdatSchemaHdrPtr;
  EFI_STATUS   Status;
  UINT16       NextSchema;
  UINT32       BdatSchemaSize;
  UINT16       BdatHobSize;
  UINT8        BdatSchemaType;

#ifdef MRC_DEBUG_PRINT
  const char   RmtSchemaString[]      = "RMT";
  const char   Margin2DSchemaString[] = "Margin 2D";
  const char   *SchemaTypeString;
#endif // MRC_DEBUG_PRINT

  Outputs        = &MrcData->Outputs;
  Debug          = &Outputs->Debug;
  Inputs         = &MrcData->Inputs;
  MrcCall        = Inputs->Call.Func;
  MemorySchema   = NULL;

  BdatSchemaType = Inputs->BdatTestType;
  SchemaGuid     = (Inputs->BdatSchema == MrcBdatSchema6B) ? gSsaBiosResultsGuid : gEfiMemorySchemaGuid;

#ifdef MRC_DEBUG_PRINT
  if (BdatSchemaType == Margin2DType) {
    SchemaTypeString = Margin2DSchemaString;
  } else {
    SchemaTypeString = RmtSchemaString;
  }
#endif

  if (Inputs->BdatEnable) {
    // Find the first empty spot in the Schema List
    for (Index = 0; Index < MAX_SCHEMA_LIST_LENGTH; Index++) {
      if (Outputs->BdatMemoryHob[Index].Pointer == NULL) {
        break;
      }
    }

    // Create a HOB to store the BDAT Schema
    if ((Index < MAX_SCHEMA_LIST_LENGTH) && (Outputs->BdatSchemasHob.Pointer != NULL)) {
      BdatSchemaSize = sizeof (BDAT_MEMORY_DATA_STRUCTURE);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Filling/Saving %s structure of size %d at schema list index:%d\n", SchemaTypeString, BdatSchemaSize, Index);
      BdatHobSize = (UINT16) (BdatSchemaSize + sizeof (MRC_BDAT_SCHEMA_HEADER_STRUCTURE) + sizeof (EFI_HOB_GUID_TYPE));
      Status = MrcGetHobForDataStorage (
        (VOID **) &Outputs->BdatMemoryHob[Index].Pointer,
        BdatHobSize,
        &SchemaGuid
      );
      if (Status == EFI_SUCCESS) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s Schema %s HOB at %08Xh\n", SchemaTypeString, (Inputs->BdatSchema == MrcBdatSchema2) ? "2" : "6B", Outputs->BdatMemoryHob[Index]);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s HOB size: %d\n", SchemaTypeString, BdatHobSize);
        NextSchema = Outputs->BdatSchemasHob.Pointer->SchemaHobCount;
        Outputs->BdatSchemasHob.Pointer->SchemaHobCount = NextSchema + 1;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, ">SchemaHobCount: %d \n", Outputs->BdatSchemasHob.Pointer->SchemaHobCount);
        MrcCall->MrcCopyMem ((UINT8 *) &(Outputs->BdatSchemasHob.Pointer->SchemaHobGuids[NextSchema]), (UINT8 *) &SchemaGuid, sizeof (EFI_GUID));  // Housekeeping for the list of schema IDs
        MemorySchema = &((Outputs->BdatMemoryHob[Index].Pointer)->MemorySchema);
        BdatSchemaHdrPtr = (MRC_BDAT_SCHEMA_HEADER_STRUCTURE *) &(MemorySchema->SchemaHeader);
        MrcCall->MrcCopyMem ((UINT8 *) &BdatSchemaHdrPtr->SchemaId, (UINT8 *) &SchemaGuid, sizeof (EFI_GUID));
        BdatSchemaHdrPtr->DataSize = BdatSchemaSize;
        GetCrc16 ((UINT8 *) BdatSchemaHdrPtr, sizeof (MRC_BDAT_SCHEMA_HEADER_STRUCTURE), &BdatSchemaHdrPtr->Crc16);  // CRC for the schema header section only
        if (BdatSchemaType == Margin2DType) {
          FillMargin2DBdatStructure(
            MrcData,
            ((UINT8 *) MemorySchema) + sizeof (MRC_BDAT_SCHEMA_HEADER_STRUCTURE),
            BdatSchemaSize,
            FALSE
          );
        } else {
          if (Inputs->BdatSchema == MrcBdatSchema6B) {
            FillRMTBdat6BStructure (
              MrcData,
              ((UINT8 *) MemorySchema) + sizeof (MRC_BDAT_SCHEMA_HEADER_STRUCTURE),
              BdatSchemaSize,
              FALSE
            );
          } else {
            FillRMTBdat2Structure (
              MrcData,
              MemorySchema
            );
          }
        }
        GetCrc16 ((const UINT8 *const) MemorySchema, sizeof (BDAT_MEMORY_DATA_STRUCTURE), &MemorySchema->SchemaHeader.Crc16);
      }
    } else {
      if (Index == MAX_SCHEMA_LIST_LENGTH) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "No more room left in BDAT Schema List\n");
      } else if (Outputs->BdatSchemasHob.Pointer == NULL) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "BDAT Schema HOB Pointer is NULL!\n");
      }
    }

    if (MemorySchema != NULL) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "BdatMemoryHob->MemorySchema %Xh\n", (UINT32) MemorySchema);
      MrcWriteCR (MrcData, NCDECS_CR_SCRATCHPAD_NCU_2_REG, (UINT32) MemorySchema);
    }
  }
#endif
  return mrcSuccess;
}
#endif // BDAT_SUPPORT
