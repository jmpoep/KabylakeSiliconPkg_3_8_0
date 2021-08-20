/** @file
  This file contains power management configuration functions for processors.

  <b>Acronyms:</b>
     - PPM:  Processor Power Management
     - TM:   Thermal Monitor
     - IST:  Intel(R) Speedstep technology
     - HT:   Hyper-Threading Technology

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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

#include "PowerMgmtInit.h"

/**
  Retrieve turbo power limit from MCHBAR MMIO and save it to S3 BootScript.
**/
VOID
CtdpS3Save (
  VOID
  )
{
  UINTN        PciD0F0RegBase;
  UINT32       MchBar;
  UINT16       PowerLimit1;
  UINT16       PowerLimit2;
  UINT8        CpuConfigTdpBootLevel;

  CpuConfigTdpBootLevel = gCpuGlobalNvsAreaProtocol->Area->ConfigTdpBootModeIndex;

  ///
  /// Select Ctdp Nominal if Ctdp disabled or boot level not supported.
  ///
  if (CpuConfigTdpBootLevel >= gCpuGlobalNvsAreaProtocol->Area->CtdpLevelsSupported) {
    CpuConfigTdpBootLevel = 0;
  }

  PowerLimit1 = gCpuGlobalNvsAreaProtocol->Area->CtdpLevelSettings[CpuConfigTdpBootLevel].CtdpPowerLimit1;
  PowerLimit2 = gCpuGlobalNvsAreaProtocol->Area->CtdpLevelSettings[CpuConfigTdpBootLevel].CtdpPowerLimit2;
  ///
  /// Check if Power Limits are initalized
  ///
  if (PowerLimit1 != 0 && PowerLimit2 != 0) {
    ///
    /// Get the MCH space base address.
    /// Program Turbo Power Limit MMIO register MCHBAR+0x59A0 Bits [14:0] and [46:32]
    /// for ConfigTdp mode PL1 and PL2
    ///
    PciD0F0RegBase  = MmPciBase (0, 0, 0);
    MchBar          = MmioRead32 (PciD0F0RegBase + 0x48) &~BIT0;
    S3BootScriptSaveMemWrite (
      S3BootScriptWidthUint32,
      (UINTN) (MchBar + MMIO_TURBO_POWER_LIMIT),
      1,
      (VOID *) (UINTN) (MchBar + MMIO_TURBO_POWER_LIMIT)
      );

    S3BootScriptSaveMemWrite (
      S3BootScriptWidthUint32,
      (UINTN) (MchBar + MMIO_TURBO_POWER_LIMIT + 4),
      1,
      (VOID *) (UINTN) (MchBar + MMIO_TURBO_POWER_LIMIT + 4)
      );
  }

}
