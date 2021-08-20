/** @file
  PCH RESET PEIM DRIVER.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2017 Intel Corporation.

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
#include <Library/IoLib.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <PchAccess.h>
#include <Ppi/Reset2.h>
#include <Ppi/PchReset.h>
#include <Library/PeiMeLib.h>  // AdvancedFeaturesContent
#include <Library/ResetSystemLib.h>
#include <PchResetPlatformSpecific.h>

VOID
EFIAPI
ResetPlatformSpecific (
  IN EFI_STATUS       ResetStatus,
  IN UINTN            DataSize,
  IN VOID             *ResetData OPTIONAL
  );


/**
  Resets the entire platform.

  @param[in] ResetType            UEFI defined reset type.
  @param[in] ResetStatus          The status code for the reset.
  @param[in] DataSize             The size of ResetData in bytes.
  @param[in] ResetData            Optional element used to introduce a platform specific reset.
                                  The exact type of the reset is defined by the EFI_GUID that follows
                                  the Null-terminated Unicode string.

**/
VOID
EFIAPI
ResetSystem (
  IN EFI_RESET_TYPE     ResetType,
  IN EFI_STATUS         ResetStatus,
  IN UINTN              DataSize,
  IN VOID               *ResetData OPTIONAL
  )
{
  switch (ResetType) {
  case EfiResetWarm:
    ResetWarm ();
    break;

  case EfiResetCold:
    ResetCold ();
    break;

  case EfiResetShutdown:
    ResetShutdown ();
    return;

  case EfiResetPlatformSpecific:
    ResetPlatformSpecific (ResetStatus, DataSize, ResetData);
    return;

  default:
    return;
  }

  //
  // Given we should have reset getting here would be bad
  //
  ASSERT (FALSE);
}

/**
  Execute Pch Reset from the host controller.

  @param[in] This                 Pointer to the PCH_RESET_PPI instance.
  @param[in] PchResetType         Pch Reset Types which includes PchColdReset, PchWarmReset,
                                  PchShutdownReset, PchGlobalReset

  @retval EFI_SUCCESS             Successfully completed.
  @retval EFI_INVALID_PARAMETER   If ResetType is invalid.
**/
EFI_STATUS
EFIAPI
Reset (
  IN PCH_RESET_PPI        *This,
  IN PCH_RESET_TYPE       PchResetType
  )
{
  PCH_RESET_DATA          ResetData;

  switch (PchResetType) {
    case PchColdReset:
      ResetCold();
      break;

    case PchWarmReset:
      ResetWarm();
      break;

    case PchShutdownReset:
      ResetShutdown();
      break;

    case PchGlobalReset:
      CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
      StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
      ResetPlatformSpecific (EFI_SUCCESS, sizeof (PCH_RESET_DATA), &ResetData);
      break;

    default:
      return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}

/**
  Initialize PCH Reset APIs

  @retval EFI_SUCCESS             APIs are installed successfully
  @retval EFI_OUT_OF_RESOURCES    Can't allocate pool
**/
EFI_STATUS
EFIAPI
PchInitializeReset (
  VOID
  )
{
  EFI_STATUS              Status;
  PCH_RESET_PPI           *PeiPchResetPpi;
  EFI_PEI_PPI_DESCRIPTOR  *PeiPchResetDescriptor;
  EFI_PEI_RESET2_PPI      *EfiPeiReset2Ppi;
  EFI_PEI_PPI_DESCRIPTOR  *EfiPeiReset2Descriptor;

  DEBUG ((DEBUG_INFO, "PchInitializeReset() Start\n"));

  PeiPchResetDescriptor = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  PeiPchResetPpi = (PCH_RESET_PPI *) AllocateZeroPool (sizeof (PCH_RESET_PPI));
  if ((PeiPchResetDescriptor == NULL) ||
      (PeiPchResetPpi == NULL)) {
    ASSERT (FALSE);
    return EFI_OUT_OF_RESOURCES;
  }

  ///
  /// Initialize the Reset ppi instance
  ///
  PeiPchResetPpi->Reset         = Reset;
  PeiPchResetDescriptor->Flags  = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  PeiPchResetDescriptor->Guid   = &gPchResetPpiGuid;
  PeiPchResetDescriptor->Ppi    = PeiPchResetPpi;

  ///
  /// Install the PCH RESET PPI
  ///
  Status = PeiServicesInstallPpi (PeiPchResetDescriptor);
  ASSERT_EFI_ERROR (Status);

  EfiPeiReset2Descriptor = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  EfiPeiReset2Ppi = (EFI_PEI_RESET2_PPI *) AllocateZeroPool (sizeof (EFI_PEI_RESET2_PPI));
  if ((EfiPeiReset2Descriptor == NULL) ||
      (EfiPeiReset2Ppi == NULL)) {
    ASSERT (FALSE);
    return EFI_OUT_OF_RESOURCES;
  }

  ///
  /// Initialize the EFI Reset2 ppi instance
  ///
  EfiPeiReset2Ppi->ResetSystem  = ResetSystem;

  EfiPeiReset2Descriptor->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  EfiPeiReset2Descriptor->Guid  = &gEfiPeiReset2PpiGuid;
  EfiPeiReset2Descriptor->Ppi   = EfiPeiReset2Ppi;

  Status = PeiServicesInstallPpi (EfiPeiReset2Descriptor);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "PchInitializeReset() End\n"));

  return Status;
}

