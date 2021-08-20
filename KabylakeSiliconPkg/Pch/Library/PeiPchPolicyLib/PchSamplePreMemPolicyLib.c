/** @file
  This file is to load sample board policy.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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
#include "PeiPchPolicyLibrary.h"

/*
  Apply sample board PCH specific default settings

  @param[in] SiPreMemPolicy      The pointer to SI PREMEM Policy PPI instance
*/
VOID
EFIAPI
PchLoadSamplePreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI       *SiPreMemPolicy
  )
{
  EFI_STATUS                      Status;
  PCH_TRACE_HUB_PREMEM_CONFIG     *TraceHubPreMemConfig;
  PCH_HSIO_PCIE_PREMEM_CONFIG     *HsioPciePreMemConfig;
  PCH_HSIO_SATA_PREMEM_CONFIG     *HsioSataPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gTraceHubPreMemConfigGuid, (VOID *) &TraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gHsioPciePreMemConfigGuid, (VOID *) &HsioPciePreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gHsioSataPreMemConfigGuid, (VOID *) &HsioSataPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  //
  // TRACEHUB
  //
  TraceHubPreMemConfig->MemReg0Size = 0x100000;  // 1MB
  TraceHubPreMemConfig->MemReg1Size = 0x100000;  // 1MB

  //
  // HSIO PCIE
  //
  HsioPciePreMemConfig->Lane[0].HsioRxSetCtleEnable = TRUE;
  HsioPciePreMemConfig->Lane[0].HsioRxSetCtle = 6;
  HsioPciePreMemConfig->Lane[1].HsioRxSetCtleEnable = TRUE;
  HsioPciePreMemConfig->Lane[1].HsioRxSetCtle = 6;
  HsioPciePreMemConfig->Lane[2].HsioRxSetCtleEnable = TRUE;
  HsioPciePreMemConfig->Lane[2].HsioRxSetCtle = 6;
  HsioPciePreMemConfig->Lane[3].HsioRxSetCtleEnable = TRUE;
  HsioPciePreMemConfig->Lane[3].HsioRxSetCtle = 6;
  HsioPciePreMemConfig->Lane[5].HsioRxSetCtleEnable = TRUE;
  HsioPciePreMemConfig->Lane[5].HsioRxSetCtle = 8;
  HsioPciePreMemConfig->Lane[7].HsioRxSetCtleEnable = TRUE;
  HsioPciePreMemConfig->Lane[7].HsioRxSetCtle = 8;
  HsioPciePreMemConfig->Lane[8].HsioRxSetCtleEnable = TRUE;
  HsioPciePreMemConfig->Lane[8].HsioRxSetCtle = 8;
  HsioPciePreMemConfig->Lane[9].HsioRxSetCtleEnable = TRUE;
  HsioPciePreMemConfig->Lane[9].HsioRxSetCtle = 8;
  HsioPciePreMemConfig->Lane[10].HsioRxSetCtleEnable = TRUE;
  HsioPciePreMemConfig->Lane[10].HsioRxSetCtle = 8;
  HsioPciePreMemConfig->Lane[11].HsioRxSetCtleEnable = TRUE;
  HsioPciePreMemConfig->Lane[11].HsioRxSetCtle = 8;
  HsioPciePreMemConfig->PciePllSsc = 0xFF;

  //
  // HSIO SATA
  //
  HsioSataPreMemConfig->PortLane[0].HsioRxGen3EqBoostMagEnable = TRUE;
  HsioSataPreMemConfig->PortLane[0].HsioRxGen3EqBoostMag = 4;
  HsioSataPreMemConfig->PortLane[0].HsioTxGen1DownscaleAmpEnable = TRUE;
  HsioSataPreMemConfig->PortLane[0].HsioTxGen1DownscaleAmp = 0x2C;
  HsioSataPreMemConfig->PortLane[0].HsioTxGen2DownscaleAmpEnable = 0;
  HsioSataPreMemConfig->PortLane[0].HsioTxGen2DownscaleAmp = 0x38;

}
