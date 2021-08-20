/** @file
  This files contains Pch CIO2 services for RCs usage

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 Intel Corporation.

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

#include "PchRcLibrary.h"

/**
  Check if CIO2 device is enabled

  @param[inout] Cio2Enabled             TRUE - CIO2 device enabled
                                        FALSE - CIO2 device disabled

  @retval EFI_SUCCESS                   The function completed successfully.
**/
EFI_STATUS
EFIAPI
PchIsCio2Enabled (
  IN OUT  UINT32                        *Cio2Enabled
  )
{
  UINTN  BaseAddress;

  DEBUG ((DEBUG_INFO, "PchIsCio2Enabled() - Start\n"));

  BaseAddress = MmPciBase (
                  DEFAULT_PCI_BUS_NUMBER_PCH,
                  PCI_DEVICE_NUMBER_PCH_CIO2,
                  PCI_FUNCTION_NUMBER_PCH_CIO2
                  );

  // check if CIO2 is enabled
  if (MmioRead16 (BaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    *Cio2Enabled = FALSE;
    DEBUG ((DEBUG_INFO, "PchIsCio2Enabled() - FALSE\n"));
  } else {
    *Cio2Enabled = TRUE;
    DEBUG ((DEBUG_INFO, "PchIsCio2Enabled() - TRUE\n"));
  }

  DEBUG ((DEBUG_INFO, "PchIsCio2Enabled() - End\n"));
  return EFI_SUCCESS;
}

/**
  Configure CIO2 device

  @retval EFI_SUCCESS                   The function completed successfully.
**/
EFI_STATUS
EFIAPI
PchConfigureCio2 (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "PchConfigureCio2() - Start\n"));

  //
  // clear HID_DEV bit in HDEVCtrl private register for Camera Pipe Host Controller IP (MSG IOSF-SB Port 0xA1)
  //
  PchPcrAndThenOr32 (
    PID_CAM_CHC,
    R_PCH_PCR_CAM_CHC_HDEVC,
    (UINT32) (~BIT0),
    0
    );

  DEBUG ((DEBUG_INFO, "PchConfigureCio2() - End\n"));

  return EFI_SUCCESS;
}

