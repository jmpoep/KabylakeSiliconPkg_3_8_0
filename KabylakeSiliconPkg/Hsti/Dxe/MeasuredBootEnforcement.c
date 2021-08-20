/** @file
  This file contains the tests for the MeasuredBootEnforcement BIT

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 Intel Corporation.

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

#include "HstiSiliconDxe.h"

TPM2B_AUTH             mNewPlatformAuth;

/**
  Check if buffer is all zero.

  @param[in] Buffer      Buffer to be checked.
  @param[in] BufferSize  Size of buffer to be checked.

  @retval TRUE  Buffer is all zero.
  @retval FALSE Buffer is not all zero.
**/
BOOLEAN
IsZeroBuffer (
  IN VOID  *Buffer,
  IN UINTN BufferSize
  )
{
  UINT8 *BufferData;
  UINTN Index;

  BufferData = Buffer;
  for (Index = 0; Index < BufferSize; Index++) {
    if (BufferData[Index] != 0) {
      return FALSE;
    }
  }
  return TRUE;
}

/**
  Run tests for MeasuredBootEnforcement bit
**/
VOID
CheckMeasuredBootEnforcement (
  VOID
  )
{
  EFI_STATUS                Status;
  BOOLEAN                   Result;
  BOOLEAN                   TpmPresent;
  CHAR16                    *HstiErrorString;
  TPML_PCR_SELECTION        PcrSelectionIn;
  UINT32                    PcrUpdateCounter;
  TPML_PCR_SELECTION        PcrSelectionOut;
  TPML_DIGEST               PcrValues;
  TPML_PCR_SELECTION        Pcrs;
  UINT32                    Index;
  BOOLEAN                   Pcr7Initialized;
  UINTN                     Index3;
  EFI_PHYSICAL_ADDRESS      EventLogLocation;
  EFI_PHYSICAL_ADDRESS      EventLogLastEntry;
  BOOLEAN                   EventLogTruncated;
  TPMS_AUTH_COMMAND         LocalAuthSession;
  UINT16                    AuthSize;
  UINT32                    PttPchStrap;

  EFI_TREE_PROTOCOL         *TreeProtocol = NULL;
  PCH_SPI_PROTOCOL          *SpiProtocol = NULL;

  if ((mFeatureImplemented[0] & HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT) == 0) {
    return;
  }

  Status = gBS->LocateProtocol (&gPchSpiProtocolGuid, NULL, (VOID **) &SpiProtocol);
  ASSERT_EFI_ERROR (Status);

  Result     = TRUE;
  TpmPresent = TRUE;
  Status     = EFI_SUCCESS;

  DEBUG ((DEBUG_INFO, "MeasuredBoot Enforcement\n"));

  DEBUG ((DEBUG_INFO, "    1. If chipset supports FW TPM it must be enabled or the platorm must have a dTPM\n"));

  Status = SpiProtocol->ReadPchSoftStrap (SpiProtocol, R_PCH_SPI_STRP_DSCR_0, sizeof (PttPchStrap), &PttPchStrap);

  if (((PttPchStrap & BIT22) == 0) &&
      (*(UINT8 *) (UINTN) TPM_BASE_ADDRESS == 0xFF)) {

    DEBUG ((DEBUG_INFO, "Fail: FW TPM supported but no TPM present on system\n"));

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_ERROR_CODE_1,HSTI_MEASURED_BOOT_CONFIGURATION, HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_ERROR_STRING_1);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
    TpmPresent = FALSE;
  }

  DEBUG ((DEBUG_INFO, "    2.PCR[7] Must be initialized\n"));

  ZeroMem (&PcrSelectionIn, sizeof (PcrSelectionIn));
  ZeroMem (&PcrUpdateCounter, sizeof (UINT32));
  ZeroMem (&PcrSelectionOut, sizeof (PcrSelectionOut));
  ZeroMem (&PcrValues, sizeof (PcrValues));
  ZeroMem (&Pcrs, sizeof (TPML_PCR_SELECTION));
  Pcr7Initialized = FALSE;

  if (TpmPresent == TRUE) {
    Status = Tpm2GetCapabilityPcrs (&Pcrs);

    for (Index3 = 0; Index3 < Pcrs.count; Index3++) {
      PcrSelectionIn.pcrSelections[PcrSelectionIn.count].hash = Pcrs.pcrSelections[Index3].hash;
      PcrSelectionIn.pcrSelections[PcrSelectionIn.count].sizeofSelect = PCR_SELECT_MAX;
      PcrSelectionIn.pcrSelections[PcrSelectionIn.count].pcrSelect[0] = 0x80;
      PcrSelectionIn.pcrSelections[PcrSelectionIn.count].pcrSelect[1] = 0x00;
      PcrSelectionIn.pcrSelections[PcrSelectionIn.count].pcrSelect[2] = 0x00;
      PcrSelectionIn.count++;
    }

    Tpm2PcrRead (&PcrSelectionIn,&PcrUpdateCounter,&PcrSelectionOut,&PcrValues);

    for (Index = 0; Index < PcrValues.count; Index++) {
      Pcr7Initialized = !IsZeroBuffer (PcrValues.digests[Index].buffer,PcrValues.digests[Index].size);
      if ( !Pcr7Initialized ) {
        DEBUG ((DEBUG_INFO, "Fail: Pcr 7 not initialized\n"));
        break;
      }
    }
  }

  if ( !Pcr7Initialized || (TpmPresent != TRUE)) {
    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_ERROR_CODE_2,HSTI_MEASURED_BOOT_CONFIGURATION, HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_ERROR_STRING_2);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    3.Event log must be published\n"));

  EventLogLocation = (EFI_PHYSICAL_ADDRESS) NULL;
  if (TpmPresent == TRUE) {

    Status = gBS->LocateProtocol (&gEfiTrEEProtocolGuid, NULL, (VOID **) &TreeProtocol);

    if (!EFI_ERROR ( Status )) {
      Status = TreeProtocol->GetEventLog (TreeProtocol,
                               TREE_EVENT_LOG_FORMAT_TCG_1_2,
                               &EventLogLocation,
                               &EventLogLastEntry,
                               &EventLogTruncated
                               );
    }
    DEBUG ((DEBUG_INFO, "EventLogLocation - EventLogLocation - %x\n", EventLogLocation));

  }

  if ( EFI_ERROR ( Status ) || (EventLogLocation == (EFI_PHYSICAL_ADDRESS) NULL) || (TpmPresent != TRUE)) {
    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_ERROR_CODE_3,HSTI_MEASURED_BOOT_CONFIGURATION, HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_ERROR_STRING_3);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    4. Platform Auth value must not be all zero\n"));

  if ( TpmPresent == TRUE ) {
    AuthSize = MAX_NEW_AUTHORIZATION_SIZE;
    for (Index = 0; Index < Pcrs.count; Index++) {
      switch (Pcrs.pcrSelections[Index].hash) {
        case TPM_ALG_SHA1:
          AuthSize = SHA1_DIGEST_SIZE;
          break;
        case TPM_ALG_SHA256:
          AuthSize = SHA256_DIGEST_SIZE;
          break;
        case TPM_ALG_SHA384:
          AuthSize = SHA384_DIGEST_SIZE;
          break;
        case TPM_ALG_SHA512:
          AuthSize = SHA512_DIGEST_SIZE;
          break;
        case TPM_ALG_SM3_256:
          AuthSize = SM3_256_DIGEST_SIZE;
          break;
      }
    }

    ZeroMem (mNewPlatformAuth.buffer, AuthSize);
    ZeroMem (&LocalAuthSession, sizeof (LocalAuthSession));
    LocalAuthSession.sessionHandle = TPM_RS_PW;
    LocalAuthSession.hmac.size = AuthSize;
    CopyMem (LocalAuthSession.hmac.buffer, mNewPlatformAuth.buffer, AuthSize);

    Status = Tpm2HierarchyChangeAuth (TPM_RH_PLATFORM, NULL, &mNewPlatformAuth);
    DEBUG ((DEBUG_INFO, "Tpm2HierarchyChangeAuth with NULL auth Result: - %r\n", Status));
  }

  if (!EFI_ERROR (Status) || (TpmPresent != TRUE)) {
    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_ERROR_CODE_4,HSTI_MEASURED_BOOT_CONFIGURATION, HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_ERROR_STRING_4);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  //
  // ALL PASS
  //
  if (Result) {

    Status = HstiLibSetFeaturesVerified (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               0,
               HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT
               );
    ASSERT_EFI_ERROR (Status);
  }

  return;
}
