;;@file
;   This file contains the code to go from real mode to protected mode.
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

;------------------------------------------------------------------------------
;
; Module Name:
;
;   crcpm32.asm
;
; Abstract:
;
;
;
; Notes:
;
;------------------------------------------------------------------------------

   .686p
   .xmm

.XLIST

; Files generated during build time...do not edit!!!
   include peentry.inc

.LIST

_TEXT16         SEGMENT PARA USE16 PUBLIC 'CODE16'

ALIGN 16

;------------------------------------------------------------------------------
; _PM32Entry:
;       In this sample implementation, entry to this procedure is from
;       a FAR JMP at the reset vector itself. Then load GDT, enter protected
;       mode, and performs a far jump into 32-bit flat code.
;
; Input:
;       Nothing.
;
; Output:
;       Nothing.
;
; Destroys:
;       All.
;
; Note:
;------------------------------------------------------------------------------
_PM32Entry      PROC    NEAR    PUBLIC

   ;
   ; Save BIST state currently in EAX into MM0
   ;
   movd    MM0, eax

   ;
   ; Switch to Protected mode.
   ;
   xor     eax, eax
   mov     ax, cs
   mov     ebx, eax                           ; Save the code segment for use later
   mov     ds, ax
   DB      66h
   lgdt    fword ptr cs:GDTDescriptor

   mov     eax, cr0                           ; Get control register 0
   or      eax, 00000003h                     ; Set PE bit (bit #0) & MP bit (bit #1)
   mov     cr0, eax                           ; Activate protected mode
   mov     eax, cr4                           ; Get control register 4
   or      eax, 00000600h                     ; Set OSFXSR bit (bit #9) & OSXMMEXCPT bit (bit #10)
   mov     cr4, eax

   ; Set up selectors for Protected Mode entry.
   mov     ax, SYS_DATA_SEL
   mov     ds, ax
   mov     es, ax
   mov     fs, ax
   mov     gs, ax
   mov     ss, ax

   ;
   ; Go to Protected32
   ;
   jmp     FWORD PTR cs:[CpuRefCodeLinearAddress]

; 16-bit Selector and 32-bit offset value for the FAR JMP to Processor Reference Code.

CpuRefCodeLinearAddress   LABEL   FWORD
   DD      BIOSINITENTRYPOINT
   DW      LINEAR_CODE_SEL

	ALIGN	16

	PUBLIC  BootGDTtable

; GDT[0]: 0x00: Null entry, never used.
GDT_BASE:
NULL_SEL        EQU     $ - GDT_BASE            ; Selector [0]
BootGDTtable    DD      0
                DD      0
;
; Linear code segment descriptor
;
LINEAR_CODE_SEL EQU     $ - GDT_BASE            ; Selector [0x8]
                DW      0FFFFh                  ; limit 0xFFFFF
                DW      0                       ; base 0
                DB      0
                DB      09Bh                    ; present, ring 0, code, execute/read, non-conforming, accessed
                DB      0CFh                    ; page-granular, 32-bit
                DB      0
; System data segment descriptor
SYS_DATA_SEL    EQU     $ - GDT_BASE            ; Selector [0x10]
                DW      0FFFFh                  ; limit 0xFFFFF
                DW      0                       ; base 0
                DB      0
                DB      093h                    ; present, ring 0, data, read/write, expand-up, accessed
                DB      0CFh                    ; page-granular, 32-bit
                DB      0

; F000h code segment descriptor
F000_CODE_SEL   EQU     $ - GDT_BASE            ; Selector [0x18]
                DW      0FFFFh                  ; limit 0xFFFF
                DW      0000h                   ; base 0xF000
                DB      0Fh
                DB      09Bh                    ; present, ring 0, code, execute/read, non-conforming, accessed
                DB      000h                    ; byte-granular, 16-bit
                DB      0

GDT_SIZE        EQU     $ - BootGDTtable        ; Size, in bytes

; Global Descriptor Table Descriptor
GDTDescriptor:                                          ; GDT descriptor
                DW      GDT_SIZE - 1                    ; GDT limit
                DW      LOWWORD OFFSET BootGDTtable     ; GDT base address
                DW      0ffffh



_PM32Entry      ENDP

_TEXT16 ENDS

END

