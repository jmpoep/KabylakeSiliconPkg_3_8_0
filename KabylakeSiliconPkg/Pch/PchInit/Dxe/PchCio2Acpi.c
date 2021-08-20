/** @file
  Initializes PCH CIO2 device ACPI data.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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

#include <PchInit.h>

/**
  Update ASL definitions for CIO2 device.

  @retval EFI_SUCCESS         The function completed successfully
**/
EFI_STATUS
UpdateCio2AcpiData (
  VOID
  )
{
  UINT32 Index;
  PCH_STEPPING    PchStep;

  DEBUG ((DEBUG_INFO, "UpdateCio2AcpiData() Start\n"));
  PchStep   = PchStepping ();

  //if CIO2 is enabled as ACPI device then update its ACPI data
  if (PchStep >= PchLpC0) {
    mPchNvsAreaProtocol.Area->Cio2EnabledAsAcpiDevice = 0;
    DEBUG ((DEBUG_INFO, "UpdateCio2AcpiData() Cio2 has not been enabled as ACPI device\n"));
  } else {
    mPchNvsAreaProtocol.Area->Cio2EnabledAsAcpiDevice = 0;
    if (mPchConfigHob->Cio2.DeviceEnable == 1) {
      mPchNvsAreaProtocol.Area->Cio2EnabledAsAcpiDevice = 1;
      for (Index = 0; Index < mPchConfigHob->Interrupt.NumOfDevIntConfig; Index++) {
        if ((mPchConfigHob->Interrupt.DevIntConfig[Index].Device == PCI_DEVICE_NUMBER_PCH_CIO2) &&
            (mPchConfigHob->Interrupt.DevIntConfig[Index].Function == PCI_FUNCTION_NUMBER_PCH_CIO2)) {
          mPchNvsAreaProtocol.Area->Cio2IrqNumber = mPchConfigHob->Interrupt.DevIntConfig[Index].Irq;
          DEBUG ((DEBUG_INFO, "UpdateCio2AcpiData() Cio2 has been enabled as ACPI device. Irq number = 0x%x\n", mPchConfigHob->Interrupt.DevIntConfig[Index].Irq));
          break;
        }
      }
    }
  }

  DEBUG ((DEBUG_INFO, "UpdateCio2AcpiData() End\n"));

  return EFI_SUCCESS;
}


