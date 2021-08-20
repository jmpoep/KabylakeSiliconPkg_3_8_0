/** @file
  Initializes Storage and Communication Subsystem Controller.

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

typedef enum {
  PchEmmc = 0,
  PchSdio,
  PchSdcard,
  PchMaxScsControllerNum
} PCH_SCS_DEV_NUM;

typedef struct {
  UINT8  DevNum;
  UINT8  FuncNum;
  UINT8  PortId;
  UINT8  HcDisable;
  UINT16 PciCfgCtr;
  UINT8  Rsvd1[2];
} PCH_SCS_DEVICE_DESCRIPTOR;

GLOBAL_REMOVE_IF_UNREFERENCED PCH_SCS_DEVICE_DESCRIPTOR mScsDevice [PchMaxScsControllerNum] =
{
  {PCI_DEVICE_NUMBER_PCH_SCS_EMMC,  PCI_FUNCTION_NUMBER_PCH_SCS_EMMC, PID_SCS,
   B_PCH_PCR_SCS_GPPRVRW2_EMMC_DIS,  R_PCH_PCR_SCS_PCICFGCTR_EMMC},
  {PCI_DEVICE_NUMBER_PCH_SCS_SDIO,  PCI_FUNCTION_NUMBER_PCH_SCS_SDIO, PID_SCS,
   B_PCH_PCR_SCS_GPPRVRW2_SDIO_SDCARD_DIS,  R_PCH_PCR_SCS_PCICFGCTR_SDIO},
  {PCI_DEVICE_NUMBER_PCH_SCS_SDCARD,  PCI_FUNCTION_NUMBER_PCH_SCS_SDCARD, PID_SCS,
   B_PCH_PCR_SCS_GPPRVRW2_SDIO_SDCARD_DIS,  R_PCH_PCR_SCS_PCICFGCTR_SDCARD}
};

typedef struct {
  UINT32 TxCmdDelayControl1;     // Offset 820h: Tx CMD Delay Control 1
  UINT32 TxCmdDelayControl2;     // Offset 80Ch: Tx CMD Delay Control 2
  UINT32 TxDataDelayControl1;    // Offset 824h: Tx Data Delay Control 1
  UINT32 TxDataDelayControl2;    // Offset 828h: Tx Data Delay Control 2
  UINT32 RxCmdDataDelayControl1; // Offset 82Ch: Rx CMD + Data Delay Control 1
  UINT32 RxCmdDataDelayControl2; // Offset 834h: Rx CMD + Data Delay Control 2
  UINT32 RxStrobeDelayControl;   // Offset 830h: Rx Strobe Delay Control
} PCH_SCS_DEVICE_DLL;

GLOBAL_REMOVE_IF_UNREFERENCED PCH_SCS_DEVICE_DLL mScsDeviceDll [PchMaxScsControllerNum] =
{
  {0x0F, 0x1C282828, 0x090F, 0x1C272828, 0x1C070B13, 0x1C, 0xA0A},    // [0] PchEmmc
  {0, 0, 0, 0, 0, 0, 0},                                              // [1] PchSdio (Deprecated)
  {0xC, 0x22282824, 0x0A13, 0x28272824, 0x07070D0E, 0x0,     0x0}     // [2] PchSdcard
};

/**
  Configure SKL PCH SCS Host Controller Disable

  @param[in] ScsDevNum          SCS Device Number

  @retval None
**/
VOID
ConfigureScsHcDisable (
  IN PCH_SCS_DEV_NUM  ScsDevNum
  )
{
  if (ScsDevNum == PchSdcard) {
    PchPcrAndThenOr32 (
      mScsDevice[ScsDevNum].PortId,
      R_PCH_PCR_SCS_GPPRVRW2,
      (UINT32) ~(mScsDevice[ScsDevNum].HcDisable),
      0
      );
  } else {
    PchPcrAndThenOr32 (
      mScsDevice[ScsDevNum].PortId,
      R_PCH_PCR_SCS_GPPRVRW2,
      (UINT32) ~0,
      mScsDevice[ScsDevNum].HcDisable
      );
  }
}

/**
  Configure SKL PCH SCS Device into D3 state

  @param[in] ScsDevNum          SCS Device Number

  @retval None
**/
VOID
ConfigureScsDevD3 (
  IN PCH_SCS_DEV_NUM  ScsDevNum
  )
{
  UINTN               PciCfgBase;

  PciCfgBase = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, mScsDevice[ScsDevNum].DevNum, mScsDevice[ScsDevNum].FuncNum);

  MmioOr32 (PciCfgBase + R_PCH_SCS_DEV_PCS, B_PCH_SCS_DEV_PCS_PS_D3HOT);

  MmioRead32 (PciCfgBase + R_PCH_SCS_DEV_PCS);
}
/**
  Configure SKL PCH SCS Device BAR1 Disabling

  @param[in] ScsDevNum          SCS Device Number

  @retval None
**/
VOID
ConfigureScsDevBar1Disable (
  IN PCH_SCS_DEV_NUM  ScsDevNum
  )
{
  PchPcrAndThenOr32 (
    mScsDevice[ScsDevNum].PortId,
    mScsDevice[ScsDevNum].PciCfgCtr,
    (UINT32) ~0,
    B_PCH_PCR_SCS_PCICFGCTR_BAR1DIS
    );
}
/**
  Configure SKL PCH eMMC Host HS400 Support
  Set Rx Strobe Delay Control - Rx Strobe Delay DLL 1 if supported
  Set Tx Data Delay Control 1 - Tx Data Delay DLL if supported

  @param[in] SiPolicy                 The SI Policy PPI instance
  @param[in] TempMemBaseAddr          Temporary Memory Base Address for PCI
                                      devices to be used to initialize MMIO
                                      registers.

  @retval None
**/
VOID
ConfigureEmmcHostHs400 (
  IN SI_POLICY_PPI            *SiPolicy,
  IN UINT32                   TempMemBaseAddr
  )
{
  UINTN             EmmcPciBaseAddress;
  UINTN             EmmcMmioBaseAddress;
  UINT32            Data32And;
  UINT32            Data32Or;
  EFI_STATUS        Status;
  PCH_SCS_CONFIG    *ScsConfig;

  DEBUG ((DEBUG_INFO, "ConfigureEmmcHostHs400() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gScsConfigGuid, (VOID *) &ScsConfig);
  ASSERT_EFI_ERROR (Status);

  EmmcPciBaseAddress = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, mScsDevice[PchEmmc].DevNum, mScsDevice[PchEmmc].FuncNum);
  //
  // Since EMMC MMIO Base Address is not defined here yet, a temporary Base Address must be written to EMMC BAR
  //
  EmmcMmioBaseAddress = TempMemBaseAddr;
  //
  // Disable MSE
  //
  MmioAnd32 ((UINTN) (EmmcPciBaseAddress + PCI_COMMAND_OFFSET), (UINT32) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Write temp address to lower base address
  //
  MmioWrite32 (EmmcPciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET, EmmcMmioBaseAddress);
  //
  // Clear upper base address
  //
  MmioWrite32 (EmmcPciBaseAddress + (PCI_BASE_ADDRESSREG_OFFSET + 4), 0);
  //
  // Enable MSE
  //
  MmioOr32 ((UINTN) (EmmcPciBaseAddress + PCI_COMMAND_OFFSET), EFI_PCI_COMMAND_MEMORY_SPACE);

  if (ScsConfig->ScsEmmcHs400Enabled == TRUE) {
    Data32And = (UINT32) ~0;
    Data32Or = B_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_HS400;
  } else {
    Data32And = (UINT32) ~B_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_HS400;
    Data32Or = 0;
  }

  MmioAndThenOr32 (
    EmmcMmioBaseAddress + R_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1,
    Data32And,
    Data32Or
    );

  if ((ScsConfig->ScsEmmcHs400Enabled == TRUE) && (ScsConfig->ScsEmmcHs400DllDataValid == TRUE)) {
    DEBUG ((DEBUG_INFO, "ConfigureEmmcHostHs400() Set Valid Tuning Data\n"));
    ///
    /// Set Rx Strobe Delay Control - Rx Strobe Delay DLL 1 (HS400 Mode)
    /// Set Tx Data Delay Control 1 - Tx Data Delay DLL (HS400 Mode)
    ///
    MmioAndThenOr8 (EmmcMmioBaseAddress + (R_PCH_SCS_DEV_MEM_RX_STROBE_DLL_CNTL), 0, (UINT8) ScsConfig->ScsEmmcHs400RxStrobeDll1);
    MmioAndThenOr8 (EmmcMmioBaseAddress + (R_PCH_SCS_DEV_MEM_RX_STROBE_DLL_CNTL + 1), 0, (UINT8) ScsConfig->ScsEmmcHs400RxStrobeDll1);
    MmioAndThenOr8 (EmmcMmioBaseAddress + (R_PCH_SCS_DEV_MEM_TX_DATA_DLL_CNTL1 + 1), 0, (UINT8) ScsConfig->ScsEmmcHs400TxDataDll);
  }
  //
  // Disable MSE
  //
  MmioAnd32 ((UINTN) (EmmcPciBaseAddress + PCI_COMMAND_OFFSET), (UINT32) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Clear lower base address
  //
  MmioWrite32 (EmmcPciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET, 0);
}

/**
  Configure Storage and Communication Subsystems Controllers (eMMC, SD Card)
  default DLL registers in accordance with values defined in mScsDeviceDll

  @param[in] ScsDevNum                SCS Device Number
  @param[in] TempMemBaseAddr          Temporary Memory Base Address for PCI
                                      devices to be used to initialize MMIO
                                      registers.

  @retval None
**/
VOID
ConfigureScsDefaultDll (
  IN PCH_SCS_DEV_NUM          ScsDevNum,
  IN UINT32                   TempMemBaseAddr
  )
{
  UINTN         PciCfgBase;
  UINTN         ScsDevMmioBaseAddress;

  DEBUG ((DEBUG_INFO, "ConfigureScsDefaultDll() Start, SCS Device = %d\n", ScsDevNum));

  PciCfgBase = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, mScsDevice[ScsDevNum].DevNum, mScsDevice[ScsDevNum].FuncNum);
  //
  // Since SDIO MMIO Base Address is not defined here yet, a temporary Base Address must be written to SDIO BAR
  //
  ScsDevMmioBaseAddress = TempMemBaseAddr;
  //
  // Disable MSE
  //
  MmioAnd32 ((UINTN) (PciCfgBase + PCI_COMMAND_OFFSET), (UINT32) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Write temp address to lower base address
  //
  MmioWrite32 (PciCfgBase + PCI_BASE_ADDRESSREG_OFFSET, ScsDevMmioBaseAddress);
  //
  // Clear upper base address
  //
  MmioWrite32 (PciCfgBase + (PCI_BASE_ADDRESSREG_OFFSET + 4), 0);
  //
  // Enable MSE
  //
  MmioOr32 ((UINTN) (PciCfgBase + PCI_COMMAND_OFFSET), EFI_PCI_COMMAND_MEMORY_SPACE);

  //
  // Set Tx CMD Delay Control 1 (820h) Register
  //
  MmioWrite32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_TX_CMD_DLL_CNTL1, mScsDeviceDll[ScsDevNum].TxCmdDelayControl1);
  //
  // Set Tx CMD Delay Control 2 (80Ch) Register
  //
  MmioWrite32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_TX_CMD_DLL_CNTL2, mScsDeviceDll[ScsDevNum].TxCmdDelayControl2);

  //
  // Set Tx Data Delay Control 1 (824h) Register
  //
  MmioWrite32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_TX_DATA_DLL_CNTL1, mScsDeviceDll[ScsDevNum].TxDataDelayControl1);
  //
  //  Set Tx Data Delay Control 2 (828h) Register
  //
  MmioWrite32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_TX_DATA_DLL_CNTL2, mScsDeviceDll[ScsDevNum].TxDataDelayControl2);

  //
  // Set Rx CMD + Data Delay Control 1 (82Ch) Register
  //
  MmioWrite32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_RX_CMD_DATA_DLL_CNTL1, mScsDeviceDll[ScsDevNum].RxCmdDataDelayControl1);
  //
  // Set Rx CMD + Data Delay Control 2 (834h) Register
  //
  MmioWrite32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_RX_CMD_DATA_DLL_CNTL2, mScsDeviceDll[ScsDevNum].RxCmdDataDelayControl2);

  //
  // Set Rx Strobe Delay Control (830h) Register
  //
  MmioWrite32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_RX_STROBE_DLL_CNTL, mScsDeviceDll[ScsDevNum].RxStrobeDelayControl);

  DEBUG ((DEBUG_INFO, "Tx CMD Delay Control 1 (820h) = 0x%08x\n", MmioRead32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_TX_CMD_DLL_CNTL1)));
  DEBUG ((DEBUG_INFO, "Tx CMD Delay Control 2 (80Ch) = 0x%08x\n", MmioRead32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_TX_CMD_DLL_CNTL2)));
  DEBUG ((DEBUG_INFO, "Tx Data Delay Control 1 (824h) = 0x%08x\n", MmioRead32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_TX_DATA_DLL_CNTL1)));
  DEBUG ((DEBUG_INFO, "Tx Data Delay Control 2 (828h) = 0x%08x\n", MmioRead32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_TX_DATA_DLL_CNTL2)));
  DEBUG ((DEBUG_INFO, "Rx CMD + Data Delay Control 1 (82Ch) = 0x%08x\n", MmioRead32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_RX_CMD_DATA_DLL_CNTL1)));
  DEBUG ((DEBUG_INFO, "Rx CMD + Data Delay Control 2 (834h) = 0x%08x\n", MmioRead32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_RX_CMD_DATA_DLL_CNTL2)));
  DEBUG ((DEBUG_INFO, "Rx Strobe Delay Control (830h) = 0x%08x\n", MmioRead32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_RX_STROBE_DLL_CNTL)));

  //
  // Disable MSE
  //
  MmioAnd32 ((UINTN) (PciCfgBase + PCI_COMMAND_OFFSET), (UINT32) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Clear lower base address
  //
  MmioWrite32 (PciCfgBase + PCI_BASE_ADDRESSREG_OFFSET, 0);
}

/**
  Configure SKL PCH SCS Device (eMMC, SD Card) Clock Source for Rx Path

  @param[in] ScsDevNum                SCS Device Number
  @param[in] TempMemBaseAddr          Temporary Memory Base Address for PCI
                                      devices to be used to initialize MMIO
                                      registers.

  @retval None
**/
VOID
ConfigureScsRxClkSrc (
  IN PCH_SCS_DEV_NUM          ScsDevNum,
  IN UINT32                   TempMemBaseAddr
  )
{
  UINTN         PciCfgBase;
  UINTN         ScsDevMmioBaseAddress;
  PCH_STEPPING  PchStep;

  DEBUG ((DEBUG_INFO, "ConfigureScsRxClkSrc() Start, SCS Device = %d\n", ScsDevNum));

  PchStep   = PchStepping ();

  PciCfgBase = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, mScsDevice[ScsDevNum].DevNum, mScsDevice[ScsDevNum].FuncNum);

  //
  // Since SCS Controller MMIO Base Address is not defined here yet, a temporary Base Address must be written to SCS BAR
  //
  ScsDevMmioBaseAddress = TempMemBaseAddr;
  //
  // Disable MSE
  //
  MmioAnd32 ((UINTN) (PciCfgBase + PCI_COMMAND_OFFSET), (UINT32) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Write temp address to lower base address
  //
  MmioWrite32 (PciCfgBase + PCI_BASE_ADDRESSREG_OFFSET, ScsDevMmioBaseAddress);
  //
  // Clear upper base address
  //
  MmioWrite32 (PciCfgBase + (PCI_BASE_ADDRESSREG_OFFSET + 4), 0);
  //
  // Enable MSE
  //
  MmioOr32 ((UINTN) (PciCfgBase + PCI_COMMAND_OFFSET), EFI_PCI_COMMAND_MEMORY_SPACE);

  if (PchStep < PchLpC0) {
    MmioAndThenOr32 (
      ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_RX_CMD_DATA_DLL_CNTL2,
      (UINT32) ~(BIT17 | BIT16),
      (UINT32) (V_PCH_SCS_DEV_MEM_RX_CMD_DATA_DLL_CNTL2_CLKSRC_RX_CLK_BEFORE << N_PCH_SCS_DEV_MEM_RX_CMD_DATA_DLL_CNTL2_CLKSRC_RX)
      );
  } else {
    MmioAndThenOr32 (
      ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_RX_CMD_DATA_DLL_CNTL2,
      (UINT32) ~(BIT17 | BIT16),
      (UINT32) (V_PCH_SCS_DEV_MEM_RX_CMD_DATA_DLL_CNTL2_CLKSRC_RX_CLK_AUTO << N_PCH_SCS_DEV_MEM_RX_CMD_DATA_DLL_CNTL2_CLKSRC_RX)
      );
  }

  DEBUG ((DEBUG_INFO, "Set Clock Source: Rx CMD + Data Delay Control 2 (834h) = 0x%08x\n", MmioRead32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_RX_CMD_DATA_DLL_CNTL2)));

  //
  // Disable MSE
  //
  MmioAnd32 ((UINTN) (PciCfgBase + PCI_COMMAND_OFFSET), (UINT32) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Clear lower base address
  //
  MmioWrite32 (PciCfgBase + PCI_BASE_ADDRESSREG_OFFSET, 0);
}

/**
  Configure SKL PCH SCS Device (eMMC, SD Card) Capabilities
  via Capabilites Bypass register

  @param[in] ScsDevNum                SCS Device Number
  @param[in] TempMemBaseAddr          Temporary Memory Base Address for PCI
                                      devices to be used to initialize MMIO
                                      registers.

  @retval None
**/
VOID
ConfigureScsCapabilities (
  IN PCH_SCS_DEV_NUM          ScsDevNum,
  IN UINT32                   TempMemBaseAddr
  )
{
  UINTN         PciCfgBase;
  UINTN         ScsDevMmioBaseAddress;
  UINT32        Data32Reg1;
  UINT32        Data32Reg2;

  DEBUG ((DEBUG_INFO, "ConfigureScsCapabilities() Start, SCS Device = %d\n", ScsDevNum));

  Data32Reg1 = 0;
  Data32Reg2 = 0;

  PciCfgBase = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, mScsDevice[ScsDevNum].DevNum, mScsDevice[ScsDevNum].FuncNum);
  //
  // Since EMMC MMIO Base Address is not defined here yet, a temporary Base Address must be written to EMMC BAR
  //
  ScsDevMmioBaseAddress = TempMemBaseAddr;
  //
  // Disable MSE
  //
  MmioAnd32 ((UINTN) (PciCfgBase + PCI_COMMAND_OFFSET), (UINT32) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Write temp address to lower base address
  //
  MmioWrite32 (PciCfgBase + PCI_BASE_ADDRESSREG_OFFSET, ScsDevMmioBaseAddress);
  //
  // Clear upper base address
  //
  MmioWrite32 (PciCfgBase + (PCI_BASE_ADDRESSREG_OFFSET + 4), 0);
  //
  // Enable MSE
  //
  MmioOr32 ((UINTN) (PciCfgBase + PCI_COMMAND_OFFSET), EFI_PCI_COMMAND_MEMORY_SPACE);

  //
  // CAP_BYPASS_REGx_DEFAULTS value keeps HW/Reset defaults of Capabilities Register (SCS MMIO, offset 40h)
  //
  switch (ScsDevNum) {
    case PchEmmc:
      Data32Reg1 = V_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_EMMC_DEFAULTS;
      Data32Reg2 = V_PCH_SCS_DEV_MEM_CAP_BYPASS_REG2_EMMC_DEFAULTS;
      break;
    case PchSdio:
      Data32Reg1 = V_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_SDIO_DEFAULTS;
      Data32Reg2 = V_PCH_SCS_DEV_MEM_CAP_BYPASS_REG2_SDIO_DEFAULTS;
      break;
    case PchSdcard:
      Data32Reg1 = V_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_SDCARD_DEFAULTS;
      Data32Reg2 = V_PCH_SCS_DEV_MEM_CAP_BYPASS_REG2_SDCARD_DEFAULTS;

      //
      // Capabilities Bypass Reg1: Set Slot Type [12:11] to 01b for SDCard
      //
      Data32Reg1 &= ~(B_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_SLOT_TYPE);
      Data32Reg1 |= (V_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_SLOT_TYPE_EMBEDDED << N_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_SLOT_TYPE);
      break;
    case PchMaxScsControllerNum:
    default:
      DEBUG ((DEBUG_ERROR, "ConfigureScsCapabilities() Incorrect SCS Device number!\n"));
  }

  //
  // Capabilities Bypass Reg1: Set Timeout Clock Frequency [27:22] to 000001b for all SCS controllers
  //
  Data32Reg1 &= ~(B_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_TIMEOUT_CLK_FREQ);
  Data32Reg1 |= (V_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_TIMEOUT_CLK_FREQ << N_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_TIMEOUT_CLK_FREQ);

  //
  // Capabilities Bypass Reg1: Set Timer Count for Re-Tuning [20:17] to 1000b for all SCS controllers
  //
  Data32Reg1 &= ~(B_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_TIMER_COUNT);
  Data32Reg1 |= (V_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_TIMER_COUNT << N_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1_TIMER_COUNT);

  MmioWrite32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1, Data32Reg1);
  MmioWrite32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_CAP_BYPASS_REG2, Data32Reg2);

  //
  // Enable Capabilities Bypass
  //
  MmioWrite32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_CAP_BYPASS_CONTROL, V_PCH_SCS_DEV_MEM_CAP_BYPASS_CONTROL_EN);

  DEBUG ((DEBUG_INFO, "Capabilities Bypass Control    (810h) = 0x%08x\n", MmioRead32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_CAP_BYPASS_CONTROL)));
  DEBUG ((DEBUG_INFO, "Capabilities Bypass Register 1 (814h) = 0x%08x\n", MmioRead32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_CAP_BYPASS_REG1)));
  DEBUG ((DEBUG_INFO, "Capabilities Bypass Register 2 (818h) = 0x%08x\n", MmioRead32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_CAP_BYPASS_REG2)));

  DEBUG ((DEBUG_INFO, "Capabilities Register [31:0]  (40h) = 0x%08x\n", MmioRead32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_CAP1)));
  DEBUG ((DEBUG_INFO, "Capabilities Register [63:32] (44h) = 0x%08x\n", MmioRead32 (ScsDevMmioBaseAddress + R_PCH_SCS_DEV_MEM_CAP2)));

  //
  // Disable MSE
  //
  MmioAnd32 ((UINTN) (PciCfgBase + PCI_COMMAND_OFFSET), (UINT32) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Clear lower base address
  //
  MmioWrite32 (PciCfgBase + PCI_BASE_ADDRESSREG_OFFSET, 0);
}

/**
  Configure SKL PCH SCS Device (eMMC, SD Card, SDIO) Power Gating features

  @param[in] ScsDevNum                SCS Device Number

  @retval None
**/
VOID
ConfigureScsPowerGating (
  IN PCH_SCS_DEV_NUM          ScsDevNum
  )
{
  UINTN         PciCfgBase;

  DEBUG ((DEBUG_INFO, "ConfigureScsPowerGating() Start, SCS Device = %d\n", ScsDevNum));

  PciCfgBase = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, mScsDevice[ScsDevNum].DevNum, mScsDevice[ScsDevNum].FuncNum);

  MmioOr16 (
    (UINTN) (PciCfgBase + R_PCH_SCS_DEV_PG_CONFIG),
    (UINT16) (B_PCH_SCS_DEV_PG_CONFIG_SE | B_PCH_SCS_DEV_PG_CONFIG_PGE | B_PCH_SCS_DEV_PG_CONFIG_I3E | B_PCH_SCS_DEV_PG_CONFIG_PMCRE)
    );
}

/**
  Configure SKL PCH SCS Controllers

  @param[in] SiPolicy                 The SI Policy PPI instance
  @param[in] TempMemBaseAddr          Temporary Memory Base Address for PCI
                                      devices to be used to initialize MMIO
                                      registers.
  @retval None
**/
VOID
ConfigureScsControllers (
  IN SI_POLICY_PPI            *SiPolicy,
  IN UINT32                   TempMemBaseAddr
  )
{
  PCH_SERIES        PchSeries;
  PCH_STEPPING      PchStep;
  UINT32            PchPwrmBase;
  EFI_STATUS        Status;
  PCH_SCS_CONFIG    *ScsConfig;

  DEBUG ((DEBUG_INFO, "ConfigureScsControllers() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gScsConfigGuid, (VOID *) &ScsConfig);
  ASSERT_EFI_ERROR (Status);

  PchSeries = GetPchSeries ();
  PchStep   = PchStepping ();

  ///
  /// PCH BIOS Spec Section 28.2 Disabling SCS Controllers
  /// By default all controllers are enabled in hardware.
  ///
  /// Disable SDIO Controller unconditionally
  /// Step 1. Host Controller Disable: Set "IOSF2OCP.GPPRVRW2[2]", PCR[SCS] + 604h bit[2] = 1
  /// Step 2. Put SDIO Device into D3: Program SDIO PCI offset 84h bit[1:0] = 11b
  /// Step 3. PSF Function Disable: Set PCR[PSF_2] + "AGNT_T0_SHDW_PCIEN"[SDIO] [8] = 1
  ///
  ConfigureScsRxClkSrc (PchSdio, TempMemBaseAddr);
  ConfigureScsPowerGating (PchSdio);
  ConfigureScsHcDisable (PchSdio);
  ConfigureScsDevD3 (PchSdio);
  PsfDisableScsDevice (PchPsfSdio);

  ///
  /// Disable eMMC Controller
  /// Step 1. Host Controller Disable: Set "IOSF2OCP.GPPRVRW2[1]", PCR[SCS] + 604h bit [1]=1b
  /// Step 2. Put eMMC Device into D3: Program eMMC PCI offset 84h bit[1:0] = 11b
  /// Step 3. PSF Function Disable: Set PCR[PSF_2] + "AGNT_T0_SHDW_PCIEN"[eMMC] [8] = 1
  ///
  if (ScsConfig->ScsEmmcEnabled == FALSE) {
    ConfigureScsPowerGating (PchEmmc);
    ConfigureScsHcDisable (PchEmmc);
    ConfigureScsDevD3 (PchEmmc);
    PsfDisableScsDevice (PchPsfEmmc);
  }

  ///
  /// Disable SDCARD Controller
  /// Step 1. Put SDCARD Device into D3: Program SDCARD PCI offset 84h bit[1:0] = 11b
  /// Step 2. PSF Function Disable: Set PCR[PSF_2] + "AGNT_T0_SHDW_PCIEN"[SDIO] [8] = 1
  ///
  if (ScsConfig->ScsSdSwitch == PchScsSdDisabled) {
    ConfigureScsPowerGating (PchSdcard);
    ConfigureScsDevD3 (PchSdcard);
    PsfDisableScsDevice (PchPsfSdcard);
  }

  ///
  /// While all SCS controllers are disabled.
  ///
  if ((ScsConfig->ScsEmmcEnabled == FALSE) &&
      (ScsConfig->ScsSdSwitch == PchScsSdDisabled)) {
    ConfigurePmcWhenScsDisabled (TRUE);
    ///
    /// Set PWRMBASE + 0x628 [25] = 1b to disable ISH Controller in PMC
    /// This bit is only available on B0 onward.
    /// No need to clear this non-static PG bit while IP re-enabled since it's reset to 0 when PLTRST.
    ///
    PchPwrmBaseGet (&PchPwrmBase);
    if ((PchSeries == PchLp) && (PchStep >= PchLpB0)) {
      MmioOr32 (PchPwrmBase + R_PCH_PWRM_NST_PG_FDIS_1, B_PCH_PWRM_NST_PG_FDIS_1_SCC_FDIS_PMC);
    }
    return;
  }

  ///
  /// PCH BIOS Spec Section 28.3 Snoop Programming
  /// Set "IOSF2OCP.IOSFCTL[NSNPDIS]", PCR[SCS] + 00h bit[7] = 1
  /// Set "IOSF2OCP.IOSFCTL[MAX_RD_PEND]", PCR[SCS] + 00h bit[3:0] = 0
  /// Set "IOSF2OCP.OCPCTL[NPEN]", PCR[SCS] + 10h bit[0] = 0
  ///
  PchPcrAndThenOr32 (
    PID_SCS,
    R_PCH_PCR_SCS_IOSFCTL,
    (UINT32) ~(B_PCH_PCR_SCS_IOSFCTL_MAX_RD_PEND),
    B_PCH_PCR_SCS_IOSFCTL_NSNPDIS
    );

  PchPcrAndThenOr32 (
    PID_SCS,
    R_PCH_PCR_SCS_OCPCTL,
    (UINT32) ~(B_PCH_PCR_SCS_OCPCTL_NPEN),
    0
    );

  //
  // eMMC Specific Config
  //
  if (ScsConfig->ScsEmmcEnabled == TRUE) {
    DEBUG ((DEBUG_INFO, "eMMC Configuration [DevNum = 0]\n"));

    ConfigureScsCapabilities (PchEmmc, TempMemBaseAddr);
    ConfigureScsDefaultDll (PchEmmc, TempMemBaseAddr);
    ConfigureScsRxClkSrc (PchEmmc, TempMemBaseAddr);

    ///
    /// Enabled or Disable eMMC Host HS400 Support
    ///
    ConfigureEmmcHostHs400 (SiPolicy, TempMemBaseAddr);
  }

  //
  // SD Card Specific Config
  //
  if (ScsConfig->ScsSdSwitch == PchScsSdcardMode) {
    DEBUG ((DEBUG_INFO, "SD Card Configuration [DevNum = 2]\n"));

    ConfigureScsCapabilities (PchSdcard, TempMemBaseAddr);
    ConfigureScsDefaultDll (PchSdcard, TempMemBaseAddr);
    ConfigureScsRxClkSrc (PchSdcard, TempMemBaseAddr);

    ///
    /// Set Rcomp delay from 1p8mode to 10ms
    /// Set "IOSF2OCP.GPPRVRW6[1P8_SEL_DELAY]", PCR[SCS] + 614h bit[7:0] = 0x7F
    ///
    PchPcrWrite32 (PID_SCS, R_PCH_PCR_SCS_GPPRVRW6, (UINT32) V_PCH_PCR_SCS_GPPRVRW6_1P8_SEL_DELAY);
  }

  DEBUG ((DEBUG_INFO, "ConfigureScsControllers() End\n"));
}

/**
  Check if SerialIo UART0 is in PCI mode

  @param[in] N/A

  @retval TRUE                        SerialIo UART0 is in PCI mode
  @retval FALSE                       SerialIo UART0 is not in PCI mode
**/
BOOLEAN
IsUartInPciMode (
  VOID
  )
{
  UINTN               PciCfgBase;
  UINT32              VendorId;

  ///
  /// SerialIo UART0 must be enabled as PCI mode
  ///
  PciCfgBase = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART0, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART0);
  VendorId = MmioRead16 (PciCfgBase + PCI_VENDOR_ID_OFFSET);

  if (VendorId == 0xFFFF) {
    DEBUG ((DEBUG_ERROR, "IsUartInPciMode: SerialIo UART0 must be enabled as PCI mode in order to enable SCS device.\n"));
    return FALSE;
  }
  return TRUE;
}

/**
  Configures Storange and Communication Subsystem Controllers
  to work in PCI Mode.

  @param[in] SiPolicy        The SI Policy PPI instance

  @retval None
**/
VOID
ConfigureScsPciMode (
  IN SI_POLICY_PPI  *SiPolicy
  )
{
  EFI_STATUS        Status;
  PCH_SCS_CONFIG    *ScsConfig;

  DEBUG ((DEBUG_INFO, "ConfigureScsPciMode() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gScsConfigGuid, (VOID *) &ScsConfig);
  ASSERT_EFI_ERROR (Status);
  ///
  /// PCH BIOS Spec Rev 0.4.0 Section 28.5.1 PCI Mode of Operation
  /// By default all controllers are operate in PCI Mode
  /// For eMMC Controller
  /// Step 1. Set PCICFGCTR1.BAR1_DISABLE1, offset 0x200 [7] = 1b.
  /// Step 2. Set PCR[PSF2] + "AGNT_T0_SHDW_PCIEN"[eMMC][19, 18] to [1b, 1b]
  /// For SDCARD Controller
  /// Step 3. Set PCICFGCTR3.BAR1_DISABLE1, offset 0x208 [7] = 1b.
  /// Step 4. Set PCR[PSF2] + "AGNT_T0_SHDW_PCIEN"[SDCARD][19, 18] to [1b, 1b]
  ///
  if (ScsConfig->ScsEmmcEnabled == TRUE) {
    ConfigureScsDevBar1Disable (PchEmmc);
    PsfDisableScsBar1 (PchPsfEmmc);
  }

  if (ScsConfig->ScsSdSwitch == PchScsSdcardMode) {
    ConfigureScsDevBar1Disable (PchSdcard);
    PsfDisableScsBar1 (PchPsfSdcard);
  }

  DEBUG ((DEBUG_INFO, "ConfigureScsPciMode() End\n"));
}
/**

  Function to configure low power feature for Storage and Communication Subsystem

  @param[in] SiPolicy             The SI Policy PPI instance

  @retval EFI_SUCCESS             The function completed successfully
**/
VOID
ConfigureScsLowPowerFeature (
  IN SI_POLICY_PPI               *SiPolicy
  )
{
  UINT32            Data32;
  PCH_STEPPING      PchStep;
  EFI_STATUS        Status;
  PCH_SCS_CONFIG    *ScsConfig;

  DEBUG ((DEBUG_ERROR, "ConfigureScsLowPowerFeature() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gScsConfigGuid, (VOID *) &ScsConfig);
  ASSERT_EFI_ERROR (Status);

  PchStep = PchStepping ();

  //
  // Program the "Power Management Control (PMCTL) and Clock Gating Control (GPPRVRW1) Register" according to the recommended value
  //
  PchPcrAndThenOr32 (
    PID_SCS,
    R_PCH_PCR_SCS_PMCTL,
    0,
    (BIT5| BIT4 | BIT3 | BIT2 | BIT1 | BIT0)
    );

  //
  // Program Clock Gating  - set bits 31, 19, 18, 16, 15, 14, 13, 10, 9, 8, 7, 6, 5, 2, 1, 0
  //
  PchPcrAndThenOr32 (
    PID_SCS,
    R_PCH_PCR_SCS_GPPRVRW1,
    0,
    (BIT31 | BIT19 | BIT18 | BIT16 | BIT15 | BIT14 | BIT13 | BIT10 | BIT9 | BIT8 | BIT7 | BIT6 | BIT5 | BIT2 | BIT1 | BIT0)
    );

  if (PchStep > PchLpC0) {
    //
    // Set GPPRVRW1 High Speed Trunk Clock Req [BIT3] = 1 to allow Gen2 PLL shutdown
    //
    PchPcrAndThenOr32 (
      PID_SCS,
      R_PCH_PCR_SCS_GPPRVRW1,
      (UINT32) ~0,
      BIT3
      );
  }
  PchPcrRead32 (PID_SCS, R_PCH_PCR_SCS_PMCTL, &Data32);
  DEBUG ((DEBUG_INFO, "Power Management Control PMCTL (1D0h) = 0x%08x\n", Data32));
  PchPcrRead32 (PID_SCS, R_PCH_PCR_SCS_GPPRVRW1, &Data32);
  DEBUG ((DEBUG_INFO, "Clock Gating Control GPPRVRW1 (600h) = 0x%08x\n", Data32));

}
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
  IN  SI_POLICY_PPI             *SiPolicy,
  IN UINT32                     TempMemBaseAddr
  )
{

  DEBUG ((DEBUG_INFO, "PchScsInit() Start\n"));
  ConfigureScsLowPowerFeature (SiPolicy);
  ConfigureScsControllers (SiPolicy, TempMemBaseAddr);
  if (IsUartInPciMode ()) {
    ConfigureScsPciMode (SiPolicy);
  }
  DEBUG ((DEBUG_INFO, "PchScsInit() End\n"));
  return EFI_SUCCESS;
}

