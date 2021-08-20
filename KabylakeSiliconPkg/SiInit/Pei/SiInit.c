/** @file
    Source code file for Silicon Init Post Memory module.

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

#include "SiInit.h"
#include <Library/PerformanceLib.h>

EFI_PEI_PPI_DESCRIPTOR mEndOfSiInit = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI |EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEndOfSiInitPpiGuid,
  NULL
};

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_NOTIFY_DESCRIPTOR  mSiInitNotifyList[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiEndOfPeiSignalPpiGuid,
    SiInitOnEndOfPei
  }
};

static EFI_PEI_NOTIFY_DESCRIPTOR  mSiInitPostMemNotifyList[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gSiPolicyPpiGuid,
    SiInitPostMemOnPolicy
  }
};

/**
  Silicon Init End of PEI callback function. This is the last change before entering DXE and OS when S3 resume.

  @param[in] PeiServices   - Pointer to PEI Services Table.
  @param[in] NotifyDesc    - Pointer to the descriptor for the Notification event that
                             caused this function to execute.
  @param[in] Ppi           - Pointer to the PPI data associated with this function.

  @retval EFI_STATUS       - Always return EFI_SUCCESS
**/
EFI_STATUS
SiInitOnEndOfPei (
  IN EFI_PEI_SERVICES                   **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR          *NotifyDesc,
  IN VOID                               *Ppi
  )
{
  EFI_BOOT_MODE BootMode;
  PeiServicesGetBootMode(&BootMode);
  DEBUG ((DEBUG_INFO, "SiInitOnEndOfPei - Start\n"));

  //
  // Initializes PCH after End of Pei
  //
  PchOnEndOfPei ();

  MeOnEndOfPei ();
  SaOnEndOfPei ();

  S3TxtScheck ();

  if (BootMode != BOOT_ON_S3_RESUME) {
    InitializeSmbiosCpuHobs ();
  }
  DEBUG ((DEBUG_INFO, "SiInitOnEndOfPei - End\n"));
  return EFI_SUCCESS;
}

/**
  Slicon Initializes after PostMem phase Policy PPI produced,
  All required polices must be installed before the callback

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  SiPolicy PPI.

  @retval EFI_SUCCESS             Succeeds.
  @retval EFI_UNSUPPORTED         The function failed to locate SiPolicy
**/
EFI_STATUS
EFIAPI
SiInitPostMemOnPolicy (
  IN  EFI_PEI_SERVICES             **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN  VOID                         *Ppi
  )
{
  SI_POLICY_PPI             *SiPolicy;
  VOID                      *HobPtr;
  EFI_STATUS                Status;
  CPU_CONFIG                *CpuConfig;
  SI_CONFIG                 *SiConfig;

  DEBUG ((DEBUG_INFO, "SiInit () - Start\n"));
  SiPolicy = (SI_POLICY_PPI*) Ppi;

  Status = GetConfigBlock((VOID *)SiPolicy, &gCpuConfigGuid, (VOID *)&CpuConfig);
  ASSERT_EFI_ERROR(Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSiConfigGuid, (VOID *) &SiConfig);
  ASSERT_EFI_ERROR(Status);

  HobPtr = BuildGuidDataHob (&gSiConfigHobGuid, SiConfig, sizeof (SI_CONFIG));
  ASSERT (HobPtr != 0);

  //
  // Initializes PCH after memory services initialized
  //
  PERF_START_EX (&gPerfPchPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4020);
  PchInit (SiPolicy);
  PERF_END_EX (&gPerfPchPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4021);

  //
  // SA Post Mem initialization
  //
  PERF_START_EX (&gPerfSaPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4030);
  SaInit ();
  PERF_END_EX (&gPerfSaPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4031);

  //
  // SA Security Lock down after all initialization done
  //
  PERF_START_EX (&gPerfSaSecLockPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4050);
  SaSecurityLock ();
  PERF_END_EX (&gPerfSaSecLockPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4051);

  //
  // Initialize processor features, performance and power management features,
  // BIOS GUARD, and overclocking etc features before RESET_CPL at post-memory phase.
  //
  PERF_START_EX (&gPerfCpuPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4080);
  CpuInit ((CONST EFI_PEI_SERVICES **) PeiServices, SiPolicy);
  PERF_END_EX (&gPerfCpuPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4081);

  //
  // Restore Cpu settings only during S3 resume
  //
  if (CpuConfig->SkipMpInit == 0) {
    PERF_START_EX(&gPerfS3CpuInitPostMemGuid, NULL, NULL, AsmReadTsc(), 0x4040);
    S3InitializeCpu ((CONST EFI_PEI_SERVICES **) PeiServices, SiPolicy);
    PERF_END_EX (&gPerfS3CpuInitPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4041);
  }

  //
  // Set BIOS_RESET_CPL to indicate BIOS initialization completed
  //
  PERF_START_EX (&gPerfSaResetPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4090);
  SaResetComplete ();
  PERF_END_EX (&gPerfSaResetPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4091);

  //
  // Initialize power management after RESET_CPL at post-memory phase.
  //
  if (CpuConfig->SkipMpInit == 0) {
    PERF_START_EX (&gPerfCpuPowerMgmtGuid, NULL, NULL, AsmReadTsc (), 0x40A0);
    CpuPowerMgmtInit ((CONST EFI_PEI_SERVICES **) PeiServices);
    PERF_END_EX (&gPerfCpuPowerMgmtGuid, NULL, NULL, AsmReadTsc (), 0x40A1);
  }

  //
  // Perform ME post mem init
  //
  PERF_START_EX (&gPerfMePostMemGuid, NULL, NULL, AsmReadTsc (), 0x40B0);
  MePostMemInit ();
  PERF_END_EX (&gPerfMePostMemGuid, NULL, NULL, AsmReadTsc (), 0x40B1);

  //
  // Perform AMT post mem init
  //
  PERF_START_EX (&gPerfAmtPostMemGuid, NULL, NULL, AsmReadTsc (), 0x40C0);
  AmtPostMemInit ();
  PERF_END_EX (&gPerfAmtPostMemGuid, NULL, NULL, AsmReadTsc (), 0x40C1);

  //
  // Install EndOfPei callback function.
  //
  Status = PeiServicesNotifyPpi (mSiInitNotifyList);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "SiInit () - End\n"));
  //
  // End of SiInit notification event
  //
  Status = PeiServicesInstallPpi (&mEndOfSiInit);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Silicon Initializes after memory services initialized

  @param[in] FileHandle           The file handle of the file, Not used.
  @param[in] PeiServices          General purpose services available to every PEIM.

  @retval EFI_SUCCESS             The function completes successfully
**/
EFI_STATUS
EFIAPI
SiInit (
  IN  EFI_PEI_FILE_HANDLE               FileHandle,
  IN CONST EFI_PEI_SERVICES             **PeiServices
  )
{
  EFI_STATUS                Status;

  //
  // Install PostMem phase OnPolicyInstalled callback function.
  //
  Status = PeiServicesNotifyPpi (mSiInitPostMemNotifyList);
  ASSERT_EFI_ERROR (Status);

  return Status;
}
