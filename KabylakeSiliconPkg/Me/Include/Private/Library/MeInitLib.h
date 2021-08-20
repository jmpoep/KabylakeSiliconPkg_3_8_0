/** @file
  The PEI Library Implements ME Init.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2008 - 2016 Intel Corporation.

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
#ifndef _ME_INIT_LIB_H_
#define _ME_INIT_LIB_H_

#include <Ppi/SiPolicy.h>

/**
  Check some ME policies are valid for debugging unexpected problem if these
  values are not initialized or assigned incorrect resource.

  @param[in] MePolicyPpi    The Me Policy protocol instance

**/
VOID
MeValidatePolicy (
  IN SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi
  );

/**
  This function performs basic initialization for ME in PEI phase after Policy produced.
**/
VOID
EFIAPI
MeOnPolicyInstalled (
  VOID
  );

/**
  Configure HECI devices on End Of Pei
**/
VOID
MeOnEndOfPei (
  VOID
  );

/**
  Internal function performing Heci PPIs init needed in PEI phase

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_DEVICE_ERROR        ME FPT is bad
**/
EFI_STATUS
InstallHeciPpi (
  VOID
  );

/**
  Initialize HECI devices

  @retval EFI_SUCCESS             HECI devices initialize succeefully
  @retval others                  Error occur
**/
EFI_STATUS
PeiHeciDevicesInit (
  VOID
  );

/**
  This function performs basic initialization for ME in PEI phase after memory is initiliazed.
**/
VOID
EFIAPI
MePostMemInit (
  VOID
  );

//
// Function Prototype(s) for PchMeUma.c
//

/**
  This procedure will read and return the amount of ME UMA requested
  by ME ROM from the HECI device.

  @param[in] FfsHeader            Pointer to the FFS file header

  @retval UINT32                  Return ME UMA Size
  @retval EFI_SUCCESS             Do not check for ME UMA
**/
UINT32
MeSendUmaSize (
  IN VOID                         *FfsHeader
  );

/**
  This procedure will determine whether or not the CPU was replaced
  during system power loss or via dynamic fusing.
  Calling this procedure could result in a warm reset (if ME FW is requesting one).

  @param[in] FfsHeader            Not used.
  @param[out] ForceFullTraining   When set = 0x1, MRC will be forced to perform a full
                                  memory training cycle.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
CpuReplacementCheck (
  IN VOID                         *FfsHeader,
  OUT UINT8                       *ForceFullTraining
  );

/**
  This procedure will configure the ME Host General Status register,
  indicating that DRAM Initialization is complete and ME FW may
  begin using the allocated ME UMA space.

  @param[in] FfsHeader            Pointer to the FFS file header
  @param[in] InitStat             H_GS[27:24] Status
  @param[in] PttStolenBase        The base of PTT
  @param[in] MeUmaSize            The UMA size FW requested
  @retval EFI_SUCCESS
**/
EFI_STATUS
MeConfigDidReg (
  IN VOID                         *FfsHeader,
  IN UINT8                        InitStat,
  IN UINT32                       PttStolenBase,
  IN UINT32                       MeUmaSize
  );

#endif
