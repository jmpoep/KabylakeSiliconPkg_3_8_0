/** @file
  Macros to simplify and abstract the interface to PCI configuration.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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
#ifndef _SAACCESS_H_
#define _SAACCESS_H_

#include "SaRegs.h"
#include "SaCommonDefinitions.h"      // AdvancedFeaturesContent

///
/// SystemAgent Base Address definition
///
#ifndef STALL_ONE_MICRO_SECOND
#define STALL_ONE_MICRO_SECOND  1
#endif
#ifndef STALL_ONE_MILLI_SECOND
#define STALL_ONE_MILLI_SECOND  1000
#endif

#ifndef MINTREE_FLAG
//
// SA DMI configuration
//
#define SA_DMI_MAX_LANE    0x04
#define SA_DMI_MAX_BUNDLE  0x02
#endif //MINTREE_FLAG
//
// SA PCI Express* Port configuration
//
#define SA_PEG_BUS_NUM     0x00
#define SA_PEG_DEV_NUM     0x01
#define SA_PEG10_DEV_NUM   SA_PEG_DEV_NUM
#define SA_PEG10_FUN_NUM   0x00
#ifndef MINTREE_FLAG
#define SA_PEG11_DEV_NUM   SA_PEG_DEV_NUM
#define SA_PEG11_FUN_NUM   0x01
#define SA_PEG12_DEV_NUM   SA_PEG_DEV_NUM
#define SA_PEG12_FUN_NUM   0x02
#define SA_PEG_MAX_FUN     0x03
#define SA_PEG_MAX_LANE    0x10
#define SA_PEG_MAX_BUNDLE  0x08

#define SA_SWING_FULL      0x0
#define SA_SWING_REDUCED   0x1
#define SA_SWING_MINIMUM   0x2



//
// PCI Express* Port configuration Hardware Strapping value
//
#define SA_PEG_x8_x4_x4  0x00
#define SA_PEG_x8_x8_x0  0x02
#define SA_PEG_x16_x0_x0 0x03

///
/// The value before AutoConfig match the setting of PCI Express Base Specification 1.1, please be careful for adding new feature
///
typedef enum {
  PcieAspmDisabled,
  PcieAspmL0s,
  PcieAspmL1,
  PcieAspmL0sL1,
  PcieAspmAutoConfig,
  PcieAspmMax
} SA_PCIE_ASPM_CONFIG;

///
/// SgMode settings
///
typedef enum {
  SgModeDisabled = 0,
  SgModeReserved,
  SgModeMuxless,
  SgModeDgpu,
  SgModeMax
} SG_MODE;
#endif //MINTREE_FLAG
#endif
