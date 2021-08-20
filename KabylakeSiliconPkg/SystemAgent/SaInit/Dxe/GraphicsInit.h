/** @file
  Header file for initialization of GT PowerManagement

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
#ifndef _GRAPHICS_INIT_H_
#define _GRAPHICS_INIT_H_

#include <Library/DxeServicesTableLib.h>
#include <Guid/DxeServices.h>
#include <Protocol/PciHostBridgeResourceAllocation.h>
#include <Library/MmPciLib.h>
#include <SaAccess.h>
#include <Protocol/SaPolicy.h>
#include "SaInitDxe.h"
#include "SaInit.h"
#include <PchAccess.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>

#ifndef MINTREE_FLAG
///
/// Data definitions
///
///
/// GT RELATED EQUATES
///
#define GTT_MEM_ALIGN      24
#define GTTMMADR_SIZE_16MB 0x1000000
#define GT_WAIT_TIMEOUT    3000000     ///< ~3 seconds
#endif //MINTREE_FLAG

/**
  Initialize GT ACPI tables

  @param[in] ImageHandle - Handle for the image of this driver
  @param[in] SaPolicy    - SA DXE Policy protocol

  @retval EFI_SUCCESS          - GT ACPI initialization complete
  @retval EFI_NOT_FOUND        - Dxe System Table not found.
  @retval EFI_OUT_OF_RESOURCES - Mmio not allocated successfully.
**/
EFI_STATUS
GraphicsInit (
  IN EFI_HANDLE             ImageHandle,
  IN SA_POLICY_PROTOCOL     *SaPolicy
  );

#ifndef MINTREE_FLAG
/**
  Do Post GT PM Init Steps after VBIOS Initialization.

  @retval EFI_SUCCESS          Succeed.
**/
EFI_STATUS
PostPmInitEndOfDxe (
  VOID
  );
#endif //MINTREE_FLAG
#endif
