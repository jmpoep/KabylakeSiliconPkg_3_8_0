/** @file
  MP Support functions

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2007 - 2016 Intel Corporation.

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

#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <MpService.h>

GLOBAL_REMOVE_IF_UNREFERENCED ACPI_CPU_DATA  *mAcpiCpuData;
GLOBAL_REMOVE_IF_UNREFERENCED MP_SYSTEM_DATA *mMPSystemData;

///
/// Function declarations
///
/**
  Initializes MP support in the system.

  @retval EFI_SUCCESS          - Multiple processors are initialized successfully.
  @retval EFI_OUT_OF_RESOURCES - No enough resoruces (such as out of memory).
**/
EFI_STATUS
InitializeMpSupport (
  VOID
  )
{
  EFI_STATUS           Status;
  MP_CPU_RESERVED_DATA *MpCpuReservedData;

  MpCpuReservedData = NULL;

  ///
  /// Allocate memory for MP CPU related data below 4G
  ///
  Status = AllocateReservedMemoryBelow4G (
             sizeof (MP_CPU_RESERVED_DATA),
             (VOID **) &MpCpuReservedData
             );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (MpCpuReservedData != NULL) {
    ZeroMem (MpCpuReservedData, sizeof (MP_CPU_RESERVED_DATA));
  } else {
    ASSERT (MpCpuReservedData != NULL);
    return EFI_OUT_OF_RESOURCES;
  }

  mMPSystemData = &(MpCpuReservedData->MPSystemData);
  mAcpiCpuData  = &(MpCpuReservedData->AcpiCpuData);

  ///
  /// Initialize ACPI_CPU_DATA data
  ///
  mAcpiCpuData->CpuPrivateData          = (EFI_PHYSICAL_ADDRESS) & (mMPSystemData->CpuPrivateData);
  mAcpiCpuData->S3BootPath              = FALSE;
  mAcpiCpuData->GdtrProfile             = (EFI_PHYSICAL_ADDRESS) & (MpCpuReservedData->GdtrProfile);
  mAcpiCpuData->IdtrProfile             = (EFI_PHYSICAL_ADDRESS) & (MpCpuReservedData->IdtrProfile);

  ///
  /// Initialize MP services
  ///
  InitializeMpServices ();

  return EFI_SUCCESS;
}
