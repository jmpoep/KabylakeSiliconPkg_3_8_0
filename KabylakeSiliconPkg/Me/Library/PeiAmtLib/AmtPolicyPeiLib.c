/** @file
  Implementation file for AMT Policy functionality for PEIM

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2015 Intel Corporation.

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

#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/PeiServicesLib.h>

#include <Library/PeiAmtLib.h>
#include <Library/ConfigBlockLib.h>

#define MNT_OFF     0x00


/**
  Get config block of AMT PEI from AMT policy ppi

  @param[in] AmtPeiConfig         The AMT config block.

  @retval EFI_SUCCESS             Get config block of AMT PEI successfully.
  @retval All other error conditions encountered result in an ASSERT.
**/
EFI_STATUS
PeiAmtConfigBlockInit (
  IN AMT_PEI_CONFIG   **AmtPeiConfig
  )
{
  EFI_STATUS             Status;
  SI_POLICY_PPI          *SiPolicyPpi;

  ///
  /// Locate system configuration variable
  ///
  SiPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gAmtPeiConfigGuid, (VOID *) AmtPeiConfig);
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use PeiAmtIsWatchdogTimerEnabled () function from now on.

  Check if AMT Watchdog Timer is enabled in setup options.

  @retval FALSE                   AMT Watchdog Timer is disabled.
  @retval TRUE                    AMT Watchdog Timer is enabled.
**/

BOOLEAN
PeiAmtWatchDog (
  VOID
  )
{
  return PeiAmtIsWatchdogTimerEnabled ();
}

/**
  Check if AMT Watchdog Timer is enabled in setup options.

  @retval FALSE                   AMT Watchdog Timer is disabled.
  @retval TRUE                    AMT Watchdog Timer is enabled.
**/
BOOLEAN
PeiAmtIsWatchdogTimerEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;
  BOOLEAN                         Enabled;
  AMT_PEI_CONFIG                  *AmtPeiConfig;

  Enabled = FALSE;

  if (PeiGetManageabilityModeSetting () != MNT_OFF) {
    Status = PeiAmtConfigBlockInit (&AmtPeiConfig);
    ASSERT_EFI_ERROR (Status);
    if (AmtPeiConfig->WatchDog == 1) {
      Enabled = TRUE;
    }
  }
  return Enabled;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use PeiAmtGetBiosWatchdogTimer () function from now on.

  Get BIOS Watchdog Timer value.

  @retval UINT16                  BIOS Watchdog Timer value
**/
UINT16
PeiAmtWatchTimerBiosGet (
  VOID
  )
{
  return PeiAmtGetBiosWatchdogTimer ();
}

/**
  Get BIOS Watchdog Timer value.

  @retval UINT16                  BIOS Watchdog Timer value
**/
UINT16
PeiAmtGetBiosWatchdogTimer (
  VOID
  )
{
  EFI_STATUS                      Status;
  AMT_PEI_CONFIG                  *AmtPeiConfig;

  Status = PeiAmtConfigBlockInit (&AmtPeiConfig);
  if (!EFI_ERROR (Status)) {
    return AmtPeiConfig->WatchDogTimerBios;
  } else {
    return 0;
  }

}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use PeiIsAmtBiosSupportEnabled () function from now on.

  Check if AMT is enabled in setup options.

  @retval FALSE                   ActiveManagement is disabled.
  @retval TRUE                    ActiveManagement is enabled.
**/
BOOLEAN
PeiAmtSupported (
  VOID
  )
{
  return PeiIsAmtBiosSupportEnabled ();
}

/**
  Check if AMT is enabled in setup options.

  @retval FALSE                   ActiveManagement is disabled.
  @retval TRUE                    ActiveManagement is enabled.
**/
BOOLEAN
PeiIsAmtBiosSupportEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;
  BOOLEAN                         Supported;
  AMT_PEI_CONFIG                  *AmtPeiConfig;

  Status = PeiAmtConfigBlockInit (&AmtPeiConfig);
  ASSERT_EFI_ERROR (Status);

  if (AmtPeiConfig->AmtEnabled == 1) {
    Supported = TRUE;
  } else {
    Supported = FALSE;
  }

  return Supported;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use PeiIsAsfBiosSupportEnabled () function from now on.

  Check if ASF is enabled in setup options.

  @retval FALSE                   ASF is disabled.
  @retval TRUE                    ASF is enabled.
**/
BOOLEAN
PeiAsfSupported (
  VOID
  )
{
  return PeiIsAsfBiosSupportEnabled ();
}

/**
  Check if ASF is enabled in setup options.

  @retval FALSE                   ASF is disabled.
  @retval TRUE                    ASF is enabled.
**/
BOOLEAN
PeiIsAsfBiosSupportEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;
  BOOLEAN                         Supported;
  AMT_PEI_CONFIG                  *AmtPeiConfig;

  Status = PeiAmtConfigBlockInit (&AmtPeiConfig);
  ASSERT_EFI_ERROR (Status);

  if (AmtPeiConfig->AsfEnabled == 1) {
    Supported = TRUE;
  } else {
    Supported = FALSE;
  }

  return Supported;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use PeiGetManageabilityModeSetting () function from now on.

  Provide Manageability Mode setting from MEBx BIOS Sync Data

  @retval UINT8                   Manageability Mode = MNT_ON or MNT_OFF
**/
UINT8
ManageabilityModeSetting (
  VOID
  )
{
  return PeiGetManageabilityModeSetting ();
}

/**
  Provide Manageability Mode setting from MEBx BIOS Sync Data

  @retval UINT8                   Manageability Mode = MNT_ON or MNT_OFF
**/
UINT8
PeiGetManageabilityModeSetting (
  VOID
  )
{
  EFI_STATUS                      Status;
  AMT_PEI_CONFIG                  *AmtPeiConfig;

  Status = PeiAmtConfigBlockInit (&AmtPeiConfig);
  ASSERT_EFI_ERROR (Status);

  return (UINT8) (AmtPeiConfig->ManageabilityMode);
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use PeiIsFwProgressSupported () function from now on.

  This will return Progress Event Option.
  True if the option is enabled.

  @param[in] VOID

  @retval True                    Progress Event is enabled.
  @retval False                   Progress Event is disabled.
**/
BOOLEAN
PeiFwProgressSupport (
  VOID
  )
{
  return PeiIsFwProgressSupported ();
}

/**
  This will return Progress Event Option.
  True if the option is enabled.

  @param[in] VOID

  @retval True                    Progress Event is enabled.
  @retval False                   Progress Event is disabled.
**/
BOOLEAN
PeiIsFwProgressSupported (
  VOID
  )
{
  EFI_STATUS                      Status;
  BOOLEAN                         Supported;
  AMT_PEI_CONFIG                  *AmtPeiConfig;

  Status = PeiAmtConfigBlockInit (&AmtPeiConfig);
  ASSERT_EFI_ERROR (Status);

  Supported = FALSE;

  if (AmtPeiConfig->FwProgress == 1) {
    Supported = TRUE;
  }

  return Supported;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use PeiAmtIsSolFeatureEnabled () function from now on.

  Provide Amt Sol setting from MEBx BIOS Sync Data

  @retval TRUE                    Amt Sol is enabled.
  @retval FALSE                   Amt Sol is disabled.
**/
BOOLEAN
AmtSolSetting (
  VOID
  )
{
  return PeiAmtIsSolFeatureEnabled ();
}

/**
  Provide Amt Sol feature setting from MEBx BIOS Sync Data

  @retval TRUE                    Amt Sol feature is enabled.
  @retval FALSE                   Amt Sol feature is disabled.
**/
BOOLEAN
PeiAmtIsSolFeatureEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;
  AMT_PEI_CONFIG                  *AmtPeiConfig;

  Status = PeiAmtConfigBlockInit (&AmtPeiConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Referring AmtSol state from Mebx by previous POST boot status. The AmtSol status was retrieved via Mebx
  /// and saved in DXE phase by ME_BIOS_EXTENSION_SETUP variable, then reflect the next boot path via AmtPolicyPpi.
  /// Platform should ensure the state is updated depended on current ME_BIOS_EXTENSION_SETUP.AmtSol status.
  ///

  return (UINT8) (AmtPeiConfig->AmtSolEnabled);
}
