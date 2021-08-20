/** @file
  Main implementation source file for the ActiveBios driver

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2005 - 2014 Intel Corporation.

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
#include "ActiveBios.h"

//
// Global data
//
GLOBAL_REMOVE_IF_UNREFERENCED ACTIVE_BIOS_INSTANCE  mPrivateData;

/**
  <b>ActiveBios DXE Module Entry Point</b>\n
  - <b>Introduction</b>\n
    The ActiveBios module is a DXE driver that provides the capability of switching
    the PCH mapping of the memory range from 4 GB - 16 MB to 4 GB to different devices.
    The current code supports mapping the range to LPC/eSPi and SPI.

  - <b>Details</b>\n
    This module is required if you want to support mapping BIOS address space to different
    buses: LPC/eSPI or SPI. The protocol produced by this module allows code to easily switch
    the BIOS mapping. For example: to switch between SPI and FWH if the platform supports both.
      - @note If you do not utilize this module, it may be necessary to modify existing FWH or
        SPI drivers and utilities to remove dependencies on the PCH_ACTIVE_BIOS_PROTOCOL protocol.

  - @pre
    PCH PCR base address configured

  - @result
    The ActiveBios driver produces the @link Include/Protocol/ActiveBios.h PCH_ACTIVE_BIOS_PROTOCOL @endlink

  - <b>Integration Checklists</b>\n
    - Verify prerequisites are met
    - Add ActiveBios\Dxe\ActiveBios.inf to the platform DSC file.

  - <b>Porting Recommendations</b>\n
    Any modification of this module should be done in compliance with the PCH_ACTIVE_BIOS_PROTOCOL protocol definition.
    For some platforms, it may be desirable to add support for PCI BIOS mapping.
    It is unlikely that this module will vary much between PCH generations. It may be desirable
    to port to a single module that supports multiple PCH generations to enable more code sharing.

  @param[in] ImageHandle          Image handle for this driver image
  @param[in] SystemTable          Pointer to the EFI System Table

  @retval EFI_SUCCESS             Application completed successfully
  @exception EFI_UNSUPPORTED      Unsupported chipset detected
**/
EFI_STATUS
EFIAPI
InstallActiveBios (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS  Status;
  EFI_HANDLE  Handle;

  Status  = EFI_SUCCESS;
  Handle  = NULL;


  //
  // Initialize private data
  //
  mPrivateData.Signature  = ACTIVE_BIOS_SIGNATURE;
  mPrivateData.Handle     = ImageHandle;

  //
  // Initialize our ActiveBios protocol
  //
  Status = ActiveBiosProtocolConstructor (&mPrivateData.ActiveBiosProtocol);
  ASSERT_EFI_ERROR (Status);

  return Status;
}
