/** @file
  This file contains functions to get DDR IO Data Offsets
  used memory training.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2015 Intel Corporation.

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

#include "McAddress.h"
#include "MrcInterface.h"
#include "MrcDdrIoDataOffsets.h"

#ifdef SSA_FLAG
/**
  Function used to get the CR Offset for Data Read Groups.

  @param[in]  Group     - DDRIO group being accessed.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  Rank      - Rank index in the channel. (0-based).
  @param[in]  Strobe    - Dqs data group within the rank (0-based).
  @param[in]  Bit       - Bit index within the data group (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] RegOffset - Type of CR broadcast and various register offsets.

  @retval CR Offset.
**/
UINT32
GetDdrIoDataReadOffsets (
  IN  GSM_GT          Group,
  IN  UINT8           Socket,
  IN  UINT8           Channel,
  IN  UINT8           Rank,
  IN  UINT8           Strobe,
  IN  UINT8           Bit,
  IN  UINT8           FreqIndex,
  OUT MRC_REG_OFFSETS *RegOffset
  )
{
  UINT32 Offset = MRC_UINT32_MAX;

  switch (Group) {
    case RecEnDelay:
    case RxDqsPDelay:
    case RxDqsNDelay:
    case RxEq:
    case RxVref:
      if (Channel >= MAX_CHANNEL) {
        // Channel/Strobe Broadcast
        Offset = DDRDATA_CR_RXTRAINRANK0_REG +
          ((DDRDATA_CR_RXTRAINRANK1_REG - DDRDATA_CR_RXTRAINRANK0_REG) * Rank);
        RegOffset->BCastType = MrcBcastChannelStrobe;
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Strobe Broadcast
        Offset = DDRDATACH0_CR_RXTRAINRANK0_REG +
          ((DDRDATACH1_CR_RXTRAINRANK0_REG - DDRDATACH0_CR_RXTRAINRANK0_REG) * Channel) +
          ((DDRDATACH0_CR_RXTRAINRANK1_REG - DDRDATACH0_CR_RXTRAINRANK0_REG) * Rank);
        RegOffset->BCastType = MrcBcastStrobe;
      } else {
        Offset = DDRDATA0CH0_CR_RXTRAINRANK0_REG +
          ((DDRDATA0CH1_CR_RXTRAINRANK0_REG - DDRDATA0CH0_CR_RXTRAINRANK0_REG) * Channel) +
          ((DDRDATA0CH0_CR_RXTRAINRANK1_REG - DDRDATA0CH0_CR_RXTRAINRANK0_REG) * Rank) +
          ((DDRDATA1CH0_CR_RXTRAINRANK0_REG - DDRDATA0CH0_CR_RXTRAINRANK0_REG) * Strobe);
        RegOffset->BCastType = MrcBcastUnicast;
      }
      RegOffset->BOffset = DDRDATA0CH0_CR_RXTRAINRANK0_REG;
      RegOffset->COffset = DDRDATA0CH1_CR_RXTRAINRANK0_REG - DDRDATA0CH0_CR_RXTRAINRANK0_REG;
      RegOffset->ROffset = DDRDATA0CH0_CR_RXTRAINRANK1_REG - DDRDATA0CH0_CR_RXTRAINRANK0_REG;
      RegOffset->SOffset = DDRDATA1CH0_CR_RXTRAINRANK0_REG - DDRDATA0CH0_CR_RXTRAINRANK0_REG;
      break;

    case RxDqBitDelay:
      if (Channel >= MAX_CHANNEL) {
        // Channel/Strobe Broadcast
        Offset = DDRDATA_CR_RXPERBITRANK0_REG +
          ((DDRDATA_CR_RXPERBITRANK1_REG - DDRDATA_CR_RXPERBITRANK0_REG) * Rank);
        RegOffset->BCastType = MrcBcastChannelStrobe;
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Strobe Broadcast
        Offset = DDRDATACH0_CR_RXPERBITRANK0_REG +
          ((DDRDATACH1_CR_RXPERBITRANK0_REG - DDRDATACH0_CR_RXPERBITRANK0_REG) * Channel) +
          ((DDRDATACH0_CR_RXPERBITRANK1_REG - DDRDATACH0_CR_RXPERBITRANK0_REG) * Rank);
        RegOffset->BCastType = MrcBcastStrobe;
      } else {
        Offset = DDRDATA0CH0_CR_RXPERBITRANK0_REG +
          ((DDRDATA0CH0_CR_RXPERBITRANK1_REG - DDRDATA0CH0_CR_RXPERBITRANK0_REG) * Rank) +
          ((DDRDATA1CH0_CR_RXPERBITRANK0_REG - DDRDATA0CH0_CR_RXPERBITRANK0_REG) * Strobe) +
          ((DDRDATA0CH1_CR_RXPERBITRANK0_REG - DDRDATA0CH0_CR_RXPERBITRANK0_REG) * Channel);
        RegOffset->BCastType = MrcBcastUnicast;
      }
      RegOffset->BOffset = DDRDATA0CH0_CR_RXPERBITRANK0_REG;
      RegOffset->COffset = DDRDATACH1_CR_RXPERBITRANK0_REG - DDRDATACH0_CR_RXPERBITRANK0_REG;
      RegOffset->ROffset = DDRDATA_CR_RXPERBITRANK1_REG - DDRDATA_CR_RXPERBITRANK0_REG;
      RegOffset->SOffset = DDRDATA1CH0_CR_RXPERBITRANK0_REG - DDRDATA0CH0_CR_RXPERBITRANK0_REG;
      break;

    default:
      break;
  }

  return Offset;
}

/**
  Function used to get the CR Offset for Write Data Groups.

  @param[in]  Group     - DDRIO group being accessed.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  Rank      - Rank index in the channel. (0-based).
  @param[in]  Strobe    - Dqs data group within the rank (0-based).
  @param[in]  Bit       - Bit index within the data group (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] RegOffset - Type of CR broadcast and various register offsets.

  @retval CR Offset.
**/
UINT32
GetDdrIoDataWriteOffsets (
  IN  GSM_GT          Group,
  IN  UINT8           Socket,
  IN  UINT8           Channel,
  IN  UINT8           Rank,
  IN  UINT8           Strobe,
  IN  UINT8           Bit,
  IN  UINT8           FreqIndex,
  OUT MRC_REG_OFFSETS *RegOffset
  )
{
  UINT32 Offset = MRC_UINT32_MAX;

  switch (Group) {
    case TxDqsDelay:
    case TxDqDelay:
    case TxEq:
      if (Channel >= MAX_CHANNEL) {
        // Channel/Strobe Broadcast
        Offset = DDRDATA_CR_TXTRAINRANK0_REG +
          ((DDRDATA_CR_TXTRAINRANK1_REG - DDRDATA_CR_TXTRAINRANK0_REG) * Rank);
        RegOffset->BCastType = MrcBcastChannelStrobe;
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Strobe Broadcast
        Offset = DDRDATACH0_CR_TXTRAINRANK0_REG +
          ((DDRDATACH1_CR_TXTRAINRANK0_REG - DDRDATACH0_CR_TXTRAINRANK0_REG) * Channel) +
          ((DDRDATACH0_CR_TXTRAINRANK1_REG - DDRDATACH0_CR_TXTRAINRANK0_REG) * Rank);
        RegOffset->BCastType = MrcBcastStrobe;
      } else {
        Offset = DDRDATA0CH0_CR_TXTRAINRANK0_REG +
          ((DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Channel) +
          ((DDRDATA0CH0_CR_TXTRAINRANK1_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Rank) +
          ((DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Strobe);
        RegOffset->BCastType = MrcBcastUnicast;
      }
      RegOffset->BOffset = DDRDATA0CH0_CR_TXTRAINRANK0_REG;
      RegOffset->COffset = DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG;
      RegOffset->ROffset = DDRDATA0CH0_CR_TXTRAINRANK1_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG;
      RegOffset->SOffset = DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG;
      break;

    case TxDqBitDelay:
      if (Channel >= MAX_CHANNEL) {
        // Channel/Strobe Broadcast
        Offset = DDRDATA_CR_TXPERBITRANK0_REG +
          ((DDRDATA_CR_TXPERBITRANK1_REG - DDRDATA_CR_TXPERBITRANK0_REG) * Rank);
        RegOffset->BCastType = MrcBcastChannelStrobe;
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Strobe Broadcast
        Offset = DDRDATACH0_CR_TXPERBITRANK0_REG +
          ((DDRDATACH1_CR_TXPERBITRANK0_REG - DDRDATACH0_CR_TXPERBITRANK0_REG) * Channel) +
          ((DDRDATACH0_CR_TXPERBITRANK1_REG - DDRDATACH0_CR_TXPERBITRANK0_REG) * Rank);
        RegOffset->BCastType = MrcBcastStrobe;
      } else {
        Offset = DDRDATA0CH0_CR_TXPERBITRANK0_REG +
          ((DDRDATA0CH1_CR_TXPERBITRANK0_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG) * Channel) +
          ((DDRDATA0CH0_CR_TXPERBITRANK1_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG) * Rank) +
          ((DDRDATA1CH0_CR_TXPERBITRANK0_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG) * Strobe);
        RegOffset->BCastType = MrcBcastUnicast;
      }
      RegOffset->BOffset = DDRDATA0CH0_CR_TXPERBITRANK0_REG;
      RegOffset->COffset = DDRDATA0CH1_CR_TXPERBITRANK0_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG;
      RegOffset->ROffset = DDRDATA0CH0_CR_TXPERBITRANK1_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG;
      RegOffset->SOffset = DDRDATA1CH0_CR_TXPERBITRANK0_REG - DDRDATA0CH0_CR_TXPERBITRANK0_REG;
      break;

    default:
      break;
  }

  return Offset;
}

/**
  Function used to get the CR Offset for training offset Groups.

  @param[in]  Group     - DDRIO group being accessed.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  Rank      - Rank index in the channel. (0-based).
  @param[in]  Strobe    - Dqs data group within the rank (0-based).
  @param[in]  Bit       - Bit index within the data group (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] RegOffset - Type of CR broadcast and various register offsets.

  @retval CR Offset.
**/
UINT32
GetDdrIoDataTrainOffsets (
  IN  GSM_GT          Group,
  IN  UINT8           Socket,
  IN  UINT8           Channel,
  IN  UINT8           Rank,
  IN  UINT8           Strobe,
  IN  UINT8           Bit,
  IN  UINT8           FreqIndex,
  OUT MRC_REG_OFFSETS *RegOffset
  )
{
  UINT32 Offset = MRC_UINT32_MAX;

  switch (Group) {

    case RecEnOffset:
    case RxDqsOffset:
    case RxVrefOffset:
    case TxDqsOffset:
    case TxDqOffset:
      if (Channel >= MAX_CHANNEL) {
        //
        // Overall Broadcast
        //
        Offset = DDRDATA_CR_DDRCRDATAOFFSETTRAIN_REG;
        RegOffset->BCastType = MrcBcastOverall;
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        //
        // Channel Broadcast
        //
        Offset = DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_REG +
          ((DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_REG - DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_REG) * Channel);
        RegOffset->BCastType = MrcBcastChannel;
      } else {
        //
        // Specific Channel and Strobe
        //
        Offset = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG +
          ((DDRDATA0CH1_CR_DDRCRDATAOFFSETTRAIN_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG) * Channel) +
          ((DDRDATA1CH0_CR_DDRCRDATAOFFSETTRAIN_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG) * Strobe);
        RegOffset->BCastType = MrcBcastUnicast;
      }
      RegOffset->BOffset = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG;
      RegOffset->COffset = DDRDATA0CH1_CR_DDRCRDATAOFFSETTRAIN_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG;
      RegOffset->ROffset = 0;
      RegOffset->SOffset = DDRDATA1CH0_CR_DDRCRDATAOFFSETTRAIN_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG;
      break;

    default:
      break;
  }

  return Offset;
}

/**
  Function used to get the CR Offset for Data Control 1 Groups.

  @param[in]  Group     - DDRIO group being accessed.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  Rank      - Rank index in the channel. (0-based).
  @param[in]  Strobe    - Dqs data group within the rank (0-based).
  @param[in]  Bit       - Bit index within the data group (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset.
**/
UINT32
GetDdrIoDataControl1 (
  IN  GSM_GT  Group,
  IN  UINT8   Socket,
  IN  UINT8   Channel,
  IN  UINT8   Rank,
  IN  UINT8   Strobe,
  IN  UINT8   Bit,
  IN  UINT8   FreqIndex
  )
{
  UINT32 Offset = MRC_UINT32_MAX;

  switch (Group) {
    case RxCtleR:
      if (Channel >= MAX_CHANNEL) {
        //
        // Overall Broadcast
        //
        Offset = DDRDATA_CR_DDRCRDATACONTROL1_REG;
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        //
        // Channel Broadcast
        //
        Offset = DDRDATACH0_CR_DDRCRDATACONTROL1_REG +
          ((DDRDATACH1_CR_DDRCRDATACONTROL1_REG - DDRDATACH0_CR_DDRCRDATACONTROL1_REG) * Channel);
      } else {
        //
        // Specific Channel and Strobe
        //
        Offset = DDRDATA0CH0_CR_DDRCRDATACONTROL1_REG +
          ((DDRDATA0CH1_CR_DDRCRDATACONTROL1_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL1_REG) * Channel) +
          ((DDRDATA1CH0_CR_DDRCRDATACONTROL1_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL1_REG) * Strobe);
      }
      break;

    default:
      break;
  }

  return Offset;
}

/**
  Function used to get the CR Offset for Data Control 2 Groups.

  @param[in]  Group     - DDRIO group being accessed.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  Rank      - Rank index in the channel. (0-based).
  @param[in]  Strobe    - Dqs data group within the rank (0-based).
  @param[in]  Bit       - Bit index within the data group (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset.
**/
UINT32
GetDdrIoDataControl2 (
  IN  GSM_GT  Group,
  IN  UINT8   Socket,
  IN  UINT8   Channel,
  IN  UINT8   Rank,
  IN  UINT8   Strobe,
  IN  UINT8   Bit,
  IN  UINT8   FreqIndex
  )
{
  UINT32 Offset = MRC_UINT32_MAX;

  switch (Group) {
    case RxCtleC:
      if (Channel >= MAX_CHANNEL) {
        //
        // Overall Broadcast
        //
        Offset = DDRDATA_CR_DDRCRDATACONTROL2_REG;
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        //
        // Channel Broadcast
        //
        Offset = DDRDATACH0_CR_DDRCRDATACONTROL2_REG +
          ((DDRDATACH1_CR_DDRCRDATACONTROL2_REG - DDRDATACH0_CR_DDRCRDATACONTROL2_REG) * Channel);
      } else {
        //
        // Specific Channel and Strobe
        //
        Offset = DDRDATA0CH0_CR_DDRCRDATACONTROL2_REG +
          ((DDRDATA0CH1_CR_DDRCRDATACONTROL2_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL2_REG) * Channel) +
          ((DDRDATA1CH0_CR_DDRCRDATACONTROL2_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL2_REG) * Strobe);
      }
      break;

    default:
      break;
  }

  return Offset;
}

/**
  Function used to get the CR Offset for Data Offset Comp Groups.

  @param[in]  Group     - DDRIO group being accessed.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  Rank      - Rank index in the channel. (0-based).
  @param[in]  Strobe    - Dqs data group within the rank (0-based).
  @param[in]  Bit       - Bit index within the data group (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset.
**/
UINT32
GetDdrIoDataOffsetComp (
  IN  GSM_GT  Group,
  IN  UINT8   Socket,
  IN  UINT8   Channel,
  IN  UINT8   Rank,
  IN  UINT8   Strobe,
  IN  UINT8   Bit,
  IN  UINT8   FreqIndex
  )
{
  UINT32 Offset = MRC_UINT32_MAX;

  switch (Group) {
    case RxOdtUp:
    case RxOdtDn:
    case TxRonUp:
    case TxRonDn:
    case TxSlewRate:
      if (Channel >= MAX_CHANNEL) {
        //
        // Overall Broadcast
        //
        Offset = DDRDATA_CR_DDRCRDATAOFFSETCOMP_REG;
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        //
        // Channel Broadcast
        //
        Offset = DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_REG +
          ((DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_REG - DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_REG) * Channel);
      } else {
        //
        // Specific Channel and Strobe
        //
        Offset = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG +
          ((DDRDATA0CH1_CR_DDRCRDATAOFFSETCOMP_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG) * Channel) +
          ((DDRDATA1CH0_CR_DDRCRDATAOFFSETCOMP_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG) * Strobe);
      }
      break;

    default:
      break;
  }

  return Offset;
}
#endif // SSA_FLAG
