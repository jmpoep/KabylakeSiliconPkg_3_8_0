/** @file
  The Header file of the Pci Host Bridge Driver

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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
#ifndef _PCI_HOST_BRIDGE_H_
#define _PCI_HOST_BRIDGE_H_

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/DevicePathLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/PciHostBridgeResourceAllocation.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>


///
/// Hard code the host bridge number in the platform.
/// In this chipset, there is only one host bridge.
///
#define HOST_BRIDGE_NUMBER        1


#define PCI_HOST_BRIDGE_SIGNATURE SIGNATURE_32 ('e', 'h', 's', 't')
typedef struct {
  UINTN                                             Signature;
  EFI_HANDLE                                        HostBridgeHandle;
  UINTN                                             RootBridgeNumber;
  LIST_ENTRY                                        Head;
  BOOLEAN                                           ResourceSubmited;
  BOOLEAN                                           CanRestarted;
  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL  ResAlloc;
} PCI_HOST_BRIDGE_INSTANCE;

#define INSTANCE_FROM_RESOURCE_ALLOCATION_THIS(a) CR (a, PCI_HOST_BRIDGE_INSTANCE, ResAlloc, PCI_HOST_BRIDGE_SIGNATURE)

///
///  HostBridge Resource Allocation interface
///
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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  IN  struct _EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL  *This,
  IN  EFI_HANDLE                                                RootBridgeHandle,
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_PCI_ADDRESS               PciAddress,
  IN  EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE              Phase
  );

/**
  Calculate max memory of power 2

  @param[in] MemoryLength  -  Input memory length.

  @retval Returned Maximum length.
**/
UINT64
Power2MaxMemory (
  IN UINT64                     MemoryLength
  );

/**
  <b>Entry point of PCI Host Bridge driver</b>
  - <b>Introduction</b> \n
    This module publishes the PCI Host Bridge Resource Allocation Protocol.  The PCI Host Bridge Resource Allocation Protocol is used by a PCI bus driver to program a PCI host bridge.  The registers inside a PCI host bridge that control configuration of PCI root buses are not governed by the PCI specification and vary from chipset to chipset.  The PCI Host Bridge Resource Allocation Protocol implementation is therefore specific to a particular chipset.  Please refer to the PCI Host Bridge Resource Allocation Protocol Specification for more information.
    This driver is likely required by all systems supporting PCI and Intel Broadwell.

  - @pre
    - The PCI Host Bridge DXE Driver should be executed after PCI Express root complex initialization is done.
    - EFI_CPU_IO_PROTOCOL: Documented in CPU I/O Protocol Specification, available at the URL: http://www.intel.com/technology/framework/spec.htm
    - EFI_METRONOME_ARCH_PROTOCOL: Documented in Driver Execution Environment Core Interface Specification (DxeCis_0-91.pdf), available at the URL: http://www.intel.com/technology/framework/spec.htm

  - @result
    - Publishes the EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL: Documented in the PCI Host Bridge Resource Allocation Protocol Specification, available at the URL: http://www.intel.com/technology/framework/spec.htm
    - Publishes the EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL: Documented in the Unified Extensible Firmware Interface Specification, version 2.0, available at the URL: http://www.uefi.org/specs/

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
  );
#endif
