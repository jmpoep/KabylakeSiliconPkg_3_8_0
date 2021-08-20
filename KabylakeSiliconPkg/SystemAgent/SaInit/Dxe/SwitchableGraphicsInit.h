/** @file
  Header file for the SwitchableGraphics Dxe driver.
  This driver loads SwitchableGraphics ACPI tables.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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
#ifndef _SWITCHABLE_GRAPHICS_DXE_H_
#define _SWITCHABLE_GRAPHICS_DXE_H_

#include <IndustryStandard/Acpi.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Library/UefiLib.h>
#include <Library/PciLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/TimerLib.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/PciIo.h>
#include <Guid/HobList.h>
#include <Guid/EventGroup.h>
#include <Protocol/LegacyBios.h>
#include <Protocol/FirmwareVolume2.h>

#include <Library/MmPciLib.h>
#include <PchAccess.h>
#include <SaAccess.h>
#include <Private/SaConfigHob.h>
#include <Protocol/SaPolicy.h>
#include <Protocol/SaGlobalNvsArea.h>
#include <CpuRegs.h>
#include <PcieRegs.h>
#include <Library/CpuPlatformLib.h>
#include <Library/PchPcieRpLib.h>

///
/// Switchable Graphics defines.
///
#define CONVENTIONAL_MEMORY_TOP 0xA0000 ///< 640 KB
#define BIN_FILE_SIZE_MAX       0x10000

#define OPTION_ROM_SIGNATURE    0xAA55

///
/// PEG Capability Equates
///
#define PEG_CAP_ID  0x10
#define PEG_CAP_VER 0x2

#pragma pack(1)
typedef struct {
  UINT16  Signature;  ///< 0xAA55
  UINT8   Reserved[22];
  UINT16  PcirOffset;
} VBIOS_OPTION_ROM_HEADER;
#pragma pack()

#pragma pack(1)
typedef struct {
  UINT32  Signature;  ///< "PCIR"
  UINT16  VendorId;
  UINT16  DeviceId;
  UINT16  Reserved0;
  UINT16  Length;
  UINT8   Revision;
  UINT8   ClassCode[3];
  UINT16  ImageLength;
  UINT16  CodeRevision;
  UINT8   CodeType;
  UINT8   Indicator;
  UINT16  Reserved1;
} VBIOS_PCIR_STRUCTURE;
#pragma pack()

/**
  Initialize the SwitchableGraphics support.

  @retval EFI_SUCCESS          - SwitchableGraphics initialization complete
  @retval EFI_OUT_OF_RESOURCES - Unable to allocated memory
**/
EFI_STATUS
SwitchableGraphicsInit (
  VOID
  );

/**
  Load and execute the dGPU VBIOS.

  @param[in] VbiosConfig - Pointer to VbiosData policy for Load/Execute and VBIOS Source.
      LoadVbios    : 0 = Do Not Load   ; 1 = Load VBIOS
      ExecuteVbios : 0 = Do Not Execute; 1 = Execute VBIOS
      VbiosSource  : 0 = PCIE Device   ; 1 = FirmwareVolume => TBD

  @retval EFI_SUCCESS     - Load and execute successful.
  @exception EFI_UNSUPPORTED - Secondary VBIOS not loaded.
**/
EFI_STATUS
LoadAndExecuteDgpuVbios (
  IN   SA_POLICY_PROTOCOL       *SaPolicy
  );

/**
  Initialize the runtime SwitchableGraphics support data for ACPI tables in GlobalNvs.

  @retval EFI_SUCCESS - The data updated successfully.
**/
EFI_STATUS
UpdateGlobalNvsData (
  VOID
  );

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
  );

/**
  Search and return the offset of desired Pci Express Capability ID
    CAPID list:
      0x0001 = Advanced Error Rreporting Capability
      0x0002 = Virtual Channel Capability
      0x0003 = Device Serial Number Capability
      0x0004 = Power Budgeting Capability

    @param[in] Bus       -   Pci Bus Number
    @param[in] Device    -   Pci Device Number
    @param[in] Function  -   Pci Function Number
    @param[in] CapId     -   Extended CAPID to search for

    @retval 0       - CAPID not found
    @retval Other   - CAPID found, Offset of desired CAPID
**/
UINT32
PcieFindExtendedCapId (
  IN UINT8  Bus,
  IN UINT8  Device,
  IN UINT8  Function,
  IN UINT16 CapId
  );

/**
  Find the Offset to a given Capabilities ID
    CAPID list:
      0x01 = PCI Power Management Interface
      0x04 = Slot Identification
      0x05 = MSI Capability
      0x10 = PCI Express Capability

    @param[in] Bus       -   Pci Bus Number
    @param[in] Device    -   Pci Device Number
    @param[in] Function  -   Pci Function Number
    @param[in] CapId     -   CAPID to search for

    @retval 0       - CAPID not found
    @retval Other   - CAPID found, Offset of desired CAPID
**/
UINT32
PcieFindCapId (
  IN UINT8 Bus,
  IN UINT8 Device,
  IN UINT8 Function,
  IN UINT8 CapId
  );

/**
Load Intel SG SSDT Tables

@param[in] SsdtSelector       - Selector to load particular SSDT

@retval EFI_SUCCESS - SG SSDT Table load successful.
**/
EFI_STATUS
LoadAcpiTables (
  IN  UINTN                     SsdtSelector
  );


/**
  This function gets registered as a EndOfDxe callback to perform SG initialization

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
SgEndOfDxeCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  );

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
  );

/**
  Find the Pcie Capability ID for PEG1/2 port.

  @param[in] PegPortDev       - PEG Port Device Number
  @param[in] PegPortFun       - PEG Port Function Number

  @retval EFI_SUCCESS - Found  out the Cap Id.
**/
EFI_STATUS
FindPegEpCapId (
  IN UINT8 PegPortDev,
  IN UINT8 PegPortFun
  );

#endif
