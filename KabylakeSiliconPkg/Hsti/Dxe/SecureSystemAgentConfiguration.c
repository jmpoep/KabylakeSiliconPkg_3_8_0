/** @file
  This file contains the tests for the SecureSystemAgentConfiguration bit

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
  Run tests for SecureSystemAgentConfiguration bit
**/
VOID
CheckSecureSystemAgentConfiguration (
  VOID
  )
{
  EFI_STATUS      Status;
  BOOLEAN         Result;
  UINT32          MchBar;
  UINTN           CpuNumber;
  UINTN           CpuIndex;
  UINT64          ConfigLock;
  CHAR16          *HstiErrorString;

  if ((mFeatureImplemented[0] & HSTI_BYTE0_SECURE_SYSTEM_AGENT_CONFIGURATION) == 0) {
    return;
  }

  Result = TRUE;
  MchBar = (UINT32)((UINT64)(MmioRead32 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_MC_DEV, SA_MC_FUN) + R_SA_MCHBAR)) & B_SA_MCHBAR_MCHBAR_MASK);

  DEBUG ((DEBUG_INFO, "  Table 3-2. Configuration Locking\n"));

  CpuNumber = GetCpuNumber ();
  for (CpuIndex = 0; CpuIndex < CpuNumber; CpuIndex++) {
    DEBUG ((DEBUG_INFO, "  [CPU - 0x%x]\n", CpuIndex));

    DEBUG ((DEBUG_INFO, "    1. ConfigLock\n"));

    ConfigLock = ProcessorReadMsr64 (CpuIndex, MSR_LT_LOCK_MEMORY);
    if ((ConfigLock & BIT0) == 0) {
      DEBUG ((DEBUG_INFO, "Fail: ConfigLock not set\n"));

      HstiErrorString = BuildHstiErrorString (
                          HSTI_BYTE0_SECURE_SYSTEM_AGENT_CONFIGURATION_ERROR_CODE_1,
                          HSTI_SYSTEM_AGENT_SECURITY_CONFIGURATION,
                          HSTI_BYTE0_SECURE_SYSTEM_AGENT_CONFIGURATION_ERROR_STRING_1
                          );
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

  DEBUG ((DEBUG_INFO, "    2. MC_LOCK\n"));

  if ((MmioRead32 (MchBar + R_SA_MCHBAR_MC_LOCK_OFFSET) & 0x87) != 0x87) {
    DEBUG ((DEBUG_INFO, "Fail: MC_LOCK not set\n"));

    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE0_SECURE_SYSTEM_AGENT_CONFIGURATION_ERROR_CODE_2,
                        HSTI_SYSTEM_AGENT_SECURITY_CONFIGURATION,
                        HSTI_BYTE0_SECURE_SYSTEM_AGENT_CONFIGURATION_ERROR_STRING_2
                        );
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    3. SA arbiter locks\n"));

  if (((MmioRead32 (MchBar + R_SA_MCHBAR_RESERVED_1_OFFSET) & BIT31) == 0) ||
      ((MmioRead32 (MchBar + R_SA_MCHBAR_RESERVED_2_OFFSET) & BIT0) == 0) ||
      ((MmioRead32 (MchBar + R_SA_MCHBAR_RESERVED_3_OFFSET) & BIT0) == 0) ||
      ((MmioRead32 (MchBar + R_SA_MCHBAR_RESERVED_0_OFFSET) & BIT31) == 0)) {

    DEBUG ((DEBUG_INFO, "Fail: SA arbiter locks not set\n"));
    DEBUG ((DEBUG_INFO, "SA arbiter R_SA_MCHBAR_RESERVED_1_OFFSET%x\n",MmioRead32 (MchBar + R_SA_MCHBAR_RESERVED_1_OFFSET)));
    DEBUG ((DEBUG_INFO, "SA arbiter R_SA_MCHBAR_RESERVED_2_OFFSET %x\n",MmioRead32 (MchBar + R_SA_MCHBAR_RESERVED_2_OFFSET)));
    DEBUG ((DEBUG_INFO, "SA arbiter R_SA_MCHBAR_RESERVED_3_OFFSET %x\n",MmioRead32 (MchBar + R_SA_MCHBAR_RESERVED_3_OFFSET)));
    DEBUG ((DEBUG_INFO, "SA arbiter R_SA_MCHBAR_RESERVED_0_OFFSET %x\n",MmioRead32 (MchBar + R_SA_MCHBAR_RESERVED_0_OFFSET)));


    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE0_SECURE_SYSTEM_AGENT_CONFIGURATION_ERROR_CODE_3,
                        HSTI_SYSTEM_AGENT_SECURITY_CONFIGURATION,
                        HSTI_BYTE0_SECURE_SYSTEM_AGENT_CONFIGURATION_ERROR_STRING_3
                        );
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    4. UMAGFXCTL\n"));

  if ((MmioRead32 (MchBar + R_SA_MCHBAR_UMAGFXCTL) & BIT0) == 0) {
    DEBUG ((DEBUG_INFO, "Fail: UMAGFXCTL not locked\n"));


    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE0_SECURE_SYSTEM_AGENT_CONFIGURATION_ERROR_CODE_4,
                        HSTI_SYSTEM_AGENT_SECURITY_CONFIGURATION,
                        HSTI_BYTE0_SECURE_SYSTEM_AGENT_CONFIGURATION_ERROR_STRING_4
                        );
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    5. VTDTRKLCK\n"));

  if ((MmioRead32 (MchBar + R_SA_MCHBAR_VTDTRKLCK) & BIT0) == 0) {
    DEBUG ((DEBUG_INFO, "Fail: VTDTRKLCK registers not locked\n"));

    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE0_SECURE_SYSTEM_AGENT_CONFIGURATION_ERROR_CODE_5,
                        HSTI_SYSTEM_AGENT_SECURITY_CONFIGURATION,
                        HSTI_BYTE0_SECURE_SYSTEM_AGENT_CONFIGURATION_ERROR_STRING_5
                        );
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  //
  // ALL PASS
  //
  if (Result) {
    Status = HstiLibSetFeaturesVerified (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               0,
               HSTI_BYTE0_SECURE_SYSTEM_AGENT_CONFIGURATION
               );
    ASSERT_EFI_ERROR (Status);
  }

  return;
}
