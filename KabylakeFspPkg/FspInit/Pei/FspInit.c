/** @file
  Source file for FSP Init PEI module

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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

#include "FspInit.h"
#include <Library/PcdLib.h>

/**
  FSP Init PEI module entry point

  @param[in]  FileHandle           Not used.
  @param[in]  PeiServices          General purpose services available to every PEIM.

  @retval     EFI_SUCCESS          The function completes successfully
  @retval     EFI_OUT_OF_RESOURCES Insufficient resources to create database
**/
EFI_STATUS
FspInitEntryPoint (
  IN       EFI_PEI_FILE_HANDLE    FileHandle,
  IN CONST EFI_PEI_SERVICES       **PeiServices
  )
{
  EFI_STATUS          Status;
  FSPS_UPD            *FspsUpd;
  SI_POLICY_PPI       *SiPolicyPpi;
  FSP_INFO_HEADER     *FspInfoHeader;

  Status = EFI_SUCCESS;
  FspsUpd = NULL;
  FspInfoHeader = GetFspInfoHeaderFromApiContext ();
  SetFspInfoHeader (FspInfoHeader);

  FspsUpd = (FSPS_UPD *)GetFspApiParameter ();
  if (FspsUpd == NULL) {
    //
    // Use the UpdRegion as default
    //
    FspsUpd = (FSPS_UPD *) (FspInfoHeader->ImageBase + FspInfoHeader->CfgRegionOffset);
  }
  SetFspUpdDataPointer(FspsUpd);
  SetFspSiliconInitUpdDataPointer (FspsUpd);

  DEBUG_CODE_BEGIN ();
    UINT32  Index;
    DEBUG ((DEBUG_INFO, "Dumping FSPS_UPD - Size: 0x%8X", sizeof(FSPS_UPD)));
    for (Index = 0; Index < sizeof (FSPS_UPD); ++Index) {
      if (Index % 0x10 == 0) {
        DEBUG ((DEBUG_INFO, "\n0x%8X:", Index));
      }
      DEBUG ((DEBUG_INFO, " 0x%02X", *(((UINT8 *)FspsUpd) + Index)));
    }
    DEBUG ((DEBUG_INFO, "\n"));
  DEBUG_CODE_END ();

  DEBUG ((DEBUG_INFO, "Updating UPDs consumed in FspSiliconInitApi...\n"));

  Status = SiCreateConfigBlocks (&SiPolicyPpi);
  ASSERT_EFI_ERROR (Status);
  FspUpdatePeiPchPolicy (
    SiPolicyPpi,
    FspsUpd
    );

  FspUpdatePeiCpuPolicy (SiPolicyPpi, FspsUpd);
  //
  // Update Security Policy before install CpuPolicyPpi
  //
  FspUpdatePeiSecurityPolicy(SiPolicyPpi, FspsUpd);

  FspUpdatePeiMePolicy (SiPolicyPpi, FspsUpd);
  FspUpdatePeiSaPolicy (SiPolicyPpi, FspsUpd);
  FspUpdatePeiAmtPolicy (SiPolicyPpi, FspsUpd);
  FspUpdatePeiSiPolicy (SiPolicyPpi, FspsUpd);

  //
  // If FSP UPD SkipMpInit is enabled, PcdCpuMaxLogicalProcessorNumber is to 1. When set to 1, driver CpuMpPei doesn't start APs.
  //

  if (FspsUpd->FspsConfig.CpuConfig.Bits.SkipMpInit) {
    PcdSet32(PcdCpuMaxLogicalProcessorNumber, 1);
  }

  //
  // Install SiPolicy to indicate execution as PostMem (Must be last step)
  //
  Status = SiInstallPolicyPpi (SiPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "SI PEI Policy Initialization Done in Post-Memory\n"));

  return Status;
}
