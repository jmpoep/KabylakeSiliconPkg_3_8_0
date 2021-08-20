;; @file
;  Equates for MP initialization
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

VacantFlag                    Equ   00h
NotVacantFlag                 Equ   0ffh
BreakToRunApSignal            Equ   6E755200h

MonitorFilterSize             Equ   40h
WakeUpApCounterInit           Equ   0
WakeUpApPerHltLoop            Equ   1
WakeUpApPerMwaitLoop          Equ   2
WakeUpApPerRunLoop            Equ   3
WakeUpApPerMwaitLoop32        Equ   4
WakeUpApPerRunLoop32          Equ   5

LockLocation                  equ        1000h - 0400h
StackStartAddressLocation     equ        LockLocation + 08h
StackSizeLocation             equ        LockLocation + 10h
CProcedureLocation            equ        LockLocation + 18h
GdtrLocation                  equ        LockLocation + 20h
IdtrLocation                  equ        LockLocation + 2Ah
BufferStartLocation           equ        LockLocation + 34h
Cr3OffsetLocation             equ        LockLocation + 38h
InitFlagLocation              equ        LockLocation + 3Ch
WakeUpApManner                equ        LockLocation + 40h
BistBuffer                    equ        LockLocation + 44h

PAUSE32   MACRO
            DB      0F3h
            DB      090h
            ENDM

;-------------------------------------------------------------------------------

