#ifndef __MrcMcRegister3xxx_h__
#define __MrcMcRegister3xxx_h__
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


#define DDRDATACH0_CR_RXTRAINRANK0_REG                                 (0x00003000)

  #define DDRDATACH0_CR_RXTRAINRANK0_RxRcvEnPi_OFF                     ( 0)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxRcvEnPi_WID                     ( 9)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxRcvEnPi_MSK                     (0x000001FF)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxRcvEnPi_MIN                     (0)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxRcvEnPi_MAX                     (511) // 0x000001FF
  #define DDRDATACH0_CR_RXTRAINRANK0_RxRcvEnPi_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxRcvEnPi_HSH                     (0x09003000)

  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsPPi_OFF                      ( 9)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsPPi_WID                      ( 6)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsPPi_MSK                      (0x00007E00)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsPPi_MIN                      (0)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsPPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsPPi_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsPPi_HSH                      (0x06093000)

  #define DDRDATACH0_CR_RXTRAINRANK0_RxEq_OFF                          (15)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxEq_WID                          ( 5)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxEq_MSK                          (0x000F8000)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxEq_MIN                          (0)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxEq_MAX                          (31) // 0x0000001F
  #define DDRDATACH0_CR_RXTRAINRANK0_RxEq_DEF                          (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxEq_HSH                          (0x050F3000)

  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsNPi_OFF                      (20)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsNPi_WID                      ( 6)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsNPi_MSK                      (0x03F00000)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsNPi_MIN                      (0)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsNPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsNPi_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxDqsNPi_HSH                      (0x06143000)

  #define DDRDATACH0_CR_RXTRAINRANK0_RxVref_OFF                        (26)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxVref_WID                        ( 6)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxVref_MSK                        (0xFC000000)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxVref_MIN                        (-32)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxVref_MAX                        (31) // 0x0000001F
  #define DDRDATACH0_CR_RXTRAINRANK0_RxVref_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK0_RxVref_HSH                        (0x861A3000)

#define DDRDATACH0_CR_RXTRAINRANK1_REG                                 (0x00003004)

  #define DDRDATACH0_CR_RXTRAINRANK1_RxRcvEnPi_OFF                     ( 0)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxRcvEnPi_WID                     ( 9)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxRcvEnPi_MSK                     (0x000001FF)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxRcvEnPi_MIN                     (0)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxRcvEnPi_MAX                     (511) // 0x000001FF
  #define DDRDATACH0_CR_RXTRAINRANK1_RxRcvEnPi_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxRcvEnPi_HSH                     (0x09003004)

  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsPPi_OFF                      ( 9)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsPPi_WID                      ( 6)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsPPi_MSK                      (0x00007E00)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsPPi_MIN                      (0)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsPPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsPPi_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsPPi_HSH                      (0x06093004)

  #define DDRDATACH0_CR_RXTRAINRANK1_RxEq_OFF                          (15)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxEq_WID                          ( 5)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxEq_MSK                          (0x000F8000)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxEq_MIN                          (0)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxEq_MAX                          (31) // 0x0000001F
  #define DDRDATACH0_CR_RXTRAINRANK1_RxEq_DEF                          (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxEq_HSH                          (0x050F3004)

  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsNPi_OFF                      (20)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsNPi_WID                      ( 6)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsNPi_MSK                      (0x03F00000)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsNPi_MIN                      (0)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsNPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsNPi_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxDqsNPi_HSH                      (0x06143004)

  #define DDRDATACH0_CR_RXTRAINRANK1_RxVref_OFF                        (26)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxVref_WID                        ( 6)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxVref_MSK                        (0xFC000000)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxVref_MIN                        (-32)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxVref_MAX                        (31) // 0x0000001F
  #define DDRDATACH0_CR_RXTRAINRANK1_RxVref_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK1_RxVref_HSH                        (0x861A3004)

#define DDRDATACH0_CR_RXTRAINRANK2_REG                                 (0x00003008)

  #define DDRDATACH0_CR_RXTRAINRANK2_RxRcvEnPi_OFF                     ( 0)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxRcvEnPi_WID                     ( 9)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxRcvEnPi_MSK                     (0x000001FF)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxRcvEnPi_MIN                     (0)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxRcvEnPi_MAX                     (511) // 0x000001FF
  #define DDRDATACH0_CR_RXTRAINRANK2_RxRcvEnPi_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxRcvEnPi_HSH                     (0x09003008)

  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsPPi_OFF                      ( 9)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsPPi_WID                      ( 6)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsPPi_MSK                      (0x00007E00)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsPPi_MIN                      (0)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsPPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsPPi_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsPPi_HSH                      (0x06093008)

  #define DDRDATACH0_CR_RXTRAINRANK2_RxEq_OFF                          (15)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxEq_WID                          ( 5)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxEq_MSK                          (0x000F8000)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxEq_MIN                          (0)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxEq_MAX                          (31) // 0x0000001F
  #define DDRDATACH0_CR_RXTRAINRANK2_RxEq_DEF                          (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxEq_HSH                          (0x050F3008)

  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsNPi_OFF                      (20)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsNPi_WID                      ( 6)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsNPi_MSK                      (0x03F00000)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsNPi_MIN                      (0)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsNPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsNPi_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxDqsNPi_HSH                      (0x06143008)

  #define DDRDATACH0_CR_RXTRAINRANK2_RxVref_OFF                        (26)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxVref_WID                        ( 6)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxVref_MSK                        (0xFC000000)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxVref_MIN                        (-32)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxVref_MAX                        (31) // 0x0000001F
  #define DDRDATACH0_CR_RXTRAINRANK2_RxVref_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK2_RxVref_HSH                        (0x861A3008)

#define DDRDATACH0_CR_RXTRAINRANK3_REG                                 (0x0000300C)

  #define DDRDATACH0_CR_RXTRAINRANK3_RxRcvEnPi_OFF                     ( 0)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxRcvEnPi_WID                     ( 9)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxRcvEnPi_MSK                     (0x000001FF)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxRcvEnPi_MIN                     (0)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxRcvEnPi_MAX                     (511) // 0x000001FF
  #define DDRDATACH0_CR_RXTRAINRANK3_RxRcvEnPi_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxRcvEnPi_HSH                     (0x0900300C)

  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsPPi_OFF                      ( 9)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsPPi_WID                      ( 6)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsPPi_MSK                      (0x00007E00)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsPPi_MIN                      (0)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsPPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsPPi_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsPPi_HSH                      (0x0609300C)

  #define DDRDATACH0_CR_RXTRAINRANK3_RxEq_OFF                          (15)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxEq_WID                          ( 5)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxEq_MSK                          (0x000F8000)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxEq_MIN                          (0)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxEq_MAX                          (31) // 0x0000001F
  #define DDRDATACH0_CR_RXTRAINRANK3_RxEq_DEF                          (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxEq_HSH                          (0x050F300C)

  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsNPi_OFF                      (20)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsNPi_WID                      ( 6)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsNPi_MSK                      (0x03F00000)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsNPi_MIN                      (0)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsNPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsNPi_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxDqsNPi_HSH                      (0x0614300C)

  #define DDRDATACH0_CR_RXTRAINRANK3_RxVref_OFF                        (26)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxVref_WID                        ( 6)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxVref_MSK                        (0xFC000000)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxVref_MIN                        (-32)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxVref_MAX                        (31) // 0x0000001F
  #define DDRDATACH0_CR_RXTRAINRANK3_RxVref_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXTRAINRANK3_RxVref_HSH                        (0x861A300C)

#define DDRDATACH0_CR_RXPERBITRANK0_REG                                (0x00003010)

  #define DDRDATACH0_CR_RXPERBITRANK0_Lane0_OFF                        ( 0)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane0_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane0_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane0_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane0_HSH                        (0x04003010)

  #define DDRDATACH0_CR_RXPERBITRANK0_Lane1_OFF                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane1_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane1_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane1_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane1_HSH                        (0x04043010)

  #define DDRDATACH0_CR_RXPERBITRANK0_Lane2_OFF                        ( 8)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane2_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane2_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane2_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane2_HSH                        (0x04083010)

  #define DDRDATACH0_CR_RXPERBITRANK0_Lane3_OFF                        (12)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane3_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane3_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane3_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane3_HSH                        (0x040C3010)

  #define DDRDATACH0_CR_RXPERBITRANK0_Lane4_OFF                        (16)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane4_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane4_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane4_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane4_HSH                        (0x04103010)

  #define DDRDATACH0_CR_RXPERBITRANK0_Lane5_OFF                        (20)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane5_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane5_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane5_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane5_HSH                        (0x04143010)

  #define DDRDATACH0_CR_RXPERBITRANK0_Lane6_OFF                        (24)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane6_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane6_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane6_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane6_HSH                        (0x04183010)

  #define DDRDATACH0_CR_RXPERBITRANK0_Lane7_OFF                        (28)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane7_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane7_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane7_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK0_Lane7_HSH                        (0x041C3010)

#define DDRDATACH0_CR_RXPERBITRANK1_REG                                (0x00003014)

  #define DDRDATACH0_CR_RXPERBITRANK1_Lane0_OFF                        ( 0)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane0_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane0_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane0_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane0_HSH                        (0x04003014)

  #define DDRDATACH0_CR_RXPERBITRANK1_Lane1_OFF                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane1_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane1_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane1_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane1_HSH                        (0x04043014)

  #define DDRDATACH0_CR_RXPERBITRANK1_Lane2_OFF                        ( 8)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane2_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane2_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane2_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane2_HSH                        (0x04083014)

  #define DDRDATACH0_CR_RXPERBITRANK1_Lane3_OFF                        (12)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane3_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane3_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane3_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane3_HSH                        (0x040C3014)

  #define DDRDATACH0_CR_RXPERBITRANK1_Lane4_OFF                        (16)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane4_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane4_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane4_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane4_HSH                        (0x04103014)

  #define DDRDATACH0_CR_RXPERBITRANK1_Lane5_OFF                        (20)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane5_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane5_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane5_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane5_HSH                        (0x04143014)

  #define DDRDATACH0_CR_RXPERBITRANK1_Lane6_OFF                        (24)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane6_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane6_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane6_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane6_HSH                        (0x04183014)

  #define DDRDATACH0_CR_RXPERBITRANK1_Lane7_OFF                        (28)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane7_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane7_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane7_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK1_Lane7_HSH                        (0x041C3014)

#define DDRDATACH0_CR_RXPERBITRANK2_REG                                (0x00003018)

  #define DDRDATACH0_CR_RXPERBITRANK2_Lane0_OFF                        ( 0)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane0_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane0_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane0_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane0_HSH                        (0x04003018)

  #define DDRDATACH0_CR_RXPERBITRANK2_Lane1_OFF                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane1_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane1_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane1_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane1_HSH                        (0x04043018)

  #define DDRDATACH0_CR_RXPERBITRANK2_Lane2_OFF                        ( 8)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane2_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane2_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane2_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane2_HSH                        (0x04083018)

  #define DDRDATACH0_CR_RXPERBITRANK2_Lane3_OFF                        (12)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane3_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane3_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane3_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane3_HSH                        (0x040C3018)

  #define DDRDATACH0_CR_RXPERBITRANK2_Lane4_OFF                        (16)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane4_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane4_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane4_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane4_HSH                        (0x04103018)

  #define DDRDATACH0_CR_RXPERBITRANK2_Lane5_OFF                        (20)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane5_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane5_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane5_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane5_HSH                        (0x04143018)

  #define DDRDATACH0_CR_RXPERBITRANK2_Lane6_OFF                        (24)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane6_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane6_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane6_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane6_HSH                        (0x04183018)

  #define DDRDATACH0_CR_RXPERBITRANK2_Lane7_OFF                        (28)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane7_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane7_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane7_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK2_Lane7_HSH                        (0x041C3018)

#define DDRDATACH0_CR_RXPERBITRANK3_REG                                (0x0000301C)

  #define DDRDATACH0_CR_RXPERBITRANK3_Lane0_OFF                        ( 0)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane0_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane0_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane0_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane0_HSH                        (0x0400301C)

  #define DDRDATACH0_CR_RXPERBITRANK3_Lane1_OFF                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane1_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane1_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane1_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane1_HSH                        (0x0404301C)

  #define DDRDATACH0_CR_RXPERBITRANK3_Lane2_OFF                        ( 8)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane2_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane2_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane2_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane2_HSH                        (0x0408301C)

  #define DDRDATACH0_CR_RXPERBITRANK3_Lane3_OFF                        (12)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane3_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane3_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane3_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane3_HSH                        (0x040C301C)

  #define DDRDATACH0_CR_RXPERBITRANK3_Lane4_OFF                        (16)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane4_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane4_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane4_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane4_HSH                        (0x0410301C)

  #define DDRDATACH0_CR_RXPERBITRANK3_Lane5_OFF                        (20)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane5_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane5_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane5_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane5_HSH                        (0x0414301C)

  #define DDRDATACH0_CR_RXPERBITRANK3_Lane6_OFF                        (24)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane6_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane6_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane6_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane6_HSH                        (0x0418301C)

  #define DDRDATACH0_CR_RXPERBITRANK3_Lane7_OFF                        (28)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane7_WID                        ( 4)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane7_MIN                        (0)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane7_DEF                        (0x00000000)
  #define DDRDATACH0_CR_RXPERBITRANK3_Lane7_HSH                        (0x041C301C)

#define DDRDATACH0_CR_TXTRAINRANK0_REG                                 (0x00003020)

  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqDelay_OFF                     ( 0)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqDelay_WID                     ( 9)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqDelay_MSK                     (0x000001FF)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqDelay_MIN                     (0)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqDelay_MAX                     (511) // 0x000001FF
  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqDelay_DEF                     (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqDelay_HSH                     (0x09003020)

  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqsDelay_OFF                    ( 9)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqsDelay_WID                    ( 9)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqsDelay_MSK                    (0x0003FE00)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqsDelay_MIN                    (0)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqsDelay_MAX                    (511) // 0x000001FF
  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqsDelay_DEF                    (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxDqsDelay_HSH                    (0x09093020)

  #define DDRDATACH0_CR_TXTRAINRANK0_Spare0_OFF                        (18)
  #define DDRDATACH0_CR_TXTRAINRANK0_Spare0_WID                        ( 2)
  #define DDRDATACH0_CR_TXTRAINRANK0_Spare0_MSK                        (0x000C0000)
  #define DDRDATACH0_CR_TXTRAINRANK0_Spare0_MIN                        (0)
  #define DDRDATACH0_CR_TXTRAINRANK0_Spare0_MAX                        (3) // 0x00000003
  #define DDRDATACH0_CR_TXTRAINRANK0_Spare0_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK0_Spare0_HSH                        (0x02123020)

  #define DDRDATACH0_CR_TXTRAINRANK0_TxEqualization_OFF                (20)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxEqualization_WID                ( 6)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxEqualization_MSK                (0x03F00000)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxEqualization_MIN                (0)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxEqualization_MAX                (63) // 0x0000003F
  #define DDRDATACH0_CR_TXTRAINRANK0_TxEqualization_DEF                (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK0_TxEqualization_HSH                (0x06143020)

  #define DDRDATACH0_CR_TXTRAINRANK0_Spare1_OFF                        (26)
  #define DDRDATACH0_CR_TXTRAINRANK0_Spare1_WID                        ( 6)
  #define DDRDATACH0_CR_TXTRAINRANK0_Spare1_MSK                        (0xFC000000)
  #define DDRDATACH0_CR_TXTRAINRANK0_Spare1_MIN                        (0)
  #define DDRDATACH0_CR_TXTRAINRANK0_Spare1_MAX                        (63) // 0x0000003F
  #define DDRDATACH0_CR_TXTRAINRANK0_Spare1_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK0_Spare1_HSH                        (0x061A3020)

#define DDRDATACH0_CR_TXTRAINRANK1_REG                                 (0x00003024)

  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqDelay_OFF                     ( 0)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqDelay_WID                     ( 9)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqDelay_MSK                     (0x000001FF)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqDelay_MIN                     (0)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqDelay_MAX                     (511) // 0x000001FF
  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqDelay_DEF                     (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqDelay_HSH                     (0x09003024)

  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqsDelay_OFF                    ( 9)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqsDelay_WID                    ( 9)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqsDelay_MSK                    (0x0003FE00)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqsDelay_MIN                    (0)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqsDelay_MAX                    (511) // 0x000001FF
  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqsDelay_DEF                    (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxDqsDelay_HSH                    (0x09093024)

  #define DDRDATACH0_CR_TXTRAINRANK1_Spare0_OFF                        (18)
  #define DDRDATACH0_CR_TXTRAINRANK1_Spare0_WID                        ( 2)
  #define DDRDATACH0_CR_TXTRAINRANK1_Spare0_MSK                        (0x000C0000)
  #define DDRDATACH0_CR_TXTRAINRANK1_Spare0_MIN                        (0)
  #define DDRDATACH0_CR_TXTRAINRANK1_Spare0_MAX                        (3) // 0x00000003
  #define DDRDATACH0_CR_TXTRAINRANK1_Spare0_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK1_Spare0_HSH                        (0x02123024)

  #define DDRDATACH0_CR_TXTRAINRANK1_TxEqualization_OFF                (20)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxEqualization_WID                ( 6)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxEqualization_MSK                (0x03F00000)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxEqualization_MIN                (0)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxEqualization_MAX                (63) // 0x0000003F
  #define DDRDATACH0_CR_TXTRAINRANK1_TxEqualization_DEF                (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK1_TxEqualization_HSH                (0x06143024)

  #define DDRDATACH0_CR_TXTRAINRANK1_Spare1_OFF                        (26)
  #define DDRDATACH0_CR_TXTRAINRANK1_Spare1_WID                        ( 6)
  #define DDRDATACH0_CR_TXTRAINRANK1_Spare1_MSK                        (0xFC000000)
  #define DDRDATACH0_CR_TXTRAINRANK1_Spare1_MIN                        (0)
  #define DDRDATACH0_CR_TXTRAINRANK1_Spare1_MAX                        (63) // 0x0000003F
  #define DDRDATACH0_CR_TXTRAINRANK1_Spare1_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK1_Spare1_HSH                        (0x061A3024)

#define DDRDATACH0_CR_TXTRAINRANK2_REG                                 (0x00003028)

  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqDelay_OFF                     ( 0)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqDelay_WID                     ( 9)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqDelay_MSK                     (0x000001FF)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqDelay_MIN                     (0)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqDelay_MAX                     (511) // 0x000001FF
  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqDelay_DEF                     (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqDelay_HSH                     (0x09003028)

  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqsDelay_OFF                    ( 9)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqsDelay_WID                    ( 9)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqsDelay_MSK                    (0x0003FE00)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqsDelay_MIN                    (0)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqsDelay_MAX                    (511) // 0x000001FF
  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqsDelay_DEF                    (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxDqsDelay_HSH                    (0x09093028)

  #define DDRDATACH0_CR_TXTRAINRANK2_Spare0_OFF                        (18)
  #define DDRDATACH0_CR_TXTRAINRANK2_Spare0_WID                        ( 2)
  #define DDRDATACH0_CR_TXTRAINRANK2_Spare0_MSK                        (0x000C0000)
  #define DDRDATACH0_CR_TXTRAINRANK2_Spare0_MIN                        (0)
  #define DDRDATACH0_CR_TXTRAINRANK2_Spare0_MAX                        (3) // 0x00000003
  #define DDRDATACH0_CR_TXTRAINRANK2_Spare0_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK2_Spare0_HSH                        (0x02123028)

  #define DDRDATACH0_CR_TXTRAINRANK2_TxEqualization_OFF                (20)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxEqualization_WID                ( 6)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxEqualization_MSK                (0x03F00000)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxEqualization_MIN                (0)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxEqualization_MAX                (63) // 0x0000003F
  #define DDRDATACH0_CR_TXTRAINRANK2_TxEqualization_DEF                (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK2_TxEqualization_HSH                (0x06143028)

  #define DDRDATACH0_CR_TXTRAINRANK2_Spare1_OFF                        (26)
  #define DDRDATACH0_CR_TXTRAINRANK2_Spare1_WID                        ( 6)
  #define DDRDATACH0_CR_TXTRAINRANK2_Spare1_MSK                        (0xFC000000)
  #define DDRDATACH0_CR_TXTRAINRANK2_Spare1_MIN                        (0)
  #define DDRDATACH0_CR_TXTRAINRANK2_Spare1_MAX                        (63) // 0x0000003F
  #define DDRDATACH0_CR_TXTRAINRANK2_Spare1_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK2_Spare1_HSH                        (0x061A3028)

#define DDRDATACH0_CR_TXTRAINRANK3_REG                                 (0x0000302C)

  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqDelay_OFF                     ( 0)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqDelay_WID                     ( 9)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqDelay_MSK                     (0x000001FF)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqDelay_MIN                     (0)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqDelay_MAX                     (511) // 0x000001FF
  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqDelay_DEF                     (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqDelay_HSH                     (0x0900302C)

  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqsDelay_OFF                    ( 9)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqsDelay_WID                    ( 9)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqsDelay_MSK                    (0x0003FE00)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqsDelay_MIN                    (0)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqsDelay_MAX                    (511) // 0x000001FF
  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqsDelay_DEF                    (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxDqsDelay_HSH                    (0x0909302C)

  #define DDRDATACH0_CR_TXTRAINRANK3_Spare0_OFF                        (18)
  #define DDRDATACH0_CR_TXTRAINRANK3_Spare0_WID                        ( 2)
  #define DDRDATACH0_CR_TXTRAINRANK3_Spare0_MSK                        (0x000C0000)
  #define DDRDATACH0_CR_TXTRAINRANK3_Spare0_MIN                        (0)
  #define DDRDATACH0_CR_TXTRAINRANK3_Spare0_MAX                        (3) // 0x00000003
  #define DDRDATACH0_CR_TXTRAINRANK3_Spare0_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK3_Spare0_HSH                        (0x0212302C)

  #define DDRDATACH0_CR_TXTRAINRANK3_TxEqualization_OFF                (20)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxEqualization_WID                ( 6)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxEqualization_MSK                (0x03F00000)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxEqualization_MIN                (0)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxEqualization_MAX                (63) // 0x0000003F
  #define DDRDATACH0_CR_TXTRAINRANK3_TxEqualization_DEF                (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK3_TxEqualization_HSH                (0x0614302C)

  #define DDRDATACH0_CR_TXTRAINRANK3_Spare1_OFF                        (26)
  #define DDRDATACH0_CR_TXTRAINRANK3_Spare1_WID                        ( 6)
  #define DDRDATACH0_CR_TXTRAINRANK3_Spare1_MSK                        (0xFC000000)
  #define DDRDATACH0_CR_TXTRAINRANK3_Spare1_MIN                        (0)
  #define DDRDATACH0_CR_TXTRAINRANK3_Spare1_MAX                        (63) // 0x0000003F
  #define DDRDATACH0_CR_TXTRAINRANK3_Spare1_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXTRAINRANK3_Spare1_HSH                        (0x061A302C)

#define DDRDATACH0_CR_TXPERBITRANK0_REG                                (0x00003030)

  #define DDRDATACH0_CR_TXPERBITRANK0_Lane0_OFF                        ( 0)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane0_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane0_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane0_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane0_HSH                        (0x04003030)

  #define DDRDATACH0_CR_TXPERBITRANK0_Lane1_OFF                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane1_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane1_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane1_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane1_HSH                        (0x04043030)

  #define DDRDATACH0_CR_TXPERBITRANK0_Lane2_OFF                        ( 8)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane2_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane2_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane2_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane2_HSH                        (0x04083030)

  #define DDRDATACH0_CR_TXPERBITRANK0_Lane3_OFF                        (12)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane3_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane3_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane3_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane3_HSH                        (0x040C3030)

  #define DDRDATACH0_CR_TXPERBITRANK0_Lane4_OFF                        (16)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane4_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane4_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane4_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane4_HSH                        (0x04103030)

  #define DDRDATACH0_CR_TXPERBITRANK0_Lane5_OFF                        (20)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane5_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane5_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane5_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane5_HSH                        (0x04143030)

  #define DDRDATACH0_CR_TXPERBITRANK0_Lane6_OFF                        (24)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane6_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane6_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane6_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane6_HSH                        (0x04183030)

  #define DDRDATACH0_CR_TXPERBITRANK0_Lane7_OFF                        (28)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane7_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane7_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane7_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK0_Lane7_HSH                        (0x041C3030)

#define DDRDATACH0_CR_TXPERBITRANK1_REG                                (0x00003034)

  #define DDRDATACH0_CR_TXPERBITRANK1_Lane0_OFF                        ( 0)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane0_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane0_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane0_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane0_HSH                        (0x04003034)

  #define DDRDATACH0_CR_TXPERBITRANK1_Lane1_OFF                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane1_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane1_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane1_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane1_HSH                        (0x04043034)

  #define DDRDATACH0_CR_TXPERBITRANK1_Lane2_OFF                        ( 8)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane2_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane2_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane2_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane2_HSH                        (0x04083034)

  #define DDRDATACH0_CR_TXPERBITRANK1_Lane3_OFF                        (12)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane3_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane3_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane3_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane3_HSH                        (0x040C3034)

  #define DDRDATACH0_CR_TXPERBITRANK1_Lane4_OFF                        (16)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane4_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane4_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane4_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane4_HSH                        (0x04103034)

  #define DDRDATACH0_CR_TXPERBITRANK1_Lane5_OFF                        (20)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane5_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane5_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane5_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane5_HSH                        (0x04143034)

  #define DDRDATACH0_CR_TXPERBITRANK1_Lane6_OFF                        (24)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane6_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane6_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane6_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane6_HSH                        (0x04183034)

  #define DDRDATACH0_CR_TXPERBITRANK1_Lane7_OFF                        (28)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane7_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane7_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane7_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK1_Lane7_HSH                        (0x041C3034)

#define DDRDATACH0_CR_TXPERBITRANK2_REG                                (0x00003038)

  #define DDRDATACH0_CR_TXPERBITRANK2_Lane0_OFF                        ( 0)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane0_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane0_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane0_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane0_HSH                        (0x04003038)

  #define DDRDATACH0_CR_TXPERBITRANK2_Lane1_OFF                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane1_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane1_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane1_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane1_HSH                        (0x04043038)

  #define DDRDATACH0_CR_TXPERBITRANK2_Lane2_OFF                        ( 8)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane2_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane2_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane2_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane2_HSH                        (0x04083038)

  #define DDRDATACH0_CR_TXPERBITRANK2_Lane3_OFF                        (12)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane3_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane3_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane3_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane3_HSH                        (0x040C3038)

  #define DDRDATACH0_CR_TXPERBITRANK2_Lane4_OFF                        (16)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane4_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane4_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane4_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane4_HSH                        (0x04103038)

  #define DDRDATACH0_CR_TXPERBITRANK2_Lane5_OFF                        (20)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane5_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane5_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane5_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane5_HSH                        (0x04143038)

  #define DDRDATACH0_CR_TXPERBITRANK2_Lane6_OFF                        (24)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane6_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane6_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane6_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane6_HSH                        (0x04183038)

  #define DDRDATACH0_CR_TXPERBITRANK2_Lane7_OFF                        (28)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane7_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane7_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane7_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK2_Lane7_HSH                        (0x041C3038)

#define DDRDATACH0_CR_TXPERBITRANK3_REG                                (0x0000303C)

  #define DDRDATACH0_CR_TXPERBITRANK3_Lane0_OFF                        ( 0)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane0_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane0_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane0_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane0_HSH                        (0x0400303C)

  #define DDRDATACH0_CR_TXPERBITRANK3_Lane1_OFF                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane1_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane1_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane1_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane1_HSH                        (0x0404303C)

  #define DDRDATACH0_CR_TXPERBITRANK3_Lane2_OFF                        ( 8)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane2_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane2_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane2_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane2_HSH                        (0x0408303C)

  #define DDRDATACH0_CR_TXPERBITRANK3_Lane3_OFF                        (12)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane3_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane3_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane3_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane3_HSH                        (0x040C303C)

  #define DDRDATACH0_CR_TXPERBITRANK3_Lane4_OFF                        (16)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane4_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane4_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane4_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane4_HSH                        (0x0410303C)

  #define DDRDATACH0_CR_TXPERBITRANK3_Lane5_OFF                        (20)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane5_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane5_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane5_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane5_HSH                        (0x0414303C)

  #define DDRDATACH0_CR_TXPERBITRANK3_Lane6_OFF                        (24)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane6_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane6_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane6_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane6_HSH                        (0x0418303C)

  #define DDRDATACH0_CR_TXPERBITRANK3_Lane7_OFF                        (28)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane7_WID                        ( 4)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane7_MIN                        (0)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane7_DEF                        (0x00000000)
  #define DDRDATACH0_CR_TXPERBITRANK3_Lane7_HSH                        (0x041C303C)

#define DDRDATACH0_CR_RCOMPDATA0_REG                                   (0x00003040)

  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvUp_OFF                      ( 0)
  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvUp_WID                      ( 6)
  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvUp_MSK                      (0x0000003F)
  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvUp_MIN                      (0)
  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvUp_MAX                      (63) // 0x0000003F
  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvUp_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvUp_HSH                      (0x06003040)

  #define DDRDATACH0_CR_RCOMPDATA0_Rsvd_OFF                            ( 6)
  #define DDRDATACH0_CR_RCOMPDATA0_Rsvd_WID                            ( 3)
  #define DDRDATACH0_CR_RCOMPDATA0_Rsvd_MSK                            (0x000001C0)
  #define DDRDATACH0_CR_RCOMPDATA0_Rsvd_MIN                            (0)
  #define DDRDATACH0_CR_RCOMPDATA0_Rsvd_MAX                            (7) // 0x00000007
  #define DDRDATACH0_CR_RCOMPDATA0_Rsvd_DEF                            (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA0_Rsvd_HSH                            (0x03063040)

  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvDown_OFF                    ( 9)
  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvDown_WID                    ( 6)
  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvDown_MSK                    (0x00007E00)
  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvDown_MIN                    (0)
  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvDown_MAX                    (63) // 0x0000003F
  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvDown_DEF                    (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA0_RcompDrvDown_HSH                    (0x06093040)

  #define DDRDATACH0_CR_RCOMPDATA0_VTComp_OFF                          (15)
  #define DDRDATACH0_CR_RCOMPDATA0_VTComp_WID                          ( 5)
  #define DDRDATACH0_CR_RCOMPDATA0_VTComp_MSK                          (0x000F8000)
  #define DDRDATACH0_CR_RCOMPDATA0_VTComp_MIN                          (0)
  #define DDRDATACH0_CR_RCOMPDATA0_VTComp_MAX                          (31) // 0x0000001F
  #define DDRDATACH0_CR_RCOMPDATA0_VTComp_DEF                          (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA0_VTComp_HSH                          (0x050F3040)

  #define DDRDATACH0_CR_RCOMPDATA0_SlewRateComp_OFF                    (20)
  #define DDRDATACH0_CR_RCOMPDATA0_SlewRateComp_WID                    ( 5)
  #define DDRDATACH0_CR_RCOMPDATA0_SlewRateComp_MSK                    (0x01F00000)
  #define DDRDATACH0_CR_RCOMPDATA0_SlewRateComp_MIN                    (0)
  #define DDRDATACH0_CR_RCOMPDATA0_SlewRateComp_MAX                    (31) // 0x0000001F
  #define DDRDATACH0_CR_RCOMPDATA0_SlewRateComp_DEF                    (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA0_SlewRateComp_HSH                    (0x05143040)

  #define DDRDATACH0_CR_RCOMPDATA0_Spare0_OFF                          (25)
  #define DDRDATACH0_CR_RCOMPDATA0_Spare0_WID                          ( 1)
  #define DDRDATACH0_CR_RCOMPDATA0_Spare0_MSK                          (0x02000000)
  #define DDRDATACH0_CR_RCOMPDATA0_Spare0_MIN                          (0)
  #define DDRDATACH0_CR_RCOMPDATA0_Spare0_MAX                          (1) // 0x00000001
  #define DDRDATACH0_CR_RCOMPDATA0_Spare0_DEF                          (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA0_Spare0_HSH                          (0x01193040)

  #define DDRDATACH0_CR_RCOMPDATA0_TcoComp_OFF                         (26)
  #define DDRDATACH0_CR_RCOMPDATA0_TcoComp_WID                         ( 6)
  #define DDRDATACH0_CR_RCOMPDATA0_TcoComp_MSK                         (0xFC000000)
  #define DDRDATACH0_CR_RCOMPDATA0_TcoComp_MIN                         (0)
  #define DDRDATACH0_CR_RCOMPDATA0_TcoComp_MAX                         (63) // 0x0000003F
  #define DDRDATACH0_CR_RCOMPDATA0_TcoComp_DEF                         (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA0_TcoComp_HSH                         (0x061A3040)

#define DDRDATACH0_CR_RCOMPDATA1_REG                                   (0x00003044)

  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtUp_OFF                      ( 0)
  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtUp_WID                      ( 6)
  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtUp_MSK                      (0x0000003F)
  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtUp_MIN                      (0)
  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtUp_MAX                      (63) // 0x0000003F
  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtUp_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtUp_HSH                      (0x06003044)

  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvDn_OFF                      ( 6)
  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvDn_WID                      (10)
  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvDn_MSK                      (0x0000FFC0)
  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvDn_MIN                      (0)
  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvDn_MAX                      (1023) // 0x000003FF
  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvDn_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvDn_HSH                      (0x0A063044)

  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvUp_OFF                      (16)
  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvUp_WID                      (10)
  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvUp_MSK                      (0x03FF0000)
  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvUp_MIN                      (0)
  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvUp_MAX                      (1023) // 0x000003FF
  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvUp_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA1_PanicDrvUp_HSH                      (0x0A103044)

  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtDown_OFF                    (26)
  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtDown_WID                    ( 6)
  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtDown_MSK                    (0xFC000000)
  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtDown_MIN                    (0)
  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtDown_MAX                    (63) // 0x0000003F
  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtDown_DEF                    (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA1_RcompOdtDown_HSH                    (0x061A3044)

#define DDRDATACH0_CR_TXXTALK_REG                                      (0x00003048)

  #define DDRDATACH0_CR_TXXTALK_Lane0_OFF                              ( 0)
  #define DDRDATACH0_CR_TXXTALK_Lane0_WID                              ( 4)
  #define DDRDATACH0_CR_TXXTALK_Lane0_MSK                              (0x0000000F)
  #define DDRDATACH0_CR_TXXTALK_Lane0_MIN                              (-8)
  #define DDRDATACH0_CR_TXXTALK_Lane0_MAX                              (7) // 0x00000007
  #define DDRDATACH0_CR_TXXTALK_Lane0_DEF                              (0x00000000)
  #define DDRDATACH0_CR_TXXTALK_Lane0_HSH                              (0x84003048)

  #define DDRDATACH0_CR_TXXTALK_Lane1_OFF                              ( 4)
  #define DDRDATACH0_CR_TXXTALK_Lane1_WID                              ( 4)
  #define DDRDATACH0_CR_TXXTALK_Lane1_MSK                              (0x000000F0)
  #define DDRDATACH0_CR_TXXTALK_Lane1_MIN                              (-8)
  #define DDRDATACH0_CR_TXXTALK_Lane1_MAX                              (7) // 0x00000007
  #define DDRDATACH0_CR_TXXTALK_Lane1_DEF                              (0x00000000)
  #define DDRDATACH0_CR_TXXTALK_Lane1_HSH                              (0x84043048)

  #define DDRDATACH0_CR_TXXTALK_Lane2_OFF                              ( 8)
  #define DDRDATACH0_CR_TXXTALK_Lane2_WID                              ( 4)
  #define DDRDATACH0_CR_TXXTALK_Lane2_MSK                              (0x00000F00)
  #define DDRDATACH0_CR_TXXTALK_Lane2_MIN                              (-8)
  #define DDRDATACH0_CR_TXXTALK_Lane2_MAX                              (7) // 0x00000007
  #define DDRDATACH0_CR_TXXTALK_Lane2_DEF                              (0x00000000)
  #define DDRDATACH0_CR_TXXTALK_Lane2_HSH                              (0x84083048)

  #define DDRDATACH0_CR_TXXTALK_Lane3_OFF                              (12)
  #define DDRDATACH0_CR_TXXTALK_Lane3_WID                              ( 4)
  #define DDRDATACH0_CR_TXXTALK_Lane3_MSK                              (0x0000F000)
  #define DDRDATACH0_CR_TXXTALK_Lane3_MIN                              (-8)
  #define DDRDATACH0_CR_TXXTALK_Lane3_MAX                              (7) // 0x00000007
  #define DDRDATACH0_CR_TXXTALK_Lane3_DEF                              (0x00000000)
  #define DDRDATACH0_CR_TXXTALK_Lane3_HSH                              (0x840C3048)

  #define DDRDATACH0_CR_TXXTALK_Lane4_OFF                              (16)
  #define DDRDATACH0_CR_TXXTALK_Lane4_WID                              ( 4)
  #define DDRDATACH0_CR_TXXTALK_Lane4_MSK                              (0x000F0000)
  #define DDRDATACH0_CR_TXXTALK_Lane4_MIN                              (-8)
  #define DDRDATACH0_CR_TXXTALK_Lane4_MAX                              (7) // 0x00000007
  #define DDRDATACH0_CR_TXXTALK_Lane4_DEF                              (0x00000000)
  #define DDRDATACH0_CR_TXXTALK_Lane4_HSH                              (0x84103048)

  #define DDRDATACH0_CR_TXXTALK_Lane5_OFF                              (20)
  #define DDRDATACH0_CR_TXXTALK_Lane5_WID                              ( 4)
  #define DDRDATACH0_CR_TXXTALK_Lane5_MSK                              (0x00F00000)
  #define DDRDATACH0_CR_TXXTALK_Lane5_MIN                              (-8)
  #define DDRDATACH0_CR_TXXTALK_Lane5_MAX                              (7) // 0x00000007
  #define DDRDATACH0_CR_TXXTALK_Lane5_DEF                              (0x00000000)
  #define DDRDATACH0_CR_TXXTALK_Lane5_HSH                              (0x84143048)

  #define DDRDATACH0_CR_TXXTALK_Lane6_OFF                              (24)
  #define DDRDATACH0_CR_TXXTALK_Lane6_WID                              ( 4)
  #define DDRDATACH0_CR_TXXTALK_Lane6_MSK                              (0x0F000000)
  #define DDRDATACH0_CR_TXXTALK_Lane6_MIN                              (-8)
  #define DDRDATACH0_CR_TXXTALK_Lane6_MAX                              (7) // 0x00000007
  #define DDRDATACH0_CR_TXXTALK_Lane6_DEF                              (0x00000000)
  #define DDRDATACH0_CR_TXXTALK_Lane6_HSH                              (0x84183048)

  #define DDRDATACH0_CR_TXXTALK_Lane7_OFF                              (28)
  #define DDRDATACH0_CR_TXXTALK_Lane7_WID                              ( 4)
  #define DDRDATACH0_CR_TXXTALK_Lane7_MSK                              (0xF0000000)
  #define DDRDATACH0_CR_TXXTALK_Lane7_MIN                              (-8)
  #define DDRDATACH0_CR_TXXTALK_Lane7_MAX                              (7) // 0x00000007
  #define DDRDATACH0_CR_TXXTALK_Lane7_DEF                              (0x00000000)
  #define DDRDATACH0_CR_TXXTALK_Lane7_HSH                              (0x841C3048)

#define DDRDATACH0_CR_RCOMPDATA2_REG                                   (0x0000304C)

  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicUp_OFF                      ( 0)
  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicUp_WID                      ( 8)
  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicUp_MSK                      (0x000000FF)
  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicUp_MIN                      (0)
  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicUp_MAX                      (255) // 0x000000FF
  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicUp_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicUp_HSH                      (0x0800304C)

  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicDn_OFF                      ( 8)
  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicDn_WID                      ( 8)
  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicDn_MSK                      (0x0000FF00)
  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicDn_MIN                      (0)
  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicDn_MAX                      (255) // 0x000000FF
  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicDn_DEF                      (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA2_VttPanicDn_HSH                      (0x0808304C)

  #define DDRDATACH0_CR_RCOMPDATA2_Spare_OFF                           (16)
  #define DDRDATACH0_CR_RCOMPDATA2_Spare_WID                           (16)
  #define DDRDATACH0_CR_RCOMPDATA2_Spare_MSK                           (0xFFFF0000)
  #define DDRDATACH0_CR_RCOMPDATA2_Spare_MIN                           (0)
  #define DDRDATACH0_CR_RCOMPDATA2_Spare_MAX                           (65535) // 0x0000FFFF
  #define DDRDATACH0_CR_RCOMPDATA2_Spare_DEF                           (0x00000000)
  #define DDRDATACH0_CR_RCOMPDATA2_Spare_HSH                           (0x1010304C)

#define DDRDATACH0_CR_RXOFFSETVDQRANK0_REG                             (0x00003050)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane0_OFF                     ( 0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane0_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane0_MSK                     (0x0000000F)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane0_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane0_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane0_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane0_HSH                     (0x04003050)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane1_OFF                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane1_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane1_MSK                     (0x000000F0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane1_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane1_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane1_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane1_HSH                     (0x04043050)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane2_OFF                     ( 8)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane2_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane2_MSK                     (0x00000F00)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane2_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane2_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane2_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane2_HSH                     (0x04083050)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane3_OFF                     (12)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane3_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane3_MSK                     (0x0000F000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane3_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane3_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane3_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane3_HSH                     (0x040C3050)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane4_OFF                     (16)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane4_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane4_MSK                     (0x000F0000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane4_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane4_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane4_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane4_HSH                     (0x04103050)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane5_OFF                     (20)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane5_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane5_MSK                     (0x00F00000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane5_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane5_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane5_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane5_HSH                     (0x04143050)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane6_OFF                     (24)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane6_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane6_MSK                     (0x0F000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane6_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane6_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane6_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane6_HSH                     (0x04183050)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane7_OFF                     (28)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane7_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane7_MSK                     (0xF0000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane7_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane7_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane7_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK0_Lane7_HSH                     (0x041C3050)

#define DDRDATACH0_CR_RXOFFSETVDQRANK1_REG                             (0x00003054)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane0_OFF                     ( 0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane0_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane0_MSK                     (0x0000000F)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane0_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane0_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane0_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane0_HSH                     (0x04003054)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane1_OFF                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane1_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane1_MSK                     (0x000000F0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane1_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane1_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane1_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane1_HSH                     (0x04043054)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane2_OFF                     ( 8)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane2_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane2_MSK                     (0x00000F00)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane2_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane2_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane2_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane2_HSH                     (0x04083054)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane3_OFF                     (12)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane3_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane3_MSK                     (0x0000F000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane3_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane3_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane3_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane3_HSH                     (0x040C3054)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane4_OFF                     (16)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane4_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane4_MSK                     (0x000F0000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane4_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane4_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane4_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane4_HSH                     (0x04103054)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane5_OFF                     (20)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane5_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane5_MSK                     (0x00F00000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane5_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane5_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane5_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane5_HSH                     (0x04143054)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane6_OFF                     (24)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane6_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane6_MSK                     (0x0F000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane6_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane6_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane6_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane6_HSH                     (0x04183054)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane7_OFF                     (28)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane7_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane7_MSK                     (0xF0000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane7_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane7_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane7_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK1_Lane7_HSH                     (0x041C3054)

#define DDRDATACH0_CR_RXOFFSETVDQRANK2_REG                             (0x00003058)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane0_OFF                     ( 0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane0_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane0_MSK                     (0x0000000F)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane0_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane0_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane0_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane0_HSH                     (0x04003058)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane1_OFF                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane1_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane1_MSK                     (0x000000F0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane1_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane1_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane1_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane1_HSH                     (0x04043058)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane2_OFF                     ( 8)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane2_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane2_MSK                     (0x00000F00)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane2_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane2_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane2_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane2_HSH                     (0x04083058)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane3_OFF                     (12)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane3_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane3_MSK                     (0x0000F000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane3_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane3_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane3_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane3_HSH                     (0x040C3058)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane4_OFF                     (16)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane4_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane4_MSK                     (0x000F0000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane4_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane4_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane4_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane4_HSH                     (0x04103058)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane5_OFF                     (20)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane5_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane5_MSK                     (0x00F00000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane5_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane5_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane5_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane5_HSH                     (0x04143058)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane6_OFF                     (24)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane6_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane6_MSK                     (0x0F000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane6_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane6_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane6_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane6_HSH                     (0x04183058)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane7_OFF                     (28)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane7_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane7_MSK                     (0xF0000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane7_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane7_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane7_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK2_Lane7_HSH                     (0x041C3058)

#define DDRDATACH0_CR_RXOFFSETVDQRANK3_REG                             (0x0000305C)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane0_OFF                     ( 0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane0_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane0_MSK                     (0x0000000F)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane0_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane0_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane0_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane0_HSH                     (0x0400305C)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane1_OFF                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane1_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane1_MSK                     (0x000000F0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane1_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane1_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane1_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane1_HSH                     (0x0404305C)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane2_OFF                     ( 8)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane2_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane2_MSK                     (0x00000F00)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane2_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane2_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane2_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane2_HSH                     (0x0408305C)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane3_OFF                     (12)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane3_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane3_MSK                     (0x0000F000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane3_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane3_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane3_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane3_HSH                     (0x040C305C)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane4_OFF                     (16)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane4_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane4_MSK                     (0x000F0000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane4_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane4_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane4_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane4_HSH                     (0x0410305C)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane5_OFF                     (20)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane5_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane5_MSK                     (0x00F00000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane5_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane5_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane5_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane5_HSH                     (0x0414305C)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane6_OFF                     (24)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane6_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane6_MSK                     (0x0F000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane6_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane6_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane6_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane6_HSH                     (0x0418305C)

  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane7_OFF                     (28)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane7_WID                     ( 4)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane7_MSK                     (0xF0000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane7_MIN                     (0)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane7_MAX                     (15) // 0x0000000F
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane7_DEF                     (0x00000000)
  #define DDRDATACH0_CR_RXOFFSETVDQRANK3_Lane7_HSH                     (0x041C305C)

#define DDRDATACH0_CR_DATATRAINFEEDBACK_REG                            (0x00003060)

  #define DDRDATACH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_OFF        ( 0)
  #define DDRDATACH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_WID        ( 9)
  #define DDRDATACH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_MSK        (0x000001FF)
  #define DDRDATACH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_MIN        (0)
  #define DDRDATACH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_MAX        (511) // 0x000001FF
  #define DDRDATACH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_DEF        (0x00000000)
  #define DDRDATACH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_HSH        (0x09003060)

  #define DDRDATACH0_CR_DATATRAINFEEDBACK_Spare_OFF                    ( 9)
  #define DDRDATACH0_CR_DATATRAINFEEDBACK_Spare_WID                    (23)
  #define DDRDATACH0_CR_DATATRAINFEEDBACK_Spare_MSK                    (0xFFFFFE00)
  #define DDRDATACH0_CR_DATATRAINFEEDBACK_Spare_MIN                    (0)
  #define DDRDATACH0_CR_DATATRAINFEEDBACK_Spare_MAX                    (8388607) // 0x007FFFFF
  #define DDRDATACH0_CR_DATATRAINFEEDBACK_Spare_DEF                    (0x00000000)
  #define DDRDATACH0_CR_DATATRAINFEEDBACK_Spare_HSH                    (0x17093060)

#define DDRDATACH0_CR_DLLPITESTANDADC_REG                              (0x00003064)

  #define DDRDATACH0_CR_DLLPITESTANDADC_RunTest_OFF                    ( 0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_RunTest_WID                    ( 1)
  #define DDRDATACH0_CR_DLLPITESTANDADC_RunTest_MSK                    (0x00000001)
  #define DDRDATACH0_CR_DLLPITESTANDADC_RunTest_MIN                    (0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_RunTest_MAX                    (1) // 0x00000001
  #define DDRDATACH0_CR_DLLPITESTANDADC_RunTest_DEF                    (0x00000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_RunTest_HSH                    (0x01003064)

  #define DDRDATACH0_CR_DLLPITESTANDADC_Load_OFF                       ( 1)
  #define DDRDATACH0_CR_DLLPITESTANDADC_Load_WID                       ( 1)
  #define DDRDATACH0_CR_DLLPITESTANDADC_Load_MSK                       (0x00000002)
  #define DDRDATACH0_CR_DLLPITESTANDADC_Load_MIN                       (0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_Load_MAX                       (1) // 0x00000001
  #define DDRDATACH0_CR_DLLPITESTANDADC_Load_DEF                       (0x00000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_Load_HSH                       (0x01013064)

  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeHVM_OFF                    ( 2)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeHVM_WID                    ( 1)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeHVM_MSK                    (0x00000004)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeHVM_MIN                    (0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeHVM_MAX                    (1) // 0x00000001
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeHVM_DEF                    (0x00000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeHVM_HSH                    (0x01023064)

  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeDV_OFF                     ( 3)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeDV_WID                     ( 1)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeDV_MSK                     (0x00000008)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeDV_MIN                     (0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeDV_MAX                     (1) // 0x00000001
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeDV_DEF                     (0x00000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeDV_HSH                     (0x01033064)

  #define DDRDATACH0_CR_DLLPITESTANDADC_CalCfdl_OFF                    ( 4)
  #define DDRDATACH0_CR_DLLPITESTANDADC_CalCfdl_WID                    ( 1)
  #define DDRDATACH0_CR_DLLPITESTANDADC_CalCfdl_MSK                    (0x00000010)
  #define DDRDATACH0_CR_DLLPITESTANDADC_CalCfdl_MIN                    (0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_CalCfdl_MAX                    (1) // 0x00000001
  #define DDRDATACH0_CR_DLLPITESTANDADC_CalCfdl_DEF                    (0x00000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_CalCfdl_HSH                    (0x01043064)

  #define DDRDATACH0_CR_DLLPITESTANDADC_LoadCount_OFF                  ( 5)
  #define DDRDATACH0_CR_DLLPITESTANDADC_LoadCount_WID                  (10)
  #define DDRDATACH0_CR_DLLPITESTANDADC_LoadCount_MSK                  (0x00007FE0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_LoadCount_MIN                  (0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_LoadCount_MAX                  (1023) // 0x000003FF
  #define DDRDATACH0_CR_DLLPITESTANDADC_LoadCount_DEF                  (0x00000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_LoadCount_HSH                  (0x0A053064)

  #define DDRDATACH0_CR_DLLPITESTANDADC_CountStatus_OFF                (15)
  #define DDRDATACH0_CR_DLLPITESTANDADC_CountStatus_WID                (10)
  #define DDRDATACH0_CR_DLLPITESTANDADC_CountStatus_MSK                (0x01FF8000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_CountStatus_MIN                (0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_CountStatus_MAX                (1023) // 0x000003FF
  #define DDRDATACH0_CR_DLLPITESTANDADC_CountStatus_DEF                (0x00000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_CountStatus_HSH                (0x0A0F3064)

  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeADC_OFF                    (25)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeADC_WID                    ( 1)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeADC_MSK                    (0x02000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeADC_MIN                    (0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeADC_MAX                    (1) // 0x00000001
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeADC_DEF                    (0x00000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ModeADC_HSH                    (0x01193064)

  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCClkDiv_OFF                  (26)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCClkDiv_WID                  ( 2)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCClkDiv_MSK                  (0x0C000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCClkDiv_MIN                  (0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCClkDiv_MAX                  (3) // 0x00000003
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCClkDiv_DEF                  (0x00000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCClkDiv_HSH                  (0x021A3064)

  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF              (28)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDdrChanSel_WID              ( 1)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK              (0x10000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN              (0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX              (1) // 0x00000001
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF              (0x00000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH              (0x011C3064)

  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCChopEn_OFF                  (29)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCChopEn_WID                  ( 1)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCChopEn_MSK                  (0x20000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCChopEn_MIN                  (0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCChopEn_MAX                  (1) // 0x00000001
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCChopEn_DEF                  (0x00000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCChopEn_HSH                  (0x011D3064)

  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDone_OFF                    (30)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDone_WID                    ( 1)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDone_MSK                    (0x40000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDone_MIN                    (0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDone_MAX                    (1) // 0x00000001
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDone_DEF                    (0x00000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_ADCDone_HSH                    (0x011E3064)

  #define DDRDATACH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF           (31)
  #define DDRDATACH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID           ( 1)
  #define DDRDATACH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK           (0x80000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN           (0)
  #define DDRDATACH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX           (1) // 0x00000001
  #define DDRDATACH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF           (0x00000000)
  #define DDRDATACH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH           (0x011F3064)

#define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_REG                          (0x00003068)

  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_OFF      ( 0)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_WID      ( 6)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MSK      (0x0000003F)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MIN      (-32)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MAX      (31) // 0x0000001F
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_DEF      (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_HSH      (0x86003068)

  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_OFF    ( 6)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_WID    ( 6)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MSK    (0x00000FC0)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MIN    (-32)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MAX    (31) // 0x0000001F
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_DEF    (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_HSH    (0x86063068)

  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_OFF      (12)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_WID      ( 5)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MSK      (0x0001F000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MIN      (-16)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MAX      (15) // 0x0000000F
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_DEF      (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_HSH      (0x850C3068)

  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_OFF    (17)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_WID    ( 5)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MSK    (0x003E0000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MIN    (-16)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MAX    (15) // 0x0000000F
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_DEF    (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_HSH    (0x85113068)

  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_OFF        (22)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_WID        ( 5)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MSK        (0x07C00000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MIN        (-16)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MAX        (15) // 0x0000000F
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_DEF        (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_HSH        (0x85163068)

  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_OFF   (27)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_WID   ( 5)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MSK   (0xF8000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MIN   (-16)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MAX   (15) // 0x0000000F
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_DEF   (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_HSH   (0x851B3068)

#define DDRDATACH0_CR_DDRCRDATACONTROL1_REG                            (0x0000306C)

  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RefPi_OFF                    ( 0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RefPi_WID                    ( 4)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RefPi_MSK                    (0x0000000F)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RefPi_MIN                    (-8)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RefPi_MAX                    (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RefPi_DEF                    (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RefPi_HSH                    (0x8400306C)

  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllMask_OFF                  ( 4)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllMask_WID                  ( 2)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllMask_MSK                  (0x00000030)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllMask_MIN                  (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllMask_MAX                  (3) // 0x00000003
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllMask_DEF                  (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllMask_HSH                  (0x0204306C)

  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllWeakLock_OFF              ( 6)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllWeakLock_WID              ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllWeakLock_MSK              (0x00000040)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllWeakLock_MIN              (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllWeakLock_MAX              (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllWeakLock_DEF              (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_DllWeakLock_HSH              (0x0106306C)

  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_OFF       ( 7)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_WID       ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MSK       (0x00000380)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MIN       (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MAX       (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_DEF       (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_HSH       (0x0307306C)

  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RxBiasCtl_OFF                (10)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RxBiasCtl_WID                ( 4)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RxBiasCtl_MSK                (0x00003C00)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RxBiasCtl_MIN                (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RxBiasCtl_MAX                (15) // 0x0000000F
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RxBiasCtl_DEF                (0x00000008)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_RxBiasCtl_HSH                (0x040A306C)

  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDelay_OFF                 (14)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDelay_WID                 ( 4)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDelay_MSK                 (0x0003C000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDelay_MIN                 (-8)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDelay_MAX                 (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDelay_DEF                 (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDelay_HSH                 (0x840E306C)

  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDuration_OFF              (18)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDuration_WID              ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDuration_MSK              (0x001C0000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDuration_MIN              (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDuration_MAX              (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDuration_DEF              (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_OdtDuration_HSH              (0x0312306C)

  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_OFF            (21)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_WID            ( 4)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_MSK            (0x01E00000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_MIN            (-8)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_MAX            (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_DEF            (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_HSH            (0x8415306C)

  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_OFF         (25)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_WID         ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_MSK         (0x0E000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_MIN         (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_MAX         (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_DEF         (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_HSH         (0x0319306C)

  #define DDRDATACH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_OFF           (28)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_WID           ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_MSK           (0x70000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_MIN           (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_MAX           (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_DEF           (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_HSH           (0x031C306C)

  #define DDRDATACH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_OFF           (31)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_WID           ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MSK           (0x80000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MIN           (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MAX           (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_DEF           (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_HSH           (0x011F306C)

#define DDRDATACH0_CR_DDRCRDATACONTROL2_REG                            (0x00003070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_OFF             ( 0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_WID             ( 5)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_MSK             (0x0000001F)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_MIN             (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_MAX             (31) // 0x0000001F
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_DEF             (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_HSH             (0x05003070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceBiasOn_OFF              ( 5)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceBiasOn_WID              ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceBiasOn_MSK              (0x00000020)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceBiasOn_MIN              (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceBiasOn_MAX              (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceBiasOn_DEF              (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceBiasOn_HSH              (0x01053070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceRxOn_OFF                ( 6)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceRxOn_WID                ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceRxOn_MSK                (0x00000040)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceRxOn_MIN                (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceRxOn_MAX                (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceRxOn_DEF                (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_ForceRxOn_HSH                (0x01063070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_LeakerComp_OFF               ( 7)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_LeakerComp_WID               ( 2)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_LeakerComp_MSK               (0x00000180)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_LeakerComp_MIN               (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_LeakerComp_MAX               (3) // 0x00000003
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_LeakerComp_DEF               (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_LeakerComp_HSH               (0x02073070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_OFF           ( 9)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_WID           ( 4)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MSK           (0x00001E00)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MIN           (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MAX           (15) // 0x0000000F
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_DEF           (0x00000008)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_HSH           (0x04093070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxClkStgNum_OFF              (13)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxClkStgNum_WID              ( 5)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MSK              (0x0003E000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MIN              (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MAX              (31) // 0x0000001F
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxClkStgNum_DEF              (0x00000011)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxClkStgNum_HSH              (0x050D3070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_WlLongDelEn_OFF              (18)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_WlLongDelEn_WID              ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_WlLongDelEn_MSK              (0x00040000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_WlLongDelEn_MIN              (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_WlLongDelEn_MAX              (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_WlLongDelEn_DEF              (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_WlLongDelEn_HSH              (0x01123070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_OFF          (19)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_WID          ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MSK          (0x00080000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MIN          (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MAX          (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_DEF          (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_HSH          (0x01133070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Ddr4Mode_OFF                 (20)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Ddr4Mode_WID                 ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Ddr4Mode_MSK                 (0x00100000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Ddr4Mode_MIN                 (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Ddr4Mode_MAX                 (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Ddr4Mode_DEF                 (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Ddr4Mode_HSH                 (0x01143070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVddqOdt_OFF                (21)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVddqOdt_WID                ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVddqOdt_MSK                (0x00200000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVddqOdt_MIN                (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVddqOdt_MAX                (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVddqOdt_DEF                (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVddqOdt_HSH                (0x01153070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVttOdt_OFF                 (22)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVttOdt_WID                 ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVttOdt_MSK                 (0x00400000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVttOdt_MIN                 (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVttOdt_MAX                 (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVttOdt_DEF                 (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnVttOdt_HSH                 (0x01163070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_OFF             (23)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_WID             ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_MSK             (0x00800000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_MIN             (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_MAX             (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_DEF             (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_HSH             (0x01173070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxEqDis_OFF                  (24)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxEqDis_WID                  ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxEqDis_MSK                  (0x01000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxEqDis_MIN                  (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxEqDis_MAX                  (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxEqDis_DEF                  (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxEqDis_HSH                  (0x01183070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_OFF            (25)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_WID            ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MSK            (0x02000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MIN            (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MAX            (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_DEF            (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_HSH            (0x01193070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Cben_OFF                     (26)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Cben_WID                     ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Cben_MSK                     (0x1C000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Cben_MIN                     (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Cben_MAX                     (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Cben_DEF                     (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_Cben_HSH                     (0x031A3070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_OFF          (29)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_WID          ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_MSK          (0x20000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_MIN          (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_MAX          (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_DEF          (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_HSH          (0x011D3070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_OFF          (30)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_WID          ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_MSK          (0x40000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_MIN          (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_MAX          (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_DEF          (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_HSH          (0x011E3070)

  #define DDRDATACH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_OFF          (31)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_WID          ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MSK          (0x80000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MIN          (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MAX          (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_DEF          (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_HSH          (0x011F3070)

#define DDRDATACH0_CR_DDRCRVREFCONTROL_REG                             (0x00003074)

  #define DDRDATACH0_CR_DDRCRVREFCONTROL_VrefCtl_OFF                   ( 0)
  #define DDRDATACH0_CR_DDRCRVREFCONTROL_VrefCtl_WID                   (24)
  #define DDRDATACH0_CR_DDRCRVREFCONTROL_VrefCtl_MSK                   (0x00FFFFFF)
  #define DDRDATACH0_CR_DDRCRVREFCONTROL_VrefCtl_MIN                   (0)
  #define DDRDATACH0_CR_DDRCRVREFCONTROL_VrefCtl_MAX                   (16777215) // 0x00FFFFFF
  #define DDRDATACH0_CR_DDRCRVREFCONTROL_VrefCtl_DEF                   (0x000E453A)
  #define DDRDATACH0_CR_DDRCRVREFCONTROL_VrefCtl_HSH                   (0x18003074)

  #define DDRDATACH0_CR_DDRCRVREFCONTROL_OutputCode_OFF                (24)
  #define DDRDATACH0_CR_DDRCRVREFCONTROL_OutputCode_WID                ( 8)
  #define DDRDATACH0_CR_DDRCRVREFCONTROL_OutputCode_MSK                (0xFF000000)
  #define DDRDATACH0_CR_DDRCRVREFCONTROL_OutputCode_MIN                (0)
  #define DDRDATACH0_CR_DDRCRVREFCONTROL_OutputCode_MAX                (255) // 0x000000FF
  #define DDRDATACH0_CR_DDRCRVREFCONTROL_OutputCode_DEF                (0x00000000)
  #define DDRDATACH0_CR_DDRCRVREFCONTROL_OutputCode_HSH                (0x08183074)

#define DDRDATACH0_CR_DDRCRVSSHICONTROL_REG                            (0x00003078)

  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_VssHiCtl_OFF                 ( 0)
  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_VssHiCtl_WID                 (25)
  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_VssHiCtl_MSK                 (0x01FFFFFF)
  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_VssHiCtl_MIN                 (0)
  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_VssHiCtl_MAX                 (33554431) // 0x01FFFFFF
  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_VssHiCtl_DEF                 (0x014D8234)
  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_VssHiCtl_HSH                 (0x19003078)

  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_OutputCode_OFF               (25)
  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_OutputCode_WID               ( 7)
  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_OutputCode_MSK               (0xFE000000)
  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_OutputCode_MIN               (0)
  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_OutputCode_MAX               (127) // 0x0000007F
  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_OutputCode_DEF               (0x00000000)
  #define DDRDATACH0_CR_DDRCRVSSHICONTROL_OutputCode_HSH               (0x07193078)

#define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_REG                         (0x0000307C)

  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_OFF           ( 0)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_WID           ( 6)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MSK           (0x0000003F)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MIN           (-32)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MAX           (31) // 0x0000001F
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_DEF           (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_HSH           (0x8600307C)

  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_OFF           ( 6)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_WID           ( 6)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MSK           (0x00000FC0)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MIN           (-32)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MAX           (31) // 0x0000001F
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_DEF           (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_HSH           (0x8606307C)

  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_OFF            (12)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_WID            ( 6)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MSK            (0x0003F000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MIN            (-32)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MAX            (31) // 0x0000001F
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_DEF            (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_HSH            (0x860C307C)

  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_OFF           (18)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_WID           ( 6)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MSK           (0x00FC0000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MIN           (-32)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MAX           (31) // 0x0000001F
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_DEF           (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_HSH           (0x8612307C)

  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_OFF            (24)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_WID            ( 7)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MSK            (0x7F000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MIN            (-64)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MAX            (63) // 0x0000003F
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_DEF            (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_HSH            (0x8718307C)

  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_Spare_OFF                 (31)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_Spare_WID                 ( 1)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_Spare_MSK                 (0x80000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_Spare_MIN                 (0)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_Spare_MAX                 (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_Spare_DEF                 (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_Spare_HSH                 (0x011F307C)

#define DDRDATACH0_CR_DDRCRDATACONTROL0_REG                            (0x00003080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxTrainingMode_OFF           ( 0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxTrainingMode_WID           ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxTrainingMode_MSK           (0x00000001)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxTrainingMode_MIN           (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxTrainingMode_MAX           (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxTrainingMode_DEF           (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxTrainingMode_HSH           (0x01003080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_WLTrainingMode_OFF           ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_WLTrainingMode_WID           ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_WLTrainingMode_MSK           (0x00000002)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_WLTrainingMode_MIN           (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_WLTrainingMode_MAX           (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_WLTrainingMode_DEF           (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_WLTrainingMode_HSH           (0x01013080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RLTrainingMode_OFF           ( 2)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RLTrainingMode_WID           ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RLTrainingMode_MSK           (0x00000004)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RLTrainingMode_MIN           (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RLTrainingMode_MAX           (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RLTrainingMode_DEF           (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RLTrainingMode_HSH           (0x01023080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_OFF     ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_WID     ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MSK     (0x00000008)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MIN     (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MAX     (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_DEF     (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_HSH     (0x01033080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxOn_OFF                     ( 4)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxOn_WID                     ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxOn_MSK                     (0x00000010)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxOn_MIN                     (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxOn_MAX                     (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxOn_DEF                     (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxOn_HSH                     (0x01043080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RfOn_OFF                     ( 5)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RfOn_WID                     ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RfOn_MSK                     (0x00000020)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RfOn_MIN                     (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RfOn_MAX                     (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RfOn_DEF                     (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RfOn_HSH                     (0x01053080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxPiOn_OFF                   ( 6)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxPiOn_WID                   ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxPiOn_MSK                   (0x00000040)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxPiOn_MIN                   (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxPiOn_MAX                   (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxPiOn_DEF                   (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxPiOn_HSH                   (0x01063080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxPiOn_OFF                   ( 7)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxPiOn_WID                   ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxPiOn_MSK                   (0x00000080)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxPiOn_MIN                   (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxPiOn_MAX                   (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxPiOn_DEF                   (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxPiOn_HSH                   (0x01073080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_InternalClocksOn_OFF         ( 8)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_InternalClocksOn_WID         ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_InternalClocksOn_MSK         (0x00000100)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_InternalClocksOn_MIN         (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_InternalClocksOn_MAX         (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_InternalClocksOn_DEF         (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_InternalClocksOn_HSH         (0x01083080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_OFF         ( 9)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_WID         ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MSK         (0x00000200)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MIN         (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MAX         (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_DEF         (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_HSH         (0x01093080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxDisable_OFF                (10)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxDisable_WID                ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxDisable_MSK                (0x00000400)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxDisable_MIN                (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxDisable_MAX                (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxDisable_DEF                (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxDisable_HSH                (0x010A3080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDisable_OFF                (11)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDisable_WID                ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDisable_MSK                (0x00000800)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDisable_MIN                (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDisable_MAX                (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDisable_DEF                (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDisable_HSH                (0x010B3080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxLong_OFF                   (12)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxLong_WID                   ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxLong_MSK                   (0x00001000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxLong_MIN                   (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxLong_MAX                   (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxLong_DEF                   (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_TxLong_HSH                   (0x010C3080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDqsCtle_OFF                (13)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDqsCtle_WID                ( 2)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDqsCtle_MSK                (0x00006000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDqsCtle_MIN                (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDqsCtle_MAX                (3) // 0x00000003
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDqsCtle_DEF                (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxDqsCtle_HSH                (0x020D3080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxReadPointer_OFF            (15)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxReadPointer_WID            ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxReadPointer_MSK            (0x00038000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxReadPointer_MIN            (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxReadPointer_MAX            (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxReadPointer_DEF            (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_RxReadPointer_HSH            (0x030F3080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LongOdtR2W_OFF               (18)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LongOdtR2W_WID               ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LongOdtR2W_MSK               (0x00040000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LongOdtR2W_MIN               (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LongOdtR2W_MAX               (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LongOdtR2W_DEF               (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LongOdtR2W_HSH               (0x01123080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DataVccddqHi_OFF             (19)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DataVccddqHi_WID             ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DataVccddqHi_MSK             (0x00080000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DataVccddqHi_MIN             (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DataVccddqHi_MAX             (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DataVccddqHi_DEF             (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DataVccddqHi_HSH             (0x01133080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRd_OFF                 (20)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRd_WID                 ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRd_MSK                 (0x00100000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRd_MIN                 (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRd_MAX                 (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRd_DEF                 (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRd_HSH                 (0x01143080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFWr_OFF                 (21)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFWr_WID                 ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFWr_MSK                 (0x00200000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFWr_MIN                 (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFWr_MAX                 (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFWr_DEF                 (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFWr_HSH                 (0x01153080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRank_OFF               (22)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRank_WID               ( 2)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRank_MSK               (0x00C00000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRank_MIN               (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRank_MAX               (3) // 0x00000003
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRank_DEF               (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ReadRFRank_HSH               (0x02163080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ForceOdtOn_OFF               (24)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ForceOdtOn_WID               ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ForceOdtOn_MSK               (0x01000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ForceOdtOn_MIN               (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ForceOdtOn_MAX               (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ForceOdtOn_DEF               (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_ForceOdtOn_HSH               (0x01183080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampOff_OFF               (25)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampOff_WID               ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampOff_MSK               (0x02000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampOff_MIN               (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampOff_MAX               (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampOff_DEF               (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampOff_HSH               (0x01193080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_OFF         (26)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_WID         ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_MSK         (0x04000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_MIN         (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_MAX         (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_DEF         (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_HSH         (0x011A3080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_OFF          (27)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_WID          ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MSK          (0x08000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MIN          (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MAX          (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_DEF          (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_HSH          (0x011B3080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_OFF               (28)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_WID               ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_MSK               (0x10000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_MIN               (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_MAX               (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_DEF               (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_HSH               (0x011C3080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EnReadPreamble_OFF           (29)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EnReadPreamble_WID           ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EnReadPreamble_MSK           (0x20000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EnReadPreamble_MIN           (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EnReadPreamble_MAX           (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EnReadPreamble_DEF           (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EnReadPreamble_HSH           (0x011D3080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_OFF          (30)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_WID          ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MSK          (0x40000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MIN          (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MAX          (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_DEF          (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_HSH          (0x011E3080)

  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_OFF             (31)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_WID             ( 1)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_MSK             (0x80000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_MIN             (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_MAX             (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_DEF             (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_HSH             (0x011F3080)

#define DDRDATACH0_CR_DDRCRVREFADJUST1_REG                             (0x00003084)

  #define DDRDATACH0_CR_DDRCRVREFADJUST1_CAVrefCtl_OFF                 ( 0)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_CAVrefCtl_WID                 ( 7)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_CAVrefCtl_MSK                 (0x0000007F)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_CAVrefCtl_MIN                 (-64)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_CAVrefCtl_MAX                 (63) // 0x0000003F
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_CAVrefCtl_DEF                 (0x00000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_CAVrefCtl_HSH                 (0x87003084)

  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_OFF                ( 7)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_WID                ( 7)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MSK                (0x00003F80)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MIN                (-64)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MAX                (63) // 0x0000003F
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_DEF                (0x00000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_HSH                (0x87073084)

  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_OFF                (14)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_WID                ( 7)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MSK                (0x001FC000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MIN                (-64)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MAX                (63) // 0x0000003F
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_DEF                (0x00000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_HSH                (0x870E3084)

  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_OFF              (21)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_WID              ( 1)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MSK              (0x00200000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MIN              (0)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MAX              (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_DEF              (0x00000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_HSH              (0x01153084)

  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_OFF             (22)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_WID             ( 1)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MSK             (0x00400000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MIN             (0)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MAX             (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_DEF             (0x00000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_HSH             (0x01163084)

  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_OFF             (23)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_WID             ( 1)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MSK             (0x00800000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MIN             (0)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MAX             (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_DEF             (0x00000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_HSH             (0x01173084)

  #define DDRDATACH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_OFF              (24)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_WID              ( 2)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MSK              (0x03000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MIN              (0)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MAX              (3) // 0x00000003
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_DEF              (0x00000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_HSH              (0x02183084)

  #define DDRDATACH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_OFF             (26)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_WID             ( 1)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MSK             (0x04000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MIN             (0)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MAX             (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_DEF             (0x00000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_HSH             (0x011A3084)

  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Rsvd_OFF                      (27)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Rsvd_WID                      ( 2)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Rsvd_MSK                      (0x18000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Rsvd_MIN                      (0)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Rsvd_MAX                      (3) // 0x00000003
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Rsvd_DEF                      (0x00000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_Rsvd_HSH                      (0x021B3084)

  #define DDRDATACH0_CR_DDRCRVREFADJUST1_caSlowBW_OFF                  (29)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_caSlowBW_WID                  ( 1)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_caSlowBW_MSK                  (0x20000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_caSlowBW_MIN                  (0)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_caSlowBW_MAX                  (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_caSlowBW_DEF                  (0x00000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_caSlowBW_HSH                  (0x011D3084)

  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch0SlowBW_OFF                 (30)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch0SlowBW_WID                 ( 1)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch0SlowBW_MSK                 (0x40000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch0SlowBW_MIN                 (0)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch0SlowBW_MAX                 (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch0SlowBW_DEF                 (0x00000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch0SlowBW_HSH                 (0x011E3084)

  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch1SlowBW_OFF                 (31)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch1SlowBW_WID                 ( 1)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch1SlowBW_MSK                 (0x80000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch1SlowBW_MIN                 (0)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch1SlowBW_MAX                 (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch1SlowBW_DEF                 (0x00000000)
  #define DDRDATACH0_CR_DDRCRVREFADJUST1_ch1SlowBW_HSH                 (0x011F3084)

#define DDRDATACH0_CR_DDRCRDATACONTROL3_REG                            (0x00003088)

  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_OFF         ( 0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_WID         ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_MSK         (0x00000007)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_MIN         (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_MAX         (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_DEF         (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_HSH         (0x03003088)

  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_OFF         ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_WID         ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_MSK         (0x00000038)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_MIN         (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_MAX         (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_DEF         (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_HSH         (0x03033088)

  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_OFF         ( 6)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_WID         ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_MSK         (0x000001C0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_MIN         (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_MAX         (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_DEF         (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_HSH         (0x03063088)

  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_OFF         ( 9)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_WID         ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_MSK         (0x00000E00)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_MIN         (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_MAX         (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_DEF         (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_HSH         (0x03093088)

  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_OFF         (12)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_WID         ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_MSK         (0x00007000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_MIN         (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_MAX         (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_DEF         (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_HSH         (0x030C3088)

  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_OFF         (15)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_WID         ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_MSK         (0x00038000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_MIN         (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_MAX         (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_DEF         (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_HSH         (0x030F3088)

  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_OFF         (18)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_WID         ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_MSK         (0x001C0000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_MIN         (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_MAX         (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_DEF         (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_HSH         (0x03123088)

  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_OFF         (21)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_WID         ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_MSK         (0x00E00000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_MIN         (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_MAX         (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_DEF         (0x00000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_HSH         (0x03153088)

  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp2_OFF                 (24)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp2_WID                 ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp2_MSK                 (0x07000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp2_MIN                 (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp2_MAX                 (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp2_DEF                 (0x00000003)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp2_HSH                 (0x03183088)

  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_OFF              (27)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_WID              ( 3)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MSK              (0x38000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MIN              (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MAX              (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_DEF              (0x00000003)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_HSH              (0x031B3088)

  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp1_OFF                 (30)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp1_WID                 ( 2)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp1_MSK                 (0xC0000000)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp1_MIN                 (0)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp1_MAX                 (3) // 0x00000003
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp1_DEF                 (0x00000001)
  #define DDRDATACH0_CR_DDRCRDATACONTROL3_CBEnAmp1_HSH                 (0x021E3088)

#define DDRDATACH0_CR_DDRCRVTTGENCONTROL_REG                           (0x0000308C)

  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Target_OFF                  ( 0)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Target_WID                  ( 4)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Target_MSK                  (0x0000000F)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Target_MIN                  (0)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Target_MAX                  (15) // 0x0000000F
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Target_DEF                  (0x00000000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Target_HSH                  (0x0400308C)

  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Panic_OFF                   ( 4)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Panic_WID                   ( 5)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Panic_MSK                   (0x000001F0)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Panic_MIN                   (0)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Panic_MAX                   (31) // 0x0000001F
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Panic_DEF                   (0x00000010)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Panic_HSH                   (0x0504308C)

  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_OFF             ( 9)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_WID             ( 2)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MSK             (0x00000600)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MIN             (0)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MAX             (3) // 0x00000003
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_DEF             (0x00000000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_HSH             (0x0209308C)

  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_OFF          (11)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_WID          ( 1)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MSK          (0x00000800)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MIN          (0)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MAX          (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_DEF          (0x00000000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_HSH          (0x010B308C)

  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_OFF              (12)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_WID              ( 1)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MSK              (0x00001000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MIN              (0)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MAX              (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_DEF              (0x00000000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_HSH              (0x010C308C)

  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_OFF             (13)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_WID             ( 3)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MSK             (0x0000E000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MIN             (0)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MAX             (7) // 0x00000007
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_DEF             (0x00000000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_HSH             (0x030D308C)

  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_OFF       (16)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_WID       ( 1)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MSK       (0x00010000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MIN       (0)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MAX       (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_DEF       (0x00000000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_HSH       (0x0110308C)

  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Spares_OFF                  (17)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Spares_WID                  ( 8)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Spares_MSK                  (0x01FE0000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Spares_MIN                  (0)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Spares_MAX                  (255) // 0x000000FF
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Spares_DEF                  (0x00000000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Spares_HSH                  (0x0811308C)

  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_OFF              (25)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_WID              ( 1)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MSK              (0x02000000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MIN              (0)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MAX              (1) // 0x00000001
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_DEF              (0x00000000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_HSH              (0x0119308C)

  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_OFF          (26)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_WID          ( 6)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MSK          (0xFC000000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MIN          (0)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MAX          (63) // 0x0000003F
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_DEF          (0x00000000)
  #define DDRDATACH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_HSH          (0x061A308C)

#define DDRDATACH1_CR_RXTRAINRANK0_REG                                 (0x00003100)

  #define DDRDATACH1_CR_RXTRAINRANK0_RxRcvEnPi_OFF                     ( 0)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxRcvEnPi_WID                     ( 9)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxRcvEnPi_MSK                     (0x000001FF)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxRcvEnPi_MIN                     (0)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxRcvEnPi_MAX                     (511) // 0x000001FF
  #define DDRDATACH1_CR_RXTRAINRANK0_RxRcvEnPi_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxRcvEnPi_HSH                     (0x09003100)

  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsPPi_OFF                      ( 9)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsPPi_WID                      ( 6)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsPPi_MSK                      (0x00007E00)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsPPi_MIN                      (0)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsPPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsPPi_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsPPi_HSH                      (0x06093100)

  #define DDRDATACH1_CR_RXTRAINRANK0_RxEq_OFF                          (15)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxEq_WID                          ( 5)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxEq_MSK                          (0x000F8000)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxEq_MIN                          (0)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxEq_MAX                          (31) // 0x0000001F
  #define DDRDATACH1_CR_RXTRAINRANK0_RxEq_DEF                          (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxEq_HSH                          (0x050F3100)

  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsNPi_OFF                      (20)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsNPi_WID                      ( 6)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsNPi_MSK                      (0x03F00000)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsNPi_MIN                      (0)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsNPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsNPi_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxDqsNPi_HSH                      (0x06143100)

  #define DDRDATACH1_CR_RXTRAINRANK0_RxVref_OFF                        (26)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxVref_WID                        ( 6)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxVref_MSK                        (0xFC000000)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxVref_MIN                        (-32)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxVref_MAX                        (31) // 0x0000001F
  #define DDRDATACH1_CR_RXTRAINRANK0_RxVref_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK0_RxVref_HSH                        (0x861A3100)

#define DDRDATACH1_CR_RXTRAINRANK1_REG                                 (0x00003104)

  #define DDRDATACH1_CR_RXTRAINRANK1_RxRcvEnPi_OFF                     ( 0)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxRcvEnPi_WID                     ( 9)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxRcvEnPi_MSK                     (0x000001FF)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxRcvEnPi_MIN                     (0)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxRcvEnPi_MAX                     (511) // 0x000001FF
  #define DDRDATACH1_CR_RXTRAINRANK1_RxRcvEnPi_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxRcvEnPi_HSH                     (0x09003104)

  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsPPi_OFF                      ( 9)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsPPi_WID                      ( 6)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsPPi_MSK                      (0x00007E00)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsPPi_MIN                      (0)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsPPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsPPi_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsPPi_HSH                      (0x06093104)

  #define DDRDATACH1_CR_RXTRAINRANK1_RxEq_OFF                          (15)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxEq_WID                          ( 5)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxEq_MSK                          (0x000F8000)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxEq_MIN                          (0)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxEq_MAX                          (31) // 0x0000001F
  #define DDRDATACH1_CR_RXTRAINRANK1_RxEq_DEF                          (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxEq_HSH                          (0x050F3104)

  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsNPi_OFF                      (20)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsNPi_WID                      ( 6)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsNPi_MSK                      (0x03F00000)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsNPi_MIN                      (0)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsNPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsNPi_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxDqsNPi_HSH                      (0x06143104)

  #define DDRDATACH1_CR_RXTRAINRANK1_RxVref_OFF                        (26)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxVref_WID                        ( 6)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxVref_MSK                        (0xFC000000)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxVref_MIN                        (-32)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxVref_MAX                        (31) // 0x0000001F
  #define DDRDATACH1_CR_RXTRAINRANK1_RxVref_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK1_RxVref_HSH                        (0x861A3104)

#define DDRDATACH1_CR_RXTRAINRANK2_REG                                 (0x00003108)

  #define DDRDATACH1_CR_RXTRAINRANK2_RxRcvEnPi_OFF                     ( 0)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxRcvEnPi_WID                     ( 9)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxRcvEnPi_MSK                     (0x000001FF)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxRcvEnPi_MIN                     (0)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxRcvEnPi_MAX                     (511) // 0x000001FF
  #define DDRDATACH1_CR_RXTRAINRANK2_RxRcvEnPi_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxRcvEnPi_HSH                     (0x09003108)

  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsPPi_OFF                      ( 9)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsPPi_WID                      ( 6)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsPPi_MSK                      (0x00007E00)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsPPi_MIN                      (0)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsPPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsPPi_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsPPi_HSH                      (0x06093108)

  #define DDRDATACH1_CR_RXTRAINRANK2_RxEq_OFF                          (15)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxEq_WID                          ( 5)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxEq_MSK                          (0x000F8000)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxEq_MIN                          (0)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxEq_MAX                          (31) // 0x0000001F
  #define DDRDATACH1_CR_RXTRAINRANK2_RxEq_DEF                          (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxEq_HSH                          (0x050F3108)

  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsNPi_OFF                      (20)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsNPi_WID                      ( 6)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsNPi_MSK                      (0x03F00000)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsNPi_MIN                      (0)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsNPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsNPi_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxDqsNPi_HSH                      (0x06143108)

  #define DDRDATACH1_CR_RXTRAINRANK2_RxVref_OFF                        (26)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxVref_WID                        ( 6)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxVref_MSK                        (0xFC000000)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxVref_MIN                        (-32)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxVref_MAX                        (31) // 0x0000001F
  #define DDRDATACH1_CR_RXTRAINRANK2_RxVref_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK2_RxVref_HSH                        (0x861A3108)

#define DDRDATACH1_CR_RXTRAINRANK3_REG                                 (0x0000310C)

  #define DDRDATACH1_CR_RXTRAINRANK3_RxRcvEnPi_OFF                     ( 0)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxRcvEnPi_WID                     ( 9)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxRcvEnPi_MSK                     (0x000001FF)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxRcvEnPi_MIN                     (0)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxRcvEnPi_MAX                     (511) // 0x000001FF
  #define DDRDATACH1_CR_RXTRAINRANK3_RxRcvEnPi_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxRcvEnPi_HSH                     (0x0900310C)

  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsPPi_OFF                      ( 9)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsPPi_WID                      ( 6)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsPPi_MSK                      (0x00007E00)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsPPi_MIN                      (0)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsPPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsPPi_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsPPi_HSH                      (0x0609310C)

  #define DDRDATACH1_CR_RXTRAINRANK3_RxEq_OFF                          (15)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxEq_WID                          ( 5)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxEq_MSK                          (0x000F8000)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxEq_MIN                          (0)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxEq_MAX                          (31) // 0x0000001F
  #define DDRDATACH1_CR_RXTRAINRANK3_RxEq_DEF                          (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxEq_HSH                          (0x050F310C)

  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsNPi_OFF                      (20)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsNPi_WID                      ( 6)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsNPi_MSK                      (0x03F00000)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsNPi_MIN                      (0)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsNPi_MAX                      (63) // 0x0000003F
  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsNPi_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxDqsNPi_HSH                      (0x0614310C)

  #define DDRDATACH1_CR_RXTRAINRANK3_RxVref_OFF                        (26)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxVref_WID                        ( 6)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxVref_MSK                        (0xFC000000)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxVref_MIN                        (-32)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxVref_MAX                        (31) // 0x0000001F
  #define DDRDATACH1_CR_RXTRAINRANK3_RxVref_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXTRAINRANK3_RxVref_HSH                        (0x861A310C)

#define DDRDATACH1_CR_RXPERBITRANK0_REG                                (0x00003110)

  #define DDRDATACH1_CR_RXPERBITRANK0_Lane0_OFF                        ( 0)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane0_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane0_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane0_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane0_HSH                        (0x04003110)

  #define DDRDATACH1_CR_RXPERBITRANK0_Lane1_OFF                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane1_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane1_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane1_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane1_HSH                        (0x04043110)

  #define DDRDATACH1_CR_RXPERBITRANK0_Lane2_OFF                        ( 8)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane2_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane2_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane2_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane2_HSH                        (0x04083110)

  #define DDRDATACH1_CR_RXPERBITRANK0_Lane3_OFF                        (12)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane3_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane3_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane3_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane3_HSH                        (0x040C3110)

  #define DDRDATACH1_CR_RXPERBITRANK0_Lane4_OFF                        (16)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane4_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane4_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane4_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane4_HSH                        (0x04103110)

  #define DDRDATACH1_CR_RXPERBITRANK0_Lane5_OFF                        (20)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane5_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane5_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane5_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane5_HSH                        (0x04143110)

  #define DDRDATACH1_CR_RXPERBITRANK0_Lane6_OFF                        (24)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane6_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane6_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane6_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane6_HSH                        (0x04183110)

  #define DDRDATACH1_CR_RXPERBITRANK0_Lane7_OFF                        (28)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane7_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane7_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane7_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK0_Lane7_HSH                        (0x041C3110)

#define DDRDATACH1_CR_RXPERBITRANK1_REG                                (0x00003114)

  #define DDRDATACH1_CR_RXPERBITRANK1_Lane0_OFF                        ( 0)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane0_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane0_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane0_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane0_HSH                        (0x04003114)

  #define DDRDATACH1_CR_RXPERBITRANK1_Lane1_OFF                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane1_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane1_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane1_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane1_HSH                        (0x04043114)

  #define DDRDATACH1_CR_RXPERBITRANK1_Lane2_OFF                        ( 8)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane2_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane2_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane2_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane2_HSH                        (0x04083114)

  #define DDRDATACH1_CR_RXPERBITRANK1_Lane3_OFF                        (12)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane3_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane3_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane3_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane3_HSH                        (0x040C3114)

  #define DDRDATACH1_CR_RXPERBITRANK1_Lane4_OFF                        (16)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane4_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane4_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane4_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane4_HSH                        (0x04103114)

  #define DDRDATACH1_CR_RXPERBITRANK1_Lane5_OFF                        (20)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane5_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane5_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane5_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane5_HSH                        (0x04143114)

  #define DDRDATACH1_CR_RXPERBITRANK1_Lane6_OFF                        (24)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane6_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane6_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane6_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane6_HSH                        (0x04183114)

  #define DDRDATACH1_CR_RXPERBITRANK1_Lane7_OFF                        (28)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane7_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane7_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane7_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK1_Lane7_HSH                        (0x041C3114)

#define DDRDATACH1_CR_RXPERBITRANK2_REG                                (0x00003118)

  #define DDRDATACH1_CR_RXPERBITRANK2_Lane0_OFF                        ( 0)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane0_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane0_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane0_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane0_HSH                        (0x04003118)

  #define DDRDATACH1_CR_RXPERBITRANK2_Lane1_OFF                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane1_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane1_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane1_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane1_HSH                        (0x04043118)

  #define DDRDATACH1_CR_RXPERBITRANK2_Lane2_OFF                        ( 8)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane2_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane2_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane2_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane2_HSH                        (0x04083118)

  #define DDRDATACH1_CR_RXPERBITRANK2_Lane3_OFF                        (12)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane3_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane3_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane3_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane3_HSH                        (0x040C3118)

  #define DDRDATACH1_CR_RXPERBITRANK2_Lane4_OFF                        (16)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane4_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane4_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane4_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane4_HSH                        (0x04103118)

  #define DDRDATACH1_CR_RXPERBITRANK2_Lane5_OFF                        (20)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane5_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane5_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane5_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane5_HSH                        (0x04143118)

  #define DDRDATACH1_CR_RXPERBITRANK2_Lane6_OFF                        (24)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane6_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane6_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane6_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane6_HSH                        (0x04183118)

  #define DDRDATACH1_CR_RXPERBITRANK2_Lane7_OFF                        (28)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane7_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane7_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane7_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK2_Lane7_HSH                        (0x041C3118)

#define DDRDATACH1_CR_RXPERBITRANK3_REG                                (0x0000311C)

  #define DDRDATACH1_CR_RXPERBITRANK3_Lane0_OFF                        ( 0)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane0_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane0_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane0_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane0_HSH                        (0x0400311C)

  #define DDRDATACH1_CR_RXPERBITRANK3_Lane1_OFF                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane1_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane1_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane1_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane1_HSH                        (0x0404311C)

  #define DDRDATACH1_CR_RXPERBITRANK3_Lane2_OFF                        ( 8)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane2_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane2_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane2_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane2_HSH                        (0x0408311C)

  #define DDRDATACH1_CR_RXPERBITRANK3_Lane3_OFF                        (12)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane3_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane3_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane3_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane3_HSH                        (0x040C311C)

  #define DDRDATACH1_CR_RXPERBITRANK3_Lane4_OFF                        (16)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane4_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane4_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane4_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane4_HSH                        (0x0410311C)

  #define DDRDATACH1_CR_RXPERBITRANK3_Lane5_OFF                        (20)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane5_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane5_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane5_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane5_HSH                        (0x0414311C)

  #define DDRDATACH1_CR_RXPERBITRANK3_Lane6_OFF                        (24)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane6_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane6_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane6_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane6_HSH                        (0x0418311C)

  #define DDRDATACH1_CR_RXPERBITRANK3_Lane7_OFF                        (28)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane7_WID                        ( 4)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane7_MIN                        (0)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane7_DEF                        (0x00000000)
  #define DDRDATACH1_CR_RXPERBITRANK3_Lane7_HSH                        (0x041C311C)

#define DDRDATACH1_CR_TXTRAINRANK0_REG                                 (0x00003120)

  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqDelay_OFF                     ( 0)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqDelay_WID                     ( 9)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqDelay_MSK                     (0x000001FF)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqDelay_MIN                     (0)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqDelay_MAX                     (511) // 0x000001FF
  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqDelay_DEF                     (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqDelay_HSH                     (0x09003120)

  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqsDelay_OFF                    ( 9)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqsDelay_WID                    ( 9)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqsDelay_MSK                    (0x0003FE00)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqsDelay_MIN                    (0)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqsDelay_MAX                    (511) // 0x000001FF
  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqsDelay_DEF                    (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxDqsDelay_HSH                    (0x09093120)

  #define DDRDATACH1_CR_TXTRAINRANK0_Spare0_OFF                        (18)
  #define DDRDATACH1_CR_TXTRAINRANK0_Spare0_WID                        ( 2)
  #define DDRDATACH1_CR_TXTRAINRANK0_Spare0_MSK                        (0x000C0000)
  #define DDRDATACH1_CR_TXTRAINRANK0_Spare0_MIN                        (0)
  #define DDRDATACH1_CR_TXTRAINRANK0_Spare0_MAX                        (3) // 0x00000003
  #define DDRDATACH1_CR_TXTRAINRANK0_Spare0_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK0_Spare0_HSH                        (0x02123120)

  #define DDRDATACH1_CR_TXTRAINRANK0_TxEqualization_OFF                (20)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxEqualization_WID                ( 6)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxEqualization_MSK                (0x03F00000)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxEqualization_MIN                (0)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxEqualization_MAX                (63) // 0x0000003F
  #define DDRDATACH1_CR_TXTRAINRANK0_TxEqualization_DEF                (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK0_TxEqualization_HSH                (0x06143120)

  #define DDRDATACH1_CR_TXTRAINRANK0_Spare1_OFF                        (26)
  #define DDRDATACH1_CR_TXTRAINRANK0_Spare1_WID                        ( 6)
  #define DDRDATACH1_CR_TXTRAINRANK0_Spare1_MSK                        (0xFC000000)
  #define DDRDATACH1_CR_TXTRAINRANK0_Spare1_MIN                        (0)
  #define DDRDATACH1_CR_TXTRAINRANK0_Spare1_MAX                        (63) // 0x0000003F
  #define DDRDATACH1_CR_TXTRAINRANK0_Spare1_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK0_Spare1_HSH                        (0x061A3120)

#define DDRDATACH1_CR_TXTRAINRANK1_REG                                 (0x00003124)

  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqDelay_OFF                     ( 0)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqDelay_WID                     ( 9)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqDelay_MSK                     (0x000001FF)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqDelay_MIN                     (0)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqDelay_MAX                     (511) // 0x000001FF
  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqDelay_DEF                     (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqDelay_HSH                     (0x09003124)

  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqsDelay_OFF                    ( 9)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqsDelay_WID                    ( 9)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqsDelay_MSK                    (0x0003FE00)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqsDelay_MIN                    (0)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqsDelay_MAX                    (511) // 0x000001FF
  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqsDelay_DEF                    (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxDqsDelay_HSH                    (0x09093124)

  #define DDRDATACH1_CR_TXTRAINRANK1_Spare0_OFF                        (18)
  #define DDRDATACH1_CR_TXTRAINRANK1_Spare0_WID                        ( 2)
  #define DDRDATACH1_CR_TXTRAINRANK1_Spare0_MSK                        (0x000C0000)
  #define DDRDATACH1_CR_TXTRAINRANK1_Spare0_MIN                        (0)
  #define DDRDATACH1_CR_TXTRAINRANK1_Spare0_MAX                        (3) // 0x00000003
  #define DDRDATACH1_CR_TXTRAINRANK1_Spare0_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK1_Spare0_HSH                        (0x02123124)

  #define DDRDATACH1_CR_TXTRAINRANK1_TxEqualization_OFF                (20)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxEqualization_WID                ( 6)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxEqualization_MSK                (0x03F00000)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxEqualization_MIN                (0)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxEqualization_MAX                (63) // 0x0000003F
  #define DDRDATACH1_CR_TXTRAINRANK1_TxEqualization_DEF                (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK1_TxEqualization_HSH                (0x06143124)

  #define DDRDATACH1_CR_TXTRAINRANK1_Spare1_OFF                        (26)
  #define DDRDATACH1_CR_TXTRAINRANK1_Spare1_WID                        ( 6)
  #define DDRDATACH1_CR_TXTRAINRANK1_Spare1_MSK                        (0xFC000000)
  #define DDRDATACH1_CR_TXTRAINRANK1_Spare1_MIN                        (0)
  #define DDRDATACH1_CR_TXTRAINRANK1_Spare1_MAX                        (63) // 0x0000003F
  #define DDRDATACH1_CR_TXTRAINRANK1_Spare1_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK1_Spare1_HSH                        (0x061A3124)

#define DDRDATACH1_CR_TXTRAINRANK2_REG                                 (0x00003128)

  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqDelay_OFF                     ( 0)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqDelay_WID                     ( 9)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqDelay_MSK                     (0x000001FF)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqDelay_MIN                     (0)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqDelay_MAX                     (511) // 0x000001FF
  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqDelay_DEF                     (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqDelay_HSH                     (0x09003128)

  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqsDelay_OFF                    ( 9)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqsDelay_WID                    ( 9)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqsDelay_MSK                    (0x0003FE00)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqsDelay_MIN                    (0)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqsDelay_MAX                    (511) // 0x000001FF
  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqsDelay_DEF                    (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxDqsDelay_HSH                    (0x09093128)

  #define DDRDATACH1_CR_TXTRAINRANK2_Spare0_OFF                        (18)
  #define DDRDATACH1_CR_TXTRAINRANK2_Spare0_WID                        ( 2)
  #define DDRDATACH1_CR_TXTRAINRANK2_Spare0_MSK                        (0x000C0000)
  #define DDRDATACH1_CR_TXTRAINRANK2_Spare0_MIN                        (0)
  #define DDRDATACH1_CR_TXTRAINRANK2_Spare0_MAX                        (3) // 0x00000003
  #define DDRDATACH1_CR_TXTRAINRANK2_Spare0_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK2_Spare0_HSH                        (0x02123128)

  #define DDRDATACH1_CR_TXTRAINRANK2_TxEqualization_OFF                (20)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxEqualization_WID                ( 6)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxEqualization_MSK                (0x03F00000)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxEqualization_MIN                (0)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxEqualization_MAX                (63) // 0x0000003F
  #define DDRDATACH1_CR_TXTRAINRANK2_TxEqualization_DEF                (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK2_TxEqualization_HSH                (0x06143128)

  #define DDRDATACH1_CR_TXTRAINRANK2_Spare1_OFF                        (26)
  #define DDRDATACH1_CR_TXTRAINRANK2_Spare1_WID                        ( 6)
  #define DDRDATACH1_CR_TXTRAINRANK2_Spare1_MSK                        (0xFC000000)
  #define DDRDATACH1_CR_TXTRAINRANK2_Spare1_MIN                        (0)
  #define DDRDATACH1_CR_TXTRAINRANK2_Spare1_MAX                        (63) // 0x0000003F
  #define DDRDATACH1_CR_TXTRAINRANK2_Spare1_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK2_Spare1_HSH                        (0x061A3128)

#define DDRDATACH1_CR_TXTRAINRANK3_REG                                 (0x0000312C)

  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqDelay_OFF                     ( 0)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqDelay_WID                     ( 9)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqDelay_MSK                     (0x000001FF)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqDelay_MIN                     (0)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqDelay_MAX                     (511) // 0x000001FF
  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqDelay_DEF                     (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqDelay_HSH                     (0x0900312C)

  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqsDelay_OFF                    ( 9)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqsDelay_WID                    ( 9)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqsDelay_MSK                    (0x0003FE00)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqsDelay_MIN                    (0)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqsDelay_MAX                    (511) // 0x000001FF
  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqsDelay_DEF                    (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxDqsDelay_HSH                    (0x0909312C)

  #define DDRDATACH1_CR_TXTRAINRANK3_Spare0_OFF                        (18)
  #define DDRDATACH1_CR_TXTRAINRANK3_Spare0_WID                        ( 2)
  #define DDRDATACH1_CR_TXTRAINRANK3_Spare0_MSK                        (0x000C0000)
  #define DDRDATACH1_CR_TXTRAINRANK3_Spare0_MIN                        (0)
  #define DDRDATACH1_CR_TXTRAINRANK3_Spare0_MAX                        (3) // 0x00000003
  #define DDRDATACH1_CR_TXTRAINRANK3_Spare0_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK3_Spare0_HSH                        (0x0212312C)

  #define DDRDATACH1_CR_TXTRAINRANK3_TxEqualization_OFF                (20)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxEqualization_WID                ( 6)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxEqualization_MSK                (0x03F00000)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxEqualization_MIN                (0)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxEqualization_MAX                (63) // 0x0000003F
  #define DDRDATACH1_CR_TXTRAINRANK3_TxEqualization_DEF                (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK3_TxEqualization_HSH                (0x0614312C)

  #define DDRDATACH1_CR_TXTRAINRANK3_Spare1_OFF                        (26)
  #define DDRDATACH1_CR_TXTRAINRANK3_Spare1_WID                        ( 6)
  #define DDRDATACH1_CR_TXTRAINRANK3_Spare1_MSK                        (0xFC000000)
  #define DDRDATACH1_CR_TXTRAINRANK3_Spare1_MIN                        (0)
  #define DDRDATACH1_CR_TXTRAINRANK3_Spare1_MAX                        (63) // 0x0000003F
  #define DDRDATACH1_CR_TXTRAINRANK3_Spare1_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXTRAINRANK3_Spare1_HSH                        (0x061A312C)

#define DDRDATACH1_CR_TXPERBITRANK0_REG                                (0x00003130)

  #define DDRDATACH1_CR_TXPERBITRANK0_Lane0_OFF                        ( 0)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane0_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane0_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane0_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane0_HSH                        (0x04003130)

  #define DDRDATACH1_CR_TXPERBITRANK0_Lane1_OFF                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane1_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane1_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane1_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane1_HSH                        (0x04043130)

  #define DDRDATACH1_CR_TXPERBITRANK0_Lane2_OFF                        ( 8)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane2_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane2_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane2_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane2_HSH                        (0x04083130)

  #define DDRDATACH1_CR_TXPERBITRANK0_Lane3_OFF                        (12)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane3_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane3_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane3_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane3_HSH                        (0x040C3130)

  #define DDRDATACH1_CR_TXPERBITRANK0_Lane4_OFF                        (16)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane4_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane4_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane4_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane4_HSH                        (0x04103130)

  #define DDRDATACH1_CR_TXPERBITRANK0_Lane5_OFF                        (20)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane5_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane5_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane5_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane5_HSH                        (0x04143130)

  #define DDRDATACH1_CR_TXPERBITRANK0_Lane6_OFF                        (24)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane6_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane6_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane6_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane6_HSH                        (0x04183130)

  #define DDRDATACH1_CR_TXPERBITRANK0_Lane7_OFF                        (28)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane7_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane7_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane7_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK0_Lane7_HSH                        (0x041C3130)

#define DDRDATACH1_CR_TXPERBITRANK1_REG                                (0x00003134)

  #define DDRDATACH1_CR_TXPERBITRANK1_Lane0_OFF                        ( 0)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane0_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane0_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane0_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane0_HSH                        (0x04003134)

  #define DDRDATACH1_CR_TXPERBITRANK1_Lane1_OFF                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane1_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane1_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane1_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane1_HSH                        (0x04043134)

  #define DDRDATACH1_CR_TXPERBITRANK1_Lane2_OFF                        ( 8)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane2_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane2_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane2_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane2_HSH                        (0x04083134)

  #define DDRDATACH1_CR_TXPERBITRANK1_Lane3_OFF                        (12)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane3_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane3_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane3_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane3_HSH                        (0x040C3134)

  #define DDRDATACH1_CR_TXPERBITRANK1_Lane4_OFF                        (16)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane4_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane4_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane4_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane4_HSH                        (0x04103134)

  #define DDRDATACH1_CR_TXPERBITRANK1_Lane5_OFF                        (20)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane5_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane5_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane5_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane5_HSH                        (0x04143134)

  #define DDRDATACH1_CR_TXPERBITRANK1_Lane6_OFF                        (24)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane6_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane6_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane6_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane6_HSH                        (0x04183134)

  #define DDRDATACH1_CR_TXPERBITRANK1_Lane7_OFF                        (28)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane7_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane7_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane7_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK1_Lane7_HSH                        (0x041C3134)

#define DDRDATACH1_CR_TXPERBITRANK2_REG                                (0x00003138)

  #define DDRDATACH1_CR_TXPERBITRANK2_Lane0_OFF                        ( 0)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane0_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane0_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane0_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane0_HSH                        (0x04003138)

  #define DDRDATACH1_CR_TXPERBITRANK2_Lane1_OFF                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane1_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane1_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane1_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane1_HSH                        (0x04043138)

  #define DDRDATACH1_CR_TXPERBITRANK2_Lane2_OFF                        ( 8)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane2_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane2_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane2_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane2_HSH                        (0x04083138)

  #define DDRDATACH1_CR_TXPERBITRANK2_Lane3_OFF                        (12)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane3_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane3_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane3_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane3_HSH                        (0x040C3138)

  #define DDRDATACH1_CR_TXPERBITRANK2_Lane4_OFF                        (16)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane4_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane4_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane4_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane4_HSH                        (0x04103138)

  #define DDRDATACH1_CR_TXPERBITRANK2_Lane5_OFF                        (20)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane5_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane5_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane5_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane5_HSH                        (0x04143138)

  #define DDRDATACH1_CR_TXPERBITRANK2_Lane6_OFF                        (24)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane6_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane6_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane6_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane6_HSH                        (0x04183138)

  #define DDRDATACH1_CR_TXPERBITRANK2_Lane7_OFF                        (28)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane7_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane7_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane7_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK2_Lane7_HSH                        (0x041C3138)

#define DDRDATACH1_CR_TXPERBITRANK3_REG                                (0x0000313C)

  #define DDRDATACH1_CR_TXPERBITRANK3_Lane0_OFF                        ( 0)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane0_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane0_MSK                        (0x0000000F)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane0_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane0_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane0_HSH                        (0x0400313C)

  #define DDRDATACH1_CR_TXPERBITRANK3_Lane1_OFF                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane1_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane1_MSK                        (0x000000F0)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane1_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane1_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane1_HSH                        (0x0404313C)

  #define DDRDATACH1_CR_TXPERBITRANK3_Lane2_OFF                        ( 8)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane2_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane2_MSK                        (0x00000F00)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane2_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane2_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane2_HSH                        (0x0408313C)

  #define DDRDATACH1_CR_TXPERBITRANK3_Lane3_OFF                        (12)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane3_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane3_MSK                        (0x0000F000)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane3_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane3_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane3_HSH                        (0x040C313C)

  #define DDRDATACH1_CR_TXPERBITRANK3_Lane4_OFF                        (16)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane4_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane4_MSK                        (0x000F0000)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane4_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane4_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane4_HSH                        (0x0410313C)

  #define DDRDATACH1_CR_TXPERBITRANK3_Lane5_OFF                        (20)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane5_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane5_MSK                        (0x00F00000)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane5_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane5_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane5_HSH                        (0x0414313C)

  #define DDRDATACH1_CR_TXPERBITRANK3_Lane6_OFF                        (24)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane6_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane6_MSK                        (0x0F000000)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane6_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane6_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane6_HSH                        (0x0418313C)

  #define DDRDATACH1_CR_TXPERBITRANK3_Lane7_OFF                        (28)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane7_WID                        ( 4)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane7_MSK                        (0xF0000000)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane7_MIN                        (0)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane7_DEF                        (0x00000000)
  #define DDRDATACH1_CR_TXPERBITRANK3_Lane7_HSH                        (0x041C313C)

#define DDRDATACH1_CR_RCOMPDATA0_REG                                   (0x00003140)

  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvUp_OFF                      ( 0)
  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvUp_WID                      ( 6)
  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvUp_MSK                      (0x0000003F)
  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvUp_MIN                      (0)
  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvUp_MAX                      (63) // 0x0000003F
  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvUp_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvUp_HSH                      (0x06003140)

  #define DDRDATACH1_CR_RCOMPDATA0_Rsvd_OFF                            ( 6)
  #define DDRDATACH1_CR_RCOMPDATA0_Rsvd_WID                            ( 3)
  #define DDRDATACH1_CR_RCOMPDATA0_Rsvd_MSK                            (0x000001C0)
  #define DDRDATACH1_CR_RCOMPDATA0_Rsvd_MIN                            (0)
  #define DDRDATACH1_CR_RCOMPDATA0_Rsvd_MAX                            (7) // 0x00000007
  #define DDRDATACH1_CR_RCOMPDATA0_Rsvd_DEF                            (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA0_Rsvd_HSH                            (0x03063140)

  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvDown_OFF                    ( 9)
  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvDown_WID                    ( 6)
  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvDown_MSK                    (0x00007E00)
  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvDown_MIN                    (0)
  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvDown_MAX                    (63) // 0x0000003F
  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvDown_DEF                    (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA0_RcompDrvDown_HSH                    (0x06093140)

  #define DDRDATACH1_CR_RCOMPDATA0_VTComp_OFF                          (15)
  #define DDRDATACH1_CR_RCOMPDATA0_VTComp_WID                          ( 5)
  #define DDRDATACH1_CR_RCOMPDATA0_VTComp_MSK                          (0x000F8000)
  #define DDRDATACH1_CR_RCOMPDATA0_VTComp_MIN                          (0)
  #define DDRDATACH1_CR_RCOMPDATA0_VTComp_MAX                          (31) // 0x0000001F
  #define DDRDATACH1_CR_RCOMPDATA0_VTComp_DEF                          (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA0_VTComp_HSH                          (0x050F3140)

  #define DDRDATACH1_CR_RCOMPDATA0_SlewRateComp_OFF                    (20)
  #define DDRDATACH1_CR_RCOMPDATA0_SlewRateComp_WID                    ( 5)
  #define DDRDATACH1_CR_RCOMPDATA0_SlewRateComp_MSK                    (0x01F00000)
  #define DDRDATACH1_CR_RCOMPDATA0_SlewRateComp_MIN                    (0)
  #define DDRDATACH1_CR_RCOMPDATA0_SlewRateComp_MAX                    (31) // 0x0000001F
  #define DDRDATACH1_CR_RCOMPDATA0_SlewRateComp_DEF                    (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA0_SlewRateComp_HSH                    (0x05143140)

  #define DDRDATACH1_CR_RCOMPDATA0_Spare0_OFF                          (25)
  #define DDRDATACH1_CR_RCOMPDATA0_Spare0_WID                          ( 1)
  #define DDRDATACH1_CR_RCOMPDATA0_Spare0_MSK                          (0x02000000)
  #define DDRDATACH1_CR_RCOMPDATA0_Spare0_MIN                          (0)
  #define DDRDATACH1_CR_RCOMPDATA0_Spare0_MAX                          (1) // 0x00000001
  #define DDRDATACH1_CR_RCOMPDATA0_Spare0_DEF                          (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA0_Spare0_HSH                          (0x01193140)

  #define DDRDATACH1_CR_RCOMPDATA0_TcoComp_OFF                         (26)
  #define DDRDATACH1_CR_RCOMPDATA0_TcoComp_WID                         ( 6)
  #define DDRDATACH1_CR_RCOMPDATA0_TcoComp_MSK                         (0xFC000000)
  #define DDRDATACH1_CR_RCOMPDATA0_TcoComp_MIN                         (0)
  #define DDRDATACH1_CR_RCOMPDATA0_TcoComp_MAX                         (63) // 0x0000003F
  #define DDRDATACH1_CR_RCOMPDATA0_TcoComp_DEF                         (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA0_TcoComp_HSH                         (0x061A3140)

#define DDRDATACH1_CR_RCOMPDATA1_REG                                   (0x00003144)

  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtUp_OFF                      ( 0)
  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtUp_WID                      ( 6)
  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtUp_MSK                      (0x0000003F)
  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtUp_MIN                      (0)
  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtUp_MAX                      (63) // 0x0000003F
  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtUp_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtUp_HSH                      (0x06003144)

  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvDn_OFF                      ( 6)
  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvDn_WID                      (10)
  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvDn_MSK                      (0x0000FFC0)
  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvDn_MIN                      (0)
  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvDn_MAX                      (1023) // 0x000003FF
  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvDn_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvDn_HSH                      (0x0A063144)

  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvUp_OFF                      (16)
  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvUp_WID                      (10)
  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvUp_MSK                      (0x03FF0000)
  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvUp_MIN                      (0)
  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvUp_MAX                      (1023) // 0x000003FF
  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvUp_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA1_PanicDrvUp_HSH                      (0x0A103144)

  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtDown_OFF                    (26)
  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtDown_WID                    ( 6)
  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtDown_MSK                    (0xFC000000)
  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtDown_MIN                    (0)
  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtDown_MAX                    (63) // 0x0000003F
  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtDown_DEF                    (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA1_RcompOdtDown_HSH                    (0x061A3144)

#define DDRDATACH1_CR_TXXTALK_REG                                      (0x00003148)

  #define DDRDATACH1_CR_TXXTALK_Lane0_OFF                              ( 0)
  #define DDRDATACH1_CR_TXXTALK_Lane0_WID                              ( 4)
  #define DDRDATACH1_CR_TXXTALK_Lane0_MSK                              (0x0000000F)
  #define DDRDATACH1_CR_TXXTALK_Lane0_MIN                              (-8)
  #define DDRDATACH1_CR_TXXTALK_Lane0_MAX                              (7) // 0x00000007
  #define DDRDATACH1_CR_TXXTALK_Lane0_DEF                              (0x00000000)
  #define DDRDATACH1_CR_TXXTALK_Lane0_HSH                              (0x84003148)

  #define DDRDATACH1_CR_TXXTALK_Lane1_OFF                              ( 4)
  #define DDRDATACH1_CR_TXXTALK_Lane1_WID                              ( 4)
  #define DDRDATACH1_CR_TXXTALK_Lane1_MSK                              (0x000000F0)
  #define DDRDATACH1_CR_TXXTALK_Lane1_MIN                              (-8)
  #define DDRDATACH1_CR_TXXTALK_Lane1_MAX                              (7) // 0x00000007
  #define DDRDATACH1_CR_TXXTALK_Lane1_DEF                              (0x00000000)
  #define DDRDATACH1_CR_TXXTALK_Lane1_HSH                              (0x84043148)

  #define DDRDATACH1_CR_TXXTALK_Lane2_OFF                              ( 8)
  #define DDRDATACH1_CR_TXXTALK_Lane2_WID                              ( 4)
  #define DDRDATACH1_CR_TXXTALK_Lane2_MSK                              (0x00000F00)
  #define DDRDATACH1_CR_TXXTALK_Lane2_MIN                              (-8)
  #define DDRDATACH1_CR_TXXTALK_Lane2_MAX                              (7) // 0x00000007
  #define DDRDATACH1_CR_TXXTALK_Lane2_DEF                              (0x00000000)
  #define DDRDATACH1_CR_TXXTALK_Lane2_HSH                              (0x84083148)

  #define DDRDATACH1_CR_TXXTALK_Lane3_OFF                              (12)
  #define DDRDATACH1_CR_TXXTALK_Lane3_WID                              ( 4)
  #define DDRDATACH1_CR_TXXTALK_Lane3_MSK                              (0x0000F000)
  #define DDRDATACH1_CR_TXXTALK_Lane3_MIN                              (-8)
  #define DDRDATACH1_CR_TXXTALK_Lane3_MAX                              (7) // 0x00000007
  #define DDRDATACH1_CR_TXXTALK_Lane3_DEF                              (0x00000000)
  #define DDRDATACH1_CR_TXXTALK_Lane3_HSH                              (0x840C3148)

  #define DDRDATACH1_CR_TXXTALK_Lane4_OFF                              (16)
  #define DDRDATACH1_CR_TXXTALK_Lane4_WID                              ( 4)
  #define DDRDATACH1_CR_TXXTALK_Lane4_MSK                              (0x000F0000)
  #define DDRDATACH1_CR_TXXTALK_Lane4_MIN                              (-8)
  #define DDRDATACH1_CR_TXXTALK_Lane4_MAX                              (7) // 0x00000007
  #define DDRDATACH1_CR_TXXTALK_Lane4_DEF                              (0x00000000)
  #define DDRDATACH1_CR_TXXTALK_Lane4_HSH                              (0x84103148)

  #define DDRDATACH1_CR_TXXTALK_Lane5_OFF                              (20)
  #define DDRDATACH1_CR_TXXTALK_Lane5_WID                              ( 4)
  #define DDRDATACH1_CR_TXXTALK_Lane5_MSK                              (0x00F00000)
  #define DDRDATACH1_CR_TXXTALK_Lane5_MIN                              (-8)
  #define DDRDATACH1_CR_TXXTALK_Lane5_MAX                              (7) // 0x00000007
  #define DDRDATACH1_CR_TXXTALK_Lane5_DEF                              (0x00000000)
  #define DDRDATACH1_CR_TXXTALK_Lane5_HSH                              (0x84143148)

  #define DDRDATACH1_CR_TXXTALK_Lane6_OFF                              (24)
  #define DDRDATACH1_CR_TXXTALK_Lane6_WID                              ( 4)
  #define DDRDATACH1_CR_TXXTALK_Lane6_MSK                              (0x0F000000)
  #define DDRDATACH1_CR_TXXTALK_Lane6_MIN                              (-8)
  #define DDRDATACH1_CR_TXXTALK_Lane6_MAX                              (7) // 0x00000007
  #define DDRDATACH1_CR_TXXTALK_Lane6_DEF                              (0x00000000)
  #define DDRDATACH1_CR_TXXTALK_Lane6_HSH                              (0x84183148)

  #define DDRDATACH1_CR_TXXTALK_Lane7_OFF                              (28)
  #define DDRDATACH1_CR_TXXTALK_Lane7_WID                              ( 4)
  #define DDRDATACH1_CR_TXXTALK_Lane7_MSK                              (0xF0000000)
  #define DDRDATACH1_CR_TXXTALK_Lane7_MIN                              (-8)
  #define DDRDATACH1_CR_TXXTALK_Lane7_MAX                              (7) // 0x00000007
  #define DDRDATACH1_CR_TXXTALK_Lane7_DEF                              (0x00000000)
  #define DDRDATACH1_CR_TXXTALK_Lane7_HSH                              (0x841C3148)

#define DDRDATACH1_CR_RCOMPDATA2_REG                                   (0x0000314C)

  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicUp_OFF                      ( 0)
  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicUp_WID                      ( 8)
  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicUp_MSK                      (0x000000FF)
  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicUp_MIN                      (0)
  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicUp_MAX                      (255) // 0x000000FF
  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicUp_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicUp_HSH                      (0x0800314C)

  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicDn_OFF                      ( 8)
  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicDn_WID                      ( 8)
  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicDn_MSK                      (0x0000FF00)
  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicDn_MIN                      (0)
  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicDn_MAX                      (255) // 0x000000FF
  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicDn_DEF                      (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA2_VttPanicDn_HSH                      (0x0808314C)

  #define DDRDATACH1_CR_RCOMPDATA2_Spare_OFF                           (16)
  #define DDRDATACH1_CR_RCOMPDATA2_Spare_WID                           (16)
  #define DDRDATACH1_CR_RCOMPDATA2_Spare_MSK                           (0xFFFF0000)
  #define DDRDATACH1_CR_RCOMPDATA2_Spare_MIN                           (0)
  #define DDRDATACH1_CR_RCOMPDATA2_Spare_MAX                           (65535) // 0x0000FFFF
  #define DDRDATACH1_CR_RCOMPDATA2_Spare_DEF                           (0x00000000)
  #define DDRDATACH1_CR_RCOMPDATA2_Spare_HSH                           (0x1010314C)

#define DDRDATACH1_CR_RXOFFSETVDQRANK0_REG                             (0x00003150)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane0_OFF                     ( 0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane0_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane0_MSK                     (0x0000000F)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane0_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane0_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane0_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane0_HSH                     (0x04003150)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane1_OFF                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane1_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane1_MSK                     (0x000000F0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane1_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane1_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane1_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane1_HSH                     (0x04043150)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane2_OFF                     ( 8)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane2_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane2_MSK                     (0x00000F00)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane2_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane2_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane2_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane2_HSH                     (0x04083150)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane3_OFF                     (12)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane3_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane3_MSK                     (0x0000F000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane3_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane3_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane3_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane3_HSH                     (0x040C3150)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane4_OFF                     (16)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane4_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane4_MSK                     (0x000F0000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane4_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane4_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane4_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane4_HSH                     (0x04103150)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane5_OFF                     (20)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane5_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane5_MSK                     (0x00F00000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane5_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane5_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane5_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane5_HSH                     (0x04143150)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane6_OFF                     (24)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane6_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane6_MSK                     (0x0F000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane6_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane6_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane6_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane6_HSH                     (0x04183150)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane7_OFF                     (28)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane7_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane7_MSK                     (0xF0000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane7_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane7_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane7_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK0_Lane7_HSH                     (0x041C3150)

#define DDRDATACH1_CR_RXOFFSETVDQRANK1_REG                             (0x00003154)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane0_OFF                     ( 0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane0_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane0_MSK                     (0x0000000F)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane0_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane0_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane0_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane0_HSH                     (0x04003154)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane1_OFF                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane1_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane1_MSK                     (0x000000F0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane1_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane1_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane1_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane1_HSH                     (0x04043154)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane2_OFF                     ( 8)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane2_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane2_MSK                     (0x00000F00)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane2_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane2_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane2_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane2_HSH                     (0x04083154)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane3_OFF                     (12)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane3_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane3_MSK                     (0x0000F000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane3_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane3_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane3_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane3_HSH                     (0x040C3154)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane4_OFF                     (16)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane4_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane4_MSK                     (0x000F0000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane4_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane4_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane4_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane4_HSH                     (0x04103154)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane5_OFF                     (20)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane5_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane5_MSK                     (0x00F00000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane5_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane5_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane5_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane5_HSH                     (0x04143154)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane6_OFF                     (24)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane6_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane6_MSK                     (0x0F000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane6_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane6_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane6_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane6_HSH                     (0x04183154)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane7_OFF                     (28)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane7_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane7_MSK                     (0xF0000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane7_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane7_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane7_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK1_Lane7_HSH                     (0x041C3154)

#define DDRDATACH1_CR_RXOFFSETVDQRANK2_REG                             (0x00003158)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane0_OFF                     ( 0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane0_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane0_MSK                     (0x0000000F)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane0_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane0_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane0_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane0_HSH                     (0x04003158)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane1_OFF                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane1_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane1_MSK                     (0x000000F0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane1_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane1_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane1_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane1_HSH                     (0x04043158)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane2_OFF                     ( 8)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane2_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane2_MSK                     (0x00000F00)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane2_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane2_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane2_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane2_HSH                     (0x04083158)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane3_OFF                     (12)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane3_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane3_MSK                     (0x0000F000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane3_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane3_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane3_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane3_HSH                     (0x040C3158)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane4_OFF                     (16)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane4_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane4_MSK                     (0x000F0000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane4_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane4_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane4_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane4_HSH                     (0x04103158)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane5_OFF                     (20)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane5_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane5_MSK                     (0x00F00000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane5_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane5_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane5_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane5_HSH                     (0x04143158)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane6_OFF                     (24)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane6_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane6_MSK                     (0x0F000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane6_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane6_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane6_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane6_HSH                     (0x04183158)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane7_OFF                     (28)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane7_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane7_MSK                     (0xF0000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane7_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane7_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane7_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK2_Lane7_HSH                     (0x041C3158)

#define DDRDATACH1_CR_RXOFFSETVDQRANK3_REG                             (0x0000315C)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane0_OFF                     ( 0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane0_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane0_MSK                     (0x0000000F)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane0_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane0_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane0_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane0_HSH                     (0x0400315C)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane1_OFF                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane1_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane1_MSK                     (0x000000F0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane1_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane1_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane1_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane1_HSH                     (0x0404315C)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane2_OFF                     ( 8)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane2_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane2_MSK                     (0x00000F00)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane2_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane2_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane2_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane2_HSH                     (0x0408315C)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane3_OFF                     (12)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane3_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane3_MSK                     (0x0000F000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane3_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane3_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane3_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane3_HSH                     (0x040C315C)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane4_OFF                     (16)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane4_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane4_MSK                     (0x000F0000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane4_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane4_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane4_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane4_HSH                     (0x0410315C)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane5_OFF                     (20)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane5_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane5_MSK                     (0x00F00000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane5_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane5_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane5_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane5_HSH                     (0x0414315C)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane6_OFF                     (24)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane6_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane6_MSK                     (0x0F000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane6_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane6_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane6_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane6_HSH                     (0x0418315C)

  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane7_OFF                     (28)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane7_WID                     ( 4)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane7_MSK                     (0xF0000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane7_MIN                     (0)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane7_MAX                     (15) // 0x0000000F
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane7_DEF                     (0x00000000)
  #define DDRDATACH1_CR_RXOFFSETVDQRANK3_Lane7_HSH                     (0x041C315C)

#define DDRDATACH1_CR_DATATRAINFEEDBACK_REG                            (0x00003160)

  #define DDRDATACH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_OFF        ( 0)
  #define DDRDATACH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_WID        ( 9)
  #define DDRDATACH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_MSK        (0x000001FF)
  #define DDRDATACH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_MIN        (0)
  #define DDRDATACH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_MAX        (511) // 0x000001FF
  #define DDRDATACH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_DEF        (0x00000000)
  #define DDRDATACH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_HSH        (0x09003160)

  #define DDRDATACH1_CR_DATATRAINFEEDBACK_Spare_OFF                    ( 9)
  #define DDRDATACH1_CR_DATATRAINFEEDBACK_Spare_WID                    (23)
  #define DDRDATACH1_CR_DATATRAINFEEDBACK_Spare_MSK                    (0xFFFFFE00)
  #define DDRDATACH1_CR_DATATRAINFEEDBACK_Spare_MIN                    (0)
  #define DDRDATACH1_CR_DATATRAINFEEDBACK_Spare_MAX                    (8388607) // 0x007FFFFF
  #define DDRDATACH1_CR_DATATRAINFEEDBACK_Spare_DEF                    (0x00000000)
  #define DDRDATACH1_CR_DATATRAINFEEDBACK_Spare_HSH                    (0x17093160)

#define DDRDATACH1_CR_DLLPITESTANDADC_REG                              (0x00003164)

  #define DDRDATACH1_CR_DLLPITESTANDADC_RunTest_OFF                    ( 0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_RunTest_WID                    ( 1)
  #define DDRDATACH1_CR_DLLPITESTANDADC_RunTest_MSK                    (0x00000001)
  #define DDRDATACH1_CR_DLLPITESTANDADC_RunTest_MIN                    (0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_RunTest_MAX                    (1) // 0x00000001
  #define DDRDATACH1_CR_DLLPITESTANDADC_RunTest_DEF                    (0x00000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_RunTest_HSH                    (0x01003164)

  #define DDRDATACH1_CR_DLLPITESTANDADC_Load_OFF                       ( 1)
  #define DDRDATACH1_CR_DLLPITESTANDADC_Load_WID                       ( 1)
  #define DDRDATACH1_CR_DLLPITESTANDADC_Load_MSK                       (0x00000002)
  #define DDRDATACH1_CR_DLLPITESTANDADC_Load_MIN                       (0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_Load_MAX                       (1) // 0x00000001
  #define DDRDATACH1_CR_DLLPITESTANDADC_Load_DEF                       (0x00000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_Load_HSH                       (0x01013164)

  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeHVM_OFF                    ( 2)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeHVM_WID                    ( 1)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeHVM_MSK                    (0x00000004)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeHVM_MIN                    (0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeHVM_MAX                    (1) // 0x00000001
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeHVM_DEF                    (0x00000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeHVM_HSH                    (0x01023164)

  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeDV_OFF                     ( 3)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeDV_WID                     ( 1)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeDV_MSK                     (0x00000008)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeDV_MIN                     (0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeDV_MAX                     (1) // 0x00000001
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeDV_DEF                     (0x00000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeDV_HSH                     (0x01033164)

  #define DDRDATACH1_CR_DLLPITESTANDADC_CalCfdl_OFF                    ( 4)
  #define DDRDATACH1_CR_DLLPITESTANDADC_CalCfdl_WID                    ( 1)
  #define DDRDATACH1_CR_DLLPITESTANDADC_CalCfdl_MSK                    (0x00000010)
  #define DDRDATACH1_CR_DLLPITESTANDADC_CalCfdl_MIN                    (0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_CalCfdl_MAX                    (1) // 0x00000001
  #define DDRDATACH1_CR_DLLPITESTANDADC_CalCfdl_DEF                    (0x00000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_CalCfdl_HSH                    (0x01043164)

  #define DDRDATACH1_CR_DLLPITESTANDADC_LoadCount_OFF                  ( 5)
  #define DDRDATACH1_CR_DLLPITESTANDADC_LoadCount_WID                  (10)
  #define DDRDATACH1_CR_DLLPITESTANDADC_LoadCount_MSK                  (0x00007FE0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_LoadCount_MIN                  (0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_LoadCount_MAX                  (1023) // 0x000003FF
  #define DDRDATACH1_CR_DLLPITESTANDADC_LoadCount_DEF                  (0x00000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_LoadCount_HSH                  (0x0A053164)

  #define DDRDATACH1_CR_DLLPITESTANDADC_CountStatus_OFF                (15)
  #define DDRDATACH1_CR_DLLPITESTANDADC_CountStatus_WID                (10)
  #define DDRDATACH1_CR_DLLPITESTANDADC_CountStatus_MSK                (0x01FF8000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_CountStatus_MIN                (0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_CountStatus_MAX                (1023) // 0x000003FF
  #define DDRDATACH1_CR_DLLPITESTANDADC_CountStatus_DEF                (0x00000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_CountStatus_HSH                (0x0A0F3164)

  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeADC_OFF                    (25)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeADC_WID                    ( 1)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeADC_MSK                    (0x02000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeADC_MIN                    (0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeADC_MAX                    (1) // 0x00000001
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeADC_DEF                    (0x00000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ModeADC_HSH                    (0x01193164)

  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCClkDiv_OFF                  (26)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCClkDiv_WID                  ( 2)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCClkDiv_MSK                  (0x0C000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCClkDiv_MIN                  (0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCClkDiv_MAX                  (3) // 0x00000003
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCClkDiv_DEF                  (0x00000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCClkDiv_HSH                  (0x021A3164)

  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF              (28)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDdrChanSel_WID              ( 1)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK              (0x10000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN              (0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX              (1) // 0x00000001
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF              (0x00000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH              (0x011C3164)

  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCChopEn_OFF                  (29)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCChopEn_WID                  ( 1)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCChopEn_MSK                  (0x20000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCChopEn_MIN                  (0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCChopEn_MAX                  (1) // 0x00000001
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCChopEn_DEF                  (0x00000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCChopEn_HSH                  (0x011D3164)

  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDone_OFF                    (30)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDone_WID                    ( 1)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDone_MSK                    (0x40000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDone_MIN                    (0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDone_MAX                    (1) // 0x00000001
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDone_DEF                    (0x00000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_ADCDone_HSH                    (0x011E3164)

  #define DDRDATACH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF           (31)
  #define DDRDATACH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID           ( 1)
  #define DDRDATACH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK           (0x80000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN           (0)
  #define DDRDATACH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX           (1) // 0x00000001
  #define DDRDATACH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF           (0x00000000)
  #define DDRDATACH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH           (0x011F3164)

#define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_REG                          (0x00003168)

  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_OFF      ( 0)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_WID      ( 6)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MSK      (0x0000003F)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MIN      (-32)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MAX      (31) // 0x0000001F
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_DEF      (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_HSH      (0x86003168)

  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_OFF    ( 6)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_WID    ( 6)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MSK    (0x00000FC0)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MIN    (-32)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MAX    (31) // 0x0000001F
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_DEF    (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_HSH    (0x86063168)

  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_OFF      (12)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_WID      ( 5)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MSK      (0x0001F000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MIN      (-16)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MAX      (15) // 0x0000000F
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_DEF      (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_HSH      (0x850C3168)

  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_OFF    (17)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_WID    ( 5)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MSK    (0x003E0000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MIN    (-16)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MAX    (15) // 0x0000000F
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_DEF    (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_HSH    (0x85113168)

  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_OFF        (22)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_WID        ( 5)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MSK        (0x07C00000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MIN        (-16)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MAX        (15) // 0x0000000F
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_DEF        (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_HSH        (0x85163168)

  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_OFF   (27)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_WID   ( 5)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MSK   (0xF8000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MIN   (-16)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MAX   (15) // 0x0000000F
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_DEF   (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_HSH   (0x851B3168)

#define DDRDATACH1_CR_DDRCRDATACONTROL1_REG                            (0x0000316C)

  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RefPi_OFF                    ( 0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RefPi_WID                    ( 4)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RefPi_MSK                    (0x0000000F)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RefPi_MIN                    (-8)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RefPi_MAX                    (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RefPi_DEF                    (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RefPi_HSH                    (0x8400316C)

  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllMask_OFF                  ( 4)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllMask_WID                  ( 2)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllMask_MSK                  (0x00000030)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllMask_MIN                  (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllMask_MAX                  (3) // 0x00000003
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllMask_DEF                  (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllMask_HSH                  (0x0204316C)

  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllWeakLock_OFF              ( 6)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllWeakLock_WID              ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllWeakLock_MSK              (0x00000040)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllWeakLock_MIN              (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllWeakLock_MAX              (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllWeakLock_DEF              (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_DllWeakLock_HSH              (0x0106316C)

  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_OFF       ( 7)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_WID       ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MSK       (0x00000380)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MIN       (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MAX       (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_DEF       (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_HSH       (0x0307316C)

  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RxBiasCtl_OFF                (10)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RxBiasCtl_WID                ( 4)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RxBiasCtl_MSK                (0x00003C00)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RxBiasCtl_MIN                (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RxBiasCtl_MAX                (15) // 0x0000000F
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RxBiasCtl_DEF                (0x00000008)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_RxBiasCtl_HSH                (0x040A316C)

  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDelay_OFF                 (14)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDelay_WID                 ( 4)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDelay_MSK                 (0x0003C000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDelay_MIN                 (-8)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDelay_MAX                 (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDelay_DEF                 (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDelay_HSH                 (0x840E316C)

  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDuration_OFF              (18)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDuration_WID              ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDuration_MSK              (0x001C0000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDuration_MIN              (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDuration_MAX              (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDuration_DEF              (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_OdtDuration_HSH              (0x0312316C)

  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_OFF            (21)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_WID            ( 4)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_MSK            (0x01E00000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_MIN            (-8)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_MAX            (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_DEF            (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_HSH            (0x8415316C)

  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_OFF         (25)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_WID         ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_MSK         (0x0E000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_MIN         (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_MAX         (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_DEF         (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_HSH         (0x0319316C)

  #define DDRDATACH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_OFF           (28)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_WID           ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_MSK           (0x70000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_MIN           (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_MAX           (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_DEF           (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_HSH           (0x031C316C)

  #define DDRDATACH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_OFF           (31)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_WID           ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MSK           (0x80000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MIN           (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MAX           (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_DEF           (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_HSH           (0x011F316C)

#define DDRDATACH1_CR_DDRCRDATACONTROL2_REG                            (0x00003170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_OFF             ( 0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_WID             ( 5)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_MSK             (0x0000001F)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_MIN             (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_MAX             (31) // 0x0000001F
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_DEF             (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_HSH             (0x05003170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceBiasOn_OFF              ( 5)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceBiasOn_WID              ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceBiasOn_MSK              (0x00000020)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceBiasOn_MIN              (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceBiasOn_MAX              (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceBiasOn_DEF              (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceBiasOn_HSH              (0x01053170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceRxOn_OFF                ( 6)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceRxOn_WID                ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceRxOn_MSK                (0x00000040)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceRxOn_MIN                (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceRxOn_MAX                (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceRxOn_DEF                (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_ForceRxOn_HSH                (0x01063170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_LeakerComp_OFF               ( 7)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_LeakerComp_WID               ( 2)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_LeakerComp_MSK               (0x00000180)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_LeakerComp_MIN               (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_LeakerComp_MAX               (3) // 0x00000003
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_LeakerComp_DEF               (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_LeakerComp_HSH               (0x02073170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_OFF           ( 9)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_WID           ( 4)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MSK           (0x00001E00)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MIN           (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MAX           (15) // 0x0000000F
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_DEF           (0x00000008)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_HSH           (0x04093170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxClkStgNum_OFF              (13)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxClkStgNum_WID              ( 5)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxClkStgNum_MSK              (0x0003E000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxClkStgNum_MIN              (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxClkStgNum_MAX              (31) // 0x0000001F
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxClkStgNum_DEF              (0x00000011)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxClkStgNum_HSH              (0x050D3170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_WlLongDelEn_OFF              (18)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_WlLongDelEn_WID              ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_WlLongDelEn_MSK              (0x00040000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_WlLongDelEn_MIN              (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_WlLongDelEn_MAX              (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_WlLongDelEn_DEF              (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_WlLongDelEn_HSH              (0x01123170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_OFF          (19)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_WID          ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MSK          (0x00080000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MIN          (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MAX          (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_DEF          (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_HSH          (0x01133170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Ddr4Mode_OFF                 (20)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Ddr4Mode_WID                 ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Ddr4Mode_MSK                 (0x00100000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Ddr4Mode_MIN                 (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Ddr4Mode_MAX                 (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Ddr4Mode_DEF                 (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Ddr4Mode_HSH                 (0x01143170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVddqOdt_OFF                (21)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVddqOdt_WID                ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVddqOdt_MSK                (0x00200000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVddqOdt_MIN                (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVddqOdt_MAX                (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVddqOdt_DEF                (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVddqOdt_HSH                (0x01153170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVttOdt_OFF                 (22)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVttOdt_WID                 ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVttOdt_MSK                 (0x00400000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVttOdt_MIN                 (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVttOdt_MAX                 (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVttOdt_DEF                 (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnVttOdt_HSH                 (0x01163170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_OFF             (23)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_WID             ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_MSK             (0x00800000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_MIN             (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_MAX             (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_DEF             (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_HSH             (0x01173170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxEqDis_OFF                  (24)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxEqDis_WID                  ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxEqDis_MSK                  (0x01000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxEqDis_MIN                  (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxEqDis_MAX                  (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxEqDis_DEF                  (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxEqDis_HSH                  (0x01183170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_OFF            (25)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_WID            ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MSK            (0x02000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MIN            (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MAX            (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_DEF            (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_HSH            (0x01193170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Cben_OFF                     (26)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Cben_WID                     ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Cben_MSK                     (0x1C000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Cben_MIN                     (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Cben_MAX                     (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Cben_DEF                     (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_Cben_HSH                     (0x031A3170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_OFF          (29)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_WID          ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_MSK          (0x20000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_MIN          (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_MAX          (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_DEF          (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_HSH          (0x011D3170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_OFF          (30)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_WID          ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_MSK          (0x40000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_MIN          (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_MAX          (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_DEF          (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_HSH          (0x011E3170)

  #define DDRDATACH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_OFF          (31)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_WID          ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MSK          (0x80000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MIN          (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MAX          (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_DEF          (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_HSH          (0x011F3170)

#define DDRDATACH1_CR_DDRCRVREFCONTROL_REG                             (0x00003174)

  #define DDRDATACH1_CR_DDRCRVREFCONTROL_VrefCtl_OFF                   ( 0)
  #define DDRDATACH1_CR_DDRCRVREFCONTROL_VrefCtl_WID                   (24)
  #define DDRDATACH1_CR_DDRCRVREFCONTROL_VrefCtl_MSK                   (0x00FFFFFF)
  #define DDRDATACH1_CR_DDRCRVREFCONTROL_VrefCtl_MIN                   (0)
  #define DDRDATACH1_CR_DDRCRVREFCONTROL_VrefCtl_MAX                   (16777215) // 0x00FFFFFF
  #define DDRDATACH1_CR_DDRCRVREFCONTROL_VrefCtl_DEF                   (0x000E453A)
  #define DDRDATACH1_CR_DDRCRVREFCONTROL_VrefCtl_HSH                   (0x18003174)

  #define DDRDATACH1_CR_DDRCRVREFCONTROL_OutputCode_OFF                (24)
  #define DDRDATACH1_CR_DDRCRVREFCONTROL_OutputCode_WID                ( 8)
  #define DDRDATACH1_CR_DDRCRVREFCONTROL_OutputCode_MSK                (0xFF000000)
  #define DDRDATACH1_CR_DDRCRVREFCONTROL_OutputCode_MIN                (0)
  #define DDRDATACH1_CR_DDRCRVREFCONTROL_OutputCode_MAX                (255) // 0x000000FF
  #define DDRDATACH1_CR_DDRCRVREFCONTROL_OutputCode_DEF                (0x00000000)
  #define DDRDATACH1_CR_DDRCRVREFCONTROL_OutputCode_HSH                (0x08183174)

#define DDRDATACH1_CR_DDRCRVSSHICONTROL_REG                            (0x00003178)

  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_VssHiCtl_OFF                 ( 0)
  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_VssHiCtl_WID                 (25)
  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_VssHiCtl_MSK                 (0x01FFFFFF)
  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_VssHiCtl_MIN                 (0)
  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_VssHiCtl_MAX                 (33554431) // 0x01FFFFFF
  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_VssHiCtl_DEF                 (0x014D8234)
  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_VssHiCtl_HSH                 (0x19003178)

  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_OutputCode_OFF               (25)
  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_OutputCode_WID               ( 7)
  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_OutputCode_MSK               (0xFE000000)
  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_OutputCode_MIN               (0)
  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_OutputCode_MAX               (127) // 0x0000007F
  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_OutputCode_DEF               (0x00000000)
  #define DDRDATACH1_CR_DDRCRVSSHICONTROL_OutputCode_HSH               (0x07193178)

#define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_REG                         (0x0000317C)

  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_OFF           ( 0)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_WID           ( 6)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MSK           (0x0000003F)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MIN           (-32)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MAX           (31) // 0x0000001F
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_DEF           (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_HSH           (0x8600317C)

  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_OFF           ( 6)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_WID           ( 6)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MSK           (0x00000FC0)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MIN           (-32)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MAX           (31) // 0x0000001F
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_DEF           (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_HSH           (0x8606317C)

  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_OFF            (12)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_WID            ( 6)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MSK            (0x0003F000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MIN            (-32)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MAX            (31) // 0x0000001F
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_DEF            (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_HSH            (0x860C317C)

  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_OFF           (18)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_WID           ( 6)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MSK           (0x00FC0000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MIN           (-32)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MAX           (31) // 0x0000001F
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_DEF           (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_HSH           (0x8612317C)

  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_OFF            (24)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_WID            ( 7)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MSK            (0x7F000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MIN            (-64)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MAX            (63) // 0x0000003F
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_DEF            (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_HSH            (0x8718317C)

  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_Spare_OFF                 (31)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_Spare_WID                 ( 1)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_Spare_MSK                 (0x80000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_Spare_MIN                 (0)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_Spare_MAX                 (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_Spare_DEF                 (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_Spare_HSH                 (0x011F317C)

#define DDRDATACH1_CR_DDRCRDATACONTROL0_REG                            (0x00003180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxTrainingMode_OFF           ( 0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxTrainingMode_WID           ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxTrainingMode_MSK           (0x00000001)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxTrainingMode_MIN           (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxTrainingMode_MAX           (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxTrainingMode_DEF           (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxTrainingMode_HSH           (0x01003180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_WLTrainingMode_OFF           ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_WLTrainingMode_WID           ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_WLTrainingMode_MSK           (0x00000002)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_WLTrainingMode_MIN           (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_WLTrainingMode_MAX           (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_WLTrainingMode_DEF           (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_WLTrainingMode_HSH           (0x01013180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RLTrainingMode_OFF           ( 2)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RLTrainingMode_WID           ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RLTrainingMode_MSK           (0x00000004)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RLTrainingMode_MIN           (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RLTrainingMode_MAX           (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RLTrainingMode_DEF           (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RLTrainingMode_HSH           (0x01023180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_OFF     ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_WID     ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MSK     (0x00000008)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MIN     (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MAX     (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_DEF     (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_HSH     (0x01033180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxOn_OFF                     ( 4)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxOn_WID                     ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxOn_MSK                     (0x00000010)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxOn_MIN                     (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxOn_MAX                     (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxOn_DEF                     (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxOn_HSH                     (0x01043180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RfOn_OFF                     ( 5)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RfOn_WID                     ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RfOn_MSK                     (0x00000020)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RfOn_MIN                     (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RfOn_MAX                     (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RfOn_DEF                     (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RfOn_HSH                     (0x01053180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxPiOn_OFF                   ( 6)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxPiOn_WID                   ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxPiOn_MSK                   (0x00000040)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxPiOn_MIN                   (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxPiOn_MAX                   (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxPiOn_DEF                   (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxPiOn_HSH                   (0x01063180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxPiOn_OFF                   ( 7)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxPiOn_WID                   ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxPiOn_MSK                   (0x00000080)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxPiOn_MIN                   (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxPiOn_MAX                   (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxPiOn_DEF                   (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxPiOn_HSH                   (0x01073180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_InternalClocksOn_OFF         ( 8)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_InternalClocksOn_WID         ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_InternalClocksOn_MSK         (0x00000100)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_InternalClocksOn_MIN         (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_InternalClocksOn_MAX         (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_InternalClocksOn_DEF         (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_InternalClocksOn_HSH         (0x01083180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_OFF         ( 9)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_WID         ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MSK         (0x00000200)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MIN         (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MAX         (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_DEF         (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_HSH         (0x01093180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxDisable_OFF                (10)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxDisable_WID                ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxDisable_MSK                (0x00000400)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxDisable_MIN                (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxDisable_MAX                (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxDisable_DEF                (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxDisable_HSH                (0x010A3180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDisable_OFF                (11)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDisable_WID                ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDisable_MSK                (0x00000800)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDisable_MIN                (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDisable_MAX                (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDisable_DEF                (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDisable_HSH                (0x010B3180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxLong_OFF                   (12)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxLong_WID                   ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxLong_MSK                   (0x00001000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxLong_MIN                   (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxLong_MAX                   (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxLong_DEF                   (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_TxLong_HSH                   (0x010C3180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDqsCtle_OFF                (13)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDqsCtle_WID                ( 2)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDqsCtle_MSK                (0x00006000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDqsCtle_MIN                (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDqsCtle_MAX                (3) // 0x00000003
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDqsCtle_DEF                (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxDqsCtle_HSH                (0x020D3180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxReadPointer_OFF            (15)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxReadPointer_WID            ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxReadPointer_MSK            (0x00038000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxReadPointer_MIN            (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxReadPointer_MAX            (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxReadPointer_DEF            (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_RxReadPointer_HSH            (0x030F3180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LongOdtR2W_OFF               (18)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LongOdtR2W_WID               ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LongOdtR2W_MSK               (0x00040000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LongOdtR2W_MIN               (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LongOdtR2W_MAX               (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LongOdtR2W_DEF               (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LongOdtR2W_HSH               (0x01123180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DataVccddqHi_OFF             (19)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DataVccddqHi_WID             ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DataVccddqHi_MSK             (0x00080000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DataVccddqHi_MIN             (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DataVccddqHi_MAX             (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DataVccddqHi_DEF             (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DataVccddqHi_HSH             (0x01133180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRd_OFF                 (20)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRd_WID                 ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRd_MSK                 (0x00100000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRd_MIN                 (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRd_MAX                 (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRd_DEF                 (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRd_HSH                 (0x01143180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFWr_OFF                 (21)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFWr_WID                 ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFWr_MSK                 (0x00200000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFWr_MIN                 (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFWr_MAX                 (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFWr_DEF                 (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFWr_HSH                 (0x01153180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRank_OFF               (22)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRank_WID               ( 2)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRank_MSK               (0x00C00000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRank_MIN               (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRank_MAX               (3) // 0x00000003
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRank_DEF               (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ReadRFRank_HSH               (0x02163180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ForceOdtOn_OFF               (24)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ForceOdtOn_WID               ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ForceOdtOn_MSK               (0x01000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ForceOdtOn_MIN               (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ForceOdtOn_MAX               (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ForceOdtOn_DEF               (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_ForceOdtOn_HSH               (0x01183180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampOff_OFF               (25)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampOff_WID               ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampOff_MSK               (0x02000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampOff_MIN               (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampOff_MAX               (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampOff_DEF               (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampOff_HSH               (0x01193180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_OFF         (26)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_WID         ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_MSK         (0x04000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_MIN         (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_MAX         (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_DEF         (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_HSH         (0x011A3180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_OFF          (27)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_WID          ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MSK          (0x08000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MIN          (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MAX          (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_DEF          (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_HSH          (0x011B3180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_OFF               (28)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_WID               ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_MSK               (0x10000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_MIN               (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_MAX               (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_DEF               (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_HSH               (0x011C3180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EnReadPreamble_OFF           (29)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EnReadPreamble_WID           ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EnReadPreamble_MSK           (0x20000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EnReadPreamble_MIN           (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EnReadPreamble_MAX           (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EnReadPreamble_DEF           (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EnReadPreamble_HSH           (0x011D3180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_OFF          (30)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_WID          ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MSK          (0x40000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MIN          (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MAX          (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_DEF          (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_HSH          (0x011E3180)

  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_OFF             (31)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_WID             ( 1)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_MSK             (0x80000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_MIN             (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_MAX             (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_DEF             (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_HSH             (0x011F3180)

#define DDRDATACH1_CR_DDRCRVREFADJUST1_REG                             (0x00003184)

  #define DDRDATACH1_CR_DDRCRVREFADJUST1_CAVrefCtl_OFF                 ( 0)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_CAVrefCtl_WID                 ( 7)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_CAVrefCtl_MSK                 (0x0000007F)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_CAVrefCtl_MIN                 (-64)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_CAVrefCtl_MAX                 (63) // 0x0000003F
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_CAVrefCtl_DEF                 (0x00000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_CAVrefCtl_HSH                 (0x87003184)

  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_OFF                ( 7)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_WID                ( 7)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MSK                (0x00003F80)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MIN                (-64)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MAX                (63) // 0x0000003F
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_DEF                (0x00000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_HSH                (0x87073184)

  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_OFF                (14)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_WID                ( 7)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MSK                (0x001FC000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MIN                (-64)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MAX                (63) // 0x0000003F
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_DEF                (0x00000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_HSH                (0x870E3184)

  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_OFF              (21)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_WID              ( 1)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MSK              (0x00200000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MIN              (0)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MAX              (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_DEF              (0x00000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_HSH              (0x01153184)

  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_OFF             (22)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_WID             ( 1)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MSK             (0x00400000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MIN             (0)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MAX             (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_DEF             (0x00000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_HSH             (0x01163184)

  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_OFF             (23)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_WID             ( 1)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MSK             (0x00800000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MIN             (0)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MAX             (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_DEF             (0x00000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_HSH             (0x01173184)

  #define DDRDATACH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_OFF              (24)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_WID              ( 2)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MSK              (0x03000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MIN              (0)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MAX              (3) // 0x00000003
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_DEF              (0x00000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_HSH              (0x02183184)

  #define DDRDATACH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_OFF             (26)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_WID             ( 1)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MSK             (0x04000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MIN             (0)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MAX             (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_DEF             (0x00000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_HSH             (0x011A3184)

  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Rsvd_OFF                      (27)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Rsvd_WID                      ( 2)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Rsvd_MSK                      (0x18000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Rsvd_MIN                      (0)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Rsvd_MAX                      (3) // 0x00000003
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Rsvd_DEF                      (0x00000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_Rsvd_HSH                      (0x021B3184)

  #define DDRDATACH1_CR_DDRCRVREFADJUST1_caSlowBW_OFF                  (29)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_caSlowBW_WID                  ( 1)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_caSlowBW_MSK                  (0x20000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_caSlowBW_MIN                  (0)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_caSlowBW_MAX                  (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_caSlowBW_DEF                  (0x00000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_caSlowBW_HSH                  (0x011D3184)

  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch0SlowBW_OFF                 (30)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch0SlowBW_WID                 ( 1)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch0SlowBW_MSK                 (0x40000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch0SlowBW_MIN                 (0)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch0SlowBW_MAX                 (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch0SlowBW_DEF                 (0x00000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch0SlowBW_HSH                 (0x011E3184)

  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch1SlowBW_OFF                 (31)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch1SlowBW_WID                 ( 1)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch1SlowBW_MSK                 (0x80000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch1SlowBW_MIN                 (0)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch1SlowBW_MAX                 (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch1SlowBW_DEF                 (0x00000000)
  #define DDRDATACH1_CR_DDRCRVREFADJUST1_ch1SlowBW_HSH                 (0x011F3184)

#define DDRDATACH1_CR_DDRCRDATACONTROL3_REG                            (0x00003188)

  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_OFF         ( 0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_WID         ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_MSK         (0x00000007)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_MIN         (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_MAX         (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_DEF         (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_HSH         (0x03003188)

  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_OFF         ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_WID         ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_MSK         (0x00000038)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_MIN         (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_MAX         (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_DEF         (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_HSH         (0x03033188)

  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_OFF         ( 6)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_WID         ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_MSK         (0x000001C0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_MIN         (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_MAX         (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_DEF         (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_HSH         (0x03063188)

  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_OFF         ( 9)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_WID         ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_MSK         (0x00000E00)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_MIN         (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_MAX         (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_DEF         (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_HSH         (0x03093188)

  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_OFF         (12)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_WID         ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_MSK         (0x00007000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_MIN         (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_MAX         (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_DEF         (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_HSH         (0x030C3188)

  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_OFF         (15)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_WID         ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_MSK         (0x00038000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_MIN         (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_MAX         (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_DEF         (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_HSH         (0x030F3188)

  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_OFF         (18)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_WID         ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_MSK         (0x001C0000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_MIN         (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_MAX         (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_DEF         (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_HSH         (0x03123188)

  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_OFF         (21)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_WID         ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_MSK         (0x00E00000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_MIN         (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_MAX         (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_DEF         (0x00000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_HSH         (0x03153188)

  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp2_OFF                 (24)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp2_WID                 ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp2_MSK                 (0x07000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp2_MIN                 (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp2_MAX                 (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp2_DEF                 (0x00000003)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp2_HSH                 (0x03183188)

  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_OFF              (27)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_WID              ( 3)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MSK              (0x38000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MIN              (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MAX              (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_DEF              (0x00000003)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_HSH              (0x031B3188)

  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp1_OFF                 (30)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp1_WID                 ( 2)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp1_MSK                 (0xC0000000)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp1_MIN                 (0)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp1_MAX                 (3) // 0x00000003
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp1_DEF                 (0x00000001)
  #define DDRDATACH1_CR_DDRCRDATACONTROL3_CBEnAmp1_HSH                 (0x021E3188)

#define DDRDATACH1_CR_DDRCRVTTGENCONTROL_REG                           (0x0000318C)

  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Target_OFF                  ( 0)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Target_WID                  ( 4)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Target_MSK                  (0x0000000F)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Target_MIN                  (0)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Target_MAX                  (15) // 0x0000000F
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Target_DEF                  (0x00000000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Target_HSH                  (0x0400318C)

  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Panic_OFF                   ( 4)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Panic_WID                   ( 5)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Panic_MSK                   (0x000001F0)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Panic_MIN                   (0)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Panic_MAX                   (31) // 0x0000001F
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Panic_DEF                   (0x00000010)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Panic_HSH                   (0x0504318C)

  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_OFF             ( 9)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_WID             ( 2)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MSK             (0x00000600)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MIN             (0)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MAX             (3) // 0x00000003
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_DEF             (0x00000000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_HSH             (0x0209318C)

  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_OFF          (11)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_WID          ( 1)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MSK          (0x00000800)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MIN          (0)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MAX          (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_DEF          (0x00000000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_HSH          (0x010B318C)

  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_OFF              (12)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_WID              ( 1)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MSK              (0x00001000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MIN              (0)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MAX              (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_DEF              (0x00000000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_HSH              (0x010C318C)

  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_OFF             (13)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_WID             ( 3)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MSK             (0x0000E000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MIN             (0)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MAX             (7) // 0x00000007
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_DEF             (0x00000000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_HSH             (0x030D318C)

  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_OFF       (16)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_WID       ( 1)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MSK       (0x00010000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MIN       (0)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MAX       (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_DEF       (0x00000000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_HSH       (0x0110318C)

  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Spares_OFF                  (17)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Spares_WID                  ( 8)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Spares_MSK                  (0x01FE0000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Spares_MIN                  (0)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Spares_MAX                  (255) // 0x000000FF
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Spares_DEF                  (0x00000000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Spares_HSH                  (0x0811318C)

  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_OFF              (25)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_WID              ( 1)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MSK              (0x02000000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MIN              (0)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MAX              (1) // 0x00000001
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_DEF              (0x00000000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_HSH              (0x0119318C)

  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_OFF          (26)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_WID          ( 6)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MSK          (0xFC000000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MIN          (0)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MAX          (63) // 0x0000003F
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_DEF          (0x00000000)
  #define DDRDATACH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_HSH          (0x061A318C)

#define DDRCMDCH0_CR_DDRCRCMDCOMP_REG                                  (0x00003200)

  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Scomp_OFF                          ( 0)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Scomp_WID                          ( 6)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Scomp_MSK                          (0x0000003F)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Scomp_MIN                          (0)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Scomp_MAX                          (63) // 0x0000003F
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Scomp_HSH                          (0x06003200)

  #define DDRCMDCH0_CR_DDRCRCMDCOMP_TcoComp_OFF                        ( 6)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_TcoComp_WID                        ( 6)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_TcoComp_MSK                        (0x00000FC0)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_TcoComp_MIN                        (0)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_TcoComp_DEF                        (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_TcoComp_HSH                        (0x06063200)

  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvUp_OFF                     (12)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvUp_MSK                     (0x0003F000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvUp_HSH                     (0x060C3200)

  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvDown_OFF                   (18)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvDown_MSK                   (0x00FC0000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_RcompDrvDown_HSH                   (0x06123200)

  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Spare_OFF                          (24)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Spare_WID                          ( 8)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Spare_MSK                          (0xFF000000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Spare_MIN                          (0)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Spare_MAX                          (255) // 0x000000FF
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Spare_DEF                          (0x00000004)
  #define DDRCMDCH0_CR_DDRCRCMDCOMP_Spare_HSH                          (0x08183200)

#define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_REG                            (0x00003204)

  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_WID              ( 5)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MSK              (0x0000001F)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MIN              (-16)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MAX              (15) // 0x0000000F
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_HSH              (0x85003204)

  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_OFF            ( 5)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_WID            ( 4)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MSK            (0x000001E0)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MIN            (-8)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MAX            (7) // 0x00000007
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_DEF            (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_HSH            (0x84053204)

  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_OFF         ( 9)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MSK         (0x00001E00)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84093204)

  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_OFF       (13)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MSK       (0x0001E000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_HSH       (0x840D3204)

  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_Spare_OFF                    (17)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_Spare_WID                    (15)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_Spare_MSK                    (0xFFFE0000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_Spare_MAX                    (32767) // 0x00007FFF
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_Spare_HSH                    (0x0F113204)

#define DDRCMDCH0_CR_DDRCRCMDPICODING_REG                              (0x00003208)

  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_OFF                 ( 0)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_WID                 ( 7)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MSK                 (0x0000007F)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN                 (0)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX                 (127) // 0x0000007F
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_DEF                 (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_HSH                 (0x07003208)

  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi1Code_OFF                 ( 7)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi1Code_WID                 ( 7)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi1Code_MSK                 (0x00003F80)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi1Code_MIN                 (0)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi1Code_MAX                 (127) // 0x0000007F
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi1Code_DEF                 (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi1Code_HSH                 (0x07073208)

  #define DDRCMDCH0_CR_DDRCRCMDPICODING_Spare_OFF                      (14)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_Spare_WID                      (18)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_Spare_MSK                      (0xFFFFC000)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_Spare_MIN                      (0)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_Spare_MAX                      (262143) // 0x0003FFFF
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_Spare_DEF                      (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDPICODING_Spare_HSH                      (0x120E3208)

#define DDRCMDCH0_CR_DDRCRCMDCONTROLS_REG                              (0x0000320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RefPi_OFF                      ( 0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RefPi_WID                      ( 4)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RefPi_MSK                      (0x0000000F)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RefPi_MIN                      (-8)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RefPi_MAX                      (7) // 0x00000007
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RefPi_DEF                      (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RefPi_HSH                      (0x8400320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllMask_OFF                    ( 4)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllMask_WID                    ( 2)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllMask_MSK                    (0x00000030)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllMask_MIN                    (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllMask_MAX                    (3) // 0x00000003
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllMask_DEF                    (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllMask_HSH                    (0x0204320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_OFF             ( 6)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_WID             ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_MSK             (0x00000040)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_MIN             (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_MAX             (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_DEF             (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_HSH             (0x0106320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_TxOn_OFF                       ( 7)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_TxOn_WID                       ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_TxOn_MSK                       (0x00000080)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_TxOn_MIN                       (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_TxOn_MAX                       (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_TxOn_DEF                       (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_TxOn_HSH                       (0x0107320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IntClkOn_OFF                   ( 8)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IntClkOn_WID                   ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IntClkOn_MSK                   (0x00000100)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IntClkOn_MIN                   (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IntClkOn_MAX                   (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IntClkOn_DEF                   (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IntClkOn_HSH                   (0x0108320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RepClkOn_OFF                   ( 9)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RepClkOn_WID                   ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RepClkOn_MSK                   (0x00000200)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RepClkOn_MIN                   (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RepClkOn_MAX                   (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RepClkOn_DEF                   (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RepClkOn_HSH                   (0x0109320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_OFF                 (10)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_WID                 ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_MSK                 (0x00000400)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_MIN                 (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_MAX                 (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_DEF                 (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_HSH                 (0x010A320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbHold_OFF                   (11)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbHold_WID                   ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbHold_MSK                   (0x00000800)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbHold_MIN                   (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbHold_MAX                   (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbHold_DEF                   (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_IolbHold_HSH                   (0x010B320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_OdtMode_OFF                    (12)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_OdtMode_WID                    ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_OdtMode_MSK                    (0x00001000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_OdtMode_MIN                    (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_OdtMode_MAX                    (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_OdtMode_DEF                    (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_OdtMode_HSH                    (0x010C320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_OFF                    (13)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_WID                    ( 2)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_MSK                    (0x00006000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_MIN                    (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_MAX                    (3) // 0x00000003
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_DEF                    (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_HSH                    (0x020D320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_OFF             (15)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_WID             ( 2)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MSK             (0x00018000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MIN             (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MAX             (3) // 0x00000003
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_DEF             (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_HSH             (0x020F320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_PrtEn_OFF                      (17)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_PrtEn_WID                      ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_PrtEn_MSK                      (0x00020000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_PrtEn_MIN                      (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_PrtEn_MAX                      (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_PrtEn_DEF                      (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_PrtEn_HSH                      (0x0111320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_AlrtEn_OFF                     (18)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_AlrtEn_WID                     ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_AlrtEn_MSK                     (0x00040000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_AlrtEn_MIN                     (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_AlrtEn_MAX                     (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_AlrtEn_DEF                     (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_AlrtEn_HSH                     (0x0112320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_OFF                (19)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_WID                ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MSK                (0x00080000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MIN                (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MAX                (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_DEF                (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_HSH                (0x0113320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_OFF            (20)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_WID            ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MSK            (0x00100000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MIN            (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MAX            (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_DEF            (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_HSH            (0x0114320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RxVref_OFF                     (21)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RxVref_WID                     ( 6)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RxVref_MSK                     (0x07E00000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RxVref_MIN                     (-32)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RxVref_MAX                     (31) // 0x0000001F
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RxVref_DEF                     (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_RxVref_HSH                     (0x8615320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_VccddqHi_OFF                   (27)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_VccddqHi_WID                   ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_VccddqHi_MSK                   (0x08000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_VccddqHi_MIN                   (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_VccddqHi_MAX                   (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_VccddqHi_DEF                   (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_VccddqHi_HSH                   (0x011B320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_OFF                (28)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_WID                ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_MSK                (0x10000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_MIN                (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_MAX                (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_DEF                (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_HSH                (0x011C320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_OFF                 (29)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_WID                 ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MSK                 (0x20000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MIN                 (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MAX                 (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_DEF                 (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_HSH                 (0x011D320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_OFF               (30)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_WID               ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MSK               (0x40000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MIN               (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MAX               (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_DEF               (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_HSH               (0x011E320C)

  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_OFF               (31)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_WID               ( 1)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MSK               (0x80000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MIN               (0)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MAX               (1) // 0x00000001
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_DEF               (0x00000000)
  #define DDRCMDCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_HSH               (0x011F320C)

#define DDRCMDCH0_CR_DLLPITESTANDADC_REG                               (0x00003224)

  #define DDRCMDCH0_CR_DLLPITESTANDADC_RunTest_OFF                     ( 0)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_RunTest_WID                     ( 1)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_RunTest_MSK                     (0x00000001)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_RunTest_MIN                     (0)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_RunTest_MAX                     (1) // 0x00000001
  #define DDRCMDCH0_CR_DLLPITESTANDADC_RunTest_DEF                     (0x00000000)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_RunTest_HSH                     (0x01003224)

  #define DDRCMDCH0_CR_DLLPITESTANDADC_Load_OFF                        ( 1)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_Load_WID                        ( 1)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_Load_MSK                        (0x00000002)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_Load_MIN                        (0)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_Load_MAX                        (1) // 0x00000001
  #define DDRCMDCH0_CR_DLLPITESTANDADC_Load_DEF                        (0x00000000)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_Load_HSH                        (0x01013224)

  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeHVM_OFF                     ( 2)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeHVM_WID                     ( 1)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeHVM_MSK                     (0x00000004)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeHVM_MIN                     (0)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeHVM_MAX                     (1) // 0x00000001
  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeHVM_DEF                     (0x00000000)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeHVM_HSH                     (0x01023224)

  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeDV_OFF                      ( 3)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeDV_WID                      ( 1)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeDV_MSK                      (0x00000008)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeDV_MIN                      (0)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeDV_MAX                      (1) // 0x00000001
  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeDV_DEF                      (0x00000000)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_ModeDV_HSH                      (0x01033224)

  #define DDRCMDCH0_CR_DLLPITESTANDADC_CalCfdl_OFF                     ( 4)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_CalCfdl_WID                     ( 1)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_CalCfdl_MSK                     (0x00000010)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_CalCfdl_MIN                     (0)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_CalCfdl_MAX                     (1) // 0x00000001
  #define DDRCMDCH0_CR_DLLPITESTANDADC_CalCfdl_DEF                     (0x00000000)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_CalCfdl_HSH                     (0x01043224)

  #define DDRCMDCH0_CR_DLLPITESTANDADC_LoadCount_OFF                   ( 5)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_LoadCount_WID                   (10)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_LoadCount_MSK                   (0x00007FE0)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_LoadCount_MIN                   (0)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_LoadCount_MAX                   (1023) // 0x000003FF
  #define DDRCMDCH0_CR_DLLPITESTANDADC_LoadCount_DEF                   (0x00000000)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_LoadCount_HSH                   (0x0A053224)

  #define DDRCMDCH0_CR_DLLPITESTANDADC_CountStatus_OFF                 (15)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_CountStatus_WID                 (10)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_CountStatus_MSK                 (0x01FF8000)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_CountStatus_MIN                 (0)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_CountStatus_MAX                 (1023) // 0x000003FF
  #define DDRCMDCH0_CR_DLLPITESTANDADC_CountStatus_DEF                 (0x00000000)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_CountStatus_HSH                 (0x0A0F3224)

  #define DDRCMDCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF            (25)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID            ( 1)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK            (0x02000000)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN            (0)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX            (1) // 0x00000001
  #define DDRCMDCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF            (0x00000000)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH            (0x01193224)

  #define DDRCMDCH0_CR_DLLPITESTANDADC_Spare_OFF                       (26)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_Spare_WID                       ( 6)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_Spare_MSK                       (0xFC000000)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_Spare_MIN                       (0)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_Spare_MAX                       (63) // 0x0000003F
  #define DDRCMDCH0_CR_DLLPITESTANDADC_Spare_DEF                       (0x00000000)
  #define DDRCMDCH0_CR_DLLPITESTANDADC_Spare_HSH                       (0x061A3224)

#define DDRCMDCH1_CR_DDRCRCMDCOMP_REG                                  (0x00003300)

  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Scomp_OFF                          ( 0)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Scomp_WID                          ( 6)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Scomp_MSK                          (0x0000003F)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Scomp_MIN                          (0)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Scomp_MAX                          (63) // 0x0000003F
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Scomp_HSH                          (0x06003300)

  #define DDRCMDCH1_CR_DDRCRCMDCOMP_TcoComp_OFF                        ( 6)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_TcoComp_WID                        ( 6)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_TcoComp_MSK                        (0x00000FC0)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_TcoComp_MIN                        (0)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_TcoComp_DEF                        (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_TcoComp_HSH                        (0x06063300)

  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvUp_OFF                     (12)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvUp_MSK                     (0x0003F000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvUp_HSH                     (0x060C3300)

  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvDown_OFF                   (18)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvDown_MSK                   (0x00FC0000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_RcompDrvDown_HSH                   (0x06123300)

  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Spare_OFF                          (24)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Spare_WID                          ( 8)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Spare_MSK                          (0xFF000000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Spare_MIN                          (0)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Spare_MAX                          (255) // 0x000000FF
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Spare_DEF                          (0x00000004)
  #define DDRCMDCH1_CR_DDRCRCMDCOMP_Spare_HSH                          (0x08183300)

#define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_REG                            (0x00003304)

  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_WID              ( 5)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MSK              (0x0000001F)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MIN              (-16)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MAX              (15) // 0x0000000F
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_HSH              (0x85003304)

  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_OFF            ( 5)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_WID            ( 4)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MSK            (0x000001E0)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MIN            (-8)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MAX            (7) // 0x00000007
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_DEF            (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_HSH            (0x84053304)

  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_OFF         ( 9)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MSK         (0x00001E00)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84093304)

  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_OFF       (13)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MSK       (0x0001E000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_HSH       (0x840D3304)

  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_Spare_OFF                    (17)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_Spare_WID                    (15)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_Spare_MSK                    (0xFFFE0000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_Spare_MAX                    (32767) // 0x00007FFF
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCOMPOFFSET_Spare_HSH                    (0x0F113304)

#define DDRCMDCH1_CR_DDRCRCMDPICODING_REG                              (0x00003308)

  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi0Code_OFF                 ( 0)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi0Code_WID                 ( 7)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi0Code_MSK                 (0x0000007F)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi0Code_MIN                 (0)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi0Code_MAX                 (127) // 0x0000007F
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi0Code_DEF                 (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi0Code_HSH                 (0x07003308)

  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi1Code_OFF                 ( 7)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi1Code_WID                 ( 7)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi1Code_MSK                 (0x00003F80)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi1Code_MIN                 (0)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi1Code_MAX                 (127) // 0x0000007F
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi1Code_DEF                 (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_CmdPi1Code_HSH                 (0x07073308)

  #define DDRCMDCH1_CR_DDRCRCMDPICODING_Spare_OFF                      (14)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_Spare_WID                      (18)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_Spare_MSK                      (0xFFFFC000)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_Spare_MIN                      (0)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_Spare_MAX                      (262143) // 0x0003FFFF
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_Spare_DEF                      (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDPICODING_Spare_HSH                      (0x120E3308)

#define DDRCMDCH1_CR_DDRCRCMDCONTROLS_REG                              (0x0000330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RefPi_OFF                      ( 0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RefPi_WID                      ( 4)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RefPi_MSK                      (0x0000000F)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RefPi_MIN                      (-8)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RefPi_MAX                      (7) // 0x00000007
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RefPi_DEF                      (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RefPi_HSH                      (0x8400330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllMask_OFF                    ( 4)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllMask_WID                    ( 2)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllMask_MSK                    (0x00000030)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllMask_MIN                    (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllMask_MAX                    (3) // 0x00000003
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllMask_DEF                    (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllMask_HSH                    (0x0204330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_OFF             ( 6)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_WID             ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_MSK             (0x00000040)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_MIN             (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_MAX             (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_DEF             (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_HSH             (0x0106330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_TxOn_OFF                       ( 7)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_TxOn_WID                       ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_TxOn_MSK                       (0x00000080)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_TxOn_MIN                       (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_TxOn_MAX                       (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_TxOn_DEF                       (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_TxOn_HSH                       (0x0107330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IntClkOn_OFF                   ( 8)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IntClkOn_WID                   ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IntClkOn_MSK                   (0x00000100)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IntClkOn_MIN                   (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IntClkOn_MAX                   (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IntClkOn_DEF                   (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IntClkOn_HSH                   (0x0108330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RepClkOn_OFF                   ( 9)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RepClkOn_WID                   ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RepClkOn_MSK                   (0x00000200)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RepClkOn_MIN                   (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RepClkOn_MAX                   (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RepClkOn_DEF                   (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RepClkOn_HSH                   (0x0109330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_OFF                 (10)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_WID                 ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_MSK                 (0x00000400)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_MIN                 (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_MAX                 (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_DEF                 (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_HSH                 (0x010A330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbHold_OFF                   (11)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbHold_WID                   ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbHold_MSK                   (0x00000800)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbHold_MIN                   (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbHold_MAX                   (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbHold_DEF                   (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_IolbHold_HSH                   (0x010B330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_OdtMode_OFF                    (12)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_OdtMode_WID                    ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_OdtMode_MSK                    (0x00001000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_OdtMode_MIN                    (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_OdtMode_MAX                    (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_OdtMode_DEF                    (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_OdtMode_HSH                    (0x010C330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_OFF                    (13)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_WID                    ( 2)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_MSK                    (0x00006000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_MIN                    (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_MAX                    (3) // 0x00000003
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_DEF                    (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_HSH                    (0x020D330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_OFF             (15)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_WID             ( 2)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MSK             (0x00018000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MIN             (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MAX             (3) // 0x00000003
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_DEF             (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_HSH             (0x020F330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_PrtEn_OFF                      (17)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_PrtEn_WID                      ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_PrtEn_MSK                      (0x00020000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_PrtEn_MIN                      (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_PrtEn_MAX                      (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_PrtEn_DEF                      (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_PrtEn_HSH                      (0x0111330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_AlrtEn_OFF                     (18)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_AlrtEn_WID                     ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_AlrtEn_MSK                     (0x00040000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_AlrtEn_MIN                     (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_AlrtEn_MAX                     (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_AlrtEn_DEF                     (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_AlrtEn_HSH                     (0x0112330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_OFF                (19)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_WID                ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MSK                (0x00080000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MIN                (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MAX                (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_DEF                (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_HSH                (0x0113330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_OFF            (20)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_WID            ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MSK            (0x00100000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MIN            (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MAX            (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_DEF            (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_HSH            (0x0114330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RxVref_OFF                     (21)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RxVref_WID                     ( 6)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RxVref_MSK                     (0x07E00000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RxVref_MIN                     (-32)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RxVref_MAX                     (31) // 0x0000001F
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RxVref_DEF                     (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_RxVref_HSH                     (0x8615330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_VccddqHi_OFF                   (27)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_VccddqHi_WID                   ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_VccddqHi_MSK                   (0x08000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_VccddqHi_MIN                   (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_VccddqHi_MAX                   (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_VccddqHi_DEF                   (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_VccddqHi_HSH                   (0x011B330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_OFF                (28)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_WID                ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_MSK                (0x10000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_MIN                (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_MAX                (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_DEF                (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_HSH                (0x011C330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_OFF                 (29)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_WID                 ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MSK                 (0x20000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MIN                 (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MAX                 (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_DEF                 (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_HSH                 (0x011D330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_OFF               (30)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_WID               ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MSK               (0x40000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MIN               (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MAX               (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_DEF               (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_HSH               (0x011E330C)

  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_OFF               (31)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_WID               ( 1)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MSK               (0x80000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MIN               (0)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MAX               (1) // 0x00000001
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_DEF               (0x00000000)
  #define DDRCMDCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_HSH               (0x011F330C)

#define DDRCMDCH1_CR_DLLPITESTANDADC_REG                               (0x00003324)

  #define DDRCMDCH1_CR_DLLPITESTANDADC_RunTest_OFF                     ( 0)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_RunTest_WID                     ( 1)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_RunTest_MSK                     (0x00000001)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_RunTest_MIN                     (0)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_RunTest_MAX                     (1) // 0x00000001
  #define DDRCMDCH1_CR_DLLPITESTANDADC_RunTest_DEF                     (0x00000000)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_RunTest_HSH                     (0x01003324)

  #define DDRCMDCH1_CR_DLLPITESTANDADC_Load_OFF                        ( 1)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_Load_WID                        ( 1)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_Load_MSK                        (0x00000002)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_Load_MIN                        (0)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_Load_MAX                        (1) // 0x00000001
  #define DDRCMDCH1_CR_DLLPITESTANDADC_Load_DEF                        (0x00000000)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_Load_HSH                        (0x01013324)

  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeHVM_OFF                     ( 2)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeHVM_WID                     ( 1)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeHVM_MSK                     (0x00000004)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeHVM_MIN                     (0)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeHVM_MAX                     (1) // 0x00000001
  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeHVM_DEF                     (0x00000000)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeHVM_HSH                     (0x01023324)

  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeDV_OFF                      ( 3)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeDV_WID                      ( 1)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeDV_MSK                      (0x00000008)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeDV_MIN                      (0)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeDV_MAX                      (1) // 0x00000001
  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeDV_DEF                      (0x00000000)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_ModeDV_HSH                      (0x01033324)

  #define DDRCMDCH1_CR_DLLPITESTANDADC_CalCfdl_OFF                     ( 4)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_CalCfdl_WID                     ( 1)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_CalCfdl_MSK                     (0x00000010)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_CalCfdl_MIN                     (0)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_CalCfdl_MAX                     (1) // 0x00000001
  #define DDRCMDCH1_CR_DLLPITESTANDADC_CalCfdl_DEF                     (0x00000000)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_CalCfdl_HSH                     (0x01043324)

  #define DDRCMDCH1_CR_DLLPITESTANDADC_LoadCount_OFF                   ( 5)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_LoadCount_WID                   (10)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_LoadCount_MSK                   (0x00007FE0)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_LoadCount_MIN                   (0)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_LoadCount_MAX                   (1023) // 0x000003FF
  #define DDRCMDCH1_CR_DLLPITESTANDADC_LoadCount_DEF                   (0x00000000)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_LoadCount_HSH                   (0x0A053324)

  #define DDRCMDCH1_CR_DLLPITESTANDADC_CountStatus_OFF                 (15)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_CountStatus_WID                 (10)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_CountStatus_MSK                 (0x01FF8000)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_CountStatus_MIN                 (0)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_CountStatus_MAX                 (1023) // 0x000003FF
  #define DDRCMDCH1_CR_DLLPITESTANDADC_CountStatus_DEF                 (0x00000000)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_CountStatus_HSH                 (0x0A0F3324)

  #define DDRCMDCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF            (25)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID            ( 1)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK            (0x02000000)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN            (0)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX            (1) // 0x00000001
  #define DDRCMDCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF            (0x00000000)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH            (0x01193324)

  #define DDRCMDCH1_CR_DLLPITESTANDADC_Spare_OFF                       (26)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_Spare_WID                       ( 6)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_Spare_MSK                       (0xFC000000)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_Spare_MIN                       (0)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_Spare_MAX                       (63) // 0x0000003F
  #define DDRCMDCH1_CR_DLLPITESTANDADC_Spare_DEF                       (0x00000000)
  #define DDRCMDCH1_CR_DLLPITESTANDADC_Spare_HSH                       (0x061A3324)

#define DDRCKECTLCH0_CR_DDRCRCTLCOMP_REG                               (0x00003410)

  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Scomp_OFF                       ( 0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Scomp_WID                       ( 6)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Scomp_MSK                       (0x0000003F)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Scomp_MIN                       (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Scomp_MAX                       (63) // 0x0000003F
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Scomp_DEF                       (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Scomp_HSH                       (0x06003410)

  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_TcoComp_OFF                     ( 6)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_TcoComp_WID                     ( 6)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_TcoComp_MSK                     (0x00000FC0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_TcoComp_MIN                     (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_TcoComp_MAX                     (63) // 0x0000003F
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_TcoComp_DEF                     (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_TcoComp_HSH                     (0x06063410)

  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_OFF                  (12)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_WID                  ( 6)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_MSK                  (0x0003F000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_MIN                  (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_MAX                  (63) // 0x0000003F
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_DEF                  (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_HSH                  (0x060C3410)

  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_OFF                (18)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_WID                ( 6)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_MSK                (0x00FC0000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_MIN                (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_MAX                (63) // 0x0000003F
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_DEF                (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_HSH                (0x06123410)

  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Spare_OFF                       (24)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Spare_WID                       ( 8)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Spare_MSK                       (0xFF000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Spare_MIN                       (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Spare_MAX                       (255) // 0x000000FF
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Spare_DEF                       (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMP_Spare_HSH                       (0x08183410)

#define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_REG                         (0x00003414)

  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_OFF           ( 0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_WID           ( 5)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MSK           (0x0000001F)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MIN           (-16)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MAX           (15) // 0x0000000F
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_DEF           (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_HSH           (0x85003414)

  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_OFF         ( 5)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_WID         ( 4)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MSK         (0x000001E0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MIN         (-8)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MAX         (7) // 0x00000007
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_DEF         (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_HSH         (0x84053414)

  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_OFF      ( 9)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_WID      ( 4)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MSK      (0x00001E00)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MIN      (-8)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MAX      (7) // 0x00000007
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_DEF      (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_HSH      (0x84093414)

  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_OFF    (13)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_WID    ( 4)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MSK    (0x0001E000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MIN    (-8)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MAX    (7) // 0x00000007
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_DEF    (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_HSH    (0x840D3414)

  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_OFF                 (17)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_WID                 (15)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_MSK                 (0xFFFE0000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_MIN                 (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_MAX                 (32767) // 0x00007FFF
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_DEF                 (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_HSH                 (0x0F113414)

#define DDRCKECTLCH0_CR_DDRCRCTLPICODING_REG                           (0x00003418)

  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_OFF              ( 0)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_WID              ( 7)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MSK              (0x0000007F)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MIN              (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MAX              (127) // 0x0000007F
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_DEF              (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_HSH              (0x07003418)

  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_OFF              ( 7)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_WID              ( 7)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_MSK              (0x00003F80)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_MIN              (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_MAX              (127) // 0x0000007F
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_DEF              (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_HSH              (0x07073418)

  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_OFF              (14)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_WID              ( 7)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_MSK              (0x001FC000)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_MIN              (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_MAX              (127) // 0x0000007F
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_DEF              (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_HSH              (0x070E3418)

  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_OFF              (21)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_WID              ( 7)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_MSK              (0x0FE00000)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_MIN              (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_MAX              (127) // 0x0000007F
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_DEF              (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_HSH              (0x07153418)

  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_OFF          (28)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_WID          ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_MSK          (0x10000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_MIN          (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_MAX          (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_DEF          (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_HSH          (0x011C3418)

  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_Spare_OFF                   (29)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_Spare_WID                   ( 3)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_Spare_MSK                   (0xE0000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_Spare_MIN                   (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_Spare_MAX                   (7) // 0x00000007
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_Spare_DEF                   (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLPICODING_Spare_HSH                   (0x031D3418)

#define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_REG                           (0x0000341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RefPi_OFF                   ( 0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RefPi_WID                   ( 4)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RefPi_MSK                   (0x0000000F)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RefPi_MIN                   (-8)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RefPi_MAX                   (7) // 0x00000007
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RefPi_DEF                   (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RefPi_HSH                   (0x8400341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllMask_OFF                 ( 4)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllMask_WID                 ( 2)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllMask_MSK                 (0x00000030)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllMask_MIN                 (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllMask_MAX                 (3) // 0x00000003
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllMask_DEF                 (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllMask_HSH                 (0x0204341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_OFF          ( 6)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_WID          ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_MSK          (0x00000040)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_MIN          (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_MAX          (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_DEF          (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_HSH          (0x0106341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_TxOn_OFF                    ( 7)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_TxOn_WID                    ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_TxOn_MSK                    (0x00000080)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_TxOn_MIN                    (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_TxOn_MAX                    (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_TxOn_DEF                    (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_TxOn_HSH                    (0x0107341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_OFF                ( 8)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_WID                ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_MSK                (0x00000100)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_MIN                (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_MAX                (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_DEF                (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_HSH                (0x0108341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_OFF                ( 9)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_WID                ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_MSK                (0x00000200)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_MIN                (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_MAX                (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_DEF                (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_HSH                (0x0109341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_OFF              (10)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_WID              ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_MSK              (0x00000400)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_MIN              (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_MAX              (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_DEF              (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_HSH              (0x010A341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_OFF                (11)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_WID                ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_MSK                (0x00000800)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_MIN                (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_MAX                (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_DEF                (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_HSH                (0x010B341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_OFF                 (12)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_WID                 ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_MSK                 (0x00001000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_MIN                 (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_MAX                 (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_DEF                 (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_HSH                 (0x010C341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_OFF                 (13)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_WID                 ( 2)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_MSK                 (0x00006000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_MIN                 (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_MAX                 (3) // 0x00000003
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_DEF                 (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_HSH                 (0x020D341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_OFF          (15)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_WID          ( 2)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MSK          (0x00018000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MIN          (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MAX          (3) // 0x00000003
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_DEF          (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_HSH          (0x020F341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_OFF                 (17)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_WID                 ( 2)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_MSK                 (0x00060000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_MIN                 (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_MAX                 (3) // 0x00000003
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_DEF                 (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_HSH                 (0x0211341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_OFF                (19)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_WID                ( 2)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_MSK                (0x00180000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_MIN                (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_MAX                (3) // 0x00000003
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_DEF                (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_HSH                (0x0213341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RxVref_OFF                  (21)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RxVref_WID                  ( 6)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RxVref_MSK                  (0x07E00000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RxVref_MIN                  (-32)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RxVref_MAX                  (31) // 0x0000001F
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RxVref_DEF                  (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_RxVref_HSH                  (0x8615341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_OFF                (27)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_WID                ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_MSK                (0x08000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_MIN                (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_MAX                (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_DEF                (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_HSH                (0x011B341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_OFF             (28)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_WID             ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_MSK             (0x10000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_MIN             (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_MAX             (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_DEF             (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_HSH             (0x011C341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_OFF              (29)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_WID              ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MSK              (0x20000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MIN              (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MAX              (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_DEF              (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_HSH              (0x011D341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_OFF             (30)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_WID             ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MSK             (0x40000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MIN             (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MAX             (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_DEF             (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_HSH             (0x011E341C)

  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_OFF            (31)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_WID            ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MSK            (0x80000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MIN            (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MAX            (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_DEF            (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_HSH            (0x011F341C)

#define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_REG                          (0x00003420)

  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_OFF                 ( 0)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_WID                 ( 4)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_MSK                 (0x0000000F)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_MIN                 (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_MAX                 (15) // 0x0000000F
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_DEF                 (0x0000000F)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_HSH                 (0x04003420)

  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_OFF             ( 4)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_WID             ( 2)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_MSK             (0x00000030)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_MIN             (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_MAX             (3) // 0x00000003
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_DEF             (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_HSH             (0x02043420)

  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_OFF     ( 6)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_WID     ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MSK     (0x00000040)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MIN     (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MAX     (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_DEF     (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_HSH     (0x01063420)

  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_OFF     ( 7)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_WID     ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MSK     (0x00000080)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MIN     (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MAX     (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_DEF     (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_HSH     (0x01073420)

  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_OFF          ( 8)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_WID          ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MSK          (0x00000100)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MIN          (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MAX          (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_DEF          (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_HSH          (0x01083420)

  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_OFF           ( 9)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_WID           ( 1)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MSK           (0x00000200)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MIN           (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MAX           (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_DEF           (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_HSH           (0x01093420)

  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_Spare_OFF                  (10)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_Spare_WID                  (22)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_Spare_MSK                  (0xFFFFFC00)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_Spare_MIN                  (0)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_Spare_MAX                  (4194303) // 0x003FFFFF
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_Spare_DEF                  (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCRCTLRANKSUSED_Spare_HSH                  (0x160A3420)

#define DDRCKECTLCH0_CR_DLLPITESTANDADC_REG                            (0x00003424)

  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_RunTest_OFF                  ( 0)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_RunTest_WID                  ( 1)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_RunTest_MSK                  (0x00000001)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_RunTest_MIN                  (0)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_RunTest_MAX                  (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_RunTest_DEF                  (0x00000000)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_RunTest_HSH                  (0x01003424)

  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Load_OFF                     ( 1)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Load_WID                     ( 1)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Load_MSK                     (0x00000002)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Load_MIN                     (0)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Load_MAX                     (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Load_DEF                     (0x00000000)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Load_HSH                     (0x01013424)

  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeHVM_OFF                  ( 2)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeHVM_WID                  ( 1)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeHVM_MSK                  (0x00000004)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeHVM_MIN                  (0)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeHVM_MAX                  (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeHVM_DEF                  (0x00000000)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeHVM_HSH                  (0x01023424)

  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeDV_OFF                   ( 3)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeDV_WID                   ( 1)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeDV_MSK                   (0x00000008)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeDV_MIN                   (0)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeDV_MAX                   (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeDV_DEF                   (0x00000000)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_ModeDV_HSH                   (0x01033424)

  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CalCfdl_OFF                  ( 4)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CalCfdl_WID                  ( 1)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CalCfdl_MSK                  (0x00000010)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CalCfdl_MIN                  (0)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CalCfdl_MAX                  (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CalCfdl_DEF                  (0x00000000)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CalCfdl_HSH                  (0x01043424)

  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_LoadCount_OFF                ( 5)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_LoadCount_WID                (10)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_LoadCount_MSK                (0x00007FE0)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_LoadCount_MIN                (0)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_LoadCount_MAX                (1023) // 0x000003FF
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_LoadCount_DEF                (0x00000000)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_LoadCount_HSH                (0x0A053424)

  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CountStatus_OFF              (15)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CountStatus_WID              (10)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CountStatus_MSK              (0x01FF8000)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CountStatus_MIN              (0)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CountStatus_MAX              (1023) // 0x000003FF
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CountStatus_DEF              (0x00000000)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_CountStatus_HSH              (0x0A0F3424)

  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF         (25)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID         ( 1)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK         (0x02000000)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN         (0)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX         (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF         (0x00000000)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH         (0x01193424)

  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Spare_OFF                    (26)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Spare_WID                    ( 6)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Spare_MSK                    (0xFC000000)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Spare_MIN                    (0)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Spare_MAX                    (63) // 0x0000003F
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Spare_DEF                    (0x00000000)
  #define DDRCKECTLCH0_CR_DLLPITESTANDADC_Spare_HSH                    (0x061A3424)

#define DDRCKECTLCH0_CR_DDRCMDMISR_REG                                 (0x00003428)

  #define DDRCKECTLCH0_CR_DDRCMDMISR_shift_16_OFF                      ( 0)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_shift_16_WID                      ( 1)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_shift_16_MSK                      (0x00000001)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_shift_16_MIN                      (0)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_shift_16_MAX                      (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCMDMISR_shift_16_DEF                      (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_shift_16_HSH                      (0x01003428)

  #define DDRCKECTLCH0_CR_DDRCMDMISR_clken_pulse_mode_OFF              ( 1)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_clken_pulse_mode_WID              ( 1)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_clken_pulse_mode_MSK              (0x00000002)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_clken_pulse_mode_MIN              (0)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_clken_pulse_mode_MAX              (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCMDMISR_clken_pulse_mode_DEF              (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_clken_pulse_mode_HSH              (0x01013428)

  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_mode_OFF                ( 2)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_mode_WID                ( 1)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_mode_MSK                (0x00000004)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_mode_MIN                (0)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_mode_MAX                (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_mode_DEF                (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_mode_HSH                (0x01023428)

  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_OFF                     ( 3)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_WID                     ( 1)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_MSK                     (0x00000008)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_MIN                     (0)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_MAX                     (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_DEF                     (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_reg_clken_HSH                     (0x01033428)

  #define DDRCKECTLCH0_CR_DDRCMDMISR_feedback_en_OFF                   ( 4)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_feedback_en_WID                   ( 1)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_feedback_en_MSK                   (0x00000010)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_feedback_en_MIN                   (0)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_feedback_en_MAX                   (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCMDMISR_feedback_en_DEF                   (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_feedback_en_HSH                   (0x01043428)

  #define DDRCKECTLCH0_CR_DDRCMDMISR_event_mode_OFF                    ( 5)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_event_mode_WID                    ( 1)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_event_mode_MSK                    (0x00000020)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_event_mode_MIN                    (0)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_event_mode_MAX                    (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCMDMISR_event_mode_DEF                    (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_event_mode_HSH                    (0x01053428)

  #define DDRCKECTLCH0_CR_DDRCMDMISR_lfsr_reset_OFF                    ( 6)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_lfsr_reset_WID                    ( 1)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_lfsr_reset_MSK                    (0x00000040)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_lfsr_reset_MIN                    (0)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_lfsr_reset_MAX                    (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCMDMISR_lfsr_reset_DEF                    (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_lfsr_reset_HSH                    (0x01063428)

  #define DDRCKECTLCH0_CR_DDRCMDMISR_sdo_en_OFF                        ( 7)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_sdo_en_WID                        ( 1)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_sdo_en_MSK                        (0x00000080)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_sdo_en_MIN                        (0)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_sdo_en_MAX                        (1) // 0x00000001
  #define DDRCKECTLCH0_CR_DDRCMDMISR_sdo_en_DEF                        (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_sdo_en_HSH                        (0x01073428)

  #define DDRCKECTLCH0_CR_DDRCMDMISR_cr_rd_data_OFF                    (16)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_cr_rd_data_WID                    (16)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_cr_rd_data_MSK                    (0xFFFF0000)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_cr_rd_data_MIN                    (0)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_cr_rd_data_MAX                    (65535) // 0x0000FFFF
  #define DDRCKECTLCH0_CR_DDRCMDMISR_cr_rd_data_DEF                    (0x00000000)
  #define DDRCKECTLCH0_CR_DDRCMDMISR_cr_rd_data_HSH                    (0x10103428)

#define DDRCKECTLCH1_CR_DDRCRCTLCOMP_REG                               (0x00003510)

  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Scomp_OFF                       ( 0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Scomp_WID                       ( 6)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Scomp_MSK                       (0x0000003F)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Scomp_MIN                       (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Scomp_MAX                       (63) // 0x0000003F
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Scomp_DEF                       (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Scomp_HSH                       (0x06003510)

  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_TcoComp_OFF                     ( 6)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_TcoComp_WID                     ( 6)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_TcoComp_MSK                     (0x00000FC0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_TcoComp_MIN                     (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_TcoComp_MAX                     (63) // 0x0000003F
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_TcoComp_DEF                     (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_TcoComp_HSH                     (0x06063510)

  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_OFF                  (12)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_WID                  ( 6)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_MSK                  (0x0003F000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_MIN                  (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_MAX                  (63) // 0x0000003F
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_DEF                  (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_HSH                  (0x060C3510)

  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_OFF                (18)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_WID                ( 6)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_MSK                (0x00FC0000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_MIN                (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_MAX                (63) // 0x0000003F
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_DEF                (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_HSH                (0x06123510)

  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Spare_OFF                       (24)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Spare_WID                       ( 8)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Spare_MSK                       (0xFF000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Spare_MIN                       (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Spare_MAX                       (255) // 0x000000FF
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Spare_DEF                       (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMP_Spare_HSH                       (0x08183510)

#define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_REG                         (0x00003514)

  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_OFF           ( 0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_WID           ( 5)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MSK           (0x0000001F)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MIN           (-16)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MAX           (15) // 0x0000000F
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_DEF           (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_HSH           (0x85003514)

  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_OFF         ( 5)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_WID         ( 4)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MSK         (0x000001E0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MIN         (-8)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MAX         (7) // 0x00000007
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_DEF         (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_HSH         (0x84053514)

  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_OFF      ( 9)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_WID      ( 4)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MSK      (0x00001E00)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MIN      (-8)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MAX      (7) // 0x00000007
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_DEF      (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_HSH      (0x84093514)

  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_OFF    (13)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_WID    ( 4)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MSK    (0x0001E000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MIN    (-8)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MAX    (7) // 0x00000007
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_DEF    (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_HSH    (0x840D3514)

  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_OFF                 (17)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_WID                 (15)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_MSK                 (0xFFFE0000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_MIN                 (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_MAX                 (32767) // 0x00007FFF
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_DEF                 (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_HSH                 (0x0F113514)

#define DDRCKECTLCH1_CR_DDRCRCTLPICODING_REG                           (0x00003518)

  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_OFF              ( 0)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_WID              ( 7)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_MSK              (0x0000007F)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_MIN              (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_MAX              (127) // 0x0000007F
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_DEF              (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_HSH              (0x07003518)

  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_OFF              ( 7)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_WID              ( 7)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_MSK              (0x00003F80)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_MIN              (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_MAX              (127) // 0x0000007F
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_DEF              (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_HSH              (0x07073518)

  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_OFF              (14)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_WID              ( 7)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_MSK              (0x001FC000)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_MIN              (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_MAX              (127) // 0x0000007F
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_DEF              (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_HSH              (0x070E3518)

  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_OFF              (21)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_WID              ( 7)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_MSK              (0x0FE00000)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_MIN              (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_MAX              (127) // 0x0000007F
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_DEF              (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_HSH              (0x07153518)

  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_OFF          (28)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_WID          ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_MSK          (0x10000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_MIN          (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_MAX          (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_DEF          (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_HSH          (0x011C3518)

  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_Spare_OFF                   (29)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_Spare_WID                   ( 3)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_Spare_MSK                   (0xE0000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_Spare_MIN                   (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_Spare_MAX                   (7) // 0x00000007
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_Spare_DEF                   (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLPICODING_Spare_HSH                   (0x031D3518)

#define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_REG                           (0x0000351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RefPi_OFF                   ( 0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RefPi_WID                   ( 4)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RefPi_MSK                   (0x0000000F)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RefPi_MIN                   (-8)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RefPi_MAX                   (7) // 0x00000007
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RefPi_DEF                   (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RefPi_HSH                   (0x8400351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllMask_OFF                 ( 4)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllMask_WID                 ( 2)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllMask_MSK                 (0x00000030)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllMask_MIN                 (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllMask_MAX                 (3) // 0x00000003
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllMask_DEF                 (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllMask_HSH                 (0x0204351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_OFF          ( 6)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_WID          ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_MSK          (0x00000040)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_MIN          (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_MAX          (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_DEF          (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_HSH          (0x0106351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_TxOn_OFF                    ( 7)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_TxOn_WID                    ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_TxOn_MSK                    (0x00000080)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_TxOn_MIN                    (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_TxOn_MAX                    (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_TxOn_DEF                    (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_TxOn_HSH                    (0x0107351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_OFF                ( 8)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_WID                ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_MSK                (0x00000100)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_MIN                (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_MAX                (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_DEF                (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_HSH                (0x0108351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_OFF                ( 9)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_WID                ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_MSK                (0x00000200)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_MIN                (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_MAX                (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_DEF                (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_HSH                (0x0109351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_OFF              (10)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_WID              ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_MSK              (0x00000400)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_MIN              (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_MAX              (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_DEF              (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_HSH              (0x010A351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_OFF                (11)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_WID                ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_MSK                (0x00000800)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_MIN                (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_MAX                (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_DEF                (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_HSH                (0x010B351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_OFF                 (12)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_WID                 ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_MSK                 (0x00001000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_MIN                 (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_MAX                 (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_DEF                 (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_HSH                 (0x010C351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_OFF                 (13)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_WID                 ( 2)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_MSK                 (0x00006000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_MIN                 (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_MAX                 (3) // 0x00000003
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_DEF                 (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_HSH                 (0x020D351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_OFF          (15)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_WID          ( 2)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MSK          (0x00018000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MIN          (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MAX          (3) // 0x00000003
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_DEF          (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_HSH          (0x020F351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_OFF                 (17)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_WID                 ( 2)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_MSK                 (0x00060000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_MIN                 (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_MAX                 (3) // 0x00000003
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_DEF                 (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_HSH                 (0x0211351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_OFF                (19)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_WID                ( 2)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_MSK                (0x00180000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_MIN                (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_MAX                (3) // 0x00000003
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_DEF                (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_HSH                (0x0213351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RxVref_OFF                  (21)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RxVref_WID                  ( 6)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RxVref_MSK                  (0x07E00000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RxVref_MIN                  (-32)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RxVref_MAX                  (31) // 0x0000001F
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RxVref_DEF                  (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_RxVref_HSH                  (0x8615351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_OFF                (27)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_WID                ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_MSK                (0x08000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_MIN                (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_MAX                (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_DEF                (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_HSH                (0x011B351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_OFF             (28)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_WID             ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_MSK             (0x10000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_MIN             (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_MAX             (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_DEF             (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_HSH             (0x011C351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_OFF              (29)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_WID              ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MSK              (0x20000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MIN              (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MAX              (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_DEF              (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_HSH              (0x011D351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_OFF             (30)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_WID             ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MSK             (0x40000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MIN             (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MAX             (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_DEF             (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_HSH             (0x011E351C)

  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_OFF            (31)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_WID            ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MSK            (0x80000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MIN            (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MAX            (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_DEF            (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_HSH            (0x011F351C)

#define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_REG                          (0x00003520)

  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_OFF                 ( 0)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_WID                 ( 4)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_MSK                 (0x0000000F)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_MIN                 (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_MAX                 (15) // 0x0000000F
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_DEF                 (0x0000000F)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_HSH                 (0x04003520)

  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_OFF             ( 4)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_WID             ( 2)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_MSK             (0x00000030)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_MIN             (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_MAX             (3) // 0x00000003
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_DEF             (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_HSH             (0x02043520)

  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_OFF     ( 6)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_WID     ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MSK     (0x00000040)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MIN     (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MAX     (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_DEF     (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_HSH     (0x01063520)

  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_OFF     ( 7)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_WID     ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MSK     (0x00000080)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MIN     (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MAX     (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_DEF     (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_HSH     (0x01073520)

  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_OFF          ( 8)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_WID          ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MSK          (0x00000100)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MIN          (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MAX          (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_DEF          (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_HSH          (0x01083520)

  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_OFF           ( 9)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_WID           ( 1)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MSK           (0x00000200)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MIN           (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MAX           (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_DEF           (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_HSH           (0x01093520)

  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_Spare_OFF                  (10)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_Spare_WID                  (22)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_Spare_MSK                  (0xFFFFFC00)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_Spare_MIN                  (0)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_Spare_MAX                  (4194303) // 0x003FFFFF
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_Spare_DEF                  (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCRCTLRANKSUSED_Spare_HSH                  (0x160A3520)

#define DDRCKECTLCH1_CR_DLLPITESTANDADC_REG                            (0x00003524)

  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_RunTest_OFF                  ( 0)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_RunTest_WID                  ( 1)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_RunTest_MSK                  (0x00000001)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_RunTest_MIN                  (0)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_RunTest_MAX                  (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_RunTest_DEF                  (0x00000000)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_RunTest_HSH                  (0x01003524)

  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Load_OFF                     ( 1)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Load_WID                     ( 1)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Load_MSK                     (0x00000002)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Load_MIN                     (0)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Load_MAX                     (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Load_DEF                     (0x00000000)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Load_HSH                     (0x01013524)

  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeHVM_OFF                  ( 2)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeHVM_WID                  ( 1)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeHVM_MSK                  (0x00000004)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeHVM_MIN                  (0)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeHVM_MAX                  (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeHVM_DEF                  (0x00000000)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeHVM_HSH                  (0x01023524)

  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeDV_OFF                   ( 3)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeDV_WID                   ( 1)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeDV_MSK                   (0x00000008)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeDV_MIN                   (0)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeDV_MAX                   (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeDV_DEF                   (0x00000000)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_ModeDV_HSH                   (0x01033524)

  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CalCfdl_OFF                  ( 4)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CalCfdl_WID                  ( 1)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CalCfdl_MSK                  (0x00000010)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CalCfdl_MIN                  (0)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CalCfdl_MAX                  (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CalCfdl_DEF                  (0x00000000)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CalCfdl_HSH                  (0x01043524)

  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_LoadCount_OFF                ( 5)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_LoadCount_WID                (10)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_LoadCount_MSK                (0x00007FE0)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_LoadCount_MIN                (0)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_LoadCount_MAX                (1023) // 0x000003FF
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_LoadCount_DEF                (0x00000000)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_LoadCount_HSH                (0x0A053524)

  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CountStatus_OFF              (15)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CountStatus_WID              (10)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CountStatus_MSK              (0x01FF8000)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CountStatus_MIN              (0)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CountStatus_MAX              (1023) // 0x000003FF
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CountStatus_DEF              (0x00000000)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_CountStatus_HSH              (0x0A0F3524)

  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF         (25)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID         ( 1)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK         (0x02000000)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN         (0)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX         (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF         (0x00000000)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH         (0x01193524)

  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Spare_OFF                    (26)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Spare_WID                    ( 6)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Spare_MSK                    (0xFC000000)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Spare_MIN                    (0)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Spare_MAX                    (63) // 0x0000003F
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Spare_DEF                    (0x00000000)
  #define DDRCKECTLCH1_CR_DLLPITESTANDADC_Spare_HSH                    (0x061A3524)

#define DDRCKECTLCH1_CR_DDRCMDMISR_REG                                 (0x00003528)

  #define DDRCKECTLCH1_CR_DDRCMDMISR_shift_16_OFF                      ( 0)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_shift_16_WID                      ( 1)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_shift_16_MSK                      (0x00000001)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_shift_16_MIN                      (0)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_shift_16_MAX                      (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCMDMISR_shift_16_DEF                      (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_shift_16_HSH                      (0x01003528)

  #define DDRCKECTLCH1_CR_DDRCMDMISR_clken_pulse_mode_OFF              ( 1)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_clken_pulse_mode_WID              ( 1)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_clken_pulse_mode_MSK              (0x00000002)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_clken_pulse_mode_MIN              (0)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_clken_pulse_mode_MAX              (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCMDMISR_clken_pulse_mode_DEF              (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_clken_pulse_mode_HSH              (0x01013528)

  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_mode_OFF                ( 2)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_mode_WID                ( 1)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_mode_MSK                (0x00000004)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_mode_MIN                (0)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_mode_MAX                (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_mode_DEF                (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_mode_HSH                (0x01023528)

  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_OFF                     ( 3)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_WID                     ( 1)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_MSK                     (0x00000008)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_MIN                     (0)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_MAX                     (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_DEF                     (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_reg_clken_HSH                     (0x01033528)

  #define DDRCKECTLCH1_CR_DDRCMDMISR_feedback_en_OFF                   ( 4)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_feedback_en_WID                   ( 1)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_feedback_en_MSK                   (0x00000010)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_feedback_en_MIN                   (0)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_feedback_en_MAX                   (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCMDMISR_feedback_en_DEF                   (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_feedback_en_HSH                   (0x01043528)

  #define DDRCKECTLCH1_CR_DDRCMDMISR_event_mode_OFF                    ( 5)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_event_mode_WID                    ( 1)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_event_mode_MSK                    (0x00000020)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_event_mode_MIN                    (0)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_event_mode_MAX                    (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCMDMISR_event_mode_DEF                    (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_event_mode_HSH                    (0x01053528)

  #define DDRCKECTLCH1_CR_DDRCMDMISR_lfsr_reset_OFF                    ( 6)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_lfsr_reset_WID                    ( 1)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_lfsr_reset_MSK                    (0x00000040)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_lfsr_reset_MIN                    (0)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_lfsr_reset_MAX                    (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCMDMISR_lfsr_reset_DEF                    (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_lfsr_reset_HSH                    (0x01063528)

  #define DDRCKECTLCH1_CR_DDRCMDMISR_sdo_en_OFF                        ( 7)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_sdo_en_WID                        ( 1)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_sdo_en_MSK                        (0x00000080)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_sdo_en_MIN                        (0)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_sdo_en_MAX                        (1) // 0x00000001
  #define DDRCKECTLCH1_CR_DDRCMDMISR_sdo_en_DEF                        (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_sdo_en_HSH                        (0x01073528)

  #define DDRCKECTLCH1_CR_DDRCMDMISR_cr_rd_data_OFF                    (16)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_cr_rd_data_WID                    (16)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_cr_rd_data_MSK                    (0xFFFF0000)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_cr_rd_data_MIN                    (0)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_cr_rd_data_MAX                    (65535) // 0x0000FFFF
  #define DDRCKECTLCH1_CR_DDRCMDMISR_cr_rd_data_DEF                    (0x00000000)
  #define DDRCKECTLCH1_CR_DDRCMDMISR_cr_rd_data_HSH                    (0x10103528)

#define DDRDATA_CR_RXTRAINRANK0_REG                                    (0x00003600)

  #define DDRDATA_CR_RXTRAINRANK0_RxRcvEnPi_OFF                        ( 0)
  #define DDRDATA_CR_RXTRAINRANK0_RxRcvEnPi_WID                        ( 9)
  #define DDRDATA_CR_RXTRAINRANK0_RxRcvEnPi_MSK                        (0x000001FF)
  #define DDRDATA_CR_RXTRAINRANK0_RxRcvEnPi_MIN                        (0)
  #define DDRDATA_CR_RXTRAINRANK0_RxRcvEnPi_MAX                        (511) // 0x000001FF
  #define DDRDATA_CR_RXTRAINRANK0_RxRcvEnPi_DEF                        (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK0_RxRcvEnPi_HSH                        (0x09003600)

  #define DDRDATA_CR_RXTRAINRANK0_RxDqsPPi_OFF                         ( 9)
  #define DDRDATA_CR_RXTRAINRANK0_RxDqsPPi_WID                         ( 6)
  #define DDRDATA_CR_RXTRAINRANK0_RxDqsPPi_MSK                         (0x00007E00)
  #define DDRDATA_CR_RXTRAINRANK0_RxDqsPPi_MIN                         (0)
  #define DDRDATA_CR_RXTRAINRANK0_RxDqsPPi_MAX                         (63) // 0x0000003F
  #define DDRDATA_CR_RXTRAINRANK0_RxDqsPPi_DEF                         (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK0_RxDqsPPi_HSH                         (0x06093600)

  #define DDRDATA_CR_RXTRAINRANK0_RxEq_OFF                             (15)
  #define DDRDATA_CR_RXTRAINRANK0_RxEq_WID                             ( 5)
  #define DDRDATA_CR_RXTRAINRANK0_RxEq_MSK                             (0x000F8000)
  #define DDRDATA_CR_RXTRAINRANK0_RxEq_MIN                             (0)
  #define DDRDATA_CR_RXTRAINRANK0_RxEq_MAX                             (31) // 0x0000001F
  #define DDRDATA_CR_RXTRAINRANK0_RxEq_DEF                             (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK0_RxEq_HSH                             (0x050F3600)

  #define DDRDATA_CR_RXTRAINRANK0_RxDqsNPi_OFF                         (20)
  #define DDRDATA_CR_RXTRAINRANK0_RxDqsNPi_WID                         ( 6)
  #define DDRDATA_CR_RXTRAINRANK0_RxDqsNPi_MSK                         (0x03F00000)
  #define DDRDATA_CR_RXTRAINRANK0_RxDqsNPi_MIN                         (0)
  #define DDRDATA_CR_RXTRAINRANK0_RxDqsNPi_MAX                         (63) // 0x0000003F
  #define DDRDATA_CR_RXTRAINRANK0_RxDqsNPi_DEF                         (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK0_RxDqsNPi_HSH                         (0x06143600)

  #define DDRDATA_CR_RXTRAINRANK0_RxVref_OFF                           (26)
  #define DDRDATA_CR_RXTRAINRANK0_RxVref_WID                           ( 6)
  #define DDRDATA_CR_RXTRAINRANK0_RxVref_MSK                           (0xFC000000)
  #define DDRDATA_CR_RXTRAINRANK0_RxVref_MIN                           (-32)
  #define DDRDATA_CR_RXTRAINRANK0_RxVref_MAX                           (31) // 0x0000001F
  #define DDRDATA_CR_RXTRAINRANK0_RxVref_DEF                           (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK0_RxVref_HSH                           (0x861A3600)

#define DDRDATA_CR_RXTRAINRANK1_REG                                    (0x00003604)

  #define DDRDATA_CR_RXTRAINRANK1_RxRcvEnPi_OFF                        ( 0)
  #define DDRDATA_CR_RXTRAINRANK1_RxRcvEnPi_WID                        ( 9)
  #define DDRDATA_CR_RXTRAINRANK1_RxRcvEnPi_MSK                        (0x000001FF)
  #define DDRDATA_CR_RXTRAINRANK1_RxRcvEnPi_MIN                        (0)
  #define DDRDATA_CR_RXTRAINRANK1_RxRcvEnPi_MAX                        (511) // 0x000001FF
  #define DDRDATA_CR_RXTRAINRANK1_RxRcvEnPi_DEF                        (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK1_RxRcvEnPi_HSH                        (0x09003604)

  #define DDRDATA_CR_RXTRAINRANK1_RxDqsPPi_OFF                         ( 9)
  #define DDRDATA_CR_RXTRAINRANK1_RxDqsPPi_WID                         ( 6)
  #define DDRDATA_CR_RXTRAINRANK1_RxDqsPPi_MSK                         (0x00007E00)
  #define DDRDATA_CR_RXTRAINRANK1_RxDqsPPi_MIN                         (0)
  #define DDRDATA_CR_RXTRAINRANK1_RxDqsPPi_MAX                         (63) // 0x0000003F
  #define DDRDATA_CR_RXTRAINRANK1_RxDqsPPi_DEF                         (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK1_RxDqsPPi_HSH                         (0x06093604)

  #define DDRDATA_CR_RXTRAINRANK1_RxEq_OFF                             (15)
  #define DDRDATA_CR_RXTRAINRANK1_RxEq_WID                             ( 5)
  #define DDRDATA_CR_RXTRAINRANK1_RxEq_MSK                             (0x000F8000)
  #define DDRDATA_CR_RXTRAINRANK1_RxEq_MIN                             (0)
  #define DDRDATA_CR_RXTRAINRANK1_RxEq_MAX                             (31) // 0x0000001F
  #define DDRDATA_CR_RXTRAINRANK1_RxEq_DEF                             (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK1_RxEq_HSH                             (0x050F3604)

  #define DDRDATA_CR_RXTRAINRANK1_RxDqsNPi_OFF                         (20)
  #define DDRDATA_CR_RXTRAINRANK1_RxDqsNPi_WID                         ( 6)
  #define DDRDATA_CR_RXTRAINRANK1_RxDqsNPi_MSK                         (0x03F00000)
  #define DDRDATA_CR_RXTRAINRANK1_RxDqsNPi_MIN                         (0)
  #define DDRDATA_CR_RXTRAINRANK1_RxDqsNPi_MAX                         (63) // 0x0000003F
  #define DDRDATA_CR_RXTRAINRANK1_RxDqsNPi_DEF                         (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK1_RxDqsNPi_HSH                         (0x06143604)

  #define DDRDATA_CR_RXTRAINRANK1_RxVref_OFF                           (26)
  #define DDRDATA_CR_RXTRAINRANK1_RxVref_WID                           ( 6)
  #define DDRDATA_CR_RXTRAINRANK1_RxVref_MSK                           (0xFC000000)
  #define DDRDATA_CR_RXTRAINRANK1_RxVref_MIN                           (-32)
  #define DDRDATA_CR_RXTRAINRANK1_RxVref_MAX                           (31) // 0x0000001F
  #define DDRDATA_CR_RXTRAINRANK1_RxVref_DEF                           (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK1_RxVref_HSH                           (0x861A3604)

#define DDRDATA_CR_RXTRAINRANK2_REG                                    (0x00003608)

  #define DDRDATA_CR_RXTRAINRANK2_RxRcvEnPi_OFF                        ( 0)
  #define DDRDATA_CR_RXTRAINRANK2_RxRcvEnPi_WID                        ( 9)
  #define DDRDATA_CR_RXTRAINRANK2_RxRcvEnPi_MSK                        (0x000001FF)
  #define DDRDATA_CR_RXTRAINRANK2_RxRcvEnPi_MIN                        (0)
  #define DDRDATA_CR_RXTRAINRANK2_RxRcvEnPi_MAX                        (511) // 0x000001FF
  #define DDRDATA_CR_RXTRAINRANK2_RxRcvEnPi_DEF                        (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK2_RxRcvEnPi_HSH                        (0x09003608)

  #define DDRDATA_CR_RXTRAINRANK2_RxDqsPPi_OFF                         ( 9)
  #define DDRDATA_CR_RXTRAINRANK2_RxDqsPPi_WID                         ( 6)
  #define DDRDATA_CR_RXTRAINRANK2_RxDqsPPi_MSK                         (0x00007E00)
  #define DDRDATA_CR_RXTRAINRANK2_RxDqsPPi_MIN                         (0)
  #define DDRDATA_CR_RXTRAINRANK2_RxDqsPPi_MAX                         (63) // 0x0000003F
  #define DDRDATA_CR_RXTRAINRANK2_RxDqsPPi_DEF                         (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK2_RxDqsPPi_HSH                         (0x06093608)

  #define DDRDATA_CR_RXTRAINRANK2_RxEq_OFF                             (15)
  #define DDRDATA_CR_RXTRAINRANK2_RxEq_WID                             ( 5)
  #define DDRDATA_CR_RXTRAINRANK2_RxEq_MSK                             (0x000F8000)
  #define DDRDATA_CR_RXTRAINRANK2_RxEq_MIN                             (0)
  #define DDRDATA_CR_RXTRAINRANK2_RxEq_MAX                             (31) // 0x0000001F
  #define DDRDATA_CR_RXTRAINRANK2_RxEq_DEF                             (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK2_RxEq_HSH                             (0x050F3608)

  #define DDRDATA_CR_RXTRAINRANK2_RxDqsNPi_OFF                         (20)
  #define DDRDATA_CR_RXTRAINRANK2_RxDqsNPi_WID                         ( 6)
  #define DDRDATA_CR_RXTRAINRANK2_RxDqsNPi_MSK                         (0x03F00000)
  #define DDRDATA_CR_RXTRAINRANK2_RxDqsNPi_MIN                         (0)
  #define DDRDATA_CR_RXTRAINRANK2_RxDqsNPi_MAX                         (63) // 0x0000003F
  #define DDRDATA_CR_RXTRAINRANK2_RxDqsNPi_DEF                         (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK2_RxDqsNPi_HSH                         (0x06143608)

  #define DDRDATA_CR_RXTRAINRANK2_RxVref_OFF                           (26)
  #define DDRDATA_CR_RXTRAINRANK2_RxVref_WID                           ( 6)
  #define DDRDATA_CR_RXTRAINRANK2_RxVref_MSK                           (0xFC000000)
  #define DDRDATA_CR_RXTRAINRANK2_RxVref_MIN                           (-32)
  #define DDRDATA_CR_RXTRAINRANK2_RxVref_MAX                           (31) // 0x0000001F
  #define DDRDATA_CR_RXTRAINRANK2_RxVref_DEF                           (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK2_RxVref_HSH                           (0x861A3608)

#define DDRDATA_CR_RXTRAINRANK3_REG                                    (0x0000360C)

  #define DDRDATA_CR_RXTRAINRANK3_RxRcvEnPi_OFF                        ( 0)
  #define DDRDATA_CR_RXTRAINRANK3_RxRcvEnPi_WID                        ( 9)
  #define DDRDATA_CR_RXTRAINRANK3_RxRcvEnPi_MSK                        (0x000001FF)
  #define DDRDATA_CR_RXTRAINRANK3_RxRcvEnPi_MIN                        (0)
  #define DDRDATA_CR_RXTRAINRANK3_RxRcvEnPi_MAX                        (511) // 0x000001FF
  #define DDRDATA_CR_RXTRAINRANK3_RxRcvEnPi_DEF                        (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK3_RxRcvEnPi_HSH                        (0x0900360C)

  #define DDRDATA_CR_RXTRAINRANK3_RxDqsPPi_OFF                         ( 9)
  #define DDRDATA_CR_RXTRAINRANK3_RxDqsPPi_WID                         ( 6)
  #define DDRDATA_CR_RXTRAINRANK3_RxDqsPPi_MSK                         (0x00007E00)
  #define DDRDATA_CR_RXTRAINRANK3_RxDqsPPi_MIN                         (0)
  #define DDRDATA_CR_RXTRAINRANK3_RxDqsPPi_MAX                         (63) // 0x0000003F
  #define DDRDATA_CR_RXTRAINRANK3_RxDqsPPi_DEF                         (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK3_RxDqsPPi_HSH                         (0x0609360C)

  #define DDRDATA_CR_RXTRAINRANK3_RxEq_OFF                             (15)
  #define DDRDATA_CR_RXTRAINRANK3_RxEq_WID                             ( 5)
  #define DDRDATA_CR_RXTRAINRANK3_RxEq_MSK                             (0x000F8000)
  #define DDRDATA_CR_RXTRAINRANK3_RxEq_MIN                             (0)
  #define DDRDATA_CR_RXTRAINRANK3_RxEq_MAX                             (31) // 0x0000001F
  #define DDRDATA_CR_RXTRAINRANK3_RxEq_DEF                             (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK3_RxEq_HSH                             (0x050F360C)

  #define DDRDATA_CR_RXTRAINRANK3_RxDqsNPi_OFF                         (20)
  #define DDRDATA_CR_RXTRAINRANK3_RxDqsNPi_WID                         ( 6)
  #define DDRDATA_CR_RXTRAINRANK3_RxDqsNPi_MSK                         (0x03F00000)
  #define DDRDATA_CR_RXTRAINRANK3_RxDqsNPi_MIN                         (0)
  #define DDRDATA_CR_RXTRAINRANK3_RxDqsNPi_MAX                         (63) // 0x0000003F
  #define DDRDATA_CR_RXTRAINRANK3_RxDqsNPi_DEF                         (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK3_RxDqsNPi_HSH                         (0x0614360C)

  #define DDRDATA_CR_RXTRAINRANK3_RxVref_OFF                           (26)
  #define DDRDATA_CR_RXTRAINRANK3_RxVref_WID                           ( 6)
  #define DDRDATA_CR_RXTRAINRANK3_RxVref_MSK                           (0xFC000000)
  #define DDRDATA_CR_RXTRAINRANK3_RxVref_MIN                           (-32)
  #define DDRDATA_CR_RXTRAINRANK3_RxVref_MAX                           (31) // 0x0000001F
  #define DDRDATA_CR_RXTRAINRANK3_RxVref_DEF                           (0x00000000)
  #define DDRDATA_CR_RXTRAINRANK3_RxVref_HSH                           (0x861A360C)

#define DDRDATA_CR_RXPERBITRANK0_REG                                   (0x00003610)

  #define DDRDATA_CR_RXPERBITRANK0_Lane0_OFF                           ( 0)
  #define DDRDATA_CR_RXPERBITRANK0_Lane0_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK0_Lane0_MSK                           (0x0000000F)
  #define DDRDATA_CR_RXPERBITRANK0_Lane0_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK0_Lane0_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK0_Lane0_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK0_Lane0_HSH                           (0x04003610)

  #define DDRDATA_CR_RXPERBITRANK0_Lane1_OFF                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK0_Lane1_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK0_Lane1_MSK                           (0x000000F0)
  #define DDRDATA_CR_RXPERBITRANK0_Lane1_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK0_Lane1_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK0_Lane1_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK0_Lane1_HSH                           (0x04043610)

  #define DDRDATA_CR_RXPERBITRANK0_Lane2_OFF                           ( 8)
  #define DDRDATA_CR_RXPERBITRANK0_Lane2_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK0_Lane2_MSK                           (0x00000F00)
  #define DDRDATA_CR_RXPERBITRANK0_Lane2_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK0_Lane2_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK0_Lane2_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK0_Lane2_HSH                           (0x04083610)

  #define DDRDATA_CR_RXPERBITRANK0_Lane3_OFF                           (12)
  #define DDRDATA_CR_RXPERBITRANK0_Lane3_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK0_Lane3_MSK                           (0x0000F000)
  #define DDRDATA_CR_RXPERBITRANK0_Lane3_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK0_Lane3_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK0_Lane3_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK0_Lane3_HSH                           (0x040C3610)

  #define DDRDATA_CR_RXPERBITRANK0_Lane4_OFF                           (16)
  #define DDRDATA_CR_RXPERBITRANK0_Lane4_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK0_Lane4_MSK                           (0x000F0000)
  #define DDRDATA_CR_RXPERBITRANK0_Lane4_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK0_Lane4_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK0_Lane4_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK0_Lane4_HSH                           (0x04103610)

  #define DDRDATA_CR_RXPERBITRANK0_Lane5_OFF                           (20)
  #define DDRDATA_CR_RXPERBITRANK0_Lane5_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK0_Lane5_MSK                           (0x00F00000)
  #define DDRDATA_CR_RXPERBITRANK0_Lane5_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK0_Lane5_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK0_Lane5_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK0_Lane5_HSH                           (0x04143610)

  #define DDRDATA_CR_RXPERBITRANK0_Lane6_OFF                           (24)
  #define DDRDATA_CR_RXPERBITRANK0_Lane6_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK0_Lane6_MSK                           (0x0F000000)
  #define DDRDATA_CR_RXPERBITRANK0_Lane6_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK0_Lane6_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK0_Lane6_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK0_Lane6_HSH                           (0x04183610)

  #define DDRDATA_CR_RXPERBITRANK0_Lane7_OFF                           (28)
  #define DDRDATA_CR_RXPERBITRANK0_Lane7_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK0_Lane7_MSK                           (0xF0000000)
  #define DDRDATA_CR_RXPERBITRANK0_Lane7_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK0_Lane7_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK0_Lane7_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK0_Lane7_HSH                           (0x041C3610)

#define DDRDATA_CR_RXPERBITRANK1_REG                                   (0x00003614)

  #define DDRDATA_CR_RXPERBITRANK1_Lane0_OFF                           ( 0)
  #define DDRDATA_CR_RXPERBITRANK1_Lane0_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK1_Lane0_MSK                           (0x0000000F)
  #define DDRDATA_CR_RXPERBITRANK1_Lane0_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK1_Lane0_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK1_Lane0_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK1_Lane0_HSH                           (0x04003614)

  #define DDRDATA_CR_RXPERBITRANK1_Lane1_OFF                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK1_Lane1_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK1_Lane1_MSK                           (0x000000F0)
  #define DDRDATA_CR_RXPERBITRANK1_Lane1_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK1_Lane1_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK1_Lane1_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK1_Lane1_HSH                           (0x04043614)

  #define DDRDATA_CR_RXPERBITRANK1_Lane2_OFF                           ( 8)
  #define DDRDATA_CR_RXPERBITRANK1_Lane2_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK1_Lane2_MSK                           (0x00000F00)
  #define DDRDATA_CR_RXPERBITRANK1_Lane2_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK1_Lane2_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK1_Lane2_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK1_Lane2_HSH                           (0x04083614)

  #define DDRDATA_CR_RXPERBITRANK1_Lane3_OFF                           (12)
  #define DDRDATA_CR_RXPERBITRANK1_Lane3_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK1_Lane3_MSK                           (0x0000F000)
  #define DDRDATA_CR_RXPERBITRANK1_Lane3_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK1_Lane3_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK1_Lane3_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK1_Lane3_HSH                           (0x040C3614)

  #define DDRDATA_CR_RXPERBITRANK1_Lane4_OFF                           (16)
  #define DDRDATA_CR_RXPERBITRANK1_Lane4_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK1_Lane4_MSK                           (0x000F0000)
  #define DDRDATA_CR_RXPERBITRANK1_Lane4_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK1_Lane4_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK1_Lane4_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK1_Lane4_HSH                           (0x04103614)

  #define DDRDATA_CR_RXPERBITRANK1_Lane5_OFF                           (20)
  #define DDRDATA_CR_RXPERBITRANK1_Lane5_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK1_Lane5_MSK                           (0x00F00000)
  #define DDRDATA_CR_RXPERBITRANK1_Lane5_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK1_Lane5_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK1_Lane5_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK1_Lane5_HSH                           (0x04143614)

  #define DDRDATA_CR_RXPERBITRANK1_Lane6_OFF                           (24)
  #define DDRDATA_CR_RXPERBITRANK1_Lane6_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK1_Lane6_MSK                           (0x0F000000)
  #define DDRDATA_CR_RXPERBITRANK1_Lane6_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK1_Lane6_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK1_Lane6_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK1_Lane6_HSH                           (0x04183614)

  #define DDRDATA_CR_RXPERBITRANK1_Lane7_OFF                           (28)
  #define DDRDATA_CR_RXPERBITRANK1_Lane7_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK1_Lane7_MSK                           (0xF0000000)
  #define DDRDATA_CR_RXPERBITRANK1_Lane7_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK1_Lane7_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK1_Lane7_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK1_Lane7_HSH                           (0x041C3614)

#define DDRDATA_CR_RXPERBITRANK2_REG                                   (0x00003618)

  #define DDRDATA_CR_RXPERBITRANK2_Lane0_OFF                           ( 0)
  #define DDRDATA_CR_RXPERBITRANK2_Lane0_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK2_Lane0_MSK                           (0x0000000F)
  #define DDRDATA_CR_RXPERBITRANK2_Lane0_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK2_Lane0_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK2_Lane0_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK2_Lane0_HSH                           (0x04003618)

  #define DDRDATA_CR_RXPERBITRANK2_Lane1_OFF                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK2_Lane1_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK2_Lane1_MSK                           (0x000000F0)
  #define DDRDATA_CR_RXPERBITRANK2_Lane1_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK2_Lane1_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK2_Lane1_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK2_Lane1_HSH                           (0x04043618)

  #define DDRDATA_CR_RXPERBITRANK2_Lane2_OFF                           ( 8)
  #define DDRDATA_CR_RXPERBITRANK2_Lane2_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK2_Lane2_MSK                           (0x00000F00)
  #define DDRDATA_CR_RXPERBITRANK2_Lane2_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK2_Lane2_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK2_Lane2_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK2_Lane2_HSH                           (0x04083618)

  #define DDRDATA_CR_RXPERBITRANK2_Lane3_OFF                           (12)
  #define DDRDATA_CR_RXPERBITRANK2_Lane3_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK2_Lane3_MSK                           (0x0000F000)
  #define DDRDATA_CR_RXPERBITRANK2_Lane3_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK2_Lane3_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK2_Lane3_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK2_Lane3_HSH                           (0x040C3618)

  #define DDRDATA_CR_RXPERBITRANK2_Lane4_OFF                           (16)
  #define DDRDATA_CR_RXPERBITRANK2_Lane4_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK2_Lane4_MSK                           (0x000F0000)
  #define DDRDATA_CR_RXPERBITRANK2_Lane4_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK2_Lane4_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK2_Lane4_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK2_Lane4_HSH                           (0x04103618)

  #define DDRDATA_CR_RXPERBITRANK2_Lane5_OFF                           (20)
  #define DDRDATA_CR_RXPERBITRANK2_Lane5_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK2_Lane5_MSK                           (0x00F00000)
  #define DDRDATA_CR_RXPERBITRANK2_Lane5_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK2_Lane5_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK2_Lane5_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK2_Lane5_HSH                           (0x04143618)

  #define DDRDATA_CR_RXPERBITRANK2_Lane6_OFF                           (24)
  #define DDRDATA_CR_RXPERBITRANK2_Lane6_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK2_Lane6_MSK                           (0x0F000000)
  #define DDRDATA_CR_RXPERBITRANK2_Lane6_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK2_Lane6_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK2_Lane6_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK2_Lane6_HSH                           (0x04183618)

  #define DDRDATA_CR_RXPERBITRANK2_Lane7_OFF                           (28)
  #define DDRDATA_CR_RXPERBITRANK2_Lane7_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK2_Lane7_MSK                           (0xF0000000)
  #define DDRDATA_CR_RXPERBITRANK2_Lane7_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK2_Lane7_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK2_Lane7_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK2_Lane7_HSH                           (0x041C3618)

#define DDRDATA_CR_RXPERBITRANK3_REG                                   (0x0000361C)

  #define DDRDATA_CR_RXPERBITRANK3_Lane0_OFF                           ( 0)
  #define DDRDATA_CR_RXPERBITRANK3_Lane0_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK3_Lane0_MSK                           (0x0000000F)
  #define DDRDATA_CR_RXPERBITRANK3_Lane0_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK3_Lane0_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK3_Lane0_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK3_Lane0_HSH                           (0x0400361C)

  #define DDRDATA_CR_RXPERBITRANK3_Lane1_OFF                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK3_Lane1_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK3_Lane1_MSK                           (0x000000F0)
  #define DDRDATA_CR_RXPERBITRANK3_Lane1_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK3_Lane1_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK3_Lane1_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK3_Lane1_HSH                           (0x0404361C)

  #define DDRDATA_CR_RXPERBITRANK3_Lane2_OFF                           ( 8)
  #define DDRDATA_CR_RXPERBITRANK3_Lane2_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK3_Lane2_MSK                           (0x00000F00)
  #define DDRDATA_CR_RXPERBITRANK3_Lane2_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK3_Lane2_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK3_Lane2_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK3_Lane2_HSH                           (0x0408361C)

  #define DDRDATA_CR_RXPERBITRANK3_Lane3_OFF                           (12)
  #define DDRDATA_CR_RXPERBITRANK3_Lane3_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK3_Lane3_MSK                           (0x0000F000)
  #define DDRDATA_CR_RXPERBITRANK3_Lane3_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK3_Lane3_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK3_Lane3_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK3_Lane3_HSH                           (0x040C361C)

  #define DDRDATA_CR_RXPERBITRANK3_Lane4_OFF                           (16)
  #define DDRDATA_CR_RXPERBITRANK3_Lane4_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK3_Lane4_MSK                           (0x000F0000)
  #define DDRDATA_CR_RXPERBITRANK3_Lane4_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK3_Lane4_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK3_Lane4_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK3_Lane4_HSH                           (0x0410361C)

  #define DDRDATA_CR_RXPERBITRANK3_Lane5_OFF                           (20)
  #define DDRDATA_CR_RXPERBITRANK3_Lane5_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK3_Lane5_MSK                           (0x00F00000)
  #define DDRDATA_CR_RXPERBITRANK3_Lane5_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK3_Lane5_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK3_Lane5_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK3_Lane5_HSH                           (0x0414361C)

  #define DDRDATA_CR_RXPERBITRANK3_Lane6_OFF                           (24)
  #define DDRDATA_CR_RXPERBITRANK3_Lane6_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK3_Lane6_MSK                           (0x0F000000)
  #define DDRDATA_CR_RXPERBITRANK3_Lane6_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK3_Lane6_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK3_Lane6_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK3_Lane6_HSH                           (0x0418361C)

  #define DDRDATA_CR_RXPERBITRANK3_Lane7_OFF                           (28)
  #define DDRDATA_CR_RXPERBITRANK3_Lane7_WID                           ( 4)
  #define DDRDATA_CR_RXPERBITRANK3_Lane7_MSK                           (0xF0000000)
  #define DDRDATA_CR_RXPERBITRANK3_Lane7_MIN                           (0)
  #define DDRDATA_CR_RXPERBITRANK3_Lane7_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_RXPERBITRANK3_Lane7_DEF                           (0x00000000)
  #define DDRDATA_CR_RXPERBITRANK3_Lane7_HSH                           (0x041C361C)

#define DDRDATA_CR_TXTRAINRANK0_REG                                    (0x00003620)

  #define DDRDATA_CR_TXTRAINRANK0_TxDqDelay_OFF                        ( 0)
  #define DDRDATA_CR_TXTRAINRANK0_TxDqDelay_WID                        ( 9)
  #define DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MSK                        (0x000001FF)
  #define DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MIN                        (0)
  #define DDRDATA_CR_TXTRAINRANK0_TxDqDelay_MAX                        (511) // 0x000001FF
  #define DDRDATA_CR_TXTRAINRANK0_TxDqDelay_DEF                        (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK0_TxDqDelay_HSH                        (0x09003620)

  #define DDRDATA_CR_TXTRAINRANK0_TxDqsDelay_OFF                       ( 9)
  #define DDRDATA_CR_TXTRAINRANK0_TxDqsDelay_WID                       ( 9)
  #define DDRDATA_CR_TXTRAINRANK0_TxDqsDelay_MSK                       (0x0003FE00)
  #define DDRDATA_CR_TXTRAINRANK0_TxDqsDelay_MIN                       (0)
  #define DDRDATA_CR_TXTRAINRANK0_TxDqsDelay_MAX                       (511) // 0x000001FF
  #define DDRDATA_CR_TXTRAINRANK0_TxDqsDelay_DEF                       (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK0_TxDqsDelay_HSH                       (0x09093620)

  #define DDRDATA_CR_TXTRAINRANK0_Spare0_OFF                           (18)
  #define DDRDATA_CR_TXTRAINRANK0_Spare0_WID                           ( 2)
  #define DDRDATA_CR_TXTRAINRANK0_Spare0_MSK                           (0x000C0000)
  #define DDRDATA_CR_TXTRAINRANK0_Spare0_MIN                           (0)
  #define DDRDATA_CR_TXTRAINRANK0_Spare0_MAX                           (3) // 0x00000003
  #define DDRDATA_CR_TXTRAINRANK0_Spare0_DEF                           (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK0_Spare0_HSH                           (0x02123620)

  #define DDRDATA_CR_TXTRAINRANK0_TxEqualization_OFF                   (20)
  #define DDRDATA_CR_TXTRAINRANK0_TxEqualization_WID                   ( 6)
  #define DDRDATA_CR_TXTRAINRANK0_TxEqualization_MSK                   (0x03F00000)
  #define DDRDATA_CR_TXTRAINRANK0_TxEqualization_MIN                   (0)
  #define DDRDATA_CR_TXTRAINRANK0_TxEqualization_MAX                   (63) // 0x0000003F
  #define DDRDATA_CR_TXTRAINRANK0_TxEqualization_DEF                   (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK0_TxEqualization_HSH                   (0x06143620)

  #define DDRDATA_CR_TXTRAINRANK0_Spare1_OFF                           (26)
  #define DDRDATA_CR_TXTRAINRANK0_Spare1_WID                           ( 6)
  #define DDRDATA_CR_TXTRAINRANK0_Spare1_MSK                           (0xFC000000)
  #define DDRDATA_CR_TXTRAINRANK0_Spare1_MIN                           (0)
  #define DDRDATA_CR_TXTRAINRANK0_Spare1_MAX                           (63) // 0x0000003F
  #define DDRDATA_CR_TXTRAINRANK0_Spare1_DEF                           (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK0_Spare1_HSH                           (0x061A3620)

#define DDRDATA_CR_TXTRAINRANK1_REG                                    (0x00003624)

  #define DDRDATA_CR_TXTRAINRANK1_TxDqDelay_OFF                        ( 0)
  #define DDRDATA_CR_TXTRAINRANK1_TxDqDelay_WID                        ( 9)
  #define DDRDATA_CR_TXTRAINRANK1_TxDqDelay_MSK                        (0x000001FF)
  #define DDRDATA_CR_TXTRAINRANK1_TxDqDelay_MIN                        (0)
  #define DDRDATA_CR_TXTRAINRANK1_TxDqDelay_MAX                        (511) // 0x000001FF
  #define DDRDATA_CR_TXTRAINRANK1_TxDqDelay_DEF                        (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK1_TxDqDelay_HSH                        (0x09003624)

  #define DDRDATA_CR_TXTRAINRANK1_TxDqsDelay_OFF                       ( 9)
  #define DDRDATA_CR_TXTRAINRANK1_TxDqsDelay_WID                       ( 9)
  #define DDRDATA_CR_TXTRAINRANK1_TxDqsDelay_MSK                       (0x0003FE00)
  #define DDRDATA_CR_TXTRAINRANK1_TxDqsDelay_MIN                       (0)
  #define DDRDATA_CR_TXTRAINRANK1_TxDqsDelay_MAX                       (511) // 0x000001FF
  #define DDRDATA_CR_TXTRAINRANK1_TxDqsDelay_DEF                       (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK1_TxDqsDelay_HSH                       (0x09093624)

  #define DDRDATA_CR_TXTRAINRANK1_Spare0_OFF                           (18)
  #define DDRDATA_CR_TXTRAINRANK1_Spare0_WID                           ( 2)
  #define DDRDATA_CR_TXTRAINRANK1_Spare0_MSK                           (0x000C0000)
  #define DDRDATA_CR_TXTRAINRANK1_Spare0_MIN                           (0)
  #define DDRDATA_CR_TXTRAINRANK1_Spare0_MAX                           (3) // 0x00000003
  #define DDRDATA_CR_TXTRAINRANK1_Spare0_DEF                           (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK1_Spare0_HSH                           (0x02123624)

  #define DDRDATA_CR_TXTRAINRANK1_TxEqualization_OFF                   (20)
  #define DDRDATA_CR_TXTRAINRANK1_TxEqualization_WID                   ( 6)
  #define DDRDATA_CR_TXTRAINRANK1_TxEqualization_MSK                   (0x03F00000)
  #define DDRDATA_CR_TXTRAINRANK1_TxEqualization_MIN                   (0)
  #define DDRDATA_CR_TXTRAINRANK1_TxEqualization_MAX                   (63) // 0x0000003F
  #define DDRDATA_CR_TXTRAINRANK1_TxEqualization_DEF                   (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK1_TxEqualization_HSH                   (0x06143624)

  #define DDRDATA_CR_TXTRAINRANK1_Spare1_OFF                           (26)
  #define DDRDATA_CR_TXTRAINRANK1_Spare1_WID                           ( 6)
  #define DDRDATA_CR_TXTRAINRANK1_Spare1_MSK                           (0xFC000000)
  #define DDRDATA_CR_TXTRAINRANK1_Spare1_MIN                           (0)
  #define DDRDATA_CR_TXTRAINRANK1_Spare1_MAX                           (63) // 0x0000003F
  #define DDRDATA_CR_TXTRAINRANK1_Spare1_DEF                           (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK1_Spare1_HSH                           (0x061A3624)

#define DDRDATA_CR_TXTRAINRANK2_REG                                    (0x00003628)

  #define DDRDATA_CR_TXTRAINRANK2_TxDqDelay_OFF                        ( 0)
  #define DDRDATA_CR_TXTRAINRANK2_TxDqDelay_WID                        ( 9)
  #define DDRDATA_CR_TXTRAINRANK2_TxDqDelay_MSK                        (0x000001FF)
  #define DDRDATA_CR_TXTRAINRANK2_TxDqDelay_MIN                        (0)
  #define DDRDATA_CR_TXTRAINRANK2_TxDqDelay_MAX                        (511) // 0x000001FF
  #define DDRDATA_CR_TXTRAINRANK2_TxDqDelay_DEF                        (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK2_TxDqDelay_HSH                        (0x09003628)

  #define DDRDATA_CR_TXTRAINRANK2_TxDqsDelay_OFF                       ( 9)
  #define DDRDATA_CR_TXTRAINRANK2_TxDqsDelay_WID                       ( 9)
  #define DDRDATA_CR_TXTRAINRANK2_TxDqsDelay_MSK                       (0x0003FE00)
  #define DDRDATA_CR_TXTRAINRANK2_TxDqsDelay_MIN                       (0)
  #define DDRDATA_CR_TXTRAINRANK2_TxDqsDelay_MAX                       (511) // 0x000001FF
  #define DDRDATA_CR_TXTRAINRANK2_TxDqsDelay_DEF                       (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK2_TxDqsDelay_HSH                       (0x09093628)

  #define DDRDATA_CR_TXTRAINRANK2_Spare0_OFF                           (18)
  #define DDRDATA_CR_TXTRAINRANK2_Spare0_WID                           ( 2)
  #define DDRDATA_CR_TXTRAINRANK2_Spare0_MSK                           (0x000C0000)
  #define DDRDATA_CR_TXTRAINRANK2_Spare0_MIN                           (0)
  #define DDRDATA_CR_TXTRAINRANK2_Spare0_MAX                           (3) // 0x00000003
  #define DDRDATA_CR_TXTRAINRANK2_Spare0_DEF                           (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK2_Spare0_HSH                           (0x02123628)

  #define DDRDATA_CR_TXTRAINRANK2_TxEqualization_OFF                   (20)
  #define DDRDATA_CR_TXTRAINRANK2_TxEqualization_WID                   ( 6)
  #define DDRDATA_CR_TXTRAINRANK2_TxEqualization_MSK                   (0x03F00000)
  #define DDRDATA_CR_TXTRAINRANK2_TxEqualization_MIN                   (0)
  #define DDRDATA_CR_TXTRAINRANK2_TxEqualization_MAX                   (63) // 0x0000003F
  #define DDRDATA_CR_TXTRAINRANK2_TxEqualization_DEF                   (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK2_TxEqualization_HSH                   (0x06143628)

  #define DDRDATA_CR_TXTRAINRANK2_Spare1_OFF                           (26)
  #define DDRDATA_CR_TXTRAINRANK2_Spare1_WID                           ( 6)
  #define DDRDATA_CR_TXTRAINRANK2_Spare1_MSK                           (0xFC000000)
  #define DDRDATA_CR_TXTRAINRANK2_Spare1_MIN                           (0)
  #define DDRDATA_CR_TXTRAINRANK2_Spare1_MAX                           (63) // 0x0000003F
  #define DDRDATA_CR_TXTRAINRANK2_Spare1_DEF                           (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK2_Spare1_HSH                           (0x061A3628)

#define DDRDATA_CR_TXTRAINRANK3_REG                                    (0x0000362C)

  #define DDRDATA_CR_TXTRAINRANK3_TxDqDelay_OFF                        ( 0)
  #define DDRDATA_CR_TXTRAINRANK3_TxDqDelay_WID                        ( 9)
  #define DDRDATA_CR_TXTRAINRANK3_TxDqDelay_MSK                        (0x000001FF)
  #define DDRDATA_CR_TXTRAINRANK3_TxDqDelay_MIN                        (0)
  #define DDRDATA_CR_TXTRAINRANK3_TxDqDelay_MAX                        (511) // 0x000001FF
  #define DDRDATA_CR_TXTRAINRANK3_TxDqDelay_DEF                        (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK3_TxDqDelay_HSH                        (0x0900362C)

  #define DDRDATA_CR_TXTRAINRANK3_TxDqsDelay_OFF                       ( 9)
  #define DDRDATA_CR_TXTRAINRANK3_TxDqsDelay_WID                       ( 9)
  #define DDRDATA_CR_TXTRAINRANK3_TxDqsDelay_MSK                       (0x0003FE00)
  #define DDRDATA_CR_TXTRAINRANK3_TxDqsDelay_MIN                       (0)
  #define DDRDATA_CR_TXTRAINRANK3_TxDqsDelay_MAX                       (511) // 0x000001FF
  #define DDRDATA_CR_TXTRAINRANK3_TxDqsDelay_DEF                       (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK3_TxDqsDelay_HSH                       (0x0909362C)

  #define DDRDATA_CR_TXTRAINRANK3_Spare0_OFF                           (18)
  #define DDRDATA_CR_TXTRAINRANK3_Spare0_WID                           ( 2)
  #define DDRDATA_CR_TXTRAINRANK3_Spare0_MSK                           (0x000C0000)
  #define DDRDATA_CR_TXTRAINRANK3_Spare0_MIN                           (0)
  #define DDRDATA_CR_TXTRAINRANK3_Spare0_MAX                           (3) // 0x00000003
  #define DDRDATA_CR_TXTRAINRANK3_Spare0_DEF                           (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK3_Spare0_HSH                           (0x0212362C)

  #define DDRDATA_CR_TXTRAINRANK3_TxEqualization_OFF                   (20)
  #define DDRDATA_CR_TXTRAINRANK3_TxEqualization_WID                   ( 6)
  #define DDRDATA_CR_TXTRAINRANK3_TxEqualization_MSK                   (0x03F00000)
  #define DDRDATA_CR_TXTRAINRANK3_TxEqualization_MIN                   (0)
  #define DDRDATA_CR_TXTRAINRANK3_TxEqualization_MAX                   (63) // 0x0000003F
  #define DDRDATA_CR_TXTRAINRANK3_TxEqualization_DEF                   (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK3_TxEqualization_HSH                   (0x0614362C)

  #define DDRDATA_CR_TXTRAINRANK3_Spare1_OFF                           (26)
  #define DDRDATA_CR_TXTRAINRANK3_Spare1_WID                           ( 6)
  #define DDRDATA_CR_TXTRAINRANK3_Spare1_MSK                           (0xFC000000)
  #define DDRDATA_CR_TXTRAINRANK3_Spare1_MIN                           (0)
  #define DDRDATA_CR_TXTRAINRANK3_Spare1_MAX                           (63) // 0x0000003F
  #define DDRDATA_CR_TXTRAINRANK3_Spare1_DEF                           (0x00000000)
  #define DDRDATA_CR_TXTRAINRANK3_Spare1_HSH                           (0x061A362C)

#define DDRDATA_CR_TXPERBITRANK0_REG                                   (0x00003630)

  #define DDRDATA_CR_TXPERBITRANK0_Lane0_OFF                           ( 0)
  #define DDRDATA_CR_TXPERBITRANK0_Lane0_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK0_Lane0_MSK                           (0x0000000F)
  #define DDRDATA_CR_TXPERBITRANK0_Lane0_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK0_Lane0_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK0_Lane0_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK0_Lane0_HSH                           (0x04003630)

  #define DDRDATA_CR_TXPERBITRANK0_Lane1_OFF                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK0_Lane1_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK0_Lane1_MSK                           (0x000000F0)
  #define DDRDATA_CR_TXPERBITRANK0_Lane1_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK0_Lane1_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK0_Lane1_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK0_Lane1_HSH                           (0x04043630)

  #define DDRDATA_CR_TXPERBITRANK0_Lane2_OFF                           ( 8)
  #define DDRDATA_CR_TXPERBITRANK0_Lane2_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK0_Lane2_MSK                           (0x00000F00)
  #define DDRDATA_CR_TXPERBITRANK0_Lane2_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK0_Lane2_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK0_Lane2_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK0_Lane2_HSH                           (0x04083630)

  #define DDRDATA_CR_TXPERBITRANK0_Lane3_OFF                           (12)
  #define DDRDATA_CR_TXPERBITRANK0_Lane3_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK0_Lane3_MSK                           (0x0000F000)
  #define DDRDATA_CR_TXPERBITRANK0_Lane3_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK0_Lane3_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK0_Lane3_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK0_Lane3_HSH                           (0x040C3630)

  #define DDRDATA_CR_TXPERBITRANK0_Lane4_OFF                           (16)
  #define DDRDATA_CR_TXPERBITRANK0_Lane4_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK0_Lane4_MSK                           (0x000F0000)
  #define DDRDATA_CR_TXPERBITRANK0_Lane4_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK0_Lane4_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK0_Lane4_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK0_Lane4_HSH                           (0x04103630)

  #define DDRDATA_CR_TXPERBITRANK0_Lane5_OFF                           (20)
  #define DDRDATA_CR_TXPERBITRANK0_Lane5_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK0_Lane5_MSK                           (0x00F00000)
  #define DDRDATA_CR_TXPERBITRANK0_Lane5_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK0_Lane5_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK0_Lane5_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK0_Lane5_HSH                           (0x04143630)

  #define DDRDATA_CR_TXPERBITRANK0_Lane6_OFF                           (24)
  #define DDRDATA_CR_TXPERBITRANK0_Lane6_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK0_Lane6_MSK                           (0x0F000000)
  #define DDRDATA_CR_TXPERBITRANK0_Lane6_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK0_Lane6_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK0_Lane6_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK0_Lane6_HSH                           (0x04183630)

  #define DDRDATA_CR_TXPERBITRANK0_Lane7_OFF                           (28)
  #define DDRDATA_CR_TXPERBITRANK0_Lane7_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK0_Lane7_MSK                           (0xF0000000)
  #define DDRDATA_CR_TXPERBITRANK0_Lane7_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK0_Lane7_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK0_Lane7_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK0_Lane7_HSH                           (0x041C3630)

#define DDRDATA_CR_TXPERBITRANK1_REG                                   (0x00003634)

  #define DDRDATA_CR_TXPERBITRANK1_Lane0_OFF                           ( 0)
  #define DDRDATA_CR_TXPERBITRANK1_Lane0_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK1_Lane0_MSK                           (0x0000000F)
  #define DDRDATA_CR_TXPERBITRANK1_Lane0_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK1_Lane0_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK1_Lane0_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK1_Lane0_HSH                           (0x04003634)

  #define DDRDATA_CR_TXPERBITRANK1_Lane1_OFF                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK1_Lane1_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK1_Lane1_MSK                           (0x000000F0)
  #define DDRDATA_CR_TXPERBITRANK1_Lane1_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK1_Lane1_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK1_Lane1_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK1_Lane1_HSH                           (0x04043634)

  #define DDRDATA_CR_TXPERBITRANK1_Lane2_OFF                           ( 8)
  #define DDRDATA_CR_TXPERBITRANK1_Lane2_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK1_Lane2_MSK                           (0x00000F00)
  #define DDRDATA_CR_TXPERBITRANK1_Lane2_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK1_Lane2_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK1_Lane2_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK1_Lane2_HSH                           (0x04083634)

  #define DDRDATA_CR_TXPERBITRANK1_Lane3_OFF                           (12)
  #define DDRDATA_CR_TXPERBITRANK1_Lane3_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK1_Lane3_MSK                           (0x0000F000)
  #define DDRDATA_CR_TXPERBITRANK1_Lane3_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK1_Lane3_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK1_Lane3_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK1_Lane3_HSH                           (0x040C3634)

  #define DDRDATA_CR_TXPERBITRANK1_Lane4_OFF                           (16)
  #define DDRDATA_CR_TXPERBITRANK1_Lane4_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK1_Lane4_MSK                           (0x000F0000)
  #define DDRDATA_CR_TXPERBITRANK1_Lane4_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK1_Lane4_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK1_Lane4_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK1_Lane4_HSH                           (0x04103634)

  #define DDRDATA_CR_TXPERBITRANK1_Lane5_OFF                           (20)
  #define DDRDATA_CR_TXPERBITRANK1_Lane5_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK1_Lane5_MSK                           (0x00F00000)
  #define DDRDATA_CR_TXPERBITRANK1_Lane5_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK1_Lane5_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK1_Lane5_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK1_Lane5_HSH                           (0x04143634)

  #define DDRDATA_CR_TXPERBITRANK1_Lane6_OFF                           (24)
  #define DDRDATA_CR_TXPERBITRANK1_Lane6_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK1_Lane6_MSK                           (0x0F000000)
  #define DDRDATA_CR_TXPERBITRANK1_Lane6_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK1_Lane6_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK1_Lane6_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK1_Lane6_HSH                           (0x04183634)

  #define DDRDATA_CR_TXPERBITRANK1_Lane7_OFF                           (28)
  #define DDRDATA_CR_TXPERBITRANK1_Lane7_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK1_Lane7_MSK                           (0xF0000000)
  #define DDRDATA_CR_TXPERBITRANK1_Lane7_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK1_Lane7_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK1_Lane7_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK1_Lane7_HSH                           (0x041C3634)

#define DDRDATA_CR_TXPERBITRANK2_REG                                   (0x00003638)

  #define DDRDATA_CR_TXPERBITRANK2_Lane0_OFF                           ( 0)
  #define DDRDATA_CR_TXPERBITRANK2_Lane0_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK2_Lane0_MSK                           (0x0000000F)
  #define DDRDATA_CR_TXPERBITRANK2_Lane0_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK2_Lane0_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK2_Lane0_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK2_Lane0_HSH                           (0x04003638)

  #define DDRDATA_CR_TXPERBITRANK2_Lane1_OFF                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK2_Lane1_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK2_Lane1_MSK                           (0x000000F0)
  #define DDRDATA_CR_TXPERBITRANK2_Lane1_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK2_Lane1_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK2_Lane1_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK2_Lane1_HSH                           (0x04043638)

  #define DDRDATA_CR_TXPERBITRANK2_Lane2_OFF                           ( 8)
  #define DDRDATA_CR_TXPERBITRANK2_Lane2_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK2_Lane2_MSK                           (0x00000F00)
  #define DDRDATA_CR_TXPERBITRANK2_Lane2_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK2_Lane2_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK2_Lane2_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK2_Lane2_HSH                           (0x04083638)

  #define DDRDATA_CR_TXPERBITRANK2_Lane3_OFF                           (12)
  #define DDRDATA_CR_TXPERBITRANK2_Lane3_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK2_Lane3_MSK                           (0x0000F000)
  #define DDRDATA_CR_TXPERBITRANK2_Lane3_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK2_Lane3_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK2_Lane3_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK2_Lane3_HSH                           (0x040C3638)

  #define DDRDATA_CR_TXPERBITRANK2_Lane4_OFF                           (16)
  #define DDRDATA_CR_TXPERBITRANK2_Lane4_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK2_Lane4_MSK                           (0x000F0000)
  #define DDRDATA_CR_TXPERBITRANK2_Lane4_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK2_Lane4_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK2_Lane4_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK2_Lane4_HSH                           (0x04103638)

  #define DDRDATA_CR_TXPERBITRANK2_Lane5_OFF                           (20)
  #define DDRDATA_CR_TXPERBITRANK2_Lane5_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK2_Lane5_MSK                           (0x00F00000)
  #define DDRDATA_CR_TXPERBITRANK2_Lane5_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK2_Lane5_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK2_Lane5_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK2_Lane5_HSH                           (0x04143638)

  #define DDRDATA_CR_TXPERBITRANK2_Lane6_OFF                           (24)
  #define DDRDATA_CR_TXPERBITRANK2_Lane6_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK2_Lane6_MSK                           (0x0F000000)
  #define DDRDATA_CR_TXPERBITRANK2_Lane6_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK2_Lane6_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK2_Lane6_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK2_Lane6_HSH                           (0x04183638)

  #define DDRDATA_CR_TXPERBITRANK2_Lane7_OFF                           (28)
  #define DDRDATA_CR_TXPERBITRANK2_Lane7_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK2_Lane7_MSK                           (0xF0000000)
  #define DDRDATA_CR_TXPERBITRANK2_Lane7_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK2_Lane7_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK2_Lane7_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK2_Lane7_HSH                           (0x041C3638)

#define DDRDATA_CR_TXPERBITRANK3_REG                                   (0x0000363C)

  #define DDRDATA_CR_TXPERBITRANK3_Lane0_OFF                           ( 0)
  #define DDRDATA_CR_TXPERBITRANK3_Lane0_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK3_Lane0_MSK                           (0x0000000F)
  #define DDRDATA_CR_TXPERBITRANK3_Lane0_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK3_Lane0_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK3_Lane0_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK3_Lane0_HSH                           (0x0400363C)

  #define DDRDATA_CR_TXPERBITRANK3_Lane1_OFF                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK3_Lane1_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK3_Lane1_MSK                           (0x000000F0)
  #define DDRDATA_CR_TXPERBITRANK3_Lane1_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK3_Lane1_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK3_Lane1_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK3_Lane1_HSH                           (0x0404363C)

  #define DDRDATA_CR_TXPERBITRANK3_Lane2_OFF                           ( 8)
  #define DDRDATA_CR_TXPERBITRANK3_Lane2_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK3_Lane2_MSK                           (0x00000F00)
  #define DDRDATA_CR_TXPERBITRANK3_Lane2_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK3_Lane2_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK3_Lane2_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK3_Lane2_HSH                           (0x0408363C)

  #define DDRDATA_CR_TXPERBITRANK3_Lane3_OFF                           (12)
  #define DDRDATA_CR_TXPERBITRANK3_Lane3_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK3_Lane3_MSK                           (0x0000F000)
  #define DDRDATA_CR_TXPERBITRANK3_Lane3_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK3_Lane3_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK3_Lane3_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK3_Lane3_HSH                           (0x040C363C)

  #define DDRDATA_CR_TXPERBITRANK3_Lane4_OFF                           (16)
  #define DDRDATA_CR_TXPERBITRANK3_Lane4_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK3_Lane4_MSK                           (0x000F0000)
  #define DDRDATA_CR_TXPERBITRANK3_Lane4_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK3_Lane4_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK3_Lane4_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK3_Lane4_HSH                           (0x0410363C)

  #define DDRDATA_CR_TXPERBITRANK3_Lane5_OFF                           (20)
  #define DDRDATA_CR_TXPERBITRANK3_Lane5_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK3_Lane5_MSK                           (0x00F00000)
  #define DDRDATA_CR_TXPERBITRANK3_Lane5_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK3_Lane5_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK3_Lane5_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK3_Lane5_HSH                           (0x0414363C)

  #define DDRDATA_CR_TXPERBITRANK3_Lane6_OFF                           (24)
  #define DDRDATA_CR_TXPERBITRANK3_Lane6_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK3_Lane6_MSK                           (0x0F000000)
  #define DDRDATA_CR_TXPERBITRANK3_Lane6_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK3_Lane6_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK3_Lane6_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK3_Lane6_HSH                           (0x0418363C)

  #define DDRDATA_CR_TXPERBITRANK3_Lane7_OFF                           (28)
  #define DDRDATA_CR_TXPERBITRANK3_Lane7_WID                           ( 4)
  #define DDRDATA_CR_TXPERBITRANK3_Lane7_MSK                           (0xF0000000)
  #define DDRDATA_CR_TXPERBITRANK3_Lane7_MIN                           (0)
  #define DDRDATA_CR_TXPERBITRANK3_Lane7_MAX                           (15) // 0x0000000F
  #define DDRDATA_CR_TXPERBITRANK3_Lane7_DEF                           (0x00000000)
  #define DDRDATA_CR_TXPERBITRANK3_Lane7_HSH                           (0x041C363C)

#define DDRDATA_CR_RCOMPDATA0_REG                                      (0x00003640)

  #define DDRDATA_CR_RCOMPDATA0_RcompDrvUp_OFF                         ( 0)
  #define DDRDATA_CR_RCOMPDATA0_RcompDrvUp_WID                         ( 6)
  #define DDRDATA_CR_RCOMPDATA0_RcompDrvUp_MSK                         (0x0000003F)
  #define DDRDATA_CR_RCOMPDATA0_RcompDrvUp_MIN                         (0)
  #define DDRDATA_CR_RCOMPDATA0_RcompDrvUp_MAX                         (63) // 0x0000003F
  #define DDRDATA_CR_RCOMPDATA0_RcompDrvUp_DEF                         (0x00000000)
  #define DDRDATA_CR_RCOMPDATA0_RcompDrvUp_HSH                         (0x06003640)

  #define DDRDATA_CR_RCOMPDATA0_Rsvd_OFF                               ( 6)
  #define DDRDATA_CR_RCOMPDATA0_Rsvd_WID                               ( 3)
  #define DDRDATA_CR_RCOMPDATA0_Rsvd_MSK                               (0x000001C0)
  #define DDRDATA_CR_RCOMPDATA0_Rsvd_MIN                               (0)
  #define DDRDATA_CR_RCOMPDATA0_Rsvd_MAX                               (7) // 0x00000007
  #define DDRDATA_CR_RCOMPDATA0_Rsvd_DEF                               (0x00000000)
  #define DDRDATA_CR_RCOMPDATA0_Rsvd_HSH                               (0x03063640)

  #define DDRDATA_CR_RCOMPDATA0_RcompDrvDown_OFF                       ( 9)
  #define DDRDATA_CR_RCOMPDATA0_RcompDrvDown_WID                       ( 6)
  #define DDRDATA_CR_RCOMPDATA0_RcompDrvDown_MSK                       (0x00007E00)
  #define DDRDATA_CR_RCOMPDATA0_RcompDrvDown_MIN                       (0)
  #define DDRDATA_CR_RCOMPDATA0_RcompDrvDown_MAX                       (63) // 0x0000003F
  #define DDRDATA_CR_RCOMPDATA0_RcompDrvDown_DEF                       (0x00000000)
  #define DDRDATA_CR_RCOMPDATA0_RcompDrvDown_HSH                       (0x06093640)

  #define DDRDATA_CR_RCOMPDATA0_VTComp_OFF                             (15)
  #define DDRDATA_CR_RCOMPDATA0_VTComp_WID                             ( 5)
  #define DDRDATA_CR_RCOMPDATA0_VTComp_MSK                             (0x000F8000)
  #define DDRDATA_CR_RCOMPDATA0_VTComp_MIN                             (0)
  #define DDRDATA_CR_RCOMPDATA0_VTComp_MAX                             (31) // 0x0000001F
  #define DDRDATA_CR_RCOMPDATA0_VTComp_DEF                             (0x00000000)
  #define DDRDATA_CR_RCOMPDATA0_VTComp_HSH                             (0x050F3640)

  #define DDRDATA_CR_RCOMPDATA0_SlewRateComp_OFF                       (20)
  #define DDRDATA_CR_RCOMPDATA0_SlewRateComp_WID                       ( 5)
  #define DDRDATA_CR_RCOMPDATA0_SlewRateComp_MSK                       (0x01F00000)
  #define DDRDATA_CR_RCOMPDATA0_SlewRateComp_MIN                       (0)
  #define DDRDATA_CR_RCOMPDATA0_SlewRateComp_MAX                       (31) // 0x0000001F
  #define DDRDATA_CR_RCOMPDATA0_SlewRateComp_DEF                       (0x00000000)
  #define DDRDATA_CR_RCOMPDATA0_SlewRateComp_HSH                       (0x05143640)

  #define DDRDATA_CR_RCOMPDATA0_Spare0_OFF                             (25)
  #define DDRDATA_CR_RCOMPDATA0_Spare0_WID                             ( 1)
  #define DDRDATA_CR_RCOMPDATA0_Spare0_MSK                             (0x02000000)
  #define DDRDATA_CR_RCOMPDATA0_Spare0_MIN                             (0)
  #define DDRDATA_CR_RCOMPDATA0_Spare0_MAX                             (1) // 0x00000001
  #define DDRDATA_CR_RCOMPDATA0_Spare0_DEF                             (0x00000000)
  #define DDRDATA_CR_RCOMPDATA0_Spare0_HSH                             (0x01193640)

  #define DDRDATA_CR_RCOMPDATA0_TcoComp_OFF                            (26)
  #define DDRDATA_CR_RCOMPDATA0_TcoComp_WID                            ( 6)
  #define DDRDATA_CR_RCOMPDATA0_TcoComp_MSK                            (0xFC000000)
  #define DDRDATA_CR_RCOMPDATA0_TcoComp_MIN                            (0)
  #define DDRDATA_CR_RCOMPDATA0_TcoComp_MAX                            (63) // 0x0000003F
  #define DDRDATA_CR_RCOMPDATA0_TcoComp_DEF                            (0x00000000)
  #define DDRDATA_CR_RCOMPDATA0_TcoComp_HSH                            (0x061A3640)

#define DDRDATA_CR_RCOMPDATA1_REG                                      (0x00003644)

  #define DDRDATA_CR_RCOMPDATA1_RcompOdtUp_OFF                         ( 0)
  #define DDRDATA_CR_RCOMPDATA1_RcompOdtUp_WID                         ( 6)
  #define DDRDATA_CR_RCOMPDATA1_RcompOdtUp_MSK                         (0x0000003F)
  #define DDRDATA_CR_RCOMPDATA1_RcompOdtUp_MIN                         (0)
  #define DDRDATA_CR_RCOMPDATA1_RcompOdtUp_MAX                         (63) // 0x0000003F
  #define DDRDATA_CR_RCOMPDATA1_RcompOdtUp_DEF                         (0x00000000)
  #define DDRDATA_CR_RCOMPDATA1_RcompOdtUp_HSH                         (0x06003644)

  #define DDRDATA_CR_RCOMPDATA1_PanicDrvDn_OFF                         ( 6)
  #define DDRDATA_CR_RCOMPDATA1_PanicDrvDn_WID                         (10)
  #define DDRDATA_CR_RCOMPDATA1_PanicDrvDn_MSK                         (0x0000FFC0)
  #define DDRDATA_CR_RCOMPDATA1_PanicDrvDn_MIN                         (0)
  #define DDRDATA_CR_RCOMPDATA1_PanicDrvDn_MAX                         (1023) // 0x000003FF
  #define DDRDATA_CR_RCOMPDATA1_PanicDrvDn_DEF                         (0x00000000)
  #define DDRDATA_CR_RCOMPDATA1_PanicDrvDn_HSH                         (0x0A063644)

  #define DDRDATA_CR_RCOMPDATA1_PanicDrvUp_OFF                         (16)
  #define DDRDATA_CR_RCOMPDATA1_PanicDrvUp_WID                         (10)
  #define DDRDATA_CR_RCOMPDATA1_PanicDrvUp_MSK                         (0x03FF0000)
  #define DDRDATA_CR_RCOMPDATA1_PanicDrvUp_MIN                         (0)
  #define DDRDATA_CR_RCOMPDATA1_PanicDrvUp_MAX                         (1023) // 0x000003FF
  #define DDRDATA_CR_RCOMPDATA1_PanicDrvUp_DEF                         (0x00000000)
  #define DDRDATA_CR_RCOMPDATA1_PanicDrvUp_HSH                         (0x0A103644)

  #define DDRDATA_CR_RCOMPDATA1_RcompOdtDown_OFF                       (26)
  #define DDRDATA_CR_RCOMPDATA1_RcompOdtDown_WID                       ( 6)
  #define DDRDATA_CR_RCOMPDATA1_RcompOdtDown_MSK                       (0xFC000000)
  #define DDRDATA_CR_RCOMPDATA1_RcompOdtDown_MIN                       (0)
  #define DDRDATA_CR_RCOMPDATA1_RcompOdtDown_MAX                       (63) // 0x0000003F
  #define DDRDATA_CR_RCOMPDATA1_RcompOdtDown_DEF                       (0x00000000)
  #define DDRDATA_CR_RCOMPDATA1_RcompOdtDown_HSH                       (0x061A3644)

#define DDRDATA_CR_TXXTALK_REG                                         (0x00003648)

  #define DDRDATA_CR_TXXTALK_Lane0_OFF                                 ( 0)
  #define DDRDATA_CR_TXXTALK_Lane0_WID                                 ( 4)
  #define DDRDATA_CR_TXXTALK_Lane0_MSK                                 (0x0000000F)
  #define DDRDATA_CR_TXXTALK_Lane0_MIN                                 (-8)
  #define DDRDATA_CR_TXXTALK_Lane0_MAX                                 (7) // 0x00000007
  #define DDRDATA_CR_TXXTALK_Lane0_DEF                                 (0x00000000)
  #define DDRDATA_CR_TXXTALK_Lane0_HSH                                 (0x84003648)

  #define DDRDATA_CR_TXXTALK_Lane1_OFF                                 ( 4)
  #define DDRDATA_CR_TXXTALK_Lane1_WID                                 ( 4)
  #define DDRDATA_CR_TXXTALK_Lane1_MSK                                 (0x000000F0)
  #define DDRDATA_CR_TXXTALK_Lane1_MIN                                 (-8)
  #define DDRDATA_CR_TXXTALK_Lane1_MAX                                 (7) // 0x00000007
  #define DDRDATA_CR_TXXTALK_Lane1_DEF                                 (0x00000000)
  #define DDRDATA_CR_TXXTALK_Lane1_HSH                                 (0x84043648)

  #define DDRDATA_CR_TXXTALK_Lane2_OFF                                 ( 8)
  #define DDRDATA_CR_TXXTALK_Lane2_WID                                 ( 4)
  #define DDRDATA_CR_TXXTALK_Lane2_MSK                                 (0x00000F00)
  #define DDRDATA_CR_TXXTALK_Lane2_MIN                                 (-8)
  #define DDRDATA_CR_TXXTALK_Lane2_MAX                                 (7) // 0x00000007
  #define DDRDATA_CR_TXXTALK_Lane2_DEF                                 (0x00000000)
  #define DDRDATA_CR_TXXTALK_Lane2_HSH                                 (0x84083648)

  #define DDRDATA_CR_TXXTALK_Lane3_OFF                                 (12)
  #define DDRDATA_CR_TXXTALK_Lane3_WID                                 ( 4)
  #define DDRDATA_CR_TXXTALK_Lane3_MSK                                 (0x0000F000)
  #define DDRDATA_CR_TXXTALK_Lane3_MIN                                 (-8)
  #define DDRDATA_CR_TXXTALK_Lane3_MAX                                 (7) // 0x00000007
  #define DDRDATA_CR_TXXTALK_Lane3_DEF                                 (0x00000000)
  #define DDRDATA_CR_TXXTALK_Lane3_HSH                                 (0x840C3648)

  #define DDRDATA_CR_TXXTALK_Lane4_OFF                                 (16)
  #define DDRDATA_CR_TXXTALK_Lane4_WID                                 ( 4)
  #define DDRDATA_CR_TXXTALK_Lane4_MSK                                 (0x000F0000)
  #define DDRDATA_CR_TXXTALK_Lane4_MIN                                 (-8)
  #define DDRDATA_CR_TXXTALK_Lane4_MAX                                 (7) // 0x00000007
  #define DDRDATA_CR_TXXTALK_Lane4_DEF                                 (0x00000000)
  #define DDRDATA_CR_TXXTALK_Lane4_HSH                                 (0x84103648)

  #define DDRDATA_CR_TXXTALK_Lane5_OFF                                 (20)
  #define DDRDATA_CR_TXXTALK_Lane5_WID                                 ( 4)
  #define DDRDATA_CR_TXXTALK_Lane5_MSK                                 (0x00F00000)
  #define DDRDATA_CR_TXXTALK_Lane5_MIN                                 (-8)
  #define DDRDATA_CR_TXXTALK_Lane5_MAX                                 (7) // 0x00000007
  #define DDRDATA_CR_TXXTALK_Lane5_DEF                                 (0x00000000)
  #define DDRDATA_CR_TXXTALK_Lane5_HSH                                 (0x84143648)

  #define DDRDATA_CR_TXXTALK_Lane6_OFF                                 (24)
  #define DDRDATA_CR_TXXTALK_Lane6_WID                                 ( 4)
  #define DDRDATA_CR_TXXTALK_Lane6_MSK                                 (0x0F000000)
  #define DDRDATA_CR_TXXTALK_Lane6_MIN                                 (-8)
  #define DDRDATA_CR_TXXTALK_Lane6_MAX                                 (7) // 0x00000007
  #define DDRDATA_CR_TXXTALK_Lane6_DEF                                 (0x00000000)
  #define DDRDATA_CR_TXXTALK_Lane6_HSH                                 (0x84183648)

  #define DDRDATA_CR_TXXTALK_Lane7_OFF                                 (28)
  #define DDRDATA_CR_TXXTALK_Lane7_WID                                 ( 4)
  #define DDRDATA_CR_TXXTALK_Lane7_MSK                                 (0xF0000000)
  #define DDRDATA_CR_TXXTALK_Lane7_MIN                                 (-8)
  #define DDRDATA_CR_TXXTALK_Lane7_MAX                                 (7) // 0x00000007
  #define DDRDATA_CR_TXXTALK_Lane7_DEF                                 (0x00000000)
  #define DDRDATA_CR_TXXTALK_Lane7_HSH                                 (0x841C3648)

#define DDRDATA_CR_RCOMPDATA2_REG                                      (0x0000364C)

  #define DDRDATA_CR_RCOMPDATA2_VttPanicUp_OFF                         ( 0)
  #define DDRDATA_CR_RCOMPDATA2_VttPanicUp_WID                         ( 8)
  #define DDRDATA_CR_RCOMPDATA2_VttPanicUp_MSK                         (0x000000FF)
  #define DDRDATA_CR_RCOMPDATA2_VttPanicUp_MIN                         (0)
  #define DDRDATA_CR_RCOMPDATA2_VttPanicUp_MAX                         (255) // 0x000000FF
  #define DDRDATA_CR_RCOMPDATA2_VttPanicUp_DEF                         (0x00000000)
  #define DDRDATA_CR_RCOMPDATA2_VttPanicUp_HSH                         (0x0800364C)

  #define DDRDATA_CR_RCOMPDATA2_VttPanicDn_OFF                         ( 8)
  #define DDRDATA_CR_RCOMPDATA2_VttPanicDn_WID                         ( 8)
  #define DDRDATA_CR_RCOMPDATA2_VttPanicDn_MSK                         (0x0000FF00)
  #define DDRDATA_CR_RCOMPDATA2_VttPanicDn_MIN                         (0)
  #define DDRDATA_CR_RCOMPDATA2_VttPanicDn_MAX                         (255) // 0x000000FF
  #define DDRDATA_CR_RCOMPDATA2_VttPanicDn_DEF                         (0x00000000)
  #define DDRDATA_CR_RCOMPDATA2_VttPanicDn_HSH                         (0x0808364C)

  #define DDRDATA_CR_RCOMPDATA2_Spare_OFF                              (16)
  #define DDRDATA_CR_RCOMPDATA2_Spare_WID                              (16)
  #define DDRDATA_CR_RCOMPDATA2_Spare_MSK                              (0xFFFF0000)
  #define DDRDATA_CR_RCOMPDATA2_Spare_MIN                              (0)
  #define DDRDATA_CR_RCOMPDATA2_Spare_MAX                              (65535) // 0x0000FFFF
  #define DDRDATA_CR_RCOMPDATA2_Spare_DEF                              (0x00000000)
  #define DDRDATA_CR_RCOMPDATA2_Spare_HSH                              (0x1010364C)

#define DDRDATA_CR_RXOFFSETVDQRANK0_REG                                (0x00003650)

  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane0_OFF                        ( 0)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane0_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane0_MSK                        (0x0000000F)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane0_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane0_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane0_HSH                        (0x04003650)

  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane1_OFF                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane1_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane1_MSK                        (0x000000F0)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane1_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane1_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane1_HSH                        (0x04043650)

  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane2_OFF                        ( 8)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane2_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane2_MSK                        (0x00000F00)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane2_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane2_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane2_HSH                        (0x04083650)

  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane3_OFF                        (12)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane3_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane3_MSK                        (0x0000F000)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane3_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane3_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane3_HSH                        (0x040C3650)

  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane4_OFF                        (16)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane4_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane4_MSK                        (0x000F0000)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane4_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane4_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane4_HSH                        (0x04103650)

  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane5_OFF                        (20)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane5_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane5_MSK                        (0x00F00000)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane5_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane5_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane5_HSH                        (0x04143650)

  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane6_OFF                        (24)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane6_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane6_MSK                        (0x0F000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane6_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane6_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane6_HSH                        (0x04183650)

  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane7_OFF                        (28)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane7_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane7_MSK                        (0xF0000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane7_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane7_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK0_Lane7_HSH                        (0x041C3650)

#define DDRDATA_CR_RXOFFSETVDQRANK1_REG                                (0x00003654)

  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane0_OFF                        ( 0)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane0_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane0_MSK                        (0x0000000F)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane0_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane0_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane0_HSH                        (0x04003654)

  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane1_OFF                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane1_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane1_MSK                        (0x000000F0)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane1_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane1_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane1_HSH                        (0x04043654)

  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane2_OFF                        ( 8)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane2_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane2_MSK                        (0x00000F00)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane2_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane2_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane2_HSH                        (0x04083654)

  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane3_OFF                        (12)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane3_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane3_MSK                        (0x0000F000)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane3_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane3_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane3_HSH                        (0x040C3654)

  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane4_OFF                        (16)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane4_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane4_MSK                        (0x000F0000)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane4_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane4_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane4_HSH                        (0x04103654)

  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane5_OFF                        (20)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane5_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane5_MSK                        (0x00F00000)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane5_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane5_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane5_HSH                        (0x04143654)

  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane6_OFF                        (24)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane6_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane6_MSK                        (0x0F000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane6_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane6_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane6_HSH                        (0x04183654)

  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane7_OFF                        (28)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane7_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane7_MSK                        (0xF0000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane7_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane7_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK1_Lane7_HSH                        (0x041C3654)

#define DDRDATA_CR_RXOFFSETVDQRANK2_REG                                (0x00003658)

  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane0_OFF                        ( 0)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane0_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane0_MSK                        (0x0000000F)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane0_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane0_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane0_HSH                        (0x04003658)

  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane1_OFF                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane1_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane1_MSK                        (0x000000F0)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane1_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane1_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane1_HSH                        (0x04043658)

  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane2_OFF                        ( 8)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane2_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane2_MSK                        (0x00000F00)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane2_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane2_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane2_HSH                        (0x04083658)

  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane3_OFF                        (12)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane3_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane3_MSK                        (0x0000F000)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane3_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane3_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane3_HSH                        (0x040C3658)

  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane4_OFF                        (16)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane4_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane4_MSK                        (0x000F0000)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane4_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane4_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane4_HSH                        (0x04103658)

  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane5_OFF                        (20)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane5_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane5_MSK                        (0x00F00000)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane5_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane5_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane5_HSH                        (0x04143658)

  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane6_OFF                        (24)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane6_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane6_MSK                        (0x0F000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane6_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane6_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane6_HSH                        (0x04183658)

  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane7_OFF                        (28)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane7_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane7_MSK                        (0xF0000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane7_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane7_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK2_Lane7_HSH                        (0x041C3658)

#define DDRDATA_CR_RXOFFSETVDQRANK3_REG                                (0x0000365C)

  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane0_OFF                        ( 0)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane0_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane0_MSK                        (0x0000000F)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane0_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane0_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane0_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane0_HSH                        (0x0400365C)

  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane1_OFF                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane1_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane1_MSK                        (0x000000F0)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane1_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane1_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane1_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane1_HSH                        (0x0404365C)

  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane2_OFF                        ( 8)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane2_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane2_MSK                        (0x00000F00)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane2_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane2_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane2_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane2_HSH                        (0x0408365C)

  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane3_OFF                        (12)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane3_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane3_MSK                        (0x0000F000)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane3_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane3_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane3_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane3_HSH                        (0x040C365C)

  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane4_OFF                        (16)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane4_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane4_MSK                        (0x000F0000)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane4_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane4_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane4_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane4_HSH                        (0x0410365C)

  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane5_OFF                        (20)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane5_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane5_MSK                        (0x00F00000)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane5_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane5_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane5_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane5_HSH                        (0x0414365C)

  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane6_OFF                        (24)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane6_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane6_MSK                        (0x0F000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane6_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane6_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane6_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane6_HSH                        (0x0418365C)

  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane7_OFF                        (28)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane7_WID                        ( 4)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane7_MSK                        (0xF0000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane7_MIN                        (0)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane7_MAX                        (15) // 0x0000000F
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane7_DEF                        (0x00000000)
  #define DDRDATA_CR_RXOFFSETVDQRANK3_Lane7_HSH                        (0x041C365C)

#define DDRDATA_CR_DATATRAINFEEDBACK_REG                               (0x00003660)

  #define DDRDATA_CR_DATATRAINFEEDBACK_DataTrainFeedback_OFF           ( 0)
  #define DDRDATA_CR_DATATRAINFEEDBACK_DataTrainFeedback_WID           ( 9)
  #define DDRDATA_CR_DATATRAINFEEDBACK_DataTrainFeedback_MSK           (0x000001FF)
  #define DDRDATA_CR_DATATRAINFEEDBACK_DataTrainFeedback_MIN           (0)
  #define DDRDATA_CR_DATATRAINFEEDBACK_DataTrainFeedback_MAX           (511) // 0x000001FF
  #define DDRDATA_CR_DATATRAINFEEDBACK_DataTrainFeedback_DEF           (0x00000000)
  #define DDRDATA_CR_DATATRAINFEEDBACK_DataTrainFeedback_HSH           (0x09003660)

  #define DDRDATA_CR_DATATRAINFEEDBACK_Spare_OFF                       ( 9)
  #define DDRDATA_CR_DATATRAINFEEDBACK_Spare_WID                       (23)
  #define DDRDATA_CR_DATATRAINFEEDBACK_Spare_MSK                       (0xFFFFFE00)
  #define DDRDATA_CR_DATATRAINFEEDBACK_Spare_MIN                       (0)
  #define DDRDATA_CR_DATATRAINFEEDBACK_Spare_MAX                       (8388607) // 0x007FFFFF
  #define DDRDATA_CR_DATATRAINFEEDBACK_Spare_DEF                       (0x00000000)
  #define DDRDATA_CR_DATATRAINFEEDBACK_Spare_HSH                       (0x17093660)

#define DDRDATA_CR_DLLPITESTANDADC_REG                                 (0x00003664)

  #define DDRDATA_CR_DLLPITESTANDADC_RunTest_OFF                       ( 0)
  #define DDRDATA_CR_DLLPITESTANDADC_RunTest_WID                       ( 1)
  #define DDRDATA_CR_DLLPITESTANDADC_RunTest_MSK                       (0x00000001)
  #define DDRDATA_CR_DLLPITESTANDADC_RunTest_MIN                       (0)
  #define DDRDATA_CR_DLLPITESTANDADC_RunTest_MAX                       (1) // 0x00000001
  #define DDRDATA_CR_DLLPITESTANDADC_RunTest_DEF                       (0x00000000)
  #define DDRDATA_CR_DLLPITESTANDADC_RunTest_HSH                       (0x01003664)

  #define DDRDATA_CR_DLLPITESTANDADC_Load_OFF                          ( 1)
  #define DDRDATA_CR_DLLPITESTANDADC_Load_WID                          ( 1)
  #define DDRDATA_CR_DLLPITESTANDADC_Load_MSK                          (0x00000002)
  #define DDRDATA_CR_DLLPITESTANDADC_Load_MIN                          (0)
  #define DDRDATA_CR_DLLPITESTANDADC_Load_MAX                          (1) // 0x00000001
  #define DDRDATA_CR_DLLPITESTANDADC_Load_DEF                          (0x00000000)
  #define DDRDATA_CR_DLLPITESTANDADC_Load_HSH                          (0x01013664)

  #define DDRDATA_CR_DLLPITESTANDADC_ModeHVM_OFF                       ( 2)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeHVM_WID                       ( 1)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeHVM_MSK                       (0x00000004)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeHVM_MIN                       (0)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeHVM_MAX                       (1) // 0x00000001
  #define DDRDATA_CR_DLLPITESTANDADC_ModeHVM_DEF                       (0x00000000)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeHVM_HSH                       (0x01023664)

  #define DDRDATA_CR_DLLPITESTANDADC_ModeDV_OFF                        ( 3)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeDV_WID                        ( 1)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeDV_MSK                        (0x00000008)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeDV_MIN                        (0)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeDV_MAX                        (1) // 0x00000001
  #define DDRDATA_CR_DLLPITESTANDADC_ModeDV_DEF                        (0x00000000)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeDV_HSH                        (0x01033664)

  #define DDRDATA_CR_DLLPITESTANDADC_CalCfdl_OFF                       ( 4)
  #define DDRDATA_CR_DLLPITESTANDADC_CalCfdl_WID                       ( 1)
  #define DDRDATA_CR_DLLPITESTANDADC_CalCfdl_MSK                       (0x00000010)
  #define DDRDATA_CR_DLLPITESTANDADC_CalCfdl_MIN                       (0)
  #define DDRDATA_CR_DLLPITESTANDADC_CalCfdl_MAX                       (1) // 0x00000001
  #define DDRDATA_CR_DLLPITESTANDADC_CalCfdl_DEF                       (0x00000000)
  #define DDRDATA_CR_DLLPITESTANDADC_CalCfdl_HSH                       (0x01043664)

  #define DDRDATA_CR_DLLPITESTANDADC_LoadCount_OFF                     ( 5)
  #define DDRDATA_CR_DLLPITESTANDADC_LoadCount_WID                     (10)
  #define DDRDATA_CR_DLLPITESTANDADC_LoadCount_MSK                     (0x00007FE0)
  #define DDRDATA_CR_DLLPITESTANDADC_LoadCount_MIN                     (0)
  #define DDRDATA_CR_DLLPITESTANDADC_LoadCount_MAX                     (1023) // 0x000003FF
  #define DDRDATA_CR_DLLPITESTANDADC_LoadCount_DEF                     (0x00000000)
  #define DDRDATA_CR_DLLPITESTANDADC_LoadCount_HSH                     (0x0A053664)

  #define DDRDATA_CR_DLLPITESTANDADC_CountStatus_OFF                   (15)
  #define DDRDATA_CR_DLLPITESTANDADC_CountStatus_WID                   (10)
  #define DDRDATA_CR_DLLPITESTANDADC_CountStatus_MSK                   (0x01FF8000)
  #define DDRDATA_CR_DLLPITESTANDADC_CountStatus_MIN                   (0)
  #define DDRDATA_CR_DLLPITESTANDADC_CountStatus_MAX                   (1023) // 0x000003FF
  #define DDRDATA_CR_DLLPITESTANDADC_CountStatus_DEF                   (0x00000000)
  #define DDRDATA_CR_DLLPITESTANDADC_CountStatus_HSH                   (0x0A0F3664)

  #define DDRDATA_CR_DLLPITESTANDADC_ModeADC_OFF                       (25)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeADC_WID                       ( 1)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeADC_MSK                       (0x02000000)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeADC_MIN                       (0)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeADC_MAX                       (1) // 0x00000001
  #define DDRDATA_CR_DLLPITESTANDADC_ModeADC_DEF                       (0x00000000)
  #define DDRDATA_CR_DLLPITESTANDADC_ModeADC_HSH                       (0x01193664)

  #define DDRDATA_CR_DLLPITESTANDADC_ADCClkDiv_OFF                     (26)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCClkDiv_WID                     ( 2)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCClkDiv_MSK                     (0x0C000000)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCClkDiv_MIN                     (0)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCClkDiv_MAX                     (3) // 0x00000003
  #define DDRDATA_CR_DLLPITESTANDADC_ADCClkDiv_DEF                     (0x00000000)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCClkDiv_HSH                     (0x021A3664)

  #define DDRDATA_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                 (28)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                 ( 1)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                 (0x10000000)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                 (0)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                 (1) // 0x00000001
  #define DDRDATA_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                 (0x00000000)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                 (0x011C3664)

  #define DDRDATA_CR_DLLPITESTANDADC_ADCChopEn_OFF                     (29)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCChopEn_WID                     ( 1)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCChopEn_MSK                     (0x20000000)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCChopEn_MIN                     (0)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCChopEn_MAX                     (1) // 0x00000001
  #define DDRDATA_CR_DLLPITESTANDADC_ADCChopEn_DEF                     (0x00000000)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCChopEn_HSH                     (0x011D3664)

  #define DDRDATA_CR_DLLPITESTANDADC_ADCDone_OFF                       (30)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCDone_WID                       ( 1)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCDone_MSK                       (0x40000000)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCDone_MIN                       (0)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCDone_MAX                       (1) // 0x00000001
  #define DDRDATA_CR_DLLPITESTANDADC_ADCDone_DEF                       (0x00000000)
  #define DDRDATA_CR_DLLPITESTANDADC_ADCDone_HSH                       (0x011E3664)

  #define DDRDATA_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF              (31)
  #define DDRDATA_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID              ( 1)
  #define DDRDATA_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK              (0x80000000)
  #define DDRDATA_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN              (0)
  #define DDRDATA_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX              (1) // 0x00000001
  #define DDRDATA_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF              (0x00000000)
  #define DDRDATA_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH              (0x011F3664)

#define DDRDATA_CR_DDRCRDATAOFFSETCOMP_REG                             (0x00003668)

  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_OFF         ( 0)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_WID         ( 6)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MSK         (0x0000003F)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MIN         (-32)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MAX         (31) // 0x0000001F
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_DEF         (0x00000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_HSH         (0x86003668)

  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_OFF       ( 6)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_WID       ( 6)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MSK       (0x00000FC0)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MIN       (-32)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MAX       (31) // 0x0000001F
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_DEF       (0x00000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_HSH       (0x86063668)

  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_OFF         (12)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_WID         ( 5)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MSK         (0x0001F000)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MIN         (-16)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MAX         (15) // 0x0000000F
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_DEF         (0x00000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_HSH         (0x850C3668)

  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_OFF       (17)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_WID       ( 5)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MSK       (0x003E0000)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MIN       (-16)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MAX       (15) // 0x0000000F
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_DEF       (0x00000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_HSH       (0x85113668)

  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_OFF           (22)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_WID           ( 5)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MSK           (0x07C00000)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MIN           (-16)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MAX           (15) // 0x0000000F
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_DEF           (0x00000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_HSH           (0x85163668)

  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_OFF      (27)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_WID      ( 5)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MSK      (0xF8000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MIN      (-16)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MAX      (15) // 0x0000000F
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_DEF      (0x00000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_HSH      (0x851B3668)

#define DDRDATA_CR_DDRCRDATACONTROL1_REG                               (0x0000366C)

  #define DDRDATA_CR_DDRCRDATACONTROL1_RefPi_OFF                       ( 0)
  #define DDRDATA_CR_DDRCRDATACONTROL1_RefPi_WID                       ( 4)
  #define DDRDATA_CR_DDRCRDATACONTROL1_RefPi_MSK                       (0x0000000F)
  #define DDRDATA_CR_DDRCRDATACONTROL1_RefPi_MIN                       (-8)
  #define DDRDATA_CR_DDRCRDATACONTROL1_RefPi_MAX                       (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL1_RefPi_DEF                       (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_RefPi_HSH                       (0x8400366C)

  #define DDRDATA_CR_DDRCRDATACONTROL1_DllMask_OFF                     ( 4)
  #define DDRDATA_CR_DDRCRDATACONTROL1_DllMask_WID                     ( 2)
  #define DDRDATA_CR_DDRCRDATACONTROL1_DllMask_MSK                     (0x00000030)
  #define DDRDATA_CR_DDRCRDATACONTROL1_DllMask_MIN                     (0)
  #define DDRDATA_CR_DDRCRDATACONTROL1_DllMask_MAX                     (3) // 0x00000003
  #define DDRDATA_CR_DDRCRDATACONTROL1_DllMask_DEF                     (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_DllMask_HSH                     (0x0204366C)

  #define DDRDATA_CR_DDRCRDATACONTROL1_DllWeakLock_OFF                 ( 6)
  #define DDRDATA_CR_DDRCRDATACONTROL1_DllWeakLock_WID                 ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL1_DllWeakLock_MSK                 (0x00000040)
  #define DDRDATA_CR_DDRCRDATACONTROL1_DllWeakLock_MIN                 (0)
  #define DDRDATA_CR_DDRCRDATACONTROL1_DllWeakLock_MAX                 (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL1_DllWeakLock_DEF                 (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_DllWeakLock_HSH                 (0x0106366C)

  #define DDRDATA_CR_DDRCRDATACONTROL1_SdllSegmentDisable_OFF          ( 7)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SdllSegmentDisable_WID          ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MSK          (0x00000380)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MIN          (0)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MAX          (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL1_SdllSegmentDisable_DEF          (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SdllSegmentDisable_HSH          (0x0307366C)

  #define DDRDATA_CR_DDRCRDATACONTROL1_RxBiasCtl_OFF                   (10)
  #define DDRDATA_CR_DDRCRDATACONTROL1_RxBiasCtl_WID                   ( 4)
  #define DDRDATA_CR_DDRCRDATACONTROL1_RxBiasCtl_MSK                   (0x00003C00)
  #define DDRDATA_CR_DDRCRDATACONTROL1_RxBiasCtl_MIN                   (0)
  #define DDRDATA_CR_DDRCRDATACONTROL1_RxBiasCtl_MAX                   (15) // 0x0000000F
  #define DDRDATA_CR_DDRCRDATACONTROL1_RxBiasCtl_DEF                   (0x00000008)
  #define DDRDATA_CR_DDRCRDATACONTROL1_RxBiasCtl_HSH                   (0x040A366C)

  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDelay_OFF                    (14)
  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDelay_WID                    ( 4)
  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDelay_MSK                    (0x0003C000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDelay_MIN                    (-8)
  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDelay_MAX                    (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDelay_DEF                    (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDelay_HSH                    (0x840E366C)

  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDuration_OFF                 (18)
  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDuration_WID                 ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDuration_MSK                 (0x001C0000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDuration_MIN                 (0)
  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDuration_MAX                 (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDuration_DEF                 (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_OdtDuration_HSH                 (0x0312366C)

  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDelay_OFF               (21)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDelay_WID               ( 4)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDelay_MSK               (0x01E00000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDelay_MIN               (-8)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDelay_MAX               (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDelay_DEF               (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDelay_HSH               (0x8415366C)

  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDuration_OFF            (25)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDuration_WID            ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDuration_MSK            (0x0E000000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDuration_MIN            (0)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDuration_MAX            (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDuration_DEF            (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_SenseAmpDuration_HSH            (0x0319366C)

  #define DDRDATA_CR_DDRCRDATACONTROL1_StrongWkLeaker_OFF              (28)
  #define DDRDATA_CR_DDRCRDATACONTROL1_StrongWkLeaker_WID              ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL1_StrongWkLeaker_MSK              (0x70000000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_StrongWkLeaker_MIN              (0)
  #define DDRDATA_CR_DDRCRDATACONTROL1_StrongWkLeaker_MAX              (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL1_StrongWkLeaker_DEF              (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_StrongWkLeaker_HSH              (0x031C366C)

  #define DDRDATA_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_OFF              (31)
  #define DDRDATA_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_WID              ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MSK              (0x80000000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MIN              (0)
  #define DDRDATA_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MAX              (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_DEF              (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_HSH              (0x011F366C)

#define DDRDATA_CR_DDRCRDATACONTROL2_REG                               (0x00003670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_RxStaggerCtl_OFF                ( 0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxStaggerCtl_WID                ( 5)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxStaggerCtl_MSK                (0x0000001F)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxStaggerCtl_MIN                (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxStaggerCtl_MAX                (31) // 0x0000001F
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxStaggerCtl_DEF                (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxStaggerCtl_HSH                (0x05003670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceBiasOn_OFF                 ( 5)
  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceBiasOn_WID                 ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceBiasOn_MSK                 (0x00000020)
  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceBiasOn_MIN                 (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceBiasOn_MAX                 (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceBiasOn_DEF                 (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceBiasOn_HSH                 (0x01053670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceRxOn_OFF                   ( 6)
  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceRxOn_WID                   ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceRxOn_MSK                   (0x00000040)
  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceRxOn_MIN                   (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceRxOn_MAX                   (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceRxOn_DEF                   (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_ForceRxOn_HSH                   (0x01063670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_LeakerComp_OFF                  ( 7)
  #define DDRDATA_CR_DDRCRDATACONTROL2_LeakerComp_WID                  ( 2)
  #define DDRDATA_CR_DDRCRDATACONTROL2_LeakerComp_MSK                  (0x00000180)
  #define DDRDATA_CR_DDRCRDATACONTROL2_LeakerComp_MIN                  (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_LeakerComp_MAX                  (3) // 0x00000003
  #define DDRDATA_CR_DDRCRDATACONTROL2_LeakerComp_DEF                  (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_LeakerComp_HSH                  (0x02073670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_OFF              ( 9)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_WID              ( 4)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MSK              (0x00001E00)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MIN              (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MAX              (15) // 0x0000000F
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_DEF              (0x00000008)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_HSH              (0x04093670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_RxClkStgNum_OFF                 (13)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxClkStgNum_WID                 ( 5)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxClkStgNum_MSK                 (0x0003E000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxClkStgNum_MIN                 (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxClkStgNum_MAX                 (31) // 0x0000001F
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxClkStgNum_DEF                 (0x00000011)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxClkStgNum_HSH                 (0x050D3670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_WlLongDelEn_OFF                 (18)
  #define DDRDATA_CR_DDRCRDATACONTROL2_WlLongDelEn_WID                 ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL2_WlLongDelEn_MSK                 (0x00040000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_WlLongDelEn_MIN                 (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_WlLongDelEn_MAX                 (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL2_WlLongDelEn_DEF                 (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_WlLongDelEn_HSH                 (0x01123670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_OFF             (19)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_WID             ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MSK             (0x00080000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MIN             (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MAX             (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_DEF             (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_HSH             (0x01133670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_Ddr4Mode_OFF                    (20)
  #define DDRDATA_CR_DDRCRDATACONTROL2_Ddr4Mode_WID                    ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL2_Ddr4Mode_MSK                    (0x00100000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_Ddr4Mode_MIN                    (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_Ddr4Mode_MAX                    (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL2_Ddr4Mode_DEF                    (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_Ddr4Mode_HSH                    (0x01143670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVddqOdt_OFF                   (21)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVddqOdt_WID                   ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVddqOdt_MSK                   (0x00200000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVddqOdt_MIN                   (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVddqOdt_MAX                   (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVddqOdt_DEF                   (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVddqOdt_HSH                   (0x01153670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVttOdt_OFF                    (22)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVttOdt_WID                    ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVttOdt_MSK                    (0x00400000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVttOdt_MIN                    (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVttOdt_MAX                    (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVttOdt_DEF                    (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnVttOdt_HSH                    (0x01163670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_EnConstZEqTx_OFF                (23)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnConstZEqTx_WID                ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnConstZEqTx_MSK                (0x00800000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnConstZEqTx_MIN                (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnConstZEqTx_MAX                (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnConstZEqTx_DEF                (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_EnConstZEqTx_HSH                (0x01173670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_TxEqDis_OFF                     (24)
  #define DDRDATA_CR_DDRCRDATACONTROL2_TxEqDis_WID                     ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL2_TxEqDis_MSK                     (0x01000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_TxEqDis_MIN                     (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_TxEqDis_MAX                     (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL2_TxEqDis_DEF                     (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_TxEqDis_HSH                     (0x01183670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_RxVrefProgMFC_OFF               (25)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxVrefProgMFC_WID               ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MSK               (0x02000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MIN               (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MAX               (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxVrefProgMFC_DEF               (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxVrefProgMFC_HSH               (0x01193670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_Cben_OFF                        (26)
  #define DDRDATA_CR_DDRCRDATACONTROL2_Cben_WID                        ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL2_Cben_MSK                        (0x1C000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_Cben_MIN                        (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_Cben_MAX                        (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL2_Cben_DEF                        (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_Cben_HSH                        (0x031A3670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_TxDeskewDisable_OFF             (29)
  #define DDRDATA_CR_DDRCRDATACONTROL2_TxDeskewDisable_WID             ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL2_TxDeskewDisable_MSK             (0x20000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_TxDeskewDisable_MIN             (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_TxDeskewDisable_MAX             (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL2_TxDeskewDisable_DEF             (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_TxDeskewDisable_HSH             (0x011D3670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDeskewDisable_OFF             (30)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDeskewDisable_WID             ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDeskewDisable_MSK             (0x40000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDeskewDisable_MIN             (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDeskewDisable_MAX             (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDeskewDisable_DEF             (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_RxDeskewDisable_HSH             (0x011E3670)

  #define DDRDATA_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_OFF             (31)
  #define DDRDATA_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_WID             ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MSK             (0x80000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MIN             (0)
  #define DDRDATA_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MAX             (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_DEF             (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_HSH             (0x011F3670)

#define DDRDATA_CR_DDRCRVREFCONTROL_REG                                (0x00003674)

  #define DDRDATA_CR_DDRCRVREFCONTROL_VrefCtl_OFF                      ( 0)
  #define DDRDATA_CR_DDRCRVREFCONTROL_VrefCtl_WID                      (24)
  #define DDRDATA_CR_DDRCRVREFCONTROL_VrefCtl_MSK                      (0x00FFFFFF)
  #define DDRDATA_CR_DDRCRVREFCONTROL_VrefCtl_MIN                      (0)
  #define DDRDATA_CR_DDRCRVREFCONTROL_VrefCtl_MAX                      (16777215) // 0x00FFFFFF
  #define DDRDATA_CR_DDRCRVREFCONTROL_VrefCtl_DEF                      (0x000E453A)
  #define DDRDATA_CR_DDRCRVREFCONTROL_VrefCtl_HSH                      (0x18003674)

  #define DDRDATA_CR_DDRCRVREFCONTROL_OutputCode_OFF                   (24)
  #define DDRDATA_CR_DDRCRVREFCONTROL_OutputCode_WID                   ( 8)
  #define DDRDATA_CR_DDRCRVREFCONTROL_OutputCode_MSK                   (0xFF000000)
  #define DDRDATA_CR_DDRCRVREFCONTROL_OutputCode_MIN                   (0)
  #define DDRDATA_CR_DDRCRVREFCONTROL_OutputCode_MAX                   (255) // 0x000000FF
  #define DDRDATA_CR_DDRCRVREFCONTROL_OutputCode_DEF                   (0x00000000)
  #define DDRDATA_CR_DDRCRVREFCONTROL_OutputCode_HSH                   (0x08183674)

#define DDRDATA_CR_DDRCRVSSHICONTROL_REG                               (0x00003678)

  #define DDRDATA_CR_DDRCRVSSHICONTROL_VssHiCtl_OFF                    ( 0)
  #define DDRDATA_CR_DDRCRVSSHICONTROL_VssHiCtl_WID                    (25)
  #define DDRDATA_CR_DDRCRVSSHICONTROL_VssHiCtl_MSK                    (0x01FFFFFF)
  #define DDRDATA_CR_DDRCRVSSHICONTROL_VssHiCtl_MIN                    (0)
  #define DDRDATA_CR_DDRCRVSSHICONTROL_VssHiCtl_MAX                    (33554431) // 0x01FFFFFF
  #define DDRDATA_CR_DDRCRVSSHICONTROL_VssHiCtl_DEF                    (0x014D8234)
  #define DDRDATA_CR_DDRCRVSSHICONTROL_VssHiCtl_HSH                    (0x19003678)

  #define DDRDATA_CR_DDRCRVSSHICONTROL_OutputCode_OFF                  (25)
  #define DDRDATA_CR_DDRCRVSSHICONTROL_OutputCode_WID                  ( 7)
  #define DDRDATA_CR_DDRCRVSSHICONTROL_OutputCode_MSK                  (0xFE000000)
  #define DDRDATA_CR_DDRCRVSSHICONTROL_OutputCode_MIN                  (0)
  #define DDRDATA_CR_DDRCRVSSHICONTROL_OutputCode_MAX                  (127) // 0x0000007F
  #define DDRDATA_CR_DDRCRVSSHICONTROL_OutputCode_DEF                  (0x00000000)
  #define DDRDATA_CR_DDRCRVSSHICONTROL_OutputCode_HSH                  (0x07193678)

#define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_REG                            (0x0000367C)

  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_OFF              ( 0)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_WID              ( 6)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MSK              (0x0000003F)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MIN              (-32)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MAX              (31) // 0x0000001F
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_DEF              (0x00000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_HSH              (0x8600367C)

  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_OFF              ( 6)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_WID              ( 6)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MSK              (0x00000FC0)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MIN              (-32)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MAX              (31) // 0x0000001F
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_DEF              (0x00000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_HSH              (0x8606367C)

  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_OFF               (12)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_WID               ( 6)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MSK               (0x0003F000)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MIN               (-32)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MAX               (31) // 0x0000001F
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_DEF               (0x00000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_HSH               (0x860C367C)

  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_OFF              (18)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_WID              ( 6)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MSK              (0x00FC0000)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MIN              (-32)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MAX              (31) // 0x0000001F
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_DEF              (0x00000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_HSH              (0x8612367C)

  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_OFF               (24)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_WID               ( 7)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MSK               (0x7F000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MIN               (-64)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MAX               (63) // 0x0000003F
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_DEF               (0x00000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_HSH               (0x8718367C)

  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_Spare_OFF                    (31)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_Spare_WID                    ( 1)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_Spare_MSK                    (0x80000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_Spare_MIN                    (0)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_Spare_MAX                    (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_Spare_DEF                    (0x00000000)
  #define DDRDATA_CR_DDRCRDATAOFFSETTRAIN_Spare_HSH                    (0x011F367C)

#define DDRDATA_CR_DDRCRDATACONTROL0_REG                               (0x00003680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_RxTrainingMode_OFF              ( 0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxTrainingMode_WID              ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxTrainingMode_MSK              (0x00000001)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxTrainingMode_MIN              (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxTrainingMode_MAX              (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxTrainingMode_DEF              (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxTrainingMode_HSH              (0x01003680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_WLTrainingMode_OFF              ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_WLTrainingMode_WID              ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_WLTrainingMode_MSK              (0x00000002)
  #define DDRDATA_CR_DDRCRDATACONTROL0_WLTrainingMode_MIN              (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_WLTrainingMode_MAX              (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_WLTrainingMode_DEF              (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_WLTrainingMode_HSH              (0x01013680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_RLTrainingMode_OFF              ( 2)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RLTrainingMode_WID              ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RLTrainingMode_MSK              (0x00000004)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RLTrainingMode_MIN              (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RLTrainingMode_MAX              (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_RLTrainingMode_DEF              (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RLTrainingMode_HSH              (0x01023680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_SenseampTrainingMode_OFF        ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL0_SenseampTrainingMode_WID        ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MSK        (0x00000008)
  #define DDRDATA_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MIN        (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MAX        (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_SenseampTrainingMode_DEF        (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_SenseampTrainingMode_HSH        (0x01033680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_TxOn_OFF                        ( 4)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxOn_WID                        ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxOn_MSK                        (0x00000010)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxOn_MIN                        (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxOn_MAX                        (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxOn_DEF                        (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxOn_HSH                        (0x01043680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_RfOn_OFF                        ( 5)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RfOn_WID                        ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RfOn_MSK                        (0x00000020)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RfOn_MIN                        (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RfOn_MAX                        (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_RfOn_DEF                        (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RfOn_HSH                        (0x01053680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_RxPiOn_OFF                      ( 6)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxPiOn_WID                      ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxPiOn_MSK                      (0x00000040)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxPiOn_MIN                      (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxPiOn_MAX                      (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxPiOn_DEF                      (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxPiOn_HSH                      (0x01063680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_TxPiOn_OFF                      ( 7)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxPiOn_WID                      ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxPiOn_MSK                      (0x00000080)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxPiOn_MIN                      (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxPiOn_MAX                      (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxPiOn_DEF                      (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxPiOn_HSH                      (0x01073680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_InternalClocksOn_OFF            ( 8)
  #define DDRDATA_CR_DDRCRDATACONTROL0_InternalClocksOn_WID            ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_InternalClocksOn_MSK            (0x00000100)
  #define DDRDATA_CR_DDRCRDATACONTROL0_InternalClocksOn_MIN            (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_InternalClocksOn_MAX            (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_InternalClocksOn_DEF            (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_InternalClocksOn_HSH            (0x01083680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_RepeaterClocksOn_OFF            ( 9)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RepeaterClocksOn_WID            ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MSK            (0x00000200)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MIN            (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MAX            (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_RepeaterClocksOn_DEF            (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RepeaterClocksOn_HSH            (0x01093680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_TxDisable_OFF                   (10)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxDisable_WID                   ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxDisable_MSK                   (0x00000400)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxDisable_MIN                   (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxDisable_MAX                   (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxDisable_DEF                   (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxDisable_HSH                   (0x010A3680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDisable_OFF                   (11)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDisable_WID                   ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDisable_MSK                   (0x00000800)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDisable_MIN                   (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDisable_MAX                   (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDisable_DEF                   (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDisable_HSH                   (0x010B3680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_TxLong_OFF                      (12)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxLong_WID                      ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxLong_MSK                      (0x00001000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxLong_MIN                      (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxLong_MAX                      (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxLong_DEF                      (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_TxLong_HSH                      (0x010C3680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDqsCtle_OFF                   (13)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDqsCtle_WID                   ( 2)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDqsCtle_MSK                   (0x00006000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDqsCtle_MIN                   (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDqsCtle_MAX                   (3) // 0x00000003
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDqsCtle_DEF                   (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxDqsCtle_HSH                   (0x020D3680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_RxReadPointer_OFF               (15)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxReadPointer_WID               ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxReadPointer_MSK               (0x00038000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxReadPointer_MIN               (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxReadPointer_MAX               (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxReadPointer_DEF               (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_RxReadPointer_HSH               (0x030F3680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_LongOdtR2W_OFF                  (18)
  #define DDRDATA_CR_DDRCRDATACONTROL0_LongOdtR2W_WID                  ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_LongOdtR2W_MSK                  (0x00040000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_LongOdtR2W_MIN                  (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_LongOdtR2W_MAX                  (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_LongOdtR2W_DEF                  (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_LongOdtR2W_HSH                  (0x01123680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_DataVccddqHi_OFF                (19)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DataVccddqHi_WID                ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DataVccddqHi_MSK                (0x00080000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DataVccddqHi_MIN                (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DataVccddqHi_MAX                (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_DataVccddqHi_DEF                (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DataVccddqHi_HSH                (0x01133680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRd_OFF                    (20)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRd_WID                    ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRd_MSK                    (0x00100000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRd_MIN                    (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRd_MAX                    (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRd_DEF                    (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRd_HSH                    (0x01143680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFWr_OFF                    (21)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFWr_WID                    ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFWr_MSK                    (0x00200000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFWr_MIN                    (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFWr_MAX                    (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFWr_DEF                    (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFWr_HSH                    (0x01153680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRank_OFF                  (22)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRank_WID                  ( 2)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRank_MSK                  (0x00C00000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRank_MIN                  (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRank_MAX                  (3) // 0x00000003
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRank_DEF                  (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ReadRFRank_HSH                  (0x02163680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_ForceOdtOn_OFF                  (24)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ForceOdtOn_WID                  ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ForceOdtOn_MSK                  (0x01000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ForceOdtOn_MIN                  (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ForceOdtOn_MAX                  (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_ForceOdtOn_DEF                  (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_ForceOdtOn_HSH                  (0x01183680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampOff_OFF                  (25)
  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampOff_WID                  ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampOff_MSK                  (0x02000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampOff_MIN                  (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampOff_MAX                  (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampOff_DEF                  (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampOff_HSH                  (0x01193680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_DisableOdtStatic_OFF            (26)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DisableOdtStatic_WID            ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DisableOdtStatic_MSK            (0x04000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DisableOdtStatic_MIN            (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DisableOdtStatic_MAX            (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_DisableOdtStatic_DEF            (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DisableOdtStatic_HSH            (0x011A3680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_OFF             (27)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_WID             ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MSK             (0x08000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MIN             (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MAX             (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_DEF             (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_HSH             (0x011B3680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_LPDDR_Mode_OFF                  (28)
  #define DDRDATA_CR_DDRCRDATACONTROL0_LPDDR_Mode_WID                  ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_LPDDR_Mode_MSK                  (0x10000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_LPDDR_Mode_MIN                  (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_LPDDR_Mode_MAX                  (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_LPDDR_Mode_DEF                  (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_LPDDR_Mode_HSH                  (0x011C3680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_EnReadPreamble_OFF              (29)
  #define DDRDATA_CR_DDRCRDATACONTROL0_EnReadPreamble_WID              ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_EnReadPreamble_MSK              (0x20000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_EnReadPreamble_MIN              (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_EnReadPreamble_MAX              (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_EnReadPreamble_DEF              (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_EnReadPreamble_HSH              (0x011D3680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampExtendEn_OFF             (30)
  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampExtendEn_WID             ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MSK             (0x40000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MIN             (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MAX             (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampExtendEn_DEF             (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_OdtSampExtendEn_HSH             (0x011E3680)

  #define DDRDATA_CR_DDRCRDATACONTROL0_EarlyRleakEn_OFF                (31)
  #define DDRDATA_CR_DDRCRDATACONTROL0_EarlyRleakEn_WID                ( 1)
  #define DDRDATA_CR_DDRCRDATACONTROL0_EarlyRleakEn_MSK                (0x80000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_EarlyRleakEn_MIN                (0)
  #define DDRDATA_CR_DDRCRDATACONTROL0_EarlyRleakEn_MAX                (1) // 0x00000001
  #define DDRDATA_CR_DDRCRDATACONTROL0_EarlyRleakEn_DEF                (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL0_EarlyRleakEn_HSH                (0x011F3680)

#define DDRDATA_CR_DDRCRVREFADJUST1_REG                                (0x00003684)

  #define DDRDATA_CR_DDRCRVREFADJUST1_CAVrefCtl_OFF                    ( 0)
  #define DDRDATA_CR_DDRCRVREFADJUST1_CAVrefCtl_WID                    ( 7)
  #define DDRDATA_CR_DDRCRVREFADJUST1_CAVrefCtl_MSK                    (0x0000007F)
  #define DDRDATA_CR_DDRCRVREFADJUST1_CAVrefCtl_MIN                    (-64)
  #define DDRDATA_CR_DDRCRVREFADJUST1_CAVrefCtl_MAX                    (63) // 0x0000003F
  #define DDRDATA_CR_DDRCRVREFADJUST1_CAVrefCtl_DEF                    (0x00000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_CAVrefCtl_HSH                    (0x87003684)

  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch1VrefCtl_OFF                   ( 7)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch1VrefCtl_WID                   ( 7)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MSK                   (0x00003F80)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MIN                   (-64)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MAX                   (63) // 0x0000003F
  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch1VrefCtl_DEF                   (0x00000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch1VrefCtl_HSH                   (0x87073684)

  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch0VrefCtl_OFF                   (14)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch0VrefCtl_WID                   ( 7)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MSK                   (0x001FC000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MIN                   (-64)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MAX                   (63) // 0x0000003F
  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch0VrefCtl_DEF                   (0x00000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Ch0VrefCtl_HSH                   (0x870E3684)

  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCA_OFF                 (21)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCA_WID                 ( 1)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MSK                 (0x00200000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MIN                 (0)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MAX                 (1) // 0x00000001
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCA_DEF                 (0x00000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCA_HSH                 (0x01153684)

  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_OFF                (22)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_WID                ( 1)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MSK                (0x00400000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MIN                (0)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MAX                (1) // 0x00000001
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_DEF                (0x00000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_HSH                (0x01163684)

  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_OFF                (23)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_WID                ( 1)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MSK                (0x00800000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MIN                (0)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MAX                (1) // 0x00000001
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_DEF                (0x00000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_HSH                (0x01173684)

  #define DDRDATA_CR_DDRCRVREFADJUST1_HiZTimerCtrl_OFF                 (24)
  #define DDRDATA_CR_DDRCRVREFADJUST1_HiZTimerCtrl_WID                 ( 2)
  #define DDRDATA_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MSK                 (0x03000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MIN                 (0)
  #define DDRDATA_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MAX                 (3) // 0x00000003
  #define DDRDATA_CR_DDRCRVREFADJUST1_HiZTimerCtrl_DEF                 (0x00000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_HiZTimerCtrl_HSH                 (0x02183684)

  #define DDRDATA_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_OFF                (26)
  #define DDRDATA_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_WID                ( 1)
  #define DDRDATA_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MSK                (0x04000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MIN                (0)
  #define DDRDATA_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MAX                (1) // 0x00000001
  #define DDRDATA_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_DEF                (0x00000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_HSH                (0x011A3684)

  #define DDRDATA_CR_DDRCRVREFADJUST1_Rsvd_OFF                         (27)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Rsvd_WID                         ( 2)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Rsvd_MSK                         (0x18000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Rsvd_MIN                         (0)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Rsvd_MAX                         (3) // 0x00000003
  #define DDRDATA_CR_DDRCRVREFADJUST1_Rsvd_DEF                         (0x00000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_Rsvd_HSH                         (0x021B3684)

  #define DDRDATA_CR_DDRCRVREFADJUST1_caSlowBW_OFF                     (29)
  #define DDRDATA_CR_DDRCRVREFADJUST1_caSlowBW_WID                     ( 1)
  #define DDRDATA_CR_DDRCRVREFADJUST1_caSlowBW_MSK                     (0x20000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_caSlowBW_MIN                     (0)
  #define DDRDATA_CR_DDRCRVREFADJUST1_caSlowBW_MAX                     (1) // 0x00000001
  #define DDRDATA_CR_DDRCRVREFADJUST1_caSlowBW_DEF                     (0x00000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_caSlowBW_HSH                     (0x011D3684)

  #define DDRDATA_CR_DDRCRVREFADJUST1_ch0SlowBW_OFF                    (30)
  #define DDRDATA_CR_DDRCRVREFADJUST1_ch0SlowBW_WID                    ( 1)
  #define DDRDATA_CR_DDRCRVREFADJUST1_ch0SlowBW_MSK                    (0x40000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_ch0SlowBW_MIN                    (0)
  #define DDRDATA_CR_DDRCRVREFADJUST1_ch0SlowBW_MAX                    (1) // 0x00000001
  #define DDRDATA_CR_DDRCRVREFADJUST1_ch0SlowBW_DEF                    (0x00000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_ch0SlowBW_HSH                    (0x011E3684)

  #define DDRDATA_CR_DDRCRVREFADJUST1_ch1SlowBW_OFF                    (31)
  #define DDRDATA_CR_DDRCRVREFADJUST1_ch1SlowBW_WID                    ( 1)
  #define DDRDATA_CR_DDRCRVREFADJUST1_ch1SlowBW_MSK                    (0x80000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_ch1SlowBW_MIN                    (0)
  #define DDRDATA_CR_DDRCRVREFADJUST1_ch1SlowBW_MAX                    (1) // 0x00000001
  #define DDRDATA_CR_DDRCRVREFADJUST1_ch1SlowBW_DEF                    (0x00000000)
  #define DDRDATA_CR_DDRCRVREFADJUST1_ch1SlowBW_HSH                    (0x011F3684)

#define DDRDATA_CR_DDRCRDATACONTROL3_REG                               (0x00003688)

  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit0_OFF            ( 0)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit0_WID            ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit0_MSK            (0x00000007)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit0_MIN            (0)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit0_MAX            (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit0_DEF            (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit0_HSH            (0x03003688)

  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit1_OFF            ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit1_WID            ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit1_MSK            (0x00000038)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit1_MIN            (0)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit1_MAX            (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit1_DEF            (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit1_HSH            (0x03033688)

  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit2_OFF            ( 6)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit2_WID            ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit2_MSK            (0x000001C0)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit2_MIN            (0)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit2_MAX            (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit2_DEF            (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit2_HSH            (0x03063688)

  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit3_OFF            ( 9)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit3_WID            ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit3_MSK            (0x00000E00)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit3_MIN            (0)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit3_MAX            (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit3_DEF            (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit3_HSH            (0x03093688)

  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit4_OFF            (12)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit4_WID            ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit4_MSK            (0x00007000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit4_MIN            (0)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit4_MAX            (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit4_DEF            (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit4_HSH            (0x030C3688)

  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit5_OFF            (15)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit5_WID            ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit5_MSK            (0x00038000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit5_MIN            (0)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit5_MAX            (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit5_DEF            (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit5_HSH            (0x030F3688)

  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit6_OFF            (18)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit6_WID            ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit6_MSK            (0x001C0000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit6_MIN            (0)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit6_MAX            (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit6_DEF            (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit6_HSH            (0x03123688)

  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit7_OFF            (21)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit7_WID            ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit7_MSK            (0x00E00000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit7_MIN            (0)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit7_MAX            (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit7_DEF            (0x00000000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_AttackerDataBit7_HSH            (0x03153688)

  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp2_OFF                    (24)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp2_WID                    ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp2_MSK                    (0x07000000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp2_MIN                    (0)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp2_MAX                    (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp2_DEF                    (0x00000003)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp2_HSH                    (0x03183688)

  #define DDRDATA_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_OFF                 (27)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_WID                 ( 3)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MSK                 (0x38000000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MIN                 (0)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MAX                 (7) // 0x00000007
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_DEF                 (0x00000003)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_HSH                 (0x031B3688)

  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp1_OFF                    (30)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp1_WID                    ( 2)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp1_MSK                    (0xC0000000)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp1_MIN                    (0)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp1_MAX                    (3) // 0x00000003
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp1_DEF                    (0x00000001)
  #define DDRDATA_CR_DDRCRDATACONTROL3_CBEnAmp1_HSH                    (0x021E3688)

#define DDRDATA_CR_DDRCRVTTGENCONTROL_REG                              (0x0000368C)

  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Target_OFF                     ( 0)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Target_WID                     ( 4)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Target_MSK                     (0x0000000F)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Target_MIN                     (0)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Target_MAX                     (15) // 0x0000000F
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Target_DEF                     (0x00000000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Target_HSH                     (0x0400368C)

  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Panic_OFF                      ( 4)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Panic_WID                      ( 5)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Panic_MSK                      (0x000001F0)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Panic_MIN                      (0)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Panic_MAX                      (31) // 0x0000001F
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Panic_DEF                      (0x00000010)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Panic_HSH                      (0x0504368C)

  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisPanicDrv_OFF                ( 9)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisPanicDrv_WID                ( 2)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MSK                (0x00000600)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MIN                (0)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MAX                (3) // 0x00000003
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisPanicDrv_DEF                (0x00000000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisPanicDrv_HSH                (0x0209368C)

  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_OFF             (11)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_WID             ( 1)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MSK             (0x00000800)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MIN             (0)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MAX             (1) // 0x00000001
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_DEF             (0x00000000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_HSH             (0x010B368C)

  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_OFF                 (12)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_WID                 ( 1)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MSK                 (0x00001000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MIN                 (0)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MAX                 (1) // 0x00000001
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_DEF                 (0x00000000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_HSH                 (0x010C368C)

  #define DDRDATA_CR_DDRCRVTTGENCONTROL_ViewOfstsel_OFF                (13)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_ViewOfstsel_WID                ( 3)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MSK                (0x0000E000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MIN                (0)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MAX                (7) // 0x00000007
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_ViewOfstsel_DEF                (0x00000000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_ViewOfstsel_HSH                (0x030D368C)

  #define DDRDATA_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_OFF          (16)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_WID          ( 1)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MSK          (0x00010000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MIN          (0)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MAX          (1) // 0x00000001
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_DEF          (0x00000000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_HSH          (0x0110368C)

  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Spares_OFF                     (17)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Spares_WID                     ( 8)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Spares_MSK                     (0x01FE0000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Spares_MIN                     (0)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Spares_MAX                     (255) // 0x000000FF
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Spares_DEF                     (0x00000000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Spares_HSH                     (0x0811368C)

  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Disable2Vt_OFF                 (25)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Disable2Vt_WID                 ( 1)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Disable2Vt_MSK                 (0x02000000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Disable2Vt_MIN                 (0)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Disable2Vt_MAX                 (1) // 0x00000001
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Disable2Vt_DEF                 (0x00000000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_Disable2Vt_HSH                 (0x0119368C)

  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_OFF             (26)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_WID             ( 6)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MSK             (0xFC000000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MIN             (0)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MAX             (63) // 0x0000003F
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_DEF             (0x00000000)
  #define DDRDATA_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_HSH             (0x061A368C)

#define DDRCMD_CR_DDRCRCMDCOMP_REG                                     (0x00003700)

  #define DDRCMD_CR_DDRCRCMDCOMP_Scomp_OFF                             ( 0)
  #define DDRCMD_CR_DDRCRCMDCOMP_Scomp_WID                             ( 6)
  #define DDRCMD_CR_DDRCRCMDCOMP_Scomp_MSK                             (0x0000003F)
  #define DDRCMD_CR_DDRCRCMDCOMP_Scomp_MIN                             (0)
  #define DDRCMD_CR_DDRCRCMDCOMP_Scomp_MAX                             (63) // 0x0000003F
  #define DDRCMD_CR_DDRCRCMDCOMP_Scomp_DEF                             (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCOMP_Scomp_HSH                             (0x06003700)

  #define DDRCMD_CR_DDRCRCMDCOMP_TcoComp_OFF                           ( 6)
  #define DDRCMD_CR_DDRCRCMDCOMP_TcoComp_WID                           ( 6)
  #define DDRCMD_CR_DDRCRCMDCOMP_TcoComp_MSK                           (0x00000FC0)
  #define DDRCMD_CR_DDRCRCMDCOMP_TcoComp_MIN                           (0)
  #define DDRCMD_CR_DDRCRCMDCOMP_TcoComp_MAX                           (63) // 0x0000003F
  #define DDRCMD_CR_DDRCRCMDCOMP_TcoComp_DEF                           (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCOMP_TcoComp_HSH                           (0x06063700)

  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvUp_OFF                        (12)
  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvUp_WID                        ( 6)
  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvUp_MSK                        (0x0003F000)
  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvUp_MIN                        (0)
  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvUp_MAX                        (63) // 0x0000003F
  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvUp_DEF                        (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvUp_HSH                        (0x060C3700)

  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvDown_OFF                      (18)
  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvDown_WID                      ( 6)
  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvDown_MSK                      (0x00FC0000)
  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvDown_MIN                      (0)
  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvDown_MAX                      (63) // 0x0000003F
  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvDown_DEF                      (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCOMP_RcompDrvDown_HSH                      (0x06123700)

  #define DDRCMD_CR_DDRCRCMDCOMP_Spare_OFF                             (24)
  #define DDRCMD_CR_DDRCRCMDCOMP_Spare_WID                             ( 8)
  #define DDRCMD_CR_DDRCRCMDCOMP_Spare_MSK                             (0xFF000000)
  #define DDRCMD_CR_DDRCRCMDCOMP_Spare_MIN                             (0)
  #define DDRCMD_CR_DDRCRCMDCOMP_Spare_MAX                             (255) // 0x000000FF
  #define DDRCMD_CR_DDRCRCMDCOMP_Spare_DEF                             (0x00000004)
  #define DDRCMD_CR_DDRCRCMDCOMP_Spare_HSH                             (0x08183700)

#define DDRCMD_CR_DDRCRCMDCOMPOFFSET_REG                               (0x00003704)

  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_ScompOffset_OFF                 ( 0)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_ScompOffset_WID                 ( 5)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MSK                 (0x0000001F)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MIN                 (-16)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MAX                 (15) // 0x0000000F
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_ScompOffset_DEF                 (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_ScompOffset_HSH                 (0x85003704)

  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_OFF               ( 5)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_WID               ( 4)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MSK               (0x000001E0)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MIN               (-8)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MAX               (7) // 0x00000007
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_DEF               (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_HSH               (0x84053704)

  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_OFF            ( 9)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_WID            ( 4)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MSK            (0x00001E00)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MIN            (-8)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MAX            (7) // 0x00000007
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_DEF            (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_HSH            (0x84093704)

  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_OFF          (13)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_WID          ( 4)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MSK          (0x0001E000)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MIN          (-8)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MAX          (7) // 0x00000007
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_DEF          (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_HSH          (0x840D3704)

  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_Spare_OFF                       (17)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_Spare_WID                       (15)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_Spare_MSK                       (0xFFFE0000)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_Spare_MIN                       (0)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_Spare_MAX                       (32767) // 0x00007FFF
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_Spare_DEF                       (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCOMPOFFSET_Spare_HSH                       (0x0F113704)

#define DDRCMD_CR_DDRCRCMDPICODING_REG                                 (0x00003708)

  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi0Code_OFF                    ( 0)
  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi0Code_WID                    ( 7)
  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi0Code_MSK                    (0x0000007F)
  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi0Code_MIN                    (0)
  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi0Code_MAX                    (127) // 0x0000007F
  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi0Code_DEF                    (0x00000000)
  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi0Code_HSH                    (0x07003708)

  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi1Code_OFF                    ( 7)
  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi1Code_WID                    ( 7)
  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi1Code_MSK                    (0x00003F80)
  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi1Code_MIN                    (0)
  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi1Code_MAX                    (127) // 0x0000007F
  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi1Code_DEF                    (0x00000000)
  #define DDRCMD_CR_DDRCRCMDPICODING_CmdPi1Code_HSH                    (0x07073708)

  #define DDRCMD_CR_DDRCRCMDPICODING_Spare_OFF                         (14)
  #define DDRCMD_CR_DDRCRCMDPICODING_Spare_WID                         (18)
  #define DDRCMD_CR_DDRCRCMDPICODING_Spare_MSK                         (0xFFFFC000)
  #define DDRCMD_CR_DDRCRCMDPICODING_Spare_MIN                         (0)
  #define DDRCMD_CR_DDRCRCMDPICODING_Spare_MAX                         (262143) // 0x0003FFFF
  #define DDRCMD_CR_DDRCRCMDPICODING_Spare_DEF                         (0x00000000)
  #define DDRCMD_CR_DDRCRCMDPICODING_Spare_HSH                         (0x120E3708)

#define DDRCMD_CR_DDRCRCMDCONTROLS_REG                                 (0x0000370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_RefPi_OFF                         ( 0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RefPi_WID                         ( 4)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RefPi_MSK                         (0x0000000F)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RefPi_MIN                         (-8)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RefPi_MAX                         (7) // 0x00000007
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RefPi_DEF                         (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RefPi_HSH                         (0x8400370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllMask_OFF                       ( 4)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllMask_WID                       ( 2)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllMask_MSK                       (0x00000030)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllMask_MIN                       (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllMask_MAX                       (3) // 0x00000003
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllMask_DEF                       (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllMask_HSH                       (0x0204370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_ClkGateDisable_OFF                ( 6)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_ClkGateDisable_WID                ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_ClkGateDisable_MSK                (0x00000040)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_ClkGateDisable_MIN                (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_ClkGateDisable_MAX                (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_ClkGateDisable_DEF                (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_ClkGateDisable_HSH                (0x0106370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_TxOn_OFF                          ( 7)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_TxOn_WID                          ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_TxOn_MSK                          (0x00000080)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_TxOn_MIN                          (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_TxOn_MAX                          (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_TxOn_DEF                          (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_TxOn_HSH                          (0x0107370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_IntClkOn_OFF                      ( 8)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IntClkOn_WID                      ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IntClkOn_MSK                      (0x00000100)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IntClkOn_MIN                      (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IntClkOn_MAX                      (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IntClkOn_DEF                      (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IntClkOn_HSH                      (0x0108370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_RepClkOn_OFF                      ( 9)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RepClkOn_WID                      ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RepClkOn_MSK                      (0x00000200)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RepClkOn_MIN                      (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RepClkOn_MAX                      (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RepClkOn_DEF                      (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RepClkOn_HSH                      (0x0109370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbOrMisr_OFF                    (10)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbOrMisr_WID                    ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbOrMisr_MSK                    (0x00000400)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbOrMisr_MIN                    (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbOrMisr_MAX                    (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbOrMisr_DEF                    (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbOrMisr_HSH                    (0x010A370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbHold_OFF                      (11)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbHold_WID                      ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbHold_MSK                      (0x00000800)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbHold_MIN                      (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbHold_MAX                      (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbHold_DEF                      (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_IolbHold_HSH                      (0x010B370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_OdtMode_OFF                       (12)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_OdtMode_WID                       ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_OdtMode_MSK                       (0x00001000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_OdtMode_MIN                       (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_OdtMode_MAX                       (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_OdtMode_DEF                       (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_OdtMode_HSH                       (0x010C370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_CmdTxEq_OFF                       (13)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_CmdTxEq_WID                       ( 2)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_CmdTxEq_MSK                       (0x00006000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_CmdTxEq_MIN                       (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_CmdTxEq_MAX                       (3) // 0x00000003
  #define DDRCMD_CR_DDRCRCMDCONTROLS_CmdTxEq_DEF                       (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_CmdTxEq_HSH                       (0x020D370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_OFF                (15)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_WID                ( 2)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MSK                (0x00018000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MIN                (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MAX                (3) // 0x00000003
  #define DDRCMD_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_DEF                (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_HSH                (0x020F370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_PrtEn_OFF                         (17)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_PrtEn_WID                         ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_PrtEn_MSK                         (0x00020000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_PrtEn_MIN                         (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_PrtEn_MAX                         (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_PrtEn_DEF                         (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_PrtEn_HSH                         (0x0111370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_AlrtEn_OFF                        (18)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_AlrtEn_WID                        ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_AlrtEn_MSK                        (0x00040000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_AlrtEn_MIN                        (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_AlrtEn_MAX                        (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_AlrtEn_DEF                        (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_AlrtEn_HSH                        (0x0112370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_OFF                   (19)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_WID                   ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MSK                   (0x00080000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MIN                   (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MAX                   (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_DEF                   (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_HSH                   (0x0113370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_OFF               (20)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_WID               ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MSK               (0x00100000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MIN               (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MAX               (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_DEF               (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_HSH               (0x0114370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_RxVref_OFF                        (21)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RxVref_WID                        ( 6)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RxVref_MSK                        (0x07E00000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RxVref_MIN                        (-32)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RxVref_MAX                        (31) // 0x0000001F
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RxVref_DEF                        (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_RxVref_HSH                        (0x8615370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_VccddqHi_OFF                      (27)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_VccddqHi_WID                      ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_VccddqHi_MSK                      (0x08000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_VccddqHi_MIN                      (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_VccddqHi_MAX                      (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_VccddqHi_DEF                      (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_VccddqHi_HSH                      (0x011B370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllWeakLock_OFF                   (28)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllWeakLock_WID                   ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllWeakLock_MSK                   (0x10000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllWeakLock_MIN                   (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllWeakLock_MAX                   (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllWeakLock_DEF                   (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_DllWeakLock_HSH                   (0x011C370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDDR_Mode_OFF                    (29)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDDR_Mode_WID                    ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MSK                    (0x20000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MIN                    (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MAX                    (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDDR_Mode_DEF                    (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDDR_Mode_HSH                    (0x011D370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_OFF                  (30)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_WID                  ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MSK                  (0x40000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MIN                  (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MAX                  (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_DEF                  (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_HSH                  (0x011E370C)

  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_OFF                  (31)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_WID                  ( 1)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MSK                  (0x80000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MIN                  (0)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MAX                  (1) // 0x00000001
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_DEF                  (0x00000000)
  #define DDRCMD_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_HSH                  (0x011F370C)

#define DDRCMD_CR_DLLPITESTANDADC_REG                                  (0x00003724)

  #define DDRCMD_CR_DLLPITESTANDADC_RunTest_OFF                        ( 0)
  #define DDRCMD_CR_DLLPITESTANDADC_RunTest_WID                        ( 1)
  #define DDRCMD_CR_DLLPITESTANDADC_RunTest_MSK                        (0x00000001)
  #define DDRCMD_CR_DLLPITESTANDADC_RunTest_MIN                        (0)
  #define DDRCMD_CR_DLLPITESTANDADC_RunTest_MAX                        (1) // 0x00000001
  #define DDRCMD_CR_DLLPITESTANDADC_RunTest_DEF                        (0x00000000)
  #define DDRCMD_CR_DLLPITESTANDADC_RunTest_HSH                        (0x01003724)

  #define DDRCMD_CR_DLLPITESTANDADC_Load_OFF                           ( 1)
  #define DDRCMD_CR_DLLPITESTANDADC_Load_WID                           ( 1)
  #define DDRCMD_CR_DLLPITESTANDADC_Load_MSK                           (0x00000002)
  #define DDRCMD_CR_DLLPITESTANDADC_Load_MIN                           (0)
  #define DDRCMD_CR_DLLPITESTANDADC_Load_MAX                           (1) // 0x00000001
  #define DDRCMD_CR_DLLPITESTANDADC_Load_DEF                           (0x00000000)
  #define DDRCMD_CR_DLLPITESTANDADC_Load_HSH                           (0x01013724)

  #define DDRCMD_CR_DLLPITESTANDADC_ModeHVM_OFF                        ( 2)
  #define DDRCMD_CR_DLLPITESTANDADC_ModeHVM_WID                        ( 1)
  #define DDRCMD_CR_DLLPITESTANDADC_ModeHVM_MSK                        (0x00000004)
  #define DDRCMD_CR_DLLPITESTANDADC_ModeHVM_MIN                        (0)
  #define DDRCMD_CR_DLLPITESTANDADC_ModeHVM_MAX                        (1) // 0x00000001
  #define DDRCMD_CR_DLLPITESTANDADC_ModeHVM_DEF                        (0x00000000)
  #define DDRCMD_CR_DLLPITESTANDADC_ModeHVM_HSH                        (0x01023724)

  #define DDRCMD_CR_DLLPITESTANDADC_ModeDV_OFF                         ( 3)
  #define DDRCMD_CR_DLLPITESTANDADC_ModeDV_WID                         ( 1)
  #define DDRCMD_CR_DLLPITESTANDADC_ModeDV_MSK                         (0x00000008)
  #define DDRCMD_CR_DLLPITESTANDADC_ModeDV_MIN                         (0)
  #define DDRCMD_CR_DLLPITESTANDADC_ModeDV_MAX                         (1) // 0x00000001
  #define DDRCMD_CR_DLLPITESTANDADC_ModeDV_DEF                         (0x00000000)
  #define DDRCMD_CR_DLLPITESTANDADC_ModeDV_HSH                         (0x01033724)

  #define DDRCMD_CR_DLLPITESTANDADC_CalCfdl_OFF                        ( 4)
  #define DDRCMD_CR_DLLPITESTANDADC_CalCfdl_WID                        ( 1)
  #define DDRCMD_CR_DLLPITESTANDADC_CalCfdl_MSK                        (0x00000010)
  #define DDRCMD_CR_DLLPITESTANDADC_CalCfdl_MIN                        (0)
  #define DDRCMD_CR_DLLPITESTANDADC_CalCfdl_MAX                        (1) // 0x00000001
  #define DDRCMD_CR_DLLPITESTANDADC_CalCfdl_DEF                        (0x00000000)
  #define DDRCMD_CR_DLLPITESTANDADC_CalCfdl_HSH                        (0x01043724)

  #define DDRCMD_CR_DLLPITESTANDADC_LoadCount_OFF                      ( 5)
  #define DDRCMD_CR_DLLPITESTANDADC_LoadCount_WID                      (10)
  #define DDRCMD_CR_DLLPITESTANDADC_LoadCount_MSK                      (0x00007FE0)
  #define DDRCMD_CR_DLLPITESTANDADC_LoadCount_MIN                      (0)
  #define DDRCMD_CR_DLLPITESTANDADC_LoadCount_MAX                      (1023) // 0x000003FF
  #define DDRCMD_CR_DLLPITESTANDADC_LoadCount_DEF                      (0x00000000)
  #define DDRCMD_CR_DLLPITESTANDADC_LoadCount_HSH                      (0x0A053724)

  #define DDRCMD_CR_DLLPITESTANDADC_CountStatus_OFF                    (15)
  #define DDRCMD_CR_DLLPITESTANDADC_CountStatus_WID                    (10)
  #define DDRCMD_CR_DLLPITESTANDADC_CountStatus_MSK                    (0x01FF8000)
  #define DDRCMD_CR_DLLPITESTANDADC_CountStatus_MIN                    (0)
  #define DDRCMD_CR_DLLPITESTANDADC_CountStatus_MAX                    (1023) // 0x000003FF
  #define DDRCMD_CR_DLLPITESTANDADC_CountStatus_DEF                    (0x00000000)
  #define DDRCMD_CR_DLLPITESTANDADC_CountStatus_HSH                    (0x0A0F3724)

  #define DDRCMD_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF               (25)
  #define DDRCMD_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID               ( 1)
  #define DDRCMD_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK               (0x02000000)
  #define DDRCMD_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN               (0)
  #define DDRCMD_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX               (1) // 0x00000001
  #define DDRCMD_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF               (0x00000000)
  #define DDRCMD_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH               (0x01193724)

  #define DDRCMD_CR_DLLPITESTANDADC_Spare_OFF                          (26)
  #define DDRCMD_CR_DLLPITESTANDADC_Spare_WID                          ( 6)
  #define DDRCMD_CR_DLLPITESTANDADC_Spare_MSK                          (0xFC000000)
  #define DDRCMD_CR_DLLPITESTANDADC_Spare_MIN                          (0)
  #define DDRCMD_CR_DLLPITESTANDADC_Spare_MAX                          (63) // 0x0000003F
  #define DDRCMD_CR_DLLPITESTANDADC_Spare_DEF                          (0x00000000)
  #define DDRCMD_CR_DLLPITESTANDADC_Spare_HSH                          (0x061A3724)

#define DDRCKECTL_CR_DDRCRCTLCOMP_REG                                  (0x00003810)

  #define DDRCKECTL_CR_DDRCRCTLCOMP_Scomp_OFF                          ( 0)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_Scomp_WID                          ( 6)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_Scomp_MSK                          (0x0000003F)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_Scomp_MIN                          (0)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_Scomp_MAX                          (63) // 0x0000003F
  #define DDRCKECTL_CR_DDRCRCTLCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_Scomp_HSH                          (0x06003810)

  #define DDRCKECTL_CR_DDRCRCTLCOMP_TcoComp_OFF                        ( 6)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_TcoComp_WID                        ( 6)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_TcoComp_MSK                        (0x00000FC0)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_TcoComp_MIN                        (0)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRCKECTL_CR_DDRCRCTLCOMP_TcoComp_DEF                        (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_TcoComp_HSH                        (0x06063810)

  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvUp_OFF                     (12)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvUp_MSK                     (0x0003F000)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvUp_HSH                     (0x060C3810)

  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvDown_OFF                   (18)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvDown_MSK                   (0x00FC0000)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_RcompDrvDown_HSH                   (0x06123810)

  #define DDRCKECTL_CR_DDRCRCTLCOMP_Spare_OFF                          (24)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_Spare_WID                          ( 8)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_Spare_MSK                          (0xFF000000)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_Spare_MIN                          (0)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_Spare_MAX                          (255) // 0x000000FF
  #define DDRCKECTL_CR_DDRCRCTLCOMP_Spare_DEF                          (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCOMP_Spare_HSH                          (0x08183810)

#define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_REG                            (0x00003814)

  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_ScompOffset_WID              ( 5)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MSK              (0x0000001F)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MIN              (-16)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MAX              (15) // 0x0000000F
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_ScompOffset_HSH              (0x85003814)

  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_OFF            ( 5)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_WID            ( 4)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MSK            (0x000001E0)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MIN            (-8)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MAX            (7) // 0x00000007
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_DEF            (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_HSH            (0x84053814)

  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_OFF         ( 9)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MSK         (0x00001E00)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84093814)

  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_OFF       (13)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MSK       (0x0001E000)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_HSH       (0x840D3814)

  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_Spare_OFF                    (17)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_Spare_WID                    (15)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_Spare_MSK                    (0xFFFE0000)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_Spare_MAX                    (32767) // 0x00007FFF
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_Spare_HSH                    (0x0F113814)

#define DDRCKECTL_CR_DDRCRCTLPICODING_REG                              (0x00003818)

  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode0_OFF                 ( 0)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode0_WID                 ( 7)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode0_MSK                 (0x0000007F)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode0_MIN                 (0)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode0_MAX                 (127) // 0x0000007F
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode0_DEF                 (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode0_HSH                 (0x07003818)

  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode1_OFF                 ( 7)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode1_WID                 ( 7)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode1_MSK                 (0x00003F80)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode1_MIN                 (0)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode1_MAX                 (127) // 0x0000007F
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode1_DEF                 (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode1_HSH                 (0x07073818)

  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode2_OFF                 (14)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode2_WID                 ( 7)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode2_MSK                 (0x001FC000)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode2_MIN                 (0)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode2_MAX                 (127) // 0x0000007F
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode2_DEF                 (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode2_HSH                 (0x070E3818)

  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode3_OFF                 (21)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode3_WID                 ( 7)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode3_MSK                 (0x0FE00000)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode3_MIN                 (0)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode3_MAX                 (127) // 0x0000007F
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode3_DEF                 (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlPiCode3_HSH                 (0x07153818)

  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlXoverEnable_OFF             (28)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlXoverEnable_WID             ( 1)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlXoverEnable_MSK             (0x10000000)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlXoverEnable_MIN             (0)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlXoverEnable_MAX             (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlXoverEnable_DEF             (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_CtlXoverEnable_HSH             (0x011C3818)

  #define DDRCKECTL_CR_DDRCRCTLPICODING_Spare_OFF                      (29)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_Spare_WID                      ( 3)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_Spare_MSK                      (0xE0000000)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_Spare_MIN                      (0)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_Spare_MAX                      (7) // 0x00000007
  #define DDRCKECTL_CR_DDRCRCTLPICODING_Spare_DEF                      (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLPICODING_Spare_HSH                      (0x031D3818)

#define DDRCKECTL_CR_DDRCRCTLCONTROLS_REG                              (0x0000381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RefPi_OFF                      ( 0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RefPi_WID                      ( 4)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RefPi_MSK                      (0x0000000F)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RefPi_MIN                      (-8)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RefPi_MAX                      (7) // 0x00000007
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RefPi_DEF                      (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RefPi_HSH                      (0x8400381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllMask_OFF                    ( 4)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllMask_WID                    ( 2)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllMask_MSK                    (0x00000030)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllMask_MIN                    (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllMask_MAX                    (3) // 0x00000003
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllMask_DEF                    (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllMask_HSH                    (0x0204381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_ClkGateDisable_OFF             ( 6)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_ClkGateDisable_WID             ( 1)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_ClkGateDisable_MSK             (0x00000040)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_ClkGateDisable_MIN             (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_ClkGateDisable_MAX             (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_ClkGateDisable_DEF             (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_ClkGateDisable_HSH             (0x0106381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_TxOn_OFF                       ( 7)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_TxOn_WID                       ( 1)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_TxOn_MSK                       (0x00000080)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_TxOn_MIN                       (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_TxOn_MAX                       (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_TxOn_DEF                       (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_TxOn_HSH                       (0x0107381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IntClkOn_OFF                   ( 8)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IntClkOn_WID                   ( 1)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IntClkOn_MSK                   (0x00000100)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IntClkOn_MIN                   (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IntClkOn_MAX                   (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IntClkOn_DEF                   (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IntClkOn_HSH                   (0x0108381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RepClkOn_OFF                   ( 9)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RepClkOn_WID                   ( 1)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RepClkOn_MSK                   (0x00000200)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RepClkOn_MIN                   (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RepClkOn_MAX                   (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RepClkOn_DEF                   (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RepClkOn_HSH                   (0x0109381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IolbOrMisr_OFF                 (10)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IolbOrMisr_WID                 ( 1)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IolbOrMisr_MSK                 (0x00000400)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IolbOrMisr_MIN                 (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IolbOrMisr_MAX                 (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IolbOrMisr_DEF                 (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IolbOrMisr_HSH                 (0x010A381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IOLBHold_OFF                   (11)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IOLBHold_WID                   ( 1)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IOLBHold_MSK                   (0x00000800)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IOLBHold_MIN                   (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IOLBHold_MAX                   (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IOLBHold_DEF                   (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_IOLBHold_HSH                   (0x010B381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_OdtMode_OFF                    (12)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_OdtMode_WID                    ( 1)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_OdtMode_MSK                    (0x00001000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_OdtMode_MIN                    (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_OdtMode_MAX                    (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_OdtMode_DEF                    (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_OdtMode_HSH                    (0x010C381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CmdTxEq_OFF                    (13)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CmdTxEq_WID                    ( 2)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CmdTxEq_MSK                    (0x00006000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CmdTxEq_MIN                    (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CmdTxEq_MAX                    (3) // 0x00000003
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CmdTxEq_DEF                    (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CmdTxEq_HSH                    (0x020D381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_OFF             (15)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_WID             ( 2)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MSK             (0x00018000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MIN             (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MAX             (3) // 0x00000003
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_DEF             (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_HSH             (0x020F381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlTxEq_OFF                    (17)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlTxEq_WID                    ( 2)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlTxEq_MSK                    (0x00060000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlTxEq_MIN                    (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlTxEq_MAX                    (3) // 0x00000003
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlTxEq_DEF                    (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlTxEq_HSH                    (0x0211381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlSRDrv_OFF                   (19)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlSRDrv_WID                   ( 2)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlSRDrv_MSK                   (0x00180000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlSRDrv_MIN                   (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlSRDrv_MAX                   (3) // 0x00000003
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlSRDrv_DEF                   (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_CtlSRDrv_HSH                   (0x0213381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RxVref_OFF                     (21)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RxVref_WID                     ( 6)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RxVref_MSK                     (0x07E00000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RxVref_MIN                     (-32)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RxVref_MAX                     (31) // 0x0000001F
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RxVref_DEF                     (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_RxVref_HSH                     (0x8615381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_VccddqHi_OFF                   (27)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_VccddqHi_WID                   ( 1)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_VccddqHi_MSK                   (0x08000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_VccddqHi_MIN                   (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_VccddqHi_MAX                   (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_VccddqHi_DEF                   (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_VccddqHi_HSH                   (0x011B381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllWeakLock_OFF                (28)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllWeakLock_WID                ( 1)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllWeakLock_MSK                (0x10000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllWeakLock_MIN                (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllWeakLock_MAX                (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllWeakLock_DEF                (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_DllWeakLock_HSH                (0x011C381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDDR_Mode_OFF                 (29)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDDR_Mode_WID                 ( 1)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MSK                 (0x20000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MIN                 (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MAX                 (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDDR_Mode_DEF                 (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDDR_Mode_HSH                 (0x011D381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_OFF                (30)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_WID                ( 1)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MSK                (0x40000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MIN                (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MAX                (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_DEF                (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_HSH                (0x011E381C)

  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_OFF               (31)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_WID               ( 1)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MSK               (0x80000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MIN               (0)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MAX               (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_DEF               (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_HSH               (0x011F381C)

#define DDRCKECTL_CR_DDRCRCTLRANKSUSED_REG                             (0x00003820)

  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_RankEn_OFF                    ( 0)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_RankEn_WID                    ( 4)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_RankEn_MSK                    (0x0000000F)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_RankEn_MIN                    (0)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_RankEn_MAX                    (15) // 0x0000000F
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_RankEn_DEF                    (0x0000000F)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_RankEn_HSH                    (0x04003820)

  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_OdtDisable_OFF                ( 4)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_OdtDisable_WID                ( 2)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_OdtDisable_MSK                (0x00000030)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_OdtDisable_MIN                (0)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_OdtDisable_MAX                (3) // 0x00000003
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_OdtDisable_DEF                (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_OdtDisable_HSH                (0x02043820)

  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_OFF        ( 6)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_WID        ( 1)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MSK        (0x00000040)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MIN        (0)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_DEF        (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_HSH        (0x01063820)

  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_OFF        ( 7)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_WID        ( 1)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MSK        (0x00000080)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MIN        (0)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_DEF        (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_HSH        (0x01073820)

  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_OFF             ( 8)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_WID             ( 1)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MSK             (0x00000100)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MIN             (0)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MAX             (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_DEF             (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_HSH             (0x01083820)

  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsClkGateDis_OFF              ( 9)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsClkGateDis_WID              ( 1)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MSK              (0x00000200)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MIN              (0)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MAX              (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsClkGateDis_DEF              (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_CsClkGateDis_HSH              (0x01093820)

  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_Spare_OFF                     (10)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_Spare_WID                     (22)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_Spare_MSK                     (0xFFFFFC00)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_Spare_MIN                     (0)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_Spare_MAX                     (4194303) // 0x003FFFFF
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_Spare_DEF                     (0x00000000)
  #define DDRCKECTL_CR_DDRCRCTLRANKSUSED_Spare_HSH                     (0x160A3820)

#define DDRCKECTL_CR_DLLPITESTANDADC_REG                               (0x00003824)

  #define DDRCKECTL_CR_DLLPITESTANDADC_RunTest_OFF                     ( 0)
  #define DDRCKECTL_CR_DLLPITESTANDADC_RunTest_WID                     ( 1)
  #define DDRCKECTL_CR_DLLPITESTANDADC_RunTest_MSK                     (0x00000001)
  #define DDRCKECTL_CR_DLLPITESTANDADC_RunTest_MIN                     (0)
  #define DDRCKECTL_CR_DLLPITESTANDADC_RunTest_MAX                     (1) // 0x00000001
  #define DDRCKECTL_CR_DLLPITESTANDADC_RunTest_DEF                     (0x00000000)
  #define DDRCKECTL_CR_DLLPITESTANDADC_RunTest_HSH                     (0x01003824)

  #define DDRCKECTL_CR_DLLPITESTANDADC_Load_OFF                        ( 1)
  #define DDRCKECTL_CR_DLLPITESTANDADC_Load_WID                        ( 1)
  #define DDRCKECTL_CR_DLLPITESTANDADC_Load_MSK                        (0x00000002)
  #define DDRCKECTL_CR_DLLPITESTANDADC_Load_MIN                        (0)
  #define DDRCKECTL_CR_DLLPITESTANDADC_Load_MAX                        (1) // 0x00000001
  #define DDRCKECTL_CR_DLLPITESTANDADC_Load_DEF                        (0x00000000)
  #define DDRCKECTL_CR_DLLPITESTANDADC_Load_HSH                        (0x01013824)

  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeHVM_OFF                     ( 2)
  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeHVM_WID                     ( 1)
  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeHVM_MSK                     (0x00000004)
  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeHVM_MIN                     (0)
  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeHVM_MAX                     (1) // 0x00000001
  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeHVM_DEF                     (0x00000000)
  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeHVM_HSH                     (0x01023824)

  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeDV_OFF                      ( 3)
  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeDV_WID                      ( 1)
  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeDV_MSK                      (0x00000008)
  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeDV_MIN                      (0)
  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeDV_MAX                      (1) // 0x00000001
  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeDV_DEF                      (0x00000000)
  #define DDRCKECTL_CR_DLLPITESTANDADC_ModeDV_HSH                      (0x01033824)

  #define DDRCKECTL_CR_DLLPITESTANDADC_CalCfdl_OFF                     ( 4)
  #define DDRCKECTL_CR_DLLPITESTANDADC_CalCfdl_WID                     ( 1)
  #define DDRCKECTL_CR_DLLPITESTANDADC_CalCfdl_MSK                     (0x00000010)
  #define DDRCKECTL_CR_DLLPITESTANDADC_CalCfdl_MIN                     (0)
  #define DDRCKECTL_CR_DLLPITESTANDADC_CalCfdl_MAX                     (1) // 0x00000001
  #define DDRCKECTL_CR_DLLPITESTANDADC_CalCfdl_DEF                     (0x00000000)
  #define DDRCKECTL_CR_DLLPITESTANDADC_CalCfdl_HSH                     (0x01043824)

  #define DDRCKECTL_CR_DLLPITESTANDADC_LoadCount_OFF                   ( 5)
  #define DDRCKECTL_CR_DLLPITESTANDADC_LoadCount_WID                   (10)
  #define DDRCKECTL_CR_DLLPITESTANDADC_LoadCount_MSK                   (0x00007FE0)
  #define DDRCKECTL_CR_DLLPITESTANDADC_LoadCount_MIN                   (0)
  #define DDRCKECTL_CR_DLLPITESTANDADC_LoadCount_MAX                   (1023) // 0x000003FF
  #define DDRCKECTL_CR_DLLPITESTANDADC_LoadCount_DEF                   (0x00000000)
  #define DDRCKECTL_CR_DLLPITESTANDADC_LoadCount_HSH                   (0x0A053824)

  #define DDRCKECTL_CR_DLLPITESTANDADC_CountStatus_OFF                 (15)
  #define DDRCKECTL_CR_DLLPITESTANDADC_CountStatus_WID                 (10)
  #define DDRCKECTL_CR_DLLPITESTANDADC_CountStatus_MSK                 (0x01FF8000)
  #define DDRCKECTL_CR_DLLPITESTANDADC_CountStatus_MIN                 (0)
  #define DDRCKECTL_CR_DLLPITESTANDADC_CountStatus_MAX                 (1023) // 0x000003FF
  #define DDRCKECTL_CR_DLLPITESTANDADC_CountStatus_DEF                 (0x00000000)
  #define DDRCKECTL_CR_DLLPITESTANDADC_CountStatus_HSH                 (0x0A0F3824)

  #define DDRCKECTL_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF            (25)
  #define DDRCKECTL_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID            ( 1)
  #define DDRCKECTL_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK            (0x02000000)
  #define DDRCKECTL_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN            (0)
  #define DDRCKECTL_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX            (1) // 0x00000001
  #define DDRCKECTL_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF            (0x00000000)
  #define DDRCKECTL_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH            (0x01193824)

  #define DDRCKECTL_CR_DLLPITESTANDADC_Spare_OFF                       (26)
  #define DDRCKECTL_CR_DLLPITESTANDADC_Spare_WID                       ( 6)
  #define DDRCKECTL_CR_DLLPITESTANDADC_Spare_MSK                       (0xFC000000)
  #define DDRCKECTL_CR_DLLPITESTANDADC_Spare_MIN                       (0)
  #define DDRCKECTL_CR_DLLPITESTANDADC_Spare_MAX                       (63) // 0x0000003F
  #define DDRCKECTL_CR_DLLPITESTANDADC_Spare_DEF                       (0x00000000)
  #define DDRCKECTL_CR_DLLPITESTANDADC_Spare_HSH                       (0x061A3824)

#define DDRCKECTL_CR_DDRCMDMISR_REG                                    (0x00003828)

  #define DDRCKECTL_CR_DDRCMDMISR_shift_16_OFF                         ( 0)
  #define DDRCKECTL_CR_DDRCMDMISR_shift_16_WID                         ( 1)
  #define DDRCKECTL_CR_DDRCMDMISR_shift_16_MSK                         (0x00000001)
  #define DDRCKECTL_CR_DDRCMDMISR_shift_16_MIN                         (0)
  #define DDRCKECTL_CR_DDRCMDMISR_shift_16_MAX                         (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCMDMISR_shift_16_DEF                         (0x00000000)
  #define DDRCKECTL_CR_DDRCMDMISR_shift_16_HSH                         (0x01003828)

  #define DDRCKECTL_CR_DDRCMDMISR_clken_pulse_mode_OFF                 ( 1)
  #define DDRCKECTL_CR_DDRCMDMISR_clken_pulse_mode_WID                 ( 1)
  #define DDRCKECTL_CR_DDRCMDMISR_clken_pulse_mode_MSK                 (0x00000002)
  #define DDRCKECTL_CR_DDRCMDMISR_clken_pulse_mode_MIN                 (0)
  #define DDRCKECTL_CR_DDRCMDMISR_clken_pulse_mode_MAX                 (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCMDMISR_clken_pulse_mode_DEF                 (0x00000000)
  #define DDRCKECTL_CR_DDRCMDMISR_clken_pulse_mode_HSH                 (0x01013828)

  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_mode_OFF                   ( 2)
  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_mode_WID                   ( 1)
  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_mode_MSK                   (0x00000004)
  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_mode_MIN                   (0)
  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_mode_MAX                   (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_mode_DEF                   (0x00000000)
  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_mode_HSH                   (0x01023828)

  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_OFF                        ( 3)
  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_WID                        ( 1)
  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_MSK                        (0x00000008)
  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_MIN                        (0)
  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_MAX                        (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_DEF                        (0x00000000)
  #define DDRCKECTL_CR_DDRCMDMISR_reg_clken_HSH                        (0x01033828)

  #define DDRCKECTL_CR_DDRCMDMISR_feedback_en_OFF                      ( 4)
  #define DDRCKECTL_CR_DDRCMDMISR_feedback_en_WID                      ( 1)
  #define DDRCKECTL_CR_DDRCMDMISR_feedback_en_MSK                      (0x00000010)
  #define DDRCKECTL_CR_DDRCMDMISR_feedback_en_MIN                      (0)
  #define DDRCKECTL_CR_DDRCMDMISR_feedback_en_MAX                      (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCMDMISR_feedback_en_DEF                      (0x00000000)
  #define DDRCKECTL_CR_DDRCMDMISR_feedback_en_HSH                      (0x01043828)

  #define DDRCKECTL_CR_DDRCMDMISR_event_mode_OFF                       ( 5)
  #define DDRCKECTL_CR_DDRCMDMISR_event_mode_WID                       ( 1)
  #define DDRCKECTL_CR_DDRCMDMISR_event_mode_MSK                       (0x00000020)
  #define DDRCKECTL_CR_DDRCMDMISR_event_mode_MIN                       (0)
  #define DDRCKECTL_CR_DDRCMDMISR_event_mode_MAX                       (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCMDMISR_event_mode_DEF                       (0x00000000)
  #define DDRCKECTL_CR_DDRCMDMISR_event_mode_HSH                       (0x01053828)

  #define DDRCKECTL_CR_DDRCMDMISR_lfsr_reset_OFF                       ( 6)
  #define DDRCKECTL_CR_DDRCMDMISR_lfsr_reset_WID                       ( 1)
  #define DDRCKECTL_CR_DDRCMDMISR_lfsr_reset_MSK                       (0x00000040)
  #define DDRCKECTL_CR_DDRCMDMISR_lfsr_reset_MIN                       (0)
  #define DDRCKECTL_CR_DDRCMDMISR_lfsr_reset_MAX                       (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCMDMISR_lfsr_reset_DEF                       (0x00000000)
  #define DDRCKECTL_CR_DDRCMDMISR_lfsr_reset_HSH                       (0x01063828)

  #define DDRCKECTL_CR_DDRCMDMISR_sdo_en_OFF                           ( 7)
  #define DDRCKECTL_CR_DDRCMDMISR_sdo_en_WID                           ( 1)
  #define DDRCKECTL_CR_DDRCMDMISR_sdo_en_MSK                           (0x00000080)
  #define DDRCKECTL_CR_DDRCMDMISR_sdo_en_MIN                           (0)
  #define DDRCKECTL_CR_DDRCMDMISR_sdo_en_MAX                           (1) // 0x00000001
  #define DDRCKECTL_CR_DDRCMDMISR_sdo_en_DEF                           (0x00000000)
  #define DDRCKECTL_CR_DDRCMDMISR_sdo_en_HSH                           (0x01073828)

  #define DDRCKECTL_CR_DDRCMDMISR_cr_rd_data_OFF                       (16)
  #define DDRCKECTL_CR_DDRCMDMISR_cr_rd_data_WID                       (16)
  #define DDRCKECTL_CR_DDRCMDMISR_cr_rd_data_MSK                       (0xFFFF0000)
  #define DDRCKECTL_CR_DDRCMDMISR_cr_rd_data_MIN                       (0)
  #define DDRCKECTL_CR_DDRCMDMISR_cr_rd_data_MAX                       (65535) // 0x0000FFFF
  #define DDRCKECTL_CR_DDRCMDMISR_cr_rd_data_DEF                       (0x00000000)
  #define DDRCKECTL_CR_DDRCMDMISR_cr_rd_data_HSH                       (0x10103828)

#define DDRCLK_CR_DDRCRCLKRANKSUSED_REG                                (0x00003900)

  #define DDRCLK_CR_DDRCRCLKRANKSUSED_RankEn_OFF                       ( 0)
  #define DDRCLK_CR_DDRCRCLKRANKSUSED_RankEn_WID                       ( 4)
  #define DDRCLK_CR_DDRCRCLKRANKSUSED_RankEn_MSK                       (0x0000000F)
  #define DDRCLK_CR_DDRCRCLKRANKSUSED_RankEn_MIN                       (0)
  #define DDRCLK_CR_DDRCRCLKRANKSUSED_RankEn_MAX                       (15) // 0x0000000F
  #define DDRCLK_CR_DDRCRCLKRANKSUSED_RankEn_DEF                       (0x0000000F)
  #define DDRCLK_CR_DDRCRCLKRANKSUSED_RankEn_HSH                       (0x04003900)

  #define DDRCLK_CR_DDRCRCLKRANKSUSED_Spare_OFF                        ( 4)
  #define DDRCLK_CR_DDRCRCLKRANKSUSED_Spare_WID                        (28)
  #define DDRCLK_CR_DDRCRCLKRANKSUSED_Spare_MSK                        (0xFFFFFFF0)
  #define DDRCLK_CR_DDRCRCLKRANKSUSED_Spare_MIN                        (0)
  #define DDRCLK_CR_DDRCRCLKRANKSUSED_Spare_MAX                        (268435455) // 0x0FFFFFFF
  #define DDRCLK_CR_DDRCRCLKRANKSUSED_Spare_DEF                        (0x00000000)
  #define DDRCLK_CR_DDRCRCLKRANKSUSED_Spare_HSH                        (0x1C043900)

#define DDRCLK_CR_DDRCRCLKCOMP_REG                                     (0x00003904)

  #define DDRCLK_CR_DDRCRCLKCOMP_Scomp_OFF                             ( 0)
  #define DDRCLK_CR_DDRCRCLKCOMP_Scomp_WID                             ( 5)
  #define DDRCLK_CR_DDRCRCLKCOMP_Scomp_MSK                             (0x0000001F)
  #define DDRCLK_CR_DDRCRCLKCOMP_Scomp_MIN                             (0)
  #define DDRCLK_CR_DDRCRCLKCOMP_Scomp_MAX                             (31) // 0x0000001F
  #define DDRCLK_CR_DDRCRCLKCOMP_Scomp_DEF                             (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCOMP_Scomp_HSH                             (0x05003904)

  #define DDRCLK_CR_DDRCRCLKCOMP_TcoComp_OFF                           ( 5)
  #define DDRCLK_CR_DDRCRCLKCOMP_TcoComp_WID                           ( 6)
  #define DDRCLK_CR_DDRCRCLKCOMP_TcoComp_MSK                           (0x000007E0)
  #define DDRCLK_CR_DDRCRCLKCOMP_TcoComp_MIN                           (0)
  #define DDRCLK_CR_DDRCRCLKCOMP_TcoComp_MAX                           (63) // 0x0000003F
  #define DDRCLK_CR_DDRCRCLKCOMP_TcoComp_DEF                           (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCOMP_TcoComp_HSH                           (0x06053904)

  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvUp_OFF                        (11)
  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvUp_WID                        ( 6)
  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvUp_MSK                        (0x0001F800)
  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvUp_MIN                        (0)
  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvUp_MAX                        (63) // 0x0000003F
  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvUp_DEF                        (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvUp_HSH                        (0x060B3904)

  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvDown_OFF                      (17)
  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvDown_WID                      ( 6)
  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvDown_MSK                      (0x007E0000)
  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvDown_MIN                      (0)
  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvDown_MAX                      (63) // 0x0000003F
  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvDown_DEF                      (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCOMP_RcompDrvDown_HSH                      (0x06113904)

  #define DDRCLK_CR_DDRCRCLKCOMP_Spare_OFF                             (23)
  #define DDRCLK_CR_DDRCRCLKCOMP_Spare_WID                             ( 9)
  #define DDRCLK_CR_DDRCRCLKCOMP_Spare_MSK                             (0xFF800000)
  #define DDRCLK_CR_DDRCRCLKCOMP_Spare_MIN                             (0)
  #define DDRCLK_CR_DDRCRCLKCOMP_Spare_MAX                             (511) // 0x000001FF
  #define DDRCLK_CR_DDRCRCLKCOMP_Spare_DEF                             (0x00000003)
  #define DDRCLK_CR_DDRCRCLKCOMP_Spare_HSH                             (0x09173904)

#define DDRCLK_CR_DDRCRCLKCOMPOFFSET_REG                               (0x00003908)

  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_ScompOffset_OFF                 ( 0)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_ScompOffset_WID                 ( 4)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_ScompOffset_MSK                 (0x0000000F)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_ScompOffset_MIN                 (-8)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_ScompOffset_MAX                 (7) // 0x00000007
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_ScompOffset_DEF                 (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_ScompOffset_HSH                 (0x84003908)

  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_OFF               ( 4)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_WID               ( 4)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_MSK               (0x000000F0)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_MIN               (-8)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_MAX               (7) // 0x00000007
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_DEF               (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_HSH               (0x84043908)

  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_OFF            ( 8)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_WID            ( 4)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_MSK            (0x00000F00)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_MIN            (-8)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_MAX            (7) // 0x00000007
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_DEF            (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_HSH            (0x84083908)

  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_OFF          (12)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_WID          ( 4)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_MSK          (0x0000F000)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_MIN          (-8)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_MAX          (7) // 0x00000007
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_DEF          (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_HSH          (0x840C3908)

  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_Spare_OFF                       (16)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_Spare_WID                       (16)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_Spare_MSK                       (0xFFFF0000)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_Spare_MIN                       (0)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_Spare_MAX                       (65535) // 0x0000FFFF
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_Spare_DEF                       (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCOMPOFFSET_Spare_HSH                       (0x10103908)

#define DDRCLK_CR_DDRCRCLKPICODE_REG                                   (0x0000390C)

  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank0_OFF                  ( 0)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank0_WID                  ( 7)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank0_MSK                  (0x0000007F)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank0_MIN                  (0)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank0_MAX                  (127) // 0x0000007F
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank0_DEF                  (0x00000000)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank0_HSH                  (0x0700390C)

  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank1_OFF                  ( 7)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank1_WID                  ( 7)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank1_MSK                  (0x00003F80)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank1_MIN                  (0)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank1_MAX                  (127) // 0x0000007F
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank1_DEF                  (0x00000000)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank1_HSH                  (0x0707390C)

  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank2_OFF                  (14)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank2_WID                  ( 7)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank2_MSK                  (0x001FC000)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank2_MIN                  (0)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank2_MAX                  (127) // 0x0000007F
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank2_DEF                  (0x00000000)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank2_HSH                  (0x070E390C)

  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank3_OFF                  (21)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank3_WID                  ( 7)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank3_MSK                  (0x0FE00000)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank3_MIN                  (0)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank3_MAX                  (127) // 0x0000007F
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank3_DEF                  (0x00000000)
  #define DDRCLK_CR_DDRCRCLKPICODE_PiSettingRank3_HSH                  (0x0715390C)

  #define DDRCLK_CR_DDRCRCLKPICODE_Spare_OFF                           (28)
  #define DDRCLK_CR_DDRCRCLKPICODE_Spare_WID                           ( 4)
  #define DDRCLK_CR_DDRCRCLKPICODE_Spare_MSK                           (0xF0000000)
  #define DDRCLK_CR_DDRCRCLKPICODE_Spare_MIN                           (0)
  #define DDRCLK_CR_DDRCRCLKPICODE_Spare_MAX                           (15) // 0x0000000F
  #define DDRCLK_CR_DDRCRCLKPICODE_Spare_DEF                           (0x00000000)
  #define DDRCLK_CR_DDRCRCLKPICODE_Spare_HSH                           (0x041C390C)

#define DDRCLK_CR_DDRCRCLKCONTROLS_REG                                 (0x00003910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_RefPi_OFF                         ( 0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RefPi_WID                         ( 4)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RefPi_MSK                         (0x0000000F)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RefPi_MIN                         (-8)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RefPi_MAX                         (7) // 0x00000007
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RefPi_DEF                         (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RefPi_HSH                         (0x84003910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllMask_OFF                       ( 4)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllMask_WID                       ( 2)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllMask_MSK                       (0x00000030)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllMask_MIN                       (0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllMask_MAX                       (3) // 0x00000003
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllMask_DEF                       (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllMask_HSH                       (0x02043910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllRsvd1_OFF                      ( 6)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllRsvd1_WID                      ( 1)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllRsvd1_MSK                      (0x00000040)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllRsvd1_MIN                      (0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllRsvd1_MAX                      (1) // 0x00000001
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllRsvd1_DEF                      (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllRsvd1_HSH                      (0x01063910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_TxOn_OFF                          ( 7)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_TxOn_WID                          ( 1)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_TxOn_MSK                          (0x00000080)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_TxOn_MIN                          (0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_TxOn_MAX                          (1) // 0x00000001
  #define DDRCLK_CR_DDRCRCLKCONTROLS_TxOn_DEF                          (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_TxOn_HSH                          (0x01073910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_IntClkOn_OFF                      ( 8)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_IntClkOn_WID                      ( 1)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_IntClkOn_MSK                      (0x00000100)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_IntClkOn_MIN                      (0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_IntClkOn_MAX                      (1) // 0x00000001
  #define DDRCLK_CR_DDRCRCLKCONTROLS_IntClkOn_DEF                      (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_IntClkOn_HSH                      (0x01083910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_RepClkOn_OFF                      ( 9)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RepClkOn_WID                      ( 1)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RepClkOn_MSK                      (0x00000200)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RepClkOn_MIN                      (0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RepClkOn_MAX                      (1) // 0x00000001
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RepClkOn_DEF                      (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RepClkOn_HSH                      (0x01093910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_IOLBCtl_OFF                       (10)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_IOLBCtl_WID                       ( 2)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_IOLBCtl_MSK                       (0x00000C00)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_IOLBCtl_MIN                       (0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_IOLBCtl_MAX                       (3) // 0x00000003
  #define DDRCLK_CR_DDRCRCLKCONTROLS_IOLBCtl_DEF                       (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_IOLBCtl_HSH                       (0x020A3910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_OdtMode_OFF                       (12)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_OdtMode_WID                       ( 1)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_OdtMode_MSK                       (0x00001000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_OdtMode_MIN                       (0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_OdtMode_MAX                       (1) // 0x00000001
  #define DDRCLK_CR_DDRCRCLKCONTROLS_OdtMode_DEF                       (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_OdtMode_HSH                       (0x010C3910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_Reserved_OFF                      (13)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_Reserved_WID                      ( 8)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_Reserved_MSK                      (0x001FE000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_Reserved_MIN                      (0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_Reserved_MAX                      (255) // 0x000000FF
  #define DDRCLK_CR_DDRCRCLKCONTROLS_Reserved_DEF                      (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_Reserved_HSH                      (0x080D3910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_RxVref_OFF                        (21)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RxVref_WID                        ( 6)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RxVref_MSK                        (0x07E00000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RxVref_MIN                        (-32)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RxVref_MAX                        (31) // 0x0000001F
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RxVref_DEF                        (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_RxVref_HSH                        (0x86153910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_VccddqHi_OFF                      (27)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_VccddqHi_WID                      ( 1)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_VccddqHi_MSK                      (0x08000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_VccddqHi_MIN                      (0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_VccddqHi_MAX                      (1) // 0x00000001
  #define DDRCLK_CR_DDRCRCLKCONTROLS_VccddqHi_DEF                      (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_VccddqHi_HSH                      (0x011B3910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllWeakLock_OFF                   (28)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllWeakLock_WID                   ( 1)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllWeakLock_MSK                   (0x10000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllWeakLock_MIN                   (0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllWeakLock_MAX                   (1) // 0x00000001
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllWeakLock_DEF                   (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_DllWeakLock_HSH                   (0x011C3910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDDR_Mode_OFF                    (29)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDDR_Mode_WID                    ( 1)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDDR_Mode_MSK                    (0x20000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDDR_Mode_MIN                    (0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDDR_Mode_MAX                    (1) // 0x00000001
  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDDR_Mode_DEF                    (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDDR_Mode_HSH                    (0x011D3910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_OFF               (30)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_WID               ( 1)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_MSK               (0x40000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_MIN               (0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_MAX               (1) // 0x00000001
  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_DEF               (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_HSH               (0x011E3910)

  #define DDRCLK_CR_DDRCRCLKCONTROLS_ClkGateDisable_OFF                (31)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_ClkGateDisable_WID                ( 1)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_ClkGateDisable_MSK                (0x80000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_ClkGateDisable_MIN                (0)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_ClkGateDisable_MAX                (1) // 0x00000001
  #define DDRCLK_CR_DDRCRCLKCONTROLS_ClkGateDisable_DEF                (0x00000000)
  #define DDRCLK_CR_DDRCRCLKCONTROLS_ClkGateDisable_HSH                (0x011F3910)

#define DDRCLK_CR_DLLPITESTANDADC_REG                                  (0x00003914)

  #define DDRCLK_CR_DLLPITESTANDADC_RunTest_OFF                        ( 0)
  #define DDRCLK_CR_DLLPITESTANDADC_RunTest_WID                        ( 1)
  #define DDRCLK_CR_DLLPITESTANDADC_RunTest_MSK                        (0x00000001)
  #define DDRCLK_CR_DLLPITESTANDADC_RunTest_MIN                        (0)
  #define DDRCLK_CR_DLLPITESTANDADC_RunTest_MAX                        (1) // 0x00000001
  #define DDRCLK_CR_DLLPITESTANDADC_RunTest_DEF                        (0x00000000)
  #define DDRCLK_CR_DLLPITESTANDADC_RunTest_HSH                        (0x01003914)

  #define DDRCLK_CR_DLLPITESTANDADC_Load_OFF                           ( 1)
  #define DDRCLK_CR_DLLPITESTANDADC_Load_WID                           ( 1)
  #define DDRCLK_CR_DLLPITESTANDADC_Load_MSK                           (0x00000002)
  #define DDRCLK_CR_DLLPITESTANDADC_Load_MIN                           (0)
  #define DDRCLK_CR_DLLPITESTANDADC_Load_MAX                           (1) // 0x00000001
  #define DDRCLK_CR_DLLPITESTANDADC_Load_DEF                           (0x00000000)
  #define DDRCLK_CR_DLLPITESTANDADC_Load_HSH                           (0x01013914)

  #define DDRCLK_CR_DLLPITESTANDADC_ModeHVM_OFF                        ( 2)
  #define DDRCLK_CR_DLLPITESTANDADC_ModeHVM_WID                        ( 1)
  #define DDRCLK_CR_DLLPITESTANDADC_ModeHVM_MSK                        (0x00000004)
  #define DDRCLK_CR_DLLPITESTANDADC_ModeHVM_MIN                        (0)
  #define DDRCLK_CR_DLLPITESTANDADC_ModeHVM_MAX                        (1) // 0x00000001
  #define DDRCLK_CR_DLLPITESTANDADC_ModeHVM_DEF                        (0x00000000)
  #define DDRCLK_CR_DLLPITESTANDADC_ModeHVM_HSH                        (0x01023914)

  #define DDRCLK_CR_DLLPITESTANDADC_ModeDV_OFF                         ( 3)
  #define DDRCLK_CR_DLLPITESTANDADC_ModeDV_WID                         ( 1)
  #define DDRCLK_CR_DLLPITESTANDADC_ModeDV_MSK                         (0x00000008)
  #define DDRCLK_CR_DLLPITESTANDADC_ModeDV_MIN                         (0)
  #define DDRCLK_CR_DLLPITESTANDADC_ModeDV_MAX                         (1) // 0x00000001
  #define DDRCLK_CR_DLLPITESTANDADC_ModeDV_DEF                         (0x00000000)
  #define DDRCLK_CR_DLLPITESTANDADC_ModeDV_HSH                         (0x01033914)

  #define DDRCLK_CR_DLLPITESTANDADC_CalCfdl_OFF                        ( 4)
  #define DDRCLK_CR_DLLPITESTANDADC_CalCfdl_WID                        ( 1)
  #define DDRCLK_CR_DLLPITESTANDADC_CalCfdl_MSK                        (0x00000010)
  #define DDRCLK_CR_DLLPITESTANDADC_CalCfdl_MIN                        (0)
  #define DDRCLK_CR_DLLPITESTANDADC_CalCfdl_MAX                        (1) // 0x00000001
  #define DDRCLK_CR_DLLPITESTANDADC_CalCfdl_DEF                        (0x00000000)
  #define DDRCLK_CR_DLLPITESTANDADC_CalCfdl_HSH                        (0x01043914)

  #define DDRCLK_CR_DLLPITESTANDADC_LoadCount_OFF                      ( 5)
  #define DDRCLK_CR_DLLPITESTANDADC_LoadCount_WID                      (10)
  #define DDRCLK_CR_DLLPITESTANDADC_LoadCount_MSK                      (0x00007FE0)
  #define DDRCLK_CR_DLLPITESTANDADC_LoadCount_MIN                      (0)
  #define DDRCLK_CR_DLLPITESTANDADC_LoadCount_MAX                      (1023) // 0x000003FF
  #define DDRCLK_CR_DLLPITESTANDADC_LoadCount_DEF                      (0x00000000)
  #define DDRCLK_CR_DLLPITESTANDADC_LoadCount_HSH                      (0x0A053914)

  #define DDRCLK_CR_DLLPITESTANDADC_CountStatus_OFF                    (15)
  #define DDRCLK_CR_DLLPITESTANDADC_CountStatus_WID                    (10)
  #define DDRCLK_CR_DLLPITESTANDADC_CountStatus_MSK                    (0x01FF8000)
  #define DDRCLK_CR_DLLPITESTANDADC_CountStatus_MIN                    (0)
  #define DDRCLK_CR_DLLPITESTANDADC_CountStatus_MAX                    (1023) // 0x000003FF
  #define DDRCLK_CR_DLLPITESTANDADC_CountStatus_DEF                    (0x00000000)
  #define DDRCLK_CR_DLLPITESTANDADC_CountStatus_HSH                    (0x0A0F3914)

  #define DDRCLK_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF               (25)
  #define DDRCLK_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID               ( 1)
  #define DDRCLK_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK               (0x02000000)
  #define DDRCLK_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN               (0)
  #define DDRCLK_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX               (1) // 0x00000001
  #define DDRCLK_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF               (0x00000000)
  #define DDRCLK_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH               (0x01193914)

  #define DDRCLK_CR_DLLPITESTANDADC_Spare_OFF                          (26)
  #define DDRCLK_CR_DLLPITESTANDADC_Spare_WID                          ( 6)
  #define DDRCLK_CR_DLLPITESTANDADC_Spare_MSK                          (0xFC000000)
  #define DDRCLK_CR_DLLPITESTANDADC_Spare_MIN                          (0)
  #define DDRCLK_CR_DLLPITESTANDADC_Spare_MAX                          (63) // 0x0000003F
  #define DDRCLK_CR_DLLPITESTANDADC_Spare_DEF                          (0x00000000)
  #define DDRCLK_CR_DLLPITESTANDADC_Spare_HSH                          (0x061A3914)

#define DDRCLK_CR_DDRCBSTATUS_REG                                      (0x00003918)

  #define DDRCLK_CR_DDRCBSTATUS_DllCB_OFF                              ( 0)
  #define DDRCLK_CR_DDRCBSTATUS_DllCB_WID                              ( 2)
  #define DDRCLK_CR_DDRCBSTATUS_DllCB_MSK                              (0x00000003)
  #define DDRCLK_CR_DDRCBSTATUS_DllCB_MIN                              (0)
  #define DDRCLK_CR_DDRCBSTATUS_DllCB_MAX                              (3) // 0x00000003
  #define DDRCLK_CR_DDRCBSTATUS_DllCB_DEF                              (0x00000000)
  #define DDRCLK_CR_DDRCBSTATUS_DllCB_HSH                              (0x02003918)

  #define DDRCLK_CR_DDRCBSTATUS_Spare_OFF                              ( 2)
  #define DDRCLK_CR_DDRCBSTATUS_Spare_WID                              (30)
  #define DDRCLK_CR_DDRCBSTATUS_Spare_MSK                              (0xFFFFFFFC)
  #define DDRCLK_CR_DDRCBSTATUS_Spare_MIN                              (0)
  #define DDRCLK_CR_DDRCBSTATUS_Spare_MAX                              (1073741823) // 0x3FFFFFFF
  #define DDRCLK_CR_DDRCBSTATUS_Spare_DEF                              (0x00000000)
  #define DDRCLK_CR_DDRCBSTATUS_Spare_HSH                              (0x1E023918)

#define DDRCLK_CR_DDR4CRBSCANDATA_REG                                  (0x0000391C)

  #define DDRCLK_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_OFF           ( 0)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_WID           ( 1)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_MSK           (0x00000001)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_MIN           (0)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_MAX           (1) // 0x00000001
  #define DDRCLK_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_DEF           (0x00000000)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_HSH           (0x0100391C)

  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkP_OFF                      ( 1)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkP_WID                      ( 4)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkP_MSK                      (0x0000001E)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkP_MIN                      (0)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkP_MAX                      (15) // 0x0000000F
  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkP_DEF                      (0x00000000)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkP_HSH                      (0x0401391C)

  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkN_OFF                      ( 5)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkN_WID                      ( 4)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkN_MSK                      (0x000001E0)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkN_MIN                      (0)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkN_MAX                      (15) // 0x0000000F
  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkN_DEF                      (0x00000000)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Data_ClkN_HSH                      (0x0405391C)

  #define DDRCLK_CR_DDR4CRBSCANDATA_Spare_OFF                          ( 9)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Spare_WID                          (23)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Spare_MSK                          (0xFFFFFE00)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Spare_MIN                          (0)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Spare_MAX                          (8388607) // 0x007FFFFF
  #define DDRCLK_CR_DDR4CRBSCANDATA_Spare_DEF                          (0x00000000)
  #define DDRCLK_CR_DDR4CRBSCANDATA_Spare_HSH                          (0x1709391C)

#define DDRCLK_CR_DDRVSSHICOMPCTL_REG                                  (0x00003920)

  #define DDRCLK_CR_DDRVSSHICOMPCTL_Rsvd_OFF                           ( 0)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Rsvd_WID                           (11)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Rsvd_MSK                           (0x000007FF)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Rsvd_MIN                           (0)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Rsvd_MAX                           (2047) // 0x000007FF
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Rsvd_DEF                           (0x00000000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Rsvd_HSH                           (0x0B003920)

  #define DDRCLK_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_OFF                 (11)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_WID                 ( 1)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_MSK                 (0x00000800)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_MIN                 (0)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_MAX                 (1) // 0x00000001
  #define DDRCLK_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_DEF                 (0x00000000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_HSH                 (0x010B3920)

  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdEn_OFF                     (12)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdEn_WID                     ( 1)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdEn_MSK                     (0x00001000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdEn_MIN                     (0)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdEn_MAX                     (1) // 0x00000001
  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdEn_DEF                     (0x00000000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdEn_HSH                     (0x010C3920)

  #define DDRCLK_CR_DDRVSSHICOMPCTL_ViewOfstsel_OFF                    (13)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_ViewOfstsel_WID                    ( 3)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_ViewOfstsel_MSK                    (0x0000E000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_ViewOfstsel_MIN                    (0)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_ViewOfstsel_MAX                    (7) // 0x00000007
  #define DDRCLK_CR_DDRVSSHICOMPCTL_ViewOfstsel_DEF                    (0x00000000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_ViewOfstsel_HSH                    (0x030D3920)

  #define DDRCLK_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_OFF              (16)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_WID              ( 1)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_MSK              (0x00010000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_MIN              (0)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_MAX              (1) // 0x00000001
  #define DDRCLK_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_DEF              (0x00000000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_HSH              (0x01103920)

  #define DDRCLK_CR_DDRVSSHICOMPCTL_Spares_OFF                         (17)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Spares_WID                         ( 8)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Spares_MSK                         (0x01FE0000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Spares_MIN                         (0)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Spares_MAX                         (255) // 0x000000FF
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Spares_DEF                         (0x00000000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Spares_HSH                         (0x08113920)

  #define DDRCLK_CR_DDRVSSHICOMPCTL_Disable2Vt_OFF                     (25)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Disable2Vt_WID                     ( 1)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Disable2Vt_MSK                     (0x02000000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Disable2Vt_MIN                     (0)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Disable2Vt_MAX                     (1) // 0x00000001
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Disable2Vt_DEF                     (0x00000000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_Disable2Vt_HSH                     (0x01193920)

  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_OFF                 (26)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_WID                 ( 6)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_MSK                 (0xFC000000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_MIN                 (0)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_MAX                 (63) // 0x0000003F
  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_DEF                 (0x00000000)
  #define DDRCLK_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_HSH                 (0x061A3920)

#define DDRCOMP_CR_DDRCRDATACOMP0_REG                                  (0x00003A00)

  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvUp_OFF                     ( 0)
  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvUp_WID                     ( 6)
  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvUp_MSK                     (0x0000003F)
  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvUp_MIN                     (0)
  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvUp_HSH                     (0x06003A00)

  #define DDRCOMP_CR_DDRCRDATACOMP0_Rsvd_OFF                           ( 6)
  #define DDRCOMP_CR_DDRCRDATACOMP0_Rsvd_WID                           ( 3)
  #define DDRCOMP_CR_DDRCRDATACOMP0_Rsvd_MSK                           (0x000001C0)
  #define DDRCOMP_CR_DDRCRDATACOMP0_Rsvd_MIN                           (0)
  #define DDRCOMP_CR_DDRCRDATACOMP0_Rsvd_MAX                           (7) // 0x00000007
  #define DDRCOMP_CR_DDRCRDATACOMP0_Rsvd_DEF                           (0x00000000)
  #define DDRCOMP_CR_DDRCRDATACOMP0_Rsvd_HSH                           (0x03063A00)

  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvDown_OFF                   ( 9)
  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvDown_WID                   ( 6)
  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvDown_MSK                   (0x00007E00)
  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvDown_MIN                   (0)
  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCOMP_CR_DDRCRDATACOMP0_RcompDrvDown_HSH                   (0x06093A00)

  #define DDRCOMP_CR_DDRCRDATACOMP0_VTComp_OFF                         (15)
  #define DDRCOMP_CR_DDRCRDATACOMP0_VTComp_WID                         ( 5)
  #define DDRCOMP_CR_DDRCRDATACOMP0_VTComp_MSK                         (0x000F8000)
  #define DDRCOMP_CR_DDRCRDATACOMP0_VTComp_MIN                         (0)
  #define DDRCOMP_CR_DDRCRDATACOMP0_VTComp_MAX                         (31) // 0x0000001F
  #define DDRCOMP_CR_DDRCRDATACOMP0_VTComp_DEF                         (0x00000005)
  #define DDRCOMP_CR_DDRCRDATACOMP0_VTComp_HSH                         (0x050F3A00)

  #define DDRCOMP_CR_DDRCRDATACOMP0_SlewRateComp_OFF                   (20)
  #define DDRCOMP_CR_DDRCRDATACOMP0_SlewRateComp_WID                   ( 5)
  #define DDRCOMP_CR_DDRCRDATACOMP0_SlewRateComp_MSK                   (0x01F00000)
  #define DDRCOMP_CR_DDRCRDATACOMP0_SlewRateComp_MIN                   (0)
  #define DDRCOMP_CR_DDRCRDATACOMP0_SlewRateComp_MAX                   (31) // 0x0000001F
  #define DDRCOMP_CR_DDRCRDATACOMP0_SlewRateComp_DEF                   (0x00000000)
  #define DDRCOMP_CR_DDRCRDATACOMP0_SlewRateComp_HSH                   (0x05143A00)

  #define DDRCOMP_CR_DDRCRDATACOMP0_Spare_OFF                          (25)
  #define DDRCOMP_CR_DDRCRDATACOMP0_Spare_WID                          ( 1)
  #define DDRCOMP_CR_DDRCRDATACOMP0_Spare_MSK                          (0x02000000)
  #define DDRCOMP_CR_DDRCRDATACOMP0_Spare_MIN                          (0)
  #define DDRCOMP_CR_DDRCRDATACOMP0_Spare_MAX                          (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRDATACOMP0_Spare_DEF                          (0x00000000)
  #define DDRCOMP_CR_DDRCRDATACOMP0_Spare_HSH                          (0x01193A00)

  #define DDRCOMP_CR_DDRCRDATACOMP0_TcoComp_OFF                        (26)
  #define DDRCOMP_CR_DDRCRDATACOMP0_TcoComp_WID                        ( 6)
  #define DDRCOMP_CR_DDRCRDATACOMP0_TcoComp_MSK                        (0xFC000000)
  #define DDRCOMP_CR_DDRCRDATACOMP0_TcoComp_MIN                        (0)
  #define DDRCOMP_CR_DDRCRDATACOMP0_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRDATACOMP0_TcoComp_DEF                        (0x00000000)
  #define DDRCOMP_CR_DDRCRDATACOMP0_TcoComp_HSH                        (0x061A3A00)

#define DDRCOMP_CR_DDRCRDATACOMP1_REG                                  (0x00003A04)

  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtUp_OFF                     ( 0)
  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtUp_WID                     ( 6)
  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtUp_MSK                     (0x0000003F)
  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtUp_MIN                     (0)
  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtUp_MAX                     (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtUp_DEF                     (0x00000000)
  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtUp_HSH                     (0x06003A04)

  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvDn_OFF                     ( 6)
  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvDn_WID                     (10)
  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvDn_MSK                     (0x0000FFC0)
  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvDn_MIN                     (0)
  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvDn_MAX                     (1023) // 0x000003FF
  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvDn_DEF                     (0x00000094)
  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvDn_HSH                     (0x0A063A04)

  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvUp_OFF                     (16)
  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvUp_WID                     (10)
  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvUp_MSK                     (0x03FF0000)
  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvUp_MIN                     (0)
  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvUp_MAX                     (1023) // 0x000003FF
  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvUp_DEF                     (0x00000094)
  #define DDRCOMP_CR_DDRCRDATACOMP1_PanicDrvUp_HSH                     (0x0A103A04)

  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtDown_OFF                   (26)
  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtDown_WID                   ( 6)
  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtDown_MSK                   (0xFC000000)
  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtDown_MIN                   (0)
  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtDown_MAX                   (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtDown_DEF                   (0x00000000)
  #define DDRCOMP_CR_DDRCRDATACOMP1_RcompOdtDown_HSH                   (0x061A3A04)

#define DDRCOMP_CR_DDRCRCMDCOMP_REG                                    (0x00003A08)

  #define DDRCOMP_CR_DDRCRCMDCOMP_Scomp_OFF                            ( 0)
  #define DDRCOMP_CR_DDRCRCMDCOMP_Scomp_WID                            ( 6)
  #define DDRCOMP_CR_DDRCRCMDCOMP_Scomp_MSK                            (0x0000003F)
  #define DDRCOMP_CR_DDRCRCMDCOMP_Scomp_MIN                            (0)
  #define DDRCOMP_CR_DDRCRCMDCOMP_Scomp_MAX                            (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCMDCOMP_Scomp_DEF                            (0x00000000)
  #define DDRCOMP_CR_DDRCRCMDCOMP_Scomp_HSH                            (0x06003A08)

  #define DDRCOMP_CR_DDRCRCMDCOMP_TcoComp_OFF                          ( 6)
  #define DDRCOMP_CR_DDRCRCMDCOMP_TcoComp_WID                          ( 6)
  #define DDRCOMP_CR_DDRCRCMDCOMP_TcoComp_MSK                          (0x00000FC0)
  #define DDRCOMP_CR_DDRCRCMDCOMP_TcoComp_MIN                          (0)
  #define DDRCOMP_CR_DDRCRCMDCOMP_TcoComp_MAX                          (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCMDCOMP_TcoComp_DEF                          (0x00000000)
  #define DDRCOMP_CR_DDRCRCMDCOMP_TcoComp_HSH                          (0x06063A08)

  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvUp_OFF                       (12)
  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvUp_WID                       ( 6)
  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvUp_MSK                       (0x0003F000)
  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvUp_MIN                       (0)
  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvUp_MAX                       (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvUp_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvUp_HSH                       (0x060C3A08)

  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvDown_OFF                     (18)
  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvDown_WID                     ( 6)
  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvDown_MSK                     (0x00FC0000)
  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvDown_MIN                     (0)
  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvDown_MAX                     (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvDown_DEF                     (0x00000000)
  #define DDRCOMP_CR_DDRCRCMDCOMP_RcompDrvDown_HSH                     (0x06123A08)

  #define DDRCOMP_CR_DDRCRCMDCOMP_Spare_OFF                            (24)
  #define DDRCOMP_CR_DDRCRCMDCOMP_Spare_WID                            ( 8)
  #define DDRCOMP_CR_DDRCRCMDCOMP_Spare_MSK                            (0xFF000000)
  #define DDRCOMP_CR_DDRCRCMDCOMP_Spare_MIN                            (0)
  #define DDRCOMP_CR_DDRCRCMDCOMP_Spare_MAX                            (255) // 0x000000FF
  #define DDRCOMP_CR_DDRCRCMDCOMP_Spare_DEF                            (0x00000004)
  #define DDRCOMP_CR_DDRCRCMDCOMP_Spare_HSH                            (0x08183A08)

#define DDRCOMP_CR_DDRCRCTLCOMP_REG                                    (0x00003A0C)

  #define DDRCOMP_CR_DDRCRCTLCOMP_Scomp_OFF                            ( 0)
  #define DDRCOMP_CR_DDRCRCTLCOMP_Scomp_WID                            ( 6)
  #define DDRCOMP_CR_DDRCRCTLCOMP_Scomp_MSK                            (0x0000003F)
  #define DDRCOMP_CR_DDRCRCTLCOMP_Scomp_MIN                            (0)
  #define DDRCOMP_CR_DDRCRCTLCOMP_Scomp_MAX                            (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCTLCOMP_Scomp_DEF                            (0x00000000)
  #define DDRCOMP_CR_DDRCRCTLCOMP_Scomp_HSH                            (0x06003A0C)

  #define DDRCOMP_CR_DDRCRCTLCOMP_TcoComp_OFF                          ( 6)
  #define DDRCOMP_CR_DDRCRCTLCOMP_TcoComp_WID                          ( 6)
  #define DDRCOMP_CR_DDRCRCTLCOMP_TcoComp_MSK                          (0x00000FC0)
  #define DDRCOMP_CR_DDRCRCTLCOMP_TcoComp_MIN                          (0)
  #define DDRCOMP_CR_DDRCRCTLCOMP_TcoComp_MAX                          (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCTLCOMP_TcoComp_DEF                          (0x00000000)
  #define DDRCOMP_CR_DDRCRCTLCOMP_TcoComp_HSH                          (0x06063A0C)

  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvUp_OFF                       (12)
  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvUp_WID                       ( 6)
  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvUp_MSK                       (0x0003F000)
  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvUp_MIN                       (0)
  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvUp_MAX                       (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvUp_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvUp_HSH                       (0x060C3A0C)

  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvDown_OFF                     (18)
  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvDown_WID                     ( 6)
  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvDown_MSK                     (0x00FC0000)
  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvDown_MIN                     (0)
  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvDown_MAX                     (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvDown_DEF                     (0x00000000)
  #define DDRCOMP_CR_DDRCRCTLCOMP_RcompDrvDown_HSH                     (0x06123A0C)

  #define DDRCOMP_CR_DDRCRCTLCOMP_Spare_OFF                            (24)
  #define DDRCOMP_CR_DDRCRCTLCOMP_Spare_WID                            ( 8)
  #define DDRCOMP_CR_DDRCRCTLCOMP_Spare_MSK                            (0xFF000000)
  #define DDRCOMP_CR_DDRCRCTLCOMP_Spare_MIN                            (0)
  #define DDRCOMP_CR_DDRCRCTLCOMP_Spare_MAX                            (255) // 0x000000FF
  #define DDRCOMP_CR_DDRCRCTLCOMP_Spare_DEF                            (0x00000000)
  #define DDRCOMP_CR_DDRCRCTLCOMP_Spare_HSH                            (0x08183A0C)

#define DDRCOMP_CR_DDRCRCLKCOMP_REG                                    (0x00003A10)

  #define DDRCOMP_CR_DDRCRCLKCOMP_Scomp_OFF                            ( 0)
  #define DDRCOMP_CR_DDRCRCLKCOMP_Scomp_WID                            ( 5)
  #define DDRCOMP_CR_DDRCRCLKCOMP_Scomp_MSK                            (0x0000001F)
  #define DDRCOMP_CR_DDRCRCLKCOMP_Scomp_MIN                            (0)
  #define DDRCOMP_CR_DDRCRCLKCOMP_Scomp_MAX                            (31) // 0x0000001F
  #define DDRCOMP_CR_DDRCRCLKCOMP_Scomp_DEF                            (0x00000000)
  #define DDRCOMP_CR_DDRCRCLKCOMP_Scomp_HSH                            (0x05003A10)

  #define DDRCOMP_CR_DDRCRCLKCOMP_TcoComp_OFF                          ( 5)
  #define DDRCOMP_CR_DDRCRCLKCOMP_TcoComp_WID                          ( 6)
  #define DDRCOMP_CR_DDRCRCLKCOMP_TcoComp_MSK                          (0x000007E0)
  #define DDRCOMP_CR_DDRCRCLKCOMP_TcoComp_MIN                          (0)
  #define DDRCOMP_CR_DDRCRCLKCOMP_TcoComp_MAX                          (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCLKCOMP_TcoComp_DEF                          (0x00000000)
  #define DDRCOMP_CR_DDRCRCLKCOMP_TcoComp_HSH                          (0x06053A10)

  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvUp_OFF                       (11)
  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvUp_WID                       ( 6)
  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvUp_MSK                       (0x0001F800)
  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvUp_MIN                       (0)
  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvUp_MAX                       (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvUp_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvUp_HSH                       (0x060B3A10)

  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvDown_OFF                     (17)
  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvDown_WID                     ( 6)
  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvDown_MSK                     (0x007E0000)
  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvDown_MIN                     (0)
  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvDown_MAX                     (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvDown_DEF                     (0x00000000)
  #define DDRCOMP_CR_DDRCRCLKCOMP_RcompDrvDown_HSH                     (0x06113A10)

  #define DDRCOMP_CR_DDRCRCLKCOMP_Spare_OFF                            (23)
  #define DDRCOMP_CR_DDRCRCLKCOMP_Spare_WID                            ( 9)
  #define DDRCOMP_CR_DDRCRCLKCOMP_Spare_MSK                            (0xFF800000)
  #define DDRCOMP_CR_DDRCRCLKCOMP_Spare_MIN                            (0)
  #define DDRCOMP_CR_DDRCRCLKCOMP_Spare_MAX                            (511) // 0x000001FF
  #define DDRCOMP_CR_DDRCRCLKCOMP_Spare_DEF                            (0x00000003)
  #define DDRCOMP_CR_DDRCRCLKCOMP_Spare_HSH                            (0x09173A10)

#define DDRCOMP_CR_DDRCRCOMPCTL0_REG                                   (0x00003A14)

  #define DDRCOMP_CR_DDRCRCOMPCTL0_En200ohmVsshiPncUp_OFF              ( 0)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_En200ohmVsshiPncUp_WID              ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_En200ohmVsshiPncUp_MSK              (0x00000001)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_En200ohmVsshiPncUp_MIN              (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_En200ohmVsshiPncUp_MAX              (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL0_En200ohmVsshiPncUp_DEF              (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_En200ohmVsshiPncUp_HSH              (0x01003A14)

  #define DDRCOMP_CR_DDRCRCOMPCTL0_Spare_OFF                           ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_Spare_WID                           ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_Spare_MSK                           (0x00000002)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_Spare_MIN                           (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_Spare_MAX                           (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL0_Spare_DEF                           (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_Spare_HSH                           (0x01013A14)

  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableCompRotate_OFF               ( 2)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableCompRotate_WID               ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableCompRotate_MSK               (0x00000004)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableCompRotate_MIN               (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableCompRotate_MAX               (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableCompRotate_DEF               (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableCompRotate_HSH               (0x01023A14)

  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableOdtStatic_OFF                ( 3)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableOdtStatic_WID                ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableOdtStatic_MSK                (0x00000008)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableOdtStatic_MIN                (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableOdtStatic_MAX                (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableOdtStatic_DEF                (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DisableOdtStatic_HSH                (0x01033A14)

  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtUpDnOff_OFF                    ( 4)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtUpDnOff_WID                    ( 6)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtUpDnOff_MSK                    (0x000003F0)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtUpDnOff_MIN                    (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtUpDnOff_MAX                    (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtUpDnOff_DEF                    (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtUpDnOff_HSH                    (0x06043A14)

  #define DDRCOMP_CR_DDRCRCOMPCTL0_FixOdtD_OFF                         (10)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_FixOdtD_WID                         ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_FixOdtD_MSK                         (0x00000400)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_FixOdtD_MIN                         (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_FixOdtD_MAX                         (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL0_FixOdtD_DEF                         (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_FixOdtD_HSH                         (0x010A3A14)

  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqDrvVref_OFF                       (11)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqDrvVref_WID                       ( 4)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqDrvVref_MSK                       (0x00007800)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqDrvVref_MIN                       (-8)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqDrvVref_MAX                       (7) // 0x00000007
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqDrvVref_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqDrvVref_HSH                       (0x840B3A14)

  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_OFF                       (15)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_WID                       ( 5)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_MSK                       (0x000F8000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_MIN                       (-16)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_MAX                       (15) // 0x0000000F
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_DqOdtVref_HSH                       (0x850F3A14)

  #define DDRCOMP_CR_DDRCRCOMPCTL0_CmdDrvVref_OFF                      (20)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_CmdDrvVref_WID                      ( 4)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_CmdDrvVref_MSK                      (0x00F00000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_CmdDrvVref_MIN                      (-8)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_CmdDrvVref_MAX                      (7) // 0x00000007
  #define DDRCOMP_CR_DDRCRCOMPCTL0_CmdDrvVref_DEF                      (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_CmdDrvVref_HSH                      (0x84143A14)

  #define DDRCOMP_CR_DDRCRCOMPCTL0_CtlDrvVref_OFF                      (24)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_CtlDrvVref_WID                      ( 4)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_CtlDrvVref_MSK                      (0x0F000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_CtlDrvVref_MIN                      (-8)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_CtlDrvVref_MAX                      (7) // 0x00000007
  #define DDRCOMP_CR_DDRCRCOMPCTL0_CtlDrvVref_DEF                      (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_CtlDrvVref_HSH                      (0x84183A14)

  #define DDRCOMP_CR_DDRCRCOMPCTL0_ClkDrvVref_OFF                      (28)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_ClkDrvVref_WID                      ( 4)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_ClkDrvVref_MSK                      (0xF0000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_ClkDrvVref_MIN                      (-8)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_ClkDrvVref_MAX                      (7) // 0x00000007
  #define DDRCOMP_CR_DDRCRCOMPCTL0_ClkDrvVref_DEF                      (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL0_ClkDrvVref_HSH                      (0x841C3A14)

#define DDRCOMP_CR_DDRCRCOMPCTL1_REG                                   (0x00003A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompCells_OFF                    ( 0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompCells_WID                    ( 4)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompCells_MSK                    (0x0000000F)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompCells_MIN                    (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompCells_MAX                    (15) // 0x0000000F
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompCells_DEF                    (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompCells_HSH                    (0x04003A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompPC_OFF                       ( 4)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompPC_WID                       ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompPC_MSK                       (0x00000010)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompPC_MIN                       (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompPC_MAX                       (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompPC_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqScompPC_HSH                       (0x01043A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompCells_OFF                   ( 5)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompCells_WID                   ( 4)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompCells_MSK                   (0x000001E0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompCells_MIN                   (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompCells_MAX                   (15) // 0x0000000F
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompCells_DEF                   (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompCells_HSH                   (0x04053A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompPC_OFF                      ( 9)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompPC_WID                      ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompPC_MSK                      (0x00000200)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompPC_MIN                      (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompPC_MAX                      (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompPC_DEF                      (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CmdScompPC_HSH                      (0x01093A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompCells_OFF                   (10)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompCells_WID                   ( 4)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompCells_MSK                   (0x00003C00)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompCells_MIN                   (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompCells_MAX                   (15) // 0x0000000F
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompCells_DEF                   (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompCells_HSH                   (0x040A3A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompPC_OFF                      (14)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompPC_WID                      ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompPC_MSK                      (0x00004000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompPC_MIN                      (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompPC_MAX                      (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompPC_DEF                      (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CtlScompPC_HSH                      (0x010E3A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompCells_OFF                   (15)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompCells_WID                   ( 4)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompCells_MSK                   (0x00078000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompCells_MIN                   (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompCells_MAX                   (15) // 0x0000000F
  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompCells_DEF                   (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompCells_HSH                   (0x040F3A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompPC_OFF                      (19)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompPC_WID                      ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompPC_MSK                      (0x00080000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompPC_MIN                      (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompPC_MAX                      (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompPC_DEF                      (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_ClkScompPC_HSH                      (0x01133A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_TcoCmdOffset_OFF                    (20)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_TcoCmdOffset_WID                    ( 4)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_TcoCmdOffset_MSK                    (0x00F00000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_TcoCmdOffset_MIN                    (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_TcoCmdOffset_MAX                    (15) // 0x0000000F
  #define DDRCOMP_CR_DDRCRCOMPCTL1_TcoCmdOffset_DEF                    (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_TcoCmdOffset_HSH                    (0x04143A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_CompClkOn_OFF                       (24)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CompClkOn_WID                       ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CompClkOn_MSK                       (0x01000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CompClkOn_MIN                       (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CompClkOn_MAX                       (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CompClkOn_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_CompClkOn_HSH                       (0x01183A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqHi_OFF                        (25)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqHi_WID                        ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqHi_MSK                        (0x02000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqHi_MIN                        (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqHi_MAX                        (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqHi_DEF                        (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqHi_HSH                        (0x01193A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqLo_OFF                        (26)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqLo_WID                        ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqLo_MSK                        (0x04000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqLo_MIN                        (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqLo_MAX                        (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqLo_DEF                        (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_VccddqLo_HSH                        (0x011A3A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqRcompStatLegs_OFF                 (27)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqRcompStatLegs_WID                 ( 2)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqRcompStatLegs_MSK                 (0x18000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqRcompStatLegs_MIN                 (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqRcompStatLegs_MAX                 (3) // 0x00000003
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqRcompStatLegs_DEF                 (0x00000003)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DqRcompStatLegs_HSH                 (0x021B3A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_DisableQuickComp_OFF                (29)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DisableQuickComp_WID                ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DisableQuickComp_MSK                (0x20000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DisableQuickComp_MIN                (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DisableQuickComp_MAX                (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DisableQuickComp_DEF                (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_DisableQuickComp_HSH                (0x011D3A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStep_OFF                         (30)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStep_WID                         ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStep_MSK                         (0x40000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStep_MIN                         (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStep_MAX                         (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStep_DEF                         (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStep_HSH                         (0x011E3A18)

  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStepAdv_OFF                      (31)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStepAdv_WID                      ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStepAdv_MSK                      (0x80000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStepAdv_MIN                      (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStepAdv_MAX                      (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStepAdv_DEF                      (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL1_SinStepAdv_HSH                      (0x011F3A18)

#define DDRCOMP_CR_DDRCRCOMPVSSHI_REG                                  (0x00003A1C)

  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicDrvUpVref_OFF                 ( 0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicDrvUpVref_WID                 ( 6)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicDrvUpVref_MSK                 (0x0000003F)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicDrvUpVref_MIN                 (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicDrvUpVref_MAX                 (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicDrvUpVref_DEF                 (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicDrvUpVref_HSH                 (0x06003A1C)

  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtOffset_OFF                       ( 6)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtOffset_WID                       ( 5)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtOffset_MSK                       (0x000007C0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtOffset_MIN                       (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtOffset_MAX                       (31) // 0x0000001F
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtOffset_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtOffset_HSH                       (0x05063A1C)

  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeA_OFF                       (11)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeA_WID                       ( 3)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeA_MSK                       (0x00003800)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeA_MIN                       (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeA_MAX                       (7) // 0x00000007
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeA_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeA_HSH                       (0x030B3A1C)

  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeB_OFF                       (14)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeB_WID                       ( 3)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeB_MSK                       (0x0001C000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeB_MIN                       (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeB_MAX                       (7) // 0x00000007
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeB_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_VtSlopeB_HSH                       (0x030E3A1C)

  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompUpMult_OFF                (17)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompUpMult_WID                ( 7)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompUpMult_MSK                (0x00FE0000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompUpMult_MIN                (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompUpMult_MAX                (127) // 0x0000007F
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompUpMult_DEF                (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompUpMult_HSH                (0x07113A1C)

  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompDnMult_OFF                (24)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompDnMult_WID                ( 7)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompDnMult_MSK                (0x7F000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompDnMult_MIN                (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompDnMult_MAX                (127) // 0x0000007F
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompDnMult_DEF                (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_PanicCompDnMult_HSH                (0x07183A1C)

  #define DDRCOMP_CR_DDRCRCOMPVSSHI_Spare_OFF                          (31)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_Spare_WID                          ( 1)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_Spare_MSK                          (0x80000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_Spare_MIN                          (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_Spare_MAX                          (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_Spare_DEF                          (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHI_Spare_HSH                          (0x011F3A1C)

#define DDRCOMP_CR_DDRCRCOMPOVR_REG                                    (0x00003A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvU_OFF                           ( 0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvU_WID                           ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvU_MSK                           (0x00000001)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvU_MIN                           (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvU_MAX                           (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvU_DEF                           (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvU_HSH                           (0x01003A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvD_OFF                           ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvD_WID                           ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvD_MSK                           (0x00000002)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvD_MIN                           (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvD_MAX                           (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvD_DEF                           (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqDrvD_HSH                           (0x01013A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtU_OFF                           ( 2)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtU_WID                           ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtU_MSK                           (0x00000004)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtU_MIN                           (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtU_MAX                           (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtU_DEF                           (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtU_HSH                           (0x01023A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtD_OFF                           ( 3)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtD_WID                           ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtD_MSK                           (0x00000008)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtD_MIN                           (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtD_MAX                           (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtD_DEF                           (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqOdtD_HSH                           (0x01033A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvU_OFF                          ( 4)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvU_WID                          ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvU_MSK                          (0x00000010)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvU_MIN                          (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvU_MAX                          (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvU_DEF                          (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvU_HSH                          (0x01043A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvD_OFF                          ( 5)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvD_WID                          ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvD_MSK                          (0x00000020)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvD_MIN                          (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvD_MAX                          (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvD_DEF                          (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDrvD_HSH                          (0x01053A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvU_OFF                          ( 6)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvU_WID                          ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvU_MSK                          (0x00000040)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvU_MIN                          (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvU_MAX                          (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvU_DEF                          (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvU_HSH                          (0x01063A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvD_OFF                          ( 7)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvD_WID                          ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvD_MSK                          (0x00000080)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvD_MIN                          (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvD_MAX                          (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvD_DEF                          (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlDrvD_HSH                          (0x01073A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvU_OFF                          ( 8)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvU_WID                          ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvU_MSK                          (0x00000100)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvU_MIN                          (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvU_MAX                          (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvU_DEF                          (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvU_HSH                          (0x01083A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvD_OFF                          ( 9)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvD_WID                          ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvD_MSK                          (0x00000200)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvD_MIN                          (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvD_MAX                          (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvD_DEF                          (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkDrvD_HSH                          (0x01093A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_DqSR_OFF                             (10)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqSR_WID                             ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqSR_MSK                             (0x00000400)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqSR_MIN                             (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqSR_MAX                             (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqSR_DEF                             (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqSR_HSH                             (0x010A3A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdSR_OFF                            (11)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdSR_WID                            ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdSR_MSK                            (0x00000800)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdSR_MIN                            (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdSR_MAX                            (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdSR_DEF                            (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdSR_HSH                            (0x010B3A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlSR_OFF                            (12)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlSR_WID                            ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlSR_MSK                            (0x00001000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlSR_MIN                            (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlSR_MAX                            (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlSR_DEF                            (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlSR_HSH                            (0x010C3A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkSR_OFF                            (13)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkSR_WID                            ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkSR_MSK                            (0x00002000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkSR_MIN                            (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkSR_MAX                            (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkSR_DEF                            (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkSR_HSH                            (0x010D3A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTcoOff_OFF                         (14)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTcoOff_WID                         ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTcoOff_MSK                         (0x00004000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTcoOff_MIN                         (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTcoOff_MAX                         (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTcoOff_DEF                         (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTcoOff_HSH                         (0x010E3A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTcoOff_OFF                        (15)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTcoOff_WID                        ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTcoOff_MSK                        (0x00008000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTcoOff_MIN                        (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTcoOff_MAX                        (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTcoOff_DEF                        (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTcoOff_HSH                        (0x010F3A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTco_OFF                            (16)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTco_WID                            ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTco_MSK                            (0x00010000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTco_MIN                            (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTco_MAX                            (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTco_DEF                            (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_DqTco_HSH                            (0x01103A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTco_OFF                           (17)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTco_WID                           ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTco_MSK                           (0x00020000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTco_MIN                           (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTco_MAX                           (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTco_DEF                           (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdTco_HSH                           (0x01113A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlTco_OFF                           (18)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlTco_WID                           ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlTco_MSK                           (0x00040000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlTco_MIN                           (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlTco_MAX                           (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlTco_DEF                           (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CtlTco_HSH                           (0x01123A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkTco_OFF                           (19)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkTco_WID                           ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkTco_MSK                           (0x00080000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkTco_MIN                           (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkTco_MAX                           (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkTco_DEF                           (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_ClkTco_HSH                           (0x01133A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDn200_OFF                         (20)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDn200_WID                         ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDn200_MSK                         (0x00100000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDn200_MIN                         (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDn200_MAX                         (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDn200_DEF                         (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_CmdDn200_HSH                         (0x01143A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvUp_OFF                       (21)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvUp_WID                       ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvUp_MSK                       (0x00200000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvUp_MIN                       (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvUp_MAX                       (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvUp_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvUp_HSH                       (0x01153A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvDn_OFF                       (22)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvDn_WID                       ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvDn_MSK                       (0x00400000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvDn_MIN                       (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvDn_MAX                       (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvDn_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicDrvDn_HSH                       (0x01163A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_VTComp_OFF                           (23)
  #define DDRCOMP_CR_DDRCRCOMPOVR_VTComp_WID                           ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_VTComp_MSK                           (0x00800000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_VTComp_MIN                           (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_VTComp_MAX                           (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_VTComp_DEF                           (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_VTComp_HSH                           (0x01173A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_LsComp_OFF                           (24)
  #define DDRCOMP_CR_DDRCRCOMPOVR_LsComp_WID                           ( 3)
  #define DDRCOMP_CR_DDRCRCOMPOVR_LsComp_MSK                           (0x07000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_LsComp_MIN                           (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_LsComp_MAX                           (7) // 0x00000007
  #define DDRCOMP_CR_DDRCRCOMPOVR_LsComp_DEF                           (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_LsComp_HSH                           (0x03183A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttUp_OFF                       (27)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttUp_WID                       ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttUp_MSK                       (0x08000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttUp_MIN                       (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttUp_MAX                       (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttUp_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttUp_HSH                       (0x011B3A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttDn_OFF                       (28)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttDn_WID                       ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttDn_MSK                       (0x10000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttDn_MIN                       (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttDn_MAX                       (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttDn_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_PanicVttDn_HSH                       (0x011C3A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompCheckEn_OFF                     (29)
  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompCheckEn_WID                     ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompCheckEn_MSK                     (0x20000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompCheckEn_MIN                     (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompCheckEn_MAX                     (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompCheckEn_DEF                     (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompCheckEn_HSH                     (0x011D3A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompSwapEn_OFF                      (30)
  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompSwapEn_WID                      ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompSwapEn_MSK                      (0x40000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompSwapEn_MIN                      (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompSwapEn_MAX                      (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompSwapEn_DEF                      (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_RcompSwapEn_HSH                      (0x011E3A20)

  #define DDRCOMP_CR_DDRCRCOMPOVR_Spare2_OFF                           (31)
  #define DDRCOMP_CR_DDRCRCOMPOVR_Spare2_WID                           ( 1)
  #define DDRCOMP_CR_DDRCRCOMPOVR_Spare2_MSK                           (0x80000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_Spare2_MIN                           (0)
  #define DDRCOMP_CR_DDRCRCOMPOVR_Spare2_MAX                           (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPOVR_Spare2_DEF                           (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPOVR_Spare2_HSH                           (0x011F3A20)

#define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_REG                           (0x00003A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_Target_OFF                  ( 0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_Target_WID                  ( 6)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_Target_MSK                  (0x0000003F)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_Target_MIN                  (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_Target_MAX                  (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_Target_DEF                  (0x00000034)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_Target_HSH                  (0x06003A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_HiBWDivider_OFF             ( 6)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_HiBWDivider_WID             ( 2)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_HiBWDivider_MSK             (0x000000C0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_HiBWDivider_MIN             (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_HiBWDivider_MAX             (3) // 0x00000003
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_HiBWDivider_DEF             (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_HiBWDivider_HSH             (0x02063A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_LoBWDivider_OFF             ( 8)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_LoBWDivider_WID             ( 2)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_LoBWDivider_MSK             (0x00000300)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_LoBWDivider_MIN             (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_LoBWDivider_MAX             (3) // 0x00000003
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_LoBWDivider_DEF             (0x00000002)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_LoBWDivider_HSH             (0x02083A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SampleDivider_OFF           (10)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SampleDivider_WID           ( 2)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SampleDivider_MSK           (0x00000C00)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SampleDivider_MIN           (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SampleDivider_MAX           (3) // 0x00000003
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SampleDivider_DEF           (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SampleDivider_HSH           (0x020A3A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnIdleActiveSwap_OFF        (12)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnIdleActiveSwap_WID        ( 1)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnIdleActiveSwap_MSK        (0x00001000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnIdleActiveSwap_MIN        (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnIdleActiveSwap_MAX        (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnIdleActiveSwap_DEF        (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnIdleActiveSwap_HSH        (0x010C3A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OpenLoop_OFF                (13)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OpenLoop_WID                ( 1)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OpenLoop_MSK                (0x00002000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OpenLoop_MIN                (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OpenLoop_MAX                (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OpenLoop_DEF                (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OpenLoop_HSH                (0x010D3A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_BWError_OFF                 (14)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_BWError_WID                 ( 2)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_BWError_MSK                 (0x0000C000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_BWError_MIN                 (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_BWError_MAX                 (3) // 0x00000003
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_BWError_DEF                 (0x00000002)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_BWError_HSH                 (0x020E3A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicEn_OFF                 (16)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicEn_WID                 ( 1)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicEn_MSK                 (0x00010000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicEn_MIN                 (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicEn_MAX                 (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicEn_DEF                 (0x00000001)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicEn_HSH                 (0x01103A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnCkePanic_OFF              (17)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnCkePanic_WID              ( 1)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnCkePanic_MSK              (0x00020000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnCkePanic_MIN              (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnCkePanic_MAX              (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnCkePanic_DEF              (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_EnCkePanic_HSH              (0x01113A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicVoltage_OFF            (18)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicVoltage_WID            ( 4)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicVoltage_MSK            (0x003C0000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicVoltage_MIN            (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicVoltage_MAX            (15) // 0x0000000F
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicVoltage_DEF            (0x00000003)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_PanicVoltage_HSH            (0x04123A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_GainBoost_OFF               (22)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_GainBoost_WID               ( 1)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_GainBoost_MSK               (0x00400000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_GainBoost_MIN               (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_GainBoost_MAX               (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_GainBoost_DEF               (0x00000001)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_GainBoost_HSH               (0x01163A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SelCode_OFF                 (23)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SelCode_WID                 ( 1)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SelCode_MSK                 (0x00800000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SelCode_MIN                 (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SelCode_MAX                 (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SelCode_DEF                 (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_SelCode_HSH                 (0x01173A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_DisableOverFlowDrv_OFF      (24)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_DisableOverFlowDrv_WID      ( 1)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_DisableOverFlowDrv_MSK      (0x01000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_DisableOverFlowDrv_MIN      (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_DisableOverFlowDrv_MAX      (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_DisableOverFlowDrv_DEF      (0x00000001)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_DisableOverFlowDrv_HSH      (0x01183A24)

  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OutputCode_OFF              (25)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OutputCode_WID              ( 7)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OutputCode_MSK              (0xFE000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OutputCode_MIN              (0)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OutputCode_MAX              (127) // 0x0000007F
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OutputCode_DEF              (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPVSSHICONTROL_OutputCode_HSH              (0x07193A24)

#define DDRCOMP_CR_DDRCRCOMPCTL2_REG                                   (0x00003A28)

  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVddqOdt_OFF                       ( 0)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVddqOdt_WID                       ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVddqOdt_MSK                       (0x00000001)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVddqOdt_MIN                       (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVddqOdt_MAX                       (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVddqOdt_DEF                       (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVddqOdt_HSH                       (0x01003A28)

  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVttOdt_OFF                        ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVttOdt_WID                        ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVttOdt_MSK                        (0x00000002)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVttOdt_MIN                        (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVttOdt_MAX                        (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVttOdt_DEF                        (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_EnVttOdt_HSH                        (0x01013A28)

  #define DDRCOMP_CR_DDRCRCOMPCTL2_TcoCompVrefCtl_OFF                  ( 2)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_TcoCompVrefCtl_WID                  ( 6)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_TcoCompVrefCtl_MSK                  (0x000000FC)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_TcoCompVrefCtl_MIN                  (-32)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_TcoCompVrefCtl_MAX                  (31) // 0x0000001F
  #define DDRCOMP_CR_DDRCRCOMPCTL2_TcoCompVrefCtl_DEF                  (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_TcoCompVrefCtl_HSH                  (0x86023A28)

  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompUpMult_OFF              ( 8)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompUpMult_WID              ( 4)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompUpMult_MSK              (0x00000F00)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompUpMult_MIN              (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompUpMult_MAX              (15) // 0x0000000F
  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompUpMult_DEF              (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompUpMult_HSH              (0x04083A28)

  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompDnMult_OFF              (12)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompDnMult_WID              ( 5)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompDnMult_MSK              (0x0001F000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompDnMult_MIN              (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompDnMult_MAX              (31) // 0x0000001F
  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompDnMult_DEF              (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_VttPanicCompDnMult_HSH              (0x050C3A28)

  #define DDRCOMP_CR_DDRCRCOMPCTL2_Cben_OFF                            (17)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_Cben_WID                            ( 3)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_Cben_MSK                            (0x000E0000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_Cben_MIN                            (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_Cben_MAX                            (7) // 0x00000007
  #define DDRCOMP_CR_DDRCRCOMPCTL2_Cben_DEF                            (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_Cben_HSH                            (0x03113A28)

  #define DDRCOMP_CR_DDRCRCOMPCTL2_CmdDrvVref200ohm_OFF                (20)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_CmdDrvVref200ohm_WID                ( 4)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_CmdDrvVref200ohm_MSK                (0x00F00000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_CmdDrvVref200ohm_MIN                (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_CmdDrvVref200ohm_MAX                (15) // 0x0000000F
  #define DDRCOMP_CR_DDRCRCOMPCTL2_CmdDrvVref200ohm_DEF                (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_CmdDrvVref200ohm_HSH                (0x04143A28)

  #define DDRCOMP_CR_DDRCRCOMPCTL2_Spare_OFF                           (24)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_Spare_WID                           ( 6)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_Spare_MSK                           (0x3F000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_Spare_MIN                           (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_Spare_MAX                           (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPCTL2_Spare_DEF                           (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_Spare_HSH                           (0x06183A28)

  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepBin_OFF                      (30)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepBin_WID                      ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepBin_MSK                      (0x40000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepBin_MIN                      (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepBin_MAX                      (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepBin_DEF                      (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepBin_HSH                      (0x011E3A28)

  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepAdvBin_OFF                   (31)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepAdvBin_WID                   ( 1)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepAdvBin_MSK                   (0x80000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepAdvBin_MIN                   (0)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepAdvBin_MAX                   (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepAdvBin_DEF                   (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPCTL2_SinStepAdvBin_HSH                   (0x011F3A28)

#define DDRCOMP_CR_DDRCRDATACOMP2_REG                                  (0x00003A2C)

  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttUp_OFF                     ( 0)
  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttUp_WID                     ( 8)
  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttUp_MSK                     (0x000000FF)
  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttUp_MIN                     (0)
  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttUp_MAX                     (255) // 0x000000FF
  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttUp_DEF                     (0x00000000)
  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttUp_HSH                     (0x08003A2C)

  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttDn_OFF                     ( 8)
  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttDn_WID                     ( 8)
  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttDn_MSK                     (0x0000FF00)
  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttDn_MIN                     (0)
  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttDn_MAX                     (255) // 0x000000FF
  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttDn_DEF                     (0x00000000)
  #define DDRCOMP_CR_DDRCRDATACOMP2_PanicVttDn_HSH                     (0x08083A2C)

  #define DDRCOMP_CR_DDRCRDATACOMP2_RcompCmdDn200ohm_OFF               (16)
  #define DDRCOMP_CR_DDRCRDATACOMP2_RcompCmdDn200ohm_WID               ( 6)
  #define DDRCOMP_CR_DDRCRDATACOMP2_RcompCmdDn200ohm_MSK               (0x003F0000)
  #define DDRCOMP_CR_DDRCRDATACOMP2_RcompCmdDn200ohm_MIN               (0)
  #define DDRCOMP_CR_DDRCRDATACOMP2_RcompCmdDn200ohm_MAX               (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRDATACOMP2_RcompCmdDn200ohm_DEF               (0x00000000)
  #define DDRCOMP_CR_DDRCRDATACOMP2_RcompCmdDn200ohm_HSH               (0x06103A2C)

  #define DDRCOMP_CR_DDRCRDATACOMP2_Spare_OFF                          (22)
  #define DDRCOMP_CR_DDRCRDATACOMP2_Spare_WID                          (10)
  #define DDRCOMP_CR_DDRCRDATACOMP2_Spare_MSK                          (0xFFC00000)
  #define DDRCOMP_CR_DDRCRDATACOMP2_Spare_MIN                          (0)
  #define DDRCOMP_CR_DDRCRDATACOMP2_Spare_MAX                          (1023) // 0x000003FF
  #define DDRCOMP_CR_DDRCRDATACOMP2_Spare_DEF                          (0x00000000)
  #define DDRCOMP_CR_DDRCRDATACOMP2_Spare_HSH                          (0x0A163A2C)

#define DDRCOMP_CR_DDRCRCOMPDEBUG0_REG                                 (0x00003A30)

  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvUp_Previous_OFF         ( 0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvUp_Previous_WID         ( 6)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvUp_Previous_MSK         (0x0000003F)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvUp_Previous_MIN         (0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvUp_Previous_MAX         (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvUp_Previous_DEF         (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvUp_Previous_HSH         (0x06003A30)

  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvDn_Previous_OFF         ( 6)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvDn_Previous_WID         ( 6)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvDn_Previous_MSK         (0x00000FC0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvDn_Previous_MIN         (0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvDn_Previous_MAX         (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvDn_Previous_DEF         (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_DqRcompDrvDn_Previous_HSH         (0x06063A30)

  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvUp_Previous_OFF        (12)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvUp_Previous_WID        ( 6)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvUp_Previous_MSK        (0x0003F000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvUp_Previous_MIN        (0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvUp_Previous_MAX        (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvUp_Previous_DEF        (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvUp_Previous_HSH        (0x060C3A30)

  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvDn_Previous_OFF        (18)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvDn_Previous_WID        ( 6)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvDn_Previous_MSK        (0x00FC0000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvDn_Previous_MIN        (0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvDn_Previous_MAX        (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvDn_Previous_DEF        (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_OdtRcompDrvDn_Previous_HSH        (0x06123A30)

  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_ClkRcompDrvUp_Previous_OFF        (24)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_ClkRcompDrvUp_Previous_WID        ( 6)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_ClkRcompDrvUp_Previous_MSK        (0x3F000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_ClkRcompDrvUp_Previous_MIN        (0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_ClkRcompDrvUp_Previous_MAX        (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_ClkRcompDrvUp_Previous_DEF        (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_ClkRcompDrvUp_Previous_HSH        (0x06183A30)

  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_Rcomp_DriftLimit_OFF              (30)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_Rcomp_DriftLimit_WID              ( 2)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_Rcomp_DriftLimit_MSK              (0xC0000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_Rcomp_DriftLimit_MIN              (0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_Rcomp_DriftLimit_MAX              (3) // 0x00000003
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_Rcomp_DriftLimit_DEF              (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG0_Rcomp_DriftLimit_HSH              (0x021E3A30)

#define DDRCOMP_CR_DDRCRCOMPDEBUG1_REG                                 (0x00003A34)

  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_ClkRcompDrvDn_Previous_OFF        ( 0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_ClkRcompDrvDn_Previous_WID        ( 6)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_ClkRcompDrvDn_Previous_MSK        (0x0000003F)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_ClkRcompDrvDn_Previous_MIN        (0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_ClkRcompDrvDn_Previous_MAX        (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_ClkRcompDrvDn_Previous_DEF        (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_ClkRcompDrvDn_Previous_HSH        (0x06003A34)

  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvUp_Previous_OFF        ( 6)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvUp_Previous_WID        ( 6)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvUp_Previous_MSK        (0x00000FC0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvUp_Previous_MIN        (0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvUp_Previous_MAX        (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvUp_Previous_DEF        (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvUp_Previous_HSH        (0x06063A34)

  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvDn_Previous_OFF        (12)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvDn_Previous_WID        ( 6)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvDn_Previous_MSK        (0x0003F000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvDn_Previous_MIN        (0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvDn_Previous_MAX        (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvDn_Previous_DEF        (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CmdRcompDrvDn_Previous_HSH        (0x060C3A34)

  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvUp_Previous_OFF        (18)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvUp_Previous_WID        ( 6)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvUp_Previous_MSK        (0x00FC0000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvUp_Previous_MIN        (0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvUp_Previous_MAX        (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvUp_Previous_DEF        (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvUp_Previous_HSH        (0x06123A34)

  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvDn_Previous_OFF        (24)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvDn_Previous_WID        ( 6)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvDn_Previous_MSK        (0x3F000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvDn_Previous_MIN        (0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvDn_Previous_MAX        (63) // 0x0000003F
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvDn_Previous_DEF        (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_CtlRcompDrvDn_Previous_HSH        (0x06183A34)

  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Drift_detected_OFF                (30)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Drift_detected_WID                ( 1)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Drift_detected_MSK                (0x40000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Drift_detected_MIN                (0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Drift_detected_MAX                (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Drift_detected_DEF                (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Drift_detected_HSH                (0x011E3A34)

  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Spare_OFF                         (31)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Spare_WID                         ( 1)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Spare_MSK                         (0x80000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Spare_MIN                         (0)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Spare_MAX                         (1) // 0x00000001
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Spare_DEF                         (0x00000000)
  #define DDRCOMP_CR_DDRCRCOMPDEBUG1_Spare_HSH                         (0x011F3A34)
#pragma pack(pop)
#endif
