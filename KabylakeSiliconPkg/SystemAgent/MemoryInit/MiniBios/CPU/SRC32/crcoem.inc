;;@file
;   Contains equates which are implementation specific.
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


IFNDEF CRCOEM_INC
CRCOEM_INC EQU   1

;
; Define the CodeRegion - using 64KB code area below 4GB
; See BWG - chapter "Restrictions to Using Cache for Stack and Code"
;
IF ROM_SIZE EQ 1
CODE_REGION_BASE_ADDRESS	EQU	0FFF00000h
CODE_REGION_SIZE		EQU	(1024 * 1024)
ELSE
CODE_REGION_BASE_ADDRESS	EQU	0FFE00000h
CODE_REGION_SIZE		EQU	(2 * 1024 * 1024)
ENDIF

;
; Define the DataStack - using 32KB data area at least 4KB away from code
; This must be in an address range the chipset decodes
; See BWG - chapter "Restrictions to Using Cache for Stack and Code"
;
DATA_STACK_BASE_ADDRESS		EQU	0FEF80000h
DATA_STACK_SIZE			EQU	(256 * 1024);(192 * 1024)
DATA_HEAP_SIZE			EQU	(4 * 1024)

MCH_BAR_BASE			EQU	0FED10000h
DMI_BAR_BASE			EQU	0FED18000h
PCIE_BAR_BASE			EQU	0E0000000h
SMBUS_BASE			EQU	0EFA0h
ACPI_BASE_ADDRESS		EQU	01800h
HPET_BASE			EQU	0FED00000h
RCBA_BASE			EQU	0FED1C000h
GDXC_BASE			EQU	0FED80000h
PCH_PWRM_BASE_ADDRESS		EQU	0FE000000h	; PMC MBAR MMIO base address
PCH_PCR_BASE_ADDRESS		EQU	0FD000000h	; SBREG MMIO base address
TCO_BASE_ADDRESS		EQU	0400h		; SPT TCO base address

MEMORY_STACK_ADDR   EQU (DATA_STACK_BASE_ADDRESS + DATA_STACK_SIZE)

ENDIF    ;IFNDEF CRCOEM_INC
