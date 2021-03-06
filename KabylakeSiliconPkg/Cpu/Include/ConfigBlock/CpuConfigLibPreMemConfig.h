/** @file
  CPU PreMemory Config Block.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#ifndef _CPU_CONFIG_LIB_PREMEM_CONFIG_H_
#define _CPU_CONFIG_LIB_PREMEM_CONFIG_H_

#define CPU_CONFIG_LIB_PREMEM_CONFIG_REVISION 3

extern EFI_GUID gCpuConfigLibPreMemConfigGuid;

#pragma pack (push,1)

/**
  CPU Config Library PreMemory Configuration Structure.

  <b>Revision 1</b>:
  - Initial version.

  <b>Revision 2</b>:
  - Added PeciC10Reset.
  - Added PeciSxReset.

  <b>Revision 3</b>:
  - Added DpSscMarginEnable.

**/
typedef struct {
  CONFIG_BLOCK_HEADER Header;            ///< Config Block Header
  UINT32 HyperThreading             : 1; ///< Enable or Disable Hyper Threading; 0: Disable; <b>1: Enable</b>.
  /**
   Enable or disable override of default max non-turbo ratio. If enabled, BIOS will take the value specified in
     CpuRatio policy and updates the max non-turbo ratio. See policy CpuRatio for more details.
     If disabled, BIOS will use the default max non-turbo ratio, and will not use any flex ratio setting.
   - <b>0: Disable</b>
   -    1: Enable
  **/
  UINT32 CpuRatioOverride           : 1;
  /**
  Sets the boot frequency starting from reset vector.
   - 0: Maximum battery performance.
   - <b>1: Maximum non-turbo performance</b>.
   - 2: Turbo performance.
  @note If Turbo is selected BIOS will start in max non-turbo mode and switch to Turbo mode.
  **/
  UINT32 BootFrequency              : 2;
  /**
    Number of processor cores to enable.
    - <b> 0: All cores</b>
    -     1: 1 core
    -     2: 2 cores
    -     3: 3 cores
  **/
  UINT32 ActiveCoreCount            : 3;
  /**
  Processor Early Power On Configuration FCLK setting.
   - <b>0: 800 MHz (ULT/ULX)</b>.
   - <b>1: 1 GHz (DT/Halo)</b>. Not supported on ULT/ULX.
   - 2: 400 MHz.
   - 3: Reserved.
  **/
  UINT32 FClkFrequency              : 2;
  UINT32 JtagC10PowerGateDisable    : 1; ///< Power JTAG in C10 and deeper power states; <b>0: Disable</b>; 1: Enable.
  UINT32 BistOnReset                : 1; ///< <b>(Test)</b> Enable or Disable BIST on Reset; <b>0: Disable</b>; 1: Enable.
  /**
    Enable or Disable Virtual Machine Extensions (VMX) feature.
    -    0: Disable
    - <b>1: Enable</b>
  **/
  UINT32 VmxEnable                  : 1;
  /**
    Enables a mailbox command to resolve rare PECI related Sx issues.
    @note This should only be used on systems that observe PECI Sx issues.
    - <b>0: Disable</b>
    - 1: Enable
  **/
  UINT32 PeciSxReset               : 1;
  /**
    Enables the mailbox command to resolve PECI reset issues during Pkg-C10 exit.
    - 0: Disable
    - <b>1: Enable</b>
  **/
  UINT32 PeciC10Reset               : 1;
  /**
    Enable DisplayPort SSC range reduction
    @note This should only be used on systems that exceeds allowed SSC modulation range as defined in VESA's spec.
    - <b>0: Disable</b>
    - 1: Enable
  **/
  UINT32 DpSscMarginEnable          : 1;
  UINT32 RsvdBits                   : 17;
  /**
    CpuRatio - When CpuRatioOverride is enabled, max non-turbo ratio (Flexible Ratio Boot) is set to CpuRatio.
  **/
  UINT8  CpuRatio;
  UINT8  Reserved[3];                    ///< Reserved for alignment
} CPU_CONFIG_LIB_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _CPU_CONFIG_LIB_PREMEM_CONFIG_H_
