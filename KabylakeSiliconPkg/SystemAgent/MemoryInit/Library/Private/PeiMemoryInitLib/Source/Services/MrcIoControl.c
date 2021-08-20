/** @file
  This file is used as a driver to all memory controller IO registers.
  It includes all the functions that the MRC needs to configure the IO and do the training.

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
//
// Include files
//
#include "MrcIoControl.h"

/**
  Reset the MC IO module. The MC hardware will handle creating the 20 dclk pulse
  after the bit is set and will also clear the bit.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess    - IO Reset was done successfully
  @retval mrcDeviceBusy - Timed out waiting for the IO to clear the bit
**/
MrcStatus
IoReset (
  IN MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION                      *MrcCall;
  MCDECS_CR_MC_INIT_STATE_G_MCMAIN_STRUCT McInitStateG;
  BOOLEAN                                 Busy;
  UINT64                                  Timeout;

  MrcCall = MrcData->Inputs.Call.Func;
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout

  McInitStateG.Data          = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
  McInitStateG.Bits.no_block_reset_io = 1;
  MrcWriteCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG, McInitStateG.Data);

  //
  // Wait until the bit is cleared by hardware
  //
  do {
    McInitStateG.Data = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
    Busy              = (McInitStateG.Bits.no_block_reset_io == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));


  MrcWait (MrcData, 60 * HPET_1US); // @todo Temporary W/A for LCT/CMDVC failures on some DDR3 SO-DIMMs

  return (Busy ? mrcDeviceBusy : mrcSuccess);
}

/**
  Reset the MC IO module. The MC hardware will handle creating the 20 dclk pulse
  after the bit is set and will also clear the bit.

  @param[in] MrcData - Include all MRC global data.
  @param[in] TrainingStep - define mode of reset.  The default is 0.

  @retval mrcSuccess    - IO Reset was done successfully
  @retval mrcDeviceBusy - Timed out waiting for the IO to clear the bit
**/
MrcStatus
MrcIoReset (
  IN MrcParameters *const MrcData,
  UINT16                  TrainingStep
  )
{
  const MRC_FUNCTION                        *MrcCall;
  const MrcInput                            *Inputs;
  MrcDebug                                  *Debug;
  MrcStatus                                 Status;
  MrcIntOutput                              *MrcIntData;
  MrcOutput                                 *Outputs;
  DDRSCRAM_CR_DDRMISCCONTROL0_STRUCT        DdrMiscControl0;
  DDRDATACH0_CR_DDRCRDATACONTROL0_STRUCT    DdrCrDataControl0;
  DDRDATACH0_CR_DDRCRDATACONTROL0_STRUCT    DdrCrDataControl0Save;
  DDRDATA0CH0_CR_RCOMPDATA1_STRUCT          DdrDataRcompData1;
  DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetComp;
  UINT32                                    CompSave[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32                                    CompOffSave[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8                                     Channel;
  UINT8                                     Byte;
  UINT32                                    Offset;
  MrcIntControllerOut                       *IntControllerOut;

  MrcCall = MrcData->Inputs.Call.Func;
  Inputs  = &MrcData->Inputs;
  Debug   = &MrcData->Outputs.Debug;
  Outputs             = &MrcData->Outputs;
  MrcIntData          = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntControllerOut    = &MrcIntData->Controller[0];
  DdrMiscControl0.Data = IntControllerOut->MiscControl0.Data;
  DdrCrDataControl0Save.Data = 0;


  if (TrainingStep == OemReceiveEnable) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0);
      DdrCrDataControl0Save.Data = DdrCrDataControl0.Data = MrcReadCR (MrcData, Offset);
      DdrCrDataControl0.Bits.ForceOdtOn = 0;
      Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
      MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);
    }
  }

  if (TrainingStep == 0) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        //  comp codes
        Offset = DDRDATA0CH0_CR_RCOMPDATA1_REG +
          ((DDRDATA0CH1_CR_RCOMPDATA1_REG - DDRDATA0CH0_CR_RCOMPDATA1_REG) * Channel) +
          ((DDRDATA1CH0_CR_RCOMPDATA1_REG - DDRDATA0CH0_CR_RCOMPDATA1_REG) * Byte);
        DdrDataRcompData1.Data = MrcReadCR (MrcData, Offset);
        CompSave[Channel][Byte] = DdrDataRcompData1.Data;
        DdrDataRcompData1.Bits.RcompOdtUp = 0;
        MrcWriteCR (MrcData, Offset, DdrDataRcompData1.Data);
        // comp offsets
        Offset = MrcGetOffsetDataOffsetComp (MrcData, Channel, Byte);
        DdrCrDataOffsetComp.Data = MrcReadCR (MrcData, Offset);
        CompOffSave[Channel][Byte] = DdrCrDataOffsetComp.Data;
        DdrCrDataOffsetComp.Bits.DqOdtUpCompOffset = 0;
        MrcWriteCR (MrcData, Offset, DdrCrDataOffsetComp.Data);
      }
    }
    DdrMiscControl0.Bits.DataClkGateDisAtIdle = 1;
    DdrMiscControl0.Bits.ForceCompUpdate = 1;
    MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL0_REG, DdrMiscControl0.Data);
  }

  Status = IoReset (MrcData);

  //
  // Clean up
  //
  if (TrainingStep == OemReceiveEnable) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++)   {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
      MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0Save.Data);
    }
  }

  if (TrainingStep == 0) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++)   {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        // restore comp codes
        Offset = DDRDATA0CH0_CR_RCOMPDATA1_REG +
          ((DDRDATA0CH1_CR_RCOMPDATA1_REG - DDRDATA0CH0_CR_RCOMPDATA1_REG) * Channel) +
          ((DDRDATA1CH0_CR_RCOMPDATA1_REG - DDRDATA0CH0_CR_RCOMPDATA1_REG) * Byte);
        MrcWriteCR (MrcData, Offset, CompSave[Channel][Byte]);
        // restore comp offset up
        Offset = MrcGetOffsetDataOffsetComp (MrcData, Channel, Byte);
        MrcWriteCR (MrcData, Offset, CompOffSave[Channel][Byte]);
      }
    }
    // force update bit already 1
    MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL0_REG, DdrMiscControl0.Data);
    // restore misc reg
    MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL0_REG, IntControllerOut->MiscControl0.Data);
  }

  return Status;
}

