/** @file
  PCH SPI PEI Library implements the SPI Host Controller Compatibility Interface.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2015 Intel Corporation.

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
#include "PchSpi.h"

/**
  Hide SPI controller before OS avoid BAR0 changed.
**/
VOID
HideSpiController (
  VOID
  )
{
  UINTN                                 PchSpiBase;

  PchSpiBase = MmPciBase (
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_SPI,
                 PCI_FUNCTION_NUMBER_PCH_SPI
                 );

  ///
  /// BWG 3.5.1, For SKL PCH-LP/H B0 stepping and above, the SPI configuration space
  /// is to be hidden from OS by setting the SPI PCI offset DCh [9].
  ///
  MmioAndThenOr8 (
    PchSpiBase + R_PCH_SPI_BC + 1,
    (UINT8) ~(B_PCH_SPI_BC_SYNC_SS >> 8),
    (B_PCH_SPI_BC_OSFH >> 8)
    );
}

/**
  Configure SPI device after memory.

  @param[in] SiPolicyPpi  The SI Policy PPI instance
**/
VOID
ConfigureSpiAfterMem (
  IN  SI_POLICY_PPI                    *SiPolicyPpi
  )
{
  EFI_STATUS                            Status;
  PCH_SPI_CONFIG                         *SpiConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSpiConfigGuid, (VOID *) &SpiConfig);
  ASSERT_EFI_ERROR (Status);

  if (SpiConfig->ShowSpiController == FALSE) {
    //
    // Hide SPI controller before OS avoid BAR0 changed.
    //
    HideSpiController ();
  }
}

/**
  PCI Enumeratuion is not done till later in DXE
  Initlialize SPI BAR0 to a default value till enumeration is done
  also enable memory space decoding for SPI

**/
VOID
InitSpiBar0 (
  VOID
  )
{
  UINTN                                 PchSpiBase;
  PchSpiBase = MmPciBase (
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_SPI,
                 PCI_FUNCTION_NUMBER_PCH_SPI
                 );
  MmioWrite32 (PchSpiBase + R_PCH_SPI_BAR0, PCH_SPI_BASE_ADDRESS);
  MmioOr32 (PchSpiBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
}

/**
  Installs PCH SPI PPI

  @retval EFI_SUCCESS             PCH SPI PPI is installed successfully
  @retval EFI_OUT_OF_RESOURCES    Can't allocate pool
**/
EFI_STATUS
EFIAPI
InstallPchSpi (
  VOID
  )
{
  EFI_STATUS        Status;
  PEI_SPI_INSTANCE  *PeiSpiInstance;
  SPI_INSTANCE      *SpiInstance;

  DEBUG ((DEBUG_INFO, "InstallPchSpi() Start\n"));

  //
  // PCI Enumeratuion is not done till later in DXE
  // Initlialize SPI BAR0 to a default value till enumeration is done
  // also enable memory space decoding for SPI
  //
  InitSpiBar0 ();

  PeiSpiInstance = (PEI_SPI_INSTANCE *) AllocateZeroPool (sizeof (PEI_SPI_INSTANCE));
  if (NULL == PeiSpiInstance) {
    return EFI_OUT_OF_RESOURCES;
  }

  SpiInstance = &(PeiSpiInstance->SpiInstance);
  SpiProtocolConstructor (SpiInstance);

  PeiSpiInstance->PpiDescriptor.Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  PeiSpiInstance->PpiDescriptor.Guid  = &gPchSpiPpiGuid;
  PeiSpiInstance->PpiDescriptor.Ppi   = &(SpiInstance->SpiProtocol);

  ///
  /// Install the SPI PPI
  ///
  Status = PeiServicesInstallPpi (&PeiSpiInstance->PpiDescriptor);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "SPI PPI Installed\n"));

  DEBUG ((DEBUG_INFO, "InstallPchSpi() End\n"));

  return Status;
}

/**
  Acquire pch spi mmio address.

  @param[in] SpiInstance          Pointer to SpiInstance to initialize

  @retval PchSpiBar0              return SPI MMIO address
**/
UINTN
AcquireSpiBar0 (
  IN  SPI_INSTANCE                *SpiInstance
  )
{
  return MmioRead32 (SpiInstance->PchSpiBase + R_PCH_SPI_BAR0) & ~(B_PCH_SPI_BAR0_MASK);
}

/**
  Release pch spi mmio address. Do nothing.

  @param[in] SpiInstance          Pointer to SpiInstance to initialize

  @retval None
**/
VOID
ReleaseSpiBar0 (
  IN  SPI_INSTANCE                *SpiInstance
  )
{
}

/**
  This function is a hook for Spi to disable BIOS Write Protect

  @retval EFI_SUCCESS             The protocol instance was properly initialized
  @retval EFI_ACCESS_DENIED       The BIOS Region can only be updated in SMM phase

**/
EFI_STATUS
EFIAPI
DisableBiosWriteProtect (
  VOID
  )
{
  UINTN             SpiBaseAddress;

  SpiBaseAddress = MmPciBase (
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_SPI,
                     PCI_FUNCTION_NUMBER_PCH_SPI
                     );
  if ((MmioRead8 (SpiBaseAddress + R_PCH_SPI_BC) & B_PCH_SPI_BC_EISS) != 0) {
    return EFI_ACCESS_DENIED;
  }
  ///
  /// Enable the access to the BIOS space for both read and write cycles
  ///
  MmioOr8 (
    SpiBaseAddress + R_PCH_SPI_BC,
    B_PCH_SPI_BC_WPD
    );

  return EFI_SUCCESS;
}

/**
  This function is a hook for Spi to enable BIOS Write Protect


**/
VOID
EFIAPI
EnableBiosWriteProtect (
  VOID
  )
{
  UINTN                           SpiBaseAddress;

  SpiBaseAddress = MmPciBase (
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_SPI,
                     PCI_FUNCTION_NUMBER_PCH_SPI
                     );
  ///
  /// Disable the access to the BIOS space for write cycles
  ///
  MmioAnd8 (
    SpiBaseAddress + R_PCH_SPI_BC,
    (UINT8) (~B_PCH_SPI_BC_WPD)
    );
}