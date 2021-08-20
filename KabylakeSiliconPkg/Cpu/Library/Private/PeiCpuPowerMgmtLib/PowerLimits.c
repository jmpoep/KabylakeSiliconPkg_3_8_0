/** @file
  This file contains power management configuration functions for processors.

  <b>Acronyms:</b>
     - PPM:  Processor Power Management
     - TM:   Thermal Monitor
     - IST:  Intel(R) Speedstep technology
     - HT:   Hyper-Threading Technology

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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

@par Specification
**/

#include "PowerMgmtCommon.h"
#include <Private/Library/CpuCommonLib.h>
#include <Ppi/SiPolicy.h>

GLOBAL_REMOVE_IF_UNREFERENCED PPM_CTDP_OVERRIDE_TABLE mSklUltPpmCtdpOverrideTable[]={
///  TDP  MSR PL1  MSR PL2   TdpUp   TdpUp   TdpNominal  TdpNominal  TdpDown   TdpDown  MSR PL4   CpuIdentifier (Optional)
///                          PL1     PL2     PL1         PL2         PL1       PL2
  { 450,  700,     1500,     0,      1500,   0,          1500,       0,        1500,    0,        0 },                /// 4.5W Sku Overrides
  { 1500, 2500,    2500,     0,      2500,   0,          2500,       0,        2500,    0,        CPU_SKL_U_2_2 },    /// 15W Sku Overrides 2+2 part
  { 1500, 2500,    3000,     0,      3000,   0,          3000,       0,        3000,    0,        CPU_SKL_U_2_3_E },  /// 15W Sku Overrides 2+3e part
  { 4500, 4500,    6000,     0,      6000,   0,          6000,       0,        6000,    0,        0 }                 /// 45W Sku Overrides
};

GLOBAL_REMOVE_IF_UNREFERENCED PPM_CTDP_OVERRIDE_TABLE mKblPpmCtdpOverrideTable[]={
///  TDP  MSR PL1  MSR PL2   TdpUp   TdpUp   TdpNominal  TdpNominal  TdpDown   TdpDown  MSR PL4   CpuIdentifier (Optional)
///                          PL1     PL2     PL1         PL2         PL1       PL2
  { 450,  450,     1500,     0,      1500,   0,          1500,       0,        1500,    3000,     KBL_Y_4PT5_WATT_2_2 },    /// 4.5W Y Sku Overrides
  { 500,  500,     1800,     0,      1800,   0,          1800,       0,        1800,    4000,     AML_Y_5_WATT_2_2 },       /// 5W AML Y 2+2
  { 700,  700,     2400,     0,      2400,   0,          2400,       0,        2400,    4000,     AML_Y_7_WATT_2_2 },       /// 7W AML Y 2+2
  { 700,  700,     3300,     0,      3300,   0,          3300,       0,        3300,    5000,     EnumAmlY7Watt42CpuId },   /// 7W AML Y 4+2
  { 1500, 1500,    2500,     0,      2500,   0,          2500,       0,        2500,    0,        CPU_KBL_U_2_2_V1 },       /// 15W U Sku Overrides 2+2 part
  { 1500, 1500,    3300,     0,      3300,   0,          3300,       0,        3300,    0,        CPU_KBL_U_2_3_E },        /// 15W U Sku Overrides 2+3e part
  { 1500, 1500,    2900,     0,      2900,   0,          2900,       0,        2900,    4300,     CPU_KBL_U_2_2_V2 },       /// 15W KBL-U Sku Overrides 2+2 part
  { 1500, 1500,    4400,     0,      4400,   0,          4400,       0,        4400,    7100,     CPU_KBL_R_U_4_2 },        /// 15W KBL-R U Sku Overrides 4+2 part
  { 4500, 0,       6000,     0,      0,      0,          6000,       0,        6000,    0,        0 },                      /// 45W H 4+2 Sku Overrides
  { 3500, 0,       5500,     0,      0,      0,          0,          0,        5500,    0,        0 },                      /// 35W S Sku Overrides
  { 3500, 3500,    4400,     0,      4400,   0,          4400,       0,        4400,    7200,     EnumCflS35Watt22CpuId },  /// 35W CFL-S 2+2
  { 3500, 3500,    6900,     0,      6900,   0,          6900,       0,        6900,    9000,     EnumCflS35Watt42CpuId },  /// 35W CFL-S 4+2
  { 3500, 3500,    9200,     0,      9200,   0,          9200,       0,        9200,    12000,    EnumCflS35Watt62CpuId },  /// 35W CFL-S 6+2
  { 3500, 3500,    9200,     0,      9200,   0,          9200,       0,        9200,    12000,    EnumCflS35Watt82CpuId },  /// 35W CFL-S 8+2
  { 5100, 5100,    9000,     0,      9000,   0,          9000,       0,        9000,    10600,    EnumKblS51Watt22Cpuid },  /// 51W KBL-S 2+2
  { 5400, 5100,    9000,     0,      9000,   0,          9000,       0,        9000,    10600,    EnumKblS54Watt22Cpuid }   /// 54W KBL-S 2+2
};


GLOBAL_REMOVE_IF_UNREFERENCED PPM_OVERRIDE_TABLE mPpmOverrideTable[]={
/// TDP   MSR PL1  MSR PL2  MSR PL4   CpuIdentifier (Optional)
  { 3500, 3500,     4400,    7200,    EnumCflS35Watt22CpuId },  /// 35W CFL-S 2+2
  { 3500, 3500,     6900,    9000,    EnumCflS35Watt42CpuId },  /// 35W CFL-S 4+2
  { 3500, 3500,     9200,   12000,    EnumCflS35Watt62CpuId },  /// 35W CFL-S 6+2
  { 3500, 3500,     9200,   12000,    EnumCflS35Watt82CpuId },  /// 35W CFL-S 8+2
  { 5400, 5400,     5900,    7400,    EnumCflS54Watt22CpuId },  /// 54W CFL-S
  { 5800, 5800,     5900,    7400,    EnumCflS58Watt22CpuId },  /// 58W CFL-S
  { 6200, 6200,     9000,   10600,    EnumCflS62Watt42CpuId },  /// 62W CFL-S 4+2
  { 6200, 6200,     9000,   10600,    EnumCflS62Watt42CpuId },  /// 62W CFL-S 4+2
  { 6500, 6500,     9000,   10600,    EnumCflS65Watt42CpuId },  /// 65W CFL-S 4+2
  { 6500, 6500,    12200,   15900,    EnumCflS65Watt62CpuId },  /// 65W CFL-S 6+2
  { 6500, 6500,    20000,   25800,    EnumCflS65Watt82CpuId },  /// 65W CFL-S 8+2
  { 7100, 7100,    10000,   13400,    EnumCflS71Watt42CpuId },  /// 71W CFL-S 4+2 workstation
  { 8000, 8000,    11200,   15400,    EnumCflS80Watt62CpuId },  /// 80W CFL-S 6+2 workstation
  { 8000, 8000,    21000,   26600,    EnumCflS80Watt82CpuId },  /// 80W CFL-S 8+2 workstation
  { 9500, 9500,    10000,   15100,    EnumCflS95Watt42CpuId },  /// 95W CFL-S 4+2
  { 9500, 9500,    13100,   16400,    EnumCflS95Watt62CpuId },  /// 95W CFL-S 6+2
  { 9500, 9500,    21000,   26600,    EnumCflS95Watt82CpuId },  /// 95W CFL-S 8+2
  { 3500, 3500,     6900,    9000,    EnumKblS35Watt22Cpuid },  /// 35W KBL-S 2+2
  { 6000, 6000,        0,       0,    EnumKblS60Watt22Cpuid },  /// 60W KBL-S 2+2
  { 3500, 3500,     6900,    9000,    EnumKblS35Watt42Cpuid },  /// 35W KBL-S 4+2
  { 6500, 6500,     9000,   10600,    EnumKblS65Watt42Cpuid },  /// 65W KBL-S 4+2
  { 9500, 9100,    10000,   15100,    EnumKblS95Watt42Cpuid },  /// 95W KBL-S 4+2
  { 9900, 9900,        0,       0,    EnumKblS99Watt42Cpuid },  /// 99W KBL-S 4+2
  { 500,  500,     1800,     4000,    EnumAmlY5Watt22CpuId  },  /// 5W AML Y 2+2
  { 700,  700,     2400,     4000,    EnumAmlY7Watt22CpuId  },  /// 7W AML Y 2+2
  { 700,  700,     3300,     5000,    EnumAmlY7Watt2f2CpuId },  /// 7W AML Y 2f+2
  { 700,  700,     3300,     5000,    EnumAmlY7Watt42CpuId  },  /// 7W AML Y 4+2
  { 4500, 4500,    6300,     9000,    EnumSklH45Watt42Cpuid }   /// 45W SKL H 4+2
};

///
/// The number of additional cTDP levels as read from MSR 0xCE.
/// 0 - no cTDP support
/// 1 - one additional level
/// 2 - two additional levels
///
UINT8 mCpuConfigTdpLevels;

/**
  Configurable TDP BIOS Initialization

  @exception EFI_UNSUPPORTED  Ctdp not Supported
  @retval EFI_SUCCESS         Ctdp Initiation done
**/
EFI_STATUS
InitializeConfigurableTdp (
  VOID
  )
{
  EFI_STATUS Status;
  UINTN      Index;

  if (gCpuGlobalNvsAreaConfig == NULL) {
    DEBUG ((DEBUG_INFO, "PPM:: ConfigTDP Require gCpuGlobalNvsAreaConfig.\n"));
    return EFI_UNSUPPORTED;
  }
  ///
  /// Intialize PPM Global NVS with custom CTDP level settings or CPU provided.
  ///
  Status = InitConfigurableTdpSettings ();
  if (Status != EFI_SUCCESS) {
    return EFI_UNSUPPORTED;
  }

  ///
  /// In case of LFM == TDP Down Ratio/Tdp Nominal , consider TDP Down TAR as the new LFM to insert fake P state.
  ///
  for (Index = 0; Index < (gCpuGlobalNvsAreaConfig->Area->CtdpLevelsSupported); Index++) {
    if (mMinBusRatio == gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpTar+1) {
      mMinBusRatio = gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpTar;
      DEBUG ((DEBUG_INFO, "PPM:: mMinBusRatio Modified for Ctdp %d\n", mMinBusRatio));
    }
  }

  return EFI_SUCCESS;
}

/**
  Verify and fix Custom Power Limit values

  @param[in] CustomPowerLimit  Custom Power Limit value
  @param[in] CustomPlUnit  Custom Power Limit Unit
**/
UINT16
VerifyAndFixCustomPowerLimit (
  IN UINT32 CustomPowerLimit,
  IN UINT16 CustomPlUnit
  )
{
  UINT16 ConvertedPowerLimit;
  UINT16 CpuConvertedPowerLimitMaxLimit;

  ConvertedPowerLimit = (UINT16) ((CustomPowerLimit * mProcessorPowerUnit) / CustomPlUnit);
  if (mPackageMaxPower == 0 && ConvertedPowerLimit >= mPackageMinPower) {
    ///
    ///  If PACKAGE_POWER_SKU_MSR [46:32] = 0 means there is no upper limit ( since this field is 15 bits, the max value is 2^15 - 1 )
    ///
    CpuConvertedPowerLimitMaxLimit = (UINT16) (LShiftU64 (2, 15) - 1);
    if (ConvertedPowerLimit > CpuConvertedPowerLimitMaxLimit) {
      ///
      /// If new Power Limit 1 is > CpuConvertedPowerLimit1MaxLimit, program Power Limit 1 to CpuConvertedPowerLimit1MaxLimit
      ///
      ConvertedPowerLimit = CpuConvertedPowerLimitMaxLimit;
    }
  } else if (mPackageMinPower == 0 && ConvertedPowerLimit > 0 && ConvertedPowerLimit <= mPackageMaxPower) {
    ///
    ///  If PACKAGE_POWER_SKU_MSR [30:16] = 0 means there is no lower limit
    ///
    ConvertedPowerLimit = (UINT16) ((CustomPowerLimit * mProcessorPowerUnit) / CustomPlUnit);
  } else {
    ///
    /// Power Limit 1 needs to be between mPackageMinPower and mPackageMaxPower
    ///
    CpuConvertedPowerLimitMaxLimit = mPackageMaxPower;
    if (ConvertedPowerLimit < mPackageMinPower) {
      ///
      /// If new Power Limit 1 is < mPackageMinPower, program Power Limit 1 to mPackageMinPower
      ///
      ConvertedPowerLimit = mPackageMinPower;
    } else if (ConvertedPowerLimit > CpuConvertedPowerLimitMaxLimit) {
      ///
      /// If new Power Limit 1 is > mPackageMaxPower, program Power Limit 1 to mPackageMaxPower
      ///
      ConvertedPowerLimit = CpuConvertedPowerLimitMaxLimit;
    }
  }

  return ConvertedPowerLimit;
}

/**
  Verify and fix Custom Ratio values
  Custom Ratio should be between MaxTurboFrequency and LFM

  @param[in] CustomRatio  Custom Ratio value
**/
UINT8
VerifyAndFixCustomRatio (
  IN UINT8 CustomRatio
  )
{
  if (CustomRatio > mTurboBusRatio) {
    ///
    /// Use HFM as max value if Turbo is not supported
    ///
    if (mTurboBusRatio == 0) {
      CustomRatio = (UINT8) mMaxBusRatio;
    } else {
      CustomRatio = (UINT8) mTurboBusRatio;
    }
  } else if (CustomRatio < mMinBusRatio) {
    ///
    /// Use LFM as min value
    ///
    CustomRatio = (UINT8) mMinBusRatio;
  }

  return CustomRatio;
}

/**
  Initalizes CTDP BIOS settings from silicon defaults and overrides custom cTDP settings if needed

  @exception EFI_UNSUPPORTED  Ctdp not supported
  @retval EFI_SUCCESS         Ctdp Settings Initialized successfully from MSRs
**/
EFI_STATUS
InitConfigurableTdpSettings (
  VOID
  )
{
  MSR_REGISTER TempMsr;
  UINTN        Index;
  UINT16       CpuConfigTdpNominalTdp;
  UINT16       CpuConfigTdpLevel1Tdp;
  UINT16       CpuConfigTdpLevel2Tdp;
  UINT8        CpuConfigTdpNominalRatio;
  UINT8        CpuConfigTdpLevel1Ratio;
  UINT8        CpuConfigTdpLevel2Ratio;

  ///
  /// Get the number of configurable TDP Levels supported
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_PLATFORM_INFO);
  TempMsr.Qword &= V_CONFIG_TDP_NUM_LEVELS_MASK;
  mCpuConfigTdpLevels = (UINT8) RShiftU64 (TempMsr.Qword, N_MSR_PLATFORM_INFO_CONFIG_TDP_NUM_LEVELS_OFFSET);
  DEBUG ((DEBUG_INFO, "PPM:: ConfigTDP Supported Levels=%d\n", mCpuConfigTdpLevels));
  ///
  /// Return if ConfigTDP Levels not supported
  ///
  if (mCpuConfigTdpLevels == 0) {
    DEBUG ((DEBUG_INFO, "PPM:: ConfigTDP Levels not supported\n"));
    return EFI_UNSUPPORTED;
  }
  gCpuGlobalNvsAreaConfig->Area->CtdpLevelsSupported    = (UINT8) mCpuConfigTdpLevels + 1;
  gCpuGlobalNvsAreaConfig->Area->ConfigTdpBootModeIndex = (UINT8) gCpuPowerMgmtTestConfig->ConfigTdpLevel;
  ///
  /// Get PKG_TDP for Config TDP Nominal
  ///
  TempMsr.Qword             = AsmReadMsr64 (MSR_CONFIG_TDP_NOMINAL);
  CpuConfigTdpNominalRatio  = (UINT8) (TempMsr.Dwords.Low & CONFIG_TDP_NOMINAL_RATIO_MASK);
  CpuConfigTdpNominalTdp    = mPackageTdp;
  DEBUG ((DEBUG_INFO, "PPM:: ConfigTDP Nominal Ratio=%d Tdp=%d\n", CpuConfigTdpNominalRatio, CpuConfigTdpNominalTdp));
  ///
  /// Set Level0 as Tdp Nominal
  ///
  gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpPowerLimit1 = mPackageTdp;
  gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpPowerLimit2 = GetCtdpPowerLimit2 (gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpPowerLimit1);
  if (IS_SA_DEVICE_ID_MOBILE (mProcessorFlavor) || IS_SA_DEVICE_ID_HALO (mProcessorFlavor)) {
    gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpPowerLimitWindow = MB_POWER_LIMIT1_TIME_DEFAULT;
  } else {
    gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpPowerLimitWindow = DT_POWER_LIMIT1_TIME_DEFAULT;
  }
  gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpTar = (UINT8) (CpuConfigTdpNominalRatio - 1);
  gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpCtc = CONFIG_TDP_NOMINAL;
  ///
  /// Get PKG_TDP and Ratio for Config TDP Level1
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_CONFIG_TDP_LVL1);
  CpuConfigTdpLevel1Ratio = (UINT8) RShiftU64 (
                                      TempMsr.Qword & CONFIG_TDP_LVL1_RATIO_MASK,
                                      CONFIG_TDP_LVL1_RATIO_OFFSET
                                      );
  CpuConfigTdpLevel1Tdp = (UINT16) (TempMsr.Dwords.Low & CONFIG_TDP_LVL1_PKG_TDP_MASK);
  DEBUG ((DEBUG_INFO, "PPM:: ConfigTDP Level1 Ratio=%d Tdp=%d\n", CpuConfigTdpLevel1Ratio, CpuConfigTdpLevel1Tdp));
  ///
  /// Set Level 1
  ///
  Index = 1;
  if (CpuConfigTdpLevel1Ratio != 0) {
    gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimit1 = CpuConfigTdpLevel1Tdp;
    gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimit2 = GetCtdpPowerLimit2 (gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimit1);
    gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimitWindow = gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpPowerLimitWindow;
    gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpTar = (UINT8) (CpuConfigTdpLevel1Ratio - 1);
    gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpCtc = CONFIG_TDP_LEVEL1;
    Index++;
  }
  ///
  /// If two levels are supported or Level1 was not valid
  /// then read Level2 registers
  ///
  if (mCpuConfigTdpLevels == CONFIG_TDP_LEVEL2 || CpuConfigTdpLevel1Ratio == 0) {
    ///
    /// Get PKG_TDP and Ratio for Config TDP Level2
    ///
    TempMsr.Qword = AsmReadMsr64 (MSR_CONFIG_TDP_LVL2);
    CpuConfigTdpLevel2Ratio = (UINT8) RShiftU64 (
                                        TempMsr.Qword & CONFIG_TDP_LVL2_RATIO_MASK,
                                        CONFIG_TDP_LVL2_RATIO_OFFSET
                                        );
    CpuConfigTdpLevel2Tdp = (UINT16) (TempMsr.Dwords.Low & CONFIG_TDP_LVL2_PKG_TDP_MASK);
    DEBUG ((DEBUG_INFO, "PPM:: ConfigTDP Level2 Ratio=%d Tdp=%d\n", CpuConfigTdpLevel2Ratio, CpuConfigTdpLevel2Tdp));
    ///
    /// Set Level2
    ///
    gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimit1 = CpuConfigTdpLevel2Tdp;
    gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimit2 = GetCtdpPowerLimit2 (gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimit1);
    gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimitWindow = gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpPowerLimitWindow;
    gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpTar = (UINT8) (CpuConfigTdpLevel2Ratio - 1);
    gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpCtc = CONFIG_TDP_LEVEL2;
  }

  ///
  /// Override any custom ConfigTdp information if applicable. This will only update if a custom
  /// setting change is detected, otherwise the CPU based default cTDP  settings will be applied.
  ///
  for (Index = 0; Index < MAX_CUSTOM_CTDP_ENTRIES; Index++) {
    ///
    /// Verify and fix Custom configured CTDP Levels PL1
    ///
    if (gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomPowerLimit1 != 0) {
      gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomPowerLimit1 = VerifyAndFixCustomPowerLimit (gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomPowerLimit1,mCustomPowerUnit);
      gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimit1 = (UINT16) gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomPowerLimit1;
    }

    ///
    /// Ctdp PL1 Time Window
    ///
    if (gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomPowerLimit1Time != 0) {
      gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimitWindow = (UINT8) gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomPowerLimit1Time;
    }

    ///
    /// Verify and fix Custom configured CTDP Levels PL2
    ///
    if (gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomPowerLimit2 != 0) {
      gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomPowerLimit2 = VerifyAndFixCustomPowerLimit (gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomPowerLimit2,mCustomPowerUnit);
      gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimit2 = (UINT16) gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomPowerLimit2;
    }

    ///
    /// cTDP Turbo Activation Ratio
    ///
    if (gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomTurboActivationRatio != 0) {
      gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomTurboActivationRatio = VerifyAndFixCustomRatio ((UINT8) gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomTurboActivationRatio+1)-1;
      gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpTar = (UINT8) gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomTurboActivationRatio;
    }
  }

  return EFI_SUCCESS;
}

/**
  Get Power Limit2 based on Power Limit1 on Config TDP

  @param[in] PowerLimit1  Power Limit 1 Value

  @retval Calculated Power Limit2 value
**/
UINT16
GetCtdpPowerLimit2 (
  IN UINT16 PowerLimit1
  )
{
  UINT16 ConvertedPowerLimit2;
  UINT16 Multiplier;

  ///
  /// By default,for Mobile & Desktop Processors: Short duration Power Limit  = 1.25 * Package TDP
  ///
  Multiplier = 125;
  ///
  /// For XE/non-ULV skus Configure PL2 as (1.25 x cTDP).
  ///
  ConvertedPowerLimit2 = EFI_IDIV_ROUND ((Multiplier * PowerLimit1), 100);

  return ConvertedPowerLimit2;
}

/**
  Patch Fvid Table with Ctdp Tar ratio and Tar-1 Ratio

  @param[in] FvidPointer  Pointer to Fvid Table
**/
VOID
CtdpPatchFvidTable (
  IN OUT FVID_TABLE *FvidPointer
  )
{
  UINTN PssIndex;
  UINTN Index;
  UINTN TempRatio;

  ///
  /// Check and patch Fvid table for TAR ratios
  ///
  for (Index = 0; Index < gCpuGlobalNvsAreaConfig->Area->CtdpLevelsSupported; Index++) {
    TempRatio = gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpTar;
    for (PssIndex = 1; PssIndex < FvidPointer[0].FvidHeader.EistStates; PssIndex++) {
      if (FvidPointer[PssIndex].FvidState.BusRatio < TempRatio) {
        if (FvidPointer[PssIndex - 1].FvidState.BusRatio != TempRatio) {
          ///
          /// If Tar not Found ,Replace Turbo Active ratio at PssIndex-1
          ///
          CtdpReplaceFvidRatio (FvidPointer, PssIndex - 1, TempRatio);
          DEBUG ((DEBUG_INFO, " TAR Ratio Replace at %x with %x \n",PssIndex - 1,TempRatio));
        }
        break;
      }
    }
  }
  ///
  /// Check and patch Fvid table for CTDP ratios.
  /// This is done separately to make sure Ctdp ratios are not override by Tar ratios
  /// when ctdp ratios are adjacent
  ///
  for (Index = 0; Index < gCpuGlobalNvsAreaConfig->Area->CtdpLevelsSupported; Index++) {
    TempRatio = gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpTar + 1;
    for (PssIndex = 1; PssIndex < FvidPointer[0].FvidHeader.EistStates; PssIndex++) {

      if (FvidPointer[PssIndex].FvidState.BusRatio == TempRatio) {
        gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPpc = (UINT8) FvidPointer[PssIndex].FvidState.State;
      }

      if (FvidPointer[PssIndex].FvidState.BusRatio < TempRatio) {
        if (FvidPointer[PssIndex - 1].FvidState.BusRatio == TempRatio) {
          ///
          /// Found Turbo Active ratio at PssIndex-1
          ///
          gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPpc = (UINT8) FvidPointer[PssIndex - 1].FvidState.State;
          break;
        } else {
          ///
          /// If Tar not Found, Replace Turbo Active ratio at PssIndex-1
          ///
          CtdpReplaceFvidRatio (FvidPointer, PssIndex - 1, TempRatio);
          gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPpc = (UINT8) FvidPointer[PssIndex - 1].FvidState.State;
          DEBUG ((DEBUG_INFO, " CTDP Ratio Replace at %x with %x \n",PssIndex - 1,TempRatio));
          break;
        }
      }
    }
  }
}

/**
  Patch Fvid Table with Ctdp Tar ratio and Tar-1 Ratio for Legacy OS

  @param[in] FvidPointer  Pointer to Fvid Table
**/
VOID
CtdpPatchFvidTableforLimitPstate (
  IN OUT FVID_TABLE *FvidPointer
  )
{
  UINTN PssIndex;
  UINTN Index;
  UINTN TempRatio;

  ///
  /// Check and patch Fvid table for TAR ratios
  ///
  for (Index = 0; Index < gCpuGlobalNvsAreaConfig->Area->CtdpLevelsSupported; Index++) {
    TempRatio = gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpTar;
    for (PssIndex = 1; PssIndex < LPSS_FVID_MAX_STATES; PssIndex++) {
      if (FvidPointer[PssIndex].FvidState.Limit16BusRatio < TempRatio) {
        if (FvidPointer[PssIndex - 1].FvidState.Limit16BusRatio != TempRatio) {
          ///
          /// If Tar not Found ,Replace Turbo Active ratio at PssIndex-1
          ///
          CtdpReplaceFvidRatio (FvidPointer, PssIndex - 1, TempRatio);
          DEBUG ((DEBUG_INFO, " TAR Ratio Replace at %x with %x \n",PssIndex - 1,TempRatio));
        }
        break;
      }
    }
  }
  ///
  /// Check and patch Fvid table for CTDP ratios.
  /// This is done separately to make sure Ctdp ratios are not override by Tar ratios
  /// when ctdp ratios are adjacent
  ///
  for (Index = 0; Index < gCpuGlobalNvsAreaConfig->Area->CtdpLevelsSupported; Index++) {
    TempRatio = gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpTar + 1;
    for (PssIndex = 1; PssIndex < LPSS_FVID_MAX_STATES; PssIndex++) {

      if (FvidPointer[PssIndex].FvidState.Limit16BusRatio == TempRatio) {
        gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPpc = (UINT8) FvidPointer[PssIndex].FvidState.Limit16State;
      }

      if (FvidPointer[PssIndex].FvidState.Limit16BusRatio < TempRatio) {
        if (FvidPointer[PssIndex - 1].FvidState.Limit16BusRatio == TempRatio) {
          ///
          /// Found Turbo Active ratio at PssIndex-1
          ///
          gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPpc = (UINT8) FvidPointer[PssIndex - 1].FvidState.Limit16State;
          break;
        } else {
          ///
          /// If Tar not Found, Replace Turbo Active ratio at PssIndex-1
          ///
          CtdpReplaceFvidRatio (FvidPointer, PssIndex - 1, TempRatio);
          gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPpc = (UINT8) FvidPointer[PssIndex - 1].FvidState.Limit16State;
          DEBUG ((DEBUG_INFO, " CTDP Ratio Replace at %x with %x \n",PssIndex - 1,TempRatio));
          break;
        }
      }
    }
  }
}

/**
  Replace P state with given ratio

  @param[in out] FvidPointer  Pointer to Fvid Table
  @param[in]     PssIndex     FVID table index of P state to be replaced
  @param[in]     Ratio        Target Ratio to put in
**/
VOID
CtdpReplaceFvidRatio (
  IN OUT FVID_TABLE *FvidPointer,
  UINTN             PssIndex,
  UINTN             Ratio
  )
{
  UINT64 wPower1;
  UINT64 wPower2;

  ///
  /// Replace new Ratio
  ///
  if (mOver16Pstates) {
    FvidPointer[PssIndex].FvidState.Limit16BusRatio = (UINT16) Ratio;
  } else {
    FvidPointer[PssIndex].FvidState.BusRatio = (UINT16) Ratio;
  }
  ///
  /// Calculate relative Power
  ///
  if (mOver16Pstates) {
    wPower1 = (mMaxBusRatio - FvidPointer[PssIndex].FvidState.Limit16BusRatio) * 625;
  } else {
    wPower1 = (mMaxBusRatio - FvidPointer[PssIndex].FvidState.BusRatio) * 625;
  }
  wPower1 = (110000 - wPower1);
  wPower1 = DivU64x32 (wPower1, 11);
  wPower1 = MultU64x64 (wPower1, wPower1);
  //
  // Power is calculated in milliwatts
  //
  if (mOver16Pstates) {
    wPower2 = (((FvidPointer[PssIndex].FvidState.Limit16BusRatio * 100) / mMaxBusRatio));
    wPower2 = DivU64x32 (MultU64x32 (MultU64x64 (wPower2, wPower1), mPackageTdpWatt), 10000000);
    FvidPointer[PssIndex].FvidState.Limit16Power = (UINT32) wPower2;
  } else {
    wPower2 = (((FvidPointer[PssIndex].FvidState.BusRatio * 100) / mMaxBusRatio));
    wPower2 = DivU64x32 (MultU64x32 (MultU64x64 (wPower2, wPower1), mPackageTdpWatt), 10000000);
    FvidPointer[PssIndex].FvidState.Power = (UINT32) wPower2;
  }
}

/**
  Configures following fields of MSR 0x610 based on user configuration:
    Configures Long duration Turbo Mode (power limit 1) power level and time window
    Configures Short duration turbo mode (power limit 2)
**/
VOID
ConfigurePowerLimitsNonConfigTdpSkus (
  VOID
  )
{
  MSR_REGISTER PackagePowerLimitMsr;
  PPM_OVERRIDE_TABLE *PpmOverrideTable;
  UINT16       ConvertedPowerLimit1;
  UINT8        ConvertedPowerLimit1Time;
  UINT16       ConvertedShortDurationPowerLimit;
  UINT16       CpuConvertedPowerLimit1MaxLimit;
  UINT16       CpuConvertedPowerLimit2MaxLimit;
  UINT16       SaDid;
  UINT16       Multiplier;
  UINTN        PciD0F0RegBase;
  UINTN        NoOfOverrides;
  UINTN        Index;
  UINTN        PackageTdp;
  UINT32       MchBar;

  CpuConvertedPowerLimit1MaxLimit = 0;
  CpuConvertedPowerLimit2MaxLimit = 0;
  ConvertedPowerLimit1Time        = 0;
  SaDid = MmioRead16 (MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN) + R_SA_MC_DEVICE_ID);

  ///
  /// Select override table
  ///
  PpmOverrideTable = mPpmOverrideTable;
  if (sizeof (PPM_CTDP_OVERRIDE_TABLE) != 0) {
    NoOfOverrides = (sizeof (mPpmOverrideTable)) / (sizeof (PPM_OVERRIDE_TABLE));
  }

  PackageTdp = (mPackageTdpWatt * 100);
  if ((mPackageTdp % mProcessorPowerUnit) != 0) {
   PackageTdp += ((mPackageTdp % mProcessorPowerUnit) * 100) / mProcessorPowerUnit;
  }

  ///
  /// By default, for Mobile & Desktop Processors: Short duration Power Limit  = 1.25 * Package TDP
  ///
  Multiplier = 125;
  ///
  ///  Check if TDP limits are programmable
  ///   - Platform Info MSR (0xCE) [29]
  ///
  if (mTdpLimitProgrammble) {
    PackagePowerLimitMsr.Qword = AsmReadMsr64 (MSR_PACKAGE_POWER_LIMIT);
    ///
    /// Initialize the Power Limit 1 and Power Limit 1 enable bit
    ///  - Power Limit 1: Turbo Power Limit MSR  [14:0]
    ///  - Power Limit 1 Enable: Turbo Power Limit MSR  [15]
    ///
    ///
    /// By default, program Power Limit 1 to Package TDP limit
    ///
    ConvertedPowerLimit1 = mPackageTdp;
    if (gCpuPowerMgmtBasicConfig->PowerLimit1 != AUTO) {
      ///
      /// gTurboSettings->PowerLimit1 is in mW or watts. We need to convert it to
      /// CPU Power unit, specified in PACKAGE_POWER_SKU_UNIT_MSR[3:0].
      /// Since we are converting from Watts to CPU power units, multiply by
      /// PACKAGE_POWER_SKU_UNIT_MSR[3:0].
      /// Refer to BWG 14.13.7 for Power Limit 1 limits.
      ///
      ConvertedPowerLimit1 = (UINT16) ((gCpuPowerMgmtBasicConfig->PowerLimit1 * mProcessorPowerUnit) / mCustomPowerUnit);
      if (mPackageMaxPower == 0 && ConvertedPowerLimit1 >= mPackageMinPower) {
        ///
        ///  If PACKAGE_POWER_SKU_MSR [46:32] = 0 means there is no upper limit ( since this field is 15 bits, the max value is 2^15 - 1 )
        ///
        CpuConvertedPowerLimit1MaxLimit = (UINT16) (LShiftU64 (2, 15) - 1);
        if (ConvertedPowerLimit1 > CpuConvertedPowerLimit1MaxLimit) {
          ///
          /// If new Power Limit 1 is > CpuConvertedPowerLimit1MaxLimit, program Power Limit 1 to CpuConvertedPowerLimit1MaxLimit
          ///
          ConvertedPowerLimit1 = CpuConvertedPowerLimit1MaxLimit;
        }
      } else if (mPackageMinPower == 0 && ConvertedPowerLimit1 > 0 && ConvertedPowerLimit1 <= mPackageMaxPower) {
        ///
        ///  If PACKAGE_POWER_SKU_MSR [30:16] = 0 means there is no lower limit
        ///
        ConvertedPowerLimit1 = (UINT16) ((gCpuPowerMgmtBasicConfig->PowerLimit1 * mProcessorPowerUnit) / mCustomPowerUnit);

      } else {
        ///
        /// Power Limit 1 needs to be between mPackageMinPower and mPackageMaxPower
        ///
        CpuConvertedPowerLimit1MaxLimit = mPackageMaxPower;

        if (ConvertedPowerLimit1 < mPackageMinPower) {
          ///
          /// If new Power Limit 1 is < mPackageMinPower, program Power Limit 1 to mPackageMinPower
          ///
          ConvertedPowerLimit1 = mPackageMinPower;
        } else if (ConvertedPowerLimit1 > CpuConvertedPowerLimit1MaxLimit) {
          ///
          /// If new Power Limit 1 is > mPackageMaxPower, program Power Limit 1 to mPackageMaxPower
          ///
          ConvertedPowerLimit1 = CpuConvertedPowerLimit1MaxLimit;
        }
      }
    } else {
      DEBUG ((DEBUG_INFO, "Power Limit 1 = AUTO\n"));
      for (Index = 0; Index < NoOfOverrides; Index++, PpmOverrideTable++) {
        if ( (PpmOverrideTable->CpuIdentifier == mCpuIdentifier) && (PpmOverrideTable->MsrPowerLimit1 != 0) ) {
          ///
          /// Some TDP segments have multiple CPU types. We need to check that the CpuIdentifier matches in this case.
          ///
          ConvertedPowerLimit1 = (UINT16)(PpmOverrideTable->MsrPowerLimit1 / 100) * 8;
        }
      }
    }
    PackagePowerLimitMsr.Dwords.Low &= ~POWER_LIMIT_MASK;
    PackagePowerLimitMsr.Dwords.Low |= (UINT32) ((ConvertedPowerLimit1) & POWER_LIMIT_MASK);
    DEBUG (
            (DEBUG_INFO,
             "New Power Limit 1  %d watt (%d in CPU power unit)\n",
             gCpuPowerMgmtBasicConfig->PowerLimit1,
             ConvertedPowerLimit1)
            );
    ///
    /// Force Power Limit 1 override to be enabled
    ///
    PackagePowerLimitMsr.Dwords.Low |= B_POWER_LIMIT_ENABLE;
    ///
    /// Program Power Limit 1 (Long Duration Turbo) Time Window
    ///  If PowerLimit1Time is AUTO OR If PowerLimit1Time is > MAX_POWER_LIMIT_1_TIME_IN_SECONDS
    ///    program default values
    ///
    if ((gCpuPowerMgmtBasicConfig->PowerLimit1Time == AUTO) ||
        (gCpuPowerMgmtBasicConfig->PowerLimit1Time > MAX_POWER_LIMIT_1_TIME_IN_SECONDS)
        ) {
      if (IS_SA_DEVICE_ID_MOBILE (mProcessorFlavor) || IS_SA_DEVICE_ID_HALO (mProcessorFlavor)) {
        ///
        /// For Mobile and Halo, default value is 28 seconds
        ///
        gCpuPowerMgmtBasicConfig->PowerLimit1Time = MB_POWER_LIMIT1_TIME_DEFAULT;
      } else {
        ///
        /// For Desktop, default value is 8 seconds
        ///
        gCpuPowerMgmtBasicConfig->PowerLimit1Time = DT_POWER_LIMIT1_TIME_DEFAULT;
      }

      ///
      /// CFL-S will use a PL1 Tau value of 28 seconds.
      ///
      if (IsCflSCpu ()) {
        gCpuPowerMgmtBasicConfig->PowerLimit1Time = MB_POWER_LIMIT1_TIME_DEFAULT;
      }
    }
    ConvertedPowerLimit1Time = GetConvertedTime (gCpuPowerMgmtBasicConfig->PowerLimit1Time, SecondsTimeWindowConvert);
    ///
    ///  Configure Power Limit 1 (Long Duration Turbo) time windows: PACKAGE_POWER_LIMIT_MSR 0x610 [23:17]
    ///
    PackagePowerLimitMsr.Dwords.Low &= ~POWER_LIMIT_1_TIME_MASK;
    PackagePowerLimitMsr.Dwords.Low |= (UINT32) (LShiftU64 (ConvertedPowerLimit1Time, 17) & POWER_LIMIT_1_TIME_MASK);
    ///
    /// Configure Power Limit 2 : PACKAGE_POWER_LIMIT_MSR 0x610 [46:32]
    /// gCpuPowerMgmtBasicConfig->PowerLimit2Power value is in mW or watts. We need to convert it to
    /// CPU Power unit, specified in PACKAGE_POWER_SKU_UNIT_MSR[3:0].
    /// Since we are converting from Watts to CPU power units, multiply by
    /// PACKAGE_POWER_SKU_UNIT_MSR[3:0]
    ///
    ConvertedShortDurationPowerLimit = (UINT16) ((gCpuPowerMgmtBasicConfig->PowerLimit2Power * mProcessorPowerUnit) / mCustomPowerUnit);
    PackagePowerLimitMsr.Dwords.High &= ~(POWER_LIMIT_MASK | B_POWER_LIMIT_ENABLE);
    ///
    /// If PowerLimit2 is AUTO OR if PowerLimit2 is > mPackageMaxPower OR if PowerLimit2 < mPackageMinPower
    /// program defaul values.
    ///
    CpuConvertedPowerLimit2MaxLimit = mPackageMaxPower;
    if (CpuConvertedPowerLimit2MaxLimit == 0) {
      CpuConvertedPowerLimit2MaxLimit = (UINT16) (LShiftU64 (2, 15) - 1);
    }

    if (gCpuPowerMgmtBasicConfig->PowerLimit2Power == AUTO) {
      ConvertedShortDurationPowerLimit = EFI_IDIV_ROUND ((Multiplier * mPackageTdp), 100);
      ///
      /// If Power Limit 2 is set to AUTO, then program PL2 defaults by sku
      ///
      DEBUG ((DEBUG_INFO, "Power Limit 2 overrides\n"));
      PpmOverrideTable = mPpmOverrideTable;
      for (Index = 0; Index < NoOfOverrides; Index++, PpmOverrideTable++) {
        if ( (PpmOverrideTable->CpuIdentifier == mCpuIdentifier) && (PpmOverrideTable->MsrPowerLimit2 != 0) ) {
          DEBUG ((DEBUG_INFO, "Power Limit 2 override found! PpmOverrideTable->MsrPowerLimit2 = %d\n", PpmOverrideTable->MsrPowerLimit2));
          ///
          /// Some TDP segments have multiple CPU types. We need to check that the CpuIdentifier matches in this case.
          ///
          ConvertedShortDurationPowerLimit = (UINT16)(PpmOverrideTable->MsrPowerLimit2 / 100) * 8;
          break;
        }
      }
    }
    if (ConvertedShortDurationPowerLimit > CpuConvertedPowerLimit2MaxLimit) {
      ConvertedShortDurationPowerLimit = CpuConvertedPowerLimit2MaxLimit;
    }
    if (ConvertedShortDurationPowerLimit < mPackageMinPower) {
      ConvertedShortDurationPowerLimit = mPackageMinPower;
    }
    PackagePowerLimitMsr.Dwords.High |= (UINT32) ((ConvertedShortDurationPowerLimit) & POWER_LIMIT_MASK);

    if (gCpuPowerMgmtBasicConfig->PowerLimit2 == TRUE) {
      PackagePowerLimitMsr.Dwords.High |= B_POWER_LIMIT_ENABLE;
    } else {
      ///
      /// When we disable Power Limit 2, we need to write power limit = 0
      ///
      PackagePowerLimitMsr.Dwords.High &= ~(POWER_LIMIT_MASK | B_POWER_LIMIT_ENABLE);
    }

    DEBUG (
            (DEBUG_INFO,
             "Short duration Power limit enabled, Power Limit = %d Watts\n",
             gCpuPowerMgmtBasicConfig->PowerLimit2Power)
            );

    DEBUG ((DEBUG_INFO,"MSR(610h)=%08X%08X\n",PackagePowerLimitMsr.Dwords.High,PackagePowerLimitMsr.Dwords.Low));

    AsmWriteMsr64 (MSR_PACKAGE_POWER_LIMIT, PackagePowerLimitMsr.Qword);
  }
  ///
  /// PL1 and PL2 BIOS Overrides for 57W Non CTDP SKU
  ///
  if (mPackageTdp == 57 * mProcessorPowerUnit) {
    PackagePowerLimitMsr.Qword = AsmReadMsr64 (MSR_PACKAGE_POWER_LIMIT);
    ///
    /// PL1=67W
    ///
    PackagePowerLimitMsr.Dwords.Low &= ~POWER_LIMIT_MASK;
    PackagePowerLimitMsr.Dwords.Low |= (UINT32) ((67 * mProcessorPowerUnit) & POWER_LIMIT_MASK);
    ///
    /// PL2=83.75W
    ///
    PackagePowerLimitMsr.Dwords.High &= ~POWER_LIMIT_MASK;
    PackagePowerLimitMsr.Dwords.High |= (UINT32) (((8375 * mProcessorPowerUnit) / 100) & POWER_LIMIT_MASK);

    AsmWriteMsr64 (MSR_PACKAGE_POWER_LIMIT, PackagePowerLimitMsr.Qword);
  }
  ///
  /// Set PACKAGE_POWER_LIMIT.CRITICAL_POWER_CLAMP_1(bit 16)
  ///
  PackagePowerLimitMsr.Qword = AsmReadMsr64 (MSR_PACKAGE_POWER_LIMIT);
  PackagePowerLimitMsr.Dwords.Low |= (UINT32) B_CRITICAL_POWER_CLAMP_ENABLE;
  AsmWriteMsr64 (MSR_PACKAGE_POWER_LIMIT, PackagePowerLimitMsr.Qword);

  ///
  /// Get the MCH space base address.
  ///
  PciD0F0RegBase  = MmPciBase (0, 0, 0);
  MchBar          = MmioRead32 (PciD0F0RegBase + 0x48) &~BIT0;

  ///
  /// Program MMIO PL1 clamp enable
  ///
  MmioOr32 (MchBar + MMIO_TURBO_POWER_LIMIT, B_CRITICAL_POWER_CLAMP_ENABLE);

  ///
  /// Pass the power limits of the non-CTDP part to the Global NVS Area for use by DPTF
  ///
  PackagePowerLimitMsr.Qword = AsmReadMsr64 (MSR_PACKAGE_POWER_LIMIT);
  gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpPowerLimit1      = (UINT16) (PackagePowerLimitMsr.Dwords.Low & POWER_LIMIT_MASK);
  gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpPowerLimit2      = (UINT16) (PackagePowerLimitMsr.Dwords.High & POWER_LIMIT_MASK);
  gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpPowerLimitWindow = (UINT8) gCpuPowerMgmtBasicConfig->PowerLimit1Time;
  gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpTar              = (UINT8) mTurboBusRatio;
  gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpCtc              = 1;
  gCpuGlobalNvsAreaConfig->Area->CtdpLevelsSupported                       = 1;
  gCpuGlobalNvsAreaConfig->Area->ConfigTdpBootModeIndex                    = 0;
}

/**
  Configures BIOS overrides in MSR 0x610
    Configures Long duration Turbo Mode (power limit 1) power level and time window
    Configures Short duration turbo mode (power limit 2)
**/
VOID
ConfigureCtdpPowerLimitsOverrides (
  VOID
  )
{
  UINTN         Index;
  UINTN         NoOfOverrides;
  CPU_FAMILY    CpuFamilyId;
  UINTN         PackageTdp;
  MSR_REGISTER  PackagePowerLimitMsr;
  PPM_CTDP_OVERRIDE_TABLE *PpmCtdpOverrideTable;
  CPU_STEPPING  CpuSteppingId;
  BOOLEAN       HasEdram;
  CPU_SKU       CpuSku;
  UINT16        SaDid;

  CpuFamilyId   = GetCpuFamily ();
  CpuSku        = GetCpuSku ();
  CpuSteppingId = GetCpuStepping ();
  SaDid         = MmioRead16 (MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN) + R_SA_MC_DEVICE_ID);

  if ((EnumSklCpu == GetCpuGeneration()) && (CpuSku != EnumCpuTrad)) {
    ///
    /// SKL SKU Override Table for ULX/ULT & Halo
    ///
    PpmCtdpOverrideTable = mSklUltPpmCtdpOverrideTable;
    if (sizeof (PPM_CTDP_OVERRIDE_TABLE) != 0) {
      NoOfOverrides = (sizeof (mSklUltPpmCtdpOverrideTable)) / (sizeof (PPM_CTDP_OVERRIDE_TABLE));
    }
  } else {
    PpmCtdpOverrideTable = mKblPpmCtdpOverrideTable;
    if (sizeof (PPM_CTDP_OVERRIDE_TABLE) != 0) {
      NoOfOverrides = (sizeof (mKblPpmCtdpOverrideTable)) / (sizeof (PPM_CTDP_OVERRIDE_TABLE));
    }
  }

  PackageTdp = (mPackageTdpWatt * 100);
  if ((mPackageTdp % mProcessorPowerUnit) !=0) {
    PackageTdp += ((mPackageTdp % mProcessorPowerUnit)* 100) / mProcessorPowerUnit;
  }

  HasEdram      = ((AsmReadMsr64 (MSR_PLATFORM_INFO) & B_PLATFORM_INFO_EDRAM_EN) != 0);
  ///
  /// This code supports several 15W SKL/KBL parts. The logic below will identify
  /// which 15W part requires the power limit overrides and updates the correct
  /// cpu identifier for the override loop.
  ///
  if (PackageTdp == TDP_15_WATTS) {
    if (CpuSteppingId < EnumKblY0) {
      if (CpuFamilyId == CPUID_FULL_FAMILY_MODEL_SKYLAKE_ULT_ULX) {
        ///
        /// SKL-U
        ///
        if (HasEdram) {
          mCpuIdentifier = CPU_SKL_U_2_3_E;  /// SKL-U 2+3e
        } else {
          mCpuIdentifier = CPU_SKL_U_2_2;  /// SKL-U 2+2
        }
      } else if (CpuFamilyId == CPUID_FULL_FAMILY_MODEL_KABYLAKE_ULT_ULX) {
        ///
        /// KBL-U
        ///
        if (HasEdram) {
          mCpuIdentifier = CPU_KBL_U_2_3_E;  /// KBL-U 2+3e
        } else {
          mCpuIdentifier = CPU_KBL_U_2_2_V1;  /// KBL-U 2+2
        }
      }
    } else if (CpuSteppingId >= EnumKblY0) {
      ///
      /// KBL-U and KBL-R
      ///
      if (SaDid == V_SA_DEVICE_ID_KBL_MB_ULT_1) {
        mCpuIdentifier = CPU_KBL_U_2_2_V2;  /// KBL-U 2+2
      } else if (SaDid == V_SA_DEVICE_ID_KBLR_MB_ULT_1) {
        mCpuIdentifier = CPU_KBL_R_U_4_2;  /// KBL-R U 4+2
      }
    } else {
      mCpuIdentifier = GetCpuIdentifier ();
    }
  }

  for (Index = 0; Index < NoOfOverrides; Index++, PpmCtdpOverrideTable++) {
    if (PpmCtdpOverrideTable->CpuIdentifier == mCpuIdentifier) {

      DEBUG ((DEBUG_INFO, "PPM:: Ctdp BIOS PL1/PL2 Override Ctdp SKU Found  :%d  override table index :%d\n",PpmCtdpOverrideTable->SkuPackageTdp,Index));

      ///
      /// MSR Overrides
      ///
      PackagePowerLimitMsr.Qword = AsmReadMsr64 (MSR_PACKAGE_POWER_LIMIT);
      if (PpmCtdpOverrideTable->MsrCtdpPowerLimit1) {
        PackagePowerLimitMsr.Dwords.Low &= ~POWER_LIMIT_MASK;
        PackagePowerLimitMsr.Dwords.Low |= ((PpmCtdpOverrideTable->MsrCtdpPowerLimit1 * mProcessorPowerUnit) /100) & POWER_LIMIT_MASK;
      }
      if (PpmCtdpOverrideTable->MsrCtdpPowerLimit2) {
        PackagePowerLimitMsr.Dwords.High &= ~POWER_LIMIT_MASK;
        PackagePowerLimitMsr.Dwords.High |= ((PpmCtdpOverrideTable->MsrCtdpPowerLimit2 * mProcessorPowerUnit) /100) & POWER_LIMIT_MASK;
      }
      AsmWriteMsr64 (MSR_PACKAGE_POWER_LIMIT, PackagePowerLimitMsr.Qword);

      ///
      /// MMIO Overrides
      ///
      if (PpmCtdpOverrideTable->CtdpNominalPowerLimit1) {
        gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpPowerLimit1 = (UINT16) (PpmCtdpOverrideTable->CtdpNominalPowerLimit1 * mProcessorPowerUnit) /100;
      }
      if (PpmCtdpOverrideTable->CtdpNominalPowerLimit2) {
        gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[0].CtdpPowerLimit2 = (UINT16) (PpmCtdpOverrideTable->CtdpNominalPowerLimit2 * mProcessorPowerUnit) /100;
      }
      if (PpmCtdpOverrideTable->CtdpDownPowerLimit1) {
        gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[1].CtdpPowerLimit1 = (UINT16) (PpmCtdpOverrideTable->CtdpDownPowerLimit1 * mProcessorPowerUnit) /100;
      }
      if (PpmCtdpOverrideTable->CtdpDownPowerLimit2) {
        gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[1].CtdpPowerLimit2 = (UINT16) (PpmCtdpOverrideTable->CtdpDownPowerLimit2 * mProcessorPowerUnit) /100;
      }
      if (PpmCtdpOverrideTable->CtdpUpPowerLimit1) {
        gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[2].CtdpPowerLimit1 = (UINT16) (PpmCtdpOverrideTable->CtdpUpPowerLimit1 * mProcessorPowerUnit) /100;
      }
      if (PpmCtdpOverrideTable->CtdpUpPowerLimit2) {
        gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[2].CtdpPowerLimit2 = (UINT16) (PpmCtdpOverrideTable->CtdpUpPowerLimit2 * mProcessorPowerUnit) /100;
      }
      break;
    }
  }
}

/**
  Configures following fields of MSR 0x615
    Configures power limit 3 power level and time window
**/
VOID
ConfigurePl3PowerLimits (
  VOID
  )
{
  MSR_REGISTER PlatformPowerLimitMsr;
  UINT16       ConvertedPowerLimit3;
  UINT8        ConvertedPowerLimit3Time;
  UINTN        Index;
  UINT8        TimeWindowValid;
  UINT32       ValidPl3TimeWindow[] = {3,4,5,6,7,8,10,12,14,16,20,24,28,32,40,48,55,56,64};

  TimeWindowValid = FALSE;
  PlatformPowerLimitMsr.Qword = AsmReadMsr64 (MSR_PL3_CONTROL);
  DEBUG ((DEBUG_INFO," PL3 MSR 615 Before Writing %x \n",PlatformPowerLimitMsr.Dwords.Low));

  ///
  /// Configure PL3 Power Limit if custom value is avaiable
  ///
  if (gCpuPowerMgmtBasicConfig->PowerLimit3 != AUTO) {
    ConvertedPowerLimit3 = (UINT16) (((gCpuPowerMgmtBasicConfig->PowerLimit3 * mProcessorPowerUnit) / mCustomPowerUnit) & POWER_LIMIT_MASK);
    PlatformPowerLimitMsr.Dwords.Low &= ~POWER_LIMIT_MASK;
    PlatformPowerLimitMsr.Dwords.Low |= (UINT32) (ConvertedPowerLimit3);
    PlatformPowerLimitMsr.Dwords.Low |= B_POWER_LIMIT_ENABLE;
  }

  ///
  /// Configure PL3 Time window if custom value is avaiable
  ///
  if (gCpuPowerMgmtBasicConfig->PowerLimit3Time != AUTO) {
    ///
    /// Validate time window input is valid before converting
    ///
    for (Index = 0; Index < (sizeof(ValidPl3TimeWindow)/sizeof(UINT32)); Index++) {
      if (gCpuPowerMgmtBasicConfig->PowerLimit3Time == ValidPl3TimeWindow[Index]) {
        TimeWindowValid = TRUE;
        break;
      }
    }

    if (TimeWindowValid) {
      ConvertedPowerLimit3Time = GetConvertedTime (gCpuPowerMgmtBasicConfig->PowerLimit3Time, MilliSecondsTimeWindowConvert);
      PlatformPowerLimitMsr.Dwords.Low &= ~POWER_LIMIT_3_TIME_MASK;
      PlatformPowerLimitMsr.Dwords.Low |= (UINT32) (LShiftU64 (ConvertedPowerLimit3Time, 17) & POWER_LIMIT_3_TIME_MASK);
      PlatformPowerLimitMsr.Dwords.Low |= B_POWER_LIMIT_ENABLE;
    }
    else {
      DEBUG ((DEBUG_ERROR,"ERROR: PL3 Time Window value of %X is invalid. Bypassing PL3 update. \n", gCpuPowerMgmtBasicConfig->PowerLimit3Time));
      return;
    }
  }

  ///
  /// Configure PL3 Duty Cycle if custom value is avaiable
  ///
  if (gCpuPowerMgmtBasicConfig->PowerLimit3DutyCycle != AUTO) {
    PlatformPowerLimitMsr.Dwords.Low &= ~POWER_LIMIT_3_DUTY_CYCLE_MASK;
    PlatformPowerLimitMsr.Dwords.Low |= (UINT32) (LShiftU64 (gCpuPowerMgmtBasicConfig->PowerLimit3DutyCycle, 24) & POWER_LIMIT_3_DUTY_CYCLE_MASK);
    PlatformPowerLimitMsr.Dwords.Low |= B_POWER_LIMIT_ENABLE;
  }

  //
  // Enable/Disable PL3 lock
  //
  if (gCpuPowerMgmtBasicConfig->PowerLimit3Lock == TRUE) {
    PlatformPowerLimitMsr.Dwords.Low |= (UINT32) B_POWER_LIMIT_LOCK;
  } else {
    PlatformPowerLimitMsr.Dwords.Low &= (~((UINT32) B_POWER_LIMIT_LOCK));
  }

  if ((gCpuPowerMgmtBasicConfig->PowerLimit3DutyCycle == AUTO) &&
      (gCpuPowerMgmtBasicConfig->PowerLimit3Time == AUTO) &&
      (gCpuPowerMgmtBasicConfig->PowerLimit3 == AUTO)) {
    //
    // Explicitly disable PL3 if all options are set to AUTO
    //
    PlatformPowerLimitMsr.Dwords.Low &= ~(POWER_LIMIT_MASK | B_POWER_LIMIT_ENABLE);
  }

  AsmWriteMsr64 (MSR_PL3_CONTROL, PlatformPowerLimitMsr.Qword);
  DEBUG ((DEBUG_INFO," PL3 MSR 615 After Writing %x \n",PlatformPowerLimitMsr.Dwords.Low));
}

/**
  Configure PL4 limits by programming the CURRENT LIMIT and LOCK fields of MSR 601
**/
VOID
ConfigurePl4PowerLimits (
  VOID
  )
{
  MSR_REGISTER PowerLimit4Msr;
  UINT16       ConvertedPowerLimit4;
  CPU_SKU      CpuSku;
  CPU_STEPPING CpuSteppingId;
  UINT16       SaDid;
  UINTN        PackageTdp;
  UINTN        NoOfOverrides;
  UINTN        Index;
  CPU_FAMILY   CpuFamilyId;
  BOOLEAN      HasEdram;
  PPM_OVERRIDE_TABLE *PpmOverrideTable;
  PPM_CTDP_OVERRIDE_TABLE *PpmCtdpOverrideTable;

  CpuSku        = GetCpuSku ();
  CpuSteppingId = GetCpuStepping ();
  CpuFamilyId   = GetCpuFamily ();
  SaDid         = MmioRead16 (MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN) + R_SA_MC_DEVICE_ID);
  NoOfOverrides = 0;
  PackageTdp = (mPackageTdpWatt * 100);
  if ((mPackageTdp % mProcessorPowerUnit) !=0) {
    PackageTdp += ((mPackageTdp % mProcessorPowerUnit)* 100) / mProcessorPowerUnit;
  }

  ///
  /// If CFL-S, update Cpu Identifier based on VrPowerDeliveryDesign input
  ///
  if (mCpuIdentifier >= EnumCflSMinCpuId && mCpuIdentifier <= EnumCflSMaxCpuId) {
   if ( gCpuPowerMgmtVrConfig->VrPowerDeliveryDesign == EnumUnknownCpuVrPowerDesign) {
     DEBUG ((DEBUG_ERROR, "VR ERROR: VrPowerDeliveryDesign is missing! VR PL4 override values may cause system instability!\n"));
   } else if ( gCpuPowerMgmtVrConfig->VrPowerDeliveryDesign <= EnumMaxCflVrPowerDesign ){
     ///
     /// This field is required to be non-zero on CFL S-based platforms.
     /// Used to communicate the power delivery design of the board.
     /// The VR override code traditionally looked at the CPU sku to determine the default VR
     /// override values. However, the CFL-S platforms require different VR values based on the
     /// board power delivery design. This is due to CPU socket compatibility across different board
     /// designs. Without this field populated, the system may experience VR OCP shutdowns, hangs,
     /// thermal and performance loss.
     ///
     mCpuIdentifier = (CPU_OVERRIDE_IDENTIFIER) gCpuPowerMgmtVrConfig->VrPowerDeliveryDesign;
   }
  }


  PowerLimit4Msr.Qword = AsmReadMsr64 (MSR_PL4_CONTROL);
  PowerLimit4Msr.Dwords.Low &= ~V_POWER_LIMIT_4_MASK;
  DEBUG ((DEBUG_INFO," PL4 MSR 601 Before Writing %x \n ", PowerLimit4Msr.Dwords.Low));
  if (gCpuPowerMgmtBasicConfig->PowerLimit4 != AUTO){
    ///
    /// User defined PL4
    ///
    ConvertedPowerLimit4 = (UINT16) (((gCpuPowerMgmtBasicConfig->PowerLimit4 * mProcessorPowerUnit) / mCustomPowerUnit) & V_POWER_LIMIT_4_MASK);
    PowerLimit4Msr.Dwords.Low &= ~V_POWER_LIMIT_4_MASK;
    PowerLimit4Msr.Dwords.Low |= (UINT32) (ConvertedPowerLimit4);
  } else {
    //
    // Set PL4 power limit = 0 when AUTO is selected
    //
    HasEdram      = ((AsmReadMsr64 (MSR_PLATFORM_INFO) & B_PLATFORM_INFO_EDRAM_EN) != 0);
    if (gCpuOverClockingPreMemConfig->OcSupport == 0) {
      ///
      /// This code supports several 15W SKL/KBL parts. The logic below will identify
      /// which 15W part requires the power limit overrides and updates the correct
      /// cpu identifier for the override loop.
      ///
      if (PackageTdp == TDP_15_WATTS) {
        if (CpuSteppingId < EnumKblY0) {
          if (CpuFamilyId == CPUID_FULL_FAMILY_MODEL_SKYLAKE_ULT_ULX) {
            ///
            /// SKL-U
            ///
            if (HasEdram) {
              mCpuIdentifier = CPU_SKL_U_2_3_E;  /// SKL-U 2+3e
            } else {
              mCpuIdentifier = CPU_SKL_U_2_2;  /// SKL-U 2+2
            }
          } else if (CpuFamilyId == CPUID_FULL_FAMILY_MODEL_KABYLAKE_ULT_ULX) {
            ///
            /// KBL-U
            ///
            if (HasEdram) {
              mCpuIdentifier = CPU_KBL_U_2_3_E;  /// KBL-U 2+3e
            } else {
              mCpuIdentifier = CPU_KBL_U_2_2_V1;  /// KBL-U 2+2
            }
          }
        } else if (CpuSteppingId >= EnumKblY0) {
          ///
          /// KBL-U and KBL-R
          ///
          if (SaDid == V_SA_DEVICE_ID_KBL_MB_ULT_1) {
            mCpuIdentifier = CPU_KBL_U_2_2_V2;  /// KBL-U 2+2
          } else if (SaDid == V_SA_DEVICE_ID_KBLR_MB_ULT_1) {
            mCpuIdentifier = CPU_KBL_R_U_4_2;  /// KBL-R U 4+2
          }
        }
      }

      //
      // Override PL4 for specific CPU skus
      //
      if (mCpuConfigTdpLevels > 0) {
        //
        //  Select cTDP override table
        //
        if (EnumSklCpu == GetCpuGeneration()) {
          ///
          /// SKL SKU Override Table for ULX/ULT & Halo
          ///
          PpmCtdpOverrideTable = mSklUltPpmCtdpOverrideTable;
          if (sizeof (PPM_CTDP_OVERRIDE_TABLE) != 0) {
            NoOfOverrides = (sizeof (mSklUltPpmCtdpOverrideTable)) / (sizeof (PPM_CTDP_OVERRIDE_TABLE));
          }
          for (Index = 0; Index < NoOfOverrides; Index++, PpmCtdpOverrideTable++) {
            if ( (PpmCtdpOverrideTable->SkuPackageTdp == PackageTdp) &&
                 (PpmCtdpOverrideTable->CpuIdentifier == mCpuIdentifier) &&
                 (PpmCtdpOverrideTable->MsrPowerLimit4 != 0)) {
              PowerLimit4Msr.Dwords.Low = (PpmCtdpOverrideTable->MsrPowerLimit4 * mProcessorPowerUnit) / 100;
            }
          }
        } else if (EnumKblCpu == GetCpuGeneration()) {
          ///
          /// KBL SKU Override Table for ULX/ULT & Halo
          ///
          PpmCtdpOverrideTable = mKblPpmCtdpOverrideTable;
          if (sizeof (PPM_CTDP_OVERRIDE_TABLE) != 0) {
            NoOfOverrides = (sizeof (mKblPpmCtdpOverrideTable)) / (sizeof (PPM_CTDP_OVERRIDE_TABLE));
          }
          for (Index = 0; Index < NoOfOverrides; Index++, PpmCtdpOverrideTable++) {
            if ( (PpmCtdpOverrideTable->SkuPackageTdp == PackageTdp) &&
                 (PpmCtdpOverrideTable->CpuIdentifier == mCpuIdentifier) &&
                 (PpmCtdpOverrideTable->MsrPowerLimit4 != 0)) {
              PowerLimit4Msr.Dwords.Low = (PpmCtdpOverrideTable->MsrPowerLimit4 * mProcessorPowerUnit) / 100;
            }
          }
        }
      } else {
          ///
          /// Select CFL non-cTDP override table
          ///
          PpmOverrideTable = mPpmOverrideTable;
          if (sizeof (PPM_OVERRIDE_TABLE) != 0) {
            NoOfOverrides = (sizeof (mPpmOverrideTable)) / (sizeof (PPM_OVERRIDE_TABLE));
          }

          ///
          /// Override the PL4 power limit with the table value
          ///
          for (Index = 0; Index < NoOfOverrides; Index++, PpmOverrideTable++) {
            if ((PpmOverrideTable->CpuIdentifier == mCpuIdentifier) && (PpmOverrideTable->MsrPowerLimit4 != 0)) {
              ///
              /// Some TDP segments have multiple CPU types. We need to check that the CpuIdentifier matches in this case.
              ///
              PowerLimit4Msr.Dwords.Low = (((PpmOverrideTable->MsrPowerLimit4 * mProcessorPowerUnit) / 100) & V_POWER_LIMIT_4_MASK);
            }
          }
        }
    } else {
      ///
      /// Disable PL4 when AUTO is selected and overclocking is enabled.
      ///
      PowerLimit4Msr.Dwords.Low = 0;
    }
  }

  //
  // Enable/Disable PL4 lock
  //
  if (gCpuPowerMgmtBasicConfig->PowerLimit4Lock == TRUE) {
    PowerLimit4Msr.Dwords.Low |= (UINT32) B_POWER_LIMIT_LOCK;
  } else {
    PowerLimit4Msr.Dwords.Low &= (~((UINT32) B_POWER_LIMIT_LOCK));
  }

  AsmWriteMsr64 (MSR_PL4_CONTROL, PowerLimit4Msr.Qword);
  DEBUG ((DEBUG_INFO," PL4 MSR 601 After Writing %x \n ", PowerLimit4Msr.Dwords.Low));
}

/**
  Configures following fields of MSR 0x610
    Configures Long duration Turbo Mode (power limit 1) power level and time window
    Configures Short duration turbo mode (power limit 2)
**/
VOID
ConfigureCtdpPowerLimits (
  VOID
  )
{
  MSR_REGISTER PackagePowerLimitMsr;
  UINT16       ConvertedPowerLimit1;
  UINT16       ConvertedPowerLimit2;
  UINT8        ConvertedPowerLimit1Time;
  UINTN        PciD0F0RegBase;
  UINT32       MchBar;
  UINT16       Multiplier;
  UINTN        Index;
  CPU_FAMILY   mCpuFamilyId;

  mCpuFamilyId = gCpuGlobalNvsAreaConfig->Area->Cpuid & CPUID_FULL_FAMILY_MODEL;
  ConvertedPowerLimit1Time = 0;
  ///
  /// By default, for Mobile & Desktop Processors: Short duration Power Limit  = 1.25 * Package TDP
  ///
  Multiplier = 125;
  //
  // For ConfigTdp enabled skus
  //
  PackagePowerLimitMsr.Qword = AsmReadMsr64 (MSR_PACKAGE_POWER_LIMIT);
  PackagePowerLimitMsr.Dwords.Low &= ~POWER_LIMIT_MASK;
  PackagePowerLimitMsr.Dwords.High &= ~POWER_LIMIT_MASK;
  ///
  /// Initialize the Power Limit 1/2 and Power Limit 2 enable bit in MSR
  ///  Power Limit 1: Turbo Power Limit MSR  [14:0] and Power Limit 2: Turbo Power Limit MSR  [46:32]
  ///  Set MSR value for Power Limit 1/2 to Max Package Power Value or Maximum Supported Value
  ///
  ///
  if (mPackageMaxPower) {
    ConvertedPowerLimit1 = mPackageMaxPower;
    ///
    ///  Short duration Power Limit (PL2)  = 1.25 * PL1
    ///
    ConvertedPowerLimit2 = EFI_IDIV_ROUND ((Multiplier * ConvertedPowerLimit1), 100);
    if (ConvertedPowerLimit2 > PACKAGE_TDP_POWER_MASK) {
      ConvertedPowerLimit2 = PACKAGE_TDP_POWER_MASK;
    }
  } else {
    ///
    /// Set Maximum value for Turbo Power Limit MSR  [14:0] and [46:32] =
    /// Max of CTDP Level Power Limts
    ///
    ConvertedPowerLimit1 = 0;
    for (Index = 0; Index < gCpuGlobalNvsAreaConfig->Area->CtdpLevelsSupported; Index++) {
      if (ConvertedPowerLimit1 < gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimit1) {
        ConvertedPowerLimit1 = gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimit1;
      }
    }
    ConvertedPowerLimit2 = 0;
    for (Index = 0; Index < gCpuGlobalNvsAreaConfig->Area->CtdpLevelsSupported; Index++) {
      if (ConvertedPowerLimit2 < gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimit2) {
        ConvertedPowerLimit2 = gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[Index].CtdpPowerLimit2;
      }
    }
  }
  ///
  /// Program Power Limit 1 (Long Duration Turbo) Time Window
  ///  If PowerLimit1Time is AUTO OR If PowerLimit1Time is > MAX_POWER_LIMIT_1_TIME_IN_SECONDS
  ///    program default values
  ///
  if (gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomPowerLimit1Time != 0) {
    ConvertedPowerLimit1Time = GetConvertedTime (gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomPowerLimit1Time, SecondsTimeWindowConvert);
  } else {
    if (IS_SA_DEVICE_ID_MOBILE (mProcessorFlavor) || IS_SA_DEVICE_ID_HALO (mProcessorFlavor)) {
      ///
      /// For Mobile and Halo, default value is 28 seconds
      ///
      gCpuPowerMgmtBasicConfig->PowerLimit1Time = MB_POWER_LIMIT1_TIME_DEFAULT;
    } else {
      ///
      /// For Desktop, default value is 1 second
      ///
      gCpuPowerMgmtBasicConfig->PowerLimit1Time = DT_POWER_LIMIT1_TIME_DEFAULT;
    }
    ConvertedPowerLimit1Time = GetConvertedTime (gCpuPowerMgmtBasicConfig->PowerLimit1Time, SecondsTimeWindowConvert);
  }
  ///
  /// Set MSR_PACKAGE_POWER_LIMIT.CRITICAL_POWER_CLAMP_1(bit 16)
  ///
  PackagePowerLimitMsr.Dwords.Low |= (UINT32) B_CRITICAL_POWER_CLAMP_ENABLE;

  ///
  /// Get the MCH space base address.
  ///
  PciD0F0RegBase  = MmPciBase (0, 0, 0);
  MchBar          = MmioRead32 (PciD0F0RegBase + 0x48) &~BIT0;

  ///
  /// Program MMIO PL1 clamp enable
  ///
  MmioOr32 (MchBar + MMIO_TURBO_POWER_LIMIT, B_CRITICAL_POWER_CLAMP_ENABLE);

  ///
  ///  Configure Power Limit 1 (Long Duration Turbo) time windows: Turbo Power Limit MSR [23:17]
  ///
  PackagePowerLimitMsr.Dwords.Low &= ~POWER_LIMIT_1_TIME_MASK;
  PackagePowerLimitMsr.Dwords.Low |= (UINT32) LShiftU64 (ConvertedPowerLimit1Time, 17);
  PackagePowerLimitMsr.Dwords.High |= B_POWER_LIMIT_ENABLE;
  PackagePowerLimitMsr.Dwords.Low |= (UINT32) (ConvertedPowerLimit1);
  PackagePowerLimitMsr.Dwords.High |= (UINT32) (ConvertedPowerLimit2);
  AsmWriteMsr64 (MSR_PACKAGE_POWER_LIMIT, PackagePowerLimitMsr.Qword);
}

/**
  Configure cTDP BIOS MSRs to Boot Ctdp values
    - Configures CONFIG_TDP_CONTROL MSR
    - Configures TURBO_ACTIVATION_RATIO MSR

  @param[in] CpuConfigTdpBootLevel  ConfigTdpBootLevel policy setting by user
**/
VOID
SelectCtdpLevel (
  IN UINT8             CpuConfigTdpBootLevel
  )
{
  MSR_REGISTER TempMsr;

  ///
  /// Select cTDP Nominal if cTDP is disabled or the level is not supported.
  ///
  if (CpuConfigTdpBootLevel == CONFIG_TDP_DEACTIVATE || CpuConfigTdpBootLevel >= gCpuGlobalNvsAreaConfig->Area->CtdpLevelsSupported) {
    CpuConfigTdpBootLevel = 0;
  }

  if (CpuConfigTdpBootLevel >= 3) {
    DEBUG ((DEBUG_ERROR, "ERROR: Invalid CpuConfigTdpBootLevel=%x, and CpuConfigTdpBootLevel should be range in 0-2 \n", CpuConfigTdpBootLevel));
    ASSERT (FALSE);
    return;
  }
  mCpuConfigTdpBootRatio     = gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[CpuConfigTdpBootLevel].CtdpTar+1;
  gCpuGlobalNvsAreaConfig->Area->ConfigurablePpc = gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[CpuConfigTdpBootLevel].CtdpPpc;
  ///
  /// Program the selected level 00:nominal,01:level1,10:level2 to
  /// CONFIG TDP CONTROL MSR.
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_CONFIG_TDP_CONTROL);
  if ((TempMsr.Qword & CONFIG_TDP_CONTROL_LOCK) == 0) {
    TempMsr.Dwords.Low  = (UINT16) TempMsr.Dwords.Low &~CONFIG_TDP_CONTROL_LVL_MASK;
    TempMsr.Dwords.Low  = (UINT16) TempMsr.Dwords.Low | (CpuConfigTdpBootLevel & CONFIG_TDP_CONTROL_LVL_MASK);
    if (gCpuPowerMgmtCustomConfig->ConfigTdpLock == TRUE ) {
      TempMsr.Dwords.Low |= CONFIG_TDP_CONTROL_LOCK;
      DEBUG ((DEBUG_INFO, "PPM:: ConfigTDP MSR_CONFIG_TDP_CONTROL is locked\n"));
    }
    AsmWriteMsr64 (MSR_CONFIG_TDP_CONTROL, TempMsr.Qword);
    DEBUG ((DEBUG_INFO, "PPM:: ConfigTDP MSR_CONFIG_TDP_CONTROL=%x\n", TempMsr.Qword));
  } else {
    DEBUG ((DEBUG_INFO, "PPM:: Could not write MSR_CONFIG_TDP_CONTROL\n"));
  }
  ///
  /// Program the max non-turbo ratio corresponding to default selected level
  /// in TURBO_ACTIVATION_RATIO MSR.
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_TURBO_ACTIVATION_RATIO);
  if ((TempMsr.Qword & MSR_TURBO_ACTIVATION_RATIO_LOCK) == 0) {
    TempMsr.Dwords.Low &= ~MSR_TURBO_ACTIVATION_RATIO_MASK;
    TempMsr.Dwords.Low |= (UINT32) ((mCpuConfigTdpBootRatio - 1) & MSR_TURBO_ACTIVATION_RATIO_MASK);
    if (gCpuPowerMgmtCustomConfig->ConfigTdpLock == TRUE) {
      TempMsr.Dwords.Low |= MSR_TURBO_ACTIVATION_RATIO_LOCK;
      DEBUG ((DEBUG_INFO, "PPM:: ConfigTDP MSR_TURBO_ACTIVATION_RATIO is locked\n"));
    }
    AsmWriteMsr64 (MSR_TURBO_ACTIVATION_RATIO, TempMsr.Qword);
    DEBUG ((DEBUG_INFO, "PPM:: ConfigTDP MSR_TURBO_ACTIVATION_RATIO=%x\n", TempMsr.Qword));
  } else {
    DEBUG ((DEBUG_INFO, "PPM:: Could not write MSR_TURBO_ACTIVATION_RATIO\n"));
  }
}

/**
  Configures the TURBO_POWER_LIMIT MMIO for Boot ConfigTdp Level

  @param[in] CpuConfigTdpBootLevel  ConfigTdpBootLevel policy setting by user
**/
VOID
SelectCtdpPowerLimits (
  IN UINT8             CpuConfigTdpBootLevel
  )
{
  UINTN        PciD0F0RegBase;
  UINT32       MchBar;
  UINT32       Data32And;
  UINT32       Data32Or;
  UINT16       PowerLimit1;
  UINT16       PowerLimit2;
  MSR_REGISTER TempMsr;

  ///
  /// Select cTDP Nominal if Ctdp disabled or boot level not supported.
  ///
  if (CpuConfigTdpBootLevel >= gCpuGlobalNvsAreaConfig->Area->CtdpLevelsSupported) {
    CpuConfigTdpBootLevel = 0;
  }

  PowerLimit1 = gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[CpuConfigTdpBootLevel].CtdpPowerLimit1;
  PowerLimit2 = gCpuGlobalNvsAreaConfig->Area->CtdpLevelSettings[CpuConfigTdpBootLevel].CtdpPowerLimit2;
  ///
  /// Check if Power Limits are initalized
  ///
  if (PowerLimit1 != 0 && PowerLimit2 != 0) {
    ///
    /// Get the MCH space base address.
    /// Program Turbo Power Limit MMIO register MCHBAR+0x59A0 Bits [14:0] and [46:32]
    /// for ConfigTdp mode PL1 and PL2
    ///
    PciD0F0RegBase  = MmPciBase (0, 0, 0);
    MchBar          = MmioRead32 (PciD0F0RegBase + 0x48) &~BIT0;
    ///
    /// Read PowerLimit MSR
    ///
    TempMsr.Qword = AsmReadMsr64 (MSR_PACKAGE_POWER_LIMIT);
    ///
    /// Program cTDP Power Limit1
    ///
    Data32And = (UINT32) ~(PACKAGE_TDP_POWER_MASK);
    Data32Or  = (UINT32) (PowerLimit1 | (TempMsr.Dwords.Low & ~PACKAGE_TDP_POWER_MASK));
    MmioAndThenOr32 (MchBar + MMIO_TURBO_POWER_LIMIT, Data32And, Data32Or);
    ///
    /// Program cTDP Power Limit2
    ///
    Data32And = (UINT32) ~(PACKAGE_TDP_POWER_MASK);
    Data32Or  = (UINT32) (PowerLimit2 | (TempMsr.Dwords.High & ~PACKAGE_TDP_POWER_MASK));
    MmioAndThenOr32 (MchBar + MMIO_TURBO_POWER_LIMIT + 4, Data32And, Data32Or);
  }
}

/**
  Configures following fields of MSR 0x618 based on corresponding MMIO register (MCHBAR+0x58E0):
    Configures Long duration Turbo Mode (power limit 1) power level and time window for DDR domain
    Configures Short duration Turbo Mode (power limit 2) power level and time window for DDR domain
**/
VOID
ConfigureDdrPowerLimits (
  VOID
  )
{
  MSR_REGISTER  DdrPowerLimitMsr;
  UINTN         PciD0F0RegBase;
  UINT32        MchBar;

  PciD0F0RegBase  = MmPciBase (0, 0, 0);
  MchBar          = MmioRead32 (PciD0F0RegBase + 0x48) &~BIT0;

  DdrPowerLimitMsr.Qword = 0;
  DdrPowerLimitMsr.Qword = (MmioRead32 (MchBar + MMIO_DDR_RAPL_LIMIT) &~BIT0) + LShiftU64 (MmioRead32 (MchBar + MMIO_DDR_RAPL_LIMIT + 4), 32);

  DEBUG (
    (DEBUG_INFO,
     "DDR Power Limit 1 = %d\n",
     DdrPowerLimitMsr.Dwords.Low & POWER_LIMIT_MASK)
    );
  DEBUG (
    (DEBUG_INFO,
     "DDR Power Limit 2 = %d\n",
     DdrPowerLimitMsr.Dwords.High & POWER_LIMIT_MASK)
    );

  AsmWriteMsr64 (MSR_DDR_RAPL_LIMIT, DdrPowerLimitMsr.Qword);
}

/**
  Configures MSR 0x65C platform power limits (PSys)
    -Configures Platform Power Limit 1 Enable, power and time window
    -Configures Platform Power Limit 2 Enable, power
    -Platform power limits are limited by the Package Max and Min power
**/
VOID
ConfigurePlatformPowerLimits (
  VOID
  )
{
  MSR_REGISTER PlatformPowerLimitMsr;
  UINT16       ConvertedPowerLimit1;
  UINT8        ConvertedPowerLimit1Time;
  UINT16       ConvertedPowerLimit2;
  UINT16       CpuConvertedPowerLimit1MaxLimit;
  UINT16       CpuConvertedPowerLimit2MaxLimit;
  UINT16       Multiplier;
  CPU_STEPPING CpuSteppingId;
  CPU_FAMILY   CpuFamilyId;

  CpuFamilyId   = gCpuGlobalNvsAreaConfig->Area->Cpuid & CPUID_FULL_FAMILY_MODEL;
  CpuSteppingId = gCpuGlobalNvsAreaConfig->Area->Cpuid & CPUID_FULL_STEPPING;
  CpuConvertedPowerLimit1MaxLimit = 0;
  CpuConvertedPowerLimit2MaxLimit = 0;
  ConvertedPowerLimit1Time        = 0;
  ///
  /// By default, for Mobile & Desktop Processors: Platform Power Limit 2 = 1.25 * Package TDP
  ///
  Multiplier = 125;
  ///
  ///  Check if Psys power limits are programmable

  ///   -SPI strap 300 bit 31
  ///
    PlatformPowerLimitMsr.Qword = AsmReadMsr64 (MSR_PLATFORM_POWER_LIMIT);
    ///
    /// Initialize the Power Limit 1 and Power Limit 1 enable bit
    ///  - Power Limit 1: Platform Power Limit MSR  [14:0]
    ///  - Power Limit 1 Enable: Platform Power Limit MSR  [15]
    ///
    ///
    /// By default, program Power Limit 1 to Package TDP limit
    ///
    ConvertedPowerLimit1 = mPackageTdp;
    if (gCpuPowerMgmtPsysConfig->PsysPowerLimit1Power != AUTO) {
      ///
      /// gTurboSettings->PlatformPowerLimit1Power is in mW or watts. We need to
      /// convert it to CPU Power unit, specified in PACKAGE_POWER_SKU_UNIT_MSR[3:0].
      /// Since we are converting from Watts to CPU power units, multiply by
      /// PACKAGE_POWER_SKU_UNIT_MSR[3:0].
      ///
      ConvertedPowerLimit1 = (UINT16) ((gCpuPowerMgmtPsysConfig->PsysPowerLimit1Power * mProcessorPowerUnit) / mCustomPowerUnit);
      if (mPackageMaxPower == 0 && ConvertedPowerLimit1 >= mPackageMinPower) {
        ///
        ///  If PACKAGE_POWER_SKU_MSR [46:32] = 0 means there is no upper limit ( since this field is 15 bits, the max value is 2^15 - 1 )
        ///
        CpuConvertedPowerLimit1MaxLimit = (UINT16) (LShiftU64 (2, 15) - 1);
        if (ConvertedPowerLimit1 > CpuConvertedPowerLimit1MaxLimit) {
          ///
          /// If new Power Limit 1 is > CpuConvertedPowerLimit1MaxLimit, program Power Limit 1 to CpuConvertedPowerLimit1MaxLimit
          ///
          ConvertedPowerLimit1 = CpuConvertedPowerLimit1MaxLimit;
        }
      } else if (mPackageMinPower == 0 && ConvertedPowerLimit1 > 0 && ConvertedPowerLimit1 <= mPackageMaxPower) {
        ///
        ///  If PACKAGE_POWER_SKU_MSR [30:16] = 0 means there is no lower limit
        ///
        ConvertedPowerLimit1 = (UINT16) ((gCpuPowerMgmtBasicConfig->PowerLimit1 * mProcessorPowerUnit) / mCustomPowerUnit);

      } else {
        ///
        /// Power Limit 1 needs to be between mPackageMinPower and mPackageMaxPower
        ///
        CpuConvertedPowerLimit1MaxLimit = mPackageMaxPower;

        if (ConvertedPowerLimit1 < mPackageMinPower) {
          ///
          /// If new Power Limit 1 is < mPackageMinPower, program Power Limit 1 to mPackageMinPower
          ///
          ConvertedPowerLimit1 = mPackageMinPower;
        } else if (ConvertedPowerLimit1 > CpuConvertedPowerLimit1MaxLimit) {
          ///
          /// If new Power Limit 1 is > mPackageMaxPower, program Power Limit 1 to mPackageMaxPower
          ///
          ConvertedPowerLimit1 = CpuConvertedPowerLimit1MaxLimit;
        }
      }
    }
    PlatformPowerLimitMsr.Dwords.Low &= ~POWER_LIMIT_MASK;
    PlatformPowerLimitMsr.Dwords.Low |= (UINT32) (ConvertedPowerLimit1);
    DEBUG (
            (DEBUG_INFO,
             "New Platform Power Limit 1  %d watt (%d in CPU power unit)\n",
             gCpuPowerMgmtPsysConfig->PsysPowerLimit1Power,
             ConvertedPowerLimit1)
            );

    ///
    /// Set PlatformPowerLimitMsr.CRITICAL_POWER_CLAMP_1(bit 16)
    ///
    PlatformPowerLimitMsr.Dwords.Low |= (UINT32) B_CRITICAL_POWER_CLAMP_ENABLE;

    ///
    /// Update Platform Power Limit 1 enable bit
    ///
    if (gCpuPowerMgmtPsysConfig->PsysPowerLimit1) {
      PlatformPowerLimitMsr.Dwords.Low |= B_POWER_LIMIT_ENABLE;
    } else {
      ///
      /// When we disable Platform Power Limit we need to write power limit = 0
      ///
      PlatformPowerLimitMsr.Dwords.Low &= ~(POWER_LIMIT_MASK | B_POWER_LIMIT_ENABLE);
    }

    ///
    /// Program Platform Power Limit 1 Time Window
    ///  If PlatformPowerLimit1Time is AUTO OR If PlatformPowerLimit1Time
    ///  is > MAX_POWER_LIMIT_1_TIME_IN_SECONDS program default values
    ///
    if ((gCpuPowerMgmtPsysConfig->PsysPowerLimit1Time == AUTO) ||
        (gCpuPowerMgmtPsysConfig->PsysPowerLimit1Time > MAX_POWER_LIMIT_1_TIME_IN_SECONDS)
        ) {
      if (IS_SA_DEVICE_ID_MOBILE (mProcessorFlavor) || IS_SA_DEVICE_ID_HALO (mProcessorFlavor)) {
        ///
        /// For Mobile and Halo, default value is 28 seconds
        ///
        gCpuPowerMgmtPsysConfig->PsysPowerLimit1Time = MB_POWER_LIMIT1_TIME_DEFAULT;
      } else {
        ///
        /// For Desktop, default value is 1 second
        ///
        gCpuPowerMgmtPsysConfig->PsysPowerLimit1Time = DT_POWER_LIMIT1_TIME_DEFAULT;
      }
    }
    ConvertedPowerLimit1Time = GetConvertedTime (gCpuPowerMgmtPsysConfig->PsysPowerLimit1Time, SecondsTimeWindowConvert);
    ///
    ///  Configure Platform Power Limit 1 time windows: Platform Power Limit MSR [23:17]
    ///
    PlatformPowerLimitMsr.Dwords.Low &= ~POWER_LIMIT_1_TIME_MASK;
    PlatformPowerLimitMsr.Dwords.Low |= (UINT32) LShiftU64 (ConvertedPowerLimit1Time, 17);
    ///
    /// gTurboSettings->PlatformPowerLimit2Power value is in mW or watts. We need to convert it to
    /// CPU Power unit, specified in PACKAGE_POWER_SKU_UNIT_MSR[3:0].Since we are converting
    /// from Watts to CPU power units, multiply by PACKAGE_POWER_SKU_UNIT_MSR[3:0]
    ///
    ConvertedPowerLimit2 = (UINT16) ((gCpuPowerMgmtPsysConfig->PsysPowerLimit2Power * mProcessorPowerUnit) / mCustomPowerUnit);
    PlatformPowerLimitMsr.Dwords.High &= ~(POWER_LIMIT_MASK | B_POWER_LIMIT_ENABLE);
    ///
    /// If PlatformPowerLimit2 is AUTO OR if PlatformPowerLimit2 is > mPackageMaxPower
    /// OR if Platform PowerLimit2 < mPackageMinPower program defaul values.
    ///
    CpuConvertedPowerLimit2MaxLimit = mPackageMaxPower;
    if (CpuConvertedPowerLimit2MaxLimit == 0) {
      CpuConvertedPowerLimit2MaxLimit = (UINT16) (LShiftU64 (2, 15) - 1);
    }
    if (gCpuPowerMgmtPsysConfig->PsysPowerLimit2Power == AUTO) {
      ConvertedPowerLimit2 = EFI_IDIV_ROUND ((Multiplier * mPackageTdp), 100);

    }
    if (ConvertedPowerLimit2 > CpuConvertedPowerLimit2MaxLimit) {
      ConvertedPowerLimit2 = CpuConvertedPowerLimit2MaxLimit;
    }
    if (ConvertedPowerLimit2 < mPackageMinPower) {
      ConvertedPowerLimit2 = mPackageMinPower;
    }
    PlatformPowerLimitMsr.Dwords.High |= (UINT32) (ConvertedPowerLimit2);

    if (gCpuPowerMgmtPsysConfig->PsysPowerLimit2 == TRUE) {
      PlatformPowerLimitMsr.Dwords.High |= B_POWER_LIMIT_ENABLE;
    } else {
      ///
      /// When we disable Platform Power Limit we need to write power limit = 0
      ///
      PlatformPowerLimitMsr.Dwords.High &= ~(POWER_LIMIT_MASK | B_POWER_LIMIT_ENABLE);
    }

    DEBUG (
            (DEBUG_INFO,
             "Platform Power Limit 2 Power = %d Watts (%d in CPU power unit)\n",
             gCpuPowerMgmtPsysConfig->PsysPowerLimit2Power,
             ConvertedPowerLimit2)
            );

    DEBUG ((DEBUG_INFO,"MSR(65Ch)=%08X%08X\n",PlatformPowerLimitMsr.Dwords.High,PlatformPowerLimitMsr.Dwords.Low));

    AsmWriteMsr64 (MSR_PLATFORM_POWER_LIMIT, PlatformPowerLimitMsr.Qword);
}

/**
  Configures PowerLimits and Config TDP values
**/
VOID
ConfigureCtdp (
  VOID
  )
{
  UINT8 CustomPowerLimits;
  UINT8 Index;
  ///
  /// Configure CTDP power limits.Refer Rev 0.6.0 BWG sec 16.7.1: Enabling Intel Configurable TDP support
  ///
  ConfigureCtdpPowerLimits ();

  ///
  ///
  /// Check if any power limits are overriden, flag CustomPowerLimits if detected
  ///
  CustomPowerLimits = FALSE;
  for (Index = 0; Index < MAX_CUSTOM_CTDP_ENTRIES; Index++) {
    if (gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomPowerLimit1 != 0 ||
        gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomPowerLimit1Time != 0 ||
        gCpuPowerMgmtCustomConfig->CustomConfigTdpTable[Index].CustomPowerLimit2 != 0) {
      CustomPowerLimits = TRUE;
    }
  }

  ///
  /// BIOS power limit overrides
  /// Don't override if custom ctdp settings are provided.
  ///
  if (CustomPowerLimits == FALSE) {
    ConfigureCtdpPowerLimitsOverrides ();
  }
  ///
  /// To avoid issues and race conditions it is recommended for the below order to be followed:
  ///    - For TDP Up program the Power Limits followed by Config TDP Level
  ///    - For TDP Down program the Config TDP Level followed by Power Limits
  ///
  if (gCpuPowerMgmtTestConfig->ConfigTdpLevel == CONFIG_TDP_UP) {
    SelectCtdpPowerLimits (gCpuGlobalNvsAreaConfig->Area->ConfigTdpBootModeIndex);
    SelectCtdpLevel (gCpuGlobalNvsAreaConfig->Area->ConfigTdpBootModeIndex);
  } else {
    SelectCtdpLevel (gCpuGlobalNvsAreaConfig->Area->ConfigTdpBootModeIndex);
    SelectCtdpPowerLimits (gCpuGlobalNvsAreaConfig->Area->ConfigTdpBootModeIndex);
  }
}
