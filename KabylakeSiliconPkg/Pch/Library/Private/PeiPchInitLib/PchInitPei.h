/** @file
  Header file for the PCH Init PEIM

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2017 Intel Corporation.

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
#ifndef _PCH_INIT_PEI_H_
#define _PCH_INIT_PEI_H_

#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/TimerLib.h>
#include <Library/ConfigBlockLib.h>
#include <PchAccess.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PchGbeLib.h>
#include <Library/PchEspiLib.h>
#include <Library/PchHsioLib.h>
#include <Library/PchPcieRpLib.h>
#include <Library/PchP2sbLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchSbiAccessLib.h>
#include <Library/PchInfoLib.h>
#include <Library/TraceHubInitLib.h>
#include <Library/MmPciLib.h>
#include <Private/Library/PchPciExpressHelpersLib.h>
#include <Private/Library/PchInitCommonLib.h>
#include <Private/SiConfigHob.h>
#include <Ppi/SiPolicy.h>
#include <Ppi/PchReset.h>
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Private/Library/GpioPrivateLib.h>
#include <IndustryStandard/Pci30.h>
#include <MeChipset.h>
#include "PchUsb.h"
#include <Library/PchPsfLib.h>
#include <Private/Library/PchPsfPrivateLib.h>
#include <PchResetPlatformSpecific.h>

/**
  Hide rootports disabled by policy. This needs to be done in premem,
  because graphics init from SystemAgent code depends on those ports
  being already hidden

  @param[in] PcieRpPreMemConfig   Platform policy
**/
VOID
EarlyPcieRpDisabling (
  IN PCH_PCIE_RP_PREMEM_CONFIG *PcieRpPreMemConfig
  );

/**
  Creates a PcieStorageInfoHob that is later used by BIOS setup and remapping code

  @param[in] SiPolicyPpi      SiPolicyInstance
  @param[in] TempPciBusMin    Temporary Min Pci Bus Number
  @param[in] TempPciBusMax    Temporary Max Pci Bus Number
**/
VOID
CreateStorageInfoHob (
  IN CONST SI_POLICY_PPI    *SiPolicyPpi,
  IN UINT8                  TempPciBusMin,
  IN UINT8                  TempPciBusMax
  );

/**
  This function assigns a CLKREQ# signal to PCI Express ports and GbE.
  Each enabled ports must have distinct CLKREQ# pin assigned before power management features are enabled.

  Assignment is based on the platform policy with assumption that unused ports will be disabled
  before enabling power management on remaining ports.

  @param[in] SiPolicyPpi    The SI Policy PPI instance
**/
VOID
PchConfigureClkreqMapping (
  IN  SI_POLICY_PPI  *SiPolicyPpi
  );

#ifndef MINTREE_FLAG
/**
  Perform PCH SKU detection to check if the RST PCIe Storage Remapping feature is supported
  Prior to any PCIe device enumeration, initial the RST PCIe Storage "Cycle Router Enable (CRE)" bit to 1
  If the CRE bit value after the write is 1, it indicates the bit is RW,and is enabled by fuse
  else, it indicates the bit is RO only and is disabled by fuse
  The value after the write is stored in RST PCIe Storage Cycle Router Global Control regiser, and then CRE bit is cleared

  @retval None
**/
VOID
PchRstPcieStorageCreEarlyInit (
  VOID
  );
#endif //MINTREE_FLAG

/**
  Configures PCH Sata Controller for PCH-LP

  @param[in] SataConfig                     The PCH Policy for SATA configuration
  @param[in] RstPcieStorageRemapEnabled     A Boolean to indicate if RST PCIe Storage Remapping is enabled
  @param[in] AhciBarAddress                 The Base Address for AHCI BAR

  @retval EFI_SUCCESS                       The function completed successfully
**/
EFI_STATUS
EarlyConfigurePchLpSata (
  IN  CONST PCH_SATA_CONFIG                   *SataConfig,
  IN BOOLEAN                                  RstPcieStorageRemapEnabled,
  IN UINT32                                   AhciBarAddress
  );

/**
  Additional SATA configuration

  @param[in] SataConfig                     The PCH Policy for SATA configuration
  @param[in] AhciBarAddress                 The Base Address for AHCI BAR
**/
VOID
ConfigurePchLpSata (
  IN CONST PCH_SATA_CONFIG                    *SataConfig,
  IN UINT32                                   AhciBarAddress
  );

/**
  Configures Sata Controller for PCH-H

  @param[in] SataConfig                     The PCH Policy for SATA configuration
  @param[in] RstPcieStorageRemapEnabled     A Boolean to indicate if RST PCIe Storage Remapping is enabled
  @param[in] AhciBarAddress                 The Base Address for AHCI BAR

  @retval EFI_SUCCESS                       The function completed successfully
**/
EFI_STATUS
EarlyConfigurePchHSata (
  IN  CONST PCH_SATA_CONFIG                   *SataConfig,
  IN BOOLEAN                                  RstPcieStorageRemapEnabled,
  IN UINT32                                   AhciBarAddress
  );

/**
  Additional Sata configuration for PCH-H

  @param[in]      SataConfig                The PCH Policy for SATA configuration
  @param[in] AhciBarAddress                 The Base Address for AHCI BAR
**/
VOID
ConfigurePchHSata (
  IN CONST PCH_SATA_CONFIG                    *SataConfig,
  IN UINT32                                   AhciBarAddress
  );

/**
  Perform Root Port Initialization.

  @param[in]  PortIndex               The root port to be initialized (zero based)
  @param[in]  SiPolicy                The SI Policy PPI
  @param[in] TempPciBusMin            The temporary minimum Bus number for root port initialization
  @param[in] TempPciBusMax            The temporary maximum Bus number for root port initialization

  @retval EFI_SUCCESS             Device found. The root port must be enabled.
  @retval EFI_NOT_FOUND           No device is found on the root port. It may be disabled.
  @exception EFI_UNSUPPORTED      Unsupported operation.
**/
EFI_STATUS
PchInitSingleRootPort (
  IN  UINT8                                     PortIndex,
  IN  CONST SI_POLICY_PPI                       *SiPolicy,
  IN  UINT8                                     TempPciBusMin,
  IN  UINT8                                     TempPciBusMax,
  OUT BOOLEAN                                   *Gen3DeviceFound
  );

/**
  Perform Initialization of the Downstream Root Ports.

  @param[in] SiPolicy             The SI Policy PPI
  @param[in] TempPciBusMin        The temporary minimum Bus number for root port initialization
  @param[in] TempPciBusMax        The temporary maximum Bus number for root port initialization

  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
PchInitRootPorts (
  IN CONST SI_POLICY_PPI     *SiPolicy,
  IN UINT8                   TempPciBusMin,
  IN UINT8                   TempPciBusMax
  );

/**
  This is the function to enable the clock gating for PCI Express ports.

  @param[in] BusNumber            The Bus Number of the PCH device
  @param[in] PortIndex            The root port number (zero based)

  @retval EFI_SUCCESS             Successfully completed.
**/
EFI_STATUS
PcieEnableClockGating (
  IN  UINT8                                PortIndex
  );

/**
  This is the function to do IOSF Port Configuration and Grant Count Programming.

  @param[in] RootComplexBar       Root complex base address
  @param[in] RPBase               Root Port Base Address
  @param[in] SiPolicy             SI Policy PPI

  @retval None
**/
VOID
SetPcieIosfPortAndGrantCount (
  IN UINTN             RPBase,
  IN SI_POLICY_PPI*    SiPolicy
  );

/**
  This function performs basic initialization for TraceHub in PEI phase.

  @param[in] SiPolicyPpi The SI Policy PPI instance

**/
VOID
TraceHubPolicyInit (
  IN  SI_POLICY_PPI   *SiPolicyPpi
  );

/**
  Program Pch devices Subsystem Vendor Identifier (SVID) and Subsystem Identifier (SID).

  @param[in] SiPolicy    The SI Policy PPI instance

  @retval EFI_SUCCESS     The function completed successfully
**/
EFI_STATUS
ProgramSvidSid (
  IN  SI_POLICY_PPI     *SiPolicy
  );

/**
  Configures PCH USB device (xDCI)

  @param[in]  SiPolicy          The SI Policy PPI instance
  @param[in]  TempMemBaseAddr   Temporary Memory Base Address for PCI
                                devices to be used to initialize MMIO
                                registers.

  @retval EFI_SUCCESS           The function completed successfully
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver
**/
EFI_STATUS
ConfigureXdci (
  IN  SI_POLICY_PPI   *SiPolicy,
  IN  UINT32           TempMemBaseAddr
  );

/**
  Configures PCH eSPI

  @param[in]  PCH_ESPI_CONFIG   The eSPI config block
**/
VOID
ConfigureEspi (
  IN  PCH_ESPI_CONFIG     *EspiConfig
  );

/**
  This function performs TraceHub PCH initialization stage on end of PEI phase, when DRAM is available.

  @param[in] SiPreMemPolicy        The SI PreMem Policy PPI instance

  @retval EFI_OUT_OF_RESOURCES      Requested amount of memory could not be allocated.
  @retval EFI_NOT_FOUND             The Cache PPI descriptor is not found in the database.
  @retval EFI_LOAD_ERROR            No empty MTRRs to use.
  @retval EFI_INVALID_PARAMETER     The input parameter to SetCache is not valid.
**/
EFI_STATUS
PchTraceHubOnEndOfPei (
  IN  SI_PREMEM_POLICY_PPI         *SiPreMemPolicy
  );

/**
  This function completes power gating management for TraceHub and ensures locking of HSWPGCR1 register.
**/
VOID
TraceHubManagePowerGateControl (
  VOID
  );

/**
  This function configures DMI and OP-DMI.

  @param[in] SiPolicyPpi The SI Policy PPI instance

  @retval None
**/
VOID
PchDmiAndOpDmiInit (
  IN  SI_POLICY_PPI  *SiPolicyPpi
  );

/**
  Initialize IOAPIC according to IoApicConfig policy of the PCH
  Policy PPI

  @param[in] SiPolicyPpi         The SI Policy PPI instance

  @retval EFI_SUCCESS             Succeeds.
  @retval EFI_DEVICE_ERROR        Device error, aborts abnormally.
**/
EFI_STATUS
PchIoApicInit (
  IN  SI_POLICY_PPI     *SiPolicyPpi
  );

/**
  Configures PCH devices interrupts

  @param[in] SiPolicy          Policy

  @retval Status
**/
EFI_STATUS
PchConfigureInterrupts (
  IN  SI_POLICY_PPI           *SiPolicy
  );

/**
  Initialize CIO2 according to Cio2Config policy of the SI Policy PPI

  @param[in] SiPolicy           The SI Policy PPI instance

  @retval EFI_SUCCESS           Succeeds.
**/
EFI_STATUS
PchCio2Init (
  IN  SI_POLICY_PPI           *SiPolicy
  );

/**
   Finalize CIO2 configuration: power off CSI2 HC core logic and lock registers

   @param[in] SiPolicy            The SI Policy PPI instance
   @param[in] TempMemBaseAddr     Temporary Memory Base Address for PCI
                                  devices to be used to initialize MMIO
                                  registers.

   @retval EFI_SUCCESS                  Succeeds.
   @retval EFI_DEVICE_ERROR             Device error, aborts abnormally.
**/
EFI_STATUS
PchCio2FinalizeDeviceConfiguration (
  IN  SI_POLICY_PPI      *SiPolicy,
  IN  UINT32             TempMemBaseAddr
  );

/**
  Initialize LAN device.

  Global reset may be perfomed due to static power gating requirements.

  @param[in] SiPolicy             The SI Policy PPI instance
  @param[in] TempMemBaseAddr      Temporary Memory Base Address for PCI
                                  devices to be used to initialize MMIO
                                  registers.
**/
VOID
PchConfigureLan (
  IN  SI_POLICY_PPI      *SiPolicy,
  IN  UINT32             TempMemBaseAddr
  );

/**
  Initialize the Intel High Definition Audio Controller and Codec(s) present in the system.
  For each codec, a predefined codec verb table should be programmed.
  The list contains 32-bit verbs to be sent to the corresponding codec.
  If it is not programmed, the codec uses the default verb table, which may or may not
  correspond to the platform jack information.

  @param[in] SiPolicy             Policy
  @param[in] TempMemBaseAddr      Temporary Memory Base Address for PCI
                                  devices to be used to initialize MMIO
                                  registers.

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Provided VerbTableData is null
**/
EFI_STATUS
PchHdAudioInit (
  IN  SI_POLICY_PPI     *SiPolicy,
  IN  UINT32             TempMemBaseAddr
  );

/**
  Perform Thermal Management Support initialization

  @param[in] SiPolicy             The SI Policy PPI instance
  @param[in] TempMemBaseAddr      Temporary Memory Base Address for PCI
                                  devices to be used to initialize MMIO
                                  registers.

  @retval EFI_SUCCESS             Succeeds.
  @retval EFI_DEVICE_ERROR        Device error, aborts abnormally.
**/
EFI_STATUS
PchThermalInit (
  IN  SI_POLICY_PPI     *SiPolicy,
  IN  UINT32             TempMemBaseAddr
  );

/**
  Init Memory Throttling.

  @param[in] SiPolicyPpi               The SI Policy PPI instance
**/
VOID
PchMemoryThrottlingInit (
  IN  SI_POLICY_PPI                    *SiPolicyPpi
  );

/**
  Initializes SerialIo controllers
  @param[in] SiPolicy        The SI Policy PPI instance
**/
VOID
ConfigureSerialIoPei (
  IN SI_POLICY_PPI           *SiPolicy
  );

/**
  Prepares SerialIo controllers for OS boot
  @param[in] SiPolicy        The SI Policy PPI instance
**/
VOID
ConfigureSerialIoAtS3Resume (
  IN SI_POLICY_PPI           *SiPolicy
  );

/**
  Initializes GPIO pins assigned to SerialIo
  @param[in] SiPolicy        The SI Policy PPI instance
**/
VOID
SerialIoGpioInit (
  IN SI_POLICY_PPI           *SiPolicy
  );

/**
  Configures Storage and Communication Subsystem (SCS)
  Controllers before Pci Enum

  @param[in] SiPolicy                 The SI Policy PPI instance
  @param[in] TempMemBaseAddr          Temporary Memory Base Address for PCI
                                      devices to be used to initialize MMIO
                                      registers.

  @retval EFI_SUCCESS
**/
EFI_STATUS
PchScsInit (
  IN SI_POLICY_PPI    *SiPolicy,
  IN UINT32           TempMemBaseAddr
  );

/**
  Initialize Integrated Sensor Hub (ISH)

  @param[in] SiPolicy       The SI Policy PPI instance

  @retval EFI_SUCCESS       Initialized successfully
  @retval EFI_UNSUPPORTED   Controller fuse disabled
**/
EFI_STATUS
PchIshInit (
  IN  SI_POLICY_PPI   *SiPolicy
  );

/**
  Perform power management initialization

  @param[in] SiPolicy           The SI Policy PPI instance

  @retval EFI_SUCCESS           Succeeds.
**/
EFI_STATUS
PchPmInit (
  IN  SI_POLICY_PPI           *SiPolicy
  );

/**
  The function is used to detemine if a ChipsetInitSync with ME is required and syncs with ME if required.

  @param[in] MeSync               Sync ME Settings

  @retval EFI_SUCCESS             BIOS and ME ChipsetInit settings are in sync
  @retval EFI_UNSUPPORTED         BIOS and ME ChipsetInit settings are not in sync
**/
EFI_STATUS
PchHsioChipsetInitProg (
  IN  BOOLEAN                     MeSync
  );

/**
  The function program HSIO registers.

  @param[in] SiPreMemPolicyPpi          The SI PREMEM Policy PPI instance

  @retval EFI_SUCCESS                   THe HSIO settings have been programmed correctly
**/
VOID
PchHsioBiosProgPreMem (
  IN  SI_PREMEM_POLICY_PPI             *SiPreMemPolicyPpi
  );

/**
  The function program HSIO registers.

  @param[in] PchPolicyPpi               The PCH Policy PPI instance

**/
VOID
PchHsioBiosProg (
  IN  SI_POLICY_PPI    *SiPolicyPpi
  );

/**
  Write Pmc Xram data.

  @param[in]  Pid                       Port ID
  @param[in]  Offset                    Register offset of Port ID.
  @param[in]  InData                    Input Data. Must be the same size as Size parameter.
  @param[in]  TempMemBaseAddr           Temporary memory base address for PMC device
  @param[in]  PmcBaseAddress            PMC Base Address
**/
VOID
PchPmcXramWrite32 (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT16                            Offset,
  IN  UINT32                            InData,
  IN  UINT32                            TempMemBaseAddr,
  IN  UINTN                             PmcBaseAddress
  );

/**
  Write PMC XRAM End Table Marker

  @param[in]  TempMemBaseAddr           Temporary memory base address for PMC device
  @param[in]  PmcBaseAddress            PMC Base Address
**/
VOID
PchPmcXramEndTableMarker (
  IN  UINT32          TempMemBaseAddr,
  IN  UINTN           PmcBaseAddress
  );

/**
  Program PMC XRAM Data Header

  @param[in]  TempMemBaseAddr           Temporary memory base address for PMC device
  @param[in]  PmcBaseAddress            PMC Base Address
**/
VOID
PchPmcXramDataHdrProg (
  IN  UINT32                            TempMemBaseAddr,
  IN  UINTN                             PmcBaseAddress
  );

/**
  Configure PMC related settings when SCS controllers are disabled.
**/
VOID
ConfigurePmcWhenScsDisabled (
  BOOLEAN                               Disable
  );

/**
  Configure PMC related settings when CIO2 controllers is disabled.
**/
VOID
ConfigurePmcWhenCio2Disabled (
  BOOLEAN                               Disable
  );

/**
  Configure PM Timer power management.
  Once PM Timer is disabled, TCO timer stops counting.
  This must be executed after uCode PM timer emulation.

  @param[in] SiPolicy                  The SI Policy PPI instance
**/
VOID
ConfigurePmTimer (
  IN  SI_POLICY_PPI                    *SiPolicy
  );

/**
  Lock down PMC settings

  @param[in] SiPolicy                  The SI Policy PPI instance
**/
VOID
LockPmcSettings (
  IN  SI_POLICY_PPI                    *SiPolicy
  );

/**
  Configure LPC device on early PEI.
**/
VOID
ConfigureLpcOnEarlyPei (
  VOID
  );

/**
  Configure LPC device on Policy callback.

  @param[in] SiPreMemPolicyPpi   The SI PreMem Policy PPI instance
**/
VOID
ConfigureLpcOnPolicy (
  IN  SI_PREMEM_POLICY_PPI       *SiPreMemPolicyPpi
  );

#endif
