/** @file
  Additional programming steps for disabling IGFX.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 Intel Corporation.

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
#include <Library/DebugLib.h>
#include <Library/MmPciLib.h>
#include <Library/IoLib.h>

///
/// Driver Consumed PPI Prototypes
///
#include <SaPolicyCommon.h>

/**
  Additional steps for disabling IGFX.
  @param[in] GtPreMemConfig  - GRAPHICS_PEI_PREMEM_CONFIG to access the GtPreMemConfig related information
**/
VOID
AdditionalStepsForDisablingIgfx (
  IN       GRAPHICS_PEI_PREMEM_CONFIG   *GtPreMemConfig
  )
{
  UINTN                   McD0BaseAddress;

  DEBUG ((DEBUG_INFO, "Disable IGD Device.\n"));
  ///
  /// Disable IGD device
  ///
  ///
  /// For SKL/KBL
  ///   Set Register D0:F0 Offset 50h [15:8] = '00000000b'.
  /// This prevents UMA memory from being pre-allocated to IGD.
  ///
  /// For SKL/KBL
  ///   Set D0:F0 Offset 50h [7:6] = '00b'.
  /// GTT Graphics Memory Size to 0
  /// Set VGA Disable (IVD) in D0:F0 Offset 50h [1] = '1b'.
  ///
  McD0BaseAddress   = MmPciBase (SA_MC_BUS, 0, 0);
  MmioAndThenOr16 (McD0BaseAddress + R_SA_GGC, (UINT16) ~(B_SKL_SA_GGC_GGMS_MASK | B_SKL_SA_GGC_GMS_MASK), B_SA_GGC_IVD_MASK);

  GtPreMemConfig->GttSize            = 0;
  GtPreMemConfig->IgdDvmt50PreAlloc  = 0;

  ///
  /// Disable IGD. D0.F0.R 054h [4] = '0b'.
  ///
  MmioAnd8 (McD0BaseAddress + R_SA_DEVEN, (UINT8) ~(B_SA_DEVEN_D2EN_MASK));
  return;
}
