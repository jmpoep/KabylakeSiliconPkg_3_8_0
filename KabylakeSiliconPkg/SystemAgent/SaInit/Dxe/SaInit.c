/** @file
  This is the Common driver that initializes the Intel System Agent.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#include "SaInit.h"
#include <Library/MmPciLib.h>
#include <Private/SaConfigHob.h>
#include <Protocol/PciEnumerationComplete.h>

///
/// Global Variables
///
GLOBAL_REMOVE_IF_UNREFERENCED SA_CONFIG_HOB                          *mSaConfigHob;
BOOLEAN                                                              mSkipPamLock = FALSE;

/*
  Intel(R) Core Processor Skylake BWG version 0.4.0

  18.6 System Agent Configuration Locking
   For reliable operation and security, System BIOS must set the following bits:
   1. For all modern Intel processors, Intel strongly recommends that BIOS should set
       the D_LCK bit. Set B0:D0:F0.R088h [4] = 1b to lock down SMRAM space.
  BaseAddr values for mSaSecurityRegisters that uses PciExpressBaseAddress will be initialized at
  Runtime inside function SaPcieInitPolicy().
*/
GLOBAL_REMOVE_IF_UNREFERENCED BOOT_SCRIPT_REGISTER_SETTING mSaSecurityRegisters[] = {
  {0,  R_SA_SMRAMC,  0xFFFFFFFF,  BIT4}
};

/**
  SystemAgent Initialization Common Function.

  @retval EFI_SUCCESS   - Always.
**/

VOID
SaInitEntryPoint (
  VOID
  )
{
  ///
  /// Get SaConfigHob HOB
  ///
  mSaConfigHob              = NULL;
  mSaConfigHob              = (SA_CONFIG_HOB *) GetFirstGuidHob (&gSaConfigHobGuid);
  if (mSaConfigHob != NULL) {
    mSkipPamLock = mSaConfigHob->SkipPamLock;
  }
  return;
}



/**
  Common function locks the PAM register as part of the SA Security requirements.

  @retval EFI_SUCCESS   - Always.
**/

VOID
SaPamLock (
  VOID
  )
{
  UINTN  BaseAddress;
  UINT32 Data32Or;

  if (mSkipPamLock == FALSE) {
    BaseAddress = MmPciBase (0, 0, 0);
    Data32Or    = BIT0;
    DEBUG ((DEBUG_INFO, "PAM_LOCK!!\n"));
    MmioOr32 (BaseAddress + R_SA_PAM0, Data32Or);
  }
}

/**
  This function does SA security lock
**/
VOID
SaSecurityLock (
  VOID
  )
{
  UINT8           Index;
  UINT64          BaseAddress;
  UINT32          RegOffset;
  UINT32          Data32And;
  UINT32          Data32Or;

  ///
  /// 17.2 System Agent Security Lock configuration
  ///
  DEBUG ((DEBUG_INFO, "DXE SaSecurityLock\n"));
  for (Index = 0; Index < (sizeof (mSaSecurityRegisters) / sizeof (BOOT_SCRIPT_REGISTER_SETTING)); Index++) {
    BaseAddress = mSaSecurityRegisters[Index].BaseAddr;
    RegOffset   = mSaSecurityRegisters[Index].Offset;
    Data32And   = mSaSecurityRegisters[Index].AndMask;
    Data32Or    = mSaSecurityRegisters[Index].OrMask;

    if (RegOffset == R_SA_SMRAMC) {
      ///
      /// SMRAMC LOCK must use CF8/CFC access
      ///
      PciOr8 (PCI_LIB_ADDRESS (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_SMRAMC), (UINT8) Data32Or);
      BaseAddress = S3_BOOT_SCRIPT_LIB_PCI_ADDRESS (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_SMRAMC);
      S3BootScriptSavePciCfgReadWrite (
        S3BootScriptWidthUint8,
        (UINTN) BaseAddress,
        &Data32Or,
        &Data32And
        );
    }
  }

  ///
  /// Lock processor/chipset BAR registers, This has moved to CPU code for SoftwareGuard support
  ///
}

/**
  This function performs SA Security locking in EndOfDxe callback

  @retval EFI_SUCCESS     - Security lock has done
  @retval EFI_UNSUPPORTED - Security lock not done successfully
**/
EFI_STATUS
SaSecurityInit (
  VOID
  )
{

  UINT8                     Index;

  for (Index = 0; Index < (sizeof (mSaSecurityRegisters) / sizeof (BOOT_SCRIPT_REGISTER_SETTING)); Index++) {
    if (mSaSecurityRegisters[Index].BaseAddr != (UINT32) PcdGet64 (PcdMchBaseAddress)) {
      mSaSecurityRegisters[Index].BaseAddr = (UINT32) MmPciBase (0,0,0);
    }
  }
  SaSecurityLock ();

  return EFI_SUCCESS;
}

