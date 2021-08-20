/** @file
  This file contains definitions for FIT table entries
  including error string definitions

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification
**/

#ifndef __FIT_H__
#define __FIT_H__
//
// FIT definition
//
#define FIT_TABLE_TYPE_HEADER         0
#define FIT_TABLE_TYPE_MICROCODE      1
#define FIT_TABLE_TYPE_STARTUP_ACM    2
#define FIT_TABLE_TYPE_BIOS_MODULE    7
#define FIT_TABLE_TYPE_TPM_POLICY     8
#define FIT_TABLE_TYPE_BIOS_POLICY    9
#define FIT_TABLE_TYPE_TXT_POLICY     10
#define FIT_TABLE_TYPE_SKIP           0x7F

#define FIT_TABLE_TYPE_KEY_MANIFEST           11
#define FIT_TABLE_TYPE_BOOT_POLICY_MANIFEST   12

typedef struct {
  UINT64 Address;
  UINT8  Size[3];
  UINT8  Reserved;
  UINT16 Version;
  UINT8  Type : 7;
  UINT8  Cv   : 1;
  UINT8  Chksum;
} FIRMWARE_INTERFACE_TABLE_ENTRY;
#endif
