/** @file
  PCH xHCI Sx handler implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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

#include <Library/TimerLib.h>
#include "PchInitSmm.h"

/**
  xHCI Sx entry handler
**/
VOID
PchXhciSxCallback (
  EFI_SLEEP_TYPE  SxType
  )
{
  UINTN      XhciPciMmBase;
  UINT8      OrgCmdByte;
  UINT16     OrgPmcs;
  UINT32     OrgMmioAddr;
  UINT32     OrgMmioHAddr;
  UINT32     XhciMmioBase;
  #ifndef MINTREE_FLAG
  UINT8      Usb3SsicMode;
  UINT32     Usb2PortCount;
  UINT32     Usb3PortCount;
  UINT32     UsbPortIndex;
  UINT32     PortScxUsb3;
  UINT32     Usb3PortScOffset;
  UINT32     LoopCount;
  #endif //MINTREE_FLAG

  XhciPciMmBase = MmPciBase (
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_XHCI,
                    PCI_FUNCTION_NUMBER_PCH_XHCI
                    );

  ///
  /// Save Cmd and XhciBar and Pmcs registers
  ///
  OrgCmdByte     = MmioRead8  (XhciPciMmBase + PCI_COMMAND_OFFSET);
  OrgPmcs        = MmioRead16 (XhciPciMmBase + R_PCH_XHCI_PWR_CNTL_STS);
  OrgMmioAddr    = MmioRead32 (XhciPciMmBase + R_PCH_XHCI_MEM_BASE) & 0xFFFF0000;
  OrgMmioHAddr   = MmioRead32 (XhciPciMmBase + R_PCH_XHCI_MEM_BASE + 4);

  ///
  /// Use the reserved MMIO
  /// Clear MSE before changing MMIO address
  ///
  MmioAnd8 (XhciPciMmBase + PCI_COMMAND_OFFSET, (UINT8)~(EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));
  MmioWrite32 (XhciPciMmBase + R_PCH_XHCI_MEM_BASE, (UINT32) mXhciMmioBaseAddr);
  MmioWrite32 (XhciPciMmBase + R_PCH_XHCI_MEM_BASE + 4, 0);

  ///
  /// Set MSE
  ///
  MmioOr8 (XhciPciMmBase + PCI_COMMAND_OFFSET, (EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));

  XhciMmioBase = (UINT32) mXhciMmioBaseAddr;

  #ifndef MINTREE_FLAG
  //
  // Bring device to D0
  //
  MmioAnd8 (XhciPciMmBase + R_PCH_XHCI_PWR_CNTL_STS, (UINT8)~(B_PCH_XHCI_PWR_CNTL_STS_PWR_STS));

  Usb2PortCount = (MmioRead32 (XhciMmioBase + R_PCH_XHCI_XECP_SUPP_USB2_2) & 0x0000FF00) >> 8;
  Usb3PortCount = (MmioRead32 (XhciMmioBase + R_PCH_XHCI_XECP_SUPP_USB3_2) & 0x0000FF00) >> 8;

  for (UsbPortIndex = 0; UsbPortIndex < Usb3PortCount; UsbPortIndex++) {
    Usb3PortScOffset = R_PCH_LP_XHCI_PORTSC01USB2 + (0x10 * (Usb2PortCount + UsbPortIndex));
    PortScxUsb3 = MmioRead32 (XhciMmioBase + Usb3PortScOffset);
    if (PortScxUsb3 & B_PCH_XHCI_PORTSCXUSB3_CAS) {
      //
      // Issue Warm Port Reset on USB3 Port with CAS bit set
      //
      MmioOr32 (
        XhciMmioBase + Usb3PortScOffset,
        B_PCH_XHCI_PORTSCXUSB3_WPR
        );
      MicroSecondDelay(50);
      LoopCount = 10;
      while ((MmioRead32 (XhciMmioBase + Usb3PortScOffset) & B_PCH_XHCI_PORTSCXUSB3_PR) && (LoopCount != 0)) {
        MicroSecondDelay(100);
        LoopCount--;
      }

      //
      // Clear WPC and PRC status bits
      //
      MmioOr32 (
        XhciMmioBase + Usb3PortScOffset,
        (B_PCH_XHCI_PORTSCXUSB3_WRC | B_PCH_XHCI_PORTSCXUSB3_PRC)
        );
    }
  }

  if (SxType == SxS3) {
    //
    // If any USB3 ports are configured for SSIC
    //
    Usb3SsicMode = MmioRead8 (XhciMmioBase + R_PCH_XHCI_STRAP2) & B_PCH_XHCI_STRAP2_USB3_SSIC_MODE;
    if (Usb3SsicMode > 0) {
      ///
      /// Bring device to D0
      ///
      MmioAnd8 (XhciPciMmBase + R_PCH_XHCI_PWR_CNTL_STS, (UINT8)~(B_PCH_XHCI_PWR_CNTL_STS_PWR_STS));

      ///
      /// Set D3HE Bit
      ///
      MmioOr8 (XhciPciMmBase + R_PCH_XHCI_PCE, B_PCH_XHCI_PCE_D3HE);

      ///
      /// Restore XHCI Pwer Cntr Sts
      ///
      MmioWrite16 (XhciPciMmBase + R_PCH_XHCI_PWR_CNTL_STS, OrgPmcs);

      ///
      /// 20 uS delay
      ///
      MicroSecondDelay (20);
    }
    ///
    /// If in D0, need to place in D3 for 10us to allow power gating
    ///
    if ((MmioRead8 (XhciPciMmBase + R_PCH_XHCI_PWR_CNTL_STS) & V_PCH_XHCI_PWR_CNTL_STS_PWR_STS_D3) == 0) {
      ///
      /// Set SSLTCGE Bit
      ///
      MmioOr8 (XhciPciMmBase + R_PCH_XHCI_XHCLKGTEN, B_PCH_XHCI_XHCLKGTEN_SSLTCGE);
      ///
      /// Set D3HE Bit
      ///
      MmioOr8 (XhciPciMmBase + R_PCH_XHCI_PCE, B_PCH_XHCI_PCE_D3HE);
      ///
      /// Bring device to D3 for 10 us
      ///
      MmioOr8 (XhciPciMmBase + R_PCH_XHCI_PWR_CNTL_STS, (UINT8)(B_PCH_XHCI_PWR_CNTL_STS_PWR_STS));
      ///
      /// 10 uS delay
      ///
      MicroSecondDelay (10);
    }

    if (GetPchSeries () == PchLp) {
      //
      // Bring device to D0
      //
      MmioAnd8 (XhciPciMmBase + R_PCH_XHCI_PWR_CNTL_STS, (UINT8)~(B_PCH_XHCI_PWR_CNTL_STS_PWR_STS));

      ///
      /// AUX_CTRL_REG - AUX Reset Control
      /// Address Offset: 80C0-80C3h
      /// [10] 1b
      ///
      MmioOr32 (XhciMmioBase + R_PCH_XHCI_AUX_CTRL_REG, (UINT32) (BIT10));
    }
  }
  #endif //MINTREE_FLAG
  ///
  /// Restore Cmd and XhciBar and Pmcs registers
  ///
  MmioWrite32 (XhciPciMmBase + R_PCH_XHCI_MEM_BASE + 4, OrgMmioHAddr);
  MmioWrite32 (XhciPciMmBase + R_PCH_XHCI_MEM_BASE, OrgMmioAddr);
  MmioWrite8 (XhciPciMmBase + PCI_COMMAND_OFFSET, OrgCmdByte);
  ///
  /// Bring device to D3
  ///
  MmioOr8 (XhciPciMmBase + R_PCH_XHCI_PWR_CNTL_STS, (UINT8)(V_PCH_XHCI_PWR_CNTL_STS_PWR_STS_D3));

}