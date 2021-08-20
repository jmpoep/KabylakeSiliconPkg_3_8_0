## @file
#  Component description file for the SkyLake SiPkg PEI libraries.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2012 - 2017 Intel Corporation.
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
# Silicon Init Pei Library
#
 SiPolicyLib|$(PLATFORM_SI_PACKAGE)/Library/PeiSiPolicyLib/PeiSiPolicyLib.inf
 SiConfigBlockLib|$(PLATFORM_SI_PACKAGE)/Library/BaseSiConfigBlockLib/BaseSiConfigBlockLib.inf

#
# Pch
#
 PchPolicyLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiPchPolicyLib/PeiPchPolicyLib.inf
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
 PchInitLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiPchInitLib/PeiPchInitLib.inf
 PchRcLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiPchRcLib/PeiPchRcLib.inf
!if gSiPkgTokenSpaceGuid.PcdS3Enable == TRUE
 PchSmmControlLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiPchSmmControlLib/PeiPchSmmControlLib.inf
!else
 PchSmmControlLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiPchSmmControlLibNull/PeiPchSmmControlLibNull.inf
!endif
 PeiI2cMasterLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/Private/PeiI2cMasterLib/PeiI2cMasterLib.inf
!endif # PcdMinTreeEnable
!if gSiPkgTokenSpaceGuid.PcdOcWdtEnable == TRUE
 OcWdtLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiOcWdtLib/PeiOcWdtLib.inf
!else
 OcWdtLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiOcWdtLibNull/PeiOcWdtLibNull.inf
!endif
 ResetSystemLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiResetSystemLib/PeiResetSystemLib.inf
 PchResetLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiPchResetLib/PeiPchResetLib.inf

#
# Cpu
#
 CpuCommonLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiDxeSmmCpuCommonLib/PeiDxeSmmCpuCommonLib.inf
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
 CpuInitLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuInitLib/PeiCpuInitLib.inf
!if gSiPkgTokenSpaceGuid.PcdS3Enable == TRUE
 CpuS3Lib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuS3Lib/PeiCpuS3Lib.inf
!else
 CpuS3Lib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuS3LibNull/PeiCpuS3LibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdBiosGuardEnable == TRUE
 BiosGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiBiosGuardLib/PeiBiosGuardLib.inf
!else
 BiosGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiBiosGuardLibNull/PeiBiosGuardLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdOverclockEnable == TRUE
 CpuOcLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuOcLib/PeiCpuOcLib.inf
 CpuOcInitLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuOcInitLib/PeiCpuOcInitLib.inf
!else
 CpuOcLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuOcLibNull/PeiCpuOcLibNull.inf
 CpuOcInitLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuOcInitLibNull/PeiCpuOcInitLibNull.inf
!endif
 CpuPowerMgmtLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiCpuPowerMgmtLib/PeiCpuPowerMgmtLib.inf
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
!endif
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
!if gSiPkgTokenSpaceGuid.PcdSoftwareGuardEnable == TRUE
 SoftwareGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiDxeSoftwareGuardLib/PeiDxeSoftwareGuardLib.inf
!else
 SoftwareGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/BaseSoftwareGuardLibNull/BaseSoftwareGuardLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdSmbiosEnable == TRUE
 SmbiosCpuLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiSmbiosCpuLib/PeiSmbiosCpuLib.inf
!else
 SmbiosCpuLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/Private/PeiSmbiosCpuLibNull/PeiSmbiosCpuLibNull.inf
!endif
!endif

#
# Me
#
 PeiMePolicyLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiMePolicyLib/PeiMePolicyLib.inf
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
 PeiMeLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiMeLib/PeiMeLib.inf
 MeInitLib|$(PLATFORM_SI_PACKAGE)/Me/Library/Private/PeiMeInitLib/PeiMeInitLib.inf
!if gSiPkgTokenSpaceGuid.PcdAmtEnable == TRUE
 PeiAmtPolicyLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiAmtPolicyLib/PeiAmtPolicyLib.inf
 PeiAmtLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiAmtLib/PeiAmtLib.inf
 ActiveManagementLib|$(PLATFORM_SI_PACKAGE)/Me/Library/Private/PeiActiveManagementLib/PeiActiveManagementLib.inf
!else
 PeiAmtPolicyLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiAmtPolicyLibNull/PeiAmtPolicyLibNull.inf
 PeiAmtLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiAmtLibNull/PeiAmtLibNull.inf
 ActiveManagementLib|$(PLATFORM_SI_PACKAGE)/Me/Library/Private/PeiActiveManagementLibNull/PeiActiveManagementLibNull.inf
!endif
!endif

#
# SA
#
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
!if gSiPkgTokenSpaceGuid.PcdSsaFlagEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdEvLoaderEnable == TRUE
 EvLoaderLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/MemoryInit/Library/Private/PeiEvLoaderLib/PeiEvLoaderLib.inf
!else
 EvLoaderLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/MemoryInit/Library/Private/PeiEvLoaderLibNull/PeiEvLoaderLibNull.inf
!endif
!else
 EvLoaderLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/MemoryInit/Library/Private/PeiEvLoaderLibNull/PeiEvLoaderLibNull.inf
!endif

 MemoryInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/MemoryInit/Library/Private/PeiMemoryInitLib/PeiMemoryInitLib.inf


!if gSiPkgTokenSpaceGuid.PcdSgEnable == TRUE
 SwitchableGraphicsInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSwitchableGraphicsInitLib/PeiSwitchableGraphicsInitLib.inf
!else
 SwitchableGraphicsInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSwitchableGraphicsInitLibNull/PeiSwitchableGraphicsInitLibNull.inf
!endif
 SaInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/PeiSaInitLib/PeiSaInitLib.inf
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
!if gSiPkgTokenSpaceGuid.PcdS3Enable == TRUE
 SmmAccessLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/PeiSmmAccessLib/PeiSmmAccessLib.inf
!else
 SmmAccessLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/PeiSmmAccessLibNull/PeiSmmAccessLibNull.inf
!endif
!endif

  PeiSaPolicyLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/PeiSaPolicyLib/PeiSaPolicyLib.inf
#
# Cpu
#
 CpuPolicyLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiCpuPolicyLib/PeiCpuPolicyLib.inf
 CpuPolicyLibPreMem|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiCpuPolicyLibPreMem/PeiCpuPolicyLibPreMem.inf

