/** @file
  CPU Platform Lib implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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
#include "CpuPlatformLibrary.h"
#include <Library/MmPciLib.h>
#include <SaRegs.h>

#define SKIP_MICROCODE_CHECKSUM_CHECK 1

#define KBLG_PLATFORM_ID              0x3  // KblGContent
#define KBLG_KSKU_ID                  0x7  // KblGContent

/**
  Return CPU Family ID

  @retval CPU_FAMILY              CPU Family ID
**/
CPU_FAMILY
EFIAPI
GetCpuFamily (
  VOID
  )
{
  EFI_CPUID_REGISTER Cpuid;
  ///
  /// Read the CPUID information
  ///
  AsmCpuid (CPUID_VERSION_INFO, &Cpuid.RegEax, &Cpuid.RegEbx, &Cpuid.RegEcx, &Cpuid.RegEdx);
  return ((CPU_FAMILY) (Cpuid.RegEax & CPUID_FULL_FAMILY_MODEL));
}

/**
  Return Cpu stepping type

  @retval UINT8                   Cpu stepping type
**/
CPU_STEPPING
EFIAPI
GetCpuStepping (
  VOID
  )
{
  EFI_CPUID_REGISTER Cpuid;
  ///
  /// Read the CPUID information
  ///
  AsmCpuid (CPUID_VERSION_INFO, &Cpuid.RegEax, &Cpuid.RegEbx, &Cpuid.RegEcx, &Cpuid.RegEdx);
  return ((CPU_STEPPING) (Cpuid.RegEax & CPUID_FULL_STEPPING));
}

/**
  Return CPU Sku

  @retval UINT8              CPU Sku
**/
UINT8
EFIAPI
GetCpuSku (
  VOID
  )
{
  UINT8              CpuType;
  UINT16             CpuDid;
  UINT32             CpuFamilyModel;
  EFI_CPUID_REGISTER Cpuid;
  BOOLEAN            SkuFound;

  SkuFound  = TRUE;
  CpuType   = EnumCpuUnknown;

  ///
  /// Read the CPUID & DID information
  ///
  AsmCpuid (CPUID_VERSION_INFO, &Cpuid.RegEax, &Cpuid.RegEbx, &Cpuid.RegEcx, &Cpuid.RegEdx);
  CpuFamilyModel = Cpuid.RegEax & CPUID_FULL_FAMILY_MODEL;
  CpuDid = MmioRead16 (MmPciBase (0, 0, 0) + 2);

  switch (CpuFamilyModel) {
    case CPUID_FULL_FAMILY_MODEL_SKYLAKE_ULT_ULX:
      switch (CpuDid) {
        case V_SA_DEVICE_ID_SKL_MB_ULT_1:    // ULT OPI
        case V_SA_DEVICE_ID_KBL_MB_ULT_1:    // KBL ULT OPI
          CpuType = EnumCpuUlt;
          break;

        case V_SA_DEVICE_ID_SKL_MB_ULX_2:    // ULX OPI
        case V_SA_DEVICE_ID_SKL_MB_ULX_3:    // ULX OPI
        case V_SA_DEVICE_ID_KBL_MB_ULX_1:    // ULX OPI
        case V_SA_DEVICE_ID_AML_MB_ULX_1:    // ULX OPI
          CpuType = EnumCpuUlx;
          break;

        default:
          SkuFound = FALSE;
          break;
      }
      break;

    case CPUID_FULL_FAMILY_MODEL_SKYLAKE_DT_HALO:
      switch (CpuDid) {

        case V_SA_DEVICE_ID_SKL_DT_1:      // DT
        case V_SA_DEVICE_ID_SKL_DT_2:      // DT
        case V_SA_DEVICE_ID_KBL_DT_1:      // DT
        case V_SA_DEVICE_ID_KBL_DT_2:      // DT
        case V_SA_DEVICE_ID_CFL_DT_1:      // DT
        case V_SA_DEVICE_ID_CFL_DT_2:      // DT
        case V_SA_DEVICE_ID_CFL_DT_3:      // DT
        case V_SA_DEVICE_ID_CFL_DT_4:      // DT
        case V_SA_DEVICE_ID_CFL_SVR_1:     // Server
        case V_SA_DEVICE_ID_CFL_SVR_2:     // Server
          CpuType = EnumCpuTrad;
          break;

        case V_SA_DEVICE_ID_SKL_HALO_1:    // Halo
        case V_SA_DEVICE_ID_SKL_HALO_2:    // Halo
        case V_SA_DEVICE_ID_KBL_HALO_1:    // Halo
        case V_SA_DEVICE_ID_KBL_HALO_2:    // Halo
        case V_SA_DEVICE_ID_SKL_SVR_1:     // Server
        case V_SA_DEVICE_ID_SKL_SVR_2:     // Server
        case V_SA_DEVICE_ID_KBL_SVR_1:     // Server
        case V_SA_DEVICE_ID_KBL_SVR_2:     // Server
          CpuType = EnumCpuHalo;
          break;

        default:
          SkuFound = FALSE;
          break;
      }
      break;
    case CPUID_FULL_FAMILY_MODEL_KABYLAKE_ULT_ULX:
      switch (CpuDid) {
        case V_SA_DEVICE_ID_KBL_MB_ULT_1:    // KBL ULT OPI
        case V_SA_DEVICE_ID_KBLR_MB_ULT_1:   // KBL-R ULT
          CpuType = EnumCpuUlt;
          break;

        case V_SA_DEVICE_ID_KBL_MB_ULX_1:    // ULX OPI
        case V_SA_DEVICE_ID_AML_MB_ULX_1:    // ULX OPI
          CpuType = EnumCpuUlx;
          break;

        default:
          SkuFound = FALSE;
          break;
      }
      break;

    case CPUID_FULL_FAMILY_MODEL_KABYLAKE_DT_HALO:
      switch (CpuDid) {

        case V_SA_DEVICE_ID_KBL_DT_1:      // DT
        case V_SA_DEVICE_ID_KBL_DT_2:      // DT
        case V_SA_DEVICE_ID_CFL_DT_1:      // DT
        case V_SA_DEVICE_ID_CFL_DT_2:      // DT
        case V_SA_DEVICE_ID_CFL_DT_3:      // DT
        case V_SA_DEVICE_ID_CFL_DT_4:      // DT
        case V_SA_DEVICE_ID_CFL_SVR_1:     // Server
        case V_SA_DEVICE_ID_CFL_SVR_2:     // Server
          CpuType = EnumCpuTrad;
          break;

        case V_SA_DEVICE_ID_KBL_HALO_1:    // Halo
        case V_SA_DEVICE_ID_KBL_HALO_2:    // Halo
        case V_SA_DEVICE_ID_KBL_SVR_1:     // Server
        case V_SA_DEVICE_ID_KBL_SVR_2:     // Server
          CpuType = EnumCpuHalo;
          break;

        default:
          SkuFound = FALSE;
          break;
      }
      break;

    default:
      SkuFound = FALSE;
      break;
  }

  if (!SkuFound) {
    DEBUG ((DEBUG_ERROR, "Unsupported CPU SKU, Device ID: 0x%02X, CPUID: 0x%08X!\n", CpuDid, CpuFamilyModel));
    ASSERT (FALSE);
  }

  return CpuType;
}

//
// KblGBegin
//

/**
  Detect KBLG Package

  @retval TRUE           G Pkg was detected
  @retval FALSE          G Pkg was not detected
**/
BOOLEAN
EFIAPI
IsKblGPackage (
  VOID
  )
{
  UINT8                               CpuSku;
  CPU_GENERATION                      CpuGeneration;
  MSR_IA32_PLATFORM_ID_REGISTER       Msr;

  CpuSku = GetCpuSku ();
  CpuGeneration = GetCpuGeneration ();

  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_PLATFORM_ID);

  if ((CpuSku == EnumCpuHalo) && (CpuGeneration == EnumKblCpu)) {
    if ((UINT8) Msr.Bits.PlatformId == KBLG_PLATFORM_ID) {
      return TRUE;
    }
  }
  return FALSE;
}

#ifndef MINTREE_FLAG
/**
Detect if the KBL G part is a K-SKU

@retval TRUE           XT K-SKU was detected
@retval FALSE          XT K-SKU was not detected
**/
BOOLEAN
EFIAPI
IsKblGKSku(
  VOID
  )
{
  UINT64                KSkuCheck;

  KSkuCheck = AsmReadMsr64 (MSR_FLEX_RATIO);

  if (IsKblGPackage ()) {
    if (RShiftU64 ((KSkuCheck & B_OVERCLOCKING_BINS), N_OVERCLOCKING_BINS) == KBLG_KSKU_ID) {
      return TRUE;
    }
  }
  return FALSE;
}
#endif  // MINTREE_FLAG
//
// KblGEnd
//

/**
  Detect CFL-S CPU

  @retval TRUE           CPU was detected
  @retval FALSE          CPU was not detected
**/
BOOLEAN
EFIAPI
IsCflSCpu (
  VOID
  )
{
  UINT16             CpuDid;

  ///
  /// Read the DID information
  ///
  CpuDid = MmioRead16 (MmPciBase (0, 0, 0) + 2);

  if (CpuDid == V_SA_DEVICE_ID_CFL_DT_1  ||
      CpuDid == V_SA_DEVICE_ID_CFL_DT_2  ||
      CpuDid == V_SA_DEVICE_ID_CFL_DT_3  ||
      CpuDid == V_SA_DEVICE_ID_CFL_DT_4  ||
      CpuDid == V_SA_DEVICE_ID_CFL_SVR_1 ||
      CpuDid == V_SA_DEVICE_ID_CFL_SVR_2 ||
      CpuDid == V_SA_DEVICE_ID_CFL_SVR_3
  ) {
    return TRUE;
  }

  return FALSE;
}

/**
  Return CPU Identifier used to identify various CPU types

  @retval CPU_OVERRIDE_IDENTIFIER           CPU Identifier
**/
CPU_OVERRIDE_IDENTIFIER
EFIAPI
GetCpuIdentifier (
  VOID
  )
{
  CPU_OVERRIDE_IDENTIFIER CpuIdentifier;
#ifndef MINTREE_FLAG
  CPU_SKU CpuSku;
  CPU_FAMILY  CpuFamily;
  BOOLEAN HasEdram;
  UINT16 PackageTdp;
  UINT16 PackageTdpWatt;
  UINT16 TempPackageTdp;
  MSR_REGISTER TempMsr;
  MSR_REGISTER PackagePowerSkuUnitMsr;
  UINT8 ProcessorPowerUnit;
  UINT16  CpuDid;
  UINT16  GtDid;

  CpuDid = MmioRead16 (MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN) + R_SA_MC_DEVICE_ID);
  GtDid  = MmioRead16 (MmPciBase (SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0) + 0x2);

  ///
  /// Initialize local variables
  ///
  CpuSku    = GetCpuSku();
  CpuFamily = GetCpuFamily();

  HasEdram = ((AsmReadMsr64 (MSR_PLATFORM_INFO) & B_PLATFORM_INFO_EDRAM_EN) != 0);
  CpuIdentifier = EnumUnknownCpuId;

  ///
  /// Find Package TDP value in 1/100 Watt units
  ///
  TempMsr.Qword                 = AsmReadMsr64 (MSR_PACKAGE_POWER_SKU);
  PackagePowerSkuUnitMsr.Qword  = AsmReadMsr64 (MSR_PACKAGE_POWER_SKU_UNIT);
  ProcessorPowerUnit           = (PackagePowerSkuUnitMsr.Bytes.FirstByte & PACKAGE_POWER_UNIT_MASK);
  if (ProcessorPowerUnit == 0) {
    ProcessorPowerUnit = 1;
  } else {
    ProcessorPowerUnit = (UINT8) LShiftU64 (2, (ProcessorPowerUnit - 1));
  }
  TempPackageTdp = (UINT16) (TempMsr.Dwords.Low & PACKAGE_TDP_POWER_MASK);
  PackageTdpWatt = (UINT16) DivU64x32 (TempPackageTdp, ProcessorPowerUnit);


  PackageTdp = (PackageTdpWatt * 100);
  if ((TempPackageTdp % ProcessorPowerUnit) !=0) {
    PackageTdp += ((TempPackageTdp % ProcessorPowerUnit) * 100) / ProcessorPowerUnit;
  }

  ///
  /// Dump the CPU information
  ///
  DEBUG ((DEBUG_INFO, "GetCpuIdentifier: CpuFamily  - 0x%X\n", CpuFamily));
  DEBUG ((DEBUG_INFO, "                  CpuSku     - 0x%X\n", CpuSku));
  DEBUG ((DEBUG_INFO, "                  SaDid      - 0x%X\n", CpuDid));
  DEBUG ((DEBUG_INFO, "                  GtDid      - 0x%X\n", GtDid));
  DEBUG ((DEBUG_INFO, "                  PackageTdp - %d\n", PackageTdp));

  ///
  /// Logic to determine the CPU Identifier
  ///
  switch(CpuSku) {

    case EnumCpuTrad:
      ///
      /// CFL-S/KBL-S
      ///
      if (CpuFamily == CPUID_FULL_FAMILY_MODEL_KABYLAKE_DT_HALO) {
        switch (PackageTdp) {
          case CPU_TDP_35_WATTS:
            ///
            ///  35 Watts
            ///
            if (CpuDid == V_SA_DEVICE_ID_CFL_DT_3) {
              ///
              /// CFL-S 2+2
              ///
              CpuIdentifier = EnumCflS35Watt22CpuId;
            } else if (CpuDid == V_SA_DEVICE_ID_KBL_DT_1) {
              ///
              /// KBL-S 2+2
              ///
              CpuIdentifier = EnumKblS35Watt22Cpuid;
            } else if (CpuDid == V_SA_DEVICE_ID_CFL_DT_2 ||
                       CpuDid == V_SA_DEVICE_ID_CFL_WS_2 ||
                       CpuDid == V_SA_DEVICE_ID_CFL_SVR_3) {
              ///
              /// CFL-S 4+2
              ///
              CpuIdentifier = EnumCflS35Watt42CpuId;
            } else if (CpuDid == V_SA_DEVICE_ID_KBL_DT_2) {
              ///
              /// KBL-S 4+2
              ///
              CpuIdentifier = EnumKblS35Watt42Cpuid;
            } else if (CpuDid == V_SA_DEVICE_ID_CFL_DT_1 ||
                       CpuDid == V_SA_DEVICE_ID_CFL_WS_1 ||
                       CpuDid == V_SA_DEVICE_ID_CFL_SVR_1) {
              ///
              /// CFL-S 6+2
              ///
              CpuIdentifier = EnumCflS35Watt62CpuId;
            } else if (CpuDid == V_SA_DEVICE_ID_CFL_DT_4 ||
                      CpuDid == V_SA_DEVICE_ID_CFL_WS_3  ||
                      CpuDid == V_SA_DEVICE_ID_CFL_SVR_2) {
              ///
              /// CFL-S 8+2
              ///
              CpuIdentifier = EnumCflS35Watt82CpuId;
            } else {
              CpuIdentifier = EnumUnknownCpuId;
            }
          break;

          case CPU_TDP_51_WATTS:
            ///
            ///  51 Watts
            ///
            if (CpuDid == V_SA_DEVICE_ID_KBL_DT_1) {
              ///
              /// KBL-S 2+2
              ///
              CpuIdentifier = EnumKblS51Watt22Cpuid;
            } else {
              CpuIdentifier = EnumUnknownCpuId;
            }
          break;

          case CPU_TDP_54_WATTS:
            ///
            ///  54 Watts
            ///
            if (CpuDid == V_SA_DEVICE_ID_CFL_DT_3) {
              ///
              /// CFL-S 2+2
              ///
              CpuIdentifier = EnumCflS54Watt22CpuId;
            } else if (CpuDid == V_SA_DEVICE_ID_KBL_DT_1) {
              ///
              /// KBL-S 2+2
              ///
              CpuIdentifier = EnumKblS54Watt22Cpuid;
            } else {
              CpuIdentifier = EnumUnknownCpuId;
            }
          break;

          case CPU_TDP_58_WATTS:
            ///
            ///  58 Watts
            ///
            if (CpuDid == V_SA_DEVICE_ID_CFL_DT_3) {
              ///
              /// CFL-S 2+2
              ///
              CpuIdentifier = EnumCflS58Watt22CpuId;
            } else {
              CpuIdentifier = EnumUnknownCpuId;
            }
          break;

          case CPU_TDP_60_WATTS:
            ///
            ///  60 Watts
            ///
            if (CpuDid == V_SA_DEVICE_ID_KBL_DT_1) {
              ///
              /// KBL-S 2+2
              ///
              CpuIdentifier = EnumKblS60Watt22Cpuid;
            } else {
              CpuIdentifier = EnumUnknownCpuId;
            }
          break;

          case CPU_TDP_62_WATTS:
            ///
            ///  65 Watts
            ///
            if (CpuDid == V_SA_DEVICE_ID_CFL_DT_2 ||
                CpuDid == V_SA_DEVICE_ID_CFL_WS_2 ||
                CpuDid == V_SA_DEVICE_ID_CFL_SVR_3) {
              ///
              /// CFL-S 4+2
              ///
              CpuIdentifier = EnumCflS62Watt42CpuId;
            } else {
              CpuIdentifier = EnumUnknownCpuId;
            }
            break;

          case CPU_TDP_65_WATTS:
            ///
            ///  65 Watts
            ///
            if (CpuDid == V_SA_DEVICE_ID_CFL_DT_2 ||
                CpuDid == V_SA_DEVICE_ID_CFL_WS_2 ||
                CpuDid == V_SA_DEVICE_ID_CFL_SVR_3) {
              ///
              /// CFL-S 4+2
              ///
              CpuIdentifier = EnumCflS65Watt42CpuId;
            } else if (CpuDid == V_SA_DEVICE_ID_KBL_DT_2) {
              ///
              /// KBL-S 4+2
              ///
              CpuIdentifier = EnumKblS65Watt42Cpuid;
            } else if (CpuDid == V_SA_DEVICE_ID_CFL_DT_1 ||
                       CpuDid == V_SA_DEVICE_ID_CFL_WS_1 ||
                       CpuDid == V_SA_DEVICE_ID_CFL_SVR_1) {
              ///
              /// CFL-S 6+2
              ///
              CpuIdentifier = EnumCflS65Watt62CpuId;
            } else if (CpuDid == V_SA_DEVICE_ID_CFL_DT_4 ||
                       CpuDid == V_SA_DEVICE_ID_CFL_WS_3  ||
                       CpuDid == V_SA_DEVICE_ID_CFL_SVR_2) {
              ///
              /// CFL-S 8+2
              ///
              CpuIdentifier = EnumCflS65Watt82CpuId;
            } else {
              CpuIdentifier = EnumUnknownCpuId;
            }
          break;

          case CPU_TDP_91_WATTS:
          case CPU_TDP_95_WATTS:
            ///
            ///  95 Watts
            ///
            if (CpuDid == V_SA_DEVICE_ID_CFL_DT_2 ||
                CpuDid == V_SA_DEVICE_ID_CFL_WS_2 ||
                CpuDid == V_SA_DEVICE_ID_CFL_SVR_3) {
              ///
              /// 4+2 TDP reports as 91W
              ///
              CpuIdentifier = EnumCflS95Watt42CpuId;
            } else if (CpuDid == V_SA_DEVICE_ID_KBL_DT_2) {
              ///
              /// KBL-S 4+2
              ///
              CpuIdentifier = EnumKblS95Watt42Cpuid;
            } else if (CpuDid == V_SA_DEVICE_ID_CFL_DT_1 ||
                       CpuDid == V_SA_DEVICE_ID_CFL_WS_1 ||
                       CpuDid == V_SA_DEVICE_ID_CFL_SVR_1) {
              ///
              /// CFL-S 6+2, 95W
              ///
              CpuIdentifier = EnumCflS95Watt62CpuId;
            } else if (CpuDid == V_SA_DEVICE_ID_CFL_DT_4 ||
                       CpuDid == V_SA_DEVICE_ID_CFL_WS_3 ||
                       CpuDid == V_SA_DEVICE_ID_CFL_SVR_2) {
              ///
              /// CFL-S 8+2, 95W
              ///
              CpuIdentifier = EnumCflS95Watt82CpuId;
            } else {
              CpuIdentifier = EnumUnknownCpuId;
            }
          break;

          case CPU_TDP_99_WATTS:
            ///
            /// 99 Watts
            ///
            CpuIdentifier = KBL_S_99_WATT_4_2;
          break;
          }
        }
      break;

    case EnumCpuHalo:
      if (CpuFamily == CPUID_FULL_FAMILY_MODEL_SKYLAKE_DT_HALO) {
        CpuIdentifier = EnumSklH45Watt42Cpuid;
      }
      break;

    case EnumCpuUlx:
      ///
      /// KBL/AML Y 2+2
      ///
      if (CpuDid == V_SA_DEVICE_ID_KBL_MB_ULX_1 || CpuDid == V_SA_DEVICE_ID_KBL_MB_ULT_1 ) {
        if (PackageTdp == CPU_TDP_5_WATTS) {
          ///
          ///  AML-Y 2+2 5W
          ///
          CpuIdentifier = EnumAmlY5Watt22CpuId;
        } else if (PackageTdp == CPU_TDP_7_WATTS) {
          if (GtDid == V_SA_PCI_DEV_2_GT2_ULX_R_ID) {
            ///
            ///  AML-Y 2+2 7W
            ///
            CpuIdentifier = EnumAmlY7Watt22CpuId;
          } else if (GtDid == V_SA_PCI_DEV_2_GT2_AML_1_ID) {
            ///
            ///  AML-Y 2f+2 7W
            ///
            CpuIdentifier = EnumAmlY7Watt2f2CpuId;
          }
        } else {
          ///
          ///  KBL-Y 2+2 4.5W
          ///
          CpuIdentifier = EnumKblY4pt5Watt22CpuId;
       }
      } else if (CpuDid == V_SA_DEVICE_ID_AML_MB_ULX_1) {
        ///
        ///  AML-Y 4+2 7W
        ///
        CpuIdentifier = EnumAmlY7Watt42CpuId;
      }
    break;

    default:
      CpuIdentifier = EnumUnknownCpuId;
      break;
    }
#else
  CpuIdentifier = EnumUnknownCpuId;
#endif
  DEBUG ((DEBUG_INFO, "                  CpuIdentifier - %d\n", CpuIdentifier));
  return CpuIdentifier;
}

/**
  Returns the processor microcode revision of the processor installed in the system.

  @retval Processor Microcode Revision
**/
UINT32
GetCpuUcodeRevision (
  VOID
  )
{
  AsmWriteMsr64 (MSR_IA32_BIOS_SIGN_ID, 0);
  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, NULL, NULL);
  return (UINT32) RShiftU64 (AsmReadMsr64 (MSR_IA32_BIOS_SIGN_ID), 32);
}

/**
  Verify the DWORD type checksum

  @param[in] ChecksumAddr  - The start address to be checkumed
  @param[in] ChecksumLen   - The length of data to be checksumed

  @retval EFI_SUCCESS           - Checksum correct
  @retval EFI_CRC_ERROR         - Checksum incorrect
**/
EFI_STATUS
Checksum32Verify (
  IN UINT32 *ChecksumAddr,
  IN UINT32 ChecksumLen
  )
{
#if SKIP_MICROCODE_CHECKSUM_CHECK
  return EFI_SUCCESS;
#else
  UINT32 Checksum;
  UINT32 Index;

  Checksum = 0;

  for (Index = 0; Index < ChecksumLen; Index++) {
    Checksum += ChecksumAddr[Index];
  }

  return (Checksum == 0) ? EFI_SUCCESS : EFI_CRC_ERROR;
#endif
}

/**
  This function checks the MCU revision to decide if BIOS needs to load
  microcode.

  @param[in] MicrocodePointer - Microcode in memory
  @param[in] Revision         - Current CPU microcode revision

  @retval EFI_SUCCESS - BIOS needs to load microcode
  @retval EFI_ABORTED - Don't need to update microcode
**/
EFI_STATUS
CheckMcuRevision (
  IN CPU_MICROCODE_HEADER *MicrocodePointer,
  IN UINT32               Revision
  )
{
  EFI_STATUS Status;
  Status = EFI_ABORTED;

  if ((MicrocodePointer->UpdateRevision & 0x80000000) ||
      (MicrocodePointer->UpdateRevision > Revision) ||
      (Revision == 0)) {
    Status = EFI_SUCCESS;
  }

  return Status;
}

/**
  Check if this microcode is correct one for processor

  @param[in] Cpuid               - processor CPUID
  @param[in] MicrocodeEntryPoint - entry point of microcode
  @param[in] Revision            - revision of microcode

  @retval CorrectMicrocode if this microcode is correct
**/
BOOLEAN
CheckMicrocode (
  IN UINT32               Cpuid,
  IN CPU_MICROCODE_HEADER *MicrocodeEntryPoint,
  IN UINT32               *Revision
  )
{
  EFI_STATUS                          Status;
  UINT8                               ExtendedIndex;
  MSR_IA32_PLATFORM_ID_REGISTER       Msr;
  UINT32                              ExtendedTableLength;
  UINT32                              ExtendedTableCount;
  BOOLEAN                             CorrectMicrocode;
  CPU_MICROCODE_EXTENDED_TABLE        *ExtendedTable;
  CPU_MICROCODE_EXTENDED_TABLE_HEADER *ExtendedTableHeader;

  Status              = EFI_NOT_FOUND;
  ExtendedTableLength = 0;
  CorrectMicrocode    = FALSE;

  if (MicrocodeEntryPoint == NULL) {
    return FALSE;
  }

  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_PLATFORM_ID);

  ///
  /// Check if the microcode is for the Cpu and the version is newer
  /// and the update can be processed on the platform
  ///
  if ((MicrocodeEntryPoint->HeaderVersion == 0x00000001) &&
      !EFI_ERROR (CheckMcuRevision (MicrocodeEntryPoint, *Revision))
      ) {
    if ((MicrocodeEntryPoint->ProcessorId == Cpuid) && (MicrocodeEntryPoint->ProcessorFlags & (1 << (UINT8) Msr.Bits.PlatformId))) {
      if (MicrocodeEntryPoint->DataSize == 0) {
        Status = Checksum32Verify ((UINT32 *) MicrocodeEntryPoint, 2048 / sizeof (UINT32));
      } else {
        Status = Checksum32Verify (
                   (UINT32 *) MicrocodeEntryPoint,
                   (MicrocodeEntryPoint->DataSize + sizeof (CPU_MICROCODE_HEADER)) / sizeof (UINT32)
                   );
      }

      if (!EFI_ERROR (Status)) {
        CorrectMicrocode = TRUE;
      }
    } else if ((MicrocodeEntryPoint->DataSize != 0)) {
      ///
      /// Check the  Extended Signature if the entended signature exist
      /// Only the data size != 0 the extended signature may exist
      ///
      ExtendedTableLength = MicrocodeEntryPoint->TotalSize - (MicrocodeEntryPoint->DataSize + sizeof (CPU_MICROCODE_HEADER));
      if (ExtendedTableLength != 0) {
        ///
        /// Extended Table exist, check if the CPU in support list
        ///
        ExtendedTableHeader = (CPU_MICROCODE_EXTENDED_TABLE_HEADER *) ((UINT8 *) (MicrocodeEntryPoint) + MicrocodeEntryPoint->DataSize + 48);
        ///
        /// Calulate Extended Checksum
        ///
        if ((ExtendedTableLength % 4) == 0) {
          Status = Checksum32Verify ((UINT32 *) ExtendedTableHeader, ExtendedTableLength / sizeof (UINT32));
          if (!EFI_ERROR (Status)) {
            ///
            /// Checksum correct
            ///
            ExtendedTableCount  = ExtendedTableHeader->ExtendedSignatureCount;
            ExtendedTable       = (CPU_MICROCODE_EXTENDED_TABLE *) (ExtendedTableHeader + 1);
            for (ExtendedIndex = 0; ExtendedIndex < ExtendedTableCount; ExtendedIndex++) {
              ///
              /// Verify Header
              ///
              if ((ExtendedTable->ProcessorSignature == Cpuid) && (ExtendedTable->ProcessorFlag & (1 << (UINT8) Msr.Bits.PlatformId))) {
                Status = Checksum32Verify (
                           (UINT32 *) ExtendedTable,
                           sizeof (CPU_MICROCODE_EXTENDED_TABLE) / sizeof (UINT32)
                           );
                if (!EFI_ERROR (Status)) {
                  ///
                  /// Find one
                  ///
                  CorrectMicrocode = TRUE;
                  break;
                }
              }

              ExtendedTable++;
            }
          }
        }
      }
    }
  }

  return CorrectMicrocode;
}

#ifndef MINTREE_FLAG
/**
  This function is to program Trace Hub ACPI base address to processor's MSR TRACE_HUB_STH_ACPIBAR_BASE.

  @param[in]  TraceHubAcpiBase - Base address of Trace Hub ACPI Base address
**/
VOID
EFIAPI
CpuWriteTraceHubAcpiBase (
  IN UINT64  TraceHubAcpiBase
  )
{
  //
  // Check the pass in Trace Hub ACPI base if 256KB alignment.
  //
  if ((TraceHubAcpiBase & (UINT64) V_MSR_TRACE_HUB_STH_ACPIBAR_BASE_MASK) != 0) {
    ASSERT ((TraceHubAcpiBase & (UINT64) V_MSR_TRACE_HUB_STH_ACPIBAR_BASE_MASK) == 0);
    return;
  }

  ///
  /// Set MSR TRACE_HUB_STH_ACPIBAR_BASE[0] LOCK bit for the AET packets to be directed to NPK MMIO.
  ///
  AsmWriteMsr64 (MSR_TRACE_HUB_STH_ACPIBAR_BASE, TraceHubAcpiBase | B_MSR_TRACE_HUB_STH_ACPIBAR_BASE_LOCK);

  return;
}
#endif

/**
  Check on the processor if SGX is supported.

  @dot
    digraph G {
      subgraph cluster_c0 {
        node [shape = box];
          b1[label="Read CPUID(EAX=7,ECX=0):EBX[2] \nto check SGX feature" fontsize=12 style=filled color=lightblue];
          b2[label="Return TRUE" fontsize=12 style=filled color=lightblue];
          b3[label="Return FALSE" fontsize=12 style=filled color=lightblue];

        node [shape = ellipse];
          e1[label="Start" fontsize=12 style=filled color=lightblue];
          e2[label="End" fontsize=12 style=filled color=lightblue];

        node [shape = diamond,style=filled,color=lightblue];
          d1[label="Are SGX feature supported and \nPRMRR configuration enabled" fontsize=12];

        label = "IsSgxSupported Flow"; fontsize=15; fontcolor=black; color=lightblue;
        e1 -> b1
        b1 -> d1
        d1 -> b2 [label="Yes" fontsize=9]
        d1 -> b3 [label="No" fontsize=9]
        b2 -> e2
        b3 -> e2

      }
    }
  @enddot

  @retval TRUE  if SGX supported
  @retval FALSE if SGX is not supported
**/
BOOLEAN
IsSgxSupported (
  VOID
  )
{
  EFI_CPUID_REGISTER CpuidRegs;

  //
  // Processor support SGX feature by reading CPUID.(EAX=7,ECX=0):EBX[2]
  //
  AsmCpuidEx (CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS, 0, &CpuidRegs.RegEax,&CpuidRegs.RegEbx,&CpuidRegs.RegEcx,&CpuidRegs.RegEdx);

  ///
  /// SGX feature is supported only on SKL and later,
  /// with CPUID.(EAX=7,ECX=0):EBX[2]=1
  /// PRMRR configuration enabled, MSR IA32_MTRRCAP (FEh) [12] == 1
  ///
  if (((CpuidRegs.RegEbx & BIT2)) && (AsmReadMsr64 (MSR_IA32_MTRRCAP) & BIT12)) {
    return TRUE;
  }
  return FALSE;
}

/**
  Get processor generation

  @retval EnumSklCpu    Executing thread is Skylake
  @retval EnumKblCpu    Executing thread is Kabylake
**/
CPU_GENERATION
GetCpuGeneration (
  VOID
  )
{
  EFI_CPUID_REGISTER Cpuid;
  CPU_FAMILY         CpuFamilyModel;
  CPU_STEPPING       CpuStepping;
  CPU_GENERATION     CpuGeneration;

  CpuGeneration = EnumSklCpu;
  ///
  /// Read the CPUID information
  ///
  AsmCpuid (CPUID_VERSION_INFO, &Cpuid.RegEax, &Cpuid.RegEbx, &Cpuid.RegEcx, &Cpuid.RegEdx);
  CpuFamilyModel = (CPU_FAMILY) (Cpuid.RegEax & CPUID_FULL_FAMILY_MODEL);
  CpuStepping    = (CPU_STEPPING) (Cpuid.RegEax & CPUID_FULL_STEPPING);

  switch (CpuFamilyModel) {
    case EnumCpuKblUltUlx:
    case EnumCpuKblDtHalo:
      CpuGeneration = EnumKblCpu;
      break;

    case EnumCpuSklUltUlx:
    case EnumCpuSklDtHalo:
      if (((CpuStepping > EnumSklMaxUltUlxStep) && (CpuStepping <= EnumKblMaxUltUlxStep)) ||
          ((CpuStepping > EnumSklMaxDtHaloStep) && (CpuStepping <= EnumKblMaxDtHaloStep))) {
        CpuGeneration = EnumKblCpu;
      }
      break;

    default:
      CpuGeneration = EnumSklCpu;
      break;
  }

  return CpuGeneration;
}
