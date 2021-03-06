/** @file
  Source code file for Silicon Init Pre Memory module.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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
#include "SiInitPreMem.h"
#include <Library/PerformanceLib.h>


/**
  Slicon Initializes after Policy PPI produced, All required polices must be installed before the callback

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  The memory discovered PPI.  Not used.

  @retval EFI_SUCCESS             Succeeds.
**/
EFI_STATUS
EFIAPI
SiInitPreMemOnPolicy (
  IN  EFI_PEI_SERVICES             **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN  VOID                         *Ppi
  );

static EFI_PEI_NOTIFY_DESCRIPTOR  mSiInitNotifyList[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gSiPreMemPolicyPpiGuid,
    SiInitPreMemOnPolicy
  }
};

/**
  Slicon Initializes after Policy PPI produced, All required polices must be installed before the callback

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  The memory discovered PPI.  Not used.

  @retval EFI_SUCCESS             Succeeds.
**/
EFI_STATUS
EFIAPI
SiInitPreMemOnPolicy (
  IN  EFI_PEI_SERVICES             **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN  VOID                         *Ppi
  )
{
  EFI_STATUS              Status;
  SI_POLICY_PPI           *SiPolicyPpi;
  SI_PREMEM_POLICY_PPI    *SiPreMemPolicyPpi;

  DEBUG ((DEBUG_INFO, "SiInitPreMemOnPolicy() Start\n"));

  SiPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **)&SiPolicyPpi
             );
  //
  // Prevent from potential execution in PostMem phase
  //
  if (Status == EFI_SUCCESS) {
    return EFI_SUCCESS;
  }

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **)&SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

#ifndef MDEPKG_NDEBUG

  //
  // Validate PCH policies
  //
  PERF_START_EX (&gPerfPchValidateGuid, NULL, NULL, AsmReadTsc (), 0x5010);
  PchValidatePolicy (SiPreMemPolicyPpi);
  PERF_END_EX (&gPerfPchValidateGuid, NULL, NULL, AsmReadTsc (), 0x5011);

  //
  // Validate CPU policies
  //
  PERF_START_EX (&gPerfCpuValidateGuid, NULL, NULL, AsmReadTsc(), 0x5030);
  CpuValidatePolicy (SiPreMemPolicyPpi);
  PERF_END_EX (&gPerfCpuValidateGuid, NULL, NULL, AsmReadTsc(), 0x5031);

  //
  // Validate ME policies
  //
  PERF_START_EX (&gPerfMeValidateGuid, NULL, NULL, AsmReadTsc (), 0x5040);
  MeValidatePolicy (SiPreMemPolicyPpi);
  PERF_END_EX (&gPerfMeValidateGuid, NULL, NULL, AsmReadTsc (), 0x5041);

  //
  // Validate SA policies
  //
  PERF_START_EX (&gPerfSaValidateGuid, NULL, NULL, AsmReadTsc (), 0x5050);
  SaValidatePolicy (SiPreMemPolicyPpi);
  PERF_END_EX (&gPerfSaValidateGuid, NULL, NULL, AsmReadTsc (), 0x5051);

#endif // MDEPKG_NDEBUG

  //
  // Initialize ME after Policy PPI produced
  //
  PERF_START_EX (&gPerfHeciPreMemGuid, NULL, NULL, AsmReadTsc (), 0x5060);
  Status = PeiHeciDevicesInit ();
  if (!EFI_ERROR (Status)) {
    //
    // Install HECI PPI
    // PCH needs to get CRC from HECI message. So it must be ready
    // before Policy callback function of PCH.
    //
    Status = InstallHeciPpi ();
    ASSERT (Status == EFI_SUCCESS);
  }
  PERF_END_EX (&gPerfHeciPreMemGuid, NULL, NULL, AsmReadTsc (), 0x5061);

  //
  // Initialize PCH after Policy PPI produced
  //
  PERF_START_EX (&gPerfPchPreMemGuid, NULL, NULL, AsmReadTsc (), 0x5070);
  PchOnPolicyInstalled (SiPreMemPolicyPpi);
  PERF_END_EX (&gPerfPchPreMemGuid, NULL, NULL, AsmReadTsc (), 0x5071);

  //
  // Initialize CPU after Policy PPI produced
  //
  PERF_START_EX (&gPerfCpuPreMemGuid, NULL, NULL, AsmReadTsc(), 0x5080);
  CpuOnPolicyInstalled (SiPreMemPolicyPpi);
  PERF_END_EX (&gPerfCpuPreMemGuid, NULL, NULL, AsmReadTsc(), 0x5081);

  //
  // Initialize ME after Policy PPI produced
  //
  PERF_START_EX (&gPerfMePreMemGuid, NULL, NULL, AsmReadTsc (), 0x5090);
  MeOnPolicyInstalled ();
  PERF_END_EX (&gPerfMePreMemGuid, NULL, NULL, AsmReadTsc (), 0x5091);

  //
  // Initialize SA after Policy PPI produced
  //
  PERF_START_EX (&gPerfSaPreMemGuid, NULL, NULL, AsmReadTsc (), 0x50B0);
  SaOnPolicyInstalled ();
  PERF_END_EX (&gPerfSaPreMemGuid, NULL, NULL, AsmReadTsc (), 0x50B1);

  //
  // Initialize EvLoader after EfiPeiReadOnlyVariable2Ppi is ready.
  //
  PERF_START_EX (&gPerfEvlGuid, NULL, NULL, AsmReadTsc (), 0x50C0);
  InstallEvLoader ();
  PERF_END_EX (&gPerfEvlGuid, NULL, NULL, AsmReadTsc (), 0x50C1);

  //
  // Register MRC initialization callback when gEfiPeiMasterBootModePpiGuid is installed.
  //
  PERF_START_EX (&gPerfMemGuid, NULL, NULL, AsmReadTsc (), 0x50D0);
  InstallMrcCallback ();
  PERF_END_EX (&gPerfMemGuid, NULL, NULL, AsmReadTsc (), 0x50D1);

  DEBUG ((DEBUG_INFO, "SiInitPreMemOnPolicy() - End\n"));
  return EFI_SUCCESS;
}

/**
  Silicon Initializes before Policy PPI produced

  @param[in] FileHandle           The file handle of the file, Not used.
  @param[in] PeiServices          General purpose services available to every PEIM.

  @retval EFI_SUCCESS             The function completes successfully
**/
EFI_STATUS
EFIAPI
SiInitPrePolicy (
  IN  EFI_PEI_FILE_HANDLE      FileHandle,
  IN CONST EFI_PEI_SERVICES  **PeiServices
  )
{
  EFI_STATUS                            Status;

  DEBUG ((DEBUG_INFO, "SiInitPrePolicy() Start\n"));

  //
  // Initializes PCH before Policy initialized
  //
  PERF_START_EX (&gPerfPchPrePolicyGuid, NULL, NULL, AsmReadTsc (), 0x50F0);
  PchInitPrePolicy ();
  PERF_END_EX (&gPerfPchPrePolicyGuid, NULL, NULL, AsmReadTsc (), 0x50F1);

  //
  // Register Silicon init call back after PlatformPolicy PPI produced
  //
  Status = PeiServicesNotifyPpi (mSiInitNotifyList);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "SiInitPrePolicy() - End\n"));
  return EFI_SUCCESS;
}
