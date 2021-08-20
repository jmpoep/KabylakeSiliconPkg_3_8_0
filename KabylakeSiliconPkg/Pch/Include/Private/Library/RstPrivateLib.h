/** @file
  Header file for Rst Library

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016-2017 Intel Corporation.

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

#ifndef _RST_PRIVATE_LIB_
#define _RST_PRIVATE_LIB_
#include <Uefi/UefiBaseType.h>
#include <Library/PchInfoLib.h>
#include <PchLimits.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PchPcieRpLib.h>
#include <Library/MmPciLib.h>
#include <Private/Library/PchInitCommonLib.h>
#include <PcieRegs.h>

#define RST_PCIE_STORAGE_INTERFACE_NONE             0
#define RST_PCIE_STORAGE_INTERFACE_AHCI             1
#define RST_PCIE_STORAGE_INTERFACE_NVME             2

#define RST_STONY_BEACH_VENDOR_ID       0x8086
#define RST_STONY_BEACH_DEVICE_ID       0x2522

#define PCI_CLASS_MASS_STORAGE_NVME     0x08
#define PCI_CLASS_MASS_STORAGE_AHCI     PCI_CLASS_MASS_STORAGE_SATADPA

#ifndef MINTREE_FLAG
/**
  Check if the Cycle Router is fuse enabled

  @param[in] CrNumber               Cycle Router Number
  @param[in] SataRegBase            Sata Controller Pci base

  @retval BOOLEAN                   TRUE for fuse enabled Cycle Router
**/
BOOLEAN
RstIsCrFuseEnabled (
  IN  UINT32                   CrNumber,
  IN  UINTN                    SataRegBase
  );
#endif //MINTREE_FLAG

/**
  Check if there is a remap capable storage device present on Root Port

  @param[in]  RpNumber               Number of a Root Port to check
  @param[in]  TempPciBus             Temporary Pci Bus Number

  @retval  UINT8                     Device Programming interface, 0 if no remap capable device present

**/
UINT8
RstGetProgInterfaceForRemapDevice (
  IN UINT32        RpNumber,
  IN UINT32        TempPciBus
  );

/**
  Check the lane occupied by certain root port according to the root port number and configuration strap
  Return 8-bit bitmap where each bit represents the lane number (e.g.: return 00000011b means the root port owns 2 lane)

  @param[in] RootPortNum            Root Port Number

  @retval UINT8                     Lane Occupied by the Root Port (bitmap)
**/
UINT8
RstGetRpLaneOccupyMask (
  IN  UINT32                   RootPortNum
  );

#ifndef MINTREE_FLAG
/**
  Check if there is a mismatch between Cycle Router Straps and Pcie controller straps

  @param[in] RootPortLane
  @param[in] PortNum                 Root Port Number
  @param[in] SataRegBase             Sata Controller Pci base

  @retval  BOOLEAN                   TRUE if there is a mismatch in straps
**/
BOOLEAN
RstIsRemapConfigValid (
  IN  UINT8          RootPortLane,
  IN  UINT32         PortNum,
  IN  UINTN          SataRegBase
  );
#endif //MINTREE_FLAG

/**
  Checks PCH generation and returns SATA's GCR.PLS bit number according to root port number with a PCIe storage device
  connected to.

  @param[in] RootPortNum        Root port number which PCIe storage device is connected to

  @retval UINT32                Number of GCR.PLS bit representing root port
**/
UINT32
RstPlsBitNumber (
  IN UINT32           RootPortNum
  );

/**
  Checks if device with given PCI config space address is Intel's Stony Beach.

  @param[in] EndPointPciBase    Address of device's PCI config space

  @retval BOOLEAN               TRUE if device is Intel's Stony Beach, FALSE othrwise
**/
BOOLEAN
RstIsStonyBeach (
  IN UINTN            EndPointPciBase
  );
#endif
