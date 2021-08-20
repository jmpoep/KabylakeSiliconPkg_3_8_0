/** @file
  PEIM to initialize IGFX.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2020 Intel Corporation.

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
#include <Library/PeiServicesLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MmPciLib.h>
#include <IndustryStandard/Pci22.h>
#include <Private/Library/GraphicsInitLib.h>
#include <Private/Library/SaInitLib.h>
#include <Library/PciLib.h>
#include <Library/TimerLib.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>
#include <SaPolicyCommon.h>
#include <PchAccess.h>
#include <Library/PchSbiAccessLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PeiSaPolicyLib.h>
#include <Ppi/Spi.h>


/**
  Check and Force Vdd On based on the H/W Status

  @param[in] GRAPHICS_PEI_PREMEM_CONFIG   GtPreMemConfig

  @retval EFI_NOT_READY                   H/W Power Cycle sequence in progress, Vdd on not enabled
  @retval EFI_SUCCESS                     Vdd On already enabled or enabled successfully

**/
STATIC EFI_STATUS
CheckAndForceVddOn (
  IN   GRAPHICS_PEI_PREMEM_CONFIG      *GtPreMemConfig
  )
{
  UINTN                   GttMmAdr;
  UINTN                   GmAdr;
  UINTN                   McD2BaseAddress;
  UINT32                  GTBaseAddress;
  UINT8                   Msac;
  EFI_STATUS              Status = EFI_SUCCESS;

  McD2BaseAddress   = MmPciBase (SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0);
  GttMmAdr = GtPreMemConfig->GttMmAdr;
  GmAdr    = GtPreMemConfig->GmAdr;

  GTBaseAddress = (UINT32) (GttMmAdr & 0xFF000000);
  MmioWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, GTBaseAddress);
  MmioWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, GmAdr);
  Msac = MmioRead8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET);
  MmioAndThenOr8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, (UINT8) ~(BIT4 + BIT3 + BIT2 + BIT1 + BIT0), SA_GT_APERTURE_SIZE_256MB);
  GmAdr = GtPreMemConfig->GmAdr;
  MmioWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, GmAdr);

  ///
  /// Enable Bus Master and Memory access on 0:2:0
  ///
  MmioOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));
  /// Skip if VDD Bit is already set
  if ( (MmioRead32 (GttMmAdr + R_SA_GTTMMADR_PP_CONTROL) & BIT3) == 0 ) {
    if ( (MmioRead32(GttMmAdr + R_SA_GTTMMADR_PP_STATUS) & (BIT29|BIT28|BIT27)) == 0 ) {
      ///
      /// Panel Power Enable - VDD bit, as H/W Power cycle sequence completed
      ///
      MmioOr32 (GttMmAdr + R_SA_GTTMMADR_PP_CONTROL, (UINT32) BIT3);
    } else {
      Status = EFI_NOT_READY;
    }
  }

  MmioAnd16 (McD2BaseAddress + R_SA_IGD_CMD, (UINT16) ~(BIT2 | BIT1));
  MmioWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, 0);
  MmioWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR + 0x4, 0);
  MmioWrite8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, Msac);
  MmioWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, 0x0);

  return Status;
}

/**
  Check and Force Vdd On in End Of PEI

  @retval EFI_NOT_READY                   H/W Power Cycle sequence in progress, Vdd on not enabled or Policy not found
  @retval EFI_SUCCESS                     Vdd On already enabled or enabled successfully

**/
EFI_STATUS
EndOfPeiCheckAndForceVddOn (
  VOID
  )
{
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  SI_POLICY_PPI               *SiPolicyPpi;
  GRAPHICS_PEI_PREMEM_CONFIG  *GtPreMemConfig;
  GRAPHICS_PEI_CONFIG         *GtConfig;
  EFI_STATUS                   Status = EFI_SUCCESS;
  EFI_BOOT_MODE                BootMode;

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  if (BootMode != BOOT_ON_S3_RESUME) {
    DEBUG ((DEBUG_INFO, "EndOfPeiCheckAndForceVddOn start\n"));
    ///
    /// Get SA Policy settings through the SaInitConfigBlock PPI
    ///
    Status = PeiServicesLocatePpi (
               &gSiPreMemPolicyPpiGuid,
               0,
               NULL,
               (VOID **) &SiPreMemPolicyPpi
               );
    if (EFI_ERROR (Status) || (SiPreMemPolicyPpi == NULL)) {
      return EFI_NOT_FOUND;
    }
    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
    ASSERT_EFI_ERROR (Status);

    if (GtPreMemConfig->PanelPowerEnable == 1) {
      ///
      /// Get policy settings through the SiSaPolicyPpi
      ///
      Status = PeiServicesLocatePpi (
                 &gSiPolicyPpiGuid,
                 0,
                 NULL,
                 (VOID **) &SiPolicyPpi
                 );
      if ((EFI_ERROR (Status)) || (SiPolicyPpi == NULL)) {
        return EFI_NOT_FOUND;
      }
      Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGraphicsPeiConfigGuid, (VOID *) &GtConfig);
      ASSERT_EFI_ERROR (Status);

      /// Enable Panel Power (VDD bit), only when PEIM Graphics init is disabled
      if (GtConfig->PeiGraphicsPeimInit == 0) {
        Status = CheckAndForceVddOn (GtPreMemConfig);
      }
    }
    DEBUG ((DEBUG_INFO, "EndOfPeiCheckAndForceVddOn end status - 0x%x\n", Status));
  }

  return Status;
}

/**
  Check and Force Vdd On in PostMem Phase

  @param[in] GRAPHICS_PEI_PREMEM_CONFIG      GtPreMemConfig
  @param[in] GRAPHICS_PEI_CONFIG             GtConfig

**/
VOID
PostMemCheckAndForceVddOn (
  IN   GRAPHICS_PEI_PREMEM_CONFIG      *GtPreMemConfig,
  IN   GRAPHICS_PEI_CONFIG             *GtConfig
  )
{
  EFI_STATUS              Status = EFI_SUCCESS;
  EFI_BOOT_MODE                BootMode;


  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  if ((GtPreMemConfig->PanelPowerEnable == 1) && (BootMode != BOOT_ON_S3_RESUME)) {
    DEBUG ((DEBUG_INFO, "PostMemCheckAndForceVddOn start\n"));
    Status = CheckAndForceVddOn(GtPreMemConfig);
    DEBUG ((DEBUG_INFO, "PostMemCheckAndForceVddOn end status - 0x%x\n", Status));
  }
}

/**
  Additional steps for disabling IGFX.
  @param[in] GtPreMemConfig  - GRAPHICS_PEI_PREMEM_CONFIG to access the GtPreMemConfig related information
**/
VOID
AdditionalStepsForDisablingIgfx (
  IN       GRAPHICS_PEI_PREMEM_CONFIG   *GtPreMemConfig
  );

/**
  InitializeDisplayAudio: Initialize display engine for iDisplay Audio programming

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_ABORTED             S3 boot - display already initialized
  @retval EFI_UNSUPPORTED         iGfx disabled, iDisplay Audio not present
  @retval EFI_NOT_FOUND           SaPolicy or temporary GTT base address not found
**/
EFI_STATUS
InitializeDisplayAudio (
  VOID
  )
{
  UINTN                       McD2BaseAddress;
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  GRAPHICS_PEI_PREMEM_CONFIG  *GtPreMemConfig;
  UINTN                        GttMmAdr;
  UINTN                        GmAdr;
  BOOLEAN                      IsGttBarInitiallyAssigned;
  BOOLEAN                      IsGttBarInitiallyEnabled;
  EFI_BOOT_MODE                BootMode;
  EFI_STATUS                   Status;
  UINT8                        Msac;
  UINT8                        DpModeLinkRate;
  UINT32                       CdClkRegValue;

  DEBUG ((DEBUG_INFO, "InitializeDisplayAudio() Start\n"));

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  McD2BaseAddress = MmPciBase (SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0);
  Msac = MmioRead8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET);
  IsGttBarInitiallyAssigned = FALSE;
  IsGttBarInitiallyEnabled  = FALSE;

  if (MmioRead16 (McD2BaseAddress + R_SA_IGD_VID) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "iGFX not enabled - iDisplayAudio not supported - Exit!\n"));
    return EFI_UNSUPPORTED;
  }

  // Check if GttMmAdr has been already assigned, initialize if not
  GttMmAdr = (MmioRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;
  if (GttMmAdr == 0) {
    ///
    /// Get SA Policy settings through the SaInitConfigBlock PPI
    ///
    Status = PeiServicesLocatePpi (
               &gSiPreMemPolicyPpiGuid,
               0,
               NULL,
               (VOID **) &SiPreMemPolicyPpi
               );
    if (EFI_ERROR (Status) || (SiPreMemPolicyPpi == NULL)) {
      DEBUG ((DEBUG_WARN, "SaPolicy PPI not found - Exit!\n"));
      return EFI_NOT_FOUND;
    }

    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
    ASSERT_EFI_ERROR (Status);

    GttMmAdr = GtPreMemConfig->GttMmAdr;
    GmAdr    = GtPreMemConfig->GmAdr;

    if (GttMmAdr == 0) {
      DEBUG ((DEBUG_WARN, "Temporary GttMmAdr Bar is not initialized - Exit!\n"));
      return EFI_NOT_FOUND;
    }

    ///
    /// Program and read back GTT Memory Mapped BAR
    ///
    MmioWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, (UINT32) (GttMmAdr & 0xFF000000));
    GttMmAdr = (MmioRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;

    MmioAndThenOr8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, (UINT8) ~(BIT4 + BIT3 + BIT2 + BIT1 + BIT0), SA_GT_APERTURE_SIZE_256MB);
    MmioWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, GmAdr);
  } else {
    DEBUG ((DEBUG_INFO, "GttMmAdr Bar already initialized\n"));
    IsGttBarInitiallyAssigned = TRUE;
    IsGttBarInitiallyEnabled  = (MmioRead16 (McD2BaseAddress + R_SA_IGD_CMD) & (BIT2 | BIT1)) ? TRUE : FALSE;
  }

  if (!IsGttBarInitiallyEnabled) {
    ///
    /// Enable Bus Master and Memory access on 0:2:0
    ///
    MmioOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));
  }

  ///
  /// Enable PCH Reset Handshake
  ///
  MmioOr32 ((GttMmAdr + 0x46408), BIT4);

  ///
  /// Enable Power Well 1 (PG1), Power Well 2 (PG2) and Misc IO Power
  ///
  PollGtReady (GttMmAdr, 0x42000, BIT27, BIT27);

  MmioOr32 (GttMmAdr + 0x45400, (BIT31 | BIT29 | BIT1));
  PollGtReady (GttMmAdr, 0x45400, (BIT30 | BIT28 | BIT0), (BIT30 | BIT28 | BIT0));
  PollGtReady (GttMmAdr, 0x42000, (BIT26 | BIT25), (BIT26 | BIT25));

  ///
  /// If DPLL_CTRL1 (0x6C058) BIT[3:1] == 100b or 101b (2.16 GHz or 4.32 GHz), toggle the frequency select to get the PLL to recover.
  ///
  CdClkRegValue = MmioRead32(GttMmAdr + 0x46000);
  DpModeLinkRate = (((MmioRead32(GttMmAdr + 0x6C058)) >> 1) & 0x07);
  if (DpModeLinkRate == 0x04 || DpModeLinkRate == 0x05) {
    MmioOr32(GttMmAdr + 0x46000, BIT19);
    MmioOr32(GttMmAdr + 0x46010, BIT31);
    PollGtReady(GttMmAdr, 0x46010, BIT30, BIT30);

    MmioAnd32 (GttMmAdr + 0x46000, (UINT32)(~(BIT27 | BIT26)));
    MmioOr32 (GttMmAdr + 0x46000, (UINT32)((CdClkRegValue & (BIT27 | BIT26))));
    MmioAnd32 (GttMmAdr + 0x46000, (UINT32)(~(BIT19)));
  } else {
    ///
    /// Enable CDCLK PLL
    ///
    MmioOr32 (GttMmAdr + 0x46010, BIT31);
    PollGtReady (GttMmAdr, 0x46010, BIT30, BIT30);
  }

  if (!IsGttBarInitiallyEnabled) {
    ///
    /// Disable Bus Master and Memory access on 0:2:0 and clear GTTMMADR
    ///
    MmioAnd16 (McD2BaseAddress + R_SA_IGD_CMD, (UINT16) ~(BIT2 | BIT1));
    if (!IsGttBarInitiallyAssigned) {
      MmioAnd32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, 0x0);
      MmioAnd32 (McD2BaseAddress + R_SA_IGD_GMADR, 0x0);
      MmioWrite8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, Msac);
    }
  }

  DEBUG ((DEBUG_INFO, "InitializeDisplayAudio() End\n"));
  return EFI_SUCCESS;
}

/**
  ConfigureIDispAudioFrequency: Configures iDisplay Audio BCLK frequency and T-Mode

  @param[in] RequestedBclkFrequency     IDisplay Link clock frequency to be set
  @param[in] RequestedTmode             IDisplay Link T-Mode to be set

  @retval EFI_NOT_FOUND                 SA Policy PPI or GT config block not found, cannot initialize GttMmAdr
  @retval EFI_UNSUPPORTED               iDisp link unsupported frequency
  @retval EFI_SUCCESS                   The function completed successfully
**/
EFI_STATUS
ConfigureIDispAudioFrequency (
  IN       PCH_HDAUDIO_LINK_FREQUENCY   RequestedBclkFrequency,
  IN       PCH_HDAUDIO_IDISP_TMODE      RequestedTmode
  )
{
  UINTN                      McD2BaseAddress;
  SI_POLICY_PPI             *SiPreMemPolicyPpi;
  GRAPHICS_PEI_PREMEM_CONFIG *GtPreMemConfig;
  UINTN                      GttMmAdr;
  UINTN                      GmAdr;
  UINT32                     Data32And;
  UINT32                     Data32Or;
  BOOLEAN                    IsGttBarInitialyAssigned;
  BOOLEAN                    IsGttBarInitialyEnabled;
  EFI_STATUS                 Status;
  UINT8                      Msac;

  DEBUG ((DEBUG_INFO, "ConfigureIDispAudioFrequency() Start\n"));
  McD2BaseAddress = MmPciBase (SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0);
  Msac = MmioRead8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET);
  IsGttBarInitialyAssigned = FALSE;
  IsGttBarInitialyEnabled  = FALSE;

  if (MmioRead16 (McD2BaseAddress + R_SA_IGD_VID) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "iGFX not enabled - frequency switching for iDisplay link not supported - Exit!\n"));
    return EFI_UNSUPPORTED;
  }

  // Check if GttMmAdr has been already assigned, initialize if not
  GttMmAdr = (MmioRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;
  if (GttMmAdr == 0) {
    ///
    /// Get SA Policy settings through the SaInitConfigBlock PPI
    ///
    Status = PeiServicesLocatePpi (
               &gSiPreMemPolicyPpiGuid,
               0,
               NULL,
               (VOID **) &SiPreMemPolicyPpi
               );
    if (EFI_ERROR (Status) || (SiPreMemPolicyPpi == NULL)) {
      DEBUG ((DEBUG_WARN, "SaPolicy PPI not found - Exit!\n"));
      return EFI_NOT_FOUND;
    }

    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
    ASSERT_EFI_ERROR (Status);

    GttMmAdr = GtPreMemConfig->GttMmAdr;
    GmAdr    = GtPreMemConfig->GmAdr;

    if (GttMmAdr == 0) {
      DEBUG ((DEBUG_WARN, "Temporary GttMmAdr Bar is not initialized - Exit!\n"));
      return EFI_NOT_FOUND;
    }

    ///
    /// Program and read back GTT Memory Mapped BAR
    ///
    MmioWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, (UINT32) (GttMmAdr & 0xFF000000));
    GttMmAdr = (MmioRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;
    MmioWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, GmAdr);
    MmioAndThenOr8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, (UINT8) ~(BIT4 + BIT3 + BIT2 + BIT1 + BIT0), SA_GT_APERTURE_SIZE_256MB);
  } else {
    DEBUG ((DEBUG_INFO, "GttMmAdr Bar already initialized\n"));
    IsGttBarInitialyAssigned = TRUE;
    IsGttBarInitialyEnabled  = (MmioRead16 (McD2BaseAddress + R_SA_IGD_CMD) & (BIT2 | BIT1)) ? TRUE : FALSE;
  }

  switch (RequestedBclkFrequency) {
    case PchHdaLinkFreq96MHz:
      //
      // SA IGD: GttMmAdr + 0x65900[15] =  0b, [4:3] = 10b (2T Mode, 96MHz)
      //
      Data32And = (UINT32) ~(B_SA_IGD_AUD_FREQ_CNTRL_TMODE | B_SA_IGD_AUD_FREQ_CNTRL_48MHZ);
      Data32Or  = (UINT32) B_SA_IGD_AUD_FREQ_CNTRL_96MHZ;
      break;
    case PchHdaLinkFreq48MHz:
      //
      // SA IGD: GttMmAdr + 0x65900[4:3] = 01b (48MHz)
      //
      Data32And = (UINT32) ~(B_SA_IGD_AUD_FREQ_CNTRL_96MHZ);
      Data32Or  = (UINT32) B_SA_IGD_AUD_FREQ_CNTRL_48MHZ;

      if (RequestedTmode == PchHdaIDispMode2T) {
        //
        // SA IGD: 2T Mode [15] = 0b
        //
        Data32And &= (UINT32) ~(B_SA_IGD_AUD_FREQ_CNTRL_TMODE);
      } else {
        //
        // SA IGD: 1T Mode [15] = 1b
        //
        Data32Or |= (UINT32) B_SA_IGD_AUD_FREQ_CNTRL_TMODE;
      }
      break;
    default:
      DEBUG ((DEBUG_WARN, "SA iGFX: Unsupported iDisplay Audio link frequency - Exit!\n"));
      return EFI_UNSUPPORTED;
  }

  if (!IsGttBarInitialyEnabled) {
    ///
    /// Enable Bus Master and Memory access on 0:2:0
    ///
    MmioOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));
  }

  ///
  /// Program iDisplay Audio link frequency
  ///
  MmioAndThenOr32 ((UINTN) (GttMmAdr + R_SA_IGD_AUD_FREQ_CNTRL_OFFSET), Data32And, Data32Or);

  if (!IsGttBarInitialyEnabled) {
    ///
    /// Disable Bus Master and Memory access on 0:2:0 and clear GTTMMADR
    ///
    MmioAnd16 (McD2BaseAddress + R_SA_IGD_CMD, (UINT16) ~(BIT2 | BIT1));
    if (!IsGttBarInitialyAssigned) {
      MmioAnd32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, 0x0);
      MmioAnd32 (McD2BaseAddress + R_SA_IGD_GMADR, 0x0);
      MmioWrite8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, Msac);
    }
  }

  DEBUG ((DEBUG_INFO, "ConfigureIDispAudioFrequency() End\n"));
  return EFI_SUCCESS;
}

/**
  GraphicsInit: Initialize the IGD if no other external graphics is present

  @param[in] GtPreMemConfig       - GtPreMemConfig to access the GtPreMemConfig related information
  @param[in] PrimaryDisplay       - Primary Display - default is IGD
  @param[in, out] PegMmioLength   - Total IGFX MMIO length

**/
VOID
GraphicsInit (
  IN       GRAPHICS_PEI_PREMEM_CONFIG   *GtPreMemConfig,
  IN       DISPLAY_DEVICE               *PrimaryDisplay,
  IN       UINT32                       *IGfxMmioLength
  )
{
  UINT8                   GMSData;
  BOOLEAN                 IGfxSupported;
  UINT32                  GTBaseAddress;
  EFI_STATUS              Status;
  UINTN                   GttMmAdr;
  UINTN                   GmAdr;
  UINTN                   McD0BaseAddress;
  UINTN                   McD2BaseAddress;
  UINT32                  MchBarBase;
  EFI_BOOT_MODE           BootMode;
  BOOLEAN                 IsMmioLengthInfoRequired;
  UINT32                  Data32;
  UINT32                  Data32H;
  UINT32                  Data32Mask;
  PCH_SPI_PPI             *SpiPpi;
  UINT8                   SoftStrapValue;

  DEBUG ((DEBUG_INFO, "iGFX initialization start\n"));

  IsMmioLengthInfoRequired = FALSE;
  *IGfxMmioLength   = 0;
  GttMmAdr          = 0;
  McD0BaseAddress   = MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN);
  McD2BaseAddress   = MmPciBase (SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0);
  MchBarBase        = MmioRead32 (McD0BaseAddress + 0x48) &~BIT0;

  ///
  /// Get the boot mode
  ///
  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Check if IGfx is supported
  ///
  IGfxSupported = (BOOLEAN) (MmioRead16 (McD2BaseAddress + R_SA_IGD_VID) != 0xFFFF);
  if (!IGfxSupported) {
    DEBUG ((DEBUG_INFO, "iGFX is unsupported or disabled!\n"));
    AdditionalStepsForDisablingIgfx (GtPreMemConfig);
    return;
  }

  ///
  /// Temporarily program GttMmAdr
  ///
  GttMmAdr = GtPreMemConfig->GttMmAdr;
  GmAdr    = GtPreMemConfig->GmAdr;

  if (GttMmAdr == 0) {
    DEBUG ((DEBUG_INFO, "Temporary GttMmAdr Bar is not initialized. Returning from GraphicsInit().\n"));
    return;
  }

  ///
  /// Program GttMmAdr
  /// set [23:0] = 0
  ///
  GTBaseAddress = (UINT32) (GttMmAdr & 0xFF000000);
  MmioWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, GTBaseAddress);
  MmioWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, GmAdr);
  DEBUG ((DEBUG_INFO, "GTBaseAddress 0X%x:\n", GTBaseAddress));
  ///
  /// Read back the programmed GttMmAdr
  ///
  GttMmAdr = (MmioRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;

  ///
  /// Enable Bus Master and Memory access on 0:2:0
  ///
  MmioOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));

  ///
  /// If primary display device is IGD or no other display detected then enable IGD
  ///
  if (IGfxSupported &&
      (
        (
          ((*PrimaryDisplay == IGD) || (GtPreMemConfig->PrimaryDisplay == IGD)) &&
          (GtPreMemConfig->InternalGraphics != DISABLED)
          ) || (GtPreMemConfig->InternalGraphics == ENABLED)
        )
      ) {

    DEBUG ((DEBUG_INFO, "IGD enabled.\n"));

    ///
    /// Program GFX Memory
    ///
    GMSData = (UINT8) (GtPreMemConfig->IgdDvmt50PreAlloc);
    ///
    /// For SKL
    /// Description of GMS (8:15)
    ///
    MmioAnd16 (McD0BaseAddress + R_SA_GGC, (UINT16) ~(B_SKL_SA_GGC_GMS_MASK));
    MmioOr16 (McD0BaseAddress + R_SA_GGC, (GMSData & 0xFF) << N_SKL_SA_GGC_GMS_OFFSET);
    ///
    /// For SKL
    /// Program Graphics GTT Memory D0:F0:R50h[7:6]
    ///   01b => 2MB of GTT
    ///   10b => 4MB of GTT
    ///   11b => 8MB of GTT
    ///
    if (GtPreMemConfig->GttSize != V_SKL_SA_GGC_GGMS_DIS) {
      ASSERT (GtPreMemConfig->GttSize <= 3);
      MmioAndThenOr16 (McD0BaseAddress + R_SA_GGC, (UINT16) ~(B_SKL_SA_GGC_GGMS_MASK), (GtPreMemConfig->GttSize << N_SKL_SA_GGC_GGMS_OFFSET) & B_SKL_SA_GGC_GGMS_MASK);
    }
    ///
    /// For SKL/KBL
    /// Set register D2.F0.R 062h [4:0] = `00001b' to set a 256MByte aperture.
    /// This must be done before Device 2 registers are enumerated.
    ///
    MmioAndThenOr8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, (UINT8) ~(BIT4 + BIT3 + BIT2 + BIT1 + BIT0), SA_GT_APERTURE_SIZE_256MB);

    ///
    /// Enable IGD VGA Decode.  This is needed so the Class Code will
    /// be correct for the IGD Device when determining which device
    /// should be primary.  If disabled, IGD will show up as a non VGA device.
    ///
    if ((GtPreMemConfig->PrimaryDisplay != IGD) && (*PrimaryDisplay != IGD)) {
      ///
      /// If IGD is forced to be enabled, but is a secondary display, disable IGD VGA Decode
      ///
      MmioOr16 (McD0BaseAddress + R_SA_GGC, B_SA_GGC_IVD_MASK);
      DEBUG ((DEBUG_INFO, "IGD VGA Decode is disabled because it's not a primary display.\n"));
    } else {
      MmioAnd16 (McD0BaseAddress + R_SA_GGC, (UINT16) ~(B_SA_GGC_IVD_MASK));
    }
    if ((GtPreMemConfig->PanelPowerEnable == 1) && (BootMode != BOOT_ON_S3_RESUME)) {
      ///
      /// Enable Panel Power(VDD bit) if there is no H/W Power sequence restriction.
      /// Will check and enable it in Post Mem (SaInit()) and at End Of PEI, if H/W Power sequence is not done here.
      ///
      if ( (MmioRead32(GttMmAdr + R_SA_GTTMMADR_PP_STATUS) & (BIT29|BIT28|BIT27)) == 0 ) {
        ///
        /// Panel Power Enable - VDD bit
        ///
        MmioOr32 (GttMmAdr + R_SA_GTTMMADR_PP_CONTROL, (UINT32) BIT3);
      }
    }

    ///
    /// Configure iTouch Doorbell Source Registers
    /// Configure Doorbell Register 0x124828 BDF bits[63:48] with Bus Device Function of DoorBell Source HECI Device 0/22/4 and lock BDF bit[40]
    /// Configure GSA_Touch Register 0x1300B4 BDF bits[31:16] with Bus Device Function of DoorBell Source HECI Device 0/22/4 and lock BDF bit[0]
    ///
    DEBUG ((DEBUG_INFO, "Configuring iTouch Source Registers Doorbell and GSA_Touch \n"));

    Data32H = MmioRead32 (GttMmAdr + R_SA_GTTMMADR_GTDOORBELL_OFFSET + 4); // Higher 32 bits of 0x124828
    Data32H = ((Data32H & 0x0000FFFF) | 0x00B40100); // Bus 0, Device 22, Func 4 and lock bit

    Data32 = MmioRead32 (GttMmAdr + R_SA_GTTMMADR_GSA_TOUCH_OFFSET);
    Data32 = ((Data32 & 0x0000FFFF) | 0x00B40001); // Bus 0, Device 22, Func 4 and lock bit
    MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_GTDOORBELL_OFFSET + 4, Data32H);
    MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_GSA_TOUCH_OFFSET, Data32);

    ///
    /// Get Mmio length of iGFX later for dynamic TOLUD support
    ///
    IsMmioLengthInfoRequired = TRUE;

    ///
    /// Read PCH Strap for VccIo value bits[2:1] for ULX and program MMIO Offset 0x4F074[1:0]
    ///
    if (GetCpuSku () == EnumCpuUlx) {
      DEBUG ((DEBUG_INFO, "Read PCH Strap for VccIo value\n"));
      Status = PeiServicesLocatePpi (
                 &gPchSpiPpiGuid,
                 0,
                 NULL,
                 (VOID **) &SpiPpi
                 );
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "GraphicsInitPreMem: SPI PPI is not available\n"));
        ASSERT_EFI_ERROR (Status);
      } else {
        Status = SpiPpi->ReadPchSoftStrap (SpiPpi, R_PCH_SPI_STRP_MMP0, sizeof (SoftStrapValue), &SoftStrapValue);
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_ERROR, "GraphicsInitPreMem: Reading strap error\n"));
          ASSERT_EFI_ERROR (Status);
        } else {
          DEBUG ((DEBUG_INFO, "SoftStrapValue Read : 0x%x\n", SoftStrapValue));
          Data32 = (SoftStrapValue & (BIT2 + BIT1)) >> 1;
          Data32Mask = (UINT32) ~(BIT1 + BIT0);
          MmioAndThenOr32 ((UINTN) (GttMmAdr + 0x4F074), Data32Mask, Data32);
          DEBUG ((DEBUG_INFO, "GttMmAdr + 0x4F074 After the write : %x\n", MmioRead32 (GttMmAdr + 0x4F074)));
        }
      }
    }
  } else {
    AdditionalStepsForDisablingIgfx (GtPreMemConfig);
  }

  ///
  /// Disable Bus Master and Memory access on 0:2:0 and clear GTTMMADR
  ///
  MmioAnd16 (McD2BaseAddress + R_SA_IGD_CMD, (UINT16) ~(BIT2 | BIT1));
  MmioAnd32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, 0x0);

  ///
  /// Program Aperture Size MSAC register based on policy and clear GMADR
  ///
  MmioAndThenOr8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, (UINT8)~(BIT4 + BIT3 + BIT2 + BIT1 + BIT0), (UINT8)GtPreMemConfig->ApertureSize);
  MmioAnd32 (McD2BaseAddress + R_SA_IGD_GMADR, 0x0);

  ///
  ///. Get Mmio length of iGFX for dynamic TOLUD support
  ///
  if (IsMmioLengthInfoRequired) {
    FindPciDeviceMmioLength (0, 2, 0, IGfxMmioLength);
  }
  DEBUG ((DEBUG_INFO, "iGFX initialization end\n"));
}

/**

  "Poll Status" for GT Readiness

  @param[in] Base            - Base address of MMIO
  @param[in] Offset          - MMIO Offset
  @param[in] Mask            - Mask
  @param[in] Result          - Value to wait for

**/
VOID
PollGtReady (
  IN       UINT64                       Base,
  IN       UINT32                       Offset,
  IN       UINT32                       Mask,
  IN       UINT32                       Result
  )
{
  UINT32  GtStatus;
  UINT32  StallCount;

  StallCount = 0;

  ///
  /// Register read
  ///
  GtStatus = MmioRead32 ((UINTN) Base + Offset);

  while (((GtStatus & Mask) != Result) && (StallCount < GT_WAIT_TIMEOUT)) {

    GtStatus = MmioRead32 ((UINTN) Base + Offset);
    ///
    /// 10uSec wait
    ///
    MicroSecondDelay (10);
    StallCount = StallCount + 1;
  }
  ASSERT ((StallCount != GT_WAIT_TIMEOUT));
}
