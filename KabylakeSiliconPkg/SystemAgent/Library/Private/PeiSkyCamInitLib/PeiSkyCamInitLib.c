/** @file
  PEIM to initialize Sky Cam device

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2017 Intel Corporation.

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
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <SaAccess.h>
#include <PchAccess.h>
#include <Library/MmPciLib.h>
#include <Private/Library/PchRcLib.h>
#include <Private/Library/SkyCamInitLib.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>
#include <Private/SaConfigHob.h>
#include <IndustryStandard/Pci30.h>

/**
  SkyCamInit: Initialize the Sky Cam device

  @param[in] SKYCAM_CONFIG          SkyCamPolicy

**/
VOID
SkyCamInit (
  IN       SKYCAM_CONFIG                *SkyCamPolicy
  )
{
  UINT32          Reg32;
  BOOLEAN         ImguDisabled;
  UINT32          Cio2Enabled;
  SA_CONFIG_HOB   *SaConfigHob;

  Reg32 = MmioRead32 (MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN) + R_SA_MC_CAPID0_B);
  ImguDisabled = FALSE;
  //
  // Assume CIO2 is either not supported, fused off or disabled
  //
  Cio2Enabled = FALSE;

  if (Reg32 & BIT31) {
    DEBUG ((DEBUG_INFO, "IMGU Fused off\n"));
    ImguDisabled = TRUE;
  } else {
    //
    // IMGU is not fused off
    //
    if ((MmioRead16 (MmPciBase (SA_IMGU_BUS_NUM, SA_IMGU_DEV_NUM, SA_IMGU_FUN_NUM) + PCI_VENDOR_ID_OFFSET)) == 0xFFFF) {
      DEBUG ((DEBUG_ERROR, "IMGU config space not accessible!\n"));
      ImguDisabled = TRUE;
    }
    if (SkyCamPolicy->SaImguEnable == 1) {
      /*
        Configure IMGU basing on CIO2 mode. If CIO2 disabled by BIOS, recommend also disable SA IMGU
        Only check CIO2 mode when PCH PPI is available, otherwise skip checking CIO2
      */
      PchIsCio2Enabled (&Cio2Enabled);
      if (Cio2Enabled == FALSE) {
        DEBUG ((DEBUG_INFO, "CIO2 disabled so IMGU disabled too\n"));
        ImguDisabled = TRUE;
      }
    } else {
      //
      // Policy decides to disable IMGU
      //
      ImguDisabled = TRUE;
    }

    if (ImguDisabled) {
      //
      // If IMGU is not fused off it is enabled anyway so here BIOS has to disable it if required
      //
      DEBUG ((DEBUG_INFO, "Disable IMGU\n"));
      MmioAnd32 (MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN) + R_SA_DEVEN, (UINT32) ~BIT10);
    } else {
      //
      // Initialize IMGU registers
      //
      DEBUG ((DEBUG_INFO, "Enable IMGU\n"));
      MmioWrite8 (MmPciBase (SA_IMGU_BUS_NUM, SA_IMGU_DEV_NUM, SA_IMGU_FUN_NUM) + R_PCI_BCC_OFFSET, 0x04);
      MmioWrite8 (MmPciBase (SA_IMGU_BUS_NUM, SA_IMGU_DEV_NUM, SA_IMGU_FUN_NUM) + R_PCI_SCC_OFFSET, 0x80);
      MmioWrite8 (MmPciBase (SA_IMGU_BUS_NUM, SA_IMGU_DEV_NUM, SA_IMGU_FUN_NUM) + R_PCI_PI_OFFSET,  0x00);
    }
  }

  //
  // If CIO2 is not fused off or disabled, configure CIO2
  //
  if (Cio2Enabled == TRUE) {
    DEBUG ((DEBUG_INFO, "Configure CIO2\n"));
    PchConfigureCio2 ();
  }
  if (!ImguDisabled) {
    DEBUG ((DEBUG_INFO, "Set IMGU to support PCIe mode\n"));
    MmioAnd8 (MmPciBase (SA_IMGU_BUS_NUM, SA_IMGU_DEV_NUM, SA_IMGU_FUN_NUM) + 0x40, 0xFE);
  }

  //
  // Initialize specific policy into Hob for DXE phase use.
  //
  SaConfigHob = NULL;
  SaConfigHob = (SA_CONFIG_HOB *) GetFirstGuidHob (&gSaConfigHobGuid);
  if (SaConfigHob != NULL) {
    //
    // Update IMGU ACPI mode depending on IGFX present or not
    //
    if (ImguDisabled) {
      //
      // Set IMGU ACPI mode as Disabled
      //
      SaConfigHob->ImguAcpiMode = 0;
    } else if (MmioRead16 (MmPciBase (SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0)) != 0xFFFF) {
      //
      // Set IMGU ACPI mode as IGFX Child device
      //
      SaConfigHob->ImguAcpiMode = 1;
    } else {
      //
      // Set IMGU ACPI mode as ACPI device
      //
      SaConfigHob->ImguAcpiMode = 2;
    }
  }
}
