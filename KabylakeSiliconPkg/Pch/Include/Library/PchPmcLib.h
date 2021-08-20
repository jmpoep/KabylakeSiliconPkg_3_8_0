/** @file
  Header file for PchPmcLib.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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
#ifndef _PCH_PMC_LIB_H_
#define _PCH_PMC_LIB_H_

typedef enum {
  WarmBoot          = 1,
  ColdBoot,
  PwrFlr,
  PwrFlrSys,
  PwrFlrPch,
  PchPmStatusMax
} PCH_PM_STATUS;

/**
  Query PCH to determine the Pm Status

  @param[in] PmStatus - The Pch Pm Status to be probed

  @retval Status TRUE if Status querried is Valid or FALSE if otherwise
**/
BOOLEAN
GetPchPmStatus (
  PCH_PM_STATUS PmStatus
  );

/**
  Funtion to check if Battery lost or CMOS cleared.

  @reval TRUE  Battery is always present.
  @reval FALSE CMOS is cleared.
**/
BOOLEAN
EFIAPI
PchIsRtcBatteryGood (
  VOID
  );

/**
  Check if this system boot is due to Overclocking flow reset during S3
  - BCLK update causes reset.
  - PLL voltage changed causes reset.
  - TjMax update causes reset.

  @retval  TRUE   OC related reset occured during S3
  @retval  FALSE  OC related reset did not occur during S3
**/
BOOLEAN
PmcIsBclkS3Boot (
  VOID
  );

/**
  Set OC BCLK S3 scratchpad bit

**/
VOID
PmcSetBclkS3 (
  VOID
  );

/**
  Clear OC BCLK S3 scratchpad bit

**/
VOID
PmcClearBclkS3 (
  VOID
  );

#endif // _PCH_PMC_LIB_H_
