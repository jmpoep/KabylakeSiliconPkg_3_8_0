/** @file
  This file is SampleCode of the library for Intel CPU PEI Policy initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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

#include <Library/DebugLib.h>
#include <Ppi/SiPolicy.h>
#include <FspmUpd.h>
#include <Library/ConfigBlockLib.h>

/**
  This function performs Security PEI Policy initialization in Pre-memory.

  @param[in] SiPreMemPolicyPpi     The SI Pre-Mem Policy PPI instance
  @param[in] FspmUpd               The pointer of FspmUpd

  @retval EFI_SUCCESS              The PPI is installed and initialized.
  @retval EFI ERRORS               The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES     Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
FspUpdatePeiSecurityPolicyPreMem (
  IN OUT SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi,
  IN      FSPM_UPD            *FspmUpd
  )
{
  EFI_STATUS                    Status;
  CPU_SECURITY_PREMEM_CONFIG    *CpuSecurityPreMemConfig;
  CPU_TXT_PREMEM_CONFIG         *CpuTxtPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuTxtPreMemConfigGuid, (VOID *) &CpuTxtPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  ///Test RC Policies
  ///
  CpuSecurityPreMemConfig->SkipStopPbet = FspmUpd->FspmConfig.SkipStopPbet;
  CpuSecurityPreMemConfig->EnableC6Dram = FspmUpd->FspmConfig.EnableC6Dram;

  ///
  ///Production Policies
  ///
  CpuSecurityPreMemConfig->BiosGuard                 = FspmUpd->FspmConfig.BiosGuard;
  CpuSecurityPreMemConfig->EnableSgx                 = FspmUpd->FspmConfig.EnableSgx;
  CpuSecurityPreMemConfig->Txt                       = FspmUpd->FspmConfig.Txt;
  CpuSecurityPreMemConfig->FlashWearOutProtection    = FspmUpd->FspmConfig.FlashWearOutProtection;
  CpuSecurityPreMemConfig->PrmrrSize                 = FspmUpd->FspmConfig.PrmrrSize;

  if ((CpuSecurityPreMemConfig->EnableC6Dram == 1) && (CpuSecurityPreMemConfig->PrmrrSize == 0)) {
    //
    // Set PrmrrSize to 1 MB
    //
    CpuSecurityPreMemConfig->PrmrrSize = SIZE_1MB;
  }

  //
  //Value is produced premem (value initialized in TXT_INFO_HOB premem).  It is not consumed until DXE.
  //In theory, could be produced in postmem - will be done during TXT enablement
  //
  CpuTxtPreMemConfig->SinitMemorySize   = FspmUpd->FspmConfig.SinitMemorySize;
  CpuTxtPreMemConfig->TxtHeapMemorySize = FspmUpd->FspmConfig.TxtHeapMemorySize;
  CpuTxtPreMemConfig->TxtDprMemoryBase  = FspmUpd->FspmConfig.TxtDprMemoryBase;
  CpuTxtPreMemConfig->TxtDprMemorySize  = FspmUpd->FspmConfig.TxtDprMemorySize;

  ///
  ///Test RC Policies
  ///
  CpuSecurityPreMemConfig->BiosSize        = FspmUpd->FspmTestConfig.BiosSize;
  CpuTxtPreMemConfig->BiosAcmBase          = FspmUpd->FspmTestConfig.BiosAcmBase;
  CpuTxtPreMemConfig->BiosAcmSize          = FspmUpd->FspmTestConfig.BiosAcmSize;
  CpuTxtPreMemConfig->TgaSize              = FspmUpd->FspmTestConfig.TgaSize;
  CpuTxtPreMemConfig->TxtLcpPdBase         = FspmUpd->FspmTestConfig.TxtLcpPdBase;
  CpuTxtPreMemConfig->TxtLcpPdSize         = FspmUpd->FspmTestConfig.TxtLcpPdSize;

  return EFI_SUCCESS;
}
