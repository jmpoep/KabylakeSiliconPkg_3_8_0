/** @file
  This file contains the tests for the BootFirmwareMediaProtection BIT

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

@par Specification
**/

#include "HstiSiliconDxe.h"

#define B_PCH_SPI_FMRWA_MASK 0xFFF00000
#define B_PCH_SPI_FMRRA_MASK 0x000FFF00

/**
  Run tests for BootFirmwareMediaProtection bit
**/
VOID
CheckBootFirmwareMediaProtection (
  VOID
  )
{
  EFI_STATUS      Status;
  BOOLEAN         Result;
  UINT16          PmBase;
  UINT8           BiosControl;
  UINT16          Hsfs;
  UINT32          Cpptv;
  UINT32          Frap;
  UINT8           Data8;
  UINT32          Data32;
  CHAR16          *HstiErrorString;
  UINT32          PchSpiBar0;
  UINT8           PcrDmi;
  UINT32          SpiHostSs;

  if ((mFeatureImplemented[0] & HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION) == 0) {
    return;
  }

  Result = TRUE;

  PchAcpiBaseGet (&PmBase);

  PchSpiBar0 = MmioRead32 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH,PCI_DEVICE_NUMBER_PCH_SPI,PCI_FUNCTION_NUMBER_PCH_SPI) + R_PCH_SPI_BAR0) & ~B_PCH_SPI_BAR0_MASK;

  DEBUG ((DEBUG_INFO, "  Table 3-5. SPI Flash and BIOS Security Configuration\n"));
  DEBUG ((DEBUG_INFO, "    1. BIOS write-protection\n"));

  BiosControl = MmioRead8 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH,PCI_DEVICE_NUMBER_PCH_LPC,PCI_FUNCTION_NUMBER_PCH_SPI) + R_PCH_SPI_BC);
  if (((BiosControl & B_PCH_SPI_BC_LE) == 0) ||
      ((BiosControl & B_PCH_SPI_BC_WPD) != 0) ||
      ((BiosControl & B_PCH_SPI_BC_EISS) == 0)) {

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_1 ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_1);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    2. SPI flash descriptor security override pin-strap\n"));

  Hsfs = MmioRead16 (PchSpiBar0 + R_PCH_SPI_HSFSC);
  if ((Hsfs & B_PCH_SPI_HSFSC_FDOPSS) == 0) {

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_2 ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_2);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    3. SPI controller configuration is locked\n"));

  if ((Hsfs & B_PCH_SPI_HSFSC_FLOCKDN) == 0) {

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_3 ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_3);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    4. BIOS Interface Lock\n"));

  PcrDmi = MmioRead8 (PCH_PCR_ADDRESS (PID_DMI,R_PCH_PCR_DMI_GCS));

  if (((PcrDmi & BIT0) == 0x0) ||
      ((BiosControl & BIT7) == 0x0)) {
    DEBUG ((DEBUG_INFO, "PcrDmi %x or BILD[7] %x not set\n",PcrDmi,BiosControl));

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_4 ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_4);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    5. BIOS Top Swap Mode\n"));

  if ((BiosControl & B_PCH_SPI_BC_TSS) != 0) {

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_5 ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_5);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    6. Component Property Parameter Table Valid\n"));

  Cpptv = MmioRead32 (PchSpiBar0 + R_PCH_SPI_SFDP0_VSCC0);
  if ((Cpptv & B_PCH_SPI_SFDPX_VSCCX_CPPTV) == 0) {

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_6 ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_6);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    7. Component Property Parameter Table Valid, Secondary Flash Part\n"));
  Data32 = 0;
  Data32 = Data32 | 0x14;
  MmioWrite32 (PchSpiBar0 + R_PCH_SPI_FDOC, Data32);
  Data32  = MmioRead32 (PchSpiBar0 + R_PCH_SPI_FDOD);

  Cpptv = MmioRead32 (PchSpiBar0 + R_PCH_SPI_SFDP1_VSCC1);

  //
  // If Second part is present the verify CPPTV is set, otherwise if not present verify that it's clear
  //
  if ((Data32 & BIT8) != 0) {
    if ((Cpptv & B_PCH_SPI_SFDPX_VSCCX_CPPTV) == 0) {

      HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_6 ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_6);
      Status = HstiLibAppendErrorString (
                 PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                 NULL,
                 HstiErrorString
                 );
      ASSERT_EFI_ERROR (Status);
      Result = FALSE;
      FreePool (HstiErrorString);
    }
  } else {
    if ((Cpptv & B_PCH_SPI_SFDPX_VSCCX_CPPTV) == 1) {

      HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_6 ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_6);
      Status = HstiLibAppendErrorString (
                 PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                 NULL,
                 HstiErrorString
                 );
      ASSERT_EFI_ERROR (Status);
      Result = FALSE;
      FreePool (HstiErrorString);
    }
  }

  DEBUG ((DEBUG_INFO, "    8. ME Firmware Status\n"));

  Data8 = MmioRead8 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH,ME_DEVICE_NUMBER,HECI_FUNCTION_NUMBER) + 0x40);
  if ((Data8 & 0xF) != 0x5) {

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_8 ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_8);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    9. BIOS Flash Descriptor Valid\n"));

  if ((Hsfs & B_PCH_SPI_HSFSC_FDV) == 0) {

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_9 ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_9);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  Data32 = 0;
  Data32 = Data32 | V_PCH_SPI_FDOC_FDSS_MSTR | 0x0;
  MmioWrite32 (PchSpiBar0 + R_PCH_SPI_FDOC, Data32);
  Data32  = MmioRead32 (PchSpiBar0 + R_PCH_SPI_FDOD);

  DEBUG ((DEBUG_INFO, "    11. BIOS Region Flash Write Access\n"));
  ///
  /// Descriptor Master Access Read:  BIT 8
  /// Bios Master Access Read:        BIT 9
  /// CSE Master Access Read:         BIT 10
  /// GBE Master Access Read:         BIT 11
  /// PDR Master Access Read:         BIT 12
  /// EC  Master Access Read:         BIT 16
  /// Descriptor Master Access Write: BIT 20
  /// Bios Master Access Write:       BIT 21
  /// CSE Master Access Write:        BIT 22
  /// GBE Master Access Write:        BIT 23
  /// PDR Master Access Write:        BIT 24
  /// EC Master Access Write:         BIT 28
  ///
  if (((Data32 & B_PCH_SPI_FMRWA_MASK) != 0x00A00000) &&
      ((Data32 & B_PCH_SPI_FMRWA_MASK) != 0x01A00000) &&
      ((Data32 & B_PCH_SPI_FMRWA_MASK) != 0x10A00000) &&
      ((Data32 & B_PCH_SPI_FMRWA_MASK) != 0x11A00000)) {

    DEBUG ((DEBUG_INFO, "Bios Region Master Write Access 0x%x\n",(Data32 & B_PCH_SPI_FMRWA_MASK)));

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_A ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_A);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    12. BIOS Region Flash Read Access\n"));

  if (((Data32 & B_PCH_SPI_FMRRA_MASK) != 0x00000F00) &&
      ((Data32 & B_PCH_SPI_FMRRA_MASK) != 0x00001F00) &&
      ((Data32 & B_PCH_SPI_FMRRA_MASK) != 0x00010F00) &&
      ((Data32 & B_PCH_SPI_FMRRA_MASK) != 0x00011F00) &&
      ((Data32 & B_PCH_SPI_FMRRA_MASK) != 0x00000B00) &&
      ((Data32 & B_PCH_SPI_FMRRA_MASK) != 0x00001B00) &&
      ((Data32 & B_PCH_SPI_FMRRA_MASK) != 0x00010B00) &&
      ((Data32 & B_PCH_SPI_FMRRA_MASK) != 0x00011B00)) {

    DEBUG ((DEBUG_INFO, "Bios Region Master Read Access 0x%x\n",(Data32 & B_PCH_SPI_FMRRA_MASK)));

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_A ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_A);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    13. BIOS Master Read Access\n"));
  Frap = MmioRead16 (PchSpiBar0+ R_PCH_SPI_FRAP);

  if ((Frap & B_PCH_SPI_FRAP_BMRAG_MASK) != 0) {
    DEBUG ((DEBUG_INFO, "BMRAG 0x%x\n",(Frap & B_PCH_SPI_FRAP_BMRAG_MASK)));

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_A ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_A);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    14. BIOS Master Write Access\n"));

  if ((Frap & B_PCH_SPI_FRAP_BMWAG_MASK) != 0) {
    DEBUG ((DEBUG_INFO, "BMWAG 0x%x\n",(Frap & B_PCH_SPI_FRAP_BMWAG_MASK)));

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_A ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_A);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  if (PchIsGbeRegionValid ()) {
    DEBUG ((DEBUG_INFO, "    15. GbE Region Access\n"));

    Data32 = 0;
    Data32 = Data32 | V_PCH_SPI_FDOC_FDSS_MSTR | 0x8;
    MmioWrite32 (PchSpiBar0 + R_PCH_SPI_FDOC, Data32);
    Data32  = MmioRead32 (PchSpiBar0 + R_PCH_SPI_FDOD);

    if (Data32 != 0x00800900) {
      DEBUG ((DEBUG_INFO, "Gbe Region Access 0x%x\n",Data32));

      HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_A ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_A);
      Status = HstiLibAppendErrorString (
                 PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                 NULL,
                 HstiErrorString
                 );
      ASSERT_EFI_ERROR (Status);
      Result = FALSE;
      FreePool (HstiErrorString);
    }
  }

  DEBUG ((DEBUG_INFO, "    16. CSME Region Access\n"));

  Data32 = 0;
  Data32 = Data32 | V_PCH_SPI_FDOC_FDSS_MSTR | 0x4;
  MmioWrite32 (PchSpiBar0 + R_PCH_SPI_FDOC, Data32);
  Data32  = MmioRead32 (PchSpiBar0 + R_PCH_SPI_FDOD);

  if ((Data32 != 0x00400D00) &&
      (Data32 != 0x00C00D00) &&
      (Data32 != 0x10C10D00)) {
    DEBUG ((DEBUG_INFO, "Csme Region Access 0x%x\n",Data32));

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_A ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_A);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    17. EC Region Access\n"));

  Data32 = 0;
  Data32 = Data32 | V_PCH_SPI_FDOC_FDSS_MSTR | 0x10;
  MmioWrite32 (PchSpiBar0 + R_PCH_SPI_FDOC, Data32);
  Data32  = MmioRead32 (PchSpiBar0 + R_PCH_SPI_FDOD);

  if ((Data32  != 0x10010300)&&
       (Data32 != 0x10010100)&&
       (Data32 != 0x10010000)) {
    DEBUG ((DEBUG_INFO, "Ec Region access 0x%x\n",Data32));

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_A ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_A);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    18. Disable Software Sequencing\n"));
  PchPcrRead32 ( PID_ESPISPI ,0xC204,&SpiHostSs);

  if ((SpiHostSs & BIT13) != 0x0) {
    DEBUG ((DEBUG_INFO, "Soft sequencing 0x%x\n",(SpiHostSs & BIT13)));

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_CODE_A ,HSTI_SPI_FLASH_CONFIGURATION, HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_ERROR_STRING_A);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }


  //
  // ALL PASS
  //
  if (Result) {
    Status = HstiLibSetFeaturesVerified (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               0,
               HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION
               );
    ASSERT_EFI_ERROR (Status);
  }

  return;
}
