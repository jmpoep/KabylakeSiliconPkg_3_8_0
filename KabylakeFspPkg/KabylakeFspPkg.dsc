## @file
#  Platform description.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2008 - 2019 Intel Corporation.
#
#  The source code contained or described herein and all documents related to the
#  source code ("Material") are owned by Intel Corporation or its suppliers or
#  licensors. Title to the Material remains with Intel Corporation or its suppliers
#  and licensors. The Material may contain trade secrets and proprietary and
#  confidential information of Intel Corporation and its suppliers and licensors,
#  and is protected by worldwide copyright and trade secret laws and treaty
#  provisions. No part of the Material may be used, copied, reproduced, modified,
#  published, uploaded, posted, transmitted, distributed, or disclosed in any way
#  without Intel's prior express written permission.
#
#  No license under any patent, copyright, trade secret or other intellectual
#  property right is granted to or conferred upon you by disclosure or delivery
#  of the Materials, either expressly, by implication, inducement, estoppel or
#  otherwise. Any license under such intellectual property rights must be
#  express and approved by Intel in writing.
#
#  Unless otherwise agreed by Intel in writing, you may not remove or alter
#  this notice or any other notice embedded in Materials by Intel or
#  Intel's suppliers or licensors in any way.
#
#  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
#  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
#  the terms of your license agreement with Intel or your vendor. This file may
#  be modified by the user, subject to additional terms of the license agreement.
#
# @par Specification
##

[Defines]
  #
  # Set platform specific package/folder name, same as passed from PREBUILD script.
  # PLATFORM_PACKAGE would be the same as PLATFORM_NAME as well as package build folder
  # DEFINE only takes effect at R9 DSC and FDF.
  #
  DEFINE      FSP_PACKAGE                     = KabylakeFspPkg
  DEFINE      PLATFORM_SI_PACKAGE             = KabylakeSiliconPkg
  DEFINE      CLIENT_SILICON_PACKAGE          = ClientSiliconPkg

[PcdsFeatureFlag]
  #
  # BIOS build switches configuration
  #
  !include $(FSP_PACKAGE)/KabylakeFspPkgConfig.dsc
  !include $(FSP_PACKAGE)/KabylakeFspPkgExtConfig.dsc

[PcdsDynamicDefault]
  gUefiCpuPkgTokenSpaceGuid.PcdCpuMicrocodePatchAddress    | 0
  gUefiCpuPkgTokenSpaceGuid.PcdCpuMicrocodePatchRegionSize | 0

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = $(FSP_PACKAGE)
  PLATFORM_GUID                  = 1BEDB57A-7904-406e-8486-C89FC7FB39EE
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = $(CFG_OUTDIR)/$(FSP_PACKAGE)
  SUPPORTED_ARCHITECTURES        = IA32
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = $(FSP_PACKAGE)/$(FSP_PACKAGE).fdf

  #
  # UPD tool definition
  #
  FSP_T_UPD_TOOL_GUID            = 34686CA3-34F9-4901-B82A-BA630F0714C6
  FSP_M_UPD_TOOL_GUID            = 39A250DB-E465-4DD1-A2AC-E2BD3C0E2385
  FSP_S_UPD_TOOL_GUID            = CAE3605B-5B34-4C85-B3D7-27D54273C40F
  FSP_T_UPD_FFS_GUID             = 70BCF6A5-FFB1-47D8-B1AE-EFE5508E23EA
  FSP_M_UPD_FFS_GUID             = D5B86AEA-6AF7-40D4-8014-982301BC3D89
  FSP_S_UPD_FFS_GUID             = E3CD9B18-998C-4F76-B65E-98B154E5446F
################################################################################
#
# SKU Identification section - list of all SKU IDs supported by this
#                              Platform.
#
################################################################################
[SkuIds]
  0|DEFAULT              # The entry: 0|DEFAULT is reserved and always required.

################################################################################
#
# Library Class section - list of all Library Classes needed by this Platform.
#
################################################################################
[LibraryClasses.IA32]
  ExtractGuidedSectionLib|MdePkg/Library/PeiExtractGuidedSectionLib/PeiExtractGuidedSectionLib.inf
  PeiPolicyUpdatePreMemLib|$(FSP_PACKAGE)/Library/PeiPolicyUpdatePreMemLib/PeiPolicyUpdatePreMemLib.inf
  PeiPolicyUpdateLib|$(FSP_PACKAGE)/Library/PeiPolicyUpdateLib/PeiPolicyUpdateLib.inf

#
# Silicon Init Pei Library
#
  SiPolicyLib|$(PLATFORM_SI_PACKAGE)/Library/PeiSiPolicyLib/PeiSiPolicyLib.inf
  SiConfigBlockLib|$(PLATFORM_SI_PACKAGE)/Library/BaseSiConfigBlockLib/BaseSiConfigBlockLib.inf
  ConfigBlockLib|$(CLIENT_SILICON_PACKAGE)/Library/BaseConfigBlockLib/BaseConfigBlockLib.inf

#
# Pch
#
  PchPolicyLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiPchPolicyLib/PeiPchPolicyLib.inf
  PchInitLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiPchInitLib/PeiPchInitLibFsp.inf
  PchRcLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiPchRcLib/PeiPchRcLib.inf
  PchResetLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiPchResetLib/PeiPchResetLib.inf
  PchInitCommonLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmPchInitCommonLib/PeiDxeSmmPchInitCommonLib.inf
  ResetSystemLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiResetSystemLib/PeiResetSystemLibFsp.inf
  PchSmbusCommonLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmPchSmbusCommonLib/PeiDxeSmmPchSmbusCommonLib.inf
  PchSpiCommonLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/BasePchSpiCommonLib/BasePchSpiCommonLib.inf
  PchWdtCommonLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchWdtCommonLib/PeiDxeSmmPchWdtCommonLib.inf
  PchAlternateAccessModeLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmPchAlternateAccessModeLib/PeiDxeSmmPchAlternateAccessModeLib.inf
  PchXhciLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmPchXhciLib/PeiDxeSmmPchXhciLib.inf
  PchEspiLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchEspiLib/PeiDxeSmmPchEspiLib.inf
!if gSiPkgTokenSpaceGuid.PcdTraceHubEnable == TRUE
  TraceHubInitLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmTraceHubInitLib/PeiDxeSmmTraceHubInitLib.inf
!else
  TraceHubInitLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/BaseTraceHubInitLibNull/BaseTraceHubInitLibNull.inf
!endif
  PeiI2cMasterLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiI2cMasterLib/PeiI2cMasterLib.inf
  I2cMasterCommonLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeI2cMasterCommonLib/PeiDxeI2cMasterCommonLib.inf
!if gSiPkgTokenSpaceGuid.PcdOcWdtEnable == TRUE
  OcWdtLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiOcWdtLib/PeiOcWdtLib.inf
!else
  OcWdtLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiOcWdtLibNull/PeiOcWdtLibNull.inf
!endif
  RstPrivateLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmRstPrivateLib/PeiDxeSmmRstPrivateLib.inf
  PeiHybridStorageLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiHybridStorageLib/PeiHybridStorageLib.inf
#
# Cpu
#
  CpuInitLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuInitLib/PeiCpuInitLib.inf
!if gSiPkgTokenSpaceGuid.PcdS3Enable == TRUE
  CpuS3Lib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuS3Lib/PeiCpuS3LibFsp.inf
!else
  CpuS3Lib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuS3LibNull/PeiCpuS3LibNull.inf
!endif
  CpuPowerMgmtLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuPowerMgmtLib/PeiCpuPowerMgmtLib.inf
  CpuCommonLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiDxeSmmCpuCommonLib/PeiDxeSmmCpuCommonLib.inf
!if gSiPkgTokenSpaceGuid.PcdTxtEnable == TRUE
  PeiTxtLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiTxtLib/PeiTxtLib.inf
!else
  PeiTxtLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiTxtLibNull/PeiTxtLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdCpuPowerOnConfigEnable == TRUE
  CpuPowerOnConfigLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuPowerOnConfigLib/PeiCpuPowerOnConfigLib.inf
!else
  CpuPowerOnConfigLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuPowerOnConfigLibDisable/PeiCpuPowerOnConfigLibDisable.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdOverclockEnable == TRUE
  CpuOcLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuOcLib/PeiCpuOcLib.inf
  CpuOcInitLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuOcInitLib/PeiCpuOcInitLib.inf
!else
  CpuOcLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuOcLibNull/PeiCpuOcLibNull.inf
  CpuOcInitLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuOcInitLibNull/PeiCpuOcInitLibNull.inf
!endif
  BiosGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiBiosGuardLib/PeiBiosGuardLib.inf
!if gSiPkgTokenSpaceGuid.PcdSmbiosEnable == TRUE
  SmbiosCpuLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiSmbiosCpuLib/PeiSmbiosCpuLib.inf
!else
  SmbiosCpuLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiSmbiosCpuLibNull/PeiSmbiosCpuLibNull.inf
!endif
#
# Me
#
  MeTypeLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiDxeMeTypeLib/PeiDxeMeTypeLib.inf
  HeciInitLib|$(PLATFORM_SI_PACKAGE)/Me/Library/Private/PeiDxeHeciInitLib/PeiDxeHeciInitLib.inf
  AlertStandardFormatLib|$(PLATFORM_SI_PACKAGE)/Me/Library/Private/PeiDxeAlertStandardFormatLib/PeiDxeAlertStandardFormatLib.inf
  MeInitLib|$(PLATFORM_SI_PACKAGE)/Me/Library/Private/PeiMeInitLib/PeiMeInitLibFsp.inf
  PeiMeLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiMeLib/PeiMeLib.inf
  PeiMePolicyLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiMePolicyLib/PeiMePolicyLib.inf
!if gSiPkgTokenSpaceGuid.PcdAmtEnable == TRUE
  PeiAmtPolicyLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiAmtPolicyLib/PeiAmtPolicyLib.inf
  PeiAmtLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiAmtLib/PeiAmtLib.inf
  ActiveManagementLib|$(PLATFORM_SI_PACKAGE)/Me/Library/Private/PeiActiveManagementLib/PeiActiveManagementLib.inf
!else
  PeiAmtPolicyLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiAmtPolicyLibNull/PeiAmtPolicyLibNull.inf
  PeiAmtLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiAmtLibNull/PeiAmtLibNull.inf
  ActiveManagementLib|$(PLATFORM_SI_PACKAGE)/Me/Library/Private/PeiActiveManagementLibNull/PeiActiveManagementLibNull.inf
!endif
  MeShowBufferLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiDxeMeShowBufferLib/PeiDxeMeShowBufferLib.inf
  MeChipsetLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiDxeMeChipsetLib/PeiDxeMeChipsetLib.inf
  MeFwStsLib|$(PLATFORM_SI_PACKAGE)/Me/Library/BaseMeFwStsLib/BaseMeFwStsLib.inf

#
# SA
#
!if gSiPkgTokenSpaceGuid.PcdSgEnable == TRUE
  SwitchableGraphicsInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSwitchableGraphicsInitLib/PeiSwitchableGraphicsInitLib.inf
!else
  SwitchableGraphicsInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSwitchableGraphicsInitLibNull/PeiSwitchableGraphicsInitLibNull.inf
!endif
  SaInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSaInitLib/PeiSaInitLibFsp.inf
!if gSiPkgTokenSpaceGuid.PcdIgdEnable == TRUE
  GraphicsInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiGraphicsInitLib/PeiGraphicsInitLib.inf
!else
  GraphicsInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiGraphicsInitLib/PeiGraphicsInitLibDisable.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdPeiDisplayEnable == TRUE
  DisplayInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiDisplayInitLib/PeiDisplayInitLib.inf
!else
  DisplayInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiDisplayInitLibNull/PeiDisplayInitLibNull.inf
!endif
  PcieInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiPcieInitLib/PeiPcieInitLib.inf
!if (gSiPkgTokenSpaceGuid.PcdPegEnable == TRUE) OR (gSiPkgTokenSpaceGuid.PcdSaDmiEnable == TRUE)
  SaPcieDmiLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSaPcieDmiLib/PeiSaPcieDmiLib.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdPegEnable == TRUE
  SaPcieInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSaPcieInitLib/PeiSaPcieInitLib.inf
!else
  SaPcieInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSaPcieInitLib/PeiSaPcieInitLibDisable.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdSaDmiEnable == TRUE
  SaDmiInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSaDmiInitLib/PeiSaDmiInitLib.inf
!else
  SaDmiInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSaDmiInitLibNull/PeiSaDmiInitLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdSkycamEnable == TRUE
  SkyCamInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSkyCamInitLib/PeiSkyCamInitLib.inf
!else
  SkyCamInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSkyCamInitLibNull/PeiSkyCamInitLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdGmmEnable == TRUE
  GmmInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiGmmInitLib/PeiGmmInitLib.inf
!else
  GmmInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiGmmInitLibNull/PeiGmmInitLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdSaOcEnable == TRUE
  SaOcInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSaOcInitLib/PeiSaOcInitLib.inf
!else
  SaOcInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSaOcInitLibNull/PeiSaOcInitLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdVtdEnable == TRUE
  VtdInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiVtdInitLib/PeiVtdInitLib.inf
!else
  VtdInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiVtdInitLibNull/PeiVtdInitLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdSsaFlagEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdEvLoaderEnable == TRUE
  EvLoaderLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/MemoryInit/Library/Private/PeiEvLoaderLib/PeiEvLoaderLib.inf
!else
  EvLoaderLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/MemoryInit/Library/Private/PeiEvLoaderLibNull/PeiEvLoaderLibNull.inf
!endif
!else
  EvLoaderLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/MemoryInit/Library/Private/PeiEvLoaderLibNull/PeiEvLoaderLibNull.inf
!endif

  MemoryInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/MemoryInit/Library/Private/PeiMemoryInitLib/PeiMemoryInitLibFsp.inf

#
# Cpu
#
  CpuPolicyLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiCpuPolicyLib/PeiCpuPolicyLib.inf
  CpuPolicyLibPreMem|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiCpuPolicyLibPreMem/PeiCpuPolicyLibPreMem.inf
#
# System Agent
#
  PeiSaPolicyLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/PeiSaPolicyLib/PeiSaPolicyLib.inf

#
# Memory
#
  MemoryAddressEncodeDecodeLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/MemoryInit/Library/PeiDxeSmmMemoryAddressEncodeDecodeLib/PeiDxeSmmMemoryAddressEncodeDecodeLib.inf

[LibraryClasses]
  #
  # Entry point
  #
  PeiCoreEntryPoint|MdePkg/Library/PeiCoreEntryPoint/PeiCoreEntryPoint.inf
  PeimEntryPoint|MdePkg/Library/PeimEntryPoint/PeimEntryPoint.inf
  #
  # Basic
  #
  DebugPrintErrorLevelLib|$(FSP_PACKAGE)/Library/DebugPrintErrorLevelLib/FspDebugPrintErrorLevelLib.inf
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
  PciLib|MdePkg/Library/BasePciLibPciExpress/BasePciLibPciExpress.inf
  PciCf8Lib|MdePkg/Library/BasePciCf8Lib/BasePciCf8Lib.inf
  PciExpressLib|MdePkg/Library/BasePciExpressLib/BasePciExpressLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLibRepStr/BaseMemoryLibRepStr.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  PeCoffGetEntryPointLib|MdePkg/Library/BasePeCoffGetEntryPointLib/BasePeCoffGetEntryPointLib.inf
  CacheMaintenanceLib|MdePkg/Library/BaseCacheMaintenanceLib/BaseCacheMaintenanceLib.inf
  PeCoffLib|MdePkg/Library/BasePeCoffLib/BasePeCoffLib.inf
  PeCoffExtraActionLib|MdePkg/Library/BasePeCoffExtraActionLibNull/BasePeCoffExtraActionLibNull.inf
  UefiDecompressLib|$(PLATFORM_SI_PACKAGE)/Override/MdePkg/Library/BaseUefiDecompressLib/BaseUefiDecompressLib.inf  # SICO-KBL-0009: RoyalParkOverrideContent
  SynchronizationLib|MdePkg/Library/BaseSynchronizationLib/BaseSynchronizationLib.inf
  CpuLib|MdePkg/Library/BaseCpuLib/BaseCpuLib.inf
  #
  # UEFI & PI
  #
  PeiServicesTablePointerLib|MdePkg/Library/PeiServicesTablePointerLibIdt/PeiServicesTablePointerLibIdt.inf
  PeiServicesLib|MdePkg/Library/PeiServicesLib/PeiServicesLib.inf
  #
  # Generic Modules
  #
  OemHookStatusCodeLib|MdeModulePkg/Library/OemHookStatusCodeLibNull/OemHookStatusCodeLibNull.inf

  #
  # Misc
  #
  MtrrLib|UefiCpuPkg/Library/MtrrLib/MtrrLib.inf
  LocalApicLib|UefiCpuPkg/Library/BaseXApicX2ApicLib/BaseXApicX2ApicLib.inf
  ### Base on debug/release mode, choose one of the DebugLib
  ####  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
  UefiCpuLib|UefiCpuPkg/Library/BaseUefiCpuLib/BaseUefiCpuLib.inf

[LibraryClasses.IA32.SEC]
  MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
  TimerLib|$(FSP_PACKAGE)/Library/TscAcpiTimerLib/SecTscTimerLib.inf

[LibraryClasses.IA32.SEC,LibraryClasses.IA32.PEI_CORE]
!if $(TARGET) == DEBUG
  DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
!else
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
!endif

[LibraryClasses.IA32.PEIM]
!if $(TARGET) == DEBUG
  DebugLib|$(FSP_PACKAGE)/Library/FspDebugLibService/FspDebugLibService.inf
!else
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
!endif

[LibraryClasses.IA32.PEIM,LibraryClasses.IA32.PEI_CORE]
  MmPciLib|$(PLATFORM_SI_PACKAGE)/Library/PeiDxeSmmMmPciLib/PeiDxeSmmMmPciLib.inf
  TimerLib|$(FSP_PACKAGE)/Library/TscAcpiTimerLib/PeiTscTimerLib.inf

[LibraryClasses.IA32.PEIM,LibraryClasses.IA32.PEI_CORE,LibraryClasses.IA32.SEC]
  #
  # SEC and PEI phase common
  #
  S3BootScriptLib|MdePkg/Library/BaseS3BootScriptLibNull/BaseS3BootScriptLibNull.inf
  PcdLib|MdePkg/Library/PeiPcdLib/PeiPcdLib.inf
  HobLib|MdePkg/Library/PeiHobLib/PeiHobLib.inf
  FspSwitchStackLib|IntelFsp2Pkg/Library/BaseFspSwitchStackLib/BaseFspSwitchStackLib.inf
  SecPlatformLib|$(PLATFORM_SI_PACKAGE)/SampleCode/Library/PlatformSecLib/FspTPlatformSecLib.inf
  SecCpuLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/SecCpuLib/SecCpuLibFsp.inf
  SecPchLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/SecPchLib/SecPchLibFsp.inf
  SecSaLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/SecSaLib/SecSaLib.inf
  CacheAsRamLib|$(FSP_PACKAGE)/Library/BaseCacheAsRamLib/BaseCacheAsRamLib.inf
  FspCommonLib|IntelFsp2Pkg/Library/BaseFspCommonLib/BaseFspCommonLib.inf
  FspPlatformLib|IntelFsp2Pkg/Library/BaseFspPlatformLib/BaseFspPlatformLib.inf

!if $(TARGET) == DEBUG
  SerialPortLib|$(FSP_PACKAGE)/Library/SerialPortLib/SerialPortLib.inf
!else
  SerialPortLib|MdePkg/Library/BaseSerialPortLibNull/BaseSerialPortLibNull.inf
!endif

  MemoryAllocationLib|MdePkg/Library/PeiMemoryAllocationLib/PeiMemoryAllocationLib.inf
  PostCodeLib|$(FSP_PACKAGE)/Library/BasePostCodeLibPort80Ex/BasePostCodeLibPort80Ex.inf
  ReportStatusCodeLib|MdeModulePkg/Library/PeiReportStatusCodeLib/PeiReportStatusCodeLib.inf
!if gKabylakeFspPkgTokenSpaceGuid.PcdFspPerformanceEnable == TRUE
  PerformanceLib|$(PLATFORM_SI_PACKAGE)/Override/ClientSiliconPkg/Library/PeiPerformanceLibFpdt/PeiPerformanceLibFpdt.inf  # SICO-KBL-0001
!else
  PerformanceLib|MdeModulePkg/Library/PeiPerformanceLib/PeiPerformanceLib.inf
!endif

  #
  # Silicon initialization library
  #
  PchPciExpressHelpersLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmPchPciExpressHelpersLib/PeiDxeSmmPchPciExpressHelpersLib.inf

  GpioLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmGpioLib/PeiDxeSmmGpioLib.inf
  GpioPrivateLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmGpioPrivateLib/PeiDxeSmmGpioPrivateLib.inf
  PchCycleDecodingLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchCycleDecodingLib/PeiDxeSmmPchCycleDecodingLib.inf
  PchGbeLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchGbeLib/PeiDxeSmmPchGbeLib.inf
  PchHsioLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchHsioLib/PeiDxeSmmPchHsioLib.inf
  PchInfoLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchInfoLib/PeiDxeSmmPchInfoLib.inf
  PchP2sbLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchP2sbLib/PeiDxeSmmPchP2sbLib.inf
  PchPcieRpLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchPcieRpLib/PeiDxeSmmPchPcieRpLib.inf
  PchPcrLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchPcrLib/PeiDxeSmmPchPcrLib.inf
  PchPmcLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchPmcLib/PeiDxeSmmPchPmcLib.inf
  PchSbiAccessLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchSbiAccessLib/PeiDxeSmmPchSbiAccessLib.inf
  PchSerialIoLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchSerialIoLib/PeiDxeSmmPchSerialIoLib.inf
  PchSerialIoUartLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchSerialIoUartLib/PeiDxeSmmPchSerialIoUartLib.inf
  PchPsfPrivateLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmPchPsfPrivateLib/PeiDxeSmmPchPsfPrivateLib.inf
  PchPsfLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchPsfLib/PeiDxeSmmPchPsfLib.inf
  BootGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmBootGuardLib/PeiDxeSmmBootGuardLib.inf
  CpuPlatformLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmCpuPlatformLib/PeiDxeSmmCpuPlatformLib.inf
  SaPlatformLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/PeiDxeSmmSaPlatformLib/PeiDxeSmmSaPlatformLib.inf
  SoftwareGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiDxeSoftwareGuardLib/PeiDxeSoftwareGuardLib.inf
  TxtLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeTxtLib/PeiDxeTxtLib.inf
  SmbusLib|MdePkg/Library/BaseSmbusLibNull/BaseSmbusLibNull.inf
  RngLib|MdePkg/Library/BaseRngLib/BaseRngLib.inf
  CpuMailboxLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmCpuMailboxLib/PeiDxeSmmCpuMailboxLib.inf

################################################################################
#
# Pcd Section - list of all EDK II PCD Entries defined by this Platform
#
################################################################################
[PcdsFeatureFlag.common]

[PcdsFixedAtBuild]
!if $(TARGET) == DEBUG
  gKabylakeFspPkgTokenSpaceGuid.PcdMrcDebugMsg              | 0x02
!else
  gKabylakeFspPkgTokenSpaceGuid.PcdMrcDebugMsg              | 0x00
!endif

  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask            | 0x27
  gIntelFsp2PkgTokenSpaceGuid.PcdTemporaryRamBase           | 0xFEF00000
  gIntelFsp2PkgTokenSpaceGuid.PcdTemporaryRamSize           | 0x00040000
!if gSiPkgTokenSpaceGuid.PcdSsaFlagEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdEvLoaderEnable == TRUE
  gIntelFsp2PkgTokenSpaceGuid.PcdFspTemporaryRamSize        | 0x00030000
!else
  gIntelFsp2PkgTokenSpaceGuid.PcdFspTemporaryRamSize        | 0x00026000
!endif
!else
  gIntelFsp2PkgTokenSpaceGuid.PcdFspTemporaryRamSize        | 0x00026000
!endif

  # This defines how much space will be used for heap in FSP temporary memory
  # x % of FSP temporary memory will be used for heap
  # (100 - x) % of FSP temporary memory will be used for stack
  gIntelFsp2PkgTokenSpaceGuid.PcdFspHeapSizePercentage      | 50

  # This is a platform specific global pointer used by FSP
  gIntelFsp2PkgTokenSpaceGuid.PcdGlobalDataPointerAddress   | 0xFED00148

  # Override PcdFspMaxPatchEntry to match FspHeader.aslc
  gIntelFsp2PkgTokenSpaceGuid.PcdFspMaxPatchEntry           | 0x02

  # Temp solution to avoid halt in PeiVariable->GetVariable (PeiGetVariable)
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableBase               |0xFFF80000
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableSize               |0x10000

  gIntelFsp2PkgTokenSpaceGuid.PcdFspReservedMemoryLength    | 0x00400000


  ## Specifies the size of the microcode Region.
  # @Prompt Microcode Region size.
  gUefiCpuPkgTokenSpaceGuid.PcdCpuMicrocodePatchRegionSize|0

  ## Specifies timeout value in microseconds for the BSP to detect all APs for the first time.
  # @Prompt Timeout for the BSP to detect all APs for the first time.
  gUefiCpuPkgTokenSpaceGuid.PcdCpuApInitTimeOutInMicroSeconds|1000

!if gKabylakeFspPkgTokenSpaceGuid.PcdFspPerformanceEnable == TRUE
  gEfiMdePkgTokenSpaceGuid.PcdPerformanceLibraryPropertyMask|0x1
  gEfiMdeModulePkgTokenSpaceGuid.PcdMaxPeiPerformanceLogEntries|120
!endif

[PcdsPatchableInModule]
!if $(TARGET) == DEBUG
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel         | 0x80000042
!else
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel         | 0x00000001
!endif
  #
  # This entry will be patched during the build process
  #
  gEfiMdeModulePkgTokenSpaceGuid.PcdVpdBaseAddress         | 0x12345678

[PcdsDynamicDefault]
  ## Specifies max supported number of Logical Processors.
  # @Prompt Configure max supported number of Logical Processorss
  gUefiCpuPkgTokenSpaceGuid.PcdCpuMaxLogicalProcessorNumber | 12
  gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress         | 0xE0000000
  gSiPkgTokenSpaceGuid.PcdPciExpressRegionLength            | 0x10000000

  ## Specifies the AP wait loop state during POST phase.
  #  The value is defined as below.
  #  1: Place AP in the Hlt-Loop state.
  #  2: Place AP in the Mwait-Loop state.
  #  3: Place AP in the Run-Loop state.
  # @Prompt The AP wait loop state.
  gUefiCpuPkgTokenSpaceGuid.PcdCpuApLoopMode|2

[PcdsDynamicVpd.Upd]
  #
  # This section is not used by the normal build process
  # Howerver, FSP will use dedicated tool to handle it and generate a
  # VPD simliar binary block (User Configuration Data). This block will
  # be accessed through a generated data structure directly rather than
  # PCD services. This is for size consideration.
  # Format:
  #   gKabylakeFspPkgTokenSpaceGuid.Updxxxxxxxxxxxxn        | OFFSET | LENGTH | VALUE
  # Only simple data type is supported
  #

  #
  # Comments with !BSF will be used to generate BSF file
  # Comments with !HDR will be used to generate H header file
  #

  # Global definitions in BSF
  # !BSF PAGES:{SKL:"Kabylake System Agent", MRC:"Memory Reference Code", SPT:"Sunrise Point PCH"}
  # !BSF BLOCK:{NAME:"KabyLake Platform", VER:"0.1"}

  # !BSF FIND:{KBLUPD_T}
  # !HDR COMMENT:{FSP_UPD_HEADER:FSP UPD Header}
  # !HDR EMBED:{FSP_UPD_HEADER:FspUpdHeader:START}
  # FsptUpdSignature: {KBLUPD_T}
  gKabylakeFspPkgTokenSpaceGuid.Signature                   | 0x0000 | 0x08 | 0x545F4450554C424B
  # !BSF NAME:{FsptUpdRevision}  TYPE:{None}
  gKabylakeFspPkgTokenSpaceGuid.Revision                    | 0x0008 | 0x01 | 0x00
  # !HDR EMBED:{FSP_UPD_HEADER:FspUpdHeader:END}
  gKabylakeFspPkgTokenSpaceGuid.Reserved                    | 0x0009 | 0x17 | {0x00}

  # !HDR COMMENT:{FSPT_CORE_UPD:Fsp T Core UPD}
  # !HDR EMBED:{FSPT_CORE_UPD:FsptCoreUpd:START}
  # Base address of the microcode region.
  gKabylakeFspPkgTokenSpaceGuid.MicrocodeRegionBase         | 0x0020 | 0x04 | 0x00000000

  # Length of the microcode region.
  gKabylakeFspPkgTokenSpaceGuid.MicrocodeRegionSize         | 0x0024 | 0x04 | 0x00000000

  # Base address of the cacheable flash region.
  gKabylakeFspPkgTokenSpaceGuid.CodeRegionBase              | 0x0028 | 0x04 | 0x00000000

  # Length of the cacheable flash region.
  gKabylakeFspPkgTokenSpaceGuid.CodeRegionSize              | 0x002C | 0x04 | 0x00000000

  # !HDR EMBED:{FSPT_CORE_UPD:FsptCoreUpd:END}
  gKabylakeFspPkgTokenSpaceGuid.Reserved                    | 0x0030 | 0x10 | {0x00}

  # !HDR COMMENT:{FSP_T_CONFIG:Fsp T Configuration}
  # !HDR EMBED:{FSP_T_CONFIG:FsptConfig:START}

  # !BSF PAGE:{SPT}
  # !BSF NAME:{PcdSerialIoUartDebugEnable} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable and Initialize, 2:Enable without Initializing}
  # !BSF HELP:{Enable SerialIo Uart debug library with/without initializing SerialIo Uart device in FSP. }
  gSiPkgTokenSpaceGuid.PcdSerialIoUartDebugEnable           | 0x0040 | 0x01 | 0x00

  # !BSF NAME:{PcdSerialIoUartNumber} TYPE:{Combo}
  # !BSF OPTION:{0:SerialIoUart0, 1:SerialIoUart1, 2:SerialIoUart2}
  # !BSF HELP:{Select SerialIo Uart Controller for debug.}
  gSiPkgTokenSpaceGuid.PcdSerialIoUartNumber                | 0x0041 | 0x01 | 0x02
  # This won't be in BSF page

  gSiPkgTokenSpaceGuid.PcdSerialIoUartInputClock            | 0x0044 | 0x04 | 1843200

  #
  # NOTE: If offset for PcdPciExpressBaseAddress & PcdPciExpressRegion is changed,
  # then please change offset accordingly in SecSaInit in SecSaLib.asm & SecSaLibGcc.S
  #

  # !BSF NAME:{Pci Express Base Address}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Base address to be programmed for Pci Express }
  gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress         | 0x0048 | 0x08 | 0xE0000000

  # !BSF NAME:{Pci Express Region Length}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Region Length to be programmed for Pci Express }
  gSiPkgTokenSpaceGuid.PcdPciExpressRegionLength            | 0x0050 | 0x04 | 0x10000000

  # !HDR EMBED:{FSP_T_CONFIG:FsptConfig:END}
  gKabylakeFspPkgTokenSpaceGuid.ReservedFsptUpd1            | 0x0054 | 0x0C | {0x00}

  # Note please keep "UpdTerminator" at the end of each UPD region.
  # The tool will use this field to determine the actual end of the UPD data
  # structure.
  gKabylakeFspPkgTokenSpaceGuid.UpdTerminator               | 0x0066 | 0x02 | 0x55AA

  ################################################################################
  #
  # UPDs consumed in FspMemoryInit Api
  #
  ################################################################################
  # !BSF FIND:{KBLUPD_M}
  # !HDR COMMENT:{FSP_UPD_HEADER:FSP UPD Header}
  # !HDR EMBED:{FSP_UPD_HEADER:FspUpdHeader:START}
  # FspmUpdSignature: {KBLUPD_M}
  gKabylakeFspPkgTokenSpaceGuid.Signature                   | 0x0000 | 0x08 | 0x4D5F4450554C424B
  # !BSF NAME:{FspmUpdRevision}  TYPE:{None}
  gKabylakeFspPkgTokenSpaceGuid.Revision                    | 0x0008 | 0x01 | 0x00
  # !HDR EMBED:{FSP_UPD_HEADER:FspUpdHeader:END}
  gKabylakeFspPkgTokenSpaceGuid.Reserved                    | 0x0009 | 0x17 | {0x00}

  # !HDR COMMENT:{FSPM_ARCH_UPD:Fsp M Architecture UPD}
  # !HDR EMBED:{FSPM_ARCH_UPD:FspmArchUpd:START}
  gKabylakeFspPkgTokenSpaceGuid.Revision                    | 0x0020 | 0x01 | 0x01

  gKabylakeFspPkgTokenSpaceGuid.Reserved                    | 0x0021 | 0x03 | {0x00}

  # !HDR STRUCT:{VOID *}
  gKabylakeFspPkgTokenSpaceGuid.NvsBufferPtr                | 0x0024 | 0x04 | 0x00000000

  # !HDR STRUCT:{VOID *}
  gKabylakeFspPkgTokenSpaceGuid.StackBase                   | 0x0028 | 0x04 | 0xFEF17F00

!if gSiPkgTokenSpaceGuid.PcdSsaFlagEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdEvLoaderEnable == TRUE
  gKabylakeFspPkgTokenSpaceGuid.StackSize                   | 0x002C | 0x04 | 0x30000
!else
  gKabylakeFspPkgTokenSpaceGuid.StackSize                   | 0x002C | 0x04 | 0x28000
!endif
!else
  gKabylakeFspPkgTokenSpaceGuid.StackSize                   | 0x002C | 0x04 | 0x28000
!endif

  gKabylakeFspPkgTokenSpaceGuid.BootLoaderTolumSize         | 0x0030 | 0x04 | 0x00000000

  gKabylakeFspPkgTokenSpaceGuid.BootMode                    | 0x0034 | 0x04 | 0x00

  # !HDR EMBED:{FSPM_ARCH_UPD:FspmArchUpd:END}
  gKabylakeFspPkgTokenSpaceGuid.Reserved1                   | 0x0038 | 0x08 | {0x00}

  # !HDR COMMENT:{FSP_M_CONFIG:Fsp M Configuration}
  # !HDR EMBED:{FSP_M_CONFIG:FspmConfig:START}
  # !BSF PAGE:{MRC}
  # !BSF NAME:{Platform Reserved Memory Size}
  # !BSF TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{The minimum platform memory size required to pass control into DXE}
  gPlatformFspPkgTokenSpaceGuid.PlatformMemorySize          | 0x0040 | 0x08 | 0x440000

  # !BSF NAME:{Memory SPD Pointer Channel 0 Dimm 0}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Pointer to SPD data in Memory}
  gKabylakeFspPkgTokenSpaceGuid.MemorySpdPtr00              | 0x0048 | 0x04 | 0x00000000

  # !BSF NAME:{Memory SPD Pointer Channel 0 Dimm 1}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Pointer to SPD data in Memory}
  gKabylakeFspPkgTokenSpaceGuid.MemorySpdPtr01              | 0x004C | 0x04 | 0x00000000

  # !BSF NAME:{Memory SPD Pointer Channel 1 Dimm 0}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Pointer to SPD data in Memory}
  gKabylakeFspPkgTokenSpaceGuid.MemorySpdPtr10              | 0x0050 | 0x04 | 0x00000000

  # !BSF NAME:{Memory SPD Pointer Channel 1 Dimm 1}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Pointer to SPD data in Memory}
  gKabylakeFspPkgTokenSpaceGuid.MemorySpdPtr11              | 0x0054 | 0x04 | 0x00000000

  # !BSF NAME:{SPD Data Length} TYPE:{Combo}
  # !BSF OPTION:{0x100:256 Bytes, 0x200:512 Bytes}
  # !BSF HELP:{Length of SPD Data}
  gKabylakeFspPkgTokenSpaceGuid.MemorySpdDataLen            | 0x0058 | 0x02 | 0x100

  # !BSF NAME:{Dq Byte Map CH0} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Dq byte mapping between CPU and DRAM, Channel 0: board-dependent}
  gKabylakeFspPkgTokenSpaceGuid.DqByteMapCh0                | 0x005A | 0x0C | { 0x0F, 0xF0, 0x00, 0xF0, 0x0F, 0xF0, 0x0F, 0x00, 0xFF, 0x00, 0xFF, 0x00 }

  # !BSF NAME:{Dq Byte Map CH1} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Dq byte mapping between CPU and DRAM, Channel 1: board-dependent}
  gKabylakeFspPkgTokenSpaceGuid.DqByteMapCh1                | 0x0066 | 0x0C | { 0x0F, 0xF0, 0x00, 0xF0, 0x0F, 0xF0, 0x0F, 0x00, 0xFF, 0x00, 0xFF, 0x00 }

  # !BSF NAME:{Dqs Map CPU to DRAM CH 0} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Set Dqs mapping relationship between CPU and DRAM, Channel 0: board-dependent}
  gKabylakeFspPkgTokenSpaceGuid.DqsMapCpu2DramCh0           | 0x0072 | 0x08 | { 2, 0, 1, 3, 6, 4, 7, 5 }

  # !BSF NAME:{Dqs Map CPU to DRAM CH 1} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Set Dqs mapping relationship between CPU and DRAM, Channel 1: board-dependent}
  gKabylakeFspPkgTokenSpaceGuid.DqsMapCpu2DramCh1           | 0x007A | 0x08 | { 1, 3, 2, 0, 5, 7, 6, 4 }

  # !BSF NAME:{RcompResister settings} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Indicates  RcompReister settings: Board-dependent}
  gKabylakeFspPkgTokenSpaceGuid.RcompResistor               | 0x0082 | 0x06 | { 200, 81, 162 }

  # !BSF NAME:{RcompTarget settings} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{RcompTarget settings: board-dependent}
  gKabylakeFspPkgTokenSpaceGuid.RcompTarget                 | 0x0088 | 0x0A | { 100, 40, 40, 23, 40 }

  # !BSF NAME:{Dqs Pins Interleaved Setting} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Indicates DqPinsInterleaved setting: board-dependent}
  gKabylakeFspPkgTokenSpaceGuid.DqPinsInterleaved           | 0x0092 | 0x01 | 0x0

  # !BSF NAME:{VREF_CA} TYPE:{Combo}
  # !BSF OPTION:{0:VREF_CA goes to both CH_A and CH_B, 1: VREF_CA to CH_A and VREF_DQ_A to CH_B, 2:VREF_CA to CH_A and VREF_DQ_B to CH_B}
  # !BSF HELP:{CA Vref routing: board-dependent}
  gKabylakeFspPkgTokenSpaceGuid.CaVrefConfig                | 0x0093 | 0x01 | 0x0

  # !BSF NAME:{Smram Mask} TYPE:{Combo}
  # !BSF OPTION:{0: Neither, 1:AB-SEG, 2:H-SEG, 3: Both}
  # !BSF HELP:{The SMM Regions AB-SEG and/or H-SEG reserved}
  gKabylakeFspPkgTokenSpaceGuid.SmramMask                   | 0x0094 | 0x01 | 0x0

  # !BSF NAME:{MRC Fast Boot} TYPE:{Combo}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable the MRC fast path thru the MRC}
  gKabylakeFspPkgTokenSpaceGuid.MrcFastBoot                 | 0x0095 | 0x01 | 0x1

  # !BSF NAME:{Intel Enhanced Debug} TYPE:{Combo}
  # !BSF OPTION:{0 : Disable, 0x400000 : Enable}
  # !BSF HELP:{Intel Enhanced Debug (IED): 0=Disabled, 0x400000=Enabled and 4MB SMRAM occupied}
  gKabylakeFspPkgTokenSpaceGuid.IedSize                     | 0x0098 | 0x04 | 0x00000000

  # !BSF NAME:{Tseg Size} TYPE:{Combo}
  # !BSF OPTION:{0x0400000:4MB, 0x01000000:16MB}
  # !BSF HELP:{Size of SMRAM memory reserved. 0x400000 for Release build and 0x1000000 for Debug build}
!if $(TARGET) == DEBUG
  gKabylakeFspPkgTokenSpaceGuid.TsegSize                    | 0x009C | 0x04 | 0x01000000
!else
  gKabylakeFspPkgTokenSpaceGuid.TsegSize                    | 0x009C | 0x04 | 0x0400000
!endif

  # !BSF NAME:{MMIO Size} TYPE:{EditNum, HEX, (0,0xC00)}
  # !BSF HELP:{Size of MMIO space reserved for devices. 0(Default)=Auto, non-Zero=size in MB}
  gKabylakeFspPkgTokenSpaceGuid.MmioSize                    | 0x00A0 | 0x02 | 0x0

  # !BSF NAME:{Probeless Trace}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Probeless Trace: 0=Disabled, 1=Enable. Enabling Probeless Trace will reserve 128MB. This also requires IED to be enabled.}
  gKabylakeFspPkgTokenSpaceGuid.ProbelessTrace              | 0x00A2 | 0x01 | 0x00

  # PCH configuration


  # !BSF NAME:{Enable SMBus} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable SMBus controller.}
  gKabylakeFspPkgTokenSpaceGuid.SmbusEnable                 | 0x00A5 | 0x01 | 0x01

  # !BSF NAME:{Enable Trace Hub} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable Trace Hub function.}
  gKabylakeFspPkgTokenSpaceGuid.EnableTraceHub              | 0x00A6 | 0x01 | 0x00

  # !BSF NAME:{DpSscMarginEnable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, Use default DisplayPort SSC modulation range 0.5% down spread, 1: Enable DisplayPort SSC range reduction. Note this should only be used on systems that exceeds allowed SSC modulation range as defined in VESA's spec}
  gKabylakeFspPkgTokenSpaceGuid.DpSscMarginEnable            | 0x0A7 | 0x01 | 0x00

  # !BSF NAME:{Internal Graphics Pre-allocated Memory} TYPE:{Combo}
  # !BSF OPTION:{0x00:0 MB, 0x01:32 MB, 0x02:64 MB}
  # !BSF HELP:{Size of memory preallocated for internal graphics.}
  gKabylakeFspPkgTokenSpaceGuid.IgdDvmt50PreAlloc           | 0x00E3 | 0x01 | 0x01

  # !BSF NAME:{Internal Graphics} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable internal graphics.}
  gKabylakeFspPkgTokenSpaceGuid.InternalGfx                 | 0x00E4 | 0x01 | 0x01

  # !BSF NAME:{Aperture Size} TYPE:{Combo}
  # !BSF OPTION:{0:128 MB, 1:256 MB, 2:512 MB}
  # !BSF HELP:{Select the Aperture Size.}
  gKabylakeFspPkgTokenSpaceGuid.ApertureSize                | 0x00E5 | 0x01 | 0x01

  # !BSF PAGE:{SKL}
  # !BSF NAME:{SA GV} TYPE:{Combo}
  # !BSF OPTION:{0:Disabled, 1:FixedLow, 2:FixedHigh, 3:Enabled}
  # !BSF HELP:{System Agent dynamic frequency support and when enabled memory will be training at two different frequencies. Only effects ULX/ULT CPUs. 0=Disabled, 1=FixedLow, 2=FixedHigh, and 3=Enabled.}
  gKabylakeFspPkgTokenSpaceGuid.SaGv                        | 0x00E6 | 0x01 | 0x00

  # !BSF PAGE:{MRC}
  # !BSF NAME:{Rank Margin Tool}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable Rank Margin Tool.}
  gKabylakeFspPkgTokenSpaceGuid.RMT                         | 0x00E7 | 0x01 | 0x00

  # !BSF NAME:{DDR Frequency Limit}
  # !BSF TYPE:{Combo} OPTION:{1067:1067, 1333:1333, 1600:1600, 1867:1867, 2133:2133, 2400:2400, 0:Auto}
  # !BSF HELP:{Maximum Memory Frequency Selections in Mhz. Options are 1067, 1333, 1600, 1867, 2133, 2400 and 0 for Auto.}
  gKabylakeFspPkgTokenSpaceGuid.DdrFreqLimit                | 0x00E8 | 0x02 | 0

  # !BSF NAME:{Board Type}
  # !BSF TYPE:{Combo} OPTION:{0:Mobile/Mobile Halo, 1:Desktop/DT Halo, 5:ULT/ULX/Mobile Halo, 7:UP Server}
  # !BSF HELP:{MrcBoardType, Options are 0=Mobile/Mobile Halo, 1=Desktop/DT Halo, 5=ULT/ULX/Mobile Halo, 7=UP Server}
  gKabylakeFspPkgTokenSpaceGuid.UserBd                      | 0x00EA | 0x01 | 0x00

  # !BSF NAME:{MMA Test Content Pointer}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{Pointer to MMA Test Content in Memory}
  gKabylakeFspPkgTokenSpaceGuid.MmaTestContentPtr           | 0x0154 | 0x04 | 0x00000000

  # !BSF NAME:{MMA Test Content Size}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{Size of MMA Test Content in Memory}
  gKabylakeFspPkgTokenSpaceGuid.MmaTestContentSize          | 0x0158 | 0x04 | 0x00000000

  # !BSF NAME:{MMA Test Config Pointer}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{Pointer to MMA Test Config in Memory}
  gKabylakeFspPkgTokenSpaceGuid.MmaTestConfigPtr            | 0x015C | 0x04 | 0x00000000

  # !BSF NAME:{MMA Test Config Size}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{Size of MMA Test Config in Memory}
  gKabylakeFspPkgTokenSpaceGuid.MmaTestConfigSize           | 0x0160 | 0x04 | 0x00000000

  # !BSF NAME:{SPD Profile Selected}
  # !BSF TYPE:{Combo} OPTION:{0:Default profile, 1:Custom profile, 2:XMP profile 1, 3:XMP profile 2}
  # !BSF HELP:{Select DIMM timing profile. Options are 0=Default profile, 1=Custom profile, 2=XMP Profile 1, 3=XMP Profile 2}
  gKabylakeFspPkgTokenSpaceGuid.SpdProfileSelected          | 0x0177 | 0x01 | 0x00

  # !BSF NAME:{Memory Voltage}
  # !BSF TYPE:{Combo} OPTION:{0:Default, 1100:1.10 Volts, 1150:1.15 Volts, 1200:1.20 Volts, 1250:1.25 Volts, 1300:1.30 Volts, 1350:1.35 Volts, 1400:1.40 Volts, 1450:1.45 Volts, 1500:1.50 Volts, 1550:1.55 Volts, 1600:1.60 Volts, 1650:1.65 Volts}
  # !BSF HELP:{Memory Voltage Override (Vddq). Default = no override}
  gKabylakeFspPkgTokenSpaceGuid.VddVoltage                  | 0x0178 | 0x02 | 0x0000

  # !BSF NAME:{Memory Reference Clock}
  # !BSF TYPE:{Combo} OPTION:{0:Auto, 1:133MHz, 2:100MHz}
  # !BSF HELP:{Automatic, 100MHz, 133MHz.}
  gKabylakeFspPkgTokenSpaceGuid.RefClk                      | 0x017A | 0x01 | 0x01

  # !BSF NAME:{Memory Ratio}
  # !BSF TYPE:{Combo} OPTION:{0:Auto, 4:4, 5:5, 6:6, 7:7, 8:8, 9:9, 10:10, 11:11, 12:12, 13:13, 14:14, 15:15}
  # !BSF HELP:{Automatic or the frequency will equal ratio times reference clock. Set to Auto to recalculate memory timings listed below.}
  gKabylakeFspPkgTokenSpaceGuid.Ratio                       | 0x017B | 0x01 | 0x00

  # !BSF NAME:{QCLK Odd Ratio}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Adds 133 or 100 MHz to QCLK frequency, depending on RefClk}
  gKabylakeFspPkgTokenSpaceGuid.OddRatioMode                | 0x017C | 0x01 | 0x00

  # !BSF NAME:{tCL}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x1F)}
  # !BSF HELP:{CAS Latency, 0: AUTO, max: 31}
  gKabylakeFspPkgTokenSpaceGuid.tCL                         | 0x017D | 0x01 | 0x00

  # !BSF NAME:{tFAW}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x3F)}
  # !BSF HELP:{Min Four Activate Window Delay Time, 0: AUTO, max: 63}
  gKabylakeFspPkgTokenSpaceGuid.tFAW                        | 0x017E | 0x02 | 0x0000

  # !BSF NAME:{tRAS}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x40)}
  # !BSF HELP:{RAS Active Time, 0: AUTO, max: 64}
  gKabylakeFspPkgTokenSpaceGuid.tRAS                        | 0x0180 | 0x02 | 0x0000

  # !BSF NAME:{tCWL}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x14)}
  # !BSF HELP:{Min CAS Write Latency Delay Time, 0: AUTO, max: 20}
  gKabylakeFspPkgTokenSpaceGuid.tCWL                        | 0x0182 | 0x01 | 0x00

  # !BSF NAME:{tRCD/tRP}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x3F)}
  # !BSF HELP:{RAS to CAS delay time and Row Precharge delay time, 0: AUTO, max: 63}
  gKabylakeFspPkgTokenSpaceGuid.tRCDtRP                     | 0x0183 | 0x01 | 0x00

  # !BSF NAME:{tREFI}
  # !BSF TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Refresh Interval, 0: AUTO, max: 65535}
  gKabylakeFspPkgTokenSpaceGuid.tREFI                       | 0x0184 | 0x02 | 0x0000

  # !BSF NAME:{tRFC}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x3FF)}
  # !BSF HELP:{Min Refresh Recovery Delay Time, 0: AUTO, max: 1023}
  gKabylakeFspPkgTokenSpaceGuid.tRFC                        | 0x0186 | 0x02 | 0x0000

  # !BSF NAME:{tRRD}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x0F)}
  # !BSF HELP:{Min Row Active to Row Active Delay Time, 0: AUTO, max: 15}
  gKabylakeFspPkgTokenSpaceGuid.tRRD                        | 0x0188 | 0x01 | 0x00

  # !BSF NAME:{tRTP}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x0F)}
  # !BSF HELP:{Min Internal Read to Precharge Command Delay Time, 0: AUTO, max: 15. DDR4 legal values: 5, 6, 7, 8, 9, 10, 12}
  gKabylakeFspPkgTokenSpaceGuid.tRTP                        | 0x0189 | 0x01 | 0x00

  # !BSF NAME:{tWR}
  # !BSF TYPE:{Combo} OPTION:{0:Auto, 5:5, 6:6, 7:7, 8:8, 10:10, 12:12, 14:14, 16:16, 18:18, 20:20, 24:24}
  # !BSF HELP:{Min Write Recovery Time, 0: AUTO, legal values: 5, 6, 7, 8, 10, 12, 14, 16, 18, 20, 24}
  gKabylakeFspPkgTokenSpaceGuid.tWR                         | 0x018A | 0x01 | 0x00

  # !BSF NAME:{tWTR}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x1C)}
  # !BSF HELP:{Min Internal Write to Read Command Delay Time, 0: AUTO, max: 28}
  gKabylakeFspPkgTokenSpaceGuid.tWTR                        | 0x018B | 0x01 | 0x00

  # !BSF NAME:{NMode}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x02)}
  # !BSF HELP:{System command rate, range 0-2, 0 means auto, 1 = 1N, 2 = 2N}
  gKabylakeFspPkgTokenSpaceGuid.NModeSupport                | 0x018C | 0x01 | 0x00

  # !BSF NAME:{DllBwEn[0]}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x07)}
  # !BSF HELP:{DllBwEn[0], for 1067 (0..7)}
  gKabylakeFspPkgTokenSpaceGuid.DllBwEn0                    | 0x018D | 0x01 | 0x00

  # !BSF NAME:{DllBwEn[1]}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x07)}
  # !BSF HELP:{DllBwEn[1], for 1333 (0..7)}
  gKabylakeFspPkgTokenSpaceGuid.DllBwEn1                    | 0x018E | 0x01 | 0x01

  # !BSF NAME:{DllBwEn[2]}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x07)}
  # !BSF HELP:{DllBwEn[2], for 1600 (0..7)}
  gKabylakeFspPkgTokenSpaceGuid.DllBwEn2                    | 0x018F | 0x01 | 0x02

  # !BSF NAME:{DllBwEn[3]}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x07)}
  # !BSF HELP:{DllBwEn[3], for 1867 and up (0..7)}
  gKabylakeFspPkgTokenSpaceGuid.DllBwEn3                    | 0x0190 | 0x01 | 0x02

  # !BSF NAME:{Command Tristate Support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable Command Tristate; <b>0: Enable</b>; 1: Disable.}
  gKabylakeFspPkgTokenSpaceGuid.CmdTriStateDis              | 0x0191 | 0x01 | 0x00


  # ME configuration

  # !BSF NAME:{HECI1 BAR address}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{BAR address of HECI1}
  gKabylakeFspPkgTokenSpaceGuid.Heci1BarAddress             | 0x01A0 | 0x04 | 0xFED1A000

  # !BSF NAME:{HECI2 BAR address}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{BAR address of HECI2}
  gKabylakeFspPkgTokenSpaceGuid.Heci2BarAddress             | 0x01A4 | 0x04 | 0xFED1B000

  # !BSF NAME:{HECI3 BAR address}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{BAR address of HECI3}
  gKabylakeFspPkgTokenSpaceGuid.Heci3BarAddress             | 0x01A8 | 0x04 | 0xFED1C000

  # !BSF NAME:{HECI Timeouts} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, disable timeout check for HECI, 1: enable}
  gKabylakeFspPkgTokenSpaceGuid.HeciTimeouts                | 0x01AC | 0x01 | 0x01

  #
  # SA Pre-Mem Production Block Start
  #
  # !BSF NAME:{SG dGPU Power Delay} TYPE:{EditNum, HEX, (0,1000)}
  # !BSF HELP:{SG dGPU delay interval after power enabling: 0=Minimal, 1000=Maximum, default is 300=300 microseconds}
  gKabylakeFspPkgTokenSpaceGuid.SgDelayAfterPwrEn           | 0x0220 | 0x02 | 300

  # !BSF NAME:{SG dGPU Reset Delay} TYPE:{EditNum, HEX, (0,1000)}
  # !BSF HELP:{SG dGPU delay interval for Reset complete: 0=Minimal, 1000=Maximum, default is 100=100 microseconds}
  gKabylakeFspPkgTokenSpaceGuid.SgDelayAfterHoldReset       | 0x0222 | 0x02 | 100

  # !BSF NAME:{MMIO size adjustment for AUTO mode} TYPE:{EditNum, HEX, (0, 0xFFFF)}
  # !BSF HELP:{Positive number means increasing MMIO size, Negative value means decreasing MMIO size: 0 (Default)=no change to AUTO mode MMIO size}
  gKabylakeFspPkgTokenSpaceGuid.MmioSizeAdjustment          | 0x0224 | 0x02 | 0

  # !BSF NAME:{Enable/Disable DMI GEN3 Static EQ Phase1 programming} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Program DMI Gen3 EQ Phase1 Static Presets. Disabled(0x0): Disable EQ Phase1 Static Presets Programming, Enabled(0x1)(Default): Enable  EQ Phase1 Static Presets Programming}
  gKabylakeFspPkgTokenSpaceGuid.DmiGen3ProgramStaticEq      | 0x226 | 0x01 | 0x1

  # !BSF NAME:{Enable/Disable PEG 0} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable, 2:AUTO}
  # !BSF HELP:{Disabled(0x0): Disable PEG Port, Enabled(0x1): Enable PEG Port (If Silicon SKU permits it), Auto(0x2)(Default): If an endpoint is present, enable the PEG Port, Disable otherwise}
  gKabylakeFspPkgTokenSpaceGuid.Peg0Enable                  | 0x227 | 0x01 | 0x2

  # !BSF NAME:{Enable/Disable PEG 1} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable, 2:AUTO}
  # !BSF HELP:{Disabled(0x0): Disable PEG Port, Enabled(0x1): Enable PEG Port (If Silicon SKU permits it), Auto(0x2)(Default): If an endpoint is present, enable the PEG Port, Disable otherwise}
  gKabylakeFspPkgTokenSpaceGuid.Peg1Enable                  | 0x228 | 0x01 | 0x2

  # !BSF NAME:{Enable/Disable PEG 2} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable, 2:AUTO}
  # !BSF HELP:{Disabled(0x0): Disable PEG Port, Enabled(0x1): Enable PEG Port (If Silicon SKU permits it), Auto(0x2)(Default): If an endpoint is present, enable the PEG Port, Disable otherwise}
  gKabylakeFspPkgTokenSpaceGuid.Peg2Enable                  | 0x229 | 0x01 | 0x2

  # !BSF NAME:{PEG 0 Max Link Speed} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:Gen1, 2:Gen2, 3:Gen3}
  # !BSF HELP:{Auto (Default)(0x0): Maximum possible link speed, Gen1(0x1): Limit Link to Gen1 Speed, Gen2(0x2): Limit Link to Gen2 Speed, Gen3(0x3):Limit Link to Gen3 Speed}
  gKabylakeFspPkgTokenSpaceGuid.Peg0MaxLinkSpeed            | 0x22A | 0x01 | 0x00

  # !BSF NAME:{PEG 1 Max Link Speed} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:Gen1, 2:Gen2, 3:Gen3}
  # !BSF HELP:{Auto (Default)(0x0): Maximum possible link speed, Gen1(0x1): Limit Link to Gen1 Speed, Gen2(0x2): Limit Link to Gen2 Speed, Gen3(0x3):Limit Link to Gen3 Speed}
  gKabylakeFspPkgTokenSpaceGuid.Peg1MaxLinkSpeed            | 0x22B | 0x01 | 0x00

  # !BSF NAME:{PEG 2 Max Link Speed} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:Gen1, 2:Gen2, 3:Gen3}
  # !BSF HELP:{Auto (Default)(0x0): Maximum possible link speed, Gen1(0x1): Limit Link to Gen1 Speed, Gen2(0x2): Limit Link to Gen2 Speed, Gen3(0x3):Limit Link to Gen3 Speed}
  gKabylakeFspPkgTokenSpaceGuid.Peg2MaxLinkSpeed            | 0x22C | 0x01 | 0x00

  # !BSF NAME:{PEG 0 Max Link Width} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:x1, 2:x2, 3:x4, 4:x8}
  # !BSF HELP:{Auto (Default)(0x0): Maximum possible link width, (0x1): Limit Link to x1, (0x2): Limit Link to x2, (0x3):Limit Link to x4, (0x4): Limit Link to x8}
  gKabylakeFspPkgTokenSpaceGuid.Peg0MaxLinkWidth            | 0x22D | 0x01 | 0x00

  # !BSF NAME:{PEG 1 Max Link Width} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:x1, 2:x2, 3:x4}
  # !BSF HELP:{Auto (Default)(0x0): Maximum possible link width, (0x1): Limit Link to x1, (0x2): Limit Link to x2, (0x3):Limit Link to x4}
  gKabylakeFspPkgTokenSpaceGuid.Peg1MaxLinkWidth            | 0x22E | 0x01 | 0x00

  # !BSF NAME:{PEG 2 Max Link Width} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:x1, 2:x2}
  # !BSF HELP:{Auto (Default)(0x0): Maximum possible link width, (0x1): Limit Link to x1, (0x2): Limit Link to x2}
  gKabylakeFspPkgTokenSpaceGuid.Peg2MaxLinkWidth            | 0x22F | 0x01 | 0x00

  # !BSF NAME:{Power down unused lanes on PEG 0} TYPE:{Combo}
  # !BSF OPTION:{0:No power saving, 1:Auto}
  # !BSF HELP:{(0x0): Do not power down any lane, (0x1): Bios will power down unused lanes based on the max possible link width}
  gKabylakeFspPkgTokenSpaceGuid.Peg0PowerDownUnusedLanes    | 0x230 | 0x01 | 0x01

  # !BSF NAME:{Power down unused lanes on PEG 1} TYPE:{Combo}
  # !BSF OPTION:{0:No power saving, 1:Auto}
  # !BSF HELP:{(0x0): Do not power down any lane, (0x1): Bios will power down unused lanes based on the max possible link width}
  gKabylakeFspPkgTokenSpaceGuid.Peg1PowerDownUnusedLanes    | 0x231 | 0x01 | 0x01

  # !BSF NAME:{Power down unused lanes on PEG 2} TYPE:{Combo}
  # !BSF OPTION:{0:No power saving, 1:Auto}
  # !BSF HELP:{(0x0): Do not power down any lane, (0x1): Bios will power down unused lanes based on the max possible link width}
  gKabylakeFspPkgTokenSpaceGuid.Peg2PowerDownUnusedLanes    | 0x232 | 0x01 | 0x01

  # !BSF NAME:{PCIe ASPM programming will happen in relation to the Oprom} TYPE:{Combo}
  # !BSF OPTION:{0:Before, 1:After}
  # !BSF HELP:{Select when PCIe ASPM programming will happen in relation to the Oprom. Before(0x0)(Default): Do PCIe ASPM programming before Oprom, After(0x1): Do PCIe ASPM programming after Oprom, requires an SMI handler to save/restore ASPM settings during S3 resume}
  gKabylakeFspPkgTokenSpaceGuid.InitPcieAspmAfterOprom      | 0x233 | 0x01 | 0x0

  # !BSF NAME:{PCIe Disable Spread Spectrum Clocking} TYPE:{Combo}
  # !BSF OPTION:{0:Normal Operation, 1:Disable SSC}
  # !BSF HELP:{PCIe Disable Spread Spectrum Clocking. Normal Operation(0x0)(Default) - SSC enabled, Disable SSC(0X1) - Disable SSC per platform design or for compliance testing}
  gKabylakeFspPkgTokenSpaceGuid.PegDisableSpreadSpectrumClocking  | 0x234 | 0x01 | 0x0

  # !BSF NAME:{DMI Gen3 Root port preset values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming DMI Gen3 preset values per lane. Range: 0-9, 4 is default for each lane}
  gKabylakeFspPkgTokenSpaceGuid.DmiGen3RootPortPreset       | 0x235 | 0x4 | {0x4, 0x4, 0x4, 0x4}

  # !BSF NAME:{DMI Gen3 End port preset values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming DMI Gen3 preset values per lane. Range: 0-9, 7 is default for each lane}
  gKabylakeFspPkgTokenSpaceGuid.DmiGen3EndPointPreset       | 0x239 | 0x4 | {0x7, 0x7, 0x7, 0x7}

  # !BSF NAME:{DMI Gen3 End port Hint values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming DMI Gen3 Hint values per lane. Range: 0-6, 2 is default for each lane}
  gKabylakeFspPkgTokenSpaceGuid.DmiGen3EndPointHint         | 0x23D | 0x4 | {0x2, 0x2, 0x2, 0x2}

  # !BSF NAME:{DMI Gen3 RxCTLEp per-Bundle control} TYPE:{EditNum, HEX, (0x00, 0xFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Range: 0-15, 3 is default for each bundle, must be specified based upon platform design}
  gKabylakeFspPkgTokenSpaceGuid.DmiGen3RxCtlePeaking        | 0x241 | 0x2 | {0x3, 0x3}

  # !BSF NAME:{DeEmphasis control for DMI} TYPE:{Combo}
  # !BSF OPTION:{0: -6dB, 1: -3.5dB}
  # !BSF HELP:{DeEmphasis control for DMI. 0=-6dB, 1(Default)=-3.5 dB}
  gKabylakeFspPkgTokenSpaceGuid.DmiDeEmphasis               | 0x0243 | 0x01 | 0x1

  # !BSF NAME:{PEG Gen3 RxCTLEp per-Bundle control} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Range: 0-15, 12 is default for each bundle, must be specified based upon platform design}
  gKabylakeFspPkgTokenSpaceGuid.PegGen3RxCtlePeaking        | 0x244 | 0x8 | {0xC, 0xC, 0xC, 0xC, 0xC, 0xC, 0xC, 0xC}

  # !BSF NAME:{Memory data pointer for saved preset search results} TYPE:{EditNum, HEX, (0, 0xFFFFFFFF)}
  # !BSF HELP:{The reference code will store the Gen3 Preset Search results in the SaDataHob's PegData structure (SA_PEG_DATA) and platform code can save/restore this data to skip preset search in the following boots. Range: 0-0xFFFFFFFF, default is 0}
  gKabylakeFspPkgTokenSpaceGuid.PegDataPtr                  | 0x024C | 0x04 | 0

  # !BSF NAME:{PEG PERST# GPIO information} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{The reference code will use the information in this structure in order to reset PCIe Gen3 devices during equalization, if necessary}
  gKabylakeFspPkgTokenSpaceGuid.PegGpioData                 | 0x250 | 0x10 | {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}

  # !BSF NAME:{PCIe Hot Plug Enable/Disable per port} TYPE:{EditNum, HEX, (0x00, 0xFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{0(Default): Disable, 1: Enable}
  gKabylakeFspPkgTokenSpaceGuid.PegRootPortHPE              | 0x261 | 0x3 | {0x0, 0x0, 0x0}

  # !BSF NAME:{Temporary MMIO address for GTTMMADR} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{The reference code will use the information in this structure in order to reset PCIe Gen3 devices during equalization, if necessary}
  gKabylakeFspPkgTokenSpaceGuid.GttMmAdr                    | 0x264 | 0x4 | 0xDF000000

  # !BSF NAME:{Selection of iGFX GTT Memory size} TYPE:{Combo}
  # !BSF OPTION:{1:2MB, 2:4MB, 3:8MB}
  # !BSF HELP:{1=2MB, 2=4MB, 3=8MB, Default is 3}
  gKabylakeFspPkgTokenSpaceGuid.GttSize                     | 0x0268 | 0x02 | 0x3

  # !BSF NAME:{Selection of the primary display device} TYPE:{Combo}
  # !BSF OPTION:{0:iGFX, 1:PEG, 2:PCIe Graphics on PCH, 3:AUTO, 4:Switchable Graphics}
  # !BSF HELP:{0=iGFX, 1=PEG, 2=PCIe Graphics on PCH, 3(Default)=AUTO, 4=Switchable Graphics}
  gKabylakeFspPkgTokenSpaceGuid.PrimaryDisplay              | 0x026A | 0x01 | 0x3

  # !BSF NAME:{Switchable Graphics GPIO information for PEG 0} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Switchable Graphics GPIO information for PEG 0, for Reset, power and wake GPIOs}
  gKabylakeFspPkgTokenSpaceGuid.SaRtd3Pcie0Gpio             | 0x26B | 0x18 | {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}

  # !BSF NAME:{Switchable Graphics GPIO information for PEG 1} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Switchable Graphics GPIO information for PEG 1, for Reset, power and wake GPIOs}
  gKabylakeFspPkgTokenSpaceGuid.SaRtd3Pcie1Gpio             | 0x283 | 0x18 | {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}

  # !BSF NAME:{Switchable Graphics GPIO information for PEG 2} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Switchable Graphics GPIO information for PEG 2, for Reset, power and wake GPIOs}
  gKabylakeFspPkgTokenSpaceGuid.SaRtd3Pcie2Gpio             | 0x29B | 0x18 | {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}

  # !BSF NAME:{PEG root port Device number for Switchable Graphics dGPU} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Device number to indicate which PEG root port has dGPU}
  gKabylakeFspPkgTokenSpaceGuid.RootPortDev                 | 0x2B3 | 0x1 | 0x0

  # !BSF NAME:{PEG root port Function number for Switchable Graphics dGPU} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Function number to indicate which PEG root port has dGPU}
  gKabylakeFspPkgTokenSpaceGuid.RootPortFun                 | 0x2B4 | 0x1 | 0x0

  # !BSF NAME:{Enable/Disable MRC TXT dependency} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When enabled MRC execution will wait for TXT initialization to be done first. Disabled(0x0)(Default): MRC will not wait for TXT initialization, Enabled(0x1): MRC will wait for TXT initialization}
  gKabylakeFspPkgTokenSpaceGuid.TxtImplemented              | 0x2B5 | 0x01 | 0x0

  # !BSF NAME:{Enable/Disable SA OcSupport} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Enable SA OcSupport, Disable(Default): Disable SA OcSupport}
  gKabylakeFspPkgTokenSpaceGuid.SaOcSupport                 | 0x02B6 | 0x01 | 0x0

  # !BSF NAME:{GT slice Voltage Mode} TYPE:{Combo}
  # !BSF OPTION:{0: Adaptive, 1: Override}
  # !BSF HELP:{0(Default): Adaptive, 1: Override}
  gKabylakeFspPkgTokenSpaceGuid.GtsVoltageMode              | 0x02B7 | 0x01 | 0x0

  # !BSF NAME:{GT unslice Voltage Mode} TYPE:{Combo}
  # !BSF OPTION:{0: Adaptive, 1: Override}
  # !BSF HELP:{0(Default): Adaptive, 1: Override}
  gKabylakeFspPkgTokenSpaceGuid.GtusVoltageMode             | 0x02B8 | 0x01 | 0x0

  # !BSF NAME:{Maximum GTs turbo ratio override} TYPE:{EditNum, HEX, (0, 60)}
  # !BSF HELP:{0(Default)=Minimal/Auto, 60=Maximum}
  gKabylakeFspPkgTokenSpaceGuid.GtsMaxOcRatio               | 0x02B9 | 0x1 | 0

  # !BSF NAME:{The voltage offset applied to GT slice} TYPE:{EditNum, HEX, (0, 1000)}
  # !BSF HELP:{0(Default)=Minimal, 1000=Maximum}
  gKabylakeFspPkgTokenSpaceGuid.GtsVoltageOffset            | 0x02BA | 0x2 | 0

  # !BSF NAME:{The GT slice voltage override which is applied to the entire range of GT frequencies} TYPE:{EditNum, HEX, (0, 2000)}
  # !BSF HELP:{0(Default)=Minimal, 2000=Maximum}
  gKabylakeFspPkgTokenSpaceGuid.GtsVoltageOverride          | 0x02BC | 0x2 | 0

  # !BSF NAME:{adaptive voltage applied during turbo frequencies} TYPE:{EditNum, HEX, (0, 2000)}
  # !BSF HELP:{0(Default)=Minimal, 2000=Maximum}
  gKabylakeFspPkgTokenSpaceGuid.GtsExtraTurboVoltage        | 0x02BE | 0x2 | 0

  # !BSF NAME:{voltage offset applied to GT unslice} TYPE:{EditNum, HEX, (0, 1000)}
  # !BSF HELP:{0(Default)=Minimal, 2000=Maximum}
  gKabylakeFspPkgTokenSpaceGuid.GtusVoltageOffset           | 0x02C0 | 0x2 | 0

  # !BSF NAME:{GT unslice voltage override which is applied to the entire range of GT frequencies} TYPE:{EditNum, HEX, (0, 2000)}
  # !BSF HELP:{0(Default)=Minimal, 2000=Maximum}
  gKabylakeFspPkgTokenSpaceGuid.GtusVoltageOverride         | 0x02C2 | 0x2 | 0

  # !BSF NAME:{adaptive voltage applied during turbo frequencies} TYPE:{EditNum, HEX, (0, 2000)}
  # !BSF HELP:{0(Default)=Minimal, 2000=Maximum}
  gKabylakeFspPkgTokenSpaceGuid.GtusExtraTurboVoltage       | 0x02C4 | 0x2 | 0

  # !BSF NAME:{voltage offset applied to the SA} TYPE:{EditNum, HEX, (0, 1000)}
  # !BSF HELP:{0(Default)=Minimal, 1000=Maximum}
  gKabylakeFspPkgTokenSpaceGuid.SaVoltageOffset             | 0x02C6 | 0x2 | 0

  # !BSF NAME:{EDRAM ratio override} TYPE:{EditNum, HEX, (0, 30)}
  # !BSF HELP:{EdramRatio is deprecated on Kabylake}
  gKabylakeFspPkgTokenSpaceGuid.EdramRatio                  | 0x02C8 | 0x1 | 0

  # !BSF NAME:{Maximum GTus turbo ratio override} TYPE:{EditNum, HEX, (0, 60)}
  # !BSF HELP:{0(Default)=Minimal, 60=Maximum}
  gKabylakeFspPkgTokenSpaceGuid.GtusMaxOcRatio              | 0x02C9 | 0x1 | 0
  #
  # SA Pre-Mem Production Block End
  #

  #
  # CPU Pre-Mem Production Block Start
  #
  # !BSF NAME:{BIST on Reset} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable BIST on Reset; <b>0: Disable</b>; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.BistOnReset                 | 0x02CA | 0x01 | 0x00

  # !BSF NAME:{Skip Stop PBET Timer Enable/Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Skip Stop PBET Timer; <b>0: Disable</b>; 1: Enable}
  gKabylakeFspPkgTokenSpaceGuid.SkipStopPbet                | 0x02CB| 0x01 | 0x00

  # !BSF NAME:{C6DRAM power gating feature} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This feature is not supported. BIOS is required to disable. <b>0: Disable</b>}
  gKabylakeFspPkgTokenSpaceGuid.EnableC6Dram                | 0x02CC | 0x01 | 0x00

  # !BSF NAME:{Over clocking support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Over clocking support; <b>0: Disable</b>; 1: Enable}
  gKabylakeFspPkgTokenSpaceGuid.OcSupport                   | 0x02CD | 0x01 | 0x00

  # !BSF NAME:{Over clocking Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Over clocking Lock Enable/Disable; 0: Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.OcLock                      | 0x02CE | 0x01 | 0x01

  # !BSF NAME:{Maximum Core Turbo Ratio Override}
  # !BSF TYPE:{EditNum, DEC, (0, 255)}
  # !BSF HELP:{Maximum core turbo ratio override allows to increase CPU core frequency beyond the fused max turbo ratio limit. <b>0: Hardware defaults.</b> Range: 0-255}
  gKabylakeFspPkgTokenSpaceGuid.CoreMaxOcRatio              | 0x02CF | 0x01 | 0x00

  # !BSF NAME:{Core voltage mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Core voltage mode; <b>0: Adaptive</b>; 1: Override.}
  gKabylakeFspPkgTokenSpaceGuid.CoreVoltageMode             | 0x02D0 | 0x01 | 0x00

  # !BSF NAME:{Minimum clr turbo ratio override}
  # !BSF TYPE:{EditNum, DEC, (0, 255)}
  # !BSF HELP:{Minimum clr turbo ratio override. <b>0: Hardware defaults.</b> Range: 0-255}
  gKabylakeFspPkgTokenSpaceGuid.RingMinOcRatio              | 0x02D1 | 0x01 | 0x00

  # !BSF NAME:{Maximum clr turbo ratio override}
  # !BSF TYPE:{EditNum, DEC, (0, 255)}
  # !BSF HELP:{Maximum clr turbo ratio override allows to increase CPU clr frequency beyond the fused max turbo ratio limit. <b>0: Hardware defaults.</b>  Range: 0-255}
  gKabylakeFspPkgTokenSpaceGuid.RingMaxOcRatio              | 0x02D2 | 0x01 | 0x00

  # !BSF NAME:{Hyper Threading Enable/Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Hyper Threading; 0: Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.HyperThreading              | 0x02D3 | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable CPU Ratio Override} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable CPU Ratio Override; <b>0: Disable</b>; 1: Enable. @note If disabled, BIOS will use the default max non-turbo ratio, and will not use any flex ratio setting.}
  gKabylakeFspPkgTokenSpaceGuid.CpuRatioOverride            | 0x02D4 | 0x01 | 0x00

  # !BSF NAME:{CPU ratio value}
  # !BSF TYPE:{EditNum, DEC, (0, 63)}
  # !BSF HELP:{CPU ratio value. Valid Range 0 to 63}
  gKabylakeFspPkgTokenSpaceGuid.CpuRatio                    | 0x02D5 | 0x01 | 0x1C

  # !BSF NAME:{Boot frequency}
  # !BSF TYPE:{Combo}
  # !BSF OPTION:{0:0, 1:1, 2:2}
  # !BSF HELP:{Sets the boot frequency starting from reset vector.- 0: Maximum battery performance.- <b>1: Maximum non-turbo performance</b>.- 2: Turbo performance. @note If Turbo is selected BIOS will start in max non-turbo mode and switch to Turbo mode.}
  gKabylakeFspPkgTokenSpaceGuid.BootFrequency               | 0x02D6 | 0x01 | 0x01

  # !BSF NAME:{Number of active cores}
  # !BSF TYPE:{Combo} OPTION:{0:All, 1:1, 2:2, 3:3}
  # !BSF HELP:{Number of active cores(Depends on Number of cores). <b>0: All</b>;<b>1: 1 </b>;<b>2: 2 </b>;<b>3: 3 </b>}
  gKabylakeFspPkgTokenSpaceGuid.ActiveCoreCount             | 0x02D7 | 0x01 | 0x00

  # !BSF NAME:{Processor Early Power On Configuration FCLK setting}
  # !BSF TYPE:{Combo} OPTION:{0:800 MHz, 1: 1 GHz, 2: 400 MHz, 3: Reserved }
  # !BSF HELP:{ <b>0: 800 MHz (ULT/ULX)</b>. <b>1: 1 GHz (DT/Halo)</b>. Not supported on ULT/ULX.- 2: 400 MHz. - 3: Reserved}
  gKabylakeFspPkgTokenSpaceGuid.FClkFrequency               | 0x02D8 | 0x01 | 0x00

  # !BSF NAME:{Power JTAG in C10 and deeper power states} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Power JTAG in C10 and deeper power states; <b>0: Disable</b>; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.JtagC10PowerGateDisable     | 0x02D9 | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable VMX} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable VMX; 0: Disable; <b>1: Enable</b>.}
  gKabylakeFspPkgTokenSpaceGuid.VmxEnable                   | 0x02DA | 0x01 | 0x01

  # !BSF NAME:{AVX2 Ratio Offset} TYPE:{EditNum, HEX, (0, 31)}
  # !BSF HELP:{0(Default)= No Offset. Range 0 - 31. Specifies number of bins to decrease AVX ratio vs. Core Ratio. Uses Mailbox MSR 0x150, cmd 0x1B.}
  gKabylakeFspPkgTokenSpaceGuid.Avx2RatioOffset             | 0x02DB | 0x1 | 0

  # !BSF NAME:{core voltage override}
  # !BSF TYPE:{EditNum, DEC, (0, 2000)}
  # !BSF HELP:{The core voltage override which is applied to the entire range of cpu core frequencies. Valid Range 0 to 2000}
  gKabylakeFspPkgTokenSpaceGuid.CoreVoltageOverride         | 0x02DC | 0x02 | 0x00

  # !BSF NAME:{Core Turbo voltage Adaptive}
  # !BSF TYPE:{EditNum, DEC, (0, 2000)}
  # !BSF HELP:{Extra Turbo voltage applied to the cpu core when the cpu is operating in turbo mode. Valid Range 0 to 2000}
  gKabylakeFspPkgTokenSpaceGuid.CoreVoltageAdaptive         | 0x02DE | 0x02 | 0x00

  # !BSF NAME:{Core Turbo voltage Offset}
  # !BSF TYPE:{EditNum, DEC, (0, 1000)}
  # !BSF HELP:{The voltage offset applied to the core while operating in turbo mode.Valid Range 0 to 1000}
  gKabylakeFspPkgTokenSpaceGuid.CoreVoltageOffset           | 0x02E0 | 0x02 | 0x00

  # !BSF NAME:{Core PLL voltage offset}
  # !BSF TYPE:{EditNum, DEC, (0, 63)}
  # !BSF HELP:{Core PLL voltage offset. <b>0: No offset</b>. Range 0-63}
  gKabylakeFspPkgTokenSpaceGuid.CorePllVoltageOffset        | 0x02E2 | 0x01 | 0x00

  # !BSF NAME:{Ring Downbin} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Ring Downbin enable/disable. When enabled, CPU will ensure the ring ratio is always lower than the core ratio. 0: Disable; <b>1: Enable.</b>}
  gKabylakeFspPkgTokenSpaceGuid.RingDownBin                 | 0x02E3 | 0x01 | 0x01

  # !BSF NAME:{BCLK Adaptive Voltage Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When enabled, the CPU V/F curves are aware of BCLK frequency when calculated. </b>0: Disable;<b> 1: Enable}
  gKabylakeFspPkgTokenSpaceGuid.BclkAdaptiveVoltage         | 0x02E4 | 0x01 | 0x00

  #
  # CPU Pre-Mem Production Block End
  #

  #
  #  Security Pre-Mem start
  #

  # !BSF NAME:{BiosGuard} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, Enable/Disable BIOS Guard feature, 1: enable}
  gSkylakeFspPkgTokenSpaceGuid.BiosGuard                    | 0x02E5 | 0x01 | 0x00

  # !BSF NAME:{EnableSgx} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, Enable/Disable SGX feature, 1: enable}
  gSkylakeFspPkgTokenSpaceGuid.EnableSgx                    | 0x02E6 | 0x01 | 0x00

  # !BSF NAME:{Txt} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, Enable/Disable Txt feature, 1: enable}
  gSkylakeFspPkgTokenSpaceGuid.Txt                          | 0x02E7 | 0x01 | 0x00

  # !BSF NAME:{PrmrrSize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of PrmrrSize , 1: enable}
  # TODO: change the value according to EnableSgx token
  gSkylakeFspPkgTokenSpaceGuid.PrmrrSize                    | 0x02E8 | 0x04 | 0x00000000

  # !BSF NAME:{SinitMemorySize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of SinitMemorySize , 1: enable}
  # TODO: Check if default 0 is ok
  gSkylakeFspPkgTokenSpaceGuid.SinitMemorySize              | 0x02EC | 0x04 | 0x00000000

  # !BSF NAME:{TxtDprMemoryBase}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TxtDprMemoryBase , 1: enable}
  # TODO: Check if default 0 is ok
  gSkylakeFspPkgTokenSpaceGuid.TxtDprMemoryBase             | 0x02F0 | 0x08 | 0x0000000000000000

  # !BSF NAME:{TxtDprMemorySize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TxtDprMemorySize , 1: enable}
  # TODO: Check if default 0 is ok
  gSkylakeFspPkgTokenSpaceGuid.TxtDprMemorySize             | 0x2F8 | 0x04 | 0x00000000

  # !BSF NAME:{TxtHeapMemorySize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TxtHeapMemorySize , 1: enable}
  # TODO: Check if default 0 is ok
  gSkylakeFspPkgTokenSpaceGuid.TxtHeapMemorySize            | 0x02FC | 0x04 | 0x00000000

  # !BSF NAME:{FlashWearOutProtection} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, Enable/Disable FlashWearOutProtection feature, 1: enable}
  gSkylakeFspPkgTokenSpaceGuid.FlashWearOutProtection       | 0x0300 | 0x01 | 0x00

  # !BSF NAME:{Thermal Velocity Boost Ratio clipping} TYPE:{Combo}
  # !BSF OPTION:{0: Disabled, 1: Enabled}
  # !BSF HELP:{0(Default): Disabled, 1: Enabled. This service controls Core frequency reduction caused by high package temperatures for processors that implement the Intel Thermal Velocity Boost (TVB) feature}
  gKabylakeFspPkgTokenSpaceGuid.TvbRatioClipping            | 0x0301 | 0x01 | 0x0

  # !BSF NAME:{Thermal Velocity Boost voltage optimization} TYPE:{Combo}
  # !BSF OPTION:{0: Disabled, 1: Enabled}
  # !BSF HELP:{0: Disabled, 1: Enabled(Default). This service controls thermal based voltage optimizations for processors that implement the Intel Thermal Velocity Boost (TVB) feature.}
  gKabylakeFspPkgTokenSpaceGuid.TvbVoltageOptimization      | 0x0302 | 0x01 | 0x1
  
  # !BSF NAME:{ReservedSecurityPreMem} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for Security Pre-Mem}
  gKabylakeFspPkgTokenSpaceGuid.ReservedSecurityPreMem      | 0x0303 | 0x07 | {0x00}

  #
  #  Security Pre-Mem End
  #

  #
  #  PCH Pre-Mem start
  #

  # !BSF NAME:{PCH HPET Enabled} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PCH HPET.}
  gKabylakeFspPkgTokenSpaceGuid.PchHpetEnable               | 0x030A | 0x01 | 0x01

  # !BSF NAME:{PCH HPET BDF valid} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Whether the BDF value is valid. 0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchHpetBdfValid             | 0x030B | 0x01 | 0x00

  # !BSF NAME:{The HPET Base Address} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{The HPET base address. Default is 0xFED00000.}
  gKabylakeFspPkgTokenSpaceGuid.PchHpetBase                 | 0x030C | 0x04 | 0xFED00000

  # !BSF NAME:{PCH HPET Bus Number}  TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Bus Number HPETn used as Requestor / Completer ID. Default is 0xF0.}
  gKabylakeFspPkgTokenSpaceGuid.PchHpetBusNumber            | 0x0310 | 0x01 | 0xF0

  # !BSF NAME:{PCH HPET Device Number}  TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Device Number HPETn used as Requestor / Completer ID. Default is 0x1F.}
  gKabylakeFspPkgTokenSpaceGuid.PchHpetDeviceNumber         | 0x0311 | 0x01 | 0x1F

  # !BSF NAME:{PCH HPET Function Number}  TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Function Number HPETn used as Requestor / Completer ID. Default is 0x00.}
  gKabylakeFspPkgTokenSpaceGuid.PchHpetFunctionNumber       | 0x0312 | 0x01 | 0x00

  # !BSF NAME:{Enable PCH HSIO PCIE Rx Set Ctle} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable PCH PCIe Gen 3 Set CTLE Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioRxSetCtleEnable          | 0x0313 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Rx Set Ctle Value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 3 Set CTLE Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioRxSetCtle                | 0x032B | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enble PCH HSIO PCIE TX Gen 1 Downscale Amplitude Adjustment value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioTxGen1DownscaleAmpEnable | 0x0343 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Gen 2 TX Output Downscale Amplitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 2 TX Output Downscale Amplitude Adjustment value.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioTxGen1DownscaleAmp       | 0x035B | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO PCIE TX Gen 2 Downscale Amplitude Adjustment value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioTxGen2DownscaleAmpEnable | 0x0373 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Gen 2 TX Output Downscale Amplitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 2 TX Output Downscale Amplitude Adjustment value.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioTxGen2DownscaleAmp       | 0x038B | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO PCIE TX Gen 3 Downscale Amplitude Adjustment value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioTxGen3DownscaleAmpEnable | 0x03A3 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Gen 3 TX Output Downscale Amplitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 3 TX Output Downscale Amplitude Adjustment value.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioTxGen3DownscaleAmp       | 0x03BB | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO PCIE Gen 1 TX Output De-Emphasis Adjustment Setting value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioTxGen1DeEmphEnable       | 0x03D3 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Gen 1 TX Output De-Emphasis Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 1 TX Output De-Emphasis Adjustment Setting.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioTxGen1DeEmph             | 0x03EB | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO PCIE Gen 2 TX Output -3.5dB De-Emphasis Adjustment Setting value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioTxGen2DeEmph3p5Enable    | 0x0403 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Gen 2 TX Output -3.5dB De-Emphasis Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 2 TX Output -3.5dB De-Emphasis Adjustment Setting.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioTxGen2DeEmph3p5          | 0x041B | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO PCIE Gen 2 TX Output -6.0dB De-Emphasis Adjustment Setting value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioTxGen2DeEmph6p0Enable    | 0x0433 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Gen 2 TX Output -6.0dB De-Emphasis Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 2 TX Output -6.0dB De-Emphasis Adjustment Setting.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieHsioTxGen2DeEmph6p0          | 0x044B | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA Receiver Equalization Boost Magnitude Adjustment Value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioRxGen1EqBoostMagEnable   | 0x0463 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 1.5 Gb/s Receiver Equalization Boost Magnitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 1.5 Gb/s Receiver Equalization Boost Magnitude Adjustment value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioRxGen1EqBoostMag         | 0x046B | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA Receiver Equalization Boost Magnitude Adjustment Value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioRxGen2EqBoostMagEnable   | 0x0473 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 3.0 Gb/s Receiver Equalization Boost Magnitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 3.0 Gb/s Receiver Equalization Boost Magnitude Adjustment value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioRxGen2EqBoostMag         | 0x047B | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA Receiver Equalization Boost Magnitude Adjustment Value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioRxGen3EqBoostMagEnable   | 0x0483 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 6.0 Gb/s Receiver Equalization Boost Magnitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 6.0 Gb/s Receiver Equalization Boost Magnitude Adjustment value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioRxGen3EqBoostMag         | 0x048B | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA 1.5 Gb/s TX Output Downscale Amplitude Adjustment value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioTxGen1DownscaleAmpEnable | 0x0493 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 1.5 Gb/s TX Output Downscale Amplitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 1.5 Gb/s TX Output Downscale Amplitude Adjustment value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioTxGen1DownscaleAmp       | 0x049B | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA 3.0 Gb/s TX Output Downscale Amplitude Adjustment value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioTxGen2DownscaleAmpEnable | 0x04A3 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 3.0 Gb/s TX Output Downscale Amplitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 3.0 Gb/s TX Output Downscale Amplitude Adjustment value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioTxGen2DownscaleAmp       | 0x04AB | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA 6.0 Gb/s TX Output Downscale Amplitude Adjustment value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioTxGen3DownscaleAmpEnable | 0x04B3 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 6.0 Gb/s TX Output Downscale Amplitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 6.0 Gb/s TX Output Downscale Amplitude Adjustment value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioTxGen3DownscaleAmp       | 0x04BB | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA 1.5 Gb/s TX Output De-Emphasis Adjustment Setting value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioTxGen1DeEmphEnable       | 0x04C3 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 1.5 Gb/s TX Output De-Emphasis Adjustment Setting} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 1.5 Gb/s TX Output De-Emphasis Adjustment Setting.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioTxGen1DeEmph             | 0x04CB | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA 3.0 Gb/s TX Output De-Emphasis Adjustment Setting value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioTxGen2DeEmphEnable       | 0x04D3 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 3.0 Gb/s TX Output De-Emphasis Adjustment Setting} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 3.0 Gb/s TX Output De-Emphasis Adjustment Setting.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioTxGen2DeEmph             | 0x04DB | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA 6.0 Gb/s TX Output De-Emphasis Adjustment Setting value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioTxGen3DeEmphEnable       | 0x04E3 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 6.0 Gb/s TX Output De-Emphasis Adjustment Setting} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 6.0 Gb/s TX Output De-Emphasis Adjustment Setting.}
  gKabylakeFspPkgTokenSpaceGuid.PchSataHsioTxGen3DeEmph             | 0x04EB | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH LPC Enhance the port 8xh decoding} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Original LPC only decodes one byte of port 80h.}
  gKabylakeFspPkgTokenSpaceGuid.PchLpcEnhancePort8xhDecoding        | 0x04F3 | 0x01 | 0x01

  # !BSF NAME:{PCH Acpi Base} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Power management I/O base address. Default is 0x1800.}
  gKabylakeFspPkgTokenSpaceGuid.PchAcpiBase                 | 0x04F4 | 0x02 | 0x1800

  # !BSF NAME:{PCH Port80 Route} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Control where the Port 80h cycles are sent, 0: LPC; 1: PCI.}
  gKabylakeFspPkgTokenSpaceGuid.PchPort80Route              | 0x04F6 | 0x01 | 0x00

  # !BSF NAME:{Enable SMBus ARP support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable SMBus ARP support.}
  gKabylakeFspPkgTokenSpaceGuid.SmbusArpEnable              | 0x04F7 | 0x01 | 0x00

  # !BSF NAME:{SMBUS Base Address} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{SMBUS Base Address (IO space).}
  gKabylakeFspPkgTokenSpaceGuid.PchSmbusIoBase              | 0x04F8 | 0x02 | 0xEFA0

  # !BSF NAME:{Number of RsvdSmbusAddressTable.} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{The number of elements in the RsvdSmbusAddressTable.}
  gKabylakeFspPkgTokenSpaceGuid.PchNumRsvdSmbusAddresses    | 0x04FA | 0x01 | 0x00

  ## only need 4 bytes to use point for this policy
  # !BSF NAME:{Point of RsvdSmbusAddressTable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Array of addresses reserved for non-ARP-capable SMBus devices.}
  gKabylakeFspPkgTokenSpaceGuid.RsvdSmbusAddressTablePtr    | 0x04FC | 0x04 | 0x00000000

  # !BSF NAME:{Trace Hub Memory Region 0} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Trace Hub Memory Region 0.}
  gKabylakeFspPkgTokenSpaceGuid.TraceHubMemReg0Size         | 0x0500 | 0x04 | 0x00000000

  # !BSF NAME:{Trace Hub Memory Region 1} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Trace Hub Memory Region 1.}
  gKabylakeFspPkgTokenSpaceGuid.TraceHubMemReg1Size         | 0x0504 | 0x04 | 0x00000000

  # !BSF NAME:{Enable PCIE RP Mask} TYPE:{EditNum, HEX, (0x00,0x00FFFFFF)}
  # !BSF HELP:{Enable/disable PCIE Root Ports. 0: disable, 1: enable. One bit for each port, bit0 for port1, bit1 for port2, and so on.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpEnableMask            | 0x0508 | 0x04 | 0x00FFFFFF

  # !BSF PAGE:{SPT}
  # !BSF NAME:{Debug Interfaces} TYPE:{EditNum, HEX, (0x00,0x3F)}
  # !BSF HELP:{Debug Interfaces. BIT0-RAM, BIT1-UART, BIT3-USB3, BIT4-Serial IO, BIT5-TraceHub, BIT2 - Not used.}
  gSiPkgTokenSpaceGuid.PcdDebugInterfaceFlags               | 0x050C | 0x01 | 0x12

  # !BSF NAME:{SerialIo Uart Number Selection} TYPE:{Combo}
  # !BSF OPTION:{0:SerialIoUart0, 1:SerialIoUart1, 2:SerialIoUart2}
  # !BSF HELP:{Select SerialIo Uart Controller for debug.}
  gSiPkgTokenSpaceGuid.PcdSerialIoUartNumber                | 0x050D | 0x01 | 0x02

  #
  #  PCH Pre-Mem End
  #

  # !BSF NAME:{ISA Serial Base selection} TYPE:{Combo}
  # !BSF OPTION:{0:0x3F8, 1:0x2F8}
  # !BSF HELP:{Select ISA Serial Base address. Default is 0x3F8.}
  gSiPkgTokenSpaceGuid.PcdIsaSerialUartBase                 | 0x050E | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Pcie Pll Ssc} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Specifies the Pcie Pll Spread Spectrum Percentage. The default is 0xFF: AUTO - No BIOS override.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmPciePllSsc             | 0x050F | 0x01 | 0xFF

  # !BSF NAME:{Enable or Disable Peci C10 Reset command} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Peci C10 Reset command; 0: Disable; <b>1: Enable.</b>}
  gKabylakeFspPkgTokenSpaceGuid.PeciC10Reset                | 0x0510 | 0x01 | 0x1

  # !BSF NAME:{Enable or Disable Peci Sx Reset command} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Peci Sx Reset command; <b>0: Disable;</b> 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PeciSxReset                 | 0x0511 | 0x01 | 0x00

  # !BSF NAME:{PcdSerialDebugBaudRate} TYPE:{Combo}
  # !BSF OPTION:{3:9600, 4:19200, 6:56700, 7:115200}
  # !BSF HELP:{Baud Rate for Serial Debug Messages. 3:9600, 4:19200, 6:56700, 7:115200.}
  gKabylakeFspPkgTokenSpaceGuid.PcdSerialDebugBaudRate      | 0x512  | 0x01 | 0x07

  # !BSF NAME:{PcdSerialDebugLevel} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Error Only, 2:Error and Warnings, 3:Load Error Warnings and Info, 4:Load Error Warnings and Info, 5:Load Error Warnings Info and Verbose}
  # !BSF HELP:{Serial Debug Message Level. 0:Disable, 1:Error Only, 2:Error & Warnings, 3:Load, Error, Warnings & Info, 4:Load, Error, Warnings, Info & Event, 5:Load, Error, Warnings, Info & Verbose}
  gKabylakeFspPkgTokenSpaceGuid.PcdSerialDebugLevel         | 0x513  | 0x01 | 0x03

  # !BSF NAME:{Enable or Disable EV Loader} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable EV Loader; <b>0: Disable;</b> 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.EvLoader                    | 0x0514 | 0x01 | 0x00

  # !BSF NAME:{GT PLL voltage offset}
  # !BSF OPTION:{0x0:0xFF}
  # !BSF HELP:{Core PLL voltage offset. <b>0: No offset</b>. Range 0-63}
  gKabylakeFspPkgTokenSpaceGuid.GtPllVoltageOffset          | 0x0515 | 0x01 | 0x00

  # !BSF NAME:{Ring PLL voltage offset}
  # !BSF OPTION:{0x0:0xFF}
  # !BSF HELP:{Core PLL voltage offset. <b>0: No offset</b>. Range 0-63}
  gKabylakeFspPkgTokenSpaceGuid.RingPllVoltageOffset        | 0x0516 | 0x01 | 0x00

  # !BSF NAME:{System Agent PLL voltage offset}
  # !BSF OPTION:{0x0:0xFF}
  # !BSF HELP:{Core PLL voltage offset. <b>0: No offset</b>. Range 0-63}
  gKabylakeFspPkgTokenSpaceGuid.SaPllVoltageOffset          | 0x0517 | 0x01 | 0x00

  # !BSF NAME:{Memory Controller PLL voltage offset}
  # !BSF OPTION:{0x0:0xFF}
  # !BSF HELP:{Core PLL voltage offset. <b>0: No offset</b>. Range 0-63}
  gKabylakeFspPkgTokenSpaceGuid.McPllVoltageOffset          | 0x0518 | 0x01 | 0x00

  # !BSF NAME:{Realtime Memory Timing} TYPE:{Combo}
  # !BSF OPTION:{0: Disabled, 1: Enabled}
  # !BSF HELP:{0(Default): Disabled, 1: Enabled. When enabled, it will allow the system to perform realtime memory timing changes after MRC_DONE.}
  gKabylakeFspPkgTokenSpaceGuid.RealtimeMemoryTiming        | 0x0519 | 0x01 | 0x00

  # !BSF NAME:{AVX3 Ratio Offset} TYPE:{EditNum, HEX, (0, 31)}
  # !BSF HELP:{0(Default)= No Offset. Range 0 - 31. Specifies number of bins to decrease AVX ratio vs. Core Ratio. Uses Mailbox MSR 0x150, cmd 0x1B.}
  gKabylakeFspPkgTokenSpaceGuid.Avx3RatioOffset             | 0x051A | 0x01 | 0x00

  # !BSF NAME:{Ask MRC to clear memory content} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Ask MRC to clear memory content <b>0: Do not Clear Memory;</b> 1: Clear Memory.}
  gKabylakeFspPkgTokenSpaceGuid.CleanMemory                 | 0x051B | 0x01 | 0x00

  # !BSF NAME:{TjMax Offset}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x3F)}
  # !BSF HELP:{TjMax offset. Specified value here is clipped by pCode (125 - TjMax Offset) to support TjMax in the range of 62 to 115 deg Celsius. Valid Range 0 - 63}
  gKabylakeFspPkgTokenSpaceGuid.TjMaxOffset                 | 0x051C | 0x01 | 0x00
  
  # !HDR EMBED:{FSP_M_CONFIG:FspmConfig:END}
  gKabylakeFspPkgTokenSpaceGuid.ReservedFspmUpd             | 0x051D | 0x03 | {0x00}

  # !HDR COMMENT:{FSP_M_TEST_CONFIG:Fsp M Test Configuration}
  # !HDR EMBED:{FSP_M_TEST_CONFIG:FspmTestConfig:START}
  # Signature: {TEST}
  gKabylakeFspPkgTokenSpaceGuid.Signature                   | 0x0520 | 0x04 | 0x54534554

  #
  # SA Pre-Mem Test Block Start
  #
  # !BSF NAME:{Skip external display device scanning} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Do not scan for external display device, Disable (Default): Scan external display devices}
  gKabylakeFspPkgTokenSpaceGuid.SkipExtGfxScan              | 0x0524 | 0x01 | 0x0

  # !BSF NAME:{Generate BIOS Data ACPI Table} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Generate BDAT for MRC RMT or SA PCIe data. Disable (Default): Do not generate it}
  gKabylakeFspPkgTokenSpaceGuid.BdatEnable                  | 0x0525 | 0x01 | 0x00

  # !BSF NAME:{Detect External Graphics device for LegacyOpROM} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Detect and report if external graphics device only support LegacyOpROM or not (to support CSM auto-enable). Enable(Default)=1, Disable=0}
  gKabylakeFspPkgTokenSpaceGuid.ScanExtGfxForLegacyOpRom    | 0x0526 | 0x01 | 0x01

  # !BSF NAME:{Lock PCU Thermal Management registers} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Lock PCU Thermal Management registers. Enable(Default)=1, Disable=0}
  gKabylakeFspPkgTokenSpaceGuid.LockPTMregs                 | 0x0527 | 0x01 | 0x01

  # !BSF NAME:{Enable/Disable DmiVc1} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable DmiVc1. Enable = 1, Disable (Default) = 0}
  gKabylakeFspPkgTokenSpaceGuid.DmiVc1                      | 0x0528 | 0x01 | 0x0

  # !BSF NAME:{Enable/Disable DmiVcm} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable DmiVcm. Enable (Default) = 1, Disable = 0}
  gKabylakeFspPkgTokenSpaceGuid.DmiVcm                      | 0x0529 | 0x01 | 0x1

  # !BSF NAME:{DMI Max Link Speed} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:Gen1, 2:Gen2, 3:Gen3}
  # !BSF HELP:{Auto (Default)(0x0): Maximum possible link speed, Gen1(0x1): Limit Link to Gen1 Speed, Gen2(0x2): Limit Link to Gen2 Speed, Gen3(0x3):Limit Link to Gen3 Speed}
  gKabylakeFspPkgTokenSpaceGuid.DmiMaxLinkSpeed             | 0x052A | 0x01 | 0x00

  # !BSF NAME:{DMI Equalization Phase 2} TYPE:{Combo}
  # !BSF OPTION:{0:Disable phase2, 1:Enable phase2, 2:Auto}
  # !BSF HELP:{DMI Equalization Phase 2. (0x0): Disable phase 2, (0x1): Enable phase 2, (0x2)(Default): AUTO - Use the current default method}
  gKabylakeFspPkgTokenSpaceGuid.DmiGen3EqPh2Enable          | 0x052B | 0x01 | 0x02

  # !BSF NAME:{DMI Gen3 Equalization Phase3} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:HwEq, 2:SwEq, 3:StaticEq, 4:BypassPhase3}
  # !BSF HELP:{DMI Gen3 Equalization Phase3. Auto(0x0)(Default): Use the current default method, HwEq(0x1): Use Adaptive Hardware Equalization, SwEq(0x2): Use Adaptive Software Equalization (Implemented in BIOS Reference Code), Static(0x3): Use the Static EQs provided in DmiGen3EndPointPreset array for Phase1 AND Phase3 (Instead of just Phase1), Disabled(0x4): Bypass Equalization Phase 3}
  gKabylakeFspPkgTokenSpaceGuid.DmiGen3EqPh3Method          | 0x052C | 0x01 | 0x0

  # !BSF NAME:{Phase2 EQ enable on the PEG 0:1:0.} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable, 2:Auto}
  # !BSF HELP:{Phase2 EQ enable on the PEG 0:1:0. Disabled(0x0): Disable phase 2, Enabled(0x1): Enable phase 2, Auto(0x2)(Default): Use the current default method}
  gKabylakeFspPkgTokenSpaceGuid.Peg0Gen3EqPh2Enable         | 0x052D | 0x01 | 0x2

  # !BSF NAME:{Phase2 EQ enable on the PEG 0:1:1.} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable, 2:Auto}
  # !BSF HELP:{Phase2 EQ enable on the PEG 0:1:0. Disabled(0x0): Disable phase 2, Enabled(0x1): Enable phase 2, Auto(0x2)(Default): Use the current default method}
  gKabylakeFspPkgTokenSpaceGuid.Peg1Gen3EqPh2Enable         | 0x052E | 0x01 | 0x2

  # !BSF NAME:{Phase2 EQ enable on the PEG 0:1:2.} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable, 2:Auto}
  # !BSF HELP:{Phase2 EQ enable on the PEG 0:1:0. Disabled(0x0): Disable phase 2, Enabled(0x1): Enable phase 2, Auto(0x2)(Default): Use the current default method}
  gKabylakeFspPkgTokenSpaceGuid.Peg2Gen3EqPh2Enable         | 0x052F | 0x01 | 0x2

  # !BSF NAME:{Phase3 EQ method on the PEG 0:1:0.} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:HwEq, 2:SwEq, 3:StaticEq, 4:BypassPhase3}
  # !BSF HELP:{PEG Gen3 Equalization Phase3. Auto(0x0)(Default): Use the current default method, HwEq(0x1): Use Adaptive Hardware Equalization, SwEq(0x2): Use Adaptive Software Equalization (Implemented in BIOS Reference Code), Static(0x3): Use the Static EQs provided in DmiGen3EndPointPreset array for Phase1 AND Phase3 (Instead of just Phase1), Disabled(0x4): Bypass Equalization Phase 3}
  gKabylakeFspPkgTokenSpaceGuid.Peg0Gen3EqPh3Method         | 0x0530 | 0x01 | 0x0

  # !BSF NAME:{Phase3 EQ method on the PEG 0:1:1.} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:HwEq, 2:SwEq, 3:StaticEq, 4:BypassPhase3}
  # !BSF HELP:{PEG Gen3 Equalization Phase3. Auto(0x0)(Default): Use the current default method, HwEq(0x1): Use Adaptive Hardware Equalization, SwEq(0x2): Use Adaptive Software Equalization (Implemented in BIOS Reference Code), Static(0x3): Use the Static EQs provided in DmiGen3EndPointPreset array for Phase1 AND Phase3 (Instead of just Phase1), Disabled(0x4): Bypass Equalization Phase 3}
  gKabylakeFspPkgTokenSpaceGuid.Peg1Gen3EqPh3Method         | 0x0531 | 0x01 | 0x0

  # !BSF NAME:{Phase3 EQ method on the PEG 0:1:2.} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:HwEq, 2:SwEq, 3:StaticEq, 4:BypassPhase3}
  # !BSF HELP:{PEG Gen3 Equalization Phase3. Auto(0x0)(Default): Use the current default method, HwEq(0x1): Use Adaptive Hardware Equalization, SwEq(0x2): Use Adaptive Software Equalization (Implemented in BIOS Reference Code), Static(0x3): Use the Static EQs provided in DmiGen3EndPointPreset array for Phase1 AND Phase3 (Instead of just Phase1), Disabled(0x4): Bypass Equalization Phase 3}
  gKabylakeFspPkgTokenSpaceGuid.Peg2Gen3EqPh3Method         | 0x0532 | 0x01 | 0x0

  # !BSF NAME:{Enable/Disable PEG GEN3 Static EQ Phase1 programming} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Program PEG Gen3 EQ Phase1 Static Presets. Disabled(0x0): Disable EQ Phase1 Static Presets Programming, Enabled(0x1)(Default): Enable  EQ Phase1 Static Presets Programming}
  gKabylakeFspPkgTokenSpaceGuid.PegGen3ProgramStaticEq      | 0x0533 | 0x01 | 0x1

  # !BSF NAME:{PEG Gen3 SwEq Always Attempt} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable}
  # !BSF HELP:{Gen3 Software Equalization will be executed every boot. Disabled(0x0)(Default): Reuse EQ settings saved/restored from NVRAM whenever possible, Enabled(0x1): Re-test and generate new EQ values every boot, not recommended}
  gKabylakeFspPkgTokenSpaceGuid.Gen3SwEqAlwaysAttempt       | 0x0534 | 0x01 | 0x0

  # !BSF NAME:{Select number of TxEq presets to test in the PCIe/DMI SwEq} TYPE:{Combo}
  # !BSF OPTION:{0:P7 P3 P5, 1:P0 to P9, 2:Auto}
  # !BSF HELP:{Select number of TxEq presets to test in the PCIe/DMI SwEq. P7,P3,P5(0x0): Test Presets 7, 3, and 5, P0-P9(0x1): Test Presets 0-9, Auto(0x2)(Default): Use the current default method (Default)Auto will test Presets 7, 3, and 5.  It is possible for this default to change over time;using Auto will ensure Reference Code always uses the latest default settings}
  gKabylakeFspPkgTokenSpaceGuid.Gen3SwEqNumberOfPresets     | 0x0535 | 0x01 | 0x2

  # !BSF NAME:{Enable use of the Voltage Offset and Centering Test in the PCIe SwEq} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable, 2:Auto}
  # !BSF HELP:{Enable use of the Voltage Offset and Centering Test in the PCIe Software Equalization Algorithm. Disabled(0x0): Disable VOC Test, Enabled(0x1): Enable VOC Test, Auto(0x2)(Default): Use the current default}
  gKabylakeFspPkgTokenSpaceGuid.Gen3SwEqEnableVocTest       | 0x0536 | 0x01 | 0x2

  # !BSF NAME:{PPCIe Rx Compliance Testing Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disabled(0x0)(Default): Normal Operation - Disable PCIe Rx Compliance testing, Enabled(0x1): PCIe Rx Compliance Test Mode - PEG controller is in Rx Compliance Testing Mode; it should only be set when doing PCIe compliance testing}
  gKabylakeFspPkgTokenSpaceGuid.PegRxCemTestingMode         | 0x0537 | 0x01 | 0x0

  # !BSF NAME:{PCIe Rx Compliance Loopback Lane  When PegRxCemTestingMode is Enabled} TYPE:{EditNum, HEX, (0, 0xF)}
  # !BSF HELP:{the specificied Lane (0 - 15) will be  used for RxCEMLoopback.  Default is Lane 0}
  gKabylakeFspPkgTokenSpaceGuid.PegRxCemLoopbackLane        | 0x0538 | 0x01 | 0

  # !BSF NAME:{Generate PCIe BDAT Margin Table} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set this policy to enable the generation and addition of PCIe margin data to the BDAT table. Disabled(0x0)(Default): Normal Operation - Disable PCIe BDAT margin data generation, Enable(0x1): Generate PCIe BDAT margin data}
  gKabylakeFspPkgTokenSpaceGuid.PegGenerateBdatMarginTable  | 0x0539 | 0x01 | 0x00

  # !BSF NAME:{PCIe Non-Protocol Awareness for Rx Compliance Testing} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set this policy to enable the generation and addition of PCIe margin data to the BDAT table. Disabled(0x0)(Default): Normal Operation - Disable non-protocol awareness, Enable(0x1): Non-Protocol Awareness Enabled - Enable non-protocol awareness for compliance testing}
  gKabylakeFspPkgTokenSpaceGuid.PegRxCemNonProtocolAwareness  | 0x0540 | 0x01 | 0x00

  # !BSF NAME:{PCIe Override RxCTLE} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable(0x0)(Default): Normal Operation - RxCTLE adaptive behavior enabled, Enable(0x1): Override RxCTLE - Disable RxCTLE adaptive behavior to keep the configured RxCTLE peak values unmodified}
  gKabylakeFspPkgTokenSpaceGuid.PegGen3RxCtleOverride       | 0x0541 | 0x01 | 0x00

  # !BSF NAME:{Rsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable(0x0)(Default): Normal Operation - RxCTLE adaptive behavior enabled, Enable(0x1): Override RxCTLE - Disable RxCTLE adaptive behavior to keep the configured RxCTLE peak values unmodified}
  gKabylakeFspPkgTokenSpaceGuid.PegGen3Rsvd                 | 0x0542 | 0x01 | 0x00

  # !BSF NAME:{Panel Power Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Control for enabling/disabling VDD force bit (Required only for early enabling of eDP panel). 0=Disable, 1(Default)=Enable}
  gKabylakeFspPkgTokenSpaceGuid.PanelPowerEnable            | 0x0543 | 0x01 | 0x01

  # !BSF NAME:{PEG Gen3 Root port preset values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming PEG Gen3 preset values per lane. Range: 0-9, 8 is default for each lane}
  gKabylakeFspPkgTokenSpaceGuid.PegGen3RootPortPreset       | 0x0544 | 0x10 | {0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7}

  # !BSF NAME:{PEG Gen3 End port preset values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming PEG Gen3 preset values per lane. Range: 0-9, 7 is default for each lane}
  gKabylakeFspPkgTokenSpaceGuid.PegGen3EndPointPreset       | 0x0554 | 0x10 | {0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7}

  # !BSF NAME:{PEG Gen3 End port Hint values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming PEG Gen3 Hint values per lane. Range: 0-6, 2 is default for each lane}
  gKabylakeFspPkgTokenSpaceGuid.PegGen3EndPointHint         | 0x0564 | 0x10 | {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2}

  # !BSF NAME:{Jitter Dwell Time for PCIe Gen3 Software Equalization} TYPE:{EditNum, HEX, (0, 0xFFFF)}
  # !BSF HELP:{Range: 0-65535, default is 1000. @warning Do not change from the default}
  gKabylakeFspPkgTokenSpaceGuid.Gen3SwEqJitterDwellTime     | 0x0574 | 0x02 | 3000

  # !BSF NAME:{Jitter Error Target for PCIe Gen3 Software Equalization} TYPE:{EditNum, HEX, (0, 0xFFFF)}
  # !BSF HELP:{Range: 0-65535, default is 1. @warning Do not change from the default}
  gKabylakeFspPkgTokenSpaceGuid.Gen3SwEqJitterErrorTarget   | 0x0576 | 0x02 | 2

  # !BSF NAME:{VOC Dwell Time for PCIe Gen3 Software Equalization} TYPE:{EditNum, HEX, (0, 0xFFFF)}
  # !BSF HELP:{Range: 0-65535, default is 10000. @warning Do not change from the default}
  gKabylakeFspPkgTokenSpaceGuid.Gen3SwEqVocDwellTime        | 0x0578 | 0x02 | 10000

  # !BSF NAME:{VOC Error Target for PCIe Gen3 Software Equalization} TYPE:{EditNum, HEX, (0, 0xFFFF)}
  # !BSF HELP:{Range: 0-65535, default is 2. @warning Do not change from the default}
  gKabylakeFspPkgTokenSpaceGuid.Gen3SwEqVocErrorTarget      | 0x057A | 0x02 | 2

  # !BSF NAME:{SaPreMemTestRsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for SA Pre-Mem Test}
  gKabylakeFspPkgTokenSpaceGuid.SaPreMemTestRsvd            | 0x057C | 0x04 | {0x00}

  #
  # SA Pre-Mem Test Block End
  #

  #
  # Security Test Block Start
  #

  # !BSF NAME:{BiosAcmBase}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of BiosAcmBase , 1: enable}
  #TODO: This value is obtained from flash using GUID - so keeping the default value as 0
  gSkylakeFspPkgTokenSpaceGuid.BiosAcmBase                  | 0x0580 | 0x08 | 0x0000000000000000

  # !BSF NAME:{BiosAcmSize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of BiosAcmSize , 1: enable}
  gSkylakeFspPkgTokenSpaceGuid.BiosAcmSize                  | 0x0588 | 0x04 | 0x00000000

  # !BSF NAME:{TgaSize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TgaSize , 1: enable}
  #TODO: Check if default 0 is ok
  gSkylakeFspPkgTokenSpaceGuid.TgaSize                      | 0x058C | 0x04 | 0x00000000

  # !BSF NAME:{TxtLcpPdBase}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TxtLcpPdBase , 1: enable}
  #TODO: Check if default 0 is ok
  gSkylakeFspPkgTokenSpaceGuid.TxtLcpPdBase                 | 0x0590 | 0x08 | 0x0000000000000000

  # !BSF NAME:{TxtLcpPdSize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TxtLcpPdSize , 1: enable}
  #TODO: Check if default 0 is ok
  gSkylakeFspPkgTokenSpaceGuid.TxtLcpPdSize                 | 0x0598 | 0x08 | 0x0000000000000000

  # !BSF NAME:{TotalFlashSize}  TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TotalFlashSize , 1: enable}
  #TODO: change the value
  gSkylakeFspPkgTokenSpaceGuid.TotalFlashSize               | 0x05A0 | 0x02 | 0x0000

  # !BSF NAME:{BiosSize}  TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of BiosSize , 1: enable}
  gSkylakeFspPkgTokenSpaceGuid.BiosSize                     | 0x05A2 | 0x02 | 0x2000

  #
  # Security Test Block End
  #

  #
  # PCH Pre-Mem Test Block start
  #

  # !BSF NAME:{PCH Dci Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PCH Dci.}
  gKabylakeFspPkgTokenSpaceGuid.PchDciEn                    | 0x05A4 | 0x01 | 0x00

  # !BSF NAME:{PCH Dci Auto Detect} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Deprecated}
  gKabylakeFspPkgTokenSpaceGuid.PchDciAutoDetect            | 0x05A5 | 0x01 | 0x01

  # !BSF NAME:{Smbus dynamic power gating} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable or Enable Smbus dynamic power gating.}
  gKabylakeFspPkgTokenSpaceGuid.SmbusDynamicPowerGating     | 0x05A6 | 0x01 | 0x00

  # !BSF NAME:{Disable and Lock Watch Dog Register} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set 1 to clear WDT status, then disable and lock WDT registers.}
  gKabylakeFspPkgTokenSpaceGuid.WdtDisableAndLock           | 0x05A7 | 0x01 | 0x00

  # !BSF NAME:{SMBUS SPD Write Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set/Clear Smbus SPD Write Disable. 0: leave SPD Write Disable bit; 1: set SPD Write Disable bit. For security recommendations, SPD write disable bit must be set.}
  gKabylakeFspPkgTokenSpaceGuid.SmbusSpdWriteDisable        | 0x05A8 | 0x01 | 0x01

  # !BSF NAME:{ChipsetInit HECI message} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Enable or disable ChipsetInit HECI message. If disabled, it prevents from sending ChipsetInit HECI message. }
  gKabylakeFspPkgTokenSpaceGuid.ChipsetInitMessage          | 0x05A9 | 0x01 | 0x01

  # !BSF NAME:{Bypass ChipsetInit sync reset.} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: disable, 1: enable, Set Enable to bypass the reset after ChipsetInit HECI message.}
  gKabylakeFspPkgTokenSpaceGuid.BypassPhySyncReset          | 0x05AA | 0x01 | 0x0

  #
  # PCH Pre-Mem Test Block End
  #

  #
  # ME Pre-Mem Test Block start
  #
  # !BSF NAME:{Force ME DID Init Status} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: Success, 2: No Memory in Channels, 3: Memory Init Error, 4: Memory not preserved across reset, Set ME DID init stat value}
  gKabylakeFspPkgTokenSpaceGuid.DidInitStat                 | 0x05AB | 0x01 | 0x0

  # !BSF NAME:{CPU Replaced Polling Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Setting this option disables CPU replacement polling loop}
  gKabylakeFspPkgTokenSpaceGuid.DisableCpuReplacedPolling   | 0x05AC | 0x01 | 0x0

  # !BSF NAME:{ME DID Message} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Enable/Disable ME DID Message (disable will prevent the DID message from being sent)}
  gKabylakeFspPkgTokenSpaceGuid.SendDidMsg                  | 0x05AD | 0x01 | 0x1

  # !BSF NAME:{Retry mechanism for HECI APIs} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Enable/Disable HECI retry.}
  gKabylakeFspPkgTokenSpaceGuid.DisableHeciRetry            | 0x05AE | 0x01 | 0x0

  # !BSF NAME:{Check HECI message before send} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Enable/Disable message check.}
  gKabylakeFspPkgTokenSpaceGuid.DisableMessageCheck         | 0x05AF | 0x01 | 0x0

  # !BSF NAME:{Skip MBP HOB} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Enable/Disable MOB HOB.}
  gKabylakeFspPkgTokenSpaceGuid.SkipMbpHob                  | 0x05B0 | 0x01 | 0x0

  # !BSF NAME:{HECI2 Interface Communication} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Adds or Removes HECI2 Device from PCI space.}
  gKabylakeFspPkgTokenSpaceGuid.HeciCommunication2          | 0x05B1 | 0x01 | 0x0

  # !BSF NAME:{Enable KT device} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Enable or Disable KT device.}
  gKabylakeFspPkgTokenSpaceGuid.KtDeviceEnable              | 0x05B2 | 0x01 | 0x1

  # !BSF NAME:{Enable IDEr} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Enable or Disable IDEr.}
  gKabylakeFspPkgTokenSpaceGuid.IderDeviceEnable            | 0x05B3 | 0x01 | 0x1
  #
  # ME Pre-Mem Test Block End
  #

  # !HDR EMBED:{FSP_M_TEST_CONFIG:FspmTestConfig:END}
  gKabylakeFspPkgTokenSpaceGuid.ReservedFspmTestUpd         | 0x05B4 | 0x0C | {0x00}



  # Note please keep "UpdTerminator" at the end of each UPD region.
  # The tool will use this field to determine the actual end of the UPD data
  # structure.
  gKabylakeFspPkgTokenSpaceGuid.UpdTerminator               | 0x0646 | 0x02 | 0x55AA

  ################################################################################
  #
  # UPDs consumed in FspSiliconInit Api
  #
  ################################################################################
  # !BSF FIND:{KBLUPD_S}
  # !HDR COMMENT:{FSP_UPD_HEADER:FSP UPD Header}
  # !HDR EMBED:{FSP_UPD_HEADER:FspUpdHeader:START}
  # FspsUpdSignature: {KBLUPD_S}
  gKabylakeFspPkgTokenSpaceGuid.Signature                   | 0x0000 | 0x08 | 0x535F4450554C424B
  # !BSF NAME:{FspsUpdRevision}  TYPE:{None}
  gKabylakeFspPkgTokenSpaceGuid.Revision                    | 0x0008 | 0x01 | 0x00
  # !HDR EMBED:{FSP_UPD_HEADER:FspUpdHeader:END}
  gKabylakeFspPkgTokenSpaceGuid.Reserved                    | 0x0009 | 0x17 | {0x00}

  # !HDR COMMENT:{FSP_S_CONFIG:Fsp S Configuration}
  # !HDR EMBED:{FSP_S_CONFIG:FspsConfig:START}
  # !BSF PAGE:{SKL}
  # !BSF NAME:{Logo Pointer}
  # !BSF TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Points to PEI Display Logo Image}
  gKabylakeFspPkgTokenSpaceGuid.LogoPtr                     | 0x0020 | 0x04 | 0x00000000

  # !BSF NAME:{Logo Size}
  # !BSF TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Size of PEI Display Logo Image}
  gKabylakeFspPkgTokenSpaceGuid.LogoSize                    | 0x0024 | 0x04 | 0x00000000

  # !BSF NAME:{Graphics Configuration Ptr}
  # !BSF TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Points to VBT}
  gKabylakeFspPkgTokenSpaceGuid.GraphicsConfigPtr           | 0x0028 | 0x04 | 0x00000000

  # !BSF NAME:{Enable Device 4}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable Device 4}
  gKabylakeFspPkgTokenSpaceGuid.Device4Enable               | 0x002C | 0x01 | 0x00

  # !BSF PAGE:{SPT}
  # !BSF NAME:{Enable Intel HD Audio (Azalia)} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable Azalia controller.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaEnable                | 0x002D | 0x01 | 0x01

  # !BSF NAME:{Enable HD Audio DSP} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable HD Audio DSP feature.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaDspEnable             | 0x002E | 0x01 | 0x01

  # !BSF NAME:{Select HDAudio IoBuffer Ownership} TYPE:{Combo}
  # !BSF OPTION:{0:HD-A Link, 1:Shared HD-A Link and I2S Port, 3:I2S Ports}
  # !BSF HELP:{Indicates the ownership of the I/O buffer between Intel HD Audio link vs I2S0 / I2S port. 0: Intel HD-Audio link owns all the I/O buffers. 1: Intel HD-Audio link owns 4 of the I/O buffers for 1 HD-Audio codec connection, and I2S1 port owns 4 of the I/O buffers for 1 I2S codec connection. 2: Reserved. 3: I2S0 and I2S1 ports own all the I/O buffers.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaIoBufferOwnership     | 0x002F | 0x01 | 0x00

  # !BSF NAME:{Enable CIO2 Controller} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable SKYCAM CIO2 Controller.}
  gKabylakeFspPkgTokenSpaceGuid.PchCio2Enable               | 0x0030 | 0x01 | 0x01

  # !BSF NAME:{Enable eMMC Controller} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable eMMC Controller.}
  gKabylakeFspPkgTokenSpaceGuid.ScsEmmcEnabled              | 0x0031 | 0x01 | 0x01

  # !BSF NAME:{Enable eMMC HS400 Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable eMMC HS400 Mode.}
  gKabylakeFspPkgTokenSpaceGuid.ScsEmmcHs400Enabled         | 0x0032 | 0x01 | 0x01

  # !BSF NAME:{Enable SdCard Controller} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable SD Card Controller.}
  gKabylakeFspPkgTokenSpaceGuid.ScsSdCardEnabled            | 0x0033 | 0x01 | 0x01

  # !BSF NAME:{Enable PCH ISH Controller} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable ISH Controller.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshEnable                | 0x0034 | 0x01 | 0x01

  # !BSF NAME:{Show SPI controller} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable to show SPI controller.}
  gKabylakeFspPkgTokenSpaceGuid.ShowSpiController           | 0x0035 | 0x01 | 0x00

  # !BSF NAME:{Flash Configuration Lock Down} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable flash lock down. If platform decides to skip this programming, it must lock SPI flash register DLOCK, FLOCKDN, and WRSDIS before end of post.}
  gKabylakeFspPkgTokenSpaceGuid.SpiFlashCfgLockDown         | 0x0036 | 0x01 | 0x01

  # !BSF NAME:{MicrocodeRegionBase} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Memory Base of Microcode Updates}
  gKabylakeFspPkgTokenSpaceGuid.MicrocodeRegionBase         | 0x0038 | 0x04 | 0x0

  # !BSF NAME:{MicrocodeRegionSize} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Size of Microcode Updates}
  gKabylakeFspPkgTokenSpaceGuid.MicrocodeRegionSize         | 0x003C | 0x04 | 0x0

  # !BSF NAME:{Turbo Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable Turbo mode. 0: disable, 1: enable}
  gKabylakeFspPkgTokenSpaceGuid.TurboMode                   | 0x0040 | 0x01 | 0x1

  # !BSF NAME:{Enable SATA SALP Support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable SATA Aggressive Link Power Management.}
  gKabylakeFspPkgTokenSpaceGuid.SataSalpSupport             | 0x0041 | 0x01 | 0x01

  # !BSF NAME:{Enable SATA ports} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/disable SATA ports. One byte for each port, byte0 for port0, byte1 for port1, and so on.}
  gKabylakeFspPkgTokenSpaceGuid.SataPortsEnable             | 0x0042 | 0x08 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}

  # !BSF NAME:{Enable SATA DEVSLP Feature} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/disable SATA DEVSLP per port. 0 is disable, 1 is enable. One byte for each port, byte0 for port0, byte1 for port1, and so on.}
  gKabylakeFspPkgTokenSpaceGuid.SataPortsDevSlp             | 0x004A | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable USB2 ports} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/disable per USB2 ports. One byte for each port, byte0 for port0, byte1 for port1, and so on.}
  gKabylakeFspPkgTokenSpaceGuid.PortUsb20Enable             | 0x0052 | 0x10 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}

  # !BSF NAME:{Enable USB3 ports} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/disable per USB3 ports. One byte for each port, byte0 for port0, byte1 for port1, and so on.}
  gKabylakeFspPkgTokenSpaceGuid.PortUsb30Enable             | 0x0062 | 0x0A | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}

  # !BSF NAME:{Enable xDCI controller} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable to xDCI controller.}
  gKabylakeFspPkgTokenSpaceGuid.XdciEnable                  | 0x006C | 0x01 | 0x01

  # !BSF NAME:{Enable XHCI SSIC Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable XHCI SSIC port.}
  gKabylakeFspPkgTokenSpaceGuid.SsicPortEnable              | 0x006D | 0x01 | 0x01

  # !BSF NAME:{Number of DevIntConfig Entry} TYPE:{EditNum, HEX, (0x00,0x40)}
  # !BSF HELP:{Number of Device Interrupt Configuration Entry. If this is not zero, the DevIntConfigPtr must not be NULL.}
  gKabylakeFspPkgTokenSpaceGuid.NumOfDevIntConfig           | 0x006F | 0x01 | 0x00

  # !BSF NAME:{Address of PCH_DEVICE_INTERRUPT_CONFIG table.} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{The address of the table of PCH_DEVICE_INTERRUPT_CONFIG.}
  gKabylakeFspPkgTokenSpaceGuid.DevIntConfigPtr             | 0x0070 | 0x04 | 0x00

  # !BSF NAME:{Enable SerialIo Device Mode} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0:Disabled, 1:ACPI Mode, 2:PCI Mode, 3:Hidden mode, 4:Legacy UART mode - Enable/disable SerialIo I2C0,I2C1,I2C2,I2C3,I2C4,I2C5,SPI0,SPI1,UART0,UART1,UART2 device mode respectively. One byte for each controller, byte0 for I2C0, byte1 for I2C1, and so on.}
  gKabylakeFspPkgTokenSpaceGuid.SerialIoDevMode             | 0x0074 | 0x0B | { 0x02, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x04}

  # !BSF NAME:{PIRQx to IRQx Map Config} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PIRQx to IRQx mapping. The valid value is 0x00 to 0x0F for each. First byte is for PIRQA, second byte is for PIRQB, and so on. The setting is only available in Legacy 8259 PCI mode.}
  gKabylakeFspPkgTokenSpaceGuid.PxRcConfig                  | 0x007F | 0x08 | { 0x0B, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B}

  # !BSF NAME:{Select GPIO IRQ Route}
  # !BSF TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{GPIO IRQ Select. The valid value is 14 or 15.}
  gKabylakeFspPkgTokenSpaceGuid.GpioIrqRoute                | 0x0087 | 0x01 | 0x0E

  # !BSF NAME:{Select SciIrqSelect}
  # !BSF TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{SCI IRQ Select. The valid value is 9, 10, 11, and 20, 21, 22, 23 for APIC only.}
  gKabylakeFspPkgTokenSpaceGuid.SciIrqSelect                | 0x0088 | 0x01 | 0x09

  # !BSF NAME:{Select TcoIrqSelect}
  # !BSF TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{TCO IRQ Select. The valid value is 9, 10, 11, 20, 21, 22, 23.}
  gKabylakeFspPkgTokenSpaceGuid.TcoIrqSelect                | 0x0089 | 0x01 | 0x09

  # !BSF NAME:{Enable/Disable Tco IRQ}
  # !BSF OPTION:{$EN_DIS}}
  # !BSF HELP:{Enable/disable TCO IRQ}
  gKabylakeFspPkgTokenSpaceGuid.TcoIrqEnable                | 0x008A | 0x01 | 0x00

  # !BSF NAME:{PCH HDA Verb Table Entry Number} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Number of Entries in Verb Table.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaVerbTableEntryNum     | 0x008B | 1 | 0

  # !BSF NAME:{PCH HDA Verb Table Pointer} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Pointer to Array of pointers to Verb Table.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaVerbTablePtr          | 0x008C | 4 | 0

  # !BSF NAME:{Enable SATA} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable SATA controller.}
  gKabylakeFspPkgTokenSpaceGuid.SataEnable                  | 0x0091 | 0x01 | 0x01

  # !BSF NAME:{SATA Mode} TYPE:{Combo}
  # !BSF OPTION:{0:AHCI, 1:RAID}
  # !BSF HELP:{Select SATA controller working mode.}
  gKabylakeFspPkgTokenSpaceGuid.SataMode                    | 0x0092 | 0x01 | 0x00

  # !BSF NAME:{USB Per Port HS Preemphasis Bias} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB Per Port HS Preemphasis Bias. 000b-0mV, 001b-11.25mV, 010b-16.9mV, 011b-28.15mV, 100b-28.15mV, 101b-39.35mV, 110b-45mV, 111b-56.3mV. One byte for each port.}
  gKabylakeFspPkgTokenSpaceGuid.Usb2AfePetxiset             | 0x0093 | 0x10 | {0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07}
  # !BSF NAME:{USB Per Port HS Transmitter Bias} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB Per Port HS Transmitter Bias. 000b-0mV, 001b-11.25mV, 010b-16.9mV, 011b-28.15mV, 100b-28.15mV, 101b-39.35mV, 110b-45mV, 111b-56.3mV, One byte for each port.}
  gKabylakeFspPkgTokenSpaceGuid.Usb2AfeTxiset               | 0x00A3 | 0x10 | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
  # !BSF NAME:{USB Per Port HS Transmitter Emphasis} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB Per Port HS Transmitter Emphasis. 00b - Emphasis OFF, 01b - De-emphasis ON, 10b - Pre-emphasis ON, 11b - Pre-emphasis & De-emphasis ON. One byte for each port.}
  gKabylakeFspPkgTokenSpaceGuid.Usb2AfePredeemp             | 0x00B3 | 0x10 | {0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03}
  # !BSF NAME:{USB Per Port Half Bit Pre-emphasis} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB Per Port Half Bit Pre-emphasis. 1b - half-bit pre-emphasis, 0b - full-bit pre-emphasis. One byte for each port.}
  gKabylakeFspPkgTokenSpaceGuid.Usb2AfePehalfbit            | 0x00C3 | 0x10 | {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable the write to USB 3.0 TX Output -3.5dB De-Emphasis Adjustment} TYPE:{EditNum, HEX, (0x00,0x01010101010101010101)}
  # !BSF HELP:{Enable the write to USB 3.0 TX Output -3.5dB De-Emphasis Adjustment. Each value in arrary can be between 0-1. One byte for each port.}
  gKabylakeFspPkgTokenSpaceGuid.Usb3HsioTxDeEmphEnable      | 0x00D3 | 0x0A | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
  # !BSF NAME:{USB 3.0 TX Output -3.5dB De-Emphasis Adjustment Setting} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB 3.0 TX Output -3.5dB De-Emphasis Adjustment Setting, HSIO_TX_DWORD5[21:16], <b>Default = 29h</b> (approximately -3.5dB De-Emphasis). One byte for each port.}
  gKabylakeFspPkgTokenSpaceGuid.Usb3HsioTxDeEmph            | 0x00DD | 0x0A | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
  # !BSF NAME:{Enable the write to USB 3.0 TX Output Downscale Amplitude Adjustment} TYPE:{EditNum, HEX, (0x00,0x01010101010101010101)}
  # !BSF HELP:{Enable the write to USB 3.0 TX Output Downscale Amplitude Adjustment, Each value in arrary can be between 0-1. One byte for each port.}
  gKabylakeFspPkgTokenSpaceGuid.Usb3HsioTxDownscaleAmpEnable  | 0x00E7 | 0x0A | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
  # !BSF NAME:{USB 3.0 TX Output Downscale Amplitude Adjustment} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB 3.0 TX Output Downscale Amplitude Adjustment, HSIO_TX_DWORD8[21:16], <b>Default = 00h</b>. One byte for each port.}
  gKabylakeFspPkgTokenSpaceGuid.Usb3HsioTxDownscaleAmp      | 0x00F1 | 0x0A | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable LAN} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable LAN controller.}
  gKabylakeFspPkgTokenSpaceGuid.PchLanEnable                | 0x00FB | 0x01 | 0x01

  # !BSF NAME:{Delay USB PDO Programming} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable delay of PDO programming for USB from PEI phase to DXE phase. 0: disable, 1: enable}
  gKabylakeFspPkgTokenSpaceGuid.DelayUsbPdoProgramming      | 0x00FC | 0x01 | 0x00

  # !BSF NAME:{Enable PCIE RP CLKREQ Support} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/disable PCIE Root Port CLKREQ support. 0: disable, 1: enable. One byte for each port, byte0 for port1, byte1 for port2, and so on.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpClkReqSupport         | 0x0114 | 0x18 | { 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Configure CLKREQ Number} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Configure Root Port CLKREQ Number if CLKREQ is supported. Each value in arrary can be between 0-6. One byte for each port, byte0 for port1, byte1 for port2, and so on.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpClkReqNumber          | 0x012C | 0x18 | { 0x02, 0x00, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x05, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  #
  # ME
  #
  # !BSF NAME:{HECI3 state} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{The HECI3 state from Mbp for reference in S3 path or when MbpHob is not installed. 0: disable, 1: enable}
  gKabylakeFspPkgTokenSpaceGuid.Heci3Enabled                | 0x0149 | 0x01 | 0x0

  #
  # AMT
  #
  # !BSF NAME:{AMT Switch} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Enable or disable AMT functionality.}
  gKabylakeFspPkgTokenSpaceGuid.AmtEnabled                  | 0x0153 | 0x01 | 0x01
  # !BSF NAME:{WatchDog Timer Switch} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Enable or disable WatchDog timer.}
  gKabylakeFspPkgTokenSpaceGuid.WatchDog                    | 0x0154 | 0x01 | 0x0
  # !BSF NAME:{ASF Switch} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Enable or disable ASF functionality.}
  gKabylakeFspPkgTokenSpaceGuid.AsfEnabled                  | 0x0155 | 0x01 | 0x0
  # !BSF NAME:{Manageability Mode set by Mebx} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Enable or disable  Manageability Mode.}
  gKabylakeFspPkgTokenSpaceGuid.ManageabilityMode           | 0x0156 | 0x01 | 0x0
  # !BSF NAME:{PET Progress} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Enable/Disable PET Events Progress to receive PET Events.}
  gKabylakeFspPkgTokenSpaceGuid.FwProgress                  | 0x0157 | 0x01 | 0x0
  # !BSF NAME:{OS Timer} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{16 bits Value, Set OS watchdog timer.}
  gKabylakeFspPkgTokenSpaceGuid.WatchDogTimerOs             | 0x0158 | 0x02 | 0x0
  # !BSF NAME:{BIOS Timer} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{16 bits Value, Set BIOS watchdog timer.}
  gKabylakeFspPkgTokenSpaceGuid.WatchDogTimerBios           | 0x015A | 0x02 | 0x0
  # !BSF NAME:{SOL Switch} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Serial Over Lan enable/disable state by Mebx}
  gKabylakeFspPkgTokenSpaceGuid.AmtSolEnabled               | 0x015C | 0x01 | 0x0

  #
  # PCH continued
  #
  # !BSF NAME:{Configure CLKSRC Number} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Configure Root Port CLKSRC Number. Each value in arrary can be between 0-6 for valid clock numbers or 0x1F for an invalid number. One byte for each port, byte0 for port1, byte1 for port2, and so on.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpClkSrcNumber          | 0x015D | 0x18 | { 0x02, 0x1f, 0x1f, 0x1f, 0x03, 0x01, 0x1f, 0x1f, 0x05, 0x04, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f }

  # !BSF NAME:{Force Disable clock } TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Disables clock even if link is inactive default value is 0}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpForceClkDisableWhenRpDisable            | 0x0175 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  #
  # SA Post-Mem Production Block Start
  #

  # !BSF NAME:{Subsystem Vendor ID for SA devices} TYPE:{EditNum, HEX, (0x00, 0xFFFF)}
  # !BSF HELP:{Subsystem ID that will be programmed to SA devices: Default SubSystemVendorId=0x8086}
  gKabylakeFspPkgTokenSpaceGuid.DefaultSvid                 | 0x0200 | 0x2 | 0x8086

  # !BSF NAME:{Subsystem Device ID for SA devices} TYPE:{EditNum, HEX, (0x00, 0xFFFF)}
  # !BSF HELP:{Subsystem ID that will be programmed to SA devices: Default SubSystemId=0x2015}
  gKabylakeFspPkgTokenSpaceGuid.DefaultSid                  | 0x0202 | 0x2 | 0x2015

  # !BSF NAME:{Enable/Disable SA CRID} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: SA CRID, Disable (Default): SA CRID}
  gKabylakeFspPkgTokenSpaceGuid.CridEnable                  | 0x0204 | 0x01 | 0x0

  # !BSF NAME:{DMI ASPM} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 2:L1}
  # !BSF HELP:{0=Disable, 2(Default)=L1}
  gKabylakeFspPkgTokenSpaceGuid.DmiAspm                     | 0x0205 | 0x01 | 0x2

  # !BSF NAME:{PCIe Physical Slot Number per root port} TYPE:{EditNum, HEX, (0, 8191)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Physical Slot Number per root port}
  gKabylakeFspPkgTokenSpaceGuid.PegPhysicalSlotNumber       | 0x0206 | 0x6 | {1, 1, 1}

  # !BSF NAME:{PCIe DeEmphasis control per root port} TYPE:{EditNum, HEX, (0x00, 0xFFFFFF)}
  # !BSF OPTION:{0:-6dB, 1:-3.5dB}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{0: -6dB, 1(Default): -3.5dB}
  gKabylakeFspPkgTokenSpaceGuid.PegDeEmphasis               | 0x020C | 0x3 | {0x1, 0x1, 0x1}

  # !BSF NAME:{PCIe Slot Power Limit value per root port} TYPE:{EditNum, HEX, (0x00, 0xFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Slot power limit value per root port}
  gKabylakeFspPkgTokenSpaceGuid.PegSlotPowerLimitValue      | 0x020F | 0x3 | {75, 75, 75}

  # !BSF NAME:{PCIe Slot Power Limit scale per root port} TYPE:{EditNum, HEX, (0x00, 0xFFFFFF)}
  # !BSF OPTION:{0:1.0x, 1:0.1x, 2:0.01x, 3:0x001x}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Slot power limit scale per root port}
  gKabylakeFspPkgTokenSpaceGuid.PegSlotPowerLimitScale      | 0x0212 | 0x3 | {0, 0, 0}

  # !BSF NAME:{Enable/Disable PavpEnable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable PavpEnable, Disable: Disable PavpEnable}
  gKabylakeFspPkgTokenSpaceGuid.PavpEnable                  | 0x0215 | 0x01 | 0x1

  # !BSF NAME:{CdClock Frequency selection} TYPE:{Combo}
  # !BSF OPTION:{0: 337.5 Mhz, 1: 450 Mhz, 2: 540 Mhz, 3: 675 Mhz}
  # !BSF HELP:{0=337.5 Mhz, 1=450 Mhz, 2=540 Mhz, 3(Default)= 675 Mhz}
  gKabylakeFspPkgTokenSpaceGuid.CdClock                     | 0x0216 | 0x1 | 0x3

  # !BSF NAME:{Enable/Disable PeiGraphicsPeimInit} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Enable PeiGraphicsPeimInit, Disable(Default): Disable PeiGraphicsPeimInit}
  gKabylakeFspPkgTokenSpaceGuid.PeiGraphicsPeimInit         | 0x0217 | 0x01 | 0x1

  # !BSF NAME:{Enable/Disable SA IMGU(SKYCAM)} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable SA IMGU(SKYCAM), Disable: Disable SA IMGU(SKYCAM)}
  gKabylakeFspPkgTokenSpaceGuid.SaImguEnable                | 0x0218 | 0x01 | 0x1

  # !BSF NAME:{Enable or disable GMM device} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable, 1(Default)=Enable}
  gKabylakeFspPkgTokenSpaceGuid.GmmEnable                   | 0x0219 | 0x1 | 0x1

  # !BSF NAME:{State of X2APIC_OPT_OUT bit in the DMAR table} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable/Clear, 1=Enable/Set}
  gKabylakeFspPkgTokenSpaceGuid.X2ApicOptOut                | 0x021A | 0x1 | 0x0

  # !BSF NAME:{Base addresses for VT-d function MMIO access} TYPE:{EditNum, HEX, (0, 0xFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Base addresses for VT-d MMIO access per VT-d engine}
  gKabylakeFspPkgTokenSpaceGuid.VtdBaseAddress              | 0x021C | 0x8 | {0xFED90000, 0xFED91000}

  # !BSF NAME:{Program GT Chicken bits}
  # !BSF HELP:{Progarm the GT chicken bits in GTTMMADR + 0xD00 BITS [3:1]}
  gPlatformFspPkgTokenSpaceGuid.ProgramGtChickenBits        | 0x0224 | 0x1 | 0xE

  # !BSF NAME:{SaPostMemProductionRsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for SA Post-Mem Production}
  gKabylakeFspPkgTokenSpaceGuid.SaPostMemProductionRsvd     | 0x0237 | 0xF | {0x00}

  #
  # SA Post-Mem Production Block End
  #

  #
  # CPU Post-Mem Production Block Start
  #
  # !BSF NAME:{Power State 3 enable/disable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Power State 3 enable/disable; 0: Disable; <b>1: Enable</b>. For all VR Indexes}
  gKabylakeFspPkgTokenSpaceGuid.Psi3Enable                  | 0x024E | 0x05 | {0x01, 0x01, 0x01, 0x01, 0x01}

  # !BSF NAME:{Power State 4 enable/disable}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Power State 4 enable/disable; 0: Disable; <b>1: Enable</b>.For all VR Indexes}
  gKabylakeFspPkgTokenSpaceGuid.Psi4Enable                  | 0x0253 | 0x05 | {0x01, 0x01, 0x01, 0x01, 0x01}

  # !BSF NAME:{Imon slope correction}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Imon slope correction. Specified in 1/100 increment values. Range is 0-200. 125 = 1.25. <b>0: Auto</b>.For all VR Indexes}
  gKabylakeFspPkgTokenSpaceGuid.ImonSlope                   | 0x0258 | 0x05 | {0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Imon offset correction}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Imon offset correction. Value is a 2's complement signed integer. Units 1/1000, Range 0-63999. For an offset = 12.580, use 12580. <b>0: Auto</b>}
  gKabylakeFspPkgTokenSpaceGuid.ImonOffset                  | 0x025D | 0x05 | {0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable/Disable BIOS configuration of VR}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable BIOS configuration of VR; <b>0: Disable</b>; 1: Enable.For all VR Indexes}
  gKabylakeFspPkgTokenSpaceGuid.VrConfigEnable              | 0x0262 | 0x05 | {0x01, 0x01, 0x01, 0x01, 0x01}

  # !BSF NAME:{Thermal Design Current enable/disable}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Thermal Design Current enable/disable; <b>0: Disable</b>; 1: Enable.For all VR Indexes}
  gKabylakeFspPkgTokenSpaceGuid.TdcEnable                   | 0x0267 | 0x05 | {0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{HECI3 state} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Thermal Design Current time window. Defined in milli seconds. Valid Values 1 - 1ms , 2 - 2ms , 3 - 3ms , 4 - 4ms , 5 - 5ms , 6 - 6ms , 7 - 7ms , 8 - 8ms , 10 - 10ms.For all VR Indexe}
  gKabylakeFspPkgTokenSpaceGuid.TdcTimeWindow               | 0x026C | 0x05 | {0x01, 0x01, 0x01, 0x01, 0x01}

  # !BSF NAME:{Thermal Design Current Lock}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Thermal Design Current Lock; <b>0: Disable</b>; 1: Enable.For all VR Indexes}
  gKabylakeFspPkgTokenSpaceGuid.TdcLock                     | 0x0271 | 0x05 | {0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Platform Psys slope correction}
  # !BSF TYPE:{EditNum, HEX, (0x00,0xC8)}
  # !BSF HELP:{PCODE MMIO Mailbox: Platform Psys slope correction. <b>0 - Auto</b> Specified in 1/100 increment values. Range is 0-200. 125 = 1.25}
  gKabylakeFspPkgTokenSpaceGuid.PsysSlope                   | 0x0276 | 0x01 | 0x00

  # !BSF NAME:{Platform Psys offset correction}
  # !BSF TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Platform Psys offset correction. <b>0 - Auto</b> Units 1/4, Range 0-255. Value of 100 = 100/4 = 25 offset}
  gKabylakeFspPkgTokenSpaceGuid.PsysOffset                  | 0x0277 | 0x01 | 0x00

  # !BSF NAME:{Acoustic Noise Mitigation feature}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Acoustic Noise Mitigation feature. <b>0: Disabled</b>; 1: Enabled}
  gKabylakeFspPkgTokenSpaceGuid.AcousticNoiseMitigation     | 0x0278 | 0x01 | 0x00

  # !BSF NAME:{Disable Fast Slew Rate for Deep Package C States for VR IA domain}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable Fast Slew Rate for Deep Package C States based on Acoustic Noise Mitigation feature enabled. <b>0: False</b>; 1: True}
  gKabylakeFspPkgTokenSpaceGuid.FastPkgCRampDisableIa           | 0x0279 | 0x01 | 0x00

  # !BSF NAME:{Slew Rate configuration for Deep Package C States for VR IA domain}
  # !BSF TYPE:{Combo} OPTION:{0: Fast/2, 1: Fast/4, 2: Fast/8, 3: Fast/16}
  # !BSF HELP:{Slew Rate configuration for Deep Package C States for VR IA domain based on Acoustic Noise Mitigation feature enabled. <b>0: Fast/2</b>; 1: Fast/4; 2: Fast/8; 3: Fast/16}
  gKabylakeFspPkgTokenSpaceGuid.SlowSlewRateForIa           | 0x027A | 0x01 | 0x00

  # !BSF NAME:{Slew Rate configuration for Deep Package C States for VR GT domain}
  # !BSF TYPE:{Combo} OPTION:{0: Fast/2, 1: Fast/4, 2: Fast/8, 3: Fast/16}
  # !BSF HELP:{Slew Rate configuration for Deep Package C States for VR GT domain based on Acoustic Noise Mitigation feature enabled. <b>0: Fast/2</b>; 1: Fast/4; 2: Fast/8; 3: Fast/16}
  gKabylakeFspPkgTokenSpaceGuid.SlowSlewRateForGt           | 0x027B | 0x01 | 0x00

  # !BSF NAME:{Slew Rate configuration for Deep Package C States for VR SA domain}
  # !BSF TYPE:{Combo} OPTION:{0: Fast/2, 1: Fast/4, 2: Fast/8, 3: Fast/16}
  # !BSF HELP:{Slew Rate configuration for Deep Package C States for VR SA domain based on Acoustic Noise Mitigation feature enabled. <b>0: Fast/2</b>; 1: Fast/4; 2: Fast/8; 3: Fast/16}
  gKabylakeFspPkgTokenSpaceGuid.SlowSlewRateForSa           | 0x027C | 0x01 | 0x00

  # !BSF NAME:{Thermal Design Current current limit} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: Thermal Design Current current limit. Specified in 1/8A units. Range is 0-4095. 1000 = 125A. <b>0: Auto</b>. For all VR Indexes}
  gKabylakeFspPkgTokenSpaceGuid.TdcPowerLimit               | 0x0286 | 0xA | {0x0 , 0x0, 0x0 , 0x0 , 0x0}

  # !BSF NAME:{CPU VR Power Delivery Design}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Used to communicate the power delivery design capability of the board. This value is an enum of the available power delivery segments that are defined in the Platform Design Guide.}
  gKabylakeFspPkgTokenSpaceGuid.VrPowerDeliveryDesign       | 0x0290 | 0x04 | 0x00000000

  # !BSF NAME:{AcLoadline}TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: AcLoadline in 1/100 mOhms (ie. 1250 = 12.50 mOhm); Range is 0-6249. <b>Intel Recommended Defaults vary by domain and SKU.}
  gKabylakeFspPkgTokenSpaceGuid.AcLoadline                  | 0x0298 | 0xA | {0x0 , 0x0, 0x0 , 0x0 , 0x0}

  # !BSF NAME:{DcLoadline} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: DcLoadline in 1/100 mOhms (ie. 1250 = 12.50 mOhm); Range is 0-6249.<b>Intel Recommended Defaults vary by domain and SKU.</b>}
  gKabylakeFspPkgTokenSpaceGuid.DcLoadline                  | 0x02A2 | 0xA | {0x0 , 0x0, 0x0 , 0x0 , 0x0}

  # !BSF NAME:{Power State 1 Threshold current} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: Power State 1 current cuttof in 1/4 Amp increments. Range is 0-128A. Default Value = 20A.}
  gKabylakeFspPkgTokenSpaceGuid.Psi1Threshold               | 0x02AC | 0xA | {0x0 , 0x0, 0x0 , 0x0 , 0x0}

  # !BSF NAME:{Power State 2 Threshold current} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: Power State 2 current cuttof in 1/4 Amp increments. Range is 0-128A. Default Value = 5A.}
  gKabylakeFspPkgTokenSpaceGuid.Psi2Threshold               | 0x02B6 | 0xA | {0x0 , 0x0, 0x0 , 0x0 , 0x0}

  # !BSF NAME:{Power State 3 Threshold current} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: Power State 3 current cuttof in 1/4 Amp increments. Range is 0-128A. Default Value = 1A.}
  gKabylakeFspPkgTokenSpaceGuid.Psi3Threshold               | 0x02C0 | 0xA | {0x0 , 0x0, 0x0 , 0x0 , 0x0}

  # !BSF NAME:{Icc Max limit} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: VR Icc Max limit. 0-255A in 1/4 A units. 400 = 100A}
  gKabylakeFspPkgTokenSpaceGuid.IccMax                      | 0x02CA | 0xA | {0x0 , 0x0, 0x0 , 0x0 , 0x0}

  # !BSF NAME:{VR Voltage Limit} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: VR Voltage Limit. Range is 0-7999mV.}
  gKabylakeFspPkgTokenSpaceGuid.VrVoltageLimit              | 0x02D4 | 0xA | {0x0 , 0x0, 0x0 , 0x0 , 0x0}

  # !BSF NAME:{Disable Fast Slew Rate for Deep Package C States for VR GT domain}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable Fast Slew Rate for Deep Package C States based on Acoustic Noise Mitigation feature enabled. <b>0: False</b>; 1: True}
  gKabylakeFspPkgTokenSpaceGuid.FastPkgCRampDisableGt           | 0x02DF | 0x01 | 0x00

  # !BSF NAME:{Disable Fast Slew Rate for Deep Package C States for VR SA domain}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable Fast Slew Rate for Deep Package C States based on Acoustic Noise Mitigation feature enabled. <b>0: False</b>; 1: True}
  gKabylakeFspPkgTokenSpaceGuid.FastPkgCRampDisableSa           | 0x02E0 | 0x01 | 0x00

  # !BSF NAME:{Enable VR specific mailbox command} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{VR specific mailbox commands. <b>00b - no VR specific command sent.</b>  01b - A VR mailbox command specifically for the MPS IMPV8 VR will be sent. 10b - VR specific command sent for PS4 exit issue. 11b - Reserved.}
  gKabylakeFspPkgTokenSpaceGuid.SendVrMbxCmd                | 0x02E2 | 0x01 | 0x00

  # !BSF NAME:{Select VR specific mailbox command to send} TYPE:{EditNum, HEX, (0x0,0x7)}
  # !BSF HELP:{VR specific mailbox commands. <b>000b - no VR specific command sent.</b>  001b - VR mailbox command specifically for the MPS IMPV8 VR will be sent. 010b - VR specific command sent for PS4 exit issue. 100b - VR specific command sent for MPS VR decay issue.}
  gKabylakeFspPkgTokenSpaceGuid.SendVrMbxCmd1               | 0x02E3 | 0x01 | 0x00

  # !BSF NAME:{CpuS3ResumeMtrrData} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Pointer to CPU S3 Resume MTRR Data}
  gKabylakeFspPkgTokenSpaceGuid.CpuS3ResumeMtrrData         | 0x02E4| 0x04 | 0

  # !HDR STRUCT:{CPU_CONFIG_FSP_DATA}
  # !BSF HELP:{Cpu Configuration data.}
  # !BSF NAME:{Cpu Configuration}
  gKabylakeFspPkgTokenSpaceGuid.CpuConfig | 0x2E8 | 0x08 | {0x09, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{AesEnable} TYPE:{Combo} OPTION:{0:Disable, 1:Enable}
  # !BSF HELP:{Enable or Disable Advanced Encryption Standard (AES) feature.}
  # !BSF FIELD:{AesEnable:1b}

  # !BSF NAME:{EnableRsr} TYPE:{Combo} OPTION:{0:Disable, 1:Enable}
  # !BSF HELP:{Enable or Disable RSR feature.}
  # !BSF FIELD:{EnableRsr:1b}

  # !BSF NAME:{EnableDts} TYPE:{Combo} OPTION:{0:EC, 1:DTS SMM, 2:EC and DTS SMM}
  # !BSF HELP:{Policies to obtain CPU temperature. 0: ACPI thermal management uses EC reported temperature values. 1: ACPI thermal management uses DTS SMM mechanism to obtain CPU temperature values. 2: ACPI Thermal Management uses EC reported temperature values and DTS SMM is used to handle Out of Spec condition.}
  # !BSF FIELD:{EnableDts:2b}

  # !BSF NAME:{SmmbaseSwSmiNumber} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Software SMI number for handler to save CPU information in SMRAM.}
  # !BSF FIELD:{SmmbaseSwSmiNumber:8b}

  # !BSF NAME:{TxtEnable} TYPE:{Combo} OPTION:{0:Disable, 1:Enable}
  # !BSF HELP:{Enable or Disable Trusted Execution Technology (TXT) feature.}
  # !BSF FIELD:{TxtEnable:1b}

  # !BSF NAME:{SkipMpInit} TYPE:{Combo} OPTION:{0:Disable, 1:Enable}
  # !BSF HELP:{Silicon Initialization will skip MP Initialization (including BSP) if enabled.}
  # !BSF FIELD:{SkipMpInit:1b}

  # !BSF NAME:{RsvdBits} TYPE:{EditNum, HEX, (0x0,0x7FFF)}
  # !BSF HELP:{Reserved for future use.}
  # !BSF FIELD:{RsvdBits:18b}

  # !BSF NAME:{MicrocodePatchAddress} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Pointer to microcode patch that is suitable for this processor.}
  gKabylakeFspPkgTokenSpaceGuid.MicrocodePatchAddress       | 0x2F0 | 0x08 | 0x00


  # !BSF NAME:{CpuS3ResumeMtrrDataSize} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Size of S3 resume MTRR data.}
  gKabylakeFspPkgTokenSpaceGuid.CpuS3ResumeMtrrDataSize     | 0x02F8 | 0x02 | 0

  #
  # CPU Post-Mem Production Block End
  #

  #
  #  PCH Silicon Offset start
  #

  # !BSF NAME:{Enable SkyCam PortA Termination override} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PortA Termination override.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortATermOvrEnable | 0x02FB | 0x01 | 0x00

  # !BSF NAME:{Enable SkyCam PortB Termination override} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PortB Termination override.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortBTermOvrEnable | 0x02FC | 0x01 | 0x00

  # !BSF NAME:{Enable SkyCam PortC Termination override} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PortC Termination override.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortCTermOvrEnable | 0x02FD | 0x01 | 0x00

  # !BSF NAME:{Enable SkyCam PortD Termination override} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PortD Termination override.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortDTermOvrEnable | 0x02FE | 0x01 | 0x00

  # !BSF NAME:{Enable SkyCam PortA Clk Trim} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PortA Clk Trim.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortATrimEnable    | 0x02FF | 0x01 | 0x01

  # !BSF NAME:{Enable SkyCam PortB Clk Trim} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PortB Clk Trim.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortBTrimEnable    | 0x0300 | 0x01 | 0x01

  # !BSF NAME:{Enable SkyCam PortC Clk Trim} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PortC Clk Trim.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortCTrimEnable    | 0x0301 | 0x01 | 0x01

  # !BSF NAME:{Enable SkyCam PortD Clk Trim} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PortD Clk Trim.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortDTrimEnable    | 0x0302 | 0x01 | 0x01

  # !BSF NAME:{Enable SkyCam PortA Ctle} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PortA Ctle.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortACtleEnable    | 0x0303 | 0x01 | 0x00

  # !BSF NAME:{Enable SkyCam PortB Ctle} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PortB Ctle.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortBCtleEnable    | 0x0304 | 0x01 | 0x00

  # !BSF NAME:{Enable SkyCam PortCD Ctle} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PortCD Ctle.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortCDCtleEnable   | 0x0305 | 0x01 | 0x00

  # !BSF NAME:{Enable SkyCam PortA Ctle Cap Value} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Enable/disable PortA Ctle Cap Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortACtleCapValue  | 0x0306 | 0x01 | 0x0E

  # !BSF NAME:{Enable SkyCam PortB Ctle Cap Value} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Enable/disable PortB Ctle Cap Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortBCtleCapValue  | 0x0307 | 0x01 | 0x0E

  # !BSF NAME:{Enable SkyCam PortCD Ctle Cap Value} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Enable/disable PortCD Ctle Cap Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortCDCtleCapValue | 0x0308 | 0x01 | 0x0E

  # !BSF NAME:{Enable SkyCam PortA Ctle Res Value} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Enable/disable PortA Ctle Res Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortACtleResValue  | 0x0309 | 0x01 | 0x0D

  # !BSF NAME:{Enable SkyCam PortB Ctle Res Value} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Enable/disable PortB Ctle Res Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortBCtleResValue  | 0x030A | 0x01 | 0x0D

  # !BSF NAME:{Enable SkyCam PortCD Ctle Res Value} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Enable/disable PortCD Ctle Res Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortCDCtleResValue | 0x030B | 0x01 | 0x0D

  # !BSF NAME:{Enable SkyCam PortA Clk Trim Value} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Enable/disable PortA Clk Trim Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortAClkTrimValue  | 0x030C | 0x01 | 0x0A

  # !BSF NAME:{Enable SkyCam PortB Clk Trim Value} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Enable/disable PortB Clk Trim Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortBClkTrimValue  | 0x030D | 0x01 | 0x0A

  # !BSF NAME:{Enable SkyCam PortC Clk Trim Value} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Enable/disable PortC Clk Trim Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortCClkTrimValue  | 0x030E | 0x01 | 0x09

  # !BSF NAME:{Enable SkyCam PortD Clk Trim Value} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Enable/disable PortD Clk Trim Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortDClkTrimValue  | 0x030F | 0x01 | 0x0A

  # !BSF NAME:{Enable SkyCam Port A Data Trim Value} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Enable/disable Port A Data Trim Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortADataTrimValue | 0x0310 | 0x02 | 0xBBBB

  # !BSF NAME:{Enable SkyCam Port B Data Trim Value} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Enable/disable Port B Data Trim Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortBDataTrimValue | 0x0312 | 0x02 | 0xBBBB

  # !BSF NAME:{Enable SkyCam C/D Data Trim Value} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Enable/disable C/D Data Trim Value.}
  gKabylakeFspPkgTokenSpaceGuid.PchSkyCamPortCDDataTrimValue  | 0x0314 | 0x02 | 0xCCCC

  # !BSF NAME:{Enable DMI ASPM} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{ASPM on PCH side of the DMI Link.}
  gKabylakeFspPkgTokenSpaceGuid.PchDmiAspm                  | 0x0316 | 0x01 | 0x01

  # !BSF NAME:{Enable Power Optimizer} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable DMI Power Optimizer on PCH side.}
  gKabylakeFspPkgTokenSpaceGuid.PchPwrOptEnable             | 0x0317 | 0x01 | 0x00

  # !BSF NAME:{PCH Flash Protection Ranges Write Enble} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{Write or erase is blocked by hardware.}
  gKabylakeFspPkgTokenSpaceGuid.PchWriteProtectionEnable    | 0x0318 | 0x05 | { 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH Flash Protection Ranges Read Enble} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{Read is blocked by hardware.}
  gKabylakeFspPkgTokenSpaceGuid.PchReadProtectionEnable     | 0x031D | 0x05 | { 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH Protect Range Limit} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Left shifted address by 12 bits with address bits 11:0 are assumed to be FFFh for limit comparison.}
  gKabylakeFspPkgTokenSpaceGuid.PchProtectedRangeLimit      | 0x0322 | 0x0A | { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }

  # !BSF NAME:{PCH Protect Range Base} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Left shifted address by 12 bits with address bits 11:0 are assumed to be 0.}
  gKabylakeFspPkgTokenSpaceGuid.PchProtectedRangeBase       | 0x032C | 0x0A | { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }

  # !BSF NAME:{Enable Pme} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable Azalia wake-on-ring.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaPme                   | 0x0336 | 0x01 | 0x00

  # !BSF NAME:{IO Buffer Voltage} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{I/O Buffer Voltage Mode Select: 0: 3.3V, 1: 1.8V.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaIoBufferVoltage       | 0x0337 | 0x01 | 0x00

  # !BSF NAME:{VC Type} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Virtual Channel Type Select: 0: VC0, 1: VC1.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaVcType                | 0x0338 | 0x01 | 0x00

  # !BSF NAME:{HD Audio Link Frequency} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{HDA Link Freq (PCH_HDAUDIO_LINK_FREQUENCY enum): 0: 6MHz, , 1: 12MHz, 2: 24MHz.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaLinkFrequency         | 0x0339 | 0x01 | 0x02

  # !BSF NAME:{iDisp-Link Frequency} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{iDisp-Link Freq (PCH_HDAUDIO_LINK_FREQUENCY enum): 4: 96MHz, 3: 48MHz.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaIDispLinkFrequency    | 0x033A | 0x01 | 0x04

  # !BSF NAME:{iDisp-Link T-mode} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{iDisp-Link T-Mode (PCH_HDAUDIO_IDISP_TMODE enum): 0: 2T, 1: 1T.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaIDispLinkTmode        | 0x033B | 0x01 | 0x00

  # !BSF NAME:{Universal Audio Architecture compliance for DSP enabled system} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Not-UAA Compliant (Intel SST driver supported only), 1: UAA Compliant (HDA Inbox driver or SST driver supported).}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaDspUaaCompliance      | 0x033C | 0x01 | 0x00

  # !BSF NAME:{iDisplay Audio Codec disconnection} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Not disconnected, enumerable, 1: Disconnected SDI, not enumerable.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaIDispCodecDisconnect  | 0x033D | 0x01 | 0x00

  # !BSF NAME:{DSP DMIC Select (PCH_HDAUDIO_DMIC_TYPE enum)} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{0: Disable; 1: 2ch array; 2: 4ch array; 3: 1ch array.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaDspEndpointDmic       | 0x033E | 0x01 | 0x02

  # !BSF NAME:{DSP Bluetooth enablement} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaDspEndpointBluetooth  | 0x033F | 0x01 | 0x00

  # !BSF NAME:{Bitmask of supported DSP features} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{[BIT0] - WoV; [BIT1] - BT Sideband; [BIT2] - Codec VAD; [BIT5] - BT Intel HFP; [BIT6] - BT Intel A2DP; [BIT7] - DSP based speech pre-processing disabled; [BIT8] - 0: Intel WoV, 1: Windows Voice Activation.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaDspFeatureMask        | 0x0340 | 0x04 | 0x00000000

  # !BSF NAME:{Bitmask of supported DSP Pre/Post-Processing Modules} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Deprecated: Specific pre/post-processing module bit position must be coherent with the ACPI implementation: \_SB.PCI0.HDAS._DSM Function 3: Query Pre/Post Processing Module Support.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaDspPpModuleMask       | 0x0344 | 0x04 | 0x00000000

  # !BSF NAME:{DSP I2S enablement} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaDspEndpointI2s        | 0x0348 | 0x01 | 0x00

  # !BSF NAME:{Enable PCH Io Apic} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set to 1 if BDF value is valid.}
  gKabylakeFspPkgTokenSpaceGuid.PchIoApicBdfValid           | 0x0349 | 0x01 | 0x00

  # !BSF NAME:{PCH Io Apic Bus Number} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Bus/Device/Function used as Requestor / Completer ID. Default is 0xF0.}
  gKabylakeFspPkgTokenSpaceGuid.PchIoApicBusNumber          | 0x034A | 0x01 | 0xF0

  # !BSF NAME:{PCH Io Apic Device Number} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Bus/Device/Function used as Requestor / Completer ID. Default is 0x1F.}
  gKabylakeFspPkgTokenSpaceGuid.PchIoApicDeviceNumber       | 0x034B | 0x01 | 0x1F

  # !BSF NAME:{PCH Io Apic Function Number} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Bus/Device/Function used as Requestor / Completer ID. Default is 0x00.}
  gKabylakeFspPkgTokenSpaceGuid.PchIoApicFunctionNumber     | 0x034C | 0x01 | 0x00

  # !BSF NAME:{Enable PCH Io Apic Entry 24-119} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIoApicEntry24_119        | 0x034D | 0x01 | 0x01

  # !BSF NAME:{PCH Io Apic ID} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{This member determines IOAPIC ID. Default is 0x02.}
  gKabylakeFspPkgTokenSpaceGuid.PchIoApicId                 | 0x034E | 0x01 | 0x02

  # !BSF NAME:{PCH Io Apic Range Select} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Define address bits 19:12 for the IOxAPIC range. Default is 0.}
  gKabylakeFspPkgTokenSpaceGuid.PchIoApicRangeSelect        | 0x034F | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH SPI GPIO pins assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshSpiGpioAssign         | 0x0350 | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH UART0 GPIO pins assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshUart0GpioAssign       | 0x0351 | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH UART1 GPIO pins assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshUart1GpioAssign       | 0x0352 | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH I2C0 GPIO pins assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshI2c0GpioAssign        | 0x0353 | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH I2C1 GPIO pins assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshI2c1GpioAssign        | 0x0354 | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH I2C2 GPIO pins assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshI2c2GpioAssign        | 0x0355 | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH GP_0 GPIO pin assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshGp0GpioAssign         | 0x0356 | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH GP_1 GPIO pin assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshGp1GpioAssign         | 0x0357 | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH GP_2 GPIO pin assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshGp2GpioAssign         | 0x0358 | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH GP_3 GPIO pin assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshGp3GpioAssign         | 0x0359 | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH GP_4 GPIO pin assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshGp4GpioAssign         | 0x035A | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH GP_5 GPIO pin assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshGp5GpioAssign         | 0x035B | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH GP_6 GPIO pin assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshGp6GpioAssign         | 0x035C | 0x01 | 0x00

  # !BSF NAME:{Enable PCH ISH GP_7 GPIO pin assigned} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshGp7GpioAssign         | 0x035D | 0x01 | 0x00

  # !BSF NAME:{PCH ISH PDT Unlock Msg} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: False; 1: True.}
  gKabylakeFspPkgTokenSpaceGuid.PchIshPdtUnlock             | 0x035E | 0x01 | 0x00

  # !BSF NAME:{Enable PCH Lan LTR capabilty of PCH internal LAN} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchLanLtrEnable             | 0x035F | 0x01 | 0x01

  # !BSF NAME:{Enable PCH Lan use CLKREQ for GbE power management} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchLanK1OffEnable           | 0x0360 | 0x01 | 0x00

  # !BSF NAME:{Indicate whether dedicated CLKREQ# is supported} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchLanClkReqSupported       | 0x0361 | 0x01 | 0x00

  # !BSF NAME:{CLKREQ# used by GbE} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Valid if ClkReqSupported is TRUE.}
  gKabylakeFspPkgTokenSpaceGuid.PchLanClkReqNumber          | 0x0362 | 0x01 | 0x00

  # !BSF NAME:{Enable LOCKDOWN BIOS LOCK} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable the BIOS Lock feature and set EISS bit (D31:F5:RegDCh[5]) for the BIOS region protection.}
  gKabylakeFspPkgTokenSpaceGuid.PchLockDownBiosLock         | 0x0363 | 0x01 | 0x00

  # !BSF NAME:{Enable LOCKDOWN SPI Eiss} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable InSMM.STS (EISS) in SPI.}
  gKabylakeFspPkgTokenSpaceGuid.PchLockDownSpiEiss          | 0x0364 | 0x01 | 0x01

  # !BSF NAME:{PCH Compatibility Revision ID} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This member describes whether or not the CRID feature of PCH should be enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PchCrid                     | 0x0365 | 0x01 | 0x00

  # !BSF NAME:{PCH Sub system vendor ID} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Default Subsystem Vendor ID of the PCH devices. Default is 0x8086.}
  gKabylakeFspPkgTokenSpaceGuid.PchSubSystemVendorId        | 0x0366 | 0x02 | 0x8086

  # !BSF NAME:{PCH Sub system ID} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Default Subsystem ID of the PCH devices. Default is 0x7270.}
  gKabylakeFspPkgTokenSpaceGuid.PchSubSystemId              | 0x0368 | 0x02 | 0x7270

  # !BSF NAME:{PCH Legacy IO Low Latency Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{todo}
  gKabylakeFspPkgTokenSpaceGuid.PchLegacyIoLowLatency       | 0x036A | 0x01 | 0x00

  # !BSF NAME:{Enable PCIE RP HotPlug} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the root port is hot plug available.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpHotPlug               | 0x0370 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCIE RP Pm Sci} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the root port power manager SCI is enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpPmSci                 | 0x0388 | 0x18 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{Enable PCIE RP Ext Sync} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the extended synch is enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpExtSync               | 0x03A0 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCIE RP Transmitter Half Swing} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Transmitter Half Swing is enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpTransmitterHalfSwing  | 0x03B8 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCIE RP Clk Req Detect} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Probe CLKREQ# signal before enabling CLKREQ# based power management.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpClkReqDetect          | 0x03D0 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Advanced Error Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Advanced Error Reporting is enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpAdvancedErrorReporting   | 0x03E8 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Unsupported Request Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Unsupported Request Report is enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpUnsupportedRequestReport | 0x0400 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Fatal Error Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Fatal Error Report is enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpFatalErrorReport      | 0x0418 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP No Fatal Error Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the No Fatal Error Report is enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpNoFatalErrorReport    | 0x0430 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Correctable Error Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Correctable Error Report is enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpCorrectableErrorReport   | 0x0448 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP System Error On Fatal Error} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the System Error on Fatal Error is enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpSystemErrorOnFatalError  | 0x0460 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP System Error On Non Fatal Error} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the System Error on Non Fatal Error is enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpSystemErrorOnNonFatalError | 0x0478 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP System Error On Correctable Error} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the System Error on Correctable Error is enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpSystemErrorOnCorrectableError | 0x0490 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Max Payload} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Max Payload Size supported, Default 128B, see enum PCH_PCIE_MAX_PAYLOAD.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpMaxPayload            | 0x04A8 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Device Reset Pad Active High} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicated whether PERST# is active 0: Low; 1: High, See: DeviceResetPad.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpDeviceResetPadActiveHigh | 0x04C0 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Pcie Speed} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Determines each PCIE Port speed capability. 0: Auto; 1: Gen1; 2: Gen2; 3: Gen3 (see: PCH_PCIE_SPEED).}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpPcieSpeed             | 0x04D8 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Gen3 Equalization Phase Method} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCIe Gen3 Eq Ph3 Method (see PCH_PCIE_EQ_METHOD). 0: Default; 2: Software Search; 4: Fixed Coeficients.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpGen3EqPh3Method       | 0x04F0 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Physical Slot Number} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicates the slot number for the root port. Default is the value as root port index.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpPhysicalSlotNumber    | 0x0508 | 0x18 | { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 }

  # !BSF NAME:{PCIE RP Completion Timeout} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{The root port completion timeout(see: PCH_PCIE_COMPLETION_TIMEOUT). Default is PchPcieCompletionTO_Default.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpCompletionTimeout     | 0x0520 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Device Reset Pad} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{The PCH pin assigned to device PERST# signal if available, zero otherwise.  See also DeviceResetPadActiveHigh.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpDeviceResetPad        | 0x0538 | 0x60 | { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }

  # !BSF NAME:{PCIE RP Aspm} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{The ASPM configuration of the root port (see: PCH_PCIE_ASPM_CONTROL). Default is PchPcieAspmAutoConfig.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpAspm                  | 0x0598 | 0x18 | { 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 }

  # !BSF NAME:{PCIE RP L1 Substates} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{The L1 Substates configuration of the root port (see: PCH_PCIE_L1SUBSTATES_CONTROL). Default is PchPcieL1SubstatesL1_1_2.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpL1Substates           | 0x05B0 | 0x18 | { 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 }

  # !BSF NAME:{PCIE RP Ltr Enable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting Mechanism.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpLtrEnable             | 0x05C8 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Ltr Config Lock} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpLtrConfigLock         | 0x05E0 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE Eq Ph3 Lane Param Cm} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH_PCIE_EQ_LANE_PARAM. Coefficient C-1.}
  gKabylakeFspPkgTokenSpaceGuid.PcieEqPh3LaneParamCm        | 0x05F8 | 0x18 | { 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 }

  # !BSF NAME:{PCIE Eq Ph3 Lane Param Cp} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH_PCIE_EQ_LANE_PARAM. Coefficient C+1.}
  gKabylakeFspPkgTokenSpaceGuid.PcieEqPh3LaneParamCp        | 0x0610 | 0x18 | { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE Sw Eq CoeffList Cm} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCH_PCIE_EQ_PARAM. Coefficient C-1.}
  gKabylakeFspPkgTokenSpaceGuid.PcieSwEqCoeffListCm         | 0x0628 | 0x05 | { 0x06, 0x04, 0x08, 0x02, 0x0A }

  # !BSF NAME:{PCIE Sw Eq CoeffList Cp} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCH_PCIE_EQ_PARAM. Coefficient C+1.}
  gKabylakeFspPkgTokenSpaceGuid.PcieSwEqCoeffListCp         | 0x062D | 0x05 | { 0x02, 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE Disable RootPort Clock Gating} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Describes whether the PCI Express Clock Gating for each root port is enabled by platform modules. 0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PcieDisableRootPortClockGating | 0x0632 | 0x01 | 0x00

  # !BSF NAME:{PCIE Enable Peer Memory Write} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This member describes whether Peer Memory Writes are enabled on the platform.}
  gKabylakeFspPkgTokenSpaceGuid.PcieEnablePeerMemoryWrite   | 0x0633 | 0x01 | 0x00

  # !BSF NAME:{PCIE Allow No Ltr Icc PLL Shutdown} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Allows BIOS to control ICC PLL Shutdown by determining PCIe devices are LTR capable or leaving untouched.}
  gKabylakeFspPkgTokenSpaceGuid.PcieAllowNoLtrIccPllShutdown   | 0x0634 | 0x01 | 0x00

  # !BSF NAME:{PCIE Compliance Test Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Compliance Test Mode shall be enabled when using Compliance Load Board.}
  gKabylakeFspPkgTokenSpaceGuid.PcieComplianceTestMode      | 0x0635 | 0x01 | 0x00

  # !BSF NAME:{PCIE Rp Detect Timeout Ms} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Will wait for link to exit Detect state for enabled ports before assuming there is no device and potentially disabling the port.}
  gKabylakeFspPkgTokenSpaceGuid.PcieDetectTimeoutMs         | 0x0636 | 0x02 | 0x0000

  # !BSF NAME:{PCIE Rp Function Swap} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Allows BIOS to use root port function number swapping when root port of function 0 is disabled.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpFunctionSwap          | 0x0638 | 0x01 | 0x01

  # !BSF NAME:{PCH Pm PME_B0_S5_DIS} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When cleared (default), wake events from PME_B0_STS are allowed in S5 if PME_B0_EN = 1.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmPmeB0S5Dis             | 0x0639 | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Slp S0 Voltage Margining Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Indicates platform has support for VCCPrim_Core Voltage Margining in SLP_S0# asserted state.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmSlpS0VmEnable          | 0x063A | 0x01 | 0x01

  # !BSF NAME:{PCH Pm Wol Enable Override} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Corresponds to the WOL Enable Override bit in the General PM Configuration B (GEN_PMCON_B) register.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmWolEnableOverride      | 0x0640 | 0x01 | 0x01

  # !BSF NAME:{PCH Pm Pcie Wake From DeepSx} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Determine if enable PCIe to wake from deep Sx.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmPcieWakeFromDeepSx     | 0x0641 | 0x01 | 0x00

  # !BSF NAME:{PCH Pm WoW lan Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Determine if WLAN wake from Sx, corresponds to the HOST_WLAN_PP_EN bit in the PWRM_CFG3 register.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmWoWlanEnable           | 0x0642 | 0x01 | 0x00

  # !BSF NAME:{PCH Pm WoW lan DeepSx Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Determine if WLAN wake from DeepSx, corresponds to the DSX_WLAN_PP_EN bit in the PWRM_CFG3 register.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmWoWlanDeepSxEnable     | 0x0643 | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Lan Wake From DeepSx} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Determine if enable LAN to wake from deep Sx.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmLanWakeFromDeepSx      | 0x0644 | 0x01 | 0x01

  # !BSF NAME:{PCH Pm Deep Sx Pol} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Deep Sx Policy.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmDeepSxPol              | 0x0645 | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Slp S3 Min Assert} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{SLP_S3 Minimum Assertion Width Policy. Default is PchSlpS350ms.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmSlpS3MinAssert         | 0x0646 | 0x01 | 0x02

  # !BSF NAME:{PCH Pm Slp S4 Min Assert} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{SLP_S4 Minimum Assertion Width Policy. Default is PchSlpS44s.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmSlpS4MinAssert         | 0x0647 | 0x01 | 0x04

  # !BSF NAME:{PCH Pm Slp Sus Min Assert} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{SLP_SUS Minimum Assertion Width Policy. Default is PchSlpSus4s.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmSlpSusMinAssert        | 0x0648 | 0x01 | 0x03

  # !BSF NAME:{PCH Pm Slp A Min Assert} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{SLP_A Minimum Assertion Width Policy. Default is PchSlpA2s.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmSlpAMinAssert          | 0x0649 | 0x01 | 0x03

  # !BSF NAME:{PCH Pm Lpc Clock Run} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This member describes whether or not the LPC ClockRun feature of PCH should be enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmLpcClockRun            | 0x0650 | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Slp Strch Sus Up} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable SLP_X Stretching After SUS Well Power Up.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmSlpStrchSusUp          | 0x0651 | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Slp Lan Low Dc} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable SLP_LAN# Low on DC Power.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmSlpLanLowDc            | 0x0652 | 0x01 | 0x01

  # !BSF NAME:{PCH Pm Pwr Btn Override Period} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{PCH power button override period. 000b-4s, 001b-6s, 010b-8s, 011b-10s, 100b-12s, 101b-14s.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmPwrBtnOverridePeriod   | 0x0653 | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Disable Dsx Ac Present Pulldown} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When Disable, PCH will internal pull down AC_PRESENT in deep SX and during G3 exit.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmDisableDsxAcPresentPulldown  | 0x0654 | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Capsule Reset Type} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Deprecated: Determines type of reset issued during UpdateCapsule(). Always Warm reset.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmCapsuleResetType       | 0x0655 | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Disable Native Power Button} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Power button native mode disable.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmDisableNativePowerButton  | 0x0656 | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Slp S0 Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Indicates whether SLP_S0# is to be asserted when PCH reaches idle state.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmSlpS0Enable            | 0x0657 | 0x01 | 0x01

  # !BSF NAME:{PCH Pm ME_WAKE_STS} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Clear the ME_WAKE_STS bit in the Power and Reset Status (PRSTS) register.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmMeWakeSts              | 0x0658 | 0x01 | 0x01

  # !BSF NAME:{PCH Pm WOL_OVR_WK_STS} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Clear the WOL_OVR_WK_STS bit in the Power and Reset Status (PRSTS) register.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmWolOvrWkSts            | 0x0659 | 0x01 | 0x01

  # !BSF NAME:{PCH Pm Reset Power Cycle Duration} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Could be customized in the unit of second. Please refer to EDS for all support settings. 0 is default, 1 is 1 second, 2 is 2 seconds, ...}
  gKabylakeFspPkgTokenSpaceGuid.PchPmPwrCycDur              | 0x065A | 0x01 | 0x00

  # !BSF NAME:{PCH Port 61h Config Enable/Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Used for the emulation feature for Port61h read. The port is trapped and the SMI handler will toggle bit4 according to the handler's internal state.}
  gKabylakeFspPkgTokenSpaceGuid.PchPort61hEnable            | 0x065C | 0x01 | 0x00

  # !BSF NAME:{PCH Sata Pwr Opt Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{SATA Power Optimizer on PCH side.}
  gKabylakeFspPkgTokenSpaceGuid.SataPwrOptEnable            | 0x065D | 0x01 | 0x00

  # !BSF NAME:{PCH Sata eSATA Speed Limit} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When enabled, BIOS will configure the PxSCTL.SPD to 2 to limit the eSATA port speed.}
  gKabylakeFspPkgTokenSpaceGuid.EsataSpeedLimit             | 0x065E | 0x01 | 0x00

  # !BSF NAME:{PCH Sata Speed Limit} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Indicates the maximum speed the SATA controller can support 0h: PchSataSpeedDefault.}
  gKabylakeFspPkgTokenSpaceGuid.SataSpeedLimit              | 0x065F | 0x01 | 0x00

  # !BSF NAME:{Enable SATA Port HotPlug} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable SATA Port HotPlug.}
  gKabylakeFspPkgTokenSpaceGuid.SataPortsHotPlug            | 0x0660 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port Interlock Sw} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable SATA Port Interlock Sw.}
  gKabylakeFspPkgTokenSpaceGuid.SataPortsInterlockSw        | 0x0668 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port External} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable SATA Port External.}
  gKabylakeFspPkgTokenSpaceGuid.SataPortsExternal           | 0x0670 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port SpinUp} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable the COMRESET initialization Sequence to the device.}
  gKabylakeFspPkgTokenSpaceGuid.SataPortsSpinUp             | 0x0678 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port Solid State Drive} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: HDD; 1: SSD.}
  gKabylakeFspPkgTokenSpaceGuid.SataPortsSolidStateDrive    | 0x0680 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port Enable Dito Config} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable DEVSLP Idle Timeout settings (DmVal, DitoVal).}
  gKabylakeFspPkgTokenSpaceGuid.SataPortsEnableDitoConfig   | 0x0688 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port DmVal} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{DITO multiplier. Default is 15.}
  gKabylakeFspPkgTokenSpaceGuid.SataPortsDmVal              | 0x0690 | 0x08 | { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F}

  # !BSF NAME:{Enable SATA Port DmVal} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{DEVSLP Idle Timeout (DITO), Default is 625.}
  gKabylakeFspPkgTokenSpaceGuid.SataPortsDitoVal            | 0x0698 | 0x10 | { 625, 625, 625, 625, 625, 625, 625, 625}

  # !BSF NAME:{Enable SATA Port ZpOdd} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Support zero power ODD.}
  gKabylakeFspPkgTokenSpaceGuid.SataPortsZpOdd              | 0x06A8 | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{PCH Sata Rst Raid Alternate Id} TYPE:{Combo} OPTION:{0:Client, 1:Alternate, 2:Server}
  # !BSF HELP:{Enable RAID Alternate ID.}
  gKabylakeFspPkgTokenSpaceGuid.SataRstRaidAlternateId      | 0x06B0 | 0x01 | 0x00

  # !BSF NAME:{PCH Sata Rst Raid0} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{RAID0.}
  gKabylakeFspPkgTokenSpaceGuid.SataRstRaid0                | 0x06B1 | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Raid1} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{RAID1.}
  gKabylakeFspPkgTokenSpaceGuid.SataRstRaid1                | 0x06B2 | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Raid10} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{RAID10.}
  gKabylakeFspPkgTokenSpaceGuid.SataRstRaid10               | 0x06B3 | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Raid5} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{RAID5.}
  gKabylakeFspPkgTokenSpaceGuid.SataRstRaid5                | 0x06B4 | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Irrt} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Intel Rapid Recovery Technology.}
  gKabylakeFspPkgTokenSpaceGuid.SataRstIrrt                 | 0x06B5 | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Orom Ui Banner} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{OROM UI and BANNER.}
  gKabylakeFspPkgTokenSpaceGuid.SataRstOromUiBanner         | 0x06B6 | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Orom Ui Delay} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{00b: 2 secs; 01b: 4 secs; 10b: 6 secs; 11: 8 secs (see: PCH_SATA_OROM_DELAY).}
  gKabylakeFspPkgTokenSpaceGuid.SataRstOromUiDelay          | 0x06B7 | 0x01 | 0x00

  # !BSF NAME:{PCH Sata Rst Hdd Unlock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Indicates that the HDD password unlock in the OS is enabled.}
  gKabylakeFspPkgTokenSpaceGuid.SataRstHddUnlock            | 0x06B8 | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Led Locate} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Indicates that the LED/SGPIO hardware is attached and ping to locate feature is enabled on the OS.}
  gKabylakeFspPkgTokenSpaceGuid.SataRstLedLocate            | 0x06B9 | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Irrt Only} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Allow only IRRT drives to span internal and external ports.}
  gKabylakeFspPkgTokenSpaceGuid.SataRstIrrtOnly             | 0x06BA | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Smart Storage} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{RST Smart Storage caching Bit.}
  gKabylakeFspPkgTokenSpaceGuid.SataRstSmartStorage         | 0x06BB | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Pcie Storage Remap enable} TYPE:{EditNum, HEX, (0x00,0xFFFFFF)}
  # !BSF HELP:{Enable Intel RST for PCIe Storage remapping.}
  gKabylakeFspPkgTokenSpaceGuid.SataRstPcieEnable           | 0x06BC | 0x03 | { 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH Sata Rst Pcie Storage Port} TYPE:{EditNum, HEX, (0x00,0xFFFFFF)}
  # !BSF HELP:{Intel RST for PCIe Storage remapping - PCIe Port Selection (1-based, 0 = autodetect).}
  gKabylakeFspPkgTokenSpaceGuid.SataRstPcieStoragePort      | 0x06BF | 0x03 | { 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH Sata Rst Pcie Device Reset Delay} TYPE:{EditNum, HEX, (0x00,0xFFFFFF)}
  # !BSF HELP:{PCIe Storage Device Reset Delay in milliseconds. Default value is 100ms}
  gKabylakeFspPkgTokenSpaceGuid.SataRstPcieDeviceResetDelay | 0x06C2 | 0x03 | { 100, 100, 100 }


  # !BSF NAME:{Enable eMMC HS400 Training} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Determine if HS400 Training is required.}
  gKabylakeFspPkgTokenSpaceGuid.PchScsEmmcHs400TuningRequired  | 0x06C5 | 0x01 | 0x00

  # !BSF NAME:{Set HS400 Tuning Data Valid} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set if HS400 Tuning Data Valid.}
  gKabylakeFspPkgTokenSpaceGuid.PchScsEmmcHs400DllDataValid | 0x06C6 | 0x01 | 0x00

  # !BSF NAME:{Rx Strobe Delay Control} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Rx Strobe Delay Control - Rx Strobe Delay DLL 1 (HS400 Mode).}
  gKabylakeFspPkgTokenSpaceGuid.PchScsEmmcHs400RxStrobeDll1 | 0x06C7 | 0x01 | 0x00

  # !BSF NAME:{Tx Data Delay Control} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Tx Data Delay Control 1 - Tx Data Delay (HS400 Mode).}
  gKabylakeFspPkgTokenSpaceGuid.PchScsEmmcHs400TxDataDll    | 0x06C8 | 0x01 | 0x00

  # !BSF NAME:{I/O Driver Strength} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{I/O driver strength: 0 - 33 Ohm, 1 - 40 Ohm, 2 - 50 Ohm.}
  gKabylakeFspPkgTokenSpaceGuid.PchScsEmmcHs400DriverStrength  | 0x06C9 | 0x01 | 0x00

  # !BSF NAME:{Enable Pch Serial IO GPIO} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Determines if enable Serial IO GPIO.}
  gKabylakeFspPkgTokenSpaceGuid.SerialIoGpio                | 0x06CA | 0x01 | 0x01

  # !BSF NAME:{IO voltage for I2C controllers} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFF)}
  # !BSF HELP:{Selects the IO voltage for I2C controllers, 0: PchSerialIoIs33V, 1: PchSerialIoIs18V. Note: I2C 2/3/4/5 does not support 3.3V (only 1.8V), due to GPIO GPP_F limitation}
  gKabylakeFspPkgTokenSpaceGuid.SerialIoI2cVoltage          | 0x06CB | 0x06 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{SPI ChipSelect signal polarity} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Selects SPI ChipSelect signal polarity.}
  gKabylakeFspPkgTokenSpaceGuid.SerialIoSpiCsPolarity       | 0x06D1 | 0x02 | { 0x00, 0x00 }

  # !BSF NAME:{Enables UART hardware flow control, CTS and RTS lines} TYPE:{EditNum, HEX, (0x00,0xFFFFFF)}
  # !BSF HELP:{Enables UART hardware flow control, CTS and RTS linesh.}
  gKabylakeFspPkgTokenSpaceGuid.SerialIoUartHwFlowCtrl      | 0x06D3 | 0x03 | { 0x00, 0x00, 0x00 }

  # !BSF NAME:{UART Number For Debug Purpose} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{UART number for debug purpose. 0:UART0, 1: UART1, 2:UART2.}
  gKabylakeFspPkgTokenSpaceGuid.SerialIoDebugUartNumber     | 0x06D6 | 0x01 | 0x02

  # !BSF NAME:{Enable Debug UART Controller} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Enable debug UART controller after post.}
  gKabylakeFspPkgTokenSpaceGuid.SerialIoEnableDebugUartAfterPost   | 0x06D7 | 0x01 | 0x01

  # !BSF NAME:{Enable Serial IRQ} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Determines if enable Serial IRQ.}
  gKabylakeFspPkgTokenSpaceGuid.PchSirqEnable               | 0x06D8 | 0x01 | 0x01

  # !BSF NAME:{Serial IRQ Mode Select} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Serial IRQ Mode Select, 0: quiet mode, 1: continuous mode.}
  gKabylakeFspPkgTokenSpaceGuid.PchSirqMode                 | 0x06D9 | 0x01 | 0x00

  # !BSF NAME:{Start Frame Pulse Width} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Start Frame Pulse Width, 0: PchSfpw4Clk, 1: PchSfpw6Clk, 2: PchSfpw8Clk.}
  gKabylakeFspPkgTokenSpaceGuid.PchStartFramePulse          | 0x06DA | 0x01 | 0x00

  # !BSF NAME:{Enable Thermal Device} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable Thermal Device.}
  gKabylakeFspPkgTokenSpaceGuid.PchThermalDeviceEnable      | 0x06DB | 0x01 | 0x01

  # !BSF NAME:{Thermal Throttling Custimized T0Level Value} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Custimized T0Level value.}
  gKabylakeFspPkgTokenSpaceGuid.PchT0Level                  | 0x06DC | 0x02 | 0x0000

  # !BSF NAME:{Thermal Throttling Custimized T1Level Value} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Custimized T1Level value.}
  gKabylakeFspPkgTokenSpaceGuid.PchT1Level                  | 0x06DE | 0x02 | 0x0000

  # !BSF NAME:{Thermal Throttling Custimized T2Level Value} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Custimized T2Level value.}
  gKabylakeFspPkgTokenSpaceGuid.PchT2Level                  | 0x06E0 | 0x02 | 0x0000

  # !BSF NAME:{Thermal Device SMI Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This locks down SMI Enable on Alert Thermal Sensor Trip.}
  gKabylakeFspPkgTokenSpaceGuid.PchTsmicLock                | 0x06E2 | 0x01 | 0x01

  # !BSF NAME:{Enable The Thermal Throttle} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable the thermal throttle function.}
  gKabylakeFspPkgTokenSpaceGuid.PchTTEnable                 | 0x06E3 | 0x01 | 0x00

  # !BSF NAME:{PMSync State 13} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When set to 1 and the programmed GPIO pin is a 1, then PMSync state 13 will force at least T2 state.}
  gKabylakeFspPkgTokenSpaceGuid.PchTTState13Enable          | 0x06E4 | 0x01 | 0x00

  # !BSF NAME:{Thermal Throttle Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Thermal Throttle Lock.}
  gKabylakeFspPkgTokenSpaceGuid.PchTTLock                   | 0x06E5 | 0x01 | 0x00

  # !BSF NAME:{Thermal Throttling Suggested Setting} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Thermal Throttling Suggested Setting.}
  gKabylakeFspPkgTokenSpaceGuid.TTSuggestedSetting          | 0x06E6 | 0x01 | 0x01

  # !BSF NAME:{Enable PCH Cross Throttling} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable PCH Cross Throttling}
  gKabylakeFspPkgTokenSpaceGuid.TTCrossThrottling           | 0x06E7 | 0x01 | 0x01

  # !BSF NAME:{DMI Thermal Sensor Autonomous Width Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{DMI Thermal Sensor Autonomous Width Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchDmiTsawEn                | 0x06E8 | 0x01 | 0x00

  # !BSF NAME:{DMI Thermal Sensor Suggested Setting} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{DMT thermal sensor suggested representative values.}
  gKabylakeFspPkgTokenSpaceGuid.DmiSuggestedSetting         | 0x06E9 | 0x01 | 0x01

  # !BSF NAME:{Thermal Sensor 0 Target Width} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Thermal Sensor 0 Target Width.}
  gKabylakeFspPkgTokenSpaceGuid.DmiTS0TW                    | 0x06EA | 0x01 | 0x00

  # !BSF NAME:{Thermal Sensor 1 Target Width} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Thermal Sensor 1 Target Width.}
  gKabylakeFspPkgTokenSpaceGuid.DmiTS1TW                    | 0x06EB | 0x01 | 0x00

  # !BSF NAME:{Thermal Sensor 2 Target Width} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Thermal Sensor 2 Target Width.}
  gKabylakeFspPkgTokenSpaceGuid.DmiTS2TW                    | 0x06EC | 0x01 | 0x00

  # !BSF NAME:{Thermal Sensor 3 Target Width} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Thermal Sensor 3 Target Width.}
  gKabylakeFspPkgTokenSpaceGuid.DmiTS3TW                    | 0x06ED | 0x01 | 0x00

  # !BSF NAME:{Port 0 T1 Multipler} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 0 T1 Multipler.}
  gKabylakeFspPkgTokenSpaceGuid.SataP0T1M                   | 0x06EE | 0x01 | 0x01

  # !BSF NAME:{Port 0 T2 Multipler} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 0 T2 Multipler.}
  gKabylakeFspPkgTokenSpaceGuid.SataP0T2M                   | 0x06EF | 0x01 | 0x02

  # !BSF NAME:{Port 0 T3 Multipler} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 0 T3 Multipler.}
  gKabylakeFspPkgTokenSpaceGuid.SataP0T3M                   | 0x06F0 | 0x01 | 0x03

  # !BSF NAME:{Port 0 Tdispatch} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 0 Tdispatch.}
  gKabylakeFspPkgTokenSpaceGuid.SataP0TDisp                 | 0x06F1 | 0x01 | 0x00

  # !BSF NAME:{Port 1 T1 Multipler} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 1 T1 Multipler.}
  gKabylakeFspPkgTokenSpaceGuid.SataP1T1M                   | 0x06F2 | 0x01 | 0x01

  # !BSF NAME:{Port 1 T2 Multipler} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 1 T2 Multipler.}
  gKabylakeFspPkgTokenSpaceGuid.SataP1T2M                   | 0x06F3 | 0x01 | 0x02

  # !BSF NAME:{Port 1 T3 Multipler} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 1 T3 Multipler.}
  gKabylakeFspPkgTokenSpaceGuid.SataP1T3M                   | 0x06F4 | 0x01 | 0x03

  # !BSF NAME:{Port 1 Tdispatch} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 1 Tdispatch.}
  gKabylakeFspPkgTokenSpaceGuid.SataP1TDisp                 | 0x06F5 | 0x01 | 0x00

  # !BSF NAME:{Port 0 Tinactive} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 0 Tinactive.}
  gKabylakeFspPkgTokenSpaceGuid.SataP0Tinact                | 0x06F6 | 0x01 | 0x00

  # !BSF NAME:{Port 0 Alternate Fast Init Tdispatch} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Port 0 Alternate Fast Init Tdispatch.}
  gKabylakeFspPkgTokenSpaceGuid.SataP0TDispFinit            | 0x06F7 | 0x01 | 0x00

  # !BSF NAME:{Port 1 Tinactive} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 1 Tinactive.}
  gKabylakeFspPkgTokenSpaceGuid.SataP1Tinact                | 0x06F8 | 0x01 | 0x00

  # !BSF NAME:{Port 1 Alternate Fast Init Tdispatch} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Port 1 Alternate Fast Init Tdispatch.}
  gKabylakeFspPkgTokenSpaceGuid.SataP1TDispFinit            | 0x06F9 | 0x01 | 0x00

  # !BSF NAME:{Sata Thermal Throttling Suggested Setting} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Sata Thermal Throttling Suggested Setting.}
  gKabylakeFspPkgTokenSpaceGuid.SataThermalSuggestedSetting | 0x06FA | 0x01 | 0x01

  # !BSF NAME:{Enable Memory Thermal Throttling} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable Memory Thermal Throttling.}
  gKabylakeFspPkgTokenSpaceGuid.PchMemoryThrottlingEnable   | 0x06FB | 0x01 | 0x00

  # !BSF NAME:{Memory Thermal Throttling} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Enable Memory Thermal Throttling.}
  gKabylakeFspPkgTokenSpaceGuid.PchMemoryPmsyncEnable       | 0x06FC | 0x02 | { 0x00, 0x00 }

  # !BSF NAME:{Enable Memory Thermal Throttling} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Enable Memory Thermal Throttling.}
  gKabylakeFspPkgTokenSpaceGuid.PchMemoryC0TransmitEnable   | 0x06FE | 0x02 | { 0x00, 0x00 }

  # !BSF NAME:{Enable Memory Thermal Throttling} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Enable Memory Thermal Throttling.}
  gKabylakeFspPkgTokenSpaceGuid.PchMemoryPinSelection       | 0x0700 | 0x02 | { 0x00, 0x00 }

  # !BSF NAME:{Thermal Device Temperature} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Decides the temperature.}
  gKabylakeFspPkgTokenSpaceGuid.PchTemperatureHotLevel      | 0x0702 | 0x02 | 0x0000

  # !BSF NAME:{Disable XHCI Compliance Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This policy will disable XHCI compliance mode on all ports. Complicance Mode should be default enabled.}
  gKabylakeFspPkgTokenSpaceGuid.PchDisableComplianceMode    | 0x0704 | 0x01 | 0x00

  # !BSF NAME:{USB2 Port Over Current Pin} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Describe the specific over current pin number of USB 2.0 Port N.}
  gKabylakeFspPkgTokenSpaceGuid.Usb2OverCurrentPin          | 0x0705 | 0x10 | { 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x05, 0x05, 0x06, 0x06, 0x07, 0x07 }

  # !BSF NAME:{USB3 Port Over Current Pin} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Describe the specific over current pin number of USB 3.0 Port N.}
  gKabylakeFspPkgTokenSpaceGuid.Usb3OverCurrentPin          | 0x0715 | 0x0A | { 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04 }

  # !BSF NAME:{Enable 8254 Static Clock Gating in early POST time} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set 8254CGE=1 is required for C11 support. However, set 8254CGE=1 in POST time might fail to boot legacy OS which using 8254 timer. Make sure it won't break legacy OS boot before enabling this.}
  gKabylakeFspPkgTokenSpaceGuid.Early8254ClockGatingEnable  | 0x071F | 0x01 | 0x00

  # !BSF NAME:{PCH Sata Rst Optane Memory} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Optane Memory}
  gKabylakeFspPkgTokenSpaceGuid.SataRstOptaneMemory         | 0x0720 | 0x01 | 0x01

  # !BSF NAME:{PCH SATA RST CPU attached storage} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{RST CPU attached storage}
  gKabylakeFspPkgTokenSpaceGuid.SataRstCpuAttachedStorage   | 0x0721 | 0x01 | 0x01

  # !BSF NAME:{Hybrid Storage Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables support for Hybrid storage devices. 0: Disabled; 1: Dynamic Configuration. Default is 0: Disabled}
  gKabylakeFspPkgTokenSpaceGuid.HybridStorageMode         | 0x0722 | 0x01 | 0x00

  # !BSF NAME:{Pch PCIE device override table pointer} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{The PCIe device table is being used to override PCIe device ASPM settings. This is a pointer points to a 32bit address. And it's only used in PostMem phase. Please refer to PCH_PCIE_DEVICE_OVERRIDE structure for the table. Last entry VendorId must be 0.}
  gKabylakeFspPkgTokenSpaceGuid.PchPcieDeviceOverrideTablePtr  | 0x0724 | 0x04 | 0x00000000

  # !BSF NAME:{Enable TCO timer.} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When FALSE, it disables PCH ACPI timer, and stops TCO timer. NOTE: This will have huge power impact when it's enabled. If TCO timer is disabled, uCode ACPI timer emulation must be enabled, and WDAT table must not be exposed to the OS.}
  gKabylakeFspPkgTokenSpaceGuid.EnableTcoTimer              | 0x0728 | 0x01 | 0x00

  #
  #  PCH Silicon Offset End
  #

  ###########Security Production Policies Start ###########################################

  # !BSF NAME:{EcCmdProvisionEav} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Ephemeral Authorization Value default values. Provisions an ephemeral shared secret to the EC}
  gSkylakeFspPkgTokenSpaceGuid.EcCmdProvisionEav            | 0x0729 | 0x1 | 0xFF

  # !BSF NAME:{EcCmdLock} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{EcCmdLock default values. Locks Ephemeral Authorization Value sent previously}
  gSkylakeFspPkgTokenSpaceGuid.EcCmdLock                    | 0x072A | 0x1 | 0xFF

  # !BSF NAME:{SendEcCmd} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{SendEcCmd function pointer. \n @code typedef EFI_STATUS (EFIAPI *PLATFORM_SEND_EC_COMMAND) (IN EC_COMMAND_TYPE  EcCmdType, IN UINT8  EcCmd, IN UINT8  SendData, IN OUT UINT8  *ReceiveData); @endcode}
  gSkylakeFspPkgTokenSpaceGuid.SendEcCmd                    | 0x0730 | 0x8 | 0xFFFFFFFFFFFFFFFF

  # Bios Guard

  # !BSF NAME:{BgpdtHash[4]} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT64}
  # !BSF HELP:{BgpdtHash values}
  gSkylakeFspPkgTokenSpaceGuid.BgpdtHash                    | 0x0738 | 0x20 | {0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000}

  # !BSF NAME:{BiosGuardModulePtr} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{BiosGuardModulePtr default values}
  gSkylakeFspPkgTokenSpaceGuid.BiosGuardModulePtr           | 0x0758 | 0x8 | 0xFFFFFFFFFFFFFFFF

  # !BSF NAME:{BiosGuardAttr} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{BiosGuardAttr default values}
  gSkylakeFspPkgTokenSpaceGuid.BiosGuardAttr                | 0x0760 | 0x4 | 0xFFFFFFFF

  # SGX

  # !BSF NAME:{SgxSinitNvsData} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{SgxSinitNvsData default values}
  gSkylakeFspPkgTokenSpaceGuid.SgxSinitNvsData              | 0x0764 | 0x1 | 0xFF

  # !BSF NAME:{SgxEpoch0} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{SgxEpoch0 default values}
  #TODO: Just a place holder - feature owner to change the default value
  gSkylakeFspPkgTokenSpaceGuid.SgxEpoch0                    | 0x0768 | 0x8 | 0xFFFFFFFFFFFFFFFF

  # !BSF NAME:{SgxEpoch1} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{SgxEpoch1 default values}
  #TODO: Just a place holder - feature owner to change the default value
  gSkylakeFspPkgTokenSpaceGuid.SgxEpoch1                    | 0x0770 | 0x8 | 0xFFFFFFFFFFFFFFFF

  ###########Security Production Policies End ###########################################

  #
  # ME Post-Mem Production Block Start
  #
  # !BSF NAME:{Enable/Disable ME Unconfig on RTC clear} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable ME Unconfig On Rtc Clear, Disable: Disable ME Unconfig On Rtc Clear}
  gKabylakeFspPkgTokenSpaceGuid.MeUnconfigOnRtcClear        | 0x0778 | 0x01 | 0x01

  # !BSF NAME:{Check if MeUnconfigOnRtcClear is valid} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{The MeUnconfigOnRtcClear item could be not valid due to CMOS is clear.}
  gKabylakeFspPkgTokenSpaceGuid.MeUnconfigIsValid           | 0x0779 | 0x01 | 0x01
  #
  # ME Post-Mem Production Block End
  #

  # !BSF NAME:{Activates VR mailbox command for Intersil VR C-state issues.} TYPE:{EditNum, HEX, (0x0,0x7)}
  # !BSF HELP:{Intersil VR mailbox command. <b>0 - no mailbox command sent.</b>  1 - VR mailbox command sent for IA/GT rails only. 2 - VR mailbox command sent for IA/GT/SA rails.}
  gKabylakeFspPkgTokenSpaceGuid.IslVrCmd                    | 0x077A | 0x01 | 0x00

  # !HDR EMBED:{FSP_S_CONFIG:FspsConfig:END}
  gKabylakeFspPkgTokenSpaceGuid.ReservedFspsUpd             | 0x077B | 0x05 | {0x00}

  # !HDR COMMENT:{FSP_S_TEST_CONFIG:Fsp S Test Configuration}
  # !HDR EMBED:{FSP_S_TEST_CONFIG:FspsTestConfig:START}
  # Signature: {TEST}
  gKabylakeFspPkgTokenSpaceGuid.Signature                   | 0x0780 | 0x04 | 0x54534554

  #
  # SA Post-Mem Test Block Start
  #
  # !BSF NAME:{Enable/Disable Device 7 } TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Device  7 enabled, Disable (Default): Device 7 disabled}
  gKabylakeFspPkgTokenSpaceGuid.ChapDeviceEnable            | 0x0784 | 0x01 | 0x0

  # !BSF NAME:{Skip PAM register lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: PAM register will not be locked by RC, platform code should lock it, Disable(Default): PAM registers will be locked by RC}
  gKabylakeFspPkgTokenSpaceGuid.SkipPamLock                 | 0x0785 | 0x01 | 0x0

  # !BSF NAME:{EDRAM Test Mode} TYPE:{Combo}
  # !BSF OPTION:{0: EDRAM SW disable, 1: EDRAM SW Enable, 2: EDRAM HW mode}
  gKabylakeFspPkgTokenSpaceGuid.EdramTestMode               | 0x0786 | 0x01 | 0x2

  # !BSF NAME:{DMI Extended Sync Control} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Enable DMI Extended Sync Control, Disable(Default): Disable DMI Extended Sync Control}
  gKabylakeFspPkgTokenSpaceGuid.DmiExtSync                  | 0x0787 | 0x01 | 0x0

  # !BSF NAME:{DMI IOT Control} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Enable DMI IOT Control, Disable(Default): Disable DMI IOT Control}
  gKabylakeFspPkgTokenSpaceGuid.DmiIot                      | 0x0788 | 0x01 | 0x0

  # !BSF NAME:{PEG Max Payload size per root port} TYPE:{EditNum, HEX, (0x00, 0xFFFFFF)}
  # !BSF OPTION:{0xFF: Auto, 0x1: Force 128B, 0x2: Force 256B}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{0xFF(Default):Auto, 0x1: Force 128B, 0x2: Force 256B}
  gKabylakeFspPkgTokenSpaceGuid.PegMaxPayload               | 0x0789 | 0x3 | {0xFF, 0xFF, 0xFF}

  # !BSF NAME:{Enable/Disable IGFX RenderStandby} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable IGFX RenderStandby, Disable: Disable IGFX RenderStandby}
  gKabylakeFspPkgTokenSpaceGuid.RenderStandby               | 0x078C | 0x01 | 0x1

  # !BSF NAME:{Enable/Disable IGFX PmSupport} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable IGFX PmSupport, Disable: Disable IGFX PmSupport}
  gKabylakeFspPkgTokenSpaceGuid.PmSupport                   | 0x078D | 0x01 | 0x1

  # !BSF NAME:{Enable/Disable CdynmaxClamp} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable CdynmaxClamp, Disable: Disable CdynmaxClamp}
  gKabylakeFspPkgTokenSpaceGuid.CdynmaxClampEnable          | 0x078E | 0x01 | 0x1

  # !BSF NAME:{Disable VT-d} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Enable/FALSE(VT-d disabled), 1=Disable/TRUE (VT-d enabled)}
  gKabylakeFspPkgTokenSpaceGuid.VtdDisable                  | 0x078F | 0x1 | 0x1

  # !BSF NAME:{GT Frequency Limit} TYPE:{Combo}
  # !BSF OPTION:{0xFF: Auto(Default), 2: 100 Mhz, 3: 150 Mhz, 4: 200 Mhz, 5: 250 Mhz, 6: 300 Mhz, 7: 350 Mhz, 8: 400 Mhz, 9: 450 Mhz, 0xA: 500 Mhz, 0xB: 550 Mhz, 0xC: 600 Mhz, 0xD: 650 Mhz, 0xE: 700 Mhz, 0xF: 750 Mhz, 0x10: 800 Mhz, 0x11: 850 Mhz, 0x12:900 Mhz, 0x13: 950 Mhz, 0x14: 1000 Mhz, 0x15: 1050 Mhz, 0x16: 1100 Mhz, 0x17: 1150 Mhz, 0x18: 1200 Mhz}
  # !BSF HELP:{0xFF: Auto(Default), 2: 100 Mhz, 3: 150 Mhz, 4: 200 Mhz, 5: 250 Mhz, 6: 300 Mhz, 7: 350 Mhz, 8: 400 Mhz, 9: 450 Mhz, 0xA: 500 Mhz, 0xB: 550 Mhz, 0xC: 600 Mhz, 0xD: 650 Mhz, 0xE: 700 Mhz, 0xF: 750 Mhz, 0x10: 800 Mhz, 0x11: 850 Mhz, 0x12:900 Mhz, 0x13: 950 Mhz, 0x14: 1000 Mhz, 0x15: 1050 Mhz, 0x16: 1100 Mhz, 0x17: 1150 Mhz, 0x18: 1200 Mhz}
  gKabylakeFspPkgTokenSpaceGuid.GtFreqMax                   | 0x0790 | 0x1 | 0xFF

  # !BSF NAME:{SaPostMemTestRsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for SA Post-Mem Test}
  gKabylakeFspPkgTokenSpaceGuid.SaPostMemTestRsvd           | 0x0791 | 0xB | {0x00}

  #
  # SA Post-Mem Test Block End
  #

  #
  # CPU Post-Mem Test Block Start
  #
  # !BSF NAME:{1-Core Ratio Limit}
  # !BSF TYPE:{EditNum, DEC, (0, 255)}
  # !BSF HELP:{1-Core Ratio Limit: LFM to Fused max, For overclocking part: LFM to 255. This 1-Core Ratio Limit Must be greater than or equal to 2-Core Ratio Limit, 3-Core Ratio Limit, 4-Core Ratio Limit, 5-Core Ratio Limit, 6-Core Ratio Limit, 7-Core Ratio Limit, 8-Core Ratio Limit. Range is 0 to 255}
  gKabylakeFspPkgTokenSpaceGuid.OneCoreRatioLimit           | 0x079C | 0x01 | 0x00

  # !BSF NAME:{2-Core Ratio Limit}
  # !BSF TYPE:{EditNum, DEC, (0, 255)}
  # !BSF HELP:{2-Core Ratio Limit: LFM to Fused max, For overclocking part: LFM to 255. This 2-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 255}
  gKabylakeFspPkgTokenSpaceGuid.TwoCoreRatioLimit           | 0x079D | 0x01 | 0x00

  # !BSF NAME:{3-Core Ratio Limit}
  # !BSF TYPE:{EditNum, DEC, (0, 255)}
  # !BSF HELP:{3-Core Ratio Limit: LFM to Fused max, For overclocking part: LFM to 255. This 3-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 255}
  gKabylakeFspPkgTokenSpaceGuid.ThreeCoreRatioLimit         | 0x079E | 0x01 | 0x00

  # !BSF NAME:{4-Core Ratio Limit}
  # !BSF TYPE:{EditNum, DEC, (0, 255)}
  # !BSF HELP:{4-Core Ratio Limit: LFM to Fused max, For overclocking part: LFM to 255. This 4-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 255}
  gKabylakeFspPkgTokenSpaceGuid.FourCoreRatioLimit          | 0x079F | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable HWP} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable HWP(Hardware P states) Support. 0: Disable; <b>1: Enable;</b> 2-3:Reserved}
  gKabylakeFspPkgTokenSpaceGuid.Hwp                         | 0x07A1 | 0x01 | 0x01

  # !BSF NAME:{Hardware Duty Cycle Control} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Hardware Duty Cycle Control configuration. 0: Disabled; <b>1: Enabled</b> 2-3:Reserved}
  gKabylakeFspPkgTokenSpaceGuid.HdcControl                  | 0x07A2 | 0x01 | 0x01

  # !BSF NAME:{Package Long duration turbo mode time}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Package Long duration turbo mode time window in seconds. Valid values(Unit in seconds) 0 to 8 , 10 , 12 ,14 , 16 , 20 , 24 , 28 , 32 , 40 , 48 , 56 , 64 , 80 , 96 , 112 , 128}
  gKabylakeFspPkgTokenSpaceGuid.PowerLimit1Time             | 0x07A3 | 0x01 | 0x00

  # !BSF NAME:{Short Duration Turbo Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable short duration Turbo Mode. </b>0 : Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.PowerLimit2                 | 0x07A4 | 0x01 | 0x01

  # !BSF NAME:{Turbo settings Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Lock all Turbo settings Enable/Disable; <b>0: Disable , </b> 1: Enable}
  gKabylakeFspPkgTokenSpaceGuid.TurboPowerLimitLock         | 0x07A5 | 0x01 | 0x00

  # !BSF NAME:{Package PL3 time window}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Package PL3 time window range for this policy in milliseconds. Valid values are 0, 3 to 8, 10, 12, 14, 16, 20 , 24, 28, 32, 40, 48, 55, 56, 64}
  gKabylakeFspPkgTokenSpaceGuid.PowerLimit3Time             | 0x07A6 | 0x01 | 0x00

  # !BSF NAME:{Package PL3 Duty Cycle}
  # !BSF TYPE:{EditNum, DEC, (0, 100)}
  # !BSF HELP:{Package PL3 Duty Cycle; Valid Range is 0 to 100}
  gKabylakeFspPkgTokenSpaceGuid.PowerLimit3DutyCycle        | 0x07A7 | 0x01 | 0x00

  # !BSF NAME:{Package PL3 Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Package PL3 Lock Enable/Disable; <b>0: Disable ; <b> 1: Enable}
  gKabylakeFspPkgTokenSpaceGuid.PowerLimit3Lock             | 0x07A8 | 0x01 | 0x01

  # !BSF NAME:{Package PL4 Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Package PL4 Lock Enable/Disable; <b>0: Disable ; <b>1: Enable}
  gKabylakeFspPkgTokenSpaceGuid.PowerLimit4Lock             | 0x07A9 | 0x01 | 0x00

  # !BSF NAME:{TCC Activation Offset}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{TCC Activation Offset. Offset from factory set TCC activation temperature at which the Thermal Control Circuit must be activated. TCC will be activated at TCC Activation Temperature, in volts.For SKL Y SKU, the recommended default for this policy is  <b>10</b>, For all other SKUs the recommended default are <b>0</b>}
  gKabylakeFspPkgTokenSpaceGuid.TccActivationOffset         | 0x07AA | 0x01 | 0x0A

  # !BSF NAME:{Tcc Offset Clamp Enable/Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Tcc Offset Clamp for Runtime Average Temperature Limit (RATL) allows CPU to throttle below P1.For SKL Y SKU, the recommended default for this policy is <b>1: Enabled</b>, For all other SKUs the recommended default are  <b>0: Disabled</b>.}
  gKabylakeFspPkgTokenSpaceGuid.TccOffsetClamp              | 0x07AB | 0x01 | 0x01

  # !BSF NAME:{Tcc Offset Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Tcc Offset Lock for Runtime Average Temperature Limit (RATL) to lock temperature target; <b>0: Disabled</b>; 1: Enabled.}
  gKabylakeFspPkgTokenSpaceGuid.TccOffsetLock               | 0x07AC | 0x01 | 0x00

  # !BSF NAME:{Custom Ratio State Entries}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x28)}
  # !BSF HELP:{The number of custom ratio state entries, ranges from 0 to 40 for a valid custom ratio table.Sets the number of custom P-states. At least 2 states must be present}
  gKabylakeFspPkgTokenSpaceGuid.NumberOfEntries             | 0x07AD | 0x01 | 0x00

  # !BSF NAME:{Custom Short term Power Limit time window}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x80)}
  # !BSF HELP:{Short term Power Limit time window value for custom CTDP level 1. Valid Range 0 to 128}
  gKabylakeFspPkgTokenSpaceGuid.Custom1PowerLimit1Time      | 0x07AE | 0x01 | 0x1C

  # !BSF NAME:{Custom Turbo Activation Ratio}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Turbo Activation Ratio for custom cTDP level 1. Valid Range 0 to 255}
  gKabylakeFspPkgTokenSpaceGuid.Custom1TurboActivationRatio | 0x07AF | 0x01 | 0x14

  # !BSF NAME:{Custom Config Tdp Control}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x2)}
  # !BSF HELP:{Config Tdp Control (0/1/2) value for custom cTDP level 1. Valid Range is 0 to 2}
  gKabylakeFspPkgTokenSpaceGuid.Custom1ConfigTdpControl     | 0x07B0 | 0x01 | 0x00

  # !BSF NAME:{Custom Short term Power Limit time window}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x80)}
  # !BSF HELP:{Short term Power Limit time window value for custom CTDP level 2. Valid Range 0 to 128}
  gKabylakeFspPkgTokenSpaceGuid.Custom2PowerLimit1Time      | 0x07B1 | 0x01 | 0x1C

  # !BSF NAME:{Custom Turbo Activation Ratio}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Turbo Activation Ratio for custom cTDP level 2. Valid Range 0 to 255}
  gKabylakeFspPkgTokenSpaceGuid.Custom2TurboActivationRatio | 0x07B2 | 0x01 | 0x14

  # !BSF NAME:{Custom Config Tdp Control}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x2)}
  # !BSF HELP:{Config Tdp Control (0/1/2) value for custom cTDP level 1. Valid Range is 0 to 2}
  gKabylakeFspPkgTokenSpaceGuid.Custom2ConfigTdpControl     | 0x07B3 | 0x01 | 0x00

  # !BSF NAME:{Custom Short term Power Limit time window}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x80)}
  # !BSF HELP:{Short term Power Limit time window value for custom CTDP level 3. Valid Range 0 to 128}
  gKabylakeFspPkgTokenSpaceGuid.Custom3PowerLimit1Time      | 0x07B4 | 0x01 | 0x1C

  # !BSF NAME:{Custom Turbo Activation Ratio}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Turbo Activation Ratio for custom cTDP level 3. Valid Range 0 to 255}
  gKabylakeFspPkgTokenSpaceGuid.Custom3TurboActivationRatio | 0x07B5 | 0x01 | 0x14

  # !BSF NAME:{Custom Config Tdp Control}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x2)}
  # !BSF HELP:{Config Tdp Control (0/1/2) value for custom cTDP level 1. Valid Range is 0 to 2}
  gKabylakeFspPkgTokenSpaceGuid.Custom3ConfigTdpControl     | 0x07B6 | 0x01 | 0x00

  # !BSF NAME:{ConfigTdp mode settings Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Lock the ConfigTdp mode settings from runtime changes; <b>0: Disable</b>; 1: Enable}
  gKabylakeFspPkgTokenSpaceGuid.ConfigTdpLock               | 0x07B7 | 0x01 | 0x00

  # !BSF NAME:{Load Configurable TDP SSDT} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Configure whether to load Configurable TDP SSDT; <b>0: Disable</b>; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.ConfigTdpBios               | 0x07B8 | 0x01 | 0x00

  # !BSF NAME:{PL1 Enable value} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{PL1 Enable value to limit average platform power. <b>0: Disable</b>; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PsysPowerLimit1             | 0x07B9 | 0x01 | 0x00

  # !BSF NAME:{PL1 timewindow}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x80)}
  # !BSF HELP:{PL1 timewindow in seconds.Valid values(Unit in seconds) 0 to 8 , 10 , 12 ,14 , 16 , 20 , 24 , 28 , 32 , 40 , 48 , 56 , 64 , 80 , 96 , 112 , 128}
  gKabylakeFspPkgTokenSpaceGuid.PsysPowerLimit1Time         | 0x07BA | 0x01 | 0x00

  # !BSF NAME:{PL2 Enable Value} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{PL2 Enable activates the PL2 value to limit average platform power.<b>0: Disable</b>; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PsysPowerLimit2             | 0x07BB | 0x01 | 0x00


  # !BSF NAME:{Enable or Disable MLC Streamer Prefetcher} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable MLC Streamer Prefetcher; 0: Disable; <b>1: Enable</b>.}
  gKabylakeFspPkgTokenSpaceGuid.MlcStreamerPrefetcher       | 0x07BE | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable MLC Spatial Prefetcher} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable MLC Spatial Prefetcher; 0: Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.MlcSpatialPrefetcher        | 0x07BF | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Monitor /MWAIT instructions} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Monitor /MWAIT instructions; 0: Disable; <b>1: Enable</b>.}
  gKabylakeFspPkgTokenSpaceGuid.MonitorMwaitEnable          | 0x07C0 | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable initialization of machine check registers} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable initialization of machine check registers; 0: Disable; <b>1: Enable</b>.}
  gKabylakeFspPkgTokenSpaceGuid.MachineCheckEnable          | 0x07C1 | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable processor debug features} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable processor debug features; <b>0: Disable</b>; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.DebugInterfaceEnable        | 0x07C2 | 0x01 | 0x00

  # !BSF NAME:{Lock or Unlock debug interface features} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Lock or Unlock debug interface features; 0: Disable; <b>1: Enable</b>.}
  gKabylakeFspPkgTokenSpaceGuid.DebugInterfaceLockEnable    | 0x07C3 | 0x01 | 0x01

  # !BSF NAME:{AP Idle Manner of waiting for SIPI}
  # !BSF TYPE:{Combo} OPTION:{1:HALT loop, 2:MWAIT loop, 3:RUN loop}
  # !BSF HELP:{AP Idle Manner of waiting for SIPI; 1: HALT loop; <b>2: MWAIT loop</b>; 3: RUN loop.}
  gKabylakeFspPkgTokenSpaceGuid.ApIdleManner                | 0x07C4 | 0x01 | 0x02

  # !BSF NAME:{Settings for AP Handoff to OS}
  # !BSF TYPE:{Combo} OPTION:{1:HALT loop, 2:MWAIT loop}
  # !BSF HELP:{Settings for AP Handoff to OS; 1: HALT loop; <b>2: MWAIT loop</b>.}
  gKabylakeFspPkgTokenSpaceGuid.ApHandoffManner             | 0x07C5 | 0x01 | 0x02

  # !BSF NAME:{Control on Processor Trace output scheme}
  # !BSF TYPE:{Combo} OPTION:{0:Single Range Output, 1:ToPA Output}
  # !BSF HELP:{Control on Processor Trace output scheme; <b>0: Single Range Output</b>; 1: ToPA Output.}
  gKabylakeFspPkgTokenSpaceGuid.ProcTraceOutputScheme       | 0x07C8 | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable Processor Trace feature} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Processor Trace feature; <b>0: Disable</b>; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.ProcTraceEnable             | 0x07C9 | 0x01 | 0x00

  # !BSF NAME:{Memory region allocation for Processor Trace}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Memory region allocation for Processor Trace, Total Memory required is up to requested value * 2 (for memory alignment) * 8 active threads, to enable Processor Trace, PcdFspReservedMemoryLength must be increased by the total memory required, and PlatformMemorySize policy must also be increased by the total memory required over 32MB, Valid Values are 0 - 4KB , 0x1 - 8KB , 0x2 - 16KB , 0x3 - 32KB , 0x4 - 64KB , 0x5 - 128KB , 0x6 - 256KB , 0x7 - 512KB , 0x8 - 1MB , 0x9 - 2MB , 0xA - 4MB , 0xB - 8MB , 0xC - 16MB , 0xD - 32MB , 0xE - 64MB , 0xF - 128MB , 0xFF: Disable}
  gKabylakeFspPkgTokenSpaceGuid.ProcTraceMemSize            | 0x07CA | 0x01 | 0xFF

  # !BSF NAME:{Enable or Disable Voltage Optimization feature} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Voltage Optimization feature 0: Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.VoltageOptimization         | 0x07CC | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Intel SpeedStep Technology} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Intel SpeedStep Technology. 0: Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.Eist                        | 0x07CD | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Energy Efficient P-state} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Energy Efficient P-state will be applied in Turbo mode. Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.EnergyEfficientPState       | 0x07CE | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Energy Efficient Turbo} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Energy Efficient Turbo, will be applied in Turbo mode. Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.EnergyEfficientTurbo        | 0x07CF | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable T states} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable T states; <b>0: Disable</b>; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.TStates                     | 0x07D0 | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Bi-Directional PROCHOT#} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Bi-Directional PROCHOT#; 0: Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.BiProcHot                   | 0x07D1 | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable PROCHOT# signal being driven externally} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable PROCHOT# signal being driven externally; 0: Disable; <b>1: Enable</b>.}
  gKabylakeFspPkgTokenSpaceGuid.DisableProcHotOut           | 0x07D2 | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable PROCHOT# Response} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable PROCHOT# Response; <b>0: Disable</b>; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.ProcHotResponse             | 0x07D3 | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable VR Thermal Alert} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable VR Thermal Alert; <b>0: Disable</b>; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.DisableVrThermalAlert       | 0x07D4 | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable Thermal Reporting} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Thermal Reporting through ACPI tables; 0: Disable; <b>1: Enable</b>.}
  gKabylakeFspPkgTokenSpaceGuid.AutoThermalReporting        | 0x07D5 | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable Thermal Monitor} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Thermal Monitor; 0: Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.ThermalMonitor              | 0x07D6 | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable CPU power states (C-states)} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable CPU power states (C-states). 0: Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.Cx                          | 0x07D7 | 0x01 | 0x00

  # !BSF NAME:{Configure C-State Configuration Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Configure C-State Configuration Lock; 0: Disable; <b>1: Enable</b>.}
  gKabylakeFspPkgTokenSpaceGuid.PmgCstCfgCtrlLock           | 0x07D8 | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Enhanced C-states} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Enhanced C-states. 0: Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.C1e                         | 0x07D9 | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Package C-State Demotion}
  # !BSF TYPE:{Combo} OPTION:{0:Disable, 1:Enable, 2:Auto}
  # !BSF HELP:{Enable or Disable Package C-State Demotion. 0: Disable; 1: Enable; <b>2: Auto</b> (Auto: Enabled for Skylake; Disabled for Kabylake)}
  gKabylakeFspPkgTokenSpaceGuid.PkgCStateDemotion           | 0x07DA | 0x01 | 0x02

  # !BSF NAME:{Enable or Disable Package C-State UnDemotion}
  # !BSF TYPE:{Combo} OPTION:{0:Disable, 1:Enable, 2:Auto}
  # !BSF HELP:{Enable or Disable Package C-State UnDemotion. 0: Disable; 1: Enable; <b>2: Auto</b> (Auto: Enabled for Skylake; Disabled for Kabylake)}
  gKabylakeFspPkgTokenSpaceGuid.PkgCStateUnDemotion         | 0x07DB | 0x01 | 0x02

  # !BSF NAME:{Enable or Disable CState-Pre wake} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable CState-Pre wake. 0: Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.CStatePreWake               | 0x07DC | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable TimedMwait Support.} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable TimedMwait Support. <b>0: Disable</b>; 1: Enable}
  gKabylakeFspPkgTokenSpaceGuid.TimedMwait                  | 0x07DD | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable IO to MWAIT redirection} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable IO to MWAIT redirection; <b>0: Disable</b>; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.CstCfgCtrIoMwaitRedirection | 0x07DE | 0x01 | 0x00

  # !BSF NAME:{Set the Max Pkg Cstate}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Set the Max Pkg Cstate. Default set to Auto which limits the Max Pkg Cstate to deep C-state. Valid values 0 - C0/C1 , 1 - C2 , 2 - C3 , 3 - C6 , 4 - C7 , 5 - C7S , 6 - C8 , 7 - C9 , 8 - C10 , 254 - CPU Default , 255 - Auto}
  gKabylakeFspPkgTokenSpaceGuid.PkgCStateLimit              | 0x07DF | 0x01 | 0x08

  # !BSF NAME:{TimeUnit for C-State Latency Control0}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x5)}
  # !BSF HELP:{TimeUnit for C-State Latency Control0; Valid values 0 - 1ns , 1 - 32ns , 2 - 1024ns , 3 - 32768ns , 4 - 1048576ns , 5 - 33554432ns}
  gKabylakeFspPkgTokenSpaceGuid.CstateLatencyControl0TimeUnit   | 0x07E0 | 0x01 | 0x02

  # !BSF NAME:{TimeUnit for C-State Latency Control1}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x5)}
  # !BSF HELP:{TimeUnit for C-State Latency Control1;Valid values 0 - 1ns , 1 - 32ns , 2 - 1024ns , 3 - 32768ns , 4 - 1048576ns , 5 - 33554432ns}
  gKabylakeFspPkgTokenSpaceGuid.CstateLatencyControl1TimeUnit   | 0x07E1 | 0x01 | 0x02

  # !BSF NAME:{TimeUnit for C-State Latency Control2}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x5)}
  # !BSF HELP:{TimeUnit for C-State Latency Control2;Valid values 0 - 1ns , 1 - 32ns , 2 - 1024ns , 3 - 32768ns , 4 - 1048576ns , 5 - 33554432ns}
  gKabylakeFspPkgTokenSpaceGuid.CstateLatencyControl2TimeUnit   | 0x07E2 | 0x01 | 0x02

  # !BSF NAME:{TimeUnit for C-State Latency Control3}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x5)}
  # !BSF HELP:{TimeUnit for C-State Latency Control3;Valid values 0 - 1ns , 1 - 32ns , 2 - 1024ns , 3 - 32768ns , 4 - 1048576ns , 5 - 33554432ns}
  gKabylakeFspPkgTokenSpaceGuid.CstateLatencyControl3TimeUnit   | 0x07E3 | 0x01 | 0x02

  # !BSF NAME:{TimeUnit for C-State Latency Control4}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x5)}
  # !BSF HELP:{TimeUnit for C-State Latency Control4;Valid values 0 - 1ns , 1 - 32ns , 2 - 1024ns , 3 - 32768ns , 4 - 1048576ns , 5 - 33554432ns}
  gKabylakeFspPkgTokenSpaceGuid.CstateLatencyControl4TimeUnit   | 0x07E4 | 0x01 | 0x02

  # !BSF NAME:{TimeUnit for C-State Latency Control5}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x5)}
  # !BSF HELP:{TimeUnit for C-State Latency Control5;Valid values 0 - 1ns , 1 - 32ns , 2 - 1024ns , 3 - 32768ns , 4 - 1048576ns , 5 - 33554432ns}
  gKabylakeFspPkgTokenSpaceGuid.CstateLatencyControl5TimeUnit   | 0x07E5 | 0x01 | 0x02

  # !BSF NAME:{Interrupt Redirection Mode Select}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x7)}
  # !BSF HELP:{Interrupt Redirection Mode Select.0: Fixed priority; 1: Round robin;2: Hash vector;4: PAIR with fixed priority;5: PAIR with round robin;6: PAIR with hash vector;7: No change.}
  gKabylakeFspPkgTokenSpaceGuid.PpmIrmSetting               | 0x07E6 | 0x01 | 0x04

  # !BSF NAME:{Lock prochot configuration} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Lock prochot configuration Enable/Disable; <b>0: Disable</b>; 1: Enable}
  gKabylakeFspPkgTokenSpaceGuid.ProcHotLock                 | 0x07E7 | 0x01 | 0x00

  # !BSF NAME:{Configuration for boot TDP selection}
  # !BSF TYPE:{Combo} OPTION:{0:TDP Nominal, 1:TDP Down, 2:TDP Up, 0xFF:Deactivate}
  # !BSF HELP:{Configuration for boot TDP selection; <b>0: TDP Nominal</b>; 1: TDP Down; 2: TDP Up; 0xFF: Deactivate}
  gKabylakeFspPkgTokenSpaceGuid.ConfigTdpLevel              | 0x07E8 | 0x01 | 0x00

  # !BSF NAME:{Race To Halt} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable Race To Halt feature. RTH will dynamically increase CPU frequency in order to enter pkg C-State faster to reduce overall power. (RTH is controlled through MSR 1FC bit 20)Disable; <b>1: Enable</b>}
  gKabylakeFspPkgTokenSpaceGuid.RaceToHalt                 | 0x07E9 | 0x01 | 0x01

  # !BSF NAME:{Max P-State Ratio}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x7F)}
  # !BSF HELP:{Max P-State Ratio , Valid Range 0 to 0x7F}
  gKabylakeFspPkgTokenSpaceGuid.MaxRatio                    | 0x07EA | 0x02 | 0x00

  # !BSF NAME:{Maximum P-state ratio to use in the custom P-state table} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Maximum P-state ratio to use in the custom P-state table. NumOfCustomPStates has valid range between 0 to 40. For no. of P-States supported(NumOfCustomPStates) , StateRatio[NumOfCustomPStates] are configurable. Valid Range of value is 0 to 0x7F}
  gKabylakeFspPkgTokenSpaceGuid.StateRatio                  | 0x07EC | 0x50 | {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}

  # !BSF NAME:{Interrupt Response Time Limit of C-State LatencyContol0}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3FF)}
  # !BSF HELP:{Interrupt Response Time Limit of C-State LatencyContol0.Range of value 0 to 0x3FF, Default is 0x4E, Server Platform is 0x4B}
  gKabylakeFspPkgTokenSpaceGuid.CstateLatencyControl0Irtl   | 0x083C | 0x02 | 0x4E

  # !BSF NAME:{Interrupt Response Time Limit of C-State LatencyContol1}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3FF)}
  # !BSF HELP:{Interrupt Response Time Limit of C-State LatencyContol1.Range of value 0 to 0x3FF, Default is 0x76, Server Platform is 0x6B}
  gKabylakeFspPkgTokenSpaceGuid.CstateLatencyControl1Irtl   | 0x083E | 0x02 | 0x76

  # !BSF NAME:{Interrupt Response Time Limit of C-State LatencyContol2}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3FF)}
  # !BSF HELP:{Interrupt Response Time Limit of C-State LatencyContol2.Range of value 0 to 0x3FF}
  gKabylakeFspPkgTokenSpaceGuid.CstateLatencyControl2Irtl   | 0x0840 | 0x02 | 0x94

  # !BSF NAME:{Interrupt Response Time Limit of C-State LatencyContol3}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3FF)}
  # !BSF HELP:{Interrupt Response Time Limit of C-State LatencyContol3.Range of value 0 to 0x3FF}
  gKabylakeFspPkgTokenSpaceGuid.CstateLatencyControl3Irtl   | 0x0842 | 0x02 | 0xFA

  # !BSF NAME:{Interrupt Response Time Limit of C-State LatencyContol4}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3FF)}
  # !BSF HELP:{Interrupt Response Time Limit of C-State LatencyContol4.Range of value 0 to 0x3FF}
  gKabylakeFspPkgTokenSpaceGuid.CstateLatencyControl4Irtl   | 0x0844 | 0x02 | 0x14C

  # !BSF NAME:{Interrupt Response Time Limit of C-State LatencyContol5}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3FF)}
  # !BSF HELP:{Interrupt Response Time Limit of C-State LatencyContol5.Range of value 0 to 0x3FF}
  gKabylakeFspPkgTokenSpaceGuid.CstateLatencyControl5Irtl   | 0x0846 | 0x02 | 0x3F2

  # !BSF NAME:{Package Long duration turbo mode power limit}
  # !BSF TYPE:{EditNum, DEC, (0, 4095875)}
  # !BSF HELP:{Package Long duration turbo mode power limit. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit. Valid Range 0 to 4095875 in Step size of 125}
  gKabylakeFspPkgTokenSpaceGuid.PowerLimit1                 | 0x0848 | 0x04 | 0x1B58

  # !BSF NAME:{Package Short duration turbo mode power limit}
  # !BSF TYPE:{EditNum, DEC, (0, 4095875)}
  # !BSF HELP:{Package Short duration turbo mode power limit. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gKabylakeFspPkgTokenSpaceGuid.PowerLimit2Power            | 0x084C | 0x04 | 0x3A98

  # !BSF NAME:{Package PL3 power limit}
  # !BSF TYPE:{EditNum, DEC, (0, 4095875)}
  # !BSF HELP:{Package PL3 power limit. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gKabylakeFspPkgTokenSpaceGuid.PowerLimit3                 | 0x0850 | 0x04 | 0x3A98

  # !BSF NAME:{Package PL4 power limit}
  # !BSF TYPE:{EditNum, DEC, (0, 4095875)}
  # !BSF HELP:{Package PL4 power limit. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gKabylakeFspPkgTokenSpaceGuid.PowerLimit4                 | 0x0854 | 0x04 | 0x5208

  # !BSF NAME:{Tcc Offset Time Window for RATL}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Tcc Offset Time Window can range from 5ms to 448000ms for Runtime Average Temperature Limit (RATL).For SKL Y SKU, the recommended default for this policy is <b>5000: 5 seconds</b>, For all other SKUs the recommended default are <b>0: Disabled</b>
  # 0: Disabled,5: 5ms , 10:10ms , 55:55ms , 156:156ms , 375:375ms , 500:500ms,750:750ms ,1000:1s,2000:2s,3000:3s,4000:4s,5000:5s,6000:6s,7000:7s,8000:8s,10000:10s,12000:12s,14000:14s,16000:16s,20000:20s,24000:24s,28000:28s,32000:32s,40000:40s,48000:48s,56000:56s,64000:64s,80000:80s,96000:96s,112000:112s,128000:128s,160000:160s,192000:192s,224000:224s,256000:256s,320000:320s,384000:384s,448000:448s}
  gKabylakeFspPkgTokenSpaceGuid.TccOffsetTimeWindowForRatl  | 0x0858 | 0x04 | 0x00

  # !BSF NAME:{Short term Power Limit value for custom cTDP level 1}
  # !BSF TYPE:{EditNum, DEC, (0, 4095875)}
  # !BSF HELP:{Short term Power Limit value for custom cTDP level 1. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gKabylakeFspPkgTokenSpaceGuid.Custom1PowerLimit1          | 0x085C | 0x04 | 0x9C40

  # !BSF NAME:{Long term Power Limit value for custom cTDP level 1}
  # !BSF TYPE:{EditNum, DEC, (0, 4095875)}
  # !BSF HELP:{Long term Power Limit value for custom cTDP level 1. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gKabylakeFspPkgTokenSpaceGuid.Custom1PowerLimit2          | 0x0860 | 0x04 | 0xC350

  # !BSF NAME:{Short term Power Limit value for custom cTDP level 2}
  # !BSF TYPE:{EditNum, DEC, (0, 4095875)}
  # !BSF HELP:{Short term Power Limit value for custom cTDP level 2. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gKabylakeFspPkgTokenSpaceGuid.Custom2PowerLimit1          | 0x0864 | 0x04 | 0x9C40

  # !BSF NAME:{Long term Power Limit value for custom cTDP level 2}
  # !BSF TYPE:{EditNum, DEC, (0, 4095875)}
  # !BSF HELP:{Long term Power Limit value for custom cTDP level 2. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gKabylakeFspPkgTokenSpaceGuid.Custom2PowerLimit2          | 0x0868 | 0x04 | 0xC350

  # !BSF NAME:{Short term Power Limit value for custom cTDP level 3}
  # !BSF TYPE:{EditNum, DEC, (0, 4095875)}
  # !BSF HELP:{Short term Power Limit value for custom cTDP level 3. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gKabylakeFspPkgTokenSpaceGuid.Custom3PowerLimit1          | 0x086C | 0x04 | 0x9C40

  # !BSF NAME:{Long term Power Limit value for custom cTDP level 3}
  # !BSF TYPE:{EditNum, DEC, (0, 4095875)}
  # !BSF HELP:{Long term Power Limit value for custom cTDP level 3. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gKabylakeFspPkgTokenSpaceGuid.Custom3PowerLimit2          | 0x0870 | 0x04 | 0xC350

  # !BSF NAME:{Platform PL1 power}
  # !BSF TYPE:{EditNum, DEC, (0, 4095875)}
  # !BSF HELP:{Platform PL1 power. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gKabylakeFspPkgTokenSpaceGuid.PsysPowerLimit1Power        | 0x0874 | 0x04 | 0x00

  # !BSF NAME:{Platform PL2 power}
  # !BSF TYPE:{EditNum, DEC, (0, 4095875)}
  # !BSF HELP:{Platform PL2 power. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gKabylakeFspPkgTokenSpaceGuid.PsysPowerLimit2Power        | 0x0878 | 0x04 | 0x00

  # !BSF NAME:{Platform Power Pmax}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x400)}
  # !BSF HELP:{PCODE MMIO Mailbox: Platform Power Pmax. <b>0 - Auto</b> Specified in 1/8 Watt increments. Range 0-1024 Watts. Value of 800 = 100W}
  gKabylakeFspPkgTokenSpaceGuid.PsysPmax                    | 0x087C | 0x02 | 0xAC

  # !BSF NAME:{CpuS3ResumeDataSize} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Size of CPU S3 Resume Data}
  gKabylakeFspPkgTokenSpaceGuid.CpuS3ResumeDataSize         | 0x087E | 0x02 | 0

  # !BSF NAME:{CpuS3ResumeData} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Pointer to CPU S3 Resume Data}
  gKabylakeFspPkgTokenSpaceGuid.CpuS3ResumeData             | 0x0880 | 0x04 | 0

  # !BSF NAME:{5-Core Ratio Limit}
  # !BSF TYPE:{EditNum, DEC, (0, 255)}
  # !BSF HELP:{5-Core Ratio Limit: LFM to Fused max, For overclocking part: LFM to 255. This 5-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 255}
  gKabylakeFspPkgTokenSpaceGuid.FiveCoreRatioLimit          | 0x0884 | 0x01 | 0x00

  # !BSF NAME:{6-Core Ratio Limit}
  # !BSF TYPE:{EditNum, DEC, (0, 255)}
  # !BSF HELP:{6-Core Ratio Limit: LFM to Fused max, For overclocking part: LFM to 255. This 6-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 255}
  gKabylakeFspPkgTokenSpaceGuid.SixCoreRatioLimit           | 0x0885 | 0x01 | 0x00

  # !BSF NAME:{7-Core Ratio Limit}
  # !BSF TYPE:{EditNum, DEC, (0, 255)}
  # !BSF HELP:{7-Core Ratio Limit: LFM to Fused max, For overclocking part: LFM to 255. This 7-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 255}
  gKabylakeFspPkgTokenSpaceGuid.SevenCoreRatioLimit         | 0x0886 | 0x01 | 0x00

  # !BSF NAME:{8-Core Ratio Limit}
  # !BSF TYPE:{EditNum, DEC, (0, 255)}
  # !BSF HELP:{8-Core Ratio Limit: LFM to Fused max, For overclocking part: LFM to 255. This 8-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 255}
  gKabylakeFspPkgTokenSpaceGuid.EightCoreRatioLimit         | 0x0887 | 0x01 | 0x00

  # !BSF NAME:{Set Three Strike Counter Disable} TYPE:{Combo} OPTION:{0: False, 1: True}
  # !BSF HELP:{False (default): Three Strike counter will be incremented and True: Prevents Three Strike counter from incrementing; <b>0: False</b>; 1: True.}
  gKabylakeFspPkgTokenSpaceGuid.ThreeStrikeCounterDisable   | 0x0888 | 0x01 | 0x00

  # !BSF NAME:{ReservedCpuPostMemTest} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for CPU Post-Mem Test}
  gKabylakeFspPkgTokenSpaceGuid.ReservedCpuPostMemTest      | 0x0889 | 0x1 | {0x00}
  #
  # CPU Post-Mem Test Block End
  #

  ###########Security Test Policies Start ###########################################
  # !BSF NAME:{SgxSinitDataFromTpm} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{SgxSinitDataFromTpm default values}
  gSkylakeFspPkgTokenSpaceGuid.SgxSinitDataFromTpm          | 0x088A | 0x1 | 0xFF
  ###########Security Test Policies End ###########################################

  #
  # ME Post-Mem Test Block Begin
  #
  # !BSF NAME:{End of Post message} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Send in PEI, 2:Send in DXE, 3:Reserved}
  # !BSF HELP:{Test, Send End of Post message. Disable(0x0): Disable EOP message, Send in PEI(0x1): EOP send in PEI, Send in DXE(0x2)(Default): EOP send in PEI}
  gKabylakeFspPkgTokenSpaceGuid.EndOfPostMessage            | 0x088B | 0x01 | 0x1

  # !BSF NAME:{D0I3 Setting for HECI Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Setting this option disables setting D0I3 bit for all HECI devices}
  gKabylakeFspPkgTokenSpaceGuid.DisableD0I3SettingForHeci   | 0x088C | 0x01 | 0x0
  #
  # ME Post-Mem Test Block End
  #

  #
  #  PCH Silicon Test Policies start
  #

  # !BSF NAME:{Enable LOCKDOWN SMI} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable SMI_LOCK bit to prevent writes to the Global SMI Enable bit.}
  gKabylakeFspPkgTokenSpaceGuid.PchLockDownGlobalSmi        | 0x088D | 0x01 | 0x01

  # !BSF NAME:{HD Audio Reset Wait Timer} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{The delay timer after Azalia reset, the value is number of microseconds. Default is 600.}
  gKabylakeFspPkgTokenSpaceGuid.PchHdaResetWaitTimer        | 0x088E | 0x02 | 0x258

  # !BSF NAME:{Enable LOCKDOWN BIOS Interface} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable BIOS Interface Lock Down bit to prevent writes to the Backup Control Register.}
  gKabylakeFspPkgTokenSpaceGuid.PchLockDownBiosInterface    | 0x0890 | 0x01 | 0x01

  # !BSF NAME:{RTC CMOS RAM LOCK}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}}
  # !BSF HELP:{Enable RTC lower and upper 128 byte Lock bits to lock Bytes 38h-3Fh in the upper and and lower 128-byte bank of RTC RAM.}
  gKabylakeFspPkgTokenSpaceGuid.PchLockDownRtcLock          | 0x0891 | 0x01 | 0x01

  # !BSF NAME:{PCH Sbi lock bit} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This unlock the SBI lock bit to allow SBI after post time. 0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchSbiUnlock                | 0x0892 | 0x01 | 0x00

  # !BSF NAME:{PCH Psf lock bit} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{The PSF registers will be locked before 3rd party code execution. 0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PchSbAccessUnlock           | 0x0893 | 0x01 | 0x00

  # !BSF NAME:{PCIE RP Ltr Max Snoop Latency} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Max Snoop Latency.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpLtrMaxSnoopLatency    | 0x0894 | 0x30 | { 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003 }

  # !BSF NAME:{PCIE RP Ltr Max No Snoop Latency} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Max Non-Snoop Latency.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpLtrMaxNoSnoopLatency  | 0x08C4 | 0x30 | { 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003, 0x1003 }

  # !BSF NAME:{PCIE RP Snoop Latency Override Mode} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Snoop Latency Override Mode.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpSnoopLatencyOverrideMode          | 0x08F4 | 0x18 | { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Snoop Latency Override Multiplier} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Snoop Latency Override Multiplier.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpSnoopLatencyOverrideMultiplier    | 0x090C | 0x18 | { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Snoop Latency Override Value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Snoop Latency Override Value.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpSnoopLatencyOverrideValue         | 0x0924 | 0x30 | { 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C }

  # !BSF NAME:{PCIE RP Non Snoop Latency Override Mode} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Non-Snoop Latency Override Mode.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpNonSnoopLatencyOverrideMode       | 0x0954 | 0x18 | { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Non Snoop Latency Override Multiplier} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Non-Snoop Latency Override Multiplier.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpNonSnoopLatencyOverrideMultiplier | 0x096C | 0x18 | { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Non Snoop Latency Override Value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Non-Snoop Latency Override Value.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpNonSnoopLatencyOverrideValue      | 0x0984 | 0x30 | { 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C }

  # !BSF NAME:{PCIE RP Slot Power Limit Scale} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Specifies scale used for slot power limit value. Leave as 0 to set to default.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpSlotPowerLimitScale   | 0x09B4 | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Slot Power Limit Value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Specifies upper limit on power supplie by slot. Leave as 0 to set to default.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpSlotPowerLimitValue   | 0x09CC | 0x30 | { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }

  # !BSF NAME:{PCIE RP Upstream Port Transmiter Preset} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Used during Gen3 Link Equalization. Used for all lanes.  Default is 5.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpUptp                  | 0x09FC | 0x18 | { 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05 }

  # !BSF NAME:{PCIE RP Downstream Port Transmiter Preset} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Used during Gen3 Link Equalization. Used for all lanes.  Default is 7.}
  gKabylakeFspPkgTokenSpaceGuid.PcieRpDptp                  | 0x0A14 | 0x18 | { 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07 }

  # !BSF NAME:{PCIE RP Enable Port8xh Decode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This member describes whether PCIE root port Port 8xh Decode is enabled. 0: Disable; 1: Enable.}
  gKabylakeFspPkgTokenSpaceGuid.PcieEnablePort8xhDecode     | 0x0A2C | 0x01 | 0x00

  # !BSF NAME:{PCIE Port8xh Decode Port Index} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{The Index of PCIe Port that is selected for Port8xh Decode (0 Based).}
  gKabylakeFspPkgTokenSpaceGuid.PchPciePort8xhDecodePortIndex  | 0x0A2D | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Disable Energy Report} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable/Enable PCH to CPU enery report feature.}
  gKabylakeFspPkgTokenSpaceGuid.PchPmDisableEnergyReport    | 0x0A2E | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Pmc Read Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Deprecated}
  gKabylakeFspPkgTokenSpaceGuid.PchPmPmcReadDisable         | 0x0A2F | 0x01 | 0x00

  # !BSF NAME:{PCH Sata Test Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Allow entrance to the PCH SATA test modes.}
  gKabylakeFspPkgTokenSpaceGuid.SataTestMode                | 0x0A30 | 0x01 | 0x00

  #
  #  PCH Silicon Test Policies End
  #

  # !HDR EMBED:{FSP_S_TEST_CONFIG:FspsTestConfig:END}
  gKabylakeFspPkgTokenSpaceGuid.ReservedFspsTestUpd         | 0x0A31 | 0xF | {0x00}


  # Note please keep "UpdTerminator" at the end of each UPD region.
  # The tool will use this field to determine the actual end of the UPD data
  # structure.
  gKabylakeFspPkgTokenSpaceGuid.UpdTerminator               | 0x0C16 | 0x02 | 0x55AA

###################################################################################################
#
# Components Section - list of the modules and components that will be processed by compilation
#                      tools and the EDK II tools to generate PE32/PE32+/Coff image files.
#
# Note: The EDK II DSC file is not used to specify how compiled binary images get placed
#       into firmware volume images. This section is just a list of modules to compile from
#       source into UEFI-compliant binaries.
#       It is the FDF file that contains information on combining binary files into firmware
#       volume images, whose concept is beyond UEFI and is described in PI specification.
#       Binary modules do not need to be listed in this section, as they should be
#       specified in the FDF file. For example: Shell binary (Shell_Full.efi), FAT binary (Fat.efi),
#       Logo (Logo.bmp), and etc.
#       There may also be modules listed in this section that are not required in the FDF file,
#       When a module listed here is excluded from FDF file, then UEFI-compliant binary will be
#       generated for it, but the binary will not be put into any firmware volume.
#
###################################################################################################

[Components.IA32]
  #
  # SEC
  #
  IntelFsp2Pkg/FspSecCore/FspSecCoreT.inf {
    <LibraryClasses>
      MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
      FspSecPlatformLib|$(PLATFORM_SI_PACKAGE)/SampleCode/Library/PlatformSecLib/FspTPlatformSecLib.inf
  }
  IntelFsp2Pkg/FspSecCore/FspSecCoreM.inf {
    <LibraryClasses>
      MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
      FspSecPlatformLib|$(PLATFORM_SI_PACKAGE)/SampleCode/Library/PlatformSecLib/FspMPlatformSecLib.inf
  }
  IntelFsp2Pkg/FspSecCore/FspSecCoreS.inf {
    <LibraryClasses>
      MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
      FspSecPlatformLib|$(PLATFORM_SI_PACKAGE)/SampleCode/Library/PlatformSecLib/FspSPlatformSecLib.inf
  }

  #
  # PEI Core
  #
  $(FSP_PACKAGE)/Override/MdeModulePkg/Core/Pei/PeiMain.inf {  # FSPO-0006: RoyalParkOverrideContent
    <LibraryClasses>
      MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
    <PcdsFixedAtBuild>
      gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x27
  }

  #
  # PCD
  #
  MdeModulePkg/Universal/PCD/Pei/Pcd.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  }

  #
  # FSP Binary Components
  #
  $(FSP_PACKAGE)/FspDebugInit/Pei/FspDebugServicePei.inf
  $(FSP_PACKAGE)/FspHeader/FspHeader.inf
  $(PLATFORM_SI_PACKAGE)/SiInit/Pei/SiInitPreMemFsp.inf
  MdeModulePkg/Universal/PcatSingleSegmentPciCfg2Pei/PcatSingleSegmentPciCfg2Pei.inf
  $(PLATFORM_SI_PACKAGE)/SystemAgent/IntelGraphicsPeim/Binaries/IntelGraphicsPeim.inf
  #
  # CpuMp PEIM for MpService PPI
  #
  $(PLATFORM_SI_PACKAGE)/Override/UefiCpuPkg/CpuMpPei/CpuMpPei.inf      # SICO-KBL-0002
  $(PLATFORM_SI_PACKAGE)/SiInit/Pei/SiInit.inf
  $(PLATFORM_SI_PACKAGE)/SystemAgent/SaInit/Dxe/SaInitFsp.inf
  $(PLATFORM_SI_PACKAGE)/Pch/PchInit/Dxe/PchInitDxeFsp.inf
  $(PLATFORM_SI_PACKAGE)/Me/HeciInit/Dxe/HeciInitFsp.inf
  MdeModulePkg/Core/DxeIplPeim/DxeIpl.inf {
    <LibraryClasses>
      DebugAgentLib|MdeModulePkg/Library/DebugAgentLibNull/DebugAgentLibNull.inf
      ResetSystemLib|MdeModulePkg/Library/BaseResetSystemLibNull/BaseResetSystemLibNull.inf
  }
  $(FSP_PACKAGE)/FspInit/Pei/FspInitPreMem.inf {
    <LibraryClasses>
      CpuPolicyLibPreMem|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiCpuPolicyLibPreMem/PeiCpuPolicyLibPreMem.inf
  }
  $(FSP_PACKAGE)/FspPcdInit/Pei/FspPcdInit.inf
  $(FSP_PACKAGE)/FspInit/Pei/FspInit.inf {
    <LibraryClasses>
      CpuPolicyLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiCpuPolicyLib/PeiCpuPolicyLib.inf
  }
  IntelFsp2Pkg/FspNotifyPhase/FspNotifyPhasePeim.inf

!include $(PLATFORM_SI_PACKAGE)/SiPkgBuildOption.dsc

###################################################################################################
#
# BuildOptions Section - Define the module specific tool chain flags that should be used as
#                        the default flags for a module. These flags are appended to any
#                        standard flags that are defined by the build process. They can be
#                        applied for any modules or only those modules with the specific
#                        module style (EDK or EDKII) specified in [Components] section.
#
###################################################################################################
[BuildOptions]
# Append build options for EDK and EDKII drivers (= is Append, == is Replace)

[BuildOptions.Common.EDKII]

!if gKabylakeFspPkgTokenSpaceGuid.PcdMiniBiosEnable == TRUE
  DEFINE EDKII_DSC_MINIBIOS_BUILD_OPTIONS = -DMRC_MINIBIOS_BUILD
!else
  DEFINE EDKII_DSC_MINIBIOS_BUILD_OPTIONS =
!endif

!if gSiPkgTokenSpaceGuid.PcdSsaFlagEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdEvLoaderEnable == TRUE
  DEFINE EV_LOADER_BUILD_OPTIONS = -DSSA_FLAG=1
!else
  DEFINE EV_LOADER_BUILD_OPTIONS =
!endif
!else
  DEFINE EV_LOADER_BUILD_OPTIONS =
!endif


  DEFINE EDKII_DSC_FEATURE_BUILD_OPTIONS = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS) $(EDKII_DSC_MINIBIOS_BUILD_OPTIONS) $(EV_LOADER_BUILD_OPTIONS) -DFSP_FLAG
  DEFINE EDKII_DSC_ALL_BUILD_OPTIONS = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)

GCC:   *_*_IA32_ASM_FLAGS   = $(EDKII_DSC_FEATURE_BUILD_OPTIONS) -Wa,--defsym,FSP_FLAG=1 -Wa,--defsym,SEC_LOAD_UCODE_FLAG=1
MSFT:  *_*_IA32_ASM_FLAGS   = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)
  *_*_IA32_CC_FLAGS    = $(EDKII_DSC_ALL_BUILD_OPTIONS)
  *_*_IA32_VFRPP_FLAGS = $(EDKII_DSC_ALL_BUILD_OPTIONS)
  *_*_IA32_APP_FLAGS   = $(EDKII_DSC_ALL_BUILD_OPTIONS)
