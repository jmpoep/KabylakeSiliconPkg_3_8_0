/** @file
  This file contains the main entry point for the MRC mini-BIOS.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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
#ifndef _MrcSsaCommon_h_
#define _MrcSsaCommon_h_

#include "MrcSsaServices.h"
#ifdef SSA_FLAG

///
/// Hook handler type selectors.
///
typedef enum {
  HookHandlerTypeInvalid,                 ///< Signifies that the hook handler pointer is invalid.
  HookHandlerTypeFunction,                ///< Signifies that the hook handler pointer is a pointer to a function.
  HookHandlerTypeData,                    ///< Signifies that the hook handler pointer is a pointer to a data block.
  HookHandlerTypeMax,                     ///< HOOK_HANDLER_TYPE structure maximum value.
  HookHandlerTypeDelim = INT32_MAX        ///< HOOK_HANDLER_TYPE structure delimiter value.
} HOOK_HANDLER_TYPE;

///
/// SSA hook handler entry.
///
typedef struct {
  EFI_GUID          Guid;     ///< EFI guid.
  HOOK_HANDLER_TYPE HookType; ///< The type of pointer, function or data.
  UINT32            HookPtr;  ///< Pointer to the data or pointer to the function to execute.
} HOOK_HANDLER_ENTRY;

///
/// SSA hook handler buffer.
///
typedef struct _HOOK_HANDLER_BUFFER {
  HOOK_HANDLER_ENTRY          Hook[MAX_HOOK_HANDLER]; ///< Hook handler entries.
  struct _HOOK_HANDLER_BUFFER *FwdLink;               ///< Forward link to the next hook handler buffer.
} HOOK_HANDLER_BUFFER;

/**
  This is used to set various registers prior to the SSA stop point.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess
**/
extern
MrcStatus
MrcSsaPreStopPoint (
  IN MrcParameters *const MrcData
  );

/**
  This is used to have a common stopping point for the SSA when in the different boot paths.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess
**/
extern
MrcStatus
MrcSsaStopPoint (
  IN MrcParameters *const MrcData
  );

/**
  Execute code whenever a MRC checkpoint occurs.

  @param[in] MrcData        - The MRC global data area.
  @param[in] Checkpoint     - PostCode value used to identify the current checkpoint.
  @param[in] CheckpointData - Data passed from the caller at the postcode. It can be NULL if no data is expected at a given postcode.

  @retval TRUE if there were at least one function that executed, otherwise FALSE.
**/
extern
BOOLEAN
SsaBiosCheckpoint (
  IN MrcParameters *MrcData,
  IN UINT16        Checkpoint,
  IN void          *CheckpointData
  );

/**
  Function checks the GUID.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Guid        - The address to the given EFI_GUID.

  @retval Success, UnsupportedValue.
**/
extern
SSA_STATUS
EfiGuidCheck (
  SSA_BIOS_SERVICES_PPI *This,
  EFI_GUID              *Guid
  );

/**
  Function checks and sets the GUID.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Source      - The address to the given EFI_GUID.
  @param[in, out] Destination - Where to save the given EFI_GUID if it is valid.

  @retval Success, UnsupportedValue.
**/
extern
SSA_STATUS
EfiGuidCheckAndSave (
  SSA_BIOS_SERVICES_PPI *This,
  EFI_GUID              *Source,
  EFI_GUID              *Destination
  );

/**
  Function compares two GUIDs.

  @param[in]      Source      - The address to the given EFI_GUID.
  @param[in, out] Destination - Where to save the given EFI_GUID if it is valid.

  @retval Success, UnsupportedValue.
**/
extern
BOOLEAN
EfiGuidCompare (
  const EFI_GUID *const Guid1,
  const EFI_GUID *const Guid2
  );

/**
  This function to register a new handler for a hook.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      HookGuid    - GUID defining the hook to invoke the handlers for.
  @param[in]      HookType    - The type of the pointer.
  @param[in]      HookHandler - Function pointer to the new hook handler. This hook handler will be invoked whenever a corresponding call to RunHook() is made with the correct hook GUID.

  @retval Success, UnsupportedValue, or Failure if unable to allocate a buffer to store the hook.
**/
extern
SSA_STATUS
AddToHookHandler (
  SSA_BIOS_SERVICES_PPI *This,
  VOID                  *HookGuid,
  HOOK_HANDLER_TYPE     HookType,
  VOID                  *HookHandler
  );

/**
  This function returns the first pointer that matches the GUID that was earlier saved using AddToHookHandler function.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      HookGuid    - GUID defining the hook pointer to get.
  @param[in]      HookType    - The type of the pointer.
  @param[in]      PointerId   - GUID that uniquely identifies the pointer.

  @retval The value of the pointer or NULL if the pointer for the specified GUID does not exist.
**/
extern
SSA_STATUS
GetHookHandler (
  SSA_BIOS_SERVICES_PPI *This,
  EFI_GUID              *HookGuid,
  HOOK_HANDLER_TYPE     HookType,
  UINT32                *HookHandler
  );

#ifdef SSA_DEBUG_PRINT
extern
void
SsaStackCheck (
  MrcDebug *Debug
 );
#endif // SSA_DEBUG_PRINT
#endif // SSA_FLAG
#endif // _MrcSsaCommon_h_
