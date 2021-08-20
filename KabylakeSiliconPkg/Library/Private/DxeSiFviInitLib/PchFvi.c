/** @file
  PCH Firmware Version Info implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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
#include "PchFvi.h"


GLOBAL_REMOVE_IF_UNREFERENCED FVI_DATA mPchFviData[] = {
  DEFAULT_FVI_DATA (),
  FVI_VERSION (DEFAULT_FVI_VERSION),   // PCH CRID status
  FVI_VERSION (DEFAULT_FVI_VERSION),   // PCH CRID origin
  FVI_VERSION (DEFAULT_FVI_VERSION),   // PCH CRID new
  FVI_VERSION (DEFAULT_FVI_VERSION),   // RAID RC version
  FVI_VERSION (FVI_PCH_H_BX_HSIO_VERSION),
  FVI_VERSION (FVI_PCH_H_DX_HSIO_VERSION),
  FVI_VERSION (FVI_KBL_PCH_H_AX_HSIO_VERSION),
  FVI_VERSION (FVI_PCH_LP_BX_HSIO_VERSION),
  FVI_VERSION (FVI_PCH_LP_CX_HSIO_VERSION)
};

GLOBAL_REMOVE_IF_UNREFERENCED FVI_HEADER     mPchFviHeader = DEFAULT_FVI_HEADER_DATA (mPchFviData);

GLOBAL_REMOVE_IF_UNREFERENCED FVI_STRINGS mPchFviStrings[] = {
  DEFAULT_FVI_STRINGS (PCH),
  {
    PCH_CRID_STATUS_STRING,
    PCH_CRID_DISABLED,
  },
  { PCH_CRID_ORIGINAL_VALUE, NULL, },
  { PCH_CRID_NEW_VALUE, NULL, },
  { RAID_FVI_STRING, NULL, },
  { SKL_PCH_HBX_HSIO_STRING, NULL, },
  { SKL_PCH_HDX_HSIO_STRING, NULL, },
  { KBL_PCH_HAX_HSIO_STRING, NULL, },
  { SKL_PCH_LPBX_HSIO_STRING, NULL, },
  { SKL_PCH_LPCX_HSIO_STRING, NULL, }
};

/**
  Create and update PCH related FVI Records.

  @param[in] CridOrg                    Original Crid number
  @param[in] CridNew                    New Crid number
**/
VOID
CreateAndUpdateFviRecords (
  UINT16                                CridOrg,
  UINT16                                CridNew
  )
{
  STATIC CONST UINT8                        StrEnabled[sizeof (PCH_CRID_ENABLED) ]    = PCH_CRID_ENABLED;
  STATIC CONST UINT8                        StrDisabled[sizeof (PCH_CRID_DISABLED) ]  = PCH_CRID_DISABLED;
  BOOLEAN                                   FoundLegacyRaid;
  EFI_STATUS                                Status;
  UINTN                                     NumHandles;
  EFI_HANDLE                                *HandleBuffer;
  UINTN                                     Index;
  PCI_DATA_STRUCTURE                        *PcirBlockPtr;
  EFI_PCI_IO_PROTOCOL                       *PciIo;
  PCI_EXPANSION_ROM_HEADER                  *RomImage;
  EFI_COMPONENT_NAME2_PROTOCOL              *ComponentName2;
  CHAR16                                    RstDriverName1[] = L"Intel RST";
  CHAR16                                    RstDriverName2[] = L"Intel(R) RST";
  EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL *DriverEfiVersion;
  EFI_STRING                                DriverName;

  DEBUG ((DEBUG_INFO, "CreateAndUpdateFviRecords() Start\n"));

  mPchFviData[PCH_CRID_ORIGINAL].Version.BuildNum = CridOrg;
  if (CridOrg != CridNew) {
    mPchFviStrings[PCH_CRID_STATUS].VersionString = (CHAR8 *) &StrEnabled;
  } else {
    mPchFviStrings[PCH_CRID_STATUS].VersionString = (CHAR8 *) &StrDisabled;
  }
  mPchFviData[PCH_CRID_NEW].Version.BuildNum = CridNew;

  FoundLegacyRaid = FALSE;
  //
  // Get all PCI IO protocols
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &NumHandles,
                  &HandleBuffer
                  );
  if (!EFI_ERROR (Status)) {
    //
    // Find the RAID BIOS by checking each PCI IO handle for RST OPROM
    //
    for (Index = 0; Index < NumHandles; Index++) {
      Status = gBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gEfiPciIoProtocolGuid,
                      (VOID **) &PciIo
                      );
      if (EFI_ERROR (Status) || (PciIo->RomImage == NULL)) {
        //
        // If this PCI device doesn't have a ROM image, skip to the next device.
        //
        continue;
      }

      RomImage = PciIo->RomImage;

      //
      // Get pointer to PCIR structure
      //
      PcirBlockPtr = (PCI_DATA_STRUCTURE *) ((UINTN) RomImage + RomImage->PcirOffset);

      //
      // Check if we have an RAID BIOS OPROM.
      //
      if ((RomImage->Signature == 0xAA55) &&
          (PcirBlockPtr->ClassCode[0] == 0x00) &&
          (PcirBlockPtr->ClassCode[1] == 0x04) &&
          (PcirBlockPtr->ClassCode[2] == 0x01)
          ) {
        mPchFviData[RAID_VER].Version.MajorVersion = (UINT8) ((PcirBlockPtr->CodeRevision & 0xFF00) >> 8);
        mPchFviData[RAID_VER].Version.MinorVersion = (UINT8)  (PcirBlockPtr->CodeRevision & 0x00FF);
        mPchFviData[RAID_VER].Version.Revision     = 0;
        mPchFviData[RAID_VER].Version.BuildNum     = 0;
        FoundLegacyRaid = TRUE;
      }
    }
  }
  //
  // Search EFI RST OPROM
  //
  if (FoundLegacyRaid == FALSE) {
    Status = gBS->LocateHandleBuffer (
                    ByProtocol,
                    &gEfiDriverSupportedEfiVersionProtocolGuid,
                    NULL,
                    &NumHandles,
                    &HandleBuffer
                    );
    if (!EFI_ERROR (Status)) {
      for (Index = 0; Index < NumHandles; Index++) {
        Status = gBS->HandleProtocol (
                        HandleBuffer[Index],
                        &gEfiComponentName2ProtocolGuid,
                        (VOID **) &ComponentName2
                        );
        if (EFI_ERROR (Status)) {
          continue;
        }

        Status = ComponentName2->GetDriverName (ComponentName2, "en-US", &DriverName);
        if (EFI_ERROR (Status)) {
          continue;
        }

        if ((StrnCmp (DriverName, RstDriverName1, (sizeof (RstDriverName1) / sizeof (CHAR16)) - 1) == 0) ||
            (StrnCmp (DriverName, RstDriverName2, (sizeof (RstDriverName2) / sizeof (CHAR16)) - 1) == 0)) {
          Status = gBS->HandleProtocol (
                          HandleBuffer[Index],
                          &gEfiDriverSupportedEfiVersionProtocolGuid,
                          (VOID**)&DriverEfiVersion
                          );
          mPchFviData[RAID_VER].Version.MajorVersion = (UINT8) ((DriverEfiVersion->FirmwareVersion & 0x00FF0000) >> 16);
          mPchFviData[RAID_VER].Version.MinorVersion = (UINT8)  (DriverEfiVersion->FirmwareVersion & 0x000000FF);
          mPchFviData[RAID_VER].Version.Revision     = 0;
          mPchFviData[RAID_VER].Version.BuildNum     = 0;
        }
      }
    }
  }

  //
  // Create silicon FVI data HOB
  //
  if (mPchFviHeader.SmbiosHeader.Type > 0x7f) {
    Status = AddFviEntry (mPchFviHeader, mPchFviData, mPchFviStrings);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "AddFviEntry failed. Status = %r\n", Status));
    }
  }

  DEBUG ((DEBUG_INFO, "CreateAndUpdateFviRecords() End\n"));
}

VOID
PchFviInit (
  IN UINT8 FviSmbiosType
  )
{
  UINTN                           PciPmcRegBase;
  UINT8                           Data8;
  UINT8                           CridOrg;
  UINT8                           CridNew;
  EFI_PEI_HOB_POINTERS            HobPtr;
  PCH_CONFIG_HOB                  *PchConfigHob;

  mPchFviHeader.SmbiosHeader.Type = FviSmbiosType;
  ///
  /// PCH BIOS Spec Section 5.15 IntelR Stable Image Platform Program (SIPP)
  /// For platforms supporting Intel(R) SIPP, System BIOS will need to enable the CRID feature by:
  /// Write the value 1Dh to to the RevID field in PMC PCI Offset 08h
  ///
  //
  // Do Crid programming as late as possible so others can get the ture PCH stepping.
  //
  PciPmcRegBase   = MmPciBase (
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PCI_DEVICE_NUMBER_PCH_PMC,
                      PCI_FUNCTION_NUMBER_PCH_PMC
                      );
  CridOrg = MmioRead8 ((UINTN) (PciPmcRegBase + PCI_REVISION_ID_OFFSET));
  //
  // Get PCH Config HOB.
  //
  HobPtr.Guid   = GetFirstGuidHob (&gPchConfigHobGuid);
  ASSERT (HobPtr.Guid != NULL);
  PchConfigHob = (PCH_CONFIG_HOB *) GET_GUID_HOB_DATA (HobPtr.Guid);

  if (PchConfigHob->General.Crid == TRUE) {
    Data8 = 0x1D;
    MmioWrite8 ((UINTN) (PciPmcRegBase + PCI_REVISION_ID_OFFSET), Data8);
    S3BootScriptSaveMemWrite (
      S3BootScriptWidthUint8,
      (UINTN) (PciPmcRegBase + PCI_REVISION_ID_OFFSET),
      1,
      &Data8
      );
  }
  CridNew = MmioRead8 ((UINTN) (PciPmcRegBase + PCI_REVISION_ID_OFFSET));
  //
  // Default value of Silicon Init version
  //
  mPchFviData[RC_VER].Version.MajorVersion = (UINT8)  PcdGet8 (PcdSiliconInitVersionMajor);
  mPchFviData[RC_VER].Version.MinorVersion = (UINT8)  PcdGet8 (PcdSiliconInitVersionMinor);
  mPchFviData[RC_VER].Version.Revision     = (UINT8)  PcdGet8 (PcdSiliconInitVersionRevision);
  mPchFviData[RC_VER].Version.BuildNum     = (UINT16) PcdGet8 (PcdSiliconInitVersionBuild);
  //
  // Create and update CRID FVI record
  //
  CreateAndUpdateFviRecords ((UINT16) CridOrg, (UINT16) CridNew);

}
