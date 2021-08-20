/** @file
  This file contains the main entry point for the MRC mini-BIOS.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2014 Intel Corporation.

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
#include "MrcSsaServices.h"
#include "MrcSsaInitialize.h"
#include "MrcDebugPrint.h"
#include "MrcDebugHook.h"
#include "MrcGlobal.h"
#ifndef MRC_MINIBIOS_BUILD
#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiServicesLib.h>
extern EFI_GUID gSsaBiosServicesPpiGuid;
#endif

#ifdef SSA_FLAG

/**
  Initialize the SsaBiosServices data structure.

  @param[in] MrcData  - The MRC global data area.

  @retval Nothing
**/
void
SsaBiosInitialize (
  IN MrcParameters *MrcData
  )
{
  MrcIntOutput           *IntOutputs;
  SSA_BIOS_FUNCTION_RW   *SsaBios;
  SSA_BIOS_SERVICES_PPI  *SsaBiosServices;
  MRC_FUNCTION           *MrcCall;
  MrcDebug               *Debug;

#ifndef MRC_MINIBIOS_BUILD
  EFI_PEI_PPI_DESCRIPTOR *SsaBiosServicesPpiDesc;
  EFI_STATUS             Status;
#endif

  IntOutputs      = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Debug           = &MrcData->Outputs.Debug;
  MrcCall         = MrcData->Inputs.Call.Func;
#ifdef MRC_MINIBIOS_BUILD
  SsaBios         = &IntOutputs->SsaBiosServicesBuffer;
  SsaBiosServices = &SsaBios->SsaBiosPointers;
#else
  SsaBios = (SSA_BIOS_FUNCTION_RW *) AllocatePool (sizeof (SSA_BIOS_FUNCTION_RW));
  ASSERT (SsaBios != NULL);
  MrcCall->MrcSetMem ((UINT8 *) SsaBios, sizeof (SSA_BIOS_FUNCTION_RW), 0);
  SsaBiosServices = &SsaBios->SsaBiosPointers;
  IntOutputs->SsaBiosServicesPpi = (UINT32) SsaBiosServices;
#endif

  if (SsaBios != NULL) {
    //
    // Since some of the SSA structures contain R/W data, we need to move them from code space to data space.
    //
    MrcCall->MrcCopyMem ((UINT8 *) SsaBiosServices,            (UINT8 *) &SsaBiosServicesPpi, sizeof (SSA_BIOS_SERVICES_PPI));
    MrcCall->MrcCopyMem ((UINT8 *) &SsaBios->SsaCommonConfig,  (UINT8 *) &SsaCommonConfig,    sizeof (SSA_COMMON_CONFIG));
    MrcCall->MrcCopyMem ((UINT8 *) &SsaBios->SsaResultsConfig, (UINT8 *) &SsaResultsConfig,   sizeof (SSA_RESULTS_CONFIG));
    MrcCall->MrcCopyMem ((UINT8 *) &SsaBios->SsaMemoryConfig,  (UINT8 *) &SsaMemoryConfig,    sizeof (SSA_MEMORY_CONFIG));
    SsaBiosServices->SsaCommonConfig  = &SsaBios->SsaCommonConfig;
    SsaBiosServices->SsaMemoryConfig  = &SsaBios->SsaMemoryConfig;
    SsaBiosServices->SsaResultsConfig = &SsaBios->SsaResultsConfig;
    SsaBios->SsaCommonConfig.BiosData = MrcData;
    SsaBios->SsaMemoryConfig.MrcData  = MrcData;


#ifndef MRC_MINIBIOS_BUILD
    SsaBiosServicesPpiDesc        = &SsaBios->SsaPpiDescriptor;
    SsaBiosServicesPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    SsaBiosServicesPpiDesc->Guid  = &gSsaBiosServicesPpiGuid;
    SsaBiosServicesPpiDesc->Ppi   = SsaBiosServices;
    Status                        = PeiServicesInstallPpi (SsaBiosServicesPpiDesc);
    ASSERT_EFI_ERROR (Status);
#endif

#ifdef SSA_DEBUG_PRINT
    Debug->PostCode[MRC_POST_CODE_WRITE] = MRC_SSA_STOP_POINT;
    Debug->PostCode[MRC_POST_CODE_READ]  = MRC_SSA_STOP_POINT;
#endif

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SSA Interface ready\n");
  }
  return;
}

#endif // SSA_FLAG
