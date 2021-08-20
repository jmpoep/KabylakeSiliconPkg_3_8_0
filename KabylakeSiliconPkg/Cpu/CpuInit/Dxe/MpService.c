/** @file
  Code which support multi-processor

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

@par Specification Reference:
**/

#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/HobLib.h>
#include <Library/SynchronizationLib.h>
#include <Library/ReportStatusCodeLib.h>
#include <Protocol/LegacyBios.h>
#include <Library/CpuPlatformLib.h>
#include <Private/Library/CpuCommonLib.h>

#include "MpService.h"
#include "CpuInitDxe.h"
#include <Library/TimerLib.h>

extern EFI_GUID                         gHtBistHobGuid;

STATIC EFI_HANDLE        mHandle         = NULL;
STATIC UINT32            mFinishedCount  = 0;

GLOBAL_REMOVE_IF_UNREFERENCED EFI_MP_SERVICES_PROTOCOL mMpService = {
  GetNumberOfProcessors,
  GetProcessorInfo,
  StartupAllAPs,
  StartupThisAP,
  SwitchBSP,
  EnableDisableAP,
  WhoAmI
};

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PHYSICAL_ADDRESS  mOriginalBuffer;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_PHYSICAL_ADDRESS  mBackupBuffer;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN               mStopCheckApsStatus = FALSE;

/**
  Initialize MP services by MP Service Protocol
**/
VOID
EFIAPI
InitializeMpServices (
  VOID
  )
{
  EFI_STATUS               Status;
  EFI_EVENT                LegacyBootEvent;
  EFI_EVENT                ExitBootServicesEvent;
  VOID                     *Registration;
  EFI_EVENT                EndOfDxeEvent;
  EFI_PEI_HOB_POINTERS     HobPtr;
  SI_CONFIG_HOB            *SiConfigHob;

  LegacyBootEvent       = NULL;
  ExitBootServicesEvent = NULL;

  ///
  /// Save Mtrr Registers in global data areas
  ///
  ReadMtrrRegisters ();

  ///
  /// Initialize and collect MP related data
  ///
  Status = InitializeMpSystemData ();
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  ///
  /// Since PI1.2.1, we need use EndOfDxe instead of ExitPmAuth
  ///
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  ReAllocateMemoryForAP,
                  NULL,
                  &gEfiEndOfDxeEventGroupGuid,
                  &EndOfDxeEvent
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Get Silicon Config data HOB
  //
  HobPtr.Guid = GetFirstGuidHob (&gSiConfigHobGuid);
  SiConfigHob = (SI_CONFIG_HOB *)GET_GUID_HOB_DATA (HobPtr.Guid);

  if (SiConfigHob->CsmFlag == 1) {
    ///
    /// Register protocol notifaction function to allocate memory in EBDA as early as possible
    ///
    EfiCreateProtocolNotifyEvent (
      &gEfiLegacyBiosProtocolGuid,
      TPL_NOTIFY,
      ReAllocateEbdaMemoryForAP,
      NULL,
      &Registration
      );
  }

  ///
  /// Create legacy boot and EFI boot events to reset APs before OS handoff
  ///
  Status = EfiCreateEventLegacyBootEx (
             TPL_CALLBACK,
             ResetAps,
             mMPSystemData,
             &LegacyBootEvent
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  Status = gBS->CreateEvent (
                  EVT_SIGNAL_EXIT_BOOT_SERVICES,
                  TPL_CALLBACK,
                  ResetAps,
                  mMPSystemData,
                  &ExitBootServicesEvent
                  );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  ///
  /// Create timer event to check AP state for non-blocking execution.
  ///
  Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  CheckApsStatus,
                  NULL,
                  &mMPSystemData->CheckAPsEvent
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Now install the Frameowrk & PI MP services protocol.
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &mHandle,
                  &gEfiMpServiceProtocolGuid,
                  &mMpService,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->SetTimer (
                  mMPSystemData->CheckAPsEvent,
                  TimerPeriodic,
                  10000 * MICROSECOND
                  );
  ASSERT_EFI_ERROR (Status);

  if (EFI_ERROR (Status)) {

Done:
    if (LegacyBootEvent != NULL) {
      gBS->CloseEvent (LegacyBootEvent);
    }

    if (ExitBootServicesEvent != NULL) {
      gBS->CloseEvent (ExitBootServicesEvent);
    }

    FreePool (mMPSystemData);
  }
}

/**
  Implementation of GetNumberOfProcessors() service of MP Services Protocol.

  This service retrieves the number of logical processor in the platform
  and the number of those logical processors that are enabled on this boot.
  This service may only be called from the BSP.

  @param[in] This                      - A pointer to the EFI_MP_SERVICES_PROTOCOL instance.
  @param[in] NumberOfProcessors        - Pointer to the total number of logical processors in the system,
                                         including the BSP and disabled APs.
  @param[in] NumberOfEnabledProcessors - Pointer to the number of enabled logical processors that exist
                                         in system, including the BSP.

  @retval EFI_SUCCESS            - Number of logical processors and enabled logical processors retrieved..
  @retval EFI_DEVICE_ERROR       - Caller processor is AP.
  @retval EFI_INVALID_PARAMETER  - NumberOfProcessors is NULL.
  @retval EFI_INVALID_PARAMETER  - NumberOfEnabledProcessors is NULL.
**/
EFI_STATUS
EFIAPI
GetNumberOfProcessors (
  IN EFI_MP_SERVICES_PROTOCOL *This,
  OUT UINTN                   *NumberOfProcessors,
  OUT UINTN                   *NumberOfEnabledProcessors
  )
{
  UINTN          CallerNumber;
  UINTN          Index;
  CPU_DATA_BLOCK *CpuData;

  ///
  /// Check whether caller processor is BSP
  ///
  WhoAmI (This, &CallerNumber);
  if (CallerNumber != mMPSystemData->BSP) {
    return EFI_DEVICE_ERROR;
  }
  ///
  /// Check parameter NumberOfProcessors and NumberOfEnabledProcessors
  ///
  if (NumberOfProcessors == NULL || NumberOfEnabledProcessors == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ///
  /// Count the number of enabled processors
  ///
  *NumberOfProcessors        = mMPSystemData->NumberOfCpus;
  *NumberOfEnabledProcessors = 0;
  for (Index = 0; Index < mMPSystemData->NumberOfCpus; Index++) {
    CpuData = &mMPSystemData->CpuData[Index];
    if (mMPSystemData->EnableSecondaryCpu) {
      if (CpuData->State != CPU_STATE_DISABLED) {
        (*NumberOfEnabledProcessors) ++;
      }
    } else if (CpuData->State != CPU_STATE_DISABLED && !mMPSystemData->CpuData[Index].SecondaryCpu) {
      (*NumberOfEnabledProcessors) ++;
    }
  }

  return EFI_SUCCESS;
}

/**
  Implementation of GetProcessorInfo() service of MP Services Protocol.

  Gets detailed MP-related information on the requested processor at the
  instant this call is made. This service may only be called from the BSP.

  @param[in] This                - A pointer to the EFI_MP_SERVICES_PROTOCOL instance.
  @param[in] ProcessorNumber     - The handle number of processor.
  @param[in] ProcessorInfoBuffer - A pointer to the buffer where information for the requested processor is deposited.

  @retval EFI_SUCCESS           - Processor information successfully returned.
  @retval EFI_DEVICE_ERROR      - Caller processor is AP.
  @retval EFI_INVALID_PARAMETER - ProcessorInfoBuffer is NULL
  @retval EFI_NOT_FOUND         - Processor with the handle specified by ProcessorNumber does not exist.
**/
EFI_STATUS
EFIAPI
GetProcessorInfo (
  IN EFI_MP_SERVICES_PROTOCOL    *This,
  IN UINTN                       ProcessorNumber,
  OUT EFI_PROCESSOR_INFORMATION  *ProcessorInfoBuffer
  )
{
  CPU_DATA_BLOCK      *CpuData;
  UINTN               CallerNumber;

  ///
  /// Check whether caller processor is BSP
  ///
  WhoAmI (This, &CallerNumber);
  if (CallerNumber != mMPSystemData->BSP) {
    return EFI_DEVICE_ERROR;
  }
  ///
  /// Check parameter ProcessorInfoBuffer
  ///
  if (ProcessorInfoBuffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  ///
  /// Check whether processor with the handle specified by ProcessorNumber exists
  ///
  if (ProcessorNumber >= mMPSystemData->NumberOfCpus) {
    return EFI_NOT_FOUND;
  }

  CpuData = &mMPSystemData->CpuData[ProcessorNumber];

  ///
  /// Get Local APIC ID of specified processor
  ///
  ProcessorInfoBuffer->ProcessorId = (UINT64) CpuData->ApicID;

  ///
  /// Get physical location of specified processor
  ///
  ProcessorInfoBuffer->Location.Package = (UINT32) CpuData->PhysicalLocation.Package;
  ProcessorInfoBuffer->Location.Core    = (UINT32) CpuData->PhysicalLocation.Core;
  ProcessorInfoBuffer->Location.Thread  = (UINT32) CpuData->PhysicalLocation.Thread;

  ///
  /// Get Status Flag of specified processor
  ///
  ProcessorInfoBuffer->StatusFlag = 0;

  ProcessorInfoBuffer->StatusFlag |= PROCESSOR_ENABLED_BIT;
  if (CpuData->State == CPU_STATE_DISABLED) {
    ProcessorInfoBuffer->StatusFlag &= ~PROCESSOR_ENABLED_BIT;
  } else if (!mMPSystemData->EnableSecondaryCpu) {
    if (CpuData->SecondaryCpu) {
      ProcessorInfoBuffer->StatusFlag &= ~PROCESSOR_ENABLED_BIT;
    }
  }

  if (ProcessorNumber == mMPSystemData->BSP) {
    ProcessorInfoBuffer->StatusFlag |= PROCESSOR_AS_BSP_BIT;
  }

  if (CpuData->Health == 0) {
    ProcessorInfoBuffer->StatusFlag |= PROCESSOR_HEALTH_STATUS_BIT;
  }

  return EFI_SUCCESS;
}

/**
  MP Service to get specified application processor (AP)
  to execute a caller-provided code stream.

  @param[in] This                  - Pointer to MP Service Protocol
  @param[in] Procedure             - The procedure to be assigned to AP.
  @param[in] ProcessorNumber       - Number of the specified processor.
  @param[in] WaitEvent             - If timeout, the event to be triggered after this AP finishes.
  @param[in] TimeoutInMicroSeconds - The timeout value in microsecond. Zero means infinity.
  @param[in] ProcArguments         - Argument for Procedure.
  @param[in] Finished              - Indicates whether AP has finished assigned function.
                                     In blocking mode, it is ignored.

  @retval EFI_SUCCESS           In blocking mode, specified AP has finished before the timeout expires.
  @retval EFI_SUCCESS           In non-blocking mode, function has been dispatched to specified AP.
  @retval EFI_DEVICE_ERROR      Caller processor is AP.
  @retval EFI_TIMEOUT           In blocking mode, the timeout expires before specified AP has finished.
  @retval EFI_NOT_READY         Specified AP is busy.
  @retval EFI_NOT_FOUND         Processor with the handle specified by ProcessorNumber does not exist.
  @retval EFI_INVALID_PARAMETER ProcessorNumber specifies the BSP or disabled AP.
  @retval EFI_INVALID_PARAMETER Procedure is NULL.
**/
EFI_STATUS
EFIAPI
StartupThisAP (
  IN EFI_MP_SERVICES_PROTOCOL *This,
  IN EFI_AP_PROCEDURE         Procedure,
  IN UINTN                    ProcessorNumber,
  IN EFI_EVENT                WaitEvent OPTIONAL,
  IN UINTN                    TimeoutInMicroSeconds,
  IN VOID                     *ProcArguments OPTIONAL,
  OUT BOOLEAN                 *Finished OPTIONAL
  )
{
  EFI_STATUS     Status;
  CPU_DATA_BLOCK *CpuData;
  UINTN          CallerNumber;

  if ((Finished != NULL) && (WaitEvent != NULL)) {
    *Finished = FALSE;
  }

  ///
  /// Check whether caller processor is BSP
  ///
  WhoAmI (This, &CallerNumber);
  if (CallerNumber != mMPSystemData->BSP) {
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Check whether processor with the handle specified by ProcessorNumber exists
  ///
  if (ProcessorNumber >= mMPSystemData->NumberOfCpus) {
    return EFI_NOT_FOUND;
  }

  ///
  /// Check whether specified processor is BSP
  ///
  if (ProcessorNumber == mMPSystemData->BSP) {
    return EFI_INVALID_PARAMETER;
  }

  ///
  /// Check parameter Procedure
  ///
  if (Procedure == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  CpuData = &mMPSystemData->CpuData[ProcessorNumber];

  ///
  /// Temporarily suppress CheckAPsStatus()
  ///
  mStopCheckApsStatus = TRUE;

  ///
  /// Update AP state
  ///
  CheckAndUpdateApsStatus ();

  ///
  /// Check whether specified AP is disabled
  ///
  if (CpuData->State == CPU_STATE_DISABLED) {
    mStopCheckApsStatus = FALSE;
    return EFI_INVALID_PARAMETER;
  }

  ///
  /// Check whether specified AP is busy
  ///
  if (CpuData->State != CPU_STATE_IDLE) {
    mStopCheckApsStatus = FALSE;
    return EFI_NOT_READY;
  }

  ///
  /// Wakeup specified AP for Procedure.
  ///
  AsmAcquireMPLock (&CpuData->StateLock);
  CpuData->State = CPU_STATE_READY;
  AsmReleaseMPLock (&CpuData->StateLock);

  WakeUpAp (
    ProcessorNumber,
    Procedure,
    ProcArguments
    );

  ///
  /// If WaitEvent is not NULL, execute in non-blocking mode.
  /// BSP saves data for CheckAPsStatus(), and returns EFI_SUCCESS.
  /// CheckAPsStatus() will check completion and timeout periodically.
  ///
  CpuData->WaitEvent      = WaitEvent;
  CpuData->Finished       = Finished;
  CpuData->ExpectedTime   = CalculateTimeout (TimeoutInMicroSeconds, &CpuData->CurrentTime);
  CpuData->TotalTime      = 0;

  if (WaitEvent != NULL) {
    //
    // Allow CheckAPsStatus()
    //
    mStopCheckApsStatus = FALSE;
    return EFI_SUCCESS;
  }

  //
  // If WaitEvent is NULL, execute in blocking mode.
  // BSP checks AP's state until it finishes or TimeoutInMicrosecsond expires.
  //
  do {
    Status = CheckThisAp (ProcessorNumber);
  } while (Status == EFI_NOT_READY);

  //
  // Allow CheckAPsStatus()
  //
  mStopCheckApsStatus = FALSE;

  return Status;
}

/**
  MP Service to get all the available application processors (APs)
  to execute a caller-provided code stream.

  @param[in] This                  - Pointer to MP Service Protocol
  @param[in] Procedure             - The procedure to be assigned to APs.
  @param[in] SingleThread          - If true, all APs execute in block mode.
                                     Otherwise, all APs exceute in non-block mode.
  @param[in] WaitEvent             - If timeout, the event to be triggered after all APs finish.
  @param[in] TimeoutInMicroSeconds - The timeout value in microsecond. Zero means infinity.
  @param[in] ProcArguments         - Argument for Procedure.
  @param[in] FailedCpuList         - The list of processor numbers that fail to finish the function before
                                     TimeoutInMicrosecsond expires.

  @retval EFI_SUCCESS           In blocking mode, all APs have finished before the timeout expired.
  @retval EFI_SUCCESS           In non-blocking mode, function has been dispatched to all enabled APs.
  @retval EFI_DEVICE_ERROR      Caller processor is AP.
  @retval EFI_NOT_STARTED       No enabled AP exists in the system.
  @retval EFI_NOT_READY         Any enabled AP is busy.
  @retval EFI_TIMEOUT           In blocking mode, The timeout expired before all enabled APs have finished.
  @retval EFI_INVALID_PARAMETER Procedure is NULL.
**/
EFI_STATUS
EFIAPI
StartupAllAPs (
  IN EFI_MP_SERVICES_PROTOCOL *This,
  IN EFI_AP_PROCEDURE         Procedure,
  IN BOOLEAN                  SingleThread,
  IN EFI_EVENT                WaitEvent OPTIONAL,
  IN UINTN                    TimeoutInMicroSeconds,
  IN VOID                     *ProcArguments OPTIONAL,
  OUT UINTN                   **FailedCpuList OPTIONAL
  )
{
  EFI_STATUS     Status;
  CPU_DATA_BLOCK *CpuData;
  UINTN          ProcessorNumber;
  BOOLEAN        Blocking;

  if (FailedCpuList != NULL) {
    *FailedCpuList = NULL;
  }

  ///
  /// Check whether caller processor is BSP
  ///
  WhoAmI (This, &ProcessorNumber);
  if (ProcessorNumber != mMPSystemData->BSP) {
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Check for valid procedure for APs
  ///
  if (Procedure == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ///
  /// Temporarily suppress CheckAPsStatus()
  ///
  mStopCheckApsStatus = TRUE;

  ///
  /// Check and update APs status if needed.
  ///
  CheckAndUpdateApsStatus ();

  ///
  /// Check whether all enabled APs are idle.
  /// If any enabled AP is not idle, return EFI_NOT_READY.
  ///
  for (ProcessorNumber = 0; ProcessorNumber < mMPSystemData->NumberOfCpus; ProcessorNumber++) {

    CpuData = &mMPSystemData->CpuData[ProcessorNumber];

    mMPSystemData->CpuList[ProcessorNumber] = FALSE;
    if (ProcessorNumber != mMPSystemData->BSP) {
      if (CpuData->State != CPU_STATE_DISABLED) {
        if (CpuData->State != CPU_STATE_IDLE) {
          mStopCheckApsStatus = FALSE;
          return EFI_NOT_READY;
        } else {
          //
          // Mark this processor as responsible for current calling.
          //
          mMPSystemData->CpuList[ProcessorNumber] = TRUE;
        }
      }
    }
  }

  mMPSystemData->FinishCount = 0;
  mMPSystemData->StartCount  = 0;
  Blocking                   = FALSE;
  //
  // Go through all enabled APs to wakeup them for Procedure.
  // If in Single Thread mode, then only one AP is woken up, and others are waiting.
  //
  for (ProcessorNumber = 0; ProcessorNumber < mMPSystemData->NumberOfCpus; ProcessorNumber++) {

    CpuData = &mMPSystemData->CpuData[ProcessorNumber];
    //
    // Check whether this processor is responsible for current calling.
    //
    if (mMPSystemData->CpuList[ProcessorNumber]) {

      mMPSystemData->StartCount++;

      AsmAcquireMPLock (&CpuData->StateLock);
      CpuData->State = CPU_STATE_READY;
      AsmReleaseMPLock (&CpuData->StateLock);

      if (!Blocking) {
        WakeUpAp (
          ProcessorNumber,
          Procedure,
          ProcArguments
          );
      }

      if (SingleThread) {
        Blocking = TRUE;
      }
    }
  }

  //
  // If no enabled AP exists, return EFI_NOT_STARTED.
  //
  if (mMPSystemData->StartCount == 0) {
    mStopCheckApsStatus = FALSE;
    return EFI_NOT_STARTED;
  }
  //
  // If WaitEvent is not NULL, execute in non-blocking mode.
  // BSP saves data for CheckAPsStatus(), and returns EFI_SUCCESS.
  // CheckAPsStatus() will check completion and timeout periodically.
  //
  mMPSystemData->Procedure      = Procedure;
  mMPSystemData->ProcArguments  = ProcArguments;
  mMPSystemData->SingleThread   = SingleThread;
  mMPSystemData->FailedCpuList  = FailedCpuList;
  mMPSystemData->ExpectedTime   = CalculateTimeout (TimeoutInMicroSeconds, &mMPSystemData->CurrentTime);
  mMPSystemData->TotalTime      = 0;
  mMPSystemData->WaitEvent      = WaitEvent;

  if (WaitEvent != NULL) {
    //
    // Allow CheckAPsStatus()
    //
    mStopCheckApsStatus = FALSE;
    return EFI_SUCCESS;
  }

  //
  // If WaitEvent is NULL, execute in blocking mode.
  // BSP checks APs'state until all APs finish or TimeoutInMicrosecsond expires.
  //
  do {
    Status = CheckAllAps ();
  } while (Status == EFI_NOT_READY);

  //
  // Allow CheckAPsStatus()
  //
  mStopCheckApsStatus = FALSE;

  return Status;
}

/**
  MP Service to makes the current BSP into an AP and then switches the
  designated AP into the AP. This procedure is usually called after a CPU
  test that has found that BSP is not healthy to continue it's responsbilities.

  @param[in] This            - Pointer to MP Service Protocol.
  @param[in] ProcessorNumber - The number of the specified AP.
  @param[in] EnableOldBSP    - Whether to enable or disable the original BSP.

  @retval EFI_SUCCESS           BSP successfully switched.
  @retval EFI_DEVICE_ERROR      Caller processor is AP.
  @retval EFI_NOT_FOUND         Processor with the handle specified by ProcessorNumber does not exist.
  @retval EFI_INVALID_PARAMETER ProcessorNumber specifies the BSP or disabled AP.
  @retval EFI_NOT_READY         Specified AP is busy.
**/
EFI_STATUS
EFIAPI
SwitchBSP (
  IN EFI_MP_SERVICES_PROTOCOL *This,
  IN UINTN                    ProcessorNumber,
  IN BOOLEAN                  EnableOldBSP
  )
{
  EFI_STATUS            Status;
  EFI_CPU_ARCH_PROTOCOL *CpuArch;
  BOOLEAN               OldInterruptState;
  CPU_DATA_BLOCK        *CpuData;
  CPU_STATE             CpuState;
  UINTN                 CallerNumber;

  ///
  /// Check whether caller processor is BSP
  ///
  WhoAmI (This, &CallerNumber);
  if (CallerNumber != mMPSystemData->BSP) {
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Check whether processor with the handle specified by ProcessorNumber exists
  ///
  if (ProcessorNumber >= mMPSystemData->NumberOfCpus) {
    return EFI_NOT_FOUND;
  }

  ///
  /// Check if the specified CPU is already BSP
  ///
  if (ProcessorNumber == mMPSystemData->BSP) {
    return EFI_INVALID_PARAMETER;
  }

  CpuData = &mMPSystemData->CpuData[ProcessorNumber];

  ///
  /// Check whether specified AP is disabled
  ///
  if (CpuData->State == CPU_STATE_DISABLED) {
    return EFI_NOT_READY;
  }
  ///
  /// Check whether specified AP is busy
  ///
  if (CpuData->State != CPU_STATE_IDLE) {
    return EFI_NOT_READY;
  }

  ///
  /// Before send both BSP and AP to a procedure to exchange their roles,
  /// interrupt must be disabled. This is because during the exchange role
  /// process, 2 CPU may use 1 stack. If interrupt happens, the stack will
  /// be corrputed, since interrupt return address will be pushed to stack
  /// by hardware.
  ///
  CpuArch = mMPSystemData->CpuArch;
  (CpuArch->GetInterruptState) (CpuArch, &OldInterruptState);
  if (OldInterruptState) {
    Status = CpuArch->DisableInterrupt (CpuArch);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  ///
  /// Unprogram virtual wire mode for the old BSP
  ///
  ProgramCpuXApic (FALSE);
  SetApicBspBit (FALSE);

  mMPSystemData->BSPInfo.State  = CPU_SWITCH_STATE_IDLE;
  mMPSystemData->BSPInfo.Lock   = VacantFlag;
  mMPSystemData->APInfo.State   = CPU_SWITCH_STATE_IDLE;
  mMPSystemData->APInfo.Lock    = VacantFlag;

  ///
  /// Need to wakeUp AP (future BSP)
  ///
  WakeUpAp (
    ProcessorNumber,
    (EFI_AP_PROCEDURE) FutureBspProc,
    mMPSystemData
    );

  AsmExchangeRole (&mMPSystemData->BSPInfo, &mMPSystemData->APInfo);

  ///
  /// The new BSP has come out. Since it carries the register value of the AP, need
  /// to pay attention to variable which are stored in registers (due to optimization)
  ///
  SetApicBspBit (TRUE);
  ProgramCpuXApic (TRUE);

  if (OldInterruptState) {
    Status = CpuArch->EnableInterrupt (CpuArch);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  CpuData = &mMPSystemData->CpuData[mMPSystemData->BSP];
  while (TRUE) {
    AsmAcquireMPLock (&CpuData->StateLock);
    CpuState = CpuData->State;
    AsmReleaseMPLock (&CpuData->StateLock);

    if (CpuState == CPU_STATE_FINISHED) {
      break;
    }
  }

  Status              = ChangeCpuState (mMPSystemData->BSP, EnableOldBSP, CPU_CAUSE_NOT_DISABLED);
  mMPSystemData->BSP  = ProcessorNumber;

  return EFI_SUCCESS;
}

/**
  This procedure enables Or disables APs.

  @param[in] This            - Pointer to MP Service Protocol.
  @param[in] ProcessorNumber - The number of the specified AP.
  @param[in] NewAPState      - Indicate new desired AP state
  @param[in] HealthState     - If not NULL, it points to the value that specifies
                               the new health status of the AP.  If it is NULL,
                               this parameter is ignored.

  @retval EFI_SUCCESS            AP successfully enabled or disabled.
  @retval EFI_DEVICE_ERROR       Caller processor is AP.
  @retval EFI_NOT_FOUND          Processor with the handle specified by ProcessorNumber does not exist.
  @retval EFI_INVALID_PARAMETERS ProcessorNumber specifies the BSP.
**/
EFI_STATUS
EFIAPI
EnableDisableAP (
  IN EFI_MP_SERVICES_PROTOCOL   *This,
  IN UINTN                      ProcessorNumber,
  IN BOOLEAN                    NewAPState,
  IN UINT32                     *HealthState OPTIONAL
  )
{
  EFI_STATUS     Status;
  CPU_DATA_BLOCK *CpuData;
  UINTN          CallerNumber;

  ///
  /// Check whether caller processor is BSP
  ///
  WhoAmI (This, &CallerNumber);
  if (CallerNumber != mMPSystemData->BSP) {
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Check whether processor with the handle specified by ProcessorNumber exists
  ///
  if (ProcessorNumber >= mMPSystemData->NumberOfCpus) {
    return EFI_NOT_FOUND;
  }

  //
  // Check whether specified processor is BSP
  //
  if (ProcessorNumber == mMPSystemData->BSP) {
    return EFI_INVALID_PARAMETER;
  }

  CpuData = &mMPSystemData->CpuData[ProcessorNumber];
  Status  = ChangeCpuState (ProcessorNumber, NewAPState, CPU_CAUSE_USER_SELECTION);

  if (HealthState != NULL) {
    CopyMem (&CpuData->Health, HealthState, sizeof (UINT32));
  }

  return EFI_SUCCESS;
}

/**
  This procedure returns the calling CPU handle.

  @param[in] This            - Pointer to MP Service Protocol.
  @param[in] ProcessorNumber - The number of the specified AP.

  @retval EFI_SUCCESS           Processor number successfully returned.
  @retval EFI_INVALID_PARAMETER ProcessorNumber is NULL
**/
EFI_STATUS
EFIAPI
WhoAmI (
  IN EFI_MP_SERVICES_PROTOCOL *This,
  OUT UINTN                   *ProcessorNumber
  )
{
  UINTN ApicID;
  UINTN Index;

  //
  // Check parameter ProcessorNumber
  //
  if (ProcessorNumber == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ApicID    = GetCpuApicId ();

  for (Index = 0; Index < mMPSystemData->NumberOfCpus; Index++) {
    if (ApicID == mMPSystemData->CpuData[Index].ApicID) {
      break;
    }
  }

  *ProcessorNumber = Index;
  return EFI_SUCCESS;
}

/**
  Checks APs' status periodically.

  This function is triggerred by timer perodically to check the
  state of APs for StartupAllAPs() and StartupThisAP() executed
  in non-blocking mode.

  @param[in] Event   - Event triggered.
  @param[in] Context - Parameter passed with the event.
**/
VOID
EFIAPI
CheckApsStatus (
  IN  EFI_EVENT                           Event,
  IN  VOID                                *Context
  )
{
  //
  // If CheckAPsStatus() is not stopped, otherwise return immediately.
  //
  if (!mStopCheckApsStatus) {
    CheckAndUpdateApsStatus ();
  }
}

/**
  Searches the HOB list provided by the core to find
  if a MP guided HOB list exists or not. If it does, it copies it to the driver
  data area, else returns 0

  @param[in] MPSystemData - Pointer to an MP_SYSTEM_DATA structure

  @retval EFI_SUCCESS  - Success
  @retval EFI_NOT_FOUND - HOB not found or else
**/
EFI_STATUS
GetMpBistStatus (
  IN MP_SYSTEM_DATA *MPSystemData
  )
{
  VOID                 *HobList;
  VOID                 *DataInHob;
  EFI_PEI_HOB_POINTERS Hob;
  UINTN                DataSize;

  ///
  /// Check for MP Data Hob.
  ///
  HobList = GetFirstGuidHob (&gHtBistHobGuid);

  if (HobList == NULL) {
    DEBUG ((DEBUG_ERROR, "No HOBs found\n"));
    return EFI_NOT_FOUND;
  }

  DataInHob   = (VOID *) ((UINTN) HobList + sizeof (EFI_HOB_GUID_TYPE));

  Hob.Header  = HobList;
  DataSize    = Hob.Header->HobLength - sizeof (EFI_HOB_GUID_TYPE);

  ///
  /// This is the MP HOB. So, copy all the data
  ///
  if (HobList != NULL) {
    if (NULL == MPSystemData->BistHobData) {
      MPSystemData->BistHobData = AllocateReservedPool (DataSize);
    }

    CopyMem (MPSystemData->BistHobData, DataInHob, DataSize);
    MPSystemData->BistHobSize = DataSize;
  }

  return EFI_SUCCESS;
}

/**
  Allocate data pool for MP information and fill data in it.

  @param[in] WakeUpBuffer           - The address of wakeup buffer.
  @param[in] StackAddressStart      - The start address of APs's stacks.
  @param[in] TotalCpusForThisSystem - Total number of logical processors in this system.

  @retval EFI_SUCCESS              - Function successfully executed.
  @retval Other                    - Error occurred while allocating memory.
**/
EFI_STATUS
FillMpData (
  OUT EFI_PHYSICAL_ADDRESS WakeUpBuffer,
  OUT VOID                 *StackAddressStart,
  IN UINTN                 TotalCpusForThisSystem
  )
{
  EFI_STATUS             Status;
  UINT16                 ProcessorThreadsPerCore;
  BOOLEAN                HyperThreadingEnabled;
  VOID                   *GuidHob;

  ///
  /// First check if the MP data structures and AP rendezvous routine have been
  /// supplied by the PEIMs that executed in early boot stage.
  ///
  ///
  /// Clear the data structure area first. @todo: Remove this line. Memory already cleared when it was first initialized.
  ///
  ZeroMem (mMPSystemData, sizeof (MP_SYSTEM_DATA));
  Status = GetMpBistStatus (mMPSystemData);
  HyperThreadingEnabled = TRUE;

  ///
  /// HyperThreading is disabled if there's only 1 thread per core.
  ///
  GetEnabledCount (&ProcessorThreadsPerCore, NULL, NULL, NULL);
  if (ProcessorThreadsPerCore == 1) {
    HyperThreadingEnabled = FALSE;
  }

  mAcpiCpuData->APState         = HyperThreadingEnabled;
  mAcpiCpuData->WakeUpBuffer    = WakeUpBuffer;
  mAcpiCpuData->StackAddress    = (EFI_PHYSICAL_ADDRESS) (UINTN) StackAddressStart;

  ///
  /// Copy CpuPrivateData from CpuS3ResumeDataHob
  ///
  GuidHob = GetFirstGuidHob (&gCpuS3ResumeDataHobGuid);
  if ((GuidHob != NULL) && (GET_GUID_HOB_DATA_SIZE (GuidHob) == sizeof(CPU_PRIVATE_DATA))) {
    CopyMem (
      &mMPSystemData->CpuPrivateData,
      GET_GUID_HOB_DATA (GuidHob),
      GET_GUID_HOB_DATA_SIZE (GuidHob)
      );
  } else {
    DEBUG ((DEBUG_ERROR, "Error restoring CpuPrivateData from CpuS3ResumeDataHob\n"));
  }

  mMPSystemData->CpuPrivateData.S3BspMtrrTablePointer = (UINT32) (UINTN) mMPSystemData->S3BspMtrrTable;

  Status = PrepareGdtIdtForAP (
             (IA32_DESCRIPTOR *) (UINTN) mAcpiCpuData->GdtrProfile,
             (IA32_DESCRIPTOR *) (UINTN) mAcpiCpuData->IdtrProfile
             );

  ///
  /// First BSP fills and inits all known values, including it's own records.
  ///
  mMPSystemData->ApSerializeLock    = VacantFlag;
  mMPSystemData->NumberOfCpus       = 1;
  mMPSystemData->EnableSecondaryCpu = HyperThreadingEnabled;

  ///
  /// Record these CPU configuration data (both for normal boot and for S3 use)
  ///
  mMPSystemData->CpuArch                   = NULL;
  gBS->LocateProtocol (&gEfiCpuArchProtocolGuid, NULL, (VOID **) &mMPSystemData->CpuArch);

  mMPSystemData->TotalCpusForThisSystem = TotalCpusForThisSystem;

  mMPSystemData->BSP                      = 0;

  ///
  /// Save Mtrr Register for S3 resume
  ///
  SaveBspMtrrForS3 ();

  FillInProcessorInformation (mMPSystemData, TRUE, 0);

  return EFI_SUCCESS;
}

/**
  Wake up APs for the first time to count their number and collect BIST data.

  @param[in] WakeUpBuffer      - Address of the wakeup buffer.

  @retval EFI_SUCCESS       - Function successfully finishes.
**/
EFI_STATUS
CountApNumberAndCollectBist (
  IN EFI_PHYSICAL_ADDRESS WakeUpBuffer
  )
{
  MP_CPU_EXCHANGE_INFO *ExchangeInfo;
  UINTN                Index;
  UINT64               MsrValue;
  UINT64               ProcessorThreadCount;
  UINT32               ResponseProcessorCount;
  UINTN                TimeoutTime;

  ///
  /// Send INIT IPI - SIPI to all APs
  ///
  SendInterrupt (
    BROADCAST_MODE_ALL_EXCLUDING_SELF,
    0,
    0,
    DELIVERY_MODE_INIT,
    TRIGGER_MODE_EDGE,
    TRUE
    );
  MicroSecondDelay (10 * STALL_ONE_MILLI_SECOND);
  SendInterrupt (
    BROADCAST_MODE_ALL_EXCLUDING_SELF,
    0,
    (UINT32) RShiftU64 (WakeUpBuffer, 12),
    DELIVERY_MODE_SIPI,
    TRIGGER_MODE_EDGE,
    TRUE
    );
  MicroSecondDelay (200 * STALL_ONE_MICRO_SECOND);
  SendInterrupt (
    BROADCAST_MODE_ALL_EXCLUDING_SELF,
    0,
    (UINT32) RShiftU64 (WakeUpBuffer, 12),
    DELIVERY_MODE_SIPI,
    TRIGGER_MODE_EDGE,
    TRUE
    );
  MicroSecondDelay (200 * STALL_ONE_MICRO_SECOND);
  ExchangeInfo = (MP_CPU_EXCHANGE_INFO *) (UINTN) (WakeUpBuffer + MP_CPU_EXCHANGE_INFO_OFFSET);

  ///
  /// Get thread count
  ///
  MsrValue              = AsmReadMsr64 (MSR_CORE_THREAD_COUNT);
  ProcessorThreadCount  = MsrValue & 0xffff;

  ///
  /// Only support MAX_PROCESSOR_THREADS threads so far
  ///
  ASSERT (ProcessorThreadCount <= MAX_PROCESSOR_THREADS);
  if (ProcessorThreadCount > MAX_PROCESSOR_THREADS) {
    ProcessorThreadCount = MAX_PROCESSOR_THREADS;
  }

  for (TimeoutTime = 0; TimeoutTime <= CPU_WAIT_FOR_TASK_TO_BE_COMPLETED; TimeoutTime += CPU_CHECK_AP_INTERVAL) {
    ///
    /// Wait for task to complete and then exit.
    ///
    MicroSecondDelay (CPU_CHECK_AP_INTERVAL);
    for (Index = 1, ResponseProcessorCount = 1; Index < MAX_PROCESSOR_THREADS; Index++) {
      if (ExchangeInfo->BistBuffer[Index].Number == 1) {
        ResponseProcessorCount++;
      }
    }

    if (ResponseProcessorCount == ProcessorThreadCount) {
      break;
    }
  }

  for (Index = 0; Index < MAX_PROCESSOR_THREADS; Index++) {
    if (ExchangeInfo->BistBuffer[Index].Number == 1) {
      ExchangeInfo->BistBuffer[Index].Number = (UINT32) mMPSystemData->NumberOfCpus++;
    }
  }

  mAcpiCpuData->NumberOfCpus  = (UINT32) mMPSystemData->NumberOfCpus;

  ExchangeInfo->InitFlag      = 0;

  return EFI_SUCCESS;
}

/**
  Wake up APs for the second time to collect detailed information.

  @param[in] WakeUpBuffer      - Address of the wakeup buffer.

  @retval EFI_SUCCESS       - Function successfully finishes.
**/
EFI_STATUS
PollForInitialization (
  IN EFI_PHYSICAL_ADDRESS WakeUpBuffer
  )
{
  MP_CPU_EXCHANGE_INFO *ExchangeInfo;

  ExchangeInfo              = (MP_CPU_EXCHANGE_INFO *) (UINTN) (WakeUpBuffer + MP_CPU_EXCHANGE_INFO_OFFSET);

  ExchangeInfo->ApFunction  = (VOID *) (UINTN) DetailedMpInitialization;

  CpuInitFloatPointUnit ();

  ///
  /// Wait until all APs finish
  ///
  while (mFinishedCount < mAcpiCpuData->NumberOfCpus - 1) {
    CpuPause ();
  }
  return EFI_SUCCESS;
}

/**
  Initialize multiple processors and collect MP related data

  @retval EFI_SUCCESS   - Multiple processors get initialized and data collected successfully
  @retval Other         - The operation failed and appropriate error status will be returned
**/
EFI_STATUS
InitializeMpSystemData (
  VOID
  )
{
  EFI_STATUS Status;
  UINT16     EnabledThreadsPerCore;
  UINT16     EnabledCoresPerDie;
  UINT16     DiesPerPackage;
  UINT16     Packages;

  VOID                 *StackAddressStart;
  EFI_PHYSICAL_ADDRESS WakeUpBuffer;
  MP_CPU_EXCHANGE_INFO *ExchangeInfo;
  UINTN                Index;

  EFI_CPU_ARCH_PROTOCOL *CpuArch;
  BOOLEAN               mInterruptState;
  CPU_DATA_BLOCK        *CpuData;
  UINTN                 TotalCpusForThisSystem;
  EFI_HANDLE            Handle;
  Handle                = NULL;

  ///
  /// Program Local APIC registers
  ///
  ProgramCpuXApic (TRUE);

  ///
  /// Get information on enabled threads, cores, dies and package for the CPU(s) on this platform
  ///
  GetEnabledCount (
    &EnabledThreadsPerCore,
    &EnabledCoresPerDie,
    &DiesPerPackage,
    &Packages
    );
  ///
  /// Get the total CPU count
  ///
  TotalCpusForThisSystem = EnabledThreadsPerCore * EnabledCoresPerDie * DiesPerPackage * Packages;

  ///
  /// Prepare Wakeup Buffer and Stack for APs
  ///
  Status = PrepareMemoryForAPs (
             &WakeUpBuffer,
             &StackAddressStart,
             TotalCpusForThisSystem
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  mOriginalBuffer = WakeUpBuffer;
  mBackupBuffer   = (EFI_PHYSICAL_ADDRESS) (UINTN) AllocatePages (1);

  ///
  /// Fill MP Data
  ///
  FillMpData (
    WakeUpBuffer,
    StackAddressStart,
    TotalCpusForThisSystem
    );

  ///
  /// Prepare exchange information for APs
  ///
  ExchangeInfo = (MP_CPU_EXCHANGE_INFO *) (UINTN) (WakeUpBuffer + MP_CPU_EXCHANGE_INFO_OFFSET);
  PrepareExchangeInfo (
    ExchangeInfo,
    StackAddressStart,
    NULL,
    WakeUpBuffer
    );

  ReportStatusCode (
    EFI_PROGRESS_CODE,
    EFI_COMPUTING_UNIT_HOST_PROCESSOR | EFI_CU_HP_PC_AP_INIT
    );

  CpuArch = mMPSystemData->CpuArch;
  (CpuArch->GetInterruptState) (CpuArch, &mInterruptState);
  CpuArch->DisableInterrupt (CpuArch);

  ///
  /// First INIT-SIPI-SIPI and reset AP waking counters
  ///
  CountApNumberAndCollectBist (WakeUpBuffer);
  ExchangeInfo->WakeUpApManner = WakeUpApCounterInit;

  ///
  /// Assign AP function to initialize FPU MCU MTRR and get detail info
  ///
  PollForInitialization (WakeUpBuffer);
  ///
  /// Assign WakeUpApManner (WakeUpApPerHltLoop/WakeUpApPerMwaitLoop/WakeUpApPerRunLoop)
  ///
  ExchangeInfo->WakeUpApManner = (WAKEUP_AP_MANNER) mCpuConfigData->ApIdleManner;
  ///
  /// Assign AP function to ApProcWrapper for StartAllAps/StartThisAp calling
  ///
  ExchangeInfo->ApFunction = (VOID *) (UINTN) ApProcWrapper;

  if (mInterruptState) {
    CpuArch->EnableInterrupt (CpuArch);
  }

  for (Index = 1; Index < mMPSystemData->NumberOfCpus; Index++) {
    CpuData = &mMPSystemData->CpuData[Index];
    if (CpuData->Health != 0) {
      DEBUG ((DEBUG_ERROR, "BIST for the following AP failed\n"));
      DEBUG ((DEBUG_ERROR, "EAX=%x\n", CpuData->Health));
      ReportStatusCode (
        EFI_ERROR_MAJOR | EFI_ERROR_CODE,
        EFI_COMPUTING_UNIT_HOST_PROCESSOR | EFI_CU_HP_EC_SELF_TEST
        );
    }

  }

  Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  CheckAllApsStatus,
                  NULL,
                  &mMPSystemData->CheckAllAPsEvent
                  );
  for (Index = 0; Index < mMPSystemData->NumberOfCpus; Index++) {
    CpuData = &mMPSystemData->CpuData[Index];
    if (Index == mMPSystemData->BSP) {
      continue;
    }
    Status = gBS->CreateEvent (
                    EVT_TIMER | EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    CheckThisApStatus,
                    (VOID *) CpuData,
                    CpuData->CheckThisAPEvent
                    );
  }

  CopyMem ((VOID *) (UINTN) mBackupBuffer, (VOID *) (UINTN) mOriginalBuffer, EFI_PAGE_SIZE);

  return EFI_SUCCESS;
}

/**
  Wrapper function for all procedures assigned to AP via MP service protocol.
  It controls states of AP and invokes assigned precedure.
**/
VOID
ApProcWrapper (
  VOID
  )
{
  EFI_AP_PROCEDURE     Procedure;
  VOID                 *Parameter;
  UINTN                ProcessorNumber;
  CPU_DATA_BLOCK       *CpuData;
  MP_CPU_EXCHANGE_INFO *ExchangeInfo;
  MONITOR_MWAIT_DATA   *MonitorAddr;

  WhoAmI (&mMpService, &ProcessorNumber);
  CpuData = &mMPSystemData->CpuData[ProcessorNumber];

  ///
  /// Now let us check it out.
  ///
  Procedure = CpuData->Procedure;
  Parameter = (VOID*)CpuData->Parameter;

  if (Procedure != NULL) {
    AsmAcquireMPLock (&CpuData->StateLock);
    CpuData->State = CPU_STATE_BUSY;
    AsmReleaseMPLock (&CpuData->StateLock);
    Procedure (Parameter);

    ///
    /// if BSP is switched to AP, it continue execute from here, but it carries register state
    /// of the old AP, so need to reload CpuData (might be stored in a register after compiler
    /// optimization) to make sure it points to the right data
    ///
    WhoAmI (&mMpService, &ProcessorNumber);
    CpuData = &mMPSystemData->CpuData[ProcessorNumber];

    AsmAcquireMPLock (&CpuData->ProcedureLock);
    CpuData->Procedure = NULL;
    AsmReleaseMPLock (&CpuData->ProcedureLock);

    AsmAcquireMPLock (&CpuData->StateLock);
    CpuData->State = CPU_STATE_FINISHED;
    AsmReleaseMPLock (&CpuData->StateLock);

    ///
    /// Check AP wakeup manner, update signal and relating counter once finishing AP task
    ///
    ExchangeInfo = (MP_CPU_EXCHANGE_INFO *) (UINTN) (mAcpiCpuData->WakeUpBuffer + MP_CPU_EXCHANGE_INFO_OFFSET);
    MonitorAddr = (MONITOR_MWAIT_DATA *)
                    (
                    (UINT8 *) ExchangeInfo->StackStart +
                    (ExchangeInfo->BistBuffer[CpuData->ApicID].Number + 1) *
                    ExchangeInfo->StackSize -
                    MONITOR_FILTER_SIZE
                    );

    switch (ExchangeInfo->WakeUpApManner) {
      case WakeUpApPerHltLoop:
        MonitorAddr->HltLoopBreakCounter += 1;
        break;

      case WakeUpApPerMwaitLoop:
        MonitorAddr->MwaitLoopBreakCounter += 1;
        break;

      case WakeUpApPerRunLoop:
        MonitorAddr->RunLoopBreakCounter += 1;
        break;

      case WakeUpApPerMwaitLoop32:
        MonitorAddr->MwaitLoopBreakCounter32 += 1;
        break;

      case WakeUpApPerRunLoop32:
        MonitorAddr->RunLoopBreakCounter32 += 1;
        break;

      default:
        break;
    }

    MonitorAddr->BreakToRunApSignal = 0;
  }
}

/**
  Procedure for detailed initialization of APs. It will be assigned to all APs
  after first INIT-SIPI-SIPI finishing CPU number counting and BIST collection.
**/
VOID
DetailedMpInitialization (
  VOID
  )
{

  CpuInitFloatPointUnit ();

  ///
  /// Save Mtrr Registers in global data areas
  ///
  MpMtrrSynchUp (NULL);
  ProgramCpuXApic (FALSE);
  FillInProcessorInformation (mMPSystemData, FALSE, 0);
  InterlockedIncrement (&mFinishedCount);
}

/**
  Switch current BSP processor to AP

  @param[in] MPSystemData  - Pointer to the data structure containing MP related data
**/
VOID
EFIAPI
FutureBspProc (
  IN MP_SYSTEM_DATA *MPSystemData
  )
{
  AsmExchangeRole (&MPSystemData->APInfo, &MPSystemData->BSPInfo);
  return;
}

/**
  Fill in the CPU location information

  @param[out] Location  - CPU location information

  @retval EFI_SUCCESS  - always return success
**/
EFI_STATUS
FillInCpuLocation (
  OUT EFI_CPU_PHYSICAL_LOCATION *Location
  )
{
  UINT32             ApicId;
  EFI_CPUID_REGISTER RegsInfo;
  UINT32             LevelType;
  UINT32             LevelBits;
  UINT8              Shift;
  UINT8              Bits;
  UINT32             Mask;
  BOOLEAN            HyperThreadingEnabled;

  AsmCpuid (CPUID_VERSION_INFO, &RegsInfo.RegEax, &RegsInfo.RegEbx, &RegsInfo.RegEcx, &RegsInfo.RegEdx);
  ApicId = (RegsInfo.RegEbx >> 24);

  AsmCpuid (CPUID_SIGNATURE, &RegsInfo.RegEax, &RegsInfo.RegEbx, &RegsInfo.RegEcx, &RegsInfo.RegEdx);
  if (RegsInfo.RegEax >= CPUID_EXTENDED_TOPOLOGY) {
    LevelBits = 0;
    LevelType = 0;
    do {
      AsmCpuidEx (
        CPUID_EXTENDED_TOPOLOGY,
        LevelType,
        &RegsInfo.RegEax,
        &RegsInfo.RegEbx,
        &RegsInfo.RegEcx,
        &RegsInfo.RegEdx
        );
      LevelType = ((RegsInfo.RegEcx >> 8) & 0xFF);
      switch (LevelType) {
        case 1:
          ///
          /// Thread
          ///
          Location->Thread  = ApicId & ((1 << (RegsInfo.RegEax & 0x0F)) - 1);
          LevelBits         = RegsInfo.RegEax & 0x0F;
          break;

        case 2:
          ///
          /// Core
          ///
          Location->Core  = ApicId >> LevelBits;
          LevelBits       = RegsInfo.RegEax & 0x0F;
          break;

        default:
          ///
          /// End of Level
          ///
          Location->Package = ApicId >> LevelBits;
          break;
      }
    } while (!(RegsInfo.RegEax == 0 && RegsInfo.RegEbx == 0));
  } else {

    AsmCpuid (CPUID_VERSION_INFO, &RegsInfo.RegEax, &RegsInfo.RegEbx, &RegsInfo.RegEcx, &RegsInfo.RegEdx);
    Bits  = 0;
    Shift = (UINT8) ((RegsInfo.RegEbx >> 16) & 0xFF);

    Mask  = Shift - 1;
    while (Shift > 1) {
      Shift >>= 1;
      Bits++;
    }

    HyperThreadingEnabled = FALSE;
    AsmCpuidEx (CPUID_CACHE_PARAMS, 0, &RegsInfo.RegEax, &RegsInfo.RegEbx, &RegsInfo.RegEcx, &RegsInfo.RegEdx);
    if (Mask > (RegsInfo.RegEax >> 26)) {
      HyperThreadingEnabled = TRUE;
    }

    Location->Package = (ApicId >> Bits);
    if (HyperThreadingEnabled) {
      Location->Core    = (ApicId & Mask) >> 1;
      Location->Thread  = (ApicId & Mask) & 1;
    } else {
      Location->Core    = (ApicId & Mask);
      Location->Thread  = 0;
    }
  }

  return EFI_SUCCESS;
}

/**
  This function is called by all processors (both BSP and AP) once and collects MP related data

  @param[in] MPSystemData  - Pointer to the data structure containing MP related data
  @param[in] BSP           - TRUE if the CPU is BSP
  @param[in] BistParam     - BIST (build-in self test) data for the processor. This data
                             is only valid for processors that are waked up for the 1ast
                             time in this CPU DXE driver.

  @retval EFI_SUCCESS   - Data for the processor collected and filled in
**/
EFI_STATUS
FillInProcessorInformation (
  IN MP_SYSTEM_DATA *MPSystemData,
  IN BOOLEAN        BSP,
  IN UINT32         BistParam
  )
{
  UINT32               Health;
  UINT32               ApicID;
  CPU_DATA_BLOCK       *CpuData;
  UINT32               BIST;
  UINTN                ProcessorNumber;
  UINTN                Index;
  UINTN                Count;
  MP_CPU_EXCHANGE_INFO *ExchangeInfo;

  ApicID  = GetCpuApicId ();
  BIST    = 0;

  if (BSP) {
    ProcessorNumber = 0;
    BIST      = BistParam;
  } else {
    ExchangeInfo  = (MP_CPU_EXCHANGE_INFO *) (UINTN) (mAcpiCpuData->WakeUpBuffer + MP_CPU_EXCHANGE_INFO_OFFSET);
    ProcessorNumber     = ExchangeInfo->BistBuffer[ApicID].Number;
    BIST          = ExchangeInfo->BistBuffer[ApicID].Bist;
  }

  CpuData                 = &MPSystemData->CpuData[ProcessorNumber];
  CpuData->SecondaryCpu   = IsSecondaryThread ();
  CpuData->ApicID         = ApicID;
  CpuData->Procedure      = NULL;
  CpuData->Parameter      = NULL;
  CpuData->StateLock      = VacantFlag;
  CpuData->ProcedureLock  = VacantFlag;
  CpuData->State          = CPU_STATE_IDLE;

  Health                  = BIST;
  Count                   = MPSystemData->BistHobSize / sizeof (BIST_HOB_DATA);
  for (Index = 0; Index < Count; Index++) {
    if (ApicID == MPSystemData->BistHobData[Index].ApicId) {
      Health = MPSystemData->BistHobData[Index].Health;
    }
  }

  if (Health > 0) {
    CpuData->State                        = CPU_STATE_DISABLED;
    MPSystemData->DisableCause[ProcessorNumber] = CPU_CAUSE_SELFTEST_FAILURE;

  } else {
    MPSystemData->DisableCause[ProcessorNumber] = CPU_CAUSE_NOT_DISABLED;
  }

  FillInCpuLocation (&CpuData->PhysicalLocation);

  return EFI_SUCCESS;
}

/**
  Set APIC BSP bit

  @param[in] Enable  - enable as BSP or not

  @retval EFI_SUCCESS - always return success
**/
EFI_STATUS
SetApicBspBit (
  IN BOOLEAN Enable
  )
{
  UINT64 ApicBaseReg;

  ApicBaseReg = AsmReadMsr64 (MSR_IA32_APIC_BASE);

  if (Enable) {
    ApicBaseReg |= 0x100;
  } else {
    ApicBaseReg &= 0xfffffffffffffe00;
  }

  AsmWriteMsr64 (MSR_IA32_APIC_BASE, ApicBaseReg);

  return EFI_SUCCESS;
}

/**
  Change CPU state

  @param[in] ProcessorNumber - CPU number
  @param[in] NewState  - the new state that will be changed to
  @param[in] Cause     - Cause

  @retval EFI_SUCCESS - always return success
**/
EFI_STATUS
ChangeCpuState (
  IN UINTN                  ProcessorNumber,
  IN BOOLEAN                NewState,
  IN CPU_STATE_CHANGE_CAUSE Cause
  )
{
  CPU_DATA_BLOCK                             *CpuData;

  CpuData = &mMPSystemData->CpuData[ProcessorNumber];

  mMPSystemData->DisableCause[ProcessorNumber] = Cause;

  if (!NewState) {
    AsmAcquireMPLock (&CpuData->StateLock);
    CpuData->State = CPU_STATE_DISABLED;
    AsmReleaseMPLock (&CpuData->StateLock);

    ReportStatusCode (
      EFI_ERROR_MINOR | EFI_ERROR_CODE,
      EFI_COMPUTING_UNIT_HOST_PROCESSOR | EFI_CU_EC_DISABLED
      );
  } else {
    AsmAcquireMPLock (&CpuData->StateLock);
    CpuData->State = CPU_STATE_IDLE;
    AsmReleaseMPLock (&CpuData->StateLock);
  }

  return EFI_SUCCESS;
}

/**
  If timeout occurs in StartupAllAps(), a timer is set, which invokes this
  procedure periodically to check whether all APs have finished.

  @param[in] Event   - Event triggered.
  @param[in] Context - Parameter passed with the event.
**/
VOID
EFIAPI
CheckAllApsStatus (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  UINTN          ProcessorNumber;
  UINTN          NextCpuNumber;
  CPU_DATA_BLOCK *CpuData;
  CPU_DATA_BLOCK *NextCpuData;
  EFI_STATUS     Status;
  CPU_STATE      CpuState;

  for (ProcessorNumber = 0; ProcessorNumber < mMPSystemData->NumberOfCpus; ProcessorNumber++) {
    CpuData = &mMPSystemData->CpuData[ProcessorNumber];
    if (ProcessorNumber == mMPSystemData->BSP) {
      continue;
    }

    AsmAcquireMPLock (&CpuData->StateLock);
    CpuState = CpuData->State;
    AsmReleaseMPLock (&CpuData->StateLock);

    switch (CpuState) {
      case CPU_STATE_READY:
        WakeUpAp (
          ProcessorNumber,
          mMPSystemData->Procedure,
          mMPSystemData->ProcArguments
          );
        break;

      case CPU_STATE_FINISHED:
        if (mMPSystemData->SingleThread) {
          Status = GetNextBlockedCpuNumber (&NextCpuNumber);
          if (!EFI_ERROR (Status)) {
            NextCpuData = &mMPSystemData->CpuData[NextCpuNumber];

            AsmAcquireMPLock (&NextCpuData->StateLock);
            NextCpuData->State = CPU_STATE_READY;
            AsmReleaseMPLock (&NextCpuData->StateLock);

            WakeUpAp (
              NextCpuNumber,
              mMPSystemData->Procedure,
              mMPSystemData->ProcArguments
              );
          }
        }

        AsmAcquireMPLock (&CpuData->StateLock);
        CpuData->State = CPU_STATE_IDLE;
        AsmReleaseMPLock (&CpuData->StateLock);

        mMPSystemData->FinishCount++;
        break;

      default:
        break;
    }
  }

  if (mMPSystemData->FinishCount == mMPSystemData->StartCount) {
    gBS->SetTimer (
           mMPSystemData->CheckAllAPsEvent,
           TimerCancel,
           0
           );
    Status = gBS->SignalEvent (mMPSystemData->WaitEvent);
  }

  return;
}

/**
  Check if this AP has finished task

  @param[in] Event   - Event triggered.
  @param[in] Context - Parameter passed with the event.
**/
VOID
EFIAPI
CheckThisApStatus (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  CPU_DATA_BLOCK *CpuData;
  EFI_STATUS     Status;
  CPU_STATE      CpuState;

  CpuData = (CPU_DATA_BLOCK *) Context;

  AsmAcquireMPLock (&CpuData->StateLock);
  CpuState = CpuData->State;
  AsmReleaseMPLock (&CpuData->StateLock);

  if (CpuState == CPU_STATE_FINISHED) {
    gBS->SetTimer (
           CpuData->CheckThisAPEvent,
           TimerCancel,
           0
           );
    Status = gBS->SignalEvent (mMPSystemData->WaitEvent);
    AsmAcquireMPLock (&CpuData->StateLock);
    CpuData->State = CPU_STATE_IDLE;
    AsmReleaseMPLock (&CpuData->StateLock);
  }

  return;
}

/**
  Calculate timeout value and return the current performance counter value.

  Calculate the number of performance counter ticks required for a timeout.
  If TimeoutInMicroseconds is 0, return value is also 0, which is recognized
  as infinity.

  @param[in]  TimeoutInMicroseconds   Timeout value in microseconds.
  @param[in]  CurrentTime             Returns the current value of the performance counter.

  @retval     Expected timestamp counter for timeout.
              If TimeoutInMicroseconds is 0, return value is also 0, which is recognized
              as infinity.
**/
UINT64
CalculateTimeout (
  IN UINTN TimeoutInMicroSeconds,
  OUT UINT64  *CurrentTime
  )
{
  UINT64 TimeoutInSeconds;
  UINT64 TimeoutValue;
  UINT64 TimestampCounterFreq;

  //
  // Read the current value of the performance counter
  //
  *CurrentTime = GetPerformanceCounter ();

  //
  // If TimeoutInMicroSeconds is 0, return value is also 0, which is recognized
  // as infinity.
  //
  if (TimeoutInMicroSeconds == 0) {
    return 0;
  }

  //
  // GetPerformanceCounterProperties () returns the timestamp counter's frequency
  // in Hz.
  //
  TimestampCounterFreq = GetPerformanceCounterProperties (NULL, NULL);

  if (TimeoutInMicroSeconds >= 60000000) {
    //
    // if timeout is on minute based, first convert microseconds into seconds,
  // and then multiply with frequency to get number of ticks for the timeout value.
  //
    TimeoutInSeconds = DivU64x32 (TimeoutInMicroSeconds, 1000000);
  TimeoutValue = MultU64x64 (
                     TimestampCounterFreq,
                     TimeoutInSeconds
                     );
  } else {
    //
    // multiply the frequency with TimeoutInMicroSeconds and then divide
    // it by 1,000,000, to get the number of ticks for the timeout value.
    //
  TimeoutValue = DivU64x32 (
                     MultU64x64 (
                       TimestampCounterFreq,
                       TimeoutInMicroSeconds
                       ),
                     1000000
                     );
  }

  return TimeoutValue;
}

/**
  Checks whether timeout expires.

  Check whether the number of ellapsed performance counter ticks required for a timeout condition
  has been reached.  If Timeout is zero, which means infinity, return value is always FALSE.

  @param[in]  PreviousTime         On input, the value of the performance counter when it was last read.
                                   On output, the current value of the performance counter
  @param[in]  TotalTime            The total amount of ellapsed time in performance counter ticks.
  @param[in]  Timeout              The number of performance counter ticks required to reach a timeout condition.

  @retval TRUE                     A timeout condition has been reached.
  @retval FALSE                    A timeout condition has not been reached.
**/
BOOLEAN
CheckTimeout (
  IN OUT UINT64  *PreviousTime,
  IN     UINT64  *TotalTime,
  IN     UINT64  Timeout
  )
{
  UINT64  Start;
  UINT64  End;
  UINT64  CurrentTime;
  INT64   Delta;
  INT64   Cycle;

  if (Timeout == 0) {
    return FALSE;
  }
  GetPerformanceCounterProperties (&Start, &End);
  Cycle = End - Start;
  if (Cycle < 0) {
    Cycle = -Cycle;
  }
  Cycle++;
  CurrentTime = GetPerformanceCounter ();
  Delta = (INT64) (CurrentTime - *PreviousTime);
  if (Start > End) {
    Delta = -Delta;
  }
  if (Delta < 0) {
    Delta += Cycle;
  }
  *TotalTime += Delta;
  *PreviousTime = CurrentTime;
  if (*TotalTime > Timeout) {
    return TRUE;
  }
  return FALSE;
}

/**
  Get the next blocked processor

  @param[in] NextCpuNumber - that will be updated for next blocked CPU number

  @retval EFI_SUCCESS - The next blocked CPU found
  @retval EFI_NOT_FOUND - cannot find blocked CPU
**/
EFI_STATUS
GetNextBlockedCpuNumber (
  OUT UINTN *NextCpuNumber
  )
{
  UINTN          ProcessorNumber;
  CPU_STATE      CpuState;
  CPU_DATA_BLOCK *CpuData;

  for (ProcessorNumber = 0; ProcessorNumber < mMPSystemData->NumberOfCpus; ProcessorNumber++) {
    if (ProcessorNumber == mMPSystemData->BSP) {
      continue;
    }

    CpuData = &mMPSystemData->CpuData[ProcessorNumber];

    AsmAcquireMPLock (&CpuData->StateLock);
    CpuState = CpuData->State;
    AsmReleaseMPLock (&CpuData->StateLock);

    if (CpuState == CPU_STATE_BLOCKED) {
      *NextCpuNumber = ProcessorNumber;
      return EFI_SUCCESS;
    }
  }

  return EFI_NOT_FOUND;
}

/**
  Function to wake up a specified AP and assign procedure to it.

  @param[in] ProcessorNumber Handle number of the specified processor.
  @param[in] Procedure       Procedure to assign.
  @param[in] ProcArguments   Argument for Procedure.
**/
VOID
WakeUpAp (
  IN   UINTN            ProcessorNumber,
  IN   EFI_AP_PROCEDURE Procedure,
  IN   VOID             *ProcArguments
  )
{
  CPU_DATA_BLOCK       *CpuData;
  MP_CPU_EXCHANGE_INFO *ExchangeInfo;
  MONITOR_MWAIT_DATA   *MonitorAddr;

  CpuData = &mMPSystemData->CpuData[ProcessorNumber];

  AsmAcquireMPLock (&CpuData->ProcedureLock);
  CpuData->Parameter  = ProcArguments;
  CpuData->Procedure  = Procedure;
  AsmReleaseMPLock (&CpuData->ProcedureLock);

  ExchangeInfo = (MP_CPU_EXCHANGE_INFO *) (UINTN) (mAcpiCpuData->WakeUpBuffer + MP_CPU_EXCHANGE_INFO_OFFSET);

  ///
  /// Check AP wakeup manner, update signal to wake up AP
  ///
  MonitorAddr = (MONITOR_MWAIT_DATA *)
                  (
                  (UINT8 *) ExchangeInfo->StackStart +
                  (ProcessorNumber + 1) *
                  ExchangeInfo->StackSize -
                  MONITOR_FILTER_SIZE
                  );

  if (ExchangeInfo->WakeUpApManner == WakeUpApPerHltLoop) {
    //
    // Wake up APs by INIT SIPI SIPI
    //
    SendInterrupt (
      BROADCAST_MODE_SPECIFY_CPU,
      CpuData->ApicID,
      0,
      DELIVERY_MODE_INIT,
      TRIGGER_MODE_EDGE,
      TRUE
      );

    MicroSecondDelay (10 * STALL_ONE_MILLI_SECOND);

    SendInterrupt (
      BROADCAST_MODE_SPECIFY_CPU,
      CpuData->ApicID,
      (UINT32) RShiftU64 (mAcpiCpuData->WakeUpBuffer, 12),
      DELIVERY_MODE_SIPI,
      TRIGGER_MODE_EDGE,
      TRUE
      );

    MicroSecondDelay (200 * STALL_ONE_MICRO_SECOND);

    SendInterrupt (
      BROADCAST_MODE_SPECIFY_CPU,
      CpuData->ApicID,
      (UINT32) RShiftU64 (mAcpiCpuData->WakeUpBuffer, 12),
      DELIVERY_MODE_SIPI,
      TRIGGER_MODE_EDGE,
      TRUE
      );

    MicroSecondDelay (200 * STALL_ONE_MICRO_SECOND);
    MonitorAddr->WakeUpApVectorChangeFlag = FALSE;

    //
    // Clear StateLock to 0 to avoid AP locking it then entering SMM and getting INIT-SIPI here could cause dead-lock
    //
    CpuData->StateLock = 0;
  } else if (ExchangeInfo->WakeUpApManner == WakeUpApPerMwaitLoop ||
             ExchangeInfo->WakeUpApManner == WakeUpApPerMwaitLoop32 ||
             ExchangeInfo->WakeUpApManner == WakeUpApPerRunLoop ||
             ExchangeInfo->WakeUpApManner == WakeUpApPerRunLoop32) {
    //
    // Wake up APs by update Monitor memory from Cx state
    //
    MonitorAddr->MwaitTargetCstate        = 0; // Back to C1 state
    MonitorAddr->BreakToRunApSignal       = (UINTN) (BREAK_TO_RUN_AP_SIGNAL | CpuData->ApicID);
    MonitorAddr->WakeUpApVectorChangeFlag = FALSE;
  }
}

/**
  Check whether any AP is running for assigned task.

  @retval TRUE  - Some APs are running.
  @retval FALSE - No AP is running.
**/
BOOLEAN
ApRunning (
  VOID
  )
{
  CPU_DATA_BLOCK *CpuData;
  UINTN          ProcessorNumber;

  for (ProcessorNumber = 0; ProcessorNumber < mMPSystemData->NumberOfCpus; ProcessorNumber++) {
    CpuData = &mMPSystemData->CpuData[ProcessorNumber];

    if (ProcessorNumber != mMPSystemData->BSP) {
      if (CpuData->State == CPU_STATE_READY || CpuData->State == CPU_STATE_BUSY) {
        return TRUE;
      }
    }
  }

  return FALSE;
}

/**
  Checks APs status and updates APs status if needed.
**/
VOID
CheckAndUpdateApsStatus (
  VOID
  )
{
  EFI_STATUS      Status;
  UINTN           ProcessorNumber;
  CPU_DATA_BLOCK  *CpuData;

  //
  // First, check whether pending StartupAllAPs() exists.
  //
  if (mMPSystemData->WaitEvent != NULL) {

    Status = CheckAllAps ();
    //
    // If all APs finish for StartupAllAPs(), signal the WaitEvent for it..
    //
    if (Status != EFI_NOT_READY) {
      Status = gBS->SignalEvent (mMPSystemData->WaitEvent);
      mMPSystemData->WaitEvent = NULL;
    }
  }

  //
  // Second, check whether pending StartupThisAPs() callings exist.
  //
  for (ProcessorNumber = 0; ProcessorNumber < mMPSystemData->NumberOfCpus; ProcessorNumber++) {

    CpuData = &mMPSystemData->CpuData[ProcessorNumber];

    if (CpuData->WaitEvent == NULL) {
      continue;
    }

    Status = CheckThisAp (ProcessorNumber);

    if (Status != EFI_NOT_READY) {
      gBS->SignalEvent (CpuData->WaitEvent);
      CpuData->WaitEvent = NULL;
    }
  }
}

/**
  Checks status of all APs.

  This function checks whether all APs have finished task assigned by StartupAllAPs(),
  and whether timeout expires.

  @retval EFI_SUCCESS          - All APs have finished task assigned by StartupAllAPs().
  @retval EFI_TIMEOUT          - The timeout expires.
  @retval EFI_NOT_READY        - APs have not finished task and timeout has not expired.
  @retval EFI_OUT_OF_RESOURCES - Out of memory.
**/
EFI_STATUS
CheckAllAps (
  VOID
  )
{
  UINTN          ProcessorNumber;
  UINTN          NextProcessorNumber;
  UINTN          ListIndex;
  EFI_STATUS     Status;
  CPU_STATE      CpuState;
  CPU_DATA_BLOCK *CpuData;

  NextProcessorNumber = 0;

  ///
  /// Go through all APs that are responsible for the StartupAllAPs().
  ///
  for (ProcessorNumber = 0; ProcessorNumber < mMPSystemData->NumberOfCpus; ProcessorNumber++) {
    if (!mMPSystemData->CpuList[ProcessorNumber]) {
      continue;
    }

    CpuData = &mMPSystemData->CpuData[ProcessorNumber];

    ///
    ///  Check the CPU state of AP. If it is CPU_STATE_FINISHED, then the AP has finished its task.
    ///  Only BSP and corresponding AP access this unit of CPU Data. This means the AP will not modify the
    ///  value of state after setting the it to CPU_STATE_FINISHED, so BSP can safely make use of its value.
    ///
    CpuState = CpuData->State;

    if (CpuState == CPU_STATE_FINISHED) {
      mMPSystemData->FinishCount++;
      mMPSystemData->CpuList[ProcessorNumber] = FALSE;

      AsmAcquireMPLock (&CpuData->StateLock);
      CpuData->State = CPU_STATE_IDLE;
      AsmReleaseMPLock (&CpuData->StateLock);

      ///
      /// If in Single Thread mode, then search for the next waiting AP for execution.
      ///
      if (mMPSystemData->SingleThread) {
        Status = GetNextWaitingProcessorNumber (&NextProcessorNumber);

        if (!EFI_ERROR (Status)) {
          WakeUpAp (
            NextProcessorNumber,
            mMPSystemData->Procedure,
            mMPSystemData->ProcArguments
            );
        }
      }
    }
  }
  ///
  /// If all APs finish, return EFI_SUCCESS.
  ///
  if (mMPSystemData->FinishCount == mMPSystemData->StartCount) {
    return EFI_SUCCESS;
  }
  ///
  /// If timeout expires, report timeout.
  ///
  if (CheckTimeout (&mMPSystemData->CurrentTime, &mMPSystemData->TotalTime, mMPSystemData->ExpectedTime)) {
    ///
    /// If FailedCpuList is not NULL, record all failed APs in it.
    ///
    if (mMPSystemData->FailedCpuList != NULL) {
      *(mMPSystemData->FailedCpuList) = AllocatePool ((mMPSystemData->StartCount - mMPSystemData->FinishCount +1) * sizeof (UINTN));
      if (*(mMPSystemData->FailedCpuList) == NULL) {
        ASSERT (FALSE);
        return EFI_OUT_OF_RESOURCES;
      }
    }

    ListIndex = 0;

    for (ProcessorNumber = 0; ProcessorNumber < mMPSystemData->NumberOfCpus; ProcessorNumber++) {
      ///
      /// Check whether this processor is responsible for StartupAllAPs().
      ///
      if (mMPSystemData->CpuList[ProcessorNumber]) {
        ///
        /// Reset failed APs to idle state
        ///
        ResetProcessorToIdleState (ProcessorNumber);
        mMPSystemData->CpuList[ProcessorNumber] = FALSE;
        if (mMPSystemData->FailedCpuList != NULL) {
          (*mMPSystemData->FailedCpuList) [ListIndex++] = ProcessorNumber;
        }
      }
    }

    if (mMPSystemData->FailedCpuList != NULL) {
      (*mMPSystemData->FailedCpuList) [ListIndex] = END_OF_CPU_LIST;
    }
    return EFI_TIMEOUT;
  }
  return EFI_NOT_READY;
}

/**
  Checks status of specified AP.

  This function checks whether specified AP has finished task assigned by StartupThisAP(),
  and whether timeout expires.

  @param[in] ProcessorNumber - The handle number of processor.

  @retval EFI_SUCCESS     - Specified AP has finished task assigned by StartupThisAPs().
  @retval EFI_TIMEOUT     - The timeout expires.
  @retval EFI_NOT_READY   - Specified AP has not finished task and timeout has not expired.
**/
EFI_STATUS
CheckThisAp (
  UINTN ProcessorNumber
  )
{
  CPU_DATA_BLOCK *CpuData;
  CPU_STATE      CpuState;

  CpuData = &mMPSystemData->CpuData[ProcessorNumber];

  ///
  ///  Check the CPU state of AP. If it is CPU_STATE_FINISHED, then the AP has finished its task.
  ///  Only BSP and corresponding AP access this unit of CPU Data. This means the AP will not modify the
  ///  value of state after setting the it to CPU_STATE_FINISHED, so BSP can safely make use of its value.
  ///
  CpuState = CpuData->State;

  ///
  /// If the APs finishes for StartupThisAP(), return EFI_SUCCESS.
  ///
  if (CpuState == CPU_STATE_FINISHED) {

    AsmAcquireMPLock (&CpuData->StateLock);
    CpuData->State = CPU_STATE_IDLE;
    AsmReleaseMPLock (&CpuData->StateLock);

    if (CpuData->Finished != NULL) {
      *(CpuData->Finished) = TRUE;
    }

    return EFI_SUCCESS;
  } else {
    ///
    /// If timeout expires for StartupThisAP(), report timeout.
    ///
    if (CheckTimeout (&CpuData->CurrentTime, &CpuData->TotalTime, CpuData->ExpectedTime)) {
      if (CpuData->Finished != NULL) {
        *(CpuData->Finished) = FALSE;
      }
      ///
      /// Reset failed AP to idle state
      ///
      ResetProcessorToIdleState (ProcessorNumber);

      return EFI_TIMEOUT;
    }
  }

  return EFI_NOT_READY;
}

/**
  Searches for the next waiting AP.

  Search for the next AP that is put in waiting state by single-threaded StartupAllAPs().

  @param[in] NextProcessorNumber  - Pointer to the processor number of the next waiting AP.

  @retval EFI_SUCCESS          - The next waiting AP has been found.
  @retval EFI_NOT_FOUND        - No waiting AP exists.
**/
EFI_STATUS
GetNextWaitingProcessorNumber (
  OUT UINTN *NextProcessorNumber
  )
{
  UINTN ProcessorNumber;

  for (ProcessorNumber = 0; ProcessorNumber < mMPSystemData->NumberOfCpus; ProcessorNumber++) {

    if (mMPSystemData->CpuList[ProcessorNumber]) {
      *NextProcessorNumber = ProcessorNumber;
      return EFI_SUCCESS;
    }
  }

  return EFI_NOT_FOUND;
}

/**
  Abort any task on the AP and reset the AP to be in idle state.

  @param[in] ProcessorNumber - Processor index of an AP.
**/
VOID
ResetProcessorToIdleState (
  UINTN ProcessorNumber
  )
{
  CPU_DATA_BLOCK *CpuData;

  CpuData = &mMPSystemData->CpuData[ProcessorNumber];

  CpuData->Procedure = NULL;

  SendInterrupt (
    BROADCAST_MODE_SPECIFY_CPU,
    CpuData->ApicID,
    0,
    DELIVERY_MODE_INIT,
    TRIGGER_MODE_EDGE,
    TRUE
    );

  MicroSecondDelay (10 * STALL_ONE_MILLI_SECOND);

  SendInterrupt (
    BROADCAST_MODE_SPECIFY_CPU,
    CpuData->ApicID,
    (UINT32) RShiftU64 (mAcpiCpuData->WakeUpBuffer, 12),
    DELIVERY_MODE_SIPI,
    TRIGGER_MODE_EDGE,
    TRUE
    );

  MicroSecondDelay (200 * STALL_ONE_MICRO_SECOND);

  SendInterrupt (
    BROADCAST_MODE_SPECIFY_CPU,
    CpuData->ApicID,
    (UINT32) RShiftU64 (mAcpiCpuData->WakeUpBuffer, 12),
    DELIVERY_MODE_SIPI,
    TRIGGER_MODE_EDGE,
    TRUE
    );

  MicroSecondDelay (200 * STALL_ONE_MICRO_SECOND);

  //
  // Re-initialize states
  //

  CpuData->ProcedureLock = VacantFlag;
  CpuData->StateLock = VacantFlag;
  CpuData->State = CPU_STATE_IDLE;
}
