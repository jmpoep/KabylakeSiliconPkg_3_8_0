/** @file
  Framework PEIM to HECI.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2008 - 2016 Intel Corporation.

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

#include "HeciInit.h"

//
// Function Declarations
//
static HECI_PPI               mHeciPpi = {
  HeciSendwAckWithRetry,
  HeciReceiveWithRetry,
  HeciSendWithRetry,
  HeciInitialize,
  HeciGetMeStatus,
  HeciGetMeMode
};

static EFI_PEI_PPI_DESCRIPTOR mInstallHeciPpi = {
  EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gHeciPpiGuid,
  &mHeciPpi
};

//
// Function Implementations
//

/**
  Initialize MMIO BAR address for HECI devices

  @retval EFI_SUCCESS             HECI devices initialize succeefully
  @retval others                  Error occur
**/
EFI_STATUS
PeiHeciDevicesInit (
  VOID
  )
{
  SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi;
  EFI_STATUS           Status;
  ME_PEI_PREMEM_CONFIG *MePeiPreMemConfig;
  BOOLEAN              HeciCommunication2;

  ///
  /// Get Policy settings through the SiPreMemPolicy PPI
  ///
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  if (!EFI_ERROR (Status)) {
    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMePeiPreMemConfigGuid, (VOID *) &MePeiPreMemConfig);
    ASSERT_EFI_ERROR (Status);

    MeDeviceInit (HECI1, MePeiPreMemConfig->Heci1BarAddress, 0);
    MeDeviceInit (HECI2, MePeiPreMemConfig->Heci2BarAddress, 0);
    MeDeviceInit (HECI3, MePeiPreMemConfig->Heci3BarAddress, 0);

    ///
    /// Determine if ME devices should be Enabled/Disable and Program Subsystem IDs if Enabled
    /// Zero in Bit x enables the device
    ///
    HeciCommunication2 = MeHeci2Enabled ();

      DEBUG ((DEBUG_INFO, "HeciEnable\n"));
      HeciEnable ();

    if (HeciCommunication2) {
      DEBUG ((DEBUG_INFO, "Heci2Enable\n"));
      Heci2Enable ();
    } else {
      DEBUG ((DEBUG_INFO, "Heci2Disable\n"));
      Heci2Disable ();
    }

      DEBUG ((DEBUG_INFO, "Heci3Enable\n"));
      Heci3Enable ();
    if (MePeiPreMemConfig->KtDeviceEnable) {
      DEBUG ((DEBUG_INFO, "SolEnable\n"));
      SolEnable ();
    } else {
      DEBUG ((DEBUG_INFO, "SolDisable\n"));
      SolDisable ();
    }
    if (MePeiPreMemConfig->IderDeviceEnable) {
      DEBUG ((DEBUG_INFO, "IderEnable\n"));
      IderEnable ();
    } else {
      DEBUG ((DEBUG_INFO, "IderDisable\n"));
      IderDisable ();
    }
  }

  return Status;
}

/**
  Internal function performing Heci PPIs init needed in PEI phase

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_DEVICE_ERROR        ME FPT is bad
**/
EFI_STATUS
InstallHeciPpi (
  VOID
  )
{
  EFI_STATUS  Status;

  DEBUG((DEBUG_INFO, "ME-BIOS: HECI PPI Entry.\n"));
  PostCode (0xE03);

  ///
  /// Check for HECI device present and ME FPT Bad
  ///
  if ((MmioRead32 (MmPciBase (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER) + R_VENDORID) == 0x0) ||
      (MmioRead32 (MmPciBase (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER) + R_VENDORID) == 0xFFFFFFFF) ||
      (((MmioRead32 (MmPciBase (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER) + R_FWSTATE) & 0x0020) != 0) && !MeTypeIsSps())) {
    DEBUG((DEBUG_ERROR, "ME-BIOS: HECI PPI Exit - Error by HECI device error.\n"));
    PostCode (0xE83);
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Initialize Heci platform PPIs
  ///
  Status = HeciInitialize (HECI1_DEVICE);

  ///
  /// Heci Ppi should be installed always due to DID message might be required still.
  /// Unsupported messages requested will be blocked when utilize Heci Ppi
  ///
  Status = PeiServicesInstallPpi (&mInstallHeciPpi);

  if (!EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "ME-BIOS: HECI PPI Exit - Success.\n"));
    PostCode (0xE23);
  } else {
    DEBUG((DEBUG_ERROR, "ME-BIOS: HECI PPI Exit - Error by install HeciPpi fail, Status: %r\n", Status));
    ASSERT_EFI_ERROR (Status);
    PostCode (0xEA3);
  }

  return Status;
}

/**
  Internal function performing PM register initialization for Me
**/
VOID
MePmInit (
  VOID
  )
{
  UINT16  ABase;
  UINT16  Pm1Cnt;

  ///
  /// Before system memory initialization, BIOS should check the WAK_STS bit in PM1_STS[15] (PCH register ABASE+00h)
  /// to determine if Intel Management Engine has reset the system while the host was in a sleep state. If WAK_STS is
  /// not set, BIOS should ensure a non-sleep exit path is taken. One way to accomplish this is by overwriting
  /// PM1_CNT[12:10] (PCH register ABASE+04h) to 111b to force an S5 exit path by the BIOS.
  ///
  ABase = 0;
  PchAcpiBaseGet (&ABase);

  if (ABase != 0) {
    if ((IoRead16 (ABase + R_PCH_ACPI_PM1_STS) & B_PCH_ACPI_PM1_STS_WAK) == 0) {
      Pm1Cnt = IoRead16 (ABase + R_PCH_ACPI_PM1_CNT) | V_PCH_ACPI_PM1_CNT_S5;
      IoWrite16 (ABase + R_PCH_ACPI_PM1_CNT, Pm1Cnt);
      DEBUG ((DEBUG_INFO, "MePmInit () - Force an S5 exit path.\n"));
    }
  } else {
    DEBUG ((DEBUG_ERROR, "MePmInit () - Failed to get valid ABase.\n"));
    ASSERT (ABase != 0);
  }
}

