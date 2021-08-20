/** @file
  Header file for PchPsfPrivateLib.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 Intel Corporation.

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
#ifndef _PCH_PSF_PRIVATE_LIB_H_
#define _PCH_PSF_PRIVATE_LIB_H_

/**
  Hide CIO2 devices PciCfgSpace at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfHideCio2Device (
  VOID
  );

/**
  Disable CIO2 device at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfDisableCio2Device (
  VOID
  );

/**
  Disable HDAudio device at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfDisableHdaDevice (
  VOID
  );

/**
  Disable xDCI device at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfDisableXdciDevice (
  VOID
  );

/**
  Disable xHCI device at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfDisableXhciDevice (
  VOID
  );

/**
  Disable SATA device at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfDisableSataDevice (
  VOID
  );

typedef enum {
  PchPsfEmmc = 0,
  PchPsfSdio,
  PchPsfSdcard,
  PchPsfUfs,
  PchPsfMaxScsDevNum
} PCH_PSF_SCS_DEV_NUM;

/**
  Disable SCS device at PSF level

  @param[in] ScsDevNum   SCS Device

  @retval None
**/
VOID
PsfDisableScsDevice (
  IN PCH_PSF_SCS_DEV_NUM  ScsDevNum
  );

/**
  Disable SCS devices BAR1 PSF level

  @param[in] ScsDevNum   SCS Device

  @retval None
**/
VOID
PsfDisableScsBar1 (
  IN PCH_PSF_SCS_DEV_NUM  ScsDevNum
  );

/**
  Disable ISH device at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfDisableIshDevice (
  VOID
  );

/**
  Disable ISH BAR1 at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfDisableIshBar1 (
  VOID
  );

/**
  Disable GbE device at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfDisableGbeDevice (
  VOID
  );

/**
  Disable SMBUS device at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfDisableSmbusDevice (
  VOID
  );

/**
  Disable Thermal device at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfDisableThermalDevice (
  VOID
  );

/**
  Hide Thermal device PciCfgSpace at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfHideThermalDevice (
  VOID
  );

/**
  Hide TraceHub ACPI devices PciCfgSpace at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfHideTraceHubAcpiDevice (
  VOID
  );

/**
  This procedure will hide TraceHub PciCfgSpace at PSF level

  @retval None
**/
VOID
PsfHideTraceHubDevice (
  VOID
  );

/**
  This procedure will reveal TraceHub PciCfgSpace at PSF level

  @retval None
**/
VOID
PsfRevealTraceHubDevice (
  VOID
  );

/**
  This procedure will disable TraceHub device at PSF level

  @param[in] None

  @retval None
**/
VOID
PsfDisableTraceHubDevice (
  VOID
  );

/**
  Re-enable PCIe Root Port at PSF level after it was disabled

  @param[in] RpIndex        PCIe Root Port Index (0 based)

  @retval None
**/
VOID
PsfEnablePcieRootPort (
  IN UINT32  RpIndex
  );

/**
  Disable PCIe Root Port at PSF level

  @param[in] RpIndex        PCIe Root Port Index (0 based)

  @retval None
**/
VOID
PsfDisablePcieRootPort (
  IN UINT32  RpIndex
  );

/**
  Disable PCIe Root Port at PSF level.
  This function will also perform S3 boot script programming

  @param[in] RpIndex        PCIe Root Port Index (0 based)

  @retval None
**/
VOID
PsfDisablePcieRootPortWithS3BootScript (
  IN UINT32  RpIndex
  );

/**
  Program PSF grant counts for PCI express depending on controllers configuration

  @param[in] Controller        PCIe controller index
  @param[in] ControllerConfig  Port configuration of controller

  @retval Status
**/
EFI_STATUS
PsfConfigurePcieGrantCounts (
  UINT8 Controller,
  UINT8 ControllerConfig
  );

/**
  Disable ISM NP Completion Tracking for GbE PSF port

  @param[in] None

  @retval None
**/
VOID
PsfDisableIsmNpCompletionTrackForGbe (
  VOID
  );

/**
  Program PSF EOI Multicast configuration

  @param[in] None

  @retval None
**/
VOID
PsfSetEoiMulticastConfiguration (
  VOID
  );

/**
  This function enables EOI message forwarding in PSF for PCIe ports
  for cases where IOAPIC is present behind this root port.

  @param[in] RpIndex        Root port index (0 based)

  @retval Status
**/
EFI_STATUS
PsfConfigurEoiForPciePort (
  IN  UINT32   RpIndex
  );

/**
  Reload default RP PSF device number and function number.
  The PSF register doesn't got reset after system reset, which will result in mismatch between
  PSF register setting and PCIE PCR PCD register setting. Reset PSF register in early phase
  to avoid cycle decoding confusing.

  @param[in] None

  @retval Status
**/
VOID
PsfReloadDefaultPcieRpDevFunc (
  VOID
  );

/**
  Assign new function number for PCIe Port Number.
  This function will also perform S3 boot script programming

  @param[in] RpIndex        PCIe Root Port Index (0 based)
  @param[in] NewFunction    New Function number

  @retval None
**/
VOID
PsfSetPcieFunctionWithS3BootScript (
  IN UINT32  RpIndex,
  IN UINT32  NewFunction
  );

/**
  This function enables PCIe Relaxed Order in PSF

  @param[in] None

  @retval None
**/
VOID
PsfEnablePcieRelaxedOrder (
  VOID
  );

/**
  Configure PSF power management.
  Must be called after all PSF configuration is completed.

  @param[in] None

  @retval None
**/
VOID
PsfConfigurePowerManagement (
  VOID
  );

/**
  Enable VTd support in PSF.

  @param[in] None

  @retval None
**/
VOID
PchPsfEnableVtd (
  VOID
  );

/**
  Disable PSF address-based peer-to-peer decoding.
**/
VOID
PchPsfDisableP2pDecoding (
  VOID
  );


#endif // _PCH_PSF_PRIVATE_LIB_H_
