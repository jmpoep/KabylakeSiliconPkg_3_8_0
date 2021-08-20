/** @file
  Code which supports Software Guard Extensions DXE component

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

#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <MpService.h>
#include <Protocol/CpuGlobalNvsArea.h>
#include <Private/Library/SoftwareGuardLib.h>
#include <Private/Library/CpuCommonLib.h>

/**
 Code to update SGX Global NVS variable in EPC.ASL
**/
VOID
UpdateSgxNvs (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_CPUID_REGISTER            Cpuid;
  CPU_GLOBAL_NVS_AREA_PROTOCOL  *CpuGlobalNvsAreaProtocol;

  DEBUG ((DEBUG_INFO, "\n UpdateSgxNvs started \n"));

  ///
  /// Locate CPU Global NVS
  ///
  Status = gBS->LocateProtocol (&gCpuGlobalNvsAreaProtocolGuid, NULL, (VOID **) &CpuGlobalNvsAreaProtocol);
  if (Status != EFI_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "\n UpdateSgxNvs: Unable to Locate CPU global NVS Protocol, EPC device will not be available\n"));
    return;
  }

  CpuGlobalNvsAreaProtocol->Area->SgxStatus      = 0;
  CpuGlobalNvsAreaProtocol->Area->EpcBaseAddress = 0;
  CpuGlobalNvsAreaProtocol->Area->EpcLength      = 1;

  /**
    Check if all of these conditions are met
    - 1: EnableSgx policy was set to enable
    - 2: SGX feature is supported by CPU
    - 3: PRM was successfully allocated and PRMRRs were set
    - 4: SGX IA32_FEATURE_CONTROL MSR(3Ah) [18] == 1
  **/
  if (IsSgxSupported () && IsPrmrrAlreadySet () && IsSgxFeatureCtrlSet ()) {
    //
    // Check if SGX is present
    //
    if (!IsSgxPresent ()) {
      DEBUG ((DEBUG_WARN, "\n SGX is not present\n"));

    } else {
      //
      // Read CPUID_SGX_ENABLED.0x2 to get EPC Base and Size
      //
      AsmCpuidEx (CPUID_SGX_ENABLED, 0x2, &Cpuid.RegEax, &Cpuid.RegEbx, &Cpuid.RegEcx, &Cpuid.RegEdx);

      //
      // Check if the first sub-leaf is a valid EPC section
      //
      if ((Cpuid.RegEax & 0xF) != 0x1) {
        return;
      }
      DEBUG ((DEBUG_INFO, "\n SGX is ENABLED\n"));
      CpuGlobalNvsAreaProtocol->Area->EpcBaseAddress = LShiftU64 ((UINT64) (Cpuid.RegEbx & 0xFFFFF), 32) + (UINT64) (Cpuid.RegEax & 0xFFFFF000);
      CpuGlobalNvsAreaProtocol->Area->EpcLength      = LShiftU64 ((UINT64) (Cpuid.RegEdx & 0xFFFFF), 32) + (UINT64) (Cpuid.RegEcx & 0xFFFFF000);
      CpuGlobalNvsAreaProtocol->Area->SgxStatus      = TRUE;
    }
  } else {
    DEBUG ((DEBUG_WARN, "\n SGX is not supported\n"));
  }
  DEBUG ((DEBUG_INFO, "CpuGlobalNvsAreaProtocol->Area->SgxStatus      = 0x%X\n",      CpuGlobalNvsAreaProtocol->Area->SgxStatus));
  DEBUG ((DEBUG_INFO, "CpuGlobalNvsAreaProtocol->Area->EpcBaseAddress = 0x%016llX\n", CpuGlobalNvsAreaProtocol->Area->EpcBaseAddress));
  DEBUG ((DEBUG_INFO, "CpuGlobalNvsAreaProtocol->Area->EpcLength      = 0x%016llX\n", CpuGlobalNvsAreaProtocol->Area->EpcLength));
  return;
}
