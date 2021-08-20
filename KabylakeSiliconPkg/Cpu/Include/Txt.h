/** @file
  This file contains definitions required to use the TXT BIOS
  Authenticated Code Module Library.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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
#ifndef _TXT_BIOS_ACM_LIB_H_
#define _TXT_BIOS_ACM_LIB_H_

#define TPM_TIME_OUT  750

//
// TxT BIOS Spec version
//
#define TXT_BIOS_SPEC_VER_MAJOR     2
#define TXT_BIOS_SPEC_VER_MINOR     1
#define TXT_BIOS_SPEC_VER_REVISION  0

//
// TXT HEAP extended data type
//
#define HEAP_EXTDATA_TYPE_END           0
#define HEAP_EXTDATA_TYPE_BIOS_SPEC_VER 1
#define HEAP_EXTDATA_TYPE_BIOSACM       2
#define BIOS_OS_DATAREGION_VERSION      6

//
// The following are values that are placed in the esi register when
// calling the BIOS ACM.  These constants are used as parameters to the
// TxtSetupandLaunchBiosAcm function.
//
#define TXT_LAUNCH_SCLEAN         0x00
#define TXT_RESET_EST_BIT         0x01
#define TXT_RESET_AUX             0x02
#define TXT_LAUNCH_SCHECK         0x04
#define TXT_LAUNCH_ACHECK         0x07

#define TPM_STATUS_REG_ADDRESS    0xFED40000
#define TXT_PUBLIC_BASE           0xFED30000
#define TXT_PRIVATE_BASE          0xFED20000
#define TXT_CONFIG_SPACE_LENGTH   0x60000

#define TXT_ERROR_STATUS_REG_OFF  0x8
#define TXT_CRASHCODE_REG_OFF     0x30
#define TXT_SINIT_BASE_REG_OFF    0x270
#define TXT_SINIT_SIZE_REG_OFF    0x278
#define TXT_SINIT_SIZE_REG_OFF2   0x27C
#define TXT_SVMM_JOIN_REG_OFF     0x290
#define TXT_SVMM_JOIN_REG_OFF2    0x294
#define TXT_HEAP_BASE_REG_OFF     0x300
#define TXT_HEAP_SIZE_REG_OFF     0x308
#define TXT_SCRATCHPAD          0x320
#define TXT_SCRATCHPAD2         0x324
#define TXT_SCRATCHPAD3         0x328
#define TXT_SCRATCHPAD4         0x32C
#define TXT_DPR_SIZE_REG_OFF    0x330

#define TXT_PTT_FTIF_OFF        0x800
#define TXT_PTT_PRESENT         0x70000

#define TXT_E2STS_REG_OFF       0x8F0
#define TXT_BLOCK_MEM_STS       BIT2
#define TXT_SECRETS_STS         BIT1
#define TXT_SLP_ENTRY_ERROR_STS BIT0

#define BIOACM_ADDR             TXT_SINIT_SIZE_REG_OFF2
#define APINIT_ADDR             TXT_SVMM_JOIN_REG_OFF
#define SEMAPHORE               TXT_SVMM_JOIN_REG_OFF2

///
/// BIOS ACM GUID. BIOS ACM interface is described in Intel Trusted Execution Technology BIOS Specification
/// @pre BIOS ACM must be placed in flash part on 4KB boundary
///
extern EFI_GUID gTxtBiosAcmPeiFileGuid;
extern EFI_GUID gTxtApStartupPeiFileGuid;
extern EFI_GUID gCpuMicrocodeFileGuid;


#pragma pack(push, 1)
///
/// HEAP Extended data elements
///
typedef struct {
  UINT32 Type; ///< Type of HEAP extended data element
  UINT32 Size; ///< Size of HEAP extended data element
} HEAP_EXT_DATA_ELEMENT;

///
/// BIOS spec version element
///
typedef struct {
  HEAP_EXT_DATA_ELEMENT Header;          ///< Header of HEAP extended data. Header.Type = <b>1</b>.
  UINT16                SpecVerMajor;    ///< Major number of TXT BIOS spec version
  UINT16                SpecVerMinor;    ///< Minor number of TXT BIOS spec version
  UINT16                SpecVerRevision; ///< Revision number of TXT BIOS spec version
} HEAP_BIOS_SPEC_VER_ELEMENT;

///
/// BIOS ACM element
///
typedef struct {
  HEAP_EXT_DATA_ELEMENT Header;  ///< Header of HEAP extended data. Header.Type = <b>2</b>.
  UINT32                NumAcms; ///< Number of BIOS ACMs carried by BIOS
} HEAP_BIOSACM_ELEMENT;

///
/// BIOS OS Data region definitions
///
typedef struct {
  UINT32                Version;                 ///< Version number of the BIOS to OS data
  /**
  This field indicates the size of the SINIT AC module stored in system firmware.
  A value of 0 indicates the system firmware is not providing a SINIT module for OS use.
  **/
  UINT32                BiosSinitSize;
  /**
  Physical base address of the Platform Default Launch Control Policy structure.
  If the Platform Default Policy does not require additional data this field should
  be set to 0x00 and will be ignored.
  **/
  EFI_PHYSICAL_ADDRESS  LcpPdBase;
  /**
  Size of the Launch Control Policy Platform Default Policy Data.
  If the Platform Default Policy does not require additional data this field should
  be set to 0x00 and will be ignored.
  **/
  UINT64                LcpPdSize;
  UINT32                NumOfLogicalProcessors;  ///< The total number of logical processors in the system. The minimum value in this register must be at least <b>0x01</b>.
  UINT64                Flags;                   ///< BIOS provided info for SINIT consumption
  HEAP_EXT_DATA_ELEMENT ExtData;                 ///< Array/list of extended data element structures
} BIOS_OS_DATA_REGION;

#pragma pack(pop)
#endif
