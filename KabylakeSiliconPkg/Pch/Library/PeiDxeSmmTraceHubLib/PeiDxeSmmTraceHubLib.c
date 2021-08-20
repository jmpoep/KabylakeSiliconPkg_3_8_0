/** @file
  Pei/Dxe/Smm TraceHub Lib.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2015 Intel Corporation.

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
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/MmPciLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <PchAccess.h>

/**
  Calculate TraceHub Trace Address.
  According to Software Trace Hub HAS 1.0 - 3.2.1 STMR
  Master number for the SKL PCH is >=32 and <256, for BIOS usage specifically, it should be >=32 and <=39
  Channel number for BIOS usage should be >=13 and <=22

  @param [in] Master                    Master is being used.
  @param [in] Channel                   Channel is being used.
  @param [out] TraceAddress             TraceHub Address for the Master/Channel is being used.

  @retval EFI_SUCCESS                   Retrieve correct Address.
          EFI_DEVICE_ERROR              TraceHub device is power gated
          Other                         Failed to retrieve correct TraceHub Address.

**/
EFI_STATUS
EFIAPI
TraceHubMmioTraceAddress (
  IN  UINT16                            Master,
  IN  UINT16                            Channel,
  OUT UINT32                            *TraceAddress
  )
{

  UINT32                  PwrmBase;

  PchPwrmBaseGet (&PwrmBase);

  ///
  /// Check HSWPGCR1 (PWRMBASE+0x5D0)[0], if it is 1, then skip the rest of initialization as it is power gated.
  ///
  if ((MmioRead32 (PwrmBase + R_PCH_PWRM_HSWPGCR1) & B_PCH_PWRM_DFX_SW_PG_CTRL) == B_PCH_PWRM_DFX_SW_PG_CTRL) {
    return EFI_DEVICE_ERROR;
  }

  if ((MmioRead32 (PCH_TRACE_HUB_SW_BASE_ADDRESS) == 0xFFFFFFFF)) {
    return EFI_DEVICE_ERROR;
  }

  if (Master >= V_PCH_TRACE_HUB_MTB_STHMSTR) {
    *TraceAddress = PCH_TRACE_HUB_SW_BASE_ADDRESS + 0x40 * (V_PCH_TRACE_HUB_MTB_CHLCNT * (Master - V_PCH_TRACE_HUB_MTB_STHMSTR)) + 0x40 * Channel;
  } else {
    return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}
