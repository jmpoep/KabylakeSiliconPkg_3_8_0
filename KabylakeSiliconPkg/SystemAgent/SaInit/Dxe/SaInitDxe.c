/** @file
  This is the driver that initializes the Intel System Agent.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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
#include "SaInitDxe.h"
#include "SaInit.h"
#include <Library/MmPciLib.h>
#include <MemInfoHob.h>
#ifndef MINTREE_FLAG
#include <Protocol/PciEnumerationComplete.h>
#include <Protocol/MemoryAddressEncodeDecode.h>
#include <Library/MemoryAddressEncodeDecodeLib.h>

///
/// Global Variables
///

/// Memory Address Encode Decode Protocol
GLOBAL_REMOVE_IF_UNREFERENCED MEMORY_ADDRESS_ENCODE_DECODE_PROTOCOL      mMemoryAddressEncodeDecodeProtocol = {
  (MEMORY_ADDRESS_ENCODE) MrcMemoryAddressEncode,
  (MEMORY_ADDRESS_DECODE) MrcMemoryAddressDecode
};
#endif //MINTREE_FLAG

/**
  SystemAgent Dxe Initialization.

  @param[in] ImageHandle             Handle for the image of this driver
  @param[in] SystemTable             Pointer to the EFI System Table

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    No enough buffer to allocate
**/
EFI_STATUS
EFIAPI
SaInitEntryPointDxe (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                Status;
#ifndef MINTREE_FLAG
  VOID                      *Registration;
#ifndef FSP_WRAPPER_FLAG
  EFI_EVENT                 Event;
#endif
#endif //MINTREE_FLAG

  DEBUG ((DEBUG_INFO, "SaInitDxe Start\n"));

  SaInitEntryPoint ();   // AdvancedFeaturesContent

  Status = SaAcpiInit (ImageHandle);

#ifndef MINTREE_FLAG
  ///
  /// Create PCI Enumeration Completed callback for SA
  ///
  EfiCreateProtocolNotifyEvent (
    &gEfiPciEnumerationCompleteProtocolGuid,
    TPL_CALLBACK,
    SaPciEnumCompleteCallback,
    NULL,
    &Registration
    );

#ifndef FSP_WRAPPER_FLAG
  DEBUG ((DEBUG_INFO, "RegisterForExitBootService() to set PAM lock before OS handoff\n"));
  Status = EfiCreateEventLegacyBootEx (
             TPL_CALLBACK,
             SaPamLockDxe,
             NULL,
             &Event
             );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEvent (
                  EVT_SIGNAL_EXIT_BOOT_SERVICES,
                  TPL_CALLBACK,
                  SaPamLockDxe,
                  NULL,
                  &Event
                  );
  ASSERT_EFI_ERROR (Status);
#endif
  /// Install Memory Address Encode Decode Protocol
  InstallMemoryAddressEncodeDecodeProtocol ();
#endif //MINTREE_FLAG

  DEBUG ((DEBUG_INFO, "SaInitDxe End\n"));

  return EFI_SUCCESS;
}

#ifndef MINTREE_FLAG
/**
  This function gets registered as a callback to perform SA initialization before EndOfDxe

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
SaPciEnumCompleteCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS          Status;
  VOID                *ProtocolPointer;

  DEBUG ((DEBUG_INFO, "SaPciEnumCompleteCallback Start\n"));
  ///
  /// Check if this is first time called by EfiCreateProtocolNotifyEvent() or not,
  /// if it is, we will skip it until real event is triggered
  ///
  Status = gBS->LocateProtocol (&gEfiPciEnumerationCompleteProtocolGuid, NULL, (VOID **) &ProtocolPointer);
  if (EFI_SUCCESS != Status) {
    return;
  }

  gBS->CloseEvent (Event);

  Status = PegInitBeforeEndOfDxe ();
  if (EFI_SUCCESS != Status) {
    DEBUG ((DEBUG_ERROR, "[SA] Pcie initialization before EndOfDxe Error, Status = %r \n", Status));
    ASSERT_EFI_ERROR (Status);
  }

  SaSaveRestore ();
  Status = SaSecurityInit ();
  DEBUG ((DEBUG_INFO, "SaPciEnumCompleteCallback End\n"));
  return;
}

/**
  This function locks the PAM register as part of the SA Security requirements.

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.

**/
VOID
EFIAPI
SaPamLockDxe (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  DEBUG ((DEBUG_INFO, "SaPamLockDxe Start\n"));

  SaPamLock ();

  DEBUG ((DEBUG_INFO, "SaPamLockDxe End\n"));
}

/**
  This function installs the Memory Address Encode Decode Protocol

  @retval EFI_SUCCESS     - Protocol was installed successfully
  @exception EFI_UNSUPPORTED - Protocol was not installed
**/
EFI_STATUS
InstallMemoryAddressEncodeDecodeProtocol (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    Handle;

  Handle = NULL;

  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gMemoryAddressEncodeDecodeProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mMemoryAddressEncodeDecodeProtocol
                  );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}
#endif //MINTREE_FLAG
