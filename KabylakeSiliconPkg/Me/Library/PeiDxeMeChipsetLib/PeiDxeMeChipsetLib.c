/** @file
  Me Chipset Lib implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2017 Intel Corporation.

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
#include <Uefi.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Library/MmPciLib.h>
#include <MeChipset.h>
#include <HeciRegs.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <IndustryStandard/Pci22.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/PchPsfLib.h>


/**
  Put ME device out of D0I3

  @param[in] Function  ME function where DOI3 is to be changed

**/
VOID
ClearD0I3Bit (
  IN  UINT32   Function
  )
{
  UINTN        DevicePciCfgBase;
  UINT32       DeviceBar[2];
  UINTN        *pBar;
  UINT8        Cmd;
  UINTN        Timeout;
  UINT32       D0I3Ctrl;

  DEBUG ((DEBUG_INFO, "[HECI%d] Clearing D0I3 bit\n", HECI_NAME_MAP (Function)));
  ///
  /// Get Device MMIO address
  ///
  DevicePciCfgBase = MmPciBase (ME_BUS, ME_DEVICE_NUMBER, Function);
  if (MmioRead16 (DevicePciCfgBase + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_WARN, "[HECI%d] Function is disabled, cannot clear D0I3 bit!\n", HECI_NAME_MAP (Function)));
    return;
  }
  DeviceBar[0] = MmioRead32 (DevicePciCfgBase + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFFFF0;
  DeviceBar[1] = 0x0;
  if ((MmioRead32 (DevicePciCfgBase + PCI_BASE_ADDRESSREG_OFFSET) & 0x6) == 0x4) {
    DeviceBar[1] = MmioRead32 (DevicePciCfgBase + (PCI_BASE_ADDRESSREG_OFFSET + 4));
  }

  ///
  /// Put CSME Device out of D0I3
  /// (1) Poll D0I3C[0] CIP bit is 0 with timeout 5 seconds
  /// (2) Write D0I3C[2] = 0
  /// (3) Poll D0I3C[0] CIP bit is 0 with timeout 5 seconds
  ///
  if (!(DeviceBar[0] == 0x0 && DeviceBar[1] == 0x0) && !(DeviceBar[0] == 0xFFFFFFF0 && DeviceBar[1] == 0xFFFFFFFF)) {
    Cmd = MmioRead8 (DevicePciCfgBase + PCI_COMMAND_OFFSET);
    if ((Cmd & EFI_PCI_COMMAND_MEMORY_SPACE) != EFI_PCI_COMMAND_MEMORY_SPACE) {
      MmioOr8 (DevicePciCfgBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
    }
    pBar = (UINTN*) DeviceBar;
    D0I3Ctrl = MmioRead32 (*pBar + D0I3C);
    if ((D0I3Ctrl & BIT2) == BIT2) {
      ///
      /// (1) If entering D0I3 is in progress wait till it finishes. Let's give it 5000 ms timeout.
      ///
      Timeout = 5000;
      while ((D0I3Ctrl & BIT0) == BIT0 && Timeout-- > 0) {
        MicroSecondDelay (1000);
        D0I3Ctrl = MmioRead32 (*pBar + D0I3C);
      }

      ///
      /// (2) Write D0I3C[2] = 0
      ///
      MmioWrite32 (*pBar + D0I3C, D0I3Ctrl & ~BIT2);

      D0I3Ctrl = MmioRead32 (*pBar + D0I3C);
      ///
      /// (3) If exiting D0I3 is in progress wait till it finishes. Let's give it 5000 ms timeout.
      ///
      Timeout = 5000;
      while ((D0I3Ctrl & BIT0) == BIT0 && Timeout-- > 0) {
        MicroSecondDelay (1000);
        D0I3Ctrl = MmioRead32 (*pBar + D0I3C);
      }
    }
    DEBUG ((DEBUG_INFO, "[HECI%d] D0I3C register = %08X\n", HECI_NAME_MAP (Function), MmioRead32 (*pBar + D0I3C)));
    MmioWrite8 (DevicePciCfgBase + PCI_COMMAND_OFFSET, Cmd);
  }
}


/**
  Put ME device into D0I3

  @param[in] Function          Select of Me device

**/
VOID
SetD0I3Bit (
  IN  UINT32   Function
  )
{
  UINTN                           DevicePciCfgBase;
  UINT32                          DeviceBar[2];
  UINTN                           *Bar;

  DEBUG ((DEBUG_INFO, "[HECI%d] Setting D0I3 bit\n", HECI_NAME_MAP (Function)));
  ///
  /// Get Device MMIO address
  ///
  DevicePciCfgBase = MmPciBase (ME_BUS, ME_DEVICE_NUMBER, Function);
  if (MmioRead16 (DevicePciCfgBase + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_WARN, "[HECI%d] Function is disabled, can't set D0I3 bit!\n", HECI_NAME_MAP (Function)));
    return;
  }
  if (MmioRead32 (DevicePciCfgBase + R_ME_HIDM) != V_ME_HIDM_MSI) {
    DEBUG ((DEBUG_WARN, "[HECI%d] HIDM is not legacy/MSI, do not set DOI3 bit!\n", HECI_NAME_MAP (Function)));
    return;
  }
  DeviceBar[0] = MmioRead32 (DevicePciCfgBase + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFFFF0;
  DeviceBar[1] = 0x0;
  if ((MmioRead32 (DevicePciCfgBase + PCI_BASE_ADDRESSREG_OFFSET) & 0x6) == 0x4) {
    DeviceBar[1] = MmioRead32 (DevicePciCfgBase + (PCI_BASE_ADDRESSREG_OFFSET + 4));
  }

  ///
  /// Put CSME Device in D0I3
  ///
  MmioOr8 (DevicePciCfgBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER);
  if (!(DeviceBar[0] == 0x0 && DeviceBar[1] == 0x0) && !(DeviceBar[0] == 0xFFFFFFF0 && DeviceBar[1] == 0xFFFFFFFF)) {
    Bar = (UINTN*) DeviceBar;
    MmioOr32 (*Bar + D0I3C, BIT2);
    DEBUG ((DEBUG_INFO, "[HECI%d] D0I3C register = %08X\n", HECI_NAME_MAP (Function), MmioRead32 (*Bar + D0I3C)));
  }

  MmioAnd8 (DevicePciCfgBase + PCI_COMMAND_OFFSET,(UINT8) ~(EFI_PCI_COMMAND_MEMORY_SPACE));
}

/**
  Enable/Disable Me devices

  @param[in] WhichDevice          Select of Me device
  @param[in] DeviceFuncCtrl       Function control

**/
VOID
MeDeviceControl (
  IN  ME_DEVICE                   WhichDevice,
  IN  ME_DEVICE_FUNC_CTRL         DeviceFuncCtrl
  )
{
  UINT16                          DevPsfBase;
  UINT32                          PchPwrmBase;
  UINTN                           PciBaseAdd;
  PCH_SERIES                      PchSeries;

  DevPsfBase = 0;
  PciBaseAdd = 0;
  PchSeries  = GetPchSeries ();
  PchPwrmBaseGet (&PchPwrmBase);

  switch (WhichDevice) {
    case HECI1:
      if (DeviceFuncCtrl == Enabled) {
        PsfEnableHeciDevice (1);
        ClearD0I3Bit ((UINT32) HECI1);
      } else {
        SetD0I3Bit ((UINT32) HECI1);
        PsfDisableHeciDevice (1);
      }
      break;
    case HECI2:
      if (DeviceFuncCtrl == Enabled) {
        PsfEnableHeciDevice (2);
        ClearD0I3Bit ((UINT32) HECI2);
      } else {
        SetD0I3Bit ((UINT32) HECI2);
        PsfDisableHeciDevice (2);
      }
      break;
    case HECI3:
      if (DeviceFuncCtrl == Enabled) {
        PsfEnableHeciDevice (3);
        ClearD0I3Bit ((UINT32) HECI3);
      } else {
        SetD0I3Bit ((UINT32) HECI3);
        PsfDisableHeciDevice (3);
      }
      break;
    case IDER:
      if (DeviceFuncCtrl == Enabled) {
        PsfEnableIderDevice ();
      } else {
        PciBaseAdd = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, ME_DEVICE_NUMBER, IDER_FUNCTION_NUMBER);
        MmioWrite32 (PciBaseAdd + R_ME_PMCSR, (UINT32) V_ME_PMCSR);
        PsfDisableIderDevice ();
      }
      break;
    case SOL:
      if (DeviceFuncCtrl == Enabled) {
        PsfEnableSolDevice ();
      } else {
        PciBaseAdd = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, ME_DEVICE_NUMBER, SOL_FUNCTION_NUMBER);
        MmioWrite32 (PciBaseAdd + R_ME_PMCSR, (UINT32) V_ME_PMCSR);
        PsfDisableSolDevice ();
      }
      break;
      ///
      /// Function Disable SUS well lockdown
      ///
    case FDSWL:
      if (DeviceFuncCtrl) {
        MmioOr32 (PchPwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1, (UINT32) (B_PCH_PWRM_ST_PG_FDIS_PMC_1_ST_FDIS_LK));
      } else {
        MmioAnd32 (PchPwrmBase + R_PCH_PWRM_ST_PG_FDIS_PMC_1, (UINT32) (~B_PCH_PWRM_ST_PG_FDIS_PMC_1_ST_FDIS_LK));
      }
      break;

    default:
      break;
  }

  if (WhichDevice != FDSWL) {
    if (DeviceFuncCtrl == Enabled) {
      DEBUG ((DEBUG_INFO, "Enabling CSME device 0:22:%d\n", (UINT8) WhichDevice));
    } else {
      DEBUG ((DEBUG_INFO, "Disabling CSME device 0:22:%d\n", (UINT8) WhichDevice));
    }
  }
}


/**
  Initialize Me devices

  @param[in] WhichDevice          Select of Me device
  @param[in] MmioAddrL32          MMIO address for 32-bit low dword
  @param[in] MmioAddrH32          MMIO address for 32-bit high dword

**/
VOID
MeDeviceInit (
  IN  ME_DEVICE                   WhichDevice,
  IN  UINT32                      MmioAddrL32,
  IN  UINT32                      MmioAddrH32
  )
{
  UINTN                           DevicePciCfgBase;

  DEBUG ((DEBUG_INFO, "MeDeviceInit [HECI%d] H: %08x, L: %08X\n",
    HECI_NAME_MAP (WhichDevice), MmioAddrH32, MmioAddrL32));
  switch (WhichDevice) {
    case HECI1:
    case HECI2:
    case HECI3:
      break;

    default:
      DEBUG ((DEBUG_ERROR, "MeDeviceInit[HECI%d] fail, invalid parameter.\n", HECI_NAME_MAP (WhichDevice)));
      return;
  }

  ///
  /// Get Device MMIO address
  ///
  DevicePciCfgBase = MmPciBase (ME_BUS, ME_DEVICE_NUMBER, (UINT32) WhichDevice);
  if (MmioRead16 (DevicePciCfgBase + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_ERROR, "[HECI%d] Function is disabled, can't initialize\n", HECI_NAME_MAP (WhichDevice)));
    return;
  }

  ///
  /// Program HECI BAR
  ///
  DEBUG ((DEBUG_INFO, "Program HECI MMIO address\n"));
  MmioWrite32 (DevicePciCfgBase + PCI_COMMAND_OFFSET,              0);
  MmioWrite32 (DevicePciCfgBase + PCI_BASE_ADDRESSREG_OFFSET,      MmioAddrL32 | BIT0);
  MmioWrite32 (DevicePciCfgBase + PCI_BASE_ADDRESSREG_OFFSET + 4,  MmioAddrH32);
  MmioWrite32 (DevicePciCfgBase + PCI_COMMAND_OFFSET,              EFI_PCI_COMMAND_MEMORY_SPACE);
}

/**
  Save HECI BARs

  @param[in] WhichDevice          Select of Me device
  @param[in] BarList              Buffer to store BAR addresses

**/
VOID
MeSaveBars (
  IN  ME_DEVICE                   WhichDevice,
  IN OUT UINT32                   BarList[PCI_MAX_BAR]
  )
{
  UINTN        DevicePciCfgBase;
  UINTN        BarNumber;

  DEBUG ((DEBUG_INFO, "[HECI%d] MeSaveBars\n", HECI_NAME_MAP (WhichDevice)));
  ///
  /// Get Device MMIO address
  ///
  DevicePciCfgBase = MmPciBase (ME_BUS, ME_DEVICE_NUMBER, (UINT32) WhichDevice);
  if (MmioRead16 (DevicePciCfgBase + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_ERROR, "[HECI%d] Function is disabled, cannot save BAR addresses\n", HECI_NAME_MAP (WhichDevice)));
    return;
  }

  for (BarNumber = 0; BarNumber < PCI_MAX_BAR; BarNumber++) {
    BarList[BarNumber] = MmioRead32 (DevicePciCfgBase + PCI_BASE_ADDRESSREG_OFFSET + (BarNumber * sizeof(UINT32)));
    DEBUG ((DEBUG_INFO, "[%d] %08X\n", BarNumber, BarList[BarNumber]));
  }

}

/**
  Restore HECI BARs

  @param[in] WhichDevice          Select of Me device
  @param[in] BarList              Buffer for BAR addresses to be restored

**/
VOID
MeRestoreBars (
  IN  ME_DEVICE                   WhichDevice,
  IN  UINT32                      BarList[PCI_MAX_BAR]
  )
{
  UINTN        DevicePciCfgBase;
  UINTN        BarNumber;
  UINT32       CmdSt;

  DEBUG ((DEBUG_INFO, "[HECI%d] MeRestoreBars\n", HECI_NAME_MAP (WhichDevice)));
  ///
  /// Get Device MMIO address
  ///
  DevicePciCfgBase = MmPciBase (ME_BUS, ME_DEVICE_NUMBER, (UINT32) WhichDevice);
  if (MmioRead16 (DevicePciCfgBase + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_ERROR, "[HECI%d] Function is disabled, cannot restore BAR addresses\n", HECI_NAME_MAP (WhichDevice)));
    return;
  }

  CmdSt = MmioRead32 (DevicePciCfgBase + PCI_COMMAND_OFFSET);
  MmioWrite32 (DevicePciCfgBase + PCI_COMMAND_OFFSET, 0);     // Stop PCIe communication first.
  for (BarNumber = 0; BarNumber < PCI_MAX_BAR; BarNumber++) {
    MmioWrite32 (DevicePciCfgBase + PCI_BASE_ADDRESSREG_OFFSET + (BarNumber * sizeof(UINT32)), BarList[BarNumber]);
    DEBUG ((DEBUG_INFO, "[%d] %08X\n", BarNumber, MmioRead32 (DevicePciCfgBase + PCI_BASE_ADDRESSREG_OFFSET + (BarNumber * sizeof(UINT32)))));
  }
  MmioWrite32 (DevicePciCfgBase + PCI_COMMAND_OFFSET, CmdSt); // Restore setting of Command/Status register.

}

