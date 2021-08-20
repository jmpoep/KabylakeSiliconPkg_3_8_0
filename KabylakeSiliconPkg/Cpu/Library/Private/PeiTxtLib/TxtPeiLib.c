/** @file
  This file contains an implementation of the function call interfaces
  required by the main TXT PEIM file. Hopefully, future platform porting
  tasks will be mostly limited to modifying the functions in this file.

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

@par Specification
**/

#include <Private/Library/TxtPeiLib.h>
#include <Private/Library/CpuCommonLib.h>
#include <Library/TxtLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <PchResetPlatformSpecific.h>


/**
  This routine initializes and collects all PPIs and data required
  by the routines in this file.

  @param[in] TxtContextDataPtr          - A pointer to an initialized TXT PEI Context data structure

  @exception EFI_UNSUPPORTED   - If any of the required PPIs or data are unavailable
  @retval EFI_SUCCESS       - In all cases not listed above
**/
EFI_STATUS
InitializeTxtPeiLib (
  IN TXT_PEI_LIB_CONTEXT *TxtContextDataPtr
  )
{
  EFI_STATUS Status;

  ///
  /// Make sure our pointers start life as NULL pointers
  ///
  TxtContextDataPtr->BiosAcmBase = NULL;
  TxtContextDataPtr->ApStartup   = NULL;

  ///
  /// Find TxtInfoHob by platform code
  ///
  Status = CreateTxtInfoHob (TxtContextDataPtr);

  if (Status != EFI_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "TXTPEI: TXT Info Hob not found or TXT is not supported.\n"));
    return EFI_UNSUPPORTED;
  }
  ///
  /// Print out the TxtInfo HOB if TXT_DEBUG_INFO is set
  ///
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtInfoHob passed from platform as:\n"));
  DEBUG ((DEBUG_INFO, "TXTPEI: ChipsetIsTxtCapable   = %x\n", TxtContextDataPtr->Hob->Data.ChipsetIsTxtCapable));
  DEBUG ((DEBUG_INFO, "TXTPEI: ProcessorIsTxtCapable = %x\n", TxtContextDataPtr->Hob->Data.ProcessorIsTxtCapable));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtMode               = %x\n", TxtContextDataPtr->Hob->Data.TxtMode));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtAcheckRequest      = %x\n", TxtContextDataPtr->Hob->Data.TxtAcheckRequest));
  DEBUG ((DEBUG_INFO, "TXTPEI: ResetAux              = %x\n", TxtContextDataPtr->Hob->Data.ResetAux));
  DEBUG ((DEBUG_INFO, "TXTPEI: AcpiBase              = %x\n", TxtContextDataPtr->Hob->Data.AcpiBase));
  DEBUG ((DEBUG_INFO, "TXTPEI: SinitMemorySize       = %x\n", TxtContextDataPtr->Hob->Data.SinitMemorySize));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtHeapMemorySize     = %x\n", TxtContextDataPtr->Hob->Data.TxtHeapMemorySize));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtDprMemoryBase      = %x\n", TxtContextDataPtr->Hob->Data.TxtDprMemoryBase));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtDprMemorySize      = %x\n", TxtContextDataPtr->Hob->Data.TxtDprMemorySize));
  DEBUG ((DEBUG_INFO, "TXTPEI: BiosAcmBase           = %x\n", TxtContextDataPtr->Hob->Data.BiosAcmBase));
  DEBUG ((DEBUG_INFO, "TXTPEI: BiosAcmSize           = %x\n", TxtContextDataPtr->Hob->Data.BiosAcmSize));
  DEBUG ((DEBUG_INFO, "TXTPEI: SinitAcmBase          = %x\n", TxtContextDataPtr->Hob->Data.SinitAcmBase));
  DEBUG ((DEBUG_INFO, "TXTPEI: SinitAcmSize          = %x\n", TxtContextDataPtr->Hob->Data.SinitAcmSize));
  DEBUG ((DEBUG_INFO, "TXTPEI: TgaSize               = %x\n", TxtContextDataPtr->Hob->Data.TgaSize));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtLcpPdBase          = %x\n", TxtContextDataPtr->Hob->Data.TxtLcpPdBase));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtLcpPdSize          = %x\n", TxtContextDataPtr->Hob->Data.TxtLcpPdSize));
  DEBUG ((DEBUG_INFO, "TXTPEI: Flags                 = %x\n", TxtContextDataPtr->Hob->Data.Flags));
  DEBUG ((DEBUG_INFO, "TXTPEI: ApStartupBase         = %x\n", TxtContextDataPtr->Hob->Data.ApStartupBase));

  ///
  /// Check if platform specify BIOS ACM address by itself, BIOS ACM address must be 4K alignment in FLASH address space
  ///
  if (TxtContextDataPtr->Hob->Data.BiosAcmBase != 0) {
    DEBUG ((DEBUG_INFO, "TXTPEI: BIOS ACM location at %x\n", TxtContextDataPtr->Hob->Data.BiosAcmBase));
    ///
    /// Check BIOS ACM is 4K alignment or not
    ///
    if ((TxtContextDataPtr->Hob->Data.BiosAcmBase & 0xFFF) != 0) {
      DEBUG ((DEBUG_ERROR, "TXTPEI: BIOS ACM is not 4K aligned, force TxtMode=0 and unloaded!!\n"));
      TxtContextDataPtr->Hob->Data.TxtMode = 0;
      return EFI_UNSUPPORTED;
    }
    ///
    /// Get BIOS ACM base from TxtInfoHob provided by platform code
    ///
    TxtContextDataPtr->BiosAcmBase = (ACM_HEADER *) (UINT32) TxtContextDataPtr->Hob->Data.BiosAcmBase;
  } else {
    DEBUG ((DEBUG_ERROR, "TXTPEI: BIOS ACM not found, force TxtMode=0 and unloaded!\n"));
    TxtContextDataPtr->Hob->Data.TxtMode = 0;
    return EFI_UNSUPPORTED;
  }
  ///
  /// Check ACM is matched to chipset or not, if not, disable TXT and return EFI_UNLOAD_IMAGE
  ///
  if (!CheckTxtAcmMatch (TxtContextDataPtr, TxtContextDataPtr->BiosAcmBase)) {
    DEBUG ((DEBUG_ERROR, "TXTPEI: BIOS ACM is not matched to chipset!! Force TxtMode=0 and unloaded!!\n"));
    TxtContextDataPtr->Hob->Data.TxtMode = 0;
    return EFI_UNSUPPORTED;
  }

  TxtContextDataPtr->BiosAcmSize = (TxtContextDataPtr->BiosAcmBase->Size) << 2;

  ///
  /// Check if platform specify AP starup address
  ///
  if (TxtContextDataPtr->Hob->Data.ApStartupBase != 0) {
    DEBUG ((DEBUG_INFO, "TXTPEI: AP Startup location at %x\n", TxtContextDataPtr->Hob->Data.ApStartupBase));
    ///
    /// Get AP startup base from TxtInfoHob provided by platform code
    ///
    TxtContextDataPtr->ApStartup = (ACM_HEADER *) (UINT32) TxtContextDataPtr->Hob->Data.ApStartupBase;
  } else {
    DEBUG ((DEBUG_ERROR, "TXTPEI: AP Startup location not found, force TxtMode=0 and unloaded!\n"));
    TxtContextDataPtr->Hob->Data.TxtMode = 0;
    return EFI_UNSUPPORTED;
  }

  ///
  /// Initialize local APIC
  ///
  if ((((AsmReadMsr64 (MSR_IA32_APIC_BASE)) & (BIT11 + BIT10)) == BIT11 + BIT10)) {
    AsmWriteMsr64 (MSR_IA32_X2APIC_SIVR, 0x1FF);
  } else {
    ///
    /// Determine address of Local APIC
    ///
    TxtContextDataPtr->Ia32ApicBase  = ((UINT32) AsmReadMsr64 (MSR_IA32_APIC_BASE)) & BASE_ADDR_MASK;
    *(UINT32 *) (TxtContextDataPtr->Ia32ApicBase + APIC_SPURIOUS_VECTOR_REGISTER) = 0x1FF;
  }
  ///
  /// Initialize TxtInfoHob fields
  ///
  TxtContextDataPtr->Hob->Data.BiosAcmBase       = (UINTN) TxtContextDataPtr->BiosAcmBase;
  TxtContextDataPtr->Hob->Data.BiosAcmSize       = (UINTN) TxtContextDataPtr->BiosAcmSize;

  ///
  /// Make sure none of our pointers are still NULL
  ///
  if (!(TxtContextDataPtr->BiosAcmBase && TxtContextDataPtr->ApStartup)) {
    TxtContextDataPtr->Hob->Data.TxtMode = 0;
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/**
  Determines whether or not the current processor is TXT Capable.

  @retval TRUE          - If the current processor supports TXT
  @retval FALSE         - If the current processor does not support TXT
**/
BOOLEAN
IsTxtProcessor (
  VOID
  )
{
  CPUID_VERSION_INFO_ECX Ecx;

  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &Ecx.Uint32, NULL);

  return (BOOLEAN) (Ecx.Bits.SMX == 1);
}

/**
  Determines whether or not the current chipset is TXT Capable.

  @param[in] TxtContextDataPtr          - A pointer to an initialized TXT PEI Context data structure

  @retval TRUE          - If the current chipset supports TXT
  @retval FALSE         - If the current chipset doesn't supports TXT
**/
BOOLEAN
IsTxtChipset (
  IN TXT_PEI_LIB_CONTEXT *TxtContextDataPtr
  )
{
  BOOLEAN TxtCapable;
  UINT32  Data32;

  TxtCapable  = FALSE;
  Data32      = CheckSmxCapabilities ();

  if ((Data32 & BIT0) != 0) {
    TxtCapable = TRUE;
    DEBUG ((DEBUG_INFO, "Platform/PCH - TXT supported\n"));
  } else {
    TxtCapable = FALSE;
    DEBUG ((DEBUG_INFO, "Platform/PCH - TXT not supported!!!\n"));
  }

  return TxtCapable;
}

/**
  Determines whether TXT is enabled by platform setting

  @param[in] TxtContextDataPtr          - A pointer to an initialized TXT PEI Context data structure

  @retval TRUE          - If TXT is enabled by platform setting
  @retval FALSE         - If TXT is disabled by platform setting
**/
BOOLEAN
IsTxtEnabled (
  IN TXT_PEI_LIB_CONTEXT *TxtContextDataPtr
  )
{
  if (TxtContextDataPtr->Hob == 0) {
    return FALSE;
  }

  return (BOOLEAN) (TxtContextDataPtr->Hob->Data.TxtMode);
}

/**
  Determines whether Alias Check Request is enabled by platform setting

  @param[in] TxtContextDataPtr          - A pointer to an initialized TXT PEI Context data structure

  @retval TRUE          - If ACHECK REQUEST is enabled by platform setting
  @retval FALSE         - If ACHECK REQUEST is disabled by platform setting
**/
BOOLEAN
IsAcheckRequested (
  TXT_PEI_LIB_CONTEXT *TxtContextDataPtr
  )
{
  if (TxtContextDataPtr->Hob == 0) {
    return FALSE;
  }

  return (BOOLEAN) (TxtContextDataPtr->Hob->Data.TxtAcheckRequest);
}

/**
  Determines ACM is matched to chipset or not

  @param[in] TxtContextDataPtr         - Point to TXT_PEI_LIB_CONTEXT structure
  @param[in] BiosAcmBase  - A pointer to BIOS ACM location

  @retval TRUE          - BIOS ACM is matched to chipset
  @retval FALSE         - BIOS ACM is NOT matched to chipset
**/
BOOLEAN
CheckTxtAcmMatch (
  IN TXT_PEI_LIB_CONTEXT *TxtContextDataPtr,
  IN ACM_HEADER          *BiosAcmBase
  )
{
  BOOLEAN ChipsetIsProduction;
  BOOLEAN BiosAcmIsProduction;

  if (BiosAcmBase == NULL) {
    return FALSE;

  }
  ///
  /// Initializing ChipsetIsProduction default value
  ///
  ChipsetIsProduction = (*(UINT32 *) (TXT_PUBLIC_BASE + 0x200) & BIT31) ? TRUE : FALSE;

  ///
  /// Check ACM is production or not
  ///
  BiosAcmIsProduction = (BiosAcmBase->ModuleID & BIT31) ? FALSE : TRUE;

  return ChipsetIsProduction == BiosAcmIsProduction;
}

/**
  Create TXT Info HOB

  @param[in] TxtContextDataPtr          - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS   - If TXT Info Hob is found
  @exception EFI_NOT_FOUND - If TXT Info Hob is not found
  @exception EFI_UNSUPPORTED - If the platform is not TXT capable.
**/
EFI_STATUS
CreateTxtInfoHob (
  IN TXT_PEI_LIB_CONTEXT *TxtContextDataPtr
  )
{
  EFI_STATUS                   Status;
  SI_PREMEM_POLICY_PPI         *SiPreMemPolicy;
  TXT_INFO_HOB                 *TxtInfoHob;
  CPU_SECURITY_PREMEM_CONFIG   *CpuSecurityPreMemConfig;
  CPU_TXT_PREMEM_CONFIG        *CpuTxtPreMemConfig;
  UINT16                       AcpiBase;

  TxtInfoHob = NULL;
  //
  // Get TxtInfoHob if it is already present, then this is the reinitalize, just reload the hob and exit
  //
  TxtInfoHob = (TXT_INFO_HOB *) GetFirstGuidHob (&gTxtInfoHobGuid);
  if (TxtInfoHob != NULL) {
    TxtContextDataPtr->Hob = TxtInfoHob;
    return EFI_SUCCESS;
  }
  ///
  /// Locate Cpu policy ppi to initialized.
  ///
  Status = PeiServicesLocatePpi (
                  &gSiPreMemPolicyPpiGuid,
                  0,
                  NULL,
                  (VOID **) &SiPreMemPolicy
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gCpuTxtPreMemConfigGuid, (VOID *) &CpuTxtPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  ///
  /// Create hob for storing TXT data
  ///
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (TXT_INFO_HOB),
             (VOID **) &TxtInfoHob
             );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  TxtContextDataPtr->Hob = TxtInfoHob;
  TxtInfoHob->EfiHobGuidType.Name = gTxtInfoHobGuid;
  ///
  /// Initiate Txt Info Hob
  ///
  ZeroMem (&(TxtInfoHob->Data), sizeof (TXT_INFO_DATA));

  TxtInfoHob->Data.ChipsetIsTxtCapable = IsTxtChipset (TxtContextDataPtr);
  TxtInfoHob->Data.ProcessorIsTxtCapable = IsTxtProcessor ();
  if (CpuSecurityPreMemConfig->Txt == 1) {
    TxtInfoHob->Data.TxtMode = 1;
  }

  PchAcpiBaseGet (&AcpiBase);

  TxtInfoHob->Data.AcpiBase           = (UINT16) AcpiBase;
  TxtInfoHob->Data.TxtAcheckRequest   = (BOOLEAN) CpuSecurityPreMemConfig->TxtAcheckRequest;
  TxtInfoHob->Data.ResetAux           = (BOOLEAN) CpuSecurityPreMemConfig->ResetAux;
  TxtInfoHob->Data.SinitMemorySize    = (UINT64) CpuTxtPreMemConfig->SinitMemorySize;
  TxtInfoHob->Data.TxtHeapMemorySize  = (UINT64) CpuTxtPreMemConfig->TxtHeapMemorySize;
  TxtInfoHob->Data.TxtDprMemoryBase   = CpuTxtPreMemConfig->TxtDprMemoryBase;
  TxtInfoHob->Data.TxtDprMemorySize   = (UINT64) CpuTxtPreMemConfig->TxtDprMemorySize;
  TxtInfoHob->Data.BiosAcmBase        = CpuTxtPreMemConfig->BiosAcmBase;
  TxtInfoHob->Data.BiosAcmSize        = (UINT64) CpuTxtPreMemConfig->BiosAcmSize;
  TxtInfoHob->Data.TgaSize            = (UINT64) CpuTxtPreMemConfig->TgaSize;
  TxtInfoHob->Data.TxtLcpPdBase       = CpuTxtPreMemConfig->TxtLcpPdBase;
  TxtInfoHob->Data.TxtLcpPdSize       = CpuTxtPreMemConfig->TxtLcpPdSize;
  TxtInfoHob->Data.ApStartupBase      = CpuTxtPreMemConfig->ApStartupBase;

  return EFI_SUCCESS;
}

/**
  Is Spt in PTT mode

  @retval TRUE          - If the PTT mode is asserted.
  @retval FALSE         - If the PTT mode is unasserted.
**/

BOOLEAN
IsSptPtt (
  VOID
  )
{
  UINT32 RegRead;

  RegRead = MmioRead32 (TXT_PUBLIC_BASE + TXT_PTT_FTIF_OFF);
  DEBUG ((DEBUG_INFO, "IsSptPtt: LT FTIF = %x\n", RegRead));
  RegRead = RegRead & TXT_PTT_PRESENT;
  if (RegRead == TXT_PTT_PRESENT) {
    DEBUG ((DEBUG_INFO, "IsSptPtt: PTT cycle\n"));
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Determines whether or not the platform has executed a TXT launch by
  examining the TPM Establishment bit.

  @param[in] TxtContextDataPtr      - A pointer to an initialized TXT PEI Context data structure

  @retval TRUE          - If the TPM establishment bit is asserted.
  @retval FALSE         - If the TPM establishment bit is unasserted.
**/
BOOLEAN
TxtIsEstablishmentBitAsserted (
  IN TXT_PEI_LIB_CONTEXT *TxtContextDataPtr
  )
{
  UINT8  Access;
  UINT16 TimeOutCount;

  if (IsSptPtt ()) {
    MmioRead8 (TPM_STATUS_REG_ADDRESS);
    return FALSE;
  }
  ///
  /// Set TPM.ACCESS polling timeout about 750ms
  ///
  TimeOutCount = TPM_TIME_OUT;
  do {
    ///
    /// Read TPM status register
    ///

    Access = MmioRead8 (TPM_STATUS_REG_ADDRESS);

    ///
    /// if TPM.Access == 0xFF, TPM is not present
    ///
    if (Access == 0xFF) {
      return FALSE;
    }
    ///
    /// Check tpmRegValidSts bit before checking establishment bit
    ///
    if ((Access & 0x80) != 0x80) {
      ///
      /// Delay 1ms
      ///
      MicroSecondDelay (1000);
    } else {
      ///
      /// tpmRegValidSts set, we can check establishment bit now.
      ///
      break;
    }

    TimeOutCount--;
  } while (TimeOutCount != 0);
  ///
  /// if tpmRegValidSts is not set, TPM is not usable
  ///
  if ((Access & 0x80) != 0x80) {
    DEBUG ((DEBUG_ERROR, "TXTPEI: TPM Valid Status is not set!! TPM.ACCESS=%x\n", Access));
    ASSERT (TRUE);
    CpuDeadLoop ();
  }
  ///
  /// The bit we're interested in uses negative logic:
  /// If bit 0 == 1 then return False
  /// Else return True
  ///
  return (Access & 0x1) ? FALSE : TRUE;
}

/**
  Determines whether or not the platform has encountered an error during
  a sleep or power-off state.

  @retval TRUE          - If the TXT_WAKE_ERROR bit is asserted.
  @retval FALSE         - If the TXT_WAKE_ERROR bit is unasserted.
**/
BOOLEAN
IsTxtWakeError (
  VOID
  )
{
  UINT8 Ests;

  ///
  /// Read TXT.ESTS register
  ///
  Ests = MmioRead8 (TXT_PUBLIC_BASE + TXT_ERROR_STATUS_REG_OFF);

  DEBUG ((DEBUG_INFO, "TXTPEI: TXT.ESTS=%x\n", Ests));

  return (Ests & (0x1 << 6)) ? TRUE : FALSE;
}

/**
  Determines whether or not the platform memory has been locked

  @retval TRUE          - If memroy is locked
  @retval FALSE         - If memory is unlocked
**/
BOOLEAN
IsMemoryLocked (
  VOID
  )
{
  UINT32 CpuMemLockStatus;

  ///
  /// Check status register for now.
  ///
  CpuMemLockStatus = MmioRead32 (TXT_PUBLIC_BASE + TXT_E2STS_REG_OFF);

  DEBUG ((DEBUG_INFO, "TXTPEI: CPU_UNCORE_MEMLOCK_STATUS=%x\n", CpuMemLockStatus));
  ///
  /// if BLOCK_MEM_STS (BIT2) is set to 1, memory is in unlock.
  ///
  return (CpuMemLockStatus & TXT_BLOCK_MEM_STS) ? TRUE : FALSE;
}

/**
  Determines whether or not POISON bit is set in status register

  @retval TRUE          - If the TPM reset bit is asserted.
  @retval FALSE         - If the TPM reset bit is unasserted.
**/
BOOLEAN
IsTxtResetSet (
  VOID
  )
{
  UINT8 Ests;
  ///
  /// Read TXT.ESTS register
  ///
  Ests = MmioRead8 (TXT_PUBLIC_BASE + TXT_ERROR_STATUS_REG_OFF);

  return (Ests & (0x1 << 0)) ? TRUE : FALSE;
}

/**
  Determines whether or not SECRETS.STS bit is set in E2STS status register

  @retval TRUE          - If the LT.SECRETS.STS bit is asserted.
  @retval FALSE         - If the LT.SECRETS.STS bit is unasserted.
**/
BOOLEAN
IsTxtSecretsSet (
  VOID
  )
{
  UINT8 E2sts;

  ///
  /// Read TXT.E2STS register
  ///
  E2sts = MmioRead8 (TXT_PUBLIC_BASE + TXT_E2STS_REG_OFF);

  return (E2sts & TXT_SECRETS_STS) ? TRUE : FALSE;
}

/**
  Determines presence of TPM in system

  @param[in] TxtContextDataPtr           - Point to TXT_PEI_LIB_CONTEXT structure
  @param[in] TxtPeiCtx      - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS          - If the TPM is present.
  @exception EFI_NOT_FOUND         - If the TPM is not present.
**/
EFI_STATUS
IsTpmPresent (
  IN TXT_PEI_LIB_CONTEXT *TxtContextDataPtr
  )
{
  EFI_STATUS Status;
  VOID       *TpmInitialize;

  ///
  /// Locate TPM Initialized Ppi to determine TPM is present and initialized properly.
  ///
  Status = PeiServicesLocatePpi (
             &gPeiTpmInitializedPpiGuid,
             0,
             NULL,
             (VOID **) &TpmInitialize
             );
  if (EFI_ERROR (Status)) {
    ///
    /// TPM initiated failed
    ///
    TxtContextDataPtr->Hob->Data.Flags |= TPM_INIT_FAILED;
  }

  return Status;
}

/**
  Clear Sleep Type register.

  @param[in] TxtContextDataPtr          - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS   - Always
**/
EFI_STATUS
ClearSlpTyp (
  IN TXT_PEI_LIB_CONTEXT *TxtContextDataPtr
  )
{
  UINT32 Pm1Addr;
  UINT32 Pm1Value;

  ///
  /// Make address for PM1_CNT
  ///
  Pm1Addr = ((UINT32) TxtContextDataPtr->Hob->Data.AcpiBase) + 4;

  ///
  /// Read 32-bits from PM1_CNT
  ///
  Pm1Value = IoRead32 ((UINTN) Pm1Addr);

  ///
  /// Clear SLP_TYP bits 10-12
  ///
  Pm1Value = Pm1Value & 0xffffe3ff;
  IoWrite32 (
    (UINTN) Pm1Addr,
    (UINT32) (Pm1Value)
    );

  return EFI_SUCCESS;
}

/**
  Issue a Global Reset
**/
VOID
IssueGlobalReset(
  VOID
  )
{
  PCH_RESET_DATA             ResetData;

  CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
  StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
  (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetPlatformSpecific, EFI_SUCCESS, sizeof (PCH_RESET_DATA), &ResetData);

  CpuDeadLoop();
}

/**
  Initializes values passed to AP

  @param[in] TxtContextDataPtr      - A pointer to an initialized TXT PEI Context data structure
**/
VOID
PrepareApParams (
  IN TXT_PEI_LIB_CONTEXT *TxtContextDataPtr
  )
{
  UINT32 TxtPublicSpace;

  TxtPublicSpace  = TXT_PUBLIC_BASE;

  *(UINT32 *) (TxtPublicSpace + BIOACM_ADDR)    = (UINT32) (TxtContextDataPtr->BiosAcmBase);
  *(UINT32 *) (TxtPublicSpace + APINIT_ADDR)    = (UINT32) (TxtContextDataPtr->ApStartup);
  *(UINT32 *) (TxtPublicSpace + SEMAPHORE)      = 0;
}

/**
  Invokes the SCLEAN/ACHECK function from the TXT BIOS ACM.
  1. Clearing of sleep type is necessary because SCLEAN/ACHECK destroys memory
  context, so S3 after it is run and system is reset is impossible. We
  do it here since there is no any indication that can sustain reset
  for any other module to do it on our behalf.
  2. APs are initialized before calling of SCLEAN/ACHECK
  3. SCLEAN/ACHECK function is invoked.

  @param[in] TxtContextDataPtr      - A pointer to an initialized TXT PEI Context data structure
  @param[in] func      - Acm function to be launch

  @retval EFI_SUCCESS   - Always.
**/
EFI_STATUS
DoAcmLaunch (
  IN TXT_PEI_LIB_CONTEXT *TxtContextDataPtr,
  IN UINT8               func
  )
{
  EFI_STATUS                    Status;
  SI_PREMEM_POLICY_PPI          *SiPreMemPolicy;
  CPU_SECURITY_PREMEM_CONFIG    *CpuSecurityPreMemConfig;

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicy
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  ClearSlpTyp (TxtContextDataPtr);

  PrepareApParams (TxtContextDataPtr);

  if (CpuSecurityPreMemConfig->SkipStopPbet != TRUE) {
    ///
    /// Disable PBET before send IPI to APs
    ///
    StopPbeTimer ();
  }

  if (func == TXT_LAUNCH_SCLEAN) {
    LaunchBiosAcmSclean ();
  } else if (func == TXT_LAUNCH_ACHECK) {
    LaunchBiosAcmAcheck ();
  }

  return EFI_SUCCESS;
}

/**
  Launching of SCHECK function from the TXT BIOS ACM.

  @param[in] TxtContextDataPtr         - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS     - Always.
**/
EFI_STATUS
DoPeiScheck (
  IN TXT_PEI_LIB_CONTEXT   *TxtContextDataPtr
  )
{
  ///
  /// ApCfg array contains 10 elements for 8 MTRRs + 10 element for
  /// IA32_MTRR_DEF_TYPE MTRR + 1 element for IDT + 1 element for
  /// IA32_MISC_ENABLE MSR
  ///
  UINT64  ApCfg[MSR_IA32_MTRR_PHYSMASK9 - MSR_IA32_MTRR_PHYSBASE0 + 4];
  UINT64  BiosAcAddr;
  UINT64  SavedSmiSourcesVariables[2];

  BiosAcAddr = (UINT64) (UINTN) (*TxtContextDataPtr).BiosAcmBase;
  SaveApConfig (ApCfg);
  DisableSmiSources (TxtContextDataPtr, SavedSmiSourcesVariables, TRUE);
#ifdef TXT_RLP_INIT
  StartupAllAPs (DoApInit, &BiosAcAddr);
#endif
  PutApsInWfs ();
  LaunchBiosAcmScheck (&BiosAcAddr);
  StartupAllAPs (RestoreApConfig, ApCfg);
  DisableSmiSources (TxtContextDataPtr, SavedSmiSourcesVariables, FALSE);
  RestoreMtrrProgramming (ApCfg);
  return EFI_SUCCESS;
}

/**
  Disable or restore possible SMI sources before or after SCHECK on S3 resume.

  @param[in] TxtContextDataPtr               - A pointer to an initialized TXT PEI Context data structure
  @param[in] SavedSmiSourcesVariablesPointer - Saved SMI source Variable
  @param[in] Operation
                                             - Boolean value telling what operation is requested:
                                             - TRUE: save and then disable possible SMI sources.
                                             - FALSE: restore original SMI settings.

  @retval EFI_SUCCESS   - Always.
**/
EFI_STATUS
DisableSmiSources (
  IN TXT_PEI_LIB_CONTEXT   *TxtContextDataPtr,
  IN UINT64*               SavedSmiSourcesVariablesPointer,
  IN BOOLEAN               Operation
  )
{
  UINT64        GlobalSmiControlIoAddr;
  UINT32        SavedSmiControl;
  UINT64        SavedIa32ThermInterruptMsr;

  GlobalSmiControlIoAddr = (*TxtContextDataPtr).Hob->Data.AcpiBase + 0x30;

  if (Operation == TRUE) {
    SavedIa32ThermInterruptMsr = AsmReadMsr64 ((UINT32) MSR_IA32_THERM_INTERRUPT);
    //
    // Cannot use static variables because of PEI phase, static variables would be in code region which is read-only.
    //
    *SavedSmiSourcesVariablesPointer = SavedIa32ThermInterruptMsr;
    AsmWriteMsr64 (
      (UINT32) MSR_IA32_THERM_INTERRUPT,
      (UINT64) (SavedIa32ThermInterruptMsr & ~(BIT0 + BIT1 + BIT2 + BIT4 + BIT15 + BIT23))
      );
    SavedSmiControl = IoRead32 ((UINTN) GlobalSmiControlIoAddr);
    *((UINT64 *) (SavedSmiSourcesVariablesPointer + 1)) = SavedSmiControl;
    //
    // We can not disable Global SMI since it should be locked after SCHECK. we can only disable SMI sources individually.
    //

    IoWrite32 ((UINTN) GlobalSmiControlIoAddr, (UINT32) (SavedSmiControl & 0x01));
  } else {
    //
    // We can not disable Global SMI since it should be locked after SCHECK. we can only disable SMI sources individually.
    // Restore original SMI setting after SCHECK
    //

    SavedSmiControl = (UINT32) *((UINT64 *) (SavedSmiSourcesVariablesPointer + 1));
    IoWrite32 (
      (UINTN) GlobalSmiControlIoAddr,
      (UINT32) (SavedSmiControl)
      );

    SavedIa32ThermInterruptMsr = *SavedSmiSourcesVariablesPointer;
    //
    // Restore IA32_THERMAL_INTERRUPT MSR
    //
    AsmWriteMsr64 (
      (UINT32) MSR_IA32_THERM_INTERRUPT,
      (UINT64) SavedIa32ThermInterruptMsr
      );
  }

  return EFI_SUCCESS;
}

/**
  Unlock memory when security is set and TxT is not enabled

  @param[in] TxtContextDataPtr      - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS  - If address has been found
  @exception EFI_UNSUPPORTED - CPU doesn't support TxT.
**/
EFI_STATUS
TxtUnlockMemory (
  IN TXT_PEI_LIB_CONTEXT *TxtContextDataPtr
  )
{
  BOOLEAN EstablishmentBitAsserted;

  EstablishmentBitAsserted = TxtIsEstablishmentBitAsserted (TxtContextDataPtr);

  ///
  /// Need to read FED40000 before unlocking memory
  ///
  if (!EstablishmentBitAsserted) {
    DEBUG ((DEBUG_INFO, "TXTPEI::Unlock memory\n"));
    AsmWriteMsr64 (MSR_LT_UNLOCK_MEMORY, 0);
  } else {
    ///
    /// Lunch SCLEAN if wake error bit is set.
    ///
    if (IsTxtWakeError ()) {
      ///
      /// If TXTRESET is set , we must clean TXTRESET bit otherwise SCLEAN
      /// will fail
      ///
      if (IsTxtResetSet ()) {
        IssueGlobalReset ();
      }

      if ((TxtContextDataPtr->BiosAcmBase == 0) || (TxtContextDataPtr->ApStartup == 0)) {
        return EFI_UNSUPPORTED;
      }
      ///
      /// Setup and Launch SCLEAN
      ///
      DEBUG ((DEBUG_INFO, "TXTPEI::Entering SCLEAN to unlock memory\n"));
      DoAcmLaunch (TxtContextDataPtr, TXT_LAUNCH_SCLEAN);

      ///
      /// Reset platform - performed by DoSclean, should not return to execute the following dead looping
      ///
      CpuDeadLoop ();
    } else {
      return EFI_UNSUPPORTED;
    }
  }

  return EFI_SUCCESS;
}
