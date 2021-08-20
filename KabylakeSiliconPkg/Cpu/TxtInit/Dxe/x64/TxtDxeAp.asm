;; @file
;  This file contains DXE AP initialization code.
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 2005 - 2016 Intel Corporation.
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

    .xlist
    include txt.inc
    include mmx64.inc
    .list


    _TEXT   SEGMENT


EXTERN        mAcmBase:QWORD
EXTERN        mApMtrrTab:QWORD
EXTERN        mApIdt:QWORD
EXTERN        mApCr4:QWORD
EXTERN        mApSavedIa32ThermInterruptMSR:QWORD
EXTERN        mApSavedApicThermalValue:DWORD

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Do Ap Init
;
;  @param[in]   AcmBase   Base address of LT BIOS ACM
;
;
;  Initiatialize AP before GETSEC as per TXT BWG
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------

DoApInit PROC FRAME

        START_FRAME
        MAKE_LOCAL ACM_SIZE_TO_CACHE:QWORD
        MAKE_LOCAL ACM_BASE_TO_CACHE:QWORD
        MAKE_LOCAL NEXT_MTRR_INDEX:QWORD
        MAKE_LOCAL NEXT_MTRR_SIZE:QWORD
        ; jmp     $
        END_FRAME

        pushf
        cli
        PUSHA_64

;-----------------------------------------------------------------------------
;
;  Section: Initial RLPs cache requirements
;
;  Description: Ensure CR0.CD and CR0.NW are cleared
;
;-----------------------------------------------------------------------------
        ;
        ; Clear CR0.CD and CR0.NW
        ;
        mov     rax, cr0
        and     rax, NOT (CR0_CD_MASK + CR0_NW_MASK)
        mov     cr0, rax

;-----------------------------------------------------------------------------
;
;  Section: Clean all MCi_STATUS MSR registers
;
;  Description: MCA registers are cleaned
;
;-----------------------------------------------------------------------------
        ;
        ; check smx, skip if smx  not supported
        ;
        mov     rax, cr4
        or      rax, CR4_SMXE
        jne     Continue
        ;
        ; check getsec[capabilities], skip if parameters not supported
        ;
        mov     eax, CAPABILITIES          ; eax = CAPABILITIES

        _GETSEC

        or      ebx, ebx
        jnz     Continue

        or      eax, CAPABILITIES_PARAM
        jne     Continue
        ;
        ; check getsec[parameters], skip MCi clr if set
        ;
        mov     eax, PARAMETERS          ; eax = PARAMETERS

        _GETSEC

        or      eax, PARAMETERS_MCi_HDL
        je      Continue

        mov     rcx, MCG_CAP
        rdmsr
        movzx   rbx, al                 ; ebx = MCR bank count
        xor     rax, rax                ; Write 0 into all MCi_STATUS registers
        xor     rdx, rdx
        mov     rcx, MC0_STATUS

McaErrorCleanLoopStart:
        wrmsr
        dec     rbx
        jz      Continue
        add     rcx, 4                  ; ecx = number of MSRs per bank
        jmp     McaErrorCleanLoopStart

Continue:
        mov     rcx,IA32_APIC_BASE
        rdmsr
        and     rax,BIT11+BIT10
        cmp     rax,BIT11+BIT10
        jne     x2ApicDisabled
        mov     rcx,EFI_MSR_EXT_XAPIC_LVT_THERM
        rdmsr
        and     eax, NOT (B_INTERRUPT_MASK + B_DELIVERY_MODE + B_VECTOR)
        or      eax, (B_INTERRUPT_MASK + V_MODE_SMI)
        wrmsr
        jmp     @f
x2ApicDisabled:
        ; mask thermal LVT
        mov     rcx, IA32_APIC_BASE
        rdmsr               ; Get APIC Base
        and     rax, BASE_ADDR_MASK ; Just need the address
        mov     edx, [rax+LOCAL_APIC_THERMAL_DEF]
        and     edx, NOT (B_INTERRUPT_MASK + B_DELIVERY_MODE + B_VECTOR)
        or      edx, (B_INTERRUPT_MASK + V_MODE_SMI)
        mov     DWORD PTR [rax+LOCAL_APIC_THERMAL_DEF], edx ;disable DTS SMIs
@@:
        POPA_64
        popf

        leave
        ret     0
DoApInit    ENDP


;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Ap Save Config
;
;  Saves AP configuration
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
ApSaveConfig PROC FRAME
        START_FRAME
        END_FRAME

        pushf
        cli
        PUSHA_64

        mov     rcx, IA32_MTRR_CAP
        rdmsr
        and     rax, 0FFh
        shl     rax, 1
        mov     rcx, rax

        lea     rbx, mApMtrrTab

SaveNextMtrr:
        add     rcx, IA32_MTRR_PHYSBASE0 - 1
        rdmsr
        mov     QWORD PTR [rbx+0], rax
        mov     QWORD PTR [rbx+8], rdx
        sub     rcx, IA32_MTRR_PHYSBASE0 - 1
        add     rbx, 10h
        loop    SaveNextMtrr

        mov     rcx, IA32_MTRR_DEF_TYPE
        rdmsr
        mov     QWORD PTR [rbx+0], rax
        mov     QWORD PTR [rbx+8], rdx

        lea     rbx, mApIdt
        sidt    [rbx]
        lea     rbx, mApCr4
        mov     rax, cr4
        mov     QWORD PTR [rbx], rax

        mov     rcx,IA32_APIC_BASE
        rdmsr
        and     rax,BIT11+BIT10
        cmp     rax,BIT11+BIT10
        jne     x2ApicDisabled
        mov     rcx,EFI_MSR_EXT_XAPIC_LVT_THERM
        rdmsr
        lea     rbx, mApSavedApicThermalValue
        mov     DWORD PTR [rbx], eax    ; read and save thermal LVT
        jmp     @f
x2ApicDisabled:

        mov     rcx, IA32_APIC_BASE
        rdmsr               ; Get APIC Base
        and     rax, BASE_ADDR_MASK ; Just need the address
        lea     rbx, mApSavedApicThermalValue
        mov     edx, DWORD PTR [rax+LOCAL_APIC_THERMAL_DEF]
        mov     DWORD PTR [rbx], edx    ; read and save thermal LVT
@@:
        mov     rcx, EFI_MSR_IA32_THERM_INTERRUPT
        rdmsr               ;
        lea     rbx, mApSavedIa32ThermInterruptMSR
        mov     QWORD PTR [rbx+0], rax
        mov     QWORD PTR [rbx+8], rdx
        ;disable THERMAL INT
        and     rax, NOT (BIT0+BIT1+BIT2+BIT4+BIT15+BIT23)
        wrmsr

        wbinvd

        POPA_64
        popf

        leave
        ret 0
ApSaveConfig    ENDP


;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Ap Restore Config
;
;  Restores AP configuration
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
ApRestoreConfig PROC FRAME
        START_FRAME
        END_FRAME

        pushf
        cli
        PUSHA_64

        ;
        ; Disable cache
        ;
        mov     rax, cr0                ; set CR0:CD and CR0:NE, clear CR0:NW
        or      rax, CR0_CD_MASK OR CR0_NE_MASK
        and     rax, NOT CR0_NW_MASK
        mov     cr0, rax
        wbinvd

        mov     rcx, IA32_MTRR_CAP
        rdmsr
        and     rax, 0FFh
        shl     rax, 1
        mov     rcx, rax

        lea     rbx, mApMtrrTab

RestoreNextMtrr:
        add     rcx, IA32_MTRR_PHYSBASE0 - 1
        mov     rax, QWORD PTR [rbx+0]
        mov     rdx, QWORD PTR [rbx+8]
        wrmsr
        sub     rcx, IA32_MTRR_PHYSBASE0 - 1
        add     rbx, 10h
        loop    RestoreNextMtrr

        mov     rax, QWORD PTR [rbx+0]
        mov     rdx, QWORD PTR [rbx+8]
        mov     rcx, IA32_MTRR_DEF_TYPE
        wrmsr

        lea     rbx, mApIdt
        lidt    FWORD PTR [rbx]
        lea     rbx, mApCr4
        mov     rax, QWORD PTR [rbx]
        mov     cr4, rax

        mov     rcx, EFI_MSR_IA32_THERM_INTERRUPT
        lea     rbx, mApSavedIa32ThermInterruptMSR
        mov     rax, QWORD PTR [rbx+0]
        mov     rdx, QWORD PTR [rbx+8]
        wrmsr

        mov     rcx,IA32_APIC_BASE
        rdmsr
        and     rax,BIT11+BIT10
        cmp     rax,BIT11+BIT10
        jne     x2ApicDisabled
        mov     rcx,EFI_MSR_EXT_XAPIC_LVT_THERM
        lea     rbx, mApSavedApicThermalValue
        mov     eax,DWORD PTR [rbx]     ;restore thermal LVT
        xor     rdx,rdx
        wrmsr
        jmp     @f
x2ApicDisabled:

        mov     rcx, IA32_APIC_BASE
        rdmsr               ; Get APIC Base
        and     rax, BASE_ADDR_MASK ; Just need the address
        lea     rbx, mApSavedApicThermalValue
        mov     edx, DWORD PTR [rbx]
        mov     DWORD PTR [rax+LOCAL_APIC_THERMAL_DEF], edx ; restore thermal LVT
@@:
        ;
        ; Enable cache
        ;
        mov     rax, cr0
        and     rax, NOT CR0_CD_MASK
        mov     cr0, rax

        POPA_64
        popf

        leave
        ret 0
ApRestoreConfig ENDP

_TEXT   ENDS

    END
