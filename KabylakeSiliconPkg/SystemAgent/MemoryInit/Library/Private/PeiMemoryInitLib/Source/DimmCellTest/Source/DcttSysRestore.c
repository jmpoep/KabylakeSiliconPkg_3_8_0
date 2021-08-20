/** @file
  Manages the saving and restoring of various MC/DIMM values that the
  tool may adjust in testing memory.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2015 Intel Corporation.

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
#include "DcttApiFunctions.h"
#include "DcttRegList.h"
#include "DcttMarginFunctions.h"
#include "DcttSysRestore.h"
#include "DcttCpgcFunctions.h"


INT32
SysRestore_InitObject (
  DCTT_API            *DcttMain,
  DCTT_SYSTEM_RESTORE *RestoreData
  )
{
  RestoreData->numChannels  = DcttMain->DcttConfigData.numberChannels;
  RestoreData->numRanks     = DcttMain->DcttConfigData.numberRankPerChannel;

  return DCTT_SUCCESS;
}

INT32
SysRestore_TakeSnapshot (
  DCTT_API            *DcttMain,
  DCTT_SYSTEM_RESTORE *RestoreData
  )
{
  MCDECS_CR_MC_INIT_STATE_G_MCMAIN_STRUCT McInitStateG;
  UINT32  RegAddress;
  UINT8   Channel;

  McInitStateG.Data = DcttReadReg32Func (DcttMain, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
  RestoreData->RefreshesEnabled = (McInitStateG.Bits.refresh_enable == 1) ? TRUE : FALSE;
  DcttGetSelfRefreshConfigFunc (DcttMain, &RestoreData->SelfRefreshEnabled, &RestoreData->SelfRefreshIdleTimer);

  for (Channel = 0; Channel < RestoreData->numChannels; Channel++) {
    RegAddress = DcttGetMcAddressFunc (DcttMain, DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
    RestoreData->seqConfig[Channel] = DcttReadReg64Func (DcttMain, RegAddress);
    MarginFunctions_GetMarginParamValue (
      DcttMain,
      Channel,
      DcttMain->DcttConfigData.marginOperation,
      &RestoreData->MarginParamValue[Channel]
      );
    RestoreData->RefreshVal[Channel] = DcttGetRefiFunc (DcttMain, 0, Channel);
  }

  return DCTT_SUCCESS;
}

INT32
SysRestore_RestoreSnapshot (
  DCTT_API            *DcttMain,
  DCTT_SYSTEM_RESTORE *RestoreData
  )
{
  UINT8   Channel;
  UINT32  RegAddress;

  CPGCFunctions_RefreshControl (DcttMain, RestoreData->RefreshesEnabled);
  DcttSetSelfRefreshConfigFunc (DcttMain, &RestoreData->SelfRefreshEnabled, &RestoreData->SelfRefreshIdleTimer);

  for (Channel = 0; Channel < RestoreData->numChannels; Channel++) {
    RegAddress = DcttGetMcAddressFunc (DcttMain, DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
    DcttWriteReg64Func (DcttMain, RegAddress, RestoreData->seqConfig[Channel]);
    MarginFunctions_ChangeMargin (
      DcttMain,
      Channel,
      DcttMain->DcttConfigData.marginOperation,
      RestoreData->MarginParamValue[Channel]
      );
    DcttSetRefiFunc (DcttMain, 0, Channel, RestoreData->RefreshVal[Channel]);
  }

  return DCTT_SUCCESS;
}
