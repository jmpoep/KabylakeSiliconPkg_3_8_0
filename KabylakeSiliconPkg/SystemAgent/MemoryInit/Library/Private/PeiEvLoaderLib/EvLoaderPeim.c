/** @file
  The PEI Library Implements the EVI Callback PEI Initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2017 Intel Corporation.

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
#include "EvLoaderPeim.h"
#include <MrcSsaServices.h>
#include <Ppi/SsaPeiInit.h>
#include "ScratchPadReg.h"
#include "PeLoader.h"
#include "EvItpDownloadAgent.h"
#include <MrcInterface.h>


GLOBAL_REMOVE_IF_UNREFERENCED const char *EvLoaderCheckpointStr      = "EvLoaderCheckpoint()";
GLOBAL_REMOVE_IF_UNREFERENCED const char *EvLoaderEntryPointStr      = "EvLoaderEntryPoint()";
GLOBAL_REMOVE_IF_UNREFERENCED const char *EvLoadToolStr              = "EvLoadTool()";
GLOBAL_REMOVE_IF_UNREFERENCED const char *EvLoadConfigStr            = "EvLoadConfig()";
GLOBAL_REMOVE_IF_UNREFERENCED const char *CopyVariableListToCacheStr = "CopyVariableListToCache()";
GLOBAL_REMOVE_IF_UNREFERENCED const char *SaveResultsToBdatStr       = "SaveResultsToBdat()";

#ifndef FSP_FLAG
static
VOID *
EvCopyToGlobalMemory (
  VOID * Data,
  UINTN  DataSize
  );
#endif

static
VOID
EvLoadTool (
  SSA_BIOS_SERVICES_PPI           *SsaServicesPpi,
  SSA_BIOS_SERVICES_LOADER_STATE  *LoaderServiceState,
  UINT32                          *Buffer_0_Ptr,
  UINT32                          *ImageHandlePtr,
  UINT32                          *Buffer_1_Ptr
  );

static
VOID
EvLoadConfig (
  SSA_BIOS_SERVICES_PPI           *SsaServicesPpi,
  SSA_BIOS_SERVICES_LOADER_STATE  *LoaderServiceState,
  UINT32                          ConfigCount,
  UINT32                          ConfigIndex,
  UINT32                          *ConfigHandlePtr
  );

#ifndef FSP_FLAG
static
VOID
CopyVariableListToCache (
  SSA_BIOS_SERVICES_PPI           *SsaServicesPpi,
  UINT32                          DestinationHandle,
  EFI_GUID                        *SourceGuidPtr,
  CHAR16                          *SourceName,
  UINT32                          DestinationSize
  );
#endif

static
SSA_STATUS
SaveResultsToBdat (
  SSA_BIOS_SERVICES_PPI           *SsaServicesPpi
  );

extern
UINT32
FlushBios (
  void
  );

static
CHAR8
SsaLoaderSerialGetLineStatusRegister (
  SSA_BIOS_SERVICES_PPI           *SsaServicesPpi
  )
{
  UINT8 data = 0;
  SsaServicesPpi->SsaCommonConfig->ReadIo (SsaServicesPpi, RegWidth8, SSA_LOADER_GLOBALCOMPORT + SSA_LOADER_COM_LINE_STATUS, &data);
  return (CHAR8) data;
}

#define SsaLoaderIsPrintable(a) (((a) >= ' ') && ((a) <= '~') ? (a) : 0)

static
UINT8
SsaLoaderSerialGetChar (
  SSA_BIOS_SERVICES_PPI           *SsaServicesPpi
  )
{
  UINT8 data = SSA_LOADER_COM_EOF;

  if ((SsaLoaderSerialGetLineStatusRegister (SsaServicesPpi) & SSA_LOADER_COM_DATA_READY) == SSA_LOADER_COM_DATA_READY) {
    SsaServicesPpi->SsaCommonConfig->ReadIo (SsaServicesPpi, RegWidth8, SSA_LOADER_GLOBALCOMPORT + SSA_LOADER_COM_RECEIVER_BUFFER, &data);
  }
  return data;
}

static
BOOLEAN
SsaLoaderSerialStopCharacter (
  CHAR8                     ReceivedChar
  )
{
  return (SsaLoaderIsPrintable (ReceivedChar)) || (ReceivedChar == SSA_LOADER_CHAR_CR) || (ReceivedChar == SSA_LOADER_CHAR_LF);
}

static
BOOLEAN
SsaLoaderShouldAbortTargetOnlyTest (
  SSA_BIOS_SERVICES_PPI     *SsaServicesPpi
  )
{
  UINT32 numberSteps = 0;

  DEBUG ((
           DEBUG_ERROR, "Press any letter now to stop the target only test from runnning and continue booting."
           ));

  while (numberSteps < SSA_LOADER_SKIP_TEST_WAIT_STEPS) {
    UINT8 data;

    DEBUG ((
             DEBUG_ERROR, "."
             ));
    data = SsaLoaderSerialGetChar (SsaServicesPpi);
    if ((data != SSA_LOADER_COM_EOF) && (SsaLoaderSerialStopCharacter (data))) {
      DEBUG ((
               DEBUG_ERROR, "\n"
               ));
      return TRUE;
    }
    SsaServicesPpi->SsaCommonConfig->Wait (SsaServicesPpi, SSA_LOADER_SKIP_TEST_WAIT_STEP_SIZE_USEC);
    numberSteps++;
  }
  DEBUG ((
           DEBUG_ERROR, "\n"
           ));
  return FALSE;
}

static
VOID
SsaLoaderOneTimeMessage (
  SSA_BIOS_SERVICES_PPI     *SsaServicesPpi
  )
{
  UINT32 numberSteps = 0;

  DEBUG ((
           DEBUG_ERROR, "BIOS code loader is enabled. Will continue booting in 2 seconds."
           ));
  while (numberSteps < SSA_LOADER_MESSAGE_WAIT_STEPS) {
    DEBUG ((
             DEBUG_ERROR, "."
             ));
    SsaServicesPpi->SsaCommonConfig->Wait (SsaServicesPpi, SSA_LOADER_SKIP_TEST_WAIT_STEP_SIZE_USEC);
    numberSteps++;
  }
}

/**

  The function is used to signal the EV module that checkpoint 'StatusCommand' has been reached.

  @param[in] StatusCommand  - The current checkpoint value.
  @param[in] CheckpointData - General data related to the current checkpoint.

  @retval Nothing

**/
static
MrcStatus
EvLoaderCheckpoint (
  SSA_BIOS_CALLBACKS_PPI    *SsaBiosCallBacksPpi,
  MRC_OEM_STATUS_COMMAND    StatusCommand,
  VOID                      *CheckpointData
  )
{
  SSA_BIOS_SERVICES_LOADER_STATE        *LoaderServiceState;
  SSA_BIOS_SERVICES_PPI                 *SsaServicesPpi;
  EFI_PHYSICAL_ADDRESS                  baseAddress;
  EFI_STATUS                            EfiStatus;
  MrcStatus                             mrcStatus;
  MrcParameters                         *MrcData;
  UINT32                                Buffer_0 = 0;
  UINT32                                ImageHandle = 0;
  UINT32                                Buffer_1 = 0;
  UINT32                                ConfigCount = 0;
  UINT32                                ConfigBuffer = 0;
  UINT32                                ConfigVersionHandle = 0;
  UINT32                                ConfigPointerFixupCountHandle = 0;
  UINT32                                ConfigPointerFixupCount = 0;
  UINT32                                PointerIndex = 0;
  UINT32                                ConfigBlockHandle = 0;
  const SCRATCHPAD_REGISTER_FUNCTIONS   *scratchpadFunctions;
#ifndef FSP_FLAG
  EFI_STATUS                            Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI       *VarAccessPpiPtr = NULL;
#endif

  DEBUG ((
           DEBUG_ERROR, "%a \n",
           EvLoaderCheckpointStr
           ));
#ifndef FSP_FLAG
  Status = PeiServicesLocatePpi (&gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, (VOID **)&VarAccessPpiPtr);
  if (Status == EFI_NOT_FOUND) {
    DEBUG ((
             DEBUG_ERROR, "Read Only Variable PPI NOT found.\n"
             ));
  }
#endif // FSP_FLAG
  DEBUG ((
           DEBUG_ERROR,
           "EviCheckpoint %Xh.\n",
           StatusCommand
           ));

  SsaServicesPpi = NULL;
  EfiStatus = EFI_SUCCESS;

  LoaderServiceState = SsaBiosCallBacksPpi->ModuleState;
  if (LoaderServiceState != NULL) {
    if (LoaderServiceState->RunCheckpoint == 0) {
      EfiStatus = PeiServicesLocatePpi (&gSsaBiosServicesPpiGuid, 0, NULL, (VOID **) &SsaServicesPpi);
      if (EFI_SUCCESS == EfiStatus) {
        MrcData = (MrcParameters *) SsaServicesPpi->SsaCommonConfig->BiosData;
        if (!(MrcData->Inputs.EvLoader)) {
          return mrcSuccess;
        }
        if (LoaderServiceState->LoaderPresenceCheck) {
          if (MrcData->Inputs.EvLoaderDelay) {
            SsaLoaderOneTimeMessage (SsaServicesPpi);
          } else {
            DEBUG ((
                     DEBUG_ERROR, "BIOS code loader is enabled.\n"
                     ));
          }
          LoaderServiceState->LoaderPresenceCheck = FALSE;
        }
        scratchpadFunctions = GetScratchpadFunctions (SsaServicesPpi);
        mrcStatus = (MrcStatus) SsaServicesPpi->SsaCommonConfig->GetBaseAddress (SsaServicesPpi, 0, 0, 0, MCH_BAR, &baseAddress);
        LoaderServiceState->RunCheckpoint = scratchpadFunctions->readScratchPad0 (SsaServicesPpi, baseAddress);
        if (LoaderServiceState->RunCheckpoint != 0) {
          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "%a RunCheckpoint is set to %Xh\n",
            EvLoaderCheckpointStr,
            LoaderServiceState->RunCheckpoint
            );
        }
      } else {
        DEBUG ((
                 DEBUG_ERROR,
                 "%a LoacatePpi failed\n",
                 EvLoaderCheckpointStr
                 ));
      }
    }

    if (LoaderServiceState->RunCheckpoint == StatusCommand) {
      if ((SsaServicesPpi == NULL) ||
          (EFI_SUCCESS != EfiStatus)) {
        EfiStatus = PeiServicesLocatePpi (&gSsaBiosServicesPpiGuid, 0, NULL, (VOID **) &SsaServicesPpi);
      }
      if (EFI_SUCCESS == EfiStatus) {
        MrcData = (MrcParameters *) SsaServicesPpi->SsaCommonConfig->BiosData;
        if (!(MrcData->Inputs.EvLoader)) {
          return mrcSuccess;
        }
        if (LoaderServiceState->LoadFromTarget) {
          UINT32 configIndex = 0;
#ifdef FSP_FLAG
          if (MrcData->Inputs.MmaTestContentPtr == 0) {
            DEBUG ((
                     DEBUG_ERROR, "%a - MmaTestContentPtr is NULL, aborted execution of tool.\n",
                     EvLoaderCheckpointStr
                     ));
            return mrcSuccess;
          }
#endif
          //
          //Check if we should skip execution of test and continue booting.
          //On external BIOS this will be done on a different place
          //
          if ((MrcData->Inputs.EvLoaderDelay) && (SsaLoaderShouldAbortTargetOnlyTest (SsaServicesPpi))) {
            DEBUG ((
                     DEBUG_ERROR, "Aborted execution of tool.\n"
                     ));
            return mrcSuccess;
          }

          EV_LOADER_PRINT (
            DEBUG_ERROR, "if(LoaderServiceState->LoadFromTarget) \n"
            );
          //
          // Reassemble tool, load tool, iterate over each config and reassemble config, load config, run tool and repeat.
          //

          //
          // Load tool.
          //
          EvLoadTool (SsaServicesPpi, LoaderServiceState, &Buffer_0, &ImageHandle, &Buffer_1);

          EV_LOADER_PRINT (
            DEBUG_ERROR, "Returned from %a \n",
            EvLoadToolStr
            );
          EV_LOADER_PRINT (
            DEBUG_ERROR, "SystemConfigRevision = %d \n", ((SSA_BIOS_SYS_CONFIG_HEADER *) LoaderServiceState->SysConfig)->SystemConfigRevision
            );
          EV_LOADER_PRINT (
            DEBUG_ERROR, "ToolSize = %d \n", ((SSA_BIOS_SYS_CONFIG_HEADER *) LoaderServiceState->SysConfig)->ToolSize
            );
          EV_LOADER_PRINT (
            DEBUG_ERROR, "PostCode = 0x%08X  \n", ((SSA_BIOS_SYS_CONFIG_HEADER *) LoaderServiceState->SysConfig)->PostCode
            );
          EV_LOADER_PRINT (
            DEBUG_ERROR, "PrintLevel = %d \n", ((SSA_BIOS_SYS_CONFIG_HEADER *) LoaderServiceState->SysConfig)->PrintLevel
            );
          EV_LOADER_PRINT (
            DEBUG_ERROR, "ConfigCount = %d \n", ((SSA_BIOS_SYS_CONFIG_HEADER *) LoaderServiceState->SysConfig)->ConfigCount
            );
          //
          // Iterate over each config.
          //
          ConfigCount = ((SSA_BIOS_SYS_CONFIG_HEADER *) LoaderServiceState->SysConfig)->ConfigCount;

          if (ConfigCount) {// Execute for each config
            for (configIndex = 0; configIndex < ConfigCount; configIndex++) {
              UINT32  entryPoint = 0;

              EV_LOADER_PRINT (
                DEBUG_ERROR, "configIndex = %d \n", configIndex
                );
              //
              // Load config.
              //
              EvLoadConfig (SsaServicesPpi, LoaderServiceState, ConfigCount, configIndex, &ConfigBuffer);
              ConfigVersionHandle = ConfigBuffer;
              ConfigPointerFixupCountHandle = ConfigBuffer + sizeof (UINT32);
              ConfigPointerFixupCount = *(UINT32*) ConfigPointerFixupCountHandle;
              ConfigBlockHandle = ConfigPointerFixupCountHandle + sizeof (UINT32) + (ConfigPointerFixupCount * sizeof (UINT32));
              //
              // Fixup string pointers.
              //
              for (PointerIndex = 0; PointerIndex < ConfigPointerFixupCount; PointerIndex++) {
                UINT32 PointerOffset = 0;
                UINT32 StringPointerLocation = 0;

                PointerOffset = *((UINT32*) ((ConfigPointerFixupCountHandle + sizeof (UINT32)) + (PointerIndex * sizeof (UINT32))));
                StringPointerLocation = ConfigBlockHandle + PointerOffset;
                *((UINT32*) StringPointerLocation) = *((UINT32*) StringPointerLocation) + ConfigBlockHandle;
              }
              //
              // Run tool.
              //
              EV_LOADER_PRINT (
                DEBUG_ERROR, "About to run tool... \n"
                );

              entryPoint = GetPeEntrypoint ((UINT8 *) ImageHandle);
              ((EvToolEntryPoint*) entryPoint) (SsaServicesPpi, (UINT32 *) ConfigBlockHandle);

              EV_LOADER_PRINT (
                DEBUG_ERROR, "The tool has finished execution. \n"
                );
              EV_LOADER_PRINT (
                DEBUG_ERROR, "SsaServicesPpi->SsaResultsConfig->ResultsData =  0x%08X \n", SsaServicesPpi->SsaResultsConfig->ResultsData
                );
              //
              // Return results?
              //
              SaveResultsToBdat (SsaServicesPpi);
              //
              // Repeat.
              //
            }
          } else {// Execute a test w/o a config
            UINT32  entryPoint = 0;
            //
            // Run tool.
            //
            EV_LOADER_PRINT (
              DEBUG_ERROR, "About to run tool... \n"
              );

            entryPoint = GetPeEntrypoint ((UINT8 *) ImageHandle);
            ((EvToolEntryPoint*) entryPoint) (SsaServicesPpi, NULL);
            //
            // Return results?
            //
            SaveResultsToBdat (SsaServicesPpi);
          }

        } else {
          EV_LOADER_PRINT (
            DEBUG_ERROR, "NOT: if(LoaderServiceState->LoadFromTarget) \n"
            );
          mrcStatus = EvItpDownloadCmd (SsaServicesPpi, CheckpointData);
        }
      } else {
        EV_LOADER_PRINT (
          DEBUG_ERROR,
          "EvLoaderCheckpoint LoacatePpi failed\n",
          NULL
          );
      }
    }
  }

  if (Buffer_0 != 0) {
    EV_LOADER_PRINT (DEBUG_ERROR, "Freeing Buffer_0 at 0x%x\n", Buffer_0);
    SsaServicesPpi->SsaCommonConfig->Free (SsaServicesPpi, (UINT32 *) Buffer_0);
  }

  if (ImageHandle != 0) {
    EV_LOADER_PRINT (DEBUG_ERROR, "Freeing ImageHandle at 0x%x\n", ImageHandle);
    SsaServicesPpi->SsaCommonConfig->Free (SsaServicesPpi, (UINT32 *) ImageHandle);
  }

  if (Buffer_1 != 0) {
    EV_LOADER_PRINT (DEBUG_ERROR, "Freeing Buffer_1 at 0x%x\n", Buffer_1);
    SsaServicesPpi->SsaCommonConfig->Free (SsaServicesPpi, (UINT32 *) Buffer_1);
  }

  return mrcSuccess;
}

#ifdef FSP_FLAG
/**

  The main entry function for the EVI callback library for FSP. This code installs the EVI callback PPI.

  @retval EFI_SUCCESS

**/
VOID
EFIAPI
InstallEvLoader (
  VOID
  )
{
  EFI_PEI_PPI_DESCRIPTOR      *EvLoaderDesc;
  SSA_BIOS_CALLBACKS_PPI      *EvLoaderPpi;
  EFI_STATUS                  Status;
  SSA_BIOS_SERVICES_LOADER_STATE *LoaderServiceState = NULL;

  DEBUG ((
           DEBUG_ERROR, "%a \n",
           EvLoaderEntryPointStr
           ));

  EvLoaderPpi = (SSA_BIOS_CALLBACKS_PPI *) AllocatePool (sizeof (SSA_BIOS_CALLBACKS_PPI));
  ASSERT (EvLoaderPpi != NULL);
  ZeroMem (EvLoaderPpi, sizeof (SSA_BIOS_CALLBACKS_PPI));
  EvLoaderPpi->MrcCheckpoint = EvLoaderCheckpoint;
  EvLoaderPpi->ModuleState = (SSA_BIOS_SERVICES_LOADER_STATE *) AllocatePool (sizeof (SSA_BIOS_SERVICES_LOADER_STATE));
  ASSERT (EvLoaderPpi->ModuleState != NULL);
  ZeroMem (EvLoaderPpi->ModuleState, sizeof (SSA_BIOS_SERVICES_LOADER_STATE));

  EvLoaderDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocatePool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  ASSERT (EvLoaderDesc != NULL);
  ZeroMem (EvLoaderDesc, sizeof (EFI_PEI_PPI_DESCRIPTOR));
  EvLoaderDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  EvLoaderDesc->Guid = &gSsaBiosCallBacksPpiGuid;
  EvLoaderDesc->Ppi = EvLoaderPpi;

  Status = PeiServicesInstallPpi (EvLoaderDesc);
  ASSERT_EFI_ERROR (Status);

  LoaderServiceState = EvLoaderPpi->ModuleState;

  if (Status == EFI_SUCCESS) {// Target-Only
    SSA_BIOS_SYS_CONFIG_HEADER * sysConfigHeaderPtr = NULL;

    sysConfigHeaderPtr = (SSA_BIOS_SYS_CONFIG_HEADER *) AllocatePool (sizeof (SSA_BIOS_SYS_CONFIG_HEADER));
    ASSERT (sysConfigHeaderPtr != NULL);
    ZeroMem (sysConfigHeaderPtr, sizeof (SSA_BIOS_SYS_CONFIG_HEADER));

    EV_LOADER_PRINT (
      DEBUG_ERROR, "%a -- Target-Only \n",
      EvLoaderEntryPointStr
      );

    LoaderServiceState->LoadFromTarget = TRUE;
    //
    // Skylake Bios SSA checkpoint is at post code 0xDD7F
    // FSP currently only supports one configuration at a time.
    //
    sysConfigHeaderPtr->PostCode = 0xDD7F;
    sysConfigHeaderPtr->SystemConfigRevision = 1;
    sysConfigHeaderPtr->ConfigCount = 1;
    LoaderServiceState->SysConfig = sysConfigHeaderPtr;
    LoaderServiceState->RunCheckpoint = sysConfigHeaderPtr->PostCode;
  } else {
    ASSERT_EFI_ERROR (Status);
  }
}
#else
/**

  The main entry function for the EVI callback library. This code installs the EVI callback PPI.

  @retval EFI_SUCCESS

**/
VOID
EFIAPI
InstallEvLoader (
  VOID
  )
{
  EFI_PEI_PPI_DESCRIPTOR      *EvLoaderDesc;
  SSA_BIOS_CALLBACKS_PPI      *EvLoaderPpi;
  EFI_STATUS                  Status;
  UINT8  DataBuffer[VAR_BUFFER_SIZE];
  UINTN  DataSize = sizeof (DataBuffer);
  SSA_BIOS_SERVICES_LOADER_STATE *LoaderServiceState = NULL;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VarAccessPpiPtr = NULL;

  DEBUG ((
           DEBUG_ERROR, "%a \n",
           EvLoaderEntryPointStr
           ));

  EvLoaderPpi = (SSA_BIOS_CALLBACKS_PPI *) AllocatePool (sizeof (SSA_BIOS_CALLBACKS_PPI));
  ASSERT (EvLoaderPpi != NULL);
  ZeroMem (EvLoaderPpi, sizeof (SSA_BIOS_CALLBACKS_PPI));
  EvLoaderPpi->MrcCheckpoint = EvLoaderCheckpoint;
  EvLoaderPpi->ModuleState = (SSA_BIOS_SERVICES_LOADER_STATE *) AllocatePool (sizeof (SSA_BIOS_SERVICES_LOADER_STATE));
  ASSERT (EvLoaderPpi->ModuleState != NULL);
  ZeroMem (EvLoaderPpi->ModuleState, sizeof (SSA_BIOS_SERVICES_LOADER_STATE));

  EvLoaderDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocatePool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  ASSERT (EvLoaderDesc != NULL);
  ZeroMem (EvLoaderDesc, sizeof (EFI_PEI_PPI_DESCRIPTOR));
  EvLoaderDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  EvLoaderDesc->Guid = &gSsaBiosCallBacksPpiGuid;
  EvLoaderDesc->Ppi = EvLoaderPpi;

  Status = PeiServicesInstallPpi (EvLoaderDesc);
  ASSERT_EFI_ERROR (Status);
  //
  // Check for Target-only (NVRAM) Variable.
  //

  Status = PeiServicesLocatePpi (&gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, (VOID **) &VarAccessPpiPtr);
  ASSERT_EFI_ERROR (Status);

  EV_LOADER_PRINT (
    DEBUG_ERROR, "%a -- About to call ZeroMem (DataBuffer, sizeof(DataBuffer))\n",
    EvLoaderEntryPointStr
    );

  ZeroMem (DataBuffer, sizeof (DataBuffer));

  EV_LOADER_PRINT (
    DEBUG_ERROR, "%a -- About to call VarAccessPpiPtr->PeiGetVariable()\n",
    EvLoaderEntryPointStr
    );

  Status = VarAccessPpiPtr->GetVariable (VarAccessPpiPtr, SYS_CONFIG_NAME, &gSsaBiosVariablesGuid, NULL, &DataSize, (VOID *) DataBuffer);

  EV_LOADER_PRINT (
    DEBUG_ERROR, "%a -- After call VarAccessPpiPtr->PeiGetVariable()\n",
    EvLoaderEntryPointStr
    );

  LoaderServiceState = EvLoaderPpi->ModuleState;

  if (Status == EFI_NOT_FOUND) {// Host-Target Hybrid
    EV_LOADER_PRINT (
      DEBUG_ERROR, "%a -- Host-Target Hybrid \n",
      EvLoaderEntryPointStr
      );
    LoaderServiceState->LoadFromTarget = FALSE;
    //
    //On external BIOS we should check for cancellation on every boot, not only on target only tests.
    //This is OK because loader is only included on special builds.
    //We do not do this on internal BIOS because this would slow down execution.
    //
    LoaderServiceState->LoaderPresenceCheck = TRUE;

  } else if (Status == EFI_SUCCESS) {// Target-Only
    SSA_BIOS_SYS_CONFIG_HEADER * sysConfigHeaderPtr = NULL;
    VOID * NewSysConfigPtr = NULL;

    EV_LOADER_PRINT (
      DEBUG_ERROR, "%a -- Target-Only \n",
      EvLoaderEntryPointStr
      );

    NewSysConfigPtr = EvCopyToGlobalMemory (DataBuffer, DataSize);
    ASSERT (NewSysConfigPtr != NULL);
    LoaderServiceState->LoadFromTarget = TRUE;
    LoaderServiceState->SysConfig = NewSysConfigPtr;
    sysConfigHeaderPtr = NewSysConfigPtr;
    LoaderServiceState->RunCheckpoint = sysConfigHeaderPtr->PostCode;
  } else {
    ASSERT_EFI_ERROR (Status);
  }
}
#endif // FSP_FLAG

#ifndef FSP_FLAG
static
VOID *
EvCopyToGlobalMemory (
  VOID * Data,
  UINTN  DataSize
  )
{
  VOID * NewBlockPtr = AllocatePool (DataSize);

  CopyMem (NewBlockPtr, Data, DataSize);
  return NewBlockPtr;
}
#endif // FSP_FLAG

static
VOID
EvLoadTool (
  SSA_BIOS_SERVICES_PPI     *SsaServicesPpi,
  SSA_BIOS_SERVICES_LOADER_STATE *LoaderServiceState,
  UINT32                    *Buffer_0_Ptr,
  UINT32                    *ImageHandlePtr,
  UINT32                    *Buffer_1_Ptr
  )
{
#ifndef FSP_FLAG
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VarAccessPpiPtr = NULL;
  EFI_STATUS  Status;
#else
  MrcParameters               *MrcData;
#endif // FSP_FLAG
  UINT32      ToolSize    = 0;
  UINT32      imageHandle = 0;
  UINT32      buffer_4k_0 = 0;
  UINT32      buffer_4k_1 = 0;

  DEBUG ((
           DEBUG_ERROR, "%a \n",
           EvLoadToolStr
           ));

  //
  // Reassemble tool.
  //

  ASSERT (LoaderServiceState->SysConfig != NULL);

#ifndef FSP_FLAG
  ToolSize = ((SSA_BIOS_SYS_CONFIG_HEADER *) LoaderServiceState->SysConfig)->ToolSize;
  Status = PeiServicesLocatePpi (&gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, (VOID **) &VarAccessPpiPtr);
  ASSERT_EFI_ERROR (Status);
#else
  MrcData = (MrcParameters *) SsaServicesPpi->SsaCommonConfig->BiosData;
  ToolSize = MrcData->Inputs.MmaTestContentSize;
  DEBUG ((
           DEBUG_ERROR, "%a - MmaTestContentSize = %xh\n",
           EvLoadToolStr,
           ToolSize
           ));
  ((SSA_BIOS_SYS_CONFIG_HEADER *) LoaderServiceState->SysConfig)->ToolSize = ToolSize;
#endif // FSP_FLAG

  //
  // Reserve 4KB buffers below and above the tool image.
  // TODO: Put the next 3 buffers on a single one.
  //
  buffer_4k_0 = (UINT32) SsaServicesPpi->SsaCommonConfig->Malloc (SsaServicesPpi, (1024 * 4));
  imageHandle = (UINT32) SsaServicesPpi->SsaCommonConfig->Malloc (SsaServicesPpi, ToolSize);
  buffer_4k_1 = (UINT32) SsaServicesPpi->SsaCommonConfig->Malloc (SsaServicesPpi, (1024 * 4));

  if (!imageHandle) {
    EV_LOADER_PRINT (
      DEBUG_ERROR, "%a  !imageHandle ... \n",
      EvLoadToolStr
      );
    ASSERT (FALSE);
  }

  if (!buffer_4k_0) {
    EV_LOADER_PRINT (
      DEBUG_ERROR, "%a  !buffer_4k_0 ... \n",
      EvLoadToolStr
      );
    ASSERT (FALSE);
  }

  if (!buffer_4k_1) {
    EV_LOADER_PRINT (
      DEBUG_ERROR, "%a  !buffer_4k_1 ... \n",
      EvLoadToolStr
      );
    ASSERT (FALSE);
  }

#ifndef FSP_FLAG
  EV_LOADER_PRINT (
    DEBUG_ERROR, "About to call %a \n",
    CopyVariableListToCacheStr
    );
  CopyVariableListToCache (SsaServicesPpi, imageHandle, &gSsaBiosVariablesGuid, TOOL_BINARY_NAME, ToolSize);
  EV_LOADER_PRINT (
    DEBUG_ERROR, "Just returned from %a \n",
    CopyVariableListToCacheStr
    );
#else
  CopyMem ((VOID *) imageHandle, (VOID *) MrcData->Inputs.MmaTestContentPtr, ToolSize);
  EV_LOADER_PRINT (
    DEBUG_ERROR, "%a -- MmaTestContentPtr = %xh\n",
    EvLoadToolStr,
    imageHandle
    );
#endif // FSP_FLAG

  EV_LOADER_PRINT (
    DEBUG_ERROR, "About to call PlacePeImage((UINT8 *)imageHandle) \n"
    );
  PlacePeImage ((UINT8 *) imageHandle);
  FlushBios ();

  EV_LOADER_PRINT (
    DEBUG_ERROR, "Just called PlacePeImage((UINT8 *)imageHandle) \n"
    );
  //
  // Return the buffers and tool image addresses.
  //
  *Buffer_0_Ptr     = buffer_4k_0;
  *ImageHandlePtr   = imageHandle;
  *Buffer_1_Ptr     = buffer_4k_1;
}


static
VOID
EvLoadConfig (
  SSA_BIOS_SERVICES_PPI     *SsaServicesPpi,
  SSA_BIOS_SERVICES_LOADER_STATE *LoaderServiceState,
  UINT32                    ConfigCount,
  UINT32                    ConfigIndex,
  UINT32                    *ConfigHandlePtr
  )
{
  UINT32                      ConfigBuffer = 0;
  UINT32                      *VarSizePtr = 0;
#ifndef FSP_FLAG
  UINT32                      SysConfigHandle = 0;
  VOID                        *VarNameHeaderPtr = NULL;
  CHAR16                      HeadVarName[VAR_NULL_NAME_LENGTH];
#else
  MrcParameters               *MrcData;
#endif // FSP_FLAG


  EV_LOADER_PRINT (
    DEBUG_ERROR, "%a \n",
    EvLoadConfigStr
    );

#ifndef FSP_FLAG
  SysConfigHandle = (UINT32) ((SSA_BIOS_SYS_CONFIG_HEADER *) LoaderServiceState->SysConfig);
  //
  // Lookup config variable name address.
  //
  EV_LOADER_PRINT (
    DEBUG_ERROR, "Lookup config variable name... \n"
    );
  VarNameHeaderPtr = (VOID*) ((SysConfigHandle + sizeof (SSA_BIOS_SYS_CONFIG_HEADER)) + (ConfigIndex * VAR_NAME_SIZE));
  ZeroMem (HeadVarName, VAR_NULL_NAME_SIZE);
  CopyMem (HeadVarName, VarNameHeaderPtr, VAR_NAME_SIZE);
  EV_LOADER_PRINT (
    DEBUG_ERROR, "HeadVarName = %s \n", HeadVarName
    );
#endif // FSP_FLAG
  //
  // Lookup config variable size address.
  //
  EV_LOADER_PRINT (
    DEBUG_ERROR, "Lookup config variable size... \n"
    );
#ifndef FSP_FLAG
  VarSizePtr = (UINT32 *) ((SysConfigHandle + sizeof (SSA_BIOS_SYS_CONFIG_HEADER)) + (ConfigCount * VAR_NAME_SIZE) + (ConfigIndex * sizeof (UINT32)));
#else
  MrcData = (MrcParameters *) SsaServicesPpi->SsaCommonConfig->BiosData;
  VarSizePtr = &MrcData->Inputs.MmaTestConfigSize;
#endif // FSP_FLAG
  EV_LOADER_PRINT (
    DEBUG_ERROR, "VarSize = %d \n", *VarSizePtr
    );
  //
  // Allocate the config cache.
  //
  ConfigBuffer = (UINT32) SsaServicesPpi->SsaCommonConfig->Malloc (SsaServicesPpi, *VarSizePtr);

  if (!ConfigBuffer) {
    EV_LOADER_PRINT (
      DEBUG_ERROR, "%a  !ConfigBuffer ... \n",
      EvLoadConfigStr
      );
  }
#ifndef FSP_FLAG
  EV_LOADER_PRINT (
    DEBUG_ERROR, "About to call %a \n",
    CopyVariableListToCacheStr
    );
  CopyVariableListToCache (SsaServicesPpi, ConfigBuffer, &gSsaBiosVariablesGuid, HeadVarName, *VarSizePtr);
  EV_LOADER_PRINT (
    DEBUG_ERROR, "Just returned from %a \n",
    CopyVariableListToCacheStr
    );
#else
  CopyMem ((VOID *) ConfigBuffer, (VOID *) MrcData->Inputs.MmaTestConfigPtr, *VarSizePtr);
  EV_LOADER_PRINT (
    DEBUG_ERROR, "%a -- MmaTestConfigPtr = %xh\n",
    EvLoadConfigStr,
    ConfigBuffer
    );
#endif // FSP_FLAG

  *ConfigHandlePtr = ConfigBuffer;
}

#ifndef FSP_FLAG
static
VOID
CopyVariableListToCache (
  SSA_BIOS_SERVICES_PPI     *SsaServicesPpi,
  UINT32                    DestinationHandle,
  EFI_GUID                  *SourceVarGuidPtr,
  CHAR16                    *SourceVarName,
  UINT32                    DestinationSize
  )
{
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VarAccessPpiPtr = NULL;
  EFI_STATUS  Status;
  UINT8       DataBuffer[VAR_BUFFER_SIZE];
  UINT8 *     DataBufferPtr = DataBuffer;
  UINTN       DataSize = sizeof (DataBuffer);
  UINT32      BytesRead = 0;
  VOID *      DestinationFillPtr = NULL;
  CHAR16      NextVarName[VAR_NULL_NAME_LENGTH];

  DEBUG ((
           DEBUG_ERROR, "Entered %a \n",
           CopyVariableListToCacheStr
           ));
  Status = PeiServicesLocatePpi (&gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, (VOID **)&VarAccessPpiPtr);
  ASSERT_EFI_ERROR (Status);

  if (SourceVarName[VAR_NAME_LENGTH] != 0) {
    SourceVarName[VAR_NAME_LENGTH] = 0;
  }

  Status = VarAccessPpiPtr->GetVariable (VarAccessPpiPtr, SourceVarName, SourceVarGuidPtr, NULL, &DataSize, DataBufferPtr);
  EV_LOADER_PRINT (
    DEBUG_ERROR, "Just called VarAccessPpiPtr->PeiGetVariable() \n"
    );
  ASSERT_EFI_ERROR (Status);
  ZeroMem (NextVarName, VAR_NULL_NAME_SIZE);
  CopyMem (NextVarName, DataBufferPtr, VAR_NAME_SIZE);
  BytesRead += (DataSize - VAR_NAME_SIZE);

  DestinationFillPtr = (VOID *)DestinationHandle; // Start at the front of the image block
  CopyMem (DestinationFillPtr, (DataBufferPtr + VAR_NAME_SIZE), (DataSize - VAR_NAME_SIZE)); // Copy all but the first name bytes

  while (StrCmp (NextVarName, NULL_STRING) != 0) {
    UINT32 ActualDataSize = 0;

    ASSERT ((UINT32)DestinationFillPtr < ((UINT32)DestinationHandle + DestinationSize)); // Is it inside of the image block?

    DestinationFillPtr = (VOID *)((UINTN)DestinationFillPtr + (DataSize - VAR_NAME_SIZE)); // Increment where in image to copy to

    NextVarName[VAR_NAME_LENGTH] = 0;
    Status = VarAccessPpiPtr->GetVariable (VarAccessPpiPtr, NextVarName, SourceVarGuidPtr, NULL, &DataSize, DataBufferPtr);
    ASSERT_EFI_ERROR (Status);
    EV_LOADER_PRINT (
      DEBUG_ERROR, "About to call ZeroMem(NextVarName, VAR_NULL_NAME_LENGTH)... \n"
      );
    ZeroMem (NextVarName, VAR_NULL_NAME_SIZE);
    EV_LOADER_PRINT (
      DEBUG_ERROR, "CopyMem(NextVarName, DataBufferPtr, VAR_NAME_LENGTH)... \n"
      );
    CopyMem (NextVarName, DataBufferPtr, VAR_NAME_SIZE);
    EV_LOADER_PRINT (
      DEBUG_ERROR, "NextVarName = %s \n", NextVarName
      );
    ActualDataSize = (DataSize - VAR_NAME_SIZE);
    EV_LOADER_PRINT (
      DEBUG_ERROR, "ActualDataSize = %d \n", ActualDataSize
      );
    BytesRead += ActualDataSize;

    if (ActualDataSize > 0) {
      ASSERT ( (UINT32)DestinationFillPtr >= DestinationHandle );                                         // Is it above the bottom?
      ASSERT ( ((UINT32)DestinationFillPtr + ActualDataSize) <=  (DestinationHandle + DestinationSize) ); // Is it below the expected top?
      CopyMem (DestinationFillPtr, (DataBufferPtr + VAR_NAME_SIZE), ActualDataSize);          // Copy all but the first name bytes
      FlushBios ();
    }

  };

  DEBUG ((
           DEBUG_ERROR, "ASSERT(%d == %d) \n", BytesRead, DestinationSize
           ));
  ASSERT (BytesRead == DestinationSize);

}
#endif // FSP_FLAG


static
SSA_STATUS
SaveResultsToBdat (
  SSA_BIOS_SERVICES_PPI     *SsaServicesPpi
  )
{
  UINT8 * ResultsData = NULL;
  RESULTS_DATA_HDR * ResultsDataHdr = NULL;
  UINT32 ResultsDataSize = 0;
  SSA_STATUS RetStatus = Failure;

  if (SsaServicesPpi->SsaResultsConfig->ResultsData != NULL) {
    EV_LOADER_PRINT (
      DEBUG_ERROR, "Sending results via %a... \n",
      SaveResultsToBdatStr
      );

    ResultsData = (UINT8*) SsaServicesPpi->SsaResultsConfig->ResultsData;
    ResultsDataHdr = (RESULTS_DATA_HDR *) ResultsData;
    //
    // Reduce Result Data Size by removing unused result entries from Result Capacity.
    //
    ResultsDataHdr->RsBlock.ResultCapacity = ResultsDataHdr->RsBlock.ResultElementCount;
    ResultsDataSize = sizeof (RESULTS_DATA_HDR) + ResultsDataHdr->MdBlock.MetadataSize + (ResultsDataHdr->RsBlock.ResultElementSize * ResultsDataHdr->RsBlock.ResultCapacity);
    RetStatus = SsaServicesPpi->SsaCommonConfig->SaveToBdat (SsaServicesPpi, &gSsaBiosResultsGuid, ResultsData, ResultsDataSize);

    EV_LOADER_PRINT (
      DEBUG_ERROR, "Returned from %a. \n",
      SaveResultsToBdatStr
      );

    if (RetStatus != Success) {
      DEBUG ((
               DEBUG_ERROR, "%a did NOT return Success!\n",
               SaveResultsToBdatStr
               ));
    }
  } else {
    DEBUG ((
             DEBUG_ERROR, "NOT sending results via %a.  ResultsData is NULL. \n",
             SaveResultsToBdatStr
             ));

    RetStatus = Failure;
  }

  return RetStatus;
}
