/** @file
  SEC PCH library in C.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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
#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/MmPciLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchSerialIoLib.h>
#include <Library/PchSerialIoUartLib.h>
#include <PchAccess.h>
#include <Library/PchInfoLib.h>

#ifdef FSP_FLAG
#include <FspEas.h>
#include <FsptUpd.h>

/**
  This interface gets FspInfoHeader pointer

  @return   FSP binary base address.

**/
UINT32
EFIAPI
AsmGetFspInfoHeader (
  VOID
  );
#endif

/**
  This is helper function to initialize SerialIoUart in early init.
**/
VOID
EFIAPI
SerialIoUartConfiguration (
  VOID
  )
{
  UINT8     SerialIoUartDebugEnable;
  UINT8     SerialIoUartNumber;
  UINT32    SerialIoUartInputClock;
#ifdef FSP_FLAG
  FSP_INFO_HEADER   *FspInfoHeader;
  FSPT_UPD          *FsptUpd;

  FspInfoHeader = (FSP_INFO_HEADER *) AsmGetFspInfoHeader ();
  FsptUpd = (FSPT_UPD *) (FspInfoHeader->ImageBase + FspInfoHeader->CfgRegionOffset);
  SerialIoUartDebugEnable = FsptUpd->FsptConfig.PcdSerialIoUartDebugEnable;
  SerialIoUartNumber = FsptUpd->FsptConfig.PcdSerialIoUartNumber;
  SerialIoUartInputClock = FsptUpd->FsptConfig.PcdSerialIoUartInputClock;
#else
  SerialIoUartDebugEnable = PcdGet8 (PcdSerialIoUartDebugEnable);
  SerialIoUartNumber = PcdGet8 (PcdSerialIoUartNumber);
  SerialIoUartInputClock = PcdGet32 (PcdSerialIoUartInputClock);
#endif

  //
  // Initialize SerialIo UART for debug message
  //
  if (SerialIoUartDebugEnable == 1) {
    ConfigureSerialIoController (SerialIoUartNumber + PchSerialIoIndexUart0, PchSerialIoPci);
    SerialIoUartGpioInit (SerialIoUartNumber + PchSerialIoIndexUart0, PchSerialIoPci, FALSE);
    PchSerialIoUartInit (SerialIoUartNumber, TRUE, (SerialIoUartInputClock / 16), 3, FALSE);
  }

}

/**
  This function do the PCH cycle decoding initialization.
**/
VOID
EFIAPI
EarlyCycleDecoding (
  VOID
  )
{
  UINT32   P2sbBase;
  UINT32   SmbusBase;

  //
  // Enable PCR base address in PCH
  //
  P2sbBase = MmPciBase (
               DEFAULT_PCI_BUS_NUMBER_PCH,
               PCI_DEVICE_NUMBER_PCH_P2SB,
               PCI_FUNCTION_NUMBER_PCH_P2SB
               );
  MmioWrite32 (P2sbBase + R_PCH_P2SB_SBREG_BAR, PCH_PCR_BASE_ADDRESS);
  //
  // Enable P2SB MSE
  //
  MmioOr8 (P2sbBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);

  //
  // Program ACPI Base.
  //
  PchAcpiBaseSet (PcdGet16 (PcdAcpiBaseAddress));

  //
  // Program PWRM BASE
  //
  PchPwrmBaseSet (PCH_PWRM_BASE_ADDRESS);

  //
  // Program and Enable TCO Base
  //
  PchTcoBaseSet (PcdGet16 (PcdTcoBaseAddress));

  SmbusBase = MmPciBase (
                DEFAULT_PCI_BUS_NUMBER_PCH,
                PCI_DEVICE_NUMBER_PCH_SMBUS,
                PCI_FUNCTION_NUMBER_PCH_SMBUS
                );
  ///
  /// SMBus PCI 0x64 = 0x0A0A0000
  ///
  MmioWrite32 (SmbusBase + R_PCH_SMBUS_64, 0x0A0A0000);
  //
  // Initialize SMBUS IO BAR
  //
  MmioWrite16 (SmbusBase + R_PCH_SMBUS_BASE, PcdGet16 (PcdSmbusBaseAddress));
  //
  // Enable the Smbus I/O Enable
  //
  MmioOr8 (SmbusBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_IO_SPACE);
  //
  // Enable the SMBUS Controller
  //
  MmioOr8 (SmbusBase + R_PCH_SMBUS_HOSTC, B_PCH_SMBUS_HOSTC_HST_EN);

  //
  // Enable the upper 128-byte bank of RTC RAM.
  // PCR [RTC] + 0x3400 [2] = 1
  //
  PchPcrAndThenOr32 (PID_RTC, R_PCH_PCR_RTC_CONF, (UINT32) ~0, B_PCH_PCR_RTC_CONF_UCMOS_EN);
}
