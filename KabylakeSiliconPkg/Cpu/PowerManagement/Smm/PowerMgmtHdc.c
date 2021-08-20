/** @file
  This is the SMM driver HDC SMI interrupt

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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

#include "PowerMgmtSmm.h"
#include "CpuDataStruct.h"


/**
  HDC Callback

  This function is called via SMI from ACPI if OSC reports OSPM is HDC capable.
  If Hdc Oob is capable, enable the HDC arch interface via MSR DB0[0].

  Caution: This function may receive untrusted input.
  Variable and ACPINvs are external input, so this function will validate
  its data structure to be valid value.

  @param[in]      DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param[in]      Context         Points to an optional handler context which was specified when the
                                  handler was registered.

  @retval EFI_SUCCESS             The interrupt was handled successfully.
**/
EFI_STATUS
EFIAPI
HdcCallback (
  IN EFI_HANDLE                  DispatchHandle,
  IN EFI_SMM_SW_REGISTER_CONTEXT *DispatchContext
  )
{
  MSR_REGISTER  HdcPkgCtl;
  BOOLEAN       HdcOobCapable;

  HdcOobCapable = (BOOLEAN) (((AsmReadMsr64 (MSR_MISC_PWR_MGMT)) & B_MISC_PWR_MGMT_SDC_OOB_CAPABLE) == B_MISC_PWR_MGMT_SDC_OOB_CAPABLE);

  ///
  /// If HDC OOB is capable, set MSR DB0[0] = 1 to enable HDC Arch interface,
  ///
  if (HdcOobCapable) {
    HdcPkgCtl.Qword = AsmReadMsr64 (MSR_IA32_PKG_HDC_CTL);
    HdcPkgCtl.Dwords.Low |= B_HDC_PKG_CTL_SDC_PACKAGE_ENABLE;
    AsmWriteMsr64 (MSR_IA32_PKG_HDC_CTL, HdcPkgCtl.Qword);
  }

  ///
  /// If HDC OOB interface is not capable, disable HDCE policy in NVS to flag for platform code.
  ///
  if (!HdcOobCapable) {
    mCpuGlobalNvsAreaPtr->EnableHdcPolicy = 0;
  }

  return EFI_SUCCESS;
}

/**
  Initialize the HDC SMI Handler Callback
  @retval EFI_SUCCESS   The driver installes/initialized correctly.
  @retval EFI_NOT_FOUND CPU Data HOB not available.
**/
EFI_STATUS
EFIAPI
InitPowerMgmtHdc (
   VOID
  )
{
  EFI_STATUS             Status;
  EFI_SMM_SW_DISPATCH2_PROTOCOL  *SwDispatch;
  EFI_SMM_SW_REGISTER_CONTEXT    SwContext;
  EFI_HANDLE                     SwHandle;
  CPU_GLOBAL_NVS_AREA_PROTOCOL   *CpuGlobalNvsAreaProtocol;

  ///
  /// Locate CPU Global NVS area
  ///
  Status = gBS->LocateProtocol (&gCpuGlobalNvsAreaProtocolGuid, NULL, (VOID **) &CpuGlobalNvsAreaProtocol);
  ASSERT_EFI_ERROR (Status);
  mCpuGlobalNvsAreaPtr = CpuGlobalNvsAreaProtocol->Area;

  ///
  /// Register HDC SMI handler
  ///
  Status = gSmst->SmmLocateProtocol (&gEfiSmmSwDispatch2ProtocolGuid, NULL, (VOID**)&SwDispatch);
  ASSERT_EFI_ERROR (Status);
  SwContext.SwSmiInputValue = HDC_SMI;
  Status = SwDispatch->Register (SwDispatch, (EFI_SMM_HANDLER_ENTRY_POINT2) HdcCallback, &SwContext, &SwHandle);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}
