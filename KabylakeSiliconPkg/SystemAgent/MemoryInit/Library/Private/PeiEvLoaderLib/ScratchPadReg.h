/** @file
  Definitions of scratch pad registers used by BIOS SSA EV agent.

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

#ifndef __SCRATCHPAD_REG_H__
#define __SCRATCHPAD_REG_H__

#ifndef MRC_MINIBIOS_BUILD
#include <Library/DebugLib.h>
#endif
#include <MrcSsaServices.h>

//
// Address for SKL scratchpad registers
//
#define EV_AGENT_SCRATCHPAD_CMD_REG_ADDRESS_SKL                0x5018
#define EV_AGENT_SCRATCHPAD_CURRENT_CHECKPOINT_REG_ADDRESS_SKL 0x5428
#define EV_AGENT_SCRATCHPAD_DATA0_REG_ADDRESS_SKL              0x542c
#define EV_AGENT_SCRATCHPAD_DATA1_REG_ADDRESS_SKL              0x5430
#define EV_AGENT_SCRATCHPAD_CHECKPOINT_REG_ADDRESS_SKL         0x5434

typedef
UINT32
(*READ_SCRATCHPAD) (
  SSA_BIOS_SERVICES_PPI  *SsaServicesPpi,
  EFI_PHYSICAL_ADDRESS   baseAddress
  );

typedef
VOID
(*WRITE_SCRATCHPAD) (
  SSA_BIOS_SERVICES_PPI  *SsaServicesPpi,
  EFI_PHYSICAL_ADDRESS   baseAddress,
  UINT32                 val
  );

typedef struct _SCRATCHPAD_REGISTER_FUNCTIONS {
  READ_SCRATCHPAD  readScratchPad_CMD;
  WRITE_SCRATCHPAD writeScratchPad_CMD;
  READ_SCRATCHPAD  readScratchPad_DATA0;
  WRITE_SCRATCHPAD writeScratchPad_DATA0;
  READ_SCRATCHPAD  readScratchPad_DATA1;
  WRITE_SCRATCHPAD writeScratchPad_DATA1;
  READ_SCRATCHPAD  readScratchPad0;
  WRITE_SCRATCHPAD writeScratchPad_currentCheckPoint;
}SCRATCHPAD_REGISTER_FUNCTIONS;

//
// Factory to get scratchpad registers for platform
//
const SCRATCHPAD_REGISTER_FUNCTIONS *
GetScratchpadFunctions (
  SSA_BIOS_SERVICES_PPI         *SsaServicesPpi
  );

#endif //__SCRATCHPAD_REG_H__
