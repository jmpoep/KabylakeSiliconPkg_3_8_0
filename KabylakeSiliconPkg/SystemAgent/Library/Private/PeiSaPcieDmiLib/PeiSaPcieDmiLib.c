/** @file
  SA PCIe/DMI PEI Initialization library

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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
#include <SystemAgent/Library/Private/PeiSaPcieInitLib/LowLevel/SaPegLowLevel.h>

///
/// Functions
///

/**
  Programs the PCIe/DMI recipe.

  @param[in]  DmiBar                      - DMIBAR
  @param[in]  MchBar                      - MCHBAR
  @param[in]  Gen3CtlePeaking             - Array of CTLE Peaking values to program per bundle
  @param[in]  Gen3CtlePeakingLength       - Length of the Gen3CtlePeaking array
  @param[in]  Gen3RxCtleOverride          - RxCTLE override configuration
  @param[in]  ProgramDmiRecipe            - Set to TRUE to program DMI, FALSE to program PCIe
**/
VOID
EFIAPI
SklPegDmiRecipe (
  IN  UINT64                            DmiBar,
  IN  UINT32                            MchBar,
  IN  UINT8                             *Gen3CtlePeaking,
  IN  UINT8                             Gen3CtlePeakingLength,
  IN  UINT8                             Gen3RxCtleOverride,
  IN  BOOLEAN                           ProgramDmiRecipe
  )
{
  UINTN             BaseAddress;
  UINTN             Index;
  UINTN             BundlesCount;
  UINTN             LanesCount;
  UINT32            Mask32And;
  UINT32            Data32Or;
  UINT64            MsrValue;
  UINT32            Register;
  CPU_SKU           CpuSku;

  CpuSku      = GetCpuSku ();

  if (ProgramDmiRecipe) {
    ///
    /// DMI
    ///
    LanesCount  = SA_DMI_MAX_LANE;
    BaseAddress = (UINTN) DmiBar;
  } else {
    ///
    /// PEG
    ///
    LanesCount  = SA_PEG_MAX_LANE;
    BaseAddress = MmPciBase (SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, SA_PEG10_FUN_NUM);
  }

  BundlesCount = LanesCount >> 1;

  ///
  ///
  /// AFEBND0CFG1[24:22] IGACQ = 0x0 (DMI & PEG)
  ///
  Mask32And = (UINT32) ~(BIT24 | BIT23 | BIT22);
  Data32Or  = 0x0 << 22;
  if (ProgramDmiRecipe) {
    ///
    /// AFEBND0CFG1[28:25] DFEIDACPD = 0x3 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT28 | BIT27 | BIT26 | BIT25);
    Data32Or  |= 0x3 << 25;
    ///
    /// AFEBND0CFG1[21:16] PGACQ = 10 or 0xA (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16);
    Data32Or  |= 0xA << 16;
    ///
    /// AFEBND0CFG1[11:10] OFFCORGAIN = 0x3 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT11 | BIT10);
    Data32Or  |= 0x3 << 10;
  }
  for (Index = 0; Index < BundlesCount; Index++) {
    MmioAndThenOr32 (BaseAddress + R_SA_PEG_AFEBND0CFG1_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
  }

  ///
  ///
  if (ProgramDmiRecipe) {
    ///
    /// AFEBND0CFG2[31:30] RXVCMDSSEL = 0x1 (DMI)
    ///
    Mask32And = (UINT32) ~(BIT31 | BIT30);
    Data32Or  = 0x1 << 30;
    ///
    /// AFEBND0CFG2[23:23] G3BYPCOEFF = 0x1 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT23);
    Data32Or  |= 0x1 << 23;
    ///
    /// AFEBND0CFG2[7:1] TXEQCUR = 0x14 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1);
    Data32Or  |= 0x14 << 1;
    ///
    /// AFEBND0CFG2[21:15] TXEQPOSTCUR = 0x2 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16 | BIT15);
    Data32Or  |= 0x2 << 15;
    ///
    /// AFEBND0CFG2[14:8] TXEQPRECUR = 0x2 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT14 | BIT13 | BIT12 | BIT11 | BIT10 | BIT9 | BIT8);
    Data32Or  |= 0x2 << 8;
  } else {
    ///
    /// AFEBND0CFG2[31:30] RXVCMDSSEL = 0x1 (PEG)
    ///
    Mask32And = (UINT32) ~(BIT31 | BIT30);
    Data32Or  = 0x1 << 30;
    ///
    /// AFEBND0CFG2[7:1] TXEQCUR = 0x2A (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1);
    Data32Or  |= 0x2A << 1;
    ///
    /// AFEBND0CFG2[21:15] TXEQPOSTCUR = 0xC (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16 | BIT15);
    Data32Or  |= 0xC << 15;
    ///
    /// AFEBND0CFG2[14:8] TXEQPRECUR = 0x8 (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT14 | BIT13 | BIT12 | BIT11 | BIT10 | BIT9 | BIT8);
    Data32Or  |= 0x8 << 8;
  }
  for (Index = 0; Index < BundlesCount; Index++) {
    MmioAndThenOr32 (BaseAddress + R_SA_PEG_AFEBND0CFG2_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
  }

  ///
  ///
  /// AFEBND0CFG3[24:21] RXRTBIN = 0x3 (PEG & DMI)
  ///
  Mask32And = (UINT32) ~(BIT24 | BIT23 | BIT22 | BIT21);
  Data32Or  = 0x3 << 21;
  ///
  /// AFEBND0CFG3[29:26] TXRTBIN = 0x4 (PEG & DMI)
  ///
  Mask32And &= (UINT32) ~(BIT29 | BIT28 | BIT27 | BIT26);
  Data32Or  |= 0x4 << 26;
  if (ProgramDmiRecipe) {
    ///
    /// AFEBND0CFG3[10:5] PGTRK = 10 or 0xA (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT10 | BIT9 | BIT8 | BIT7 | BIT6 | BIT5);
    Data32Or  |= (0xA << 5);
  } else {
    ///
    /// AFEBND0CFG3[10:5] PGTRK = 0x8 (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT10 | BIT9 | BIT8 | BIT7 | BIT6 | BIT5);
    Data32Or  |= (0x8 << 5);
  }
  for (Index = 0; Index < BundlesCount; Index++) {
    MmioAndThenOr32 (BaseAddress + R_SA_PEG_AFEBND0CFG3_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
  }

  ///
  ///
  /// AFEBND0CFG4[13:10] G2RXCTLEPEAK = 0x2 (PEG & DMI)
  ///
  Mask32And = (UINT32) ~(BIT13 | BIT12 | BIT11 | BIT10);
  Data32Or  = (0x2 << 10);
  for (Index = 0; Index < BundlesCount; Index++) {
    MmioAndThenOr32 (BaseAddress + R_SA_PEG_AFEBND0CFG4_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
  }

  ///
  ///
  if (ProgramDmiRecipe) {
    ///
    /// AFEBND0CFG4[31:25] AFEBNDSPARE = 64 or 0x40  (DMI)
    ///
    Mask32And = (UINT32) ~(BIT31 | BIT30 | BIT29 | BIT28 | BIT27 | BIT26 |BIT25);
    Data32Or  = (((UINT32) 0x40) << 25);
  } else {
    ///
    /// AFEBND0CFG4[31:25] AFEBNDSPARE = 48 or 0x30  (PEG)
    ///
    Mask32And = (UINT32) ~(BIT31 | BIT30 | BIT29 | BIT28 | BIT27 | BIT26 |BIT25);
    Data32Or  = (0x30 << 25);
    ///
    /// AFEBND0CFG4[9:6] G3RXCTLEPEAK = 0x0 [48dec] (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT9 | BIT8 | BIT7 | BIT6);
    Data32Or  |= (0x0 << 5);
  }
  for (Index = 0; Index < BundlesCount; Index++) {
    MmioAndThenOr32 (BaseAddress + R_SA_PEG_AFEBND0CFG4_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
  }

  ///
  ///
  if (ProgramDmiRecipe) {
    ///
    /// AFECMNCFG1[30:29] IBIAS = 0x1 (DMI)
    ///
    Mask32And = (UINT32) ~(BIT30 | BIT29);
    Data32Or  = 0x1 << 29;
    ///
    /// AFEBND0CFG4[16:14] PIBIASICTRLGEN3 = 0x4 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT16 | BIT15 | BIT14);
    Data32Or  |= (0x4 << 14);
    MmioAndThenOr32 (BaseAddress + R_SA_DMIBAR_AFECMNCFG1_OFFSET, Mask32And, Data32Or);
  }
  ///
  ///
  if (ProgramDmiRecipe) {
    ///
    /// AFECMNCFG2[19:15] VREFRXDET = 0x17 or 23 (DMI)
    ///
    Mask32And = (UINT32) ~(BIT19 | BIT18 | BIT17 | BIT16 | BIT15);
    Data32Or  = 0x17 << 15;
    ///
    /// AFECMNCFG2[9:4] RXINCMSEL = 0x4 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT9 | BIT8 | BIT7 | BIT6 | BIT5 | BIT4);
    Data32Or  |= 0x4 << 4;
    MmioAndThenOr32 (BaseAddress + R_SA_DMIBAR_AFECMNCFG2_OFFSET, Mask32And, Data32Or);
  }

  ///
  ///
  /// AFELN0CFG0[4:0] G23RXVREF = 0xA (Peg & DMI)
  ///
  Mask32And = (UINT32) ~(BIT4 | BIT3 | BIT2 | BIT1 | BIT0);
  Data32Or  = 0xA;
  for (Index = 0; Index < LanesCount; Index++) {
    MmioAndThenOr32 (BaseAddress + R_SA_PEG_AFELN0CFG0_OFFSET + (Index * LANE_STEP), Mask32And, Data32Or);
  }

  ///
  ///
  /// AFELN0CFG1[11] CDRPDDATMODE = 0x1 (Peg & DMI)
  ///
  Mask32And = (UINT32) ~(BIT11);
  Data32Or  = 0x1 << 11;
  if (ProgramDmiRecipe) {
    ///
    /// AFELN0CFG1[8:4] G1RXVREFSEL = 0xC (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT8 | BIT7 | BIT6 | BIT5 | BIT4);
    Data32Or  |= 0xC << 4;
  }
  for (Index = 0; Index < LanesCount; Index++) {
    MmioAndThenOr32 (BaseAddress + R_SA_PEG_AFELN0CFG1_OFFSET + (Index * LANE_STEP), Mask32And, Data32Or);
  }

  ///
  ///
  if (ProgramDmiRecipe) {
    ///
    /// AFELN0VMTX2[22]    RESSEL_OVRD_EN = 0x1 (DMI)
    ///
    Mask32And = (UINT32) ~(BIT22);
    Data32Or  = 0x1 << 22;
    ///
    /// AFELN0VMTX2[21:16] PI_RESSEL_OVRD = 0x10 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16);
    Data32Or  |= 0x10 << 16;
    ///
    /// AFELN0VMTX2[15:8] SWING_CONTROL = 136 or 0x88 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT15 | BIT14 | BIT13 | BIT12 | BIT11 | BIT10 | BIT9 | BIT8);
    Data32Or  |= 0x88 << 8;
  } else {
    ///
    /// AFELN0VMTX2[21:16] PI_RESSEL_OVRD = 0x10 (PEG)
    ///
    Mask32And = (UINT32) ~(BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16);
    Data32Or  = 0x10 << 16;
    ///
    /// AFELN0VMTX2[22]    RESSEL_OVRD_EN = 0x1 (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT22);
    Data32Or  |= 0x1 << 22;
    ///
    /// AFELN0VMTX2[15:8]= 0x00 Full (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT15 | BIT14 | BIT13 | BIT12 | BIT11 | BIT10 | BIT9 | BIT8);
    Data32Or  |= 0x00 << 8;
  }
  for (Index = 0; Index < LanesCount; Index++) {
    MmioAndThenOr32 (BaseAddress + R_SA_PEG_AFELN0VMTX2_OFFSET + (Index * LANE_STEP), Mask32And, Data32Or);
  }

  ///
  ///
  if (ProgramDmiRecipe) {
    ///
    /// AFELN0IOCFG0[14:12] RXD_SUM_GAIN_GEN3 = 0x0 (DMI)
    ///
    Mask32And = (UINT32) ~(BIT14 | BIT13 | BIT12);
    Data32Or  = 0x0 << 12;
    ///
    /// AFELN0IOCFG0[11:9] RXD_SUM_GAIN_GEN2 = 0x1 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT12 | BIT10 | BIT9);
    Data32Or  |= 0x1 << 9;
    ///
    /// AFELN0IOCFG0[8:6] RXD_SUM_GAIN_GEN1 = 0x2 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT8 | BIT7 | BIT6);
    Data32Or  |= 0x2 << 6;
  } else {
    ///
    /// AFELN0IOCFG0[14:12] RXD_SUM_GAIN_GEN3 = 0x3 (PEG)
    ///
    Mask32And = (UINT32) ~(BIT14 | BIT13 | BIT12);
    Data32Or  = 0x3 << 12;
  }
  for (Index = 0; Index < LanesCount; Index++) {
    MmioAndThenOr32 (BaseAddress + R_SA_PEG_AFELN0IOCFG0_OFFSET + (Index * LANE_STEP), Mask32And, Data32Or);
  }

  ///
  ///
  /// BND0SPARE[29:27] GEN3DFEIDACPD = 0x3 (PEG & DMI)
  ///
  Mask32And = (UINT32) ~(BIT29 | BIT28 | BIT27);
  Data32Or  = 0x3 << 27;
  if (ProgramDmiRecipe) {
    ///
    /// BND0SPARE[30:30] GEN3SUMBIASSEL = 0x0 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT30);
    Data32Or  |= 0x0 << 30;
    ///
    /// BND0SPARE[25:23] GEN2DFEIDACPD = 0x3 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT25 | BIT24 | BIT23);
    Data32Or  |= 0x3 << 23;
    ///
    /// BND0SPARE[18:17] GEN3DFELSBSEL = 0x0 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT18 | BIT17);
    Data32Or  |= 0x0 << 17;
    ///
    /// BND0SPARE[16:15] GEN2DFELSBSEL = 0x1 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT16 | BIT15);
    Data32Or  |= 0x1 << 15;
    ///
    /// BND0SPARE[14:13] GEN3DFESUM_MFC_10GEN = 0x0 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT14 | BIT13);
    Data32Or  |= 0x0 << 13;
    ///
    /// BND0SPARE[10:9] GEN3DFESUMADDMFC = 0x0 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT10 | BIT9);
    Data32Or  |= 0x0 << 9;
    ///
    /// BND0SPARE[7:6] GEN2DFESUMADDMFC = 0x0 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT7 | BIT6);
    Data32Or  |= 0x0 << 6;
  } else {
    ///
    /// BND0SPARE[30:30] GEN3SUMBIASSEL = 0x0 (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT30);
    Data32Or  |= 0x0 << 30;
    ///
    /// BND0SPARE[25:23] GEN2DFEIDACPD = 0x2 (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT25 | BIT24 | BIT23);
    Data32Or  |= 0x2 << 23;
    ///
    /// BND0SPARE[18:17] GEN3DFELSBSEL = 0x0 (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT18 | BIT17);
    Data32Or  |= 0x0 << 17;
    ///
    /// BND0SPARE[14:13] GEN3DFESUM_MFC_10GEN = 0x0 (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT14 | BIT13);
    Data32Or  |= 0x0 << 13;
    ///
    /// BND0SPARE[10:9] GEN3DFESUMADDMFC = 0x0 (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT10 | BIT9);
    Data32Or  |= 0x0 << 9;
    ///
    /// BND0SPARE[7:6] GEN2DFESUMADDMFC = 0x0 (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT7 | BIT6);
    Data32Or  |= 0x0 << 6;
  }
  for (Index = 0; Index < BundlesCount; Index++) {
    MmioAndThenOr32 (BaseAddress + R_SA_PEG_BND0SPARE_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
  }

  ///
  ///
  if (ProgramDmiRecipe) {
    ///
    /// Set CFG5[14:11] UPCFGSLVTMR = 4
    ///
    Mask32And = (UINT32) ~(BIT14 | BIT13 | BIT12 | BIT11);
    Data32Or  = (UINT32)  (4 << 11);
    MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_DMIBAR_CFG5_OFFSET), Mask32And, Data32Or);
  }

  ///
  ///
  /// EQCFG[0] EXTEIEOS = 0x1 (Peg & DMI)
  ///
  Mask32And = (UINT32) ~(BIT0);
  Data32Or  = 0x1 << 0;
  if (!ProgramDmiRecipe) {
    ///
    /// EQCFG[25:20] LF = 0x14
    ///
    Mask32And &= (UINT32) ~(BIT25 | BIT24 | BIT23 | BIT22 | BIT21 | BIT20);
    Data32Or  |= 0x14 << 20;
    ///
    /// EQCFG[31:26] FS = 0x3E
    ///
    Mask32And &= (UINT32) ~(BIT31 | BIT30 | BIT29 | BIT28 | BIT27 | BIT26);
    Data32Or  |= 0x3E << 26;
  }
  MmioAndThenOr32 (BaseAddress + R_SA_PEG_EQCFG_OFFSET, Mask32And, Data32Or);
  if (!ProgramDmiRecipe) {
    MmioAndThenOr32 (
      MmPciBase (SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, SA_PEG11_FUN_NUM) +
      R_SA_PEG_EQCFG_OFFSET,
      Mask32And,
      Data32Or
      );
    MmioAndThenOr32 (
      MmPciBase (SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, SA_PEG12_FUN_NUM) +
      R_SA_PEG_EQCFG_OFFSET,
      Mask32And,
      Data32Or
      );
  }
  ///
  /// EQCFG[1] BYPADFSM = 0x1 (DMI)
  ///
  if (ProgramDmiRecipe) {
    Mask32And = (UINT32) ~(BIT1);
    Data32Or  = 0x1 << 1;
    MmioAndThenOr32 (BaseAddress + R_SA_PEG_EQCFG_OFFSET, Mask32And, Data32Or);
  }
  ///
  /// EQPH3[17:0] PH3_COEFF = 0x160C7 (DMI) This requires to set and clear PH3_COEFF_CTRL for each lane
  ///
  if (ProgramDmiRecipe) {
    Data32Or  = 0x160C7;
    for (Index = 0; Index < LanesCount; Index++) {
      MmioWrite32 (BaseAddress + R_SA_PEG_EQPH3_OFFSET, Data32Or | (Index << 19) | BIT18);
      MmioAnd32 (BaseAddress + R_SA_PEG_EQPH3_OFFSET, (UINT32) ~(BIT20 | BIT19 | BIT18));
    }
  }

  ///
  ///
  /// Preset Definitions
  ///
  if (!ProgramDmiRecipe) {
    MmioWrite32 (BaseAddress + R_SA_PEG_EQPRESET1_2_OFFSET,   0x32012B00);
    MmioWrite32 (BaseAddress + R_SA_PEG_EQPRESET2_3_4_OFFSET, 0x003B000C);
    MmioWrite32 (BaseAddress + R_SA_PEG_EQPRESET4_5_OFFSET,   0x00F802B4);
    MmioWrite32 (BaseAddress + R_SA_PEG_EQPRESET6_7_OFFSET,   0x34280D88);
    MmioWrite32 (BaseAddress + R_SA_PEG_EQPRESET7_8_9_OFFSET, 0x09369200);
    MmioWrite32 (BaseAddress + R_SA_PEG_EQPRESET9_10_OFFSET,  0x00C8C26C);
    MmioWrite32 (BaseAddress + R_SA_PEG_EQPRESET11_OFFSET,    0x00016A00);
  }

  if ((CpuSku  == EnumCpuHalo) || (CpuSku  == EnumCpuTrad)) {
    ///
    ///
    if (ProgramDmiRecipe) {
      ///
      /// AFE_PH3_CFG0_BND_0[31:30] FFEWIN_CTRL = 0x0 (DMI)
      ///
      Data32Or = 0x0 << 30;
      ///
      /// AFE_PH3_CFG0_BND_0[29:28] CYCLES_CTRL = 0x0 (DMI)
      ///
      Data32Or |= 0x0 << 28;
      ///
      /// AFE_PH3_CFG0_BND_0[27:25] PH3CDR_CTL = 0x1 (DMI)
      ///
      Data32Or |= 0x1 << 25;
      ///
      /// AFE_PH3_CFG0_BND_0[24:21] PTRNSEL = 0x0 (DMI)
      ///
      Data32Or |= 0x0 << 21;
      ///
      /// AFE_PH3_CFG0_BND_0[20:18] INITPS = 0x0 (DMI)
      ///
      Data32Or |= 0x0 << 18;
      ///
      /// AFE_PH3_CFG0_BND_0[17:14] INITCTLEP = 0x4 (DMI)
      ///
      Data32Or |= 0x4 << 14;
      ///
      /// AFE_PH3_CFG0_BND_0[13:12] DFX_CTRL = 0x0 (DMI)
      ///
      Data32Or |= 0x0 << 12;
    } else {
      ///
      /// AFE_PH3_CFG0_BND_0[31:30] FFEWIN_CTRL = 0x0 (PEG)
      ///
      Data32Or = 0x0 << 30;
      ///
      /// AFE_PH3_CFG0_BND_0[29:28] CYCLES_CTRL = 0x0 (PEG)
      ///
      Data32Or |= 0x0 << 28;
      ///
      /// AFE_PH3_CFG0_BND_0[27:25] PH3CDR_CTL = 0x1 (PEG)
      ///
      Data32Or |= 0x1 << 25;
      ///
      /// AFE_PH3_CFG0_BND_0[24:21] PTRNSEL = 0x0 (PEG)
      ///
      Data32Or |= 0x0 << 21;
      ///
      /// AFE_PH3_CFG0_BND_0[20:18] INITPS = 0x1 (PEG)
      ///
      Data32Or |= 0x1 << 18;
      ///
      /// AFE_PH3_CFG0_BND_0[17:14] INITCTLEP = 0x2 (PEG)
      ///
      Data32Or |= 0x2 << 14;
      ///
      /// AFE_PH3_CFG0_BND_0[13:12] DFX_CTRL = 0x0 (PEG)
      ///
      Data32Or |= 0x0 << 12;
    }
    for (Index = 0; Index < BundlesCount; Index++) {
      if (!ProgramDmiRecipe) {
        Register = R_SA_MSRIO_PEG_AFE_PH3_CFG0_BND_0_OFFSET + (Index * BUNDLE_STEP);
      } else {
        Register = R_SA_MSRIO_DMIBAR_AFE_PH3_CFG0_BND_0_OFFSET + (Index * BUNDLE_STEP);
      }
      MsrValue = (UINT64) (LShiftU64 ((UINT64) Register, 32) | (UINT64) Data32Or);
      AsmWriteMsr64 (R_SA_MSRIO_ADDRESS, MsrValue);
    }
    ///
    ///
    if (ProgramDmiRecipe) {
      ///
      /// AFE_PH3_CFG1_BND_0[31:16] PH3SUP_CTRL = 384 or 0x180 (DMI)
      ///
      Data32Or = 0x180 << 16;
      ///
      /// AFE_PH3_CFG1_BND_0[15:0] CTLEADJUST_CTRL = 21878 or 0x5576 (DMI)
      ///
      Data32Or |= 0x5576 << 0;
    } else {
      ///
      /// AFE_PH3_CFG1_BND_0[31:16] PH3SUP_CTRL = 384 or 0x180 (PEG)
      ///
      Data32Or = 0x180 << 16;
      ///
      /// AFE_PH3_CFG1_BND_0[15:0] CTLEADJUST_CTRL = 21878 or 0x5576 (PEG)
      ///
      Data32Or |= 0x5576 << 0;
    }
    for (Index = 0; Index < BundlesCount; Index++) {
      if (!ProgramDmiRecipe) {
        Register = R_SA_MSRIO_PEG_AFE_PH3_CFG1_BND_0_OFFSET + (Index * BUNDLE_STEP);
      } else {
        Register = R_SA_MSRIO_DMIBAR_AFE_PH3_CFG1_BND_0_OFFSET + (Index * BUNDLE_STEP);
      }
      MsrValue = (UINT64) (LShiftU64 ((UINT64) Register, 32) | (UINT64) Data32Or);
      AsmWriteMsr64 (R_SA_MSRIO_ADDRESS, MsrValue);
    }

    ///
    ///
    if (ProgramDmiRecipe) {
      ///
      /// AFE_PH3_CFG2_BND_0[2:0] AVG_CTRL = 0x2 (DMI)
      ///
      Data32Or = 0x2 << 0;
      ///
      /// AFE_PH3_CFG2_BND_0[3:3] CR_EN_PH3_NEW_CTLE_PK = 0x0 (DMI)
      ///
      Data32Or |= 0x0 << 3;
      ///
      /// Only applicable to DT/Halo
      ///
      if ((CpuSku  == EnumCpuHalo) || (CpuSku  == EnumCpuTrad)) {
        ///
        /// AFE_PH3_CFG2_BND_0[18:18] CR_ENABLE_ROUND_FIX_PH3 = 0x1 (DMI)
        ///
        Data32Or |= 0x1 << 18;
      }
    } else {
      ///
      /// AFE_PH3_CFG2_BND_0[2:0] AVG_CTRL = 0x2 (PEG)
      ///
      Data32Or = 0x2 << 0;
      ///
      /// AFE_PH3_CFG2_BND_0[3:3] CR_EN_PH3_NEW_CTLE_PK = 0x1 only if RxCTLE Override is disabled (PEG)
      ///
      if (Gen3RxCtleOverride == 0) {
      Data32Or |= 0x1 << 3;
      }
      ///
      /// Only applicable to DT/Halo
      ///
      if ((CpuSku  == EnumCpuHalo) || (CpuSku  == EnumCpuTrad)) {
        ///
        /// AFE_PH3_CFG2_BND_0[18:18] CR_ENABLE_ROUND_FIX_PH3 = 0x1 (PEG)
        ///
        Data32Or |= 0x1 << 18;
      }
    }
    for (Index = 0; Index < BundlesCount; Index++) {
      if (!ProgramDmiRecipe) {
        Register = R_SA_MSRIO_PEG_AFE_PH3_CFG2_BND_0_OFFSET + (Index * BUNDLE_STEP);
      } else {
        Register = R_SA_MSRIO_DMIBAR_AFE_PH3_CFG2_BND_0_OFFSET + (Index * BUNDLE_STEP);
      }
      MsrValue = (UINT64) (LShiftU64 ((UINT64) Register, 32) | (UINT64) Data32Or);
      AsmWriteMsr64 (R_SA_MSRIO_ADDRESS, MsrValue);
    }
  }

  ///
  /// AFEBND0CFG4[9:6] G3RXCTLEPEAK = Read from configuration. Default = 0x0 PEG, 0x0 DMI. (PEG & DMI)
  ///
  Mask32And = (UINT32) ~(BIT9 | BIT8 | BIT7 | BIT6);
  for (Index = 0; Index < BundlesCount; Index++) {
    if ((Index < Gen3CtlePeakingLength) && (Gen3CtlePeaking[Index] < 16)) {
      Data32Or = Gen3CtlePeaking[Index] << 6;
    } else {
      if (ProgramDmiRecipe) {
        Data32Or = 0 << 6;
      } else {
        Data32Or = 0 << 6;
      }
      DEBUG ((DEBUG_WARN, "CTLE Peaking array incorrect length or invalid value!\n"));
      ASSERT (FALSE);
      return;
    }
    MmioAndThenOr32 (BaseAddress + R_SA_PEG_AFEBND0CFG4_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
  }
  return;
}

