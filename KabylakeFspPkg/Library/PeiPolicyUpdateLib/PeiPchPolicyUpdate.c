/** @file
  This file is SampleCode of the library for Intel PCH PEI Policy initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2019 Intel Corporation.

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
#include <Library/DebugLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/FspCommonLib.h>
#include <FsptUpd.h>
#include <FspsUpd.h>
#include <Library/PchSerialIoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiServicesLib.h>

/**
  This function performs PCH PEI Policy update.

  @param[in, out] SiPolicy      The SI Policy PPI instance
  @param[in]      FspsUpd       The pointer of FspsUpd

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
FspUpdatePeiPchPolicy (
  IN OUT SI_POLICY_PPI     *SiPolicy,
  IN     FSPS_UPD          *FspsUpd
  )
{
  UINTN                        Index;
  UINT8                        NumOfDevIntConfig;
  PCH_DEVICE_INTERRUPT_CONFIG  *DevIntConfg;
  EFI_STATUS                   Status;
  PCH_HDAUDIO_CONFIG           *HdAudioConfig;
  PCH_LAN_CONFIG               *LanConfig;
  PCH_SCS_CONFIG               *ScsConfig;
  PCH_ISH_CONFIG               *IshConfig;
  PCH_SPI_CONFIG               *SpiConfig;
  PCH_SATA_CONFIG              *SataConfig;
  PCH_USB_CONFIG               *UsbConfig;
  PCH_SERIAL_IO_CONFIG         *SerialIoConfig;
  PCH_INTERRUPT_CONFIG         *InterruptConfig;
  PCH_LOCK_DOWN_CONFIG         *LockDownConfig;
  PCH_CIO2_CONFIG              *Cio2Config;
  PCH_PCIE_CONFIG              *PcieRpConfig;
  PCH_DMI_CONFIG               *DmiConfig;
  PCH_FLASH_PROTECTION_CONFIG  *FlashProtectionConfig;
  PCH_IOAPIC_CONFIG            *IoApicConfig;
  PCH_P2SB_CONFIG              *P2sbConfig;
  PCH_GENERAL_CONFIG           *PchGeneralConfig;
  PCH_PM_CONFIG                *PmConfig;
  PCH_PORT61H_SMM_CONFIG       *Port61hConfig;
  PCH_LPC_SIRQ_CONFIG          *PchSerialIrqConfig;
  PCH_THERMAL_CONFIG           *PchThermalConfig;
  FSPT_UPD                     *FsptUpd;
  HYBRID_STORAGE_CONFIG        *HybridStorageConfig;

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "FSP UpdatePeiPchPolicy\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gLanConfigGuid, (VOID *) &LanConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gHdAudioConfigGuid, (VOID *) &HdAudioConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gScsConfigGuid, (VOID *) &ScsConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gIshConfigGuid, (VOID *) &IshConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSpiConfigGuid, (VOID *) &SpiConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSataConfigGuid, (VOID *) &SataConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsbConfigGuid, (VOID *) &UsbConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSerialIoConfigGuid, (VOID *) &SerialIoConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gInterruptConfigGuid, (VOID *) &InterruptConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gLockDownConfigGuid, (VOID *) &LockDownConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gCio2ConfigGuid, (VOID *) &Cio2Config);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPcieRpConfigGuid, (VOID *) &PcieRpConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gDmiConfigGuid, (VOID *) &DmiConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gFlashProtectionConfigGuid, (VOID *) &FlashProtectionConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gIoApicConfigGuid, (VOID *) &IoApicConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gP2sbConfigGuid, (VOID *) &P2sbConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPort61ConfigGuid, (VOID *) &Port61hConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSerialIrqConfigGuid, (VOID *) &PchSerialIrqConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gThermalConfigGuid, (VOID *) &PchThermalConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gHybridStorageConfigGuid, (VOID *) &HybridStorageConfig);
  ASSERT_EFI_ERROR (Status);
  //
  // Get the FSPT UPD pointer.
  //
  FsptUpd = (FSPT_UPD *) GetFspCfgRegionDataPointer ();

  //
  // Update LAN policies
  //
  LanConfig->Enable          = FspsUpd->FspsConfig.PchLanEnable;
  LanConfig->LtrEnable       = FspsUpd->FspsConfig.PchLanLtrEnable;
  LanConfig->K1OffEnable     = FspsUpd->FspsConfig.PchLanK1OffEnable;
  LanConfig->ClkReqSupported = FspsUpd->FspsConfig.PchLanClkReqSupported;
  LanConfig->ClkReqNumber    = FspsUpd->FspsConfig.PchLanClkReqNumber;

  //
  // Update HDA policies
  //
  HdAudioConfig->Enable               = FspsUpd->FspsConfig.PchHdaEnable;
  HdAudioConfig->DspEnable            = FspsUpd->FspsConfig.PchHdaDspEnable;
  HdAudioConfig->IoBufferOwnership    = FspsUpd->FspsConfig.PchHdaIoBufferOwnership;

  HdAudioConfig->Pme                  = FspsUpd->FspsConfig.PchHdaPme;
  HdAudioConfig->IoBufferVoltage      = FspsUpd->FspsConfig.PchHdaIoBufferVoltage;
  HdAudioConfig->VcType               = FspsUpd->FspsConfig.PchHdaVcType;
  HdAudioConfig->HdAudioLinkFrequency = FspsUpd->FspsConfig.PchHdaLinkFrequency;
  HdAudioConfig->IDispLinkFrequency   = FspsUpd->FspsConfig.PchHdaIDispLinkFrequency;
  HdAudioConfig->IDispLinkTmode       = FspsUpd->FspsConfig.PchHdaIDispLinkTmode;
  HdAudioConfig->DspUaaCompliance     = FspsUpd->FspsConfig.PchHdaDspUaaCompliance;
  HdAudioConfig->IDispCodecDisconnect = FspsUpd->FspsConfig.PchHdaIDispCodecDisconnect;
  HdAudioConfig->DspEndpointDmic      = FspsUpd->FspsConfig.PchHdaDspEndpointDmic;
  HdAudioConfig->DspEndpointBluetooth = FspsUpd->FspsConfig.PchHdaDspEndpointBluetooth;
  HdAudioConfig->DspEndpointI2s       = FspsUpd->FspsConfig.PchHdaDspEndpointI2s;
  HdAudioConfig->DspFeatureMask       = FspsUpd->FspsConfig.PchHdaDspFeatureMask;
  HdAudioConfig->ResetWaitTimer       = FspsUpd->FspsTestConfig.PchHdaResetWaitTimer;
  HdAudioConfig->VerbTableEntryNum    = FspsUpd->FspsConfig.PchHdaVerbTableEntryNum;
  HdAudioConfig->VerbTablePtr         = FspsUpd->FspsConfig.PchHdaVerbTablePtr;

  //
  // Update CIO2 policies
  //
  Cio2Config->DeviceEnable = FspsUpd->FspsConfig.PchCio2Enable;
  Cio2Config->SkyCamPortATermOvrEnable = FspsUpd->FspsConfig.PchSkyCamPortATermOvrEnable;
  Cio2Config->SkyCamPortBTermOvrEnable = FspsUpd->FspsConfig.PchSkyCamPortBTermOvrEnable;
  Cio2Config->SkyCamPortCTermOvrEnable = FspsUpd->FspsConfig.PchSkyCamPortCTermOvrEnable;
  Cio2Config->SkyCamPortDTermOvrEnable = FspsUpd->FspsConfig.PchSkyCamPortDTermOvrEnable;
  Cio2Config->PortATrimEnable = FspsUpd->FspsConfig.PchSkyCamPortATrimEnable;
  Cio2Config->PortBTrimEnable = FspsUpd->FspsConfig.PchSkyCamPortBTrimEnable;
  Cio2Config->PortCTrimEnable = FspsUpd->FspsConfig.PchSkyCamPortCTrimEnable;
  Cio2Config->PortDTrimEnable = FspsUpd->FspsConfig.PchSkyCamPortDTrimEnable;
  Cio2Config->PortACtleEnable  = FspsUpd->FspsConfig.PchSkyCamPortACtleEnable;
  Cio2Config->PortBCtleEnable  = FspsUpd->FspsConfig.PchSkyCamPortBCtleEnable;
  Cio2Config->PortCDCtleEnable = FspsUpd->FspsConfig.PchSkyCamPortCDCtleEnable;
  Cio2Config->PortACtleCapValue  = FspsUpd->FspsConfig.PchSkyCamPortACtleCapValue;
  Cio2Config->PortBCtleCapValue  = FspsUpd->FspsConfig.PchSkyCamPortBCtleCapValue;
  Cio2Config->PortCDCtleCapValue = FspsUpd->FspsConfig.PchSkyCamPortCDCtleCapValue;
  Cio2Config->PortACtleResValue  = FspsUpd->FspsConfig.PchSkyCamPortACtleResValue;
  Cio2Config->PortBCtleResValue  = FspsUpd->FspsConfig.PchSkyCamPortBCtleResValue;
  Cio2Config->PortCDCtleResValue = FspsUpd->FspsConfig.PchSkyCamPortCDCtleResValue;
  Cio2Config->PortAClkTrimValue = FspsUpd->FspsConfig.PchSkyCamPortAClkTrimValue;
  Cio2Config->PortBClkTrimValue = FspsUpd->FspsConfig.PchSkyCamPortBClkTrimValue;
  Cio2Config->PortCClkTrimValue = FspsUpd->FspsConfig.PchSkyCamPortCClkTrimValue;
  Cio2Config->PortDClkTrimValue = FspsUpd->FspsConfig.PchSkyCamPortDClkTrimValue;
  Cio2Config->PortADataTrimValue  = FspsUpd->FspsConfig.PchSkyCamPortADataTrimValue;
  Cio2Config->PortBDataTrimValue  = FspsUpd->FspsConfig.PchSkyCamPortBDataTrimValue;
  Cio2Config->PortCDDataTrimValue = FspsUpd->FspsConfig.PchSkyCamPortCDDataTrimValue;

  //
  // Update SCS policies
  //
  ScsConfig->ScsEmmcEnabled       = FspsUpd->FspsConfig.ScsEmmcEnabled;
  ScsConfig->ScsEmmcHs400Enabled  = FspsUpd->FspsConfig.ScsEmmcHs400Enabled;
  ScsConfig->ScsSdSwitch          = FspsUpd->FspsConfig.ScsSdCardEnabled == 0 ? 0 : 2;
  ScsConfig->ScsEmmcHs400TuningRequired  = FspsUpd->FspsConfig.PchScsEmmcHs400TuningRequired;
  ScsConfig->ScsEmmcHs400DllDataValid    = FspsUpd->FspsConfig.PchScsEmmcHs400DllDataValid;
  ScsConfig->ScsEmmcHs400RxStrobeDll1    = FspsUpd->FspsConfig.PchScsEmmcHs400RxStrobeDll1;
  ScsConfig->ScsEmmcHs400TxDataDll       = FspsUpd->FspsConfig.PchScsEmmcHs400TxDataDll;
  ScsConfig->ScsEmmcHs400DriverStrength  = FspsUpd->FspsConfig.PchScsEmmcHs400DriverStrength;

  //
  // Update ISH policies
  //
  IshConfig->Enable          = FspsUpd->FspsConfig.PchIshEnable;
  IshConfig->SpiGpioAssign   = FspsUpd->FspsConfig.PchIshSpiGpioAssign;
  IshConfig->Uart0GpioAssign = FspsUpd->FspsConfig.PchIshUart0GpioAssign;
  IshConfig->Uart1GpioAssign = FspsUpd->FspsConfig.PchIshUart1GpioAssign;
  IshConfig->I2c0GpioAssign  = FspsUpd->FspsConfig.PchIshI2c0GpioAssign;
  IshConfig->I2c1GpioAssign  = FspsUpd->FspsConfig.PchIshI2c1GpioAssign;
  IshConfig->I2c2GpioAssign  = FspsUpd->FspsConfig.PchIshI2c2GpioAssign;
  IshConfig->Gp0GpioAssign   = FspsUpd->FspsConfig.PchIshGp0GpioAssign;
  IshConfig->Gp1GpioAssign   = FspsUpd->FspsConfig.PchIshGp1GpioAssign;
  IshConfig->Gp2GpioAssign   = FspsUpd->FspsConfig.PchIshGp2GpioAssign;
  IshConfig->Gp3GpioAssign   = FspsUpd->FspsConfig.PchIshGp3GpioAssign;
  IshConfig->Gp4GpioAssign   = FspsUpd->FspsConfig.PchIshGp4GpioAssign;
  IshConfig->Gp5GpioAssign   = FspsUpd->FspsConfig.PchIshGp5GpioAssign;
  IshConfig->Gp6GpioAssign   = FspsUpd->FspsConfig.PchIshGp6GpioAssign;
  IshConfig->Gp7GpioAssign   = FspsUpd->FspsConfig.PchIshGp7GpioAssign;
  IshConfig->PdtUnlock       = FspsUpd->FspsConfig.PchIshPdtUnlock;

  //
  // Update SPI policies
  //
  SpiConfig->ShowSpiController = FspsUpd->FspsConfig.ShowSpiController;
  SpiConfig->FlashCfgLockDown = FspsUpd->FspsConfig.SpiFlashCfgLockDown;

  //
  // Update Sata policies
  //
  SataConfig->Enable          = FspsUpd->FspsConfig.SataEnable;
  SataConfig->TestMode        = FspsUpd->FspsTestConfig.SataTestMode;
  SataConfig->SalpSupport     = FspsUpd->FspsConfig.SataSalpSupport;
  SataConfig->PwrOptEnable    = FspsUpd->FspsConfig.SataPwrOptEnable;
  SataConfig->EsataSpeedLimit = FspsUpd->FspsConfig.EsataSpeedLimit;
  SataConfig->SataMode        = FspsUpd->FspsConfig.SataMode;
  SataConfig->SpeedLimit      = FspsUpd->FspsConfig.SataSpeedLimit;

  for (Index = 0; Index < PCH_MAX_SATA_PORTS; Index++) {
    SataConfig->PortSettings[Index].Enable           = FspsUpd->FspsConfig.SataPortsEnable[Index];
    SataConfig->PortSettings[Index].HotPlug          = FspsUpd->FspsConfig.SataPortsHotPlug[Index];
    SataConfig->PortSettings[Index].InterlockSw      = FspsUpd->FspsConfig.SataPortsInterlockSw[Index];
    SataConfig->PortSettings[Index].External         = FspsUpd->FspsConfig.SataPortsExternal[Index];
    SataConfig->PortSettings[Index].SpinUp           = FspsUpd->FspsConfig.SataPortsSpinUp[Index];
    SataConfig->PortSettings[Index].SolidStateDrive  = FspsUpd->FspsConfig.SataPortsSolidStateDrive[Index];
    SataConfig->PortSettings[Index].DevSlp           = FspsUpd->FspsConfig.SataPortsDevSlp[Index];
    SataConfig->PortSettings[Index].EnableDitoConfig = FspsUpd->FspsConfig.SataPortsEnableDitoConfig[Index];
    SataConfig->PortSettings[Index].DmVal            = FspsUpd->FspsConfig.SataPortsDmVal[Index];
    SataConfig->PortSettings[Index].DitoVal          = FspsUpd->FspsConfig.SataPortsDitoVal[Index];
    SataConfig->PortSettings[Index].ZpOdd            = FspsUpd->FspsConfig.SataPortsZpOdd[Index];
  }

  SataConfig->Rst.RaidDeviceId       = FspsUpd->FspsConfig.SataRstRaidAlternateId;
  SataConfig->Rst.Raid0              = FspsUpd->FspsConfig.SataRstRaid0;
  SataConfig->Rst.Raid1              = FspsUpd->FspsConfig.SataRstRaid1;
  SataConfig->Rst.Raid10             = FspsUpd->FspsConfig.SataRstRaid10;
  SataConfig->Rst.Raid5              = FspsUpd->FspsConfig.SataRstRaid5;
  SataConfig->Rst.Irrt               = FspsUpd->FspsConfig.SataRstIrrt;
  SataConfig->Rst.OromUiBanner       = FspsUpd->FspsConfig.SataRstOromUiBanner;
  SataConfig->Rst.OromUiDelay        = FspsUpd->FspsConfig.SataRstOromUiDelay;
  SataConfig->Rst.HddUnlock          = FspsUpd->FspsConfig.SataRstHddUnlock;
  SataConfig->Rst.LedLocate          = FspsUpd->FspsConfig.SataRstLedLocate;
  SataConfig->Rst.IrrtOnly           = FspsUpd->FspsConfig.SataRstIrrtOnly;
  SataConfig->Rst.SmartStorage       = FspsUpd->FspsConfig.SataRstSmartStorage;
  SataConfig->Rst.OptaneMemory       = FspsUpd->FspsConfig.SataRstOptaneMemory;
  SataConfig->Rst.CpuAttachedStorage = FspsUpd->FspsConfig.SataRstCpuAttachedStorage;

  for (Index = 0; Index < PCH_MAX_RST_PCIE_STORAGE_CR; Index++) {
    SataConfig->RstPcieStorageRemap[Index].Enable             = FspsUpd->FspsConfig.SataRstPcieEnable[Index];
    SataConfig->RstPcieStorageRemap[Index].RstPcieStoragePort = FspsUpd->FspsConfig.SataRstPcieStoragePort[Index];
    SataConfig->RstPcieStorageRemap[Index].DeviceResetDelay   = FspsUpd->FspsConfig.SataRstPcieDeviceResetDelay[Index];
  }

  //
  // Update USB policies
  //
  UsbConfig->DisableComplianceMode = FspsUpd->FspsConfig.PchDisableComplianceMode;
  UsbConfig->DelayPdoProgramming   = FspsUpd->FspsConfig.DelayUsbPdoProgramming;
  for (Index = 0; Index < PCH_MAX_USB2_PORTS; Index++) {
    UsbConfig->PortUsb20[Index].Enable         = FspsUpd->FspsConfig.PortUsb20Enable[Index];
    UsbConfig->PortUsb20[Index].OverCurrentPin = FspsUpd->FspsConfig.Usb2OverCurrentPin[Index];
    UsbConfig->PortUsb20[Index].Afe.Petxiset   = FspsUpd->FspsConfig.Usb2AfePetxiset[Index];
    UsbConfig->PortUsb20[Index].Afe.Txiset     = FspsUpd->FspsConfig.Usb2AfeTxiset[Index];
    UsbConfig->PortUsb20[Index].Afe.Predeemp   = FspsUpd->FspsConfig.Usb2AfePredeemp[Index];
    UsbConfig->PortUsb20[Index].Afe.Pehalfbit  = FspsUpd->FspsConfig.Usb2AfePehalfbit[Index];
  }
  for (Index = 0; Index < PCH_MAX_USB3_PORTS; Index++) {
    UsbConfig->PortUsb30[Index].Enable                    = FspsUpd->FspsConfig.PortUsb30Enable[Index];
    UsbConfig->PortUsb30[Index].OverCurrentPin            = FspsUpd->FspsConfig.Usb3OverCurrentPin[Index];
    UsbConfig->PortUsb30[Index].HsioTxDeEmphEnable        = FspsUpd->FspsConfig.Usb3HsioTxDeEmphEnable[Index];
    UsbConfig->PortUsb30[Index].HsioTxDeEmph              = FspsUpd->FspsConfig.Usb3HsioTxDeEmph[Index];
    UsbConfig->PortUsb30[Index].HsioTxDownscaleAmpEnable  = FspsUpd->FspsConfig.Usb3HsioTxDownscaleAmpEnable[Index];
    UsbConfig->PortUsb30[Index].HsioTxDownscaleAmp        = FspsUpd->FspsConfig.Usb3HsioTxDownscaleAmp[Index];
  }
  UsbConfig->SsicConfig.SsicPort[0].Enable = FspsUpd->FspsConfig.SsicPortEnable;
  UsbConfig->XdciConfig.Enable  = FspsUpd->FspsConfig.XdciEnable;

  //
  // Update PCIE RP RootPort policies
  //
  for (Index = 0; Index < KBL_PCH_H_PCIE_MAX_ROOT_PORTS; Index ++) {
    PcieRpConfig->RootPort[Index].HotPlug                  = FspsUpd->FspsConfig.PcieRpHotPlug[Index];
    PcieRpConfig->RootPort[Index].PmSci                    = FspsUpd->FspsConfig.PcieRpPmSci[Index];
    PcieRpConfig->RootPort[Index].ExtSync                  = FspsUpd->FspsConfig.PcieRpExtSync[Index];
    PcieRpConfig->RootPort[Index].TransmitterHalfSwing     = FspsUpd->FspsConfig.PcieRpTransmitterHalfSwing[Index];
    PcieRpConfig->RootPort[Index].ClkReqSupported          = FspsUpd->FspsConfig.PcieRpClkReqSupport[Index];
    PcieRpConfig->RootPort[Index].ClkReqNumber             = FspsUpd->FspsConfig.PcieRpClkReqNumber[Index];
    PcieRpConfig->RootPort[Index].ClkSrcNumber             = FspsUpd->FspsConfig.PcieRpClkSrcNumber[Index];
    PcieRpConfig->RootPort[Index].ClkReqDetect             = FspsUpd->FspsConfig.PcieRpClkReqDetect[Index];
    PcieRpConfig->RootPort[Index].ForceClkDisableWhenRpDisable    = FspsUpd->FspsConfig.PcieRpForceClkDisableWhenRpDisable[Index];
    PcieRpConfig->RootPort[Index].AdvancedErrorReporting   = FspsUpd->FspsConfig.PcieRpAdvancedErrorReporting[Index];
    PcieRpConfig->RootPort[Index].UnsupportedRequestReport = FspsUpd->FspsConfig.PcieRpUnsupportedRequestReport[Index];
    PcieRpConfig->RootPort[Index].FatalErrorReport         = FspsUpd->FspsConfig.PcieRpFatalErrorReport[Index];
    PcieRpConfig->RootPort[Index].NoFatalErrorReport       = FspsUpd->FspsConfig.PcieRpNoFatalErrorReport[Index];
    PcieRpConfig->RootPort[Index].CorrectableErrorReport   = FspsUpd->FspsConfig.PcieRpCorrectableErrorReport[Index];
    PcieRpConfig->RootPort[Index].SystemErrorOnFatalError  = FspsUpd->FspsConfig.PcieRpSystemErrorOnFatalError[Index];
    PcieRpConfig->RootPort[Index].SystemErrorOnNonFatalError    = FspsUpd->FspsConfig.PcieRpSystemErrorOnNonFatalError[Index];
    PcieRpConfig->RootPort[Index].SystemErrorOnCorrectableError = FspsUpd->FspsConfig.PcieRpSystemErrorOnCorrectableError[Index];
    PcieRpConfig->RootPort[Index].MaxPayload               = FspsUpd->FspsConfig.PcieRpMaxPayload[Index];
    PcieRpConfig->RootPort[Index].DeviceResetPadActiveHigh = FspsUpd->FspsConfig.PcieRpDeviceResetPadActiveHigh[Index];
    PcieRpConfig->RootPort[Index].PcieSpeed                = FspsUpd->FspsConfig.PcieRpPcieSpeed[Index];
    PcieRpConfig->RootPort[Index].Gen3EqPh3Method          = FspsUpd->FspsConfig.PcieRpGen3EqPh3Method[Index];
    PcieRpConfig->RootPort[Index].PhysicalSlotNumber       = FspsUpd->FspsConfig.PcieRpPhysicalSlotNumber[Index];
    PcieRpConfig->RootPort[Index].CompletionTimeout        = FspsUpd->FspsConfig.PcieRpCompletionTimeout[Index];
    PcieRpConfig->RootPort[Index].DeviceResetPad           = FspsUpd->FspsConfig.PcieRpDeviceResetPad[Index];
    PcieRpConfig->RootPort[Index].Aspm                     = FspsUpd->FspsConfig.PcieRpAspm[Index];
    PcieRpConfig->RootPort[Index].L1Substates              = FspsUpd->FspsConfig.PcieRpL1Substates[Index];
    PcieRpConfig->RootPort[Index].LtrEnable                = FspsUpd->FspsConfig.PcieRpLtrEnable[Index];
    PcieRpConfig->RootPort[Index].LtrConfigLock            = FspsUpd->FspsConfig.PcieRpLtrConfigLock[Index];
    PcieRpConfig->RootPort[Index].LtrMaxSnoopLatency       = FspsUpd->FspsTestConfig.PcieRpLtrMaxSnoopLatency[Index];
    PcieRpConfig->RootPort[Index].LtrMaxNoSnoopLatency     = FspsUpd->FspsTestConfig.PcieRpLtrMaxNoSnoopLatency[Index];

    PcieRpConfig->RootPort[Index].SnoopLatencyOverrideMode       = FspsUpd->FspsTestConfig.PcieRpSnoopLatencyOverrideMode[Index];
    PcieRpConfig->RootPort[Index].SnoopLatencyOverrideMultiplier = FspsUpd->FspsTestConfig.PcieRpSnoopLatencyOverrideMultiplier[Index];
    PcieRpConfig->RootPort[Index].SnoopLatencyOverrideValue      = FspsUpd->FspsTestConfig.PcieRpSnoopLatencyOverrideValue[Index];

    PcieRpConfig->RootPort[Index].NonSnoopLatencyOverrideMode       = FspsUpd->FspsTestConfig.PcieRpNonSnoopLatencyOverrideMode[Index];
    PcieRpConfig->RootPort[Index].NonSnoopLatencyOverrideMultiplier = FspsUpd->FspsTestConfig.PcieRpNonSnoopLatencyOverrideMultiplier[Index];
    PcieRpConfig->RootPort[Index].NonSnoopLatencyOverrideValue      = FspsUpd->FspsTestConfig.PcieRpNonSnoopLatencyOverrideValue[Index];

    PcieRpConfig->RootPort[Index].SlotPowerLimitScale      = FspsUpd->FspsTestConfig.PcieRpSlotPowerLimitScale[Index];
    PcieRpConfig->RootPort[Index].SlotPowerLimitValue      = FspsUpd->FspsTestConfig.PcieRpSlotPowerLimitValue[Index];
    PcieRpConfig->RootPort[Index].Uptp                     = FspsUpd->FspsTestConfig.PcieRpUptp[Index];
    PcieRpConfig->RootPort[Index].Dptp                     = FspsUpd->FspsTestConfig.PcieRpDptp[Index];
  }

  //
  // Update PCIE RP EqPh3LaneParam policies
  //
  for (Index = 0; Index < SKL_PCH_H_PCIE_MAX_ROOT_PORTS; Index ++) {
    PcieRpConfig->EqPh3LaneParam[Index].Cm = FspsUpd->FspsConfig.PcieEqPh3LaneParamCm[Index];
    PcieRpConfig->EqPh3LaneParam[Index].Cp = FspsUpd->FspsConfig.PcieEqPh3LaneParamCp[Index];
  }

  //
  // Update PCIE RP SwEqCoeffList policies
  //
  for (Index = 0; Index < PCH_PCIE_SWEQ_COEFFS_MAX; Index++) {
    PcieRpConfig->SwEqCoeffList[Index].Cm = FspsUpd->FspsConfig.PcieSwEqCoeffListCm[Index];
    PcieRpConfig->SwEqCoeffList[Index].Cp = FspsUpd->FspsConfig.PcieSwEqCoeffListCp[Index];
  }

  //
  // Update PCIE RP policies
  //
  PcieRpConfig->EnablePort8xhDecode           = FspsUpd->FspsTestConfig.PcieEnablePort8xhDecode;
  PcieRpConfig->PchPciePort8xhDecodePortIndex = FspsUpd->FspsTestConfig.PchPciePort8xhDecodePortIndex;
  PcieRpConfig->DisableRootPortClockGating    = FspsUpd->FspsConfig.PcieDisableRootPortClockGating;
  PcieRpConfig->EnablePeerMemoryWrite         = FspsUpd->FspsConfig.PcieEnablePeerMemoryWrite;
  PcieRpConfig->AllowNoLtrIccPllShutdown      = FspsUpd->FspsConfig.PcieAllowNoLtrIccPllShutdown;
  PcieRpConfig->ComplianceTestMode            = FspsUpd->FspsConfig.PcieComplianceTestMode;
  PcieRpConfig->RpFunctionSwap                = FspsUpd->FspsConfig.PcieRpFunctionSwap;
  PcieRpConfig->DetectTimeoutMs               = FspsUpd->FspsConfig.PcieDetectTimeoutMs;
  PcieRpConfig->PcieDeviceOverrideTablePtr    = FspsUpd->FspsConfig.PchPcieDeviceOverrideTablePtr;

  //
  // Update SerialIo policies
  //
  for (Index = 0; Index < PCH_SERIALIO_MAX_CONTROLLERS; Index++) {
    SerialIoConfig->DevMode[Index] = FspsUpd->FspsConfig.SerialIoDevMode[Index];
  }

  for (Index = 0; Index < PCH_SERIALIO_MAX_I2C_CONTROLLERS; Index++) {
    SerialIoConfig->I2cVoltage[Index] = FspsUpd->FspsConfig.SerialIoI2cVoltage[Index];
  }
  for (Index = 0; Index < PCH_SERIALIO_MAX_SPI_CONTROLLERS; Index++) {
    SerialIoConfig->SpiCsPolarity[Index] = FspsUpd->FspsConfig.SerialIoSpiCsPolarity[Index];
  }
  for (Index = 0; Index < PCH_SERIALIO_MAX_UART_CONTROLLERS; Index++) {
    SerialIoConfig->UartHwFlowCtrl[Index] = FspsUpd->FspsConfig.SerialIoUartHwFlowCtrl[Index];
  }
  SerialIoConfig->Gpio                     = FspsUpd->FspsConfig.SerialIoGpio;
  SerialIoConfig->DebugUartNumber          = FspsUpd->FspsConfig.SerialIoDebugUartNumber;
  SerialIoConfig->EnableDebugUartAfterPost = FspsUpd->FspsConfig.SerialIoEnableDebugUartAfterPost;

  //
  // Update Interrupt policies
  //
  if (FspsUpd->FspsConfig.NumOfDevIntConfig != 0) {
    DevIntConfg = (PCH_DEVICE_INTERRUPT_CONFIG *)FspsUpd->FspsConfig.DevIntConfigPtr;
    NumOfDevIntConfig = FspsUpd->FspsConfig.NumOfDevIntConfig;
    ASSERT (NumOfDevIntConfig <= PCH_MAX_DEVICE_INTERRUPT_CONFIG);

    InterruptConfig->NumOfDevIntConfig = NumOfDevIntConfig;
    ZeroMem (
      InterruptConfig->DevIntConfig,
      PCH_MAX_DEVICE_INTERRUPT_CONFIG * sizeof (PCH_DEVICE_INTERRUPT_CONFIG)
      );
    CopyMem (
      InterruptConfig->DevIntConfig,
      DevIntConfg,
      NumOfDevIntConfig * sizeof (PCH_DEVICE_INTERRUPT_CONFIG)
      );
  }
  for (Index = 0; Index < PCH_MAX_PXRC_CONFIG; Index ++) {
    if (FspsUpd->FspsConfig.PxRcConfig[Index] != 0) {
      InterruptConfig->PxRcConfig[Index] = FspsUpd->FspsConfig.PxRcConfig[Index];
    }
  }
  InterruptConfig->GpioIrqRoute = FspsUpd->FspsConfig.GpioIrqRoute;
  InterruptConfig->SciIrqSelect = FspsUpd->FspsConfig.SciIrqSelect;
  InterruptConfig->TcoIrqSelect = FspsUpd->FspsConfig.TcoIrqSelect;
  InterruptConfig->TcoIrqEnable = FspsUpd->FspsConfig.TcoIrqEnable;

  //
  // Update LockDown policies
  //
  LockDownConfig->RtcLock       = FspsUpd->FspsTestConfig.PchLockDownRtcLock;
  LockDownConfig->GlobalSmi     = FspsUpd->FspsTestConfig.PchLockDownGlobalSmi;
  LockDownConfig->BiosInterface = FspsUpd->FspsTestConfig.PchLockDownBiosInterface;
  LockDownConfig->BiosLock      = FspsUpd->FspsConfig.PchLockDownBiosLock;
  LockDownConfig->SpiEiss       = FspsUpd->FspsConfig.PchLockDownSpiEiss;

  //
  // Update Dmi policies
  //
  DmiConfig->DmiAspm = FspsUpd->FspsConfig.PchDmiAspm;
  DmiConfig->PwrOptEnable = FspsUpd->FspsConfig.PchPwrOptEnable;
  if (FspsUpd->FspsConfig.PchLegacyIoLowLatency) {
    DmiConfig->DmiAspm = 0;
    DmiConfig->LegacyIoLowLatency = TRUE;
  }

  //
  // Update Flash Protection policies
  //
  for (Index = 0; Index < PCH_FLASH_PROTECTED_RANGES; Index ++) {
    FlashProtectionConfig->ProtectRange[Index].WriteProtectionEnable = FspsUpd->FspsConfig.PchWriteProtectionEnable[Index];
    FlashProtectionConfig->ProtectRange[Index].ReadProtectionEnable  = FspsUpd->FspsConfig.PchReadProtectionEnable[Index];
    FlashProtectionConfig->ProtectRange[Index].ProtectedRangeLimit   = FspsUpd->FspsConfig.PchProtectedRangeLimit[Index];
    FlashProtectionConfig->ProtectRange[Index].ProtectedRangeBase    = FspsUpd->FspsConfig.PchProtectedRangeBase[Index];
  }

  //
  // Update IO Apic policies
  //
  IoApicConfig->BdfValid                   = FspsUpd->FspsConfig.PchIoApicBdfValid;
  IoApicConfig->BusNumber                  = FspsUpd->FspsConfig.PchIoApicBusNumber;
  IoApicConfig->DeviceNumber               = FspsUpd->FspsConfig.PchIoApicDeviceNumber;
  IoApicConfig->FunctionNumber             = FspsUpd->FspsConfig.PchIoApicFunctionNumber;
  IoApicConfig->IoApicEntry24_119          = FspsUpd->FspsConfig.PchIoApicEntry24_119;
  IoApicConfig->Early8254ClockGatingEnable = FspsUpd->FspsConfig.Early8254ClockGatingEnable;
  IoApicConfig->IoApicId                   = FspsUpd->FspsConfig.PchIoApicId;
  IoApicConfig->ApicRangeSelect            = FspsUpd->FspsConfig.PchIoApicRangeSelect;

  //
  // Update P2sb policies
  //
  P2sbConfig->SbiUnlock = FspsUpd->FspsTestConfig.PchSbiUnlock;
  P2sbConfig->SbAccessUnlock = FspsUpd->FspsTestConfig.PchSbAccessUnlock;

  //
  // Update Pch General policies
  //
  PchGeneralConfig->SubSystemVendorId = FspsUpd->FspsConfig.PchSubSystemVendorId;
  PchGeneralConfig->SubSystemId       = FspsUpd->FspsConfig.PchSubSystemId;
  PchGeneralConfig->Crid              = FspsUpd->FspsConfig.PchCrid;

  //
  // Update Pm policies
  //
  PmConfig->WakeConfig.PmeB0S5Dis         = FspsUpd->FspsConfig.PchPmPmeB0S5Dis;
  PmConfig->WakeConfig.WolEnableOverride  = FspsUpd->FspsConfig.PchPmWolEnableOverride;
  PmConfig->WakeConfig.PcieWakeFromDeepSx = FspsUpd->FspsConfig.PchPmPcieWakeFromDeepSx;
  PmConfig->WakeConfig.WoWlanEnable       = FspsUpd->FspsConfig.PchPmWoWlanEnable;
  PmConfig->WakeConfig.WoWlanDeepSxEnable = FspsUpd->FspsConfig.PchPmWoWlanDeepSxEnable;
  PmConfig->WakeConfig.LanWakeFromDeepSx  = FspsUpd->FspsConfig.PchPmLanWakeFromDeepSx;

  PmConfig->PchDeepSxPol       = FspsUpd->FspsConfig.PchPmDeepSxPol;
  PmConfig->PchSlpS3MinAssert  = FspsUpd->FspsConfig.PchPmSlpS3MinAssert;
  PmConfig->PchSlpS4MinAssert  = FspsUpd->FspsConfig.PchPmSlpS4MinAssert;
  PmConfig->PchSlpSusMinAssert = FspsUpd->FspsConfig.PchPmSlpSusMinAssert;
  PmConfig->PchSlpAMinAssert   = FspsUpd->FspsConfig.PchPmSlpAMinAssert;

  PmConfig->LpcClockRun          = FspsUpd->FspsConfig.PchPmLpcClockRun;
  PmConfig->SlpStrchSusUp        = FspsUpd->FspsConfig.PchPmSlpStrchSusUp;
  PmConfig->SlpLanLowDc          = FspsUpd->FspsConfig.PchPmSlpLanLowDc;
  PmConfig->PwrBtnOverridePeriod = FspsUpd->FspsConfig.PchPmPwrBtnOverridePeriod;
  PmConfig->DisableEnergyReport  = FspsUpd->FspsTestConfig.PchPmDisableEnergyReport;
  PmConfig->DisableDsxAcPresentPulldown = FspsUpd->FspsConfig.PchPmDisableDsxAcPresentPulldown;
  PmConfig->DisableNativePowerButton = FspsUpd->FspsConfig.PchPmDisableNativePowerButton;
  PmConfig->SlpS0Enable          = FspsUpd->FspsConfig.PchPmSlpS0Enable;
  PmConfig->SlpS0VmEnable        = FspsUpd->FspsConfig.PchPmSlpS0VmEnable;
  PmConfig->MeWakeSts            = FspsUpd->FspsConfig.PchPmMeWakeSts;
  PmConfig->WolOvrWkSts          = FspsUpd->FspsConfig.PchPmWolOvrWkSts;
  PmConfig->EnableTcoTimer       = FspsUpd->FspsConfig.EnableTcoTimer;
  PmConfig->PchPwrCycDur         = FspsUpd->FspsConfig.PchPmPwrCycDur;

  //
  // Update Port61h policies
  //
  Port61hConfig->Enable = FspsUpd->FspsConfig.PchPort61hEnable;

  //
  // Update Pch Serial IRQ policies
  //
  PchSerialIrqConfig->SirqEnable       = FspsUpd->FspsConfig.PchSirqEnable;
  PchSerialIrqConfig->SirqMode         = FspsUpd->FspsConfig.PchSirqMode;
  PchSerialIrqConfig->StartFramePulse  = FspsUpd->FspsConfig.PchStartFramePulse;

  //
  // Update Pch Thermal policies
  //
  PchThermalConfig->ThermalDeviceEnable = FspsUpd->FspsConfig.PchThermalDeviceEnable;
  PchThermalConfig->TsmicLock = FspsUpd->FspsConfig.PchTsmicLock;

  PchThermalConfig->TTLevels.T0Level            = FspsUpd->FspsConfig.PchT0Level;
  PchThermalConfig->TTLevels.T1Level            = FspsUpd->FspsConfig.PchT1Level;
  PchThermalConfig->TTLevels.T2Level            = FspsUpd->FspsConfig.PchT2Level;
  PchThermalConfig->TTLevels.TTEnable           = FspsUpd->FspsConfig.PchTTEnable;
  PchThermalConfig->TTLevels.TTState13Enable    = FspsUpd->FspsConfig.PchTTState13Enable;
  PchThermalConfig->TTLevels.TTLock             = FspsUpd->FspsConfig.PchTTLock;
  PchThermalConfig->TTLevels.SuggestedSetting   = FspsUpd->FspsConfig.TTSuggestedSetting;
  PchThermalConfig->TTLevels.PchCrossThrottling = FspsUpd->FspsConfig.TTCrossThrottling;

  PchThermalConfig->DmiHaAWC.DmiTsawEn        = FspsUpd->FspsConfig.PchDmiTsawEn;
  PchThermalConfig->DmiHaAWC.SuggestedSetting = FspsUpd->FspsConfig.DmiSuggestedSetting;
  PchThermalConfig->DmiHaAWC.TS0TW            = FspsUpd->FspsConfig.DmiTS0TW;
  PchThermalConfig->DmiHaAWC.TS1TW            = FspsUpd->FspsConfig.DmiTS1TW;
  PchThermalConfig->DmiHaAWC.TS2TW            = FspsUpd->FspsConfig.DmiTS2TW;
  PchThermalConfig->DmiHaAWC.TS3TW            = FspsUpd->FspsConfig.DmiTS3TW;

  PchThermalConfig->SataTT.P0T1M            = FspsUpd->FspsConfig.SataP0T1M;
  PchThermalConfig->SataTT.P0T2M            = FspsUpd->FspsConfig.SataP0T2M;
  PchThermalConfig->SataTT.P0T3M            = FspsUpd->FspsConfig.SataP0T3M;
  PchThermalConfig->SataTT.P0TDisp          = FspsUpd->FspsConfig.SataP0TDisp;
  PchThermalConfig->SataTT.P1T1M            = FspsUpd->FspsConfig.SataP1T1M;
  PchThermalConfig->SataTT.P1T2M            = FspsUpd->FspsConfig.SataP1T2M;
  PchThermalConfig->SataTT.P1T3M            = FspsUpd->FspsConfig.SataP1T3M;
  PchThermalConfig->SataTT.P1TDisp          = FspsUpd->FspsConfig.SataP1TDisp;
  PchThermalConfig->SataTT.P0Tinact         = FspsUpd->FspsConfig.SataP0Tinact;
  PchThermalConfig->SataTT.P0TDispFinit     = FspsUpd->FspsConfig.SataP0TDispFinit;
  PchThermalConfig->SataTT.P1Tinact         = FspsUpd->FspsConfig.SataP1Tinact;
  PchThermalConfig->SataTT.P1TDispFinit     = FspsUpd->FspsConfig.SataP1TDispFinit;
  PchThermalConfig->SataTT.SuggestedSetting = FspsUpd->FspsConfig.SataThermalSuggestedSetting;

  PchThermalConfig->MemoryThrottling.Enable = FspsUpd->FspsConfig.PchMemoryThrottlingEnable;
  PchThermalConfig->MemoryThrottling.TsGpioPinSetting[0].PmsyncEnable     = FspsUpd->FspsConfig.PchMemoryPmsyncEnable[0];
  PchThermalConfig->MemoryThrottling.TsGpioPinSetting[1].PmsyncEnable     = FspsUpd->FspsConfig.PchMemoryPmsyncEnable[1];
  PchThermalConfig->MemoryThrottling.TsGpioPinSetting[0].C0TransmitEnable = FspsUpd->FspsConfig.PchMemoryC0TransmitEnable[0];
  PchThermalConfig->MemoryThrottling.TsGpioPinSetting[1].C0TransmitEnable = FspsUpd->FspsConfig.PchMemoryC0TransmitEnable[1];
  PchThermalConfig->MemoryThrottling.TsGpioPinSetting[0].PinSelection     = FspsUpd->FspsConfig.PchMemoryPinSelection[0];
  PchThermalConfig->MemoryThrottling.TsGpioPinSetting[1].PinSelection     = FspsUpd->FspsConfig.PchMemoryPinSelection[1];

  PchThermalConfig->PchHotLevel = FspsUpd->FspsConfig.PchTemperatureHotLevel;

  //
  // Update Hybrid Storage Policies
  //
  HybridStorageConfig->HybridStorageMode         = FspsUpd->FspsConfig.HybridStorageMode;


  return EFI_SUCCESS;
}

