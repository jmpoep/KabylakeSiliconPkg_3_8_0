/** @file
  PCH Gbe Library.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2015 Intel Corporation.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/MmPciLib.h>
#include <PchAccess.h>
#include <Library/PchInfoLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchCycleDecodingLib.h>

/**
  Check whether GbE region is valid
  Check SPI region directly since GbE might be disabled in SW.

  @retval TRUE                    Gbe Region is valid
  @retval FALSE                   Gbe Region is invalid
**/
BOOLEAN
PchIsGbeRegionValid (
  VOID
  )
{
  UINT32  SpiBar;
  SpiBar = MmioRead32 (MmPciBase (
                         DEFAULT_PCI_BUS_NUMBER_PCH,
                         PCI_DEVICE_NUMBER_PCH_SPI,
                         PCI_FUNCTION_NUMBER_PCH_SPI)
                         + R_PCH_SPI_BAR0) & ~B_PCH_SPI_BAR0_MASK;
  ASSERT (SpiBar != 0);
  if (MmioRead32 (SpiBar + R_PCH_SPI_FREG3_GBE) != B_PCH_SPI_FREGX_BASE_MASK) {
    return TRUE;
  }
  return FALSE;
}

/**
  Returns GbE over PCIe port number based on a soft strap.

  @return                         Root port number (1-based)
  @retval 0                       GbE over PCIe disabled
**/
UINT32
PchGetGbePortNumber (
  VOID
  )
{
  UINT32   GbePortSel;
  UINT32   PcieStrapFuse;

  PchPcrRead32 (PID_FIA, R_PCH_PCR_FIA_STRPFUSECFG1_REG_BASE, &PcieStrapFuse);
  if ((PcieStrapFuse & B_PCH_PCR_FIA_STRPFUSECFG1_GBE_PCIE_PEN) == 0) {
    return 0; // GbE disabled
  }
  GbePortSel = (PcieStrapFuse & B_PCH_PCR_FIA_STRPFUSECFG1_GBE_PCIEPORTSEL) >> N_PCH_PCR_FIA_STRPFUSECFG1_GBE_PCIEPORTSEL;
  if (GetPchSeries () == PchLp) {
    switch (GbePortSel) {
      case 0: return 3;
      case 1: return 4;
      case 2: return 5;
      case 3: return 9;
      case 4: return 10;
    }
  } else {
    switch (GbePortSel) {
      case 0: return 4;
      case 1: return 5;
      case 2: return 9;
      case 3: return 12;
      case 4: return 13;
    }
  }
  DEBUG ((DEBUG_ERROR, "Invalid GbE port\n"));
  ASSERT (FALSE);
  return 0;
}

/**
  Check whether LAN controller is enabled in the platform.

  @retval TRUE                    GbE is enabled
  @retval FALSE                   GbE is disabled
**/
BOOLEAN
PchIsGbePresent (
  VOID
  )
{
  UINT32  PwrmBase;
  UINT32  FuseDis2State;
  //
  // Check PMC strap/fuse
  //
  PchPwrmBaseGet (&PwrmBase);
  FuseDis2State = MmioRead32 (PwrmBase + R_PCH_PWRM_FUSE_DIS_RD_2);
  if (FuseDis2State & B_PCH_PWRM_FUSE_DIS_RD_2_GBE_FUSE_SS_DIS) {
    return FALSE;
  }
  //
  // Check FIA strap/fuse
  //
  if (PchGetGbePortNumber () == 0) {
    return FALSE;
  }
  //
  // Check GbE NVM
  //
  if (PchIsGbeRegionValid () == FALSE) {
    return FALSE;
  }
  return TRUE;
}

/**
  Check whether LAN controller is enabled in the platform.

  @deprecated Use PchIsGbePresent instead.

  @retval TRUE                    GbE is enabled
  @retval FALSE                   GbE is disabled
**/
BOOLEAN
PchIsGbeAvailable (
  VOID
  )
{
  return PchIsGbePresent ();
}


