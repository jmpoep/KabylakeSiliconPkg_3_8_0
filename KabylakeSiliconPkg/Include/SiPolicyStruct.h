/** @file
  Intel reference code configuration policies.

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

@par Specification Reference:
**/
#ifndef _SI_POLICY_STRUCT_H_
#define _SI_POLICY_STRUCT_H_

#include <ConfigBlock.h>

/**
  Silicon Policy revision number
  Any change to this structure will result in an update in the revision number

  This member specifies the revision of the Silicon Policy. This field is used to indicate change
  to the policy structure.

  <b>Revision 1</b>:
   - Initial version.
**/
#define SI_POLICY_REVISION  1
#define SI_CONFIG_REVISION  1

/**
  Silicon pre-memory Policy revision number
  Any change to this structure will result in an update in the revision number

  <b>Revision 1</b>:
   - Initial version.
**/
#define SI_PREMEM_POLICY_REVISION  1

extern EFI_GUID gSiConfigGuid;

/**
  The Silicon Policy allows the platform code to publish a set of configuration
  information that the RC drivers will use to configure the silicon hardware.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header; ///< Offset 0 - 27 Config Block Header
  //
  // Platform specific common policies that used by several silicon components.
  //
  ///
  /// Offset 28 The minimum temporary bus number available to be assigned to each root port and its downstream
  /// devices for initialization of these devices before PCI Bus enumeration.
  ///
  UINT8  TempPciBusMin;
  ///
  /// Offset 29 The maximum temporary bus number available to be assigned to each root port and its downstream
  /// devices for initialization of these devices before PCI Bus enumeration.
  ///
  UINT8  TempPciBusMax;
  UINT8  Rsvd0[2];         ///< Offset 30 - 31 Reserved bytes, align to multiple 4.
  ///
  /// Offset 32 Temporary Memory Base Address for PCI devices to be used to initialize MMIO registers.
  /// Minimum size is 2MB bytes
  ///
  UINT32 TempMemBaseAddr;
  ///
  /// Offset 36 Size of allocated temp MMIO space
  ///
  UINT32 TempMemSize;
  ///
  /// Offset 40 Temporary IO Base Address for PCI devices to be used to initialize IO registers.
  ///
  UINT16 TempIoBaseAddr;
  UINT16 TempIoSize;           ///< Offset 42 Size of temporary IO space
  UINT32 CsmFlag          :1;  ///< Offset 44 BIT0: CSM status flag.
  UINT32 RsvdBits         :31; ///< Reserved
} SI_CONFIG;

/**
  SI Policy PPI in Pre-Mem\n
  All SI config block change history will be listed here\n\n

  - <b>Revision 1</b>:
    - Initial version.\n
**/
struct _SI_PREMEM_POLICY_STRUCT {
  CONFIG_BLOCK_TABLE_HEADER      TableHeader;
/*
  Individual Config Block Structures are added here in memory as part of AddConfigBlock()
*/
};

/**
  SI Policy PPI\n
  All SI config block change history will be listed here\n\n

  - <b>Revision 1</b>:
    - Initial version.\n
**/
struct _SI_POLICY_STRUCT {
  CONFIG_BLOCK_TABLE_HEADER      TableHeader;
/*
  Individual Config Block Structures are added here in memory as part of AddConfigBlock()
*/
};

#endif
