/** @file
  SA PCIe Initialization Private Low Level functions for Skylake DT/HALO

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#include "SaPegLowLevel.h"
#include <Private/Library/SaPcieDmiLib.h>
#include <Library/PchPcrLib.h>

/**
  Determines if the PEG root ports are capable of PCIe 3.0 speed

  @param[in]  This                        - Low level function table

  @retval TRUE - PEG Root Ports are PCIe 3.0 capable
  @retval FALSE - otherwise
**/
BOOLEAN
EFIAPI
SklPegIsGen3Capable (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This
  )
{
  BOOLEAN   Gen3Capable;

  Gen3Capable = TRUE;
  if (MmioRead32 (MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN) + R_SA_MC_CAPID0_B) & BIT20) {
    DEBUG ((DEBUG_INFO, "PEG Gen3 Fused off\n"));
    Gen3Capable = FALSE;
  }
  return Gen3Capable;
}

/**
  Performs AFE and RP programming that needs to be done prior to enabling the
  PCIe link and allowing it to train to active state for the first time.

  @param[in]  This                        - Low level function table
  @param[in]  PciePorts                   - PCIe Root Ports
  @param[in]  PciePortsLength             - Length of the PciePorts array
**/
VOID
EFIAPI
SklPegPreDetectionProgramming (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePorts,
  IN  UINT8                             PciePortsLength
  )
{
  SA_PCIE_PRIVATE_FUNCTION_CALLS  *PciePrivate;
  PCIE_PEI_PREMEM_CONFIG          *PciePeiPreMemConfig;
  UINTN                           PegBaseAddress;
  UINT32                          Data32;
  UINT32                          Data32And;
  UINT32                          Data32Or;
  UINT32                          Bundle;
  UINT8                           Index;
  UINT8                           PegBus;
  UINT8                           PegDev;
  UINT8                           PegFunc;

  PciePrivate         = (SA_PCIE_PRIVATE_FUNCTION_CALLS*) This->PrivateData;
  PciePeiPreMemConfig          = PciePrivate->PciePeiPreMemConfig;
  PegBaseAddress      = MmPciBase (SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, SA_PEG10_FUN_NUM);
  ///
  ///
  ///
  /// Set PCIE_CR_REUT_OVR_CTL_0_1_0_MMR.GRCLKGTDIS [28] to 1 (for PCIE Margin Test, Default is kept 0)
  ///
  Data32And = (UINT32) ~BIT28;
  Data32Or  = 0;
  MmioAndThenOr32 (PegBaseAddress + R_SA_PEG_REUT_OVR_CTL_OFFSET, Data32And, Data32Or);

  ///
  ///
  ///
  /// DCBLNC = 0
  ///
  Data32And = (UINT32) ~(BIT3 | BIT2);
  Data32Or  = 0;
  for (Bundle = 0; Bundle < SA_PEG_MAX_BUNDLE; Bundle++) {
    MmioAndThenOr32 (PegBaseAddress + R_SA_PEG_G3CTL0_OFFSET + (Bundle * BUNDLE_STEP), Data32And, Data32Or);
  }

  for (Index = 0; Index < PciePortsLength; Index++) {
    PegBus         = PciePorts[Index].Bus;
    PegDev         = PciePorts[Index].Device;
    PegFunc        = PciePorts[Index].Function;
    PegBaseAddress = PciePorts[Index].ConfigSpaceBase;

    ///
    ///
    MmioOr32 (PegBaseAddress + R_SA_PEG_LTSSMC_OFFSET, (UINT32) (BIT4 | BIT3 | BIT2 | BIT1 | BIT0));

    ///
    ///
    ///
    /// Program Read-Only Write-Once Registers
    ///   R 308h [31:0]
    ///   R 314h [31:0]
    ///   R 32Ch [31:0]
    ///   R 330h [31:0]
    ///
    Data32 = MmioRead32 (PegBaseAddress + R_SA_PEG_VC0PRCA_OFFSET);
    MmioWrite32 (PegBaseAddress + R_SA_PEG_VC0PRCA_OFFSET, Data32);
    Data32 = MmioRead32 (PegBaseAddress + R_SA_PEG_VC0NPRCA_OFFSET);
    MmioWrite32 (PegBaseAddress + R_SA_PEG_VC0NPRCA_OFFSET, Data32);
    Data32 = MmioRead32 (PegBaseAddress + R_SA_PEG_VC1PRCA_OFFSET);
    MmioWrite32 (PegBaseAddress + R_SA_PEG_VC1PRCA_OFFSET, Data32);
    Data32 = MmioRead32 (PegBaseAddress + R_SA_PEG_VC1NPRCA_OFFSET);
    MmioWrite32 (PegBaseAddress + R_SA_PEG_VC1NPRCA_OFFSET, Data32);

    ///
    ///
    ///
    /// Program Read-Write Register
    ///   R CD4h [30:24]
    ///
    Data32And = (UINT32) ~(BIT30 | BIT29 | BIT28 | BIT27 | BIT26 | BIT25 | BIT24);
    Data32Or  = 0x40 << 24;
    MmioAndThenOr32 (PegBaseAddress + R_SA_PEG_G3PLINIT_OFFSET, Data32And, Data32Or);

    ///
    /// Program Peg PCI Register 208h [31:30] to 01
    ///
    MmioAndThenOr32 (PegBaseAddress + R_SA_PEG_PEGCC_OFFSET,  (UINT32) ~ (BIT31 | BIT30),(UINT32) (BIT30));
  }

  ///
  /// Program PEG Recipe
  ///
  PciePrivate->PcieDmiRecipe (
                 PciePrivate->DmiBar,
                 PciePrivate->MchBar,
                 &(PciePeiPreMemConfig->PegGen3RxCtlePeaking[0]),
                 SA_PEG_MAX_BUNDLE,
                 (UINT8) PciePeiPreMemConfig->PegGen3RxCtleOverride,
                 FALSE
                 );
}

/**
  Configure PCIe Max Speed and Width

  @param[in]  This                        - Low level function table
  @param[in]  PciePorts                   - PCIe Root Ports
  @param[in]  PciePortsLength             - Length of the PciePorts array
  @param[in]  Gen3Capable                 - PEG is Gen3 capable
**/
VOID
EFIAPI
SklConfigureMaxSpeedWidth (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePorts,
  IN  UINT8                             PciePortsLength,
  IN  BOOLEAN                           Gen3Capable
  )
{
  PCIE_PEI_PREMEM_CONFIG  *PciePeiPreMemConfig;
  UINTN                   PegBaseAddress;
  UINT16                  LinkSpeed;
  UINT8                   Index;
  UINT8                   PegPortMaxLinkSpeed;
  UINT8                   PegBus;
  UINT8                   PegDev;
  UINT8                   PegFunc;
  UINT8                   MaxLinkWidth;

  PciePeiPreMemConfig = ((SA_PCIE_PRIVATE_FUNCTION_CALLS*) This->PrivateData)->PciePeiPreMemConfig;
  for (Index = 0; Index < PciePortsLength; Index++) {
    PegBus        = PciePorts[Index].Bus;
    PegDev        = PciePorts[Index].Device;
    PegFunc       = PciePorts[Index].Function;
    MaxLinkWidth  = PciePorts[Index].MaxPortWidth;

    ///
    /// Check if this port exists
    ///
    PegBaseAddress = PciePorts[Index].ConfigSpaceBase;
    if (MmioRead16 (PegBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
      continue;
    }

    ///
    /// PCIe Port Speed: 0 = Auto, 1 = Gen1, 2 = Gen2, 3 = Gen3
    ///
    PegPortMaxLinkSpeed = SaPolicyGetPegMaxLinkSpeed (PegFunc, PciePeiPreMemConfig);

    if (PegPortMaxLinkSpeed == PEG_AUTO) {
      LinkSpeed = (UINT16) (MmioRead32 (PegBaseAddress + R_SA_PEG_LCAP_OFFSET) & 0x0F);
      DEBUG((DEBUG_INFO, "PEG %x:%x:%x Speed: Auto %x\n", PegBus, PegDev, PegFunc, LinkSpeed));
    } else {
      LinkSpeed = PegPortMaxLinkSpeed;
      DEBUG ((DEBUG_INFO, "PEG %x:%x:%x Speed: %x\n", PegBus, PegDev, PegFunc, LinkSpeed));
    }
    ///
    /// If Gen3 is fused off, limit is Gen2
    ///
    if (Gen3Capable == FALSE) {
      if (LinkSpeed > 2) {
        LinkSpeed = 2;
      }
    }
    ///
    /// Set the requested speed in Max Link Speed in LCAP[3:0] and Target Link Speed in LCTL2[3:0].
    /// Update LCAP.MLW in the same write as it's a Write-Once field. MLW field is locked here.
    ///
    DEBUG ((DEBUG_INFO, "PEG%x%x (%x:%x:%x) - Max Link Speed = Gen%d - Max Link Width = %d\n", PegDev, PegFunc, PegBus, PegDev, PegFunc, LinkSpeed, MaxLinkWidth));
    MmioAndThenOr32 (PegBaseAddress + R_SA_PEG_LCAP_OFFSET, 0xFFFFFC00, ((UINT32) MaxLinkWidth << 4) | LinkSpeed);
    MmioAndThenOr16 (PegBaseAddress + R_SA_PEG_LCTL2_OFFSET, (UINT16) ~(0x0F), LinkSpeed);
  }
}

/**
  Enable RxCEM Loopback (LPBK) Mode

  @param[in]  This                        - Low level function table
  @param[in]  RxCemLoopbackLane           - Lane to use for RxCEM Testing
**/
VOID
EFIAPI
SklEnableRxCemLoopbackMode (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  UINT8                             RxCEMLoopbackLane
  )
{
  PCIE_PEI_PREMEM_CONFIG  *PciePeiPreMemConfig;
  UINTN   Peg0BaseAddress;
  UINT8        PegFunc;
  UINT8   Lane;
  UINT32       Data32Or;
  UINT32       Data32And;

  Peg0BaseAddress = MmPciBase (SA_PEG_BUS_NUM, SA_PEG10_DEV_NUM, SA_PEG10_FUN_NUM);
  PciePeiPreMemConfig = ((SA_PCIE_PRIVATE_FUNCTION_CALLS*) This->PrivateData)->PciePeiPreMemConfig;

  MmioAndThenOr32 (Peg0BaseAddress + R_SA_PEG_PEGTST_OFFSET, (UINT32) ~(BIT19|BIT18|BIT17|BIT16), (RxCEMLoopbackLane & 0xF) << 16);
  for (Lane = 0; Lane < SA_PEG_MAX_LANE; Lane++) {
    if (Lane == RxCEMLoopbackLane) {
      MmioAnd32 (Peg0BaseAddress + R_SA_PEG_AFELN0CFG0_OFFSET + (LANE_STEP * Lane), (UINT32) ~BIT9);
    } else {
      MmioOr32 (Peg0BaseAddress + R_SA_PEG_AFELN0CFG0_OFFSET + (LANE_STEP * Lane), BIT9);
    }
  }
  ///
  /// Configure Protocol Awareness for testing according to policy
  ///
  if (PciePeiPreMemConfig->PegRxCemNonProtocolAwareness == 1) {
    Data32And = (UINT32) ~(0x7 << 8);
    Data32Or = 0x5 << 8;
    for (PegFunc = 0; PegFunc < SA_PEG_MAX_FUN; PegFunc++) {
      MmioAndThenOr32 (MmPciBase (SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, PegFunc) + R_SA_PEG_REUT_PH_CTR_OFFSET, Data32And, Data32Or);
    }
  }
}

/**
  Disable Spread Spectrum Clocking

  @param[in]  This                        - Low level function table
**/
VOID
EFIAPI
SklDisableSpreadSpectrumClocking (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This
  )
{
  ///
  /// Disable spread spectrum clocking
  ///
  PchPcrAndThenOr32 (
    PID_MODPHY1,
    R_PCH_HSIO_PLL_SSC_DWORD2,
    (UINT32) ~B_PCH_HSIO_PLL_SSC_DWORD2_SSCSEN,
    0
    );
  DEBUG ((DEBUG_INFO, "Disable PEG Spread Spectrum Clocking\n"));
}


/**
  Clear DEFER_OC and allow the PCIe controllers to begin training

  @param[in]  This                        - Low level function table
**/
VOID
EFIAPI
SklClearDeferOc (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This
  )
{
  UINTN                   Peg0BaseAddress;
  UINTN                   Peg1BaseAddress;
  UINTN                   Peg2BaseAddress;
  PCIE_PEI_PREMEM_CONFIG  *PciePeiPreMemConfig;

  PciePeiPreMemConfig = ((SA_PCIE_PRIVATE_FUNCTION_CALLS*) This->PrivateData)->PciePeiPreMemConfig;

  Peg0BaseAddress = MmPciBase (SA_PEG_BUS_NUM, SA_PEG10_DEV_NUM, SA_PEG10_FUN_NUM);
  Peg1BaseAddress = MmPciBase (SA_PEG_BUS_NUM, SA_PEG11_DEV_NUM, SA_PEG11_FUN_NUM);
  Peg2BaseAddress = MmPciBase (SA_PEG_BUS_NUM, SA_PEG12_DEV_NUM, SA_PEG12_FUN_NUM);

  if (!SaPolicyForceDisablesPort(SA_PEG10_FUN_NUM, PciePeiPreMemConfig)) {
    MmioAnd32 (Peg0BaseAddress + R_SA_PEG_AFE_PWRON_OFFSET, (UINT32) ~BIT16);
  }
  if (!SaPolicyForceDisablesPort(SA_PEG11_FUN_NUM, PciePeiPreMemConfig)) {
    MmioAnd32 (Peg1BaseAddress + R_SA_PEG_AFE_PWRON_OFFSET, (UINT32) ~BIT16);
  }
  if (!SaPolicyForceDisablesPort(SA_PEG12_FUN_NUM, PciePeiPreMemConfig)) {
    MmioAnd32 (Peg2BaseAddress + R_SA_PEG_AFE_PWRON_OFFSET, (UINT32) ~BIT16);
  }
}

/**
  Set DisableAutoSpeedUp bit

  @param[in]  This                        - Low level function table
  @param[in]  PciePort                    - PCIe Root Port
  @param[in]  DisableAutoSpeedUp          - New value for DisableAutoSpeedUp
**/
VOID
EFIAPI
SklSetDisableAutoSpeedUp (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort,
  IN  BOOLEAN                           DisableAutoSpeedUp
  )
{
  if (DisableAutoSpeedUp) {
    MmioOr32 (PciePort->ConfigSpaceBase + R_SA_PEG_CFG5_OFFSET, BIT9);
  } else {
    MmioAnd32 (PciePort->ConfigSpaceBase + R_SA_PEG_CFG5_OFFSET, (UINT32) ~(BIT9));
  }
}

/**
  Performs any additional equalization programming that needs to be done after
  initial link training and endpoint detection

  @param[in]  This                        - Low level function table
  @param[in]  PciePorts                   - PCIe Root Ports to program Phase2 for
  @param[in]  PciePortsLength             - Length of the PciePorts array
**/
VOID
EFIAPI
SklPostDetectionEqProgramming (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePorts,
  IN  UINT8                             PciePortsLength
  )
{
  SA_PCIE_PRIVATE_FUNCTION_CALLS  *PciePrivate;
  PCIE_PEI_PREMEM_CONFIG          *PciePeiPreMemConfig;
  EFI_STATUS                      Status;
  UINTN                           Peg0BaseAddress;
  BOOLEAN                         AnyGen3Link;
  BOOLEAN                         AnyPh3Hijack;
  UINT8                           LaneReversal;
  UINT8                           FullSwing;
  UINT8                           PreCursor;
  UINT8                           Cursor;
  UINT8                           PostCursor;
  UINT8                           PortIndex;
  UINT8                           Lane;
  UINT8                           PresenceDetect;
  UINT8                           EqMethod;

  PciePrivate         = (SA_PCIE_PRIVATE_FUNCTION_CALLS*) This->PrivateData;
  PciePeiPreMemConfig          = PciePrivate->PciePeiPreMemConfig;
  Peg0BaseAddress     = MmPciBase (SA_PEG_BUS_NUM, SA_PEG10_DEV_NUM, SA_PEG10_FUN_NUM);
  LaneReversal        = (MmioRead32 (Peg0BaseAddress + R_SA_PEG_PEGTST_OFFSET) >> 20) & 0x1;
  AnyGen3Link         = FALSE;
  AnyPh3Hijack        = FALSE;
  PresenceDetect      = 0;
  FullSwing           = 0;
  for (PortIndex = 0; PortIndex < PciePortsLength; PortIndex++) {
    if (PciePorts[PortIndex].SwEqData.MaxCapableSpeed >= 3) {
      AnyGen3Link = TRUE;
    }
    if (PciePorts[PortIndex].EndpointPresent) {
      PresenceDetect |= (0x1 << PciePorts[PortIndex].Function);
    }
  }

  ///
  ///
  for (PortIndex = 0; PortIndex < PciePortsLength; PortIndex++) {
    EqMethod = SaPolicyGetEqPhase3Method (PciePorts[PortIndex].Function, PciePeiPreMemConfig);
    if (SaPolicySwEqEnabledOnPort (PciePorts[PortIndex].Function, PciePeiPreMemConfig) ||
       (EqMethod == PH3_METHOD_STATIC)) {
      AnyPh3Hijack = TRUE;
      MmioOr32 (PciePorts[PortIndex].ConfigSpaceBase + R_SA_PEG_EQCFG_OFFSET, BIT1);
      ///
      /// Clear phase2 bypass if phase2 is enabled
      ///
      if (SaPolicyGetEqPhase2Enable (PciePorts[PortIndex].Function, PciePeiPreMemConfig)) {
        Status = This->SetPhase2Bypass (This, &PciePorts[PortIndex], 1, FALSE);
        ASSERT_EFI_ERROR (Status);
      }
    }
  }

  ///
  /// If any Gen3 device, setup equalization values and retrain link
  ///
  if (AnyGen3Link && AnyPh3Hijack) {
    ///
    /// Program presets based upon endpoint fullswing value
    ///
    for (Lane = 0; Lane < SA_PEG_MAX_LANE; Lane++) {
      switch (Lane) {
        case  0:
          PciePrivate->GetLinkPartnerFullSwing (This, Lane, &FullSwing);
          break;
        case  8:
          if ((PresenceDetect & BIT1) == BIT1) {
            PciePrivate->GetLinkPartnerFullSwing (This, Lane, &FullSwing);
          }
          break;
        case 12:
          if ((PresenceDetect & BIT2) == BIT2) {
            PciePrivate->GetLinkPartnerFullSwing (This, Lane, &FullSwing);
          }
          break;
        default:
          break;
      }
      GetCoefficientsFromPreset (
        PciePeiPreMemConfig->PegGen3EndPointPreset[ReverseLane (Lane, LaneReversal) ],
        FullSwing,
        &PreCursor,
        &Cursor,
        &PostCursor
        );
      PciePrivate->SetPartnerTxCoefficients (This, Lane, &PreCursor, &Cursor, &PostCursor);
    }

    ///
    /// Redo EQ
    ///
    for (PortIndex = 0; PortIndex < PciePortsLength; PortIndex++) {
      if (PciePorts[PortIndex].EndpointPresent) {
        ///
        /// Go to Gen1
        ///
        MmioAndThenOr16 (PciePorts[PortIndex].ConfigSpaceBase + R_SA_PEG_LCTL2_OFFSET, (UINT16) ~(0x0F), 1);
        This->RetrainLink (This, &(PciePorts[PortIndex]));
      }
    }
    for (PortIndex = 0; PortIndex < PciePortsLength; PortIndex++) {
      if (PciePorts[PortIndex].EndpointPresent) {
        This->WaitForL0 (This, &(PciePorts[PortIndex]));
      }
    }
    for (PortIndex = 0; PortIndex < PciePortsLength; PortIndex++) {
      if (PciePorts[PortIndex].EndpointPresent) {
        ///
        /// Go to Gen3
        ///
        MmioOr32 (PciePorts[PortIndex].ConfigSpaceBase + R_SA_PEG_LCTL3_OFFSET, BIT0);  ///< DOEQ
        MmioAndThenOr16 (PciePorts[PortIndex].ConfigSpaceBase + R_SA_PEG_LCTL2_OFFSET, (UINT16) ~(0x0F), 3);
        This->RetrainLink (This, &(PciePorts[PortIndex]));
      }
    }
    for (PortIndex = 0; PortIndex < PciePortsLength; PortIndex++) {
      if (PciePorts[PortIndex].EndpointPresent) {
        This->WaitForL0 (This, &(PciePorts[PortIndex]));
      }
    }
  }
}

/**
 This function programs Equalization Phase 2/3 Bypass

  @param[in]  This                        - Low level function table
  @param[in]  PciePorts                   - PCIe Root Ports to sampler calibrate
  @param[in]  PciePortsLength             - Length of the PciePorts array
**/
VOID
EFIAPI
SklEqPh2Ph3BypassProgramming (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePorts,
  IN  UINT8                             PciePortsLength
  )
{
  SA_PCIE_PRIVATE_FUNCTION_CALLS  *PciePrivate;
  PCIE_PEI_PREMEM_CONFIG          *PciePeiPreMemConfig;
  EFI_STATUS                      Status;
  UINT8                           PortIndex;
  UINT8                           PegFunc;
  BOOLEAN                         RedoEqNeeded[SA_PEG_MAX_FUN];

  PciePrivate   = (SA_PCIE_PRIVATE_FUNCTION_CALLS*) This->PrivateData;
  PciePeiPreMemConfig    = PciePrivate->PciePeiPreMemConfig;
  for (PortIndex = 0; PortIndex < SA_PEG_MAX_FUN; PortIndex++) {
      RedoEqNeeded[PortIndex] = FALSE;
  }

  ///
  /// After last equalization, set PH3 bypass if needed
  ///
  for (PortIndex = 0; PortIndex < PciePortsLength; PortIndex++) {
    PegFunc = PciePorts[PortIndex].Function;
    if (SaPolicyGetPegMaxLinkSpeed (PegFunc, PciePeiPreMemConfig) >= PEG_GEN3 ||
        SaPolicyGetPegMaxLinkSpeed (PegFunc, PciePeiPreMemConfig) == 0) {
      if (SaPolicySwEqEnabledOnPort (PegFunc, PciePeiPreMemConfig) ||
          (SaPolicyGetEqPhase3Method (PegFunc, PciePeiPreMemConfig) == PH3_METHOD_DISABLED)) {
        RedoEqNeeded[PortIndex] = TRUE;
        MmioOr32 (PciePorts[PortIndex].ConfigSpaceBase + R_SA_PEG_EQCFG_OFFSET, BIT14);
      }
    }
  }
  ///
  /// Set Ph2 Bypass if enabled by SA policy
  ///
  for (PortIndex = 0; PortIndex < PciePortsLength; PortIndex++) {
    PegFunc = PciePorts[PortIndex].Function;
    if (SaPolicyGetPegMaxLinkSpeed (PegFunc, PciePeiPreMemConfig) >= PEG_GEN3 ||
        SaPolicyGetPegMaxLinkSpeed (PegFunc, PciePeiPreMemConfig) == 0) {
      if (SaPolicyGetEqPhase2Enable (PegFunc, PciePeiPreMemConfig)) {
        RedoEqNeeded[PortIndex] = TRUE;
        Status = This->SetPhase2Bypass (This, &PciePorts[PortIndex], 1, FALSE);
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_WARN, "Error clearing Phase2 bypass!\n"));
        }
      } else {
        Status = This->SetPhase2Bypass (This, &PciePorts[PortIndex], 1, TRUE);
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_WARN, "Error setting Phase2 bypass!\n"));
        }
      }
    }
  }
  ///
  /// Redo EQ
  ///
  for (PortIndex = 0; PortIndex < PciePortsLength; PortIndex++) {
    if (PciePorts[PortIndex].EndpointPresent && RedoEqNeeded[PortIndex]) {
      ///
      /// Go to Gen1
      ///
      MmioAndThenOr16 (PciePorts[PortIndex].ConfigSpaceBase + R_SA_PEG_LCTL2_OFFSET, (UINT16) ~(0x0F), 1);
      This->RetrainLink (This, &(PciePorts[PortIndex]));
    }
  }
  for (PortIndex = 0; PortIndex < PciePortsLength; PortIndex++) {
    if (PciePorts[PortIndex].EndpointPresent && RedoEqNeeded[PortIndex]) {
      This->WaitForL0(This, &(PciePorts[PortIndex]));
    }
  }
  for (PortIndex = 0; PortIndex < PciePortsLength; PortIndex++) {
    if (PciePorts[PortIndex].EndpointPresent && RedoEqNeeded[PortIndex]) {
      ///
      /// Go to Gen3
      ///
      MmioOr32 (PciePorts[PortIndex].ConfigSpaceBase + R_SA_PEG_LCTL3_OFFSET, BIT0);  ///< DOEQ
      MmioAndThenOr16 (PciePorts[PortIndex].ConfigSpaceBase + R_SA_PEG_LCTL2_OFFSET, (UINT16) ~(0x0F), 3);
      This->RetrainLink (This, &(PciePorts[PortIndex]));
    }
  }
  for (PortIndex = 0; PortIndex < PciePortsLength; PortIndex++) {
    if (PciePorts[PortIndex].EndpointPresent && RedoEqNeeded[PortIndex]) {
      This->WaitForL0 (This, &(PciePorts[PortIndex]));
    }
  }
  ///
  /// Make sure the link is operating at the max speed and width, if not attempt a reset
  ///
  if (PciePeiPreMemConfig->PegGpioData.GpioSupport) {
    for (PortIndex = 0; PortIndex < PciePortsLength; PortIndex++) {
      if (RedoEqNeeded[PortIndex] &&
            (((This->GetCurrentLinkSpeed (This, &(PciePorts[PortIndex])) < PEG_GEN3) &&
              (PciePorts[PortIndex].SwEqData.MaxCapableSpeed >= PEG_GEN3)) ||
            (This->GetNegotiatedWidth (This, &(PciePorts[PortIndex])) < PciePorts[PortIndex].SwEqData.MaxCapableWidth))) {
        DEBUG ((DEBUG_INFO, "Toggling PCIe slot PERST#.\n"));
        for (PegFunc = 0; PegFunc < SA_PEG_MAX_FUN; PegFunc++) {
          MmioOr16 (MmPciBase (SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, PegFunc) + R_SA_PEG_LCTL_OFFSET, BIT4);
        }
        if (PciePeiPreMemConfig->PegGpioData.SaPegReset.Active == 1) {
          Status = This->SetPchGpio (This, PciePeiPreMemConfig->PegGpioData.SaPegReset.GpioPad, 1);
        } else {
          Status = This->SetPchGpio (This, PciePeiPreMemConfig->PegGpioData.SaPegReset.GpioPad, 0);
        }
        if (!EFI_ERROR (Status)) {
          MicroSecondDelay (100 * STALL_ONE_MICRO_SECOND);
          for (PegFunc = 0; PegFunc < SA_PEG_MAX_FUN; PegFunc++) {
            MmioAnd16 (MmPciBase (SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, PegFunc) + R_SA_PEG_LCTL_OFFSET, (UINT16) ~(BIT4));
          }
          if (PciePeiPreMemConfig->PegGpioData.SaPegReset.Active == 1) {
            Status = This->SetPchGpio (This, PciePeiPreMemConfig->PegGpioData.SaPegReset.GpioPad, 0);
          } else {
            Status = This->SetPchGpio (This, PciePeiPreMemConfig->PegGpioData.SaPegReset.GpioPad, 1);
          }
        } else {
          for (PegFunc = 0; PegFunc < SA_PEG_MAX_FUN; PegFunc++) {
            MmioAnd16 (MmPciBase (SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, PegFunc) + R_SA_PEG_LCTL_OFFSET, (UINT16) ~(BIT4));
          }
        }
        if (!EFI_ERROR (Status)) {
          This->WaitForL0 (This, &(PciePorts[PortIndex]));
        }
        This->ReportPcieLinkStatus (This, &(PciePorts[PortIndex]));
      }
    }
  }
}

/**
  Program EQ Phase1 preset value

  @param[in]  This                        - Low level function table
  @param[in]  PciePorts                   - PCIe Root Port
  @param[in]  Direction                   - 0 = Root Port, 1 = End Point
  @param[in]  PresetValue                 - Preset value to program
  @param[in]  LogicalLane                 - Logical Lane to be configured
**/
VOID
EFIAPI
SklProgramPhase1Preset (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort,
  IN  UINT8                             Direction,
  IN  UINT8                             PresetValue,
  IN  UINT8                             LogicalLane
  )
{
  UINT32                          Data32Or;
  UINT32                          Data32And;

  switch (PciePort->Function) {
    case 1:
      if (LogicalLane < 8) {
        DEBUG ((DEBUG_WARN, "Invalid input to ProgramPreset() function!  PegFunc=%d, Lane=%d\n", PciePort->Function, LogicalLane));
        return;
      } else {
        LogicalLane -= 8;
      }
      break;
    case 2:
      if (LogicalLane < 12) {
        DEBUG ((DEBUG_WARN, "Invalid input to ProgramPreset() function!  PegFunc=%d, Lane=%d\n", PciePort->Function, LogicalLane));
        return;
      } else {
        LogicalLane -= 12;
      }
      break;
    default:
      break;
  }
  ///
  /// RP preset goes to bits [3:0]  for even lane and [19:16] for odd lane
  /// EP preset goes to bits [11:8] for even lane and [27:24] for odd lane
  ///
  if (Direction != 0) {
    if ((LogicalLane % 2) == 0) {
      Data32And = 0xFFFFF0FF;
      Data32Or  = PresetValue << 8;
    } else {
      Data32And = 0xF0FFFFFF;
      Data32Or  = PresetValue << 24;
    }
  } else {
    if ((LogicalLane % 2) == 0) {
      Data32And = 0xFFFFFFF0;
      Data32Or  = PresetValue;
    } else {
      Data32And = 0xFFF0FFFF;
      Data32Or  = PresetValue << 16;
    }
  }

  MmioAndThenOr32 (PciePort->ConfigSpaceBase + R_SA_PEG_EQCTL0_1_OFFSET + (LogicalLane / 2) * 4, Data32And, Data32Or);

  return;
}

/**
  Power Down Unused Lanes on the given PCIe Root Port

  @param[in]  This                        - Low level function table
  @param[in]  PciePort                    - PCIe Root Port
**/
VOID
EFIAPI
SklPowerDownUnusedLanes (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort
  )
{
  UINTN                           Peg0BaseAddress;
  UINT8                           LanesToPowerDown[SA_PEG_MAX_LANE];
  UINT8                           BundlesToPowerDown[SA_PEG_MAX_BUNDLE];
  UINT8                           LanesToPowerDownLength;
  UINT8                           BundlesToPowerDownLength;
  UINT8                           Width;
  UINT8                           LaneIndex;
  UINT8                           Index;
  UINT8                           Bundle;

  Peg0BaseAddress = MmPciBase (SA_PEG_BUS_NUM, SA_PEG10_DEV_NUM, SA_PEG10_FUN_NUM);
  if (PciePort->EndpointPresent) {
    Width = PciePort->SwEqData.MaxCapableWidth;
  } else {
    ///
    ///
    /// If endpoint is not present then we should use the disable root port
    /// sequence to shut down all bundles
    ///
    return;
  }
  if (Width <= 0) {
    ///
    /// Powering down all bundles should be done by the disable root port sequence
    ///
    return;
  }
  if ((Width % 2) > 0) {
    ///
    /// If a bundle is partially in use (for example X1 link width) leave it powered up
    ///
    Width += 1;
  }
  LanesToPowerDownLength = PciePort->MaxPortWidth - Width;
  if (LanesToPowerDownLength > PciePort->MaxPortLaneListLength) {
    ///
    /// This should never happen, just to make sure a buffer overrun is impossible
    ///
    LanesToPowerDownLength = PciePort->MaxPortLaneListLength;
  }
  if (Width > LanesToPowerDownLength) {
    ///
    /// This should never happen, just to make sure a buffer overrun is impossible
    ///
    Width = LanesToPowerDownLength;
  }
  ASSERT (LanesToPowerDownLength <= SA_PEG_MAX_LANE);
  if (LanesToPowerDownLength > SA_PEG_MAX_LANE) {
    return;
  }
  ///
  /// Create array of lanes to power down
  ///
  LaneIndex = Width;
  for (Index = 0; ((Index < LanesToPowerDownLength) && (LaneIndex < SA_PEG_MAX_LANE)); Index++) {
    LanesToPowerDown[Index] = PciePort->MaxPortLaneList[LaneIndex];
    LaneIndex++;
  }
  ///
  /// Convert to bundles
  ///
  GetBundleList (
    &LanesToPowerDown[0],
    LanesToPowerDownLength,
    &BundlesToPowerDown[0],
    &BundlesToPowerDownLength
    );
  ///
  /// Power down unused lanes
  ///
  if (BundlesToPowerDownLength > 0) {
    DEBUG ((
      DEBUG_INFO,
      "PCIe RP (%x:%x:%x) - Powering Down Bundles[%d:%d]\n",
      PciePort->Bus,
      PciePort->Device,
      PciePort->Function,
      BundlesToPowerDown[0],
      BundlesToPowerDown[BundlesToPowerDownLength - 1]
      ));
  } else {
    DEBUG ((
      DEBUG_INFO,
      "PCIe RP (%x:%x:%x) - All Bundles Active, Skipping Bundle Power Down\n",
      PciePort->Bus,
      PciePort->Device,
      PciePort->Function
      ));
  }
  if (BundlesToPowerDownLength > SA_PEG_MAX_BUNDLE) {
    BundlesToPowerDownLength = SA_PEG_MAX_BUNDLE;
  }
  for (Index = 0; Index < BundlesToPowerDownLength; Index++) {
    Bundle = BundlesToPowerDown[Index];
    MmioOr32 (Peg0BaseAddress + R_SA_PEG_BND0SPARE_OFFSET + (Bundle * BUNDLE_STEP), BIT31);
  }
}

/**
  Power Down All Lanes on the given PCIe Root Port

  @param[in]  This                        - Low level function table
  @param[in]  PegFunction                 - The function number of the PEG port to power down
**/
VOID
EFIAPI
SklPowerDownAllLanes (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  UINT8                             PegFunction
  )
{
  UINTN                           Peg0BaseAddress;
  UINT32                          HwStrap;
  UINT8                           LaneReversal;
  UINT8                           StartBundle;
  UINT8                           EndBundle;
  UINT8                           Bundle;

  Peg0BaseAddress = MmPciBase (SA_PEG_BUS_NUM, SA_PEG10_DEV_NUM, SA_PEG10_FUN_NUM);
  HwStrap         = (MmioRead32 (Peg0BaseAddress + R_SA_PEG_FUSESCMN_OFFSET) >> 16) & 0x3;
  LaneReversal    = (MmioRead32 (Peg0BaseAddress + R_SA_PEG_PEGTST_OFFSET) >> 20) & 0x1;
  StartBundle     = 0;
  EndBundle       = 0;

  switch (PegFunction) {
    case SA_PEG10_FUN_NUM:
      switch (HwStrap) {
        case SA_PEG_x16_x0_x0:
          StartBundle   = 0;
          EndBundle     = 7;
          break;
        default:
          if (LaneReversal == 0) {
            StartBundle = 0;
            EndBundle   = 3;
          } else {
            StartBundle = 4;
            EndBundle   = 7;
          }
          break;
      }
      break;
    case SA_PEG11_FUN_NUM:
      switch (HwStrap) {
        case SA_PEG_x8_x8_x0:
          if (LaneReversal == 0) {
            StartBundle = 4;
            EndBundle   = 7;
          } else {
            StartBundle = 0;
            EndBundle   = 3;
          }
          break;
        case SA_PEG_x8_x4_x4:
          if (LaneReversal == 0) {
            StartBundle = 4;
            EndBundle   = 5;
          } else {
            StartBundle = 2;
            EndBundle   = 3;
          }
          break;
        default:
          return; ///< Nothing to do for PEG11
      }
      break;
    case SA_PEG12_FUN_NUM:
      switch (HwStrap) {
        case SA_PEG_x8_x4_x4:
          if (LaneReversal == 0) {
            StartBundle = 6;
            EndBundle   = 7;
          } else {
            StartBundle = 0;
            EndBundle   = 1;
          }
          break;
        default:
          return; ///< Nothing to do for PEG12
      }
      break;
    default:
      return; ///< Invalid PEG Controller
  }

  ///
  /// Power down unused lanes
  ///
  DEBUG ((
    DEBUG_INFO,
    "PCIe RP (%x:%x:%x) - Powering Down Bundles[%d:%d]\n",
    SA_PEG_BUS_NUM,
    SA_PEG_DEV_NUM,
    PegFunction,
    StartBundle,
    EndBundle
    ));
  for (Bundle = StartBundle; Bundle <= EndBundle; Bundle++) {
    MmioOr32 (Peg0BaseAddress + R_SA_PEG_BND0SPARE_OFFSET + (Bundle * BUNDLE_STEP), BIT31);
  }
}

/**
  Sets the link width

  @param[in]  This                        - Low level function table
  @param[in]  PciePort                    - PCIe Root Port
  @param[in]  LinkWidth                   - Desired Link Width
**/
VOID
EFIAPI
SklSetLinkWidth (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort,
  IN  UINT8                             LinkWidth
  )
{
  UINT32            Data32Or;

  Data32Or = 0;
  if (LinkWidth != 0) {
    switch (LinkWidth) {
      case 1:
        Data32Or = BIT0;
        break;
      case 2:
        Data32Or = BIT1 | BIT0;
        break;
      case 4:
        Data32Or = BIT2 | BIT1 | BIT0;
        break;
      case 8:
        Data32Or = BIT3 | BIT2 | BIT1 | BIT0;
        break;
      case 16:
      default:
        Data32Or = BIT4 | BIT3 | BIT2 | BIT1 | BIT0;
        break;
    }
    MmioAndThenOr32 (PciePort->ConfigSpaceBase + R_SA_PEG_LTSSMC_OFFSET, (UINT32) ~(BIT4 | BIT3 | BIT2 | BIT1 | BIT0), Data32Or);

    This->SetLinkDisable (This, PciePort, TRUE);
    MicroSecondDelay (STALL_ONE_MICRO_SECOND);
    This->SetLinkDisable (This, PciePort, FALSE);

    This->WaitForL0 (This, PciePort);
  }
}

/**
  Additional Programming steps that need to be performed post endpoint detection

  @param[in]  This                        - Low level function table
  @param[in]  PciePort                    - PCIe Root Port
**/
VOID
EFIAPI
SklPostDetectionAdditionalProgramming (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort
  )
{
  UINT32              Data32And;
  UINT32              Data32Or;
  UINT8               Index;


  ///
  /// Set L0SLAT[15:0] to 0x2020
  ///
  ///
  ///
  Data32And = (UINT32) ~(0xFFFF);
  Data32Or  = 0x00002020;
  MmioAndThenOr32 (PciePort->ConfigSpaceBase + R_SA_PEG_L0SLAT_OFFSET, Data32And, Data32Or);

  ///
  /// Disable PEG Debug Align Message - set 258[29] = '1b'
  ///
  MmioOr32 (PciePort->ConfigSpaceBase + R_SA_PEG_CFG4_OFFSET, BIT29);

  ///
  ///
  MmioOr32 (PciePort->ConfigSpaceBase + R_SA_PEG_PEGCLKGTCMN_OFFSET, (UINT32) BIT31);

  ///
  /// Retrain the link only if VC0 negotiation is complete at this point.
  /// This is to support CLB card together with "Aways Enable PEG" option
  ///
  if (This->DataLinkLayerLinkActive (This, PciePort)) {
    This->RetrainLink (This, PciePort);
    ///
    /// Wait for Link training complete
    ///
    for (Index = 0; Index < 100; Index++) {
      if ((MmioRead16 (PciePort->ConfigSpaceBase + R_SA_PEG_LSTS_OFFSET) & BIT11) != 0) {
        break;
      }
      MicroSecondDelay (STALL_ONE_MILLI_SECOND);
    }
  }
}

/**
  Perform flow control credit programming

  @param[in]  This                        - Low level function table
  @param[in]  PegDisableMask              - Bitmap of controllers to disable by function number
**/
VOID
EFIAPI
SklFlowControlCreditProgramming (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  UINT8                             PegDisableMask
  )
{
  UINT32  MchBar;

  MchBar   = ((SA_PCIE_PRIVATE_FUNCTION_CALLS*) This->PrivateData)->MchBar;

  ///
  /// Select the configuration base on which PEGs are enabled.
  ///
  if (((PegDisableMask >> 2) & 0x1) == 0) {
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL0_OFFSET, 0x08241251);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL1_OFFSET, 0x08241251);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL2_OFFSET, 0x0220A412);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL3_OFFSET, 0x00000010);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL4_OFFSET, 0x000006D6);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL5_OFFSET, 0x00339DC7);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL6_OFFSET, 0x00301080);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL7_OFFSET, 0x00339DC7);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL8_OFFSET, 0x00601080);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL9_OFFSET, 0x041C7388);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL10_OFFSET, 0x00000200);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL11_OFFSET, 0x00004100);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL12_OFFSET, 0x0000048A);
    DEBUG ((DEBUG_INFO, "Program PEG flow control credit values for x8 x4 x4 configuration\n"));
  } else if (((PegDisableMask >> 1) & 0x1) == 0) {
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL0_OFFSET, 0x08241051);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL1_OFFSET, 0x08241051);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL2_OFFSET, 0x02208412);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL3_OFFSET, 0x00000010);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL4_OFFSET, 0x00000758);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL5_OFFSET, 0x003039C8);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL6_OFFSET, 0x00301080);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL7_OFFSET, 0x003039C7);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL8_OFFSET, 0x00601080);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL9_OFFSET, 0x0400E388);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL10_OFFSET, 0x00000200);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL11_OFFSET, 0x00004100);
    MmioWrite32 ((UINTN) MchBar + R_SA_MCHBAR_CRDTCTL12_OFFSET, 0x0000048A);
    DEBUG ((DEBUG_INFO, "Program PEG flow control credit values for x8 x8 x0 configuration\n"));
  } else {
    FlowControlCreditProgrammingNoPegLib();
  }
}

/**
  Disable or enable Icomp for a root port
  @param[in]  This                        - Low level function table
  @param[in]  PciePort                    - PCIe Root Port
  @param[in]  Disable                     - TRUE to Disable, FALSE to Enable
**/
VOID
EFIAPI
SklSetRootPortIcompDisable (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort,
  IN  BOOLEAN                           Disable
  )
{
  UINTN                           Peg0BaseAddress;
  UINT8                           RootPortBundles[SA_PEG_MAX_BUNDLE];
  UINT8                           RootPortBundlesLength;
  UINT8                           Index;

  Peg0BaseAddress = MmPciBase (SA_PEG_BUS_NUM, SA_PEG10_DEV_NUM, SA_PEG10_FUN_NUM);
  ///
  /// Get the enpoint bundles from the max lane list
  ///
  GetBundleList (
    &PciePort->MaxPortLaneList[0],
    PciePort->MaxPortLaneListLength,
    &RootPortBundles[0],
    &RootPortBundlesLength
    );
  if (RootPortBundlesLength > SA_PEG_MAX_BUNDLE) {
    RootPortBundlesLength = SA_PEG_MAX_BUNDLE;
  }
  if (Disable) {
    DEBUG ((DEBUG_INFO, "PEG %x:%x:%x Icomp Disabled\n", PciePort->Bus, PciePort->Device, PciePort->Function));
    for (Index = 0; Index < RootPortBundlesLength; Index++) {
      MmioOr32 (Peg0BaseAddress + R_SA_PEG_AFEBND0CFG5_OFFSET + (RootPortBundles[Index] * BUNDLE_STEP), BIT17);
    }
  } else {
    DEBUG ((DEBUG_INFO, "PEG %x:%x:%x Icomp Enabled\n", PciePort->Bus, PciePort->Device, PciePort->Function));
    for (Index = 0; Index < RootPortBundlesLength; Index++) {
      MmioAnd32 (Peg0BaseAddress + R_SA_PEG_AFEBND0CFG5_OFFSET + (RootPortBundles[Index] * BUNDLE_STEP), (UINT32) ~BIT17);
    }
  }
}

/**
  Program the Spine Clock Gating feature according to the configuration

  @param[in]  PciePeiPreMemConfig                  - PCIE configuration block
**/
VOID
EFIAPI
SklSpineClockGatingProgramming (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This
  )
{
  SA_PCIE_PRIVATE_FUNCTION_CALLS  *PciePrivate;
  PCIE_PEI_PREMEM_CONFIG          *PciePeiPreMemConfig;
  UINT32                          Data32Or;
  UINT32                          Data32And;
  UINT32                          Peg0BaseAddress;
  UINT32                          Peg1BaseAddress;
  UINT32                          Peg2BaseAddress;
  CPU_SKU                         CpuSku;

  CpuSku        = GetCpuSku ();
  PciePrivate   = (SA_PCIE_PRIVATE_FUNCTION_CALLS*) This->PrivateData;
  PciePeiPreMemConfig    = PciePrivate->PciePeiPreMemConfig;

  if ((CpuSku == EnumCpuHalo) || (CpuSku == EnumCpuTrad)) {
    ///
    /// Configure Spine Clock Gating for PEG
    ///
    Peg0BaseAddress  = MmPciBase (SA_PEG_BUS_NUM, SA_PEG10_DEV_NUM, SA_PEG10_FUN_NUM);
    Peg1BaseAddress  = MmPciBase (SA_PEG_BUS_NUM, SA_PEG11_DEV_NUM, SA_PEG11_FUN_NUM);
    Peg2BaseAddress  = MmPciBase (SA_PEG_BUS_NUM, SA_PEG12_DEV_NUM, SA_PEG12_FUN_NUM);
    Data32And = (UINT32) ~(BIT29 | BIT28 | BIT27);
    Data32Or = 0;
    DEBUG ((DEBUG_INFO, "Configure Spine Clock Gating for PEG\n"));
    ///
    /// Write the configuration for all PEGs.
    ///
    MmioAndThenOr32 (Peg0BaseAddress + R_SA_PEG_PEGCLKGTCMN_OFFSET, Data32And, Data32Or);
    MmioAndThenOr32 (Peg1BaseAddress + R_SA_PEG_PEGCLKGTCMN_OFFSET, Data32And, Data32Or);
    MmioAndThenOr32 (Peg2BaseAddress + R_SA_PEG_PEGCLKGTCMN_OFFSET, Data32And, Data32Or);
    ///
    /// Configure Spine Clock Gating for DMI
    ///
    Data32And = (UINT32) ~(BIT29 | BIT28 | BIT27);
    Data32Or = 0;
    DEBUG ((DEBUG_INFO, "Configure Spine Clock Gating for DMI\n"));
    ///
    /// Write the configuration for DMI.
    ///
    MmioAndThenOr32 ((UINTN) (PciePrivate->DmiBar + R_SA_PEG_PEGCLKGTCMN_OFFSET), Data32And, Data32Or);
  }
}

/**
  Determines if the platform requires the ICOMP disable check

  @param[in]  This                        - Low level function table

  @retval TRUE  - The current platform requires the ICOMP disable check
  @retval FALSE - The current platform does not require the ICOMP disable check
**/
BOOLEAN
EFIAPI
SklIsIcompCheckRequired (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This
  )
{
  UINT16                          GtDid;

  GtDid = MmioRead16 (MmPciBase (SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0) + PCI_DEVICE_ID_OFFSET);
  DEBUG ((DEBUG_INFO, "GtDid = 0x%x\n", GtDid));
    //
    //
  if (GtDid == V_SA_PCI_DEV_2_GT2_SHALM_ID) {
    return TRUE;
  }
  return FALSE;
}

/**
  This function gets the private data for the SA PCIe low level functions

  @param[in]  IN  PCIE_PEI_PREMEM_CONFIG    - PciePeiPreMemConfig
  @param[in]  IN  SA_MISC_PEI_PREMEM_CONFIG - MiscPeiPreMemConfig
  @param[out] SaPciePrivateData   - Table of function calls for SA PEG

  @retval EFI_SUCCESS - Table of function calls returned successfully
**/
EFI_STATUS
GetSklPegPrivateData (
  IN  PCIE_PEI_PREMEM_CONFIG                  *PciePeiPreMemConfig,
  IN  SA_MISC_PEI_PREMEM_CONFIG               *MiscPeiPreMemConfig,
  OUT SA_PCIE_PRIVATE_FUNCTION_CALLS          *SaPciePrivateData
  )
{
  UINTN   McBaseAddress;

  McBaseAddress                                         = MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN);
  SaPciePrivateData->PciePeiPreMemConfig                = PciePeiPreMemConfig;
  SaPciePrivateData->MchBar                             = MmioRead32 (McBaseAddress + R_SA_MCHBAR) &~BIT0;
  SaPciePrivateData->DmiBar                             = (MmioRead32(McBaseAddress + R_SA_DMIBAR) &~BIT0) + LShiftU64(MmioRead32(McBaseAddress + R_SA_DMIBAR + 4), 32);
  SaPciePrivateData->GdxcBar                            = MiscPeiPreMemConfig->GdxcBar;
  SaPciePrivateData->IsGen3Capable                      = SklPegIsGen3Capable;
  SaPciePrivateData->PreDetectionProgramming            = SklPegPreDetectionProgramming;
  SaPciePrivateData->PcieDmiRecipe                      = SklPegDmiRecipe;
  SaPciePrivateData->ConfigureMaxSpeedWidth             = SklConfigureMaxSpeedWidth;
  SaPciePrivateData->EnableRxCemLoopbackMode            = SklEnableRxCemLoopbackMode;
  SaPciePrivateData->ClearDeferOc                       = SklClearDeferOc;
  SaPciePrivateData->SetDisableAutoSpeedUp              = SklSetDisableAutoSpeedUp;
  SaPciePrivateData->PostDetectionEqProgramming         = SklPostDetectionEqProgramming;
  SaPciePrivateData->GetLinkPartnerFullSwing            = GetLinkPartnerFullSwing;
  SaPciePrivateData->SetPartnerTxCoefficients           = SetPartnerTxCoefficients;
  SaPciePrivateData->EqPh2Ph3BypassProgramming          = SklEqPh2Ph3BypassProgramming;
  SaPciePrivateData->ProgramPhase1Preset                = SklProgramPhase1Preset;
  SaPciePrivateData->PowerDownUnusedLanes               = SklPowerDownUnusedLanes;
  SaPciePrivateData->PowerDownAllLanes                  = SklPowerDownAllLanes;
  SaPciePrivateData->SetLinkWidth                       = SklSetLinkWidth;
  SaPciePrivateData->PostDetectionAdditionalProgramming = SklPostDetectionAdditionalProgramming;
  SaPciePrivateData->DisableUnusedPcieControllers       = SklDisableUnusedPcieControllers;
  SaPciePrivateData->FlowControlCreditProgramming       = SklFlowControlCreditProgramming;
  SaPciePrivateData->SetRootPortIcompDisable            = SklSetRootPortIcompDisable;
  SaPciePrivateData->SpineClockGatingProgramming        = SklSpineClockGatingProgramming;
  SaPciePrivateData->DisableSpreadSpectrumClocking      = SklDisableSpreadSpectrumClocking;
  SaPciePrivateData->IsIcompCheckRequired               = SklIsIcompCheckRequired;

  return EFI_SUCCESS;
}
