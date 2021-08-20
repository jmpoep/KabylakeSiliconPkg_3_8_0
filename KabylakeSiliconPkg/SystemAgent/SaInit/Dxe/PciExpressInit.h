/** @file
  Header file for PciExpress Initialization Driver.

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
#ifndef _PCIEXPRESS_INITIALIZATION_DRIVER_H_
#define _PCIEXPRESS_INITIALIZATION_DRIVER_H_

#include <Library/HobLib.h>
#include <IndustryStandard/Pci30.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/UefiLib.h>
#include <Library/PciLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/MmPciLib.h>
#include <Register/Msr.h>
#include <SaAccess.h>
#include <PchAccess.h>
#include <Private/SaConfigHob.h>
#include <Library/CpuPlatformLib.h>
#include <Protocol/SaPolicy.h>
#include <Protocol/SaGlobalNvsArea.h>

#define GEN1      1
#define GEN2      2

///
/// Function prototypes
///
/**
  PCI Express Dxe Initialization.
  Run before PCI Bus Init, where assignment of Bus, Memory,
    and I/O Resources are assigned.

  @param[in] SaPolicy    -     SA DXE Policy protocol

  @retval EFI_SUCCESS        - Pci Express successfully started and ready to be used
  @exception EFI_UNSUPPORTED - Pci Express can't be initialized
**/
EFI_STATUS
PciExpressInit (
  IN SA_POLICY_PROTOCOL *SaPolicy
  );

/**
  Find the Offset to a given Capabilities ID

  @param[in] Bus       -   Pci Bus Number
  @param[in] Device    -   Pci Device Number
  @param[in] Function  -   Pci Function Number
  @param[in] CapId     -   CAPID to search fo

  @retval 0       - CAPID not found
  @retval Other   - CAPID found, Offset of desired CAPID
**/
UINT32
PcieFindCapId (
  IN UINT8   Bus,
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   CapId
  );

/**
  Search and return the offset of desired Pci Express Capability ID

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
  );
#endif
