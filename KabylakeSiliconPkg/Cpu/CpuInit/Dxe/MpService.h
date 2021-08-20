/** @file
  Some definitions for MP services Protocol.

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

#ifndef _MP_SERVICE_H_
#define _MP_SERVICE_H_

#include <Protocol/MpService.h>

#include "MpCommon.h"

//
// Constant definitions
//
#define FOURGB                            0x100000000
#define ONEPAGE                           0x1000

#define RENDEZVOUS_PROC_LENGTH            0x1000
#define STACK_SIZE_PER_PROC               0x8000
#define MAX_CPU_S3_MTRR_ENTRY             0x0020
#define MAX_CPU_S3_TABLE_SIZE             0x0400

#define AP_HALT_CODE_SIZE                 10

#define CPU_CHECK_AP_INTERVAL             10     // multiply to microseconds for gBS->SetTimer in 100nsec.
#define CPU_WAIT_FOR_TASK_TO_BE_COMPLETED 100000 // microseconds
///
///  The MP data structure follows.
///
#define CPU_SWITCH_STATE_IDLE   0
#define CPU_SWITCH_STATE_STORED 1
#define CPU_SWITCH_STATE_LOADED 2

#define MSR_L3_CACHE_DISABLE    0x40

typedef struct {
  UINT8             Lock;         ///< offset 0
  UINT8             State;        ///< offset 1
  UINTN             StackPointer; ///< offset 4 / 8
  IA32_DESCRIPTOR   Gdtr;         ///< offset 8 / 16
  IA32_DESCRIPTOR   Idtr;         ///< offset 14 / 26
} CPU_EXCHANGE_ROLE_INFO;

//
// MTRR table definitions
//
typedef struct {
  UINT16 Index;
  UINT64 Value;
} MTRR_VALUES;

typedef enum {
  CPU_STATE_IDLE,
  CPU_STATE_BLOCKED,
  CPU_STATE_READY,
  CPU_STATE_BUSY,
  CPU_STATE_FINISHED,
  CPU_STATE_DISABLED
} CPU_STATE;

//
// Define CPU feature information
//
#define MAX_FEATURE_NUM 6
typedef struct {
  UINTN  Index;
  UINT32 ApicId;
  UINT32 Version;
  UINT32 FeatureDelta;
  UINT32 Features[MAX_FEATURE_NUM];
} LEAST_FEATURE_PROC;

///
/// Define Individual Processor Data block.
///
typedef struct {
  UINT32                    ApicID;
  volatile EFI_AP_PROCEDURE  Procedure;
  volatile VOID             *Parameter;
  volatile UINT8            StateLock;
  //
  // Padding in structure to make sure semaphores are in separate cache lines.
  // Cache lines are 64 bytes.
  //
  UINT8                     Padding[0x40-sizeof(UINT8)];
  volatile UINT8            ProcedureLock;
  UINT8                     Padding2[0x40-sizeof(UINT8)];
  UINT32                    Health;
  BOOLEAN                   SecondaryCpu;
  EFI_CPU_PHYSICAL_LOCATION PhysicalLocation;
  volatile CPU_STATE        State;
  UINT8                     Padding3[0x40-sizeof(CPU_STATE)];
  //
  // for PI MP Services Protocol
  //
  BOOLEAN                   *Finished;
  UINT64                    ExpectedTime;
  EFI_EVENT                 WaitEvent;
  EFI_EVENT                 CheckThisAPEvent;
  UINT64                    CurrentTime;
  UINT64                    TotalTime;
} CPU_DATA_BLOCK;

///
/// Define MP data block which consumes individual processor block.
///
typedef struct {
  UINT8                  ApSerializeLock;
  BOOLEAN                EnableSecondaryCpu;
  UINTN                  NumberOfCpus;
  UINTN                  TotalCpusForThisSystem;

  CPU_EXCHANGE_ROLE_INFO BSPInfo;
  CPU_EXCHANGE_ROLE_INFO APInfo;

  EFI_CPU_ARCH_PROTOCOL  *CpuArch;
  EFI_EVENT              CheckAllAPsEvent;
  EFI_EVENT              WaitEvent;
  UINTN                  BSP;
  BIST_HOB_DATA          *BistHobData;
  UINTN                  BistHobSize;

  UINTN                  FinishCount;
  UINTN                  StartCount;
  EFI_AP_PROCEDURE       Procedure;
  VOID                   *ProcArguments;
  BOOLEAN                SingleThread;
  UINTN                  StartedCpuNumber;

  CPU_DATA_BLOCK         CpuData[MAX_PROCESSOR_THREADS];
  CPU_STATE_CHANGE_CAUSE DisableCause[MAX_PROCESSOR_THREADS];

  CPU_PRIVATE_DATA       CpuPrivateData;
  MTRR_VALUES            S3BspMtrrTable[MAX_CPU_S3_MTRR_ENTRY];

  ///
  /// for PI MP Services Protocol
  ///
  BOOLEAN                CpuList[MAX_PROCESSOR_THREADS];
  UINTN                  **FailedCpuList;
  UINT64                 ExpectedTime;
  EFI_EVENT              CheckAPsEvent;
  UINT64                 CurrentTime;
  UINT64                 TotalTime;
} MP_SYSTEM_DATA;

typedef struct {
  ACPI_CPU_DATA        AcpiCpuData;
  MP_SYSTEM_DATA       MPSystemData;
  IA32_DESCRIPTOR      GdtrProfile;
  IA32_DESCRIPTOR      IdtrProfile;
} MP_CPU_RESERVED_DATA;

extern MP_SYSTEM_DATA              *mMPSystemData;
extern ACPI_CPU_DATA               *mAcpiCpuData;
extern EFI_MP_SERVICES_PROTOCOL    mMpService; // equals to EFI_MP_SERVICES_PROTOCOL
extern EFI_METRONOME_ARCH_PROTOCOL *mMetronome;

///
/// Prototypes.
///

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
  );

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
  );

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
  );

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
  );

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
  );


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
  );

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
  );

/**
  Initialize multiple processors and collect MP related data

  @retval EFI_SUCCESS           - Multiple processors get initialized and data collected successfully
  @retval Other                 - The operation failed due to some reason
**/
EFI_STATUS
InitializeMpSystemData (
  VOID
  );

/**
  Exchange 2 processors (BSP to AP or AP to BSP)

  @param[in] MyInfo      - CPU info for current processor
  @param[in] OthersInfo  - CPU info that will be exchanged with
**/
VOID
AsmExchangeRole (
  IN CPU_EXCHANGE_ROLE_INFO *MyInfo,
  IN CPU_EXCHANGE_ROLE_INFO *OthersInfo
  );

/**
  Switch current BSP processor to AP

  @param[in] MPSystemData  - Pointer to the data structure containing MP related data
**/
VOID
EFIAPI
FutureBspProc (
  IN MP_SYSTEM_DATA *MPSystemData
  );

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
  );

/**
  Initialize the state information for the MP DXE Protocol.
**/
VOID
EFIAPI
InitializeMpServices (
  VOID
  );

/**
  Copy Global MTRR data to S3
**/
VOID
SaveBspMtrrForS3 (
  VOID
  );

/**
  This function is called by all processors (both BSP and AP) once and collects MP related data

  @param[in] MPSystemData  - Pointer to the data structure containing MP related data
  @param[in] BSP           - TRUE if the CPU is BSP
  @param[in] BistParam     - BIST (build-in self test) data for the processor. This data
                             is only valid for processors that are waked up for the 1st
                             time in this CPU DXE driver.

  @retval EFI_SUCCESS   - Data for the processor collected and filled in
**/
EFI_STATUS
FillInProcessorInformation (
  IN MP_SYSTEM_DATA *MPSystemData,
  IN BOOLEAN        BSP,
  IN UINT32         BistParam
  );

/**
  Set APIC BSP bit

  @param[in] Enable  - enable as BSP or not

  @retval EFI_SUCCESS - always return success
**/
EFI_STATUS
SetApicBspBit (
  IN BOOLEAN Enable
  );

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
  );

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
  );

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
  );

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
  IN  UINTN   TimeoutInMicroSeconds,
  OUT UINT64  *CurrentTime
  );

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
  );

/**
  Get the next blocked processor

  @param[in] NextCpuNumber - that will be updated for next blocked CPU number

  @retval EFI_SUCCESS - The next blocked CPU found
  @retval EFI_NOT_FOUND - cannot find blocked CPU
**/
EFI_STATUS
GetNextBlockedCpuNumber (
  OUT UINTN *NextCpuNumber
  );

/**
  Procedure for detailed initialization of APs. It will be assigned to all APs while
  they are waken up for the second time.
**/
VOID
DetailedMpInitialization (
  VOID
  );

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
  );

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
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

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
  );

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
  );

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
  );

/**
  Abort any task on the AP and reset the AP to be in idle state.

  @param[in] ProcessorNumber - Processor index of an AP.
**/
VOID
ResetProcessorToIdleState (
  UINTN ProcessorNumber
  );

/**
  Checks APs status and updates APs status if needed.
**/
VOID
CheckAndUpdateApsStatus (
  VOID
  );
#endif
