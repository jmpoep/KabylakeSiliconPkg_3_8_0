/** @file
  This is the FSP driver that initializes the Intel PCH.

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
#include "PchInit.h"

EFI_STATUS
EFIAPI
PchOnPciEnumCompleteFsp (
  IN  EFI_PEI_SERVICES            **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN  VOID                        *Ppi
  );

STATIC
EFI_PEI_NOTIFY_DESCRIPTOR  mPchOnPciEnumCompleteNotifyList[] = {
  {
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK  | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPciEnumerationCompleteProtocolGuid,
    PchOnPciEnumCompleteFsp
  }
};

EFI_STATUS
EFIAPI
PchReadyToBootEventFsp (
  IN  EFI_PEI_SERVICES            **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN  VOID                        *Ppi
  );

STATIC EFI_PEI_NOTIFY_DESCRIPTOR  mReadyToBootNotifyList[] = {
  {
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK  | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiEventReadyToBootGuid,
    PchReadyToBootEventFsp
  }
};


/**
  <b>FSP PchInit Module Entry Point for FSP</b>\n

  @param[in] FileHandle      PEIM's file handle
  @param[in] PeiServices     An indirect pointer to the EFI_PEI_SERVICES table published by the PEI Foundation

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
PchInitEntryPointFsp (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS  Status;

  DEBUG ((DEBUG_INFO, "PchInitEntryPointFsp() Start\n"));

  PchInitEntryPointCommon ();

  Status = PeiServicesNotifyPpi (mPchOnPciEnumCompleteNotifyList);
  ASSERT_EFI_ERROR (Status);

  Status = PeiServicesNotifyPpi (mReadyToBootNotifyList);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "PchInitEntryPointFsp() End\n"));

  return Status;
}

/**
  Fsp PCH initialization on PCI enumeration complete

  @param[in]  PeiServices       An indirect pointer to the EFI_PEI_SERVICES table published by the PEI Foundation
  @param[in]  NotifyDescriptor  Address of the notification descriptor data structure.
  @param[in]  Ppi               Address of the PPI that was installed.

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
PchOnPciEnumCompleteFsp (
  IN  EFI_PEI_SERVICES            **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN  VOID                        *Ppi
  )
{
  DEBUG ((DEBUG_INFO, "PchOnPciEnumCompleteFsp() Start\n"));

  PchOnPciEnumCompleteCommon ();

  DEBUG ((DEBUG_INFO, "PchOnPciEnumCompleteFsp() End\n"));

  return EFI_SUCCESS;
}

/**
  FSP PCH Ready to boot event handler

  @param[in]  PeiServices       An indirect pointer to the EFI_PEI_SERVICES table published by the PEI Foundation
  @param[in]  NotifyDescriptor  Address of the notification descriptor data structure.
  @param[in]  Ppi               Address of the PPI that was installed.

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
PchReadyToBootEventFsp (
  IN  EFI_PEI_SERVICES            **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN  VOID                        *Ppi
  )
{
  UINTN           XhciMmioBase;
  UINTN           XhciPciMmBase;
  UINT16          XhciPciCommand;
  BOOLEAN         XhciPdoRestartNeeded;

  DEBUG ((DEBUG_INFO, "PchReadyToBootEventFsp() Start\n"));

  // Check if USB PDO programming was skipped during PEI phase
  if (mPchConfigHob->Usb.DelayPdoProgramming == TRUE) {
    XhciPciMmBase = MmPciBase (
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PCI_DEVICE_NUMBER_PCH_XHCI,
                      PCI_FUNCTION_NUMBER_PCH_XHCI
                      );

    // Check if xHCI has memory access
    XhciPciCommand = MmioRead16 (XhciPciMmBase + PCI_COMMAND_OFFSET);
    if ((XhciPciCommand & EFI_PCI_COMMAND_MEMORY_SPACE) == 0x0) {
      DEBUG ((DEBUG_ERROR, "xHCI Controller isn't configured properly\n"));
    } else {
      // Getting base MMIO address for xHCI
      XhciMmioBase = MmioRead32 (XhciPciMmBase + R_PCH_XHCI_MEM_BASE) & (B_PCH_XHCI_MEM_ALIGN_MASK << N_PCH_XHCI_MEM_ALIGN);

      XhciPdoRestartNeeded = UsbPdoProgramming (
                               XhciMmioBase,
                               mPchConfigHob->Usb.Usb2DisabledPorts,
                               mPchConfigHob->Usb.Usb3DisabledPorts
                               );
      // If PDO registers are locked, reset platform to unlock them
      if (XhciPdoRestartNeeded) {
        (*PeiServices)->ResetSystem2 (EfiResetWarm, EFI_SUCCESS, 0, NULL);
      }
    }
  } else {
    DEBUG ((DEBUG_INFO, "PDO register already programmed\n"));
  }

  DEBUG ((DEBUG_INFO, "PchReadyToBootEventFsp() End\n"));

  return EFI_SUCCESS;
}

