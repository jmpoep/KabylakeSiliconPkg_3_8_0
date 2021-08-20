/** @file
  Header file for Cpu Init Lib Pei Phase

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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
#ifndef _CPU_S3_LIB_H_
#define _CPU_S3_LIB_H_

#include <Library/SynchronizationLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/TimerLib.h>
#include <Library/HobLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Ppi/SmmAccess.h>
#include <Ppi/MasterBootMode.h>
#include <Ppi/EndOfPeiPhase.h>
#include <Ppi/MpServices.h>
#include <Ppi/SiPolicy.h>
#include <Private/Library/CpuCommonLib.h>
#include "CpuAccess.h"

#define MICROSECOND         10

extern UINTN FixedMtrrNumber;
extern UINTN MtrrDefTypeNumber;

typedef struct {
  UINT16 Index;
  UINT64 Value;
} MTRR_VALUES;

/**
  Cpu initialization called during S3 resume to take care
  of CPU related activities in PEI phase.

  @param[in] PeiServices   - Indirect reference to the PEI Services Table.
  @param[in] SiPolicyPpi   - The SI Policy PPI instance

  @retval EFI_SUCCESS   - Multiple processors are intialized successfully.
  @retval EFI_NOT_FOUND - Unable to find AcpiCpuData.
**/
EFI_STATUS
S3InitializeCpu (
  IN CONST EFI_PEI_SERVICES    **PeiServices,
  IN       SI_POLICY_PPI       *SiPolicyPpi
  );

/**
  Read MTRR settings

  @param[in] MtrrValues  - buffer to store MTRR settings
**/
VOID
ReadMtrrRegisters (
  UINT64              *MtrrValues
  );

/**
  Syncup MTRR settings between all processors

  @param[in] Buffer  - buffer to store MTRR settings
**/
VOID
MpMtrrSynchUp (
  IN VOID  *Buffer
  );

/**
  Set MTRR registers

  @param[in] Buffer   - buffer with MTRR settings
**/
VOID
SetMtrrRegisters (
  IN VOID  *Buffer
  );

/**
  Print MTRR settings in debug build BIOS

  @param[in] MtrrArray   - buffer with MTRR settings
**/
VOID
ShowMtrrRegisters (
  IN MTRR_VALUES  *MtrrArray
  );

/**
  This will check if the microcode address is valid for this processor, and if so, it will
  load it to the processor.

  @param[in]  MicrocodeAddress - The address of the microcode update binary (in memory).
  @param[out] FailedRevision   - The microcode revision that fails to be loaded.

  @retval EFI_SUCCESS           - A new microcode update is loaded.
  @retval Other                 - Due to some reason, no new microcode update is loaded.
**/
EFI_STATUS
S3InitializeMicrocode (
  IN  CPU_MICROCODE_HEADER *MicrocodeAddress,
  OUT UINT32               *FailedRevision
  );

#endif
