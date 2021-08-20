/** @file
  HPET policy

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

@par Specification Reference:
**/
#ifndef _HPET_CONFIG_H_
#define _HPET_CONFIG_H_

#define HPET_PREMEM_CONFIG_REVISION 1
extern EFI_GUID gHpetPreMemConfigGuid;

#pragma pack (push,1)

/**
  The PCH_HPET_CONFIG block passes the bus/device/function value for HPET.
  The address resource range of HPET must be reserved in E820 and ACPI as
  system resource.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;         ///< Config Block Header
  /**
    Determines if enable HPET timer. 0: Disable; <b>1: Enable</b>.
    The HPET timer address decode is always enabled.
    This policy is used to configure the HPET timer count, and also the _STA of HPET device in ACPI.
    While enabled, the HPET timer is started, else the HPET timer is halted.
  **/
  UINT32   Enable             :  1;
  UINT32   BdfValid           :  1;     ///< Whether the BDF value is valid. <b>0: Disable</b>; 1: Enable.
  UINT32   RsvdBits0          :  6;     ///< Reserved bits
  UINT32   BusNumber          :  8;     ///< Bus Number HPETn used as Requestor / Completer ID. Default is <b>0xF0</b>.
  UINT32   DeviceNumber       :  5;     ///< Device Number HPETn used as Requestor / Completer ID. Default is <b>0x1F</b>.
  UINT32   FunctionNumber     :  3;     ///< Function Number HPETn used as Requestor / Completer ID. Default is <b>0x00</b>.
  UINT32   RsvdBits1          :  8;     ///< Reserved bits
  UINT32   Base;                        ///< The HPET base address. Default is <b>0xFED00000</b>.
} PCH_HPET_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _HPET_CONFIG_H_
