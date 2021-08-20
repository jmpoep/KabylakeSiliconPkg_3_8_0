/** @file
  Definition for EM64T processor

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2016 Intel Corporation.

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

#ifndef _PROCESSOR_DEF_H
#define _PROCESSOR_DEF_H

#pragma pack(1)

typedef struct {
  UINT16  Offset15To0;
  UINT16  SegmentSelector;
  UINT16  Attributes;
  UINT16  Offset31To16;
  UINT32  Offset63To32;
  UINT32  Reserved;
} INTERRUPT_GATE_DESCRIPTOR;

#pragma pack()

typedef struct {
  UINT8 *RendezvousFunnelAddress;
  UINTN PModeEntryOffset;
  UINTN FlatJumpOffset;
  UINTN LModeEntryOffset;
  UINTN LongJumpOffset;
  UINTN Size;
} MP_ASSEMBLY_ADDRESS_MAP;

/**
  Get address map of RendezvousFunnelProc.

  @param[in] AddressMap  - Output buffer for address map information
**/
VOID
AsmGetAddressMap (
  OUT MP_ASSEMBLY_ADDRESS_MAP    *AddressMap
  );

#endif
