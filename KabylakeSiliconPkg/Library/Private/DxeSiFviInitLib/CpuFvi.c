/** @file
  CPU Firmware Version Info implementation.

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

#include "CpuFvi.h"
#include <Library/HobLib.h>

extern EFI_GUID gBiosGuardHobGuid;

FVI_DATA mCpuFviData[] = {
  DEFAULT_FVI_DATA (),
  FVI_VERSION (DEFAULT_FVI_VERSION),   // uCode RC version
  FVI_VERSION (TXT_VERSION),           // TXT RC version
  FVI_VERSION (BIOSGUARD_VERSION),     // BIOS Guard RC version
};

FVI_HEADER mCpuFviHeader = DEFAULT_FVI_HEADER_DATA (mCpuFviData);

FVI_STRINGS mCpuFviStrings[] = {
  DEFAULT_FVI_STRINGS (CPU),
  { UCODE_FVI_STRING, NULL, },
  { TXT_FVI_STRING, NULL, },
  { BIOSGUARD_FVI_STRING, NULL, },
};

/**
  This function populates the CPU FVI version numbers
**/
VOID
CpuFviInit (
  IN UINT8 FviSmbiosType
  )
{
  EFI_STATUS                      Status;
  UINT32                          uCodeRevision;
  BIOSGUARD_HOB                   *BiosGuardHobPtr;

  //
  // Create SMBIOS Table type - FviSmbiosType
  //
  mCpuFviHeader.SmbiosHeader.Type = FviSmbiosType;
  if (mCpuFviHeader.SmbiosHeader.Type > 0x7f) {

    //
    // Default value of Silicon Init version
    //
    mCpuFviData[CPU_RC_VER].Version.MajorVersion = (UINT8)  PcdGet8 (PcdSiliconInitVersionMajor);
    mCpuFviData[CPU_RC_VER].Version.MinorVersion = (UINT8)  PcdGet8 (PcdSiliconInitVersionMinor);
    mCpuFviData[CPU_RC_VER].Version.Revision     = (UINT8)  PcdGet8 (PcdSiliconInitVersionRevision);
    mCpuFviData[CPU_RC_VER].Version.BuildNum     = (UINT16) PcdGet8 (PcdSiliconInitVersionBuild);

    ///
    /// uCode FVI Information
    ///
    uCodeRevision = GetCpuUcodeRevision ();
    mCpuFviData[UCODE_VER].Version.MajorVersion = (UINT8) ((uCodeRevision & 0xFF000000) >> 24);
    mCpuFviData[UCODE_VER].Version.MinorVersion = (UINT8) ((uCodeRevision & 0x00FF0000) >> 16);
    mCpuFviData[UCODE_VER].Version.Revision     = (UINT8) ((uCodeRevision & 0x0000FF00) >> 8);
    mCpuFviData[UCODE_VER].Version.BuildNum     = (UINT16) (uCodeRevision & 0x000000FF);

    ///
    /// TXT FVI Information
    ///
    mCpuFviData[TXT_VER].Version.MajorVersion   = 0x0;
    mCpuFviData[TXT_VER].Version.MinorVersion   = 0x5;
    mCpuFviData[TXT_VER].Version.Revision       = 0x0;
    mCpuFviData[TXT_VER].Version.BuildNum       = 0x0;

    ///
    /// BIOS Guard FVI Information
    ///
    BiosGuardHobPtr = GetFirstGuidHob (&gBiosGuardHobGuid);
    if (BiosGuardHobPtr == NULL) {
      DEBUG ((DEBUG_ERROR, "BIOS Guard HOB not available. FVI information was not updated.\n"));
    } else if (BiosGuardHobPtr->BiosGuardModulePtr == (EFI_PHYSICAL_ADDRESS) NULL) {
      DEBUG ((DEBUG_ERROR, "BIOS Guard module not available. FVI information was not updated.\n"));
    } else {
      mCpuFviData[BIOSGUARD_VER].Version.MajorVersion = *(UINT8 *)(BiosGuardHobPtr->BiosGuardModulePtr + BIOSGUARD_REVISION_ID_MAJOR_OFFSET);
      mCpuFviData[BIOSGUARD_VER].Version.MinorVersion = *(UINT8 *)(BiosGuardHobPtr->BiosGuardModulePtr + BIOSGUARD_REVISION_ID_MINOR_OFFSET);
      mCpuFviData[BIOSGUARD_VER].Version.Revision     = 0;
      mCpuFviData[BIOSGUARD_VER].Version.BuildNum     = *(UINT16 *)(BiosGuardHobPtr->BiosGuardModulePtr + BIOSGUARD_BUILD_NUMBER_OFFSET);;
    }

    ///
    /// Add CPU RC Firmware Version Info (FVI) Entry
    ///
    Status = AddFviEntry (mCpuFviHeader, mCpuFviData, mCpuFviStrings);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "AddFviEntry failed. Status = %r\n", Status));
    }
  }
}
