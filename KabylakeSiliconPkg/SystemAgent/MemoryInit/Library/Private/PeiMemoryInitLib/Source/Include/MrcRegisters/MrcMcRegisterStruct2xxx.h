#ifndef __MrcMcRegisterStruct2xxx_h__
#define __MrcMcRegisterStruct2xxx_h__
/** @file
  This file was automatically generated. Modify at your own risk.
  Note that no error checking is done in these functions so ensure that the correct values are passed.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

#pragma pack(push, 1)

typedef union {
  struct {
    UINT32 ScramEn                                 :  1;  // Bits 0:0
    UINT32 ScramKey                                :  16;  // Bits 16:1
    UINT32 ClockGateAB                             :  2;  // Bits 18:17
    UINT32 ClockGateC                              :  2;  // Bits 20:19
    UINT32 EnableDbiAB                             :  1;  // Bits 21:21
    UINT32 Spare                                   :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRSCRAMBLECH0_STRUCT;

typedef union {
  struct {
    UINT32 ScramEn                                 :  1;  // Bits 0:0
    UINT32 ScramKey                                :  16;  // Bits 16:1
    UINT32 ClockGateAB                             :  2;  // Bits 18:17
    UINT32 ClockGateC                              :  2;  // Bits 20:19
    UINT32 EnableDbiAB                             :  1;  // Bits 21:21
    UINT32 Spare                                   :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRSCRAMBLECH1_STRUCT;

typedef union {
  struct {
    UINT32 WL_WakeCycles                           :  2;  // Bits 1:0
    UINT32 WL_SleepCycles                          :  3;  // Bits 4:2
    UINT32 ForceCompUpdate                         :  1;  // Bits 5:5
    UINT32 WeakLock_Latency                        :  4;  // Bits 9:6
    UINT32 DdrNoChInterleave                       :  1;  // Bits 10:10
    UINT32 LPDDR_Mode                              :  1;  // Bits 11:11
    UINT32 CKEMappingCh0                           :  4;  // Bits 15:12
    UINT32 CKEMappingCh1                           :  4;  // Bits 19:16
    UINT32 Ddr4_Mode                               :  1;  // Bits 20:20
    UINT32 ClkGateDisable                          :  1;  // Bits 21:21
    UINT32 DllDataWeakLckEn                        :  1;  // Bits 22:22
    UINT32 DataClkGateDisAtIdle                    :  1;  // Bits 23:23
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRMISCCONTROL0_STRUCT;

#pragma pack(pop)
#endif
