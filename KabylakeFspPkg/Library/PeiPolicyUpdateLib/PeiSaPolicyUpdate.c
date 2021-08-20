/** @file
  Do Platform Stage System Agent initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2020 Intel Corporation.

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

#include <SaPolicyCommon.h>
#include <Library/DebugLib.h>
#include <FspEas.h>
#include <Library/PeiSaPolicyLib.h>
#include <Library/FspCommonLib.h>
#include <Library/DebugLib.h>
#include <FspsUpd.h>

/**
  UpdatePeiSaPolicy performs SA PEI Policy initialization

  @param[in out] SiPolicyPpi       SI_POLICY PPI
  @param[in]     FspsUpd           The pointer of FspsUpd

  @retval EFI_SUCCESS              The policy is installed and initialized.
**/
EFI_STATUS
FspUpdatePeiSaPolicy (
  IN OUT SI_POLICY_PPI       *SiPolicyPpi,
  IN     FSPS_UPD            *FspsUpd
  )
{
  EFI_STATUS                    Status;
  SA_MISC_PEI_CONFIG            *MiscPeiConfig;
  GRAPHICS_PEI_CONFIG           *GtConfig;
  PCIE_PEI_CONFIG               *PciePeiConfig;
  SKYCAM_CONFIG                 *SkyCamPolicy;
  VTD_CONFIG                    *Vtd;
  GMM_CONFIG                    *GmmConfig;
  UINT8                         Index;

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "FSP UpdatePeiSaPolicy\n"));

  MiscPeiConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaMiscPeiConfigGuid, (VOID *)&MiscPeiConfig);
  ASSERT_EFI_ERROR (Status);

  GtConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGraphicsPeiConfigGuid, (VOID *)&GtConfig);
  ASSERT_EFI_ERROR (Status);

  SkyCamPolicy = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSkyCamConfigGuid, (VOID *)&SkyCamPolicy);
  ASSERT_EFI_ERROR (Status);

  Vtd = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gVtdConfigGuid, (VOID *)&Vtd);
  ASSERT_EFI_ERROR (Status);

  GmmConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGmmConfigGuid, (VOID *)&GmmConfig);
  ASSERT_EFI_ERROR (Status);

  PciePeiConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaPciePeiConfigGuid, (VOID *)&PciePeiConfig);
  ASSERT_EFI_ERROR (Status);

  if (MiscPeiConfig != NULL) {
    MiscPeiConfig->Device4Enable = FspsUpd->FspsConfig.Device4Enable;
    MiscPeiConfig->CridEnable = FspsUpd->FspsConfig.CridEnable;
    MiscPeiConfig->DefaultSvidSid.SubSystemVendorId = FspsUpd->FspsConfig.DefaultSvid;
    MiscPeiConfig->DefaultSvidSid.SubSystemId = FspsUpd->FspsConfig.DefaultSid;
    MiscPeiConfig->ChapDeviceEnable = FspsUpd->FspsTestConfig.ChapDeviceEnable;
    MiscPeiConfig->SkipPamLock = FspsUpd->FspsTestConfig.SkipPamLock;
    MiscPeiConfig->EdramTestMode = FspsUpd->FspsTestConfig.EdramTestMode;
  }

  if (PciePeiConfig != NULL) {
    PciePeiConfig->DmiAspm = FspsUpd->FspsConfig.DmiAspm;
    PciePeiConfig->DmiExtSync = FspsUpd->FspsTestConfig.DmiExtSync;
    PciePeiConfig->DmiIot = FspsUpd->FspsTestConfig.DmiIot;
    for (Index = 0; Index < SA_PEG_MAX_FUN; Index++) {
      PciePeiConfig->PegDeEmphasis[Index] = FspsUpd->FspsConfig.PegDeEmphasis[Index];
      PciePeiConfig->PegSlotPowerLimitValue[Index] = FspsUpd->FspsConfig.PegSlotPowerLimitValue[Index];
      PciePeiConfig->PegSlotPowerLimitScale[Index] = FspsUpd->FspsConfig.PegSlotPowerLimitScale[Index];
      PciePeiConfig->PegPhysicalSlotNumber[Index] = FspsUpd->FspsConfig.PegPhysicalSlotNumber[Index];
      PciePeiConfig->PegMaxPayload[Index] = FspsUpd->FspsTestConfig.PegMaxPayload[Index];
    }

  }

  if (GtConfig != NULL) {
    GtConfig->GraphicsConfigPtr = (VOID *) FspsUpd->FspsConfig.GraphicsConfigPtr;
    GtConfig->LogoPtr = (VOID *) FspsUpd->FspsConfig.LogoPtr;
    GtConfig->LogoSize = FspsUpd->FspsConfig.LogoSize;
    GtConfig->PavpEnable = FspsUpd->FspsConfig.PavpEnable;
    GtConfig->CdClock = FspsUpd->FspsConfig.CdClock;
    GtConfig->PeiGraphicsPeimInit = FspsUpd->FspsConfig.PeiGraphicsPeimInit;
    GtConfig->RenderStandby = FspsUpd->FspsTestConfig.RenderStandby;
    GtConfig->PmSupport = FspsUpd->FspsTestConfig.PmSupport;
    GtConfig->CdynmaxClampEnable = FspsUpd->FspsTestConfig.CdynmaxClampEnable;
    GtConfig->GtFreqMax = FspsUpd->FspsTestConfig.GtFreqMax;
    GtConfig->ProgramGtChickenBits = FspsUpd->FspsConfig.ProgramGtChickenBits;
    //
    // disable RC6 if GT PM is disabled
    //
    if (GtConfig->PmSupport == 0) {
      GtConfig->RenderStandby = 0;
    }
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "GtConfig->GraphicsConfigPtr from FSP UpdatePeiSaPolicy: 0x%x\n", GtConfig->GraphicsConfigPtr));
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "GtConfig->LogoPtr: 0x%x \n", GtConfig->LogoPtr ));
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "GtConfig->LogoSize: 0x%x \n", GtConfig->LogoSize));


  }

  if (SkyCamPolicy != NULL) {
    SkyCamPolicy->SaImguEnable = FspsUpd->FspsConfig.SaImguEnable;
  }
  if (Vtd != NULL) {
    Vtd->X2ApicOptOut = FspsUpd->FspsConfig.X2ApicOptOut;
    Vtd->BaseAddress[0] = FspsUpd->FspsConfig.VtdBaseAddress[0];
    Vtd->BaseAddress[1] = FspsUpd->FspsConfig.VtdBaseAddress[1];
    Vtd->VtdDisable = FspsUpd->FspsTestConfig.VtdDisable;
  }
  if (GmmConfig != NULL) {
    GmmConfig->GmmEnable = FspsUpd->FspsConfig.GmmEnable;
  }

  return EFI_SUCCESS;
}
