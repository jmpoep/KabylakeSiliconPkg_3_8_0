/** @file
  This file is SampleCode of the library for Intel PCH PEI Policy initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

#include <Library/DebugLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/FspCommonLib.h>
#include <Library/ConfigBlockLib.h>
#include <FspmUpd.h>
#include <Library/PchSerialIoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

/**
  This function performs PCH PEI Policy update in pre-memory.

  @param[in, out] SiPreMemPolicy  The SI PreMem Policy PPI instance
  @param[in]      FspmUpd         The pointer of MemoryInitUpd

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
FspUpdatePeiPchPolicyPreMem (
  IN OUT SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN     FSPM_UPD                 *FspmUpd
  )
{
  EFI_STATUS                      Status;
  UINTN                           Index;
  UINT8                           NumRsvdSmbusTable;
  UINT8                           *RsvdSmbusTable;
  PCH_TRACE_HUB_PREMEM_CONFIG     *TraceHubPreMemConfig;
  PCH_SMBUS_PREMEM_CONFIG         *SmbusPreMemConfig;
  PCH_DCI_PREMEM_CONFIG           *DciPreMemConfig;
  PCH_HPET_PREMEM_CONFIG          *HpetPreMemConfig;
  PCH_HSIO_PCIE_PREMEM_CONFIG     *HsioPciePreMemConfig;
  PCH_HSIO_SATA_PREMEM_CONFIG     *HsioSataPreMemConfig;
  PCH_HSIO_PREMEM_CONFIG          *HsioPreMemConfig;
  PCH_LPC_PREMEM_CONFIG           *LpcPreMemConfig;
  PCH_GENERAL_PREMEM_CONFIG       *PchGeneralPreMemConfig;
  PCH_WDT_PREMEM_CONFIG           *WdtPreMemConfig;
  PCH_PCIE_RP_PREMEM_CONFIG       *PcieRpPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gTraceHubPreMemConfigGuid, (VOID *) &TraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gSmbusPreMemConfigGuid, (VOID *) &SmbusPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gDciPreMemConfigGuid, (VOID *) &DciPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gHpetPreMemConfigGuid, (VOID *) &HpetPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gHsioPciePreMemConfigGuid, (VOID *) &HsioPciePreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gHsioSataPreMemConfigGuid, (VOID *) &HsioSataPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gHsioPreMemConfigGuid, (VOID *) &HsioPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gLpcPreMemConfigGuid, (VOID *) &LpcPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPchGeneralPreMemConfigGuid, (VOID *) &PchGeneralPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gWatchDogPreMemConfigGuid, (VOID *) &WdtPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPcieRpPreMemConfigGuid, (VOID *) &PcieRpPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  //
  // Update TraceHub policies
  //
  TraceHubPreMemConfig->EnableMode  = (FspmUpd->FspmConfig.EnableTraceHub == 0) ? 0 : 2;
  TraceHubPreMemConfig->MemReg0Size = FspmUpd->FspmConfig.TraceHubMemReg0Size;
  TraceHubPreMemConfig->MemReg1Size = FspmUpd->FspmConfig.TraceHubMemReg1Size;

  //
  // Update Smbus policies
  //
  SmbusPreMemConfig->Enable                = FspmUpd->FspmConfig.SmbusEnable;
  SmbusPreMemConfig->ArpEnable             = FspmUpd->FspmConfig.SmbusArpEnable;
  SmbusPreMemConfig->DynamicPowerGating    = FspmUpd->FspmTestConfig.SmbusDynamicPowerGating;
  SmbusPreMemConfig->SpdWriteDisable       = FspmUpd->FspmTestConfig.SmbusSpdWriteDisable;
  SmbusPreMemConfig->SmbusIoBase           = FspmUpd->FspmConfig.PchSmbusIoBase;
  SmbusPreMemConfig->NumRsvdSmbusAddresses = FspmUpd->FspmConfig.PchNumRsvdSmbusAddresses;

  if (FspmUpd->FspmConfig.PchNumRsvdSmbusAddresses != 0) {
    NumRsvdSmbusTable = FspmUpd->FspmConfig.PchNumRsvdSmbusAddresses;
    RsvdSmbusTable = (UINT8 *)FspmUpd->FspmConfig.RsvdSmbusAddressTablePtr;
    ZeroMem (
      SmbusPreMemConfig->RsvdSmbusAddressTable,
      PCH_MAX_SMBUS_RESERVED_ADDRESS * sizeof (UINT8)
      );
    CopyMem (
      SmbusPreMemConfig->RsvdSmbusAddressTable,
      RsvdSmbusTable,
      NumRsvdSmbusTable * sizeof (UINT8)
      );
  }

  //
  // Update Dci policies
  //
  DciPreMemConfig->DciEn = FspmUpd->FspmTestConfig.PchDciEn;

  //
  // Update HPET policies
  //
  HpetPreMemConfig->Enable         = FspmUpd->FspmConfig.PchHpetEnable;
  HpetPreMemConfig->BdfValid       = FspmUpd->FspmConfig.PchHpetBdfValid;
  HpetPreMemConfig->BusNumber      = FspmUpd->FspmConfig.PchHpetBusNumber;
  HpetPreMemConfig->DeviceNumber   = FspmUpd->FspmConfig.PchHpetDeviceNumber;
  HpetPreMemConfig->FunctionNumber = FspmUpd->FspmConfig.PchHpetFunctionNumber;
  HpetPreMemConfig->Base           = FspmUpd->FspmConfig.PchHpetBase;

  //
  // Update PCIE RP policies
  //
  PcieRpPreMemConfig->RpEnabledMask = FspmUpd->FspmConfig.PcieRpEnableMask & ((1 << KBL_PCH_H_PCIE_MAX_ROOT_PORTS) - 1);

  //
  // Update HSIO PCIE policies
  //
  HsioPciePreMemConfig->PciePllSsc = FspmUpd->FspmConfig.PchPmPciePllSsc;
  for (Index = 0; Index < KBL_PCH_H_PCIE_MAX_ROOT_PORTS; Index ++) {
    HsioPciePreMemConfig->Lane[Index].HsioRxSetCtleEnable           = FspmUpd->FspmConfig.PchPcieHsioRxSetCtleEnable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioRxSetCtle                 = FspmUpd->FspmConfig.PchPcieHsioRxSetCtle[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmpEnable  = FspmUpd->FspmConfig.PchPcieHsioTxGen1DownscaleAmpEnable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmp        = FspmUpd->FspmConfig.PchPcieHsioTxGen1DownscaleAmp[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen2DownscaleAmpEnable  = FspmUpd->FspmConfig.PchPcieHsioTxGen2DownscaleAmpEnable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen2DownscaleAmp        = FspmUpd->FspmConfig.PchPcieHsioTxGen2DownscaleAmp[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen3DownscaleAmpEnable  = FspmUpd->FspmConfig.PchPcieHsioTxGen3DownscaleAmpEnable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen3DownscaleAmp        = FspmUpd->FspmConfig.PchPcieHsioTxGen3DownscaleAmp[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmphEnable        = FspmUpd->FspmConfig.PchPcieHsioTxGen1DeEmphEnable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmph              = FspmUpd->FspmConfig.PchPcieHsioTxGen1DeEmph[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph3p5Enable     = FspmUpd->FspmConfig.PchPcieHsioTxGen2DeEmph3p5Enable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph3p5           = FspmUpd->FspmConfig.PchPcieHsioTxGen2DeEmph3p5[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph6p0Enable     = FspmUpd->FspmConfig.PchPcieHsioTxGen2DeEmph6p0Enable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph6p0           = FspmUpd->FspmConfig.PchPcieHsioTxGen2DeEmph6p0[Index];
  }

  //
  // Update HSIO SATA policies
  //
  for (Index = 0; Index < PCH_MAX_SATA_PORTS; Index ++) {
    HsioSataPreMemConfig->PortLane[Index].HsioRxGen1EqBoostMagEnable    = FspmUpd->FspmConfig.PchSataHsioRxGen1EqBoostMagEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioRxGen1EqBoostMag          = FspmUpd->FspmConfig.PchSataHsioRxGen1EqBoostMag[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioRxGen2EqBoostMagEnable    = FspmUpd->FspmConfig.PchSataHsioRxGen2EqBoostMagEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioRxGen2EqBoostMag          = FspmUpd->FspmConfig.PchSataHsioRxGen2EqBoostMag[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioRxGen3EqBoostMagEnable    = FspmUpd->FspmConfig.PchSataHsioRxGen3EqBoostMagEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioRxGen3EqBoostMag          = FspmUpd->FspmConfig.PchSataHsioRxGen3EqBoostMag[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DownscaleAmpEnable  = FspmUpd->FspmConfig.PchSataHsioTxGen1DownscaleAmpEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DownscaleAmp        = FspmUpd->FspmConfig.PchSataHsioTxGen1DownscaleAmp[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DownscaleAmpEnable  = FspmUpd->FspmConfig.PchSataHsioTxGen2DownscaleAmpEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DownscaleAmp        = FspmUpd->FspmConfig.PchSataHsioTxGen2DownscaleAmp[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DownscaleAmpEnable  = FspmUpd->FspmConfig.PchSataHsioTxGen3DownscaleAmpEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DownscaleAmp        = FspmUpd->FspmConfig.PchSataHsioTxGen3DownscaleAmp[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DeEmphEnable        = FspmUpd->FspmConfig.PchSataHsioTxGen1DeEmphEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DeEmph              = FspmUpd->FspmConfig.PchSataHsioTxGen1DeEmph[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DeEmphEnable        = FspmUpd->FspmConfig.PchSataHsioTxGen2DeEmphEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DeEmph              = FspmUpd->FspmConfig.PchSataHsioTxGen2DeEmph[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DeEmphEnable        = FspmUpd->FspmConfig.PchSataHsioTxGen3DeEmphEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DeEmph              = FspmUpd->FspmConfig.PchSataHsioTxGen3DeEmph[Index];
  }

  //
  // Update HSIO policies
  //
  HsioPreMemConfig->ChipsetInitMessage                                  = FspmUpd->FspmTestConfig.ChipsetInitMessage;
  HsioPreMemConfig->BypassPhySyncReset                                  = FspmUpd->FspmTestConfig.BypassPhySyncReset;

  //
  // Update LPC policies
  //
  LpcPreMemConfig->EnhancePort8xhDecoding = FspmUpd->FspmConfig.PchLpcEnhancePort8xhDecoding;

  //
  // Update Pch General Premem policies
  //
  PchGeneralPreMemConfig->AcpiBase    = FspmUpd->FspmConfig.PchAcpiBase;
  PchGeneralPreMemConfig->Port80Route = FspmUpd->FspmConfig.PchPort80Route;

  //
  // Update Wdt policies
  //
  WdtPreMemConfig->DisableAndLock = FspmUpd->FspmTestConfig.WdtDisableAndLock;


  return EFI_SUCCESS;
}
