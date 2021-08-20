/** @file
  Register names for PCH DCI device

  Conventions:

  - Prefixes:
    Definitions beginning with "R_" are registers
    Definitions beginning with "B_" are bits within registers
    Definitions beginning with "V_" are meaningful values within the bits
    Definitions beginning with "S_" are register sizes
    Definitions beginning with "N_" are the bit position
  - In general, PCH registers are denoted by "_PCH_" in register names
  - Registers / bits that are different between PCH generations are denoted by
    "_PCH_[generation_name]_" in register/bit names.
  - Registers / bits that are specific to PCH-H denoted by "_H_" in register/bit names.
    Registers / bits that are specific to PCH-LP denoted by "_LP_" in register/bit names.
    e.g., "_PCH_H_", "_PCH_LP_"
    Registers / bits names without _H_ or _LP_ apply for both H and LP.
  - Registers / bits that are different between SKUs are denoted by "_[SKU_name]"
    at the end of the register/bit names
  - Registers / bits of new devices introduced in a PCH generation will be just named
    as "_PCH_" without [generation_name] inserted.

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
#ifndef _PCH_REGS_DCI_H_
#define _PCH_REGS_DCI_H_

//
// DCI PCR Registers
//
#define R_PCH_PCR_DCI_ECTRL                       0x04            ///< DCI Control Register
#define B_PCH_PCR_DCI_ECTRL_HDCIEN                BIT4            ///< Host DCI enable
#define B_PCH_PCR_DCI_ECTRL_HDCIEN_LOCK           BIT0            ///< Host DCI Enable Lock
#define R_PCH_PCR_DCI_ECKPWRCTL                   0x08            ///< DCI Power Control
#define R_PCH_PCR_DCI_PCE                         0x30            ///< DCI Power Control Enable Register
#define B_PCH_PCR_DCI_PCE_HAE                     BIT5            ///< Hardware Autonomous Enable
#define B_PCH_PCR_DCI_PCE_D3HE                    BIT2            ///< D3-Hot Enable
#define B_PCH_PCR_DCI_PCE_I3E                     BIT1            ///< I3 Enable
#define B_PCH_PCR_DCI_PCE_PMCRE                   BIT0            ///< PMC Request Enable

#endif
