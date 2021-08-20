/** @file
  PEIM to initialize GMM.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <SaAccess.h>
#include <Library/MmPciLib.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>
#include <Private/Library/GmmInitLib.h>

/**
  GmmInit: Initialize the GMM device
  @param[in] GmmConfig  - GmmConfig to access the GMM Policy related information

**/
VOID
GmmInit (
  IN       GMM_CONFIG     *GmmConfig
  )
{
  UINT32            Data32;
  UINTN             McD0BaseAddress;
  UINT32            MchBarBase;
  UINT32            McD8BaseAddress;

  McD0BaseAddress = MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN);
  McD8BaseAddress = MmPciBase (SA_GMM_BUS_NUM, SA_GMM_DEV_NUM, SA_GMM_FUN_NUM);
  MchBarBase      = MmioRead32 (McD0BaseAddress + 0x48) &~BIT0;

  ///
  /// Read PCI Device 0 offset 0xe8 CAPID0_B register offset 0x8 to check GMM capability
  ///
  Data32 = MmioRead32 (McD0BaseAddress + 0xE8);

  if ((Data32 & 0x100) == 0x100) {
    ///
    /// GMM device not supported
    ///
    DEBUG ((DEBUG_INFO, "\nGMM Device not supported"));
    return;
  }


  if (GmmConfig->GmmEnable == FALSE) {
    ///
    /// Disable device by clearing BIT 15 of DEVEN register
    ///
    MmioAnd32 (McD0BaseAddress + 0x54, 0xFFFF7FFF);
    DEBUG ((DEBUG_INFO, "\nGMM Device has been disabled"));
    return;
  }

}
