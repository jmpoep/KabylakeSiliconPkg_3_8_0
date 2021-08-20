/** @file
  Implementation of the memory controller hardware abstraction layer.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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
#include "MrcMcRegisterEnum.h"
#include "MrcMcRegisterMacro.h"
#include "MrcHalRegisterAccess.h"
#include "MrcInterface.h"
#include "MrcCommon.h"
#include "MrcDebugPrint.h"

#ifdef SSA_FLAG
/**
  This function waits for the test to complete on the specified channels.

  @param[in]  MrcData     - Include all MRC global data.
  @param[in]  ChannelMask - Channels to operate on. bit 0 = channel 0, bit 1 = channel 1, etc.
  @param[out] StatusMask  - Channels where the test failed. bit 0 = channel 0, bit 1 = channel 1, etc.

  @retval mrcSuccess, mrcFail if at least one channel stopped with error, or mrcDeviceBusy on timeout.
**/
MrcStatus
MrcHalWaitForMrcTestCompletion (
  IN MrcParameters *const MrcData,
  IN const UINT32  ChannelMask,
  OUT UINT8        *const StatusMask
  )
{
  const MRC_FUNCTION  *MrcCall;
  MRC_GET_CPU_TIME    MrcGetCpuTime;
  UINT64              Timer;
  UINT32              RunStatusMask;
  UINT32              ErrorStatusMask;

  MrcCall        = MrcData->Inputs.Call.Func;
  MrcGetCpuTime  = MrcCall->MrcGetCpuTime;
  Timer          = MrcGetCpuTime (MrcData) + 10000; // 10 Second timeout
  do {
    MrcHalGetReutGlobalStatus (MrcData, &RunStatusMask, &ErrorStatusMask);
    ErrorStatusMask &= ChannelMask;
  } while (
           ((RunStatusMask & ChannelMask) != ChannelMask)
           && (MrcGetCpuTime (MrcData) < Timer)
          );
  if ((RunStatusMask & ChannelMask) != ChannelMask) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_ERROR,
      "Timeout occured while running the test, channel bit mask: 0x%X.\n",
      RunStatusMask & ChannelMask
      );
    return (mrcDeviceBusy);
  }
  if (ErrorStatusMask) {
    return (mrcFail);
  }
  return (mrcSuccess);
}

/**
  This function waits for self refresh entry or exit to complete.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Flag    - TRUE when entering, FALSE when exiting self refresh.

  @retval mrcSuccess or mrcDeviceBusy on timeout.
**/
MrcStatus
MrcHalWaitForSelfRefreshTransition (
  IN MrcParameters *const MrcData,
  IN const BOOLEAN Flag
  )
{
  const MRC_FUNCTION  *MrcCall;
  MRC_GET_CPU_TIME    MrcGetCpuTime;
  UINT64              Timer;
  BOOLEAN             Transition;

  MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "Waiting for MC to e%s self refresh\n", Flag ? "nter" : "xit");
  MrcCall        = MrcData->Inputs.Call.Func;
  MrcGetCpuTime  = MrcCall->MrcGetCpuTime;
  Timer          = MrcGetCpuTime (MrcData) + 10000; // 10 Second timeout
  do {
    Transition = (MrcHalGetBfMcdecsCrStallDrainMcmainSrState (MrcHalGetRegMcdecsCrStallDrainMcmain (MrcData)) != (UINT32) Flag);
  } while (
           (Transition)
           && (MrcGetCpuTime (MrcData) < Timer)
          );
  if (Transition) {
    MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "Timeout occured\n");
    return (mrcDeviceBusy);
  }
  return (mrcSuccess);
}
#endif // SSA_FLAG
