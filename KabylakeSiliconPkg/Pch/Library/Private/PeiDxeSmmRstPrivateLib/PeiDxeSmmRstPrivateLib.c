/** @file
 Routines for Rst remapping

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2020 Intel Corporation.

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

#include <Private/Library/RstPrivateLib.h>
#include <PchPcieStorageDetectHob.h>

#ifndef MINTREE_FLAG
/**
Checks if given cycle router is in fuse enabled state

  @param[in]  CrNumber         Cycle Router Number
  @param[in]  SataRegBase      Sata Pci Base

  @retval BOOLEAN              TRUE if CR is fuse enabled
**/
BOOLEAN
RstIsCrFuseEnabled (
  IN  UINT32                   CrNumber,
  IN  UINTN                    SataRegBase
)
{
  if (MmioRead32 (SataRegBase + R_PCH_RST_PCIE_STORAGE_CRGC) & (BIT16 << CrNumber)) {
    return TRUE;
  } else {
    return FALSE;
  }
}
#endif //MINTREE_FLAG
/**
  Checks whether device on given Root Port is remap capable

  @param[in] RpNumber                   Root Port Number
  @param[in] TempPciBus                 Temporary Pci Bus

  @retval UINT8                         Device Programming Interface
**/
UINT8
RstGetProgInterfaceForRemapDevice (
  IN UINT32        RpNumber,
  IN UINT32        TempPciBus
)
{
  UINTN           RpDevice;
  UINTN           RpFunction;
  UINT8           BusNumber;
  UINTN           EpBase;
  UINT8           PiInterface;
  UINTN           RpBase;
  UINT8           ClassCode;
  UINT8           SubClassCode;


  DEBUG ((DEBUG_INFO, "Detect storage device on Rp: %d\n", RpNumber));

  GetPchPcieRpDevFun (RpNumber, &RpDevice, &RpFunction);
  BusNumber = DEFAULT_PCI_BUS_NUMBER_PCH;
  PiInterface = RST_PCIE_STORAGE_INTERFACE_NONE;
  RpBase = MmPciBase (BusNumber, (UINT32) RpDevice, (UINT32) RpFunction);

  if (MmioRead16 (RpBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    DEBUG((DEBUG_INFO, "RstGetProgInterfaceForRemapDevices: RootPort does not exists Rp = %d\n", RpNumber));

    return PiInterface;
  }

  //
  // Assign Temporary Bus Number
  //
  MmioAndThenOr32 (
    RpBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET,
    (UINT32) ~B_PCI_BRIDGE_BNUM_SBBN_SCBN,
    ((UINT32) (TempPciBus << 8)) | ((UINT32) (TempPciBus << 16))
    );

  //
  // A config write is required in order for the device to re-capture the Bus number,
  // according to PCI Express Base Specification, 2.2.6.2
  // Write to a read-only register VendorID to not cause any side effects.
  //
  EpBase  = MmPciBase (TempPciBus, 0, 0);
  MmioWrite16 (EpBase + PCI_VENDOR_ID_OFFSET, 0);

  //
  // Read Vendor Id to check if device exists
  // if not clear bus number and return RST_PCIE_STORAGE_INTERFACE_NONE
  //
  if (MmioRead16 (EpBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    MmioAnd32 (RpBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, (UINT32) ~B_PCI_BRIDGE_BNUM_SBBN_SCBN);
    return PiInterface;
  }

  ClassCode = MmioRead8 (EpBase + R_PCI_BCC_OFFSET);
  SubClassCode = MmioRead8 (EpBase + R_PCI_SCC_OFFSET);
  PiInterface = MmioRead8 (EpBase + R_PCI_PI_OFFSET);

  if ( ClassCode == PCI_CLASS_MASS_STORAGE) {
    DEBUG ((DEBUG_INFO, "RstGetProgInterfaceForRemapDevice: ClassCode = %X, SubClassCode = %X,  PiInterface = %X\n", ClassCode, SubClassCode, PiInterface));
    switch (SubClassCode) {
      case PCI_CLASS_MASS_STORAGE_AHCI:
        if (PiInterface == RST_PCIE_STORAGE_INTERFACE_AHCI) {
          DEBUG ((DEBUG_INFO, "RstGetProgInterfaceForRemapDevice: AHCI Card found on Rp: %d\n", RpNumber));
          PiInterface = RST_PCIE_STORAGE_INTERFACE_AHCI;
        }
        break;
      case PCI_CLASS_MASS_STORAGE_NVME:
        if (PiInterface == RST_PCIE_STORAGE_INTERFACE_NVME) {
          DEBUG ((DEBUG_INFO, "RstGetProgInterfaceForRemapDevice: NVMe Card found on Rp: %d\n", RpNumber));
          PiInterface = RST_PCIE_STORAGE_INTERFACE_NVME;
        }
        break;
      case PCI_CLASS_MASS_STORAGE_RAID:
        DEBUG ((DEBUG_INFO, "RstGetProgInterfaceForRemapDevice: RAID Card found on Rp: %d\n", RpNumber));
        PiInterface = RST_PCIE_STORAGE_INTERFACE_NVME;
        break;
      default:
        PiInterface = RST_PCIE_STORAGE_INTERFACE_NONE;
        break;
    }
  } else {
    PiInterface = RST_PCIE_STORAGE_INTERFACE_NONE;
  }
  //
  // Clear temporary bus number
  //
  MmioAnd32 (RpBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, (UINT32) ~B_PCI_BRIDGE_BNUM_SBBN_SCBN);

  return PiInterface;

}

/**
  Check the lane occupied by certain root port according to the root port number and configuration strap
  Return 8-bit bitmap where each bit represents the lane number (e.g.: return 00000011b means the root port owns 2 lane)

  @param[in] RootPortNum            Root Port Number

  @retval UINT8                     Lane Occupied by the Root Port (bitmap)
**/
UINT8
RstGetRpLaneOccupyMask (
  IN  UINT32                   RootPortNum
  )
{
  EFI_STATUS              Status;
  UINT32                  CtrlNum;
  UINT32                  CtrlFirstRpNum;
  UINT32                  Data32;
  UINT8                   LaneOccupied;

  LaneOccupied          = 0;

  CtrlNum = RootPortNum / PCH_PCIE_CONTROLLER_PORTS;
  CtrlFirstRpNum = CtrlNum * PCH_PCIE_CONTROLLER_PORTS;

  //
  // Read the Root Port Configuration Straps for the link width, and return LaneOccupied by the Root Port accordingly
  //
  Status = PchSbiRpPciRead32 (CtrlFirstRpNum, R_PCH_PCIE_STRPFUSECFG, &Data32);
  ASSERT_EFI_ERROR (Status);

  switch ((Data32 & B_PCH_PCIE_STRPFUSECFG_RPC) >> N_PCH_PCIE_STRPFUSECFG_RPC) {
    case V_PCH_PCIE_STRPFUSECFG_RPC_4:
      if (RootPortNum % 4 == 0) {
        LaneOccupied = (BIT3|BIT2|BIT1|BIT0);
      }
      break;
    case V_PCH_PCIE_STRPFUSECFG_RPC_2_2:
      if ((RootPortNum % 2 == 0)) {
        LaneOccupied = (BIT1|BIT0);
      }
      break;
    case V_PCH_PCIE_STRPFUSECFG_RPC_2_1_1:
      if (RootPortNum % 4 == 0) {
        LaneOccupied = (BIT1|BIT0);
      } else if (RootPortNum % 4 != 1) {
        LaneOccupied = BIT0;
      }
      break;
    case V_PCH_PCIE_STRPFUSECFG_RPC_1_1_1_1:
      LaneOccupied = BIT0;
      break;
    default:
      break;
  }

  return LaneOccupied;
}

/**
  Checks PCH generation and returns SATA's GCR.PLS bit number according to root port number with a PCIe storage device
  connected to.

  @param[in] RootPortNum        Root port number which PCIe storage device is connected to

  @retval UINT32                Number of GCR.PLS bit representing root port
**/
UINT32
RstPlsBitNumber (
  IN UINT32           RootPortNum
  )
{
  if ((GetPchGeneration () == KblPch) && (RstGetCycleRouterNumber (RootPortNum) == RST_PCIE_STORAGE_CR_2)) {
    return RootPortNum - 2 * PCH_PCIE_CONTROLLER_PORTS;
  } else {
    return RootPortNum;
  }
}

/**
  Checks if device with given PCI config space address is Intel's Stony Beach.

  @param[in] EndPointPciBase    Address of device's PCI config space

  @retval BOOLEAN               TRUE if device is Intel's Stony Beach, FALSE othrwise
**/
BOOLEAN
RstIsStonyBeach (
  IN UINTN            EndPointPciBase
  )
{
  UINT16              DeviceVendorId;
  UINT16              DeviceDeviceId;

  DeviceVendorId = MmioRead16 (EndPointPciBase + PCI_VENDOR_ID_OFFSET);
  DeviceDeviceId = MmioRead16 (EndPointPciBase + PCI_DEVICE_ID_OFFSET);

  if (DeviceVendorId == RST_STONY_BEACH_VENDOR_ID && DeviceDeviceId == RST_STONY_BEACH_DEVICE_ID) {
    return TRUE;
  }

  return FALSE;
}


#ifndef MINTREE_FLAG
/**
  Check for mismatch in Pcie straps

  @param[in] RootPortLane        Lanes occupied by storage device
  @param[in] PortNum             Root Port Number
  @param[in] SataRegBase         Sata Pci Base

  @retval BOOLEAN                TRUE if mismatch occured FALSE otherwise
**/
BOOLEAN
RstIsRemapConfigValid (
  IN  UINT8        RootPortLane,
  IN  UINT32       PortNum,
  IN  UINTN        SataRegBase
  )
{
  UINT32    PortConfigurationCheck;
  UINT32    CycleRouterNum;

  CycleRouterNum = RstGetCycleRouterNumber (PortNum);

  //
  // Set RST PCIe Storage Cycle Router Accessibility Select, Sata offset FC0h bit [1:0] based on CR#
  //
  MmioWrite8 (SataRegBase + R_PCH_RST_PCIE_STORAGE_CRGC, (UINT8) CycleRouterNum);

  //
  // Check for mismatching configuration
  // Set "PCIe Lane Selected (PLS)" Bit[RP#], Sata PCI offset 300h[RP#] to 1
  //
  MmioAndThenOr32 (SataRegBase + R_PCH_RST_PCIE_STORAGE_GCR, (UINT32) ~(B_PCH_RST_PCIE_STORAGE_GCR_PLS), (UINT32) RootPortLane << (RstPlsBitNumber (PortNum) + 1));

  //
  // Clear PCCS, Sata PCI offset 304h [30], then read the value of PCCS
  //
  MmioOr32 (SataRegBase + R_PCH_RST_PCIE_STORAGE_GSR, (UINT32) B_PCH_RST_PCIE_STORAGE_GSR_PCCS);
  PortConfigurationCheck = MmioRead32 (SataRegBase + R_PCH_RST_PCIE_STORAGE_GSR) & (UINT32) B_PCH_RST_PCIE_STORAGE_GSR_PCCS;

  //
  // Clear "PCIe Lane Selected (PLS)", Sata PCI offset 300h [20:1] to 0
  //
  MmioAnd32 (SataRegBase + R_PCH_RST_PCIE_STORAGE_GCR, (UINT32) ~(B_PCH_RST_PCIE_STORAGE_GCR_PLS));

  //
  // If PCCS value is 1, a mismatch configuration is occurred, skip this root port and proceed to next root port
  //
  if (PortConfigurationCheck) {
    return TRUE;
  } else {
    return FALSE;
  }
}
#endif //MINTREE_FLAG
