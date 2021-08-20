/** @file
  The PEI Library Implements ME Init.

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

#include "MbpData.h"
#include "HeciInit.h"
#include <Library/DebugLib.h>
#include <MeChipset.h>
#include <Library/PeiServicesLib.h>
#include <Library/HobLib.h>
#include <Ppi/SiPolicy.h>
#include <MeBiosPayloadHob.h>
#include <Library/PeiAmtLib.h>
#include <Library/PeiMeLib.h>
#include <MeFwHob.h>
#include <Library/MmPciLib.h>
#include <Library/MeShowBufferLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/MeFwStsLib.h>

/**
  Query if ME operation mode is Temp Disable mode.

  @retval TRUE            ME is in Temp Disable mode.
  @retval FALSE           ME is not in Temp Disable mode.
**/
BOOLEAN
IsMeInTempDisabledMode (
  VOID
  )
{
  HECI_FWS_REGISTER        MeFirmwareStatus;
  UINTN                    Timeout;
  UINTN                    HeciBaseAddress;

  HeciBaseAddress = MmPciBase (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER);
  if (MmioRead16 (HeciBaseAddress + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    return FALSE;
  }

  Timeout = MSG_MAX_WAIT_TIMEOUT;

  do {
    ///
    /// Read ME status and check for operation mode
    ///
    MeFirmwareStatus.ul = MmioRead32 (HeciBaseAddress + R_FWSTATE);
    if (MeFirmwareStatus.r.MeOperationMode == ME_OPERATION_MODE_SOFT_TEMP_DISABLE) {
      return TRUE;
    }

    MicroSecondDelay (ME_STATE_STALL_1_SECOND);
    Timeout--;
  } while (Timeout > 0);

  DEBUG ((DEBUG_ERROR, "Timeout: ME not in temp disabled mode after 5s. MeFirmwareStatus: %08x.\n", MeFirmwareStatus.ul));
  return FALSE;
}


/**
  Save FWSTS to ME FWSTS HOB, if the HOB is not existing, the HOB will be created and publish.
  If the HOB is existing, the data will be overrided.
**/
VOID
SaveFwStsToHob (
  VOID
  )
{
  ME_FW_HOB       *MeFwHob;
  UINT8           Index;
  UINT8           Count;
  EFI_STATUS      Status;

  MeFwHob = GetFirstGuidHob (&gMeFwHobGuid);
  if (MeFwHob == NULL) {
    ///
    /// Create HOB for ME Data
    ///
    Status = PeiServicesCreateHob (
               EFI_HOB_TYPE_GUID_EXTENSION,
               sizeof (ME_FW_HOB),
               (VOID **) &MeFwHob
               );
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      return;
    }

    DEBUG ((DEBUG_INFO, "ME FW HOB installed\n"));

    //
    // Initialize default HOB data
    //
    ZeroMem (&(MeFwHob->Revision), (sizeof (ME_FW_HOB) - sizeof (EFI_HOB_GUID_TYPE)));
    MeFwHob->EfiHobGuidType.Name = gMeFwHobGuid;
    MeFwHob->Revision = 1;
    MeFwHob->Count = GetMeFwStsDeviceCount ();
  }

  DEBUG ((DEBUG_INFO, "ME FW HOB data updated\n"));
  ///
  /// Save the FWSTS registers set for each MEI device.
  ///
  for (Count = 0; Count < GetMeFwStsDeviceCount (); Count++) {
    for (Index = 0; Index < GetMeFwStsOffsetCount (); Index++) {
      MeFwHob->Group[Count].Reg[Index] = MmioRead32 (MmPciBase (ME_BUS, ME_DEVICE_NUMBER, (UINT32)gFwStsDeviceList[Count].HeciDev) + gFwStsOffsetTable[Index]);
    }
    MeFwHob->Group[Count].FunNumber = (UINT32)gFwStsDeviceList[Count].HeciDev;
  }

  DEBUG_CODE_BEGIN ();
  DEBUG ((DEBUG_INFO, "Current ME FW HOB data printed - \n"));
  ShowBuffer ((UINT8 *) MeFwHob, sizeof (ME_FW_HOB));
  DEBUG_CODE_END ();
}

/**
  Save all policies in PEI phase to HOB.
**/
VOID
SavePolicyToHob (
  VOID
  )
{
  EFI_STATUS                Status;
  SI_POLICY_PPI             *SiPolicyPpi;
  SI_PREMEM_POLICY_PPI      *SiPreMemPolicyPpi;
  ME_PEI_PREMEM_CONFIG      *MePeiPreMemConfig;
  ME_PEI_CONFIG             *MePeiConfig;
#ifdef AMT_SUPPORT
  AMT_PEI_CONFIG            *AmtPeiConfig;
#endif
  UINTN                     HobSize;
  VOID                      *HobPtr;

  SiPreMemPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMePeiPreMemConfigGuid, (VOID *) &MePeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  SiPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gMePeiConfigGuid, (VOID *) &MePeiConfig);
  ASSERT_EFI_ERROR (Status);

#ifdef AMT_SUPPORT
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gAmtPeiConfigGuid, (VOID *) &AmtPeiConfig);
  ASSERT_EFI_ERROR (Status);
#endif

  //
  // Create ME/AMT HOBs.
  //
  HobSize = MePeiPreMemConfig->Header.GuidHob.Header.HobLength;
  DEBUG ((DEBUG_INFO, "HobSize for MePeiPreMemConfig: %x\n", HobSize));
  HobPtr = BuildGuidDataHob (&gMePreMemPolicyHobGuid, MePeiPreMemConfig, HobSize);
  ASSERT (HobPtr != 0);

  HobSize = MePeiConfig->Header.GuidHob.Header.HobLength;
  DEBUG ((DEBUG_INFO, "HobSize for MePeiConfig: %x\n", HobSize));
  HobPtr = BuildGuidDataHob (&gMePolicyHobGuid, MePeiConfig, HobSize);
  ASSERT (HobPtr != 0);

#ifdef AMT_SUPPORT
  HobSize = AmtPeiConfig->Header.GuidHob.Header.HobLength;
  DEBUG ((DEBUG_INFO, "HobSize for AmtPeiConfig: %x\n", HobSize));
  HobPtr = BuildGuidDataHob (&gAmtPolicyHobGuid, AmtPeiConfig, HobSize);
  ASSERT (HobPtr != 0);
#endif

}

/**
  Disable ME Devices when needed

  @param[in] HeciPpi                  The pointer with Heci Ppi
  @param[in] IntegratedTouchEnabled   The boolean value indicates IntegratedTouchEnabled should be enabled
                                      through MbpHob or via MePolicyPpi set by previous POST boot for S3 boot path
**/
VOID
MeDeviceConfigure (
  IN HECI_PPI                     *HeciPpi,
  IN BOOLEAN                      IntegratedTouchEnabled
  )
{
  EFI_STATUS                      Status;
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
  ME_PEI_PREMEM_CONFIG            *MePeiPreMemConfig;
  ME_BIOS_BOOT_PATH               MeBiosPath;
  UINT32                          DeviceMap;

  DEBUG ((DEBUG_INFO, "MeDeviceConfigure () - Start\n"));


  CheckMeBootPath (&MeBiosPath);

  ///
  /// Step 1. Perform checking for ME Bios Boot path check in all boot mode
  ///
  DeviceMap = MeBiosPath & DEVICE_HIDE_MASK;

  ///
  /// Step 2. Perform device disabling based on FW capability and feature state
  ///         in all boot mode if it is not listed by ME Bios Boot path.
  ///         Policy can only control device disabling when the device is not
  ///         specified to be disabled by any non MeNormalBiosPath.
  ///

  ///
  /// 2-a. Disable HECI2 with CSME in all boot mode - already in MeBiosPath.
  ///
  //
  // Disable Heci2 if and only if policy dictates
  //
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMePeiPreMemConfigGuid, (VOID *) &MePeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  if (!EFI_ERROR (Status)) {
    if (MeHeci2Enabled () == TRUE) {
      DeviceMap &= ~HIDE_MEI2;
    } else {
      DeviceMap |= HIDE_MEI2;
    }
  }

  ///
  /// 2-b. Disable Heci3 when no Integrated Touch support
  ///
  if (!IntegratedTouchEnabled) {
    DeviceMap |= HIDE_MEI3;
  }

  if (!PeiAmtIsSolFeatureEnabled ()) {
    DeviceMap |= HIDE_SOL;
  }

  ///
  /// Step 3. Perform checking for specific boot mode with ME Bios Boot Path,
  ///         like MeDisableSecoverMeiMsgBiosPath. HECI1 shall be disabled
  ///         after HMRFPO_DISABLE_MSG sent in previous POST boot path
  ///
  if ((MeBiosPath == MeSecoverMeiMsgBiosPath) || (MeBiosPath == MeSwTempDisableBiosPath)) {
    if (GetBootModeHob () == BOOT_ON_S3_RESUME) {
      DeviceMap |= HIDE_MEI1;
    }
  }

  ///
  /// Save MEI FWSTS registers set before disable it. The MEI device access right will be removed
  /// by late POST, hence save current FWSTS before disable them for reference without further enabling
  /// MEI steps required. The HOB data might be updated if gets failure when send EOP message in PEI
  /// phase, then FWSTS registers will be updated to reflect the last status before disable rest MEI devices
  ///
  SaveFwStsToHob ();

  if ((DeviceMap & HIDE_ALL_ME_DEVICE) != 0) {
    if ((DeviceMap & HIDE_MEI1) != 0) {
      HeciDisable ();
    }
    if ((DeviceMap & HIDE_MEI2) != 0) {
      Heci2Disable ();
    }
    if ((DeviceMap & HIDE_MEI3) != 0) {
      Heci3Disable ();
    }
    if ((DeviceMap & HIDE_SOL) != 0) {
      SolDisable ();
    }
  }
  ///
  /// Disable IDE-r always with CSME in all boot mode.
  ///
  IderDisable ();

}

/**
  Send Optional Heci Command.
**/
VOID
SendOptionalHeciCommand (
  VOID
  )
{
  EFI_STATUS                Status;
  SI_POLICY_PPI             *SiPolicyPpi;
  ME_PEI_CONFIG             *MePeiConfig;
  ME_BIOS_PAYLOAD_HOB       *MbpHob;
  UINT32                    UnconfigOnRtcClear = 0;

  DEBUG ((DEBUG_INFO, "SendOptionalHeciCommand\n"));

  SiPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Locate gSiPolicyPpiGuid fail. Status = %r\n", Status));
    return;
  }
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gMePeiConfigGuid, (VOID *) &MePeiConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Get ME PeiConfigBlock fail, Status = %r\n", Status));
    return;
  }

  if (MePeiConfig->MeUnconfigIsValid == 0) {
    DEBUG ((DEBUG_INFO, "MeUnconfigOnRtcClear is not valid. Skip MeUnconfig command\n"));
    return;
  }

  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob != NULL) {
    DEBUG ((DEBUG_INFO, "MbpHob NOT NULL\n"));

    if (MbpHob->MeBiosPayload.UnconfigOnRtcClearState.Available == 1) {
      UnconfigOnRtcClear = MbpHob->MeBiosPayload.UnconfigOnRtcClearState.UnconfigOnRtcClearData.DisUnconfigOnRtcClearState;
      if ((MePeiConfig->MeUnconfigOnRtcClear == 1) && (UnconfigOnRtcClear == DisableState)) {
        UnconfigOnRtcClear = EnableState;
        Status = PeiHeciSetUnconfigOnRtcClearDisableMsg (UnconfigOnRtcClear);
      } else if ((MePeiConfig->MeUnconfigOnRtcClear == 0) && (UnconfigOnRtcClear == EnableState)) {
        UnconfigOnRtcClear = DisableState;
        Status = PeiHeciSetUnconfigOnRtcClearDisableMsg (UnconfigOnRtcClear);
      }
    }
  }

  return;
}


/**
  Configure HECI devices on End Of Pei
**/
VOID
MeOnEndOfPei (
  VOID
  )
{
  UINT32                   Heci1Bars[PCI_MAX_BAR];
  UINT32                   Heci2Bars[PCI_MAX_BAR];
  UINT32                   Heci3Bars[PCI_MAX_BAR];

  DEBUG ((DEBUG_INFO, "MeOnEndOfPei\n"));

  if (GetBootModeHob () == BOOT_ON_S3_RESUME) {
    if (MeHeciD0I3Enabled () == FALSE) {
      return;
    }

    //
    // Set D0I3 bits if resuming from S3.
    // We have to make sure the HECI BARs are 32-bit here after restoring S3 boot script.
    //

    //
    // Save MMIO BAR addresses for all HECI devices.
    //
    MeSaveBars (HECI1, Heci1Bars);
    MeSaveBars (HECI2, Heci2Bars);
    MeSaveBars (HECI3, Heci3Bars);

    // Set to default (32-bit) BAR addresses for all HECI devices.
    MeDeviceInit (HECI1, MeGetHeciBarAddress (HECI1), 0);
    MeDeviceInit (HECI2, MeGetHeciBarAddress (HECI2), 0);
    MeDeviceInit (HECI3, MeGetHeciBarAddress (HECI3), 0);

    DEBUG ((DEBUG_INFO, "Setting D0I3 bits for HECI devices on S3 resume path\n"));
    SetD0I3Bit (HECI1);
    SetD0I3Bit (HECI2);
    SetD0I3Bit (HECI3);

    //
    // Restore MMIO BAR addresses for all HECI devices.
    //
    MeRestoreBars (HECI1, Heci1Bars);
    MeRestoreBars (HECI2, Heci2Bars);
    MeRestoreBars (HECI3, Heci3Bars);
  } else {

    //
    // Send optional HECI command
    //
    SendOptionalHeciCommand ();

    //
    // Save ME/AMT policies in PEI phase to HOB for using in DXE.
    //
    SavePolicyToHob ();
  }

  DEBUG ((DEBUG_INFO, "MeOnEndOfPei done.\n"));
}

/**
  This function performs basic initialization for ME in PEI phase after Policy produced.
**/
VOID
EFIAPI
MePostMemInit (
  VOID
  )
{
  EFI_STATUS                Status;
  HECI_PPI                  *HeciPpi;
  ME_BIOS_PAYLOAD_HOB       *MbpHob;
  SI_POLICY_PPI             *SiPolicyPpi;
  BOOLEAN                   IntegratedTouchEnabled;
  ME_PEI_CONFIG             *MePeiConfig;

  DEBUG ((DEBUG_INFO, "MePostMemInit() - Start\n"));

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  IntegratedTouchEnabled = FALSE;

  ///
  /// Install Mbp in POST Mem unless it's S3 resume boot. If MbpHob exists, reflect IntegratedTouch state
  /// from Mbp directly. Otherwise, refer to MePolicy and Me Bios boot path to disable/enable the support.
  ///
  MbpHob = NULL;

  if (GetBootModeHob () != BOOT_ON_S3_RESUME) {
    InstallMbp (HeciPpi, &MbpHob);
    if ((MbpHob != NULL) && (MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.IntegratedTouch == 1)) {
      IntegratedTouchEnabled = TRUE;
    }
  }

  if (MbpHob == NULL) {
    ///
    /// Referring IntegratedTouch by previous POST boot status. The IntegratedTouch status was retrieved via Mbp
    /// and saved in DXE phase by platform code, then reflect to next S3/Error/Recovery boot path via SiPolicyPpi.
    /// Platform should ensure the state is updated depended on current IntegratedTouch status.
    /// Even if the current path is not S3/Error/Recovery bios boot path when MbpHob is not existing,
    /// the continuous MeDeviceConfigure () check may still disable IntegratedTouch device(MEI3) based
    /// on current ME Bios boot path requirement.
    ///
    SiPolicyPpi = NULL;
    Status = PeiServicesLocatePpi (
               &gSiPolicyPpiGuid,
               0,
               NULL,
               (VOID **) &SiPolicyPpi
               );
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      return;
    }

    Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gMePeiConfigGuid, (VOID *) &MePeiConfig);
    ASSERT_EFI_ERROR (Status);

    if (MePeiConfig->Heci3Enabled == 1) {
      IntegratedTouchEnabled = TRUE;
    }
  }

  //
  // Configure CSME devices
  //
  MeDeviceConfigure (HeciPpi, IntegratedTouchEnabled);

  DEBUG ((DEBUG_INFO, "MePostMemInit() - End\n"));
  return;
}
