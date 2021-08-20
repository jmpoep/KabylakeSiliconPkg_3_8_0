/** @file
  PCH P2sb access lib.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/MmPciLib.h>
#include <PchAccess.h>

/**
  Get P2SB pci configuration register. (This is internal function)
  It returns register at Offset of P2SB controller and size in 1byte/2bytes/4bytes.
  The Offset should not exceed 255 and must be aligned with size.
  This function will be unavailable after P2SB is hidden by PSF.

  @param[in]  Offset                    Register offset of P2SB controller.
  @param[in]  Size                      Size for read. Must be 1 or 2 or 4.
  @param[out] OutData                   Buffer of Output Data. Must be the same size as Size parameter.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_INVALID_PARAMETER         Invalid offset passed.
**/
STATIC
EFI_STATUS
PchP2sbCfgGet (
  IN  UINTN                             Offset,
  IN  UINTN                             Size,
  OUT UINT32                            *OutData
  )
{
  UINTN                                 P2sbBase;
  BOOLEAN                               DevicePresent;

  if ((Offset > 255) ||
      ((Offset & (Size - 1)) != 0)) {
    DEBUG ((DEBUG_ERROR, "PchP2sbCfgGet error. Invalid Offset: %x Size: %x", Offset, Size));
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  P2sbBase      = MmPciBase (
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_P2SB,
                    PCI_FUNCTION_NUMBER_PCH_P2SB
                    );
  DevicePresent = (MmioRead16 (P2sbBase + PCI_VENDOR_ID_OFFSET) != 0xFFFF);
  if (!DevicePresent) {
    MmioWrite8 (P2sbBase + R_PCH_P2SB_E0 + 1, 0);
  }
  ASSERT (MmioRead16 (P2sbBase + PCI_VENDOR_ID_OFFSET) != 0xFFFF);

  switch (Size) {
    case 4:
      *(UINT32*) OutData = MmioRead32 (P2sbBase + Offset);
      break;
    case 2:
      *(UINT16*) OutData = MmioRead16 (P2sbBase + Offset);
      break;
    case 1:
      *(UINT8*) OutData = MmioRead8  (P2sbBase + Offset);
      break;
    default:
      break;
  }

  if (!DevicePresent) {
    MmioWrite8 (P2sbBase + R_PCH_P2SB_E0 + 1, BIT0);
  }
  return EFI_SUCCESS;
}

/**
  Get P2SB pci configuration register.
  It returns register at Offset of P2SB controller and size in 4bytes.
  The Offset should not exceed 255 and must be aligned with size.
  This function will be unavailable after P2SB is hidden by PSF.

  @param[in]  Offset                    Register offset of P2SB controller.
  @param[out] OutData                   Buffer of Output Data. Must be the same size as Size parameter.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_INVALID_PARAMETER         Invalid offset passed.
**/
EFI_STATUS
PchP2sbCfgGet32 (
  IN  UINTN                             Offset,
  OUT UINT32                            *OutData
  )
{
  return PchP2sbCfgGet (Offset, 4, (UINT32*) OutData);
}

/**
  Get P2SB pci configuration register.
  It returns register at Offset of P2SB controller and size in 2bytes.
  The Offset should not exceed 255 and must be aligned with size.
  This function will be unavailable after P2SB is hidden by PSF.

  @param[in]  Offset                    Register offset of P2SB controller.
  @param[out] OutData                   Buffer of Output Data. Must be the same size as Size parameter.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_INVALID_PARAMETER         Invalid offset passed.
**/
EFI_STATUS
PchP2sbCfgGet16 (
  IN  UINTN                             Offset,
  OUT UINT16                            *OutData
  )
{
  return PchP2sbCfgGet (Offset, 2, (UINT32*) OutData);
}

/**
  Get P2SB pci configuration register.
  It returns register at Offset of P2SB controller and size in 1byte.
  The Offset should not exceed 255 and must be aligned with size.
  This function will be unavailable after P2SB is hidden by PSF.

  @param[in]  Offset                    Register offset of P2SB controller.
  @param[out] OutData                   Buffer of Output Data. Must be the same size as Size parameter.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_INVALID_PARAMETER         Invalid offset passed.
**/
EFI_STATUS
PchP2sbCfgGet8 (
  IN  UINTN                             Offset,
  OUT UINT8                             *OutData
  )
{
  return PchP2sbCfgGet (Offset, 1, (UINT32*) OutData);
}

/**
  Set P2SB pci configuration register. (This is internal function)
  It programs register at Offset of P2SB controller and size in 1byte/2bytes/4bytes.
  The Offset should not exceed 255 and must be aligned with size.
  This function will be unavailable after P2SB is hidden by PSF.

  @param[in]  Offset                    Register offset of P2SB controller.
  @param[in]  Size                      Size for read. Must be 1 or 2 or 4.
  @param[in]  AndData                   AND Data. Must be the same size as Size parameter.
  @param[in]  OrData                    OR Data. Must be the same size as Size parameter.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_INVALID_PARAMETER         Invalid offset passed.
**/
STATIC
EFI_STATUS
PchP2sbCfgSet (
  IN  UINTN                             Offset,
  IN  UINTN                             Size,
  IN  UINT32                            AndData,
  IN  UINT32                            OrData
  )
{
  UINTN                                 P2sbBase;
  BOOLEAN                               DevicePresent;
  UINT32                                Data32;

  if ((Offset > 255) ||
      ((Offset & (Size - 1)) != 0)) {
    DEBUG ((DEBUG_ERROR, "PchP2sbCfgSet error. Invalid Offset: %x Size: %x", Offset, Size));
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  Data32 = 0;

  P2sbBase      = MmPciBase (
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_P2SB,
                    PCI_FUNCTION_NUMBER_PCH_P2SB
                    );
  DevicePresent = (MmioRead16 (P2sbBase + PCI_VENDOR_ID_OFFSET) != 0xFFFF);
  if (!DevicePresent) {
    MmioWrite8 (P2sbBase + R_PCH_P2SB_E0 + 1, 0);
  }
  ASSERT (MmioRead16 (P2sbBase + PCI_VENDOR_ID_OFFSET) != 0xFFFF);

  switch (Size) {
    case 4:
      Data32 = MmioRead32 (P2sbBase + Offset);
      Data32 &= AndData;
      Data32 |= OrData;
      MmioWrite32 (P2sbBase + Offset, (UINT32) Data32);
      break;
    case 2:
      Data32 = MmioRead16 (P2sbBase + Offset);
      Data32 &= AndData;
      Data32 |= OrData;
      MmioWrite16 (P2sbBase + Offset, (UINT16) Data32);
      break;
    case 1:
      Data32 = MmioRead8 (P2sbBase + Offset);
      Data32 &= AndData;
      Data32 |= OrData;
      MmioWrite8  (P2sbBase + Offset, (UINT8)  Data32);
      break;
    default:
      break;
  }

  if (!DevicePresent) {
    MmioWrite8 (P2sbBase + R_PCH_P2SB_E0 + 1, BIT0);
  }
  return EFI_SUCCESS;
}

/**
  Set P2SB pci configuration register.
  It programs register at Offset of P2SB controller and size in 4bytes.
  The Offset should not exceed 255 and must be aligned with size.
  This function will be unavailable after P2SB is hidden by PSF.

  @param[in]  Offset                    Register offset of P2SB controller.
  @param[in]  AndData                   AND Data. Must be the same size as Size parameter.
  @param[in]  OrData                    OR Data. Must be the same size as Size parameter.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_INVALID_PARAMETER         Invalid offset passed.
**/
EFI_STATUS
PchP2sbCfgSet32 (
  IN  UINTN                             Offset,
  IN  UINT32                            AndData,
  IN  UINT32                            OrData
  )
{
  return PchP2sbCfgSet (Offset, 4, AndData, OrData);
}

/**
  Set P2SB pci configuration register.
  It programs register at Offset of P2SB controller and size in 2bytes.
  The Offset should not exceed 255 and must be aligned with size.
  This function will be unavailable after P2SB is hidden by PSF.

  @param[in]  Offset                    Register offset of P2SB controller.
  @param[in]  AndData                   AND Data. Must be the same size as Size parameter.
  @param[in]  OrData                    OR Data. Must be the same size as Size parameter.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_INVALID_PARAMETER         Invalid offset passed.
**/
EFI_STATUS
PchP2sbCfgSet16 (
  IN  UINTN                             Offset,
  IN  UINT16                            AndData,
  IN  UINT16                            OrData
  )
{
  return PchP2sbCfgSet (Offset, 2, AndData, OrData);
}

/**
  Set P2SB pci configuration register.
  It programs register at Offset of P2SB controller and size in 1bytes.
  The Offset should not exceed 255 and must be aligned with size.
  This function will be unavailable after P2SB is hidden by PSF.

  @param[in]  Offset                    Register offset of P2SB controller.
  @param[in]  AndData                   AND Data. Must be the same size as Size parameter.
  @param[in]  OrData                    OR Data. Must be the same size as Size parameter.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_INVALID_PARAMETER         Invalid offset passed.
**/
EFI_STATUS
PchP2sbCfgSet8 (
  IN  UINTN                             Offset,
  IN  UINT8                             AndData,
  IN  UINT8                             OrData
  )
{
  return PchP2sbCfgSet (Offset, 1, AndData, OrData);
}

/**
  Hide P2SB device.

  @param[in]  P2sbBase                  Pci base address of P2SB controller.

  @retval EFI_SUCCESS                   Always return success.
**/
EFI_STATUS
PchHideP2sb (
  IN  UINTN                             P2sbBase
  )
{
  MmioWrite8 (P2sbBase + R_PCH_P2SB_E0 + 1, BIT0);
  return EFI_SUCCESS;
}

/**
  Reveal P2SB device.
  Also return the original P2SB status which is for Hidding P2SB or not after.
  If OrgStatus is not NULL, then TRUE means P2SB is unhidden,
  and FALSE means P2SB is hidden originally.

  @param[in]  P2sbBase                  Pci base address of P2SB controller.
  @param[out] OrgStatus                 Original P2SB hidding/unhidden status

  @retval EFI_SUCCESS                   Always return success.
**/
EFI_STATUS
PchRevealP2sb (
  IN  UINTN                             P2sbBase,
  OUT BOOLEAN                           *OrgStatus
  )
{
  BOOLEAN                               DevicePresent;

  DevicePresent = (MmioRead16 (P2sbBase + PCI_VENDOR_ID_OFFSET) != 0xFFFF);
  if (OrgStatus != NULL) {
    *OrgStatus = DevicePresent;
  }
  if (!DevicePresent) {
    MmioWrite8 (P2sbBase + R_PCH_P2SB_E0 + 1, 0);
  }
  return EFI_SUCCESS;
}
