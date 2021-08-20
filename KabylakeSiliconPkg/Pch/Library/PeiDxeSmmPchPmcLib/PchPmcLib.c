/** @file
  PCH PMC Library.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/MmPciLib.h>
#include <PchAccess.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PchPmcLib.h>

/**
  Query PCH to determine the Pm Status
  NOTE:
  It's matter when did platform code use this library, since some status could be cleared by write one clear.
  Therefore this funciton is not always return the same result in one boot.
  It's suggested that platform code read this status in the beginning of post.
  For the ColdBoot case, this function only returns one case of the cold boot. Some cold boot case might
  depends on the power cycle scenario and should check with different condtion.

  @param[in] PmStatus - The Pch Pm Status to be probed

  @retval Return TRUE if Status querried is Valid or FALSE if otherwise
**/
BOOLEAN
GetPchPmStatus (
  PCH_PM_STATUS PmStatus
  )
{
  UINTN  PmcRegBase;
  UINT32 PchPwrmBase;
  UINT32 PmConA;
  UINT32 PmConB;
  UINT32 GblRst0;

  PmcRegBase = MmPciBase (
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_PMC,
                 PCI_FUNCTION_NUMBER_PCH_PMC
                 );
  PchPwrmBaseGet (&PchPwrmBase);

  PmConA     = MmioRead32 (PmcRegBase + R_PCH_PMC_GEN_PMCON_A);
  PmConB     = MmioRead32 (PmcRegBase + R_PCH_PMC_GEN_PMCON_B);

  GblRst0    = MmioRead32 (PchPwrmBase + R_PCH_PWRM_124);

  switch (PmStatus) {
    case WarmBoot:
      if (PmConA & B_PCH_PMC_GEN_PMCON_A_MEM_SR) {
        return TRUE;
      }
      break;

    case PwrFlr:
      if (PmConB & B_PCH_PMC_GEN_PMCON_B_PWR_FLR) {
        return TRUE;
      }
      break;

    case PwrFlrSys:
      if (GblRst0 & BIT12) {
        return TRUE;
      }
      break;

    case PwrFlrPch:
      if (GblRst0 & BIT11) {
        return TRUE;
      }
      break;

    case ColdBoot:
      ///
      /// Check following conditions for cold boot.
      ///
      if ((GblRst0 & BIT11) &&  // PCHPWR_FLR
          (GblRst0 & BIT12) &&  // SYSPWR_FLR
          (!(PmConA & B_PCH_PMC_GEN_PMCON_A_MEM_SR))) {
        return TRUE;
      }
      break;

    default:
      break;
  }

  return FALSE;
}

/**
  Funtion to check if Battery lost or CMOS cleared.

  @reval TRUE  Battery is always present.
  @reval FALSE CMOS is cleared.
**/
BOOLEAN
EFIAPI
PchIsRtcBatteryGood (
  VOID
  )
{
  UINTN    Data;
  UINTN    PmcBaseAddress;

  //
  // Check if the CMOS battery is present
  // Checks RTC_PWR_STS bit in the GEN_PMCON_3 register
  //
  PmcBaseAddress = MmPciBase (
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_PMC,
                     PCI_FUNCTION_NUMBER_PCH_PMC
                     );
  Data = MmioRead32 (PmcBaseAddress + R_PCH_PMC_GEN_PMCON_B);

  if ((Data & B_PCH_PMC_GEN_PMCON_B_RTC_PWR_STS) == 0) {
    return TRUE;
  }
  return FALSE;
}

/**
  Check if this system boot is due to Overclocking flow reset during S3
  - BCLK update causes reset.
  - PLL voltage changed causes reset.
  - TjMax update causes reset.

  @retval  TRUE   OC related reset occured during S3
  @retval  FALSE  OC related reset did not occur during S3
**/
BOOLEAN
PmcIsBclkS3Boot (
  VOID
  )
{
  UINT16 PmcScratchPad;
  UINT32            PwrmBase;

  PchPwrmBaseGet (&PwrmBase);
  PmcScratchPad = MmioRead16 ((UINTN) (PwrmBase + R_PCH_TCO_WDCNT));

  if ((PmcScratchPad & B_PCH_PMC_HOST_MISC_SUS_CFG_BCLK_S3) == BIT8) {
    DEBUG ((DEBUG_INFO, "OC PLL or BCLK reset occured during S3 resume on the previous boot.\n"));
    return TRUE;
  }

  DEBUG ((DEBUG_INFO, "OC PLL or BCLK reset during S3 did not occur.\n"));
  return FALSE;
}

/**
  Set OC BCLK S3 scratchpad bit

**/
VOID
PmcSetBclkS3 (
  VOID
  )
{
  UINT32            PwrmBase;

  PchPwrmBaseGet (&PwrmBase);
  ///
  /// Set OC S3 of scratchpad register to indicate PLL or BCLK OC reset during S3
  ///
  MmioOr16 (PwrmBase + R_PCH_TCO_WDCNT, B_PCH_PMC_HOST_MISC_SUS_CFG_BCLK_S3);
}


/**
  Clear OC BCLK S3 scratchpad bit

**/
VOID
PmcClearBclkS3 (
  VOID
  )
{
  UINT32            PwrmBase;

  PchPwrmBaseGet (&PwrmBase);
  ///
  /// Clear OC S3 of scratchpad register so we do not detect another PLL or BCLK reset.
  ///
  MmioAnd16 ((UINTN) (PwrmBase + R_PCH_TCO_WDCNT), (UINT16) (~B_PCH_PMC_HOST_MISC_SUS_CFG_BCLK_S3));
}