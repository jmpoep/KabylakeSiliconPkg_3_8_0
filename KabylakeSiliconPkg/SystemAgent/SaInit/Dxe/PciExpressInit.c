/** @file
  This driver does SA PCI Express ACPI table initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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
#include "PciExpressInit.h"

extern SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL  mSaGlobalNvsAreaProtocol;
extern SA_CONFIG_HOB                          *mSaConfigHob;

/**
  PCI Express Dxe Initialization.
  Run before PCI Bus Init, where assignment of Bus, Memory,
    and I/O Resources are assigned.

  @param[in] SaPolicy     -     SA DXE Policy protocol

  @retval EFI_SUCCESS     - Pci Express successfully started and ready to be used
**/
EFI_STATUS
PciExpressInit (
  IN SA_POLICY_PROTOCOL *SaPolicy
  )
{
  EFI_STATUS                                    Status;
  CPU_SKU                                       CpuSku;
  PCIE_DXE_CONFIG                               *PcieDxeConfig;
  MSR_BROADWELL_PKG_CST_CONFIG_CONTROL_REGISTER Msr;

  Status = GetConfigBlock ((VOID *) SaPolicy, &gPcieDxeConfigGuid, (VOID *)&PcieDxeConfig);
  ASSERT_EFI_ERROR (Status);

  CpuSku = GetCpuSku ();

  Msr.Uint64 = AsmReadMsr64 (MSR_BROADWELL_PKG_CST_CONFIG_CONTROL);
  mSaGlobalNvsAreaProtocol.Area->PackageCstateLimit  = (UINT8) Msr.Bits.Limit;

  mSaGlobalNvsAreaProtocol.Area->PwrDnBundlesGlobalEnable  = 0;

  if (mSaConfigHob != NULL) {
    mSaGlobalNvsAreaProtocol.Area->Peg0PowerDownUnusedBundles  = mSaConfigHob->PowerDownUnusedBundles[0];
    mSaGlobalNvsAreaProtocol.Area->Peg1PowerDownUnusedBundles  = mSaConfigHob->PowerDownUnusedBundles[1];
    mSaGlobalNvsAreaProtocol.Area->Peg2PowerDownUnusedBundles  = mSaConfigHob->PowerDownUnusedBundles[2];
  }
  ///
  /// LTR/OBFF
  ///
  mSaGlobalNvsAreaProtocol.Area->Peg0LtrEnable                = PcieDxeConfig->PegPwrOpt[0].LtrEnable;
  mSaGlobalNvsAreaProtocol.Area->Peg0ObffEnable               = PcieDxeConfig->PegPwrOpt[0].ObffEnable;
  mSaGlobalNvsAreaProtocol.Area->Peg1LtrEnable                = PcieDxeConfig->PegPwrOpt[1].LtrEnable;
  mSaGlobalNvsAreaProtocol.Area->Peg1ObffEnable               = PcieDxeConfig->PegPwrOpt[1].ObffEnable;
  mSaGlobalNvsAreaProtocol.Area->Peg2LtrEnable                = PcieDxeConfig->PegPwrOpt[2].LtrEnable;
  mSaGlobalNvsAreaProtocol.Area->Peg2ObffEnable               = PcieDxeConfig->PegPwrOpt[2].ObffEnable;

  mSaGlobalNvsAreaProtocol.Area->PegLtrMaxSnoopLatency        = LTR_MAX_SNOOP_LATENCY_VALUE;
  mSaGlobalNvsAreaProtocol.Area->PegLtrMaxNoSnoopLatency      = LTR_MAX_NON_SNOOP_LATENCY_VALUE;

  return EFI_SUCCESS;
}

/**
  Find the Offset to a given Capabilities ID
  CAPID list:
    0x01 = PCI Power Management Interface
    0x04 = Slot Identification
    0x05 = MSI Capability
    0x10 = PCI Express Capability

  @param[in] Bus       -   Pci Bus Number
  @param[in] Device    -   Pci Device Number
  @param[in] Function  -   Pci Function Number
  @param[in] CapId     -   CAPID to search for

  @retval 0       - CAPID not found
  @retval Other   - CAPID found, Offset of desired CAPID
**/
UINT32
PcieFindCapId (
  IN UINT8   Bus,
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   CapId
  )
{
  UINTN DeviceBaseAddress;
  UINT8 CapHeader;

  ///
  /// Always start at Offset 0x34
  ///
  DeviceBaseAddress = MmPciBase (Bus, Device, Function);
  CapHeader         = MmioRead8 (DeviceBaseAddress + PCI_CAPBILITY_POINTER_OFFSET);
  if (CapHeader == 0xFF) {
    return 0;
  }

  while (CapHeader != 0) {
    ///
    /// Bottom 2 bits of the pointers are reserved per PCI Local Bus Spec 2.2
    ///
    CapHeader &= ~(BIT1 + BIT0);
    ///
    /// Search for desired CapID
    ///
    if (MmioRead8 (DeviceBaseAddress + CapHeader) == CapId) {
      return CapHeader;
    }

    CapHeader = MmioRead8 (DeviceBaseAddress + CapHeader + 1);
  }

  return 0;
}

/**
  Search and return the offset of desired Pci Express Capability ID
  CAPID list:
    0x0001 = Advanced Error Rreporting Capability
    0x0002 = Virtual Channel Capability
    0x0003 = Device Serial Number Capability
    0x0004 = Power Budgeting Capability

  @param[in] Bus       -   Pci Bus Number
  @param[in] Device    -   Pci Device Number
  @param[in] Function  -   Pci Function Number
  @param[in] CapId     -   Extended CAPID to search for

  @retval 0       - CAPID not found
  @retval Other   - CAPID found, Offset of desired CAPID
**/
UINT32
PcieFindExtendedCapId (
  IN UINT8   Bus,
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT16  CapId
  )
{
  UINTN   DeviceBaseAddress;
  UINT16  CapHeaderOffset;
  UINT16  CapHeaderId;

  ///
  /// Start to search at Offset 0x100
  /// Get Capability Header
  ///
  DeviceBaseAddress = MmPciBase (Bus, Device, Function);
  CapHeaderId     = 0;
  CapHeaderOffset = 0x100;

  while (CapHeaderOffset != 0 && CapHeaderId != 0xFFFF) {
    ///
    /// Search for desired CapID
    ///
    CapHeaderId = MmioRead16 (DeviceBaseAddress + CapHeaderOffset);
    if (CapHeaderId == CapId) {
      return CapHeaderOffset;
    }

    CapHeaderOffset = (MmioRead16 (DeviceBaseAddress + CapHeaderOffset + 2) >> 4);
  }

  return 0;
}
