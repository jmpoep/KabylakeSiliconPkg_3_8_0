/** @file
  This code provides a initialization of intel VT-d (Virtualization Technology for Directed I/O).

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PostCodeLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/MmPciLib.h>
#include <SaAccess.h>
#include <Private/Library/VtdInitLib.h>
#include <Library/CpuPlatformLib.h>
#include <Private/Library/PchPsfPrivateLib.h>
#include <CpuRegs.h>
#include <Private/SaConfigHob.h>

extern EFI_GUID gSaConfigHobGuid;

/**
  Configure VT-d Base and capabilities.

  @param[in]   VTD_CONFIG                 VTD config block from SA Policy PPI
  @param[in]   SA_MISC_PEI_CONFIG         MISC config block from SA Policy PPI

  @retval EFI_SUCCESS     - Vtd initialization complete
  @exception EFI_UNSUPPORTED - Vtd is not enabled by policy
**/
EFI_STATUS
VtdInit (
  IN       VTD_CONFIG                        *Vtd,
  IN       SA_MISC_PEI_CONFIG                *MiscPeiConfig
  )
{
  UINTN          i;
  UINTN          McD0BaseAddress;
  UINT32         MchBar;
  UINT32         Data32Or;
  UINT32         VtdBase;
  UINT32         VtBarReg [SA_VTD_ENGINE_NUMBER];
  CPU_SKU        CpuSku;
  UINT32         VtdRegOffsetF04;
  UINT32         VtdRegOffsetFF0;
  UINT32         VtdRegOffsetFF4;
  SA_CONFIG_HOB  *SaConfigHob;

  SaConfigHob       = NULL;
  SaConfigHob = GetFirstGuidHob (&gSaConfigHobGuid);
  if (SaConfigHob == NULL) {
    DEBUG ((DEBUG_ERROR, "Failed to retrieve SaConfigHob for VT-d! VT-d cannot be enabled!\n"));
    return EFI_UNSUPPORTED;
  }

  McD0BaseAddress             = MmPciBase (SA_MC_BUS, 0, 0);
  MchBar                      = MmioRead32 (McD0BaseAddress + R_SA_MCHBAR) &~BIT0;
  VtBarReg[0]                 = R_SA_MCHBAR_VTD1_OFFSET;
  VtBarReg[1]                 = R_SA_MCHBAR_VTD2_OFFSET;
  CpuSku                      = GetCpuSku ();

  if ((Vtd->VtdDisable) || (MmioRead32 (McD0BaseAddress + R_SA_MC_CAPID0_A_OFFSET) & BIT23)) {
    DEBUG ((DEBUG_WARN, "VTd disabled or no capability!\n"));
    return EFI_UNSUPPORTED;
  }
  ///
  /// Check SA supports VTD and VTD is enabled in setup menu
  ///
  DEBUG ((DEBUG_INFO, "VTd enabled\n"));

  ///
  /// Enable VTd in PCH
  ///
  PchPsfEnableVtd ();

  ///
  /// 14.1 Program Remap Engine Base Address
  /// Configure VTD1 BAR
  ///
  i = 0;

  ///
  /// Skip GFXVTBAR if IGD is disabled
  ///
  if (MmioRead16 (MmPciBase (SA_MC_BUS, 2, 0) + R_SA_IGD_VID) != 0xFFFF) {
    Data32Or = Vtd->BaseAddress[i];
    Data32Or |= 0x1;
    MmioWrite32 (MchBar + R_SA_MCHBAR_VTD1_OFFSET, Data32Or);
    i++;
  }

  ///
  /// Configure VTD2 BAR
  ///
  Data32Or = Vtd->BaseAddress[i];
  Data32Or |= 0x1;
  MmioWrite32 (MchBar + R_SA_MCHBAR_VTD2_OFFSET, Data32Or);

  for (i = 0; i < SA_VTD_ENGINE_NUMBER; i++) {
    VtdBase = MmioRead32 (MchBar + VtBarReg[i]) & 0xfffffffe;

    ///
    /// skip if the VT bar is 0
    ///
    if (VtdBase == 0) {
      continue;
    }

    ///
    /// Initialize register value before overrides
    /// Register settings will be overridden basing on requirements
    /// All registers will be updated in the end of the loop (for register locking sequence consideration)
    ///
    VtdRegOffsetF04 = MmioRead32 (VtdBase + 0xF04);
    VtdRegOffsetFF4 = MmioRead32 (VtdBase + 0xFF4);
    VtdRegOffsetFF0 = MmioRead32 (VtdBase + 0xFF0);

    if ((VtdRegOffsetFF0 & BIT31) == BIT31) {
      DEBUG ((DEBUG_WARN, "Lock bit of this VT engine has been set. Skip initialization.\n"));
      continue;
    }
    ///
    /// Overrides
    ///
    ///
    /// Set lock bit
    ///
    VtdRegOffsetFF0 |= BIT31;


    if (i == 0) {
      MmioWrite32 (VtdBase + 0x100, 0x50A);
    }

    ///
    /// Program all register after all overrides applied
    ///
    MmioWrite32 (VtdBase + 0xF04, VtdRegOffsetF04);
    MmioWrite32 (VtdBase + 0xFF4, VtdRegOffsetFF4);
    MmioWrite32 (VtdBase + 0xFF0, VtdRegOffsetFF0);

    ///
    /// Check IR status
    ///
    SaConfigHob->VtdData.InterruptRemappingSupport = FALSE;
    if (MmioRead32 (VtdBase + VTD_ECAP_REG) & IR) {
      SaConfigHob->VtdData.InterruptRemappingSupport = TRUE;
    }
  }

  return EFI_SUCCESS;
}
