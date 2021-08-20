/** @file
  EM64T Exception Handler

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2016 Intel Corporation.

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

#include <Library/BaseMemoryLib.h>
#include <Library/ReportStatusCodeLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Private/Library/CpuCommonLib.h>

#include "CpuInitDxe.h"
#include "MpCommon.h"
#include "Exception.h"

typedef
VOID
(*EFI_INSTALL_EXCEPTION) (
  IN UINT32 InterruptType,
  IN VOID   *SystemContext
  );

typedef struct {
  UINT32 ErrorMessage;
  UINT8 Interrupt;
} EFI_EXCEPTION_HANDLER;

///
/// Error code flag indicating whether or not an error code will be
/// pushed on the stack if an exception occurs.
///
/// 1 means an error code will be pushed, otherwise 0
///
/// bit 0 - exception 0
/// bit 1 - exception 1
/// etc.
///
GLOBAL_REMOVE_IF_UNREFERENCED UINT32 mErrorCodeFlag = 0x00027d00;

///
/// Local Table
///
GLOBAL_REMOVE_IF_UNREFERENCED EFI_EXCEPTION_HANDLER mExceptionTable[] = {
  {
    EFI_SW_EC_IA32_DIVIDE_ERROR,
    INTERRUPT_HANDLER_DIVIDE_ZERO
  },
  {
    EFI_SW_EC_IA32_DEBUG,
    INTERRUPT_HANDLER_DEBUG
  },
  {
    EFI_SW_EC_IA32_NMI,
    INTERRUPT_HANDLER_NMI
  },
  {
    EFI_SW_EC_IA32_BREAKPOINT,
    INTERRUPT_HANDLER_BREAKPOINT
  },
  {
    EFI_SW_EC_IA32_OVERFLOW,
    INTERRUPT_HANDLER_OVERFLOW
  },
  {
    EFI_SW_EC_IA32_BOUND,
    INTERRUPT_HANDLER_BOUND
  },
  {
    EFI_SW_EC_IA32_INVALID_OPCODE,
    INTERRUPT_HANDLER_INVALID_OPCODE
  },
  ///
  /// Interrupt 7, 9, 15 not defined in the debug support protocol. Hence no status codes for them!
  ///
  {
    EFI_SW_EC_IA32_DOUBLE_FAULT,
    INTERRUPT_HANDLER_DOUBLE_FAULT
  },
  {
    EFI_SW_EC_IA32_INVALID_TSS,
    INTERRUPT_HANDLER_INVALID_TSS
  },
  {
    EFI_SW_EC_IA32_SEG_NOT_PRESENT,
    INTERRUPT_HANDLER_SEGMENT_NOT_PRESENT
  },
  {
    EFI_SW_EC_IA32_STACK_FAULT,
    INTERRUPT_HANDLER_STACK_SEGMENT_FAULT
  },
  {
    EFI_SW_EC_IA32_GP_FAULT,
    INTERRUPT_HANDLER_GP_FAULT
  },
  {
    EFI_SW_EC_IA32_PAGE_FAULT,
    INTERRUPT_HANDLER_PAGE_FAULT
  },
  {
    EFI_SW_EC_IA32_FP_ERROR,
    INTERRUPT_HANDLER_MATH_FAULT
  },
  {
    EFI_SW_EC_IA32_ALIGNMENT_CHECK,
    INTERRUPT_HANDLER_ALIGNMENT_FAULT
  },
  {
    EFI_SW_EC_IA32_MACHINE_CHECK,
    INTERRUPT_HANDLER_MACHINE_CHECK
  },
  {
    EFI_SW_EC_IA32_SIMD,
    INTERRUPT_HANDLER_STREAMING_SIMD
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED UINTN mExceptionNumber = sizeof (mExceptionTable) / sizeof (EFI_EXCEPTION_HANDLER);

GLOBAL_REMOVE_IF_UNREFERENCED CPU_STATUS_CODE_TEMPLATE mStatusCodeData = {
  {
    sizeof (EFI_STATUS_CODE_DATA),
    sizeof (EFI_SYSTEM_CONTEXT_X64),
    { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } }
  },
  {
    {
      0,
      {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
      },
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      { 0, 0 },
      { 0, 0 },
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    }
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 mExceptionLock = 0;

/**
  Report StatusCode for Exception

  @param[in] InterruptType - Interrupt type
  @param[in] SystemContext - EFI_SYSTEM_CONTEXT

  @retval EFI_SUCCESS
**/
EFI_STATUS
ReportData (
  IN EFI_EXCEPTION_TYPE InterruptType,
  IN EFI_SYSTEM_CONTEXT SystemContext
  )
{
  UINT32 ErrorMessage;
  UINT32 Index;

  CopyMem (
    &mStatusCodeData.SystemContext.SystemContextX64,
    SystemContext.SystemContextX64,
    sizeof (EFI_SYSTEM_CONTEXT_X64)
    );

  ErrorMessage = EFI_SOFTWARE_DXE_BS_DRIVER;
  for (Index = 0; Index < mExceptionNumber; Index++) {
    if (mExceptionTable[Index].Interrupt == InterruptType) {
      ErrorMessage |= mExceptionTable[Index].ErrorMessage;
      break;
    }
  }

  ReportStatusCode (
    (EFI_ERROR_CODE | EFI_ERROR_UNRECOVERED),
    EFI_SOFTWARE_UNSPECIFIED | ErrorMessage
    );

  return EFI_SUCCESS;
}

/**
  Common exception handler

  @param[in] InterruptType - Exception type
  @param[in] SystemContext - EFI_SYSTEM_CONTEXT
**/
VOID
EFIAPI
CommonExceptionHandler (
  IN EFI_EXCEPTION_TYPE InterruptType,
  IN EFI_SYSTEM_CONTEXT SystemContext
  )
{
  AsmAcquireMPLock (&mExceptionLock);

  DEBUG (
    (DEBUG_ERROR,
     "!!!! X64 Exception Type - %016lx    CPU Apic ID - %08x!!!!\n",
     InterruptType,
     GetCpuApicId ())
    );
  DEBUG (
    (DEBUG_ERROR,
     "RIP - %016lx, CS - %016lx, RFLAGS - %016lx\n",
     SystemContext.SystemContextX64->Rip,
     SystemContext.SystemContextX64->Cs,
     SystemContext.SystemContextX64->Rflags)
    );
  if (mErrorCodeFlag & (1 << InterruptType)) {
    DEBUG (
      (DEBUG_ERROR,
       "ExceptionData - %016lx\n",
       SystemContext.SystemContextX64->ExceptionData)
      );
  }

  DEBUG (
    (DEBUG_ERROR,
     "RAX - %016lx, RCX - %016lx, RDX - %016lx\n",
     SystemContext.SystemContextX64->Rax,
     SystemContext.SystemContextX64->Rcx,
     SystemContext.SystemContextX64->Rdx)
    );
  DEBUG (
    (DEBUG_ERROR,
     "RBX - %016lx, RSP - %016lx, RBP - %016lx\n",
     SystemContext.SystemContextX64->Rbx,
     SystemContext.SystemContextX64->Rsp,
     SystemContext.SystemContextX64->Rbp)
    );
  DEBUG (
    (DEBUG_ERROR,
     "RSI - %016lx, RDI - %016lx\n",
     SystemContext.SystemContextX64->Rsi,
     SystemContext.SystemContextX64->Rdi)
    );
  DEBUG (
    (DEBUG_ERROR,
     "R8 - %016lx, R9 - %016lx, R10 - %016lx\n",
     SystemContext.SystemContextX64->R8,
     SystemContext.SystemContextX64->R9,
     SystemContext.SystemContextX64->R10)
    );
  DEBUG (
    (DEBUG_ERROR,
     "R11 - %016lx, R12 - %016lx, R13 - %016lx\n",
     SystemContext.SystemContextX64->R11,
     SystemContext.SystemContextX64->R12,
     SystemContext.SystemContextX64->R13)
    );
  DEBUG (
    (DEBUG_ERROR,
     "R14 - %016lx, R15 - %016lx\n",
     SystemContext.SystemContextX64->R14,
     SystemContext.SystemContextX64->R15)
    );
  DEBUG (
    (DEBUG_ERROR,
     "DS - %016lx, ES - %016lx, FS - %016lx\n",
     SystemContext.SystemContextX64->Ds,
     SystemContext.SystemContextX64->Es,
     SystemContext.SystemContextX64->Fs)
    );
  DEBUG (
    (DEBUG_ERROR,
     "GS - %016lx, SS - %016lx\n",
     SystemContext.SystemContextX64->Gs,
     SystemContext.SystemContextX64->Ss)
    );
  DEBUG (
    (DEBUG_ERROR,
     "GDTR - %016lx %016lx, LDTR - %016lx\n",
     SystemContext.SystemContextX64->Gdtr[0],
     SystemContext.SystemContextX64->Gdtr[1],
     SystemContext.SystemContextX64->Ldtr)
    );
  DEBUG (
    (DEBUG_ERROR,
     "IDTR - %016lx %016lx, TR - %016lx\n",
     SystemContext.SystemContextX64->Idtr[0],
     SystemContext.SystemContextX64->Idtr[1],
     SystemContext.SystemContextX64->Tr)
    );
  DEBUG (
    (DEBUG_ERROR,
     "CR0 - %016lx, CR2 - %016lx, CR3 - %016lx\n",
     SystemContext.SystemContextX64->Cr0,
     SystemContext.SystemContextX64->Cr2,
     SystemContext.SystemContextX64->Cr3)
    );
  DEBUG (
    (DEBUG_ERROR,
     "CR4 - %016lx, CR8 - %016lx\n",
     SystemContext.SystemContextX64->Cr4,
     SystemContext.SystemContextX64->Cr8)
    );
  DEBUG (
    (DEBUG_ERROR,
     "DR0 - %016lx, DR1 - %016lx, DR2 - %016lx\n",
     SystemContext.SystemContextX64->Dr0,
     SystemContext.SystemContextX64->Dr1,
     SystemContext.SystemContextX64->Dr2)
    );
  DEBUG (
    (DEBUG_ERROR,
     "DR3 - %016lx, DR6 - %016lx, DR7 - %016lx\n",
     SystemContext.SystemContextX64->Dr3,
     SystemContext.SystemContextX64->Dr6,
     SystemContext.SystemContextX64->Dr7)
    );

  ///
  /// Report Status Code
  ///
  ReportData (InterruptType, SystemContext);
  AsmReleaseMPLock (&mExceptionLock);

  ///
  /// Use this macro to hang so that the compiler does not optimize out
  /// the following RET instructions. This allows us to return if we
  /// have a debugger attached.
  ///
  CpuDeadLoop ();

  return;
}

/**
  Install the IA-32 EM64T Exception Handler.
  The current operation (which likely will change) will uninstall all the
  pertinent exception handlers (0-7, 10-14, 16-19) except for Int8 which the timer
  is currently sitting on (or soon will be).

  It then installs all the appropriate handlers for each exception.

  The handler then calls gRT->ReportStatusCode with a specific progress code.  The
  progress codes for now start at 0x200 for IA-32 processors. See Status Code
  Specification for details. The Status code Specification uses the enumeration from
  the EFI 1.1 Debug Support Protocol.

  @param[in] CpuProtocol - Instance of CPU Arch Protocol

  @retval EFI_SUCCESS - This function always return success after registering handlers.
**/
EFI_STATUS
InitializeException (
  IN EFI_CPU_ARCH_PROTOCOL *CpuProtocol
  )
{
  EFI_STATUS Status;
  UINTN      Index;

  mStatusCodeData.Header.Type = gCpuStatusCodeDataTypeExceptionHandlerGuid;

  CpuProtocol->DisableInterrupt (CpuProtocol);

  for (Index = 0; Index < mExceptionNumber; Index++) {

    Status = CpuProtocol->RegisterInterruptHandler (
                            CpuProtocol,
                            mExceptionTable[Index].Interrupt,
                            NULL
                            );

    ///
    /// Add in our handler
    ///
    Status = CpuProtocol->RegisterInterruptHandler (
                            CpuProtocol,
                            mExceptionTable[Index].Interrupt,
                            CommonExceptionHandler
                            );
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}
