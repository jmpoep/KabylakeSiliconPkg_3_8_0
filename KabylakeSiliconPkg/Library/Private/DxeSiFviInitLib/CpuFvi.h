/** @file
  Definitions for CPU FVI DXE driver.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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
#ifndef _CPU_FVI_H_
#define _CPU_FVI_H_

#include <PiDxe.h>
#include <Library/DebugLib.h>
#include <Library/SiFviLib.h>
#include <Library/CpuPlatformLib.h>
#include <BiosGuard.h>

#define CPU_FVI_STRING          "Reference Code - CPU"
#define UCODE_FVI_STRING        "uCode Version"
#define TXT_FVI_STRING          "TXT ACM Version"
#define TXT_ACM_MAJOR_VERSION   0xFF
#define TXT_ACM_MINOR_VERSION   0xFF
#define TXT_ACM_REVISION        0xFF
#define TXT_ACM_BUILD_NUMBER    0xFFFF
#define TXT_VERSION \
  { \
    TXT_ACM_MAJOR_VERSION, TXT_ACM_MINOR_VERSION, TXT_ACM_REVISION, TXT_ACM_BUILD_NUMBER \
  }
#define BIOSGUARD_FVI_STRING    "BIOS Guard Version"
#define BIOSGUARD_MAJOR_VERSION 0xFF
#define BIOSGUARD_MINOR_VERSION 0xFF
#define BIOSGUARD_REVISION      0xFF
#define BIOSGUARD_BUILD_NUMBER  0xFFFF
#define BIOSGUARD_VERSION \
  { \
    BIOSGUARD_MAJOR_VERSION, BIOSGUARD_MINOR_VERSION, BIOSGUARD_REVISION, BIOSGUARD_BUILD_NUMBER \
  }

enum {
  CPU_RC_VER= 0,
  UCODE_VER,
  TXT_VER,
  BIOSGUARD_VER
} CPU_FVI_INDEX;

#endif
