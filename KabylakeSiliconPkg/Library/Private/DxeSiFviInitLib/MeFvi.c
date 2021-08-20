/** @file
  ME Firmware Version Info implementation.

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
#include <PiDxe.h>
#include <Base.h>
#include <Uefi.h>
#include "MeFvi.h"
#include <Library/SiFviLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Library/HobLib.h>
#include <Protocol/MebxProtocol.h>
#include <MeBiosPayloadHob.h>

GLOBAL_REMOVE_IF_UNREFERENCED FVI_DATA mMeFviData[] = {
  DEFAULT_FVI_DATA (),
  DEFAULT_FVI_DATA (),
  FVI_VERSION (DEFAULT_FVI_VERSION),
};

GLOBAL_REMOVE_IF_UNREFERENCED FVI_HEADER mMeFviHeader = DEFAULT_FVI_HEADER_DATA (mMeFviData);

GLOBAL_REMOVE_IF_UNREFERENCED FVI_STRINGS mMeFviStrings[] = {
  DEFAULT_FVI_STRINGS (ME),
  DEFAULT_FVI_STRINGS (MEBX),
  {
    ME_FW_FVI_STRING,
    ME_FW_CONSUMER_SKU_STRING,
  },
};

/**
  This function populates the CPU FVI version numbers
**/
VOID
MeFviInit (
  IN UINT8 FviSmbiosType
  )
{
  EFI_STATUS                      Status;
  const UINT8                     StrCorporateSkuFw[sizeof (ME_FW_CORPORATE_SKU_STRING)] = ME_FW_CORPORATE_SKU_STRING;
  MEBX_PROTOCOL                   *MebxProtocol;
  ME_BIOS_PAYLOAD_HOB             *MbpHob;

  //
  // Get the MBP Data.
  //
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob == NULL) {
    DEBUG ((DEBUG_ERROR, "MbpGetMeFwInfo: No MBP Data Protocol available\n"));
    return;
  }

  ///
  /// Report ME components version information to FVI
  ///
  mMeFviHeader.SmbiosHeader.Type = FviSmbiosType;
  if (mMeFviHeader.SmbiosHeader.Type > 0x7f) {
    //
    // Default value of Silicon Init version
    //
    mMeFviData[EnumMeRc].Version.MajorVersion = (UINT8)  PcdGet8 (PcdSiliconInitVersionMajor);
    mMeFviData[EnumMeRc].Version.MinorVersion = (UINT8)  PcdGet8 (PcdSiliconInitVersionMinor);
    mMeFviData[EnumMeRc].Version.Revision     = (UINT8)  PcdGet8 (PcdSiliconInitVersionRevision);
    mMeFviData[EnumMeRc].Version.BuildNum     = (UINT16) PcdGet8 (PcdSiliconInitVersionBuild);

    mMeFviData[EnumMeFw].Version.MajorVersion = (UINT8)  MbpHob->MeBiosPayload.FwVersionName.MajorVersion;
    mMeFviData[EnumMeFw].Version.MinorVersion = (UINT8)  MbpHob->MeBiosPayload.FwVersionName.MinorVersion;
    mMeFviData[EnumMeFw].Version.Revision     = (UINT8)  MbpHob->MeBiosPayload.FwVersionName.HotfixVersion;
    mMeFviData[EnumMeFw].Version.BuildNum     = (UINT16) MbpHob->MeBiosPayload.FwVersionName.BuildVersion;
    if (MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType == IntelMeCorporateFw) {
      mMeFviStrings[EnumMeFw].VersionString = (CHAR8 *) &StrCorporateSkuFw;
    }

    Status = gBS->LocateProtocol (&gMebxProtocolGuid, NULL, (VOID **) &MebxProtocol);
    if (!EFI_ERROR (Status)) {
      mMeFviData[EnumMebx].Version.MajorVersion = (UINT8)  MebxProtocol->MebxVersion.Major;
      mMeFviData[EnumMebx].Version.MinorVersion = (UINT8)  MebxProtocol->MebxVersion.Minor;
      mMeFviData[EnumMebx].Version.Revision     = (UINT8)  MebxProtocol->MebxVersion.Hotfix;
      mMeFviData[EnumMebx].Version.BuildNum     = (UINT16) MebxProtocol->MebxVersion.Build;
    }

    Status = AddFviEntry (mMeFviHeader, mMeFviData, mMeFviStrings);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "AddFviEntry failed. Status = %r\n", Status));
    }
  }
}
