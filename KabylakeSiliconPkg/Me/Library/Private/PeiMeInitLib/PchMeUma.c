/** @file
  Framework PEIM to PchMeUma

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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
#include <IndustryStandard/Pci22.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>
#include <Library/PciLib.h>
#include <Library/PerformanceLib.h>
#include <Library/IoLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/MmPciLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PttPtpLib.h>
#include <Library/PeiMeLib.h>
#include <Library/MeTypeLib.h>
#include <Ppi/SiPolicy.h>
#include <Ppi/Wdt.h>
#include <MeChipset.h>
#include <HeciRegs.h>
#include <MeDataHob.h>
#include <PttPtpRegs.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PostCodeLib.h>

///
/// LPT PCI Register Definition(s)
///
#define R_MESEG_BASE  0x70

//
// ME FW communication timeout value definitions
//
#define DID_TIMEOUT_MULTIPLIER    0x1388
#define MUSZV_TIMEOUT_MULTIPLIER  0x1388
#define CPURV_TIMEOUT_MULTIPLIER  0x32
#define STALL_1_MILLISECOND       1000

extern EFI_GUID gMeDidSentPpiGuid;

EFI_PEI_PPI_DESCRIPTOR mMeDidSendPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gMeDidSentPpiGuid,
  NULL
};

//
// Internal Function Declarations
//
/**
  Init and Install ME Hob

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
InstallMeHob (
  VOID
  )
{
  EFI_STATUS                      Status;
  ME_DATA_HOB                     *MeDataHob;

  ///
  /// Create HOB for ME Data
  ///
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (ME_DATA_HOB),
             (VOID **) &MeDataHob
             );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Initialize default HOB data
  ///
  MeDataHob->EfiHobGuidType.Name = gMeDataHobGuid;
  ZeroMem (&(MeDataHob->PttBufferAddress), sizeof (UINT64));

  DEBUG ((DEBUG_INFO, "ME Data HOB installed\n"));

  return EFI_SUCCESS;
}

/**
  This procedure will issue a Non-Power Cycle, Power Cycle, or Global Rest.

  @param[in] ResetType            Type of reset to be issued.

  @retval EFI_SUCCESS             The function completed successfully.
  @retval All other error conditions encountered result in an ASSERT.
**/
EFI_STATUS
PerformReset (
  UINT8                           ResetType
  )
{
  EFI_STATUS                      Status;
  UINTN                           LpcBaseAddress;
  UINTN                           PmcBaseAddress;
  UINT32                          ETR3;
  UINT8                           Reset;
  WDT_PPI                         *Wdt;
  PCH_SERIES                      PchSeries;

  ETR3      = 0;
  Reset     = 0;
  Wdt       = NULL;
  PchSeries = GetPchSeries ();

  ///
  /// Locate WDT PPI for access to Wdt->AllowKnownReset()
  ///
  Status = PeiServicesLocatePpi (
             &gWdtPpiGuid,
             0,
             NULL,
             (VOID **) &Wdt
             );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Clear CF9GR of PCH (B0/D31/f0 offset 0x0AC[20] = 1b) to  indicate Host reset
  /// Make sure CWORWRE (CF9 Without Resume Well Reset Enable) is cleared
  ///
  LpcBaseAddress = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC);
  PmcBaseAddress = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_PMC, PCI_FUNCTION_NUMBER_PCH_PMC);

  ETR3  = MmioRead32 (PmcBaseAddress + R_PCH_PMC_ETR3);
  ETR3  = ETR3 &~BIT20;
  ETR3  = ETR3 &~BIT18;
  MmioWrite32 (PmcBaseAddress + R_PCH_PMC_ETR3, ETR3);

  Reset = IoRead8 (R_PCH_RST_CNT);
  Reset &= 0xF1;

  switch (ResetType) {
    case CBM_DIR_NON_PCR:
      ///
      /// Case: Non Power Cycle Reset requested
      ///
      DEBUG ((DEBUG_INFO, "ME FW DID ACK has requested a Non Power Cycle Reset.\n"));
      Reset |= 0x06;
      break;

    case CBM_DIR_PCR:
      ///
      /// Case: Power Cycle Reset requested
      ///
      Wdt->ReloadAndStart (2);
      DEBUG ((DEBUG_INFO, "ME FW DID ACK has requested a Power Cycle Reset.\n"));
      Reset |= 0x0E;
      break;

    case CBM_DIR_GLOBAL_RESET:
      ///
      /// Case: Global Reset
      ///
      DEBUG ((DEBUG_INFO, "ME FW DID Ack requested a global reset.\n"));
      MmioOr32 (LpcBaseAddress + R_PCH_PMC_ETR3, (UINT32) (B_PCH_PMC_ETR3_CF9GR));

      ///
      /// Issue global reset CF9 = 0x0E
      ///
      DEBUG ((DEBUG_INFO, "Issuing global reset.\n"));
      Reset |= 0x0E;
      break;
  }
  ///
  /// Write PCH RST CNT, Issue Reset
  ///
  Wdt->AllowKnownReset ();

  IoWrite8 (R_PCH_RST_CNT, Reset);

  return EFI_SUCCESS;
}

/**
  This procedure will clear the DISB.

  @retval EFI_SUCCESS             Always return EFI_SUCCESS
**/
EFI_STATUS
ClearDisb (
  VOID
  )
{
  UINTN   PmcBaseAddress;

  PmcBaseAddress = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_PMC, PCI_FUNCTION_NUMBER_PCH_PMC);
  //
  // Clear B_PCH_PMC_GEN_PMCON_A_DISB.
  // NOTE: Byte access to not clear BIT18 and BIT16
  //
  MmioWrite8 (PmcBaseAddress + R_PCH_PMC_GEN_PMCON_A + 2, 0);

  return EFI_SUCCESS;
}

/**
  This procedure will Set the DISB.

  @retval EFI_SUCCESS             Always return EFI_SUCCESS
**/
EFI_STATUS
SetDISB (
  VOID
  )
{
  UINTN   PmcBaseAddress;

  PmcBaseAddress = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_PMC, PCI_FUNCTION_NUMBER_PCH_PMC);
  //
  // Set B_PCH_PMC_GEN_PMCON_A_DISB.
  // NOTE: Byte access to not clear BIT18 and BIT16
  //
  MmioWrite8 (PmcBaseAddress + R_PCH_PMC_GEN_PMCON_A + 2, (B_PCH_PMC_GEN_PMCON_A_DISB >> 16));

  return EFI_SUCCESS;
}

/**
  This procedure will enforce the BIOS Action that was requested by ME FW
  as part of the DRAM Init Done message.

  @param[in] BiosAction           Me requests BIOS to act

  @retval EFI_SUCCESS             Always return EFI_SUCCESS
**/
EFI_STATUS
HandleMeBiosAction (
  IN UINT8                        BiosAction
  )
{
  EFI_STATUS                      Status;
  UINTN                           HeciBaseAddress;
  HECI_GS_SHDW_REGISTER           MeFwsts2;
  ///
  /// Read ME FWS2
  ///
  HeciBaseAddress = MmPciBase (
                      ME_BUS,
                      ME_DEVICE_NUMBER,
                      HECI_FUNCTION_NUMBER
                      );
  MeFwsts2.ul = MmioRead32 (HeciBaseAddress + R_ME_GS_SHDW);
  DEBUG ((DEBUG_INFO, "MeFwsts2 = %x.\n", MeFwsts2.r));

  switch (BiosAction) {
    case 0:
      ///
      /// Case: DID ACK was not received
      ///
      DEBUG ((DEBUG_WARN, "DID Ack was not received, no BIOS Action to process.\n"));
      break;

    case CBM_DIR_NON_PCR:
      ///
      /// Case: Perform Non-Power Cycle Reset
      ///
      DEBUG ((DEBUG_INFO, "ME FW has requested a Non-PCR.\n"));
      Status = PerformReset (CBM_DIR_NON_PCR);
      break;

    case CBM_DIR_PCR:
      ///
      /// Case: Perform Power Cycle Reset
      ///
      DEBUG ((DEBUG_INFO, "ME FW has requested a PCR.\n"));
      Status = PerformReset (CBM_DIR_PCR);
      break;

    case 3:
      ///
      /// Case: Go To S3
      ///
      DEBUG ((DEBUG_INFO, "ME FW DID ACK has requested entry to S3.  Not defined, continuing to POST.\n"));
      break;

    case 4:
      ///
      /// Case: Go To S4
      ///
      DEBUG ((DEBUG_INFO, "ME FW DID ACK has requested entry to S4.  Not defined, continuing to POST.\n"));
      break;

    case 5:
      ///
      /// Case: Go To S5
      ///
      DEBUG ((DEBUG_INFO, "ME FW DID ACK has requested entry to S5.  Not defined, continuing to POST.\n"));
      break;

    case CBM_DIR_GLOBAL_RESET:
      ///
      /// Case: Perform Global Reset
      ///
      DEBUG ((DEBUG_INFO, "ME FW has requested a Global Reset.\n"));
      Status = PerformReset (CBM_DIR_GLOBAL_RESET);
      break;

    case CBM_DIR_CONTINUE_POST:
      ///
      /// Case: Continue to POST
      ///
      DEBUG ((DEBUG_INFO, "ME FW DID Ack requested to continue to POST.\n"));
      break;
  }

  return EFI_SUCCESS;
}

//
// RC Private Function Declarations
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
  )
{
  UINT32                          Timeout;
  UINTN                           HeciBaseAddress;
  HECI_MISC_SHDW_REGISTER         MeMiscShdw;
  HECI_FWS_REGISTER               MeHfs;

  HeciBaseAddress = MmPciBase (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER);
  MeMiscShdw.ul = MmioRead32 (HeciBaseAddress + R_ME_MISC_SHDW);
  MeHfs.ul      = MmioRead32 (HeciBaseAddress + R_ME_HFS);
  Timeout       = 0x0;

  if (MeHfs.r.MeOperationMode == ME_OPERATION_MODE_DEBUG) {
    DEBUG ((DEBUG_INFO, "ME debug mode, do not check for ME UMA. \n"));
    return EFI_SUCCESS;
  }

  ///
  /// Poll on MUSZV until it indicates a valid size is present or 5s timeout expires.
  ///

  PERF_START_EX (FfsHeader, NULL, NULL, AsmReadTsc (), 0x3070);

  while ((MeMiscShdw.r.MUSZV == 0) && (Timeout < MUSZV_TIMEOUT_MULTIPLIER)) {
    MicroSecondDelay (STALL_1_MILLISECOND);
    MeMiscShdw.ul = MmioRead32 (HeciBaseAddress + R_ME_MISC_SHDW);
    Timeout++;
  }

  if (Timeout >= MUSZV_TIMEOUT_MULTIPLIER) {
    DEBUG ((DEBUG_INFO, "Timeout occurred waiting for MUSZV. \n"));
    return EFI_SUCCESS;
  }
  PERF_END_EX (FfsHeader, NULL, NULL, AsmReadTsc (), 0x3071);

  ///
  /// Return MeUmaSize value
  ///
  DEBUG ((DEBUG_INFO, "ME UMA Size Requested: %x\n", MeMiscShdw.r.MUSZ));

  return MeMiscShdw.r.MUSZ;
}

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
  )
{
  UINTN                           HeciBaseAddress;
  HECI_GS_SHDW_REGISTER           MeFwsts2;
  EFI_STATUS                      Status;
  UINT32                          Timeout;
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
  ME_PEI_PREMEM_CONFIG            *MePeiPreMemConfig;

  if (MeTypeIsSps ()) {
    //
    // SPS firmware does not support CPU replaced detection
    //
    *ForceFullTraining = TRUE;
    return EFI_SUCCESS;
  }
  HeciBaseAddress = MmPciBase (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER);


  //
  // Get Policy settings through the SiPreMemPolicyPpi PPI
  //
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  Status  = EFI_SUCCESS;
  Timeout = 0x0;
  ///
  /// Read ME FWS2
  ///
  MeFwsts2.ul = MmioRead32 (HeciBaseAddress + R_ME_GS_SHDW);
  DEBUG ((DEBUG_INFO, "MeFwsts2 = %x.\n", MeFwsts2.r));

  if (MeFwsts2.ul == 0xFFFFFFFF) {
    DEBUG ((DEBUG_INFO, "HECI not present! Skip detection!\n"));
    return EFI_SUCCESS;
  }

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMePeiPreMemConfigGuid, (VOID *) &MePeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  PERF_START_EX (FfsHeader, NULL, NULL, AsmReadTsc (), 0x3050);
  ///
  /// Poll 50 ms on CPU Replaced Valid bit
  ///
  while ((((MeFwsts2.r.CpuReplacedValid == 0) && Timeout < CPURV_TIMEOUT_MULTIPLIER))
      && (MePeiPreMemConfig->DisableCpuReplacedPolling != 1)
         ) {
    MicroSecondDelay (STALL_1_MILLISECOND);
    MeFwsts2.ul = MmioRead32 (HeciBaseAddress + R_ME_GS_SHDW);
    Timeout++;
  }
  PERF_END_EX (FfsHeader, NULL, NULL, AsmReadTsc (), 0x3051);

  DEBUG ((DEBUG_INFO, "CpuReplacedValid = %x, ", MeFwsts2.r.CpuReplacedValid));
  DEBUG ((DEBUG_INFO, "CpuReplacedStatus = %x, ", MeFwsts2.r.CpuReplacedSts));
  DEBUG ((DEBUG_INFO, "WarmRstReqForDF = %x.\n", MeFwsts2.r.WarmRstReqForDF));

  if (Timeout >= CPURV_TIMEOUT_MULTIPLIER || MeFwsts2.r.CpuReplacedValid == 0x0) {
    DEBUG ((DEBUG_WARN, "Timeout occurred, the CPU Replacement Valid Bit is not set.\n"));
    *ForceFullTraining = 0x1;
  } else {
    if (MeFwsts2.r.CpuReplacedValid == 0x1) {
      if (MeFwsts2.r.WarmRstReqForDF == 0x1) {
        ///
        /// Clear DISB and Issue a Non-Power Cycle Reset
        ///
        Status  = ClearDisb ();
        Status  = PerformReset (CBM_DIR_NON_PCR);
      }

      if ((MeFwsts2.r.CpuReplacedSts == 0x1 && MeFwsts2.r.WarmRstReqForDF == 0x0)) {
        *ForceFullTraining = 0x1;
      }
    }
  }

  return Status;
}

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
  )
{
  UINTN                           HeciBaseAddress;
  UINTN                           HostBaseAddress;
  UINT32                          MeUmaBase;
  UINT32                          MeUmaBaseExt;
  UINT32                          DidRequestInput;
  UINT32                          Timeout;
  HECI_FWS_REGISTER               MeHfs;
  EFI_STATUS                      Status;
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
  ME_DATA_HOB                     *MeDataHob;
  UINT32                          RegRead;
  UINT32                          WaitTime;
  UINT8                           BiosAction;
  UINT32                          TpmStsFtif;
  UINT32                          LocalityState;
  UINT32                          MeFwSts4;
  EFI_STATUS                      ActionStatus;
  ME_PEI_PREMEM_CONFIG            *MePeiPreMemConfig;
  EFI_BOOT_MODE                   BootMode;

  DEBUG ((DEBUG_INFO, "ME-BIOS: DID Entry.\n"));
  PostCode (0xE01);

  BiosAction = 0;
  BootMode   = GetBootModeHob ();

  ///
  /// Get Policy settings through the SiPreMemPolicyPpi PPI
  ///
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: DID Exit - Error by SiPreMemPolicyPpi not found, Status: %r\n", Status));
    ASSERT_EFI_ERROR (Status);
    PostCode (0xE81);
    return Status;
  }

  DidRequestInput = 0x0;
  Timeout         = 0x0;
  HeciBaseAddress = MmPciBase (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER);
  MeHfs.ul        = MmioRead32 (HeciBaseAddress + R_ME_HFS);

  DEBUG ((DEBUG_INFO, "ME status: 0x%08x\n", MeHfs.ul));

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMePeiPreMemConfigGuid, (VOID *) &MePeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  if (MePeiPreMemConfig->SendDidMsg == 0) {
    ///
    /// Do not send End of Post message to ME FW when the DRAM Init Done message is not sent, as ME FW will not be
    /// capable of handling the EOP message.
    ///
    DEBUG ((DEBUG_INFO, "MePeiPreMemConfig->SendDidMsg = 0, do not check for ME UMA. \n"));
    DEBUG ((DEBUG_INFO, "ME-BIOS: DID Exit - Success.\n"));
    PostCode (0xE21);
    return EFI_SUCCESS;
  }

  if (MeHfs.r.MeOperationMode == ME_OPERATION_MODE_DEBUG) {
    DEBUG ((DEBUG_INFO, "ME debug mode, do not check for ME UMA. \n"));
    DEBUG ((DEBUG_INFO, "ME-BIOS: DID Exit - Success.\n"));
    PostCode (0xE21);
    return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "Entered ME DRAM Init Done procedure.\n"));

  if (MeTypeIsSps () || MeHfs.r.ErrorCode != 0) {
    //
    // PTT not supported when ME is SPS or Error Code detected
    //
    goto PttNotResponsive;
  }

  TpmStsFtif     = MmioRead32 (R_PTT_TXT_STS_FTIF);

  if (((TpmStsFtif & V_FTIF_FTPM_PRESENT) == V_FTIF_FTPM_PRESENT) &&
      (InitStat != 0x1)) {
    ///
    /// Install ME HOBs
    ///
    InstallMeHob ();

    MeDataHob = NULL;
    MeDataHob = GetFirstGuidHob (&gMeDataHobGuid);

    if (MeDataHob != NULL) {
      MeDataHob->PttBufferAddress = PttStolenBase;
      DEBUG ((DEBUG_INFO, "Ptt Allocated Buffer Address: %x\n", MeDataHob->PttBufferAddress ));
      ///
      /// Verify FWSTS4.BIT19. If it's already set then skip the polling.
      ///
      MeFwSts4 = PciRead32 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS_4));
      if (((MeFwSts4 & B_PTT_RESERVED_BIT) == B_PTT_RESERVED_BIT) && (MeFwSts4 != V_PTT_HCI_ALL_BITS_CLEAR)) {
        goto PollingNotNeeded;
      }
      ///
      /// Poll for FWSTS4.BIT19 for 60 ms PLUS a guard buffer of another 30 ms
      ///
      WaitTime = 0;

      while (WaitTime < (3 * PTT_HCI_TIMEOUT_D)) {
        MeFwSts4 = PciRead32 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS_4));
        if ((MeFwSts4 & B_PTT_RESERVED_BIT) == B_PTT_RESERVED_BIT) {
          DEBUG ((DEBUG_INFO, "Polling Period so far: %x\n", WaitTime));
          DEBUG ((DEBUG_INFO, "Polling of FWSTS4.BIT19 was successful.\n"));
          DEBUG ((DEBUG_INFO, "Here is the value of FWSTS4. See the BIT19: %x\n", MeFwSts4));
          break;
        }
        MicroSecondDelay (PTT_HCI_POLLING_PERIOD);
        WaitTime += PTT_HCI_POLLING_PERIOD;
      }

      if (WaitTime >= (3 * PTT_HCI_TIMEOUT_D)) {
        DEBUG ((DEBUG_INFO, "Polling of 60 ms PLUS a guard buffer of another 30 ms, to read FWSTS4.BIT19 has timed out.\n"));
        DEBUG ((DEBUG_INFO, "TPM Establishment bit is not set and TPM is not available for use, please reset or use ME FW Kit 11.0.0.1108 & beyond.\n"));
        DEBUG ((DEBUG_INFO, "Here is the value of FWSTS4. See the BIT19: %x\n", MeFwSts4));
        goto PttNotResponsive;
      }

PollingNotNeeded:
      LocalityState = MmioRead32 ((UINTN) R_PTT_HCI_BASE_ADDRESS + R_PTT_LOCALITY_STATE);
      MeDataHob->LocalityState = LocalityState;

      if ((((LocalityState & V_CRB_LOCALITY_STATE_ACTIVE_LOC_MASK) >> 2) == TPM_LOCALITY_0) &&
          ((LocalityState & B_CRB_LOCALITY_STATE_LOCALITY_ASSIGNED) != 0)) {
        DEBUG ((DEBUG_INFO, "PTT Locality 0 already assigned\n"));
      } else {
        DEBUG ((DEBUG_INFO, "PTT Requesting Locality\n"));

        ///
        /// Request access to locality
        ///
        MmioWrite32 ((UINTN) R_PTT_HCI_BASE_ADDRESS + R_TPM_LOCALITY_CONTROL,
          B_CRB_LOCALITY_CTL_REQUEST_ACCESS
          );
        ///
        /// Wait for assignment of locality
        ///
        LocalityState = MmioRead32 ((UINTN) R_PTT_HCI_BASE_ADDRESS + R_PTT_LOCALITY_STATE);

        WaitTime = 0;
        while ((WaitTime < PTT_HCI_TIMEOUT_A) &&
               (((LocalityState & B_CRB_LOCALITY_STATE_REGISTER_VALID) != B_CRB_LOCALITY_STATE_REGISTER_VALID) ||
                ((LocalityState & B_CRB_LOCALITY_STATE_LOCALITY_ASSIGNED) != B_CRB_LOCALITY_STATE_LOCALITY_ASSIGNED) ||
                (((LocalityState & V_CRB_LOCALITY_STATE_ACTIVE_LOC_MASK) >> 2) != TPM_LOCALITY_0))
                ) {

          LocalityState = MmioRead32 ((UINTN) R_PTT_HCI_BASE_ADDRESS + R_PTT_LOCALITY_STATE);

          MicroSecondDelay (PTT_HCI_POLLING_PERIOD);
          WaitTime += PTT_HCI_POLLING_PERIOD;
        }
        if (WaitTime >= PTT_HCI_TIMEOUT_A) {
          goto PttNotResponsive;
        }
      }

      ///
      /// Make sure TPM is not in fatal error state
      ///
      RegRead = MmioRead32 ((UINTN) R_PTT_HCI_BASE_ADDRESS +
                            ( TPM_LOCALITY_0 * TPM_LOCALITY_BUFFER_SIZE ) +
                            R_CRB_CONTROL_STS);

      if (( RegRead & B_CRB_CONTROL_STS_TPM_STATUS ) != 0 ) {
        goto PttNotResponsive;
      }

      if ((RegRead & B_CRB_CONTROL_STS_TPM_IDLE) != 0) {
        ///
        /// Request TPM to come out of idle
        ///
        MmioWrite32 (
          (UINTN) R_PTT_HCI_BASE_ADDRESS +
          ( TPM_LOCALITY_0 * TPM_LOCALITY_BUFFER_SIZE ) +
          R_CRB_CONTROL_REQ,
          B_CRB_CONTROL_REQ_COMMAND_READY
          );

        ///
        /// Wait for tpm to clear tpmidle
        ///
        WaitTime = 0;
        while ((WaitTime < PTT_HCI_TIMEOUT_C) &&
               ((RegRead & B_CRB_CONTROL_REQ_COMMAND_READY) != 0)) {

          RegRead = MmioRead32 ((UINTN) R_PTT_HCI_BASE_ADDRESS +
                                ( TPM_LOCALITY_0 * TPM_LOCALITY_BUFFER_SIZE ) +
                                R_CRB_CONTROL_REQ);

          MicroSecondDelay (PTT_HCI_POLLING_PERIOD);
          WaitTime += PTT_HCI_POLLING_PERIOD;
        }
        if (WaitTime >= PTT_HCI_TIMEOUT_C) {
          goto PttNotResponsive;
        }
      }

      ///
      /// Write DMA buffer address to command buffer
      ///
      MmioWrite32 (
        (UINTN) R_PTT_HCI_BASE_ADDRESS +
        ( TPM_LOCALITY_0 * TPM_LOCALITY_BUFFER_SIZE ) +
        R_CRB_DATA_BUFFER,
        PttStolenBase
        );

      ///
      /// Write 0x3 to start reg to let PTT know DMA buffer address is there
      ///
      MmioWrite32 (
        (UINTN) R_PTT_HCI_BASE_ADDRESS +
        ( TPM_LOCALITY_0 * TPM_LOCALITY_BUFFER_SIZE ) +
        R_CRB_CONTROL_START,
        0x3
        );

      ///
      /// Wait for command completion
      ///
      WaitTime = 0;
      RegRead = 0;
      RegRead = MmioRead32 ((UINTN) R_PTT_HCI_BASE_ADDRESS +
                            ( TPM_LOCALITY_0 * TPM_LOCALITY_BUFFER_SIZE ) +
                            R_CRB_CONTROL_START);

      while ((WaitTime < PTT_HCI_TIMEOUT_C) &&
             ((RegRead & B_CRB_CONTROL_START) != 0)) {

        RegRead = MmioRead32 ((UINTN) R_PTT_HCI_BASE_ADDRESS +
                              ( TPM_LOCALITY_0 * TPM_LOCALITY_BUFFER_SIZE ) +
                              R_CRB_CONTROL_START);

        MicroSecondDelay (PTT_HCI_POLLING_PERIOD);
        WaitTime += PTT_HCI_POLLING_PERIOD;
      }
      if (WaitTime >= PTT_HCI_TIMEOUT_C) {
        goto PttNotResponsive;
      }

      if (BootMode == BOOT_ON_S3_RESUME) {
        DEBUG ((DEBUG_INFO, "Detecting S3 leaving PTT in idle for OS\n"));
        MmioWrite32 (
          (UINTN)R_PTT_HCI_BASE_ADDRESS +
          (TPM_LOCALITY_0 * TPM_LOCALITY_BUFFER_SIZE) +
          R_CRB_CONTROL_REQ,
          B_CRB_CONTROL_REQ_GO_IDLE
          );
      }
    } else {
      DEBUG ((DEBUG_INFO, "ME DataHob error, MeDataHob not found\n"));
    }
  }

  ///
  /// PTT is not responsive. Cannot just return as DID needs to be signaled
  ///
PttNotResponsive:

  ///
  /// Read MESEGBASE value
  ///
  HostBaseAddress = MmPciBase (0, 0, 0);
  MeUmaBase     = MmioRead32 (HostBaseAddress + R_MESEG_BASE);
  MeUmaBaseExt  = MmioRead32 (HostBaseAddress + (R_MESEG_BASE + 0x04));
  DEBUG ((DEBUG_INFO, "  MeUmaBase read: %x\n", MeUmaBase));

  ///
  /// Write DRAM Init Done (DID) data to the ME H_GS[23:0].
  /// H_GS[23:16] = extended UMA base address (reserved)
  /// H_GS[15:0] = 1M aligned UMA base address
  /// ME FW will 0 extend these values to determine MeUmaBase
  ///
  MeUmaBase = ((MeUmaBaseExt << 28) + (MeUmaBase >> 4)) >> 16;
  DidRequestInput     = MeUmaBase;

  ///
  /// Set H_GS[31:28] = 0x1 indicating DRAM Init Done
  ///
  DidRequestInput |= B_ME_DID_TYPE_MASK;

  InitStat &= 0x7F;

  ///
  /// Set H_GS[27:24] = Status
  ///   0x0 = Success
  ///   0x1 = No Memory in channels
  ///   0x2 = Memory Init Error
  ///   0x3 = Memory not preserved across reset
  ///   0x4-0xF = Reserved
  ///

  if (MePeiPreMemConfig->DidInitStat != 0) {
    InitStat = (UINT8) (UINTN) MePeiPreMemConfig->DidInitStat - 1;
  }
  DEBUG ((DEBUG_INFO, "  InitStat: %x\n", InitStat));

  DidRequestInput |= (InitStat << 24);

  PERF_START_EX (FfsHeader, NULL, NULL, AsmReadTsc (), 0x30A0);
  //
  // Send DID using HECI message
  //
  DEBUG ((DEBUG_INFO, " Sending DID as MKHI message\n"));

  Status = PeiHeciSendDid (DidRequestInput, &BiosAction);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Sending DID failed! Error: %r\n", Status));
  } else {
    DEBUG ((DEBUG_INFO, "ME DRAM Init Done ACK received.\n"));
    DEBUG ((DEBUG_INFO, "HFS read after DID ACK: %x\n", MeHfs.r));
  }
  PERF_END_EX (FfsHeader, NULL, NULL, AsmReadTsc (), 0x30A1);

  DEBUG ((DEBUG_INFO, "BiosAction = %x\n", BiosAction));
  ActionStatus = HandleMeBiosAction (BiosAction);

  if (EFI_ERROR (PeiServicesInstallPpi (&mMeDidSendPpi))) {
    ASSERT (TRUE);
  }

  //
  // The 'Status' local variable still keeps value of PeiHeciSendDid function.
  // Use it to update POSTCODE.
  //
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "ME-BIOS: DID Exit - Success.\n"));
    PostCode (0xE21);
  } else {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: DID Exit - Error by fail to send DID message, Status: %r\n", Status));
    PostCode (0xEA1);
  }

  return ActionStatus;
}

