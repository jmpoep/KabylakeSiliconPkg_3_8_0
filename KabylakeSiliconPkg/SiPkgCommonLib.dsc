## @file
#  Component description file for the SkyLake SiPkg both Pei and Dxe libraries DSC file.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2012 - 2019 Intel Corporation.
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
#@par Specification Reference:
#
##
#
# Silicon Init Common Library
#

#
# Common
#
 MmPciLib|$(PLATFORM_SI_PACKAGE)/Library/PeiDxeSmmMmPciLib/PeiDxeSmmMmPciLib.inf

#
# Cpu
#
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
 SecCpuLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/SecCpuLib/SecCpuLib.inf
!endif

CpuPlatformLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmCpuPlatformLib/PeiDxeSmmCpuPlatformLib.inf

!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
 TxtLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeTxtLib/PeiDxeTxtLib.inf

!if gSiPkgTokenSpaceGuid.PcdBootGuardEnable == TRUE
 BootGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmBootGuardLib/PeiDxeSmmBootGuardLib.inf
!else
 BootGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmBootGuardLibNull/PeiDxeSmmBootGuardLibNull.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdSoftwareGuardEnable == TRUE
 SoftwareGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiDxeSoftwareGuardLib/PeiDxeSoftwareGuardLib.inf
!else
 SoftwareGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/BaseSoftwareGuardLibNull/BaseSoftwareGuardLibNull.inf
!endif
!endif

!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
 CpuMailboxLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmCpuMailboxLib/PeiDxeSmmCpuMailboxLib.inf
!else
 CpuMailboxLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/BaseCpuMailboxLibNull/BaseCpuMailboxLibNull.inf
!endif
#
# Me
#
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
 MeTypeLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiDxeMeTypeLib/PeiDxeMeTypeLib.inf
 PttPtpLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiDxePttPtpLib/PeiDxePttPtpLib.inf
 MeShowBufferLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiDxeMeShowBufferLib/PeiDxeMeShowBufferLib.inf
 MeFwStsLib|$(PLATFORM_SI_PACKAGE)/Me/Library/BaseMeFwStsLib/BaseMeFwStsLib.inf
 HeciInitLib|$(PLATFORM_SI_PACKAGE)/Me/Library/Private/PeiDxeHeciInitLib/PeiDxeHeciInitLib.inf
 AlertStandardFormatLib|$(PLATFORM_SI_PACKAGE)/Me/Library/Private/PeiDxeAlertStandardFormatLib/PeiDxeAlertStandardFormatLib.inf
 MeChipsetLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiDxeMeChipsetLib/PeiDxeMeChipsetLib.inf
!endif

#
# Pch
#
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
 SecPchLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/SecPchLib/SecPchLib.inf
 PchSerialIoUartLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchSerialIoUartLib/PeiDxeSmmPchSerialIoUartLib.inf
 PchEspiLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchEspiLib/PeiDxeSmmPchEspiLib.inf
 PchAlternateAccessModeLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmPchAlternateAccessModeLib/PeiDxeSmmPchAlternateAccessModeLib.inf
 PchXhciLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmPchXhciLib/PeiDxeSmmPchXhciLib.inf
!endif
 PchCycleDecodingLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchCycleDecodingLib/PeiDxeSmmPchCycleDecodingLib.inf
 PchGbeLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchGbeLib/PeiDxeSmmPchGbeLib.inf
 PchHsioLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchHsioLib/PeiDxeSmmPchHsioLib.inf
 PchInfoLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchInfoLib/PeiDxeSmmPchInfoLib.inf
 PchP2sbLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchP2sbLib/PeiDxeSmmPchP2sbLib.inf
 PchPcieRpLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchPcieRpLib/PeiDxeSmmPchPcieRpLib.inf
 PchPcrLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchPcrLib/PeiDxeSmmPchPcrLib.inf
 PchPmcLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchPmcLib/PeiDxeSmmPchPmcLib.inf
 PchSbiAccessLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchSbiAccessLib/PeiDxeSmmPchSbiAccessLib.inf
 GpioLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmGpioLib/PeiDxeSmmGpioLib.inf
!if gSiPkgTokenSpaceGuid.PcdTraceHubEnable == TRUE
 TraceHubInitLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmTraceHubInitLib/PeiDxeSmmTraceHubInitLib.inf
!else
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
 TraceHubInitLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/BaseTraceHubInitLibNull/BaseTraceHubInitLibNull.inf
!endif
!endif
 PchSerialIoLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchSerialIoLib/PeiDxeSmmPchSerialIoLib.inf
 PchWdtCommonLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchWdtCommonLib/PeiDxeSmmPchWdtCommonLib.inf
 ResetSystemLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/BaseResetSystemLib/BaseResetSystemLib.inf
 SmbusLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/BaseSmbusLib/BaseSmbusLib.inf
 #private
 PchPciExpressHelpersLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmPchPciExpressHelpersLib/PeiDxeSmmPchPciExpressHelpersLib.inf
 PchInitCommonLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmPchInitCommonLib/PeiDxeSmmPchInitCommonLib.inf
 PchSmbusCommonLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmPchSmbusCommonLib/PeiDxeSmmPchSmbusCommonLib.inf
 PchSpiCommonLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/BasePchSpiCommonLib/BasePchSpiCommonLib.inf
 GpioPrivateLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmGpioPrivateLib/PeiDxeSmmGpioPrivateLib.inf
 I2cMasterCommonLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeI2cMasterCommonLib/PeiDxeI2cMasterCommonLib.inf
 PchPsfPrivateLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmPchPsfPrivateLib/PeiDxeSmmPchPsfPrivateLib.inf
 PchPsfLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchPsfLib/PeiDxeSmmPchPsfLib.inf
 RstPrivateLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiDxeSmmRstPrivateLib/PeiDxeSmmRstPrivateLib.inf
 PeiHybridStorageLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiHybridStorageLib/PeiHybridStorageLib.inf


#
# SA
#
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
 SecSaLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/SecSaLib/SecSaLib.inf
!endif
 SaPlatformLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/PeiDxeSmmSaPlatformLib/PeiDxeSmmSaPlatformLib.inf

#
# Memory
#
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
 MemoryAddressEncodeDecodeLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/MemoryInit/Library/PeiDxeSmmMemoryAddressEncodeDecodeLib/PeiDxeSmmMemoryAddressEncodeDecodeLib.inf
!endif

