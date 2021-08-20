/** @file
  Used to ensure the Configuration does not viloate any constraints.

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
#include "DcttParametersCheck.h"
#include "DcttDebug.h"

INT32
DcttConfigCheck (
  DCTT_API  *DcttMain
  )
{
  DCTT_CONFIG_PARAMS  *DcttConfig;
  UINT8               swizzleUniqCheck[DCTT_MAX_NUM_SWIZZLE_LANES];
  UINT8               lane;
  UINT8               swizzledLane;

  DcttConfig = &DcttMain->DcttConfigData;

  for (lane = 0; lane < DCTT_MAX_NUM_SWIZZLE_LANES; lane++) {
    swizzleUniqCheck[lane] = 0;
  }

  if (DcttConfig->numberLanesSwizzle > DCTT_MAX_NUM_SWIZZLE_LANES) {
    return BAD_SWIZZLE_CONFIGURATION;
  }

  //Checking swizzle
  for (lane = 0; lane < DCTT_MAX_NUM_SWIZZLE_LANES; lane++) {
    swizzledLane = DcttConfig->swizzle[lane];

    if (DcttConfig->swizzle[lane] >= DCTT_MAX_NUM_SWIZZLE_LANES) {
      DcttLogVerbose (DcttMain, "Found a lane on the swizzle configuration greater than MAX_NUM_LANES\n");
      return BAD_SWIZZLE_CONFIGURATION;
    }
    if ((lane > MAX_LANE_MAP_ANY_LANE) && (swizzledLane > MAX_LANE_MAP_ANY_LANE) && (swizzledLane != lane)) {
      //only the lower MAX_LANE_MAP_ANY_LANE can be mapped to any lane,
      //All lanes higher than MAX_LANE_MAP_ANY_LANE can only be mapped to
      //lanes lower than MAX_LANE_MAP_ANY_LANE.
      DcttLogVerbose (
        DcttMain,
        "Bad swizzel mapping. Lanes greater than %d can only be swizzled with lanes lower than %d\n",
        MAX_LANE_MAP_ANY_LANE,
        MAX_LANE_MAP_ANY_LANE
        );
      return BAD_SWIZZLE_CONFIGURATION;
    }
    swizzleUniqCheck[swizzledLane] = swizzleUniqCheck[swizzledLane] + 1;
    //Checking uniqueness of swizzled lane
    if (swizzleUniqCheck[swizzledLane] > 1) {
      DcttLogVerbose (DcttMain, "Remapping more than 1 lane to the same bit is not allowed.\n");
      return BAD_SWIZZLE_CONFIGURATION;
    }
  }

  if (DcttConfig->numberTests >= MAX_NUMBER_TESTS) {
    DcttLogVerbose (
      DcttMain,
      "Number of tests (%d) is greater than max (%d)\n",
      DcttConfig->numberTests,
      MAX_NUMBER_TESTS
      );
    return TOO_MANY_TESTS;
  }

  //Checking memory traversing order
  if ((DcttConfig->firstOrder == DcttOrderRank)  ||
      (DcttConfig->secondOrder == DcttOrderRank) ||
      (DcttConfig->thirdOrder == DcttOrderRank)  ||
      (DcttConfig->fourthOrder != DcttOrderRank)) {
    DcttLogVerbose (
      DcttMain,
      "Rank has to be the higher memory traversing parameter\n"
      );
    return BAD_MEMORY_TRAVERSING_ORDER;
  }

  return DCTT_SUCCESS;
}
