/** @file
  Synchronization of MTRRs on S3 boot path.

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

#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <Private/Library/CpuS3Lib.h>

UINTN
MpMtrrSynchUpEntry (
  VOID
  );

VOID
MpMtrrSynchUpExit (
  UINTN Cr4
  );

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mFixedMtrrIndex[] = {
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
  MSR_IA32_MTRR_FIX4K_F8000,
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mMtrrDefType[] = { MSR_IA32_MTRR_DEF_TYPE };

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mVariableMtrrIndex[] = {
  MSR_IA32_MTRR_PHYSBASE0,
  MSR_IA32_MTRR_PHYSBASE0 + 1,
  MSR_IA32_MTRR_PHYSBASE0 + 2,
  MSR_IA32_MTRR_PHYSBASE0 + 3,
  MSR_IA32_MTRR_PHYSBASE0 + 4,
  MSR_IA32_MTRR_PHYSBASE0 + 5,
  MSR_IA32_MTRR_PHYSBASE0 + 6,
  MSR_IA32_MTRR_PHYSBASE0 + 7,
  MSR_IA32_MTRR_PHYSBASE0 + 8,
  MSR_IA32_MTRR_PHYSBASE0 + 9,
  MSR_IA32_MTRR_PHYSBASE0 + 10,
  MSR_IA32_MTRR_PHYSBASE0 + 11,
  MSR_IA32_MTRR_PHYSBASE0 + 12,
  MSR_IA32_MTRR_PHYSBASE0 + 13,
  MSR_IA32_MTRR_PHYSBASE0 + 14,
  MSR_IA32_MTRR_PHYSBASE0 + 15,
  MSR_IA32_MTRR_PHYSBASE0 + 16,
  MSR_IA32_MTRR_PHYSBASE0 + 17,
  MSR_IA32_MTRR_PHYSBASE0 + 18,
  MSR_IA32_MTRR_PHYSBASE0 + 19,
  ///
  /// CACHE_VARIABLE_MTRR_END,
  ///
};

GLOBAL_REMOVE_IF_UNREFERENCED UINTN FixedMtrrNumber   = sizeof (mFixedMtrrIndex) / sizeof (UINT16);
GLOBAL_REMOVE_IF_UNREFERENCED UINTN MtrrDefTypeNumber = sizeof (mMtrrDefType) / sizeof (UINT16);

/**
  Save the MTRR registers to global variables

  @param[in] MtrrValues    - pointer to the buffer which stores MTRR settings
**/
VOID
ReadMtrrRegisters (
  IN UINT64           *MtrrValues
  )
{
  UINT32                    Index;
  MSR_IA32_MTRRCAP_REGISTER Msr;

  ///
  /// Read all Mtrrs
  ///
  for (Index = 0; Index < FixedMtrrNumber; Index++) {
    *MtrrValues = AsmReadMsr64 (mFixedMtrrIndex[Index]);
    MtrrValues++;
  }

  for (Index = 0; Index < MtrrDefTypeNumber; Index++) {
    *MtrrValues = AsmReadMsr64 (mMtrrDefType[Index]);
    MtrrValues++;
  }

  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_MTRRCAP);

  //
  // Handle error condition by asserting in debug case, and limiting the value otherwise.
  //
  ASSERT ((Msr.Bits.VCNT * 2) <= (sizeof(mVariableMtrrIndex) / sizeof(UINT16)));
  if ((Msr.Bits.VCNT * 2) > (sizeof(mVariableMtrrIndex) / sizeof(UINT16))) {
    Msr.Bits.VCNT = (sizeof(mVariableMtrrIndex) / sizeof(UINT16)) / 2;
  }

  for (Index = 0; Index < Msr.Bits.VCNT * 2; Index++) {
    *MtrrValues = AsmReadMsr64 (mVariableMtrrIndex[Index]);
    MtrrValues++;
  }
  return;
}

/**
  Synch up the MTRR values for all processors

  @param[in] Buffer    - pointer to the buffer which stores MTRR settings
**/
VOID
MpMtrrSynchUp (
  IN VOID  *Buffer
  )
{
  UINT32                    Index;
  MSR_IA32_MTRRCAP_REGISTER Msr;
  UINTN                     Cr4;
  UINT64                    *FixedMtrr;
  UINT64                    *MtrrDefType;
  UINT64                    *VariableMtrr;
  UINT64                    ValidMtrrAddressMask;
  EFI_CPUID_REGISTER        FeatureInfo;
  EFI_CPUID_REGISTER        FunctionInfo;
  UINT8                     PhysicalAddressBits;
  UINT64                    *MtrrValues;
  BOOLEAN                   IsBspVal;

  IsBspVal = IsBsp();
  if (IsBspVal) {
    DEBUG ((DEBUG_INFO, "CpuS3: Synch up all types of MTRR values.\n"));
  }

  ///
  /// Init XMM support on all APs
  ///
  if (!IsBspVal) {
    XmmInit ();
  }

  ProgramXApic (IsBspVal);

  MtrrValues = (UINT64 *) Buffer;
  ///
  /// Get physical CPU MTRR width in case of difference from BSP
  ///
  AsmCpuid (
          CPUID_EXTENDED_FUNCTION,
          &FunctionInfo.RegEax,
          &FunctionInfo.RegEbx,
          &FunctionInfo.RegEcx,
          &FunctionInfo.RegEdx
          );
  PhysicalAddressBits = 36;
  if (FunctionInfo.RegEax >= CPUID_VIR_PHY_ADDRESS_SIZE) {
    AsmCpuid (
            CPUID_VIR_PHY_ADDRESS_SIZE,
            &FeatureInfo.RegEax,
            &FeatureInfo.RegEbx,
            &FeatureInfo.RegEcx,
            &FeatureInfo.RegEdx
            );
    PhysicalAddressBits = (UINT8) FeatureInfo.RegEax;
  }

  ValidMtrrAddressMask  = (LShiftU64 (1, PhysicalAddressBits) - 1) & 0xfffffffffffff000ULL;

  FixedMtrr             = MtrrValues;
  MtrrDefType           = MtrrValues + FixedMtrrNumber;
  VariableMtrr          = MtrrValues + FixedMtrrNumber + MtrrDefTypeNumber;

  ///
  /// ASM code to setup processor register before synching up the MTRRs
  ///
  Cr4 = MpMtrrSynchUpEntry ();

  ///
  /// Disable Fixed Mtrrs
  ///
  AsmWriteMsr64 (MSR_IA32_MTRR_DEF_TYPE, MtrrDefType[0] & 0xFFFFF7FF);

  ///
  /// Update Fixed Mtrrs
  ///
  for (Index = 0; Index < FixedMtrrNumber; Index++) {
    AsmWriteMsr64 (mFixedMtrrIndex[Index], FixedMtrr[Index]);
  }
  ///
  /// Synchup Base Variable Mtrr
  ///
  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_MTRRCAP);

  //
  // Handle error condition by asserting in debug case, and limiting the value otherwise.
  //
  ASSERT ((Msr.Bits.VCNT * 2) <= (sizeof(mVariableMtrrIndex) / sizeof(UINT16)));
  if ((Msr.Bits.VCNT * 2) > (sizeof(mVariableMtrrIndex) / sizeof(UINT16))) {
    Msr.Bits.VCNT = (sizeof(mVariableMtrrIndex) / sizeof(UINT16)) / 2;
  }

  for (Index = 0; Index < Msr.Bits.VCNT * 2; Index++) {
    AsmWriteMsr64 (
            mVariableMtrrIndex[Index],
            (VariableMtrr[Index] & 0x0FFF) | (VariableMtrr[Index] & ValidMtrrAddressMask)
            );
  }

  ///
  /// Synchup def type Fixed Mtrrs
  ///
  AsmWriteMsr64 (MSR_IA32_MTRR_DEF_TYPE, MtrrDefType[0]);

  ///
  /// ASM code to setup processor register after synching up the MTRRs
  ///
  MpMtrrSynchUpExit (Cr4);

  return;
}

/**
  Set MTRR registers

  @param[in] Buffer   - buffer with MTRR settings
**/
VOID
SetMtrrRegisters (
  IN VOID  *Buffer
  )
{
  UINT32           Index;
  UINTN            Cr4;
  MTRR_VALUES      *MtrrArray;
  BOOLEAN          IsBspVal;

  IsBspVal = IsBsp();
  if (IsBspVal) {
    DEBUG ((DEBUG_INFO, "CpuS3 End of PEI: Synch up Variable MTRR values.\n"));
  }

  ///
  /// Init XMM support on all APs
  ///
  if (!IsBspVal) {
    XmmInit ();
  }

  ProgramXApic (IsBspVal);

  MtrrArray = (MTRR_VALUES *) Buffer;
  ///
  /// ASM code to setup processor register before synching up the MTRRs
  ///
  Cr4   = MpMtrrSynchUpEntry ();

  Index = 0;
  while ((MtrrArray[Index].Index != 0) && (MtrrArray[Index].Index >= MSR_IA32_MTRR_PHYSBASE0)) {
    AsmWriteMsr64 (MtrrArray[Index].Index, MtrrArray[Index].Value);
    Index++;
  }
  ///
  /// ASM code to setup processor register after synching up the MTRRs
  ///
  MpMtrrSynchUpExit (Cr4);
}


/**
  Print MTRR settings in debug build BIOS

  @param[in] MtrrArray   - buffer with MTRR settings
**/
VOID
ShowMtrrRegisters (
  IN MTRR_VALUES  *MtrrArray
  )
{
DEBUG_CODE_BEGIN();
  UINT32 Index;

  Index = 0;
  while ((MtrrArray[Index].Index != 0) && (MtrrArray[Index].Index >= MSR_IA32_MTRR_PHYSBASE0)) {
    DEBUG ((DEBUG_INFO, "MTRR: MtrrArray Index = %x\n", Index));
    DEBUG (
            (DEBUG_INFO,
             "MTRR: MtrrArray[%x].Index = %x    MtrrArray[%x].Value = %x\n",
             Index,
             MtrrArray[Index].Index,
             Index,
             MtrrArray[Index].Value)
            );
    Index++;
  }

  DEBUG ((DEBUG_INFO, "MTRR: Total Index = %x\n", Index));
DEBUG_CODE_END();
}
