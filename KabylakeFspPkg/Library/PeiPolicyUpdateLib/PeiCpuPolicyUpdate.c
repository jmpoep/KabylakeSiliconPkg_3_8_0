/** @file
  This file is SampleCode of the library for Intel CPU PEI Policy initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2018 Intel Corporation.

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

#include <PiPei.h>
#include <Ppi/SiPolicy.h>
#include <Library/FspCommonLib.h>
#include <FspsUpd.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/CpuPlatformLib.h>
#include <Register/Cpuid.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PcdLib.h>

/**
  Get the next microcode patch pointer.

  @param[in, out] MicrocodeData - Input is a pointer to the last microcode patch address found,
                                  and output points to the next patch address found.

  @retval EFI_SUCCESS           - Patch found.
  @retval EFI_NOT_FOUND         - Patch not found.
**/
EFI_STATUS
EFIAPI
RetrieveNextMicrocode (
  IN OUT CPU_MICROCODE_HEADER   **MicrocodeData,
  IN UINT32 MicrocodeEnd
  )
{
  UINT32  TotalSize;

  TotalSize =(UINT32)((*MicrocodeData)->TotalSize);
  if (TotalSize == 0) {
    TotalSize = 2048;
  } else if (TotalSize == (UINT32) -1) {
    //
    // Return if function tries to read from empty region (0xFFFFFFFF)
    //
    return EFI_NOT_FOUND;
  }

  *MicrocodeData = (CPU_MICROCODE_HEADER *)((UINTN)*MicrocodeData + TotalSize);
  if (*MicrocodeData >= (CPU_MICROCODE_HEADER *)(UINTN)MicrocodeEnd || *MicrocodeData == (VOID*)-1) {
    return EFI_NOT_FOUND;
  }

  return EFI_SUCCESS;
}

/**
  Get the microcode patch pointer.

  @retval CPU_MICROCODE_HEADER * - Address of the microcode patch, or NULL if not found.
**/

CPU_MICROCODE_HEADER *
PlatformCpuLocateMicrocodePatch (
    IN UINT32 MicrocodeRegionBase,
    IN UINT32 MicrocodeRegionLength
  )
{
  EFI_STATUS              Status;
  CPU_MICROCODE_HEADER    *MicrocodeData = (CPU_MICROCODE_HEADER *)MicrocodeRegionBase;
  UINT32                  MicrocodeEnd = MicrocodeRegionBase + MicrocodeRegionLength;
  EFI_CPUID_REGISTER      Cpuid;
  UINT32                  UcodeRevision;


  AsmCpuid (
    CPUID_VERSION_INFO,
    &Cpuid.RegEax,
    &Cpuid.RegEbx,
    &Cpuid.RegEcx,
    &Cpuid.RegEdx
    );

  UcodeRevision = GetCpuUcodeRevision ();

  Status = EFI_SUCCESS;   //Initialize to EFI_SUCCESS, so first microcode is successful.
  while (TRUE) {
    if (CheckMicrocode (Cpuid.RegEax, MicrocodeData, &UcodeRevision)) break;

    //
    // Find the next patch address
    //
    Status = RetrieveNextMicrocode (&MicrocodeData, MicrocodeEnd);
    if (Status != EFI_SUCCESS) {
      break;
    }

  }

  if (EFI_ERROR (Status)) {
    return 0;
  }

  return MicrocodeData;
}

/**
  This function performs CPU PEI Policy initialization.

  @param[in] SiPolicyPpi           The SI Policy PPI instance
  @param[in] FspsUpd               The pointer of FspsUpd

  @retval EFI_SUCCESS              The PPI is installed and initialized.
  @retval EFI ERRORS               The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES     Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
FspUpdatePeiCpuPolicy (
  IN OUT SI_POLICY_PPI        *SiPolicyPpi,
  IN FSPS_UPD                 *FspsUpd
  )
{
  EFI_STATUS                       Status;
  CPU_MICROCODE_HEADER             *MicrocodePatchAddress;
  UINT32                           MicrocodeRegionBase;
  UINT32                           MicrocodeRegionSize;
  CPU_CONFIG                       *CpuConfig;
  CPU_POWER_MGMT_BASIC_CONFIG      *CpuPowerMgmtBasicConfig;
  CPU_POWER_MGMT_VR_CONFIG         *CpuPowerMgmtVrConfig;
  CPU_POWER_MGMT_CUSTOM_CONFIG     *CpuPowerMgmtCustomConfig;
  CPU_POWER_MGMT_PSYS_CONFIG       *CpuPowerMgmtPsysConfig;
  CPU_TEST_CONFIG                  *CpuTestConfig;
  CPU_POWER_MGMT_TEST_CONFIG       *CpuPowerMgmtTestConfig;
  UINTN                             Index;
  CPU_FAMILY                       CpuFamily;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuConfigGuid, (VOID *) &CpuConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtBasicConfigGuid, (VOID *) &CpuPowerMgmtBasicConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtVrConfigGuid, (VOID *) &CpuPowerMgmtVrConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtCustomConfigGuid, (VOID *) &CpuPowerMgmtCustomConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtPsysConfigGuid, (VOID *) &CpuPowerMgmtPsysConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuTestConfigGuid, (VOID *) &CpuTestConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtTestConfigGuid, (VOID *) &CpuPowerMgmtTestConfig);
  ASSERT_EFI_ERROR (Status);
  MicrocodeRegionBase = FspsUpd->FspsConfig.MicrocodeRegionBase;
  MicrocodeRegionSize = FspsUpd->FspsConfig.MicrocodeRegionSize;

  MicrocodePatchAddress = 0; //This must be initialized, since if statement below may not initialize.

  if (MicrocodeRegionBase != 0 && MicrocodeRegionSize != 0) {
    DEBUG((DEBUG_INFO, "Searching for microcode updates in region UPD MicrocodeRegionBase = 0x%x, UPD MicrocodeRegionSize = 0x%x.\n",
      MicrocodeRegionBase, MicrocodeRegionSize
      ));

    MicrocodePatchAddress = PlatformCpuLocateMicrocodePatch(MicrocodeRegionBase, MicrocodeRegionSize);

    if (MicrocodePatchAddress == 0)
      DEBUG((DEBUG_ERROR, "Microcode update not available in UPD region.\n"));
  }

  if (MicrocodePatchAddress == 0) {
    FSP_GLOBAL_DATA * FspGlobalData = GetFspGlobalDataPointer ();

    MicrocodeRegionBase = FspGlobalData->PlatformData.MicrocodeRegionBase;
    MicrocodeRegionSize = FspGlobalData->PlatformData.MicrocodeRegionSize;

    DEBUG((DEBUG_INFO, "Searching for microcode updates in region passed in TempRamInit API MicrocodeRegionBase = 0x%x, MicrocodeRegionSize = 0x%x.\n",
      MicrocodeRegionBase, MicrocodeRegionSize
      ));

    MicrocodePatchAddress = PlatformCpuLocateMicrocodePatch(MicrocodeRegionBase, MicrocodeRegionSize);
    if (MicrocodePatchAddress == 0)
      DEBUG((DEBUG_ERROR, "Microcode update not available in FSP_TEMP_RAM_INIT_PARAMS region.\n"));
  }

  if (MicrocodePatchAddress != 0) {
    PcdSet64(PcdCpuMicrocodePatchAddress, (EFI_PHYSICAL_ADDRESS)(UINTN)MicrocodePatchAddress);
    if (MicrocodePatchAddress->TotalSize == 0) {
      PcdSet64(PcdCpuMicrocodePatchRegionSize, 2048);
    } else {
      PcdSet64(PcdCpuMicrocodePatchRegionSize, MicrocodePatchAddress->TotalSize);
    }

    DEBUG((DEBUG_INFO, "Microcode update found at 0x%x\n", (UINTN)MicrocodePatchAddress));
  }
  CpuConfig->MicrocodePatchAddress = (EFI_PHYSICAL_ADDRESS)(UINTN)MicrocodePatchAddress;

  //
  // Production RC Policies
  //

  CopyMem ((VOID *)&(((CPU_CONFIG_UNION *)CpuConfig)->CpuConfigFsp.Data), (VOID *)&(FspsUpd->FspsConfig.CpuConfig), sizeof (UINT32));
  CpuConfig->MicrocodePatchAddress                = FspsUpd->FspsConfig.MicrocodePatchAddress;

  CpuPowerMgmtBasicConfig->TurboMode              = FspsUpd->FspsConfig.TurboMode;

  for (Index = 0; Index < MAX_NUM_VRS; Index++) {
      CpuPowerMgmtVrConfig->Psi3Enable[Index]     = FspsUpd->FspsConfig.Psi3Enable[Index];
      CpuPowerMgmtVrConfig->Psi4Enable[Index]     = FspsUpd->FspsConfig.Psi4Enable[Index];
      CpuPowerMgmtVrConfig->ImonSlope[Index]      = FspsUpd->FspsConfig.ImonSlope[Index];
      CpuPowerMgmtVrConfig->ImonOffset[Index]     = FspsUpd->FspsConfig.ImonOffset[Index];
      CpuPowerMgmtVrConfig->VrConfigEnable[Index] = FspsUpd->FspsConfig.VrConfigEnable[Index];
      CpuPowerMgmtVrConfig->TdcEnable[Index]      = FspsUpd->FspsConfig.TdcEnable[Index];
      CpuPowerMgmtVrConfig->TdcTimeWindow[Index]  = FspsUpd->FspsConfig.TdcTimeWindow[Index];
      CpuPowerMgmtVrConfig->TdcLock[Index]        = FspsUpd->FspsConfig.TdcLock[Index];
      CpuPowerMgmtVrConfig->TdcPowerLimit[Index]  = FspsUpd->FspsConfig.TdcPowerLimit[Index];
      CpuPowerMgmtVrConfig->AcLoadline[Index]     = FspsUpd->FspsConfig.AcLoadline[Index];
      CpuPowerMgmtVrConfig->DcLoadline[Index]     = FspsUpd->FspsConfig.DcLoadline[Index];
      CpuPowerMgmtVrConfig->Psi1Threshold[Index]  = FspsUpd->FspsConfig.Psi1Threshold[Index];
      CpuPowerMgmtVrConfig->Psi2Threshold[Index]  = FspsUpd->FspsConfig.Psi2Threshold[Index];
      CpuPowerMgmtVrConfig->Psi3Threshold[Index]  = FspsUpd->FspsConfig.Psi3Threshold[Index];
      CpuPowerMgmtVrConfig->IccMax[Index]         = FspsUpd->FspsConfig.IccMax[Index];
      CpuPowerMgmtVrConfig->VrVoltageLimit[Index] = FspsUpd->FspsConfig.VrVoltageLimit[Index];
  }

  CpuPowerMgmtVrConfig->PsysSlope                 = FspsUpd->FspsConfig.PsysSlope;
  CpuPowerMgmtVrConfig->PsysOffset                = FspsUpd->FspsConfig.PsysOffset;
  CpuPowerMgmtVrConfig->AcousticNoiseMitigation   = FspsUpd->FspsConfig.AcousticNoiseMitigation;
  CpuPowerMgmtVrConfig->FastPkgCRampDisableIa     = FspsUpd->FspsConfig.FastPkgCRampDisableIa;
  CpuPowerMgmtVrConfig->FastPkgCRampDisableGt     = FspsUpd->FspsConfig.FastPkgCRampDisableGt;
  CpuPowerMgmtVrConfig->FastPkgCRampDisableSa     = FspsUpd->FspsConfig.FastPkgCRampDisableSa;
  CpuPowerMgmtVrConfig->SlowSlewRateForIa         = FspsUpd->FspsConfig.SlowSlewRateForIa;
  CpuPowerMgmtVrConfig->SlowSlewRateForGt         = FspsUpd->FspsConfig.SlowSlewRateForGt;
  CpuPowerMgmtVrConfig->SlowSlewRateForSa         = FspsUpd->FspsConfig.SlowSlewRateForSa;
  CpuPowerMgmtVrConfig->SendVrMbxCmd1             = FspsUpd->FspsConfig.SendVrMbxCmd1;
  CpuPowerMgmtVrConfig->IslVrCmd                  = FspsUpd->FspsConfig.IslVrCmd;
  CpuPowerMgmtVrConfig->VrPowerDeliveryDesign     = FspsUpd->FspsConfig.VrPowerDeliveryDesign;

  ///
  ///Test RC Policies
  ///
  CpuTestConfig->MlcStreamerPrefetcher    = FspsUpd->FspsTestConfig.MlcStreamerPrefetcher;
  CpuTestConfig->MlcSpatialPrefetcher     = FspsUpd->FspsTestConfig.MlcSpatialPrefetcher;
  CpuTestConfig->MonitorMwaitEnable       = FspsUpd->FspsTestConfig.MonitorMwaitEnable;
  CpuTestConfig->DebugInterfaceEnable     = FspsUpd->FspsTestConfig.DebugInterfaceEnable;
  CpuTestConfig->DebugInterfaceLockEnable = FspsUpd->FspsTestConfig.DebugInterfaceLockEnable;
  CpuTestConfig->ApIdleManner             = FspsUpd->FspsTestConfig.ApIdleManner;
  CpuTestConfig->ApHandoffManner          = FspsUpd->FspsTestConfig.ApHandoffManner;
  CpuTestConfig->ProcTraceOutputScheme    = FspsUpd->FspsTestConfig.ProcTraceOutputScheme;
  CpuTestConfig->ProcTraceEnable          = FspsUpd->FspsTestConfig.ProcTraceEnable;
  CpuTestConfig->ProcTraceMemSize         = FspsUpd->FspsTestConfig.ProcTraceMemSize;
  CpuTestConfig->VoltageOptimization      = FspsUpd->FspsTestConfig.VoltageOptimization;
  CpuTestConfig->ThreeStrikeCounterDisable  = FspsUpd->FspsTestConfig.ThreeStrikeCounterDisable;

  PcdSet8S (PcdCpuApLoopMode, (UINT8) CpuTestConfig->ApIdleManner);

  CpuPowerMgmtBasicConfig->OneCoreRatioLimit          = FspsUpd->FspsTestConfig.OneCoreRatioLimit;
  CpuPowerMgmtBasicConfig->TwoCoreRatioLimit          = FspsUpd->FspsTestConfig.TwoCoreRatioLimit;
  CpuPowerMgmtBasicConfig->ThreeCoreRatioLimit        = FspsUpd->FspsTestConfig.ThreeCoreRatioLimit;
  CpuPowerMgmtBasicConfig->FourCoreRatioLimit         = FspsUpd->FspsTestConfig.FourCoreRatioLimit;
  CpuPowerMgmtBasicConfig->FiveCoreRatioLimit         = FspsUpd->FspsTestConfig.FiveCoreRatioLimit;
  CpuPowerMgmtBasicConfig->SixCoreRatioLimit          = FspsUpd->FspsTestConfig.SixCoreRatioLimit;
  CpuPowerMgmtBasicConfig->SevenCoreRatioLimit        = FspsUpd->FspsTestConfig.SevenCoreRatioLimit;
  CpuPowerMgmtBasicConfig->EightCoreRatioLimit        = FspsUpd->FspsTestConfig.EightCoreRatioLimit;
  CpuPowerMgmtBasicConfig->Hwp                        = FspsUpd->FspsTestConfig.Hwp;
  CpuPowerMgmtBasicConfig->HdcControl                 = FspsUpd->FspsTestConfig.HdcControl;
  CpuPowerMgmtBasicConfig->PowerLimit1Time            = FspsUpd->FspsTestConfig.PowerLimit1Time;
  CpuPowerMgmtBasicConfig->PowerLimit2                = FspsUpd->FspsTestConfig.PowerLimit2;
  CpuPowerMgmtBasicConfig->TurboPowerLimitLock        = FspsUpd->FspsTestConfig.TurboPowerLimitLock;
  CpuPowerMgmtBasicConfig->PowerLimit3Time            = FspsUpd->FspsTestConfig.PowerLimit3Time;
  CpuPowerMgmtBasicConfig->PowerLimit3DutyCycle       = FspsUpd->FspsTestConfig.PowerLimit3DutyCycle;
  CpuPowerMgmtBasicConfig->PowerLimit3Lock            = FspsUpd->FspsTestConfig.PowerLimit3Lock;
  CpuPowerMgmtBasicConfig->PowerLimit4Lock            = FspsUpd->FspsTestConfig.PowerLimit4Lock;
  CpuPowerMgmtBasicConfig->TccActivationOffset        = FspsUpd->FspsTestConfig.TccActivationOffset;
  CpuPowerMgmtBasicConfig->TccOffsetClamp             = FspsUpd->FspsTestConfig.TccOffsetClamp;
  CpuPowerMgmtBasicConfig->TccOffsetLock              = FspsUpd->FspsTestConfig.TccOffsetLock;
  CpuPowerMgmtBasicConfig->PowerLimit1                = (UINT16) (FspsUpd->FspsTestConfig.PowerLimit1 / 125);
  CpuPowerMgmtBasicConfig->PowerLimit2Power           = (UINT16) (FspsUpd->FspsTestConfig.PowerLimit2Power / 125);
  CpuPowerMgmtBasicConfig->PowerLimit3                = (UINT16) (FspsUpd->FspsTestConfig.PowerLimit3 / 125);
  CpuPowerMgmtBasicConfig->PowerLimit4                = (UINT16) (FspsUpd->FspsTestConfig.PowerLimit4 / 125);
  CpuPowerMgmtBasicConfig->TccOffsetTimeWindowForRatl = FspsUpd->FspsTestConfig.TccOffsetTimeWindowForRatl;

  CpuPowerMgmtCustomConfig->CustomRatioTable.NumberOfEntries                                      = FspsUpd->FspsTestConfig.NumberOfEntries;
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomPowerLimit1Time      = FspsUpd->FspsTestConfig.Custom1PowerLimit1Time;
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[1].CustomPowerLimit1Time      = FspsUpd->FspsTestConfig.Custom2PowerLimit1Time;
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[2].CustomPowerLimit1Time      = FspsUpd->FspsTestConfig.Custom3PowerLimit1Time;
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomTurboActivationRatio = FspsUpd->FspsTestConfig.Custom1TurboActivationRatio;
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[1].CustomTurboActivationRatio = FspsUpd->FspsTestConfig.Custom2TurboActivationRatio;
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[2].CustomTurboActivationRatio = FspsUpd->FspsTestConfig.Custom3TurboActivationRatio;
  CpuPowerMgmtCustomConfig->ConfigTdpLock                                                         = FspsUpd->FspsTestConfig.ConfigTdpLock;
  CpuPowerMgmtCustomConfig->ConfigTdpBios                                                         = FspsUpd->FspsTestConfig.ConfigTdpBios;
  CpuPowerMgmtCustomConfig->CustomRatioTable.MaxRatio                                             = FspsUpd->FspsTestConfig.MaxRatio;
  for (Index = 0; Index < CpuPowerMgmtCustomConfig->CustomRatioTable.NumberOfEntries; Index++) {
      CpuPowerMgmtCustomConfig->CustomRatioTable.StateRatio[Index]                                = FspsUpd->FspsTestConfig.StateRatio[Index];
  }
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomPowerLimit1          = (UINT16) (FspsUpd->FspsTestConfig.Custom1PowerLimit1 / 125);
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomPowerLimit2          = (UINT16) (FspsUpd->FspsTestConfig.Custom1PowerLimit2 / 125);
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[1].CustomPowerLimit1          = (UINT16) (FspsUpd->FspsTestConfig.Custom2PowerLimit1 / 125);
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[1].CustomPowerLimit2          = (UINT16) (FspsUpd->FspsTestConfig.Custom2PowerLimit2 / 125);
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[2].CustomPowerLimit1          = (UINT16) (FspsUpd->FspsTestConfig.Custom3PowerLimit1 / 125);
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[2].CustomPowerLimit2          = (UINT16) (FspsUpd->FspsTestConfig.Custom3PowerLimit2 / 125);

  CpuPowerMgmtPsysConfig->PsysPowerLimit1      = FspsUpd->FspsTestConfig.PsysPowerLimit1;
  CpuPowerMgmtPsysConfig->PsysPowerLimit1Time  = FspsUpd->FspsTestConfig.PsysPowerLimit1Time;
  CpuPowerMgmtPsysConfig->PsysPowerLimit2      = FspsUpd->FspsTestConfig.PsysPowerLimit2;
  CpuPowerMgmtPsysConfig->PsysPmax             = FspsUpd->FspsTestConfig.PsysPmax;
  CpuPowerMgmtPsysConfig->PsysPowerLimit1Power = (UINT16) (FspsUpd->FspsTestConfig.PsysPowerLimit1Power / 125);
  CpuPowerMgmtPsysConfig->PsysPowerLimit2Power = (UINT16) (FspsUpd->FspsTestConfig.PsysPowerLimit2Power / 125);

  CpuPowerMgmtTestConfig->Eist                          = FspsUpd->FspsTestConfig.Eist;
  CpuPowerMgmtTestConfig->EnergyEfficientPState         = FspsUpd->FspsTestConfig.EnergyEfficientPState;
  CpuPowerMgmtTestConfig->EnergyEfficientTurbo          = FspsUpd->FspsTestConfig.EnergyEfficientTurbo;
  CpuPowerMgmtTestConfig->TStates                       = FspsUpd->FspsTestConfig.TStates;
  CpuPowerMgmtTestConfig->BiProcHot                     = FspsUpd->FspsTestConfig.BiProcHot;
  CpuPowerMgmtTestConfig->DisableProcHotOut             = FspsUpd->FspsTestConfig.DisableProcHotOut;
  CpuPowerMgmtTestConfig->ProcHotResponse               = FspsUpd->FspsTestConfig.ProcHotResponse;
  CpuPowerMgmtTestConfig->DisableVrThermalAlert         = FspsUpd->FspsTestConfig.DisableVrThermalAlert;
  CpuPowerMgmtTestConfig->AutoThermalReporting          = FspsUpd->FspsTestConfig.AutoThermalReporting;
  CpuPowerMgmtTestConfig->ThermalMonitor                = FspsUpd->FspsTestConfig.ThermalMonitor;
  CpuPowerMgmtTestConfig->Cx                            = FspsUpd->FspsTestConfig.Cx;
  CpuPowerMgmtTestConfig->PmgCstCfgCtrlLock             = FspsUpd->FspsTestConfig.PmgCstCfgCtrlLock;
  CpuPowerMgmtTestConfig->C1e                           = FspsUpd->FspsTestConfig.C1e;
  CpuPowerMgmtTestConfig->CStatePreWake                 = FspsUpd->FspsTestConfig.CStatePreWake;
  CpuPowerMgmtTestConfig->TimedMwait                    = FspsUpd->FspsTestConfig.TimedMwait;
  CpuPowerMgmtTestConfig->CstCfgCtrIoMwaitRedirection   = FspsUpd->FspsTestConfig.CstCfgCtrIoMwaitRedirection;
  CpuPowerMgmtTestConfig->PkgCStateLimit                = FspsUpd->FspsTestConfig.PkgCStateLimit;
  CpuPowerMgmtTestConfig->CstateLatencyControl0TimeUnit = FspsUpd->FspsTestConfig.CstateLatencyControl0TimeUnit;
  CpuPowerMgmtTestConfig->CstateLatencyControl1TimeUnit = FspsUpd->FspsTestConfig.CstateLatencyControl1TimeUnit;
  CpuPowerMgmtTestConfig->CstateLatencyControl2TimeUnit = FspsUpd->FspsTestConfig.CstateLatencyControl2TimeUnit;
  CpuPowerMgmtTestConfig->CstateLatencyControl3TimeUnit = FspsUpd->FspsTestConfig.CstateLatencyControl3TimeUnit;
  CpuPowerMgmtTestConfig->CstateLatencyControl4TimeUnit = FspsUpd->FspsTestConfig.CstateLatencyControl4TimeUnit;
  CpuPowerMgmtTestConfig->CstateLatencyControl5TimeUnit = FspsUpd->FspsTestConfig.CstateLatencyControl5TimeUnit;
  CpuPowerMgmtTestConfig->PpmIrmSetting                 = FspsUpd->FspsTestConfig.PpmIrmSetting;
  CpuPowerMgmtTestConfig->ProcHotLock                   = FspsUpd->FspsTestConfig.ProcHotLock;
  CpuPowerMgmtTestConfig->RaceToHalt                    = FspsUpd->FspsTestConfig.RaceToHalt;
  CpuPowerMgmtTestConfig->ConfigTdpLevel                = FspsUpd->FspsTestConfig.ConfigTdpLevel;
  CpuPowerMgmtTestConfig->CstateLatencyControl0Irtl     = FspsUpd->FspsTestConfig.CstateLatencyControl0Irtl;
  CpuPowerMgmtTestConfig->CstateLatencyControl1Irtl     = FspsUpd->FspsTestConfig.CstateLatencyControl1Irtl;
  CpuPowerMgmtTestConfig->CstateLatencyControl2Irtl     = FspsUpd->FspsTestConfig.CstateLatencyControl2Irtl;
  CpuPowerMgmtTestConfig->CstateLatencyControl3Irtl     = FspsUpd->FspsTestConfig.CstateLatencyControl3Irtl;
  CpuPowerMgmtTestConfig->CstateLatencyControl4Irtl     = FspsUpd->FspsTestConfig.CstateLatencyControl4Irtl;
  CpuPowerMgmtTestConfig->CstateLatencyControl5Irtl     = FspsUpd->FspsTestConfig.CstateLatencyControl5Irtl;

  //
  // Pkg C-state Demotion/Un Demotion
  //
  CpuFamily = GetCpuFamily();
  if(FspsUpd->FspsTestConfig.PkgCStateDemotion != 0x2) {
    CpuPowerMgmtTestConfig->PkgCStateDemotion             = FspsUpd->FspsTestConfig.PkgCStateDemotion;
  } else {
    if((CpuFamily == EnumCpuSklUltUlx) || (CpuFamily == EnumCpuSklDtHalo)){
      CpuPowerMgmtTestConfig->PkgCStateDemotion                  = 0x1;
    } else if((CpuFamily == EnumCpuKblUltUlx) || (CpuFamily == EnumCpuKblDtHalo)) {
      CpuPowerMgmtTestConfig->PkgCStateDemotion                  = 0x0;
    }
  }
  if(FspsUpd->FspsTestConfig.PkgCStateUnDemotion != 0x2) {
    CpuPowerMgmtTestConfig->PkgCStateUnDemotion           = FspsUpd->FspsTestConfig.PkgCStateUnDemotion;
  } else {
    if((CpuFamily == EnumCpuSklUltUlx) || (CpuFamily == EnumCpuSklDtHalo)){
      CpuPowerMgmtTestConfig->PkgCStateUnDemotion                  = 0x1;
    } else if((CpuFamily == EnumCpuKblUltUlx) || (CpuFamily == EnumCpuKblDtHalo)) {
      CpuPowerMgmtTestConfig->PkgCStateUnDemotion                  = 0x0;
    }
  }


  return EFI_SUCCESS;
}

