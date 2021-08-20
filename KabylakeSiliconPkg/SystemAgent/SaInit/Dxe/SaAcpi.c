/** @file
  This is the driver that initializes the Intel System Agent.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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
#include "SaInitDxe.h"
#include "SaInit.h"
#include <Private/SaConfigHob.h>      // AdvancedFeaturesContent
#include <Protocol/SaGlobalNvsArea.h>

///
/// Global Variables
///
GLOBAL_REMOVE_IF_UNREFERENCED SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL  mSaGlobalNvsAreaProtocol;
GLOBAL_REMOVE_IF_UNREFERENCED SA_POLICY_PROTOCOL                     *mSaPolicy;
extern SA_CONFIG_HOB                                                 *mSaConfigHob;    // AdvancedFeaturesContent

/**
  Initialize System Agent SSDT ACPI tables

  @retval EFI_SUCCESS    ACPI tables are initialized successfully
  @retval EFI_NOT_FOUND  ACPI tables not found
**/
EFI_STATUS
InitializeSaSsdtAcpiTables (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  EFI_FV_FILETYPE               FileType;
  UINT32                        FvStatus;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINTN                         Size;
  UINTN                         i;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVol;
  INTN                          Instance;
  EFI_ACPI_COMMON_HEADER        *CurrentTable;
  UINTN                         AcpiTableKey;
  UINT8                         *CurrPtr;
  UINT8                         *EndPtr;
  UINT32                        *Signature;
  EFI_ACPI_DESCRIPTION_HEADER   *SaAcpiTable;
  EFI_ACPI_TABLE_PROTOCOL       *AcpiTable;

  FwVol       = NULL;
  SaAcpiTable = NULL;

  ///
  /// Locate ACPI Table protocol
  ///
  DEBUG ((DEBUG_INFO, "Init SA SSDT table\n"));
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);
  if (Status != EFI_SUCCESS) {
    DEBUG ((DEBUG_WARN, "Fail to locate EfiAcpiTableProtocol.\n"));
    return EFI_NOT_FOUND;
  }

  ///
  /// Locate protocol.
  /// There is little chance we can't find an FV protocol
  ///
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);
  ///
  /// Looking for FV with ACPI storage file
  ///
  for (i = 0; i < NumberOfHandles; i++) {
    ///
    /// Get the protocol on this handle
    /// This should not fail because of LocateHandleBuffer
    ///
    Status = gBS->HandleProtocol (
                    HandleBuffer[i],
                    &gEfiFirmwareVolume2ProtocolGuid,
                    (VOID **) &FwVol
                    );
    ASSERT_EFI_ERROR (Status);

    ///
    /// See if it has the ACPI storage file
    ///
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                      FwVol,
                      &gSaSsdtAcpiTableStorageGuid,
                      NULL,
                      &Size,
                      &FileType,
                      &Attributes,
                      &FvStatus
                      );

    ///
    /// If we found it, then we are done
    ///
    if (Status == EFI_SUCCESS) {
      break;
    }
  }
  ///
  /// Free any allocated buffers
  ///
  FreePool (HandleBuffer);

  ///
  /// Sanity check that we found our data file
  ///
  ASSERT (FwVol != NULL);
  if (FwVol == NULL) {
    DEBUG ((DEBUG_INFO, "SA Global NVS table not found\n"));
    return EFI_NOT_FOUND;
  }
  ///
  /// Our exit status is determined by the success of the previous operations
  /// If the protocol was found, Instance already points to it.
  /// Read tables from the storage file.
  ///
  Instance      = 0;
  CurrentTable  = NULL;
  while (Status == EFI_SUCCESS) {
    Status = FwVol->ReadSection (
                      FwVol,
                      &gSaSsdtAcpiTableStorageGuid,
                      EFI_SECTION_RAW,
                      Instance,
                      (VOID **) &CurrentTable,
                      &Size,
                      &FvStatus
                      );

    if (!EFI_ERROR (Status)) {
      ///
      /// Check the table ID to modify the table
      ///
      if (((EFI_ACPI_DESCRIPTION_HEADER *) CurrentTable)->OemTableId == SIGNATURE_64 ('S', 'a', 'S', 's', 'd', 't', ' ', 0)) {
        SaAcpiTable = (EFI_ACPI_DESCRIPTION_HEADER *) CurrentTable;
        ///
        /// Locate the SSDT package
        ///
        CurrPtr = (UINT8 *) SaAcpiTable;
        EndPtr  = CurrPtr + SaAcpiTable->Length;

        for (; CurrPtr <= EndPtr; CurrPtr++) {
          Signature = (UINT32 *) (CurrPtr + 3);
          if (*Signature == SIGNATURE_32 ('S', 'A', 'N', 'V')) {
            ASSERT (*(UINT32 *) (CurrPtr + 3 + sizeof (*Signature) + 2) == 0xFFFF0000);
            ASSERT (*(UINT16 *) (CurrPtr + 3 + sizeof (*Signature) + 2 + sizeof (UINT32) + 1) == 0xAA55);
            ///
            /// SA Global NVS Area address
            ///
            *(UINT32 *) (CurrPtr + 3 + sizeof (*Signature) + 2) = (UINT32) (UINTN) mSaGlobalNvsAreaProtocol.Area;
            ///
            /// SA Global NVS Area size
            ///
            *(UINT16 *) (CurrPtr + 3 + sizeof (*Signature) + 2 + sizeof (UINT32) + 1) =
              sizeof (SYSTEM_AGENT_GLOBAL_NVS_AREA);

            AcpiTableKey = 0;
            Status = AcpiTable->InstallAcpiTable (
                                  AcpiTable,
                                  SaAcpiTable,
                                  SaAcpiTable->Length,
                                  &AcpiTableKey
                                  );
            ASSERT_EFI_ERROR (Status);
            return EFI_SUCCESS;
          }
        }
      }
      ///
      /// Increment the instance
      ///
      Instance++;
      CurrentTable = NULL;
    }
  }

  return Status;

}
#ifndef MINTREE_FLAG
/**
  Install PEG SSDT Table

  @retval EFI_SUCCESS - PEG SSDT Table load successful.
**/
EFI_STATUS
InstallPegSsdtAcpiTable (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  BOOLEAN                       LoadTable;
  UINTN                         NumberOfHandles;
  UINTN                         Index;
  INTN                          Instance;
  UINTN                         Size;
  UINT32                        FvStatus;
  UINTN                         TableHandle;
  EFI_FV_FILETYPE               FileType;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVol;
  EFI_ACPI_TABLE_PROTOCOL       *AcpiTable;
  EFI_ACPI_DESCRIPTION_HEADER   *TableHeader;
  EFI_ACPI_COMMON_HEADER        *Table;

  FwVol         = NULL;
  Table         = NULL;

  DEBUG ((DEBUG_INFO, "Loading PEG SSDT Table...\n"));

  ///
  /// Locate FV protocol.
  ///
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Look for FV with ACPI storage file
  ///
  for (Index = 0; Index < NumberOfHandles; Index++) {
    ///
    /// Get the protocol on this handle
    /// This should not fail because of LocateHandleBuffer
    ///
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiFirmwareVolume2ProtocolGuid,
                    (VOID **) &FwVol
                    );
    ASSERT_EFI_ERROR (Status);
    if (FwVol == NULL) {
      return EFI_NOT_FOUND;
    }
    ///
    /// See if it has the ACPI storage file
    ///
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                      FwVol,
                      &gPegSsdtAcpiTableStorageGuid,
                      NULL,
                      &Size,
                      &FileType,
                      &Attributes,
                      &FvStatus
                      );

    ///
    /// If we found it, then we are done
    ///
    if (!EFI_ERROR (Status)) {
      break;
    }
  }
  ///
  /// Our exit status is determined by the success of the previous operations
  /// If the protocol was found, Instance already points to it.
  ///
  ///
  /// Free any allocated buffers
  ///
  FreePool (HandleBuffer);

  ///
  /// Sanity check that we found our data file
  ///
  ASSERT (FwVol);

  ///
  /// Locate ACPI tables
  ///
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);

  ///
  /// Read tables from the storage file.
  ///
  if (FwVol == NULL) {
    ASSERT_EFI_ERROR (EFI_NOT_FOUND);
    return EFI_NOT_FOUND;
  }
  Instance = 0;

  while (Status == EFI_SUCCESS) {
    ///
    /// Read the ACPI tables
    ///
    Status = FwVol->ReadSection (
                      FwVol,
                      &gPegSsdtAcpiTableStorageGuid,
                      EFI_SECTION_RAW,
                      Instance,
                      (VOID **) &Table,
                      &Size,
                      &FvStatus
                      );
    if (!EFI_ERROR (Status)) {
      ///
      /// check and load SwitchableGraphics SSDT table
      ///
      LoadTable   = FALSE;
      TableHeader = (EFI_ACPI_DESCRIPTION_HEADER *) Table;

      if (((EFI_ACPI_DESCRIPTION_HEADER *) TableHeader)->OemTableId == SIGNATURE_64 (
                                                                          'P',
                                                                          'e',
                                                                          'g',
                                                                          'S',
                                                                          's',
                                                                          'd',
                                                                          't',
                                                                          0
                                                                          )
          ) {
        ///
        /// This is PEG SSDT
        ///
        DEBUG ((DEBUG_INFO, "Found out PEG SSDT Table.\n"));
        LoadTable = TRUE;
      }

      ///
      /// Add the table
      ///
      if (LoadTable) {
        TableHandle = 0;
        Status = AcpiTable->InstallAcpiTable (
                              AcpiTable,
                              TableHeader,
                              TableHeader->Length,
                              &TableHandle
                              );
      }
      ///
      /// Increment the instance
      ///
      Instance++;
      Table = NULL;
    }
  }

  return EFI_SUCCESS;
}
#endif //MINTREE_FLAG

/**
  This function gets registered as a callback to perform Dmar Igd

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
SaAcpiEndOfDxeCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS          Status;
#ifndef MINTREE_FLAG
  if (MmioRead16 (MmPciBase (SA_MC_BUS, 2, 0) + R_SA_IGD_VID) != 0xFFFF) {
    Status = PostPmInitEndOfDxe ();
    if (EFI_SUCCESS != Status) {
      DEBUG ((DEBUG_ERROR, "[SA] EndOfDxe GraphicsInit Error, Status = %r \n", Status));
      ASSERT_EFI_ERROR (Status);
    }
  }

  UpdateDmarEndOfDxe ();
#endif //MINTREE_FLAG
  if (MmioRead16 (MmPciBase (SA_MC_BUS, 2, 0) + R_SA_IGD_VID) != 0xFFFF) {
    Status = GetVBiosVbtEndOfDxe ();
    if (EFI_SUCCESS != Status) {
      DEBUG ((DEBUG_WARN, "[SA] EndOfDxe Op Region Error, Status = %r \n", Status));
    }

#ifndef MINTREE_FLAG
    Status = UpdateIgdOpRegionEndOfDxe ();
    if (EFI_SUCCESS != Status) {
      DEBUG ((DEBUG_WARN, "[SA] EndOfDxe Update Op Region Error, Status = %r \n", Status));
    }
#endif //MINTREE_FLAG
  }

  return;
}

/**
  SystemAgent Acpi Initialization.

  @param[in] ImageHandle             Handle for the image of this driver

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    No enough buffer to allocate
**/
EFI_STATUS
EFIAPI
SaAcpiInit (
  IN EFI_HANDLE         ImageHandle
  )
{
  EFI_STATUS                Status;
  EFI_EVENT                 EndOfDxeEvent;
#ifndef MINTREE_FLAG
  EFI_CPUID_REGISTER        CpuidRegs;
  CPU_FAMILY                CpuFamilyId;

  CpuFamilyId = GetCpuFamily();
  AsmCpuid (1, &CpuidRegs.RegEax, 0, 0, 0);
#endif //MINTREE
  ///
  /// Get the platform setup policy.
  ///
  Status = gBS->LocateProtocol (&gSaPolicyProtocolGuid, NULL, (VOID **) &mSaPolicy);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Install System Agent Global NVS protocol
  ///
  DEBUG ((DEBUG_INFO, "Install SA GNVS protocol\n"));
  Status = (gBS->AllocatePool) (EfiACPIMemoryNVS, sizeof (SYSTEM_AGENT_GLOBAL_NVS_AREA), (VOID **) &mSaGlobalNvsAreaProtocol.Area);
  ASSERT_EFI_ERROR (Status);
  ZeroMem ((VOID *) mSaGlobalNvsAreaProtocol.Area, sizeof (SYSTEM_AGENT_GLOBAL_NVS_AREA));
  mSaGlobalNvsAreaProtocol.Area->XPcieCfgBaseAddress  = (UINT32) (MmPciBase (0, 0, 0));
#ifndef MINTREE_FLAG
  mSaGlobalNvsAreaProtocol.Area->CpuIdInfo            = CpuidRegs.RegEax;
  if (mSaConfigHob != NULL) {
    mSaGlobalNvsAreaProtocol.Area->ImguAcpiMode = mSaConfigHob->ImguAcpiMode;
  }
#endif //MINTREE_FLAG
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gSaGlobalNvsAreaProtocolGuid,
                  &mSaGlobalNvsAreaProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

#ifndef MINTREE_FLAG
  ///
  /// PciExpress Dxe Initialization
  ///
  DEBUG ((DEBUG_INFO, "Initializing PciExpress (Dxe)\n"));
  PciExpressInit (mSaPolicy);
#endif //MINTREE_FLAG

  ///
  /// GtPostInit Initialization
  ///
  DEBUG ((DEBUG_INFO, "Initializing GT ACPI tables\n"));
  GraphicsInit (ImageHandle, mSaPolicy);

#ifndef MINTREE_FLAG
  ///
  /// Vtd Initialization
  ///
  DEBUG ((DEBUG_INFO, "Initializing VT-d ACPI tables\n"));
  VtdInit (mSaPolicy);
#endif //MINTREE_FLAG
  ///
  /// IgdOpRegion Install Initialization
  ///
  DEBUG ((DEBUG_INFO, "Initializing IGD OpRegion\n"));
  IgdOpRegionInit ();

  ///
  /// Register an end of DXE event for SA ACPI to do tasks before invoking any UEFI drivers,
  /// applications, or connecting consoles,...
  ///
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  SaAcpiEndOfDxeCallback,
                  NULL,
                  &gEfiEndOfDxeEventGroupGuid,
                  &EndOfDxeEvent
                  );

  ///
  /// Install System Agent Global NVS ACPI table
  ///
  Status = InitializeSaSsdtAcpiTables ();

#ifndef MINTREE_FLAG
  ///
  /// Install PEG SSDT table only if PEG port is present
  ///
  if (IsPchLinkDmi(CpuFamilyId)) {
    if (MmioRead16(MmPciBase(SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, SA_PEG10_FUN_NUM) + R_SA_PEG_DID_OFFSET) != 0xFFFF) {
      Status = InstallPegSsdtAcpiTable();
    }
  }
#endif //MINTREE_FLAG

#ifndef MINTREE_FLAG
#ifdef SG_SUPPORT
  DEBUG ((DEBUG_INFO, "Initializing Switchable Graphics (Dxe)\n"));
  SwitchableGraphicsInit ();
#endif //SG_SUPPORT
#endif //MINTREE_FLAG

  return EFI_SUCCESS;
}

