/** @file
  This code provides a initialization of intel VT-d (Virtualization Technology for Directed I/O).

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#include "VTd.h"
#include <CpuRegs.h>
#include <Private/SaConfigHob.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PchP2sbLib.h>
#include <Library/PchInfoLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED SA_POLICY_PROTOCOL              *mSaPolicy;
GLOBAL_REMOVE_IF_UNREFERENCED SA_CONFIG_HOB                   *SaConfigHob;

/**
  For device that specified by Device Num and Function Num,
  mDevEnMap is used to check device presence.
  0x80 means use Device ID to detemine presence

  The structure is used to check if device scope is valid when update DMAR table
**/
UINT16  mDevEnMap[][2] = {{0x0200, 0x80}, {0x1400, 0x80}, {0x1401, 0x80}};

BOOLEAN mInterruptRemappingSupport;

/**
  Get the corresponding device Enable/Disable bit according DevNum and FunNum

  @param[in] DevNum  - Device Number
  @param[in] FunNum  - Function Number

  @retval If the device is found, return disable/Enable bit in FD/Deven reigster
  @retval If not found return 0xFF
**/
UINT16
GetFunDisableBit (
  UINT8 DevNum,
  UINT8 FunNum
  )
{
  UINTN Index;

  for (Index = 0; Index < sizeof (mDevEnMap) / 4; Index++) {
    if (mDevEnMap[Index][0] == ((DevNum << 0x08) | FunNum)) {
      return mDevEnMap[Index][1];
    }
  }

  return 0xFF;
}

/**
  Update the DRHD structure

  @param[in, out] DrhdEnginePtr       - A pointer to DRHD structure
**/
VOID
UpdateDrhd (
  IN OUT VOID *DrhdEnginePtr
  )
{
  UINT16                        Length;
  UINT16                        DisableBit;
  UINTN                         DeviceScopeNum;
  BOOLEAN                       NeedRemove;
  EFI_ACPI_DRHD_ENGINE1_STRUCT  *DrhdEngine;

  //
  // Convert DrhdEnginePtr to EFI_ACPI_DRHD_ENGINE1_STRUCT Pointer
  //
  DrhdEngine      = (EFI_ACPI_DRHD_ENGINE1_STRUCT *) DrhdEnginePtr;
  Length          = DrhdEngine->Length;
  DeviceScopeNum  = (DrhdEngine->Length - EFI_ACPI_DRHD_ENGINE_HEADER_LENGTH) / sizeof (EFI_ACPI_DEV_SCOPE_STRUCTURE);
  DisableBit = GetFunDisableBit (
                 DrhdEngine->DeviceScope[0].PciPath[0],
                 DrhdEngine->DeviceScope[0].PciPath[1]
                 );
  NeedRemove = FALSE;
  if ((DisableBit == 0xFF) ||
      (DrhdEngine->RegisterBaseAddress == 0) ||
      ((DisableBit == 0x80) &&
       (MmioRead32 (MmPciBase (0, DrhdEngine->DeviceScope[0].PciPath[0], DrhdEngine->DeviceScope[0].PciPath[1]) + 0x00) == 0xFFFFFFFF))
      ) {
    NeedRemove = TRUE;
  }
  if (NeedRemove) {
    Length -= sizeof (EFI_ACPI_DEV_SCOPE_STRUCTURE);
  }
  ///
  /// If no devicescope is left, we set the structure length as 0x00
  ///
  if ((Length > EFI_ACPI_DRHD_ENGINE_HEADER_LENGTH) || (DrhdEngine->Flags == 0x01)) {
    DrhdEngine->Length = Length;
  } else {
    DrhdEngine->Length = 0;
  }
}

/**
  Get IOAPIC ID from LPC

  @retval APIC ID
**/
UINT8
GetIoApicId (
  VOID
  )
{
  UINT8 volatile  *IoapicIndex;
  UINT32 volatile *IoapicData;
  UINT32          IoApicIndexAddr;
  UINT32          IoApicDataAddr;
  UINT32          Data32;

  ///
  /// Get IOAPIC base
  ///
  PchIoApicBaseGet (&IoApicIndexAddr, &IoApicDataAddr);
  IoapicIndex = (UINT8 *) (UINTN) IoApicIndexAddr;
  IoapicData  = (UINT32 *) (UINTN) IoApicDataAddr;

  ///
  /// Get APIC ID from Identification Register (Index 0)
  ///
  *IoapicIndex  = 0;
  Data32        = (*IoapicData & 0x0F000000) >> 24;

  return (UINT8) Data32;
}

/**
  Update the second DRHD structure

  @param[in, out] DrhdEnginePtr       - A pointer to DRHD structure
**/
VOID
UpdateDrhd2 (
  IN OUT VOID *DrhdEnginePtr
  )
{
  UINT16                        Length;
  UINTN                         DeviceScopeNum;
  UINTN                         ValidDeviceScopeNum;
  UINT16                        Data16;
  UINT16                        Index;
  UINT8                         Bus;
  UINT8                         Path[2];
  BOOLEAN                       NeedRemove;
  EFI_ACPI_DRHD_ENGINE2_STRUCT  *DrhdEngine;

  ///
  /// Convert DrhdEnginePtr to EFI_ACPI_DRHD_ENGINE2_STRUCT Pointer
  ///
  DrhdEngine      = (EFI_ACPI_DRHD_ENGINE2_STRUCT *) DrhdEnginePtr;

  Length          = DrhdEngine->Length;
  DeviceScopeNum  = (DrhdEngine->Length - EFI_ACPI_DRHD_ENGINE_HEADER_LENGTH) / sizeof (EFI_ACPI_DEV_SCOPE_STRUCTURE);
  Data16          = 0;
  Bus             = 0;
  ValidDeviceScopeNum = 0;
  Path[0]         = 0;
  Path[1]         = 0;

  for (Index = 0; Index < DeviceScopeNum; Index++) {
    NeedRemove = FALSE;
    /**
      For HPET and APIC, update device scope if Interrupt remapping is supported. remove device scope
      if interrupt remapping is not supported.
      - Index = 0 - IOAPIC
      - Index = 1 - HPET
    **/
    if (mInterruptRemappingSupport) {
      if (Index == 0) {
        ///
        /// Update source id for IoApic's device scope entry
        ///
        PchP2sbCfgGet16 (R_PCH_P2SB_IBDF, &Data16);
        Bus     = (UINT8) (Data16 >> 8);
        if (Bus != 0x00) {
          Path[0] = (UINT8) ((Data16 & 0xff) >> 3);
          Path[1] = (UINT8) (Data16 & 0x7);
        } else {
          DEBUG ((DEBUG_WARN, "P2SB APIC Bus, Device and Function numbers were not programmed yet or invalid, use hardcoding values instead!\n"));
          Bus     = 0xF0;
          Path[0] = 0x1F;
          Path[1] = 0x0;
        }
        DrhdEngine->DeviceScope[Index].StartBusNumber = Bus;
        DrhdEngine->DeviceScope[Index].PciPath[0] = Path[0];
        DrhdEngine->DeviceScope[Index].PciPath[1] = Path[1];
        //
        // Update APIC ID
        //
        DrhdEngine->DeviceScope[Index].EnumId = GetIoApicId ();
      }
      if (Index == 1) {
        ///
        /// Update source id for HPET's device scope entry
        ///
        PchP2sbCfgGet16 (R_PCH_P2SB_HBDF, &Data16);
        Bus     = (UINT8) (Data16 >> 8);
        Path[0] = (UINT8) ((Data16 & 0xFF) >> 3);
        Path[1] = (UINT8) (Data16 & 0x7);
        DrhdEngine->DeviceScope[Index].StartBusNumber = Bus;
        DrhdEngine->DeviceScope[Index].PciPath[0] = Path[0];
        DrhdEngine->DeviceScope[Index].PciPath[1] = Path[1];
      }
    } else {
      if ((Index == 0) || (Index == 1)) {
        NeedRemove = TRUE;
      }
    }

    CopyMem (
      &DrhdEngine->DeviceScope[ValidDeviceScopeNum],
      &DrhdEngine->DeviceScope[Index],
      sizeof (EFI_ACPI_DEV_SCOPE_STRUCTURE)
      );
    if (NeedRemove) {
      Length -= sizeof (EFI_ACPI_DEV_SCOPE_STRUCTURE);
    } else {
      ValidDeviceScopeNum++;
    }
  }
  ///
  /// If no devicescope is left, we set the structure length as 0x00
  ///
  if ((Length > EFI_ACPI_DRHD_ENGINE_HEADER_LENGTH) || (DrhdEngine->Flags == 0x01)) {
    DrhdEngine->Length = Length;
  } else {
    DrhdEngine->Length = 0;
  }
}

/**
  Update the RMRR structure

  @param[in, out] RmrrPtr             - A pointer to RMRR structure
**/
VOID
UpdateRmrr (
  IN OUT VOID *RmrrPtr
  )
{
  UINT16                  Length;
  UINT16                  DisableBit;
  UINTN                   DeviceScopeNum;
  UINTN                   ValidDeviceScopeNum;
  UINTN                   Index;
  BOOLEAN                 NeedRemove;
  EFI_ACPI_RMRR_USB_STRUC *Rmrr;

  ///
  /// To make sure all devicescope can be checked,
  /// we convert the RmrrPtr to EFI_ACPI_RMRR_USB_STRUC pointer
  ///
  Rmrr                = (EFI_ACPI_RMRR_USB_STRUC *) RmrrPtr;

  Length              = Rmrr->Length;
  ValidDeviceScopeNum = 0;
  DeviceScopeNum      = (Rmrr->Length - EFI_ACPI_RMRR_HEADER_LENGTH) / sizeof (EFI_ACPI_DEV_SCOPE_STRUCTURE);
  for (Index = 0; Index < DeviceScopeNum; Index++) {
    DisableBit = GetFunDisableBit (
                   Rmrr->DeviceScope[Index].PciPath[0],
                   Rmrr->DeviceScope[Index].PciPath[1]
                   );
    NeedRemove = FALSE;
    if ((DisableBit == 0xFF) ||
        ((DisableBit == 0x80) &&
         (MmioRead32 (MmPciBase (0, Rmrr->DeviceScope[Index].PciPath[0], Rmrr->DeviceScope[Index].PciPath[1]) + 0x00) == 0xFFFFFFFF))
        ) {
      NeedRemove = TRUE;
    }
    CopyMem (
      &Rmrr->DeviceScope[ValidDeviceScopeNum],
      &Rmrr->DeviceScope[Index],
      sizeof (EFI_ACPI_DEV_SCOPE_STRUCTURE)
      );

    if (Rmrr->RmrLimitAddress == 0x0) {
      NeedRemove = TRUE;
    }

    if (NeedRemove) {
      Length -= sizeof (EFI_ACPI_DEV_SCOPE_STRUCTURE);
    } else {
      ValidDeviceScopeNum++;
    }
  }
  ///
  /// If No deviceScope is left, set length as 0x00
  ///
  if (Length > EFI_ACPI_RMRR_HEADER_LENGTH) {
    Rmrr->Length = Length;
  } else {
    Rmrr->Length = 0;
  }
}

/**
  Update the DMAR table

  @param[in, out] TableHeader         - The table to be set
  @param[in, out] Version             - Version to publish
**/
VOID
DmarTableUpdate (
  IN OUT   EFI_ACPI_DESCRIPTION_HEADER       *TableHeader,
  IN OUT   EFI_ACPI_TABLE_VERSION            *Version
  )
{
  EFI_ACPI_DMAR_TABLE *DmarTable;
  EFI_ACPI_DMAR_TABLE TempDmarTable;
  UINTN               Offset;
  UINTN               StructureLen;
  UINTN               McD0BaseAddress;
  UINT64              MchBar;
  UINT16              IgdMode;
  UINT16              GttMode;
  UINT32              IgdMemSize;
  UINT32              GttMemSize;
  EFI_STATUS          Status;
  MISC_DXE_CONFIG     *MiscDxeConfig;

  IgdMemSize  = 0;
  GttMemSize  = 0;
  DmarTable   = (EFI_ACPI_DMAR_TABLE *) TableHeader;

  Status = GetConfigBlock ((VOID *) mSaPolicy, &gMiscDxeConfigGuid, (VOID *)&MiscDxeConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Set INTR_REMAP bit (BIT 0) if interrupt remapping is supported
  ///
  if (mInterruptRemappingSupport) {
    DmarTable->Flags |= BIT0;
  }

  if (SaConfigHob->VtdData.X2ApicOptOut == 1) {
    DmarTable->Flags |= BIT1;
  } else {
    DmarTable->Flags &= 0xFD;
  }

  ///
  /// Get OemId
  ///
  CopyMem (DmarTable->Header.OemId, PcdGetPtr (PcdAcpiDefaultOemId), sizeof (DmarTable->Header.OemId));
  DmarTable->Header.OemTableId = PcdGet64 (PcdAcpiDefaultOemTableId);

  ///
  /// Calculate IGD memsize
  ///
  McD0BaseAddress = MmPciBase (SA_MC_BUS, 0, 0);
  MchBar = MmioRead32 (McD0BaseAddress + R_SA_MCHBAR) &~BIT0;
  //
  // For 64-Bit Memory Space BARs ((BAR[x] & 0xFFFFF000) + ((BAR[x+1] & 0xFFFFFFFF) << 32)
  //
  if ((MchBar & B_PCI_BAR_MEMORY_TYPE_MASK) == B_PCI_BAR_MEMORY_TYPE_64) {
    MchBar = (MchBar & 0xFFFFF000) + LShiftU64(MmioRead32 (McD0BaseAddress + R_SA_MCHBAR + 4), 32);
  }

  IgdMode = ((MmioRead16 (McD0BaseAddress + R_SA_GGC) & B_SKL_SA_GGC_GMS_MASK) >> N_SKL_SA_GGC_GMS_OFFSET) & 0xFF;
  if (IgdMode < 0xF0) {
    IgdMemSize = IgdMode * 32 * (1024) * (1024);
  } else {
    IgdMemSize = 4 * (IgdMode - 0xF0 + 1) * (1024) * (1024);
  }
  ///
  /// Calculate GTT mem size
  ///
  GttMemSize = 0;
  GttMode = (MmioRead16 (McD0BaseAddress + R_SA_GGC) & B_SKL_SA_GGC_GGMS_MASK) >> N_SKL_SA_GGC_GGMS_OFFSET;
  if (GttMode <= V_SKL_SA_GGC_GGMS_8MB) {
    GttMemSize = (1 << GttMode) * (1024) * (1024);
  }

  DmarTable->RmrrIgd.RmrBaseAddress   = (MmioRead32 (McD0BaseAddress + R_SA_TOLUD) & ~(0x01)) - IgdMemSize - GttMemSize;
  DmarTable->RmrrIgd.RmrLimitAddress  = DmarTable->RmrrIgd.RmrBaseAddress + IgdMemSize + GttMemSize - 1;
  DEBUG ((DEBUG_INFO, "RMRR Base  address IGD %016lX\n", DmarTable->RmrrIgd.RmrBaseAddress));
  DEBUG ((DEBUG_INFO, "RMRR Limit address IGD %016lX\n", DmarTable->RmrrIgd.RmrLimitAddress));

  DmarTable->RmrrUsb.RmrBaseAddress   = MiscDxeConfig->RmrrUsbBaseAddress[0];
  DmarTable->RmrrUsb.RmrLimitAddress  = MiscDxeConfig->RmrrUsbBaseAddress[1];

  ///
  /// Convert to 4KB alignment.
  ///
  if (DmarTable->RmrrUsb.RmrLimitAddress != 0x0) {
    DmarTable->RmrrUsb.RmrBaseAddress  &= (EFI_PHYSICAL_ADDRESS) ~0xFFF;
    DmarTable->RmrrUsb.RmrLimitAddress &= (EFI_PHYSICAL_ADDRESS) ~0xFFF;
    DmarTable->RmrrUsb.RmrLimitAddress += 0x1000-1;
  }

  DEBUG ((DEBUG_INFO, "RMRR Base  address USB %016lX\n", DmarTable->RmrrUsb.RmrBaseAddress));
  DEBUG ((DEBUG_INFO, "RMRR Limit address USB %016lX\n", DmarTable->RmrrUsb.RmrLimitAddress));

  if (DmarTable->RmrrUsb.RmrBaseAddress == 0) {
    DEBUG ((DEBUG_WARN, "WARNING:  RmrrUsb.RmrBaseAddress is 0.\n"));
  }
  ///
  /// Update DRHD structures of DmarTable
  ///
  DmarTable->DrhdEngine1.RegisterBaseAddress = (MmioRead32 (MchBar + R_SA_MCHBAR_VTD1_OFFSET) &~1);
  DmarTable->DrhdEngine2.RegisterBaseAddress = (MmioRead32 (MchBar + R_SA_MCHBAR_VTD2_OFFSET) &~1);

  DEBUG ((DEBUG_INFO, "VTD base address1 %x\n", DmarTable->DrhdEngine1.RegisterBaseAddress));
  DEBUG ((DEBUG_INFO, "VTD base address2 %x\n", DmarTable->DrhdEngine2.RegisterBaseAddress));
  ///
  /// copy DmarTable to TempDmarTable to be processed
  ///
  CopyMem (&TempDmarTable, DmarTable, sizeof (EFI_ACPI_DMAR_TABLE));

  UpdateDrhd (&TempDmarTable.DrhdEngine1);
  UpdateDrhd2 (&TempDmarTable.DrhdEngine2);

  ///
  /// Update RMRR structures of temp DMAR table
  ///
  UpdateRmrr ((VOID *) &TempDmarTable.RmrrUsb);
  UpdateRmrr ((VOID *) &TempDmarTable.RmrrIgd);

  ///
  /// Remove unused device scope or entire DRHD structures
  ///
  Offset = (UINTN) (&TempDmarTable.DrhdEngine1);
  if (TempDmarTable.DrhdEngine1.Length != 0) {
    Offset += TempDmarTable.DrhdEngine1.Length;
  }
  if (TempDmarTable.DrhdEngine2.Length != 0) {
    StructureLen = TempDmarTable.DrhdEngine2.Length;
    CopyMem ((VOID *) Offset, (VOID *) &TempDmarTable.DrhdEngine2, TempDmarTable.DrhdEngine2.Length);
    Offset += StructureLen;
  }
  ///
  /// Remove unused device scope or entire RMRR structures
  ///
  if (TempDmarTable.RmrrUsb.Length != 0) {
    StructureLen = TempDmarTable.RmrrUsb.Length;
    CopyMem ((VOID *) Offset, (VOID *) &TempDmarTable.RmrrUsb, TempDmarTable.RmrrUsb.Length);
    Offset += StructureLen;
  }
  if (TempDmarTable.RmrrIgd.Length != 0) {
    StructureLen = TempDmarTable.RmrrIgd.Length;
    CopyMem ((VOID *) Offset, (VOID *) &TempDmarTable.RmrrIgd, TempDmarTable.RmrrIgd.Length);
    Offset += StructureLen;
  }
  Offset = Offset - (UINTN) &TempDmarTable;
  ///
  /// Re-calculate DMAR table check sum
  ///
  TempDmarTable.Header.Checksum = (UINT8) (TempDmarTable.Header.Checksum + TempDmarTable.Header.Length - Offset);
  ///
  /// Set DMAR table length
  ///
  TempDmarTable.Header.Length = (UINT32) Offset;
  ///
  /// Replace DMAR table with rebuilt table TempDmarTable
  ///
  CopyMem ((VOID *) DmarTable, (VOID *) &TempDmarTable, TempDmarTable.Header.Length);
}

/**
  EndOfDxe routine for update DMAR
**/
VOID
UpdateDmarEndOfDxe (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_HANDLE                      *HandleBuffer;
  UINTN                           NumberOfHandles;
  EFI_FV_FILETYPE                 FileType;
  UINT32                          FvStatus;
  EFI_FV_FILE_ATTRIBUTES          Attributes;
  UINTN                           Size;
  UINTN                           i;
  INTN                            Instance;
  EFI_ACPI_TABLE_VERSION          Version;
  EFI_ACPI_COMMON_HEADER          *CurrentTable;
  UINTN                           AcpiTableHandle;
  EFI_FIRMWARE_VOLUME2_PROTOCOL   *FwVol;
  EFI_ACPI_TABLE_PROTOCOL         *AcpiTable;
  EFI_ACPI_DESCRIPTION_HEADER     *VtdAcpiTable;
  STATIC BOOLEAN                  Triggered = FALSE;
  if (Triggered) {
    return;
  }

  Triggered     = TRUE;

  FwVol         = NULL;
  AcpiTable     = NULL;
  VtdAcpiTable  = NULL;


  ///
  ///
  if ((SaConfigHob->VtdData.VtdDisable == TRUE) || (MmioRead32 (MmPciBase (SA_MC_BUS, 0, 0) + R_SA_MC_CAPID0_A_OFFSET) & BIT23)) {
    DEBUG ((DEBUG_INFO, "Vtd Disabled, skip DMAR Table install\n"));
    return;
  }

  ///
  /// Locate ACPI support protocol
  ///
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);

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
                      &gSaAcpiTableStorageGuid,
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
  if (FwVol == NULL) {
    return;
  }
  ///
  /// By default, a table belongs in all ACPI table versions published.
  ///
  Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;

  ///
  /// Read tables from the storage file.
  ///
  Instance      = 0;
  CurrentTable  = NULL;

  while (Status == EFI_SUCCESS) {
    Status = FwVol->ReadSection (
                      FwVol,
                      &gSaAcpiTableStorageGuid,
                      EFI_SECTION_RAW,
                      Instance,
                      (VOID **) &CurrentTable,
                      &Size,
                      &FvStatus
                      );

    if (!EFI_ERROR (Status)) {
      ///
      /// Check the Signature ID to modify the table
      ///
      switch (((EFI_ACPI_DESCRIPTION_HEADER *) CurrentTable)->Signature) {

        case EFI_ACPI_VTD_DMAR_TABLE_SIGNATURE:
          VtdAcpiTable = (EFI_ACPI_DESCRIPTION_HEADER *) CurrentTable;
          DmarTableUpdate (VtdAcpiTable, &Version);
          break;

        default:
          break;
      }
      ///
      /// Increment the instance
      ///
      Instance++;
      CurrentTable = NULL;
    }
  }
  ///
  /// Update the VTD table in the ACPI tables.
  ///
  AcpiTableHandle = 0;
  if (VtdAcpiTable != NULL) {
    Status = AcpiTable->InstallAcpiTable (
                          AcpiTable,
                          VtdAcpiTable,
                          VtdAcpiTable->Length,
                          &AcpiTableHandle
                          );
    FreePool (VtdAcpiTable);
  }
}

/**
  Locate the VT-d ACPI tables data file and read ACPI SSDT tables.
  Publish the appropriate SSDT based on current configuration and capabilities.

  @param[in] SaPolicy     -  SA DXE Policy protocol

  @retval EFI_SUCCESS     - Vtd initialization complete
  @exception EFI_UNSUPPORTED - Vtd is not enabled by policy
**/
EFI_STATUS
VtdInit (
  IN  SA_POLICY_PROTOCOL    *SaPolicy
  )
{
  UINTN        McD0BaseAddress;

  mInterruptRemappingSupport  = FALSE;
  SaConfigHob       = NULL;
  SaConfigHob = GetFirstGuidHob (&gSaConfigHobGuid);
  if (SaConfigHob != NULL) {
    mInterruptRemappingSupport  = SaConfigHob->VtdData.InterruptRemappingSupport;
  }

  McD0BaseAddress             = MmPciBase (SA_MC_BUS, 0, 0);
  mSaPolicy                   = SaPolicy;

  if (((SaConfigHob != NULL) && (SaConfigHob->VtdData.VtdDisable)) || (MmioRead32 (McD0BaseAddress + R_SA_MC_CAPID0_A_OFFSET) & BIT23)) {
    DEBUG ((DEBUG_WARN, "VTd disabled or no capability!\n"));
    return EFI_UNSUPPORTED;
  }
  ///
  /// Check SA supports VTD and VTD is enabled in setup menu
  ///
  DEBUG ((DEBUG_INFO, "VTd enabled\n"));

  return EFI_SUCCESS;
}
