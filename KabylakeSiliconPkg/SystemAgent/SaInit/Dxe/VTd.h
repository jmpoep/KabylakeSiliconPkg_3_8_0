/** @file
  This code provides a initialization of intel VT-d (Virtualization Technology for Directed I/O).

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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
#ifndef _VT_D_H_
#define _VT_D_H_

///
/// Include files
///
#include <DmaRemappingTable.h>
#include <SaAccess.h>
#include <PchAccess.h>
#include <Uefi.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Protocol/AcpiTable.h>
#include <Library/MmPciLib.h>
#include <Protocol/SaPolicy.h>
#include <Private/SiConfigHob.h>
#include <Private/PchConfigHob.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>


#define VTD_ECAP_REG  0x10
#define IR            BIT3

/**
  Locate the VT-d ACPI tables data file and read ACPI SSDT tables.
  Publish the appropriate SSDT based on current configuration and capabilities.

  @param[in] SaPolicy            SA DXE Policy protocol

  @retval EFI_SUCCESS - Vtd initialization complete
  @retval Other       - No Vtd function initiated
**/
EFI_STATUS
VtdInit (
  IN  SA_POLICY_PROTOCOL    *SaPolicy
  );

/**
  EndOfDxe routine for update DMAR
**/
VOID
UpdateDmarEndOfDxe (
  VOID
  );
#endif
