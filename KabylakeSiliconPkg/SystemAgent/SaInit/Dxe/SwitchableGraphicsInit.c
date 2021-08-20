/** @file
  SwitchableGraphics Dxe driver.
  This DXE driver loads SwitchableGraphics acpi tables
  for the platform.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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
#include "SwitchableGraphicsInit.h"
#include <Library/GpioNativeLib.h>
#include <Library/PchInfoLib.h>

extern SA_POLICY_PROTOCOL                           *mSaPolicy;
extern EFI_GUID gSgAcpiTableStorageGuid;
extern EFI_GUID gSgAcpiTablePchStorageGuid;

GLOBAL_REMOVE_IF_UNREFERENCED SA_CONFIG_HOB         *SaConfigHob;
GLOBAL_REMOVE_IF_UNREFERENCED VOID                  *VbiosAddress = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                VbiosSize;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                 EndpointBus;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                 RootPortDev;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                 RootPortFun;
GLOBAL_REMOVE_IF_UNREFERENCED PCH_SERIES            PchSeries;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_SKU               CpuSku;

/**
  Initialize the SwitchableGraphics support (DXE).

  @retval EFI_SUCCESS          - SwitchableGraphics initialization complete
  @retval EFI_OUT_OF_RESOURCES - Unable to allocated memory
  @retval EFI_NOT_FOUND        - SA DataHob not found
  @retval EFI_DEVICE_ERROR     - Error Accessing SG GPIO
**/
EFI_STATUS
SwitchableGraphicsInit (
  VOID
  )
{
  EFI_STATUS  Status;
  EFI_EVENT   EndOfDxeEvent;

  PchSeries   = GetPchSeries ();
  CpuSku      = GetCpuSku ();

  ///
  /// Get SG GPIO info from SA HOB.
  ///
  Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, (VOID **) &SaConfigHob);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SaConfigHob = GetNextGuidHob (&gSaConfigHobGuid, SaConfigHob);
  if (SaConfigHob == NULL) {
    return EFI_NOT_FOUND;
  }

  RootPortDev = SaConfigHob->SaRtd3.RootPortDev;
  RootPortFun = SaConfigHob->SaRtd3.RootPortFun;

  DEBUG ((DEBUG_INFO, "dGPU Rootport info[B/D/F] : [0x00/0x%x/0x%x]\n", RootPortDev, RootPortFun));


  ///
  /// Register an end of DXE event for SG to do tasks before invoking any UEFI drivers,
  /// applications, or connecting consoles,...
  ///
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  SgEndOfDxeCallback,
                  NULL,
                  &gEfiEndOfDxeEventGroupGuid,
                  &EndOfDxeEvent
                  );

  return Status;
}

/**
  Initialize the runtime SwitchableGraphics support data for ACPI tables in GlobalNvs.

  @retval EFI_SUCCESS    - The data updated successfully.
**/
EFI_STATUS
UpdateGlobalNvsData (
  VOID
  )
{
  SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL  *SaGlobalNvsArea;
  EFI_STATUS                             Status;

  ///
  ///  Locate the SA Global NVS Protocol.
  ///
  Status = gBS->LocateProtocol (
                  &gSaGlobalNvsAreaProtocolGuid,
                  NULL,
                  (VOID **) &SaGlobalNvsArea
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ///
  /// SG Mode for ASL usage
  ///
  SaGlobalNvsArea->Area->SgMode                  |= SaConfigHob->SaRtd3.SgMode;
  SaGlobalNvsArea->Area->Pcie0GpioSupport         = SaConfigHob->SaRtd3.Rtd3Pcie0Gpio.GpioSupport;
  SaGlobalNvsArea->Area->Pcie1GpioSupport         = SaConfigHob->SaRtd3.Rtd3Pcie1Gpio.GpioSupport;
  SaGlobalNvsArea->Area->Pcie2GpioSupport         = SaConfigHob->SaRtd3.Rtd3Pcie2Gpio.GpioSupport;
  SaGlobalNvsArea->Area->DelayAfterPwrEn          = SaConfigHob->SaRtd3.DelayAfterPwrEn;
  SaGlobalNvsArea->Area->DelayAfterHoldReset      = SaConfigHob->SaRtd3.DelayAfterHoldReset;
//
// KblGBegin
//
  SaGlobalNvsArea->Area->DelayAfterOffMethod      = SaConfigHob->SaRtd3.DelayAfterOffMethod;
  SaGlobalNvsArea->Area->DelayAfterLinkEnable     = SaConfigHob->SaRtd3.DelayAfterLinkEnable;
  SaGlobalNvsArea->Area->GenSpeedChangeEnable     = SaConfigHob->SaRtd3.GenSpeedChangeEnable;
//
// KblGEnd
//
  DEBUG ((DEBUG_INFO, "SG:: Switchable Graphics Mode : 0x%x\n", SaConfigHob->SaRtd3.SgMode));

  if (SaConfigHob->SaRtd3.Rtd3Pcie0Gpio.GpioSupport != 0 && PcieDevicePresent(RootPortDev, RootPortFun)) {
    ///
    /// GPIO Assignment for ASL usage
    ///
    SaGlobalNvsArea->Area->Pcie0HoldRstExpanderNo  = SaConfigHob->SaRtd3.Rtd3Pcie0Gpio.HoldRst.ExpanderNo;
    SaGlobalNvsArea->Area->Pcie0HoldRstGpioNo      = SaConfigHob->SaRtd3.Rtd3Pcie0Gpio.HoldRst.GpioNo;
    SaGlobalNvsArea->Area->Pcie0HoldRstActiveInfo  = SaConfigHob->SaRtd3.Rtd3Pcie0Gpio.HoldRst.Active;
    SaGlobalNvsArea->Area->Pcie0PwrEnExpanderNo    = SaConfigHob->SaRtd3.Rtd3Pcie0Gpio.PwrEnable.ExpanderNo;
    SaGlobalNvsArea->Area->Pcie0PwrEnGpioNo        = SaConfigHob->SaRtd3.Rtd3Pcie0Gpio.PwrEnable.GpioNo;
    SaGlobalNvsArea->Area->Pcie0PwrEnActiveInfo    = SaConfigHob->SaRtd3.Rtd3Pcie0Gpio.PwrEnable.Active;
    SaGlobalNvsArea->Area->Pcie0WakeGpioNo         = SaConfigHob->SaRtd3.Rtd3Pcie0Gpio.WakeGpioNo;
    SaGlobalNvsArea->Area->Pcie0ClkReqMaskValue    = ((UINT32)0x1 << SaConfigHob->SaRtd3.SaRtd3Pcie0ClkRecNumber);

    ///
    /// Find capability ID for Endpoint on PEG Port 0
    ///
    Status = FindPegEpCapId (RootPortDev, RootPortFun);
  }

  if (SaConfigHob->SaRtd3.Rtd3Pcie1Gpio.GpioSupport != 0 && PcieDevicePresent(SA_PEG11_DEV_NUM, SA_PEG11_FUN_NUM)) {
    ///
    /// GPIO Assignment for ASL usage
    ///
    SaGlobalNvsArea->Area->Pcie1HoldRstExpanderNo  = SaConfigHob->SaRtd3.Rtd3Pcie1Gpio.HoldRst.ExpanderNo;
    SaGlobalNvsArea->Area->Pcie1HoldRstGpioNo      = SaConfigHob->SaRtd3.Rtd3Pcie1Gpio.HoldRst.GpioNo;
    SaGlobalNvsArea->Area->Pcie1HoldRstActiveInfo  = SaConfigHob->SaRtd3.Rtd3Pcie1Gpio.HoldRst.Active;
    SaGlobalNvsArea->Area->Pcie1PwrEnExpanderNo    = SaConfigHob->SaRtd3.Rtd3Pcie1Gpio.PwrEnable.ExpanderNo;
    SaGlobalNvsArea->Area->Pcie1PwrEnGpioNo        = SaConfigHob->SaRtd3.Rtd3Pcie1Gpio.PwrEnable.GpioNo;
    SaGlobalNvsArea->Area->Pcie1PwrEnActiveInfo    = SaConfigHob->SaRtd3.Rtd3Pcie1Gpio.PwrEnable.Active;
    SaGlobalNvsArea->Area->Pcie1WakeGpioNo         = SaConfigHob->SaRtd3.Rtd3Pcie1Gpio.WakeGpioNo;
    SaGlobalNvsArea->Area->Pcie1ClkReqMaskValue    = ((UINT32)0x1 << SaConfigHob->SaRtd3.SaRtd3Pcie1ClkRecNumber);

    ///
    /// Find capability ID for Endpoint on PEG Port 1
    ///
    Status = FindPegEpCapId (SA_PEG11_DEV_NUM, SA_PEG11_FUN_NUM);
  }

  if (SaConfigHob->SaRtd3.Rtd3Pcie2Gpio.GpioSupport != 0 && PcieDevicePresent(SA_PEG12_DEV_NUM, SA_PEG12_FUN_NUM)) {
    ///
    /// GPIO Assignment for ASL usage
    ///
    SaGlobalNvsArea->Area->Pcie2HoldRstExpanderNo  = SaConfigHob->SaRtd3.Rtd3Pcie2Gpio.HoldRst.ExpanderNo;
    SaGlobalNvsArea->Area->Pcie2HoldRstGpioNo      = SaConfigHob->SaRtd3.Rtd3Pcie2Gpio.HoldRst.GpioNo;
    SaGlobalNvsArea->Area->Pcie2HoldRstActiveInfo  = SaConfigHob->SaRtd3.Rtd3Pcie2Gpio.HoldRst.Active;
    SaGlobalNvsArea->Area->Pcie2PwrEnExpanderNo    = SaConfigHob->SaRtd3.Rtd3Pcie2Gpio.PwrEnable.ExpanderNo;
    SaGlobalNvsArea->Area->Pcie2PwrEnGpioNo        = SaConfigHob->SaRtd3.Rtd3Pcie2Gpio.PwrEnable.GpioNo;
    SaGlobalNvsArea->Area->Pcie2PwrEnActiveInfo    = SaConfigHob->SaRtd3.Rtd3Pcie2Gpio.PwrEnable.Active;
    SaGlobalNvsArea->Area->Pcie2WakeGpioNo         = SaConfigHob->SaRtd3.Rtd3Pcie2Gpio.WakeGpioNo;
    SaGlobalNvsArea->Area->Pcie2ClkReqMaskValue    = ((UINT32)0x1 << SaConfigHob->SaRtd3.SaRtd3Pcie2ClkRecNumber);

    ///
    /// Find capability ID for Endpoint on PEG Port 2
    ///
    Status = FindPegEpCapId (SA_PEG12_DEV_NUM, SA_PEG12_FUN_NUM);
  }


  return Status;
}

/**
  Load and execute the dGPU VBIOS.

  @param[in] SaPolicy    - SA DXE Policy protocol
      LoadVbios    - 0 = Do Not Load   ; 1 = Load VBIOS
      ExecuteVbios - 0 = Do Not Execute; 1 = Execute VBIOS
      VbiosSource  - 0 = PCIE Device   ; 1 = FirmwareVolume => TBD

  @retval EFI_SUCCESS     - Load and execute successful.
  @exception EFI_UNSUPPORTED - Secondary VBIOS not loaded.
**/
EFI_STATUS
LoadAndExecuteDgpuVbios (
  IN   SA_POLICY_PROTOCOL       *SaPolicy
  )
{
  EFI_HANDLE                *HandleBuffer;
  UINTN                     HandleCount;
  UINTN                     Index;
  VBIOS_PCIR_STRUCTURE      *PcirBlockPtr;
  EFI_STATUS                Status;
  EFI_PCI_IO_PROTOCOL       *PciIo;
  VBIOS_OPTION_ROM_HEADER   *VBiosRomImage;
  EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;
  EFI_IA32_REGISTER_SET     RegSet;
  EFI_PHYSICAL_ADDRESS      ImageLocation;
  UINTN                     RootBaseAddress;
  UINTN                     EpBusBaseAddress;
  UINTN                     Offset;
  VBIOS_DXE_CONFIG          *VbiosDxeConfig;
  BOOLEAN                   DgpuOpRomCopied;

  Status = GetConfigBlock ((VOID *) SaPolicy, &gVbiosDxeConfigGuid, (VOID *)&VbiosDxeConfig);
  ASSERT_EFI_ERROR (Status);

  HandleBuffer = NULL;
  DgpuOpRomCopied = FALSE;

  DEBUG ((DEBUG_INFO, "SG:: LoadAndExecuteDgpuVbios\n"));

  ///
  /// Endpoint Device Bus#
  ///

  RootBaseAddress  = MmPciBase (SA_MC_BUS, RootPortDev, RootPortFun);
  EndpointBus      = MmioRead8 (RootBaseAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);
  EpBusBaseAddress = MmPciBase (EndpointBus, SA_TEMP_DGPU_DEV, SA_TEMP_DGPU_FUN);

  ///
  ///  Endpoint Device Not found
  ///
  if (EndpointBus == 0xFF) {
    DEBUG ((DEBUG_ERROR, "SG:: 0x00/0x%x/0x%x Rootport's Endpoint Device Not found\n", RootPortDev, RootPortFun));
    return EFI_UNSUPPORTED;
  }

  ///
  /// Check Policy setting for loading VBIOS
  ///
  if (VbiosDxeConfig->LoadVbios != 0) {

    DEBUG ((DEBUG_INFO, "SG:: Start to load dGPU VBIOS if available\n"));

    ///
    /// Set as if an umcompressed video BIOS image was not obtainable.
    ///
    VBiosRomImage = NULL;

    ///
    /// Get all PCI IO protocols
    ///
    Status = gBS->LocateHandleBuffer (
                    ByProtocol,
                    &gEfiPciIoProtocolGuid,
                    NULL,
                    &HandleCount,
                    &HandleBuffer
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    ///
    /// Find the video BIOS by checking each PCI IO handle for DGPU video
    /// BIOS OPROM.
    ///
    for (Index = 0; Index < HandleCount; Index++) {
      Status = gBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gEfiPciIoProtocolGuid,
                      (VOID **) &PciIo
                      );
      if (EFI_ERROR (Status) || (PciIo->RomImage == NULL)) {
        ///
        /// If this PCI device doesn't have a ROM image, skip to the next device.
        ///
        continue;
      }

      VBiosRomImage = PciIo->RomImage;

      ///
      /// Get pointer to PCIR structure
      ///
      PcirBlockPtr = (VBIOS_PCIR_STRUCTURE *) ((UINTN) VBiosRomImage + VBiosRomImage->PcirOffset);

      ///
      /// Check if we have an video BIOS OPROM for DGPU.
      ///
      if ((VBiosRomImage->Signature == OPTION_ROM_SIGNATURE) &&
          (MmioRead16 (EpBusBaseAddress + PCI_VENDOR_ID_OFFSET) == PcirBlockPtr->VendorId) &&
          (PcirBlockPtr->ClassCode[2] == 0x03)
          ) {

        DEBUG ((DEBUG_INFO, "SG:: Loading dGPU VBIOS...\n"));

        ///
        /// Allocate space for copying Oprom
        ///
        VbiosSize    = (PcirBlockPtr->ImageLength) * 512;
        VbiosAddress = AllocatePool (VbiosSize);
        if (VbiosAddress == NULL) {
          break;
        }

        ///
        /// Execute VBIOS based on Policy setting
        ///
        if (VbiosDxeConfig->ExecuteVbios) {
          DEBUG ((DEBUG_INFO, "SG:: Execute dGPU VBIOS...\n"));
          ///
          /// Memory IO Bus Master needs to be enabled when we execute the vbios
          ///
          ///
          /// Enable Memory Access, IO Access Bus Master enable on PEG/PCH ROOT PORT
          ///
          MmioOr16 (RootBaseAddress + PCI_COMMAND_OFFSET, BIT0 + BIT1 + BIT2);

          ///
          /// Enable Memory Access, IO Access Bus Master enable and Rom Enable on Peg/PCH Endpoint device
          ///
          MmioOr16 (EpBusBaseAddress + PCI_COMMAND_OFFSET, BIT0 + BIT1 + BIT2);

          ///
          /// Allocate 64kb under 1MB memory region
          ///
          Status = AllocateLegacyMemory (
                     AllocateMaxAddress,
                     CONVENTIONAL_MEMORY_TOP,
                     (BIN_FILE_SIZE_MAX / 4096),
                     &ImageLocation
                     );
          if (!EFI_ERROR (Status)) {
            SetMem ((VOID *) (UINTN) ImageLocation, BIN_FILE_SIZE_MAX, 0);

            ///
            /// After allocation copy VBIOS to buffer
            ///
            CopyMem ((VOID *) (UINTN) ImageLocation, PciIo->RomImage, VbiosSize);

            Status = gBS->LocateProtocol (
                            &gEfiLegacyBiosProtocolGuid,
                            NULL,
                            (VOID **) &LegacyBios
                            );
            if (!EFI_ERROR (Status)) {
              SetMem (&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);

              RegSet.H.AH = MmioRead8  (RootBaseAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);
              Offset      = MmioRead16 ((UINTN) ImageLocation + 0x40);
              LegacyBios->FarCall86 (
                            LegacyBios,
                            ((UINT16) RShiftU64 ((ImageLocation & 0x000FFFF0),
                                        4)),
                            ((UINT16) Offset),
                            &RegSet,
                            NULL,
                            0
                            );

              Offset = MmioRead16 ((UINTN) ImageLocation + 0x42) + (UINTN) ImageLocation;
              if (MmioRead16 ((UINTN) ImageLocation + 0x44) == 0x0) {
                VbiosSize = MmioRead8 ((UINTN) ImageLocation + 0x2) * 512;
              } else {
                VbiosSize = MmioRead16 ((UINTN) ImageLocation + 0x44) * 512;
              }
              ///
              /// Copy Oprom to allocated space for the following scenario:
              /// # Load vbios and Execute vbios policy setting
              ///
              DEBUG ((DEBUG_INFO, "Copy Oprom to allocated space: Load & Execute policy satisfied\n"));
              CopyMem (VbiosAddress, (VOID *) Offset, VbiosSize);
              DgpuOpRomCopied = TRUE;
              SetMem ((VOID *) (UINTN) ImageLocation, BIN_FILE_SIZE_MAX, 0);
            }
            FreePages ((VOID *) (UINTN) ImageLocation, (BIN_FILE_SIZE_MAX / 4096));
          }

          ///
          /// Disable Memory Access, IO Access Bus Master enable and Rom Enable on PEG/PCH Endpoint device
          ///
          MmioAnd16 (EpBusBaseAddress + PCI_COMMAND_OFFSET, (UINT16) ~(BIT0 + BIT1 + BIT2));

          ///
          /// Disable Memory Access, IO Access Bus Master enable on PEG/PCH Root Port
          ///
          MmioAnd16 (RootBaseAddress + PCI_COMMAND_OFFSET, (UINT16) ~(BIT0 + BIT1 + BIT2));
        }

        ///
        /// Copy Oprom to allocated space  for the following scenario:
        /// # Load vbios and Execute vbios policy setting in which dGPU execution is not called
        /// # Load vbios but don't Execute vbios policy setting
        ///
        if ((VbiosAddress!=NULL) && (!DgpuOpRomCopied)) {
          DEBUG ((DEBUG_INFO, "Copy Oprom to allocated space: Load policy satisfied\n"));
          CopyMem (VbiosAddress, PciIo->RomImage, VbiosSize);
          DgpuOpRomCopied = TRUE;
        }

        break;
      }
    }

  }


  if (VbiosAddress!=NULL) {
    FreePool (VbiosAddress);
  }

  if (HandleBuffer!=NULL) {
    FreePool (HandleBuffer);
  }

  return EFI_SUCCESS;
}

/**
  Do an AllocatePages () of type AllocateMaxAddress for EfiBootServicesCode
  memory.

  @param[in] AllocateType     - Allocated Legacy Memory Type
  @param[in] StartPageAddress - Start address of range
  @param[in] Pages            - Number of pages to allocate
  @param[in, out] Result      - Result of allocation

  @retval EFI_SUCCESS - Legacy16 code loaded
  @retval Other       - No protocol installed, unload driver.
**/
EFI_STATUS
AllocateLegacyMemory (
  IN  EFI_ALLOCATE_TYPE         AllocateType,
  IN  EFI_PHYSICAL_ADDRESS      StartPageAddress,
  IN  UINTN                     Pages,
  IN OUT  EFI_PHYSICAL_ADDRESS  *Result
  )
{
  EFI_STATUS            Status;
  EFI_PHYSICAL_ADDRESS  MemPage;

  ///
  /// Allocate Pages of memory less <= StartPageAddress
  ///
  MemPage = (EFI_PHYSICAL_ADDRESS) (UINTN) StartPageAddress;
  Status  = gBS->AllocatePages (AllocateType, EfiBootServicesCode, Pages, &MemPage);
  ///
  /// Do not ASSERT on Status error but let caller decide since some cases
  /// memory is already taken but that is ok.
  ///
  if (!EFI_ERROR (Status)) {
    *Result = (EFI_PHYSICAL_ADDRESS) (UINTN) MemPage;
  }

  return Status;
}

/**
  Load Intel SG SSDT Tables

  @param[in] SsdtSelector       - Selector to load particular SSDT

  @retval EFI_SUCCESS - SG SSDT Table load successful.
**/
EFI_STATUS
LoadAcpiTables (
  IN  UINTN                     SsdtSelector
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
  EFI_GUID                      AcpiTableGuid;
  EFI_FV_FILETYPE               FileType;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVol;
  EFI_ACPI_TABLE_PROTOCOL       *AcpiTable;
  EFI_ACPI_TABLE_VERSION        Version;
  EFI_ACPI_DESCRIPTION_HEADER   *TableHeader;
  EFI_ACPI_COMMON_HEADER        *Table;

  FwVol         = NULL;
  Table         = NULL;

  AcpiTableGuid = gSgAcpiTableStorageGuid;
  if (PchSeries == PchLp) {
    AcpiTableGuid = gSgAcpiTablePchStorageGuid;
  }

  DEBUG ((DEBUG_INFO, "SG:: Loading ACPI Tables...\n"));

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
                      &AcpiTableGuid,
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
  /// By default, a table belongs in all ACPI table versions published.
  ///
  Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;

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
                      &AcpiTableGuid,
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

      if (CompareGuid (&gSgAcpiTableStorageGuid, &AcpiTableGuid)) {
        if (((EFI_ACPI_DESCRIPTION_HEADER *) TableHeader)->OemTableId == SIGNATURE_64 ('S', 'g', 'P', 'e', 'g', 0, 0, 0)) {
          ///
          /// This is SG SSDT [dGPU is present on PEG RootPort]
          ///
          DEBUG ((DEBUG_INFO, "SG:: ---- SG SSDT ----\n"));
          DEBUG ((DEBUG_INFO, "SG:: Found out SSDT:SgPeg [SgSsdt.asl]. dGPU is present on PEG RootPort.\n"));
          LoadTable = TRUE;
        }
      }
      if (CompareGuid (&gSgAcpiTablePchStorageGuid, &AcpiTableGuid)) {
        if ((SsdtSelector == 0) && (CpuSku == EnumCpuUlt)) {
          if (((EFI_ACPI_DESCRIPTION_HEADER *) TableHeader)->OemTableId == SIGNATURE_64 ('S', 'g', 'U', 'l', 't', 0, 0, 0)) {
            ///
            /// This is SG SSDT [dGPU is present on PCH RootPort]
            ///
            DEBUG ((DEBUG_INFO, "SG:: ---- SG SSDT ----\n"));
            DEBUG ((DEBUG_INFO, "SG:: Found out SSDT:SgUlt [SgUlt.asl]. dGPU is present on PCH RootPort.\n"));
            LoadTable = TRUE;
          }
        }

        if ((SsdtSelector == 0) && (CpuSku == EnumCpuUlx)) {
          if (((EFI_ACPI_DESCRIPTION_HEADER *) TableHeader)->OemTableId == SIGNATURE_64 ('S', 'g', 'U', 'l', 'x', 0, 0, 0)) {
            ///
            /// This is SG SSDT [dGPU is present on PCH RootPort]
            ///
            DEBUG ((DEBUG_INFO, "SG:: ---- SG SSDT ----\n"));
            DEBUG ((DEBUG_INFO, "SG:: Found out SSDT:SgUlx [SgUlx.asl]. dGPU is present on PCH RootPort.\n"));
            LoadTable = TRUE;
          }
        }

        if (SsdtSelector == 2) {
          if (((EFI_ACPI_DESCRIPTION_HEADER *) TableHeader)->OemTableId == SIGNATURE_64('S', 'g', 'U', 'l', 'x', 0, 0, 0)) {
            ///
            /// This is SG SSDT [dGPU is present on PCH RootPort]
            ///
            DEBUG ((DEBUG_INFO, "SG:: ---- SG SSDT ----\n"));
            DEBUG ((DEBUG_INFO, "SG:: Found out SSDT:SgUlx [SgUlx.asl]. dGPU is present on PCH RootPort.\n"));
            LoadTable = TRUE;
          }
        }

        if (SsdtSelector == 1) {
          if (((EFI_ACPI_DESCRIPTION_HEADER *) TableHeader)->OemTableId == SIGNATURE_64 ('S', 'g', 'P', 'c', 'h', 0, 0, 0)) {
            ///
            /// This is SG SSDT [dGPU is present on PCH RootPort]
            ///
            DEBUG ((DEBUG_INFO, "SG:: ---- SG SSDT ----\n"));
            DEBUG ((DEBUG_INFO, "SG:: Found out SSDT:SgPch [SgPch.asl]. dGPU is present on PCH RootPort.\n"));
            LoadTable = TRUE;
          }
        }
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


/**
  This function gets registered as a EndOfDxe callback to perform SG initialization

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
SgEndOfDxeCallback (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS  Status;
  UINTN       Count;
  UINTN       RootPortIndex;

  DEBUG ((DEBUG_INFO, "SG:: EndOfDxe Callback\n"));

  Count = 0;

  ///
  /// Update GlobalNvs data for runtime usage
  ///
  Status = UpdateGlobalNvsData ();
  ASSERT_EFI_ERROR (Status);

  if (((SaConfigHob->SaRtd3.SgMode == SgModeMuxless) &&
       (SaConfigHob->SaRtd3.Rtd3Pcie0Gpio.GpioSupport != 0))
      || IsKblGPackage() // KblGContent
      ) {
    ///
    /// Load Intel SG SSDT tables
    ///
    if (PchSeries == PchH) {
      Status = LoadAcpiTables (Count);
      ASSERT_EFI_ERROR (Status);
    } else if (PchSeries == PchLp) {
        //
        // For, KBL - R, RootPort #1 is required so based on the CPU and Rootport check, SgUlx SSDT will load which is giving RootPort #1 unlike SgUlt which is giving RootPort #9.
        //
        GetPchPcieRpNumber ((UINTN) RootPortDev, (UINTN) RootPortFun, &RootPortIndex);
        if ((CpuSku == EnumCpuUlt) && (RootPortIndex == PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_1)) {
          LoadAcpiTables (1);
          LoadAcpiTables (2);
        } else {
          for (Count = 0; Count < 2; Count++) {
            Status = LoadAcpiTables (Count);
            ASSERT_EFI_ERROR(Status);
          }
        }
    }

    ///
    /// Load and Execute dGPU VBIOS
    ///
    Status = LoadAndExecuteDgpuVbios (mSaPolicy);
    ASSERT_EFI_ERROR (Status);
  }
}

/**
  Find if the Pcie Device is present.

  @param[in] PciePortDev       - Pcie Port Device Number
  @param[in] PciePortFun       - Pcie Port Function Number

  @retval TRUE - Found  out the device is present
  @retval FALSE - Device is not present
**/
BOOLEAN
PcieDevicePresent (
  IN UINT8 PciePortDev,
  IN UINT8 PciePortFun
  )
{
  UINTN                                  PciePortAddress;
  UINT8                                  PciePortBus;
  ///
  /// Get the PCIe Port Base Address to find Secondary bus number & sub-ordinate bus number
  ///
  PciePortAddress = MmPciBase (0, PciePortDev, PciePortFun);

  ///
  /// Check if Pcie device is present or not.
  ///
  if (MmioRead16 (PciePortAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return FALSE;
  }
  ///
  /// Get the Endpoint PCIe Port Bus number by reading secondary bus offset.
  ///
  PciePortBus = MmioRead8 (PciePortAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);

  ///
  /// Check if End Point is prensent or not on Pcie device..
  ///
  if (MmioRead16 (MmPciBase (PciePortBus, 0, 0) + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return FALSE;
  }

  return TRUE;
}

/**
  Find the Pcie Capability ID for PEG1/2 port.

  @param[in] PciePortDev       - Pcie Port Device Number
  @param[in] PciePortFun       - Pcie Port Function Number

  @retval EFI_SUCCESS - Found  out the Cap Id.
**/
EFI_STATUS
FindPegEpCapId (
  IN UINT8 PciePortDev,
  IN UINT8 PciePortFun
  )
{
  SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL  *SaGlobalNvsArea;
  UINTN                                  PciePortAddress;
  UINT8                                  PciePortBus;
  UINT8                                  PcieCapOffset;
  EFI_STATUS                             Status;

  ///
  ///  Locate the SA Global NVS Protocol.
  ///
  Status = gBS->LocateProtocol (
                  &gSaGlobalNvsAreaProtocolGuid,
                  NULL,
                  (VOID **) &SaGlobalNvsArea
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ///
  /// Get the PCIe Port Base Address to find Secondary bus number & sub-ordinate bus number
  ///
  PciePortAddress = MmPciBase (0, PciePortDev, PciePortFun);

  ///
  /// Check if Pcie device is present or not.
  ///
  if (MmioRead16 (PciePortAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return EFI_UNSUPPORTED;
  }
  ///
  /// Get the Endpoint PCIe Port Bus number by reading secondary bus offset.
  ///
  PciePortBus = MmioRead8 (PciePortAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);

  ///
  /// Check if End Point is prensent or not on Pcie device..
  ///
  if (MmioRead16 (MmPciBase (PciePortBus, 0, 0) + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return EFI_UNSUPPORTED;
  }

  PcieCapOffset = (UINT8) PcieFindCapId (PciePortBus, 0, 0, PEG_CAP_ID);

  switch (PciePortFun) {

    case 0:
      SaGlobalNvsArea->Area->Pcie0SecBusNum   = PciePortBus;
      SaGlobalNvsArea->Area->Pcie0EpCapOffset = PcieCapOffset;
      break;

    case 1:
      SaGlobalNvsArea->Area->Pcie1SecBusNum   = PciePortBus;
      SaGlobalNvsArea->Area->Pcie1EpCapOffset = PcieCapOffset;
      break;

    case 2:
      SaGlobalNvsArea->Area->Pcie2SecBusNum   = PciePortBus;
      SaGlobalNvsArea->Area->Pcie2EpCapOffset = PcieCapOffset;
      break;
  }

  return Status;
}

