## @file
#  This file implements SEC system agent library
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2014 - 2016 Intel Corporation.
#
#  The source code contained or described herein and all documents related to the
#  source code ("Material") are owned by Intel Corporation or its suppliers or
#  licensors. Title to the Material remains with Intel Corporation or its suppliers
#  and licensors. The Material may contain trade secrets and proprietary and
#  confidential information of Intel Corporation and its suppliers and licensors,
#  and is protected by worldwide copyright and trade secret laws and treaty
#  provisions. No part of the Material may be used, copied, reproduced, modified,
#  published, uploaded, posted, transmitted, distributed, or disclosed in any way
#  without Intel's prior express written permission.
#
#  No license under any patent, copyright, trade secret or other intellectual
#  property right is granted to or conferred upon you by disclosure or delivery
#  of the Materials, either expressly, by implication, inducement, estoppel or
#  otherwise. Any license under such intellectual property rights must be
#  express and approved by Intel in writing.
#
#  Unless otherwise agreed by Intel in writing, you may not remove or alter
#  this notice or any other notice embedded in Materials by Intel or
#  Intel's suppliers or licensors in any way.
#
#  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
#  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
#  the terms of your license agreement with Intel or your vendor. This file may
#  be modified by the user, subject to additional terms of the license agreement.
#
#@par Specification Reference:
##

.INCLUDE "SecSaLibGcc.inc"

.macro RET_EBP
  jmp     *%ebp
.endm

.ifdef FSP_FLAG
.equ   FSPT_CFG_PCI_EXPRESS_BASE_OFF,               0x48      #FsptConfig.PcdPciExpressBaseAddress offset
.equ   FSPT_CFG_PCI_EXPRESS_LENGHTH_OFF,            0x50      #FsptConfig.PcdPciExpressRegionLength offset
#.macro    CALL_EDI   RoutineLabel
# #.local   ReturnAddress
#  movl    $ReturnAddress, %edi
#  jmp     RoutineLabel
#  ReturnAddress:
#.endm
.endif

ASM_GLOBAL ASM_PFX(SecSaInit)
ASM_PFX(SecSaInit):

.ifdef FSP_FLAG
  #
  # Get FSP-T Config region offset, to get the FSP-T UPD values
  #
  movl    $ReadFsptConfig, %edi        # CALL_EDI  AsmGetFspInfoHeaderNoStack
  jmp     AsmGetFspInfoHeaderNoStack
ReadFsptConfig:
  movl    0x1C(%eax), %ecx            # Read FsptImageBaseAddress
  addl    0x24(%eax), %ecx            # Get Cfg Region base address = FsptImageBaseAddress + CfgRegionOffset
.endif
  #
  # Program PCI Express base address
  #
  movl    $PCIEX_BAR_REG, %eax               # B0:D0:F0:R60
  mov     $0x0CF8, %dx
  out     %eax, %dx
.ifdef FSP_FLAG
  movl    FSPT_CFG_PCI_EXPRESS_LENGHTH_OFF(%ecx), %eax          # Read FsptConfig.PcdPciExpressRegionLength
.else
  movl    PcdGet32 (PcdPciExpressRegionLength), %eax
.endif
  mov     $0x4, %dx                          # Default is PCIEXBAR length is 64MB ([2:1] = 10b)
  cmpl    $0x10000000, %eax                  # Is it 256MB length?
  jne     Check128MB
  mov     $0x0, %dx                          # Set PCIEXBAR length as 256MB ([2:1] = 00b)
  jmp     ProgramLength
Check128MB:
  cmpl    $0x8000000, %eax                   # Is it 128MB length?
  jne     ProgramLength
  mov     $0x2, %dx                          # Set PCIEXBAR length as 128MB ([2:1] = 01b)
ProgramLength:
.ifdef FSP_FLAG
  movl    FSPT_CFG_PCI_EXPRESS_BASE_OFF(%ecx), %eax            # Read FsptConfig.PcdPciExpressBaseAddress
.else
  movl    PcdGet64 (PcdPciExpressBaseAddress), %eax
.endif
  or      %dx,  %ax
  orl     $(0 | 1), %eax                     # PCIEX_EN_BIT_SETTING = 1
  mov     $0x0CFC, %dx
  out     %eax, %dx

  #
  # Enable MCH Bar
  #
.ifdef FSP_FLAG
  movl    FSPT_CFG_PCI_EXPRESS_BASE_OFF(%ecx), %esi            # Read FsptConfig.PcdPciExpressBaseAddress
.else
  movl    PcdGet64 (PcdPciExpressBaseAddress), %esi
.endif
  addl    $MCHBAR_REG, %esi
  movl    PcdGet64 (PcdMchBaseAddress), %eax
  orl     $0x01, %eax
  movl    %eax, (%esi)
  #
  # Clear upper 32bit for MCHBAR
  #
  xorl    %eax, %eax
  movl    %eax, 0x04(%esi)
  RET_EBP

#SecSaInit    ENDP
