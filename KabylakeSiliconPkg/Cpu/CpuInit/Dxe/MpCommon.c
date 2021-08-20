/** @file
  Code which support multi-processor

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#ifndef MINTREE_FLAG
#include <Private/Library/SoftwareGuardLib.h>
#endif
#include <Protocol/SmmControl2.h>
#include <Protocol/LegacyBios.h>
#include <Protocol/CpuInfo.h>

#include "MpCommon.h"
#include "CpuInitDxe.h"
#include "MpService.h"

extern EFI_GUID                         gSmramCpuDataHeaderGuid;
extern EFI_PHYSICAL_ADDRESS             mOriginalBuffer;
extern EFI_PHYSICAL_ADDRESS             mBackupBuffer;

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PHYSICAL_ADDRESS mLegacyRegion;

//
//This is for relocating APs in AsmRelocateApsInMwaitLoop.
//
volatile UINT32 mCpuCountSync;
UINT64 mOrigChgWakeUpBufferDelta;

VOID AsmRelocateApsInMwaitLoop (
  VOID
  );

/**
  Check if X2APIC is enabled

  @retval TRUE if enabled
  @retval FALSE if not enabled
**/
BOOLEAN
IsX2apicEnabled (
  VOID
  )
{
  MSR_IA32_APIC_BASE_REGISTER Msr;

  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_APIC_BASE);
  return (BOOLEAN) ((Msr.Bits.EXTD == 1) && (Msr.Bits.EN == 1));
}

/**
  Function to get APIC register from MSR or MMIO

  @param[in] X2apicEnabled    - x2APIC enabled or not
  @param[in] MsrIndex        - MSR index of APIC register
  @param[in] MemoryMappedIo  - MMIO address for APIC register

  @retval The value of APIC register
**/
UINT64
ReadApicMsrOrMemory (
  BOOLEAN X2apicEnabled,
  UINT32  MsrIndex,
  UINT64  MemoryMappedIo
  )
{
  UINT64 Value;

  if (X2apicEnabled) {
    Value = AsmReadMsr64 (MsrIndex);
  } else {
    Value = (UINT64) *(volatile UINT32 *) (UINTN) MemoryMappedIo;
  }

  return Value;
}

/**
  Function to write APIC register by MSR or MMIO

  @param[in] X2apicEnabled    - x2APIC enabled or not
  @param[in] MsrIndex        - MSR index of APIC register
  @param[in] MemoryMappedIo  - MMIO address for APIC register
  @param[in] Value           - Value that will be written to APIC register
**/
VOID
WriteApicMsrOrMemory (
  BOOLEAN X2apicEnabled,
  UINT32  MsrIndex,
  UINT64  MemoryMappedIo,
  UINT64  Value
  )
{
  if (X2apicEnabled) {
    AsmWriteMsr64 (MsrIndex, Value);
  } else {
    if (MsrIndex == MSR_IA32_X2APIC_ICR) {
      *(volatile UINT32 *) (UINTN) (MemoryMappedIo - APIC_REGISTER_ICR_LOW_OFFSET + APIC_REGISTER_ICR_HIGH_OFFSET) = (UINT32) (Value >> 32);
    }
    *(volatile UINT32 *) (UINTN) MemoryMappedIo = (UINT32) Value;
  }
}

/**
  Send interrupt to CPU

  @param[in] BroadcastMode       - Interrupt broadcast mode
  @param[in] ApicID              - APIC ID for sending interrupt
  @param[in] VectorNumber        - Vector number
  @param[in] DeliveryMode        - Interrupt delivery mode
  @param[in] TriggerMode         - Interrupt trigger mode
  @param[in] Assert              - Interrupt pin polarity

  @retval EFI_INVALID_PARAMETER  - Input parameter not correct
  @retval EFI_NOT_READY          - There was a pending interrupt
  @retval EFI_SUCCESS            - Interrupt sent successfully
**/
EFI_STATUS
SendInterrupt (
  IN UINT32  BroadcastMode,
  IN UINT32  ApicID,
  IN UINT32  VectorNumber,
  IN UINT32  DeliveryMode,
  IN UINT32  TriggerMode,
  IN BOOLEAN Assert
  )
{
  UINT64               ApicBaseReg;
  EFI_PHYSICAL_ADDRESS ApicBase;
  UINT32               IcrLow;
  UINT32               IcrHigh;
  BOOLEAN              X2apicEnabled;

  ///
  /// Initialze ICR high dword, since P6 family processor needs
  /// the destination field to be 0x0F when it is a broadcast
  ///
  IcrHigh = 0x0f000000;
  IcrLow  = VectorNumber | (DeliveryMode << 8);

  if (TriggerMode == TRIGGER_MODE_LEVEL) {
    IcrLow |= 0x8000;
  }

  if (Assert) {
    IcrLow |= 0x4000;
  }

  X2apicEnabled = IsX2apicEnabled ();

  switch (BroadcastMode) {
    case BROADCAST_MODE_SPECIFY_CPU:
      if (X2apicEnabled) {
        IcrHigh = (UINT32) ApicID;
      } else {
        IcrHigh = ApicID << 24;
      }
      break;

    case BROADCAST_MODE_ALL_INCLUDING_SELF:
      IcrLow |= 0x80000;
      break;

    case BROADCAST_MODE_ALL_EXCLUDING_SELF:
      IcrLow |= 0xC0000;
      break;

    default:
      return EFI_INVALID_PARAMETER;
  }

  ApicBaseReg = AsmReadMsr64 (MSR_IA32_APIC_BASE);
  ApicBase    = ApicBaseReg & 0xffffff000;

  /* If Extended XAPIC Mode is enabled,
     legacy xAPIC is no longer working.
     So, previous MMIO offset must be transferred to MSR offset R/W.
     ----------------------------------------------------------------
     MMIO Offset     MSR Offset     Register Name
     ----------------------------------------------------------------
     300h-310h        830h         Interrupt Command Register [63:0]
                      831h         [Reserved]
     ----------------------------------------------------------------
  */
  WriteApicMsrOrMemory (
    X2apicEnabled,
    MSR_IA32_X2APIC_ICR,
    ApicBase + APIC_REGISTER_ICR_LOW_OFFSET,
    (((UINT64) IcrHigh << 32) | (UINT64) IcrLow)
    );

  MicroSecondDelay (10);

  IcrLow = (UINT32) ReadApicMsrOrMemory (X2apicEnabled, MSR_IA32_X2APIC_ICR, ApicBase + APIC_REGISTER_ICR_LOW_OFFSET);

  if (IcrLow & BIT12) {
    return EFI_NOT_READY;
  }

  MicroSecondDelay (100);

  return EFI_SUCCESS;
}

/**
  Programs Local APIC registers.

  @param[in] Bsp  - Is this BSP?
**/
VOID
ProgramCpuXApic (
  BOOLEAN Bsp
  )
{
  UINT64               ApicBaseReg;
  EFI_PHYSICAL_ADDRESS ApicBase;
  UINT64               EntryValue;
  BOOLEAN              X2apicEnabled;

  ApicBaseReg   = AsmReadMsr64 (MSR_IA32_APIC_BASE);
  ApicBase      = ApicBaseReg & 0xffffff000;

  X2apicEnabled  = IsX2apicEnabled ();

  ///
  /// Program the Spurious Vector entry if XAPIC is enabled
  ///
  EntryValue = ReadApicMsrOrMemory (X2apicEnabled, MSR_IA32_X2APIC_SIVR, ApicBase + APIC_REGISTER_SPURIOUS_VECTOR_OFFSET);
  EntryValue &= 0xFFFFFD0F;
  EntryValue |= 0x10F;
  WriteApicMsrOrMemory (X2apicEnabled, MSR_IA32_X2APIC_SIVR, ApicBase + APIC_REGISTER_SPURIOUS_VECTOR_OFFSET, EntryValue);

  ///
  /// Double check if it is BSP
  ///
  if (!Bsp) {
    DisableInterrupts ();
  }

  ///
  /// Program the LINT0 vector entry as EntInt
  ///
  EntryValue = ReadApicMsrOrMemory (X2apicEnabled, MSR_IA32_X2APIC_LVT_LINT0, ApicBase + APIC_REGISTER_LINT0_VECTOR_OFFSET);
  if (Bsp) {
    EntryValue &= 0xFFFE00FF;
    EntryValue |= 0x700;
  } else {
    EntryValue |= 0x10000;
    ///
    /// set bit 16 as mask for LINT0
    ///
  }

  WriteApicMsrOrMemory (X2apicEnabled, MSR_IA32_X2APIC_LVT_LINT0, ApicBase + APIC_REGISTER_LINT0_VECTOR_OFFSET, EntryValue);

  ///
  /// Program the LINT1 vector entry as NMI
  ///
  EntryValue = ReadApicMsrOrMemory (X2apicEnabled, MSR_IA32_X2APIC_LVT_LINT1, ApicBase + APIC_REGISTER_LINT1_VECTOR_OFFSET);
  EntryValue &= 0xFFFE00FF;
  if (Bsp) {
    EntryValue |= 0x400;
  } else {
    EntryValue |= 0x10400;
  }

  WriteApicMsrOrMemory (X2apicEnabled, MSR_IA32_X2APIC_LVT_LINT1, ApicBase + APIC_REGISTER_LINT1_VECTOR_OFFSET, EntryValue);

}

/**
  Allocate a temporary memory under 1MB for MP Init to perform INIT-SIPI.
  This buffer also provides memory for stack/data for MP running

  @param[in] WakeUpBuffer  - Return buffer location

  @retval EFI_SUCCESS if ok to get a memory under 1MB for MP running.
**/
EFI_STATUS
AllocateWakeUpBuffer (
  OUT EFI_PHYSICAL_ADDRESS *WakeUpBuffer
  )
{
  EFI_STATUS Status;

  Status = EFI_SUCCESS;
  for (*WakeUpBuffer = PcdGet32(PcdCpuApWakeupBufferMaxAddr); *WakeUpBuffer >= 0x2000; *WakeUpBuffer -= 0x1000) {
    Status = gBS->AllocatePages (AllocateAddress, EfiReservedMemoryType, 1, WakeUpBuffer);
    if (!EFI_ERROR (Status)) {
      break;
    }
  }

  return Status;
}

/**
  Allocate Reserved Memory below 4G memory address

  @param[in] Size       - Memory Size
  @param[in] Alignment  - Alignment size
  @param[in] Pointer    - return memory location

  @retval EFI_SUCCESS   - Allocate a reserved memory successfully
**/
EFI_STATUS
AllocateAlignedReservedMemoryBelow4G (
  IN UINTN Size,
  IN UINTN Alignment,
  OUT VOID **Pointer
  )
{
  EFI_STATUS Status;
  UINTN      PointerValue;

  Status = AllocateReservedMemoryBelow4G (
             Size + Alignment - 1,
             Pointer
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  PointerValue  = (UINTN) *Pointer;
  PointerValue  = (PointerValue + Alignment - 1) / Alignment * Alignment;

  *Pointer      = (VOID *) PointerValue;
  return EFI_SUCCESS;
}

/**
  Allocate EfiReservedMemoryType below 4G memory address.

  @param[in] Size      - Size of memory to allocate.
  @param[in] Buffer    - Allocated address for output.

  @retval EFI_SUCCESS  - Memory successfully allocated.
  @retval Other        - Other errors occur.
**/
EFI_STATUS
AllocateReservedMemoryBelow4G (
  IN UINTN Size,
  OUT VOID **Buffer
  )
{
  UINTN                Pages;
  EFI_PHYSICAL_ADDRESS Address;
  EFI_STATUS           Status;

  Pages   = EFI_SIZE_TO_PAGES (Size);

  ///
  /// Limit allocate memory below 4GB
  ///
  Address = 0xffffffff;
  Status  = gBS->AllocatePages (
                   AllocateMaxAddress,
                   EfiReservedMemoryType,
                   Pages,
                   &Address
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (Address == 0) {
    return EFI_OUT_OF_RESOURCES;
  }

  *Buffer = (VOID *) (UINTN) Address;

  return EFI_SUCCESS;
}

/**
  This function is invoked when SMM_BASE protocol is installed, then we
  allocate SMRAM and save all information there.

  @param[in] Event   - The triggered event.
  @param[in] Context - Context for this event.
**/
VOID
EFIAPI
InitializeSmramDataContent (
  VOID
  )
{
  SMRAM_CPU_DATA           SmramCpuDataTemplate;
  UINTN                    LockBoxSize;
  IA32_DESCRIPTOR          *Idtr;
  IA32_DESCRIPTOR          *Gdtr;
  EFI_STATUS               Status;
  EFI_SMM_CONTROL2_PROTOCOL *SmmControl;
  UINT8                    *SmramCpuData;
  UINTN                    ArgBufferSize;
  UINT8                    ArgBuffer;
  CPU_INFO_PROTOCOL        *CpuInfo;

  DEBUG ((DEBUG_INFO, "InitializeSmramDataContent\n"));
  Status = gBS->LocateProtocol (&gEfiSmmControl2ProtocolGuid, NULL, (VOID **) &SmmControl);
  ASSERT_EFI_ERROR (Status);
  ///
  /// Init
  ///
  CopyMem (&SmramCpuDataTemplate.HeaderGuid, &gSmramCpuDataHeaderGuid, sizeof (EFI_GUID));
  SmramCpuDataTemplate.AcpiCpuPointer = (EFI_PHYSICAL_ADDRESS) (UINTN) mAcpiCpuData;
  CopyMem (&SmramCpuDataTemplate.AcpiCpuData, mAcpiCpuData, sizeof (ACPI_CPU_DATA));

  ///
  /// Calculate size
  ///
  SmramCpuDataTemplate.GdtrProfileSize = sizeof (IA32_DESCRIPTOR);
  Gdtr = (IA32_DESCRIPTOR *) (UINTN) mAcpiCpuData->GdtrProfile;
  SmramCpuDataTemplate.GdtSize = Gdtr->Limit + 1;
  SmramCpuDataTemplate.IdtrProfileSize = sizeof (IA32_DESCRIPTOR);
  Idtr = (IA32_DESCRIPTOR *) (UINTN) mAcpiCpuData->IdtrProfile;
  SmramCpuDataTemplate.IdtSize = Idtr->Limit + 1;
  SmramCpuDataTemplate.CpuPrivateDataSize = sizeof (CPU_PRIVATE_DATA);
  SmramCpuDataTemplate.S3BspMtrrTableSize = sizeof (mMPSystemData->S3BspMtrrTable);

  SmramCpuDataTemplate.GdtrProfileOffset    = sizeof (SMRAM_CPU_DATA);
  SmramCpuDataTemplate.GdtOffset            = SmramCpuDataTemplate.GdtrProfileOffset + SmramCpuDataTemplate.GdtrProfileSize;
  SmramCpuDataTemplate.IdtrProfileOffset    = SmramCpuDataTemplate.GdtOffset + SmramCpuDataTemplate.GdtSize;
  SmramCpuDataTemplate.IdtOffset            = SmramCpuDataTemplate.IdtrProfileOffset + SmramCpuDataTemplate.IdtrProfileSize;
  SmramCpuDataTemplate.CpuPrivateDataOffset = SmramCpuDataTemplate.IdtOffset + SmramCpuDataTemplate.IdtSize;
  SmramCpuDataTemplate.S3BspMtrrTableOffset = SmramCpuDataTemplate.CpuPrivateDataOffset + SmramCpuDataTemplate.CpuPrivateDataSize;

  LockBoxSize = sizeof (SMRAM_CPU_DATA) +
    SmramCpuDataTemplate.GdtrProfileSize +
    SmramCpuDataTemplate.GdtSize +
    SmramCpuDataTemplate.IdtrProfileSize +
    SmramCpuDataTemplate.IdtSize +
    SmramCpuDataTemplate.CpuPrivateDataSize +
    SmramCpuDataTemplate.S3BspMtrrTableSize;

  DEBUG ((DEBUG_INFO, "LockBoxSize                               - %x\n", LockBoxSize));
  DEBUG ((DEBUG_INFO, "SmramCpuData.GdtrProfileSize              - %x\n", SmramCpuDataTemplate.GdtrProfileSize));
  DEBUG ((DEBUG_INFO, "SmramCpuData.GdtSize                      - %x\n", SmramCpuDataTemplate.GdtSize));
  DEBUG ((DEBUG_INFO, "SmramCpuData.IdtrProfileSize              - %x\n", SmramCpuDataTemplate.IdtrProfileSize));
  DEBUG ((DEBUG_INFO, "SmramCpuData.IdtSize                      - %x\n", SmramCpuDataTemplate.IdtSize));
  DEBUG ((DEBUG_INFO, "SmramCpuData.CpuPrivateDataSize           - %x\n", SmramCpuDataTemplate.CpuPrivateDataSize));
  DEBUG ((DEBUG_INFO, "SmramCpuData.S3BspMtrrTableSize           - %x\n", SmramCpuDataTemplate.S3BspMtrrTableSize));
  DEBUG ((DEBUG_INFO, "SmramCpuData.GdtrProfileOffset            - %x\n", SmramCpuDataTemplate.GdtrProfileOffset));
  DEBUG ((DEBUG_INFO, "SmramCpuData.GdtOffset                    - %x\n", SmramCpuDataTemplate.GdtOffset));
  DEBUG ((DEBUG_INFO, "SmramCpuData.IdtrProfileOffset            - %x\n", SmramCpuDataTemplate.IdtrProfileOffset));
  DEBUG ((DEBUG_INFO, "SmramCpuData.IdtOffset                    - %x\n", SmramCpuDataTemplate.IdtOffset));
  DEBUG ((DEBUG_INFO, "SmramCpuData.CpuPrivateDataOffset         - %x\n", SmramCpuDataTemplate.CpuPrivateDataOffset));
  DEBUG ((DEBUG_INFO, "SmramCpuData.S3BspMtrrTableOffset         - %x\n", SmramCpuDataTemplate.S3BspMtrrTableOffset));

  ///
  /// Allocate Normal Memory
  ///
  SmramCpuData = AllocatePool (LockBoxSize);
  ASSERT (SmramCpuData != NULL);

  ///
  /// Allocate SMRAM
  ///
  ///
  /// Copy data buffer
  ///
  CopyMem (SmramCpuData, &SmramCpuDataTemplate, sizeof (SmramCpuDataTemplate));

  CopyMem (
    SmramCpuData + SmramCpuDataTemplate.GdtrProfileOffset,
    (VOID *) (UINTN) mAcpiCpuData->GdtrProfile,
    SmramCpuDataTemplate.GdtrProfileSize
    );
  CopyMem (
    SmramCpuData + SmramCpuDataTemplate.GdtOffset,
    (VOID *) (UINTN) Gdtr->Base,
    SmramCpuDataTemplate.GdtSize
    );
  CopyMem (
    SmramCpuData + SmramCpuDataTemplate.IdtrProfileOffset,
    (VOID *) (UINTN) mAcpiCpuData->IdtrProfile,
    SmramCpuDataTemplate.IdtrProfileSize
    );
  CopyMem (
    SmramCpuData + SmramCpuDataTemplate.IdtOffset,
    (VOID *) (UINTN) Idtr->Base,
    SmramCpuDataTemplate.IdtSize
    );
  CopyMem (
    SmramCpuData + SmramCpuDataTemplate.CpuPrivateDataOffset,
    (VOID *) (UINTN) mAcpiCpuData->CpuPrivateData,
    SmramCpuDataTemplate.CpuPrivateDataSize
    );
  ///
  /// Save Mtrr Register for S3 resume
  ///
  SaveBspMtrrForS3 ();

  CopyMem (
    SmramCpuData + SmramCpuDataTemplate.S3BspMtrrTableOffset,
    (VOID *) (UINTN) mMPSystemData->CpuPrivateData.S3BspMtrrTablePointer,
    SmramCpuDataTemplate.S3BspMtrrTableSize
    );

  ///
  /// Locate CPU Info Protocol
  ///
  Status = gBS->LocateProtocol (
                  &gCpuInfoProtocolGuid,
                  NULL,
                  (VOID **) &CpuInfo
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Fail to locate CpuInfo protocol would cause S3 resume get error.\n"));
    ASSERT_EFI_ERROR (Status);
    return;
  }

  CpuInfo->SmramCpuInfo->LockBoxData  = (EFI_PHYSICAL_ADDRESS) 0;
  CpuInfo->SmramCpuInfo->SmramCpuData = (EFI_PHYSICAL_ADDRESS) (UINTN) SmramCpuData;
  CpuInfo->SmramCpuInfo->LockBoxSize  = (UINT64) LockBoxSize;
  IoWrite8 (R_PCH_APM_STS, SMM_FROM_CPU_DRIVER_SAVE_INFO);

  ///
  /// Trigger SMI
  ///
  ArgBufferSize = sizeof (ArgBuffer);
  ArgBuffer     = mSmmbaseSwSmiNumber;
  Status        = SmmControl->Trigger (SmmControl, (UINT8 *) &ArgBuffer, (UINT8 *)&ArgBufferSize, FALSE, 0);
  Status        = SmmControl->Clear (SmmControl, 0);
  return;
}

/**
  This function is invoked when LegacyBios protocol is installed, we must
  allocate reserved memory under 1M for AP.

  @param[in] Event    - The triggered event.
  @param[in] Context  - Context for this event.
**/
VOID
EFIAPI
ReAllocateEbdaMemoryForAP (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_LEGACY_BIOS_PROTOCOL *LegacyBios;
  EFI_PHYSICAL_ADDRESS     EbdaOld;
  EFI_PHYSICAL_ADDRESS     EbdaNew;
  UINTN                    EbdaSize;
  EFI_STATUS               Status;
  EFI_PEI_HOB_POINTERS     HobPtr;
  SI_CONFIG_HOB            *SiConfigHob;

  //
  // Get Silicon Config data HOB
  //
  HobPtr.Guid = GetFirstGuidHob (&gSiConfigHobGuid);
  SiConfigHob = (SI_CONFIG_HOB *)GET_GUID_HOB_DATA (HobPtr.Guid);

  //
  // Check CSM Status
  //
  if (SiConfigHob->CsmFlag == 0) {
    return;
  }
  ///
  /// Check whether this is real LegacyBios notification
  ///
  Status = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, (VOID **) &LegacyBios);
  if (EFI_ERROR (Status)) {
    return;
  }
  ///
  /// PLEASE NOTE:
  /// For legacy implementation, we have reserved 0x9F000 to 0x9FFFF for S3 usage in CSM,
  /// No don't need to allocate it again
  /// This range will be used for MpS3 driver and S3Resume driver on S3 boot path
  /// The base needs to be aligned to 4K to satisfy the AP vector requirement
  /// The original implementation requires 8K from legacy memory form E/F segment,
  /// which needs lock/unlock and makes lots of code chipset dependent on S3 boot path
  /// Here we just use normal low memory to eliminate the dependency
  /// In this case, EBDA will start from 0x9F000 - sizeof (EBDA) in CSM definition
  /// CSM EBDA base and memory size in BDA area needs to be consistent with this
  ///
  ///
  /// Get EDBA address/length and turn it into the S3 reserved address
  /// The length of this range is limited so we need to keep the real mode code small
  ///
  EbdaOld                     = (EFI_PHYSICAL_ADDRESS) (*(UINT16 *) (UINTN) 0x40E) << 4;
  EbdaSize                    = (UINTN) (*((UINT8 *) (UINTN) EbdaOld));
  mLegacyRegion               = EbdaOld + (EbdaSize << 10);
  mLegacyRegion               = (mLegacyRegion - 0x1000) & 0xFFFFF000;
  EbdaNew                     = mLegacyRegion - (EbdaSize << 10);
  (*(UINT16 *) (UINTN) 0x40E) = (UINT16) (EbdaNew >> 4);
  CopyMem ((VOID *) (UINTN) EbdaNew, (VOID *) (UINTN) EbdaOld, EbdaSize << 10);

  ///
  /// Update 40:13 with the new size of available base memory
  ///
  *(UINT16 *) (UINTN) 0x413 = (*(UINT16 *) (UINTN) 0x413) - (UINT16) (((EbdaOld - EbdaNew) >> 10));

  ///
  /// Free the Wake-up buffer and re-declare it as Reserved Memory
  ///
  DEBUG ((DEBUG_INFO, "Legacy region freed before re-allocation:  %X\n", mLegacyRegion));
  Status  = (gBS->FreePages) (mLegacyRegion, 1);
  ASSERT_EFI_ERROR (Status);
  DEBUG ((DEBUG_INFO, "Allocate and reserve the 4K buffer for Legacy Region\n"));
  Status = (gBS->AllocatePages) (AllocateAddress, EfiReservedMemoryType, 1, &mLegacyRegion);
  ASSERT_EFI_ERROR (Status);
  DEBUG ((DEBUG_INFO, "mLegacyRegion CSM - %x\n", mLegacyRegion));
}

/**
  This callback function will be executed when EndofDxe event is signaled.
  This function will do the following:
    - Allocate memory (wakeup buffer) for AP
    - Set all threads to deepest C states
    - Initialize SMRAM contents

  @param[in] Event    - The triggered event.
  @param[in] Context  - Context for this event.
**/
VOID
EFIAPI
ReAllocateMemoryForAP (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS               Status;
  EFI_PHYSICAL_ADDRESS     OrigWakeUpBuffer;
  MP_CPU_EXCHANGE_INFO     *OrigExchangeInfo;
  EFI_PHYSICAL_ADDRESS     LegacyRegion;
  MP_CPU_EXCHANGE_INFO     *ExchangeInfo;
  MONITOR_MWAIT_DATA       *MonitorAddr;
  UINTN                    Index;
  EFI_LEGACY_BIOS_PROTOCOL *LegacyBios;
  BOOLEAN                  HasCsm;
  EFI_PEI_HOB_POINTERS     HobPtr;
  SI_CONFIG_HOB            *SiConfigHob;

  STATIC BOOLEAN InitDone = FALSE;

  ///
  /// Make sure it is invoked only once.
  ///
  if (InitDone) {
    return;
  }

  InitDone   = TRUE;
  HasCsm     = FALSE;
  LegacyBios = NULL;
  //
  // Get Silicon Config data HOB
  //
  HobPtr.Guid = GetFirstGuidHob (&gSiConfigHobGuid);
  SiConfigHob = (SI_CONFIG_HOB *)GET_GUID_HOB_DATA (HobPtr.Guid);

  if (SiConfigHob->CsmFlag == 1) {
    Status    = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, (VOID **) &LegacyBios);
    if (EFI_ERROR (Status)) {
      HasCsm = FALSE;
    } else {
      HasCsm = TRUE;
    }
  }


  while (ApRunning ()) {
    CpuPause ();
  }


#ifndef MINTREE_FLAG
  ///
  /// Update SGX Global NVS Information
  ///
  UpdateSgxNvs ();
#endif

  if (HasCsm) {
    LegacyRegion = mLegacyRegion;
    DEBUG ((DEBUG_INFO, "Using LegacyRegion CSM - %x\n", LegacyRegion));
  } else {
    ///
    /// The BackBuffer is 4k. Allocate 0x2000 bytes from below 640K memory to ensure 4k aligned spaces of 0x1000 bytes,
    /// since Alignment argument does not work.
    ///
    LegacyRegion = 0x9FFFF;
    Status = gBS->AllocatePages (AllocateMaxAddress, EfiReservedMemoryType, EFI_SIZE_TO_PAGES (0x2000), &LegacyRegion);
    ASSERT_EFI_ERROR (Status);
    DEBUG ((DEBUG_INFO, "LegacyRegion NonCSM - %x\n", LegacyRegion));
    if (EFI_ERROR (Status)) {
      return;
    }
  }
  ///
  /// This address should be less than A seg.
  /// And it should be aligned to 4K
  ///
  ASSERT (!((UINTN) LegacyRegion & 0x0FFF) && ((UINTN) LegacyRegion < 0xA0000));
  LegacyRegion = (LegacyRegion + 0x0FFF) & 0x0FFFFF000;

  ///
  /// Save original wake-up Buffer and difference between new wake-buffer and original wake-up buffer.
  /// This is needed to transistion the APs in a monitor/mwait or free run loop into the new buffer.
  ///

  OrigWakeUpBuffer = mAcpiCpuData->WakeUpBuffer;
  OrigExchangeInfo = (MP_CPU_EXCHANGE_INFO *) (UINTN) (OrigWakeUpBuffer + MP_CPU_EXCHANGE_INFO_OFFSET);
  mOrigChgWakeUpBufferDelta = LegacyRegion - OrigWakeUpBuffer;

  mAcpiCpuData->WakeUpBuffer  = (EFI_PHYSICAL_ADDRESS) LegacyRegion;
  ExchangeInfo                = (MP_CPU_EXCHANGE_INFO *) (UINTN) (mBackupBuffer + MP_CPU_EXCHANGE_INFO_OFFSET);
  ExchangeInfo->BufferStart   = (UINT32) mAcpiCpuData->WakeUpBuffer;
  CopyMem (
    (VOID *) (UINTN) mAcpiCpuData->WakeUpBuffer,
    (VOID *) (UINTN) mBackupBuffer,
    EFI_PAGE_SIZE
    );
  RedirectFarJump ();
  if (HasCsm) {
    Status = LegacyBios->CopyLegacyRegion (
                           LegacyBios,
                           sizeof (MP_CPU_EXCHANGE_INFO),
                           (VOID *) (UINTN) (mAcpiCpuData->WakeUpBuffer + MP_CPU_EXCHANGE_INFO_OFFSET),
                           (VOID *) (UINTN) (mBackupBuffer + MP_CPU_EXCHANGE_INFO_OFFSET)
                           );
  }

  ///
  /// Set all APs to deepest C-State before ready to boot for better power saving,
  /// if boot to DOS/EFI_SHARE or any operating system that running only single thread.
  ///
  ExchangeInfo = (MP_CPU_EXCHANGE_INFO *) (UINTN) (mAcpiCpuData->WakeUpBuffer + MP_CPU_EXCHANGE_INFO_OFFSET);
  if (mCpuConfigData->ApIdleManner != WakeUpApPerHltLoop) {
    //
    // Relocate APs into new exchange buffer
    //
    mCpuCountSync = (UINT32)mMPSystemData->NumberOfCpus - 1;
    OrigExchangeInfo->ApFunction = (VOID *) (UINTN)AsmRelocateApsInMwaitLoop; // This changes only in old location.

    //
    // Release APs into new Wake-up buffer.
    // Exchange Info will be new with the new one with expected values for MP Services.
    //
    for (Index = 0; Index < mMPSystemData->NumberOfCpus; Index++) {
      MonitorAddr = (MONITOR_MWAIT_DATA *) ((UINT8 *) OrigExchangeInfo->StackStart + (Index + 1) * OrigExchangeInfo->StackSize - MONITOR_FILTER_SIZE);
      MonitorAddr->BreakToRunApSignal       = (UINTN) (BREAK_TO_RUN_AP_SIGNAL) | mMPSystemData->CpuData[Index].ApicID;
    }

    //
    // Wait for APs to complete.
    //
    while (mCpuCountSync > 0);
  }

  ///
  /// Invoke the InitializeSmram directly, since it is in EndOfDxe event.
  ///
  InitializeSmramDataContent ();
}

/**
  This function is invoked by EFI_EVENT_SIGNAL_LEGACY_BOOT.
  Before booting to legacy OS, preparing for S3 usage.

  @param[in] Event    - The triggered event.
  @param[in] Context  - Context for this event.
**/
VOID
EFIAPI
ResetAps (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  MP_CPU_EXCHANGE_INFO                          *ExchangeInfo;
  MONITOR_MWAIT_DATA                            *MonitorAddr;
  UINTN                                         Index;
  UINTN                                         MaxCstate;
  MSR_BROADWELL_PKG_CST_CONFIG_CONTROL_REGISTER Msr;
  UINT32                                        SubStates;
  EFI_CPUID_REGISTER                            MwaitInfo;

  ExchangeInfo = (MP_CPU_EXCHANGE_INFO *) (UINTN) (mAcpiCpuData->WakeUpBuffer + MP_CPU_EXCHANGE_INFO_OFFSET);
  if (mCpuConfigData->ApHandoffManner != WakeUpApPerHltLoop) {
    ///
    /// Set all APs to deepest C-State before ready to boot for better power saving,
    /// if boot to DOS/EFI_SHARE or any operating system that running only single thread.
    ///
    /// BIOS should use CPUID.(EAX=5) Monitor/Mwait Leaf and also check MSR E2h[3:0] Package C-state limit to determine
    /// if the processor supports MONITOR/MWAIT extensions for various C-states and sub C-states.
    ///
    Msr.Uint64 = AsmReadMsr64 (MSR_BROADWELL_PKG_CST_CONFIG_CONTROL);
    AsmCpuid (5, &MwaitInfo.RegEax, &MwaitInfo.RegEbx, &MwaitInfo.RegEcx, &MwaitInfo.RegEdx);
    MaxCstate = 0;
    SubStates = 0;
    if (MwaitInfo.RegEcx & BIT0) {
      switch (Msr.Bits.Limit) {
        case V_CSTATE_LIMIT_C10:
          SubStates = (MwaitInfo.RegEdx & (BIT31 | BIT30 | BIT29 | BIT28)) >> 28;
          MaxCstate = 0x60;
          break;

        case V_CSTATE_LIMIT_C9:
          SubStates = (MwaitInfo.RegEdx & (BIT27 | BIT26 | BIT25 | BIT24)) >> 24;
          MaxCstate = 0x50;
          break;

        case V_CSTATE_LIMIT_C8:
          SubStates = (MwaitInfo.RegEdx & (BIT23 | BIT22 | BIT21 | BIT20)) >> 20;
          MaxCstate = 0x40;
          break;

        case V_CSTATE_LIMIT_C7S:
          SubStates = (MwaitInfo.RegEdx & (BIT19 | BIT18 | BIT17 | BIT16)) >> 16;
          MaxCstate = 0x30;
          break;

        case V_CSTATE_LIMIT_C7:
          SubStates = (MwaitInfo.RegEdx & (BIT19 | BIT18 | BIT17 | BIT16)) >> 16;
          MaxCstate = 0x30;
          break;

        case V_CSTATE_LIMIT_C6:
          SubStates = (MwaitInfo.RegEdx & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12;
          MaxCstate = 0x20;
          break;

        case V_CSTATE_LIMIT_C3:
          SubStates = (MwaitInfo.RegEdx & (BIT11 | BIT10 | BIT9 | BIT8)) >> 8;
          MaxCstate = 0x10;
          break;

        case V_CSTATE_LIMIT_C1:
          SubStates = (MwaitInfo.RegEdx & (BIT7 | BIT6 | BIT5 | BIT4)) >> 4;
          MaxCstate = 0x00;
          break;

        default:
          break;
      }
    }

    ///
    /// If Substates opcode is greater than 1 than add that info to the MaxCstate Opcode.
    ///
    if (SubStates > 1) {
      MaxCstate |= (UINTN) (SubStates - 1);
    }

    ///
    /// Use WakeUpApPerMwaitLoop32 if CR4 paging table entities are not allocated as RESERVED MEMORY TYPE in 64-bits mode.
    ///
    ExchangeInfo->WakeUpApManner  = WakeUpApPerMwaitLoop32;
    for (Index = 0; Index < mMPSystemData->NumberOfCpus; Index++) {
      MonitorAddr = (MONITOR_MWAIT_DATA *) ((UINT8 *) ExchangeInfo->StackStart + (Index + 1) * ExchangeInfo->StackSize - MONITOR_FILTER_SIZE);
      MonitorAddr->WakeUpApVectorChangeFlag = TRUE;
      MonitorAddr->MwaitTargetCstate        = MaxCstate;
    }
  } else {
    //
    // If APs are halt, they will remian in halt.
    // If APs are in free run, they will immediately go into halt.
    // If Aps are in monitor/mwait, they will have to be woken up.
    //
    ExchangeInfo->WakeUpApManner = WakeUpApPerHltLoop;

    if (mCpuConfigData->ApIdleManner == WakeUpApPerMwaitLoop) {
      //
      // Release APs from monitor/mwait loop to go into halt.
      //
      for (Index = 0; Index < mMPSystemData->NumberOfCpus; Index++) {
        MonitorAddr = (MONITOR_MWAIT_DATA *) ((UINT8 *) ExchangeInfo->StackStart + (Index + 1) * ExchangeInfo->StackSize - MONITOR_FILTER_SIZE);
        MonitorAddr->WakeUpApVectorChangeFlag = TRUE;
      }
    }
  }
}
