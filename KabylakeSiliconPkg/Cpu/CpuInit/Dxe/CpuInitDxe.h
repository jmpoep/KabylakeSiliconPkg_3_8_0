/** @file
  Private data structures and function prototypes.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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

@par Specification
**/

#ifndef _CPU_INIT_DXE_H
#define _CPU_INIT_DXE_H

#include <Protocol/Metronome.h>
#include <Protocol/Cpu.h>
#include <Library/MemoryAllocationLib.h>
#include <Guid/EventGroup.h>
#include "MemoryAttribute.h"
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <CpuAccess.h>
#include <Protocol/CpuInfo.h>
#include <Library/CpuPlatformLib.h>
#include <Library/HobLib.h>
#include <Library/ConfigBlockLib.h>
#include <Private/CpuInitDataHob.h>
#include <Private/SiConfigHob.h>

#define INTERRUPT_VECTOR_NUMBER     256
#define INTERRUPT_GATE_ATTRIBUTE    0x8e00

extern UINT8 mSmmbaseSwSmiNumber;

extern CPU_INIT_DATA_HOB  *mCpuInitDataHob;
extern CPU_CONFIG_DATA    *mCpuConfigData;

/**
  Adjust length to a paragraph boundry

  @param[in] MemoryLength  -  Input memory length.

  @retval Returned Maximum length.
**/
UINT64
Power2MaxMemory (
  IN UINT64 MemoryLength
  );

/**
  Disable cache and its mtrr

  @param[in] OldMtrr - To return the Old MTRR value
**/
VOID
EfiDisableCacheMtrr (
  IN UINT64 *OldMtrr
  );

/**
  Recover cache MTRR

  @param[in] EnableMtrr - Whether to enable the MTRR
  @param[in] OldMtrr    - The saved old MTRR value to restore when not to
                          enable the MTRR
**/
VOID
EfiRecoverCacheMtrr (
  IN BOOLEAN EnableMtrr,
  IN UINT64  OldMtrr
  );

typedef struct _ALIGNED_DWORD {
  UINT32 High;
  UINT32 Low;
} ALIGNED_DWORD;

typedef union _ALIGNED {
  UINT64        AlignedQword;
  ALIGNED_DWORD AlignedDword;
} ALIGNED;

/**
  Initialize the state information for the CPU Architectural Protocol

  @param[in] ImageHandle - Image handle of the loaded driver
  @param[in] SystemTable - Pointer to the System Table

  @retval EFI_SUCCESS           - thread can be successfully created
  @retval EFI_OUT_OF_RESOURCES  - cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      - cannot create the thread
**/
EFI_STATUS
EFIAPI
InitializeCpu (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  );

/**
  Prepare memory for essential system tables.

  @retval EFI_SUCCESS  - Memory successfully prepared.
**/
EFI_STATUS
PrepareMemory (
  VOID
  );

/**
  Flush CPU data cache. If the instruction cache is fully coherent
  with all DMA operations then function can just return EFI_SUCCESS.

  @param[in] This             - Protocol instance structure
  @param[in] Start            - Physical address to start flushing from.
  @param[in] Length           - Number of bytes to flush. Round up to chipset granularity.
  @param[in] FlushType        - Specifies the type of flush operation to perform.

  @retval EFI_SUCCESS         - If cache was flushed
  @exception EFI_UNSUPPORTED  - If flush type is not supported.
  @retval EFI_DEVICE_ERROR    - If requested range could not be flushed.
**/
EFI_STATUS
EFIAPI
FlushCpuDataCache (
  IN EFI_CPU_ARCH_PROTOCOL *This,
  IN EFI_PHYSICAL_ADDRESS  Start,
  IN UINT64                Length,
  IN EFI_CPU_FLUSH_TYPE    FlushType
  );

/**
  Enables CPU interrupts.

  @param[in] This            - Protocol instance structure

  @retval EFI_SUCCESS        - If interrupts were enabled in the CPU
  @retval EFI_DEVICE_ERROR   - If interrupts could not be enabled on the CPU.
**/
EFI_STATUS
EFIAPI
EnableInterrupt (
  IN EFI_CPU_ARCH_PROTOCOL *This
  );

/**
  Disables CPU interrupts.

  @param[in] This           - Protocol instance structure

  @retval EFI_SUCCESS       - If interrupts were disabled in the CPU.
  @retval EFI_DEVICE_ERROR  - If interrupts could not be disabled on the CPU.
**/
EFI_STATUS
EFIAPI
DisableInterrupt (
  IN EFI_CPU_ARCH_PROTOCOL *This
  );

/**
  Return the state of interrupts.

  @param[in] This                - Protocol instance structure
  @param[in] State               - Pointer to the CPU's current interrupt state

  @retval EFI_SUCCESS            - If interrupts were disabled in the CPU.
  @retval EFI_INVALID_PARAMETER  - State is NULL.
**/
EFI_STATUS
EFIAPI
CpuGetInterruptState (
  IN EFI_CPU_ARCH_PROTOCOL *This,
  OUT BOOLEAN              *State
  );

/**
  Generates an INIT to the CPU

  @param[in] This             - Protocol instance structure
  @param[in] InitType         - Type of CPU INIT to perform

  @retval EFI_SUCCESS         - If CPU INIT occurred. This value should never be seen.
  @retval EFI_DEVICE_ERROR    - If CPU INIT failed.
  @exception EFI_UNSUPPORTED  - Requested type of CPU INIT not supported.
**/
EFI_STATUS
EFIAPI
Init (
  IN EFI_CPU_ARCH_PROTOCOL *This,
  IN EFI_CPU_INIT_TYPE     InitType
  );

/**
  Registers a function to be called from the CPU interrupt handler.

  @param[in] This                - Protocol instance structure
  @param[in] InterruptType       - Defines which interrupt to hook.
                                   IA-32 valid range is 0x00 through 0xFF
  @param[in] InterruptHandler    - A pointer to a function of type EFI_CPU_INTERRUPT_HANDLER
                                   that is called when a processor interrupt occurs.
                                   A null pointer is an error condition.

  @retval EFI_SUCCESS            - If handler installed or uninstalled.
  @retval EFI_ALREADY_STARTED    - InterruptHandler is not NULL, and a handler for
                                   InterruptType was previously installed
  @retval EFI_INVALID_PARAMETER  - InterruptHandler is NULL, and a handler for
                                   InterruptType was not previously installed.
  @exception EFI_UNSUPPORTED     - The interrupt specified by InterruptType is not supported.
**/
EFI_STATUS
EFIAPI
RegisterInterruptHandler (
  IN EFI_CPU_ARCH_PROTOCOL     *This,
  IN EFI_EXCEPTION_TYPE        InterruptType,
  IN EFI_CPU_INTERRUPT_HANDLER InterruptHandler
  );

/**
  Returns a timer value from one of the CPU's internal timers. There is no
  inherent time interval between ticks but is a function of the CPU frequency.

  @param[in] This                - Protocol instance structure.
  @param[in] TimerIndex          - Specifies which CPU timer is requested.
  @param[in] TimerValue          - Pointer to the returned timer value.
  @param[in] TimerPeriod         - A pointer to the amount of time that passes in femtoseconds (10-15) for each
                                   increment of TimerValue. If TimerValue does not increment at a predictable
                                   rate, then 0 is returned. The amount of time that has passed between two calls to
                                   GetTimerValue() can be calculated with the formula
                                   (TimerValue2 - TimerValue1) * TimerPeriod. This parameter is optional and may be NULL.

  @retval EFI_SUCCESS            - If the CPU timer count was returned.
  @exception EFI_UNSUPPORTED     - If the CPU does not have any readable timers.
  @retval EFI_DEVICE_ERROR       - If an error occurred while reading the timer.
  @retval EFI_INVALID_PARAMETER  - TimerIndex is not valid or TimerValue is NULL.
**/
EFI_STATUS
EFIAPI
GetTimerValue (
  IN EFI_CPU_ARCH_PROTOCOL *This,
  IN UINT32                TimerIndex,
  OUT UINT64               *TimerValue,
  OUT UINT64 *TimerPeriod  OPTIONAL
  );

/**
  Set memory cacheability attributes for given range of memeory

  @param[in] This                - Protocol instance structure
  @param[in] BaseAddress         - Specifies the start address of the memory range
  @param[in] Length              - Specifies the length of the memory range
  @param[in] Attributes          - The memory cacheability for the memory range

  @retval EFI_SUCCESS            - If the cacheability of that memory range is set successfully
  @exception EFI_UNSUPPORTED     - If the desired operation cannot be done
  @retval EFI_INVALID_PARAMETER  - The input parameter is not correct, such as Length = 0
**/
EFI_STATUS
EFIAPI
SetMemoryAttributes (
  IN EFI_CPU_ARCH_PROTOCOL *This,
  IN EFI_PHYSICAL_ADDRESS  BaseAddress,
  IN UINT64                Length,
  IN UINT64                Attributes
  );

/**
  Init Global Descriptor table
**/
VOID
InitializeSelectors (
  VOID
  );

/**
  Initializes MP support in the system.

  @retval EFI_SUCCESS           - Multiple processors are initialized successfully.
  @retval EFI_NOT_FOUND         - The ACPI variable is not found in S3 boot path.
  @retval EFI_OUT_OF_RESOURCES  - No enough resoruces (such as out of memory).
**/
EFI_STATUS
InitializeMpSupport (
  VOID
  );

/**
  Save the MTRR registers to global variables
**/
VOID
ReadMtrrRegisters (
  VOID
  );

/**
  Synch up the MTRR values for all processors
**/
VOID
EFIAPI
MpMtrrSynchUp (
  IN VOID *Buffer
  );

/**
  Copy Global MTRR data to S3
**/
VOID
SaveBspMtrrForS3 (
  VOID
  );

/**
  Returns the actual CPU core frequency in MHz.

  @param[in] Metronome           - Metronome protocol
  @param[in] Frequency           - Pointer to the CPU core frequency

  @retval EFI_SUCCESS            - If the frequency is returned successfully
  @retval EFI_INVALID_PARAMETER  - If the input parameter is wrong
**/
EFI_STATUS
GetActualFrequency (
  IN EFI_METRONOME_ARCH_PROTOCOL *Metronome,
  OUT UINT64                     *Frequency
  );

/**
  Initialize Cpu float point unit
**/
VOID
CpuInitFloatPointUnit (
  VOID
  );

#ifndef MINTREE_FLAG
/**
 * Code to update SGX Global NVS variable in EPC.ASL
 *
 */
VOID
UpdateSgxNvs (
  VOID
  );
#endif

/**
  Initialize CPU info.

  @retval EFI_SUCCESS          - Successfully prepared.
  @retval EFI_OUT_OF_RESOURCES - Not enough memory to complete the function.
**/
EFI_STATUS
InitCpuInfo (
  VOID
  );

/**
  Set Interrupt Descriptor Table Handler Address.

  @param Index        The Index of the interrupt descriptor table handle.

**/
VOID
SetInterruptDescriptorTableHandlerAddress (
  IN UINTN  Index
  );

/**
  Restore original Interrupt Descriptor Table Handler Address.

  @param Index        The Index of the interrupt descriptor table handle.
**/
VOID
RestoreInterruptDescriptorTableHandlerAddress (
  IN UINTN  Index
  );

/**
  Initialize Cpu Global Nvs Area Protocol

  @param[in] ImageHandle - Image handle of the loaded driver

  @retval EFI_SUCCESS           - thread can be successfully created
**/
EFI_STATUS
EFIAPI
CpuAcpiInit (
  IN EFI_HANDLE       ImageHandle
  );

#endif
