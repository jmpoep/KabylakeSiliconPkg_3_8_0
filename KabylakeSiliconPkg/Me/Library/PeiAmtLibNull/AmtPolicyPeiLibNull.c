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
#include <Library/PeiAmtLib.h>


/**
  Start Watch Dog Timer HECI message

  @param[in] HeciPpi              The pointer to HECI PPI
  @param[in] HeciMemBar           HECI Memory BAR
  @param[in] WaitTimerBios        The value of waiting limit

  @exception EFI_UNSUPPORTED      Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
PeiHeciAsfStartWatchDog (
  IN  HECI_PPI                    *HeciPpi,
  IN  UINT16                      WaitTimerBios
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Stop Watch Dog Timer HECI message

  @param[in] HeciPpi              The pointer to HECI PPI

**/
VOID
PeiHeciAsfStopWatchDog (
  IN  HECI_PPI                    *HeciPpi
  )
{
  return;
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
  return FALSE;
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
  Get BIOS WatchDog Timer value.

  @retval UINT16                  BIOS WatchDog Timer value
**/

UINT16
PeiAmtGetBiosWatchdogTimer (
  VOID
  )
{

  return 0;
}

/**
  This function is deprecated. Maintained only for backward compatibility in KBL.
  Please use IsAmtBiosSupportEnabled () function from now on.

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
  return FALSE;
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
  return FALSE;
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
  return 0;
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
  return FALSE;
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
  return FALSE;
}

