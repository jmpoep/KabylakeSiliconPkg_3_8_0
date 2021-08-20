/** @file
  Initializes PCH power management controller.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ConfigBlockLib.h>
#include <PchAccess.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/PchSbiAccessLib.h>
#include <Library/PchHsioLib.h>
#include <Library/PchEspiLib.h>
#include <Library/MmPciLib.h>
#include <Ppi/SiPolicy.h>
#include <Private/PchHsio.h>
#include <Private/Ppi/PchPmcXramOffsetData.h>
#include <Private/Library/CpuCommonLib.h>
#include <Private/Library/PchPsfPrivateLib.h>

//
// PCH - CPU Power sharing defines
//
#define PCH2CPU_PWR_LIM_WIDTH           5
#define PCH2CPU_PWR_LIM_WIDTH_MASK      0x1F
#define NUM_PRIMARY_PCH2CPU_PL_SUPPORT  3
#define NUM_EXTENDED_PCH2CPU_PL_SUPPORT 4

/**
  Configure PMC related settings when SCS controllers are disabled.
**/
VOID
ConfigurePmcWhenScsDisabled (
  BOOLEAN                               Disable
  )
{
  UINT32                                PchPwrmBase;

  PchPwrmBaseGet (&PchPwrmBase);

  if (Disable == TRUE) {
    MmioOr32 (
      PchPwrmBase + R_PCH_PWRM_31C,
      BIT14
      );
  } else {
    MmioAnd32 (
      PchPwrmBase + R_PCH_PWRM_31C,
      (UINT32) ~BIT14
      );
  }
}

/**
  Configure PMC related settings when CIO2 controllers is disabled.
**/
VOID
ConfigurePmcWhenCio2Disabled (
  BOOLEAN                               Disable
  )
{
  UINT32                                PchPwrmBase;
  PCH_STEPPING                          PchStep;

  PchPwrmBaseGet (&PchPwrmBase);
  PchStep   = PchStepping ();

  if (Disable == TRUE) {
    MmioOr32 (
      PchPwrmBase + R_PCH_PWRM_31C,
      BIT12
      );
  } else {
    if (PchStep >= PchLpC0) {
      MmioAnd32 (
        PchPwrmBase + R_PCH_PWRM_31C,
        (UINT32) ~BIT12
        );
    }
  }
}

/**
  Configure deep Sx programming

  @param[in] SiPolicy                   The SI Policy instance

  @retval EFI_SUCCESS                   The function completed successfully
**/
EFI_STATUS
ProgramDeepSx (
  SI_POLICY_PPI               *SiPolicy
  )
{
  UINT32                                PchPwrmBase;
  UINT32                                S3Data32;
  UINT32                                S4Data32;
  UINT32                                S5Data32;
  EFI_STATUS                            Status;
  PCH_PM_CONFIG                         *PmConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);

  PchPwrmBaseGet (&PchPwrmBase);
  ///
  /// PCH BIOS Spec Section 19.11  Deep Sx Power Policies
  /// The System BIOS can perform the following register programming guidelines to enable system
  /// enter Deep S3, Deep S4 or Deep S5.
  ///
  ///                            DPS3_EN_DC          DPS3_EN_AC               DPS4_EN_DC              DPS4_EN_AC             DPS5_EN_DC             DPS5_EN_AC
  ///                           PchPwrmBase+28h[1]   PchPwrmBase + 28h[0]     PchPwrmBase + 2Ch[1]    PchPwrmBase + 2Ch[0]   PchPwrmBase + 30h[15]  PchPwrmBase + 30h[14]
  /// Deep Sx disabled                 0              0                            0                        0                       0                 0
  ///
  /// Enabled in S5                    0              0                            0                        0                       1                 1
  ///
  /// Enabled in S4 and S5             0              0                            1                        1                       1                 1
  ///
  /// Enabled in S3, S4 and S5         1              1                            1                        1                       1                 1
  ///
  /// Configuration supported by MOBILE:
  /// Enabled in S5                    0              0                            0                        0                       1                 0
  /// (Battery mode)
  /// Enabled in S4 and S5             0              0                            1                        0                       1                 0
  /// (Battery Mode)
  /// Enabled in S3, S4 and S5         1              0                            1                        0                       1                 0
  /// (Battery Mode)
  ///
  /// NOTE: Mobile platforms support Deep S3/S4/S5 in DC ONLY,
  /// Desktop and Intel C206 Chipset (LPC Dev ID 0x1C56) platforms support Deep S3/S4/S5 in AC ONLY,
  /// Intel C204 Chipset (LPC Dev ID 0x1C54) and Intel C202 Chipset (LPC Dev ID 0x1C52) platforms DO NOT support Deep S4/S5.
  ///
  /// Deep Sx disabled                 0              0                   0                 0                 0                 0
  ///
  switch (PmConfig->PchDeepSxPol) {
    case PchDpS5AlwaysEn:
      ///
      /// Configuration 2: Enabled in S5/AC-DC
      /// DEEP_S3_POL.DPS3_EN_DC = 0; DEEP_S3_POL.DPS3_EN_AC = 0;
      /// DEEP_S4_POL.DPS4_EN_DC = 0; DEEP_S4_POL.DPS4_EN_AC = 0;
      /// DEEP_S5_POL.DPS5_EN_DC = 1; DEEP_S5_POL.DPS5_EN_AC = 1;
      ///
      S3Data32  = 0;
      S4Data32  = 0;
      S5Data32  = (UINT32) (B_PCH_PWRM_S5AC_GATE_SUS | B_PCH_PWRM_S5DC_GATE_SUS);
      break;

    case PchDpS4S5AlwaysEn:
      ///
      /// Configuration 4: Enabled only in S4-S5
      /// DEEP_S3_POL.DPS3_EN_DC = 0; DEEP_S3_POL.DPS3_EN_AC = 0;
      /// DEEP_S4_POL.DPS4_EN_DC = 1; DEEP_S4_POL.DPS4_EN_AC = 1;
      /// DEEP_S5_POL.DPS5_EN_DC = 1; DEEP_S5_POL.DPS5_EN_AC = 1;
      ///
      S3Data32  = 0;
      S4Data32  = (UINT32) (B_PCH_PWRM_S4AC_GATE_SUS | B_PCH_PWRM_S4DC_GATE_SUS);
      S5Data32  = (UINT32) (B_PCH_PWRM_S5AC_GATE_SUS | B_PCH_PWRM_S5DC_GATE_SUS);
      break;

    case PchDpS3S4S5AlwaysEn:
      ///
      /// Configuration 6: Enabled only in S3-S4-S5
      /// DEEP_S3_POL.DPS3_EN_DC = 1; DEEP_S3_POL.DPS3_EN_AC = 1;
      /// DEEP_S4_POL.DPS4_EN_DC = 1; DEEP_S4_POL.DPS4_EN_AC = 1;
      /// DEEP_S5_POL.DPS5_EN_DC = 1; DEEP_S5_POL.DPS5_EN_AC = 1;
      ///
      S3Data32  = (UINT32) (B_PCH_PWRM_S3AC_GATE_SUS | B_PCH_PWRM_S3DC_GATE_SUS);
      S4Data32  = (UINT32) (B_PCH_PWRM_S4AC_GATE_SUS | B_PCH_PWRM_S4DC_GATE_SUS);
      S5Data32  = (UINT32) (B_PCH_PWRM_S5AC_GATE_SUS | B_PCH_PWRM_S5DC_GATE_SUS);
      break;

    case PchDpS5BatteryEn:
      ///
      /// Configuration 1: Enabled in S5/Battery only
      /// DEEP_S3_POL.DPS3_EN_DC = 0; DEEP_S3_POL.DPS3_EN_AC = 0;
      /// DEEP_S4_POL.DPS4_EN_DC = 0; DEEP_S4_POL.DPS4_EN_AC = 0;
      /// DEEP_S5_POL.DPS5_EN_DC = 1; DEEP_S5_POL.DPS5_EN_AC = 0;
      ///
      S3Data32  = 0;
      S4Data32  = 0;
      S5Data32  = (UINT32) (B_PCH_PWRM_S5DC_GATE_SUS);
      break;

    case PchDpS4S5BatteryEn:
      ///
      /// Configuration 3: Enabled only in S4-S5/Battery Mode
      /// DEEP_S3_POL.DPS3_EN_DC = 0; DEEP_S3_POL.DPS3_EN_AC = 0;
      /// DEEP_S4_POL.DPS4_EN_DC = 1; DEEP_S4_POL.DPS4_EN_AC = 0;
      /// DEEP_S5_POL.DPS5_EN_DC = 1; DEEP_S5_POL.DPS5_EN_AC = 0;
      ///
      S3Data32  = 0;
      S4Data32  = (UINT32) (B_PCH_PWRM_S4DC_GATE_SUS);
      S5Data32  = (UINT32) (B_PCH_PWRM_S5DC_GATE_SUS);
      break;

    case PchDpS3S4S5BatteryEn:
      ///
      /// Configuration 5: Enabled only in S4-S5/Battery Mode
      /// DEEP_S3_POL.DPS3_EN_DC = 1; DEEP_S3_POL.DPS3_EN_AC = 0;
      /// DEEP_S4_POL.DPS4_EN_DC = 1; DEEP_S4_POL.DPS4_EN_AC = 0;
      /// DEEP_S5_POL.DPS5_EN_DC = 1; DEEP_S5_POL.DPS5_EN_AC = 0;
      ///
      S3Data32  = (UINT32) (B_PCH_PWRM_S3DC_GATE_SUS);
      S4Data32  = (UINT32) (B_PCH_PWRM_S4DC_GATE_SUS);
      S5Data32  = (UINT32) (B_PCH_PWRM_S5DC_GATE_SUS);
      break;

    case PchDeepSxPolDisable:
    default:
      ///
      /// Configuration 5: DeepSx Disabled
      /// DEEP_S3_POL.DPS3_EN_DC = 0; DEEP_S3_POL.DPS3_EN_AC = 0;
      /// DEEP_S4_POL.DPS4_EN_DC = 0; DEEP_S4_POL.DPS4_EN_AC = 0;
      /// DEEP_S5_POL.DPS5_EN_DC = 0; DEEP_S5_POL.DPS5_EN_AC = 0;
      ///
      S3Data32  = 0;
      S4Data32  = 0;
      S5Data32  = 0;
      break;
  }

  MmioWrite32 ((PchPwrmBase + R_PCH_PWRM_S3_PWRGATE_POL), S3Data32);
  MmioWrite32 ((PchPwrmBase + R_PCH_PWRM_S4_PWRGATE_POL), S4Data32);
  MmioWrite32 ((PchPwrmBase + R_PCH_PWRM_S5_PWRGATE_POL), S5Data32);

  return EFI_SUCCESS;
}

/**
  Configure miscellaneous power management settings

  @param[in] SiPolicy          The SI Policy instance

  @retval EFI_SUCCESS          The function completed successfully
**/
EFI_STATUS
ConfigureMiscPm (
  IN  SI_POLICY_PPI           *SiPolicy
  )
{
  EFI_STATUS                            Status;
  UINTN                                 PciPmcRegBase;
  UINT32                                PchPwrmBase;
  UINT32                                Data32;
  UINT32                                PmConA;
  UINT32                                PmConB;
  PCH_SERIES                            PchSeries;
  PCH_STEPPING                          PchStep;
  PCH_PM_CONFIG                         *PmConfig;
  PCH_DMI_CONFIG                        *DmiConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gDmiConfigGuid, (VOID *) &DmiConfig);
  ASSERT_EFI_ERROR (Status);

  PciPmcRegBase = MmPciBase (
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_PMC,
                    PCI_FUNCTION_NUMBER_PCH_PMC
                    );

  PchPwrmBaseGet (&PchPwrmBase);
  PchStep   = PchStepping ();
  PchSeries = GetPchSeries ();

  ///
  /// Clear power / reset status bits on PCH Corporate
  ///
  Data32 = 0;
  if (PmConfig->MeWakeSts) {
    Data32 |= B_PCH_PWRM_PRSTS_ME_WAKE_STS;
  }
  if (PmConfig->WolOvrWkSts) {
    Data32 |= B_PCH_PWRM_PRSTS_WOL_OVR_WK_STS;
  }
  ///
  /// Handling Status Registers
  /// System BIOS must set 1b to clear the following registers during power-on
  /// and resuming from Sx sleep state.
  /// - PWRMBASE + Offset 10h[0] = 1b
  /// - PWRMBASE + Offset 10h[4] = 1b, needs to be done as early as possible during PEI
  ///   Done in PchEarlyInit ()
  /// - PWRMBASE + Offset 10h[5] = 1b
  ///
  MmioOr32 (PchPwrmBase + R_PCH_PWRM_PRSTS, Data32);

  ///
  /// We need to enable LAN_WAKE_PIN_DSX_EN for Wake from both SX and DSX
  ///
  Data32 = MmioRead32 (PchPwrmBase + R_PCH_PWRM_DSX_CFG);
  if (PmConfig->WakeConfig.LanWakeFromDeepSx == TRUE) {
    Data32 |= B_PCH_PWRM_DSX_CFG_LAN_WAKE_EN;
  } else {
    Data32 &= ~B_PCH_PWRM_DSX_CFG_LAN_WAKE_EN;
  }
  //
  // Disable PCH internal AC PRESENT pulldown
  //
  if (PmConfig->DisableDsxAcPresentPulldown) {
    Data32 |= B_PCH_PWRM_DSX_CFG_ACPRES_PD_DSX_DIS;
  } else {
    Data32 &= ~B_PCH_PWRM_DSX_CFG_ACPRES_PD_DSX_DIS;
  }
  ///
  /// Enable WAKE_PIN__DSX_EN for Wake
  ///
  if (PmConfig->WakeConfig.PcieWakeFromDeepSx) {
    Data32 |= B_PCH_PWRM_DSX_CFG_WAKE_PIN_DSX_EN;
  } else {
    Data32 &= ~B_PCH_PWRM_DSX_CFG_WAKE_PIN_DSX_EN;
  }
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_DSX_CFG, Data32);

  ///
  /// Handle wake policy
  ///
  PmConA = MmioRead32 (PciPmcRegBase + R_PCH_PMC_GEN_PMCON_A);
  PmConB = MmioRead32 (PciPmcRegBase + R_PCH_PMC_GEN_PMCON_B);

  //
  // Don't clear B_PCH_PMC_GEN_PMCON_A_MS4V, B_PCH_PMC_GEN_PMCON_A_GBL_RST_STS,
  // B_PCH_PMC_GEN_PMCON_B_SUS_PWR_FLR, B_PCH_PMC_GEN_PMCON_B_HOST_RST_STS, B_PCH_PMC_GEN_PMCON_B_PWR_FLR by accident
  // since those are RW/1C.
  //
  PmConA &= (UINT32) ~(B_PCH_PMC_GEN_PMCON_A_MS4V | B_PCH_PMC_GEN_PMCON_A_GBL_RST_STS);
  PmConB &= (UINT32) ~(B_PCH_PMC_GEN_PMCON_B_SUS_PWR_FLR | B_PCH_PMC_GEN_PMCON_B_HOST_RST_STS | B_PCH_PMC_GEN_PMCON_B_PWR_FLR);

  PmConB &= (UINT32) ~(B_PCH_PMC_GEN_PMCON_B_PME_B0_S5_DIS | B_PCH_PMC_GEN_PMCON_B_WOL_EN_OVRD);

  if (PmConfig->WakeConfig.PmeB0S5Dis) {
    PmConB |= B_PCH_PMC_GEN_PMCON_B_PME_B0_S5_DIS;
  }

  if (PmConfig->WakeConfig.WolEnableOverride) {
    ///
    /// Wake-On-LAN (WOL) Implementation
    /// Step 1
    /// Clear PMC PCI offset A0h[30] = 0b to ensure the LAN PHY will be powered for WOL
    /// when the power source is either the AC or the DC battery.
    ///
    PmConA &= (UINT32) ~B_PCH_PMC_GEN_PMCON_A_DC_PP_DIS;

    ///
    /// Step 2
    /// Clear PMC PCI offset A0h[29] = 0b to ensure the LAN PHY will be powered for WOL in Deep Sx.
    ///
    PmConA &= (UINT32) ~B_PCH_PMC_GEN_PMCON_A_DSX_PP_DIS;

    ///
    /// Step 3
    /// Set PMC PCI offset A0h[28] = 1b to ensure the LAN PHY will be powered for WOL after a G3 transition.
    ///
    PmConA |= (UINT32) B_PCH_PMC_GEN_PMCON_A_AG3_PP_EN;

    ///
    /// Step 4
    /// Set PMC PCI offset A0h[27] = 1b to ensure the LAN PHY will be powered for WOL from Sx.
    ///
    PmConA |= (UINT32) B_PCH_PMC_GEN_PMCON_A_SX_PP_EN;

    ///
    /// Step 5
    /// "PME_B0_EN", ABASE + Offset 28h[13], bit must be programmed to enable wakes
    /// from S1-S4 at the Power Management Controller
    /// Done in ASL code(_PRW)
    ///
    ///
    /// Step 6
    /// Set "WOL Enable Override", PMC PCI offset A4h[13], bit to 1b to guarantee the
    /// LAN-Wakes are enabled at the Power Management Controller, even in surprise
    /// S5 cases such as power loss/return and Power Button Override
    ///
    PmConB |= B_PCH_PMC_GEN_PMCON_B_WOL_EN_OVRD;

    ///
    /// Step 7
    /// Moreover, system BIOS also require to enables in the LAN device by performing
    /// the WOL configuration requirements in the GbE region of the SPI flash.
    /// Done in PchSmmSxGoToSleep() SMM handler.
    ///
  } else {
    ///
    /// PMC PCI offset A0h[30:27] and PMC PCI offset A4h[13] are all in RTC or DSW well, so BIOS also
    /// needs to program them while WOL setup option is disabled.
    ///
    PmConA &= (UINT32) ~(B_PCH_PMC_GEN_PMCON_A_AG3_PP_EN | B_PCH_PMC_GEN_PMCON_A_SX_PP_EN);
    PmConA |= (B_PCH_PMC_GEN_PMCON_A_DC_PP_DIS | B_PCH_PMC_GEN_PMCON_A_DSX_PP_DIS);

    PmConB &= (UINT32) ~(B_PCH_PMC_GEN_PMCON_B_WOL_EN_OVRD);
  }

  ///
  /// Configure On DC PHY Power Diable according to policy SlpLanLowDc.
  /// When this bit is set, SLP_LAN# will be driven low when ACPRESENT is low.
  /// This indicates that LAN PHY should be powered off on battery mode.
  /// This will override the DC_PP_DIS setting by WolEnableOverride.
  ///
  if (PmConfig->SlpLanLowDc) {
    PmConA |= (UINT32) (B_PCH_PMC_GEN_PMCON_A_DC_PP_DIS);
  } else {
    PmConA &= (UINT32) ~(B_PCH_PMC_GEN_PMCON_A_DC_PP_DIS);
  }

  ///
  /// Enabling SLP_S3# and SLP_S4# Stretch
  /// PMC PCI offset A4h[12:10]
  /// PMC PCI offset A4h[5:3]
  ///
  PmConB &= (UINT32) ~(B_PCH_PMC_GEN_PMCON_B_SLP_S3_MAW | B_PCH_PMC_GEN_PMCON_B_SLP_S4_MAW);

  switch (PmConfig->PchSlpS3MinAssert) {
    case PchSlpS360us:
      PmConB |= V_PCH_PMC_GEN_PMCON_B_SLP_S3_MAW_60US;
      break;

    case PchSlpS31ms:
      PmConB |= V_PCH_PMC_GEN_PMCON_B_SLP_S3_MAW_1MS;
      break;

    case PchSlpS350ms:
    default:
      PmConB |= V_PCH_PMC_GEN_PMCON_B_SLP_S3_MAW_50MS;
      break;

    case PchSlpS32s:
      PmConB |= V_PCH_PMC_GEN_PMCON_B_SLP_S3_MAW_2S;
      break;
  }

  switch (PmConfig->PchSlpS4MinAssert) {
    case PchSlpS4PchTime:
      PmConB &= (UINT32) (~B_PCH_PMC_GEN_PMCON_B_SLP_S4_ASE);
      break;

    case PchSlpS41s:
      PmConB |= V_PCH_PMC_GEN_PMCON_B_SLP_S4_MAW_1S | B_PCH_PMC_GEN_PMCON_B_SLP_S4_ASE;
      break;

    case PchSlpS42s:
      PmConB |= V_PCH_PMC_GEN_PMCON_B_SLP_S4_MAW_2S | B_PCH_PMC_GEN_PMCON_B_SLP_S4_ASE;
      break;

    case PchSlpS43s:
      PmConB |= V_PCH_PMC_GEN_PMCON_B_SLP_S4_MAW_3S | B_PCH_PMC_GEN_PMCON_B_SLP_S4_ASE;
      break;

    case PchSlpS44s:
    default:
      PmConB |= V_PCH_PMC_GEN_PMCON_B_SLP_S4_MAW_4S | B_PCH_PMC_GEN_PMCON_B_SLP_S4_ASE;
      break;
  }

  if (PmConfig->SlpStrchSusUp == FALSE) {
    PmConB |= B_PCH_PMC_GEN_PMCON_B_DISABLE_SX_STRETCH;
  } else {
    PmConB &= (UINT32) ~B_PCH_PMC_GEN_PMCON_B_DISABLE_SX_STRETCH;
  }

  MmioWrite32 (PciPmcRegBase + R_PCH_PMC_GEN_PMCON_A, PmConA);
  MmioWrite32 (PciPmcRegBase + R_PCH_PMC_GEN_PMCON_B, PmConB);

  ///
  /// Set Power Management Initialization Register (PMIR) Field 1, PMC PCI offset ACh[31] = 1b
  /// Done in Intel Management Engine Framework Reference Code
  /// Set GEN_PMCON_LOCK register, PMC PCI offset A6h = 06h, after stretch and ACPI base programming completed.
  /// Done in PchOnEndOfDxe()
  ///

  ///
  /// Note: PchPwrmBase + 18h[19:16] are platform dependent settings (0Fh provides longest assertion),
  /// please consult with your board design engineers for correct values to be programmed to.
  ///
  /// For PchPwrmBase + 18h[9:8] Reset Power Cycle Duration could be customized, please refer to EDS
  /// and make sure the setting correct, which never less than the following register.
  /// - GEN_PMCON_3.SLP_S3_MIN_ASST_WDTH
  /// - GEN_PMCON_3.SLP_S4_MIN_ASST_WDTH
  /// - PM_CFG.SLP_A_MIN_ASST_WDTH
  /// - PM_CFG.SLP_LAN_MIN_ASST_WDTH
  ///
  Data32 = MmioRead32 (PchPwrmBase + R_PCH_PWRM_CFG);
  Data32 &= (UINT32) ~(B_PCH_PWRM_CFG_SSMAW_MASK | B_PCH_PWRM_CFG_SAMAW_MASK | B_PCH_PWRM_CFG_RPCD_MASK);
  switch (PmConfig->PchSlpSusMinAssert) {
    case PchSlpSus0ms:
      Data32 |= V_PCH_PWRM_CFG_SSMAW_0S;
      break;

    case PchSlpSus500ms:
      Data32 |= V_PCH_PWRM_CFG_SSMAW_0_5S;
      break;

    case PchSlpSus1s:
      Data32 |= V_PCH_PWRM_CFG_SSMAW_1S;
      break;

    case PchSlpSus4s:
    default:
      Data32 |= V_PCH_PWRM_CFG_SSMAW_4S;
      break;
  }
  switch (PmConfig->PchSlpAMinAssert) {
    case PchSlpA0ms:
      Data32 |= V_PCH_PWRM_CFG_SAMAW_0S;
      break;

    case PchSlpA4s:
      Data32 |= V_PCH_PWRM_CFG_SAMAW_4S;
      break;

    case PchSlpA98ms:
      Data32 |= V_PCH_PWRM_CFG_SAMAW_98ms;
      break;

    case PchSlpA2s:
    default:
      Data32 |= V_PCH_PWRM_CFG_SAMAW_2S;
      break;
  }
  switch (PmConfig->PchPwrCycDur) {
    case 0:  // treat as PCH default
      Data32 |= V_PCH_PWRM_CFG_RPCD_4S;
      break;

    case 1:
      Data32 |= V_PCH_PWRM_CFG_RPCD_1S;
      break;

    case 2:
      Data32 |= V_PCH_PWRM_CFG_RPCD_2S;
      break;

    case 3:
      Data32 |= V_PCH_PWRM_CFG_RPCD_3S;
      break;

    case 4:
      Data32 |= V_PCH_PWRM_CFG_RPCD_4S;
      break;

    default:
      Data32 |= V_PCH_PWRM_CFG_RPCD_4S;
      DEBUG ((DEBUG_ERROR, "Invalid value for PchPwrCycDur. Using 4Sec as the default value.\n"));
      break;
  }
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_CFG, Data32);

  ///
  /// For wake on WLAN from S3/S4/S5, set PWRM_CFG3 [BIT17], HOST_WLAN_PP_EN = 1
  ///
  if (PmConfig->WakeConfig.WoWlanEnable == TRUE) {
    MmioOr32 (PchPwrmBase + R_PCH_PWRM_CFG3, B_PCH_PWRM_CFG3_HOST_WLAN_PP_EN);
    ///
    /// For wake on WLAN from DeepSx S3/S4/S5, set PWRM_CFG3 [BIT16], DSX_WLAN_PP_EN = 1
    ///
    if (PmConfig->WakeConfig.WoWlanDeepSxEnable == TRUE) {
      MmioOr32 (PchPwrmBase + R_PCH_PWRM_CFG3, B_PCH_PWRM_CFG3_DSX_WLAN_PP_EN);
    }
  }


  return EFI_SUCCESS;
}

/**
  Configure PCH to CPU energy report

  @param[in] SiPolicy                  The SI Policy instance

**/
VOID
ConfigureEnergyReport (
  IN  SI_POLICY_PPI                    *SiPolicy
  )
{
  UINT32                                PchPwrmBase;
  PCH_SERIES                            PchSeries;
  PCH_STEPPING                          PchStep;
  PCH_GENERATION                        PchGen;
  EFI_STATUS                            Status;
  PCH_PM_CONFIG                         *PmConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);

  if (PmConfig->DisableEnergyReport) {
    return;
  }

  PchPwrmBaseGet (&PchPwrmBase);
  PchStep   = PchStepping ();
  PchSeries = GetPchSeries ();
  PchGen    = GetPchGeneration ();

  //
  // Energy Report is supported on PCH-LP C0+, SKL-PCH-H C0+ and all KBL-PCH-H.
  // The Energy Report is supported by all CPU steppings except B0.
  // All the latest microcode can support the feature. So
  // must make sure the latest microcode patch is loaded.
  //
  // CPU stepping    Microcode Patch version
  // C0/J0           0x26
  // D0/K0           0x0A
  // Q0              0x22
  // M0              0x22
  // R0              0x0A
  // All new steppings
  //
  if ((PchGen == SklPch) &&
     (((PchSeries == PchLp) && (PchStep < PchLpC0)) ||
      ((PchSeries == PchH) && (PchStep < PchHC0)))) {
    return;
  }


  //
  // PM_CFG (0x018h[2]) = 1
  // PM_CFG (0x018h[24]) = 1  Must perform this setting as a separate write
  //
  MmioOr32 (PchPwrmBase + R_PCH_PWRM_CFG, BIT2);
  MmioOr32 (PchPwrmBase + R_PCH_PWRM_CFG, BIT24);
}

/**
  Configure SPI/eSPI power management
**/
VOID
ConfigureSpiPm (
  VOID
  )
{
  //
  // Set SPI PCR 0xC004 bits 29, 10-8, 5-0 to 1b, 111b, 11111b
  // Clear SPI PCR 0xC008 bit 2,1,0
  PchPcrAndThenOr32 (PID_ESPISPI, R_PCH_PCR_SPI_CLK_CTL, ~0u, 0x2000073F);
  PchPcrAndThenOr32 (PID_ESPISPI, R_PCH_PCR_SPI_PWR_CTL, (UINT32) ~(BIT2 | BIT1 | BIT0), 0x00);
}

/**
  Configure LPC power management.

  @param[in] SiPolicy                  The SI Policy instance
**/
VOID
ConfigureLpcPm (
  IN  SI_POLICY_PPI                    *SiPolicy
  )
{
  UINTN                                 PciLpcRegBase;
  EFI_STATUS                            Status;
  PCH_PM_CONFIG                         *PmConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);

  PciLpcRegBase   = MmPciBase (
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PCI_DEVICE_NUMBER_PCH_LPC,
                      PCI_FUNCTION_NUMBER_PCH_LPC
                      );

  ///
  /// BIOS need to set LPC PCR 0x341C[13,3:0] to all 1's and [8,9,10] = 0's
  ///
  PchPcrAndThenOr32 (PID_LPC, R_PCH_PCR_LPC_PRC, (UINT32) ~(BIT10 | BIT9 | BIT8), (BIT13 | BIT3 | BIT2 | BIT1 | BIT0));

  ///
  /// System BIOS is also required to set following bit.
  /// PCI CLKRUN# Enable" bit (LPC PCI offset E0h[0]) = 1b
  ///
  if (PmConfig->LpcClockRun == FALSE) {
    MmioAnd16 ((UINTN) (PciLpcRegBase + R_PCH_LPC_PCC), (UINT16) (~B_PCH_LPC_PCC_CLKRUN_EN));
  } else {
    MmioOr16 ((UINTN) (PciLpcRegBase + R_PCH_LPC_PCC), (UINT16) (B_PCH_LPC_PCC_CLKRUN_EN));
  }
}

/**
  Configure PM Timer power management.
  Once PM Timer is disabled, TCO timer stops counting.
  This must be executed after uCode PM timer emulation.

  @param[in] SiPolicy                  The SI Policy PPI instance
**/
VOID
ConfigurePmTimer (
  IN  SI_POLICY_PPI                    *SiPolicy
  )
{
  EFI_STATUS                            Status;
  UINT32                                PchPwrmBase;
  PCH_PM_CONFIG                         *PmConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);

  if (PmConfig->EnableTcoTimer) {
    return;
  }

  PchPwrmBaseGet (&PchPwrmBase);

  DEBUG ((DEBUG_INFO, "ConfigurePmTimer - Disable ACPI timer.\n"));
  //
  // Disable ACPI timer (set PwrmBase + 0xFC[1] = 1), and the TCO timer will also stop.
  //
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_ACPI_TMR_CTL, B_PCH_PWRM_ACPI_TMR_DIS);
}

/**
  Perform power management initialization

  @param[in] SiPolicy                  The SI Policy PPI instance

  @retval EFI_SUCCESS                   Succeeds.
**/
EFI_STATUS
PchPmInit (
  IN  SI_POLICY_PPI                    *SiPolicy
  )
{
  UINTN                                 PciPmcRegBase;
  UINT32                                PchPwrmBase;
  UINT32                                Data32;
  UINT32                                Data32And;
  UINT32                                Data32Or;
  PCH_SERIES                            PchSeries;
  UINT8                                 LaneOwner;
  UINT8                                 PortId;
  UINT8                                 LaneNum;
  UINT8                                 MaxUsb3LaneNum;
  EFI_STATUS                            Status;
  PCH_DCI_PREMEM_CONFIG                 *DciPreMemConfig;
  PCH_PM_CONFIG                         *PmConfig;
  SI_PREMEM_POLICY_PPI                  *SiPreMemPolicy;

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **)&SiPreMemPolicy
             );
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gDciPreMemConfigGuid, (VOID *) &DciPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);

  PciPmcRegBase = MmPciBase (
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_PMC,
                    PCI_FUNCTION_NUMBER_PCH_PMC
                    );
  PchPwrmBaseGet (&PchPwrmBase);

  PchSeries  = GetPchSeries ();
  Data32     = 0;


  //
  // Perform PM recommendation settings
  //

  ///
  /// GEN_PMCON_A (0x0A0h[13]) = 1, Allow OPI PLL Shutdown in C0 (ALLOW_OPI_PLL_SD_INC0)
  /// GEN_PMCON_A (0x0A0h[12]) = 1, Allow SPXB Clock Gating in C0 (ALLOW_SPXB_CG_INC0)
  /// GEN_PMCON_A (0x0A0h[7])  = 1, Allow L1.LOW Entry during C0 (ALLOW_L1LOW_C0)
  /// GEN_PMCON_A (0x0A0h[6])  = 1, Allow L1.LOW Entry with OPI Voltage ON (ALLOW_L1LOW_OPI_ON)
  /// GEN_PMCON_A (0x0A0h[5])  = 1, Allow L1.LOW Entry with CPU BCLK REQ Asserted (ALLOW_L1LOW_BCLKREQ_ON)
  ///
  //
  // Do not clear those RW/1C bits by accident.
  //
  MmioAndThenOr32 (
    PciPmcRegBase + R_PCH_PMC_GEN_PMCON_A,
    (UINT32) ~(B_PCH_PMC_GEN_PMCON_A_MS4V | B_PCH_PMC_GEN_PMCON_A_GBL_RST_STS),
    B_PCH_PMC_GEN_PMCON_A_ALLOW_OPI_PLL_SD_INC0 |
    B_PCH_PMC_GEN_PMCON_A_ALLOW_SPXB_CG_INC0 |
    B_PCH_PMC_GEN_PMCON_A_ALLOW_L1LOW_C0 |
    B_PCH_PMC_GEN_PMCON_A_ALLOW_L1LOW_OPI_ON |
    B_PCH_PMC_GEN_PMCON_A_ALLOW_L1LOW_BCLKREQ_ON
    );

  ///
  /// PMC CFG offset 0xA8 [14, 10, 9] to all 1
  /// This register MUST be programmed before PM_SYNC_MODE is programmed.
  ///
  MmioOr32 (
    PciPmcRegBase + R_PCH_PMC_BM_CX_CNF,
    B_PCH_PMC_BM_CX_CNF_PHOLD_BM_STS_BLOCK |
    B_PCH_PMC_BM_CX_CNF_BM_STS_ZERO_EN |
    B_PCH_PMC_BM_CX_CNF_PM_SYNC_MSG_MODE
    );

  ///
  /// PWRMBASE + 0x14 [24,18,16,13,11,10,9,8,7,6,5,4,3,2,1,0] = all 1s
  ///
  MmioOr32 (
    PchPwrmBase + R_PCH_PWRM_14,
    BIT24 | BIT18 | BIT16 | BIT13 | BIT11 | BIT10 | BIT9 | BIT8 | BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0
    );

  ///
  /// PWRMBASE + 0x3C[23,22] = 11b
  /// Bit[26] should be set/clear once BIOS is ready to bring DRAM out of reset (handled in SA)
  ///
  Data32Or = BIT23 | BIT22;
  ///
  /// PWRMBASE + 0x3C[31:29]
  /// For PCH power button override period, 0=4sec, 011b=10sec
  ///
  Data32Or |= (PmConfig->PwrBtnOverridePeriod) << N_PCH_PWRM_CFG2_PBOP;
  ///
  /// PWRMBASE + 0x3C[28] for power button native mode disable
  ///
  if (PmConfig->DisableNativePowerButton) {
    Data32Or |= B_PCH_PWRM_CFG2_PB_DIS;
  }
  MmioAndThenOr32 (PchPwrmBase + R_PCH_PWRM_CFG2, (UINT32)~(B_PCH_PWRM_CFG2_PBOP | B_PCH_PWRM_CFG2_PB_DIS), Data32Or);

  ///
  /// PWRMBASE + 0x48 = 0x1E2DD701
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_SN_SLOW_RING, 0x1E2DD701);

  ///
  /// PWRMBASE + 0x4C = 0x00000001
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_SN_SLOW_RING2, 1);

  ///
  /// PWRMBASE + 0x50 = 0x1E2DD701
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_SN_SA, 0x1E2DD701);

  ///
  /// PWRMBASE + 0x54 = 0x00000001
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_SN_SA2, 1);

  ///
  /// PWRMBASE + 0x58 = 0x0001C000
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_SN_SLOW_RING_CF, 0x0001C000);

  ///
  /// PWRMBASE + 0x68 = 0x04043400
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_NS_SA, 0x04043400);

  ///
  /// PWRMBASE + 0x80 = 0xBF8FF701
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_CW_SLOW_RING, 0xBF8FF701);

  ///
  /// PWRMBASE + 0x84 = 0x0201C7E1
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_CW_SLOW_RING2, 0x0201C7E1);

  ///
  /// PWRMBASE + 0x88 = 0x3F8FF701
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_CW_SA, 0x3F8FF701);

  ///
  /// PWRMBASE + 0x8C = 0x0201C7E1
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_CW_SA2, 0x0201C7E1);

  ///
  /// PWRMBASE + 0x98 = 0x0001C000
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_CW_SLOW_RING_CF, 0x0001C000);

  ///
  /// PWRMBASE + 0xA8 = 0x00181300
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_PA_SLOW_RING, 0x00181300);

  ///
  /// PWRMBASE + 0xAC = 0x02006001
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_PA_SLOW_RING2, 0x02006001);

  ///
  /// PWRMBASE + 0xB0 = 0x00181300
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_PA_SA, 0x00181300);

  ///
  /// PWRMBASE + 0xB4 = 0x02006001
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_PA_SA2, 0x02006001);

  ///
  /// PWRMBASE + 0xC0 = 0x00060A00
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_EN_MISC_EVENT, 0x00060A00);

  ///
  /// PWRMBASE + 0xD0 = 0x00200840
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_PM_SYNC_STATE_HYS, 0x00200840);

  ///
  /// PWRMBASE + 0xD4 = 0x7000F4E6
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_PM_SYNC_MODE, 0x7000F4E6);

  ///
  /// if SPI boot, PWRMBASE + 0xE0 = 0x01040001
  /// If eSPI boot or ESPI strap enabled, PWRMBASE + 0xE0 = 0x01040009
  ///
  if (IsEspiEnabled ()) {
    MmioWrite32 (PchPwrmBase + R_PCH_PWRM_CFG3, 0x01040009);
  } else {
    MmioWrite32 (PchPwrmBase + R_PCH_PWRM_CFG3, 0x01040001);
  }

  ///
  /// PWRMBASE + 0xE4 = 0x16BF0003
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_PM_DOWN_PPB_CFG, 0x16BF0003);

  ///
  /// PWRMBASE + 0xF4 = 0x7000F4C0
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_PM_SYNC_MODE_C0, 0x7000F4C0);
  ///
  /// For LP, set R_PCH_PWRM_MODPHY_PM_CFG1[MLS0SWPGP] Bits 31:16 = 0xFFFF
  ///
  if (PchSeries == PchLp) {
    MmioOr32 (PchPwrmBase + R_PCH_PWRM_MODPHY_PM_CFG1, 0xFFFF0000);
  }
  ///
  /// Clear corresponding bit in MLSXSWPGP when ModPHY SUS Well Lane Power Gating is not permitted in Sx
  /// As USB3 lanes do not support SUS Well Power Gating as they support in-band wake, the bits corresponding
  /// to USB3 lanes need to be cleared
  ///
  if (PchSeries == PchLp) {
    MaxUsb3LaneNum = 5;
  } else {
    MaxUsb3LaneNum = 9;
  }
  for (LaneNum = 0; LaneNum <= MaxUsb3LaneNum; LaneNum++) {
    if (PchGetLaneInfo (LaneNum, &PortId, &LaneOwner) == EFI_SUCCESS) {
      if (LaneOwner == V_PCH_PCR_FIA_LANE_OWN_USB3) {
        MmioAnd32 (
          PchPwrmBase + R_PCH_PWRM_MODPHY_PM_CFG1,
          (UINT32) ~(1 << LaneNum)
          );
      }
    }
  }
  ///
  /// MODPHY_PM_CFG2 (0x204h[28:24]) = 01010, External FET Ramp Time (EFRT)
  ///
  Data32And = (UINT32) ~(B_PCH_PWRM_MODPHY_PM_CFG2_EMFC | B_PCH_PWRM_MODPHY_PM_CFG2_EFRT);
  Data32Or  = 0;
  MmioAndThenOr32 (
    PchPwrmBase + R_PCH_PWRM_MODPHY_PM_CFG2,
    Data32And,
    Data32Or
    );

  ///
  /// PM_CFG4 (0x0E8h[30])  = 1,    USB2 PHY SUS Well Power Gating Enable (U2_PHY_PG_EN)
  /// PM_CFG4 (0x0E8h[8:0]) = 018h, CPU I/O VR Ramp Duration
  ///
  MmioAndThenOr32(
    PchPwrmBase + R_PCH_PWRM_CFG4,
    (UINT32)~B_PCH_PWRM_CFG4_CPU_IOVR_RAMP_DUR,
    B_PCH_PWRM_CFG4_U2_PHY_PG_EN |
    (V_PCH_PWRM_CFG4_CPU_IOVR_RAMP_DUR_240US << N_PCH_PWRM_CFG4_CPU_IOVR_RAMP_DUR)
    );
  ///
  /// CPPM_CG_POL1A (0x0324h[30])  = 1,    CPPM Shutdown Qualifier Enable for Clock Source Group 1 (CPPM_G1_QUAL)
  /// CPPM_CG_POL2A (0x0340h[30])  = 1,    CPPM Shutdown Qualifier Enable for Clock Source Group 2 (CPPM_G2_QUAL)
  /// CPPM_CG_POL3A (0x03A8h[30])  = 1,    CPPM Shutdown Qualifier Enable for Clock Source Group 3 (CPPM_G3_QUAL)
  /// CPPM_CG_POL1A (0x0324h[8:0]) = 006h, LTR Threshold for Clock Source Group 1 (LTR_G1_THRESH)
  /// CPPM_CG_POL2A (0x0340h[8:0]) = 008h, LTR Threshold for Clock Source Group 2 (LTR_G2_THRESH)
  /// CPPM_CG_POL3A (0x03A8h[8:0]) = 029h, LTR Threshold for Clock Source Group 3 (LTR_G3_THRESH)
  ///
  MmioAndThenOr32 (
    PchPwrmBase + R_PCH_PWRM_CPPM_CG_POL1A,
    (UINT32) ~B_PCH_PWRM_CPPM_CG_POLXA_LTR_GX_THRESH,
    B_PCH_PWRM_CPPM_CG_POLXA_CPPM_GX_QUAL |
    0x006
    );
  MmioAndThenOr32 (
    PchPwrmBase + R_PCH_PWRM_CPPM_CG_POL2A,
    (UINT32) ~B_PCH_PWRM_CPPM_CG_POLXA_LTR_GX_THRESH,
    B_PCH_PWRM_CPPM_CG_POLXA_CPPM_GX_QUAL |
    0x008
    );
  MmioAndThenOr32 (
    PchPwrmBase + R_PCH_PWRM_CPPM_CG_POL3A,
    (UINT32) ~B_PCH_PWRM_CPPM_CG_POLXA_LTR_GX_THRESH,
    B_PCH_PWRM_CPPM_CG_POLXA_CPPM_GX_QUAL |
    0x029
    );

  ///
  /// PWRMBASE + 0x314 = 0x1E0A4616
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_OBFF_CFG, 0x1E0A4616);

  ///
  /// PWRMBASE + 0x31C [8:0] = 0x003
  /// Program  PWRMBASE + 0x31C [29,27,25,24,23] = all 1s
  /// Program  PWRMBASE + 0x31C [22,15,13] = all 0s
  /// For H  - PWRMBASE + 0x31C [14,22] = all 1s
  /// Program  PWRMBASE + 0x31C [15] to 1b if SLP_S0# is enabled.
  /// For LP - PWRMBASE + 0x31C [13] to 1b if SLP_S0# is enabled and SLP_S0# Voltage Margining is enabled.
  /// For LP - PWRMBASE + 0x31C [22] to 1b if SLP_S0# is enabled and SLP_S0# Voltage Margining is disabled
  ///
  Data32And = (UINT32) ~(BIT22 | BIT15 | BIT13 | 0x000001FF);
  Data32Or  = BIT29 | BIT27 | BIT25 | BIT24 | BIT23 | 0x003;
  if (PchSeries == PchH) {
    Data32Or |= BIT14 | BIT22;
  }

  if (PmConfig->SlpS0Enable) {
    Data32Or |= BIT15;
    if (PchSeries == PchLp) {
      if (PmConfig->SlpS0VmEnable) {
        Data32Or |= BIT13;
      } else {
        Data32Or |= BIT22;
      }
    }
  }

  MmioAndThenOr32 (
    PchPwrmBase + R_PCH_PWRM_31C,
    Data32And,
    Data32Or
    );

  ///
  /// PWRMBASE + 0x320 = 0x0005DB01
  ///
  MmioWrite32 (PchPwrmBase + R_PCH_PWRM_CPPM_MISC_CFG, 0x0005DB01);

  Data32  = BIT31 | BIT30;
  if (PchSeries == PchH) {
    Data32 |= BIT21;
  } else {
    Data32 |= BIT19;
  }
  MmioOr32 (
    PchPwrmBase + R_PCH_PWRM_34C,
    Data32
    );
  ///
  /// PWRM + 0x100 [3] = 1
  ///
  MmioOr32 (PchPwrmBase + R_PCH_PWRM_VR_MISC_CTL, B_PCH_PWRM_VR_MISC_CTL_VIDSOVEN);

  ///
  /// CS_SD_CTL1 (0x3E8[22:20]) = 010, Clock Source 5 Control Configuration (CS5_CTL_CFG)
  /// CS_SD_CTL1 (0x3E8[2:0])   = 001, Clock Source 1 Control Configuration (CS1_CTL_CFG)
  ///
  MmioAndThenOr32 (
    PchPwrmBase + R_PCH_PWRM_CS_SD_CTL1,
    (UINT32) ~(B_PCH_PWRM_CS_SD_CTL1_CS5_CTL_CFG | B_PCH_PWRM_CS_SD_CTL1_CS1_CTL_CFG),
    (2 << N_PCH_PWRM_CS_SD_CTL1_CS5_CTL_CFG) |
    (1 << N_PCH_PWRM_CS_SD_CTL1_CS1_CTL_CFG)
    );
  ///
  /// PWRMBASE + 0x3EC [17, 25] = all 1s
  ///
  if (GetPchGeneration () == SklPch) {
    MmioOr32 (PchPwrmBase + R_PCH_PWRM_CS_SD_CTL2, BIT17 | BIT25);
  }
  ///
  /// PWRMBASE + 0x600 [31,30] = 1,1
  /// PWRMBASE + 0x600 [29] = 1
  /// PWRMBASE + 0x600 [10:6] = 02h
  ///
  MmioAndThenOr32 (
    PchPwrmBase + R_PCH_PWRM_600,
    (UINT32) ~(0x1F << 6),
    BIT31 | BIT30 | BIT29 | (2 << 6)
    );

  ///
  /// PWRMBASE + 0x604 [10:6] = 02h
  ///
  MmioAndThenOr32 (
    PchPwrmBase + R_PCH_PWRM_604,
    (UINT32) ~(0x1F << 6),
    (2 << 6)
    );

  ///
  /// PWRMBASE + 0x3D0 [31] = 1
  /// PWRMBASE + 0x3D0 [11,10] = all 0s
  /// PWRMBASE + 0x3D0 [21:16] = 0Ah
  ///
  MmioAndThenOr32 (
    PchPwrmBase + R_PCH_PWRM_3D0,
    (UINT32) ~((0x3F << 16) | BIT11 | BIT10),
    BIT31 | (0x0A << 16)
    );

  ///
  /// CPPM_MPG_POL1A (0x3E0h[30])  = 1,    CPPM Shutdown Qualifier Enable for ModPHY (CPPM_MODPHY_QUAL)
  /// CPPM_MPG_POL1A (0x3E0h[29])  = 1,    ASLT/PLT Selection for ModPHY (LT_MODPHY_SEL)
  /// CPPM_MPG_POL1A (0x3E0h[8:0]) = 069h, LTR Treshold for ModPHY (LTR_MODPHY_THRESH)
  ///
  MmioAndThenOr32 (
    PchPwrmBase + R_PCH_PWRM_CPPM_MPG_POL1A,
    (UINT32) ~B_PCH_PWRM_CPPM_MPG_POL1A_LTR_MODPHY_THRESH,
    B_PCH_PWRM_CPPM_MPG_POL1A_CPPM_MODPHY_QUAL |
    B_PCH_PWRM_CPPM_MPG_POL1A_LT_MODPHY_SEL |
    0x69
    );

  //
  // Configure MISC settings
  //
  ConfigureMiscPm (SiPolicy);

  //
  // Configure Energy Report
  //
  ConfigureEnergyReport (SiPolicy);

  //
  // Deep Sx Enabling
  //
  ProgramDeepSx (SiPolicy);

  PsfConfigurePowerManagement ();

  ConfigureSpiPm ();


  ConfigureLpcPm (SiPolicy);

  return EFI_SUCCESS;
}

/**
  Get PMC Data BAR Address

  @param[in]   TempMemBaseAddr          Temporary memory base address for PMC device
  @param[in]   PmcBaseAddress           PMC Base Address
  @param[out]  PmcDataBar               PMC Data BAR Address

  @retval FALSE                         No cleanup temporary MMIO resource to PM_DATA_BAR required
  @retval TRUE                          Cleanup of temporary MMIO resource to PM_DATA_BAR required
**/
BOOLEAN
PchPmcGetDataBar (
  IN  UINT32                          TempMemBaseAddr,
  IN  UINTN                           PmcBaseAddress,
  OUT UINTN                           *PmcDataBar
  )
{
  BOOLEAN       ResetPmcBar;

  ResetPmcBar = FALSE;
  if ((MmioRead32 (PmcBaseAddress + R_PCH_PMC_PM_DATA_BAR) & B_PCH_PMC_PM_DATA_BAR) == 0x0 ||
      (MmioRead32 (PmcBaseAddress + R_PCH_PMC_PM_DATA_BAR) & B_PCH_PMC_PM_DATA_BAR) == B_PCH_PMC_PM_DATA_BAR) {
    ResetPmcBar = TRUE;
    //
    // Disable memory space decoding in command register
    //
    MmioAnd16 (PmcBaseAddress + PCI_COMMAND_OFFSET, (UINT16) ~(EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));
    //
    // Program temporary memory base address
    //
    MmioWrite32 (PmcBaseAddress + R_PCH_PMC_PM_DATA_BAR, TempMemBaseAddr);
    //
    // Enable memory space decoding in command register
    //
    MmioOr16 (PmcBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
  }
  *PmcDataBar = MmioRead32 (PmcBaseAddress + R_PCH_PMC_PM_DATA_BAR) & B_PCH_PMC_PM_DATA_BAR;

  return ResetPmcBar;
}

/**
  Reset PMC Data BAR
  @param[in]  PmcBaseAddress            PMC Base Address
**/
VOID
PchPmcResetDataBar (
  IN  UINTN                           PmcBaseAddress
  )
{
  //
  // Disable memory space decoding in command register
  //
  MmioAnd16 (PmcBaseAddress + PCI_COMMAND_OFFSET, (UINT16) ~(EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));
  ///
  /// Clean up Temporary MMIO resource to PM_DATA_BAR
  ///
  MmioWrite32 (PmcBaseAddress + R_PCH_PMC_PM_DATA_BAR, 0);
}


/**
  Worker function that return the PMC XRAM Offset Data

  @retval PCH_PMC_XRAM_OFFSET_DATA        PMC XRAM Offset Data
**/
PCH_PMC_XRAM_OFFSET_DATA *
GetPchPmcXramOffsetDataPpi (
  VOID
  )
{
  EFI_PEI_PPI_DESCRIPTOR      *PchPmcXramOffsetDataPpiDesc;
  PCH_PMC_XRAM_OFFSET_DATA    *PchPmcXramOffsetData;
  EFI_STATUS                  Status;

  PchPmcXramOffsetDataPpiDesc = NULL;
  PchPmcXramOffsetData        = NULL;

  Status = PeiServicesLocatePpi (
             &gPchPmcXramOffsetDataPpiGuid,
             0,
             NULL,
             (VOID **) &PchPmcXramOffsetData
             );
  if (Status != EFI_SUCCESS) {
    //
    // Initialize PMC XRAM Offset Data
    //
    PchPmcXramOffsetData = AllocateZeroPool (sizeof (PCH_PMC_XRAM_OFFSET_DATA));
    ASSERT (PchPmcXramOffsetData != NULL);
    if (PchPmcXramOffsetData != NULL) {
      PchPmcXramOffsetData->PmcXramHsioCount = 0;
      PchPmcXramOffsetData->PmcXramAfeCount = 0;
      PchPmcXramOffsetData->PmcXramOffset = sizeof (PCH_SBI_HSIO_HDR_TBL);
    }
    PchPmcXramOffsetDataPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
    ASSERT (PchPmcXramOffsetDataPpiDesc != NULL);
    if (PchPmcXramOffsetDataPpiDesc != NULL) {
      PchPmcXramOffsetDataPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
      PchPmcXramOffsetDataPpiDesc->Guid = &gPchPmcXramOffsetDataPpiGuid;
      PchPmcXramOffsetDataPpiDesc->Ppi = PchPmcXramOffsetData;
      DEBUG ((DEBUG_INFO, "Installing PMC XRAM Data\n"));
      Status = PeiServicesInstallPpi (PchPmcXramOffsetDataPpiDesc);
      ASSERT_EFI_ERROR (Status);
    }
  }
  return PchPmcXramOffsetData;
}

/**
  Calculate PMC XRAM Header offset based on group data

  @param[in]  Pid                       Port ID
  @param[in]  RowOffset                 Rows of data already present
  @param[in]  EndTableMarkers           Total bytes required for end table marker
  @param[in]  Delay                     Number of delays introduced

  @retval Header Data
**/
UINT16
SurvPhyGrpTblEntry (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT8                             RowOffset,
  IN  UINT8                             EndTableMarkers,
  IN  UINT8                             Delay
  )
{
  UINT8 Dwords;
  if ((Pid == 0x00) && (RowOffset == 0x0F)) {
    return (UINT16) 0x0F00;
  } else {
    DEBUG ((DEBUG_INFO, "Pid = %d\n", Pid));
    DEBUG ((DEBUG_INFO, "RowOffset = %d\n", RowOffset));
    DEBUG ((DEBUG_INFO, "EndTableMarkers = %d\n", EndTableMarkers));
    DEBUG ((DEBUG_INFO, "Delay = %d\n", Delay));
    Dwords = (RowOffset * 3) + EndTableMarkers + Delay;
    DEBUG ((DEBUG_INFO, "Dwords = %d\n", Dwords));
    return (UINT16) (((Dwords & 0x0F) << 12) | ((Pid & 0x0F) << 8) | (Dwords >> 4));
  }
}

/**
  Write Pmc Xram data.

  @param[in]  Pid                       Port ID
  @param[in]  Offset                    Register offset of Port ID.
  @param[in]  InData                    Input Data. Must be the same size as Size parameter.
  @param[in]  TempMemBaseAddr           Temporary memory base address for PMC device
  @param[in]  PmcBaseAddress            PMC Base Address
**/
VOID
PchPmcXramWrite32 (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT16                            Offset,
  IN  UINT32                            InData,
  IN  UINT32                            TempMemBaseAddr,
  IN  UINTN                             PmcBaseAddress
  )
{
  BOOLEAN                     ResetPmcBar;
  PCH_SBI_HSIO_CMD_TBL        PchHsioCmdTblEntry;
  PCH_DELAY_HSIO_CMD_TBL      PchDelayTblEntry;
  UINTN                       PmcDataBar;
  UINTN                       XramOffset;
  PCH_PMC_XRAM_OFFSET_DATA    *PchPmcXramOffsetData;

  if (GetPchSeries () == PchLp) {
    ResetPmcBar = PchPmcGetDataBar (TempMemBaseAddr, PmcBaseAddress, &PmcDataBar);
    SetMem (&PchHsioCmdTblEntry, sizeof (PCH_SBI_HSIO_CMD_TBL), 0x00);
    PchPmcXramOffsetData = GetPchPmcXramOffsetDataPpi ();
    if (PchPmcXramOffsetData == NULL) {
      return;
    }
    if (Pid == PID_USB2) {
      if (PchPmcXramOffsetData->PmcXramAfeCount == 0) {
        XramOffset = PchPmcXramOffsetData->PmcXramOffset + PmcDataBar;
        //Add delay of 700us before USB2 Restore Table Execution
        SetMem (&PchDelayTblEntry, sizeof (PCH_DELAY_HSIO_CMD_TBL), 0x00);
        PchDelayTblEntry.Command = DoDelay;
        PchDelayTblEntry.Size = PMC_DATA_DELAY_CMD_SIZE;
        PchDelayTblEntry.DelayPeriod = Delay100us;
        PchDelayTblEntry.DelayCount = 7;
        PchDelayTblEntry.Padding = 0;
        CopyMem ((EFI_PHYSICAL_ADDRESS *) XramOffset, &PchDelayTblEntry, sizeof (PCH_DELAY_HSIO_CMD_TBL));
        DEBUG ((DEBUG_INFO, "HSIO : XramOffset = %x, Value0-3 = %x\n", XramOffset, MmioRead32 (XramOffset)));
        PchPmcXramOffsetData->PmcXramOffset += sizeof (PCH_DELAY_HSIO_CMD_TBL);
      }
      PchPmcXramOffsetData->PmcXramAfeCount++;
    } else {
      PchPmcXramOffsetData->PmcXramHsioCount++;
    }
    PchHsioCmdTblEntry.Command = SendSBIPosted;
    PchHsioCmdTblEntry.Size = PMC_DATA_SBI_CMD_SIZE;
    PchHsioCmdTblEntry.Pid = Pid;
    PchHsioCmdTblEntry.Bar = 0;
    PchHsioCmdTblEntry.OpCode = PrivateControlWrite;
    PchHsioCmdTblEntry.Fbe = 0x0F;
    PchHsioCmdTblEntry.Fid = 0x00;
    PchHsioCmdTblEntry.Offset = Offset;
    PchHsioCmdTblEntry.Value = InData;
    XramOffset = PchPmcXramOffsetData->PmcXramOffset + PmcDataBar;
    CopyMem ((EFI_PHYSICAL_ADDRESS *) XramOffset, &PchHsioCmdTblEntry, sizeof (PCH_SBI_HSIO_CMD_TBL));
    DEBUG ((DEBUG_INFO, "HSIO : XramOffset = %x, Value0-3 = %x, Value4-7 = %x, Value8-11 = %x\n", XramOffset, MmioRead32 (XramOffset), MmioRead32 (XramOffset + 4), MmioRead32 (XramOffset + 8)));
    PchPmcXramOffsetData->PmcXramOffset += sizeof (PCH_SBI_HSIO_CMD_TBL);
    if (ResetPmcBar == TRUE) {
      PchPmcResetDataBar (PmcBaseAddress);
    }
  }
}

/**
  Write PMC XRAM End Table Marker

  @param[in]  TempMemBaseAddr           Temporary memory base address for PMC device
  @param[in]  PmcBaseAddress            PMC Base Address
**/
VOID
PchPmcXramEndTableMarker (
  IN  UINT32          TempMemBaseAddr,
  IN  UINTN           PmcBaseAddress
  )
{
  BOOLEAN                     ResetPmcBar;
  UINTN                       PmcDataBar;
  UINTN                       XramOffset;
  PCH_PMC_XRAM_OFFSET_DATA    *PchPmcXramOffsetData;
  UINT32                      Data32;

  if (GetPchSeries () == PchLp) {
    ResetPmcBar = PchPmcGetDataBar (TempMemBaseAddr, PmcBaseAddress, &PmcDataBar);
    PchPmcXramOffsetData = GetPchPmcXramOffsetDataPpi ();
    if (PchPmcXramOffsetData == NULL) {
      return;
    }
    XramOffset = PchPmcXramOffsetData->PmcXramOffset + PmcDataBar;
    Data32 = 0x0F;
    CopyMem ((EFI_PHYSICAL_ADDRESS *) XramOffset, &Data32, sizeof (UINT32));
    PchPmcXramOffsetData->PmcXramOffset += 4;
    if (ResetPmcBar == TRUE) {
      PchPmcResetDataBar (PmcBaseAddress);
    }
  }
}

/**
  Program PMC XRAM Data Header

  @param[in]  TempMemBaseAddr           Temporary memory base address for PMC device
  @param[in]  PmcBaseAddress            PMC Base Address
**/
VOID
PchPmcXramDataHdrProg (
  IN  UINT32                            TempMemBaseAddr,
  IN  UINTN                             PmcBaseAddress
  )
{
  BOOLEAN                     ResetPmcBar;
  PCH_PMC_XRAM_OFFSET_DATA    *PchPmcXramOffsetData;
  PCH_SBI_HSIO_HDR_TBL        PchHsioHdrTbl;
  UINTN                       PmcDataBar;
  UINT16                      Data16;
  UINT8                       TotalRows;
  UINT8                       CurrentRowOffset;
  UINT8                       Delay;

  if (GetPchSeries () == PchLp) {
    PchPmcXramOffsetData = GetPchPmcXramOffsetDataPpi ();
    if (PchPmcXramOffsetData == NULL) {
      return;
    }
    ResetPmcBar = PchPmcGetDataBar (TempMemBaseAddr, PmcBaseAddress, &PmcDataBar);
    SetMem (&PchHsioHdrTbl, sizeof (PCH_SBI_HSIO_HDR_TBL), 0x00);
    TotalRows = 16;
    CurrentRowOffset = 0;
    Delay = 0;
    if (PchPmcXramOffsetData->PmcXramAfeCount != 0) {
      Data16 = SurvPhyGrpTblEntry (1, CurrentRowOffset, 16 - TotalRows, Delay);
      CopyMem ((EFI_PHYSICAL_ADDRESS *) (PmcDataBar + (16 - TotalRows) * sizeof (UINT16)), &Data16, sizeof (UINT16));
      CurrentRowOffset += PchPmcXramOffsetData->PmcXramAfeCount;
      TotalRows--;
      Delay++;
      DEBUG ((DEBUG_INFO, "Total AFE settings in PMC : %d\n", PchPmcXramOffsetData->PmcXramAfeCount));
    }
    if (PchPmcXramOffsetData->PmcXramHsioCount != 0) {
      Data16 = SurvPhyGrpTblEntry (3, CurrentRowOffset, 16 - TotalRows, Delay);
      CopyMem ((EFI_PHYSICAL_ADDRESS *) (PmcDataBar + (16 - TotalRows) * sizeof (UINT16)), &Data16, sizeof (UINT16));
      CurrentRowOffset += PchPmcXramOffsetData->PmcXramHsioCount;
      TotalRows--;
      DEBUG ((DEBUG_INFO, "Total HSIO settings in PMC : %d\n", PchPmcXramOffsetData->PmcXramHsioCount));
    }
    Data16 = SurvPhyGrpTblEntry (0x00, 0x0F, 0x00, Delay);
    CopyMem ((EFI_PHYSICAL_ADDRESS *) (PmcDataBar + (16 - TotalRows) * sizeof (UINT16)), &Data16, sizeof (UINT16));
    if (ResetPmcBar == TRUE) {
      PchPmcResetDataBar (PmcBaseAddress);
    }
    ///
    /// Program the PM_DATA_BAR_DIS, PMC PCI offset A4h bit[16] to 1
    ///
    MmioOr8 (PmcBaseAddress + R_PCH_PMC_GEN_PMCON_B + 2, B_PCH_PMC_GEN_PMCON_B_PM_DATA_BAR_DIS >> 16);
  }
}

/**
  Lock down PMC settings

  @param[in] SiPolicy                  The SI Policy PPI instance
**/
VOID
LockPmcSettings (
  IN  SI_POLICY_PPI                    *SiPolicy
  )
{
  UINTN                                 PciPmcRegBase;

  PciPmcRegBase = MmPciBase (
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_PMC,
                    PCI_FUNCTION_NUMBER_PCH_PMC
                    );
  ///
  /// Set PMC PCI Offset 0xAC [24]
  ///
  MmioOr32 (PciPmcRegBase + R_PCH_PMC_ETR3, BIT24);
}
