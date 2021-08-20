/** @file
  This file is SampleCode of the library for Intel CPU PEI Policy initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
  This function performs CPU PEI Policy initialization in Pre-memory.

  @param[in] SiPreMemPolicyPpi     The SI Pre-Mem Policy PPI instance
  @param[in] FspmUpd               The pointer of FspmUpd

  @retval EFI_SUCCESS              The PPI is installed and initialized.
  @retval EFI ERRORS               The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES     Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
FspUpdatePeiCpuPolicyPreMem (
  IN OUT SI_PREMEM_POLICY_PPI     *SiPreMemPolicyPpi,
  IN FSPM_UPD                     *FspmUpd
  )
{
  CPU_OVERCLOCKING_PREMEM_CONFIG  *CpuOverClockingPreMemConfig;
  CPU_CONFIG_LIB_PREMEM_CONFIG    *CpuConfigLibPreMemConfig;
  EFI_STATUS                      Status;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuOverclockingPreMemConfigGuid, (VOID *) &CpuOverClockingPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuConfigLibPreMemConfigGuid, (VOID *) &CpuConfigLibPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  //
  //  Update CpuOverClockingPreMem Config Block data
  //
  CpuOverClockingPreMemConfig->OcSupport                = FspmUpd->FspmConfig.OcSupport;
  CpuOverClockingPreMemConfig->OcLock                   = FspmUpd->FspmConfig.OcLock;
  CpuOverClockingPreMemConfig->CoreMaxOcRatio           = FspmUpd->FspmConfig.CoreMaxOcRatio;
  CpuOverClockingPreMemConfig->CoreVoltageMode          = FspmUpd->FspmConfig.CoreVoltageMode;
  CpuOverClockingPreMemConfig->RingMinOcRatio           = FspmUpd->FspmConfig.RingMinOcRatio;
  CpuOverClockingPreMemConfig->RingMaxOcRatio           = FspmUpd->FspmConfig.RingMaxOcRatio;
  CpuOverClockingPreMemConfig->RingDownBin              = FspmUpd->FspmConfig.RingDownBin;
  CpuOverClockingPreMemConfig->CoreVoltageOverride      = FspmUpd->FspmConfig.CoreVoltageOverride;
  CpuOverClockingPreMemConfig->CoreVoltageAdaptive      = FspmUpd->FspmConfig.CoreVoltageAdaptive;
  CpuOverClockingPreMemConfig->CoreVoltageOffset        = FspmUpd->FspmConfig.CoreVoltageOffset;
  CpuOverClockingPreMemConfig->CorePllVoltageOffset     = FspmUpd->FspmConfig.CorePllVoltageOffset;
  CpuOverClockingPreMemConfig->GtPllVoltageOffset       = FspmUpd->FspmConfig.GtPllVoltageOffset;
  CpuOverClockingPreMemConfig->RingPllVoltageOffset     = FspmUpd->FspmConfig.RingPllVoltageOffset;
  CpuOverClockingPreMemConfig->SaPllVoltageOffset       = FspmUpd->FspmConfig.SaPllVoltageOffset;
  CpuOverClockingPreMemConfig->McPllVoltageOffset       = FspmUpd->FspmConfig.McPllVoltageOffset;
  CpuOverClockingPreMemConfig->BclkAdaptiveVoltage      = FspmUpd->FspmConfig.BclkAdaptiveVoltage;
  CpuOverClockingPreMemConfig->TvbRatioClipping         = FspmUpd->FspmConfig.TvbRatioClipping;
  CpuOverClockingPreMemConfig->TvbVoltageOptimization   = FspmUpd->FspmConfig.TvbVoltageOptimization;
  CpuOverClockingPreMemConfig->Avx2RatioOffset          = FspmUpd->FspmConfig.Avx2RatioOffset;
  CpuOverClockingPreMemConfig->TjMaxOffset              = FspmUpd->FspmConfig.TjMaxOffset;

  //
  //  Update CpuConfigLibPreMem Config Block data
  //
  CpuConfigLibPreMemConfig->HyperThreading          = FspmUpd->FspmConfig.HyperThreading;
  CpuConfigLibPreMemConfig->BootFrequency           = FspmUpd->FspmConfig.BootFrequency;
  CpuConfigLibPreMemConfig->ActiveCoreCount         = FspmUpd->FspmConfig.ActiveCoreCount;
  CpuConfigLibPreMemConfig->FClkFrequency           = FspmUpd->FspmConfig.FClkFrequency;
  CpuConfigLibPreMemConfig->JtagC10PowerGateDisable = FspmUpd->FspmConfig.JtagC10PowerGateDisable;
  CpuConfigLibPreMemConfig->BistOnReset             = FspmUpd->FspmConfig.BistOnReset;
  CpuConfigLibPreMemConfig->VmxEnable               = FspmUpd->FspmConfig.VmxEnable;
  CpuConfigLibPreMemConfig->CpuRatioOverride        = FspmUpd->FspmConfig.CpuRatioOverride;
  CpuConfigLibPreMemConfig->CpuRatio                = FspmUpd->FspmConfig.CpuRatio;
  CpuConfigLibPreMemConfig->PeciSxReset             = FspmUpd->FspmConfig.PeciSxReset;
  CpuConfigLibPreMemConfig->PeciC10Reset            = FspmUpd->FspmConfig.PeciC10Reset;
  CpuConfigLibPreMemConfig->DpSscMarginEnable       = FspmUpd->FspmConfig.DpSscMarginEnable;

  return EFI_SUCCESS;
}
