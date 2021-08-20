/** @file
  Cpu S3 library running on S3 resume paths

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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

#include <Private/CpuPrivateData.h>
#include <Private/Library/CpuS3Lib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PostCodeLib.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>

#ifdef FSP_FLAG
#include <Library/FspCommonLib.h>
#include <Library/MemoryAllocationLib.h>
#include <FspsUpd.h>
#endif

GLOBAL_REMOVE_IF_UNREFERENCED CPU_TEST_CONFIG              *mCpuTestConfigBlock             = NULL;

extern EFI_GUID gSmramCpuDataHeaderGuid;
extern EFI_GUID gPeiAcpiCpuDataGuid;

/**
  This function handles CPU S3 resume task at the end of PEI

  @param[in] PeiServices   - Pointer to PEI Services Table.
  @param[in] NotifyDesc    - Pointer to the descriptor for the Notification event that
                             caused this function to execute.
  @param[in] Ppi           - Pointer to the PPI data associated with this function.

  @retval EFI_STATUS       - Always return EFI_SUCCESS
**/
STATIC
EFI_STATUS
CpuS3ResumeAtEndOfPei (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
  IN VOID                      *Ppi
  );

STATIC EFI_PEI_NOTIFY_DESCRIPTOR mCpuS3ResumeNotifyDesc = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiEndOfPeiSignalPpiGuid,
  CpuS3ResumeAtEndOfPei
};

#ifndef FSP_FLAG
/**
  This routine is used to search SMRAM and get SmramCpuData point.

  @param[in] PeiServices  - PEI services global pointer
  @param[in] SmmAccessPpi - SmmAccess PPI instance

  @retval SmramCpuData - The pointer of CPU information in SMRAM.
  @retval NULL         - Unable to find the CPU information.
**/

STATIC
SMRAM_CPU_DATA *
GetSmmCpuData (
  IN CONST EFI_PEI_SERVICES   **PeiServices,
  IN PEI_SMM_ACCESS_PPI       *SmmAccessPpi
  )
{
  EFI_SMRAM_DESCRIPTOR *SmramRanges;
  UINTN                SmramRangeCount;
  UINTN                Size;
  EFI_STATUS           Status;
  UINT32               Address;
  SMRAM_CPU_DATA       *SmramCpuData;

  ///
  /// Get all SMRAM range
  ///
  Size    = 0;
  Status  = SmmAccessPpi->GetCapabilities ((EFI_PEI_SERVICES **) PeiServices, SmmAccessPpi, &Size, NULL);
  ASSERT (Status == EFI_BUFFER_TOO_SMALL);

  Status = PeiServicesAllocatePool (
             Size,
             (VOID **) &SmramRanges
             );
  ASSERT_EFI_ERROR (Status);

  Status = SmmAccessPpi->GetCapabilities ((EFI_PEI_SERVICES **) PeiServices, SmmAccessPpi, &Size, SmramRanges);
  ASSERT_EFI_ERROR (Status);

  Size /= sizeof (*SmramRanges);
  SmramRangeCount = Size;

  ///
  ///@bug We assume TSEG is the last range of SMRAM in SmramRanges
  ///
  SmramRanges += SmramRangeCount - 1;

  DEBUG ((DEBUG_INFO, "TsegBase - %x\n", SmramRanges->CpuStart));
  DEBUG ((DEBUG_INFO, "TsegTop  - %x\n", SmramRanges->CpuStart + SmramRanges->PhysicalSize));

  ///
  /// Search SMRAM on page alignment for the SMMNVS signature
  ///
  for (Address = (UINT32) (SmramRanges->CpuStart + SmramRanges->PhysicalSize - EFI_PAGE_SIZE);
       Address >= (UINT32) SmramRanges->CpuStart;
       Address -= EFI_PAGE_SIZE
       ) {
    SmramCpuData = (SMRAM_CPU_DATA *) (UINTN) Address;
    if (CompareGuid (&SmramCpuData->HeaderGuid, &gSmramCpuDataHeaderGuid)) {
      return SmramCpuData;
    }
  }

  ASSERT (FALSE);

  return NULL;
}

/**
  This routine is restore the CPU information from SMRAM to original reserved memory region.

  @param[in] PeiServices  - PEI services global pointer

  @retval AcpiCpuData - The pointer of CPU information in reserved memory.
  @retval NULL        - Unable to find the CPU information.
**/
ACPI_CPU_DATA *
RestoreSmramCpuData (
  IN CONST EFI_PEI_SERVICES    **PeiServices
  )
{
  PEI_SMM_ACCESS_PPI     *SmmAccessPpi;
  SMRAM_CPU_DATA         *SmramCpuData;
  EFI_STATUS             Status;
  ACPI_CPU_DATA          *AcpiCpuData;
  CPU_PRIVATE_DATA       *CpuPrivateData;
  IA32_DESCRIPTOR        *Idtr;
  IA32_DESCRIPTOR        *Gdtr;
  UINTN                  Index;

  Status = PeiServicesLocatePpi (
             &gPeiSmmAccessPpiGuid,
             0,
             NULL,
             (VOID **) &SmmAccessPpi
             );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Open all SMM regions
  ///
  Index = 0;
  do {
    Status = SmmAccessPpi->Open ((EFI_PEI_SERVICES **) PeiServices, SmmAccessPpi, Index);
    Index++;
  } while (!EFI_ERROR (Status));

  SmramCpuData = GetSmmCpuData ((CONST EFI_PEI_SERVICES **) PeiServices, SmmAccessPpi);
  if (SmramCpuData == NULL) {
    ASSERT (FALSE);
    return NULL;
  }
  DEBUG ((DEBUG_INFO, "CpuS3 SmramCpuData                         - 0x%x \n", SmramCpuData));
  DEBUG ((DEBUG_INFO, "SmramCpuData->GdtrProfileSize              - %x\n", SmramCpuData->GdtrProfileSize));
  DEBUG ((DEBUG_INFO, "SmramCpuData->GdtSize                      - %x\n", SmramCpuData->GdtSize));
  DEBUG ((DEBUG_INFO, "SmramCpuData->IdtrProfileSize              - %x\n", SmramCpuData->IdtrProfileSize));
  DEBUG ((DEBUG_INFO, "SmramCpuData->IdtSize                      - %x\n", SmramCpuData->IdtSize));
  DEBUG ((DEBUG_INFO, "SmramCpuData->CpuPrivateDataSize           - %x\n", SmramCpuData->CpuPrivateDataSize));
  DEBUG ((DEBUG_INFO, "SmramCpuData->S3BspMtrrTableSize           - %x\n", SmramCpuData->S3BspMtrrTableSize));
  DEBUG ((DEBUG_INFO, "SmramCpuData->GdtrProfileOffset            - %x\n", SmramCpuData->GdtrProfileOffset));
  DEBUG ((DEBUG_INFO, "SmramCpuData->GdtOffset                    - %x\n", SmramCpuData->GdtOffset));
  DEBUG ((DEBUG_INFO, "SmramCpuData->IdtrProfileOffset            - %x\n", SmramCpuData->IdtrProfileOffset));
  DEBUG ((DEBUG_INFO, "SmramCpuData->IdtOffset                    - %x\n", SmramCpuData->IdtOffset));
  DEBUG ((DEBUG_INFO, "SmramCpuData->CpuPrivateDataOffset         - %x\n", SmramCpuData->CpuPrivateDataOffset));
  DEBUG ((DEBUG_INFO, "SmramCpuData->S3BspMtrrTableOffset         - %x\n", SmramCpuData->S3BspMtrrTableOffset));

  ///
  /// Start restore data to NVS
  ///
  AcpiCpuData = (ACPI_CPU_DATA *) (UINTN) SmramCpuData->AcpiCpuPointer;
  CopyMem (AcpiCpuData, &SmramCpuData->AcpiCpuData, sizeof (ACPI_CPU_DATA));

  CopyMem (
    (VOID *) (UINTN) AcpiCpuData->GdtrProfile,
    (UINT8 *) SmramCpuData + SmramCpuData->GdtrProfileOffset,
    SmramCpuData->GdtrProfileSize
    );
  Gdtr = (IA32_DESCRIPTOR *) (UINTN) AcpiCpuData->GdtrProfile;
  CopyMem (
    (VOID *) (UINTN) Gdtr->Base,
    (UINT8 *) SmramCpuData + SmramCpuData->GdtOffset,
    SmramCpuData->GdtSize
    );
  CopyMem (
    (VOID *) (UINTN) AcpiCpuData->IdtrProfile,
    (UINT8 *) SmramCpuData + SmramCpuData->IdtrProfileOffset,
    SmramCpuData->IdtrProfileSize
    );
  Idtr = (IA32_DESCRIPTOR *) (UINTN) AcpiCpuData->IdtrProfile;
  CopyMem (
    (VOID *) (UINTN) Idtr->Base,
    (UINT8 *) SmramCpuData + SmramCpuData->IdtOffset,
    SmramCpuData->IdtSize
    );
  CopyMem (
    (VOID *) (UINTN) AcpiCpuData->CpuPrivateData,
    (UINT8 *) SmramCpuData + SmramCpuData->CpuPrivateDataOffset,
    SmramCpuData->CpuPrivateDataSize
    );
  CpuPrivateData = (CPU_PRIVATE_DATA *) (UINTN) AcpiCpuData->CpuPrivateData;
  CopyMem (
    (VOID *) (UINTN) CpuPrivateData->S3BspMtrrTablePointer,
    (UINT8 *) SmramCpuData + SmramCpuData->S3BspMtrrTableOffset,
    SmramCpuData->S3BspMtrrTableSize
    );
  ///
  /// Close all SMM regions
  ///
  Index = 0;
  do {
    Status = SmmAccessPpi->Close ((EFI_PEI_SERVICES **) PeiServices, SmmAccessPpi, Index);
    Index++;
  } while (!EFI_ERROR (Status));

  return AcpiCpuData;
}
#endif

/**
  This routine is restore the CPU information from UPD for FSP. This similarly simulates the non-FSP SMM RAM data.

  @param[in] PeiServices  - PEI services global pointer

  @retval AcpiCpuData - The pointer of CPU information in reserved memory.
  @retval NULL        - Unable to find the CPU information.
**/
#ifdef FSP_FLAG
ACPI_CPU_DATA *
RestoreFspCpuData (
  IN CONST EFI_PEI_SERVICES    **PeiServices
  )
{
  ACPI_CPU_DATA           *AcpiCpuData;
  IA32_DESCRIPTOR         BspGdtr;
  IA32_DESCRIPTOR         BspIdtr;
  CPU_PRIVATE_DATA        *CpuPrivateData;
  FSPS_UPD                *FspsUpd = (FSPS_UPD *)GetFspSiliconInitUpdDataPointer();
  FSP_S_CONFIG            *FspsConfigUpd = &FspsUpd->FspsConfig;
  MTRR_VALUES             *MtrrValues = (MTRR_VALUES *) FspsConfigUpd->CpuS3ResumeMtrrData;
  UINT16                  MtrrDataSize = (UINT16)FspsConfigUpd->CpuS3ResumeMtrrDataSize;
  FSP_S_TEST_CONFIG       *FspsTestConfigUpd = &FspsUpd->FspsTestConfig;
  UINT8                   *CpuS3ResumeData = (UINT8 *) FspsTestConfigUpd->CpuS3ResumeData;
  UINT16                  CpuS3ResumeDataSize = (UINT16) FspsTestConfigUpd->CpuS3ResumeDataSize;

  ///
  /// Start restore data to NVS
  ///
  AcpiCpuData = (ACPI_CPU_DATA*) AllocatePool(sizeof(ACPI_CPU_DATA));
  ASSERT (AcpiCpuData != NULL);
  if (AcpiCpuData == NULL) {
    return NULL;
  }

  AcpiCpuData->GdtrProfile = (EFI_PHYSICAL_ADDRESS)(UINTN) AllocatePool(sizeof(IA32_DESCRIPTOR));
  AcpiCpuData->IdtrProfile = (EFI_PHYSICAL_ADDRESS)(UINTN) AllocatePool(sizeof(IA32_DESCRIPTOR));
  if (AcpiCpuData->GdtrProfile == 0 || AcpiCpuData->IdtrProfile == 0) {
    DEBUG ((DEBUG_ERROR, "Fail to allocate GDTR or IDTR Profile\n"));
    ASSERT (FALSE);
    return NULL;
  }

  //
  // For FSP APs, uses BSP GDT and IDT from Boot Loader.
  //

  AsmReadGdtr (&BspGdtr);
  AsmReadIdtr (&BspIdtr);

  CopyMem (
         (VOID *)(UINTN)AcpiCpuData->GdtrProfile,
         &BspGdtr,
         sizeof(IA32_DESCRIPTOR)
         );
  CopyMem (
         (VOID *)(UINTN)AcpiCpuData->IdtrProfile,
         &BspIdtr,
         sizeof(IA32_DESCRIPTOR)
         );

  AcpiCpuData->CpuPrivateData = (EFI_PHYSICAL_ADDRESS)(UINTN) AllocateZeroPool(sizeof(CPU_PRIVATE_DATA));
  CpuPrivateData = (CPU_PRIVATE_DATA *) (UINTN) AcpiCpuData->CpuPrivateData;

  //
  // Copy CPU_PRIVATE_DATA from UPD.
  //
  if (CpuS3ResumeDataSize == sizeof(CPU_PRIVATE_DATA)) {
    CopyMem ((VOID*) CpuPrivateData, CpuS3ResumeData, CpuS3ResumeDataSize);
  }

  //
  // Allocate memory for UPD MTRR Data plus memory for NULL terminator. NULL terminator added
  //  through zeroing memory when allocation.
  //

  CpuPrivateData->S3BspMtrrTablePointer = (UINT32) AllocateZeroPool(MtrrDataSize + sizeof(MTRR_VALUES)); //Add Null terminator
  if (CpuPrivateData->S3BspMtrrTablePointer == 0) {
    DEBUG ((DEBUG_ERROR, "Fail to allocate ProfileS3BspMtrrTablePointer\n"));
    ASSERT (CpuPrivateData->S3BspMtrrTablePointer != 0);
    return NULL;
  }

  //
  // Copy BSP MTRR table from UPD.
  //
  CopyMem ((VOID*) CpuPrivateData->S3BspMtrrTablePointer, MtrrValues, MtrrDataSize);

  return AcpiCpuData;
}
#endif


/**
  Restore Processor Trace Feature during S3 resume.

  @param[in] Buffer    Pointer to the array of UINT64 memory addresses to reprogram.
**/
VOID
MpSafeRestoreProcTrace (
  IN VOID *Buffer
  )
{
  UINT64                                    MsrValue;
  UINT32                                    MemRegionSize;
  UINT64                                    *SavedMemRegionAddresses;
  UINT64                                    MsrBaseAddress;
  CPUID_INTEL_PROCESSOR_TRACE_MAIN_LEAF_ECX Ecx;
  BOOLEAN                                   IsTopaSupported;
  BOOLEAN                                   IsSingleRangeSupported;
  BOOLEAN                                   IsBspInt;
  UINT32                                    ApicId;
  UINTN                                     Index;

  IsBspInt     = IsBsp ();
  SavedMemRegionAddresses = ((UINT64 *) Buffer);

  if (IsBspInt) {
    DEBUG ((DEBUG_INFO, "Restore Processor Trace\n"));
    for (Index = 0; Index < MAX_PROCESSOR_THREADS; Index++) {
      DEBUG ((DEBUG_INFO, "ProcTrace: SavedAddress apic ID 0x%X passed in: 0x%X \n", Index, SavedMemRegionAddresses[Index]));
    }
  }

  ///
  /// Detect which processor trace output schemes are supported.
  ///
  AsmCpuidEx (CPUID_INTEL_PROCESSOR_TRACE, CPUID_INTEL_PROCESSOR_TRACE_MAIN_LEAF, NULL, NULL, &Ecx.Uint32, NULL);
  IsTopaSupported = (Ecx.Bits.RTIT == 1) ? TRUE : FALSE;
  IsSingleRangeSupported = (Ecx.Bits.SingleRangeOutput == 1) ? TRUE : FALSE;

  if (!(IsTopaSupported || IsSingleRangeSupported)) {
    return;
  }
  ///
  /// Refer to PROC_TRACE_MEM_SIZE Table for Size Encoding
  ///
  MemRegionSize = (UINT32) (1 << (mCpuTestConfigBlock->ProcTraceMemSize + 12));
  if (IsBspInt) {
    DEBUG ((DEBUG_INFO, "ProcTrace: MemSize requested: 0x%X \n", MemRegionSize));
  }

  ApicId = GetCpuApicId ();

  //
  // Only support MAX_PROCESSOR_THREADS threads so far
  //
  ASSERT (ApicId < MAX_PROCESSOR_THREADS);
  if (ApicId >= MAX_PROCESSOR_THREADS) {
    return;
  }
  MsrBaseAddress = SavedMemRegionAddresses[ApicId];
  if (MsrBaseAddress == 0) {
    if (IsBspInt) {
      DEBUG ((DEBUG_ERROR, "ProcTrace: Unable to restore memory address for thread with APIC ID: 0x%X \n", ApicId));
    }
    return;
  }

  //
  // Clear MSR_IA32_RTIT_CTL[0] and IA32_RTIT_STS only if MSR_IA32_RTIT_CTL[0]==1b
  //
  MsrValue = AsmReadMsr64 (MSR_IA32_RTIT_CTL);
  if (MsrValue & B_RTIT_CTL_TRACE_ENABLE) {
    ///
    /// Clear bit 0 in MSR IA32_RTIT_CTL (570)
    ///
    MsrValue &= (UINT64) ~B_RTIT_CTL_TRACE_ENABLE;
    AsmWriteMsr64 (MSR_IA32_RTIT_CTL, MsrValue);

    ///
    /// Clear MSR IA32_RTIT_STS (571h) to all zeros
    ///
    MsrValue = AsmReadMsr64 (MSR_IA32_RTIT_STATUS);
    MsrValue &= 0x0;
    AsmWriteMsr64 (MSR_IA32_RTIT_STATUS, MsrValue);
  }

  ///
  /// Check Processor Trace output scheme: Single Range output or ToPA table
  ///
  //
  //  Single Range output scheme
  //
  if (IsSingleRangeSupported && (mCpuTestConfigBlock->ProcTraceOutputScheme == 0)) {
    if (IsBspInt) {
      DEBUG ((DEBUG_INFO, "ProcTrace: Enabling Single Range Output scheme \n"));
    }

    //
    // Clear MSR IA32_RTIT_CTL (0x570) ToPA (Bit 8)
    //
    MsrValue = AsmReadMsr64 (MSR_IA32_RTIT_CTL);
    MsrValue &= (UINT64) ~BIT8;
    AsmWriteMsr64 (MSR_IA32_RTIT_CTL, MsrValue);

    //
    // Program MSR IA32_RTIT_OUTPUT_BASE (0x560) bits[47:12] with the allocated Memory Region
    //
    MsrValue = MsrBaseAddress;
    AsmWriteMsr64 (MSR_IA32_RTIT_OUTPUT_BASE, MsrValue);

    //
    // Program the Mask bits for the Memory Region to MSR IA32_RTIT_OUTPUT_MASK_PTRS (561h)
    //
    MsrValue = (UINT64) MemRegionSize - 1;
    AsmWriteMsr64 (MSR_IA32_RTIT_OUTPUT_MASK_PTRS, MsrValue);
  }

  //
  //  ToPA(Table of physical address) scheme
  //
  if (IsTopaSupported && (mCpuTestConfigBlock->ProcTraceOutputScheme == 1)) {

    //
    // Program the MSR IA32_RTIT_OUTPUT_BASE (0x560) bits[47:12] with ToPA base
    //
    MsrValue = MsrBaseAddress;
    AsmWriteMsr64 (MSR_IA32_RTIT_OUTPUT_BASE, MsrValue);
    //
    // Set the MSR IA32_RTIT_OUTPUT_MASK (0x561) bits[63:7] to 0
    //
    AsmWriteMsr64 (MSR_IA32_RTIT_OUTPUT_MASK_PTRS, 0x7f);
    //
    // Enable ToPA output scheme by enabling MSR IA32_RTIT_CTL (0x570) ToPA (Bit 8)
    //
    MsrValue = AsmReadMsr64 (MSR_IA32_RTIT_CTL);
    MsrValue |= BIT8;
    AsmWriteMsr64 (MSR_IA32_RTIT_CTL, MsrValue);
  }

  ///
  /// Enable the Processor Trace feature from MSR IA32_RTIT_CTL (570h)
  ///
  MsrValue = AsmReadMsr64 (MSR_IA32_RTIT_CTL);
  MsrValue |= (UINT64) BIT0 + BIT2 + BIT3 + BIT13;
  if (!(mCpuTestConfigBlock->ProcTraceEnable)) {
    MsrValue &= (UINT64) ~BIT0;
  }
  AsmWriteMsr64 (MSR_IA32_RTIT_CTL, MsrValue);
}


/**
  Cpu initialization called during S3 resume to take care
  of CPU related activities in PEI phase.

  @param[in] PeiServices   - Indirect reference to the PEI Services Table.
  @param[in] SiPolicyPpi   - The SI Policy PPI instance

  @retval EFI_SUCCESS   - Multiple processors are intialized successfully.
  @retval EFI_NOT_FOUND - Unable to find AcpiCpuData.
**/
EFI_STATUS
S3InitializeCpu (
  IN CONST EFI_PEI_SERVICES    **PeiServices,
  IN       SI_POLICY_PPI       *SiPolicyPpi
  )
{
  EFI_STATUS                                  Status;
  ACPI_CPU_DATA                               *AcpiCpuData;
  CPU_PRIVATE_DATA                            *CpuPrivateData;
  UINTN                                       VariableMtrrNumber;
  VOID                                        *Hob;
  EFI_BOOT_MODE                               BootMode;
  EFI_PEI_MP_SERVICES_PPI                     *MpServicesPpi;
  SI_PREMEM_POLICY_PPI                        *SiPreMemPolicyPpi;
  UINT64                                      *MtrrValues;
  MSR_IA32_MTRRCAP_REGISTER                   Msr;
  CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS_EBX Ebx;

  Status = PeiServicesGetBootMode (&BootMode);
  DEBUG ((DEBUG_INFO, "CPU: BootMode = %X\n", BootMode));
  if ((Status == EFI_SUCCESS) && (BootMode != BOOT_ON_S3_RESUME)) {
    DEBUG ((DEBUG_INFO,"CPU: Normal Boot\n"));
    return EFI_SUCCESS;
  }

  DEBUG((DEBUG_INFO, "S3InitializeCpu Start \n"));
  PostCode (0xC50);

  ///
  /// Locate CpuMpCpu MpService Ppi
  ///
  Status = PeiServicesLocatePpi (
             &gEfiPeiMpServicesPpiGuid,
             0,
             NULL,
             (VOID **) &MpServicesPpi);
  ASSERT_EFI_ERROR (Status);
  DEBUG ((DEBUG_INFO, "CpuS3: Locate MpServicesPpi Status = %r\n", Status));

  Status = PeiServicesLocatePpi (
                &gSiPreMemPolicyPpiGuid,
                0,
                NULL,
                (VOID **) &SiPreMemPolicyPpi
                );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Restore ACPI Nvs data from SMRAM
  ///
#ifndef FSP_FLAG
  AcpiCpuData = RestoreSmramCpuData ((CONST EFI_PEI_SERVICES **) PeiServices);
#else
  AcpiCpuData = RestoreFspCpuData ((CONST EFI_PEI_SERVICES **) PeiServices);
#endif
  DEBUG ((DEBUG_INFO, "CpuS3 RestoreCpu Data pointer - 0x%x \n", AcpiCpuData));
  if (AcpiCpuData == NULL) {
    return EFI_NOT_FOUND;
  }

  AcpiCpuData->S3BootPath = TRUE;
  CpuPrivateData = (CPU_PRIVATE_DATA *) (UINTN) AcpiCpuData->CpuPrivateData;

  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_MTRRCAP);
  VariableMtrrNumber  = Msr.Bits.VCNT * 2;
  Status = PeiServicesAllocatePool (
             (FixedMtrrNumber + MtrrDefTypeNumber + VariableMtrrNumber) * sizeof (UINT64),
             (VOID **) &MtrrValues
             );
  ASSERT_EFI_ERROR (Status);
  ReadMtrrRegisters (MtrrValues);

  DEBUG((DEBUG_INFO, "MpRendezvousProcedure Start \n"));
  PostCode (0xC55);

  ///
  /// Sync up all types of MTRR values for all APs
  ///
  MpServicesPpi->StartupAllAPs (
                   (CONST EFI_PEI_SERVICES **)PeiServices,
                   MpServicesPpi,
                   (EFI_AP_PROCEDURE) MpMtrrSynchUp,
                   FALSE,
                   0,
                   (VOID *) MtrrValues
                   );

  ///
  /// Get Config Block for Processor Trace
  ///
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuTestConfigGuid, (VOID *) &mCpuTestConfigBlock);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Initialize Processor Trace from saved settings for all processors.
  /// Check if Processor Trace is supported and ProcTraceMemorySize option is enabled (0xFF means disable by user)
  ///
  AsmCpuidEx (CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS, 0, NULL, &Ebx.Uint32, NULL, NULL);
  if ((Ebx.Bits.IntelProcessorTrace == 1) && (mCpuTestConfigBlock->ProcTraceMemSize < EnumProcTraceMemDisable)) {
    MpSafeRestoreProcTrace ((VOID *) CpuPrivateData->ProcessorTraceAddress);
    MpServicesPpi->StartupAllAPs (
                     (CONST EFI_PEI_SERVICES **)PeiServices,
                     MpServicesPpi,
                     (EFI_AP_PROCEDURE) MpSafeRestoreProcTrace,
                     FALSE,
                     0,
                     (VOID *) CpuPrivateData->ProcessorTraceAddress
                     );
  }

  DEBUG((DEBUG_INFO, "MpRendezvousProcedure Done \n"));
  PostCode (0xC56);

  ///
  /// Save acpi cpu data into one hob, it will be used by a callback when End of Pei Signal installed.
  ///
  Hob = BuildGuidDataHob (
          &gPeiAcpiCpuDataGuid,
          (VOID *) (UINTN) AcpiCpuData,
          (UINTN) sizeof (ACPI_CPU_DATA)
          );
  ASSERT (Hob != NULL);
  DEBUG ((DEBUG_INFO, "CPU S3: Register notification to be trigerred at End of Pei event\n"));
  Status = PeiServicesNotifyPpi (&mCpuS3ResumeNotifyDesc);
  ASSERT_EFI_ERROR (Status);

  DEBUG((DEBUG_INFO, "S3InitializeCpu Done \n"));
  PostCode (0xC69);

  return EFI_SUCCESS;
}

/**
  This function handles CPU S3 resume task at the end of PEI

  @param[in] PeiServices   - Pointer to PEI Services Table.
  @param[in] NotifyDesc    - Pointer to the descriptor for the Notification event that
                             caused this function to execute.
  @param[in] Ppi           - Pointer to the PPI data associated with this function.

  @retval EFI_STATUS       - Always return EFI_SUCCESS
**/
STATIC
EFI_STATUS
CpuS3ResumeAtEndOfPei (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
  IN VOID                      *Ppi
  )
{
  EFI_STATUS              Status;
  ACPI_CPU_DATA           *AcpiCpuData;
  CPU_PRIVATE_DATA        *CpuPrivateData;
  UINT32                  S3BspMtrrTablePointer;
  EFI_PEI_MP_SERVICES_PPI *MpServicesPpi;
  VOID                    *Hob;

  DEBUG ((DEBUG_INFO, "Cpu S3 callback Entry\n"));

  ///
  /// Find the saved acpi cpu data from HOB.
  ///
  AcpiCpuData = NULL;
  Hob = GetFirstGuidHob (&gPeiAcpiCpuDataGuid);
  if (Hob != NULL) {
    AcpiCpuData = (ACPI_CPU_DATA *) ((UINTN) Hob + sizeof (EFI_HOB_GUID_TYPE));
    ASSERT (AcpiCpuData != NULL);
    if (AcpiCpuData == NULL) {
      return EFI_UNSUPPORTED;
    }
  } else {
    return EFI_UNSUPPORTED;
  }

  ///
  /// Locate CpuMpCpu MpService Ppi
  ///
  Status = PeiServicesLocatePpi (
             &gEfiPeiMpServicesPpiGuid,
             0,
             NULL,
             (VOID **) &MpServicesPpi);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Set MTRR to the final values
  /// Do not do it too early so as to avoid performance penalty
  ///
  CpuPrivateData = (CPU_PRIVATE_DATA *) (UINTN) AcpiCpuData->CpuPrivateData;
  S3BspMtrrTablePointer = (UINT32) CpuPrivateData->S3BspMtrrTablePointer;

  DEBUG ((DEBUG_INFO, "Print MTRR settings to restore:\n"));
  DEBUG_CODE (
    ShowMtrrRegisters ((MTRR_VALUES *) S3BspMtrrTablePointer);
    );

  SetMtrrRegisters ((VOID *) S3BspMtrrTablePointer);
  ///
  /// Restore AP Variable MTRRs
  ///
  MpServicesPpi->StartupAllAPs (
                   (CONST EFI_PEI_SERVICES **)PeiServices,
                   MpServicesPpi,
                   (EFI_AP_PROCEDURE) SetMtrrRegisters,
                   FALSE,
                   0,
                   (VOID *) S3BspMtrrTablePointer
                   );

  SetMtrrRegisters ((MTRR_VALUES *) S3BspMtrrTablePointer);

  MicroSecondDelay (1 * STALL_ONE_MILLI_SECOND); ///< 1ms

  return EFI_SUCCESS;
}
