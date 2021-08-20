/** @file
  PCH RESET Runtime Driver

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

@par Specification Reference:
**/
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/PchReset.h>
#include <PchAccess.h>
#include <Library/MmPciLib.h>
#include <Library/ResetSystemLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <PchResetPlatformSpecific.h>

GLOBAL_REMOVE_IF_UNREFERENCED PCH_RESET_PROTOCOL  *mPchResetProtocol;

GLOBAL_REMOVE_IF_UNREFERENCED PCH_RESET_DATA mPchGlobalReset = {
  PCH_PLATFORM_SPECIFIC_RESET_STRING,
  {0}
};

VOID
EFIAPI
ResetPlatformSpecific (
  IN EFI_STATUS       ResetStatus,
  IN UINTN            DataSize,
  IN VOID             *ResetData OPTIONAL
  );

/**
  Retrieve PCH platform specific ResetData

  @param[in]  Guid      PCH platform specific reset GUID.
  @param[out] DataSize  The size of ResetData in bytes.

  @retval ResetData     A platform specific reset that the exact type of
                        the reset is defined by the EFI_GUID that follows
                        the Null-terminated Unicode string.
  @retval NULL          If Guid is not defined in PCH platform specific reset.
**/
VOID *
EFIAPI
GetResetData (
  IN   EFI_GUID *Guid,
  OUT  UINTN    *DataSize
  )
{
  *DataSize = 0;
  if (CompareGuid (Guid, &gPchGlobalResetGuid)) {
    CopyMem (&mPchGlobalReset.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
    *DataSize = sizeof (mPchGlobalReset);
    return (VOID *)&mPchGlobalReset;
  }
  return NULL;
}

/**
  Execute Pch Reset from the host controller.

  @param[in] This                 Pointer to the PCH_RESET_PROTOCOL instance.
  @param[in] ResetType            UEFI defined reset type.
  @param[in] DataSize             The size of ResetData in bytes.
  @param[in] ResetData            Optional element used to introduce a platform specific reset.
                                  The exact type of the reset is defined by the EFI_GUID that follows
                                  the Null-terminated Unicode string.

  @retval EFI_SUCCESS             Successfully completed.
  @retval EFI_INVALID_PARAMETER   If ResetType is invalid.
**/
EFI_STATUS
EFIAPI
Reset (
  IN PCH_RESET_PROTOCOL *This,
  IN EFI_RESET_TYPE     ResetType,
  IN UINTN              DataSize,
  IN VOID               *ResetData OPTIONAL
  )
{
  EFI_STATUS          ResetStatus;

  ResetStatus = EFI_SUCCESS;

  switch (ResetType) {
    case EfiResetCold:
      ResetCold ();
      break;

    case EfiResetWarm:
      ResetWarm ();
      break;

    case EfiResetShutdown:
      ResetShutdown ();
      break;

    case EfiResetPlatformSpecific:
      ResetPlatformSpecific (ResetStatus, DataSize, ResetData);
      break;

    default:
      return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}

/**
  <b>PchReset Runtime DXE Driver Entry Point</b>\n
  - <b>Introduction</b>\n
    The PchReset Runtime DXE driver provide a standard way for other modules to
    use the PCH Reset Interface in DXE/SMM/Runtime environments. It has no longer
    hooked ResetSystem() function of the runtime service table.

  - @pre
    - If there is any driver which needs to run the callback function right before
      issuing the reset, PCH Reset Callback Protocol will need to be installed
      before PCH Reset Runtime DXE driver. If PchReset Runtime DXE driver is run
      before Status Code Runtime Protocol is installed and there is the need
      to use Status code in the driver, it will be necessary to add EFI_STATUS_CODE_RUNTIME_PROTOCOL_GUID
      to the dependency file.
    - @link _PCH_RESET_CALLBACK_PROTOCOL  PCH_RESET_CALLBACK_PROTOCOL @endlink

  - @result
    The Reset driver produces @link _PCH_RESET_PROTOCOL PCH_RESET_PROTOCOL @endlink

  @param[in] ImageHandle          Image handle of the loaded driver
  @param[in] SystemTable          Pointer to the System Table

  @retval EFI_SUCCESS             Thread can be successfully created
  @retval EFI_OUT_OF_RESOURCES    Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR        Cannot create the timer service
**/
EFI_STATUS
EFIAPI
InstallPchReset (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                      Status;
  EFI_HANDLE                      Handle;

  DEBUG ((DEBUG_INFO, "InstallPchReset() Start\n"));

  ///
  /// Allocate Runtime memory for the PchReset protocol instance.
  ///
  mPchResetProtocol = AllocateRuntimeZeroPool (sizeof (PCH_RESET_PROTOCOL));
  if (mPchResetProtocol == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  ///
  /// Initialize the Reset protocol instance
  ///
  mPchResetProtocol->Reset        = Reset;
  mPchResetProtocol->GetResetData = GetResetData;

  ///
  /// Install protocol interface
  ///
  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gPchResetProtocolGuid,
                  mPchResetProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// The Lib Deconstruct will automatically be called when entrypoint return error.
  ///
  DEBUG ((DEBUG_INFO, "InstallPchReset() End\n"));

  return Status;
}

