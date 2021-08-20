/** @file
  Do Platform Stage System Agent initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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

#include <FspEas.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiSaPolicyLib.h>
#include <Library/FspCommonLib.h>
#include <Library/DebugLib.h>
#include <FspmUpd.h>


/**
  UpdatePeiSaPolicy performs SA PEI Policy initialization in pre-memory

  @param[in, out] SiPreMemPolicyPpi       SI_PREMEM_POLICY_PPI
  @param[in]      FspmUpd                 The pointer of FspmUpd

  @retval EFI_SUCCESS              The policy is installed and initialized.
**/
EFI_STATUS
FspUpdatePeiSaPolicyPreMem (
  IN OUT SI_PREMEM_POLICY_PPI       *SiPreMemPolicyPpi,
  IN     FSPM_UPD                   *FspmUpd
  )
{
  EFI_STATUS                    Status;
  SA_MISC_PEI_PREMEM_CONFIG     *MiscPeiPreMemConfig;
  MEMORY_CONFIG_NO_CRC          *MemConfigNoCrc;
  GRAPHICS_PEI_PREMEM_CONFIG    *GtPreMemConfig;
  MEMORY_CONFIGURATION          *MemConfig;
  PCIE_PEI_PREMEM_CONFIG        *PciePeiPreMemConfig;
  SWITCHABLE_GRAPHICS_CONFIG    *SgGpioData;
  OVERCLOCKING_PREMEM_CONFIG    *OcPreMemConfig;
  FSPM_UPD                      *FspmUpdDataPtr;
  UINT8                         Index;


  DEBUG ((DEBUG_INFO | DEBUG_INIT, "FSP UpdatePeiSaPolicyPreMem\n"));

  FspmUpdDataPtr = (FSPM_UPD *) GetFspMemoryInitUpdDataPointer ();
  MiscPeiPreMemConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSaMiscPeiPreMemConfigGuid, (VOID *) &MiscPeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  GtPreMemConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  MemConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMemoryConfigGuid, (VOID *) &MemConfig);
  ASSERT_EFI_ERROR (Status);

  MemConfigNoCrc = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMemoryConfigNoCrcGuid, (VOID *) &MemConfigNoCrc);
  ASSERT_EFI_ERROR (Status);

  PciePeiPreMemConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSaPciePeiPreMemConfigGuid, (VOID *) &PciePeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  SgGpioData = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSwitchableGraphicsConfigGuid, (VOID *) &SgGpioData);
  ASSERT_EFI_ERROR (Status);

  OcPreMemConfig = NULL;
  Status = GetConfigBlock((VOID *) SiPreMemPolicyPpi, &gSaOverclockingPreMemConfigGuid, (VOID *) &OcPreMemConfig);
  ASSERT_EFI_ERROR(Status);

  //
  // Update ConfigBlock: MemConfigNoCrc
  //
  ZeroMem((VOID *)MiscPeiPreMemConfig->SpdAddressTable, sizeof(MiscPeiPreMemConfig->SpdAddressTable));
  if ((VOID *)FspmUpd->FspmConfig.MemorySpdPtr00 != NULL) {
    CopyMem ((VOID *) MemConfigNoCrc->SpdData->SpdData[0][0], (VOID *)FspmUpd->FspmConfig.MemorySpdPtr00, FspmUpd->FspmConfig.MemorySpdDataLen);
  } else {
    ZeroMem ((VOID *)MemConfigNoCrc->SpdData->SpdData[0][0], sizeof(SA_MC_MAX_SPD_SIZE));
  }

  if ((VOID *)FspmUpd->FspmConfig.MemorySpdPtr01 != NULL) {
    CopyMem ((VOID *) MemConfigNoCrc->SpdData->SpdData[0][1], (VOID*)FspmUpd->FspmConfig.MemorySpdPtr01, FspmUpd->FspmConfig.MemorySpdDataLen);
  } else {
    ZeroMem ((VOID *)MemConfigNoCrc->SpdData->SpdData[0][1], sizeof(SA_MC_MAX_SPD_SIZE));
  }

  if ((VOID *)FspmUpd->FspmConfig.MemorySpdPtr10 != NULL) {
    CopyMem ((VOID *) MemConfigNoCrc->SpdData->SpdData[1][0], (VOID*)FspmUpd->FspmConfig.MemorySpdPtr10, FspmUpd->FspmConfig.MemorySpdDataLen);
  } else {
    ZeroMem ((VOID *)MemConfigNoCrc->SpdData->SpdData[1][0], sizeof(SA_MC_MAX_SPD_SIZE));
  }

  if ((VOID *)FspmUpd->FspmConfig.MemorySpdPtr11 != NULL) {
    CopyMem ((VOID *) MemConfigNoCrc->SpdData->SpdData[1][1], (VOID*)FspmUpd->FspmConfig.MemorySpdPtr11, FspmUpd->FspmConfig.MemorySpdDataLen);
  } else {
    ZeroMem ((VOID *) MemConfigNoCrc->SpdData->SpdData[1][1], sizeof(SA_MC_MAX_SPD_SIZE));
  }

  if (FspmUpd->FspmConfig.DqByteMapCh0 != NULL) {
    CopyMem ((VOID *) MemConfigNoCrc->DqByteMap->DqByteMap[0], &FspmUpd->FspmConfig.DqByteMapCh0[0], 12);
  }

  if (FspmUpd->FspmConfig.DqByteMapCh1 != NULL) {
    CopyMem ((VOID *) MemConfigNoCrc->DqByteMap->DqByteMap[1] , &FspmUpd->FspmConfig.DqByteMapCh1[0], 12);
  }

  if (FspmUpd->FspmConfig.DqsMapCpu2DramCh0 != NULL) {
    CopyMem ((VOID *) MemConfigNoCrc->DqsMap->DqsMapCpu2Dram[0], &FspmUpd->FspmConfig.DqsMapCpu2DramCh0[0], 8);
  }

  if (FspmUpd->FspmConfig.DqsMapCpu2DramCh1 != NULL) {
    CopyMem ((VOID *) MemConfigNoCrc->DqsMap->DqsMapCpu2Dram[1], &FspmUpd->FspmConfig.DqsMapCpu2DramCh1[0], 8);
  }

  if (FspmUpd->FspmConfig.RcompResistor != NULL) {
    CopyMem ((VOID *) &(MemConfigNoCrc->RcompData->RcompResistor[0]), (VOID *) &FspmUpd->FspmConfig.RcompResistor[0], 6);
  }

  if (FspmUpd->FspmConfig.RcompTarget != NULL) {
    CopyMem ((VOID *) &(MemConfigNoCrc->RcompData->RcompTarget[0]), (VOID *) &FspmUpd->FspmConfig.RcompTarget[0], 10);
  }
  MemConfigNoCrc->PlatformMemorySize = FspmUpd->FspmConfig.PlatformMemorySize;
  MemConfigNoCrc->SerialDebugLevel   = FspmUpd->FspmConfig.PcdSerialDebugLevel;
  MemConfigNoCrc->CleanMemory        = FspmUpd->FspmConfig.CleanMemory;

  //
  // Update ConfigBlock: MemConfig
  //
  MemConfig->SmramMask               = FspmUpd->FspmConfig.SmramMask;
  MemConfig->DqPinsInterleaved       = FspmUpd->FspmConfig.DqPinsInterleaved;
  MemConfig->MrcFastBoot             = FspmUpd->FspmConfig.MrcFastBoot;
  MemConfig->SaGv                    = FspmUpd->FspmConfig.SaGv;
  MemConfig->DdrFreqLimit            = FspmUpd->FspmConfig.DdrFreqLimit;

  //
  // Enabling Probeless Trace will need to enable IED together
  //
  MemConfig->ProbelessTrace          = FspmUpd->FspmConfig.ProbelessTrace;
  MiscPeiPreMemConfig->IedSize       = FspmUpd->FspmConfig.IedSize;
  MemConfig->CaVrefConfig            = FspmUpd->FspmConfig.CaVrefConfig;
  MemConfig->RMT                     = FspmUpd->FspmConfig.RMT;
  MiscPeiPreMemConfig->UserBd        = FspmUpd->FspmConfig.UserBd;

#ifdef SSA_FLAG
  //
  // Copy Test Content Pointers and Configuration for MMA Testing.
  //
  MemConfigNoCrc->MmaTestContentPtr  = FspmUpd->FspmConfig.MmaTestContentPtr;
  MemConfigNoCrc->MmaTestContentSize = FspmUpd->FspmConfig.MmaTestContentSize;
  MemConfigNoCrc->MmaTestConfigPtr   = FspmUpd->FspmConfig.MmaTestConfigPtr;
  MemConfigNoCrc->MmaTestConfigSize  = FspmUpd->FspmConfig.MmaTestConfigSize;
#endif

  MemConfig->SpdProfileSelected = FspmUpd->FspmConfig.SpdProfileSelected;
  MemConfig->VddVoltage         = FspmUpd->FspmConfig.VddVoltage;
  MemConfig->RefClk             = FspmUpd->FspmConfig.RefClk;
  MemConfig->Ratio              = FspmUpd->FspmConfig.Ratio;
  MemConfig->OddRatioMode       = FspmUpd->FspmConfig.OddRatioMode;
  MemConfig->tCL                = FspmUpd->FspmConfig.tCL;
  MemConfig->tCWL               = FspmUpd->FspmConfig.tCWL;
  MemConfig->tFAW               = FspmUpd->FspmConfig.tFAW;
  MemConfig->tRAS               = FspmUpd->FspmConfig.tRAS;
  MemConfig->tRCDtRP            = FspmUpd->FspmConfig.tRCDtRP;
  MemConfig->tREFI              = FspmUpd->FspmConfig.tREFI;
  MemConfig->tRFC               = FspmUpd->FspmConfig.tRFC;
  MemConfig->tRRD               = FspmUpd->FspmConfig.tRRD;
  MemConfig->tRTP               = FspmUpd->FspmConfig.tRTP;
  MemConfig->tWR                = FspmUpd->FspmConfig.tWR;
  MemConfig->tWTR               = FspmUpd->FspmConfig.tWTR;
  MemConfig->NModeSupport       = FspmUpd->FspmConfig.NModeSupport;
  MemConfig->DllBwEn0           = FspmUpd->FspmConfig.DllBwEn0;
  MemConfig->DllBwEn1           = FspmUpd->FspmConfig.DllBwEn1;
  MemConfig->DllBwEn2           = FspmUpd->FspmConfig.DllBwEn2;
  MemConfig->DllBwEn3           = FspmUpd->FspmConfig.DllBwEn3;
  MemConfig->CmdTriStateDis     = FspmUpd->FspmConfig.CmdTriStateDis;
  MemConfig->EvLoader           = FspmUpd->FspmConfig.EvLoader;

  //
  // Update ConfigBlock:GtPreMemConfig
  //
  if (GtPreMemConfig != NULL) {
    GtPreMemConfig->IgdDvmt50PreAlloc = FspmUpd->FspmConfig.IgdDvmt50PreAlloc;
    GtPreMemConfig->InternalGraphics = FspmUpd->FspmConfig.InternalGfx;
    GtPreMemConfig->ApertureSize = FspmUpd->FspmConfig.ApertureSize;
    GtPreMemConfig->PrimaryDisplay = FspmUpd->FspmConfig.PrimaryDisplay;
    GtPreMemConfig->GttMmAdr = FspmUpd->FspmConfig.GttMmAdr;
    GtPreMemConfig->GttSize = FspmUpd->FspmConfig.GttSize;
    GtPreMemConfig->PanelPowerEnable = FspmUpd->FspmTestConfig.PanelPowerEnable;
  }

  if (SgGpioData != NULL) {
    CopyMem(&SgGpioData->SaRtd3Pcie0Gpio, (VOID *)FspmUpd->FspmConfig.SaRtd3Pcie0Gpio, sizeof (SA_PCIE_RTD3_GPIO));
    CopyMem(&SgGpioData->SaRtd3Pcie1Gpio, (VOID *)FspmUpd->FspmConfig.SaRtd3Pcie1Gpio, sizeof (SA_PCIE_RTD3_GPIO));
    CopyMem(&SgGpioData->SaRtd3Pcie2Gpio, (VOID *)FspmUpd->FspmConfig.SaRtd3Pcie2Gpio, sizeof (SA_PCIE_RTD3_GPIO));
    SgGpioData->RootPortDev = FspmUpd->FspmConfig.RootPortDev;
    SgGpioData->RootPortFun = FspmUpd->FspmConfig.RootPortFun;
  }


  //
  // Update ConfigBlock: MiscPeiPreMemConfig
  //
  if (MiscPeiPreMemConfig != NULL) {
    MiscPeiPreMemConfig->SgDelayAfterPwrEn = FspmUpd->FspmConfig.SgDelayAfterPwrEn;
    MiscPeiPreMemConfig->SgDelayAfterHoldReset = FspmUpd->FspmConfig.SgDelayAfterHoldReset;
    MiscPeiPreMemConfig->MmioSizeAdjustment = FspmUpd->FspmConfig.MmioSizeAdjustment;
    MiscPeiPreMemConfig->MmioSize = FspmUpd->FspmConfig.MmioSize;
    MiscPeiPreMemConfig->TsegSize = FspmUpd->FspmConfig.TsegSize;
    MiscPeiPreMemConfig->S3DataPtr = FspmUpdDataPtr->FspmArchUpd.NvsBufferPtr;
    MiscPeiPreMemConfig->TxtImplemented = 0; // Currently TXT is not ready for FSP Wrapper. MiscPeiPreMemConfig->TxtImplemented = FspmUpd->TxtImplemented;
    MiscPeiPreMemConfig->SkipExtGfxScan = FspmUpd->FspmTestConfig.SkipExtGfxScan;
    MiscPeiPreMemConfig->BdatEnable = FspmUpd->FspmTestConfig.BdatEnable;
    MiscPeiPreMemConfig->ScanExtGfxForLegacyOpRom = FspmUpd->FspmTestConfig.ScanExtGfxForLegacyOpRom;
    MiscPeiPreMemConfig->LockPTMregs = FspmUpd->FspmTestConfig.LockPTMregs;

    //
    // Initialize the Switchable Graphics Configuration
    //
    if (GtPreMemConfig != NULL) {
      if (GtPreMemConfig->PrimaryDisplay == 4) {
        ///
        /// In Switchable Gfx mode PCIe needs to be always enabled and IGFX must be set as Primary Display.
        ///
        MiscPeiPreMemConfig->SgMode = 2;
        MiscPeiPreMemConfig->SgSubSystemId = 0x2112;
        GtPreMemConfig->PrimaryDisplay = 0;
      } else if (GtPreMemConfig->PrimaryDisplay == 0) {
        ///
        /// In IGFX only mode mode set Switchable Gfx mode as Disabled
        ///
        MiscPeiPreMemConfig->SgMode = 0;
        MiscPeiPreMemConfig->SgSubSystemId = 0x2212;
      } else {
        ///
        /// In PEG/PCI/Auto mode set Switchable Gfx mode as dGPU
        ///
        MiscPeiPreMemConfig->SgMode = 3;
        MiscPeiPreMemConfig->SgSubSystemId = 0x2212;
      }
    }

  }


  if (PciePeiPreMemConfig != NULL) {
    PciePeiPreMemConfig->DmiGen3ProgramStaticEq = FspmUpd->FspmConfig.DmiGen3ProgramStaticEq;
    PciePeiPreMemConfig->Peg0Enable = FspmUpd->FspmConfig.Peg0Enable;
    PciePeiPreMemConfig->Peg1Enable = FspmUpd->FspmConfig.Peg1Enable;
    PciePeiPreMemConfig->Peg2Enable = FspmUpd->FspmConfig.Peg2Enable;
    PciePeiPreMemConfig->Peg0MaxLinkSpeed = FspmUpd->FspmConfig.Peg0MaxLinkSpeed;
    PciePeiPreMemConfig->Peg1MaxLinkSpeed = FspmUpd->FspmConfig.Peg1MaxLinkSpeed;
    PciePeiPreMemConfig->Peg2MaxLinkSpeed = FspmUpd->FspmConfig.Peg2MaxLinkSpeed;
    PciePeiPreMemConfig->Peg0MaxLinkWidth = FspmUpd->FspmConfig.Peg0MaxLinkWidth;
    PciePeiPreMemConfig->Peg1MaxLinkWidth = FspmUpd->FspmConfig.Peg1MaxLinkWidth;
    PciePeiPreMemConfig->Peg2MaxLinkWidth = FspmUpd->FspmConfig.Peg2MaxLinkWidth;
    PciePeiPreMemConfig->Peg0PowerDownUnusedLanes = FspmUpd->FspmConfig.Peg0PowerDownUnusedLanes;
    PciePeiPreMemConfig->Peg1PowerDownUnusedLanes = FspmUpd->FspmConfig.Peg1PowerDownUnusedLanes;
    PciePeiPreMemConfig->Peg2PowerDownUnusedLanes = FspmUpd->FspmConfig.Peg2PowerDownUnusedLanes;
    PciePeiPreMemConfig->InitPcieAspmAfterOprom = FspmUpd->FspmConfig.InitPcieAspmAfterOprom;
    PciePeiPreMemConfig->PegDisableSpreadSpectrumClocking = FspmUpd->FspmConfig.PegDisableSpreadSpectrumClocking;
    for (Index = 0; Index < SA_DMI_MAX_LANE; Index++) {
      PciePeiPreMemConfig->DmiGen3RootPortPreset[Index] = FspmUpd->FspmConfig.DmiGen3RootPortPreset[Index];
      PciePeiPreMemConfig->DmiGen3EndPointPreset[Index] = FspmUpd->FspmConfig.DmiGen3EndPointPreset[Index];
      PciePeiPreMemConfig->DmiGen3EndPointHint[Index] = FspmUpd->FspmConfig.DmiGen3EndPointHint[Index];
    }
    for (Index = 0; Index < SA_DMI_MAX_BUNDLE; Index++) {
      PciePeiPreMemConfig->DmiGen3RxCtlePeaking[Index] = FspmUpd->FspmConfig.DmiGen3RxCtlePeaking[Index];
    }
    for (Index = 0; Index < SA_DMI_MAX_BUNDLE; Index++) {
      PciePeiPreMemConfig->PegGen3RxCtlePeaking[Index] = FspmUpd->FspmConfig.PegGen3RxCtlePeaking[Index];
    }
    PciePeiPreMemConfig->PegDataPtr = (VOID *) FspmUpd->FspmConfig.PegDataPtr;
    CopyMem(&PciePeiPreMemConfig->PegGpioData, (VOID *)FspmUpd->FspmConfig.PegGpioData, sizeof (PEG_GPIO_DATA));
    PciePeiPreMemConfig->DmiDeEmphasis = FspmUpd->FspmConfig.DmiDeEmphasis;

    for (Index = 0; Index < SA_PEG_MAX_FUN; Index++) {
      PciePeiPreMemConfig->PegRootPortHPE[Index] = FspmUpd->FspmConfig.PegRootPortHPE[Index];
    }

    PciePeiPreMemConfig->DmiVc1 = FspmUpd->FspmTestConfig.DmiVc1;
    PciePeiPreMemConfig->DmiVcm = FspmUpd->FspmTestConfig.DmiVcm;
    PciePeiPreMemConfig->DmiMaxLinkSpeed = FspmUpd->FspmTestConfig.DmiMaxLinkSpeed;
    PciePeiPreMemConfig->DmiGen3EqPh2Enable = FspmUpd->FspmTestConfig.DmiGen3EqPh2Enable;
    PciePeiPreMemConfig->DmiGen3EqPh3Method = FspmUpd->FspmTestConfig.DmiGen3EqPh3Method;
    PciePeiPreMemConfig->Peg0Gen3EqPh2Enable = FspmUpd->FspmTestConfig.Peg0Gen3EqPh2Enable;
    PciePeiPreMemConfig->Peg1Gen3EqPh2Enable = FspmUpd->FspmTestConfig.Peg1Gen3EqPh2Enable;
    PciePeiPreMemConfig->Peg2Gen3EqPh2Enable = FspmUpd->FspmTestConfig.Peg2Gen3EqPh2Enable;
    PciePeiPreMemConfig->Peg0Gen3EqPh3Method = FspmUpd->FspmTestConfig.Peg0Gen3EqPh3Method;
    PciePeiPreMemConfig->Peg1Gen3EqPh3Method = FspmUpd->FspmTestConfig.Peg1Gen3EqPh3Method;
    PciePeiPreMemConfig->Peg2Gen3EqPh3Method = FspmUpd->FspmTestConfig.Peg2Gen3EqPh3Method;
    PciePeiPreMemConfig->PegGen3ProgramStaticEq = FspmUpd->FspmTestConfig.PegGen3ProgramStaticEq;
    PciePeiPreMemConfig->Gen3SwEqAlwaysAttempt = FspmUpd->FspmTestConfig.Gen3SwEqAlwaysAttempt;
    PciePeiPreMemConfig->Gen3SwEqNumberOfPresets = FspmUpd->FspmTestConfig.Gen3SwEqNumberOfPresets;
    PciePeiPreMemConfig->Gen3SwEqEnableVocTest = FspmUpd->FspmTestConfig.Gen3SwEqEnableVocTest;
    PciePeiPreMemConfig->PegRxCemTestingMode = FspmUpd->FspmTestConfig.PegRxCemTestingMode;
    PciePeiPreMemConfig->PegRxCemLoopbackLane = FspmUpd->FspmTestConfig.PegRxCemLoopbackLane;
    PciePeiPreMemConfig->PegGenerateBdatMarginTable = FspmUpd->FspmTestConfig.PegGenerateBdatMarginTable;
    PciePeiPreMemConfig->PegRxCemNonProtocolAwareness = FspmUpd->FspmTestConfig.PegRxCemNonProtocolAwareness;
    PciePeiPreMemConfig->PegGen3RxCtleOverride = FspmUpd->FspmTestConfig.PegGen3RxCtleOverride;
    for (Index = 0; Index < SA_PEG_MAX_LANE; Index++) {
      PciePeiPreMemConfig->PegGen3RootPortPreset[Index] = FspmUpd->FspmTestConfig.PegGen3RootPortPreset[Index];
      PciePeiPreMemConfig->PegGen3EndPointPreset[Index] = FspmUpd->FspmTestConfig.PegGen3EndPointPreset[Index];
      PciePeiPreMemConfig->PegGen3EndPointHint[Index] = FspmUpd->FspmTestConfig.PegGen3EndPointHint[Index];
    }
    PciePeiPreMemConfig->Gen3SwEqJitterDwellTime = FspmUpd->FspmTestConfig.Gen3SwEqJitterDwellTime;
    PciePeiPreMemConfig->Gen3SwEqJitterErrorTarget = FspmUpd->FspmTestConfig.Gen3SwEqJitterErrorTarget;
    PciePeiPreMemConfig->Gen3SwEqVocDwellTime = FspmUpd->FspmTestConfig.Gen3SwEqVocDwellTime;
    PciePeiPreMemConfig->Gen3SwEqVocErrorTarget = FspmUpd->FspmTestConfig.Gen3SwEqVocErrorTarget;

  }


  //
  // Initialize the Overclocking Configuration
  //
  if (OcPreMemConfig != NULL) {
    OcPreMemConfig->OcSupport = FspmUpd->FspmConfig.SaOcSupport;
    OcPreMemConfig->GtsVoltageMode = FspmUpd->FspmConfig.GtsVoltageMode;
    OcPreMemConfig->GtusVoltageMode = FspmUpd->FspmConfig.GtusVoltageMode;
    OcPreMemConfig->GtsMaxOcRatio = FspmUpd->FspmConfig.GtsMaxOcRatio;
    OcPreMemConfig->GtsVoltageOffset = FspmUpd->FspmConfig.GtsVoltageOffset;
    OcPreMemConfig->GtsVoltageOverride = FspmUpd->FspmConfig.GtsVoltageOverride;
    OcPreMemConfig->GtsExtraTurboVoltage = FspmUpd->FspmConfig.GtsExtraTurboVoltage;
    OcPreMemConfig->GtusVoltageOffset = FspmUpd->FspmConfig.GtusVoltageOffset;
    OcPreMemConfig->GtusVoltageOverride = FspmUpd->FspmConfig.GtusVoltageOverride;
    OcPreMemConfig->GtusExtraTurboVoltage = FspmUpd->FspmConfig.GtusExtraTurboVoltage;
    OcPreMemConfig->SaVoltageOffset = FspmUpd->FspmConfig.SaVoltageOffset;
    OcPreMemConfig->GtusMaxOcRatio = FspmUpd->FspmConfig.GtusMaxOcRatio;
  }
  return EFI_SUCCESS;
}
