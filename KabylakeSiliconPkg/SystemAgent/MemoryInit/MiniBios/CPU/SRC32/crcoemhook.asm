;;@file
;   Routine to get setup options for various features.
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 2007 - 2016 Intel Corporation.
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
   include crcoem.inc
.LIST


.const

.code

;-----------------------------------------------------------------------------
; OemStacklessStatusCode: OEM hook for status codes.
;
; Input:    
;  AX = Status code
;
; Register Usage:
;  No memory exists. No stack exists.
;  All registers must be preserved.
;
; Output:   
;  None
;
;-----------------------------------------------------------------------------
oemStacklessStatusCode  PROC

   ; insert OEM code here to display status code
   out   80h, ax
   
   test  ax, ax
   jns   exit
   jmp   $
   
exit:      
   ret
      
oemStacklessStatusCode  ENDP


;-----------------------------------------------------------------------------
; OemMemoryBase: Get the NEM memory start. 
;
; Input:    
;  N/A
;
; Register Usage:
;  eax 
;  
;
; Output:   
;  eax return the data stack base address. 
;
;-----------------------------------------------------------------------------
OemMemoryBase  PROC

   mov eax,DATA_STACK_BASE_ADDRESS 			
   ret
      
OemMemoryBase  ENDP

END
