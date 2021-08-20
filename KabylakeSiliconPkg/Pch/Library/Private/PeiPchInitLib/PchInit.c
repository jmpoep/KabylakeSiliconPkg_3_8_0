/** @file
  The PCH Init After Memory PEI module.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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

#include "PchInitPei.h"
#include <HeciRegs.h>
#include <MeChipset.h>
#include "Wdt.h"
#include "PchSpi.h"
#include <Private/PchConfigHob.h>
#include <Library/PchSerialIoLib.h>
#include <Library/SiPolicyLib.h>
#include <Library/PostCodeLib.h>
#include <Private/Library/PeiI2cMasterLib.h>
#include <Private/Ppi/HybridStoragePpi.h>
#include <Library/PeiMeLib.h>

#ifndef FSP_FLAG
#include <Library/PchSmmControlLib.h>
#endif
/**
  Configure SpiEiss according to policy setting.

  @param[in] LockDownConfig       LockDownConfig policy
**/
VOID
ConfigureSpiEiss (
  IN  PCH_LOCK_DOWN_CONFIG        *LockDownConfig
  )
{
  UINTN                   LpcBaseAddress;
  UINTN                   SpiBaseAddress;

  LpcBaseAddress = MmPciBase (
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_LPC,
                     PCI_FUNCTION_NUMBER_PCH_LPC
                     );
  SpiBaseAddress = MmPciBase (
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_SPI,
                     PCI_FUNCTION_NUMBER_PCH_SPI
                     );

  ///
  /// PCH BIOS Spec Section 3.6 Flash Security Recommendation
  /// BIOS needs to enable the "Enable in SMM.STS" (EISS) feature of the PCH by setting
  /// SPI PCI offset DCh[5] = 1b for SPI or setting eSPI PCI offset DCh[5] = 1b for eSPI.
  /// When this bit is set, the BIOS region is not writable until SMM sets the InSMM.STS bit,
  /// to ensure BIOS can only be modified from SMM. Please refer to CPU BWG for more details
  /// on InSMM.STS bit.
  /// Intel requires that BIOS enables the Lock Enable (LE) feature of the PCH to ensure
  /// SMM protection of flash.
  /// SPI PCI offset DCh[1] = 1b for SPI or setting eSPI PCI offset DCh[1] = 1b for eSPI.
  /// When this bit is set, EISS is locked down.
  ///
  if (LockDownConfig->SpiEiss == 1) {
    //
    // Set SPI EISS (SPI PCI offset DCh[5]) and LE (SPI PCI offset DCh[1])
    // Set LPC/eSPI EISS (LPC/eSPI PCI offset DCh[5]) and LE (LPC/eSPI PCI offset DCh[1])
    //
    MmioOr8 (SpiBaseAddress + R_PCH_SPI_BC, B_PCH_SPI_BC_EISS);
    MmioOr8 (LpcBaseAddress + R_PCH_LPC_BC, B_PCH_LPC_BC_EISS);
  } else {
    //
    // Clear SMM_EISS (SPI PCI offset DCh[5])
    // Clear LPC/eSPI EISS (LPC/eSPI PCI offset DCh[5])
    // Since the HW default is 1, need to clear it when disabled in policy
    //
    MmioAnd8 (SpiBaseAddress + R_PCH_SPI_BC, (UINT8) ~B_PCH_SPI_BC_EISS);
    MmioAnd8 (LpcBaseAddress + R_PCH_LPC_BC, (UINT8) ~B_PCH_LPC_BC_EISS);
  }
}

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
  )
{
  UINT32                              MaxPciePortNum;
  UINT32                              MaxDrcrmRegisters;
  UINT32                              PortIndex;
  UINT32                              PlaceInDrcrm;
  UINT32                              Index;
  UINT32                              Drcrm[PCH_MAX_FIA_DRCRM];
  UINT32                              ClkReqNum;
  EFI_STATUS                          Status;
  PCH_PCIE_CONFIG                     *PcieRpConfig;
  PCH_LAN_CONFIG                      *LanConfig;
  HYBRID_STORAGE_CONFIG               *HybridStorageConfig;
  EFI_PEI_PPI_DESCRIPTOR              *HybridStorageConfigPpiDesc;;
  HYBRID_STORAGE_CFG_PPI              *HybridStorageCfg;
  UINT8                               ControllerConfig[PCH_MAX_PCIE_CONTROLLERS];
  UINT8                               HbrStoragePresent;
  UINT16                              NumOfControllers;

  HbrStoragePresent = 0;
  MaxPciePortNum = GetPchMaxPciePortNum ();
  ASSERT (MaxPciePortNum <= PCH_MAX_PCIE_ROOT_PORTS);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gPcieRpConfigGuid, (VOID *) &PcieRpConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gLanConfigGuid, (VOID *) &LanConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gHybridStorageConfigGuid, (VOID *) &HybridStorageConfig);
  ASSERT_EFI_ERROR (Status);

  //
  // Check Hybrid Storage Support
  //
  NumOfControllers = GetPchMaxPcieControllerNum ();
  ZeroMem (ControllerConfig, sizeof (ControllerConfig));
  if (HybridStorageConfig->HybridStorageMode) {
    Status = PeiHeciGetSoftStrpConfigMsg (NumOfControllers, ControllerConfig);
    if (Status == EFI_SUCCESS) {
      for (Index = 0; Index < NumOfControllers; Index++) {
        HbrStoragePresent |= ControllerConfig[Index];
      }
    }
    Status = PeiServicesLocatePpi (
               &gHybridStorageCfgPpiGuid,
               0,
               NULL,
               (VOID **) &HybridStorageCfg
               );
    if (Status == EFI_NOT_FOUND) {
      HybridStorageCfg = (HYBRID_STORAGE_CFG_PPI *) AllocateZeroPool (sizeof (HYBRID_STORAGE_CFG_PPI));
      if (HybridStorageCfg == NULL) {
        return;
      }
      CopyMem (HybridStorageCfg, ControllerConfig, PCH_MAX_PCIE_CONTROLLERS * sizeof (UINT8));
      HybridStorageConfigPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
      if (HybridStorageConfigPpiDesc == NULL) {
        ASSERT(FALSE);
        return;
      }
      HybridStorageConfigPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
      HybridStorageConfigPpiDesc->Guid = &gHybridStorageCfgPpiGuid;
      HybridStorageConfigPpiDesc->Ppi = HybridStorageCfg;
      DEBUG ((DEBUG_INFO, "Installing Hybrid Storage device configuration PPI\n"));
      Status = PeiServicesInstallPpi (HybridStorageConfigPpiDesc);
      ASSERT_EFI_ERROR (Status);
    }
  }
  if (GetPchGeneration () == KblPch) {
    MaxDrcrmRegisters = KBL_PCH_MAX_FIA_DRCRM;
  } else {
    MaxDrcrmRegisters = SKL_PCH_MAX_FIA_DRCRM;
  }

  for (Index = 0; Index < MaxDrcrmRegisters; ++Index) {
    Drcrm[Index] = 0;
  }

  ///
  /// PCH BIOS Spec Section 29.1.1 CLKREQ to Root Port Mapping
  /// The mapping of the PCIeExpress Ports to the CLKREQ# pins can be
  /// specified through the DRCRMx registers
  ///
  MaxPciePortNum  = GetPchMaxPciePortNum ();
  ASSERT ((MaxPciePortNum + 1) < MaxDrcrmRegisters * S_PCH_PCR_FIA_DRCRM_FIELDS_PER_REG); // +1 is for GbE

  for (PortIndex = 0; PortIndex < MaxPciePortNum; PortIndex++) {
    if (PortIndex < N_PCH_PCR_FIA_DRCRM_GBEPCKRQM) {
      PlaceInDrcrm = PortIndex;
    } else {
      PlaceInDrcrm = PortIndex + 1;
    }

    if ((HybridStorageConfig->HybridStorageMode) && (HbrStoragePresent != 0)) {
      for (Index = 0; Index < NumOfControllers; Index++) {
        if (ControllerConfig[Index] == PcieOverride2x2) {
          PcieRpConfig->RootPort[Index * PCH_PCIE_CONTROLLER_PORTS + 2].ClkReqSupported = 1;
          PcieRpConfig->RootPort[Index * PCH_PCIE_CONTROLLER_PORTS + 2].ClkReqNumber = PcieRpConfig->RootPort[Index * PCH_PCIE_CONTROLLER_PORTS].ClkReqNumber;
          break;
        }
      }
    }
    if (PcieRpConfig->RootPort[PortIndex].ClkReqSupported) {
      ClkReqNum = PcieRpConfig->RootPort[PortIndex].ClkReqNumber;
      DEBUG ((DEBUG_INFO, "ClkReqNum(%d) = %d\n", PortIndex, ClkReqNum));
    } else {
      ClkReqNum = V_PCH_PCR_FIA_DRCRM_NO_CLKREQ;
    }
    Drcrm[PlaceInDrcrm / S_PCH_PCR_FIA_DRCRM_FIELDS_PER_REG] |=
      ClkReqNum << (S_PCH_PCR_FIA_DRCRM_BITS_PER_FIELD * (PlaceInDrcrm % S_PCH_PCR_FIA_DRCRM_FIELDS_PER_REG));
  }

  PlaceInDrcrm = N_PCH_PCR_FIA_DRCRM_GBEPCKRQM;
  ClkReqNum = LanConfig->ClkReqNumber;
  Drcrm[PlaceInDrcrm / S_PCH_PCR_FIA_DRCRM_FIELDS_PER_REG] |=
    ClkReqNum << (S_PCH_PCR_FIA_DRCRM_BITS_PER_FIELD * (PlaceInDrcrm % S_PCH_PCR_FIA_DRCRM_FIELDS_PER_REG));

  DEBUG ((DEBUG_INFO, "DRCRM: 0x%08x 0x%08x 0x%08x 0x%08x\n", Drcrm[0], Drcrm[1], Drcrm[2], Drcrm[3]));

  for (Index = 0; Index < MaxDrcrmRegisters; ++Index) {
    PchPcrWrite32 (
      PID_FIA,
      (UINT16) (R_PCH_PCR_FIA_DRCRM1 + (Index * S_PCH_PCR_FIA_DRCRM)),
      Drcrm[Index]
      );
  }

  ///
  /// Lock DRCRM registers and enable FIA power management
  /// PCR[FIA] + 0h bits [31, 17, 16, 15] to [1, 1, 1, 1]
  ///
  PchPcrAndThenOr32 (
    PID_FIA,
    R_PCH_PCR_FIA_CC,
    ~0u,
    B_PCH_PCR_FIA_CC_SRL | B_PCH_PCR_FIA_CC_PTOCGE | B_PCH_PCR_FIA_CC_OSCDCGE | B_PCH_PCR_FIA_CC_SCPTCGE
    );
}

//
// SVID / SID init table entry
//
typedef struct {
  UINT8 DeviceNumber;
  UINT8 FunctionNumber;
  UINT8 SvidRegOffset;
} PCH_SVID_SID_INIT_ENTRY;

STATIC PCH_SVID_SID_INIT_ENTRY  SvidSidInitTable[] = {
  { PCI_DEVICE_NUMBER_PCH_LPC,                  PCI_FUNCTION_NUMBER_PCH_LPC,                 PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_P2SB,                 PCI_FUNCTION_NUMBER_PCH_P2SB,                PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_PMC,                  PCI_FUNCTION_NUMBER_PCH_PMC,                 PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_HDA,                  PCI_FUNCTION_NUMBER_PCH_HDA,                 PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SATA,                 PCI_FUNCTION_NUMBER_PCH_SATA,                PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SMBUS,                PCI_FUNCTION_NUMBER_PCH_SMBUS,               PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SPI,                  PCI_FUNCTION_NUMBER_PCH_SPI,                 PCI_SVID_OFFSET},
  //
  // Skip PCH LAN controller
  // PCH LAN SVID/SID may be loaded automatically from the NVM Word 0Ch/0Bh upon power up or reset
  // depending on the "Load Subsystem ID" bit field in NVM word 0Ah
  //
  //{ PCI_DEVICE_NUMBER_PCH_LAN,                  PCI_FUNCTION_NUMBER_PCH_LAN,                 PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_TRACE_HUB,            PCI_FUNCTION_NUMBER_PCH_TRACE_HUB,           PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART0,      PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART0,     PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART1,      PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART1,     PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI0,       PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI0,      PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI1,       PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI1,      PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SCS_EMMC,             PCI_FUNCTION_NUMBER_PCH_SCS_EMMC,            PCI_SVID_OFFSET}, ///< SCS EMMC, SKL PCH-LP only
  { PCI_DEVICE_NUMBER_PCH_SCS_SDIO,             PCI_FUNCTION_NUMBER_PCH_SCS_SDIO,            PCI_SVID_OFFSET}, ///< SCS SDIO, SKL PCH-LP only
  { PCI_DEVICE_NUMBER_PCH_SCS_SDCARD,           PCI_FUNCTION_NUMBER_PCH_SCS_SDCARD,          PCI_SVID_OFFSET}, ///< SCS SD Card, SKL PCH-LP only
  { PCI_DEVICE_NUMBER_PCH_XHCI,                 PCI_FUNCTION_NUMBER_PCH_XHCI,                PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_XDCI,                 PCI_FUNCTION_NUMBER_PCH_XDCI,                PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_THERMAL,              PCI_FUNCTION_NUMBER_PCH_THERMAL,             PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_CIO2,                 PCI_FUNCTION_NUMBER_PCH_CIO2,                PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_ISH,                  PCI_FUNCTION_NUMBER_PCH_ISH,                 PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_1,    R_PCH_PCIE_SVID},
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_2,    R_PCH_PCIE_SVID},
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_3,    R_PCH_PCIE_SVID},
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_4,    R_PCH_PCIE_SVID},
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_5,    R_PCH_PCIE_SVID},
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_6,    R_PCH_PCIE_SVID},
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_7,    R_PCH_PCIE_SVID},
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_8,    R_PCH_PCIE_SVID},
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_9,    R_PCH_PCIE_SVID},
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_10,   R_PCH_PCIE_SVID},
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_11,   R_PCH_PCIE_SVID},
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_12,   R_PCH_PCIE_SVID},
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_13,   R_PCH_PCIE_SVID}, ///< PCI Express Root Port #13, SKL-H and KBL-H only
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_14,   R_PCH_PCIE_SVID}, ///< PCI Express Root Port #14, SKL-H and KBL-H only
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_15,   R_PCH_PCIE_SVID}, ///< PCI Express Root Port #15, SKL-H and KBL-H only
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_16,   R_PCH_PCIE_SVID}, ///< PCI Express Root Port #16, SKL-H and KBL-H only
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_17,   R_PCH_PCIE_SVID}, ///< PCI Express Root Port #17, SKL-H and KBL-H only
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_18,   R_PCH_PCIE_SVID}, ///< PCI Express Root Port #18, SKL-H and KBL-H only
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_19,   R_PCH_PCIE_SVID}, ///< PCI Express Root Port #19, SKL-H and KBL-H only
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_20,   R_PCH_PCIE_SVID}, ///< PCI Express Root Port #20, SKL-H and KBL-H only
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_21,   R_PCH_PCIE_SVID}, ///< PCI Express Root Port #21, KBL-H only
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_22,   R_PCH_PCIE_SVID}, ///< PCI Express Root Port #22, KBL-H only
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_23,   R_PCH_PCIE_SVID}, ///< PCI Express Root Port #23, KBL-H only
  { PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3,        PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_24,   R_PCH_PCIE_SVID}, ///< PCI Express Root Port #24, KBL-H only
  { PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C0,       PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C0,      PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C1,       PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C1,      PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C2,       PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C2,      PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C3,       PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C3,      PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART2,      PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART2,     PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C5,       PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C5,      PCI_SVID_OFFSET},
  { PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C4,       PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C4,      PCI_SVID_OFFSET},
  { ME_DEVICE_NUMBER,                           HECI_FUNCTION_NUMBER,                        PCI_SVID_OFFSET},
  { ME_DEVICE_NUMBER,                           HECI2_FUNCTION_NUMBER,                       PCI_SVID_OFFSET},
  { ME_DEVICE_NUMBER,                           IDER_FUNCTION_NUMBER,                        PCI_SVID_OFFSET},
  { ME_DEVICE_NUMBER,                           SOL_FUNCTION_NUMBER,                         PCI_SVID_OFFSET}
};

/**
  Program Pch devices Subsystem Vendor Identifier (SVID) and Subsystem Identifier (SID).

  @param[in] SiPolicy    The SI Policy PPI instance
**/
VOID
PchProgramSvidSid (
  IN SI_POLICY_PPI      *SiPolicy
  )
{
  UINT8                           Index;
  UINT8                           BusNumber;
  UINTN                           PciEAddressBase;
  UINT8                           DeviceNumber;
  UINT8                           FunctionNumber;
  UINT8                           SvidRegOffset;
  UINTN                           SvidSidInitTableSize;
  EFI_STATUS                      Status;
  PCH_GENERAL_CONFIG              *PchGeneralConfig;

  DEBUG ((DEBUG_INFO, "ProgramSvidSid() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);

  if ((PchGeneralConfig->SubSystemVendorId != 0) ||
      (PchGeneralConfig->SubSystemId != 0)) {
    BusNumber            = DEFAULT_PCI_BUS_NUMBER_PCH;
    SvidSidInitTableSize = sizeof (SvidSidInitTable) / sizeof (PCH_SVID_SID_INIT_ENTRY);

    for (Index = 0; Index < SvidSidInitTableSize; Index++) {
      DeviceNumber    = SvidSidInitTable[Index].DeviceNumber;
      FunctionNumber  = SvidSidInitTable[Index].FunctionNumber;
      SvidRegOffset   = SvidSidInitTable[Index].SvidRegOffset;
      PciEAddressBase = MmPciBase (
                          BusNumber,
                          DeviceNumber,
                          FunctionNumber
                          );
      //
      // Skip if the device is disabled
      //
      if (MmioRead16 (PciEAddressBase) != V_PCH_INTEL_VENDOR_ID) {
        continue;
      }
      //
      // Program Pch devices Subsystem Vendor Identifier (SVID) and Subsystem Identifier (SID)
      //
      MmioWrite32 (
        (UINTN) (PciEAddressBase + SvidRegOffset),
        (UINT32) (PchGeneralConfig->SubSystemVendorId |
                  (PchGeneralConfig->SubSystemId << 16))
        );
    }
  }

  DEBUG ((DEBUG_INFO, "ProgramSvidSid() End\n"));
}


/**
  Initialize IOAPIC according to IoApicConfig policy of the PCH
  Policy PPI

  @param[in] SiPolicyPpi          The SI Policy PPI instance

  @retval EFI_SUCCESS             Succeeds.
  @retval EFI_DEVICE_ERROR        Device error, aborts abnormally.
**/
EFI_STATUS
PchIoApicInit (
  IN  SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS            Status;
  UINT16                RegData16;
  UINTN                 P2sbBase;
  PCH_IOAPIC_CONFIG     *IoApicConfig;
  PCH_DMI_CONFIG        *DmiConfig;
  UINT32                IoApicAddress;
  UINT32                IoApicId;
  UINT32                Data32;

  ///
  /// Program PSF Multicast registers accordingly to SKL PCH BWG 5.14.4 PSF EOI Multicast Configuration
  ///
  PsfSetEoiMulticastConfiguration ();

  //
  // Configure ITSS power management settings
  //
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gIoApicConfigGuid, (VOID *) &IoApicConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gDmiConfigGuid, (VOID *) &DmiConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  /// If enable legacy IO low latency
  ///   Set PCR[ITSS] + 3300h[4:0] = 00000b
  /// else
  ///   Set PCR[ITSS] + 3300h[4:0] = 11011b
  /// Set PCR[ITSS] + 3300h[2] = 1 in POST time only if 8254 timer is not used.
  ///
  if (DmiConfig->LegacyIoLowLatency) {
    Data32 = 0;
  } else {
    Data32 = (B_PCH_PCR_ITSS_ITSSPRC_PGCBDCGE | B_PCH_PCR_ITSS_ITSSPRC_HPETDCGE | B_PCH_PCR_ITSS_ITSSPRC_IOSFICGE | B_PCH_PCR_ITSS_ITSSPRC_ITSSCGE);
    if (IoApicConfig->Early8254ClockGatingEnable) {
      Data32 |= B_PCH_PCR_ITSS_ITSSPRC_8254CGE;
    }
  }
  PchPcrAndThenOr32 (
    PID_ITSS, R_PCH_PCR_ITSS_ITSSPRC,
    ~0u,
    Data32
    );

  //
  // Get P2SB base address
  //
  P2sbBase = MmPciBase (
               DEFAULT_PCI_BUS_NUMBER_PCH,
               PCI_DEVICE_NUMBER_PCH_P2SB,
               PCI_FUNCTION_NUMBER_PCH_P2SB
               );

  if (IoApicConfig->ApicRangeSelect != (UINT8) (MmioRead16 (P2sbBase + R_PCH_P2SB_IOAC) & B_PCH_P2SB_IOAC_ASEL)) {
    ///
    /// Program APIC Range Select bits that define address bits 19:12 for the IOxAPIC range.
    /// This value must not be changed unless the IOxAPIC Enable bit is cleared.
    ///
    MmioAnd16 (P2sbBase + R_PCH_P2SB_IOAC, (UINT16) ~(B_PCH_P2SB_IOAC_AE));
    ///
    /// Program APIC Range Select bits at P2SB PCI offset 64h[7:0]
    ///
    MmioAndThenOr16 (
      P2sbBase + R_PCH_P2SB_IOAC,
      (UINT16) ~(B_PCH_P2SB_IOAC_ASEL),
      (UINT16) IoApicConfig->ApicRangeSelect
      );
  }
  ///
  /// PCH BIOS Spec Section 6.6.2.1
  /// 1. Enable the IOAPIC by setting the APIC Enable bit, P2SB PCI offset 64h [8], if the
  ///    system needs to use the IOxAPIC. The APIC Enable bits needs read back after the bit is written.
  ///
  MmioOr16 (P2sbBase + R_PCH_P2SB_IOAC, B_PCH_P2SB_IOAC_AE);
  ///
  /// Reads back for posted write to take effect
  ///
  MmioRead16 (P2sbBase + R_PCH_P2SB_IOAC);

  ///
  /// Get current IO APIC ID
  ///
  IoApicAddress = (UINT32) (MmioRead8 (P2sbBase + R_PCH_P2SB_IOAC) << N_PCH_IO_APIC_ASEL);
  MmioWrite8 ((UINTN) (R_PCH_IO_APIC_INDEX | IoApicAddress), 0);
  IoApicId = MmioRead32 ((UINTN) (R_PCH_IO_APIC_DATA | IoApicAddress)) >> 24;
  ///
  /// IO APIC ID is at APIC Identification Register [27:24]
  ///
  if ((IoApicConfig->IoApicId != IoApicId) && (IoApicConfig->IoApicId < 0x10)) {
    ///
    /// Program APIC ID
    ///
    MmioWrite8 ((UINTN) (R_PCH_IO_APIC_INDEX | IoApicAddress), 0);
    MmioWrite32 ((UINTN) (R_PCH_IO_APIC_DATA | IoApicAddress), (UINT32) (IoApicConfig->IoApicId << 24));
  }

  if (IoApicConfig->IoApicEntry24_119 == FALSE) {
    ///
    /// Program IOAPIC maximal entry to 24 in PCR[ITSS] + 31FCh[9]
    /// and in IOAPIC Version Register
    PchPcrAndThenOr16 (PID_ITSS, R_PCH_PCR_ITSS_GIC, 0xFFFF, (UINT16) B_PCH_PCR_ITSS_GIC_MAX_IRQ_24);
    MmioWrite8 ((UINTN) (R_PCH_IO_APIC_INDEX | IoApicAddress), 1);
    MmioWrite32 ((R_PCH_IO_APIC_DATA | IoApicAddress), 0x170020);
  } else {
    ///
    /// Program IOAPIC maximal entry to 119 in PCR[ITSS] + 31FCh[9]
    /// and in IOAPIC Version Register
    PchPcrAndThenOr16 (PID_ITSS, R_PCH_PCR_ITSS_GIC, (UINT16) (~B_PCH_PCR_ITSS_GIC_MAX_IRQ_24), 0x0);
    MmioWrite8 ((UINTN) (R_PCH_IO_APIC_INDEX | IoApicAddress), 1);
    MmioWrite32 ((R_PCH_IO_APIC_DATA | IoApicAddress), 0x770020);
  }

  ///
  /// Program this field to provide a unique bus:device:function number for the internal IOxAPIC
  ///
  if (IoApicConfig->BdfValid) {
    RegData16 = ((UINT16) (IoApicConfig->BusNumber) << 8) & B_PCH_P2SB_IBDF_BUF;
    RegData16 |= ((UINT16) (IoApicConfig->DeviceNumber) << 3) & B_PCH_P2SB_IBDF_DEV;
    RegData16 |= (UINT16) (IoApicConfig->FunctionNumber) & B_PCH_P2SB_IBDF_FUNC;
    MmioWrite16 ((UINTN) (P2sbBase + R_PCH_P2SB_IBDF), RegData16);
  }

  //
  // Build the resource descriptor hob for IOAPIC address resource.
  //
  BuildResourceDescriptorHob (
    EFI_RESOURCE_MEMORY_MAPPED_IO,
    (EFI_RESOURCE_ATTRIBUTE_PRESENT    |
     EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE),
    R_PCH_IO_APIC_INDEX | IoApicAddress,
    0x1000
    );
  BuildMemoryAllocationHob (
    R_PCH_IO_APIC_INDEX | IoApicAddress,
    0x1000,
    EfiMemoryMappedIO
    );

  return EFI_SUCCESS;
}

/**
  The function performs P2SB specific programming.

  @param[in] SiPolicy           The SI Policy PPI instance

  @retval EFI_SUCCESS           The required settings programmed successfully
**/
EFI_STATUS
EFIAPI
PchP2sbConfigure (
  IN  SI_POLICY_PPI           *SiPolicy
  )
{
  UINTN                       P2sbBase;
  EFI_STATUS                  Status;
  PCH_DMI_CONFIG              *DmiConfig;
  //
  // Get P2SB base address
  //
  P2sbBase = MmPciBase (
               DEFAULT_PCI_BUS_NUMBER_PCH,
               PCI_DEVICE_NUMBER_PCH_P2SB,
               PCI_FUNCTION_NUMBER_PCH_P2SB
               );

  Status = GetConfigBlock ((VOID *) SiPolicy, &gDmiConfigGuid, (VOID *) &DmiConfig);
  ASSERT_EFI_ERROR (Status);

  //
  // P2SB power management settings.
  //

  ///
  /// Set PGCB clock gating enable (PGCBCGE)
  /// P2SB PCI offset 0xE0[16] = 1
  ///
  MmioOr8 (P2sbBase + R_PCH_P2SB_E0 + 2, BIT0);
  ///
  /// Set Hardware Autonomous Enable (HAE) and PMC Power Gating Enable (PMCPG_EN)
  /// 0xE4[2,1.0] = 0's
  /// If enable legacy IO low latency
  ///   P2SB PCI offset 0xE4[5] = 0
  /// else
  ///   P2SB PCI offset 0xE4[5] = 1
  ///
  if (DmiConfig->LegacyIoLowLatency) {
    MmioAnd8 (P2sbBase + R_PCH_P2SB_E4, (UINT8)~(BIT2 | BIT1 | BIT0));
  } else {
    MmioAndThenOr8 (P2sbBase + R_PCH_P2SB_E4, (UINT8)~(BIT2 | BIT1 | BIT0), BIT5);
  }

  //
  // If enable legacy IO low latency
  // set P2SB PCI offset 0xE8[0] = 1
  // set P2SB PCI offset 0xE8[1] = 1
  // set P2SB PCI offset 0xEA[0] = 1
  // set P2SB PCI offset 0xEA[1] = 1
  //
  if (DmiConfig->LegacyIoLowLatency) {
    MmioOr16 (P2sbBase + R_PCH_P2SB_E8, BIT1 | BIT0);
    MmioOr16 (P2sbBase + R_PCH_P2SB_EA, BIT1 | BIT0);
  }

  return EFI_SUCCESS;
}

/**
  The function performs PSTH specific programming.

  @param[in] SiPolicy          The SI Policy instance

  @retval EFI_SUCCESS          The required settings programmed successfully
**/
EFI_STATUS
EFIAPI
PchPsthConfigure (
  IN  SI_POLICY_PPI           *SiPolicy
  )
{
  //
  // PSTH power management settings.
  //

  ///
  /// PSTHCTL (0xD00h[2]) = 0, PSTH IOSF Primary Trunk Clock Gating Enable (PSTHIOSFPTCGE)
  /// PSTHCTL (0xD00h[1]) = 1, PSTH IOSF Sideband Trunk Clock Gating Enable (PSTHIOSFSTCGE)
  /// PSTHCTL (0xD00h[0]) = 1, PSTH Dynamic Clock Gating Enable (PSTHDCGE)
  ///
  PchPcrAndThenOr32 (
    PID_PSTH, R_PCH_PCR_PSTH_PSTHCTL,
    (UINT32) ~(B_PCH_PCR_PSTH_PSTHIOSFPTCGE),
    B_PCH_PCR_PSTH_PSTHIOSFSTCGE |
    B_PCH_PCR_PSTH_PSTHDCGE
    );

  return EFI_SUCCESS;
}

/**
  The function performs GPIO Power Management programming.

  @param[in] SiPolicyPpi    The SI Policy PPI instance

  @retval EFI_SUCCESS       The required settings programmed successfully
**/
EFI_STATUS
EFIAPI
PchGpioConfigurePm (
  IN  SI_POLICY_PPI           *SiPolicyPpi
  )
{
  //
  // Program MISCCFG.GPDLCGEn and MISCCFG.GPDPCGEn for Community 0
  //
  MmioAndThenOr32 (
    (UINTN) PCH_PCR_ADDRESS (PID_GPIOCOM0, R_PCH_PCR_GPIO_MISCCFG),
    ~(UINT32) (0),
    (UINT32) (B_PCH_PCR_GPIO_MISCCFG_GPDLCGEN | B_PCH_PCR_GPIO_MISCCFG_GPDPCGEN)
    );

  //
  // Program MISCCFG.GPDLCGEn and MISCCFG.GPDPCGEn for Community 1
  //
  MmioAndThenOr32 (
    (UINTN) PCH_PCR_ADDRESS (PID_GPIOCOM1, R_PCH_PCR_GPIO_MISCCFG),
    ~(UINT32) (0),
    (UINT32) (B_PCH_PCR_GPIO_MISCCFG_GPDLCGEN | B_PCH_PCR_GPIO_MISCCFG_GPDPCGEN)
    );

  //
  // Program MISCCFG.GPDLCGEn and MISCCFG.GPDPCGEn for Community 2
  //
  MmioAndThenOr32 (
    (UINTN) PCH_PCR_ADDRESS (PID_GPIOCOM2, R_PCH_PCR_GPIO_MISCCFG),
    ~(UINT32) (0),
    (UINT32) (B_PCH_PCR_GPIO_MISCCFG_GPDLCGEN | B_PCH_PCR_GPIO_MISCCFG_GPDPCGEN)
    );

  //
  // Program MISCCFG.GPDLCGEn and MISCCFG.GPDPCGEn for Community 3
  //
  MmioAndThenOr32 (
    (UINTN) PCH_PCR_ADDRESS (PID_GPIOCOM3, R_PCH_PCR_GPIO_MISCCFG),
    ~(UINT32) (0),
    (UINT32) (B_PCH_PCR_GPIO_MISCCFG_GPDLCGEN | B_PCH_PCR_GPIO_MISCCFG_GPDPCGEN)
    );

  return EFI_SUCCESS;
}

/**
  The function performs RTC specific programming.

  @param[in] SiPolicyPpi        The SI Policy PPI instance

  @retval EFI_SUCCESS           The required settings programmed successfully
**/
EFI_STATUS
EFIAPI
PchRtcConfigure (
  IN  SI_POLICY_PPI           *SiPolicyPpi
  )
{
  ///
  /// Set PCR[RTC] + 3418h[1:0] = 11b
  ///
  PchPcrAndThenOr32 (
    PID_RTC, R_PCH_PCR_RTC_RTCDCG,
    ~(UINT32) (0),
    (UINT32) (R_PCH_PCR_RTC_RTCDCG_RTCPCICLKDCGEN | R_PCH_PCR_RTC_RTCDCG_RTCROSIDEDCGEN)
    );

  ///
  /// Set PCR[RTC] + 3F00h[8] = 1b
  ///
  PchPcrAndThenOr32 (
    PID_RTC, R_PCH_PCR_RTC_3F00,
    ~(UINT32) (0),
    (UINT32) (BIT8)
    );

  //
  // Clear RTC SMI enable and status.
  //
  PchPcrWrite32 (PID_RTC, R_PCH_PCR_RTC_UIPSMI, 0x00030000);

  return EFI_SUCCESS;
}

/**
  The function performs SMBUS specific programming.

  @param[in] SiPolicyPpi       The SI Policy PPI instance

  @retval EFI_SUCCESS          The required settings programmed successfully
**/
EFI_STATUS
EFIAPI
PchSmbusConfigure (
  IN  SI_POLICY_PPI           *SiPolicyPpi
  )
{
  UINTN                       SmbusBaseAddress;
  UINT32                      Data32And;
  UINT32                      Data32Or;
  EFI_STATUS                  Status;
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  PCH_SMBUS_PREMEM_CONFIG     *SmbusPreMemConfig;
  UINT16                      SmbusIoBase;

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **)&SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSmbusPreMemConfigGuid, (VOID *) &SmbusPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  SmbusBaseAddress = MmPciBase (
                       DEFAULT_PCI_BUS_NUMBER_PCH,
                       PCI_DEVICE_NUMBER_PCH_SMBUS,
                       PCI_FUNCTION_NUMBER_PCH_SMBUS
                       );
  ///
  /// Enable SMBus dynamic clock gating by setting Smbus PCI offset 80h [16,14,12,10,8] = 0b and [5] = 1b respectively
  /// Disable SMBus dynamic clock gating of PGCB by [18] = 1
  ///
  Data32And = (UINT32) ~(BIT16 | BIT14 | BIT12 | BIT10 | BIT8);
  Data32Or  = BIT18 | BIT5;
  if (SmbusPreMemConfig->DynamicPowerGating) {
    Data32Or &= (UINT32) ~BIT18;
  }
  MmioAndThenOr32 (
    SmbusBaseAddress + R_PCH_SMBUS_80,
    Data32And,
    Data32Or
    );
  #ifndef MINTREE_FLAG
  ///
  /// Set SMBUS PCR 0x10h [5] = 1 and clear [2,1,0] = 0
  ///
  PchPcrAndThenOr32 (
    PID_SMB, R_PCH_PCR_SMBUS_PCE,
    ~(UINT32) (BIT2 | BIT1 | BIT0),
    (UINT32) B_PCH_PCR_SMBUS_PCE_HAE
    );
  #endif //MINTREE_FLAG
  SmbusIoBase = MmioRead16 (SmbusBaseAddress + R_PCH_SMBUS_BASE) & B_PCH_SMBUS_BASE_BAR;
  ASSERT (SmbusIoBase != 0);
  ASSERT (MmioRead8 (SmbusBaseAddress + PCI_COMMAND_OFFSET) & EFI_PCI_COMMAND_IO_SPACE);

  ///
  /// Clear SMBUS Alert status in case it got set after enabling SMBALERT# pin
  ///
  IoWrite8 (SmbusIoBase + R_PCH_SMBUS_HSTS, B_PCH_SMBUS_SMBALERT_STS);

  ///
  /// Check to disable Smbus controller
  ///
  if (SmbusPreMemConfig->Enable == FALSE) {
    PchPcrAndThenOr32 (
      PID_SMB, R_PCH_PCR_SMBUS_GC,
      0xFFFFFFFF,
      B_PCH_PCR_SMBUS_GC_FD
      );

    ///
    /// Disable and hide SMBUS in PSF
    ///
    PsfDisableSmbusDevice ();
  }

  return EFI_SUCCESS;
}

/**
  The function performs Serial IRQ specific programming.

  @param[in] SiPolicyPpi               The SI Policy PPI instance
**/
VOID
EFIAPI
PchConfigureSerialIrq (
  IN  SI_POLICY_PPI                    *SiPolicyPpi
  )
{
  UINTN                                 PciPmcRegBase;
  UINTN                                 PciLpcRegBase;
  UINT8                                 RegData8;
  EFI_STATUS                            Status;
  PCH_LPC_SIRQ_CONFIG                   *SerialIrqConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSerialIrqConfigGuid, (VOID *) &SerialIrqConfig);
  ASSERT_EFI_ERROR (Status);

  if (SerialIrqConfig->SirqEnable == FALSE) {
    return;
  }

  PciLpcRegBase = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC);
  PciPmcRegBase = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_PMC, PCI_FUNCTION_NUMBER_PCH_PMC);
  RegData8        = 0;

  ///
  /// PCH BIOS Spec Section 6.3 Serial IRQs
  /// The only System BIOS requirement to use IRQs as a serial IRQ is to enable the function in LPC PCI offset 64h[7] and
  /// select continuous or quiet mode, LPC PCI offset 64h[6].
  /// PCH requires that the System BIOS first set the SERIRQ logic to continuous mode operation for at least one frame
  /// before switching it into quiet mode operation. This operation should be performed during the normal boot sequence
  /// as well as a resume from STR (S3).
  ///
  RegData8  = MmioRead8 (PciLpcRegBase + R_PCH_LPC_SERIRQ_CNT);
  RegData8  &= (UINT8) ~(B_PCH_LPC_SERIRQ_CNT_SIRQEN | B_PCH_LPC_SERIRQ_CNT_SFPW);

  switch (SerialIrqConfig->StartFramePulse) {
    case PchSfpw8Clk:
      RegData8 |= V_PCH_LPC_SERIRQ_CNT_SFPW_8CLK;
      break;

    case PchSfpw6Clk:
      RegData8 |= V_PCH_LPC_SERIRQ_CNT_SFPW_6CLK;
      break;

    case PchSfpw4Clk:
    default:
      RegData8 |= V_PCH_LPC_SERIRQ_CNT_SFPW_4CLK;
      break;
  }
  ///
  /// Set the SERIRQ logic to continuous mode
  ///
  RegData8 |= (UINT8) (B_PCH_LPC_SERIRQ_CNT_SIRQEN | B_PCH_LPC_SERIRQ_CNT_SIRQMD);

  MmioWrite8 (PciLpcRegBase + R_PCH_LPC_SERIRQ_CNT, RegData8);

  ///
  /// PCH BIOS Spec Section 6.3 Serial IRQs
  /// The only System BIOS requirement to use IRQs as a serial IRQ is to enable the function
  /// in LPC PCI offset 64h[7] and select continuous or quiet mode, LPC PCI offset 64h[6].
  ///
  if (SerialIrqConfig->SirqMode == PchQuietMode) {
    MmioAnd8 (PciLpcRegBase + R_PCH_LPC_SERIRQ_CNT, (UINT8) ~B_PCH_LPC_SERIRQ_CNT_SIRQMD);
  }
}

/**
  Clear RTC PWR STS.
**/
VOID
ClearRtcPwrSts (
  VOID
  )
{
  UINTN                                 PciPmcRegBase;

  PciPmcRegBase = MmPciBase (
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_PMC,
                    PCI_FUNCTION_NUMBER_PCH_PMC
                    );
  ///
  /// PCH BIOS Spec Section 19.8.1 RTC Resets
  /// The PCH will set the RTC_PWR_STS bit (PMC PCI offset A4h[2]) when the RTCRST# pin goes low.
  /// The System BIOS shouldn't rely on the RTC RAM contents when the RTC_PWR_STS bit is set.
  /// BIOS should clear this bit by writing a 0 to this bit position.
  /// This bit isn't cleared by any reset function.
  ///
  //
  // Set B_PCH_PMC_GEN_PMCON_B_RTC_PWR_STS to 0 to clear it.
  // Don't clear B_PCH_PMC_GEN_PMCON_B_PWR_FLR by accident, since it's RW/1C.
  //
  MmioAnd8 ((UINTN) (PciPmcRegBase + R_PCH_PMC_GEN_PMCON_B), (UINT8) ~(B_PCH_PMC_GEN_PMCON_B_RTC_PWR_STS | B_PCH_PMC_GEN_PMCON_B_PWR_FLR));
}

/**
  The function update pch data hob in the end of PchInit.

  @param[in]      SiPolicy               The SI Policy PPI instance
  @param[in, out] PchConfigHob           The PCH data HOB
**/
VOID
UpdatePchDataHob (
  IN     SI_POLICY_PPI          *SiPolicy,
  IN OUT PCH_CONFIG_HOB         *PchConfigHob
  )
{
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicy;
  PCH_SMBUS_PREMEM_CONFIG     *SmbusPreMemConfig;
  PCH_GENERAL_CONFIG          *PchGeneralConfig;
  PCH_INTERRUPT_CONFIG        *InterruptConfig;
  PCH_SERIAL_IO_CONFIG        *SerialIoConfig;
  PCH_PCIE_CONFIG             *PcieRpConfig;
  PCH_THERMAL_CONFIG          *ThermalConfig;
  PCH_SCS_CONFIG              *ScsConfig;
  PCH_CIO2_CONFIG             *Cio2Config;
  PCH_HDAUDIO_CONFIG          *HdAudioConfig;
  PCH_DMI_CONFIG              *DmiConfig;
  PCH_LOCK_DOWN_CONFIG        *LockDownConfig;
  PCH_PM_CONFIG               *PmConfig;
  PCH_P2SB_CONFIG             *P2sbConfig;
  PCH_USB_CONFIG              *UsbConfig;
  PCH_SATA_CONFIG             *SataConfig;
  PCH_FLASH_PROTECTION_CONFIG *FlashProtectionConfig;
  PCH_LAN_CONFIG              *LanConfig;
  PCH_PORT61H_SMM_CONFIG      *Port61hConfig;
  PCH_SPI_CONFIG              *SpiConfig;
  PCH_ESPI_CONFIG             *EspiConfig;
  EFI_STATUS                  Status;
  UINT32                      Index;

  //
  // Get Policy settings through the SiPreMemPolicy PPI
  //
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicy
             );
  if (Status != EFI_SUCCESS) {
    //
    // SI_PREMEM_POLICY_PPI must be installed at this point
    //
    ASSERT (FALSE);
    return;
  }
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gSmbusPreMemConfigGuid, (VOID *) &SmbusPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gInterruptConfigGuid, (VOID *) &InterruptConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSerialIoConfigGuid, (VOID *) &SerialIoConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPcieRpConfigGuid, (VOID *) &PcieRpConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gThermalConfigGuid, (VOID *) &ThermalConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gScsConfigGuid, (VOID *) &ScsConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gCio2ConfigGuid, (VOID *) &Cio2Config);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gHdAudioConfigGuid, (VOID *) &HdAudioConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gDmiConfigGuid, (VOID *) &DmiConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gLockDownConfigGuid, (VOID *) &LockDownConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gP2sbConfigGuid, (VOID *) &P2sbConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsbConfigGuid, (VOID *) &UsbConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSataConfigGuid, (VOID *) &SataConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gFlashProtectionConfigGuid, (VOID *) &FlashProtectionConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gLanConfigGuid, (VOID *) &LanConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPort61ConfigGuid, (VOID *) &Port61hConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSpiConfigGuid, (VOID *) &SpiConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gEspiConfigGuid, (VOID *) &EspiConfig);
  ASSERT_EFI_ERROR (Status);  

  PchConfigHob->Smbus.NumRsvdSmbusAddresses = SmbusPreMemConfig->NumRsvdSmbusAddresses;
  CopyMem (
    &PchConfigHob->Smbus.RsvdSmbusAddressTable[0],
    &SmbusPreMemConfig->RsvdSmbusAddressTable[0],
    PCH_MAX_SMBUS_RESERVED_ADDRESS
    );

  PchConfigHob->General.Crid = PchGeneralConfig->Crid;
  PchConfigHob->Interrupt.NumOfDevIntConfig = InterruptConfig->NumOfDevIntConfig;
  PchConfigHob->Interrupt.GpioIrqRoute = InterruptConfig->GpioIrqRoute;
  CopyMem (
    &PchConfigHob->Interrupt.DevIntConfig[0],
    &InterruptConfig->DevIntConfig[0],
    PCH_MAX_DEVICE_INTERRUPT_CONFIG * sizeof (PCH_DEVICE_INTERRUPT_CONFIG)
    );
  CopyMem (
    &PchConfigHob->SerialIo.DevMode[0],
    &SerialIoConfig->DevMode[0],
    PCH_SERIALIO_MAX_CONTROLLERS
    );
  PchConfigHob->SerialIo.Gpio = SerialIoConfig->Gpio;
  PchConfigHob->SerialIo.DebugUartNumber = SerialIoConfig->DebugUartNumber;
  PchConfigHob->SerialIo.EnableDebugUartAfterPost = SerialIoConfig->EnableDebugUartAfterPost;
  CopyMem (
    &PchConfigHob->PcieRp.RootPort[0],
    &PcieRpConfig->RootPort[0],
    PCH_MAX_PCIE_ROOT_PORTS * sizeof (PCH_PCIE_ROOT_PORT_CONFIG)
    );
  PchConfigHob->PcieRp.AllowNoLtrIccPllShutdown = PcieRpConfig->AllowNoLtrIccPllShutdown;
  PchConfigHob->Thermal.ThermalDeviceEnable = ThermalConfig->ThermalDeviceEnable;
  PchConfigHob->Scs.ScsEmmcEnabled = ScsConfig->ScsEmmcEnabled;
  PchConfigHob->Scs.ScsEmmcHs400Enabled = ScsConfig->ScsEmmcHs400Enabled;
  PchConfigHob->Scs.ScsEmmcHs400TuningRequired = ScsConfig->ScsEmmcHs400TuningRequired;
  PchConfigHob->Scs.ScsEmmcHs400DllDataValid = ScsConfig->ScsEmmcHs400DllDataValid;
  PchConfigHob->Scs.ScsEmmcHs400DriverStrength = ScsConfig->ScsEmmcHs400DriverStrength;
  PchConfigHob->Cio2.DeviceEnable = Cio2Config->DeviceEnable;
  PchConfigHob->HdAudio.DspEnable = HdAudioConfig->DspEnable;
  PchConfigHob->HdAudio.DspEndpointDmic = HdAudioConfig->DspEndpointDmic;
  PchConfigHob->HdAudio.DspEndpointBluetooth = HdAudioConfig->DspEndpointBluetooth;
  PchConfigHob->HdAudio.DspEndpointI2s = HdAudioConfig->DspEndpointI2s;
  PchConfigHob->HdAudio.DspFeatureMask = HdAudioConfig->DspFeatureMask;
  PchConfigHob->LockDown.GlobalSmi = LockDownConfig->GlobalSmi;
  PchConfigHob->LockDown.BiosInterface = LockDownConfig->BiosInterface;
  PchConfigHob->LockDown.RtcLock = LockDownConfig->RtcLock;
  PchConfigHob->LockDown.BiosLock = LockDownConfig->BiosLock;
  PchConfigHob->P2sb.SbiUnlock = P2sbConfig->SbiUnlock;
  PchConfigHob->P2sb.SbAccessUnlock = P2sbConfig->SbAccessUnlock;
  PchConfigHob->Sata.Enable = SataConfig->Enable;
  PchConfigHob->Sata.TestMode = SataConfig->TestMode;
  PchConfigHob->Espi.BmeMasterSlaveEnabled = EspiConfig->BmeMasterSlaveEnabled;  
  CopyMem (
    &PchConfigHob->Sata.PortSettings[0],
    &SataConfig->PortSettings[0],
    PCH_MAX_SATA_PORTS * sizeof (PCH_SATA_PORT_CONFIG)
    );
  CopyMem (
    &PchConfigHob->Sata.RstPcieStorageRemap[0],
    &SataConfig->RstPcieStorageRemap[0],
    PCH_MAX_RST_PCIE_STORAGE_CR * sizeof (PCH_RST_PCIE_STORAGE_CONFIG)
    );
  CopyMem (
    &PchConfigHob->ProtectRange[0],
    &FlashProtectionConfig->ProtectRange[0],
    PCH_FLASH_PROTECTED_RANGES * sizeof (PROTECTED_RANGE)
    );
  PchConfigHob->Port61hSmm.Enable = Port61hConfig->Enable;

  PchConfigHob->Usb.DelayPdoProgramming = UsbConfig->DelayPdoProgramming;
  if (PchConfigHob->Usb.DelayPdoProgramming == TRUE) {
    PchConfigHob->Usb.Usb2DisabledPorts = 0;
    for (Index = 0; Index < GetPchUsbMaxPhysicalPortNum (); Index++) {
      if (UsbConfig->PortUsb20[Index].Enable == FALSE) {
        PchConfigHob->Usb.Usb2DisabledPorts |= (BIT0 << Index);
      }
    }
    PchConfigHob->Usb.Usb3DisabledPorts = 0;
    for (Index = 0; Index < GetPchXhciMaxUsb3PortNum (); Index++) {
      if (UsbConfig->PortUsb30[Index].Enable == FALSE) {
        PchConfigHob->Usb.Usb3DisabledPorts |= (BIT0 << Index);
      }
    }
  }

  PchConfigHob->Spi.FlashCfgLockDown = SpiConfig->FlashCfgLockDown;
}
/**
  Pch End of PEI callback function. This is the last event before entering DXE and OS in S3 resume.
**/
VOID
PchOnEndOfPei (
  VOID
  )
{
  EFI_STATUS             Status;
  UINTN                  P2sbBase;
  SI_PREMEM_POLICY_PPI   *SiPreMemPolicy;
  SI_POLICY_PPI          *SiPolicy;
  PCH_SERIES             PchSeries;
  EFI_BOOT_MODE          BootMode;
  PCH_P2SB_CONFIG        *P2sbConfig;
  SI_CONFIG              *SiConfig;

  PostCode (0xB40);
  DEBUG ((DEBUG_INFO, "PchOnEndOfPei after memory PEI module - Start\n"));

  PchSeries = GetPchSeries ();

  //
  // Get Policy settings through the SiPolicy PPI
  //
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicy
             );
  if (Status != EFI_SUCCESS) {
    //
    // SI_POLICY_PPI must be installed at this point
    //
    ASSERT (FALSE);
    return;
  }

  //
  // Get Policy settings through the SiPreMemPolicy PPI
  //
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicy
             );
  if (Status != EFI_SUCCESS) {
    //
    // SI_PREMEM_POLICY_PPI must be installed at this point
    //
    ASSERT (FALSE);
    return;
  }

  //
  // Clear RTC PWR STS in end of PEI so others won't miss the status
  //
  ClearRtcPwrSts ();

  //
  // Init thermal device and lock down settings.
  //
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSiConfigGuid, (VOID *) &SiConfig);
  ASSERT_EFI_ERROR (Status);

  PostCode (0xB41);
  Status = PchThermalInit (SiPolicy, SiConfig->TempMemBaseAddr);

  //
  // Init Memory Throttling.
  // Memory Throttling doesn't depend on PCH thermal.
  //
  PostCode (0xB42);
  PchMemoryThrottlingInit (SiPolicy);

  WdtEndOfPeiCallback ();

  P2sbBase = MmPciBase (
               DEFAULT_PCI_BUS_NUMBER_PCH,
               PCI_DEVICE_NUMBER_PCH_P2SB,
               PCI_FUNCTION_NUMBER_PCH_P2SB
               );
  PostCode (0xB4D);
  Status = PchTraceHubOnEndOfPei (SiPreMemPolicy);

#ifdef FSP_FLAG
  //
  // Configure root port function number mapping
  // For FSP, execute RPFN mapping here before PCI enumeration.
  //
  Status = PchConfigureRpfnMapping ();
  ASSERT_EFI_ERROR (Status);
#endif

  //
  // Configure Pm timer
  // This must be done after uCode PM timer emulation.
  //
  ConfigurePmTimer (SiPolicy);

  //
  // Lock PMC settings
  //
  LockPmcSettings (SiPolicy);

  //
  // SKL PCH BWG 16.6. PCH-LP GPP_A_12 Special Handling
  //
  if (PchSeries == PchLp) {
    GpioA12SpecialHandling ();
  }

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  //
  // For S3 path:
  //   If it's PCH A0 stepping, skip the P2SB SBI lock and Hidden.
  //   else, lock SBI, hide P2SB and do P2SB PSF configuration space disable.
  // For S4/S5 path:
  //   Hide P2SB only.
  //   If FSP is supported, also lock SBI and do P2SB PSF configuration space disable.
  //
  Status = GetConfigBlock ((VOID *) SiPolicy, &gP2sbConfigGuid, (VOID *) &P2sbConfig);
  ASSERT_EFI_ERROR (Status);

  if (BootMode == BOOT_ON_S3_RESUME) {
    ///
    /// Lock down the P2sb SBI before going into OS.
    /// This only apply to PCH B0 onward.
    ///
    ConfigureP2sbSbiLock ((BOOLEAN) P2sbConfig->SbiUnlock);
    ///
    /// Hide P2SB controller in the end of PEI.
    ///
    PchHideP2sb (P2sbBase);
  } else {
    ///
    /// Hide P2SB controller in the end of PEI.
    ///
    PchHideP2sb (P2sbBase);
  }

  if (BootMode == BOOT_ON_S3_RESUME) {
    if ((BOOLEAN)P2sbConfig->SbAccessUnlock != TRUE) {
      RemoveSidebandAccess ();
    }
  }
#ifndef FSP_FLAG
  if (BootMode == BOOT_ON_S3_RESUME) {
    ConfigureSerialIoAtS3Resume (SiPolicy);
  }
#endif
  PostCode (0xB47);
  DEBUG ((DEBUG_INFO, "PchOnEndOfPei after memory PEI module - End\n"));
}

/**
  Pch init after memory PEI module

  @param[in] SiPolicy     The Silicon Policy PPI instance

  @retval None
**/
VOID
EFIAPI
PchInit (
  IN  SI_POLICY_PPI  *SiPolicy
  )
{
  EFI_STATUS                            Status;
  PCH_PCIE_DEVICE_OVERRIDE              *PcieDeviceTable;
  VOID                                  *HobPtr;
  UINTN                                 Count;
  PCH_SERIES                            PchSeries;
  BOOLEAN                               RstPcieStorageRemapEnabled;
  PCH_SATA_CONFIG                       *SataConfig;
  PCH_USB_CONFIG                        *UsbConfig;
  PCH_ESPI_CONFIG                       *EspiConfig;
  PCH_LOCK_DOWN_CONFIG                  *LockDownConfig;
  PCH_PCIE_CONFIG                       *PcieRpConfig;
  PCH_CONFIG_HOB                        *PchConfigHob;
  SI_CONFIG                             *SiConfig;

  PostCode (0xB00); // PCH API Entry
  DEBUG ((DEBUG_INFO, "PchInit - Start\n"));

  PchSeries = GetPchSeries ();

#ifndef FSP_FLAG
  //
  // Install PEI SMM Control PPI
  //
  Status = PchSmmControlInit ();
#endif

  //
  // Check if ME has the right HSIO Settings and sync with ME if required
  //
  Status = PchHsioChipsetInitProg (TRUE);
  ASSERT_EFI_ERROR (Status);

  //
  // HSIO programming
  //
  PchHsioBiosProg (SiPolicy);

  //
  // Build PchDeviceTableHob
  //
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPcieRpConfigGuid, (VOID *) &PcieRpConfig);
  ASSERT_EFI_ERROR (Status);
  PcieDeviceTable = (PCH_PCIE_DEVICE_OVERRIDE *) PcieRpConfig->PcieDeviceOverrideTablePtr;
  if (PcieDeviceTable != NULL) {
    for (Count = 0; PcieDeviceTable[Count].DeviceId != 0; Count++) {
    }
    DEBUG ((DEBUG_INFO, "PCH Installing PcieDeviceTable HOB (%d entries)\n", Count));
    HobPtr = BuildGuidDataHob (
               &gPchDeviceTableHobGuid,
               PcieDeviceTable,
               Count * sizeof (PCH_PCIE_DEVICE_OVERRIDE)
               );
    ASSERT (HobPtr != 0);
  }

  Status = GetConfigBlock ((VOID *) SiPolicy, &gLockDownConfigGuid, (VOID *) &LockDownConfig);
  ASSERT_EFI_ERROR (Status);
  //
  // EISS configuration
  //
  ConfigureSpiEiss (LockDownConfig);

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSataConfigGuid, (VOID *) &SataConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSiConfigGuid, (VOID *) &SiConfig);
  ASSERT_EFI_ERROR (Status);

  RstPcieStorageRemapEnabled  = IsRstPcieStorageRemapEnabled (&SataConfig->RstPcieStorageRemap[0]);

  if (PchSeries == PchH) {
    Status = EarlyConfigurePchHSata (
               SataConfig,
               RstPcieStorageRemapEnabled,
               SiConfig->TempMemBaseAddr
               );
    if (Status == EFI_SUCCESS) {
      ConfigurePchHSata (
        SataConfig,
        SiConfig->TempMemBaseAddr
        );
    }
  } else {
    Status = EarlyConfigurePchLpSata (
               SataConfig,
               RstPcieStorageRemapEnabled,
               SiConfig->TempMemBaseAddr
               );
    if (Status == EFI_SUCCESS) {
      ConfigurePchLpSata (
        SataConfig,
        SiConfig->TempMemBaseAddr
        );
    }
  }

  PchConfigureClkreqMapping (SiPolicy);

  //
  // Initialize LAN
  // This may cause platform reset if GbE enable policy changed
  //
  PchConfigureLan (SiPolicy, SiConfig->TempMemBaseAddr);


  Status = PchInitRootPorts (SiPolicy, SiConfig->TempPciBusMin, SiConfig->TempPciBusMax);
  ASSERT_EFI_ERROR (Status);

  PchPsfDisableP2pDecoding ();

  //
  // Program SVID and SID of PCH devices.
  // Program SVID and SID before most PCH device init since some device might be locked after init.
  //
  PostCode (0xB02);
  PchProgramSvidSid (SiPolicy);

  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsbConfigGuid, (VOID *) &UsbConfig);
  ASSERT_EFI_ERROR (Status);

  // Tune the USB 2.0 high-speed signals quality.
  // This is done before USB Initialization because the PMC XRAM has
  // to be filled up with USB2 AFE settings followed by HSIO settings
  // before it is locked
  //
  PostCode (0xB03);
  Usb2AfeProgramming (UsbConfig, SiConfig->TempMemBaseAddr);

  //
  // Configure USB3 ModPHY turning.
  //
  PostCode (0xB04);
  XhciUsb3Tune (UsbConfig);

  //
  // Configure PCH xHCI
  //
  PostCode (0xB05);
  Status = ConfigureXhci (SiPolicy, SiConfig->TempMemBaseAddr);

  //
  // Configure PCH OTG (xDCI)
  //
  PostCode (0xB08);
  Status = ConfigureXdci (SiPolicy, SiConfig->TempMemBaseAddr);

  //
  // Init Serial IO
  //
  ConfigureSerialIoPei (SiPolicy);

  //
  // Configure DMI
  //
  PostCode (0xB0A);
  PchDmiAndOpDmiInit (SiPolicy);
  //
  // Configure P2SB
  //
  PostCode (0xB0B);
  Status = PchP2sbConfigure (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  //
  // Configure PSTH
  //
  Status = PchPsthConfigure (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  //
  // Configure IOAPIC
  //
  PostCode (0xB0C);
  Status = PchIoApicInit (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  //
  // Configure interrupts.
  //
  PostCode (0xB0D);
  Status = PchConfigureInterrupts (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  //
  // Configure PCH xHCI after initialization
  //
  PostCode (0xB07);
  Status = ConfigureXhciAfterInit (SiPolicy, SiConfig->TempMemBaseAddr);
  //
  // Initialize HD-Audio
  //
  PostCode (0xB0E);
  Status = PchHdAudioInit (SiPolicy, SiConfig->TempMemBaseAddr);
  //
  //  SCS devices handling
  //
  if (PchSeries == PchLp) {
    PostCode (0xB13);
    Status = PchScsInit (SiPolicy, SiConfig->TempMemBaseAddr);
  }

  //
  // Initialize Integrated Sensor Hub (ISH)
  //
  PostCode (0xB14);
  Status = PchIshInit (SiPolicy);

  //
  // Configure GPIO PM settings
  //
  Status = PchGpioConfigurePm (SiPolicy);

  //
  // Configure RTC
  //
  Status = PchRtcConfigure (SiPolicy);

  //
  // Configure SMBUS
  //
  PostCode (0xB15);
  Status = PchSmbusConfigure (SiPolicy);

  //
  // Configure PM settings
  //
  Status = PchPmInit (SiPolicy);

  //
  // Configure Serial IRQ
  //
  PchConfigureSerialIrq (SiPolicy);

  //
  // Configure SPI after memory
  //
  ConfigureSpiAfterMem (SiPolicy);

  //
  // Configure eSPI after memory
  //
  Status = GetConfigBlock ((VOID *) SiPolicy, &gEspiConfigGuid, (VOID *) &EspiConfig);
  ASSERT_EFI_ERROR (Status);
  ConfigureEspi (EspiConfig);

  //
  // Install I2C protocol for PEI use.
  //
  InstallI2cMasterPpi (PchSerialIoIndexI2C0);

  //
  // Finalize CIO2 configuration: power off CSI2 HC core logic and lock registers
  //
  if (PchSeries == PchLp) {
    //
    // Configure CIO2 device
    //
    PostCode (0xB16);
    PchCio2Init (SiPolicy);
    //
    // Finalize CIO2 configuration: power off CSI2 HC core logic and lock registers
    //
    PchCio2FinalizeDeviceConfiguration (SiPolicy, SiConfig->TempMemBaseAddr);
  } else {
    // there is no Cio2 in PchH
    ConfigurePmcWhenCio2Disabled (TRUE);
  }

  ///
  /// Create Storage Info Hob used by Rst remapping
  ///
  CreateStorageInfoHob (SiPolicy, SiConfig->TempPciBusMin, SiConfig->TempPciBusMax);

  PchConfigHob = BuildGuidHob (&gPchConfigHobGuid, sizeof (PCH_CONFIG_HOB));
  ASSERT (PchConfigHob != 0);
  UpdatePchDataHob (SiPolicy, PchConfigHob);

  PostCode (0xB7F);  // PCH API Exit
  DEBUG ((DEBUG_INFO, "PchInit - End\n"));
}
