/** @file
  This file contains the tests for the SecureMemoryMapConfiguration bit

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

typedef struct {
  UINT64   Base;
  UINT64   End;
} MEMORY_RANGE;

typedef enum {
  LockableMemoryRangeLtSpace,
  LockableMemoryRangeHighBios,
  LockableMemoryRangeLowDram,
  LockableMemoryRangeHighDram,
  LockableMemoryRangeMchBar,
  LockableMemoryRangeDmiBar,
  LockableMemoryRangePxpEpBar,
  LockableMemoryRangeGfxVtBar,
  LockableMemoryRangeVtdPvc0Bar,
  LockableMemoryRangeGdxcBar,
  LockableMemoryRangeEdramBar,
  LockableMemoryRangeCpuRsvd1Bar,
  LockableMemoryRangeCpuRsvd2Bar,
  LockableMemoryRangeMax,
} LOCKABLE_MEMORY_RAMGE;

MEMORY_RANGE  mLockableMemoryRange[LockableMemoryRangeMax] = {
  // 1. LT space (0xFED20000 - 0xFED7FFFF)
  {0xFED20000, 0xFED7FFFF},
  // 2. High BIOS
  {0x0, SIZE_4GB - 1},
  // 3. Low DRAM (0 - TOLUD)
  {0x0, 0},
  // 4. High DRAM (4GB - TOUUD)
  {SIZE_4GB, 0},
  // 5. MCHBAR
  {0, 0},
  // 6. DMIBAR
  {0, 0},
  // 7. PXPEPBAR
  {0, 0},
  // 8. GFXVTBAR
  {0, 0},
  // 9. VTDPVC0BAR
  {0, 0},
  // 10. GDXCBAR
  {0, 0},
  // 11. EDRAMBAR (MCHBAR + 0x5408)
  {0, 0},
  // 12. CPU Reserved space: 0xFEB00000 to 0xFEB0FFFF
  {0xFEB00000, 0xFEB0FFFF},
  // 13. CPU Reserved space: 0xFEB80000 to 0xFEB8FFFF
  {0xFEB80000, 0xFEB8FFFF},
};

typedef enum {
  NonLockableMemoryRangeMBASE0,
  NonLockableMemoryRangePMBASE0,
  NonLockableMemoryRangePMBASEU0,
  NonLockableMemoryRangeMBASE1,
  NonLockableMemoryRangePMBASE1,
  NonLockableMemoryRangePMBASEU1,
  NonLockableMemoryRangeMBASE2,
  NonLockableMemoryRangePMBASE2,
  NonLockableMemoryRangePMBASEU2,
  NonLockableMemoryRangeGTTMMADR,
  NonLockableMemoryRangeGMADR,
  NonLockableMemoryRangeTMBAR,
  NonLockableMemoryRangeABAR,
  NonLockableMemoryRangeSBREG_BAR,
  NonLockableMemoryRangePWRMBASE,
  NonLockableMemoryRangeSPI_BAR0,
  NonLockableMemoryRangeMax,
} NONLOCKABLE_MEMORY_RAMGE;

MEMORY_RANGE  mNonLockableMemoryRange[NonLockableMemoryRangeMax] = {
  {0, 0},
// 1.  Local Apic for each CPU thread (IA32_APICBASE MSR 0x1B)
// 2.  MBASE0,  (PEG) BDF 0:1:0  + 0x20
// 3.  PMBASE0, (PEG) BDF 0:1:0  + 0x24 LOW
//                    BDF 0:1:1  + 0x28 HIGH
// 4.  MBASE1,  (PEG) BDF 0:1:1  + 0x20
// 5.  PMBASE1, (PEG) BDF 0:1:1  + 0x24 LOW
//                    BDF 0:1:1  + 0x28 HIGH
// 6.  MBASE2,  (PEG) BDF 0:1:2  + 0x20
// 7.  PMBASE2, (PEG) BDF 0:1:2  + 0x24 LOW
//                    BDF 0:1:1  + 0x28 HIGH
// 8.  GTTMMADR,      BDF 0:2:0  + 0x10
// 9.  GMADR,         BDF 0:2:0  + 0x18 (Need to account for MSAC)
// 10. TMBAR,         BDF 0:4:0  + 0x10 (if Device 4 is enabled in BDF 0:0:0 + 0x54[7])
// 11. ABAR,          BDF 0:31:2 + 0x24
// 12. SBREG_BAR (BDF 0:31:1 + 0x10)
// 13. PWRMBASE (BDF 0:31:2 + 0x48)
// 14. SPI_BAR0 (BDF 0:31:5 + 0x10)
};

// BIOS always keeps Below BAR address below 4G
#define B_SA_TMBAR_TMBAR_MASK             (0xffff8000)
#define B_SA_VTDBAR_VTDBAR_MASK           (0xfffff000)
#define B_SA_EDRAMBAR_EDRAMBAR_MASK       (0xffffc000)
#define B_SA_GTTMMADRBAR_GTTMMADRBAR_MASK (0xff000000)
#define B_SA_GMADRBAR_GMADRBAR_MASK       (0xf8000000)

/**
  Check for overlaps in single range array

  @param[in] Range     - Pointer to Range array
  @param[in] Count     - Number of Enties

  @retval BOOLEAN - Overlap Exists
**/
BOOLEAN
CheckOverlap (
  IN MEMORY_RANGE *Range,
  IN UINTN        Count
  )
{
  UINTN  Index;
  UINTN  SubIndex;

  for (Index = 0; Index < Count - 1; Index++) {
    if ((Range[Index].Base == 0) && (Range[Index].End == 0)) {
      continue;
    }
    for (SubIndex = Index + 1; SubIndex < Count; SubIndex++) {
      if ((Range[SubIndex].Base == 0) && (Range[SubIndex].End == 0)) {
        continue;
      }
      if (((Range[Index].Base >= Range[SubIndex].Base) && (Range[Index].Base <= Range[SubIndex].End)) ||
          ((Range[SubIndex].Base >= Range[Index].Base) && (Range[SubIndex].Base <= Range[Index].End))) {
        DEBUG ((DEBUG_ERROR, "OVERLAP: \n"));
        DEBUG ((DEBUG_ERROR, "  0x%016lx - 0x%016lx\n", Range[Index].Base, Range[Index].End));
        DEBUG ((DEBUG_ERROR, "  0x%016lx - 0x%016lx\n", Range[SubIndex].Base, Range[SubIndex].End));
        return TRUE;
      }
    }
  }

  DEBUG ((DEBUG_INFO, "CheckOverlap: PASS\n"));
  return FALSE;
}

/**
  Check for overlaps between two arrays of memory ranges

  @param[in] Range1     - Pointer to Range1 array
  @param[in] Count1     - Number of Enties
  @param[in] Range2     - Pointer to Range2 array
  @param[in] Count2     - Number of Enties

  @retval BOOLEAN - Overlap Exists
**/
BOOLEAN
CheckOverlap2 (
  IN MEMORY_RANGE *Range1,
  IN UINTN        Count1,
  IN MEMORY_RANGE *Range2,
  IN UINTN        Count2
  )
{
  UINTN  Index1;
  UINTN  Index2;

  for (Index1 = 0; Index1 < Count1; Index1++) {
    if ((Range1[Index1].Base == 0) && (Range1[Index1].End == 0)) {
      continue;
    }
    for (Index2 = 0; Index2 < Count2; Index2++) {
      if ((Range2[Index2].Base == 0) && (Range2[Index2].End == 0)) {
        continue;
      }
      if (((Range1[Index1].Base >= Range2[Index2].Base) && (Range1[Index1].Base <= Range2[Index2].End)) ||
          ((Range2[Index2].Base >= Range1[Index1].Base) && (Range2[Index2].Base <= Range1[Index1].End))) {
        DEBUG ((DEBUG_ERROR, "OVERLAP2: \n"));
        DEBUG ((DEBUG_ERROR, "  0x%016lx - 0x%016lx\n", Range1[Index1].Base, Range1[Index1].End));
        DEBUG ((DEBUG_ERROR, "  0x%016lx - 0x%016lx\n", Range2[Index2].Base, Range2[Index2].End));
        return TRUE;
      }
    }
  }

  DEBUG ((DEBUG_INFO, "CheckOverlap2: PASS\n"));
  return FALSE;
}

/**
  Dumps Ranges to Serial

  @param[in] Range     - Pointer to Range array
  @param[in] Count     - Number of Enties

**/
VOID
DumpRange (
  IN MEMORY_RANGE *Range,
  IN UINTN        Count
  )
{
  UINTN  Index;

  for (Index = 0; Index < Count; Index ++) {
    DEBUG ((DEBUG_INFO, "  [%02d] 0x%016lx - 0x%016lx\n", Index, Range[Index].Base, Range[Index].End));
  }
}

/**
  Run tests for SecureMemoryMapConfiguration bit
**/
VOID
CheckSecureMemoryMapConfiguration (
  VOID
  )
{
  EFI_STATUS        Status;
  BOOLEAN           Result;
  UINTN             McD0BaseAddress;
  UINT32            MchBar;
  UINT32            Dpr;
  UINT32            MeSegMask;
  UINT64            RemapBase;
  UINT64            RemapLimit;
  UINT32            Tom;
  UINT32            Touud;
  UINT32            Tolud;
  UINT32            Data32;
  UINT32            ApertureSize;
  UINT8             Msac;
  CHAR16            *HstiErrorString;
  UINT32            BarRead;
  UINT16            VendorIdRead;
  UINTN             PchSpiBase;
  UINT32            PwrmBase;
  UINT32            AbarSize;
  PCH_SPI_PROTOCOL  *SpiProtocol;
  UINT32            BaseAddress;
  UINT32            RegionSize;

  if ((mFeatureImplemented[1] & HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION) == 0) {
    return;
  }

  Result          = TRUE;
  McD0BaseAddress = MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN);
  // BIOS always keeps MCH BAR address below 4G
  MchBar          = (UINT32)((UINT64)(MmioRead32 (McD0BaseAddress + R_SA_MCHBAR)) & B_SA_MCHBAR_MCHBAR_MASK);

  DEBUG ((DEBUG_INFO, "  Table 3-3. Memory Map Secure Configuration\n"));

  DEBUG ((DEBUG_INFO, "    1. DPR\n"));

  Dpr = MmioRead32 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_MC_DEV, SA_MC_FUN) + R_SA_DPR);

  if ((Dpr & B_SA_DPR_LOCK_MASK) == 0) {
    DEBUG ((DEBUG_INFO, "Fail: DPR not locked\n"));

    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_CODE_1,
                        HSTI_MEMORY_MAP_SECURITY_CONFIGURATION,
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_STRING_1
                        );
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    2. MESEG\n"));
  MeSegMask =  MmioRead32 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_MC_DEV, SA_MC_FUN) + R_SA_MESEG_MASK);

  if ((MeSegMask & B_SA_MESEG_MASK_MELCK_MASK) == 0) {
    DEBUG ((DEBUG_INFO, "Fail: MESEG not locked\n"));

    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_CODE_1,
                        HSTI_MEMORY_MAP_SECURITY_CONFIGURATION,
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_STRING_1
                        );
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    3. REMAPBASE\n"));
  RemapBase = ((UINT64)(MmioRead32 (McD0BaseAddress + R_SA_REMAPBASE)) +
              LShiftU64((UINT64)MmioRead32 (McD0BaseAddress + R_SA_REMAPBASE + 4), 32));

  if ((RemapBase & B_SA_REMAPBASE_LOCK_MASK) == 0) {
    DEBUG ((DEBUG_INFO, "Fail: REMAPBASE lock not set\n"));

    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_CODE_1,
                        HSTI_MEMORY_MAP_SECURITY_CONFIGURATION,
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_STRING_1
                        );
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    4. REMAPLIMIT\n"));
  RemapLimit = (UINT64)(MmioRead32 (McD0BaseAddress + R_SA_REMAPLIMIT)) +
               LShiftU64((UINT64)MmioRead32 (McD0BaseAddress + R_SA_REMAPLIMIT + 4), 32);

  if ((RemapLimit & B_SA_REMAPLIMIT_LOCK_MASK) == 0) {
    DEBUG ((DEBUG_INFO, "Fail: REMAPLIMIT lock not set\n"));

    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_CODE_1,
                        HSTI_MEMORY_MAP_SECURITY_CONFIGURATION,
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_STRING_1
                        );
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    5. Top Of Memory (TOM)\n"));
  Tom = MmioRead32 (MmPciBase (0, SA_MC_DEV, SA_MC_FUN) + R_SA_TOM);

  if ((Tom & B_SA_TOM_LOCK_MASK) == 0) {
    DEBUG ((DEBUG_INFO, "Fail: TOM lock not set\n"));

    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_CODE_1,
                        HSTI_MEMORY_MAP_SECURITY_CONFIGURATION,
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_STRING_1
                        );
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    6. Top Of Upper Usable DRAM (TOUUD)\n"));
  Touud = MmioRead32 (MmPciBase (0, SA_MC_DEV, SA_MC_FUN) + R_SA_TOUUD);

  if ((Touud & B_SA_TOUUD_LOCK_MASK) == 0) {
    DEBUG ((DEBUG_INFO, "Fail: TOUUD lock not set\n"));

    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_CODE_1,
                        HSTI_MEMORY_MAP_SECURITY_CONFIGURATION,
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_STRING_1
                        );
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    7. Top Of Lower Usable Memory (TOLUD)\n"));
  Tolud = MmioRead32 (MmPciBase (0, SA_MC_DEV, SA_MC_FUN) + R_SA_TOLUD);

  if ((Touud & B_SA_TOLUD_LOCK_MASK) == 0) {
    DEBUG ((DEBUG_INFO, "Fail: TOLUD lock not set\n"));

    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_CODE_1,
                        HSTI_MEMORY_MAP_SECURITY_CONFIGURATION,
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_STRING_1
                        );
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    8. Lockable/fixed memory ranges overlap\n"));

 //
 // Locate BIOS region size to update High bios base address
 //
  SpiProtocol = NULL;
  Status = gBS->LocateProtocol (&gPchSpiProtocolGuid, NULL, (VOID **) &SpiProtocol);
  ASSERT_EFI_ERROR (Status);

  if(SpiProtocol != NULL) {
    SpiProtocol->GetRegionAddress (SpiProtocol, FlashRegionBios, &BaseAddress, &RegionSize);

    DEBUG ((DEBUG_INFO, "Bios Region Size %x:\n", RegionSize));
    mLockableMemoryRange[LockableMemoryRangeHighBios].Base  = SIZE_4GB - RegionSize;
    mLockableMemoryRange[LockableMemoryRangeLowDram].End    = (((UINT64)(MmioRead32 (McD0BaseAddress + R_SA_TOLUD)) +
                                                               LShiftU64((UINT64)MmioRead32 (McD0BaseAddress + R_SA_TOLUD + 4), 32)) &
                                                               B_SA_TOLUD_TOLUD_MASK) - 1;
  }

  mLockableMemoryRange[LockableMemoryRangeHighDram].End     = (((UINT64)(MmioRead32 (McD0BaseAddress + R_SA_TOUUD)) +
                                                               LShiftU64((UINT64)MmioRead32 (McD0BaseAddress + R_SA_TOUUD + 4), 32)) &
                                                               B_SA_TOUUD_TOUUD_MASK) - 1;

  mLockableMemoryRange[LockableMemoryRangeMchBar].Base      = ((UINT64)(MmioRead32 (McD0BaseAddress + R_SA_MCHBAR)) +
                                                               LShiftU64((UINT64)MmioRead32 (McD0BaseAddress + R_SA_MCHBAR + 4), 32)) &
                                                               B_SA_MCHBAR_MCHBAR_MASK;
  mLockableMemoryRange[LockableMemoryRangeMchBar].End       = mLockableMemoryRange[LockableMemoryRangeMchBar].Base + SIZE_32KB - 1;

  mLockableMemoryRange[LockableMemoryRangeDmiBar].Base      = ((UINT64)(MmioRead32 (McD0BaseAddress + R_SA_DMIBAR)) +
                                                               LShiftU64((UINT64)MmioRead32 (McD0BaseAddress + R_SA_DMIBAR + 4), 32)) &
                                                               B_SA_DMIBAR_DMIBAR_MASK;
  mLockableMemoryRange[LockableMemoryRangeDmiBar].End       = mLockableMemoryRange[LockableMemoryRangeDmiBar].Base + SIZE_4KB - 1;
  mLockableMemoryRange[LockableMemoryRangePxpEpBar].Base    = ((UINT64)(MmioRead32 (McD0BaseAddress + R_SA_PXPEPBAR)) +
                                                               LShiftU64((UINT64)MmioRead32 (McD0BaseAddress + R_SA_PXPEPBAR + 4), 32)) &
                                                               B_SA_PXPEPBAR_PXPEPBAR_MASK;
  mLockableMemoryRange[LockableMemoryRangePxpEpBar].End     = mLockableMemoryRange[LockableMemoryRangePxpEpBar].Base + SIZE_4KB - 1;

  Data32 = MmioRead32 (MchBar + R_SA_MCHBAR_VTD1_OFFSET);
  if ((Data32 & BIT0) != 0) {
    mLockableMemoryRange[LockableMemoryRangeGfxVtBar].Base = Data32 & B_SA_VTDBAR_VTDBAR_MASK;
    mLockableMemoryRange[LockableMemoryRangeGfxVtBar].End  = mLockableMemoryRange[LockableMemoryRangeGfxVtBar].Base + 0x1000 - 1;
  }

  Data32 = MmioRead32 (MchBar + R_SA_MCHBAR_VTD2_OFFSET);
  if ((Data32 & BIT0) != 0) {
    mLockableMemoryRange[LockableMemoryRangeVtdPvc0Bar].Base = Data32 & B_SA_VTDBAR_VTDBAR_MASK;
    mLockableMemoryRange[LockableMemoryRangeVtdPvc0Bar].End  = mLockableMemoryRange[LockableMemoryRangeVtdPvc0Bar].Base + 0x1000 - 1;
  }

  Data32 = MmioRead32 (MchBar + R_SA_MCHBAR_GDXCBAR_OFFSET);
  if ((Data32 & BIT0) != 0) {
    mLockableMemoryRange[LockableMemoryRangeGdxcBar].Base = Data32 & B_SA_VTDBAR_VTDBAR_MASK;
    mLockableMemoryRange[LockableMemoryRangeGdxcBar].End  = mLockableMemoryRange[LockableMemoryRangeGdxcBar].Base + 0x1000 - 1;
  }

  Data32 = MmioRead32 (MchBar + R_SA_MCHBAR_EDRAMBAR_OFFSET);
  if ((Data32 & BIT0) != 0) {
    mLockableMemoryRange[LockableMemoryRangeEdramBar].Base = Data32 & B_SA_EDRAMBAR_EDRAMBAR_MASK;
    mLockableMemoryRange[LockableMemoryRangeEdramBar].End  = mLockableMemoryRange[LockableMemoryRangeEdramBar].Base + 0x4000 - 1;
  }

  DEBUG ((DEBUG_INFO, "Lockable memory ranges:\n"));
  DumpRange (mLockableMemoryRange, LockableMemoryRangeMax);
  if (CheckOverlap (mLockableMemoryRange, LockableMemoryRangeMax) || EFI_ERROR (Status)) {

    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_CODE_2,
                        HSTI_MEMORY_MAP_SECURITY_CONFIGURATION,
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_STRING_2
                        );
    Status = HstiLibAppendErrorString (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               HstiErrorString
               );
    ASSERT_EFI_ERROR (Status);
    Result = FALSE;
    FreePool (HstiErrorString);
  }

  DEBUG ((DEBUG_INFO, "    9. Non lockable memory ranges overlap\n"));

  if (MmioRead32 (MmPciBase (0, 0, 0) + 0x54) & BIT3) {
    mNonLockableMemoryRange[NonLockableMemoryRangeMBASE0].Base = LShiftU64 ((UINT64)(MmioRead16 (MmPciBase (0, SA_PEG10_DEV_NUM, SA_PEG10_FUN_NUM) + 0x20) & 0xFFF0), 16);
    mNonLockableMemoryRange[NonLockableMemoryRangeMBASE0].End  = LShiftU64 ((UINT64)(MmioRead16 (MmPciBase (0, SA_PEG10_DEV_NUM, SA_PEG10_FUN_NUM) + 0x22) & 0xFFF0), 16);

    BarRead = (UINT32)MmioRead16 (MmPciBase (0,SA_PEG10_DEV_NUM,SA_PEG10_FUN_NUM) + 0x24);
    if ((BarRead & 0xF) != 0) {
      mNonLockableMemoryRange[NonLockableMemoryRangePMBASE0].Base = LShiftU64 ((UINT64)(BarRead & 0xFFF0), 16) + LShiftU64 ((UINT64)(MmioRead32 (MmPciBase (0, SA_PEG10_DEV_NUM, SA_PEG10_FUN_NUM) + 0x28)), 32);
    } else {
      mNonLockableMemoryRange[NonLockableMemoryRangePMBASE0].Base = LShiftU64 ((UINT64)(BarRead & 0xFFF0), 16);
    }

    BarRead = (UINT32)MmioRead16 (MmPciBase (0, SA_PEG10_DEV_NUM, SA_PEG10_FUN_NUM) + 0x26);
    if ((BarRead & 0xF) != 0) {
      mNonLockableMemoryRange[NonLockableMemoryRangePMBASE0].End = LShiftU64 ((UINT64)(BarRead & 0xFFF0), 16) + LShiftU64 ((UINT64)(MmioRead32 (MmPciBase (0, SA_PEG10_DEV_NUM, SA_PEG10_FUN_NUM) + 0x2C)), 32);
    } else {
      mNonLockableMemoryRange[NonLockableMemoryRangePMBASE0].End = LShiftU64 ((UINT64)(BarRead & 0xFFF0), 16);
    }
  }

  //
  // Check to make sure that if PEG0 is enabled but nothing is connected that we ignore these ranges
  //
  if(mNonLockableMemoryRange[NonLockableMemoryRangeMBASE0].End < mNonLockableMemoryRange[NonLockableMemoryRangeMBASE0].Base)
  {
    mNonLockableMemoryRange[NonLockableMemoryRangeMBASE0].Base = 0;
    mNonLockableMemoryRange[NonLockableMemoryRangeMBASE0].End  = 0;
  }
  if(mNonLockableMemoryRange[NonLockableMemoryRangePMBASE0].End < mNonLockableMemoryRange[NonLockableMemoryRangePMBASE0].Base)
  {
    mNonLockableMemoryRange[NonLockableMemoryRangePMBASE0].Base = 0;
    mNonLockableMemoryRange[NonLockableMemoryRangePMBASE0].End  = 0;
  }

  if (MmioRead32 (MmPciBase (0,0,0) + 0x54) & BIT2) {
    mNonLockableMemoryRange[NonLockableMemoryRangeMBASE1].Base = LShiftU64 ((UINT64)(MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_PEG11_DEV_NUM, SA_PEG11_FUN_NUM) + 0x20) & 0xFFF0), 16);
    mNonLockableMemoryRange[NonLockableMemoryRangeMBASE1].End  = LShiftU64 ((UINT64)(MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_PEG11_DEV_NUM, SA_PEG11_FUN_NUM) + 0x22) & 0xFFF0), 16);

    BarRead = (UINT32)MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_PEG11_DEV_NUM, SA_PEG11_FUN_NUM) + 0x24);

    if ((BarRead & 0xF) != 0) {
      mNonLockableMemoryRange[NonLockableMemoryRangePMBASE1].Base = LShiftU64 ((UINT64)(BarRead & 0xFFF0), 16) + LShiftU64 ((UINT64)(MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_PEG11_DEV_NUM, SA_PEG11_FUN_NUM) + 0x28)), 32);
    } else {
      mNonLockableMemoryRange[NonLockableMemoryRangePMBASE1].Base = LShiftU64 ((UINT64)(BarRead & 0xFFF0), 16);
    }

    BarRead = MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_PEG11_DEV_NUM, SA_PEG11_FUN_NUM) + 0x26);
    if ((BarRead & 0xF) != 0) {
      mNonLockableMemoryRange[NonLockableMemoryRangePMBASE1].End = LShiftU64 ((UINT64)(BarRead & 0xFFF0), 16) + LShiftU64 ((UINT64)(MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH,SA_PEG11_DEV_NUM,SA_PEG11_FUN_NUM) + 0x2C)), 32);
    } else {
      mNonLockableMemoryRange[NonLockableMemoryRangePMBASE1].End = LShiftU64 ((UINT64)(BarRead & 0xFFF0), 16);
    }
  }

  //
  // Check to make sure that if PEG1 is enabled but nothing is connected that we ignore these ranges
  //
  if(mNonLockableMemoryRange[NonLockableMemoryRangeMBASE1].End < mNonLockableMemoryRange[NonLockableMemoryRangeMBASE1].Base)
  {
    mNonLockableMemoryRange[NonLockableMemoryRangeMBASE1].Base = 0;
    mNonLockableMemoryRange[NonLockableMemoryRangeMBASE1].End  = 0;
  }
  if(mNonLockableMemoryRange[NonLockableMemoryRangePMBASE1].End < mNonLockableMemoryRange[NonLockableMemoryRangePMBASE1].Base)
  {
    mNonLockableMemoryRange[NonLockableMemoryRangePMBASE1].Base = 0;
    mNonLockableMemoryRange[NonLockableMemoryRangePMBASE1].End  = 0;
  }

  if (MmioRead32 (MmPciBase (0, 0, 0) + 0x54) & BIT1) {
    mNonLockableMemoryRange[NonLockableMemoryRangeMBASE2].Base = LShiftU64 ((UINT64)(MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_PEG12_DEV_NUM, SA_PEG12_FUN_NUM) + 0x20) & 0xFFF0), 16);
    mNonLockableMemoryRange[NonLockableMemoryRangeMBASE2].End  = LShiftU64 ((UINT64)(MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_PEG12_DEV_NUM, SA_PEG12_FUN_NUM) + 0x22) & 0xFFF0), 16);

    BarRead = MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_PEG12_DEV_NUM, SA_PEG12_FUN_NUM) + 0x24);
    if ((BarRead & 0xF) != 0) {
      mNonLockableMemoryRange[NonLockableMemoryRangePMBASE2].Base = LShiftU64 ((UINT64)(BarRead & 0xFFF0), 16) + LShiftU64 ((UINT64)(MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_PEG12_DEV_NUM, SA_PEG12_FUN_NUM) + 0x28)), 32);

    } else {
      mNonLockableMemoryRange[NonLockableMemoryRangePMBASE2].Base = LShiftU64 ((UINT64)(BarRead & 0xFFF0),16);
    }

    BarRead = (UINT32)MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_PEG12_DEV_NUM, SA_PEG12_FUN_NUM) + 0x26);

    if ((BarRead & 0xF) != 0) {
      mNonLockableMemoryRange[NonLockableMemoryRangePMBASE2].End = LShiftU64 ((UINT64)(BarRead & 0xFFF0), 16) + LShiftU64 ((UINT64)(MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_PEG12_DEV_NUM, SA_PEG12_FUN_NUM) + 0x2C)), 32);
    } else {
      mNonLockableMemoryRange[NonLockableMemoryRangePMBASE2].End = LShiftU64 ((UINT64)(BarRead & 0xFFF0), 16);
    }
  }

  //
  // Check to make sure that if PEG2 is enabled but nothing is connected that we ignore these ranges
  //
  if(mNonLockableMemoryRange[NonLockableMemoryRangeMBASE2].End < mNonLockableMemoryRange[NonLockableMemoryRangeMBASE2].Base)
  {
    mNonLockableMemoryRange[NonLockableMemoryRangeMBASE2].Base = 0;
    mNonLockableMemoryRange[NonLockableMemoryRangeMBASE2].End = 0;
  }
  if(mNonLockableMemoryRange[NonLockableMemoryRangePMBASE2].End < mNonLockableMemoryRange[NonLockableMemoryRangePMBASE2].Base)
  {
    mNonLockableMemoryRange[NonLockableMemoryRangePMBASE2].Base = 0;
    mNonLockableMemoryRange[NonLockableMemoryRangePMBASE2].End  = 0;
  }

  if (MmioRead32 (MmPciBase (0, 0, 0) + 0x54) & BIT4) {
    mNonLockableMemoryRange[NonLockableMemoryRangeGTTMMADR].Base     = MmioRead32 (MmPciBase(DEFAULT_PCI_BUS_NUMBER_PCH, SA_IGD_DEV, SA_IGD_FUN_0) + R_SA_IGD_GTTMMADR) & B_SA_GTTMMADRBAR_GTTMMADRBAR_MASK;
    mNonLockableMemoryRange[NonLockableMemoryRangeGTTMMADR].End  = mNonLockableMemoryRange[NonLockableMemoryRangeGTTMMADR].Base + SIZE_16MB - 1;

    Msac = MmioRead8 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, SA_IGD_DEV, SA_MC_FUN) + R_SA_IGD_MSAC_OFFSET);
    ApertureSize = ((Msac & (BIT0 | BIT1 | BIT2 | BIT3 | BIT4)) + 1) * SIZE_128MB;
    mNonLockableMemoryRange[NonLockableMemoryRangeGMADR].Base    = MmioRead32 (MmPciBase(DEFAULT_PCI_BUS_NUMBER_PCH, SA_IGD_DEV, SA_IGD_FUN_0) + R_SA_IGD_GMADR) & B_SA_GMADRBAR_GMADRBAR_MASK;
    mNonLockableMemoryRange[NonLockableMemoryRangeGMADR].End     = mNonLockableMemoryRange[NonLockableMemoryRangeGMADR].Base + ApertureSize - 1;
  }

  if (MmioRead32 (MmPciBase (0, 0, 0) + 0x54) & BIT7) {
    mNonLockableMemoryRange[NonLockableMemoryRangeTMBAR].Base = MmioRead32 (MmPciBase(0, 4, 0) + 0x10) & B_SA_TMBAR_TMBAR_MASK;
    mNonLockableMemoryRange[NonLockableMemoryRangeTMBAR].End  = mNonLockableMemoryRange[NonLockableMemoryRangeTMBAR].Base + SIZE_32KB - 1;
  }

  VendorIdRead = MmioRead16 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH,PCI_DEVICE_NUMBER_PCH_SATA,PCI_FUNCTION_NUMBER_PCH_SATA) + 0);
  DEBUG ((DEBUG_INFO, "VendorIdRead SATA: %x\n", VendorIdRead));

  if (VendorIdRead != 0xFFFF) {
    BarRead = MmioRead32 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_SATA, PCI_FUNCTION_NUMBER_PCH_SATA) + R_PCH_SATA_SATAGC);

    if ((BarRead & BIT10) == 0 ) {
      mNonLockableMemoryRange[NonLockableMemoryRangeABAR].Base = MmioRead32 (MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_SATA, PCI_FUNCTION_NUMBER_PCH_SATA) + R_PCH_SATA_AHCI_BAR) & B_PCH_SATA_AHCI_BAR_BA;

      switch (BarRead & 0x7) {
        case V_PCH_SATA_SATAGC_ASSEL_2K:
          AbarSize = SIZE_2KB;
          break;

        case V_PCH_SATA_SATAGC_ASSEL_16K:
          AbarSize = SIZE_16KB;
          break;

        case V_PCH_SATA_SATAGC_ASSEL_32K:
          AbarSize = SIZE_32KB;
          break;

        case V_PCH_SATA_SATAGC_ASSEL_64K:
          AbarSize = SIZE_64KB;
          break;

        case V_PCH_SATA_SATAGC_ASSEL_128K:
          AbarSize = SIZE_128KB;
          break;

        case V_PCH_SATA_SATAGC_ASSEL_512K:
          AbarSize = SIZE_256KB;
          break;

        default:
          AbarSize= SIZE_2KB;
          break;
      }
      mNonLockableMemoryRange[NonLockableMemoryRangeABAR].End  = mNonLockableMemoryRange[NonLockableMemoryRangeABAR].Base + AbarSize - 1;
    }
  }

  mNonLockableMemoryRange[NonLockableMemoryRangeSBREG_BAR].Base = PCH_PCR_BASE_ADDRESS;
  mNonLockableMemoryRange[NonLockableMemoryRangeSBREG_BAR].End  = PCH_PCR_BASE_ADDRESS + SIZE_16MB-1;

  PchPwrmBaseGet (&PwrmBase);
  mNonLockableMemoryRange[NonLockableMemoryRangePWRMBASE].Base = PwrmBase;
  mNonLockableMemoryRange[NonLockableMemoryRangePWRMBASE].End  = PwrmBase + PCH_PWRM_MMIO_SIZE - 1;

  PchSpiBase = MmioRead32 (MmPciBase (
                             DEFAULT_PCI_BUS_NUMBER_PCH,
                             PCI_DEVICE_NUMBER_PCH_SPI,
                             PCI_FUNCTION_NUMBER_PCH_SPI)
                             + R_PCH_SPI_BAR0) & ~B_PCH_SPI_BAR0_MASK;

  mNonLockableMemoryRange[NonLockableMemoryRangeSPI_BAR0].Base = PchSpiBase;
  mNonLockableMemoryRange[NonLockableMemoryRangeSPI_BAR0].End  = PchSpiBase + SIZE_4KB-1;

  DEBUG ((DEBUG_INFO, "Non lockable memory ranges:\n"));
  DumpRange (mNonLockableMemoryRange, NonLockableMemoryRangeMax);
  if (CheckOverlap (mNonLockableMemoryRange, NonLockableMemoryRangeMax) ||
      CheckOverlap2 (mLockableMemoryRange, LockableMemoryRangeMax, mNonLockableMemoryRange, NonLockableMemoryRangeMax)) {

    HstiErrorString = BuildHstiErrorString (
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_CODE_3,
                        HSTI_MEMORY_MAP_SECURITY_CONFIGURATION,
                        HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_ERROR_STRING_3
                        );
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
               1,
               HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION
               );
    ASSERT_EFI_ERROR (Status);
  }

  return;
}
