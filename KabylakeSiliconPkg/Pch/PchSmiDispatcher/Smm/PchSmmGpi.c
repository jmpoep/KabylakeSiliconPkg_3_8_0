/** @file
  File to contain all the hardware specific stuff for the Smm Gpi dispatch protocol.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2015 Intel Corporation.

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
#include "PchSmmHelpers.h"

//
// Structure for GPI SMI is a template which needs to have
// GPI Smi bit offset and Smi Status & Enable registers updated (accordingly
// to choosen group and pad number) after adding it to SMM Callback database
//

GLOBAL_REMOVE_IF_UNREFERENCED CONST PCH_SMM_SOURCE_DESC PCH_GPI_SOURCE_DESC_TEMPLATE = {
  PCH_SMM_NO_FLAGS,
  {
    {
      {
        GPIO_ADDR_TYPE, {0x0}
      },
      S_PCH_GPIO_GP_SMI_EN, 0x0,
    },
    NULL_BIT_DESC_INITIALIZER
  },
  {
    {
      {
        GPIO_ADDR_TYPE, {0x0}
      },
      S_PCH_GPIO_GP_SMI_STS, 0x0,
    }
  },
  {
    {
      ACPI_ADDR_TYPE,
      {R_PCH_SMI_STS}
    },
    S_PCH_SMI_STS,
    N_PCH_SMI_STS_GPIO_SMI
  }
};
