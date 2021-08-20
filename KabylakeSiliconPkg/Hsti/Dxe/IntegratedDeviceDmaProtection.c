/** @file
  This file contains the tests for the IntegratedDeviceDMAProtection bit

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

#define B_VTD_MASK 0xFFFFFFFE

/**
  Run tests for IntegratedDeviceDMAProtection bit
**/
VOID
CheckIntegratedDeviceDmaProtection (
  VOID
  )
{
  EFI_STATUS      Status;
  BOOLEAN         Result;
  UINT32          MchBar;
  UINT32          Vtd1;
  UINT32          Vtd2;
  CHAR16          *HstiErrorString;

  if ((mFeatureImplemented[0] & HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION) == 0) {
    return;
  }

  Result = TRUE;
  MchBar = (UINT32)((UINT64)(MmioRead32 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_MC_DEV, SA_MC_FUN) + R_SA_MCHBAR)) & B_SA_MCHBAR_MCHBAR_MASK);

  DEBUG ((DEBUG_INFO, "  VTd check\n"));

  DEBUG ((DEBUG_INFO, "    1. VTd supported\n"));

  if ((MmioRead32 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH,SA_MC_DEV,SA_MC_FUN) + R_SA_MC_CAPID0_A_OFFSET) & BIT23) != 0) {
    DEBUG ((DEBUG_INFO, "Fail: VTd not supported\n"));


    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_ERROR_CODE_1,
                        HSTI_INTEGRATED_DEVICE_DMA_PROTECTION,
                        HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_ERROR_STRING_1
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

  if ((MmioRead32 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH,SA_MC_DEV,SA_MC_FUN) + R_SA_MC_CAPID0_A_OFFSET) & BIT23) == 0) {
    DEBUG ((DEBUG_INFO, "    2. VTd enabled\n"));

    if (MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH,2,0) + R_SA_IGD_VID) != 0xFFFF) {
      Vtd1 = MmioRead32 (MchBar + R_SA_MCHBAR_VTD1_OFFSET);
      if (((Vtd1 & BIT0) == 0) ||
          ((Vtd1 & B_VTD_MASK) == 0)) {
        DEBUG ((DEBUG_INFO, "Fail: VTd not enabled\n"));


        HstiErrorString = BuildHstiErrorString (
                            HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_ERROR_CODE_1,
                            HSTI_INTEGRATED_DEVICE_DMA_PROTECTION,
                            HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_ERROR_STRING_1
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

      if ((Vtd1 & B_VTD_MASK) != 0) {
        DEBUG ((DEBUG_INFO, "    3. VTd configured correctly\n"));

        if ((MmioRead32 ((Vtd1 & B_VTD_MASK) + 0xFF0) & BIT31) == 0) {
          DEBUG ((DEBUG_INFO, "Fail: VTd not configured correctly\n"));

          HstiErrorString = BuildHstiErrorString (
                              HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_ERROR_CODE_1,
                              HSTI_INTEGRATED_DEVICE_DMA_PROTECTION,
                              HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_ERROR_STRING_1
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
    }

    DEBUG ((DEBUG_INFO, "    2. VTd enabled\n"));

    Vtd2 = MmioRead32 (MchBar + R_SA_MCHBAR_VTD2_OFFSET);
    if (((Vtd2 & BIT0) == 0) ||
        ((Vtd2 & B_VTD_MASK) == 0)) {
      DEBUG ((DEBUG_INFO, "Fail: VTd2 not enabled\n"));

      HstiErrorString = BuildHstiErrorString (
                          HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_ERROR_CODE_1,
                          HSTI_INTEGRATED_DEVICE_DMA_PROTECTION,
                          HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_ERROR_STRING_1
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

    if ((Vtd2 & B_VTD_MASK) != 0) {
      DEBUG ((DEBUG_INFO, "    3. VTd configured correctly\n"));

      if ((MmioRead32 ((Vtd2 & B_VTD_MASK) + 0xFF0) & BIT31) == 0) {
        DEBUG ((DEBUG_INFO, "Fail: VTd2 not configured correctly\n"));

        HstiErrorString = BuildHstiErrorString (
                            HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_ERROR_CODE_1,
                            HSTI_INTEGRATED_DEVICE_DMA_PROTECTION,
                            HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_ERROR_STRING_1
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
  }

  //
  // ALL PASS
  //
  if (Result) {
    Status = HstiLibSetFeaturesVerified (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               0,
               HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION
               );
    ASSERT_EFI_ERROR (Status);
  }

  return;
}
