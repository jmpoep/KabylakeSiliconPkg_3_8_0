/** @file
  Definitions for PCH FVI DXE driver.

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
#ifndef _PCH_FVI_H_
#define _PCH_FVI_H_

#include <PiDxe.h>
#include <Library/SiFviLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/MmPciLib.h>
#include <Library/HobLib.h>
#include <Library/ConfigBlockLib.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/DriverSupportedEfiVersion.h>
#include <Protocol/PciIo.h>
#include <PchAccess.h>
#include <Private/PchConfigHob.h>
#include <Private/PchHsio.h>

#define PCH_FVI_STRING            "Reference Code - SKL PCH"
#define PCH_CRID_STATUS_STRING    "PCH-CRID Status"
#define PCH_CRID_ORIGINAL_VALUE   "PCH-CRID Original Value"
#define PCH_CRID_NEW_VALUE        "PCH-CRID New Value"
#define PCH_CRID_ENABLED          "Enabled "
#define PCH_CRID_DISABLED         "Disabled"
#define SKL_PCH_LPBX_HSIO_STRING  "SKL PCH LP Bx Hsio Version"
#define SKL_PCH_LPCX_HSIO_STRING  "SKL PCH LP Cx Hsio Version"
#define SKL_PCH_HBX_HSIO_STRING   "SKL PCH H Bx Hsio Version"
#define SKL_PCH_HDX_HSIO_STRING   "SKL PCH H Dx Hsio Version"
#define KBL_PCH_HAX_HSIO_STRING   "KBL PCH H Ax Hsio Version"
#define RAID_FVI_STRING           "OPROM - RST - RAID"
#define FVI_PCH_H_BX_HSIO_VERSION \
  { \
    PCH_H_HSIO_VER_BX, 0, 0, 0 \
  }
#define FVI_PCH_H_DX_HSIO_VERSION \
  { \
    PCH_H_HSIO_VER_DX, 0, 0, 0 \
  }
#define FVI_PCH_LP_BX_HSIO_VERSION \
  { \
    PCH_LP_HSIO_VER_BX, 0, 0, 0 \
  }
#define FVI_PCH_LP_CX_HSIO_VERSION \
  { \
    PCH_LP_HSIO_VER_CX, 0, 0, 0 \
  }
#define FVI_KBL_PCH_H_AX_HSIO_VERSION \
  { \
    KBL_PCH_H_HSIO_VER_AX, 0, 0, 0 \
  }

enum {
  RC_VER        = 0,
  PCH_CRID_STATUS,
  PCH_CRID_ORIGINAL,
  PCH_CRID_NEW,
  RAID_VER,
  HSIO_SKLPCHHAX_VER,
  HSIO_SKLPCHLPAX_VER
} PCH_FVI_INDEX;
#endif
