/** @file
  SA Firmware Version Info implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2017 Intel Corporation.

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
#include "SaFvi.h"
#include <Library/HobLib.h>
#include <Library/ConfigBlockLib.h>
#include <Private/SiConfigHob.h>

extern EFI_GUID gSaConfigHobGuid;

GLOBAL_REMOVE_IF_UNREFERENCED FVI_DATA mSaFviData[] = {
  DEFAULT_FVI_DATA (),
  FVI_VERSION (DEFAULT_FVI_VERSION),   // Memory RC version
  FVI_VERSION (DEFAULT_FVI_VERSION),   // PCIE RC version
  FVI_VERSION (DEFAULT_FVI_VERSION),   // SA CRID Status
  FVI_VERSION (DEFAULT_FVI_VERSION),   // SA CRID origin
  FVI_VERSION (DEFAULT_FVI_VERSION),   // SA CRID new
  FVI_VERSION (DEFAULT_FVI_VERSION),   // VBIOS RC version
};

GLOBAL_REMOVE_IF_UNREFERENCED FVI_HEADER    mSaFviHeader = DEFAULT_FVI_HEADER_DATA (mSaFviData);
GLOBAL_REMOVE_IF_UNREFERENCED SA_CONFIG_HOB *SaConfigHob;

GLOBAL_REMOVE_IF_UNREFERENCED FVI_STRINGS mSaFviStrings[] = {
  DEFAULT_FVI_STRINGS (SA),
  { MEM_FVI_STRING, NULL, },
  { PCIE_FVI_STRING, NULL, },
  {
    SA_CRID_STATUS,
    SA_CRID_DISABLED,
  },
  { SA_CRID_ORIGINAL_VALUE, NULL, },
  { SA_CRID_NEW_VALUE, NULL, },
  { VBIOS_FVI_STRING, NULL, },
};

/**
  This function populates the SA FVI version numbers
**/
VOID
SaFviInit (
  IN UINT8 FviSmbiosType
  )
{
  const UINT8               StrEnabled[sizeof (SA_CRID_ENABLED) ]    = SA_CRID_ENABLED;
  const UINT8               StrDisabled[sizeof (SA_CRID_DISABLED) ]  = SA_CRID_DISABLED;
  static const SiMrcVersion MemRcVersionConst = {0, 0, 0, 0};
  const SiMrcVersion        *MemRcVersion;
  MEMORY_INFO_DATA_HOB      *MemInfo;
  EFI_STATUS                Status;
  UINT16                    VbiosBuildNum;
  EFI_IA32_REGISTER_SET     RegSet;
  EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;
  UINTN                     McBaseAddress;
  UINT8                     Data8;
  UINT8                     CridOrg;
  UINT8                     CridNew;
  EFI_PEI_HOB_POINTERS      HobPtr;
  SI_CONFIG_HOB             *SiConfigHob;
  EFI_HOB_GUID_TYPE         *GuidHob;

  GuidHob = NULL;

  McBaseAddress = MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN);
  ///
  /// Save CRID_ORIGINAL value before SaSecurityInit() executes CRID function.
  ///
  CridOrg = MmioRead8(McBaseAddress + PCI_REVISION_ID_OFFSET);
  mSaFviData[CRID_ORIGINAL].Version.BuildNum = (UINT16) CridOrg;
  ///
  /// Get SaDataHob HOB
  ///
  SaConfigHob              = NULL;
  SaConfigHob              = (SA_CONFIG_HOB *) GetFirstGuidHob (&gSaConfigHobGuid);
  ///
  /// CRID configuration
  ///
  if (SaConfigHob->CridEnable == TRUE) {
    Data8 = CRID_DATA;
    MmioWrite8(McBaseAddress + PCI_REVISION_ID_OFFSET, Data8);
    S3BootScriptSaveMemWrite(
      S3BootScriptWidthUint8,
      (UINTN)(McBaseAddress + PCI_REVISION_ID_OFFSET),
      1,
      &Data8
      );
  }
  CridNew = MmioRead8((UINTN)(McBaseAddress + PCI_REVISION_ID_OFFSET));

  if (CridOrg != CridNew) {
    mSaFviStrings[CRID_STATUS].VersionString = (CHAR8 *)&StrEnabled;
  } else {
    mSaFviStrings[CRID_STATUS].VersionString = (CHAR8 *)&StrDisabled;
  }
  mSaFviData[CRID_NEW].Version.BuildNum = (UINT16) CridNew;
  mSaFviHeader.SmbiosHeader.Type = FviSmbiosType;
  if (mSaFviHeader.SmbiosHeader.Type > 0x7f) {
    MemInfo = NULL;

    //
    // Search for the Memory Configuration GUID HOB.  If it is not present, then
    // there's nothing we can do. It may not exist on the update path.
    //
    GuidHob = GetFirstGuidHob (&gSiMemoryInfoDataGuid);
    ASSERT (GuidHob != NULL);
    if (GuidHob == NULL) {
      return;
    }

    MemInfo = (MEMORY_INFO_DATA_HOB *) GET_GUID_HOB_DATA (GuidHob);
    if (MemInfo != NULL) {
      MemRcVersion = &MemInfo->Version;
    } else {
      MemRcVersion = &MemRcVersionConst;
    }

    mSaFviData[SA_RC_VER].Version.MajorVersion  = (UINT8)  PcdGet8 (PcdSiliconInitVersionMajor);
    mSaFviData[SA_RC_VER].Version.MinorVersion  = (UINT8)  PcdGet8 (PcdSiliconInitVersionMinor);
    mSaFviData[SA_RC_VER].Version.Revision      = (UINT8)  PcdGet8 (PcdSiliconInitVersionRevision);
    mSaFviData[SA_RC_VER].Version.BuildNum      = (UINT16) PcdGet8 (PcdSiliconInitVersionBuild);
    mSaFviData[PCIE_VER].Version.MajorVersion   = (UINT8)  PcdGet8 (PcdSiliconInitVersionMajor);
    mSaFviData[PCIE_VER].Version.MinorVersion   = (UINT8)  PcdGet8 (PcdSiliconInitVersionMinor);
    mSaFviData[PCIE_VER].Version.Revision       = (UINT8)  PcdGet8 (PcdSiliconInitVersionRevision);
    mSaFviData[PCIE_VER].Version.BuildNum       = (UINT16) PcdGet8 (PcdSiliconInitVersionBuild);
    mSaFviData[MEM_RC_VER].Version.MajorVersion = (UINT8)  MemRcVersion->Major;
    mSaFviData[MEM_RC_VER].Version.MinorVersion = (UINT8)  MemRcVersion->Minor;
    mSaFviData[MEM_RC_VER].Version.Revision     = (UINT8)  MemRcVersion->Rev;
    mSaFviData[MEM_RC_VER].Version.BuildNum     = (UINT16) MemRcVersion->Build;

    mSaFviData[CRID_NEW].Version.BuildNum = (UINT16) MmioRead8 (McBaseAddress + PCI_REVISION_ID_OFFSET);
    //
    // Check IGFX device
    //
    VbiosBuildNum = 0xFFFF;
    //
    // Get Silicon Config data HOB
    //
    HobPtr.Guid   = GetFirstGuidHob (&gSiConfigHobGuid);
    SiConfigHob = (SI_CONFIG_HOB *)GET_GUID_HOB_DATA (HobPtr.Guid);

    if (SiConfigHob->CsmFlag == 1) {
      Status = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, (VOID **) &LegacyBios);
      if (Status == EFI_SUCCESS) {
        RegSet.X.AX   = 0x5f01;
        Status        = LegacyBios->Int86 (LegacyBios, 0x15, &RegSet);
        VbiosBuildNum = (((RegSet.X.DX & 0x0F00) << 4) | ((RegSet.X.DX & 0x000F) << 8) | ((RegSet.X.BX & 0x0F00) >> 4) | (RegSet.X.BX & 0x000F));
      }
    }
    mSaFviData[VBIOS_VER].Version.BuildNum = VbiosBuildNum;

    Status = AddFviEntry (mSaFviHeader, mSaFviData, mSaFviStrings);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "AddFviEntry failed. Status = %r\n", Status));
    }
  }
}
