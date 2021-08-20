/** @file
  Definitions for SA FVI DXE driver.

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
#ifndef _SA_FVI_H_
#define _SA_FVI_H_

#include <PiDxe.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/IoLib.h>
#include <Library/SiFviLib.h>
#include <Library/MmPciLib.h>
#include <Protocol/LegacyBios.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <IndustryStandard/Pci22.h>
#include <SaCommonDefinitions.h>
#include <Private/SaConfigHob.h>
#include <MemInfoHob.h>
///
/// Data definitions
///
#define CRID_DATA 0x69

#define SA_FVI_STRING           "Reference Code - SA - System Agent"
#define MEM_FVI_STRING          "Reference Code - MRC"
#define PCIE_FVI_STRING         "SA - PCIe Version"
#define SA_CRID_STATUS          "SA-CRID Status"
#define SA_CRID_ORIGINAL_VALUE  "SA-CRID Original Value"
#define SA_CRID_NEW_VALUE       "SA-CRID New Value"
#define SA_CRID_ENABLED         "Enabled "
#define SA_CRID_DISABLED        "Disabled"
#define VBIOS_FVI_STRING        "OPROM - VBIOS"

enum {
  SA_RC_VER     = 0,
  MEM_RC_VER,
  PCIE_VER,
  CRID_STATUS,
  CRID_ORIGINAL,
  CRID_NEW,
  VBIOS_VER
} SA_FVI_INDEX;
#endif
