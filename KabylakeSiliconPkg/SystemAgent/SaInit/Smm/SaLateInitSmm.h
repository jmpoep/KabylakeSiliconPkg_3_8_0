/** @file
  Header file for SA SMM Handler

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2016 Intel Corporation.

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
#ifndef _SaLateInitSmm_H_
#define _SaLateInitSmm_H_

///
/// Driver Consumed Protocol Prototypes
///

#include <Protocol/SmmBase2.h>

#include <Protocol/SaPolicy.h>

/**
  <b>System Agent Initialization SMM Driver Entry Point</b>
  - <b>Introduction</b> \n
    This is an optional driver to support PCIe ASPM initialization later than Option ROM initialization.\n
    In this scenario S3 Save Boot Script table has been closed per security consideration so the ASPM settings will be stored in SMM memory and restored during S3 resume.
    If platform does not support this scenario this driver can be excluded and SI_SA_POLICY_PPI -> PCIE_CONFIG -> InitPcieAspmAfterOprom must be set to FALSE. \n
    Note: When InitPcieAspmAfterOprom enabled, the SMI callback handler must be registered successfully, otherwise it will halt the system.

  - @pre
    - _EFI_SMM_BASE_PROTOCOL (or _EFI_SMM_BASE2_PROTOCOL for EDK2): Provides SMM infrastructure services.
    - _EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL (or _EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL for EDK2): Interface structure for the SMM IO trap specific SMI Dispatch Protocol
    - SA_POLICY_PROTOCOL: A protocol published by a platform DXE module executed earlier; this is documented in this document as well.

  - @result
    PCIe ASPM has been initialized on all end point devices discovered and same settings will be restored during S3 resume.

  @param[in] ImageHandle - The image handle of Wake On Lan driver
  @param[in] SystemTable - The standard EFI system table

  @retval EFI_SUCCESS    - SA SMM handler was installed or not necessary
  @retval EFI_NOT_FOUND  - Fail to register SMI callback or required protocol/hob missing.
**/
EFI_STATUS
EFIAPI
SaLateInitSmmEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );
#endif
