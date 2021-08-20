/** @file
  Configures PCH Sata Controller for PCH-H

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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
#include "PchInitPei.h"

#ifndef MINTREE_FLAG
/**
  Perform PCH SKU detection to check if the RST PCIe Storage Remapping feature is supported
  Prior to any PCIe device enumeration, initial the RST PCIe Storage "Cycle Router Enable (CRE)" bit to 1
  If the CRE bit value after the write is 1, it indicates the bit is RW,and is enabled by fuse
  else, it indicates the bit is RO only and is disabled by fuse
  The value after the write is stored in RST PCIe Storage Cycle Router Global Control regiser, and then CRE bit is cleared

  @retval None
**/
VOID
PchRstPcieStorageCreEarlyInit (
  VOID
  )
{
  UINTN       i;
  UINT8       Data8;
  UINTN       PciSataRegBase;

  DEBUG ((DEBUG_INFO, "PchRstPcieStorageCreEarlyInit() - Start\n"));

  PciSataRegBase  = MmPciBase (
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PCI_DEVICE_NUMBER_PCH_SATA,
                      PCI_FUNCTION_NUMBER_PCH_SATA
                      );

  ///
  /// Read Vendor ID to check if Sata exists
  /// Return if Sata is not exist
  ///
  if (MmioRead16 (PciSataRegBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return;
  }

  ///
  /// Prior to any PCIe device enum, BIOS needs to detect the PCH SKU to
  /// make sure the RST PCIe Storage Remapping feature is supported
  ///
  for (i = 0; i < PCH_MAX_RST_PCIE_STORAGE_CR; i++) {
    ///
    /// Set the related RST PCIe Storage Cycle Router
    ///
    MmioWrite8 (PciSataRegBase + R_PCH_RST_PCIE_STORAGE_CRGC, (UINT8) i);

    ///
    /// Set the "Port Configuration Check Disable" bit, Sata PCI offset 304h [31]
    ///
    MmioOr32 (PciSataRegBase + R_PCH_RST_PCIE_STORAGE_GSR, B_PCH_RST_PCIE_STORAGE_GSR_PCCD);

    ///
    /// Set RST PCIe Storage's Cycle Router Enabled Bit for CR#i
    ///
    MmioOr8 (PciSataRegBase + R_PCH_RST_PCIE_STORAGE_GCR, (UINT8) B_PCH_RST_PCIE_STORAGE_GCR_CRE);

    ///
    /// Write the value into SATA PCI offset FC0h[16+i], where i = 0 for RST PCIe Storage Cycle Router 1 and so on
    ///
    Data8 = MmioRead8 (PciSataRegBase + R_PCH_RST_PCIE_STORAGE_GCR) & B_PCH_RST_PCIE_STORAGE_GCR_CRE;
    MmioOr32 (PciSataRegBase + R_PCH_RST_PCIE_STORAGE_CRGC, (UINT32) (Data8 << (16+i)));

    ///
    /// Clear RST PCIe Storage's Cycle Router Enabled Bit for CR#i
    ///
    MmioAnd8 (PciSataRegBase + R_PCH_RST_PCIE_STORAGE_GCR, (UINT8) ~(B_PCH_RST_PCIE_STORAGE_GCR_CRE));

    ///
    /// Clear the "Port Configuration Check Disable" bit, Sata PCI offset 304h [31]
    ///
    MmioAnd32 (PciSataRegBase + R_PCH_RST_PCIE_STORAGE_GSR, (UINT32) ~B_PCH_RST_PCIE_STORAGE_GSR_PCCD);

  }


  DEBUG ((DEBUG_INFO, "PchRstPcieStorageCreEarlyInit() - End\n"));
}
#endif //MINTREE_FLAG

/**
  Check if any lanes are assigned to SATA

  @retval TRUE                    Sata lanes exist
  @retval FALSE                   Sata lanes does not exist
**/
BOOLEAN
SataLaneExist (
  VOID
  )
{
  UINT8                 Index;
  UINT8                 PortId;
  UINT8                 LaneOwner;
  UINT8                 MaxSataPorts;
  UINT8                 LaneNum;
  EFI_STATUS            Status;

  MaxSataPorts = GetPchMaxSataPortNum ();
  for (Index = 0; Index < MaxSataPorts; Index++) {
    Status = PchGetSataLaneNum (Index, &LaneNum);
    if (EFI_ERROR (Status)) {
      continue;
    }
    PchGetLaneInfo (LaneNum, &PortId, &LaneOwner);
    if (LaneOwner == V_PCH_PCR_FIA_LANE_OWN_SATA) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
  //
  // Program the HSIO Settings Specific to the SPT Implementation - Elastic Buffer Configuration
  //
  @retval None
**/
VOID
ProgramSataTestMode (
  VOID
  )
{
  UINT32                Data32And;
  UINT32                Data32Or;
  UINT16                Offset;
  HSIO_LANE             HsioLane;
  UINT32                Data32;
  UINT8                 HsioRxEqBoostMagAd;
  UINT8                 LaneOwner;
  UINT8                 PortId;
  UINT32                Index;
  UINT8                 LaneNum;

  //
  // If Loopback mode, the EB inside the PHY logic is in 'half-empty' mode.
  // Each SATA port/lane in the HSIO space must be written with these values.if Sata Test Mode is enabled
  //    i.)  cri_rxeb_lowater[4:0]   = 5'h0A
  //    ii.) cri_rxeb_ptr_init[4:0]  = 5'h10
  //

  Data32And = (UINT32) ~(B_PCH_HSIO_PCS_DWORD8_CRI_RXEB_PTR_INIT_4_0 | B_PCH_HSIO_PCS_DWORD8_CRI_RXEB_LOWATER_4_0);
  Data32Or  = (UINT32) (0x100A0000);
  for (Index = 0; Index < GetPchMaxSataPortNum (); Index++) {
    if (PchGetSataLaneNum (Index, &LaneNum) == EFI_SUCCESS) {
      if (PchGetLaneInfo (LaneNum, &PortId, &LaneOwner) == EFI_SUCCESS) {
        HsioGetLane (LaneNum, &HsioLane);
        PchPcrAndThenOr32 (PortId, HsioLane.Base + R_PCH_HSIO_PCS_DWORD8, Data32And, Data32Or);
        Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_RX_DWORD20;
        PchPcrRead32 ((PCH_SBI_PID) PortId, (UINT16) Offset, &Data32);
        HsioRxEqBoostMagAd = Data32 >> N_PCH_HSIO_RX_DWORD20_ICFGCTLEDATATAP_FULLRATE_5_0;
        PchPcrAndThenOr32 (
          (PCH_SBI_PID) PortId,
          (UINT16) Offset,
          (UINT32) ~B_PCH_HSIO_RX_DWORD20_ICFGCTLEDATATAP_FULLRATE_5_0,
          (UINT32) ((HsioRxEqBoostMagAd+3) << N_PCH_HSIO_RX_DWORD20_ICFGCTLEDATATAP_FULLRATE_5_0));
      }
    }
  }
}

/**
  Configures SATA controller device ID by programming SATAGC register

  @param[in, out] SataGcReg   A value of SATAGC register to be programmed
  @param[in]      SataConfig  A pointer to PCH_SATA_CONFIG structure

**/
VOID
ConfigureSataControllerDeviceId (
  IN OUT    UINT8            *SataGcReg,
  IN CONST  PCH_SATA_CONFIG  *SataConfig
  )
{
  RST_MODE  RstMode;

  RstMode = GetSupportedRstMode ();

  //
  // Device ID programming must be done before SATA mode programming
  // therefore SATA mode check is based on policy.
  //

  if ((SataConfig->SataMode == PchSataModeRaid)  && (RstMode != RstUnsupported)) {
    if (SataConfig->Rst.RaidDeviceId == 1) {
      (*SataGcReg) |= B_PCH_SATA_SATAGC_AIE;
      (*SataGcReg) &= ~B_PCH_SATA_SATAGC_AIES;
    } else if (SataConfig->Rst.RaidDeviceId == 2) {
      (*SataGcReg) &= ~B_PCH_SATA_SATAGC_AIE;
      (*SataGcReg) |= B_PCH_SATA_SATAGC_AIES;
    }
  }

}

/**
  Program AHCI PI register for Enabled ports
  Handle hotplug, and interlock switch setting,
  and config related GPIOs.

  @param[in] SataConfig           The PCH Policy for SATA configuration
  @param[in] AhciBarAddress       The Base Address for AHCI BAR

  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
ConfigurePchSataAhci (
  IN  CONST PCH_SATA_CONFIG           *SataConfig,
  IN  UINT32                          AhciBarAddress
  )
{
  UINT32                AhciBar;
  UINT32                Data32And;
  UINT32                Data32Or;
  UINT32                PxCMDRegister;
  UINT16                SataPortsEnabled;
  UINT8                 Index;
  UINTN                 PciSataRegBase;
  UINT16                WordReg;
  UINT8                 PortSataControl;
  UINT32                CapRegister;
  PCH_SERIES            PchSeries;
  UINT8                 PortxEnabled;
  UINTN                 PortxEnabledOffset;
  UINT16                PortxEnabledMask;
  UINT32                MaxSataPorts;

  DEBUG ((DEBUG_INFO, "ConfigurePchSataAhci() Start\n"));
  MaxSataPorts = GetPchMaxSataPortNum ();
  PciSataRegBase  = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_SATA, PCI_FUNCTION_NUMBER_PCH_SATA);

  ///
  /// Set the AHCI BAR
  ///
  AhciBar = AhciBarAddress;
  MmioWrite32 (PciSataRegBase + R_PCH_SATA_AHCI_BAR, AhciBar);

  ///
  /// Enable command register memory space decoding
  ///
  MmioOr16 (PciSataRegBase + PCI_COMMAND_OFFSET, (UINT16) EFI_PCI_COMMAND_MEMORY_SPACE);

  ///
  /// Get Port Settings
  ///
  PchSeries = GetPchSeries ();
  if (PchSeries == PchH) {
    SataPortsEnabled    = MmioRead16 (PciSataRegBase + R_PCH_H_SATA_PCS);
    SataPortsEnabled    &= (UINT16) (B_PCH_H_SATA_PCS_PXE_MASK);
    PortxEnabled        = B_PCH_H_SATA_PCS_P0E;
    PortxEnabledOffset  = R_PCH_H_SATA_PCS;
    PortxEnabledMask    = B_PCH_H_SATA_PCS_PXE_MASK;
  } else {
    SataPortsEnabled    = MmioRead16 (PciSataRegBase + R_PCH_LP_SATA_PCS);
    SataPortsEnabled    &= (UINT16) (B_PCH_LP_SATA_PCS_PXE_MASK);
    PortxEnabled        = B_PCH_LP_SATA_PCS_P0E;
    PortxEnabledOffset  = R_PCH_LP_SATA_PCS;
    PortxEnabledMask    = B_PCH_LP_SATA_PCS_PXE_MASK;
  }

  //
  // Read the default value of the Host Capabilites Register
  // NOTE: many of the bits in this register are R/WO (Read/Write Once)
  //
  CapRegister = MmioRead32 (AhciBar + R_PCH_SATA_AHCI_CAP);
  CapRegister &= (UINT32) ~(B_PCH_SATA_AHCI_CAP_SIS | B_PCH_SATA_AHCI_CAP_SSS | B_PCH_SATA_AHCI_CAP_SALP |
                            B_PCH_SATA_AHCI_CAP_PMS | B_PCH_SATA_AHCI_CAP_SSC | B_PCH_SATA_AHCI_CAP_PSC |
                            B_PCH_SATA_AHCI_CAP_SXS);

  for (Index = 0; Index < MaxSataPorts; Index++) {
    //
    // Check PCS.PxE to know if the SATA Port x is disabled.
    //
    if ((SataPortsEnabled & (PortxEnabled << Index)) == 0) {
      continue;
    }

    if (SataConfig->PortSettings[Index].InterlockSw == TRUE) {
      //
      // Mechanical Presence Switch is Enabled for at least one of the ports
      //
      CapRegister |= B_PCH_SATA_AHCI_CAP_SIS;
    }

    if ((SataConfig->PortSettings[Index].SpinUp == TRUE) ||
        (SataConfig->PortSettings[Index].External == TRUE)) {
      //
      // PCH BIOS Spec Section 14.1.4 Initialize Registers in AHCI Memory-Mapped Space
      // Step 1.4
      // Set SSS (ABAR + 00h[27]) to enable SATA controller supports staggered
      // spin-up on its ports, for use in balancing power spikes
      // SATA Port Spin up is supported at least one of the ports
      // If this is an extra eSATA port. It needs to be hotpluggable but it's usually empty anyway
      // so LPM is not available but Listen Mode is available, so it will have good power management.
      // If Sata Test Mode enabled, then uncoditonally clear SSS (ABAR + 00h[27])
      // to resolve Spin-donw issue with the test equiepment
      //
      if (SataConfig->TestMode == FALSE ) {
        CapRegister |= B_PCH_SATA_AHCI_CAP_SSS;
      }
    }

    if (SataConfig->PortSettings[Index].External == TRUE) {
      //
      // External SATA is supported at least one of the ports
      //
      CapRegister |= B_PCH_SATA_AHCI_CAP_SXS;
    }
  }

  //
  // PCH BIOS Spec Section 14.1.4 Initialize Registers in AHCI Memory-Mapped Space
  // Step 1
  // Set PSC (ABAR + 00h[13]). This bit informs the Windows software driver that the AHCI
  // Controller supports the partial low-power state.
  // Set SSC (ABAR + 00h[14]). This bit informs the Windows software driver that the AHCI
  // Controller supports the slumber low-power state.
  // Set SALP (ABAR + 00h[26]) to enable Aggressive Link Power Management (LPM) support.
  //
  CapRegister |= (B_PCH_SATA_AHCI_CAP_SSC | B_PCH_SATA_AHCI_CAP_PSC);

  if (SataConfig->SalpSupport == TRUE) {
    CapRegister |= B_PCH_SATA_AHCI_CAP_SALP;
  }
  //
  // Support Command List Override & PIO Multiple DRQ Block
  //
  CapRegister |= (B_PCH_SATA_AHCI_CAP_SCLO | B_PCH_SATA_AHCI_CAP_PMD);

  //
  // Configure for the max speed support 1.5Gb/s, 3.0Gb/s and 6.0Gb/s.
  //
  CapRegister &= ~B_PCH_SATA_AHCI_CAP_ISS_MASK;

  switch (SataConfig->SpeedLimit) {
    case PchSataSpeedGen1:
      CapRegister |= (V_PCH_SATA_AHCI_CAP_ISS_1_5_G << N_PCH_SATA_AHCI_CAP_ISS);
      break;

    case PchSataSpeedGen2:
      CapRegister |= (V_PCH_SATA_AHCI_CAP_ISS_3_0_G << N_PCH_SATA_AHCI_CAP_ISS);
      break;

    case PchSataSpeedGen3:
    case PchSataSpeedDefault:
      CapRegister |= (V_PCH_SATA_AHCI_CAP_ISS_6_0_G << N_PCH_SATA_AHCI_CAP_ISS);
      break;
  }

  //
  // If remapping is enabled, disable Enclosure Management capability
  //
  if (IsRstPcieStorageRemapEnabled (&SataConfig->RstPcieStorageRemap[0])) {
    CapRegister &= ~B_PCH_SATA_AHCI_CAP_EMS;
  }

  //
  // Update the Host Capabilites Register
  // NOTE: Many of the bits in this register are R/WO (Read/Write Once)
  //
  MmioWrite32 (AhciBar + R_PCH_SATA_AHCI_CAP, CapRegister);

  ///
  /// Enable implemented SATA ports by setting respective PI bits to 1b
  /// If BIOS accesses any of the port specific AHCI address range before setting PI bit,
  /// BIOS is required to read the PI register before the initial write to the PI register.
  /// NOTE: The read before initial write to PI register is done by the MmioAndThenOr32 routine.
  /// NOTE: many of the bits in this register are R/WO (Read/Write Once)
  ///
  Data32Or = 0;
  for (Index = 0; Index < MaxSataPorts; Index++) {
    Data32Or |= SataConfig->PortSettings[Index].Enable << Index;
  }
  MmioOr32 (AhciBar + R_PCH_SATA_AHCI_PI, Data32Or);

  ///
  /// After BIOS issues initial write to this register, BIOS is requested to issue two
  /// reads to this register.
  ///
  Data32Or = MmioRead32 (AhciBar + R_PCH_SATA_AHCI_PI);
  Data32Or = MmioRead32 (AhciBar + R_PCH_SATA_AHCI_PI);

  ///
  /// Set ABAR + 24h[5] to 1b
  /// Set ABAR + 24h[4:2] to 111b
  ///
  Data32Or = B_PCH_SATA_AHCI_CAP2_DESO;
  Data32Or |= B_PCH_SATA_AHCI_CAP2_SDS | B_PCH_SATA_AHCI_CAP2_SADM | B_PCH_SATA_AHCI_CAP2_APST;
  MmioOr32 (AhciBar + R_PCH_SATA_AHCI_CAP2, Data32Or);

  ///
  /// Program all PCS "Port X Enabled" to all 0b,
  /// then program them again to all 1b in order to trigger COMRESET
  ///
  MmioAnd16 (PciSataRegBase + PortxEnabledOffset, (UINT16) ~PortxEnabledMask);
  MmioOr16 (PciSataRegBase + PortxEnabledOffset, (UINT16) PortxEnabledMask);

  ///
  /// Port[Max:0] Command Register update
  /// NOTE: this register must be updated after Port Implemented and Capabilities register,
  /// Many of the bits in this register are R/WO (Read/Write Once)
  ///
  for (Index = 0; Index < MaxSataPorts; Index++) {
    ///
    /// Check PCS.PxE to know if the SATA Port x is disabled.
    ///
    if ((SataPortsEnabled & (PortxEnabled << Index)) == 0) {
      continue;
    }
    ///
    /// Initial to zero first
    ///
    PxCMDRegister = 0;

    if (SataConfig->PortSettings[Index].HotPlug == TRUE) {
      if (SataConfig->PortSettings[Index].External == FALSE) {
        ///
        /// Hot Plug of this port is enabled
        ///
        PxCMDRegister |= B_PCH_SATA_AHCI_PxCMD_HPCP;
        if (SataConfig->PortSettings[Index].InterlockSw == TRUE) {
          ///
          /// Mechanical Switch of this port is Attached
          ///
          PxCMDRegister |= B_PCH_SATA_AHCI_PxCMD_MPSP;

          ///
          /// Check the GPIO Pin is set as used for native function not a normal GPIO
          ///
          if (GpioIsSataResetPortInGpioMode (Index)) {
            DEBUG ((DEBUG_ERROR,
                    "BIOS must set the SATA%0xGP GPIO pin to native function if Inter Lock Switch is enabled!\n",
                    Index));
            ASSERT_EFI_ERROR (EFI_DEVICE_ERROR);
          }

        }
      }
    } else {
      ///
      /// When "Mechanical Switch Attached to Port" (PxCMD[19]) is set, it is expected that HPCP (PxCMD[18]) is also set.
      ///
      if (SataConfig->PortSettings[Index].InterlockSw == TRUE) {
        DEBUG ((DEBUG_ERROR, "Hot-Plug function of Port%d should be enabled while the Inter Lock Switch of it is enabled!\n",
                Index));
      }
    }

    if (SataConfig->PortSettings[Index].External == TRUE) {
      PxCMDRegister |= B_PCH_SATA_AHCI_PxCMD_ESP;
    }

    ///
    /// Set ALPE
    ///
    PxCMDRegister |= (B_PCH_SATA_AHCI_PxCMD_ALPE);

    ///
    /// If the SATA controller supports staggerred spin-up (SSS in AHCI_CAP is set to 1b),
    /// then set the SUD bit in Port[Max:0] Command Register to 1b
    ///
    if ((CapRegister & B_PCH_SATA_AHCI_CAP_SSS) != 0) {
      PxCMDRegister |= B_PCH_SATA_AHCI_PxCMD_SUD;
    }

    MmioAndThenOr32 (
      AhciBar + (R_PCH_SATA_AHCI_P0CMD + (0x80 * Index)),
      (UINT32) ~(B_PCH_SATA_AHCI_PxCMD_MASK),
      (UINT32) PxCMDRegister
      );

    ///
    /// DevSleep programming
    /// Set ABAR + 144h[1], ABAR + 1C4h[1], ABAR + 244h[1], ABAR + 2C4[1] to 0b as default
    /// Board rework is required to enable DevSlp.
    /// POR settings are ABAR + 144h[1], ABAR + 1C4h[1], ABAR + 244h[1] = 1b, ABAR + 2C4[1] to 0b
    ///
    if (SataConfig->PortSettings[Index].DevSlp == TRUE) {
      Data32And = (UINT32) ~(B_PCH_SATA_AHCI_PxDEVSLP_DITO_MASK | B_PCH_SATA_AHCI_PxDEVSLP_DM_MASK);
      Data32Or  = (B_PCH_SATA_AHCI_PxDEVSLP_DSP | V_PCH_SATA_AHCI_PxDEVSLP_DM_16 | V_PCH_SATA_AHCI_PxDEVSLP_DITO_625);

      if (SataConfig->PortSettings[Index].EnableDitoConfig == TRUE) {
        Data32Or &= Data32And;
        Data32Or |= ((SataConfig->PortSettings[Index].DitoVal << 15) | (SataConfig->PortSettings[Index].DmVal << 25));
      }

      MmioAndThenOr32 (
        AhciBar + (R_PCH_SATA_AHCI_P0DEVSLP + (0x80 * Index)),
        Data32And,
        Data32Or
        );
    } else {
      MmioAnd32 (
        AhciBar + (R_PCH_SATA_AHCI_P0DEVSLP + (0x80 * Index)),
        (UINT32) ~(B_PCH_SATA_AHCI_PxDEVSLP_DSP)
        );
    }

    //
    // eSATA port support only up to Gen2.
    // When enabled, BIOS will configure the PxSCTL.SPD to 2 to limit the eSATA port speed.
    // Please be noted, this setting could be cleared by HBA reset, which might be issued
    // by EFI AHCI driver when POST time, or by SATA inbox driver/RST driver after POST.
    // To support the Speed Limitation when POST, the EFI AHCI driver should preserve the
    // setting before and after initialization. For support it after POST, it's dependent on
    // driver's behavior.
    //
    if ((SataConfig->EsataSpeedLimit == TRUE) &&
        (SataConfig->PortSettings[Index].External == TRUE)) {
      PortSataControl = MmioRead8 (AhciBar + (R_PCH_SATA_AHCI_P0SCTL + (0x80 * Index)));
      PortSataControl &= (UINT8) ~(B_PCH_SATA_AHCI_PXSCTL_SPD);
      PortSataControl |= (UINT8) V_PCH_SATA_AHCI_PXSCTL_SPD_2;
      MmioWrite8 (AhciBar + (R_PCH_SATA_AHCI_P0SCTL + (0x80 * Index)), PortSataControl);
    }
  }

  /// PCH BIOS Spec Section 14.1.5.2 Enable Flexible RAID OROM Features
  /// Lynx Point with RAID capable sku is able to customize the RAID features through setting the
  /// Intel RST Feature Capabilities (RSTF) register before loading the RAID Option ROM. The RAID
  /// OROM will enable the desired features based on the setting in that register, please refer to
  /// PCH EDS for more details.
  /// For example, if the platform desired features are RAID0, RAID1, RAID5, RAID10 and
  /// RST Smart Storage caching. System BIOS should set RSTF (ABAR + C8h [15:0]) to 022Fh before
  /// loading RAID OROM.
  ///
  WordReg = 0;

  if (SataConfig->Rst.HddUnlock == TRUE) {
    ///
    /// If set to "1", indicates that the HDD password unlock in the OS is enabled
    /// while SATA is configured as RAID mode.
    ///
    WordReg |= B_PCH_SATA_AHCI_RSTF_HDDLK;
  }

  if (SataConfig->Rst.LedLocate == TRUE) {
    ///
    /// If set to "1", indicates that the LED/SGPIO hardware is attached and ping to
    /// locate feature is enabled on the OS while SATA is configured as RAID mode.
    ///
    WordReg |= B_PCH_SATA_AHCI_RSTF_LEDL;
  }

  if (SataConfig->SataMode == PchSataModeRaid) {
    if (SataConfig->Rst.LegacyOrom == TRUE) {
      ///
      /// If set to "1", then Legacy OROM is enabled
      ///
      WordReg |= B_PCH_SATA_AHCI_RSTF_LEGACY;
    }

    if (SataConfig->Rst.Raid0 == TRUE) {
      ///
      /// If set to "1", then RAID0 is enabled in Flexible RAID Option ROM.
      ///
      WordReg |= B_PCH_SATA_AHCI_RSTF_R0E;
    }

    if (SataConfig->Rst.Raid1 == TRUE) {
      ///
      /// If set to "1", then RAID1 is enabled in FD-OROM.
      ///
      WordReg |= B_PCH_SATA_AHCI_RSTF_R1E;
    }

    if (SataConfig->Rst.Raid10 == TRUE) {
      ///
      /// If set to "1", then RAID10 is enabled in FD-OROM.
      ///
      WordReg |= B_PCH_SATA_AHCI_RSTF_R10E;
    }

    if (SataConfig->Rst.Raid5 == TRUE) {
      ///
      /// If set to "1", then RAID5 is enabled in FD-OROM.
      ///
      WordReg |= B_PCH_SATA_AHCI_RSTF_R5E;
    }

    if (SataConfig->Rst.Irrt == TRUE) {
      ///
      /// If set to "1", then Intel Rapid Recovery Technology is enabled.
      ///
      WordReg |= B_PCH_SATA_AHCI_RSTF_RSTE;
    }

    if (SataConfig->Rst.OromUiBanner == TRUE) {
      ///
      /// If set to "1" then the OROM UI is shown.  Otherwise, no OROM banner or information
      /// will be displayed if all disks and RAID volumes are Normal.
      ///
      WordReg |= B_PCH_SATA_AHCI_RSTF_IRSTOROM;
    }

    if (SataConfig->Rst.IrrtOnly == TRUE) {
      ///
      /// If set to "1", then only IRRT volumes can span internal and eSATA drives. If cleared
      /// to "0", then any RAID volume can span internal and eSATA drives.
      ///
      WordReg |= B_PCH_SATA_AHCI_RSTF_IROES;
    }
    ///
    /// Enable the RST Smart Storage caching bit to support Smart Storage caching.
    ///
    if (SataConfig->Rst.SmartStorage == TRUE) {
      WordReg |= B_PCH_SATA_AHCI_RSTF_SEREQ;
    }
    ///
    /// Program the delay of the OROM UI Splash Screen in a normal status.
    ///
    WordReg |= (UINT16) (SataConfig->Rst.OromUiDelay << N_PCH_SATA_AHCI_RSTF_OUD);

    if (SataConfig->Rst.OptaneMemory == TRUE) {
      ///
      /// If set to "1", then Optane(TM) Memory Acceleration is enabled
      ///
      WordReg |= B_PCH_SATA_AHCI_RSTF_OMA;
    }

    if (SataConfig->Rst.CpuAttachedStorage) {
      WordReg |= B_PCH_SATA_AHCI_RSTF_CPU_STORAGE;
    }
  }

  ///
  /// RSTF(RST Feature Capabilities) is a Write-Once register.
  ///
  MmioWrite16 (AhciBar + R_PCH_SATA_AHCI_RSTF, WordReg);

  ///
  /// Disable command register memory space decoding
  ///
  MmioAnd16 (PciSataRegBase + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);

  ///
  /// Set Ahci Bar to zero
  ///
  AhciBar = 0;
  MmioWrite32 (PciSataRegBase + R_PCH_SATA_AHCI_BAR, AhciBar);

  ///
  /// if in test mode enable, perform misc programming for test mode
  ///
  if (SataConfig->TestMode == TRUE) {
    ProgramSataTestMode ();
  }

  DEBUG ((DEBUG_INFO, "ConfigurePchSataAhci() End\n"));
  return EFI_SUCCESS;
}

#ifndef MINTREE_FLAG
/**
  Disable Sata Controller for PCH-LP

  @param[in] AhciBarAddress       The Base Address for AHCI BAR

  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
DisablePchLpSataController (
  IN UINT32                             AhciBarAddress
  )
{
  UINTN                                 PciSataRegBase;
  UINT32                                AhciBar;
  UINT32                                Data32And;
  UINT32                                Data32Or;
  UINT32                                PchPwrmBase;
  UINTN                                 Index;
  PciSataRegBase  = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_SATA, PCI_FUNCTION_NUMBER_PCH_SATA);

  DEBUG ((DEBUG_INFO, "DisablePchLpSataController: DisablePchLpSataController() Started\n"));

  ///
  /// Set the AHCI BAR
  ///
  AhciBar = AhciBarAddress;
  MmioWrite32 (PciSataRegBase + R_PCH_SATA_AHCI_BAR, AhciBar);

  ///
  /// Enable command register memory space decoding
  ///
  MmioOr16 (PciSataRegBase + PCI_COMMAND_OFFSET, (UINT16) EFI_PCI_COMMAND_MEMORY_SPACE);

  ///
  /// PCH BIOS Spec Section 14.3 SATA Controller Disabling
  /// Step 1 - Disable all ports
  /// Set SATA PCI offset 92h[2:0] to all 0b
  ///
  MmioAnd16 (PciSataRegBase + R_PCH_LP_SATA_PCS, (UINT16) ~(B_PCH_LP_SATA_PCS_PXE_MASK));

  ///
  /// Step 2 - Disable all ports
  /// Clear PI register, ABAR + 0Ch
  ///
  Data32And = (UINT32) (~B_PCH_LP_SATA_PORT_MASK);
  MmioAnd32 (AhciBar + R_PCH_SATA_AHCI_PI, Data32And);

  ///
  /// After BIOS issues initial write to this register, BIOS is requested to
  /// issue two reads to this register.
  ///
  Data32Or = MmioRead32 (AhciBar + R_PCH_SATA_AHCI_PI);
  Data32Or = MmioRead32 (AhciBar + R_PCH_SATA_AHCI_PI);

  ///
  /// Step 3
  /// Clear MSE and IOE, SATA PCI offset 4h[1:0] = 00b
  ///
  MmioAnd16 (PciSataRegBase + PCI_COMMAND_OFFSET, (UINT16) ~(EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_IO_SPACE));

  ///
  /// Step 4
  /// Set Sata Port Clock Disable bits SATA PCI offset 94h[26:24] to 7h
  ///
  MmioOr32 (PciSataRegBase + R_PCH_LP_SATA_SCLKGC, (UINT32) (B_PCH_LP_SATA_SCLKGC_PCD));

  ///
  /// Step 5 Enable all SATA dynamic clock gating and dynamic power gating features:
  ///  a. SATA PCI offset 98h bit [29, 23] = [1, 1]
  ///  b. SATA SIR offset 70h bit [26:24, 15, 10:8] to all 1b
  ///  c. SATA SIR offset 54h bit [30, 26:24, 21] = [1, 1s, 1]
  ///  d. SATA SIR offset 58h bit [26, 25, 24] = [0, 0, 0]
  ///  e. SATA SIR offset 5Ch bit [17, 16] = [1, 1]
  ///
  /// Step 5a
  /// SATA PCI offset 98h bit [29, 23] = [1, 1]
  ///
  MmioOr32 (PciSataRegBase + R_PCH_LP_SATA_98, (UINT32) (BIT29 | BIT23));

  ///
  /// Step 5b
  /// SATA SIR offset 70h bit [26:24, 15, 10:8] to all 1b
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_70);
  MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, 0x07008700);

  ///
  /// Step 5c
  /// SATA SIR offset 54h bit [30, 26:24, 21] = [1, 1s, 1]
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_54);
  MmioOr32 (
    PciSataRegBase + R_PCH_SATA_STRD,
    (UINT32) (BIT30 | BIT26 | BIT25 | BIT24 | BIT21)
    );

  ///
  /// Step 5d
  /// SATA SIR offset 58h bit [26, 25, 24] = [0, 0, 0]
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_58);
  MmioAnd32 (PciSataRegBase + R_PCH_SATA_STRD,(UINT32) ~(BIT26 | BIT25 | BIT24));

  ///
  /// Step 5e
  /// SATA SIR offset 5Ch bit [17, 16] = [1, 1]
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_5C);
  Data32And = (UINT32) ~(BIT17 | BIT16);
  Data32Or  = (UINT32) (BIT17 | BIT16);
  MmioAndThenOr32 (
    PciSataRegBase + R_PCH_SATA_STRD,
    Data32And,
    Data32Or
    );
  ///
  /// Step 5f For each RST PCIe Storage Cycle Router, program the "Extended General Configuration Register" field,
  ///
  for (Index = 0; Index < PCH_MAX_RST_PCIE_STORAGE_CR; Index++) {
    MmioWrite8 (PciSataRegBase + R_PCH_RST_PCIE_STORAGE_CRGC, (UINT8) Index);
    MmioOr32 (PciSataRegBase + R_PCH_RST_PCIE_STORAGE_EGCR,(UINT32) (B_PCH_RST_PCIE_STORAGE_EGCR_CRDCGE | B_PCH_RST_PCIE_STORAGE_EGCR_CRTCGE | B_PCH_RST_PCIE_STORAGE_EGCR_ICAS | B_PCH_RST_PCIE_STORAGE_EGCR_TSCAS));
  }
  ///
  /// Step 6
  /// Disabling SATA Device by programming SATA SCFD, SATA PCI offset 9Ch[10] = 1
  ///
  MmioOr32 (PciSataRegBase + R_PCH_SATA_SATAGC, (UINT32) (BIT10));

  ///
  /// Step 7
  /// Disable SATA in PSF
  ///
  PsfDisableSataDevice ();

  ///
  /// Set Ahci Bar to zero (Note: MSE and IO has been disabled)
  ///
  AhciBar = 0;
  MmioWrite32 (PciSataRegBase + R_PCH_SATA_AHCI_BAR, AhciBar);

  ///
  /// Set PWRMBASE + 0x628 [22] = 1b to disable SATA Controller in PMC
  /// No need to clear this non-static PG bit while IP re-enabled since it's reset to 0 when PLTRST.
  ///
  PchPwrmBaseGet (&PchPwrmBase);
  MmioOr32 (PchPwrmBase + R_PCH_PWRM_NST_PG_FDIS_1, B_PCH_PWRM_NST_PG_FDIS_1_SATA_FDIS_PMC);

  DEBUG ((DEBUG_INFO, "DisablePchLpSataController: DisablePchLpSataController() Ended\n"));

  return EFI_SUCCESS;
}

/**
  Disable Sata Controller for PCH-H

  @param[in] AhciBarAddress       The Base Address for AHCI BAR

  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
DisablePchHSataController (
  IN UINT32                             AhciBarAddress
  )
{
  UINTN                                 PciSataRegBase;
  UINT32                                AhciBar;
  UINT32                                Data32And;
  UINT32                                Data32Or;
  UINT32                                PchPwrmBase;
  UINTN                                 Index;

  PciSataRegBase  = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_SATA, PCI_FUNCTION_NUMBER_PCH_SATA);

  DEBUG ((DEBUG_INFO, "DisablePchHSataController: DisablePchHSataController() Started\n"));

  ///
  /// Set the AHCI BAR
  ///
  AhciBar = AhciBarAddress;
  MmioWrite32 (PciSataRegBase + R_PCH_SATA_AHCI_BAR, AhciBar);

  ///
  /// Enable command register memory space decoding
  ///
  MmioOr16 (PciSataRegBase + PCI_COMMAND_OFFSET, (UINT16) EFI_PCI_COMMAND_MEMORY_SPACE);

  ///
  /// PCH BIOS Spec Section 14.3 SATA Controller Disabling
  /// Step 1 - Disable all ports
  /// Set SATA PCI offset 94h[7:0] to all 0b
  ///
  MmioAnd16 (PciSataRegBase + R_PCH_H_SATA_PCS, (UINT16) ~(B_PCH_H_SATA_PCS_PXE_MASK));

  ///
  /// Step 2 - Disable all ports
  /// Clear PI register, ABAR + 0Ch
  ///
  Data32And = (UINT32) (~B_PCH_H_SATA_PORT_MASK);
  MmioAnd32 (AhciBar + R_PCH_SATA_AHCI_PI, Data32And);

  ///
  /// After BIOS issues initial write to this register, BIOS is requested to
  /// issue two reads to this register.
  ///
  Data32Or = MmioRead32 (AhciBar + R_PCH_SATA_AHCI_PI);
  Data32Or = MmioRead32 (AhciBar + R_PCH_SATA_AHCI_PI);

  ///
  /// Step 3
  /// Clear MSE and IOE, SATA PCI offset 4h[1:0] = 00b
  ///
  MmioAnd16 (PciSataRegBase + PCI_COMMAND_OFFSET, (UINT16) ~(EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_IO_SPACE));

  ///
  /// Step 4
  /// Set Sata Port Clock Disable bits, SATA PCI offset 90h[7:0] to all 1b
  ///
  MmioOr32 (PciSataRegBase + R_PCH_H_SATA_MAP, (UINT32) B_PCH_H_SATA_MAP_PCD);

  ///
  /// Step 5 Enable all SATA dynamic clock gating and dynamic power gating features:
  ///  a. SATA SIR offset 9Ch bit[29, 23] = [1, 1]
  ///  b. SATA SIR offset 8Ch bit[23:16, 7:0] to all 1b
  ///  c. SATA SIR offset A0h bit[15] to [1]
  ///  d. SATA SIR offset 84h bit[23:16] to all 1b
  ///  e. SATA SIR offset A4h bit[26, 25, 24, 14, 5] = [0, 0, 0, 1, 1]
  ///  f. SATA SIR offset A8h bit[17, 16] = [1, 1]
  ///
  /// Step 5a
  /// SATA SIR offset 9Ch bit[29, 23] = [1, 1]
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_9C);
  MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, (UINT32) (BIT29 | BIT23));

  ///
  /// Step 5b
  /// SATA SIR offset 8Ch bit[23:16, 7:0] to all 1b
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_8C);
  MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, 0x00FF00FF);

  ///
  /// Step 5c
  /// SATA SIR offset A0h bit[15] to [1]
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_A0);
  MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, (UINT32) (BIT15));

  ///
  /// Step 5d
  /// SATA SIR offset 84h bit[23:16] to all 1b
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_84);
  MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, 0x00FF0000);

  ///
  /// Step 5e
  /// SATA SIR offset A4h bit[26, 25, 24, 14, 5] = [0, 0, 0, 1, 1]
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_A4);
  Data32And = (UINT32) ~(BIT26 | BIT25 | BIT24 | BIT14 | BIT5);
  Data32Or  = (UINT32) (BIT14 | BIT5);
  MmioAndThenOr32 (
    PciSataRegBase + R_PCH_SATA_STRD,
    Data32And,
    Data32Or
    );

  ///
  /// Step 5f
  /// SATA SIR offset A8h bit[17, 16] = [1, 1]
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_A8);
  Data32And = (UINT32) ~(BIT17 | BIT16);
  Data32Or  = (UINT32) (BIT17 | BIT16);
  MmioAndThenOr32 (
    PciSataRegBase + R_PCH_SATA_STRD,
    Data32And,
    Data32Or
    );
  ///
  /// Step 5g For each RST PCIe Storage Cycle Router, program the "Extended General Configuration Register" field,
  ///
  for (Index = 0; Index < PCH_MAX_RST_PCIE_STORAGE_CR; Index++) {
    MmioWrite8 (PciSataRegBase + R_PCH_RST_PCIE_STORAGE_CRGC, (UINT8) Index);
    MmioOr32 (PciSataRegBase + R_PCH_RST_PCIE_STORAGE_EGCR,(UINT32) (B_PCH_RST_PCIE_STORAGE_EGCR_CRDCGE | B_PCH_RST_PCIE_STORAGE_EGCR_CRTCGE | B_PCH_RST_PCIE_STORAGE_EGCR_ICAS | B_PCH_RST_PCIE_STORAGE_EGCR_TSCAS));
  }
  ///
  /// Step 6
  /// Disabling SATA Device by programming SATA SCFD, SATA PCI offset 9Ch[10] = 1
  ///
  MmioOr32 (PciSataRegBase + R_PCH_SATA_SATAGC, (UINT32) (BIT10));

  ///
  /// Step 7
  /// Disable SATA in PSF
  ///
  PsfDisableSataDevice ();

  ///
  /// Set Ahci Bar to zero (Note: MSE and IO has been disabled)
  ///
  AhciBar = 0;
  MmioWrite32 (PciSataRegBase + R_PCH_SATA_AHCI_BAR, AhciBar);

  ///
  /// Set PWRMBASE + 0x628 [22] = 1b to disable SATA Controller in PMC
  /// No need to clear this non-static PG bit while IP re-enabled since it's reset to 0 when PLTRST.
  ///
  PchPwrmBaseGet (&PchPwrmBase);
  MmioOr32 (PchPwrmBase + R_PCH_PWRM_NST_PG_FDIS_1, B_PCH_PWRM_NST_PG_FDIS_1_SATA_FDIS_PMC);

  DEBUG ((DEBUG_INFO, "DisablePchHSataController: DisablePchHSataController() Ended\n"));

  return EFI_SUCCESS;
}
#endif //MINTREE_FLAG

/**
  Configure the Power Management setting for RST PCIe Storage Remapping

  @param[in] SataRegBase  SATA PCI config space base address
**/
VOID
RstConfigurePm (
  IN UINTN  SataRegBase
  )
{
  UINTN  Index;

  //
  // For each RST PCIe Storage Cycle Router, program the "Extended General Configuration Register" field,
  //
  for (Index = 0; Index < PCH_MAX_RST_PCIE_STORAGE_CR; Index++) {
    DEBUG ((DEBUG_INFO, "RstConfigurePm: Low Power Programming - Recommanded Setting\n"));
    MmioWrite8 (SataRegBase + R_PCH_RST_PCIE_STORAGE_CRGC, (UINT8)Index);
    //
    // Program the SATA PCI offset 354h bit [20, 19, 17, 16] to [1b, 1b, 1b, 1b]
    //
    MmioOr32 (SataRegBase + R_PCH_RST_PCIE_STORAGE_EGCR,
              B_PCH_RST_PCIE_STORAGE_EGCR_CRDCGE |
              B_PCH_RST_PCIE_STORAGE_EGCR_CRTCGE |
              B_PCH_RST_PCIE_STORAGE_EGCR_ICAS |
              B_PCH_RST_PCIE_STORAGE_EGCR_TSCAS);

    MmioOr32 (SataRegBase + R_PCH_RST_PCIE_STORAGE_GCR, B_PCH_RST_PCIE_STORAGE_GCR_PCRTCGP);
  }
}

/**
  Configures PCH Sata Controller for PCH-LP

  @param[in] SataConfig                     The PCH Policy for SATA configuration
  @param[in] RstPcieStorageRemapEnabled     A Boolean to indicate if RST PCIe Storage Remapping is enabled
  @param[in] AhciBarAddress                 The Base Address for AHCI BAR

  @retval EFI_SUCCESS                       The function completed successfully
  @retval EFI_ABORTED                       SATA controller is Function Disabled, to abort initializing SATA controller.
**/
EFI_STATUS
EarlyConfigurePchLpSata (
  IN CONST PCH_SATA_CONFIG                    *SataConfig,
  IN BOOLEAN                                  RstPcieStorageRemapEnabled,
  IN UINT32                                   AhciBarAddress
  )
{
  EFI_STATUS              Status;
  UINT8                   SataGcReg;
  UINTN                   PciSataRegBase;
  UINT16                  LpcDeviceId;
  UINT32                  Data32And;
  UINT32                  Data32Or;

  DEBUG ((DEBUG_INFO, "EarlyConfigurePchLpSata() Start\n"));

  PciSataRegBase    = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_SATA, PCI_FUNCTION_NUMBER_PCH_SATA);
  LpcDeviceId       = GetLpcDid ();
  Status            = EFI_SUCCESS;
  #ifndef MINTREE_FLAG
  ///
  /// If Sata is disabled or no lanes assigned to SATA when in AHCI mode
  /// perform the disabling steps to function disable the SATA Controller
  ///
  if ((SataConfig->Enable == FALSE) || ((!SataLaneExist ()) && (SataConfig->SataMode == PchSataModeAhci))) {
    DisablePchLpSataController (AhciBarAddress);
    return EFI_ABORTED;
  }
  #endif //MINTREE_FLAG
  ///
  /// PCH BIOS Spec section 14.1.7 Additional Programming Requirements during
  /// SATA Initialization
  /// Step 1
  /// System BIOS must set SATA PCI offset 94h[8:0] = 183h as part of the chipset initialization
  /// prior to SATA configuration. These bits should be restored while resuming from a S3
  /// sleep state.
  ///
  Data32And = (UINT32) ~(BIT8 | BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0);
  Data32Or  = 0x183;
  MmioAndThenOr32 (
    PciSataRegBase + R_PCH_LP_SATA_SCLKGC,
    Data32And,
    Data32Or
    );

  ///
  /// Step 2
  /// Set SATA PCI offset 92h[15] = 1b
  /// Set OOB Retry Mode bit of Port Control and Status (PCS) register
  /// These bits should be restored while resuming from a S3 sleep state
  ///
  MmioOr16 (PciSataRegBase + R_PCH_LP_SATA_PCS, (UINT16) (B_PCH_LP_SATA_PCS_OOB_RETRY));

  ///
  /// Step 3
  /// System BIOS must program SATA Hsio table as stated in Table 7-7 to 7-8 BEFORE the SATA
  /// ports are enabled.
  ///

  ///
  /// PCH BIOS Spec section 14.1.7 Additional Programming Requirements during
  /// SATA Initialization
  /// Step 4
  /// Program SATA PCI offset 98h[22] to 1b for desktop and mobile platform only. (Server may leave as default)
  ///
  if (IS_PCH_LPC_DEVICE_ID_DESKTOP (LpcDeviceId) ||
      IS_PCH_LPC_DEVICE_ID_MOBILE (LpcDeviceId)) {
    MmioOr32 (PciSataRegBase + R_PCH_LP_SATA_98, (UINT32) (BIT22));
  }

  ///
  /// Step 4
  /// Program SATA PCI offset 98h[29,23,20,19,18] to all 1b
  /// Program SATA PCI offset 98h[12:7] = 04h
  /// Program SATA PCI offset 98h[6:5] to 01b
  /// Program SATA PCI offset 98h[3:2] to 01b
  /// Note: If [3:2] value recommendation get changed, please refer to definition if Bit 1:0 and program per table accordingly
  ///
  Data32And = (UINT32) (~(BIT12 | BIT11 | BIT10 | BIT9 | BIT8 | BIT7 | BIT6 | BIT5 | BIT3 | BIT2));
  Data32Or  = (UINT32) (BIT29 | BIT23 | BIT20 | BIT19 | BIT18 | BIT9 | BIT5 | BIT2);
  MmioAndThenOr32 (
    PciSataRegBase + R_PCH_LP_SATA_98,
    Data32And,
    Data32Or
    );

  ///
  /// Step 5
  /// Program SATA PCI offset 9Ch[5] to 1b
  /// @note: Bits 7:0 are RWO, perform byte write here, program the 9Ch[31] to 1b later in PchOnEndOfDxe ()
  ///
  SataGcReg = MmioRead8 (PciSataRegBase + R_PCH_SATA_SATAGC);
  SataGcReg |= BIT5;

  ConfigureSataControllerDeviceId (&SataGcReg, SataConfig);

  ///
  /// If RstPcieStorageRemapEnabled is TRUE, program Sata PCI offset 9Ch, bit[4:3] and bit[2:0] to [00'b] and [110'b]
  /// else, program Sata PCI offset 9Ch, bit[4:3] and bit[2:0] to [10'b] and [000'b], and also disable Rst remap decoding
  ///
  if (RstPcieStorageRemapEnabled) {
    SataGcReg |= V_PCH_SATA_SATAGC_ASSEL_512K;
    SataGcReg &= ~(B_PCH_SATA_SATAGC_MSS);
  } else {
    SataGcReg &= ~B_PCH_SATA_SATAGC_ASSEL;
    SataGcReg |= V_PCH_SATA_SATAGC_MSS_8K << N_PCH_SATA_SATAGC_MSS;
    DisableRstRemapDecoding (AhciBarAddress);
  }

  ///
  /// Unconditional write is necessary to lock the register
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SATAGC, SataGcReg);

  ///
  /// Program PCS "Port X Enabled", SATA PCI offset 92h[2:0] to all 1b
  ///
  MmioOr16 (PciSataRegBase + R_PCH_LP_SATA_PCS, (UINT16) B_PCH_LP_SATA_PCS_PXE_MASK);

  ///
  /// PCH BIOS Spec section 19.10
  /// Step 4.2
  /// After configuring Port and Control Status (PCS) Register Port x Enabled (PxE) bits accordingly,
  /// wait 1.4 micro second
  ///
  MicroSecondDelay (0x02);

  DEBUG ((DEBUG_INFO, "EarlyConfigurePchLpSata() End\n"));

  return Status;
}

/**
  Additional SATA configuration

  @param[in] SataConfig                     The PCH Policy for SATA configuration
  @param[in] AhciBarAddress                 The Base Address for AHCI BAR
**/
VOID
ConfigurePchLpSata (
  IN CONST PCH_SATA_CONFIG                    *SataConfig,
  IN UINT32                                   AhciBarAddress
  )
{
  EFI_STATUS              Status;
  UINTN                   PciSataRegBase;
  RST_MODE                RstMode;
  UINTN                   MaxSataPorts;
  UINT32                  DisableDynamicPowerGateBitMap;
  UINT8                   Index;
  UINT32                  Data32And;
  UINT32                  Data32Or;

  DEBUG ((DEBUG_INFO, "ConfigurePchLpSata() Start\n"));

  PciSataRegBase    = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_SATA, PCI_FUNCTION_NUMBER_PCH_SATA);
  RstMode           = GetSupportedRstMode ();

  ///
  /// Configure AHCI
  ///
  Status = ConfigurePchSataAhci (
             SataConfig,
             AhciBarAddress
             );

  MaxSataPorts = GetPchMaxSataPortNum ();

  ///
  /// PCH BIOS Spec Section 14.1.6 Power Optimizer Configuration
  /// System BIOS must execute the following steps as part of System BIOS initialization
  /// of the PCH SATA controller on both cold boot (G3/S5) and S3/S4 resume path. Please
  /// refer to the PCH EDS, section 14.1.35.1 for the SATA initialization settings and
  /// the actual register indexes/values to be programmed.
  ///
  if (SataConfig->PwrOptEnable == TRUE) {

    //
    // When platform design has one of below condition,
    // BIOS has to set SATA PHYDPGE=0 and SQOFFIDLED=1 for specific the SATA port.
    //   - SATA hot-plug enabled port (PxCMD.HPCP = 1)
    //   - SATA external port (PxCMD.ESP = 1)
    //   - SATA slimline port with zero-power ODD (ZPODD) attached (or other AN capable ODD)
    //
    // Set PHYDPGE=0 and SQOFFIDLED=1 for selected ports.
    //
    // PCH-LP
    //   [MPHY Dynamic Power gating] SIR offset 50h[18:16] bit16=port0... bit18=port2
    //   [Slumber Squelch off] SIR offset 54h[2:0]  bit0=port0 ... bit2=port2
    //
    // PCH-H
    //   [MPHY Dynamic Power gating] SIR offset 90h[7:0] . bit0=port0...bit7=port7
    //   [Slumber Squelch off] SIR offset 80h[16:23] . bit16=port0... bit23=port7
    //
    DisableDynamicPowerGateBitMap = 0;
    for (Index = 0; Index < MaxSataPorts; Index++) {
      if (SataConfig->PortSettings[Index].Enable) {
        if (SataConfig->PortSettings[Index].External ||
            SataConfig->PortSettings[Index].HotPlug  ||
            SataConfig->PortSettings[Index].ZpOdd) {
          DisableDynamicPowerGateBitMap |= 1u << Index;
        }
      }
    }

    ///
    /// Step 1
    /// Set SATA SIR Index 50h[18:16] = 111b
    ///
    Data32Or = BIT18 | BIT17 | BIT16;
    //
    //  [MPHY Dynamic Power gating] SIR offset 50h[18:16] bit16=port0... bit18=port2
    //
    Data32Or &= (UINT32) ~(DisableDynamicPowerGateBitMap << 16);
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_50);
    MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, Data32Or);

    ///
    /// Set SATA SIR Index 70h[26:24, 15, 10:8] = 1'S, [23:18] = 010110b
    ///
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_70);
    MmioAndThenOr32 (
      PciSataRegBase + R_PCH_SATA_STRD,
      (UINT32) ~(BIT23 | BIT21 | BIT18),
      0x07008700 | (BIT22 | BIT20 | BIT19)
      );

    ///
    /// Step 2
    /// Set SATA SIR Index 54h[30, 26:24, 10:8] = 1's
    ///
    Data32Or = 0x47000700;
    //
    //  [Slumber Squelch off] SIR offset 54h[2:0]  bit0=port0 ... bit2=port2
    //
    Data32Or |= DisableDynamicPowerGateBitMap;
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_54);
    MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, Data32Or);

    ///
    /// Step 3
    /// Set SATA SIR Index 64h[31:0] = 883C9001h
    ///
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_64);
    MmioWrite32 (PciSataRegBase + R_PCH_SATA_STRD, 0x883C9001);

    ///
    /// Step 4
    /// Set SATA SIR Index 68h[15:0] = 880Ah
    ///
    Data32And = 0xFFFF0000;
    Data32Or  = 0x0000880A;
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_68);
    MmioAndThenOr32 (
      PciSataRegBase + R_PCH_SATA_STRD,
      Data32And,
      Data32Or
      );

    ///
    /// Step 5
    /// Set SATA SIR Index 60h[3] = 1b
    ///
    Data32And = 0xFFFFFFF7;
    Data32Or  = 0x00000008;
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_60);
    MmioAndThenOr32 (
      PciSataRegBase + R_PCH_SATA_STRD,
      Data32And,
      Data32Or
      );

    ///
    /// Step 6
    /// Set SATA SIR Index 60h[0] = 1b
    ///
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_60);
    Data32And = 0xFFFFFFFE;
    Data32Or  = 0x00000001;
    MmioAndThenOr32 (
      PciSataRegBase + R_PCH_SATA_STRD,
      Data32And,
      Data32Or
      );
    ///
    /// Step 5
    /// Set SATA SIR Index 60h[1] = 1b
    ///
      MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_60);
      Data32And = 0xFFFFFFFD;
      Data32Or  = 0x00000002;
      MmioAndThenOr32 (
        PciSataRegBase + R_PCH_SATA_STRD,
        Data32And,
        Data32Or
        );
  }

  ///
  /// Set SATA SIR Index 5Ch[18:16] = 111b
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_5C);
  MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, (BIT18 | BIT17 | BIT16));

  ///
  /// Set SATA SIR Index 6Ch[29:24] = 101100b,
  ///                       [21:16] = 011110b,
  ///                       [12:8]  = 10001b,
  ///                       [4:0]   = 01000b
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_6C);
  MmioAndThenOr32 (
    PciSataRegBase + R_PCH_SATA_STRD,
    (UINT32) ~(BIT28 | BIT25 | BIT24 | BIT21 | BIT16 | BIT11 | BIT10 | BIT9 | BIT4 | BIT2 | BIT1 | BIT0),
    (BIT29 | BIT27 | BIT26 | BIT20 | BIT19 | BIT18 | BIT17 | BIT12 | BIT8 | BIT3)
    );

  ///
  /// Initialize the SATA mode to be in AHCI, then check the SATA mode from the policy
  /// If RAID mode is selected and the SKU supports RAID feature, set the SATA Mode Select to 1b (RAID)
  ///
  MmioAndThenOr8 (
    PciSataRegBase + R_PCH_LP_SATA_MAP,
    (UINT8) (~B_PCH_LP_SATA_MAP_SMS_MASK),
    (UINT8) (V_PCH_LP_SATA_MAP_SMS_AHCI << N_PCH_LP_SATA_MAP_SMS_MASK)
    );

  if (SataConfig->SataMode == PchSataModeRaid) {
    if (RstMode != RstUnsupported) {
      MmioAndThenOr8 (
        PciSataRegBase + R_PCH_LP_SATA_MAP,
        (UINT8) ~(B_PCH_LP_SATA_MAP_SMS_MASK),
        (UINT8) (V_PCH_LP_SATA_MAP_SMS_RAID << N_PCH_LP_SATA_MAP_SMS_MASK)
        );
    } else {
      DEBUG ((DEBUG_ERROR, "This SKU doesn't support RAID feature. Set to AHCI mode.\n"));
    }
  }

  RstConfigurePm (PciSataRegBase);

  DEBUG ((DEBUG_INFO, "ConfigurePchLpSata() End\n"));
}

/**
  Configures Sata Controller for PCH-H

  @param[in] SataConfig                     The PCH Policy for SATA configuration
  @param[in] RstPcieStorageRemapEnabled     A Boolean to indicate if RST PCIe Storage Remapping is enabled
  @param[in] AhciBarAddress                 The Base Address for AHCI BAR

  @retval EFI_SUCCESS                       The function completed successfully
  @retval EFI_ABORTED                       SATA controller is Function Disabled, to abort initializing SATA controller.
**/
EFI_STATUS
EarlyConfigurePchHSata (
  IN  CONST PCH_SATA_CONFIG                   *SataConfig,
  IN BOOLEAN                                  RstPcieStorageRemapEnabled,
  IN UINT32                                   AhciBarAddress
  )
{
  EFI_STATUS              Status;
  UINT8                   SataGcReg;
  UINTN                   PciSataRegBase;
  UINT16                  LpcDeviceId;
  UINT32                  Data32And;
  UINT32                  Data32Or;

  DEBUG ((DEBUG_INFO, "EarlyConfigurePchHSata() Start\n"));

  PciSataRegBase    = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_SATA, PCI_FUNCTION_NUMBER_PCH_SATA);
  LpcDeviceId       = GetLpcDid ();
  Status            = EFI_SUCCESS;
  #ifndef MINTREE_FLAG
  ///
  /// If Sata is disabled or no lanes assigned to SATA when in AHCI mode
  /// perform the disabling steps to function disable the SATA Controller
  ///
  if ((SataConfig->Enable == FALSE) || ((!SataLaneExist ()) && (SataConfig->SataMode == PchSataModeAhci))) {
    DisablePchHSataController (AhciBarAddress);
    return EFI_ABORTED;
  }
  #endif //MINTREE_FLAG
  ///
  /// PCH BIOS Spec section 14.1.6 Additional Programming Requirements during
  /// SATA Initialization
  /// Step 1
  /// System BIOS must set SATA SIR Index 98h[8:0] = 183h
  /// as part of the chipset initialization prior to SATA configuration.
  /// These bits should be restored while resuming from a S3 sleep state.
  ///
  Data32And = (UINT32) ~(BIT8 | BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0);
  Data32Or  = 0x183;
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_98);
  MmioAndThenOr32 (PciSataRegBase + R_PCH_SATA_STRD, Data32And, Data32Or);

  ///
  /// Step 2
  /// Set SATA SIR Index A4h[6] = 1b
  /// These bits should be restored while resuming from a S3 sleep state
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_A4);
  MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, BIT6);

  ///
  /// Step 3
  /// System BIOS must program SATA Hsio table as stated in Table 7-7 to 7-8 BEFORE the SATA
  /// ports are enabled.
  ///

  ///
  /// PCH BIOS Spec section 14.1.7 Additional Programming Requirements during
  /// SATA Initialization
  /// Step 4
  /// Set SATA SIR Index 9Ch[22] = 1b for desktop and mobile platform only
  /// (Server may leave as default)
  ///
  if (IS_PCH_LPC_DEVICE_ID_DESKTOP (LpcDeviceId) ||
      IS_PCH_LPC_DEVICE_ID_MOBILE (LpcDeviceId)) {
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_9C);
    MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, BIT22);
  }

  ///
  /// Step 4
  /// Program SATA SIR Index 9Ch[29,23,20,19,18] to all 1b
  /// Program SATA SIR Index 9Ch[12:7] = 04h
  /// Program SATA SIR Index 9Ch[6:5] to 01b
  /// Program SATA SIR Index 9Ch[3:2] to 01b
  /// Note: If [3:2] value recommendation get changed, please refer to definition if Bit 1:0 and program per table accordingly
  ///
  Data32And = (UINT32) (~(BIT12 | BIT11 | BIT10 | BIT9 | BIT8 | BIT7 | BIT6 | BIT5 | BIT3 | BIT2));
  Data32Or  = (UINT32) (BIT29 | BIT23 | BIT20 | BIT19 | BIT18 | BIT9 | BIT5 | BIT2);
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_9C);
  MmioAndThenOr32 (
    PciSataRegBase + R_PCH_SATA_STRD,
    Data32And,
    Data32Or
    );

  ///
  /// Step 5
  /// Program SATA PCI offset 9Ch[5] to 1b
  /// Note: Bits 7:0 are RWO, perform byte write here, program the 9Ch[31] to 1b later in PchOnEndOfDxe ()
  ///
  SataGcReg = MmioRead8 (PciSataRegBase + R_PCH_SATA_SATAGC);
  SataGcReg |= BIT5;

  ConfigureSataControllerDeviceId (&SataGcReg, SataConfig);

  ///
  /// If RstPcieStorageRemapEnabled is TRUE, program Sata PCI offset 9Ch, bit[4:3] and bit[2:0] to [00'b] and [110'b]
  /// else, program Sata PCI offset 9Ch, bit[4:3] and bit[2:0] to [10'b] and [000'b], and also disable Rst remap decoding
  ///
  if (RstPcieStorageRemapEnabled) {
    SataGcReg |= V_PCH_SATA_SATAGC_ASSEL_512K;
    SataGcReg &= ~(B_PCH_SATA_SATAGC_MSS);
  } else {
    SataGcReg &= ~B_PCH_SATA_SATAGC_ASSEL;
    SataGcReg |= V_PCH_SATA_SATAGC_MSS_8K << N_PCH_SATA_SATAGC_MSS;
    DisableRstRemapDecoding (AhciBarAddress);
  }

  ///
  /// Unconditional write is necessary to lock the register
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SATAGC, SataGcReg);

  ///
  /// Program PCS "Port X Enabled", SATA PCI offset 94h[7:0] to all 1b.
  ///
  MmioOr16 (PciSataRegBase + R_PCH_H_SATA_PCS, (UINT16) B_PCH_H_SATA_PCS_PXE_MASK);

  ///
  /// PCH BIOS Spec section 19.10
  /// Step 4.2
  /// After configuring Port and Control Status (PCS) Register Port x Enabled (PxE) bits accordingly,
  /// wait 1.4 micro second
  ///
  MicroSecondDelay (0x02);

  DEBUG ((DEBUG_INFO, "EarlyConfigurePchHSata() End\n"));

  return Status;
}

/**
  Additional Sata configuration for PCH-H

  @param[in]      SataConfig                The PCH Policy for SATA configuration
  @param[in] AhciBarAddress                 The Base Address for AHCI BAR
**/
VOID
ConfigurePchHSata (
  IN CONST PCH_SATA_CONFIG                    *SataConfig,
  IN UINT32                                   AhciBarAddress
  )
{
  EFI_STATUS              Status;
  UINTN                   PciSataRegBase;
  RST_MODE                RstMode;
  UINTN                   MaxSataPorts;
  UINT32                  DisableDynamicPowerGateBitMap;
  UINT8                   Index;
  UINT32                  Data32And;
  UINT32                  Data32Or;

  DEBUG ((DEBUG_INFO, "ConfigurePchHSata() Start\n"));

  PciSataRegBase    = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_SATA, PCI_FUNCTION_NUMBER_PCH_SATA);
  RstMode           = GetSupportedRstMode ();

  ///
  /// Configure AHCI
  ///
  Status = ConfigurePchSataAhci (
             SataConfig,
             AhciBarAddress
             );

  MaxSataPorts = GetPchMaxSataPortNum ();

  ///
  /// PCH BIOS Spec Section 14.1.6 Power Optimizer Configuration
  /// System BIOS must execute the following steps as part of System BIOS initialization
  /// of the PCH SATA controller on both cold boot (G3/S5) and S3/S4 resume path. Please
  /// refer to the PCH EDS, section 14.1.35.1 for the SATA initialization settings and
  /// the actual register indexes/values to be programmed.
  ///
  if (SataConfig->PwrOptEnable == TRUE) {

    //
    // When platform design has one of below condition,
    // BIOS has to set SATA PHYDPGE=0 and SQOFFIDLED=1 for specific the SATA port.
    //   - SATA hot-plug enabled port (PxCMD.HPCP = 1)
    //   - SATA external port (PxCMD.ESP = 1)
    //   - SATA slimline port with zero-power ODD (ZPODD) attached (or other AN capable ODD)
    //
    // Set PHYDPGE=0 and SQOFFIDLED=1 for selected ports.
    //
    // PCH-LP
    //   [MPHY Dynamic Power gating] SIR offset 50h[18:16] bit16=port0... bit18=port2
    //   [Slumber Squelch off] SIR offset 54h[2:0]  bit0=port0 ... bit2=port2
    //
    // PCH-H
    //   [MPHY Dynamic Power gating] SIR offset 90h[7:0] . bit0=port0...bit7=port7
    //   [Slumber Squelch off] SIR offset 80h[16:23] . bit16=port0... bit23=port7
    //
    DisableDynamicPowerGateBitMap = 0;
    for (Index = 0; Index < MaxSataPorts; Index++) {
      if (SataConfig->PortSettings[Index].Enable) {
        if (SataConfig->PortSettings[Index].External ||
            SataConfig->PortSettings[Index].HotPlug  ||
            SataConfig->PortSettings[Index].ZpOdd) {
          DisableDynamicPowerGateBitMap |= 1u << Index;
        }
      }
    }

    ///
    /// Step 1
    /// Set SATA SIR Index 90h[7:0] = 1'S
    ///
    Data32Or = 0xFF;
    //
    //  [MPHY Dynamic Power gating] SIR offset 90h[7:0] . bit0=port0...bit7=port7
    //
    Data32Or &= (UINT32) ~DisableDynamicPowerGateBitMap;
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_90);
    MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, Data32Or);

    //
    //  [Slumber Squelch off] SIR offset 80h[16:23] . bit16=port0... bit23=port7
    //
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_80);
    MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, (DisableDynamicPowerGateBitMap << 16));

    ///
    /// Set SATA SIR Index 8Ch[23:16, 7:0] = 1'S
    ///
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_8C);
    MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, 0x00FF00FF);

    ///
    /// Set SATA SIR Index A0h[15] = 1b, [23:18] = 010110b
    ///
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_A0);
    MmioAndThenOr32 (
      PciSataRegBase + R_PCH_SATA_STRD,
      (UINT32) ~(BIT23 | BIT21 | BIT18),
      BIT22 | BIT20 | BIT19 | BIT15
      );

    ///
    /// Step 2
    /// Set SATA SIR Index 84h[23:16, 7:0] = 1'S
    ///
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_84);
    MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, 0x00FF00FF);

    ///
    /// Set SATA SIR Index A4h[14] = 1b
    ///
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_A4);
    MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, BIT14);

    ///
    /// Step 3
    /// Set SATA SIR Index CCh[31:0] = 883C9001h
    ///
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_CC);
    MmioWrite32 (PciSataRegBase + R_PCH_SATA_STRD, 0x883C9001);

    ///
    /// Step 4
    /// Set SATA SIR Index D0h[15:0] = 880Ah
    ///
    Data32And = 0xFFFF0000;
    Data32Or  = 0x0000880A;
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_D0);
    MmioAndThenOr32 (
      PciSataRegBase + R_PCH_SATA_STRD,
      Data32And,
      Data32Or
      );

    ///
    /// Step 5
    /// Set SATA SIR Index C8h[3] = 1b
    ///
    Data32And = 0xFFFFFFF7;
    Data32Or  = 0x00000008;
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_C8);
    MmioAndThenOr32 (
      PciSataRegBase + R_PCH_SATA_STRD,
      Data32And,
      Data32Or
      );

    ///
    /// Step 6
    /// Set SATA SIR Index C8h[0] = 1b
    ///
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_C8);
    Data32And = 0xFFFFFFFE;
    Data32Or  = 0x00000001;
    MmioAndThenOr32 (
      PciSataRegBase + R_PCH_SATA_STRD,
      Data32And,
      Data32Or
      );
  ///
  /// Step 5
  /// Set SATA SIR Index C8h[1] = 1b
  ///
    MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_C8);
    Data32And = 0xFFFFFFFD;
    Data32Or  = 0x00000002;
    MmioAndThenOr32 (
      PciSataRegBase + R_PCH_SATA_STRD,
      Data32And,
      Data32Or
      );
  }

  ///
  /// Set SATA SIR Index A8h[18:16] = 111b
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_A8);
  MmioOr32 (PciSataRegBase + R_PCH_SATA_STRD, (BIT18 | BIT17 | BIT16));

  ///
  /// Set SATA SIR Index D4h[29:24] = 101100b,
  ///                       [21:16] = 011110b,
  ///                       [12:8]  = 10001b,
  ///                       [4:0]   = 01000b
  ///
  MmioWrite8 (PciSataRegBase + R_PCH_SATA_SIRI, R_PCH_SATA_SIR_D4);
  MmioAndThenOr32 (
    PciSataRegBase + R_PCH_SATA_STRD,
    (UINT32) ~(BIT28 | BIT25 | BIT24 | BIT21 | BIT16 | BIT11 | BIT10 | BIT9 | BIT4 | BIT2 | BIT1 | BIT0),
    BIT29 | BIT27 | BIT26 | BIT20 | BIT19 | BIT18 | BIT17 | BIT12 | BIT8 | BIT3
    );

  ///
  /// Initialize the SATA mode to be in AHCI, then check the SATA mode from the policy
  /// If RAID mode is selected and the SKU supports RAID feature, set the SATA Mode Select to 1b (RAID)
  ///
  MmioAnd8 (PciSataRegBase + R_PCH_SATA_SATAGC + 2,(UINT8) ~(BIT0));

  if (SataConfig->SataMode == PchSataModeRaid) {
    if (RstMode != RstUnsupported) {
      MmioAndThenOr8 (
        PciSataRegBase + R_PCH_SATA_SATAGC + 2,
        (UINT8) ~(BIT0),
        (UINT8) (V_PCH_H_SATA_SATAGC_SMS_RAID)
        );
    } else {
      DEBUG ((DEBUG_ERROR, "This SKU doesn't support RAID feature. Set to AHCI mode.\n"));
    }
  }

  RstConfigurePm (PciSataRegBase);

  DEBUG ((DEBUG_INFO, "ConfigurePchHSata() End\n"));
}
