/** @file
  Header file for the PCH USB Driver.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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
#ifndef _PCH_USB_H_
#define _PCH_USB_H_
#include "PchInitPei.h"

#define USB_PR_CASE_0           0
#define USB_PR_CASE_1           1
#define USB_PR_CASE_2           2
#define TEN_MS_TIMEOUT          10000
#define PORT_RESET_TIMEOUT      12000  ///< 12000 * 10 us = 120 ms timeout for xHCI port reset, according to USB3 spec
#define XHCI_TEST_MODE_DURATION 100
#define XHCI_TEST_MODE_LOOP     160

typedef struct {
  UINT8   Device;
  UINT8   Function;
} USB_CONTROLLER;

/**
  Configures PCH xHCI device

  @param[in]  SiPolicy            The SI Policy PPI instance
  @param[in] TempMemBaseAddr      Temporary Memory Base Address for PCI
                                  devices to be used to initialize MMIO
                                  registers.

  @retval EFI_INVALID_PARAMETER   The parameter of SiPolicy is invalid
  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
EFIAPI
ConfigureXhci (
  IN  SI_POLICY_PPI   *SiPolicy,
  IN  UINT32          TempMemBaseAddr
  );

#ifndef MINTREE_FLAG
/**
  Performs configuration of PCH xHCI SSIC.

  @param[in] SiPolicy             The SI Policy PPI
  @param[in] XhciMmioBase         Memory base address of xHCI Controller
  @param[in] XhciPciMmBase        XHCI PCI Base Address

**/
VOID
XhciSsicInit (
  IN  SI_POLICY_PPI      *SiPolicy,
  IN  UINT32             XhciMmioBase,
  IN  UINTN              XhciPciMmBase
  );
#endif //MINTREE_FLAG

/**
  Performs basic configuration of PCH USB3 (xHCI) controller.

  @param[in] SiPolicy             The SI Policy PPI
  @param[in] XhciMmioBase         Memory base address of xHCI Controller
  @param[in] XhciPciMmBase        XHCI PCI Base Address

**/
VOID
XhciHcInit (
  IN  SI_POLICY_PPI      *SiPolicy,
  IN  UINT32             XhciMmioBase,
  IN  UINTN              XhciPciMmBase
  );

/**
  Setup XHCI Over-Current Mapping

  @param[in] UsbConfig            The PCH Policy for USB configuration
  @param[in] XhciPciMmBase        XHCI PCI Base Address

**/
VOID
XhciOverCurrentMapping (
  IN  CONST PCH_USB_CONFIG        *UsbConfig,
  IN  UINTN                       XhciPciMmBase
  );

/**
  Program Xhci Port Disable Override

  @param[in] UsbConfig            The PCH Policy for USB configuration
  @param[in] XhciPciMmBase        XHCI PCI Base Address

**/
VOID
XhciPortDisableOverride (
  IN  CONST PCH_USB_CONFIG        *UsbConfig,
  IN  UINTN                       XhciPciMmBase
  );

/**
  Program and enable XHCI Memory Space

  @param[in] UsbConfig            The PCH Policy for USB configuration
  @param[in] XhciMmioBase         Memory base address of XHCI Controller
  @param[in] XhciPciMmBase        XHCI PCI Base Address

**/
VOID
XhciMemorySpaceOpen (
  IN  CONST PCH_USB_CONFIG        *UsbConfig,
  IN  UINT32                      XhciMmioBase,
  IN  UINTN                       XhciPciMmBase
  );

/**
  Clear and disable XHCI Memory Space

  @param[in] UsbConfig            The PCH Policy for USB configuration
  @param[in] XhciMmioBase         Memory base address of XHCI Controller
  @param[in] XhciPciMmBase        XHCI PCI Base Address

**/
VOID
XhciMemorySpaceClose (
  IN  CONST PCH_USB_CONFIG        *UsbConfig,
  IN  UINT32                      XhciMmioBase,
  IN  UINTN                       XhciPciMmBase
  );

/**
  Configure PCH xHCI after initialization

  @param[in]  SiPolicy            The SI Policy PPI instance
  @param[in]  TempMemBaseAddr     Temporary Memory Base Address for PCI
                                  devices to be used to initialize MMIO
                                  registers.

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
ConfigureXhciAfterInit (
  IN  SI_POLICY_PPI    *SiPolicy,
  IN  UINT32           TempMemBaseAddr
  );

/**
  Performs USB3 warm port reset.

  @param[in] XhciMmioBase        XHCI Mmio Base Address

  @retval None
**/
VOID
Usb3WarmPortReset (
  IN  UINT32    XhciMmioBase
  );

/**
  Tune the USB 2.0 high-speed signals quality.

  @param[in]  UsbConfig                 The PCH Policy for USB configuration
  @param[in]  TempMemBaseAddr           The temporary memory base address for PMC device
**/
VOID
Usb2AfeProgramming (
  IN  CONST PCH_USB_CONFIG    *UsbConfig,
  IN  UINT32                  TempMemBaseAddr
  );

/**
  Tune the USB 3.0 signals quality.

  @param[in]  UsbConfig                 The PCH Policy for USB configuration
**/
VOID
XhciUsb3Tune (
  IN  CONST PCH_USB_CONFIG    *UsbConfig
  );

#endif
