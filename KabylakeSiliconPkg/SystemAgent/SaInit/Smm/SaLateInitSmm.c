/** @file
  This SMM driver will handle SA relevant late initialization

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2016 Intel Corporation.

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
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Protocol/SmmIoTrapDispatch2.h>
#include "SaLateInitSmm.h"
#include <SaRegs.h>
#include <SaAccess.h>
#include <PchAccess.h>
#include <Private/SaConfigHob.h>
#include <Private/Library/SaPcieLib.h>
#include <Private/Protocol/SaIotrapSmi.h>

typedef enum {
  EnumSaSmiCallbackForMaxPayLoad,
  EnumSaSmiCallbackForSaSaveRestore,
  EnumSaSmiCallbackForLateInit,
  EnumSaSmiCallbackForS3resume,
  EnumSaSmiCallbackMax
} SMI_OPERATION;

GLOBAL_REMOVE_IF_UNREFERENCED UINT8                           mSaSmiCallbackPhase      = EnumSaSmiCallbackForMaxPayLoad;

/**
  A SMI callback to do SA relevant late initialization

  @param[in] DispatchHandle  - The handle of this callback, obtained when registering
  @param[in] DispatchContext - Pointer to the EFI_SMM_IO_TRAP_DISPATCH_CALLBACK_CONTEXT
**/
VOID
EFIAPI
SaIoTrapSmiCallback (
  IN  EFI_HANDLE                            DispatchHandle,
  IN CONST VOID                             *CallbackContext,
  IN OUT VOID                               *CommBuffer,
  IN OUT UINTN                              *CommBufferSize
  )
{

  if (mSaSmiCallbackPhase == EnumSaSmiCallbackMax) {
    return;
  }
  if (mSaSmiCallbackPhase == EnumSaSmiCallbackForMaxPayLoad) {
    SaPcieEnumCallback ();
    ///
    /// Switch to next phase
    ///
    mSaSmiCallbackPhase = EnumSaSmiCallbackForSaSaveRestore;
  } else if (mSaSmiCallbackPhase == EnumSaSmiCallbackForSaSaveRestore) {
    ///
    /// Save platform registers including IGFX BAR & COMMAND registers and PAM
    ///
    SaSaveRestorePlatform (TRUE);
    ///
    /// Switch to next phase
    ///
    mSaSmiCallbackPhase = EnumSaSmiCallbackForLateInit;
  } else if (mSaSmiCallbackPhase == EnumSaSmiCallbackForLateInit) {
    ///
    /// Expected to execute in ReadyToBoot point (after OROM)
    ///
    SaPcieConfigAfterOpRom ();
    ///
    /// Switch to next phase
    ///
    mSaSmiCallbackPhase = EnumSaSmiCallbackForS3resume;
  } else if (mSaSmiCallbackPhase == EnumSaSmiCallbackForS3resume) {
    ///
    /// Expected to execute in end of S3 resume flow
    ///
    SaS3ResumeCallback ();
  }
}

/**
  Initializes the SA SMM handler

  @param[in] ImageHandle - The image handle of Wake On Lan driver
  @param[in] SystemTable - The standard EFI system table

  @retval EFI_SUCCESS    - SA SMM handler was installed or not necessary
  @retval EFI_NOT_FOUND  - Fail to register SMI callback or required protocol/hob missing.
**/
EFI_STATUS
EFIAPI
SaLateInitSmmEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL        *PchIoTrap;
  EFI_SMM_IO_TRAP_REGISTER_CONTEXT          PchIoTrapContext;
  EFI_HANDLE                                PchIoTrapHandle;
  SA_CONFIG_HOB                             *SaConfigHob;
  SA_POLICY_PROTOCOL                        *SaPolicy;
  EFI_STATUS                                Status;
  SA_IOTRAP_SMI_PROTOCOL                    *SaIotrapSmiProtocol;

  DEBUG ((DEBUG_INFO, "SaLateInitSmmEntryPoint()\n"));

  SaConfigHob = NULL;
  SaConfigHob = (SA_CONFIG_HOB *) GetFirstGuidHob (&gSaConfigHobGuid);
  Status = EFI_NOT_FOUND;
  if (SaConfigHob != NULL) {
    ///
    /// Locate the PCH Trap dispatch protocol
    ///
    Status = gSmst->SmmLocateProtocol (&gEfiSmmIoTrapDispatch2ProtocolGuid, NULL, (VOID **) &PchIoTrap);
    ASSERT_EFI_ERROR (Status);
    if (Status == EFI_SUCCESS) {
      if (SaConfigHob->InitPcieAspmAfterOprom == TRUE) {
        ///
        /// Register SMI callback to initialize PCIe ASPM after OPROM
        ///
        PchIoTrapContext.Type     = ReadWriteTrap;
        PchIoTrapContext.Length   = 4;
        PchIoTrapContext.Address  = 0;
        Status = PchIoTrap->Register (
                              PchIoTrap,
                              (EFI_SMM_HANDLER_ENTRY_POINT2) SaIoTrapSmiCallback,
                              &PchIoTrapContext,
                              &PchIoTrapHandle
                              );
        ASSERT_EFI_ERROR (Status);
        if (Status == EFI_SUCCESS) {
          ///
          /// Initialize module global variables - Stepping ID and Policy for runtime SMI handler
          /// Get the platform setup policy.
          ///
          Status = gBS->LocateProtocol (&gSaPolicyProtocolGuid, NULL, (VOID **) &SaPolicy);
          ASSERT_EFI_ERROR (Status);
          if (SaPolicy != NULL) {
            SaPcieInitPolicy (SaPolicy);
          }
          ///
          /// Install the SA IOTRAP SMI protocol
          ///
          (gBS->AllocatePool) (EfiBootServicesData, sizeof (SA_IOTRAP_SMI_PROTOCOL), (VOID **)&SaIotrapSmiProtocol);
          SaIotrapSmiProtocol->SaIotrapSmiAddress = PchIoTrapContext.Address;
          Status = gBS->InstallMultipleProtocolInterfaces (
                          &ImageHandle,
                          &gSaIotrapSmiProtocolGuid,
                          SaIotrapSmiProtocol,
                          NULL
                          );
          DEBUG ((DEBUG_INFO, "SA Iotrap address=%X\n", SaIotrapSmiProtocol->SaIotrapSmiAddress));
        }
      } else {
        ///
        /// If ASPM policy is set to "Before OPROM", this SMI callback is not necessary
        /// Ensure the SMI callback handler will directly return and continue the POST.
        ///
        mSaSmiCallbackPhase = EnumSaSmiCallbackMax;
        Status = EFI_SUCCESS;
      }
    }
  }

  if (Status != EFI_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "Failed to register SaIotrapSmiCallback!\n"));
    ///
    /// System will halt when failing to register required SMI handler
    ///
    CpuDeadLoop ();
  }

  return EFI_SUCCESS;
}
