/** @file
  Some definitions for MP and HT driver.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _MP_COMMON_
#define _MP_COMMON_

#include <Library/BaseLib.h>
#include <Library/TimerLib.h>
#include "CpuInitDxe.h"
#include "Exception.h"
#include "ProcessorDef.h"
#include "PchAccess.h"
#include <Private/CpuInitDataHob.h>
#include <Private/CpuPrivateData.h>

#include <Protocol/MpService.h>

#define VacantFlag             0x00
#define NotVacantFlag          0xff
#define MICROSECOND            10
#define STACK_SIZE_PER_PROC    0x8000
#define IO_APIC_INDEX_REGISTER 0xFEC00000
#define IO_APIC_DATA_REGISTER  0xFEC00010

///
/// Data structure used in MP/HT driver
///
#define MP_CPU_EXCHANGE_INFO_OFFSET     (0x1000 - 0x400)
#define MP_CPU_LEGACY_RESET_INFO_OFFSET (0x100 - 0x20)

#define SMM_FROM_CPU_DRIVER_SAVE_INFO   0x81

#pragma pack(1)
#define SIZE_OF_MCE_HANDLER 16

typedef struct {
  UINT16 LimitLow;
  UINT16 BaseLow;
  UINT8  BaseMiddle;
  UINT16 Attributes;
  UINT8  BaseHigh;
} SEGMENT_DESCRIPTOR;

#pragma pack()

#define BREAK_TO_RUN_AP_SIGNAL  0x6E755200
#define MONITOR_FILTER_SIZE     0x40

typedef enum {
  WakeUpApCounterInit   = 0,
  WakeUpApPerHltLoop    = 1,
  WakeUpApPerMwaitLoop  = 2,
  WakeUpApPerRunLoop    = 3,
  WakeUpApPerMwaitLoop32= 4,
  WakeUpApPerRunLoop32  = 5
} WAKEUP_AP_MANNER;

typedef struct {
  UINTN BreakToRunApSignal;
  UINTN HltLoopBreakCounter;
  UINTN MwaitLoopBreakCounter;
  UINTN RunLoopBreakCounter;
  UINTN MwaitLoopBreakCounter32;
  UINTN RunLoopBreakCounter32;
  UINTN WakeUpApVectorChangeFlag;
  UINTN MwaitTargetCstate;
} MONITOR_MWAIT_DATA;

typedef struct {
  UINT32 Number;
  UINT32 Bist;
} BIST_INFO;

typedef struct {
  UINTN             Lock;
  VOID              *StackStart;
  UINTN             StackSize;
  VOID              *ApFunction;
  IA32_DESCRIPTOR   GdtrProfile;
  IA32_DESCRIPTOR   IdtrProfile;
  UINT32            BufferStart;
  UINT32            Cr3;
  UINT32            InitFlag;
  WAKEUP_AP_MANNER  WakeUpApManner;
  BIST_INFO         BistBuffer[MAX_PROCESSOR_THREADS];
} MP_CPU_EXCHANGE_INFO;

extern ACPI_CPU_DATA *mAcpiCpuData;

///
/// Functions shared in MP/HT drivers
///
/**
  Send interrupt to CPU

  @param[in] BroadcastMode - interrupt broadcast mode
  @param[in] ApicID        - APIC ID for sending interrupt
  @param[in] VectorNumber  - Vector number
  @param[in] DeliveryMode  - Interrupt delivery mode
  @param[in] TriggerMode   - Interrupt trigger mode
  @param[in] Assert        - Interrupt pin polarity

  @retval EFI_INVALID_PARAMETER - input parameter not correct
  @retval EFI_NOT_READY         - there was a pending interrupt
  @retval EFI_SUCCESS           - interrupt sent successfully
**/
EFI_STATUS
SendInterrupt (
  IN UINT32  BroadcastMode,
  IN UINT32  ApicID,
  IN UINT32  VectorNumber,
  IN UINT32  DeliveryMode,
  IN UINT32  TriggerMode,
  IN BOOLEAN Assert
  );

/**
  Programs XAPIC registers.

  @param[in] Bsp             - Is this BSP
**/
VOID
ProgramCpuXApic (
  IN BOOLEAN Bsp
  );

/**
  Allocate a temporary memory under 1MB for MP Init to perform INIT-SIPI.
  This buffer also provides memory for stack/data for MP running.

  @param[in] WakeUpBuffer  - Return buffer location

  @retval EFI_SUCCESS if ok to get a memory under 1MB for MP running.
**/
EFI_STATUS
AllocateWakeUpBuffer (
  OUT EFI_PHYSICAL_ADDRESS *WakeUpBuffer
  );

///
/// Assembly functions implemented in MP/HT drivers
///
/**
  Lock APs

  @param[in] Lock  - Lock state
**/
VOID
AsmAcquireMPLock (
  IN volatile UINT8 *Lock
  );

/**
  Release APs

  @param[in] Lock  - Lock state
**/
VOID
AsmReleaseMPLock (
  IN volatile UINT8 *Lock
  );

/**
  Prepare GDTR and IDTR for AP

  @param[in] GDTR  - The GDTR profile
  @param[in] IDTR  - The IDTR profile

  @retval EFI_STATUS  - status returned by each sub-routine
  @retval EFI_SUCCESS - GDTR and IDTR has been prepared for AP
**/
EFI_STATUS
PrepareGdtIdtForAP (
  OUT IA32_DESCRIPTOR *GDTR,
  OUT IA32_DESCRIPTOR *IDTR
  );

/**
  Allocate Reserved Memory below 4G memory address

  @param[in] Size      - Memory Size
  @param[in] Alignment - Alignment size
  @param[in] Pointer   - return memory location

  @retval EFI_SUCCESS  - Allocate a reserved memory successfully
**/
EFI_STATUS
AllocateAlignedReservedMemoryBelow4G (
  IN UINTN Size,
  IN UINTN Alignment,
  OUT VOID **Pointer
  );

/**
  This function is invoked when LegacyBios protocol is installed, we must
  allocate reserved memory under 1M for AP.

  @param[in] Event   - The triggered event.
  @param[in] Context - Context for this event.
**/
VOID
EFIAPI
ReAllocateEbdaMemoryForAP (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

/**
  This function is invoked when LegacyBios protocol is installed, we must
  allocate reserved memory under 1M for AP.

  @param[in] Event   - The triggered event.
  @param[in] Context - Context for this event.
**/
VOID
EFIAPI
ReAllocateMemoryForAP (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

/**
  This function is invoked by EFI_EVENT_SIGNAL_LEGACY_BOOT.
  Before booting to legacy OS, reset it with memory allocated
  by ReAllocateMemoryForAp() and set local APIC correctly.

  @param[in] Event   - The triggered event.
  @param[in] Context - Context for this event.
**/
VOID
EFIAPI
ResetAps (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

/**
  Prepare Wakeup Buffer and stack for APs.

  @param[in] WakeUpBuffer           - Pointer to the address of wakeup buffer for output.
  @param[in] StackAddressStart      - Pointer to the stack address of APs for output.
  @param[in] TotalCpusForThisSystem - Total number of logical processors in this system.

  @retval EFI_SUCCESS              - Memory successfully prepared for APs.
  @retval Other                    - Error occurred while allocating memory.
**/
EFI_STATUS
PrepareMemoryForAPs (
  OUT EFI_PHYSICAL_ADDRESS *WakeUpBuffer,
  OUT VOID                 **StackAddressStart,
  IN UINTN                 TotalCpusForThisSystem
  );

/**
  Prepare exchange information for APs.

  @param[in] ExchangeInfo      - Pointer to the exchange info buffer for output.
  @param[in] StackAddressStart - Start address of APs' stacks.
  @param[in] ApFunction        - Address of function assigned to AP.
  @param[in] WakeUpBuffer      - Pointer to the address of wakeup buffer.

  @retval EFI_SUCCESS       - Exchange Info successfully prepared for APs.
  @retval Other             - Error occurred while allocating memory.
**/
EFI_STATUS
PrepareExchangeInfo (
  OUT MP_CPU_EXCHANGE_INFO *ExchangeInfo,
  IN VOID                  *StackAddressStart,
  IN VOID                  *ApFunction,
  IN EFI_PHYSICAL_ADDRESS  WakeUpBuffer
  );

/**
  Check whether any AP is running for assigned task.

  @retval TRUE  - Some APs are running.
  @retval FALSE - No AP is running.
**/
BOOLEAN
ApRunning (
  VOID
  );

/**
  Wrapper function for all procedures assigned to AP via MP service protocol.
  It controls states of AP and invokes assigned precedure.
**/
VOID
ApProcWrapper (
  VOID
  );

/**
  Allocate EfiReservedMemoryType below 4G memory address.

  @param[in] Size   - Size of memory to allocate.
  @param[in] Buffer - Allocated address for output.

  @retval EFI_SUCCESS - Memory successfully allocated.
  @retval Other       - Other errors occur.
**/
EFI_STATUS
AllocateReservedMemoryBelow4G (
  IN UINTN Size,
  OUT VOID **Buffer
  );

/**
  Dynamically write the far jump destination in APs' wakeup buffer,
  in order to refresh APs' CS registers for mode switching.
**/
VOID
RedirectFarJump (
  VOID
  );

#endif
