## @file
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2015 - 2016 Intel Corporation.
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
# @par Specification
##

ASM_GLOBAL ASM_PFX(SaMmioRead64)
ASM_PFX(SaMmioRead64):
   subl    $16, %esp
   movq    %mm0, (%esp)       #Save mm0 on stack
   movl    20(%esp), %edx     #edx = Address
   movq    (%edx), %mm0       #mm0 = [Address]
   movq    %mm0, 8(%esp)      #Store mm0 on Stack
   movq    (%esp), %mm0       #Restore mm0
   emms
   movl    8(%esp), %eax      #eax = [Address][31:0]
   movl    12(%esp), %edx     #edx = [Address][64:32]
   addl    $16, %esp
   ret

#-----------------------------------------------------------------------------
#
#  Section:     SaMmioWrite64
#
#  Description: Write 64 bits to the Memory Mapped I/O space.
#  Use MMX instruction for atomic access, because some MC registers have side effect.
#
#  @param[in] Address - Memory mapped I/O address.
#  @param[in] Value   - The value to write.
#
#-----------------------------------------------------------------------------

#UINT64
#SaMmioWrite64 (
#  IN UINTN Address,
#  IN UINT64 Value
#  )

ASM_GLOBAL ASM_PFX(SaMmioWrite64)
ASM_PFX(SaMmioWrite64):
   subl    $8, %esp
   movq    %mm0, (%esp)       #Save mm0 on Stack
   movl    12(%esp), %edx     #edx = Address
   movq    16(%esp), %mm0     #mm0 = Value
   movq    %mm0, (%edx)       #[Address] = Value
   movq    (%esp), %mm0       #Restore mm0
   emms
   movl     16(%esp), %eax    #eax = Value[31:0]
   movl     20(%esp), %edx    #edx = Value[64:32]
   addl     $8, %esp
   ret
