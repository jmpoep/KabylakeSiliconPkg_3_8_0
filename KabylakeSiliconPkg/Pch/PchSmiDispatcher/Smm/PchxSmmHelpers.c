/** @file
  This driver is responsible for the registration of child drivers
  and the abstraction of the PCH SMI sources.

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
**/
#include "PchSmmHelpers.h"

//
// Help handle porting bit shifts to IA-64.
//
#define BIT_ZERO  0x00000001

/**
  Publish SMI Dispatch protocols.


**/
VOID
PchSmmPublishDispatchProtocols (
  VOID
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINTN      Index;
  //
  // Install protocol interfaces.
  //
  for (Index = 0; Index < PCH_SMM_PROTOCOL_TYPE_MAX; Index++) {
    Status = gSmst->SmmInstallProtocolInterface (
                      &mPrivateData.InstallMultProtHandle,
                      mPrivateData.Protocols[Index].Guid,
                      EFI_NATIVE_INTERFACE,
                      &mPrivateData.Protocols[Index].Protocols.Generic
                      );
  }
  ASSERT_EFI_ERROR (Status);
}

/**
  Initialize bits that aren't necessarily related to an SMI source.


  @retval EFI_SUCCESS             SMI source initialization completed.
  @retval Asserts                 Global Smi Bit is not enabled successfully.
**/
EFI_STATUS
PchSmmInitHardware (
  VOID
  )
{
  EFI_STATUS  Status;

  ///
  /// Clear all SMIs
  ///
  PchSmmClearSmi ();

  Status = PchSmmEnableGlobalSmiBit ();
  ASSERT_EFI_ERROR (Status);

  ///
  /// Be *really* sure to clear all SMIs
  ///
  PchSmmClearSmi ();

  return EFI_SUCCESS;
}

/**
  Enables the PCH to generate SMIs. Note that no SMIs will be generated
  if no SMI sources are enabled. Conversely, no enabled SMI source will
  generate SMIs if SMIs are not globally enabled. This is the main
  switchbox for SMI generation.


  @retval EFI_SUCCESS             Enable Global Smi Bit completed
**/
EFI_STATUS
PchSmmEnableGlobalSmiBit (
  VOID
  )
{
  UINT32  SmiEn;

  SmiEn = IoRead32 ((UINTN) (mAcpiBaseAddr + R_PCH_SMI_EN));

  ///
  /// Set the "global smi enable" bit
  ///
  SmiEn |= B_PCH_SMI_EN_GBL_SMI;

  IoWrite32 ((UINTN) (mAcpiBaseAddr + R_PCH_SMI_EN), SmiEn);

  return EFI_SUCCESS;
}

/**
  Clears the SMI after all SMI source have been processed.
  Note that this function will not work correctly (as it is
  written) unless all SMI sources have been processed.
  A revision of this function could manually clear all SMI
  status bits to guarantee success.


  @retval EFI_SUCCESS             Clears the SMIs completed
  @retval Asserts                 EOS was not set to a 1
**/
EFI_STATUS
PchSmmClearSmi (
  VOID
  )
{
  BOOLEAN     EosSet;
  BOOLEAN     SciEn;
  UINT32      Pm1Cnt;
  UINT16      Pm1Sts;
  UINT32      Gpe0Sts;
  UINT32      SmiSts;
  UINT16      DevActSts;
  UINT16      Tco1Sts;

  Gpe0Sts      = 0;
  ///
  /// Determine whether an ACPI OS is present (via the SCI_EN bit)
  ///
  Pm1Cnt = IoRead32 ((UINTN) (mAcpiBaseAddr + R_PCH_ACPI_PM1_CNT));
  SciEn  = (BOOLEAN) ((Pm1Cnt & B_PCH_ACPI_PM1_CNT_SCI_EN) == B_PCH_ACPI_PM1_CNT_SCI_EN);
  if (!SciEn) {
    ///
    /// Clear any SMIs that double as SCIs (when SCI_EN==0)
    ///
    Pm1Sts   = IoRead16 ((UINTN) (mAcpiBaseAddr + R_PCH_ACPI_PM1_STS));
    Gpe0Sts  = IoRead32 ((UINTN) (mAcpiBaseAddr + R_PCH_ACPI_GPE0_STS_127_96));

    Pm1Sts |=
    (
      B_PCH_ACPI_PM1_STS_WAK |
      B_PCH_ACPI_PM1_STS_PRBTNOR |
      B_PCH_ACPI_PM1_STS_RTC |
      B_PCH_ACPI_PM1_STS_PWRBTN |
      B_PCH_ACPI_PM1_STS_GBL |
      B_PCH_ACPI_PM1_STS_TMROF
      );

    Gpe0Sts &= (UINT32)~(B_PCH_ACPI_GPE0_STS_127_96_WADT);

    IoWrite16 ((UINTN) (mAcpiBaseAddr + R_PCH_ACPI_PM1_STS), (UINT16) Pm1Sts);
    IoWrite32 ((UINTN) (mAcpiBaseAddr + R_PCH_ACPI_GPE0_STS_127_96), (UINT32) Gpe0Sts);
  }
  ///
  /// Clear all SMIs that are unaffected by SCI_EN
  ///
  SmiSts        = IoRead32 ((UINTN) (mAcpiBaseAddr + R_PCH_SMI_STS));
  DevActSts     = IoRead16 ((UINTN) (mAcpiBaseAddr + R_PCH_DEVACT_STS));
  Tco1Sts       = IoRead16 ((UINTN) (mTcoBaseAddr + R_PCH_TCO1_STS));

  SmiSts |=
  (
    B_PCH_SMI_STS_SMBUS |
    B_PCH_SMI_STS_PERIODIC |
    B_PCH_SMI_STS_TCO |
    B_PCH_SMI_STS_MCSMI |
    B_PCH_SMI_STS_SWSMI_TMR |
    B_PCH_SMI_STS_APM |
    B_PCH_SMI_STS_ON_SLP_EN |
    B_PCH_SMI_STS_BIOS
    );
  DevActSts |=
  (
    B_PCH_DEVACT_STS_KBC |
    B_PCH_DEVACT_STS_PIRQDH |
    B_PCH_DEVACT_STS_PIRQCG |
    B_PCH_DEVACT_STS_PIRQBF |
    B_PCH_DEVACT_STS_PIRQAE
    );
  Tco1Sts |=
  (
    B_PCH_TCO1_STS_DMISERR |
    B_PCH_TCO1_STS_DMISMI |
    B_PCH_TCO1_STS_DMISCI |
    B_PCH_TCO1_STS_BIOSWR |
    B_PCH_TCO1_STS_NEWCENTURY |
    B_PCH_TCO1_STS_TIMEOUT |
    B_PCH_TCO1_STS_TCO_INT |
    B_PCH_TCO1_STS_SW_TCO_SMI
    );

  GpioClearAllGpiSmiSts ();

  //
  // If NewCentury Sts is set here, it must clear the NewCentury Sts separately.
  //
  PchTcoClearNewCenturySts (NULL);

  IoWrite16 ((UINTN) (mTcoBaseAddr + R_PCH_TCO1_STS), Tco1Sts);

  //
  // We do not want to write 1 to clear INTRD_DET bit.
  //
  IoWrite16 ((UINTN) (mTcoBaseAddr + R_PCH_TCO2_STS), (UINT16) ~B_PCH_TCO2_STS_INTRD_DET);

  IoWrite32 ((UINTN) (mAcpiBaseAddr + R_PCH_SMI_STS), SmiSts);

  IoWrite16 ((UINTN) (mAcpiBaseAddr + R_PCH_DEVACT_STS), DevActSts);

  ///
  /// Try to clear the EOS bit. ASSERT on an error
  ///
  EosSet = PchSmmSetAndCheckEos ();
  ASSERT (EosSet);

  return EFI_SUCCESS;
}

/**
  Set the SMI EOS bit after all SMI source have been processed.


  @retval FALSE                   EOS was not set to a 1; this is an error
  @retval TRUE                    EOS was correctly set to a 1
**/
BOOLEAN
PchSmmSetAndCheckEos (
  VOID
  )
{
  UINT32  SmiEn;

  SmiEn = IoRead32 ((UINTN) (mAcpiBaseAddr + R_PCH_SMI_EN));

  ///
  /// Reset the PCH to generate subsequent SMIs
  ///
  SmiEn |= B_PCH_SMI_EN_EOS;

  IoWrite32 ((UINTN) (mAcpiBaseAddr + R_PCH_SMI_EN), SmiEn);

  ///
  /// Double check that the assert worked
  ///
  SmiEn = IoRead32 ((UINTN) (mAcpiBaseAddr + R_PCH_SMI_EN));

  ///
  /// Return TRUE if EOS is set correctly
  ///
  if ((SmiEn & B_PCH_SMI_EN_EOS) == 0) {
    ///
    /// EOS was not set to a 1; this is an error
    ///
    return FALSE;
  } else {
    ///
    /// EOS was correctly set to a 1
    ///
    return TRUE;
  }
}

/**
  Determine whether an ACPI OS is present (via the SCI_EN bit)


  @retval TRUE                    ACPI OS is present
  @retval FALSE                   ACPI OS is not present
**/
BOOLEAN
PchSmmGetSciEn (
  VOID
  )
{
  BOOLEAN SciEn;
  UINT32  Pm1Cnt;

  ///
  /// Determine whether an ACPI OS is present (via the SCI_EN bit)
  ///
  Pm1Cnt  = IoRead32 ((UINTN) (mAcpiBaseAddr + R_PCH_ACPI_PM1_CNT));
  SciEn   = (BOOLEAN) ((Pm1Cnt & B_PCH_ACPI_PM1_CNT_SCI_EN) == B_PCH_ACPI_PM1_CNT_SCI_EN);

  return SciEn;
}

/**
  Read a specifying bit with the register
  These may or may not need to change w/ the PCH version; they're highly IA-32 dependent, though.

  @param[in] BitDesc              The struct that includes register address, size in byte and bit number

  @retval TRUE                    The bit is enabled
  @retval FALSE                   The bit is disabled
**/
BOOLEAN
ReadBitDesc (
  CONST PCH_SMM_BIT_DESC  *BitDesc
  )
{
  EFI_STATUS  Status;
  UINT64      Register;
  UINT32      PciBus;
  UINT32      PciDev;
  UINT32      PciFun;
  UINT32      PciReg;
  UINTN       RegSize;
  BOOLEAN     BitWasOne;
  UINTN       ShiftCount;
  UINTN       RegisterOffset;
  UINT32      BaseAddr;
  UINTN       PciBaseAddress;

  ASSERT (BitDesc != NULL);
  ASSERT (!IS_BIT_DESC_NULL (*BitDesc));

  RegSize     = 0;
  Register    = 0;
  ShiftCount  = 0;
  BitWasOne   = FALSE;

  switch (BitDesc->Reg.Type) {

    case ACPI_ADDR_TYPE:
    case TCO_ADDR_TYPE:
      if (BitDesc->Reg.Type == ACPI_ADDR_TYPE) {
        RegisterOffset  = BitDesc->Reg.Data.acpi;
        BaseAddr        = mAcpiBaseAddr;
      } else {
        RegisterOffset  = BitDesc->Reg.Data.tco;
        BaseAddr        = mTcoBaseAddr;
      }
      switch (BitDesc->SizeInBytes) {

        case 0:
          ///
          /// Chances are that this field didn't get initialized.
          /// Check your assignments to bit descriptions.
          ///
          ASSERT (FALSE);
          break;

        case 1:
          RegSize = SMM_IO_UINT8;
          break;

        case 2:
          RegSize = SMM_IO_UINT16;
          break;

        case 4:
          RegSize = SMM_IO_UINT32;
          break;

        case 8:
          RegSize = SMM_IO_UINT64;
          break;

        default:
          ///
          /// Unsupported or invalid register size
          ///
          ASSERT (FALSE);
          break;
      }
      ///
      /// Double check that we correctly read in the acpi base address
      ///
      ASSERT ((BaseAddr != 0x0) && ((BaseAddr & 0x1) != 0x1));

      ShiftCount      = BitDesc->Bit;
      ///
      /// As current CPU Smm Io can only support at most
      /// 32-bit read/write,if Operation is 64 bit,
      /// we do a 32 bit operation according to BitDesc->Bit
      ///
      if (RegSize == SMM_IO_UINT64) {
        RegSize = SMM_IO_UINT32;
        ///
        /// If the operation is for high 32 bits
        ///
        if (BitDesc->Bit >= 32) {
          RegisterOffset += 4;
          ShiftCount -= 32;
        }
      }

      Status = gSmst->SmmIo.Io.Read (
                                 &gSmst->SmmIo,
                                 RegSize,
                                 BaseAddr + RegisterOffset,
                                 1,
                                 &Register
                                 );
      ASSERT_EFI_ERROR (Status);

      if ((Register & (LShiftU64 (BIT_ZERO, ShiftCount))) != 0) {
        BitWasOne = TRUE;
      } else {
        BitWasOne = FALSE;
      }
      break;

    case GPIO_ADDR_TYPE:
    case MEMORY_MAPPED_IO_ADDRESS_TYPE:
      ///
      /// Read the register, and it with the bit to read
      ///
      switch (BitDesc->SizeInBytes) {
        case 1:
          Register = (UINT64) MmioRead8 ((UINTN) BitDesc->Reg.Data.Mmio);
          break;

        case 2:
          Register = (UINT64) MmioRead16 ((UINTN) BitDesc->Reg.Data.Mmio);
          break;

        case 4:
          Register = (UINT64) MmioRead32 ((UINTN) BitDesc->Reg.Data.Mmio);
          break;

        case 8:
          Register                      = (UINT64) MmioRead32 ((UINTN) BitDesc->Reg.Data.Mmio);
          *((UINT32 *) (&Register) + 1) = MmioRead32 ((UINTN) BitDesc->Reg.Data.Mmio + 4);
          break;

        default:
          ///
          /// Unsupported or invalid register size
          ///
          ASSERT (FALSE);
          break;
      }

      Register = Register & (LShiftU64 (BIT0, BitDesc->Bit));
      if (Register) {
        BitWasOne = TRUE;
      } else {
        BitWasOne = FALSE;
      }
      break;

    case PCIE_ADDR_TYPE:
      PciBus  = BitDesc->Reg.Data.pcie.Fields.Bus;
      PciDev  = BitDesc->Reg.Data.pcie.Fields.Dev;
      PciFun  = BitDesc->Reg.Data.pcie.Fields.Fnc;
      PciReg  = BitDesc->Reg.Data.pcie.Fields.Reg;
      PciBaseAddress = MmPciBase (PciBus, PciDev, PciFun);
      switch (BitDesc->SizeInBytes) {

        case 0:
          ///
          /// Chances are that this field didn't get initialized.
          /// Check your assignments to bit descriptions.
          ///
          ASSERT (FALSE);
          break;

        case 1:
          Register = (UINT64) MmioRead8 (PciBaseAddress + PciReg);
          break;

        case 2:
          Register = (UINT64) MmioRead16 (PciBaseAddress + PciReg);
          break;

        case 4:
          Register = (UINT64) MmioRead32 (PciBaseAddress + PciReg);
          break;

        default:
          ///
          /// Unsupported or invalid register size
          ///
          ASSERT (FALSE);
          break;
      }

      if ((Register & (LShiftU64 (BIT_ZERO, BitDesc->Bit))) != 0) {
        BitWasOne = TRUE;
      } else {
        BitWasOne = FALSE;
      }
      break;

    case PCR_ADDR_TYPE:
      ///
      /// Read the register, and it with the bit to read
      ///
      switch (BitDesc->SizeInBytes) {
        case 1:
          PchPcrRead8  (BitDesc->Reg.Data.Pcr.Fields.Pid, BitDesc->Reg.Data.Pcr.Fields.Offset, (UINT8*)  &Register);
          break;

        case 2:
          PchPcrRead16 (BitDesc->Reg.Data.Pcr.Fields.Pid, BitDesc->Reg.Data.Pcr.Fields.Offset, (UINT16*) &Register);
          break;

        case 4:
          PchPcrRead32 (BitDesc->Reg.Data.Pcr.Fields.Pid, BitDesc->Reg.Data.Pcr.Fields.Offset, (UINT32*) &Register);
          break;

        default:
          ///
          /// Unsupported or invalid register size
          ///
          ASSERT (FALSE);
          break;
      }

      Register = Register & (LShiftU64 (BIT0, BitDesc->Bit));
      if (Register) {
        BitWasOne = TRUE;
      } else {
        BitWasOne = FALSE;
      }
      break;

    default:
      ///
      /// This address type is not yet implemented
      ///
      ASSERT (FALSE);
      break;
  }

  return BitWasOne;
}

/**
  Write a specifying bit with the register

  @param[in] BitDesc              The struct that includes register address, size in byte and bit number
  @param[in] ValueToWrite         The value to be wrote
  @param[in] WriteClear           If the rest bits of the register is write clear

**/
VOID
WriteBitDesc (
  CONST PCH_SMM_BIT_DESC  *BitDesc,
  CONST BOOLEAN           ValueToWrite,
  CONST BOOLEAN           WriteClear
  )
{
  EFI_STATUS  Status;
  UINT64      Register;
  UINT64      AndVal;
  UINT64      OrVal;
  UINT32      RegSize;
  UINT32      PciBus;
  UINT32      PciDev;
  UINT32      PciFun;
  UINT32      PciReg;
  UINTN       RegisterOffset;
  UINT32      BaseAddr;
  UINTN       PciBaseAddress;

  ASSERT (BitDesc != NULL);
  ASSERT (!IS_BIT_DESC_NULL (*BitDesc));

  RegSize   = 0;
  Register  = 0;

  if (WriteClear) {
    AndVal = LShiftU64 (BIT_ZERO, BitDesc->Bit);
  } else {
    AndVal = ~(LShiftU64 (BIT_ZERO, BitDesc->Bit));
  }

  OrVal = (LShiftU64 ((UINT32) ValueToWrite, BitDesc->Bit));

  switch (BitDesc->Reg.Type) {

    case ACPI_ADDR_TYPE:
    case TCO_ADDR_TYPE:
      if (BitDesc->Reg.Type == ACPI_ADDR_TYPE) {
        RegisterOffset  = BitDesc->Reg.Data.acpi;
        BaseAddr        = mAcpiBaseAddr;
      } else {
        RegisterOffset  = BitDesc->Reg.Data.tco;
        BaseAddr        = mTcoBaseAddr;
      }

      switch (BitDesc->SizeInBytes) {

        case 0:
          ///
          /// Chances are that this field didn't get initialized.
          /// Check your assignments to bit descriptions.
          ///
          ASSERT (FALSE);
          break;

        case 1:
          RegSize = SMM_IO_UINT8;
          break;

        case 2:
          RegSize = SMM_IO_UINT16;
          break;

        case 4:
          RegSize = SMM_IO_UINT32;
          break;

        case 8:
          RegSize = SMM_IO_UINT64;
          break;

        default:
          ///
          /// Unsupported or invalid register size
          ///
          ASSERT (FALSE);
          break;
      }
      ///
      /// Double check that we correctly read in the acpi base address
      ///
      ASSERT ((BaseAddr != 0x0) && ((BaseAddr & 0x1) != 0x1));

      ///
      /// As current CPU Smm Io can only support at most
      /// 32-bit read/write,if Operation is 64 bit,
      /// we do a 32 bit operation according to BitDesc->Bit
      ///
      if (RegSize == SMM_IO_UINT64) {
        RegSize = SMM_IO_UINT32;
        ///
        /// If the operation is for high 32 bits
        ///
        if (BitDesc->Bit >= 32) {
          RegisterOffset += 4;

          if (WriteClear) {
            AndVal = LShiftU64 (BIT_ZERO, BitDesc->Bit - 32);
          } else {
            AndVal = ~(LShiftU64 (BIT_ZERO, BitDesc->Bit - 32));
          }

          OrVal = LShiftU64 ((UINT32) ValueToWrite, BitDesc->Bit - 32);
        }
      }

      Status = gSmst->SmmIo.Io.Read (
                                 &gSmst->SmmIo,
                                 RegSize,
                                 BaseAddr + RegisterOffset,
                                 1,
                                 &Register
                                 );
      ASSERT_EFI_ERROR (Status);

      Register &= AndVal;
      Register |= OrVal;

      Status = gSmst->SmmIo.Io.Write (
                                 &gSmst->SmmIo,
                                 RegSize,
                                 BaseAddr + RegisterOffset,
                                 1,
                                 &Register
                                 );
      ASSERT_EFI_ERROR (Status);
      break;

    case GPIO_ADDR_TYPE:
    case MEMORY_MAPPED_IO_ADDRESS_TYPE:
      ///
      /// Read the register, or it with the bit to set, then write it back.
      ///
      switch (BitDesc->SizeInBytes) {
        case 1:
          MmioAndThenOr8  ((UINTN) BitDesc->Reg.Data.Mmio, (UINT8)  AndVal, (UINT8)  OrVal);
          break;

        case 2:
          MmioAndThenOr16 ((UINTN) BitDesc->Reg.Data.Mmio, (UINT16) AndVal, (UINT16) OrVal);
          break;

        case 4:
          MmioAndThenOr32 ((UINTN) BitDesc->Reg.Data.Mmio, (UINT32) AndVal, (UINT32) OrVal);
          break;

        case 8:
          Register                      = (UINT64) MmioRead32 ((UINTN) BitDesc->Reg.Data.Mmio);
          *((UINT32 *) (&Register) + 1) = MmioRead32 ((UINTN) BitDesc->Reg.Data.Mmio + 4);
          Register &= AndVal;
          Register |= OrVal;
          MmioWrite32 ((UINTN) BitDesc->Reg.Data.Mmio, (UINT32) Register);
          MmioWrite32 ((UINTN) BitDesc->Reg.Data.Mmio + 4, *((UINT32 *) (&Register) + 1));
          break;

        default:
          ///
          /// Unsupported or invalid register size
          ///
          ASSERT (FALSE);
          break;
      }
      break;

    case PCIE_ADDR_TYPE:
      PciBus  = BitDesc->Reg.Data.pcie.Fields.Bus;
      PciDev  = BitDesc->Reg.Data.pcie.Fields.Dev;
      PciFun  = BitDesc->Reg.Data.pcie.Fields.Fnc;
      PciReg  = BitDesc->Reg.Data.pcie.Fields.Reg;
      PciBaseAddress = MmPciBase (PciBus, PciDev, PciFun);
      switch (BitDesc->SizeInBytes) {

        case 0:
          ///
          /// Chances are that this field didn't get initialized -- check your assignments
          /// to bit descriptions.
          ///
          ASSERT (FALSE);
          break;

        case 1:
          MmioAndThenOr8 (PciBaseAddress + PciReg, (UINT8) AndVal, (UINT8) OrVal);
          break;

        case 2:
          MmioAndThenOr16 (PciBaseAddress + PciReg, (UINT16) AndVal, (UINT16) OrVal);
          break;

        case 4:
          MmioAndThenOr32 (PciBaseAddress + PciReg, (UINT32) AndVal, (UINT32) OrVal);
          break;

        default:
          ///
          /// Unsupported or invalid register size
          ///
          ASSERT (FALSE);
          break;
      }
      break;

    case PCR_ADDR_TYPE:
      ///
      /// Read the register, or it with the bit to set, then write it back.
      ///
      switch (BitDesc->SizeInBytes) {
        case 1:
          PchPcrAndThenOr8  ((PCH_SBI_PID) BitDesc->Reg.Data.Pcr.Fields.Pid, (UINT16) BitDesc->Reg.Data.Pcr.Fields.Offset, (UINT8)  AndVal, (UINT8)  OrVal);
          break;

        case 2:
          PchPcrAndThenOr16 ((PCH_SBI_PID) BitDesc->Reg.Data.Pcr.Fields.Pid, (UINT16) BitDesc->Reg.Data.Pcr.Fields.Offset, (UINT16) AndVal, (UINT16) OrVal);
          break;

        case 4:
          PchPcrAndThenOr32 ((PCH_SBI_PID) BitDesc->Reg.Data.Pcr.Fields.Pid, (UINT16) BitDesc->Reg.Data.Pcr.Fields.Offset, (UINT32) AndVal, (UINT32) OrVal);
          break;

        default:
          ///
          /// Unsupported or invalid register size
          ///
          ASSERT (FALSE);
          break;
      }
      break;

    default:
      ///
      /// This address type is not yet implemented
      ///
      ASSERT (FALSE);
      break;
  }
}
