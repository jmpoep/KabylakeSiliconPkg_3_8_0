/** @file
  Additional programming steps for disabling PEG controller.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#include "SaPegLowLevel.h"
#include <Private/Library/SaPcieInitLib.h>
#include <Library/CpuPlatformLib.h>

/**
Program flow control credits for configurations where PEG is disabled or x16x0x0.
**/
VOID
FlowControlCreditProgrammingNoPegLib (
  VOID
  )
{
}

/**
  Disable Unused PEG Controllers

  @param[in]  This                        - Low level function table
  @param[in]  PegDisableMask              - Bitmap of controllers to disable by function number
**/
VOID
EFIAPI
SklDisableUnusedPcieControllers (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  UINT8                             PegDisableMask
  )
{
  SA_PCIE_PRIVATE_FUNCTION_CALLS  *PciePrivate;
  UINTN                           McBaseAddress;
  UINTN                           Peg0BaseAddress;
  UINTN                           PegBaseAddress;
  UINT16                          LoopCount;
  UINT8                           PegFunc;
  CPU_SKU                         CpuSku;
  BOOLEAN                         DisableLinkFunc0;
  BOOLEAN                         FunctionExists;
  BOOLEAN                         PowerGatingSupported;
  UINT32                          StateTracker;

  PciePrivate      = (SA_PCIE_PRIVATE_FUNCTION_CALLS*) This->PrivateData;
  DisableLinkFunc0 = FALSE;
  McBaseAddress    = MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN);
  Peg0BaseAddress  = MmPciBase (SA_PEG_BUS_NUM, SA_PEG10_DEV_NUM, SA_PEG10_FUN_NUM);
  CpuSku           = GetCpuSku ();
  ///
  /// PEG10 must be enabled if PEG11 and/or PEG12 are enabled
  ///
  if (((PegDisableMask & BIT1) == 0) || ((PegDisableMask & BIT2) == 0)) {
    if ((PegDisableMask & BIT0) != 0) {
      DisableLinkFunc0 = TRUE;
    }
    PegDisableMask &= (UINT8) ~(BIT0);
  }

  PegFunc = SA_PEG_MAX_FUN;
  do {
    PegFunc--;
    PegBaseAddress = MmPciBase (SA_PEG_BUS_NUM, SA_PEG10_DEV_NUM, PegFunc);
    if (MmioRead16 (PegBaseAddress + R_SA_PEG_VID_OFFSET) == 0xFFFF) {
      FunctionExists = FALSE;
      DEBUG ((DEBUG_WARN, "PCIe RP (0:1:%x) Disabled.\n", PegFunc));
    } else {
      FunctionExists = TRUE;
    }
    if (((((PegDisableMask >> PegFunc) & 0x1) != 0) ||
          ((PegFunc == 0) && DisableLinkFunc0))     && FunctionExists) {
      ///
      /// Set D1.F0.R D20h [30] = 1
      ///
      MmioOr32 (PegBaseAddress + R_SA_PEG_PEGCOMLCGCTRL_OFFSET, BIT30);
      ///
      /// DisableLink. Set D1.F0.R 0B0h [4] (LD (Link Disable) bit in Link Control Register
      ///
      MmioOr8 (PegBaseAddress + R_SA_PEG_LCTL_OFFSET, BIT4);
      ///
      /// Poll until D1.F0.R 464h = 0 or 2
      ///
      StateTracker = 0;
      for (LoopCount = 0; LoopCount < (100 * 10); LoopCount++) {
        StateTracker = (MmioRead32 (Peg0BaseAddress + R_SA_PEG_REUT_PH1_PIS_OFFSET) >> (8 * PegFunc)) & 0x3F;
        if (StateTracker == 0x0 || StateTracker == 0x2) {
          break;
        }
        MicroSecondDelay (STALL_ONE_MICRO_SECOND * 100); //100usec
      }
      ///
      /// Check if successful, if not then abort flow for this controller
      ///
      if (StateTracker != 0x0 && StateTracker != 0x2) {
        PegDisableMask |= (1 << PegFunc);
        DEBUG ((DEBUG_WARN, "PCIe RP (0:1:%x) Timeout disabling link.\n", PegFunc));
        continue;
      }
      ///
      /// Program AFEOVR.RXSQDETOVR
      /// PCIe link disable for Switchable GFx
      /// Additional Power savings: Set 0:1:0 0xC20 BIT4 = 1 & BIT5 = 1
      ///
      MmioOr8 (PegBaseAddress + R_SA_PEG_AFEOVR_OFFSET, (UINT8) (BIT5 | BIT4));
      ///
      /// Power Down All Lanes
      ///
      PciePrivate->PowerDownAllLanes (This, PegFunc);
      ///
      /// Disable Controller
      ///
      if (((PegDisableMask >> PegFunc) & 0x1) != 0) {
        ///
        /// Clear D0.F0.R 054h (DEVEN) enable bit.
        ///
        MmioAnd8 (McBaseAddress + R_SA_DEVEN, (UINT8) ~(BIT3 >> PegFunc));
        DEBUG ((DEBUG_WARN, "PCIe RP (0:1:%x) Disabled.\n", PegFunc));
      }
    }
  } while (PegFunc > 0);
  ///
  /// If all PEG Controllers are disabled, disable PEG
  ///
  if ((PegDisableMask & 0x7) == 0x7) {
    PowerGatingSupported = FALSE;
    if ((CpuSku  == EnumCpuHalo) || (CpuSku  == EnumCpuTrad)) {
      PowerGatingSupported = TRUE;
    }

    if (PowerGatingSupported) {
      DEBUG ((DEBUG_INFO, "No PEG Root Ports active, Power Gating PEG\n"));
      MmioOr32 (((UINTN) PciePrivate->MchBar) + R_SA_MCHBAR_BIOS_RESET_CPL_OFFSET, BIT3);
    } else {
      DEBUG ((DEBUG_WARN, "PEG Power Gate not supported on this stepping\n"));
    }
  }
}

/**
  This function gets the private data for the SA PCIe low level functions

  @param[in]  PCIE_PEI_PREMEM_CONFIG     - PciePeiPreMemConfig
  @param[in]  SA_MISC_PEI_PREMEM_CONFIG  - MiscPeiPreMemConfig
  @param[out] SaPciePrivateData          - Table of function calls for SA PEG

  @retval EFI_SUCCESS - Table of function calls returned successfully
**/
EFI_STATUS
GetSaPciePrivateData (
  IN  PCIE_PEI_PREMEM_CONFIG                  *PciePeiPreMemConfig,
  IN  SA_MISC_PEI_PREMEM_CONFIG               *MiscPeiPreMemConfig,
  OUT SA_PCIE_PRIVATE_FUNCTION_CALLS          *SaPciePrivateData
  )
{
  CPU_SKU  CpuSku;

  CpuSku = GetCpuSku ();

  if ((CpuSku == EnumCpuHalo) || (CpuSku == EnumCpuTrad)) {
    return GetSklPegPrivateData (
             PciePeiPreMemConfig,
             MiscPeiPreMemConfig,
             SaPciePrivateData
             );
  }
  return EFI_UNSUPPORTED;
}
