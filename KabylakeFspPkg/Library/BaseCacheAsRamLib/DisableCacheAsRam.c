/** @file
  Disable Cache As Ram

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

@par Specification
**/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/CacheAsRamLib.h>
#include <Register/Msr.h>

#define EFI_MSR_NO_EVICT_MODE                  0x000002E0
#define   B_EFI_MSR_NO_EVICT_MODE_RUN                                  BIT1
#define   B_EFI_MSR_NO_EVICT_MODE_SETUP                                BIT0

VOID
CacheInvd (
  VOID
  );

/**
  @todo ADD function description.

  @param[in] DisableCar       TRUE means use CacheINVD, FALSE means use WBINVD

**/
VOID
EFIAPI
DisableCacheAsRam (
  IN BOOLEAN                   DisableCar
  )
{
  MSR_IA32_MCG_CAP_REGISTER MsrIa32McgCapReg;
  UINT64 CacheAsRamMsr;
  UINT32 Index;
  UINT32 McEnd;
  UINT32 McMaxBank;

  CacheAsRamMsr = AsmReadMsr64 (EFI_MSR_NO_EVICT_MODE);

  //
  // @todo: check VLV spec and see any similar requirement of Disable FERR Assertion,
  //   however, vlv has no such MSR B_EFI_MSR_NO_EVICT_MODE_DISABLE_FERR.
  //

  //
  // Step 3: Disable No-Eviction Mode Run State by clearing
  //         NO_EVICT_MODE MSR 2E0h bit [1] = 0
  CacheAsRamMsr &= ~B_EFI_MSR_NO_EVICT_MODE_RUN;
  AsmWriteMsr64 (EFI_MSR_NO_EVICT_MODE, CacheAsRamMsr);

  // Step 4: Disable No-Eviction Mode Setup State by clearing
  //         NO_EVICT_MODE MSR 2E0h bit [0] = 0
  CacheAsRamMsr &= ~B_EFI_MSR_NO_EVICT_MODE_SETUP;
  AsmWriteMsr64 (EFI_MSR_NO_EVICT_MODE, CacheAsRamMsr);

  if (DisableCar) {
    CacheInvd ();
  } else {
    AsmWbinvd();
  }

  //
  // After NEM is disabled, BIOS must clear any Machine Check Bank 6-9 errors that may
  // have occurred as the result of ... MLC to to LLC Evictions.
  //

  //
  // Get number of max number of banks.
  //
  MsrIa32McgCapReg.Uint64 = AsmReadMsr64 (MSR_IA32_MCG_CAP);
  McMaxBank = MsrIa32McgCapReg.Bits.Count - 1;

  //
  // Limit to max number of banks or bank 9.
  //
  McEnd = McMaxBank < 9 ? McMaxBank : 9;

  for (Index = 6; Index <= McEnd; Index++) {
    AsmWriteMsr64 (MSR_IA32_MC0_STATUS + Index * 4, 0);
  }
}
