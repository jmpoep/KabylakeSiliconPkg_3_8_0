/** @file
  Initializes the PCH HD Audio ACPI Tables.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#include <PchInit.h>
#include <Guid/Acpi.h>
#include <Library/PcdLib.h>
#include <Private/Library/PchHdaLib.h>

PCH_HDA_NHLT_ENDPOINTS mPchHdaNhltEndpoints[HdaEndpointMax] =
{
  {HdaDmicX1,     B_HDA_DMIC_1CH_48KHZ_16BIT_FORMAT,                                              FALSE},
  {HdaDmicX2,     (B_HDA_DMIC_2CH_48KHZ_16BIT_FORMAT | B_HDA_DMIC_2CH_48KHZ_32BIT_FORMAT),        FALSE},
  {HdaDmicX4,     (B_HDA_DMIC_4CH_48KHZ_16BIT_FORMAT | B_HDA_DMIC_4CH_48KHZ_32BIT_FORMAT),        FALSE},
  {HdaBtRender,   (B_HDA_BT_NARROWBAND_FORMAT | B_HDA_BT_WIDEBAND_FORMAT | B_HDA_BT_A2DP_FORMAT), FALSE},
  {HdaBtCapture,  (B_HDA_BT_NARROWBAND_FORMAT | B_HDA_BT_WIDEBAND_FORMAT),                        FALSE},
  {HdaI2sRender1, (B_HDA_I2S_RTK298_RENDER_4CH_48KHZ_24BIT_FORMAT),                               FALSE},
  {HdaI2sRender2, (B_HDA_I2S_RTK298_RENDER_4CH_48KHZ_24BIT_FORMAT),                               FALSE},
  {HdaI2sCapture, (B_HDA_I2S_RTK298_CAPTURE_4CH_48KHZ_24BIT_FORMAT),                              FALSE}
};

/**
  Retrieves address of NHLT table from XSDT/RSDT.

  @retval NHLT_ACPI_TABLE*  Pointer to NHLT table if found
  @retval NULL              NHLT could not be found
**/
NHLT_ACPI_TABLE *
LocateNhltAcpiTable (
  VOID
  )
{
  EFI_ACPI_3_0_ROOT_SYSTEM_DESCRIPTION_POINTER  *Rsdp;
  EFI_ACPI_DESCRIPTION_HEADER                   *Xsdt;
  NHLT_ACPI_TABLE                               *Nhlt;
  UINTN                                         Index;
  UINT64                                        Data64;
  EFI_STATUS                                    Status;
  Rsdp  = NULL;
  Xsdt  = NULL;
  Nhlt  = NULL;

  ///
  /// Find the AcpiSupport protocol returns RSDP (or RSD PTR) address.
  ///
  DEBUG ((DEBUG_INFO, "LocateNhltAcpiTable() Start\n"));

  Status = EfiGetSystemConfigurationTable (&gEfiAcpiTableGuid, (VOID *) &Rsdp);
  if (EFI_ERROR (Status) || (Rsdp == NULL)) {
    DEBUG ((DEBUG_ERROR, "EFI_ERROR or Rsdp == NULL\n"));
    return NULL;
  }

  Xsdt = (EFI_ACPI_DESCRIPTION_HEADER *) (UINTN) Rsdp->XsdtAddress;
  if (Xsdt == NULL || Xsdt->Signature != EFI_ACPI_5_0_EXTENDED_SYSTEM_DESCRIPTION_TABLE_SIGNATURE) {
    // If XSDT has not been found, check RSDT
    Xsdt = (EFI_ACPI_DESCRIPTION_HEADER *) (UINTN) Rsdp->RsdtAddress;
    if (Xsdt == NULL || Xsdt->Signature != EFI_ACPI_5_0_ROOT_SYSTEM_DESCRIPTION_TABLE_SIGNATURE) {
      DEBUG ((DEBUG_ERROR, "XSDT/RSDT == NULL or wrong signature\n"));
      return NULL;
    }
  }

  for (Index = sizeof (EFI_ACPI_DESCRIPTION_HEADER); Index < Xsdt->Length; Index = Index + sizeof (UINT64)) {
    Data64  = *(UINT64 *) ((UINT8 *) Xsdt + Index);
    Nhlt    = (NHLT_ACPI_TABLE *) (UINTN) Data64;
    if (Nhlt != NULL && Nhlt->Header.Signature == NHLT_ACPI_TABLE_SIGNATURE) {
      break;
    }
    Nhlt = NULL;
  }

  if (Nhlt == NULL || Nhlt->Header.Signature != NHLT_ACPI_TABLE_SIGNATURE) {
    DEBUG ((DEBUG_ERROR, "Nhlt == NULL or wrong signature\n"));
    return NULL;
  }

  DEBUG ((DEBUG_INFO, "Found NhltTable, Address = 0x%016x\n", Nhlt));

  return Nhlt;
}

/**
  Constructs and installs NHLT table.

  @retval EFI_SUCCESS       ACPI Table installed successfully
  @retval EFI_UNSUPPORTED   ACPI Table protocol not found
**/
EFI_STATUS
PublishNhltAcpiTable (
  VOID
  )
{
  UINTN                                     AcpiTableKey;
  EFI_ACPI_TABLE_PROTOCOL                   *AcpiTable;
  NHLT_ACPI_TABLE                           *NhltTable;
  UINT32                                    TableLength;
  EFI_STATUS                                Status;

  AcpiTable = NULL;
  NhltTable = NULL;
  AcpiTableKey = 0;

  DEBUG ((DEBUG_INFO, "PublishNhltAcpiTable() Start\n"));

  //
  // Locate ACPI support protocol
  //
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);
  if ( EFI_ERROR (Status) || AcpiTable == NULL) {
    return EFI_UNSUPPORTED;
  }

  NhltConstructor (mPchHdaNhltEndpoints, &NhltTable, &TableLength);
  NhltAcpiHeaderConstructor (NhltTable, TableLength);

  Status = AcpiTable->InstallAcpiTable (AcpiTable, NhltTable, NhltTable->Header.Length, &AcpiTableKey);

  DEBUG ((DEBUG_INFO, "PublishNhltAcpiTable() End\n"));
  return Status;
}

/**
  Sets NVS ACPI variables for _DSM accordingly to policy.

  @param[in]                NhltAcpiTableAddress
  @param[in]                NhltAcpiTableLength
  @param[in]                DspFeatureMask
**/
VOID
UpdateHdaAcpiData (
  IN      UINT64   NhltAcpiTableAddress,
  IN      UINT32   NhltAcpiTableLength,
  IN      UINT32   DspFeatureMask
  )
{
  DEBUG ((DEBUG_INFO, "UpdateHdaAcpiData():\n NHLT Address = 0x%016x, Length = 0x%08x\n", NhltAcpiTableAddress, NhltAcpiTableLength));
  DEBUG ((DEBUG_INFO, " FeatureMask = 0x%08x\n", DspFeatureMask));

  mPchNvsAreaProtocol.Area->NHLA = NhltAcpiTableAddress;
  mPchNvsAreaProtocol.Area->NHLL = NhltAcpiTableLength;
  mPchNvsAreaProtocol.Area->ADFM = DspFeatureMask;
}

/**
  Initialize and publish NHLT (Non-HDA Link Table), update NVS variables.

  @param[in]             *HdaConfig

  @retval EFI_SUCCESS    The function completed successfully
**/
EFI_STATUS
SetHdaAcpiTable (
  IN CONST HDAUDIO_HOB     *HdaConfig
  )
{
  NHLT_ACPI_TABLE     *NhltTable;
  EFI_STATUS          Status;
  NhltTable = NULL;


  switch (HdaConfig->DspEndpointDmic) {
    case PchHdaDmic1chArray:
      mPchHdaNhltEndpoints[HdaDmicX1].Enable   = TRUE;
      break;
    case PchHdaDmic2chArray:
      mPchHdaNhltEndpoints[HdaDmicX2].Enable   = TRUE;
      break;
    case PchHdaDmic4chArray:
      mPchHdaNhltEndpoints[HdaDmicX4].Enable   = TRUE;
      break;
    case PchHdaDmicDisabled:
    default:
      mPchHdaNhltEndpoints[HdaDmicX2].Enable   = FALSE;
      mPchHdaNhltEndpoints[HdaDmicX4].Enable   = FALSE;
  }

  if (HdaConfig->DspEndpointBluetooth) {
    mPchHdaNhltEndpoints[HdaBtRender].Enable   = TRUE;
    mPchHdaNhltEndpoints[HdaBtCapture].Enable  = TRUE;
  }

  if (HdaConfig->DspEndpointI2s) {
    mPchHdaNhltEndpoints[HdaI2sRender1].Enable = TRUE;
    mPchHdaNhltEndpoints[HdaI2sRender2].Enable = TRUE;
    mPchHdaNhltEndpoints[HdaI2sCapture].Enable = TRUE;
  }

  Status    = PublishNhltAcpiTable ();
  NhltTable = LocateNhltAcpiTable ();
  if (NhltTable == NULL) {
    return EFI_LOAD_ERROR;
  }

  UpdateHdaAcpiData ((UINT64) (UINTN) NhltTable, (UINT32) (NhltTable->Header.Length), HdaConfig->DspFeatureMask);

  DEBUG_CODE ( NhltAcpiTableDump (NhltTable); );
  return Status;
}

/**
  Initialize Intel High Definition Audio ACPI Tables

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_LOAD_ERROR          ACPI table cannot be installed
  @retval EFI_UNSUPPORTED         ACPI table not set because DSP is disabled
**/
EFI_STATUS
PchHdAudioAcpiInit (
  VOID
  )
{
  EFI_STATUS                    Status;
  CONST HDAUDIO_HOB            *HdaConfig;
  UINTN                         HdaPciBase;

  DEBUG ((DEBUG_INFO, "PchHdAudioAcpiInit() Start\n"));

  HdaConfig = &mPchConfigHob->HdAudio;

  HdaPciBase = MmPciBase (
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_HDA,
                 PCI_FUNCTION_NUMBER_PCH_HDA
                 );

  if ((MmioRead16 (HdaPciBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) || (HdaConfig->DspEnable == FALSE)) {
    // Do not set ACPI tables if HDAudio is Function disabled or DSP is disabled
    DEBUG ((DEBUG_INFO, "AudioDSP: Non-HDAudio ACPI Table (NHLT) not set!\n"));
    return EFI_UNSUPPORTED;
  }

  Status = SetHdaAcpiTable (HdaConfig);

  DEBUG ((DEBUG_INFO, "PchHdAudioAcpiInit() End - Status = %r\n", Status));
  return Status;
}

