/** @file
  Prototype of the DxeAmtPolicyLib library.

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
#ifndef _DXE_AMT_POLICY_LIB_H_
#define _DXE_AMT_POLICY_LIB_H_

#include <Protocol/AmtPolicy.h>

/**
  This function prints the AMT DXE phase policy.

  @param[in] DxeAmtPolicy - AMT DXE Policy protocol
**/
VOID
AmtPrintPolicyProtocol (
  IN  AMT_POLICY_PROTOCOL             *DxeAmtPolicy
  );

/**
  AmtCreatePolicyDefaults creates the default setting of Amt Policy.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[in, out] DxeAmtPolicy          The pointer to get Amt Policy protocol instance

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer

**/
EFI_STATUS
EFIAPI
AmtCreatePolicyDefaults (
  IN OUT  AMT_POLICY_PROTOCOL       **DxeAmtPolicy
  );

/**
  AmtInstallPolicyProtocol installs Amt Policy.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @param[in] ImageHandle                Image handle of this driver.
  @param[in] DxeAmtPolicy               The pointer to Amt Policy Protocol instance

  @retval EFI_SUCCESS                   The policy is installed.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer

**/
EFI_STATUS
EFIAPI
AmtInstallPolicyProtocol (
  IN  EFI_HANDLE                        ImageHandle,
  IN  AMT_POLICY_PROTOCOL               *DxeAmtPolicy
  );

#endif // _DXE_AMT_POLICY_LIB_H_
