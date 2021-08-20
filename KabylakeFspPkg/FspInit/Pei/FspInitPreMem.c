/** @file
  Source code file for FSP Init Pre-Memory PEI module

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2017 Intel Corporation.

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

#include <FspInitPreMem.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <CpuRegs.h>
#include <Library/PostCodeLib.h>
#include <Library/FspCommonLib.h>
#include <Library/PerformanceLib.h>
#include <Library/MemoryAllocationLib.h>

extern EFI_GUID gFspSiliconFvGuid;
extern EFI_GUID gFspPerformanceDataGuid;

EFI_PEI_RESET_PPI mResetPpi = {
  ResetSystem
};

static EFI_PEI_PPI_DESCRIPTOR mPreMemPpiList[] = {
  {
    (EFI_PEI_PPI_DESCRIPTOR_PPI| EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiResetPpiGuid,
    &mResetPpi
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_PPI_DESCRIPTOR mPpiBootMode = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiMasterBootModePpiGuid,
  NULL
};

EFI_PEI_NOTIFY_DESCRIPTOR mMemoryDiscoveredNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiMemoryDiscoveredPpiGuid,
  MemoryDiscoveredPpiNotifyCallback
};

/**
  This function reset the entire platform, including all processor and devices, and
  reboots the system.

  @param  PeiServices General purpose services available to every PEIM.

  @retval EFI_SUCCESS if it completed successfully.
**/
EFI_STATUS
EFIAPI
ResetSystem (
  IN CONST EFI_PEI_SERVICES **PeiServices
  )
{
  IoWrite8 (0xCF9, 0x06);
  CpuDeadLoop ();
  return EFI_SUCCESS;
}

/**
  This function retrieves the top of usable low memory.

  @param    HobListPtr   A HOB list pointer.

  @retval                Usable low memory top.

**/
UINT32
GetUsableLowMemTop (
  CONST VOID       *HobStart
)
{
  EFI_PEI_HOB_POINTERS  Hob;
  UINT32                MemLen;
  /*
   * Get the HOB list for processing
   */
  Hob.Raw = (VOID *)HobStart;

  /*
   * Collect memory ranges
   */
  MemLen = 0x100000;
  while (!END_OF_HOB_LIST (Hob)) {
    if (Hob.Header->HobType == EFI_HOB_TYPE_RESOURCE_DESCRIPTOR) {
      if (Hob.ResourceDescriptor->ResourceType == EFI_RESOURCE_SYSTEM_MEMORY) {
        /*
         * Need memory above 1MB to be collected here
         */
        if (Hob.ResourceDescriptor->PhysicalStart >= 0x100000 &&
            Hob.ResourceDescriptor->PhysicalStart < (EFI_PHYSICAL_ADDRESS) 0x100000000) {
          MemLen += (UINT32) (Hob.ResourceDescriptor->ResourceLength);
        }
      }
    }
    Hob.Raw = GET_NEXT_HOB (Hob);
  }

  return MemLen;
}

/**
  This function determines if any MTRRs have been programmed.

  @retval  TRUE if any MTRRs have been programmed.
  @retval  FALSE if no MTRRs have been programmed.
**/
BOOLEAN
CheckIfMtrrsProgrammed()
{
  static UINT32 FixedMtrrs[] = {
    MSR_IA32_MTRR_FIX64K_00000,
    MSR_IA32_MTRR_FIX16K_80000,
    MSR_IA32_MTRR_FIX16K_A0000,
    MSR_IA32_MTRR_FIX4K_C0000,
    MSR_IA32_MTRR_FIX4K_C8000,
    MSR_IA32_MTRR_FIX4K_D0000,
    MSR_IA32_MTRR_FIX4K_D8000,
    MSR_IA32_MTRR_FIX4K_E0000,
    MSR_IA32_MTRR_FIX4K_E8000,
    MSR_IA32_MTRR_FIX4K_F0000,
    MSR_IA32_MTRR_FIX4K_F8000
  };

  MSR_IA32_MTRRCAP_REGISTER Msr;
  UINT32                    Index;
  UINT32                    Mtrr;

  for (Index = 0; Index < sizeof(FixedMtrrs) / sizeof(UINT32); ++Index) {
    if (AsmReadMsr64(FixedMtrrs[Index]) != 0) return TRUE;
  }

  Msr.Uint64 = AsmReadMsr64(MSR_IA32_MTRRCAP);
  for (Index = 0; Index < Msr.Bits.VCNT * 2; ++Index) {
    Mtrr = MSR_IA32_MTRR_PHYSBASE0 + Index;
    if (AsmReadMsr64(Mtrr) != 0) return TRUE;
  }

  return FALSE;
}

/**
  This function prints MTRRs.
**/
VOID
PrintMtrrs (
  VOID
)
{
  DEBUG_CODE_BEGIN();

  typedef struct {
    char    *Desc;
    UINT32  Msr;
  } MTRR_INFO;

  MSR_IA32_MTRRCAP_REGISTER Msr;
  UINT32                    Index;
  UINT32                    Mtrr;

  static MTRR_INFO MtrrInfo[] = {
    {"MSR_IA32_MTRR_FIX64K_00000",  MSR_IA32_MTRR_FIX64K_00000},
    {"MSR_IA32_MTRR_FIX16K_80000",  MSR_IA32_MTRR_FIX16K_80000},
    {"MSR_IA32_MTRR_FIX16K_A0000",  MSR_IA32_MTRR_FIX16K_A0000},
    {"MSR_IA32_MTRR_FIX4K_C0000 ",  MSR_IA32_MTRR_FIX4K_C0000},
    {"MSR_IA32_MTRR_FIX4K_C8000 ",  MSR_IA32_MTRR_FIX4K_C8000},
    {"MSR_IA32_MTRR_FIX4K_D0000 ",  MSR_IA32_MTRR_FIX4K_D0000},
    {"MSR_IA32_MTRR_FIX4K_D8000 ",  MSR_IA32_MTRR_FIX4K_D8000},
    {"MSR_IA32_MTRR_FIX4K_E0000 ",  MSR_IA32_MTRR_FIX4K_E0000},
    {"MSR_IA32_MTRR_FIX4K_E8000 ",  MSR_IA32_MTRR_FIX4K_E8000},
    {"MSR_IA32_MTRR_FIX4K_F0000 ",  MSR_IA32_MTRR_FIX4K_F0000},
    {"MSR_IA32_MTRR_FIX4K_F8000 ",  MSR_IA32_MTRR_FIX4K_F8000}
  };

  for (Index = 0; Index < sizeof(MtrrInfo) / sizeof(MTRR_INFO); ++Index) {
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "%a Msr %x = %016llx\n", MtrrInfo[Index].Desc, MtrrInfo[Index].Msr, AsmReadMsr64(MtrrInfo[Index].Msr)));
  }

  Msr.Uint64 = AsmReadMsr64(MSR_IA32_MTRRCAP);
  for (Index = 0; Index < Msr.Bits.VCNT; ++Index) {
    Mtrr = MSR_IA32_MTRR_PHYSBASE0 + (2 * Index);
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "MSR_IA32_MTRR_PHYSBASE%d Msr %x = %016llx\n",
        Index, Mtrr, AsmReadMsr64(Mtrr)
    ));

    DEBUG ((DEBUG_INFO | DEBUG_INIT, "MSR_IA32_MTRR_PHYSMASK%d Msr %x = %016llx\n",
        Index, Mtrr + 1, AsmReadMsr64(Mtrr + 1)
    ));
  }
  DEBUG_CODE_END();
}

/**
  This function programs Cache Attributes.
**/
VOID ProgramCacheAttributes (
  VOID
  )
{
  UINT64            LowMemoryLength;
  UINT64            HighMemoryLength;
  UINT64            MaxLowMemoryLength;
  FSP_GLOBAL_DATA   *FspData;

  MTRR_SETTINGS     MtrrSetting;
  EFI_STATUS        Status;

  ///
  /// Reset all MTRR setting.
  ///
  ZeroMem (&MtrrSetting, sizeof (MTRR_SETTINGS));


  //
  // Disable Cache as RAM
  //
  DisableCacheAsRam (TRUE);

  ///
  /// Cache the Flash area as WP to boost performance
  /// Set WP cache size to fixed at 16MB for saving MTRR usage.
  ///
  Status = MtrrSetMemoryAttributeInMtrrSettings (
             &MtrrSetting,
             0xff000000,
             0x01000000,
             CacheWriteProtected
             );
  ASSERT_EFI_ERROR (Status);

  MtrrSetAllMtrrs (&MtrrSetting);

  //
  // Get system memory from HOB
  //
  FspGetSystemMemorySize (&LowMemoryLength, &HighMemoryLength);

  FspData  = GetFspGlobalDataPointer ();
 
  DEBUG ((DEBUG_INFO | DEBUG_INIT, "MicrocodeRegionBase : 0x%08x\n", FspData->PlatformData.MicrocodeRegionBase));
  DEBUG ((DEBUG_INFO | DEBUG_INIT, "MicrocodeRegionSize : 0x%08x\n", FspData->PlatformData.MicrocodeRegionSize));
  DEBUG ((DEBUG_INFO | DEBUG_INIT, "CodeRegionBase      : 0x%08x\n", FspData->PlatformData.CodeRegionBase));
  DEBUG ((DEBUG_INFO | DEBUG_INIT, "CodeRegionSize      : 0x%08x\n", FspData->PlatformData.CodeRegionSize));

  DEBUG ((DEBUG_INFO, "[FSP] Memory Length (Below 4GB) = %lx.\n", LowMemoryLength));
  DEBUG ((DEBUG_INFO, "[FSP] Memory Length (Above 4GB) = %lx.\n", HighMemoryLength));

  //
  // Set fixed MTRR values
  //
  Status = MtrrSetMemoryAttributeInMtrrSettings (
              &MtrrSetting,
              0x00000,
              0xA0000,
              CacheWriteBack
              );
   ASSERT_EFI_ERROR (Status);

   Status = MtrrSetMemoryAttributeInMtrrSettings (
               &MtrrSetting,
               0xA0000,
               0x20000,
               CacheUncacheable
               );
   ASSERT_EFI_ERROR (Status);



    Status = MtrrSetMemoryAttributeInMtrrSettings (
                &MtrrSetting,
                0xC0000,
                0x40000,
                CacheWriteBack
                );
    ASSERT_EFI_ERROR (Status);

  //
  // Set the largest range as WB and then patch smaller ranges with UC
  // It can reduce the MTRR register usage
  //
  MaxLowMemoryLength = GetPowerOfTwo64 (LowMemoryLength);
  if (LowMemoryLength != MaxLowMemoryLength) {
    MaxLowMemoryLength = LShiftU64 (MaxLowMemoryLength, 1);
  }
  if (MaxLowMemoryLength >= 0x100000000ULL) {
    MaxLowMemoryLength = (LowMemoryLength + 0x0FFFFFFF) & 0xF0000000;
  }

  Status = MtrrSetMemoryAttributeInMtrrSettings (
              &MtrrSetting,
              0x100000,
              MaxLowMemoryLength - 0x100000,
              CacheWriteBack
              );
  ASSERT_EFI_ERROR (Status);
 
  if (LowMemoryLength != MaxLowMemoryLength) {
    Status = MtrrSetMemoryAttributeInMtrrSettings (
                &MtrrSetting,
                LowMemoryLength,
                MaxLowMemoryLength - LowMemoryLength,
                CacheUncacheable
                );
    ASSERT_EFI_ERROR (Status);
  }

  if (HighMemoryLength) {
    Status = MtrrSetMemoryAttributeInMtrrSettings (
                &MtrrSetting,
                0x100000000,
                HighMemoryLength,
                CacheWriteBack
                );
  }

  ///
  /// Update MTRR setting from MTRR buffer
  ///
  MtrrSetAllMtrrs (&MtrrSetting);
}

/**
  Migrate FSP-M UPD data before destroying CAR.
**/
VOID
EFIAPI
MigrateFspmUpdData (
  VOID
 )
{
  FSP_INFO_HEADER           *FspInfoHeaderPtr;
  VOID                      *FspmUpdPtrPostMem;
  VOID                      *FspmUpdPtrPreMem;

  FspInfoHeaderPtr = GetFspInfoHeader();
  FspmUpdPtrPostMem = (VOID *)AllocatePages (EFI_SIZE_TO_PAGES ((UINTN)FspInfoHeaderPtr->CfgRegionSize));
  ASSERT(FspmUpdPtrPostMem != NULL);

  FspmUpdPtrPreMem = (VOID *)GetFspMemoryInitUpdDataPointer ();
  CopyMem (FspmUpdPtrPostMem, (VOID *)FspmUpdPtrPreMem, (UINTN)FspInfoHeaderPtr->CfgRegionSize);

  //
  // Update FSP-M UPD pointer in FSP Global Data
  //
  SetFspMemoryInitUpdDataPointer((VOID *)FspmUpdPtrPostMem);

  DEBUG ((DEBUG_INFO, "Migrate FSP-M UPD from %x to %x \n", FspmUpdPtrPreMem, FspmUpdPtrPostMem));

}

/**
  This function reports and installs new FV

  @retval     EFI_SUCCESS          The function completes successfully
**/
EFI_STATUS
ReportAndInstallNewFv (
  VOID
)
{
  EFI_FIRMWARE_VOLUME_EXT_HEADER *FwVolExtHeader;
  FSP_INFO_HEADER                *FspInfoHeader;
  EFI_FIRMWARE_VOLUME_HEADER     *FvHeader;
  UINT8                          *CurPtr;
  UINT8                          *EndPtr;

  FspInfoHeader = GetFspInfoHeaderFromApiContext();
  if (FspInfoHeader->Signature != FSP_INFO_HEADER_SIGNATURE) {
    DEBUG ((DEBUG_ERROR, "The signature of FspInfoHeader getting from API context is invalid.\n"));
    FspInfoHeader = GetFspInfoHeader();
  }

  CurPtr = (UINT8 *)FspInfoHeader->ImageBase;
  EndPtr = CurPtr + FspInfoHeader->ImageSize - 1;

  while (CurPtr < EndPtr) {
    FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)CurPtr;
    if (FvHeader->Signature != EFI_FVH_SIGNATURE) {
      break;
    }

    if (FvHeader->ExtHeaderOffset != 0) {
      //
      // Searching for the silicon FV in the FSP image.
      //
      FwVolExtHeader = (EFI_FIRMWARE_VOLUME_EXT_HEADER *) ((UINT8 *) FvHeader + FvHeader->ExtHeaderOffset);
      if (CompareGuid(&FwVolExtHeader->FvName, &gFspSiliconFvGuid)) {
        PeiServicesInstallFvInfoPpi (
          NULL,
          (VOID *)FvHeader,
          (UINTN) FvHeader->FvLength,
          NULL,
          NULL
          );
      }
    }
    CurPtr += FvHeader->FvLength;
  }

  return EFI_SUCCESS;
}


/**
  This function will be called when MRC is done.

  @param  PeiServices General purpose services available to every PEIM.

  @param  NotifyDescriptor Information about the notify event..

  @param  Ppi The notify context.

  @retval EFI_SUCCESS If the function completed successfully.
**/
EFI_STATUS
EFIAPI
MemoryDiscoveredPpiNotifyCallback (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  UINT8                          PhysicalAddressBits;
  CPUID_VIR_PHY_ADDRESS_SIZE_EAX Eax;
  VOID                           **HobListPtr;

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "Memory Discovered Notify invoked ...\n"));

  AsmCpuid (CPUID_EXTENDED_FUNCTION, &Eax.Uint32, NULL, NULL, NULL);
  if (Eax.Uint32 >= CPUID_VIR_PHY_ADDRESS_SIZE) {
    AsmCpuid (CPUID_VIR_PHY_ADDRESS_SIZE, &Eax.Uint32, NULL, NULL, NULL);
    PhysicalAddressBits = (UINT8) Eax.Bits.PhysicalAddressBits;
  } else {
    PhysicalAddressBits = 36;
  }

  ///
  /// Create a CPU hand-off information
  ///
  BuildCpuHob (PhysicalAddressBits, 16);

  //
  // Create a memory allocation HOB at fixed location.
  //
  BuildMemoryAllocationHob (
    PcdGet32 (PcdFspCpuPeiApWakeupBufferAddr),
    EFI_PAGE_SIZE,
    EfiBootServicesData
    );

  //
  // Migrate FSP-M UPD data before destroying CAR
  //
  MigrateFspmUpdData ();

  //
  // Calling use FspMemoryInit API
  // Return the control directly
  //
  HobListPtr = (VOID **)GetFspApiParameter2 ();
  //FSP Common Module(0x800) | Api Exit(0x7F)
  PostCode (0x87F);
  //
  // This is the end of the FspMemoryInit API
  // Give control back to the boot loader
  //
  FspMemoryInitDone (HobListPtr);

  if (GetFspApiCallingIndex () == TempRamExitApiIndex) {
    //TempRamExit Api Entry PostCode
    //FSP Common Module(0x800) | Api Entry(0x00)
    PostCode (0x800);
    //
    // Program MTRR values.
    //
    ProgramCacheAttributes ();
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "MTRR programming:\n"));
    PrintMtrrs ();

    //
    // This is the end of the TempRamExit API
    // Give control back to the boot loader
    //
    FspTempRamExitDone ();
  }
  //FSP Common Module(0x800) | Api Entry(0x00)
  PostCode (0x800);
  // MTRRs are not already programmed in FSP flow 1.1.
  //
  if (!CheckIfMtrrsProgrammed ()) {
    ProgramCacheAttributes ();
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "MTRR programming:\n"));
    PrintMtrrs ();
  }

  //
  // Install FSP silicon FV
  //
  ReportAndInstallNewFv ();

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "Memory Discovered Notify completed ...\n"));

  return EFI_SUCCESS;
}

/**
  FSP Init before memory PEI module entry point

  @param[in]  FileHandle           Not used.
  @param[in]  PeiServices          General purpose services available to every PEIM.

  @retval     EFI_SUCCESS          The function completes successfully
  @retval     EFI_OUT_OF_RESOURCES Insufficient resources to create database
**/
EFI_STATUS
FspInitPreMemEntryPoint (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS              Status;
  SI_PREMEM_POLICY_PPI    *SiPreMemPolicyPpi;
  EFI_BOOT_MODE           BootMode;
  FSPM_UPD                *FspmUpdDataPtr;

  DEBUG ((DEBUG_INFO, "FspInitPreMemEntryPoint\n"));

  //MemoryInit Phase Postcode set
  SetPhaseStatusCode (0xD000);
  //MemoryInit API Entry PostCode
  //FSP Common Module(0x800) | Api Entry(0x00)
  PostCode (0x800);

  FspmUpdDataPtr = NULL;

  ///
  /// Install Pre Memory PPIs
  ///
  Status = PeiServicesInstallPpi (&mPreMemPpiList[0]);
  ASSERT_EFI_ERROR (Status);

  //
  // Get the UPD pointer.
  //
  FspmUpdDataPtr = (FSPM_UPD *) GetFspMemoryInitUpdDataPointer ();
  SetFspSiliconInitUpdDataPointer ((void *)NULL);

  DEBUG_CODE_BEGIN ();
    UINT32  Index;
    DEBUG ((DEBUG_INFO, "Dumping FSPM_UPD - Size: 0x%8X", sizeof(FSPM_UPD)));
    for (Index = 0; Index < sizeof (FSPM_UPD); ++Index) {
      if (Index % 0x10 == 0) {
        DEBUG ((DEBUG_INFO, "\n0x%8X:", Index));
      }
      DEBUG ((DEBUG_INFO, " 0x%02X", *(((UINT8 *)FspmUpdDataPtr) + Index)));
    }
    DEBUG ((DEBUG_INFO, "\n"));
  DEBUG_CODE_END ();

  //
  // Get the Boot Mode
  //
  BootMode = FspmUpdDataPtr->FspmArchUpd.BootMode;
  PeiServicesSetBootMode (BootMode);
  Status = PeiServicesInstallPpi (&mPpiBootMode);

  Status = SiCreatePreMemConfigBlocks (&SiPreMemPolicyPpi);
  FspUpdatePeiPchPolicyPreMem (SiPreMemPolicyPpi, FspmUpdDataPtr);

  FspUpdatePeiCpuPolicyPreMem (SiPreMemPolicyPpi, FspmUpdDataPtr);
  FspUpdatePeiSecurityPolicyPreMem (SiPreMemPolicyPpi, FspmUpdDataPtr);//Security Policy also needs to be updated before CpuInstallPolicyPpi
  FspUpdatePeiMePolicyPreMem (SiPreMemPolicyPpi, FspmUpdDataPtr);
  FspUpdatePeiSaPolicyPreMem (SiPreMemPolicyPpi, FspmUpdDataPtr);
  FspUpdatePeiSiPolicyPreMem (SiPreMemPolicyPpi, FspmUpdDataPtr);

  Status = SiPreMemInstallPolicyPpi(SiPreMemPolicyPpi);

  ///
  /// Now that all of the pre-permament memory activities have
  /// been taken care of, post a call-back for the permament-memory
  /// resident services, such as HOB construction.
  /// PEI Core will switch stack after this PEIM exit.  After that the MTRR
  /// can be set.
  ///
  Status = PeiServicesNotifyPpi (&mMemoryDiscoveredNotifyList);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "FspInitPreMemEntryPoint done\n"));
  return Status;
}
