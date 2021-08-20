/** @file
  This file contains functions to get DDR IO Data Offsets
  used memory training.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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

#ifndef _MRC_DDR_IO_DATA_OFFSETS_H_
#define _MRC_DDR_IO_DATA_OFFSETS_H_
#include "MrcInterface.h"

#pragma pack (push, 1)
typedef enum {
  MrcBcastUnicast,
  MrcBcastChannelStrobe,
  MrcBcastStrobe,
  MrcBcastChannel,
  MrcBcastController,
  MrcBcastOverall,
  MrcBcastMax,
  MrcBcastDelimiter = 0x7FFFFFFF
} MRC_BCAST_TYPES;

typedef struct {
  MRC_BCAST_TYPES BCastType;
  UINT32          BOffset;
  UINT32          COffset;
  UINT32          ROffset;
  UINT32          SOffset;
} MRC_REG_OFFSETS;

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
  );

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
  );

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
  );

/**
  Function used to get the CR Offset for training offset Groups.

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
  );

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
  );

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
  );

#pragma pack (pop)
#endif // _MRC_DDR_IO_DATA_OFFSETS_H_
