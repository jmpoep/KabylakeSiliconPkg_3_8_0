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
  Copyright 2013 - 2017 Intel Corporation.

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
//#define PCH_PCR_BASE_ADDRESS            0xFD000000
//#define PCH_PCR_MMIO_SIZE               0x01000000
/**
  Definition for PCR address
  The PCR address is used to the PCR MMIO programming
**/
#define PCH_PCR_ADDRESS(Pid, Offset)    (PCH_PCR_BASE_ADDRESS | ((UINT8)(Pid) << 16) | (UINT16)(Offset))

/**
  PCH PCR boot script accessing macro
  Those macros are only available for DXE phase.
**/
#define PCH_PCR_BOOT_SCRIPT_WRITE(Width, Pid, Offset, Count, Buffer) \
          S3BootScriptSaveMemWrite (Width, PCH_PCR_ADDRESS (Pid, Offset), Count, Buffer); \
          S3BootScriptSaveMemPoll (Width, PCH_PCR_ADDRESS (Pid, Offset), Buffer, Buffer, 1, 1);

#define PCH_PCR_BOOT_SCRIPT_READ_WRITE(Width, Pid, Offset, DataOr, DataAnd) \
          S3BootScriptSaveMemReadWrite (Width, PCH_PCR_ADDRESS (Pid, Offset), DataOr, DataAnd); \
          S3BootScriptSaveMemPoll (Width, PCH_PCR_ADDRESS (Pid, Offset), DataOr, DataOr, 1, 1);


/**
  Definition for SBI PID
  The PCH_SBI_PID defines the PID for PCR MMIO programming and PCH SBI programming as well.
**/
#define  PID_DMI                          0xEF
#define  PID_ESPISPI                      0xEE
#define  PID_OPIPHY                       0xEC
#define  PID_MODPHY0                      0xEA
#define  PID_MODPHY1                      0xE9
#define  PID_OTG                          0xE5
#define  PID_XHCI                         0xE6
#define  PID_SPF                          0xC9 // Available only in KBL PCH H
#define  PID_SPE                          0xE4 // Reserved in SKL PCH LP
#define  PID_SPD                          0xE3 // Reserved in SKL PCH LP
#define  PID_SPC                          0xE2
#define  PID_SPB                          0xE1
#define  PID_SPA                          0xE0
#define  PID_ICC                          0xDC
#define  PID_DSP                          0xD7
#define  PID_FIA                          0xCF
#define  PID_SERIALIO                     0xCB
#define  PID_USB2                         0xCA
#define  PID_LPC                          0xC7
#define  PID_SMB                          0xC6
#define  PID_ITSS                         0xC4
#define  PID_RTC                          0xC3
#define  PID_SCS                          0xC0 // Reserved in SKL PCH H
#define  PID_ISHBR                        0xBF
#define  PID_ISH                          0xBE
#define  PID_PSF4                         0xBD
#define  PID_PSF3                         0xBC
#define  PID_PSF2                         0xBB
#define  PID_PSF1                         0xBA
#define  PID_DCI                          0xB8
#define  PID_MMP0                         0xB0 // for SKL-LP only
#define  PID_MODPHY4                      0xB0 // for KBL-H only
#define  PID_GPIOCOM0                     0xAF
#define  PID_GPIOCOM1                     0xAE
#define  PID_GPIOCOM2                     0xAD
#define  PID_GPIOCOM3                     0xAC
#define  PID_CAM_FLS                      0xAA
#define  PID_MODPHY2                      0xA9
#define  PID_MODPHY3                      0xA8
#define  PID_CAM_CHC                      0xA1
#define  PID_CSME12                       0x9C
#define  PID_CSME0                        0x90
#define  PID_CSME_PSF                     0x8F
#define  PID_PSTH                         0x89

typedef  UINT8                            PCH_SBI_PID;

#endif
