/** @file
  This file contains the required header files for the HSTI Silicon DXE driver

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

#ifndef _HSTI_SILICON_DXE_H_
#define _HSTI_SILICON_DXE_H_

#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/MpService.h>
#include <Library/PciLib.h>
#include <Library/TimerLib.h>
#include <Library/IoLib.h>
#include <Guid/EventGroup.h>
#include <Library/UefiLib.h>
#include <Protocol/TrEEProtocol.h>
#include <Protocol/SiPolicyProtocol.h>
#include <IndustryStandard/Hsti.h>
#include <Protocol/AdapterInformation.h>
#include <Library/HstiLib.h>
#include <HstiFeatureBit.h>
#include <Fit.h>
#include <Protocol/Spi.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/HobLib.h>
#include <Library/PchPcrLib.h>
#include <Library/MmPciLib.h>
#include <Library/PchP2sbLib.h>

#ifndef TPM_BASE
#define TPM_BASE                  0
#endif
#include <Library/Tpm2CommandLib.h>

#define TPM_BASE_ADDRESS            0xfed40000

//
// Silicon
//
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <SaRegs.h>
#include <SaAccess.h>
#include <PchAccess.h>
#include <MeChipset.h>
#include <MemInfoHob.h>
#include <Library/PchGbeLib.h>
#include <Library/CpuPlatformLib.h>

#define  SIZE_4KB    0x00001000
#define  SIZE_16KB   0x00004000
#define  SIZE_32KB   0x00008000
#define  SIZE_1MB    0x00100000
#define  SIZE_2MB    0x00200000
#define  SIZE_4MB    0x00400000
#define  SIZE_8MB    0x00800000
#define  SIZE_16MB   0x01000000
#define  SIZE_32MB   0x02000000
#define  SIZE_128MB  0x08000000
#define  SIZE_4GB    0x0000000100000000ULL
#define  BASE_4GB    0x0000000100000000ULL
//@todo need to take this back to ClientSiliconPkg HstiFeatureBit.h
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_ERROR_STRING_B                   L" SMM Code Fetch outside SMRAM detection feature is disabled\r\n"

//@todo need to take this back to ClientSiliconPkg HstiFeatureBit.h
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_ERROR_CODE_4                     L"0x000A0004"
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_ERROR_STRING_4                   L" P2SB SBI lock not set\r\n"

#define MAX_NEW_AUTHORIZATION_SIZE        SHA512_DIGEST_SIZE

#define HSTI_PLATFORM_NAME  L"Intel(R) 9-Series v1"

#pragma pack(1)
typedef struct {
  UINT32  Version;
  UINT32  Role;
  CHAR16  ImplementationID[256];
  UINT32  SecurityFeaturesSize;
  UINT8   SecurityFeaturesRequired[HSTI_SECURITY_FEATURE_SIZE];
  UINT8   SecurityFeaturesImplemented[HSTI_SECURITY_FEATURE_SIZE];
  UINT8   SecurityFeaturesVerified[HSTI_SECURITY_FEATURE_SIZE];
  CHAR16  End;
} ADAPTER_INFO_PLATFORM_SECURITY_STRUCT;
#pragma pack()

extern UINT8  mFeatureImplemented[HSTI_SECURITY_FEATURE_SIZE];
extern EFI_GUID gHstiProtocolGuid;
extern EFI_GUID gHstiPublishCompleteProtocolGuid;

/**
  Concatenate error string.

  @param[in] ErrorCodeString     - Error Code
  @param[in] ErrorCategoryString - Error Category
  @param[in] ErrorString         - Error Text

  @retval CHAR16 - Concatenated string.
**/
CHAR16 *
EFIAPI
BuildHstiErrorString (
  IN  CHAR16                   *ErrorCodeString,
  IN  CHAR16                   *ErrorCategoryString,
  IN  CHAR16                   *ErrorString
  );

/**
  Run tests for HardwareRootedBootIntegrity bit
**/
VOID
CheckHardwareRootedBootIntegrity (
  VOID
  );

/**
  Run tests for BootFirmwareMediaProtection bit
**/
VOID
CheckBootFirmwareMediaProtection (
  VOID
  );

/**
  Run tests for SignedFirmwareUpdate bit
**/
VOID
CheckSignedFirmwareUpdate (
  VOID
  );

/**
  Run tests for MeasuredBootEnforcement bit
**/
VOID
CheckMeasuredBootEnforcement (
  VOID
  );

/**
  Run tests for IntegratedDeviceDMAProtection bit
**/
VOID
CheckIntegratedDeviceDmaProtection (
  VOID
  );

/**
  Run tests for DebugModeDisabled bit
**/
VOID
CheckDebugModeDisabled (
  VOID
  );

/**
  Run tests for SecureCPUConfiguration bit
**/
VOID
CheckSecureCpuConfiguration (
  VOID
  );

/**
  Run tests for SecureSystemAgentConfiguration bit
**/
VOID
CheckSecureSystemAgentConfiguration (
  VOID
  );

/**
  Run tests for SecureMemoryMapConfiguration bit
**/
VOID
CheckSecureMemoryMapConfiguration (
  VOID
  );

/**
  Run tests for SecureIntegratedGraphicsConfiguration bit
**/
VOID
CheckSecureIntegratedGraphicsConfiguration (
  VOID
  );

/**
  Run tests for SecurePCHConfiguration bit
**/
VOID
CheckSecurePchConfiguration (
  VOID
  );

//
// Help function
//

/**
  Initialize MP Helper
**/
VOID
InitMp (
  VOID
  );

/**
  Concatenate error string.

  @retval UINTN - CpuNumber.
**/
UINTN
GetCpuNumber (
  VOID
  );


/**
  Read each processor MSR value.

  @param[in] ProcessorNumber     - Processor ID
  @param[in] Index               - Index

  @retval UINT64 - Msr Value.
**/
UINT64
ProcessorReadMsr64 (
  IN UINTN   ProcessorNumber,
  IN UINT32  Index
  );

/**
  Write value to each processor MSR.

  @param[in] ProcessorNumber     - Processor ID
  @param[in] Index               - Index
  @param[in] Value               - Value

**/
VOID
ProcessorWriteMsr64 (
  IN UINTN   ProcessorNumber,
  IN UINT32  Index,
  IN UINTN   Value
  );

/**
  Concatenate error string.

  @param[in]  ProcessorNumber     - Processor ID
  @param[in]  Index               - Index
  @param[out] Eax                 - Eax
  @param[out] Ebx                 - Ebx
  @param[out] Ecx                 - Ecx
  @param[out] Edx                 - Edx
**/
VOID
ProcessorCpuid (
  IN  UINTN   ProcessorNumber,
  IN  UINT32  Index,
  OUT UINT32  *Eax,  OPTIONAL
  OUT UINT32  *Ebx,  OPTIONAL
  OUT UINT32  *Ecx,  OPTIONAL
  OUT UINT32  *Edx   OPTIONAL
  );

/**
  Concatenate error string.

  @param[in] Address     - Address

  @retval UINT64 - Value.
**/
UINT64
EFIAPI
PciRead64 (
  IN      UINTN                     Address
  );

#endif
