;; @file
;  Assembly code for the IA-32 resources
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 2016 Intel Corporation.
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

SECTION .text

extern ASM_PFX(mErrorCodeFlag) ; Error code flags for exceptions

ExternalVectorTablePtr DQ 0 ; point to the external interrupt vector table

;
; Float control word initial value:
; all exceptions masked, double-extended-precision, round-to-nearest
;
mFpuControlWord       DW      037Fh
;
; Multimedia-extensions control word:
; all exceptions masked, round-to-nearest, flush to zero for masked underflow
;
mMmxControlWord       DD      01F80h

global ASM_PFX(InitializeExternalVectorTablePtr)
ASM_PFX(InitializeExternalVectorTablePtr):
  mov  rax, ExternalVectorTablePtr
  mov  [rax], rcx
  ret

;
;
;
;------------------------------------------------------------------------------
;  Generic IDT Vector Handlers for the Host. They are all the same so they
;  will compress really well.
;
;  By knowing the return address for Vector 00 you can can calculate the
;  vector number by looking at the call CommonInterruptEntry return address.
;  (return address - (AsmIdtVector00 + 5))/8 == IDT index
;
;------------------------------------------------------------------------------

ALIGN   8

global ASM_PFX(AsmIdtVector00)
ASM_PFX(AsmIdtVector00):
%rep    256
        call  ASM_PFX(CommonInterruptEntry)
        dw ( $ - ASM_PFX(AsmIdtVector00) - 5 ) / 8 ; vector number
        nop
%endrep


;---------------------------------------;
; CommonInterruptEntry                  ;
;---------------------------------------;
; The follow algorithm is used for the common interrupt routine.

;
; +---------------------+ <-- 16-byte aligned ensured by processor
; +    Old SS           +
; +---------------------+
; +    Old RSP          +
; +---------------------+
; +    RFlags           +
; +---------------------+
; +    CS               +
; +---------------------+
; +    RIP              +
; +---------------------+
; +    Error Code       +
; +---------------------+
; + RCX / Vector Number +
; +---------------------+
; +    RBP              +
; +---------------------+ <-- RBP, 16-byte aligned
;

global ASM_PFX(CommonInterruptEntry)
ASM_PFX(CommonInterruptEntry):

  cli
  ;
  ; All interrupt handlers are invoked through interrupt gates, so
  ; IF flag automatically cleared at the entry point
  ;
  ;
  ; Calculate vector number
  ;
  xchg    rcx, [rsp] ; get the return address of call, actually, it is the address of vector number.
  movzx   ecx, word [rcx]
  cmp     ecx, 32         ; Intel reserved vector for exceptions?
  jae     .NoErrorCode
  mov     rax,ASM_PFX(mErrorCodeFlag)
  mov     rax,[rax]
  bt      ecx,eax
  jc      .l0

.NoErrorCode:
  ;
  ; Push a dummy error code on the stack
  ; to maintain coherent stack map
  ;
  push    qword [rsp]
  mov     qword [rsp + 8], 0
.l0:
  push    rbp
  mov     rbp, rsp

  ;
  ; Since here the stack pointer is 16-byte aligned, so
  ; EFI_FX_SAVE_STATE_X64 of EFI_SYSTEM_CONTEXT_x64
  ; is 16-byte aligned
  ;

;; UINT64  Rdi, Rsi, Rbp, Rsp, Rbx, Rdx, Rcx, Rax;
;; UINT64  R8, R9, R10, R11, R12, R13, R14, R15;
  push r15
  push r14
  push r13
  push r12
  push r11
  push r10
  push r9
  push r8
  push rax
  push qword [rbp + 8]   ; RCX
  push rdx
  push rbx
  push qword [rbp + 48]  ; RSP
  push qword [rbp]       ; RBP
  push rsi
  push rdi

;; UINT64  Gs, Fs, Es, Ds, Cs, Ss;  insure high 16 bits of each is zero
  movzx   rax, word [rbp + 56]
  push    rax                      ; for ss
  movzx   rax, word [rbp + 32]
  push    rax                      ; for cs
  mov     rax, ds
  push    rax
  mov     rax, es
  push    rax
  mov     rax, fs
  push    rax
  mov     rax, gs
  push    rax

  mov     [rbp + 8], rcx               ; save vector number

;; UINT64  Rip;
  push    qword [rbp + 24]

;; UINT64  Gdtr[2], Idtr[2];
  sub     rsp, 16
  sidt    [rsp]
  sub     rsp, 16
  sgdt    [rsp]

;; UINT64  Ldtr, Tr;
  xor     rax, rax
  str     ax
  push    rax
  sldt    ax
  push    rax

;; UINT64  RFlags;
  push    qword [rbp + 40]

;; UINT64  Cr0, Cr1, Cr2, Cr3, Cr4, Cr8;
  mov     rax, cr8
  push    rax
  mov     rax, cr4
  or      rax, 208h
  mov     cr4, rax
  push    rax
  mov     rax, cr3
  push    rax
  mov     rax, cr2
  push    rax
  xor     rax, rax
  push    rax
  mov     rax, cr0
  push    rax

;; UINT64  Dr0, Dr1, Dr2, Dr3, Dr6, Dr7;
  mov     rax, dr7
  push    rax
;; clear Dr7 while executing debugger itself
  xor     rax, rax
  mov     dr7, rax

  mov     rax, dr6
  push    rax
;; insure all status bits in dr6 are clear...
  xor     rax, rax
  mov     dr6, rax

  mov     rax, dr3
  push    rax
  mov     rax, dr2
  push    rax
  mov     rax, dr1
  push    rax
  mov     rax, dr0
  push    rax

;; FX_SAVE_STATE_X64 FxSaveState;

  sub rsp, 512
  mov rdi, rsp
  db 0fh, 0aeh, 00000111y ;fxsave [rdi]

;; UINT32  ExceptionData;
  push    qword [rbp + 16]

;; call into exception handler
  mov     rcx, [rbp + 8]
  mov     rax, ExternalVectorTablePtr  ; get the interrupt vectors base
  mov     rax, [rax]
  mov     rax, [rax + rcx * 8]
  or      rax, rax                        ; NULL?

  je    nonNullValue;

;; Prepare parameter and call
;  mov     rcx, [rbp + 8]
  mov     rdx, rsp
  ;
  ; Per X64 calling convention, allocate maximum parameter stack space
  ; and make sure RSP is 16-byte aligned
  ;
  sub     rsp, 4 * 8 + 8
  call    rax
  add     rsp, 4 * 8 + 8

nonNullValue:
  cli
;; UINT64  ExceptionData;
  add     rsp, 8

;; FX_SAVE_STATE_X64 FxSaveState;

  mov rsi, rsp
  db 0fh, 0aeh, 00001110y ; fxrstor [rsi]
  add rsp, 512

;; UINT64  Dr0, Dr1, Dr2, Dr3, Dr6, Dr7;
  pop     rax
  mov     dr0, rax
  pop     rax
  mov     dr1, rax
  pop     rax
  mov     dr2, rax
  pop     rax
  mov     dr3, rax
;; skip restore of dr6.  We cleared dr6 during the context save.
  add     rsp, 8
  pop     rax
  mov     dr7, rax

;; UINT64  Cr0, Cr1, Cr2, Cr3, Cr4, Cr8;
  pop     rax
  mov     cr0, rax
  add     rsp, 8   ; not for Cr1
  pop     rax
  mov     cr2, rax
  pop     rax
  mov     cr3, rax
  pop     rax
  mov     cr4, rax
  pop     rax
  mov     cr8, rax

;; UINT64  RFlags;
  pop     qword [rbp + 40]

;; UINT64  Ldtr, Tr;
;; UINT64  Gdtr[2], Idtr[2];
;; Best not let anyone mess with these particular registers...
  add     rsp, 48

;; UINT64  Rip;
  pop     qword [rbp + 24]

;; UINT64  Gs, Fs, Es, Ds, Cs, Ss;
  pop     rax
  ; mov     gs, rax ; not for gs
  pop     rax
  ; mov     fs, rax ; not for fs
  ; (X64 will not use fs and gs, so we do not restore it)
  pop     rax
  mov     es, rax
  pop     rax
  mov     ds, rax
  pop     qword [rbp + 32]  ; for cs
  pop     qword [rbp + 56]  ; for ss

;; UINT64  Rdi, Rsi, Rbp, Rsp, Rbx, Rdx, Rcx, Rax;
;; UINT64  R8, R9, R10, R11, R12, R13, R14, R15;
  pop     rdi
  pop     rsi
  add     rsp, 8               ; not for rbp
  pop     qword [rbp + 48] ; for rsp
  pop     rbx
  pop     rdx
  pop     rcx
  pop     rax
  pop     r8
  pop     r9
  pop     r10
  pop     r11
  pop     r12
  pop     r13
  pop     r14
  pop     r15

  mov     rsp, rbp
  pop     rbp
  add     rsp, 16
  iretq



global ASM_PFX(LongMode)
ASM_PFX(LongMode):

in_long_mode:
    ;
    ; Debug Stop
    ;
    jmp   in_long_mode

    ;
    ; We're in long mode, so marshall the arguments to call the
    ; passed in function pointers
    ; Recall
    ;         [ebp][10h] = HobStart
    ;         [ebp][18h] = Stack
    ;         [ebp][20h] = PpisNeededByDxeIplEntryPoint <--- Call this first (for each call, pass HOB pointer)
    ;         [ebp][28h] = DxeCoreEntryPoint            <--- Call this second
    ;
    mov rbx, [rbp+18h]        ; Setup the stack
    mov rsp, rbx              ; On a new stack now

    mov rcx, [rbp+10h]        ; Pass Hob Start in RCX
    mov rax, [rbp+20h]        ; Get the function pointer for
                              ; PpisNeededByDxeIplEntryPoint into EAX
    call far [rax]            ; Make the call into PpisNeededByDxeIplEntryPoint

    mov ecx, [rbp+10h]        ; Pass Hob Start in RCX
    mov eax, [rbp+28h]        ; Get the function pointer for
                              ; DxeCoreEntryPoint into EAX
    call [rax]               ; Make the call into Dxe Core

    call ASM_PFX(CommonInterruptEntry)

    mov rdi, ASM_PFX(CommonInterruptEntry)

    lgdt [rdi]

    lidt [rdi]

    call [rax]      ; Make the call into PpisNeededByDxeIplEntryPoint

    call rax

    ;
    ; Should never get here.
    ;
no_long_mode:
    jmp   no_long_mode
    ;
    ; WE SHOULD NEVER GET HERE!!!!!!!!!!!!!
    ;

;
; Initializes floating point units for requirement of UEFI specification.
;
; This function initializes floating-point control word to 0x037F (all exceptions
; masked,double-extended-precision, round-to-nearest) and multimedia-extensions control word
; (if supported) to 0x1F80 (all exceptions masked, round-to-nearest, flush to zero
; for masked underflow).
;
global ASM_PFX(CpuInitFloatPointUnit)
ASM_PFX(CpuInitFloatPointUnit):

    ;
    ; Initialize floating point units
    ;
    ; The following opcodes stand for instruction 'finit'
    ; to be supported by some 64-bit assemblers
    ;
    DB      9Bh, 0DBh, 0E3h
    mov     rax, mFpuControlWord
    fldcw   [rax]

    ;
    ; Set OSFXSR bit 9 in CR4
    ;
    mov     rax, cr4
    or      rax, 200h
    mov     cr4, rax
    mov     rax, mMmxControlWord
    ldmxcsr [rax]
    ret


