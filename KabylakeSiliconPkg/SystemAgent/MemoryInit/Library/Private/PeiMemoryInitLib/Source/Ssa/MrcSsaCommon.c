/** @file
  This file contains the main entry point for the MRC mini-BIOS.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2015 Intel Corporation.

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
#include "MrcDebugPrint.h"
#include "MrcSsaServices.h"
#include "MrcSsaCommon.h"
#include "SsaCommonConfig.h"
#include "McAddress.h"
#include "MrcCommon.h"

#ifdef SSA_FLAG


/**
  This is used to set various registers prior to the SSA stop point.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcSsaPreStopPoint (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput        *Outputs;
  MrcIntOutput     *MrcIntData;
  MrcIntChannelOut *IntChannelOut;
  UINT8            Byte;
  UINT8            Channel;
  UINT32           Offset;
  MRC_HAL_SEQUENCE_CONFIG_STRUCT            SeqConfig;
  MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT ReutChSeqCfg;

  Outputs    = &MrcData->Outputs;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (&MrcData->Outputs, Channel)) {
      SeqConfig.StopBaseSequenceOnWrapTrigger   = MrcHalSequenceWrapIgnoreArg;
      SeqConfig.AddressUpdateRateMode           = MrcHalAddressUpdateRateModeIgnoreArg;
      SeqConfig.EnableDummyReads                = MrcHalDummyReadIgnoreArg;
      SeqConfig.ReutAllowOppRefresh             = MrcHalOpportunisticRefreshIgnoreArg;
      SeqConfig.GlobalControl                   = MrcHalGlobalControlIgnoreArg;
      SeqConfig.InitializationMode              = MrcHalInitializationModeReutTesting;
      SeqConfig.SubsequenceStartPointer         = MrcHalSubSequencePointerIgnoreArg;
      SeqConfig.SubsequenceEndPointer           = MrcHalSubSequencePointerIgnoreArg;
      SeqConfig.StartTestDelay                  = MRC_IGNORE_ARG;
      SeqConfig.SubSequenceCachelineCounterMode = MrcHalCachelineCounterIgnoreArg;
      MrcHalSetReutSequenceConfig (MrcData, Channel, &SeqConfig);
    }
  }
  if (MrcData->Inputs.BootMode == bmFast) {
    //
    // Set CPGC mode
    //
    ReutChSeqCfg.Data                     = 0;
    ReutChSeqCfg.Bits.Initialization_Mode = REUT_Testing_Mode;
    MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_REG, (UINT32) ReutChSeqCfg.Data);
    MrcWriteCR (MrcData, MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_REG, (UINT32) ReutChSeqCfg.Data);

    //
    // Enable SlaveDLL Lengths for margining
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      IntChannelOut =  &MrcIntData->Controller->Channel[Channel];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        IntChannelOut->DqControl1[Byte].Bits.SdllSegmentDisable = 0;
        Offset = MrcGetOffsetDataControl1 (MrcData, Channel, Byte);
        MrcWriteCR (MrcData, Offset, IntChannelOut->DqControl1[Byte].Data);
      }
    }
  }
  return (mrcSuccess);
}

/**
  This is used to have a common stopping point for the SSA when in the different boot paths.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcSsaStopPoint (
  IN MrcParameters *const MrcData
  )
{
  UINT8 Channel;
  MRC_HAL_SEQUENCE_CONFIG_STRUCT SeqConfig;

  if ((MrcData->Inputs.BootMode == bmWarm) || (MrcData->Inputs.BootMode == bmFast)) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (&MrcData->Outputs, Channel)) {
        SeqConfig.StopBaseSequenceOnWrapTrigger   = MrcHalSequenceWrapDisable;
        SeqConfig.AddressUpdateRateMode           = MrcHalAddressUpdateRateModeCachelines;
        SeqConfig.EnableDummyReads                = MrcHalDummyReadDisable;
        SeqConfig.ReutAllowOppRefresh             = MrcHalOpportunisticRefreshDisable;
        SeqConfig.GlobalControl                   = MrcHalGlobalControlDisable;
        SeqConfig.InitializationMode              = MrcHalInitializationModeReutTesting;
        SeqConfig.SubsequenceStartPointer         = MrcHalSubSequencePointer0;
        SeqConfig.SubsequenceEndPointer           = MrcHalSubSequencePointer0;
        SeqConfig.StartTestDelay                  = 0; //Delay period in DCLKs
        SeqConfig.SubSequenceCachelineCounterMode = MrcHalCachelineCounterCommands;
        MrcHalSetReutSequenceConfig (MrcData, Channel, &SeqConfig);
      }
    }
  }
  return (mrcSuccess);
}
/**
  Execute code whenever a MRC checkpoint occurs.

  @param[in] MrcData        - The MRC global data area.
  @param[in] Checkpoint     - PostCode value used to identify the current checkpoint.
  @param[in] CheckpointData - Data passed from the caller at the postcode. It can be NULL if no data is expected at a given postcode.

  @retval TRUE if there were at least one function that executed, otherwise FALSE.
**/
BOOLEAN
SsaBiosCheckpoint (
  IN MrcParameters *MrcData,
  IN UINT16        Checkpoint,
  IN void          *CheckpointData
  )
{
#ifndef MRC_MINIBIOS_BUILD
  SSA_BIOS_SERVICES_PPI  *SsaBiosServices;
  SSA_POSTCODE_HOOK_DATA PostCodeHookData;
  MrcInput               *Inputs;

  SsaBiosServices = (SSA_BIOS_SERVICES_PPI *) ((MrcIntOutput *) (MrcData->IntOutputs.Internal))->SsaBiosServicesPpi;
  if (SsaBiosServices != NULL) {
    Inputs                        = &MrcData->Inputs;
    PostCodeHookData.Postcode     = Checkpoint;
    PostCodeHookData.PostcodeData = CheckpointData;
    if ((void *) (Inputs->SsaCallbackPpi) != NULL) {
      (((SSA_BIOS_CALLBACKS_PPI *) (Inputs->SsaCallbackPpi))->MrcCheckpoint) (((SSA_BIOS_CALLBACKS_PPI *) Inputs->SsaCallbackPpi), Checkpoint, NULL);
    }
    return (((Success == SsaBiosServices->SsaCommonConfig->RunHook (SsaBiosServices, (VOID *) &gSsaPostcodeHookGuid, (VOID *) (&PostCodeHookData)))) ? TRUE : FALSE);
  }
#else
#endif
  return FALSE;
}

/**
  Function checks the GUID.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Guid        - The address to the given EFI_GUID.

  @retval Success, UnsupportedValue.
**/
SSA_STATUS
EfiGuidCheck (
  SSA_BIOS_SERVICES_PPI *This,
  EFI_GUID              *Guid
  )
{
  SSA_STATUS Status;
  UINT8      Check;
  UINT8      Index;

  Status = UnsupportedValue;
  if (Guid != NULL) {
    for (Index = 0, Check = 0; Index < sizeof (EFI_GUID); Index++) {
      Check |= ((UINT8 *) Guid) [Index];
    }
    if (Check != 0) {
      Status = Success;
    }
  }

  return (Status);
}

/**
  Function checks and sets the GUID.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Source      - The address to the given EFI_GUID.
  @param[in, out] Destination - Where to save the given EFI_GUID if it is valid.

  @retval Success, UnsupportedValue.
**/
SSA_STATUS
EfiGuidCheckAndSave (
  SSA_BIOS_SERVICES_PPI *This,
  EFI_GUID              *Source,
  EFI_GUID              *Destination
  )
{
  SSA_STATUS    Status;

  Status = UnsupportedValue;
  if (Destination != NULL) {
    Status = EfiGuidCheck (This, Source);
    if (Status == Success) {
      ((MrcParameters *) This->SsaMemoryConfig->MrcData)->Inputs.Call.Func->MrcCopyMem ((UINT8 *) Destination, (UINT8 *) Source, sizeof (EFI_GUID));
    }
  }

  return (Status);
}

/**
  Function compares two GUIDs.

  @param[in]      Source      - The address to the given EFI_GUID.
  @param[in, out] Destination - Where to save the given EFI_GUID if it is valid.

  @retval Success, UnsupportedValue.
**/
BOOLEAN
EfiGuidCompare (
  const EFI_GUID *const Guid1,
  const EFI_GUID *const Guid2
  )
{
  const UINT8 *P1;
  const UINT8 *P2;
  UINT8       Index;

  P1 = (const UINT8 *) Guid1;
  P2 = (const UINT8 *) Guid2;
  for (Index = 0; Index < sizeof (EFI_GUID); Index++) {
    if (*P1++ != *P2++) {
      return (FALSE);
    }
  }
  return (TRUE);
}

/**
  This function to register a new handler for a hook.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      HookGuid    - GUID defining the hook to invoke the handlers for.
  @param[in]      HookType    - The type of the pointer.
  @param[in]      HookHandler - Function pointer to the new hook handler. This hook handler will be invoked whenever a corresponding call to RunHook() is made with the correct hook GUID.

  @retval Success, UnsupportedValue, or Failure if unable to allocate a buffer to store the hook.
**/
SSA_STATUS
AddToHookHandler (
  SSA_BIOS_SERVICES_PPI *This,
  VOID                  *HookGuid,
  HOOK_HANDLER_TYPE     HookType,
  VOID                  *HookHandler
  )
{
  MrcParameters       *MrcData;
  MRC_FUNCTION        *MrcCall;
  HOOK_HANDLER_BUFFER *OldHookBuffer;
  HOOK_HANDLER_BUFFER *HookBuffer;
  SSA_STATUS          SsaStatus;
  UINT8               Index;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  MrcCall = MrcData->Inputs.Call.Func;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "AddToHookHandler entry, %08Xh %08Xh\n", HookGuid, HookHandler);
  SsaStatus = UnsupportedValue;
  if (HookHandler != NULL) {
    HookBuffer    = (HOOK_HANDLER_BUFFER *) This->SsaCommonConfig->HookBuffer;
    OldHookBuffer = HookBuffer;
    SsaStatus  = EfiGuidCheck (This, HookGuid);
    while (Success == SsaStatus) {
      if (HookBuffer == NULL) {
        HookBuffer = (HOOK_HANDLER_BUFFER *) This->SsaCommonConfig->Malloc (This, sizeof (HOOK_HANDLER_BUFFER));
        if (HookBuffer != NULL) {
          MrcCall->MrcSetMem ((UINT8 *) HookBuffer, sizeof (HOOK_HANDLER_BUFFER), 0);
          if (This->SsaCommonConfig->HookBuffer == NULL) {
            This->SsaCommonConfig->HookBuffer = HookBuffer;
          } else {
            OldHookBuffer->FwdLink = HookBuffer;
          }
        } else {
          SsaStatus = Failure;
          break;
        }
      }
      while (HookBuffer != NULL) {
        for (Index = 0; Index < MAX_HOOK_HANDLER; Index++) {
          if (HookBuffer->Hook[Index].HookPtr == 0) {
            MrcCall->MrcCopyMem ((UINT8 *) &HookBuffer->Hook[Index].Guid, HookGuid, sizeof (EFI_GUID));
            HookBuffer->Hook[Index].HookPtr  = (UINT32) HookHandler;
            HookBuffer->Hook[Index].HookType = HookType;
            return (Success);
          }
        }
        if (Index >= MAX_HOOK_HANDLER) {
          if (HookBuffer->FwdLink != NULL) {
            HookBuffer = HookBuffer->FwdLink;
          } else {
            OldHookBuffer = HookBuffer;
            HookBuffer    = NULL;
            break;
          }
        }
      }
    }
  }
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "AddToHookHandler exit %u\n", SsaStatus);
  return (SsaStatus);
}

/**
  This function returns the first pointer that matches the GUID that was earlier saved using AddToHookHandler function.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      HookGuid    - GUID defining the hook pointer to get.
  @param[in]      HookType    - The type of the pointer.
  @param[in]      PointerId   - GUID that uniquely identifies the pointer.

  @retval The value of the pointer or NULL if the pointer for the specified GUID does not exist.
**/
SSA_STATUS
GetHookHandler (
  SSA_BIOS_SERVICES_PPI *This,
  EFI_GUID              *HookGuid,
  HOOK_HANDLER_TYPE     HookType,
  UINT32                *HookHandler
  )
{
  HOOK_HANDLER_BUFFER *HookBuffer;
  SSA_STATUS          SsaStatus;
  UINT8               Index;
#ifdef SSA_DEBUG_PRINT
  MrcParameters       *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetHookHandler entry, %08Xh, %u\n", HookGuid, HookType);
#endif
  HookBuffer = (HOOK_HANDLER_BUFFER *) This->SsaCommonConfig->HookBuffer;
  SsaStatus  = EfiGuidCheck (This, HookGuid);
  while (Success == SsaStatus) {
    if (HookBuffer == NULL) {
      SsaStatus = UnsupportedValue;
    }
    while (HookBuffer != NULL) {
      for (Index = 0; Index < MAX_HOOK_HANDLER; Index++) {
        if (HookHandlerTypeData == HookBuffer->Hook[Index].HookType) {
          if (TRUE == EfiGuidCompare (HookGuid, &HookBuffer->Hook[Index].Guid)) {
            SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "Pointer found %08Xh\n", HookBuffer->Hook[Index].HookPtr);
            *HookHandler = HookBuffer->Hook[Index].HookPtr;
            return (SsaStatus);
          }
        }
      }
      HookBuffer = HookBuffer->FwdLink;
    }
    break;
  }
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "Pointer not found\n");
  return (SsaStatus);
}

#ifdef SSA_DEBUG_PRINT
void
SsaStackCheck (
  MrcDebug *Debug
  )
{
  MrcParameters *MrcData;
  UINT32        StackValue;

  MrcData    = (MrcParameters *) Debug->MrcData;
  StackValue = (UINT32) &MrcData;
  if ((Debug > 0) && (MrcData > 0)) {
    if ((StackValue >= MrcData->Inputs.HeapBase) && (StackValue <= (MrcData->Inputs.HeapBase + MrcData->Inputs.HeapSize))) {
      MrcPrintf (Debug, MSG_LEVEL_ERROR, "Stack %08X inside heap\n", StackValue);
    }
  }
}
#endif // SSA_DEBUG_PRINT
#endif // SSA_FLAG
