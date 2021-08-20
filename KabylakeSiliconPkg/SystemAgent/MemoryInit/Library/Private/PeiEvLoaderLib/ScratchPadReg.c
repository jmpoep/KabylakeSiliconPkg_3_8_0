/** @file
  Routines to access scratch pad register

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2015 Intel Corporation.

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

#include "ScratchPadReg.h"

//
// Routines to access scratch pad registers
//
UINT32
readScratchPad_CMD_SKL (
  SSA_BIOS_SERVICES_PPI     *SsaServicesPpi,
  EFI_PHYSICAL_ADDRESS      baseAddress
  )
{
  UINT32 val;
  SsaServicesPpi->SsaCommonConfig->ReadMem (SsaServicesPpi, RegWidth32, baseAddress + EV_AGENT_SCRATCHPAD_CMD_REG_ADDRESS_SKL, &val);
  return val;
}

VOID
writeScratchPad_CMD_SKL (
  SSA_BIOS_SERVICES_PPI     *SsaServicesPpi,
  EFI_PHYSICAL_ADDRESS      baseAddress,
  UINT32                    val
  )
{
  SsaServicesPpi->SsaCommonConfig->WriteMem (SsaServicesPpi, RegWidth32, baseAddress + EV_AGENT_SCRATCHPAD_CMD_REG_ADDRESS_SKL, &val);
}

UINT32
readScratchPad_DATA0_SKL (
  SSA_BIOS_SERVICES_PPI      *SsaServicesPpi,
  EFI_PHYSICAL_ADDRESS       baseAddress
  )
{
  UINT32 val;
  SsaServicesPpi->SsaCommonConfig->ReadMem (SsaServicesPpi, RegWidth32, baseAddress + EV_AGENT_SCRATCHPAD_DATA0_REG_ADDRESS_SKL, &val);
  return val;
}

VOID
writeScratchPad_DATA0_SKL (
  SSA_BIOS_SERVICES_PPI         *SsaServicesPpi,
  EFI_PHYSICAL_ADDRESS          baseAddress,
  UINT32                        val
  )
{
  SsaServicesPpi->SsaCommonConfig->WriteMem (SsaServicesPpi, RegWidth32, baseAddress + EV_AGENT_SCRATCHPAD_DATA0_REG_ADDRESS_SKL, &val);
}

UINT32
readScratchPad_DATA1_SKL (
  SSA_BIOS_SERVICES_PPI         *SsaServicesPpi,
  EFI_PHYSICAL_ADDRESS          baseAddress
  )
{
  UINT32 val;
  SsaServicesPpi->SsaCommonConfig->ReadMem (SsaServicesPpi, RegWidth32, baseAddress + EV_AGENT_SCRATCHPAD_DATA1_REG_ADDRESS_SKL, &val);
  return val;
}

VOID
writeScratchPad_DATA1_SKL (
  SSA_BIOS_SERVICES_PPI         *SsaServicesPpi,
  EFI_PHYSICAL_ADDRESS          baseAddress,
  UINT32                        val
  )
{
  SsaServicesPpi->SsaCommonConfig->WriteMem (SsaServicesPpi, RegWidth32, baseAddress + EV_AGENT_SCRATCHPAD_DATA1_REG_ADDRESS_SKL, &val);
}

UINT32
readScratchPad0_SKL (
  SSA_BIOS_SERVICES_PPI         *SsaServicesPpi,
  EFI_PHYSICAL_ADDRESS          baseAddress
  )
{
  UINT32 val;
  SsaServicesPpi->SsaCommonConfig->ReadMem (SsaServicesPpi, RegWidth32, baseAddress + EV_AGENT_SCRATCHPAD_CHECKPOINT_REG_ADDRESS_SKL, &val);
  return val;
}

VOID
writeScratchPad_currentCheckPoint_SKL (
  SSA_BIOS_SERVICES_PPI         *SsaServicesPpi,
  EFI_PHYSICAL_ADDRESS          baseAddress,
  UINT32                        val
  )
{
  SsaServicesPpi->SsaCommonConfig->WriteMem (SsaServicesPpi,RegWidth32,baseAddress + EV_AGENT_SCRATCHPAD_CURRENT_CHECKPOINT_REG_ADDRESS_SKL, &val);
}


const SCRATCHPAD_REGISTER_FUNCTIONS SklScratchpadRegisterFunctions = {
  readScratchPad_CMD_SKL,
  writeScratchPad_CMD_SKL,
  readScratchPad_DATA0_SKL,
  writeScratchPad_DATA0_SKL,
  readScratchPad_DATA1_SKL,
  writeScratchPad_DATA1_SKL,
  readScratchPad0_SKL,
  writeScratchPad_currentCheckPoint_SKL,
};

const SCRATCHPAD_REGISTER_FUNCTIONS *
GetScratchpadFunctions (
  SSA_BIOS_SERVICES_PPI         *SsaServicesPpi
  )
{
  return &SklScratchpadRegisterFunctions;
}
