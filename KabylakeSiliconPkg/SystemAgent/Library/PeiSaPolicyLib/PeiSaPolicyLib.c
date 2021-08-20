/** @file
  This file provides services for PEI policy default initialization

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2020 Intel Corporation.

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
#include "PeiSaPolicyLibrary.h"
#include <Library/GpioLib.h>
#include <GpioPinsSklH.h>
#include <Library/CpuPlatformLib.h>
#include <MrcTypes.h>
#include "MrcInterface.h"


extern EFI_GUID gSaMiscPeiPreMemConfigGuid;
extern EFI_GUID gMemoryConfigGuid;
extern EFI_GUID gMemoryConfigNoCrcGuid;
extern EFI_GUID gGraphicsPeiConfigGuid;
//
// AdvancedFeaturesBegin
//
extern EFI_GUID gSaPciePeiConfigGuid;
extern EFI_GUID gSaPciePeiPreMemConfigGuid;
extern EFI_GUID gGraphicsPeiPreMemConfigGuid;
extern EFI_GUID gSwitchableGraphicsConfigGuid;
extern EFI_GUID gSkyCamConfigGuid;
extern EFI_GUID gGmmConfigGuid;
extern EFI_GUID gVtdConfigGuid;
extern EFI_GUID gSaOverclockingPreMemConfigGuid;

#define DEFAULT_OPTION_ROM_TEMP_BAR            0x80000000
#define DEFAULT_OPTION_ROM_TEMP_MEM_LIMIT      0xC0000000
//
// AdvancedFeaturesEnd
//

//
// Function call to Load defaults for Individial IP Blocks
//
VOID
LoadSaMiscPeiPreMemDefault (
  IN   VOID          *ConfigBlockPointer
  )
{
  SA_MISC_PEI_PREMEM_CONFIG            *MiscPeiPreMemConfig;

  MiscPeiPreMemConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "MiscPeiPreMemConfig->Header.GuidHob.Name = %g\n", &MiscPeiPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "MiscPeiPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", MiscPeiPreMemConfig->Header.GuidHob.Header.HobLength));
#ifndef MINTREE_FLAG
  //
  // Policy initialization commented out here is because it's the same with default 0 and no need to re-do again.
  //
  MiscPeiPreMemConfig->LockPTMregs                      = 1;

  //
  // Initialize the Platform Configuration
  //
  MiscPeiPreMemConfig->MchBar              = (UINT32) PcdGet64 (PcdMchBaseAddress);
  MiscPeiPreMemConfig->DmiBar              = 0xFED18000;
  MiscPeiPreMemConfig->EpBar               = 0xFED19000;
  MiscPeiPreMemConfig->EdramBar            = 0xFED80000;
  MiscPeiPreMemConfig->SmbusBar            = PcdGet16 (PcdSmbusBaseAddress);
  MiscPeiPreMemConfig->TsegSize            = PcdGet32 (PcdTsegSize);
  MiscPeiPreMemConfig->GdxcBar             = 0xFED84000;
  //
  // Initialize the Switchable Graphics Default Configuration
  //
  MiscPeiPreMemConfig->SgDelayAfterHoldReset  = 100; //100ms
  MiscPeiPreMemConfig->SgDelayAfterPwrEn      = 300; //300ms
//
// KblGBegin
//
  MiscPeiPreMemConfig->SgDelayAfterOffMethod  = 0;
  MiscPeiPreMemConfig->SgDelayAfterLinkEnable = 0;
  MiscPeiPreMemConfig->SgGenSpeedChangeEnable = 0;
//
// KblGEnd
//
  ///
  /// Initialize the DataPtr for S3 resume
  ///
  MiscPeiPreMemConfig->S3DataPtr = NULL;
  MiscPeiPreMemConfig->OpRomScanTempMmioBar      = DEFAULT_OPTION_ROM_TEMP_BAR;
  MiscPeiPreMemConfig->OpRomScanTempMmioLimit    = DEFAULT_OPTION_ROM_TEMP_MEM_LIMIT;
#endif //MINTREE_FLAG
}

#ifndef MINTREE_FLAG
VOID
LoadSaMiscPeiDefault (
  IN   VOID          *ConfigBlockPointer
  )
{
  SA_MISC_PEI_CONFIG        *MiscPeiConfig;

  MiscPeiConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "MiscPeiConfig->Header.GuidHob.Name = %g\n", &MiscPeiConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "MiscPeiConfig->Header.GuidHob.Header.HobLength = 0x%x\n", MiscPeiConfig->Header.GuidHob.Header.HobLength));
  //
  // Policy initialization commented out here is because it's the same with default 0 and no need to re-do again.
  //
  //
  // Initialize the Svid Configuration
  //
  MiscPeiConfig->DefaultSvidSid.SubSystemVendorId = V_SA_MC_VID;
  MiscPeiConfig->DefaultSvidSid.SubSystemId = 0x2015;
  ///
  /// EDRAM H/W Mode by default (0- EDRAM SW Disable, 1- EDRAM SW Enable, 2- EDRAM HW Mode)
  ///
  MiscPeiConfig->EdramTestMode = 2;
}

VOID
LoadVtdDefault (
  IN VOID   *ConfigBlockPointer
  )
{
  VTD_CONFIG   *Vtd;

  Vtd = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "Vtd->Header.GuidHob.Name = %g\n", &Vtd->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "Vtd->Header.GuidHob.Header.HobLength = 0x%x\n", Vtd->Header.GuidHob.Header.HobLength));

  //
  // Initialize the Vtd Configuration
  //
  Vtd->BaseAddress[0]  = 0xFED90000;
  Vtd->BaseAddress[1]  = 0xFED91000;
}

VOID
LoadSkyCamDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  SKYCAM_CONFIG      *SkyCamPolicy;

  SkyCamPolicy = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "SkyCamPolicy->Header.GuidHob.Name = %g\n", &SkyCamPolicy->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "SkyCamPolicy->Header.GuidHob.Header.HobLength = 0x%x\n", SkyCamPolicy->Header.GuidHob.Header.HobLength));

  SkyCamPolicy->SaImguEnable = TRUE;
}

VOID
LoadPciePeiPreMemDefault (
  IN   VOID          *ConfigBlockPointer
  )
{
  UINT8                  Index;
  PCIE_PEI_PREMEM_CONFIG *PciePeiPreMemConfig;

  PciePeiPreMemConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "PciePeiPreMemConfig->Header.GuidHob.Name = %g\n", &PciePeiPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "PciePeiPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", PciePeiPreMemConfig->Header.GuidHob.Header.HobLength));

  //
  // Initialize the PciExpress Configuration
  //
  PciePeiPreMemConfig->DmiVcm                         = 1;
  PciePeiPreMemConfig->DmiGen3EqPh2Enable             = 2;
  PciePeiPreMemConfig->DmiGen3ProgramStaticEq         = 1;
  PciePeiPreMemConfig->Peg0Enable                     = 2;
  PciePeiPreMemConfig->Peg1Enable                     = 2;
  PciePeiPreMemConfig->Peg2Enable                     = 2;
  PciePeiPreMemConfig->Peg0PowerDownUnusedLanes       = 1;
  PciePeiPreMemConfig->Peg1PowerDownUnusedLanes       = 1;
  PciePeiPreMemConfig->Peg2PowerDownUnusedLanes       = 1;
  PciePeiPreMemConfig->Peg0Gen3EqPh2Enable            = 2;
  PciePeiPreMemConfig->Peg1Gen3EqPh2Enable            = 2;
  PciePeiPreMemConfig->Peg2Gen3EqPh2Enable            = 2;
  PciePeiPreMemConfig->PegGen3ProgramStaticEq         = 1;
  PciePeiPreMemConfig->Gen3SwEqNumberOfPresets        = 2;
  PciePeiPreMemConfig->Gen3SwEqEnableVocTest          = 2;

  for (Index = 0; Index < SA_DMI_MAX_LANE; Index++) {
    PciePeiPreMemConfig->DmiGen3RootPortPreset[Index] = 4;
    PciePeiPreMemConfig->DmiGen3EndPointPreset[Index] = 7;
    PciePeiPreMemConfig->DmiGen3EndPointHint[Index]   = 2;
  }
  for (Index = 0; Index < SA_DMI_MAX_BUNDLE; Index++) {
    ///
    /// Gen3 RxCTLE peaking default is 0 for DMI
    ///
    PciePeiPreMemConfig->DmiGen3RxCtlePeaking[Index]  = 3;
  }
  for (Index = 0; Index < SA_PEG_MAX_LANE; Index++) {
    PciePeiPreMemConfig->PegGen3RootPortPreset[Index] = 7;
    PciePeiPreMemConfig->PegGen3EndPointPreset[Index] = 7;
    PciePeiPreMemConfig->PegGen3EndPointHint[Index]   = 2;
  }
  PciePeiPreMemConfig->DmiDeEmphasis = 1;
  ///
  /// Gen3 Software Equalization Jitter Dwell Time:               1 msec
  /// Gen3 Software Equalization Jitter Error Target:             1
  /// Gen3 Software Equalization VOC    Dwell Time:               10 msec
  /// Gen3 Software Equalization VOC    Error Target:             2
  ///
  PciePeiPreMemConfig->Gen3SwEqJitterDwellTime        = 3 * STALL_ONE_MILLI_SECOND;
  PciePeiPreMemConfig->Gen3SwEqJitterErrorTarget      = 2;
  PciePeiPreMemConfig->Gen3SwEqVocDwellTime           = 10 * STALL_ONE_MILLI_SECOND;
  PciePeiPreMemConfig->Gen3SwEqVocErrorTarget         = 2;

  /**
  Parameters for PCIe Gen3 device reset
  @note Refer to the Platform Design Guide (PDG) for additional information about this GPIO.
  **/
  PciePeiPreMemConfig->PegGpioData.GpioSupport        = TRUE;
  PciePeiPreMemConfig->PegGpioData.SaPegReset.GpioPad = GPIO_SKL_H_GPP_F22;

  //
  // KblGBegin
  //
  if (IsKblGPackage()) {
    //
    // Initialize the PciExpress Configuration for G Pkg
    //
    DEBUG ((DEBUG_INFO, "Pcie dGPU Config for KBLG\n"));

    // Enable Peg0 and set Peg1 and Peg2 to Auto
    PciePeiPreMemConfig->Peg0Enable                     = 1;

    // Disable hot plug for function 0
    PciePeiPreMemConfig->PegRootPortHPE[0] = 0;

    // Program the first PEG0 lanes : RootPort Preset 4,  EndPoint Preset 6, EndPoint Hint Value 6
    for (Index = 0; Index < (SA_PEG_MAX_LANE/2); Index++) {
      PciePeiPreMemConfig->PegGen3RootPortPreset[Index] = 4;
      PciePeiPreMemConfig->PegGen3EndPointPreset[Index] = 6;
      PciePeiPreMemConfig->PegGen3EndPointHint[Index]   = 6;      
    }
  }
  //
  // KblGEnd
  //
}

VOID
LoadPciePeiDefault (
  IN   VOID          *ConfigBlockPointer
  )
{
  UINT8                Index;
  PCIE_PEI_CONFIG      *PciePeiConfig;

  PciePeiConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "PciePeiConfig->Header.GuidHob.Name = %g\n", &PciePeiConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "PciePeiConfig->Header.GuidHob.Header.HobLength = 0x%x\n", PciePeiConfig->Header.GuidHob.Header.HobLength));

  // Initialize the PciExpress Configuration
  //
  for (Index = 0; Index < SA_PEG_MAX_FUN; Index++) {
    PciePeiConfig->PegDeEmphasis[Index] = 1;
    PciePeiConfig->PegMaxPayload[Index] = 0xFF;
  }
  ///
  /// Slot Power Limit Value:   75 W
  /// Slot Power Limit Scale:   1.0x
  /// Physical Slot Number:     Peg Index + 1 (1,2,3)
  ///
  for (Index = 0; Index < SA_PEG_MAX_FUN; Index++) {
    PciePeiConfig->PegSlotPowerLimitValue[Index] = 75;
    PciePeiConfig->PegPhysicalSlotNumber[Index] =  Index + 1;
  }

}

VOID
LoadGraphichsPeiPreMemDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  GRAPHICS_PEI_PREMEM_CONFIG                         *GtPreMemConfig;

  GtPreMemConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "GtPreMemConfig->Header.GuidHob.Name = %g\n", &GtPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "GtPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", GtPreMemConfig->Header.GuidHob.Header.HobLength));
  ///
  /// Initialize GttSize for SKL to 8MB
  ///
  GtPreMemConfig->GttMmAdr            = 0xDF000000;
  GtPreMemConfig->GmAdr               = 0xC0000000;
  GtPreMemConfig->GttSize             = 3;
  GtPreMemConfig->IgdDvmt50PreAlloc   = 1;
  GtPreMemConfig->InternalGraphics    = 2;
  GtPreMemConfig->PrimaryDisplay      = 3;
  GtPreMemConfig->ApertureSize        = SA_GT_APERTURE_SIZE_256MB;
  GtPreMemConfig->PanelPowerEnable    = 1;
}
#endif //MINTREE_FLAG

VOID
LoadGraphichsPeiDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  GRAPHICS_PEI_CONFIG                         *GtConfig;

  GtConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "GtConfig->Header.GuidHob.Name = %g\n", &GtConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "GtConfig->Header.GuidHob.Header.HobLength = 0x%x\n", GtConfig->Header.GuidHob.Header.HobLength));
#ifndef MINTREE_FLAG
  //
  // Initialize the Graphics configuration
  //
  GtConfig->RenderStandby       = 1;
  GtConfig->PavpEnable          = 1;
  GtConfig->PmSupport           = 1;
  GtConfig->CdynmaxClampEnable  = 1;
  GtConfig->GtFreqMax           = 0xFF;
  //
  // disable RC6 if GT PM is disabled
  //
  if (GtConfig->PmSupport == 0) {
    GtConfig->RenderStandby = 0;
  }
  ///
  /// Initialize the CdClock to 675 Mhz
  ///
  GtConfig->CdClock             = 3;
  GtConfig->ProgramGtChickenBits = (UINT32) (BIT3 | BIT2 | BIT1);
#endif //MINTREE_FLAG
}
#ifndef MINTREE_FLAG
VOID
LoadSwitchableGraphichsDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  SWITCHABLE_GRAPHICS_CONFIG        *SgConfig;
  SgConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "SgConfig->Header.GuidHob.Name = %g\n", &SgConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "SgConfig->Header.GuidHob.Header.HobLength = 0x%x\n", SgConfig->Header.GuidHob.Header.HobLength));
}
#endif //MINTREE_FLAG

VOID
LoadMemConfigNoCrcDefault (
  IN VOID    *ConfigBlockPointer
  )
{

  MEMORY_CONFIG_NO_CRC                    *MemConfigNoCrc;

  MemConfigNoCrc = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "MemConfigNoCrc->Header.GuidHob.Name = %g\n", &MemConfigNoCrc->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "MemConfigNoCrc->Header.GuidHob.Header.HobLength = 0x%x\n", MemConfigNoCrc->Header.GuidHob.Header.HobLength));
  //
  // Allocating memory space for pointer structures inside MemConfigNoCrc
  //
  MemConfigNoCrc->SpdData = (SPD_DATA_BUFFER *) AllocateZeroPool (sizeof (SPD_DATA_BUFFER));
  ASSERT (MemConfigNoCrc->SpdData != NULL);
  if (MemConfigNoCrc->SpdData == NULL) {
    return;
  }

  MemConfigNoCrc->DqByteMap = (SA_MEMORY_DQ_MAPPING *) AllocateZeroPool (sizeof (SA_MEMORY_DQ_MAPPING));
  ASSERT (MemConfigNoCrc->DqByteMap != NULL);
  if (MemConfigNoCrc->DqByteMap == NULL) {
    return;
  }

  MemConfigNoCrc->DqsMap = (SA_MEMORY_DQS_MAPPING *) AllocateZeroPool (sizeof (SA_MEMORY_DQS_MAPPING));
  ASSERT (MemConfigNoCrc->DqsMap != NULL);
  if (MemConfigNoCrc->DqsMap == NULL) {
    return;
  }

  MemConfigNoCrc->RcompData = (SA_MEMORY_RCOMP *) AllocateZeroPool (sizeof (SA_MEMORY_RCOMP));
  ASSERT (MemConfigNoCrc->RcompData != NULL);
  if (MemConfigNoCrc->RcompData == NULL) {
    return;
  }

  //
  // Set PlatformMemory Size
  //
  MemConfigNoCrc->PlatformMemorySize = PcdGet32 (PcdPeiMinMemorySize);

  MemConfigNoCrc->SerialDebugLevel  = 3;  //< Enable MRC debug message

}

#ifndef MINTREE_FLAG
VOID
LoadGmmDefault (
  IN VOID *ConfigBlockPointer
  )
{
  GMM_CONFIG                        *GmmConfig;
  GmmConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "GmmConfig->Header.GuidHob.Name = %g\n", &GmmConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "GmmConfig->Header.GuidHob.Header.HobLength = 0x%x\n", GmmConfig->Header.GuidHob.Header.HobLength));
  GmmConfig->GmmEnable    = TRUE;
}
#endif //MINTREE_FLAG

VOID
LoadMemConfigDefault (
  IN VOID *ConfigBlockPointer
  )
{
  MEMORY_CONFIGURATION                    *MemConfig;
  CPU_SKU                                 CpuSku;
  UINT16                                  DeviceId;
  BOOLEAN                                 HasEdram;

  CpuSku = GetCpuSku ();
  DeviceId    = MmioRead16 (MmPciBase (SA_MC_BUS, 0, 0) + R_SA_MC_DEVICE_ID);
  HasEdram    = ((AsmReadMsr64 (MSR_PLATFORM_INFO) & B_PLATFORM_INFO_EDRAM_EN) != 0);


  MemConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "MemConfig->Header.GuidHob.Name = %g\n", &MemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "MemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", MemConfig->Header.GuidHob.Header.HobLength));
  //
  // Initialize the Memory Configuration
  //
  MemConfig->EccSupport         = 1;
  MemConfig->ScramblerSupport   = 1;
  MemConfig->PowerDownMode      = 0xFF;
  MemConfig->RankInterleave     = TRUE;
  MemConfig->EnhancedInterleave = TRUE;
  MemConfig->CmdTriStateDis     = 0;
  MemConfig->EnCmdRate          = 3;
  MemConfig->AutoSelfRefreshSupport = TRUE;
  MemConfig->ExtTemperatureSupport  = TRUE;
  MemConfig->Ddr4MixedUDimm2DpcLimit = 0;

  //
  // Thermal Management Configuration
  //
  MemConfig->ThermalManagement  = 1;
  //
  // Channel Hash Configuration
  //
  MemConfig->ChHashEnable         = TRUE;
  MemConfig->ChHashMask           = ((CpuSku == EnumCpuUlt) && (HasEdram)) ? 0x30D0 : 0x30C8;
  MemConfig->ChHashInterleaveBit  = 2;
  //
  // Options for Thermal settings
  //
  MemConfig->EnablePwrDn            = 1;
  MemConfig->EnablePwrDnLpddr       = 1;
  MemConfig->DdrThermalSensor     = 1;

  MemConfig->EnergyScaleFact        = 3;
  MemConfig->WarmThresholdCh0Dimm0  = 0xFF;
  MemConfig->WarmThresholdCh0Dimm1  = 0xFF;
  MemConfig->WarmThresholdCh1Dimm0  = 0xFF;
  MemConfig->WarmThresholdCh1Dimm1  = 0xFF;
  MemConfig->HotThresholdCh0Dimm0   = 0xFF;
  MemConfig->HotThresholdCh0Dimm1   = 0xFF;
  MemConfig->HotThresholdCh1Dimm0   = 0xFF;
  MemConfig->HotThresholdCh1Dimm1   = 0xFF;
  MemConfig->WarmBudgetCh0Dimm0     = 0xFF;
  MemConfig->WarmBudgetCh0Dimm1     = 0xFF;
  MemConfig->WarmBudgetCh1Dimm0     = 0xFF;
  MemConfig->WarmBudgetCh1Dimm1     = 0xFF;
  MemConfig->HotBudgetCh0Dimm0      = 0xFF;
  MemConfig->HotBudgetCh0Dimm1      = 0xFF;
  MemConfig->HotBudgetCh1Dimm0      = 0xFF;
  MemConfig->HotBudgetCh1Dimm1      = 0xFF;

  MemConfig->SrefCfgEna             = 1;
  MemConfig->SrefCfgIdleTmr         = 0x200;
  MemConfig->ThrtCkeMinTmr          = 0x30;
  MemConfig->ThrtCkeMinDefeatLpddr = 1;
  MemConfig->ThrtCkeMinTmrLpddr    = 0x40;

  //
  // CA Vref routing: board-dependent
  // 0 - VREF_CA goes to both CH_A and CH_B (LPDDR3/DDR3L)
  // 1 - VREF_CA to CH_A, VREF_DQ_A to CH_B (should not be used)
  // 2 - VREF_CA to CH_A, VREF_DQ_B to CH_B (DDR4)
  //
  //MemConfig->CaVrefConfig = 0;

  MemConfig->VttTermination     = ((CpuSku == EnumCpuUlx) || (CpuSku == EnumCpuUlt));
  MemConfig->VttCompForVsshi    = 1;

  MemConfig->McLock               = TRUE;

  MemConfig->GdxcIotSize          = 4;
  MemConfig->GdxcMotSize          = 12;

  //
  // MRC training steps
  //
  MemConfig->ERDMPRTC2D           = 1;
  MemConfig->SOT                  = 1;
  MemConfig->RDMPRT               = 1;
  MemConfig->RCVET                = 1;
  MemConfig->JWRL                 = 1;
  MemConfig->EWRTC2D              = 1;
  MemConfig->ERDTC2D              = 1;
  MemConfig->WRTC1D               = 1;
  MemConfig->WRVC1D               = 1;
  MemConfig->RDTC1D               = 1;
  MemConfig->DIMMODTT             = 1;
  MemConfig->DIMMRONT             = 1;
  MemConfig->WRSRT                = 1;
  MemConfig->RDODTT               = 1;
  MemConfig->RDEQT                = 1;
  MemConfig->RDAPT                = 1;
  MemConfig->WRTC2D               = 1;
  MemConfig->RDTC2D               = 1;
  MemConfig->CMDVC                = 1;
  MemConfig->WRVC2D               = 1;
  MemConfig->RDVC2D               = 1;
  MemConfig->LCT                  = 1;
  MemConfig->RTL                  = 1;
  MemConfig->TAT                  = 1;
  MemConfig->ALIASCHK             = 1;
  MemConfig->RCVENC1D             = 1;
  MemConfig->RMC                  = 1;
  MemConfig->CMDSR                = 1;
  MemConfig->CMDDSEQ              = 1;
  MemConfig->CMDNORM              = 1;
  MemConfig->EWRDSEQ              = 1;
  MemConfig->TXDQVREF             = 1;

  // MrcFastBoot enabled by default
  MemConfig->MrcFastBoot          = TRUE;
  MemConfig->RemapEnable          = TRUE;
  MemConfig->BClkFrequency        = 100 * 1000 * 1000;

#ifdef EMBEDDED_FLAG
  MemConfig->Force1Dpc = TRUE;
#endif
  MemConfig->Vc1ReadMeter           = TRUE;
  MemConfig->Vc1ReadMeterTimeWindow = 0x320;
  MemConfig->Vc1ReadMeterThreshold  = 0x118;
  MemConfig->StrongWkLeaker         = 7;

  MemConfig->MobilePlatform     = (IS_SA_DEVICE_ID_MOBILE (DeviceId)) ? TRUE : FALSE;
  MemConfig->PciIndex           = 0xCF8;
  MemConfig->PciData            = 0xCFC;
  MemConfig->CkeRankMapping     = 0xAA;
  //
  // SA GV: 0 - Disabled, 1 - FixedLow, 2 - FixedHigh, 3 - Enabled
  //
  //
  // Current Simics will fail in MRC training when SAGV enabled so need to by default disable SAGV.
  //
  MemConfig->SaGv               = 3;  // This only affects ULX/ULT and CPU steppings C0/J0 and above; otherwise SA GV is disabled.

  MemConfig->Idd3n              = 26;
  MemConfig->Idd3p              = 11;

  MemConfig->RhPrevention       = TRUE;         // Row Hammer prevention.
  MemConfig->RhSolution         = HardwareRhp;  // Type of solution to be used for RHP - 0/1 = HardwareRhp/Refresh2x
  MemConfig->RhActProbability   = OneIn2To11;    // Activation probability for Hardware RHP

  MemConfig->LpddrMemWriteLatencySet = 1;  // Enable LPDDR3 WL Set B if supported by DRAM
  MemConfig->EvLoaderDelay           = 1;

  MemConfig->DllBwEn1 = 1;
  MemConfig->DllBwEn2 = 2;
  MemConfig->DllBwEn3 = 2;
  MemConfig->Ddr4SkipRefreshEn = 1;

  MemConfig->RetrainOnFastFail = 1; //  Restart MRC in Cold mode if SW MemTest fails during Fast flow. 0 = Disabled, 1 = Enabled
}

#ifndef MINTREE_FLAG
VOID
LoadOverClockConfigDefault (
  IN VOID   *ConfigBlockPointer
  )
{
  OVERCLOCKING_PREMEM_CONFIG    *OcPreMemConfig;
  OcPreMemConfig = (OVERCLOCKING_PREMEM_CONFIG *)ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "OcPreMemConfig->Header.GuidHob.Name = %g\n", &OcPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "OcPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", OcPreMemConfig->Header.GuidHob.Header.HobLength));
}
#endif //MINTREE_FLAG

#ifndef MINTREE_FLAG
static COMPONENT_BLOCK_ENTRY  mSaIpBlocksPreMem [] = {
  {&gSaMiscPeiPreMemConfigGuid,       sizeof (SA_MISC_PEI_PREMEM_CONFIG),  SA_MISC_PEI_PREMEM_CONFIG_REVISION,     LoadSaMiscPeiPreMemDefault},
  {&gSaPciePeiPreMemConfigGuid,       sizeof (PCIE_PEI_PREMEM_CONFIG),     SA_PCIE_PEI_PREMEM_CONFIG_REVISION,     LoadPciePeiPreMemDefault},
  {&gGraphicsPeiPreMemConfigGuid,     sizeof (GRAPHICS_PEI_PREMEM_CONFIG), GRAPHICS_PEI_PREMEM_CONFIG_REVISION,    LoadGraphichsPeiPreMemDefault},
  {&gSwitchableGraphicsConfigGuid,    sizeof (SWITCHABLE_GRAPHICS_CONFIG), SWITCHABLE_GRAPHICS_CONFIG_REVISION,    LoadSwitchableGraphichsDefault},
  {&gMemoryConfigGuid,                sizeof (MEMORY_CONFIGURATION),       MEMORY_CONFIG_REVISION,                 LoadMemConfigDefault},
  {&gMemoryConfigNoCrcGuid,           sizeof (MEMORY_CONFIG_NO_CRC),       MEMORY_CONFIG_REVISION,                 LoadMemConfigNoCrcDefault},
  {&gSaOverclockingPreMemConfigGuid,  sizeof (OVERCLOCKING_PREMEM_CONFIG), SA_OVERCLOCKING_PREMEM_CONFIG_REVISION, LoadOverClockConfigDefault}
};

static COMPONENT_BLOCK_ENTRY  mSaIpBlocks [] = {
  {&gSaMiscPeiConfigGuid,       sizeof (SA_MISC_PEI_CONFIG),   SA_MISC_PEI_CONFIG_REVISION,      LoadSaMiscPeiDefault},
  {&gSaPciePeiConfigGuid,       sizeof (PCIE_PEI_CONFIG),      SA_PCIE_PEI_CONFIG_REVISION,      LoadPciePeiDefault},
  {&gGraphicsPeiConfigGuid,     sizeof (GRAPHICS_PEI_CONFIG),  GRAPHICS_PEI_CONFIG_REVISION,     LoadGraphichsPeiDefault},
  {&gSkyCamConfigGuid,          sizeof (SKYCAM_CONFIG),        SKYCAM_CONFIG_REVISION,           LoadSkyCamDefault},
  {&gGmmConfigGuid,             sizeof (GMM_CONFIG),           GMM_CONFIG_REVISION,              LoadGmmDefault},
  {&gVtdConfigGuid,             sizeof (VTD_CONFIG),           VTD_CONFIG_REVISION,              LoadVtdDefault}
};
#else
static COMPONENT_BLOCK_ENTRY  mSaIpBlocksPreMem[] = {
  { &gSaMiscPeiPreMemConfigGuid, sizeof(SA_MISC_PEI_PREMEM_CONFIG), SA_MISC_PEI_PREMEM_CONFIG_REVISION, LoadSaMiscPeiPreMemDefault },
  { &gMemoryConfigGuid, sizeof(MEMORY_CONFIGURATION), MEMORY_CONFIG_REVISION, LoadMemConfigDefault },
  { &gMemoryConfigNoCrcGuid, sizeof(MEMORY_CONFIG_NO_CRC), MEMORY_CONFIG_REVISION, LoadMemConfigNoCrcDefault }
};

static COMPONENT_BLOCK_ENTRY  mSaIpBlocks [] = {
  {&gGraphicsPeiConfigGuid,     sizeof (GRAPHICS_PEI_CONFIG),  GRAPHICS_PEI_CONFIG_REVISION,     LoadGraphichsPeiDefault}
};
#endif //MINTREE_FLAG

/**
  Get SA config block table total size.

  @retval     Size of SA config block table
**/
UINT16
EFIAPI
SaGetConfigBlockTotalSize (
  VOID
  )
{
  return GetComponentConfigBlockTotalSize (&mSaIpBlocks[0], sizeof (mSaIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}

/**
  Get SA config block table total size.

  @retval      Size of SA config block table
**/
UINT16
EFIAPI
SaGetConfigBlockTotalSizePreMem (
  VOID
  )
{
  return GetComponentConfigBlockTotalSize (&mSaIpBlocksPreMem[0], sizeof (mSaIpBlocksPreMem) / sizeof (COMPONENT_BLOCK_ENTRY));
}

/**
  SaAddConfigBlocksPreMem add all SA config blocks.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SaAddConfigBlocksPreMem (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;

  DEBUG ((DEBUG_INFO, "SA AddConfigBlocks. TotalBlockCount = 0x%x\n",  sizeof (mSaIpBlocksPreMem) / sizeof (COMPONENT_BLOCK_ENTRY)));
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mSaIpBlocksPreMem[0], sizeof (mSaIpBlocksPreMem) / sizeof (COMPONENT_BLOCK_ENTRY));
  if (Status == EFI_SUCCESS) {
    SaLoadSamplePolicyPreMem (ConfigBlockTableAddress);
  }
  return Status;
}

/**
  SaAddConfigBlocks add all SA config blocks.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SaAddConfigBlocks (
  IN VOID           *ConfigBlockTableAddress
  )
{
  DEBUG ((DEBUG_INFO, "SA AddConfigBlocks. TotalBlockCount = 0x%x\n",  sizeof (mSaIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY)));

  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mSaIpBlocks[0], sizeof (mSaIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}
