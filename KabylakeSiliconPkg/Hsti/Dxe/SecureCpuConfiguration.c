/** @file
  This file contains the tests for the SecureCPUConfiguration bit

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

@par Specification
**/

#include "HstiSiliconDxe.h"

/**
  Run tests for SecureCPUConfiguration bit
**/
VOID
CheckSecureCpuConfiguration (
  VOID
  )
{
  EFI_STATUS                        Status;
  BOOLEAN                           Result;
  UINTN                             CpuNumber;
  UINTN                             CpuIndex;
  CPUID_VERSION_INFO_ECX            Ecx;
  UINT8                             SramC;
  UINT32                            TsegMB;
  UINT32                            Bgsm;
  UINT64                            SmrrBase;
  UINT64                            SmrrMask;
  UINT64                            MasterSmrrBase;
  UINT64                            MasterSmrrMask;
  UINT64                            PrmrrBase;
  UINT64                            PrmrrMask;
  BOOLEAN                           PrmrrEnabled;
  BOOLEAN                           PrmrrsConsistent;
  UINT64                            MasterPrmrrBase;
  UINT64                            MasterPrmrrMask;
  UINT64                            UncorePrmrrBase;
  UINT64                            UncorePrmrrMask;
  FIRMWARE_INTERFACE_TABLE_ENTRY    *FitEntry;
  UINT32                            EntryNum;
  UINT64                            FitTableOffset;
  UINT32                            FitIndex;
  UINTN                             FoundValidUcode;
  CHAR16                            *HstiErrorString;
  MEMORY_PLATFORM_DATA_HOB          *MemInfo;
  UINT64                            SmmFeatureControl;
  MSR_IA32_FEATURE_CONTROL_REGISTER Ia32FeatureControlMsr;
  MSR_IA32_MTRRCAP_REGISTER         MtrrCapMsr;
  MSR_IA32_BIOS_SIGN_ID_REGISTER    Ia32BiosSignIdMsr;

  if ((mFeatureImplemented[0] & HSTI_BYTE0_SECURE_CPU_CONFIGURATION) == 0) {
    return;
  }

  Result = TRUE;

  DEBUG ((DEBUG_INFO, "  Table 3-1. CPU Security Configuration\n"));

  CpuNumber = GetCpuNumber ();
  for (CpuIndex = 0; CpuIndex < CpuNumber; CpuIndex++) {
    DEBUG ((DEBUG_INFO, "  [CPU - 0x%x]\n", CpuIndex));

    DEBUG ((DEBUG_INFO, "    1. Microcode Update Revision\n"));
    ProcessorWriteMsr64 (CpuIndex, MSR_IA32_BIOS_SIGN_ID, 0);
    ProcessorCpuid (CpuIndex, CPUID_VERSION_INFO, NULL, NULL, NULL, NULL);
    Ia32BiosSignIdMsr.Uint64 = ProcessorReadMsr64 (CpuIndex, MSR_IA32_BIOS_SIGN_ID);
    if (Ia32BiosSignIdMsr.Bits.MicrocodeUpdateSignature == 0) {
      HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_1 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_1);
      Status = HstiLibAppendErrorString (
                 PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                 NULL,
                 HstiErrorString
                 );
      ASSERT_EFI_ERROR (Status);
      Result = FALSE;
      FreePool (HstiErrorString);
    }

    DEBUG ((DEBUG_INFO, "    2. Sample Part \n"));

    if ((ProcessorReadMsr64 (CpuIndex, MSR_PLATFORM_INFO) & BIT27) != 0) {
      DEBUG ((DEBUG_INFO, "Fail: This is a sample part\n"));

      HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_2 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_2);
      Status = HstiLibAppendErrorString (
                 PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                 NULL,
                 HstiErrorString
                 );
      ASSERT_EFI_ERROR (Status);
      Result = FALSE;
      FreePool (HstiErrorString);
    }

    DEBUG ((DEBUG_INFO, "    3. IA32_FEATURE_CONTROL MSR Lock\n"));

    Ia32FeatureControlMsr.Uint64 = ProcessorReadMsr64 (CpuIndex, MSR_IA32_FEATURE_CONTROL);
    if (Ia32FeatureControlMsr.Bits.Lock == 0) {
      DEBUG ((DEBUG_INFO, "Fail: This is a sample part\n"));

      HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_3 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_3);
      Status = HstiLibAppendErrorString (
                 PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                 NULL,
                 HstiErrorString
                 );
      ASSERT_EFI_ERROR (Status);
      Result = FALSE;
      FreePool (HstiErrorString);
    }

    DEBUG ((DEBUG_INFO, "    4. SMM_FEATURE_CONTROL MSR Lock\n"));

    SmmFeatureControl = ProcessorReadMsr64 (CpuIndex, MSR_SMM_FEATURE_CONTROL);

    DEBUG ((DEBUG_INFO, "    4. SMM_CODE_CHK_EN TEST\n"));

    if ((SmmFeatureControl & B_SMM_CODE_CHK_EN) == 0) {

      DEBUG ((DEBUG_INFO, "Fail: SMM Code Fetch outside SMRAM dectect feature disabled\n"));

      HstiErrorString = BuildHstiErrorString(HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_4 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_B);
      Status = HstiLibAppendErrorString(
                 PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                 NULL,
                 HstiErrorString
                 );
      ASSERT_EFI_ERROR (Status);
      Result = FALSE;
      FreePool(HstiErrorString);
    }

    DEBUG ((DEBUG_INFO, "    SMM_FEATURE_CONTROL MSR Lock\n"));

    if ((SmmFeatureControl & B_SMM_FEATURE_CONTROL_LOCK) == 0) {

      DEBUG ((DEBUG_INFO, "Fail: Smm feature control msr not locked\n"));

      HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_4 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_4);
      Status = HstiLibAppendErrorString (
                 PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                 NULL,
                 HstiErrorString
                 );
      ASSERT_EFI_ERROR (Status);
      Result = FALSE;
      FreePool (HstiErrorString);
    }

    DEBUG ((DEBUG_INFO, "    5. FEATURE_CONFIG MSR  Lock\n"));

    ProcessorCpuid (CpuIndex, CPUID_VERSION_INFO, NULL, NULL, &Ecx.Uint32, NULL);
    if (Ecx.Bits.AESNI == 1) {
      if ((ProcessorReadMsr64 (CpuIndex, MSR_IA32_FEATURE_CONFIG) & B_IA32_FEATURE_CONFIG_LOCK) == 0) {
        DEBUG ((DEBUG_INFO, "Fail: Feature control msr not locked\n"));

        HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_5 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_5);
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
  }

  DEBUG ((DEBUG_INFO, "    6. FIT Patch Support \n"));

  FitTableOffset = *(UINT64 *) (UINTN) (BASE_4GB - 0x40);
  FitEntry = (FIRMWARE_INTERFACE_TABLE_ENTRY *) (UINTN) FitTableOffset;

  if ((FitEntry <= (FIRMWARE_INTERFACE_TABLE_ENTRY *) (UINTN) 0xFF000000) ||
      (FitEntry >= (FIRMWARE_INTERFACE_TABLE_ENTRY *) (UINTN) 0xFFFFFFB0) ||
      (FitEntry[0].Address != *(UINT64 *) "_FIT_   ")) {
    DEBUG ((DEBUG_INFO, "Fail: Fit header incorrect\n"));


    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_6 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_6);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  if ((FitEntry[0].Size[0] == 0) ||
      ((FitEntry[0].Size[0] * 16) + FitEntry > (FIRMWARE_INTERFACE_TABLE_ENTRY *) (UINTN) 0xFFFFFFC0 ) ||
      (FitEntry[0].Type != 0) ||
      (FitEntry[0].Version != 0x0100) ||
      (FitEntry[0].Reserved != 0)) {
    DEBUG ((DEBUG_INFO, "Fail: Fit table sanity checks failed\n"));


    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_6 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_6);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  EntryNum = *(UINT32 *) (&FitEntry[0].Size[0]) & 0xFFFFFF;
  FoundValidUcode = 0;

  for (FitIndex = 0; FitIndex < EntryNum; FitIndex++) {
    if (FitEntry[FitIndex].Type == FIT_TABLE_TYPE_HEADER) {
      continue;
    }

    if (FitEntry[FitIndex].Type == FIT_TABLE_TYPE_SKIP) {
      continue;
    }

    if (FitEntry[FitIndex].Type == FIT_TABLE_TYPE_MICROCODE) {
      if (MmioRead32 (FitEntry[FitIndex].Address) == 0xFFFFFFFF) {
        continue;
      }

      if (FitEntry[FitIndex].Address > BASE_4GB) {
        FoundValidUcode = 0;
        break;
      }

      if (MmioRead32 (FitEntry[FitIndex].Address) != 0x00000001) {
        FoundValidUcode = 0;
        break;
      }
      FoundValidUcode = 1;
    }

    if (FitEntry[FitIndex].Type != FIT_TABLE_TYPE_MICROCODE) {
      continue;
    }
  }

  if (FoundValidUcode != 1) {
    DEBUG ((DEBUG_INFO, "Fail: Fit table does not contain valid ucode entry\n"));

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_6 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_6);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "  Table 7-4. SMM Security Configuration\n"));

  DEBUG ((DEBUG_INFO, "    1. SMRAMC\n"));

  SramC = MmioRead8 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH,SA_MC_DEV,SA_MC_FUN) + R_SA_SMRAMC);
  if ((SramC & B_SA_SMRAMC_D_LCK_MASK) == 0) {
    DEBUG ((DEBUG_INFO, "Fail: SMRAMC not locked\n"));

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_8 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_8);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    2. TSEGMB\n"));

  TsegMB = MmioRead32 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH,SA_MC_DEV,SA_MC_FUN) + R_SA_TSEGMB);
  if ((TsegMB & B_SA_TSEGMB_LOCK_MASK) == 0) {
    DEBUG ((DEBUG_INFO, "Fail: TSEGMB not locked\n"));

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_8 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_8);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    3. TSEGMB Alignment\n"));

  MemInfo = (MEMORY_PLATFORM_DATA_HOB*) GetFirstGuidHob (&gSiMemoryPlatformDataGuid);

  if (((TsegMB & B_SA_TSEGMB_TSEGMB_MASK) & (LShiftU64 (MemInfo->Data.TsegSize,20) - 1)) != 0) {
    DEBUG ((DEBUG_INFO, "Fail: TSEGMB not size aligned, TSEG size: 0x%x\n",(LShiftU64 (MemInfo->Data.TsegSize,20) - 1)));

    HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_9 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_9);
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  MasterSmrrBase = 0;
  MasterSmrrMask = 0;
  for (CpuIndex = 0; CpuIndex < CpuNumber; CpuIndex++) {
    DEBUG ((DEBUG_INFO, "  [CPU - 0x%x]\n", CpuIndex));

    DEBUG ((DEBUG_INFO, "    4. SMRR1 are supported\n"));

    MtrrCapMsr.Uint64 = ProcessorReadMsr64 (CpuIndex, MSR_IA32_MTRRCAP);
    if (MtrrCapMsr.Bits.SMRR == 0) {
      DEBUG ((DEBUG_INFO, "Fail: SMRR1 not supported\n"));

      HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_A ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_A);
      Status = HstiLibAppendErrorString (
                 PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                 NULL,
                 HstiErrorString
                 );
      ASSERT_EFI_ERROR (Status);
      Result = FALSE;
      FreePool (HstiErrorString);
    } else {
      DEBUG ((DEBUG_INFO, "    5. SMRR1 programmed consistently on all cores\n"));

      SmrrBase = ProcessorReadMsr64 (CpuIndex, MSR_IA32_SMRR_PHYSBASE);
      SmrrMask = ProcessorReadMsr64 (CpuIndex, MSR_IA32_SMRR_PHYSMASK);

      if (CpuIndex == 0) {
        MasterSmrrBase = SmrrBase;
        MasterSmrrMask = SmrrMask;
      } else {
        if ((SmrrBase != MasterSmrrBase) || (SmrrMask != MasterSmrrMask)) {
          DEBUG ((DEBUG_INFO, "Fail: SMRR1 not programmed consistently across all cores\n"));

          HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_A ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_A);
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

      DEBUG ((DEBUG_INFO, "    6. SMRR1 enabled/correct\n"));

      if (((SmrrMask & BIT11) == 0x0) ||
          ((SmrrMask & BIT9) != 0x0) ||
          ((SmrrBase & 0x7) != 0x6)) {
        DEBUG ((DEBUG_INFO, "Fail: SMRR1 not enabled/correct\n"));

        HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_A ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_A);
        Status = HstiLibAppendErrorString (
                   PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                   NULL,
                   HstiErrorString
                   );
        ASSERT_EFI_ERROR (Status);
        Result = FALSE;
        FreePool (HstiErrorString);
      }

      DEBUG ((DEBUG_INFO, "    7. SMRR1 and TSEGMB match\n"));

      DEBUG ((DEBUG_INFO, "SMRR:   0x%08x - 0x%08x\n", SmrrBase & (SmrrMask & 0xFFFFF000), (UINT32) (~(SmrrMask & 0xFFFFF000) + 1)));
      DEBUG ((DEBUG_INFO, "TSEGMB: 0x%08x\n", TsegMB & B_SA_TSEGMB_TSEGMB_MASK));

      if ((SmrrBase & (SmrrMask & 0xFFFFF000)) != (TsegMB & B_SA_TSEGMB_TSEGMB_MASK)) {
        DEBUG ((DEBUG_INFO, "Fail: SMRR1 != TSEGMB\n"));

        HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_A ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_A);
        Status = HstiLibAppendErrorString (
                   PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                   NULL,
                   HstiErrorString
                   );
        ASSERT_EFI_ERROR (Status);
        Result = FALSE;
        FreePool (HstiErrorString);
      }

      DEBUG ((DEBUG_INFO, "    8. SMRR1 size\n"));
      Bgsm = MmioRead32 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH,SA_MC_DEV,SA_MC_FUN) + R_SA_BGSM);

      if ((UINT32) (~(SmrrMask & 0xFFFFF000) + 1) !=
          ((Bgsm & B_SA_BGSM_BGSM_MASK) - (TsegMB & B_SA_TSEGMB_TSEGMB_MASK))) {
        DEBUG ((DEBUG_INFO, "Fail: SMRR1 size != BGSM-TSEGMB\n"));

        HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_A ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_A);
        Status = HstiLibAppendErrorString (
                   PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                   NULL,
                   HstiErrorString
                   );
        ASSERT_EFI_ERROR (Status);
        Result = FALSE;
        FreePool (HstiErrorString);
      }

      DEBUG ((DEBUG_INFO, "    9. SMRR1 work\n"));

      if (MmioRead32 (SmrrBase & SmrrMask) != 0xFFFFFFFF) {
        DEBUG ((DEBUG_INFO, "Fail: SMRR1 not working, read succeeded\n"));


        HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_A ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_A);
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
  }

  DEBUG ((DEBUG_INFO, "  Table 3-8. Protected Range Microcode Range Register (PRMRR) Security Configuration\n"));

  MasterPrmrrBase = 0;
  MasterPrmrrMask = 0;

  for (CpuIndex = 0; CpuIndex < CpuNumber; CpuIndex++) {
    DEBUG ((DEBUG_INFO, "  [CPU - 0x%x]\n", CpuIndex));

    DEBUG ((DEBUG_INFO, "    1. PRMRR supported\n"));

    if ((ProcessorReadMsr64 (CpuIndex, MSR_IA32_MTRRCAP) & B_IA32_MTRR_CAP_PRMRR_SUPPORT) == 0) {
      DEBUG ((DEBUG_INFO, "PRMRR not supported by CPU skipping PRMRR tests\n"));
    } else{

      DEBUG ((DEBUG_INFO, "    2. PRMRR programmed consistently on all cores\n"));

      PrmrrBase = ProcessorReadMsr64 (CpuIndex, MSR_PRMRR_PHYS_BASE);
      PrmrrMask = ProcessorReadMsr64 (CpuIndex, MSR_PRMRR_PHYS_MASK);
      PrmrrEnabled = FALSE;

      if ((PrmrrMask & BIT11) != 0) {
        PrmrrEnabled = TRUE;
      }

      if (PrmrrEnabled) {

        PrmrrsConsistent = TRUE;
        if (CpuIndex == 0) {
          MasterPrmrrBase = PrmrrBase;
          MasterPrmrrMask = PrmrrMask;
        } else {
          if ((PrmrrBase != MasterPrmrrBase) || (PrmrrMask != MasterPrmrrMask)) {
            PrmrrsConsistent = FALSE;
            DEBUG ((DEBUG_INFO, "Fail: PRMRR's not programmed consistently\n"));

            HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_7 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_7);
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

        DEBUG ((DEBUG_INFO, "    3. PRMRR correctly programmed\n"));
        if (PrmrrsConsistent) {
          if (((PrmrrMask & BIT9) != 0x0) ||
              ((PrmrrMask & B_MSR_PRMRR_PHYS_MASK_LOCK) == 0x0) ||
              ((PrmrrBase & 0x7) != 0x6)) {
            DEBUG ((DEBUG_INFO, "Fail: PRMRR's not programmed correctly\n"));

            HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_7 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_7);
            Status = HstiLibAppendErrorString (
                       PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                       NULL,
                       HstiErrorString
                       );
            ASSERT_EFI_ERROR (Status);
            Result = FALSE;
            FreePool (HstiErrorString);
          }

          DEBUG ((DEBUG_INFO, "    4. Core PRMRR and Uncore PRMRR match\n"));

          UncorePrmrrBase = ProcessorReadMsr64 (CpuIndex, MSR_UNCORE_PRMRR_PHYS_BASE);
          UncorePrmrrMask = ProcessorReadMsr64 (CpuIndex, MSR_UNCORE_PRMRR_PHYS_MASK);

          if (((UncorePrmrrBase & ~0xFFF) != (PrmrrBase & ~0xFFF)) ||
              ((UncorePrmrrMask & ~0xFFF) != (PrmrrMask & ~0xFFF))) {
            DEBUG ((DEBUG_INFO, "Fail: Core and Uncore PRMRR's not matching\n"));

            HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_7 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_7);
            Status = HstiLibAppendErrorString (
                       PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                       NULL,
                       HstiErrorString
                       );
            ASSERT_EFI_ERROR (Status);
            Result = FALSE;
            FreePool (HstiErrorString);
          }

          DEBUG ((DEBUG_INFO, "    5. PRMRR working \n"));

          if (MmioRead32 (PrmrrBase & PrmrrMask) != 0xFFFFFFFF) {
            DEBUG ((DEBUG_INFO, "Fail: PRMRR's not working, able to read from range\n"));

            HstiErrorString = BuildHstiErrorString (HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_CODE_7 ,HSTI_CPU_SECURITY_CONFIGURATION, HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_7);
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
      }
    }
  }

  //
  // ALL PASS
  //
  if (Result) {
    Status = HstiLibSetFeaturesVerified (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               0,
               HSTI_BYTE0_SECURE_CPU_CONFIGURATION
               );
    ASSERT_EFI_ERROR (Status);
  }

  return;
}
