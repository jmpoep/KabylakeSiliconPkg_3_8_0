## @file
#  Component description file for the SkyLake SiPkg DXE drivers.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2012 - 2018 Intel Corporation.
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
# Common
#
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
  $(PLATFORM_SI_PACKAGE)/SiInit/Dxe/SiInitDxe.inf
!endif

#
# Pch
#
  $(PLATFORM_SI_PACKAGE)/Pch/PchInit/Dxe/PchInitDxe.inf
  $(PLATFORM_SI_PACKAGE)/Pch/ActiveBios/Dxe/ActiveBios.inf
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
  $(PLATFORM_SI_PACKAGE)/Pch/I2cMaster/Dxe/I2cMasterDxe.inf
  $(PLATFORM_SI_PACKAGE)/Pch/Spi/RuntimeDxe/PchSpiRuntime.inf
!endif
  $(PLATFORM_SI_PACKAGE)/Pch/SmmControl/RuntimeDxe/SmmControl.inf
  $(PLATFORM_SI_PACKAGE)/Pch/Reset/RuntimeDxe/PchResetRuntime.inf
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
  $(PLATFORM_SI_PACKAGE)/Pch/Smbus/Smm/PchSmbusSmm.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdSmmVariableEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Pch/Spi/Smm/PchSpiSmm.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
!if gSiPkgTokenSpaceGuid.PcdSerialGpioEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Pch/SerialGpio/Dxe/PchSerialGpio.inf
!endif
!endif

!if gSiPkgTokenSpaceGuid.PcdAtaEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Pch/SataController/Dxe/SataController.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdSiCsmEnable != FALSE
  $(PLATFORM_SI_PACKAGE)/Pch/LegacyInterrupt/Dxe/LegacyInterrupt.inf
!endif


!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
  $(PLATFORM_SI_PACKAGE)/Pch/Wdt/Dxe/WdtDxe.inf
!endif
  $(PLATFORM_SI_PACKAGE)/Pch/Smbus/Dxe/PchSmbusDxe.inf
  $(PLATFORM_SI_PACKAGE)/Pch/PchSmiDispatcher/Smm/PchSmiDispatcher.inf
  $(PLATFORM_SI_PACKAGE)/Pch/PchInit/Smm/PchInitSmm.inf

#
# SystemAgent
#
  $(PLATFORM_SI_PACKAGE)/SystemAgent/SmmAccess/Dxe/SmmAccess.inf
  $(PLATFORM_SI_PACKAGE)/SystemAgent/SaInit/Dxe/SaInitDxe.inf {
    <LibraryClasses>
      !if gSiPkgTokenSpaceGuid.PcdSiCsmEnable == TRUE
        NULL|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/Private/DxeLegacyRegionLib/DxeLegacyRegionLib.inf
      !endif
  }
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
  $(PLATFORM_SI_PACKAGE)/SystemAgent/BdatAccessHandler/Dxe/BdatAccessHandler.inf
!endif

#
# AdvancedFeaturesBegin
#
!if gSiPkgTokenSpaceGuid.PcdSgEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdAcpiEnable == TRUE
  $(PLATFORM_PACKAGE)/Board/KblG/AcpiTable/AltoAcpiTable.inf # KblGContent
  $(PLATFORM_SI_PACKAGE)/SystemAgent/AcpiTables/SwitchableGraphics/Peg/SgAcpiTables.inf
  $(PLATFORM_SI_PACKAGE)/SystemAgent/AcpiTables/SwitchableGraphics/Pch/SgAcpiTablesPch.inf
!endif
!endif
#
# AdvancedFeaturesEnd
#
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
  $(PLATFORM_SI_PACKAGE)/SystemAgent/SaInit/Smm/SaLateInitSmm.inf {
    <LibraryClasses>
      S3BootScriptLib|MdePkg/Library/BaseS3BootScriptLibNull/BaseS3BootScriptLibNull.inf
  }
!endif

!if gSiPkgTokenSpaceGuid.PcdAcpiEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
  $(PLATFORM_SI_PACKAGE)/SystemAgent/AcpiTables/SaAcpiTables.inf
  $(PLATFORM_SI_PACKAGE)/SystemAgent/AcpiTables/PegSsdt/PegSsdt.inf
!endif
  $(PLATFORM_SI_PACKAGE)/SystemAgent/AcpiTables/SaSsdt/SaSsdt.inf
!endif

  $(PLATFORM_SI_PACKAGE)/SystemAgent/PciHostBridge/Dxe/PciHostBridge.inf

#
# Cpu
#

!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
  $(PLATFORM_SI_PACKAGE)/Cpu/CpuInit/Dxe/CpuInitDxe.inf {
    <BuildOptions>
!if gSiPkgTokenSpaceGuid.PcdSourceDebugEnable == TRUE
      *_*_*_CC_FLAGS       = -DSOURCE_DEBUG_ENABLE
!endif
  }
!endif

!if gSiPkgTokenSpaceGuid.PcdBiosGuardEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Cpu/BiosGuard/Smm/BiosGuardServices.inf
!endif
#
# AdvancedFeaturesBegin
#
!if gSiPkgTokenSpaceGuid.PcdAcpiEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Cpu/AcpiTables/CpuAcpiTables.inf
!endif
#
# AdvancedFeaturesEnd
#
!if gSiPkgTokenSpaceGuid.PcdPpmEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Cpu/PowerManagement/Dxe/PowerMgmtDxe.inf
  $(PLATFORM_SI_PACKAGE)/Cpu/PowerManagement/Smm/PowerMgmtSmm.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdTxtEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Cpu/TxtInit/Dxe/TxtDxe.inf
!endif

#
# Me
#
  $(PLATFORM_SI_PACKAGE)/Me/MePlatformReset/RuntimeDxe/MePlatformReset.inf {
    <LibraryClasses>
      ResetSystemLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/DxeRuntimeResetSystemLib/DxeRuntimeResetSystemLib.inf
  }

!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
  $(PLATFORM_SI_PACKAGE)/Me/HeciInit/Dxe/HeciInit.inf
!if gSiPkgTokenSpaceGuid.PcdIntegratedTouchEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Me/IntegratedTouch/IntegratedTouch.inf
!endif
!endif

!if gSiPkgTokenSpaceGuid.PcdAmtEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Me/ActiveManagement/AlertStandardFormat/Dxe/AlertStandardFormatDxe.inf
  $(PLATFORM_SI_PACKAGE)/Me/ActiveManagement/AmtBootOptions/Dxe/ActiveManagement.inf
  $(PLATFORM_SI_PACKAGE)/Me/BiosExtensionLoader/Dxe/BiosExtensionLoader.inf
  $(PLATFORM_SI_PACKAGE)/Me/ActiveManagement/Sol/Dxe/SerialOverLan.inf
  $(PLATFORM_SI_PACKAGE)/Me/MeFwDowngrade/Dxe/MeFwDowngrade.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdPttEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Me/Ptt/Smm/PttHciSmm.inf
  !if gSiPkgTokenSpaceGuid.PcdAcpiEnable == TRUE
    $(PLATFORM_SI_PACKAGE)/Me/AcpiTables/MeSsdt/MeSsdt.inf
    $(PLATFORM_SI_PACKAGE)/Me/Ptt/Smm/Tpm2AcpiTables.inf
  !endif
!endif

!if gSiPkgTokenSpaceGuid.PcdJhiEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Me/Jhi/Dxe/JhiDxe.inf
!endif


!if gSiPkgTokenSpaceGuid.PcdMinTreeEnable == FALSE
#
# Hsti
#
  $(PLATFORM_SI_PACKAGE)/Hsti/Dxe/HstiSiliconDxe.inf {
    <LibraryClasses>
      HstiLib|$(PLATFORM_SI_PACKAGE)/Override/MdePkg/Library/DxeHstiLib/DxeHstiLib.inf  # SICO-KBL-0003
      Tpm2CommandLib|$(PLATFORM_SI_PACKAGE)/SampleCode/SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
  }
!endif
