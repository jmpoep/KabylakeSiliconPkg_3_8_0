/** @file
  The driver for the host to pci bridge (root bridge).

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
#ifndef _PCI_ROOT_BRIDGE_H_
#define _PCI_ROOT_BRIDGE_H_

#include <Protocol/PciRootBridgeIo.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/PciLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Uefi/UefiSpec.h>
#include <Protocol/Metronome.h>
#include <Protocol/CpuIo2.h>
#include <Library/S3BootScriptLib.h>
#include <Library/MmPciLib.h>
#include <IndustryStandard/Acpi.h>
#include <SaAccess.h>
#include <Library/UefiLib.h>
#include <Library/TimerLib.h>
///
/// Define resource status constant
///
#define EFI_RESOURCE_NONEXISTENT  0xFFFFFFFFFFFFFFFF
#define EFI_RESOURCE_LESS         0xFFFFFFFFFFFFFFFE
#ifndef EFI_RESOURCE_SATISFIED
#define EFI_RESOURCE_SATISFIED    0x0000000000000000      // redefined in PciHostBridgeResourceAllocation.h
#endif

///
/// Driver Instance Data Prototypes
///
typedef struct {
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION Operation;
  UINTN                                     NumberOfBytes;
  UINTN                                     NumberOfPages;
  EFI_PHYSICAL_ADDRESS                      HostAddress;
  EFI_PHYSICAL_ADDRESS                      MappedHostAddress;
} MAP_INFO;

typedef struct {
  ACPI_HID_DEVICE_PATH      AcpiDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  EndDevicePath;
} EFI_PCI_ROOT_BRIDGE_DEVICE_PATH;

typedef struct {
  UINT64  BusBase;
  UINT64  BusLimit;
  UINT64  MemBase;
  UINT64  MemLimit;
  UINT64  IoBase;
  UINT64  IoLimit;
} PCI_ROOT_BRIDGE_RESOURCE_APERTURE;

typedef enum {
  TypeIo    = 0,
  TypeMem32,
  TypePMem32,
  TypeMem64,
  TypePMem64,
  TypeBus,
  TypeMax
} PCI_RESOURCE_TYPE;

typedef enum {
  ResNone     = 0,
  ResSubmitted,
  ResRequested,
  ResAllocated,
  ResStatusMax
} RES_STATUS;

typedef struct {
  PCI_RESOURCE_TYPE Type;
  UINT64            Base;
  UINT64            Length;
  UINT64            Alignment;
  RES_STATUS        Status;
} PCI_RES_NODE;

#define PCI_ROOT_BRIDGE_SIGNATURE SIGNATURE_32 ('e', '2', 'p', 'b')

typedef struct {
  UINT32                          Signature;
  LIST_ENTRY                      Link;
  EFI_HANDLE                      Handle;
  UINT64                          RootBridgeAttrib;
  UINT64                          Attributes;
  UINT64                          Supports;

  ///
  /// Specific for this memory controller: Bus, I/O, Mem
  ///
  PCI_RES_NODE                    ResAllocNode[TypeMax];

  ///
  /// Addressing for Memory and I/O and Bus arrange
  ///
  UINT64                          BusBase;
  UINT64                          MemBase;
  UINT64                          IoBase;
  UINT64                          BusLimit;
  UINT64                          MemLimit;
  UINT64                          IoLimit;
  EFI_LOCK                        PciLock;
  UINTN                           PciAddress;
  UINTN                           PciData;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL Io;
} PCI_ROOT_BRIDGE_INSTANCE;

///
/// Driver Instance Data Macros
///
#define DRIVER_INSTANCE_FROM_PCI_ROOT_BRIDGE_IO_THIS(a) CR (a, PCI_ROOT_BRIDGE_INSTANCE, Io, PCI_ROOT_BRIDGE_SIGNATURE)

#define DRIVER_INSTANCE_FROM_LIST_ENTRY(a)              CR (a, PCI_ROOT_BRIDGE_INSTANCE, Link, PCI_ROOT_BRIDGE_SIGNATURE)

/**
  Construct the Pci Root Bridge Io protocol

  @param[in] Protocol         - Point to protocol instance
  @param[in] HostBridgeHandle - Handle of host bridge
  @param[in] Attri            - Attribute of host bridge
  @param[in] ResAperture      - ResourceAperture for host bridge

  @retval EFI_SUCCESS     - Success to initialize the Pci Root Bridge.
**/
EFI_STATUS
RootBridgeConstructor (
  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL    *Protocol,
  IN EFI_HANDLE                         HostBridgeHandle,
  IN UINT64                             Attri,
  IN PCI_ROOT_BRIDGE_RESOURCE_APERTURE  *ResAperture
  );

#endif
