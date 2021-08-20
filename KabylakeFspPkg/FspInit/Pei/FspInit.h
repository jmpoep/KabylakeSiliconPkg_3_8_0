/** @file
  Header file for FSP Init PEI module

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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

#ifndef _FSP_INIT_PEI_H_
#define _FSP_INIT_PEI_H_

#include <Library/PeiServicesLib.h>
#include <Library/DebugLib.h>
#include <Library/FspCommonLib.h>
#include <FspsUpd.h>
#include <Library/SiPolicyLib.h>
#include <Library/CpuPolicyLib.h>
#include <Library/PeiSaPolicyLib.h>
#include <Library/PchPolicyLib.h>
#include <Library/PeiMePolicyLib.h>
#include <Library/PeiAmtPolicyLib.h>

#define END_OF_GPIO_TABLE   0xFFFFFFFF
#define MAX_GPIO_COUNT 300

/**
  This function performs Active Management PEI Policy update.

  @param[in, out] SiPolicyPpi   The Si Policy PPI instance
  @param[in]      FspsUpd       The pointer of FspsUpd

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
FspUpdatePeiAmtPolicy (
  IN OUT SI_POLICY_PPI    *SiPolicyPpi,
  IN     FSPS_UPD         *FspsUpd
  );

/**
  This function performs CPU PEI Policy initialization.

  @param[in] SiPolicyPpi           The SI Policy PPI instance
  @param[in] FspsUpd               The pointer of FspsUpd

  @retval EFI_SUCCESS              The PPI is installed and initialized.
  @retval EFI ERRORS               The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES     Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
FspUpdatePeiCpuPolicy (
  IN OUT SI_POLICY_PPI        *SiPolicyPpi,
  IN FSPS_UPD                 *FspsUpd
  );

/**
This function performs Security PEI Policy initialization.

@param[in] SiPolicyPpi           The SI Policy PPI instance
@param[in] FspsUpd               The pointer of FspsUpd

@retval EFI_SUCCESS              The PPI is installed and initialized.
@retval EFI ERRORS               The PPI is not successfully installed.
@retval EFI_OUT_OF_RESOURCES     Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
FspUpdatePeiSecurityPolicy(
IN OUT SI_POLICY_PPI        *SiPolicyPpi,
IN FSPS_UPD                 *FspsUpd
);

/**
  This function performs Me PEI Policy update.

  @param[in] SiPolicy       The SI Policy PPI instance
  @param[in] FspsUpd        The pointer of FspsUpd

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
FspUpdatePeiMePolicy (
  IN OUT SI_POLICY_PPI    *SiPolicy,
  IN     FSPS_UPD         *FspsUpd
  );

/**
  This function performs PCH PEI Policy update.

  @param[in, out] SiPolicy      The SI Policy PPI instance
  @param[in]      FspsUpd       The pointer of FspsUpd

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
FspUpdatePeiPchPolicy (
  IN OUT SI_POLICY_PPI     *SiPolicy,
  IN     FSPS_UPD          *FspsUpd
  );

/**
  This function performs SA PEI Policy update.

  @param[in out] SiPolicy          SI_POLICY_PPI PPI
  @param[in]     FspsUpd           The pointer of FspsUpd

  @retval EFI_SUCCESS              The policy is installed and initialized.
**/
EFI_STATUS
FspUpdatePeiSaPolicy (
  IN OUT SI_POLICY_PPI   *SiPolicy,
  IN     FSPS_UPD        *FspsUpd
  );

/**
  This function performs Silicon PEI Policy initialization.

  @param[in] SiPolicy       The Silicon Policy PPI instance
  @param[in] FspsUpd        The pointer of FspsUpd

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
FspUpdatePeiSiPolicy (
  IN OUT SI_POLICY_PPI *SiPolicy,
  IN FSPS_UPD          *FspsUpd
  );
#endif
