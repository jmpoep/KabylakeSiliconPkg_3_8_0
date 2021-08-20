/** @file
  This driver does SA PCI Express initialization.

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
  - 1) PCI Express Base Specification, www.pcisig.com
**/
#include <Private/Library/SaPcieInitLib.h>
#include <Register/Msr.h>
#include <CpuRegs.h>
#include <CpuAccess.h>
#include <Library/CpuPlatformLib.h>
#include <Library/SaPlatformLib.h>

/**
  PCI Express Post Memory Initialization.

  @param[in] PCIE_PEI_PREMEM_CONFIG    *PciePeiPreMemConfig
  @param[in] PCIE_PEI_CONFIG           *PciePeiConfig

  @retval EFI_SUCCESS     - Pci Express successfully started and ready to be used
  @exception EFI_UNSUPPORTED - Pci Express can't be initialized
**/
EFI_STATUS
PciExpressInitPostMem (
  IN PCIE_PEI_PREMEM_CONFIG    *PciePeiPreMemConfig,
  IN PCIE_PEI_CONFIG           *PciePeiConfig
  )
{
  EFI_STATUS  Status;
  UINTN       McD0BaseAddress;
  UINT32      EgressPortBar;
  UINT32      MchBar;
  UINT32      PciExpressBar;
  UINT32      DmiBar;
  CPU_FAMILY  CpuFamilyId;
  CPU_SKU     CpuSku;

  DEBUG ((DEBUG_INFO, "Initializing PciExpress PostMem\n"));
  CpuFamilyId = GetCpuFamily ();
  CpuSku = GetCpuSku ();

  /**
   The SA Represents Component ID 1 (CID1), while the PCH represents
   Component ID 2 (CID2).  This code will completely configure both Components
   CID1 Integrated Ports:
      Egress Port = Port 0
      DMI Port    = Port 1
      Peg Port10  = Port 2
      Peg Port11  = Port 3
      Peg Port12  = Port 4
   CID2 Integated Ports:
      Egress Port = Port 0
      Root Port 1 = Port 1
      Root Port 2 = Port 2
      Root Port 3 = Port 3
      Root Port 4 = Port 4
      Azalia      = Port 5

   Get BAR registers
  **/
  McD0BaseAddress   = MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN);
  PciExpressBar     = (UINT32) MmioRead32 (McD0BaseAddress + R_SA_PCIEXBAR) & (B_SA_PCIEXBAR_PCIEXBAR_MASK | B_SA_PCIEXBAR_ADMSK128_MASK | B_SA_PCIEXBAR_ADMSK64_MASK);
  EgressPortBar     = (UINT32) MmioRead32 (McD0BaseAddress + R_SA_PXPEPBAR) &~BIT0;
  MchBar            = (UINT32) MmioRead32 (McD0BaseAddress + R_SA_MCHBAR) &~BIT0;
  DmiBar            = (UINT32) MmioRead32 (McD0BaseAddress + R_SA_DMIBAR) &~BIT0;

  ///
  /// Configure the Egress Port (0) in CID1
  ///
  Status = Cid1EgressPort0Init (EgressPortBar);

  if (IsPchLinkDmi (CpuFamilyId)) {
    ///
    /// Configure the PEG Ports in CID1
    ///
    Status = Cid1PegPortInit (PciePeiPreMemConfig, PciePeiConfig);
  }

  ///
  /// Configure the SA DMI Port (1) in CID1 and the PCH DMI Port (0) in CID2.
  /// Note that both links must be fully configured before the link
  /// should be checked for negotiation between the 2 CIDs.
  ///
  DEBUG ((DEBUG_INFO, " Going to call Cid1Cid2DmiPortInit\n"));
  Status = Cid1Cid2DmiPortInit (DmiBar, PciePeiConfig);

  ///
  /// Configure the RootComplex Topology in CID1.
  ///
  DEBUG ((DEBUG_INFO, " Going to call Cid1TopologyInit\n"));
  Status = Cid1TopologyInit (EgressPortBar, DmiBar);

  ///
  /// Configure the RootComplex Topology in CID2.
  ///
  DEBUG ((DEBUG_INFO, " Going to call Cid2TopologyInit\n"));
  Status = Cid2TopologyInit (DmiBar);

  return Status;
}

/**
  Additional PEG Programming Steps as in SA BIOS spec

  @param[in] Bus                    - Pci Bus Number
  @param[in] pegDev                 - Pci Device Number
  @param[in] pegFn                  - Pci Func Number
  @param[in] PCIE_PEI_PREMEM_CONFIG - PciePeiPreMemConfig
  @param[in] PCIE_PEI_CONFIG        - PciePeiConfig
**/
VOID
AdditionalPEGProgramStepsBeforeASPM (
  IN  UINT8                          Bus,
  IN  UINT8                          pegDev,
  IN  UINT8                          pegFn,
  IN  PCIE_PEI_PREMEM_CONFIG         *PciePeiPreMemConfig,
  IN PCIE_PEI_CONFIG                 *PciePeiConfig
  )
{
  UINT32                Data32Or;
  UINT32                Data32And;
  UINT32                PegBaseAddress;

  PegBaseAddress = (UINT32) MmPciBase (Bus, pegDev, pegFn);

  ///
  /// Permanently set PEGUESEV[CTS](0x1CC bit14) to 1b during BIOS boot for all the PEG controllers
  ///
  Data32And = 0xFFFFFFFF;
  Data32Or  = BIT14;
  MmioOr32 (PegBaseAddress + 0x1CC, Data32Or);

  ///
  /// Configure the De-emphasis control on PEG
  ///
  Data32And = (UINT32) ~BIT6;
  Data32Or  = (PciePeiConfig->PegDeEmphasis[pegFn] & BIT0) << 6;
  MmioAndThenOr32 (PegBaseAddress + R_SA_PEG_LCTL2_OFFSET, Data32And, Data32Or);

  ///
  ///
  ///
  /// Set 0x22C[31] to 1 before enabling ASPM
  ///
  Data32And = (UINT32) ~(BIT31);
  Data32Or  = (UINT32)   BIT31;
  MmioAndThenOr32 (PegBaseAddress + R_SA_PEG_L0SLAT_OFFSET, Data32And, Data32Or);

  ///
  /// Program 0x250 bit[22:20] to 010b for all the PEG controllers before enabling ASPM
  ///
  Data32And = (UINT32) ~(BIT22 + BIT21 + BIT20);
  Data32Or  = 0x02 << 20;
  MmioAndThenOr32 (PegBaseAddress + 0x250, Data32And, Data32Or);

  ///
  /// Set 0x238 bit29 for PEG controller before enabling ASPM
  ///
  Data32And = 0xFFFFFFFF;
  Data32Or  = BIT29;
  MmioOr32 (PegBaseAddress + 0x238, Data32Or);

  ///
  /// Set PEG Offset 0x1F8 bit16
  ///
  Data32And = 0xFFFFFFFF;
  Data32Or  = BIT16;
  MmioOr32 (PegBaseAddress + 0x1F8, Data32Or);

  ///
  ///
  ///
  ///
  ///
  /// Set PEG Offset 0xC28 [4:0]
  ///
  Data32And = 0xFFFFFFE0;
  Data32Or  = 0x13;
  MmioAndThenOr32 (PegBaseAddress + R_SA_PEG_AFE_PM_TMR_OFFSET, Data32And, Data32Or);
}

