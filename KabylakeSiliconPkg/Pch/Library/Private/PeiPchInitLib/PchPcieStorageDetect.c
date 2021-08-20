/** @file
  Pch Storage Detection Routines

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation.

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

#include "PchInitPei.h"
#include <Private/Library/RstPrivateLib.h>
#include <PchPcieStorageDetectHob.h>

typedef enum {
  Rst1LaneOccupied = 0x01,
  Rst2LanesOccupied = 0x03,
  Rst4LanesOccupied = 0x0F
} RST_LANES_OCCUPIED_MAP;

/**
  Creates a Cycle Router map 1- cycle router can be used for remapping

  @param[in]   SataRegBas      Sata Pci Base
  @param[out]  CrMap           Pointer to cycle router map
**/
STATIC
VOID
CreateCycleRouterMap (
   IN   UINTN          SataRegBase,
   OUT  UINT8          *CrMap
  )
{

  UINT8                 Index;
  UINT32                CycleRouterNum;

  for (Index = 0; Index < PCH_MAX_PCIE_CONTROLLERS; Index++) {
    CycleRouterNum = RstGetCycleRouterNumber (4*Index);
    #ifndef MINTREE_FLAG
    if (CycleRouterNum == RST_PCIE_STORAGE_CR_INVALID || !RstIsCrFuseEnabled (CycleRouterNum, SataRegBase)) {
      CrMap[Index] = RST_PCIE_STORAGE_CR_INVALID;
    } else {
      CrMap[Index] = (UINT8) CycleRouterNum;
    }
    #else //MINTREE_FLAG
    if (CycleRouterNum == RST_PCIE_STORAGE_CR_INVALID) {
      CrMap[Index] = RST_PCIE_STORAGE_CR_INVALID;
    }
    else {
      CrMap[Index] = (UINT8)CycleRouterNum;
    }
    #endif //MINTREE_FLAG
  }

}

/**
  Creates a map that indicates which root ports are occupied by rst remap capable mass storage devices

  @param[in]  SiPolicy         Pointer to SI_POLICY_PPI instance
  @param[in]  TempPciBusMin    Temporary minimal bus number
  @param[in]  TempPciBusMax    Temporary max bus number
**/
VOID
CreateStorageInfoHob (
  IN CONST SI_POLICY_PPI   *SiPolicy,
  IN UINT8                 TempPciBusMin,
  IN UINT8                 TempPciBusMax
  )
{
  UINT8                        RpIndex;
  UINT8                        MaxPcieRootPorts;
  UINT8                        LanesOccupied;
  PCIE_STORAGE_INFO_HOB        PcieStorageInfoHob;
  UINT8                        PiInterface;
  UINTN                        SataRegBase;

  DEBUG((DEBUG_INFO, "CreateStorageInfoHob() Start\n"));

  ZeroMem (&PcieStorageInfoHob, sizeof (PCIE_STORAGE_INFO_HOB));
  MaxPcieRootPorts = GetPchMaxPciePortNum ();
  SataRegBase = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_SATA, PCI_FUNCTION_NUMBER_PCH_SATA);
  PcieStorageInfoHob.Revision = PCIE_STORAGE_INFO_HOB_REVISION;
  CreateCycleRouterMap (SataRegBase, PcieStorageInfoHob.RstCycleRouterMap);

  for (RpIndex = 0; RpIndex < MaxPcieRootPorts; RpIndex++) {

    LanesOccupied = RstGetRpLaneOccupyMask (RpIndex);
    PiInterface = RstGetProgInterfaceForRemapDevice (RpIndex, TempPciBusMin);

    if (PiInterface) {

      #ifndef MINTREE_FLAG
      if (RstIsRemapConfigValid (LanesOccupied, RpIndex, SataRegBase)) {
        DEBUG ((DEBUG_INFO, "CreateStorageInfoHob: mismatch occured on Rp = %d\n", RpIndex));
      } else {
        PcieStorageInfoHob.PcieStorageProgrammingInterface[RpIndex] = PiInterface;
      }
      #else //MINTREE_FLAG
      PcieStorageInfoHob.PcieStorageProgrammingInterface[RpIndex] = PiInterface;
      #endif //MINTREE_FLAG

      switch (LanesOccupied) {
        case Rst4LanesOccupied:
          PcieStorageInfoHob.PcieStorageLinkWidth[RpIndex] = RstLinkWidthX4;
          RpIndex += 3;
          break;
        case Rst2LanesOccupied:
          PcieStorageInfoHob.PcieStorageLinkWidth[RpIndex] = RstLinkWidthX2;
          RpIndex += 1;
          break;
        case Rst1LaneOccupied:
          PcieStorageInfoHob.PcieStorageLinkWidth[RpIndex] = RstLinkWidthX1;
          break;
      }
    }
  }

  BuildGuidDataHob (&gPchPcieStorageDetectHobGuid, (VOID*) &PcieStorageInfoHob, sizeof (PCIE_STORAGE_INFO_HOB));

  DEBUG((DEBUG_INFO, "CreateStorageInfoHob() End\n"));
}
