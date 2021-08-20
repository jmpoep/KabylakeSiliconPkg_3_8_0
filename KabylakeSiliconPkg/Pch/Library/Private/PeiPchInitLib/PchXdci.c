/**@file
  This is the code that initializes xDCI.

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
#include "PchInitPei.h"

#define XDCI_WAIT_FOR_DRD_MODE  1000
#define XDCI_WAIT_FOR_D3        10000   ///< Timeout of 10000 * 10us = 100ms
#define HUNDRED_US_TIMEOUT      100

/**
  Configures PCH USB device (xDCI)

  @param[in]  SiPolicy          The SI Policy PPI instance
  @param[in]  TempMemBaseAddr   Temporary Memory Base Address for PCI
                                devices to be used to initialize MMIO
                                registers.

  @retval EFI_SUCCESS           The function completed successfully
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
ConfigureXdci (
  IN  SI_POLICY_PPI            *SiPolicy,
  IN  UINT32                    TempMemBaseAddr
  )
{
  UINTN              XhciPciMmBase;
  UINTN              XdciPciMmBase;
  UINT32             WaitForTimeout;
  UINT32             MmioBase;
  UINT32             PchPwrmBase;
  PCH_SERIES         PchSeries;
  PCH_STEPPING       PchStep;
  EFI_STATUS         Status;
  PCH_USB_CONFIG     *UsbConfig;
  UINT16             Data16;

  MmioBase = TempMemBaseAddr;

  XdciPciMmBase   = MmPciBase (
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PCI_DEVICE_NUMBER_PCH_XDCI,
                      PCI_FUNCTION_NUMBER_PCH_XDCI
                      );

  if (MmioRead16 (XdciPciMmBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "xDCI: Pci device NOT found\n"));
    return EFI_NOT_FOUND;
  }

  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsbConfigGuid, (VOID *) &UsbConfig);
  ASSERT_EFI_ERROR (Status);

  //
  //  BIOS Function Disable of xDCI
  //
  //  Note: This DUAL_ROLE_CFG register is in the xHCI MMIO,
  //  instead of xDCI space, because this is a OTG function.
  //

  XhciPciMmBase   = MmPciBase (
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PCI_DEVICE_NUMBER_PCH_XHCI,
                      PCI_FUNCTION_NUMBER_PCH_XHCI
                      );

  //
  //  Enabling Trunk Clock Gating
  //  Set bit [5:0]=6'b111111
  //
  PchPcrAndThenOr32 (
    PID_OTG, R_PCH_PCR_OTG_IOSF_PMCTL,
    (UINT32) ~(0),
    (BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0)
    );

  //
  //  Enabling Trunk Clock Gating
  //  Set bit [2]=1'b1
  //
  PchPcrAndThenOr16 (
    PID_OTG, R_PCH_PCR_OTG_IOSF_A2,
    (UINT16) ~(0),
    (BIT2)
    );

  if (UsbConfig->XdciConfig.Enable == 0) {
    DEBUG ((DEBUG_INFO, "xDCI: Device disabled\n"));

    //
    // Assign memory resources for xHCI
    //
    MmioWrite32 (XhciPciMmBase + R_PCH_XHCI_MEM_BASE, MmioBase);
    MmioOr16 ((UINTN) (XhciPciMmBase + PCI_COMMAND_OFFSET), (UINT16) EFI_PCI_COMMAND_MEMORY_SPACE);

    //
    //  1.  BIOS has to set the DRD mux to host mode in the xHCI MMIO space by using the SW ID flow,
    //  by first setting DUAL_ROLE_CFG0.SW_IDPIN_EN (bit 21) to 1.
    //  Address Offset: 80D8-80DBh
    //  [21] 1b
    //
    MmioOr32 (
      (MmioBase + R_PCH_XHCI_DUAL_ROLE_CFG0),
      (UINT32) (BIT21)
      );

    //
    //  2.  Clear DUAL_ROLE_CFG0.SW_IDPIN (bit 20) to 0.
    //  Address Offset: 80D8-80DBh
    //  [20] 0b
    //
    MmioAnd32 (
      (MmioBase + R_PCH_XHCI_DUAL_ROLE_CFG0),
      (UINT32) ~(BIT20)
      );

    //
    //  3.  Wait for host owned (DUAL_ROLE_CFG1 bit 29) SS DRD mode to be 1.
    //
    WaitForTimeout = 0;
    while (((MmioRead32 (MmioBase + R_PCH_XHCI_DUAL_ROLE_CFG1) & (BIT29)) == 0) &&
           (WaitForTimeout < XDCI_WAIT_FOR_DRD_MODE)) {
      MicroSecondDelay (HUNDRED_US_TIMEOUT);
      WaitForTimeout++;
    }

    //
    // Clear memory resources for xHCI
    //
    MmioAnd16 ((UINTN) (XhciPciMmBase + PCI_COMMAND_OFFSET), (UINT16) (~EFI_PCI_COMMAND_MEMORY_SPACE));
    MmioWrite32 (XhciPciMmBase + R_PCH_XHCI_MEM_BASE, 0);

    //
    // Assign memory resources for xDCI
    //
    MmioWrite32 (XdciPciMmBase + R_PCH_XDCI_MEM_BASE, MmioBase);
    MmioOr16 ((UINTN) (XdciPciMmBase + PCI_COMMAND_OFFSET), (UINT16) EFI_PCI_COMMAND_MEMORY_SPACE);

    //
    //  4. Set xDCIBAR + C110h [1] to 1b
    //
    MmioOr32 (MmioBase + R_PCH_XDCI_GCTL,
      B_PCH_XDCI_GCTL_GHIBEREN
      );

    //
    //  5. Set the following bit to 1 to enable the USB2 PHY suspend if no XDCI driver is not loaded.
    //  Set xDCIBAR + C200h [6] to 1b
    //
    MmioOr32 (MmioBase + R_PCH_XDCI_GUSB2PHYCFG,
      B_PCH_XDCI_GUSB2PHYCFG_SUSPHY
      );

    //
    //  6. Set xDCIBAR + C2C0h [27] to 1b
    //
    MmioOr32 (MmioBase + R_PCH_XDCI_GUSB3PIPECTL0,
      B_PCH_XDCI_GUSB3PIPECTL0_UX_IN_PX
      );

    //
    //  7.  Put xDCI into D3 (APBFC_U3PMU_CFG4[1:0] =2'b11)
    //  Address Offset: 0x10F818
    //  [1:0]=2'b11
    //
    MmioOr16 (
      MmioBase + R_PCH_XDCI_APBFC_U3PMU_CFG4,
      (UINT32) (BIT1 | BIT0)
      );

    //
    //  8.  Wait for D3 (APBFC_U3PMU_CFG2[11:8] =4'b1111)
    //  Address Offset: 0x10F810
    //
    WaitForTimeout = 0;
    Data16 = MmioRead16 (MmioBase + R_PCH_XDCI_APBFC_U3PMU_CFG2);
    while (((Data16 & (BIT11 | BIT10 | BIT9 | BIT8)) != 0xF00) &&
           (WaitForTimeout < XDCI_WAIT_FOR_D3)) {
      MicroSecondDelay (10);
      WaitForTimeout++;
      Data16 = MmioRead16 (MmioBase + R_PCH_XDCI_APBFC_U3PMU_CFG2);
    }

    //
    // Clear memory resources for xDCI
    //
    MmioAnd16 ((UINTN) (XdciPciMmBase + PCI_COMMAND_OFFSET), (UINT16) (~EFI_PCI_COMMAND_MEMORY_SPACE));
    MmioWrite32 (XdciPciMmBase + R_PCH_XDCI_MEM_BASE, 0);

    //
    //  9.  Set the CPGE D3-Hot to Enable( xDCI cfg space 0xA2 bit [2:1] =2'b10)
    //
    MmioAndThenOr16 (
      (XdciPciMmBase + R_PCH_XDCI_CPGE),
      (UINT16) ~(BIT1),
      (UINT16) (BIT2)
      );

    //
    //  10.  Set the PMCSR to D3 ( XDCI cfg space 0x84 bit [1:0] =2'b11)
    //
    MmioOr32 (
      XdciPciMmBase + R_PCH_XDCI_PMCSR,
      (UINT32) (BIT1 | BIT0)
      );

    PchSeries = GetPchSeries ();
    PchStep   = PchStepping ();
    //
    // Disable xDCI function.
    //
    PsfDisableXdciDevice ();

    ///
    /// Set PWRMBASE + 0x628 [24] = 1b to disable XDCI Controller in PMC
    /// This bit is only available on B0 onward.
    /// No need to clear this non-static PG bit while IP re-enabled since it's reset to 0 when PLTRST.
    ///
    PchPwrmBaseGet (&PchPwrmBase);
    if ((PchSeries == PchLp) && (PchStep >= PchLpB0)) {
      MmioOr32 (PchPwrmBase + R_PCH_PWRM_NST_PG_FDIS_1, B_PCH_PWRM_NST_PG_FDIS_1_XDCI_FDIS_PMC);
    }

  } else {

    //
    // Assign memory resources for xHCI
    //
    MmioWrite32 (XhciPciMmBase + R_PCH_XHCI_MEM_BASE, MmioBase);
    MmioOr16 ((UINTN) (XhciPciMmBase + PCI_COMMAND_OFFSET), (UINT16) EFI_PCI_COMMAND_MEMORY_SPACE);

    //
    //  Set DUAL_ROLE_CFG0, xHCIBAR +80D8h bit [21, 20] to [0, 0]
    //
    MmioAnd32 (
      (MmioBase + R_PCH_XHCI_DUAL_ROLE_CFG0),
      (UINT32) ~(BIT21 | BIT20)
      );

    //
    // Clear memory resources for xHCI
    //
    MmioAnd16 ((UINTN) (XhciPciMmBase + PCI_COMMAND_OFFSET), (UINT16) (~EFI_PCI_COMMAND_MEMORY_SPACE));
    MmioWrite32 (XhciPciMmBase + R_PCH_XHCI_MEM_BASE, 0);

    //
    // Set the CPGE D3-Hot to Enable
    // xDCI cfg space 0xA2 bit [2:1] = 2'b10
    //

    MmioAndThenOr16 (
      (XdciPciMmBase + R_PCH_XDCI_CPGE),
      (UINT16) ~(BIT1),
      (UINT16) (BIT2)
      );
  }

  return EFI_SUCCESS;
}
