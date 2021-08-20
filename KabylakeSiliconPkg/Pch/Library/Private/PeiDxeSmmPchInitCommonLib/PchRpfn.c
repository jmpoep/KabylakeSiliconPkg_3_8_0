/** @file
  This file contains functions that configures PCI Express Root Ports function swapping.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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
#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/MmPciLib.h>
#include <Library/PchPcieRpLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Private/Library/PchPciExpressHelpersLib.h>
#include <Private/Library/PchInitCommonLib.h>
#include <Private/Library/PchPsfPrivateLib.h>
#include <Library/S3BootScriptLib.h>

/**
  Configure root port function number mapping

  @retval EFI_SUCCESS                   The function completed successfully
**/
EFI_STATUS
PchConfigureRpfnMapping (
  VOID
  )
{
  UINT8                                 PortIndex;
  UINT8                                 OriginalFuncZeroRp;
  UINT8                                 MaxPciePortNum;
  UINT32                                Data32;
  UINTN                                 DevNum;
  UINTN                                 FuncNum;
  UINTN                                 RpBase;
  UINT32                                ControllerPcd[PCH_MAX_PCIE_CONTROLLERS];
  PCH_SERIES                            PchSeries;
  PCH_GENERATION                        PchGen;
  UINT32                                PcieControllers;
  UINT32                                ControllerIndex;
  UINT32                                FirstController;
  PCH_SBI_PID                           ControllerPid;

  DEBUG ((DEBUG_INFO,"PchConfigureRpfnMapping () Start\n"));

  PchSeries      = GetPchSeries ();
  PchGen         = GetPchGeneration ();
  MaxPciePortNum = GetPchMaxPciePortNum ();

  PcieControllers = GetPchMaxPcieControllerNum ();

  for (ControllerIndex = 0; ControllerIndex < PcieControllers; ++ControllerIndex) {
    PchPcrRead32 (PchGetPcieControllerSbiPid (ControllerIndex), R_PCH_PCR_SPX_PCD, &ControllerPcd[ControllerIndex]);
  }

  ///
  /// Configure root port function number mapping
  ///
  for (PortIndex = 0; PortIndex < MaxPciePortNum; ) {
    GetPchPcieRpDevFun (PortIndex, &DevNum, &FuncNum);
    RpBase = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, (UINT32) DevNum, (UINT32) FuncNum);
    //
    // Search for first enabled function
    //
    if (MmioRead16 (RpBase) != 0xFFFF) {
      if (FuncNum != 0) {
        //
        // First enabled root port that is not function zero will be swapped with function zero on the same device
        // RP PCD register must sync with PSF RP function config register
        //
        ControllerIndex    = PortIndex / 4;
        OriginalFuncZeroRp = (PortIndex / 8) * 8;
        FirstController    = OriginalFuncZeroRp / 4;

        //
        // The enabled root port becomes function zero
        //
        ControllerPcd[ControllerIndex] &= (UINT32) ~(B_PCH_PCR_SPX_PCD_RP1FN << ((PortIndex % 4) * S_PCH_PCR_SPX_PCD_RP_FIELD));
        ControllerPcd[ControllerIndex] |= 0u;
        //
        // Origianl function zero on the same device takes the numer of the current port
        //
        ControllerPcd[FirstController] &= (UINT32) ~B_PCH_PCR_SPX_PCD_RP1FN;
        ControllerPcd[FirstController] |= (UINT32) FuncNum;

        //
        // Program PSF1 RP function config register.
        //
        PsfSetPcieFunctionWithS3BootScript (OriginalFuncZeroRp, (UINT32) FuncNum);
        PsfSetPcieFunctionWithS3BootScript (PortIndex, 0);
      }
      //
      // Once enabled root port was found move to next PCI device
      //
      PortIndex = ((PortIndex / 8) + 1) * 8;
      continue;
    }
    //
    // Continue search for first enabled root port
    //
    PortIndex++;
  }

  //
  // Write to PCD and lock the register
  //
  for (ControllerIndex = 0; ControllerIndex < PcieControllers; ++ControllerIndex) {
    ControllerPid = PchGetPcieControllerSbiPid (ControllerIndex);
    Data32 = ControllerPcd[ControllerIndex] | B_PCH_PCR_SPX_PCD_SRL;
    PchPcrWrite32 (ControllerPid, R_PCH_PCR_SPX_PCD, Data32);
    PCH_PCR_BOOT_SCRIPT_WRITE (
      S3BootScriptWidthUint32,
      ControllerPid, R_PCH_PCR_SPX_PCD,
      1,
      &Data32
      );
  }
  return EFI_SUCCESS;
}

