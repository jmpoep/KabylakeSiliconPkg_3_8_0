/** @file
  Provides the basic interfaces to abstract a PCI Host Bridge Resource Allocation

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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
#include "PciHostBridge.h"
#include "PciRootBridge.h"
#include <Protocol/SaPolicy.h>
#include <Protocol/SaGlobalNvsArea.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>
#include <Library/HobLib.h>
#include <Private/SaConfigHob.h> // AdvancedFeaturesContent

///
/// Support 4G address space
///
#define HIGHEST_SUPPORTED_ADDRESS 0x8000000000L

///
/// Support above 4G MMIO address space
///
#ifndef BASE_128GB
#define BASE_128GB  0x2000000000ULL  //128GB
#endif
#ifndef SIZE_64GB
#define SIZE_64GB  0x1000000000ULL  //64GB
#endif

///
/// Hard code: Root Bridge Number within the host bridge
///            Root Bridge's attribute
///            Root Bridge's device path
///            Root Bridge's resource aperture
///
static UINTN                              RootBridgeNumber[1] = { 1 };
///
/// Hard code EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM  0 to support prefetchable memory allocation
///
static UINT64                             RootBridgeAttribute[1] = { EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM };
static EFI_PCI_ROOT_BRIDGE_DEVICE_PATH    mEfiPciRootBridgeDevicePath[1] = {
  {
    {
      {
        ACPI_DEVICE_PATH,
        ACPI_DP,
        {
          (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)),
          (UINT8) ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8)
        }
      },
      EISA_PNP_ID (0x0A03),
      0
    },
    {
      END_DEVICE_PATH_TYPE,
      END_ENTIRE_DEVICE_PATH_SUBTYPE,
      {
        END_DEVICE_PATH_LENGTH,
        0
      }
    }
  }
};

static PCI_ROOT_BRIDGE_RESOURCE_APERTURE  mResAperture[1] = { { 0, 255, 0, 0xffffffff, 0, 1 << 16 } };
static EFI_HANDLE                         mDriverImageHandle;


GLOBAL_REMOVE_IF_UNREFERENCED SA_POLICY_PROTOCOL                    *mSaPolicy;     // AdvancedFeaturesContent
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                                 mEnableAbove4GBMmioBiosAssignemnt;    // AdvancedFeaturesContent
GLOBAL_REMOVE_IF_UNREFERENCED SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL *mSaGlobalNvsAreaProtocol;
GLOBAL_REMOVE_IF_UNREFERENCED UINT64                                mMmio64Base;
GLOBAL_REMOVE_IF_UNREFERENCED UINT64                                mMmio64Length;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                                mMmio32Base;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                                mMmio32Length;

///
/// Implementation
///
/**
  A protocol callback which updates 64bits MMIO Base and Length in SA GNVS area

  @param[in] Event    - The triggered event.
  @param[in] Context  - Context for this event.

**/
VOID
UpdateSaGnvsForMmioResourceBaseLength (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS                    Status;

  Status = gBS->LocateProtocol (&gSaGlobalNvsAreaProtocolGuid, NULL, (VOID **) &mSaGlobalNvsAreaProtocol);
  if (Status != EFI_SUCCESS) {
    return;
  }
  gBS->CloseEvent (Event);

  DEBUG ((DEBUG_INFO, "[PciHostBridge] Update SA GNVS Area.\n"));
  mSaGlobalNvsAreaProtocol->Area->Mmio64Base                    = mMmio64Base;
  mSaGlobalNvsAreaProtocol->Area->Mmio64Length                  = mMmio64Length;
  mSaGlobalNvsAreaProtocol->Area->Mmio32Base                    = mMmio32Base;
  mSaGlobalNvsAreaProtocol->Area->Mmio32Length                  = mMmio32Length;
}

/**
  Entry point of PCI Host Bridge driver

  @param[in] ImageHandle -
  @param[in] SystemTable -

  @retval EFI_SUCCESS          - Driver Start OK
  @retval EFI_OUT_OF_RESOURCES - Fail to allocate required resource
  @retval EFI_DEVICE_ERROR     - Fail to install PCI_ROOT_BRIDGE_IO protocol.
**/
EFI_STATUS
EFIAPI
PciHostBridgeEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS                Status;
  UINTN                     Loop1;
  UINTN                     Loop2;
  PCI_HOST_BRIDGE_INSTANCE  *HostBridge;
  PCI_ROOT_BRIDGE_INSTANCE  *PrivateData;
  EFI_PHYSICAL_ADDRESS      PciBaseAddress;
  EFI_PHYSICAL_ADDRESS      RemapBase;
  EFI_PHYSICAL_ADDRESS      RemapLimit;
  EFI_PHYSICAL_ADDRESS      MeSegMask;
  EFI_PHYSICAL_ADDRESS      MeStolenSize;
  BOOLEAN                   MeStolenEnable;
  UINT32                    Tolud;
  UINT64                    Length;
  UINTN                     McD0BaseAddress;
  UINTN                     ResMemLimit1;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR PciMemorySpaceDescriptor;
  UINT64                    BaseAddress;
  UINT64                    Attributes;


  mDriverImageHandle = ImageHandle;

  mSaPolicy              = NULL;         // AdvancedFeaturesContent
  mEnableAbove4GBMmioBiosAssignemnt = 0; // AdvancedFeaturesContent
  mMmio64Base                       = 0;
  mMmio64Length                     = 0;
  mMmio32Base                       = 0;
  mMmio32Length                     = 0;
  ///
  /// This system has one Host Bridge (one Root Bridge in this Host Bridge)
  ///
  ///
  /// Create Host Bridge Device Handle
  ///
  for (Loop1 = 0; Loop1 < HOST_BRIDGE_NUMBER; Loop1++) {
    HostBridge = AllocatePool (sizeof (PCI_HOST_BRIDGE_INSTANCE));
    ASSERT (HostBridge != NULL);
    if (HostBridge == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    HostBridge->Signature         = PCI_HOST_BRIDGE_SIGNATURE;
    HostBridge->RootBridgeNumber  = RootBridgeNumber[Loop1];
    HostBridge->ResourceSubmited  = FALSE;
    HostBridge->CanRestarted      = TRUE;

    ///
    /// InitializeListHead (&HostBridge->Head);
    ///
    HostBridge->ResAlloc.NotifyPhase          = NotifyPhase;
    HostBridge->ResAlloc.GetNextRootBridge    = GetNextRootBridge;
    HostBridge->ResAlloc.GetAllocAttributes   = GetAttributes;
    HostBridge->ResAlloc.StartBusEnumeration  = StartBusEnumeration;
    HostBridge->ResAlloc.SetBusNumbers        = SetBusNumbers;
    HostBridge->ResAlloc.SubmitResources      = SubmitResources;
    HostBridge->ResAlloc.GetProposedResources = GetProposedResources;
    HostBridge->ResAlloc.PreprocessController = PreprocessController;
    HostBridge->HostBridgeHandle              = NULL;
    Status = gBS->InstallProtocolInterface (
                    &HostBridge->HostBridgeHandle,
                    &gEfiPciHostBridgeResourceAllocationProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &HostBridge->ResAlloc
                    );
    if (EFI_ERROR (Status)) {
      FreePool (HostBridge);
      return EFI_DEVICE_ERROR;
    }
    ///
    /// Create Root Bridge Device Handle in this Host Bridge
    ///
    InitializeListHead (&HostBridge->Head);
    for (Loop2 = 0; Loop2 < HostBridge->RootBridgeNumber; Loop2++) {
      PrivateData = AllocatePool (sizeof (PCI_ROOT_BRIDGE_INSTANCE));
      ASSERT (PrivateData != NULL);
      if (PrivateData == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }
      PrivateData->Signature  = PCI_ROOT_BRIDGE_SIGNATURE;
      PrivateData->DevicePath = (EFI_DEVICE_PATH_PROTOCOL *) &mEfiPciRootBridgeDevicePath[Loop2];
      RootBridgeConstructor (
        &PrivateData->Io,
        HostBridge->HostBridgeHandle,
        RootBridgeAttribute[Loop2],
        &mResAperture[Loop2]
        );
      PrivateData->Handle = NULL;
      Status = gBS->InstallMultipleProtocolInterfaces (
                      &PrivateData->Handle,
                      &gEfiDevicePathProtocolGuid,
                      PrivateData->DevicePath,
                      &gEfiPciRootBridgeIoProtocolGuid,
                      &PrivateData->Io,
                      NULL
                      );
      if (EFI_ERROR (Status)) {
        FreePool (PrivateData);
        return EFI_DEVICE_ERROR;
      }

      InsertTailList (&HostBridge->Head, &PrivateData->Link);
    }
  }
  ///
  /// Allocate 56 KB of I/O space [0x2000..0xFFFF]
  ///
  DEBUG ((DEBUG_INFO, " Allocating  IO space for PCI from 0x%X to 0x%X\n", PcdGet16 (PcdPciReservedIobase) ,PcdGet16 (PcdPciReservedIoLimit)));
  Status = gDS->AddIoSpace (
                  EfiGcdIoTypeIo,
                  PcdGet16 (PcdPciReservedIobase),
                  PcdGet16 (PcdPciReservedIoLimit) - PcdGet16 (PcdPciReservedIobase) + 1
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Allocate PCI memory space.
  ///
  ///
  /// Read memory map registers
  ///
  McD0BaseAddress = MmPciBase (SA_MC_BUS, 0, 0);
  RemapBase       = (MmioRead32 (McD0BaseAddress + R_SA_REMAPBASE) + LShiftU64(MmioRead32 (McD0BaseAddress + R_SA_REMAPBASE + 4), 32)) & B_SA_REMAPBASE_REMAPBASE_MASK;
  RemapLimit      = (MmioRead32 (McD0BaseAddress + R_SA_REMAPLIMIT) + LShiftU64(MmioRead32 (McD0BaseAddress + R_SA_REMAPLIMIT + 4), 32)) & B_SA_REMAPLIMIT_REMAPLMT_MASK;
  Tolud           = MmioRead32 (McD0BaseAddress + R_SA_TOLUD) & B_SA_TOLUD_TOLUD_MASK;
  PciBaseAddress  = Tolud;
  MeSegMask       = (MmioRead32(McD0BaseAddress + R_SA_MESEG_MASK) + LShiftU64(MmioRead32(McD0BaseAddress + R_SA_MESEG_MASK + 4), 32));
  MeStolenEnable  = (BOOLEAN) ((MeSegMask & B_SA_MESEG_MASK_ME_STLEN_EN_MASK) != 0);

  ///
  /// First check if memory remap is used
  ///
  if ((RemapBase > RemapLimit) && (MeStolenEnable)) {
    MeStolenSize = MeSegMask & B_SA_MESEG_MASK_MEMASK_MASK;
    if (MeStolenSize != 0) {
      MeStolenSize = HIGHEST_SUPPORTED_ADDRESS - MeStolenSize;
    }
    ///
    /// Remap is disabled -> PCI starts at TOLUD + ME Stolen size
    ///
    PciBaseAddress += MeStolenSize;
  }

  ResMemLimit1 = PcdGet32 (PcdPciReservedMemLimit);
  if (ResMemLimit1 == 0) {
    ResMemLimit1 = ((UINTN) MmPciBase (0,0,0));
  }

  Length = ResMemLimit1 - PciBaseAddress;

  if (Length != 0) {
    DEBUG ((DEBUG_INFO, " Allocating PCI space from 0x%X to 0x%X\n", (UINT32) PciBaseAddress, (UINT32)
            (PciBaseAddress + Length - 1)));
    Status = gDS->AddMemorySpace (
                    EfiGcdMemoryTypeMemoryMappedIo,
                    PciBaseAddress,
                    Length,
                    0
                    );
    ASSERT_EFI_ERROR (Status);
    mMmio32Base = (UINT32) PciBaseAddress;
    mMmio32Length = (UINT32) Length;
  }

  ///
  /// Reserve Pcie MMIO range
  ///
  DEBUG ((EFI_D_INFO, "Allocating PCIe MMIO space from 0x%X to 0x%X\n", PcdGet64 (PcdPciExpressBaseAddress), PcdGet64 (PcdPciExpressBaseAddress) + PcdGet32 (PcdPciExpressRegionLength) - 1));
  Status = gDS->AddMemorySpace (
                EfiGcdMemoryTypeMemoryMappedIo,
                PcdGet64 (PcdPciExpressBaseAddress),
                PcdGet32 (PcdPciExpressRegionLength),
                0
                );

  //
  //  Change PCI memory space attribute to Runtime Memory
  //
  BaseAddress = (EFI_PHYSICAL_ADDRESS)PcdGet64 (PcdPciExpressBaseAddress);
  Length      = PcdGet32 (PcdPciExpressRegionLength);
  Status      = gDS->GetMemorySpaceDescriptor (BaseAddress, &PciMemorySpaceDescriptor);
  ASSERT_EFI_ERROR (Status);

  Attributes  = PciMemorySpaceDescriptor.Attributes | EFI_MEMORY_RUNTIME;

  Status      = gDS->SetMemorySpaceAttributes (
                         BaseAddress,
                         Length,
                         Attributes
                         );
  ASSERT_EFI_ERROR (Status);
  DEBUG ((EFI_D_INFO, "Successfully changed memory attribute for PCIe\n"));

  return EFI_SUCCESS;
}

/**
  Enter a certain phase of the PCI enumeration process

  @param[in] This  - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL instance
  @param[in] Phase - The phase during enumeration

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_INVALID_PARAMETER  -  Wrong phase parameter passed in.
  @retval EFI_NOT_READY          -  Resources have not been submitted yet.
**/
EFI_STATUS
EFIAPI
NotifyPhase (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PHASE    Phase
  )
{
  PCI_HOST_BRIDGE_INSTANCE  *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE  *RootBridgeInstance;
  PCI_RESOURCE_TYPE         Index;
  LIST_ENTRY                *List;
  EFI_PHYSICAL_ADDRESS      BaseAddress;
  UINT64                    AddrLen;
  UINTN                     BitsOfAlignment;
  UINT64                    Alignment;
  EFI_STATUS                Status;
  EFI_STATUS                ReturnStatus;
  UINT64                    Length;    // AdvancedFeaturesContent
  EFI_PHYSICAL_ADDRESS      PciBaseAddress;    // AdvancedFeaturesContent
  BOOLEAN                   MmioHasBeenAllocated;
  EFI_EVENT                 SaGlobalNvsUpdateEvent;
  VOID                      *SaGlobalNvsInstalledRegistration;
  SA_CONFIG_HOB             *SaConfigHob;    // AdvancedFeaturesContent
  MISC_DXE_CONFIG           *MiscDxeConfig;  // AdvancedFeaturesContent

  HostBridgeInstance = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  RootBridgeInstance = NULL;
  switch (Phase) {
    case EfiPciHostBridgeBeginEnumeration:
      if (HostBridgeInstance->CanRestarted) {
        ///
        /// Reset the Each Root Bridge
        ///
        List = HostBridgeInstance->Head.ForwardLink;
        while (List != &HostBridgeInstance->Head) {
          RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
          for (Index = TypeIo; Index < TypeMax; Index++) {
            RootBridgeInstance->ResAllocNode[Index].Type    = Index;
            RootBridgeInstance->ResAllocNode[Index].Base    = 0;
            RootBridgeInstance->ResAllocNode[Index].Length  = 0;
            RootBridgeInstance->ResAllocNode[Index].Status  = ResNone;
          }

          List = List->ForwardLink;
        }

        HostBridgeInstance->ResourceSubmited  = FALSE;
        HostBridgeInstance->CanRestarted      = TRUE;
#ifndef MINTREE_FLAG
        ///
        /// Retrieve SaPolicy and see if above 4GB MMIO BIOS assignment enabled
        ///
        if (mSaPolicy == NULL) {
          Status = gBS->LocateProtocol (&gSaPolicyProtocolGuid, NULL, (VOID **) &mSaPolicy);
          if (mSaPolicy != NULL) {
            Status = GetConfigBlock ((VOID *) mSaPolicy, &gMiscDxeConfigGuid, (VOID *)&MiscDxeConfig);
            ASSERT_EFI_ERROR (Status);
            if ((MiscDxeConfig != NULL) && (MiscDxeConfig->EnableAbove4GBMmio == 1)) {
              mEnableAbove4GBMmioBiosAssignemnt = 1;
            }
          }
          ///
          /// Enable Above 4GB MMIO when Aperture Size is 2GB or higher
          ///
          ///
          /// Get SaConfigHob HOB
          ///
          SaConfigHob = NULL;
          SaConfigHob = (SA_CONFIG_HOB *) GetFirstGuidHob (&gSaConfigHobGuid);
          if ((SaConfigHob != NULL) && (SaConfigHob->ApertureSize >= 15)) {
            mEnableAbove4GBMmioBiosAssignemnt = 1;
          }
          if (mEnableAbove4GBMmioBiosAssignemnt == 1) {
            ///
            /// Provide 64GB available above 4GB MMIO resource
            /// limited to use single variable MTRR to cover this above 4GB MMIO region.
            ///
            PciBaseAddress = BASE_128GB;
            Length         = SIZE_64GB;
            if (Length != 0) {
              DEBUG ((DEBUG_INFO, " Allocating PCI space from 0x%lX", (UINT64) PciBaseAddress));
              DEBUG ((DEBUG_INFO, " to 0x%lX\n", (UINT64) (PciBaseAddress + Length - 1)));
              Status = gDS->AddMemorySpace (
                              EfiGcdMemoryTypeMemoryMappedIo,
                              PciBaseAddress,
                              Length,
                              EFI_MEMORY_UC
                              );
              ASSERT_EFI_ERROR (Status);
              DEBUG ((DEBUG_INFO, " [HostBridge]Setting Attributes...\n"));
              Status = gDS->SetMemorySpaceAttributes (
                              PciBaseAddress,
                              Length,
                              EFI_MEMORY_UC
                              );
              ASSERT_EFI_ERROR (Status);
              if (Status == EFI_SUCCESS) {
                mEnableAbove4GBMmioBiosAssignemnt = 1;
                if (RootBridgeInstance != NULL) {
                  RootBridgeInstance->MemLimit = MAX_ADDRESS;
                }
                ///
                /// Update variables for above 4GB MMIO Base/Length.
                ///
                mMmio64Base   = PciBaseAddress;
                mMmio64Length = Length;
              } else {
                ///
                /// Something wrong when creating above 4GB resource -> disable the support.
                ///
                mEnableAbove4GBMmioBiosAssignemnt = 0;
              }
            }
          }
#endif //MINTREE_FLAG
          ///
          /// If SA Global NVS protocol not installed yet, register SA Global Nvs protocol callback event
          ///
          Status = gBS->LocateProtocol (&gSaGlobalNvsAreaProtocolGuid, NULL, (VOID **) &mSaGlobalNvsAreaProtocol);
          if (Status == EFI_NOT_FOUND) {
            Status = gBS->CreateEvent (
                            EVT_NOTIFY_SIGNAL,
                            TPL_CALLBACK,
                            (EFI_EVENT_NOTIFY) UpdateSaGnvsForMmioResourceBaseLength,
                            NULL,
                            &SaGlobalNvsUpdateEvent
                            );
            ASSERT_EFI_ERROR (Status);
            Status = gBS->RegisterProtocolNotify (
                            &gSaGlobalNvsAreaProtocolGuid,
                            SaGlobalNvsUpdateEvent,
                            &SaGlobalNvsInstalledRegistration
                            );
            ASSERT_EFI_ERROR (Status);
          } else {
            UpdateSaGnvsForMmioResourceBaseLength (NULL, NULL);
          }
        }  // AdvancedFeaturesContent
      } else {
        ///
        /// Can not restart
        ///
        return EFI_NOT_READY;
      }
      break;

    case EfiPciHostBridgeEndEnumeration:
      break;

    case EfiPciHostBridgeBeginBusAllocation:
      ///
      /// No specific action is required here, can perform any chipset specific programing
      ///
      HostBridgeInstance->CanRestarted = FALSE;
      return EFI_SUCCESS;
      break;

    case EfiPciHostBridgeEndBusAllocation:
      ///
      /// No specific action is required here, can perform any chipset specific programing
      ///
      return EFI_SUCCESS;
      break;

    case EfiPciHostBridgeBeginResourceAllocation:
      ///
      /// No specific action is required here, can perform any chipset specific programing
      ///
      return EFI_SUCCESS;
      break;

    case EfiPciHostBridgeAllocateResources:
      ReturnStatus = EFI_SUCCESS;
      if (HostBridgeInstance->ResourceSubmited) {
        ///
        /// Take care of the resource dependencies between the root bridges
        ///
        List = HostBridgeInstance->Head.ForwardLink;
        while (List != &HostBridgeInstance->Head) {
          RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
          for (Index = TypeIo; Index < TypeBus; Index++) {
            if (RootBridgeInstance->ResAllocNode[Index].Status != ResNone) {
              AddrLen   = RootBridgeInstance->ResAllocNode[Index].Length;
              Alignment = RootBridgeInstance->ResAllocNode[Index].Alignment;

              ///
              /// Get the number of '1' in Alignment.
              ///
              for (BitsOfAlignment = 0; Alignment != 0; BitsOfAlignment++) {
                Alignment = RShiftU64 (Alignment, 1);
              }

              switch (Index) {
                case TypeIo:
                  ///
                  /// It is impossible for this chipset to align 0xFFFF for IO16
                  /// So clear it
                  ///
                  if (BitsOfAlignment >= 16) {
                    BitsOfAlignment = 0;
                  }
                  if ((PcdGet8 (PcdEfiGcdAllocateType) == EfiGcdAllocateMaxAddressSearchBottomUp) || (PcdGet8 (PcdEfiGcdAllocateType) == EfiGcdAllocateMaxAddressSearchTopDown)) {
                    BaseAddress = 0xFFFF;
                  }
                  Status = gDS->AllocateIoSpace (
                                  PcdGet8 (PcdEfiGcdAllocateType),
                                  EfiGcdIoTypeIo,
                                  BitsOfAlignment,
                                  AddrLen,
                                  &BaseAddress,
                                  mDriverImageHandle,
                                  NULL
                                  );
                  if (!EFI_ERROR (Status)) {
                    RootBridgeInstance->ResAllocNode[Index].Base    = (UINTN) BaseAddress;
                    RootBridgeInstance->ResAllocNode[Index].Status  = ResAllocated;
                  } else {
                    ///
                    /// Not able to allocate enough I/O memory - critical stop
                    ///
                    DEBUG ((DEBUG_ERROR, "Out of I/O space! AllocateIoSpace() returned %r\n", Status));
                    DEBUG ((DEBUG_ERROR, "Size requested: 0x%lX bytes\n", AddrLen));
                    ReturnStatus = Status;
                  }
                  break;

                case TypeMem32:
                case TypePMem32:
                case TypeMem64:
                case TypePMem64:
                  MmioHasBeenAllocated = FALSE;
                  Status               = EFI_OUT_OF_RESOURCES;
                  BaseAddress          = 0;
                  ///
                  /// It is impossible for this chipset to align 0xFFFFFFFF for Mem32
                  /// So clear it
                  ///
                  if ((Index == TypeMem32) || (Index == TypePMem32)) {
                    if (BitsOfAlignment >= 32) {
                      BitsOfAlignment = 0;
                    }
                  }
#ifndef MINTREE_FLAG
                  ///
                  /// Enable BIOS above 4GB MMIO assignment only when policy enabled.
                  ///
                  if (mEnableAbove4GBMmioBiosAssignemnt == 1) {
                    ///
                    /// It is impossible for this chipset to align 0xFFFFFFFFFFFFFFFF for Mem64
                    /// So clear it
                    ///
                    if ((Index == TypeMem64) || (Index == TypePMem64)) {
                      if (BitsOfAlignment >= 64) {
                        BitsOfAlignment = 0;
                      }
                      DEBUG ((DEBUG_INFO, " Allocating TypeMem64..\n"));
                      BaseAddress = MAX_ADDRESS;
                      Status = gDS->AllocateMemorySpace (
                                      EfiGcdAllocateAnySearchTopDown,
                                      EfiGcdMemoryTypeMemoryMappedIo,
                                      BitsOfAlignment,
                                      AddrLen,
                                      &BaseAddress,
                                      mDriverImageHandle,
                                      NULL
                                      );
                      if (Status == EFI_SUCCESS) {
                        MmioHasBeenAllocated = TRUE;
                      }
                    }
                  }
#endif //MINTREE_FLAG
                  if (MmioHasBeenAllocated == FALSE) {
                    DEBUG ((DEBUG_INFO, " Allocating TypeMem32..\n"));
                    if ((PcdGet8 (PcdEfiGcdAllocateType) == EfiGcdAllocateMaxAddressSearchBottomUp) || (PcdGet8 (PcdEfiGcdAllocateType) == EfiGcdAllocateMaxAddressSearchTopDown)) {
                      BaseAddress = 0xFFFFFFFF;
                    }
                    Status = gDS->AllocateMemorySpace (
                                    PcdGet8 (PcdEfiGcdAllocateType),
                                    EfiGcdMemoryTypeMemoryMappedIo,
                                    BitsOfAlignment,
                                    AddrLen,
                                    &BaseAddress,
                                    mDriverImageHandle,
                                    NULL
                                    );
                  }
                  if (!EFI_ERROR (Status)) {
                    ///
                    /// We were able to allocate the PCI memory
                    ///
                    RootBridgeInstance->ResAllocNode[Index].Base    = (UINTN) BaseAddress;
                    RootBridgeInstance->ResAllocNode[Index].Status  = ResAllocated;
                  } else {
                    ///
                    /// Not able to allocate enough PCI memory - critical stop
                    ///
                    DEBUG ((DEBUG_ERROR, "Out of PCI memory! AllocateMemorySpace() returned %r\n", Status));
                    DEBUG ((DEBUG_ERROR, "Size requested: 0x%lX bytes\n", AddrLen));
                    ReturnStatus = Status;
                  }
                  break;
                default:
                  break;
              }
              ///
              /// end switch
              ///
            }
          }

          List = List->ForwardLink;
        }

        return ReturnStatus;
      } else {
        return EFI_NOT_READY;
      }
      break;

    case EfiPciHostBridgeSetResources:
      break;

    case EfiPciHostBridgeFreeResources:
      ReturnStatus  = EFI_SUCCESS;

      List          = HostBridgeInstance->Head.ForwardLink;
      while (List != &HostBridgeInstance->Head) {
        RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
        for (Index = TypeIo; Index < TypeBus; Index++) {
          if (RootBridgeInstance->ResAllocNode[Index].Status == ResAllocated) {
            AddrLen     = RootBridgeInstance->ResAllocNode[Index].Length;
            BaseAddress = RootBridgeInstance->ResAllocNode[Index].Base;
            switch (Index) {
              case TypeIo:
                Status = gDS->FreeIoSpace (BaseAddress, AddrLen);
                break;

              case TypeMem32:
              case TypePMem32:
              case TypeMem64:
              case TypePMem64:
                Status = gDS->FreeMemorySpace (BaseAddress, AddrLen);
                break;

              default:
                Status = EFI_INVALID_PARAMETER;

            }

            if (EFI_ERROR (Status)) {
              ReturnStatus = Status;
            }
            ///
            /// end switch
            ///
            RootBridgeInstance->ResAllocNode[Index].Type    = Index;
            RootBridgeInstance->ResAllocNode[Index].Base    = 0;
            RootBridgeInstance->ResAllocNode[Index].Length  = 0;
            RootBridgeInstance->ResAllocNode[Index].Status  = ResNone;
          }
        }

        List = List->ForwardLink;
      }

      HostBridgeInstance->ResourceSubmited  = FALSE;
      HostBridgeInstance->CanRestarted      = TRUE;
      return ReturnStatus;
      break;

    case EfiPciHostBridgeEndResourceAllocation:
      HostBridgeInstance->CanRestarted = FALSE;
      break;

    default:
      return EFI_INVALID_PARAMETER;
  }
  ///
  /// end switch
  ///
  return EFI_SUCCESS;
}

/**
  Return the device handle of the next PCI root bridge that is associated with
  this Host Bridge

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance
  @param[in] RootBridgeHandle  - Returns the device handle of the next PCI Root Bridge.
                      On input, it holds the RootBridgeHandle returned by the most
                      recent call to GetNextRootBridge().The handle for the first
                      PCI Root Bridge is returned if RootBridgeHandle is NULL on input

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_NOT_FOUND          -  Next PCI root bridge not found.
  @retval EFI_INVALID_PARAMETER  -  Wrong parameter passed in.
**/
EFI_STATUS
EFIAPI
GetNextRootBridge (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN OUT EFI_HANDLE                                   *RootBridgeHandle
  )
{
  BOOLEAN                   NoRootBridge;
  LIST_ENTRY                *List;
  PCI_HOST_BRIDGE_INSTANCE  *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE  *RootBridgeInstance;

  NoRootBridge        = TRUE;
  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;

  while (List != &HostBridgeInstance->Head) {
    NoRootBridge        = FALSE;
    RootBridgeInstance  = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (*RootBridgeHandle == NULL) {
      ///
      /// Return the first Root Bridge Handle of the Host Bridge
      ///
      *RootBridgeHandle = RootBridgeInstance->Handle;
      return EFI_SUCCESS;
    } else {
      if (*RootBridgeHandle == RootBridgeInstance->Handle) {
        ///
        /// Get next if have
        ///
        List = List->ForwardLink;
        if (List != &HostBridgeInstance->Head) {
          RootBridgeInstance  = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
          *RootBridgeHandle   = RootBridgeInstance->Handle;
          return EFI_SUCCESS;
        } else {
          return EFI_NOT_FOUND;
        }
      }
    }

    List = List->ForwardLink;
  }
  ///
  /// end while
  ///
  if (NoRootBridge) {
    return EFI_NOT_FOUND;
  } else {
    return EFI_INVALID_PARAMETER;
  }
}

/**
  Returns the attributes of a PCI Root Bridge.

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance.
  @param[in] RootBridgeHandle  - The device handle of the PCI Root Bridge
                      that the caller is interested in
  @param[in] Attributes        - The pointer to attributes of the PCI Root Bridge

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_INVALID_PARAMETER  -  Attributes parameter passed in is NULL or
                            RootBridgeHandle is not an EFI_HANDLE
                            that was returned on a previous call to
                            GetNextRootBridge().
**/
EFI_STATUS
EFIAPI
GetAttributes (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN EFI_HANDLE                                       RootBridgeHandle,
  OUT UINT64                                          *Attributes
  )
{
  LIST_ENTRY                *List;
  PCI_HOST_BRIDGE_INSTANCE  *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE  *RootBridgeInstance;

  if (Attributes == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;
  while (List != &HostBridgeInstance->Head) {
    RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (RootBridgeHandle == RootBridgeInstance->Handle) {
#ifndef MINTREE_FLAG
      if (mEnableAbove4GBMmioBiosAssignemnt == 1) {
        RootBridgeInstance->RootBridgeAttrib |= EFI_PCI_HOST_BRIDGE_MEM64_DECODE;
      }
#endif //MINTREE_FLAG
      *Attributes = RootBridgeInstance->RootBridgeAttrib;
      return EFI_SUCCESS;
    }

    List = List->ForwardLink;
  }
  ///
  /// RootBridgeHandle is not an EFI_HANDLE
  /// that was returned on a previous call to GetNextRootBridge()
  ///
  return EFI_INVALID_PARAMETER;
}

/**
  This is the request from the PCI enumerator to set up
  the specified PCI Root Bridge for bus enumeration process.

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance.
  @param[in] RootBridgeHandle  - The PCI Root Bridge to be set up.
  @param[in] Configuration     - Pointer to the pointer to the PCI bus resource descriptor.

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_OUT_OF_RESOURCES   -  Not enough pool to be allocated.
  @retval EFI_INVALID_PARAMETER  -  RootBridgeHandle is not a valid handle.
**/
EFI_STATUS
EFIAPI
StartBusEnumeration (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN EFI_HANDLE                                       RootBridgeHandle,
  OUT VOID                                            **Configuration
  )
{
  LIST_ENTRY                *List;
  PCI_HOST_BRIDGE_INSTANCE  *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE  *RootBridgeInstance;
  VOID                      *Buffer;
  UINT8                     *Temp;
  UINT64                    BusStart;
  UINT64                    BusEnd;

  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;

  while (List != &HostBridgeInstance->Head) {
    RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (RootBridgeHandle == RootBridgeInstance->Handle) {
      ///
      /// Set up the Root Bridge for Bus Enumeration
      ///
      BusStart  = RootBridgeInstance->BusBase;
      BusEnd    = RootBridgeInstance->BusLimit;

      ///
      /// Program the Hardware(if needed) if error return EFI_DEVICE_ERROR
      ///
      Buffer = AllocatePool (sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) + sizeof (EFI_ACPI_END_TAG_DESCRIPTOR));
      if (Buffer == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }

      Temp  = (UINT8 *) Buffer;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->Desc                  = ACPI_ADDRESS_SPACE_DESCRIPTOR;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->Len                   = 0x2B;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->ResType               = ACPI_ADDRESS_SPACE_TYPE_BUS;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->GenFlag               = 0;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->SpecificFlag          = 0;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->AddrSpaceGranularity  = 0;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->AddrRangeMin          = BusStart;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->AddrRangeMax          = 0;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->AddrTranslationOffset = 0;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->AddrLen               = BusEnd - BusStart + 1;

      Temp = Temp + sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR);

      ((EFI_ACPI_END_TAG_DESCRIPTOR *) Temp)->Desc = ACPI_END_TAG_DESCRIPTOR;
      ((EFI_ACPI_END_TAG_DESCRIPTOR *) Temp)->Checksum = 0x0;
      *Configuration = Buffer;
      return EFI_SUCCESS;
    }

    List = List->ForwardLink;
  }

  return EFI_INVALID_PARAMETER;
}

/**
  This function programs the PCI Root Bridge hardware so that
  it decodes the specified PCI bus range

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance
  @param[in] RootBridgeHandle  - The PCI Root Bridge whose bus range is to be programmed
  @param[in] Configuration     - The pointer to the PCI bus resource descriptor

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_INVALID_PARAMETER  -  Wrong parameters passed in.
**/
EFI_STATUS
EFIAPI
SetBusNumbers (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN EFI_HANDLE                                       RootBridgeHandle,
  IN VOID                                             *Configuration
  )
{
  LIST_ENTRY                *List;
  PCI_HOST_BRIDGE_INSTANCE  *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE  *RootBridgeInstance;
  UINT8                     *Ptr;
  UINTN                     BusStart;
  UINTN                     BusEnd;
  UINTN                     BusLen;

  if (Configuration == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Ptr = Configuration;

  ///
  /// Check the Configuration is valid
  ///
  if (*Ptr != ACPI_ADDRESS_SPACE_DESCRIPTOR) {
    return EFI_INVALID_PARAMETER;
  }

  if (((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Ptr)->ResType != ACPI_ADDRESS_SPACE_TYPE_BUS) {
    return EFI_INVALID_PARAMETER;
  }

  Ptr += sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR);
  if (*Ptr != ACPI_END_TAG_DESCRIPTOR) {
    return EFI_INVALID_PARAMETER;
  }

  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;
  Ptr                 = Configuration;
  while (List != &HostBridgeInstance->Head) {
    RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (RootBridgeHandle == RootBridgeInstance->Handle) {
      BusStart  = (UINTN) ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Ptr)->AddrRangeMin;
      BusLen    = (UINTN) ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Ptr)->AddrLen;
      BusEnd    = BusStart + BusLen - 1;
      if (BusStart > BusEnd) {
        return EFI_INVALID_PARAMETER;
      }

      if ((BusStart < RootBridgeInstance->BusBase) || (BusEnd > RootBridgeInstance->BusLimit)) {
        return EFI_INVALID_PARAMETER;
      }
      ///
      /// Update the Bus Range
      ///
      RootBridgeInstance->ResAllocNode[TypeBus].Base    = BusStart;
      RootBridgeInstance->ResAllocNode[TypeBus].Length  = BusLen;
      RootBridgeInstance->ResAllocNode[TypeBus].Status  = ResAllocated;

      ///
      /// Program the Root Bridge Hardware
      ///
      return EFI_SUCCESS;
    }

    List = List->ForwardLink;
  }

  return EFI_INVALID_PARAMETER;
}

/**
  Submits the I/O and memory resource requirements for the specified PCI Root Bridge

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance
  @param[in] RootBridgeHandle  - The PCI Root Bridge whose I/O and memory resource requirements
                      are being submitted
  @param[in] Configuration     - The pointer to the PCI I/O and PCI memory resource descriptor

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_INVALID_PARAMETER  -  Wrong parameters passed in.
**/
EFI_STATUS
EFIAPI
SubmitResources (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN EFI_HANDLE                                       RootBridgeHandle,
  IN VOID                                             *Configuration
  )
{
  LIST_ENTRY                        *List;
  PCI_HOST_BRIDGE_INSTANCE          *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE          *RootBridgeInstance;
  UINT8                             *Temp;
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *ptr;
  UINT64                            AddrLen;
  UINT64                            Alignment;

  ///
  /// Check the input parameter: Configuration
  ///
  if (Configuration == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;
  Temp                = (UINT8 *) Configuration;
  while (*Temp == ACPI_ADDRESS_SPACE_DESCRIPTOR) {
    Temp += sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR);
  }

  if (*Temp != ACPI_END_TAG_DESCRIPTOR) {
    return EFI_INVALID_PARAMETER;
  }

  Temp = (UINT8 *) Configuration;
  while (List != &HostBridgeInstance->Head) {
    RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (RootBridgeHandle == RootBridgeInstance->Handle) {
      while (*Temp == ACPI_ADDRESS_SPACE_DESCRIPTOR) {
        ptr = (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp;

        ///
        /// Check address range alignment
        ///
        if (ptr->AddrRangeMax != (Power2MaxMemory (ptr->AddrRangeMax + 1) - 1)) {
          return EFI_INVALID_PARAMETER;
        }

        switch (ptr->ResType) {
          case ACPI_ADDRESS_SPACE_TYPE_MEM:
            ///
            /// check the memory resource request is supported by PCI root bridge
            ///
            if (((RootBridgeInstance->RootBridgeAttrib & EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM) == EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM) && (ptr->SpecificFlag == 0x06)) {
              return EFI_INVALID_PARAMETER;
            }

            AddrLen   = (UINT64) ptr->AddrLen;
            Alignment = (UINT64) ptr->AddrRangeMax;
            if (ptr->AddrSpaceGranularity == 32) {
              if ((ptr->SpecificFlag & 0x06) == 0x06) {
                ///
                /// Apply from GCD
                ///
                RootBridgeInstance->ResAllocNode[TypePMem32].Length     = AddrLen;
                RootBridgeInstance->ResAllocNode[TypePMem32].Alignment  = Alignment;
                RootBridgeInstance->ResAllocNode[TypePMem32].Status     = ResRequested;
                HostBridgeInstance->ResourceSubmited                    = TRUE;

              } else {
                RootBridgeInstance->ResAllocNode[TypeMem32].Length    = AddrLen;
                RootBridgeInstance->ResAllocNode[TypeMem32].Alignment = Alignment;
                RootBridgeInstance->ResAllocNode[TypeMem32].Status    = ResRequested;
                HostBridgeInstance->ResourceSubmited                  = TRUE;
              }
            }

            if (ptr->AddrSpaceGranularity == 64) {
              if ((RootBridgeInstance->RootBridgeAttrib & EFI_PCI_HOST_BRIDGE_MEM64_DECODE) == 0) {
                return EFI_INVALID_PARAMETER;
              } else {
                if ((ptr->SpecificFlag & 0x06) == 0x06) {
                  RootBridgeInstance->ResAllocNode[TypePMem64].Length     = AddrLen;
                  RootBridgeInstance->ResAllocNode[TypePMem64].Alignment  = Alignment;
                  RootBridgeInstance->ResAllocNode[TypePMem64].Status     = ResSubmitted;
                  HostBridgeInstance->ResourceSubmited                    = TRUE;

                } else {
                  RootBridgeInstance->ResAllocNode[TypeMem64].Length    = AddrLen;
                  RootBridgeInstance->ResAllocNode[TypeMem64].Alignment = Alignment;
                  RootBridgeInstance->ResAllocNode[TypeMem64].Status    = ResSubmitted;
                  HostBridgeInstance->ResourceSubmited                  = TRUE;
                }
              }
            }
            break;

          case ACPI_ADDRESS_SPACE_TYPE_IO:
            AddrLen   = (UINT64) ptr->AddrLen;
            Alignment = (UINT64) ptr->AddrRangeMax;
            RootBridgeInstance->ResAllocNode[TypeIo].Length     = AddrLen;
            RootBridgeInstance->ResAllocNode[TypeIo].Alignment  = Alignment;
            RootBridgeInstance->ResAllocNode[TypeIo].Status     = ResRequested;
            HostBridgeInstance->ResourceSubmited                = TRUE;
            break;

          default:
            break;
        }

        Temp += sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR);
      }

      return EFI_SUCCESS;
    }

    List = List->ForwardLink;
  }

  return EFI_INVALID_PARAMETER;
}

/**
  This function returns the proposed resource settings for the specified
  PCI Root Bridge

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance
  @param[in] RootBridgeHandle  - The PCI Root Bridge handle
  @param[in] Configuration     - The pointer to the pointer to the PCI I/O
                      and memory resource descriptor

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_OUT_OF_RESOURCES   -  Not enough pool to be allocated.
  @retval EFI_INVALID_PARAMETER  -  RootBridgeHandle is not a valid handle.
**/
EFI_STATUS
EFIAPI
GetProposedResources (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN EFI_HANDLE                                       RootBridgeHandle,
  OUT VOID                                            **Configuration
  )
{
  LIST_ENTRY                        *List;
  PCI_HOST_BRIDGE_INSTANCE          *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE          *RootBridgeInstance;
  UINTN                             Index;
  UINTN                             Number;
  VOID                              *Buffer;
  UINT8                             *Temp;
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *ptr;
  UINT64                            ResStatus;

  Buffer  = NULL;
  Number  = 0;

  ///
  /// Get the Host Bridge Instance from the resource allocation protocol
  ///
  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;

  ///
  /// Enumerate the root bridges in this host bridge
  ///
  while (List != &HostBridgeInstance->Head) {
    RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (RootBridgeHandle == RootBridgeInstance->Handle) {
      for (Index = 0; Index < TypeBus; Index++) {
        if (RootBridgeInstance->ResAllocNode[Index].Status != ResNone) {
          Number++;
        }
      }

      if (Number > 0) {
        Buffer = AllocatePool (Number * sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) + sizeof (EFI_ACPI_END_TAG_DESCRIPTOR));
        if (Buffer == NULL) {
          return EFI_OUT_OF_RESOURCES;
        }

        ZeroMem (Buffer, sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) * Number + sizeof (EFI_ACPI_END_TAG_DESCRIPTOR));

        Temp = Buffer;
        for (Index = 0; Index < TypeBus; Index++) {
          if (RootBridgeInstance->ResAllocNode[Index].Status != ResNone) {
            ptr       = (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp;
            ResStatus = RootBridgeInstance->ResAllocNode[Index].Status;
            switch (Index) {
              case TypeIo:
                ///
                /// Io
                ///
                ptr->Desc                   = 0x8A;
                ptr->Len                    = 0x2B;
                ptr->ResType                = 1;
                ptr->GenFlag                = 0;
                ptr->SpecificFlag           = 0;
                ptr->AddrRangeMin           = RootBridgeInstance->ResAllocNode[Index].Base;
                ptr->AddrRangeMax           = 0;
                ptr->AddrTranslationOffset  = (ResStatus == ResAllocated) ? EFI_RESOURCE_SATISFIED : EFI_RESOURCE_LESS;
                ptr->AddrLen                = RootBridgeInstance->ResAllocNode[Index].Length;
                break;

              case TypeMem32:
                ///
                /// Memory 32
                ///
                ptr->Desc                   = 0x8A;
                ptr->Len                    = 0x2B;
                ptr->ResType                = 0;
                ptr->GenFlag                = 0;
                ptr->SpecificFlag           = 0;
                ptr->AddrSpaceGranularity   = 32;
                ptr->AddrRangeMin           = RootBridgeInstance->ResAllocNode[Index].Base;
                ptr->AddrRangeMax           = 0;
                ptr->AddrTranslationOffset  = (ResStatus == ResAllocated) ? EFI_RESOURCE_SATISFIED : EFI_RESOURCE_LESS;
                ptr->AddrLen                = RootBridgeInstance->ResAllocNode[Index].Length;
                break;

              case TypePMem32:
                ///
                /// Prefetch memory 32
                ///
                ptr->Desc                   = 0x8A;
                ptr->Len                    = 0x2B;
                ptr->ResType                = 0;
                ptr->GenFlag                = 0;
                ptr->SpecificFlag           = 6;
                ptr->AddrSpaceGranularity   = 32;
                ptr->AddrRangeMin           = 0;
                ptr->AddrRangeMax           = 0;
                ptr->AddrTranslationOffset  = (ResStatus == ResAllocated) ? EFI_RESOURCE_SATISFIED : EFI_RESOURCE_LESS;
                ptr->AddrLen                = RootBridgeInstance->ResAllocNode[Index].Length;
                break;

              case TypeMem64:
                ///
                /// Memory 64
                ///
                ptr->Desc                   = 0x8A;
                ptr->Len                    = 0x2B;
                ptr->ResType                = 0;
                ptr->GenFlag                = 0;
                ptr->SpecificFlag           = 0;
                ptr->AddrSpaceGranularity   = 64;
                ptr->AddrRangeMin           = RootBridgeInstance->ResAllocNode[Index].Base;
                ptr->AddrRangeMax           = 0;
                ptr->AddrTranslationOffset  = (ResStatus == ResAllocated) ? EFI_RESOURCE_SATISFIED : EFI_RESOURCE_LESS;
                ptr->AddrLen                = RootBridgeInstance->ResAllocNode[Index].Length;
                break;

              case TypePMem64:
                ///
                /// Prefetch memory 64
                ///
                ptr->Desc                   = 0x8A;
                ptr->Len                    = 0x2B;
                ptr->ResType                = 0;
                ptr->GenFlag                = 0;
                ptr->SpecificFlag           = 6;
                ptr->AddrSpaceGranularity   = 64;
                ptr->AddrRangeMin           = 0;
                ptr->AddrRangeMax           = 0;
                ptr->AddrTranslationOffset  = (ResStatus == ResAllocated) ? EFI_RESOURCE_SATISFIED : EFI_RESOURCE_LESS;
                ptr->AddrLen                = RootBridgeInstance->ResAllocNode[Index].Length;
                break;
            }

            Temp += sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR);
          }
        }

        ((EFI_ACPI_END_TAG_DESCRIPTOR *) Temp)->Desc      = 0x79;
        ((EFI_ACPI_END_TAG_DESCRIPTOR *) Temp)->Checksum  = 0x0;
        *Configuration = Buffer;
      }

      return EFI_SUCCESS;
    }

    List = List->ForwardLink;
  }

  return EFI_INVALID_PARAMETER;
}

/**
  This function is called for all the PCI controllers that the PCI
  bus driver finds. Can be used to Preprogram the controller.

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance
  @param[in] RootBridgeHandle  - The PCI Root Bridge handle
  @param[in] PciAddress        - Address of the controller on the PCI bus
  @param[in] Phase             - The Phase during resource allocation

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_INVALID_PARAMETER  -  RootBridgeHandle is not a valid handle.
**/
EFI_STATUS
EFIAPI
PreprocessController (
  IN  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL          *This,
  IN  EFI_HANDLE                                                RootBridgeHandle,
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_PCI_ADDRESS               PciAddress,
  IN  EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE              Phase
  )
{
  PCI_HOST_BRIDGE_INSTANCE  *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE  *RootBridgeInstance;
  LIST_ENTRY                *List;

  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;

  ///
  /// Enumerate the root bridges in this host bridge
  ///
  while (List != &HostBridgeInstance->Head) {
    RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (RootBridgeHandle == RootBridgeInstance->Handle) {
      return EFI_SUCCESS;
    }

    List = List->ForwardLink;
  }

  return EFI_INVALID_PARAMETER;
}

/**
  Calculate max memory of power 2

  @param[in] MemoryLength  -  Input memory length.

  @retval Returned Maximum length.
**/
UINT64
Power2MaxMemory (
  IN UINT64                     MemoryLength
  )
{
  UINT64  Result;

  if (RShiftU64 (MemoryLength, 32)) {
    Result = LShiftU64 ((UINT64) GetPowerOfTwo64 (RShiftU64 (MemoryLength, 32)), 32);
  } else {
    Result = (UINT64) GetPowerOfTwo64 (MemoryLength);
  }

  return Result;
}
