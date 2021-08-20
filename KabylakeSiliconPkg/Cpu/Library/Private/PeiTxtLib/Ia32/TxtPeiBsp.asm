;; @file
;  This file contains the code to launch BIOS ACM functions in PEI phase
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
;@par Specification
;;


    .XLIST
    include txt.inc
    .LIST

    .686p
    .MMX
    .XMM
    .MODEL FLAT,C
    .CODE

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Launch BiosAcm SCLEAN
;
;  Setup GETSEC environment (protected mode, mtrrs, etc) and
;    invoke GETSEC:ENTERACCS with requested BIOS ACM entry point.
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------

LaunchBiosAcmSclean PROC PUBLIC
        ;
        ; Tell where we are
        ;
        mov     eax, 11110000h
        in      ax, 80h
        mov     ah, PORT80_CODE_PREFIX + TXT_LAUNCH_SCLEAN
        out     80h, eax
        ;
        ; Enable SMXE, SSE and debug extensions always.
        ;
        mov     eax, CR4
        or      eax, CR4_OSFXSR + CR4_DE + CR4_SMXE
        mov     CR4, eax
        ;
        ; Prepare cache of BSP
        ;
        mov     esi, TXT_PUBLIC_BASE + BIOACM_ADDR
        mov     edi, 0

        CALL_NS PrepareCacheForAcModuleRetNS

        CALL_NS CleanMcaRetNS

IFDEF MKF_TXT_RLP_INIT
  IF MKF_TXT_RLP_INIT
        CALL_NS InitializeApsRetNS
  ENDIF
ENDIF

        ;
        ; Call GETSEC[ENTERACCS]
        ;
        cli
        mov     eax, ENTERACCS          ; eax = ENTERACCS
        mov     ebx, TXT_PUBLIC_BASE + BIOACM_ADDR
        mov     ebx, [ebx]
        mov     ecx, [ebx].ACM_HEADER.AcmSize
        shl     ecx, 2
        xor     edx, edx
        xor     edi, edi
        mov     esi, TXT_LAUNCH_SCLEAN

        _GETSEC

        jmp     DoPowerCycleReset
LaunchBiosAcmSclean  ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Launch BiosAcm Alias Check
;
;  Setup GETSEC environment (protected mode, mtrrs, etc) and
;   invoke GETSEC:ENTERACCS with requested BIOS ACM entry point.
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------

LaunchBiosAcmAcheck PROC PUBLIC
        ;
        ; Tell where we are
        ;

        mov     eax, 11110000h
        in      ax, 80h
        mov     ah, PORT80_CODE_PREFIX + TXT_LAUNCH_ACHECK
        out     80h, eax

        ;
        ; Enable SMXE, SSE and debug extensions always.
        ;
        mov     eax, CR4
        or      eax, CR4_OSFXSR + CR4_DE + CR4_SMXE
        mov     CR4, eax

        ;
        ; Prepare cache of BSP
        ;
        mov     esi, TXT_PUBLIC_BASE + BIOACM_ADDR
        mov     edi, 0

        CALL_NS PrepareCacheForAcModuleRetNS

        CALL_NS CleanMcaRetNS

ifdef MKF_TXT_RLP_INIT
  if MKF_TXT_RLP_INIT
        CALL_NS InitializeApsRetNS
  endif
endif
        ;
        ; Call GETSEC[ENTERACCS]
        ;
        cli
        mov     eax, ENTERACCS          ; eax = ENTERACCS
        mov     ebx, TXT_PUBLIC_BASE + BIOACM_ADDR
        mov     ebx, [ebx]
        mov     ecx, [ebx].ACM_HEADER.AcmSize
        shl     ecx, 2
        xor     edx, edx
        xor     edi, edi
        mov     esi, TXT_LAUNCH_ACHECK

        _GETSEC

        jmp     DoPowerCycleReset
LaunchBiosAcmAcheck  ENDP

DoGlobalReset PROC PUBLIC
        mov     dx, 0CF8h               ; Make warm system reset through port 0CF9h
        mov     eax, 8000FAACh          ; to be global system reset - set bit 20
        out     dx, eax                 ; of device 1F
        mov     dx, 0CFCh
        in      eax, dx
        or      eax, (1 SHL 20)
        out     dx, eax

        mov     dx, 0CF9h               ; After return from SCLEAN function
        mov     al, 0                   ; system must be reset.
        out     dx, al
        mov     dx, 0CF9h               ; After return from SCLEAN function
        mov     al, 6                   ; system must be reset.
        out     dx, al
        cli
        hlt
        jmp     $

DoGlobalReset ENDP

DoPowerCycleReset PROC PUBLIC
        mov     dx, 0CF8h               ; Make warm system reset through port 0CF9h
        mov     eax, 8000FAACh          ; to be global system reset - set bit 20
        out     dx, eax                 ; of device 1F
        mov     dx, 0CFCh
        in      eax, dx
        or      eax, (1 SHL 20)
        out     dx, eax

        mov     dx, 0CF9h               ; After return from SCLEAN function
        mov     al, 0                   ; system must be reset.
        out     dx, al
        mov     dx, 0CF9h               ; After return from SCLEAN function
        mov     al, 0Eh                 ; system must be reset.
        out     dx, al
        cli
        hlt
        jmp     $

DoPowerCycleReset ENDP

DoHostReset PROC PUBLIC
        mov     dx, 0CF8h               ; Make warm system reset through port 0CF9h
        mov     eax, 8000FAACh          ; to be global system reset - set bit 20
        out     dx, eax                 ; of device 1F
        mov     dx, 0CFCh
        in      eax, dx
        and     eax, NOT (1 SHL 20)
        out     dx, eax

        mov     dx, 0CF9h               ; After return from SCLEAN function
        mov     al, 0                   ; system must be reset.
        out     dx, al
        mov     dx, 0CF9h               ; After return from SCLEAN function
        mov     al, 6                   ; system must be reset.
        out     dx, al
        cli
        hlt
        jmp     $

DoHostReset ENDP

DoCpuReset PROC PUBLIC
        mov     dx, 0CF8h               ; Make warm system reset through port 0CF9h
        mov     eax, 8000FAACh          ; to be global system reset - set bit 20
        out     dx, eax                 ; of device 1F
        mov     dx, 0CFCh
        in      eax, dx
        and     eax, NOT (1 SHL 20)
        out     dx, eax

        mov     dx, 0CF9h               ; Issue a CPU only reset by CF9h
        mov     al, 0                   ; toggle bit2 from 0 to 1
        out     dx, al
        mov     dx, 0CF9h               ; Issue a CPU only reset by CF9h
        mov     al, 4                   ;
        out     dx, al
        cli
        hlt
        jmp     $

DoCpuReset ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Prepare Cache for AcModule NoStack
;    MTRRs are set per BIOS spec
;
;  @param[in] esi     BiosAc Address
;  @param[in] edi     in memory flag
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------

PrepareCacheForAcModuleRetNS PROC FAR PUBLIC
        ;
        ; Enable local APIC
        ;
        mov     ecx, IA32_APIC_BASE
        rdmsr                       ; Get APIC Base
        and     eax, BASE_ADDR_MASK ; Just need the address
        mov     DWORD PTR [eax+SPURIOUS_VECTOR_1], 1FFh ; Enable APIC, keep spurious vector
        ;
        ; Disable cache
        ;
        mov     eax, cr0            ; set CR0:CD and CR0:NE, clear CR0:NW
        or      eax, CR0_CD_MASK OR CR0_NE_MASK
        and     eax, NOT CR0_NW_MASK
        mov     cr0, eax
        cmp     edi, 0
        je      @F                  ; JIf stackless environment
        wbinvd                      ; Invalidate the cache
        jmp     disableMtrrs

@@:
        invd

disableMtrrs:
        ;
        ; Disable all MTRRs
        ;
        xor     eax, eax
        xor     edx, edx
        mov     ecx, IA32_MTRR_DEF_TYPE
        wrmsr



        ;
        ; Disable NEM only if PRMRR is not locked!
        ;
        ;
        mov     ecx, MSR_PRMRR_PHYS_MASK
        rdmsr
        test    eax, B_MSR_PRMRR_PHYS_MASK_LOCK
        jnz     skip_nem_disable        ; Skip NEM disable if PRMRR lock bit is set to avoid taking GP fault.
nem_disable:
        mov     ecx, NO_EVICT_MODE
        rdmsr
        and     eax, NOT (BIT1)
        wrmsr                           ; Clear No-Eviction Mode Run bit
        mov     ecx, NO_EVICT_MODE
        rdmsr
        and     eax, NOT (BIT0)
        wrmsr                           ; Clear No-Eviction Mode SETUP bit

        invd
skip_nem_disable:
        ;
        ; Clear all variable MTRRs
        ;
        mov     ecx, IA32_MTRR_CAP
        rdmsr
        and     eax, 0FFh
        shl     eax, 1
        mov     ecx, eax
        xor     eax, eax
        xor     edx, edx
@@:
        add     ecx, IA32_MTRR_PHYSBASE0 - 1
        wrmsr
        sub     ecx, IA32_MTRR_PHYSBASE0 - 1
        loop    @B

        ;
        ; Determine size of AC module
        ;
        mov     esi, [esi]
        mov     eax, [esi].ACM_HEADER.AcmSize
        shl     eax, 2          ;  ...in bytes (ACM header has size in dwords)
        ;
        ; Round up to page size
        ;
        mov     ecx, eax        ; Save
        and     ecx, 0FFFFF000h     ; Number of pages in AC module
        and     eax, 0FFFh      ; Number of "less-than-page" bytes
        jz      rounded
        mov     eax, 1000h      ; Add the whole page size

rounded:
        add     eax, ecx        ; eax - rounded up AC module size

        ;
        ; Define "local" vars for this routine
        ;
        ACM_SIZE_TO_CACHE   TEXTEQU <mm0>
        ACM_BASE_TO_CACHE   TEXTEQU <mm1>
        NEXT_MTRR_INDEX     TEXTEQU <mm2>
        NEXT_MTRR_SIZE      TEXTEQU <mm3>
        ;
        ; Initialize "locals"
        ;
        sub     ecx, ecx
        movd    NEXT_MTRR_INDEX, ecx    ; Start from MTRR0

        ;
        ; Save remaining size to cache
        ;
        movd    ACM_SIZE_TO_CACHE, eax  ; Size of ACM that must be cached
        movd    ACM_BASE_TO_CACHE, esi  ; Base ACM address

nextMtrr:
        ;
        ; Get remaining size to cache
        ;
        movd    eax, ACM_SIZE_TO_CACHE
        and     eax, eax
        jz  done            ; If no left size - we are done
        ;
        ; Determine next size to cache.
        ; We start from bottom up. Use the following algorythm:
        ; 1. Get our own alignment. Max size we can cache equals to our alignment
        ; 2. Determine what is bigger - alignment or remaining size to cache.
        ;    If aligment is bigger - cache it.
        ;      Adjust remaing size to cache and base address
        ;      Loop to 1.
        ;    If remaining size to cache is bigger
        ;      Determine the biggest 2^N part of it and cache it.
        ;      Adjust remaing size to cache and base address
        ;      Loop to 1.
        ; 3. End when there is no left size to cache or no left MTRRs
        ;
        movd    esi, ACM_BASE_TO_CACHE
        bsf     ecx, esi    ; Get index of lowest bit set in base address
        ;
        ; Convert index into size to be cached by next MTRR
        ;
        mov     edx, 1h
        shl     edx, cl     ; Alignment is in edx
        cmp     edx, eax    ; What is bigger, alignment or remaining size?
        jbe     gotSize     ; JIf aligment is less
        ;
        ; Remaining size is bigger. Get the biggest part of it, 2^N in size
        ;
        bsr     ecx, eax    ; Get index of highest set bit
        ;
        ; Convert index into size to be cached by next MTRR
        ;
        mov     edx, 1
        shl     edx, cl     ; Size to cache

gotSize:
        mov     eax, edx
        movd    NEXT_MTRR_SIZE, eax ; Save

        ;
        ; Compute MTRR mask value:  Mask = NOT (Size - 1)
        ;
        dec     eax         ; eax - size to cache less one byte
        not     eax         ; eax contains low 32 bits of mask
        or      eax, MTRR_VALID     ; Set valid bit

        ;
        ; Program mask register
        ;
        mov     ecx, IA32_MTRR_PHYSMASK0 ; setup variable mtrr
        movd    ebx, NEXT_MTRR_INDEX
        add     ecx, ebx

        mov     edx, 7Fh    ; 8K range (FFFFFFE800)
        wrmsr
        ;
        ; Program base register
        ;
        sub     edx, edx
        mov     ecx, IA32_MTRR_PHYSBASE0 ; setup variable mtrr
        add     ecx, ebx        ; ebx is still NEXT_MTRR_INDEX

        movd    eax, ACM_BASE_TO_CACHE
        or      eax, WB         ; set type to write back
        wrmsr
        ;
        ; Advance and loop
        ; Reduce remaining size to cache
        ;
        movd    ebx, ACM_SIZE_TO_CACHE
        movd    eax, NEXT_MTRR_SIZE
        sub     ebx, eax
        movd    ACM_SIZE_TO_CACHE, ebx

        ;
        ; Increment MTRR index
        ;
        movd    ebx, NEXT_MTRR_INDEX
        add     ebx, 2
        movd    NEXT_MTRR_INDEX, ebx
        ;
        ; Increment base address to cache
        ;
        movd    ebx, ACM_BASE_TO_CACHE
        movd    eax, NEXT_MTRR_SIZE
        add     ebx, eax
        movd    ACM_BASE_TO_CACHE, ebx

        jmp nextMtrr

done:
        ;
        ; Enable variable MTRRs
        ;
        xor     edx, edx
        mov     eax, MTRR_ENABLE; enable mtrrs (but not fixed ones)
        mov     ecx, IA32_MTRR_DEF_TYPE
        wrmsr
        ;
        ; Enable cache
        ;
        mov     eax, cr0    ; Enable caching - WB (NW stays clear)
        and     eax, NOT CR0_CD_MASK
        mov     cr0, eax

        RET_NS
PrepareCacheForAcModuleRetNS ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Clean Mca NoStack
;
;  Setup GETSEC environment (protected mode, mtrrs, etc)
;     invoke GETSEC:ENTERACCS with requested module
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------

CleanMcaRetNS PROC NEAR PUBLIC
        ;
        ; check getsec[capabilities], skip if parameters not supported
        ;
        mov     eax, CAPABILITIES          ; eax = CAPABILITIES

        _GETSEC

        or      ebx, ebx
        jnz     exit

        and     eax, CAPABILITIES_PARAM
        jz      exit
        ;
        ; check getsec[parameters], skip MCi clr if set
        ;
        mov     eax, PARAMETERS          ; eax = PARAMETERS

        _GETSEC

        or      eax, PARAMETERS_MCi_HDL
        je      exit
        ;
        ; Clean all MCi_STATUS MSR registers
        ; SCLEAN will generate GPF otherwise
        ;
        ;mov    ecx, MCG_CAP
        ;rdmsr
        mov     al, 5           ; skl only supports clear mc0-4 early PEI phase
        movzx   ebx, al         ; Bank count to ebx
        sub     eax, eax        ; Write 0 into all MCi_STATUS registers
        sub     edx, edx
        mov     ecx, MC0_STATUS

McaErrorCleanLoopStart:
        wrmsr
        dec     ebx
        jz      exit
        add     ecx, 4          ; Number of MSRs per bank
        jmp     McaErrorCleanLoopStart

exit:
    RET_NS
CleanMcaRetNS ENDP


;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Initialize Aps NoStack
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
InitializeApsRetNS PROC NEAR
        mov     eax, 1
        cpuid
        shr     ebx, 16         ; Total Logical Proc Count in BL
        cmp     bl, 1           ; If 1 thread - nothing to do
        je      exit
        ;
        ; More than one thread
        ; Get APIC address
        ;
        mov     ecx, IA32_APIC_BASE
        rdmsr                           ; Get APIC Base
        and     eax, BASE_ADDR_MASK     ; Just need the address
        mov     edi, eax                ; edi points to APIC base
        ;
        ; Wait for  APIC ready
        ;
        mov     edx, IcrStatusRetNs
        mov     ecx, 200
        CALL_NS ltWaitStatusRetNS

        ;
        ; Broadcast INIT message to put all APs into Wait for SIPI state
        ; C0500 -> Destination = All excl self, Delivery = INIT
        ;
        mov     DWORD PTR ICR_LOW[edi], 000C0500h
        mov     edx, NeverStatusRetNS
        mov     ecx, 10000
        CALL_NS ltWaitStatusRetNS   ; Wait full 10ms
        ;
        ; Create vector used in the following SIPI message
        ; Below address is the real mode address of AP code in Boot Block
        ; LTCACHE.BIN containg AP thread code must be placed at the above address
        ; in Boot block (FFFF0000h). See file LTCACHE.ASM
        ;
        mov     esi, TXT_PUBLIC_BASE    ; esi  points to public space
        mov     ebx, [esi+APINIT_ADDR]
        shr     ebx, 12
        and     ebx, 0FFh
        or      ebx, 0C0600h            ; This is message

        ;
        ; Broadcast SIPI message with our vector
        ; Wait for  APIC ready
        ;
        mov     edx, IcrStatusRetNs
        mov     ecx, 200
        CALL_NS ltWaitStatusRetNS
        ;
        ; Create vector used in the following SIPI message
        ; Below address is the real mode address of AP code in Boot Block
        ; LTCACHE.BIN containg AP thread code must be placed at the above address
        ; in Boot block (FFFF0000h). See file LTCACHE.ASM
        ;
        mov     esi, TXT_PUBLIC_BASE    ; esi  points to public space
        mov     ebx, [esi+APINIT_ADDR]
        shr     ebx, 12
        and     ebx, 0FFh
        or      ebx, 0C0600h            ; This is message
        ;
        ; Send message
        ;
        mov     ICR_LOW[edi], ebx
        ;
        ; Wait 200us as recommended
        ;
        mov     edx, NeverStatusRetNS
        mov     ecx, 200
        CALL_NS ltWaitStatusRetNS
        ;
        ; Broadcast second SIPI message with our vector
        ; Wait for  APIC ready
        ;
        mov     edx, IcrStatusRetNs
        mov     ecx, 200
        CALL_NS ltWaitStatusRetNS
        ;
        ; Create vector used in the following SIPI message
        ; Below address is the real mode address of AP code in Boot Block
        ; LTCACHE.BIN containg AP thread code must be placed at the above address
        ; in Boot block (FFFF0000h). See file LTCACHE.ASM
        ;
        mov     esi, TXT_PUBLIC_BASE    ; esi  points to public space
        mov     ebx, [esi+APINIT_ADDR]
        shr     ebx, 12
        and     ebx, 0FFh
        or      ebx, 0C0600h            ; This is message
        ;
        ; Send message
        ;
         mov    ICR_LOW[edi], ebx
        ;
        ; Wait for semaphore reflect number of CPUs
        ;
        mov     eax, 1
        cpuid
        shr     ebx, 16         ; Total Logical Proc Count in BL
        dec     bl                      ; bl is number of APs

        mov     esi, TXT_PUBLIC_BASE    ; esi  points to public space
        mov     edx, SemaphoreStatusRetNS
        mov     ecx, 100000
        CALL_NS ltWaitStatusRetNS   ; Wait for up to 100ms

        ;
        ; Broadcast INIT message to put all APs back into Wait for SIPI state
        ; Wait for  APIC ready
        ;
        mov     edx, IcrStatusRetNs
        mov     ecx, 200
        CALL_NS ltWaitStatusRetNS
        ;
        ; Send message
        ;
        mov     DWORD PTR ICR_LOW[edi], 000C0500h

        mov     edx, NeverStatusRetNS
        mov     ecx, 10000
        CALL_NS ltWaitStatusRetNS   ; Wait full 10ms

exit:
        RET_NS
InitializeApsRetNS ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Save Ap Config
;
;  @param[in]  ApCfg   pointer to save area
;
;  Function is called in memory present environment on S3 resume
;    path. Saves contents of all MTRRs into table plus some registers.
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
SaveApConfig PROC NEAR PUBLIC, ApCfg:PTR QWORD

        pushad

        mov     esi, ApCfg
        mov     ecx, IA32_MTRR_CAP
        rdmsr
        and     eax, 0FFh
        shl     eax, 1
        mov     ecx, eax

@@:
        add     ecx, IA32_MTRR_PHYSBASE0 - 1
        rdmsr
        mov     [esi], eax
        mov     [esi+4], edx
        add     esi, SIZEOF QWORD
        sub     ecx, IA32_MTRR_PHYSBASE0 - 1
        loop    @B

        mov     ecx, IA32_MTRR_DEF_TYPE
        rdmsr
        mov     [esi], eax
        mov     [esi+4], edx

        sidt    [esi+8]

        mov     ecx, IA32_MISC_ENABLE_MSR
        rdmsr
        mov     [esi+010h], eax
        mov     [esi+014h], edx

        popad
        ret
SaveApConfig ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Startup All APs
;
;  @param[in]   pFunction   pointer to function to execute on AP
;  @param[in]   pParam      pointer to pFunction parameters
;
;  Procedure is called in memmory present enironment on S3
;    resume path and is executed on BSP
;    It saves memory at address 1000h into buffer
;    It then copies AP start-up code into address 1000h
;    Then variables in the 1000h area are updated and APs are started
;    After APs finish execution of function passed as parameter they
;    are halted.  BSP restores contents 1000h area from buffer and
;    returns.
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------

Func TYPEDEF PROTO

PFUNC TYPEDEF PTR Func

StartUp STRUCT
        db      0FAh                    ; cli
        db      066h, 0BBh              ; mov   ebx, OFFSET gdtLim
        db      StartUp.gdtLim, 0,0,0
        db      066h
        db      067h, 02Eh, 00Fh, 001h, 013h ; lgdt    FWORD PTR cs:[ebx]
        db      00Fh, 020h, 0C0h        ; mov   eax, CR0
        db      00Ch, 001h              ; or    al, 01
        db      00Fh, 022h, 0C0h        ; mov   CR0, eax
        ;
        ; 32 bit jump to 32 bit Function handler
        ;
        db      066h
        db      0eah
fOff    dd      0
fCs     dw      0

        ALIGN   16
fDs     dw      0
gdtLim  dw      ?                       ; Size of LT GDT in bytes
gdtBas  dd      ?                       ; Physical address of LT GDT
fParam  dd      ?
smphr   dd      ?
StartUp ENDS


StartupAllAPs PROC NEAR, pFunction:PFUNC, pParam:PTR QWORD
        LOCAL   buffer:StartUp
        LOCAL   savedESP:DWORD

        pushad
        mov     savedESP, esp
        mov     eax, 1
        cpuid
        shr     ebx, 16         ; Total Logical Proc Count in BL
        cmp     bl, 1           ; If 1 thread - nothing to do
        je      exit

        ;
        ; More than one thread. Prepare Startup area
        ;
        mov     esi, 1000h              ; Source
        lea     edi, buffer             ; Destination
        mov     ecx, sizeof StartUp / 4
        CALL_NS MemCopyRetNS

        mov     esi, offset ApHandler16 ; Source
        mov     edi, 1000h              ; Destination
        mov     ecx, sizeof StartUp / 4
        CALL_NS MemCopyRetNS
        ;
        ; Update Srartup area variables
        ;
        mov     edi, 1000h
        mov     ds:[edi].StartUp.fCs, cs
        mov     ds:[edi].StartUp.fDs, ds
        mov     eax, pFunction
        mov     ds:[edi].StartUp.fOff, eax
        sub     eax, eax
        mov     ds:[edi].StartUp.smphr, eax
        mov     eax, pParam
        mov     ds:[edi].StartUp.fParam, eax
        sgdt    ds:[edi].StartUp.gdtLim

        ;
        ; Get APIC address
        ;
        mov     ecx, IA32_APIC_BASE
        rdmsr                       ; Get APIC Base
        and     eax, BASE_ADDR_MASK ; Just need the address
        mov     edi, eax            ; edi points to APIC base

        ;
        ; Wait for  APIC ready
        ;
        mov     edx, IcrStatusRetNs
        mov     ecx, 200
        CALL_NS ltWaitStatusRetNS

        ;
        ; Broadcast INIT message to put all APs into Wait for SIPI state
        ; C0500 -> Destination = All excl self, Delivery = INIT
        ;
        mov     DWORD PTR ICR_LOW[edi], 000C0500h
        mov     edx, NeverStatusRetNS
        mov     ecx, 10000
        CALL_NS ltWaitStatusRetNS   ; Wait full 10ms
        ;
        ; Broadcast SIPI message with our vector
        ; Wait for  APIC ready
        ;
        mov     edx, IcrStatusRetNs
        mov     ecx, 200
        CALL_NS ltWaitStatusRetNS
        ;
        ; Create vector used in the following SIPI message
        ;
        mov     ebx, 0C0600h + (1000h SHR 12)
        ;
        ; Send message
        ;
        mov     ICR_LOW[edi], ebx
        ;
        ; Wait 200us as recommended
        ;
        mov     edx, NeverStatusRetNS
        mov     ecx, 200
        CALL_NS ltWaitStatusRetNS
        ;
        ; Broadcast second SIPI message with our vector
        ; Wait for  APIC ready
        ;
        mov     edx, IcrStatusRetNs
        mov     ecx, 200
        CALL_NS ltWaitStatusRetNS
        ;
        ; Create vector used in the following SIPI message
        ;
        mov     ebx, 0C0600h + (1000h SHR 12)
        ;
        ; Send message
        ;
        mov     ICR_LOW[edi], ebx
        ;
        ; Wait for semaphore reflect number of CPUs
        ;
        mov     eax, 1
        cpuid
        shr     ebx, 16         ; Total Logical Proc Count in BL
        dec     bl              ; bl is number of APs

        mov     esi, offset ApHandler16
        mov     edx, SemaphoreStatus2RetNS
        mov     ecx, 100000
        CALL_NS ltWaitStatusRetNS   ; Wait for up to 100ms
        ;
        ; Restore StartUp area
        ;
        lea     esi, buffer             ; Source
        mov     edi, 1000h              ; Destination
        mov     ecx, sizeof StartUp / 4
        CALL_NS MemCopyRetNS

exit:
        mov     esp, savedESP
        popad
        ret

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Ap Handler 16 bit
;
;
; This code is copied over address 0:1000. After recieving SIPI
;   AP is directed to this address where it starts execution in real mode.
;   AP first switches to protected mode, loads the same GDT which is used
;   by BSP and jumps to Procedure at fCs:fOff
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------

        ALIGN   16
        ;
        ; Note After coppying this code must be aligned on page boundary!
        ;

ApHandler16  StartUp <>

StartupAllAPs ENDP


;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Put Aps in Wfs
;
;  Procedure is called in memory present environment on S3 resume path.
;    INIT SIPI message is sent to all APs.
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------

PutApsInWfs PROC PUBLIC
        LOCAL   savedESP:DWORD
        pushad
        mov     savedESP, esp

        mov     eax, 1
        cpuid
        shr     ebx, 16         ; Total Logical Proc Count in BL
        cmp     bl, 1           ; If 1 thread - nothing to do
        je      exit

        ;
        ; Get APIC address
        ;
        mov     ecx, IA32_APIC_BASE
        rdmsr                   ; Get APIC Base
        and     eax, BASE_ADDR_MASK ; Just need the address
        mov     edi, eax        ; edi points to APIC base
        ;
        ; Broadcast INIT message to put all APs back into Wait for SIPI state
        ; Wait for  APIC ready
        ;
        mov     edx, IcrStatusRetNs
        mov     ecx, 15
        CALL_NS ltWaitStatusRetNS
        ;
        ; Send message
        ;
        mov     DWORD PTR ICR_LOW[edi], 000C0500h

        mov     edx, NeverStatusRetNS
        mov     ecx, 667
        CALL_NS ltWaitStatusRetNS   ; Wait full 10ms

exit:
        mov     esp, savedESP
        popad
        ret
PutApsInWfs ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Launch Bios Acm Scheck
;
;  Setup GETSEC environment (protected mode, mtrrs, etc) and
;    invoke GETSEC:ENTERACCS with requested BIOS ACM entry point.
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------

LaunchBiosAcmScheck PROC PUBLIC, BiosAcAddr:PTR QWORD

        LOCAL   SavedGdtr:QWORD
        LOCAL   SavedSS:dword
        LOCAL   SavedESP:dword
        LOCAL   SavedCS:dword
        LOCAL   SavedCR3:dword
        pushf
        cli
        pushad
        ;
        ; Tell where we are
        ;
        in      ax, 80h
        mov     ah, PORT80_CODE_PREFIX + TXT_LAUNCH_SCHECK
        out     80h, ax
        ;
        ; Save control registers
        ;
        mov     eax, cr4
        push    eax
        mov     eax, cr0
        push    eax
        ;
        ; Save segment registers
        ;
        push    ds
        push    es
        push    gs
        push    fs
        ;
        ; Save CS
        ;
        sub     eax, eax                ; Clean upper word
        mov     ax, cs
        mov     SavedCS, eax
        ;
        ; Save stack at this level
        ;
        mov     ax, ss
        mov     SavedSS, eax
        mov     SavedESP, esp
        mov     eax, cr3
        mov     SavedCR3, eax
        ;
        ; Save GDT
        ;
        sgdt    SavedGdtr ; save value of gdtr in local variable
        ;
        ; Define "local" vars for this routine
        ;
        SAVED_EBP   TEXTEQU <mm4>
        ;
        ; Save ebp in MMX register
        ;
        movd    SAVED_EBP, ebp          ; Size of ACM that must be cached

        ;
        ; Enable SMXE, SSE and debug extensions always.
        ;
        mov     eax, CR4
        or      eax, CR4_OSFXSR + CR4_DE + CR4_SMXE
        mov     CR4, eax
        ;
        ; Prepare cache of BSP
        ;
        mov     esi, BiosAcAddr
        mov     edi, 1

        CALL_NS PrepareCacheForAcModuleRetNS

        CALL_NS CleanMcaRetNS
        ;
        ; Call GETSEC[ENTERACCS]
        ;
        mov     eax, ENTERACCS ; eax = ENTERACCS
        mov     ebx, BiosAcAddr
        mov     ebx, [ebx]
        mov     ecx, [ebx].ACM_HEADER.AcmSize
        shl     ecx, 2
        xor     edx, edx
        mov     edi, S3_RESUME_PATH
        mov     esi, 4

        _GETSEC

        ;
        ; Return point after ACEXIT.
        ;
        movd    ebp, SAVED_EBP
        lea     eax, SavedGdtr
        lgdt    FWORD PTR [eax]
        mov     eax, SavedSS
        mov     ss, ax
        mov     esp, SavedESP
        mov     eax, SavedCR3
        mov     cr3, eax
        ;
        ; Restore segment registers
        ;
        pop     fs
        pop     gs
        pop     es
        pop     ds
        ;
        ; Restore control registers
        ;
        pop     eax
        ;
        ;remain cache disabled until MTRRs restored
        ;
        or      eax, CR0_CD_MASK
        and     eax, NOT CR0_NW_MASK
        wbinvd

        mov     cr0, eax
        pop     eax
        mov     cr4, eax
        ;
        ; Restore CS
        ;
        mov     eax, SavedCS
        push    eax
        push    OFFSET ReloadCS
        retf

ReloadCS:
        popad
        popf
        emms

        ret
LaunchBiosAcmScheck ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Restore Mtrr Programming
;    Function is executed on BSP in memory present environment on S3
;    resume path. Restores contents of all MTRRs from table
;
;  @param[in]   ApMtrrTab    pointer to save area
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
RestoreMtrrProgramming PROC NEAR PUBLIC, ApMtrrTab:PTR QWORD
        LOCAL   savedESP:DWORD
        pushad
        mov     savedESP, esp

        mov     esi, ApMtrrTab
        CALL_NS RestoreMtrrProgrammingRetNS

        mov     esp, savedESP
        popad
        ret
RestoreMtrrProgramming ENDP


;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Restore Mtrr Programming NoStack
;    Restores contents of all MTRRs from table
;
;  @param[in]   esi     pointer to save area
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
RestoreMtrrProgrammingRetNS PROC NEAR PUBLIC
        mov     eax, cr0    ; set CR0:CD and CR0:NE, clear CR0:NW
        or      eax, CR0_CD_MASK OR CR0_NE_MASK
        and     eax, NOT CR0_NW_MASK
        mov     cr0, eax
        wbinvd          ; flush and invalidate the cache

        xor     edx, edx
        mov     eax, MTRR_ENABLE + MTRR_FIXED_ENABLE ; enable mtrrs
        mov     ecx, 2FFh
        wrmsr

        mov     ecx, IA32_MTRR_CAP
        rdmsr
        and     eax, 0FFh
        shl     eax, 1
        mov     ecx, eax

@@:
        add     ecx, IA32_MTRR_PHYSBASE0 - 1
        mov     eax, [esi]
        mov     edx, [esi+4]
        wrmsr
        add     esi, SIZEOF QWORD
        sub     ecx, IA32_MTRR_PHYSBASE0 - 1
        loop    @B

        mov     ecx, IA32_MTRR_DEF_TYPE
        mov     eax, [esi]
        mov     edx, [esi+4]
        wrmsr
        mov     ecx, IA32_MISC_ENABLE_MSR
        mov     eax, [esi+010h]
        mov     edx, [esi+014h]
        wrmsr

        mov     eax, cr0    ; Enable caching - WB (NW stays clear)
        and     eax, NOT CR0_CD_MASK
        mov     cr0, eax

        RET_NS
RestoreMtrrProgrammingRetNS ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Restore Ap Config
;  Function is executed on AP in memory present environment on S3
;    resume path. Restores contents of all MTRRs from table
;
;  @param[in]   esi  pointer to save area
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
RestoreApConfig PROC NEAR PUBLIC
        mov     eax, CR4
        or      eax, CR4_OSFXSR + CR4_DE
        mov     CR4, eax

        mov     esi, 1000h
        mov     ds, cs:[esi].StartUp.fDs
        mov     es, cs:[esi].StartUp.fDs
        mov     fs, cs:[esi].StartUp.fDs
        mov     gs, cs:[esi].StartUp.fDs
        mov     ss, cs:[esi].StartUp.fDs

        mov     esi, [esi].StartUp.fParam

        CALL_NS RestoreMtrrProgrammingRetNS

        lidt    FWORD PTR [esi+8]

        jmp     updateSemaphore

RestoreApConfig ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Do Ap Init
;
;  Contents of startup area at 1000h
;  Executed on AP. Persforms CPU initialization for running
;    of GETSEC
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
DoApInit PROC NEAR PUBLIC
        mov     eax, CR4
        or      eax, CR4_OSFXSR + CR4_DE + CR4_SMXE
        mov     CR4, eax

        mov     esi, 1000h
        mov     ds, cs:[esi].StartUp.fDs

        mov     esi, [esi].StartUp.fParam
        mov     edi, 1

        CALL_NS PrepareCacheForAcModuleRetNS

        CALL_NS CleanMcaRetNS

updateSemaphore::
        mov     ecx, 1000h + StartUp.smphr
        lock    inc  DWORD PTR [ecx]

hltLoop:
        cli
        hlt
        jmp     hltLoop

DoApInit ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Mem Copy NoStack
;  Swaps contents of two input buffers.
;
;  @param[in]   esi    from linear address
;  @param[in]   edi    to linear address
;  @param[in]   ecx    swap size in dwords
;  @param[in]   ds     flat segment
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------

MemCopyRetNS PROC NEAR

start:
        mov     eax, ds:[esi]       ; source
        mov     ds:[edi], eax
        add     esi, 4
        add     edi, 4
        loop    start
        RET_NS
MemCopyRetNS ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  lt Wait Status NoStack
;  Calls status procedure. If status is met - returns Z and
;   NZ otherwise.
;   Status procedure is required to return Z if status is met and
;   NZ if not
;
;  @param[in]   cx     Number of usec
;  @param[in]   edx    offset of Status procedure
;
;  @param[out]  Z if status is met
;       NZ - timeout occured
;       NC - always
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
ltWaitStatusRetNS PROC NEAR

        mov     esi, edx        ; save procedure
        mov     dx, 1808h       ; dx = acpi timer i/o address
waitLoop:
        in      eax, dx         ; eax = initial value
        mov     ebx, eax        ; ebx = initial value

        CALL_NS esi             ; Call status procedure.
        jz      exit            ; Z - status met

waitLoop0:
        in      eax, dx
        sub     eax, ebx
        cmp     eax, 4           ; 1.11 us, ~1 us
        jl      waitLoop0
        loop    waitLoop
        mov     ax, 2
        or      ax, 1           ; Clear the ZERO flag - timeout.
                                ; This also clears C flag
exit:
        RET_NS
ltWaitStatusRetNS ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Icr Status NoStack
;  Calls status procedure. If status is met - returns Z and
;   NZ otherwise.
;   Status procedure is required to return Z if status is met and
;   NZ if not
;
;  @param[in]   ds  - Flat
;  @param[in]   edi - xAPIC Base Address
;  @param[out]  Z if status is met
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
IcrStatusRetNS PROC NEAR PUBLIC
        test    DWORD PTR ICR_LOW[edi], BIT12
        RET_NS
IcrStatusRetNS ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Semaphore Status NoStack
;  Returns ZF if semaphore is 0
;
;  @param[in]   ds   Flat
;  @param[out]  ZF if status is met
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
SemaphoreStatusRetNS PROC NEAR PUBLIC
        bswap   eax
        mov     al, BYTE PTR [esi+SEMAPHORE]
        cmp     al, bl
        bswap   eax
        RET_NS
SemaphoreStatusRetNS ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Procedure:   Semaphore Status 2 NoStack
;
;  @param[in]   ds   Flat
;  @param[out]  ZF if status is met
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
SemaphoreStatus2RetNS PROC NEAR PUBLIC
        bswap   eax
        mov     al, BYTE PTR [esi].StartUp.smphr
        cmp     al, bl
        bswap   eax
        RET_NS
SemaphoreStatus2RetNS ENDP

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Never Status NoStack
;
;  @param[out]  ZF not set
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
NeverStatusRetNS PROC NEAR PUBLIC
        or      dx, dx          ; dx is never 0 so return is NZ
        RET_NS
NeverStatusRetNS ENDP



END
