/** @file
  DCTT CPGC functions to test memory.

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
#include "DcttCpgcFunctions.h"
#include "DcttDebug.h"
#include "DcttSymbol.h"
#include "DcttHelpers.h"
#include "DcttPauseRefresh.h"
#include "DcttAddressFunctions.h"
#include "DcttPrintHelpers.h"

#define SELF_REFRESH_IDLE_COUNT (0x200)

/*
  Determines the selected and presnet channels by AND'ing
  the config requested channels and the channels present.

  @param[in] -

  @retval Channel Bit Mask
*/
UINT8
DCTT_GetChannelMask (
  DCTT_API  *DcttMain,
  UINT8     Controller
  )
{
  UINT8 configMask;
  UINT8 SystemMask;
  UINT8 resultMask;

  SystemMask = DcttSysGetPresentChannelBitMaskFunc (DcttMain, 0);
  configMask = (UINT8) DcttMain->DcttConfigData.channelBitMask;

  resultMask = SystemMask & configMask;

  return resultMask;
}

BOOLEAN
DCTT_ChannelExists (
  DCTT_API  *DcttMain,
  UINT8     Controller,
  UINT8     Channel
  )
{
  UINT32  ChannelMask;
  BOOLEAN Result;

  Result = DcttSysChannelExistsFunc (DcttMain, Controller, Channel);
  if (Result) {
    ChannelMask = DcttMain->DcttConfigData.channelBitMask;
    ChannelMask = ((ChannelMask >> Channel) & 1);
    if (ChannelMask != 1) {
      Result = FALSE;
    }
  }

  return Result;
}

BOOLEAN
DCTT_RankInChannelExists (
  DCTT_API  *DcttMain,
  UINT8     Controller,
  UINT8     Rank,
  UINT8     Channel
  )
{
  BOOLEAN Result;
  UINT8   RankMask;

  Result = DcttSysRankInChannelExistsFunc (DcttMain, Controller, Channel, Rank);
  if (Result) {
    RankMask = DcttMain->DcttConfigData.ranksToIgnoreBitMask[Channel];
    RankMask = ((RankMask >> Rank) & 1);
    if (RankMask) {
      Result = FALSE;
    }
    if (DcttMain->DcttConfigData.SubMemoryRangeTest) {
      if ((Rank < DcttMain->DcttConfigData.internalBottomAddress[Channel].Rank) ||
          (Rank > DcttMain->DcttConfigData.internalTopAddress[Channel].Rank)) {
        Result = FALSE;
      }
    }
  }

  return Result;
}

VOID
CPGCFunctions_SetRefreshDisableBitmask (
  DCTT_API  *DcttMain,
  UINT8     RankMask
  )
{
  UINT8           Channel;
  UINT32          RefreshRegData;
  UINT32          ReutRegAddress;

  for (Channel = 0; Channel < DcttMain->DcttConfigData.numberChannels; Channel++) {
    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_MISC_REFRESH_CTRL,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );

    RefreshRegData = DcttReadReg32Func (DcttMain, ReutRegAddress);

    RefreshRegData = (UINT32) Helpers_SetField (
                                RefreshRegData,
                                RankMask,
                                DCTT_REUT_CH_MISC_REFRESH_CTRL_F_REFRESH_RANK_MASK_START,
                                DCTT_REUT_CH_MISC_REFRESH_CTRL_F_REFRESH_RANK_MASK_LEN
                                );

    DcttWriteReg32Func (DcttMain, ReutRegAddress, RefreshRegData);
  }
}

#ifndef DISABLE_DUMMY_READS
INT32
CPGCFunctions_SetDummyReadRegisters (
  DCTT_API  *DcttMain
  )
{
  DCTT_CONFIG_PARAMS  *DcttConfig;
  UINT32              ReutRegAddress;
  UINT8               Channel;
  UINT32              DummyReadMask;
  UINT32              DummyReadCtl;

  DcttConfig = &DcttMain->DcttConfigData;

  DcttLogDebug (DcttMain, "+++++++");
  DcttLogVerbose (DcttMain, "Enabling Dummy Reads\n");
  for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
    DummyReadMask  = 0;
    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_DUMMYREAD_MASK_0,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    DcttWriteReg32Func (DcttMain, ReutRegAddress, DummyReadMask);

    DummyReadCtl = 0;

    DummyReadCtl = (UINT32) Helpers_SetField (
                              DummyReadCtl,
                              0, // 1
                              DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_F_L_DUMMY_READ_SELECT_START,
                              DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_F_L_DUMMY_READ_SELECT_LEN
                              );

    DummyReadCtl = (UINT32) Helpers_SetField (
                              DummyReadCtl,
                              0,
                              DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_F_ENABLE_SWEEP_FREQ_START,
                              DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_F_ENABLE_SWEEP_FREQ_LEN
                              );

    DummyReadCtl = (UINT32) Helpers_SetField (
                              DummyReadCtl,
                              DcttConfig->startTestDelay + 5,
                              DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_F_L_COUNTER_START,
                              DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_F_L_COUNTER_LEN
                              );

    //Setting M counter to max value
    DummyReadCtl = (UINT32) Helpers_SetField (
                              DummyReadCtl,
                              (1 << DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_F_M_COUNTER_LEN) - 1, // 1
                              DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_F_M_COUNTER_START,
                              DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_F_M_COUNTER_LEN
                              );

    //Setting N counter to min value
    DummyReadCtl = (UINT32) Helpers_SetField (
                              DummyReadCtl,
                              1, // (1 << DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_F_N_COUNTER_LEN) - 1
                              DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_F_N_COUNTER_START,
                              DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_F_N_COUNTER_LEN
                              );

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_DUMMYREAD_CTL_0,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );

    DcttWriteReg32Func (DcttMain, ReutRegAddress, DummyReadCtl);
  }

  return DCTT_SUCCESS;
}
#endif

#ifndef DISABLE_SWIZZLE
INT32
CPGCFunctions_ChangeSwizzle (
  DCTT_API  *DcttMain,
  UINT8     *NewSwizzle
  )
{
  // TODO: Add checkup for invalid swizzles
  UINT32          ReutRegAddress;
  UINT64          UpperSwizzle;
  UINT32          LowerSwizzle;
  UINT8           Channel;

  for (Channel = 0; Channel < DcttMain->DcttConfigData.numberChannels; Channel++) {
    UpperSwizzle = 0;
    LowerSwizzle = 0;

    LowerSwizzle = (UINT32) Helpers_SetField (
                              LowerSwizzle,
                              NewSwizzle[0],
                              DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW0_START,
                              DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW0_LEN
                              );

    LowerSwizzle = (UINT32) Helpers_SetField (
                              LowerSwizzle,
                              NewSwizzle[1],
                              DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW1_START,
                              DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW1_LEN
                              );

    LowerSwizzle = (UINT32) Helpers_SetField (
                              LowerSwizzle,
                              NewSwizzle[2],
                              DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW2_START,
                              DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW2_LEN
                              );

    LowerSwizzle = (UINT32) Helpers_SetField (
                              LowerSwizzle,
                              NewSwizzle[3],
                              DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW3_START,
                              DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW3_LEN
                              );

    LowerSwizzle = (UINT32) Helpers_SetField (
                              LowerSwizzle,
                              NewSwizzle[4],
                              DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW4_START,
                              DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW4_LEN
                              );

    LowerSwizzle = (UINT32) Helpers_SetField (
                              LowerSwizzle,
                              NewSwizzle[5],
                              DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW5_START,
                              DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW5_LEN
                              );

    UpperSwizzle = Helpers_SetField (
                     UpperSwizzle,
                     NewSwizzle[6],
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW6_START,
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW6_LEN
                     );

    UpperSwizzle = Helpers_SetField (
                     UpperSwizzle,
                     NewSwizzle[7],
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW7_START,
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW7_LEN
                     );

    UpperSwizzle = Helpers_SetField (
                     UpperSwizzle,
                     NewSwizzle[8],
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW8_START,
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW8_LEN
                     );

    UpperSwizzle = Helpers_SetField (
                     UpperSwizzle,
                     NewSwizzle[9],
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW9_START,
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW9_LEN
                     );

    UpperSwizzle = Helpers_SetField (
                     UpperSwizzle,
                     NewSwizzle[10],
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW10_START,
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW10_LEN
                     );

    UpperSwizzle = Helpers_SetField (
                     UpperSwizzle,
                     NewSwizzle[11],
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW11_START,
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW11_LEN
                     );

    UpperSwizzle = Helpers_SetField (
                     UpperSwizzle,
                     NewSwizzle[12],
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW12_START,
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW12_LEN
                     );

    UpperSwizzle = Helpers_SetField (
                     UpperSwizzle,
                     NewSwizzle[13],
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW13_START,
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW13_LEN
                     );

    UpperSwizzle = Helpers_SetField (
                     UpperSwizzle,
                     NewSwizzle[14],
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW14_START,
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW14_LEN
                     );

    UpperSwizzle = Helpers_SetField (
                     UpperSwizzle,
                     NewSwizzle[15],
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW15_START,
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW15_LEN
                     );

    UpperSwizzle = Helpers_SetField (
                     UpperSwizzle,
                     NewSwizzle[16],
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW16_START,
                     DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW16_LEN
                     );

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    DcttWriteReg64Func (DcttMain, ReutRegAddress, UpperSwizzle);

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    DcttWriteReg32Func (DcttMain, ReutRegAddress, LowerSwizzle);
  }

  return DCTT_SUCCESS;
}

INT32
CPGCFunctions_PrintSwizzle (
  DCTT_API  *DcttMain
  )
{
  UINT32          ReutRegAddress;
  UINT64          UpperSwizzle;
  UINT32          LowerSwizzle;
  UINT8           CurrentSwizzle[DCTT_MAX_NUM_SWIZZLE_LANES];
  UINT8           Channel;
  UINT8           Lane;

  for (Channel = 0; Channel < DcttMain->DcttConfigData.numberChannels; Channel++) {
    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    UpperSwizzle = DcttReadReg64Func (DcttMain, ReutRegAddress);

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    LowerSwizzle = DcttReadReg32Func (DcttMain, ReutRegAddress);

    CurrentSwizzle[0] = (UINT8) Helpers_GetField (
                                  LowerSwizzle,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW0_START,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW0_LEN
                                  );
    CurrentSwizzle[1] = (UINT8) Helpers_GetField (
                                  LowerSwizzle,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW1_START,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW1_LEN
                                  );
    CurrentSwizzle[2] = (UINT8) Helpers_GetField (
                                  LowerSwizzle,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW2_START,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW2_LEN
                                  );
    CurrentSwizzle[3] = (UINT8) Helpers_GetField (
                                  LowerSwizzle,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW3_START,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW3_LEN
                                  );
    CurrentSwizzle[4] = (UINT8) Helpers_GetField (
                                  LowerSwizzle,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW4_START,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW4_LEN
                                  );
    CurrentSwizzle[5] = (UINT8) Helpers_GetField (
                                  LowerSwizzle,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW5_START,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_F_ROW5_LEN
                                  );
    CurrentSwizzle[6] = (UINT8) Helpers_GetField (
                                  UpperSwizzle,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW6_START,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW6_LEN
                                  );
    CurrentSwizzle[7] = (UINT8) Helpers_GetField (
                                  UpperSwizzle,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW7_START,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW7_LEN
                                  );
    CurrentSwizzle[8] = (UINT8) Helpers_GetField (
                                  UpperSwizzle,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW8_START,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW8_LEN
                                  );
    CurrentSwizzle[9] = (UINT8) Helpers_GetField (
                                  UpperSwizzle,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW9_START,
                                  DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW9_LEN
                                  );
    CurrentSwizzle[10] = (UINT8) Helpers_GetField (
                                   UpperSwizzle,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW10_START,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW10_LEN
                                   );
    CurrentSwizzle[11] = (UINT8) Helpers_GetField (
                                   UpperSwizzle,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW11_START,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW11_LEN
                                   );
    CurrentSwizzle[12] = (UINT8) Helpers_GetField (
                                   UpperSwizzle,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW12_START,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW12_LEN
                                   );
    CurrentSwizzle[13] = (UINT8) Helpers_GetField (
                                   UpperSwizzle,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW13_START,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW13_LEN
                                   );
    CurrentSwizzle[14] = (UINT8) Helpers_GetField (
                                   UpperSwizzle,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW14_START,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW14_LEN
                                   );
    CurrentSwizzle[15] = (UINT8) Helpers_GetField (
                                   UpperSwizzle,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW15_START,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW15_LEN
                                   );
    CurrentSwizzle[16] = (UINT8) Helpers_GetField (
                                   UpperSwizzle,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW16_START,
                                   DCTT_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_F_ROW16_LEN
                                   );
    DcttLogVerbose (DcttMain, "Swizzle Ch %d: ", Channel);

    for (Lane = 0; Lane < DCTT_MAX_NUM_SWIZZLE_LANES; Lane++) {
      DcttLogVerbose (DcttMain, "%d ", CurrentSwizzle[Lane]);
    }

    DcttLogVerbose (DcttMain, "\n");
  }

  return DCTT_SUCCESS;
}
#endif

INT32
CPGCFunctions_RefreshControl (
  DCTT_API  *DcttMain,
  BOOLEAN   Enable
  )
{
  UINT32 McInitStateG;

  DcttLogDebug (DcttMain, "+++++++");
  DcttLogVerbose (DcttMain, "%s refresh\n", (Enable == TRUE) ? "Activate" : "Disabled");

  McInitStateG = DcttReadReg32Func (DcttMain, DCTT_MC_INIT_STATE_G);
  if (Enable == TRUE) {
    DcttEnterSelfRefreshFunc (DcttMain);
    McInitStateG = (UINT32) Helpers_SetField (
                              McInitStateG,
                              1,
                              DCTT_MC_INIT_STATE_G_F_REFRESH_ENABLE_START,
                              DCTT_MC_INIT_STATE_G_F_REFRESH_ENABLE_LEN
                              );
  } else {
    DcttExitSelfRefreshFunc (DcttMain);
    McInitStateG = (UINT32) Helpers_SetField (
                              McInitStateG,
                              0,
                              DCTT_MC_INIT_STATE_G_F_REFRESH_ENABLE_START,
                              DCTT_MC_INIT_STATE_G_F_REFRESH_ENABLE_LEN
                              );
  }
  DcttWriteReg32Func (DcttMain, DCTT_MC_INIT_STATE_G, McInitStateG);

  return DCTT_SUCCESS;
}

INT32
CPGCFunctions_PreInit (
  DCTT_API  *DcttMain
  )
{
  UINT64              SeqConfigRegVal;
  UINT32              ReutRegAddress;
  DCTT_CONFIG_PARAMS  *DcttConfig;
  UINT8               Channel;

  DcttConfig = &DcttMain->DcttConfigData;
  DcttLogDebug (DcttMain, "+++++++Pre Init\n");
  DcttLogDebug (DcttMain, "MRC Channel mask: %d\n", DcttSysGetPresentChannelBitMaskFunc (DcttMain, 0));

  for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
    SeqConfigRegVal = 0;

    SeqConfigRegVal = Helpers_SetField (
                        SeqConfigRegVal,
                        DcttConfig->startTestDelay,
                        DCTT_REUT_CH_SEQ_CFG_F_START_TEST_DELAY_START,
                        DCTT_REUT_CH_SEQ_CFG_F_START_TEST_DELAY_LEN);

    if (!DCTT_ChannelExists (DcttMain, 0, Channel)) {
      //DIsabling the global control in the Channel that doesn't exists
      ReutRegAddress = DcttGetMcAddressFunc (DcttMain, DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
      SeqConfigRegVal |= (1ULL << DCTT_REUT_CH_SEQ_CFG_F_INITIALIZATION_MODE_START);
      SeqConfigRegVal |= (0ULL << DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START);
      SeqConfigRegVal |= (1ULL << DCTT_REUT_CH_SEQ_CFG_F_ADDR_UPDATE_RATE_MODE_START);
      SeqConfigRegVal |= (1ULL << DCTT_REUT_CH_SEQ_CFG_F_STOP_BASE_SEQUENCE_WRAP_TRIGGER_START); //Stop base sequence on wrap trigger
#ifndef DISABLE_DUMMY_READS
      if (DcttConfig->enableDummyReads) {
        SeqConfigRegVal |= (1ULL << DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_START);
      }
#endif
      DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal);
      continue;
    }

    ReutRegAddress = DcttGetMcAddressFunc (DcttMain, DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
    SeqConfigRegVal |= (1ULL << DCTT_REUT_CH_SEQ_CFG_F_INITIALIZATION_MODE_START);
    SeqConfigRegVal |= (1ULL << DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START);
    SeqConfigRegVal |= (1ULL << DCTT_REUT_CH_SEQ_CFG_F_ADDR_UPDATE_RATE_MODE_START);
    SeqConfigRegVal |= (1ULL << DCTT_REUT_CH_SEQ_CFG_F_STOP_BASE_SEQUENCE_WRAP_TRIGGER_START); //Stop base sequence on wrap trigger
#ifndef DISABLE_DUMMY_READS
    if (DcttConfig->enableDummyReads) {
      SeqConfigRegVal |= (1ULL << DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_START);
    }
#endif
    DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal);
  }

  return DCTT_SUCCESS;
}

VOID
CPGCFunctions_PrintMemConfig (
  DCTT_API  *DcttMain
  )
{
  UINT8   Channel;
  UINT8   Rank;
  UINT8   DimmNumber;
  UINT32  RowSize;
  UINT32  ColumnSize;

  for (Rank = 0; Rank < DCTT_MAX_RANK_IN_CHANNEL; Rank++) {
    for (Channel = 0; Channel < DcttMain->DcttConfigData.numberChannels; Channel++) {
      if (!DcttSysRankInChannelExistsFunc (DcttMain, 0, Channel, Rank)) {
        continue;
      }

      //DimmNumber  = DcttSysInfo_GetDimmIDFromLogicalRank (DcttMain, 0, Channel, Rank);
      DimmNumber  = Rank / DCTT_MAX_RANK_IN_DIMM;
      RowSize     = DcttGetRowSizeFunc (DcttMain, 0, Channel, DimmNumber);
      ColumnSize  = DcttGetColumnSizeFunc (DcttMain, 0, Channel, DimmNumber);

      DcttLogVerbose (DcttMain, "Row size Rank %d in Channel %d: %d\n", Rank, Channel, RowSize);
      DcttLogVerbose (DcttMain, "Col size Rank %d in Channel %d: %d\n", Rank, Channel, ColumnSize);
      DcttLogVerbose (DcttMain, "Number rows %d\n", (Helpers_Log2 (RowSize) - 1));
      DcttLogVerbose (DcttMain, "DIMM %d\n", DimmNumber);
      DcttLogDebug (DcttMain, "DimmCapacity:  %d\n", DcttGetDimmSizeFunc (DcttMain, 0, Channel, DimmNumber));
    }
  }
}

static
INT32
_CPGCFunctions_SetBaseAddrIncCtrlForRank (
  DCTT_API  *DcttMain,
  UINT8     Channel,
  UINT8     Rank
  )
{
  DCTT_ORDER_NAMES    traverseOrder[4];
  DCTT_CONFIG_PARAMS  *DcttConfig;
  UINT32              ReutRegAddress;
  UINT64              BaseAddressIncCtl;
  UINT8               DimmNumber;
  UINT8               RowSize;
  UINT8               ColumnSize;
  UINT8               OrderIndex;
  UINT8               AccumBitsUpdateRate;

  DcttConfig          = &DcttMain->DcttConfigData;
  AccumBitsUpdateRate = 0;

  DcttLogDebug (DcttMain, "----Setting BaseAddrIncCtrl for Rank %d in Channel %d\n",Rank, Channel);
  ReutRegAddress = DcttGetMcAddressFunc (
                     DcttMain,
                     DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL,
                     0,
                     Channel,
                     DCTT_BYTE_CTL_NA
                     );

  BaseAddressIncCtl = DcttReadReg64Func (DcttMain, ReutRegAddress);
  //DimmNumber        = DcttSysInfo_GetDimmIDFromLogicalRank (DcttMain, 0, Channel, Rank);
  DimmNumber        = Rank / DCTT_MAX_RANK_IN_DIMM;
  RowSize           = Helpers_Log2 ((DcttGetRowSizeFunc (DcttMain, 0, Channel, DimmNumber)));
  RowSize           = RowSize - 1;
  ColumnSize        = Helpers_Log2 ((DcttGetColumnSizeFunc (DcttMain, 0, Channel, DimmNumber) - 1));
  ColumnSize        = ColumnSize - CPGC_NUMBER_BITS_CACHELINE;

  DcttLogDebug (DcttMain, "Number bits row: %d\n", RowSize);
  DcttLogDebug (DcttMain, "Number bits column: %d\n", ColumnSize);

  // TODO: Review Note
  //This next part is mainly for the workaround for early wrap and no negative carries
  traverseOrder[0] = DcttConfig->firstOrder;
  traverseOrder[1] = DcttConfig->secondOrder;
  traverseOrder[2] = DcttConfig->thirdOrder;
  traverseOrder[3] = DcttConfig->fourthOrder;
  //
  // Only traversing the 3 lower orders because the higher one is always Rank.
  // TODO: Evaluate possibility of moving config checks prior to point run.
  //
  DcttError_Assert (DcttMain, DcttConfig->fourthOrder == DcttOrderRank, "Fourth traversing order has to be Rank\n");
  for (OrderIndex = 0; OrderIndex < 3; OrderIndex++) {
    switch (traverseOrder[OrderIndex]) {
      case DcttOrderColumn:
        if (OrderIndex > 0) {
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                AccumBitsUpdateRate,
                                12,
                                5
                                );
        }
        AccumBitsUpdateRate = AccumBitsUpdateRate + ColumnSize;
        break;

      case DcttOrderRow:
        if (OrderIndex > 0) {
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                AccumBitsUpdateRate,
                                32,
                                4
                                );
        }
        AccumBitsUpdateRate = AccumBitsUpdateRate + RowSize;
        break;

      case DcttOrderBank:
        if (OrderIndex > 0) {
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                AccumBitsUpdateRate,
                                44,
                                5
                                );
          DcttError_Assert (
            DcttMain,
            AccumBitsUpdateRate <= CPGC_MAX_BANK_UPDATE_RATE,
            "Maximum number of bits for Bank update rate is 23"
            );
        }
        AccumBitsUpdateRate = AccumBitsUpdateRate + 3;
        break;

      case DcttOrderRank:
      default:
        DcttError_Assert (DcttMain, 1 == 0, "Unsupported memory traverse order.");
        break;
    }
  }

  ////X0 WA: Using a different work around when capturing all errors
  ////On this workaround I will ignore errors after wrap.
  ////TODO: Refactor. This can be merged with the previous code
  ////after testing is complete
  if (DcttConfig->dontStopErrors) {
    BaseAddressIncCtl = Helpers_SetField (
                          BaseAddressIncCtl,
                          0,
                          DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_UPDATE_RATE_START,
                          DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_UPDATE_RATE_LEN
                          );
    BaseAddressIncCtl = Helpers_SetField (
                          BaseAddressIncCtl,
                          0,
                          DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_START,
                          DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_LEN
                          );
    BaseAddressIncCtl = Helpers_SetField (
                          BaseAddressIncCtl,
                          0,
                          DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_UPDATE_RATE_START,
                          DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_UPDATE_RATE_LEN
                          );
  }

  DcttWriteReg64Func (DcttMain, ReutRegAddress, BaseAddressIncCtl);

  return DCTT_SUCCESS;
}

/*
  Initialize memory traversing order.

  @param[] -

  @retval
*/
// TODO: add address swizzle if desired
INT32
CPGCFunctions_InitAddress (
  DCTT_API  *DcttMain
  )
{
  DCTT_ORDER_NAMES    UniqueCheck[DcttOrderMax] = {0, 0, 0, 0};
  DCTT_ORDER_NAMES    traverseOrder[4];
  DCTT_CONFIG_PARAMS  *DcttConfig;
  UINT64              BaseAddressIncCtl;
  UINT32              BaseAddressOrder;
  UINT32              ReutRegAddress;
  UINT8               Channel;
  UINT8               i;
  UINT8               DimmNumber;
  UINT8               RowSize;
  UINT8               ColumnSize;
  UINT8               OrderIndex;
  UINT8               AccumBitsUpdateRate;

  DcttConfig = &DcttMain->DcttConfigData;

  DcttLogDebug (DcttMain, "+++++++Init Address\n");

  // TODO: Move check to before Point Test Run?
  //Checking that memory traversing order is correct.
  DcttError_Assert (DcttMain, DcttConfig->firstOrder < DcttOrderMax, "Bad Mem traversing order");
  DcttError_Assert (DcttMain, DcttConfig->secondOrder < DcttOrderMax, "Bad Mem traversing order");
  DcttError_Assert (DcttMain, DcttConfig->thirdOrder < DcttOrderMax, "Bad Mem traversing order");
  DcttError_Assert (DcttMain, DcttConfig->fourthOrder < DcttOrderMax, "Bad Mem traversing order");

  UniqueCheck[DcttConfig->firstOrder]   += 1;
  UniqueCheck[DcttConfig->secondOrder]  += 1;
  UniqueCheck[DcttConfig->thirdOrder]   += 1;
  UniqueCheck[DcttConfig->fourthOrder]  += 1;

  for (i = 0; i < DcttOrderMax; i++) {
    DcttError_Assert (DcttMain, UniqueCheck[i] == 1, "Order elements (Row, Col, Bank, Rank) are not unique.");
  }
  // TODO: End Assert Check

  for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
    if (!DCTT_ChannelExists (DcttMain, 0, Channel)) {
      DcttLogDebug (DcttMain, "Skipping Channel\n", Channel);
      continue;
    }

    BaseAddressOrder = 0;
    BaseAddressIncCtl = 0;

    //Setting the memory traversing order
    BaseAddressOrder |= (0 << (DcttConfig->firstOrder * 2));
    BaseAddressOrder |= (1 << (DcttConfig->secondOrder * 2));
    BaseAddressOrder |= (2 << (DcttConfig->thirdOrder * 2));
    BaseAddressOrder |= (3 << (DcttConfig->fourthOrder * 2));
    BaseAddressOrder |= (1 << DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_RANK_BASE_WRAP_CARRY_ENABLE_START);
    BaseAddressOrder |= (1 << DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_BANK_BASE_WRAP_CARRY_ENABLE_START);
    BaseAddressOrder |= (1 << DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_ROW_BASE_WRAP_CARRY_ENABLE_START);
    BaseAddressOrder |= (1 << DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_COL_BASE_WRAP_CARRY_ENABLE_START);

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    DcttWriteReg32Func (DcttMain, ReutRegAddress, BaseAddressOrder);

    switch (DcttConfig->firstOrder) {
      case DcttOrderColumn:
        BaseAddressIncCtl = Helpers_SetField (
                              BaseAddressIncCtl,
                              1,
                              DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                              DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN
                              );
        break;

      case DcttOrderRow:
        BaseAddressIncCtl = Helpers_SetField (
                              BaseAddressIncCtl,
                              1,
                              DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                              DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN
                              );
        break;

      case DcttOrderBank:
        BaseAddressIncCtl = Helpers_SetField (
                              BaseAddressIncCtl,
                              1,
                              DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_ADDRESS_INCREMENT_START,
                              DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_ADDRESS_INCREMENT_LEN
                              );
        break;

      case DcttOrderRank:
        BaseAddressIncCtl = Helpers_SetField (
                              BaseAddressIncCtl,
                              1,
                              DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_RANK_ADDRESS_INCREMENT_START,
                              DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_RANK_ADDRESS_INCREMENT_LEN
                              );
        break;

      default:
        DcttError_Assert (DcttMain, 1 == 0, "Unknown first order traverser selected.");
    }

    // TODO: Review W/A
    ////////////Workaround for early wrap on Bank///////////
    if (DCTT_RankInChannelExists (DcttMain, 0, 0, Channel)) {
      DcttLogDebug (DcttMain, "Using Rank 0 in Channel for row size\n", Channel);
      //DimmNumber = DcttSysInfo_GetDimmIDFromLogicalRank (DcttMain, 0, Channel, 0);
      DimmNumber = 0 / DCTT_MAX_RANK_IN_DIMM;
    } else if (DCTT_RankInChannelExists (DcttMain, 0, 2, Channel)) {
      DcttLogDebug (DcttMain, "Using Rank 2 in Channel for row size\n", Channel);
      //DimmNumber = DcttSysInfo_GetDimmIDFromLogicalRank (DcttMain, 0, Channel, 2);
      DimmNumber = 2 / DCTT_MAX_RANK_IN_DIMM;
    } else if (DCTT_RankInChannelExists (DcttMain, 0, 1, Channel)) { // TODO: Not sure if possible to reach
      DcttLogDebug (DcttMain, "Using Rank 1 in Channel for row size\n", Channel);
      //DimmNumber = DcttSysInfo_GetDimmIDFromLogicalRank (DcttMain, 0, Channel, 1);
      DimmNumber = 1 / DCTT_MAX_RANK_IN_DIMM;
    } else if (DCTT_RankInChannelExists (DcttMain, 0, 3, Channel)) { // TODO: Not sure if possible to reach
      DcttLogDebug (DcttMain, "Using Rank 3 in Channel for row size\n", Channel);
      //DimmNumber = DcttSysInfo_GetDimmIDFromLogicalRank (DcttMain, 0, Channel, 3);
      DimmNumber = 3 / DCTT_MAX_RANK_IN_DIMM;
    } else {
      DimmNumber = 0;
      DcttOutputPrint (DcttMain, "Couldn't find any Rank on Channel %d\n", Channel);
    }
    RowSize = Helpers_Log2 ((DcttGetRowSizeFunc (DcttMain, 0, Channel, DimmNumber)));
    RowSize = RowSize - 1;
    DcttLogDebug (DcttMain, "Number ranks: %d\n", (DcttGetNumberOfRanksFunc (DcttMain, 0, Channel, DimmNumber)));
    DcttLogDebug (DcttMain, "Number bits row: %d\n", RowSize);

    ColumnSize = Helpers_Log2 ((DcttGetColumnSizeFunc (DcttMain, 0, Channel, DimmNumber) - 1));
    ColumnSize = ColumnSize - CPGC_NUMBER_BITS_CACHELINE;

    DcttLogDebug (DcttMain, "Number bits column: %d\n", ColumnSize);

    //This next part is mainly for the workaround for early wrap and no negative carries
    traverseOrder[0] = DcttConfig->firstOrder;
    traverseOrder[1] = DcttConfig->secondOrder;
    traverseOrder[2] = DcttConfig->thirdOrder;
    traverseOrder[3] = DcttConfig->fourthOrder;
    //
    //Only traversing the 3 lower orders because the higher one is always Rank.
    //
    AccumBitsUpdateRate = 0;
    // TODO: Check merging this with the code found later (This call might be unnecessary because it is reset later)
    for (OrderIndex = 0; OrderIndex < 3; OrderIndex++) {
      switch (traverseOrder[OrderIndex]) {
        case DcttOrderColumn:
          if (OrderIndex > 0) {
            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  AccumBitsUpdateRate,
                                  12,
                                  5
                                  );
          }

          AccumBitsUpdateRate = AccumBitsUpdateRate + ColumnSize;
          break;

        case DcttOrderRow:
          if (OrderIndex > 0) {
            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  AccumBitsUpdateRate,
                                  32,
                                  4
                                  );
          }

          AccumBitsUpdateRate = AccumBitsUpdateRate + RowSize;
          break;
        case DcttOrderBank:
          if (OrderIndex > 0) {
            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  AccumBitsUpdateRate,
                                  44,
                                  5
                                  );
            DcttError_Assert (DcttMain, AccumBitsUpdateRate <= CPGC_MAX_BANK_UPDATE_RATE, "Maximum number of bits for Bank update rate is 23");
          }

          AccumBitsUpdateRate = AccumBitsUpdateRate + 3;
          break;

        case DcttOrderRank:
        default:
          DcttError_Assert (DcttMain, 1 == 0, "Unsupported memory traverse order.");
          break;
      }
    }

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    DcttWriteReg64Func (DcttMain, ReutRegAddress, BaseAddressIncCtl);
  }

  return DCTT_SUCCESS;
}

/*
  Initialize WDB with a solid pattern of Base

  @param[] -

  @retval
*/
INT32
CPGCFunctions_SetBackgroundBase (
  DCTT_API              *DcttMain,
  DCTT_BACKGROUND_BASE  Base
  )
{
  char*   Background;
  UINT8   Pattern[4] = {0x0, 0xFF, 0x55, 0xAA};
  UINT8   PatternMaskZero[1] = {0};
  UINT8   PatternMaskOne[1] = {1};
  UINT8   PatternMaskFive[2] = {0, 1};
  UINT8   PatternMaskA[2] = {1, 0};
  UINT8   PatternMaskCustom[64];
  UINT8   Spread;
  UINT8*  PatternMaskPtr;
  UINT8   DqIndex;
  UINT64  CustomPattern;

  //
  //Writing a solid pattern of 0s to WDB
  //WriteWDBFixedPattern is a function defined on the "HSWDDR IO
  //Initialization and training", but basically what I am doing here
  //is writing either 0's, 1's, 5's, or A's to one cacheline in the WDB
  //
  Background = getWDBPattern (Base);
  // TODO: Optimize for only 1 functon call
  /*if (Base == DcttBackBaseZeros) {
    DcttMRCCommon_WriteWDBFixedPattern (DcttMain, 0, Pattern, PatternMaskZero, 1, 0);
  } else if (Base == DcttBackBaseOnes) {
    DcttMRCCommon_WriteWDBFixedPattern (DcttMain, 0, Pattern, PatternMaskOne, 1, 0);
  } else if (Base == DcttBackBaseFive) {
    DcttMRCCommon_WriteWDBFixedPattern (DcttMain, 0, Pattern, PatternMaskFive, 2, 0);
  } else if (Base == DcttBackBaseA) {
    DcttMRCCommon_WriteWDBFixedPattern (DcttMain, 0, Pattern, PatternMaskA, 2, 0);
  } else {
    DcttError_Assert (DcttMain, 1 == 0, "Unknown Background %d.", Base);
  }*/
  switch (Base) {
    case DcttBackBaseZeros:
      PatternMaskPtr = PatternMaskZero;
      Spread = 1;
      break;

    case DcttBackBaseOnes:
      PatternMaskPtr = PatternMaskOne;
      Spread = 1;
      break;

    case DcttBackBaseFive:
      PatternMaskPtr = PatternMaskFive;
      Spread = 2;
      break;

    case DcttBackBaseA:
      PatternMaskPtr = PatternMaskA;
      Spread = 2;
      break;

    case DcttBackBaseCustom:
      CustomPattern = DcttMain->DcttConfigData.CustomPattern;
      for (DqIndex = 0; DqIndex < 64; DqIndex++) {
        PatternMaskCustom[DqIndex] = CustomPattern & 1;
        CustomPattern = DcttRight64Shift (DcttMain, CustomPattern, 1);
      }
      PatternMaskPtr = PatternMaskCustom;
      Spread = 64;
      break;

    default:
      DcttError_Assert (DcttMain, 1 == 0, "Unknown Background %d.", Base);
      return DCTT_FAIL;
  }

  DcttLogDebug (
    DcttMain,
    "Calling WDBFixedPattern. Pattern[4] = {0x0, 0xFF 0x55, 0xAA}. Spread = %d. Start = 0.\n",
    Spread
    );
  DcttSysWriteWdbFixedPatFunc (DcttMain, 0, Pattern, PatternMaskPtr, Spread, 0);

  if (Base != DcttBackBaseCustom) {
    DcttOutputPrint (DcttMain, "Using a pattern of %c's\n", Background[0]);
  } else {
    DcttOutputPrint (DcttMain, "Using a user defined pattern: 0x%xl\n", DcttMain->DcttConfigData.CustomPattern);
  }

  return DCTT_SUCCESS;
}

/*
  // TODO: Description

  @param[] -

  @retval
*/
INT32
CPGCFunctions_InitData (
  DCTT_API  *DcttMain
  )
{
  DCTT_CONFIG_PARAMS  *DcttConfig;
  UINT32              ReutRegAddress;
  UINT32              patWDBClCtrlRegVal;
  UINT32              errWDBCaptureRegVal;
  UINT8               Channel;

  DcttConfig = &DcttMain->DcttConfigData;
  DcttLogDebug (DcttMain, "+++++++Init Data\n");

  for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
    patWDBClCtrlRegVal  = 0;
    errWDBCaptureRegVal = 0;

    if (!DCTT_ChannelExists (DcttMain, 0, Channel)) {
      DcttLogDebug (DcttMain, "Skipping Channel\n", Channel);
      continue;
    }
    //
    // We will only use one WDB entry for our test patterns
    //
    patWDBClCtrlRegVal |= 0 << DCTT_REUT_CH_PAT_WDB_CL_CTRL_F_WDB_INCREMENT_RATE_START;
    patWDBClCtrlRegVal |= 1 << DCTT_REUT_CH_PAT_WDB_CL_CTRL_F_WDB_INCREMENT_SCALE_START;
    patWDBClCtrlRegVal |= 0 << DCTT_REUT_CH_PAT_WDB_CL_CTRL_F_WDB_START_POINTER_START;
    patWDBClCtrlRegVal |= 0 << DCTT_REUT_CH_PAT_WDB_CL_CTRL_F_WDB_END_POINTER_START;

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_PAT_WDB_CL_CTRL,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    DcttWriteReg32Func (DcttMain, ReutRegAddress, patWDBClCtrlRegVal);

    //
    // Setting the Error Capture for error reporting
    //
    errWDBCaptureRegVal |= 1  << DCTT_REUT_CH_WDB_CAPTURE_CTL_F_ENABLE_WDB_CAPTURE_START;
    errWDBCaptureRegVal |= 63 << DCTT_REUT_CH_WDB_CAPTURE_CTL_F_ENDING_POINTER_START;
    errWDBCaptureRegVal |= 63 << DCTT_REUT_CH_WDB_CAPTURE_CTL_F_STARTING_POINTER_START;

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_WDB_CAPTURE_CTL,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    DcttWriteReg32Func (DcttMain, ReutRegAddress, errWDBCaptureRegVal);
  }

  CPGCFunctions_SetBackgroundBase (DcttMain, DcttConfig->backgroundBase);

  // TODO: Add the Address inversion control here?
  return DCTT_SUCCESS;
}

/*
  Initializing registers needed to run a test
*/
INT32
CPGCFunctions_InitMisc (
  DCTT_API  *DcttMain
  )
{
  UINT32 ReutRegAddress;
  UINT32 globalCtrlRegVal = 0;

  DcttLogDebug (DcttMain, "+++++++Init Misc\n");

  globalCtrlRegVal |= 1 << DCTT_REUT_GLOBAL_CTRL_F_STOP_TEST_START;
  globalCtrlRegVal |= 1 << DCTT_REUT_GLOBAL_CTRL_F_CLEAR_ERR_START;

  ReutRegAddress = DcttGetMcAddressFunc (
                     DcttMain,
                     DCTT_REUT_GLOBAL_CTRL,
                     0,
                     DCTT_CHANNEL_CTL_NA,
                     DCTT_BYTE_CTL_NA
                     );
  DcttWriteReg32Func (DcttMain, ReutRegAddress, globalCtrlRegVal);

  return DCTT_SUCCESS;
}

INT32
CPGCFunctions_ChangeDirection (
  DCTT_API    *DcttMain,
  MemTravDir  NewDirection
  )
{
  DCTT_ORDER_NAMES    WrapOrder;
  DCTT_CONFIG_PARAMS  *DcttConfig;
  UINT64              SequenceBaseAddrStart;
  UINT64              SequenceBaseAddrWrap;
  UINT64              BaseAddressIncCtl;
  UINT32              BaseAddressOrder;
  UINT32              ReutRegAddress;
  UINT32              RowSize;
  UINT8               Channel;
  UINT8               DimmNumber;

  DcttConfig = &DcttMain->DcttConfigData;
  // TODO: check bottom and start address values in config object

  for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
    SequenceBaseAddrStart = 0;
    SequenceBaseAddrWrap = 0;

    // TODO: Remove - X0 WA: Using a different workaround when catching more than the first error.
    if (DcttConfig->OptimizeSecondOrderRun) {
      DcttError_Assert (DcttMain, DcttConfig->fourthOrder == DcttOrderRank, "Fourth memory traversing order needs to be Rank.\n");
      DcttError_Assert (DcttMain, DcttConfig->thirdOrder == DcttOrderBank, "When running test per Bank third order needs to be Bank\n");
      WrapOrder = DcttOrderInvalid;
    } else if (DcttConfig->runTestOnSecondOrder) {
      DcttError_Assert (DcttMain, DcttConfig->fourthOrder == DcttOrderRank, "Fourth memory traversing order needs to be Rank.\n");
      DcttError_Assert (DcttMain, DcttConfig->thirdOrder == DcttOrderBank, "When running test per Bank third order needs to be Bank\n");
      WrapOrder = DcttConfig->firstOrder;
    } else if (DcttConfig->dontStopErrors) {
      WrapOrder = DcttConfig->fourthOrder;
      DcttError_Assert (DcttMain, DcttConfig->fourthOrder == DcttOrderRank, "Fourth memory traversing order needs to be Rank.\n");
      if (DcttConfig->runTestPerBank) {
        DcttError_Assert (DcttMain, DcttConfig->thirdOrder == DcttOrderBank, "When running test per Bank third order needs to be Bank\n");
      }
    } else if (DcttConfig->runTestPerBank) {
      DcttError_Assert (DcttMain, DcttConfig->thirdOrder == DcttOrderBank, "When running test per Bank third order needs to be Bank\n");
      WrapOrder = DcttConfig->secondOrder;
    } else {
      WrapOrder = DcttConfig->thirdOrder;
    }

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    BaseAddressIncCtl = DcttReadReg64Func (DcttMain, ReutRegAddress);

    if (!DCTT_ChannelExists (DcttMain, 0, Channel)) {
      DcttLogDebug (DcttMain, "Skipping Channel\n", Channel);
      continue;
    }
    // TODO: Refactor
    if (DCTT_RankInChannelExists (DcttMain, 0, 0, Channel)) {
      DimmNumber  = 0 / DCTT_MAX_RANK_IN_DIMM;
      RowSize     = DcttGetRowSizeFunc (DcttMain, 0, Channel, DimmNumber);

      DcttConfig->topAddress[Channel].Row = RowSize - 1;
      DcttLogDebug (DcttMain, "Row size Rank %d in Channel %d: %d\n",0 ,Channel, RowSize);
      DcttLogDebug (DcttMain, "DIMM %d\n",DimmNumber);
      DcttLogDebug (DcttMain, "MRC row size: %d\n", RowSize);
      DcttLogDebug (DcttMain, "MRC DimmCapacity:  %d\n", DcttGetDimmSizeFunc (DcttMain, 0, Channel, DimmNumber));
    } else if (DCTT_RankInChannelExists (DcttMain, 0, 2, Channel)) {
      DimmNumber  = 2 / DCTT_MAX_RANK_IN_DIMM;
      RowSize     = DcttGetRowSizeFunc (DcttMain, 0, Channel, DimmNumber);

      DcttConfig->topAddress[Channel].Row = RowSize - 1;
      DcttLogDebug (DcttMain, "Row size Rank %d in Channel %d: %d\n", 2 ,Channel, RowSize);
      DcttLogDebug (DcttMain, "DIMM %d\n",DimmNumber);
      DcttLogDebug (DcttMain, "MRC row size: %d\n", RowSize);
      DcttLogDebug (DcttMain, "MRC DimmCapacity:  %d\n", DcttGetDimmSizeFunc (DcttMain, 0, Channel, DimmNumber));
    } else if (DCTT_RankInChannelExists (DcttMain, 0, 1, Channel)) {
      DimmNumber  = 1 / DCTT_MAX_RANK_IN_DIMM;
      RowSize     = DcttGetRowSizeFunc (DcttMain, 0, Channel, DimmNumber);

      DcttConfig->topAddress[Channel].Row = RowSize - 1;
      DcttLogDebug (DcttMain, "Row size Rank %d in Channel %d: %d\n", 1, Channel, RowSize);
      DcttLogDebug (DcttMain, "DIMM %d\n",DimmNumber);
      DcttLogDebug (DcttMain, "MRC row size: %d\n", RowSize);
      DcttLogDebug (DcttMain, "MRC DimmCapacity:  %d\n", DcttGetDimmSizeFunc (DcttMain, 0, Channel, DimmNumber));
    } else if (DCTT_RankInChannelExists (DcttMain, 0, 3, Channel)) {
      DimmNumber  = 3 / DCTT_MAX_RANK_IN_DIMM;
      RowSize     = DcttGetRowSizeFunc (DcttMain, 0, Channel, DimmNumber);

      DcttConfig->topAddress[Channel].Row = RowSize - 1;
      DcttLogDebug (DcttMain, "Row size Rank %d in Channel %d: %d\n", 3, Channel, RowSize);
      DcttLogDebug (DcttMain, "DIMM %d\n",DimmNumber);
      DcttLogDebug (DcttMain, "MRC row size: %d\n", RowSize);
      DcttLogDebug (DcttMain, "MRC DimmCapacity:  %d\n", DcttGetDimmSizeFunc (DcttMain, 0, Channel, DimmNumber));
    } else {
      DcttOutputPrint (DcttMain,"Couldn't find any Rank on Channel %d\n", Channel);
    }

    //There are no start/stop ranks because we are going to start/stop the test on each one of the ranks
    if (NewDirection == UP) {
      DcttConfig->DEBUGtestDirection = 1;
      //Going up, enable wrap triggers, carries
      ReutRegAddress = DcttGetMcAddressFunc (
                         DcttMain,
                         DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL,
                         0,
                         Channel,
                         DCTT_BYTE_CTL_NA
                         );
      BaseAddressOrder = DcttReadReg32Func (DcttMain, ReutRegAddress);

      // TODO: Optimize so there is only one set of SetFieldValue functions
      if (DcttConfig->OptimizeSecondOrderRun) {
        BaseAddressOrder = (UINT32) Helpers_SetField (
                                      BaseAddressOrder,
                                      0,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_RANK_BASE_WRAP_CARRY_ENABLE_START,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_RANK_BASE_WRAP_CARRY_ENABLE_LEN
                                      );
        BaseAddressOrder = (UINT32) Helpers_SetField (
                                      BaseAddressOrder,
                                      0,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_BANK_BASE_WRAP_CARRY_ENABLE_START,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_BANK_BASE_WRAP_CARRY_ENABLE_LEN
                                      );
        BaseAddressOrder = (UINT32) Helpers_SetField (
                                      BaseAddressOrder,
                                      0,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_ROW_BASE_WRAP_CARRY_ENABLE_START,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_ROW_BASE_WRAP_CARRY_ENABLE_LEN
                                      );
        BaseAddressOrder = (UINT32) Helpers_SetField (
                                      BaseAddressOrder,
                                      0,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_COL_BASE_WRAP_CARRY_ENABLE_START,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_COL_BASE_WRAP_CARRY_ENABLE_LEN
                                      );
      } else {
        BaseAddressOrder = (UINT32) Helpers_SetField (
                                      BaseAddressOrder,
                                      1,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_RANK_BASE_WRAP_CARRY_ENABLE_START,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_RANK_BASE_WRAP_CARRY_ENABLE_LEN
                                      );
        BaseAddressOrder = (UINT32) Helpers_SetField (
                                      BaseAddressOrder,
                                      1,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_BANK_BASE_WRAP_CARRY_ENABLE_START,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_BANK_BASE_WRAP_CARRY_ENABLE_LEN
                                      );
        BaseAddressOrder = (UINT32) Helpers_SetField (
                                      BaseAddressOrder,
                                      1,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_ROW_BASE_WRAP_CARRY_ENABLE_START,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_ROW_BASE_WRAP_CARRY_ENABLE_LEN
                                      );
        BaseAddressOrder = (UINT32) Helpers_SetField (
                                      BaseAddressOrder,
                                      1,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_COL_BASE_WRAP_CARRY_ENABLE_START,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_COL_BASE_WRAP_CARRY_ENABLE_LEN
                                      );
      }

      switch (WrapOrder) {
        case DcttOrderColumn:
          BaseAddressOrder = (UINT32) Helpers_SetField (
                                        BaseAddressOrder,
                                        1,
                                        24,
                                        1
                                        );
          break;

        case DcttOrderRow:
          BaseAddressOrder = (UINT32) Helpers_SetField (
                                        BaseAddressOrder,
                                        1,
                                        25,
                                        1
                                        );
          break;

        case DcttOrderBank:
          BaseAddressOrder = (UINT32) Helpers_SetField (
                                        BaseAddressOrder,
                                        1,
                                        26,
                                        1
                                        );
          break;

        case DcttOrderRank:
          BaseAddressOrder = (UINT32) Helpers_SetField (
                                        BaseAddressOrder,
                                        1,
                                        DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_RANK_BASE_WRAP_TRIGGER_ENABLE_START,
                                        DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_RANK_BASE_WRAP_TRIGGER_ENABLE_LEN
                                        );
          break;

        case DcttOrderInvalid:
          //We are not going to use wraps on this case
          break;

        default:
          DcttError_Assert (DcttMain, 1 == 0, "Unsupported memory traverse order.");
          break;
      }

      DcttWriteReg32Func (DcttMain, ReutRegAddress, BaseAddressOrder);

      SequenceBaseAddrStart = Helpers_SetField (
                                SequenceBaseAddrStart,
                                (DcttConfig->bottomAddress[Channel]).Col,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN
                                );
      SequenceBaseAddrStart = Helpers_SetField (
                                SequenceBaseAddrStart,
                                (DcttConfig->bottomAddress[Channel]).Row,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN
                                );
      SequenceBaseAddrStart = Helpers_SetField (
                                SequenceBaseAddrStart,
                                (DcttConfig->bottomAddress[Channel]).Bank,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_LEN
                                );

      SequenceBaseAddrWrap = Helpers_SetField (
                               SequenceBaseAddrWrap,
                               (DcttConfig->topAddress[Channel]).Col,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_START,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_LEN
                               );
      SequenceBaseAddrWrap = Helpers_SetField (
                               SequenceBaseAddrWrap,
                               (DcttConfig->topAddress[Channel]).Row,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_START,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_LEN
                               );
      SequenceBaseAddrWrap = Helpers_SetField (
                               SequenceBaseAddrWrap,
                               (DcttConfig->topAddress[Channel]).Bank,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_BANK_ADDRESS_START,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_BANK_ADDRESS_LEN
                               );

      ////X0 WA: Using a different workaround when capturing all errors
      if (DcttConfig->dontStopErrors) {
        SequenceBaseAddrWrap = Helpers_SetField (
                                 SequenceBaseAddrWrap,
                                 1,
                                 DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_RANK_ADDRESS_START,
                                 DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_RANK_ADDRESS_LEN
                                 );
      }

      switch (DcttConfig->firstOrder) {
        case DcttOrderColumn:
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN
                                );
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                0,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN
                                );
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                0,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_ADDRESS_INCREMENT_LEN
                                );
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                0, //1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_RANK_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_RANK_ADDRESS_INCREMENT_LEN
                                );
          break;

        case DcttOrderRow:
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN
                                );
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                0,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN
                                );
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                0,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_ADDRESS_INCREMENT_LEN
                                );
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                0, //1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_RANK_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_RANK_ADDRESS_INCREMENT_LEN
                                );
          break;

        case DcttOrderBank:
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_ADDRESS_INCREMENT_LEN
                                );
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                0,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN
                                );
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                0,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN
                                );
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                0, //1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_RANK_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_RANK_ADDRESS_INCREMENT_LEN
                                );
          break;

        case DcttOrderRank:
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_RANK_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_RANK_ADDRESS_INCREMENT_LEN
                                );
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                0,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN
                                );
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                0,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN
                                );
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                0, //1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_ADDRESS_INCREMENT_LEN
                                );
          break;

        default:
          DcttError_Assert (DcttMain, 1 == 0, "Unknown first order traverser selected.");
      }
      //Setting Diagonal
      if (DcttConfig->traverseDiagonal == TRUE) {
        if ((DcttConfig->firstOrder == DcttOrderColumn && DcttConfig->secondOrder == DcttOrderRow) ||
            (DcttConfig->firstOrder == DcttOrderRow && DcttConfig->secondOrder == DcttOrderColumn)) {
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN
                                );
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN
                                );
        } else {
          DcttLogVerbose (DcttMain, "Only Diagonal supported is DcttOrderColumn-DcttOrderRow");
        }
      }
      ReutRegAddress = DcttGetMcAddressFunc (
                         DcttMain,
                         DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL,
                         0,
                         Channel,
                         DCTT_BYTE_CTL_NA
                         );
      DcttWriteReg64Func (DcttMain, ReutRegAddress, BaseAddressIncCtl);
    } else if (NewDirection == DOWN) {
      DcttConfig->DEBUGtestDirection = 2;
      //Check if stop on error is enabled
      DcttError_Assert (DcttMain, !(DcttConfig->dontStopErrors), "Currently Stop on error is not supported if the test direction is DOWN");
      //Going down, disable wrap triggers, carries
      ReutRegAddress = DcttGetMcAddressFunc (
                         DcttMain,
                         DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL,
                         0,
                         Channel,
                         DCTT_BYTE_CTL_NA
                         );
      BaseAddressOrder = DcttReadReg32Func (DcttMain, ReutRegAddress);

      BaseAddressOrder = (UINT32) Helpers_SetField (
                                    BaseAddressOrder,
                                    0,
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_RANK_BASE_WRAP_CARRY_ENABLE_START,
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_RANK_BASE_WRAP_CARRY_ENABLE_LEN
                                    );
      BaseAddressOrder = (UINT32) Helpers_SetField (
                                    BaseAddressOrder,
                                    0,
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_BANK_BASE_WRAP_CARRY_ENABLE_START,
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_BANK_BASE_WRAP_CARRY_ENABLE_LEN
                                    );
      BaseAddressOrder = (UINT32) Helpers_SetField (
                                    BaseAddressOrder,
                                    0,
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_ROW_BASE_WRAP_CARRY_ENABLE_START,
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_ROW_BASE_WRAP_CARRY_ENABLE_LEN
                                    );
      BaseAddressOrder = (UINT32) Helpers_SetField (
                                    BaseAddressOrder,
                                    0,
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_COL_BASE_WRAP_CARRY_ENABLE_START,
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_COL_BASE_WRAP_CARRY_ENABLE_LEN
                                    );

      switch (WrapOrder) {
        case DcttOrderColumn:
          BaseAddressOrder = (UINT32) Helpers_SetField (
                                        BaseAddressOrder,
                                        1,
                                        24,
                                        1
                                        );
          break;
        case DcttOrderRow:
          BaseAddressOrder = (UINT32) Helpers_SetField (
                                        BaseAddressOrder,
                                        1,
                                        25,
                                        1
                                        );
          break;
        case DcttOrderBank:
          BaseAddressOrder = (UINT32) Helpers_SetField (
                                        BaseAddressOrder,
                                        1,
                                        26,
                                        1
                                        );
          break;
        case DcttOrderRank:
          BaseAddressOrder = (UINT32) Helpers_SetField (
                                        BaseAddressOrder,
                                        1,
                                        DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_RANK_BASE_WRAP_TRIGGER_ENABLE_START,
                                        DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_RANK_BASE_WRAP_TRIGGER_ENABLE_LEN
                                        );
          break;
        case DcttOrderInvalid:
          //We are not going to use wraps on this case
          break;
        default:
          DcttError_Assert (DcttMain, 1 == 0, "Unsupported memory traverse order.");
          break;
      }

      DcttWriteReg32Func (DcttMain, ReutRegAddress, BaseAddressOrder);

      SequenceBaseAddrStart = Helpers_SetField (
                                SequenceBaseAddrStart,
                                (DcttConfig->topAddress[Channel]).Col,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN
                                );

      SequenceBaseAddrStart = Helpers_SetField (
                                SequenceBaseAddrStart,
                                (DcttConfig->topAddress[Channel]).Row,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN
                                );
      SequenceBaseAddrStart = Helpers_SetField (
                                SequenceBaseAddrStart,
                                (DcttConfig->topAddress[Channel]).Bank,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_LEN
                                );
      SequenceBaseAddrWrap = Helpers_SetField (
                               SequenceBaseAddrWrap,
                               (DcttConfig->bottomAddress[Channel]).Col,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_START,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_LEN
                               );
      SequenceBaseAddrWrap = Helpers_SetField (
                               SequenceBaseAddrWrap,
                               (DcttConfig->bottomAddress[Channel]).Row,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_START,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_LEN
                               );
      SequenceBaseAddrWrap = Helpers_SetField (
                               SequenceBaseAddrWrap,
                               (DcttConfig->bottomAddress[Channel]).Bank,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_BANK_ADDRESS_START,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_BANK_ADDRESS_LEN
                               );

      BaseAddressIncCtl = Helpers_SetField (
                            BaseAddressIncCtl,
                            0,
                            DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_RANK_ADDRESS_INCREMENT_START,
                            DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_RANK_ADDRESS_INCREMENT_LEN
                            );
      BaseAddressIncCtl = Helpers_SetField (
                            BaseAddressIncCtl,
                            (UINT32) -1,
                            DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                            DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN
                            );
      BaseAddressIncCtl = Helpers_SetField (
                            BaseAddressIncCtl,
                            (UINT32) -1,
                            DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                            DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN
                            );
      BaseAddressIncCtl = Helpers_SetField (
                            BaseAddressIncCtl,
                            (UINT32) -1,
                            DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_ADDRESS_INCREMENT_START,
                            DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_BANK_ADDRESS_INCREMENT_LEN
                            );
      ReutRegAddress = DcttGetMcAddressFunc (
                         DcttMain,
                         DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL,
                         0,
                         Channel,
                         DCTT_BYTE_CTL_NA
                         );
      DcttWriteReg64Func (DcttMain, ReutRegAddress, BaseAddressIncCtl);

      if (DcttConfig->traverseDiagonal == TRUE) {
        DcttLogVerbose (DcttMain, "Diagonal is only supported when traversing UP");
      }
    } else {
      DcttError_Assert (DcttMain, 1 == 0, "Unknown direction: %d", NewDirection);
    }

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_BASE_ADDR_START,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    DcttWriteReg64Func (DcttMain, ReutRegAddress, SequenceBaseAddrStart);

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    DcttWriteReg64Func (DcttMain, ReutRegAddress, SequenceBaseAddrWrap);
  }

  return DCTT_SUCCESS;
}

// TODO: Not used.
/*static VOID _CPGCFunctions_PrintErrors(DCTT_API* DcttMain, DCTT_CONFIG_PARAMS* DcttConfig) {
  UINT64 ChunkEccError;
  UINT32 ReutRegAddress;
  UINT16 Chunk;
  UINT16 EccStatus;
  UINT16 NthError;
  UINT8  Channel;

  DcttOutputPrint (DcttMain,"\n************************Error***********************\n");

  for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {

    if (!DCTT_ChannelExists (DcttMain, 0, Channel)) {
      continue;//Channel doesn't exist
    }
    DcttOutputPrint (DcttMain, "Channel: %d\n",Channel);

    ReutRegAddress = DcttGetMcAddressFunc (
      DcttMain,
      DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS,
      0,
      Channel,
      DCTT_BYTE_CTL_NA
      );
    ChunkEccError = DcttReadReg64Func (DcttMain, ReutRegAddress);
    Chunk = (UINT16) Helpers_GetField (
      ChunkEccError,
      DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_F_CHUNK_ERR_STATUS_START,
      DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_F_CHUNK_ERR_STATUS_LEN
      );
    EccStatus = (UINT16) Helpers_GetField (
      ChunkEccError,
      DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_F_ECC_ERR_STATUS_START,
      DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_F_ECC_ERR_STATUS_LEN
      );
    NthError = (UINT16) Helpers_GetField (
      ChunkEccError,
      DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_F_NTH_ERROR_START,
      DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_F_NTH_ERROR_LEN
      );
    DcttOutputPrint (DcttMain, "Chunk Status: 0x%x\n", Chunk);
    DcttOutputPrint (DcttMain, "ECC Status: 0x%x\n", EccStatus);
    DcttOutputPrint (DcttMain, "Nth Error: %d\n", NthError);

  }

  DcttOutputPrint (DcttMain,"****************************************************\n");
}*/

INT32
CPGCFunctions_ErrorHandler (
  DCTT_API              *DcttMain,
  UINT8                 TestMask,
  UINT32                *PerBankErrors,
  TestParameters        *GlobalParameters,
  UINT32                *BaseRowAddress,
  DCTT_DIMM_ADDRESS     CurrentAddress[DCTT_MAX_NUM_CHANNELS]
  )
{
  DCTT_CONFIG_PARAMS  *DcttConfig;
  SetContainer        *ErrorAddressesContainer;
  BOOLEAN             ContainerNotFull;
  UINT64              ErrorAddress;
  UINT64              ChunkEccError;
  UINT64              ErrorDataStatus;
  UINT64              CurrentBaseAddress;
  UINT64              CurrentOffsetAddress;
  INT32               RetVal;
  UINT32              ReutRegAddress;
  UINT32              GlobalError;
  UINT32              CurrentSubsequence;
  UINT32              CompressedAddress;
  UINT32              Bank;
  UINT32              Row;
  UINT32              Column;
  UINT32              CurrentCacheline;
  UINT32              *ValueIndex;
  UINT16              ChannelErrorBitMask;
  UINT16              Chunk;
  UINT16              EccStatus;
  UINT16              NthError;
  UINT8               Channel;
  UINT8               Rank;
  UINT8               DIMM;

  RetVal            = DCTT_SUCCESS;
  ContainerNotFull  = TRUE;
  DcttConfig        = &DcttMain->DcttConfigData;

  DcttOutputPrint (DcttMain,"\n********************Error Handler*******************\n");

  ErrorAddressesContainer = TestParameters_GetErrAddresssContainer (GlobalParameters);

  ReutRegAddress = DcttGetMcAddressFunc (
                     DcttMain,
                     DCTT_REUT_GLOBAL_ERR,
                     0,
                     DCTT_CHANNEL_CTL_NA,
                     DCTT_BYTE_CTL_NA
                     );
  GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

  for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {

    ChannelErrorBitMask = 1 << Channel;

    DcttLogDebug (
      DcttMain,
      "Ch:%d GlobalError: 0x%0x, ChannelErrorBitMask:0x%0x, show error:%d\n",
      Channel,
      GlobalError,
      ChannelErrorBitMask,
      !(GlobalError & ChannelErrorBitMask)
      );

    if (!DCTT_ChannelExists (DcttMain, 0, Channel)) {
      DcttLogDebug (DcttMain, "Channel:%d doesn't exists\n",Channel);
      continue;
    }
    if (!(GlobalError & ChannelErrorBitMask)) {
      DcttLogDebug (DcttMain, "No errors on channel: %d\n",Channel);
      continue;
    }
    if (!(ChannelErrorBitMask & TestMask)) {
      DcttLogDebug (DcttMain, "Skipping Channel %d because we didn't test this channel\n",Channel);
      continue;
    }
    DcttOutputPrint (DcttMain, "Found error on Channel: %d\n",Channel);
    if (PerBankErrors[Channel] < (UINT32) (-1)) {
      PerBankErrors[Channel] = PerBankErrors[Channel] + 1;
      DcttOutputPrint (DcttMain, "Found Bank error number: %d\n", PerBankErrors[Channel]);
    } else {
      DcttOutputPrint (DcttMain, "Found Bank error number: MAX\n");
    }

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_SUBSEQ_PTR_0,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    CurrentSubsequence = DcttReadReg32Func (DcttMain, ReutRegAddress);

    DcttOutputPrint (DcttMain, "Test operation: %d\n", CurrentSubsequence);

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_ERR_DATA_STATUS,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    ErrorDataStatus = DcttReadReg64Func (DcttMain, ReutRegAddress);
    ValueIndex = (UINT32*)&ErrorDataStatus;
    DcttOutputPrint (DcttMain, "DQ Lane Error Status(1's represent error): [63:32]: 0x%0x [31:0]: 0x%0x\n", ValueIndex[1], ValueIndex[0]);

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    ChunkEccError = DcttReadReg64Func (DcttMain, ReutRegAddress);
    Chunk = (UINT16) Helpers_GetField (
                       ChunkEccError,
                       DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_F_CHUNK_ERR_STATUS_START,
                       DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_F_CHUNK_ERR_STATUS_LEN
                       );
    EccStatus = (UINT16) Helpers_GetField (
                           ChunkEccError,
                           DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_F_ECC_ERR_STATUS_START,
                           DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_F_ECC_ERR_STATUS_LEN
                           );
    NthError = (UINT16) Helpers_GetField (
                          ChunkEccError,
                          DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_F_NTH_ERROR_START,
                          DCTT_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_F_NTH_ERROR_LEN
                          );
    DcttOutputPrint (DcttMain, "Chunk Status: 0x%x\n", Chunk);
    DcttOutputPrint (DcttMain, "ECC Status: 0x%x\n", EccStatus);
    DcttOutputPrint (DcttMain, "Nth Error: %d\n", NthError);

    DcttOutputPrint (DcttMain, "Error Address\n");
    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_ERROR_Address,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    ErrorAddress = DcttReadReg64Func (DcttMain, ReutRegAddress);

    Rank = (UINT8) Helpers_GetField (
                     ErrorAddress,
                     DCTT_REUT_CH_ERROR_Address_F_RANK_ADDRESS_START,
                     DCTT_REUT_CH_ERROR_Address_F_RANK_ADDRESS_LEN
                     );
    Bank = Helpers_GetField (
             ErrorAddress,
             DCTT_REUT_CH_ERROR_Address_F_BANK_ADDRESS_START,
             DCTT_REUT_CH_ERROR_Address_F_BANK_ADDRESS_LEN
             );
    Row = Helpers_GetField (
            ErrorAddress,
            DCTT_REUT_CH_ERROR_Address_F_ROW_ADDRESS_START,
            DCTT_REUT_CH_ERROR_Address_F_ROW_ADDRESS_LEN
            );
    Column = Helpers_GetField (
               ErrorAddress,
               DCTT_REUT_CH_ERROR_Address_F_COL_ADDRESS_START,
               DCTT_REUT_CH_ERROR_Address_F_COL_ADDRESS_LEN
               );
    DIMM  = Rank / DCTT_MAX_RANK_IN_DIMM;

    //
    // If CurrentAddress is not NULL, update the address with the error address.
    // Adjust for direction and order in calling function.
    //
    if (CurrentAddress != NULL) {
      CurrentAddress[Channel].Col = Column & CPGC_CACHELINE_MASK_OFF;
      CurrentAddress[Channel].Row = Row;
      DcttLogDebug (
        DcttMain,
        "NEW Channel %d CurrentAddress Col: %u\tRow: %u\n",
        Channel,
        CurrentAddress[Channel].Col,
        CurrentAddress[Channel].Row
        );
    }

    ValueIndex = (UINT32*) &ErrorAddress;
    DcttLogDebug (
      DcttMain,
      "REUT_CH_ERROR_Address: Hi Val: 0x%0x LoVal: 0x%0x\n",
      ValueIndex[1],
      ValueIndex[0]
      );

    DcttOutputPrint (DcttMain, "DIMM: %d\n", DIMM);
    DcttOutputPrint (DcttMain, "Rank: %d\n",Rank);
    DcttOutputPrint (DcttMain, "Bank: %d\n", Bank);
    DcttOutputPrint (DcttMain, "Row: %d\n", Row);
    DcttOutputPrint (DcttMain, "Col: %d\n", Column);

    CompressedAddress = AddressToUINT32 (Channel, Rank, Bank, Row, Column);
    ContainerNotFull = SetContainer_AddItem (ErrorAddressesContainer, CompressedAddress);

    DcttOutputPrint (DcttMain, "\nCurrent Offset Address\n", DIMM);
    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    CurrentOffsetAddress = DcttReadReg64Func (DcttMain, ReutRegAddress);

    Row = Helpers_GetField (
            CurrentOffsetAddress,
            DCTT_REUT_CH_SEQ_OFFSET_ADDR_CURRENT_F_ROW_ADDRESS_START,
            DCTT_REUT_CH_SEQ_OFFSET_ADDR_CURRENT_F_ROW_ADDRESS_LEN
            );
    Column = Helpers_GetField (
               CurrentOffsetAddress,
               DCTT_REUT_CH_SEQ_OFFSET_ADDR_CURRENT_F_COL_ADDRESS_START,
               DCTT_REUT_CH_SEQ_OFFSET_ADDR_CURRENT_F_COL_ADDRESS_LEN
               );

    DcttOutputPrint (DcttMain, "Row: %d\n", Row);
    DcttOutputPrint (DcttMain, "Col: %d\n", Column);
    DcttOutputPrint (DcttMain, "\nCurrent Base Address\n", DIMM);

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_0,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    CurrentBaseAddress = DcttReadReg64Func (DcttMain, ReutRegAddress);

    Rank = (UINT8) Helpers_GetField (
                     CurrentBaseAddress,
                     DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_RANK_ADDRESS_START,
                     DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_RANK_ADDRESS_LEN
                     );
    Bank = Helpers_GetField (
             CurrentBaseAddress,
             DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_BANK_ADDRESS_START,
             DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_BANK_ADDRESS_LEN
             );
    Row = Helpers_GetField (
            CurrentBaseAddress,
            DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_ROW_ADDRESS_START,
            DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_ROW_ADDRESS_LEN
            );
    Column = Helpers_GetField (
               CurrentBaseAddress,
               DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_COL_ADDRESS_START,
               DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_COL_ADDRESS_LEN
               );

    DcttOutputPrint (DcttMain, "DIMM: %d\n", DIMM);
    DcttOutputPrint (DcttMain, "Rank: %d\n",Rank);
    DcttOutputPrint (DcttMain, "Bank: %d\n", Bank);
    DcttOutputPrint (DcttMain, "Row: %d\n", Row);
    DcttOutputPrint (DcttMain, "Col: %d\n", Column);


    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_CACHELINE_STATUS_0,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    CurrentCacheline = DcttReadReg32Func (DcttMain, ReutRegAddress);
    DcttLogDebug (DcttMain, "Current Cacheline: %d\n", CurrentCacheline);

    if (BaseRowAddress != NULL) {
      DcttOutputPrint (DcttMain, "Swizzled Base Row: %d\n", BaseRowAddress[Channel]);
    }

    // TODO: Put all this info in a report struct.
    // TODO: Read WDB @ position 63 Check with OA
  }
  DcttOutputPrint (DcttMain,"****************************************************\n");
  if (DcttConfig->failOnError) {
    DcttOutputPrint (DcttMain,"Error found in memory.  Stopping test.  Disable through DcttConfigParam.FailOnError\n");
    RetVal = DCTT_FAIL;
  }

  DcttLogVerbose (
    DcttMain,
    "StopOnMaxMarginErrors: 0x%x\tContainerNotFull: 0x%x\n",
    DcttConfig->StopOnMaxMarginErrors,
    ContainerNotFull
    );

  if ((DcttConfig->StopOnMaxMarginErrors == TRUE) && (ContainerNotFull == FALSE)) {
    DcttLogDebug (DcttMain, "StopOnMaxMarginErrors set, and container is full.\n");
    RetVal = DCTT_FAIL;
  }

  return RetVal;
}

INT32
CPGCFunctions_SetSubsequenceOffsetCtrl (
  DCTT_API  *DcttMain,
  UINT8     SubsequenceNumber,
  UINT8     BaseInverted,
  UINT8     BaseSubseqType,
  UINT8     EnableRowIncrement,
  UINT8     EnableColIncrement,
  UINT8     RowIncrementOrder,
  UINT8     ColIncrementOrder,
  UINT8     BaseRepeatRate,
  UINT8     TriggerType,
  UINT8     OffsetAddrUpdateRate
  )
{
  UINT32              ReutRegAddress;
  UINT32              SubsequenceOffsetCtl;
  UINT8               Channel;

  for (Channel = 0; Channel < DcttMain->DcttConfigData.numberChannels; Channel++) {
    if (!DCTT_ChannelExists (DcttMain, 0, Channel)) {
      continue;
    }

    SubsequenceOffsetCtl  = 0;
    SubsequenceOffsetCtl |= BaseInverted       << DCTT_REUT_CH_SUBSEQ_OFFSET_CTL_F_INV_DATA_ECC_START;
    SubsequenceOffsetCtl |= EnableRowIncrement << DCTT_REUT_CH_SUBSEQ_OFFSET_CTL_F_ROW_INC_ENABLE_START;
    SubsequenceOffsetCtl |= EnableColIncrement << DCTT_REUT_CH_SUBSEQ_OFFSET_CTL_F_COL_INC_ENABLE_START;
    SubsequenceOffsetCtl |= RowIncrementOrder  << DCTT_REUT_CH_SUBSEQ_OFFSET_CTL_F_ROW_INC_ORDER_START;
    SubsequenceOffsetCtl |= ColIncrementOrder  << DCTT_REUT_CH_SUBSEQ_OFFSET_CTL_F_COL_INC_ORDER_START;

    if (BaseSubseqType < CPGC_ST_OFFSET_BASE_NONE) {
      SubsequenceOffsetCtl |= BaseSubseqType << DCTT_REUT_CH_SUBSEQ_OFFSET_CTL_F_BASE_SUBSEQ_TYPE_START;
      SubsequenceOffsetCtl |= BaseRepeatRate << DCTT_REUT_CH_SUBSEQ_OFFSET_CTL_F_BASE_REPEAT_RATE_START;
    } else {
      // No Base operation
      SubsequenceOffsetCtl |= 0 << DCTT_REUT_CH_SUBSEQ_OFFSET_CTL_F_BASE_REPEAT_RATE_START;
    }

    if (TriggerType == CPGC_OFFSET_TRIGGER_NONE) {
      //Offset cells are neighbors of base
      SubsequenceOffsetCtl |= 0 << DCTT_REUT_CH_SUBSEQ_OFFSET_CTL_F_OFFSET_ADDR_UPDATE_RATE_START;
    } else if (TriggerType == CPGC_OFFSET_TRIGGER_ROW) {
      SubsequenceOffsetCtl |= OffsetAddrUpdateRate << DCTT_REUT_CH_SUBSEQ_OFFSET_CTL_F_OFFSET_ADDR_UPDATE_RATE_START;
      SubsequenceOffsetCtl |= 1 << DCTT_REUT_CH_SUBSEQ_OFFSET_CTL_F_OFFSET_ROW_WRAP_TRIGGER_START;
    } else {
      DcttError_Assert (DcttMain, 1 == 0, "Unknown offset trigger: %d", TriggerType);
    }

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SUBSEQ_OFFSET_CTL_0,
                       0,
                       Channel,
                       SubsequenceNumber
                       );
    DcttWriteReg32Func (DcttMain, ReutRegAddress, SubsequenceOffsetCtl);
  }
  return DCTT_SUCCESS;
}

INT32
CPGCFunctions_SetSubsequenceCtrl (
  DCTT_API  *DcttMain,
  UINT8     SubsequenceNumber,
  BOOLEAN   InvertData,
  UINT32    Pattern,
  UINT32    SubsequenceType,
  UINT32    Delay,
  UINT32    RepeatRate,
  BOOLEAN   FinishOnWrap
  )
{
  UINT32 ReutRegAddress;
  UINT32 subseqCtlRegVal;
  UINT8 Channel;

  for (Channel = 0; Channel < DcttMain->DcttConfigData.numberChannels; Channel++) {
    if (!DCTT_ChannelExists (DcttMain, 0, Channel)) {
      continue;
    }

    subseqCtlRegVal = 0;
    subseqCtlRegVal |= SubsequenceType << DCTT_REUT_CH_SUBSEQ_CTL_F_SUBSEQ_TYPE_START;
    subseqCtlRegVal |= Pattern         << DCTT_REUT_CH_SUBSEQ_CTL_F_DATA_ECC_ADDRESS_INV_START;

    subseqCtlRegVal = (UINT32) Helpers_SetField (
                                 subseqCtlRegVal,
                                 Delay,
                                 DCTT_REUT_CH_SUBSEQ_CTL_F_SUBSEQ_WAIT_START,
                                 DCTT_REUT_CH_SUBSEQ_CTL_F_SUBSEQ_WAIT_LEN
                                 );

    if (InvertData) {
      subseqCtlRegVal |= 1 << DCTT_REUT_CH_SUBSEQ_CTL_F_INV_DATA_ECC_START;
    }

    if (FinishOnWrap) {
      subseqCtlRegVal |= 1 << DCTT_REUT_CH_SUBSEQ_CTL_F_STOP_BASE_TRIGGER_START;
      subseqCtlRegVal |= 1 << DCTT_REUT_CH_SUBSEQ_CTL_F_NUMBER_CACHELINES_SCALE_START;
      subseqCtlRegVal |= 0 << DCTT_REUT_CH_SUBSEQ_CTL_F_NUMBER_CACHELINES_START;
    } else {
      subseqCtlRegVal |= 0 << DCTT_REUT_CH_SUBSEQ_CTL_F_NUMBER_CACHELINES_SCALE_START;
      subseqCtlRegVal = (UINT32) Helpers_SetField (
                                   subseqCtlRegVal,
                                   RepeatRate,
                                   DCTT_REUT_CH_SUBSEQ_CTL_F_NUMBER_CACHELINES_START,
                                   DCTT_REUT_CH_SUBSEQ_CTL_F_NUMBER_CACHELINES_LEN
                                   );
    }

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SUBSEQ_CTL_0,
                       0,
                       Channel,
                       SubsequenceNumber
                       );
    DcttWriteReg32Func (DcttMain, ReutRegAddress, subseqCtlRegVal);
  }

  return DCTT_SUCCESS;
}

// TODO: Merge this function with the error handler or create a common function called by both functions.
static
INT32
_CPGCFunctions_UpdateErrorCount (
  DCTT_API    *DcttMain,
  UINT8       TestMask,
  UINT8       Rank,
  RankErrors  *CurrentNumberErrors
  )
{
  UINT32  ReutRegAddress;
  UINT32  GlobalError;
  UINT8   Channel;
  UINT8   CurrentChannelBit;

  ReutRegAddress  = DcttGetMcAddressFunc (DcttMain, DCTT_REUT_GLOBAL_ERR, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
  GlobalError     = DcttReadReg32Func (DcttMain, ReutRegAddress);

  for (Channel = 0; Channel < DcttMain->DcttConfigData.numberChannels; Channel++) {
    if (!DCTT_ChannelExists (DcttMain, 0, Channel)) {
      continue;
    }

    CurrentChannelBit = 1 << Channel;
    if (!(GlobalError & CurrentChannelBit)) {
      continue; //No errors on this Channel.
    }

    if (!(CurrentChannelBit & TestMask)) {
      continue; //Didn't run the test on this Channel.
    }

    CurrentNumberErrors[Rank].channelErrors[Channel] = CurrentNumberErrors[Rank].channelErrors[Channel] + 1;
  }

  return DCTT_SUCCESS;
}


static
INT32
_CPGCFunctions_GetExecutionReturnCode (
  DCTT_API    *DcttMain,
  RankErrors  *CurrentNumberErrors,
  UINT8       Channel,
  UINT8       Rank,
  UINT8       ChannelErrors // TODO: remove
  )
{
  if (CurrentNumberErrors[Rank].channelErrors[Channel] < DcttMain->DcttConfigData.maxNumberErrors) {
    //If I can still rerun this Channel because I haven't reach the maximum number of errors
    //then return so the parser can be called again. O.W. continue, so the untested ranks can finish their test
    return PARSER_ERROR_RERUN;
  }

  return CONTINUE;
}

INT32
_CPGCFunctions_SetTestStartNewAddress (
  DCTT_API    *DcttMain,
  MemTravDir  TestDirection,
  UINT32      *ErrorAddress,
  UINT32      *LastAddress,
  UINT32      *FirstAddress,
  UINT8       Channel,
  UINT8       Rank
  )
{
  DCTT_ORDER_NAMES    TraverseOrder[DcttOrderMax];
  DCTT_CONFIG_PARAMS  *DcttConfig;
  UINT64              SequenceBaseAddrStart;
  UINT64              OrgSequenceBaseAddrStart;// TODO: debug only
  UINT32              TraverseOrderIndex;
  UINT32              *ValueIndex;// TODO: debug only
  UINT32              ReutRegAddress;
  UINT32              ColumnGranularity;
  INT8                IncrementDirection;
  UINT8               DimmNumber;

  DcttConfig            = &DcttMain->DcttConfigData;
  TraverseOrder[0]      = DcttConfig->firstOrder;
  TraverseOrder[1]      = DcttConfig->secondOrder;
  TraverseOrder[2]      = DcttConfig->thirdOrder;
  TraverseOrder[3]      = DcttConfig->fourthOrder;
  SequenceBaseAddrStart = 0;

  //DimmNumber = DcttSysInfo_GetDimmIDFromLogicalRank (DcttMain, 0, Channel, Rank);
  DimmNumber  = Rank / DCTT_MAX_RANK_IN_DIMM;

  ColumnGranularity = Helpers_Log2 ((DcttGetColumnSizeFunc (DcttMain, 0, Channel, DimmNumber) - 1));
  ColumnGranularity = ColumnGranularity - CPGC_NUMBER_BITS_CACHELINE + 1;

  if (TestDirection == UP) {
    IncrementDirection = 1;
  } else if (TestDirection == DOWN) {
    IncrementDirection = -1;
  } else {
    DcttError_Assert (DcttMain, 1 == 0, "Unknown Memory Traverse Direction");
    return DCTT_FAIL;
  }

  // Add one to the error address
  // Max value in traverse order is 3 because we are not iterating over Rank
  // Comparisons are set for greater or equal because we can only run this test
  // with direction == UP
  for (TraverseOrderIndex = 0; TraverseOrderIndex < DcttOrderRank; TraverseOrderIndex++) {
    if (ErrorAddress[TraverseOrder[TraverseOrderIndex]] >= LastAddress[TraverseOrder[TraverseOrderIndex]]) {
      // We cannot increment this memory traverse order because it is equal to its greatest value.
      // Reset it to the first one and try with the next one.
      ErrorAddress[TraverseOrder[TraverseOrderIndex]] = FirstAddress[TraverseOrder[TraverseOrderIndex]];
      if (TraverseOrderIndex == 2) {
        // This is the last memory traverse order.  We should never be in this case because
        // we are only calling this function if we are not in the last address.
        DcttError_Assert (DcttMain, 1 == 0, "Couldn't increment error address.");
      }
    } else {
      if (TraverseOrder[TraverseOrderIndex] == DcttOrderColumn) {
        ErrorAddress[TraverseOrder[TraverseOrderIndex]] = ErrorAddress[TraverseOrder[TraverseOrderIndex]] +
          (IncrementDirection * ColumnGranularity);
      } else {
        ErrorAddress[TraverseOrder[TraverseOrderIndex]] = ErrorAddress[TraverseOrder[TraverseOrderIndex]] +
          IncrementDirection;
      }

      DcttLogDebug (
        DcttMain,
        "Incrementing order %d on order iteration %d. New value is: %d\n",
        TraverseOrderIndex,
        TraverseOrder[TraverseOrderIndex],
        ErrorAddress[TraverseOrder[TraverseOrderIndex]]
        );
      //Address incremented in 1, stop
      break;
    }
  }

  //Set 1+ the error address as the new start
  // TODO: Check uninitalized value implications
  SequenceBaseAddrStart = Helpers_SetField (
                            SequenceBaseAddrStart,
                            ErrorAddress[0],
                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN
                            );
  SequenceBaseAddrStart = Helpers_SetField (
                            SequenceBaseAddrStart,
                            ErrorAddress[1],
                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN
                            );
  SequenceBaseAddrStart = Helpers_SetField (
                            SequenceBaseAddrStart,
                            ErrorAddress[2],
                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_START,
                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_LEN
                            );

  ReutRegAddress = DcttGetMcAddressFunc (
                     DcttMain,
                     DCTT_REUT_CH_SEQ_BASE_ADDR_START,
                     0,
                     Channel,
                     DCTT_BYTE_CTL_NA
                     );
  OrgSequenceBaseAddrStart = DcttReadReg64Func (DcttMain, ReutRegAddress);
  ValueIndex = (UINT32*) &OrgSequenceBaseAddrStart;
  DcttLogDebug (
    DcttMain,
    "Original start address on Channel %d: Hi Val: 0x%0x LoVal: 0x%0x\n",
    Channel,
    ValueIndex[1],
    ValueIndex[0]
    );
  DcttWriteReg64Func (DcttMain, ReutRegAddress, SequenceBaseAddrStart);

  SequenceBaseAddrStart = DcttReadReg64Func (DcttMain, ReutRegAddress);
  ValueIndex = (UINT32*) &SequenceBaseAddrStart;
  DcttLogDebug (
    DcttMain,
    "New start address on Channel %d: Hi Val: 0x%0x LoVal: 0x%0x\n",
    Channel,
    ValueIndex[1],
    ValueIndex[0]
    );

  return DCTT_SUCCESS;
}

INT32
CPGCFunctions_ExecuteTest (
  DCTT_API        *DcttMain,
  UINT8           NumberSubsequences,
  RankErrors      *CurrentNumberErrors,
  MemTravDir      TestDirection,
  TestParameters  *GlobalParameters
  )
{
  DCTT_CONFIG_PARAMS  *DcttConfig;
  DCTT_DIMM_ADDRESS   *LastAddressPtr;
  DCTT_DIMM_ADDRESS   *FirstAddressPtr;
  UINT64              SeqConfigRegVal;
  UINT64              SequenceBaseAddrWrap;
  UINT64              StartAddress;
  UINT64              SequenceBaseAddrStart;
  UINT64              CurrentAddress;
  UINT32              PerBankErrors[DCTT_MAX_NUM_CHANNELS];
  UINT32              ErrorAddress[DcttOrderMax];
  UINT32              LastAddress[DcttOrderMax];
  UINT32              FirstAddress[DcttOrderMax];
  UINT32              *ValueIndex;
  UINT32              ErrorBank;
  UINT32              ErrorRow;
  UINT32              ErrorColumn;
  UINT32              ErrorRank;
  UINT32              ChannelErrorCtl;
  UINT32              LoopcountREUTregAddress;
  UINT32              ReutRegAddress;
  UINT32              GlobalErrorPrevious = 27; // TODO: Refactor the polling loop on the hardware
  UINT32              TestDone;
  UINT32              ChannelErrors;
  UINT32              GlobalError;
  UINT32              RowSize;
  UINT32              LastBank;
  UINT32              Bank;
  UINT32              ColumnSize;
  UINT32              RankMapping;
  UINT32              DummyReadMask;
  INT32               ReturnCode;
  UINT8               Channel;
  UINT8               Rank;
  UINT8               ChannelMask;
  UINT8               ChannelsPresentRank;
  UINT8               ChannelFinish;
  UINT8               TestMask;
  UINT8               ErrorsChannel0;
  UINT8               ErrorsChannel1;
  UINT8               DimmNumber;
  BOOLEAN             ProcessErrors;

  DcttLogDebug (DcttMain, "ExecuteTest\n");
  DcttConfig  = &DcttMain->DcttConfigData;
  ChannelMask = DCTT_GetChannelMask (DcttMain, 0);

  DcttError_Assert (DcttMain, NumberSubsequences < 8, "Number of subsequences should be less than 8.");
  DcttError_Assert (
    DcttMain,
    DcttConfig->runTestOnSecondOrder != TRUE,
    "Cannot use normal execute test to run test on second order."
    );

  for (Rank = 0; Rank < DcttConfig->numberRankPerChannel; Rank++) {
    ErrorsChannel0      = 0;
    ErrorsChannel1      = 0;
    GlobalError         = 0;
    ChannelsPresentRank = 0;
    TestMask            = 0;

    for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
      SeqConfigRegVal = 0; // TODO: This value can be read from the CPGC register or we can cache it
      ChannelErrorCtl        = DCTT_REUT_CH_ERR_CTL_STOP_NTH_ERROR_SETTING;

      if (!DCTT_ChannelExists (DcttMain, 0, Channel)) {
        //Setting maximum errors on this Channel (that doesn't exist), so it can be skipped.
        DcttLogDebug (DcttMain, "Channel %d does not exists\n", Channel);
        CurrentNumberErrors[Rank].channelErrors[Channel] = DcttConfig->maxNumberErrors;
        continue;
      }

      //subsequence start
      SeqConfigRegVal = Helpers_SetField (
                          SeqConfigRegVal,
                          0,
                          DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_START,
                          DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_LEN
                          );
      //subsequence stop
      SeqConfigRegVal = Helpers_SetField (
                          SeqConfigRegVal,
                          NumberSubsequences - 1,
                          DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_START,
                          DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_LEN
                          );
      //Initialization Mode: REUT testing
      SeqConfigRegVal = Helpers_SetField (
                          SeqConfigRegVal,
                          1,
                          DCTT_REUT_CH_SEQ_CFG_F_INITIALIZATION_MODE_START,
                          DCTT_REUT_CH_SEQ_CFG_F_INITIALIZATION_MODE_LEN
                          );

      SeqConfigRegVal = Helpers_SetField (
                          SeqConfigRegVal,
                          1,
                          DCTT_REUT_CH_SEQ_CFG_F_ADDR_UPDATE_RATE_MODE_START,
                          DCTT_REUT_CH_SEQ_CFG_F_ADDR_UPDATE_RATE_MODE_LEN
                          );

      SeqConfigRegVal = Helpers_SetField (
                          SeqConfigRegVal,
                          1,
                          DCTT_REUT_CH_SEQ_CFG_F_STOP_BASE_SEQUENCE_WRAP_TRIGGER_START,
                          DCTT_REUT_CH_SEQ_CFG_F_STOP_BASE_SEQUENCE_WRAP_TRIGGER_LEN
                          );

      SeqConfigRegVal = Helpers_SetField (
                          SeqConfigRegVal,
                          DcttConfig->startTestDelay,
                          DCTT_REUT_CH_SEQ_CFG_F_START_TEST_DELAY_START,
                          DCTT_REUT_CH_SEQ_CFG_F_START_TEST_DELAY_LEN
                          );

      LoopcountREUTregAddress = DcttGetMcAddressFunc (
                                  DcttMain,
                                  DCTT_REUT_CH_SEQ_LOOPCOUNT_LIMIT,
                                  0,
                                  Channel,
                                  DCTT_BYTE_CTL_NA
                                  );
      DcttWriteReg32Func (DcttMain, LoopcountREUTregAddress, 0);

#ifndef DISABLE_DUMMY_READS
      if (DcttConfig->enableDummyReads) {
        SeqConfigRegVal = Helpers_SetField (
                            SeqConfigRegVal,
                            1,
                            DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_START,
                            DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_LEN
                            );
      } else
#endif
      {
        SeqConfigRegVal = Helpers_SetField (
                            SeqConfigRegVal,
                            0,
                            DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_START,
                            DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_LEN
                            );
      }

      DcttLogDebug (
        DcttMain,
        "Number errors in Rank %d, Channel %d is %d; Max is DcttConfig->maxNumberErrors: %d\n",
        Rank,
        Channel,
        CurrentNumberErrors[Rank].channelErrors[Channel],
        DcttConfig->maxNumberErrors
        );
      DcttLogDebug (
        DcttMain,
        "Channel exists: %d\n",
        DCTT_RankInChannelExists (DcttMain, 0, Rank, Channel)
        );

      if ((DCTT_RankInChannelExists (DcttMain, 0, Rank, Channel)) &&
          (CurrentNumberErrors[Rank].channelErrors[Channel] < DcttConfig->maxNumberErrors)) {
        DcttOutputPrint (DcttMain,"Running Rank %d in Channel %d\n",Rank, Channel);
        DcttLogDebug (DcttMain, "Setting vars to run Rank %d in Channel %d\n",Rank, Channel);
        ReutRegAddress = DcttGetMcAddressFunc (
                           DcttMain,
                           DCTT_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_0,
                           0,
                           Channel,
                           DCTT_BYTE_CTL_NA
                           );
        DcttWriteReg32Func (DcttMain, ReutRegAddress, Rank);
        // TODO: ? - XO WA: Different workaround to look for extra errors
        // TODO: Refactor. Previous write can be merged with this one after testing is complete.
        if (DcttConfig->dontStopErrors) {
          RankMapping = 0;

          ReutRegAddress = DcttGetMcAddressFunc (
                             DcttMain,
                             DCTT_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_0,
                             0,
                             Channel,
                             DCTT_BYTE_CTL_NA
                             );
          RankMapping = (UINT32) Helpers_SetField (
                                   RankMapping,
                                   Rank,
                                   DCTT_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_F_RANK0_START,
                                   DCTT_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_F_RANK0_LEN
                                   );
          RankMapping = (UINT32) Helpers_SetField (
                                   RankMapping,
                                   Rank,
                                   DCTT_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_F_RANK1_START,
                                   DCTT_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_F_RANK1_LEN
                                   );
          DcttWriteReg32Func (DcttMain, ReutRegAddress, RankMapping);
        }

        ChannelsPresentRank = ChannelsPresentRank + 1;
        DcttLogDebug (DcttMain, "Channel: 0x%0x TestMask :  0x%0x\n", Channel, TestMask);
        TestMask = (TestMask | (1 << Channel));
        DcttLogDebug (DcttMain, "new TestMask :  0x%0x\n", TestMask);

        _CPGCFunctions_SetBaseAddrIncCtrlForRank (DcttMain, Channel, Rank);

        //DimmNumber  = DcttSysInfo_GetDimmIDFromLogicalRank (DcttMain, 0, Channel, Rank);
        DimmNumber  = Rank / DCTT_MAX_RANK_IN_DIMM;
        RowSize     = DcttGetRowSizeFunc (DcttMain, 0, Channel, DimmNumber);
        RowSize     = RowSize - 1;
        ColumnSize  = DcttGetColumnSizeFunc (DcttMain, 0, Channel, DimmNumber) - 1;
        DcttLogDebug (DcttMain, "---Setting Row size on stop address\n");
        DcttLogDebug (
          DcttMain,
          "Row size %d in Rank %d in Channel %d\n",
          RowSize,
          Channel,
          RowSize
          );

        if (TestDirection == UP) {
          ReutRegAddress = DcttGetMcAddressFunc (
                             DcttMain,
                             DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP,
                             0,
                             Channel,
                             DCTT_BYTE_CTL_NA
                             );
          SequenceBaseAddrWrap = DcttReadReg64Func (DcttMain, ReutRegAddress);

          SequenceBaseAddrWrap = Helpers_SetField (
                                   SequenceBaseAddrWrap,
                                   RowSize,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_START,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_LEN
                                   );

          SequenceBaseAddrWrap = Helpers_SetField (
                                   SequenceBaseAddrWrap,
                                   ColumnSize,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_START,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_LEN
                                   );

          DcttWriteReg64Func (DcttMain, ReutRegAddress, SequenceBaseAddrWrap);
        } else if (TestDirection == DOWN) {
          ReutRegAddress = DcttGetMcAddressFunc (
                             DcttMain,
                             DCTT_REUT_CH_SEQ_BASE_ADDR_START,
                             0,
                             Channel,
                             DCTT_BYTE_CTL_NA
                             );
          SequenceBaseAddrStart = DcttReadReg64Func (DcttMain, ReutRegAddress);

          SequenceBaseAddrStart = Helpers_SetField (
                                    SequenceBaseAddrStart,
                                    RowSize,
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN
                                    );

          SequenceBaseAddrStart = Helpers_SetField (
                                    SequenceBaseAddrStart,
                                    ColumnSize,
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN
                                    );

          DcttWriteReg64Func (DcttMain, ReutRegAddress, SequenceBaseAddrStart);
        } else {
          DcttError_Assert (DcttMain, 1 == 0, "Unknown Direction in execute test\n");
          DcttLogDebug (DcttMain, "Unknown Direction in execute test\n");
        }

        // Enable Global Control
        SeqConfigRegVal = Helpers_SetField (SeqConfigRegVal, 1, 11, 1);
      } else {
        DcttLogDebug (DcttMain, "Will not run Rank %d in Channel %d\n",Rank, Channel);

        if (!DCTT_RankInChannelExists (DcttMain, 0, Rank, Channel)) {
          DcttLogDebug (DcttMain, "\n");
          //Setting maximum errors on this Rank/Channel (that doesn't exist), so it can be skipped.
          CurrentNumberErrors[Rank].channelErrors[Channel] = DcttConfig->maxNumberErrors;
        } else {
          DcttLogDebug (DcttMain, " because max number of errors have been detected\n");
        }

        //We are not going to run the test on this Channel.  Disable Global Control
        SeqConfigRegVal = Helpers_SetField (SeqConfigRegVal, 0, 11, 1);
      }

      ReutRegAddress = DcttGetMcAddressFunc (
                         DcttMain,
                         DCTT_REUT_CH_SEQ_CFG,
                         0,
                         Channel,
                         DCTT_BYTE_CTL_NA
                         );
      DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal);

      ReutRegAddress = DcttGetMcAddressFunc (
                         DcttMain,
                         DCTT_REUT_CH_ERR_CTL,
                         0,
                         Channel,
                         DCTT_BYTE_CTL_NA
                         );
      ChannelErrorCtl = (UINT32) Helpers_SetField (
                                   ChannelErrorCtl,
                                   CurrentNumberErrors[Rank].channelErrors[Channel] + 1,
                                   DCTT_REUT_CH_ERR_CTL_F_STOP_NTH_ERROR_START,
                                   DCTT_REUT_CH_ERR_CTL_F_STOP_NTH_ERROR_LEN
                                   );

      DcttLogDebug (
        DcttMain,
        "ChannelErrorCtl on Channel %d Rank %d is 0x%x\n",
        Channel,
        Rank,
        ChannelErrorCtl
        );

      // Stop on nth error
      DcttWriteReg32Func (DcttMain, ReutRegAddress, ChannelErrorCtl);
    }

    if (ChannelsPresentRank == 0) {
      //No Channel has this Rank, continue
      DcttLogDebug (DcttMain,  "Will completely skip Rank %d\n",Rank);
      continue;
    }

    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_GLOBAL_CTRL,
                       0,
                       DCTT_CHANNEL_CTL_NA,
                       DCTT_BYTE_CTL_NA
                       );
    DcttWriteReg32Func (DcttMain, ReutRegAddress, (6));

    // TODO: ? - Replace next while for an if that takes in account all channels
    // Next while is part of a  workaround to be able to report more than one
    // error, will be removed after bug is fixed.
    while ((CurrentNumberErrors[Rank].channelErrors[0] < DcttConfig->maxNumberErrors) ||
           (CurrentNumberErrors[Rank].channelErrors[1] < DcttConfig->maxNumberErrors)) {
      ChannelFinish = ~(TestMask) & ChannelMask;

      if (DcttConfig->runTestPerBank) {
        // Right now we are only supporting same start and stop address Bank on all channels
        // Checking if this is true
        for (Channel = 1; Channel < DCTT_MAX_NUM_CHANNELS; Channel++) {
          DcttError_Assert (
            DcttMain,
            (DcttConfig->bottomAddress[0].Bank == DcttConfig->bottomAddress[Channel].Bank),
            "Start Address Bank has to be the same on all channels\n"
            );
          DcttError_Assert (
            DcttMain,
            (DcttConfig->topAddress[0].Bank == DcttConfig->topAddress[Channel].Bank),
            "Start Address Bank has to be the same on all channels\n"
            );
        }

        LastBank = (DcttConfig->topAddress[0].Bank) + 1;
      } else {
        // In this case we are going to test all banks on one run so
        // the Bank loop only needs to do one iteration
        LastBank = 1;
      }

      for (Bank = 0; Bank < LastBank; Bank++) {
        for (Channel = 0; Channel < DCTT_MAX_NUM_CHANNELS; Channel++) {
          // Resetting the per Bank errors
          PerBankErrors[Channel] = 0;
        }

        if (DcttConfig->dontStopErrors == TRUE) {
          // Restarting test start address
          DcttError_Assert (DcttMain, TestDirection == UP, "Down direction is not allowed when dontStopOnErrors is true");

          for (Channel = 0; Channel < DCTT_MAX_NUM_CHANNELS; Channel++) {
            StartAddress = 0;
            StartAddress = Helpers_SetField (
                             StartAddress,
                             DcttConfig->bottomAddress[Channel].Col,
                             DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                             DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN
                             );
            StartAddress = Helpers_SetField (
                             StartAddress,
                             DcttConfig->bottomAddress[Channel].Row,
                             DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                             DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN
                             );
            StartAddress = Helpers_SetField (
                             StartAddress,
                             DcttConfig->bottomAddress[Channel].Bank,
                             DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_START,
                             DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_LEN
                             );

            ReutRegAddress = DcttGetMcAddressFunc (
                               DcttMain,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_START,
                               0,
                               Channel,
                               DCTT_BYTE_CTL_NA
                               );
            DcttWriteReg64Func (DcttMain, ReutRegAddress, 0);
          }
        }

        if (DcttConfig->runTestPerBank) {
          DummyReadMask  = 0;
          DummyReadMask |= (1 << Bank);

          DcttOutputPrint (DcttMain, "Running test on Bank %d\n",Bank);
          for (Channel = 0; Channel < DCTT_MAX_NUM_CHANNELS; Channel++) {
#ifndef DISABLE_DUMMY_READS
            if (DcttConfig->enableDummyReads) {
              // Setting mask on current Bank to prevent a bug
              DcttOutputPrint (DcttMain, "Dummy reads mask on Channel %d: 0x%x\n", Channel, DummyReadMask);

              ReutRegAddress = DcttGetMcAddressFunc (
                                 DcttMain,
                                 DCTT_REUT_CH_SEQ_DUMMYREAD_MASK_0,
                                 0,
                                 Channel,
                                 DCTT_BYTE_CTL_NA
                                 );
              DcttWriteReg32Func (DcttMain, ReutRegAddress, DummyReadMask);
            }
#endif
            // Set Bank on start and wrap addresses
            ReutRegAddress = DcttGetMcAddressFunc (
                               DcttMain,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP,
                               0,
                               Channel,
                               DCTT_BYTE_CTL_NA
                               );
            SequenceBaseAddrWrap = DcttReadReg64Func (DcttMain, ReutRegAddress);
            SequenceBaseAddrWrap = Helpers_SetField (
                                     SequenceBaseAddrWrap,
                                     Bank,
                                     DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_BANK_ADDRESS_START,
                                     DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_BANK_ADDRESS_LEN
                                     );
            DcttWriteReg64Func (DcttMain, ReutRegAddress, SequenceBaseAddrWrap);

            ReutRegAddress = DcttGetMcAddressFunc (
                               DcttMain,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_START,
                               0,
                               Channel,
                               DCTT_BYTE_CTL_NA
                               );
            SequenceBaseAddrStart = DcttReadReg64Func (DcttMain, ReutRegAddress);
            SequenceBaseAddrStart = Helpers_SetField (
                                      SequenceBaseAddrStart,
                                      Bank,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_START,
                                      DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_LEN
                                      );
            DcttWriteReg64Func (DcttMain, ReutRegAddress, SequenceBaseAddrStart);
          }
        } else {
          DcttOutputPrint (DcttMain,"Running test on all banks\n");
        }

        ReutRegAddress = DcttGetMcAddressFunc (
                           DcttMain,
                           DCTT_REUT_GLOBAL_CTRL,
                           0,
                           DCTT_CHANNEL_CTL_NA,
                           DCTT_BYTE_CTL_NA
                           );
        if (DcttConfig->dontStopErrors == TRUE) {
          DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST + 16));
        } else {
          DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST));
        }

        // Loop until test is done
        // TODO: Refactor IO loop
        do{
          ReutRegAddress = DcttGetMcAddressFunc (
                             DcttMain,
                             DCTT_REUT_GLOBAL_ERR,
                             0,
                             DCTT_CHANNEL_CTL_NA,
                             DCTT_BYTE_CTL_NA
                             );
          GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

          TestDone = (GlobalError & CPGC_TEST_DONE_MASK) >> 16;
          TestDone = TestDone & ChannelMask;
          ChannelErrors = (GlobalError & CPGC_ERROR_STATUS_MASK);
          ChannelErrors = ChannelErrors & ChannelMask;
          if (GlobalErrorPrevious != GlobalError) {
            GlobalErrorPrevious = GlobalError;
            DcttLogDebug (DcttMain, "GlobalError: 0x%0x\ttestDone: 0x%0x\n", GlobalError, TestDone);
          }

          ProcessErrors = (DcttConfig->dontStopErrors) && ((ChannelErrors & (~ChannelFinish)) != 0);
          if (ProcessErrors) {
            DcttLogDebug (DcttMain, "GlobalError is 0x%x\tchErrors is %d\n", GlobalError, ChannelErrors);

            // TODO: ? - X0 WA: do not take in consideretion errors if logical Rank == 1 because this means that we have wrapped around.
            for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
              ReutRegAddress = DcttGetMcAddressFunc (
                                 DcttMain,
                                 DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_0,
                                 0,
                                 Channel,
                                 DCTT_BYTE_CTL_NA
                                 );
              CurrentAddress = DcttReadReg64Func (DcttMain, ReutRegAddress);

              ErrorRank = Helpers_GetField (
                            CurrentAddress,
                            DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_RANK_ADDRESS_START,
                            DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_RANK_ADDRESS_LEN
                            );

              if (ErrorRank == 1) {
                DcttOutputPrint (DcttMain, "Ignoring errors on Channel %d because it has wrapped around.\n", Channel);
                //We are done with this Channel
                ChannelFinish = ChannelFinish | (1 << Channel);
              }
            }

            ReturnCode = CPGCFunctions_ErrorHandler (
                           DcttMain,
                           (~ChannelFinish),
                           PerBankErrors,
                           GlobalParameters,
                           NULL,
                           NULL
                           );
            if (ReturnCode != DCTT_SUCCESS) {
              return ReturnCode;
            }

            for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
              // Check if we should ignore errors on any of the channels because we are on the last address.
              DimmNumber  = Rank / DCTT_MAX_RANK_IN_DIMM;
              RowSize     = DcttGetRowSizeFunc (DcttMain, 0, Channel, DimmNumber);
              RowSize     = RowSize - 1;
              ColumnSize  = DcttGetColumnSizeFunc (DcttMain, 0, Channel, DimmNumber) - 1;

              DcttLogDebug (
                DcttMain,
                "Channel %d: ChannelFinish is %d, mask is %d ,result is %d\n",
                Channel,
                ChannelFinish,
                (1 << Channel),
                (ChannelErrors & (1 << Channel))
                );

              if (ChannelErrors & (1 << Channel)) {
                // We have an error on this Channel.
                ReutRegAddress = DcttGetMcAddressFunc (
                                   DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_0,
                                   0,
                                   Channel,
                                   DCTT_BYTE_CTL_NA
                                   );
                CurrentAddress = DcttReadReg64Func (DcttMain, ReutRegAddress);

                ErrorBank = Helpers_GetField (
                              CurrentAddress,
                              DCTT_REUT_CH_ERROR_Address_F_BANK_ADDRESS_START,
                              DCTT_REUT_CH_ERROR_Address_F_BANK_ADDRESS_LEN
                              );
                ErrorRow = Helpers_GetField (
                             CurrentAddress,
                             DCTT_REUT_CH_ERROR_Address_F_ROW_ADDRESS_START,
                             DCTT_REUT_CH_ERROR_Address_F_ROW_ADDRESS_LEN
                             );
                ErrorColumn = Helpers_GetField (
                                CurrentAddress,
                                DCTT_REUT_CH_ERROR_Address_F_COL_ADDRESS_START,
                                DCTT_REUT_CH_ERROR_Address_F_COL_ADDRESS_LEN
                                );
                ErrorRank = Helpers_GetField (
                              CurrentAddress,
                              DCTT_REUT_CH_ERROR_Address_F_RANK_ADDRESS_START,
                              DCTT_REUT_CH_ERROR_Address_F_RANK_ADDRESS_LEN
                              );

                ErrorAddress[0] = ErrorColumn;
                ErrorAddress[1] = ErrorRow;
                ErrorAddress[2] = ErrorBank;

                if (TestDirection == UP) {
                  LastAddressPtr   = &(DcttConfig->topAddress[Channel]);
                  FirstAddressPtr  = &(DcttConfig->bottomAddress[Channel]);
                  //RowSize
                  LastAddress[1]   = RowSize;
                  FirstAddress[1]  = FirstAddressPtr->Row;
                  //Column
                  LastAddress[0]   = ColumnSize;
                  FirstAddress[0]  = FirstAddressPtr->Col;
                } else if (TestDirection == DOWN) {
                  LastAddressPtr   = &(DcttConfig->bottomAddress[Channel]);
                  FirstAddressPtr  = &(DcttConfig->topAddress[Channel]);
                  //RowSize
                  FirstAddress[1]  = RowSize;
                  LastAddress[1]   = FirstAddressPtr->Row;
                  //Column
                  FirstAddress[0]  = ColumnSize;
                  LastAddress[0]   = FirstAddressPtr->Col;
                } else {
                  DcttError_Assert (DcttMain,(1 == 0),"Unknown memory traverse Direction");
                  return DCTT_FAIL; // TODO: Check DCTT_FAIL Flow
                }

                if (DcttConfig->runTestPerBank) {
                  LastAddress[2]   = Bank;
                  FirstAddress[2]  = Bank;
                } else {
                  LastAddress[2]   = LastAddressPtr->Bank;
                  FirstAddress[2]  = FirstAddressPtr->Bank;
                }

                if (((LastAddress[2] == ErrorBank)   &&
                     (LastAddress[1] == ErrorRow)     &&
                     (LastAddress[0] == ErrorColumn)) ||
                    (ErrorRank == 1)) {
                  if (ErrorRank == 1) {
                    // Ignoring error because we have wrapped around on this Channel
                    DcttLogDebug (DcttMain, "Ignoring wrapping error\n");
                  }
                  // We are on the last address, stop working on this Channel
                  ChannelFinish = ChannelFinish | (1 << Channel);

                  // Local clear errors
                  ReutRegAddress = DcttGetMcAddressFunc (
                                     DcttMain,
                                     DCTT_REUT_CH_SEQ_CTL,
                                     0,
                                     Channel,
                                     DCTT_BYTE_CTL_NA
                                     );
                  DcttWriteReg32Func (DcttMain, ReutRegAddress, 6);// Local clear errors and stop

                  // Disable this Channel because we won't use it anymore
                  ReutRegAddress = DcttGetMcAddressFunc (
                                     DcttMain,
                                     DCTT_REUT_CH_SEQ_CFG,
                                     0,
                                     Channel,
                                     DCTT_BYTE_CTL_NA
                                     );
                  SeqConfigRegVal = DcttReadReg64Func (DcttMain, ReutRegAddress);
                  // Disable Global Control
                  SeqConfigRegVal = Helpers_SetField (SeqConfigRegVal, 0, 11, 1);
                  DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal);
                  DcttLogDebug (DcttMain,"Reach last address on Channel %d\n", Channel);
                } else {
                  //Change the start address on this Channel
                  _CPGCFunctions_SetTestStartNewAddress (
                    DcttMain,
                    TestDirection,
                    ErrorAddress,
                    LastAddress,
                    FirstAddress,
                    Channel,
                    Rank
                    );
                }
              } else {
                // We do not have an error on this Channel, set new start address == current address
                ReutRegAddress = DcttGetMcAddressFunc (
                                   DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_0,
                                   0,
                                   Channel,
                                   DCTT_BYTE_CTL_NA
                                   );
                CurrentAddress = DcttReadReg64Func (DcttMain, ReutRegAddress);
                ValueIndex = (UINT32*) &CurrentAddress;
                DcttLogDebug (
                  DcttMain,
                  "Didn't found errors on Channel %d. Setting new start address to Hi Val: 0x%0x LoVal: 0x%0x\n",
                  Channel,
                  ValueIndex[1],
                  ValueIndex[0]
                  );

                ReutRegAddress = DcttGetMcAddressFunc (
                                   DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_START,
                                   0,
                                   Channel,
                                   DCTT_BYTE_CTL_NA
                                   );
                DcttWriteReg64Func (DcttMain, ReutRegAddress, CurrentAddress);
              }
            }

            // System hangs when no channels are enabled or if a channel does not exist.
            if ((ChannelFinish & ChannelMask) == ChannelMask) {
              DcttLogDebug (
                DcttMain,
                "Breaking out of test because all of the channels have been tested\n"
                );
              GlobalError = 0;
              break;
            }

            // Start test again
            ReutRegAddress = DcttGetMcAddressFunc (
                               DcttMain,
                               DCTT_REUT_GLOBAL_CTRL,
                               0,
                               DCTT_CHANNEL_CTL_NA,
                               DCTT_BYTE_CTL_NA
                               );
            DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST + 16));
          }
        } while ((TestDone != ChannelMask) || ProcessErrors);

        if ((GlobalError & TestMask) &&
            ((DcttConfig->runTestPerBank))) {
          ReturnCode = CPGCFunctions_ErrorHandler (DcttMain, TestMask, PerBankErrors, GlobalParameters, NULL, NULL);
          if (ReturnCode != DCTT_SUCCESS) {
            return ReturnCode;
          }
          // We have handled errors, so clear them
          GlobalError = 0;
        }
      }
      DcttLogDebug (DcttMain, "GlobalError: 0x%0x\tTestMask: 0x%0x\n", GlobalError, TestMask);

      // This error handling is only used if we are not stopping on errors and
      // we are restarting the error until we hit the nth error
      if ((GlobalError & TestMask) &&
          (!(DcttConfig->dontStopErrors))) {
        ReturnCode = CPGCFunctions_ErrorHandler (DcttMain, TestMask, PerBankErrors, GlobalParameters, NULL, NULL);
        if (ReturnCode != DCTT_SUCCESS) {
          return ReturnCode;
        }
        _CPGCFunctions_UpdateErrorCount (DcttMain, TestMask, Rank, CurrentNumberErrors);
        // TODO: Refactor, next 2 ifs can be compressed to 1.
        if (GlobalError & 1) {
          ReturnCode = _CPGCFunctions_GetExecutionReturnCode (
                         DcttMain,
                         CurrentNumberErrors,
                         0,
                         Rank,
                         ErrorsChannel0
                         );
          if (ReturnCode != CONTINUE) {
            return ReturnCode;
          } else {
            DcttLogDebug (DcttMain, "Hit max errors on Ch 0 Rank %d, disabling it\n", Rank);
            ReutRegAddress = DcttGetMcAddressFunc (
                               DcttMain,
                               DCTT_REUT_CH_SEQ_CFG,
                               0,
                               0,
                               DCTT_BYTE_CTL_NA
                               );
            SeqConfigRegVal = DcttReadReg64Func (DcttMain, ReutRegAddress);
            SeqConfigRegVal = Helpers_SetField ( SeqConfigRegVal, 0, 11, 1);// Disable Global Control
            DcttLogDebug (DcttMain, "TestMask %d\n", TestMask);
            TestMask = TestMask & (~1);
            DcttLogDebug (DcttMain, "New TestMask %d\n", TestMask);
          }
        }
        if (GlobalError & 2) {
          ReturnCode = _CPGCFunctions_GetExecutionReturnCode (
                         DcttMain,
                         CurrentNumberErrors,
                         1,
                         Rank,
                         ErrorsChannel1
                         );
          if (ReturnCode != CONTINUE) {
            return ReturnCode;
          } else {
            DcttLogDebug (DcttMain,  "Hit max errors on Ch 1 Rank %d, disabling it\n", Rank);
            ReutRegAddress = DcttGetMcAddressFunc (
                               DcttMain,
                               DCTT_REUT_CH_SEQ_CFG,
                               0,
                               1,
                               DCTT_BYTE_CTL_NA
                               );
            SeqConfigRegVal = DcttReadReg64Func (DcttMain, ReutRegAddress);
            SeqConfigRegVal = Helpers_SetField ( SeqConfigRegVal, 0, 11, 1);// Disable Global Control
            DcttLogDebug (DcttMain,  "TestMask %d\n", TestMask);
            TestMask = TestMask & (~2);
            DcttLogDebug (DcttMain,  "New TestMask %d\n", TestMask);
          }
        }
        ReutRegAddress = DcttGetMcAddressFunc (
                           DcttMain,
                           DCTT_REUT_GLOBAL_CTRL,
                           0,
                           DCTT_CHANNEL_CTL_NA,
                           DCTT_BYTE_CTL_NA
                           );
        break;
      } else {
        break;
      }
    }
  }

  return DCTT_SUCCESS;
}

#ifndef DISABLE_SECOND_ORDER_TESTS
INT32
CPGCFunctions_CalculateRemainingLoopcount (
  DCTT_API              *DcttMain,
  MemTravDir            TestDirection,
  UINT32                *NewLoopcount,
  DCTT_DIMM_ADDRESS     *CurrentAddress,
  UINT8                 Channel,
  UINT32                HammerRepetitions,
  BOOLEAN               FirstBank,
  BOOLEAN               LastBank,
  BOOLEAN               InitialCalculation
  )
{
  MrcParameters       *MrcData;
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  DCTT_CONFIG_PARAMS  *DcttConfig;
  DCTT_DIMM_ADDRESS   *TopAddressPtr;
  DCTT_DIMM_ADDRESS   *BottomAddressPtr;
  DCTT_DIMM_ADDRESS   *StartAddressPtr;
  DCTT_DIMM_ADDRESS   *EndAddressPtr;
  DCTT_DIMM_ADDRESS   fixedTopAddress;
  DCTT_DIMM_ADDRESS   fixedBottomAddress;
  DCTT_ORDER_NAMES    AddrToDo[DcttLowerOrderLimit];
  DCTT_ORDER_NAMES    AddrRange[DcttLowerOrderLimit];

  DCTT_ORDER_NAMES    FirstOrder;
  DCTT_ORDER_NAMES    SecondOrder;
  UINT64              OverflowCheck;
  UINT32              RemainingCount;
  UINT16              HammerRepetitionsLinear;
  INT8                Direction;
  UINT32              StartAddressFix[DcttLowerOrderLimit];
  UINT32              EndAddressFix[DcttLowerOrderLimit];
  UINT32              OrderIdx;
  BOOLEAN             FixStartAdress;
  BOOLEAN             FixEndAdress;
  UINT32              InternalTopAddressRow;
  UINT32              TopAddressRow;
  UINT32              InternalTopAddressCol;
  UINT32              TopAddressCol;

  MrcData           = DcttMain->MrcData;
  Inputs            = &MrcData->Inputs;
  MrcCall           = Inputs->Call.Func;
  *NewLoopcount     = 0;
  DcttConfig        = &DcttMain->DcttConfigData;
  TopAddressPtr     = &DcttConfig->topAddress[Channel];
  BottomAddressPtr  = &DcttConfig->bottomAddress[Channel];
  FirstOrder        = DcttConfig->firstOrder;
  SecondOrder       = DcttConfig->secondOrder;
  for (OrderIdx = 0; OrderIdx < DcttLowerOrderLimit; OrderIdx++) {
    StartAddressFix[OrderIdx] = 0;
    EndAddressFix[OrderIdx]   = 0;
  }
  DcttLogDebug (DcttMain, "In CPGCFunctions_CalculateRemainingLoopcount\n");
  DcttLogDebug (DcttMain, "Channel: %u\n", Channel);
  DcttLogDebug (DcttMain, "FirstBank: %u, LastBank: %u, InitialCalculation: %u\n", FirstBank, LastBank, InitialCalculation);
  if (FirstBank) {
    if (FirstOrder == DcttOrderColumn) {
      fixedBottomAddress.Row = DcttConfig->internalBottomAddress[Channel].Row;
      fixedBottomAddress.Col = DcttConfig->bottomAddress[Channel].Col;
      if (DcttConfig->internalBottomAddress[Channel].Col > DcttConfig->bottomAddress[Channel].Col) {
        StartAddressFix[DcttOrderColumn] = DcttConfig->internalBottomAddress[Channel].Col - DcttConfig->bottomAddress[Channel].Col;
        StartAddressFix[DcttOrderColumn] = StartAddressFix[DcttOrderColumn] >> CPGC_NUMBER_BITS_CACHELINE;
      }
    } else {
      fixedBottomAddress.Row = DcttConfig->bottomAddress[Channel].Row;
      fixedBottomAddress.Col = DcttConfig->internalBottomAddress[Channel].Col;
      if (DcttConfig->internalBottomAddress[Channel].Row > DcttConfig->bottomAddress[Channel].Row) {
        StartAddressFix[DcttOrderRow] = DcttConfig->internalBottomAddress[Channel].Row - DcttConfig->bottomAddress[Channel].Row;
      }
    }
    BottomAddressPtr = &fixedBottomAddress;
  }

  if (LastBank) {
    if (FirstOrder == DcttOrderColumn) {
      InternalTopAddressRow = DcttConfig->internalTopAddress[Channel].Row;
      TopAddressRow = DcttConfig->topAddress[Channel].Row;
      fixedTopAddress.Row = MIN (InternalTopAddressRow, TopAddressRow);
      fixedTopAddress.Col = DcttConfig->topAddress[Channel].Col;
      if (DcttConfig->topAddress[Channel].Col > DcttConfig->internalTopAddress[Channel].Col) {
        EndAddressFix[DcttOrderColumn] = DcttConfig->topAddress[Channel].Col - DcttConfig->internalTopAddress[Channel].Col;
        EndAddressFix[DcttOrderColumn] = EndAddressFix[DcttOrderColumn] >> CPGC_NUMBER_BITS_CACHELINE;
      }
    } else {
      InternalTopAddressCol = DcttConfig->internalTopAddress[Channel].Col;
      TopAddressCol = DcttConfig->topAddress[Channel].Col;
      fixedTopAddress.Col = MIN (InternalTopAddressCol, TopAddressCol);
      fixedTopAddress.Row = DcttConfig->topAddress[Channel].Row;
      if (DcttConfig->topAddress[Channel].Row > DcttConfig->internalTopAddress[Channel].Row) {
        EndAddressFix[DcttOrderRow] = DcttConfig->topAddress[Channel].Row - DcttConfig->internalTopAddress[Channel].Row;
      }
    }
    TopAddressPtr = &fixedTopAddress;
  }

  DcttError_Assert (DcttMain, (FirstOrder < DcttOrderBank), "Bad First Order Address Type.  Must be DcttOrderRow or DcttOrderColumn");
  DcttError_Assert (DcttMain, (SecondOrder < DcttOrderBank), "Bad First Order Address Type.  Must be DcttOrderRow or DcttOrderColumn");
  if ((FirstOrder > DcttOrderRow) || (SecondOrder > DcttOrderRow)) {
    return DCTT_FAIL;
  }
  //
  // Determine Min/Max of current and top/bottom addresses per up/down direction
  // and get the remaining Row/Col to complete.
  //
  if (TestDirection == UP) {
    AddrToDo[DcttOrderRow] = MIN (CurrentAddress->Row, TopAddressPtr->Row);
    DcttLogDebug (DcttMain, "CurrentAddress->Row: %u\tTopAddressPtr->Row: %u\n", CurrentAddress->Row, TopAddressPtr->Row);
    AddrToDo[DcttOrderRow] = TopAddressPtr->Row - AddrToDo[DcttOrderRow];
    DcttLogDebug (DcttMain, "AddrToDo[DcttOrderRow]: %u\n", AddrToDo[DcttOrderRow]);

    AddrToDo[DcttOrderColumn] = MIN (CurrentAddress->Col, TopAddressPtr->Col);
    DcttLogDebug (DcttMain, "CurrentAddress->Col: %u\tTopAddressPtr->Col: %u\n", CurrentAddress->Col, TopAddressPtr->Col);
    AddrToDo[DcttOrderColumn] = TopAddressPtr->Col - AddrToDo[DcttOrderColumn];
    DcttLogDebug (DcttMain, "AddrToDo[DcttOrderColumn]: %u\n", AddrToDo[DcttOrderColumn]);

    StartAddressPtr = BottomAddressPtr;
    EndAddressPtr   = TopAddressPtr;
    Direction       = 1;
  } else {
    AddrToDo[DcttOrderRow] = MAX (CurrentAddress->Row, BottomAddressPtr->Row);
    DcttLogDebug (DcttMain, "CurrentAddress->Row: %u\tBottomAddressPtr->Row: %u\n", CurrentAddress->Row, BottomAddressPtr->Row);
    AddrToDo[DcttOrderRow] = AddrToDo[DcttOrderRow] - BottomAddressPtr->Row;
    DcttLogDebug (DcttMain, "AddrToDo[DcttOrderRow]: %u\n", AddrToDo[DcttOrderRow]);

    AddrToDo[DcttOrderColumn] = MAX (CurrentAddress->Col, BottomAddressPtr->Col);
    DcttLogDebug (DcttMain, "CurrentAddress->Col: %u\tBottomAddressPtr->Col: %u\n", CurrentAddress->Col, BottomAddressPtr->Col);
    AddrToDo[DcttOrderColumn] = AddrToDo[DcttOrderColumn] - BottomAddressPtr->Col;
    DcttLogDebug (DcttMain, "AddrToDo[DcttOrderColumn]: %u\n", AddrToDo[DcttOrderColumn]);

    StartAddressPtr = TopAddressPtr;
    EndAddressPtr   = BottomAddressPtr;
    Direction       = -1;
  }

  AddrRange[DcttOrderRow] = TopAddressPtr->Row - BottomAddressPtr->Row + 1;
  AddrRange[DcttOrderColumn] = (TopAddressPtr->Col - BottomAddressPtr->Col) >> CPGC_NUMBER_BITS_CACHELINE;
  AddrToDo[DcttOrderColumn]  = AddrToDo[DcttOrderColumn] >> CPGC_NUMBER_BITS_CACHELINE;

  //Fix for start address only if:
  // 1- We are trying to calculate remaining loopcount before starting the test on the bottom address or
  // 2- We are going down to the bottom address and we are not in a middle of completing a second order or
  // 3 -We are going down to the bottom address and we are trying to complete the last second order
  FixStartAdress = ((InitialCalculation && (TestDirection == UP)) ||
                    ((TestDirection == DOWN) && ((AddrToDo[FirstOrder] == 0) || ((AddrToDo[SecondOrder] == 0)))));
  //Fix for end address only if:
  // 1- We are trying to calculate remaining loopcount before starting the test on the top address or
  // 2- We are going up to the top address and we are not in a middle of completing a second order or
  // 3 -We are going up to the top address and we are trying to complete the last second order
  FixEndAdress = ((InitialCalculation && (TestDirection == DOWN)) ||
                  ((TestDirection == UP) && ((AddrToDo[FirstOrder] == 0) || ((AddrToDo[SecondOrder] == 0)))));

  //
  // Correctly update the next starting address.
  // NOTE: AddrToDo[] is one less than the number of addresses to complete since
  // we must include the stop address.
  //
  if ((AddrToDo[FirstOrder]) == 0 && (AddrToDo[SecondOrder] == 0)) {
    RemainingCount = 0;
  } else {
    if (AddrToDo[FirstOrder] == 0) {
      switch (FirstOrder) {
        case DcttOrderColumn:
          CurrentAddress->Col  = StartAddressPtr->Col;
          CurrentAddress->Row += Direction;
          break;

        case DcttOrderRow:
          CurrentAddress->Row  = StartAddressPtr->Row;
          CurrentAddress->Col += (Direction * CPGC_NUMBER_BYTES_CACHELINES);
          break;

        default:
          break;
      }

      AddrToDo[SecondOrder]--;
      AddrToDo[FirstOrder] = AddrRange[FirstOrder];
    } else {
      //
      // Since AddrToDo[FirstOrder] is one less than the true number of addresses to complete,
      // we do not have to adjust for increasing the restart address.
      //
      switch (FirstOrder) {
        case DcttOrderColumn:
          CurrentAddress->Col += (Direction * CPGC_NUMBER_BYTES_CACHELINES);
          break;

        case DcttOrderRow:
          CurrentAddress->Row += Direction;
          break;

        default:
          break;
      }
      AddrToDo[SecondOrder] = 0;
    }

    DcttLogDebug (DcttMain, "Next starting address:\n");
    DcttLogDebug (DcttMain, "CurrentAddress->Col: %u\t CurrentAddress->Row: %u\n",
      CurrentAddress->Col, CurrentAddress->Row);
    DcttLogDebug (DcttMain, "First Order - AddrToDo[%s]: %u\tSecond Order - AddrToDo[%s]: %u\n",
      getMemoryElementName (FirstOrder), AddrToDo[FirstOrder], getMemoryElementName (SecondOrder), AddrToDo[SecondOrder]);
    //
    // Determine the scaling based on address type order.
    // Even though the types are UINT32, we should not overflow the UINT32.
    // Row = 2^17, Col = 2^8, Bank = 2^4.  Bank * Row * Col == 2^29
    //
    RemainingCount   = AddrToDo[FirstOrder];
    RemainingCount  += AddrToDo[SecondOrder] * AddrRange[FirstOrder];
    if (FixStartAdress) {
      DcttLogDebug (DcttMain, "StartAddressFix[FirstOrder]: %u\t RemainingCount: %u\n",
        StartAddressFix[FirstOrder], RemainingCount);
      if (RemainingCount > StartAddressFix[FirstOrder]) {
        RemainingCount -= StartAddressFix[FirstOrder];
      } else {
        RemainingCount = 0;
      }
    }
    if (FixEndAdress) {
      DcttLogDebug (DcttMain, "EndAddressFix[FirstOrder]: %u\t RemainingCount: %u\n",
        EndAddressFix[FirstOrder], RemainingCount);
      if (RemainingCount > EndAddressFix[FirstOrder]) {
        RemainingCount -= EndAddressFix[FirstOrder];
      } else {
        RemainingCount = 0;
      }
    }
    DcttLogDebug (DcttMain, "RemainingCount: %u\tAddrToDo[%s]: %u\tAddrToDo[%s]: %u\tAddrRange[%s]: %u\n",
      RemainingCount, getMemoryElementName (FirstOrder), AddrToDo[FirstOrder], getMemoryElementName (SecondOrder),
      AddrToDo[SecondOrder], getMemoryElementName (SecondOrder), AddrRange[FirstOrder]);
  }

  HammerRepetitionsLinear = 1 << HammerRepetitions;
  OverflowCheck = ((MrcParameters *) DcttMain->MrcData)->Inputs.Call.Func->MrcMultU64x32 (RemainingCount, HammerRepetitionsLinear); // UINT16 * UINT32 will not overflow a UINT64
  DcttLogDebug (DcttMain, "HammerRepetitionsLinear: %u\n", HammerRepetitionsLinear);
  *NewLoopcount = (OverflowCheck > CPGC_MAX_LOOPCOUNT) ? CPGC_MAX_LOOPCOUNT : (UINT32) OverflowCheck;
  DcttLogDebug (DcttMain, "NewLoopcount: %u\n", *NewLoopcount);
  DcttLogDebug (DcttMain, "Leaving CPGCFunctions_CalculateRemainingLoopcount\n");

  return DCTT_SUCCESS;
}


// TODO: Standards
VOID
CPGCFunctions_SetRegistersSequenceHammer (
  DCTT_API                *DcttMain,
  SeqHammerRegisterValues *RegValsStorage,
  TestParameters          *GlobalParams,
  UINT8                   NumberSubsequences
  )
{
  DCTT_CONFIG_PARAMS  *DcttConfig;
  UINT8               Channel;
  UINT32              ReutRegAddress;
  UINT32              newSeqBaseAddrOrderCarryInvertCtlVal;
  UINT32              lastSubseqCtlRegVal;

  DcttError_Assert (DcttMain, GlobalParams->currentDirection == UP, "Currently, only UP direction on sequence hammers is supported");
  DcttOutputPrint (DcttMain, "Setting up registers to force page closes for sequence hammer\n");

  DcttConfig = &DcttMain->DcttConfigData;
  RegValsStorage->subsequenceWait = DcttConfig->subsequenceWait;

  for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    RegValsStorage->seqBaseAddrOrderCarryInvertCtlVal[Channel] = DcttReadReg32Func (DcttMain, ReutRegAddress);
    newSeqBaseAddrOrderCarryInvertCtlVal = RegValsStorage->seqBaseAddrOrderCarryInvertCtlVal[Channel];

    if (DcttConfig->firstOrder == DcttOrderColumn) {
      newSeqBaseAddrOrderCarryInvertCtlVal = (UINT32) Helpers_SetField (
                                                        newSeqBaseAddrOrderCarryInvertCtlVal,
                                                        1,
                                                        DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_COL_BASE_WRAP_CARRY_ENABLE_START,
                                                        DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_COL_BASE_WRAP_CARRY_ENABLE_LEN
                                                        );
    } else if (DcttConfig->firstOrder == DcttOrderRow) {
      newSeqBaseAddrOrderCarryInvertCtlVal = (UINT32) Helpers_SetField (
                                                        newSeqBaseAddrOrderCarryInvertCtlVal,
                                                        1,
                                                        DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_ROW_BASE_WRAP_CARRY_ENABLE_START,
                                                        DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_F_ROW_BASE_WRAP_CARRY_ENABLE_LEN
                                                        );
    } else {
      DcttError_Assert (DcttMain, 1 == 0, "Unsupported first order memory traversing for sequence hammer\n");
    }
    DcttWriteReg32Func (DcttMain, ReutRegAddress, newSeqBaseAddrOrderCarryInvertCtlVal);

    //Incrementing subsequence wait on last subsequence to force page close
    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SUBSEQ_CTL_0,
                       0,
                       Channel,
                       (NumberSubsequences - 1)
                       );

    lastSubseqCtlRegVal = DcttReadReg32Func (DcttMain, ReutRegAddress);

    lastSubseqCtlRegVal = (UINT32) Helpers_SetField (
                                     lastSubseqCtlRegVal,
                                     25,
                                     DCTT_REUT_CH_SUBSEQ_CTL_F_SUBSEQ_WAIT_START,
                                     DCTT_REUT_CH_SUBSEQ_CTL_F_SUBSEQ_WAIT_LEN
                                     );

    DcttWriteReg32Func (DcttMain, ReutRegAddress, lastSubseqCtlRegVal);
  }
}

VOID
CPGCFunctions_RestoreRegistersSequenceHammer (
  DCTT_API                *DcttMain,
  SeqHammerRegisterValues *RegValsStorage
  )
{
  DCTT_CONFIG_PARAMS  *DcttConfig;
  UINT8               Channel;
  UINT32              ReutRegAddress;

  DcttOutputPrint (DcttMain, "Restoring all sequence hammer parameters\n");
  DcttConfig                  = &DcttMain->DcttConfigData;
  DcttConfig->subsequenceWait = RegValsStorage->subsequenceWait;

  for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
    ReutRegAddress = DcttGetMcAddressFunc (
                       DcttMain,
                       DCTT_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL,
                       0,
                       Channel,
                       DCTT_BYTE_CTL_NA
                       );
    DcttWriteReg32Func (DcttMain, ReutRegAddress, RegValsStorage->seqBaseAddrOrderCarryInvertCtlVal[Channel]);
  }
}

#ifndef DISABLE_UNOPTIMIZED_SECOND_ORDER
INT32
CPGCFunctions_ExecuteTestOnSecondOrder (
  DCTT_API        *DcttMain,
  UINT8           NumberSubsequences,
  MemTravDir      TestDirection,
  TestParameters  *GlobalParameters
  )
{
  DCTT_CONFIG_PARAMS  *DcttConfig;
  UINT32              ReutRegAddress;
  UINT8               Channel;
  UINT8               Rank;
  UINT32              Bank;
  UINT32              LastBank;
  UINT32              numberRowBits[DCTT_MAX_NUM_CHANNELS];
  UINT32              numberRows[DCTT_MAX_NUM_CHANNELS];
  UINT32              maxNumberRowsRank;
  UINT32              maxSecondOrderIteration;
  UINT32              minSecondOrderIteration;
  INT32               currentRowOrCol;
  UINT8               ChannelMask;
  INT32               rowOrColIterationStep;
  INT32               rowOrColStart;
  INT32               rowOrColEnd;
  INT32               RetVal;
  UINT32              loopCheckVal;
  UINT64              startAddressRegVal[DCTT_MAX_NUM_CHANNELS];
  UINT64              wrapAddressRegVal[DCTT_MAX_NUM_CHANNELS];

  DcttConfig = &DcttMain->DcttConfigData;
  DcttError_Assert (DcttMain, NumberSubsequences < 8, "Number of subsequences should be less than 8.");
  DcttError_Assert (DcttMain, DcttConfig->OptimizeSecondOrderRun != TRUE, "Second order Optimization uses a different test run function");

  ChannelMask = DCTT_GetChannelMask (DcttMain, 0);

  for (Rank = 0; Rank < DcttConfig->numberRankPerChannel; Rank++) {
    UINT32 TestDone;
    UINT32 ChannelErrors;
    UINT32 GlobalError = 0;
    UINT32 GlobalErrorPrevious = 27;
    UINT8 ChannelsPresentRank;
    UINT8 TestMask;
    UINT8 rankTestMask;

    ChannelsPresentRank = 0;
    TestMask = 0;
    maxNumberRowsRank = 0;

    for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
      UINT64 SeqConfigRegVal = 0; ////TODO: This value can be read from the CPGC register or we can cache it
      UINT32 chErrCtl = DCTT_REUT_CH_ERR_CTL_STOP_NTH_ERROR_SETTING + 1;//n for nth error = 1

      startAddressRegVal[Channel] = 0;
      wrapAddressRegVal[Channel] = 0;

      if (!DCTT_ChannelExists (DcttMain, 0, Channel)) {
        DcttLogDebug (DcttMain, "Channel %d does not exists\n", Channel);
        continue;
      }

      //subsequence start
      SeqConfigRegVal = Helpers_SetField (
                          SeqConfigRegVal,
                          0,
                          DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_START,
                          DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_LEN
                          );
      //subsequence stop
      SeqConfigRegVal = Helpers_SetField (
                          SeqConfigRegVal,
                          NumberSubsequences - 1,
                          DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_START,
                          DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_LEN
                          );
      //Initialization Mode: REUT testing
      SeqConfigRegVal = Helpers_SetField (
                          SeqConfigRegVal,
                          1,
                          DCTT_REUT_CH_SEQ_CFG_F_INITIALIZATION_MODE_START,
                          DCTT_REUT_CH_SEQ_CFG_F_INITIALIZATION_MODE_LEN
                          );

      SeqConfigRegVal = Helpers_SetField (
                          SeqConfigRegVal,
                          1,
                          DCTT_REUT_CH_SEQ_CFG_F_ADDR_UPDATE_RATE_MODE_START,
                          DCTT_REUT_CH_SEQ_CFG_F_ADDR_UPDATE_RATE_MODE_LEN
                          );

      if (DcttConfig->OptimizeSecondOrderRun) {
        SeqConfigRegVal = Helpers_SetField (
                            SeqConfigRegVal,
                            0,
                            DCTT_REUT_CH_SEQ_CFG_F_STOP_BASE_SEQUENCE_WRAP_TRIGGER_START,
                            DCTT_REUT_CH_SEQ_CFG_F_STOP_BASE_SEQUENCE_WRAP_TRIGGER_LEN
                            );
      } else {
        SeqConfigRegVal = Helpers_SetField (
                            SeqConfigRegVal,
                            1,
                            DCTT_REUT_CH_SEQ_CFG_F_STOP_BASE_SEQUENCE_WRAP_TRIGGER_START,
                            DCTT_REUT_CH_SEQ_CFG_F_STOP_BASE_SEQUENCE_WRAP_TRIGGER_LEN
                            );
      }

      SeqConfigRegVal = Helpers_SetField (
                          SeqConfigRegVal,
                          DcttConfig->startTestDelay,
                          DCTT_REUT_CH_SEQ_CFG_F_START_TEST_DELAY_START,
                          DCTT_REUT_CH_SEQ_CFG_F_START_TEST_DELAY_LEN
                          );

#ifndef DISABLE_DUMMY_READS
      if (DcttConfig->enableDummyReads) {
        SeqConfigRegVal = Helpers_SetField (
                            SeqConfigRegVal,
                            1,
                            DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_START,
                            DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_LEN
                            );
      } else
#endif
      {
        SeqConfigRegVal = Helpers_SetField (
                            SeqConfigRegVal,
                            0,
                            DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_START,
                            DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_LEN
                            );
      }

      if (DCTT_RankInChannelExists (DcttMain, 0, Rank, Channel)) {
        UINT8 DimmNumber;
        UINT64 BaseAddressIncCtl;

        BaseAddressIncCtl = 0;

        DcttOutputPrint (DcttMain,"Running Rank %d in Channel %d\n",Rank, Channel);

        ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                           DCTT_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_0, 0, Channel, DCTT_BYTE_CTL_NA);
        DcttWriteReg32Func (DcttMain, ReutRegAddress, Rank);

        ChannelsPresentRank = ChannelsPresentRank + 1;
        DcttLogDebug (DcttMain, "Channel: 0x%0x original TestMask :  0x%0x\n", Channel, TestMask);
        TestMask = (TestMask | (1 << Channel));
        DcttLogDebug (DcttMain, "new TestMask :  0x%0x\n", TestMask);

        //DimmNumber = DcttSysInfo_GetDimmIDFromLogicalRank (DcttMain, 0, Channel, Rank);
        DimmNumber          = Rank / DCTT_MAX_RANK_IN_DIMM;
        numberRows[Channel] = DcttGetRowSizeFunc (DcttMain, 0, Channel, DimmNumber);
        numberRows[Channel] = numberRows[Channel] - 1;
        numberRowBits[Channel] = Helpers_Log2 (numberRows[Channel]);
        numberRowBits[Channel] = numberRowBits[Channel] - 1;
        if (numberRows[Channel] > maxNumberRowsRank) {
          DcttLogDebug (
            DcttMain,
            "Found new max number of rows in Channel %d, Rank %d. It is now %d\n",
            Channel,
            Rank,
            numberRows[Channel]);

          maxNumberRowsRank = numberRows[Channel];
        }

        DcttLogDebug (DcttMain, "Number of rows in Rank %d in Channel %d is %d\n",
          Rank,
          Channel,
          numberRows[Channel]);

        ////TODO:Check for Refactor. I think this function can be simpler in this case
        ////Refactor needs to be done after we got rid of the more complex run test

        ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                           DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL, 0, Channel, DCTT_BYTE_CTL_NA);
        ////TODO: Delete any previous write to BaseAddressIncCtl because we are overwriting it now.
        DcttLogDebug (DcttMain, "Number bits row: %d\n", numberRowBits[Channel]);
        ////TODO: Next If can be simplified once we set traversing order only on rows and columns
        if ((DcttConfig->firstOrder == DcttOrderColumn) && (DcttConfig->secondOrder == DcttOrderRow)) {
          ////TODO: DELETE Next SetFieldValue is not needed
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                CPGC_NUMBER_BITS_COL,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_LEN);

          if (TestDirection == UP) {
            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  1,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN);

            wrapAddressRegVal[Channel] = Helpers_SetField (
                                           wrapAddressRegVal[Channel],
                                           CPGC_NUMBER_COLS,
                                           DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_START,
                                           DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_LEN);
          } else if (TestDirection == DOWN) {
            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  (UINT32) -1,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN);

            startAddressRegVal[Channel] = Helpers_SetField (
                                            startAddressRegVal[Channel],
                                            CPGC_NUMBER_COLS,
                                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN);
          } else {
            DcttError_Assert (DcttMain, 1==0, "Unknown test direction.");
          }

        } else if ((DcttConfig->firstOrder == DcttOrderRow) && (DcttConfig->secondOrder == DcttOrderColumn)) {
          ////TODO: DELETE Next SetFieldValue is not needed
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                numberRowBits[Channel],
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_UPDATE_RATE_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_UPDATE_RATE_LEN);

          if (TestDirection == UP) {
            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  1,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN);

            wrapAddressRegVal[Channel] = Helpers_SetField (
                                           wrapAddressRegVal[Channel],
                                           numberRows[Channel],
                                           DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_START,
                                           DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_LEN);

          } else if (TestDirection == DOWN) {
            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  (UINT32) -1,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN);

            startAddressRegVal[Channel] = Helpers_SetField (
                                            startAddressRegVal[Channel],
                                            numberRows[Channel],
                                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);
          } else {
            DcttError_Assert (DcttMain, 1==0, "Unknown test direction.");
          }
        } else {
          DcttError_Assert (DcttMain,
            (1 == 0),
            "Unsupported memory traversing order. Order 0: %d, Order 1: %d, Order 2: %d, Order 3: %d",
            DcttConfig->firstOrder,
            DcttConfig->secondOrder,
            DcttConfig->thirdOrder,
            DcttConfig->fourthOrder);
        }
        DcttWriteReg64Func (DcttMain, ReutRegAddress, BaseAddressIncCtl);
        ////End check for Refactor

        SeqConfigRegVal = Helpers_SetField (
                            SeqConfigRegVal,
                            1,
                            DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                            DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Enable Global Control
      } else {
        DcttLogDebug (DcttMain, "Will not run Rank %d in Channel %d\n",Rank, Channel);

        //We are not going to run the test on this Channel
        SeqConfigRegVal = Helpers_SetField (
                            SeqConfigRegVal,
                            0,
                            DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                            DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Disable Global Control
      }

      ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                         DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
      DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal);

      ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                         DCTT_REUT_CH_ERR_CTL, 0, Channel, DCTT_BYTE_CTL_NA);

      DcttWriteReg32Func (DcttMain, ReutRegAddress, chErrCtl);//Stop on nth error
    }

    if (ChannelsPresentRank == 0) {
      //No Channel has this Rank, continue
      DcttLogDebug (DcttMain,  "Will completely skip Rank %d\n",Rank);
      continue;
    }

    //Running test per Row
    //Right now we are only supporting same start and stop address Bank on all channels
    //Checking if that is true
    for (Channel = 1; Channel < DCTT_MAX_NUM_CHANNELS; Channel++) {
      DcttError_Assert (DcttMain,
        (DcttConfig->bottomAddress[0].Bank == DcttConfig->bottomAddress[Channel].Bank),
        "Start Address Bank has to be the same on all channels\n");
      DcttError_Assert (DcttMain,
        (DcttConfig->topAddress[0].Bank == DcttConfig->topAddress[Channel].Bank),
        "Start Address Bank has to be the same on all channels\n");
    }
    LastBank = (DcttConfig->topAddress[0].Bank) + 1;

    if (DcttConfig->secondOrder == DcttOrderColumn) {
      minSecondOrderIteration = 0;
      maxSecondOrderIteration = CPGC_NUMBER_COLS;
      rowOrColIterationStep = 8;
    } else if (DcttConfig->secondOrder == DcttOrderRow) {
      minSecondOrderIteration = 0;
      maxSecondOrderIteration = maxNumberRowsRank;
      rowOrColIterationStep = 1;
    } else {
      DcttError_Assert (DcttMain, 1 == 0, "Bad second order iteration value on per row/column test.\n");
      return DCTT_FAIL;  // TODO: Check DCTT_FAIL condition
    }

    if (TestDirection == UP) {
      rowOrColStart = minSecondOrderIteration;
      rowOrColEnd = maxSecondOrderIteration + rowOrColIterationStep;
    } else if (TestDirection == DOWN) {
      rowOrColEnd = minSecondOrderIteration - rowOrColIterationStep;
      rowOrColStart = maxSecondOrderIteration;
      rowOrColIterationStep = rowOrColIterationStep * -1;
    } else {
      DcttError_Assert (DcttMain, 1 == 0, "Unknown direction selected.\n");
      return DCTT_FAIL; // TODO: Check DCTT_FAIL condition
    }

    rankTestMask = TestMask;

    for (Bank = 0; Bank < LastBank; Bank++) {
      UINT32 PerBankErrors[DCTT_MAX_NUM_CHANNELS];

      loopCheckVal = 0;

      DcttOutputPrint (DcttMain, "Running test on Bank %d\n",Bank);

      for (Channel = 0; Channel < DcttConfig->numberChannels; Channel ++) {
        UINT64 seqCfgRegValue;

        PerBankErrors[Channel] = 0;

        startAddressRegVal[Channel] = Helpers_SetField (
                                        startAddressRegVal[Channel],
                                        Bank,
                                        DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_START,
                                        DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_LEN);


        wrapAddressRegVal[Channel] = Helpers_SetField (
                                       wrapAddressRegVal[Channel],
                                       Bank,
                                       DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_BANK_ADDRESS_START,
                                       DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_BANK_ADDRESS_LEN);

        if ((TestDirection == DOWN) && (DcttConfig->secondOrder == DcttOrderRow)) {
          //In this case we are going to start the test with all channels disabled and only enable
          //them when we get to the desired row
          DcttOutputPrint (DcttMain, "Disabling Channel %d because direction is down\n",Channel);
          TestMask = (TestMask & (~(1 << Channel)));//(TestMask | (1 << Channel));
          ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                             DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
          seqCfgRegValue = DcttReadReg64Func (DcttMain, ReutRegAddress);
          seqCfgRegValue = Helpers_SetField (
                             seqCfgRegValue,
                             0,
                             DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                             DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Disable Global Control
          DcttWriteReg64Func (DcttMain, ReutRegAddress, seqCfgRegValue);
        } else if (rankTestMask & (1 << Channel)) {
          DcttOutputPrint (DcttMain, "Enabling Channel %d\n",Channel);
          TestMask = (TestMask | (1 << Channel));
          ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                             DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
          seqCfgRegValue = DcttReadReg64Func (DcttMain, ReutRegAddress);
          seqCfgRegValue = Helpers_SetField (
                             seqCfgRegValue,
                             1,
                             DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                             DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Enable Global Control
          DcttWriteReg64Func (DcttMain, ReutRegAddress, seqCfgRegValue);
        }
      }

      // @todo Check if we can change this loop condition
      for (currentRowOrCol = rowOrColStart; currentRowOrCol != rowOrColEnd; currentRowOrCol += rowOrColIterationStep) {
        for (Channel = 0; Channel < DcttConfig->numberChannels; Channel ++) {
          if (DcttConfig->secondOrder == DcttOrderRow) {
            startAddressRegVal[Channel] = Helpers_SetField (
                                            startAddressRegVal[Channel],
                                            currentRowOrCol,
                                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);

            wrapAddressRegVal[Channel] = Helpers_SetField (
                                           wrapAddressRegVal[Channel],
                                           currentRowOrCol,
                                           DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_START,
                                           DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_LEN);
          } else if (DcttConfig->secondOrder == DcttOrderColumn) {
            startAddressRegVal[Channel] = Helpers_SetField (
                                            startAddressRegVal[Channel],
                                            currentRowOrCol,
                                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                            DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN);

            wrapAddressRegVal[Channel] = Helpers_SetField (
                                           wrapAddressRegVal[Channel],
                                           currentRowOrCol,
                                           DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_START,
                                           DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_LEN);
          } else {
            DcttError_Assert (DcttMain, 1 == 0, "non-supported second order %d.", DcttConfig->secondOrder);
          }

          ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                             DCTT_REUT_CH_SEQ_BASE_ADDR_START, 0, Channel, DCTT_BYTE_CTL_NA);
          DcttWriteReg64Func (DcttMain, ReutRegAddress, startAddressRegVal[Channel]);

          if (!(DcttConfig->OptimizeSecondOrderRun)) {
            ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP, 0, Channel, DCTT_BYTE_CTL_NA);
            DcttWriteReg64Func (DcttMain, ReutRegAddress, wrapAddressRegVal[Channel]);
          }

          if ((TestDirection == DOWN) && (DcttConfig->secondOrder == DcttOrderRow) && (!(TestMask & (1 << Channel)))) {
            //test if we should enable this Channel or not
            if ((currentRowOrCol <= (INT32) numberRows[Channel]) && (rankTestMask & (1 << Channel))) {
              UINT64 seqCfgRegValue;
              DcttOutputPrint (DcttMain, "Enabling Channel %d on row or column %d\n", Channel, currentRowOrCol);
              //Enabling Channel where we hit max address
              DcttLogDebug (DcttMain, "Channel: 0x%0x TestMask :  0x%0x\n", Channel, TestMask);
              TestMask = (TestMask | (1 << Channel));
              DcttLogDebug (DcttMain, "new TestMask :  0x%0x\n", TestMask);

              ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                 DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
              seqCfgRegValue = DcttReadReg64Func (DcttMain, ReutRegAddress);
              seqCfgRegValue = Helpers_SetField (
                                 seqCfgRegValue,
                                 1,
                                 DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                 DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Enable Global Control
              DcttWriteReg64Func (DcttMain, ReutRegAddress, seqCfgRegValue);
            }
          }
        }

        DcttError_Assert (DcttMain, TestMask != 0, "We are trying to run a test with no channels enabled.");

        ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                           DCTT_REUT_GLOBAL_CTRL, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
        DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST));

        do{
          ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                             DCTT_REUT_GLOBAL_ERR, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
          GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

          TestDone = (GlobalError & CPGC_TEST_DONE_MASK) >> 16;
          TestDone = TestDone & ChannelMask;
          ChannelErrors = (GlobalError & CPGC_ERROR_STATUS_MASK);
          ChannelErrors = ChannelErrors & ChannelMask;
          if (GlobalErrorPrevious != GlobalError) {
            GlobalErrorPrevious = GlobalError;
            DcttLogDebug (DcttMain, "GlobalError:  0x%0x   TestDone:  0x%0x\n", GlobalError, TestDone);
          }
        }while ((TestDone != ChannelMask));

        if (ChannelErrors & TestMask) {
          RetVal = CPGCFunctions_ErrorHandler (DcttMain, TestMask, PerBankErrors, GlobalParameters, NULL, NULL);
          if (RetVal != DCTT_SUCCESS) {
            return RetVal;
          }
        }

        if ((DcttConfig->secondOrder == DcttOrderRow) && (TestDirection == UP)) {
          //Checking if we have overflow any of the channels were we are running the test.
          for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
            if ((currentRowOrCol >= (INT32) numberRows[Channel]) && (TestMask & (1 << Channel))) {
              UINT64 seqCfgRegValue;
              DcttOutputPrint (DcttMain, "Disabling Channel %d on row or column %d\n", Channel, currentRowOrCol);
              //Disabling Channel where we hit max address
              DcttLogDebug (DcttMain, "Channel: 0x%0x TestMask :  0x%0x\n", Channel, TestMask);
              TestMask = (TestMask & (~(1 << Channel)));
              DcttLogDebug (DcttMain, "new TestMask :  0x%0x\n", TestMask);

              ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                 DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
              seqCfgRegValue = DcttReadReg64Func (DcttMain, ReutRegAddress);
              seqCfgRegValue = Helpers_SetField (
                                 seqCfgRegValue,
                                 0,
                                 DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                 DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Disable Global Control
              DcttWriteReg64Func (DcttMain, ReutRegAddress, seqCfgRegValue);
            }
          }

        }

        loopCheckVal++;
        DcttError_Assert (DcttMain,
          loopCheckVal < 65536,
          "Exceeded maximum number of loops (65536) on memory test. Current loop is %d\n",
          loopCheckVal);
      }
    }
  }

  return DCTT_SUCCESS;
}
#endif

/*
  This function executes tests for Pause Refresh, Row Hammers, and margining.

  This function assumes the column sizes are the same across channels.
*/
INT32
CPGCFunctions_ExecuteTestOnSecondOrderOptimized (
  DCTT_API            *DcttMain,
  UINT8               NumberSubsequences,
  MemTravDir          TestDirection,
  UINT32              HammerRepetitions,
  RunTestSymbolTypes  RunnerType,
  VOID                *RunnerParameters,
  TestParameters      *GlobalParameters
  )
{
  DCTT_CONFIG_PARAMS  *DcttConfig;
  DelayTime           PauseRefreshCalc;
  DCTT_DIMM_ADDRESS   CurrentAddress[DCTT_MAX_NUM_CHANNELS];
  UINT64              CurrentAddressRegVal;
  UINT32              ReutRegAddress;
  UINT32              wrapAddressREUTregAddress;
  UINT64              modifiedWrapAddress;
  UINT64              startAddressRegVal[DCTT_MAX_NUM_CHANNELS];
  UINT64              wrapAddressRegVal[DCTT_MAX_NUM_CHANNELS];
  UINT64              SeqConfigRegVal[DCTT_MAX_NUM_CHANNELS];
  UINT64              BaseAddressIncCtl;
  UINT32              numberRowBits[DCTT_MAX_NUM_CHANNELS];
  UINT32              numberRows[DCTT_MAX_NUM_CHANNELS];
  UINT32              LastRowAddr[DCTT_MAX_NUM_CHANNELS];
  UINT32              NumberColBits[DCTT_MAX_NUM_CHANNELS];
  UINT32              numberCols[DCTT_MAX_NUM_CHANNELS];
  UINT32              LastColAddr[DCTT_MAX_NUM_CHANNELS];
  UINT32              NumCacheLinesPerPage[DCTT_MAX_NUM_CHANNELS];
  UINT32              NewLoopcount[DCTT_MAX_NUM_CHANNELS];
  UINT32              PerBankErrors[DCTT_MAX_NUM_CHANNELS];
  UINT32              TestDone;
  UINT32              ChannelErrors;
  UINT32              chErrCtl;
  UINT32              GlobalError;
  UINT32              globalErrRegValPrev;
  UINT32              Bank;
  UINT32              LastBank;
  UINT32              MemoryFrequency;
  UINT32              HammerRepLinear;
  UINT8               Channel;
  UINT8               ChannelMask;
  UINT8               ChannelsPresentRank;
  UINT8               Rank;
  UINT8               rankTestMask;
  UINT8               DimmNumber;
  UINT8               TestMask;
  INT32               RetVal;
  UINT8               origRankTestMask;
  BOOLEAN             firstBankToTest[DCTT_MAX_NUM_CHANNELS];
  BOOLEAN             lastBankToTest[DCTT_MAX_NUM_CHANNELS];
  DCTT_DIMM_ADDRESS   dummyCurrentAddress;
  UINT32              CPGHammerRepetitions;

  DcttLogDebug (DcttMain, "ExecuteTest\n");
  DcttError_Assert (DcttMain, NumberSubsequences < 8, "Number of subsequences should be less than 8.");

  DcttConfig  = &DcttMain->DcttConfigData;
  RetVal      = DCTT_SUCCESS;
  //
  // Initializing Variables
  //
  CPGHammerRepetitions = 0;
  for (Channel = 0; Channel < DCTT_MAX_NUM_CHANNELS; Channel++) {
    numberRowBits[Channel] = 0;
    numberRows[Channel] = 0;
    NumberColBits[Channel] = 0;
    numberCols[Channel] = 0;
    firstBankToTest[Channel] = FALSE;
    lastBankToTest[Channel] = FALSE;
  }
  CPGHammerRepetitions = HammerRepetitions;
  chErrCtl = DCTT_REUT_CH_ERR_CTL_STOP_NTH_ERROR_SETTING + 1; // Stop on first error
  HammerRepLinear = (1 << CPGHammerRepetitions);
  MemoryFrequency = DcttGetMcFrequencyFunc (DcttMain, 0);
  DcttLogDebug (DcttMain, "MemoryFrequency: %u\n", MemoryFrequency);
  ChannelMask = DCTT_GetChannelMask (DcttMain, 0);
  //
  // Skipping the column init until we get the column size later in the loop.
  //
  DelayTime_Init (&PauseRefreshCalc, MemoryFrequency, 50, 0, DCTT_SYS_MIN_DELAY_FS);

  for (Rank = 0; ((Rank < DcttConfig->numberRankPerChannel) && (RetVal == DCTT_SUCCESS)); Rank++) {
    GlobalError = 0;
    globalErrRegValPrev = 27;
    ChannelsPresentRank = 0;
    TestMask = 0;

    for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
      SeqConfigRegVal[Channel] = 0;
      startAddressRegVal[Channel] = 0;
      wrapAddressRegVal[Channel] = 0;

      if (!DCTT_ChannelExists (DcttMain, 0, Channel)) {
        DcttLogDebug (DcttMain, "Channel %d does not exists\n", Channel);
        continue;
      }

      //subsequence start
      SeqConfigRegVal[Channel] = Helpers_SetField (
                                   SeqConfigRegVal[Channel],
                                   0,
                                   DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_START,
                                   DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_LEN);
      //subsequence stop
      SeqConfigRegVal[Channel] = Helpers_SetField (
                                   SeqConfigRegVal[Channel],
                                   NumberSubsequences - 1,
                                   DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_START,
                                   DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_LEN);
      //Initialization Mode: REUT testing
      SeqConfigRegVal[Channel] = Helpers_SetField (
                                   SeqConfigRegVal[Channel],
                                   1,
                                   DCTT_REUT_CH_SEQ_CFG_F_INITIALIZATION_MODE_START,
                                   DCTT_REUT_CH_SEQ_CFG_F_INITIALIZATION_MODE_LEN);

      SeqConfigRegVal[Channel] = Helpers_SetField (
                                   SeqConfigRegVal[Channel],
                                   1,
                                   DCTT_REUT_CH_SEQ_CFG_F_ADDR_UPDATE_RATE_MODE_START,
                                   DCTT_REUT_CH_SEQ_CFG_F_ADDR_UPDATE_RATE_MODE_LEN);

      SeqConfigRegVal[Channel] = Helpers_SetField (
                                   SeqConfigRegVal[Channel],
                                   0,
                                   DCTT_REUT_CH_SEQ_CFG_F_STOP_BASE_SEQUENCE_WRAP_TRIGGER_START,
                                   DCTT_REUT_CH_SEQ_CFG_F_STOP_BASE_SEQUENCE_WRAP_TRIGGER_LEN);

      SeqConfigRegVal[Channel] = Helpers_SetField (
                                   SeqConfigRegVal[Channel],
                                   DcttConfig->startTestDelay,
                                   DCTT_REUT_CH_SEQ_CFG_F_START_TEST_DELAY_START,
                                   DCTT_REUT_CH_SEQ_CFG_F_START_TEST_DELAY_LEN);

#ifndef DISABLE_DUMMY_READS
      if (DcttConfig->enableDummyReads) {
        SeqConfigRegVal[Channel] = Helpers_SetField (
                                     SeqConfigRegVal[Channel],
                                     1,
                                     DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_START,
                                     DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_LEN);
      } else
#endif
      {
        SeqConfigRegVal[Channel] = Helpers_SetField (
                                     SeqConfigRegVal[Channel],
                                     0,
                                     DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_START,
                                     DCTT_REUT_CH_SEQ_CFG_F_ENABLE_DUMMY_READS_LEN);
      }

      if (DCTT_RankInChannelExists (DcttMain, 0, Rank, Channel)) {
        BaseAddressIncCtl = 0;

        DcttOutputPrint (DcttMain,"Running Rank %d in Channel %d\n",Rank, Channel);

        ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                           DCTT_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_0, 0, Channel, DCTT_BYTE_CTL_NA);
        DcttWriteReg32Func (DcttMain, ReutRegAddress, Rank);

        ChannelsPresentRank = ChannelsPresentRank + 1;
        DcttLogDebug (DcttMain, "Channel: 0x%0x original TestMask :  0x%0x\n", Channel, TestMask);
        TestMask = (TestMask | (1 << Channel));
        DcttLogDebug (DcttMain, "new TestMask :  0x%x\n", TestMask);

        //DimmNumber = DcttSysInfo_GetDimmIDFromLogicalRank (DcttMain, 0, Channel, Rank);
        DimmNumber          = Rank / DCTT_MAX_RANK_IN_DIMM;
        numberRows[Channel] = DcttGetRowSizeFunc (DcttMain, 0, Channel, DimmNumber);
        LastRowAddr[Channel] = numberRows[Channel] - 1;
        numberRowBits[Channel] = Helpers_Log2 (LastRowAddr[Channel]);
        numberCols[Channel] = DcttGetColumnSizeFunc (DcttMain, 0, Channel, DimmNumber);
        LastColAddr[Channel] = numberCols[Channel] - CPGC_NUMBER_BYTES_CACHELINES;
        NumberColBits[Channel] = Helpers_Log2 (LastColAddr[Channel]);
        NumCacheLinesPerPage[Channel] = (numberCols[Channel]) >> CPGC_NUMBER_BITS_CACHELINE;

        //
        // Update the column information for the Pause Refresh
        // TODO: This is occuring twice, but the number of columns should be the same for both channels
        //
        DelayTime_UpdateCacheLinesPerCol (&PauseRefreshCalc, numberCols[Channel]);

        DcttLogDebug (
          DcttMain,
          "Channel %d, Rank %d: Number of %ss [%d], %s bits [%d]\n",
          Channel,
          Rank,
          "Row",
          numberRows[Channel],
          "Row",
          numberRowBits[Channel]
          );
        DcttLogDebug (
          DcttMain,
          "Channel %d, Rank %d: Number of %ss [%d], %s bits [%d]\n",
          Channel,
          Rank,
          "Column",
          numberCols[Channel],
          "Column",
          NumberColBits[Channel]
          );
        DcttLogDebug (DcttMain, "ETOSOO Init LC[C.%d]: 0x%x\n", Channel, NewLoopcount[Channel]);

        //
        // Adjust number of column bits to account for cache line size
        //
        NumberColBits[Channel] -= CPGC_NUMBER_BITS_CACHELINE;


        // TODO:Check for Refactor. I think this function can be simpler in this case
        ////Refactor needs to be done after we got rid of the more complex run test

        ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                           DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL, 0, Channel, DCTT_BYTE_CTL_NA);
        // TODO: Delete any previous write to BaseAddressIncCtl because we are overwriting it now.

        // TODO: Next If can be simplified once we set traversing order only on rows and columns
        if (TestDirection == UP) {
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN);

          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN);

          wrapAddressRegVal[Channel] = Helpers_SetField (
                                         wrapAddressRegVal[Channel],
                                         LastColAddr[Channel],
                                         DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_START,
                                         DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_LEN);

          wrapAddressRegVal[Channel] = Helpers_SetField (
                                         wrapAddressRegVal[Channel],
                                         LastRowAddr[Channel],
                                         DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_START,
                                         DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_LEN);

          CurrentAddress[Channel].Row = DcttConfig->bottomAddress[Channel].Row;
          CurrentAddress[Channel].Col = DcttConfig->bottomAddress[Channel].Col;
        } else if (TestDirection == DOWN) {
          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                (UINT32) -1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN);

          BaseAddressIncCtl = Helpers_SetField (
                                BaseAddressIncCtl,
                                (UINT32) -1,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                                DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN);

          startAddressRegVal[Channel] = Helpers_SetField (
                                          startAddressRegVal[Channel],
                                          LastColAddr[Channel],
                                          DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                          DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN);

          startAddressRegVal[Channel] = Helpers_SetField (
                                          startAddressRegVal[Channel],
                                          LastRowAddr[Channel],
                                          DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                          DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);

          CurrentAddress[Channel].Row = DcttConfig->topAddress[Channel].Row;
          CurrentAddress[Channel].Col = DcttConfig->topAddress[Channel].Col;
        } else {
          DcttError_Assert (DcttMain, 1==0, "Unknown test direction.");
        }

        if ((DcttConfig->firstOrder == DcttOrderColumn) && (DcttConfig->secondOrder == DcttOrderRow)) {
          DcttError_Assert (DcttMain, CPGHammerRepetitions <= CPGC_MAX_COL_UPDATE_RATE,
            "Maximum update rate for hammer repetitions with column on order 1 is %d. Received: %d",
            CPGC_MAX_COL_UPDATE_RATE,
            CPGHammerRepetitions);

          if (CPGHammerRepetitions > 0) {
            wrapAddressREUTregAddress = DcttGetMcAddressFunc (DcttMain,
                                          DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP, 0, Channel, DCTT_BYTE_CTL_NA);
            modifiedWrapAddress = DcttReadReg64Func (DcttMain, wrapAddressREUTregAddress);
            modifiedWrapAddress = Helpers_SetField (
                                    modifiedWrapAddress,
                                    numberRows[Channel],
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_START,
                                    DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_LEN);
            DcttWriteReg64Func (DcttMain, wrapAddressREUTregAddress, modifiedWrapAddress);

            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  0,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_LEN);

            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  CPGHammerRepetitions,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_UPDATE_RATE_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_UPDATE_RATE_LEN);

            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  0,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN);
          } else {
            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  NumberColBits[Channel],
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_LEN);

            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  0,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_UPDATE_RATE_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_UPDATE_RATE_LEN);
          }
        } else if ((DcttConfig->firstOrder == DcttOrderRow) && (DcttConfig->secondOrder == DcttOrderColumn)) {
          DcttError_Assert (DcttMain, CPGHammerRepetitions <= CPGC_MAX_ROW_UPDATE_RATE,
            "Maximum update rate for hammer repetitions with row on order 1 is %d. Received: %d",
            CPGC_MAX_ROW_UPDATE_RATE,
            CPGHammerRepetitions);

          if (CPGHammerRepetitions > 0) {
            DcttError_Assert (DcttMain, (1 == 0),"Cannot run Sequence hammer test with columns on the second order because of workaround");

            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  0,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_UPDATE_RATE_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_UPDATE_RATE_LEN);

            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  CPGHammerRepetitions,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_LEN);

            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  0,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN);
          } else {
            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  numberRowBits[Channel],
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_UPDATE_RATE_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_UPDATE_RATE_LEN);

            BaseAddressIncCtl = Helpers_SetField (
                                  BaseAddressIncCtl,
                                  0,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_START,
                                  DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_LEN);
          }
        } else {
          DcttError_Assert (DcttMain,
            (1 == 0),
            "Unsupported memory traversing order. Order 0: %d, Order 1: %d, Order 2: %d, Order 3: %d",
            DcttConfig->firstOrder,
            DcttConfig->secondOrder,
            DcttConfig->thirdOrder,
            DcttConfig->fourthOrder);
        }
        DcttWriteReg64Func (DcttMain, ReutRegAddress, BaseAddressIncCtl);
        ////End check for Refactor

        SeqConfigRegVal[Channel] = Helpers_SetField (
                                     SeqConfigRegVal[Channel],
                                     1,
                                     DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                     DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Enable Global Control
      } else {
        DcttLogDebug (DcttMain, "Will not run Rank %d in Channel %d\n",Rank, Channel);

        //We are not going to run the test on this Channel
        SeqConfigRegVal[Channel] = Helpers_SetField (
                                     SeqConfigRegVal[Channel],
                                     0,
                                     DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                     DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Disable Global Control
      }

      ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                         DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
      DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal[Channel]);

      ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                         DCTT_REUT_CH_ERR_CTL, 0, Channel, DCTT_BYTE_CTL_NA);

      DcttWriteReg32Func (DcttMain, ReutRegAddress, chErrCtl);//Stop on nth error
    }

    if (ChannelsPresentRank == 0) {
      //No Channel has this Rank, continue
      DcttLogDebug (DcttMain,  "Will completely skip Rank %d\n",Rank);
      continue;
    }

    LastBank = (DcttConfig->topAddress[0].Bank);
    //Running test per Bank
    //Right now we are only supporting same start and stop address Bank on all channels
    //Checking if that is true
    for (Channel = 1; Channel < DCTT_MAX_NUM_CHANNELS; Channel++) {
      if (DcttConfig->SubMemoryRangeTest == FALSE) {
        DcttError_Assert (DcttMain,
          (DcttConfig->bottomAddress[0].Bank == DcttConfig->bottomAddress[Channel].Bank),
          "Start Address Bank has to be the same on all channels\n");
        DcttError_Assert (DcttMain,
          (DcttConfig->topAddress[0].Bank == DcttConfig->topAddress[Channel].Bank),
          "Stop Address Bank has to be the same on all channels\n");
      } else {
        if (DcttConfig->topAddress[Channel].Bank > LastBank) {
          LastBank = DcttConfig->topAddress[Channel].Bank;
        }
      }
    }
    LastBank++;

    rankTestMask = TestMask;
    origRankTestMask = rankTestMask;

    for (Bank = 0; ((Bank < LastBank) && (RetVal == DCTT_SUCCESS)); Bank++) {
      if ((DcttConfig->SubMemoryRangeTest == FALSE) && ((1 << Bank) & (DcttConfig->BankDisableMask))) {
        DcttOutputPrint (DcttMain, "Skipping Bank %d\n",Bank);
        continue;
      } else if (DcttConfig->SubMemoryRangeTest == TRUE) {
        rankTestMask = origRankTestMask;
        for (Channel = 0; Channel < DCTT_MAX_NUM_CHANNELS; Channel++) {
          lastBankToTest[Channel] = FALSE;
          firstBankToTest[Channel] = FALSE;
          if ((Bank == DcttConfig->topAddress[Channel].Bank) && (Rank == DcttConfig->topAddress[Channel].Rank)) {
            lastBankToTest[Channel] = TRUE;
          }
          if ((Bank == DcttConfig->bottomAddress[Channel].Bank) && (Rank == DcttConfig->bottomAddress[Channel].Rank)) {
            firstBankToTest[Channel] = TRUE;
          }
          if ((Bank > DcttConfig->topAddress[Channel].Bank) || (Bank < DcttConfig->bottomAddress[Channel].Bank)) {
            rankTestMask &= ~(1 << Channel);
            DcttOutputPrint (DcttMain, "Skipping Bank %d on Channel %d\n", Bank, Channel);
          }
        }
        if (rankTestMask == 0) {
          DcttOutputPrint (DcttMain, "Completely Skipping Bank\n");
          continue;
        } else {
          DcttOutputPrint (DcttMain, "Running Test on Bank %d\n", Bank);
        }
        TestMask &= rankTestMask;
      } else {
        DcttOutputPrint (DcttMain, "Running test on Bank %d\n", Bank);
      }

      for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
        PerBankErrors[Channel] = 0;

        //
        // Set initial loopcount based on DIMM size.
        //
        NewLoopcount[Channel]  = NumCacheLinesPerPage[Channel];
        NewLoopcount[Channel] *= (numberRows[Channel]);

        if (DcttConfig->firstOrder == DcttOrderRow) {
          DcttError_Assert (
            DcttMain,
            (CPGC_MAX_LOOPCOUNT - numberRows[Channel]) >= HammerRepLinear,
            "Maximum loopcount for hammer repetitions with %ss on order 1 is %u. Avaliable Loopcount: %u",
            "Row",
            CPGC_MAX_LOOPCOUNT,
            (CPGC_MAX_LOOPCOUNT - numberRows[Channel])
            );
        } else if (DcttConfig->firstOrder == DcttOrderColumn) {
          DcttError_Assert (
            DcttMain,
            (CPGC_MAX_LOOPCOUNT - numberCols[Channel]) >= HammerRepLinear,
            "Maximum loopcount for hammer repetitions with %ss on order 1 is %u. Calculated: %u",
            "Column",
            CPGC_MAX_LOOPCOUNT,
            (CPGC_MAX_LOOPCOUNT - numberCols[Channel])
            );
        }

        if (CPGHammerRepetitions > 0) {
          if ((CPGC_MAX_LOOPCOUNT - NewLoopcount[Channel]) >= HammerRepLinear) {
            NewLoopcount[Channel] = CPGC_MAX_LOOPCOUNT;
          } else {
            NewLoopcount[Channel] += HammerRepLinear;
          }
        }

        if (TestDirection == UP) {
          CurrentAddress[Channel].Row = DcttConfig->bottomAddress[Channel].Row;
          CurrentAddress[Channel].Col = DcttConfig->bottomAddress[Channel].Col;
          if ((DcttConfig->SubMemoryRangeTest == TRUE) && (firstBankToTest[Channel])) {
            CurrentAddress[Channel].Row = DcttConfig->internalBottomAddress[Channel].Row;
            CurrentAddress[Channel].Col = DcttConfig->internalBottomAddress[Channel].Col;
          }
        } else {
          // TODO: Change to use topAddr when updated to not use max size
          CurrentAddress[Channel].Row = LastRowAddr[Channel];
          CurrentAddress[Channel].Col = LastColAddr[Channel];
          if ((DcttConfig->SubMemoryRangeTest == TRUE) && (lastBankToTest[Channel])) {
            if (DcttConfig->internalTopAddress[Channel].Row < CurrentAddress[Channel].Row) {
              CurrentAddress[Channel].Row = DcttConfig->internalTopAddress[Channel].Row;
            }
            if (DcttConfig->internalTopAddress[Channel].Col < CurrentAddress[Channel].Col) {
              CurrentAddress[Channel].Col = DcttConfig->internalTopAddress[Channel].Col;
            }
          }
        }

        if (DcttConfig->SubMemoryRangeTest == TRUE) {
          if ((firstBankToTest[Channel] || lastBankToTest[Channel]) &&
              (rankTestMask & (1 << Channel))) {
            dummyCurrentAddress.Row = CurrentAddress[Channel].Row;
            dummyCurrentAddress.Col = CurrentAddress[Channel].Col;

            RetVal = CPGCFunctions_CalculateRemainingLoopcount (
                       DcttMain,
                       TestDirection,
                       &NewLoopcount[Channel],
                       &dummyCurrentAddress,
                       Channel,
                       CPGHammerRepetitions,
                       firstBankToTest[Channel],
                       lastBankToTest[Channel],
                       TRUE
                       );
          }
        }

        startAddressRegVal[Channel] = Helpers_SetField (
                                        startAddressRegVal[Channel],
                                        Bank,
                                        DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_START,
                                        DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_BANK_ADDRESS_LEN);


        wrapAddressRegVal[Channel] = Helpers_SetField (
                                       wrapAddressRegVal[Channel],
                                       Bank,
                                       DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_BANK_ADDRESS_START,
                                       DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_BANK_ADDRESS_LEN);

        if (rankTestMask & (1 << Channel)) {
          TestMask = (TestMask | (1 << Channel));
          ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                             DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);

          SeqConfigRegVal[Channel] = Helpers_SetField (
                                       SeqConfigRegVal[Channel],
                                       1,
                                       DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                       DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Enable Global Control

          DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal[Channel]);
        } else {
          if (DcttConfig->SubMemoryRangeTest == TRUE) {
            TestMask = (TestMask & (~(1 << Channel)));
            ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                               DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);

            SeqConfigRegVal[Channel] = Helpers_SetField (
                                         SeqConfigRegVal[Channel],
                                         0,
                                         DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                         DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Disable Global Control

            DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal[Channel]);
          }
        }
      }

      do {
        for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
          startAddressRegVal[Channel] = Helpers_SetField (
                                          startAddressRegVal[Channel],
                                          CurrentAddress[Channel].Row,
                                          DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                          DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);

          startAddressRegVal[Channel] = Helpers_SetField (
                                          startAddressRegVal[Channel],
                                          CurrentAddress[Channel].Col,
                                          DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                          DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN);

          ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                             DCTT_REUT_CH_SEQ_BASE_ADDR_START, 0, Channel, DCTT_BYTE_CTL_NA);
          DcttWriteReg64Func (DcttMain, ReutRegAddress, startAddressRegVal[Channel]);

          //
          // Update the loopcount register
          //
          ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                             DCTT_REUT_CH_SEQ_LOOPCOUNT_LIMIT, 0, Channel, DCTT_BYTE_CTL_NA);
          DcttWriteReg32Func (DcttMain, ReutRegAddress, NewLoopcount[Channel]);
        }

        DcttError_Assert (DcttMain, TestMask != 0, "We are trying to run a test with no channels enabled.");

        //
        // Pause refresh runner
        //
        if (RunnerType == ST_PAUSE_REFRESH_RUN) {
          UINT32 pauseRefreshDelay;
          SymbolSeqParameters* seqParameters = (SymbolSeqParameters*) RunnerParameters;
          BOOLEAN differentLC;
          UINT32 minLC, previousLC, LCTime;
          UINT32 waitDelay, waitDelayHPET;
          UINT32 subseqRegisterVal[DCTT_MAX_NUM_CHANNELS];

          waitDelay         = 0;
          differentLC       = FALSE;
          pauseRefreshDelay = SymbolSeqParameters_GetDelay (seqParameters);
          DcttLogDebug (DcttMain, "Pause refresh runner for Delay: %d\n", pauseRefreshDelay);
          pauseRefreshDelay = pauseRefreshDelay * 1000;//changing the Delay to ns

          //Reading the subsequence register so we won't increase the waiting time on the middle of the test
          for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
            ReutRegAddress = DcttGetMcAddressFunc (DcttMain, DCTT_REUT_CH_SUBSEQ_CTL_0, 0, Channel, 0);
            subseqRegisterVal[Channel] = DcttReadReg32Func (DcttMain, ReutRegAddress);
          }

          previousLC = NewLoopcount[0];
          for (Channel = 1; Channel < DcttConfig->numberChannels; Channel++) {
            DcttLogDebug (
              DcttMain,
              "Channel %d Original loopcount: %d\n",
              Channel,
              NewLoopcount[Channel]
              );
            if (previousLC != NewLoopcount[Channel]) {
              differentLC = TRUE;
              break;
            }
            previousLC = NewLoopcount[Channel];
          }
          if (differentLC) {
            //We have different loopcounts, to simplify the algorithm make all loopcounts equal to the
            //minimum of all loopcounts that is greater than 0 (because a loopcount of 0 means that we won't
            //run a test on that Channel)
            minLC = 0;
            for (Channel = 0; Channel < DcttConfig->numberChannels; Channel ++) {
              //Looking for the minimum LC greater than 0
              if (((NewLoopcount[Channel] < minLC) && (NewLoopcount[Channel] > 0)) || (minLC == 0)) {
                minLC = NewLoopcount[Channel];
              }
            }
          } else {
            //All loopcounts are equal, so it doesn't matter which one we use for the test
            minLC = NewLoopcount[0];
          }
          //minLC cannot be 0 because we should have LC at leat on one of the channels
          //if we are going to run a test
          DcttError_Assert (DcttMain, minLC > 1, "Couldn't find minimum loopcount\n");
          //Getting how much time will be taken by the minLC on the test
          LCTime = DelayTime_GetTimensFromLoopcount (&PauseRefreshCalc, minLC);

          DcttLogDebug (DcttMain, "Min LC: %d, Min LC time: %d\n", minLC, LCTime);

          if (LCTime > pauseRefreshDelay) {
            //We have to make the number of LC smaller because it takes longer than the requested time
            minLC = DelayTime_GetLoopcountFromTimens (&PauseRefreshCalc, pauseRefreshDelay);
            DcttLogDebug (DcttMain, "LC for %uns Delay: %d\n", pauseRefreshDelay, minLC);
            //minimum number of LC is a row
            if (minLC < PauseRefreshCalc.numCachelinesPerCol) {
              DcttLogDebug (
                DcttMain,
                "Min LC is to small: %d. Setting it to %d\n",
                minLC,
                PauseRefreshCalc.numCachelinesPerCol
                );
              minLC = PauseRefreshCalc.numCachelinesPerCol;
            }
            LCTime = DelayTime_GetTimensFromLoopcount (&PauseRefreshCalc, minLC);

            DcttLogDebug (
              DcttMain,
              "Min LC was to big, new min LC: %d, Min LC time: %d\n",
              minLC,
              LCTime
              );
            if (pauseRefreshDelay > LCTime) {
              waitDelay = pauseRefreshDelay - LCTime;
            } else {
              waitDelay = 0;
            }
            DcttLogDebug (DcttMain, "Remaining wait Delay: %d\n", waitDelay);
          } else {
            waitDelay = pauseRefreshDelay - LCTime;
            DcttLogDebug (DcttMain, "Wait Delay: %d\n", waitDelay);
          }

          waitDelayHPET = DelayTime_GetNumberWaitUnits (&PauseRefreshCalc, waitDelay);

          DcttLogDebug (DcttMain, "Wait DelayHpet: %d\n", waitDelayHPET);

          //Reprogramming any loopcount that needs to be reprogrammed
          for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
            if ((NewLoopcount[Channel] != 0) && (NewLoopcount[Channel] != minLC)) {
              DcttLogDebug (DcttMain, "Changing loopcount on Channel: %d\n", Channel);
              //Write the loopcount register
              ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                 DCTT_REUT_CH_SEQ_LOOPCOUNT_LIMIT, 0, Channel, DCTT_BYTE_CTL_NA);
              DcttWriteReg32Func (DcttMain, ReutRegAddress, minLC);
            }
          }

          //Changing all the subsequences to write
          //This is needed because we run the test per Bank so the
          //register write before running the test is not enough
          for (Channel = 0; Channel < DcttConfig->numberChannels; Channel ++) {
            subseqRegisterVal[Channel] = (UINT32) Helpers_SetField (
                                                    subseqRegisterVal[Channel],
                                                    CPGC_BASE_SUBSEQ_TYPE_WRITE,
                                                    DCTT_REUT_CH_SUBSEQ_CTL_F_SUBSEQ_TYPE_START,
                                                    DCTT_REUT_CH_SUBSEQ_CTL_F_SUBSEQ_TYPE_LEN
                                                    );
            ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                               (DCTT_REUT_CH_SUBSEQ_CTL_0), 0, Channel, 0);
            DcttWriteReg32Func (DcttMain, ReutRegAddress, subseqRegisterVal[Channel]);
          }

          //Starting the write portion of the test
          ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                             DCTT_REUT_GLOBAL_CTRL, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
          DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST));

          do{
            ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                               DCTT_REUT_GLOBAL_ERR, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
            GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

            TestDone = (GlobalError & CPGC_TEST_DONE_MASK) >> 16;
            TestDone = TestDone & ChannelMask;
            ChannelErrors = (GlobalError & CPGC_ERROR_STATUS_MASK);
            ChannelErrors = ChannelErrors & ChannelMask;
            if (globalErrRegValPrev != GlobalError) {
              globalErrRegValPrev = GlobalError;
              DcttLogDebug (DcttMain, "GlobalError:  0x%0x   TestDone:  0x%0x\n", GlobalError, TestDone);
            }
          } while ((TestDone != ChannelMask));

          //Doing any extra wait if needed
          if (waitDelayHPET > 0) {
            //DcttLogDebug (DcttMain, "About to wait %d hpets\n", waitDelayHPET);
            DcttWaitFunc (DcttMain, waitDelayHPET); // TODO: Conver to NS and push HW details into provided function.
          }

          //Changing all the subsequences to read
          for (Channel = 0; Channel < DcttConfig->numberChannels; Channel ++) {
            subseqRegisterVal[Channel] = (UINT32) Helpers_SetField (
                                                    subseqRegisterVal[Channel],
                                                    CPGC_BASE_SUBSEQ_TYPE_READ,
                                                    DCTT_REUT_CH_SUBSEQ_CTL_F_SUBSEQ_TYPE_START,
                                                    DCTT_REUT_CH_SUBSEQ_CTL_F_SUBSEQ_TYPE_LEN
                                                    );
            ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                               (DCTT_REUT_CH_SUBSEQ_CTL_0), 0, Channel, 0);
            DcttWriteReg32Func (DcttMain, ReutRegAddress, subseqRegisterVal[Channel]);
          }

          //Starting the read portion of the test
          ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                             DCTT_REUT_GLOBAL_CTRL, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
          DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST));

          do{
            ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                               DCTT_REUT_GLOBAL_ERR, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
            GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

            TestDone = (GlobalError & CPGC_TEST_DONE_MASK) >> 16;
            TestDone = TestDone & ChannelMask;
            ChannelErrors = (GlobalError & CPGC_ERROR_STATUS_MASK);
            ChannelErrors = ChannelErrors & ChannelMask;
            if (globalErrRegValPrev != GlobalError) {
              globalErrRegValPrev = GlobalError;
              DcttLogDebug (DcttMain, "GlobalError:  0x%0x   TestDone:  0x%0x\n", GlobalError, TestDone);
            }
          } while ((TestDone != ChannelMask));
        } else if (RunnerType == ST_FINE_GRAIN_SEQ_HAMMER) {
          //We are going to traverse memory manually and set up the loopcount with the
          //number of hammer repetitions
          SymbolSeqParameters* hammerParams = (SymbolSeqParameters*) RunnerParameters;
          UINT32 numberCheckSubseq;
          UINT32 maxNumRow, maxNumCol;
          UINT64 seqCtlRegHammer[DCTT_MAX_NUM_CHANNELS], seqCtlRegCheck[DCTT_MAX_NUM_CHANNELS], seqCtlCellSet[DCTT_MAX_NUM_CHANNELS], seqCtlAttackerSet[DCTT_MAX_NUM_CHANNELS];
          UINT32 currRowCount;
          UINT32 currentRow[DCTT_MAX_NUM_CHANNELS], currentLogicalRow[DCTT_MAX_NUM_CHANNELS]; // currentCol[DCTT_MAX_NUM_CHANNELS],
          UINT32 startRow[DCTT_MAX_NUM_CHANNELS], startCol[DCTT_MAX_NUM_CHANNELS];
          UINT32 wrapRow[DCTT_MAX_NUM_CHANNELS], wrapCol[DCTT_MAX_NUM_CHANNELS];
          UINT32 neighborRows[2][DCTT_MAX_NUM_CHANNELS], numberRowNeighbors[DCTT_MAX_NUM_CHANNELS];
          UINT32 numberColsCacheline;
          UINT64 baseAddrIncCtrlOrig[DCTT_MAX_NUM_CHANNELS], baseAddrIncCtrlHammer[DCTT_MAX_NUM_CHANNELS];
          //UINT64 startAddressRegValNeighbors[2][DCTT_MAX_NUM_CHANNELS];

          ChannelErrors = 0;
          numberColsCacheline = CPGC_NUMBER_BYTES_CACHELINES;

          // TODO: Add check for linear LC for Fine Grain Hammer
          if (!((DcttConfig->firstOrder == DcttOrderColumn) && (DcttConfig->secondOrder == DcttOrderRow))) {
            DcttError_Assert (DcttMain, 1 == 0, "Currently fine grain hammer will only work when traversing memory Col-Row");
          }

          CPGHammerRepetitions = hammerParams->delay;////TODO:Change parameter name
          numberCheckSubseq    = hammerParams->numberHammerCheckSubSeq;////TODO: Take this out

          maxNumCol = 0;
          maxNumRow = 0;

          for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
            if (maxNumRow < LastRowAddr[Channel]) {
              maxNumRow = LastRowAddr[Channel];
            }

            if (maxNumCol < LastColAddr[Channel]) {
              maxNumCol = LastColAddr[Channel];
            }

            ////TODO: Make sure that start and stop COLs are multiple of 8
            if (TestDirection == UP) {
              wrapRow[Channel] = DcttConfig->topAddress[Channel].Row;
              if (wrapRow[Channel] > LastRowAddr[Channel]) {
                wrapRow[Channel] = LastRowAddr[Channel];
              }
              startRow[Channel] = DcttConfig->bottomAddress[Channel].Row;

              wrapCol[Channel] = DcttConfig->topAddress[Channel].Col;
              if (wrapCol[Channel] > LastColAddr[Channel]) {
                wrapCol[Channel] = LastColAddr[Channel];
              }
              startCol[Channel] = DcttConfig->bottomAddress[Channel].Col;
            } else {
              wrapRow[Channel] = DcttConfig->bottomAddress[Channel].Row;
              startRow[Channel] = DcttConfig->topAddress[Channel].Row;
              if (startRow[Channel] > LastRowAddr[Channel]) {
                startRow[Channel] = LastRowAddr[Channel];
              }

              wrapCol[Channel] = DcttConfig->bottomAddress[Channel].Col;
              startCol[Channel] = DcttConfig->topAddress[Channel].Col;
              if (startCol[Channel] > LastColAddr[Channel]) {
                startCol[Channel] = LastColAddr[Channel];
              }
            }

            //currentCol[Channel] = startCol[Channel];
            currentRow[Channel] = startRow[Channel];

            ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                               DCTT_REUT_CH_SEQ_CFG, 0, Channel, 0);
            seqCtlRegHammer[Channel] = DcttReadReg64Func (DcttMain, ReutRegAddress);

            //Setting the subsequence pointer to the hammer operation
            seqCtlRegHammer[Channel] = Helpers_SetField (
                                         seqCtlRegHammer[Channel],
                                         0,
                                         DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_START,
                                         DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_LEN);

            seqCtlRegHammer[Channel] = Helpers_SetField (
                                         seqCtlRegHammer[Channel],
                                         0,
                                         DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_START,
                                         DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_LEN);

            //Setting the subsequence pointer for the set operation
            seqCtlCellSet[Channel] = Helpers_SetField (
                                       seqCtlRegHammer[Channel],
                                       1,
                                       DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_START,
                                       DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_LEN);

            seqCtlCellSet[Channel] = Helpers_SetField (
                                       seqCtlCellSet[Channel],
                                       1,
                                       DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_START,
                                       DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_LEN);

            //Setting the subsequence pointer for the check operation
            seqCtlRegCheck[Channel] = Helpers_SetField (
                                        seqCtlRegHammer[Channel],
                                        2,
                                        DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_START,
                                        DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_LEN);

            seqCtlRegCheck[Channel] = Helpers_SetField (
                                        seqCtlRegCheck[Channel],
                                        2,
                                        DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_START,
                                        DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_LEN);

            //Setting the subseq pointers for the attacker row settings
            seqCtlAttackerSet[Channel] = Helpers_SetField (
                                           seqCtlRegHammer[Channel],
                                           3,
                                           DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_START,
                                           DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_LEN);

            seqCtlAttackerSet[Channel] = Helpers_SetField (
                                           seqCtlAttackerSet[Channel],
                                           3,
                                           DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_START,
                                           DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_LEN);

            //Changing the increment control to stay on the same cell
            ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL, 0, Channel, DCTT_BYTE_CTL_NA);
            baseAddrIncCtrlOrig[Channel] = DcttReadReg64Func (DcttMain, ReutRegAddress);
            ////TODO: Disable the wrap/carries

            //Fixing the update rate for 11 or 10 bit column memories
            ////TODO:move this fix out, so all tests can benefit from it
            baseAddrIncCtrlOrig[Channel] = Helpers_SetField (
                                             baseAddrIncCtrlOrig[Channel],
                                             NumCacheLinesPerPage[Channel],
                                             DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_START,
                                             DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_UPDATE_RATE_LEN);
            //Forcing increment control to always go up
            baseAddrIncCtrlOrig[Channel] = Helpers_SetField (
                                             baseAddrIncCtrlOrig[Channel],
                                             1,
                                             DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                                             DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN);

            baseAddrIncCtrlOrig[Channel] = Helpers_SetField (
                                             baseAddrIncCtrlOrig[Channel],
                                             1,
                                             DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                                             DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN);

            //Setting the hammer increment control
            baseAddrIncCtrlHammer[Channel] = Helpers_SetField (
                                               baseAddrIncCtrlOrig[Channel],
                                               0,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN);

            baseAddrIncCtrlHammer[Channel] = Helpers_SetField (
                                               baseAddrIncCtrlHammer[Channel],
                                               0,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN);

            ////DcttWriteReg64Func (DcttMain, ReutRegAddress, baseAddrIncCtrlHammer[Channel]);
          }

          if (DcttConfig->singleRowForHammer) {
            maxNumRow = 0;
          }

          for (currRowCount = 0; currRowCount <= maxNumRow; currRowCount++) {
            UINT32 rowIteration;

            if (TestMask == 0) {
              break;
            }

            for (rowIteration = 0; rowIteration < DcttConfig->hammerIterationsOnRow; rowIteration++) {
              for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
                if (DcttConfig->singleRowForHammer) {
                  if (TestMask &(1 << Channel)) {
                    DcttOutputPrint (DcttMain, "Testing Physical Row %d on Channel %d\n", currentRow[Channel], Channel);
                  }
                }
                //Setting the physical row addresses
                if (currentRow[Channel] == 0) {
                  neighborRows[0][Channel] = hammerParams->swizzleFunction (currentRow[Channel] + 1);
                  //Next one is not a real neighbor but having it simplifies the test
                  neighborRows[1][Channel] = hammerParams->swizzleFunction (LastRowAddr[Channel]);
                  numberRowNeighbors[Channel] = 1;
                } else if (currentRow[Channel] == LastRowAddr[Channel]) {
                  neighborRows[0][Channel] = hammerParams->swizzleFunction (currentRow[Channel] - 1);
                  //Next one is not a real neighbor but having it simplifies the test
                  neighborRows[1][Channel] = hammerParams->swizzleFunction (0);
                  numberRowNeighbors[Channel] = 1;
                } else {
                  neighborRows[0][Channel] = hammerParams->swizzleFunction (currentRow[Channel] + 1);
                  neighborRows[1][Channel] = hammerParams->swizzleFunction (currentRow[Channel] - 1);
                  numberRowNeighbors[Channel] = 2;
                }
                currentLogicalRow[Channel] = hammerParams->swizzleFunction (currentRow[Channel]);

                //Setting loopcount to number of columns of a row
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_LOOPCOUNT_LIMIT, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg32Func (DcttMain,
                  ReutRegAddress,
                  NumCacheLinesPerPage[Channel]);

                //Change the sequence pointer to the Set neighbors one
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_CFG, 0, Channel, 0);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, seqCtlCellSet[Channel]);

                //Setting the address of the first neighbor
                startAddressRegVal[Channel] = Helpers_SetField (
                                                startAddressRegVal[Channel],
                                                neighborRows[0][Channel],
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);
                startAddressRegVal[Channel] = Helpers_SetField (
                                                startAddressRegVal[Channel],
                                                0, //currentCol[Channel]
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN);
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_START, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, startAddressRegVal[Channel]);

                //Set the wrap address
                wrapAddressRegVal[Channel] = Helpers_SetField (
                                               wrapAddressRegVal[Channel],
                                               ((wrapCol[Channel]) | DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_DISABLE_COL_WRAP),
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_LEN);
                wrapAddressRegVal[Channel] = Helpers_SetField (
                                               wrapAddressRegVal[Channel],
                                               ((neighborRows[0][Channel]) | DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_DISABLE_ROW_WRAP),
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_LEN);
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, wrapAddressRegVal[Channel]);

                //Changing update count to move and test all cells
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, baseAddrIncCtrlOrig[Channel]);
              }

              ////Start CPGC engine test to set cell values on first neighbor
              ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                 DCTT_REUT_GLOBAL_CTRL, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
              DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST));

              do {
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_GLOBAL_ERR, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
                GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

                TestDone = (GlobalError & CPGC_TEST_DONE_MASK) >> 16;
                TestDone = TestDone & ChannelMask;
                ChannelErrors = (GlobalError & CPGC_ERROR_STATUS_MASK);
                ChannelErrors = ChannelErrors & ChannelMask;
              } while ((TestDone != ChannelMask));

              for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
                //Setting the address of the second neighbor
                startAddressRegVal[Channel] = Helpers_SetField (
                                                startAddressRegVal[Channel],
                                                neighborRows[1][Channel],
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);
                //
                // Do not need to set Column start to 0 as it was set above
                //
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_START, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, startAddressRegVal[Channel]);

                //Set the wrap address
                wrapAddressRegVal[Channel] = Helpers_SetField (
                                               wrapAddressRegVal[Channel],
                                               ((wrapCol[Channel]) | DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_DISABLE_COL_WRAP),
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_LEN);
                wrapAddressRegVal[Channel] = Helpers_SetField (
                                               wrapAddressRegVal[Channel],
                                               ((neighborRows[1][Channel]) | DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_DISABLE_ROW_WRAP),
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_LEN);
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, wrapAddressRegVal[Channel]);
              }

              ////Start CPGC engine test to set cell values on second neighbor
              ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                 DCTT_REUT_GLOBAL_CTRL, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
              DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST));

              do {
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_GLOBAL_ERR, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
                GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

                TestDone = (GlobalError & CPGC_TEST_DONE_MASK) >> 16;
                TestDone = TestDone & ChannelMask;
                ChannelErrors = (GlobalError & CPGC_ERROR_STATUS_MASK);
                ChannelErrors = ChannelErrors & ChannelMask;
              } while ((TestDone != ChannelMask));

              //Setting the complete aggressor row before the hammer
              for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
                ////Set current address on registers for Hammer
                startAddressRegVal[Channel] = Helpers_SetField (
                                                startAddressRegVal[Channel],
                                                currentLogicalRow[Channel],
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);
                //
                // Do not need to set Column start to 0 as it was set above
                //
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_START, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, startAddressRegVal[Channel]);

                //Set the wrap address
                wrapAddressRegVal[Channel] = Helpers_SetField (
                                               wrapAddressRegVal[Channel],
                                               ((wrapCol[Channel]) | DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_DISABLE_COL_WRAP),
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_LEN);
                wrapAddressRegVal[Channel] = Helpers_SetField (
                                               wrapAddressRegVal[Channel],
                                               ((currentLogicalRow[Channel]) | DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_DISABLE_ROW_WRAP),
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_LEN);
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, wrapAddressRegVal[Channel]);

                ////Set subsequence start and stop for attacker row setting
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_CFG, 0, Channel, 0);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, seqCtlAttackerSet[Channel]);
              }

              ////Start CPGC engine test to set attacker row
              ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                 DCTT_REUT_GLOBAL_CTRL, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
              DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST));

              do {
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_GLOBAL_ERR, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
                GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

                TestDone = (GlobalError & CPGC_TEST_DONE_MASK) >> 16;
                TestDone = TestDone & ChannelMask;
                ChannelErrors = (GlobalError & CPGC_ERROR_STATUS_MASK);
                ChannelErrors = ChannelErrors & ChannelMask;
              } while ((TestDone != ChannelMask));

              //Hammer operation
              for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
                ////Set current address on registers for Hammer
                startAddressRegVal[Channel] = Helpers_SetField (
                                                startAddressRegVal[Channel],
                                                currentLogicalRow[Channel],
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);
                startAddressRegVal[Channel] = Helpers_SetField (
                                                startAddressRegVal[Channel],
                                                0, //currentCol[Channel]
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN);
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_START, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, startAddressRegVal[Channel]);
                ////TODO: Check if it is necessary to set wraps(I don't think they are necessary)

                ////Program Hammer Loopcount on loopcount_limit register
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_LOOPCOUNT_LIMIT, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg32Func (DcttMain, ReutRegAddress, DcttConfig->hammerRepetitions);

                ////Set subsequence start and stop for hammer operation
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_CFG, 0, Channel, 0);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, seqCtlRegHammer[Channel]);

                //Changing update count to stay on the same cell
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, baseAddrIncCtrlHammer[Channel]);
              }

              ////Start CPGC engine test to run hammer
              ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                 DCTT_REUT_GLOBAL_CTRL, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
              DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST));

              do {
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_GLOBAL_ERR, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
                GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

                TestDone = (GlobalError & CPGC_TEST_DONE_MASK) >> 16;
                TestDone = TestDone & ChannelMask;
                ChannelErrors = (GlobalError & CPGC_ERROR_STATUS_MASK);
                ChannelErrors = ChannelErrors & ChannelMask;
              } while ((TestDone != ChannelMask));

              //Set registers for neighbors check
              for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
                //Setting loopcount to number of columns of a row
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_LOOPCOUNT_LIMIT, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg32Func (DcttMain,
                  ReutRegAddress,
                  NumCacheLinesPerPage[Channel]);

                //Change the sequence pointer to the check neighbors one
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_CFG, 0, Channel, 0);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, seqCtlRegCheck[Channel]);

                //Setting the address of the first neighbor
                startAddressRegVal[Channel] = Helpers_SetField (
                                                startAddressRegVal[Channel],
                                                neighborRows[0][Channel],
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);
                startAddressRegVal[Channel] = Helpers_SetField (
                                                startAddressRegVal[Channel],
                                                0, //currentCol[Channel]
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN);
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_START, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, startAddressRegVal[Channel]);
                //Set the wrap address
                wrapAddressRegVal[Channel] = Helpers_SetField (
                                               wrapAddressRegVal[Channel],
                                               ((wrapCol[Channel]) | DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_DISABLE_COL_WRAP),
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_LEN);

                wrapAddressRegVal[Channel] = Helpers_SetField (
                                               wrapAddressRegVal[Channel],
                                               ((neighborRows[0][Channel]) | DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_DISABLE_ROW_WRAP),
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_LEN);
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, wrapAddressRegVal[Channel]);

                //Changing update count to move and test all cells
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, baseAddrIncCtrlOrig[Channel]);
              }

              ////Start CPGC engine test to check cell values on first neighbor
              ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                 DCTT_REUT_GLOBAL_CTRL, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
              DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST));

              do {
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_GLOBAL_ERR, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
                GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

                TestDone = (GlobalError & CPGC_TEST_DONE_MASK) >> 16;
                TestDone = TestDone & ChannelMask;
                ChannelErrors = (GlobalError & CPGC_ERROR_STATUS_MASK);
                ChannelErrors = ChannelErrors & ChannelMask;
              } while ((TestDone != ChannelMask));

              // TODO: Check if it would be better to read the error without printing
              if (ChannelErrors & TestMask) {
                RetVal = CPGCFunctions_ErrorHandler (
                           DcttMain,
                           TestMask,
                           PerBankErrors,
                           GlobalParameters,
                           currentLogicalRow,
                           NULL
                           );
                if (RetVal != DCTT_SUCCESS) {
                  return RetVal;
                }
              }

              for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
                //Setting the address of the second neighbor
                startAddressRegVal[Channel] = Helpers_SetField (
                                                startAddressRegVal[Channel],
                                                neighborRows[1][Channel],
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);
                startAddressRegVal[Channel] = Helpers_SetField (
                                                startAddressRegVal[Channel],
                                                0, //currentCol[Channel]
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN);
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_START, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, startAddressRegVal[Channel]);
                //Set the wrap address
                wrapAddressRegVal[Channel] = Helpers_SetField (
                                               wrapAddressRegVal[Channel],
                                               ((wrapCol[Channel]) | DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_DISABLE_COL_WRAP),
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_COL_ADDRESS_LEN);

                wrapAddressRegVal[Channel] = Helpers_SetField (
                                               wrapAddressRegVal[Channel],
                                               ((neighborRows[1][Channel]) | DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_DISABLE_ROW_WRAP),
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP_F_ROW_ADDRESS_LEN);
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_WRAP, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, wrapAddressRegVal[Channel]);
              }

              ////Start CPGC engine test to check cell values on second neighbor
              ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                 DCTT_REUT_GLOBAL_CTRL, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
              DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST));

              do {
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_GLOBAL_ERR, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
                GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

                TestDone = (GlobalError & CPGC_TEST_DONE_MASK) >> 16;
                TestDone = TestDone & ChannelMask;
                ChannelErrors = (GlobalError & CPGC_ERROR_STATUS_MASK);
                ChannelErrors = ChannelErrors & ChannelMask;
              } while ((TestDone != ChannelMask));

              ////TODO: Check if it would be better to read the error without printing
              ////TODO: Clear error mask if there where only 1 neighbor for the row in that particular Channel
              if (ChannelErrors & TestMask) {
                RetVal = CPGCFunctions_ErrorHandler (
                           DcttMain,
                           TestMask,
                           PerBankErrors,
                           GlobalParameters,
                           currentLogicalRow,
                           NULL
                           );
                if (RetVal != DCTT_SUCCESS) {
                  return RetVal;
                }
              }
            }

            ////Enable channels on which row is in range and is populated
            for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
              if (DCTT_RankInChannelExists (DcttMain, 0, Rank, Channel)) {
                TestMask = (TestMask | (1 << Channel));

                SeqConfigRegVal[Channel] = Helpers_SetField (
                                             SeqConfigRegVal[Channel],
                                             1,
                                             DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                             DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Enable Global Control

                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal[Channel]);
              }

              if (TestDirection == UP) {
                if (currentRow[Channel] < wrapRow[Channel]) {
                  currentRow[Channel] = currentRow[Channel] + 1;

                  startAddressRegVal[Channel] = Helpers_SetField (
                                                  startAddressRegVal[Channel],
                                                  currentRow[Channel],
                                                  DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                                  DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);
                } else if (TestMask & (1 << Channel)) {
                  ////TODO: Disable Channel
                  ////TODO: Optimize for cases where both channels have the same # of rows
                  TestMask = (TestMask & (~(1 << Channel)));

                  SeqConfigRegVal[Channel] = Helpers_SetField (
                                               SeqConfigRegVal[Channel],
                                               0,
                                               DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                               DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Disable Global Control

                  ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                     DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
                  DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal[Channel]);
                }
              } else {
                //Going down
                if (currentRow[Channel] > wrapRow[Channel]) {
                  currentRow[Channel] = currentRow[Channel] - 1;

                  startAddressRegVal[Channel] = Helpers_SetField (
                                                  startAddressRegVal[Channel],
                                                  currentRow[Channel],
                                                  DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                                  DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);
                } else if (TestMask & (1 << Channel)) {
                  ////TODO: Disable Channel
                  ////TODO: Optimize for cases where both channels have the same # of rows
                  TestMask = (TestMask & (~(1 << Channel)));

                  SeqConfigRegVal[Channel] = Helpers_SetField (
                                               SeqConfigRegVal[Channel],
                                               0,
                                               DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                               DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Disable Global Control

                  ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                     DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
                  DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal[Channel]);
                }
              }
            }
          }

          TestMask = 0;//The whole Bank test will be done inside this runner
        } else if (RunnerType == ST_FINE_GRAIN_SEQ_HAMMER_SLOW) {
          //We are going to traverse memory manually and set up the loopcount with the
          //number of hammer repetitions
          SymbolSeqParameters* hammerParams = (SymbolSeqParameters*) RunnerParameters;
          UINT32 numberCheckSubseq;
          UINT32 maxNumRow, maxNumCol;
          UINT64 seqCtlRegHammer[DCTT_MAX_NUM_CHANNELS], seqCtlRegCheck[DCTT_MAX_NUM_CHANNELS];
          UINT32 currColCount, currRowCount;
          UINT32 currentRow[DCTT_MAX_NUM_CHANNELS], currentCol[DCTT_MAX_NUM_CHANNELS];
          UINT32 startRow[DCTT_MAX_NUM_CHANNELS], startCol[DCTT_MAX_NUM_CHANNELS];
          UINT32 wrapRow[DCTT_MAX_NUM_CHANNELS], wrapCol[DCTT_MAX_NUM_CHANNELS];
          UINT32 numberColsCacheline;
          UINT64 baseAddrIncCtrlOrig[DCTT_MAX_NUM_CHANNELS], baseAddrIncCtrlHammer[DCTT_MAX_NUM_CHANNELS];

          ChannelErrors = 0;
          numberColsCacheline = CPGC_NUMBER_BYTES_CACHELINES;
          // TODO: Add check for linear LC for Fine Grain Hammer
          if (!((DcttConfig->firstOrder == DcttOrderColumn) && (DcttConfig->secondOrder == DcttOrderRow))) {
            DcttError_Assert (DcttMain, 1 == 0, "Currently fine grain hammer will only work when traversing memory Col-Row");
          }

          CPGHammerRepetitions = hammerParams->delay;////TODO:Change parameter name
          numberCheckSubseq    = hammerParams->numberHammerCheckSubSeq;

          maxNumCol = 0;
          maxNumRow = 0;

          for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
            if (maxNumRow < LastRowAddr[Channel]) {
              maxNumRow = LastRowAddr[Channel];
            }

            if (maxNumCol < LastColAddr[Channel]) {
              maxNumCol = LastColAddr[Channel];
            }

            ////TODO: Make sure that start and stop COLs are multiple of 8
            if (TestDirection == UP) {
              wrapRow[Channel] = DcttConfig->topAddress[Channel].Row;
              if (wrapRow[Channel] > LastRowAddr[Channel]) {
                wrapRow[Channel] = LastRowAddr[Channel];
              }
              startRow[Channel] = DcttConfig->bottomAddress[Channel].Row;

              wrapCol[Channel] = DcttConfig->topAddress[Channel].Col;
              if (wrapCol[Channel] > LastColAddr[Channel]) {
                wrapCol[Channel] = LastColAddr[Channel];
              }
              startCol[Channel] = DcttConfig->bottomAddress[Channel].Col;
            } else {
              wrapRow[Channel] = DcttConfig->bottomAddress[Channel].Row;
              startRow[Channel] = DcttConfig->topAddress[Channel].Row;
              if (startRow[Channel] > LastRowAddr[Channel]) {
                startRow[Channel] = LastRowAddr[Channel];
              }

              wrapCol[Channel] = DcttConfig->bottomAddress[Channel].Col;
              startCol[Channel] = DcttConfig->topAddress[Channel].Col;
              if (startCol[Channel] > LastColAddr[Channel]) {
                startCol[Channel] = LastColAddr[Channel];
              }
            }

            currentCol[Channel] = startCol[Channel];
            currentRow[Channel] = startRow[Channel];

            ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                               DCTT_REUT_CH_SEQ_CFG, 0, Channel, 0);
            seqCtlRegHammer[Channel] = DcttReadReg64Func (DcttMain, ReutRegAddress);

            seqCtlRegHammer[Channel] = Helpers_SetField (
                                         seqCtlRegHammer[Channel],
                                         0,
                                         DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_START,
                                         DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_LEN);

            seqCtlRegHammer[Channel] = Helpers_SetField (
                                         seqCtlRegHammer[Channel],
                                         0,
                                         DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_START,
                                         DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_LEN);

            seqCtlRegCheck[Channel] = Helpers_SetField (
                                        seqCtlRegHammer[Channel],
                                        1,
                                        DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_START,
                                        DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_START_POINTER_LEN);

            seqCtlRegCheck[Channel] = Helpers_SetField (
                                        seqCtlRegCheck[Channel],
                                        1 + numberCheckSubseq - 1, //I can take out the +1 and -1 but this is more explicit
                                        DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_START,
                                        DCTT_REUT_CH_SEQ_CFG_F_SUBSEQ_END_POINTER_LEN);

            //Changing the increment control to stay on the same cell
            ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL, 0, Channel, DCTT_BYTE_CTL_NA);
            baseAddrIncCtrlOrig[Channel] = DcttReadReg64Func (DcttMain, ReutRegAddress);

            baseAddrIncCtrlHammer[Channel] = Helpers_SetField (
                                               baseAddrIncCtrlOrig[Channel],
                                               0,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_COL_ADDRESS_INCREMENT_LEN);

            baseAddrIncCtrlHammer[Channel] = Helpers_SetField (
                                               baseAddrIncCtrlHammer[Channel],
                                               0,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_START,
                                               DCTT_REUT_CH_SEQ_BASE_ADDR_INC_CTL_F_ROW_ADDRESS_INCREMENT_LEN);

            DcttWriteReg64Func (DcttMain, ReutRegAddress, baseAddrIncCtrlHammer[Channel]);

            ////TODO: Restore original baseAddrIncCtrlOrig if we check all memory with hammer
            ////TODO: or if at some point we do not reconstruct this register when running a test
          }

          if (DcttConfig->singleRowForHammer) {
            maxNumRow = 0;
          }

          for (currRowCount = 0; currRowCount <= maxNumRow; currRowCount++) {
            if (DcttConfig->singleRowForHammer) {
              for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
                if (TestMask &(1 << Channel)) {
                  DcttOutputPrint (DcttMain, "Testing Physical Row %d on Channel %d\n", currentRow[Channel], Channel);
                }
              }
            }
            for (currColCount = 0; currColCount <= maxNumCol; currColCount = currColCount + numberColsCacheline) {
              if (TestMask == 0) {
                break;
              }
              for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
                ////Set current address on registers
                startAddressRegVal[Channel] = Helpers_SetField (
                                                startAddressRegVal[Channel],
                                                currentRow[Channel],
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);
                startAddressRegVal[Channel] = Helpers_SetField (
                                                startAddressRegVal[Channel],
                                                currentCol[Channel],
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                                DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN);
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_BASE_ADDR_START, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, startAddressRegVal[Channel]);
                ////TODO: Check if it is necessary to set wraps(I don't think they are necessary)

                ////Program Hammer Loopcount on loopcount_limit register
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_LOOPCOUNT_LIMIT, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg32Func (DcttMain, ReutRegAddress, DcttConfig->hammerRepetitions);

                ////Set subsequence start and stop for hammer operation
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_CFG, 0, Channel, 0);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, seqCtlRegHammer[Channel]);
              }

              ////Start CPGC engine test
              ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                 DCTT_REUT_GLOBAL_CTRL, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
              DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST));

              do {
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_GLOBAL_ERR, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
                GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

                TestDone = (GlobalError & CPGC_TEST_DONE_MASK) >> 16;
                TestDone = TestDone & ChannelMask;
                ChannelErrors = (GlobalError & CPGC_ERROR_STATUS_MASK);
                ChannelErrors = ChannelErrors & ChannelMask;
              } while ((TestDone != ChannelMask));

              if (ChannelErrors & TestMask) {
                RetVal = CPGCFunctions_ErrorHandler (DcttMain, TestMask, PerBankErrors, GlobalParameters, NULL, NULL);
                if (RetVal != DCTT_SUCCESS) {
                  return RetVal;
                }
              }

              ////Program checking subsequences and look for errors (re-program loopcount to 1 if neighbors or Bank size if checking all neighbors)
              if (DcttConfig->hammerCheckType != DcttHamerCheckNone) {
                for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
                  ////Program check Loopcount on loopcount_limit register
                  ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                     DCTT_REUT_CH_SEQ_LOOPCOUNT_LIMIT, 0, Channel, DCTT_BYTE_CTL_NA);
                  DcttWriteReg32Func (DcttMain, ReutRegAddress, 1);

                  ////Set subsequence start and stop for hammer operation
                  ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                     DCTT_REUT_CH_SEQ_CFG, 0, Channel, 0);
                  DcttWriteReg64Func (DcttMain, ReutRegAddress, seqCtlRegCheck[Channel]);
                }

                ////Start CPGC engine test
                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_GLOBAL_CTRL, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
                DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST));

                do {
                  ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                     DCTT_REUT_GLOBAL_ERR, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
                  GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

                  TestDone = (GlobalError & CPGC_TEST_DONE_MASK) >> 16;
                  TestDone = TestDone & ChannelMask;
                  ChannelErrors = (GlobalError & CPGC_ERROR_STATUS_MASK);
                  ChannelErrors = ChannelErrors & ChannelMask;
                } while ((TestDone != ChannelMask));

                if (ChannelErrors & TestMask) {
                  RetVal = CPGCFunctions_ErrorHandler (DcttMain, TestMask, PerBankErrors, GlobalParameters, NULL, NULL);
                  if (RetVal != DCTT_SUCCESS) {
                    return RetVal;
                  }
                }
              }
              ////Disable channels on which we have reached the maximum number of columns and
              ////move current cell
              for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
                if (TestDirection == UP) {
                  if (currentCol[Channel] < wrapCol[Channel]) {
                    currentCol[Channel] = currentCol[Channel] + numberColsCacheline;

                    startAddressRegVal[Channel] = Helpers_SetField (
                                                    startAddressRegVal[Channel],
                                                    currentCol[Channel],
                                                    DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                                    DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN);
                  } else if (TestMask & (1 << Channel)) {
                    ////TODO: Disable Channel
                    SeqConfigRegVal[Channel] = Helpers_SetField (
                                                 SeqConfigRegVal[Channel],
                                                 0,
                                                 DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                                 DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Disable Global Control
                    ////TODO: Optimize for cases where both channels have the same # of columns
                    DcttLogDebug (DcttMain, "Disabling Channel %d up cols\n", Channel);
                    TestMask = (TestMask & (~(1 << Channel)));

                    ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                       DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
                    DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal[Channel]);
                  }
                } else {
                  //Going down
                  if (currentCol[Channel] > wrapCol[Channel]) {
                    currentCol[Channel] = currentCol[Channel] - numberColsCacheline;

                    startAddressRegVal[Channel] = Helpers_SetField (
                                                    startAddressRegVal[Channel],
                                                    currentCol[Channel],
                                                    DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_START,
                                                    DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_COL_ADDRESS_LEN);
                  } else if (TestMask & (1 << Channel)) {
                    ////TODO: Disable Channel
                    SeqConfigRegVal[Channel] = Helpers_SetField (
                                                 SeqConfigRegVal[Channel],
                                                 0,
                                                 DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                                 DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Disable Global Control
                    ////TODO: Optimize for cases where both channels have the same # of cols
                    TestMask = (TestMask & (~(1 << Channel)));

                    ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                       DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
                    DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal[Channel]);
                  }
                }
              }
            }
            ////Enable channels on which row is in range and is populated
            for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
              //Restart Col
              currentCol[Channel] = startCol[Channel];

              if (DCTT_RankInChannelExists (DcttMain, 0, Rank, Channel)) {
                TestMask = (TestMask | (1 << Channel));

                SeqConfigRegVal[Channel] = Helpers_SetField (
                                             SeqConfigRegVal[Channel],
                                             1,
                                             DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                             DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Enable Global Control

                ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                   DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
                DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal[Channel]);
              }

              if (TestDirection == UP) {
                if (currentRow[Channel] < wrapRow[Channel]) {
                  currentRow[Channel] = currentRow[Channel] + 1;

                  startAddressRegVal[Channel] = Helpers_SetField (
                                                  startAddressRegVal[Channel],
                                                  currentRow[Channel],
                                                  DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                                  DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);
                } else if (TestMask & (1 << Channel)) {
                  ////TODO: Disable Channel
                  ////TODO: Optimize for cases where both channels have the same # of rows
                  TestMask = (TestMask & (~(1 << Channel)));

                  SeqConfigRegVal[Channel] = Helpers_SetField (
                                               SeqConfigRegVal[Channel],
                                               0,
                                               DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                               DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Disable Global Control

                  ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                     DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
                  DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal[Channel]);
                }
              } else {
                //Going down
                if (currentRow[Channel] > wrapRow[Channel]) {
                  currentRow[Channel] = currentRow[Channel] - 1;

                  startAddressRegVal[Channel] = Helpers_SetField (
                                                  startAddressRegVal[Channel],
                                                  currentRow[Channel],
                                                  DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_START,
                                                  DCTT_REUT_CH_SEQ_BASE_ADDR_START_F_ROW_ADDRESS_LEN);
                } else if (TestMask & (1 << Channel)) {
                  ////TODO: Disable Channel
                  ////TODO: Optimize for cases where both channels have the same # of rows
                  TestMask = (TestMask & (~(1 << Channel)));

                  SeqConfigRegVal[Channel] = Helpers_SetField (
                                               SeqConfigRegVal[Channel],
                                               0,
                                               DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                               DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);//Disable Global Control

                  ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                                     DCTT_REUT_CH_SEQ_CFG, 0, Channel, DCTT_BYTE_CTL_NA);
                  DcttWriteReg64Func (DcttMain, ReutRegAddress, SeqConfigRegVal[Channel]);
                }
              }
            }
          }

          TestMask = 0;//The whole Bank test will be done inside this runner
        } else {
          //Normal runner
          ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                             DCTT_REUT_GLOBAL_CTRL, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
          DcttWriteReg32Func (DcttMain, ReutRegAddress, (CPGC_CLEAR_ERRORS_START_TEST));

          do {
            ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                               DCTT_REUT_GLOBAL_ERR, 0, DCTT_CHANNEL_CTL_NA, DCTT_BYTE_CTL_NA);
            GlobalError = DcttReadReg32Func (DcttMain, ReutRegAddress);

            TestDone = (GlobalError & CPGC_TEST_DONE_MASK) >> 16;
            TestDone = TestDone & ChannelMask;
            ChannelErrors = (GlobalError & CPGC_ERROR_STATUS_MASK);
            ChannelErrors = ChannelErrors & ChannelMask;
            if (globalErrRegValPrev != GlobalError) {
              globalErrRegValPrev = GlobalError;
              DcttLogDebug (DcttMain, "Normal Runner--; GlobalError:  0x%0x   TestDone:  0x%0x\n", GlobalError, TestDone);
            }
          } while ((TestDone != ChannelMask));
        }

        if (ChannelErrors & TestMask) {
          RetVal = CPGCFunctions_ErrorHandler (DcttMain, TestMask, PerBankErrors, GlobalParameters, NULL, &CurrentAddress[0]);
          if (RetVal != DCTT_SUCCESS) {
            return RetVal;
          }
        }

        for (Channel = 0; Channel < DcttConfig->numberChannels; Channel++) {
          if ((TestMask >> Channel) & ((~ChannelErrors) >> Channel) & 0x1) {
            ReutRegAddress = DcttGetMcAddressFunc (DcttMain,
                               DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_0, 0, Channel, DCTT_BYTE_CTL_NA);
            CurrentAddressRegVal = DcttReadReg64Func (DcttMain, ReutRegAddress);

            CurrentAddress[Channel].Col = Helpers_GetField (
                                            CurrentAddressRegVal,
                                            DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_COL_ADDRESS_START,
                                            DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_COL_ADDRESS_LEN
                                            );

            CurrentAddress[Channel].Row = Helpers_GetField (
                                            CurrentAddressRegVal,
                                            DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_ROW_ADDRESS_START,
                                            DCTT_REUT_CH_SEQ_BASE_ADDR_CURRENT_F_ROW_ADDRESS_LEN
                                            );
          }

          if (TestMask & (1 << Channel)) {
            RetVal = CPGCFunctions_CalculateRemainingLoopcount (
                       DcttMain,
                       TestDirection,
                       &NewLoopcount[Channel],
                       &CurrentAddress[Channel],
                       Channel,
                       CPGHammerRepetitions,
                       firstBankToTest[Channel],
                       lastBankToTest[Channel],
                       FALSE
                       );
          } else {
            NewLoopcount[Channel] = 0;
          }

          if (NewLoopcount[Channel] == 0) {
            //Nothing more to do on this Channel, disable it
            SeqConfigRegVal[Channel] = Helpers_SetField (
                                         SeqConfigRegVal[Channel],
                                         0,
                                         DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_START,
                                         DCTT_REUT_CH_SEQ_CFG_F_GLOBAL_CTRL_LEN);
            TestMask = (TestMask & (~(1 << Channel)));
          }
        }
        DcttLogDebug (DcttMain,"TestMask: 0x%x\tRetVal: 0x%x\n", TestMask, RetVal);
      } while ((TestMask != 0) && (RetVal == DCTT_SUCCESS));
    }
  }
  return RetVal;
}
#endif
