/** @file
  Dump whole MEBX_BPF and serial out.

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

#include <PiDxe.h>
#include <Library/DebugLib.h>
#include "BiosExtensionLoader.h"

/**
  Dump MEBx BIOS Params

  @param[in] MebxBiosParams       MEBx BIOS params

**/
VOID
DxeMebxBiosParamsDebugDump (
  IN MEBX_BPF                     *MebxBiosParams
  )
{
  DEBUG ((DEBUG_INFO, "\n------------------------ MebxBiosParams Dump Begin -----------------\n"));
  DEBUG ((DEBUG_INFO, " BpfVersion : 0x%x\n", MebxBiosParams->BpfVersion));
  DEBUG ((DEBUG_INFO, " CpuReplacementTimeout : 0x%x\n", MebxBiosParams->CpuReplacementTimeout));
  DEBUG ((DEBUG_INFO, " ActiveRemoteAssistanceProcess : 0x%x\n", MebxBiosParams->ActiveRemoteAssistanceProcess));
  DEBUG ((DEBUG_INFO, " CiraTimeout : 0x%x\n", MebxBiosParams->CiraTimeout));
  DEBUG ((DEBUG_INFO, " OemFlags : 0x%x\n", MebxBiosParams->OemFlags));
  DEBUG ((DEBUG_INFO, "MebxDebugFlags ---\n"));
  DEBUG ((DEBUG_INFO, " Port80 : 0x%x\n", MebxBiosParams->MebxDebugFlags.Port80));
  DEBUG ((DEBUG_INFO, " MeBiosSyncDataPtr : 0x%x\n", MebxBiosParams->MeBiosSyncDataPtr));
  DEBUG ((DEBUG_INFO, " UsbKeyDataStructurePtr : 0x%x\n", MebxBiosParams->UsbKeyDataStructurePtr));
  DEBUG ((DEBUG_INFO, "OemResolutionSettings ---\n"));
  DEBUG ((DEBUG_INFO, " MebxNonUiTextMode : 0x%x\n", MebxBiosParams->OemResolutionSettings.MebxNonUiTextMode));
  DEBUG ((DEBUG_INFO, " MebxUiTextMode : 0x%x\n", MebxBiosParams->OemResolutionSettings.MebxUiTextMode));
  DEBUG ((DEBUG_INFO, " MebxUiTextMode : 0x%x\n", MebxBiosParams->OemResolutionSettings.MebxGraphicsMode));
  DEBUG ((DEBUG_INFO, "\n------------------------ MebxBiosParams Dump End -------------------\n"));
}

