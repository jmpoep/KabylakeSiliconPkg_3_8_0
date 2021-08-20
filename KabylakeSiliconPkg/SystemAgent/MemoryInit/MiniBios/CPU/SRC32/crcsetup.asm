;;@file
;   This routine is only required to instantiate CRC setup options structure
;   and then call the CRC Entry Point (CrcStart) with the CRC setup options
;   structure as a parameter on the stack. Since no memory exists, the CRC
;   setup options structure and the stack are both hard-coded in the ROM.
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 2010 - 2016 Intel Corporation.
;
;  The source code contained or described herein and all documents related to the
;  source code ("Material") are owned by Intel Corporation or its suppliers or
;  licensors. Title to the Material remains with Intel Corporation or its suppliers
;  and licensors. The Material may contain trade secrets and proprietary and
;  confidential information of Intel Corporation and its suppliers and licensors,
;  and is protected by worldwide copyright and trade secret laws and treaty
;  provisions. No part of the Material may be used, copied, reproduced, modified,
;  published, uploaded, posted, transmitted, distributed, or disclosed in any way
;  without Intel's prior express written permission.
;
;  No license under any patent, copyright, trade secret or other intellectual
;  property right is granted to or conferred upon you by disclosure or delivery
;  of the Materials, either expressly, by implication, inducement, estoppel or
;  otherwise. Any license under such intellectual property rights must be
;  express and approved by Intel in writing.
;
;  Unless otherwise agreed by Intel in writing, you may not remove or alter
;  this notice or any other notice embedded in Materials by Intel or
;  Intel's suppliers or licensors in any way.
;
;  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
;  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
;  the terms of your license agreement with Intel or your vendor. This file may
;  be modified by the user, subject to additional terms of the license agreement.
;
;@par Specification Reference:
;;


   .listall
   .686p
   .xmm
   .model   flat,c

.XLIST
   ; Files generated during build time...do not edit!!!
   include crc.i
.LIST

INCLUDE crcoem.inc

.data

platform_initializers   TEXTEQU  <MCH_BAR_BASE,\
                                  PCIE_BAR_BASE,\
                                  SMBUS_BASE,\
                                  HPET_BASE>
                                 
nem_initializers        TEXTEQU  <CODE_REGION_BASE_ADDRESS,\
                                 CODE_REGION_SIZE,\
                                 DATA_STACK_BASE_ADDRESS,\
                                 DATA_STACK_SIZE,\
                                 DATA_HEAP_SIZE>
                                   
ucode_initializers      TEXTEQU  <microcode_start,\ 
                                 microcode_size>
                                 
runtime_initializers    TEXTEQU  <CrcExitAddress,\ 
                                 MEMORY_STACK_ADDR>
                                 

; This is the ROM-based CRC setup options structure.
; Do not change the format of this structure since it is shared
; by the CPU reference code via the file CRC.H. The values can 
; be changed above or by changing the underlying definitions from 
; the file CRCOEM.INC.

rom_options cpu_setup_options    <platform_initializers,\
                                 nem_initializers,\
                                 ucode_initializers,\
                                 runtime_initializers>
                                 ;wdb_initializers,\                                                                    
;
; Microcode updates must be aligned on a paragraph boundary. If more 
; than microcode update is included in the microcode storage block, 
; each microcode update be forced to to align on paragraph boundary.
align 16
PUBLIC microcode_start
PUBLIC microcode_size
; This is the microcode update region that will be searched and loaded
; CPU reference code.
microcode_start label byte
   ; The OEM is required to specify the microcode updates here
   ;
   ; INCLUDE CpuMicrocodeUpdate.inc ; Example line for Microcode Update inclusion
microcode_size EQU ($-microcode_start)

.code

CrcSetup PROC

externdef   CrcStart:NEAR32

   mov   ebp, offset rom_options    ; Set pointer to default options structure   
   jmp   CrcStart                   ; Call CPU reference code

  ; Label for the return address    
CrcExitAddress::
   jmp   $

CrcSetup ENDP   

END
