/** @file
  This file contains the tests for the HardwareRootedBootIntegrity bit

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 Intel Corporation.

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

#include "HstiSiliconDxe.h"

/**
  Run tests for HardwareRootedBootIntegrity bit
**/
VOID
CheckHardwareRootedBootIntegrity (
  VOID
  )
{
  EFI_STATUS      Status;
  BOOLEAN         Result;
  UINTN           CpuNumber;
  UINTN           CpuIndex;
  UINT64          SAcmInfo;
  CHAR16          *HstiErrorString;

  HstiErrorString = NULL;

  if ((mFeatureImplemented[0] & HSTI_BYTE0_HARDWARE_ROOTED_BOOT_INTEGRITY) == 0) {
    return;
  }

  Result = TRUE;

  DEBUG ((DEBUG_INFO, "  Boot Guard check\n"));

  CpuNumber = GetCpuNumber ();
  for (CpuIndex = 0; CpuIndex < CpuNumber; CpuIndex++) {
    DEBUG ((DEBUG_INFO, "  [CPU - 0x%x]\n", CpuIndex));
    DEBUG ((DEBUG_INFO, "    1. SACM INFO - Boot Guard Capability\n"));

    SAcmInfo = ProcessorReadMsr64 (CpuIndex, MSR_BOOT_GUARD_SACM_INFO);
    if ((SAcmInfo & B_BOOT_GUARD_SACM_INFO_CAPABILITY) == 0) {
      DEBUG ((DEBUG_INFO, "Boot Guard Capability Failed: Bootguard Disabled\n"));

      HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_HARDWARE_ROOTED_BOOT_INTEGRITY_ERROR_CODE_2, HSTI_BOOTGUARD_CONFIGURATION, HSTI_BYTE0_HARDWARE_ROOTED_BOOT_INTEGRITY_ERROR_STRING_2);
      Status = HstiLibAppendErrorString (
                 PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                 NULL,
                 HstiErrorString
                 );
      ASSERT_EFI_ERROR (Status);
      Result = FALSE;
      FreePool (HstiErrorString);
    }

    if ((SAcmInfo & B_BOOT_GUARD_SACM_INFO_CAPABILITY) != 0) {
      DEBUG ((DEBUG_INFO, "    2. SACM INFO - Boot Guard Verified Boot\n"));
      if ((SAcmInfo & B_BOOT_GUARD_SACM_INFO_VERIFIED_BOOT) == 0) {
        DEBUG ((DEBUG_INFO, "Boot Guard Capability Failed: Verified boot not enabled\n"));

        HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_HARDWARE_ROOTED_BOOT_INTEGRITY_ERROR_CODE_1, HSTI_BOOTGUARD_CONFIGURATION, HSTI_BYTE0_HARDWARE_ROOTED_BOOT_INTEGRITY_ERROR_STRING_1);
        Status = HstiLibAppendErrorString (
                   PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                   NULL,
                   HstiErrorString
                   );
        ASSERT_EFI_ERROR (Status);
        Result = FALSE;
        FreePool (HstiErrorString);
      }
    }
  }

  //
  // ALL PASS
  //
  if (Result) {
    Status = HstiLibSetFeaturesVerified (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               0,
               HSTI_BYTE0_HARDWARE_ROOTED_BOOT_INTEGRITY
               );
    ASSERT_EFI_ERROR (Status);
  }

  return;
}
