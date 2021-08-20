/** @file
  This is the main PEIM file for TXT. It represents an abstract outline of the
  steps required during PEI for enabling TXT. Each individual step is further
  abstracted behind a function call interface. This is intended to minimize
  the need to modify this file when porting TXT to future platforms.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

#include <Ppi/EndOfPeiPhase.h>
#include <Private/SaConfigHob.h>
#include <Private/Library/TxtPeiLib.h>
#include <TxtInfoHob.h>
#include <Ppi/TxtMemoryUnlocked.h>
#include <Library/MmPciLib.h>
#include <Library/PcdLib.h>
#include <CpuRegs.h>


STATIC EFI_PEI_PPI_DESCRIPTOR mPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPeiTxtMemoryUnlockedPpiGuid,
  NULL
};

STATIC EFI_PEI_PPI_DESCRIPTOR mPpiList1 = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPeiTxtReadyToRunMemoryInitPpiGuid,
  NULL
};

STATIC EFI_PEI_NOTIFY_DESCRIPTOR mNotifyDesc = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiEndOfPeiSignalPpiGuid,
  DprUpdate
};

extern EFI_GUID gSaConfigHobGuid;

/**
 TXT init callback module
**/
EFI_STATUS
EFIAPI
TpmDetectedCallback (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
  IN VOID                      *Ppi
  );

STATIC EFI_PEI_NOTIFY_DESCRIPTOR mTpmDetectDesc = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPeiTpmInitializationDonePpiGuid,
  TpmDetectedCallback
};

/**
  TPM detected callback module, must have TPM hardware initialized of detected none

  gPeiTxtMemoryUnlockedPpiGuid will tell memoryinit code if memory is unlocked and good to run.
  gPeiTxtReadyToRunMemoryInitPpiGuid will notify memoryinit code that we are done with unlock and
  should start to do memory init

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  The memory discovered PPI.  Not used.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
TpmDetectedCallback (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
  IN VOID                      *Ppi
  )
{
  EFI_STATUS          Status;
  TXT_PEI_LIB_CONTEXT ctx;
  BOOLEAN             TxtEnvInitFail;
  UINT32              Data32;
  Data32         = 0;
  TxtEnvInitFail = FALSE;

  ///
  /// Install PPI to tell memory code that it can run.
  /// Do it always.
  ///
  Status = PeiServicesInstallPpi (&mPpiList);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Initialize the TXT PEI Lib functions
  ///
  Status = InitializeTxtPeiLib (
             &ctx
             );

  if (EFI_ERROR (Status)) {
    TxtEnvInitFail = TRUE;
    DEBUG ((DEBUG_ERROR, "TXTPEI::PEI Lib initialization failure\n"));
  }

  /**
  Determine TPM presence. If TPM is not present - disabling TXT through TxtInfoHob by setting TxtMode=0
  In case TXT had been enabled but TPM was removed suddenly. Although TPM presence is precondition of this module
  since all commands executed by BIOS ACM don't depend on TPM state.
  TPM_NV_read will be successfully executed even if TPM is disabled
  and/or deactivated because all indices defined for BIOS ACM
  usage don't require authorization. TPM_ResetEstablishmentBit
  doesn't depend on TPM state at all and can
  be executed with disabled/deactivated TPM always.
  Case when TPM is completely not functional is not considered.
  **/
  Status = IsTpmPresent (&ctx);
  if (EFI_ERROR (Status)) {
    ///
    /// If TPM is not present / not supported, set TxtMode=0 in case TPM was removed after TXT enabled
    ///
    if (Status == EFI_UNSUPPORTED) {
      DEBUG ((DEBUG_WARN, "TXTPEI::TPM Support is Disabled in BIOS! Disabling TXT! TxtMode=%x\n", ctx.Hob->Data.TxtMode));
    } else {
      DEBUG ((DEBUG_WARN, "TXTPEI::TPM is not present! Disabling TXT! TxtMode=%x\n", ctx.Hob->Data.TxtMode));
    }

    TxtEnvInitFail = TRUE;
  }
  ///
  /// Detect TXT capable Processor & PCH
  ///
  if (!IsTxtChipset (&ctx)) {
    DEBUG ((DEBUG_WARN, "TXTPEI::Platform or PCH is not TXT capable\n"));
    goto Done;
  } else if (!IsTxtProcessor ()) {
    DEBUG ((DEBUG_WARN, "TXTPEI::Processor is not TXT capable\n"));
    goto Done;
  } else {
    DEBUG ((DEBUG_INFO, "TXTPEI::Processor, PCH & Platform is TXT capable\n"));
    ///
    /// If TXT Lib or TPM is initiated successful, disable TXT support.
    ///
    if (TxtEnvInitFail) {
      TxtUnlockMemory (&ctx);
      ctx.Hob->Data.TxtMode = 0;
      ASSERT (TRUE);
      goto Done;
    }
  }

  Data32 = MmioRead32 (TXT_PUBLIC_BASE + TXT_CRASHCODE_REG_OFF);
  DEBUG ((DEBUG_INFO, "TXTPEI::Crash Code Register=%x\n", Data32));

  ///
  /// Memory is supposed to lock if system is TXT capable.
  /// Check if we need to run SCLEAN. TXT BIOS spec Section 6.2.5
  ///
  if (TxtIsEstablishmentBitAsserted (&ctx) && IsTxtWakeError ()) {

    DEBUG ((DEBUG_INFO, "TXTPEI::EstablishmentBit is set\n"));
    ///
    /// If TXTRESET is set , we must clean TXTRESET bit otherwise SCLEAN
    /// will fail
    ///
    if (IsTxtResetSet ()) {
      IssueGlobalReset ();
    }
    ///
    /// Setup and Launch SCLEAN
    ///
    DEBUG ((DEBUG_INFO, "TXTPEI::Entering SCLEAN\n"));

    DoAcmLaunch (&ctx, TXT_LAUNCH_SCLEAN);

    ///
    /// Reset platform - performed by DoSclean, should not return to execute the following dead looping
    ///
    CpuDeadLoop ();
  } else {
    ///
    /// Unlock memory, and then continue running
    ///
    DEBUG ((DEBUG_INFO, "TXTPEI::EstablishmentBit not asserted - Unlock Memory\n"));
    AsmWriteMsr64 (MSR_LT_UNLOCK_MEMORY, 0);
  }

  Status = PeiServicesNotifyPpi (&mNotifyDesc);
  ASSERT_EFI_ERROR (Status);
Done:
  ///
  /// Install PPI to tell memory code that it can run.
  /// Do it always.
  ///
  Status = PeiServicesInstallPpi (&mPpiList1);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
 TXT init PEI module called by CpuInit

 TXT needs dTPM  to be detected and initialized before SCLEAN or ACHECK in ACMs to be run.
 So generate a callback when detection is done

 gPeiTpmDetectionandInitDonePpiGuid will be generated when dTPM 1.2 or 2.0 is detected and initialized
 or none is found. This will be used to initialize TXT and determine if SCLEAN needs to be run.
**/
VOID
TxtInit (
  VOID
  )
{
  PeiServicesNotifyPpi (&mTpmDetectDesc);
}

/**
  This is AliasCheck entry point for MRC call.  The routine checks for an TXT
  capable platform and determines whether ACHECK should be run.  If so,
  it launches the BIOS ACM to run ACHECK (which will reset the platform).
  The AliasCheck routine is in peitxtlib.

  @exception EFI_UNSUPPORTED  - If the platform is not TXT capable.
  @retval EFI_SUCCESS         - In all other cases not listed above.
**/

EFI_STATUS
EFIAPI
AliasCheck (
  VOID
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;
  TXT_PEI_LIB_CONTEXT ctx;

  DEBUG ((DEBUG_INFO, "TXTPEI::SKL new Alias Check Begin\n"));

  //
  // Reinitialize library context
  //
  Status = InitializeTxtPeiLib (
             &ctx
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "TXTPEI::PEI Lib initialization failure\n"));
    return Status;
  }

  if (IsTxtEnabled (&ctx)) {
    Status = IsTpmPresent (&ctx);
    if (!EFI_ERROR (Status)) {
      if (IsTxtChipset (&ctx)) {
        if (IsTxtProcessor ()) {
          DEBUG ((DEBUG_INFO, "TXTPEI::SKL TXT enabled platform\n"));
          if (((MmioRead32 (TXT_PUBLIC_BASE + TXT_CRASHCODE_REG_OFF) & 0xFE007FF0) == 0xC00040B0)
              || (IsAcheckRequested (&ctx))
              ) {
            DEBUG ((DEBUG_INFO, "TXTPEI::SKL DoAlias\n"));

            DoAcmLaunch (&ctx, TXT_LAUNCH_ACHECK);
            ///
            /// Reset platform - performed by DoAcheck, should not return to execute the following dead looping
            ///
            CpuDeadLoop ();
          }  // if special pattern
        } // IsTxtProcessor
      } // IsTxtChipset
    } // IsTpmPresent
  } // IsTxtEnabled
  DEBUG ((DEBUG_INFO, "TXTPEI::SKL new Alias Check End\n"));

  return EFI_UNSUPPORTED;
}

/**
  Fix up pointers since they are located in real memory now.

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  The memory discovered PPI.  Not used.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
DprUpdate (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
  IN VOID                      *Ppi
  )
{
  TXT_INFO_HOB        *TxtInfoHob;
  SA_CONFIG_HOB       *SaConfigHob;
  DPR_DIRECTORY_ENTRY *DprDirectory;
  UINT16              Index;

  TxtInfoHob   = NULL;
  SaConfigHob    = NULL;
  DprDirectory = NULL;
  Index        = 0;

  //
  // Get TxtInfoHob
  //
  TxtInfoHob = (TXT_INFO_HOB *) GetFirstGuidHob (&gTxtInfoHobGuid);
  if (TxtInfoHob == NULL) {
    return EFI_NOT_FOUND;
  }
  TxtInfoHob->Data.TxtDprMemoryBase = 0;

  //
  // Get SaConfigHob
  //
  SaConfigHob = (SA_CONFIG_HOB *) GetFirstGuidHob (&gSaConfigHobGuid);
  if (SaConfigHob == NULL) {
    return EFI_NOT_FOUND;
  }
  DprDirectory = (DPR_DIRECTORY_ENTRY *)&(SaConfigHob->DprDirectory[0]);

  //
  // Find TXT DPR Directory
  //
  for (Index = 0; Index < DPR_DIRECTORY_MAX; Index++) {
    if (DprDirectory[Index].Type == DPR_DIRECTORY_TYPE_TXT) {
      TxtInfoHob->Data.TxtDprMemoryBase = (EFI_PHYSICAL_ADDRESS) DprDirectory[Index].PhysBase;
      break;
    }
  }

  return EFI_SUCCESS;
}

/**
  Executes the SCHECK function from the LT BIOS ACM on S3 Resume.

  @retval EFI_SUCCESS     - SCHECK Succeeded
  @retval EFI_UNSUPPORTED - If TxtPeiLib initialization failed
**/
EFI_STATUS
S3TxtScheck (
  VOID
  )
{
  EFI_STATUS          Status;
  TXT_PEI_LIB_CONTEXT ctx;
  EFI_BOOT_MODE       BootMode;
  UINT64              MsrValue;

  Status = PeiServicesGetBootMode (&BootMode);
  DEBUG ((DEBUG_INFO, "TXTPEI:BootMode = %X\n", BootMode));
  if ((Status != EFI_SUCCESS) || (BootMode != BOOT_ON_S3_RESUME)) {
    return EFI_SUCCESS;
  }
  DEBUG ((DEBUG_INFO, "TXTPEI:Execute S3 SCHECK\n"));
  //
  // Initialize the TXT PEI Lib functions
  //
  Status = InitializeTxtPeiLib (&ctx);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "TXTPEI::PEI Lib initialization failure\n"));
    return EFI_UNSUPPORTED;
  }

  if (IsTxtEnabled (&ctx)) {
    if (IsTxtResetSet ()) {
      return EFI_UNSUPPORTED;
    }

    ///
    /// Read NO_EVICT_MODE initial value
    ///
    MsrValue = AsmReadMsr64 (NO_EVICT_MODE);
    DEBUG ((DEBUG_INFO, "NO_EVICT_MODE initial value = %016llx\n", MsrValue));
    ///
    /// if NEM is enabled, just return EFI_UNSUPPORTED
    ///
    if (MsrValue & (B_NO_EVICT_MODE_SETUP + B_NO_EVICT_MODE_RUN)) {
      DEBUG ((DEBUG_ERROR, "NEM is enabled in S3 path. TXT will not be launched\n"));
      return EFI_UNSUPPORTED;
    }


    DEBUG ((DEBUG_INFO, "TXTPEI::Skl DoScheck\n"));
    DoPeiScheck (&ctx);
  }
  return EFI_SUCCESS;
}
