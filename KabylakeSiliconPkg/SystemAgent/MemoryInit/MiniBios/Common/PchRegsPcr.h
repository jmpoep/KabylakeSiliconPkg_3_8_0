/** @file
  Register names for PCH private chipset register

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
#ifndef _PCH_REGS_PCR_H_
#define _PCH_REGS_PCR_H_

///
/// Definition for PCR base address (defined in PchReservedResources.h)
///
#define PCH_PCR_BASE_ADDRESS            0xFD000000
//#define PCH_PCR_MMIO_SIZE               0x01000000
///
/// Definition for PCR address
/// The PCR address is used to the PCR MMIO programming
///
#define PCH_PCR_ADDRESS(Pid, Offset)    (PCH_PCR_BASE_ADDRESS | ((UINT8)(Pid) << 16) | (UINT16)(Offset))

///
/// Definition for SBI PID
/// The PCH_SBI_PID defines the PID for PCR MMIO programming and PCH SBI programming as well.
///
typedef enum {
  PID_BROADCAST1                        = 0xFF,
  PID_BROADCAST2                        = 0xFE,
  //Rsv                                 = 0xFD-0xF0,
  PID_DMI                               = 0xEF,
  PID_ESPISPI                           = 0xEE,
  PID_ICLK                              = 0xED,
  PID_OPIPHY                            = 0xEC,
  //Rsv                                 = 0xEB,
  PID_MPHY0                             = 0xEA,
  PID_MPHY1                             = 0xE9,
  PID_PMC                               = 0xE8,
  //Rsv                                 = 0xE7,
  PID_XHCI                              = 0xE6,
  PID_OTG                               = 0xE5,
  PID_SPE                               = 0xE4,        // Reserved in SKL PCH LP
  PID_SPD                               = 0xE3,        // Reserved in SKL PCH LP
  PID_SPC                               = 0xE2,
  PID_SPB                               = 0xE1,
  PID_SPA                               = 0xE0,
  PID_TAP2IOSFSB1                       = 0xDF,
  PID_TAP2IOSFSB2                       = 0xDE,
  PID_TRSB                              = 0xDD,
  PID_ICC                               = 0xDC,
  PID_GBE                               = 0xDB,
  //Rsv                                 = 0xDA,
  PID_SATA                              = 0xD9,
  //Rsv                                 = 0xD8,
  PID_DSP                               = 0xD7,
  //Rsv                                 = 0xD6,
  PID_FUSE                              = 0xD5,
  PID_FSPROX0                           = 0xD4,
  PID_FSPROX1                           = 0xD3,
  PID_DRNG                              = 0xD2,
  //Rsv                                 = 0xD1,
  PID_MEXFIA                            = 0xD0,
  PID_FIA                               = 0xCF,
  //Rsv                                 = 0xCE-0xCD,
  PID_LPSS                              = 0xCC,
  PID_LPSSEP                            = 0xCB,
  PID_USB2                              = 0xCA,
  PID_EUSB2                             = 0xC9,
  //Rsv                                 = 0xC8,
  PID_LPC                               = 0xC7,
  PID_SMB                               = 0xC6,
  PID_P2S                               = 0xC5,
  PID_ITSS                              = 0xC4,
  PID_RTC                               = 0xC3,
  //Rsv                                 = 0xC2-0xC1,
  PID_SCS                               = 0xC0, // Reserved in SKL PCH H
  PID_ISHBR                             = 0xBF,
  PID_ISH                               = 0xBE,
  PID_PSF4                              = 0xBD,
  PID_PSF3                              = 0xBC,
  PID_PSF2                              = 0xBB,
  PID_PSF1                              = 0xBA,
  PID_HOTHARM                           = 0xB9,
  PID_EXI                               = 0xB8,
  PID_DFXAGG                            = 0xB7,
  PID_NPK                               = 0xB6,
  //Rsv                                 = 0xB5-0xB0,
  PID_GPIOCOM0                          = 0xAF,
  PID_GPIOCOM1                          = 0xAE,
  PID_GPIOCOM2                          = 0xAD,
  PID_GPIOCOM3                          = 0xAC,
  //Rsv                                 = 0xAB,
  PID_CAM_FLS                           = 0xAA,
  PID_MPHY2                             = 0xA9,
  PID_MPHY3                             = 0xA8,
  //Rsv                                 = 0xA7-0xA6,
  PID_PNCRC                             = 0xA5,
  PID_PNCRB                             = 0xA4,
  PID_PNCRA                             = 0xA3,
  PID_PNCR0                             = 0xA2,
  PID_CAM_CHC                           = 0xA1,
  PID_P2D                               = 0xA0,
  PID_CSME15                            = 0x9F,
  PID_CSME14                            = 0x9E,
  PID_CSME13                            = 0x9D,
  PID_CSME12                            = 0x9C,
  PID_CSME11                            = 0x9B,
  PID_CSME10                            = 0x9A,
  PID_CSME9                             = 0x99,
  PID_CSME8                             = 0x98,
  PID_CSME7                             = 0x97,
  PID_CSME6                             = 0x96,
  PID_CSME5                             = 0x95,
  PID_CSME4                             = 0x94,
  PID_CSME3                             = 0x93,
  PID_CSME2                             = 0x92,
  PID_CSME1                             = 0x91,
  PID_CSME0                             = 0x90,
  PID_MEPSF                             = 0x8F,
  //Rsv                                 = 0x8E-0x8A,
  PID_PSTH                              = 0x89
  //Rsv                                 = 0x88-0x30,
  //PID_EVA                             = 0x2F-0x00,
} PCH_SBI_PID;

#endif
